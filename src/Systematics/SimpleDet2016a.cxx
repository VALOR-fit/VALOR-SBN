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
#include "Conventions/FitParam.h"
#include "Systematics/SimpleDet2016a.h"

using namespace valor;
using namespace valor::conv;
using namespace valor::util;

ClassImp(SimpleDet2016a)

//________________________________________________________________________________________
SimpleDet2016a::SimpleDet2016a() :
CorrelatedSystematics()
{
  int nparams = kNFitParamsNuDet;
  PhysParamId_t params[nparams];
  const bool * is_relevant = conv::kFitIsNuDetRelated;
  
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
    LOG("SimpleDet2016a",pFATAL)<<"kNFitParamsNuDet does not match kFitIsNuDetRelated";
    util::Die(-1); return;
  }
  
  this->Init(nparams, params,"detector");
  
  this->SetName("SimpleDet2016a");
}
//________________________________________________________________________________________
SimpleDet2016a::~SimpleDet2016a()
{
  this->CleanUp();
}
//________________________________________________________________________________________
