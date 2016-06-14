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
#include "dune/Systematics/MINERVAFlux2016aFD.h"

using namespace valor;
using namespace valor::conv;
using namespace valor::util;

ClassImp(MINERVAFlux2016aFD)

//________________________________________________________________________________________
MINERVAFlux2016aFD::MINERVAFlux2016aFD() :
CorrelatedSystematics()
{
  int nparams = kNFitParamsNuFlux;
  PhysParamId_t params[nparams];
  bool (*is_relevant)(conv::PhysParamId_t) = util::IsFDFluxRelated;
  
  int i_params = 0;
  for(int i = 0; i < conv::kNFitParams; i++) {
    PhysParamId_t p = conv::kFitParam[i];
    if (is_relevant(p)) {
      params[i_params] = p;
      i_params++;
    }
  }
  
  // Check we have the right number of parameters labelled as related to this class
  if (nparams-i_params) {
    LOG("MINERVAFlux2016aFD",pFATAL)<<"kNFitParamsNuFlux does not match kFitIsNuFluxRelated";
    util::Die(-1); return;
  }
  
  this->Init(nparams, params,"flux");
  
  this->SetName("MINERVAFlux2016aFD");
}
//________________________________________________________________________________________
MINERVAFlux2016aFD::~MINERVAFlux2016aFD()
{
  this->CleanUp();
}
//________________________________________________________________________________________
