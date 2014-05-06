//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include "Conventions/ReacMode.h"

using namespace valor;
using namespace valor::lbnx;
using namespace valor::lbnx::conv;

//________________________________________________________________________________________
string util::AsString(ReacMode_t m)
{
  switch(m) {

    case (kmNuMuCCQE        ): return ""; break;
    case (kmNuMuCCMEC       ): return ""; break;        
    case (kmNuMuCC1piC      ): return ""; break;        
    case (kmNuMuCC1pi0      ): return ""; break;        
    case (kmNuMuCC2piC      ): return ""; break;        
    case (kmNuMuCC2pi0      ): return ""; break;        
    case (kmNuMuCCpiCpi0    ): return ""; break;         
    case (kmNuMuCCcoh       ): return ""; break;       
    case (kmNuMuCCoth       ): return ""; break;        
    case (kmNuMuNCEL        ): return ""; break;        
    case (kmNuMuNCMEC       ): return ""; break;        
    case (kmNuMuNC1piC      ): return ""; break;        
    case (kmNuMuNC1pi0      ): return ""; break;        
    case (kmNuMuNC2piC      ): return ""; break;        
    case (kmNuMuNC2pi0      ): return ""; break;        
    case (kmNuMuNCpiCpi0    ): return ""; break;       
    case (kmNuMuNCcoh       ): return ""; break;        
    case (kmNuMuNCoth       ): return ""; break;        
    case (kmNuMuBarCCQE     ): return ""; break;        
    case (kmNuMuBarCCMEC    ): return ""; break;        
    case (kmNuMuBarCC1piC   ): return ""; break;       
    case (kmNuMuBarCC1pi0   ): return ""; break;       
    case (kmNuMuBarCC2piC   ): return ""; break;      
    case (kmNuMuBarCC2pi0   ): return ""; break;       
    case (kmNuMuBarCCpiCpi0 ): return ""; break;   
    case (kmNuMuBarCCcoh    ): return ""; break;      
    case (kmNuMuBarCCoth    ): return ""; break;    
    case (kmNuMuBarNCEL     ): return ""; break;    
    case (kmNuMuBarNCMEC    ): return ""; break;    
    case (kmNuMuBarNC1piC   ): return ""; break;   
    case (kmNuMuBarNC1pi0   ): return ""; break;    
    case (kmNuMuBarNC2piC   ): return ""; break;   
    case (kmNuMuBarNC2pi0   ): return ""; break;    
    case (kmNuMuBarNCpiCpi0 ): return ""; break;   
    case (kmNuMuBarNCcoh    ): return ""; break;  
    case (kmNuMuBarNCoth    ): return ""; break;       
    case (kmNuECCQE         ): return ""; break;             
    case (kmNuECCMEC        ): return ""; break;         
    case (kmNuECC1piC       ): return ""; break; 
    case (kmNuECC1pi0       ): return ""; break;    
    case (kmNuECC2piC       ): return ""; break;    
    case (kmNuECC2pi0       ): return ""; break;    
    case (kmNuECCpiCpi0     ): return ""; break;  
    case (kmNuECCcoh        ): return ""; break;  
    case (kmNuECCoth        ): return ""; break;    
    case (kmNuENCEL         ): return ""; break;    
    case (kmNuENCMEC        ): return ""; break;    
    case (kmNuENC1piC       ): return ""; break;    
    case (kmNuENC1pi0       ): return ""; break;    
    case (kmNuENC2piC       ): return ""; break;   
    case (kmNuENC2pi0       ): return ""; break;    
    case (kmNuENCpiCpi0     ): return ""; break;   
    case (kmNuENCcoh        ): return ""; break; 
    case (kmNuENCoth        ): return ""; break;    
    case (kmNuEBarCCQE      ): return ""; break;    
    case (kmNuEBarCCMEC     ): return ""; break;    
    case (kmNuEBarCC1piC    ): return ""; break;   
    case (kmNuEBarCC1pi0    ): return ""; break;    
    case (kmNuEBarCC2piC    ): return ""; break;   
    case (kmNuEBarCC2pi0    ): return ""; break;    
    case (kmNuEBarCCpiCpi0  ): return ""; break;    
    case (kmNuEBarCCcoh     ): return ""; break;    
    case (kmNuEBarCCoth     ): return ""; break;    
    case (kmNuEBarNCEL      ): return ""; break;   
    case (kmNuEBarNCMEC     ): return ""; break;    
    case (kmNuEBarNC1piC    ): return ""; break;   
    case (kmNuEBarNC1pi0    ): return ""; break;    
    case (kmNuEBarNC2piC    ): return ""; break;   
    case (kmNuEBarNC2pi0    ): return ""; break;    
    case (kmNuEBarNCpiCpi0  ): return ""; break;  
    case (kmNuEBarNCcoh     ): return ""; break;   
    case (kmNuEBarNCoth     ): return ""; break;     
    default                  : return "--"; 
  }
  return "";
}
//________________________________________________________________________________________

	
