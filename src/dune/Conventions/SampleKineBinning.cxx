//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include <cassert>
// root
#include <TMath.h>
// fmwk
#include "valor/Messenger/Messenger.h"
// dune
#include "dune/Conventions/SampleKineBinning.h"

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
int util::NumQ2trueBins(Sample_t /*sample*/, ReacMode_t mode)
{
  switch (mode) {
    case kmNuMuCCQE:
    case kmNuMuBarCCQE:
    case kmNuECCQE:
    case kmNuEBarCCQE:
      return conv::kNQ2trueBinsCCQE;
    case kmNuMuCC1piC:
    case kmNuMuBarCC1piC:
    case kmNuECC1piC:
    case kmNuEBarCC1piC:
      return kNQ2trueBinsCC1piC;
    case kmNuMuCC1pi0:
    case kmNuMuBarCC1pi0:
    case kmNuECC1pi0:
    case kmNuEBarCC1pi0:
      return kNQ2trueBinsCC1pi0;
    default:
      return kNQ2trueBinsOther;
  }
}
//________________________________________________________________________________________
const double * util::Q2trueBinEdges(Sample_t /*sample*/, ReacMode_t mode)
{
  switch (mode) {
    case kmNuMuCCQE:
    case kmNuMuBarCCQE:
    case kmNuECCQE:
    case kmNuEBarCCQE:
      return conv::kQ2trueBinEdgesCCQE;
    case kmNuMuCC1piC:
    case kmNuMuBarCC1piC:
    case kmNuECC1piC:
    case kmNuEBarCC1piC:
      return kQ2trueBinEdgesCC1piC;
    case kmNuMuCC1pi0:
    case kmNuMuBarCC1pi0:
    case kmNuECC1pi0:
    case kmNuEBarCC1pi0:
      return kQ2trueBinEdgesCC1pi0;
    default:
      return kQ2trueBinEdgesOther;
  }
}
//________________________________________________________________________________________

//
// .......................................................................................
// Simple binning scheme
// .......................................................................................
//

