//____________________________________________________________________________
/*!

\file      FitParamApply.h

\brief     Controls which parameters get applied to which beam/sample/mode bins.

\author    Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

\created   March 20, 2016

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_apply_params_h_
#define _valor_dune_apply_params_h_

// FMWK
#include "valor/Conventions/NuFlavour.h"

// Dune
#include "dune/Conventions/BeamConf.h"
#include "dune/Conventions/DuneBuild.h"
#include "dune/Conventions/ReacMode.h"
#include "dune/Conventions/FitParam.h"

namespace valor {
namespace conv {
// A bitmask to control which parameters are applied to which modes
// If we move to C++11, we should use an enum class here instead
// But in older versions we can't use an enum and be guaranteed we have the 64 bits we need.
typedef ULong64_t ApplyMask_t;

static const ApplyMask_t kApplyMaskOne = 1ul;

static const ApplyMask_t kApplyUndefined          = (kApplyMaskOne <<  0 );
static const ApplyMask_t kbApplyToFHC             = (kApplyMaskOne <<  1 ); // Current
static const ApplyMask_t kbApplyToRHC             = (kApplyMaskOne <<  2 );
static const ApplyMask_t kfApplyToNuMu            = (kApplyMaskOne <<  3 ); // True flavour
static const ApplyMask_t kfApplyToNuMuBar         = (kApplyMaskOne <<  4 );
static const ApplyMask_t kfApplyToNuE             = (kApplyMaskOne <<  5 );
static const ApplyMask_t kfApplyToNuEBar          = (kApplyMaskOne <<  6 );
static const ApplyMask_t ksApplyToNuMuCC          = (kApplyMaskOne <<  7 ); 
static const ApplyMask_t ksApplyToNuMuCC1trkQE    = (kApplyMaskOne <<  8 ); // Sample
static const ApplyMask_t ksApplyToNuMuCC2trkQE    = (kApplyMaskOne <<  9 );
static const ApplyMask_t ksApplyToNuMuCC1piC      = (kApplyMaskOne << 10 );
static const ApplyMask_t ksApplyToNuMuCC2piC      = (kApplyMaskOne << 11 );
static const ApplyMask_t ksApplyToNuMuCC1pi0      = (kApplyMaskOne << 12 );
static const ApplyMask_t ksApplyToNuMuCC1piC1pi0  = (kApplyMaskOne << 13 );
static const ApplyMask_t ksApplyToNuMuCCoth       = (kApplyMaskOne << 14 );
static const ApplyMask_t ksApplyToNuECC           = (kApplyMaskOne << 15 );
static const ApplyMask_t ksApplyToNuMuCCWSgn      = (kApplyMaskOne << 16 );
static const ApplyMask_t ksApplyToNC              = (kApplyMaskOne << 17 );
static const ApplyMask_t ksApplyToNC1piC          = (kApplyMaskOne << 18 );
static const ApplyMask_t ksApplyToNC1pi0          = (kApplyMaskOne << 19 );
static const ApplyMask_t ksApplyToNCoth           = (kApplyMaskOne << 20 ); 
static const ApplyMask_t ktApplyToCCQE            = (kApplyMaskOne << 21 ); // Reaction type
static const ApplyMask_t ktApplyToCCMEC           = (kApplyMaskOne << 22 );
static const ApplyMask_t ktApplyToCC1piC          = (kApplyMaskOne << 23 );
static const ApplyMask_t ktApplyToCC1pi0          = (kApplyMaskOne << 24 );
static const ApplyMask_t ktApplyToCC2piC          = (kApplyMaskOne << 25 );
static const ApplyMask_t ktApplyToCC2pi0          = (kApplyMaskOne << 26 );
static const ApplyMask_t ktApplyToCCpiCpi0        = (kApplyMaskOne << 27 );
static const ApplyMask_t ktApplyToCCcoh           = (kApplyMaskOne << 28 );
static const ApplyMask_t ktApplyToCCoth           = (kApplyMaskOne << 29 );
static const ApplyMask_t ktApplyToNCEL            = (kApplyMaskOne << 30 );
static const ApplyMask_t ktApplyToNCMEC           = (kApplyMaskOne << 31 );
static const ApplyMask_t ktApplyToNC1piC          = (kApplyMaskOne << 32 );
static const ApplyMask_t ktApplyToNC1pi0          = (kApplyMaskOne << 33 );
static const ApplyMask_t ktApplyToNC2piC          = (kApplyMaskOne << 34 );
static const ApplyMask_t ktApplyToNC2pi0          = (kApplyMaskOne << 35 );
static const ApplyMask_t ktApplyToNCpiCpi0        = (kApplyMaskOne << 36 );
static const ApplyMask_t ktApplyToNCcoh           = (kApplyMaskOne << 37 );
static const ApplyMask_t ktApplyToNCoth           = (kApplyMaskOne << 38 );

// Groups of systematics
// Beam
static const ApplyMask_t kbApplyToAll = kbApplyToFHC | kbApplyToRHC;

// Nu flavour
static const ApplyMask_t kfApplyToNuAny    = kfApplyToNuMu    | kfApplyToNuE   ; // NuAny means any non-barred
static const ApplyMask_t kfApplyToNuBarAny = kfApplyToNuMuBar | kfApplyToNuEBar;
static const ApplyMask_t kfApplyToNuEAny   = kfApplyToNuE     | kfApplyToNuEBar;
static const ApplyMask_t kfApplyToNuMuAny  = kfApplyToNuMu    | kfApplyToNuMuBar;
static const ApplyMask_t kfApplyToAll      = kfApplyToNuAny   | kfApplyToNuBarAny;

// Reaction type
static const ApplyMask_t ktApplyToCCQELike = ktApplyToCCQE   | ktApplyToCCMEC;
static const ApplyMask_t ktApplyToAllCC1pi = ktApplyToCC1piC | ktApplyToCC1pi0;
static const ApplyMask_t ktApplyToAllCC2pi = ktApplyToCC2piC | ktApplyToCC2pi0 | ktApplyToCCpiCpi0;
static const ApplyMask_t ktApplyToAllCC    = ktApplyToCCQELike | ktApplyToAllCC1pi | ktApplyToAllCC2pi | ktApplyToCCcoh | ktApplyToCCoth;

static const ApplyMask_t ktApplyToNCElLike = ktApplyToNCEL   | ktApplyToNCMEC;
static const ApplyMask_t ktApplyToAllNC1pi = ktApplyToNC1piC | ktApplyToNC1pi0;
static const ApplyMask_t ktApplyToAllNC2pi = ktApplyToNC2piC | ktApplyToNC2pi0 | ktApplyToNCpiCpi0;
static const ApplyMask_t ktApplyToAllNC    = ktApplyToNCElLike | ktApplyToAllNC1pi | ktApplyToAllNC2pi | ktApplyToNCcoh | ktApplyToNCoth;

static const ApplyMask_t ktApplyToAllCoh = ktApplyToCCcoh | ktApplyToNCcoh;

static const ApplyMask_t ktApplyToAll = ktApplyToAllCC | ktApplyToAllNC;
static const ApplyMask_t ktApplyToAllButCoh = ktApplyToAll | (~ktApplyToAllCoh);

// Samples
static const ApplyMask_t ksApplyToAll = (
 ksApplyToNuMuCC     | ksApplyToNuMuCC1trkQE | ksApplyToNuMuCC2trkQE   | ksApplyToNuMuCC1piC |
 ksApplyToNuMuCC2piC | ksApplyToNuMuCC1pi0   | ksApplyToNuMuCC1piC1pi0 | ksApplyToNuMuCCoth  |
 ksApplyToNuECC      | ksApplyToNuMuCCWSgn   | ksApplyToNC             | ksApplyToNC1piC     |
 ksApplyToNC1pi0     | ksApplyToNCoth );
 

// Which masks apply to which beam modes
// This is defined for all samples in the BeamConf_t enum.
static const ApplyMask_t kApplyToBeamMode[kNBeamConf] = {
  /* kbLBNF_FHC */ kbApplyToFHC ,
  /* kbLBNF_RHC */ kbApplyToRHC ,
};

