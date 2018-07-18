//________________________________________________________________________________________
/*

Copyright (c) 2010-2018, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include <utility>

#include "valor/Messenger/Messenger.h"
#include "valor/Utilities/UtlStr.h"

#include "dune/Conventions/FitParamApply.h"

using namespace valor;
using namespace valor::conv;

// Groups of systematics
// Beam
const BeamApplyMask_t valor::conv::kbApplyToAll = kbApplyToFHC | kbApplyToRHC;

// Nu flavour
const FlavApplyMask_t valor::conv::kfApplyToNuAny    = kfApplyToNuMu    | kfApplyToNuE   ; // NuAny means any non-barred
const FlavApplyMask_t valor::conv::kfApplyToNuBarAny = kfApplyToNuMuBar | kfApplyToNuEBar;
const FlavApplyMask_t valor::conv::kfApplyToNuEAny   = kfApplyToNuE     | kfApplyToNuEBar;
const FlavApplyMask_t valor::conv::kfApplyToNuMuAny  = kfApplyToNuMu    | kfApplyToNuMuBar;
const FlavApplyMask_t valor::conv::kfApplyToAll      = kfApplyToNuAny   | kfApplyToNuBarAny;

// Reaction type
const ReacTypeApplyMask_t valor::conv::ktApplyToCCQELike    = ktApplyToCCQE     | ktApplyToCCMEC;
const ReacTypeApplyMask_t valor::conv::ktApplyToAllCCELScat = ktApplyToCCELScat | ktApplyToNuEELScat; // nu + e CC elastic scattering (inverse muon/tau decay) and nue+e
const ReacTypeApplyMask_t valor::conv::ktApplyToAllCC1pi    = ktApplyToCC1piC   | ktApplyToCC1pi0;
const ReacTypeApplyMask_t valor::conv::ktApplyToAllCC2pi    = ktApplyToCC2piC   | ktApplyToCC2pi0 | ktApplyToCCpiCpi0;
const ReacTypeApplyMask_t valor::conv::ktApplyToAllCC       = ktApplyToCCQELike | ktApplyToAllCC1pi | ktApplyToAllCC2pi | ktApplyToCCcoh | ktApplyToCCoth | ktApplyToCCELScat;

const ReacTypeApplyMask_t valor::conv::ktApplyToNCElLike    = ktApplyToNCEL     | ktApplyToNCMEC; //this is not used, modes disabled
const ReacTypeApplyMask_t valor::conv::ktApplyToAllNCELScat = ktApplyToNCELScat | ktApplyToNuEELScat; //nu+e NC elastic scattering
const ReacTypeApplyMask_t valor::conv::ktApplyToAllNC1pi    = ktApplyToNC1piC   | ktApplyToNC1pi0;
const ReacTypeApplyMask_t valor::conv::ktApplyToAllNC2pi    = ktApplyToNC2piC   | ktApplyToNC2pi0   | ktApplyToNCpiCpi0;
const ReacTypeApplyMask_t valor::conv::ktApplyToAllNC       = ktApplyToNCElLike | ktApplyToAllNC1pi | ktApplyToAllNC2pi | ktApplyToNCcoh | ktApplyToNCoth | ktApplyToNCELScat;

const ReacTypeApplyMask_t valor::conv::ktApplyToAllCoh = ktApplyToCCcoh | ktApplyToNCcoh;
const ReacTypeApplyMask_t valor::conv::ktApplyToAllELScat = ktApplyToCCELScat | ktApplyToNuEELScat | ktApplyToNCELScat;

const ReacTypeApplyMask_t valor::conv::ktApplyToAll = ktApplyToAllCC | ktApplyToAllNC | ktApplyToAllELScat;
const ReacTypeApplyMask_t valor::conv::ktApplyToAllButCoh    = ktApplyToAll & (~ktApplyToAllCoh);
const ReacTypeApplyMask_t valor::conv::ktApplyToAllButELScat = ktApplyToAll & (~ktApplyToAllELScat);
const ReacTypeApplyMask_t valor::conv::ktApplyToAllWithFSI   = ktApplyToAll & (~ktApplyToAllCoh) & (~ktApplyToAllELScat);

// Detectors
const DetectorApplyMask_t valor::conv::kdApplyToAllDUNE = kdApplyToDUNEND | kdApplyToDUNEFD;
const DetectorApplyMask_t valor::conv::kdApplyToAllSBN  = kdApplyToSBND | kdApplyToMicroBooNE | kdApplyToICARUS;
const DetectorApplyMask_t valor::conv::kdApplyToAllSBN2Det  = kdApplyToSBND | kdApplyToMicroBooNE;
const DetectorApplyMask_t valor::conv::kdApplyToAllND  = kdApplyToDUNEND | kdApplyToSBND | kdApplyToMicroBooNE | kdApplyToICARUS;
const DetectorApplyMask_t valor::conv::kdApplyToAll    = kdApplyToAllDUNE | kdApplyToAllSBN;


// Samples
const SelecApplyMask_t valor::conv::ksApplyToAllND = (
  ksApplyToNuMuCC | ksApplyToNuMuCC0pi1trk| ksApplyToNuMuCC0pi2trk | ksApplyToNuMuCC0piNtrk | 
  ksApplyToNuMuCC3trkDelta | ksApplyToNuMuCC1piC | ksApplyToNuMuCC2piC | ksApplyToNuMuCC1pi0 | 
  ksApplyToNuMuCC1piC1pi0 | ksApplyToNuMuCCoth | ksApplyToNuMuCCWS0pi | ksApplyToNuMuCCWS1piC | ksApplyToNuMuCCWS1pi0 | 
  ksApplyToNuMuCCWSoth | ksApplyToNuECC0pi | ksApplyToNuECC1piC | ksApplyToNuECC1pi0 | ksApplyToNuECCoth | 
  ksApplyToNC0pi | ksApplyToNC1piC | ksApplyToNC1pi0 | ksApplyToNCoth | ksApplyToNeutrinoElec | ksApplyToInvMuDecay | 
  ksApplyToNuECCWS | ksApplyToNuECC | ksApplyToNuMuCCWS | ksApplyToNC
);

const SelecApplyMask_t valor::conv::ksApplyToAllFD = ksApplyToLowRes | ksApplyToHighRes;
const SelecApplyMask_t valor::conv::ksApplyToAll = ksApplyToAllND | ksApplyToAllFD;
const SelecApplyMask_t valor::conv::ksApplyToAllNC =  ( ksApplyToNC0pi | ksApplyToNC1piC | ksApplyToNC1pi0 | ksApplyToNCoth );
const SelecApplyMask_t valor::conv::ksApplyToAllNuECC =  (ksApplyToNuECC0pi      | ksApplyToNuECC1piC    | ksApplyToNuECC1pi0      | ksApplyToNuECCoth);

// Targets
const NuclearTargetApplyMask_t valor::conv::kntApplyToAll = (
  kntApplyToInclusive | kntApplyToOther | kntApplyToHydrogen | kntApplyToCarbon | kntApplyToOxygen | kntApplyToArgon | kntApplyToCalcium
);

// Which masks apply to which beam modes
// This is defined for all samples in the BeamConf_t enum.
const BeamApplyMask_t valor::conv::kApplyToBeamMode[kNBeamConf] = {
  /* kbLBNF_FHC */ kbApplyToFHC ,
  /* kbLBNF_RHC */ kbApplyToRHC ,
};


