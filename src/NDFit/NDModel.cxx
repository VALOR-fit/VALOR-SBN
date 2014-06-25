//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include <cassert>
#include <ostream>

#include <TXMLEngine.h>
#include <TFile.h>
#include <TObjArray.h>
#include <TMath.h>
#include <TH1D.h>
#include <TH2D.h>

//fmwk
#include "Conventions/PhysHypothesisId.h"
#include "Conventions/PhysParamId.h"
#include "Conventions/NuOscMixParam.h"
#include "Conventions/NuOscDmsqScheme.h"
#include "Conventions/Opt.h"
#include "Conventions/PDG.h"
#include "Utilities/UtlStyle.h"
#include "Utilities/UtlXML.h"
#include "Messenger/Messenger.h"
//lbnx
#include "Conventions/ReacMode.h"
#include "Conventions/BeamConf.h"
#include "NDFit/NDModel.h"
#include "NDFit/NDSample.h"
#include "NDFit/NDBeamConf.h"

using std::endl;

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
NDModel::NDModel() :
FitModelABC()
{
  this->Init();
  this->Book();
  this->Zero();
}
//________________________________________________________________________________________
NDModel::~NDModel() 
{
  this->Clean();
}
//________________________________________________________________________________________
//
//
// FitModelABC interface implementation:
//
//________________________________________________________________________________________
string NDModel::Name(void)
{
  return "LBNxND";
}
//________________________________________________________________________________________
bool NDModel::Read(string file, Option_t * /*opt*/)
{
  this->Zero();

  LOG("NDModel",pNOTICE) << "Reading configuration from XML file [" << file << "]";

  // Parse the input XML configuration file
  TXMLEngine* xml = new TXMLEngine;   
  XMLDocPointer_t xmldoc = xml->ParseFile(file.c_str());
  if (xmldoc==0) {
    LOG("NDModel",pERROR) << "Can not parse input XML file [" << file << "]";
    delete xml;
    return false;  
  }
  XMLNodePointer_t root_node = xml->DocGetRootElement(xmldoc);

  // Ge the near detector fiducial mass
  string name = "nd/fiducial_mass";
  fNDFiducialMass = util::XML2Dbl(xml,root_node,name);
  LOG("NDModel",pINFO)
    << "ND fiducial mass = " << fNDFiducialMass*1000 << " tonnes";

  // Get assumed exposure for each beam configuration
  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
    BeamConf_t b = kNDBeamConf[ibeam];
    if(b == kbUndefined) continue;
    string node_name = "data/exposure/" + util::AsString(b, "lowercase");
    fPOT[ibeam] = util::XML2Dbl(xml,root_node,node_name);
    LOG("NDModel",pINFO) 
       << "Beam config: " << util::AsString(b) 
       << " -> Exposure = " << fPOT[ibeam] << " POT.";
  }//ibeam

  //
  // Using input in VALOR DST format?
  // If true, read the ROOT files and fill-in the MC templates.
  // If false, just read in the MC templates directly. 
  // In the later case, the templates are pre-binned so the binning
  // can not change. Make sure the templates have the expected binning.
  //
  fUseMCDST = util::XML2Bool(xml,root_node,"mc/using_dst_format");
  if(fUseMCDST) {
    LOG("NDModel",pINFO) << "Filling in VALOR MC templates using VALOR DSTs";
    for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
       BeamConf_t b = kNDBeamConf[ibeam];
       if(b == kbUndefined) continue;
       string node_name = "mc/dst/" + util::AsString(b, "lowercase");
       fMCDST[ibeam] = util::XML2TTree (xml,root_node,node_name);
       assert(fMCDST[ibeam]);
       this->Fill(fMCDST[ibeam], ibeam);
    }//ibeam
  } 
  else {
    // ** implement later (when binning is optimized) and make it the default
    // ** choice to reduce the size of data files stored in the SVN repository.
    LOG("NDModel",pINFO) << "Using stored VALOR MC templates";
    LOG("NDModel",pFATAL) << "Option note supported yet";
    exit(1);
  }
  
  // At the point the nominal MC templates are filled-in.
  // Apply any fixed tuning here, not on an event by event basis.
  // It is the tuned templates that be the starting point in the Generate() method.
  this->ApplyTuning();

  // Release memory
  xml->FreeDoc(xmldoc);
  delete xml;

  LOG("NDModel",pNOTICE) << "Done configuring LBNx/ND model... \n\n";

  return true;
}
//________________________________________________________________________________________
bool NDModel::Generate(const PhysHypothesis & ph, Option_t * opt)
{
// input opt: 
// - Leave null for the fit
// - Use "+SB" to generate finely-binned predictions too (for plotting or toy-MC generation)

  fPhysHypothesis.Copy(ph);
  //PhysHypothesis_t hyp = fPhysHypothesis.Hypothesis();

  LOG("NDModel",pINFO)  
     << "Generating model predictions for the input hypothesis: " 
     << fPhysHypothesis;

//this->ApplySystematics(opt);  // `tun' MC templates --> `sys' MC templates
  this->ApplyPhysics(opt);      // `sys' MC templates --> `fin' MC templates
  this->UpdatePDFs(opt);        // `fin' MC templates --> p.d.f

  LOG("NDModel",pINFO) << "Done generating predictions";

  return true;
}
//________________________________________________________________________________________
void NDModel::RandomizeSystematics(void)
{
  //...
}
//________________________________________________________________________________________
void NDModel::TweakSystematic(
  string /*syst_name*/, double /*twkdial*/, Option_t * /*opt*/)
{
  //...
}
//________________________________________________________________________________________
void NDModel::TweakSystematic(
  PhysParamId_t syst, double twkdial, Option_t * /*opt*/)
{
  //...
}
//________________________________________________________________________________________
PhysParamList NDModel::Tweaks(void)
{
  PhysParamList list;
  //...
  return list;
}
//________________________________________________________________________________________
void NDModel::ResetSystematics(void)
{
  //...
}
//________________________________________________________________________________________
void NDModel::PrintSystematics(ostream & stream) const
{
  stream << endl;
}
//________________________________________________________________________________________
bool NDModel::Generate (const FitParamList & fp, Option_t * opt)
{
  // extract the values of params driving the oscillation, decoherence or decay model
  PhysHypothesis ph(fp);

  // call the main Generate() method
  return this->Generate(ph, opt);
}
//________________________________________________________________________________________
bool NDModel::Write(TObjArray * array, const char * tag, Option_t * write_opt)
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

  LOG("NDModel",pINFO) << "Writing results to input object array...";

  if(!array) {
     LOG("NDModel",pERROR) << "Null input object array.";
     return false;
  }

  valor::util::SetDefaultStyle();

  string opt = (write_opt) ? write_opt : "pdft_vf";

  if(opt.find("all") != string::npos) {
    opt = "mct_vf + pdfc_vf + pdfc_rf + pdft_vf + pdft_rf + pdfcs_rf + pdfts_rf +SB";
  }
  LOG("NDModel",pINFO) << "Write option: " << opt;

  //
  // Write out MC templates (VALORArray format)
  //

  if(opt.find("mct_vf") != string::npos) {

    for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
      BeamConf_t b = kNDBeamConf[ibeam];
      if(b == kbUndefined) continue;
      for(int isample = 0; isample < kNNDSamples; isample++) {
        NDSample_t s = kNDSample[isample];
        if(s == ksNDUndefined) continue;
        for(int imode = 0; imode < kNReacModes; imode++) {
          ReacMode_t m = kNDReactionModes[isample][imode];
          if(m == kmUndefined) continue;

          for(int izone = 0; izone < kNMaxBinZones; izone++) {
             if(fMCTNull[ibeam][isample][imode][izone]) continue;
             const char * name = Form("%s_%s_%s_z%d", 
                util::AsString(b).c_str(), util::AsString(s).c_str(), util::AsString(m).c_str(), izone);
             fMCTNom [ibeam][isample][imode][izone] -> SetName( Form("%s_%s_%s", tag, "mctnom_ob_vf", name) );
             fMCTTun [ibeam][isample][imode][izone] -> SetName( Form("%s_%s_%s", tag, "mcttun_ob_vf", name) );
             fMCTSys [ibeam][isample][imode][izone] -> SetName( Form("%s_%s_%s", tag, "mctsys_ob_vf", name) );
             fMCTFin [ibeam][isample][imode][izone] -> SetName( Form("%s_%s_%s", tag, "mctfin_ob_vf", name) );
             array -> Add ( fMCTNom [ibeam][isample][imode][izone] ); 
             array -> Add ( fMCTTun [ibeam][isample][imode][izone] ); 
             array -> Add ( fMCTSys [ibeam][isample][imode][izone] ); 
             array -> Add ( fMCTFin [ibeam][isample][imode][izone] );
          }//izone

          if(opt.find("+SB") != string::npos) {
             if(fMCTSbNull[ibeam][isample][imode]) continue;
             const char * name = Form("%s_%s_%s", 
                util::AsString(b).c_str(), util::AsString(s).c_str(), util::AsString(m).c_str());
             fMCTSbNom [ibeam][isample][imode] -> SetName( Form("%s_%s_%s", tag, "mctnom_sb_vf", name) );
             fMCTSbTun [ibeam][isample][imode] -> SetName( Form("%s_%s_%s", tag, "mcttun_sb_vf", name) );
             fMCTSbSys [ibeam][isample][imode] -> SetName( Form("%s_%s_%s", tag, "mctsys_sb_vf", name) );
             fMCTSbFin [ibeam][isample][imode] -> SetName( Form("%s_%s_%s", tag, "mctfin_sb_vf", name) );
             array -> Add ( fMCTSbNom [ibeam][isample][imode] ); 
             array -> Add ( fMCTSbTun [ibeam][isample][imode] ); 
             array -> Add ( fMCTSbSys [ibeam][isample][imode] ); 
             array -> Add ( fMCTSbFin [ibeam][isample][imode] );
          }//+SB?

        }//imode
      }//isample
    }//ibeam
  }//mct_vf


  //
  // Write out the PDF components (VALORArray or bare ROOT format)
  //

  if(opt.find("pdfc_vf") != string::npos || opt.find("pdfc_rf") != string::npos) {

    for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
      BeamConf_t b = kNDBeamConf[ibeam];
      if(b == kbUndefined) continue;
      for(int isample = 0; isample < kNNDSamples; isample++) {
        NDSample_t s = kNDSample[isample];
        if(s == ksNDUndefined) continue;
        for(int imode = 0; imode < kNReacModes; imode++) {
          ReacMode_t m = kNDReactionModes[isample][imode];
          if(m == kmUndefined) continue;

          for(int izone = 0; izone < kNMaxBinZones; izone++) {
             if(fMCTNull[ibeam][isample][imode][izone]) continue;
             const char * name = Form("%s_%s_%s_z%d", 
                util::AsString(b).c_str(), util::AsString(s).c_str(), util::AsString(m).c_str(), izone);
             // in VALORArray format
             if (opt.find("pdfc_vf") != string::npos) {
               fMCPDFComp [ibeam][isample][imode][izone]->SetName(Form("%s_%s_%s",tag,"pdfc_ob_vf",name));
               array->Add(fMCPDFComp[ibeam][isample][imode][izone]);
             }
             // in TH2D format
             if (opt.find("pdfc_rf") != string::npos) {
               // get binning
               const int n_enu_reco_bins = util::NumErecoBins(s,izone);
               const int n_y_reco_bins   = util::NumYrecoBins(s,izone);
               if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
               const double * enu_reco_bins = util::ErecoBinEdges(s,izone);
               const double * y_reco_bins   = util::YrecoBinEdges(s,izone);
               // book histogram
               TH2D * h2 = new TH2D("h2","VALOR/LBNx ND (Ereco,yreco) PDF component = f(beam,sample,mode,zone)",
                 n_enu_reco_bins, enu_reco_bins, n_y_reco_bins, y_reco_bins);
               h2 -> SetName( Form("%s_%s_%s",tag, "pdfc_ob_rf",name) );
               // fill from corresponding VALOR array
               for(int ier = 0; ier < n_enu_reco_bins; ier++) {
                 for(int iy = 0; iy < n_y_reco_bins; iy++) {
                   double val = fMCPDFComp[ibeam][isample][imode][izone]->GetEntry(ier,iy);
                   h2->SetBinContent(ier+1,iy+1,val);
                 }//iy
               }//ier
               // add tp object array and clean-up
               array->Add(h2); 
               // delete h2; ???? // MEMORY LEAK?
             }
          }//izone

          if(opt.find("+SB") != string::npos) {
             if(fMCTSbNull[ibeam][isample][imode]) continue;
             const char * name = Form("%s_%s_%s", 
                util::AsString(b).c_str(), util::AsString(s).c_str(), util::AsString(m).c_str());
             // in VALORArray format
             if (opt.find("pdfc_vf") != string::npos) {
               fMCPDFSbComp [ibeam][isample][imode]->SetName(Form("%s_%s_%s",tag,"pdfc_sb_vf",name));
               array->Add(fMCPDFSbComp[ibeam][isample][imode]);
             }
             // in TH2D format
             if (opt.find("pdfc_rf") != string::npos) {
               // book histogram
               const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(s);
               TH2D * h2 = new TH2D("h2","VALOR/LBNx ND (Ereco,yreco) PDF component = f(beam,sample,mode)",
                 kNErecoBinsSb, kErecoBinEdgesSb, kNYrecoBinsSb, y_reco_bin_edges_sb);
               h2 -> SetName( Form("%s_%s_%s",tag, "pdfc_sb_rf",name) );
               // fill from corresponding VALOR array
               for(int ier = 0; ier < kNErecoBinsSb; ier++) {
                 for(int iy = 0; iy < kNYrecoBinsSb; iy++) {
                   double val = fMCPDFSbComp[ibeam][isample][imode]->GetEntry(ier,iy);
                   h2->SetBinContent(ier+1,iy+1,val);
                 }//iy
               }//ier
               // add tp object array and clean-up
               array->Add(h2); 
               // delete h2; ???? // MEMORY LEAK?
             }
          }//+SB?          

        }//imode
      }//isample
    }//ibeam
  }//pdfc_vf,pdfc_rf


  //
  // Write out the total PDF (VALORArray or bare ROOT format)
  //

  if(opt.find("pdft_vf") != string::npos || opt.find("pdft_rf") != string::npos) {

    for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
      BeamConf_t b = kNDBeamConf[ibeam];
      if(b == kbUndefined) continue;
      for(int isample = 0; isample < kNNDSamples; isample++) {
        NDSample_t s = kNDSample[isample];
        if(s == ksNDUndefined) continue;

        for(int izone = 0; izone < kNMaxBinZones; izone++) {
             const char * name = Form("%s_%s_z%d", 
                util::AsString(b).c_str(), util::AsString(s).c_str(), izone);
             // in VALORArray format
             if (opt.find("pdft_vf") != string::npos) {
               fMCPDFTot[ibeam][isample][izone]->SetName(Form("%s_%s_%s",tag,"pdft_ob_vf",name));
               array->Add(fMCPDFTot[ibeam][isample][izone]);
             }
             // in TH2D format
             if (opt.find("pdft_rf") != string::npos) {
               // get binning
               const int n_enu_reco_bins = util::NumErecoBins(s,izone);
               const int n_y_reco_bins   = util::NumYrecoBins(s,izone);
               if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
               const double * enu_reco_bins = util::ErecoBinEdges(s,izone);
               const double * y_reco_bins   = util::YrecoBinEdges(s,izone);
               // book histogram
               TH2D * h2 = new TH2D("h2","VALOR/LBNx ND (Ereco,yreco) PDF = f(beam,sample,zone)",
                 n_enu_reco_bins, enu_reco_bins, n_y_reco_bins, y_reco_bins);
               h2 -> SetName( Form("%s_%s_%s",tag, "pdft_ob_rf",name) );
               // fill from corresponding VALOR array
               for(int ier = 0; ier < n_enu_reco_bins; ier++) {
                 for(int iy = 0; iy < n_y_reco_bins; iy++) {
                   double val = fMCPDFTot[ibeam][isample][izone]->GetEntry(ier,iy);
                   h2->SetBinContent(ier+1,iy+1,val);
                 }//iy
               }//ier
               // add to object array and clean-up
               array->Add(h2); 
               // delete h2; ???? // MEMORY LEAK?
             }
        }//izone

        if(opt.find("+SB") != string::npos) {
             const char * name = Form("%s_%s", 
                util::AsString(b).c_str(), util::AsString(s).c_str());
             // in VALORArray format
             if (opt.find("pdft_vf") != string::npos) {
               fMCPDFSbTot[ibeam][isample]->SetName(Form("%s_%s_%s",tag,"pdft_sb_vf",name));
               array->Add(fMCPDFSbTot[ibeam][isample]);
             }
             // in TH2D format
             if (opt.find("pdft_rf") != string::npos) {
               // book histogram
               const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(s);
               TH2D * h2 = new TH2D("h2","VALOR/LBNx ND (Ereco,yreco) PDF = f(beam,sample)",
                 kNErecoBinsSb, kErecoBinEdgesSb, kNYrecoBinsSb, y_reco_bin_edges_sb);
               h2 -> SetName( Form("%s_%s_%s",tag, "pdft_sb_rf",name) );
               h2->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
               h2->GetYaxis()->SetTitle("y");
               h2->SetTitle(Form("Number of events /bin /%f POT", fPOT[ibeam]));
               // fill from corresponding VALOR array
               for(int ier = 0; ier < kNErecoBinsSb; ier++) {
                 for(int iy = 0; iy < kNYrecoBinsSb; iy++) {
                   double val = fMCPDFSbTot[ibeam][isample]->GetEntry(ier,iy);
                   h2->SetBinContent(ier+1,iy+1,val);
                 }//iy
               }//ier
               // add to object array and clean-up
               array->Add(h2); 
               // delete h2; ???? // MEMORY LEAK?
             }
        }//+SB?

      }//isample
    }//ibeam
  }//pdft_vf,pdft_rf


  //
  // Write out the slices of the PDF components (bare ROOT format)
  //

  if(opt.find("pdfcs_rf") != string::npos) {

    for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
      BeamConf_t b = kNDBeamConf[ibeam];
      if(b == kbUndefined) continue;
      for(int isample = 0; isample < kNNDSamples; isample++) {
        NDSample_t s = kNDSample[isample];
        if(s == ksNDUndefined) continue;
        for(int imode = 0; imode < kNReacModes; imode++) {
          ReacMode_t m = kNDReactionModes[isample][imode];
          if(m == kmUndefined) continue;

          for(int izone = 0; izone < kNMaxBinZones; izone++) {
            const char * name = Form("%s_%s_%s_z%d", 
              util::AsString(b).c_str(), util::AsString(s).c_str(), util::AsString(m).c_str(), izone);
            // get binning
            const int n_enu_reco_bins = util::NumErecoBins(s,izone);
            const int n_y_reco_bins   = util::NumYrecoBins(s,izone);
            if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
            const double * enu_reco_bins = util::ErecoBinEdges(s,izone);
            const double * y_reco_bins   = util::YrecoBinEdges(s,izone);
            // create slices of the PDF components (function of Ereco, for given yreco bin)
            TH1D * htot = new TH1D("htot", 
               "VALOR/LBNx ND PDF component: Ereco spectrum = f(beam,sample,mode,zone)", n_enu_reco_bins, enu_reco_bins);
            htot->SetName(Form("%s_%s_%s",tag, "pdfcs_ob_rf",name) );
            htot->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
            htot->GetYaxis()->SetTitle(Form("Number of events /bin /%f POT", fPOT[ibeam]));
            for(int iy = 0; iy < n_y_reco_bins; iy++) {
              TH1D * h = new TH1D("h",
                  Form("VALOR/LBNx ND PDF component slice: Ereco spectrum = f(beam,sample,mode,zone) for y in [%f,%f]", 
                       y_reco_bins[iy],y_reco_bins[iy+1]),
                  n_enu_reco_bins, enu_reco_bins);
              h->SetName(Form("%s_%s_%s_y%d",tag, "pdfcs_ob_rf",name,iy) );
              h->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
              h->GetYaxis()->SetTitle(Form("Number of events /bin /%f POT", fPOT[ibeam]));
              for(int ier = 0; ier < n_enu_reco_bins; ier++) {
                double val = fMCPDFComp[ibeam][isample][imode][izone]->GetEntry(ier,iy);
                h->SetBinContent(ier+1, val);
                htot->SetBinContent(ier+1, htot->GetBinContent(ier+1) + val);
              }//ier
              // add to obj array and clean-up 
              array->Add(h);
              //delete h; ??? MEM LEAK??
            }//iy         
            array->Add(htot);
            //delete htot; ??? MEM LEAK??
          }//izone

          if(opt.find("+SB") != string::npos) {
            const char * name = Form("%s_%s_%s", 
              util::AsString(b).c_str(), util::AsString(s).c_str(), util::AsString(m).c_str());
            // create slices of the PDF components (function of Ereco, for given yreco bin)
            const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(s);
            TH1D * htot = new TH1D("htot", 
               "VALOR/LBNx ND PDF component: Ereco spectrum = f(beam,sample,mode)", kNErecoBinsSb, kErecoBinEdgesSb);
            htot->SetName(Form("%s_%s_%s",tag, "pdfcs_sb_rf",name) );
            htot->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
            htot->GetYaxis()->SetTitle(Form("Number of events /bin /%f POT", fPOT[ibeam]));
            for(int iy = 0; iy < kNYrecoBinsSb; iy++) {
              TH1D * h = new TH1D("h",
                  Form("VALOR/LBNx ND PDF component slice: Ereco spectrum = f(beam,sample,mode) for y in [%f,%f]", 
                       y_reco_bin_edges_sb[iy], y_reco_bin_edges_sb[iy+1]),
                  kNErecoBinsSb, kErecoBinEdgesSb);
              h->SetName(Form("%s_%s_%s_y%d",tag, "pdfcs_sb_rf",name,iy) );
              h->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
              h->GetYaxis()->SetTitle(Form("Number of events /bin /%f POT", fPOT[ibeam]));
              for(int ier = 0; ier < kNErecoBinsSb; ier++) {
                double val = fMCPDFSbComp[ibeam][isample][imode]->GetEntry(ier,iy);
                h->SetBinContent(ier+1, val);
                htot->SetBinContent(ier+1, htot->GetBinContent(ier+1) + val);
              }//ier
              // add to obj array and clean-up 
              array->Add(h);
              //delete h; ??? MEM LEAK??
            }//iy         
            array->Add(htot);
            //delete htot; ??? MEM LEAK??
          }//+SB?

        }//imode
      }//isample
    }//ibeam
  }//pdfcs_rf


  //
  // Write out the slices of the total PDF (bare ROOT format)
  //

  if(opt.find("pdfts_rf") != string::npos) {
    for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
      BeamConf_t b = kNDBeamConf[ibeam];
      if(b == kbUndefined) continue;
      for(int isample = 0; isample < kNNDSamples; isample++) {
        NDSample_t s = kNDSample[isample];
        if(s == ksNDUndefined) continue;

        for(int izone = 0; izone < kNMaxBinZones; izone++) {
          const char * name = Form("%s_%s_z%d", 
            util::AsString(b).c_str(), util::AsString(s).c_str(), izone);
          // get binning
          const int n_enu_reco_bins = util::NumErecoBins(s,izone);
          const int n_y_reco_bins   = util::NumYrecoBins(s,izone);
          if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
          const double * enu_reco_bins = util::ErecoBinEdges(s,izone);
          const double * y_reco_bins   = util::YrecoBinEdges(s,izone);
          // create slices of the total PDF (function of Ereco, for given yreco bin)
          TH1D * htot = new TH1D("htot", 
              "VALOR/LBNx ND PDF: Ereco spectrum = f(beam,sample,zone)", n_enu_reco_bins, enu_reco_bins);
          htot->SetName(Form("%s_%s_%s",tag, "pdfts_ob_rf",name) );
          htot->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
          htot->GetYaxis()->SetTitle(Form("Number of events /bin /%f POT", fPOT[ibeam]));
          for(int iy = 0; iy < n_y_reco_bins; iy++) {
            TH1D * h = new TH1D("h",
                Form("VALOR/LBNx ND PDF slice: Ereco spectrum = f(beam,sample,zone) for y in [%f,%f]", 
                     y_reco_bins[iy],y_reco_bins[iy+1]),
                n_enu_reco_bins, enu_reco_bins);
            h->SetName(Form("%s_%s_%s_y%d",tag, "pdfts_ob_rf",name,iy) );
            h->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
            h->GetYaxis()->SetTitle(Form("Number of events /bin /%f POT", fPOT[ibeam]));
            for(int ier = 0; ier < n_enu_reco_bins; ier++) {
              double val = fMCPDFTot[ibeam][isample][izone]->GetEntry(ier,iy);
              h->SetBinContent(ier+1, val);
              htot->SetBinContent(ier+1, htot->GetBinContent(ier+1) + val);
            }//ier
            // add to obj array and clean-up 
            array->Add(h);
            //delete h; ??? MEM LEAK??      
          }//iy         
          array->Add(htot);
          //delete htot; ??? MEM LEAK??      
        }//izone

        if(opt.find("+SB") != string::npos) {
          const char * name = Form("%s_%s", 
            util::AsString(b).c_str(), util::AsString(s).c_str());
          // create slices of the total PDF (function of Ereco, for given yreco bin)
          const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(s);
          TH1D * htot = new TH1D("htot", 
              "VALOR/LBNx ND PDF: Ereco spectrum = f(beam,sample)", kNErecoBinsSb, kErecoBinEdgesSb);
          htot->SetName(Form("%s_%s_%s",tag, "pdfts_sb_rf",name) );
          htot->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
          htot->GetYaxis()->SetTitle(Form("Number of events /bin /%f POT", fPOT[ibeam]));
          for(int iy = 0; iy < kNYrecoBinsSb; iy++) {
            TH1D * h = new TH1D("h",
                Form("VALOR/LBNx ND PDF slice: Ereco spectrum = f(beam,sample) for y in [%f,%f]", 
                     y_reco_bin_edges_sb[iy], y_reco_bin_edges_sb[iy+1]),
                kNErecoBinsSb, kErecoBinEdgesSb);
            h->SetName(Form("%s_%s_%s_y%d",tag, "pdfts_sb_rf",name,iy) );
            h->GetXaxis()->SetTitle("Reconstructed E_{#nu} (GeV)");
            h->GetYaxis()->SetTitle(Form("Number of events /bin /%f POT", fPOT[ibeam]));
            for(int ier = 0; ier < kNErecoBinsSb; ier++) {
              double val = fMCPDFSbTot[ibeam][isample]->GetEntry(ier,iy);
              h->SetBinContent(ier+1, val);
              htot->SetBinContent(ier+1, htot->GetBinContent(ier+1) + val);
            }//ier
            // add to obj array and clean-up 
            array->Add(h);
            //delete h; ??? MEM LEAK??
          }//iy         
          array->Add(htot);
          //delete htot; ??? MEM LEAK??
        }//+SB?

      }//isample
    }//ibeam
  }//pdfts_rf

  return true;
}
//________________________________________________________________________________________
bool NDModel::Write(
  const char * filename, const char * tag, Option_t * write_opt, Option_t * file_opt)
{
  LOG("NDModel",pNOTICE) << "Writing results to file: [" << filename << "]";

  TObjArray * array = new TObjArray();
  this->Write(array,tag,write_opt);

  Option_t * used_file_opt = (file_opt == 0) ? "recreate" : file_opt;
  TFile f(filename, used_file_opt);
  array->Write();
  f.Close();

  return true;
}
//________________________________________________________________________________________
double NDModel::GetFitStatisticPenalty (Option_t * /*opt*/) const
{
  double Sp = 0;

  for(int ip = 0; ip < kNNDFitParams; ip++) {
      PhysParamId_t p = kNDFitParam[ip];
      if(p == kPhypUndefined) continue;
      double sig = kNDFitParamAPrioriFracError[ip];
      double val = fPhysHypothesis.CurrValue(p);
      double def = 1;
      double dSp = TMath::Power((val-def)/sig, 2.);
      Sp += dSp;
  }//ip

  LOG("NDModel",pDEBUG) << "Current fit statistic (systematic term) = " << Sp;

  return Sp;
}
//________________________________________________________________________________________
//
//
// Private methods:
//
//________________________________________________________________________________________

