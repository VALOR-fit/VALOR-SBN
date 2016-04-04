//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#define __show_init_mesg_info__  
//#define __init_check_inverse__
//#define __show_init_mesg_debug__   
//#define __show_cholesky_mesg_info__
//#define __show_cholesky_mesg_debug__
//#define __show_tweak_mesg_debug__
//#define __show_update_correlated_mesg_debug__
//#define __show_chisqpenalty_mesg_debug__
//#define __show_chisqpenalty_mesg_debug2__

// system
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iomanip> 
#include <limits> 
// root
#include <TRandom3.h>
#include <TMath.h>
// fmwk
#include "Conventions/Constants.h"
#include "Utilities/UtlXML.h"
#include "Utilities/UtlNumStat.h"
#include "Utilities/UtlSystem.h"
#include "Utilities/UtlPrint.h"
#include "Utilities/Rnd.h"
#include "Messenger/Messenger.h"
#include "FitCore/FitParamList.h"
#include "FitCore/PhysParamList.h"
// dune
#include "NDFit/NDFitParams.h"
#include "NDFit/NDRFL.h"
#include "NDFit/NuInt.h"

using std::cout;
using std::cerr;
using std::endl;
using std::setw;
using std::setprecision;

using namespace valor;
using namespace valor::conv;
using namespace valor::util;

ClassImp(NuInt)

