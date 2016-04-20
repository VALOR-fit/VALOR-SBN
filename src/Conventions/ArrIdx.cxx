//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include <cassert>

// fmwk
#include "Messenger/Messenger.h"
// dune
#include "Conventions/ArrIdx.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
valor::util::ArrIdx * valor::util::ArrIdx::fInstance = 0;
//________________________________________________________________________________________
valor::util::ArrIdx::ArrIdx()
{
  this->Init();
  fInstance = 0;
}
//________________________________________________________________________________________
const valor::util::ArrIdx * valor::util::ArrIdx::Instance()
{
  return MutableInstance();
}
//________________________________________________________________________________________
valor::util::ArrIdx * valor::util::ArrIdx::MutableInstance()
{
  if(fInstance == 0) {
    static valor::util::ArrIdx::Cleaner cleaner;
    cleaner.DummyMethodAndSilentCompiler();
    fInstance = new valor::util::ArrIdx;
  }
  return fInstance;
}
//________________________________________________________________________________________
void valor::util::ArrIdx::Init(void)
{
  assert(kNFitParams==kNFitParamsNuFlux+kNFitParamsNuInt+kNFitParamsNuDet);
  
  // Init to -1
  for(int i = 0; i < 2*kNBeamConf; i++) {
     fBeamConfIdx [i] = -1;
  }//i

  for(int i = 0; i < 2*kNBeamConf; i++) {
    for(int j = 0; j < 2*kNSamples; j++) {
       fSampleIdx [i][j] = -1;
    }//j
  }//i

  for(int i = 0; i < 2*kNSamples; i++) {
     for(int j = 0; j < 2*kNReacModes; j++) {
         fReacModeIdx [i][j] = -1;
     }//i
  }//j

  for(int i = 0; i < 2*knppmax; i++) {
     fFitParamIdx[i] = -1;
  }//i

  //
  // Fill-in
  //

  for(int ib = 0; ib < kNBeamConf; ib++) {
    BeamConf_t b = kBeamConf[ib];
    if(b == kbUndefined) continue;
    fBeamConfIdx[b] = ib;
    LOG("ArrIdx",pINFO)
       << "Beam config: [" << util::AsString(b) << "] --> at slot: " << fBeamConfIdx[b];
  }//ib

  for(int ib = 0; ib < kNBeamConf; ib++) {
    BeamConf_t b = kBeamConf[ib];
    if(b == kbUndefined) continue;
    for(int is = 0; is < kNSamples; is++) {
        Sample_t s = kSample[ib][is];
        if(s == ksUndefined) continue;
        fSampleIdx [b][s] = is; // HERE
        LOG("ArrIdx",pINFO) 
            << "Fit sample: [" << util::AsString(b)  << "/" 
            << util::AsString(s) << "] --> at slot: " << fSampleIdx[s][b];
    }//is
  }//ib

  int ib=0;//HERE
  for(int is = 0; is < kNSamples; is++) {
    Sample_t s = kSample[ib][is];
    if(s == ksUndefined) continue;
    for(int im = 0; im < kNReacModes; im++) {
        ReacMode_t m = kReactionModes[is][im];
        if(m == kmUndefined) continue;
        fReacModeIdx [s][m] = im;
        LOG("ArrIdx",pINFO)
               << " ... with contribution from mode: [" << util::AsString(m) 
               << "] --> at slot: " << fReacModeIdx [s][m];
    }//im
  }//is

  for(int ip = 0; ip < kNFitParams; ip++) {
     PhysParamId_t p = kFitParam[ip];
     if(p == kPhypUndefined) continue;
     fFitParamIdx[p] = ip;
     LOG("ArrIdx",pINFO)
        << "Fit parameter: " << util::AsString(p) 
        << " is at slot: " << fFitParamIdx[p];
  }
}
//________________________________________________________________________________________

