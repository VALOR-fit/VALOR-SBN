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
#include "dune/Conventions/UtlParam.h"
#include "dune/Conventions/OscParamValues.h"

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
      return ( (omp==kNuMixSinsq2Theta) ? valor::conv::duneosc::kInitSinsq2Theta23 : valor::conv::duneosc::kInitSinsqTheta23); 
    case(kPhypMixing13):
      return ( (omp==kNuMixSinsq2Theta) ? valor::conv::duneosc::kInitSinsq2Theta13 : valor::conv::duneosc::kInitSinsqTheta13); 
    case(kPhypMixing12):
      return ( (omp==kNuMixSinsq2Theta) ? valor::conv::duneosc::kInitSinsq2Theta12 : valor::conv::duneosc::kInitSinsqTheta12); 

    case(kPhypDm23sq):
      return ( (dmsqscheme==kNuDmsqFogliLisi) ? valor::conv::duneosc::kInitDmFL : valor::conv::duneosc::kInitDm23sq);

    case(kPhypDm12sq):
      return valor::conv::duneosc::kInitDm12sq;

    case (kPhypCPV):
      return valor::conv::duneosc::kInitDeltaCP;
      
      
    case (kPhypDm41sq) :
      return 0.;
    case (kPhypMixingMuE):
      return 0.;
    case (kPhypMixingMuMu):
      return 0.;
    case (kPhypMixingEE):
      return 0.;
      
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
      return ( (omp==kNuMixSinsq2Theta) ? valor::conv::duneosc::kInitErrSinsq2Theta23 : valor::conv::duneosc::kInitErrSinsqTheta23); 
    case(kPhypMixing13):
      return ( (omp==kNuMixSinsq2Theta) ? valor::conv::duneosc::kInitErrSinsq2Theta13 : valor::conv::duneosc::kInitErrSinsqTheta13); 
    case(kPhypMixing12):
      return ( (omp==kNuMixSinsq2Theta) ? valor::conv::duneosc::kInitErrSinsq2Theta12 : valor::conv::duneosc::kInitErrSinsqTheta12); 

    case(kPhypDm23sq):
      return valor::conv::duneosc::kInitErrDm23sq;

    case(kPhypDm12sq):
      return valor::conv::duneosc::kInitErrDm12sq;

    case (kPhypCPV):
      return valor::conv::duneosc::kInitErrDeltaCP;
      
    case (kPhypDm41sq) :
      return 10.;
    case (kPhypMixingMuE):
      return 1.;
    case (kPhypMixingMuMu):
      return 1.;
    case (kPhypMixingEE):
      return 1.;

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
      return valor::conv::duneosc::kMaxDm23sq;
    case(kPhypDm12sq):
      return valor::conv::duneosc::kMaxDm12sq;

    case (kPhypCPV):
      return 3.1416;
      
    case (kPhypDm41sq) :
      return 1E10;
    case (kPhypMixingMuE):
      return 1.;
    case (kPhypMixingMuMu):
      return 1.;
    case (kPhypMixingEE):
      return 1.;

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
      return valor::conv::duneosc::kMinDm23sq;
    case(kPhypDm12sq):
      return valor::conv::duneosc::kMinDm12sq;

    case (kPhypCPV):
      return -3.1416;
      
            
    case (kPhypDm41sq) :
      return 0;
    case (kPhypMixingMuE):
      return 0.;
    case (kPhypMixingMuMu):
      return 0.;
    case (kPhypMixingEE):
      return 0.;

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
      return ( (omp==kNuMixSinsq2Theta) ? valor::conv::duneosc::kStepSinsq2Theta23 : valor::conv::duneosc::kStepSinsqTheta23); 
    case(kPhypMixing13):
      return ( (omp==kNuMixSinsq2Theta) ? valor::conv::duneosc::kStepSinsq2Theta13 : valor::conv::duneosc::kStepSinsqTheta13); 
    case(kPhypMixing12):
      return ( (omp==kNuMixSinsq2Theta) ? valor::conv::duneosc::kStepSinsq2Theta12 : valor::conv::duneosc::kStepSinsqTheta12); 

    case(kPhypDm23sq):
      return valor::conv::duneosc::kStepDm23sq;

    case(kPhypDm12sq):
      return valor::conv::duneosc::kStepDm12sq;

    case (kPhypCPV):
      return valor::conv::duneosc::kStepDeltaCP;
      
    case (kPhypDm41sq) :
      return 0.05;
    case (kPhypMixingMuE):
      return 0.05;
    case (kPhypMixingMuMu):
      return 0.05;
    case (kPhypMixingEE):
      return 0.05;

    default:
      return -1;
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
void util::InitializeOAPriors()
{
  NuOscMixParam_t omp = Opt::Instance()->gOscMixingParamChoice;
  NuOscDmsqScheme_t  dmsqscheme = Opt::Instance()->GetEffectiveDmsqScheme();
  
  for (int ip = 0 ; ip < conv::kNuis000 ; ip++) {
    PhysParamId_t p = (PhysParamId_t) ip;
    Opt::Instance()->SetGlobalBestFit (p,util::OscParamInitValue(p));
    Opt::Instance()->SetGlobalFitError(p,util::OscParamInitError(p));
  }
    
  Opt::Instance()->SetGlobalBestFit (kPhypDm12sq,valor::conv::duneosc::kInitDm12sq);
  Opt::Instance()->SetGlobalFitError(kPhypDm12sq,valor::conv::duneosc::kInitErrDm12sq);
  Opt::Instance()->SetGlobalBestFit (kPhypCPV,valor::conv::duneosc::kInitDeltaCP);
  Opt::Instance()->SetGlobalFitError(kPhypCPV,valor::conv::duneosc::kInitErrDeltaCP);
  if(omp==kNuMixSinsq2Theta){
    Opt::Instance()->SetGlobalBestFit (kPhypMixing23,valor::conv::duneosc::kInitSinsq2Theta23);
    Opt::Instance()->SetGlobalFitError(kPhypMixing23,valor::conv::duneosc::kInitErrSinsq2Theta23);

    Opt::Instance()->SetGlobalBestFit (kPhypMixing12,valor::conv::duneosc::kInitSinsq2Theta12);
    Opt::Instance()->SetGlobalFitError(kPhypMixing12,valor::conv::duneosc::kInitErrSinsq2Theta12);

    Opt::Instance()->SetGlobalBestFit (kPhypMixing13,valor::conv::duneosc::kInitSinsq2Theta13);
    Opt::Instance()->SetGlobalFitError(kPhypMixing13,valor::conv::duneosc::kInitErrSinsq2Theta13);
  }
  else{
    Opt::Instance()->SetGlobalBestFit (kPhypMixing23,valor::conv::duneosc::kInitSinsqTheta23);
    Opt::Instance()->SetGlobalFitError(kPhypMixing23,valor::conv::duneosc::kInitErrSinsqTheta23);

    Opt::Instance()->SetGlobalBestFit (kPhypMixing12,valor::conv::duneosc::kInitSinsqTheta12);
    Opt::Instance()->SetGlobalFitError(kPhypMixing12,valor::conv::duneosc::kInitErrSinsqTheta12);

    Opt::Instance()->SetGlobalBestFit (kPhypMixing13,valor::conv::duneosc::kInitSinsqTheta13);
    Opt::Instance()->SetGlobalFitError(kPhypMixing13,valor::conv::duneosc::kInitErrSinsqTheta13);
  }

  if(dmsqscheme==kNuDmsqFogliLisi)
    Opt::Instance()->SetGlobalBestFit (kPhypDm23sq,valor::conv::duneosc::kInitDmFL);
  else
    Opt::Instance()->SetGlobalBestFit (kPhypDm23sq,valor::conv::duneosc::kInitDm23sq);

  Opt::Instance()->SetGlobalFitError(kPhypDm23sq,valor::conv::duneosc::kInitErrDm23sq);

}
//________________________________________________________________________________________                                                                  
