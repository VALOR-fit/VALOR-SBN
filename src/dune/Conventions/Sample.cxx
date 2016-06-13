//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

// fmwk
#include "valor/Utilities/UtlStr.h"
// dune
#include "dune/Conventions/Sample.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
string util::AsString(Sample_t s)
{
  switch(s) {
    case (ksNuMuCC         ) : return "numuCCincl";      break; 
    case (ksNuMuCC0pi1trk  ) : return "numuCC0pi1trk";   break; 
    case (ksNuMuCC0pi2trk  ) : return "numuCC0pi2trk";   break; 
    case (ksNuMuCC0piNtrk  ) : return "numuCC0piNtrk";   break;
    case (ksNuMuCC3trkDelta) : return "numuCC3trkDelta"; break;
    case (ksNuMuCC1piC     ) : return "numuCC1piC";      break; 
    case (ksNuMuCC1pi0     ) : return "numuCC1pi0";      break; 
    case (ksNuMuCC1piC1pi0 ) : return "numuCC1piC1pi0";  break; 
    case (ksNuMuCCoth      ) : return "numuCCoth";       break; 
    case (ksNuECC0pi       ) : return "nueCC0pi";        break;
    case (ksNuECC1piC      ) : return "nueCC1piC";       break;
    case (ksNuECC1pi0      ) : return "nueCC1pi0";       break;
    case (ksNuECCoth       ) : return "nueCCoth";        break;
    case (ksNuMuCCWS0pi  ) : return "numuCCWS0pi";   break;
    case (ksNuMuCCWS1piC ) : return "numuCCWS1piC";  break;
    case (ksNuMuCCWS1pi0 ) : return "numuCCWS1pi0";  break;
    case (ksNuMuCCWSoth  ) : return "numuCCWSoth";   break;
    case (ksNC0pi          ) : return "NC0pi";           break; 
    case (ksNC1piC         ) : return "NC1piC";          break; 
    case (ksNC1pi0         ) : return "NC1pi0";          break; 
    case (ksNCoth          ) : return "NCoth";           break; 
    case (ksNeutrinoElec   ) : return "NeutrinoElec";    break;
    case (ksInvMuDecay     ) : return "invMuDecay";      break;
    case (ksNuMuCC2piC     ) : return "numuCC2piC";      break; 
    case (ksNuECC          ) : return "nueCCincl";       break;
    case (ksNC             ) : return "NCincl";          break; 
    case (ksNuMuCCWS     ) : return "numuCCinclWS";  break;
    case (ksNuMuCClow      ) : return "numuCClow";       break;
    case (ksNuMuCChigh     ) : return "numuCChigh";      break;
    case (ksNuMuBarCClow   ) : return "numubarCClow";    break;
    case (ksNuMuBarCChigh  ) : return "numubarCChigh";   break;
    case (ksNuECClow       ) : return "nueCClow";        break;
    case (ksNuECChigh      ) : return "nueCChigh";       break;
    case (ksNuEBarCClow    ) : return "nuebarCClow";     break;
    case (ksNuEBarCChigh   ) : return "nuebarCChigh";    break;
    case (ksNuTauCClow     ) : return "nutauCClow";      break;
    case (ksNuTauCChigh    ) : return "nutauCChigh";     break;
    case (ksNuTauBarCClow  ) : return "nutaubarCClow";   break;
    case (ksNuTauBarCChigh ) : return "nutaubarCChigh";  break;
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
    case (ksNuMuCC0pi1trk  ) : name = "#nu_{#mu} CC 1-track 0#pi";            break; 
    case (ksNuMuCC0pi2trk  ) : name = "#nu_{#mu} CC 2-track 0#pi";            break; 
    case (ksNuMuCC0piNtrk  ) : name = "#nu_{#mu} CC N-track 0#pi";            break; 
    case (ksNuMuCC3trkDelta) : name = "#nu_{#mu} CC 3-track #Delta-enchanced";break; 
    case (ksNuMuCC1piC     ) : name = "#nu_{#mu} CC 1#pi^{#pm}";              break; 
    case (ksNuMuCC1pi0     ) : name = "#nu_{#mu} CC 1#pi^{0}";                break; 
    case (ksNuMuCC1piC1pi0 ) : name = "#nu_{#mu} CC 1#pi^{#pm} + 1#pi^{0}";   break; 
    case (ksNuMuCCoth      ) : name = "#nu_{#mu} CC other";                   break; 
    case (ksNuECC0pi       ) : name = "#nu_{e} CC 0#pi";                      break;
    case (ksNuECC1piC      ) : name = "#nu_{e} CC 1#pi^{#pm}";                break;
    case (ksNuECC1pi0      ) : name = "#nu_{e} CC 1#pi^{0}";                  break;
    case (ksNuECCoth       ) : name = "#nu_{e} CC other";                     break;
    case (ksNuMuCCWS0pi  ) : name = "Wrong sign #nu_{#mu} CC 0#pi";         break;
    case (ksNuMuCCWS1piC ) : name = "Wrong sign #nu_{#mu} CC 1#pi^{#pm}";   break;
    case (ksNuMuCCWS1pi0 ) : name = "Wrong sign #nu_{#mu} CC 1#pi^{0}";     break;
    case (ksNuMuCCWSoth  ) : name = "Wrong sign #nu_{#mu} CC other";        break;
    case (ksNC0pi          ) : name = "NC 0#pi";                              break; 
    case (ksNC1piC         ) : name = "NC 1#pi^{#pm}";                        break; 
    case (ksNC1pi0         ) : name = "NC 1#pi^{0}";                          break; 
    case (ksNCoth          ) : name = "NC other";                             break; 
    case (ksNeutrinoElec   ) : name = "#nu electron elastic scattering";      break; 
    case (ksInvMuDecay     ) : name = "Inverse muon decay" ;                  break;
    case (ksNuMuCC2piC     ) : name = "#nu_{#mu} CC 2#pi^{#pm}";              break; 
    case (ksNuECC          ) : name = "#nu_{e} CC inclusive";                 break;
    case (ksNuMuCCWS     ) : name = "Wrong sign #nu_{#mu} CC inclusive";    break;
    case (ksNC             ) : name = "NC inclusive";                         break; 
    case (ksNuMuCClow      ) : name = "#nu_{#mu} CC low-resolution";          break;
    case (ksNuMuCChigh     ) : name = "#nu_{#mu} CC high-resolution";         break;
    case (ksNuMuBarCClow   ) : name = "#bar{#nu}_{#mu} CC low-resolution";    break;
    case (ksNuMuBarCChigh  ) : name = "#bar{#nu}_{#mu} CC high-resolution";   break;
    case (ksNuECClow       ) : name = "#nu_{e} CC low-resolution";            break;
    case (ksNuECChigh      ) : name = "#nu_{e} CC high-resolution";           break;
    case (ksNuEBarCClow    ) : name = "#bar{#nu}_{e} CC low-resolution";      break;
    case (ksNuEBarCChigh   ) : name = "#bar{#nu}_{e} CC high-resolution";     break;
    case (ksNuTauCClow     ) : name = "#nu_{#tau} CC low-resolution";         break;
    case (ksNuTauCChigh    ) : name = "#nu_{#tau} CC high-resolution";        break;
    case (ksNuTauBarCClow  ) : name = "#bar{#nu}_{#tau} CC low-resolution";   break;
    case (ksNuTauBarCChigh ) : name = "#bar{#nu}_{#tau} CC high-resolution";  break;
    default                    : name = "--"; 
  }

  if(root) return name;

  // change # with \ -- later

  return name;
}
//________________________________________________________________________________________
bool util::IsFar(int is)
{
  Sample_t s = util::SampleFromInt(is);
  return util::IsFar(s);
}
//________________________________________________________________________________________
bool util::IsFar(Sample_t s)
{
  switch(s) {
  case (ksNuMuCClow      ) :
  case (ksNuMuCChigh     ) :
  case (ksNuMuBarCClow   ) :
  case (ksNuMuBarCChigh  ) :
  case (ksNuECClow       ) :
  case (ksNuECChigh      ) :
  case (ksNuEBarCClow    ) :
  case (ksNuEBarCChigh   ) :
  case (ksNuTauCClow     ) :
  case (ksNuTauCChigh    ) :
  case (ksNuTauBarCClow  ) :
  case (ksNuTauBarCChigh ) : return true; break;
  default: return false;
  }
  return false; 
}

