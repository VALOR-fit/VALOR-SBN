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
}
//________________________________________________________________________________________
SingleSampleFitModelABC::~SingleSampleFitModelABC() 
{

}
//________________________________________________________________________________________
void SingleSampleFitModelABC::Configure(
  conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s)
{
  fDetector = d;
  fBeam     = b;
  fSample   = s;

  assert(fDetector != conv::kdUndefined);
  assert(fBeam     != conv::kbUndefined);
  assert(fSample   != conv::ksUndefined);
}
//________________________________________________________________________________________

