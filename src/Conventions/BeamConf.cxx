//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

ChangeLog:

*/
//________________________________________________________________________________________

//fmwk
#include "Utilities/UtlStr.h"
//dune
#include "Conventions/BeamConf.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
string util::AsString(BeamConf_t b, Option_t * opt)
{
  string name = "";

  switch(b) {
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
BeamConf_t util::BeamConfFromInt(int b)
{
// Cast an integer to BeamConf_t, but with boundary check
//            [first]              [last]
  if(b >= (int)kbFHC && b <= (int) kbFHC) return (BeamConf_t)b;
  return kbUndefined;
}
//________________________________________________________________________________________




	
