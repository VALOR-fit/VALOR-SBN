//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include "Conventions/ReacMode.h"

using namespace valor;
using namespace valor::conv;

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
    case (kmNuMuBarCC2piC   ): return "numubarCC1piC";   break;      
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
    default                  : return "--"; 
  }
  return "";
}
//________________________________________________________________________________________
ReacMode_t util::ReacModeFromInt(int m)
{
// Cast an integer to ReacMode_t, but with boundary check
//             [first]                  [last]
  if(m >= (int)kmNuMuCCQE && m <= (int) kmNuEBarNCoth) return (ReacMode_t)m;
  return kmUndefined;
}
//________________________________________________________________________________________


	
