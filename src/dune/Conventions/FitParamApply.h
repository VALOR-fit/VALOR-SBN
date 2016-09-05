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
// Warning: already using 63 items 
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
static const ApplyMask_t ksApplyToNuMuCC0pi1trk   = (kApplyMaskOne <<  8 ); // Sample
static const ApplyMask_t ksApplyToNuMuCC0pi2trk   = (kApplyMaskOne <<  9 );
static const ApplyMask_t ksApplyToNuMuCC0piNtrk   = (kApplyMaskOne << 10 );
static const ApplyMask_t ksApplyToNuMuCC3trkDelta = (kApplyMaskOne << 11 );
static const ApplyMask_t ksApplyToNuMuCC1piC      = (kApplyMaskOne << 12 );
static const ApplyMask_t ksApplyToNuMuCC2piC      = (kApplyMaskOne << 13 );
static const ApplyMask_t ksApplyToNuMuCC1pi0      = (kApplyMaskOne << 14 );
static const ApplyMask_t ksApplyToNuMuCC1piC1pi0  = (kApplyMaskOne << 15 );
static const ApplyMask_t ksApplyToNuMuCCoth       = (kApplyMaskOne << 16 );
static const ApplyMask_t ksApplyToNuMuCCWS0pi     = (kApplyMaskOne << 17 );
static const ApplyMask_t ksApplyToNuMuCCWS1piC    = (kApplyMaskOne << 18 );
static const ApplyMask_t ksApplyToNuMuCCWS1pi0    = (kApplyMaskOne << 19 );
static const ApplyMask_t ksApplyToNuMuCCWSoth     = (kApplyMaskOne << 20 );
static const ApplyMask_t ksApplyToNuECC0pi        = (kApplyMaskOne << 21 );
static const ApplyMask_t ksApplyToNuECC1piC       = (kApplyMaskOne << 22 );
static const ApplyMask_t ksApplyToNuECC1pi0       = (kApplyMaskOne << 23 );
static const ApplyMask_t ksApplyToNuECCoth        = (kApplyMaskOne << 24 );
static const ApplyMask_t ksApplyToNC0pi           = (kApplyMaskOne << 25 );
static const ApplyMask_t ksApplyToNC1piC          = (kApplyMaskOne << 26 );
static const ApplyMask_t ksApplyToNC1pi0          = (kApplyMaskOne << 27 );
static const ApplyMask_t ksApplyToNCoth           = (kApplyMaskOne << 28 );
static const ApplyMask_t ksApplyToNeutrinoElec    = (kApplyMaskOne << 29 );
static const ApplyMask_t ksApplyToInvMuDecay      = (kApplyMaskOne << 30 );
static const ApplyMask_t ksApplyToNuECCWS         = (kApplyMaskOne << 31 );
static const ApplyMask_t ksApplyToNuECC           = (kApplyMaskOne << 32 );
static const ApplyMask_t ksApplyToNuMuCCWS        = (kApplyMaskOne << 33 );
static const ApplyMask_t ksApplyToNC              = (kApplyMaskOne << 34 );
static const ApplyMask_t ksApplyToHighRes         = (kApplyMaskOne << 35 ); // Far detector selections
static const ApplyMask_t ksApplyToLowRes          = (kApplyMaskOne << 36 ); // Far detector selections
static const ApplyMask_t ktApplyToCCQE            = (kApplyMaskOne << 37 ); // Reaction type
static const ApplyMask_t ktApplyToCCMEC           = (kApplyMaskOne << 38 );
static const ApplyMask_t ktApplyToCC1piC          = (kApplyMaskOne << 39 );
static const ApplyMask_t ktApplyToCC1pi0          = (kApplyMaskOne << 40 );
static const ApplyMask_t ktApplyToCC2piC          = (kApplyMaskOne << 41 );
static const ApplyMask_t ktApplyToCC2pi0          = (kApplyMaskOne << 42 );
static const ApplyMask_t ktApplyToCCpiCpi0        = (kApplyMaskOne << 43 );
static const ApplyMask_t ktApplyToCCcoh           = (kApplyMaskOne << 44 );
static const ApplyMask_t ktApplyToCCELScat        = (kApplyMaskOne << 45 );
static const ApplyMask_t ktApplyToCCoth           = (kApplyMaskOne << 46 );
static const ApplyMask_t ktApplyToNCEL            = (kApplyMaskOne << 47 );
static const ApplyMask_t ktApplyToNCMEC           = (kApplyMaskOne << 48 );
static const ApplyMask_t ktApplyToNC1piC          = (kApplyMaskOne << 49 );
static const ApplyMask_t ktApplyToNC1pi0          = (kApplyMaskOne << 50 );
static const ApplyMask_t ktApplyToNC2piC          = (kApplyMaskOne << 51 );
static const ApplyMask_t ktApplyToNC2pi0          = (kApplyMaskOne << 52 );
static const ApplyMask_t ktApplyToNCpiCpi0        = (kApplyMaskOne << 53 );
static const ApplyMask_t ktApplyToNCcoh           = (kApplyMaskOne << 54 );
static const ApplyMask_t ktApplyToNCELScat        = (kApplyMaskOne << 55 );
static const ApplyMask_t ktApplyToNCoth           = (kApplyMaskOne << 56 );
static const ApplyMask_t ktApplyToNuEELScat       = (kApplyMaskOne << 57 ); //only for nue: CC + NC + interference
static const ApplyMask_t kdApplyToDUNEND          = (kApplyMaskOne << 58 ); // Dectectors
static const ApplyMask_t kdApplyToDUNEFD          = (kApplyMaskOne << 59 );
static const ApplyMask_t kdApplyToSBND            = (kApplyMaskOne << 60 );
static const ApplyMask_t kdApplyToMicroBooNE      = (kApplyMaskOne << 61 );
static const ApplyMask_t kdApplyToICARUS          = (kApplyMaskOne << 62 );

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
static const ApplyMask_t ktApplyToCCQELike    = ktApplyToCCQE     | ktApplyToCCMEC;
static const ApplyMask_t ktApplyToAllCCELScat = ktApplyToCCELScat | ktApplyToNuEELScat; // nu + e CC elastic scattering (inverse muon/tau decay) and nue+e
static const ApplyMask_t ktApplyToAllCC1pi    = ktApplyToCC1piC   | ktApplyToCC1pi0;
static const ApplyMask_t ktApplyToAllCC2pi    = ktApplyToCC2piC   | ktApplyToCC2pi0 | ktApplyToCCpiCpi0;
static const ApplyMask_t ktApplyToAllCC       = ktApplyToCCQELike | ktApplyToAllCC1pi | ktApplyToAllCC2pi | ktApplyToCCcoh | ktApplyToCCoth | ktApplyToCCELScat;

