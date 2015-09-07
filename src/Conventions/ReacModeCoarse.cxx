//________________________________________________________________________________________
/*

Copyright (c) 2010-2015, The VALOR Fitting Group, All Rights Reserved. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include "Conventions/ReacModeCoarse.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
string util::AsString(ReacModeCoarse_t m)
{
  switch(m) {
    case (kmcNuMuCC         ) : return "numuCC";          break;
    case (kmcNuMuCCQEMEC    ) : return "numuCCQEMEC";     break;
    case (kmcNuMuCCQE       ) : return "numuCCQE";        break;
    case (kmcNuMuCCMEC      ) : return "numuCCMEC";       break;
    case (kmcNuMuCC1pi      ) : return "numuCC1pi";       break;
    case (kmcNuMuCC2pi      ) : return "numuCC2pi";       break;
    case (kmcNuMuCCoth      ) : return "numuCCoth";       break;
    case (kmcNuMuBarCC      ) : return "numubarCC";       break;
    case (kmcNuMuBarCCQEMEC ) : return "numubarCCQEMEC";  break;
    case (kmcNuMuBarCCQE    ) : return "numubarCCQE";     break;
    case (kmcNuMuBarCCMEC   ) : return "numubarCCMEC";    break;
    case (kmcNuMuBarCC1pi   ) : return "numubarCC1pi";    break;
    case (kmcNuMuBarCC2pi   ) : return "numubarCC2pi";    break;
    case (kmcNuMuBarCCoth   ) : return "numubarCCoth";    break;
    case (kmcNuENuEBarCC    ) : return "nuenuebarCC";     break;
    case (kmcNuECC          ) : return "nueCC";           break;
    case (kmcNuECCQEMEC     ) : return "nueCCQEMEC";      break;
    case (kmcNuECCQE        ) : return "nueCCQE";         break;
    case (kmcNuECCMEC       ) : return "nueCCMEC";        break;
    case (kmcNuECC1pi       ) : return "nueCC1pi";        break;
    case (kmcNuECC2pi       ) : return "nueCC2pi";        break;
    case (kmcNuECCoth       ) : return "nueCCoth";        break;
    case (kmcNuEBarCC       ) : return "nuebarCC";        break;
    case (kmcNuEBarCCQEMEC  ) : return "nuebarCCQEMEC";   break;
    case (kmcNuEBarCCQE     ) : return "nuebarCCQE";      break;
    case (kmcNuEBarCCMEC    ) : return "nuebarCCMEC";     break;
    case (kmcNuEBarCC1pi    ) : return "nuebarCC1pi";     break;
    case (kmcNuEBarCC2pi    ) : return "nuebarCC2pi";     break;
    case (kmcNuEBarCCoth    ) : return "nuebarCCoth";     break;
    case (kmcNC             ) : return "NC";              break;
    case (kmcNC1pi0         ) : return "NC1pi0";          break;
    case (kmcNCoth          ) : return "NCoth";           break;
    default                   : return "--";           
  }
  return "";
}
//________________________________________________________________________________________
string util::AsStringTex(ReacModeCoarse_t m, bool root)
{
  string name = "";

  switch(m) { 
    case (kmcNuMuCC         ) : name = "#nu_{#mu} CC";                break;
    case (kmcNuMuCCQEMEC    ) : name = "#nu_{#mu} CC QE+MEC";         break;
    case (kmcNuMuCCQE       ) : name = "#nu_{#mu} CC QE";             break;
    case (kmcNuMuCCMEC      ) : name = "#nu_{#mu} CC MEC";            break;
    case (kmcNuMuCC1pi      ) : name = "#nu_{#mu} CC 1#pi";           break;
    case (kmcNuMuCC2pi      ) : name = "#nu_{#mu} CC 2#pi";           break;
    case (kmcNuMuCCoth      ) : name = "#nu_{#mu} CC other";          break;
    case (kmcNuMuBarCC      ) : name = "#bar{#nu_{#mu}} CC";          break;
    case (kmcNuMuBarCCQEMEC ) : name = "#bar{#nu_{#mu}} CC QE+MEC";   break;
    case (kmcNuMuBarCCQE    ) : name = "#bar{#nu_{#mu}} CC QE";       break;
    case (kmcNuMuBarCCMEC   ) : name = "#bar{#nu_{#mu}} CC MEC";      break;
    case (kmcNuMuBarCC1pi   ) : name = "#bar{#nu_{#mu}} CC 1#pi";     break;
    case (kmcNuMuBarCC2pi   ) : name = "#bar{#nu_{#mu}} CC 2#pi";     break;
    case (kmcNuMuBarCCoth   ) : name = "#bar{#nu_{#mu}} CC other";    break;
    case (kmcNuENuEBarCC    ) : name = "#nu_{e}/#bar{#nu_{e}} CC";    break;
    case (kmcNuECC          ) : name = "#nu_{e} CC";                  break;
    case (kmcNuECCQEMEC     ) : name = "#nu_{e} CC QE+MEC";           break;
    case (kmcNuECCQE        ) : name = "#nu_{e} CC QE";               break;
    case (kmcNuECCMEC       ) : name = "#nu_{e} CC MEC";              break;
    case (kmcNuECC1pi       ) : name = "#nu_{e} CC 1#pi";             break;
    case (kmcNuECC2pi       ) : name = "#nu_{e} CC 2#pi";             break;
    case (kmcNuECCoth       ) : name = "#nu_{e} CC other";            break;
    case (kmcNuEBarCC       ) : name = "#bar{#nu_{e}} CC";            break;
    case (kmcNuEBarCCQEMEC  ) : name = "#bar{#nu_{e}} CC QE+MEC";     break;
    case (kmcNuEBarCCQE     ) : name = "#bar{#nu_{e}} CC QE";         break;
    case (kmcNuEBarCCMEC    ) : name = "#bar{#nu_{e}} CC MEC";        break;
    case (kmcNuEBarCC1pi    ) : name = "#bar{#nu_{e}} CC 1#pi";       break;
    case (kmcNuEBarCC2pi    ) : name = "#bar{#nu_{e}} CC 2#pi";       break;
    case (kmcNuEBarCCoth    ) : name = "#bar{#nu_{e}} CC other";      break;
    case (kmcNC             ) : name = "NC";                          break;
    case (kmcNC1pi0         ) : name = "NC 1#pi^{0}";                 break;
    case (kmcNCoth          ) : name = "NC other";                    break;
    default                   : name = "--"; 
  }

  if(root) return name;

  // change `#' with `\' (later)

  return name;
}
//________________________________________________________________________________________
	
