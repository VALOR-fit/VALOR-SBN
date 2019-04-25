//____________________________________________________________________________
/*!

\file      FitParams

\brief     Typedef specific systematics to free PhysParamId_t slots
           of the VALOR framework

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

\created   March 20, 2014

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_fit_param_definition_h_
#define _valor_dune_fit_param_definition_h_

#include <string>
#include <utility>

//fmwk
#include "valor/Conventions/PhysParamId.h"
#include "valor/Conventions/Detector.h"
#include "valor/Conventions/BeamConf.h"
#include "valor/FitCore/CorrelatedSystematics.h"
#include "valor/FitCore/FitParamList.h"
#include "valor/FitCore/PhysHypothesis.h"

//dune
#include "dune/Conventions/DuneBuild.h"
#include "valor/Conventions/ReacMode.h"
#include "dune/Conventions/FitParamGroup.h"

#include "dune/Conventions/SampleKineBinning.h"

using std::string;

namespace valor {
namespace util {
  // If you give a CorrelatedSystematics object, it'll ignore your list's standard systematics and use this set instead
  FitParamList * GetFitParameterList (Option_t * param_list = "standard", const CorrelatedSystematics * syst = 0);


  conv::FitParamGroup_t GetParameterGroup(conv::PhysParamId_t p);
  // Get the list of parameters associated with a set name (eg flux, int, ccqe, fsi, 3fosc)
  std::vector<conv::PhysParamId_t> GetParameterSet(std::string set_name);

  std::pair<double,double> GetKineRange(conv::PhysParamId_t p, conv::KineVar_t k);

  // Does the input parameter depend on any kine var?
  bool HasKinematicDependence(conv::PhysParamId_t p);

  // Get a vector of osc + syst params from the PhysHypothesis and ParameterPool
  std::vector<conv::PhysParamId_t> GetActiveParameters(const PhysHypothesis & ph);

} //util

} // valor

#endif

