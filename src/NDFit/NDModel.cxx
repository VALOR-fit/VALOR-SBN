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

//why is this causing a crash??
//this->Zero();
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
       this->FillTemplates(fMCDST[ibeam], ibeam);
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
bool NDModel::Generate(const PhysHypothesis & ph)
{
  fPhysHypothesis.Copy(ph);
  //PhysHypothesis_t hyp = fPhysHypothesis.Hypothesis();

  LOG("NDModel",pINFO)  
     << "Generating model predictions for the input hypothesis: " 
     << fPhysHypothesis;

  this->ApplySystematics();  // `tun' MC templates --> `sys' MC templates
  this->ApplyPhysics();      // `sys' MC templates --> `fin' MC templates
  this->CalcPDFs();          // `fin' MC templates --> p.d.f

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
  PhysParamId_t /*syst*/, double /*twkdial*/, Option_t * /*opt*/)
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
bool NDModel::Generate (const FitParamList & fp)
{
  // extract the values of params driving the oscillation, decoherence or decay model
  PhysHypothesis ph(fp);

  // call the main Generate() method
  return this->Generate(ph);
}
//________________________________________________________________________________________
bool NDModel::Write(TObjArray * array, const char * tag, Option_t * write_opt)
{
//
// write_opt:
// - if null, store only what is needed for the fit (equiv. with write_opt = "pdft_va")
// - if "all", store everything listed below
// - include the string "mct_va" to write-out the MC templates
//   (functions of beam,sample,mode,zone,Ereco,yreco,Etrue - in VALORArray format)
// - include the string "pdfc_va" to write-out the PDF components 
//   (functions of beam,sample,mode,zone,Ereco,yreco - in VALORArray format)
// - include the string "pdfc_rt" to write out the above in bare ROOT format (TH1D, TH2D,....)
// - include the string "pdft_va" to write-out the total PDF 
//   (functions of beam,sample,zone,Ereco,yreco - in VALORArray format)
// - include the string "pdft_rt" to write-out the above in bare ROOT format
// - include the string "pdfts_rt" to write-out slices of the total PDF in bare ROOT format

  LOG("NDModel",pINFO) << "Writing results to input object array...";

  if(!array) {
     LOG("NDModel",pERROR) << "Null input object array.";
     return false;
  }

  valor::util::SetDefaultStyle();

  string opt = (write_opt) ? write_opt : "pdft_va";

  if(opt.find("all") != string::npos) {
    opt = "mct_va + pdfc_va + pdfc_rt + pdft_va + pdft_rt + pdfts_rt";
  }
  LOG("NDModel",pINFO) << "Write option: " << opt;

  //
  // Write out MC templates (VALORArray format)
  //

  if(opt.find("mct_va") != string::npos) {

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

             if(fNullMC[ibeam][isample][imode][izone]) continue;

             const char * name = Form("%s_%s_%s_z%d", 
                util::AsString(b).c_str(), util::AsString(s).c_str(), util::AsString(m).c_str(), izone);

             fMCTNom [ibeam][isample][imode][izone] -> SetName( Form("%s_%s_%s", tag, "mctnom_va", name) );
             fMCTTun [ibeam][isample][imode][izone] -> SetName( Form("%s_%s_%s", tag, "mcttun_va", name) );
             fMCTSys [ibeam][isample][imode][izone] -> SetName( Form("%s_%s_%s", tag, "mctsys_va", name) );
             fMCTFin [ibeam][isample][imode][izone] -> SetName( Form("%s_%s_%s", tag, "mctfin_va", name) );

             array -> Add ( fMCTNom [ibeam][isample][imode][izone] ); 
             array -> Add ( fMCTTun [ibeam][isample][imode][izone] ); 
             array -> Add ( fMCTSys [ibeam][isample][imode][izone] ); 
             array -> Add ( fMCTFin [ibeam][isample][imode][izone] );
          }//izone
        }//imode
      }//isample
    }//ibeam
  }//mct_va

  //
  // Write out the PDF components (VALORArray or bare ROOT format)
  //

  if(opt.find("pdfc_va") != string::npos || opt.find("pdfc_rt") != string::npos) {

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

             if(fNullMC[ibeam][isample][imode][izone]) continue;

             const char * name = Form("%s_%s_%s_z%d", 
                util::AsString(b).c_str(), util::AsString(s).c_str(), util::AsString(m).c_str(), izone);

             // in VALORArray format
             if (opt.find("pdfc_va") != string::npos) {
               fMCPDFComp [ibeam][isample][imode][izone]->SetName(Form("%s_%s_%s",tag,"pdfc_va",name));
               array->Add(fMCPDFComp[ibeam][isample][imode][izone]);
             }
             // in TH2D format
             if (opt.find("pdfc_rt") != string::npos) {
               // get binning
               const int n_enu_reco_bins = util::NumErecoBins(s,izone);
               const int n_y_reco_bins   = util::NumYrecoBins(s,izone);
               if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
               const double * enu_reco_bins = util::ErecoBinEdges(s,izone);
               const double * y_reco_bins   = util::YrecoBinEdges(s,izone);
               // book histogram
               TH2D * h2 = new TH2D("h2","VALOR/LBNx ND (Ereco,yreco) PDF component = f(beam,sample,mode,zone)",
                 n_enu_reco_bins, enu_reco_bins, n_y_reco_bins, y_reco_bins);
               h2 -> SetName( Form("%s_%s_%s",tag, "pdfc_rt",name) );
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
        }//imode
      }//isample
    }//ibeam
  }//pdfc_va,pdfc_rt


  //
  // Write out the total PDF (VALORArray or bare ROOT format)
  //

  if(opt.find("pdft_va") != string::npos || opt.find("pdft_rt") != string::npos) {

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
             if (opt.find("pdft_va") != string::npos) {
               fMCPDFTot[ibeam][isample][izone]->SetName(Form("%s_%s_%s",tag,"pdft_va",name));
               array->Add(fMCPDFTot[ibeam][isample][izone]);
             }
             // in TH2D format
             if (opt.find("pdft_rt") != string::npos) {
               // get binning
               const int n_enu_reco_bins = util::NumErecoBins(s,izone);
               const int n_y_reco_bins   = util::NumYrecoBins(s,izone);
               if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
               const double * enu_reco_bins = util::ErecoBinEdges(s,izone);
               const double * y_reco_bins   = util::YrecoBinEdges(s,izone);
               // book histogram
               TH2D * h2 = new TH2D("h2","VALOR/LBNx ND (Ereco,yreco) PDF = f(beam,sample,zone)",
                 n_enu_reco_bins, enu_reco_bins, n_y_reco_bins, y_reco_bins);
               h2 -> SetName( Form("%s_%s_%s",tag, "pdft_rt",name) );
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
      }//isample
    }//ibeam
  }//pdft_va,pdft_rt


  //
  // Write out the slices of the total PDF (bare ROOT format)
  //

  if(opt.find("pdfts_rt") != string::npos) {
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
          for(int iy = 0; iy < n_y_reco_bins; iy++) {
            TH1D * h = new TH1D("h",
                Form("VALOR/LBNx ND PDF slice: Ereco spectrum = f(beam,sample,zone) for y in [%f,%f]", 
                     y_reco_bins[iy],y_reco_bins[iy+1]),
                n_enu_reco_bins, enu_reco_bins);
            h->SetName(Form("%s_%s_%s_y%d",tag, "pdfts_rt",name,iy) );
            h->GetXaxis()->SetTitle("reco. E_{#nu} (GeV)");
            for(int ier = 0; ier < n_enu_reco_bins; ier++) {
              double val = fMCPDFTot[ibeam][isample][izone]->GetEntry(ier,iy);
              h->SetBinContent(ier+1, val);
            }//ier
            // add to obj array and clean-up 
            array->Add(h);
            //delete h; ??? MEM LEAK??
          }//iy
         
        }//izone
      }//isample
    }//ibeam
  }//pdfts_rt
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
  return 0;
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
       for(int izone = 0; izone < kNMaxBinZones; izone++) {
         fNullMC [ibeam][isample][imode][izone] = true;
         // MC templates
         fMCTNom [ibeam][isample][imode][izone] = 0;
         fMCTTun [ibeam][isample][imode][izone] = 0;
         fMCTSys [ibeam][isample][imode][izone] = 0;
         fMCTFin [ibeam][isample][imode][izone] = 0;
         // PDF
         fMCPDFComp [ibeam][isample][imode][izone] = 0;
         if(imode == 0) {
           fMCPDFTot   [ibeam][isample][izone] = 0;
           fNullPDFTot [ibeam][isample][izone] = true;
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
        for(int izone = 0; izone < kNMaxBinZones; izone++) {
           const int n_enu_true_bins = util::NumEtrueBins(s,izone);
           const int n_enu_reco_bins = util::NumErecoBins(s,izone);
           const int n_y_reco_bins   = util::NumYrecoBins(s,izone);
           if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;

           LOG("NDModel",pDEBUG) 
              << "Booking MC template for " 
              << "beam: "     << util::AsString(b) 
              << ", sample: " << util::AsString(s)
              << ", mode: "   << util::AsString(m) 
              << ", zone: "   << izone;
 
           fNullMC[ibeam][isample][imode][izone] = false;

           // >> MC templates 
           // (Note order of variables: reco first, true later)
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
           if(fNullPDFTot[ibeam][isample][izone]) {              
              LOG("NDModel",pDEBUG) 
                 << "Booking PDF (total) for " 
                 << "beam: "     << util::AsString(b) 
                 << ", sample: " << util::AsString(s)
                 << ", zone: "   << izone;

              fNullPDFTot[ibeam][isample][izone] = false;
              fMCPDFTot  [ibeam][isample][izone] = 
                  new VALORArray(n_enu_reco_bins,n_y_reco_bins);           
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
        for(int izone = 0; izone < kNMaxBinZones; izone++) {

          if(!fNullMC[ibeam][isample][imode][izone]) {
              fNullMC[ibeam][isample][imode][izone] = true;
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
          if(!fNullPDFTot[ibeam][isample][izone]) {
              fNullPDFTot[ibeam][isample][izone] = true;
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
        fPOT  [ibeam] = 0;
      }
    }
  }
}
//________________________________________________________________________________________
void NDModel::Zero(void)
{
  LOG("NDModel",pDEBUG) << "Zeroing MC templates and/or PDFs...";
/*

// Add input Option_t to zero-out selectively MC templates or PDFs
//

  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
   for(int isample = 0; isample < kNNDSamples; isample++) {
     for(int imode = 0; imode < kNReacModes; imode++) {
       for(int izone = 0; izone < kNMaxBinZones; izone++) {
         bool is_null = fNullMC[ibeam][isample][imode][izone];
         if(!is_null) {
             // MC templates
             fMCTNom[ibeam][isample][imode][izone]->SetAll(0.);
             fMCTTun[ibeam][isample][imode][izone]->SetAll(0.);
             fMCTSys[ibeam][isample][imode][izone]->SetAll(0.);
             fMCTFin[ibeam][isample][imode][izone]->SetAll(0.);
             // PDF
             fMCPDFComp[ibeam][isample][imode][izone]->SetAll(0.);
         }//!null
       }//izone
     }//imode
   }//isample
  }//ibeam
*/
}
//________________________________________________________________________________________
void NDModel::FillTemplates(TTree * t, int ibeam)
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
       double pct = 100 * (double)iev+1 / (double)nev;
       LOG("NDModel",pDEBUG) << "Reading MC DST: " << pct << "% done";
     }

     // Get sample index
     NDSample_t s = util::NDSampleFromInt(sample);
     if(s == ksNDUndefined) {
       LOG("NDModel",pWARN) 
          << " ** Undefined sample ID used in MC event: " << iev
          << " (value stored in DST: " << sample << ")";
       //exit(1);
     }
     int isample = fArrIdx->NDSampleIdx(s);
     if(isample < 0) {
       // fine, we do not indlude all samples in the fit
       LOG("NDModel",pDEBUG) 
         << "Ignoring MC event: " << iev 
         << "(sample ID: " << util::AsString(s) << " not included in current fit)";
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
         << "(ignoring contribution to sample: " << util::AsString(s) << " from mode: " << util::AsString(m) << " ?)";
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

     bool is_null = fNullMC[ibeam][isample][imode][izone];
     if(is_null) {
       LOG("NDModel",pFATAL) 
         << "** Null MC template for sample: " << util::AsString(s) 
         << ", mode: " << util::AsString(m) << ", bin zone = " << izone << " ??";
       exit(1);
     }

     // Get enu_true, enu_reco, y_reco array indices
     const int n_enu_true_bins = util::NumEtrueBins(s,izone);
     const int n_enu_reco_bins = util::NumErecoBins(s,izone);
     const int n_y_reco_bins   = util::NumYrecoBins(s,izone);

     const double * enu_true_bin_edges = util::EtrueBinEdges(s,izone);
     const double * enu_reco_bin_edges = util::ErecoBinEdges(s,izone);
     const double * y_reco_bin_edges   = util::YrecoBinEdges(s,izone);

     int ienu_true = TMath::BinarySearch((Long_t)n_enu_true_bins, enu_true_bin_edges, enu_true);
     int ienu_reco = TMath::BinarySearch((Long_t)n_enu_reco_bins, enu_reco_bin_edges, enu_reco);
     int iy_reco   = TMath::BinarySearch((Long_t)n_y_reco_bins,   y_reco_bin_edges,   y_reco  );

     // Exposure for assumed data - Weight MC templates to that exposure
     double data_pot = fPOT[ibeam];
  
     // Get MC exposure
     //
     // The POT weight is given in 5*6e20*5
     // This is: 5 years of running * 6e20 POT/year * 5kt near detector mass
     // The factor of 2 is coming since nu and anti-nu are saved in the same file 
     double mc_pot = wght_pot;
     assert(wght_pot>0.);

     // Calculate POT weight (assumed data exposure) / (generated MC exposure)
     double wght = data_pot/mc_pot;

     // Add `nom' array entry (and init `tun', `sys' and `fin' arrays = `nom')
     double curr_wght = fMCTNom[ibeam][isample][imode][izone]->GetEntry(ienu_reco, iy_reco, ienu_true);
     curr_wght += wght;
     fMCTNom[ibeam][isample][imode][izone]->SetEntry(curr_wght, ienu_reco, iy_reco, ienu_true);
     fMCTTun[ibeam][isample][imode][izone]->SetEntry(curr_wght, ienu_reco, iy_reco, ienu_true);
     fMCTSys[ibeam][isample][imode][izone]->SetEntry(curr_wght, ienu_reco, iy_reco, ienu_true);
     fMCTFin[ibeam][isample][imode][izone]->SetEntry(curr_wght, ienu_reco, iy_reco, ienu_true);     
  }//iev 
}
//________________________________________________________________________________________
void NDModel::ApplyTuning(void)
{
// This method maps nom -> tun MC templates
// No external tuning available for the time-being

}
//________________________________________________________________________________________
void NDModel::ApplySystematics(void)
{
// This method maps tun -> sys MC templates.
// Applying detector systematics and uncorrelated flux/cross-section systematics.

  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
   for(int isample = 0; isample < kNNDSamples; isample++) {
    for(int imode = 0; imode < kNReacModes; imode++) {
      for(int izone = 0; izone < kNMaxBinZones; izone++) {
         bool is_null = fNullMC[ibeam][isample][imode][izone];
         if(!is_null) {
             

         }//!null
      }//izone
    }//imode
   }//isample
  }//ibeam

}
//________________________________________________________________________________________
void NDModel::ApplyPhysics(void)
{
// This method maps sys -> fin MC templates.
// Applying correlated flux and cross-section systematics

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
          bool is_null = fNullMC[ibeam][isample][imode][izone];
          if(!is_null) {
            for(int ip = 0; ip < kNNDFitParams; ip++) {
               bool apply = kNDApplyFitParamToTemplate[imode][ip];
               if(!apply) continue;
/*
               const double Etrue_min = kNDFitParamEtrueRange[ip][0];
               const double Etrue_max = kNDFitParamEtrueRange[ip][1];

               for(int it; it < ; it++) {
                 double Etrue = ;
                 if(Etrue < Etrue_min || Etrue > Etrue_max) continue;
                 for(int ir; ir < ; ir++) {
                   for(int iy; iy < ; iy++) {

                   }//iy: yreco bins
                 }//ir: Ereco bins
               }//it: Etrue bins
*/
            }//ip
          }//!null
        }//izone
      }//imode
    }//isample
  }//ibeam
}
//________________________________________________________________________________________
void NDModel::CalcPDFs(void)
{
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
      for(int imode = 0; imode < kNReacModes; imode++) {
        ReacMode_t m = kNDReactionModes[isample][imode];
        if(m == kmUndefined) continue;
        for(int izone = 0; izone < kNMaxBinZones; izone++) {
          bool is_null = fNullMC[ibeam][isample][imode][izone];
          if(is_null) continue;

          const int n_enu_true_bins = util::NumEtrueBins(s,izone);
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
                 bool is_null = fNullMC[ibeam][isample][imode][izone];
                 if(is_null) continue;
                 sum += fMCPDFComp[ibeam][isample][imode][izone]->GetEntry(ier, iyr);
              }//imode
              fMCPDFTot[ibeam][isample][izone]->SetEntry(sum, ier, iyr);
           }//iyr
         }//ier
      }//izone
    }//isample
  }//ibeam
}
//________________________________________________________________________________________
