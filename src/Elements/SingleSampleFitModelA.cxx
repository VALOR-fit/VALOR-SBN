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
#include <TH1D.h>
#include <TH2D.h>

//fmwk
#include "Conventions/Constants.h"
#include "Conventions/PhysHypothesisId.h"
#include "Conventions/PhysParamId.h"
#include "Conventions/NuOscMixParam.h"
#include "Conventions/NuOscDmsqScheme.h"
#include "Conventions/Opt.h"
#include "Conventions/PDG.h"
#include "Utilities/Rnd.h"
#include "Utilities/Env.h"
#include "Utilities/UtlNumStat.h"
#include "Utilities/UtlStyle.h"
#include "Utilities/UtlSystem.h"
#include "Utilities/UtlXML.h"
#include "Messenger/Messenger.h"
//dune
#include "Conventions/DuneBuild.h"
#include "Conventions/ReacMode.h"
#include "Conventions/BeamConf.h"
#include "Conventions/FitParamApply.h"
#include "Elements/SingleSampleFitModelA.h"
// --------------------------------------
// abstract: should come either from conventions or as configurations
#include "SDFit/NuFlux.h"
#include "SDFit/NuInt.h"
#include "SDFit/NuDet.h"
// --------------------------------------

using std::endl;

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
SingleSampleFitModelA::SingleSampleFitModelA(
  conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s) :
