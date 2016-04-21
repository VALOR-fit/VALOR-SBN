//____________________________________________________________________________
/*!

\file      SampleKineBinning

\brief     Kinematical variable binning information for DUNE samples.

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

\created   March 20, 2014

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_sample_kine_binning_h_
#define _valor_dune_sample_kine_binning_h_

// The following flag replaces the optimized Ereco,yreco binning scheme with 
// just a few very wide bins to dramatically decrease the fit time for testing purposes.
// NOTE: Do not remove this, unless you also make sure that all functions defined
// here handle all samples currently installed in the fit. Last I looked they weren't.
#define _use_single_zone_optimized_binning_scheme_v1_ 
//#define _use_single_zone_optimized_binning_scheme_v2_ 

#include "Conventions/KineVar.h"
#include "Conventions/ReacMode.h"
#include "Conventions/Sample.h"

namespace valor {
namespace conv  {

// ...........................................................................
// 
// Define fit distributions (reco. quantities) for all samples.
// The corresponding MC templates used for constructing the p.d.fs will 
//

const int kMCTemplateNdimMax  = 3; // (current) maximum dimensionality for MC templates
const int kFitSpectrumNdimMax = 2; // (current) maximum dimensionality for fit distributions

// Define dimensionality of MC templates
static const int kMCTemplateNdim[kNSamples] =
{
   3, // ksNuMuCC1trkQE
   3, // ksNuMuCC2trkQE
   3, // ksNuMuCC1piC
   3, // ksNuMuCC1pi0
   3, // ksNuMuCC1piC1pi0
   3, // ksNuMuCCoth
   3, // ksNuECC
   3, // ksNuMuCCWSgn
   2  // ksNC
};

// Define dimensionality of fit distributions
static const int kFitSpectrumNdim[kNSamples] =
{
   2, // ksNuMuCC1trkQE
   2, // ksNuMuCC2trkQE
   2, // ksNuMuCC1piC
   2, // ksNuMuCC1pi0
   2, // ksNuMuCC1piC1pi0
   2, // ksNuMuCCoth
   2, // ksNuECC
   2, // ksNuMuCCWSgn
   1  // ksNC
};

// Define variables entering in MC template definitions.
// Variable subset {0 -> kFitSpectrumNdim[isample]} is the one entering in PDF definitions.
static const KineVar_t kSampleKineVars[kNSamples][kMCTemplateNdimMax] =
{
   { kvEreco, kvYreco, kvEtrue },     // ksNuMuCC1trkQE
   { kvEreco, kvYreco, kvEtrue },     // ksNuMuCC2trkQE
   { kvEreco, kvYreco, kvEtrue },     // ksNuMuCC1piC
   { kvEreco, kvYreco, kvEtrue },     // ksNuMuCC1pi0
   { kvEreco, kvYreco, kvEtrue },     // ksNuMuCC1piC1pi0
   { kvEreco, kvYreco, kvEtrue },     // ksNuMuCCoth
   { kvEreco, kvYreco, kvEtrue },     // ksNuECC
   { kvEreco, kvYreco, kvEtrue },     // ksNuMuCCWSgn
   { kvEvis,  kvEtrue, kvUndefined }  // ksNC
};


// ...........................................................................
// 
// Parameter ranges (same for all binning schemes)
//
static const double kEtrueMin  = 0.;
static const double kEtrueMax  = 120.;
static const double kQ2trueMin = 0;
static const double kQ2trueMax = 1E6; //<-- should probably be changed
static const double kErecoMin  = 0.;
static const double kErecoMax  = 120.;
static const double kYrecoMin  = 0.;
static const double kYrecoMax  = 1.;

// ...........................................................................
// 
// Etrue binning: 
// For simplicity, both the "simple" (for plots) and "optimized" (for fit)
// Ereco,yreco binning use the exact same Etrue binning.
// Take notice of Etrue range boundaries of fit parameter boundaries 
// when setting Etrue bin edges for the MC templates. An integral number of MC
// template bins should fit within the Etrue range of all fit parameters.
//

/*
// Initial binning
static const int    kNEtrueBins = 52;
static const double kEtrueBinEdges[kNEtrueBins+1] = 
{
    0.000,  0.500,  1.000,  1.200,  1.400,  1.500,  1.600,  1.700,  1.800,  1.900,  
    2.000,  2.100,  2.200,  2.300,  2.400,  2.500,  2.600,  2.700,  2.800,  2.900,  
    3.000,  3.100,  3.200,  3.300,  3.400,  3.500,  3.600,  3.700,  3.800,  3.900,  
    4.000,  4.100,  4.200,  4.300,  4.400,  4.500,  4.700,  5.000,  5.500,  6.000,  
    6.500,  7.000,  8.000,  9.000, 10.000, 
   12.000, 16.000, 20.000, 25.000, 30.000, 40.000, 50.000,  kEtrueMax
};
*/

