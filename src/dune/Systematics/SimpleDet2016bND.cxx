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
#include "valor/Conventions/Constants.h"
#include "valor/Messenger/Messenger.h"
#include "valor/Utilities/UtlSystem.h"
// dune
#include "dune/Conventions/FitParam.h"
#include "dune/Systematics/SimpleDet2016bND.h"

using namespace valor;
using namespace valor::conv;
using namespace valor::util;

ClassImp(SimpleDet2016bND)

//________________________________________________________________________________________
SimpleDet2016bND::SimpleDet2016bND() :
CorrelatedSystematics()
{
  int nparams = kNFitParamsNuDetND;
  PhysParamId_t params[nparams];
  const bool * is_relevant = conv::kFitIsNuNDDetRelated;
  
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
    LOG("SimpleDet2016bND",pFATAL)<<"kNFitParamsNuDet does not match kFitIsNuDetRelated";
    util::Die(-1); return;
  }
  
  this->Init(nparams, params,"detector");
  
  this->SetName("SimpleDet2016bND");
}
//________________________________________________________________________________________
SimpleDet2016bND::~SimpleDet2016bND()
{
  this->CleanUp();
}
//________________________________________________________________________________________
