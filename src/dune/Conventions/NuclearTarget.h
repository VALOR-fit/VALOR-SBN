//____________________________________________________________________________
/*!

\class     valor::conv::NuclearTarget_t

\brief     Target Nucleus enumeration

\author    s.r.dennis@liverpool.ac.uk
           University of Liverpool
          
\created   November 2016

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_nuclear_target_h_
#define _valor_dune_nuclear_target_h_

#include <string>

namespace valor {
namespace conv {

typedef enum ENuclearTarget
{
  kntUndefined = -1, 
  kntAll,
  kntHydrogen,
  kntCarbon,
  kntOxygen,
  kntArgon,
  kntCalcium,
  kntOther
} 
NuclearTarget_t; 

} // conv


//
// Associated utilities
//
namespace util {

  std::string  AsString     (conv::NuclearTarget_t nt);
  std::string  AsStringTeX  (conv::NuclearTarget_t nt, bool root);

} // util

} // valor
  
#endif 

