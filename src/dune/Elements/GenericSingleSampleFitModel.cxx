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
#include <TPRegexp.h>

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
#include "valor/Oscillation/NuOsc3Flavour.h"
#include "valor/Oscillation/SimpleOsc.h"
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

#define OH_GOD_FIX_ME -999

//________________________________________________________________________________________
GenericSingleSampleFitModel::GenericSingleSampleFitModel() :
  SingleSampleFitModelABC(),
  fParamIsAppliedTo(),
  fParamHasSplines(),
  fBinning(NULL),
  fSystematics(NULL),
  fOwnerOfSystematics(false)
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
  if (fDetector == conv::kdUndefined ) { LOG("SingleSampleFitModelABC",pFATAL) << "Bad Detector"  << fDetector ; util::Die(-1); }
  if (fBeam     == conv::kbUndefined ) { LOG("SingleSampleFitModelABC",pFATAL) << "Bad Beam"      << fBeam     ; util::Die(-1); }
  if (fSample   == conv::ksUndefined ) { LOG("SingleSampleFitModelABC",pFATAL) << "Bad Sample"    << fSample   ; util::Die(-1); }
  if (fKSp      == conv::kspUndefined) { LOG("SingleSampleFitModelABC",pFATAL) << "Bad KineSpace" << fKSp      ; util::Die(-1); }
  
  int isample = fArrIdx->SampleIdx(fBeam,fSample);
  if (isample == -1) {
    LOG("GenericSingleSampleFitModel",pFATAL)
      << "Sample not included in analysis build: "<<util::AsString(fBeam)<<" "<<util::AsString(fSample);
    util::Die(-1);
  }

  fName = util::nm::MdlName(fDetector, fBeam, fSample, fKSp);
  
  TString ts_opt(opt);
  bool force_use_dst    = ts_opt.Contains("forcedst");
  bool skip_spline_read = ts_opt.Contains("nosplines");
  bool skip_mc_read     = ts_opt.Contains("nomc");
#ifdef SPLINE_WEIGHTS_ARE_ONE
  skip_spline_read = true;
