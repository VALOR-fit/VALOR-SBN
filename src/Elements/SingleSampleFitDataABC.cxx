//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR group. All rights reserved.

*/
//________________________________________________________________________________________

#include <cassert>

#include "Elements/SingleSampleFitDataABC.h"

using namespace valor;

//________________________________________________________________________________________
SingleSampleFitDataABC::SingleSampleFitDataABC() :
FitDataABC()
{
  fDetector = conv::kdUndefined;
  fBeam     = conv::kbUndefined;
  fSample   = conv::ksUndefined;
}
//________________________________________________________________________________________
SingleSampleFitDataABC::~SingleSampleFitDataABC() 
{

}
//________________________________________________________________________________________
void SingleSampleFitDataABC::Configure(
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

