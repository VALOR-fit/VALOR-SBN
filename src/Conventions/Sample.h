//____________________________________________________________________________
/*!

\class     valor::conv::Sample_t

\brief     Enumeration of DUNE ND systematic constraint samples

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

#include "Conventions/BeamConf.h"

using std::string;

namespace valor {
namespace conv {

// ...........................................................................
// Define samples
//
typedef enum ESample 
{
   ksUndefined = -1, 
   ksNuMuCC,          // numu CC inclusive
   ksNuMuCC1trkQE,    // numu CC - 1 track QE-enhanced  (mu)
   ksNuMuCC2trkQE,    // numu CC - 2 track QE-enhanched (mu + proton)
   ksNuMuCC1piC,      // numu CC - 2 track (mu + 1 pi+/-)
   ksNuMuCC2piC,      // numu CC - 3 track (mu + 2 pi+/-)
   ksNuMuCC1pi0,      // numu CC - 2 track (mu + 1 pi0)
   ksNuMuCC1piC1pi0,  // numu CC - 3 track (mu + 1 pi+/- + 1pi0)
   ksNuMuCCoth,       // numu CC - other
   ksNuECC,           // nue CC
   ksNuMuCCWSgn,      // wrong sign numu CC inclusive
   ksNC,              // NC inclusive
   ksNC1piC,          // NC - 1pi+/-
   ksNC1pi0,          // NC - 1pi0
   ksNCoth            // NC - other
} 
Sample_t; 

static const int kMaxNSamples = 14;

// 
// ...........................................................................
// Define the list of samples used in present analysis.
//
// Note: The order and position of samples in the array is important for other arrays. Maintain the not remove or re-arrange.
// If you want to remove a sample from the fit, just comment-out the corresponding line and replace with ksUndefined.
// kNDSample array elements that contain the ksUndefined flag are ignored.
//
// To add a new sample in the fit, do the following:
// - Edit NDSample.cxx: Add a new case (for the new sample) is all switch statements and make sure the boundaries defined
//   in SampleFromInt() are correct.
// - Edit NDSampleModes.h: Add an entry for the new sample in each array (to define modes for the new sample etc)
// - Edit NDSampleBinning.h/cxx: Check that an appropriate binning scheme exists, and add a new case (for the new sample)
//   all switch statements.
// - Edit NDFitParams.h: Add instructions on how to apply systematics for the new sample 
// -

static const int kNNDSamples = 9; 

static const Sample_t kNDSample[kNBeamConf][kNNDSamples] =
{
   // kbFHC
   {
      ksNuMuCC1trkQE,
      ksNuMuCC2trkQE, 
      ksNuMuCC1piC,
      ksNuMuCC1pi0,
      ksNuMuCC1piC1pi0,
      ksNuMuCCoth,
      ksNuECC,
      ksNuMuCCWSgn,
      ksNC
   },

   // kbRHC 
   {
      ksNuMuCC1trkQE,
      ksNuMuCC2trkQE, 
      ksNuMuCC1piC,
      ksNuMuCC1pi0,
      ksNuMuCC1piC1pi0,
      ksNuMuCCoth,
      ksNuECC,
      ksNuMuCCWSgn,
      ksNC
   }
};


} // conv

namespace util {

  string         AsString         (conv::Sample_t s);
  string         AsStringTeX      (conv::Sample_t s, bool root = false);
  bool           IsCC             (conv::Sample_t s);
  bool           IsNC             (conv::Sample_t s);
  conv::Sample_t SampleFromInt    (int s);
  conv::Sample_t SampleFromString (std::string s);
  
  // aliases AsString methods
  string  SampleAsString    (conv::Sample_t s);
  string  SampleAsStringTeX (conv::Sample_t s, bool root = false);
} // util
} // valor
  
#endif 