// Revised binning:
// Using Etrue bins that match exactly the bins used for flux normalization error
static const int    kNEtrueBins = 19;
static const double kEtrueBinEdges[kNEtrueBins+1] = 
{
    0.000,  0.500,  1.000,  1.500,  2.000,  2.500,  3.000,  3.500, 4.000, 4.500, 5.000,
    5.500,  6.000,  7.000,  8.000, 12.000, 16.000, 20.000, 40.000, kEtrueMax
};

// Q2 bins
//~ static const int kNQ2trueBins = 1;
//~ static const double kQ2trueBinEdges[kNQ2trueBins+1] = 
//~ {
  //~ 0.0,kQ2trueMax // Dummy binning
//~ };

static const int kNQ2trueBinsCCQE = 3;
static const double kQ2trueBinEdgesCCQE[kNQ2trueBinsCCQE+1] = 
{
  0.0,0.2,0.55,kQ2trueMax
};

static const int kNQ2trueBinsCC1piC = 3;
static const double kQ2trueBinEdgesCC1piC[kNQ2trueBinsCC1piC+1] = 
{
  0.0,0.3,0.8,kQ2trueMax
};

static const int kNQ2trueBinsCC1pi0 = 3;
static const double kQ2trueBinEdgesCC1pi0[kNQ2trueBinsCC1pi0+1] = 
{
  0.0,0.35,0.9,kQ2trueMax
};

static const int kNQ2trueBinsOther = 1;
static const double kQ2trueBinEdgesOther[kNQ2trueBinsOther+1] = 
{
  0.0,kQ2trueMax
};


// ...........................................................................
//
// Simple (~fine and ~regular) binning in (Ereco,yreco) space
// These are not optimised to reduce the CPU-intensity of the fit and are 
// employed in MC templates and PDF used only for graphical representation
// of fit results
//

static const int    kNErecoBinsSb  = 101;
static const double kErecoBinEdgesSb [kNErecoBinsSb+1] =
{
   0.0,   0.2,   0.4,   0.6,   0.8,   1.0,   1.2,   1.4,   1.6,   1.8, 
   2.0,   2.2,   2.4,   2.6,   2.8,   3.0,   3.2,   3.4,   3.6,   3.8, 
   4.0,   4.2,   4.4,   4.6,   4.8,   5.0,   5.2,   5.4,   5.6,   5.8,
   6.0,   6.2,   6.4,   6.6,   6.8,   7.0,   7.2,   7.4,   7.6,   7.8,
   8.0,   8.2,   8.4,   8.6,   8.8,   9.0,   9.2,   9.4,   9.6,   9.8,
  10.0,  10.2,  10.4,  10.6,  10.8,  11.0,  11.2,  11.4,  11.6,  11.8,
  12.0,  12.2,  12.4,  12.6,  12.8,  13.0,  13.2,  13.4,  13.6,  13.8,
  14.0,  14.2,  14.4,  14.6,  14.8,  15.0,  15.2,  15.4,  15.6,  15.8,
  16.0,  16.2,  16.4,  16.6,  16.8,  17.0,  17.2,  17.4,  17.6,  17.8,
  18.0,  18.2,  18.4,  18.6,  18.8,  19.0,  19.2,  19.4,  19.6,  19.8,
  20.0, kErecoMax
};

