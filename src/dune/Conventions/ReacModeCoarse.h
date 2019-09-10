//____________________________________________________________________________
/*!

\class     valor::conv::ReacModeCoarse_t

\brief     Enumeration of coarse true reaction modes.
           Not a systematic characterization and not mutually exlusive.
           These codes are used only in plots.
           One or more ReacMode_t types are mapped into a ReacModeCoarse_t.

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory
          
\created   April 15, 2014

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_coarse_reaction_modes_h
#define _valor_dune_coarse_reaction_modes_h

#include <string>
#include "valor/Conventions/ReacMode.h"

using std::string;

namespace valor {
namespace conv {

typedef enum EReacModeCoarse
{
   kmcUndefined = -1, 
   kmcNuMuCC,             // numu     CC all
   kmcNuMuCCQEMEC,        // numu     CC QE+MEC
   kmcNuMuCCQE,           // numu     CC QE
   kmcNuMuCCMEC,          // numu     CC MEC
   kmcNuMuCC1piC,         // numu     CC 1 pipm
   kmcNuMuCC1pi0,         // numu     CC 1 pi0
   kmcNuMuCC1pi,          // numu     CC 1 pi any
   kmcNuMuCC2pi,          // numu     CC 2 pi
   kmcNuMuCCIMD,          // numu     IMD
   kmcNuMuCCElScat,       // numu     elastic
   kmcNuMuCCoth,          // numu     CC other
   kmcNuMuBarCC,          // numubar  CC all
   kmcNuMuBarCCQEMEC,     // numubar  CC QE+MEC
   kmcNuMuBarCCQE,        // numubar  CC QE
   kmcNuMuBarCCMEC,       // numubar  CC MEC
   kmcNuMuBarCC1piC,      // numubar  CC 1 pipm
   kmcNuMuBarCC1pi0,      // numubar  CC 1 pi0
   kmcNuMuBarCC1pi,       // numubar  CC 1 pi any
   kmcNuMuBarCC2pi,       // numubar  CC 2 pi
   kmcNuMuBarCCIMD,       // numubar  IMD
   kmcNuMuBarCCElScat,    // numubar  elastic
   kmcNuMuBarCCoth,       // numubar  CC other
   kmcNuENuEBarCC,        // nue(bar) CC all
   kmcNuECC,              // nue      CC all
   kmcNuECCQEMEC,         // nue      CC QE+MEC
   kmcNuECCQE,            // nue      CC QE
   kmcNuECCMEC,           // nue      CC MEC
   kmcNuECC1pi,           // nue      CC 1 pi
   kmcNuECC2pi,           // nue      CC 2 pi
   kmcNuECCoth,           // nue      CC other
   kmcNuEElScat,          // nue      elastic
   kmcNuEBarCC,           // nuebar   CC all
   kmcNuEBarCCQEMEC,      // nuebar   CC QE+MEC
   kmcNuEBarCCQE,         // nuebar   CC QE
   kmcNuEBarCCMEC,        // nuebar   CC MEC
   kmcNuEBarCC1pi,        // nuebar   CC 1 pi
   kmcNuEBarCC2pi,        // nuebar   CC 2 pi
   kmcNuEBarCCoth,        // nuebar   CC other
   kmcNuEBarElScat,       // nuebar   elastic
   kmcNuTauNuTauBarCC,    // nutau(bar) CC all
   kmcNC,                 // NC all
   kmcNC0pi,              // NC 0 pi
   kmcNC1piC,             // NC 1 piC
   kmcNC1pi0,             // NC 1 pi0
   kmcNCoth,              // NC other
   //for the far detector
   kmcOscNuMuCC,             // nue->numu     CC all
   kmcOscNuMuBarCC,          // nuebar->numubar  CC all
   kmcOscNuECC,              // numu->nue     CC all
   kmcOscNuEBarCC,           // numubar->nuebar  CC all
   kmcNuTauCC,               // numu(nue)->nutau CC all (separated from nutaubar)
   kmcNuTauBarCC             // numubar(nuebar)->nutaubar CC all (separated from nutau)
} 
ReacModeCoarse_t;



// An array showing which ReacMode_ts go into which ReacModeCoarse_t (in order of priority
static const int kMaxCoarseReacOptions = 5;

static const ReacModeCoarse_t kCoarseReacPriority[kNReacModes][kMaxCoarseReacOptions] = 
{
   /* kmNuMuCCQE                   */ {kmcNuMuCCQE    , kmcNuMuCCQEMEC, kmcNuMuCCoth , kmcNuMuCC   , kmcUndefined},
   /* kmNuMuCCMEC                  */ {kmcNuMuCCMEC   , kmcNuMuCCQEMEC, kmcNuMuCCoth , kmcNuMuCC   , kmcUndefined},
   /* kmNuMuCC1piC                 */ {kmcNuMuCC1piC  , kmcNuMuCC1pi  , kmcNuMuCCoth , kmcNuMuCC   , kmcUndefined},
   /* kmNuMuCC1pi0                 */ {kmcNuMuCC1pi0  , kmcNuMuCC1pi  , kmcNuMuCCoth , kmcNuMuCC   , kmcUndefined},
   /* kmNuMuCC2piC                 */ {kmcNuMuCC2pi   , kmcNuMuCCoth  , kmcNuMuCC    , kmcUndefined, kmcUndefined},
   /* kmNuMuCC2pi0                 */ {kmcNuMuCC2pi   , kmcNuMuCCoth  , kmcNuMuCC    , kmcUndefined, kmcUndefined},
   /* kmNuMuCCpiCpi0               */ {kmcNuMuCC2pi   , kmcNuMuCCoth  , kmcNuMuCC    , kmcUndefined, kmcUndefined},
   /* kmNuMuCCcoh                  */ {kmcNuMuCC1pi   , kmcNuMuCCoth  , kmcNuMuCC    , kmcUndefined, kmcUndefined},
   /* kmNuMuCCIMD                  */ {kmcNuMuCCIMD   , kmcNuMuCCoth  , kmcNuMuCC    , kmcUndefined, kmcUndefined},
   /* kmNuMuCCELScat               */ {kmcNuMuCCElScat, kmcNuMuCCoth  , kmcNuMuCC    , kmcUndefined, kmcUndefined},
   /* kmNuMuCCoth                  */ {kmcNuMuCCoth   , kmcNuMuCC     , kmcUndefined , kmcUndefined, kmcUndefined},
