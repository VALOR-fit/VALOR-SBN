//________________________________________________________________________________________
/*

   Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

//#define _apply_mc_stat_fluctuation_

#include <cassert>
#include <ostream>

#include <TXMLEngine.h>
#include <TFile.h>
#include <TObjArray.h>
#include <TMath.h>
#include <TSystem.h>
#include <TH1D.h>
#include <TH2D.h>

//fmwk
#include "valor/Conventions/Constants.h"
#include "valor/Conventions/PhysHypothesisId.h"
#include "valor/Conventions/PhysParamId.h"
#include "valor/Conventions/NuFlavour.h"
#include "valor/Conventions/NuOscMixParam.h"
#include "valor/Conventions/NuOscDmsqScheme.h"
#include "valor/Conventions/Opt.h"
#include "valor/Conventions/PDG.h"
#include "valor/Utilities/Interpolator.h"
#include "valor/Utilities/Rnd.h"
#include "valor/Utilities/Env.h"
#include "valor/Utilities/UtlNumStat.h"
#include "valor/Utilities/UtlStyle.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Utilities/UtlXML.h"
#include "valor/Messenger/Messenger.h"
//dune
#include "dune/Conventions/DuneBuild.h"
#include "dune/Conventions/ReacMode.h"
#include "dune/Conventions/Baseline.h"
#include "dune/Conventions/BeamConf.h"
#include "dune/Conventions/FitParamApply.h"
#include "dune/Conventions/Names.h"
#include "dune/Elements/GenericSingleSampleFitModel.h"

using std::endl;

using namespace valor;
using namespace valor::conv;

//~ #define SPLINE_WEIGHTS_ARE_ONE

//________________________________________________________________________________________
GenericSingleSampleFitModel::GenericSingleSampleFitModel() :
  SingleSampleFitModelABC(),
  fParamIsAppliedTo(),
  fParamHasSplines()
{
  this->Init();
}
//________________________________________________________________________________________
GenericSingleSampleFitModel::~GenericSingleSampleFitModel() 
{
  this->Clean();
}
//________________________________________________________________________________________
//
//
// FitModelABC interface implementation:
//
//________________________________________________________________________________________
string GenericSingleSampleFitModel::Name(void) const
{
  return fName;
}
//________________________________________________________________________________________
bool GenericSingleSampleFitModel::Read(string file, Option_t * opt)
{
  assert(fDetector != kdUndefined);
  assert(fBeam     != kbUndefined);
  assert(fSample   != ksUndefined);
  
  int isample = fArrIdx->SampleIdx(fBeam,fSample);
  if (isample == -1) {
    LOG("GenericSingleSampleFitModel",pFATAL)
      << "Sample not included in analysis build: "<<util::AsString(fBeam)<<" "<<util::AsString(fSample);
    util::Die(-1);
  }

  fName = util::nm::MdlName(fDetector, fBeam, fSample, fKSp);

  this->Book();
  this->Zero();

  TString ts_opt(opt);
  bool force_use_dst    = ts_opt.Contains("forcedst");
  bool skip_spline_read = ts_opt.Contains("nosplines");
  bool skip_mc_read     = ts_opt.Contains("nomc");
#ifdef SPLINE_WEIGHTS_ARE_ONE
  skip_spline_read = true;
#endif
  
  LOG("GenericSingleSampleFitModel", pNOTICE) 
    << "Reading configuration from XML file [" << file << "]";

  TString ts_file = file.c_str();
  gSystem->ExpandPathName(ts_file);

  // Check for config file.
  // See if it works as a normal path
  FileStat_t dummy;
  if (gSystem->GetPathInfo(ts_file.Data(), dummy)) 
  {
    // If not, try the config folder
    ts_file = TString::Format("%s/%s",Env::Instance()->TopLevelConfDir().c_str(),ts_file.Data());
    if (gSystem->GetPathInfo(ts_file.Data(), dummy)) {
      LOG("GenericSingleSampleFitModel",pERROR) << "Config file not found: "<<file;
      util::Die(1); return false;
    }
  }

  // Parse the input XML configuration file
  TXMLEngine* xml = new TXMLEngine;   
  XMLDocPointer_t xmldoc = xml->ParseFile(ts_file.Data());
  if (xmldoc==0) {
    LOG("GenericSingleSampleFitModel",pERROR) << "Can not parse input XML file [" << ts_file << "]";
    delete xml;
    util::Die(1); return false;
  }
  XMLNodePointer_t root_node = xml->DocGetRootElement(xmldoc);

  //------------------------
  // TODO
  // fSyst = new What? CompoundCorrelatedSystematics; 
  // fSyst->Read(xml,root_node);
  //------------------------

  // Get the detector fiducial mass
  string name = "fiducial_mass";
  fFiducialMass = util::XML2Dbl(xml,root_node,name);
  LOG("GenericSingleSampleFitModel",pINFO)
    << "Fiducial mass = " << fFiducialMass*1000 << " tonnes";

  // Get assumed exposure for each beam configuration
  {
    // Optionally over-ride the POT
    if (Opt::Instance()->GlobalRegistry().Exists("pot_override")) {
      fPOT = Opt::Instance()->GlobalRegistry().GetDouble("pot_override");
    }
    else {
      string node_name = "data/exposure/" + util::AsString(fBeam, "lowercase");
      fPOT = util::XML2Dbl(xml,root_node,node_name);
    }
    LOG("GenericSingleSampleFitModel",pNOTICE) 
      << "Beam config: " << util::AsString(fBeam) 
      << " -> Exposure = " << fPOT << " POT.";
  }

  //
  // Using input in VALOR DST format?
  // If true, read the ROOT files and fill-in the MC templates.
  // If false, just read in the MC templates directly. 
  // In the later case, the templates are pre-binned so the binning
  // can not change. Make sure the templates have the expected binning.
  //
  fUseMCDST = util::XML2Bool(xml,root_node,"mc/using_dst_format") || force_use_dst;
  if (skip_mc_read) {
    LOG("GenericSingleSampleFitModel",pWARN) << "Skipping MC read.";
  }
  else if(fUseMCDST) {
    LOG("GenericSingleSampleFitModel",pINFO) << "Filling in VALOR MC templates using VALOR DSTs";
    string node_name = "mc/dst/" + util::AsString(fBeam, "lowercase");
    fMCDST = util::XML2TTree (xml,root_node,node_name);
    assert(fMCDST);
    this->FillFromDST(fMCDST);
  } 
  else {
    LOG("GenericSingleSampleFitModel",pINFO) << "Using stored VALOR MC templates";
    string template_tag = util::XML2String(xml,root_node,"mc/template/tag");
    TFile * template_file = util::XML2TFile(xml,root_node,"mc/template");

    this->FillFromTemplateFile(template_file,template_tag);
    template_file->Close();
    delete template_file;
  }
  
  double n_events = 0.;
  for(int imode = 0; imode < kNReacModes; imode++) {
    ReacMode_t m = kReactionModes[isample][imode];
    if(m == kmUndefined) continue;
    n_events+=fMCTNomSb[imode]->Integral();
  }
  LOG("GenericSingleSampleFitModel",pNOTICE) << "Untuned template contains "<<n_events<<" events.";

  // At the point the nominal MC templates are filled-in.
  // Apply any fixed tuning here, not on an event by event basis.
  // It is the tuned templates that be the starting point in the Generate() method.
  this->ApplyTuning();

  // Release memory
  xml->FreeDoc(xmldoc);
  delete xml;
  
  LOG("GenericSingleSampleFitModel",pINFO) << "Configuring the Response Function Library... \n\n";
  // And now get the RFL
  fRFL = new util::DuneRFL(fBeam, fSample, fDetector, conv::kNFitParamsWithSplines,conv::kFitParamsWithSplines);
  if (!skip_spline_read) {
    fRFL->Read(file, opt);
    
    bool null_warning = false;
  
  
    // Fill the spline array
    const int n_true1_bins = util::NumEtrueBins(fSample);
    const double * true1_bin_edges = util::EtrueBinEdges(fSample);

    for(int imode = 0; imode < kNReacModes; imode++) {
      ReacMode_t m = kReactionModes[isample][imode];
      if(m == kmUndefined) continue;
      const int n_true2_bins = util::NumQ2trueBins(fSample,m);
      const double * true2_bin_edges = util::Q2trueBinEdges(fSample,m);
      
      // Optimised binning
      for(int izone = 0; izone < kNMaxBinZones; izone++) {
        util::KinematicPoint kp;
        const int n_reco1_bins = util::NumErecoBins(fSample,izone);
        const int n_reco2_bins = util::NumYrecoBins(fSample,izone);
        const double * reco1_bin_edges = util::ErecoBinEdges(fSample,izone);
        const double * reco2_bin_edges = util::YrecoBinEdges(fSample,izone);
        for(int it1 = 0; it1 < n_true1_bins; it1++) {
          double true1 = (true1_bin_edges[it1]+true1_bin_edges[it1+1])/2.;
          kp.true1 = true1;
          for(int it2 = 0; it2 < n_true2_bins; it2++) {
            double true2 = (true2_bin_edges[it2]+true2_bin_edges[it2+1])/2.;
            kp.true2 = true2;
            for(int ir1 = 0; ir1 < n_reco1_bins; ir1++) {
              double reco1 = (reco1_bin_edges[ir1]+reco1_bin_edges[ir1+1])/2.;
              kp.reco1 = reco1;
              for(int ir2 = 0; ir2 < n_reco2_bins; ir2++) {
                double reco2 = (reco2_bin_edges[ir2]+reco2_bin_edges[ir2+1])/2.;
                kp.reco2 = reco2;
                util::KinematicBin kb = fRFL->GetBin(kp,m);
                for (int ip = 0 ; ip < kNFitParams; ip++) {
                  PhysParamId_t p = kFitParam[ip];
                  Long64_t spl_as_int = reinterpret_cast<Long64_t>(util::DuneRFL::kNoSplineRequired);
                  if (util::ParamHasSplines(p)) {
                    const util::Interpolator * spl = fRFL->GetSpline(m,p,kb);
                    if (spl == NULL) {
                      LOG("GenericSingleSampleFitModel",pINFO) << "Got null spline.\n";
                      null_warning = true;
                    }
                    spl_as_int = reinterpret_cast<Long64_t>(spl);
                    
                  }
                  fRFPtr[imode][izone]->SetEntry(spl_as_int,ir1,ir2,it1,it2,ip);
                }//ip
              }//ir2
            }//ir1
          }//it2
        }//it1
      }//izone
    }//imode
    if (null_warning) {
      LOG("GenericSingleSampleFitModel",pFATAL) << "Null splines found - giving up.";
      util::Die(-1);return false;
    }
    LOG("GenericSingleSampleFitModel",pINFO) << "Spline array filled... \n\n";
  }
    

  LOG("GenericSingleSampleFitModel",pNOTICE) << "Done configuring DUNE/ND model... \n\n";

  return true;
}
//________________________________________________________________________________________
bool GenericSingleSampleFitModel::Generate(const PhysHypothesis & ph, Option_t * opt)
{
  // input opt: 
  // - Leave null for the fit
  // - Use "+SB" to generate finely-binned predictions too (for plotting or toy-MC generation)

  //  LOG("GenericSingleSampleFitModel",pDEBUG)  
  //     << "Input physics hypothesis before copying to private data member: " << ph;

  fPhysHypothesis.Copy(ph);
  //PhysHypothesis_t hyp = fPhysHypothesis.Hypothesis();

  LOG("GenericSingleSampleFitModel",pINFO)  
    << "Generating model predictions for the input hypothesis: " 
    << fPhysHypothesis;

  this->FluctuateMCStat(opt);   // `tun' MC templates --> `tun' MC templates (NOTE: if important effect, will need to add a new type of templates
  //this->ApplySystematics(opt);  // `tun' MC templates --> `sys' MC templates
  this->ApplyPhysics(opt);      // `sys' MC templates --> `fin' MC templates
  this->ApplyOscProb(opt);      // `fin' MC templates --> `fin' MC templates
  this->UpdatePDFs(opt);        // `fin' MC templates --> p.d.f

  LOG("GenericSingleSampleFitModel",pINFO) << "Done generating predictions";

  return true;
}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::RandomizeSystematics(Option_t * options)
{
  TString opt(options);
  if (!opt.Length()) {opt="randomize-all";}

  bool randomize_flux=false, randomize_int=false, randomize_det=false;
  if (opt.Contains("randomize-all")) {
    randomize_flux = true;
    randomize_int  = true;
    randomize_det  = true;
  }
  if (opt.Contains("randomize-flux")) {randomize_flux = true;}
  if (opt.Contains("randomize-int" )) {randomize_int  = true;}
  if (opt.Contains("randomize-det" )) {randomize_det  = true;}

  // -------------------------------------------- 
  // TODO
  // How do we do that if we have a single matrix
  //       
  //if (randomize_flux) {fNuFlux->Tweak(false,0);}
  //if (randomize_int ) {fNuInt ->Tweak(false,0);}
  //if (randomize_det ) {fNuDet ->Tweak(false,0);}
  // -------------------------------------------- 

}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::TweakSystematic(
    string syst_name, double twkdial, Option_t * opt)
{
  PhysParamId_t p = util::PhysParamFromString(syst_name);
  this->TweakSystematic(p,twkdial,opt);
  return;
}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::TweakSystematic(
    PhysParamId_t syst, double twkdial, Option_t * /*opt*/)
{
  if (fSyst) {
    fSyst->SetCurrentValue(syst,twkdial);
  }
  else {
    LOG("GenericSingleSampleFitModel",pWARN) << "No systematic model - not tweaking requested parameter: "<<util::AsString(syst);
  }
}
//________________________________________________________________________________________
PhysParamList GenericSingleSampleFitModel::Tweaks(Option_t * /*opt*/) const
{
  PhysParamList list;

  // -----------------------------------  
  // TODO
  // Remove
  //fNuFlux -> CopyTweaksTo(list);
  //fNuInt  -> CopyTweaksTo(list);
  //fNuDet  -> CopyTweaksTo(list);
  // -----------------------------------  

  fSyst -> CopyTweaksTo(list);

  return list;
}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::ResetSystematics(Option_t * /*opt*/)
{
  // -----------------------------------  
  // TODO
  // Remove
  //fNuFlux -> Tweak(true, 0);
  //fNuInt  -> Tweak(true, 0);
  //fNuDet  -> Tweak(true, 0);
  // -----------------------------------  
  fSyst -> Tweak(true, 0);
}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::PrintSystematics(ostream & stream, Option_t * /*opt*/) const
{
  stream << endl;
}
//________________________________________________________________________________________
bool GenericSingleSampleFitModel::Generate (const FitParamList & fp, Option_t * opt)
{
  //  LOG("GenericSingleSampleFitModel",pDEBUG)  
  //     << "Input fit parameter list before converting to a physics hypothesis: " << fp;

  if (fSyst) {
    fSyst ->UpdateFrom(fp);
  }

  // extract the values of params driving the oscillation, decoherence or decay model
  PhysHypothesis ph(fp);

  // call the main Generate() method
  return this->Generate(ph, opt);
}
//________________________________________________________________________________________
bool GenericSingleSampleFitModel::Write(TObjArray * array, const char * tag, Option_t * write_opt)
{
  //
  // write_opt:
  // - if null, store only what is needed for the fit (equiv. with write_opt = "pdft_vf")
  // - if "all", store everything listed below
  // - include the string "mct_vf" to write-out the MC templates
  //   (functions of beam,sample,mode,zone,Ereco,yreco,Etrue - in VALORArray format)
  // - include the string "pdfc_vf" to write-out the PDF components 
  //   (functions of beam,sample,mode,zone,Ereco,yreco - in VALORArray format)
  // - include the string "pdfc_rf" to write out the above in bare ROOT format (TH1D, TH2D,....)
  // - include the string "pdft_vf" to write-out the total PDF 
  //   (functions of beam,sample,zone,Ereco,yreco - in VALORArray format)
  // - include the string "pdft_rf" to write-out the above in bare ROOT format
  // - include the string "pdfcs_rf" to write-out 1-D slices of the PDF components in bare ROOT format
  // - include the string "pdfts_rf" to write-out 1-D slices of the total PDF in bare ROOT format
  // - include the string "+SB" to write-out versions of the above in simpler binning
  //
  // Key:
  //  mct   -> MC template                    CC: f(Ereco,yreco,Etrue;s,m)
  //  pdft  -> PDF total                      CC: f(Ereco,yreco;s)
  //  pdfc  -> PDF component                  CC: f(Ereco,yreco;s,m)
  //  pdfts -> 1-D slice of PDF total         CC: f(Ereco;s)|yreco
  //  pdfcs -> 1-D slice of PDF component     CC: f(Ereco;s,m)|yreco
  //  rf    -> ROOT format
  //  vf    -> VALOR format
  //  ob    -> Optimized binning (for fit)
  //  sb    -> Simple binning (for plots)

  LOG("GenericSingleSampleFitModel", pINFO)  << "Writing results to input object array...";
  LOG("GenericSingleSampleFitModel", pDEBUG) << "tag = " << tag << ", write option = " << write_opt;

  string opt = (write_opt) ? write_opt : "pdft_vf";
  if(opt.find("all") != string::npos) {
    opt = "mct_vf + pdfc_vf + pdfc_rf + pdft_vf + pdft_rf + pdfcs_rf + pdfts_rf +SB";
    LOG("GenericSingleSampleFitModel", pDEBUG) << "Write option replaced with = " << opt;
  }

  if(!array) {
    LOG("GenericSingleSampleFitModel",pERROR) << "Null input object array.";
    return false;
  }

  valor::util::SetDefaultStyle();

  int isample = fArrIdx->SampleIdx(fBeam,fSample);

  //
  // Write out MC templates (VALORArray format)
  //

  if(opt.find("mct_vf") != string::npos) {

    for(int imode = 0; imode < kNReacModes; imode++) {
      ReacMode_t m = kReactionModes[isample][imode];
      if(m == kmUndefined) continue;

      for(int izone = 0; izone < kNMaxBinZones; izone++) {
        if(fMCTNullOb[imode][izone]) continue;
         TString name = TString::Format("%s_%s_%s_z%d", 
            util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), util::AsString(m).c_str(), izone);
        fMCTNomOb [imode][izone] -> SetName( TString::Format("%s_%s_%s", tag, "mctnom_ob_vf", name.Data()).Data() );
        fMCTTunOb [imode][izone] -> SetName( TString::Format("%s_%s_%s", tag, "mcttun_ob_vf", name.Data()).Data() );
        fMCTSysOb [imode][izone] -> SetName( TString::Format("%s_%s_%s", tag, "mctsys_ob_vf", name.Data()).Data() );
        fMCTFinOb [imode][izone] -> SetName( TString::Format("%s_%s_%s", tag, "mctfin_ob_vf", name.Data()).Data() );
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << fMCTNomOb [imode][izone]->GetName();
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << fMCTTunOb [imode][izone]->GetName();
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << fMCTSysOb [imode][izone]->GetName();
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << fMCTFinOb [imode][izone]->GetName();
        array -> Add ( fMCTNomOb [imode][izone] ); 
        array -> Add ( fMCTTunOb [imode][izone] ); 
        array -> Add ( fMCTSysOb [imode][izone] ); 
        array -> Add ( fMCTFinOb [imode][izone] );
      }//izone

      if(opt.find("+SB") != string::npos) {
        if(fMCTNullSb[imode]) continue;
        TString name = TString::Format("%s_%s_%s", 
            util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), util::AsString(m).c_str());
        fMCTNomSb [imode] -> SetName( TString::Format("%s_%s_%s", tag, "mctnom_sb_vf", name.Data()).Data() );
        fMCTTunSb [imode] -> SetName( TString::Format("%s_%s_%s", tag, "mcttun_sb_vf", name.Data()).Data() );
        fMCTSysSb [imode] -> SetName( TString::Format("%s_%s_%s", tag, "mctsys_sb_vf", name.Data()).Data() );
        fMCTFinSb [imode] -> SetName( TString::Format("%s_%s_%s", tag, "mctfin_sb_vf", name.Data()).Data() );
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << fMCTNomSb [imode]->GetName();
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << fMCTTunSb [imode]->GetName();
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << fMCTSysSb [imode]->GetName();
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << fMCTFinSb [imode]->GetName();
        array -> Add ( fMCTNomSb [imode] ); 
        array -> Add ( fMCTTunSb [imode] ); 
        array -> Add ( fMCTSysSb [imode] ); 
        array -> Add ( fMCTFinSb [imode] );
      }//+SB?
    }//imode
  }//mct_vf


  //
  // Write out the PDF components (VALORArray or bare ROOT format)
  //

  if(opt.find("pdfc_vf") != string::npos || opt.find("pdfc_rf") != string::npos) {

    for(int imode = 0; imode < kNReacModes; imode++) {
      ReacMode_t m = kReactionModes[isample][imode];
      if(m == kmUndefined) continue;

      for(int izone = 0; izone < kNMaxBinZones; izone++) {
        if(fMCTNullOb[imode][izone]) continue;
        TString name = TString::Format("%s_%s_%s_z%d", 
            util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), util::AsString(m).c_str(), izone);
        // in VALORArray format
        if (opt.find("pdfc_vf") != string::npos) {
          fPDFCompOb [imode][izone]->SetName(TString::Format("%s_%s_%s",tag,"pdfc_ob_vf",name.Data()).Data());
          LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << fPDFCompOb[imode][izone]->GetName();
          array->Add(fPDFCompOb[imode][izone]);
        }
        // in TH2D format
        // -----
        // NOTE: The following could be simplified substantially (conversion from VALOR 2-D
        // array to ROOT TH2D could happen elsewhere generically)
        // -----
        if (opt.find("pdfc_rf") != string::npos) {
          // get binning
          const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
          const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
          if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
          const double * enu_reco_bins = util::ErecoBinEdges(fSample,izone);
          const double * y_reco_bins   = util::YrecoBinEdges(fSample,izone);
          // book histogram
          TString hname = TString::Format("%s_%s_%s",tag, "pdfc_ob_rf",name.Data());
          TString htitle = "VALOR/DUNE ND (Ereco,yreco) PDF component = f(beam,sample,mode,zone)";
          TH2D * h2 = new TH2D(hname.Data(),htitle.Data(),
              n_enu_reco_bins, enu_reco_bins, n_y_reco_bins, y_reco_bins);
          // fill from corresponding VALOR array
          for(int ier = 0; ier < n_enu_reco_bins; ier++) {
            for(int iy = 0; iy < n_y_reco_bins; iy++) {
              double val = fPDFCompOb[imode][izone]->GetEntry(ier,iy);
              h2->SetBinContent(ier+1,iy+1,val);
            }//iy
          }//ier
          // add tp object array and clean-up
          LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << h2->GetName();
          array->Add(h2); 
          // delete h2; ???? // MEMORY LEAK?
        }
      }//izone

      if(opt.find("+SB") != string::npos) {
        if(fMCTNullSb[imode]) continue;
        TString name = TString::Format("%s_%s_%s", 
            util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), util::AsString(m).c_str());
        // in VALORArray format
        if (opt.find("pdfc_vf") != string::npos) {
          fPDFCompSb[imode]->SetName(TString::Format("%s_%s_%s",tag,"pdfc_sb_vf",name.Data()));
          LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << fPDFCompSb[imode]->GetName();
          array->Add(fPDFCompSb[imode]);
        }
        // in TH2D format
        // -----
        // NOTE: The following could be simplified substantially (conversion from VALOR 2-D
        // array to ROOT TH2D could happen elsewhere generically)
        // -----
        if (opt.find("pdfc_rf") != string::npos) {
          // book histogram
          const int n_y_reco_bins_sb = util::NumYrecoBinsSb(fSample);
          const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(fSample);
          TString hname = TString::Format("%s_%s_%s",tag, "pdfc_sb_rf",name.Data());
          TString htitle = "VALOR/DUNE ND (Ereco,yreco) PDF component = f(beam,sample,mode)";
          TH2D * h2 = new TH2D(hname.Data(),htitle.Data(),
              kNErecoBinsSb, kErecoBinEdgesSb, n_y_reco_bins_sb, y_reco_bin_edges_sb);
          // fill from corresponding VALOR array
          for(int ier = 0; ier < kNErecoBinsSb; ier++) {
            for(int iy = 0; iy <  n_y_reco_bins_sb; iy++) {
              double val = fPDFCompSb[imode]->GetEntry(ier,iy);
              h2->SetBinContent(ier+1,iy+1,val);
            }//iy
          }//ier
          // add tp object array and clean-up
          LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << h2->GetName();
          array->Add(h2); 
          // delete h2; ???? // MEMORY LEAK?
        }
      }//+SB?          

    }//imode
  }//pdfc_vf,pdfc_rf


  //
  // Write out the total PDF (VALORArray or bare ROOT format)
  //

  if(opt.find("pdft_vf") != string::npos || opt.find("pdft_rf") != string::npos) {

    for(int izone = 0; izone < kNMaxBinZones; izone++) {
      TString name = TString::Format("%s_%s_z%d", 
          util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), izone);
      // in VALORArray format
      if (opt.find("pdft_vf") != string::npos) {
        fPDFTotOb[izone]->SetName(TString::Format("%s_%s_%s",tag,"pdft_ob_vf",name.Data()));
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << fPDFTotOb[izone]->GetName();
        array->Add(fPDFTotOb[izone]);
      }
      // in TH2D format
      // -----
      // NOTE: The following could be simplified substantially (conversion from VALOR 2-D
      // array to ROOT TH2D could happen elsewhere generically)
      // -----
      if (opt.find("pdft_rf") != string::npos) {
        // get binning
        const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
        const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
        if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
        const double * enu_reco_bins = util::ErecoBinEdges(fSample,izone);
        const double * y_reco_bins   = util::YrecoBinEdges(fSample,izone);
        // book histogram
        TString hname = TString::Format("%s_%s_%s",tag, "pdft_ob_rf",name.Data()); 
        TString htitle = "VALOR/DUNE ND (Ereco,yreco) PDF = f(beam,sample,zone)";
        TH2D * h2 = new TH2D(hname.Data(), htitle.Data(),
            n_enu_reco_bins, enu_reco_bins, n_y_reco_bins, y_reco_bins);
        // fill from corresponding VALOR array
        for(int ier = 0; ier < n_enu_reco_bins; ier++) {
          for(int iy = 0; iy < n_y_reco_bins; iy++) {
            double val = fPDFTotOb[izone]->GetEntry(ier,iy);
            h2->SetBinContent(ier+1,iy+1,val);
          }//iy
        }//ier
        // add to object array and clean-up
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << h2->GetName();
        array->Add(h2); 
        // delete h2; ???? // MEMORY LEAK?
      }
    }//izone

    if(opt.find("+SB") != string::npos) {
      TString name = TString::Format("%s_%s", 
          util::AsString(fBeam).c_str(), util::AsString(fSample).c_str());
      // in VALORArray format
      if (opt.find("pdft_vf") != string::npos) {
        fPDFTotSb->SetName(TString::Format("%s_%s_%s",tag,"pdft_sb_vf",name.Data()));
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << fPDFTotSb->GetName();
        array->Add(fPDFTotSb);
      }
      // in TH2D format
      // -----
      // NOTE: The following could be simplified substantially (conversion from VALOR 2-D
      // array to ROOT TH2D could happen elsewhere generically)
      // -----
      if (opt.find("pdft_rf") != string::npos) {
        // book histogram
        const int n_y_reco_bins_sb = util::NumYrecoBinsSb(fSample);
        const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(fSample);
        TString hname = TString::Format("%s_%s_%s",tag, "pdft_sb_rf",name.Data());
        TString htitle = "VALOR/DUNE ND (Ereco,yreco) PDF = f(beam,sample)";
        TH2D * h2 = new TH2D(hname,htitle,
            kNErecoBinsSb, kErecoBinEdgesSb, n_y_reco_bins_sb, y_reco_bin_edges_sb);
        h2->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
        h2->GetYaxis()->SetTitle("y");
        h2->SetTitle(TString::Format("Number of events /bin /%lg POT", fPOT).Data());
        // fill from corresponding VALOR array
        for(int ier = 0; ier < kNErecoBinsSb; ier++) {
          for(int iy = 0; iy < n_y_reco_bins_sb; iy++) {
            double val = fPDFTotSb->GetEntry(ier,iy);
            h2->SetBinContent(ier+1,iy+1,val);
          }//iy
        }//ier
        // add to object array and clean-up
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << h2->GetName();
        array->Add(h2); 
        // delete h2; ???? // MEMORY LEAK?
      }
    }//+SB?

  }//pdft_vf,pdft_rf


  //
  // Write out the slices of the PDF components (bare ROOT format)
  //
  // -----
  // NOTE: The following could be simplified substantially (conversion from VALOR 2-D
  // array to ROOT TH1D slices could happen elsewhere generically)
  // -----

  if(opt.find("pdfcs_rf") != string::npos) {

    for(int imode = 0; imode < kNReacModes; imode++) {
      ReacMode_t m = kReactionModes[isample][imode];
      if(m == kmUndefined) continue;

      for(int izone = 0; izone < kNMaxBinZones; izone++) {
        TString name = TString::Format("%s_%s_%s_z%d", 
            util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), util::AsString(m).c_str(), izone);
        // get binning
        const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
        const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
        if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
        const double * enu_reco_bins = util::ErecoBinEdges(fSample,izone);
        const double * y_reco_bins   = util::YrecoBinEdges(fSample,izone);
        // create slices of the PDF components (function of Ereco, for given yreco bin)
        TString hname = TString::Format("%s_%s_%s",tag, "pdfcs_ob_rf",name.Data()) ;
        TString htitle = "VALOR/DUNE ND PDF component: Ereco spectrum = f(beam,sample,mode,zone)";
        TH1D * htot = new TH1D(hname.Data(),htitle.Data(),n_enu_reco_bins, enu_reco_bins);
        htot->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
        htot->GetYaxis()->SetTitle(TString::Format("Number of events /bin /%lg POT", fPOT).Data());
        for(int iy = 0; iy < n_y_reco_bins; iy++) {
          TString hname_s  = TString::Format("%s_%s_%s_y%d",tag, "pdfcs_ob_rf",name.Data(),iy);
          TString htitle_s = TString::Format(
            "VALOR/DUNE ND PDF component slice: Ereco spectrum = f(beam,sample,mode,zone) for y in [%f,%f]", 
            y_reco_bins[iy],y_reco_bins[iy+1]);
          TH1D * h = new TH1D(hname_s.Data(),htitle_s.Data(),
              n_enu_reco_bins, enu_reco_bins);
          h->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
          h->GetYaxis()->SetTitle(TString::Format("Number of events /bin /%lg POT", fPOT).Data());
          for(int ier = 0; ier < n_enu_reco_bins; ier++) {
            double val = fPDFCompOb[imode][izone]->GetEntry(ier,iy);
            h->SetBinContent(ier+1, val);
            htot->SetBinContent(ier+1, htot->GetBinContent(ier+1) + val);
          }//ier
          // add to obj array and clean-up 
          LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << h->GetName();
          array->Add(h);
          //delete h; ??? MEM LEAK??
        }//iy         
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << htot->GetName();
        array->Add(htot);
        //delete htot; ??? MEM LEAK??
      }//izone

      if(opt.find("+SB") != string::npos) {
        TString name = TString::Format("%s_%s_%s", 
            util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), util::AsString(m).c_str());
        // create slices of the PDF components (function of Ereco, for given yreco bin)
        const int n_y_reco_bins_sb = util::NumYrecoBinsSb(fSample);
        const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(fSample);
        TString hname = TString::Format( "%s_%s_%s",tag, "pdfcs_sb_rf",name.Data());
        TString htitle = "VALOR/DUNE ND PDF component: Ereco spectrum = f(beam,sample,mode)";
        TH1D * htot = new TH1D(hname.Data(), htitle.Data(), kNErecoBinsSb, kErecoBinEdgesSb);
        htot->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
        htot->GetYaxis()->SetTitle(TString::Format("Number of events /bin /%lg POT", fPOT).Data());
        for(int iy = 0; iy < n_y_reco_bins_sb; iy++) {
          TString hname_s = TString::Format("%s_%s_%s_y%d",tag, "pdfcs_sb_rf",name.Data(),iy);
          TString htitle_s = TString::Format(
            "VALOR/DUNE ND PDF component slice: Ereco spectrum = f(beam,sample,mode) for y in [%f,%f]", 
            y_reco_bin_edges_sb[iy], y_reco_bin_edges_sb[iy+1]);
          TH1D * h = new TH1D(hname_s.Data(), htitle_s.Data(),kNErecoBinsSb, kErecoBinEdgesSb);
          h->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
          h->GetYaxis()->SetTitle(TString::Format("Number of events /bin /%lg POT", fPOT).Data());
          for(int ier = 0; ier < kNErecoBinsSb; ier++) {
            double val = fPDFCompSb[imode]->GetEntry(ier,iy);
            h->SetBinContent(ier+1, val);
            htot->SetBinContent(ier+1, htot->GetBinContent(ier+1) + val);
          }//ier
          // add to obj array and clean-up 
          LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << h->GetName();
          array->Add(h);
          //delete h; ??? MEM LEAK??
        }//iy         
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << htot->GetName();
        array->Add(htot);
        //delete htot; ??? MEM LEAK??
      }//+SB?

    }//imode
  }//pdfcs_rf


  //
  // Write out the slices of the total PDF (bare ROOT format)
  //
  // -----
  // NOTE: The following could be simplified substantially (conversion from VALOR 2-D
  // array to ROOT TH1D slices could happen elsewhere generically)
  // -----

  if(opt.find("pdfts_rf") != string::npos) {

    for(int izone = 0; izone < kNMaxBinZones; izone++) {
      TString name = TString::Format("%s_%s_z%d", 
          util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), izone);
      // get binning
      const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
      const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
      if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
      const double * enu_reco_bins = util::ErecoBinEdges(fSample,izone);
      const double * y_reco_bins   = util::YrecoBinEdges(fSample,izone);
      // create slices of the total PDF (function of Ereco, for given yreco bin)
      TString hname  = TString::Format("%s_%s_%s",tag, "pdfts_ob_rf",name.Data());
      TString htitle = TString::Format("VALOR/DUNE ND PDF: Ereco spectrum = f(beam,sample,zone)");
      TH1D * htot = new TH1D(hname.Data(), htitle.Data(),
        n_enu_reco_bins, enu_reco_bins);
      htot->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
      htot->GetYaxis()->SetTitle(TString::Format("Number of events /bin /%lg POT", fPOT));
      for(int iy = 0; iy < n_y_reco_bins; iy++) {
        TString hname_s = TString::Format("%s_%s_%s_y%d",tag, "pdfts_ob_rf",name.Data(),iy);
        TString htitle_s = TString::Format(
          "VALOR/DUNE ND PDF slice: Ereco spectrum = f(beam,sample,zone) for y in [%f,%f]",
          y_reco_bins[iy],y_reco_bins[iy+1]);
        TH1D * h = new TH1D(hname_s.Data(), htitle_s.Data(),
            n_enu_reco_bins, enu_reco_bins);
        h->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
        h->GetYaxis()->SetTitle(TString::Format("Number of events /bin /%lg POT", fPOT).Data());
        for(int ier = 0; ier < n_enu_reco_bins; ier++) {
          double val = fPDFTotOb[izone]->GetEntry(ier,iy);
          h->SetBinContent(ier+1, val);
          htot->SetBinContent(ier+1, htot->GetBinContent(ier+1) + val);
        }//ier
        // add to obj array and clean-up 
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << h->GetName();
        array->Add(h);
        //delete h; ??? MEM LEAK??      
      }//iy         
      LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << htot->GetName();
      array->Add(htot);
      //delete htot; ??? MEM LEAK??      
    }//izone

    if(opt.find("+SB") != string::npos) {
      TString name = TString::Format("%s_%s", 
          util::AsString(fBeam).c_str(), util::AsString(fSample).c_str());
      // create slices of the total PDF (function of Ereco, for given yreco bin)
      const int n_y_reco_bins_sb = util::NumYrecoBinsSb(fSample);
      const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(fSample);
      TH1D * htot = new TH1D("htot", "htot", kNErecoBinsSb, kErecoBinEdgesSb);
      htot->SetName(TString::Format("%s_%s_%s",tag, "pdfts_sb_rf",name.Data()).Data() );
      htot->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
      htot->GetYaxis()->SetTitle(TString::Format("Number of events /bin /%lg POT", fPOT).Data());
      for(int iy = 0; iy < n_y_reco_bins_sb; iy++) {
        TString hname = TString::Format("%s_%s_%s_y%d",tag, "pdfts_sb_rf",name.Data(),iy);
        TString htitle = TString::Format(
          "VALOR/DUNE ND PDF slice: Ereco spectrum = f(beam,sample) for y in [%f,%f]", 
          y_reco_bin_edges_sb[iy], y_reco_bin_edges_sb[iy+1]);
        TH1D * h = new TH1D(hname.Data(),htitle.Data(),
            kNErecoBinsSb, kErecoBinEdgesSb);
        h->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
        h->GetYaxis()->SetTitle(TString::Format("Number of events /bin /%lg POT", fPOT).Data());
        for(int ier = 0; ier < kNErecoBinsSb; ier++) {
          double val = fPDFTotSb->GetEntry(ier,iy);
          h->SetBinContent(ier+1, val);
          htot->SetBinContent(ier+1, htot->GetBinContent(ier+1) + val);
        }//ier
        // add to obj array and clean-up 
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << h->GetName();
        array->Add(h);
        //delete h; ??? MEM LEAK??
      }//iy         
      LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << htot->GetName();
      array->Add(htot);
      //delete htot; ??? MEM LEAK??
    }//+SB?

  }//pdfts_rf

  return true;
}
//________________________________________________________________________________________
bool GenericSingleSampleFitModel::Write(
    const char * filename, const char * tag, Option_t * write_opt, Option_t * file_opt)
{
  LOG("GenericSingleSampleFitModel",pNOTICE) << "Writing results to file: [" << filename << "]";

  TObjArray * array = new TObjArray();
  this->Write(array,tag,write_opt);

  Option_t * used_file_opt = (file_opt == 0) ? "recreate" : file_opt;
  TFile f(filename, used_file_opt);
  array->Write();
  f.Close();
  delete array;

  return true;
}
//________________________________________________________________________________________
double GenericSingleSampleFitModel::GetFitStatisticPenalty (Option_t * /*opt*/) const
{
  /*
  // ------------------
  // TODO
  // Remove
  //
  double Sp_nuflux = (fNuFlux -> ChisqPenalty());
  double Sp_nuint  = (fNuInt  -> ChisqPenalty());
  double Sp_nudet  = (fNuDet  -> ChisqPenalty());

  double Sp = Sp_nuflux + Sp_nuint + Sp_nudet;

  LOG("GenericSingleSampleFitModel",pDEBUG) 
  << "Current penalty term = " << Sp 
  << " (flux = " << Sp_nuflux 
  << ", interaction = " << Sp_nuint 
  << ", detector = " << Sp_nudet << ")";
  // ------------------
  */
  double Sp = (fSyst-> ChisqPenalty());
  return Sp;
}
//________________________________________________________________________________________
//
//
// Private methods:
//
//________________________________________________________________________________________

