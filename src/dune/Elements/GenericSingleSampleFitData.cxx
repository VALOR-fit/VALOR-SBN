//________________________________________________________________________________________
/*

   Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include <cassert>

#include <TFile.h>
#include <TObjArray.h>
#include <TMath.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TSystem.h>

// fmwk
#include "valor/FitCore/FitModelABC.h"
#include "valor/FitCore/FitParamList.h"
#include "valor/FitCore/PhysHypothesis.h"
#include "valor/Utilities/Rnd.h"
#include "valor/Utilities/UtlStyle.h"
#include "valor/Utilities/UtlNumStat.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Messenger/Messenger.h"
// dune
#include "dune/Conventions/Names.h"
#include "dune/Elements/GenericSingleSampleFitData.h"
#include "dune/Elements/GenericSingleSampleFitModel.h"
#include "dune/Utilities/UtlBinning.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
GenericSingleSampleFitData::GenericSingleSampleFitData() :
  SingleSampleFitDataABC(),
  fBinning(nullptr)
{
  this->Init();
}
//________________________________________________________________________________________
GenericSingleSampleFitData::~GenericSingleSampleFitData() 
{
  this->Clean();
}
//________________________________________________________________________________________
string GenericSingleSampleFitData::Name(void) const
{  
  return fName;
}
//________________________________________________________________________________________
bool GenericSingleSampleFitData::Read(string /*file*/, Option_t * /*opt*/)
{
  
  if (!fBinning) {
    LOG("GenericSingleSampleFitData", pERROR) << "Must call AdoptBinningFromModel() with FitModel before attempting to read file.";
    return false;
  }

  return true;
}
//________________________________________________________________________________________
bool GenericSingleSampleFitData::Write(TObjArray * array, const char * tag, Option_t * write_opt)
{
  LOG("GenericSingleSampleFitData", pINFO)  
    << "Writing results to input object array...";
  LOG("GenericSingleSampleFitData", pDEBUG) 
    << "tag = " << tag << ", write option = " << write_opt;

  string opt = (write_opt) ? write_opt : "data_vf";

  if(opt.find("all") != string::npos) {
    opt = "data_vf,data_rf +slices +SB";
    LOG("GenericSingleSampleFitData", pDEBUG) << "Write option replaced with = " << opt;
  }

  if(!array) {
    LOG("GenericSingleSampleFitData", pERROR) << "Null input object array.";
    return false;
  }

  const SingleSampleKineBinning & binning = *fBinning;
  const VALORBinning & reco_smp = *(binning.RecoSmpBinning());
  const VALORBinning & reco_opt = *(binning.RecoOptBinning());
  
  //
  // Write out data distributions (VALORArray or bare ROOT format)
  //

  if(opt.find("data_vf") != string::npos || opt.find("data_rf") != string::npos) {

    // binning optimised for fit CPU performance
    if(fDataObNull)  {
      LOG("GenericSingleSampleFitData",pFATAL) << "Trying to write null data.";
      util::Die(-1) ; return false;
    }
    // Add data in VALOR array format
    if(opt.find("data_vf") != string::npos) {
      assert(fDataOb);
      fDataOb->SetName(TString::Format("%s_%s_%s",tag,"data_ob_vf",fName.c_str()).Data());
      LOG("GenericSingleSampleFitData", pDEBUG) << "Adding: " << fDataOb->GetName();
      array->Add(fDataOb);
    }

    // Add data in ROOT histogram format
    if(opt.find("data_rf") != string::npos) {
      assert(fDataOb);
      const std::vector<KineVar_t>  & reco_vars = reco_opt.KineVars();
      if(reco_vars.size() == 1) {
        conv::KineSpace_t ks(util::KineSpaceFromKineVar(reco_vars[0]));
        TH1 * hob = util::binning::Make1DHistogram(*fDataOb,binning,ks,false);
        if(hob) {
          TString hobname = TString::Format("%s_%s_%s",tag,"data_ob_rf",fName.c_str());
          hob->SetName(hobname.Data());
          array->Add(hob);
        }
      }
      else if(reco_vars.size() == 2) {
        conv::KineSpace_t ks = util::KineSpaceFromKineVars(reco_vars);
        if(ks != conv::kspUndefined) {
          TH2 *hob = util::binning::Make2DOptimisedHistogram(*fDataOb,binning,reco_vars);
          if(hob) {
            TString hobname = TString::Format("%s_%s_%s",tag,"data_ob_rf",fName.c_str());
            hob->SetName(hobname.Data());
            array->Add(hob);
          }
        }
      }
      else {
        LOG("GenericSingleSampleFitData", pWARN)
          << "Tried writing data to ROOT format, but number of kine vars != 1 or 2 (" << fDataOb->GetName() << ")";
      }

      // Write 1d slices for the total in reco only
      if (opt.find("slices") != string::npos) {
        for (const conv::KineVar_t kv : reco_vars) {
          conv::KineSpace_t ks(util::KineSpaceFromKineVar(kv));
          if (ks == conv::kspUndefined) {continue;}
          TH1 * hob = util::binning::Make1DHistogram(*fDataOb,binning,ks,false);
          if(hob) {
            TString hobname = TString::Format("%s_%s_%s_%s",tag,"data_ob_rf_slice",fName.c_str(),util::AsString(kv).c_str());
            hob->SetName(hobname.Data());
            array->Add(hob);
          }
        }
      }

    }

    // regular/fine binning for plotting
    if(opt.find("+SB") != string::npos) {
      assert(!fDataSbNull);

      // Add data in VALOR array format
      if(opt.find("data_vf") != string::npos) {
        assert(fDataSb);
        fDataSb->SetName(TString::Format("%s_%s_%s",tag,"data_sb_vf",fName.c_str()));
        LOG("GenericSingleSampleFitData", pDEBUG) << "Adding: " << fDataSb->GetName();
        array->Add(fDataSb);
      }//data_vf

      // Add data in ROOT histogram format
      if(opt.find("data_rf") != string::npos) {
        assert(fDataSb);
        const std::vector<KineVar_t>  & reco_vars = reco_smp.KineVars();
        if(reco_vars.size() == 1) {
          conv::KineSpace_t ks(util::KineSpaceFromKineVar(reco_vars[0]));
          TH1 * hsb = util::binning::Make1DHistogram(*fDataSb,binning,ks,false);
          if(hsb) {
            TString hsbname = TString::Format("%s_%s_%s",tag,"data_sb_rf",fName.c_str());
            hsb->SetName(hsbname.Data());
            array->Add(hsb);
          }
        }
        else if(reco_vars.size() == 2) {
          conv::KineSpace_t ks = util::KineSpaceFromKineVars(reco_vars);
          if(ks != conv::kspUndefined) {
            TH2 *hsb = util::binning::Make2DSimpleHistogram(*fDataSb,binning,reco_vars);
            if(hsb) {
              TString hsbname = TString::Format("%s_%s_%s",tag,"data_sb_rf",fName.c_str());
              hsb->SetName(hsbname.Data());
              array->Add(hsb);
            }
          }
        }
        else {
          LOG("GenericSingleSampleFitData", pWARN)
            << "Tried writing data to ROOT format, but number of kine vars != 1 or 2 (" << fDataSb->GetName() << ")";
        }

        // Write 1d slices for the total in reco only
        if (opt.find("slices") != string::npos) {
          for (const conv::KineVar_t kv : reco_vars) {
            conv::KineSpace_t ks(util::KineSpaceFromKineVar(kv));
            if (ks == conv::kspUndefined) {continue;}

            TH1 * hsb = util::binning::Make1DHistogram(*fDataSb,binning,ks,true);
            if(hsb) {
              TString hsbname = TString::Format("%s_%s_%s_%s",tag,"data_sb_rf_slice",fName.c_str(),util::AsString(kv).c_str());
              hsb->SetName(hsbname.Data());
              array->Add(hsb);
            }
          }
        }

      }

    }//+SB
  }//data_vf, data_rf

  LOG("GenericSingleSampleFitData", pINFO)  << "Done!";

  return true;
}
//________________________________________________________________________________________
bool GenericSingleSampleFitData::Write(
    const char * filename, const char * tag, const char * write_opt, Option_t * file_opt)
{
  LOG("GenericSingleSampleFitData",pNOTICE) 
    << "Writing results to file: [" << filename << "]";

  TObjArray * array = new TObjArray();
  this->Write(array,tag,write_opt);

  Option_t * used_file_opt = (file_opt == 0) ? "recreate" : file_opt;
  TFile f(filename, used_file_opt);
  array->Write();
  f.Close();

  return true;
}
//________________________________________________________________________________________
bool GenericSingleSampleFitData::Write(util::ToyStream* stream, Option_t * write_opt)
{
   string opt = (write_opt) ? write_opt : "";
   assert(fDataOb);
   fDataOb->SetName(TString::Format("%s_%s", "data_ob_vf", fName.c_str()));
   stream->Write(fDataOb);

   if(opt.find("+SB") != string::npos)
   {
      assert(fDataSb);
      fDataSb->SetName(TString::Format("%s_%s", "data_sb_vf", fName.c_str()));
      stream->Write(fDataSb);
   } //+SB

   return true;
}
//________________________________________________________________________________________
bool GenericSingleSampleFitData::Read(util::ToyStream* stream, Option_t * read_opt)
{
  string opt = (read_opt) ? read_opt : "";
  assert(fDataOb);
  fDataOb->SetName(TString::Format("%s_%s", "data_ob_vf", fName.c_str()));
  stream->Read(fDataOb);

  if(opt.find("+SB") != string::npos)
  {
    assert(fDataSb);
    fDataSb->SetName(TString::Format("%s_%s", "data_sb_vf", fName.c_str()));
    stream->Read(fDataSb);
  } //+SB

  return true;
}
//________________________________________________________________________________________
long GenericSingleSampleFitData::StreamSize(Option_t* opt_in) const
{
  if (!fBinning) {
    LOG("GenericSingleSampleFitData", pERROR) << "Must call AdoptBinningFromModel() with FitModel "
                                              << "before attempting to determine the toy size.";
    return false;
  }

  string opt = (opt_in) ? opt_in : "";
  long size = 0;

  assert(fDataOb);
  size += fDataOb->StreamSize();

  if(opt.find("+SB") != string::npos)
  {
    assert(fDataSb);
    size += fDataSb->StreamSize();
  } //+SB

  return size;
}
//________________________________________________________________________________________
bool GenericSingleSampleFitData::Generate(
    FitModelABC * model_abc, const FitParamList & fp, bool fluctuate)
{
  LOG("GenericSingleSampleFitData",pINFO) 
    << "Generating a toy-MC expt with the following params: " << fp;
  LOG("GenericSingleSampleFitData",pINFO)
    << "Stat. fluctuations are turned-" << ((fluctuate)? "ON" : "OFF");
  
  bool ok = model_abc->Generate(fp,"+SB");
  if(!ok) {
    LOG("GenericSingleSampleFitData",pERROR) 
      << "Could not generate predictions with model: " << model_abc->Name()
      << " and input params: " << fp;
    return false;
  }
  
  return this->Generate(model_abc,fluctuate);
}
//________________________________________________________________________________________
bool GenericSingleSampleFitData::Generate(
    FitModelABC * model_abc, const PhysHypothesis & ph, bool fluctuate)
{
  LOG("GenericSingleSampleFitData",pINFO) 
    << "Generating a toy-MC expt with the following params: " << ph;
  LOG("GenericSingleSampleFitData",pINFO)
    << "Stat. fluctuations are turned-" << ((fluctuate)? "ON" : "OFF");

  bool ok = model_abc->Generate(ph,"+SB");
  if(!ok) {
    LOG("GenericSingleSampleFitData",pERROR) 
      << "Could not generate predictions with model: " << model_abc->Name()
      << " with systematic tweaks: " << model_abc->Tweaks()
      << " and input params: " << ph;
    return false;
  }

  return this->Generate(model_abc,fluctuate);
}
//________________________________________________________________________________________
bool GenericSingleSampleFitData::Generate(FitModelABC * model_abc, bool fluctuate, Option_t * option)
{
  this->AdoptBinningFromModel(model_abc);

  bool update_sb = false;
  if(option) {
    string opt = option;
    if(opt.find("+SB") != string::npos) {
      update_sb = true;
    }
  }
  Option_t * write_opt = "pdft_vf";
  if(update_sb) { write_opt = "pdft_vf +SB"; }

  TObjArray array;
  model_abc->Write(&array, "curr", write_opt);

  this->Zero("all");
#ifndef __VALOR_FMWK_PENALTY_ONLY__
  LOG("GenericSingleSampleFitData",pINFO) 
    << "Generating toy-MC for: " 
    << fName;

  if(!update_sb) {
    // Updating only the templates using the optimized binning
    TString ob_name = TString::Format("curr_pdft_ob_vf_%s",fModelName.c_str());
    VALORArray * pdf_ob = (VALORArray*) array.FindObject(ob_name.Data());
    assert(pdf_ob);
    const int nbins_ob = pdf_ob->GetSize();
    assert(nbins_ob==fDataOb->GetSize());

    for(int ibin_ob = 0 ; ibin_ob < nbins_ob ; ibin_ob ++) {
      double nmc   = pdf_ob->GetArray()[ibin_ob];
      double ndata = (fluctuate) ? Rnd::Instance()->RndToyMCstat().Poisson(nmc) : nmc;
      fDataOb->GetArray()[ibin_ob] = ndata;

      LOG("GenericSingleSampleFitData",pDEBUG)
        << "(reco_ob_idx = "<<ibin_ob
        << "): N_{MC} = " << nmc << ", N_{Data} = " << ndata;
    }//ibin_ob
  }
  else {
    // Updating the templates using both the simple and optimised binning
    TString sb_name = TString::Format("curr_pdft_sb_vf_%s",fModelName.c_str());
    VALORArray * pdf_sb = (VALORArray*) array.FindObject(sb_name.Data());
    assert(pdf_sb);
    const int nbins_sb = pdf_sb->GetSize();
    assert(nbins_sb==fDataSb->GetSize());

    for(int ibin_sb = 0 ; ibin_sb < nbins_sb ; ibin_sb ++) {
      double nmc   = pdf_sb->GetArray()[ibin_sb];
      double ndata = (fluctuate) ? Rnd::Instance()->RndToyMCstat().Poisson(nmc) : nmc;
      fDataSb->GetArray()[ibin_sb] = ndata;

      LOG("GenericSingleSampleFitData",pDEBUG)
        << "(reco_sb_idx = "<<ibin_sb
        << "): N_{MC} = " << nmc << ", N_{Data} = " << ndata;

      // Map to distributions with optimized binning
      //
      unsigned int ibin_ob = fBinning->GetRecoOptBin(ibin_sb);
      fDataOb->GetArray()[ibin_ob] += ndata;
    }//ibin_sb
  }
#endif //__VALOR_FMWK_PENALTY_ONLY__
 
   LOG("GenericSingleSampleFitData",pINFO) << fName << ": N_{Data} SB = " <<
      fDataSb->Integral() << " ; N_{Data} OB = " << fDataOb->Integral();

  return true;
}
//________________________________________________________________________________________
int GenericSingleSampleFitData::NumOfBins(Option_t * /*opt*/) const
{
  int nbins = 0;

  for(int izone = 0; izone < kNMaxBinZones; izone++) {
    const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
    const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
    if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
    int nbins_curr = n_enu_reco_bins * n_y_reco_bins;
    nbins += nbins_curr;
  }//izone

  return nbins;
}
//________________________________________________________________________________________
double GenericSingleSampleFitData::GetFitStatistic(
    FitModelABC* model_abc, const FitParamList & fp, Option_t * opt, std::map<std::string,double> * likelihood_components)
{
  bool ok = model_abc->Generate(fp);
  assert(ok);

  return this->GetFitStatistic(model_abc,opt, likelihood_components);
}
//________________________________________________________________________________________
double GenericSingleSampleFitData::GetFitStatistic(
    FitModelABC * model_abc, const PhysHypothesis & ph, Option_t * opt, std::map<std::string,double> * likelihood_components)
{
  bool ok = model_abc->Generate(ph);
  assert(ok);

  return this->GetFitStatistic(model_abc,opt, likelihood_components);  
}
//________________________________________________________________________________________
double GenericSingleSampleFitData::GetFitStatistic(
    FitModelABC * model_abc, Option_t * /*opt*/, std::map<std::string,double> * likelihood_components) 
{
  TObjArray * array = new TObjArray();
  model_abc->Write(array, "curr", "pdft_vf");

  // Calculate statistic
  double S = 0;
  
  // Counters for total number of events to we can do rate-only
  double tot_nmc   = 0.;
  double tot_ndata = 0.;
  
  TString name = TString::Format("curr_pdft_ob_vf_%s",fModelName.c_str());
  VALORArray * pdf = (VALORArray*) array->FindObject(name.Data());
  assert(pdf);
  assert(pdf->GetSize() == fDataOb->GetSize());
  for(int ibin = 0; ibin < pdf->GetSize(); ibin++) {
    double nmc   = pdf    ->GetArray()[ibin];
    double ndata = fDataOb->GetArray()[ibin];
    tot_nmc   += nmc;
    tot_ndata += ndata;
    double dS = util::ChisqPoisson(ndata, nmc);
    S += dS;
  }//ier
  S = TMath::Max(0.,S);
  
  double S_rate_only = TMath::Max(0.,util::ChisqPoisson(tot_ndata, tot_nmc));

  LOG("GenericSingleSampleFitData",pINFO)
    << fName<<" - Current fit statistic (rate+shape) = " << S;
  LOG("GenericSingleSampleFitData",pINFO)
    << fName<<" - Current fit statistic (rate only) = " << S_rate_only
    << ", from N data = " << tot_ndata << ", N MC = " << tot_nmc;
  
  // Write our contribution to the likelihood
  if (likelihood_components) {
    TString likelihood_name = TString::Format("sample_%s",fName.c_str());
    TString likelihood_name_rate_only = TString::Format("sample_rate_only_%s",fName.c_str());
    (*likelihood_components)[likelihood_name.Data()] = S;
    (*likelihood_components)[likelihood_name_rate_only.Data()] = S_rate_only;
  }
    
  delete array;

  return S;
}
//________________________________________________________________________________________
void GenericSingleSampleFitData::Init(void)
{
  LOG("GenericSingleSampleFitData",pDEBUG) << "Initializing...";

  fName = "none";

  fDetector = kdUndefined;
  fBeam     = kbUndefined;
  fSample   = ksUndefined;

  fDataObNull= true;
  fDataOb    = 0;
  fDataSbNull = true;
  fDataSb     = 0;

  fBinning = 0;
}
//________________________________________________________________________________________
void GenericSingleSampleFitData::Book(void)
{
  LOG("GenericSingleSampleFitData",pDEBUG) << "Booking...";
  assert(fBinning);
  assert(fDetector != kdUndefined);
  assert(fBeam     != kbUndefined);
  assert(fSample   != ksUndefined);
  assert(fKSp      != kspUndefined);

  fName      = util::nm::DSetName(fDetector, fBeam, fSample, fKSp);
  fModelName = util::nm::MdlName (fDetector, fBeam, fSample, fKSp);
  
  const VALORBinning * reco_ob = fBinning->RecoOptBinning();
  const VALORBinning * reco_sb = fBinning->RecoSmpBinning();

  fDataObNull = false;
  fDataOb     = new VALORArray(reco_ob->NBins());
  fDataSbNull = false;
  fDataSb     = new VALORArray(reco_sb->NBins());
}
//________________________________________________________________________________________
void GenericSingleSampleFitData::Clean(void)
{
  LOG("GenericSingleSampleFitData",pDEBUG) << "Cleaning-up...";

  if (!fDataObNull) {
    fDataObNull = true;
    if (fDataOb) {delete fDataOb;}
    fDataOb = 0;
  }
  if (!fDataSbNull) {
    fDataSbNull = true;
    if(fDataSb) {delete fDataSb;}
    fDataSb = 0;
  }
}
//________________________________________________________________________________________
void GenericSingleSampleFitData::Zero(Option_t * opt)
{
  LOG("GenericSingleSampleFitData",pDEBUG) << "Zeroing-out (option: " << opt << ") ...";

  string option = (opt) ? opt : "all";

  if (!fDataObNull) { fDataOb->SetAll(0.); }
  if (!fDataSbNull) { fDataSb->SetAll(0.); }
}
//________________________________________________________________________________________
std::string GenericSingleSampleFitData::GetPDFIntegralAsString(Option_t * opt_in)
{
  double integral = -999;

  std::string opt = (opt_in) ? opt_in : "";
  if(opt.find("SB") != string::npos) {
    integral = fDataSb->Integral();
  }
  else {
    integral = fDataOb->Integral();
  }

  TString temp = TString::Format("%s total data PDF integral = %.5lf", this->Name().c_str(), integral);
  std::string to_print = temp.Data();

  return to_print;
}
//________________________________________________________________________________________
void GenericSingleSampleFitData::AdoptBinningFromModel(FitModelABC* model_abc)
{
  GenericSingleSampleFitModel * model = dynamic_cast<GenericSingleSampleFitModel*>(model_abc);
  if(fBinning != model->GetBinning()){
    if(!model->GetBinning()) {
      LOG("GenericSingleSampleFitData",pERROR)
        << "Failed to adopt the binning from the model, as the model had no binning set";
      util::Die(-1);
    }
    this->Clean();
    fBinning = model->GetBinning();
    this->Book();
  }

  if(!fBinning) {
    LOG("GenericSingleSampleFitData",pERROR) << "Failed to adopt the binning from the model";
    util::Die(-1);
  }
}
//________________________________________________________________________________________
util::ToyStream* GenericSingleSampleFitData::InitToyStream(const string file_name, const string read_or_write, const string opt)
{
  return new util::ToyStream(file_name, read_or_write, typeid(this), this->Name(), opt, this->StreamSize());
}
//________________________________________________________________________________________
