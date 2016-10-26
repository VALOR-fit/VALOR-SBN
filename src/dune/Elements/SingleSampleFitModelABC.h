//____________________________________________________________________________
/*!

\class     valor::SingleSampleFitModelABC

\brief     Abstract base class (pABC) for a single DUNE fit sample model

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\created   March 30, 2014

\copyright (c) 2010-2016, The VALOR group

*/
//____________________________________________________________________________

#ifndef _valor_single_sample_fit_model_abc_h_
#define _valor_single_sample_fit_model_abc_h_

// fmwk
#include "valor/FitCore/FitModelABC.h"
#include "valor/FitCore/CorrelatedSystematics.h"
// dune
#include "dune/Conventions/BeamConf.h"
#include "dune/Conventions/Sample.h"
#include "dune/Conventions/Detector.h"
#include "dune/Conventions/KineSpace.h"
#include "dune/Conventions/UniqueSampleID.h"

namespace valor {

class SingleSampleFitModelABC: public FitModelABC
{
public:
  virtual ~SingleSampleFitModelABC();

  void Configure(conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s, conv::KineSpace_t k);
  
  conv::Detector_t  GetDetector () const { return fDetector;}
  conv::BeamConf_t  GetBeam     () const { return fBeam;    }
  conv::Sample_t    GetSample   () const { return fSample;  }
  conv::KineSpace_t GetKineSpace() const { return fKSp;     }
  
  UniqueSampleID GetUniqueSampleID() const { return UniqueSampleID(fDetector,fBeam,fSample); }

protected:
  SingleSampleFitModelABC();

  // Configuration
  conv::Detector_t  fDetector;
  conv::BeamConf_t  fBeam;
  conv::Sample_t    fSample;
  conv::KineSpace_t fKSp;
  
};

} // valor

#endif