static const ApplyMask_t ktApplyToNCElLike    = ktApplyToNCEL     | ktApplyToNCMEC; //this is not used, modes disabled
static const ApplyMask_t ktApplyToAllNCELScat = ktApplyToNCELScat | ktApplyToNuEELScat; //nu+e NC elastic scattering 
static const ApplyMask_t ktApplyToAllNC1pi    = ktApplyToNC1piC   | ktApplyToNC1pi0;
static const ApplyMask_t ktApplyToAllNC2pi    = ktApplyToNC2piC   | ktApplyToNC2pi0   | ktApplyToNCpiCpi0;
static const ApplyMask_t ktApplyToAllNC       = ktApplyToNCElLike | ktApplyToAllNC1pi | ktApplyToAllNC2pi | ktApplyToNCcoh | ktApplyToNCoth | ktApplyToNCELScat;

static const ApplyMask_t ktApplyToAllCoh = ktApplyToCCcoh | ktApplyToNCcoh;
static const ApplyMask_t ktApplyToAllELScat = ktApplyToCCELScat | ktApplyToNuEELScat | ktApplyToNCELScat;

static const ApplyMask_t ktApplyToAll = ktApplyToAllCC | ktApplyToAllNC;
static const ApplyMask_t ktApplyToAllButCoh = ktApplyToAll & (~ktApplyToAllCoh);
static const ApplyMask_t ktApplyToAllButELScat = ktApplyToAll & (~ktApplyToAllELScat);//in case its necessary

