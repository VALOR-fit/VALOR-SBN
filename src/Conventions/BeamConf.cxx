//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include "Conventions/BeamConf.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
string util::AsString(BeamConf_t c)
{
  switch(c) {

    case (kbFHC) : return "FHC"; break;
    case (kbRHC) : return "RHC"; break;        
    default      : return "--"; 
  }
  return "";
}
//________________________________________________________________________________________

	
