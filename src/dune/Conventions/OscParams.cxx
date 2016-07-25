//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

//fmw
#include "valor/Conventions/NuOscMixParam.h"
#include "valor/Conventions/NuOscDmsqScheme.h"
#include "valor/Conventions/Opt.h"

//dune
#include "dune/Conventions/FitParam.h"
#include "dune/Conventions/OscParams.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
double util::OscParamInitValue(conv::PhysParamId_t p)
{

  NuOscMixParam_t omp = Opt::Instance()->gOscMixingParamChoice;
  NuOscDmsqScheme_t  dmsqscheme = Opt::Instance()->GetEffectiveDmsqScheme();

  switch (p) 
    {
    case(kPhypMixing23):
      return ( kInitSinsq2Theta23 ? (omp==kNuMixSinsq2Theta) : kInitSinsqTheta23); 
    case(kPhypMixing13):
      return ( kInitSinsq2Theta13 ? (omp==kNuMixSinsq2Theta) : kInitSinsqTheta13); 
    case(kPhypMixing12):
      return ( kInitSinsq2Theta12 ? (omp==kNuMixSinsq2Theta) : kInitSinsqTheta12); 

    case(kPhypDm23sq):
      return ( kInitDmFL ? (dmsqscheme==kNuDmsqFogliLisi) : kInitDm23sq);

    case(kPhypDm12sq):
      return kInitDm12sq;
      
    case (kPhypCPV):
      return kInitDeltaCP;

    default: 
      return -1; 

    }

  return -1;
}
//________________________________________________________________________________________
