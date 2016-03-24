//____________________________________________________________________________
/*!

\class     valor::conv::ReacMode_t

\brief     Enumeration of true reaction modes considered separately within 
           each DUNE analysis sample

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory
          
\created   April 15, 2014

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_reaction_modes_h
#define _valor_dune_reaction_modes_h

#include <string>

//FWMK
#include "Conventions/NuFlavour.h"

namespace valor {
namespace conv {

static const int kNReacModes = 52;  

typedef enum EReacMode 
{
   kmUndefined = -1, 
   kmNuMuCCQE,            // numu    CC QE
   kmNuMuCCMEC,           // numu    CC MEC
   kmNuMuCC1piC,          // numu    CC 1 pi+/-
   kmNuMuCC1pi0,          // numu    CC 1 pi0
   kmNuMuCC2piC,          // numu    CC 2 pi+/-
   kmNuMuCC2pi0,          // numu    CC 2 pi0
   kmNuMuCCpiCpi0,        // numu    CC 1 pi0 + 1 pi+/-
   kmNuMuCCcoh,           // numu    CC coherent
   kmNuMuCCoth,           // numu    CC other
//   kmNuMuNCEL,            // numu    NC EL
//   kmNuMuNCMEC,           // numu    NC MEC
   kmNuMuNC1piC,          // numu    NC 1 pi+/-
   kmNuMuNC1pi0,          // numu    NC 1 pi0
//   kmNuMuNC2piC,          // numu    NC 2 pi+/-
//   kmNuMuNC2pi0,          // numu    NC 2 pi0
//   kmNuMuNCpiCpi0,        // numu    NC 1 pi0 + 1 pi+/-
   kmNuMuNCcoh,           // numu    NC coherent
   kmNuMuNCoth,           // numu    NC other
   kmNuMuBarCCQE,         // numubar CC QE
   kmNuMuBarCCMEC,        // numubar CC MEC
   kmNuMuBarCC1piC,       // numubar CC 1 pi+/-
   kmNuMuBarCC1pi0,       // numubar CC 1 pi0
   kmNuMuBarCC2piC,       // numubar CC 2 pi+/-
   kmNuMuBarCC2pi0,       // numubar CC 2 pi0
   kmNuMuBarCCpiCpi0,     // numubar CC 1 pi0 + 1 pi+/-
   kmNuMuBarCCcoh,        // numubar CC coherent
   kmNuMuBarCCoth,        // numubar CC other
//   kmNuMuBarNCEL,         // numubar NC EL
//   kmNuMuBarNCMEC,        // numubar NC MEC
   kmNuMuBarNC1piC,       // numubar NC 1 pi+/-
   kmNuMuBarNC1pi0,       // numubar NC 1 pi0
//   kmNuMuBarNC2piC,       // numubar NC 2 pi+/-
//   kmNuMuBarNC2pi0,       // numubar NC 2 pi0
//   kmNuMuBarNCpiCpi0,     // numubar NC 1 pi0 + 1 pi+/-
   kmNuMuBarNCcoh,        // numubar NC coherent
   kmNuMuBarNCoth,        // numubar NC other
   kmNuECCQE,             // nue     CC QE
   kmNuECCMEC,            // nue     CC MEC
   kmNuECC1piC,           // nue     CC 1 pi+/-
   kmNuECC1pi0,           // nue     CC 1 pi0
   kmNuECC2piC,           // nue     CC 2 pi+/-
   kmNuECC2pi0,           // nue     CC 2 pi0
   kmNuECCpiCpi0,         // nue     CC 1 pi0 + 1 pi+/-
   kmNuECCcoh,            // nue     CC coherent
   kmNuECCoth,            // nue     CC other
//   kmNuENCEL,             // nue     NC EL
//   kmNuENCMEC,            // nue     NC MEC
   kmNuENC1piC,           // nue     NC 1 pi+/-
   kmNuENC1pi0,           // nue     NC 1 pi0
//   kmNuENC2piC,           // nue     NC 2 pi+/-
//   kmNuENC2pi0,           // nue     NC 2 pi0
//   kmNuENCpiCpi0,         // nue     NC 1 pi0 + 1 pi+/-
   kmNuENCcoh,            // nue     NC coherent
   kmNuENCoth,            // nue     NC other
   kmNuEBarCCQE,          // nuebar  CC QE
   kmNuEBarCCMEC,         // nuebar  CC MEC
   kmNuEBarCC1piC,        // nuebar  CC 1 pi+/-
   kmNuEBarCC1pi0,        // nuebar  CC 1 pi0
   kmNuEBarCC2piC,        // nuebar  CC 2 pi+/-
   kmNuEBarCC2pi0,        // nuebar  CC 2 pi0
   kmNuEBarCCpiCpi0,      // nuebar  CC 1 pi0 + 1 pi+/-
   kmNuEBarCCcoh,         // nuebar  CC coherent
   kmNuEBarCCoth,         // nuebar  CC other
//   kmNuEBarNCEL,          // nuebar  NC EL
//   kmNuEBarNCMEC,         // nuebar  NC MEC
   kmNuEBarNC1piC,        // nuebar  NC 1 pi+/-
   kmNuEBarNC1pi0,        // nuebar  NC 1 pi0
//   kmNuEBarNC2piC,        // nuebar  NC 2 pi+/-
//   kmNuEBarNC2pi0,        // nuebar  NC 2 pi0
//   kmNuEBarNCpiCpi0,      // nuebar  NC 1 pi0 + 1 pi+/-
   kmNuEBarNCcoh,         // nuebar  NC coherent
   kmNuEBarNCoth,         // nuebar  NC other
   kmOther                // other, eg contributions from interactions outside the fiducial etc
} 
ReacMode_t; 

// Same as above but not broken down by nu flavour
typedef enum EReacType
{
  kmtUndefined = -1,
  kmtCCQE,        // CC QE
  kmtCCMEC,       // CC MEC
  kmtCC1piC,      // CC 1 pi+/-
  kmtCC1pi0,      // CC 1 pi0
  kmtCC2piC,      // CC 2 pi+/-
  kmtCC2pi0,      // CC 2 pi0
  kmtCCpiCpi0,    // CC 1 pi0 + 1 pi+/-
  kmtCCcoh,       // CC coherent
  kmtCCoth,       // CC other
  kmtNCEL,        // NC EL
  kmtNCMEC,       // NC MEC
  kmtNC1piC,      // NC 1 pi+/-
  kmtNC1pi0,      // NC 1 pi0
  kmtNC2piC,      // NC 2 pi+/-
  kmtNC2pi0,      // NC 2 pi0
  kmtNCpiCpi0,    // NC 1 pi0 + 1 pi+/-
  kmtNCcoh,       // NC coherent
  kmtNCoth,       // NC other
//kmtOther        // misc
}
ReacType_t;

static const int kNReacType = 19;

// Map the reaction modes to their type
static const ReacType_t kReacModeToType[kNReacModes] =
{
   /*   kmNuMuCCQE          */ kmtCCQE     ,
   /*   kmNuMuCCMEC         */ kmtCCMEC    ,
   /*   kmNuMuCC1piC        */ kmtCC1piC   ,
   /*   kmNuMuCC1pi0        */ kmtCC1pi0   ,
   /*   kmNuMuCC2piC        */ kmtCC2piC   ,
   /*   kmNuMuCC2pi0        */ kmtCC2pi0   ,
   /*   kmNuMuCCpiCpi0      */ kmtCCpiCpi0 ,
   /*   kmNuMuCCcoh         */ kmtCCcoh    ,
   /*   kmNuMuCCoth         */ kmtCCoth    ,