void NDModel::Init(void)
{
  LOG("NDModel",pDEBUG) << "Initializing...";

  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
   for(int isample = 0; isample < kNNDSamples; isample++) {
     for(int imode = 0; imode < kNReacModes; imode++) {

       // MC templates (simple binning)
       fMCTSbNom  [ibeam][isample][imode] = 0;
       fMCTSbTun  [ibeam][isample][imode] = 0;
       fMCTSbSys  [ibeam][isample][imode] = 0;
       fMCTSbFin  [ibeam][isample][imode] = 0;
       fMCTSbNull [ibeam][isample][imode] = true;
       // PDF (simple binning)
       fMCPDFSbComp [ibeam][isample][imode] = 0;
       if(imode == 0) {
         fMCPDFSbTot     [ibeam][isample] = 0;
         fMCPDFSbTotNull [ibeam][isample] = true;
       }

       for(int izone = 0; izone < kNMaxBinZones; izone++) {
         // MC templates
         fMCTNom  [ibeam][isample][imode][izone] = 0;
         fMCTTun  [ibeam][isample][imode][izone] = 0;
         fMCTSys  [ibeam][isample][imode][izone] = 0;
         fMCTFin  [ibeam][isample][imode][izone] = 0;
         fMCTNull [ibeam][isample][imode][izone] = true;
         // PDF
         fMCPDFComp [ibeam][isample][imode][izone] = 0;
         if(imode == 0) {
           fMCPDFTot     [ibeam][isample][izone] = 0;
           fMCPDFTotNull [ibeam][isample][izone] = true;
         }
       }//izone

     }//imode
   }//isample
  }//ibeam

  fUseMCDST = false;
  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
    fPOT  [ibeam] = 0;
    fMCDST[ibeam] = 0;
  }//ibeam

