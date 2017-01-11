//________________________________________________________________________________________
/*

Copyright (c) 2010-2017, The VALOR Fitting Group, All Rights Reserved.

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
#include "dune/Systematics/VALORInt2017aFGT.h"

using namespace valor;
using namespace valor::conv;
using namespace valor::util;

ClassImp(VALORInt2017aFGT)

//________________________________________________________________________________________
VALORInt2017aFGT::VALORInt2017aFGT() :
CorrelatedSystematics()
{
  std::vector<PhysParamId_t> params;
  
  params.push_back(kNuisIntNuCCQE1               );
  params.push_back(kNuisIntNuCCQE2               );
  params.push_back(kNuisIntNuCCQE3               );
  params.push_back(kNuisIntNuBarCCQE1            );
  params.push_back(kNuisIntNuBarCCQE2            );
  params.push_back(kNuisIntNuBarCCQE3            );
  params.push_back(kNuisIntNuCCMEC               );
  params.push_back(kNuisIntNuBarCCMEC            );
  params.push_back(kNuisIntNuCC1piz1             );
  params.push_back(kNuisIntNuCC1piz2             );
  params.push_back(kNuisIntNuCC1piz3             );
  params.push_back(kNuisIntNuCC1pic1             );
  params.push_back(kNuisIntNuCC1pic2             );
  params.push_back(kNuisIntNuCC1pic3             );
  params.push_back(kNuisIntNuBarCC1piz1          );
  params.push_back(kNuisIntNuBarCC1piz2          );
  params.push_back(kNuisIntNuBarCC1piz3          );
  params.push_back(kNuisIntNuBarCC1pic1          );
  params.push_back(kNuisIntNuBarCC1pic2          );
  params.push_back(kNuisIntNuBarCC1pic3          );
  params.push_back(kNuisIntNuCC2Pi               );
  params.push_back(kNuisIntNuBarCC2Pi            );
  params.push_back(kNuisIntNuDIS1                );
  params.push_back(kNuisIntNuDIS2                );
  params.push_back(kNuisIntNuDIS3                );
  params.push_back(kNuisIntNuBarDIS1             );
  params.push_back(kNuisIntNuBarDIS2             );
  params.push_back(kNuisIntNuBarDIS3             );
  params.push_back(kNuisIntNormNuCoherent        );
  params.push_back(kNuisIntNormNuBarCoherent     );
  params.push_back(kNuisIntNuNormNC              );
  params.push_back(kNuisIntNuBarNormNC           );
  params.push_back(kNuisIntNormNuMuToNuE         );
  params.push_back(kNuisIntNormNuMuBarToNuEBar   );
  params.push_back(kNuisIntPiMeanFreePath        );
  params.push_back(kNuisIntNucMeanFreePath       );
  params.push_back(kNuisIntFracPiChargeExchange  );
  params.push_back(kNuisIntFracPiInelastic       );
  params.push_back(kNuisIntFracPiAbsorb          );
  params.push_back(kNuisIntFracPiProduction      );
  params.push_back(kNuisIntFracNucChargeExchange );
  params.push_back(kNuisIntFracNucInelastic      );
  params.push_back(kNuisIntFracNucAbsorb         );
  params.push_back(kNuisIntFracNucProduction     );
  params.push_back(kNuisIntTarget                );

  this->Init(params.size(), &params[0],"interaction");
  
  this->SetName("VALORInt2017aFGT");
}
//________________________________________________________________________________________
VALORInt2017aFGT::~VALORInt2017aFGT()
{
  this->CleanUp();
}
//________________________________________________________________________________________
