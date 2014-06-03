//____________________________________________________________________________
/*!

\file      NDBeamConf

\brief     Beam configurations used in ND fit

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory
          
\created   April 15, 2014

\copyright (c) 2010-2014, The VALOR group

*/
//____________________________________________________________________________

#ifndef _valor_lbnx_nd_beam_configuration_h_
#define _valor_lbnx_nd_beam_configuration_h_

#include "Conventions/BeamConf.h"

namespace valor {
namespace conv {

static const BeamConf_t kNDBeamConf[kNBeamConf] =
{
   kbFHC,      // forward horn current
   kbRHC       // reverse horn current
}; 

} // conv
} // valor
  
#endif 

