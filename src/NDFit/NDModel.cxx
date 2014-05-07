//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include <ostream>

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
#include "Messenger/Messenger.h"
//lbnx
#include "Conventions/ReacMode.h"
#include "NDFit/NDModel.h"
#include "NDFit/NDSample.h"

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
string NDModel::Name(void)
{
  return "LBNxND";
}
//________________________________________________________________________________________
bool NDModel::Read(string /*file*/, Option_t * /*opt*/)
{
  //...
  return true;
}
//________________________________________________________________________________________
bool NDModel::Generate(const PhysHypothesis & ph)
{
  fPhysHypothesis.Copy(ph);
  PhysHypothesis_t hyp = fPhysHypothesis.Hypothesis();

  LOG("NDModel",pINFO)  
     << "Generating model predictions for the input hypothesis: " 
     << fPhysHypothesis;



  //
  //
  // ...
  //
  //



  LOG("NDModel",pDEBUG) << "Done generating predictions";

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
bool NDModel::Write(TObjArray * array, const char * tag, Option_t * /*write_opt*/)
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
void NDModel::Init(void)
{
  for(int isample = 0; isample < kNNDSamples; isample++) {
    for(int imode = 0; imode < kNReacModes; imode++) {
      for(int izone = 0; izone < kNMaxBinZones; izone++) {
         fMCTemplNom[isample][imode][izone] = 0;
      }//izone
    }//imode
  }//isample
}
//________________________________________________________________________________________
void NDModel::Book(void)
{
  for(int isample = 0; isample < kNNDSamples; isample++) {
    NDSample_t s = kNDSample[isample];
    if(s == ksNDUndefined) continue;
    for(int imode = 0; imode < kNReacModes; imode++) {
      ReacMode_t m = kNDReactionModes[isample][imode];
      if(m == kmUndefined) continue;
      for(int izone = 0; izone < kNMaxBinZones; izone++) {
         const int n_ereco_bins = util::NumErecoBins(s,izone);
         const int n_yreco_bins = util::NumYrecoBins(s,izone);
         if(n_ereco_bins <= 0 || n_yreco_bins <= 0) continue;
         fMCTemplNom[isample][imode][izone] = new VALORArray(n_ereco_bins,n_yreco_bins);
      }//izone
    }//imode
  }//isample
}
//________________________________________________________________________________________
void NDModel::Clean(void)
{
  for(int isample = 0; isample < kNNDSamples; isample++) {
    for(int imode = 0; imode < kNReacModes; imode++) {
      for(int izone = 0; izone < kNMaxBinZones; izone++) {
        if(fMCTemplNom[isample][imode][izone]) delete fMCTemplNom[isample][imode][izone];
        fMCTemplNom[isample][imode][izone] = 0;
      }//izone
    }//imode
  }//isample
}
//________________________________________________________________________________________
