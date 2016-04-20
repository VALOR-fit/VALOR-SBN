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
#include "Conventions/Constants.h"
#include "Conventions/FitParam.h"
#include "Conventions/ReacMode.h"
#include "Conventions/Sample.h"

#include "DuneUtilities/KinematicBin.h"
#include "DuneUtilities/KinematicPoint.h"

namespace valor {
namespace util {

class DuneRFL {

public:

  DuneRFL();
  DuneRFL(conv::BeamConf_t b, conv::Sample_t s, int n_params, const conv::PhysParamId_t * param_ids);

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
  void SetSplineNamePattern(std::string);
  
  // Get the name of the spline we're looking for
  TString BuildSplineName(conv::ReacMode_t m, conv::PhysParamId_t p,
                          const KinematicBin & kb) const;
                          
  // Read splines from config file
  bool Read (string file, Option_t * opt = 0);
  
  util::KinematicBin GetBin(const util::KinematicPoint & kp) const;
  
private:

 ~DuneRFL();

  // Actual response function block
  // This is a vector, with one entry per SingleSampleModel specified.
  // Each entry be a big block, with dimensions [conv::kNReacModes][NFitParams][NBinsTrue1][NBinsTrue2][NBinsTrue3][NBinsObs1][NBinsObs2][NBinsObs3]
  TSpline** fSplines;
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
  int                         fNModes;        //
  const conv::ReacMode_t *    fModes;         //[fNModes]
  int                         fNParams;       //
  const conv::PhysParamId_t * fParams;        //[fParams]
  int                         fNBinsTrue1;    //
  const double *              fBinEdgesTrue1; //[fNBinsTrue1]
  int                         fNBinsTrue2;    //
  const double *              fBinEdgesTrue2; //[fNBinsTrue2]
  int                         fNBinsTrue3;    //
  const double *              fBinEdgesTrue3; //[fNBinsTrue3]
  int                         fNBinsReco1;    //
  const double *              fBinEdgesReco1; //[fNBinsReco1]
  int                         fNBinsReco2;    //
  const double *              fBinEdgesReco2; //[fNBinsReco2]
  int                         fNBinsReco3;    //
  const double *              fBinEdgesReco3; //[fNBinsReco3]
  int                         fNBinZones;     //
  const double *              fBinZones;      //[fNBinZones]
  
  // Name for the splines (used in filename)
  TString fSplineNamePattern;
};

std::ostream & operator << (std::ostream & stream, const DuneRFL & rfl);

}      // util namespace
}      // valor namespace

#endif 
