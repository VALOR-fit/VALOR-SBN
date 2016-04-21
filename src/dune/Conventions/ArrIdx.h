//____________________________________________________________________________
/*!

\class     valor::util::ArrIdx

\brief     A simple helper singleton object that helps improve CPU-efficiency
           by working-out and storing the indices for various enumerations in
           various arrays used in this fit.

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

\created   March 27, 2014

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_array_index_h_
#define _valor_dune_array_index_h_

#include "Conventions/PhysParamId.h"

#include "dune/Conventions/BeamConf.h"
#include "dune/Conventions/Sample.h"
#include "dune/Conventions/ReacMode.h"
#include "dune/Conventions/SampleReacMode.h"
#include "dune/Conventions/FitParam.h"

using namespace valor;

namespace valor {
namespace util {

class ArrIdx {

public:
    static const ArrIdx * Instance();
    static       ArrIdx * MutableInstance();

    int BeamConfIdx (conv::BeamConf_t b)                   const { return fBeamConfIdx[b];    }
    int SampleIdx   (conv::BeamConf_t b, conv::Sample_t s) const { return fSampleIdx[b][s];   }
    int ReacModeIdx (conv::Sample_t s, conv::ReacMode_t m) const { return fReacModeIdx[s][m]; }
    int FitParamIdx (conv::PhysParamId_t p)                const { return fFitParamIdx[p];    }

private:

    ArrIdx();
    ArrIdx(const ArrIdx &) {}
   ~ArrIdx() {}

    void Init();

    int fBeamConfIdx [2*conv::kNBeamConf];                      ///< maps each beam configuration to a kBeamConf array index
    int fSampleIdx   [2*conv::kNBeamConf] [2*conv::kNSamples];  ///< maps each sample to a kSample array index
    int fReacModeIdx [2*conv::kNSamples][2*conv::kNReacModes];  ///< maps each mode of each sample to a kReactionModes array index (same for a given sample in any beam)
    int fFitParamIdx [2*conv::knppmax];                         ///< maps each physics param to a kFitParam array index

    static ArrIdx * fInstance;

    struct Cleaner {
      void DummyMethodAndSilentCompiler() { }
      ~Cleaner() {
         if (ArrIdx::fInstance !=0) {
            delete ArrIdx::fInstance;
            ArrIdx::fInstance = 0;
         }
      }
    };
    friend struct Cleaner;
};

} // util
} // valor

#endif

