//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

//fmw
#include "valor/Messenger/Messenger.h"
#include "valor/Conventions/NuOscMixParam.h"
#include "valor/Conventions/NuOscDmsqScheme.h"
#include "valor/Conventions/Opt.h"
#include "valor/Utilities/Rnd.h"
#include "valor/Utilities/UtlSystem.h"

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
double util::OscParamInitError(conv::PhysParamId_t p)
{

  NuOscMixParam_t omp = Opt::Instance()->gOscMixingParamChoice;

  switch (p) 
  {
    case(kPhypMixing23):
      return ( (omp==kNuMixSinsq2Theta) ? kInitErrSinsq2Theta23 : kInitErrSinsqTheta23); 
    case(kPhypMixing13):
      return ( (omp==kNuMixSinsq2Theta) ? kInitErrSinsq2Theta13 : kInitErrSinsqTheta13); 
    case(kPhypMixing12):
      return ( (omp==kNuMixSinsq2Theta) ? kInitErrSinsq2Theta12 : kInitErrSinsqTheta12); 

    case(kPhypDm23sq):
      return kInitErrDm23sq;

    case(kPhypDm12sq):
      return kInitErrDm12sq;

    case (kPhypCPV):
      return kInitErrDeltaCP;

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
      return 0.0;
    case(kPhypMixing13):
      return 0.0;
    case(kPhypMixing12):
      return 0.0;

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
double util::OscParamStepSize (conv::PhysParamId_t p)
{
  NuOscMixParam_t omp = Opt::Instance()->gOscMixingParamChoice;
  switch (p) 
  {
    case(kPhypMixing23):
      return ( (omp==kNuMixSinsq2Theta) ? kStepSinsq2Theta23 : kStepSinsqTheta23); 
    case(kPhypMixing13):
      return ( (omp==kNuMixSinsq2Theta) ? kStepSinsq2Theta13 : kStepSinsqTheta13); 
    case(kPhypMixing12):
      return ( (omp==kNuMixSinsq2Theta) ? kStepSinsq2Theta12 : kStepSinsqTheta12); 

    case(kPhypDm23sq):
      return kStepDm23sq;

    case(kPhypDm12sq):
      return kStepDm12sq;

    case (kPhypCPV):
      return kStepDeltaCP;

    default: 
      LOG("Failed to get OA parameter step size",pFATAL);
      util::Die(-1);
  }
  return -1;
}
//________________________________________________________________________________________
double util::GetRandomizedOscParam(conv::PhysParamId_t p, string mode)
{

  double min = util::OscParamMinValue(p);
  double max = util::OscParamMaxValue(p);
  double rndm = min-1;
  while((rndm<min)||(rndm>max)){ //keep throwing a random number if outside limits
    if((p==kPhypCPV) || (mode == "flat")) 
      rndm = Rnd::Instance()->RndToyMCosc().Uniform(min,max);
    else if(mode == "gaus"){
      double mean  = util::OscParamInitValue(p);
      double sigma = mean * util::OscParamInitError(p);
      rndm = Rnd::Instance()->RndToyMCosc().Gaus(mean,sigma);//This does not work for deltaCP, mean = 0
    }
  }
  return rndm;
}
//________________________________________________________________________________________
