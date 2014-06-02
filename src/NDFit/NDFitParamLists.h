//____________________________________________________________________________
/*!

\brief     Utility method for configuring near detector fit parameter lists

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

#ifndef _valor_lbnx_nd_fit_param_lists_h_
#define _valor_lbnx_nd_fit_param_lists_h_

#include <string>

#include "FitCore/FitParamList.h"

using std::string;

namespace valor {
namespace util  {

  FitParamList * NamedParameterList (string name);

} // util
} // valor
  
#endif 

