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
#include "dune/Systematics/MINERVAFlux2016aNDFHC.h"

using namespace valor;
using namespace valor::conv;
using namespace valor::util;

ClassImp(MINERVAFlux2016aNDFHC)

//________________________________________________________________________________________
MINERVAFlux2016aNDFHC::MINERVAFlux2016aNDFHC() :
CorrelatedSystematics()
{
  std::vector<PhysParamId_t> params;
  
  params.push_back(kNuisFHCNuMuFlux00   );
  params.push_back(kNuisFHCNuMuFlux01   );
  params.push_back(kNuisFHCNuMuFlux02   );
  params.push_back(kNuisFHCNuMuFlux03   );
  params.push_back(kNuisFHCNuMuFlux04   );
  params.push_back(kNuisFHCNuMuFlux05   );
  params.push_back(kNuisFHCNuMuFlux06   );
  params.push_back(kNuisFHCNuMuFlux07   );
  params.push_back(kNuisFHCNuMuFlux08   );
  params.push_back(kNuisFHCNuMuFlux09   );
  params.push_back(kNuisFHCNuMuFlux10   );
  params.push_back(kNuisFHCNuMuFlux11   );
  params.push_back(kNuisFHCNuMuFlux12   );
  params.push_back(kNuisFHCNuMuFlux13   );
  params.push_back(kNuisFHCNuMuFlux14   );
  params.push_back(kNuisFHCNuMuFlux15   );
  params.push_back(kNuisFHCNuMuFlux16   );
  params.push_back(kNuisFHCNuMuFlux17   );
  params.push_back(kNuisFHCNuMuFlux18   );
  params.push_back(kNuisFHCNuMuBarFlux00);
  params.push_back(kNuisFHCNuMuBarFlux01);
  params.push_back(kNuisFHCNuMuBarFlux02);
  params.push_back(kNuisFHCNuMuBarFlux03);
  params.push_back(kNuisFHCNuMuBarFlux04);
  params.push_back(kNuisFHCNuMuBarFlux05);
  params.push_back(kNuisFHCNuMuBarFlux06);
  params.push_back(kNuisFHCNuMuBarFlux07);
  params.push_back(kNuisFHCNuMuBarFlux08);
  params.push_back(kNuisFHCNuMuBarFlux09);
  params.push_back(kNuisFHCNuMuBarFlux10);
  params.push_back(kNuisFHCNuMuBarFlux11);
  params.push_back(kNuisFHCNuMuBarFlux12);
  params.push_back(kNuisFHCNuMuBarFlux13);
  params.push_back(kNuisFHCNuMuBarFlux14);
  params.push_back(kNuisFHCNuMuBarFlux15);
  params.push_back(kNuisFHCNuMuBarFlux16);
  params.push_back(kNuisFHCNuMuBarFlux17);
  params.push_back(kNuisFHCNuMuBarFlux18);
  params.push_back(kNuisFHCNuEFlux00    );
  params.push_back(kNuisFHCNuEFlux01    );
  params.push_back(kNuisFHCNuEFlux02    );
  params.push_back(kNuisFHCNuEFlux03    );
  params.push_back(kNuisFHCNuEFlux04    );
  params.push_back(kNuisFHCNuEFlux05    );
  params.push_back(kNuisFHCNuEFlux06    );
  params.push_back(kNuisFHCNuEBarFlux00 );
  params.push_back(kNuisFHCNuEBarFlux01 );
  params.push_back(kNuisFHCNuEBarFlux02 );
  params.push_back(kNuisFHCNuEBarFlux03 );
  params.push_back(kNuisFHCNuEBarFlux04 );
  params.push_back(kNuisFHCNuEBarFlux05 );
  params.push_back(kNuisFHCNuEBarFlux06 );

  this->Init(params.size(), &params[0],"flux");
  
  this->SetName("MINERVAFlux2016aNDFHC");
}
//________________________________________________________________________________________
MINERVAFlux2016aNDFHC::~MINERVAFlux2016aNDFHC()
{
  this->CleanUp();
}
//________________________________________________________________________________________
