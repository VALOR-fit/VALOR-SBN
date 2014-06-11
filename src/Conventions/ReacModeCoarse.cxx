//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

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

    case (kmcNuMuCCQE    ) : return "numuCCQE";  break;
    case (kmcNuMuCCMEC   ) : return "numuCCMEC"; break;
    case (kmcNuMuCC1pi   ) : return "numuCC1pi"; break;
    case (kmcNuMuCC2pi   ) : return "numuCC2pi"; break;
    case (kmcNuMuCCoth   ) : return "numuCCoth"; break;
    case (kmcNuMuBarCC   ) : return "numubarCC"; break;
    case (kmcNuENueBarCC ) : return "nueCC";     break;
    case (kmcNC          ) : return "NC";        break;
    default                : return "--";           
  }
  return "";
}
//________________________________________________________________________________________
string util::AsStringTex(ReacModeCoarse_t m, bool root)
{
  string name = "";

  switch(m) {

    case (kmcNuMuCCQE    ) : name = "#nu_{#mu} CCQE";             break;
    case (kmcNuMuCCMEC   ) : name = "#nu_{#mu} CCMEC";            break;
    case (kmcNuMuCC1pi   ) : name = "#nu_{#mu} CC1#pi";           break;
    case (kmcNuMuCC2pi   ) : name = "#nu_{#mu} CC2#pi";           break;
    case (kmcNuMuCCoth   ) : name = "#nu_{#mu} CC other";         break;
    case (kmcNuMuBarCC   ) : name = "#bar{#nu_{#mu}} CC";         break;
    case (kmcNuENueBarCC ) : name = "#nu_{e}/#bar{#nu_{e}} CC";   break;
    case (kmcNC          ) : name = "NC";                         break;
    default                : name = "--"; 
  }

  if(root) return name;

  // change `#' with `\' (later)

  return name;
}
//________________________________________________________________________________________
	
