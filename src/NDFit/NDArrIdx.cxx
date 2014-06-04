//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

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
valor::util::NDArrIdx * valor::util::NDArrIdx::Instance()
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
  // Init to -1

  for(int i = 0; i < 2*kNBeamConf; i++) {
     fNDBeamConfIdx [i] = -1;
  }
  for(int i = 0; i < 2*kNNDSamples; i++) {
     fNDSampleIdx [i] = -1;
     for(int j = 0; j < 2*kNReacModes; j++) {
         fNDReacModeIdx [i][j] = -1;
     }//i
  }//j
/*
  for(int i = 0; i < 2*knppmax; i++) {
     fNDFitParamIdx[i] = -1;
  }//i
*/
  //
  // Fill-in
  //

  for(int ib = 0; ib < kNBeamConf; ib++) {
    BeamConf_t b = kNDBeamConf[ib];
    if(b == kbUndefined) continue;
    fNDBeamConfIdx[b] = ib;
    LOG("NDArrIdx",pNOTICE)
       << "Beam config: " << util::AsString(b) << " is at slot: " << fNDBeamConfIdx[b];
  }//ib

  for(int is = 0; is < kNNDSamples; is++) {
     NDSample_t s = kNDSample[is];
     if(s == ksNDUndefined) continue;
     fNDSampleIdx [s] = is;

     LOG("NDArrIdx",pNOTICE) 
        << "Sample: " << util::AsString(s) << " is at slot: " << fNDSampleIdx[s];

     for(int im = 0; im < kNReacModes; im++) {
         ReacMode_t m = kNDReactionModes[is][im];
         if(m == kmUndefined) continue;
         fNDReacModeIdx [s][m] = im;
         LOG("NDArrIdx",pNOTICE)
            << "Mode: " << util::AsString(s) << "/" << util::AsString(m)
            << " is at slot: " << fNDReacModeIdx [s][m];
     }//im
  }//is 
/*
  for(int ip = 0; ip < 2*knppmax; ip++) {
     PhysParamId_t p = kNDFitParam[ip];
     if(p == kPhypUndefined) continue;
     fNDFitParamIdx[p] = ip;
     LOG("NDArrIdx",pNOTICE)
        << "Fit parameter: " << util::RawParamAsString(p) << " is at slot: " << fNDFitParamIdx[p];
  }
*/
}
//________________________________________________________________________________________

