//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include "NDFit/NDSample.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
string util::AsString(NDSample_t s)
{
  switch(s) {
    case (ksNDNuMuCC       ) : return "numuCCincl";   break; 
    case (ksNDNuMuCC1trkQE ) : return "numuCC1trkQE"; break; 
    case (ksNDNuMuCC2trkQE ) : return "numuCC2trkQE"; break; 
    case (ksNDNuMuCC1piC   ) : return "numuCC1piC";   break; 
    case (ksNDNuMuCC1pi0   ) : return "numuCC1pi0";   break; 
    case (ksNDNuMuCCoth    ) : return "numuCCoth";    break; 
    case (ksNDNC           ) : return "NCincl";       break; 
    case (ksNDNC1pi0       ) : return "NC1pi0";       break; 
    case (ksNDNCoth        ) : return "NCoth";        break; 
    default: return "--"; 
  }
  return "";
}
//________________________________________________________________________________________

