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
#include "Systematics/MINERVAFlux2016a.h"

using namespace valor;
using namespace valor::conv;
using namespace valor::util;

ClassImp(MINERVAFlux2016a)

//________________________________________________________________________________________
MINERVAFlux2016a::MINERVAFlux2016a() :
CorrelatedSystematics()
{
  int nparams = kNNDFitParamsNuFlux;
  PhysParamId_t params[nparams];
  const bool * is_relevant = conv::kNDFitIsNuFluxRelated;
  
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
    LOG("MINERVAFlux2016a",pFATAL)<<"kNNDFitParamsNuFlux does not match kNDFitIsNuFluxRelated";
    util::Die(-1); return;
  }
  
  this->Init(nparams, params,"flux");
  
  this->SetName("MINERVAFlux2016a");
}
//________________________________________________________________________________________
MINERVAFlux2016a::~MINERVAFlux2016a()
{
  this->CleanUp();
}
//________________________________________________________________________________________
