//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include "Messenger/Messenger.h"
#include "NDFit/NDSampleBinning.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
const int util::NumEtrueBins(NDSample_t /*sample*/)
{
  return kNEtrueBins;
}
//________________________________________________________________________________________
const double * util::EtrueBinEdges(NDSample_t /*sample*/)
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
const int util::BinZone(NDSample_t sample, double enu_reco, double y_reco)
{
  LOG("NDBinning", pDEBUG) 
    << "Finding bin zone for enu_reco = " << enu_reco << " GeV, y_reco = " << y_reco 
    << " in sample: " << util::AsString(sample);

  for(int izone = 0; izone < kNMaxBinZones; izone++) {

     LOG("NDBinning",pDEBUG) << "Testing zone #" << izone;

     const int      n_enu_reco_bins    = util::NumErecoBins  (sample, izone);
     const int      n_y_reco_bins      = util::NumYrecoBins  (sample, izone);

     LOG("NDBinning",pDEBUG) << " - number of enu_reco bins = " << n_enu_reco_bins;
     LOG("NDBinning",pDEBUG) << " - number of y_reco bins   = " << n_y_reco_bins;

     const double * enu_reco_bin_edges = util::ErecoBinEdges (sample, izone);
     const double * y_reco_bin_edges   = util::YrecoBinEdges (sample, izone);

     LOG("NDBinning",pDEBUG) << " - min{enu_reco} = " << enu_reco_bin_edges [0] << " GeV";
     LOG("NDBinning",pDEBUG) << " - max{enu_reco} = " << enu_reco_bin_edges [n_enu_reco_bins] << " GeV";
     LOG("NDBinning",pDEBUG) << " - min{y_reco}   = " << y_reco_bin_edges   [0];
     LOG("NDBinning",pDEBUG) << " - max{y_reco}   = " << y_reco_bin_edges   [n_y_reco_bins];

     if ( enu_reco >= enu_reco_bin_edges [0]                &&
          enu_reco <= enu_reco_bin_edges [n_enu_reco_bins]  &&
          y_reco   >= y_reco_bin_edges   [0]                &&
          y_reco   <= y_reco_bin_edges   [n_y_reco_bins] 
        )
     {
       LOG("NDBinning",pDEBUG) << "Returning zone#" << izone;
       return izone;
     }
  }//izone

  return -1;
}
//________________________________________________________________________________________

	