static const int kNYrecoBinsCCSb = 6;
static const int kNYrecoBinsNCSb = 1;

// yreco binning for CC QE-like samples
static const double kYrecoBinEdgesQELikeSb [kNYrecoBinsCCSb+1] =
{
   0.000, 0.010, 0.020, 0.040, 0.070, 0.200, 1.000 
};
// yreco binning for other CC samples
static const double kYrecoBinEdgesMiscSb [kNYrecoBinsCCSb+1] =
{
   0.000, 0.050, 0.100, 0.200, 0.400, 0.600, 1.000 
};
// yreco binning for NC samples - yreco not defined so use [0,1]
static const double kYrecoBinEdgesNCSb [kNYrecoBinsNCSb+1] =
{
   0.000, 1.000 
};

// ...........................................................................
//
// Variable binning schemes in (Ereco,yreco) space optimised to reduce the 
// CPU-intensity of the fit. Typically, a number of bin zones are defined
// and a different variable-size binning scheme is used in each zone.
// - Note: The granularity of the binning scheme depends on the Ereco and yreco
// dependencies of systematic errors intended to be applied to the MC templates.
// Make sure that full bins below are included within the Ereco and yreco
// ranges where particular systematics are applied.
// - Note: The simple binning scheme is also used for toy-MC generation and
// then bin contents are merged together to construct the toy-MC in the variable
// binning scheme (the toy-MC is generated using the simple/fine binning so that a 
// toy-MC experiment can be plotted both in the simple/fine and optimized/variable
// binning schemes). Make sure that each bin in the optimized/variable scheme
// fits an integral number of bins from the simple/fine binning scheme.
//

#if defined (_use_single_zone_optimized_binning_scheme_v1_)
//  single zone with 5 Ereco bins and a single y bin
static const int kNMaxBinZones     = 1;
static const int kNErecoBinsOb1Z   = 5;
static const int kNYrecoBinsCCOb1Z = 1;
static const int kNYrecoBinsNCOb1Z = 1;
static const double kErecoBinEdgesOb1Z[kNErecoBinsOb1Z+1] = { kErecoMin, 1.4, 3.0, 5.0, 10.0, kErecoMax };
static const double kYrecoBinEdgesCCOb1Z[kNYrecoBinsCCOb1Z+1] = { kYrecoMin, kYrecoMax };
static const double kYrecoBinEdgesNCOb1Z[kNYrecoBinsNCOb1Z+1] = { kYrecoMin, kYrecoMax };


#elif defined (_use_single_zone_optimized_binning_scheme_v2_)
//  single zone with 10 Ereco bins and 8 y bins (necessarily 1 y bin for NC)
static const int kNMaxBinZones     = 1;
static const int kNErecoBinsOb1Z   = 10;
static const int kNYrecoBinsCCOb1Z =  8;
static const int kNYrecoBinsNCOb1Z =  1;
static const double kErecoBinEdgesOb1Z[kNErecoBinsOb1Z+1] = { kErecoMin, 1.0, 1.5, 2.0, 3.0, 4.0, 5.0, 7.5, 10.0, 15.0, kErecoMax  };
static const double kYrecoBinEdgesCCOb1Z[kNYrecoBinsCCOb1Z+1] = { kYrecoMin, 0.02, 0.05, 0.1, 0.2, 0.3, 0.5, 0.7, kYrecoMax };
static const double kYrecoBinEdgesNCOb1Z[kNYrecoBinsNCOb1Z+1] = { kYrecoMin, kYrecoMax };