// Which masks apply to which samples
// This is defined for all samples in the Sample_t enum.
static const ApplyMask_t kApplyToSample[kMaxNSamples] = {
 /* ksNuMuCC         */ ksApplyToNuMuCC          ,
 /* ksNuMuCC1trkQE   */ ksApplyToNuMuCC1trkQE    ,
 /* ksNuMuCC2trkQE   */ ksApplyToNuMuCC2trkQE    ,
 /* ksNuMuCC1piC     */ ksApplyToNuMuCC1piC      ,
 /* ksNuMuCC2piC     */ ksApplyToNuMuCC2piC      ,
 /* ksNuMuCC1pi0     */ ksApplyToNuMuCC1pi0      ,
 /* ksNuMuCC1piC1pi0 */ ksApplyToNuMuCC1piC1pi0  ,
 /* ksNuMuCCoth      */ ksApplyToNuMuCCoth       ,
 /* ksNuECC          */ ksApplyToNuECC           ,
 /* ksNuMuCCWSgn     */ ksApplyToNuMuCCWSgn      ,
 /* ksNC,            */ ksApplyToNC              ,
 /* ksNC1piC         */ ksApplyToNC1piC          ,
 /* ksNC1pi0         */ ksApplyToNC1pi0          ,
 /* ksNCoth          */ ksApplyToNCoth           ,
};

