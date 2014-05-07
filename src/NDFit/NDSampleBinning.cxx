//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include "NDFit/NDSampleBinning.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
const int util::NumEtrueBins(NDSample_t /*sample*/, int /*zone*/)
{
  return kNEtrueBins;
}
//________________________________________________________________________________________
const double * util::EtrueBinEdges(NDSample_t /*sample*/, int /*zone*/)
{
  return kEtrueBinEdges;
}
//________________________________________________________________________________________
const int util::NumErecoBins(NDSample_t sample, int zone)
{
  switch(sample) 
  {
    case (ksNDNuMuCC1trkQE) : 
    {
      if(zone >=0 && zone < kNBinZonesQELike) 
        return kNErecoBinsQELike[zone]; 
      else 
        return 0;
      break;
    }
    case (ksNDNuMuCCoth) : 
    {
      return kNErecoBinsSimple;  
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
    case (ksNDNuMuCC1trkQE) : 
    {
      if(zone >=0 && zone < kNBinZonesQELike) 
        return kErecoBinEdgesQELike[zone]; 
      else 
        return 0;
      break;
    }
    case (ksNDNuMuCCoth) : 
    {
      return kErecoBinEdgesSimple;  
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
    case (ksNDNuMuCC1trkQE) : 
    {
      if(zone >=0 && zone < kNBinZonesQELike) 
        return kNYrecoBinsQELike[zone]; 
      else 
        return 0;
      break;
    }
    case (ksNDNuMuCCoth) : 
    {
      return kNYrecoBinsSimple;  
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
    case (ksNDNuMuCC1trkQE) : 
    {
      if(zone >=0 && zone < kNBinZonesQELike) 
        return kYrecoBinEdgesQELike[zone]; 
      else 
        return 0;
      break;
    }
    case (ksNDNuMuCCoth) : 
    {
      return kYrecoBinEdgesSimple;  
      break;
    }
    default: 
      return 0;
  }//sample

  return 0;
}
//________________________________________________________________________________________

	
