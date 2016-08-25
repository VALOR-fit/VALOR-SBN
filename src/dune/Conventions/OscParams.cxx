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
      return ( (omp==kNuMixSinsq2Theta) ? kInitSinsq2Theta23 : kInitSinsqTheta23); 
    case(kPhypMixing13):
      return ( (omp==kNuMixSinsq2Theta) ? kInitSinsq2Theta13 : kInitSinsqTheta13); 
    case(kPhypMixing12):
      return ( (omp==kNuMixSinsq2Theta) ? kInitSinsq2Theta12 : kInitSinsqTheta12); 

    case(kPhypDm23sq):
      return ( (dmsqscheme==kNuDmsqFogliLisi) ? kInitDmFL : kInitDm23sq);

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
double util::OscParamMaxValue(conv::PhysParamId_t p)
{
  switch (p) 
    {
    case(kPhypMixing23):
      return 1.0;
    case(kPhypMixing13):
      return 1.0;
    case(kPhypMixing12):
      return 1.0;

    case(kPhypDm23sq):
      return kMaxDm23sq;
    case(kPhypDm12sq):
      return kMaxDm12sq;
      
    case (kPhypCPV):
	return 3.1416;

    default: 
      return -1; 
    }

  return -1;
}
//________________________________________________________________________________________
double util::OscParamMinValue(conv::PhysParamId_t p)
{
  switch (p) 
    {
    case(kPhypMixing23):
      return -1.0;
    case(kPhypMixing13):
      return -1.0;
    case(kPhypMixing12):
      return -1.0;

    case(kPhypDm23sq):
      return kMinDm23sq;
    case(kPhypDm12sq):
      return kMinDm12sq;
      
    case (kPhypCPV):
	return -3.1416;

    default: 
      return -1; 
    }

  return -1;
}
//________________________________________________________________________________________
