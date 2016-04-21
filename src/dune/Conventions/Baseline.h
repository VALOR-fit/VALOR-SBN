//____________________________________________________________________________
/*!

\class     valor::conv::

\brief     Beam configuration enumeration

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory
          
\created   April 15, 2014

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_expt_baseline_h_
#define _valor_expt_baseline_h_

#include "dune/Conventions/BeamConf.h"
#include "dune/Conventions/Detector.h"

namespace valor {
namespace conv {

//
// Baselines
//
static const double kJPARCTgt2SuperK =  295.000;  // km
static const double kJPARCTgt2ND280  =    0.280;  // km
static const double kLBNFTgt2DUNEFD  = 1300.000;  // km
static const double kLBNFTgt2DUNEND  =    0.547;  // km

} // conv

//
// Associated utilities
//
namespace util {

  double Baseline(conv::BeamConf_t b, conv::Detector_t d);

} // util

} // valor
  
#endif 

