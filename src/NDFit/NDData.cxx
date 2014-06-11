//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include <cassert>

#include <TFile.h>
#include <TObjArray.h>
#include <TMath.h>
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

  string opt = (write_opt) ? write_opt : "data_vf";

  //
  // Write out MC templates (VALORArray format)
  //

  if(opt.find("data_vf") != string::npos || opt.find("data_rf") != string::npos) {

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
          if(opt.find("data_vf") != string::npos) {
             fData[ibeam][isample][izone]->SetName(Form("%s_%s_%s",tag,"data_vf",name));
             array->Add(fData[ibeam][isample][izone]);
          }
          if(opt.find("data_rf") != string::npos) {
             const int n_enu_reco_bins = util::NumErecoBins(s,izone);
             const int n_y_reco_bins   = util::NumYrecoBins(s,izone);
             if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
             const double * enu_reco_bins = util::ErecoBinEdges(s,izone);
             const double * y_reco_bins   = util::YrecoBinEdges(s,izone);
             TH2D * h2 = new TH2D("h2", "VALOR/LBNx ND (Ereco,yreco) data = f(beam,sample,zone)",
                 n_enu_reco_bins, enu_reco_bins, n_y_reco_bins, y_reco_bins);
             h2->SetName(Form("%s_%s_%s",tag,"data_rf",name));
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
          if(opt.find("data_vf") != string::npos) {
             fDataSb[ibeam][isample]->SetName(Form("%s_%s_%s",tag,"datasb_vf",name));
             array->Add(fDataSb[ibeam][isample]);
          }//data_vf
          if(opt.find("data_rf") != string::npos) {
             const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(s);
             TH2D * h2 = new TH2D("h2","VALOR/LBNx ND (Ereco,yreco) data = f(beam,sample)",
                kNErecoBinsSb, kErecoBinEdgesSb, kNYrecoBinsSb, y_reco_bin_edges_sb);
             h2->SetName(Form("%s_%s_%s",tag,"datasb_rf",name));
             for(int ier = 0; ier < kNErecoBinsSb; ier++) {
               for(int iy = 0; iy < kNYrecoBinsSb; iy++) {
                 double val = fDataSb[ibeam][isample]->GetEntry(ier,iy);
                 h2->SetBinContent(ier+1,iy+1,val);
               }//iy
             }//ier
             // add to object array and clean-up
             array->Add(h2);
             // delete h2; ???? // MEMORY LEAK?
          }//data_vf
        }

      }//isample
    }//ibeam

  }//data_vf

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

  bool ok = model_abc->Generate(fp,"+SB");
  if(!ok) {
    LOG("NDData",pERROR) 
       << "Could not generate predictions with model: " << model_abc->Name()
       << " and input params: " << fp;
    return false;
  }

  return this->Generate(model_abc,fluctuate);
}
//________________________________________________________________________________________
bool NDData::Generate(
   FitModelABC * model_abc, const PhysHypothesis & ph, bool fluctuate)
{
  LOG("NDData",pINFO) << "Generating a toy-MC expt with the following params: " << ph;
  LOG("NDData",pINFO) << "Stat. fluctuations are turned-" << ((fluctuate)? "ON" : "OFF");

  bool ok = model_abc->Generate(ph,"+SB");
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
bool NDData::Generate(FitModelABC * model_abc, bool fluctuate)
{
  TObjArray * array = new TObjArray();
  model_abc->Write(array, "curr", "pdft_vf +SB");
  
  this->Zero("all");

  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
     BeamConf_t b = kNDBeamConf[ibeam];
     if(b == kbUndefined) continue;
     for(int isample = 0; isample < kNNDSamples; isample++) {
        NDSample_t s = kNDSample[isample];
        if(s == ksNDUndefined) continue;
        LOG("NDData",pINFO) 
          << "Generating toy-MC for: " 
          << util::AsString(b) << " / " << util::AsString(s);

        const char * name = Form("curr_pdfsbt_vf_%s_%s", 
           util::AsString(b).c_str(), util::AsString(s).c_str());
        VALORArray * pdf = (VALORArray*) array->FindObject(name);
        assert(pdf);           
        for(int ier = 0; ier < kNErecoBinsSb; ier++) {
          for(int iy = 0; iy < kNYrecoBinsSb; iy++) {
            double nmc   = pdf->GetEntry(ier,iy);
            double ndata = (fluctuate) ? Rnd::Instance()->RndToyMCstat().Poisson(nmc) : nmc;
            fDataSb[ibeam][isample]->SetEntry(ndata,ier,iy);

            LOG("NDData",pDEBUG) 
              << "(E_reco idx = " << ier << ", y_reco idx = " << iy 
              << "): N_{MC} = " << nmc << ", N_{Data} = " << ndata;

            // Map to distributions with optimized binning
            //
            const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(s);
            double enu_reco = kErecoBinEdgesSb[ier]   + (kErecoBinEdgesSb[ier+1]-kErecoBinEdgesSb[ier])/2.;
            double y_reco   = y_reco_bin_edges_sb[iy] + (y_reco_bin_edges_sb[iy+1]-y_reco_bin_edges_sb[iy])/2.;
            int izone = util::BinZone(s, enu_reco, y_reco);
            if(izone < 0) {
//             LOG("NDData",pFATAL) - turn that to fatal after binning optimization is done
               LOG("NDData",pWARN)
                  << " ** No bin zone for toy MC event (" << " (" << util::AsString(s) << ")"
                  << ", enu_reco = " << enu_reco << " GeV, " << " y_reco = " << y_reco << ")";
//             exit(1);
            }
            const int n_enu_reco_bins = util::NumErecoBins(s,izone);
            const int n_y_reco_bins   = util::NumYrecoBins(s,izone);
            const double * enu_reco_bin_edges  = util::ErecoBinEdges(s,izone);
            const double * y_reco_bin_edges    = util::YrecoBinEdges(s,izone);
            int ier2 = TMath::BinarySearch(1+(Long_t)n_enu_reco_bins, enu_reco_bin_edges, enu_reco);
            int iy2  = TMath::BinarySearch(1+(Long_t)n_y_reco_bins,   y_reco_bin_edges,   y_reco  );
            double ndata_curr = fData[ibeam][isample][izone]->GetEntry(ier2,iy2);
            fData[ibeam][isample][izone]->SetEntry(ndata_curr+ndata,ier2,iy2);

          }//iy
        }//ier
     }//isample
  }//ibeam

  return true;
}
//________________________________________________________________________________________
int NDData::NumOfBins(void)
{
  int nbins = 0;

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
          int nbins_curr = n_enu_reco_bins * n_y_reco_bins;
          nbins += nbins_curr;
      }//izone
    }//isample
  }//ibeam

  return nbins;
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
  model_abc->Write(array, "curr", "pdft_vf");

  // Calculate statistic
  double S = 0;

  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
    BeamConf_t b = kNDBeamConf[ibeam];
    if(b == kbUndefined) continue;
    for(int isample = 0; isample < kNNDSamples; isample++) {
      NDSample_t s = kNDSample[isample];
      if(s == ksNDUndefined) continue;
      for(int izone = 0; izone < kNMaxBinZones; izone++) {
         if(fDataNull[ibeam][isample][izone]) continue;
 
         const char * name = Form("curr_pdft_vf_%s_%s_z%d", 
            util::AsString(b).c_str(), util::AsString(s).c_str(),izone);
         VALORArray * pdf = (VALORArray*) array->FindObject(name);
         assert(pdf);           

         const int n_enu_reco_bins = util::NumErecoBins(s,izone);
         const int n_y_reco_bins   = util::NumYrecoBins(s,izone);

         for(int ier = 0; ier < n_enu_reco_bins; ier++) {
            for(int iy = 0; iy < n_y_reco_bins; iy++) {
                double nmc   = pdf->GetEntry(ier,iy);
                double ndata = fData[ibeam][isample][izone]->GetEntry(ier,iy); 
                double dS = util::ChisqPoisson(ndata, nmc);
                S += dS;
            }//iy
         }//ier

      }//izone
    }//isample
  }//ibeam
  S = TMath::Max(0.,S);

  double Sp   = model_abc->GetFitStatisticPenalty();
  double Stot = S+Sp;

  LOG("NDData",pINFO) 
    << "Current fit statistic = " << Stot
    << " (stat term = " << S << ", syst term = " << Sp << ")";

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
  LOG("NDData",pDEBUG) << "Cleaning-up...";

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
void NDData::Zero(Option_t * opt)
{
  LOG("NDData",pDEBUG) << "Zeroing-out (option: " << opt << ") ...";

  string option = (opt) ? opt : "all";

  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
    BeamConf_t b = kNDBeamConf[ibeam];
    if(b == kbUndefined) continue;
    for(int isample = 0; isample < kNNDSamples; isample++) {
      NDSample_t s = kNDSample[isample];
      if(s == ksNDUndefined) continue;

      for(int izone = 0; izone < kNMaxBinZones; izone++) {
          if(!fDataNull[ibeam][isample][izone]) {
            fData[ibeam][isample][izone]->SetAll(0.);
          }
      }//izone
      if(!fDataSbNull[ibeam][isample]) {
        fDataSb[ibeam][isample]->SetAll(0.);
      }
    }//isample
  }//ibeam
}
//________________________________________________________________________________________

