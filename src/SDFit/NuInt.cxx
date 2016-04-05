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
#include "SDFit/NuInt.h"

using namespace valor;
using namespace valor::conv;
using namespace valor::util;

ClassImp(NuInt)

//________________________________________________________________________________________
NuInt::NuInt() :
CorrelatedSystematics()
{
  int nparams = kNNDFitParamsNuInt;
  PhysParamId_t params[nparams];
  const bool * is_relevant = conv::kNDFitIsNuIntRelated;
  
  int i_params = 0;
  for(int i = 0; i < conv::kNNDFitParams; i++) {
    PhysParamId_t p = conv::kNDFitParam[i];
    if (is_relevant[i]) {
      params[i_params] = p;
      i_params++;
    }
  }
  
  // Check we have the right number of parameters labelled as related to this class
  if (nparams-i_params) {
    LOG("NuInt",pFATAL)<<"kNNDFitParamsNuInt does not match kNDFitIsNuIntRelated";
    util::Die(-1); return;
  }
  
  this->Init(nparams, params);
  
  this->SetName("NuInt");
  this->SetXMLNodeName("interaction");
}
//________________________________________________________________________________________
NuInt::~NuInt()
{
  this->CleanUp();
}
//________________________________________________________________________________________