// /*   kmNuMuNCEL          */ kmtNCEL     ,
// /*   kmNuMuNCMEC         */ kmtNCMEC    ,
   /*   kmNuMuNC1piC        */ kmtNC1piC   ,
   /*   kmNuMuNC1pi0        */ kmtNC1pi0   ,
// /*   kmNuMuNC2piC        */ kmtNC2piC   ,
// /*   kmNuMuNC2pi0        */ kmtNC2pi0   ,
// /*   kmNuMuNCpiCpi0      */ kmtNCpiCpi0 ,
   /*   kmNuMuNCcoh         */ kmtNCcoh    ,
   /*   kmNuMuNCoth         */ kmtNCoth    ,
   /*   kmNuMuBarCCQE       */ kmtCCQE     ,
   /*   kmNuMuBarCCMEC      */ kmtCCMEC    ,
   /*   kmNuMuBarCC1piC     */ kmtCC1piC   ,
   /*   kmNuMuBarCC1pi0     */ kmtCC1pi0   ,
   /*   kmNuMuBarCC2piC     */ kmtCC2piC   ,
   /*   kmNuMuBarCC2pi0     */ kmtCC2pi0   ,
   /*   kmNuMuBarCCpiCpi0   */ kmtCCpiCpi0 ,
   /*   kmNuMuBarCCcoh      */ kmtCCcoh    ,
   /*   kmNuMuBarCCoth      */ kmtCCoth    ,