// Which masks apply to which parent particle flavour
static const ApplyMask_t kApplyToFlavour[conv::kNNuFlavour] = {
  /* kNuE     */ kfApplyToNuE     , 
  /* kNuMu    */ kfApplyToNuMu    ,
  /* kNuTau   */ 0                , 
  /* kNuEBar  */ kfApplyToNuEBar  , 
  /* kNuMuBar */ kfApplyToNuMuBar ,
  /* kNuTau   */ 0                ,
};

// Which masks apply to which reaction type
static const ApplyMask_t kApplyToReacType[kNReacType] = {
  /* kmtCCQE,     */ ktApplyToCCQE    ,
  /* kmtCCMEC,    */ ktApplyToCCMEC   ,
  /* kmtCC1piC,   */ ktApplyToCC1piC  ,
  /* kmtCC1pi0,   */ ktApplyToCC1pi0  ,
  /* kmtCC2piC,   */ ktApplyToCC2piC  ,
  /* kmtCC2pi0,   */ ktApplyToCC2pi0  ,
  /* kmtCCpiCpi0, */ ktApplyToCCpiCpi0,
  /* kmtCCcoh,    */ ktApplyToCCcoh   ,
  /* kmtCCoth,    */ ktApplyToCCoth,
  /* kmtNCEL,     */ ktApplyToNCEL    , 
  /* kmtNCMEC,    */ ktApplyToNCMEC   | ktApplyToNCEL,
  /* kmtNC1piC,   */ ktApplyToNC1piC  | ktApplyToNCoth,
  /* kmtNC1pi0,   */ ktApplyToNC1pi0  | ktApplyToNCoth,
  /* kmtNC2piC,   */ ktApplyToNC2piC  | ktApplyToNCoth,
  /* kmtNC2pi0,   */ ktApplyToNC2pi0  | ktApplyToNCoth,
  /* kmtNCpiCpi0, */ ktApplyToNCpiCpi0| ktApplyToNCoth,
  /* kmtNCcoh,    */ ktApplyToNCcoh   | ktApplyToNCoth,
  /* kmtNCoth,    */ ktApplyToNCoth   ,
  /* kmtOther     */ 0
};

