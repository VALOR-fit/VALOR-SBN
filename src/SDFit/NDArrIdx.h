//____________________________________________________________________________
/*!

\class     valor::util::NDArrIdx

\brief     A simple helper singleton object that helps improve CPU-efficiency
           by working-out and storing the indices for various enumerations in
           various arrays used in this fit.

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

           Nick Grant <nick.grant \at stfc.ac.uk>
           University of Warwick

\created   March 27, 2014

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_nd_array_index_h_
#define _valor_dune_nd_array_index_h_

#include "Conventions/PhysParamId.h"
#include "Conventions/BeamConf.h"
#include "Conventions/Sample.h"
#include "Conventions/ReacMode.h"
#include "SDFit/NDBeamConf.h"
#include "SDFit/NDSampleModes.h"
#include "SDFit/NDFitParams.h"

using namespace valor;

namespace valor {
namespace util {

class NDArrIdx {

public:
    static const NDArrIdx * Instance();
    static       NDArrIdx * MutableInstance();

    int NDBeamConfIdx (conv::BeamConf_t b)                     const { return fNDBeamConfIdx[b];    }
    int NDSampleIdx   (conv::BeamConf_t b, conv::Sample_t s) const { return fNDSampleIdx[b][s];   }
    int NDReacModeIdx (conv::Sample_t s, conv::ReacMode_t m) const { return fNDReacModeIdx[s][m]; }
    int NDFitParamIdx (conv::PhysParamId_t p)                  const { return fNDFitParamIdx[p];    }

private:

    NDArrIdx();
    NDArrIdx(const NDArrIdx &) {}
   ~NDArrIdx() {}

    void Init();

    int fNDBeamConfIdx [2*conv::kNBeamConf];                        ///< maps each beam configuration to a kNDBeamConf array index
    int fNDSampleIdx   [2*conv::kNBeamConf] [2*conv::kNNDSamples];  ///< maps each sample to a kNDSample array index
    int fNDReacModeIdx [2*conv::kNNDSamples][2*conv::kNReacModes];  ///< maps each mode of each sample to a kNDReactionModes array index (same for a given sample in any beam)
    int fNDFitParamIdx [2*conv::knppmax];                           ///< maps each physics param to a kNDFitParam array index

    static NDArrIdx * fInstance;

    struct Cleaner {
      void DummyMethodAndSilentCompiler() { }
      ~Cleaner() {
         if (NDArrIdx::fInstance !=0) {
            delete NDArrIdx::fInstance;
            NDArrIdx::fInstance = 0;
         }
      }
    };
    friend struct Cleaner;
};

} // util
} // valor

#endif