// Detectors
static const ApplyMask_t kdApplyToAllDUNE = kdApplyToDUNEND | kdApplyToDUNEFD;
static const ApplyMask_t kdApplyToAllSBN  = kdApplyToSBND | kdApplyToMicroBooNE | kdApplyToICARUS;
static const ApplyMask_t kdApplyToAllSBN2Det  = kdApplyToSBND | kdApplyToMicroBooNE;
static const ApplyMask_t kdApplyToAllND  = kdApplyToDUNEND | kdApplyToSBND | kdApplyToMicroBooNE | kdApplyToICARUS;
static const ApplyMask_t kdApplyToAll    = kdApplyToAllND | kdApplyToAllSBN;


// Samples
static const ApplyMask_t ksApplyToAllND = (
 ksApplyToNuMuCC     | ksApplyToNuMuCC0pi1trk| ksApplyToNuMuCC0pi2trk  | ksApplyToNuMuCC0piNtrk  | ksApplyToNuMuCC3trkDelta | 
 ksApplyToNuMuCC1piC | ksApplyToNuMuCC2piC   | ksApplyToNuMuCC1pi0     | ksApplyToNuMuCC1piC1pi0 | ksApplyToNuMuCCoth       |
 ksApplyToNuMuCCWS0pi | ksApplyToNuMuCCWS1piC | ksApplyToNuMuCCWS1pi0 | ksApplyToNuMuCCWSoth |
 ksApplyToNuECC0pi   | ksApplyToNuECC1piC    | ksApplyToNuECC1pi0      | ksApplyToNuECCoth       |
 ksApplyToNC0pi      | ksApplyToNC1piC       | ksApplyToNC1pi0         | ksApplyToNCoth          |
 ksApplyToNeutrinoElec  | ksApplyToInvMuDecay   | ksApplyToNuECCWS | ksApplyToNuECC          | ksApplyToNuMuCCWS     | ksApplyToNC);

static const ApplyMask_t ksApplyToAllFD =  ksApplyToLowRes | ksApplyToHighRes;

static const ApplyMask_t ksApplyToAll = ksApplyToAllND | ksApplyToAllFD; 

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
 /* ksNuMuCC0pi1trk  */ ksApplyToNuMuCC0pi1trk   ,
 /* ksNuMuCC0pi2trk  */ ksApplyToNuMuCC0pi2trk   ,
 /* ksNuMuCC1piC     */ ksApplyToNuMuCC1piC      ,
 /* ksNuMuCC2piC     */ ksApplyToNuMuCCoth       , // ksApplyToNuMuCC2piC      ,
 /* ksNuMuCC1pi0     */ ksApplyToNuMuCC1pi0      ,
 /* ksNuMuCC1piC1pi0 */ ksApplyToNuMuCC1piC1pi0  ,
 /* ksNuMuCCoth      */ ksApplyToNuMuCCoth       ,
 /* ksNuECC          */ ksApplyToNuECC           ,
 /* ksNuMuCCWS       */ ksApplyToNuMuCCWS        ,
 /* ksNC             */ ksApplyToNC              ,
 /* ksNuMuCC0piNtrk  */ ksApplyToNuMuCCoth       , // ksApplyToNuMuCC0piNtrk   ,
 /* ksNuMuCC3trkDelta*/ ksApplyToNuMuCCoth       , // ksApplyToNuMuCC3trkDelta ,
 /* ksNuMuCCWS0pi    */ ksApplyToNuMuCCWS        , // ksApplyToNuMuCCWS0pi     ,
 /* ksNuMuCCWS1piC   */ ksApplyToNuMuCCWS        , // ksApplyToNuMuCCWS1piC    ,
 /* ksNuMuCCWS1pi0   */ ksApplyToNuMuCCWS        , // ksApplyToNuMuCCWS1pi0    ,
 /* ksNuMuCCWSoth    */ ksApplyToNuMuCCWS        , // ksApplyToNuMuCCWSoth     ,
 /* ksNuECC0pi       */ ksApplyToNuECC           , // ksApplyToNuECC0pi        ,
 /* ksNuECC1piC      */ ksApplyToNuECC           , // ksApplyToNuECC1piC       ,
 /* ksNuECC1pi0      */ ksApplyToNuECC           , // ksApplyToNuECC1pi0       ,
 /* ksNuECCoth       */ ksApplyToNuECC           , // ksApplyToNuECCoth        ,
 /* ksNC0pi          */ ksApplyToNC              , // ksApplyToNC0pi           ,
 /* ksNC1piC         */ ksApplyToNC              , // ksApplyToNC1piC          ,
 /* ksNC1pi0         */ ksApplyToNC              , // ksApplyToNC1pi0          ,
 /* ksNCoth          */ ksApplyToNC              , // ksApplyToNCoth           ,
 /* ksNeutrinoElec   */ ksApplyToNuECC           , // ksApplyToNeutrinoElec    , 
 /* ksInvMuDecay     */ ksApplyToNuMuCCoth       , // ksApplyToInvMuDecay      ,
 /* ksNuECCWS        */ ksApplyToNuECC           , // ksApplyToNuECCWS         ,
 /* ksNuMuLikeCChigh     */ ksApplyToHighRes         , 
 /* ksNuMuLikeCClow      */ ksApplyToLowRes          ,
 // /* ksNuMuBarCChigh  */ ksApplyToHighRes         , 
 // /* ksNuMuBarCClow   */ ksApplyToLowRes          ,
 /* ksNuELikeCChigh      */ ksApplyToHighRes         ,
 /* ksNuELikeCClow       */ ksApplyToLowRes          //,
 // /* ksNuEBarCChigh   */ ksApplyToHighRes         ,
 // /* ksNuEBarCClow    */ ksApplyToLowRes          
};