void GenericSingleSampleFitModel::Init(void)
{
  LOG("GenericSingleSampleFitModel",pDEBUG) << "Initializing...";

  fName         = "none";
  fFiducialMass = 0;
  fPOT          = 0;
  fUseMCDST     = false;
  fMCDST        = 0;
  fRFL          = 0;

  for(int imode = 0; imode < kNReacModes; imode++) {

    // MC templates (simple binning)
    fMCTNullSb[imode] = true;
    fMCTNomSb [imode] = 0;
    fMCTTunSb [imode] = 0;
    fMCTSysSb [imode] = 0;
    fMCTFinSb [imode] = 0;
    fMCStatSb [imode] = 0;
    // PDF (simple binning)
    fPDFCompSb[imode] = 0;
    if(imode == 0) {
      fPDFTotSb     = 0;
      fPDFTotNullSb = true;
    }

    for(int izone = 0; izone < kNMaxBinZones; izone++) {
      // MC templates
      fMCTNullOb [imode][izone] = true;
      fMCTNomOb  [imode][izone] = 0;
      fMCTTunOb  [imode][izone] = 0;
      fMCTSysOb  [imode][izone] = 0;
      fMCTFinOb  [imode][izone] = 0;
      fMCStatOb  [imode][izone] = 0;
      // Splines
      fRFPtr     [imode][izone] = 0;
      // PDF
      fPDFCompOb [imode][izone] = 0;
      if(imode == 0) {
        fPDFTotOb     [izone] = 0;
        fPDFTotNullOb [izone] = true;
      }
    }//izone
    
    // Initialise the param is applied to to false
    for(int ip = 0; ip < conv::kNFitParams; ip++) {
      fParamIsAppliedTo[imode][ip] = false;
    }
  }//imode
  
  // Do our parameters use splines
  for(int ip = 0; ip < conv::kNFitParams; ip++) {
    PhysParamId_t p = kFitParam[ip];
    const_cast<bool&>(fParamHasSplines[ip]) = util::ParamHasSplines(p);
  }
  
  fArrIdx = util::ArrIdx::Instance();

  fSyst = 0;
}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::Book(void)
{
  LOG("GenericSingleSampleFitModel",pDEBUG) << "Booking "<<util::AsString(fBeam)<<" "<<util::AsString(fSample);

  int isample = fArrIdx->SampleIdx(fBeam,fSample);

  for(int imode = 0; imode < kNReacModes; imode++) {
    ReacMode_t m = kReactionModes[isample][imode];
    if(m == kmUndefined) continue;

    const int n_e_reco_bins_sb = util::NumErecoBinsSb(fSample);
    const int n_y_reco_bins_sb = util::NumYrecoBinsSb(fSample);
    const int n_enu_true_bins  = util::NumEtrueBins  (fSample);
    const int n_q2_true_bins   = util::NumQ2trueBins (fSample,m);

    LOG("GenericSingleSampleFitModel",pDEBUG) 
      << "Booking MC template (simple binning) for " 
      << "beam: "     << util::AsString(fBeam) 
      << ", sample: " << util::AsString(fSample)
      << ", mode: "   << util::AsString(m); 

    // >> MC templates (simple binning)
    // (Note order of variables: reco first, true later)
    fMCTNullSb[imode] = false;
    fMCTNomSb [imode] = 
      new VALORArray(n_e_reco_bins_sb, n_y_reco_bins_sb, n_enu_true_bins, n_q2_true_bins);
    fMCTTunSb [imode] = 
      new VALORArray(n_e_reco_bins_sb, n_y_reco_bins_sb, n_enu_true_bins, n_q2_true_bins);
    fMCTSysSb [imode] = 
      new VALORArray(n_e_reco_bins_sb, n_y_reco_bins_sb, n_enu_true_bins, n_q2_true_bins);
    fMCTFinSb [imode] = 
      new VALORArray(n_e_reco_bins_sb, n_y_reco_bins_sb, n_enu_true_bins, n_q2_true_bins);
    fMCStatSb [imode] = 
      new VALORArray(n_e_reco_bins_sb, n_y_reco_bins_sb, n_enu_true_bins, n_q2_true_bins);

    // >> PDF component
    fPDFCompSb[imode] = 
      new VALORArray(kNErecoBinsSb, n_y_reco_bins_sb);           
    // >> PDF total
    // should get here for at least one imode value
    if(fPDFTotNullSb) {              
      LOG("GenericSingleSampleFitModel",pDEBUG) 
        << "Booking PDF (total / simple binning) for " 
        << "beam: "     << util::AsString(fBeam) 
        << ", sample: " << util::AsString(fSample);
      fPDFTotNullSb = false;
      fPDFTotSb     = new VALORArray(kNErecoBinsSb, n_y_reco_bins_sb); 
    }


    // Loop over zones
    for(int izone = 0; izone < kNMaxBinZones; izone++) {
      const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
      const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
      if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;

      LOG("GenericSingleSampleFitModel",pDEBUG) 
        << "Booking MC template for " 
        << "beam: "     << util::AsString(fBeam) 
        << ", sample: " << util::AsString(fSample)
        << ", mode: "   << util::AsString(m) 
        << ", zone: "   << izone;

      // >> MC templates 
      // (Note order of variables: reco first, true later)
      fMCTNullOb[imode][izone] = false;
      fMCTNomOb [imode][izone] = 
        new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins, n_q2_true_bins);
      fMCTTunOb [imode][izone] = 
        new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins, n_q2_true_bins);
      fMCTSysOb [imode][izone] = 
        new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins, n_q2_true_bins);
      fMCTFinOb [imode][izone] = 
        new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins, n_q2_true_bins);
      fMCStatOb [imode][izone] = 
        new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins, n_q2_true_bins);
        
      // Spline library
      fRFPtr [imode][izone] = 
        new VALORArrayL(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins, n_q2_true_bins, kNFitParams);

      // >> PDF component
      fPDFCompOb[imode][izone] = 
        new VALORArray(n_enu_reco_bins,n_y_reco_bins);           
      // >> PDF total
      // should get here for at least one imode value
      if(fPDFTotNullOb[izone]) {              
        LOG("GenericSingleSampleFitModel",pDEBUG) 
          << "Booking PDF (total) for " 
          << "beam: "     << util::AsString(fBeam) 
          << ", sample: " << util::AsString(fSample)
          << ", zone: "   << izone;

        fPDFTotNullOb [izone] = false;
        fPDFTotOb     [izone] = new VALORArray(n_enu_reco_bins,n_y_reco_bins);           
      }
    }//izone

    // Fill the ParamIsAppliedTo array
    for(int ip = 0; ip < conv::kNFitParams; ip++) {
      PhysParamId_t p = kFitParam[ip];
      if(p == kPhypUndefined) continue;
      fParamIsAppliedTo[imode][ip] = util::ParamIsAppliedTo(fBeam,fSample,fDetector,m,p);
    }
  }//imode
}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::Clean(void)
{
  LOG("GenericSingleSampleFitModel",pDEBUG) << "Cleaning-up...";

  for(int imode = 0; imode < kNReacModes; imode++) {

    if(!fMCTNullSb[imode]) {
      fMCTNullSb[imode] = true;
      // MC templates (simple binning)
      if ( fMCTNomSb [imode] ) delete fMCTNomSb [imode];
      if ( fMCTTunSb [imode] ) delete fMCTTunSb [imode];
      if ( fMCTSysSb [imode] ) delete fMCTSysSb [imode];
      if ( fMCTFinSb [imode] ) delete fMCTFinSb [imode];
      if ( fMCStatSb [imode] ) delete fMCStatSb [imode];
      fMCTNomSb[imode] = 0;
      fMCTTunSb[imode] = 0;
      fMCTSysSb[imode] = 0;
      fMCTFinSb[imode] = 0;
      fMCStatSb[imode] = 0;
      // PDF components
      if(fPDFCompSb[imode]) delete fPDFCompSb[imode];
      fPDFCompSb[imode] = 0;
    }
    if(!fPDFTotNullSb) {
      fPDFTotNullSb = true;
      if(fPDFTotSb) delete fPDFTotSb;
      fPDFTotSb = 0;
    }

    for(int izone = 0; izone < kNMaxBinZones; izone++) {
      if(!fMCTNullOb[imode][izone]) {
        fMCTNullOb[imode][izone] = true;
        // MC templates
        if ( fMCTNomOb [imode][izone] ) delete fMCTNomOb [imode][izone];
        if ( fMCTTunOb [imode][izone] ) delete fMCTTunOb [imode][izone];
        if ( fMCTSysOb [imode][izone] ) delete fMCTSysOb [imode][izone];
        if ( fMCTFinOb [imode][izone] ) delete fMCTFinOb [imode][izone];
        if ( fMCStatOb [imode][izone] ) delete fMCStatOb [imode][izone];
        if ( fRFPtr    [imode][izone] ) delete fRFPtr    [imode][izone];
        fMCTNomOb [imode][izone] = 0;
        fMCTTunOb [imode][izone] = 0;
        fMCTSysOb [imode][izone] = 0;
        fMCTFinOb [imode][izone] = 0;
        fMCStatOb [imode][izone] = 0;
        fRFPtr    [imode][izone] = 0;
        // PDF components
        if(fPDFCompOb[imode][izone]) delete fPDFCompOb[imode][izone];
        fPDFCompOb[imode][izone] = 0;
      }
      if(!fPDFTotNullOb[izone]) {
        fPDFTotNullOb[izone] = true;
        if(fPDFTotOb[izone]) delete fPDFTotOb[izone];
        fPDFTotOb[izone] = 0;
      }          
    }//izone

  }//imode

  if(fUseMCDST) {
    if (fMCDST) {
      delete fMCDST;
      fMCDST = 0;
    }
  }
  
  if (fSyst) { delete fSyst; fSyst = 0; }
  if (fRFL)  { delete fRFL ; fRFL  = 0; }
}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::Zero(void)
{
  LOG("GenericSingleSampleFitModel",pDEBUG) << "Zeroing MC templates and/or PDFs...";

  for(int imode = 0; imode < kNReacModes; imode++) {

    if(!fMCTNullSb[imode]) {
      fMCTNomSb [imode] -> SetAll(0.);
      fMCTTunSb [imode] -> SetAll(0.);
      fMCTSysSb [imode] -> SetAll(0.);
      fMCTFinSb [imode] -> SetAll(0.);
      fMCStatSb [imode] -> SetAll(0.);
      fPDFCompSb[imode] -> SetAll(0.);
    }
    if(!fPDFTotNullSb) {
      fPDFTotSb-> SetAll(0.);
    }

    for(int izone = 0; izone < kNMaxBinZones; izone++) {
      if(!fMCTNullOb[imode][izone]) {
        fMCTNomOb [imode][izone] -> SetAll(0.);
        fMCTTunOb [imode][izone] -> SetAll(0.); 
        fMCTSysOb [imode][izone] -> SetAll(0.);
        fMCTFinOb [imode][izone] -> SetAll(0.);
        fMCStatOb [imode][izone] -> SetAll(0.);
        fPDFCompOb[imode][izone] -> SetAll(0.);
      }
      if(!fPDFTotNullOb[izone]) {
        fPDFTotOb[izone] -> SetAll(0.);
      }          
    }//izone

  }//imode
}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::FillFromDST(TTree * t)
{
  // Fill MC templates from the input VALOR/DUNE DST TTree
  // We use a single tree for all samples for a single beam configuration.

  LOG("GenericSingleSampleFitModel",pDEBUG) 
    << "Filling-in MC templates for beam configuration: " << util::AsString(fBeam);

  if(!t) return;
  
  bool old_format = false;

  int    sample        = 0;
  int    reac_mode     = 0;
  double enu_true      = 0.;
  double enu_reco      = 0.;
  double y_reco        = 0.;
  double Q2_true       = 0.;
  double wght          = 1.;
  double wght_pot      = 1.;
  double wght_smear    = 1.;
  
  int bstat_sample     = 0; 
  int bstat_reac_mode  = 0; 
  int bstat_enu_true   = 0; 
  int bstat_enu_reco   = 0; 
  int bstat_y_reco     = 0; 
  int bstat_Q2_true    = 0;   
  int bstat_wght       = 0;   
  int bstat_wght_pot   = 0; 
  int bstat_wght_smear = 0; 
  
  bstat_sample    = t->SetBranchAddress("sample",    &sample);
  bstat_reac_mode = t->SetBranchAddress("reac_mode", &reac_mode);
  bstat_enu_true  = t->SetBranchAddress("enu_true",  &enu_true);
  bstat_enu_reco  = t->SetBranchAddress("enu_reco",  &enu_reco);
  bstat_y_reco    = t->SetBranchAddress("y_reco",    &y_reco);
  bstat_Q2_true   = t->SetBranchAddress("Q2_true",   &Q2_true);
  
  // Weight is not required - use one if failed
  bstat_wght       = t->SetBranchAddress("wght"       , &wght);
  bstat_wght_pot   = t->SetBranchAddress("wght_pot"   , &wght_pot);
  bstat_wght_smear = t->SetBranchAddress("wght_smear" , &wght_smear);
  
  bool any_bad_status = (bstat_sample || bstat_reac_mode || bstat_enu_true || 
      bstat_enu_reco || bstat_y_reco || bstat_wght_pot || bstat_Q2_true);

  if (any_bad_status) {
    LOG("GenericSingleSampleFitModel",pWARN)<<"MiniDST branches not found. Attempting to fall back to 2014a LBNETree format.";
    bstat_sample    = t->SetBranchAddress("sample",       &sample);
    bstat_reac_mode = t->SetBranchAddress("reactionmode", &reac_mode);
    bstat_enu_true  = t->SetBranchAddress("Ev",           &enu_true);
    bstat_enu_reco  = t->SetBranchAddress("Ev_reco",      &enu_reco);
    bstat_y_reco    = t->SetBranchAddress("y_reco",       &y_reco);
    bstat_wght_pot  = t->SetBranchAddress("POTWeight",    &wght_pot);
    bstat_Q2_true   = t->SetBranchAddress("Q2",           &Q2_true);
    
    any_bad_status = (bstat_sample || bstat_reac_mode || bstat_enu_true || 
        bstat_enu_reco || bstat_y_reco || bstat_wght_pot || bstat_Q2_true);
    assert(!any_bad_status);
    old_format = true;
  }


  //~ t->SetBranchStatus("*",             0);
  //~ t->SetBranchStatus("sample",        1); 
  //~ t->SetBranchStatus("reac_mode",     1);    
  //~ t->SetBranchStatus("enu_true",      1);  
  //~ t->SetBranchStatus("enu_reco",      1);  
  //~ t->SetBranchStatus("y_reco",        1);    
  //~ t->SetBranchStatus("wght_pot",      1);
  //~ t->SetBranchStatus("wght",          1);

  Long_t nev = t->GetEntries();
  LOG("GenericSingleSampleFitModel",pINFO) << "Input VALOR DST has " << nev << " entries";
  
  double tree_weight = t->GetWeight();
  
  LOG("GenericSingleSampleFitModel",pNOTICE) << "Input VALOR DST has weight "<<tree_weight;
  
  for(Long_t iev = 0; iev < nev; iev++) 
  {
    t->GetEntry(iev);
    
    Q2_true = TMath::Max(Q2_true,conv::kASmallNum); //DEBUG
    Q2_true = TMath::Min(Q2_true,kQ2trueMax-conv::kASmallNum); //DEBUG

    if(iev%(nev/20)==0) {
      double pct = (100 * (double)(iev+1)) / (double)nev;
      LOG("GenericSingleSampleFitModel",pINFO) << "Reading "<< util::AsString(fBeam)<<" MC DST: "<< TMath::Nint(pct) << "% done";
    }

    // Get sample index
    Sample_t s = util::SampleFromInt(sample);
    if(s == ksUndefined) {
      LOG("GenericSingleSampleFitModel",pWARN) 
        << " ** Undefined sample ID used in MC event: " << iev
        << " (value stored in DST: " << sample << ")";
      //util::Die(-1);return;
    }

    //  ================ NOTE - HACKS ================
    if(s == ksNuMuCC2piC) {
      LOG("HACK",pNOTICE) 
        << "MC event: " << iev << " belongs to sample: " << util::AsString(s) 
        << " not considered separately. Bundle in sample: " << util::AsString(ksNuMuCCoth);
      s = ksNuMuCCoth;
    }
    
#ifdef FORCE_NC_INCLUSIVE
    if(util::IsNC(s)) {
      LOG("HACK",pNOTICE) 
        << "MC event: " << iev << " belongs to NC sample: " << util::AsString(s) 
        << " Bundling it in sample: " << util::AsString(ksNC);
      s = ksNC;
    }
#endif

    //  ==============================================

    if(s != fSample) {
      LOG("GenericSingleSampleFitModel",pDEBUG) 
        << "Ignoring MC event: " << iev 
        << " (sample ID: " << s << " "<< util::AsString(s) 
        << " not matching one used for configuring model: " 
        << fSample <<" "<<util::AsString(fSample) << ")";
      continue;  
    }

    int isample = fArrIdx->SampleIdx(fBeam,fSample);
    if(isample < 0) {
      // fine, we do not indlude all samples in the fit
      LOG("GenericSingleSampleFitModel",pDEBUG) 
        << "Ignoring MC event: " << iev 
        << " (sample ID: " << util::AsString(s) << " not included in current fit)";
      continue;
    }

    // Get reaction mode index
    ReacMode_t m = util::ReacModeFromInt(reac_mode); 
    if(m == kmUndefined) {
      LOG("GenericSingleSampleFitModel",pWARN) 
        << " ** Undefined reaction mode ID used in MC event: " << iev
        << " (value stored in DST: " << reac_mode << "). Ignoring event.";
      continue;
    }
    int imode = fArrIdx->ReacModeIdx(s, m);
    if(imode < 0) {
      // For a given sample we should consider a complete list of
      // true reaction modes (otherwise there are true contributions to the
      // event sample which are not taken into account).
      LOG("GenericSingleSampleFitModel",pFATAL) 
        << " ** Ignoring MC event: " << iev 
        << " (ignoring contribution to sample: " << util::AsString(s) << " from mode: " << util::AsString(m) << " ?)";
      util::Die(-1);return;
    }
    // Get bin zone index
    int izone = util::BinZone(s, enu_reco, y_reco);
    if(izone < 0) {
      //     LOG("GenericSingleSampleFitModel",pFATAL) - turn that to fatal after binning optimization is done
      LOG("GenericSingleSampleFitModel",pWARN) 
        << " ** No bin zone for MC event: " << iev 
        << " (" << util::AsString(s) << "/" << util::AsString(m) 
        << ", enu_reco = " << enu_reco << " GeV, " << " y_reco = " << y_reco << ")";
      //     util::Die(-1);return;
      continue;
    }

    bool is_null = fMCTNullOb[imode][izone];
    if(is_null) {
      LOG("GenericSingleSampleFitModel",pFATAL) 
        << "** Null MC template for sample: " << util::AsString(s) 
        << ", mode: " << util::AsString(m) << ", bin zone = " << izone << " ??";
      util::Die(-1);return;
    }
    bool is_null_sb = fMCTNullSb[imode];
    if(is_null_sb) {
      LOG("GenericSingleSampleFitModel",pFATAL) 
        << "** Null MC template (simple binning) for sample: " << util::AsString(s) 
        << ", mode: " << util::AsString(m) << " ??";
      util::Die(-1);return;
    }

    // check Ereco, yreco and Etrue values against built-in limits
    if(enu_reco < kErecoMin || enu_reco > kErecoMax) {
      LOG("GenericSingleSampleFitModel",pWARN) 
        << "MC event: " << iev << " has reconstructed energy = " << enu_reco 
        << " GeV, range used: [" << kErecoMin << ", " << kErecoMax << "] GeV";
    }
    if(y_reco < kYrecoMin || y_reco > kYrecoMax) {
      LOG("GenericSingleSampleFitModel",pWARN) 
        << "MC event: " << iev << " has reconstructed inelasticity y = " << y_reco 
        << ", range used: [" << kYrecoMin << ", " << kYrecoMax << "]";
    }
    if(enu_true < kEtrueMin || enu_true > kEtrueMax) {
      LOG("GenericSingleSampleFitModel",pWARN) 
        << "MC event: " << iev << " has true energy = " << enu_true 
        << " GeV, range used: [" << kEtrueMin << ", " << kEtrueMax << "] GeV";
    }

    // Get enu_true, enu_reco, y_reco array indices
    const int n_enu_true_bins          = util::NumEtrueBins(s);
    const int n_enu_reco_bins          = util::NumErecoBins(s,izone);
    const int n_q2_true_bins           = util::NumQ2trueBins(s,m);
    const int n_y_reco_bins            = util::NumYrecoBins(s,izone);
    const int n_y_reco_bins_sb         = util::NumYrecoBinsSb(s);
    const double * enu_true_bin_edges  = util::EtrueBinEdges(s);
    const double * q2_true_bin_edges   = util::Q2trueBinEdges(s,m);
    const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(s);
    const double * enu_reco_bin_edges  = util::ErecoBinEdges(s,izone);
    const double * y_reco_bin_edges    = util::YrecoBinEdges(s,izone);

    // protect against vars at upper limit (eg y_reco = 1, set by hand for NC events) as
    // the binary search below will give an index out of limits
    if(enu_reco >= kErecoMax) { enu_reco = enu_reco - kASmallNum; }
    if(y_reco   >= kYrecoMax) { y_reco   = y_reco - kASmallNum;   }

    // work-out the index using the bin-edge array defining the variable-size binning scheme
    int ienu_true    = TMath::BinarySearch(1+(Long_t)n_enu_true_bins, enu_true_bin_edges, enu_true);
    int iq2_true     = TMath::BinarySearch(1+(Long_t)n_q2_true_bins , q2_true_bin_edges , Q2_true );
    int ienu_reco    = TMath::BinarySearch(1+(Long_t)n_enu_reco_bins, enu_reco_bin_edges, enu_reco);
    int iy_reco      = TMath::BinarySearch(1+(Long_t)n_y_reco_bins,   y_reco_bin_edges,   y_reco  );
    // repeat, finding the indices for the template versions using a simple binning scheme
    int ienu_reco_sb = TMath::BinarySearch(1+(Long_t)kNErecoBinsSb,    kErecoBinEdgesSb,    enu_reco);
    int iy_reco_sb   = TMath::BinarySearch(1+(Long_t)n_y_reco_bins_sb, y_reco_bin_edges_sb, y_reco  );

    // Exposure for assumed data - Weight MC templates to that exposure
    double data_pot = fPOT;

    // Calculate POT weight (assumed data exposure) / (generated MC exposure)
    double pot_wght = wght_pot * data_pot * tree_weight;
    
    if(fFiducialMass > 0) {
      pot_wght = pot_wght*fFiducialMass;
    }

    LOG("GenericSingleSampleFitModel",pDEBUG) 
      << "Inserting to MC teplates --> MC event #" << iev 
      << "\n imode     = " << imode    << " (" << util::AsString(m) << ")"
      << "\n izone     = " << izone   
      << "\n wght      = " << wght 
      << "\n pot_wght  = " << pot_wght 
      << "\n ienu_reco = " << ienu_reco  << " (Enu_reco = " << enu_reco <<   " GeV), allowed idx range: [" << 0 << " -> " << n_enu_reco_bins-1 << "], " << n_enu_reco_bins <<" bins"
      << "\n iy_reco   = " << iy_reco    << " (y_reco   = " << y_reco   <<       "), allowed idx range: [" << 0 << " -> " << n_y_reco_bins  -1 << "], " << n_y_reco_bins   <<" bins"
      << "\n ienu_true = " << ienu_true  << " (Enu_true = " << enu_true <<   " GeV), allowed idx range: [" << 0 << " -> " << n_enu_true_bins-1 << "], " << n_enu_true_bins <<" bins"
      << "\n iQ2_true  = " << iq2_true   << " (Q2_true  = " << Q2_true  << " GeV^2), allowed idx range: [" << 0 << " -> " << n_q2_true_bins -1 << "], " << n_q2_true_bins  <<" bins";

    // Believe that such a check is not performed in VALORArray, so check here just in case something went wrong in binary search above
    assert(ienu_reco >= 0 && ienu_reco < n_enu_reco_bins);
    assert(iy_reco   >= 0 && iy_reco   < n_y_reco_bins  );
    assert(ienu_true >= 0 && ienu_true < n_enu_true_bins);
    assert(iq2_true  >= 0 && iq2_true  < n_q2_true_bins);
    
    
    double this_entry = wght;
    
    this_entry *= pot_wght;
    this_entry *= wght_smear;

    // Add `nom' array entry (and init `tun', `sys' and `fin' arrays = `nom')
    double curr_wght = fMCTNomOb[imode][izone]->GetEntry(ienu_reco, iy_reco, ienu_true, iq2_true);
    curr_wght += this_entry;
    fMCTNomOb [imode][izone]->SetEntry(curr_wght, ienu_reco, iy_reco, ienu_true, iq2_true);
    fMCTTunOb [imode][izone]->SetEntry(curr_wght, ienu_reco, iy_reco, ienu_true, iq2_true);
    fMCTSysOb [imode][izone]->SetEntry(curr_wght, ienu_reco, iy_reco, ienu_true, iq2_true);
    fMCTFinOb [imode][izone]->SetEntry(curr_wght, ienu_reco, iy_reco, ienu_true, iq2_true);     
    fMCStatOb [imode][izone]->SetEntry(        1, ienu_reco, iy_reco, ienu_true, iq2_true);

    double curr_wght_sb = fMCTNomSb[imode]->GetEntry(ienu_reco_sb, iy_reco_sb, ienu_true, iq2_true);
    curr_wght_sb += this_entry;
    fMCTNomSb [imode]->SetEntry(curr_wght_sb, ienu_reco_sb, iy_reco_sb, ienu_true, iq2_true);
    fMCTTunSb [imode]->SetEntry(curr_wght_sb, ienu_reco_sb, iy_reco_sb, ienu_true, iq2_true);
    fMCTSysSb [imode]->SetEntry(curr_wght_sb, ienu_reco_sb, iy_reco_sb, ienu_true, iq2_true);
    fMCTFinSb [imode]->SetEntry(curr_wght_sb, ienu_reco_sb, iy_reco_sb, ienu_true, iq2_true);
    fMCStatSb [imode]->SetEntry(           1, ienu_reco_sb, iy_reco_sb, ienu_true, iq2_true);
  }//iev 
}
//________________________________________________________________________________________
bool GenericSingleSampleFitModel::FillFromTemplateFile (TFile * f, string tag)
{
  bool success = true;

  int isample = fArrIdx->SampleIdx(fBeam,fSample);
  BeamConf_t b = fBeam;
  Sample_t   s = fSample;

  for(int imode = 0; imode < kNReacModes; imode++) {
    ReacMode_t m = kReactionModes[isample][imode];
    if(m == kmUndefined) continue;
    for(int izone = 0; izone < kNMaxBinZones; izone++) {
      TString name = TString::Format("%s_%s_%s_z%d", 
          util::AsString(b).c_str(), util::AsString(s).c_str(), util::AsString(m).c_str(), izone);
      TString obj_name = TString::Format("%s_%s_%s", tag.c_str(), "mctnom_ob_vf", name.Data());
      VALORArray * arr = dynamic_cast<VALORArray*>(f->Get(obj_name.Data()));
      if (arr && arr->GetSize()) {
        assert(arr->GetDimensionSizes() == fMCTNomOb[imode][izone]->GetDimensionSizes());
        assert(arr->GetDimensionSizes() == fMCTTunOb[imode][izone]->GetDimensionSizes());
        assert(arr->GetDimensionSizes() == fMCTSysOb[imode][izone]->GetDimensionSizes());
        assert(arr->GetDimensionSizes() == fMCTFinOb[imode][izone]->GetDimensionSizes());
        assert(arr->GetDimensionSizes() == fMCStatOb[imode][izone]->GetDimensionSizes());
        fMCTNomOb [imode][izone]->CopyFrom(*arr);
        fMCTTunOb [imode][izone]->CopyFrom(*arr);
        fMCTSysOb [imode][izone]->CopyFrom(*arr);
        fMCTFinOb [imode][izone]->CopyFrom(*arr);
        fMCStatOb [imode][izone]->CopyFrom(*arr);
        fMCStatOb [imode][izone]->SetAll(1.);  
        delete arr;
      }
      else {
        success = false;
        LOG("GenericSingleSampleFitModel",pERROR) << "Failed to read template "<<obj_name;
      }
    }//izone
    // Do the Sb arrays
    TString name = TString::Format("%s_%s_%s", 
        util::AsString(b).c_str(), util::AsString(s).c_str(), util::AsString(m).c_str());
    TString obj_name = TString::Format("%s_%s_%s", tag.c_str(), "mctnom_sb_vf", name.Data());
    VALORArray * arr = dynamic_cast<VALORArray*>(f->Get(obj_name.Data()));
    if (arr && arr->GetSize()) {
      assert(arr->GetDimensionSizes() == fMCTNomSb[imode]->GetDimensionSizes());
      assert(arr->GetDimensionSizes() == fMCTTunSb[imode]->GetDimensionSizes());
      assert(arr->GetDimensionSizes() == fMCTSysSb[imode]->GetDimensionSizes());
      assert(arr->GetDimensionSizes() == fMCTFinSb[imode]->GetDimensionSizes());
      assert(arr->GetDimensionSizes() == fMCStatSb[imode]->GetDimensionSizes());
      fMCTNomSb [imode]->CopyFrom(*arr);
      fMCTTunSb [imode]->CopyFrom(*arr);
      fMCTSysSb [imode]->CopyFrom(*arr);
      fMCTFinSb [imode]->CopyFrom(*arr);
      fMCStatSb [imode]->CopyFrom(*arr);
      fMCStatSb [imode]->SetAll(1.);
      delete arr;
    }
    else {
      success = false;
      LOG("GenericSingleSampleFitModel",pERROR) << "Failed to read template "<<obj_name;
    }
  } //imode

  if (!success) {
    util::Die(-1);
  }
  return success;
}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::ApplyTuning(Option_t * /*opt*/)
{
  // This method maps nom -> tun MC templates
  // This is applied once when the model is constructed, not everytime Generate() is called.
  // No external tuning available for the time-being


}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::FluctuateMCStat(Option_t * option)
{
  // Take into account the effect of MC statistics on the tuned MC templates.
  // Note that this is the error due to the finite MC statistics used to construct the
  // model and not the statistical error for the assumed (or actual) experimental exposure
  // which is also taken account when generating toy-MC experiments.
  // NOTE: For the time-being the effect applied on the tuned templates and stored on the 
  // tuned templates, so we lose the tuned templates as they were before applying the MC
  // statistical error. If this is important, we ought to create a new set of templates
  // to hold this intermediate step going from the `tun' to the `sys' templates.

  LOG("GenericSingleSampleFitModel",pINFO) 
    << "Applying MC statistic error (option: " 
    << ((option) ? option : "")
    << ")";

#ifdef _apply_mc_stat_fluctuation_

  bool update_mct_sb = false;
  if(option) {
    string opt = option;
    if(opt.find("+SB") != string::npos) {
      update_mct_sb = true;
    }
  }
  
  //Rnd * rnd = Rnd::Instance()->RndToyMCstat().Poisson(nmc) : nmc;
  Rnd * rnd = Rnd::Instance();

  int isample = fArrIdx->SampleIdx(fBeam,fSample);

  const int n_enu_true_bins = util::NumEtrueBins(fSample);
  const int n_y_reco_bin_edges_sb = util::NumYrecoBinsSb(fSample);
  for(int imode = 0; imode < kNReacModes; imode++) {

    ReacMode_t m = kReactionModes[isample][imode];
    if(m == kmUndefined) continue;
    
    const int n_q2_true_bins  = util::NumQ2trueBins(fSample,m);

    // Updating only the templates using the optimized binning
    if(!update_mct_sb) {
      for(int izone = 0; izone < kNMaxBinZones; izone++) {
        bool is_null = fMCTNullOb[imode][izone];
        if(is_null) continue;
        const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
        const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
        for(int iet = 0; iet < n_enu_true_bins; iet++) {
          for(int iqt = 0; iqt < n_q2_true_bins; iqt++) {
            for(int ier = 0; ier < n_enu_reco_bins; ier++) {
              for(int iyr = 0; iyr < n_y_reco_bins; iyr++) {
                double val  = fMCTTunOb[imode][izone]->GetEntry(ier,iyr,iet,iqt);
                double nmc  = fMCStatOb[imode][izone]->GetEntry(ier,iyr,iet,iqt);
                // Fluctuate MC statistics and get the tweak factor
                double nmcf = rnd->RndToyMCstat().Poisson(nmc); 
                //double twk  = (nmc > 0) ? nmcf/nmc ? 1;
                double twk  = (nmc > 0) ? nmcf/nmc : 1;
                // Apply the tweak factor in the template, obviously a small effect for 
                // large MC statistics. Again noting that this is not the statistical error
                // for the current exposure. That one will be applied later in toy-MC generation.
                double valf = val * twk; 
                fMCTTunOb[imode][izone]->SetEntry(valf,ier,iyr,iet,iqt);
              }//iyr: yreco bins
            }//ier: Ereco bins
          }//iqt: Q2 bins
        }//iet: Etrue bins
      }//izone
    }

    // Updating both the templates in optimized and simple binning schemes.
    // They can not be fluctuated independently because the represent the exact same quantity
    // in two binning schemes. The sum of bin contents (for specific bin ranges) of templates
    // in the simple scheme should equal the contents of specific bins of templates in the optimized scheme...
    else {

      // Reset template in optimized binning
      for(int izone = 0; izone < kNMaxBinZones; izone++) {
        bool is_null = fMCTNullOb[imode][izone];
        if(is_null) continue;
        fMCTTunOb[imode][izone]->SetAll(0.); 
      }

      // Start by fluctuation the templates using the simple binning.
      // Then map each simple bin to an optimized bin and add to its contents. 
      for(int iet = 0; iet < n_enu_true_bins; iet++) {
        for(int iqt = 0; iqt < n_q2_true_bins; iqt++) {
          for(int ier = 0; ier < kNErecoBinsSb; ier++) {
            for(int iyr = 0; iyr < n_y_reco_bin_edges_sb; iyr++) {
              double val  = fMCTTunSb[imode]->GetEntry(ier,iyr,iet,iqt);
              double nmc  = fMCStatSb[imode]->GetEntry(ier,iyr,iet,iqt);
              double nmcf = rnd->RndToyMCstat().Poisson(nmc); 
              //double twk  = (nmc > 0) ? nmcf/nmc ? 1;
              double twk  = (nmc > 0) ? nmcf/nmc : 1;
              double valf = val * twk; 
              fMCTTunSb[imode]->SetEntry(valf,ier,iyr,iet,iqt);

              // Map to template with optimized binning
              const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(fSample);
              double enu_reco = kErecoBinEdgesSb[ier]   + (kErecoBinEdgesSb[ier+1]  -kErecoBinEdgesSb[ier]  )/2.;
              double y_reco   = y_reco_bin_edges_sb[iyr] + (y_reco_bin_edges_sb[iyr+1]-y_reco_bin_edges_sb[iyr])/2.;
              int izone = util::BinZone(fSample, enu_reco, y_reco);
              if(izone < 0) {
                //                  LOG("GenericSingleSampleFitModel",pFATAL) - turn that to fatal after binning optimization is done
                LOG("GenericSingleSampleFitModel",pWARN)
                  << " ** No bin zone for toy MC event (" << " (" << util::AsString(fSample) << ")"
                  << ", enu_reco = " << enu_reco << " GeV, " << " y_reco = " << y_reco << ")";
                //util::Die(-1);return;
              }
              const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
              const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
              const double * enu_reco_bin_edges  = util::ErecoBinEdges(fSample,izone);
              const double * y_reco_bin_edges    = util::YrecoBinEdges(fSample,izone);
              int ier2 = TMath::BinarySearch(1+(Long_t)n_enu_reco_bins, enu_reco_bin_edges, enu_reco);
              //int iy2  = TMath::BinarySearch(1+(Long_t)n_y_reco_bins,   y_reco_bin_edges,   y_reco  );       
              int iyr2  = TMath::BinarySearch(1+(Long_t)n_y_reco_bins,   y_reco_bin_edges,   y_reco  );
              double valf_ob = fMCTTunOb[imode][izone]->GetEntry(ier2,iyr2,iet,iqt);
              valf_ob += valf;
              fMCTTunOb[imode][izone]->SetEntry(valf_ob,ier2,iyr2,iet,iqt);
            }//iyr: yreco bins
          }//ier: Ereco bins
        }//iqt: Q2 true bins
      }//iet: Etrue bins

    }//update_mct_sb

  }//imode

#else

  LOG("GenericSingleSampleFitModel",pINFO) << "MC statistic error *not* applied";

#endif

}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::ApplySystematics(Option_t * /*opt*/)
{
  // This method maps tun -> sys MC templates.
  // Applying detector systematics and uncorrelated flux/cross-section systematics.

  // NOTE: For the time-being, everything (flux, cross-sections, detector systematics)
  // are applied together at the next method, ApplyPhysics()
  // Improve as we get to a new scheme where all detector systematic tweaks are obtained
  // using the Cholesky method and an input detector systematics correlation matrix.

  /*
     bool update_mct_sb = false;
     if(option) {
     string opt = option;
     if(opt.find("+SB") != string::npos) {
     update_mct_sb = true;
     }
     }

     for(int imode = 0; imode < kNReacModes; imode++) {

     for(int izone = 0; izone < kNMaxBinZones; izone++) {
     bool is_null = fMCTNullOb[imode][izone];
     if(!is_null) {

     }//!null
     }//izone

     }//imode
     */

}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::ApplyPhysics(Option_t * option)
{
  // This method maps sys -> fin MC templates.
  // Applying correlated flux and cross-section systematics

  LOG("GenericSingleSampleFitModel",pINFO) 
    << fName
    << " - Applying physics params (option: " 
    << ((option) ? option : "")
    << ")";

  bool update_mct_sb = false;
  if(option) {
    string opt = option;
    if(opt.find("+SB") != string::npos) {
      update_mct_sb = true;
    }
  }
  
  const int n_true1_bins         = util::NumEtrueBins  (fSample);
  const double * true1_bin_edges = util::EtrueBinEdges (fSample);

  int isample = fArrIdx->SampleIdx(fBeam,fSample);

  for(int imode = 0; imode < kNReacModes; imode++) {
    ReacMode_t m = kReactionModes[isample][imode];
    if(m == kmUndefined) continue;
    
    const int n_true2_bins = util::NumQ2trueBins(fSample,m);
    const double * true2_bin_edges = util::Q2trueBinEdges(fSample,m);

#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
    LOG("GenericSingleSampleFitModel",pDEBUG) 
      << "Handing templates for: " 
      << util::AsString(fBeam) << ", " << util::AsString(fSample) << ", " << util::AsString(m);

    LOG("GenericSingleSampleFitModel",pDEBUG) 
      << "Initializing `fin' templates to the `sys' ones";
#endif
    VALORArrayBin bin;
    for(int izone = 0; izone < kNMaxBinZones; izone++) {
      bool is_null = fMCTNullOb[imode][izone];
      if(is_null) {continue;}
      const int n_reco1_bins = util::NumErecoBins(fSample,izone);
      const int n_reco2_bins = util::NumYrecoBins(fSample,izone);
      // copy sys -> fin MC templates
      fMCTFinOb[imode][izone]->CopyDataOnlyFrom(*fMCTSysOb[imode][izone]);
      
      
      for(int ip = 0; ip < kNFitParams; ip++) {
        PhysParamId_t p = kFitParam[ip];
        if (p == kPhypUndefined          ) {continue;}
        if (util::IsOscParam(p)          ) {continue;} 
        if (!fParamIsAppliedTo[imode][ip]) {continue;}
        
        bool has_splines = fParamHasSplines[ip];
        bool has_kinematic_dependence = kFitParamTrueKinematicDependence[ip];
        
        double f = fPhysHypothesis.CurrValue(p);
        
      // First apply spline parameters
        if (has_splines) {
#ifndef SPLINE_WEIGHTS_ARE_ONE
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
          LOG("GenericSingleSampleFitModel",pDEBUG) 
            << "Applying parameter: " << util::AsString(p) << " with value = " << f 
            << " using splines.";
#endif
          //~ if (TMath::Abs(f-1) < kASmallNum ) {continue;} // SHOULD USE A MORE INTELLIGENT CENTRE
        
          VALORArrayBin splbin;
          splbin.bin5 = ip;
          for(int it1 = 0; it1 < n_true1_bins; it1++) {
            bin.bin3 = it1;
            splbin.bin3 = it1;
            for(int it2 = 0; it2 < n_true2_bins; it2++) {
              bin.bin4 = it2;
              splbin.bin4 = it2;
              for(int ir1 = 0; ir1 < n_reco1_bins; ir1++) {
                bin.bin1 = ir1;
                splbin.bin1 = ir1;
                for(int ir2 = 0; ir2 < n_reco2_bins; ir2++) {
                  bin.bin2 = ir2;
                  splbin.bin2 = ir2;
                  double response = 1;
                  const util::Interpolator * spl = reinterpret_cast<util::Interpolator*>(fRFPtr[imode][izone]->GetEntry(splbin));
                  if (spl==util::DuneRFL::kNoSplineRequired) {
                    LOG("GenericSingleSampleFitModel",pERROR)
                      <<"Got no spline required for bin expecting spline."
                      <<util::AsString(p)<<", "<<util::AsString(fBeam)<<", "
                      <<util::AsString(fSample)<<","<<util::AsString(m);
                  }
                  if (spl!=util::DuneRFL::kFlatSpline) {
                    response = spl->EvalWithLimits(f);
                    if (response<0) {
                      LOG("GenericSingleSampleFitModel",pINFO)
                       <<"Negative response from spline (OB) "//<<spl->GetName()
                       <<" evaluated at "<<f<<" with result "<<response
                       <<". Using 0 instead.";
                      response = 0;
                    }
                  }
                  double & val = fMCTFinOb[imode][izone]->GetEntryRef(bin);
                  val *= response;
                }//ir2
              }//ir1
            }//it2
          }//it1
#endif //SPLINE_WEIGHTS_ARE_ONE
        } // has_splines
        else if (has_kinematic_dependence) {
          f = TMath::Max(0.,f);
          bool tweaked = TMath::Abs(f-1) > kASmallNum;
          if(!tweaked) continue;
          const double true1_min  = kFitParamEtrueRange [ip][0];
          const double true1_max  = kFitParamEtrueRange [ip][1];     
          const double true2_min  = kFitParamQ2trueRange[ip][0];
          const double true2_max  = kFitParamQ2trueRange[ip][1];     
          int i_true1_min = TMath::BinarySearch((Long_t)n_true1_bins, true1_bin_edges, true1_min+kASmallNum);
          int i_true1_max = TMath::BinarySearch((Long_t)n_true1_bins, true1_bin_edges, true1_max-kASmallNum);
          int i_true2_min = TMath::BinarySearch((Long_t)n_true2_bins, true2_bin_edges, true2_min+kASmallNum);
          int i_true2_max = TMath::BinarySearch((Long_t)n_true2_bins, true2_bin_edges, true2_max-kASmallNum);
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
          LOG("GenericSingleSampleFitModel",pINFO) 
            << fName <<": "
            << "Applying parameter: " << util::AsString(p) << " with value = " << f 
            << " in Etrue bin range: ["   << true1_min << ", " << true1_max << "]"
            << " and Q2true bin range: [" << true2_min << ", " << true2_max << "]";
#endif
          for(int it1 = i_true1_min; it1 <= i_true1_max; it1++) {
            bin.bin3 = it1;
            for(int it2 = i_true2_min; it2 <= i_true2_max; it2++) {
              bin.bin4 = it2;
              for(int ir1 = 0; ir1 < n_reco1_bins; ir1++) {
                bin.bin1 = ir1;
                for(int ir2 = 0; ir2 < n_reco2_bins; ir2++) {
                  bin.bin2 = ir2;
                  double & val = fMCTFinOb[imode][izone]->GetEntryRef(bin);
                  val *= f;
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
                  LOG("GenericSingleSampleFitModel",pDEBUG) 
                    << "MCT[" << imode << ", " << izone << "] = " 
                    << val/f << " --> " << val;
#endif
                }//iyr: yreco bins
              }//ier: Ereco bins
            }//it2: Q2 true bins
          }//it1: Etrue bins
        }// has kinematic dependence

        // then apply the non-Etrue-dependent factors (use scale - not loop)
        else {
          double noEt = 1 ;
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
          LOG("GenericSingleSampleFitModel",pINFO)
            << fName <<": "
            << "Applying parameter: " << util::AsString(p) << " with value = " << f << " to whole mode "<<util::AsString(m);
#endif
          noEt *= f;
          noEt = TMath::Max(0.,noEt);
          fMCTFinOb[imode][izone]->Scale(noEt);
        } // No spline, no kin dependence
      } //iparam
    }//izone
    
    if(update_mct_sb) {
      if (!imode) {
        LOG("GenericSingleSampleFitModel",pNOTICE) << "Updating simple binning templates for "<<fName<<".";
      }
      const int      n_reco1_bins_sb      = util::NumErecoBinsSb (fSample);
      const double * reco1_bin_edges_sb   = util::ErecoBinEdgesSb(fSample);
      const int      n_reco2_bins_sb      = util::NumYrecoBinsSb (fSample);
      const double * reco2_bin_edges_sb   = util::YrecoBinEdgesSb(fSample);
      bool is_null = fMCTNullSb[imode];
      if(is_null) {continue;}
      fMCTFinSb[imode]->CopyDataOnlyFrom(*(fMCTSysSb[imode]));
      
      for(int ip = 0; ip < kNFitParams; ip++) {
        PhysParamId_t p = kFitParam[ip];
        if (p == kPhypUndefined          ) {continue;}
        if (util::IsOscParam(p)          ) {continue;}
        if (!fParamIsAppliedTo[imode][ip]) {continue;}
        
        double f = fPhysHypothesis.CurrValue(p);
        
        bool has_splines = fParamHasSplines[ip];
        bool has_kinematic_dependence = kFitParamTrueKinematicDependence[ip];
        
        // first apply spline parameters
        if (has_splines) {
#ifndef SPLINE_WEIGHTS_ARE_ONE
          //~ if (TMath::Abs(f-1) < kASmallNum ) {continue;} // SHOULD USE A MORE INTELLIGENT CENTRE
          VALORArrayBin sbin;
          util::KinematicPoint kp;
          for(int it1 = 0; it1 < n_true1_bins; it1++) {
            sbin.bin3 = it1;
            kp.true1 = (true1_bin_edges[it1]+true1_bin_edges[it1+1])/2;
            for(int it2 = 0; it2 < n_true2_bins; it2++) {
              sbin.bin4 = it2;
              kp.true2 = (true2_bin_edges[it2]+true2_bin_edges[it2+1])/2;
              for(int irsb1 = 0; irsb1 < n_reco1_bins_sb; irsb1++) {
                sbin.bin1 = irsb1;
                kp.reco1 = (reco1_bin_edges_sb[irsb1]+reco1_bin_edges_sb[irsb1+1])/2;
                for(int irsb2 = 0; irsb2 < n_reco2_bins_sb; irsb2++) {
                  sbin.bin2 = irsb2;
                  kp.reco2 = (reco2_bin_edges_sb[irsb2]+reco2_bin_edges_sb[irsb2+1])/2;
                  util::KinematicBin kb = fRFL->GetBin(kp,m);
                  const util::Interpolator * spl = fRFL->GetSpline(m,p,kb);
                  if (spl==util::DuneRFL::kNoSplineRequired) {
                    LOG("GenericSingleSampleFitModel",pERROR)
                      <<"Got no spline required for simple bin expecting spline."
                      <<util::AsString(p)<<", "<<util::AsString(fBeam)<<", "
                      <<util::AsString(fSample)<<","<<util::AsString(m);
                  }
                  double response = spl->EvalWithLimits(f);
                  if (response<0) {
                    LOG("GenericSingleSampleFitModel",pINFO)
                     <<"Negative response from spline (SB) "//<<spl->GetName()
                     <<" evaluated at "<<f<<" with result "<<response
                     <<". Using 0 instead.";
                    response = 0;
                  }
                  double & val = fMCTFinSb[imode]->GetEntryRef(sbin);
                  val *= response;
                }//ir2
              }//ir1
            }//it2
          }//it1
#endif
        }//has splines
        
        else if (has_kinematic_dependence) {
          f = TMath::Max(0.,f);
          bool tweaked = TMath::Abs(f-1) > kASmallNum;
          if(!tweaked) continue;
          const double true1_min = kFitParamEtrueRange[ip][0];
          const double true1_max = kFitParamEtrueRange[ip][1];     
          int itrue1_min = TMath::BinarySearch((Long_t)n_true1_bins, true1_bin_edges, true1_min+kASmallNum);
          int itrue1_max = TMath::BinarySearch((Long_t)n_true1_bins, true1_bin_edges, true1_max-kASmallNum);
          const double true2_min = kFitParamQ2trueRange[ip][0];
          const double true2_max = kFitParamQ2trueRange[ip][1];
          int itrue2_min = TMath::BinarySearch((Long_t)n_true2_bins, true2_bin_edges, true2_min+kASmallNum);
          int itrue2_max = TMath::BinarySearch((Long_t)n_true2_bins, true2_bin_edges, true2_max-kASmallNum);

          for(int it1 = itrue1_min; it1 <= itrue1_max; it1++) {
            bin.bin3 = it1;
            for(int it2 = itrue2_min; it2 <= itrue2_max; it2++) {
              bin.bin4 = it2;
              for(int irsb1 = 0; irsb1 < kNErecoBinsSb; irsb1++) {
                bin.bin1 = irsb1;
                for(int irsb2 = 0; irsb2 < n_reco2_bins_sb; irsb2++) {
                  bin.bin2 = irsb2;
                  double & val = fMCTFinSb[imode]->GetEntryRef(bin);
                  val *= f;
                }//ir2: yreco bins
              }//ir1: Ereco bins
            }//it2: Q2 bins
          }//it1: Etrue bins
        }// has kinematic dependence
        else {
          // then apply the non-Etrue-dependent factors (bundle them together to loop over the
          // Ereco,yreco,Etrue bins just once)
          double fnoEt = 1.;

          f = TMath::Max(0.,f);
          bool tweaked = TMath::Abs(f-1) > kASmallNum;
          if(!tweaked) continue;
          fnoEt *= f;
          fnoEt = TMath::Max(0.,fnoEt);
          fMCTFinSb[imode]->Scale(fnoEt);
        }// normalisations
      }//ip
    }//update_mct_sb?
  }//imode
  if (update_mct_sb) {
    LOG("GenericSingleSampleFitModel",pNOTICE) << "Simple binning update completed.";
  }
}
//________________________________________________________________________________________                                      
void GenericSingleSampleFitModel::ApplyOscProb(Option_t * option)
{
  // This method applies oscillation probabilities                                                                              
  // from fin to fin templates                       
  // a la SuperKMC
  
  LOG("GenericSingleSampleFitModel",pINFO)
    << "Applying oscillation probabilities (option: "
    << ((option) ? option : "")
    << ")";
  
  bool update_mct_sb = false;
  if(option) {
    string opt = option;
    if(opt.find("+SB") != string::npos) {
      update_mct_sb = true;
    }
  }
  
  int isample = fArrIdx->SampleIdx(fBeam,fSample);

  //first, check that there are actually osc params in the fit params list 
  bool apply_osc_prob = false;
  for(int ip = 0; ip < kNFitParams; ip++) {
    PhysParamId_t p = kFitParam[ip];
    if(util::IsOscParam(p)) {apply_osc_prob = true;}
  }
  
  // If not, just set the oscillated modes to zero and move on
  if (!apply_osc_prob) {
    for(int imode = 0; imode < kNReacModes; imode++) {
      ReacMode_t m = kReactionModes[isample][imode];
      if(m == kmUndefined) {continue;}
      conv::NuFlavour_t init_flav   = util::ReacModeToInitFlavor(m);
      conv::NuFlavour_t final_flav  = util::ReacModeToFinalFlavor(m);
      if (init_flav != final_flav) {
        for(int izone = 0; izone < kNMaxBinZones; izone++) {
          fMCTFinOb[imode][izone]->SetAll(0.);
        }
        if (update_mct_sb) {fMCTFinSb[imode]->SetAll(0.);}
      }
    }
    return;
  }
  
  // Otherwise actually do the oscillation calculation
  //first find the baseline to be applied
  double baseline = util::Baseline(fBeam,fDetector);
  fNuOsc3Flavour.SetBaseline(baseline);
  
  // set oscillation parameters to the oscillation probability calculation code
  double mixing12 = fPhysHypothesis.CurrValue(kPhypMixing12);
  double mixing13 = fPhysHypothesis.CurrValue(kPhypMixing13);
  double mixing23 = fPhysHypothesis.CurrValue(kPhypMixing23);
  double dmsq     = fPhysHypothesis.CurrValue(kPhypDm12sq);
  double Dmsq     = fPhysHypothesis.CurrValue(kPhypDm23sq);
  double delta_cp = fPhysHypothesis.CurrValue(kPhypCPV    );

  NuOscMixParam_t omp = Opt::Instance()->gOscMixingParamChoice;
  NuOscDmsqScheme_t  dmsqscheme = Opt::Instance()->GetEffectiveDmsqScheme();

  double p_osc[3][3];
  double p_osc_bar[3][3];

  // mixing params are: sin^2(2*theta)                                                                                        
  // independent squared mass splittings are: dm^2 = Dm^2_{12}, Dm^2 = |Dm^2_{23}|                                            
  if(dmsqscheme == kNuDmsq12andAbs23 && omp == kNuMixSinsq2Theta)
  {
    fNuOsc3Flavour.SetOscParameters(mixing12,mixing13,mixing23,dmsq,Dmsq,delta_cp);
  }
  // mixing params are: sin^2(theta)                                                                                     
  // independent squared mass splittings are: dm^2 = Dm^2_{12}, Dm^2 = |Dm^2_{23}|                                          
  else if(dmsqscheme == kNuDmsq12andAbs23 && omp == kNuMixSinsqTheta)
  {
    fNuOsc3Flavour.SetOscParametersSinSqTAll(mixing12,mixing13,mixing23,dmsq,Dmsq,delta_cp);
  }
  // mixing params are: sin^2(2*theta)                                                                                      
  // independent squared mass splittings are: dm^2 = Dm^2_{12}, Dm^2 = |m^2_{3} - (m^2_{1} + m^2_{1})/2|                   
  else if(dmsqscheme == kNuDmsqFogliLisi && omp == kNuMixSinsq2Theta)
  {
    fNuOsc3Flavour.SetOscParametersSSq2TDmAtmSol(mixing12,mixing13,mixing23,dmsq,Dmsq,delta_cp);
  }
  // mixing params are: sin^2(theta)                                                                                        
  // independent squared mass splittings are: dm^2 = Dm^2_{12}, Dm^2 = |m^2_{3} - (m^2_{1} + m^2_{1})/2|                    
  else if(dmsqscheme == kNuDmsqFogliLisi && omp == kNuMixSinsqTheta)
  {
    fNuOsc3Flavour.SetOscParametersDmsqAtmSol(mixing12,mixing13,mixing23,dmsq,Dmsq,delta_cp);
  }
  // mixing paras are: sin^2(2*theta)                                                                                     
  // independent squared mass splittings are: dm^2 = Dm^2_{12}, Dm^2 = |Dm^2_{31}|                                       
  else if(dmsqscheme == kNuDmsq12andAbs31 && omp == kNuMixSinsq2Theta)
  {
    fNuOsc3Flavour.SetOscParametersSSq2TDmsq13(mixing12,mixing13,mixing23,dmsq,Dmsq,delta_cp);
  }
  // mixing paras are: sin^2(theta)                                                                                        
  // independent squared mass splittings are: dm^2 = Dm^2_{12}, Dm^2 = |Dm^2_{31}|                                           
  else if(dmsqscheme == kNuDmsq12andAbs31 && omp == kNuMixSinsqTheta)
  {
    fNuOsc3Flavour.SetOscParametersDmsq13(mixing12,mixing13,mixing23,dmsq,Dmsq,delta_cp);
  }
  //unknown                                                                                                                    
  else {
    std::cerr << "**  GenericSingleSampleFitModel >> Can't handle choice of "
         << "\n oscillation mixing params: " << util::AsString(omp)
         << "\n and independent squared mass-splittings: " << util::AsString(dmsqscheme)
         << endl;
    util::Die(-1);return;
  }

  const int n_true1_bins         = util::NumEtrueBins  (fSample);
  const double * true1_bin_edges = util::EtrueBinEdges (fSample);

  for(int imode = 0; imode < kNReacModes; imode++) {
    ReacMode_t m = kReactionModes[isample][imode];
    if(m == kmUndefined) continue;
    
    //check if beam+sample+mode should be applied oscillation probabilities                                                
    if(!util::OscProbIsAppliedTo(fBeam,fSample,m)) {continue; }
    
    const int n_true2_bins = util::NumQ2trueBins(fSample,m);
    const double * true2_bin_edges = util::Q2trueBinEdges(fSample,m);
    
    VALORArrayBin bin;
    VALORArrayBin sbin;

    for(int it1 = 0; it1 < n_true1_bins; it1++) {
      bin .bin3 = it1;
      sbin.bin3 = it1;
      //get the true energy to calculate osc prob 
      double Etrue = (true1_bin_edges[it1]+true1_bin_edges[it1+1])/2; 

      fNuOsc3Flavour.CalcMatterOscProbAll(false, Etrue, p_osc    );
      fNuOsc3Flavour.CalcMatterOscProbAll(true , Etrue, p_osc_bar);

      double p_numu_numu       = p_osc    [1][1];
      double p_numu_nue        = p_osc    [1][0];
      double p_numu_nutau      = p_osc    [1][2];
      double p_numubar_numubar = p_osc_bar[1][1];
      double p_numubar_nuebar  = p_osc_bar[1][0];
      double p_numubar_nutaubar= p_osc_bar[1][2];
      double p_nue_nue         = p_osc    [0][0];
      double p_nue_numu        = p_osc    [0][1];
      double p_nue_nutau       = p_osc    [0][2];
      double p_nuebar_nuebar   = p_osc_bar[0][0];
      double p_nuebar_numubar  = p_osc_bar[0][1];
      double p_nuebar_nutaubar = p_osc_bar[0][2];

      double posc = 1.;
      if(util::IsCC(m))
      {
        if     ( util::IsNuMu(m)       ) { posc = p_numu_numu;       }
        else if( util::IsNuMuBar(m)    ) { posc = p_numubar_numubar; }
        else if( util::IsNuE(m)        ) { posc = p_nue_nue;         }
        else if( util::IsNuEBar(m)     ) { posc = p_nuebar_nuebar;   }

        else if( util::IsNuMuToNuE(m)  ) { posc = p_numu_nue;        }
        else if( util::IsNuMuToNuTau(m)) { posc = p_numu_nutau;      }
        else if( util::IsNuEToNuMu(m)  ) { posc = p_nue_numu;        }
        else if( util::IsNuEToNuTau(m) ) { posc = p_nue_nutau;       }

        else if( util::IsNuMuBarToNuEBar(m)  ) { posc = p_numubar_nuebar;        }
        else if( util::IsNuMuBarToNuTauBar(m)) { posc = p_numubar_nutaubar;      }
        else if( util::IsNuEBarToNuMuBar(m)  ) { posc = p_nuebar_numubar;        }
        else if( util::IsNuEBarToNuTauBar(m) ) { posc = p_nuebar_nutaubar;       }
      }

      for(int it2 = 0; it2 < n_true2_bins; it2++) {
        bin .bin4 = it2;
        sbin.bin4 = it2;
        
        for(int izone = 0; izone < kNMaxBinZones; izone++) {
          bool is_null = fMCTNullOb[imode][izone];
          if(is_null) {continue;}
          const int n_reco1_bins = util::NumErecoBins(fSample,izone);
          const int n_reco2_bins = util::NumYrecoBins(fSample,izone);
          
            for(int ir1 = 0; ir1 < n_reco1_bins; ir1++) {
              bin.bin1 = ir1;
              for(int ir2 = 0; ir2 < n_reco2_bins; ir2++) {
                bin.bin2 = ir2;
                
                double & val = fMCTFinOb[imode][izone]->GetEntryRef(bin);
		val *= posc;

              }//ir2
            }//ir1
        }
        
        if(update_mct_sb) {
          const int      n_reco1_bins_sb      = util::NumErecoBinsSb (fSample);
          const int      n_reco2_bins_sb      = util::NumYrecoBinsSb (fSample);
          //~ const double * reco1_bin_edges_sb   = util::ErecoBinEdgesSb(fSample);
          //~ const double * reco2_bin_edges_sb   = util::YrecoBinEdgesSb(fSample);
          bool is_null = fMCTNullSb[imode];
          if(is_null) {continue;}
          
          
          for(int irsb1 = 0; irsb1 < n_reco1_bins_sb; irsb1++) {
            sbin.bin1 = irsb1;
            for(int irsb2 = 0; irsb2 < n_reco2_bins_sb; irsb2++) {
              sbin.bin2 = irsb2;
              
              double & val = fMCTFinSb[imode]->GetEntryRef(sbin);
              val *= posc;
              
            }//irsb2
          }//irsb1
        }//update_mct_sb
        
      }//it2
    }//it1
  }//imode

}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::UpdatePDFs(Option_t * option)
{
  bool update_mct_sb = false;
  if(option) {
    string opt = option;
    if(opt.find("+SB") != string::npos) {
      update_mct_sb = true;
    }
  }

  //
  // Use the `fin' MC templates to fill in the PDF components
  // Integrate over true kinematical quantities (eg Etrue), but do not integrate
  // over true reaction modes just yet
  //

  int isample = fArrIdx->SampleIdx(fBeam,fSample);

  const int n_enu_true_bins  = util::NumEtrueBins  (fSample);
  const int n_y_reco_bins_sb = util::NumYrecoBinsSb(fSample);

  for(int imode = 0; imode < kNReacModes; imode++) {
    ReacMode_t m = kReactionModes[isample][imode];
    if(m == kmUndefined) continue;
    
    const int n_q2_true_bins   = util::NumQ2trueBins (fSample,m);

    for(int izone = 0; izone < kNMaxBinZones; izone++) {
      bool is_null = fMCTNullOb[imode][izone];
      if(is_null) continue;
      const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
      const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
      for(int ier=0; ier < n_enu_reco_bins; ier++) {
        for(int iyr=0; iyr < n_y_reco_bins; iyr++) {
          double sum = 0.;
          for(int iet=0; iet < n_enu_true_bins; iet++) {
            for(int iqt=0; iqt < n_q2_true_bins; iqt++) {
              sum += fMCTFinOb[imode][izone]->GetEntry(ier,iyr,iet,iqt);
            }//iqt
          }//iet
          fPDFCompOb[imode][izone]->SetEntry(sum, ier, iyr);
        }//iyr
      }//ier
    }//izone

    if(update_mct_sb) {
      bool is_null = fMCTNullSb[imode];
      if(is_null) continue;
      for(int ier=0; ier < kNErecoBinsSb; ier++) {
        for(int iyr=0; iyr < n_y_reco_bins_sb; iyr++) {
          double sum = 0.;
          for(int iet=0; iet < n_enu_true_bins; iet++) {
            for(int iqt=0; iqt < n_q2_true_bins; iqt++) {
              sum += fMCTFinSb[imode]->GetEntry(ier,iyr,iet,iqt);
            }//iqt
          }//iet
          fPDFCompSb[imode]->SetEntry(sum, ier, iyr);
        }//iyr
      }//ier
    }//update_mct_sb?

  }//imode

  //
  // Now integrate the above-computed PDF components over the true reaction mode
  // and calculate the total PDF
  //

  for(int izone = 0; izone < kNMaxBinZones; izone++) {
    const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
    const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
    for(int ier=0; ier < n_enu_reco_bins; ier++) {
      for(int iyr=0; iyr < n_y_reco_bins; iyr++) {
        double sum = 0.;
        for(int imode = 0; imode < kNReacModes; imode++) {
          ReacMode_t m = kReactionModes[isample][imode];
          if(m == kmUndefined) continue;
          bool is_null = fMCTNullOb[imode][izone];
          if(is_null) continue;
          sum += fPDFCompOb[imode][izone]->GetEntry(ier, iyr);
        }//imode
        fPDFTotOb[izone]->SetEntry(sum, ier, iyr);
      }//iyr
    }//ier
  }//izone

  if(update_mct_sb) {
    for(int ier=0; ier < kNErecoBinsSb; ier++) {
      for(int iyr=0; iyr < n_y_reco_bins_sb; iyr++) {
        double sum = 0.;
        for(int imode = 0; imode < kNReacModes; imode++) {
          ReacMode_t m = kReactionModes[isample][imode];
          if(m == kmUndefined) continue;
          bool is_null = fMCTNullSb[imode];
          if(is_null) continue;
          sum += fPDFCompSb[imode]->GetEntry(ier, iyr);
        }//imode
        fPDFTotSb->SetEntry(sum, ier, iyr);
      }//iyr
    }//ier
  }//update_mct_sb?

}
//________________________________________________________________________________________
valor::PhysParamList valor::GenericSingleSampleFitModel::OneSigmaErrors(Option_t * /*opt*/)
{
  PhysParamList ppl;

  // -----------------------------------  
  // TODO
  // remove
  //ppl.SetName("NDModel_Errors");
  //fNuFlux->CopyOneSigmaErrorsTo(ppl);
  //fNuDet ->CopyOneSigmaErrorsTo(ppl);
  //fNuInt ->CopyOneSigmaErrorsTo(ppl);
  //--------------------------------------- 

  ppl.SetName("PreFitErrors");
  fSyst->CopyOneSigmaErrorsTo(ppl);
  return ppl;
}
//________________________________________________________________________________________
void valor::GenericSingleSampleFitModel::UpdateObservableBinningFromSimple(Option_t * /*opt*/)
{
  LOG("GenericSingleSampleFitModel",pNOTICE)<<"Updating observable binning from simple: "<<fName;
  const int n_true1_bins            = util::NumEtrueBins   (fSample);
  //~ const double * true1_bin_edges    = util::EtrueBinEdges  (fSample);
  
  const int n_reco1_bins_sb         = util::NumErecoBinsSb (fSample);
  const double * reco1_bin_edges_sb = util::ErecoBinEdgesSb(fSample);
  const int n_reco2_bins_sb         = util::NumYrecoBinsSb (fSample);
  const double * reco2_bin_edges_sb = util::YrecoBinEdgesSb(fSample);

  int isample = fArrIdx->SampleIdx(fBeam,fSample);

  for(int imode = 0; imode < kNReacModes; imode++) {
    ReacMode_t m = kReactionModes[isample][imode];
    if(m == kmUndefined) continue;
    
    for (int izone = 0 ; izone < kNMaxBinZones ; izone++) {
      // Zero it out, since we'll just be adding to elements
      fMCTFinOb[imode][izone]->SetAll(0.);
    }
    
    const int n_true2_bins         = util::NumQ2trueBins (fSample,m);
    //~ const double * true2_bin_edges = util::Q2trueBinEdges(fSample,m);
    
    // We'll use two nested sets of loops - first over the simple bins, then over the optimised bins to get their content
    VALORArrayBin sb_bin;
    for(int irsb1 = 0; irsb1 < n_reco1_bins_sb; irsb1++) {
      sb_bin.bin1 = irsb1;
      for(int irsb2 = 0; irsb2 < n_reco2_bins_sb; irsb2++) {
        sb_bin.bin2 = irsb2;
        
        // Now loop over the observable bins
        VALORArrayBin ob_bin;
        
        for (int izone = 0 ; izone < kNMaxBinZones ; izone++) {
          
          const int n_reco1_bins            = util::NumErecoBins   (fSample,izone);
          const double * reco1_bin_edges    = util::ErecoBinEdges  (fSample,izone);
          
          const int n_reco2_bins            = util::NumYrecoBins   (fSample,izone);
          const double * reco2_bin_edges    = util::YrecoBinEdges  (fSample,izone);
  
          for(int it1 = 0; it1 < n_true1_bins; it1++) {
            ob_bin.bin3 = it1;
            sb_bin.bin3 = it1;
            for(int it2 = 0; it2 < n_true2_bins; it2++) {
              ob_bin.bin4 = it2;
              sb_bin.bin4 = it2;
              for(int ir1 = 0; ir1 < n_reco1_bins; ir1++) {
                ob_bin.bin1 = ir1;
                for(int ir2 = 0; ir2 < n_reco2_bins; ir2++) {
                  ob_bin.bin2 = ir2;
                  
                  // Fraction of the observable bin held in the simple bin.
                  double frac_sb_1 = util::FractionOfBinContained(
                    reco1_bin_edges_sb[irsb1],reco1_bin_edges_sb[irsb1+1],
                    reco1_bin_edges   [ir1]  ,reco1_bin_edges   [ir1  +1]);
                  double frac_sb_2 = util::FractionOfBinContained(
                    reco2_bin_edges_sb[irsb2],reco2_bin_edges_sb[irsb2+1],
                    reco2_bin_edges   [ir2]  ,reco2_bin_edges   [ir2  +1]);
                  
                  double frac_sb = frac_sb_1 * frac_sb_2;
                  if (frac_sb < conv::kASmallNum) {
                    continue;
                  }
                  double sb_content = fMCTFinSb[imode]->GetEntry(sb_bin);
                  double content_to_add = frac_sb * sb_content;
                  fMCTFinOb[imode][izone]->AddToEntry(content_to_add,ob_bin);
                }//ir2
              }//ir1
            }//it2
          }//it1
        }//izone
      }//isrsb2
    }//irsb1
  } //imode
  return;
}
//________________________________________________________________________________________
