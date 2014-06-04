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
    BeamConf_t b = kNDBeamConf[ibeam];
    if(b == kbUndefined) continue;
    string node_name = "data/exposure/" + util::AsString(b, "lowercase");
    fPOT[ibeam] = util::XML2Dbl(xml,root_node,node_name);
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
    BeamConf_t b = kNDBeamConf[ibeam];
    if(b == kbUndefined) continue;
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

          if(fMCTemplNom[ibeam][isample][imode][izone]) {
             delete fMCTemplNom[ibeam][isample][imode][izone];
             fMCTemplNom[ibeam][isample][imode][izone] = 0;
          }
          if(fMCTemplTun[ibeam][isample][imode][izone]) {
             delete fMCTemplTun[ibeam][isample][imode][izone];
             fMCTemplTun[ibeam][isample][imode][izone] = 0;
          }
          if(fMCTemplSys[ibeam][isample][imode][izone]) { 
             delete fMCTemplSys[ibeam][isample][imode][izone];
             fMCTemplSys[ibeam][isample][imode][izone] = 0;
          }
          if(fMCTemplFin[ibeam][isample][imode][izone]) {
             delete fMCTemplFin[ibeam][isample][imode][izone];
             fMCTemplFin[ibeam][isample][imode][izone] = 0;
          }
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
void NDModel::FillTemplates(TTree * t, int ibeam)
{
  if(!t) return;

  this->ZeroTemplates();
  //this->Init();

  /*
  TBranch * bSample   = t->GetBranch("sample");        // selected ND sample
  TBranch * bReacMode = t->GetBranch("reactionmode");  // reaction mode
  TBranch * bEnuTrue  = t->GetBranch("Ev");            // true energy (GeV)
  TBranch * bEnuReco  = t->GetBranch("Ev_reco");       // reco energy (GeV)
  TBranch * byReco    = t->GetBranch("y_reco");        // reco inelasticity y
  TBranch * bWghtPOT  = t->GetBranch("POTWeight");     // weight for 5 years of running * 6E+20 POT exposure/year * 5 kt detector mass
  TBranch * bneut     = t->GetBranch("neu");           // neutrino species 
  */

  int sample       = 0;
  int reactionmode = 0;
  double Ev        = 0;
  double Ev_reco   = 0;
  double y_reco    = 0;
  double POTWeight = 0;
  int neu          = 0;

  t->SetBranchAddress("Ev",          &Ev);
  t->SetBranchAddress("Ev_reco",     &Ev_reco);
  t->SetBranchAddress("neu",         &neu);
  t->SetBranchAddress("y_reco",      &y_reco);
  t->SetBranchAddress("POTWeight",   &POTWeight);
  t->SetBranchAddress("sample",      &sample);
  t->SetBranchAddress("reactionmode",&reactionmode);

  /*
  bSample   -> SetAddress(&sample    );
  bReacMode -> SetAddress(&reactionmode );
  bEnuTrue  -> SetAddress(&Ev  );
  bEnuReco  -> SetAddress(&Ev_reco  );
  byReco    -> SetAddress(&y_reco    );
  bWghtPOT  -> SetAddress(&POTWeight  );
  bneut     -> SetAddress(&neu  );

  t->SetBranchStatus("*",0);
  t->SetBranchStatus("sample",        1); 
  t->SetBranchStatus("reactionmode",     1);    
  t->SetBranchStatus("Ev_",      1);  
  t->SetBranchStatus("Ev_reco",      1);  
  t->SetBranchStatus("y_reco",        1);    
  t->SetBranchStatus("POTWeight", 1);
  t->SetBranchStatus("neu", 1);
  */

  for(int iev = 0; iev < t->GetEntries(); iev++) 
  {
     t->GetEntry(iev);

     int isample   = fArrIdx->NDSampleIdx  ((NDSample_t)sample);
     int imode     = -1;
     if(neu == 14)
       imode     = fArrIdx->NDReacModeIdx((NDSample_t)sample, (ReacMode_t)reactionmode);
     else if(neu == -14)
       imode     = fArrIdx->NDReacModeIdx((NDSample_t)sample, (ReacMode_t)(reactionmode + kNReacModes/4));

     
     int izone     = 2;

     bool is_null = fNullMCTempl[isample][imode][izone];
     if(is_null) continue;

     int ienu_true = 3;
     int ienu_reco = 4;
     int iy_reco   = 5;

     double data_pot = fPOT[ibeam];
     // The POT weight is given in 5*6e20*5
     // This is: 5 years of running * 6e20 POT/year * 5kt near detector mass
     // The factor of 2 is coming since nu and anti-nu are saved in the same file 
     double mc_pot   = POTWeight*2;

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
    BeamConf_t b = kNDBeamConf[ibeam];
    if(b == kbUndefined) continue;
    for(int isample = 0; isample < kNNDSamples; isample++) {
      NDSample_t s = kNDSample[isample];
      if(s == ksNDUndefined) continue;
      for(int imode = 0; imode < kNReacModes; imode++) {
        ReacMode_t m = kNDReactionModes[isample][imode];
        if(m == kmUndefined) continue;

        for(int izone = 0; izone < kNMaxBinZones; izone++) {
          bool is_null = fNullMCTempl[ibeam][isample][imode][izone];
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

