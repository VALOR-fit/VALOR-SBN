//____________________________________________________________________________
/*!

\class     valor::RFL

\brief     Pre-computed response function library for non-linear parameters
           of the VALOR/DUNE analysis.

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

// FMWK
#include "valor/Conventions/Constants.h"

// DUNE
#include "dune/Conventions/DuneBuild.h"
#include "dune/Conventions/ArrIdx.h"
#include "dune/Conventions/BeamConf.h"
#include "dune/Conventions/FitParam.h"
#include "dune/Conventions/ReacMode.h"
#include "dune/Conventions/Sample.h"
#include "dune/Utilities/KinematicBin.h"
#include "dune/Utilities/KinematicPoint.h"

namespace valor {
namespace util {

class DuneRFL {

public:

  DuneRFL();
  DuneRFL(conv::BeamConf_t b, conv::Sample_t s, int n_params, const conv::PhysParamId_t * param_ids);
 ~DuneRFL();

  // Define a dummy spline pointer to an object we know, so we can use its address as a special argument.
  static const TSpline * kNoSplineRequired;

  // And a flat spline object
  static const TSpline * kFlatSpline; //A flat spline that we'll use if we're missing RFs in testing versions
  
  void Print(std::ostream & stream) const;
  friend std::ostream & operator << (std::ostream & stream, const DuneRFL & rfl);
  
  const TSpline * GetSpline(
    conv::ReacMode_t m, conv::PhysParamId_t p,
    const util::KinematicBin & kb ) const;
    
  int Param2Idx(conv::PhysParamId_t p) const;
                      
  
  // Pattern for spline names.
  void SetSplineNamePattern(std::string pattern);
  
  // Get the name of the spline we're looking for
  TString BuildSplineName(conv::ReacMode_t m, conv::PhysParamId_t p,
                          const KinematicBin & kb) const;
                          
  // Read splines from config file
  bool Read (string file, Option_t * opt = 0);
  
  util::KinematicBin GetBin(const util::KinematicPoint & kp, conv::ReacMode_t m = conv::kmUndefined) const;
  
private:

  // Actual response function block
  // This is a vector, with one entry per SingleSampleModel specified.
  // Each entry be a big block, with dimensions [conv::kNReacModes][NFitParams][NBinsTrue1][NBinsTrue2][NBinsTrue3][NBinsObs1][NBinsObs2][NBinsObs3]
  const TSpline ** fSplines;
  UInt_t    fSplineBlockSize;
  
  // The spline indices
  inline int SplineIndex(const int& im, const int& ip, const util::KinematicBin & kb) const
  {
    return (kb.reco3 +
            kb.reco2 * fNBinsReco3 +
            kb.reco1 * fNBinsReco3*fNBinsReco2 +
            kb.true3 * fNBinsReco3*fNBinsReco2*fNBinsReco1 +
            kb.true2 * fNBinsReco3*fNBinsReco2*fNBinsReco1*fNBinsTrue3 +
            kb.true1 * fNBinsReco3*fNBinsReco2*fNBinsReco1*fNBinsTrue3*fNBinsTrue2 +
            kb.zone  * fNBinsReco3*fNBinsReco2*fNBinsReco1*fNBinsTrue3*fNBinsTrue2*fNBinsTrue1 +
            ip       * fNBinsReco3*fNBinsReco2*fNBinsReco1*fNBinsTrue3*fNBinsTrue2*fNBinsTrue1*fNBinZones +
            im       * fNBinsReco3*fNBinsReco2*fNBinsReco1*fNBinsTrue3*fNBinsTrue2*fNBinsTrue1*fNBinZones*fNParams);
  }
  
  // The beam and sample (used in spline names)
  conv::BeamConf_t fBeam;
  conv::Sample_t   fSample;
  
  // Details of binning
  int                   fNModes;        //
  conv::ReacMode_t *    fModes;         //[fNModes]
  int                   fNParams;       //
  conv::PhysParamId_t * fParams;        //[fParams]
  
  // These numbers store the largest number of bins for any mode
  int                         fNBinsTrue1;    //
  int                         fNBinsTrue2;    //
  int                         fNBinsTrue3;    //
  int                         fNBinsReco1;    //
  int                         fNBinsReco2;    //
  int                         fNBinsReco3;    //
  int                         fNBinZones;     //
  
  // Name for the splines (used in filename)
  TString fSplineNamePattern;
  
  // Array storing parameters mapped to indice within this object
  int fParam2Idx[conv::knppmax];
  
  // Check spline is positive
  bool CheckForNegativeValues(const TSpline * spl, conv::PhysParamId_t p) const;
};

std::ostream & operator << (std::ostream & stream, const DuneRFL & rfl);

}      // util namespace
}      // valor namespace

#endif 