//________________________________________________________________________________________
bool util::IsCC(Sample_t s)
{
  switch(s) {
    case (ksNuMuCC         ) :
    case (ksNuMuCC0pi1trk  ) :
    case (ksNuMuCC0pi2trk  ) :
    case (ksNuMuCC0piNtrk  ) :
    case (ksNuMuCC3trkDelta) :
    case (ksNuMuCC1piC     ) :
    case (ksNuMuCC1pi0     ) :
    case (ksNuMuCC1piC1pi0 ) :
    case (ksNuECC0pi       ) : 
    case (ksNuECC1piC      ) : 
    case (ksNuECC1pi0      ) : 
    case (ksNuECCoth       ) : 
    case (ksNuMuCCWS0pi  ) : 
    case (ksNuMuCCWS1piC ) : 
    case (ksNuMuCCWS1pi0 ) : 
    case (ksNuMuCCWSoth  ) : 
    case (ksNeutrinoElec   ) :
    case (ksInvMuDecay     ) : 
    case (ksNuMuCC2piC     ) :
    case (ksNuECC          ) : 
    case (ksNuMuCCWS     ) : 
    case (ksNuMuCClow      ) : 
    case (ksNuMuCChigh     ) : 
    case (ksNuMuBarCClow   ) : 
    case (ksNuMuBarCChigh  ) : 
    case (ksNuECClow       ) : 
    case (ksNuECChigh      ) : 
    case (ksNuEBarCClow    ) : 
    case (ksNuEBarCChigh   ) : 
    case (ksNuTauCClow     ) : 
    case (ksNuTauCChigh    ) : 
    case (ksNuTauBarCClow  ) : 
    case (ksNuTauBarCChigh ) : 
    case (ksNuMuCCoth      ) : return true; break;

    case (ksNC0pi          ) : 
    case (ksNC1piC         ) : 
    case (ksNC1pi0         ) : 
    case (ksNCoth          ) : 
    case (ksNC             ) : return false; break;
    default: return false; 
  }
  return false;
}
//________________________________________________________________________________________
bool util::IsQELike(Sample_t s)
{
  switch(s) {
    case (ksNuMuCC0piNtrk  ) :
    case (ksNuECC0pi       ) : 
    case (ksNuMuCCWS0pi  ) : 
    case (ksNeutrinoElec   ) :
    case (ksNuMuCChigh     ) : 
    case (ksNuMuBarCChigh  ) : 
    case (ksNuECChigh      ) : 
    case (ksNuEBarCChigh   ) : 
    case (ksNuTauCChigh    ) : 
    case (ksNuTauBarCChigh ) : 
    case (ksNuMuCC0pi1trk  ) :
    case (ksNuMuCC0pi2trk  ) : return true; break;

    case (ksNuMuCC3trkDelta) :
    case (ksInvMuDecay     ) : 
    case (ksNuECC1piC      ) : 
    case (ksNuECC1pi0      ) : 
    case (ksNuECCoth       ) : 
    case (ksNuMuCCWS1piC ) : 
    case (ksNuMuCCWS1pi0 ) : 
    case (ksNuMuCCWSoth  ) : 
    case (ksNC0pi          ) : 
    case (ksNC1piC         ) : 
    case (ksNC1pi0         ) : 
    case (ksNCoth          ) : 
    case (ksNuMuCC2piC     ) :
    case (ksNuECC          ) : 
    case (ksNuMuCCWS     ) : 
    case (ksNC             ) : 
    case (ksNuMuCClow      ) : 
    case (ksNuMuBarCClow   ) : 
    case (ksNuECClow       ) : 
    case (ksNuEBarCClow    ) : 
    case (ksNuTauCClow     ) : 
    case (ksNuTauBarCClow  ) : 
    case (ksNuMuCC         ) :
    case (ksNuMuCC1piC     ) :
    case (ksNuMuCC1pi0     ) :
    case (ksNuMuCC1piC1pi0 ) :
    case (ksNuMuCCoth      ) : return false; break;

    default: return false; 
  }
  return false;
}
//________________________________________________________________________________________
bool util::IsNC(Sample_t s)
{
  switch(s) {
    case (ksNuMuCC         ) :
    case (ksNuMuCC0pi1trk  ) :
    case (ksNuMuCC0pi2trk  ) :
    case (ksNuMuCC1piC     ) :
    case (ksNuMuCC1pi0     ) :
    case (ksNuMuCC1piC1pi0 ) :
    case (ksNuMuCC0piNtrk  ) :
    case (ksNuMuCC3trkDelta) :
    case (ksNuECC0pi       ) : 
    case (ksNuECC1piC      ) : 
    case (ksNuECC1pi0      ) : 
    case (ksNuECCoth       ) : 
    case (ksNuMuCCWS0pi  ) : 
    case (ksNuMuCCWS1piC ) : 
    case (ksNuMuCCWS1pi0 ) : 
    case (ksNuMuCCWSoth  ) : 
    case (ksNeutrinoElec   ) :
    case (ksInvMuDecay     ) : 
    case (ksNuMuCC2piC     ) :
    case (ksNuECC          ) : 
    case (ksNuMuCCWS       ) : 
    case (ksNuMuCClow      ) : 
    case (ksNuMuCChigh     ) : 
    case (ksNuMuBarCClow   ) : 
    case (ksNuMuBarCChigh  ) : 
    case (ksNuECClow       ) : 
    case (ksNuECChigh      ) : 
    case (ksNuEBarCClow    ) : 
    case (ksNuEBarCChigh   ) : 
    case (ksNuTauCClow     ) : 
    case (ksNuTauCChigh    ) : 
    case (ksNuTauBarCClow  ) : 
    case (ksNuTauBarCChigh ) : 
    case (ksNuMuCCoth      ) : return false; break;

    case (ksNC0pi          ) : 
    case (ksNC1piC         ) : 
    case (ksNC1pi0         ) : 
    case (ksNCoth          ) : 
    case (ksNC             ) : return true; break;
    default: return false; 
  }
  return false;
}
//________________________________________________________________________________________
Sample_t util::SampleFromInt(int s)
{
// Cast an integer to Sample_t, but with boundary check
//             [first]                  [last]
  if(s >= (int)ksNuMuCC && s <= (int) ksNuTauBarCChigh) return (Sample_t)s;
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
Sample_t util::GetActiveSample(int ibeam, int isample)
{
// Cast an integer to Sample_t, but with boundary check
//             [first]                  [last]
  if (ibeam >= 0 && ibeam < conv::kNBeamConf && isample >= 0 && isample < conv::kNSamples) {
    return conv::kSample[ibeam][isample];
  }
  return ksUndefined;
}
//________________________________________________________________________________________
