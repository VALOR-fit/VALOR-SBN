//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include <algorithm>

#include "Conventions/ReacMode.h"

using namespace valor;
using namespace valor::conv;

using std::string;

//________________________________________________________________________________________
string util::AsString(ReacMode_t m)
{
  switch(m) {

    case (kmNuMuCCQE        ): return "numuCCQE";     break;
    case (kmNuMuCCMEC       ): return "numuCCMEC";    break;        
    case (kmNuMuCC1piC      ): return "numuCC1piC";   break;        
    case (kmNuMuCC1pi0      ): return "numuCC1pi0";   break;        
    case (kmNuMuCC2piC      ): return "numuCC2piC";   break;        
    case (kmNuMuCC2pi0      ): return "numuCC2pi0";   break;        
    case (kmNuMuCCpiCpi0    ): return "numuCCpiCpi0"; break;         
    case (kmNuMuCCcoh       ): return "numuCCcoh";    break;       
    case (kmNuMuCCoth       ): return "numuCCoth";    break;        

//  case (kmNuMuNCEL        ): return ""; break;        
//  case (kmNuMuNCMEC       ): return ""; break;        
    case (kmNuMuNC1piC      ): return "numuNC1piC"; break;        
    case (kmNuMuNC1pi0      ): return "numuNC1pi0"; break;        
//  case (kmNuMuNC2piC      ): return ""; break;        
//  case (kmNuMuNC2pi0      ): return ""; break;        
//  case (kmNuMuNCpiCpi0    ): return ""; break;       
    case (kmNuMuNCcoh       ): return "numuNCcoh";  break;        
    case (kmNuMuNCoth       ): return "numuNCoth";  break;        

    case (kmNuMuBarCCQE     ): return "numubarCCQE";     break;        
    case (kmNuMuBarCCMEC    ): return "numubarCCMEC";    break;        
    case (kmNuMuBarCC1piC   ): return "numubarCC1piC";   break;       
    case (kmNuMuBarCC1pi0   ): return "numubarCC1pi0";   break;       
    case (kmNuMuBarCC2piC   ): return "numubarCC2piC";   break;      
    case (kmNuMuBarCC2pi0   ): return "numubarCC2pi0";   break;       
    case (kmNuMuBarCCpiCpi0 ): return "numubarCCpiCpi0"; break;   
    case (kmNuMuBarCCcoh    ): return "numubarCCcoh";    break;      
    case (kmNuMuBarCCoth    ): return "numubarCCoth";    break;    

//  case (kmNuMuBarNCEL     ): return ""; break;    
//  case (kmNuMuBarNCMEC    ): return ""; break;    
    case (kmNuMuBarNC1piC   ): return "numubarNC1piC"; break;   
    case (kmNuMuBarNC1pi0   ): return "numubarNC1pi0"; break;    
//  case (kmNuMuBarNC2piC   ): return ""; break;   
//  case (kmNuMuBarNC2pi0   ): return ""; break;    
//  case (kmNuMuBarNCpiCpi0 ): return ""; break;   
    case (kmNuMuBarNCcoh    ): return "numubarNCcoh";  break;  
    case (kmNuMuBarNCoth    ): return "numubarNCoth";  break;       

    case (kmNuECCQE         ): return "nueCCQE";     break;             
    case (kmNuECCMEC        ): return "nueCCMEC";    break;         
    case (kmNuECC1piC       ): return "nueCC1piC";   break; 
    case (kmNuECC1pi0       ): return "nueCC1pi0";   break;    
    case (kmNuECC2piC       ): return "nueCC2piC";   break;    
    case (kmNuECC2pi0       ): return "nueCC2pi0";   break;    
    case (kmNuECCpiCpi0     ): return "nueCCpiCpi0"; break;  
    case (kmNuECCcoh        ): return "nueCCcoh";    break;  
    case (kmNuECCoth        ): return "nueCCoth";    break;    

//  case (kmNuENCEL         ): return ""; break;    
//  case (kmNuENCMEC        ): return ""; break;    
    case (kmNuENC1piC       ): return "nueNC1piC"; break;    
    case (kmNuENC1pi0       ): return "nueNC1pi0"; break;    
//  case (kmNuENC2piC       ): return ""; break;   
//  case (kmNuENC2pi0       ): return ""; break;    
//  case (kmNuENCpiCpi0     ): return ""; break;   
    case (kmNuENCcoh        ): return "nueNCcoh";  break; 
    case (kmNuENCoth        ): return "nueNCoth";  break;    

    case (kmNuEBarCCQE      ): return "nuebarCCQE";     break;    
    case (kmNuEBarCCMEC     ): return "nuebarCCMEC";    break;    
    case (kmNuEBarCC1piC    ): return "nuebarCC1piC";   break;   
    case (kmNuEBarCC1pi0    ): return "nuebarCC1pi0";   break;    
    case (kmNuEBarCC2piC    ): return "nuebarCC2piC";   break;   
    case (kmNuEBarCC2pi0    ): return "nuebarCC2pi0";   break;    
    case (kmNuEBarCCpiCpi0  ): return "nuebarCCpiCpi0"; break;    
    case (kmNuEBarCCcoh     ): return "nuebarCCcoh";    break;    
    case (kmNuEBarCCoth     ): return "nuebarCCoth";    break;    

//  case (kmNuEBarNCEL      ): return ""; break;   
//  case (kmNuEBarNCMEC     ): return ""; break;    
    case (kmNuEBarNC1piC    ): return "nuebarNC1piC"; break;   
    case (kmNuEBarNC1pi0    ): return "nuebarNC1pi0"; break;    
//  case (kmNuEBarNC2piC    ): return ""; break;   
//  case (kmNuEBarNC2pi0    ): return ""; break;    
//  case (kmNuEBarNCpiCpi0  ): return ""; break;  
    case (kmNuEBarNCcoh     ): return "nuebarNCcoh";  break;   
    case (kmNuEBarNCoth     ): return "nuebarNCoth";  break;     

    case (kmOther           ): return "other";  break;     
    default                  : return "--"; 
  }
  return "";
}
//________________________________________________________________________________________
string util::AsStringTeX(ReacMode_t m, bool root)
{
  string name = "";

  switch(m) {

    case (kmNuMuCCQE        ): name = "#nu_{#mu} CCQE";                   break;
    case (kmNuMuCCMEC       ): name = "#nu_{#mu} CCMEC";                  break;        
    case (kmNuMuCC1piC      ): name = "#nu_{#mu} CC1#pi^{#pm}";           break;        
    case (kmNuMuCC1pi0      ): name = "#nu_{#mu} CC1#pi^{0}";             break;        
    case (kmNuMuCC2piC      ): name = "#nu_{#mu} CC2#pi^{#pm}";           break;        
    case (kmNuMuCC2pi0      ): name = "#nu_{#mu} CC2#pi^{0}";             break;        
    case (kmNuMuCCpiCpi0    ): name = "#nu_{#mu} CC#pi^{#pm}#pi^{0}";     break;         
    case (kmNuMuCCcoh       ): name = "#nu_{#mu} CCcoh";                  break;       
    case (kmNuMuCCoth       ): name = "#nu_{#mu} CCoth";                  break;        

//  case (kmNuMuNCEL        ): name = "";                                 break;        
//  case (kmNuMuNCMEC       ): name = "";                                 break;        
    case (kmNuMuNC1piC      ): name = "#nu_{#mu} NC1#pi^{#pm}";           break;        
    case (kmNuMuNC1pi0      ): name = "#nu_{#mu} NC1#pi^{0}";             break;        
//  case (kmNuMuNC2piC      ): name = "";                                 break;        
//  case (kmNuMuNC2pi0      ): name = "";                                 break;        
//  case (kmNuMuNCpiCpi0    ): name = "";                                 break;       
    case (kmNuMuNCcoh       ): name = "#nu_{#mu} NCcoh";                  break;        
    case (kmNuMuNCoth       ): name = "#nu_{#mu} NCoth";                  break;        

    case (kmNuMuBarCCQE     ): name = "#bar{#nu_{#mu}} CCQE";             break;        
    case (kmNuMuBarCCMEC    ): name = "#bar{#nu_{#mu}} CCMEC";            break;        
    case (kmNuMuBarCC1piC   ): name = "#bar{#nu_{#mu}} CC1#pi^{#pm}";     break;       
    case (kmNuMuBarCC1pi0   ): name = "#bar{#nu_{#mu}} CC1#pi^{0}";       break;       
    case (kmNuMuBarCC2piC   ): name = "#bar{#nu_{#mu}} CC2#pi^{#pm}";     break;      
    case (kmNuMuBarCC2pi0   ): name = "#bar{#nu_{#mu}} CC2#pi^{0}";       break;       
    case (kmNuMuBarCCpiCpi0 ): name = "#bar{#nu_{#mu}} CC#pi^{#pm}#pi0";  break;   
    case (kmNuMuBarCCcoh    ): name = "#bar{#nu_{#mu}} CCcoh";            break;      
    case (kmNuMuBarCCoth    ): name = "#bar{#nu_{#mu}} CCoth";            break;    

//  case (kmNuMuBarNCEL     ): name = "";                                 break;    
//  case (kmNuMuBarNCMEC    ): name = "";                                 break;    
    case (kmNuMuBarNC1piC   ): name = "#bar{#nu_{#mu}} NC1#pi^{#pm}";     break;   
    case (kmNuMuBarNC1pi0   ): name = "#bar{#nu_{#mu}} NC1#pi^{0}";       break;    
//  case (kmNuMuBarNC2piC   ): name = "";                                 break;   
//  case (kmNuMuBarNC2pi0   ): name = "";                                 break;    
//  case (kmNuMuBarNCpiCpi0 ): name = "";                                 break;   
    case (kmNuMuBarNCcoh    ): name = "#bar{#nu_{#mu}} NCcoh";            break;  
    case (kmNuMuBarNCoth    ): name = "#bar{#nu_{#mu}} NCoth";            break;       

    case (kmNuECCQE         ): name = "#nu_{e} CCQE";                     break;             
    case (kmNuECCMEC        ): name = "#nu_{e} CCMEC";                    break;         
    case (kmNuECC1piC       ): name = "#nu_{e} CC1#pi^{#pm}";             break; 
    case (kmNuECC1pi0       ): name = "#nu_{e} CC1#pi^{0}";               break;    
    case (kmNuECC2piC       ): name = "#nu_{e} CC2#pi^{#pm}";             break;    
    case (kmNuECC2pi0       ): name = "#nu_{e} CC2#pi^{0}";               break;    
    case (kmNuECCpiCpi0     ): name = "#nu_{e} CC#pi^{#pm}#pi^{0}";       break;  
    case (kmNuECCcoh        ): name = "#nu_{e} CCcoh";                    break;  
    case (kmNuECCoth        ): name = "#nu_{e} CCoth";                    break;    

//  case (kmNuENCEL         ): name = "";                                 break;    
//  case (kmNuENCMEC        ): name = "";                                 break;    
    case (kmNuENC1piC       ): name = "#nu_{e} NC1#pi^{#pm}";             break;    
    case (kmNuENC1pi0       ): name = "#nu_{e} NC1#pi^{0}";               break;    
//  case (kmNuENC2piC       ): name = "";                                 break;   
//  case (kmNuENC2pi0       ): name = "";                                 break;    
//  case (kmNuENCpiCpi0     ): name = "";                                 break;   
    case (kmNuENCcoh        ): name = "#nu_{e} NCcoh";                    break; 
    case (kmNuENCoth        ): name = "#nu_{e} NCoth";                    break;    

    case (kmNuEBarCCQE      ): name = "#bar{#nu_{e}} CCQE";               break;    
    case (kmNuEBarCCMEC     ): name = "#bar{#nu_{e}} CCMEC";              break;    
    case (kmNuEBarCC1piC    ): name = "#bar{#nu_{e}} CC1#pi^{#pm}";       break;   
    case (kmNuEBarCC1pi0    ): name = "#bar{#nu_{e}} CC1#pi^{0}";         break;    
    case (kmNuEBarCC2piC    ): name = "#bar{#nu_{e}} CC2#pi^{#pm}";       break;   
    case (kmNuEBarCC2pi0    ): name = "#bar{#nu_{e}} CC2#pi^{0}";         break;    
    case (kmNuEBarCCpiCpi0  ): name = "#bar{#nu_{e}} CC#pi^{#pm}#pi^{0}"; break;    
    case (kmNuEBarCCcoh     ): name = "#bar{#nu_{e}} CCcoh";              break;    
    case (kmNuEBarCCoth     ): name = "#bar{#nu_{e}} CCoth";              break;    

//  case (kmNuEBarNCEL      ): name = "";                                 break;   
//  case (kmNuEBarNCMEC     ): name = "";                                 break;    
    case (kmNuEBarNC1piC    ): name = "#bar{#nu_{e}} NC1#pi^{#pm}";       break;   
    case (kmNuEBarNC1pi0    ): name = "#bar{#nu_{e}} NC1#pi^{0}";         break;    
//  case (kmNuEBarNC2piC    ): name = "";                                 break;   
//  case (kmNuEBarNC2pi0    ): name = "";                                 break;    
//  case (kmNuEBarNCpiCpi0  ): name = "";                                 break;  
    case (kmNuEBarNCcoh     ): name = "#bar{#nu_{e}} NCcoh";              break;   
    case (kmNuEBarNCoth     ): name = "#bar{#nu_{e}} NCoth";              break;     

    case (kmOther           ): name = "Other";                            break;     
    default                  : name = "--"; 
  }

  if(root) return name;

  // normal TeX, not ROOT TeX - change '#' with '\'
  replace( name.begin(), name.end(), '#', '\\');

  return name;
}
//________________________________________________________________________________________
conv::NuFlavour_t  util::ReacModeToFlavor(conv::ReacMode_t m)
{
  //~ int idx = ArrIdx::Instance()->ReacModeIdx(m);
  return kReacModeToFlavour[m];
}
//________________________________________________________________________________________
bool util::IsCC(conv::ReacMode_t m)
{
  switch (m) {
    case (kmNuMuCCQE       )  : return true;
    case (kmNuMuCCMEC      )  : return true;
    case (kmNuMuCC1piC     )  : return true;
    case (kmNuMuCC1pi0     )  : return true;
    case (kmNuMuCC2piC     )  : return true;
    case (kmNuMuCC2pi0     )  : return true;
    case (kmNuMuCCpiCpi0   )  : return true;
    case (kmNuMuCCcoh      )  : return true;
    case (kmNuMuCCoth      )  : return true;
    case (kmNuMuNCcoh      )  : return true;
    case (kmNuMuNCoth      )  : return true;
    case (kmNuMuBarCCQE    )  : return true;
    case (kmNuMuBarCCMEC   )  : return true;
    case (kmNuMuBarCC1piC  )  : return true;
    case (kmNuMuBarCC1pi0  )  : return true;
    case (kmNuMuBarCC2piC  )  : return true;
    case (kmNuMuBarCC2pi0  )  : return true;
    case (kmNuMuBarCCpiCpi0)  : return true;
    case (kmNuMuBarCCcoh   )  : return true;
    case (kmNuMuBarCCoth   )  : return true;
    case (kmNuECCQE        )  : return true;
    case (kmNuECCMEC       )  : return true;
    case (kmNuECC1piC      )  : return true;
    case (kmNuECC1pi0      )  : return true;
    case (kmNuECC2piC      )  : return true;
    case (kmNuECC2pi0      )  : return true;
    case (kmNuECCpiCpi0    )  : return true;
    case (kmNuECCcoh       )  : return true;
    case (kmNuECCoth       )  : return true;
    case (kmNuEBarCCQE     )  : return true;
    case (kmNuEBarCCMEC    )  : return true;
    case (kmNuEBarCC1piC   )  : return true;
    case (kmNuEBarCC1pi0   )  : return true;
    case (kmNuEBarCC2piC   )  : return true;
    case (kmNuEBarCC2pi0   )  : return true;
    case (kmNuEBarCCpiCpi0 )  : return true;
    case (kmNuEBarCCcoh    )  : return true;
    case (kmNuEBarCCoth    )  : return true;
    
    default                  : return false;
  }
}
//________________________________________________________________________________________
ReacMode_t util::ReacModeFromInt(int m)
{
// Cast an integer to ReacMode_t, but with boundary check
//             [first]                  [last]
  if(m >= (int)kmNuMuCCQE && m <= (int) kmOther) return (ReacMode_t)m;
  return kmUndefined;
}
//________________________________________________________________________________________
//aliases for systems that can't overload based on enum type (eg python)
string util::ModeAsStringTeX(ReacMode_t m, bool root) {return AsStringTeX(m,root);}
string util::ModeAsString   (ReacMode_t m) {return AsString(m);}
//________________________________________________________________________________________
