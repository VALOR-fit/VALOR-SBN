//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include <ostream>
#include <iostream>

#include <TXMLEngine.h>
#include <TFile.h>
#include <TObjArray.h>
#include <TH1D.h>

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
#include "NDFit/NDSystematics.h"

using std::cout;
using std::endl;

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
NDModel::NDModel() :
FitModelABC()
{
  //...
}
//________________________________________________________________________________________
NDModel::~NDModel() 
{
  //...
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
cout << "READING FROM " << file << endl;

  // Parse the input XML configuration file
  TXMLEngine* xml = new TXMLEngine;   
  XMLDocPointer_t xmldoc = xml->ParseFile(file.c_str());
  if (xmldoc==0) {
    LOG("NDModel",pERROR) << "Can not pars input XML file [" << file << "]";
    delete xml;
    return false;  
  }
  XMLNodePointer_t root_node = xml->DocGetRootElement(xmldoc);

  // Get assumed exposure for each beam configuration
  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
    BeamConf_t bc = kNDBeamConf[ibeam];
    if(bc == kbUndefined) continue;
    string node_name = "data/exposure/" + util::AsString(bc, "lowercase");
    fPOT[ibeam] = util::XML2Dbl(xml,root_node,node_name);
  }//ibeam

  //
  // Using input in VALOR DST format
  // If true, read the ROOT files and fill-in the MC templates.
  // If false, just read in the MC templates. 
  // In the later case, the templates are pre-binned so the binning
  // can not change. Make sure the templates hav ethe expected binning
  //
  fUseMCDST = util::XML2Bool(xml,root_node,"mc/using_dst_format");
  if(fUseMCDST) {
    for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
       BeamConf_t bc = kNDBeamConf[ibeam];
       if(bc == kbUndefined) continue;
       string node_name = "mc/dst/" + util::AsString(bc, "lowercase");
       fMCDST[ibeam] = util::XML2TTree (xml,root_node,node_name);
       assert(fMCDST[ibeam]);
       this->FillTemplates(fMCDST[ibeam]);
    }//ibeam
  } 
  else {
    // ** implement later (when binning is optimized) and make it the default
    // ** choice to reduce the size of data files stored in the SVN repository.
  }

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



  //
  //
  // ...
  //
  //


