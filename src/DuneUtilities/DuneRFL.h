//____________________________________________________________________________
/*!

\class     valor::RFL

\brief     Pre-computed response function library for non-linear parameters
           of the VALOR/DUNE ND analysis. Implemented as a singleton

\author    Steve Dennis <s.r.dennis \at University of Liverpool>
           University of Liverpool
           
           Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\created   April 7, 2016

\copyright (c) 2010-2016, The VALOR group.

*/
//____________________________________________________________________________

#ifndef __valor_dune_response_function_library__
#define __valor_dune_response_function_library__

#include <iostream>

#include <TSpline.h>

#include "Conventions/DuneBuild.h"

#include "Conventions/ArrIdx.h"
#include "Conventions/BeamConf.h"
#include "Conventions/FitParam.h"
#include "Conventions/ReacMode.h"
#include "Conventions/Sample.h"

#include "DuneUtilities/KinematicBin.h"

using std::ostream;

namespace valor {
namespace util {

class DuneRFL {

public:

  // Define a dummy spline object, so we can use its address as a special argument.
  //~ static const TSpline3 kDummySpline;
  //~ static const TSpline * kNoSplineRequired = &kDummySpline;

  // And a flat spline object
  static const TSpline * kFlatSpline; //A flat spline that we'll use if we're missing RFs in testing versions
  
  void Print(ostream & stream) const;
  friend ostream & operator << (ostream & stream, const DuneRFL & rfl);
  
  const TSpline * GetSpline(
    conv::ReacMode_t m, conv::PhysParamId_t p,
    const util::KinematicBin & kb ) const;
                      
  
  // Pattern for spline names.
  void SetSplineNamePattern(std::string);
  
  // Get the name of the spline we're looking for
  TString BuildSplineName(conv::BeamConf_t b, conv::Sample_t s, conv::ReacMode_t m,
                          conv::PhysParamId_t p, int bin_zone,
                          int true_bin1, int true_bin2,
                          int obs1_bin, int obs2_bin) const;
                          
  // Read splines from config file
  bool Read (string file, Option_t * opt = 0);
  
private:

  DuneRFL();
  DuneRFL(const DuneRFL &);
 ~DuneRFL();

  // Actual response function block
  // This is a vector, with one entry per SingleSampleModel specified.
  // Each entry be a big block, with dimensions [conv::kNReacModes][NFitParams][NBinsTrue1][NBinsTrue2][NBinsObs1][NBinsObs2]
  TSpline** fSplines;
  UInt_t    fSplineBlockSize;
    
  // Name for the splines (used in filename)
  TString fSplineNamePattern;
  
  // Details of binning
  int      kNBinsTrue1;
  double * kBinEdgesTrue1;
  int      kNBinsTrue2;
  double * kBinEdgesTrue2;
  int      kNBinsTrue3;
  double * kBinEdgesTrue3;
  int      kNBinsReco1;
  double * kBinEdgesReco1;
  int      kNBinsReco2;
  double * kBinEdgesReco2;
  int      kNBinsReco3;
  double * kBinEdgesReco3;
};

}      // util namespace
}      // valor namespace

#endif 
