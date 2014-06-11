//____________________________________________________________________________
/*!

\class     valor::conv::ReacModeCoarse_t

\brief     Enumeration of coarse true reaction modes.
           They are used only in plots.
           One or more ReacMode_t types are mapped into a ReacModeCoarse_t.

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory
          
\created   April 15, 2014

\copyright (c) 2010-2014, The VALOR group

*/
//____________________________________________________________________________

#ifndef _valor_lbnx_coarse_reaction_modes_h
#define _valor_lbnx_coarse_reaction_modes_h

#include <string>

using std::string;

namespace valor {
namespace conv {

static const int kNReacModesCoarse = 8;  

typedef enum EReacModeCoarse
{
   kmcUndefined = -1, 
   kmcNuMuCCQE,           // numu     CC QE
   kmcNuMuCCMEC,          // numu     CC MEC
   kmcNuMuCC1pi,          // numu     CC 1 pi
   kmcNuMuCC2pi,          // numu     CC 2 pi
   kmcNuMuCCoth,          // numu     CC other
   kmcNuMuBarCC,          // numubar  CC
   kmcNuENueBarCC,        // nue(bar) CC
   kmcNC                  // NC
} 
ReacModeCoarse_t; 

} // conv


//
// Associated utilities
//
namespace util {

  string AsString    (conv::ReacModeCoarse_t m);
  string AsStringTex (conv::ReacModeCoarse_t m, bool root);

} // util

} // valor
  
#endif 

