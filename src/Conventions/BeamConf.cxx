//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include <algorithm>
//#include <functional>
//#include <locale>

#include "Conventions/BeamConf.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
string util::AsString(BeamConf_t c, Option_t * opt)
{
  string name = "";

  switch(c) {
    case (kbFHC) : name = "FHC"; break;
    case (kbRHC) : name = "RHC"; break;        
    default      : name = "--";  
  }

  if(opt) {
    string optstr = opt;
    if(optstr.find("lowercase")) {
      std::transform(name.begin(),name.end(),name.begin(),::tolower);
    }
  }

  return name;
}
//________________________________________________________________________________________

	
