//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

// fmwk
#include "Utilities/UtlStr.h"
// dune
#include "Conventions/Sample.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
string util::AsString(Sample_t s)
{
  switch(s) {
    case (ksNuMuCC         ) : return "numuCCincl";     break; 
    case (ksNuMuCC1trkQE   ) : return "numuCC1trkQE";   break; 
    case (ksNuMuCC2trkQE   ) : return "numuCC2trkQE";   break; 
    case (ksNuMuCC1piC     ) : return "numuCC1piC";     break; 
    case (ksNuMuCC2piC     ) : return "numuCC2piC";     break; 
    case (ksNuMuCC1pi0     ) : return "numuCC1pi0";     break; 
    case (ksNuMuCC1piC1pi0 ) : return "numuCC1piC1pi0"; break; 
    case (ksNuMuCCoth      ) : return "numuCCoth";      break; 
    case (ksNuECC          ) : return "nueCCincl";      break;
    case (ksNuMuCCWSgn     ) : return "numuCCinclWSgn"; break;
    case (ksNC             ) : return "NCincl";         break; 
    case (ksNC1piC         ) : return "NC1piC";         break; 
    case (ksNC1pi0         ) : return "NC1pi0";         break; 
    case (ksNCoth          ) : return "NCoth";          break; 
    default                    : return "--"; 
  }
  return "";
}
//________________________________________________________________________________________
string util::AsStringTeX(Sample_t s, bool root)
{
  string name = "";

  switch(s) {
    case (ksNuMuCC         ) : name = "#nu_{#mu} CC inclusive";               break; 
    case (ksNuMuCC1trkQE   ) : name = "#nu_{#mu} CC 1-track QE-like";         break; 
    case (ksNuMuCC2trkQE   ) : name = "#nu_{#mu} CC 2-track QE-like";         break; 
    case (ksNuMuCC1piC     ) : name = "#nu_{#mu} CC 1#pi^{#pm}";              break; 
    case (ksNuMuCC2piC     ) : name = "#nu_{#mu} CC 2#pi^{#pm}";              break; 
    case (ksNuMuCC1pi0     ) : name = "#nu_{#mu} CC 1#pi^{0}";                break; 
    case (ksNuMuCC1piC1pi0 ) : name = "#nu_{#mu} CC 1#pi^{#pm} + 1#pi^{0}";   break; 
    case (ksNuMuCCoth      ) : name = "#nu_{#mu} CC other";                   break; 
    case (ksNuECC          ) : name = "#nu_{e} CC inclusive";                 break;
    case (ksNuMuCCWSgn     ) : name = "Wrong sign #nu_{#mu} CC inclusive";    break;
    case (ksNC             ) : name = "NC inclusive";                         break; 
    case (ksNC1piC         ) : name = "NC 1#pi^{#pm}";                        break; 
    case (ksNC1pi0         ) : name = "NC 1#pi^{0}";                          break; 
    case (ksNCoth          ) : name = "NC other";                             break; 
    default                    : name = "--"; 
  }

  if(root) return name;

  // change # with \ -- later

  return name;
}
//________________________________________________________________________________________
bool util::IsCC(Sample_t s)
{
  switch(s) {

    case (ksNuMuCC         ) :
    case (ksNuMuCC1trkQE   ) :
    case (ksNuMuCC2trkQE   ) :
    case (ksNuMuCC1piC     ) :
    case (ksNuMuCC2piC     ) :
    case (ksNuMuCC1pi0     ) :
    case (ksNuMuCC1piC1pi0 ) :
    case (ksNuMuCCoth      ) :
    case (ksNuECC          ) : 
    case (ksNuMuCCWSgn     ) : return true; break;

    case (ksNC             ) : 
    case (ksNC1piC         ) : 
    case (ksNC1pi0         ) : 
    case (ksNCoth          ) : return false; break;

    default: return false; 
  }
  return false;
}
//________________________________________________________________________________________
bool util::IsNC(Sample_t s)
{
  switch(s) {

    case (ksNuMuCC         ) :
    case (ksNuMuCC1trkQE   ) :
    case (ksNuMuCC2trkQE   ) :
    case (ksNuMuCC1piC     ) :
    case (ksNuMuCC2piC     ) :
    case (ksNuMuCC1pi0     ) :
    case (ksNuMuCC1piC1pi0 ) :
    case (ksNuMuCCoth      ) :
    case (ksNuECC          ) : 
    case (ksNuMuCCWSgn     ) : return false; break;

    case (ksNC             ) : 
    case (ksNC1piC         ) : 
    case (ksNC1pi0         ) : 
    case (ksNCoth          ) : return true; break;

    default: return false; 
  }
  return false;
}
//________________________________________________________________________________________
Sample_t util::SampleFromInt(int s)
{
// Cast an integer to Sample_t, but with boundary check
//             [first]                  [last]
  if(s >= (int)ksNuMuCC && s <= (int) ksNCoth) return (Sample_t)s;
  return ksUndefined;
}
//________________________________________________________________________________________
Sample_t util::SampleFromString(string sample)
{
  string lc_sample = util::ToLowerCase(sample);
  for (int i = 0 ; i < kMaxNSamples ; i++ ) {
    Sample_t s = (Sample_t)i;
    string this_samp = util::ToLowerCase(util::AsString(s));
    if(lc_sample==this_samp && this_samp!="--") {
      return s;
    }
  }
    
  return ksUndefined;
}
//________________________________________________________________________________________
string valor::util::SampleAsString        (conv::Sample_t s)            { return util::AsString(s);}
string valor::util::SampleAsStringTeX     (conv::Sample_t s, bool root) { return util::AsStringTeX(s,root);}
//________________________________________________________________________________________
