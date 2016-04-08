//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR group. All rights reserved.

*/
//________________________________________________________________________________________

#include <cassert>

#include "Elements/SingleSampleFitModelABC.h"

using namespace valor;

//________________________________________________________________________________________
SingleSampleFitModelABC::SingleSampleFitModelABC() :
FitModelABC()
{
  fDetector = conv::kdUndefined;
  fBeam     = conv::kbUndefined;
  fSample   = conv::ksUndefined;
  fKSp      = conv::kspUndefined;
}
//________________________________________________________________________________________
SingleSampleFitModelABC::~SingleSampleFitModelABC() 
{

}
//________________________________________________________________________________________
void SingleSampleFitModelABC::Configure(
  conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s, conv::KineSpace_t k)
{
  fDetector = d;
  fBeam     = b;
  fSample   = s;
  fKSp      = k;

  assert(fDetector != conv::kdUndefined );
  assert(fBeam     != conv::kbUndefined );
  assert(fSample   != conv::ksUndefined );
  assert(fKSp      != conv::kspUndefined);

}
//________________________________________________________________________________________

