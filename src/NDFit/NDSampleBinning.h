//____________________________________________________________________________
/*!

\file      NDSampleBinning

\brief     Binning information for samples included in the ND fit.

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           George Christodoulou <georgios \at hep.ph.liv.ac.uk>
           University of Liverpool

           Nick Grant <n.grant \at lancaster.ac.uk>
           University of Lancaster

\created   March 20, 2014

\copyright (c) 2010-2014, The VALOR group

*/
//____________________________________________________________________________

#ifndef _valor_lbnx_nd_sample_binning_h_
#define _valor_lbnx_nd_sample_binning_h_

#include "NDFit/NDSample.h"

namespace valor {
namespace conv  {

static const int kNMaxBinZones = 4;

// ...........................................................................
// Binning in (Ereco,yreco) space for QE-like processes
//

static const int kNYrecoZonesQELike = 3;
static const int kNErecoBinsQELike = 6;
static const double kErecoBinEdgesQELike[kNYrecoZonesQELike][kNErecoBinsQELike+1] = 
  {
    //zone 1 in y_reco
    {0,  1.58,  2.05,  2.59,  3.13,  4.84,  100},

    //zone 2 in y_reco
    {0,  1.57,  2.05,  2.56,  3.13,  3.87,  100},

    //zone 3 in y_reco
    {0,  1.5,   2.05,  2.49,  3.13,  3.67,  100}
  };


static const int kNErecoZonesQELike = 3;
static const int kNYrecoBinsQELike = 6;
static const double kErecoBinEdgesQELike[kNErecoZonesQELike][kNYrecoBinsQELike+1] = 
  {
    //zone 1 in Ev_reco
    {0,  0.0231,  0.0451,  0.084,   0.128,  0.232,  1},

    //zone 2 in Ev_reco
    {0,  0.0219,  0.0451,  0.0784,  0.128,  0.213,  1},

    //zone 3 in Ev_reco
    {0,  0.0172,  0.0451,  0.0742,  0.128,  0.203,  1}
  };


// ...........................................................................
// Binning in (Ereco,yreco) space for CC 1 charged pion-like sample
//

static const int kNYrecoZonesCC1piC = 3;
static const int kNErecoBinsCC1piC = 6;
static const double kErecoBinEdgesCC1piC[kNYrecoZonesCC1piC][kNErecoBinsCC1piC+1] = 
  {
    //zone 1 in y_reco
    {0,  2.28,  2.77,  3.8,   7.58,  17,    100},

    //zone 2 in y_reco
    {0,  1.99,  2.77,  3.43,  7.58,  19.2,  100},

    //zone 3 in y_reco
    {0,  1.97,  2.77,  3.82,  7.58,  18.4,  100}
  };

static const int kNErecoZonesCC1piC = 3;
static const int kNYrecoBinsCC1piC = 6;
static const double kErecoBinEdgesCC1piC[kNErecoZonesCC1piC][kNYrecoBinsCC1piC+1] = 
  {
    //zone 1 in Ev_reco
    {0,  0.161,  0.203,  0.297,  0.41,  0.506,  1},

    //zone 2 in Ev_reco
    {0,  0.13,   0.203,  0.276,  0.41,  0.609,  1},

    //zone 3 in Ev_reco
    {0,  0.066,  0.203,  0.302,  0.41,  0.673,  1}
  };

// ...........................................................................
// Binning in (Ereco,yreco) space for CC other sample
//

static const int kNYrecoZonesCCoth = 3;
static const int kNErecoBinsCCoth = 6;
static const double kErecoBinEdgesCCoth[kNYrecoZonesCCoth][kNErecoBinsCCoth+1] = 
  {
    //zone 1 in y_reco
    {0,  2.2,   3.02,  4.07,  9.41,  20.7,  100},

    //zone 2 in y_reco
    {0,  2.07,  3.02,  4.14,  9.41,  19.4,  100},

    //zone 3 in y_reco
    {0,  2.37,  3.02,  4.27,  9.41,  19.4,  100}
  };


static const int kNErecoZonesCCoth = 3;
static const int kNYrecoBinsCCoth = 6;
static const double kErecoBinEdgesCCoth[kNErecoZonesCCoth][kNYrecoBinsCCoth+1] = 
  {
    //zone 1 in Ev_reco
    {0,  0.119,   0.197,  0.314,  0.466,  0.583,  1},

    //zone 2 in Ev_reco
    {0,  0.0916,  0.197,  0.324,  0.466,  0.651,  1},

    //zone 3 in Ev_reco
    {0,  0.0942,  0.197,  0.317,  0.466,  0.702,  1}
  };


// ...........................................................................
// Simple, unoptimized binning in (Ereco,yreco) space 
//

static const int kNErecoBinsSimple = 38;

static const double kErecoBinEdgesSimple[kNErecoBinsSimple+1] = 
{
    0.000,  0.400, 
    0.800,  1.000,  1.200,  1.400,  1.600,  1.800,  1.900,  2.000,  2.100,  2.200,  
    2.300,  2.400,  2.500,  2.600,  2.700,  2.800,  2.900,  3.000,  3.100,  3.200,  
    3.300,  3.400,  3.600,  3.800,  4.000,  4.200,  4.400,  4.600,  5.000,
    6.000,  7.000,  8.000,  9.000, 10.000, 15.000, 20.000, 50.000
};

static const int kNYrecoBinsSimple = 10;

static const double kYrecoBinEdgesSimple[kNYrecoBinsSimple+1] = 
{
    0.000,  0.100,  0.200,  0.300,  0.400,  0.500,  0.600,  0.700,  0.800,  0.900,
    1.000
};

// ...........................................................................
// Etrue binning
//

static const int    kNEtrueBins = 54;
static const double kMaxEtrue   = 100.;

static const double kEtrueBinEdges[kNEtrueBins+1] = 
{
    0.000,  0.400,  0.600,  0.800,  1.000,  1.100,  1.200,  1.300,  1.400,  1.500,
    1.600,  1.700,  1.800,  1.900,  2.000,  2.100,  2.200,  2.300,  2.400,  2.500,
    2.600,  2.700,  2.800,  2.900,  3.000,  3.100,  3.200,  3.300,  3.400,  3.500,
    3.600,  3.700,  3.800,  3.900,  4.000,  4.100,  4.200,  4.300,  4.400,  4.500,
    4.700,  5.000,  5.500,  6.000,  6.500,  7.000,  8.000,  9.000, 10.000, 15.000,
   20.000, 30.000, 40.000, 50.000,100.000
};


} // conv

//
// Associated utility functions
//

namespace util   {
   const int      NumEtrueBins  (conv::NDSample_t sample, int zone);
   const double * EtrueBinEdges (conv::NDSample_t sample, int zone);
   const int      NumErecoBins  (conv::NDSample_t sample, int zone);
   const double * ErecoBinEdges (conv::NDSample_t sample, int zone);
   const int      NumYrecoBins  (conv::NDSample_t sample, int zone);
   const double * YrecoBinEdges (conv::NDSample_t sample, int zone);
   const int      BinZone       (conv::NDSample_t sample, double enu_reco, double y_reco);

} // util

} // valor
  
#endif 