//________________________________________________________________________________________
int util::NumErecoBinsSb(Sample_t /*s*/)
{
  return conv::kNErecoBinsSb;
}
//________________________________________________________________________________________
const double * util::ErecoBinEdgesSb(Sample_t /*s*/)
{
  return conv::kErecoBinEdgesSb;
}
//________________________________________________________________________________________
int util::NumYrecoBinsSb(Sample_t s)
{
   LOG("KBin",pDEBUG) 
     << "Getting # yreco bins for sample " << util::AsString(s);

   if      (util::IsNC(s) || util::IsFar(s)) return kNYrecoBinsNCSb;
   else if (util::IsCC(s)) return kNYrecoBinsCCSb;
   else                    return 0;

   /*
  switch(s) 
  {
    case (ksNuMuCC0pi1trk ) :
    case (ksNuMuCC0pi2trk ) :
    case (ksNuMuCC1piC    ) :
    case (ksNuMuCC1pi0    ) :
    case (ksNuMuCC1piC1pi0) :
    case (ksNuMuCCoth     ) :
    case (ksNuMuCC0piNtrk ) :
    case (ksNuMuCC3trkDelta):
    case (ksNuMuCCWS0pi ) :   
    case (ksNuMuCCWS1piC) :   
    case (ksNuMuCCWS1pi0) :   
    case (ksNuMuCCWSoth ) :   
    case (ksNuECC0pi      ) : 
    case (ksNuECC1piC     ) : 
    case (ksNuECC1pi0     ) : 
    case (ksNuECCoth      ) : 
    case (ksNuECC         ) : 
    case (ksNuMuCCWS    ) : 
    case (ksNuMuCClow      ) :
    case (ksNuMuCChigh     ) :
    case (ksNuMuBarCClow   ) :
    case (ksNuMuBarCChigh  ) :
    case (ksNuECClow       ) :
    case (ksNuECChigh      ) :
    case (ksNuEBarCClow    ) :
    case (ksNuEBarCChigh   ) :
       return kNYrecoBinsCCSb; 
       break;

    case (ksNC1piC        ) :
    case (ksNC1pi0        ) :
    case (ksNCoth         ) :
    case (ksNC            ) :
      return kNYrecoBinsNCSb; 
      break;

    default: 
      return 0;
  }//s

  return 0;
   */
}
//________________________________________________________________________________________
const double * util::YrecoBinEdgesSb(Sample_t s)
{
  LOG("KBin",pDEBUG) 
    << "Getting yreco bin edges (simple binning) for sample " << util::AsString(s);

  if (util::IsNC(s) || util::IsFar(s)) {
    return kYrecoBinEdgesNCSb;
  }

  else if (util::IsCC(s)) {
    if (util::IsCCQELike(s)) {
      return kYrecoBinEdgesQELikeSb;
    }
    else {
      return kYrecoBinEdgesMiscSb;
    }
  }
  else {
    assert(!"YrecoBinEdgesSb not defined for sample"); return NULL;
  }
   
   /*
  switch(s) 
  {
    case (ksNuMuCC0pi1trk) : 
    case (ksNuMuCC0pi2trk) : 
    {
      return kYrecoBinEdgesQELikeSb; 
      break;
    }
    case (ksNuMuCC1piC    ) :
    case (ksNuMuCC1pi0    ) :
    case (ksNuMuCC1piC1pi0) :
    case (ksNuMuCCoth     ) :
    case (ksNuECC         ) : 
    case (ksNuMuCCWS    ) : 
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
   */
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

  if (util::IsFar(s)) {
    if (util::IsELike(s)) {return conv::kNErecoBinsFarELike ;}
    else                  {return conv::kNErecoBinsFarMuLike;}
  }

#if defined _use_single_zone_optimized_binning_scheme_v1_ || defined _use_single_zone_optimized_binning_scheme_v2_

  return kNErecoBinsOb1Z;

#else

/*
  switch(s) 
  {
    case (ksNuMuCC0pi1trk) : 
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

  if (util::IsFar(s)) {
    if (util::IsELike(s)) {return conv::kErecoBinEdgesFarELike ;}
    else                  {return conv::kErecoBinEdgesFarMuLike;}
  }

#if defined _use_single_zone_optimized_binning_scheme_v1_ || defined _use_single_zone_optimized_binning_scheme_v2_

  return kErecoBinEdgesOb1Z;

#else

/*
  switch(s) 
  {
    case (ksNuMuCC0pi1trk) : 
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

  if      (util::IsNC(s)||util::IsFar(s)) return kNYrecoBinsNCOb1Z;
  else if (util::IsCC(s)) return kNYrecoBinsCCOb1Z;
  else                    return 0;

#else

/*
  switch(s) 
  {
    case (ksNuMuCC0pi1trk) : 
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

   if          (util::IsNC(s)||util::IsFar(s)) return kYrecoBinEdgesNCOb1Z;
   else if     (util::IsCC(s)) return kYrecoBinEdgesCCOb1Z;
   else           return 0;

#else

/*
  switch(s) 
  {
    case (ksNuMuCC0pi1trk) : 
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
// Single Etrue bin for FSI splines.
int util::NumEtrueBinsXsec  (conv::Sample_t /*sample*/)
{
  return 1;
}
//________________________________________________________________________________________
const double * util::EtrueBinEdgesXsec (conv::Sample_t /*sample*/)
{
  static const double edges[2] = {0,1E10};
  return edges;
}
//________________________________________________________________________________________
// Just using the normal binning for now
int util::NumQ2trueBinsXsec (conv::Sample_t sample, conv::ReacMode_t mode)
{
  return util::NumQ2trueBins (sample,mode);
}
//________________________________________________________________________________________
const double * util::Q2trueBinEdgesXsec(conv::Sample_t sample, conv::ReacMode_t mode)
{
  return util::Q2trueBinEdges(sample,mode);
}
//________________________________________________________________________________________
int util::NumErecoBinsXsec  (conv::Sample_t sample, int zone)
{
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
   LOG("KBin",pDEBUG) 
     << "Getting # Ereco xsec bins for sample " << util::AsString(s) << ", zone = " << zone;
#endif

#if defined _use_single_zone_optimized_binning_scheme_v1_ || defined _use_single_zone_optimized_binning_scheme_v2_
  return kNErecoBinsOb1ZXsec;
#else
  return 0;
#endif
}
//________________________________________________________________________________________
const double * util::ErecoBinEdgesXsec (conv::Sample_t sample, int zone)
{
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
   LOG("KBin",pDEBUG) 
     << "Getting Ereco xsec bin edges for sample " << util::AsString(s) << ", zone = " << zone;
#endif

#if defined _use_single_zone_optimized_binning_scheme_v1_ || defined _use_single_zone_optimized_binning_scheme_v2_
  return kErecoBinEdgesOb1ZXsec;
#else
  return 0;
#endif
}
//________________________________________________________________________________________
int util::NumYrecoBinsXsec  (conv::Sample_t sample, int zone)
{
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
   LOG("KBin",pDEBUG) 
     << "Getting # yreco xsec bins for sample " << util::AsString(s) << ", zone = " << zone;
#endif

#if defined _use_single_zone_optimized_binning_scheme_v1_ || defined _use_single_zone_optimized_binning_scheme_v2_
   if (util::IsNC(sample) || util::IsFar(sample)) return kNYrecoBinsNCOb1ZXsec;
   else if      (util::IsCC(sample)) return kNYrecoBinsCCOb1ZXsec; 
   else                         return 0;
#else
  return 0;
#endif
}
//________________________________________________________________________________________
const double * util::YrecoBinEdgesXsec (conv::Sample_t sample, int zone)
{
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
   LOG("KBin",pDEBUG) 
     << "Getting yreco xsec bin edges for sample " << util::AsString(s) << ", zone = " << zone;
#endif

#if defined _use_single_zone_optimized_binning_scheme_v1_ || defined _use_single_zone_optimized_binning_scheme_v2_
   if (util::IsNC(sample)||util::IsFar(sample)) return kYrecoBinEdgesNCOb1ZXsec;
   else if      (util::IsCC(sample)) return kYrecoBinEdgesCCOb1ZXsec; 
   else                         return 0;
#else
  return 0;
#endif
}
//________________________________________________________________________________________
