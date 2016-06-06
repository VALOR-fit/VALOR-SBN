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
    case (ksNuMuCC1trk0pi  ) : return "numuCC1trk0pi";   break; 
    case (ksNuMuCC2trk0pi  ) : return "numuCC2trk0pi";   break; 
    case (ksNuMuCC1piC     ) : return "numuCC1piC";      break; 
    case (ksNuMuCC1pi0     ) : return "numuCC1pi0";      break; 
    case (ksNuMuCC1piC1pi0 ) : return "numuCC1piC1pi0";  break; 
    case (ksNuMuCCoth      ) : return "numuCCoth";       break; 
#ifdef VALOR_DUNE_THIRD_PASS_THROUGH
    case (ksNuMuCCNtrk0pi  ) : return "numuCCNtrk0pi";   break;
    case (ksNuMuCC3trkDelta) : return "numuCC3trkDelta"; break;
    case (ksNuECC0pi       ) : return "nueCC0pi";        break;
    case (ksNuECC1piC      ) : return "nueCC1piC";       break;
    case (ksNuECC1pi0      ) : return "nueCC1pi0";       break;
    case (ksNuECCoth       ) : return "nueCCoth";        break;
    case (ksNuMuCCWSgn0pi  ) : return "numuCCWSgn0pi";   break;
    case (ksNuMuCCWSgn1piC ) : return "numuCCWSgn1piC";  break;
    case (ksNuMuCCWSgn1pi0 ) : return "numuCCWSgn1pi0";  break;
    case (ksNuMuCCWSgnoth  ) : return "numuCCWSgnoth";   break;
    case (ksNC0pi          ) : return "NC0pi";           break; 
    case (ksNC1piC         ) : return "NC1piC";          break; 
    case (ksNC1pi0         ) : return "NC1pi0";          break; 
    case (ksNCoth          ) : return "NCoth";           break; 
    case (ksNuEEL          ) : return "nueEL";           break;
    case (ksInvMuDecay     ) : return "invMuDecay";      break;
#else
    case (ksNuMuCC2piC     ) : return "numuCC2piC";      break; 
    case (ksNuECC          ) : return "nueCCincl";       break;
    case (ksNC             ) : return "NCincl";          break; 
    case (ksNuMuCCWSgn     ) : return "numuCCinclWSgn";  break;
#endif
#ifdef VALOR_DUNE_FAR_DETECTOR
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
#endif
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
    case (ksNuMuCC1trk0pi  ) : name = "#nu_{#mu} CC 1-track 0#pi";            break; 
    case (ksNuMuCC2trk0pi  ) : name = "#nu_{#mu} CC 2-track 0#pi";            break; 
    case (ksNuMuCC1piC     ) : name = "#nu_{#mu} CC 1#pi^{#pm}";              break; 
    case (ksNuMuCC1pi0     ) : name = "#nu_{#mu} CC 1#pi^{0}";                break; 
    case (ksNuMuCC1piC1pi0 ) : name = "#nu_{#mu} CC 1#pi^{#pm} + 1#pi^{0}";   break; 
    case (ksNuMuCCoth      ) : name = "#nu_{#mu} CC other";                   break; 
#ifdef VALOR_DUNE_THIRD_PASS_THROUGH
    case (ksNuMuCCNtrk0pi  ) : name = "#nu_{#mu} CC N-track 0#pi";            break; 
    case (ksNuMuCC3trkDelta) : name = "#nu_{#mu} CC 3-track #Delta-enchanced";break; 
    case (ksNuECC0pi       ) : name = "#nu_{e} CC 0#pi";                      break;
    case (ksNuECC1piC      ) : name = "#nu_{e} CC 1#pi^{#pm}";                break;
    case (ksNuECC1pi0      ) : name = "#nu_{e} CC 1#pi^{0}";                  break;
    case (ksNuECCoth       ) : name = "#nu_{e} CC other";                     break;
    case (ksNuMuCCWSgn0pi  ) : name = "Wrong sign #nu_{#mu} CC 0#pi";         break;
    case (ksNuMuCCWSgn1piC ) : name = "Wrong sign #nu_{#mu} CC 1#pi^{#pm}";   break;
    case (ksNuMuCCWSgn1pi0 ) : name = "Wrong sign #nu_{#mu} CC 1#pi^{0}";     break;
    case (ksNuMuCCWSgnoth  ) : name = "Wrong sign #nu_{#mu} CC other";        break;
    case (ksNC0pi          ) : name = "NC 0#pi";                              break; 
    case (ksNC1piC         ) : name = "NC 1#pi^{#pm}";                        break; 
    case (ksNC1pi0         ) : name = "NC 1#pi^{0}";                          break; 
    case (ksNCoth          ) : name = "NC other";                             break; 
    case (ksNuEEL          ) : name = "#nu_{e} electron elastic scattering";  break; 
    case (ksInvMuDecay     ) : name = "Inverse muon decay" ;                  break;
#else
    case (ksNuMuCC2piC     ) : name = "#nu_{#mu} CC 2#pi^{#pm}";              break; 
    case (ksNuECC          ) : name = "#nu_{e} CC inclusive";                 break;
    case (ksNuMuCCWSgn     ) : name = "Wrong sign #nu_{#mu} CC inclusive";    break;
    case (ksNC             ) : name = "NC inclusive";                         break; 
#endif
#ifdef VALOR_DUNE_FAR_DETECTOR
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
#endif
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
#ifndef VALOR_DUNE_FAR_DETECTOR
  return false;