//  for(int ip = 0; ip < conv::kNNDFitParams; ip++) {
//    fPhysParamCurrVal[ip] = 0;
//    fPhysParamFracErr[ip] = 0;
//  }

  fArrIdx = util::NDArrIdx::Instance();
}
//________________________________________________________________________________________
void NDModel::Book(void)
{
  LOG("NDModel",pDEBUG) << "Booking...";

  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
    BeamConf_t b = kNDBeamConf[ibeam];
    if(b == kbUndefined) continue;
    for(int isample = 0; isample < kNNDSamples; isample++) {
      NDSample_t s = kNDSample[isample];
      if(s == ksNDUndefined) continue;
      for(int imode = 0; imode < kNReacModes; imode++) {
        ReacMode_t m = kNDReactionModes[isample][imode];
        if(m == kmUndefined) continue;

        const int n_enu_true_bins = util::NumEtrueBins(s);

        LOG("NDModel",pDEBUG) 
            << "Booking MC template (simple binning) for " 
            << "beam: "     << util::AsString(b) 
            << ", sample: " << util::AsString(s)
            << ", mode: "   << util::AsString(m); 

        // >> MC templates (simple binning)
        // (Note order of variables: reco first, true later)
        fMCTSbNull[ibeam][isample][imode] = false;
        fMCTSbNom [ibeam][isample][imode] = 
          new VALORArray(kNErecoBinsSb, kNYrecoBinsSb, n_enu_true_bins);
        fMCTSbTun [ibeam][isample][imode] = 
          new VALORArray(kNErecoBinsSb, kNYrecoBinsSb, n_enu_true_bins);
        fMCTSbSys [ibeam][isample][imode] = 
          new VALORArray(kNErecoBinsSb, kNYrecoBinsSb, n_enu_true_bins);
        fMCTSbFin [ibeam][isample][imode] = 
          new VALORArray(kNErecoBinsSb, kNYrecoBinsSb, n_enu_true_bins);

        // >> PDF component
        fMCPDFSbComp[ibeam][isample][imode] = 
            new VALORArray(kNErecoBinsSb, kNYrecoBinsSb);           
        // >> PDF total
        // should get here for at least one imode value
        if(fMCPDFSbTotNull[ibeam][isample]) {              
           LOG("NDModel",pDEBUG) 
              << "Booking PDF (total / simple binning) for " 
              << "beam: "     << util::AsString(b) 
              << ", sample: " << util::AsString(s);
           fMCPDFSbTotNull [ibeam][isample] = false;
           fMCPDFSbTot     [ibeam][isample] = new VALORArray(kNErecoBinsSb, kNYrecoBinsSb); 
        }


        // Loop over zones
        for(int izone = 0; izone < kNMaxBinZones; izone++) {
           const int n_enu_reco_bins = util::NumErecoBins(s,izone);
           const int n_y_reco_bins   = util::NumYrecoBins(s,izone);
           if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;

           LOG("NDModel",pDEBUG) 
              << "Booking MC template for " 
              << "beam: "     << util::AsString(b) 
              << ", sample: " << util::AsString(s)
              << ", mode: "   << util::AsString(m) 
              << ", zone: "   << izone;
 
           // >> MC templates 
           // (Note order of variables: reco first, true later)
           fMCTNull[ibeam][isample][imode][izone] = false;
           fMCTNom [ibeam][isample][imode][izone] = 
             new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins);
           fMCTTun [ibeam][isample][imode][izone] = 
             new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins);
           fMCTSys [ibeam][isample][imode][izone] = 
             new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins);
           fMCTFin [ibeam][isample][imode][izone] = 
             new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins);

           // >> PDF component
           fMCPDFComp[ibeam][isample][imode][izone] = 
               new VALORArray(n_enu_reco_bins,n_y_reco_bins);           
           // >> PDF total
           // should get here for at least one imode value
           if(fMCPDFTotNull[ibeam][isample][izone]) {              
              LOG("NDModel",pDEBUG) 
                 << "Booking PDF (total) for " 
                 << "beam: "     << util::AsString(b) 
                 << ", sample: " << util::AsString(s)
                 << ", zone: "   << izone;

              fMCPDFTotNull [ibeam][isample][izone] = false;
              fMCPDFTot     [ibeam][isample][izone] = new VALORArray(n_enu_reco_bins,n_y_reco_bins);           
           }
        }//izone

      }//imode
    }//isample
  }//ibeam
}
//________________________________________________________________________________________
void NDModel::Clean(void)
{
  LOG("NDModel",pDEBUG) << "Cleaning-up...";

  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
    for(int isample = 0; isample < kNNDSamples; isample++) {
      for(int imode = 0; imode < kNReacModes; imode++) {

        if(!fMCTSbNull[ibeam][isample][imode]) {
            fMCTSbNull[ibeam][isample][imode] = true;
            // MC templates (simple binning)
            delete fMCTSbNom[ibeam][isample][imode];
            delete fMCTSbTun[ibeam][isample][imode];
            delete fMCTSbSys[ibeam][isample][imode];
            delete fMCTSbFin[ibeam][isample][imode];
            fMCTSbNom[ibeam][isample][imode] = 0;
            fMCTSbTun[ibeam][isample][imode] = 0;
            fMCTSbSys[ibeam][isample][imode] = 0;
            fMCTSbFin[ibeam][isample][imode] = 0;
            // PDF components
            delete fMCPDFSbComp[ibeam][isample][imode];
            fMCPDFSbComp[ibeam][isample][imode] = 0;
        }
        if(!fMCPDFSbTotNull[ibeam][isample]) {
            fMCPDFSbTotNull[ibeam][isample] = true;
              delete fMCPDFSbTot[ibeam][isample];
              fMCPDFSbTot[ibeam][isample] = 0;
        }

        for(int izone = 0; izone < kNMaxBinZones; izone++) {
          if(!fMCTNull[ibeam][isample][imode][izone]) {
              fMCTNull[ibeam][isample][imode][izone] = true;
              // MC templates
              delete fMCTNom[ibeam][isample][imode][izone];
              delete fMCTTun[ibeam][isample][imode][izone];
              delete fMCTSys[ibeam][isample][imode][izone];
              delete fMCTFin[ibeam][isample][imode][izone];
              fMCTNom[ibeam][isample][imode][izone] = 0;
              fMCTTun[ibeam][isample][imode][izone] = 0;
              fMCTSys[ibeam][isample][imode][izone] = 0;
              fMCTFin[ibeam][isample][imode][izone] = 0;
              // PDF components
              delete fMCPDFComp[ibeam][isample][imode][izone];
              fMCPDFComp[ibeam][isample][imode][izone] = 0;
          }
          if(!fMCPDFTotNull[ibeam][isample][izone]) {
              fMCPDFTotNull[ibeam][isample][izone] = true;
              delete fMCPDFTot[ibeam][isample][izone];
              fMCPDFTot[ibeam][isample][izone] = 0;
          }          
        }//izone

      }//imode
    }//isample
  }//ibeam

  if(fUseMCDST) {
    for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
      if (fMCDST[ibeam]) {
        delete fMCDST[ibeam];
        fMCDST[ibeam] = 0;
      }
    }
  }
}
//________________________________________________________________________________________
void NDModel::Zero(void)
{
  LOG("NDModel",pDEBUG) << "Zeroing MC templates and/or PDFs...";

  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
   for(int isample = 0; isample < kNNDSamples; isample++) {
     for(int imode = 0; imode < kNReacModes; imode++) {

        if(!fMCTSbNull[ibeam][isample][imode]) {
            fMCTSbNom   [ibeam][isample][imode] -> SetAll(0.);
            fMCTSbTun   [ibeam][isample][imode] -> SetAll(0.);
            fMCTSbSys   [ibeam][isample][imode] -> SetAll(0.);
            fMCTSbFin   [ibeam][isample][imode] -> SetAll(0.);
            fMCPDFSbComp[ibeam][isample][imode] -> SetAll(0.);
        }
        if(!fMCPDFSbTotNull[ibeam][isample]) {
              fMCPDFSbTot[ibeam][isample] -> SetAll(0.);
        }

        for(int izone = 0; izone < kNMaxBinZones; izone++) {
          if(!fMCTNull[ibeam][isample][imode][izone]) {
              fMCTNom   [ibeam][isample][imode][izone] -> SetAll(0.);
              fMCTTun   [ibeam][isample][imode][izone] -> SetAll(0.); 
              fMCTSys   [ibeam][isample][imode][izone] -> SetAll(0.);
              fMCTFin   [ibeam][isample][imode][izone] -> SetAll(0.);
              fMCPDFComp[ibeam][isample][imode][izone] -> SetAll(0.);
          }
          if(!fMCPDFTotNull[ibeam][isample][izone]) {
              fMCPDFTot[ibeam][isample][izone] -> SetAll(0.);
          }          
        }//izone

     }//imode
   }//isample
  }//ibeam
}
//________________________________________________________________________________________
void NDModel::Fill(TTree * t, int ibeam)
{
  BeamConf_t b = kNDBeamConf[ibeam];

  LOG("NDModel",pDEBUG) 
     << "Filling-in MC templates for beam configuration: " << util::AsString(b);

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
  TBranch * bSample   = t->GetBranch("sample");         // selected ND sample
  TBranch * bReacMode = t->GetBranch("reactionmode");   // reaction mode
  TBranch * bEnuTrue  = t->GetBranch("Ev");             // true energy (GeV)
  TBranch * bEnuReco  = t->GetBranch("Ev_reco");        // reco energy (GeV)
  TBranch * byReco    = t->GetBranch("y_reco");         // reco inelasticity y
  TBranch * bWghtPOT  = t->GetBranch("POTWeight");      // weight for 1E+20 POT exposure

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
  LOG("NDModel",pINFO) << "Input VALOR DST has " << nev << " entries";

  for(Long_t iev = 0; iev < nev; iev++) 
  {
     t->GetEntry(iev);

     if(iev%(nev/20)==0) {
       double pct = (100 * (double)(iev+1)) / (double)nev;
       LOG("NDModel",pNOTICE) << "Reading MC DST: " << TMath::Nint(pct) << "% done";
     }

     // Get sample index
     NDSample_t s = util::NDSampleFromInt(sample);
     if(s == ksNDUndefined) {
       LOG("NDModel",pWARN) 
          << " ** Undefined sample ID used in MC event: " << iev
          << " (value stored in DST: " << sample << ")";
       //exit(1);
     }
     // NOTE - HACK
     if(s == ksNDNuMuCC2piC) {
       LOG("HACK",pNOTICE) 
         << "MC event: " << iev << " belongs to sample: " << util::AsString(s) 
         << " not considered separately. Bundle in sample: " << util::AsString(ksNDNuMuCCoth);
       s = ksNDNuMuCCoth;
     }
     int isample = fArrIdx->NDSampleIdx(s);
     if(isample < 0) {
       // fine, we do not indlude all samples in the fit
       LOG("NDModel",pDEBUG) 
         << "Ignoring MC event: " << iev 
         << " (sample ID: " << util::AsString(s) << " not included in current fit)";
       continue;
     }

     // Get reaction mode index
     ReacMode_t m = util::ReacModeFromInt(reac_mode); 
     if(m == kmUndefined) {
       LOG("NDModel",pFATAL) 
          << " ** Undefined reaction mode ID used in MC event: " << iev
          << " (value stored in DST: " << reac_mode << ")";
       exit(1);
     }
     int imode = fArrIdx->NDReacModeIdx(s, m);
     if(imode < 0) {
       // For a given sample we should consider a complete list of
       // true reaction modes (otherwise there are true contributions to the
       // event sample which are not taken into account).
       LOG("NDModel",pFATAL) 
         << " ** Ignoring MC event: " << iev 
         << " (ignoring contribution to sample: " << util::AsString(s) << " from mode: " << util::AsString(m) << " ?)";
       exit(1);
     }

     // Get bin zone index
     int izone = util::BinZone(s, enu_reco, y_reco);
     if(izone < 0) {
//     LOG("NDModel",pFATAL) - turn that to fatal after binning optimization is done
       LOG("NDModel",pWARN) 
         << " ** No bin zone for MC event: " << iev 
         << " (" << util::AsString(s) << "/" << util::AsString(m) 
         << ", enu_reco = " << enu_reco << " GeV, " << " y_reco = " << y_reco << ")";
//     exit(1);
       continue;
     }

     bool is_null = fMCTNull[ibeam][isample][imode][izone];
     if(is_null) {
       LOG("NDModel",pFATAL) 
         << "** Null MC template for sample: " << util::AsString(s) 
         << ", mode: " << util::AsString(m) << ", bin zone = " << izone << " ??";
       exit(1);
     }
     bool is_null_sb = fMCTSbNull[ibeam][isample][imode];
     if(is_null_sb) {
       LOG("NDModel",pFATAL) 
         << "** Null MC template (simple binning) for sample: " << util::AsString(s) 
         << ", mode: " << util::AsString(m) << " ??";
       exit(1);
     }

     // check Ereco, yreco and Etrue values against built-in limits
     if(enu_reco < kErecoMin || enu_reco > kErecoMax) {
        LOG("NDModel",pWARN) 
           << "MC event: " << iev << " has reconstructed energy = " << enu_reco 
           << " GeV, range used: [" << kErecoMin << ", " << kErecoMax << "] GeV";
     }
     if(y_reco < kYrecoMin || y_reco > kYrecoMax) {
        LOG("NDModel",pWARN) 
           << "MC event: " << iev << " has reconstructed inelasticity y = " << y_reco 
           << ", range used: [" << kYrecoMin << ", " << kYrecoMax << "]";
     }
     if(enu_true < kEtrueMin || enu_true > kEtrueMax) {
        LOG("NDModel",pWARN) 
           << "MC event: " << iev << " has true energy = " << enu_true 
           << " GeV, range used: [" << kEtrueMin << ", " << kEtrueMax << "] GeV";
     }

     // Get enu_true, enu_reco, y_reco array indices
     const int n_enu_true_bins = util::NumEtrueBins(s);
     const int n_enu_reco_bins = util::NumErecoBins(s,izone);
     const int n_y_reco_bins   = util::NumYrecoBins(s,izone);

     const double * enu_true_bin_edges  = util::EtrueBinEdges(s);
     const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(s);
     const double * enu_reco_bin_edges  = util::ErecoBinEdges(s,izone);
     const double * y_reco_bin_edges    = util::YrecoBinEdges(s,izone);

     // work-out the index using the bin-edge array defining the variable-size binning scheme
     int ienu_true    = TMath::BinarySearch(1+(Long_t)n_enu_true_bins, enu_true_bin_edges, enu_true);
     int ienu_reco    = TMath::BinarySearch(1+(Long_t)n_enu_reco_bins, enu_reco_bin_edges, enu_reco);
     int iy_reco      = TMath::BinarySearch(1+(Long_t)n_y_reco_bins,   y_reco_bin_edges,   y_reco  );
     // repeat, finding the indices for the template versions using a simple binning scheme
     int ienu_reco_sb = TMath::BinarySearch(1+(Long_t)kNErecoBinsSb, kErecoBinEdgesSb,    enu_reco);
     int iy_reco_sb   = TMath::BinarySearch(1+(Long_t)kNYrecoBinsSb, y_reco_bin_edges_sb, y_reco  );

     // Exposure for assumed data - Weight MC templates to that exposure
     double data_pot = fPOT[ibeam];
 
     double mc_pot = wght_pot;
     assert(wght_pot>0.);

     // Calculate POT weight (assumed data exposure) / (generated MC exposure)
     //double wght = data_pot/mc_pot;
     double wght = data_pot*mc_pot;

     if(fNDFiducialMass > 0) {
       wght = wght*fNDFiducialMass;
     }

     // Add `nom' array entry (and init `tun', `sys' and `fin' arrays = `nom')

     double curr_wght = fMCTNom[ibeam][isample][imode][izone]->GetEntry(ienu_reco, iy_reco, ienu_true);
     curr_wght += wght;
     fMCTNom[ibeam][isample][imode][izone]->SetEntry(curr_wght, ienu_reco, iy_reco, ienu_true);
     fMCTTun[ibeam][isample][imode][izone]->SetEntry(curr_wght, ienu_reco, iy_reco, ienu_true);
     fMCTSys[ibeam][isample][imode][izone]->SetEntry(curr_wght, ienu_reco, iy_reco, ienu_true);
     fMCTFin[ibeam][isample][imode][izone]->SetEntry(curr_wght, ienu_reco, iy_reco, ienu_true);     

     double curr_wght_sb = fMCTSbNom[ibeam][isample][imode]->GetEntry(ienu_reco_sb, iy_reco_sb, ienu_true);
     curr_wght_sb += wght;
     fMCTSbNom[ibeam][isample][imode]->SetEntry(curr_wght_sb, ienu_reco_sb, iy_reco_sb, ienu_true);
     fMCTSbTun[ibeam][isample][imode]->SetEntry(curr_wght_sb, ienu_reco_sb, iy_reco_sb, ienu_true);
     fMCTSbSys[ibeam][isample][imode]->SetEntry(curr_wght_sb, ienu_reco_sb, iy_reco_sb, ienu_true);
     fMCTSbFin[ibeam][isample][imode]->SetEntry(curr_wght_sb, ienu_reco_sb, iy_reco_sb, ienu_true);     
  }//iev 
}
//________________________________________________________________________________________
void NDModel::ApplyTuning(void)
{
// This method maps nom -> tun MC templates
// No external tuning available for the time-being

}
//________________________________________________________________________________________
void NDModel::ApplySystematics(Option_t * /*opt*/)
{
// This method maps tun -> sys MC templates.
// Applying detector systematics and uncorrelated flux/cross-section systematics.

/*
  bool update_mct_sb = false;
  if(option) {
    string opt = option;
    if(opt.find("+SB") != string::npos) {
      update_mct_sb = true;
    }
  }

  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
   for(int isample = 0; isample < kNNDSamples; isample++) {
    for(int imode = 0; imode < kNReacModes; imode++) {


      for(int izone = 0; izone < kNMaxBinZones; izone++) {
         bool is_null = fMCTNull[ibeam][isample][imode][izone];
         if(!is_null) {
             

         }//!null
      }//izone


    }//imode
   }//isample
  }//ibeam
*/

}
//________________________________________________________________________________________
void NDModel::ApplyPhysics(Option_t * option)
{
// This method maps sys -> fin MC templates.
// Applying correlated flux and cross-section systematics

  LOG("NDModel",pINFO) 
     << "Applying physics params (option: " 
     << ((option) ? option : "")
     << ")";

  double epsilon = 1E-4;

  bool update_mct_sb = false;
  if(option) {
    string opt = option;
    if(opt.find("+SB") != string::npos) {
      update_mct_sb = true;
    }
  }

  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
    BeamConf_t b = kNDBeamConf[ibeam];
    if(b == kbUndefined) continue;
    for(int isample = 0; isample < kNNDSamples; isample++) {
      NDSample_t s = kNDSample[isample];
      if(s == ksNDUndefined) continue;
      for(int imode = 0; imode < kNReacModes; imode++) {
        ReacMode_t m = kNDReactionModes[isample][imode];
        if(m == kmUndefined) continue;

        const int n_enu_true_bins = util::NumEtrueBins(s);
        const double * enu_true_bin_edges = util::EtrueBinEdges(s);

        LOG("NDModel",pDEBUG) 
           << "Handing templates for: " 
           << util::AsString(b) << ", " << util::AsString(s) << ", " << util::AsString(m);

        LOG("NDModel",pDEBUG) 
           << "Initializing `fin' templates to the `sys' ones";

        for(int izone = 0; izone < kNMaxBinZones; izone++) {
          bool is_null = fMCTNull[ibeam][isample][imode][izone];
          if(is_null) continue;
          const int n_enu_reco_bins = util::NumErecoBins(s,izone);
          const int n_y_reco_bins   = util::NumYrecoBins(s,izone);
          // copy sys -> fin MC templates
          for(int iet = 0; iet < n_enu_true_bins; iet++) {
            for(int ier = 0; ier < n_enu_reco_bins; ier++) {
               for(int iyr = 0; iyr < n_y_reco_bins; iyr++) {
                 double val = fMCTSys[ibeam][isample][imode][izone]->GetEntry(ier,iyr,iet);
                 fMCTFin[ibeam][isample][imode][izone]->SetEntry(val,ier,iyr,iet);
               }//iyr: yreco bins
            }//ier: Ereco bins
          }//iet: Etrue bins

          LOG("NDModel",pDEBUG) 
             << "Applying Etrue-dependent params";

          // first apply Etrue-dependent params
          for(int ip = 0; ip < kNNDFitParams; ip++) {
             bool apply = kNDApplyFitParamToTemplate[ibeam][imode][ip];
             if(!apply) continue;
             bool enu_true_dep = kNDFitParamEtrueDependence[ip];
             if(!enu_true_dep) continue;
             PhysParamId_t p = kNDFitParam[ip];
             if(p == kPhypUndefined) continue;
             double f = fPhysHypothesis.CurrValue(p);
             f = TMath::Max(0.,f);
             bool tweaked = TMath::Abs(f-1) > epsilon;
             if(!tweaked) continue;
             const double enu_true_min = kNDFitParamEtrueRange[ip][0];
             const double enu_true_max = kNDFitParamEtrueRange[ip][1];     
             int ienu_true_min = TMath::BinarySearch((Long_t)n_enu_true_bins, enu_true_bin_edges, enu_true_min+epsilon);
             int ienu_true_max = TMath::BinarySearch((Long_t)n_enu_true_bins, enu_true_bin_edges, enu_true_max-epsilon);
             LOG("NDModel",pDEBUG) 
                << "Applying parameter: " << util::AsString(p) << " with value = " << f 
                << " in Etrue bin range: [" << ienu_true_min << ", " << ienu_true_max << "]";
             for(int iet = ienu_true_min; iet <= ienu_true_max; iet++) {
               for(int ier = 0; ier < n_enu_reco_bins; ier++) {
                 for(int iyr = 0; iyr < n_y_reco_bins; iyr++) {
                    double val_old = fMCTFin[ibeam][isample][imode][izone]->GetEntry(ier,iyr,iet);
                    double val_new = val_old * f;
                    fMCTFin[ibeam][isample][imode][izone]->SetEntry(val_new,ier,iyr,iet);
                    LOG("NDModel",pDEBUG) 
                      << "MCT[" << ibeam << ", " << isample << ", " << imode << ", " << izone << "] = " 
                      << val_old << " --> " << val_new;

                 }//iyr: yreco bins
               }//ier: Ereco bins
             }//iet: Etrue bins
          }//ip

          LOG("NDModel",pDEBUG) 
             << "Applying Etrue-independent params";

          // then apply the non-Etrue-dependent factors (bundle them together to loop over the
          // Ereco,yreco,Etrue bins just once)
          double fnoEt = 1.;
          for(int ip = 0; ip < kNNDFitParams; ip++) {
             bool apply = kNDApplyFitParamToTemplate[ibeam][imode][ip];
             if(!apply) continue;
             bool enu_true_dep = kNDFitParamEtrueDependence[ip];
             if(enu_true_dep) continue;
             PhysParamId_t p = kNDFitParam[ip];
             if(p == kPhypUndefined) continue;
             double f = fPhysHypothesis.CurrValue(p);
           //double f = 1 + fPhysParamCurrVal[ip] * fPhysParamFracErr[ip];
             LOG("NDModel",pDEBUG) 
                << "Applying parameter: " << util::AsString(p) << " with value = " << f;
             fnoEt *= f;
          }//ip
          fnoEt = TMath::Max(0.,fnoEt);
          for(int iet = 0; iet < n_enu_true_bins; iet++) {
            for(int ier = 0; ier < n_enu_reco_bins; ier++) {
              for(int iyr = 0; iyr < n_y_reco_bins; iyr++) {
                 double val = fMCTFin[ibeam][isample][imode][izone]->GetEntry(ier,iyr,iet);
                 val *= fnoEt;
                 fMCTFin[ibeam][isample][imode][izone]->SetEntry(val,ier,iyr,iet);
              }//iyr: yreco bins
            }//ier: Ereco bins
          }//iet: Etrue bins
        }//izone


        if(update_mct_sb) {
          bool is_null = fMCTSbNull[ibeam][isample][imode];
          if(is_null) continue;
          // copy sys -> fin MC templates
          for(int iet = 0; iet < n_enu_true_bins; iet++) {
            for(int ier = 0; ier < kNErecoBinsSb; ier++) {
               for(int iyr = 0; iyr < kNYrecoBinsSb; iyr++) {
                 double val = fMCTSbSys[ibeam][isample][imode]->GetEntry(ier,iyr,iet);
                 fMCTSbFin[ibeam][isample][imode]->SetEntry(val,ier,iyr,iet);
               }//iyr: yreco bins
            }//ier: Ereco bins
          }//iet: Etrue bins

          // first apply Etrue-dependent params
          for(int ip = 0; ip < kNNDFitParams; ip++) {
             double epsilon = 1E-4;
             bool apply = kNDApplyFitParamToTemplate[ibeam][imode][ip];
             if(!apply) continue;
             bool enu_true_dep = kNDFitParamEtrueDependence[ip];
             if(!enu_true_dep) continue;
             PhysParamId_t p = kNDFitParam[ip];
             if(p == kPhypUndefined) continue;
             double f = fPhysHypothesis.CurrValue(p);
           //double f = 1 + fPhysParamCurrVal[ip] * fPhysParamFracErr[ip];
             f = TMath::Max(0.,f);
             bool tweaked = TMath::Abs(f-1) > epsilon;
             if(!tweaked) continue;
             const double enu_true_min = kNDFitParamEtrueRange[ip][0];
             const double enu_true_max = kNDFitParamEtrueRange[ip][1];     
             int ienu_true_min = TMath::BinarySearch((Long_t)n_enu_true_bins, enu_true_bin_edges, enu_true_min+epsilon);
             int ienu_true_max = TMath::BinarySearch((Long_t)n_enu_true_bins, enu_true_bin_edges, enu_true_max-epsilon);
             for(int iet = ienu_true_min; iet <= ienu_true_max; iet++) {
               for(int ier = 0; ier < kNErecoBinsSb; ier++) {
                 for(int iyr = 0; iyr < kNYrecoBinsSb; iyr++) {
                    double val = fMCTSbFin[ibeam][isample][imode]->GetEntry(ier,iyr,iet);
                    val *= f;
                    fMCTSbFin[ibeam][isample][imode]->SetEntry(val,ier,iyr,iet);
                 }//iyr: yreco bins
               }//ier: Ereco bins
             }//iet: Etrue bins
          }//ip

          // then apply the non-Etrue-dependent factors (bundle them together to loop over the
          // Ereco,yreco,Etrue bins just once)
          double fnoEt = 1.;
          for(int ip = 0; ip < kNNDFitParams; ip++) {
             bool apply = kNDApplyFitParamToTemplate[ibeam][imode][ip];
             if(!apply) continue;
             bool enu_true_dep = kNDFitParamEtrueDependence[ip];
             if(enu_true_dep) continue;
             PhysParamId_t p = kNDFitParam[ip];
             if(p == kPhypUndefined) continue;
             double f = fPhysHypothesis.CurrValue(p);
             f = TMath::Max(0.,f);
             bool tweaked = TMath::Abs(f-1) > epsilon;
             if(!tweaked) continue;
             fnoEt *= f;
          }//ip
          fnoEt = TMath::Max(0.,fnoEt);
          for(int iet = 0; iet < n_enu_true_bins; iet++) {
            for(int ier = 0; ier < kNErecoBinsSb; ier++) {
              for(int iyr = 0; iyr < kNYrecoBinsSb; iyr++) {
                 double val = fMCTSbFin[ibeam][isample][imode]->GetEntry(ier,iyr,iet);
                 val *= fnoEt;
                 fMCTSbFin[ibeam][isample][imode]->SetEntry(val,ier,iyr,iet);
              }//iyr: yreco bins
            }//ier: Ereco bins
          }//iet: Etrue bins
        }//update_mct_sb?

      }//imode
    }//isample
  }//ibeam
}
//________________________________________________________________________________________
void NDModel::UpdatePDFs(Option_t * option)
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
  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
    BeamConf_t b = kNDBeamConf[ibeam];
    if(b == kbUndefined) continue;
    for(int isample = 0; isample < kNNDSamples; isample++) {
      NDSample_t s = kNDSample[isample];
      if(s == ksNDUndefined) continue;
      const int n_enu_true_bins = util::NumEtrueBins(s);
      for(int imode = 0; imode < kNReacModes; imode++) {
        ReacMode_t m = kNDReactionModes[isample][imode];
        if(m == kmUndefined) continue;


        for(int izone = 0; izone < kNMaxBinZones; izone++) {
          bool is_null = fMCTNull[ibeam][isample][imode][izone];
          if(is_null) continue;
          const int n_enu_reco_bins = util::NumErecoBins(s,izone);
          const int n_y_reco_bins   = util::NumYrecoBins(s,izone);
          for(int ier=0; ier < n_enu_reco_bins; ier++) {
            for(int iyr=0; iyr < n_y_reco_bins; iyr++) {
               double sum = 0.;
               for(int iet=0; iet < n_enu_true_bins; iet++) {
                 sum += fMCTFin[ibeam][isample][imode][izone]->GetEntry(ier,iyr,iet);
               }//iet
               fMCPDFComp[ibeam][isample][imode][izone]->SetEntry(sum, ier, iyr);
            }//iyr
          }//ier
        }//izone

        if(update_mct_sb) {
          bool is_null = fMCTSbNull[ibeam][isample][imode];
          if(is_null) continue;
          for(int ier=0; ier < kNErecoBinsSb; ier++) {
            for(int iyr=0; iyr < kNYrecoBinsSb; iyr++) {
               double sum = 0.;
               for(int iet=0; iet < n_enu_true_bins; iet++) {
                 sum += fMCTSbFin[ibeam][isample][imode]->GetEntry(ier,iyr,iet);
               }//iet
               fMCPDFSbComp[ibeam][isample][imode]->SetEntry(sum, ier, iyr);
            }//iyr
          }//ier
        }//update_mct_sb?

      }//imode
    }//isample
  }//ibeam

  //
  // Now integrate the above-computed PDF components over the true reaction mode
  // and calculate the total PDF
  //
  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
    BeamConf_t b = kNDBeamConf[ibeam];
    if(b == kbUndefined) continue;
    for(int isample = 0; isample < kNNDSamples; isample++) {
      NDSample_t s = kNDSample[isample];
      if(s == ksNDUndefined) continue;

      for(int izone = 0; izone < kNMaxBinZones; izone++) {
         const int n_enu_reco_bins = util::NumErecoBins(s,izone);
         const int n_y_reco_bins   = util::NumYrecoBins(s,izone);
         for(int ier=0; ier < n_enu_reco_bins; ier++) {
           for(int iyr=0; iyr < n_y_reco_bins; iyr++) {
              double sum = 0.;
              for(int imode = 0; imode < kNReacModes; imode++) {
                 ReacMode_t m = kNDReactionModes[isample][imode];
                 if(m == kmUndefined) continue;
                 bool is_null = fMCTNull[ibeam][isample][imode][izone];
                 if(is_null) continue;
                 sum += fMCPDFComp[ibeam][isample][imode][izone]->GetEntry(ier, iyr);
              }//imode
              fMCPDFTot[ibeam][isample][izone]->SetEntry(sum, ier, iyr);
           }//iyr
         }//ier
      }//izone

      if(update_mct_sb) {
         for(int ier=0; ier < kNErecoBinsSb; ier++) {
           for(int iyr=0; iyr < kNYrecoBinsSb; iyr++) {
              double sum = 0.;
              for(int imode = 0; imode < kNReacModes; imode++) {
                 ReacMode_t m = kNDReactionModes[isample][imode];
                 if(m == kmUndefined) continue;
                 bool is_null = fMCTSbNull[ibeam][isample][imode];
                 if(is_null) continue;
                 sum += fMCPDFSbComp[ibeam][isample][imode]->GetEntry(ier, iyr);
              }//imode
              fMCPDFSbTot[ibeam][isample]->SetEntry(sum, ier, iyr);
           }//iyr
         }//ier
      }//update_mct_sb?

    }//isample
  }//ibeam
}
//________________________________________________________________________________________
