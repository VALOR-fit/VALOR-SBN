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
#include "dune/Conventions/ReacMode.h"

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
   kmcNuMuCC1pi,          // numu     CC 1 pi
   kmcNuMuCC2pi,          // numu     CC 2 pi
   kmcNuMuCCoth,          // numu     CC other
   kmcNuMuBarCC,          // numubar  CC all
   kmcNuMuBarCCQEMEC,     // numubar  CC QE+MEC
   kmcNuMuBarCCQE,        // numubar  CC QE
   kmcNuMuBarCCMEC,       // numubar  CC MEC
   kmcNuMuBarCC1pi,       // numubar  CC 1 pi
   kmcNuMuBarCC2pi,       // numubar  CC 2 pi
   kmcNuMuBarCCoth,       // numubar  CC other
   kmcNuENuEBarCC,        // nue(bar) CC all
   kmcNuECC,              // nue      CC all
   kmcNuECCQEMEC,         // nue      CC QE+MEC
   kmcNuECCQE,            // nue      CC QE
   kmcNuECCMEC,           // nue      CC MEC
   kmcNuECC1pi,           // nue      CC 1 pi
   kmcNuECC2pi,           // nue      CC 2 pi
   kmcNuECCoth,           // nue      CC other
   kmcNuEBarCC,           // nuebar   CC all
   kmcNuEBarCCQEMEC,      // nuebar   CC QE+MEC
   kmcNuEBarCCQE,         // nuebar   CC QE
   kmcNuEBarCCMEC,        // nuebar   CC MEC
   kmcNuEBarCC1pi,        // nuebar   CC 1 pi
   kmcNuEBarCC2pi,        // nuebar   CC 2 pi
   kmcNuEBarCCoth,        // nuebar   CC other
   kmcNuTauNuTauBarCC,    // nutau(bar) CC all
   kmcNC,                 // NC all
   kmcNC0pi,              // NC 0 pi
   kmcNC1piC,             // NC 1 piC
   kmcNC1pi0,             // NC 1 pi0
   kmcNCoth              // NC other
} 
ReacModeCoarse_t;



// An array showing which ReacMode_ts go into which ReacModeCoarse_t (in order of priority
static const int kMaxCoarseReacOptions = 5;