// Which masks apply to which parent particle flavour
static const ApplyMask_t kApplyToDetector[conv::kNDetectorsDefined] = {
  /* kdDUNEND    */  kdApplyToDUNEND,
  /* kdDUNEFD1ph */  kdApplyToDUNEFD,
  /* kdDUNEFD2ph */  kdApplyToDUNEFD,
  /* kdSBND      */  kdApplyToSBND,
  /* kdSBNuBooNE */  kdApplyToMicroBooNE,
  /* kdSBNICARUS */  kdApplyToICARUS,
  /* kdSuperK    */  0,
  /* kdHyperK    */  0,
  /* kdND280     */  0,
  /* kdND280Up   */  0,
  /* kdINGRID    */  0,
  /* kdNuPRISM   */  0,
  /* kdNuTIT     */  0
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
  /* kmtCCIMD,    */ ktApplyToCCELScat,
  /* kmtCCELScat, */ ktApplyToCCELScat,
  /* kmtCCoth,    */ ktApplyToCCoth,
  /* kmtNCEL,     */ ktApplyToNCEL    , 
  /* kmtNCMEC,    */ ktApplyToNCMEC   | ktApplyToNCEL,
  /* kmtNC1piC,   */ ktApplyToNC1piC  | ktApplyToNCoth, //why | ktApplyToNCoth ?
  /* kmtNC1pi0,   */ ktApplyToNC1pi0  | ktApplyToNCoth,
  /* kmtNC2piC,   */ ktApplyToNC2piC  | ktApplyToNCoth,
  /* kmtNC2pi0,   */ ktApplyToNC2pi0  | ktApplyToNCoth,
  /* kmtNCpiCpi0, */ ktApplyToNCpiCpi0| ktApplyToNCoth,
  /* kmtNCcoh,    */ ktApplyToNCcoh   | ktApplyToNCoth,
  /* kmtNCELScat, */ ktApplyToNCELScat,
  /* kmtNCoth,    */ ktApplyToNCoth   ,
  /* kmtELScat  , */ ktApplyToNuEELScat,
  /* kmtOther     */ 0
};

