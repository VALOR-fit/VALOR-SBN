//________________________________________________________________________________________
/*

Copyright (c) 2010-2015, The VALOR Fitting Group, All Rights Reserved.

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
#include "Messenger/Messenger.h"
#include "FitCore/FitParamList.h"
#include "FitCore/PhysParamList.h"
// dune
#include "NDFit/NDFitParams.h"
#include "NDFit/NuFlux.h"

using std::cout;
using std::cerr;
using std::endl;
using std::setw;
using std::setprecision;

using namespace valor;
using namespace valor::conv;
using namespace valor::util;

ClassImp(NuFlux)

//________________________________________________________________________________________
NuFlux::NuFlux() :
TObject()
{
  this->Init();
}
//________________________________________________________________________________________
NuFlux::~NuFlux()
{
  this->CleanUp();
}
//________________________________________________________________________________________
void NuFlux::Init(void)
{
  fInitialValues        = new TVectorD(conv::kNNDFitParamsNuFlx);
  fCurrentValues        = new TVectorD(conv::kNNDFitParamsNuFlx);
  fCovMtrx              = 0;
  fCovMtrxInv           = 0;
  fCovMtrxChoL          = 0; 
  fIsTweaked            = false;
  
  fInitialArray = fInitialValues->GetMatrixArray();
  fCurrentArray = fCurrentValues->GetMatrixArray();
  
  for(int i = 0 ; i < fCurrentValues->GetNrows(); i++ ) {
    fInitialArray[i] = 1.;
    fCurrentArray[i] = 1.;
    
    fFluxIndexToPhysParam[i] = (PhysParamId_t)(kNuisFHCNuMuFlux00+i);
  }
  
}
//________________________________________________________________________________________
void NuFlux::CleanUp(void)
{
  if ( fInitialValues ) delete fInitialValues;
  if ( fCurrentValues ) delete fCurrentValues;
  if ( fCovMtrx       ) delete fCovMtrx;
  if ( fCovMtrxInv    ) delete fCovMtrxInv;
  if ( fCovMtrxChoL   ) delete fCovMtrxChoL;  
}
//________________________________________________________________________________________
bool NuFlux::Read(TXMLEngine* xml, XMLNodePointer_t root_node)
{
  this->CleanUp();
  this->Init();

  // Get flux covariance matrix
  fCovMtrx = util::XML2TMatrixD(xml,root_node,"syst/flux/covariance_matrix");  
  if(!fCovMtrx) {
    LOG("NuFlux",pFATAL) << "No flux covariance matrix was found.";
    util::Die(1);
  }
  
  // Check matrix size
  TMatrixD & cov = *fCovMtrx;
  const int np = conv::kNNDFitParamsNuFlx;  
  if(cov.GetNrows() != np || cov.GetNcols() != np) 
  {
     LOG("NuFlux",pFATAL)
        << "\n Flux covariance matrix has unexpected size!"
        << "\n Expecting: " <<  np << " x " << np << " matrix"
        << "\n Found: " << cov.GetNrows() << " x " <<  cov.GetNcols() << " matrix";
     util::Die(1);
  }
  
  // Do Cholesky decomposition
  LOG("NuFlux",pNOTICE) << "Running  Cholesky decomposition of flux covariance matrix ";
  this->CholeskyDecomposeMatrix();
  double det;
  
  // Calculate matrix inversion using Cholesky triangular matrices - should be most accurate.
  TMatrixD cholInv(*fCovMtrxChoL);
  cholInv.Invert(&det);
  LOG("NuFlux",pNOTICE) << "Flux covariance matrix decomposition determinant: " << det;
  TMatrixD cholInvT(TMatrixD::kTransposed,cholInv);
  fCovMtrxInv = new TMatrixD(cholInvT * cholInv);
  
  //~ // Calculate matrix inversion directly
  //~ fCovMtrxInv = new TMatrixD(cov);
  //~ fCovMtrxInv->Invert(&det);
  //~ std::cout<<"NuFlux/Read >> Flux covariance matrix decomposition: "<<det<<endl;
  
  //~ // Use scalar value decomposition for matrix inverse
  //~ fCovMtrxInv = new TMatrixD(util::MatrixPseudoInverted(cov));

#ifdef __init_check_inverse__
  bool failure = false;
  TMatrixD covTimesInverse = (cov * (*fCovMtrxInv));
  for (int ii = 0 ; ii < np ; ii++) {
    for (int jj = 0 ; jj < np ; jj++) {
      int target = (ii==jj);
      if (fabs(covTimesInverse[ii][jj]-target) > 1E-9) {
        LOG("NuFlux",pERROR) 
          << "Bad inversion of flux matrix - element: "
          << ii << " , " << jj <<": " << covTimesInverse[ii][jj]-target << (ii==jj?"*":"");
        failure = true;
      }
    }
  }
  if (failure) {exit(-1);}
#endif // __init_check_inverse__
  
#ifdef __show_init_mesg_debug__
  LOG("NuFlux",pDEBUG) << "Input flux covariance matrix: "; 
  util::PrintMatrix(cov,7,5); // would be nice to use the same stream and threshold as mesg above
  LOG("NuFlux",pDEBUG) << "Inverse flux covariance matrix: ";
  util::PrintMatrix(*fCovMtrxInv,7,5); // would be nice to use the same stream and threshold as mesg above
#endif
  
  return true;
}
//________________________________________________________________________________________
double NuFlux::CurrentValue(PhysParamId_t p) const
{
  int idx = this->Param2Idx(p); 
  return fCurrentArray[idx];
}
//________________________________________________________________________________________
double NuFlux::CurrentValueByIndex(int idx) const
{
  return fCurrentArray[idx];
}
//________________________________________________________________________________________
double NuFlux::OneSigmaError(PhysParamId_t p) const
{
  const TMatrixD & cov = *fCovMtrx;
  int idx = this->Param2Idx(p); 
  //int idx = this->Param2Idx(p);
  return TMath::Sqrt(cov[idx][idx]);
}
//________________________________________________________________________________________
double NuFlux::OneSigmaError(int idx) const
{
  const TMatrixD & cov = *fCovMtrx;
  return TMath::Sqrt(cov[idx][idx]);
}
//________________________________________________________________________________________
void NuFlux::Tweak(
  bool       force_inputs, // force the input params or generate random ones internally  
  TVectorD * input_vec     // input vector of flux params - Set to 0 to reset to nominal ones 
)
{
  
#ifdef __show_tweak_mesg_debug__
  LOG("NuFlux",pDEBUG)  << "Tweaking flux parameters";
#endif

  // Switch flags
  fIsTweaked         = true;
  //~ fIsFluxWghtUpdated = false;

  //
  // Get best-fit and current flux params
  //

  TVectorD & initial_values = *fInitialValues;
  TVectorD & current_values = *fCurrentValues;

  //
  // Force the input parameters
  //
  if(force_inputs) 
  {
     // Input vector is NULL.
     // This resets the input params to their best-fit values.
     if(input_vec==0) {
#ifdef __show_tweak_mesg_debug__
        LOG("NuFlux",pDEBUG) << "Reset input params to best-fit values.";
#endif
        fIsTweaked = false;
        current_values = initial_values;
        return;
     }
     else     
     {
#ifdef __show_tweak_mesg_debug__
        LOG("NuFlux",pDEBUG) << "Forcing input flux parameters. ";
#endif
        const TVectorD & vec = *input_vec;
        assert(vec.GetNoElements() == conv::kNNDFitParamsNuFlx);
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
     LOG("NuFlux",pDEBUG) << "Generating random twk dials (correlated)! ";
#endif
     const TMatrixD & L = *fCovMtrxChoL;
     TVectorD vec = util::CholeskyGenerateCorrelatedParams(L,initial_values);
     current_values = vec;
  }
  return;
}
//________________________________________________________________________________________
void NuFlux::CholeskyDecomposeMatrix(void)
{
#ifdef __show_cholesky_mesg_info__  
    LOG("NuFlux",pDEBUG) 
      << "Running Cholesky's decomposition method on the flux covariance matrix.";
#endif

#ifdef __show_cholesky_mesg_debug__
    LOG("NuFlux",pDEBUG) 
       << "Flux covariance matrix: "; 
    util::PrintCompact(this->CovMatrix(),7,5); // would be nice to use the same stream and threshold as mesg above
#endif

    TMatrixD L = util::CholeskyDecomposition(this->CovMatrix());
    fCovMtrxChoL = new TMatrixD(L);
#ifdef __show_cholesky_mesg_debug__
    LOG("NuFlux",pDEBUG) 
       << "Cholesky decomposition of flux covariance matrix: ";
    util::PrintCompact(*fCovMtrxChoL,7,5); // would be nice to use the same stream and threshold as mesg above
#endif
}
//________________________________________________________________________________________
double NuFlux::ChisqPenalty(bool /*all_syst*/) const
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
  LOG("NuFlux",pDEBUG) << "Deviations in flux parameters: ";
  util::PrintVectorPair(*fCurrentValues,*fInitialValues,7,5); // would be nice to use the same stream and threshold as mesg above
