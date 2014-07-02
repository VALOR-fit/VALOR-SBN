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

//
// Etrue, all binning schemes
//

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

//
// .......................................................................................
// Simple binning scheme
// .......................................................................................
//

//________________________________________________________________________________________
const int util::NumYrecoBinsSb(NDSample_t s)
{
   LOG("NDBinning",pDEBUG) 
     << "Getting # yreco bins for sample " << util::AsString(s);

  switch(s) 
  {
    case (ksNDNuMuCC1trkQE  ) :
    case (ksNDNuMuCC2trkQE  ) :
    case (ksNDNuMuCC1piC    ) :
    case (ksNDNuMuCC1pi0    ) :
    case (ksNDNuMuCC1piC1pi0) :
    case (ksNDNuMuCCoth     ) :
    case (ksNDNuECC         ) : 

      return kNYrecoBinsCCSb; 
      break;

    case (ksNDNC            ) :
    case (ksNDNC1pi0        ) :

      return kNYrecoBinsNCSb; 
      break;

    default: 
      return 0;
  }//s

  return 0;
}
//________________________________________________________________________________________
const double * util::YrecoBinEdgesSb(NDSample_t s)
{
   LOG("NDBinning",pDEBUG) 
     << "Getting yreco bin edges (simple binning) for sample " << util::AsString(s);

  switch(s) 
  {
    case (ksNDNuMuCC1trkQE) : 
    case (ksNDNuMuCC2trkQE) : 
    {
      return kYrecoBinEdgesQELikeSb; 
      break;
    }
    case (ksNDNuMuCC1piC    ) :
    case (ksNDNuMuCC1pi0    ) :
    case (ksNDNuMuCC1piC1pi0) :
    case (ksNDNuMuCCoth     ) :
    case (ksNDNuECC         ) : 
      return kYrecoBinEdgesMiscSb;  
      break;

    case (ksNDNC            ) :
    case (ksNDNC1pi0        ) :
      return kYrecoBinEdgesNCSb;  
      break;

    default: 
      return 0;
  }//s

  return 0;
}
//________________________________________________________________________________________

//
// .......................................................................................
// Optimized binning scheme
// .......................................................................................
//

//________________________________________________________________________________________
const int util::NumErecoBins(NDSample_t s, int zone)
{
   LOG("NDBinning",pDEBUG) 
     << "Getting # Ereco bins for sample " << util::AsString(s) << ", zone = " << zone;

#ifdef _use_very_few_ereco_yreco_bins_
  return kNErecoBins1;
#else

  switch(s) 
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
  }//s

  return 0;

#endif
}
//________________________________________________________________________________________
const double * util::ErecoBinEdges(NDSample_t s, int zone)
{
   LOG("NDBinning",pDEBUG) 
     << "Getting Ereco bin edges for sample " << util::AsString(s) << ", zone = " << zone;

#ifdef _use_very_few_ereco_yreco_bins_
  return kErecoBinEdges1;
#else

  switch(s) 
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
  }//s

  return 0;

#endif
}
//________________________________________________________________________________________
const int util::NumYrecoBins(NDSample_t s, int zone)
{
   LOG("NDBinning",pDEBUG) 
     << "Getting # yreco bins for sample " << util::AsString(s) << ", zone = " << zone;

#ifdef _use_very_few_ereco_yreco_bins_
  return kNYrecoBins1;
#else

  switch(s) 
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
  }//s

  return 0;

#endif
}
//________________________________________________________________________________________
const double * util::YrecoBinEdges(NDSample_t s, int zone)
{
   LOG("NDBinning",pDEBUG) 
     << "Getting yreco bin edges for sample " << util::AsString(s) << ", zone = " << zone;

#ifdef _use_very_few_ereco_yreco_bins_
  return kYrecoBinEdges1;
#else

  switch(s) 
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
  }//s

  return 0;

#endif
}
//________________________________________________________________________________________
const int util::BinZone(NDSample_t s, double enu_reco, double y_reco)
{
  LOG("NDBinning", pDEBUG) 
    << "Finding bin zone for enu_reco = " << enu_reco << " GeV, y_reco = " << y_reco 
    << " in sample: " << util::AsString(s);

  for(int izone = 0; izone < kNMaxBinZones; izone++) {

     LOG("NDBinning",pDEBUG) << "Testing zone #" << izone;

     const int      n_enu_reco_bins    = util::NumErecoBins  (s, izone);
     const int      n_y_reco_bins      = util::NumYrecoBins  (s, izone);

     LOG("NDBinning",pDEBUG) << " - number of enu_reco bins = " << n_enu_reco_bins;
     LOG("NDBinning",pDEBUG) << " - number of y_reco bins   = " << n_y_reco_bins;

     const double * enu_reco_bin_edges = util::ErecoBinEdges (s, izone);
     const double * y_reco_bin_edges   = util::YrecoBinEdges (s, izone);

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

	
