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
#include "SDFit/NDFitParams.h"
#include "SDFit/NuDet.h"

using std::cout;
using std::cerr;
using std::endl;
using std::setw;
using std::setprecision;

using namespace valor;
using namespace valor::conv;
using namespace valor::util;

ClassImp(NuDet)

//________________________________________________________________________________________
NuDet::NuDet() :
TObject()
{
  this->Init();
}
//________________________________________________________________________________________
NuDet::~NuDet()
{
  this->CleanUp();
}
//________________________________________________________________________________________
void NuDet::Init(void)
{
  fInitialValues        = new TVectorD(conv::kNNDFitParamsNuDet);
  fCurrentValues        = new TVectorD(conv::kNNDFitParamsNuDet);
  
  fCovMtrx              = 0;
  fCovMtrxInv           = 0;
  fCovMtrxChoL          = 0; 
  
  fIsTweaked            = false;
  
  fInitialArray = fInitialValues->GetMatrixArray();
  fCurrentArray = fCurrentValues->GetMatrixArray();
  
  for (int ip = 0 ; ip < conv::knppmax; ip++) {
    fParam2Idx[ip] = -1;
  }
  
  int i_params_det = 0;
  for(int i = 0; i < conv::kNNDFitParams; i++) {
    PhysParamId_t p = conv::kNDFitParam[i];
    if (conv::kNDFitIsNuDetRelated[i]) {
      fNuDetIndexToPhysParam[i_params_det] = p;
      fParam2Idx[p] = i_params_det;
      i_params_det++;
    }
  }
  
  for(int i = 0 ; i < fCurrentValues->GetNrows(); i++ ) {
    fInitialArray[i] = 1.;
    fCurrentArray[i] = 1.;
  }
  
  // Check we have the right number of parameters labelled as related to this class
  if (conv::kNNDFitParamsNuDet-i_params_det) {
    LOG("NuDet",pERROR)<<"kNNDFitParamsNuDet does not match kNDFitIsNuDetRelated";
    util::Die(-1); return;
  }
}
//________________________________________________________________________________________
void NuDet::CleanUp(void)
{
  if ( fInitialValues ) delete fInitialValues;
  if ( fCurrentValues ) delete fCurrentValues;
  
  if ( fCovMtrx       ) delete fCovMtrx;
  if ( fCovMtrxInv    ) delete fCovMtrxInv;
  if ( fCovMtrxChoL   ) delete fCovMtrxChoL;  
  
}
//________________________________________________________________________________________
bool NuDet::Read(TXMLEngine* xml, XMLNodePointer_t root_node)
{
  this->CleanUp();
  this->Init();
  
  // Get neutrino detector model param covariance matrix
  fCovMtrx = util::XML2TMatrixD(xml,root_node,"syst/detector/covariance_matrix");  
  if(!fCovMtrx) {
    LOG("NuDet",pFATAL) 
       << "No neutrino detector model param covariance matrix was found.";
    util::Die(1); return false;
  }
  
  // Check matrix size
  TMatrixD & cov = *fCovMtrx;
  const int np = conv::kNNDFitParamsNuDet;  
  if(cov.GetNrows() != np || cov.GetNcols() != np) 
  {
     LOG("NuDet",pFATAL)
        << "\n Neutrino detector model param covariance matrix has unexpected size!"
        << "\n Expecting: " <<  np << " x " << np << " matrix"
        << "\n Found: " << cov.GetNrows() << " x " <<  cov.GetNcols() << " matrix";
     util::Die(1); return false;
  }
  
  // Do Cholesky decomposition
  LOG("NuDet",pNOTICE) 
    << "Running  Cholesky decomposition of detector model param covariance matrix ";
  this->CholeskyDecomposeMatrix();
  double det;
  
  // Calculate matrix inversion using Cholesky triangular matrices - should be most accurate.
  TMatrixD cholInv(*fCovMtrxChoL);
  cholInv.Invert(&det);
  LOG("NuDet",pNOTICE) 
     << "Detector param covariance matrix decomposition determinant: " << det;
  TMatrixD cholInvT(TMatrixD::kTransposed,cholInv);
  fCovMtrxInv = new TMatrixD(cholInvT * cholInv);
  
#ifdef __init_check_inverse__
  bool failure = false;
  TMatrixD covTimesInverse = (cov * (*fCovMtrxInv));
  for (int ii = 0 ; ii < np ; ii++) {
    for (int jj = 0 ; jj < np ; jj++) {
      int target = (ii==jj);
      if (fabs(covTimesInverse[ii][jj]-target) > 1E-9) {
        LOG("NuDet",pERROR) 
          << "Bad inversion of neutrino detector model param covariance matrix"
          << " - element: " << ii << " , " << jj << ": " 
          << covTimesInverse[ii][jj]-target << (ii==jj?"*":"");
        failure = true;
      }
    }
  }
  if (failure) {util::Die(1); return false;}
#endif // __init_check_inverse__
  
#ifdef __show_init_mesg_debug__
  LOG("NuDet",pDEBUG) 
     << "Input neutrino detector model param covariance matrix: "; 
  util::PrintMatrix(cov,7,5); // would be nice to use the same stream and threshold as mesg above
  LOG("NuDet",pDEBUG) 
     << "Inverse neutrino detector model param covariance matrix: ";
  util::PrintMatrix(*fCovMtrxInv,7,5); // would be nice to use the same stream and threshold as mesg above
#endif
  
  return true;
}
//________________________________________________________________________________________
double NuDet::CurrentValue(PhysParamId_t p) const
{
  int idx = this->Param2Idx(p); 
  return fCurrentArray[idx];
}
//________________________________________________________________________________________
double NuDet::CurrentValueByIndex(int idx) const
{
  return fCurrentArray[idx];
}
//________________________________________________________________________________________
double NuDet::OneSigmaError(PhysParamId_t p) const
{
  const TMatrixD & cov = *fCovMtrx;
  int idx = this->Param2Idx(p); 
  return TMath::Sqrt(cov[idx][idx]);
}
//________________________________________________________________________________________
double NuDet::OneSigmaErrorByIndex(int idx) const
{
  const TMatrixD & cov = *fCovMtrx;
  return TMath::Sqrt(cov[idx][idx]);
}
//________________________________________________________________________________________
void NuDet::Tweak(
  bool       force_inputs, // force the input params or generate random ones internally  
  TVectorD * input_vec     // input vector of detector model params - Set to 0 to reset to nominal ones 
)
{
#ifdef __show_tweak_mesg_debug__
  LOG("NuDet",pDEBUG)  << "Tweaking neutrino detector model parameters";
#endif

  // Switch flags
  fIsTweaked = true;

  //
  // Get initial and current neutrino detector model params
  //
  TVectorD & initial_values = *fInitialValues;
  TVectorD & current_values = *fCurrentValues;

  //
  // Force the input parameters
  //
  if(force_inputs) 
  {
     // Input vector is NULL.
     // This resets the neutrino detector params to their best-fit values.
     if(input_vec==0) {
#ifdef __show_tweak_mesg_debug__
        LOG("NuDet",pDEBUG) << "Reset input params to best-fit values.";
#endif
        fIsTweaked = false;
        current_values = initial_values;
        return;
     }
     else     
     {
#ifdef __show_tweak_mesg_debug__
        LOG("NuDet",pDEBUG) << "Forcing input detector model parameters.";
#endif
        const TVectorD & vec = *input_vec;
        assert(vec.GetNoElements() == conv::kNNDFitParamsNuDet);
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
     LOG("NuDet",pDEBUG) << "Generating random twk dials (correlated)!";
#endif
     const TMatrixD & L = *fCovMtrxChoL;
     TVectorD vec = util::CholeskyGenerateCorrelatedParams(L,initial_values);
     current_values = vec;
  }
  return;
}
//________________________________________________________________________________________
void NuDet::CholeskyDecomposeMatrix(void)
{
#ifdef __show_cholesky_mesg_info__  
    LOG("NuDet",pDEBUG)
      << "Running Cholesky's decomposition method on "
      << "neutrino detector model param covariance matrix.";
#endif

#ifdef __show_cholesky_mesg_debug__
    LOG("NuDet",pDEBUG) << "Neutrino detector model param covariance matrix: "; 
    util::PrintCompact(this->CovMatrix(),7,5);  // would be nice to use the same stream and threshold as mesg above
#endif

    TMatrixD L = util::CholeskyDecomposition(this->CovMatrix());
    fCovMtrxChoL = new TMatrixD(L);
#ifdef __show_cholesky_mesg_debug__
    LOG("NuDet",pDEBUG) 
       << "Cholesky decomposition of neutrino detector model param covariance matrix:";
    util::PrintCompact(*fCovMtrxChoL,7,5);  // would be nice to use the same stream and threshold as mesg above
#endif
}
//________________________________________________________________________________________
double NuDet::ChisqPenalty(bool /*all_syst*/) const
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
  LOG("NuDet",pDEBUG) << "Deviations in neutrino detector model parameters: ";
  util::PrintVectorPair(*fCurrentValues,*fInitialValues,7,5); // would be nice to use the same stream and threshold as mesg above
#endif

#ifdef __show_chisqpenalty_mesg_debug2__
  LOG("NuDet",pDEBUG) 
     << "Neutrino detector model param covariance matrix: ";
  util::PrintMatrix(cov,7,5); // would be nice to use the same stream and threshold as mesg above

  LOG("NuDet",pDEBUG) 
     << "Inverse of neutrino detector model param covariance matrix: ";
  util::PrintMatrix(covInv,7,5); // would be nice to use the same stream and threshold as mesg above
#endif

  TMatrixD chisqpenalty =  dev * covInv * devT;
  double chisq_penalty = chisqpenalty[0][0]; //The final matrix is 1x1, just a number

#ifdef __show_chisqpenalty_mesg_debug__
  LOG("NuDet",pDEBUG) << "ChisqPenalty = " << chisq_penalty << endl;
#endif

  return chisq_penalty;
}
//________________________________________________________________________________________ 
void NuDet::PrintSystematicVariations(std::ostream & stream) const
{
  for (int i = 0 ; i < fCurrentValues->GetNoElements(); i++) {
    PhysParamId_t p = fNuDetIndexToPhysParam[i];
    stream << util::AsString(p) << "\t" << (*fCurrentValues)[i] << endl;
  }
}
//________________________________________________________________________________________
int NuDet::Param2Idx(PhysParamId_t p) const
{
  assert(p!=kPhypUndefined);
  return fParam2Idx[p];  
}
//________________________________________________________________________________________
conv::PhysParamId_t NuDet::Idx2Param (int index) const
{
  assert(index >= 0 && index <= conv::kNNDFitParamsNuDet);
  return fNuDetIndexToPhysParam[index];
}
//________________________________________________________________________________________
void NuDet::UpdateFrom(const valor::FitParamList  & fpl)
{
  for (int i = 0 ; i < fInitialValues->GetNoElements() ; i++) {
    PhysParamId_t p = fNuDetIndexToPhysParam[i];
    if (fpl.Exists(p)) {
      fCurrentArray[i] = fpl.CurrValue(p);
    }
    else {
      LOG("NuDet",pWARN) 
        << "Unable to update neutrino interaction model parameter " 
        << util::AsString(p) << " from FPL.";
    }
  }
  fIsTweaked = true;
  return;
}
//________________________________________________________________________________________
void NuDet::CopyTweaksTo(valor::PhysParamList & ppl) const
{
  for (int i = 0 ; i < fCurrentValues->GetNoElements() ; i++) {
    PhysParamId_t p = fNuDetIndexToPhysParam[i];
    ppl.SetValue(p,fCurrentArray[i]);
  }
  return;
}
//________________________________________________________________________________________
void NuDet::CopyTweaksTo(valor::FitParamList & fpl) const
{
  for (int i = 0 ; i < fInitialValues->GetNoElements() ; i++) {
    PhysParamId_t p = fNuDetIndexToPhysParam[i];
    if (fpl.Exists(p)) {
      fpl.SetCurrentValue(p,fCurrentArray[i]);
    }
    else {
      LOG("NuDet",pWARN) 
         << "FPL does not contain parameter " << util::AsString(p);
    }
  }
  return;
}
//________________________________________________________________________________________
void NuDet::CopyOneSigmaErrorsTo(valor::PhysParamList & ppl) const
{
  for (int i = 0 ; i < fCurrentValues->GetNoElements() ; i++) {
    PhysParamId_t p = fNuDetIndexToPhysParam[i];
    ppl.SetValue(p,this->OneSigmaError(p));
  }
  return;
}
//________________________________________________________________________________________
