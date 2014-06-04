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
bool NDModel::Write(TObjArray * array, const char * /*tag*/, Option_t * /*write_opt*/)
{
  if(!array) return false;

  valor::util::SetDefaultStyle();

  //...

  return true;
}
//________________________________________________________________________________________
bool NDModel::Write(
  const char * filename, const char * tag, Option_t * write_opt, Option_t * file_opt)
{
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
         fMCPDF  [ibeam][isample][imode][izone] = 0;
         fMCPDFH2[ibeam][isample][imode][izone] = 0;
         if(imode == 0) {
           fMCPDFTot  [ibeam][isample][izone] = 0;
           fMCPDFTotH2[ibeam][isample][izone] = 0;
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

           const double * enu_reco_bins = util::ErecoBinEdges(s,izone);
           const double * y_reco_bins   = util::YrecoBinEdges(s,izone);

           LOG("NDModel",pDEBUG) 
              << "Booking MC template for " 
              << "beam: "     << util::AsString(b) 
              << ", sample: " << util::AsString(s)
              << ", mode: "   << util::AsString(m) 
              << ", zone: "   << izone;
 
           fNullMC[ibeam][isample][imode][izone] = false;

           // MC templates (Note order of variables: reco first, true later)
           fMCTNom [ibeam][isample][imode][izone] = 
             new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins);
           fMCTTun [ibeam][isample][imode][izone] = 
             new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins);
           fMCTSys [ibeam][isample][imode][izone] = 
             new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins);
           fMCTFin [ibeam][isample][imode][izone] = 
             new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins);

           // PDF

           LOG("NDModel",pDEBUG) 
              << "Booking PDF component for " 
              << "beam: "     << util::AsString(b) 
              << ", sample: " << util::AsString(s)
              << ", mode: "   << util::AsString(m) 
              << ", zone: "   << izone;
 
           const char * name = Form("valor_pdf_component_%s_%s_%s_z%d",
                util::AsString(b).c_str(),util::AsString(s).c_str(),
                util::AsString(m).c_str(),izone);
           fMCPDF  [ibeam][isample][imode][izone] = 
             new VALORArray(n_enu_reco_bins,n_y_reco_bins);           
           fMCPDFH2[ibeam][isample][imode][izone] = 
             new TH2D(name,"VALOR/LBNx ND PDF",
                      n_enu_reco_bins, enu_reco_bins, n_y_reco_bins, y_reco_bins);

           if(imode == 0) {

              LOG("NDModel",pDEBUG) 
                 << "Booking PDF (total) for " 
                 << "beam: "     << util::AsString(b) 
                 << ", sample: " << util::AsString(s)
                 << ", zone: "   << izone;

              const char * name2 = Form("valor_pdf_%s_%s_z%d",
                   util::AsString(b).c_str(),util::AsString(s).c_str(), izone);
              fMCPDFTot  [ibeam][isample][izone] = 
                  new VALORArray(n_enu_reco_bins,n_y_reco_bins);           
              fMCPDFTotH2[ibeam][isample][izone] = 
                  new TH2D(name2,"VALOR/LBNx ND PDF",
                           n_enu_reco_bins, enu_reco_bins, n_y_reco_bins, y_reco_bins);
           }//imode==0
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

          fNullMC[ibeam][isample][imode][izone] = true;

          // MC templates
          if(fMCTNom[ibeam][isample][imode][izone]) {
             delete fMCTNom[ibeam][isample][imode][izone];
             fMCTNom[ibeam][isample][imode][izone] = 0;
          }
          if(fMCTTun[ibeam][isample][imode][izone]) {
             delete fMCTTun[ibeam][isample][imode][izone];
             fMCTTun[ibeam][isample][imode][izone] = 0;
          }
          if(fMCTSys[ibeam][isample][imode][izone]) { 
             delete fMCTSys[ibeam][isample][imode][izone];
             fMCTSys[ibeam][isample][imode][izone] = 0;
          }
          if(fMCTFin[ibeam][isample][imode][izone]) {
             delete fMCTFin[ibeam][isample][imode][izone];
             fMCTFin[ibeam][isample][imode][izone] = 0;
          }

          // PDF
          if(fMCPDF[ibeam][isample][imode][izone]) {
             delete fMCPDF[ibeam][isample][imode][izone];
             fMCPDF[ibeam][isample][imode][izone] = 0;
          }
          if(fMCPDFH2[ibeam][isample][imode][izone]) {
             delete fMCPDFH2[ibeam][isample][imode][izone];
             fMCPDFH2[ibeam][isample][imode][izone] = 0;
          }
          if(imode==0) {
             if(fMCPDFTot[ibeam][isample][izone]) {
                delete fMCPDFTot[ibeam][isample][izone];
                fMCPDFTot[ibeam][isample][izone] = 0;
             }
             if(fMCPDFTotH2[ibeam][isample][izone]) {
                delete fMCPDFTotH2[ibeam][isample][izone];
                fMCPDFTotH2[ibeam][isample][izone] = 0;
             }
          }//imode==0
          
        }//izone
      }//imode
    }//isample
  }//ibeam

  //if (fMCDST) delete fMCDST;
}
//________________________________________________________________________________________
void NDModel::Zero(void)
{
  LOG("NDModel",pDEBUG) << "Zeroing MC templates and/or PDFs...";

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
             fMCPDF  [ibeam][isample][imode][izone]->SetAll(0.);
             fMCPDFH2[ibeam][isample][imode][izone]->Reset();
         }//!null
       }//izone
     }//imode
   }//isample
  }//ibeam
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
/*
     if(1) {
       LOG("NDModel",pDEBUG) << "Got MC event: " << iev;
       LOG("NDModel",pDEBUG) << " - sample    = " << sample;
       LOG("NDModel",pDEBUG) << " - reac_mode = " << reac_mode;
       LOG("NDModel",pDEBUG) << " - enu_true  = " << enu_true;
       LOG("NDModel",pDEBUG) << " - enu_reco  = " << enu_reco;
       LOG("NDModel",pDEBUG) << " - y_reco    = " << y_reco;
       LOG("NDModel",pDEBUG) << " - wght_pot  = " << wght_pot;
     }
*/

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
         << "Current MC event (" << iev << ") is in a sample not considered "
         << "by the present fit (" << util::AsString(s) << ")";
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
         << "Current MC event (" << iev << ") is in a mode not considered "
         << "by the present fit (" << util::AsString(s) << ")";
       exit(1);
     }
     
     // Get bin zone index
     int izone = util::BinZone(s, enu_reco, y_reco);
     if(izone < 0) {
//     LOG("NDModel",pFATAL) - turn that to fatal after binning optimization is done
       LOG("NDModel",pWARN) 
         << "Current MC event (" << iev << ") has enu_reco = " << enu_reco << " GeV, "
         << " y_reco = " << y_reco << " which doesn't fit in any bin zone!";
//     exit(1);
       continue;
     }

     bool is_null = fNullMC[ibeam][isample][imode][izone];
     if(is_null) {
       LOG("NDModel",pFATAL) 
         << "Null MC template for sample: " << util::AsString(s) 
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
               fMCPDF  [ibeam][isample][imode][izone]->SetEntry      (sum, ier, iyr);
               fMCPDFH2[ibeam][isample][imode][izone]->SetBinContent (1+ier, 1+iyr, sum);
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
                 sum += fMCPDF[ibeam][isample][imode][izone]->GetEntry(ier, iyr);
              }//imode
              fMCPDFTot  [ibeam][isample][izone]->SetEntry      (sum, ier, iyr);
              fMCPDFTotH2[ibeam][isample][izone]->SetBinContent (1+ier, 1+iyr, sum);
           }//iyr
         }//ier
      }//izone
    }//isample
  }//ibeam

}
//________________________________________________________________________________________
