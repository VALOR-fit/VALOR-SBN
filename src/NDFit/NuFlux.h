//____________________________________________________________________________
/*!

\class     valor::NuFlux

\brief     Info on DUNE neutrino flux and prior errors

\author    Steve Dennis <>
           University of Liverpool

	   Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_nu_flux_h_
#define _valor_dune_nu_flux_h_

#include <iostream>

#include <TObject.h>
#include <TMatrixD.h>
#include <TVectorD.h>
#include <TMatrixTSym.h>
#include <TXMLEngine.h>

class TH1D;
class TH2D;

namespace valor {

class FitParamList;
class PhysParamList;

class NuFlux: public TObject
{
public:
  NuFlux();   
 ~NuFlux();
 
  using TObject::Read; // Suppress clang warnings
  using TObject::Draw; // Suppress clang warnings

  // Read inputs from XML file
  bool Read (TXMLEngine* xml, XMLNodePointer_t root_node);

  // Get flux covariance matrix and cholesky decomposition of covariance matrix
  const TMatrixD & CovMatrix         (void) const { return *fCovMtrx;          }
  const TMatrixD & CovMatrixInv      (void) const { return *fCovMtrxInv;       }
  const TMatrixD & CovMatrixCholesky (void) const { return *fCovMtrxChoL;      }

  double OneSigmaError(conv::PhysParamId_t p) const;
  double OneSigmaErrorByIndex(int idx) const;

  // Penalty term included in the chisq 
  double ChisqPenalty (bool all_syst = true) const;

  void Tweak(bool force_inputs, TVectorD * input_vec);

  double CurrentValueByIndex(int idx) const;
  double CurrentValue(conv::PhysParamId_t p) const;

  // Get & tweak flags
  bool IsTweaked (void) const { return fIsTweaked; } 

  // Print
  void PrintSystematicVariations (std::ostream & stream = std::cout) const;
  
  void UpdateFrom(const valor::FitParamList  & fpl);
  //~ void UpdateFrom(const valor::PhysParamList & ppl);
  
  void CopyTweaksTo(valor::PhysParamList & ppl) const;
  void CopyTweaksTo(valor::FitParamList & fpl) const;
  void CopyOneSigmaErrorsTo(valor::PhysParamList & ppl) const;
    
private:

  void Init      (void);
  void CleanUp   (void);

  int  Param2Idx (conv::PhysParamId_t p) const;     ///< convert flux PhysParamId_t to a covariance matrix or vector index
  conv::PhysParamId_t  Idx2Param (int index) const; ///< convert flux a covariance matrix or vector index to PhysParamId_t
  
  void CholeskyDecomposeMatrix (void);          ///< Cholesky decompose the covariance matrix
  
  TVectorD *  fInitialValues;     ///< Initial values of flux parameters 
  TVectorD *  fCurrentValues;     ///< Current values of flux parameters 
  TMatrixD *  fCovMtrx;           ///< flux covariance matrix
  TMatrixD *  fCovMtrxInv;        ///< Inverse flux covariance matrix
  TMatrixD *  fCovMtrxChoL;       ///< Triangular matrix obtained from Cholesky decomposition of flux covariance matrix
  bool        fIsTweaked;         ///< Were flux params tweaked?

  double * fInitialArray; //! ///< Pointer to the actual memory location of the initial values
  double * fCurrentArray; //! ///< Pointer to the actual memory location of the current values
  
  int fParam2Idx[conv::knppmax];
  
  conv::PhysParamId_t fFluxIndexToPhysParam[conv::kNNDFitParamsNuFlux];

ClassDef(NuFlux, 1)
};

} //valor

#endif
