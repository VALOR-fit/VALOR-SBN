//____________________________________________________________________________
/*!

\class     valor::NDRFL

\brief     Pre-computed response function library for non-linear parameters
           of the VALOR/DUNE ND analysis. Implemented as a singleton

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\created   September 16, 2015

\copyright (c) 2010-2015, The VALOR group.

*/
//____________________________________________________________________________

#ifndef __valor_dune_nd_response_function_library__
#define __valor_dune_nd_response_function_library__

#include <iostream>

#include <TSpline.h>

#include "Conventions/BeamConf.h"
#include "NDFit/NDArrIdx.h"
#include "NDFit/NDSample.h"
#include "NDFit/NDSampleBinning.h"
#include "NDFit/NDSampleModes.h"
#include "NDFit/NDFitParams.h"

using std::ostream;

namespace valor {

class NDRFL {

public:

  static NDRFL * Instance();
  
  void Print(ostream & stream) const;
  friend ostream & operator << (ostream & stream, const NDRFL & rfl);
  
private:

  NDRFL();
  NDRFL(const NDRFL &);
 ~NDRFL();

  static NDRFL * fInstance;

  // Actual response function
  // TSpline3 * fWght [conv::kNNDFitParams][conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones]; 

  struct Cleaner {
      void DummyMethodAndSilentCompiler() { }
      ~Cleaner() {
         if (NDRFL::fInstance !=0) {
            delete NDRFL::fInstance;
            NDRFL::fInstance = 0;
         }
      }
  };
  friend struct Cleaner;
};

ostream & operator<< (ostream & stream, const NDRFL & rfl);

}      // valor namespace

#endif 