// /*   kmNuMuBarNCEL       */ kmtNCEL     ,
// /*   kmNuMuBarNCMEC      */ kmtNCMEC    ,
   /*   kmNuMuBarNC1piC     */ kmtNC1piC   ,
   /*   kmNuMuBarNC1pi0     */ kmtNC1pi0   ,
// /*   kmNuMuBarNC2piC     */ kmtNC2piC   ,
// /*   kmNuMuBarNC2pi0     */ kmtNC2pi0   ,
// /*   kmNuMuBarNCpiCpi0   */ kmtNCpiCpi0 ,
   /*   kmNuMuBarNCcoh      */ kmtNCcoh    ,
   /*   kmNuMuBarNCoth      */ kmtNCoth    ,
   /*   kmNuECCQE           */ kmtCCQE     , 
   /*   kmNuECCMEC          */ kmtCCMEC    , 
   /*   kmNuECC1piC         */ kmtCC1piC   , 
   /*   kmNuECC1pi0         */ kmtCC1pi0   , 
   /*   kmNuECC2piC         */ kmtCC2piC   , 
   /*   kmNuECC2pi0         */ kmtCC2pi0   , 
   /*   kmNuECCpiCpi0       */ kmtCCpiCpi0 , 
   /*   kmNuECCcoh          */ kmtCCcoh    , 
   /*   kmNuECCoth          */ kmtCCoth    , 
// /*   kmNuENCEL           */ kmtNCEL     , 
// /*   kmNuENCMEC          */ kmtNCMEC    , 
   /*   kmNuENC1piC         */ kmtNC1piC   , 
   /*   kmNuENC1pi0         */ kmtNC1pi0   , 
// /*   kmNuENC2piC         */ kmtNC2piC   , 
// /*   kmNuENC2pi0         */ kmtNC2pi0   , 
// /*   kmNuENCpiCpi0       */ kmtNCpiCpi0 , 
   /*   kmNuENCcoh          */ kmtNCcoh    , 
   /*   kmNuENCoth          */ kmtNCoth    , 
   /*   kmNuEBarCCQE        */ kmtCCQE     , 
   /*   kmNuEBarCCMEC       */ kmtCCMEC    , 
   /*   kmNuEBarCC1piC      */ kmtCC1piC   , 
   /*   kmNuEBarCC1pi0      */ kmtCC1pi0   , 
   /*   kmNuEBarCC2piC      */ kmtCC2piC   , 
   /*   kmNuEBarCC2pi0      */ kmtCC2pi0   , 
   /*   kmNuEBarCCpiCpi0    */ kmtCCpiCpi0 , 
   /*   kmNuEBarCCcoh       */ kmtCCcoh    , 
   /*   kmNuEBarCCoth       */ kmtCCoth    , 
// /*   kmNuEBarNCEL        */ kmtNCEL     , 
// /*   kmNuEBarNCMEC       */ kmtNCMEC    , 
   /*   kmNuEBarNC1piC      */ kmtNC1piC   , 
   /*   kmNuEBarNC1pi0      */ kmtNC1pi0   , 
// /*   kmNuEBarNC2piC      */ kmtNC2piC   , 
// /*   kmNuEBarNC2pi0      */ kmtNC2pi0   , 
// /*   kmNuEBarNCpiCpi0    */ kmtNCpiCpi0 , 
   /*   kmNuEBarNCcoh       */ kmtNCcoh    , 
   /*   kmNuEBarNCoth       */ kmtNCoth    , 
// /*   kmOther             */ kmtOther 
};

