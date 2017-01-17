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
  std::vector<PhysParamId_t> params;
  
  params.push_back(kNuisEffNuMuCC0pi1trk );
  params.push_back(kNuisEffNuMuCC0pi2trk );
  params.push_back(kNuisEffNuMuCC1piC    );
  params.push_back(kNuisEffNuMuCC1pi0    );
  //~ params.push_back(kNuisEffNuMuCC1piC1pi0);
  params.push_back(kNuisEffNuMuCCoth     );
  params.push_back(kNuisEffNuECC         );
  //~ params.push_back(kNuisEffNuMuCCWS      );
  params.push_back(kNuisEffNC            );
  
  this->Init(params.size(), &params[0],"detector");
  
  this->SetName("SimpleDet2016bND");
}
//________________________________________________________________________________________
SimpleDet2016bND::~SimpleDet2016bND()
{
  this->CleanUp();
}
//________________________________________________________________________________________
