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

// fmwk
#include "FitCore/FitModelABC.h"
#include "FitCore/FitParamList.h"
#include "FitCore/PhysHypothesis.h"
#include "Utilities/Rnd.h"
#include "Utilities/UtlStyle.h"
#include "Utilities/UtlNumStat.h"
#include "Messenger/Messenger.h"
// dune
#include "Conventions/Names.h"
#include "Elements/SingleSampleFitDataA.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
SingleSampleFitDataA::SingleSampleFitDataA() :
SingleSampleFitDataABC()
{
  this->Init();
}
//________________________________________________________________________________________
SingleSampleFitDataA::~SingleSampleFitDataA() 
{
  this->Clean();
}
//________________________________________________________________________________________
string SingleSampleFitDataA::Name(void)
{  
  return fName;
}
//________________________________________________________________________________________
bool SingleSampleFitDataA::Read(string /*file*/, Option_t * /*opt*/)
{
  assert(fDetector != kdUndefined);
  assert(fBeam     != kbUndefined);
  assert(fSample   != ksUndefined);

  fName = util::nm::DSetName(fDetector, fBeam, fSample, "");

  this->Book();
//this->Zero();

  return true;
}
//________________________________________________________________________________________
bool SingleSampleFitDataA::Write(TObjArray * array, const char * tag, Option_t * write_opt)
{
  LOG("SingleSampleFitDataA", pINFO)  
     << "Writing results to input object array...";
  LOG("SingleSampleFitDataA", pDEBUG) 
     << "tag = " << tag << ", write option = " << write_opt;

  string opt = (write_opt) ? write_opt : "data_vf";

  if(opt.find("all") != string::npos) {
    opt = "data_vf,data_rf +slices +SB";
    LOG("SingleSampleFitDataA", pDEBUG) << "Write option replaced with = " << opt;
  }

  if(!array) {
     LOG("SingleSampleFitDataA", pERROR) << "Null input object array.";
     return false;
  }

  valor::util::SetDefaultStyle();

  //
  // Write out data distributions (VALORArray or bare ROOT format)
  //

  if(opt.find("data_vf") != string::npos || opt.find("data_rf") != string::npos) {

     // binning optimised for fit CPU performance
     for(int izone = 0; izone < kNMaxBinZones; izone++) {
       if(fDataObNull[izone]) continue;
       // Add data in VALOR array format
       const char * name = Form("%s_%s_z%d",
          util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), izone);
       if(opt.find("data_vf") != string::npos) {
          assert(fDataOb[izone]);
          fDataOb[izone]->SetName(Form("%s_%s_%s",tag,"data_ob_vf",name));
          LOG("SingleSampleFitDataA", pDEBUG) << "Adding: " << fDataOb[izone]->GetName();
          array->Add(fDataOb[izone]);
       }
       // Add data in ROOT format if requested
       // -----
       // NOTE: The following could be simplified substantially (conversion from VALOR 2-D
       // array to ROOT TH2D could happen elsewhere generically)
       // -----
       if(opt.find("data_rf") != string::npos) {
          const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
          const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
          if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
          const double * enu_reco_bins = util::ErecoBinEdges(fSample,izone);
          const double * y_reco_bins   = util::YrecoBinEdges(fSample,izone);
          TH2D * h2 = new TH2D("h2", "VALOR/DUNE ND (Ereco,yreco) data = f(beam,sample,zone)",
              n_enu_reco_bins, enu_reco_bins, n_y_reco_bins, y_reco_bins);
          h2->SetName(Form("%s_%s_%s",tag,"data_ob_rf",name));
          for(int ier = 0; ier < n_enu_reco_bins; ier++) {
            for(int iy = 0; iy < n_y_reco_bins; iy++) {
              double val = fDataOb[izone]->GetEntry(ier,iy);
              h2->SetBinContent(ier+1,iy+1,val);
            }//iy
          }//ier
          // add to object array and clean-up
          LOG("SingleSampleFitDataA", pDEBUG) << "Adding: " << h2->GetName();
          array->Add(h2);
          // delete h2; ???? // MEMORY LEAK?
       }
     }//izone

     // regular/fine binning for plotting
     if(opt.find("+SB") != string::npos) {
          const char * name = Form("%s_%s",
             util::AsString(fBeam).c_str(), util::AsString(fSample).c_str());
          assert(!fDataSbNull);
          // Add data in VALOR array format
          if(opt.find("data_vf") != string::npos) {
             assert(fDataSb);
             fDataSb->SetName(Form("%s_%s_%s",tag,"data_sb_vf",name));
             LOG("SingleSampleFitDataA", pDEBUG) << "Adding: " << fDataSb->GetName();
             array->Add(fDataSb);
          }//data_vf
          // Add data in ROOT format if requested
          // -----
          // NOTE: The following could be simplified substantially (conversion from VALOR 2-D
          // array to ROOT TH2D could happen elsewhere generically)
          // -----
          if(opt.find("data_rf") != string::npos) {
              const int n_y_reco_bins_sb = util::NumYrecoBinsSb(fSample);
              const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(fSample);
              TH2D * h2 = new TH2D("h2","VALOR/DUNE ND (Ereco,yreco) data = f(beam,sample)",
                 kNErecoBinsSb, kErecoBinEdgesSb, n_y_reco_bins_sb, y_reco_bin_edges_sb);
              h2->SetName(Form("%s_%s_%s",tag,"data_sb_rf",name));
              for(int ier = 0; ier < kNErecoBinsSb; ier++) {
                for(int iy = 0; iy < n_y_reco_bins_sb; iy++) {
                  double val = fDataSb->GetEntry(ier,iy);
                  h2->SetBinContent(ier+1,iy+1,val);
                }//iy
              }//ier
              // add to object array and clean-up
              LOG("SingleSampleFitDataA", pDEBUG) << "Adding: " << h2->GetName();
              array->Add(h2);
              // delete h2; ???? // MEMORY LEAK?
          }//data_vf
     }//+SB
  }//data_vf, data_rf

  //
  // Write out the slices of the data distributions (bare ROOT format)
  //
  // -----
  // NOTE: The following could be simplified substantially (conversion from VALOR 2-D
  // array to ROOT TH1D slices could happen elsewhere generically)
  // -----
  if(opt.find("+slices") != string::npos) {

      for(int izone = 0; izone < kNMaxBinZones; izone++) {
          const char * name = Form("%s_%s_z%d",
            util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), izone);
          // get binning
          const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
          const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
          if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
          const double * enu_reco_bins = util::ErecoBinEdges(fSample,izone);
          const double * y_reco_bins   = util::YrecoBinEdges(fSample,izone);
          // create slices of the data (function of Ereco, for given yreco bin)
          TH1D * htot = new TH1D("htot",
              "VALOR/DUNE ND data: Ereco spectrum = f(beam,sample,zone)", n_enu_reco_bins, enu_reco_bins);
          htot->SetName(Form("%s_%s_%s",tag, "data_slice_ob_rf",name) );
          htot->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
          htot->GetYaxis()->SetTitle("Number of events /bin");
          for(int iy = 0; iy < n_y_reco_bins; iy++) {
            TH1D * h = new TH1D("h",
                Form("VALOR/DUNE ND data: Ereco spectrum = f(beam,sample,zone) for y in [%f,%f]",
                     y_reco_bins[iy],y_reco_bins[iy+1]),
                n_enu_reco_bins, enu_reco_bins);
            h->SetName(Form("%s_%s_%s_y%d",tag, "data_slice_ob_rf",name,iy) );
            h->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
            h->GetYaxis()->SetTitle("Number of events /bin");
            for(int ier = 0; ier < n_enu_reco_bins; ier++) {
              double val = fDataOb[izone]->GetEntry(ier,iy);
              h->SetBinContent(ier+1, val);
              htot->SetBinContent(ier+1, htot->GetBinContent(ier+1) + val);
            }//ier
            // add to obj array and clean-up
            LOG("SingleSampleFitDataA", pDEBUG) << "Adding: " << h->GetName();
            array->Add(h);
            //delete h; ??? MEM LEAK??
          }//iy
          LOG("SingleSampleFitDataA", pDEBUG) << "Adding: " << htot->GetName();
          array->Add(htot);
          //delete htot; ??? MEM LEAK??
      }//izone

      if(opt.find("+SB") != string::npos) {
          const char * name = Form("%s_%s",
            util::AsString(fBeam).c_str(), util::AsString(fSample).c_str());
          // create slices of the total PDF (function of Ereco, for given yreco bin)
          const int n_y_reco_bins_sb = util::NumYrecoBinsSb(fSample);
          const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(fSample);
          TH1D * htot = new TH1D("htot",
              "VALOR/DUNE ND data: Ereco spectrum = f(beam,sample)", kNErecoBinsSb, kErecoBinEdgesSb);
          htot->SetName(Form("%s_%s_%s",tag, "data_slice_sb_rf",name) );
          htot->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
          htot->GetYaxis()->SetTitle("Number of events /bin");
          for(int iy = 0; iy < n_y_reco_bins_sb; iy++) {
            TH1D * h = new TH1D("h",
                Form("VALOR/DUNE ND data: Ereco spectrum = f(beam,sample) for y in [%f,%f]",
                     y_reco_bin_edges_sb[iy], y_reco_bin_edges_sb[iy+1]),
                kNErecoBinsSb, kErecoBinEdgesSb);
            h->SetName(Form("%s_%s_%s_y%d",tag, "data_slice_sb_rf",name,iy) );
            h->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
            h->GetYaxis()->SetTitle("Number of events /bin /%f POT");
            for(int ier = 0; ier < kNErecoBinsSb; ier++) {
              double val = fDataSb->GetEntry(ier,iy);
              h->SetBinContent(ier+1, val);
              htot->SetBinContent(ier+1, htot->GetBinContent(ier+1) + val);
            }//ier
            // add to obj array and clean-up
            LOG("SingleSampleFitDataA", pDEBUG) << "Adding: " << h->GetName();
            array->Add(h);
            //delete h; ??? MEM LEAK??
          }//iy
          LOG("SingleSampleFitDataA", pDEBUG) << "Adding: " << htot->GetName();
          array->Add(htot);
          //delete htot; ??? MEM LEAK??
      }//+SB?
  }//+slices

  LOG("SingleSampleFitDataA", pINFO)  << "Done!";

  return true;
}
//________________________________________________________________________________________
bool SingleSampleFitDataA::Write(
  const char * filename, const char * tag, const char * write_opt, Option_t * file_opt)
{
  LOG("SingleSampleFitDataA",pNOTICE) 
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
bool SingleSampleFitDataA::Generate(
    FitModelABC * model_abc, const FitParamList & fp, bool fluctuate)
{
  LOG("SingleSampleFitDataA",pINFO) 
     << "Generating a toy-MC expt with the following params: " << fp;
  LOG("SingleSampleFitDataA",pINFO)
     << "Stat. fluctuations are turned-" << ((fluctuate)? "ON" : "OFF");

  bool ok = model_abc->Generate(fp,"+SB");
  if(!ok) {
    LOG("SingleSampleFitDataA",pERROR) 
       << "Could not generate predictions with model: " << model_abc->Name()
       << " and input params: " << fp;
    return false;
  }

  return this->Generate(model_abc,fluctuate);
}
//________________________________________________________________________________________
bool SingleSampleFitDataA::Generate(
   FitModelABC * model_abc, const PhysHypothesis & ph, bool fluctuate)
{
  LOG("SingleSampleFitDataA",pINFO) 
     << "Generating a toy-MC expt with the following params: " << ph;
  LOG("SingleSampleFitDataA",pINFO)
      << "Stat. fluctuations are turned-" << ((fluctuate)? "ON" : "OFF");

  bool ok = model_abc->Generate(ph,"+SB");
  if(!ok) {
    LOG("SingleSampleFitDataA",pERROR) 
       << "Could not generate predictions with model: " << model_abc->Name()
       << " with systematic tweaks: " << model_abc->Tweaks()
       << " and input params: " << ph;
    return false;
  }

  return this->Generate(model_abc,fluctuate);
}
//________________________________________________________________________________________
bool SingleSampleFitDataA::Generate(FitModelABC * model_abc, bool fluctuate)
{
  TObjArray * array = new TObjArray();
  model_abc->Write(array, "curr", "pdft_vf +SB");
  
  this->Zero("all");

  LOG("SingleSampleFitDataA",pINFO) 
     << "Generating toy-MC for: " 
     << util::AsString(fBeam) << " / " << util::AsString(fSample);

  const int n_y_reco_bins_sb = util::NumYrecoBinsSb(fSample);

  const char * name = Form("curr_pdft_sb_vf_%s_%s", 
       util::AsString(fBeam).c_str(), util::AsString(fSample).c_str());
  VALORArray * pdf = (VALORArray*) array->FindObject(name);
  assert(pdf);           
  for(int ier = 0; ier < kNErecoBinsSb; ier++) {
     for(int iy = 0; iy < n_y_reco_bins_sb; iy++) {
        double nmc   = pdf->GetEntry(ier,iy);
        double ndata = (fluctuate) ? Rnd::Instance()->RndToyMCstat().Poisson(nmc) : nmc;
        fDataSb->SetEntry(ndata,ier,iy);

        LOG("SingleSampleFitDataA",pDEBUG) 
           << "(E_reco idx = " << ier << ", y_reco idx = " << iy 
           << "): N_{MC} = " << nmc << ", N_{Data} = " << ndata;

        // Map to distributions with optimized binning
        //
        const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(fSample);
        double enu_reco = kErecoBinEdgesSb[ier]   + (kErecoBinEdgesSb[ier+1]-kErecoBinEdgesSb[ier])/2.;
        double y_reco   = y_reco_bin_edges_sb[iy] + (y_reco_bin_edges_sb[iy+1]-y_reco_bin_edges_sb[iy])/2.;
        int izone = util::BinZone(fSample, enu_reco, y_reco);
        if(izone < 0) {
//         LOG("SingleSampleFitDataA",pFATAL) - turn that to fatal after binning optimization is done
           LOG("SingleSampleFitDataA",pWARN)
              << " ** No bin zone for toy MC event (" << " (" << util::AsString(fSample) << ")"
              << ", enu_reco = " << enu_reco << " GeV, " << " y_reco = " << y_reco << ")";
//         exit(1);
        }
        const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
        const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
        const double * enu_reco_bin_edges  = util::ErecoBinEdges(fSample,izone);
        const double * y_reco_bin_edges    = util::YrecoBinEdges(fSample,izone);
        int ier2 = TMath::BinarySearch(1+(Long_t)n_enu_reco_bins, enu_reco_bin_edges, enu_reco);
        int iy2  = TMath::BinarySearch(1+(Long_t)n_y_reco_bins,   y_reco_bin_edges,   y_reco  );
        double ndata_curr = fDataOb[izone]->GetEntry(ier2,iy2);
        fDataOb[izone]->SetEntry(ndata_curr+ndata,ier2,iy2);
     }//iy
  }//ier

  return true;
}
//________________________________________________________________________________________
int SingleSampleFitDataA::NumOfBins(void)
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
double SingleSampleFitDataA::Statistic(
  FitModelABC* model_abc, const FitParamList & fp, Option_t * opt)
{
  bool ok = model_abc->Generate(fp);
  assert(ok);

  return this->Statistic(model_abc,opt);
}
//________________________________________________________________________________________
double SingleSampleFitDataA::Statistic(
  FitModelABC * model_abc, const PhysHypothesis & ph, Option_t * opt)
{
  bool ok = model_abc->Generate(ph);
  assert(ok);

  return this->Statistic(model_abc,opt);  
}
//________________________________________________________________________________________
double SingleSampleFitDataA::Statistic(
  FitModelABC * model_abc, Option_t * /*opt*/) 
{
  TObjArray * array = new TObjArray();
  model_abc->Write(array, "curr", "pdft_vf");

  // Calculate statistic
  double S = 0;

  for(int izone = 0; izone < kNMaxBinZones; izone++) {
     if(fDataObNull[izone]) continue;
     const char * name = Form("curr_pdft_ob_vf_%s_%s_z%d", 
         util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(),izone);
     VALORArray * pdf = (VALORArray*) array->FindObject(name);
     assert(pdf);           
     const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
     const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
     for(int ier = 0; ier < n_enu_reco_bins; ier++) {
            for(int iy = 0; iy < n_y_reco_bins; iy++) {
                double nmc   = pdf->GetEntry(ier,iy);
                double ndata = fDataOb[izone]->GetEntry(ier,iy); 
                double dS = util::ChisqPoisson(ndata, nmc);
                S += dS;
            }//iy
     }//ier
  }//izone
  S = TMath::Max(0.,S);

  double Sp   = model_abc->GetFitStatisticPenalty();
  double Stot = S+Sp;

  LOG("SingleSampleFitDataA",pINFO) 
    << "Current fit statistic = " << Stot
    << " (stat term = " << S << ", syst term = " << Sp << ")";

  return Stot;
}
//________________________________________________________________________________________
void SingleSampleFitDataA::Init(void)
{
  LOG("SingleSampleFitDataA",pDEBUG) << "Initializing...";

  fName = "none";

  fDetector = kdUndefined;
  fBeam     = kbUndefined;
  fSample   = ksUndefined;

  for(int izone = 0; izone < kNMaxBinZones; izone++) {
      fDataObNull [izone] = true;
      fDataOb     [izone] = 0;
  }//izone
  fDataSbNull = true;
  fDataSb     = 0;
}
//________________________________________________________________________________________
void SingleSampleFitDataA::Book(void)
{
  LOG("SingleSampleFitDataA",pDEBUG) << "Booking...";

  const int n_y_reco_bins_sb = util::NumYrecoBinsSb(fSample);
  for(int izone = 0; izone < kNMaxBinZones; izone++) {
     const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
     const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
     if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
     fDataObNull [izone] = false;
     fDataOb     [izone] = new VALORArray(n_enu_reco_bins, n_y_reco_bins);
  }//izone
  fDataSbNull = false;
  fDataSb     = new VALORArray(kNErecoBinsSb, n_y_reco_bins_sb);
}
//________________________________________________________________________________________
void SingleSampleFitDataA::Clean(void)
{
  LOG("SingleSampleFitDataA",pDEBUG) << "Cleaning-up...";

  for(int izone = 0; izone < kNMaxBinZones; izone++) {
    if(!fDataObNull[izone]) {
        fDataObNull[izone] = true;
        if (fDataOb[izone]) delete fDataOb[izone];
        fDataOb[izone] = 0;
    }
  }//izone
  if(!fDataSbNull) {
      fDataSbNull = true;
      if(fDataSb) delete fDataSb;
      fDataSb = 0;
  }
}
//________________________________________________________________________________________
void SingleSampleFitDataA::Zero(Option_t * opt)
{
  LOG("SingleSampleFitDataA",pDEBUG) << "Zeroing-out (option: " << opt << ") ...";

  string option = (opt) ? opt : "all";

  for(int izone = 0; izone < kNMaxBinZones; izone++) {
     if(!fDataObNull[izone]) {
         fDataOb[izone]->SetAll(0.);
     }
  }//izone
  if(!fDataSbNull) {
      fDataSb->SetAll(0.);
  }
}
//________________________________________________________________________________________