// Map the reaction modes to their neutrino flavour
static const NuFlavour_t kReacModeToFlavour[kNReacModes] =
{
   /*   kmNuMuCCQE          */ kNuMu    ,
   /*   kmNuMuCCMEC         */ kNuMu    ,
   /*   kmNuMuCC1piC        */ kNuMu    ,
   /*   kmNuMuCC1pi0        */ kNuMu    ,
   /*   kmNuMuCC2piC        */ kNuMu    ,
   /*   kmNuMuCC2pi0        */ kNuMu    ,
   /*   kmNuMuCCpiCpi0      */ kNuMu    ,
   /*   kmNuMuCCcoh         */ kNuMu    ,
   /*   kmNuMuCCoth         */ kNuMu    ,
// /*   kmNuMuNCEL          */ kNuMu    ,
// /*   kmNuMuNCMEC         */ kNuMu    ,
   /*   kmNuMuNC1piC        */ kNuMu    ,
   /*   kmNuMuNC1pi0        */ kNuMu    ,
// /*   kmNuMuNC2piC        */ kNuMu    ,
// /*   kmNuMuNC2pi0        */ kNuMu    ,
// /*   kmNuMuNCpiCpi0      */ kNuMu    ,
   /*   kmNuMuNCcoh         */ kNuMu    ,
   /*   kmNuMuNCoth         */ kNuMu    ,
   /*   kmNuMuBarCCQE       */ kNuMuBar ,
   /*   kmNuMuBarCCMEC      */ kNuMuBar ,
   /*   kmNuMuBarCC1piC     */ kNuMuBar ,
   /*   kmNuMuBarCC1pi0     */ kNuMuBar ,
   /*   kmNuMuBarCC2piC     */ kNuMuBar ,
   /*   kmNuMuBarCC2pi0     */ kNuMuBar ,
   /*   kmNuMuBarCCpiCpi0   */ kNuMuBar ,
   /*   kmNuMuBarCCcoh      */ kNuMuBar ,
   /*   kmNuMuBarCCoth      */ kNuMuBar ,
// /*   kmNuMuBarNCEL       */ kNuMuBar ,
// /*   kmNuMuBarNCMEC      */ kNuMuBar ,
   /*   kmNuMuBarNC1piC     */ kNuMuBar ,
   /*   kmNuMuBarNC1pi0     */ kNuMuBar ,
// /*   kmNuMuBarNC2piC     */ kNuMuBar ,
// /*   kmNuMuBarNC2pi0     */ kNuMuBar ,
// /*   kmNuMuBarNCpiCpi0   */ kNuMuBar ,
   /*   kmNuMuBarNCcoh      */ kNuMuBar ,
   /*   kmNuMuBarNCoth      */ kNuMuBar ,
   /*   kmNuECCQE           */ kNuE     , 
   /*   kmNuECCMEC          */ kNuE     , 
   /*   kmNuECC1piC         */ kNuE     , 
   /*   kmNuECC1pi0         */ kNuE     , 
   /*   kmNuECC2piC         */ kNuE     , 
   /*   kmNuECC2pi0         */ kNuE     , 
   /*   kmNuECCpiCpi0       */ kNuE     , 
   /*   kmNuECCcoh          */ kNuE     , 
   /*   kmNuECCoth          */ kNuE     , 
// /*   kmNuENCEL           */ kNuE     , 
// /*   kmNuENCMEC          */ kNuE     , 
   /*   kmNuENC1piC         */ kNuE     , 
   /*   kmNuENC1pi0         */ kNuE     , 
// /*   kmNuENC2piC         */ kNuE     , 
// /*   kmNuENC2pi0         */ kNuE     , 
// /*   kmNuENCpiCpi0       */ kNuE     , 
   /*   kmNuENCcoh          */ kNuE     , 
   /*   kmNuENCoth          */ kNuE     , 
   /*   kmNuEBarCCQE        */ kNuEBar  , 
   /*   kmNuEBarCCMEC       */ kNuEBar  , 
   /*   kmNuEBarCC1piC      */ kNuEBar  , 
   /*   kmNuEBarCC1pi0      */ kNuEBar  , 
   /*   kmNuEBarCC2piC      */ kNuEBar  , 
   /*   kmNuEBarCC2pi0      */ kNuEBar  , 
   /*   kmNuEBarCCpiCpi0    */ kNuEBar  , 
   /*   kmNuEBarCCcoh       */ kNuEBar  , 
   /*   kmNuEBarCCoth       */ kNuEBar  , 
// /*   kmNuEBarNCEL        */ kNuEBar  , 
// /*   kmNuEBarNCMEC       */ kNuEBar  , 
   /*   kmNuEBarNC1piC      */ kNuEBar  , 
   /*   kmNuEBarNC1pi0      */ kNuEBar  , 
// /*   kmNuEBarNC2piC      */ kNuEBar  , 
// /*   kmNuEBarNC2pi0      */ kNuEBar  , 
// /*   kmNuEBarNCpiCpi0    */ kNuEBar  , 
   /*   kmNuEBarNCcoh       */ kNuEBar  , 
   /*   kmNuEBarNCoth       */ kNuEBar  , 
// /*   kmOther             */ kNuFlavourUndefined
};

} // conv


//
// Associated utilities
//
namespace util {

  std::string      AsString        (conv::ReacMode_t m);
  std::string      AsStringTeX     (conv::ReacMode_t m, bool root = false);
  conv::ReacMode_t ReacModeFromInt (int m);
  
  // Aliases for above
  std::string      ModeAsString        (conv::ReacMode_t m);
  std::string      ModeAsStringTeX     (conv::ReacMode_t m, bool root = false);

} // util

} // valor
  
#endif 