#endif
  
  
  // Set up the initial XML reader
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
  
  
  // Get binning file name, potentially from option string
  string binning_file;
  TPRegexp binning_re("(?<=binning\\=)[^ ,]+");
  TObjArray * matches = binning_re.MatchS(opt);
  if(matches->GetEntries()==1) {
    TObjString * binning_objstring = dynamic_cast<TObjString*>(matches->At(0));
    if (binning_objstring) {
      binning_file = binning_objstring->String().Data();
    }
    LOG("GenericSingleSampleFitModel",pNOTICE) << fName<< ": Reading binning from "<<binning_file;
  }
  else {
    binning_file = util::XML2String(xml,root_node,"default_binning");
    LOG("GenericSingleSampleFitModel",pNOTICE) << fName<< ": No sample-specific binning in options \""<<opt<<"\" , falling back to default: "<<binning_file;
  }
  delete matches;
  
  if (fBinning) {delete fBinning;}
  fBinning = new SingleSampleKineBinning(fDetector,fBeam,fSample);
  fBinning->Read(binning_file);

  this->Book();
  this->Zero();
  
  exit(-1);
  

  //------------------------
  // TODO
  // fSystematics = new CompoundCorrelatedSystematics; 
  // fSystematics->Read(xml,root_node);
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
    TTree * mc_dst = util::XML2TTree (xml,root_node,node_name);
    if (!mc_dst) {
      LOG("GenericSingleSampleFitModel",pFATAL) << "Failed to read DST tree";
      util::Die(-1); return false;
    }
    this->FillFromDST(mc_dst);
    delete mc_dst;
  } 
  else {
    LOG("GenericSingleSampleFitModel",pINFO) << "Using stored VALOR MC templates";
    string template_tag = util::XML2String(xml,root_node,"mc/template/tag");
    TFile * template_file = util::XML2TFile(xml,root_node,"mc/template");

    this->FillFromTemplateFile(template_file,template_tag,fPOT);
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
                  fRFPtr[imode]->SetEntry(spl_as_int,ir1,ir2,it1,it2,ip);
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

#ifndef __VALOR_FMWK_PENALTY_ONLY__
  this->FluctuateMCStat(opt);   // `tun' MC templates --> `tun' MC templates (NOTE: if important effect, will need to add a new type of templates
  //this->ApplySystematics(opt);  // `tun' MC templates --> `sys' MC templates
  this->ApplyPhysics(opt);      // `sys' MC templates --> `fin' MC templates
  this->ApplyOscProb(opt);      // `fin' MC templates --> `fin' MC templates
  this->UpdatePDFs(opt);        // `fin' MC templates --> p.d.f
#endif //__VALOR_FMWK_PENALTY_ONLY__

  LOG("GenericSingleSampleFitModel",pINFO) << "Done generating predictions";

  return true;
}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::RandomizeSystematics(Option_t * options)
{
  fSystematics->Tweak(false,NULL,options);
}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::RandomizeSystematics(bool (* should_randomize)(conv::PhysParamId_t), Option_t * options)
{
  fSystematics->Tweak(false,0,should_randomize,options);
}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::RandomizeSystematics(std::map<valor::conv::PhysParamId_t, bool> should_randomize, Option_t * options)
{
  fSystematics->Tweak(false,0,should_randomize,options);
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
  if (fSystematics) {
    fSystematics->SetCurrentValue(syst,twkdial);
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

  fSystematics -> CopyTweaksTo(list);

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
  fSystematics -> Tweak(true, 0);
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

  if (fSystematics) {
    fSystematics ->UpdateFrom(fp);
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
  
  int izone = 0; //DEBUG!

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

  int isample = fArrIdx->SampleIdx(fBeam,fSample);

  //
  // Write out MC templates (VALORArray format)
  //

  if(opt.find("mct_vf") != string::npos) {

    for(int imode = 0; imode < kNReacModes; imode++) {
      ReacMode_t m = kReactionModes[isample][imode];
      if(m == kmUndefined) continue;

      if(fMCTNullOb[imode]) continue;
      fMCTNomOb [imode] -> SetName( TString::Format("%s_%s_%s", tag, "mctnom_ob_vf", fName.c_str() ).Data() );
      fMCTTunOb [imode] -> SetName( TString::Format("%s_%s_%s", tag, "mcttun_ob_vf", fName.c_str() ).Data() );
      fMCTSysOb [imode] -> SetName( TString::Format("%s_%s_%s", tag, "mctsys_ob_vf", fName.c_str() ).Data() );
      fMCTFinOb [imode] -> SetName( TString::Format("%s_%s_%s", tag, "mctfin_ob_vf", fName.c_str() ).Data() );
      LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << fMCTNomOb [imode]->GetName();
      LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << fMCTTunOb [imode]->GetName();
      LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << fMCTSysOb [imode]->GetName();
      LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << fMCTFinOb [imode]->GetName();
      array -> Add ( fMCTNomOb [imode] ); 
      array -> Add ( fMCTTunOb [imode] ); 
      array -> Add ( fMCTSysOb [imode] ); 
      array -> Add ( fMCTFinOb [imode] );

      if(opt.find("+SB") != string::npos) {
        if(fMCTNullSb[imode]) continue;
        fMCTNomSb [imode] -> SetName( TString::Format("%s_%s_%s", tag, "mctnom_sb_vf", fName.c_str()).Data() );
        fMCTTunSb [imode] -> SetName( TString::Format("%s_%s_%s", tag, "mcttun_sb_vf", fName.c_str()).Data() );
        fMCTSysSb [imode] -> SetName( TString::Format("%s_%s_%s", tag, "mctsys_sb_vf", fName.c_str()).Data() );
        fMCTFinSb [imode] -> SetName( TString::Format("%s_%s_%s", tag, "mctfin_sb_vf", fName.c_str()).Data() );
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

      if(fMCTNullOb[imode]) continue;
      
      // in VALORArray format
      if (opt.find("pdfc_vf") != string::npos) {
        fPDFCompOb [imode]->SetName(TString::Format("%s_%s_%s",tag,"pdfc_ob_vf",fName.c_str()).Data());
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << fPDFCompOb[imode]->GetName();
        array->Add(fPDFCompOb[imode]);
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
        TString hname = TString::Format("%s_%s_%s",tag, "pdfc_ob_rf",fName.c_str());
        TString htitle = "VALOR/DUNE ND (Ereco,yreco) PDF component = f(beam,sample,mode,zone)";
        TH2D * h2 = new TH2D(hname.Data(),htitle.Data(),
            n_enu_reco_bins, enu_reco_bins, n_y_reco_bins, y_reco_bins);
        // fill from corresponding VALOR array
        for(int ier = 0; ier < n_enu_reco_bins; ier++) {
          for(int iy = 0; iy < n_y_reco_bins; iy++) {
            double val = fPDFCompOb[imode]->GetEntry(ier,iy);
            h2->SetBinContent(ier+1,iy+1,val);
          }//iy
        }//ier
        // add tp object array and clean-up
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << h2->GetName();
        array->Add(h2); 
        // delete h2; ???? // MEMORY LEAK?
      }

      if(opt.find("+SB") != string::npos) {
        if(fMCTNullSb[imode]) continue;
        // in VALORArray format
        if (opt.find("pdfc_vf") != string::npos) {
          fPDFCompSb[imode]->SetName(TString::Format("%s_%s_%s",tag,"pdfc_sb_vf",fName.c_str()));
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
          TString hname = TString::Format("%s_%s_%s",tag, "pdfc_sb_rf",fName.c_str());
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
      // in VALORArray format
      if (opt.find("pdft_vf") != string::npos) {
        fPDFTotOb->SetName(TString::Format("%s_%s_%s",tag,"pdft_ob_vf",fName.c_str()).Data());
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << fPDFTotOb->GetName();
        array->Add(fPDFTotOb);
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
        const double * enu_reco_bins = util::ErecoBinEdges(fSample,izone);
        const double * y_reco_bins   = util::YrecoBinEdges(fSample,izone);
        // book histogram
        TString hname = TString::Format("%s_%s_%s",tag, "pdft_ob_rf",fName.c_str()); 
        TString htitle = "VALOR/DUNE ND (Ereco,yreco) PDF = f(beam,sample,zone)";
        TH2D * h2 = new TH2D(hname.Data(), htitle.Data(),
            n_enu_reco_bins, enu_reco_bins, n_y_reco_bins, y_reco_bins);
        // fill from corresponding VALOR array
        for(int ier = 0; ier < n_enu_reco_bins; ier++) {
          for(int iy = 0; iy < n_y_reco_bins; iy++) {
            double val = fPDFTotOb->GetEntry(ier,iy);
            h2->SetBinContent(ier+1,iy+1,val);
          }//iy
        }//ier
        // add to object array and clean-up
        LOG("GenericSingleSampleFitModel", pDEBUG) << "Adding: " << h2->GetName();
        array->Add(h2); 
        // delete h2; ???? // MEMORY LEAK?
      }

    if(opt.find("+SB") != string::npos) {
      // in VALORArray format
      if (opt.find("pdft_vf") != string::npos) {
        fPDFTotSb->SetName(TString::Format("%s_%s_%s",tag,"pdft_sb_vf",fName.c_str()));
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
        TString hname = TString::Format("%s_%s_%s",tag, "pdft_sb_rf",fName.c_str());
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
      
      { // Trivial block to keep some variables in scope
        // get binning
        const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
        const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
        const double * enu_reco_bins = util::ErecoBinEdges(fSample,izone);
        const double * y_reco_bins   = util::YrecoBinEdges(fSample,izone);
        // create slices of the PDF components (function of Ereco, for given yreco bin)
        TString hname_ob = TString::Format("%s_%s_%s",tag, "pdfcs_ob_rf",fName.c_str()) ;
        TString htitle_ob = "VALOR/DUNE ND PDF component: Ereco spectrum = f(beam,sample,mode,zone)";
        TH1D * htot = new TH1D(hname_ob.Data(),htitle_ob.Data(),n_enu_reco_bins, enu_reco_bins);
        htot->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
        htot->GetYaxis()->SetTitle(TString::Format("Number of events /bin /%lg POT", fPOT).Data());
        for(int iy = 0; iy < n_y_reco_bins; iy++) {
          TString hname_s  = TString::Format("%s_%s_%s_y%d",tag, "pdfcs_ob_rf",fName.c_str(),iy);
          TString htitle_s = TString::Format(
            "VALOR/DUNE ND PDF component slice: Ereco spectrum = f(beam,sample,mode,zone) for y in [%f,%f]", 
            y_reco_bins[iy],y_reco_bins[iy+1]);
          TH1D * h = new TH1D(hname_s.Data(),htitle_s.Data(),
              n_enu_reco_bins, enu_reco_bins);
          h->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
          h->GetYaxis()->SetTitle(TString::Format("Number of events /bin /%lg POT", fPOT).Data());
          for(int ier = 0; ier < n_enu_reco_bins; ier++) {
            double val = fPDFCompOb[imode]->GetEntry(ier,iy);
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
      }

      if(opt.find("+SB") != string::npos) {
        // create slices of the PDF components (function of Ereco, for given yreco bin)
        const int n_y_reco_bins_sb = util::NumYrecoBinsSb(fSample);
        const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(fSample);
        TString hname = TString::Format( "%s_%s_%s",tag, "pdfcs_sb_rf",fName.c_str());
        TString htitle = "VALOR/DUNE ND PDF component: Ereco spectrum = f(beam,sample,mode)";
        TH1D * htot = new TH1D(hname.Data(), htitle.Data(), kNErecoBinsSb, kErecoBinEdgesSb);
        htot->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
        htot->GetYaxis()->SetTitle(TString::Format("Number of events /bin /%lg POT", fPOT).Data());
        for(int iy = 0; iy < n_y_reco_bins_sb; iy++) {
          TString hname_s = TString::Format("%s_%s_%s_y%d",tag, "pdfcs_sb_rf",fName.c_str(),iy);
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
    
    { // block for variable scope
      // get binning
      const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
      const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
      const double * enu_reco_bins = util::ErecoBinEdges(fSample,izone);
      const double * y_reco_bins   = util::YrecoBinEdges(fSample,izone);
      // create slices of the total PDF (function of Ereco, for given yreco bin)
      TString hname  = TString::Format("%s_%s_%s",tag, "pdfts_ob_rf",fName.c_str());
      TString htitle = TString::Format("VALOR/DUNE ND PDF: Ereco spectrum = f(beam,sample,zone)");
      TH1D * htot = new TH1D(hname.Data(), htitle.Data(),
        n_enu_reco_bins, enu_reco_bins);
      htot->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
      htot->GetYaxis()->SetTitle(TString::Format("Number of events /bin /%lg POT", fPOT));
      for(int iy = 0; iy < n_y_reco_bins; iy++) {
        TString hname_s = TString::Format("%s_%s_%s_y%d",tag, "pdfts_ob_rf",fName.c_str(),iy);
        TString htitle_s = TString::Format(
          "VALOR/DUNE ND PDF slice: Ereco spectrum = f(beam,sample,zone) for y in [%f,%f]",
          y_reco_bins[iy],y_reco_bins[iy+1]);
        TH1D * h = new TH1D(hname_s.Data(), htitle_s.Data(),
            n_enu_reco_bins, enu_reco_bins);
        h->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
        h->GetYaxis()->SetTitle(TString::Format("Number of events /bin /%lg POT", fPOT).Data());
        for(int ier = 0; ier < n_enu_reco_bins; ier++) {
          double val = fPDFTotOb->GetEntry(ier,iy);
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
    }

    if(opt.find("+SB") != string::npos) {
      // create slices of the total PDF (function of Ereco, for given yreco bin)
      const int n_y_reco_bins_sb = util::NumYrecoBinsSb(fSample);
      const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(fSample);
      TH1D * htot = new TH1D("htot", "htot", kNErecoBinsSb, kErecoBinEdgesSb);
      htot->SetName(TString::Format("%s_%s_%s",tag, "pdfts_sb_rf",fName.c_str()).Data() );
      htot->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
      htot->GetYaxis()->SetTitle(TString::Format("Number of events /bin /%lg POT", fPOT).Data());
      for(int iy = 0; iy < n_y_reco_bins_sb; iy++) {
        TString hname = TString::Format("%s_%s_%s_y%d",tag, "pdfts_sb_rf",fName.c_str(),iy);
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
  double Sp = (fSystematics-> ChisqPenalty());
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

    // MC templates
    fMCTNullOb [imode] = true;
    fMCTNomOb  [imode] = 0;
    fMCTTunOb  [imode] = 0;
    fMCTSysOb  [imode] = 0;
    fMCTFinOb  [imode] = 0;
    fMCStatOb  [imode] = 0;
    // Splines
    fRFPtr     [imode] = 0;
    // PDF
    fPDFCompOb [imode] = 0;
    if(imode == 0) {
      fPDFTotOb      = 0;
      fPDFTotNullOb  = true;
    }
    
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

  fSystematics = 0;
}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::Book(void)
{
  LOG("GenericSingleSampleFitModel",pDEBUG) << "Booking "<<util::AsString(fBeam)<<" "<<util::AsString(fSample);
  
  const KBCubHcmbMondrian  * reco_ob = fBinning->RecoOptBinning();
  const KBCubHcmbEdge2Edge * reco_sb = fBinning->RecoSmpBinning();
  
  int isample = fArrIdx->SampleIdx(fBeam,fSample);

  for(int imode = 0; imode < kNReacModes; imode++) {
    ReacMode_t m = kReactionModes[isample][imode];
    if(m == kmUndefined) continue;
    
    const KBCubHcmbEdge2Edge * true_sb = fBinning->TrueSmpBinning(m);

    const int n_reco_bins_ob = reco_ob->NBins();
    const int n_reco_bins_sb = reco_sb->NBins();
    const int n_true_bins    = true_sb->NBins();

    LOG("GenericSingleSampleFitModel",pDEBUG) 
      << "Booking MC template (simple binning) for " 
      << "beam: "     << util::AsString(fBeam) 
      << ", sample: " << util::AsString(fSample)
      << ", mode: "   << util::AsString(m); 

    // >> MC templates (simple binning)
    // (Note order of variables: reco first, true later)
    fMCTNullSb[imode] = false;
    fMCTNomSb [imode] = new VALORArray(n_reco_bins_sb, n_true_bins);
    fMCTTunSb [imode] = new VALORArray(n_reco_bins_sb, n_true_bins);
    fMCTSysSb [imode] = new VALORArray(n_reco_bins_sb, n_true_bins);
    fMCTFinSb [imode] = new VALORArray(n_reco_bins_sb, n_true_bins);
    fMCStatSb [imode] = new VALORArray(n_reco_bins_sb, n_true_bins);

    // >> PDF component
    fPDFCompSb[imode] = 
      new VALORArray(n_reco_bins_sb);           
    // >> PDF total
    // should get here for at least one imode value
    if(fPDFTotNullSb) {              
      LOG("GenericSingleSampleFitModel",pDEBUG) 
        << "Booking PDF (total / simple binning) for " 
        << "beam: "     << util::AsString(fBeam) 
        << ", sample: " << util::AsString(fSample);
      fPDFTotNullSb = false;
      fPDFTotSb     = new VALORArray(n_reco_bins_sb); 
    }
    
    // >> MC templates 
    // (Note order of variables: reco first, true later)
    fMCTNullOb[imode] = false;
    fMCTNomOb [imode] = new VALORArray(n_reco_bins_ob, n_true_bins);
    fMCTTunOb [imode] = new VALORArray(n_reco_bins_ob, n_true_bins);
    fMCTSysOb [imode] = new VALORArray(n_reco_bins_ob, n_true_bins);
    fMCTFinOb [imode] = new VALORArray(n_reco_bins_ob, n_true_bins);
    fMCStatOb [imode] = new VALORArray(n_reco_bins_ob, n_true_bins);
      
    // Spline library
    fRFPtr [imode] = 
      new VALORArrayL(n_reco_bins_ob, n_true_bins, kNFitParams);

    // >> PDF component
    fPDFCompOb[imode] = 
      new VALORArray(n_reco_bins_ob);           
    // >> PDF total
    // should get here for at least one imode value
    if(fPDFTotNullOb) {              
      LOG("GenericSingleSampleFitModel",pDEBUG) 
        << "Booking PDF (total) for " 
        << "beam: "     << util::AsString(fBeam) 
        << ", sample: " << util::AsString(fSample);

      fPDFTotNullOb  = false;
      fPDFTotOb      = new VALORArray(n_reco_bins_ob);
    }

    // Fill the ParamIsAppliedTo array
    for(int ip = 0; ip < conv::kNFitParams; ip++) {
      PhysParamId_t p = kFitParam[ip];
      if(p == kPhypUndefined) continue;
      fParamIsAppliedTo[imode][ip] = util::ParamIsAppliedTo(fBeam,fSample,fDetector,m,p);
    }
  }//imode
  
  // Write will initialise the names of the arrays - useful for debugging in read
  TObjArray tmp_array;
  this->Write(&tmp_array,"valor","mct_vf+SB");
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

    if(!fMCTNullOb[imode]) {
      fMCTNullOb[imode] = true;
      // MC templates
      if ( fMCTNomOb [imode] ) { delete fMCTNomOb [imode]; fMCTNomOb [imode] = 0; }
      if ( fMCTTunOb [imode] ) { delete fMCTTunOb [imode]; fMCTTunOb [imode] = 0; }
      if ( fMCTSysOb [imode] ) { delete fMCTSysOb [imode]; fMCTSysOb [imode] = 0; }
      if ( fMCTFinOb [imode] ) { delete fMCTFinOb [imode]; fMCTFinOb [imode] = 0; }
      if ( fMCStatOb [imode] ) { delete fMCStatOb [imode]; fMCStatOb [imode] = 0; }
      if ( fRFPtr    [imode] ) { delete fRFPtr    [imode]; fRFPtr    [imode] = 0; }
      
      // PDF components
      if(fPDFCompOb[imode]) { delete fPDFCompOb[imode]; fPDFCompOb[imode] = 0; }
    }
    if(!fPDFTotNullOb) {
      fPDFTotNullOb = true;
      if(fPDFTotOb) { delete fPDFTotOb; fPDFTotOb = 0; }
    }

  }//imode
  
  if (fRFL)  { delete fRFL ; fRFL  = 0; }
  if (fBinning) { delete fBinning ; fBinning = 0; }
  
  if (fSystematics && fOwnerOfSystematics) { delete fSystematics; fSystematics = 0; }
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

    if(!fMCTNullOb[imode]) {
      fMCTNomOb [imode] -> SetAll(0.);
      fMCTTunOb [imode] -> SetAll(0.); 
      fMCTSysOb [imode] -> SetAll(0.);
      fMCTFinOb [imode] -> SetAll(0.);
      fMCStatOb [imode] -> SetAll(0.);
      fPDFCompOb[imode] -> SetAll(0.);
    }
    if(!fPDFTotNullOb) {
      fPDFTotOb -> SetAll(0.);
    }

  }//imode
}
//________________________________________________________________________________________
//________________________________________________________________________________________
void GenericSingleSampleFitModel::FillFromDST(TTree * t)
{
  
#ifdef __VALOR_FMWK_PENALTY_ONLY__
  return;
#endif

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
  
  const KBCubHcmbMondrian  * reco_ob = fBinning->RecoOptBinning();
  const KBCubHcmbEdge2Edge * reco_sb = fBinning->RecoSmpBinning();
  
  for(Long_t iev = 0; iev < nev; iev++) 
  {
    t->GetEntry(iev);

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
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
      LOG("GenericSingleSampleFitModel",pDEBUG) 
        << "Ignoring MC event: " << iev 
        << " (sample ID: " << s << " "<< util::AsString(s) 
        << " not matching one used for configuring model: " 
        << fSample <<" "<<util::AsString(fSample) << ")";
#endif
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

    bool is_null = fMCTNullOb[imode];
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
    
    // Exposure for assumed data - Weight MC templates to that exposure
    double data_pot = fPOT;

    // Calculate POT weight (assumed data exposure) / (generated MC exposure)
    double pot_wght = wght_pot * data_pot * tree_weight;
    
    if(fFiducialMass > 0) {
      pot_wght = pot_wght*fFiducialMass;
    }
    
    // Find the appropriate bins
    
    // MUST BE UPDATED WITH OTHER KINESPACES
    std::vector<double> reco_vars;
    reco_vars.push_back(enu_reco);
    reco_vars.push_back(y_reco);
    std::vector<double> true_vars;
    true_vars.push_back(enu_true);
    true_vars.push_back(Q2_true);
    
    const KBCubHcmbEdge2Edge * true_sb = fBinning->TrueSmpBinning(m);
    int true_bin    = true_sb->FindLinearizedBin(true_vars);
    int reco_bin_sb = reco_sb->FindLinearizedBin(reco_vars);
    int reco_bin_ob = reco_ob->FindBin(reco_vars);

    LOG("GenericSingleSampleFitModel",pDEBUG) 
      << "Inserting to MC teplates --> MC event #" << iev 
      << "\n sample      = " << s        << " (" << util::AsString(s) << ")"
      << "\n imode       = " << imode    << " (" << util::AsString(m) << ")"
      << "\n wght        = " << wght 
      << "\n pot_wght    = " << pot_wght
      << "\n true_bin    = " << true_bin
      << "\n reco_bin_ob = " << reco_bin_ob
      << "\n reco_bin_sb = " << reco_bin_sb;
      
    double this_entry = wght;
    
    this_entry *= pot_wght;
    this_entry *= wght_smear;

    // Add `nom' array entry (and init `tun', `sys' and `fin' arrays = `nom')
    double curr_wght = fMCTNomOb[imode]->GetEntry(reco_bin_ob, true_bin);
    curr_wght += this_entry;
    fMCTNomOb [imode]->SetEntry(curr_wght, reco_bin_ob, true_bin);
    fMCTTunOb [imode]->SetEntry(curr_wght, reco_bin_ob, true_bin);
    fMCTSysOb [imode]->SetEntry(curr_wght, reco_bin_ob, true_bin);
    fMCTFinOb [imode]->SetEntry(curr_wght, reco_bin_ob, true_bin);     
    fMCStatOb [imode]->SetEntry(        1, reco_bin_ob, true_bin);

    double curr_wght_sb = fMCTNomSb[imode]->GetEntry(reco_bin_sb, true_bin);
    curr_wght_sb += this_entry;
    fMCTNomSb [imode]->SetEntry(curr_wght_sb, reco_bin_sb, true_bin);
    fMCTTunSb [imode]->SetEntry(curr_wght_sb, reco_bin_sb, true_bin);
    fMCTSysSb [imode]->SetEntry(curr_wght_sb, reco_bin_sb, true_bin);
    fMCTFinSb [imode]->SetEntry(curr_wght_sb, reco_bin_sb, true_bin);
    fMCStatSb [imode]->SetEntry(           1, reco_bin_sb, true_bin);
  }//iev 
}
//________________________________________________________________________________________

bool GenericSingleSampleFitModel::FillFromTemplateFile (TFile * f, string tag, double desired_POT)
{
  bool success = true;

  int isample = fArrIdx->SampleIdx(fBeam,fSample);
  BeamConf_t b = fBeam;
  Sample_t   s = fSample;
  
  if (desired_POT > 0) {
    LOG("GenericSingleSampleFitModel",pNOTICE) << "Scaling POT template by "<<desired_POT * 1E-21 << " to get template for "<<desired_POT<<" POT.";
  }

  for(int imode = 0; imode < kNReacModes; imode++) {
    ReacMode_t m = kReactionModes[isample][imode];
    if(m == kmUndefined) continue;
    TString obj_name_ob = TString::Format("%s_%s_%s", tag.c_str(), "mctnom_ob_vf", fName.c_str());
    VALORArray * arr_ob = dynamic_cast<VALORArray*>(f->Get(obj_name_ob.Data()));
    if (arr_ob && arr_ob->GetSize()) {
      assert(arr_ob->GetDimensionSizes() == fMCTNomOb[imode]->GetDimensionSizes());
      assert(arr_ob->GetDimensionSizes() == fMCTTunOb[imode]->GetDimensionSizes());
      assert(arr_ob->GetDimensionSizes() == fMCTSysOb[imode]->GetDimensionSizes());
      assert(arr_ob->GetDimensionSizes() == fMCTFinOb[imode]->GetDimensionSizes());
      assert(arr_ob->GetDimensionSizes() == fMCStatOb[imode]->GetDimensionSizes());
      if (desired_POT > 0) {
        arr_ob->Scale(desired_POT * 1E-21);
      }
      fMCTNomOb [imode]->CopyFrom(*arr_ob);
      fMCTTunOb [imode]->CopyFrom(*arr_ob);
      fMCTSysOb [imode]->CopyFrom(*arr_ob);
      fMCTFinOb [imode]->CopyFrom(*arr_ob);
      fMCStatOb [imode]->CopyFrom(*arr_ob);
      fMCStatOb [imode]->SetAll(1.);  
      delete arr_ob;
    }
    else {
      success = false;
      LOG("GenericSingleSampleFitModel",pERROR) << "Failed to read template "<<obj_name_ob;
    }
    
    TString obj_name_sb = TString::Format("%s_%s_%s", tag.c_str(), "mctnom_sb_vf", fName.c_str());
    VALORArray * arr_sb = dynamic_cast<VALORArray*>(f->Get(obj_name_sb.Data()));
    if (arr_sb && arr_sb->GetSize()) {
      assert(arr_sb->GetDimensionSizes() == fMCTNomSb[imode]->GetDimensionSizes());
      assert(arr_sb->GetDimensionSizes() == fMCTTunSb[imode]->GetDimensionSizes());
      assert(arr_sb->GetDimensionSizes() == fMCTSysSb[imode]->GetDimensionSizes());
      assert(arr_sb->GetDimensionSizes() == fMCTFinSb[imode]->GetDimensionSizes());
      assert(arr_sb->GetDimensionSizes() == fMCStatSb[imode]->GetDimensionSizes());
      if (desired_POT > 0) {
          arr_sb->Scale(desired_POT * 1E-21);
      }
      fMCTNomSb [imode]->CopyFrom(*arr_sb);
      fMCTTunSb [imode]->CopyFrom(*arr_sb);
      fMCTSysSb [imode]->CopyFrom(*arr_sb);
      fMCTFinSb [imode]->CopyFrom(*arr_sb);
      fMCStatSb [imode]->CopyFrom(*arr_sb);
      fMCStatSb [imode]->SetAll(1.);
      delete arr_sb;
    }
    else {
      success = false;
      LOG("GenericSingleSampleFitModel",pERROR) << "Failed to read template "<<obj_name_sb;
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
  
  const KBCubHcmbMondrian  * reco_ob = fBinning->RecoOptBinning();
  const KBCubHcmbEdge2Edge * reco_sb = fBinning->RecoSmpBinning();

  int isample = fArrIdx->SampleIdx(fBeam,fSample);

  const int n_reco_bins_ob  = reco_ob->NBins();
  const int n_reco_bins_sb  = reco_sb->NBins();
  
  for(int imode = 0; imode < kNReacModes; imode++) {

    ReacMode_t m = kReactionModes[isample][imode];
    if(m == kmUndefined) continue;
    const KBCubHcmbEdge2Edge * true_sb = fBinning->TrueSmpBinning(m);
    
    const int n_true_bins  = true_sb->NBins();

    // Updating only the templates using the optimized binning
    if(!update_mct_sb) {
      bool is_null = fMCTNullOb[imode];
      if(is_null) continue;
      for(int itrue = 0; itrue < n_true_bins; itrue++) {
        for(int ireco = 0; ier < n_reco_bins_ob; ier++) {
          double val  = fMCTTunOb[imode]->GetEntry(ireco,itrue);
          double nmc  = fMCStatOb[imode]->GetEntry(ireco,itrue);
          // Fluctuate MC statistics and get the tweak factor
          double nmcf = rnd->RndToyMCstat().Poisson(nmc); 
          //double twk  = (nmc > 0) ? nmcf/nmc ? 1;
          double twk  = (nmc > 0) ? nmcf/nmc : 1;
          // Apply the tweak factor in the template, obviously a small effect for 
          // large MC statistics. Again noting that this is not the statistical error
          // for the current exposure. That one will be applied later in toy-MC generation.
          double valf = val * twk; 
          fMCTTunOb[imode]->SetEntry(valf,ireco,itrue);
        }//ireco: reco bins
      }//itrue: true bins
    }

    // Updating both the templates in optimized and simple binning schemes.
    // They can not be fluctuated independently because the represent the exact same quantity
    // in two binning schemes. The sum of bin contents (for specific bin ranges) of templates
    // in the simple scheme should equal the contents of specific bins of templates in the optimized scheme...
    else {
      
      // Reset
      fMCTTunOb[imode]->setAll(0.);

      // Start by fluctuation the templates using the simple binning.
      // Then map each simple bin to an optimized bin and add to its contents. 
      for(int itrue = 0; itrue < n_true_bins; itrue++) {
        for(int ireco = 0; ireco < n_reco_bins; ireco++) {
          double val  = fMCTTunSb[imode]->GetEntry(ireco,itrue);
          double nmc  = fMCStatSb[imode]->GetEntry(ireco,itrue);
          double nmcf = rnd->RndToyMCstat().Poisson(nmc); 
          //double twk  = (nmc > 0) ? nmcf/nmc ? 1;
          double twk  = (nmc > 0) ? nmcf/nmc : 1;
          double valf = val * twk; 
          fMCTTunSb[imode]->SetEntry(valf,ireco,itrue);
          
          std::vector<double> reco_vars = reco_sb->BinCentre(ireco);
          int ireco_ob = reco_ob->FindLinearizedBin(reco_vars);
          double valf_ob = fMCTTunOb[imode]->GetEntry(ireco_ob,itrue);
          valf_ob += valf;
          fMCTTunOb[imode]->SetEntry(valf_ob,ireco_ob,itrue);
        }//ireco: Ereco bins
      }//itrue: Etrue bins

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
  
  const KBCubHcmbMondrian  * reco_ob = fBinning->RecoOptBinning();
  const KBCubHcmbEdge2Edge * reco_sb = fBinning->RecoSmpBinning();
  
  const int n_reco_bins_sb = reco_sb->NBins();
  const int n_reco_bins_ob = reco_ob->NBins();

  const int isample = fArrIdx->SampleIdx(fBeam,fSample);

  for(int imode = 0; imode < kNReacModes; imode++) {
    ReacMode_t m = kReactionModes[isample][imode];
    if(m == kmUndefined) continue;
    
    const KBCubHcmbEdge2Edge * true_sb = fBinning->TrueSmpBinning(m);
    
    const int n_true_bins_sb = true_sb->NBins();

#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
    LOG("GenericSingleSampleFitModel",pDEBUG) 
      << "Handing templates for: " 
      << util::AsString(fBeam) << ", " << util::AsString(fSample) << ", " << util::AsString(m);

    LOG("GenericSingleSampleFitModel",pDEBUG) 
      << "Initializing `fin' templates to the `sys' ones";
#endif
    bool is_null = fMCTNullOb[imode];
    if(is_null) {continue;}
    
    // copy sys -> fin MC templates
    fMCTFinOb[imode]->CopyDataOnlyFrom(*fMCTSysOb[imode]);
    
    for(int ip = 0; ip < kNFitParams; ip++) {
      PhysParamId_t p = kFitParam[ip];
      if (p == kPhypUndefined          ) {continue;}
      if (util::IsOscParam(p)          ) {continue;} 
      if (!fParamIsAppliedTo[imode][ip]) {continue;}
      
      if (!fPhysHypothesis.Contains(p)) {
        LOG("GenericSingleSampleFitModel",pINFO) << "Skipping parameter not defined in PhysHypothesis "<<util::AsString(p);
        continue;
      }
      
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
        VALORArrayBin bin;
        VALORArrayBin splbin;
        splbin.bin3 = ip;
        for(int itrue = 0; itrue < n_true_bins_sb; itrue++) {
          bin.bin2 = itrue;
          splbin.bin2 = itrue;
          for(int ireco = 0; ireco < n_reco_bins_ob; ireco++) {
            bin.bin1 = ireco;
            splbin.bin1 = ireco;
            double response = 1;
            const util::Interpolator * spl = reinterpret_cast<util::Interpolator*>(fRFPtr[imode]->GetEntry(splbin));
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
            double & val = fMCTFinOb[imode]->GetEntryRef(bin);
            val *= response;
          }//ireco
        }//itrue
#endif //SPLINE_WEIGHTS_ARE_ONE
      } // has_splines
      else if (has_kinematic_dependence) {
        LOG("GenericSingleSampleFitModel",pWARN) << "WARNING, STEVE DID NOT FINISH UPDATING THIS";
        //~ VALORArrayBin bin;
        //~ f = TMath::Max(0.,f);
        //~ bool tweaked = TMath::Abs(f-1) > kASmallNum;
        //~ if(!tweaked) continue;
        
        //~ // MUST BE MADE MORE INTELLIGENT FOR KINESPACE
        //~ const double true1_min  = kFitParamEtrueRange [ip][0];
        //~ const double true1_max  = kFitParamEtrueRange [ip][1];     
        //~ const double true2_min  = kFitParamQ2trueRange[ip][0];
        //~ const double true2_max  = kFitParamQ2trueRange[ip][1];     
        //~ int i_true1_min = TMath::BinarySearch((Long_t)n_true1_bins, true1_bin_edges, true1_min+kASmallNum);
        //~ int i_true1_max = TMath::BinarySearch((Long_t)n_true1_bins, true1_bin_edges, true1_max-kASmallNum);
        //~ int i_true2_min = TMath::BinarySearch((Long_t)n_true2_bins, true2_bin_edges, true2_min+kASmallNum);
        //~ int i_true2_max = TMath::BinarySearch((Long_t)n_true2_bins, true2_bin_edges, true2_max-kASmallNum);
//~ #ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
        //~ LOG("GenericSingleSampleFitModel",pINFO) 
          //~ << fName <<": "
          //~ << "Applying parameter: " << util::AsString(p) << " with value = " << f 
          //~ << " in Etrue bin range: ["   << true1_min << ", " << true1_max << "]"
          //~ << " and Q2true bin range: [" << true2_min << ", " << true2_max << "]";
//~ #endif
        //~ for(int it1 = i_true1_min; it1 <= i_true1_max; it1++) {
          //~ bin.bin3 = it1;
          //~ for(int it2 = i_true2_min; it2 <= i_true2_max; it2++) {
            //~ bin.bin4 = it2;
            //~ for(int ir1 = 0; ir1 < n_reco1_bins; ir1++) {
              //~ bin.bin1 = ir1;
              //~ for(int ir2 = 0; ir2 < n_reco2_bins; ir2++) {
                //~ bin.bin2 = ir2;
                //~ double & val = fMCTFinOb[imode]->GetEntryRef(bin);
                //~ val *= f;
//~ #ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
                //~ LOG("GenericSingleSampleFitModel",pDEBUG) 
                  //~ << "MCT[" << imode << "] = " 
                  //~ << val/f << " --> " << val;
//~ #endif
            //~ }//ireco: reco bins
        //~ }//itrue: true bins
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
        fMCTFinOb[imode]->Scale(noEt);
      } // No spline, no kin dependence
    } //iparam
    
    if(update_mct_sb) {
      if (!imode) {
        LOG("GenericSingleSampleFitModel",pNOTICE) << "Updating simple binning templates for "<<fName<<".";
      }
      
      if(fMCTNullSb[imode]) {continue;}
      fMCTFinSb[imode]->CopyDataOnlyFrom(*(fMCTSysSb[imode]));
      
      for(int ip = 0; ip < kNFitParams; ip++) {
        PhysParamId_t p = kFitParam[ip];
        if (p == kPhypUndefined          ) {continue;}
        if (util::IsOscParam(p)          ) {continue;}
        if (!fParamIsAppliedTo[imode][ip]) {continue;}
        
        if (!fPhysHypothesis.Contains(p)) {
          LOG("GenericSingleSampleFitModel",pINFO) << "Skipping parameter not defined in PhysHypothesis "<<util::AsString(p);
          continue;
        }
        
        
        double f = fPhysHypothesis.CurrValue(p);
        
        bool has_splines = fParamHasSplines[ip];
        bool has_kinematic_dependence = kFitParamTrueKinematicDependence[ip];
        
        // first apply spline parameters
        if (has_splines) {
#ifndef SPLINE_WEIGHTS_ARE_ONE
          LOG("GenericSingleSampleFitModel",pWARN) << "WARNING, STEVE DID NOT FINISH UPDATING THIS";
          //~ //if (TMath::Abs(f-1) < kASmallNum ) {continue;} // SHOULD USE A MORE INTELLIGENT CENTRE
          //~ VALORArrayBin sbin;
          //~ util::KinematicPoint kp;
          //~ for(int itrue = 0; itrue < n_true_bins_sb; itrue++) {
            //~ sbin.bin2 = itrue;
            //~ kp.true1 = (true1_bin_edges[itrue]+true1_bin_edges[itrue+1])/2;
            //~ for(int ireco_sb = 0; ireco_sb < n_reco1_bins_sb; ireco_sb++) {
              //~ sbin.bin1 = ireco_sb;
              //~ kp.reco1 = (reco1_bin_edges_sb[ireco_sb]+reco1_bin_edges_sb[ireco_sb+1])/2;
              //~ util::KinematicBin kb = fRFL->GetBin(kp,m);
              //~ const util::Interpolator * spl = fRFL->GetSpline(m,p,kb);
              //~ if (spl==util::DuneRFL::kNoSplineRequired) {
                //~ LOG("GenericSingleSampleFitModel",pERROR)
                  //~ <<"Got no spline required for simple bin expecting spline."
                  //~ <<util::AsString(p)<<", "<<util::AsString(fBeam)<<", "
                  //~ <<util::AsString(fSample)<<","<<util::AsString(m);
              //~ }
              //~ double response = spl->EvalWithLimits(f);
              //~ if (response<0) {
                //~ LOG("GenericSingleSampleFitModel",pINFO)
                 //~ <<"Negative response from spline (SB) "//<<spl->GetName()
                 //~ <<" evaluated at "<<f<<" with result "<<response
                 //~ <<". Using 0 instead.";
                //~ response = 0;
              //~ }
              //~ double & val = fMCTFinSb[imode]->GetEntryRef(sbin);
              //~ val *= response;
            //~ }//ireco
          //~ }//itrue
#endif
        }//has splines
        
        else if (has_kinematic_dependence) {
          LOG("GenericSingleSampleFitModel",pWARN) << "WARNING, STEVE DID NOT FINISH UPDATING THIS";
          //~ f = TMath::Max(0.,f);
          //~ bool tweaked = TMath::Abs(f-1) > kASmallNum;
          //~ if(!tweaked) continue;
          
          //~ // MUST BE MADE SMARTER WITH KINESPACE
          //~ const double true1_min = kFitParamEtrueRange[ip][0];
          //~ const double true1_max = kFitParamEtrueRange[ip][1];     
          //~ int itrue1_min = TMath::BinarySearch((Long_t)n_true1_bins, true1_bin_edges, true1_min+kASmallNum);
          //~ int itrue1_max = TMath::BinarySearch((Long_t)n_true1_bins, true1_bin_edges, true1_max-kASmallNum);
          //~ const double true2_min = kFitParamQ2trueRange[ip][0];
          //~ const double true2_max = kFitParamQ2trueRange[ip][1];
          //~ int itrue2_min = TMath::BinarySearch((Long_t)n_true2_bins, true2_bin_edges, true2_min+kASmallNum);
          //~ int itrue2_max = TMath::BinarySearch((Long_t)n_true2_bins, true2_bin_edges, true2_max-kASmallNum);

          //~ for(int it1 = itrue1_min; it1 <= itrue1_max; it1++) {
            //~ bin.bin3 = it1;
            //~ for(int it2 = itrue2_min; it2 <= itrue2_max; it2++) {
              //~ bin.bin4 = it2;
              //~ for(int irsb1 = 0; irsb1 < kNErecoBinsSb; irsb1++) {
                //~ bin.bin1 = irsb1;
                //~ for(int irsb2 = 0; irsb2 < n_reco2_bins_sb; irsb2++) {
                  //~ bin.bin2 = irsb2;
                  //~ double & val = fMCTFinSb[imode]->GetEntryRef(bin);
                  //~ val *= f;
                //~ }//ir2: yreco bins
              //~ }//ir1: Ereco bins
            //~ }//it2: Q2 bins
          //~ }//it1: Etrue bins
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
  for(int imode = 0; imode < kNReacModes; imode++) {
    for(int ip = 0; ip < conv::kNuis000; ip++) {
      PhysParamId_t p = (PhysParamId_t) ip;
      if(fPhysHypothesis.Contains(p)) {
        apply_osc_prob = true;
      }
    }
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
          fMCTFinOb[imode]->SetAll(0.);
        }
        if (update_mct_sb) {fMCTFinSb[imode]->SetAll(0.);}
      }
    }
    return;
  }
  
  PhysHypothesis_t hypid = fPhysHypothesis.Hypothesis();
  // Variables for the sterile oscillations if we need them, since they don't come in an object
  double sinsq2thee = -1, sinsq2thmumu = -1, dm41sq = -1;
  
  // Set 3 flavour osc parameters
  if (hypid == kHypOsc3F) {
    
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
  }
  else if (hypid == kHypOscSterileEff) {
    sinsq2thee   = fPhysHypothesis.CurrValue(kPhypMixingEE);
    sinsq2thmumu = fPhysHypothesis.CurrValue(kPhypMixingMuMu);
    dm41sq       = fPhysHypothesis.CurrValue(kPhypDm41sq);
  }
    
  
  double p_numu_numu       = -1;
  double p_numu_nue        = -1;
  double p_numu_nutau      = -1;
  double p_numubar_numubar = -1;
  double p_numubar_nuebar  = -1;
  double p_numubar_nutaubar= -1;
  double p_nue_nue         = -1;
  double p_nue_numu        = -1;
  double p_nue_nutau       = -1;
  double p_nuebar_nuebar   = -1;
  double p_nuebar_numubar  = -1;
  double p_nuebar_nutaubar = -1;
  
  const KBCubHcmbMondrian  * reco_ob = fBinning->RecoOptBinning();
  const KBCubHcmbEdge2Edge * reco_sb = fBinning->RecoSmpBinning();
  
  const int n_reco_bins_ob = reco_ob->NBins();
  const int n_reco_bins_sb = reco_sb->NBins();

  for(int imode = 0; imode < kNReacModes; imode++) {
    ReacMode_t m = kReactionModes[isample][imode];
    if(m == kmUndefined) continue;
    
    //check if beam+sample+mode should be applied oscillation probabilities                                                
    if(!util::OscProbIsAppliedTo(fDetector,fBeam,fSample,m)) {continue; }
    

    const KBCubHcmbEdge2Edge * true_sb = fBinning->TrueSmpBinning(m);
    const int n_true_bins_sb = true_sb->NBins();
    
    VALORArrayBin bin;
    VALORArrayBin sbin;

    for(int itrue = 0; itrue < n_true_bins_sb; itrue++) {
      bin .bin2 = itrue;
      sbin.bin2 = itrue;
      //get the true energy to calculate osc prob 
      double Etrue = true_sb->BinCentre(itrue,conv::kvEtrue);
      
      if (hypid == kHypOsc3F) {
        double p_osc    [3][3];
        double p_osc_bar[3][3];
        fNuOsc3Flavour.CalcMatterOscProbAll(false, Etrue, p_osc    );
        fNuOsc3Flavour.CalcMatterOscProbAll(true , Etrue, p_osc_bar);
        p_numu_numu       = p_osc    [1][1];
        p_numu_nue        = p_osc    [1][0];
        p_numu_nutau      = p_osc    [1][2];
        p_numubar_numubar = p_osc_bar[1][1];
        p_numubar_nuebar  = p_osc_bar[1][0];
        p_numubar_nutaubar= p_osc_bar[1][2];
        p_nue_nue         = p_osc    [0][0];
        p_nue_numu        = p_osc    [0][1];
        p_nue_nutau       = p_osc    [0][2];
        p_nuebar_nuebar   = p_osc_bar[0][0];
        p_nuebar_numubar  = p_osc_bar[0][1];
        p_nuebar_nutaubar = p_osc_bar[0][2];
      
      }
      else if (hypid == kHypOscSterileEff) {
        double baseline = util::Baseline(fBeam,fDetector);
        double lOverE = baseline / Etrue;
        p_numu_numu       = util::Calculate2FSterileOsc(conv::kPdgNuMu   , conv::kPdgNuMu   , lOverE, sinsq2thee, sinsq2thmumu, dm41sq);
        p_numu_nue        = util::Calculate2FSterileOsc(conv::kPdgNuMu   , conv::kPdgNuE    , lOverE, sinsq2thee, sinsq2thmumu, dm41sq);
        p_numu_nutau      = 0.;
        p_numubar_numubar = util::Calculate2FSterileOsc(conv::kPdgNuMuBar, conv::kPdgNuMuBar, lOverE, sinsq2thee, sinsq2thmumu, dm41sq);
        p_numubar_nuebar  = util::Calculate2FSterileOsc(conv::kPdgNuMuBar, conv::kPdgNuEBar , lOverE, sinsq2thee, sinsq2thmumu, dm41sq);
        p_numubar_nutaubar= 0.;
        p_nue_nue         = util::Calculate2FSterileOsc(conv::kPdgNuE    , conv::kPdgNuE    , lOverE, sinsq2thee, sinsq2thmumu, dm41sq);
        p_nue_numu        = util::Calculate2FSterileOsc(conv::kPdgNuE    , conv::kPdgNuMu   , lOverE, sinsq2thee, sinsq2thmumu, dm41sq);
        p_nue_nutau       = 0;
        p_nuebar_nuebar   = util::Calculate2FSterileOsc(conv::kPdgNuEBar , conv::kPdgNuEBar , lOverE, sinsq2thee, sinsq2thmumu, dm41sq);
        p_nuebar_numubar  = util::Calculate2FSterileOsc(conv::kPdgNuEBar , conv::kPdgNuMuBar, lOverE, sinsq2thee, sinsq2thmumu, dm41sq);
        p_nuebar_nutaubar = 0;;
      }
        

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
      
      if(fMCTNullOb[imode]) {continue;}
      
      for(int ireco = 0; ireco < n_reco_bins_ob; ireco++) {
        bin.bin1 = ireco;
        double & val = fMCTFinOb[imode]->GetEntryRef(bin);
        val *= posc;
      }//ireco
        
      if(update_mct_sb) {
        if(fMCTNullSb[imode]) {continue;}
        for(int ireco_sb = 0; ireco_sb < n_reco_bins_sb; ireco_sb++) {
          sbin.bin1 = ireco_sb;
          double & val = fMCTFinSb[imode]->GetEntryRef(sbin);
          val *= posc;
        }//ireco_sb
      }//update_mct_sb
    }//itrue
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

  const int isample = fArrIdx->SampleIdx(fBeam,fSample);
  
  const KBCubHcmbMondrian  * reco_ob = fBinning->RecoOptBinning();
  const KBCubHcmbEdge2Edge * reco_sb = fBinning->RecoSmpBinning();

  const int n_reco_bins_ob  = reco_ob->NBins();
  const int n_reco_bins_sb  = reco_sb->NBins();

  for(int imode = 0; imode < kNReacModes; imode++) {
    ReacMode_t m = kReactionModes[isample][imode];
    if(m == kmUndefined) continue;
    
    const KBCubHcmbEdge2Edge * true_sb = fBinning->TrueSmpBinning(m);
    const int n_true_bins_sb = true_sb->NBins();
    
    if(fMCTNullOb[imode]) continue;
    
    for(int ireco=0; ireco < n_reco_bins_ob; ireco++) {
      double sum = 0.;
      for(int itrue=0; itrue < n_true_bins_sb; itrue++) {
        sum += fMCTFinOb[imode]->GetEntry(ireco,itrue);
      }//itrue
      fPDFCompOb[imode]->SetEntry(sum, ireco);
    }//ireco

    if(update_mct_sb) {
      bool is_null = fMCTNullSb[imode];
      if(is_null) continue;
      for(int ireco=0; ireco < n_reco_bins_sb; ireco++) {
        double sum = 0.;
        for(int itrue=0; itrue < n_true_bins_sb; itrue++) {
          sum += fMCTFinSb[imode]->GetEntry(ireco,itrue);
        }//itrue
        fPDFCompSb[imode]->SetEntry(sum, ireco);
      }//ireco
    }//update_mct_sb?

  }//imode

  //
  // Now integrate the above-computed PDF components over the true reaction mode
  // and calculate the total PDF
  //
    for(int ireco=0; ireco < n_reco_bins_ob; ireco++) {
        double sum = 0.;
        for(int imode = 0; imode < kNReacModes; imode++) {
          ReacMode_t m = kReactionModes[isample][imode];
          if(m == kmUndefined) continue;
          if(fMCTNullOb[imode]) continue;
          sum += fPDFCompOb[imode]->GetEntry(ireco);
        }//imode
        fPDFTotOb->SetEntry(sum, ireco);
    }//ireco

  if(update_mct_sb) {
    for(int ireco=0; ireco < n_reco_bins_sb; ireco++) {
      double sum = 0.;
      for(int imode = 0; imode < kNReacModes; imode++) {
        ReacMode_t m = kReactionModes[isample][imode];
        if(m == kmUndefined) continue;
        if(fMCTNullOb[imode]) continue;
        sum += fPDFCompSb[imode]->GetEntry(ireco);
      }//imode
      fPDFTotSb->SetEntry(sum, ireco);
    }//ireco
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
  fSystematics->CopyOneSigmaErrorsTo(ppl);
  return ppl;
}
//________________________________________________________________________________________
void valor::GenericSingleSampleFitModel::UpdateObservableBinningFromSimple(Option_t * /*opt*/)
{
  LOG("GenericSingleSampleFitModel",pNOTICE)<<"Updating observable binning from simple: "<<fName;
  
  
  const int isample = fArrIdx->SampleIdx(fBeam,fSample);
  
  const KBCubHcmbMondrian  * reco_ob = fBinning->RecoOptBinning();
  const KBCubHcmbEdge2Edge * reco_sb = fBinning->RecoSmpBinning();

  const int n_reco_bins_ob  = reco_ob->NBins();
  const int n_reco_bins_sb  = reco_sb->NBins();

  // OLD
  const int n_true1_bins            = util::NumEtrueBins   (fSample);
  const int n_reco1_bins_sb         = util::NumErecoBinsSb (fSample);
  const double * reco1_bin_edges_sb = util::ErecoBinEdgesSb(fSample);
  const int n_reco2_bins_sb         = util::NumYrecoBinsSb (fSample);
  const double * reco2_bin_edges_sb = util::YrecoBinEdgesSb(fSample);
  const int izone = 0;

  for(int imode = 0; imode < kNReacModes; imode++) {
    LOG("GenericSingleSampleFitModel",pWARN) << "WARNING, STEVE DID NOT FINISH UPDATING THIS";
    return;
    
    ReacMode_t m = kReactionModes[isample][imode];
    if(m == kmUndefined) continue;
    
    const KBCubHcmbEdge2Edge * true_sb = fBinning->TrueSmpBinning(m);
    const int n_true_bins_sb = true_sb->NBins();

    // OLD
    const int n_true2_bins         = util::NumQ2trueBins (fSample,m);
    
    // Zero it out, since we'll just be adding to elements
    fMCTFinOb[imode]->SetAll(0.);
    
    // We'll use two nested sets of loops - first over the simple bins, then over the optimised bins to get their content
    VALORArrayBin sb_bin;
    for(int irsb1 = 0; irsb1 < OH_GOD_FIX_ME; irsb1++) {
      sb_bin.bin1 = irsb1;
      for(int irsb2 = 0; irsb2 < OH_GOD_FIX_ME; irsb2++) {
        sb_bin.bin2 = irsb2;
        
        // Now loop over the observable bins
        VALORArrayBin ob_bin;
          
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
                  fMCTFinOb[imode]->AddToEntry(content_to_add,ob_bin);
                }//ir2
              }//ir1
            }//it2
          }//it1
      }//isrsb2
    }//irsb1
  } //imode
  return;
}
//________________________________________________________________________________________
CorrelatedSystematics * GenericSingleSampleFitModel::GetSystematics(Option_t * /*opt*/)
{
  return fSystematics;
}
//________________________________________________________________________________________
const CorrelatedSystematics * GenericSingleSampleFitModel::GetSystematics(Option_t * /*opt*/) const
{
  return fSystematics;
}
//________________________________________________________________________________________
void GenericSingleSampleFitModel::SetSystConf(CorrelatedSystematics * syst, Option_t * opt)
{
  TString ts(opt);
  if (ts.Contains("copy") ) {
    fSystematics = dynamic_cast<CorrelatedSystematics *>(syst->Clone());
    fOwnerOfSystematics = true;
  }
  else {
    fSystematics = syst;
    fOwnerOfSystematics = ts.Contains("adopt");
  }
  
  return;
}
//________________________________________________________________________________________