// /* kmNuMuNCEL                   */ {kmcNC0pi       , kmcNCoth      , kmcNC        , kmcUndefined, kmcUndefined},
// /* kmNuMuNCMEC                  */ {kmcNC0pi       , kmcNCoth      , kmcNC        , kmcUndefined, kmcUndefined},
   /* kmNuMuNC1piC                 */ {kmcNC1piC      , kmcNCoth      , kmcNC        , kmcUndefined, kmcUndefined},
   /* kmNuMuNC1pi0                 */ {kmcNC1pi0      , kmcNCoth      , kmcNC        , kmcUndefined, kmcUndefined},
// /* kmNuMuNC2piC                 */ {kmcNC2pi       , kmcNCoth      , kmcNC        , kmcUndefined, kmcUndefined},
// /* kmNuMuNC2pi0                 */ {kmcNC2pi       , kmcNCoth      , kmcNC        , kmcUndefined, kmcUndefined},
// /* kmNuMuNCpiCpi0               */ {kmcNC2pi       , kmcNCoth      , kmcNC        , kmcUndefined, kmcUndefined},
   /* kmNuMuNCcoh                  */ {kmcNC1pi0      , kmcNCoth      , kmcNC        , kmcUndefined, kmcUndefined},
   /* kmNuMuNCELScat               */ {kmcNCoth       , kmcNC         , kmcUndefined , kmcUndefined, kmcUndefined},
   /* kmNuMuNCoth                  */ {kmcNCoth       , kmcNC         , kmcUndefined , kmcUndefined, kmcUndefined},
   
   /* kmNuMuBarCCQE                */ {kmcNuMuBarCCQE    , kmcNuMuBarCCQEMEC, kmcNuMuBarCCoth, kmcNuMuBarCC, kmcUndefined},
   /* kmNuMuBarCCMEC               */ {kmcNuMuBarCCMEC   , kmcNuMuBarCCQEMEC, kmcNuMuBarCCoth, kmcNuMuBarCC, kmcUndefined},
   /* kmNuMuBarCC1piC              */ {kmcNuMuBarCC1piC  , kmcNuMuBarCC1pi  , kmcNuMuBarCCoth, kmcNuMuBarCC, kmcUndefined},
   /* kmNuMuBarCC1pi0              */ {kmcNuMuBarCC1pi0  , kmcNuMuBarCC1pi  , kmcNuMuBarCCoth, kmcNuMuBarCC, kmcUndefined},
   /* kmNuMuBarCC2piC              */ {kmcNuMuBarCC2pi   , kmcNuMuBarCCoth  , kmcNuMuBarCC   , kmcUndefined, kmcUndefined},
   /* kmNuMuBarCC2pi0              */ {kmcNuMuBarCC2pi   , kmcNuMuBarCCoth  , kmcNuMuBarCC   , kmcUndefined, kmcUndefined},
   /* kmNuMuBarCCpiCpi0            */ {kmcNuMuBarCC2pi   , kmcNuMuBarCCoth  , kmcNuMuBarCC   , kmcUndefined, kmcUndefined},
   /* kmNuMuBarCCcoh               */ {kmcNuMuBarCC1pi   , kmcNuMuBarCCoth  , kmcNuMuBarCC   , kmcUndefined, kmcUndefined},
   /* kmNuMuBarCCELScat            */ {kmcNuMuBarCCElScat, kmcNuMuBarCCoth  , kmcNuMuBarCC   , kmcUndefined, kmcUndefined},
   /* kmNuMuBarCCoth               */ {kmcNuMuBarCCoth   , kmcNuMuBarCC     , kmcUndefined   , kmcUndefined, kmcUndefined},
