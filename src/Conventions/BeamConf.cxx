//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

//fmwk
#include "Utilities/UtlStr.h"
//lbnx
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
    string name2  = name;
    string optstr = opt;
    if(optstr.find("lowercase") != string::npos) {
       name2 = util::ToLowerCase(name);
    }
    return name2;
  }

  return name;
}
//________________________________________________________________________________________

	
