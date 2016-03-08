//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include <cassert>

#include "NDFit/NDArrIdx.h"
#include "Messenger/Messenger.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
valor::util::NDArrIdx * valor::util::NDArrIdx::fInstance = 0;
//________________________________________________________________________________________
valor::util::NDArrIdx::NDArrIdx()
{
  this->Init();
  fInstance = 0;
}
//________________________________________________________________________________________
const valor::util::NDArrIdx * valor::util::NDArrIdx::Instance()
{
  return MutableInstance();
}
//________________________________________________________________________________________
valor::util::NDArrIdx * valor::util::NDArrIdx::MutableInstance()
{
  if(fInstance == 0) {
    static valor::util::NDArrIdx::Cleaner cleaner;
    cleaner.DummyMethodAndSilentCompiler();
    fInstance = new valor::util::NDArrIdx;
  }
  return fInstance;
}
//________________________________________________________________________________________
void valor::util::NDArrIdx::Init(void)
{
  assert(kNNDFitParams==kNNDFitParamsNuFlux+kNNDFitParamsNuInt+kNNDFitParamsNuDet);
  
  // Init to -1
  for(int i = 0; i < 2*kNBeamConf; i++) {
     fNDBeamConfIdx [i] = -1;
  }//i

  for(int i = 0; i < 2*kNBeamConf; i++) {
    for(int j = 0; j < 2*kNNDSamples; j++) {
       fNDSampleIdx [i][j] = -1;
    }//j
  }//i

  for(int i = 0; i < 2*kNNDSamples; i++) {
     for(int j = 0; j < 2*kNReacModes; j++) {
         fNDReacModeIdx [i][j] = -1;
     }//i
  }//j

  for(int i = 0; i < 2*knppmax; i++) {
     fNDFitParamIdx[i] = -1;
  }//i

  //
  // Fill-in
  //

  for(int ib = 0; ib < kNBeamConf; ib++) {
    BeamConf_t b = kNDBeamConf[ib];
    if(b == kbUndefined) continue;
    fNDBeamConfIdx[b] = ib;
    LOG("NDArrIdx",pNOTICE)
       << "Beam config: [" << util::AsString(b) << "] --> at slot: " << fNDBeamConfIdx[b];
  }//ib

  for(int ib = 0; ib < kNBeamConf; ib++) {
    BeamConf_t b = kNDBeamConf[ib];
    if(b == kbUndefined) continue;
    for(int is = 0; is < kNNDSamples; is++) {
        NDSample_t s = kNDSample[ib][is];
        if(s == ksNDUndefined) continue;
        fNDSampleIdx [b][s] = is; // HERE
        LOG("NDArrIdx",pNOTICE) 
            << "Fit sample: [" << util::AsString(b)  << "/" 
            << util::AsString(s) << "] --> at slot: " << fNDSampleIdx[s][b];
    }//is
  }//ib

  int ib=0;//HERE
  for(int is = 0; is < kNNDSamples; is++) {
    NDSample_t s = kNDSample[ib][is];
    if(s == ksNDUndefined) continue;
    for(int im = 0; im < kNReacModes; im++) {
        ReacMode_t m = kNDReactionModes[is][im];
        if(m == kmUndefined) continue;
        fNDReacModeIdx [s][m] = im;
        LOG("NDArrIdx",pNOTICE)
               << " ... with contribution from mode: [" << util::AsString(m) 
               << "] --> at slot: " << fNDReacModeIdx [s][m];
    }//im
  }//is

  for(int ip = 0; ip < kNNDFitParams; ip++) {
     PhysParamId_t p = kNDFitParam[ip];
     if(p == kPhypUndefined) continue;
     fNDFitParamIdx[p] = ip;
     LOG("NDArrIdx",pNOTICE)
        << "Fit parameter: " << util::RawParamAsString(p) << " is at slot: " << fNDFitParamIdx[p];
  }
}
//________________________________________________________________________________________

