//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

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
    case (ksNDNuMuCCWSgn     ) : return "numuCCinclWSgn"; break;
    case (ksNDNC             ) : return "NCincl";         break; 
    case (ksNDNC1piC         ) : return "NC1piC";         break; 
    case (ksNDNC1pi0         ) : return "NC1pi0";         break; 
    case (ksNDNCoth          ) : return "NCoth";          break; 
    default                    : return "--"; 
  }
  return "";
}
//________________________________________________________________________________________
string util::AsStringTeX(NDSample_t s, bool root)
{
  string name = "";

  switch(s) {
    case (ksNDNuMuCC         ) : name = "#nu_{#mu} CC inclusive";               break; 
    case (ksNDNuMuCC1trkQE   ) : name = "#nu_{#mu} CC 1-track QE-like";         break; 
    case (ksNDNuMuCC2trkQE   ) : name = "#nu_{#mu} CC 2-track QE-like";         break; 
    case (ksNDNuMuCC1piC     ) : name = "#nu_{#mu} CC 1#pi^{#pm}";              break; 
    case (ksNDNuMuCC2piC     ) : name = "#nu_{#mu} CC 2#pi^{#pm}";              break; 
    case (ksNDNuMuCC1pi0     ) : name = "#nu_{#mu} CC 1#pi^{0}";                break; 
    case (ksNDNuMuCC1piC1pi0 ) : name = "#nu_{#mu} CC 1#pi^{#pm} + 1#pi^{0}";   break; 
    case (ksNDNuMuCCoth      ) : name = "#nu_{#mu} CC other";                   break; 
    case (ksNDNuECC          ) : name = "#nu_{e} CC inclusive";                 break;
    case (ksNDNuMuCCWSgn     ) : name = "Wrong sign #nu_{#mu} CC inclusive";    break;
    case (ksNDNC             ) : name = "NC inclusive";                         break; 
    case (ksNDNC1piC         ) : name = "NC 1#pi^{#pm}";                        break; 
    case (ksNDNC1pi0         ) : name = "NC 1#pi^{0}";                          break; 
    case (ksNDNCoth          ) : name = "NC other";                             break; 
    default                    : name = "--"; 
  }

  if(root) return name;

  // change # with \ -- later

  return name;
}
//________________________________________________________________________________________
bool util::IsCC(NDSample_t s)
{
  switch(s) {

    case (ksNDNuMuCC         ) :
    case (ksNDNuMuCC1trkQE   ) :
    case (ksNDNuMuCC2trkQE   ) :
    case (ksNDNuMuCC1piC     ) :
    case (ksNDNuMuCC2piC     ) :
    case (ksNDNuMuCC1pi0     ) :
    case (ksNDNuMuCC1piC1pi0 ) :
    case (ksNDNuMuCCoth      ) :
    case (ksNDNuECC          ) : 
    case (ksNDNuMuCCWSgn     ) : return true; break;

    case (ksNDNC             ) : 
    case (ksNDNC1piC         ) : 
    case (ksNDNC1pi0         ) : 
    case (ksNDNCoth          ) : return false; break;

    default: return false; 
  }
  return false;
}
//________________________________________________________________________________________
bool util::IsNC(NDSample_t s)
{
  switch(s) {

    case (ksNDNuMuCC         ) :
    case (ksNDNuMuCC1trkQE   ) :
    case (ksNDNuMuCC2trkQE   ) :
    case (ksNDNuMuCC1piC     ) :
    case (ksNDNuMuCC2piC     ) :
    case (ksNDNuMuCC1pi0     ) :
    case (ksNDNuMuCC1piC1pi0 ) :
    case (ksNDNuMuCCoth      ) :
    case (ksNDNuECC          ) : 
    case (ksNDNuMuCCWSgn     ) : return false; break;

    case (ksNDNC             ) : 
    case (ksNDNC1piC         ) : 
    case (ksNDNC1pi0         ) : 
    case (ksNDNCoth          ) : return true; break;

    default: return false; 
  }
  return false;
}
//________________________________________________________________________________________
NDSample_t util::NDSampleFromInt(int s)
{
// Cast an integer to NDSample_t, but with boundary check
//             [first]                  [last]
  if(s >= (int)ksNDNuMuCC && s <= (int) ksNDNCoth) return (NDSample_t)s;
  return ksNDUndefined;
}
//________________________________________________________________________________________
string valor::util::NDSampleAsString        (conv::NDSample_t s)            { return util::AsString(s);}
string valor::util::NDSampleAsStringTeX     (conv::NDSample_t s, bool root) { return util::AsStringTeX(s,root);}
//________________________________________________________________________________________
