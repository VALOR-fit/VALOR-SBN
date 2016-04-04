//____________________________________________________________________________
/*!

\class     valor::NDRFL

\brief     Pre-computed response function library for non-linear parameters
           of the VALOR/DUNE ND analysis. Implemented as a singleton

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\created   September 16, 2015

\copyright (c) 2010-2016, The VALOR group.

*/
//____________________________________________________________________________

#ifndef __valor_dune_nd_response_function_library__
#define __valor_dune_nd_response_function_library__

#include <iostream>

#include <THashTable.h>
#include <TSpline.h>

#include "Conventions/BeamConf.h"
#include "Conventions/Sample.h"
#include "Conventions/ReacMode.h"

#include "SDFit/NDArrIdx.h"
#include "SDFit/NDSampleBinning.h"
#include "SDFit/NDSampleModes.h"
#include "SDFit/NDFitParams.h"

using std::ostream;

namespace valor {

class NDRFL {

public:

  static NDRFL * Instance();
  
  void Print(ostream & stream) const;
  friend ostream & operator << (ostream & stream, const NDRFL & rfl);
  
  TSpline * GetSpline(conv::BeamConf_t b, conv::Sample_t s, conv::ReacMode_t m,
                      conv::PhysParamId_t p, double true1, double obs1, double obs2=-999999) const;
  
  // Enable/Disable using the map lookup
  void SetSplineMapIsEnabled(bool if_enabled = true);
  
  // If we know that all of the bins have had their splines found
  // we can assume that a null spline in the map means no RF should be applied.
  void SetSplineMapIsComplete(bool if_complete = true);
  
  // Get the name of the spline we're looking for
  TString BuildSplineName(conv::BeamConf_t b, conv::Sample_t s, conv::ReacMode_t m,
                          conv::PhysParamId_t p, int true_bin, int obs1_bin, int obs2_bin = -999999) const;
                          
  // Read splines from config file
  bool Read (string file, Option_t * opt = 0);
  
private:

  NDRFL();
  NDRFL(const NDRFL &);
 ~NDRFL();

  static NDRFL * fInstance;
  
  //~ unsigned int fNNDIntDetParams;
  //~ conv::PhysParamId_t * fNDIntDetParams; // The non-flux ND params are those that can have RFs

  // Actual response function block
  TSpline ** fSplines; // This will be a big block, with dimensions [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNNDFitParams][conv::kNMaxBinsEr]
  
  TSpline * fFlatSpline; //A flat spline that we'll use if we're missing RFs in testing versions
  
  // Name for the splines (used in filename)
  std::string fTag;
  
  // The map we'll store our splines in
  mutable THashTable * fSplineMap;
  bool fSplineMapIsComplete;
  bool fSplineMapIsEnabled;

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