//  LOG("NDModel",pDEBUG) << "Done generating predictions";

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
  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
   for(int isample = 0; isample < kNNDSamples; isample++) {
     for(int imode = 0; imode < kNReacModes; imode++) {
       for(int izone = 0; izone < kNMaxBinZones; izone++) {
         fNullMCTempl[ibeam][isample][imode][izone] = true;
         fMCTemplNom [ibeam][isample][imode][izone] = 0;
         fMCTemplTun [ibeam][isample][imode][izone] = 0;
         fMCTemplSys [ibeam][isample][imode][izone] = 0;
         fMCTemplFin [ibeam][isample][imode][izone] = 0;
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
  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
   for(int isample = 0; isample < kNNDSamples; isample++) {
    NDSample_t s = kNDSample[isample];
    if(s == ksNDUndefined) continue;
    for(int imode = 0; imode < kNReacModes; imode++) {
      ReacMode_t m = kNDReactionModes[isample][imode];
      if(m == kmUndefined) continue;
      for(int izone = 0; izone < kNMaxBinZones; izone++) {
         const int n_etrue_bins = util::NumEtrueBins(s,izone);
         const int n_ereco_bins = util::NumErecoBins(s,izone);
         const int n_yreco_bins = util::NumYrecoBins(s,izone);
         if(n_ereco_bins <= 0 || n_yreco_bins <= 0) continue;

         fNullMCTempl[ibeam][isample][imode][izone] = false;

         fMCTemplNom [ibeam][isample][imode][izone] = 
            new VALORArray(n_etrue_bins,n_ereco_bins,n_yreco_bins);
         fMCTemplTun [ibeam][isample][imode][izone] = 
            new VALORArray(n_etrue_bins,n_ereco_bins,n_yreco_bins);
         fMCTemplSys [ibeam][isample][imode][izone] = 
            new VALORArray(n_etrue_bins,n_ereco_bins,n_yreco_bins);
         fMCTemplFin [ibeam][isample][imode][izone] = 
            new VALORArray(n_etrue_bins,n_ereco_bins,n_yreco_bins);

      }//izone
    }//imode
   }//isample
  }//ibeam
}
//________________________________________________________________________________________
void NDModel::Clean(void)
{
  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
   for(int isample = 0; isample < kNNDSamples; isample++) {
     for(int imode = 0; imode < kNReacModes; imode++) {
       for(int izone = 0; izone < kNMaxBinZones; izone++) {

         fNullMCTempl[ibeam][isample][imode][izone] = true;

         if(fMCTemplNom[ibeam][isample][imode][izone]) delete fMCTemplNom[ibeam][isample][imode][izone];
         fMCTemplNom[ibeam][isample][imode][izone] = 0;
         if(fMCTemplTun[ibeam][isample][imode][izone]) delete fMCTemplTun[ibeam][isample][imode][izone];
         fMCTemplTun[ibeam][isample][imode][izone] = 0;
         if(fMCTemplSys[ibeam][isample][imode][izone]) delete fMCTemplSys[ibeam][isample][imode][izone];
         fMCTemplSys[ibeam][isample][imode][izone] = 0;
         if(fMCTemplFin[ibeam][isample][imode][izone]) delete fMCTemplFin[ibeam][isample][imode][izone];
         fMCTemplFin[ibeam][isample][imode][izone] = 0;

       }//izone
     }//imode
   }//isample
  }//ibeam

  //if (fMCDST) delete fMCDST;
}
//________________________________________________________________________________________
void NDModel::ZeroTemplates(void)
{
  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
   for(int isample = 0; isample < kNNDSamples; isample++) {
     for(int imode = 0; imode < kNReacModes; imode++) {
       for(int izone = 0; izone < kNMaxBinZones; izone++) {
         bool is_null = fNullMCTempl[ibeam][isample][imode][izone];
         if(!is_null) {
             fMCTemplNom[ibeam][isample][imode][izone]->SetAll(0.);
             fMCTemplTun[ibeam][isample][imode][izone]->SetAll(0.);
             fMCTemplSys[ibeam][isample][imode][izone]->SetAll(0.);
             fMCTemplFin[ibeam][isample][imode][izone]->SetAll(0.);
         }//!null
       }//izone
     }//imode
   }//isample
  }//ibeam
}
//________________________________________________________________________________________
void NDModel::FillTemplates(TTree * t)
{
  if(!t) return;

  this->ZeroTemplates();

  TBranch * bSample   = t->GetBranch("sample");         // selected ND sample
  TBranch * bReacMode = t->GetBranch("reac_mode");      // reaction mode
  TBranch * bEnuTrue  = t->GetBranch("enu_true");       // true energy (GeV)
  TBranch * bEnuReco  = t->GetBranch("enu_reco");       // reco energy (GeV)
  TBranch * byReco    = t->GetBranch("y_reco");         // reco inelasticity y
  TBranch * bWghtPOT  = t->GetBranch("wgt_to1e20pot");  // weight for 1E+20 POT exposure

  int    sample    = 0;
  int    reac_mode = 0;
  double enu_true  = 0;
  double enu_reco  = 0;
  double y_reco    = 0;
  double wght_pot  = 0;

  bSample   -> SetAddress(&sample    );
  bReacMode -> SetAddress(&reac_mode );
  bEnuTrue  -> SetAddress(&enu_true  );
  bEnuReco  -> SetAddress(&enu_reco  );
  byReco    -> SetAddress(&y_reco    );
  bWghtPOT  -> SetAddress(&wght_pot  );

  t->SetBranchStatus("*",0);
  t->SetBranchStatus("sample",        1); 
  t->SetBranchStatus("reac_mode",     1);    
  t->SetBranchStatus("enu_true",      1);  
  t->SetBranchStatus("enu_reco",      1);  
  t->SetBranchStatus("y_reco",        1);    
  t->SetBranchStatus("wgt_to1e20pot", 1);

  for(int iev = 0; iev < t->GetEntries(); iev++) 
  {
     t->GetEntry(iev);

     int isample   = fArrIdx->NDSampleIdx  ((NDSample_t)sample);
     int imode     = fArrIdx->NDReacModeIdx((NDSample_t)sample, (ReacMode_t)reac_mode);
     int izone     = 2;

     bool is_null = fNullMCTempl[isample][imode][izone];
     if(is_null) continue;

     int ienu_true = 3;
     int ienu_reco = 4;
     int iy_reco   = 5;

     int    ibeam    = 0;
     double data_pot = fPOT[ibeam];
     double mc_pot   = wght_pot * 1E+20;

     double wght = data_pot/mc_pot;

     fMCTemplNom[ibeam][isample][imode][izone]->SetEntry(wght, ienu_true, ienu_reco, iy_reco);
     fMCTemplTun[ibeam][isample][imode][izone]->SetEntry(wght, ienu_true, ienu_reco, iy_reco);
     fMCTemplSys[ibeam][isample][imode][izone]->SetEntry(wght, ienu_true, ienu_reco, iy_reco);
     fMCTemplFin[ibeam][isample][imode][izone]->SetEntry(wght, ienu_true, ienu_reco, iy_reco);

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
         bool is_null = fNullMCTempl[ibeam][isample][imode][izone];
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
   for(int isample = 0; isample < kNNDSamples; isample++) {
    for(int imode = 0; imode < kNReacModes; imode++) {
      for(int izone = 0; izone < kNMaxBinZones; izone++) {
         bool is_null = fNullMCTempl[ibeam][isample][imode][izone];
         if(!is_null) {
           for(int isyst = 0; isyst < kNumOfSystematics; isyst++) {
             bool apply = kApplySystToTemplate[imode][isyst];
             if(!apply) continue;
/*
             const double Etrue_min = kSystEtrueRange[isyst][0];
             const double Etrue_max = kSystEtrueRange[isyst][1];

             for(int it; it < ; it++) {
               double Etrue = ;
               if(Etrue < Etrue_min || Etrue > Etrue_max) continue;
               for(int ir; ir < ; ir++) {
                 for(int iy; iy < ; iy++) {

                 }//iy: yreco bins
               }//ir: Ereco bins
             }//it: Etrue bins
*/
           }//isyst
         }//!null
      }//izone
    }//imode
   }//isample
  }//ibeam
}
//________________________________________________________________________________________