FitModelABC()
{
  this->Init();

  fDetector = d;
  fBeam     = b;
  fSample   = s;

  assert(fDetector != kdUndefined);
  assert(fBeam     != kbUndefined);
  assert(fSample   != ksUndefined);

  this->Book();
  this->Zero();
}
//________________________________________________________________________________________
SingleSampleFitModelA::~SingleSampleFitModelA() 
{
  this->Clean();
}
//________________________________________________________________________________________
//
//
// FitModelABC interface implementation:
//
//________________________________________________________________________________________
string SingleSampleFitModelA::Name(void)
{
  return "DUNEND";
}
//________________________________________________________________________________________
bool SingleSampleFitModelA::Read(string file, Option_t * opt)
{
  this->Zero();
  
  TString ts_opt(opt);
  bool force_use_dst = ts_opt.Contains("forcedst");

  LOG("SingleSampleFitModelA", pNOTICE) << "Reading configuration from XML file [" << file << "]";

  // Parse the input XML configuration file
  TXMLEngine* xml = new TXMLEngine;   
  XMLDocPointer_t xmldoc = xml->ParseFile(file.c_str());
  if (xmldoc==0) {
    LOG("SingleSampleFitModelA",pERROR) << "Can not parse input XML file [" << file << "]";
    delete xml;
    util::Die(1); return false;
  }
  XMLNodePointer_t root_node = xml->DocGetRootElement(xmldoc);
  
  // Read the neutrino flux model info
  fNuFlux = new valor::NuFlux;
  fNuFlux->Read(xml,root_node);
  // Read the neutrino interaction model info
  fNuInt = new valor::NuInt;
  fNuInt->Read(xml,root_node);
  // Read the neutrino detector model info
  fNuDet = new valor::NuDet;
  fNuDet->Read(xml,root_node);

  // Get the near detector fiducial mass
  string name = "nd/fiducial_mass";
  fNDFiducialMass = util::XML2Dbl(xml,root_node,name);
  LOG("SingleSampleFitModelA",pINFO)
    << "ND fiducial mass = " << fNDFiducialMass*1000 << " tonnes";

  // Get assumed exposure for each beam configuration
  {
     string node_name = "data/exposure/" + util::AsString(fBeam, "lowercase");
     fPOT = util::XML2Dbl(xml,root_node,node_name);
     LOG("SingleSampleFitModelA",pINFO) 
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
  fUseMCDST = util::XML2Bool(xml,root_node,"mc/using_dst_format") | force_use_dst;
  if(fUseMCDST) {
    LOG("SingleSampleFitModelA",pINFO) << "Filling in VALOR MC templates using VALOR DSTs";
    string node_name = "mc/dst/" + util::AsString(fBeam, "lowercase");
    fMCDST = util::XML2TTree (xml,root_node,node_name);
    assert(fMCDST);
    this->FillFromDST(fMCDST);
  } 
  else {
    LOG("SingleSampleFitModelA",pINFO) << "Using stored VALOR MC templates";
    string template_tag = util::XML2String(xml,root_node,"mc/template/tag");
    TFile * template_file = util::XML2TFile(xml,root_node,"mc/template");
    
    this->FillFromTemplateFile(template_file,template_tag);
    template_file->Close();
    delete template_file;
  }
  
  // At the point the nominal MC templates are filled-in.
  // Apply any fixed tuning here, not on an event by event basis.
  // It is the tuned templates that be the starting point in the Generate() method.
  this->ApplyTuning();

  // Release memory
  xml->FreeDoc(xmldoc);
  delete xml;

  LOG("SingleSampleFitModelA",pNOTICE) << "Done configuring DUNE/ND model... \n\n";

  return true;
}
//________________________________________________________________________________________
bool SingleSampleFitModelA::Generate(const PhysHypothesis & ph, Option_t * opt)
{
// input opt: 
// - Leave null for the fit
// - Use "+SB" to generate finely-binned predictions too (for plotting or toy-MC generation)

//  LOG("SingleSampleFitModelA",pDEBUG)  
//     << "Input physics hypothesis before copying to private data member: " << ph;

  fPhysHypothesis.Copy(ph);
  //PhysHypothesis_t hyp = fPhysHypothesis.Hypothesis();

  LOG("SingleSampleFitModelA",pINFO)  
     << "Generating model predictions for the input hypothesis: " 
     << fPhysHypothesis;

  this->FluctuateMCStat(opt);   // `tun' MC templates --> `tun' MC templates (NOTE: if important effect, will need to add a new type of templates
//this->ApplySystematics(opt);  // `tun' MC templates --> `sys' MC templates
  this->ApplyPhysics(opt);      // `sys' MC templates --> `fin' MC templates
  this->UpdatePDFs(opt);        // `fin' MC templates --> p.d.f

  LOG("SingleSampleFitModelA",pINFO) << "Done generating predictions";

  return true;
}
//________________________________________________________________________________________
void SingleSampleFitModelA::RandomizeSystematics(Option_t * options)
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
  
  if (randomize_flux) {fNuFlux->Tweak(false,0);}
  if (randomize_int ) {fNuInt ->Tweak(false,0);}
  if (randomize_det ) {fNuDet ->Tweak(false,0);}
  
}
//________________________________________________________________________________________
void SingleSampleFitModelA::TweakSystematic(
  string syst_name, double twkdial, Option_t * opt)
{
  PhysParamId_t p = util::PhysParamFromString(syst_name);
  this->TweakSystematic(p,twkdial,opt);
  return;
}
//________________________________________________________________________________________
void SingleSampleFitModelA::TweakSystematic(
  PhysParamId_t syst, double twkdial, Option_t * /*opt*/)
{
  if (util::IsNuFluxRelated(syst)) {
    //~ fNuFlux->Tweak();
  }
  if (util::IsNuIntRelated(syst)) {
    //~ fNuInt->Tweak();
  }
  if (util::IsNuDetRelated(syst)) {
    //~ fNuDet->Tweak();
  }
}
//________________________________________________________________________________________
PhysParamList SingleSampleFitModelA::Tweaks(void)
{
  PhysParamList list;
  
  fNuFlux -> CopyTweaksTo(list);
  fNuInt  -> CopyTweaksTo(list);
  fNuDet  -> CopyTweaksTo(list);
  
  return list;
}
//________________________________________________________________________________________
void SingleSampleFitModelA::ResetSystematics(Option_t * /*opt*/)
{
  fNuFlux -> Tweak(true, 0);
  fNuInt  -> Tweak(true, 0);
  fNuDet  -> Tweak(true, 0);
}
//________________________________________________________________________________________
void SingleSampleFitModelA::PrintSystematics(ostream & stream, Option_t * /*opt*/) const
{
  stream << endl;
}
//________________________________________________________________________________________
bool SingleSampleFitModelA::Generate (const FitParamList & fp, Option_t * opt)
{
//  LOG("SingleSampleFitModelA",pDEBUG)  
//     << "Input fit parameter list before converting to a physics hypothesis: " << fp;

  fNuFlux->UpdateFrom(fp);
  fNuDet ->UpdateFrom(fp);
  fNuInt ->UpdateFrom(fp);
  
  // extract the values of params driving the oscillation, decoherence or decay model
  PhysHypothesis ph(fp);

  // call the main Generate() method
  return this->Generate(ph, opt);
}
//________________________________________________________________________________________
bool SingleSampleFitModelA::Write(TObjArray * array, const char * tag, Option_t * write_opt)
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

  LOG("SingleSampleFitModelA", pINFO)  << "Writing results to input object array...";
  LOG("SingleSampleFitModelA", pDEBUG) << "tag = " << tag << ", write option = " << write_opt;

  string opt = (write_opt) ? write_opt : "pdft_vf";
  if(opt.find("all") != string::npos) {
    opt = "mct_vf + pdfc_vf + pdfc_rf + pdft_vf + pdft_rf + pdfcs_rf + pdfts_rf +SB";
    LOG("SingleSampleFitModelA", pDEBUG) << "Write option replaced with = " << opt;
  }

  if(!array) {
     LOG("SingleSampleFitModelA",pERROR) << "Null input object array.";
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
             const char * name = Form("%s_%s_%s_z%d", 
                util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), util::AsString(m).c_str(), izone);
             fMCTNomOb [imode][izone] -> SetName( Form("%s_%s_%s", tag, "mctnom_ob_vf", name) );
             fMCTTunOb [imode][izone] -> SetName( Form("%s_%s_%s", tag, "mcttun_ob_vf", name) );
             fMCTSysOb [imode][izone] -> SetName( Form("%s_%s_%s", tag, "mctsys_ob_vf", name) );
             fMCTFinOb [imode][izone] -> SetName( Form("%s_%s_%s", tag, "mctfin_ob_vf", name) );
             LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << fMCTNomOb [imode][izone]->GetName();
             LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << fMCTTunOb [imode][izone]->GetName();
             LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << fMCTSysOb [imode][izone]->GetName();
             LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << fMCTFinOb [imode][izone]->GetName();
             array -> Add ( fMCTNomOb [imode][izone] ); 
             array -> Add ( fMCTTunOb [imode][izone] ); 
             array -> Add ( fMCTSysOb [imode][izone] ); 
             array -> Add ( fMCTFinOb [imode][izone] );
          }//izone

          if(opt.find("+SB") != string::npos) {
             if(fMCTNullSb[imode]) continue;
             const char * name = Form("%s_%s_%s", 
                util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), util::AsString(m).c_str());
             fMCTNomSb [imode] -> SetName( Form("%s_%s_%s", tag, "mctnom_sb_vf", name) );
             fMCTTunSb [imode] -> SetName( Form("%s_%s_%s", tag, "mcttun_sb_vf", name) );
             fMCTSysSb [imode] -> SetName( Form("%s_%s_%s", tag, "mctsys_sb_vf", name) );
             fMCTFinSb [imode] -> SetName( Form("%s_%s_%s", tag, "mctfin_sb_vf", name) );
             LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << fMCTNomSb [imode]->GetName();
             LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << fMCTTunSb [imode]->GetName();
             LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << fMCTSysSb [imode]->GetName();
             LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << fMCTFinSb [imode]->GetName();
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
             const char * name = Form("%s_%s_%s_z%d", 
                util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), util::AsString(m).c_str(), izone);
             // in VALORArray format
             if (opt.find("pdfc_vf") != string::npos) {
               fPDFCompOb [imode][izone]->SetName(Form("%s_%s_%s",tag,"pdfc_ob_vf",name));
               LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << fPDFCompOb[imode][izone]->GetName();
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
               TH2D * h2 = new TH2D("h2","VALOR/DUNE ND (Ereco,yreco) PDF component = f(beam,sample,mode,zone)",
                 n_enu_reco_bins, enu_reco_bins, n_y_reco_bins, y_reco_bins);
               h2 -> SetName( Form("%s_%s_%s",tag, "pdfc_ob_rf",name) );
               // fill from corresponding VALOR array
               for(int ier = 0; ier < n_enu_reco_bins; ier++) {
                 for(int iy = 0; iy < n_y_reco_bins; iy++) {
                   double val = fPDFCompOb[imode][izone]->GetEntry(ier,iy);
                   h2->SetBinContent(ier+1,iy+1,val);
                 }//iy
               }//ier
               // add tp object array and clean-up
               LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << h2->GetName();
               array->Add(h2); 
               // delete h2; ???? // MEMORY LEAK?
             }
          }//izone

          if(opt.find("+SB") != string::npos) {
             if(fMCTNullSb[imode]) continue;
             const char * name = Form("%s_%s_%s", 
                util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), util::AsString(m).c_str());
             // in VALORArray format
             if (opt.find("pdfc_vf") != string::npos) {
               fPDFCompSb[imode]->SetName(Form("%s_%s_%s",tag,"pdfc_sb_vf",name));
               LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << fPDFCompSb[imode]->GetName();
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
               TH2D * h2 = new TH2D("h2","VALOR/DUNE ND (Ereco,yreco) PDF component = f(beam,sample,mode)",
                 kNErecoBinsSb, kErecoBinEdgesSb, n_y_reco_bins_sb, y_reco_bin_edges_sb);
               h2 -> SetName( Form("%s_%s_%s",tag, "pdfc_sb_rf",name) );
               // fill from corresponding VALOR array
               for(int ier = 0; ier < kNErecoBinsSb; ier++) {
                 for(int iy = 0; iy <  n_y_reco_bins_sb; iy++) {
                   double val = fPDFCompSb[imode]->GetEntry(ier,iy);
                   h2->SetBinContent(ier+1,iy+1,val);
                 }//iy
               }//ier
               // add tp object array and clean-up
               LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << h2->GetName();
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
             const char * name = Form("%s_%s_z%d", 
                util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), izone);
             // in VALORArray format
             if (opt.find("pdft_vf") != string::npos) {
               fPDFTotOb[izone]->SetName(Form("%s_%s_%s",tag,"pdft_ob_vf",name));
               LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << fPDFTotOb[izone]->GetName();
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
               TH2D * h2 = new TH2D("h2","VALOR/DUNE ND (Ereco,yreco) PDF = f(beam,sample,zone)",
                 n_enu_reco_bins, enu_reco_bins, n_y_reco_bins, y_reco_bins);
               h2 -> SetName( Form("%s_%s_%s",tag, "pdft_ob_rf",name) );
               // fill from corresponding VALOR array
               for(int ier = 0; ier < n_enu_reco_bins; ier++) {
                 for(int iy = 0; iy < n_y_reco_bins; iy++) {
                   double val = fPDFTotOb[izone]->GetEntry(ier,iy);
                   h2->SetBinContent(ier+1,iy+1,val);
                 }//iy
               }//ier
               // add to object array and clean-up
               LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << h2->GetName();
               array->Add(h2); 
               // delete h2; ???? // MEMORY LEAK?
             }
        }//izone

        if(opt.find("+SB") != string::npos) {
             const char * name = Form("%s_%s", 
                util::AsString(fBeam).c_str(), util::AsString(fSample).c_str());
             // in VALORArray format
             if (opt.find("pdft_vf") != string::npos) {
               fPDFTotSb->SetName(Form("%s_%s_%s",tag,"pdft_sb_vf",name));
               LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << fPDFTotSb->GetName();
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
               TH2D * h2 = new TH2D("h2","VALOR/DUNE ND (Ereco,yreco) PDF = f(beam,sample)",
                 kNErecoBinsSb, kErecoBinEdgesSb, n_y_reco_bins_sb, y_reco_bin_edges_sb);
               h2 -> SetName( Form("%s_%s_%s",tag, "pdft_sb_rf",name) );
               h2->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
               h2->GetYaxis()->SetTitle("y");
               h2->SetTitle(Form("Number of events /bin /%f POT", fPOT));
               // fill from corresponding VALOR array
               for(int ier = 0; ier < kNErecoBinsSb; ier++) {
                 for(int iy = 0; iy < n_y_reco_bins_sb; iy++) {
                   double val = fPDFTotSb->GetEntry(ier,iy);
                   h2->SetBinContent(ier+1,iy+1,val);
                 }//iy
               }//ier
               // add to object array and clean-up
               LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << h2->GetName();
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
            const char * name = Form("%s_%s_%s_z%d", 
              util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), util::AsString(m).c_str(), izone);
            // get binning
            const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
            const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
            if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
            const double * enu_reco_bins = util::ErecoBinEdges(fSample,izone);
            const double * y_reco_bins   = util::YrecoBinEdges(fSample,izone);
            // create slices of the PDF components (function of Ereco, for given yreco bin)
            TH1D * htot = new TH1D("htot", 
               "VALOR/DUNE ND PDF component: Ereco spectrum = f(beam,sample,mode,zone)", n_enu_reco_bins, enu_reco_bins);
            htot->SetName(Form("%s_%s_%s",tag, "pdfcs_ob_rf",name) );
            htot->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
            htot->GetYaxis()->SetTitle(Form("Number of events /bin /%f POT", fPOT));
            for(int iy = 0; iy < n_y_reco_bins; iy++) {
              TH1D * h = new TH1D("h",
                  Form("VALOR/DUNE ND PDF component slice: Ereco spectrum = f(beam,sample,mode,zone) for y in [%f,%f]", 
                       y_reco_bins[iy],y_reco_bins[iy+1]),
                  n_enu_reco_bins, enu_reco_bins);
              h->SetName(Form("%s_%s_%s_y%d",tag, "pdfcs_ob_rf",name,iy) );
              h->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
              h->GetYaxis()->SetTitle(Form("Number of events /bin /%f POT", fPOT));
              for(int ier = 0; ier < n_enu_reco_bins; ier++) {
                double val = fPDFCompOb[imode][izone]->GetEntry(ier,iy);
                h->SetBinContent(ier+1, val);
                htot->SetBinContent(ier+1, htot->GetBinContent(ier+1) + val);
              }//ier
              // add to obj array and clean-up 
               LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << h->GetName();
              array->Add(h);
              //delete h; ??? MEM LEAK??
            }//iy         
            LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << htot->GetName();
            array->Add(htot);
            //delete htot; ??? MEM LEAK??
          }//izone

          if(opt.find("+SB") != string::npos) {
            const char * name = Form("%s_%s_%s", 
              util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), util::AsString(m).c_str());
            // create slices of the PDF components (function of Ereco, for given yreco bin)
            const int n_y_reco_bins_sb = util::NumYrecoBinsSb(fSample);
            const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(fSample);
            TH1D * htot = new TH1D("htot", 
               "VALOR/DUNE ND PDF component: Ereco spectrum = f(beam,sample,mode)", kNErecoBinsSb, kErecoBinEdgesSb);
            htot->SetName(Form("%s_%s_%s",tag, "pdfcs_sb_rf",name) );
            htot->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
            htot->GetYaxis()->SetTitle(Form("Number of events /bin /%f POT", fPOT));
            for(int iy = 0; iy < n_y_reco_bins_sb; iy++) {
              TH1D * h = new TH1D("h",
                  Form("VALOR/DUNE ND PDF component slice: Ereco spectrum = f(beam,sample,mode) for y in [%f,%f]", 
                       y_reco_bin_edges_sb[iy], y_reco_bin_edges_sb[iy+1]),
                  kNErecoBinsSb, kErecoBinEdgesSb);
              h->SetName(Form("%s_%s_%s_y%d",tag, "pdfcs_sb_rf",name,iy) );
              h->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
              h->GetYaxis()->SetTitle(Form("Number of events /bin /%f POT", fPOT));
              for(int ier = 0; ier < kNErecoBinsSb; ier++) {
                double val = fPDFCompSb[imode]->GetEntry(ier,iy);
                h->SetBinContent(ier+1, val);
                htot->SetBinContent(ier+1, htot->GetBinContent(ier+1) + val);
              }//ier
              // add to obj array and clean-up 
               LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << h->GetName();
              array->Add(h);
              //delete h; ??? MEM LEAK??
            }//iy         
            LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << htot->GetName();
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
          const char * name = Form("%s_%s_z%d", 
            util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), izone);
          // get binning
          const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
          const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
          if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
          const double * enu_reco_bins = util::ErecoBinEdges(fSample,izone);
          const double * y_reco_bins   = util::YrecoBinEdges(fSample,izone);
          // create slices of the total PDF (function of Ereco, for given yreco bin)
          TH1D * htot = new TH1D("htot", 
              "VALOR/DUNE ND PDF: Ereco spectrum = f(beam,sample,zone)", n_enu_reco_bins, enu_reco_bins);
          htot->SetName(Form("%s_%s_%s",tag, "pdfts_ob_rf",name) );
          htot->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
          htot->GetYaxis()->SetTitle(Form("Number of events /bin /%f POT", fPOT));
          for(int iy = 0; iy < n_y_reco_bins; iy++) {
            TH1D * h = new TH1D("h",
                Form("VALOR/DUNE ND PDF slice: Ereco spectrum = f(beam,sample,zone) for y in [%f,%f]", 
                     y_reco_bins[iy],y_reco_bins[iy+1]),
                n_enu_reco_bins, enu_reco_bins);
            h->SetName(Form("%s_%s_%s_y%d",tag, "pdfts_ob_rf",name,iy) );
            h->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
            h->GetYaxis()->SetTitle(Form("Number of events /bin /%f POT", fPOT));
            for(int ier = 0; ier < n_enu_reco_bins; ier++) {
              double val = fPDFTotOb[izone]->GetEntry(ier,iy);
              h->SetBinContent(ier+1, val);
              htot->SetBinContent(ier+1, htot->GetBinContent(ier+1) + val);
            }//ier
            // add to obj array and clean-up 
            LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << h->GetName();
            array->Add(h);
            //delete h; ??? MEM LEAK??      
          }//iy         
          LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << htot->GetName();
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
              "VALOR/DUNE ND PDF: Ereco spectrum = f(beam,sample)", kNErecoBinsSb, kErecoBinEdgesSb);
          htot->SetName(Form("%s_%s_%s",tag, "pdfts_sb_rf",name) );
          htot->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
          htot->GetYaxis()->SetTitle(Form("Number of events /bin /%f POT", fPOT));
          for(int iy = 0; iy < n_y_reco_bins_sb; iy++) {
            TH1D * h = new TH1D("h",
                Form("VALOR/DUNE ND PDF slice: Ereco spectrum = f(beam,sample) for y in [%f,%f]", 
                     y_reco_bin_edges_sb[iy], y_reco_bin_edges_sb[iy+1]),
                kNErecoBinsSb, kErecoBinEdgesSb);
            h->SetName(Form("%s_%s_%s_y%d",tag, "pdfts_sb_rf",name,iy) );
            h->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
            h->GetYaxis()->SetTitle(Form("Number of events /bin /%f POT", fPOT));
            for(int ier = 0; ier < kNErecoBinsSb; ier++) {
              double val = fPDFTotSb->GetEntry(ier,iy);
              h->SetBinContent(ier+1, val);
              htot->SetBinContent(ier+1, htot->GetBinContent(ier+1) + val);
            }//ier
            // add to obj array and clean-up 
            LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << h->GetName();
            array->Add(h);
            //delete h; ??? MEM LEAK??
          }//iy         
          LOG("SingleSampleFitModelA", pDEBUG) << "Adding: " << htot->GetName();
          array->Add(htot);
          //delete htot; ??? MEM LEAK??
        }//+SB?

  }//pdfts_rf

  return true;
}
//________________________________________________________________________________________
bool SingleSampleFitModelA::Write(
  const char * filename, const char * tag, Option_t * write_opt, Option_t * file_opt)
{
  LOG("SingleSampleFitModelA",pNOTICE) << "Writing results to file: [" << filename << "]";

  TObjArray * array = new TObjArray();
  this->Write(array,tag,write_opt);

  Option_t * used_file_opt = (file_opt == 0) ? "recreate" : file_opt;
  TFile f(filename, used_file_opt);
  array->Write();
  f.Close();

  return true;
}
//________________________________________________________________________________________
double SingleSampleFitModelA::GetFitStatisticPenalty (Option_t * /*opt*/) const
{
  double Sp_nuflux = (fNuFlux -> ChisqPenalty());
  double Sp_nuint  = (fNuInt  -> ChisqPenalty());
  double Sp_nudet  = (fNuDet  -> ChisqPenalty());

  double Sp = Sp_nuflux + Sp_nuint + Sp_nudet;

  LOG("SingleSampleFitModelA",pDEBUG) 
   << "Current penalty term = " << Sp 
   << " (flux = " << Sp_nuflux 
   << ", interaction = " << Sp_nuint 
   << ", detector = " << Sp_nudet << ")";

  return Sp;
}
//________________________________________________________________________________________
//
//
// Private methods:
//
//________________________________________________________________________________________

