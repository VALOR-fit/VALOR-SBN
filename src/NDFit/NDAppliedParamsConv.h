#ifndef _valor_dune_nd_apply_params_h_
#define _valor_dune_nd_apply_params_h_

// NOT IN USE YET
// A header file designed to replace the huge arrays in NDFitParams.h

// FMWK
#include "Conventions/NuFlavour.h"

// Dune
#include "Conventions/BeamConf.h"
#include "Conventions/DuneBuild.h"
#include "Conventions/ReacMode.h"
#include "NDFit/NDFitParams.h"

namespace valor {
namespace conv {
// A bitmask to control which parameters are applied to which modes
// If we move to C++11, we should use an enum class here instead
// But in older versions we can't use an enum and be guaranteed we have the 64 bits we need.
typedef ULong64_t ApplyMask_t;

static const ApplyMask_t kApplyMaskOne = 1ul;

static const ApplyMask_t kApplyUndefined          = (kApplyMaskOne <<  0 );
static const ApplyMask_t kbApplyToAll             = (kApplyMaskOne <<  1 ); // Current
static const ApplyMask_t kbApplyToFHC             = (kApplyMaskOne <<  2 );
static const ApplyMask_t kbApplyToRHC             = (kApplyMaskOne <<  3 );
static const ApplyMask_t kfApplyToAll             = (kApplyMaskOne <<  4 ); // True flavour
static const ApplyMask_t kfApplyToNuMuAny         = (kApplyMaskOne <<  5 );
static const ApplyMask_t kfApplyToNuMu            = (kApplyMaskOne <<  6 );
static const ApplyMask_t kfApplyToNuMuBar         = (kApplyMaskOne <<  7 );
static const ApplyMask_t kfApplyToNuEAny          = (kApplyMaskOne <<  8 );
static const ApplyMask_t kfApplyToNuE             = (kApplyMaskOne <<  9 );
static const ApplyMask_t kfApplyToNuEBar          = (kApplyMaskOne << 10 );
static const ApplyMask_t ksApplyToAll             = (kApplyMaskOne << 11 ); // Sample
static const ApplyMask_t ksApplyToNuMuCC          = (kApplyMaskOne << 12 );
static const ApplyMask_t ksApplyToNuMuCC1trkQE    = (kApplyMaskOne << 13 );
static const ApplyMask_t ksApplyToNuMuCC2trkQE    = (kApplyMaskOne << 14 );
static const ApplyMask_t ksApplyToNuMuCC1piC      = (kApplyMaskOne << 15 );
static const ApplyMask_t ksApplyToNuMuCC2piC      = (kApplyMaskOne << 16 );
static const ApplyMask_t ksApplyToNuMuCC1pi0      = (kApplyMaskOne << 17 );
static const ApplyMask_t ksApplyToNuMuCC1piC1pi0  = (kApplyMaskOne << 18 );
static const ApplyMask_t ksApplyToNuMuCCoth       = (kApplyMaskOne << 19 );
static const ApplyMask_t ksApplyToNuECC           = (kApplyMaskOne << 20 );
static const ApplyMask_t ksApplyToNuMuCCWSgn      = (kApplyMaskOne << 21 );
static const ApplyMask_t ksApplyToNC              = (kApplyMaskOne << 22 );
static const ApplyMask_t ksApplyToNC1piC          = (kApplyMaskOne << 23 );
static const ApplyMask_t ksApplyToNC1pi0          = (kApplyMaskOne << 24 );
static const ApplyMask_t ksApplyToNCoth           = (kApplyMaskOne << 25 ); 
static const ApplyMask_t ktApplyToAll             = (kApplyMaskOne << 26 ); // Reaction type
static const ApplyMask_t ktApplyToAllCC           = (kApplyMaskOne << 27 );
static const ApplyMask_t ktApplyToCCQE            = (kApplyMaskOne << 28 );
static const ApplyMask_t ktApplyToCCMEC           = (kApplyMaskOne << 29 );
static const ApplyMask_t ktApplyToCC1piC          = (kApplyMaskOne << 30 );
static const ApplyMask_t ktApplyToCC1pi0          = (kApplyMaskOne << 31 );
static const ApplyMask_t ktApplyToCC2piC          = (kApplyMaskOne << 32 );
static const ApplyMask_t ktApplyToCC2pi0          = (kApplyMaskOne << 33 );
static const ApplyMask_t ktApplyToCCpiCpi0        = (kApplyMaskOne << 34 );
static const ApplyMask_t ktApplyToCCcoh           = (kApplyMaskOne << 35 );
static const ApplyMask_t ktApplyToCCoth           = (kApplyMaskOne << 36 );
static const ApplyMask_t ktApplyToAllNC           = (kApplyMaskOne << 37 );
static const ApplyMask_t ktApplyToNCEL            = (kApplyMaskOne << 38 );
static const ApplyMask_t ktApplyToNCMEC           = (kApplyMaskOne << 39 );
static const ApplyMask_t ktApplyToNC1piC          = (kApplyMaskOne << 40 );
static const ApplyMask_t ktApplyToNC1pi0          = (kApplyMaskOne << 41 );
static const ApplyMask_t ktApplyToNC2piC          = (kApplyMaskOne << 42 );
static const ApplyMask_t ktApplyToNC2pi0          = (kApplyMaskOne << 43 );
static const ApplyMask_t ktApplyToNCpiCpi0        = (kApplyMaskOne << 44 );
static const ApplyMask_t ktApplyToNCcoh           = (kApplyMaskOne << 45 );
static const ApplyMask_t ktApplyToNCoth           = (kApplyMaskOne << 46 );

// Which masks apply to which beam modes
// This is defined for all samples in the BeamConf_t enum.
static const ApplyMask_t kNDApplyToBeamMode[kNBeamConf] = {
  /* kbFHC */ kbApplyToAll | kbApplyToFHC ,
  /* kbRHC */ kbApplyToAll | kbApplyToRHC ,
};

// Which masks apply to which samples
// This is defined for all samples in the NDSample_t enum.
static const ApplyMask_t kNDApplyToSample[kMaxNNDSamples] = {
 /* ksNDNuMuCC         */ ksApplyToAll | ksApplyToNuMuCC          ,
 /* ksNDNuMuCC1trkQE   */ ksApplyToAll | ksApplyToNuMuCC1trkQE    ,
 /* ksNDNuMuCC2trkQE   */ ksApplyToAll | ksApplyToNuMuCC2trkQE    ,
 /* ksNDNuMuCC1piC     */ ksApplyToAll | ksApplyToNuMuCC1piC      ,
 /* ksNDNuMuCC2piC     */ ksApplyToAll | ksApplyToNuMuCC2piC      ,
 /* ksNDNuMuCC1pi0     */ ksApplyToAll | ksApplyToNuMuCC1pi0      ,
 /* ksNDNuMuCC1piC1pi0 */ ksApplyToAll | ksApplyToNuMuCC1piC1pi0  ,
 /* ksNDNuMuCCoth      */ ksApplyToAll | ksApplyToNuMuCCoth       ,
 /* ksNDNuECC          */ ksApplyToAll | ksApplyToNuECC           ,
 /* ksNDNuMuCCWSgn     */ ksApplyToAll | ksApplyToNuMuCCWSgn      ,
 /* ksNDNC,            */ ksApplyToAll | ksApplyToNC              ,
 /* ksNDNC1piC         */ ksApplyToAll | ksApplyToNC1piC          ,
 /* ksNDNC1pi0         */ ksApplyToAll | ksApplyToNC1pi0          ,
 /* ksNDNCoth          */ ksApplyToAll | ksApplyToNCoth           ,
};

// Which masks apply to which parent particle flavour
static const ApplyMask_t kNDApplyToFlavour[conv::kNNuFlavour] = {
  /* kNuE     */ kfApplyToAll | kfApplyToNuEAny  | kfApplyToNuE     , 
  /* kNuMu    */ kfApplyToAll | kfApplyToNuMuAny | kfApplyToNuMu    ,
  /* kNuTau   */ kfApplyToAll                                       , 
  /* kNuEBar  */ kfApplyToAll | kfApplyToNuEAny  | kfApplyToNuEBar  , 
  /* kNuMuBar */ kfApplyToAll | kfApplyToNuMuAny | kfApplyToNuMuBar ,
  /* kNuTau   */ kfApplyToAll                                       ,
};

// Which masks apply to which reaction type
static const ApplyMask_t kNDApplyToReacType[kNReacType] = {
  /* kmtCCQE,     */ ktApplyToAll | ktApplyToAllCC | ktApplyToCCQE    ,
  /* kmtCCMEC,    */ ktApplyToAll | ktApplyToAllCC | ktApplyToCCMEC   ,
  /* kmtCC1piC,   */ ktApplyToAll | ktApplyToAllCC | ktApplyToCC1piC  ,
  /* kmtCC1pi0,   */ ktApplyToAll | ktApplyToAllCC | ktApplyToCC1pi0  ,
  /* kmtCC2piC,   */ ktApplyToAll | ktApplyToAllCC | ktApplyToCC2piC  ,
  /* kmtCC2pi0,   */ ktApplyToAll | ktApplyToAllCC | ktApplyToCC2pi0  ,
  /* kmtCCpiCpi0, */ ktApplyToAll | ktApplyToAllCC | ktApplyToCCpiCpi0,
  /* kmtCCcoh,    */ ktApplyToAll | ktApplyToAllCC | ktApplyToCCcoh   ,
  /* kmtCCoth,    */ ktApplyToAll | ktApplyToAllCC | ktApplyToCCoth   ,
  /* kmtNCEL,     */ ktApplyToAll | ktApplyToAllCC | ktApplyToNCEL    , 
  /* kmtNCMEC,    */ ktApplyToAll | ktApplyToAllCC | ktApplyToNCMEC   ,
  /* kmtNC1piC,   */ ktApplyToAll | ktApplyToAllCC | ktApplyToNC1piC  ,
  /* kmtNC1pi0,   */ ktApplyToAll | ktApplyToAllCC | ktApplyToNC1pi0  ,
  /* kmtNC2piC,   */ ktApplyToAll | ktApplyToAllCC | ktApplyToNC2piC  ,
  /* kmtNC2pi0,   */ ktApplyToAll | ktApplyToAllCC | ktApplyToNC2pi0  ,
  /* kmtNCpiCpi0, */ ktApplyToAll | ktApplyToAllCC | ktApplyToNCpiCpi0,
  /* kmtNCcoh,    */ ktApplyToAll | ktApplyToAllCC | ktApplyToNCcoh   ,
  /* kmtNCoth,    */ ktApplyToAll | ktApplyToAllCC | ktApplyToNCoth   ,
  /* kmtOther     */ ktApplyToAll
};

// Which physics parameters are applied to which beam/sample/mode
// This one uses only the parameters listed in kNDFitParam and ArrIdx must be used to get the right value.
static const ApplyMask_t kNDApplyParamToTemplates[kNNDFitParams] = 
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
  /* kNuisNormCCQE         */ kbApplyToAll | kfApplyToAll     | ksApplyToAll | ktApplyToCCQE   ,
  /* kNuisNormCC1piC       */ kbApplyToAll | kfApplyToAll     | ksApplyToAll | ktApplyToCC1piC ,
  /* kNuisNormCC1pi0       */ kbApplyToAll | kfApplyToAll     | ksApplyToAll | ktApplyToCC1pi0 ,
  /* kNuisNormCCoth        */ kbApplyToAll | kfApplyToAll     | ksApplyToAll | ktApplyToCCoth  ,
  /* kNuisNormNC           */ kbApplyToAll | kfApplyToAll     | ksApplyToAll | ktApplyToAllNC  ,
  /* kNuisRatioNuENuMu     */ kbApplyToAll | kfApplyToNuEAny  | ksApplyToAll | ktApplyToAll    ,
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

#endif // _valor_dune_nd_apply_params_h_
