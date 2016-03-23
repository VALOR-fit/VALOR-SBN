//____________________________________________________________________________
/*!

\class     valor::NuDet

\brief     Info on neutrino detector model systematics

\author    Steve Dennis <>
           University of Liverpool

           Lorena Escudero <>
           University of Cambridge

           Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_nu_det_h_
#define _valor_dune_nu_det_h_

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

class NuDet: public TObject
{
public:
  NuDet();   
 ~NuDet();
 
  using TObject::Read; // Suppress clang warnings
  using TObject::Draw; // Suppress clang warnings

  // Read inputs from XML file
  bool Read (TXMLEngine* xml, XMLNodePointer_t root_node);
  
  // Get detector model param covariance matrix and cholesky decomposition of covariance matrix
  const TMatrixD & CovMatrix         (void) const { return *fCovMtrx;          }
  const TMatrixD & CovMatrixInv      (void) const { return *fCovMtrxInv;       }
  const TMatrixD & CovMatrixCholesky (void) const { return *fCovMtrxChoL;      }
  
  // 
  double OneSigmaError (conv::PhysParamId_t p) const;
  double OneSigmaErrorByIndex (int idx) const;

  // Penalty term included in the chisq 
  double ChisqPenalty (bool all_syst = true) const;

  //
  void Tweak(bool force_inputs, TVectorD * input_vec);

  //
  double CurrentValueByIndex (int idx) const;
  double CurrentValue        (conv::PhysParamId_t p) const;

  // Get & tweak flags
  bool IsTweaked (void) const { return fIsTweaked; } 

  // Print
  void PrintSystematicVariations (std::ostream & stream = std::cout) const;
  
  //
  void UpdateFrom(const valor::FitParamList & fpl);
  
  //
  void CopyTweaksTo(valor::PhysParamList & ppl) const;
  void CopyTweaksTo(valor::FitParamList & fpl) const;
  void CopyOneSigmaErrorsTo(valor::PhysParamList & ppl) const;
    
private:

  void Init      (void);
  void CleanUp   (void);

  // convert detector model PhysParamId_t to a vector index
  int Param2Idx (conv::PhysParamId_t p) const;    

  // convert a detector model param covariance matrix or vector index to PhysParamId_t
  conv::PhysParamId_t Idx2Param (int index) const; 

  void CholeskyDecomposeMatrix (void);          ///< Cholesky decompose the covariance matrix
  
  TVectorD *  fInitialValues;     ///< Initial values of detector model parameters 
  TVectorD *  fCurrentValues;     ///< Current values of detector model parameters 
  
  TMatrixD *  fCovMtrx;           ///< Detector model parameter covariance matrix
  TMatrixD *  fCovMtrxInv;        ///< Inverse detector model parameter covariance matrix
  TMatrixD *  fCovMtrxChoL;       ///< Triangular matrix obtained from Cholesky decomposition of detector model parameter covariance matrix
  
  bool        fIsTweaked;         ///< Were flux params tweaked?

  double * fInitialArray; //! ///< Pointer to the actual memory location of the initial values
  double * fCurrentArray; //! ///< Pointer to the actual memory location of the current values
  
  int fParam2Idx[conv::knppmax];
  
  conv::PhysParamId_t fNuDetIndexToPhysParam[conv::kNNDFitParamsNuDet];

ClassDef(NuDet, 1)
};

} //valor

#endif
