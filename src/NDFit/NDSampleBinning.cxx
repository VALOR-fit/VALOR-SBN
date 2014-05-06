//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include "NDFit/NDSampleBinning.h"

using namespace valor::lbnx;
using namespace valor::lbnx::conv;

//________________________________________________________________________________________
const int util::NumErecoBins(NDSample_t sample, int zone)
{
  switch(sample) 
  {
    case (ksNDNuMuCC) : 
    {
      return kNErecoBinsSimple;  
      break;
    }
    case (ksNDNuMuCC1Trk) : 
    {
      if(zone >=0 && zone < kNBinZonesQELike) 
        return kNErecoBinsQELike[zone]; 
      else 
        return 0;
      break;
    }
    default: 
      return 0;
  }//sample

  return 0;
}
//________________________________________________________________________________________
const double * util::ErecoBinEdges(NDSample_t sample, int zone)
{
  switch(sample) 
  {
    case (ksNDNuMuCC) : 
    {
      return kErecoBinEdgesSimple;  
      break;
    }
    case (ksNDNuMuCC1Trk) : 
    {
      if(zone >=0 && zone < kNBinZonesQELike) 
        return kErecoBinEdgesQELike[zone]; 
      else 
        return 0;
      break;
    }
    default: 
      return 0;
  }//sample

  return 0;
}
//________________________________________________________________________________________
const int util::NumYrecoBins(NDSample_t sample, int zone)
{
  switch(sample) 
  {
    case (ksNDNuMuCC) : 
    {
      return kNYrecoBinsSimple;  
      break;
    }
    case (ksNDNuMuCC1Trk) : 
    {
      if(zone >=0 && zone < kNBinZonesQELike) 
        return kNYrecoBinsQELike[zone]; 
      else 
        return 0;
      break;
    }
    default: 
      return 0;
  }//sample

  return 0;
}
//________________________________________________________________________________________
const double * util::YrecoBinEdges(NDSample_t sample, int zone)
{
  switch(sample) 
  {
    case (ksNDNuMuCC) : 
    {
      return kYrecoBinEdgesSimple;  
      break;
    }
    case (ksNDNuMuCC1Trk) : 
    {
      if(zone >=0 && zone < kNBinZonesQELike) 
        return kYrecoBinEdgesQELike[zone]; 
      else 
        return 0;
      break;
    }
    default: 
      return 0;
  }//sample

  return 0;
}
//________________________________________________________________________________________

	
