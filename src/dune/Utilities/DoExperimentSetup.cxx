//________________________________________________________________________________________________________________________
/*

Copyright (c) 2010-2019, The VALOR Fitting Group, All Rights Reserved.

*/
//____________________________________________________________________________________________________________________

#include <algorithm>

// fmwk
#include "valor/Conventions/ExperimentSetup.h"

// dune
#include "dune/Conventions/SampleReacMode.h"
#include "dune/Utilities/DoExperimentSetup.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
bool valor::DoExperimentSetup()
{
  ExperimentSetup & es = *ExperimentSetup::MutableInstance();
  
#ifdef SBN
  es.fExperimentName = "SBN";
#elif defined(T2K)
  es.fExperimentName = "T2K";
#else
  es.fExperimentName = "DUNE";
#endif
  
  // Beam configurations
  for (int ib = 0 ; ib < kNBeamConf ; ib++) {
    es.fBeamConfs.push_back(kBeamConf[ib]);
  }
  
  // Samples per beam
  for (int ib = 0 ; ib < kNBeamConf ; ib++) {
    std::vector<Sample_t> samples;
    for (int is = 0 ; is < kNSamples ; is++) {
      samples.push_back(kSample[ib][is]);
    }
    es.fSamples.push_back(samples);
  }
  
  // Modes per beam, per sample
  for (int ib = 0 ; ib < kNBeamConf ; ib++) {
    std::vector<std::vector<ReacMode_t> > modes_per_sample;
    for (int is = 0 ; is < kNSamples ; is++) {
      std::vector<ReacMode_t> modes;
      for (int im = 0 ; im < kNReacModes ; im++) {
        modes.push_back(kReactionModes[is][im]);
      }
      modes_per_sample.push_back(modes);
    }
    es.fReactionModes.push_back(modes_per_sample);
  }
  
  // Coarse per beam, per sample
  for (int ib = 0 ; ib < kNBeamConf ; ib++) {
    std::vector<std::vector<ReacModeCoarse_t> > modes_per_sample;
    for (int is = 0 ; is < kNSamples ; is++) {
      std::vector<ReacModeCoarse_t> modes;
      for (int im = 0 ; im < kNReacModesCoarse ; im++) {
        modes.push_back(kReactionModesCoarse[ib][is][im]);
      }
      modes_per_sample.push_back(modes);
    }
    es.fReactionModesCoarse.push_back(modes_per_sample);
  }
  
  // Coarse per beam, per sample
  for (int ib = 0 ; ib < kNBeamConf ; ib++) {
    std::vector<std::vector<std::vector<int> > > styles_per_sample;
    for (int is = 0 ; is < kNSamples ; is++) {
      std::vector<std::vector<int> > styles_per_mode;
      for (int im = 0 ; im < kNReacModesCoarse ; im++) {
        std::vector<int> style_vec;
        // Hardcoded as line color, fill color, fill style
        style_vec.push_back(kReactionModesCoarseFormatting[ib][is][im][0]);
        style_vec.push_back(kReactionModesCoarseFormatting[ib][is][im][1]);
        style_vec.push_back(kReactionModesCoarseFormatting[ib][is][im][2]);
        styles_per_mode.push_back(style_vec);
      }
      styles_per_sample.push_back(styles_per_mode);
    }
    es.fPlotStyle.push_back(styles_per_sample);
  }
  
  es.fIsSetup = true;
  
  return es.fIsSetup;
}
//________________________________________________________________________________________
ExperimentInitialiser::ExperimentInitialiser()
{
  DoExperimentSetup();
}
//________________________________________________________________________________________