//________________________________________________________________________________________
NuInt::NuInt() :
TObject()
{
  this->Init();
}
//________________________________________________________________________________________
NuInt::~NuInt()
{
  this->CleanUp();
}
//________________________________________________________________________________________
void NuInt::Init(void)
{
  fInitialValues        = new TVectorD(conv::kNNDFitParamsNuInt);
  fCurrentValues        = new TVectorD(conv::kNNDFitParamsNuInt);
  
  fCovMtrx              = 0;
  fCovMtrxInv           = 0;
  fCovMtrxChoL          = 0; 
  
  fIsTweaked            = false;
  
  fInitialArray = fInitialValues->GetMatrixArray();
  fCurrentArray = fCurrentValues->GetMatrixArray();
  
  for (int i = 0 ; i < conv::knppmax; i++) {
    fParam2Idx[i] = -1;
  }
  
  int i_params_int = 0;
  for(int i = 0; i < conv::kNNDFitParams; i++) {
    PhysParamId_t p = conv::kNDFitParam[i];
    if (conv::kNDFitIsNuIntRelated[i]) {
      fNuIntIndexToPhysParam[i_params_int] = p;
      fParam2Idx[p] = i_params_int;
      i_params_int++;
    }
  }
  
  for(int i = 0 ; i < fCurrentValues->GetNrows(); i++ ) {
    fInitialArray[i] = 1.;
    fCurrentArray[i] = 1.;
  }
  
  // Check we have the right number of parameters labelled as related to this class
  if (conv::kNNDFitParamsNuInt-i_params_int) {
    LOG("NuInt",pERROR)<<"kNNDFitParamsNuInt does not match kNDFitIsNuIntRelated";
    util::Die(-1); return;
  }
}
//________________________________________________________________________________________
void NuInt::CleanUp(void)
{
  if ( fInitialValues ) delete fInitialValues;
  if ( fCurrentValues ) delete fCurrentValues;
  if ( fCovMtrx       ) delete fCovMtrx;
  if ( fCovMtrxInv    ) delete fCovMtrxInv;
  if ( fCovMtrxChoL   ) delete fCovMtrxChoL;  
}
//________________________________________________________________________________________
bool NuInt::Read(TXMLEngine* xml, XMLNodePointer_t root_node)
{
  this->CleanUp();
  this->Init();
  
  // Get neutrino interaction model param covariance matrix
  fCovMtrx = util::XML2TMatrixD(xml,root_node,"syst/interaction/covariance_matrix");  
  if(!fCovMtrx) {
    LOG("NuInt",pFATAL) 
       << "No neutrino interaction model param covariance matrix was found.";
    util::Die(1); return false;
  }
  
  // Check matrix size
  TMatrixD & cov = *fCovMtrx;
  const int np = conv::kNNDFitParamsNuInt;  
  if(cov.GetNrows() != np || cov.GetNcols() != np) 
  {
     LOG("NuInt",pFATAL)
        << "\n Neutrino interaction model param covariance matrix has unexpected size!"
        << "\n Expecting: " <<  np << " x " << np << " matrix"
        << "\n Found: " << cov.GetNrows() << " x " <<  cov.GetNcols() << " matrix";
      util::Die(1); return false;
  }
  
  // Do Cholesky decomposition
  LOG("NuInt",pNOTICE) 
    << "Running  Cholesky decomposition of interaction model param covariance matrix ";
  this->CholeskyDecomposeMatrix();
  double det;
  
  // Calculate matrix inversion using Cholesky triangular matrices - should be most accurate.
  TMatrixD cholInv(*fCovMtrxChoL);
  cholInv.Invert(&det);
  LOG("NuInt",pNOTICE) 
     << "Interaction param covariance matrix decomposition determinant: " << det;
  TMatrixD cholInvT(TMatrixD::kTransposed,cholInv);
  fCovMtrxInv = new TMatrixD(cholInvT * cholInv);
  
#ifdef __init_check_inverse__
  bool failure = false;
  TMatrixD covTimesInverse = (cov * (*fCovMtrxInv));
  for (int ii = 0 ; ii < np ; ii++) {
    for (int jj = 0 ; jj < np ; jj++) {
      int target = (ii==jj);
      if (fabs(covTimesInverse[ii][jj]-target) > 1E-9) {
        LOG("NuInt",pERROR) 
          << "Bad inversion of neutrino interaction model param covariance matrix"
          << " - element: " << ii << " , " << jj << ": " 
          << covTimesInverse[ii][jj]-target << (ii==jj?"*":"");
        failure = true;
      }
    }
  }
  if (failure) {util::Die(1); return false;}
#endif // __init_check_inverse__
  
#ifdef __show_init_mesg_debug__
  LOG("NuInt",pDEBUG) 
     << "Input neutrino interaction model param covariance matrix: "; 
  util::PrintMatrix(cov,7,5); // would be nice to use the same stream and threshold as mesg above
  LOG("NuInt",pDEBUG) 
     << "Inverse neutrino interaction model param covariance matrix: ";
  util::PrintMatrix(*fCovMtrxInv,7,5); // would be nice to use the same stream and threshold as mesg above
#endif
  
  return true;
}
//________________________________________________________________________________________
double NuInt::CurrentValue(PhysParamId_t p) const
{
  int idx = this->Param2Idx(p); 
  return fCurrentArray[idx];
}
//________________________________________________________________________________________
double NuInt::CurrentValueByIndex(int idx) const
{
  return fCurrentArray[idx];
}
//________________________________________________________________________________________
double NuInt::OneSigmaError(PhysParamId_t p) const
{
  const TMatrixD & cov = *fCovMtrx;
  int idx = this->Param2Idx(p); 
  return TMath::Sqrt(cov[idx][idx]);
}
//________________________________________________________________________________________
double NuInt::OneSigmaErrorByIndex(int idx) const
{
  const TMatrixD & cov = *fCovMtrx;
  return TMath::Sqrt(cov[idx][idx]);
}
//________________________________________________________________________________________
void NuInt::Tweak(
  bool       force_inputs, // force the input params or generate random ones internally  
  TVectorD * input_vec     // input vector of interaction model params - Set to 0 to reset to nominal ones 
)
{
#ifdef __show_tweak_mesg_debug__
  LOG("NuInt",pDEBUG)  << "Tweaking neutrino interaction model parameters";
#endif

  // Switch flags
  fIsTweaked = true;

  //
  // Get initial and current neutrino interacion model params
  //
  TVectorD & initial_values = *fInitialValues;
  TVectorD & current_values = *fCurrentValues;

  //
  // Force the input parameters
  //
  if(force_inputs) 
  {
     // Input vector is NULL.
     // This resets the neutrino interaction params to their best-fit values.
     if(input_vec==0) {
#ifdef __show_tweak_mesg_debug__
        LOG("NuInt",pDEBUG) << "Reset input params to best-fit values.";
#endif
        fIsTweaked = false;
        current_values = initial_values;
        return;
     }
     else     
     {
#ifdef __show_tweak_mesg_debug__
        LOG("NuInt",pDEBUG) << "Forcing input interaction model parameters.";
#endif
        const TVectorD & vec = *input_vec;
        assert(vec.GetNoElements() == conv::kNNDFitParamsNuInt);
        current_values = vec;
     }
  }//force_inputs?

  //
  // If the tweaking dials were not forced, generate correlated tweaking dials
  // using the Cholesky method
  //
  else
  {
#ifdef __show_tweak_mesg_debug__
     LOG("NuInt",pDEBUG) << "Generating random twk dials (correlated)!";
#endif
     const TMatrixD & L = *fCovMtrxChoL;
     TVectorD vec = util::CholeskyGenerateCorrelatedParams(L,initial_values);
     current_values = vec;
  }
  return;

}
//________________________________________________________________________________________
void NuInt::CholeskyDecomposeMatrix(void)
{
#ifdef __show_cholesky_mesg_info__  
    LOG("NuInt",pDEBUG)
      << "Running Cholesky's decomposition method on "
      << "neutrino interaction model param covariance matrix.";
#endif

#ifdef __show_cholesky_mesg_debug__
    LOG("NuInt",pDEBUG) << "Neutrino interaction model param covariance matrix: "; 
    util::PrintCompact(this->CovMatrix(),7,5);  // would be nice to use the same stream and threshold as mesg above
#endif

    TMatrixD L = util::CholeskyDecomposition(this->CovMatrix());
    fCovMtrxChoL = new TMatrixD(L);
#ifdef __show_cholesky_mesg_debug__
    LOG("NuInt",pDEBUG) 
       << "Cholesky decomposition of neutrino interaction model param covariance matrix:";
    util::PrintCompact(*fCovMtrxChoL,7,5);  // would be nice to use the same stream and threshold as mesg above
#endif
}
//________________________________________________________________________________________
double NuInt::ChisqPenalty(bool /*all_syst*/) const
{
  //covariance matrix
  const TMatrixD & cov    (this->CovMatrix()   );
  const TMatrixD & covInv (this->CovMatrixInv());

  //Vector with deviations of current values from  best fit values
  const int np = cov.GetNrows();
  TMatrixD dev  (1,np); //vector of one column in matrix form for multiplication
  TMatrixD devT (np,1); //vector of one row in matrix form for multiplication
  for(int i = 0; i < np; i++){
    dev [0][i] = fCurrentArray[i]-fInitialArray[i];
    devT[i][0] = fCurrentArray[i]-fInitialArray[i];
  }
  
#ifdef __show_chisqpenalty_mesg_debug__
  LOG("NuInt",pDEBUG) << "Deviations in neutrino interaction model parameters: ";
  util::PrintVectorPair(*fCurrentValues,*fInitialValues,7,5); // would be nice to use the same stream and threshold as mesg above
#endif

#ifdef __show_chisqpenalty_mesg_debug2__
  LOG("NuInt",pDEBUG) 
     << "Neutrino interaction model param covariance matrix: ";
  util::PrintMatrix(cov,7,5); // would be nice to use the same stream and threshold as mesg above

  LOG("NuInt",pDEBUG) 
     << "Inverse of neutrino interaction model param covariance matrix: ";
  util::PrintMatrix(covInv,7,5); // would be nice to use the same stream and threshold as mesg above
#endif

  TMatrixD chisqpenalty =  dev * covInv * devT;
  double chisq_penalty = chisqpenalty[0][0]; //The final matrix is 1x1, just a number

#ifdef __show_chisqpenalty_mesg_debug__
  LOG("NuInt",pDEBUG) << "ChisqPenalty = " << chisq_penalty << endl;
#endif

  if(chisq_penalty) return chisq_penalty;

  return 0;
}
//________________________________________________________________________________________ 
void NuInt::PrintSystematicVariations(std::ostream & stream) const
{
  for (int i = 0 ; i < fCurrentValues->GetNoElements(); i++) {
    PhysParamId_t p = fNuIntIndexToPhysParam[i];
    stream << util::AsString(p) << "\t" << (*fCurrentValues)[i] << endl;
  }
}
//________________________________________________________________________________________
int NuInt::Param2Idx(PhysParamId_t p) const
{
  assert(p!=kPhypUndefined);
  return fParam2Idx[p];  
}
//________________________________________________________________________________________
conv::PhysParamId_t NuInt::Idx2Param (int index) const
{
  assert(index >= 0 && index <= conv::kNNDFitParamsNuInt);
  return fNuIntIndexToPhysParam[index];
}
//________________________________________________________________________________________
void NuInt::UpdateFrom(const valor::FitParamList  & fpl)
{
  for (int i = 0 ; i < fInitialValues->GetNoElements() ; i++) {
    PhysParamId_t p = fNuIntIndexToPhysParam[i];
    if (fpl.Exists(p)) {
      fCurrentArray[i] = fpl.CurrValue(p);
    }
    else {
      LOG("NuInt",pWARN) 
        << "Unable to update neutrino interaction model parameter " 
        << util::AsString(p) << " from FPL.";
    }
  }
  fIsTweaked = true;
  return;
}
//________________________________________________________________________________________
void NuInt::CopyTweaksTo(valor::PhysParamList & ppl) const
{
  for (int i = 0 ; i < fCurrentValues->GetNoElements() ; i++) {
    PhysParamId_t p = fNuIntIndexToPhysParam[i];
    ppl.SetValue(p,fCurrentArray[i]);
  }
  return;
}
//________________________________________________________________________________________
void NuInt::CopyTweaksTo(valor::FitParamList & fpl) const
{
  for (int i = 0 ; i < fInitialValues->GetNoElements() ; i++) {
    PhysParamId_t p = fNuIntIndexToPhysParam[i];
    if (fpl.Exists(p)) {
      fpl.SetCurrentValue(p,fCurrentArray[i]);
    }
    else {
      LOG("NuInt",pWARN) 
         << "FPL does not contain parameter " << util::AsString(p);
    }
  }
  return;
}
//________________________________________________________________________________________
void NuInt::CopyOneSigmaErrorsTo(valor::PhysParamList & ppl) const
{
  for (int i = 0 ; i < fCurrentValues->GetNoElements() ; i++) {
    PhysParamId_t p = fNuIntIndexToPhysParam[i];
    ppl.SetValue(p,this->OneSigmaError(p));
  }
  return;
}
//________________________________________________________________________________________
double NuInt::GetWeight(conv::BeamConf_t b, conv::Sample_t s, conv::ReacMode_t m,
                        double true1, double obs1, double obs2) const
{
  static const NDRFL * rfl = NDRFL::Instance();
  double total_weight = 1;
  bool use_spline = true;
  for (int i = 0 ; i < fCurrentValues->GetNoElements() ; i++) {
    PhysParamId_t p = fNuIntIndexToPhysParam[i];
    const double & curr_value = fCurrentArray[i];
    if (use_spline) {
      TSpline * spl = rfl->GetSpline(b,s,m,p,true1,obs1,obs2);
      
      if (spl>0) {
        double par_weight = spl->Eval(curr_value);
        total_weight *= par_weight;
      }
    }
  }
  return total_weight;
}
//________________________________________________________________________________________