#endif

#ifdef __show_chisqpenalty_mesg_debug2__
    LOG("NuFlux",pDEBUG) << "Flux covariance matrix: ";
    util::PrintMatrix(cov,7,5); // would be nice to use the same stream and threshold as mesg above
    LOG("NuFlux",pDEBUG) << "Inverse flux covariance matrix: ";
    util::PrintMatrix(covInv,7,5); // would be nice to use the same stream and threshold as mesg above
#endif

    TMatrixD chisqpenalty =  dev * covInv * devT;
    double chisq_penalty = chisqpenalty[0][0]; //The final matrix is 1x1, just a number

#ifdef __show_chisqpenalty_mesg_debug__
    LOG("NuFlux",pDEBUG) << "ChisqPenalty = " << chisq_penalty;
#endif

    if(chisq_penalty) return chisq_penalty;
    //}//all_syst
  return 0;
}
//________________________________________________________________________________________ 
void NuFlux::PrintSystematicVariations(std::ostream & stream) const
{
  //assert(fCurrentValues->GetNoElements() == conv::kNumOfParamsInBANFFfit);
  //~ const TVectorD & current_values = *fCurrentValues;
  //~ const TVectorD & bestfit_values = *fBestFitValues;
  //~ stream << "Exp/BANFF >> BANFF parameters: " << endl; 
  //~ util::PrintCompact(current_values);
  
  for (int i = 0 ; i < fCurrentValues->GetNoElements(); i++) {
    PhysParamId_t p = fFluxIndexToPhysParam[i];
    stream << util::AsString(p) << "\t" << (*fCurrentValues)[i] << endl;
  }
}
//________________________________________________________________________________________
int NuFlux::Param2Idx(PhysParamId_t p) const
{
  assert(p!=kPhypUndefined);
  return fParam2Idx[p];  
}
//________________________________________________________________________________________
conv::PhysParamId_t NuFlux::Idx2Param (int index) const
{
  assert(index >= 0 && index <= conv::kNNDFitParamsNuFlx);
  return fFluxIndexToPhysParam[index];
}
//________________________________________________________________________________________
void NuFlux::UpdateFrom(const valor::FitParamList  & fpl)
{
  for (int i = 0 ; i < fInitialValues->GetNoElements() ; i++) {
    PhysParamId_t p = fFluxIndexToPhysParam[i];
    if (fpl.Exists(p)) {
      fCurrentArray[i] = fpl.CurrValue(p);
    }
    else {
      LOG("NuFlux",pWARN) 
        << "Unable to update flux parameter " << util::AsString(p) << " from FPL.";
    }
  }
  fIsTweaked = true;
  return;
}
//________________________________________________________________________________________
void NuFlux::CopyTweaksTo(valor::PhysParamList & ppl) const
{
  for (int i = 0 ; i < fCurrentValues->GetNoElements() ; i++) {
    PhysParamId_t p = fFluxIndexToPhysParam[i];
    ppl.SetValue(p,fCurrentArray[i]);
  }
  return;
}
//________________________________________________________________________________________
void NuFlux::CopyTweaksTo(valor::FitParamList & fpl) const
{
  for (int i = 0 ; i < fInitialValues->GetNoElements() ; i++) {
    PhysParamId_t p = fFluxIndexToPhysParam[i];
    if (fpl.Exists(p)) {
      fpl.SetCurrentValue(p,fCurrentArray[i]);
    }
    else {
      LOG("NuFlux",pWARN) 
        << "FPL does not contain parameter " << util::AsString(p);
    }
  }
  return;
}
//________________________________________________________________________________________
