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
    case (ksNuMuCCWS0pi    ) : return "numuCCWS0pi";     break;
    case (ksNuMuCCWS1piC   ) : return "numuCCWS1piC";    break;
    case (ksNuMuCCWS1pi0   ) : return "numuCCWS1pi0";    break;
    case (ksNuMuCCWSoth    ) : return "numuCCWSoth";     break;
    case (ksNC0pi          ) : return "NC0pi";           break; 
    case (ksNC1piC         ) : return "NC1piC";          break; 
    case (ksNC1pi0         ) : return "NC1pi0";          break; 
    case (ksNCoth          ) : return "NCoth";           break; 
    case (ksNeutrinoElec   ) : return "NeutrinoElec";    break;
    case (ksInvMuDecay     ) : return "InvMuDecay";      break;
    case (ksNuECCWS        ) : return "nueCCinclWS";     break;
    case (ksNuMuCC2piC     ) : return "numuCC2piC";      break; 
    case (ksNuECC          ) : return "nueCCincl";       break;
    case (ksNC             ) : return "NCincl";          break; 
    case (ksNuMuCCWS       ) : return "numuCCinclWS";    break;
    case (ksNuMuCClow      ) : return "numuCClow";       break;
    case (ksNuMuCChigh     ) : return "numuCChigh";      break;
    case (ksNuMuBarCClow   ) : return "numubarCClow";    break;
    case (ksNuMuBarCChigh  ) : return "numubarCChigh";   break;
    case (ksNuECClow       ) : return "nueCClow";        break;
    case (ksNuECChigh      ) : return "nueCChigh";       break;
    case (ksNuEBarCClow    ) : return "nuebarCClow";     break;
    case (ksNuEBarCChigh   ) : return "nuebarCChigh";    break;
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
    case (ksNuMuCCWS0pi    ) : name = "Wrong sign #nu_{#mu} CC 0#pi";         break;
    case (ksNuMuCCWS1piC   ) : name = "Wrong sign #nu_{#mu} CC 1#pi^{#pm}";   break;
    case (ksNuMuCCWS1pi0   ) : name = "Wrong sign #nu_{#mu} CC 1#pi^{0}";     break;
    case (ksNuMuCCWSoth    ) : name = "Wrong sign #nu_{#mu} CC other";        break;
    case (ksNC0pi          ) : name = "NC 0#pi";                              break; 
    case (ksNC1piC         ) : name = "NC 1#pi^{#pm}";                        break; 
    case (ksNC1pi0         ) : name = "NC 1#pi^{0}";                          break; 
    case (ksNCoth          ) : name = "NC other";                             break; 
    case (ksNeutrinoElec   ) : name = "#nu electron elastic scattering";      break; 
    case (ksInvMuDecay     ) : name = "Inverse muon decay" ;                  break;
    case (ksNuECCWS        ) : name = "Wrong sign #nu_{e} CC inclusive" ;     break;
    case (ksNuMuCC2piC     ) : name = "#nu_{#mu} CC 2#pi^{#pm}";              break; 
    case (ksNuECC          ) : name = "#nu_{e} CC inclusive";                 break;
    case (ksNuMuCCWS       ) : name = "Wrong sign #nu_{#mu} CC inclusive";    break;
    case (ksNC             ) : name = "NC inclusive";                         break; 
    case (ksNuMuCClow      ) : name = "#nu_{#mu} CC low-resolution";          break;
    case (ksNuMuCChigh     ) : name = "#nu_{#mu} CC high-resolution";         break;
    case (ksNuMuBarCClow   ) : name = "#bar{#nu}_{#mu} CC low-resolution";    break;
    case (ksNuMuBarCChigh  ) : name = "#bar{#nu}_{#mu} CC high-resolution";   break;
    case (ksNuECClow       ) : name = "#nu_{e} CC low-resolution";            break;
    case (ksNuECChigh      ) : name = "#nu_{e} CC high-resolution";           break;
    case (ksNuEBarCClow    ) : name = "#bar{#nu}_{e} CC low-resolution";      break;
    case (ksNuEBarCChigh   ) : name = "#bar{#nu}_{e} CC high-resolution";     break;
    default                    : name = "--"; 
  }

  if(root) return name;

  // change # with \ -- later

  return name;
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
    case (ksNuEBarCChigh   ) : return true; break;
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
    case (ksNuMuCCWS0pi    ) : 
    case (ksNuMuCCWS1piC   ) : 
    case (ksNuMuCCWS1pi0   ) : 
    case (ksNuMuCCWSoth    ) : 
    case (ksNeutrinoElec   ) :
    case (ksInvMuDecay     ) : 
    case (ksNuECCWS        ) :
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
//______________________________________________________________________________________________
// IS CCQE Like, simply to be used to define binning, at the moment different for CC0pi1trk, etc
// elastic scattering and IDM samples included here at the moment
bool util::IsCCQELike(Sample_t s) 
{
  switch(s) {
    case (ksNuMuCC0pi1trk  ) :
    case (ksNuMuCC0pi2trk  ) : 
    case (ksNuMuCC0piNtrk  ) :
    case (ksNuECC0pi       ) : 
    case (ksNuMuCCWS0pi    ) : 
    case (ksNeutrinoElec   ) :
    case (ksInvMuDecay     ) : 
    case (ksNuMuCChigh     ) : 
    case (ksNuMuBarCChigh  ) : 
    case (ksNuECChigh      ) : 
    case (ksNuEBarCChigh   ) : return true; break;

    case (ksNuMuCC         ) :
    case (ksNuMuCC1piC     ) :
    case (ksNuMuCC1pi0     ) :
    case (ksNuMuCC1piC1pi0 ) :
    case (ksNuMuCCoth      ) : 
    case (ksNuMuCC3trkDelta) :
    case (ksNuECC1piC      ) : 
    case (ksNuECC1pi0      ) : 
    case (ksNuECCoth       ) : 
    case (ksNuMuCCWS1piC   ) : 
    case (ksNuMuCCWS1pi0   ) : 
    case (ksNuMuCCWSoth    ) : 
    case (ksNC0pi          ) : 
    case (ksNC1piC         ) : 
    case (ksNC1pi0         ) : 
    case (ksNCoth          ) : 
    case (ksNuMuCC2piC     ) :
    case (ksNuECC          ) : 
    case (ksNuMuCCWS       ) : 
    case (ksNuECCWS        ) :
    case (ksNC             ) : 
    case (ksNuMuCClow      ) : 
    case (ksNuMuBarCClow   ) : 
    case (ksNuECClow       ) : 
    case (ksNuEBarCClow    ) : return false; break;
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
    case (ksNuMuCCoth      ) : 
    case (ksNuECC0pi       ) : 
    case (ksNuECC1piC      ) : 
    case (ksNuECC1pi0      ) : 
    case (ksNuECCoth       ) : 
    case (ksNuMuCCWS0pi    ) : 
    case (ksNuMuCCWS1piC   ) : 
    case (ksNuMuCCWS1pi0   ) : 
    case (ksNuMuCCWSoth    ) : 
    case (ksNeutrinoElec   ) :
    case (ksInvMuDecay     ) : 
    case (ksNuECCWS        ) :
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
    case (ksNuEBarCChigh   ) : return false; break;

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
  if((s >= (int)ksNuMuCC && s <= (int) ksNuEBarCClow)|| //RHC
     (s >= (int)ksNuMuCC && s <= (int) ksNuECClow)) //FHC
    return (Sample_t)s;
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
// aliases
string valor::util::SampleAsString        (conv::Sample_t s)            { return util::AsString(s);}
string valor::util::SampleAsStringTeX     (conv::Sample_t s, bool root) { return util::AsStringTeX(s,root);}
bool valor::util::SampleIsCC       (conv::Sample_t s) {return util::IsCC      (s);};
bool valor::util::SampleIsCCQELike (conv::Sample_t s) {return util::IsCCQELike(s);};
bool valor::util::SampleIsNC       (conv::Sample_t s) {return util::IsNC      (s);};
bool valor::util::SampleIsFar      (conv::Sample_t s) {return util::IsFar     (s);};
bool valor::util::SampleIsMuLike   (conv::Sample_t s) {return util::IsMuLike  (s);};
bool valor::util::SampleIsELike    (conv::Sample_t s) {return util::IsELike   (s);};
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
bool util::IsMuLike(Sample_t s)
{
  switch (s) {
    case ksUndefined       : return false ;
    case ksNuMuCC          : return true  ;
    case ksNuMuCC0pi1trk   : return true  ;
    case ksNuMuCC0pi2trk   : return true  ;
    case ksNuMuCC1piC      : return true  ;
    case ksNuMuCC2piC      : return true  ;
    case ksNuMuCC1pi0      : return true  ;
    case ksNuMuCC1piC1pi0  : return true  ;
    case ksNuMuCCoth       : return true  ;
    case ksNuECC           : return false ;
    case ksNuMuCCWS        : return true  ;
    case ksNC              : return false ;
    case ksNuMuCC0piNtrk   : return true  ;
    case ksNuMuCC3trkDelta : return true  ;
    case ksNuMuCCWS0pi     : return true  ;
    case ksNuMuCCWS1piC    : return true  ;
    case ksNuMuCCWS1pi0    : return true  ;
    case ksNuMuCCWSoth     : return true  ;
    case ksNuECC0pi        : return false ;
    case ksNuECC1piC       : return false ;
    case ksNuECC1pi0       : return false ;
    case ksNuECCoth        : return false ;
    case ksNC0pi           : return false ;
    case ksNC1piC          : return false ;
    case ksNC1pi0          : return false ;
    case ksNCoth           : return false ;
    case ksNeutrinoElec    : return false ;
    case ksInvMuDecay      : return true  ;
    case ksNuECCWS         : return false ;
    case ksNuMuCChigh      : return true  ;
    case ksNuMuCClow       : return true  ;
    case ksNuMuBarCChigh   : return true  ;
    case ksNuMuBarCClow    : return true  ;
    case ksNuECChigh       : return false ;
    case ksNuECClow        : return false ;
    case ksNuEBarCChigh    : return false ;
    case ksNuEBarCClow     : return false ;
  }
}
//________________________________________________________________________________________
bool util::IsELike(Sample_t s)
{
  switch (s) {
    case ksUndefined       : return false ;
    case ksNuMuCC          : return false ;
    case ksNuMuCC0pi1trk   : return false ;
    case ksNuMuCC0pi2trk   : return false ;
    case ksNuMuCC1piC      : return false ;
    case ksNuMuCC2piC      : return false ;
    case ksNuMuCC1pi0      : return false ;
    case ksNuMuCC1piC1pi0  : return false ;
    case ksNuMuCCoth       : return false ;
    case ksNuECC           : return true  ;
    case ksNuMuCCWS        : return false ;
    case ksNC              : return false ;
    case ksNuMuCC0piNtrk   : return false ;
    case ksNuMuCC3trkDelta : return false ;
    case ksNuMuCCWS0pi     : return false ;
    case ksNuMuCCWS1piC    : return false ;
    case ksNuMuCCWS1pi0    : return false ;
    case ksNuMuCCWSoth     : return false ;
    case ksNuECC0pi        : return true  ;
    case ksNuECC1piC       : return true  ;
    case ksNuECC1pi0       : return true  ;
    case ksNuECCoth        : return true  ;
    case ksNC0pi           : return false ;
    case ksNC1piC          : return false ;
    case ksNC1pi0          : return false ;
    case ksNCoth           : return false ;
    case ksNeutrinoElec    : return true  ;
    case ksInvMuDecay      : return false ;
    case ksNuECCWS         : return true  ;
    case ksNuMuCChigh      : return false ;
    case ksNuMuCClow       : return false ;
    case ksNuMuBarCChigh   : return false ;
    case ksNuMuBarCClow    : return false ;
    case ksNuECChigh       : return true  ;
    case ksNuECClow        : return true  ;
    case ksNuEBarCChigh    : return true  ;
    case ksNuEBarCClow     : return true  ;
  }
}
//________________________________________________________________________________________