// Which masks apply to which samples
// This is defined for all samples in the Sample_t enum.
const SelecApplyMask_t valor::conv::kApplyToSample[kMaxNSamples] = {
  /* ksNuMuCC         */ ksApplyToNuMuCC          ,
  /* ksNuMuCC0pi1trk  */ ksApplyToNuMuCC0pi1trk   ,
  /* ksNuMuCC0pi2trk  */ ksApplyToNuMuCC0pi2trk   ,
  /* ksNuMuCC1piC     */ ksApplyToNuMuCC1piC      ,
  /* ksNuMuCC2piC     */ ksApplyToNuMuCC2piC      ,
  /* ksNuMuCC1pi0     */ ksApplyToNuMuCC1pi0      ,
  /* ksNuMuCC1piC1pi0 */ ksApplyToNuMuCC1piC1pi0  ,
  /* ksNuMuCCoth      */ ksApplyToNuMuCCoth       ,
  /* ksNuECC          */ ksApplyToNuECC           ,
  /* ksNuMuCCWS       */ ksApplyToNuMuCCWS        ,
  /* ksNC             */ ksApplyToNC              ,
  /* ksNuMuCC0piNtrk  */ ksApplyToNuMuCC0piNtrk   ,
  /* ksNuMuCC3trkDelta*/ ksApplyToNuMuCC3trkDelta ,
  /* ksNuMuCCWS0pi    */ ksApplyToNuMuCCWS0pi     ,
  /* ksNuMuCCWS1piC   */ ksApplyToNuMuCCWS1piC    ,
  /* ksNuMuCCWS1pi0   */ ksApplyToNuMuCCWS1pi0    ,
  /* ksNuMuCCWSoth    */ ksApplyToNuMuCCWSoth     ,
  /* ksNuECC0pi       */ ksApplyToNuECC0pi        ,
  /* ksNuECC1piC      */ ksApplyToNuECC1piC       ,
  /* ksNuECC1pi0      */ ksApplyToNuECC1pi0       ,
  /* ksNuECCoth       */ ksApplyToNuECCoth        ,
  /* ksNC0pi          */ ksApplyToNC0pi           ,
  /* ksNC1piC         */ ksApplyToNC1piC          ,
  /* ksNC1pi0         */ ksApplyToNC1pi0          ,
  /* ksNCoth          */ ksApplyToNCoth           ,
  /* ksNeutrinoElec   */ ksApplyToNuECC           , // ksApplyToNeutrinoElec    ,
  /* ksInvMuDecay     */ ksApplyToNuMuCCoth       , // ksApplyToInvMuDecay      ,
  /* ksNuECCWS        */ ksApplyToNuECCWS         ,
  /* ksNuMuLikeCChigh */ ksApplyToHighRes         ,
  /* ksNuMuLikeCClow  */ ksApplyToLowRes          ,
  /* ksNuMuBarCChigh  */ ksApplyToHighRes         ,
  /* ksNuMuBarCClow   */ ksApplyToLowRes          ,
  /* ksNuELikeCChigh  */ ksApplyToHighRes         ,
  /* ksNuELikeCClow   */ ksApplyToLowRes          ,
  /* ksNuEBarCChigh   */ ksApplyToHighRes         ,
  /* ksNuEBarCClow    */ ksApplyToLowRes
};