#else
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
#endif
  default: return false;
  }
  return false; 
}

//________________________________________________________________________________________
bool util::IsCC(Sample_t s)
{
  switch(s) {
    case (ksNuMuCC         ) :
    case (ksNuMuCC1trk0pi  ) :
    case (ksNuMuCC2trk0pi  ) :
    case (ksNuMuCC1piC     ) :
    case (ksNuMuCC1pi0     ) :
    case (ksNuMuCC1piC1pi0 ) :
#ifdef VALOR_DUNE_THIRD_PASS_THROUGH    
    case (ksNuMuCCNtrk0pi  ) :
    case (ksNuMuCC3trkDelta) :
    case (ksNuECC0pi       ) : 
    case (ksNuECC1piC      ) : 
    case (ksNuECC1pi0      ) : 
    case (ksNuECCoth       ) : 
    case (ksNuMuCCWSgn0pi  ) : 
    case (ksNuMuCCWSgn1piC ) : 
    case (ksNuMuCCWSgn1pi0 ) : 
    case (ksNuMuCCWSgnoth  ) : 
    case (ksNuEEL          ) :
    case (ksInvMuDecay     ) : 
#else
    case (ksNuMuCC2piC     ) :
    case (ksNuECC          ) : 
    case (ksNuMuCCWSgn     ) : 
#endif
#ifdef VALOR_DUNE_FAR_DETECTOR
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
#endif
    case (ksNuMuCCoth      ) : return true; break;

#ifdef VALOR_DUNE_THIRD_PASS_THROUGH
    case (ksNC0pi          ) : 
    case (ksNC1piC         ) : 
    case (ksNC1pi0         ) : 
    case (ksNCoth          ) : return false; break;
#else
    case (ksNC             ) : return false; break;
#endif
    default: return false; 
  }
  return false;
}
//________________________________________________________________________________________
bool util::IsELike(Sample_t s)
{
  switch(s) {
#ifdef VALOR_DUNE_THIRD_PASS_THROUGH    
    case (ksNuMuCCNtrk0pi  ) :
    case (ksNuECC0pi       ) : 
    case (ksNuMuCCWSgn0pi  ) : 
    case (ksNuEEL          ) :
#endif
#ifdef VALOR_DUNE_FAR_DETECTOR
    case (ksNuMuCChigh     ) : 
    case (ksNuMuBarCChigh  ) : 
    case (ksNuECChigh      ) : 
    case (ksNuEBarCChigh   ) : 
    case (ksNuTauCChigh    ) : 
    case (ksNuTauBarCChigh ) : 
#endif
    case (ksNuMuCC1trk0pi  ) :
    case (ksNuMuCC2trk0pi  ) : return true; break;

#ifdef VALOR_DUNE_THIRD_PASS_THROUGH
    case (ksNuMuCC3trkDelta) :
    case (ksInvMuDecay     ) : 
    case (ksNuECC1piC      ) : 
    case (ksNuECC1pi0      ) : 
    case (ksNuECCoth       ) : 
    case (ksNuMuCCWSgn1piC ) : 
    case (ksNuMuCCWSgn1pi0 ) : 
    case (ksNuMuCCWSgnoth  ) : 
    case (ksNC0pi          ) : 
    case (ksNC1piC         ) : 
    case (ksNC1pi0         ) : 
    case (ksNCoth          ) : 
#else
    case (ksNuMuCC2piC     ) :
    case (ksNuECC          ) : 
    case (ksNuMuCCWSgn     ) : 
    case (ksNC             ) : 
#endif
#ifdef VALOR_DUNE_FAR_DETECTOR
    case (ksNuMuCClow      ) : 
    case (ksNuMuBarCClow   ) : 
    case (ksNuECClow       ) : 
    case (ksNuEBarCClow    ) : 
    case (ksNuTauCClow     ) : 
    case (ksNuTauBarCClow  ) : 
#endif
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
    case (ksNuMuCC1trk0pi  ) :
    case (ksNuMuCC2trk0pi  ) :
    case (ksNuMuCC1piC     ) :
    case (ksNuMuCC1pi0     ) :
    case (ksNuMuCC1piC1pi0 ) :
#ifdef VALOR_DUNE_THIRD_PASS_THROUGH    
    case (ksNuMuCCNtrk0pi  ) :
    case (ksNuMuCC3trkDelta) :
    case (ksNuECC0pi       ) : 
    case (ksNuECC1piC      ) : 
    case (ksNuECC1pi0      ) : 
    case (ksNuECCoth       ) : 
    case (ksNuMuCCWSgn0pi  ) : 
    case (ksNuMuCCWSgn1piC ) : 
    case (ksNuMuCCWSgn1pi0 ) : 
    case (ksNuMuCCWSgnoth  ) : 
    case (ksNuEEL          ) :
    case (ksInvMuDecay     ) : 
#else
    case (ksNuMuCC2piC     ) :
    case (ksNuECC          ) : 
    case (ksNuMuCCWSgn     ) : 
#endif
#ifdef VALOR_DUNE_FAR_DETECTOR
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
#endif
    case (ksNuMuCCoth      ) : return false; break;

#ifdef VALOR_DUNE_THIRD_PASS_THROUGH
    case (ksNC0pi          ) : 
    case (ksNC1piC         ) : 
    case (ksNC1pi0         ) : 
    case (ksNCoth          ) : return true; break;
#else
    case (ksNC             ) : return true; break;
#endif

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