// Which physics parameters are applied to which beam/sample/mode
// This one uses only the parameters listed in kFitParam and ArrIdx must be used to get the right value.
static const ApplyMask_t kApplyParamToTemplates[kNFitParams] = 
{ 
  //                          Beam Current | True Nu Flavour  | Sample       | Interaction type
  // FHC flux
  /* kNuisFHCNuMuFlux00    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux01    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux02    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux03    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux04    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux05    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux06    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux07    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux08    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux09    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux10    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux11    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux12    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux13    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux14    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux15    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux16    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux17    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux18    */ kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux00 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux01 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux02 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux03 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux04 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux05 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux06 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux07 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux08 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux09 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux10 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux11 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux12 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux13 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux14 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux15 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux16 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux17 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux18 */ kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFlux00     */ kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFlux01     */ kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFlux02     */ kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFlux03     */ kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFlux04     */ kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFlux05     */ kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFlux06     */ kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFlux00  */ kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFlux01  */ kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFlux02  */ kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFlux03  */ kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFlux04  */ kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFlux05  */ kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFlux06  */ kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  // RHC flux
  /* kNuisRHCNuMuFlux00    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux01    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux02    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux03    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux04    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux05    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux06    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux07    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux08    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux09    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux10    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux11    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux12    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux13    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux14    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux15    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux16    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux17    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux18    */ kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux00 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux01 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux02 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux03 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux04 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux05 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux06 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux07 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux08 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux09 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux10 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux11 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux12 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux13 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux14 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux15 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux16 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux17 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux18 */ kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFlux00     */ kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFlux01     */ kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFlux02     */ kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFlux03     */ kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFlux04     */ kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFlux05     */ kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFlux06     */ kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFlux00  */ kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFlux01  */ kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFlux02  */ kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFlux03  */ kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFlux04  */ kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFlux05  */ kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFlux06  */ kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  // Cross-sections
  /* kNuisIntNuCCQE1               */ kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCCQE      ,
  /* kNuisIntNuCCQE2               */ kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCCQE      ,
  /* kNuisIntNuCCQE3               */ kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCCQE      ,
  /* kNuisIntNuBarCCQE1            */ kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCCQE      ,
  /* kNuisIntNuBarCCQE2            */ kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCCQE      ,
  /* kNuisIntNuBarCCQE3            */ kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCCQE      ,
  /* kNuisIntNuCCMEC               */ kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCCMEC     ,
  /* kNuisIntNuBarCCMEC            */ kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCCMEC     ,
  /* kNuisIntNuCC1piz1             */ kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCC1pi0    ,
  /* kNuisIntNuCC1piz2             */ kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCC1pi0    ,
  /* kNuisIntNuCC1piz3             */ kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCC1pi0    ,
  /* kNuisIntNuCC1pic1             */ kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCC1piC    ,
  /* kNuisIntNuCC1pic2             */ kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCC1piC    ,
  /* kNuisIntNuCC1pic3             */ kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCC1piC    ,
  /* kNuisIntNuBarCC1piz1          */ kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCC1pi0    ,
  /* kNuisIntNuBarCC1piz2          */ kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCC1pi0    ,
  /* kNuisIntNuBarCC1piz3          */ kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCC1pi0    ,
  /* kNuisIntNuBarCC1pic1          */ kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCC1piC    ,
  /* kNuisIntNuBarCC1pic2          */ kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCC1piC    ,
  /* kNuisIntNuBarCC1pic3          */ kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCC1piC    ,
  /* kNuisIntNuCC2Pi               */ kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToAllCC2pi  ,
  /* kNuisIntNuBarCC2Pi            */ kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToAllCC2pi  ,
  /* kNuisIntNuDIS1                */ kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCCoth     ,
  /* kNuisIntNuDIS2                */ kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCCoth     ,
  /* kNuisIntNuDIS3                */ kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCCoth     ,
  /* kNuisIntNuBarDIS1             */ kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCCoth     ,
  /* kNuisIntNuBarDIS2             */ kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCCoth     ,
  /* kNuisIntNuBarDIS3             */ kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCCoth     ,
  /* kNuisIntNormNuCoherent        */ kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCCcoh     ,
  /* kNuisIntNormNuBarCoherent     */ kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCCcoh     ,
  /* kNuisIntNuNormNC              */ kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToAllNC     ,
  /* kNuisIntNuBarNormNC           */ kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToAllNC     ,
  /* kNuisIntNormNuMuToNuE         */ kbApplyToAll | kfApplyToNuEAny    | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntPiMeanFreePath        */ kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntNucMeanFreePath       */ kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntFracPiChargeExchange  */ kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntFracPiInelastic       */ kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntFracPiAbsorb          */ kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntFracPiProduction      */ kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntFracNucChargeExchange */ kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntFracNucInelastic      */ kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntFracNucAbsorb         */ kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntFracNucProduction     */ kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  // Detector systematics
  /* kNuisEffNuMuCC1trkQE  */ kbApplyToAll | kfApplyToAll | ksApplyToNuMuCC1trkQE   | ktApplyToAll ,
  /* kNuisEffNuMuCC2trkQE  */ kbApplyToAll | kfApplyToAll | ksApplyToNuMuCC2trkQE   | ktApplyToAll ,
  /* kNuisEffNuMuCC1piC    */ kbApplyToAll | kfApplyToAll | ksApplyToNuMuCC1piC     | ktApplyToAll ,
  /* kNuisEffNuMuCC1pi0    */ kbApplyToAll | kfApplyToAll | ksApplyToNuMuCC1pi0     | ktApplyToAll ,
  /* kNuisEffNuMuCC1piC1pi0*/ kbApplyToAll | kfApplyToAll | ksApplyToNuMuCC1piC1pi0 | ktApplyToAll ,
  /* kNuisEffNuMuCCoth     */ kbApplyToAll | kfApplyToAll | ksApplyToNuMuCCoth      | ktApplyToAll ,
  /* kNuisEffNuECC         */ kbApplyToAll | kfApplyToAll | ksApplyToNuECC          | ktApplyToAll ,
  /* kNuisEffNuMuCCWSgn    */ kbApplyToAll | kfApplyToAll | ksApplyToNuMuCCWSgn     | ktApplyToAll ,
  /* kNuisEffNC            */ kbApplyToAll | kfApplyToAll | ksApplyToNC             | ktApplyToAll ,
};

} //conv
} //valor

#endif // _valor_dune_apply_params_h_
