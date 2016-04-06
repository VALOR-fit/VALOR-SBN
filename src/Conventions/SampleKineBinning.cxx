//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include <cassert>
// root
#include <TMath.h>
// fmwk
#include "Messenger/Messenger.h"
// dune
#include "Conventions/SampleKineBinning.h"

using namespace valor;
using namespace valor::conv;

//
// Etrue, all binning schemes
//

//________________________________________________________________________________________
int util::NumEtrueBins(Sample_t /*sample*/)
{
  return kNEtrueBins;
}
//________________________________________________________________________________________
const double * util::EtrueBinEdges(Sample_t /*sample*/)
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
int util::NumYrecoBinsSb(Sample_t s)
{
   LOG("KBin",pDEBUG) 
     << "Getting # yreco bins for sample " << util::AsString(s);

  switch(s) 
  {
    case (ksNuMuCC1trkQE  ) :
    case (ksNuMuCC2trkQE  ) :
    case (ksNuMuCC1piC    ) :
    case (ksNuMuCC1pi0    ) :
    case (ksNuMuCC1piC1pi0) :
    case (ksNuMuCCoth     ) :
    case (ksNuECC         ) : 
    case (ksNuMuCCWSgn    ) : 
      return kNYrecoBinsCCSb; 
      break;

    case (ksNC            ) :
    case (ksNC1piC        ) :
    case (ksNC1pi0        ) :
    case (ksNCoth         ) :
      return kNYrecoBinsNCSb; 
      break;

    default: 
      return 0;
  }//s

  return 0;
}
//________________________________________________________________________________________
const double * util::YrecoBinEdgesSb(Sample_t s)
{
   LOG("KBin",pDEBUG) 
     << "Getting yreco bin edges (simple binning) for sample " << util::AsString(s);

  switch(s) 
  {
    case (ksNuMuCC1trkQE) : 
    case (ksNuMuCC2trkQE) : 
    {
      return kYrecoBinEdgesQELikeSb; 
      break;
    }
    case (ksNuMuCC1piC    ) :
    case (ksNuMuCC1pi0    ) :
    case (ksNuMuCC1piC1pi0) :
    case (ksNuMuCCoth     ) :
    case (ksNuECC         ) : 
    case (ksNuMuCCWSgn    ) : 
      return kYrecoBinEdgesMiscSb;  
      break;

    case (ksNC            ) :
    case (ksNC1piC        ) :
    case (ksNC1pi0        ) :
    case (ksNCoth         ) :
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
int util::NumErecoBins(Sample_t s, int zone)
{
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
   LOG("KBin",pDEBUG) 
     << "Getting # Ereco bins for sample " << util::AsString(s) << ", zone = " << zone;
#endif

#if defined _use_single_zone_optimized_binning_scheme_v1_ || defined _use_single_zone_optimized_binning_scheme_v2_

  return kNErecoBinsOb1Z;

#else

/*
  switch(s) 
  {
    case (ksNuMuCC1trkQE) : 
    {
      if(zone >=0 && zone < kNBinZonesQELike) 
        return kNErecoBinsQELike[zone]; 
      else 
        return 0;
      break;
    }
    case (ksNuMuCCoth) : 
    {
      return kNErecoBinsSimple;  
      break;
    }
    default: 
      return 0;
  }//s
*/

  return 0;

#endif
}
//________________________________________________________________________________________
const double * util::ErecoBinEdges(Sample_t s, int zone)
{
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
   LOG("KBin",pDEBUG) 
     << "Getting Ereco bin edges for sample " << util::AsString(s) << ", zone = " << zone;
#endif

#if defined _use_single_zone_optimized_binning_scheme_v1_ || defined _use_single_zone_optimized_binning_scheme_v2_

  return kErecoBinEdgesOb1Z;

#else

/*
  switch(s) 
  {
    case (ksNuMuCC1trkQE) : 
    {
      if(zone >=0 && zone < kNBinZonesQELike) 
        return kErecoBinEdgesQELike[zone]; 
      else 
        return 0;
      break;
    }
    case (ksNuMuCCoth) : 
    {
      return kErecoBinEdgesSimple;  
      break;
    }
    default: 
      return 0;
  }//s
*/

  return 0;

#endif
}
//________________________________________________________________________________________
int util::NumYrecoBins(Sample_t s, int zone)
{
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
   LOG("KBin",pDEBUG) 
     << "Getting # yreco bins for sample " << util::AsString(s) << ", zone = " << zone;
#endif

#if defined _use_single_zone_optimized_binning_scheme_v1_ || defined _use_single_zone_optimized_binning_scheme_v2_

  if      (util::IsCC(s)) return kNYrecoBinsCCOb1Z;
  else if (util::IsNC(s)) return kNYrecoBinsNCOb1Z;
  else                    return 0;

#else

/*
  switch(s) 
  {
    case (ksNuMuCC1trkQE) : 
    {
      if(zone >=0 && zone < kNBinZonesQELike) 
        return kNYrecoBinsQELike[zone]; 
      else 
        return 0;
      break;
    }
    case (ksNuMuCCoth) : 
    {
      return kNYrecoBinsSimple;  
      break;
    }
    default: 
      return 0;
  }//s
*/

  return 0;

#endif
}
//________________________________________________________________________________________
const double * util::YrecoBinEdges(Sample_t s, int zone)
{
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
   LOG("KBin",pDEBUG) 
     << "Getting yreco bin edges for sample " << util::AsString(s) << ", zone = " << zone;
#endif

#if defined _use_single_zone_optimized_binning_scheme_v1_ || defined _use_single_zone_optimized_binning_scheme_v2_

  if      (util::IsCC(s)) return kYrecoBinEdgesCCOb1Z;
  else if (util::IsNC(s)) return kYrecoBinEdgesNCOb1Z;
  else                    return 0;

#else

/*
  switch(s) 
  {
    case (ksNuMuCC1trkQE) : 
    {
      if(zone >=0 && zone < kNBinZonesQELike) 
        return kYrecoBinEdgesQELike[zone]; 
      else 
        return 0;
      break;
    }
    case (ksNuMuCCoth) : 
    {
      return kYrecoBinEdgesSimple;  
      break;
    }
    default: 
      return 0;
  }//s
*/

  return 0;

#endif
}
//________________________________________________________________________________________
int util::BinZone(Sample_t s, double enu_reco, double y_reco)
{
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
  LOG("KBin", pDEBUG) 
    << "Finding bin zone for enu_reco = " << enu_reco << " GeV, y_reco = " << y_reco 
    << " in sample: " << util::AsString(s);
#endif

  for(int izone = 0; izone < kNMaxBinZones; izone++) {

#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
     LOG("KBin",pDEBUG) << "Testing zone #" << izone;
#endif

     const int n_enu_reco_bins = util::NumErecoBins  (s, izone);
     const int n_y_reco_bins   = util::NumYrecoBins  (s, izone);

     assert(n_enu_reco_bins > 0);
     assert(n_y_reco_bins   > 0);
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
     LOG("KBin",pDEBUG) << " - number of enu_reco bins = " << n_enu_reco_bins;
     LOG("KBin",pDEBUG) << " - number of y_reco bins   = " << n_y_reco_bins;
#endif

     const double * enu_reco_bin_edges = util::ErecoBinEdges (s, izone);
     const double * y_reco_bin_edges   = util::YrecoBinEdges (s, izone);
     
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
     LOG("KBin",pDEBUG) << " - min{enu_reco} = " << enu_reco_bin_edges [0] << " GeV";
     LOG("KBin",pDEBUG) << " - max{enu_reco} = " << enu_reco_bin_edges [n_enu_reco_bins] << " GeV";
     LOG("KBin",pDEBUG) << " - min{y_reco}   = " << y_reco_bin_edges   [0];
     LOG("KBin",pDEBUG) << " - max{y_reco}   = " << y_reco_bin_edges   [n_y_reco_bins];
#endif

     if ( enu_reco >= enu_reco_bin_edges [0]                &&
          enu_reco <= enu_reco_bin_edges [n_enu_reco_bins]  &&
          y_reco   >= y_reco_bin_edges   [0]                &&
          y_reco   <= y_reco_bin_edges   [n_y_reco_bins] 
        )
     {
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
       LOG("KBin",pDEBUG) << "Returning zone#" << izone;
#endif
       return izone;
     }
  }//izone

  return -1;
}
//________________________________________________________________________________________
int util::ErecoBinContaining(conv::Sample_t s, double enu_reco, double y_reco)
{
  int bin_zone             = util::BinZone(s,enu_reco, y_reco);
  int nbins                = util::NumErecoBins   (s,bin_zone);
  const double * bin_edges = util::ErecoBinEdges  (s,bin_zone);
  return TMath::BinarySearch(1+nbins, bin_edges, enu_reco);
}
//________________________________________________________________________________________
int util::YrecoBinContaining(conv::Sample_t s, double enu_reco, double y_reco)
{
  int bin_zone             = util::BinZone(s,enu_reco, y_reco);
  int nbins                = util::NumYrecoBins   (s,bin_zone);
  const double * bin_edges = util::YrecoBinEdges  (s,bin_zone);
  return TMath::BinarySearch(1+nbins, bin_edges, y_reco);
}
//________________________________________________________________________________________
int util::EtrueBinContaining(conv::Sample_t s, double enu_true)
{
  int nbins                = util::NumEtrueBins   (s);
  const double * bin_edges = util::EtrueBinEdges  (s);
  return TMath::BinarySearch(1+nbins, bin_edges, enu_true);
}
//________________________________________________________________________________________
