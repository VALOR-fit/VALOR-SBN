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
    case (ksNDNuMuCC         ) : return "numuCCincl";     break; 
    case (ksNDNuMuCC1trkQE   ) : return "numuCC1trkQE";   break; 
    case (ksNDNuMuCC2trkQE   ) : return "numuCC2trkQE";   break; 
    case (ksNDNuMuCC1piC     ) : return "numuCC1piC";     break; 
    case (ksNDNuMuCC2piC     ) : return "numuCC2piC";     break; 
    case (ksNDNuMuCC1pi0     ) : return "numuCC1pi0";     break; 
    case (ksNDNuMuCC1piC1pi0 ) : return "numuCC1piC1pi0"; break; 
    case (ksNDNuMuCCoth      ) : return "numuCCoth";      break; 
    case (ksNDNuECC          ) : return "nueCCincl";      break;
    case (ksNDNC             ) : return "NCincl";         break; 
    case (ksNDNC1piC         ) : return "NC1piC";         break; 
    case (ksNDNC1pi0         ) : return "NC1pi0";         break; 
    case (ksNDNCoth          ) : return "NCoth";          break; 
    default                    : return "--"; 
  }
  return "";
}
//________________________________________________________________________________________
NDSample_t util::FromInt(int s)
{
// Cast an integer to NDSample_t, but with boundary check

//             [first]                  [last]
  if(s >= (int)ksNDNuMuCC && s <= (int) ksNDNCoth) return (NDSample_t)s;

  return ksNDUndefined;
}
//________________________________________________________________________________________

