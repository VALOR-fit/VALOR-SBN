//____________________________________________________________________________
/*!

\class     valor::conv::BeamConf_t

\brief     Beam configuration enumeration

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory
          
\created   April 15, 2014

\copyright (c) 2010-2014, The VALOR group

*/
//____________________________________________________________________________

#ifndef _valor_lbnx_beam_configuration_h_
#define _valor_lbnx_beam_configuration_h_

#include <TROOT.h>

#include <string>

using std::string;

namespace valor {
namespace conv {

static const int kNBeamConf = 2;  

typedef enum EBeamConf
{
   kbUndefined = -1, 
   kbFHC,             // forward horn current
   kbRHC              // reverse horn current
} 
BeamConf_t; 

} // conv


//
// Associated utilities
//
namespace util {
  string AsString(conv::BeamConf_t c, Option_t * opt=0);
} // util

} // valor
  
#endif 