// /* kmNuMuBarNCEL                */ {kmcNC0pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
// /* kmNuMuBarNCMEC               */ {kmcNC0pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuMuBarNC1piC              */ {kmcNC1piC   , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuMuBarNC1pi0              */ {kmcNC1pi0   , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
// /* kmNuMuBarNC2piC              */ {kmcNCoth    , kmcNC         , kmcUndefined , kmcUndefined, kmcUndefined},
// /* kmNuMuBarNC2pi0              */ {kmcNCoth    , kmcNC         , kmcUndefined , kmcUndefined, kmcUndefined},
// /* kmNuMuBarNCpiCpi0            */ {kmcNCoth    , kmcNC         , kmcUndefined , kmcUndefined, kmcUndefined},
   /* kmNuMuBarNCcoh               */ {kmcNC1pi0   , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuMuBarNCELScat            */ {kmcNCoth    , kmcNC         , kmcUndefined , kmcUndefined, kmcUndefined},
   /* kmNuMuBarNCoth               */ {kmcNCoth    , kmcNC         , kmcUndefined , kmcUndefined, kmcUndefined},
   
   /* kmNuECCQE                    */ {kmcNuECCQE  , kmcNuECCQEMEC , kmcNuECCoth , kmcNuECC , kmcNuENuEBarCC } ,
   /* kmNuECCMEC                   */ {kmcNuECCMEC , kmcNuECCQEMEC , kmcNuECCoth , kmcNuECC , kmcNuENuEBarCC } ,
   /* kmNuECC1piC                  */ {kmcNuECC1pi , kmcNuECCoth   , kmcNuECC    , kmcNuENuEBarCC, kmcUndefined} ,
   /* kmNuECC1pi0                  */ {kmcNuECC1pi , kmcNuECCoth   , kmcNuECC    , kmcNuENuEBarCC, kmcUndefined} ,
   /* kmNuECC2piC                  */ {kmcNuECC2pi , kmcNuECCoth   , kmcNuECC    , kmcNuENuEBarCC, kmcUndefined} ,
   /* kmNuECC2pi0                  */ {kmcNuECC2pi , kmcNuECCoth   , kmcNuECC    , kmcNuENuEBarCC, kmcUndefined} ,
   /* kmNuECCpiCpi0                */ {kmcNuECC2pi , kmcNuECCoth   , kmcNuECC    , kmcNuENuEBarCC, kmcUndefined} ,
   /* kmNuECCcoh                   */ {kmcNuECC1pi , kmcNuECCoth   , kmcNuECC    , kmcNuENuEBarCC, kmcUndefined} ,
   /* kmNuECCoth                   */ {kmcNuECCoth , kmcNuECC      , kmcNuENuEBarCC, kmcUndefined, kmcUndefined} ,
// /* kmNuENCEL                    */ {kmcNC0pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
// /* kmNuENCMEC                   */ {kmcNC0pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuENC1piC                  */ {kmcNC1piC   , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuENC1pi0                  */ {kmcNC1pi0   , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
// /* kmNuENC2piC                  */ {kmcNC2pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
// /* kmNuENC2pi0                  */ {kmcNC2pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
// /* kmNuENCpiCpi0                */ {kmcNC2pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuENCcoh                   */ {kmcNC1pi0   , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuEELScat                  */ {kmcNuEElScat, kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuENCoth                   */ {kmcNCoth    , kmcNC         , kmcUndefined , kmcUndefined, kmcUndefined},
   
   /* kmNuEBarCCQE                 */ {kmcNuEBarCCQE  , kmcNuEBarCCQEMEC , kmcNuEBarCCoth , kmcNuEBarCC , kmcNuENuEBarCC } ,
   /* kmNuEBarCCMEC                */ {kmcNuEBarCCMEC , kmcNuEBarCCQEMEC , kmcNuEBarCCoth , kmcNuEBarCC , kmcNuENuEBarCC } ,
   /* kmNuEBarCC1piC               */ {kmcNuEBarCC1pi , kmcNuEBarCCoth   , kmcNuEBarCC    , kmcNuENuEBarCC, kmcUndefined} ,
   /* kmNuEBarCC1pi0               */ {kmcNuEBarCC1pi , kmcNuEBarCCoth   , kmcNuEBarCC    , kmcNuENuEBarCC, kmcUndefined} ,
   /* kmNuEBarCC2piC               */ {kmcNuEBarCC2pi , kmcNuEBarCCoth   , kmcNuEBarCC    , kmcNuENuEBarCC, kmcUndefined} ,
   /* kmNuEBarCC2pi0               */ {kmcNuEBarCC2pi , kmcNuEBarCCoth   , kmcNuEBarCC    , kmcNuENuEBarCC, kmcUndefined} ,
   /* kmNuEBarCCpiCpi0             */ {kmcNuEBarCC2pi , kmcNuEBarCCoth   , kmcNuEBarCC    , kmcNuENuEBarCC, kmcUndefined} ,
   /* kmNuEBarCCcoh                */ {kmcNuEBarCC1pi , kmcNuEBarCCoth   , kmcNuEBarCC    , kmcNuENuEBarCC, kmcUndefined} ,
   /* kmNuEBarCCIMD                */ {kmcNuEBarCCoth , kmcNuEBarCC      , kmcNuENuEBarCC , kmcUndefined   , kmcUndefined} ,
   /* kmNuEBarCCoth                */ {kmcNuEBarCCoth , kmcNuEBarCC      , kmcNuENuEBarCC , kmcUndefined   , kmcUndefined} ,
// /* kmNuEBarNCEL                 */ {kmcNC0pi       , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
// /* kmNuEBarNCMEC                */ {kmcNC0pi       , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuEBarNC1piC               */ {kmcNC1piC      , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuEBarNC1pi0               */ {kmcNC1pi0      , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
// /* kmNuEBarNC2piC               */ {kmcNC2pi       , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
// /* kmNuEBarNC2pi0               */ {kmcNC2pi       , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
// /* kmNuEBarNCpiCpi0             */ {kmcNC2pi       , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuEBarNCcoh                */ {kmcNC1pi0      , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuEBarELScat               */ {kmcNuEBarElScat, kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuEBarNCoth                */ {kmcNCoth       , kmcNC         , kmcUndefined , kmcUndefined, kmcUndefined},
   
   /* kmNuMuToNuECCQE              */ {kmcOscNuECC     , kmcNuECC          , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuECCMEC             */ {kmcOscNuECC     , kmcNuECC          , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuECC1piC            */ {kmcOscNuECC     , kmcNuECC          , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuECC1pi0            */ {kmcOscNuECC     , kmcNuECC          , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuECC2piC            */ {kmcOscNuECC     , kmcNuECC          , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuECC2pi0            */ {kmcOscNuECC     , kmcNuECC          , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuECCpiCpi0          */ {kmcOscNuECC     , kmcNuECC          , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuECCcoh             */ {kmcOscNuECC     , kmcNuECC          , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuEELScat            */ {kmcOscNuECC     , kmcNuECC          , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuECCoth             */ {kmcOscNuECC     , kmcNuECC          , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCCQE            */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCCMEC           */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCC1piC          */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCC1pi0          */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCC2piC          */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCC2pi0          */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCCpiCpi0        */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCCcoh           */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCCELScat        */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCCoth           */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuEToNuMuCCQE              */ {kmcOscNuMuCC    , kmcNuMuCCQE       , kmcNuMuCCQEMEC, kmcNuMuCCoth, kmcNuMuCC    },
   /* kmNuEToNuMuCCMEC             */ {kmcOscNuMuCC    , kmcNuMuCCMEC      , kmcNuMuCCQEMEC, kmcNuMuCCoth, kmcNuMuCC    },
   /* kmNuEToNuMuCC1piC            */ {kmcOscNuMuCC    , kmcNuMuCC1piC     , kmcNuMuCC1pi  , kmcNuMuCC   , kmcUndefined },
   /* kmNuEToNuMuCC1pi0            */ {kmcOscNuMuCC    , kmcNuMuCC1pi0     , kmcNuMuCC1pi  , kmcNuMuCC   , kmcUndefined },
   /* kmNuEToNuMuCC2piC            */ {kmcOscNuMuCC    , kmcNuMuCC2pi      , kmcNuMuCCoth  , kmcNuMuCC   , kmcUndefined },
   /* kmNuEToNuMuCC2pi0            */ {kmcOscNuMuCC    , kmcNuMuCC2pi      , kmcNuMuCCoth  , kmcNuMuCC   , kmcUndefined },
   /* kmNuEToNuMuCCpiCpi0          */ {kmcOscNuMuCC    , kmcNuMuCC2pi      , kmcNuMuCCoth  , kmcNuMuCC   , kmcUndefined },
   /* kmNuEToNuMuCCcoh             */ {kmcOscNuMuCC    , kmcNuMuCC1pi      , kmcNuMuCCoth  , kmcNuMuCC   , kmcUndefined },
   /* kmNuEToNuMuCCIMD             */ {kmcOscNuMuCC    , kmcNuMuCCIMD      , kmcNuMuCCoth  , kmcNuMuCC   , kmcUndefined },
   /* kmNuEToNuMuCCELScat          */ {kmcOscNuMuCC    , kmcNuMuCCElScat   , kmcNuMuCCoth  , kmcNuMuCC   , kmcUndefined },
   /* kmNuEToNuMuCCoth             */ {kmcOscNuMuCC    , kmcNuMuCCoth      , kmcNuMuCC     , kmcNuMuCC   , kmcUndefined },
   /* kmNuEToNuTauCCQE             */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCCMEC            */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCC1piC           */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCC1pi0           */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCC2piC           */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCC2pi0           */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCCpiCpi0         */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCCcoh            */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCCELScat         */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCCoth            */ {kmcNuTauCC      , kmcNuTauNuTauBarCC, kmcUndefined  , kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCCQE        */ {kmcOscNuEBarCC  , kmcNuEBarCC       , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCCMEC       */ {kmcOscNuEBarCC  , kmcNuEBarCC       , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCC1piC      */ {kmcOscNuEBarCC  , kmcNuEBarCC       , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCC1pi0      */ {kmcOscNuEBarCC  , kmcNuEBarCC       , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCC2piC      */ {kmcOscNuEBarCC  , kmcNuEBarCC       , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCC2pi0      */ {kmcOscNuEBarCC  , kmcNuEBarCC       , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCCpiCpi0    */ {kmcOscNuEBarCC  , kmcNuEBarCC       , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCCcoh       */ {kmcOscNuEBarCC  , kmcNuEBarCC       , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCCIMD       */ {kmcOscNuEBarCC  , kmcNuEBarCC       , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarELScat      */ {kmcOscNuEBarCC  , kmcNuEBarCC       , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCCoth       */ {kmcOscNuEBarCC  , kmcNuEBarCC       , kmcNuENuEBarCC, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuTauBarCCQE      */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined, kmcUndefined   },
   /* kmNuMuBarToNuTauBarCCMEC     */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined, kmcUndefined   },
   /* kmNuMuBarToNuTauBarCC1piC    */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined, kmcUndefined   },
   /* kmNuMuBarToNuTauBarCC1pi0    */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined, kmcUndefined   },
   /* kmNuMuBarToNuTauBarCC2piC    */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined, kmcUndefined   },
   /* kmNuMuBarToNuTauBarCC2pi0    */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined, kmcUndefined   },
   /* kmNuMuBarToNuTauBarCCpiCpi0  */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined, kmcUndefined   },
   /* kmNuMuBarToNuTauBarCCcoh     */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined, kmcUndefined   },
   /* kmNuMuBarToNuTauBarCCELScat  */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined, kmcUndefined   },
   /* kmNuMuBarToNuTauBarCCoth     */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined, kmcUndefined   },
   /* kmNuEBarToNuMuBarCCQE        */ {kmcOscNuMuBarCC , kmcNuMuBarCCQE    , kmcNuMuBarCCQEMEC, kmcNuMuBarCCoth,kmcNuMuBarCC },
   /* kmNuEBarToNuMuBarCCMEC       */ {kmcOscNuMuBarCC , kmcNuMuBarCCMEC   , kmcNuMuBarCCQEMEC, kmcNuMuBarCCoth,kmcNuMuBarCC },
   /* kmNuEBarToNuMuBarCC1piC      */ {kmcOscNuMuBarCC , kmcNuMuBarCC1piC  , kmcNuMuBarCC1pi  , kmcNuMuBarCC   , kmcUndefined},
   /* kmNuEBarToNuMuBarCC1pi0      */ {kmcOscNuMuBarCC , kmcNuMuBarCC1pi0  , kmcNuMuBarCC1pi  , kmcNuMuBarCC   , kmcUndefined},
   /* kmNuEBarToNuMuBarCC2piC      */ {kmcOscNuMuBarCC , kmcNuMuBarCC2pi   , kmcNuMuBarCCoth  , kmcNuMuBarCC   , kmcUndefined},
   /* kmNuEBarToNuMuBarCC2pi0      */ {kmcOscNuMuBarCC , kmcNuMuBarCC2pi   , kmcNuMuBarCCoth  , kmcNuMuBarCC   , kmcUndefined},
   /* kmNuEBarToNuMuBarCCpiCpi0    */ {kmcOscNuMuBarCC , kmcNuMuBarCC2pi   , kmcNuMuBarCCoth  , kmcNuMuBarCC   , kmcUndefined},
   /* kmNuEBarToNuMuBarCCcoh       */ {kmcOscNuMuBarCC , kmcNuMuBarCC1pi   , kmcNuMuBarCCoth  , kmcNuMuBarCC   , kmcUndefined},
   /* kmNuEBarToNuMuBarCCELScat    */ {kmcOscNuMuBarCC , kmcNuMuBarCCElScat, kmcNuMuBarCCoth  , kmcNuMuBarCC   , kmcUndefined},
   /* kmNuEBarToNuMuBarCCoth       */ {kmcOscNuMuBarCC , kmcNuMuBarCCoth   , kmcNuMuBarCC     , kmcUndefined   , kmcUndefined},
   /* kmNuEBarToNuTauBarCCQE       */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined   , kmcUndefined },
   /* kmNuEBarToNuTauBarCCMEC      */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined   , kmcUndefined },
   /* kmNuEBarToNuTauBarCC1piC     */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined   , kmcUndefined },
   /* kmNuEBarToNuTauBarCC1pi0     */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined   , kmcUndefined },
   /* kmNuEBarToNuTauBarCC2piC     */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined   , kmcUndefined },
   /* kmNuEBarToNuTauBarCC2pi0     */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined   , kmcUndefined },
   /* kmNuEBarToNuTauBarCCpiCpi0   */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined   , kmcUndefined },
   /* kmNuEBarToNuTauBarCCcoh      */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined   , kmcUndefined },
   /* kmNuEBarToNuTauBarCCELScat   */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined   , kmcUndefined },
   /* kmNuEBarToNuTauBarCCoth      */ {kmcNuTauBarCC   , kmcNuTauNuTauBarCC, kmcUndefined     , kmcUndefined   , kmcUndefined },
// /* kmOther                      */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },

}; //

} // conv


//
// Associated utilities
//
namespace util {

  string AsString    (conv::ReacModeCoarse_t m);
  string AsStringTex (conv::ReacModeCoarse_t m, bool root);

} // util

} // valor
  
#endif 