// Which masks apply to which parent particle flavour
const DetectorApplyMask_t valor::conv::kApplyToDetector[conv::kNDetectorsDefined] = {
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
const FlavApplyMask_t valor::conv::kApplyToFlavour[conv::kNNuFlavour] = {
  /* kNuE     */ kfApplyToNuE     ,
  /* kNuMu    */ kfApplyToNuMu    ,
  /* kNuTau   */ 0                ,
  /* kNuEBar  */ kfApplyToNuEBar  ,
  /* kNuMuBar */ kfApplyToNuMuBar ,
  /* kNuTau   */ 0                ,
};

// Which masks apply to which reaction type
const ReacTypeApplyMask_t valor::conv::kApplyToReacType[conv::kNReacType] = {
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

// Which masks apply to which nucleus
const NuclearTargetApplyMask_t valor::conv::kApplyToNuclearTarget[conv::kNNuclearTarget] = {
  /* kntInclusive */ kntApplyToInclusive ,
  /* kntOther     */ kntApplyToOther     ,
  /* kntHydrogen  */ kntApplyToHydrogen  ,
  /* kntCarbon    */ kntApplyToCarbon    ,
  /* kntOxygen    */ kntApplyToOxygen    ,
  /* kntArgon     */ kntApplyToArgon     ,
  /* kntCalcium   */ kntApplyToCalcium
};

//  TODO: delete this apply mask array when done testing the new setup
const ApplyMask_t valor::conv::kApplyParamToTemplates[kNFitParams] =
  {
    //                               Detector   , Beam Current , True Nu Flavour  , Sample       , Interaction type , nucleus
    // oscillation params
    /* kPhypMixing23         */ { kdApplyToDUNEFD , kbApplyToAll , kfApplyToAll     , ksApplyToAllFD, ktApplyToAllCC , kntApplyToAll} ,
    /* kPhypMixing13         */ { kdApplyToDUNEFD , kbApplyToAll , kfApplyToAll     , ksApplyToAllFD, ktApplyToAllCC , kntApplyToAll} ,
    /* kPhypMixing12         */ { kdApplyToDUNEFD , kbApplyToAll , kfApplyToAll     , ksApplyToAllFD, ktApplyToAllCC , kntApplyToAll} ,
    /* kPhypCPV              */ { kdApplyToDUNEFD , kbApplyToAll , kfApplyToAll     , ksApplyToAllFD, ktApplyToAllCC , kntApplyToAll} ,
    /* kPhypDm23sq           */ { kdApplyToDUNEFD , kbApplyToAll , kfApplyToAll     , ksApplyToAllFD, ktApplyToAllCC , kntApplyToAll} ,
    /* kPhypDm12sq           */ { kdApplyToDUNEFD , kbApplyToAll , kfApplyToAll     , ksApplyToAllFD, ktApplyToAllCC , kntApplyToAll} ,
    // FHC flux
    /* kNuisFHCNuMuFlux00    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuFlux01    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuFlux02    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuFlux03    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuFlux04    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuFlux05    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuFlux06    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuFlux07    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuFlux08    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuFlux09    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuFlux10    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuFlux11    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuFlux12    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuFlux13    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuFlux14    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuFlux15    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuFlux16    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuFlux17    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuFlux18    */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux00 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux01 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux02 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux03 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux04 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux05 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux06 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux07 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux08 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux09 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux10 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux11 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux12 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux13 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux14 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux15 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux16 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux17 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuMuBarFlux18 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuEFlux00     */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuEFlux01     */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuEFlux02     */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuEFlux03     */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuEFlux04     */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuEFlux05     */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuEFlux06     */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuEBarFlux00  */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuEBarFlux01  */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuEBarFlux02  */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuEBarFlux03  */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuEBarFlux04  */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuEBarFlux05  */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisFHCNuEBarFlux06  */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    // RHC flux
    /* kNuisRHCNuMuFlux00    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuFlux01    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuFlux02    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuFlux03    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuFlux04    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuFlux05    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuFlux06    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuFlux07    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuFlux08    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuFlux09    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuFlux10    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuFlux11    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuFlux12    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuFlux13    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuFlux14    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuFlux15    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuFlux16    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuFlux17    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuFlux18    */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux00 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux01 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux02 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux03 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux04 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux05 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux06 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux07 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux08 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux09 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux10 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux11 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux12 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux13 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux14 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux15 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux16 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux17 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuMuBarFlux18 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuEFlux00     */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuEFlux01     */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuEFlux02     */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuEFlux03     */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuEFlux04     */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuEFlux05     */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuEFlux06     */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuEBarFlux00  */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuEBarFlux01  */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuEBarFlux02  */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuEBarFlux03  */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuEBarFlux04  */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuEBarFlux05  */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    /* kNuisRHCNuEBarFlux06  */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll} ,
    //Far detector flux
    //FHC
    /* kNuisFHCNuMuFDFlux00    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuFDFlux01    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuFDFlux02    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuFDFlux03    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuFDFlux04    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuFDFlux05    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuFDFlux06    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuFDFlux07    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuFDFlux08    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuFDFlux09    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuFDFlux10    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuFDFlux11    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuFDFlux12    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuFDFlux13    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuFDFlux14    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuFDFlux15    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuFDFlux16    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuFDFlux17    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuFDFlux18    */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux00 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux01 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux02 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux03 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux04 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux05 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux06 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux07 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux08 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux09 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux10 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux11 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux12 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux13 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux14 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux15 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux16 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux17 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuMuBarFDFlux18 */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuEFDFlux00     */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuEFDFlux01     */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuEFDFlux02     */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuEFDFlux03     */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuEFDFlux04     */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuEFDFlux05     */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuEFDFlux06     */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuEBarFDFlux00  */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuEBarFDFlux01  */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuEBarFDFlux02  */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuEBarFDFlux03  */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuEBarFDFlux04  */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuEBarFDFlux05  */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisFHCNuEBarFDFlux06  */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    // RHC flux
    /* kNuisRHCNuMuFDFlux00    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuFDFlux01    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuFDFlux02    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuFDFlux03    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuFDFlux04    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuFDFlux05    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuFDFlux06    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuFDFlux07    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuFDFlux08    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuFDFlux09    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuFDFlux10    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuFDFlux11    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuFDFlux12    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuFDFlux13    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuFDFlux14    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuFDFlux15    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuFDFlux16    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuFDFlux17    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuFDFlux18    */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMu    , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux00 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux01 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux02 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux03 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux04 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux05 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux06 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux07 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux08 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux09 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux10 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux11 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux12 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux13 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux14 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux15 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux16 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux17 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuMuBarFDFlux18 */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuBar , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuEFDFlux00     */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuEFDFlux01     */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuEFDFlux02     */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuEFDFlux03     */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuEFDFlux04     */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuEFDFlux05     */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuEFDFlux06     */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuE     , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuEBarFDFlux00  */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuEBarFDFlux01  */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuEBarFDFlux02  */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuEBarFDFlux03  */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuEBarFDFlux04  */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuEBarFDFlux05  */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisRHCNuEBarFDFlux06  */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuEBar  , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    // Cross-sections
    /* kNuisIntNuCCQE1               */ { kdApplyToAll , kbApplyToAll , kfApplyToNuAny     , ksApplyToAll , ktApplyToCCQE       , kntApplyToAll } ,
    /* kNuisIntNuCCQE2               */ { kdApplyToAll , kbApplyToAll , kfApplyToNuAny     , ksApplyToAll , ktApplyToCCQE       , kntApplyToAll } ,
    /* kNuisIntNuCCQE3               */ { kdApplyToAll , kbApplyToAll , kfApplyToNuAny     , ksApplyToAll , ktApplyToCCQE       , kntApplyToAll } ,
    /* kNuisIntNuBarCCQE1            */ { kdApplyToAll , kbApplyToAll , kfApplyToNuBarAny  , ksApplyToAll , ktApplyToCCQE       , kntApplyToAll } ,
    /* kNuisIntNuBarCCQE2            */ { kdApplyToAll , kbApplyToAll , kfApplyToNuBarAny  , ksApplyToAll , ktApplyToCCQE       , kntApplyToAll } ,
    /* kNuisIntNuBarCCQE3            */ { kdApplyToAll , kbApplyToAll , kfApplyToNuBarAny  , ksApplyToAll , ktApplyToCCQE       , kntApplyToAll } ,
    /* kNuisIntNuCCMEC               */ { kdApplyToAll , kbApplyToAll , kfApplyToNuAny     , ksApplyToAll , ktApplyToCCMEC      , kntApplyToAll } ,
    /* kNuisIntNuBarCCMEC            */ { kdApplyToAll , kbApplyToAll , kfApplyToNuBarAny  , ksApplyToAll , ktApplyToCCMEC      , kntApplyToAll } ,
    /* kNuisIntNuCC1piz1             */ { kdApplyToAll , kbApplyToAll , kfApplyToNuAny     , ksApplyToAll , ktApplyToCC1pi0     , kntApplyToAll } ,
    /* kNuisIntNuCC1piz2             */ { kdApplyToAll , kbApplyToAll , kfApplyToNuAny     , ksApplyToAll , ktApplyToCC1pi0     , kntApplyToAll } ,
    /* kNuisIntNuCC1piz3             */ { kdApplyToAll , kbApplyToAll , kfApplyToNuAny     , ksApplyToAll , ktApplyToCC1pi0     , kntApplyToAll } ,
    /* kNuisIntNuCC1pic1             */ { kdApplyToAll , kbApplyToAll , kfApplyToNuAny     , ksApplyToAll , ktApplyToCC1piC     , kntApplyToAll } ,
    /* kNuisIntNuCC1pic2             */ { kdApplyToAll , kbApplyToAll , kfApplyToNuAny     , ksApplyToAll , ktApplyToCC1piC     , kntApplyToAll } ,
    /* kNuisIntNuCC1pic3             */ { kdApplyToAll , kbApplyToAll , kfApplyToNuAny     , ksApplyToAll , ktApplyToCC1piC     , kntApplyToAll } ,
    /* kNuisIntNuBarCC1piz1          */ { kdApplyToAll , kbApplyToAll , kfApplyToNuBarAny  , ksApplyToAll , ktApplyToCC1pi0     , kntApplyToAll } ,
    /* kNuisIntNuBarCC1piz2          */ { kdApplyToAll , kbApplyToAll , kfApplyToNuBarAny  , ksApplyToAll , ktApplyToCC1pi0     , kntApplyToAll } ,
    /* kNuisIntNuBarCC1piz3          */ { kdApplyToAll , kbApplyToAll , kfApplyToNuBarAny  , ksApplyToAll , ktApplyToCC1pi0     , kntApplyToAll } ,
    /* kNuisIntNuBarCC1pic1          */ { kdApplyToAll , kbApplyToAll , kfApplyToNuBarAny  , ksApplyToAll , ktApplyToCC1piC     , kntApplyToAll } ,
    /* kNuisIntNuBarCC1pic2          */ { kdApplyToAll , kbApplyToAll , kfApplyToNuBarAny  , ksApplyToAll , ktApplyToCC1piC     , kntApplyToAll } ,
    /* kNuisIntNuBarCC1pic3          */ { kdApplyToAll , kbApplyToAll , kfApplyToNuBarAny  , ksApplyToAll , ktApplyToCC1piC     , kntApplyToAll } ,
    /* kNuisIntNuCC2Pi               */ { kdApplyToAll , kbApplyToAll , kfApplyToNuAny     , ksApplyToAll , ktApplyToAllCC2pi   , kntApplyToAll } ,
    /* kNuisIntNuBarCC2Pi            */ { kdApplyToAll , kbApplyToAll , kfApplyToNuBarAny  , ksApplyToAll , ktApplyToAllCC2pi   , kntApplyToAll } ,
    /* kNuisIntNuDIS1                */ { kdApplyToAll , kbApplyToAll , kfApplyToNuAny     , ksApplyToAll , ktApplyToCCoth      , kntApplyToAll } ,
    /* kNuisIntNuDIS2                */ { kdApplyToAll , kbApplyToAll , kfApplyToNuAny     , ksApplyToAll , ktApplyToCCoth      , kntApplyToAll } ,
    /* kNuisIntNuDIS3                */ { kdApplyToAll , kbApplyToAll , kfApplyToNuAny     , ksApplyToAll , ktApplyToCCoth      , kntApplyToAll } ,
    /* kNuisIntNuBarDIS1             */ { kdApplyToAll , kbApplyToAll , kfApplyToNuBarAny  , ksApplyToAll , ktApplyToCCoth      , kntApplyToAll } ,
    /* kNuisIntNuBarDIS2             */ { kdApplyToAll , kbApplyToAll , kfApplyToNuBarAny  , ksApplyToAll , ktApplyToCCoth      , kntApplyToAll } ,
    /* kNuisIntNuBarDIS3             */ { kdApplyToAll , kbApplyToAll , kfApplyToNuBarAny  , ksApplyToAll , ktApplyToCCoth      , kntApplyToAll } ,
    /* kNuisIntNormNuCoherent        */ { kdApplyToAll , kbApplyToAll , kfApplyToNuAny     , ksApplyToAll , ktApplyToCCcoh      , kntApplyToAll } ,
    /* kNuisIntNormNuBarCoherent     */ { kdApplyToAll , kbApplyToAll , kfApplyToNuBarAny  , ksApplyToAll , ktApplyToCCcoh      , kntApplyToAll } ,
    /* kNuisIntNuNormNC              */ { kdApplyToAll , kbApplyToAll , kfApplyToNuAny     , ksApplyToAll , ktApplyToAllNC      , kntApplyToAll } ,
    /* kNuisIntNuBarNormNC           */ { kdApplyToAll , kbApplyToAll , kfApplyToNuBarAny  , ksApplyToAll , ktApplyToAllNC      , kntApplyToAll } ,
    /* kNuisIntNormNuMuToNuE         */ { kdApplyToAll , kbApplyToAll , kfApplyToNuE       , ksApplyToAll , ktApplyToAll        , kntApplyToAll } ,
    /* kNuisIntNormNuMuBarToNuEBar   */ { kdApplyToAll , kbApplyToAll , kfApplyToNuEBar    , ksApplyToAll , ktApplyToAll        , kntApplyToAll } ,
    /* kNuisIntPiMeanFreePath        */ { kdApplyToAll , kbApplyToAll , kfApplyToAll       , ksApplyToAll , ktApplyToAllWithFSI , kntApplyToAll } ,
    /* kNuisIntNucMeanFreePath       */ { kdApplyToAll , kbApplyToAll , kfApplyToAll       , ksApplyToAll , ktApplyToAllWithFSI , kntApplyToAll } ,
    /* kNuisIntFracPiChargeExchange  */ { kdApplyToAll , kbApplyToAll , kfApplyToAll       , ksApplyToAll , ktApplyToAllWithFSI , kntApplyToAll } ,
    /* kNuisIntFracPiInelastic       */ { kdApplyToAll , kbApplyToAll , kfApplyToAll       , ksApplyToAll , ktApplyToAllWithFSI , kntApplyToAll } ,
    /* kNuisIntFracPiAbsorb          */ { kdApplyToAll , kbApplyToAll , kfApplyToAll       , ksApplyToAll , ktApplyToAllWithFSI , kntApplyToAll } ,
    /* kNuisIntFracPiProduction      */ { kdApplyToAll , kbApplyToAll , kfApplyToAll       , ksApplyToAll , ktApplyToAllWithFSI , kntApplyToAll } ,
    /* kNuisIntFracNucChargeExchange */ { kdApplyToAll , kbApplyToAll , kfApplyToAll       , ksApplyToAll , ktApplyToAllWithFSI , kntApplyToAll } ,
    /* kNuisIntFracNucInelastic      */ { kdApplyToAll , kbApplyToAll , kfApplyToAll       , ksApplyToAll , ktApplyToAllWithFSI , kntApplyToAll } ,
    /* kNuisIntFracNucAbsorb         */ { kdApplyToAll , kbApplyToAll , kfApplyToAll       , ksApplyToAll , ktApplyToAllWithFSI , kntApplyToAll } ,
    /* kNuisIntFracNucProduction     */ { kdApplyToAll , kbApplyToAll , kfApplyToAll       , ksApplyToAll , ktApplyToAllWithFSI , kntApplyToAll } ,
    /* kNuisIntTarget                */ { kdApplyToAll , kbApplyToAll , kfApplyToAll       , ksApplyToAll , ktApplyToAll        , kntApplyToOther} ,
    // Detector systematics
    /* kNuisEffFHCnumuCC0pi1trk01      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi1trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0pi1trk02      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi1trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0pi1trk03      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi1trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0pi1trk04      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi1trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0pi1trk05      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi1trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0pi1trk06      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi1trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0pi1trk07      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi1trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0pi1trk08      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi1trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0pi1trk09      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi1trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0pi2trk01      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0pi2trk02      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0pi2trk03      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0pi2trk04      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0pi2trk05      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0pi2trk06      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0pi2trk07      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0pi2trk08      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0pi2trk09      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0piNtrk01      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0piNtrk02      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0piNtrk03      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0piNtrk04      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0piNtrk05      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0piNtrk06      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0piNtrk07      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0piNtrk08      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0piNtrk09      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0piNtrk10      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0piNtrk11      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0piNtrk12      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0piNtrk13      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0piNtrk14      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC0piNtrk15      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pi3trkDelta01 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pi3trkDelta02 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pi3trkDelta03 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pi3trkDelta04 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pi3trkDelta05 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pi3trkDelta06 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pi3trkDelta07 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pi3trkDelta08 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pi3trkDelta09 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pi3trkDelta10 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pi3trkDelta11 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pi3trkDelta12 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pi3trkDelta13 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pi3trkDelta14 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pi3trkDelta15 */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pic01         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pic02         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pic03         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pic04         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pic05         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pic06         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pic07         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pic08         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pic09         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1piz01         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1piz02         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1piz03         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1piz04         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1piz05         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1piz06         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1piz07         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1piz08         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1piz09         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pic1piz01     */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1piC1pi0, ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pic1piz02     */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1piC1pi0, ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pic1piz03     */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1piC1pi0, ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pic1piz04     */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1piC1pi0, ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pic1piz05     */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1piC1pi0, ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pic1piz06     */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1piC1pi0, ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pic1piz07     */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1piC1pi0, ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pic1piz08     */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1piC1pi0, ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCC1pic1piz09     */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCC1piC1pi0, ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCother01        */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCother02        */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCother03        */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCother04        */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCother05        */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCother06        */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCother07        */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCother08        */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCother09        */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCother10        */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCother11        */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCWS0pi01        */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCWS0pi   , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCWS0pi02        */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCWS0pi   , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCWS0pi03        */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCWS0pi   , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCWS0pi04        */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCWS0pi   , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCWS0pi05        */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCWS0pi   , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCWS1pic01       */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCWS1piC  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCWS1pic02       */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCWS1piC  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCWS1pic03       */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCWS1piC  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCWS1pic04       */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCWS1piC  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCWS1pic05       */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCWS1piC  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCWS1pic06       */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCWS1piC  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCWS1pic07       */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCWS1piC  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCWS1pic08       */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCWS1piC  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCWS1piz01       */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCWS1pi0  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCWS1piz02       */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCWS1pi0  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCWS1piz03       */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCWS1pi0  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnumuCCWSother01      */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuMuCCWSoth   , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC0pi01           */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC0pi      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC0pi02           */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC0pi      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC0pi03           */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC0pi      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC0pi04           */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC0pi      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC0pi05           */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC0pi      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC0pi06           */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC0pi      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC0pi07           */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC0pi      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC0pi08           */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC0pi      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC0pi09           */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC0pi      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC1pic01          */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC1pic02          */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC1pic03          */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC1pic04          */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC1pic05          */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC1pic06          */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC1pic07          */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC1pic08          */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC1pic09          */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC1piz01          */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC1piz02          */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC1piz03          */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC1piz04          */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC1piz05          */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC1piz06          */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC1piz07          */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC1piz08          */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCC1piz09          */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCCother01         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCCother02         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCCother03         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCCother04         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCCother05         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCCother06         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCCother07         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCCother08         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCCother09         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCCother10         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCCother11         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCCWS01            */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECCWS       , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCnueCCWS02            */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNuECCWS       , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCNC0pi01              */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNC0pi         , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCNC0pi02              */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNC0pi         , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCNC0pi03              */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNC0pi         , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCNC1pic01             */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNC1piC        , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCNC1pic02             */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNC1piC        , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCNC1pic03             */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNC1piC        , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCNC1piz01             */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNC1pi0        , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCNC1piz02             */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNC1pi0        , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCNC1piz03             */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNC1pi0        , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCNCother01            */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNCoth         , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCNCother02            */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNCoth         , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCNCother03            */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNCoth         , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCNeutrinoElec         */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToNeutrinoElec  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFHCIMD                  */ { kdApplyToDUNEND , kbApplyToFHC , kfApplyToAll , ksApplyToInvMuDecay    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0pi1trk01      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi1trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0pi1trk02      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi1trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0pi1trk03      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi1trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0pi1trk04      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi1trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0pi1trk05      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi1trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0pi1trk06      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi1trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0pi1trk07      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi1trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0pi1trk08      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi1trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0pi1trk09      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi1trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0pi2trk01      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0pi2trk02      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0pi2trk03      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0pi2trk04      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0pi2trk05      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0pi2trk06      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0pi2trk07      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0pi2trk08      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0pi2trk09      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0piNtrk01      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0piNtrk02      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0piNtrk03      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0piNtrk04      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0piNtrk05      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0piNtrk06      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0piNtrk07      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0piNtrk08      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0piNtrk09      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0piNtrk10      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0piNtrk11      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0piNtrk12      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0piNtrk13      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0piNtrk14      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC0piNtrk15      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0pi2trk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pi3trkDelta01 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pi3trkDelta02 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pi3trkDelta03 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pi3trkDelta04 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pi3trkDelta05 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pi3trkDelta06 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pi3trkDelta07 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pi3trkDelta08 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pi3trkDelta09 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pi3trkDelta10 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pi3trkDelta11 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pi3trkDelta12 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pi3trkDelta13 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pi3trkDelta14 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pi3trkDelta15 */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC0piNtrk , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pic01         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pic02         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pic03         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pic04         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pic05         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pic06         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pic07         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pic08         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pic09         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1piz01         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1piz02         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1piz03         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1piz04         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1piz05         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1piz06         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1piz07         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1piz08         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1piz09         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1pi0    , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pic1piz01     */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1piC1pi0, ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pic1piz02     */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1piC1pi0, ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pic1piz03     */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1piC1pi0, ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pic1piz04     */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1piC1pi0, ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pic1piz05     */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1piC1pi0, ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pic1piz06     */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1piC1pi0, ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pic1piz07     */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1piC1pi0, ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pic1piz08     */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1piC1pi0, ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCC1pic1piz09     */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCC1piC1pi0, ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCother01        */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCother02        */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCother03        */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCother04        */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCother05        */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCother06        */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCother07        */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCother08        */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCother09        */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCother10        */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCother11        */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCoth     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCWS0pi01        */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCWS0pi   , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCWS0pi02        */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCWS0pi   , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCWS0pi03        */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCWS0pi   , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCWS0pi04        */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCWS0pi   , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCWS0pi05        */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCWS0pi   , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCWS1pic01       */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCWS1piC  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCWS1pic02       */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCWS1piC  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCWS1pic03       */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCWS1piC  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCWS1pic04       */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCWS1piC  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCWS1pic05       */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCWS1piC  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCWS1pic06       */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCWS1piC  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCWS1pic07       */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCWS1piC  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCWS1pic08       */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCWS1piC  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCWS1piz01       */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCWS1pi0  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCWS1piz02       */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCWS1pi0  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCWS1piz03       */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCWS1pi0  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnumuCCWSother01      */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuMuCCWSoth   , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC0pi01           */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC0pi      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC0pi02           */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC0pi      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC0pi03           */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC0pi      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC0pi04           */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC0pi      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC0pi05           */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC0pi      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC0pi06           */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC0pi      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC0pi07           */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC0pi      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC0pi08           */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC0pi      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC0pi09           */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC0pi      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC1pic01          */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC1pic02          */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC1pic03          */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC1pic04          */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC1pic05          */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC1pic06          */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC1pic07          */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC1pic08          */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC1pic09          */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC1piz01          */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC1piz02          */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC1piz03          */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC1piz04          */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC1piz05          */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC1piz06          */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC1piz07          */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC1piz08          */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCC1piz09          */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCCother01         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCCother02         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCCother03         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCCother04         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCCother05         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCCother06         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCCother07         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCCother08         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCCother09         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCCother10         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCCother11         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCCWS01            */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECCWS       , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCnueCCWS02            */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNuECCWS       , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCNC0pi01              */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNC0pi         , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCNC0pi02              */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNC0pi         , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCNC0pi03              */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNC0pi         , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCNC1pic01             */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNC1piC        , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCNC1pic02             */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNC1piC        , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCNC1pic03             */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNC1piC        , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCNC1piz01             */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNC1pi0        , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCNC1piz02             */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNC1pi0        , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCNC1piz03             */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNC1pi0        , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCNCother01            */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNCoth         , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCNCother02            */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNCoth         , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCNCother03            */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNCoth         , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCNeutrinoElec         */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToNeutrinoElec  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffRHCIMD                  */ { kdApplyToDUNEND , kbApplyToRHC , kfApplyToAll , ksApplyToInvMuDecay    , ktApplyToAll , kntApplyToAll } ,
    // Far detector systematics
    /* kNuisEffFDNuMuCCHigh     */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuMuAny     , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFDNuMuCCLow      */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuMuAny     , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFDNuECCHigh      */ { kdApplyToDUNEFD , kbApplyToFHC , kfApplyToNuEAny      , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffFDNuECCLow       */ { kdApplyToDUNEFD , kbApplyToRHC , kfApplyToNuEAny      , ksApplyToAll , ktApplyToAll , kntApplyToAll } ,
    // Old det
    /* kNuisEffNuMuCC0pi1trk */ { kdApplyToAllND , kbApplyToAll , kfApplyToAll , ksApplyToNuMuCC0pi1trk  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffNuMuCC0pi2trk */ { kdApplyToAllND , kbApplyToAll , kfApplyToAll , ksApplyToNuMuCC0pi2trk  , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffNuMuCC1piC    */ { kdApplyToAllND , kbApplyToAll , kfApplyToAll , ksApplyToNuMuCC1piC     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffNuMuCC1pi0    */ { kdApplyToAllND , kbApplyToAll , kfApplyToAll , ksApplyToNuMuCC1pi0     , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffNuMuCC1piC1pi0*/ { kdApplyToAllND , kbApplyToAll , kfApplyToAll , ksApplyToNuMuCC1piC1pi0 , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffNuMuCCoth     */ { kdApplyToAllND , kbApplyToAll , kfApplyToAll , ksApplyToNuMuCCoth      , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffNuECC         */ { kdApplyToAllND , kbApplyToAll , kfApplyToAll , ksApplyToAllNuECC       , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffNuMuCCWS      */ { kdApplyToAllND , kbApplyToAll , kfApplyToAll , ksApplyToNuMuCCWS       , ktApplyToAll , kntApplyToAll } ,
    /* kNuisEffNC            */ { kdApplyToAllND , kbApplyToAll , kfApplyToAll , ksApplyToAllNC          , ktApplyToAll , kntApplyToAll }
  };



//________________________________________________________________________________________
valor::util::ApplyMaskNaming * valor::util::ApplyMaskNaming::fInstance = 0;
//________________________________________________________________________________________
valor::util::ApplyMaskNaming::ApplyMaskNaming()
{
  this->Init();
  fInstance = 0;
}
//________________________________________________________________________________________
const valor::util::ApplyMaskNaming * valor::util::ApplyMaskNaming::Instance()
{
  return MutableInstance();
}
//________________________________________________________________________________________
valor::util::ApplyMaskNaming * valor::util::ApplyMaskNaming::MutableInstance()
{
  if(fInstance == 0) {
    static valor::util::ApplyMaskNaming::Cleaner cleaner;
    cleaner.DummyMethodAndSilentCompiler();
    fInstance = new valor::util::ApplyMaskNaming;
  }
  return fInstance;
}
//________________________________________________________________________________________
void valor::util::ApplyMaskNaming::Init(void)
{
  // Beam Mask names
  fBeamMaskToName.insert( std::make_pair(kbApplyToFHC, "fhc") );
  fBeamMaskToName.insert( std::make_pair(kbApplyToRHC, "rhc") );
  fBeamMaskToName.insert( std::make_pair(kbApplyToAll, "all") );
  for(auto const& pair : fBeamMaskToName) {
    fBeamNameToMask.insert( std::make_pair(pair.second, pair.first) );
  }

  // Flavour mask names
  fFlavMaskToName.insert( std::make_pair(kfApplyToNuMu    , "numu") );
  fFlavMaskToName.insert( std::make_pair(kfApplyToNuMuBar , "numubar") );
  fFlavMaskToName.insert( std::make_pair(kfApplyToNuE     , "nue") );
  fFlavMaskToName.insert( std::make_pair(kfApplyToNuEBar  , "nuebar") );
  fFlavMaskToName.insert( std::make_pair(kfApplyToNuAny   , "nuany") );
  fFlavMaskToName.insert( std::make_pair(kfApplyToNuBarAny, "nubarany") );
  fFlavMaskToName.insert( std::make_pair(kfApplyToNuEAny  , "nueany") );
  fFlavMaskToName.insert( std::make_pair(kfApplyToNuMuAny , "numuany") );
  fFlavMaskToName.insert( std::make_pair(kfApplyToAll     , "all") );
  for(auto const& pair : fFlavMaskToName) {
    fFlavNameToMask.insert( std::make_pair(pair.second, pair.first) );
  }

  // Selection mask names
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuMuCC         , "numucc") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuMuCC0pi1trk  , "numucc0pi1trk") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuMuCC0pi2trk  , "numucc0pi2trk") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuMuCC0piNtrk  , "numucc0pintrk") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuMuCC3trkDelta, "numucc3trkdelta") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuMuCC1piC     , "numucc1pic") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuMuCC2piC     , "numucc2pic") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuMuCC1pi0     , "numucc1pi0") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuMuCC1piC1pi0 , "numucc1pic1pi0") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuMuCCoth      , "numuccoth") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuMuCCWS0pi    , "numuccws0pi") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuMuCCWS1piC   , "numuccws1pic") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuMuCCWS1pi0   , "numuccws1pi0") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuMuCCWSoth    , "numuccwsoth") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuECC0pi       , "nuecc0pi") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuECC1piC      , "nuecc1pic") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuECC1pi0      , "nuecc1pi0") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuECCoth       , "nueccoth") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNC0pi          , "nc0pi") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNC1piC         , "nc1pic") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNC1pi0         , "nc1pi0") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNCoth          , "ncoth") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNeutrinoElec   , "neutrinoelec") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToInvMuDecay     , "invmudecay") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuECCWS        , "nueccws") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuECC          , "nuecc") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNuMuCCWS       , "numuccws") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToNC             , "nc") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToHighRes        , "highres") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToLowRes         , "lowres") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToAllND          , "allnd") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToAllFD          , "allfd") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToAll            , "all") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToAllNC          , "allnc") );
  fSelecMaskToName.insert( std::make_pair(ksApplyToAllNuECC       , "allnuecc") );
  for(auto const& pair : fSelecMaskToName) {
    fSelecNameToMask.insert( std::make_pair(pair.second, pair.first) );
  }

  // Reaction type mask names
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToCCQE        , "ccqe") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToCCMEC       , "ccmec") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToCC1piC      , "cc1pic") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToCC1pi0      , "cc1pi0") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToCC2piC      , "cc2pic") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToCC2pi0      , "cc2pi0") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToCCpiCpi0    , "ccpicpi0") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToCCcoh       , "cccoh") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToCCELScat    , "ccelscat") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToCCoth       , "ccoth") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToNCEL        , "ncel") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToNCMEC       , "ncmec") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToNC1piC      , "nc1pic") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToNC1pi0      , "nc1pi0") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToNC2piC      , "nc2pic") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToNC2pi0      , "nc2pi0") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToNCpiCpi0    , "ncpicpi0") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToNCcoh       , "nccoh") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToNCELScat    , "ncelscat") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToNCoth       , "ncoth") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToNuEELScat   , "nueelscat") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToCCQELike    , "ccqelike") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToAllCCELScat , "allccelscat") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToAllCC1pi    , "allcc1pi") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToAllCC2pi    , "allcc2pi") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToAllCC       , "allcc") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToNCElLike    , "ncellike") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToAllNCELScat , "allncelscat") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToAllNC1pi    , "allnc1pi") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToAllNC2pi    , "allnc2pi") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToAllNC       , "allnc") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToAllCoh      , "allcoh") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToAllELScat   , "allelscat") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToAll         , "all") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToAllButCoh   , "allbutcoh") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToAllButELScat, "allbutelscat") );
  fReacTypeMaskToName.insert( std::make_pair(ktApplyToAllWithFSI  , "allwithfsi") );
  for(auto const& pair : fReacTypeMaskToName) {
    fReacTypeNameToMask.insert( std::make_pair(pair.second, pair.first) );
  }

  // Detector mask names
  fDetectorMaskToName.insert( std::make_pair(kdApplyToDUNEND    , "dunend") );
  fDetectorMaskToName.insert( std::make_pair(kdApplyToDUNEFD    , "dunefd") );
  fDetectorMaskToName.insert( std::make_pair(kdApplyToSBND      , "sbnd") );
  fDetectorMaskToName.insert( std::make_pair(kdApplyToMicroBooNE, "microboone") );
  fDetectorMaskToName.insert( std::make_pair(kdApplyToICARUS    , "icarus") );
  fDetectorMaskToName.insert( std::make_pair(kdApplyToAllDUNE   , "alldune") );
  fDetectorMaskToName.insert( std::make_pair(kdApplyToAllSBN    , "allsbn") );
  fDetectorMaskToName.insert( std::make_pair(kdApplyToAllSBN2Det, "allsbn2det") );
  fDetectorMaskToName.insert( std::make_pair(kdApplyToAllND     , "allnd") );
  fDetectorMaskToName.insert( std::make_pair(kdApplyToAll       , "all") );
  for(auto const& pair : fDetectorMaskToName) {
    fDetectorNameToMask.insert( std::make_pair(pair.second, pair.first) );
  }

  // Nuclear target mask names
  fNuclearTargetMaskToName.insert( std::make_pair(kntApplyToInclusive, "inclusive") );
  fNuclearTargetMaskToName.insert( std::make_pair(kntApplyToOther    , "other") );
  fNuclearTargetMaskToName.insert( std::make_pair(kntApplyToHydrogen , "hydrogen") );
  fNuclearTargetMaskToName.insert( std::make_pair(kntApplyToCarbon   , "carbon") );
  fNuclearTargetMaskToName.insert( std::make_pair(kntApplyToOxygen   , "oxygen") );
  fNuclearTargetMaskToName.insert( std::make_pair(kntApplyToArgon    , "argon") );
  fNuclearTargetMaskToName.insert( std::make_pair(kntApplyToCalcium  , "calcium") );
  fNuclearTargetMaskToName.insert( std::make_pair(kntApplyToAll      , "all") );
  for(auto const& pair : fNuclearTargetMaskToName) {
    fNuclearTargetNameToMask.insert( std::make_pair(pair.second, pair.first) );
  }
}
//________________________________________________________________________________________