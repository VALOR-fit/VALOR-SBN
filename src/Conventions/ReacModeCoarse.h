//____________________________________________________________________________
/*!

\class     valor::conv::ReacModeCoarse_t

\brief     Enumeration of coarse true reaction modes.
           Not a systematic characterization and not mutually exlusive.
           These codes are used only in plots.
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

typedef enum EReacModeCoarse
{
   kmcUndefined = -1, 
   kmcNuMuCC,             // numu     CC all
   kmcNuMuCCQEMEC,        // numu     CC QE+MEC
   kmcNuMuCCQE,           // numu     CC QE
   kmcNuMuCCMEC,          // numu     CC MEC
   kmcNuMuCC1pi,          // numu     CC 1 pi
   kmcNuMuCC2pi,          // numu     CC 2 pi
   kmcNuMuCCoth,          // numu     CC other
   kmcNuMuBarCC,          // numubar  CC all
   kmcNuMuBarCCQEMEC,     // numubar  CC QE+MEC
   kmcNuMuBarCCQE,        // numubar  CC QE
   kmcNuMuBarCCMEC,       // numubar  CC MEC
   kmcNuMuBarCC1pi,       // numubar  CC 1 pi
   kmcNuMuBarCC2pi,       // numubar  CC 2 pi
   kmcNuMuBarCCoth,       // numubar  CC other
   kmcNuENuEBarCC,        // nue(bar) CC all
   kmcNuECC,              // nue      CC all
   kmcNuECCQEMEC,         // nue      CC QE+MEC
   kmcNuECCQE,            // nue      CC QE
   kmcNuECCMEC,           // nue      CC MEC
   kmcNuECC1pi,           // nue      CC 1 pi
   kmcNuECC2pi,           // nue      CC 2 pi
   kmcNuECCoth,           // nue      CC other
   kmcNuEBarCC,           // nuebar   CC all
   kmcNuEBarCCQEMEC,      // nuebar   CC QE+MEC
   kmcNuEBarCCQE,         // nuebar   CC QE
   kmcNuEBarCCMEC,        // nuebar   CC MEC
   kmcNuEBarCC1pi,        // nuebar   CC 1 pi
   kmcNuEBarCC2pi,        // nuebar   CC 2 pi
   kmcNuEBarCCoth,        // nuebar   CC other
   kmcNC,                 // NC all
   kmcNC1pi0,             // NC 1 pi0
   kmcNCoth               // NC other
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

