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
#include "dune/Systematics/SimpleDet2016bFD.h"

using namespace valor;
using namespace valor::conv;
using namespace valor::util;

ClassImp(SimpleDet2016bFD)

//________________________________________________________________________________________
SimpleDet2016bFD::SimpleDet2016bFD() :
CorrelatedSystematics()
{
  std::vector<PhysParamId_t> params;
  
  params.push_back(kNuisEffFDNuMuLikeCCHigh);
  params.push_back(kNuisEffFDNuMuLikeCCLow );
  params.push_back(kNuisEffFDNuELikeCCHigh );
  params.push_back(kNuisEffFDNuELikeCCLow  );

  this->Init(params.size(), &params[0],"detector");
  
  this->SetName("SimpleDet2016bFD");
}
//________________________________________________________________________________________
SimpleDet2016bFD::~SimpleDet2016bFD()
{
  this->CleanUp();
}
//________________________________________________________________________________________
