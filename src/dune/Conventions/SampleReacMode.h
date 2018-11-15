//____________________________________________________________________________
/*!

\file      SampleReacMode

\brief     Define which true reaction modes to consider for each sample

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

\created   March 20, 2014

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_sample_reac_modes_h_
#define _valor_dune_sample_reac_modes_h_

#include "valor/Conventions/BeamConf.h"
#include "valor/Conventions/Sample.h"
#include "dune/Conventions/ReacMode.h"
#include "dune/Conventions/ReacModeCoarse.h"


namespace valor {  
namespace conv {

//
// ---------------------------------------------------------------------------
// Define which true reaction modes are considered for each sample 
// included in the analysis
// ---------------------------------------------------------------------------
//
  
  static const ReacMode_t kReactionModes[kNSamples][kNReacModes]  = 
    {
      // 2016b near detector selections
      // selection: ksNuMuCC0pi1trk
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },

      // selection: ksNuMuCC0pi2trk
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },

      // selection: ksNuMuCC0piNtrk
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },

      // selection: ksNuMuCC3trkDelta
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },

      // selection: ksNuMuCC1piC
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },

      // selection: ksNuMuCC1pi0
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },

      // selection: ksNuMuCC1piC1pi0
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },

      // selection: ksNuMuCCoth
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },

      // selection: ksNuMuCCWS0pi
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },
      // selection: ksNuMuCCWS1piC
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },
      // selection: ksNuMuCCWS1pi0
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },
      // selection: ksNuMuCCWSoth
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },
      // selection: ksNuECC0pi
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },
      // selection: ksNuECC1piC
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },
      // selection: ksNuECC1pi0
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },
      // selection: ksNuECCoth
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },
      // selection: ksNC0pi
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },
      // selection: ksNC1piC
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },
      // selection: ksNC1pi0
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },
      // selection: ksNCoth
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },
      // selection: ksNeutrinoElec
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },
      // selection: ksInvMuDecay
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },
      // selection: ksNuECCWS
      {
        #include "dune/Conventions/ModeLists/OscLowE.h"
      },
      //far detector
      // selection: ksNuMuCChigh/ksNuMuBarCChigh
      {
        #include "dune/Conventions/ModeLists/OscHighE.h"
      },
      // selection: ksNuMuCClow/ksNuMuBarCClow
      {
        #include "dune/Conventions/ModeLists/OscHighE.h"
      },
      // selection: ksNuECChigh/ksNuEBarCChigh
      {
        #include "dune/Conventions/ModeLists/OscHighE.h"
      },
      // selection: ksNuECClow/ksNuEBarCClow
      {
        #include "dune/Conventions/ModeLists/OscHighE.h"
      }
};
  
   
//
// ---------------------------------------------------------------------------
// Define ReacModeCoarse_t types (used only in plots) for each sample 
// ---------------------------------------------------------------------------
//

// The order of ReacModeCoarse_t types below, is the order with which the
// corresponding contributions enter in the plotted THStacks.

static const int kNReacModesCoarse = 9;  // max coarse modes used per sample

static const ReacModeCoarse_t kReactionModesCoarse[kNBeamConf][kNSamples][kNReacModesCoarse] = 
{
  // FHC
  {
    // sample: ksNuMuCC0pi1trk
    {
      kmcNuMuCCQE,    
      kmcNuMuCCMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuMuCC0pi2trk
    {
      kmcNuMuCCQE,    
      kmcNuMuCCMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuMuCC0piNtrk
    {
      kmcNuMuCCQE,    
      kmcNuMuCCMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined           
    },
    // sample: ksNuMuCC0pi3trkDelta
    {
      kmcNuMuCCQE,    
      kmcNuMuCCMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuMuCC1piC
    {
      kmcNuMuCCQEMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuMuCC1pi0
    {
      kmcNuMuCCQEMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuMuCC1piC1pi0
    {
      kmcNuMuCCQEMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuMuCCoth
    {
      kmcNuMuCCQEMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuMuCCWS0pi
    {
      kmcNuMuBarCCQEMEC,    
      kmcNuMuBarCC1pi,   
      kmcNuMuBarCC2pi,   
      kmcNuMuBarCCoth,   
      kmcNuMuCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuMuCCWS1piC
    {
      kmcNuMuBarCCQEMEC,    
      kmcNuMuBarCC1pi,   
      kmcNuMuBarCC2pi,   
      kmcNuMuBarCCoth,   
      kmcNuMuCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuMuCCWS1pi0
    {
      kmcNuMuBarCCQEMEC,    
      kmcNuMuBarCC1pi,   
      kmcNuMuBarCC2pi,   
      kmcNuMuBarCCoth,   
      kmcNuMuCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuMuCCWSoth
    {
      kmcNuMuBarCCQEMEC,    
      kmcNuMuBarCC1pi,   
      kmcNuMuBarCC2pi,   
      kmcNuMuBarCCoth,   
      kmcNuMuCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuECC0pi
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECCQEMEC,   
      kmcNuECCoth,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuECC1piC
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC1pi,   
      kmcNuECCoth,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuECC1pi0
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC1pi,   
      kmcNuECCoth,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuECCoth
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNC0pi
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1piC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNC1piC
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1piC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNC1pi0
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1piC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNCoth
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1piC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined
    },
    //TODO: revisit ksNeutrinoElec and ksInvMuDecay
    // sample: ksNeutrinoElec
    {
      kmcNuMuCCElScat,    
      kmcNuMuBarCCElScat,
      kmcNuEElScat,
      kmcNuEBarElScat, 
      kmcNuMuCCoth,   
      kmcNuMuBarCCoth,   
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined
    },
    // sample: ksInvMuDecay
    {
      kmcNuMuCCElScat,    
      kmcNuMuBarCCElScat,
      kmcNuEElScat,
      kmcNuEBarElScat, 
      kmcNuMuCCoth,
      kmcNuMuBarCCoth,   
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuECCWS
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined,
      kmcUndefined
    },
    //2016b far detector selections
    // sample: ksNuMuCChigh
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcOscNuMuCC,
      kmcOscNuMuBarCC,
      kmcNuECC, 
      kmcNuEBarCC,
      kmcNuTauCC,
      kmcNuTauBarCC,
      kmcNC           
    },
    // sample: ksNuMuCClow
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcOscNuMuCC,
      kmcOscNuMuBarCC,
      kmcNuECC, 
      kmcNuEBarCC,
      kmcNuTauCC,
      kmcNuTauBarCC,
      kmcNC           
    },
    // sample: ksNuECChigh
    {
      kmcOscNuECC,
      kmcOscNuEBarCC,
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuTauCC,
      kmcNuTauBarCC,
      kmcNC
    },
    // sample: ksNuECClow
    {
      kmcOscNuECC,
      kmcOscNuEBarCC,
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuTauCC,
      kmcNuTauBarCC,
      kmcNC
    }
  }, // end of FHC
  //RHC
  {
    // sample: ksNuMuCC0pi1trk
    {
      kmcNuMuBarCCQE,
      kmcNuMuBarCCMEC,
      kmcNuMuBarCC1pi,
      kmcNuMuBarCC2pi,
      kmcNuMuBarCCoth,
      kmcNuMuCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuMuCC0pi2trk
    {
      kmcNuMuBarCCQE,
      kmcNuMuBarCCMEC,
      kmcNuMuBarCC1pi,
      kmcNuMuBarCC2pi,
      kmcNuMuBarCCoth,
      kmcNuMuCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuMuCC0piNtrk
    {
      kmcNuMuBarCCQE,
      kmcNuMuBarCCMEC,
      kmcNuMuBarCC1pi,
      kmcNuMuBarCC2pi,
      kmcNuMuBarCCoth,
      kmcNuMuCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuMuCC0pi3trkDelta
    {
      kmcNuMuBarCCQE,
      kmcNuMuBarCCMEC,
      kmcNuMuBarCC1pi,
      kmcNuMuBarCC2pi,
      kmcNuMuBarCCoth,
      kmcNuMuCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuMuCC1piC
    {
      kmcNuMuBarCCQEMEC,
      kmcNuMuBarCC1pi,
      kmcNuMuBarCC2pi,
      kmcNuMuBarCCoth,
      kmcNuMuCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuMuCC1pi0
    {
      kmcNuMuBarCCQEMEC,
      kmcNuMuBarCC1pi,
      kmcNuMuBarCC2pi,
      kmcNuMuBarCCoth,
      kmcNuMuCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuMuCC1piC1pi0
    {
      kmcNuMuBarCCQEMEC,
      kmcNuMuBarCC1pi,
      kmcNuMuBarCC2pi,
      kmcNuMuBarCCoth,
      kmcNuMuCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuMuCCoth
    {
      kmcNuMuBarCCQEMEC,
      kmcNuMuBarCC1pi,
      kmcNuMuBarCC2pi,
      kmcNuMuBarCCoth,
      kmcNuMuCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuMuCCWS0pi
    {
      kmcNuMuCCQEMEC,
      kmcNuMuCC1pi,
      kmcNuMuCC2pi,
      kmcNuMuCCoth,
      kmcNuMuBarCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuMuCCWS1piC
    {
      kmcNuMuCCQEMEC,
      kmcNuMuCC1pi,
      kmcNuMuCC2pi,
      kmcNuMuCCoth,
      kmcNuMuBarCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuMuCCWS1pi0
    {
      kmcNuMuCCQEMEC,
      kmcNuMuCC1pi,
      kmcNuMuCC2pi,
      kmcNuMuCCoth,
      kmcNuMuBarCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuMuCCWSoth
    {
      kmcNuMuCCQEMEC,
      kmcNuMuCC1pi,
      kmcNuMuCC2pi,
      kmcNuMuCCoth,
      kmcNuMuBarCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuECC0pi
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCCQEMEC,   
      kmcNuEBarCCoth,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuECC1piC
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC1pi,   
      kmcNuEBarCCoth,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuECC1pi0
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC1pi,   
      kmcNuEBarCCoth,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNuECCoth
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNC0pi
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1piC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNC1piC
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1piC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNC1pi0
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1piC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined
    },
    // sample: ksNCoth
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1piC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined
    },
    //TODO: revisit ksNeutrinoElec and ksInvMuDecay
    // sample: ksNeutrinoElec
    {
      kmcNuMuCCElScat,    
      kmcNuMuBarCCElScat,
      kmcNuEElScat,
      kmcNuEBarElScat, 
      kmcNuMuCCoth,   
      kmcNuMuBarCCoth,   
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined
    },
    // sample: ksInvMuDecay
    {
      kmcNuMuCCElScat,    
      kmcNuMuBarCCElScat,
      kmcNuEElScat,
      kmcNuEBarElScat, 
      kmcNuMuCCoth,
      kmcNuMuBarCCoth,   
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuECCWS
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined,
      kmcUndefined
    },
    //2016b far detector selections
    // sample: ksNuMuCChigh
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcOscNuMuCC,
      kmcOscNuMuBarCC,
      kmcNuECC, 
      kmcNuEBarCC,
      kmcNuTauCC,
      kmcNuTauBarCC,
      kmcNC           
    },
    // sample: ksNuMuCClow
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcOscNuMuCC,
      kmcOscNuMuBarCC,
      kmcNuECC, 
      kmcNuEBarCC,
      kmcNuTauCC,
      kmcNuTauBarCC,
      kmcNC           
    },
    // sample: ksNuECChigh
    {
      kmcOscNuECC,
      kmcOscNuEBarCC,
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuTauCC,
      kmcNuTauBarCC,
      kmcNC
    },
    // sample: ksNuECClow
    {
      kmcOscNuECC,
      kmcOscNuEBarCC,
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuTauCC,
      kmcNuTauBarCC,
      kmcNC
    }
  }
};

//
// Also, specify formatting (line color, fill color, fill style)
//

static const int kReactionModesCoarseFormatting[kNBeamConf][kNSamples][kNReacModesCoarse][3] = 
{
  // FHC
  {
    // sample: ksNuMuCC0pi1trk
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCC0pi2trk
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCC0piNtrk,
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCC3trkDelta
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCC1piC
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0},
      {0,0,0}
    },
    // sample: ksNuMuCC1pi0
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0},
      {0,0,0}
    },
    // sample: ksNuMuCC1piC1pi0
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0},
      {0,0,0}
    },
    // sample: ksNuMuCCoth
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC         
      {0,0,0},
      {0,0,0}
    },
    // sample: ksNuMuCCWS0pi
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0},
      {0,0,0}
    },
    // sample: ksNuMuCCWS1piC
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0},
      {0,0,0}
    },
    // sample: ksNuMuCCWS1pi0
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0},
      {0,0,0}
    },
    // sample: ksNuMuCCWSoth
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuECC0pi
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECCQEMEC
      { kBlack, kMagenta,  3001 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0},
      {0,0,0}
    },
    // sample: ksNuECC1piC
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC1piC
      { kBlack, kMagenta,  3001 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth   
      {0,0,0},
      {0,0,0}
    },
    // sample: ksNuECC1pi0
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC1pi0
      { kBlack, kMagenta,  3001 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth     
      {0,0,0}  
    },
    // sample: ksNuECCoth
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0},        
      {0,0,0},
      {0,0,0}
    },
    // sample: ksNC0pi
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3022 }, // kmcNC1piC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0},
      {0,0,0}
    },
    // sample: ksNC1piC
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3022 }, // kmcNC1piC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0},
      {0,0,0}
    },
    // sample: ksNC1pi0
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3022 }, // kmcNC1piC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0},
      {0,0,0}
    },
    // sample: ksNCoth
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3022 }, // kmcNC1piC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth   
      {0,0,0},
      {0,0,0}
    },
    // sample: ksNeutrinoElec
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE 
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC 
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi 
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi 
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth 
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC 
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC 
      { kBlack, kRed,      3001 }, // kmcNC 
      {0,0,0}
    },
    // sample: ksInvMuDecay
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE 
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC 
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi 
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi 
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth 
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC 
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC 
      { kBlack, kRed,      3001 }, // kmcNC 
      {0,0,0}
    },
    // sample: ksNuECCWS
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0},
      {0,0,0}
    },
    //far detector samples
    // sample: ksNuMuCChigh/ksNuMuBarCChigh
    {
      { kBlack, kWhite,    1001 }, // kmcNuMuCC
      { kBlack, kYellow,   1001 }, // kmcNuMuBarCC
      { kBlack, kAzure,    3004 }, // kmcOscNuMuCC
      { kBlack, kBlue,     3005 }, // kmcOscNuMuBarCC
      { kBlack, kGreen,    3007 }, // kmcNuECC
      { kBlack, kMagenta,  3001 }, // kmcNuEBarCC
      { kBlack, kViolet-1, 3001 }, // kmcNuTauCC 
      { kBlack, kOrange-1, 3001 }, // kmcNuTauBarCC 
      { kBlack, kRed,      3001 }  // kmcNC 
    },
    // sample: ksNuMuCClow/ksNuMuBarCClow
    {
      { kBlack, kWhite,    1001 }, // kmcNuMuCC
      { kBlack, kYellow,   1001 }, // kmcNuMuBarCC
      { kBlack, kAzure,    3004 }, // kmcOscNuMuCC
      { kBlack, kBlue,     3005 }, // kmcOscNuMuBarCC
      { kBlack, kGreen,    3007 }, // kmcNuECC
      { kBlack, kMagenta,  3001 }, // kmcNuEBarCC
      { kBlack, kViolet-1, 3001 }, // kmcNuTauCC 
      { kBlack, kOrange-1, 3001 }, // kmcNuTauBarCC 
      { kBlack, kRed,      3001 }  // kmcNC 
    },
    // sample: ksNuECChigh/ksNuEBarCChigh
    {
      { kBlack, kCyan,     1001 }, // kmcOscNuECC                                                                                                     
      { kBlack, kBlue,     1001 }, // kmcOscNuEBarCC 
      { kBlack, kGreen,    3007 }, // kmcNuECC                                                                                                           
      { kBlack, kMagenta,  3004 }, // kmcNuEBarCC
      { kBlack, kWhite,    3544 }, // kmcNuMuCC                                                                                                          
      { kBlack, kYellow,   3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuTauCC 
      { kBlack, kOrange-1, 3001 }, // kmcNuTauBarCC 
      { kBlack, kRed,      3001 }  // kmcNC 
    },
    // sample: ksNuECClow/ksNuEBarCClow
    {
      { kBlack, kCyan,     1001 }, // kmcOscNuECC                                                                                                     
      { kBlack, kBlue,     1001 }, // kmcOscNuEBarCC 
      { kBlack, kGreen,    3007 }, // kmcNuECC                                                                                                           
      { kBlack, kMagenta,  3004 }, // kmcNuEBarCC
      { kBlack, kWhite,    3544 }, // kmcNuMuCC                                                                                                          
      { kBlack, kYellow,   3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuTauCC 
      { kBlack, kOrange-1, 3001 }, // kmcNuTauBarCC 
      { kBlack, kRed,      3001 }  // kmcNC 
    }
  }, // end of FHC
  // RHC
  {
    // sample: ksNuMuCC0pi1trk
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }  // kmcNC           
    },
    // sample: ksNuMuCC0pi2trk
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }  // kmcNC           
    },
    // sample: ksNuMuCC0piNtrk,
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }  // kmcNC           
    },
    // sample: ksNuMuCC3trkDelta
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }  // kmcNC           
    },
    // sample: ksNuMuCC1piC
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCC1pi0
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCC1piC1pi0
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCCoth
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC         
      {0,0,0}  
    },
    // sample: ksNuMuCCWS0pi
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCCWS1piC
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCCWS1pi0
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCCWSoth
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuECC0pi
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kViolet-1, 3001 }, // kmcNuECC
      { kBlack, kWhite,    3544 }, // kmcNuEBarCC0pi
      { kBlack, kMagenta,  3001 }, // kmcNuEBarCCoth
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0}  
    },
    // sample: ksNuECC1piC
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kViolet-1, 3001 }, // kmcNuECC
      { kBlack, kWhite,    3544 }, // kmcNuEBarCC1piC
      { kBlack, kMagenta,  3001 }, // kmcNuEBarCCoth
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth    
      {0,0,0}  
    },
    // sample: ksNuECC1pi0
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kViolet-1, 3001 }, // kmcNuECC
      { kBlack, kWhite,    3544 }, // kmcNuEBarCC1pi0
      { kBlack, kWhite,    3544 }, // kmcNuEBarCCoth
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth     
      {0,0,0}  
    },
    // sample: ksNuECCoth
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kViolet-1, 3001 }, // kmcNuECC
      { kBlack, kWhite,    3544 }, // kmcNuEBarCC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0},        
      {0,0,0}  
    },
    // sample: ksNC0pi
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3022 }, // kmcNC1piC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0}  
    },
    // sample: ksNC1piC
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3022 }, // kmcNC1piC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0}  
    },
    // sample: ksNC1pi0
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3022 }, // kmcNC1piC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth   
      {0,0,0}  
    },
    // sample: ksNCoth
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3022 }, // kmcNC1piC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0}  
    },
    // sample: ksNeutrinoElec
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE 
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC 
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi 
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi 
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth 
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC 
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC 
      { kBlack, kRed,      3001 }  // kmcNC 
    },
    // sample: ksInvMuDecay
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE 
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC 
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi 
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi 
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth 
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC 
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC 
      { kBlack, kRed,      3001 }  // kmcNC 
    },
    // sample: ksNuECCWS
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    //far detector samples
    // sample: ksNuMuCChigh/ksNuMuBarCChigh
    {
      { kBlack, kWhite,    1001 }, // kmcNuMuCC
      { kBlack, kYellow,   1001 }, // kmcNuMuBarCC
      { kBlack, kAzure,    3004 }, // kmcOscNuMuCC
      { kBlack, kBlue,     3005 }, // kmcOscNuMuBarCC
      { kBlack, kGreen,    3007 }, // kmcNuECC
      { kBlack, kMagenta,  3001 }, // kmcNuEBarCC
      { kBlack, kViolet-1, 3001 }, // kmcNuTauCC 
      { kBlack, kOrange-1, 3001 }, // kmcNuTauBarCC 
      { kBlack, kRed,      3001 }  // kmcNC 
    },
    // sample: ksNuMuCClow/ksNuMuBarCClow
    {
      { kBlack, kWhite ,   1001 }, // kmcNuMuCC
      { kBlack, kYellow,   1001 }, // kmcNuMuBarCC
      { kBlack, kAzure,    3004 }, // kmcOscNuMuCC
      { kBlack, kBlue,     3005 }, // kmcOscNuMuBarCC
      { kBlack, kGreen,    3007 }, // kmcNuECC
      { kBlack, kMagenta,  3001 }, // kmcNuEBarCC
      { kBlack, kViolet-1, 3001 }, // kmcNuTauCC 
      { kBlack, kOrange-1, 3001 }, // kmcNuTauBarCC 
      { kBlack, kRed,      3001 }  // kmcNC 
    },
    // sample: ksNuECChigh/ksNuEBarCChigh
    {
      { kBlack, kCyan,     1001 }, // kmcOscNuECC                                                                                                     
      { kBlack, kBlue,     1001 }, // kmcOscNuEBarCC 
      { kBlack, kGreen,    3007 }, // kmcNuECC                                                                                                           
      { kBlack, kMagenta,  3004 }, // kmcNuEBarCC
      { kBlack, kWhite,    3544 }, // kmcNuMuCC                                                                                                          
      { kBlack, kYellow,   3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuTauCC 
      { kBlack, kOrange-1, 3001 }, // kmcNuTauBarCC 
      { kBlack, kRed,      3001 }  // kmcNC 
    },
    // sample: ksNuECClow/ksNuEBarCClow
    {
      { kBlack, kCyan,     1001 }, // kmcOscNuECC                                                                                                     
      { kBlack, kBlue,     1001 }, // kmcOscNuEBarCC 
      { kBlack, kGreen,    3007 }, // kmcNuECC                                                                                                           
      { kBlack, kMagenta,  3004 }, // kmcNuEBarCC
      { kBlack, kWhite,    3544 }, // kmcNuMuCC                                                                                                          
      { kBlack, kYellow,   3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuTauCC 
      { kBlack, kOrange-1, 3001 }, // kmcNuTauBarCC 
      { kBlack, kRed,      3001 }  // kmcNC 
    }
  } // end of RHC
};

} // conv
} // valor

#endif 
