//____________________________________________________________________________
/*!

\class     valor::conv::Sample_t

\brief     Enumeration of DUNE event samples

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

\created   March 20, 2014

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_sample_h_
#define _valor_sample_h_

#include <string>

#include "dune/Conventions/BeamConf.h"

using std::string;

namespace valor {
namespace conv {

// ...........................................................................
// Define samples
//
typedef enum ESample 
{

#ifdef VALOR_DUNE_THIRD_PASS_THROUGH
   ksUndefined       = -1,
   ksNuMuCC          =  0, // numu CC inclusive 
   ksNuMuCC1trk0pi   =  1, // numu CC - 1 track QE-enhanced - 0 pions  (mu)
   ksNuMuCC2trk0pi   =  2, // numu CC - 2 track QE-enhanched - 0 pions (mu + proton)
   ksNuMuCCNtrk0pi   =  3, // numu CC - N track QE-enhanched - 0 pions (mu + >1 nucleons)
   ksNuMuCC3trkDelta =  4, // numu CC - 3 track Delta-enhanched (mu + proton + pi+, Wreco ~1.2 GeV)
   ksNuMuCC1piC      =  5, // numu CC - 2 track (mu + 1 pi+/-)
   ksNuMuCC1pi0      =  6, // numu CC - 2 track (mu + 1 pi0)
   ksNuMuCC1piC1pi0  =  7, // numu CC - 3 track (mu + 1 pi+/- + 1pi0)
   ksNuMuCCoth       =  8, // numu CC - other
   ksNuMuCCWSgn0pi   =  9, // wrong sign numu CC - 0 pions (mu+)
   ksNuMuCCWSgn1piC  = 10, // wrong sign numu CC - 1 pion charged (mu+ + 1 pi+/-)
   ksNuMuCCWSgn1pi0  = 11, // wrong sign numu CC - 1 pion neutral (mu+ + 1 pi0)
   ksNuMuCCWSgnoth   = 12, // wrong sign numu CC - other
   ksNuECC0pi        = 13, // nue CC - 0 pions (e)
   ksNuECC1piC       = 14, // nue CC - 0 pions (e + 1 pi+/-)
   ksNuECC1pi0       = 15, // nue CC - 0 pions (e + 1 pi0)
   ksNuECCoth        = 16, // nue CC - other
   ksNC0pi           = 17, // NC - 0 pions (nucleons)
   ksNC1piC          = 18, // NC - 1pi charge (1 pi+/-)
   ksNC1pi0          = 19, // NC - 1pi0 (1 pi0)
   ksNCoth           = 20, // NC - other
   ksNuEEL           = 21, // NuE elastic nue + e (kinematics to differentiate from ksNuECC0pi)
#ifndef VALOR_DUNE_FAR_DETECTOR
   ksInvMuDecay      = 22  // Inverse muon decay (nuebar + e -> mu + numubar)
#else
   ksInvMuDecay      = 22, // Inverse muon decay (nuebar + e -> mu + numubar)
   ksNuMuCClow,            // beam intrinsic numu 
   ksNuMuCChigh,           // beam intrinsic anti-numu 
   ksNuMuBarCClow,         // beam intrinsic numu 
   ksNuMuBarCChigh,        // beam intrinsic anti-numu 
   ksNuECClow,             // beam intrinsic numu 
   ksNuECChigh,            // beam intrinsic anti-numu 
   ksNuEBarCClow,          // beam intrinsic numu 
   ksNuEBarCChigh,         // beam intrinsic anti-numu 
   ksNuTauCClow,           // beam intrinsic numu 
   ksNuTauCChigh,          // beam intrinsic anti-numu 
   ksNuTauBarCClow,        // beam intrinsic numu 
   ksNuTauBarCChigh       // beam intrinsic anti-numu 
#endif
#else
   ksUndefined       = -1, 
   ksNuMuCC          =  0, // numu CC inclusive
   ksNuMuCC1trk0pi   =  1, // numu CC - 1 track QE-enhanced - 0 pions  (mu)
   ksNuMuCC2trk0pi   =  2, // numu CC - 2 track QE-enhanched - 0 pions (mu + proton)
   ksNuMuCC1piC      =  3, // numu CC - 2 track (mu + 1 pi+/-)
   ksNuMuCC2piC      =  4, // numu CC - 3 track (mu + 2 pi+/-)
   ksNuMuCC1pi0      =  5, // numu CC - 2 track (mu + 1 pi0)
   ksNuMuCC1piC1pi0  =  6, // numu CC - 3 track (mu + 1 pi+/- + 1pi0)
   ksNuMuCCoth       =  7, // numu CC - other
   ksNuECC           =  8, // nue CC
   ksNuMuCCWSgn      =  9, // wrong sign numu CC inclusive
   ksNC              = 10, // NC inclusive
   ksNC1piC,               // NC - 1pi+/-
   ksNC1pi0,               // NC - 1pi0
   ksNCoth                 // NC - other
#endif
} 
Sample_t; 

static const int kMaxNSamples = 35;

// 
// ...........................................................................
// Define the list of samples used in present analysis.
//
// Note: The order and position of samples in the array is important for other arrays. Maintain the not remove or re-arrange.
// If you want to remove a sample from the fit, just comment-out the corresponding line and replace with ksUndefined.
// kSample array elements that contain the ksUndefined flag are ignored.
//
// To add a new sample in the fit, do the following:
// - Edit Sample.cxx: Add a new case (for the new sample) is all switch statements and make sure the boundaries defined
//   in SampleFromInt() are correct.
// - Edit SampleReacMode.h: Add an entry for the new sample in each array (to define modes for the new sample etc)
// - Edit SampleKineBinning.h/cxx: Check that an appropriate binning scheme exists, and add a new case (for the new sample)
//   all switch statements.
// - Edit FitParams.h: Add instructions on how to apply systematics for the new sample 
// -
 
#ifdef VALOR_DUNE_FAR_DETECTOR
 static const int kNSamples = 34;
#elif defined(VALOR_DUNE_THIRD_PASS_THROUGH)
 static const int kNSamples = 22;
#else
 static const int kNSamples = 9;
#endif

// ---------------------------------------------------------------------
// NOTE:
// This is used to loop over all beam configurations / samples.
// Probably could be removed once we start using the Compound* classes
 static const Sample_t kSample[kNBeamConf][kNSamples] =
{
   // kbLBNF_FHC
   {
#ifdef VALOR_DUNE_THIRD_PASS_THROUGH
     ksNuMuCC1trk0pi,
     ksNuMuCC2trk0pi,
     ksNuMuCCNtrk0pi,
     ksNuMuCC3trkDelta,
     ksNuMuCC1piC,
     ksNuMuCC1pi0,
     ksNuMuCC1piC1pi0,
     ksNuMuCCoth,
     ksNuMuCCWSgn0pi,
     ksNuMuCCWSgn1piC,
     ksNuMuCCWSgn1pi0,
     ksNuMuCCWSgnoth,
     ksNuECC0pi,
     ksNuECC1piC,
     ksNuECC1pi0,
     ksNuECCoth,
     ksNC0pi,
     ksNC1piC,
     ksNC1pi0,
     ksNCoth,
     ksNuEEL,
#ifndef VALOR_DUNE_FAR_DETECTOR
     ksInvMuDecay
#else
     ksInvMuDecay,
     ksNuMuCClow,  
     ksNuMuCChigh,  
     ksNuMuBarCClow,  
     ksNuMuBarCChigh,   
     ksNuECClow,          
     ksNuECChigh,           
     ksNuEBarCClow,        
     ksNuEBarCChigh,     
     ksNuTauCClow,       
     ksNuTauCChigh,       
     ksNuTauBarCClow,     
     ksNuTauBarCChigh    
#endif
#else
     ksNuMuCC1trk0pi,
     ksNuMuCC2trk0pi,
     ksNuMuCC1piC,
     ksNuMuCC1pi0,
     ksNuMuCC1piC1pi0,
     ksNuMuCCoth,
     ksNuECC,
     ksNuMuCCWSgn,
     ksNC
#endif
   },

   {
#ifdef VALOR_DUNE_THIRD_PASS_THROUGH
     ksNuMuCC1trk0pi,
     ksNuMuCC2trk0pi,
     ksNuMuCCNtrk0pi,
     ksNuMuCC3trkDelta,
     ksNuMuCC1piC,
     ksNuMuCC1pi0,
     ksNuMuCC1piC1pi0,
     ksNuMuCCoth,
     ksNuMuCCWSgn0pi,
     ksNuMuCCWSgn1piC,
     ksNuMuCCWSgn1pi0,
     ksNuMuCCWSgnoth,
     ksNuECC0pi,
     ksNuECC1piC,
     ksNuECC1pi0,
     ksNuECCoth,
     ksNC0pi,
     ksNC1piC,
     ksNC1pi0,
     ksNCoth,
     ksNuEEL,
#ifndef VALOR_DUNE_FAR_DETECTOR
   ksInvMuDecay
#else
     ksInvMuDecay,
     ksNuMuCClow,  
     ksNuMuCChigh,  
     ksNuMuBarCClow,  
     ksNuMuBarCChigh,   
     ksNuECClow,          
     ksNuECChigh,           
     ksNuEBarCClow,        
     ksNuEBarCChigh,     
     ksNuTauCClow,       
     ksNuTauCChigh,       
     ksNuTauBarCClow,     
     ksNuTauBarCChigh    
#endif
#else
     ksNuMuCC1trk0pi,
     ksNuMuCC2trk0pi,
     ksNuMuCC1piC,
     ksNuMuCC1pi0,
     ksNuMuCC1piC1pi0,
     ksNuMuCCoth,
     ksNuECC,
     ksNuMuCCWSgn,
     ksNC
#endif
   }
};
// ---------------------------------------------------------------------


} // conv

namespace util {

  string         AsString         (conv::Sample_t s);
  string         AsStringTeX      (conv::Sample_t s, bool root = false);
  bool           IsCC             (conv::Sample_t s);
  bool           IsELike          (conv::Sample_t s);
  bool           IsNC             (conv::Sample_t s);
  bool           IsFar            (conv::Sample_t s);
  bool           IsFar            (int s);
  conv::Sample_t SampleFromInt    (int s);
  conv::Sample_t SampleFromString (std::string s);
  conv::Sample_t GetActiveSample  (int ibeam, int isample);
  
  // aliases AsString methods
  string  SampleAsString    (conv::Sample_t s);
  string  SampleAsStringTeX (conv::Sample_t s, bool root = false);
} // util
} // valor
  
#endif 