#else

static const int kNMaxBinZones = 4;

// 
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
static const double kYrecoBinEdgesQELike[kNErecoZonesQELike][kNYrecoBinsQELike+1] = 
  {
    //zone 1 in Ev_reco
    {0,  0.0231,  0.0451,  0.084,   0.128,  0.232,  1},

    //zone 2 in Ev_reco
    {0,  0.0219,  0.0451,  0.0784,  0.128,  0.213,  1},

    //zone 3 in Ev_reco
    {0,  0.0172,  0.0451,  0.0742,  0.128,  0.203,  1}
  };


// 
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
static const double kYrecoBinEdgesCC1piC[kNErecoZonesCC1piC][kNYrecoBinsCC1piC+1] = 
  {
    //zone 1 in Ev_reco
    {0,  0.161,  0.203,  0.297,  0.41,  0.506,  1},

    //zone 2 in Ev_reco
    {0,  0.13,   0.203,  0.276,  0.41,  0.609,  1},

    //zone 3 in Ev_reco
    {0,  0.066,  0.203,  0.302,  0.41,  0.673,  1}
  };

// 
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
static const double kYrecoBinEdgesCCoth[kNErecoZonesCCoth][kNYrecoBinsCCoth+1] = 
  {
    //zone 1 in Ev_reco
    {0,  0.119,   0.197,  0.314,  0.466,  0.583,  1},

    //zone 2 in Ev_reco
    {0,  0.0916,  0.197,  0.324,  0.466,  0.651,  1},

    //zone 3 in Ev_reco
    {0,  0.0942,  0.197,  0.317,  0.466,  0.702,  1}
  };

// 
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

#endif // _use_single_zone_optimized_binning_scheme_...

} // conv


// ...........................................................................
// 
// Associated utility functions
//
// ...........................................................................

namespace util   {

   // Etrue binning
   int            NumEtrueBins    (conv::Sample_t sample);
   const double * EtrueBinEdges   (conv::Sample_t sample);
   int            NumQ2trueBins   (conv::Sample_t sample, conv::ReacMode_t mode);
   const double * Q2trueBinEdges  (conv::Sample_t sample, conv::ReacMode_t mode);

   // Simple binning scheme
   int            NumYrecoBinsSb  (conv::Sample_t sample);
   const double * YrecoBinEdgesSb (conv::Sample_t sample);

   // Optimized binning scheme
   int            NumErecoBins    (conv::Sample_t sample, int zone);
   const double * ErecoBinEdges   (conv::Sample_t sample, int zone);
   int            NumYrecoBins    (conv::Sample_t sample, int zone);
   const double * YrecoBinEdges   (conv::Sample_t sample, int zone);
   int            BinZone         (conv::Sample_t sample, double enu_reco, double y_reco);
   
   // Get bin number from value (zone aware)
   int ErecoBinContaining(conv::Sample_t s, double enu_reco, double y_reco);
   int YrecoBinContaining(conv::Sample_t s, double enu_reco, double y_reco);
   int EtrueBinContaining(conv::Sample_t s, double enu_true);
   
   // Cross section spline binnings
   int            NumEtrueBinsXsec  (conv::Sample_t sample);
   const double * EtrueBinEdgesXsec (conv::Sample_t sample);
   int            NumQ2trueBinsXsec (conv::Sample_t sample, conv::ReacMode_t mode);
   const double * Q2trueBinEdgesXsec(conv::Sample_t sample, conv::ReacMode_t mode);
   int            NumErecoBinsXsec  (conv::Sample_t sample, int zone);
   const double * ErecoBinEdgesXsec (conv::Sample_t sample, int zone);
   int            NumYrecoBinsXsec  (conv::Sample_t sample, int zone);
   const double * YrecoBinEdgesXsec (conv::Sample_t sample, int zone);

} // util

} // valor
  
#endif 