void SingleSampleFitModelA::Init(void)
{
  LOG("SingleSampleFitModelA",pDEBUG) << "Initializing...";

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
         fMCTNullOb[imode][izone] = true;
         fMCTNomOb [imode][izone] = 0;
         fMCTTunOb [imode][izone] = 0;
         fMCTSysOb [imode][izone] = 0;
         fMCTFinOb [imode][izone] = 0;
         fMCStatOb [imode][izone] = 0;
         // PDF
         fPDFCompOb [imode][izone] = 0;
         if(imode == 0) {
           fPDFTotOb     [izone] = 0;
           fPDFTotNullOb [izone] = true;
         }
       }//izone

  }//imode

  fUseMCDST = false;
  fPOT   = 0;
  fMCDST = 0;

//  for(int ip = 0; ip < conv::kNFitParams; ip++) {
//    fPhysParamCurrVal[ip] = 0;
//    fPhysParamFracErr[ip] = 0;
//  }

  fArrIdx = util::ArrIdx::Instance();
  
// Flux object
  fNuFlux = 0;
  fNuInt  = 0;
}
//________________________________________________________________________________________
void SingleSampleFitModelA::Book(void)
{
  LOG("SingleSampleFitModelA",pDEBUG) << "Booking...";

  int isample = fArrIdx->SampleIdx(fBeam,fSample);

  for(int imode = 0; imode < kNReacModes; imode++) {
        ReacMode_t m = kReactionModes[isample][imode];
        if(m == kmUndefined) continue;

        const int n_y_reco_bins_sb = util::NumYrecoBinsSb(fSample);
        const int n_enu_true_bins = util::NumEtrueBins(fSample);

        LOG("SingleSampleFitModelA",pDEBUG) 
            << "Booking MC template (simple binning) for " 
            << "beam: "     << util::AsString(fBeam) 
            << ", sample: " << util::AsString(fSample)
            << ", mode: "   << util::AsString(m); 

        // >> MC templates (simple binning)
        // (Note order of variables: reco first, true later)
        fMCTNullSb[imode] = false;
        fMCTNomSb [imode] = 
          new VALORArray(kNErecoBinsSb, n_y_reco_bins_sb, n_enu_true_bins);
        fMCTTunSb [imode] = 
          new VALORArray(kNErecoBinsSb, n_y_reco_bins_sb, n_enu_true_bins);
        fMCTSysSb [imode] = 
          new VALORArray(kNErecoBinsSb, n_y_reco_bins_sb, n_enu_true_bins);
        fMCTFinSb [imode] = 
          new VALORArray(kNErecoBinsSb, n_y_reco_bins_sb, n_enu_true_bins);
        fMCStatSb [imode] = 
          new VALORArray(kNErecoBinsSb, n_y_reco_bins_sb, n_enu_true_bins);

        // >> PDF component
        fPDFCompSb[imode] = 
            new VALORArray(kNErecoBinsSb, n_y_reco_bins_sb);           
        // >> PDF total
        // should get here for at least one imode value
        if(fPDFTotNullSb) {              
           LOG("SingleSampleFitModelA",pDEBUG) 
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

           LOG("SingleSampleFitModelA",pDEBUG) 
              << "Booking MC template for " 
              << "beam: "     << util::AsString(fBeam) 
              << ", sample: " << util::AsString(fSample)
              << ", mode: "   << util::AsString(m) 
              << ", zone: "   << izone;
 
           // >> MC templates 
           // (Note order of variables: reco first, true later)
           fMCTNullOb[imode][izone] = false;
           fMCTNomOb [imode][izone] = 
             new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins);
           fMCTTunOb [imode][izone] = 
             new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins);
           fMCTSysOb [imode][izone] = 
             new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins);
           fMCTFinOb [imode][izone] = 
             new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins);
           fMCStatOb [imode][izone] = 
             new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins);

           // >> PDF component
           fPDFCompOb[imode][izone] = 
               new VALORArray(n_enu_reco_bins,n_y_reco_bins);           
           // >> PDF total
           // should get here for at least one imode value
           if(fPDFTotNullOb[izone]) {              
              LOG("SingleSampleFitModelA",pDEBUG) 
                 << "Booking PDF (total) for " 
                 << "beam: "     << util::AsString(fBeam) 
                 << ", sample: " << util::AsString(fSample)
                 << ", zone: "   << izone;

              fPDFTotNullOb [izone] = false;
              fPDFTotOb     [izone] = new VALORArray(n_enu_reco_bins,n_y_reco_bins);           
           }
        }//izone

  }//imode
}
//________________________________________________________________________________________
void SingleSampleFitModelA::Clean(void)
{
  LOG("SingleSampleFitModelA",pDEBUG) << "Cleaning-up...";

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
              if ( fMCTNomOb[imode][izone] ) delete fMCTNomOb[imode][izone];
              if ( fMCTTunOb[imode][izone] ) delete fMCTTunOb[imode][izone];
              if ( fMCTSysOb[imode][izone] ) delete fMCTSysOb[imode][izone];
              if ( fMCTFinOb[imode][izone] ) delete fMCTFinOb[imode][izone];
              if ( fMCStatOb[imode][izone] ) delete fMCStatOb[imode][izone];
              fMCTNomOb[imode][izone] = 0;
              fMCTTunOb[imode][izone] = 0;
              fMCTSysOb[imode][izone] = 0;
              fMCTFinOb[imode][izone] = 0;
              fMCStatOb[imode][izone] = 0;
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
  
  if (fNuFlux) {delete fNuFlux;}
  if (fNuInt ) {delete fNuInt; }
  if (fNuInt ) {delete fNuDet; }
  
}
//________________________________________________________________________________________
void SingleSampleFitModelA::Zero(void)
{
  LOG("SingleSampleFitModelA",pDEBUG) << "Zeroing MC templates and/or PDFs...";

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
void SingleSampleFitModelA::FillFromDST(TTree * t)
{
// Fill MC templates from the input VALOR/DUNE DST TTree
// We use a single tree for all samples for a single beam configuration.

  LOG("SingleSampleFitModelA",pDEBUG) 
     << "Filling-in MC templates for beam configuration: " << util::AsString(fBeam);

  if(!t) return;

/*
  TBranch * bSample   = t->GetBranch("sample");         // selected ND sample
  TBranch * bReacMode = t->GetBranch("reac_mode");      // reaction mode
  TBranch * bEnuTrue  = t->GetBranch("enu_true");       // true energy (GeV)
  TBranch * bEnuReco  = t->GetBranch("enu_reco");       // reco energy (GeV)
  TBranch * byReco    = t->GetBranch("y_reco");         // reco inelasticity y
  TBranch * bWghtPOT  = t->GetBranch("wght_pot");       // weight for 1E+20 POT exposure
*/
  //tmp names
  //~ TBranch * bSample   = t->GetBranch("sample");         // selected ND sample
  //~ TBranch * bReacMode = t->GetBranch("reactionmode");   // reaction mode
  //~ TBranch * bEnuTrue  = t->GetBranch("Ev");             // true energy (GeV)
  //~ TBranch * bEnuReco  = t->GetBranch("Ev_reco");        // reco energy (GeV)
  //~ TBranch * byReco    = t->GetBranch("y_reco");         // reco inelasticity y
  //~ TBranch * bWghtPOT  = t->GetBranch("POTWeight");      // weight for 1E+20 POT exposure

  int    sample        = 0;
  int    reac_mode     = 0;
  double enu_true      = 0;
  double enu_reco      = 0;
  double y_reco        = 0;
  double wght_pot      = 0;

  t->SetBranchAddress("sample",       &sample);
  t->SetBranchAddress("reactionmode", &reac_mode);
  t->SetBranchAddress("Ev",           &enu_true);
  t->SetBranchAddress("Ev_reco",      &enu_reco);
  t->SetBranchAddress("y_reco",       &y_reco);
  t->SetBranchAddress("POTWeight",    &wght_pot);

  /*
  bSample   -> SetAddress(&sample    );
  bReacMode -> SetAddress(&reac_mode );
  bEnuTrue  -> SetAddress(&enu_true  );
  bEnuReco  -> SetAddress(&enu_reco  );
  byReco    -> SetAddress(&y_reco    );
  bWghtPOT  -> SetAddress(&wgt_pot   );

  t->SetBranchStatus("*",             0);
  t->SetBranchStatus("sample",        1); 
  t->SetBranchStatus("reac_mode",     1);    
  t->SetBranchStatus("enu_true",      1);  
  t->SetBranchStatus("enu_reco",      1);  
  t->SetBranchStatus("y_reco",        1);    
  t->SetBranchStatus("wght_pot",      1);
  */

  Long_t nev = t->GetEntries();
  LOG("SingleSampleFitModelA",pINFO) << "Input VALOR DST has " << nev << " entries";

  for(Long_t iev = 0; iev < nev; iev++) 
  {
     t->GetEntry(iev);

     if(iev%(nev/20)==0) {
       double pct = (100 * (double)(iev+1)) / (double)nev;
       LOG("SingleSampleFitModelA",pNOTICE) << "Reading "<< util::AsString(fBeam)<<" MC DST: "<< TMath::Nint(pct) << "% done";
     }

     // Get sample index
     Sample_t s = util::SampleFromInt(sample);
     if(s == ksUndefined) {
       LOG("SingleSampleFitModelA",pWARN) 
          << " ** Undefined sample ID used in MC event: " << iev
          << " (value stored in DST: " << sample << ")";
       //exit(1);
     }

     //  ================ NOTE - HACKS ================
     if(s == ksNuMuCC2piC) {
       LOG("HACK",pNOTICE) 
         << "MC event: " << iev << " belongs to sample: " << util::AsString(s) 
         << " not considered separately. Bundle in sample: " << util::AsString(ksNuMuCCoth);
       s = ksNuMuCCoth;
     }
     if(util::IsNC(s)) {
       LOG("HACK",pNOTICE) 
         << "MC event: " << iev << " belongs to NC sample: " << util::AsString(s) 
         << " Bundling it in sample: " << util::AsString(ksNC);
       s = ksNC;
     }
     //  ==============================================

     if(s != fSample) {
       LOG("SingleSampleFitModelA",pDEBUG) 
         << "Ignoring MC event: " << iev 
         << " (sample ID: " << util::AsString(s) 
         << " not matching one used for configuring model: " 
         << util::AsString(fSample) << ")";
       continue;  
     }

     int isample = fArrIdx->SampleIdx(fBeam,fSample);
     if(isample < 0) {
       // fine, we do not indlude all samples in the fit
       LOG("SingleSampleFitModelA",pDEBUG) 
         << "Ignoring MC event: " << iev 
         << " (sample ID: " << util::AsString(s) << " not included in current fit)";
       continue;
     }

     // Get reaction mode index
     ReacMode_t m = util::ReacModeFromInt(reac_mode); 
     if(m == kmUndefined) {
       LOG("SingleSampleFitModelA",pFATAL) 
          << " ** Undefined reaction mode ID used in MC event: " << iev
          << " (value stored in DST: " << reac_mode << ")";
       exit(1);
     }
     int imode = fArrIdx->ReacModeIdx(s, m);
     if(imode < 0) {
       // For a given sample we should consider a complete list of
       // true reaction modes (otherwise there are true contributions to the
       // event sample which are not taken into account).
       LOG("SingleSampleFitModelA",pFATAL) 
         << " ** Ignoring MC event: " << iev 
         << " (ignoring contribution to sample: " << util::AsString(s) << " from mode: " << util::AsString(m) << " ?)";
       exit(1);
     }

     // Get bin zone index
     int izone = util::BinZone(s, enu_reco, y_reco);
     if(izone < 0) {
//     LOG("SingleSampleFitModelA",pFATAL) - turn that to fatal after binning optimization is done
       LOG("SingleSampleFitModelA",pWARN) 
         << " ** No bin zone for MC event: " << iev 
         << " (" << util::AsString(s) << "/" << util::AsString(m) 
         << ", enu_reco = " << enu_reco << " GeV, " << " y_reco = " << y_reco << ")";
//     exit(1);
       continue;
     }

     bool is_null = fMCTNullOb[imode][izone];
     if(is_null) {
       LOG("SingleSampleFitModelA",pFATAL) 
         << "** Null MC template for sample: " << util::AsString(s) 
         << ", mode: " << util::AsString(m) << ", bin zone = " << izone << " ??";
       exit(1);
     }
     bool is_null_sb = fMCTNullSb[imode];
     if(is_null_sb) {
       LOG("SingleSampleFitModelA",pFATAL) 
         << "** Null MC template (simple binning) for sample: " << util::AsString(s) 
         << ", mode: " << util::AsString(m) << " ??";
       exit(1);
     }

     // check Ereco, yreco and Etrue values against built-in limits
     if(enu_reco < kErecoMin || enu_reco > kErecoMax) {
        LOG("SingleSampleFitModelA",pWARN) 
           << "MC event: " << iev << " has reconstructed energy = " << enu_reco 
           << " GeV, range used: [" << kErecoMin << ", " << kErecoMax << "] GeV";
     }
     if(y_reco < kYrecoMin || y_reco > kYrecoMax) {
        LOG("SingleSampleFitModelA",pWARN) 
           << "MC event: " << iev << " has reconstructed inelasticity y = " << y_reco 
           << ", range used: [" << kYrecoMin << ", " << kYrecoMax << "]";
     }
     if(enu_true < kEtrueMin || enu_true > kEtrueMax) {
        LOG("SingleSampleFitModelA",pWARN) 
           << "MC event: " << iev << " has true energy = " << enu_true 
           << " GeV, range used: [" << kEtrueMin << ", " << kEtrueMax << "] GeV";
     }

     // Get enu_true, enu_reco, y_reco array indices
     const int n_enu_true_bins = util::NumEtrueBins(s);
     const int n_enu_reco_bins = util::NumErecoBins(s,izone);
     const int n_y_reco_bins   = util::NumYrecoBins(s,izone);
     const int n_y_reco_bins_sb = util::NumYrecoBinsSb(s);
     const double * enu_true_bin_edges  = util::EtrueBinEdges(s);
     const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(s);
     const double * enu_reco_bin_edges  = util::ErecoBinEdges(s,izone);
     const double * y_reco_bin_edges    = util::YrecoBinEdges(s,izone);

     // protect against vars at upper limit (eg y_reco = 1, set by hand for NC events) as
     // the binary search below will give an index out of limits
     if(enu_reco >= kErecoMax) { enu_reco = enu_reco - kASmallNum; }
     if(y_reco   >= kYrecoMax) { y_reco   = y_reco - kASmallNum;   }

     // work-out the index using the bin-edge array defining the variable-size binning scheme
     int ienu_true    = TMath::BinarySearch(1+(Long_t)n_enu_true_bins, enu_true_bin_edges, enu_true);
     int ienu_reco    = TMath::BinarySearch(1+(Long_t)n_enu_reco_bins, enu_reco_bin_edges, enu_reco);
     int iy_reco      = TMath::BinarySearch(1+(Long_t)n_y_reco_bins,   y_reco_bin_edges,   y_reco  );
     // repeat, finding the indices for the template versions using a simple binning scheme
     int ienu_reco_sb = TMath::BinarySearch(1+(Long_t)kNErecoBinsSb,    kErecoBinEdgesSb,    enu_reco);
     int iy_reco_sb   = TMath::BinarySearch(1+(Long_t)n_y_reco_bins_sb, y_reco_bin_edges_sb, y_reco  );

     // Exposure for assumed data - Weight MC templates to that exposure
     double data_pot = fPOT;
 
     double mc_pot = wght_pot;
     assert(wght_pot>0.);

     // Calculate POT weight (assumed data exposure) / (generated MC exposure)
     //double wght = data_pot/mc_pot;
     double wght = data_pot*mc_pot;

     if(fNDFiducialMass > 0) {
       wght = wght*fNDFiducialMass;
     }

     LOG("InputMC",pDEBUG) 
         << "Inserting to MC teplates --> MC event #" << iev 
         << "\n imode     = " << imode    << " (" << util::AsString(m) << ")"
         << "\n izone     = " << izone   
         << "\n wght      = " << wght 
         << "\n ienu_reco = " << ienu_reco  << " (Enu_reco = " << enu_reco << " GeV), allowed idx range: [" << 0 << " -> " << n_enu_reco_bins-1 << "], " << n_enu_reco_bins << " bins"
         << "\n iy_reco   = " << iy_reco    << " (y_reco   = " << y_reco       << "), allowed idx range: [" << 0 << " -> " << n_y_reco_bins-1   << "], " << n_y_reco_bins << " bins"
         << "\n ienu_true = " << ienu_true  << " (Enu_true = " << enu_true << " GeV), allowed idx range: [" << 0 << " -> " << n_enu_true_bins-1 << "], " << n_enu_true_bins << " bins";

     // Believe that such a check is not performed in VALORArray, so check here just in case something went wrong in binary search above
     assert(ienu_reco >= 0 && ienu_reco < n_enu_reco_bins);
     assert(iy_reco   >= 0 && iy_reco   < n_y_reco_bins  );
     assert(ienu_true >= 0 && ienu_true < n_enu_true_bins);

     // Add `nom' array entry (and init `tun', `sys' and `fin' arrays = `nom')

     double curr_wght = fMCTNomOb[imode][izone]->GetEntry(ienu_reco, iy_reco, ienu_true);
     curr_wght += wght;
     fMCTNomOb [imode][izone]->SetEntry(curr_wght, ienu_reco, iy_reco, ienu_true);
     fMCTTunOb [imode][izone]->SetEntry(curr_wght, ienu_reco, iy_reco, ienu_true);
     fMCTSysOb [imode][izone]->SetEntry(curr_wght, ienu_reco, iy_reco, ienu_true);
     fMCTFinOb [imode][izone]->SetEntry(curr_wght, ienu_reco, iy_reco, ienu_true);     
     fMCStatOb [imode][izone]->SetEntry(        1, ienu_reco, iy_reco, ienu_true);     

     double curr_wght_sb = fMCTNomSb[imode]->GetEntry(ienu_reco_sb, iy_reco_sb, ienu_true);
     curr_wght_sb += wght;
     fMCTNomSb [imode]->SetEntry(curr_wght_sb, ienu_reco_sb, iy_reco_sb, ienu_true);
     fMCTTunSb [imode]->SetEntry(curr_wght_sb, ienu_reco_sb, iy_reco_sb, ienu_true);
     fMCTSysSb [imode]->SetEntry(curr_wght_sb, ienu_reco_sb, iy_reco_sb, ienu_true);
     fMCTFinSb [imode]->SetEntry(curr_wght_sb, ienu_reco_sb, iy_reco_sb, ienu_true);
     fMCStatSb [imode]->SetEntry(           1, ienu_reco_sb, iy_reco_sb, ienu_true);
     
     //~ break;//DEBUG
  }//iev 
}
//________________________________________________________________________________________
bool SingleSampleFitModelA::FillFromTemplateFile (TFile * f, string tag)
{
  bool success = true;

  int isample = fArrIdx->SampleIdx(fBeam,fSample);
  for(int imode = 0; imode < kNReacModes; imode++) {
        ReacMode_t m = kReactionModes[isample][imode];
        if(m == kmUndefined) continue;
        for(int izone = 0; izone < kNMaxBinZones; izone++) {
          TString name = TString::Format("%s_%s_%s_z%d", 
                util::AsString(fBeam).c_str(), util::AsString(fSample).c_str(), util::AsString(m).c_str(), izone);
          TString obj_name = TString::Format("%s_%s_%s", tag.c_str(), "mctnom_ob_vf", name.Data());
          VALORArray * arr = dynamic_cast<VALORArray*>(f->Get(obj_name.Data()));
          if (arr) {
            fMCTNomOb [imode][izone]->CopyFrom(*arr);
            delete arr;
          }
          else {
            success = false;
            LOG("SingleSampleFitModelA",pERROR) << "Failed to read template "<<obj_name;
          }
        }//izone
  } //imode

  if (!success) {
    util::Die(-1);
  }
  return success;
}
//________________________________________________________________________________________
void SingleSampleFitModelA::ApplyTuning(void)
{
// This method maps nom -> tun MC templates
// This is applied once when the model is constructed, not everytime Generate() is called.
// No external tuning available for the time-being


}
//________________________________________________________________________________________
void SingleSampleFitModelA::FluctuateMCStat(Option_t * option)
{
// Take into account the effect of MC statistics on the tuned MC templates.
// Note that this is the error due to the finite MC statistics used to construct the
// model and not the statistical error for the assumed (or actual) experimental exposure
// which is also taken account when generating toy-MC experiments.
// NOTE: For the time-being the effect applied on the tuned templates and stored on the 
// tuned templates, so we lose the tuned templates as they were before applying the MC
// statistical error. If this is important, we ought to create a new set of templates
// to hold this intermediate step going from the `tun' to the `sys' templates.

  LOG("SingleSampleFitModelA",pINFO) 
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

        // Updating only the templates using the optimized binning
        if(!update_mct_sb) {
          for(int izone = 0; izone < kNMaxBinZones; izone++) {
            bool is_null = fMCTNullOb[imode][izone];
            if(is_null) continue;
            const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
            const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
            for(int iet = 0; iet < n_enu_true_bins; iet++) {
              for(int ier = 0; ier < n_enu_reco_bins; ier++) {
                 for(int iyr = 0; iyr < n_y_reco_bins; iyr++) {
                   double val  = fMCTTunOb[imode][izone]->GetEntry(ier,iyr,iet);
                   double nmc  = fMCStatOb[imode][izone]->GetEntry(ier,iyr,iet);
                   // Fluctuate MC statistics and get the tweak factor
                   double nmcf = rnd->RndToyMCstat().Poisson(nmc); 
                   //double twk  = (nmc > 0) ? nmcf/nmc ? 1;
		   double twk  = (nmc > 0) ? nmcf/nmc : 1;
                   // Apply the tweak factor in the template, obviously a small effect for 
                   // large MC statistics. Again noting that this is not the statistical error
                   // for the current exposure. That one will be applied later in toy-MC generation.
                   double valf = val * twk; 
                   fMCTTunOb[imode][izone]->SetEntry(valf,ier,iyr,iet);
                 }//iyr: yreco bins
              }//ier: Ereco bins
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
            for(int ier = 0; ier < kNErecoBinsSb; ier++) {
               for(int iyr = 0; iyr < n_y_reco_bin_edges_sb; iyr++) {
                 double val  = fMCTTunSb[imode]->GetEntry(ier,iyr,iet);
                 double nmc  = fMCStatSb[imode]->GetEntry(ier,iyr,iet);
                 double nmcf = rnd->RndToyMCstat().Poisson(nmc); 
                 //double twk  = (nmc > 0) ? nmcf/nmc ? 1;
		 double twk  = (nmc > 0) ? nmcf/nmc : 1;
                 double valf = val * twk; 
                 fMCTTunSb[imode]->SetEntry(valf,ier,iyr,iet);

                 // Map to template with optimized binning
                 const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(fSample);
                 double enu_reco = kErecoBinEdgesSb[ier]   + (kErecoBinEdgesSb[ier+1]  -kErecoBinEdgesSb[ier]  )/2.;
                 //double y_reco   = y_reco_bin_edges_sb[iy] + (y_reco_bin_edges_sb[iy+1]-y_reco_bin_edges_sb[iy])/2.;
		 double y_reco   = y_reco_bin_edges_sb[iyr] + (y_reco_bin_edges_sb[iyr+1]-y_reco_bin_edges_sb[iyr])/2.;
                 int izone = util::BinZone(fSample, enu_reco, y_reco);
                 if(izone < 0) {
//                  LOG("SingleSampleFitModelA",pFATAL) - turn that to fatal after binning optimization is done
                    LOG("SingleSampleFitModelA",pWARN)
                       << " ** No bin zone for toy MC event (" << " (" << util::AsString(fSample) << ")"
                       << ", enu_reco = " << enu_reco << " GeV, " << " y_reco = " << y_reco << ")";
//                  exit(1);
                 }
                 const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
                 const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
                 const double * enu_reco_bin_edges  = util::ErecoBinEdges(fSample,izone);
                 const double * y_reco_bin_edges    = util::YrecoBinEdges(fSample,izone);
                 int ier2 = TMath::BinarySearch(1+(Long_t)n_enu_reco_bins, enu_reco_bin_edges, enu_reco);
                 //int iy2  = TMath::BinarySearch(1+(Long_t)n_y_reco_bins,   y_reco_bin_edges,   y_reco  );       
		 int iyr2  = TMath::BinarySearch(1+(Long_t)n_y_reco_bins,   y_reco_bin_edges,   y_reco  );
                 double valf_ob = fMCTTunOb[imode][izone]->GetEntry(ier2,iyr2,iet);
                 valf_ob += valf;
               //fMCTTunOb[imode][izone]->SetEntry(val_ob,ier2,iyr2,iet);
		 fMCTTunOb[imode][izone]->SetEntry(valf_ob,ier2,iyr2,iet);
               }//iyr: yreco bins
            }//ier: Ereco bins
          }//iet: Etrue bins

        }//update_mct_sb

  }//imode

#else

  LOG("SingleSampleFitModelA",pINFO) << "MC statistic error *not* applied";

#endif

}
//________________________________________________________________________________________
void SingleSampleFitModelA::ApplySystematics(Option_t * /*opt*/)
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
void SingleSampleFitModelA::ApplyPhysics(Option_t * option)
{
// This method maps sys -> fin MC templates.
// Applying correlated flux and cross-section systematics

  LOG("SingleSampleFitModelA",pINFO) 
     << "Applying physics params (option: " 
     << ((option) ? option : "")
     << ")";

  bool update_mct_sb = false;
  if(option) {
    string opt = option;
    if(opt.find("+SB") != string::npos) {
      update_mct_sb = true;
    }
  }
      
  const int n_enu_true_bins         = util::NumEtrueBins(fSample);
  const double * enu_true_bin_edges = util::EtrueBinEdges(fSample);
  const int n_y_reco_bin_edges_sb   = util::NumYrecoBinsSb(fSample);

  int isample = fArrIdx->SampleIdx(fBeam,fSample);
        
  for(int imode = 0; imode < kNReacModes; imode++) {
        ReacMode_t m = kReactionModes[isample][imode];
        if(m == kmUndefined) continue;
        
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
        LOG("SingleSampleFitModelA",pDEBUG) 
           << "Handing templates for: " 
           << util::AsString(fBeam) << ", " << util::AsString(fSample) << ", " << util::AsString(m);

        LOG("SingleSampleFitModelA",pDEBUG) 
           << "Initializing `fin' templates to the `sys' ones";
#endif

        for(int izone = 0; izone < kNMaxBinZones; izone++) {
          bool is_null = fMCTNullOb[imode][izone];
          if(is_null) continue;
          const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
          const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
          // copy sys -> fin MC templates
          for(int iet = 0; iet < n_enu_true_bins; iet++) {
            for(int ier = 0; ier < n_enu_reco_bins; ier++) {
               for(int iyr = 0; iyr < n_y_reco_bins; iyr++) {
                 double val = fMCTSysOb[imode][izone]->GetEntry(ier,iyr,iet);
                 fMCTFinOb[imode][izone]->SetEntry(val,ier,iyr,iet);
               }//iyr: yreco bins
            }//ier: Ereco bins
          }//iet: Etrue bins
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
          LOG("SingleSampleFitModelA",pDEBUG) 
             << "Applying Etrue-dependent params";
#endif
          // first apply Etrue-dependent params
          for(int ip = 0; ip < kNFitParams; ip++) {
            //-------------- error, prone need to simplify
            PhysParamId_t p = kFitParam[ip];
            if(p == kPhypUndefined) continue;
            bool apply = util::ParamIsAppliedTo(fBeam,fSample,m,p);
              //-------------- 
             if(!apply) continue;
             bool enu_true_dep = kFitParamEtrueDependence[ip];
             if(!enu_true_dep) continue;
             double f = fPhysHypothesis.CurrValue(p);
             f = TMath::Max(0.,f);
             bool tweaked = TMath::Abs(f-1) > kASmallNum;
             if(!tweaked) continue;
             const double enu_true_min = kFitParamEtrueRange[ip][0];
             const double enu_true_max = kFitParamEtrueRange[ip][1];     
             int ienu_true_min = TMath::BinarySearch((Long_t)n_enu_true_bins, enu_true_bin_edges, enu_true_min+kASmallNum);
             int ienu_true_max = TMath::BinarySearch((Long_t)n_enu_true_bins, enu_true_bin_edges, enu_true_max-kASmallNum);
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
             LOG("SingleSampleFitModelA",pDEBUG) 
                << "Applying parameter: " << util::AsString(p) << " with value = " << f 
                << " in Etrue bin range: [" << ienu_true_min << ", " << ienu_true_max << "]";
#endif
             for(int iet = ienu_true_min; iet <= ienu_true_max; iet++) {
               for(int ier = 0; ier < n_enu_reco_bins; ier++) {
                 for(int iyr = 0; iyr < n_y_reco_bins; iyr++) {
                    double & val = fMCTFinOb[imode][izone]->GetEntryRef(ier,iyr,iet);
                    double val_old = val;
                    val *= f;
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
                    LOG("SingleSampleFitModelA",pDEBUG) 
                      << "MCT[" << imode << ", " << izone << "] = " 
                      << val_old << " --> " << val;
#endif
                 }//iyr: yreco bins
               }//ier: Ereco bins
             }//iet: Etrue bins
          }//ip

#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
          LOG("SingleSampleFitModelA",pDEBUG) 
             << "Applying Etrue-independent params";
#endif
          // then apply the non-Etrue-dependent factors (bundle them together to loop over the
          // Ereco,yreco,Etrue bins just once)
          double fnoEt = 1.;
          for(int ip = 0; ip < kNFitParams; ip++) {
             //-------------- error, prone need to simplify
             PhysParamId_t p = kFitParam[ip];
             if(p == kPhypUndefined) continue;
             bool apply = util::ParamIsAppliedTo(fBeam,fSample,m,p);
             //-------------- 
             if(!apply) continue;
             bool enu_true_dep = kFitParamEtrueDependence[ip];
             if(enu_true_dep) continue;
             double f = fPhysHypothesis.CurrValue(p);
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
             LOG("SingleSampleFitModelA",pDEBUG) 
                << "Applying parameter: " << util::AsString(p) << " with value = " << f;
#endif
             fnoEt *= f;
          }//ip
          fnoEt = TMath::Max(0.,fnoEt);
          for(int iet = 0; iet < n_enu_true_bins; iet++) {
            for(int ier = 0; ier < n_enu_reco_bins; ier++) {
              for(int iyr = 0; iyr < n_y_reco_bins; iyr++) {
                 double & val = fMCTFinOb[imode][izone]->GetEntryRef(ier,iyr,iet);
                 val *= fnoEt;
              }//iyr: yreco bins
            }//ier: Ereco bins
          }//iet: Etrue bins
        }//izone


        if(update_mct_sb) {
          bool is_null = fMCTNullSb[imode];
          if(is_null) continue;
          // copy sys -> fin MC templates
          for(int iet = 0; iet < n_enu_true_bins; iet++) {
            for(int ier = 0; ier < kNErecoBinsSb; ier++) {
               for(int iyr = 0; iyr < n_y_reco_bin_edges_sb; iyr++) {
                 double val = fMCTSysSb[imode]->GetEntry(ier,iyr,iet);
                 fMCTFinSb[imode]->SetEntry(val,ier,iyr,iet);
               }//iyr: yreco bins
            }//ier: Ereco bins
          }//iet: Etrue bins

          // first apply Etrue-dependent params
          for(int ip = 0; ip < kNFitParams; ip++) {
             //-------------- error, prone need to simplify
             PhysParamId_t p = kFitParam[ip];
             if(p == kPhypUndefined) continue;
             bool apply = util::ParamIsAppliedTo(fBeam,fSample,m,p);
             //-------------- 
             if(!apply) continue;
             bool enu_true_dep = kFitParamEtrueDependence[ip];
             if(!enu_true_dep) continue;
             double f = fPhysHypothesis.CurrValue(p);
             f = TMath::Max(0.,f);
             bool tweaked = TMath::Abs(f-1) > kASmallNum;
             if(!tweaked) continue;
             const double enu_true_min = kFitParamEtrueRange[ip][0];
             const double enu_true_max = kFitParamEtrueRange[ip][1];     
             int ienu_true_min = TMath::BinarySearch((Long_t)n_enu_true_bins, enu_true_bin_edges, enu_true_min+kASmallNum);
             int ienu_true_max = TMath::BinarySearch((Long_t)n_enu_true_bins, enu_true_bin_edges, enu_true_max-kASmallNum);
             for(int iet = ienu_true_min; iet <= ienu_true_max; iet++) {
               for(int ier = 0; ier < kNErecoBinsSb; ier++) {
                 for(int iyr = 0; iyr < n_y_reco_bin_edges_sb; iyr++) {
                    double & val = fMCTFinSb[imode]->GetEntryRef(ier,iyr,iet);
                    val *= f;
                 }//iyr: yreco bins
               }//ier: Ereco bins
             }//iet: Etrue bins
          }//ip

          // then apply the non-Etrue-dependent factors (bundle them together to loop over the
          // Ereco,yreco,Etrue bins just once)
          double fnoEt = 1.;
          for(int ip = 0; ip < kNFitParams; ip++) {
            //-------------- error, prone need to simplify
            PhysParamId_t p = kFitParam[ip];
            if(p == kPhypUndefined) continue;
            bool apply = util::ParamIsAppliedTo(fBeam,fSample,m,p);
            //-------------- 
            if(!apply) continue;
            bool enu_true_dep = kFitParamEtrueDependence[ip];
            if(enu_true_dep) continue;
            double f = fPhysHypothesis.CurrValue(p);
            f = TMath::Max(0.,f);
            bool tweaked = TMath::Abs(f-1) > kASmallNum;
            if(!tweaked) continue;
            fnoEt *= f;
          }//ip
          fnoEt = TMath::Max(0.,fnoEt);
          for(int iet = 0; iet < n_enu_true_bins; iet++) {
            for(int ier = 0; ier < kNErecoBinsSb; ier++) {
              for(int iyr = 0; iyr < n_y_reco_bin_edges_sb; iyr++) {
                 double & val = fMCTFinSb[imode]->GetEntryRef(ier,iyr,iet);
                 val *= fnoEt;
              }//iyr: yreco bins
            }//ier: Ereco bins
          }//iet: Etrue bins
        }//update_mct_sb?

      }//imode
}
//________________________________________________________________________________________
void SingleSampleFitModelA::UpdatePDFs(Option_t * option)
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

  const int n_enu_true_bins = util::NumEtrueBins(fSample);
  const int n_y_reco_bins_sb = util::NumYrecoBinsSb(fSample);

  for(int imode = 0; imode < kNReacModes; imode++) {
        ReacMode_t m = kReactionModes[isample][imode];
        if(m == kmUndefined) continue;

        for(int izone = 0; izone < kNMaxBinZones; izone++) {
          bool is_null = fMCTNullOb[imode][izone];
          if(is_null) continue;
          const int n_enu_reco_bins = util::NumErecoBins(fSample,izone);
          const int n_y_reco_bins   = util::NumYrecoBins(fSample,izone);
          for(int ier=0; ier < n_enu_reco_bins; ier++) {
            for(int iyr=0; iyr < n_y_reco_bins; iyr++) {
               double sum = 0.;
               for(int iet=0; iet < n_enu_true_bins; iet++) {
                 sum += fMCTFinOb[imode][izone]->GetEntry(ier,iyr,iet);
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
                 sum += fMCTFinSb[imode]->GetEntry(ier,iyr,iet);
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
const valor::NuFlux * valor::SingleSampleFitModelA::GetNuFlux(void) const
{
  return fNuFlux;
}
//________________________________________________________________________________________
valor::NuFlux * valor::SingleSampleFitModelA::GetNuFlux(void)
{
  return fNuFlux;
}
//________________________________________________________________________________________
const valor::NuInt * valor::SingleSampleFitModelA::GetNuInt(void) const
{
  return fNuInt;
}
//________________________________________________________________________________________
valor::NuInt * valor::SingleSampleFitModelA::GetNuInt(void)
{
  return fNuInt;
}
//________________________________________________________________________________________
const valor::NuDet * valor::SingleSampleFitModelA::GetNuDet(void) const
{
  return fNuDet;
}
//________________________________________________________________________________________
valor::NuDet * valor::SingleSampleFitModelA::GetNuDet(void)
{
  return fNuDet;
}
//________________________________________________________________________________________
valor::PhysParamList valor::SingleSampleFitModelA::OneSigmaErrors(Option_t * /*opt*/)
{
  PhysParamList ppl;
  ppl.SetName("NDModel_Errors");
  fNuFlux->CopyOneSigmaErrorsTo(ppl);
  fNuDet ->CopyOneSigmaErrorsTo(ppl);
  fNuInt ->CopyOneSigmaErrorsTo(ppl);
  return ppl;
}
//________________________________________________________________________________________
TMatrixD valor::SingleSampleFitModelA::CovarianceMatrix(Option_t * /*opt*/)
{
  // Get cov matrices from subcomponents
  vector<const TMatrixD*> cov_vec;
  cov_vec.push_back(&(fNuFlux->CovMatrix()));
  cov_vec.push_back(&(fNuInt ->CovMatrix()));
  cov_vec.push_back(&(fNuDet ->CovMatrix()));
  
  TMatrixD total = util::ConcatenateTMatrices(cov_vec);
  
  return total;
}
//________________________________________________________________________________________