static const ReacModeCoarse_t kCoarseReacPriority[kNReacModes][kMaxCoarseReacOptions] = 
{
   /* kmNuMuCCQE                   */ {kmcNuMuCCQE , kmcNuMuCCQEMEC, kmcNuMuCCoth, kmcNuMuCC  , kmcUndefined},
   /* kmNuMuCCMEC                  */ {kmcNuMuCCMEC, kmcNuMuCCQEMEC, kmcNuMuCCoth, kmcNuMuCC  , kmcUndefined},
   /* kmNuMuCC1piC                 */ {kmcNuMuCC1pi, kmcNuMuCCoth  , kmcNuMuCC   , kmcUndefined, kmcUndefined},
   /* kmNuMuCC1pi0                 */ {kmcNuMuCC1pi, kmcNuMuCCoth  , kmcNuMuCC   , kmcUndefined, kmcUndefined},
   /* kmNuMuCC2piC                 */ {kmcNuMuCC2pi, kmcNuMuCCoth  , kmcNuMuCC   , kmcUndefined, kmcUndefined},
   /* kmNuMuCC2pi0                 */ {kmcNuMuCC2pi, kmcNuMuCCoth  , kmcNuMuCC   , kmcUndefined, kmcUndefined},
   /* kmNuMuCCpiCpi0               */ {kmcNuMuCC2pi, kmcNuMuCCoth  , kmcNuMuCC   , kmcUndefined, kmcUndefined},
   /* kmNuMuCCcoh                  */ {kmcNuMuCC1pi, kmcNuMuCCoth  , kmcNuMuCC   , kmcUndefined, kmcUndefined},
   /* kmNuMuCCIMD                  */ {kmcNuMuCCoth, kmcNuMuCC     , kmcUndefined , kmcUndefined, kmcUndefined},
   /* kmNuMuCCELScat               */ {kmcNuMuCCoth, kmcNuMuCC     , kmcUndefined , kmcUndefined, kmcUndefined},
   /* kmNuMuCCoth                  */ {kmcNuMuCCoth, kmcNuMuCC     , kmcUndefined , kmcUndefined, kmcUndefined},
// /* kmNuMuNCEL                   */ {kmcNC0pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
// /* kmNuMuNCMEC                  */ {kmcNC0pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuMuNC1piC                 */ {kmcNC1piC   , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuMuNC1pi0                 */ {kmcNC1pi0   , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
// /* kmNuMuNC2piC                 */ {kmcNC2pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
// /* kmNuMuNC2pi0                 */ {kmcNC2pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
// /* kmNuMuNCpiCpi0               */ {kmcNC2pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuMuNCcoh                  */ {kmcNC1pi0   , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuMuNCELScat               */ {kmcNCoth    , kmcNC         , kmcUndefined , kmcUndefined, kmcUndefined},
   /* kmNuMuNCoth                  */ {kmcNCoth    , kmcNC         , kmcUndefined , kmcUndefined, kmcUndefined},
   
   /* kmNuMuBarCCQE                */ {kmcNuMuBarCCQE , kmcNuMuBarCCQEMEC, kmcNuMuBarCCoth, kmcNuMuBarCC  , kmcUndefined},
   /* kmNuMuBarCCMEC               */ {kmcNuMuBarCCMEC, kmcNuMuBarCCQEMEC, kmcNuMuBarCCoth, kmcNuMuBarCC  , kmcUndefined},
   /* kmNuMuBarCC1piC              */ {kmcNuMuBarCC1pi, kmcNuMuBarCCoth  , kmcNuMuBarCC   , kmcUndefined, kmcUndefined},
   /* kmNuMuBarCC1pi0              */ {kmcNuMuBarCC1pi, kmcNuMuBarCCoth  , kmcNuMuBarCC   , kmcUndefined, kmcUndefined},
   /* kmNuMuBarCC2piC              */ {kmcNuMuBarCC2pi, kmcNuMuBarCCoth  , kmcNuMuBarCC   , kmcUndefined, kmcUndefined},
   /* kmNuMuBarCC2pi0              */ {kmcNuMuBarCC2pi, kmcNuMuBarCCoth  , kmcNuMuBarCC   , kmcUndefined, kmcUndefined},
   /* kmNuMuBarCCpiCpi0            */ {kmcNuMuBarCC2pi, kmcNuMuBarCCoth  , kmcNuMuBarCC   , kmcUndefined, kmcUndefined},
   /* kmNuMuBarCCcoh               */ {kmcNuMuBarCC1pi, kmcNuMuBarCCoth  , kmcNuMuBarCC   , kmcUndefined, kmcUndefined},
   /* kmNuMuBarCCELScat            */ {kmcNuMuBarCCoth, kmcNuMuBarCC     , kmcUndefined , kmcUndefined, kmcUndefined},
   /* kmNuMuBarCCoth               */ {kmcNuMuBarCCoth, kmcNuMuBarCC     , kmcUndefined , kmcUndefined, kmcUndefined},
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
   /* kmNuEELScat                  */ {kmcNC0pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuENCoth                   */ {kmcNCoth    , kmcNC         , kmcUndefined , kmcUndefined, kmcUndefined},
   
   /* kmNuEBarCCQE                 */ {kmcNuEBarCCQE  , kmcNuEBarCCQEMEC , kmcNuEBarCCoth , kmcNuEBarCC , kmcNuENuEBarCC } ,
   /* kmNuEBarCCMEC                */ {kmcNuEBarCCMEC, kmcNuEBarCCQEMEC , kmcNuEBarCCoth , kmcNuEBarCC , kmcNuENuEBarCC } ,
   /* kmNuEBarCC1piC               */ {kmcNuEBarCC1pi , kmcNuEBarCCoth   , kmcNuEBarCC    , kmcNuENuEBarCC, kmcUndefined} ,
   /* kmNuEBarCC1pi0               */ {kmcNuEBarCC1pi , kmcNuEBarCCoth   , kmcNuEBarCC    , kmcNuENuEBarCC, kmcUndefined} ,
   /* kmNuEBarCC2piC               */ {kmcNuEBarCC2pi , kmcNuEBarCCoth   , kmcNuEBarCC    , kmcNuENuEBarCC, kmcUndefined} ,
   /* kmNuEBarCC2pi0               */ {kmcNuEBarCC2pi , kmcNuEBarCCoth   , kmcNuEBarCC    , kmcNuENuEBarCC, kmcUndefined} ,
   /* kmNuEBarCCpiCpi0             */ {kmcNuEBarCC2pi , kmcNuEBarCCoth   , kmcNuEBarCC    , kmcNuENuEBarCC, kmcUndefined} ,
   /* kmNuEBarCCcoh                */ {kmcNuEBarCC1pi , kmcNuEBarCCoth   , kmcNuEBarCC    , kmcNuENuEBarCC, kmcUndefined} ,
   /* kmNuEBarCCIMD                */ {kmcNuEBarCCoth , kmcNuEBarCC      , kmcNuENuEBarCC , kmcUndefined   , kmcUndefined} ,
   /* kmNuEBarCCoth                */ {kmcNuEBarCCoth , kmcNuEBarCC      , kmcNuENuEBarCC , kmcUndefined   , kmcUndefined} ,
// /* kmNuEBarNCEL                 */ {kmcNC0pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
// /* kmNuEBarNCMEC                */ {kmcNC0pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuEBarNC1piC               */ {kmcNC1piC   , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuEBarNC1pi0               */ {kmcNC1pi0   , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
// /* kmNuEBarNC2piC               */ {kmcNC2pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
// /* kmNuEBarNC2pi0               */ {kmcNC2pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
// /* kmNuEBarNCpiCpi0             */ {kmcNC2pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuEBarNCcoh                */ {kmcNC1pi0   , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuEBarELScat               */ {kmcNC0pi    , kmcNCoth      , kmcNC       , kmcUndefined, kmcUndefined},
   /* kmNuEBarNCoth                */ {kmcNCoth    , kmcNC         , kmcUndefined , kmcUndefined, kmcUndefined},
   
   /* kmNuMuToNuECCQE              */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuECCMEC             */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuECC1piC            */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuECC1pi0            */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuECC2piC            */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuECC2pi0            */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuECCpiCpi0          */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuECCcoh             */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuEELScat            */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuECCoth             */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCCQE            */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCCMEC           */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCC1piC          */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCC1pi0          */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCC2piC          */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCC2pi0          */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCCpiCpi0        */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCCcoh           */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCCELScat        */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuToNuTauCCoth           */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuMuCCQE              */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuMuCCMEC             */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuMuCC1piC            */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuMuCC1pi0            */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuMuCC2piC            */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuMuCC2pi0            */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuMuCCpiCpi0          */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuMuCCcoh             */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuMuCCIMD             */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuMuCCELScat          */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuMuCCoth             */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCCQE             */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCCMEC            */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCC1piC           */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCC1pi0           */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCC2piC           */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCC2pi0           */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCCpiCpi0         */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCCcoh            */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCCELScat         */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEToNuTauCCoth            */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCCQE        */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCCMEC       */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCC1piC      */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCC1pi0      */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCC2piC      */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCC2pi0      */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCCpiCpi0    */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCCcoh       */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCCIMD       */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarELScat      */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuEBarCCoth       */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuTauBarCCQE      */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuTauBarCCMEC     */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuTauBarCC1piC    */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuTauBarCC1pi0    */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuTauBarCC2piC    */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuTauBarCC2pi0    */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuTauBarCCpiCpi0  */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuTauBarCCcoh     */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuTauBarCCELScat  */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuMuBarToNuTauBarCCoth     */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuMuBarCCQE        */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuMuBarCCMEC       */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuMuBarCC1piC      */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuMuBarCC1pi0      */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuMuBarCC2piC      */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuMuBarCC2pi0      */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuMuBarCCpiCpi0    */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuMuBarCCcoh       */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuMuBarCCELScat    */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuMuBarCCoth       */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuTauBarCCQE       */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuTauBarCCMEC      */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuTauBarCC1piC     */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuTauBarCC1pi0     */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuTauBarCC2piC     */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuTauBarCC2pi0     */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuTauBarCCpiCpi0   */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuTauBarCCcoh      */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuTauBarCCELScat   */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
   /* kmNuEBarToNuTauBarCCoth      */ {kmcUndefined , kmcUndefined   , kmcUndefined, kmcUndefined, kmcUndefined },
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

