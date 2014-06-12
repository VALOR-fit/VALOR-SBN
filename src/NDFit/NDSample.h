//____________________________________________________________________________
/*!

\class     valor::conv::NDSample_t

\brief     Enumeration of LBNx ND systematic constraint samples

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

#ifndef _valor_lbnx_nd_sample_h_
#define _valor_lbnx_nd_sample_h_

#include <string>

using std::string;

namespace valor {
namespace conv {

//
// Define samples
//
typedef enum ENDSample 
{
   ksNDUndefined = -1, 
   ksNDNuMuCC,          // numu CC inclusive
   ksNDNuMuCC1trkQE,    // numu CC - 1 track QE-enhanced  (mu)
   ksNDNuMuCC2trkQE,    // numu CC - 2 track QE-enhanched (mu + proton)
   ksNDNuMuCC1piC,      // numu CC - 2 track (mu + 1 pi+/-)
   ksNDNuMuCC2piC,      // numu CC - 3 track (mu + 2 pi+/-)
   ksNDNuMuCC1pi0,      // numu CC - 2 track (mu + 1 pi0)
   ksNDNuMuCC1piC1pi0,  // numu CC - 3 track (mu + 1 pi+/- + 1pi0)
   ksNDNuMuCCoth,       // numu CC - other
   ksNDNuECC,           // nue CC
   ksNDNC,              // NC inclusive
   ksNDNC1piC,          // NC - 1pi+/-
   ksNDNC1pi0,          // NC - 1pi0
   ksNDNCoth            // NC - other
} 
NDSample_t; 

//
// Define list of samples used in present analysis
// Note: the order of samples in the array is important for other arrays
//
static const int kNNDSamples  = 6; 

static const NDSample_t kNDSample[kNNDSamples] =
{
   ksNDNuMuCC1trkQE,
   ksNDNuMuCC2trkQE, 
   ksNDNuMuCC1piC,
   ksNDNuMuCC1pi0,
   ksNDNuMuCC1piC1pi0,
   ksNDNuMuCCoth
};


} // conv

namespace util {

  string           AsString        (conv::NDSample_t s);
  string           AsStringTeX     (conv::NDSample_t s, bool root);
  conv::NDSample_t NDSampleFromInt (int s);

} // util
} // valor
  
#endif 

