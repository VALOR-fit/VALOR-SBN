//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

// system
#include <cassert>
#include <cstdlib>
#include <iostream>
// fmwk
#include "Conventions/Constants.h"
#include "Messenger/Messenger.h"
#include "Utilities/UtlSystem.h"
// dune
#include "SDFit/NDFitParams.h"
#include "Systematics/VALORInt2016a.h"

using namespace valor;
using namespace valor::conv;
using namespace valor::util;

ClassImp(VALORInt2016a)

//________________________________________________________________________________________
VALORInt2016a::VALORInt2016a() :
CorrelatedSystematics()
{
  int nparams = kNFitParamsNuInt;
  PhysParamId_t params[nparams];
  const bool * is_relevant = conv::kFitIsNuIntRelated;
  
  int i_params = 0;
  for(int i = 0; i < conv::kNFitParams; i++) {
    PhysParamId_t p = conv::kFitParam[i];
    if (is_relevant[i]) {
      params[i_params] = p;
      i_params++;
    }
  }
  
  // Check we have the right number of parameters labelled as related to this class
  if (nparams-i_params) {
    LOG("VALORInt2016a",pFATAL)<<"kNFitParamsNuInt does not match kFitIsNuIntRelated";
    util::Die(-1); return;
  }
  
  this->Init(nparams, params,"interaction");
  
  this->SetName("VALORInt2016a");
}
//________________________________________________________________________________________
VALORInt2016a::~VALORInt2016a()
{
  this->CleanUp();
}
//________________________________________________________________________________________
