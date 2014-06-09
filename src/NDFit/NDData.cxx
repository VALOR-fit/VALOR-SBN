//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include <cassert>

#include <TFile.h>
#include <TObjArray.h>
#include <TH1D.h>
#include <TH2D.h>

#include "NDFit/NDData.h"
#include "NDFit/NDSample.h"
#include "NDFit/NDSampleBinning.h"
#include "FitCore/FitModelABC.h"
#include "FitCore/FitParamList.h"
#include "FitCore/PhysHypothesis.h"
#include "Utilities/Rnd.h"
#include "Utilities/UtlStyle.h"
#include "Utilities/UtlNumStat.h"
#include "Messenger/Messenger.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
NDData::NDData() :
FitDataABC()
{
  this->Init();
  this->Book();
}
//________________________________________________________________________________________
NDData::~NDData() 
{

}
//________________________________________________________________________________________
string NDData::Name(void)
{
  return "LBNxND";
}
//________________________________________________________________________________________
bool NDData::Read(string /*file*/, Option_t * /*opt*/)
{
  return true;
}
//________________________________________________________________________________________
bool NDData::Write(TObjArray * array, const char * tag, Option_t * write_opt)
{

  LOG("NDData",pINFO) << "Writing results to input object array...";

  if(!array) {
     LOG("NDData",pERROR) << "Null input object array.";
     return false;
  }

  valor::util::SetDefaultStyle();

  string opt = (write_opt) ? write_opt : "data_va";

  //
  // Write out MC templates (VALORArray format)
  //

  if(opt.find("data_va") != string::npos || opt.find("data_rt") != string::npos) {

    for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
      BeamConf_t b = kNDBeamConf[ibeam];
      if(b == kbUndefined) continue;
      for(int isample = 0; isample < kNNDSamples; isample++) {
        NDSample_t s = kNDSample[isample];
        if(s == ksNDUndefined) continue;
        for(int izone = 0; izone < kNMaxBinZones; izone++) {
          if(fDataNull[ibeam][isample][izone]) continue;
          const char * name = Form("%s_%s_z%d",
             util::AsString(b).c_str(), util::AsString(s).c_str(), izone);
          if(opt.find("data_va") != string::npos) {
             fData[ibeam][isample][izone]->SetName(Form("%s_%s_%s",tag,"data_va",name));
             array->Add(fData[ibeam][isample][izone]);
          }
          if(opt.find("data_rt") != string::npos) {
             const int n_enu_reco_bins = util::NumErecoBins(s,izone);
             const int n_y_reco_bins   = util::NumYrecoBins(s,izone);
             if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
             const double * enu_reco_bins = util::ErecoBinEdges(s,izone);
             const double * y_reco_bins   = util::YrecoBinEdges(s,izone);
             TH2D * h2 = new TH2D("h2", "VALOR/LBNx ND (Ereco,yreco) data = f(beam,sample,zone)",
                 n_enu_reco_bins, enu_reco_bins, n_y_reco_bins, y_reco_bins);
             h2->SetName(Form("%s_%s_%s",tag,"data_rt",name));
             for(int ier = 0; ier < n_enu_reco_bins; ier++) {
               for(int iy = 0; iy < n_y_reco_bins; iy++) {
                 double val = fData[ibeam][isample][izone]->GetEntry(ier,iy);
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
          if(fDataSbNull[ibeam][isample]) continue;
          if(opt.find("data_va") != string::npos) {
             fDataSb[ibeam][isample]->SetName(Form("%s_%s_%s",tag,"datasb_va",name));
             array->Add(fDataSb[ibeam][isample]);
          }//data_va
          if(opt.find("data_rt") != string::npos) {
             const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(s);
             TH2D * h2 = new TH2D("h2","VALOR/LBNx ND (Ereco,yreco) data = f(beam,sample)",
                kNErecoBinsSb, kErecoBinEdgesSb, kNYrecoBinsSb, y_reco_bin_edges_sb);
             h2->SetName(Form("%s_%s_%s",tag,"datasb_rt",name));
             for(int ier = 0; ier < kNErecoBinsSb; ier++) {
               for(int iy = 0; iy < kNYrecoBinsSb; iy++) {
                 double val = fDataSb[ibeam][isample]->GetEntry(ier,iy);
                 h2->SetBinContent(ier+1,iy+1,val);
               }//iy
             }//ier
             // add to object array and clean-up
             array->Add(h2);
             // delete h2; ???? // MEMORY LEAK?
          }//data_va
        }

      }//isample
    }//ibeam

  }//data_va

  return true;
}
//________________________________________________________________________________________
bool NDData::Write(
  const char * filename, const char * tag, const char * write_opt, Option_t * file_opt)
{
  LOG("NDData",pNOTICE) << "Writing results to file: [" << filename << "]";

  TObjArray * array = new TObjArray();
  this->Write(array,tag,write_opt);

  Option_t * used_file_opt = (file_opt == 0) ? "recreate" : file_opt;
  TFile f(filename, used_file_opt);
  array->Write();
  f.Close();

  return true;
}
//________________________________________________________________________________________
bool NDData::Generate(
    FitModelABC * model_abc, const FitParamList & fp, bool fluctuate)
{
  LOG("NDData",pINFO) << "Generating a toy-MC expt with the following params: " << fp;
  LOG("NDData",pINFO) << "Stat. fluctuations are turned-" << ((fluctuate)? "ON" : "OFF");

  bool ok = model_abc->Generate(fp);
  if(!ok) {
    LOG("NDData",pERROR) 
       << "Could not generate predictions with model: " << model_abc->Name()
       << " and input params: " << fp;
    return false;
  }

  return this->Generate(model_abc,fp,fluctuate);
}
//________________________________________________________________________________________
bool NDData::Generate(
   FitModelABC * model_abc, const PhysHypothesis & ph, bool fluctuate)
{
  LOG("NDData",pINFO) << "Generating a toy-MC expt with the following params: " << ph;
  LOG("NDData",pINFO) << "Stat. fluctuations are turned-" << ((fluctuate)? "ON" : "OFF");

  bool ok = model_abc->Generate(ph);
  if(!ok) {
    LOG("NDData",pERROR) 
       << "Could not generate predictions with model: " << model_abc->Name()
       << " with systematic tweaks: " << model_abc->Tweaks()
       << " and input params: " << ph;
    return false;
  }

  return this->Generate(model_abc,fluctuate);
}
//________________________________________________________________________________________
bool NDData::Generate(FitModelABC * /*model_abc*/, bool /*fluctuate*/)
{

  return true;
}
//________________________________________________________________________________________
int NDData::NumOfBins(void)
{
  return 0;
}
//________________________________________________________________________________________
double NDData::Statistic(FitModelABC* model_abc, const FitParamList & fp, Option_t * opt)
{
  bool ok = model_abc->Generate(fp);
  assert(ok);

  return this->Statistic(model_abc,opt);
}
//________________________________________________________________________________________
double NDData::Statistic(FitModelABC * model_abc, const PhysHypothesis & ph, Option_t * opt)
{
  bool ok = model_abc->Generate(ph);
  assert(ok);

  return this->Statistic(model_abc,opt);  
}
//________________________________________________________________________________________
double NDData::Statistic(FitModelABC * model_abc, Option_t * /*opt*/) 
{
  TObjArray * array = new TObjArray();
  model_abc->Write(array, "model");

  // Get predictions from array

  // Calculate statistic
  double S = 0;

  return S;
}
//________________________________________________________________________________________
void NDData::Init(void)
{
  LOG("NDData",pDEBUG) << "Initializing...";

  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
   for(int isample = 0; isample < kNNDSamples; isample++) {
     for(int izone = 0; izone < kNMaxBinZones; izone++) {
        fDataNull [ibeam][isample][izone] = true;
        fData     [ibeam][isample][izone] = 0;
     }//izone
     fDataSbNull [ibeam][isample] = true;
     fDataSb     [ibeam][isample] = 0;
   }//isample
  }//ibeam
}
//________________________________________________________________________________________
void NDData::Book(void)
{
  LOG("NDData",pDEBUG) << "Booking...";

  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
    BeamConf_t b = kNDBeamConf[ibeam];
    if(b == kbUndefined) continue;
    for(int isample = 0; isample < kNNDSamples; isample++) {
      NDSample_t s = kNDSample[isample];
      if(s == ksNDUndefined) continue;
      for(int izone = 0; izone < kNMaxBinZones; izone++) {
          const int n_enu_reco_bins = util::NumErecoBins(s,izone);
          const int n_y_reco_bins   = util::NumYrecoBins(s,izone);
          if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
          fDataNull [ibeam][isample][izone] = false;
          fData     [ibeam][isample][izone] = new VALORArray(n_enu_reco_bins, n_y_reco_bins);
      }//izone
      fDataSbNull [ibeam][isample] = false;
      fDataSb     [ibeam][isample] = new VALORArray(kNErecoBinsSb, kNYrecoBinsSb);
    }//isample
  }//ibeam
}
//________________________________________________________________________________________
void NDData::Clean(void)
{
  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
    for(int isample = 0; isample < kNNDSamples; isample++) {
      for(int izone = 0; izone < kNMaxBinZones; izone++) {
        if(!fDataNull[ibeam][isample][izone]) {
           fDataNull [ibeam][isample][izone] = true;
           fData     [ibeam][isample][izone] = 0;
        }
      }//izone
      if(!fDataSbNull [ibeam][isample]) {
          fDataSbNull [ibeam][isample] = true;
          fDataSb     [ibeam][isample] = 0;
      }
    }//isample
  }//ibeam
}
//________________________________________________________________________________________