// Which physics parameters are applied to which beam/sample/mode
// This one uses only the parameters listed in kFitParam and ArrIdx must be used to get the right value.
static const ApplyMask_t kApplyParamToTemplates[kNFitParams] = 
{ 
  //                               Detector   | Beam Current | True Nu Flavour  | Sample       | Interaction type
  // oscillation params
  /* kPhypMixing23         */ kdApplyToDUNEFD | kbApplyToAll | kfApplyToAll     | ksApplyToAllFD|ktApplyToAllCC,
  /* kPhypMixing13         */ kdApplyToDUNEFD | kbApplyToAll | kfApplyToAll     | ksApplyToAllFD|ktApplyToAllCC,
  /* kPhypMixing12         */ kdApplyToDUNEFD | kbApplyToAll | kfApplyToAll     | ksApplyToAllFD|ktApplyToAllCC,
  /* kPhypCPV              */ kdApplyToDUNEFD | kbApplyToAll | kfApplyToAll     | ksApplyToAllFD|ktApplyToAllCC,
  /* kPhypDm23sq           */ kdApplyToDUNEFD | kbApplyToAll | kfApplyToAll     | ksApplyToAllFD|ktApplyToAllCC,
  /* kPhypDm12sq           */ kdApplyToDUNEFD | kbApplyToAll | kfApplyToAll     | ksApplyToAllFD|ktApplyToAllCC,
  // FHC flux
  /* kNuisFHCNuMuFlux00    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux01    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux02    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux03    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux04    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux05    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux06    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux07    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux08    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux09    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux10    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux11    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux12    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux13    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux14    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux15    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux16    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux17    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFlux18    */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux00 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux01 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux02 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux03 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux04 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux05 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux06 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux07 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux08 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux09 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux10 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux11 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux12 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux13 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux14 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux15 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux16 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux17 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFlux18 */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFlux00     */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFlux01     */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFlux02     */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFlux03     */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFlux04     */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFlux05     */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFlux06     */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFlux00  */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFlux01  */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFlux02  */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFlux03  */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFlux04  */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFlux05  */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFlux06  */ kdApplyToDUNEND | kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  // RHC flux
  /* kNuisRHCNuMuFlux00    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux01    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux02    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux03    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux04    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux05    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux06    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux07    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux08    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux09    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux10    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux11    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux12    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux13    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux14    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux15    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux16    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux17    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFlux18    */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux00 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux01 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux02 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux03 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux04 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux05 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux06 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux07 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux08 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux09 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux10 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux11 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux12 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux13 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux14 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux15 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux16 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux17 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFlux18 */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFlux00     */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFlux01     */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFlux02     */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFlux03     */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFlux04     */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFlux05     */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFlux06     */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFlux00  */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFlux01  */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFlux02  */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFlux03  */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFlux04  */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFlux05  */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFlux06  */ kdApplyToDUNEND | kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  //Far detector flux
  //FHC
  /* kNuisFHCNuMuFDFlux00    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFDFlux01    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFDFlux02    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFDFlux03    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFDFlux04    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFDFlux05    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFDFlux06    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFDFlux07    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFDFlux08    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFDFlux09    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFDFlux10    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFDFlux11    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFDFlux12    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFDFlux13    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFDFlux14    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFDFlux15    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFDFlux16    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFDFlux17    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuFDFlux18    */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux00 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux01 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux02 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux03 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux04 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux05 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux06 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux07 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux08 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux09 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux10 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux11 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux12 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux13 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux14 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux15 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux16 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux17 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuMuBarFDFlux18 */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFDFlux00     */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFDFlux01     */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFDFlux02     */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFDFlux03     */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFDFlux04     */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFDFlux05     */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEFDFlux06     */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFDFlux00  */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFDFlux01  */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFDFlux02  */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFDFlux03  */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFDFlux04  */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFDFlux05  */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisFHCNuEBarFDFlux06  */ kdApplyToDUNEFD | kbApplyToFHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  // RHC flux
  /* kNuisRHCNuMuFDFlux00    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFDFlux01    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFDFlux02    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFDFlux03    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFDFlux04    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFDFlux05    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFDFlux06    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFDFlux07    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFDFlux08    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFDFlux09    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFDFlux10    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFDFlux11    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFDFlux12    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFDFlux13    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFDFlux14    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFDFlux15    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFDFlux16    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFDFlux17    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuFDFlux18    */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMu    | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux00 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux01 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux02 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux03 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux04 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux05 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux06 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux07 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux08 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux09 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux10 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux11 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux12 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux13 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux14 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux15 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux16 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux17 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuMuBarFDFlux18 */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuMuBar | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFDFlux00     */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFDFlux01     */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFDFlux02     */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFDFlux03     */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFDFlux04     */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFDFlux05     */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEFDFlux06     */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuE     | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFDFlux00  */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFDFlux01  */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFDFlux02  */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFDFlux03  */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFDFlux04  */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFDFlux05  */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  /* kNuisRHCNuEBarFDFlux06  */ kdApplyToDUNEFD | kbApplyToRHC | kfApplyToNuEBar  | ksApplyToAll | ktApplyToAll ,
  // Cross-sections
  /* kNuisIntNuCCQE1               */ kdApplyToAll | kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCCQE      ,
  /* kNuisIntNuCCQE2               */ kdApplyToAll | kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCCQE      ,
  /* kNuisIntNuCCQE3               */ kdApplyToAll | kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCCQE      ,
  /* kNuisIntNuBarCCQE1            */ kdApplyToAll | kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCCQE      ,
  /* kNuisIntNuBarCCQE2            */ kdApplyToAll | kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCCQE      ,
  /* kNuisIntNuBarCCQE3            */ kdApplyToAll | kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCCQE      ,
  /* kNuisIntNuCCMEC               */ kdApplyToAll | kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCCMEC     ,
  /* kNuisIntNuBarCCMEC            */ kdApplyToAll | kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCCMEC     ,
  /* kNuisIntNuCC1piz1             */ kdApplyToAll | kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCC1pi0    ,
  /* kNuisIntNuCC1piz2             */ kdApplyToAll | kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCC1pi0    ,
  /* kNuisIntNuCC1piz3             */ kdApplyToAll | kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCC1pi0    ,
  /* kNuisIntNuCC1pic1             */ kdApplyToAll | kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCC1piC    ,
  /* kNuisIntNuCC1pic2             */ kdApplyToAll | kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCC1piC    ,
  /* kNuisIntNuCC1pic3             */ kdApplyToAll | kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCC1piC    ,
  /* kNuisIntNuBarCC1piz1          */ kdApplyToAll | kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCC1pi0    ,
  /* kNuisIntNuBarCC1piz2          */ kdApplyToAll | kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCC1pi0    ,
  /* kNuisIntNuBarCC1piz3          */ kdApplyToAll | kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCC1pi0    ,
  /* kNuisIntNuBarCC1pic1          */ kdApplyToAll | kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCC1piC    ,
  /* kNuisIntNuBarCC1pic2          */ kdApplyToAll | kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCC1piC    ,
  /* kNuisIntNuBarCC1pic3          */ kdApplyToAll | kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCC1piC    ,
  /* kNuisIntNuCC2Pi               */ kdApplyToAll | kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToAllCC2pi  ,
  /* kNuisIntNuBarCC2Pi            */ kdApplyToAll | kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToAllCC2pi  ,
  /* kNuisIntNuDIS1                */ kdApplyToAll | kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCCoth     ,
  /* kNuisIntNuDIS2                */ kdApplyToAll | kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCCoth     ,
  /* kNuisIntNuDIS3                */ kdApplyToAll | kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCCoth     ,
  /* kNuisIntNuBarDIS1             */ kdApplyToAll | kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCCoth     ,
  /* kNuisIntNuBarDIS2             */ kdApplyToAll | kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCCoth     ,
  /* kNuisIntNuBarDIS3             */ kdApplyToAll | kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCCoth     ,
  /* kNuisIntNormNuCoherent        */ kdApplyToAll | kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToCCcoh     ,
  /* kNuisIntNormNuBarCoherent     */ kdApplyToAll | kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToCCcoh     ,
  /* kNuisIntNuNormNC              */ kdApplyToAll | kbApplyToAll | kfApplyToNuAny     | ksApplyToAll | ktApplyToAllNC     ,
  /* kNuisIntNuBarNormNC           */ kdApplyToAll | kbApplyToAll | kfApplyToNuBarAny  | ksApplyToAll | ktApplyToAllNC     ,
  /* kNuisIntNormNuMuToNuE         */ kdApplyToAll | kbApplyToAll | kfApplyToNuEAny    | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntPiMeanFreePath        */ kdApplyToAll | kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntNucMeanFreePath       */ kdApplyToAll | kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntFracPiChargeExchange  */ kdApplyToAll | kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntFracPiInelastic       */ kdApplyToAll | kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntFracPiAbsorb          */ kdApplyToAll | kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntFracPiProduction      */ kdApplyToAll | kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntFracNucChargeExchange */ kdApplyToAll | kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntFracNucInelastic      */ kdApplyToAll | kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntFracNucAbsorb         */ kdApplyToAll | kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  /* kNuisIntFracNucProduction     */ kdApplyToAll | kbApplyToAll | kfApplyToAll       | ksApplyToAll | ktApplyToAllButCoh ,
  // Detector systematics
  /* kNuisEffNuMuCC0pi1trk */ kdApplyToAllND | kbApplyToAll | kfApplyToAll | ksApplyToNuMuCC0pi1trk  | ktApplyToAll ,
  /* kNuisEffNuMuCC0pi2trk */ kdApplyToAllND | kbApplyToAll | kfApplyToAll | ksApplyToNuMuCC0pi2trk  | ktApplyToAll ,
  /* kNuisEffNuMuCC1piC    */ kdApplyToAllND | kbApplyToAll | kfApplyToAll | ksApplyToNuMuCC1piC     | ktApplyToAll ,
  /* kNuisEffNuMuCC1pi0    */ kdApplyToAllND | kbApplyToAll | kfApplyToAll | ksApplyToNuMuCC1pi0     | ktApplyToAll ,
  /* kNuisEffNuMuCC1piC1pi0*/ kdApplyToAllND | kbApplyToAll | kfApplyToAll | ksApplyToNuMuCC1piC1pi0 | ktApplyToAll ,
  /* kNuisEffNuMuCCoth     */ kdApplyToAllND | kbApplyToAll | kfApplyToAll | ksApplyToNuMuCCoth      | ktApplyToAll ,
  /* kNuisEffNuECC         */ kdApplyToAllND | kbApplyToAll | kfApplyToAll | ksApplyToNuECC          | ktApplyToAll ,
  /* kNuisEffNuMuCCWS      */ kdApplyToAllND | kbApplyToAll | kfApplyToAll | ksApplyToNuMuCCWS       | ktApplyToAll ,
  /* kNuisEffNC            */ kdApplyToAllND | kbApplyToAll | kfApplyToAll | ksApplyToNC             | ktApplyToAll ,
  // Far detector systematics 
  /* kNuisEffFDNuMuCCHigh     */ kdApplyToDUNEFD | kbApplyToAll | kfApplyToNuMuAny     | ksApplyToHighRes | ktApplyToAll ,
  /* kNuisEffFDNuMuCCLow      */ kdApplyToDUNEFD | kbApplyToAll | kfApplyToNuMuAny     | ksApplyToLowRes  | ktApplyToAll ,
  /* kNuisEffFDNuECCHigh      */ kdApplyToDUNEFD | kbApplyToAll | kfApplyToNuEAny      | ksApplyToHighRes | ktApplyToAll ,
  /* kNuisEffFDNuECCLow       */ kdApplyToDUNEFD | kbApplyToAll | kfApplyToNuEAny      | ksApplyToLowRes  | ktApplyToAll 
};

} //conv
} //valor

#endif // _valor_dune_apply_params_h_
