//____________________________________________________________________________
/*!

\file      SampleReacMode

\brief     Define which true reaction modes to consider for each sample

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

\created   March 20, 2014

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_sample_reac_modes_h_
#define _valor_dune_sample_reac_modes_h_

#include "dune/Conventions/BeamConf.h"
#include "dune/Conventions/Sample.h"
#include "dune/Conventions/ReacMode.h"
#include "dune/Conventions/ReacModeCoarse.h"


namespace valor {  
namespace conv {

//
// ---------------------------------------------------------------------------
// Define which true reaction modes are considered for each sample 
// included in the analysis
// ---------------------------------------------------------------------------
//
  
  static const ReacMode_t kReactionModes[kNSamples][kNReacModes]  = 
    {
      // 2016b near detector selections
      // selection: ksNuMuCC0pi1trk
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },

      // selection: ksNuMuCC0pi2trk
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,      
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },

      // selection: ksNuMuCC0piNtrk
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },

      // selection: ksNuMuCC3trkDelta
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },

      // selection: ksNuMuCC1piC
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },

      // selection: ksNuMuCC1pi0
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },

      // selection: ksNuMuCC1piC1pi0
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },

      // selection: ksNuMuCCoth
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },

      // selection: ksNuMuCCWS0pi
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },
      // selection: ksNuMuCCWS1piC
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },
      // selection: ksNuMuCCWS1pi0
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },
      // selection: ksNuMuCCWSoth
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },
      // selection: ksNuECC0pi
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },
      // selection: ksNuECC1piC
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },
      // selection: ksNuECC1pi0
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },
      // selection: ksNuECCoth
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },
      // selection: ksNC0pi
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },
      // selection: ksNC1piC
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },
      // selection: ksNC1pi0
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },
      // selection: ksNCoth
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },
      // selection: ksNeutrinoElec
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },
      // selection: ksInvMuDecay
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },
      // selection: ksNuECCWS
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,  
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined,
	kmUndefined
      },
      //far detector
      // selection: ksNuMuCChigh/ksNuMuBarCChigh
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmNuMuToNuECCQE, 
	kmNuMuToNuECCMEC,
	kmNuMuToNuECC1piC,
	kmNuMuToNuECC1pi0,
	kmNuMuToNuECC2piC,
	kmNuMuToNuECC2pi0,
	kmNuMuToNuECCpiCpi0,
	kmNuMuToNuECCcoh,   
	kmNuMuToNuEELScat,  
	kmNuMuToNuECCoth,   
	kmNuMuToNuTauCCQE,  
	kmNuMuToNuTauCCMEC, 
	kmNuMuToNuTauCC1piC,
	kmNuMuToNuTauCC1pi0,
	kmNuMuToNuTauCC2piC,
	kmNuMuToNuTauCC2pi0,
	kmNuMuToNuTauCCpiCpi0,
	kmNuMuToNuTauCCcoh,   
	kmNuMuToNuTauCCELScat,
	kmNuMuToNuTauCCoth,   
	kmNuEToNuMuCCQE, 
	kmNuEToNuMuCCMEC,
	kmNuEToNuMuCC1piC,
	kmNuEToNuMuCC1pi0,
	kmNuEToNuMuCC2piC,
	kmNuEToNuMuCC2pi0,
	kmNuEToNuMuCCpiCpi0,
	kmNuEToNuMuCCcoh,   
	kmNuEToNuMuCCIMD,
	kmNuEToNuMuCCELScat,
	kmNuEToNuMuCCoth,   
	kmNuEToNuTauCCQE,   
	kmNuEToNuTauCCMEC,  
	kmNuEToNuTauCC1piC, 
	kmNuEToNuTauCC1pi0, 
	kmNuEToNuTauCC2piC, 
	kmNuEToNuTauCC2pi0, 
	kmNuEToNuTauCCpiCpi0, 
	kmNuEToNuTauCCcoh,    
	kmNuEToNuTauCCELScat, 
	kmNuEToNuTauCCoth,    
	kmNuMuBarToNuEBarCCQE,
	kmNuMuBarToNuEBarCCMEC, 
	kmNuMuBarToNuEBarCC1piC, 
	kmNuMuBarToNuEBarCC1pi0, 
	kmNuMuBarToNuEBarCC2piC, 
	kmNuMuBarToNuEBarCC2pi0, 
	kmNuMuBarToNuEBarCCpiCpi0,
	kmNuMuBarToNuEBarCCcoh,   
	kmNuMuBarToNuEBarCCIMD,
	kmNuMuBarToNuEBarELScat,  
	kmNuMuBarToNuEBarCCoth,   
	kmNuMuBarToNuTauBarCCQE,  
	kmNuMuBarToNuTauBarCCMEC, 
	kmNuMuBarToNuTauBarCC1piC,
	kmNuMuBarToNuTauBarCC1pi0, 
	kmNuMuBarToNuTauBarCC2piC, 
	kmNuMuBarToNuTauBarCC2pi0, 
	kmNuMuBarToNuTauBarCCpiCpi0,
	kmNuMuBarToNuTauBarCCcoh,   
	kmNuMuBarToNuTauBarCCELScat,
	kmNuMuBarToNuTauBarCCoth,   
	kmNuEBarToNuMuBarCCQE,      
	kmNuEBarToNuMuBarCCMEC,     
	kmNuEBarToNuMuBarCC1piC,    
	kmNuEBarToNuMuBarCC1pi0,    
	kmNuEBarToNuMuBarCC2piC,    
	kmNuEBarToNuMuBarCC2pi0,
	kmNuEBarToNuMuBarCCpiCpi0,
	kmNuEBarToNuMuBarCCcoh,
	kmNuEBarToNuMuBarCCELScat,
	kmNuEBarToNuMuBarCCoth,
	kmNuEBarToNuTauBarCCQE,
	kmNuEBarToNuTauBarCCMEC,
	kmNuEBarToNuTauBarCC1piC,
	kmNuEBarToNuTauBarCC1pi0,
	kmNuEBarToNuTauBarCC2piC,
	kmNuEBarToNuTauBarCC2pi0,
	kmNuEBarToNuTauBarCCpiCpi0,
	kmNuEBarToNuTauBarCCcoh,
	kmNuEBarToNuTauBarCCELScat,
	kmNuEBarToNuTauBarCCoth
      },
      // selection: ksNuMuCClow/ksNuMuBarCClow
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,          
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmNuMuToNuECCQE, 
	kmNuMuToNuECCMEC,
	kmNuMuToNuECC1piC,
	kmNuMuToNuECC1pi0,
	kmNuMuToNuECC2piC,
	kmNuMuToNuECC2pi0,
	kmNuMuToNuECCpiCpi0,
	kmNuMuToNuECCcoh,   
	kmNuMuToNuEELScat,  
	kmNuMuToNuECCoth,   
	kmNuMuToNuTauCCQE,  
	kmNuMuToNuTauCCMEC, 
	kmNuMuToNuTauCC1piC,
	kmNuMuToNuTauCC1pi0,
	kmNuMuToNuTauCC2piC,
	kmNuMuToNuTauCC2pi0,
	kmNuMuToNuTauCCpiCpi0,
	kmNuMuToNuTauCCcoh,   
	kmNuMuToNuTauCCELScat,
	kmNuMuToNuTauCCoth,   
	kmNuEToNuMuCCQE, 
	kmNuEToNuMuCCMEC,
	kmNuEToNuMuCC1piC,
	kmNuEToNuMuCC1pi0,
	kmNuEToNuMuCC2piC,
	kmNuEToNuMuCC2pi0,
	kmNuEToNuMuCCpiCpi0,
	kmNuEToNuMuCCcoh,   
	kmNuEToNuMuCCIMD,
	kmNuEToNuMuCCELScat,
	kmNuEToNuMuCCoth,   
	kmNuEToNuTauCCQE,   
	kmNuEToNuTauCCMEC,  
	kmNuEToNuTauCC1piC, 
	kmNuEToNuTauCC1pi0, 
	kmNuEToNuTauCC2piC, 
	kmNuEToNuTauCC2pi0, 
	kmNuEToNuTauCCpiCpi0, 
	kmNuEToNuTauCCcoh,    
	kmNuEToNuTauCCELScat, 
	kmNuEToNuTauCCoth,    
	kmNuMuBarToNuEBarCCQE,
	kmNuMuBarToNuEBarCCMEC, 
	kmNuMuBarToNuEBarCC1piC, 
	kmNuMuBarToNuEBarCC1pi0, 
	kmNuMuBarToNuEBarCC2piC, 
	kmNuMuBarToNuEBarCC2pi0, 
	kmNuMuBarToNuEBarCCpiCpi0,
	kmNuMuBarToNuEBarCCcoh,   
	kmNuMuBarToNuEBarCCIMD,
	kmNuMuBarToNuEBarELScat,  
	kmNuMuBarToNuEBarCCoth,   
	kmNuMuBarToNuTauBarCCQE,  
	kmNuMuBarToNuTauBarCCMEC, 
	kmNuMuBarToNuTauBarCC1piC,
	kmNuMuBarToNuTauBarCC1pi0, 
	kmNuMuBarToNuTauBarCC2piC, 
	kmNuMuBarToNuTauBarCC2pi0, 
	kmNuMuBarToNuTauBarCCpiCpi0,
	kmNuMuBarToNuTauBarCCcoh,   
	kmNuMuBarToNuTauBarCCELScat,
	kmNuMuBarToNuTauBarCCoth,   
	kmNuEBarToNuMuBarCCQE,      
	kmNuEBarToNuMuBarCCMEC,     
	kmNuEBarToNuMuBarCC1piC,    
	kmNuEBarToNuMuBarCC1pi0,    
	kmNuEBarToNuMuBarCC2piC,    
	kmNuEBarToNuMuBarCC2pi0,
	kmNuEBarToNuMuBarCCpiCpi0,
	kmNuEBarToNuMuBarCCcoh,
	kmNuEBarToNuMuBarCCELScat,
	kmNuEBarToNuMuBarCCoth,
	kmNuEBarToNuTauBarCCQE,
	kmNuEBarToNuTauBarCCMEC,
	kmNuEBarToNuTauBarCC1piC,
	kmNuEBarToNuTauBarCC1pi0,
	kmNuEBarToNuTauBarCC2piC,
	kmNuEBarToNuTauBarCC2pi0,
	kmNuEBarToNuTauBarCCpiCpi0,
	kmNuEBarToNuTauBarCCcoh,
	kmNuEBarToNuTauBarCCELScat,
	kmNuEBarToNuTauBarCCoth
      },
      // selection: ksNuECChigh/ksNuEBarCChigh
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmNuMuToNuECCQE, 
	kmNuMuToNuECCMEC,
	kmNuMuToNuECC1piC,
	kmNuMuToNuECC1pi0,
	kmNuMuToNuECC2piC,
	kmNuMuToNuECC2pi0,
	kmNuMuToNuECCpiCpi0,
	kmNuMuToNuECCcoh,   
	kmNuMuToNuEELScat,  
	kmNuMuToNuECCoth,   
	kmNuMuToNuTauCCQE,  
	kmNuMuToNuTauCCMEC, 
	kmNuMuToNuTauCC1piC,
	kmNuMuToNuTauCC1pi0,
	kmNuMuToNuTauCC2piC,
	kmNuMuToNuTauCC2pi0,
	kmNuMuToNuTauCCpiCpi0,
	kmNuMuToNuTauCCcoh,   
	kmNuMuToNuTauCCELScat,
	kmNuMuToNuTauCCoth,   
	kmNuEToNuMuCCQE, 
	kmNuEToNuMuCCMEC,
	kmNuEToNuMuCC1piC,
	kmNuEToNuMuCC1pi0,
	kmNuEToNuMuCC2piC,
	kmNuEToNuMuCC2pi0,
	kmNuEToNuMuCCpiCpi0,
	kmNuEToNuMuCCcoh,   
	kmNuEToNuMuCCIMD,
	kmNuEToNuMuCCELScat,
	kmNuEToNuMuCCoth,   
	kmNuEToNuTauCCQE,   
	kmNuEToNuTauCCMEC,  
	kmNuEToNuTauCC1piC, 
	kmNuEToNuTauCC1pi0, 
	kmNuEToNuTauCC2piC, 
	kmNuEToNuTauCC2pi0, 
	kmNuEToNuTauCCpiCpi0, 
	kmNuEToNuTauCCcoh,    
	kmNuEToNuTauCCELScat, 
	kmNuEToNuTauCCoth,    
	kmNuMuBarToNuEBarCCQE,
	kmNuMuBarToNuEBarCCMEC, 
	kmNuMuBarToNuEBarCC1piC, 
	kmNuMuBarToNuEBarCC1pi0, 
	kmNuMuBarToNuEBarCC2piC, 
	kmNuMuBarToNuEBarCC2pi0, 
	kmNuMuBarToNuEBarCCpiCpi0,
	kmNuMuBarToNuEBarCCcoh,   
	kmNuMuBarToNuEBarCCIMD,
	kmNuMuBarToNuEBarELScat,  
	kmNuMuBarToNuEBarCCoth,   
	kmNuMuBarToNuTauBarCCQE,  
	kmNuMuBarToNuTauBarCCMEC, 
	kmNuMuBarToNuTauBarCC1piC,
	kmNuMuBarToNuTauBarCC1pi0, 
	kmNuMuBarToNuTauBarCC2piC, 
	kmNuMuBarToNuTauBarCC2pi0, 
	kmNuMuBarToNuTauBarCCpiCpi0,
	kmNuMuBarToNuTauBarCCcoh,   
	kmNuMuBarToNuTauBarCCELScat,
	kmNuMuBarToNuTauBarCCoth,   
	kmNuEBarToNuMuBarCCQE,      
	kmNuEBarToNuMuBarCCMEC,     
	kmNuEBarToNuMuBarCC1piC,    
	kmNuEBarToNuMuBarCC1pi0,    
	kmNuEBarToNuMuBarCC2piC,    
	kmNuEBarToNuMuBarCC2pi0,
	kmNuEBarToNuMuBarCCpiCpi0,
	kmNuEBarToNuMuBarCCcoh,
	kmNuEBarToNuMuBarCCELScat,
	kmNuEBarToNuMuBarCCoth,
	kmNuEBarToNuTauBarCCQE,
	kmNuEBarToNuTauBarCCMEC,
	kmNuEBarToNuTauBarCC1piC,
	kmNuEBarToNuTauBarCC1pi0,
	kmNuEBarToNuTauBarCC2piC,
	kmNuEBarToNuTauBarCC2pi0,
	kmNuEBarToNuTauBarCCpiCpi0,
	kmNuEBarToNuTauBarCCcoh,
	kmNuEBarToNuTauBarCCELScat,
	kmNuEBarToNuTauBarCCoth
      },
      // selection: ksNuECClow/ksNuEBarCClow
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCIMD,
	kmNuMuCCELScat,
	kmNuMuCCoth,           
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCELScat,
	kmNuMuNCoth,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCELScat,
	kmNuMuBarCCoth,        
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCELScat,
	kmNuMuBarNCoth, 
	kmNuECCQE,             
	kmNuECCMEC,            
	kmNuECC1piC,           
	kmNuECC1pi0,           
	kmNuECC2piC,           
	kmNuECC2pi0,           
	kmNuECCpiCpi0,         
	kmNuECCcoh,            
	kmNuECCoth,            
	//kmNuENCEL,             
	//kmNuENCMEC,           
	kmNuENC1piC,           
	kmNuENC1pi0,           
	//kmNuENC2piC,           
	//kmNuENC2pi0,           
	//kmNuENCpiCpi0,         
	kmNuENCcoh,            
	kmNuEELScat,
	kmNuENCoth,            
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCIMD,
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,
	kmNuEBarELScat,         
	kmNuEBarNCoth,
	kmNuMuToNuECCQE, 
	kmNuMuToNuECCMEC,
	kmNuMuToNuECC1piC,
	kmNuMuToNuECC1pi0,
	kmNuMuToNuECC2piC,
	kmNuMuToNuECC2pi0,
	kmNuMuToNuECCpiCpi0,
	kmNuMuToNuECCcoh,   
	kmNuMuToNuEELScat,  
	kmNuMuToNuECCoth,   
	kmNuMuToNuTauCCQE,  
	kmNuMuToNuTauCCMEC, 
	kmNuMuToNuTauCC1piC,
	kmNuMuToNuTauCC1pi0,
	kmNuMuToNuTauCC2piC,
	kmNuMuToNuTauCC2pi0,
	kmNuMuToNuTauCCpiCpi0,
	kmNuMuToNuTauCCcoh,   
	kmNuMuToNuTauCCELScat,
	kmNuMuToNuTauCCoth,   
	kmNuEToNuMuCCQE, 
	kmNuEToNuMuCCMEC,
	kmNuEToNuMuCC1piC,
	kmNuEToNuMuCC1pi0,
	kmNuEToNuMuCC2piC,
	kmNuEToNuMuCC2pi0,
	kmNuEToNuMuCCpiCpi0,
	kmNuEToNuMuCCcoh,   
	kmNuEToNuMuCCIMD,
	kmNuEToNuMuCCELScat,
	kmNuEToNuMuCCoth,   
	kmNuEToNuTauCCQE,   
	kmNuEToNuTauCCMEC,  
	kmNuEToNuTauCC1piC, 
	kmNuEToNuTauCC1pi0, 
	kmNuEToNuTauCC2piC, 
	kmNuEToNuTauCC2pi0, 
	kmNuEToNuTauCCpiCpi0, 
	kmNuEToNuTauCCcoh,    
	kmNuEToNuTauCCELScat, 
	kmNuEToNuTauCCoth,    
	kmNuMuBarToNuEBarCCQE,
	kmNuMuBarToNuEBarCCMEC, 
	kmNuMuBarToNuEBarCC1piC, 
	kmNuMuBarToNuEBarCC1pi0, 
	kmNuMuBarToNuEBarCC2piC, 
	kmNuMuBarToNuEBarCC2pi0, 
	kmNuMuBarToNuEBarCCpiCpi0,
	kmNuMuBarToNuEBarCCcoh,   
	kmNuMuBarToNuEBarCCIMD,
	kmNuMuBarToNuEBarELScat,  
	kmNuMuBarToNuEBarCCoth,   
	kmNuMuBarToNuTauBarCCQE,  
	kmNuMuBarToNuTauBarCCMEC, 
	kmNuMuBarToNuTauBarCC1piC,
	kmNuMuBarToNuTauBarCC1pi0, 
	kmNuMuBarToNuTauBarCC2piC, 
	kmNuMuBarToNuTauBarCC2pi0, 
	kmNuMuBarToNuTauBarCCpiCpi0,
	kmNuMuBarToNuTauBarCCcoh,   
	kmNuMuBarToNuTauBarCCELScat,
	kmNuMuBarToNuTauBarCCoth,   
	kmNuEBarToNuMuBarCCQE,      
	kmNuEBarToNuMuBarCCMEC,     
	kmNuEBarToNuMuBarCC1piC,    
	kmNuEBarToNuMuBarCC1pi0,    
	kmNuEBarToNuMuBarCC2piC,    
	kmNuEBarToNuMuBarCC2pi0,
	kmNuEBarToNuMuBarCCpiCpi0,
	kmNuEBarToNuMuBarCCcoh,
	kmNuEBarToNuMuBarCCELScat,
	kmNuEBarToNuMuBarCCoth,
	kmNuEBarToNuTauBarCCQE,
	kmNuEBarToNuTauBarCCMEC,
	kmNuEBarToNuTauBarCC1piC,
	kmNuEBarToNuTauBarCC1pi0,
	kmNuEBarToNuTauBarCC2piC,
	kmNuEBarToNuTauBarCC2pi0,
	kmNuEBarToNuTauBarCCpiCpi0,
	kmNuEBarToNuTauBarCCcoh,
	kmNuEBarToNuTauBarCCELScat,
	kmNuEBarToNuTauBarCCoth
      }
};
  
   
//
// ---------------------------------------------------------------------------
// Define ReacModeCoarse_t types (used only in plots) for each sample 
// ---------------------------------------------------------------------------
//

// The order of ReacModeCoarse_t types below, is the order with which the
// corresponding contributions enter in the plotted THStacks.

static const int kNReacModesCoarse = 8;  // max coarse modes used per sample

static const ReacModeCoarse_t kReactionModesCoarse[kNBeamConf][kNSamples][kNReacModesCoarse] = 
{
  // FHC
  {
    // sample: ksNuMuCC0pi1trk
    {
      kmcNuMuCCQE,    
      kmcNuMuCCMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC           
    },
    // sample: ksNuMuCC0pi2trk
    {
      kmcNuMuCCQE,    
      kmcNuMuCCMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC           
    },
    // sample: ksNuMuCC0piNtrk
    {
      kmcNuMuCCQE,    
      kmcNuMuCCMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC           
    },
    // sample: ksNuMuCC0pi3trkDelta
    {
      kmcNuMuCCQE,    
      kmcNuMuCCMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC           
    },
    // sample: ksNuMuCC1piC
    {
      kmcNuMuCCQEMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuMuCC1pi0
    {
      kmcNuMuCCQEMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined           
    },
    // sample: ksNuMuCC1piC1pi0
    {
      kmcNuMuCCQEMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined           
    },
    // sample: ksNuMuCCoth
    {
      kmcNuMuCCQEMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined          
    },
    // sample: ksNuMuCCWS0pi
    {
      kmcNuMuBarCCQEMEC,    
      kmcNuMuBarCC1pi,   
      kmcNuMuBarCC2pi,   
      kmcNuMuBarCCoth,   
      kmcNuMuCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined           
    },
    // sample: ksNuMuCCWS1piC
    {
      kmcNuMuBarCCQEMEC,    
      kmcNuMuBarCC1pi,   
      kmcNuMuBarCC2pi,   
      kmcNuMuBarCCoth,   
      kmcNuMuCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined           
    },
    // sample: ksNuMuCCWS1pi0
    {
      kmcNuMuBarCCQEMEC,    
      kmcNuMuBarCC1pi,   
      kmcNuMuBarCC2pi,   
      kmcNuMuBarCCoth,   
      kmcNuMuCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined           
    },
    // sample: ksNuMuCCWSoth
    {
      kmcNuMuBarCCQEMEC,    
      kmcNuMuBarCC1pi,   
      kmcNuMuBarCC2pi,   
      kmcNuMuBarCCoth,   
      kmcNuMuCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined           
    },
    // sample: ksNuECC0pi
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined          
    },
    // sample: ksNuECC1piC
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined          
    },
    // sample: ksNuECC1pi0
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined          
    },
    // sample: ksNuECCoth
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined          
    },
    // sample: ksNC0pi
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1piC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined          
    },
    // sample: ksNC1piC
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1piC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined          
    },
    // sample: ksNC1pi0
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1piC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined          
    },
    // sample: ksNCoth
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1piC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined          
    },
    //TODO: revisit ksNeutrinoElec and ksInvMuDecay
    // sample: ksNeutrinoElec
    {
      kmcNuMuCCQE,    
      kmcNuMuCCMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC           
    },
    // sample: ksInvMuDecay
    {
      kmcNuMuCCQE,    
      kmcNuMuCCMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC           
    },
    // sample: ksNuECCWS
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined          
    },
    //TODO: revisit far detector ones, for the moment similarly to ND ones
    //2016b far detector selections
    // sample: ksNuMuCChigh
    {
      kmcNuMuCCQE,    
      kmcNuMuCCMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC           
    },
    // sample: ksNuMuCClow
    {
      kmcNuMuCCQEMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuECChigh
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined          
    },
    // sample: ksNuECClow
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined          
    }
  }, // end of FHC
  //RHC
  {
    // sample: ksNuMuCC0pi1trk
    {
      kmcNuMuBarCCQE,
      kmcNuMuBarCCMEC,
      kmcNuMuBarCC1pi,
      kmcNuMuBarCC2pi,
      kmcNuMuBarCCoth,
      kmcNuMuCC,
      kmcNuENuEBarCC,
      kmcNC
    },
    // sample: ksNuMuCC0pi2trk
    {
      kmcNuMuBarCCQE,
      kmcNuMuBarCCMEC,
      kmcNuMuBarCC1pi,
      kmcNuMuBarCC2pi,
      kmcNuMuBarCCoth,
      kmcNuMuCC,
      kmcNuENuEBarCC,
      kmcNC
    },
    // sample: ksNuMuCC0piNtrk
    {
      kmcNuMuBarCCQE,
      kmcNuMuBarCCMEC,
      kmcNuMuBarCC1pi,
      kmcNuMuBarCC2pi,
      kmcNuMuBarCCoth,
      kmcNuMuCC,
      kmcNuENuEBarCC,
      kmcNC
    },
    // sample: ksNuMuCC0pi3trkDelta
    {
      kmcNuMuBarCCQE,
      kmcNuMuBarCCMEC,
      kmcNuMuBarCC1pi,
      kmcNuMuBarCC2pi,
      kmcNuMuBarCCoth,
      kmcNuMuCC,
      kmcNuENuEBarCC,
      kmcNC
    },
    // sample: ksNuMuCC1piC
    {
      kmcNuMuBarCCQEMEC,
      kmcNuMuBarCC1pi,
      kmcNuMuBarCC2pi,
      kmcNuMuBarCCoth,
      kmcNuMuCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuMuCC1pi0
    {
      kmcNuMuBarCCQEMEC,
      kmcNuMuBarCC1pi,
      kmcNuMuBarCC2pi,
      kmcNuMuBarCCoth,
      kmcNuMuCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuMuCC1piC1pi0
    {
      kmcNuMuBarCCQEMEC,
      kmcNuMuBarCC1pi,
      kmcNuMuBarCC2pi,
      kmcNuMuBarCCoth,
      kmcNuMuCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuMuCCoth
    {
      kmcNuMuBarCCQEMEC,
      kmcNuMuBarCC1pi,
      kmcNuMuBarCC2pi,
      kmcNuMuBarCCoth,
      kmcNuMuCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuMuCCWS0pi
    {
      kmcNuMuCCQEMEC,
      kmcNuMuCC1pi,
      kmcNuMuCC2pi,
      kmcNuMuCCoth,
      kmcNuMuBarCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuMuCCWS1piC
    {
      kmcNuMuCCQEMEC,
      kmcNuMuCC1pi,
      kmcNuMuCC2pi,
      kmcNuMuCCoth,
      kmcNuMuBarCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuMuCCWS1pi0
    {
      kmcNuMuCCQEMEC,
      kmcNuMuCC1pi,
      kmcNuMuCC2pi,
      kmcNuMuCCoth,
      kmcNuMuBarCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuMuCCWSoth
    {
      kmcNuMuCCQEMEC,
      kmcNuMuCC1pi,
      kmcNuMuCC2pi,
      kmcNuMuCCoth,
      kmcNuMuBarCC,
      kmcNuENuEBarCC,
      kmcNC,
      kmcUndefined
    },
    // sample: ksNuECC0pi
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined          
    },
    // sample: ksNuECC1piC
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined          
    },
    // sample: ksNuECC1pi0
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined          
    },
    // sample: ksNuECCoth
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined          
    },
    // sample: ksNC0pi
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1piC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined          
    },
    // sample: ksNC1piC
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1piC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined          
    },
    // sample: ksNC1pi0
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1piC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined          
    },
    // sample: ksNCoth
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1piC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined          
    },
    //TODO: revisit ksNeutrinoElec and ksInvMuDecay
    // sample: ksNeutrinoElec
    {
      kmcNuMuCCQE,    
      kmcNuMuCCMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC           
    },
    // sample: ksInvMuDecay
    {
      kmcNuMuCCQE,    
      kmcNuMuCCMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNC           
    },
    // sample: ksNuECCWS
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined,
      kmcUndefined          
    },
    //TODO: revisit far detector ones, for the moment similarly to ND ones
    //2016b far detector selections
    // sample: ksNuMuBarCChigh
    {
      kmcNuMuCCQEMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNuTauNuTauBarCC,
      kmcNC           
    },
    // sample: ksNuMuBarCClow
    {
      kmcNuMuCCQEMEC,    
      kmcNuMuCC1pi,   
      kmcNuMuCC2pi,   
      kmcNuMuCCoth,   
      kmcNuMuBarCC,   
      kmcNuENuEBarCC, 
      kmcNuTauNuTauBarCC,
      kmcNC           
    },
    // sample: ksNuEBarCChigh
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNuTauNuTauBarCC,
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined          
    },
    // sample: ksNuEBarCClow
    {
      kmcNuMuCC,    
      kmcNuMuBarCC,   
      kmcNuECC,   
      kmcNuEBarCC,   
      kmcNuTauNuTauBarCC,
      kmcNC1pi0,   
      kmcNCoth,   
      kmcUndefined          
    }
  }
};

//
// Also, specify formatting (line color, fill color, fill style)
//

static const int kReactionModesCoarseFormatting[kNBeamConf][kNSamples][kNReacModesCoarse][3] = 
{
  // FHC
  {
    // sample: ksNuMuCC0pi1trk
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }  // kmcNC           
    },
    // sample: ksNuMuCC0pi2trk
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }  // kmcNC           
    },
    // sample: ksNuMuCC0piNtrk,
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }  // kmcNC           
    },
    // sample: ksNuMuCC3trkDelta
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }  // kmcNC           
    },
    // sample: ksNuMuCC1piC
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCC1pi0
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCC1piC1pi0
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCCoth
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC         
      {0,0,0}  
    },
    // sample: ksNuMuCCWS0pi
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCCWS1piC
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCCWS1pi0
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCCWSoth
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuECC0pi
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0},        
      {0,0,0}  
    },
    // sample: ksNuECC1piC
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0},        
      {0,0,0}  
    },
    // sample: ksNuECC1pi0
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0},        
      {0,0,0}  
    },
    // sample: ksNuECCoth
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0},        
      {0,0,0}  
    },
    // sample: ksNC0pi
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3022 }, // kmcNC1piC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0}  
    },
    // sample: ksNC1piC
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3022 }, // kmcNC1piC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0}  
    },
    // sample: ksNC1pi0
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3022 }, // kmcNC1piC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0}  
    },
    // sample: ksNCoth
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3022 }, // kmcNC1piC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth   
      {0,0,0}  
    },
    // sample: ksNeutrinoElec
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE 
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC 
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi 
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi 
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth 
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC 
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC 
      { kBlack, kRed,      3001 }  // kmcNC 
    },
    // sample: ksInvMuDecay
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE 
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC 
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi 
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi 
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth 
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC 
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC 
      { kBlack, kRed,      3001 }  // kmcNC 
    },
    // sample: ksNuECCWS
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    //far detector samples
    // sample: ksNuMuCChigh/ksNuMuBarCChigh
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE 
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC 
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi 
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi 
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth 
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC 
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC 
      { kBlack, kRed,      3001 }  // kmcNC 
    },
    // sample: ksNuMuCClow/ksNuMuBarCClow
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE 
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC 
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi 
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi 
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth 
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC 
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC 
      { kBlack, kRed,      3001 }  // kmcNC 
    },
    // sample: ksNuECChigh/ksNuEBarCChigh
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0},        
      {0,0,0}  
    },
    // sample: ksNuECClow/ksNuEBarCClow
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0},        
      {0,0,0}  
    }
  }, // end of FHC
  // RHC
  {
    // sample: ksNuMuCC0pi1trk
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }  // kmcNC           
    },
    // sample: ksNuMuCC0pi2trk
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }  // kmcNC           
    },
    // sample: ksNuMuCC0piNtrk,
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }  // kmcNC           
    },
    // sample: ksNuMuCC3trkDelta
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }  // kmcNC           
    },
    // sample: ksNuMuCC1piC
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCC1pi0
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCC1piC1pi0
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCCoth
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC         
      {0,0,0}  
    },
    // sample: ksNuMuCCWS0pi
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCCWS1piC
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCCWS1pi0
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuMuCCWSoth
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    // sample: ksNuECC0pi
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kViolet-1, 3001 }, // kmcNuECC
      { kBlack, kWhite,    3544 }, // kmcNuEBarCC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0},        
      {0,0,0}  
    },
    // sample: ksNuECC1piC
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kViolet-1, 3001 }, // kmcNuECC
      { kBlack, kWhite,    3544 }, // kmcNuEBarCC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0},        
      {0,0,0}  
    },
    // sample: ksNuECC1pi0
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kViolet-1, 3001 }, // kmcNuECC
      { kBlack, kWhite,    3544 }, // kmcNuEBarCC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0},        
      {0,0,0}  
    },
    // sample: ksNuECCoth
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kViolet-1, 3001 }, // kmcNuECC
      { kBlack, kWhite,    3544 }, // kmcNuEBarCC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0},        
      {0,0,0}  
    },
    // sample: ksNC0pi
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3022 }, // kmcNC1piC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0}  
    },
    // sample: ksNC1piC
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3022 }, // kmcNC1piC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0}  
    },
    // sample: ksNC1pi0
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3022 }, // kmcNC1piC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth   
      {0,0,0}  
    },
    // sample: ksNCoth
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3022 }, // kmcNC1piC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0}  
    },
    // sample: ksNeutrinoElec
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE 
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC 
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi 
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi 
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth 
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC 
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC 
      { kBlack, kRed,      3001 }  // kmcNC 
    },
    // sample: ksInvMuDecay
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE 
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC 
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi 
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi 
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth 
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC 
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC 
      { kBlack, kRed,      3001 }  // kmcNC 
    },
    // sample: ksNuECCWS
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQEMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }, // kmcNC           
      {0,0,0}
    },
    //far detector samples
    // sample: ksNuMuCChigh/ksNuMuBarCChigh
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE 
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC 
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi 
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi 
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth 
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC 
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC 
      { kBlack, kRed,      3001 }  // kmcNC 
    },
    // sample: ksNuMuCClow/ksNuMuBarCClow
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuCCQE 
      { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC 
      { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi 
      { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi 
      { kBlack, kGreen,    3007 }, // kmcNuMuCCoth 
      { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC 
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC 
      { kBlack, kRed,      3001 }  // kmcNC 
    },
    // sample: ksNuECChigh/ksNuEBarCChigh
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0},        
      {0,0,0}  
    },
    // sample: ksNuECClow/ksNuEBarCClow
    {
      { kBlack, kBlue,     3001 }, // kmcNuMuCC   
      { kBlack, kGreen,    3001 }, // kmcNuMuBarCC
      { kBlack, kWhite,    3544 }, // kmcNuECC
      { kBlack, kViolet-1, 3001 }, // kmcNuEBarCC
      { kBlack, kRed,      3004 }, // kmcNC1pi0
      { kBlack, kRed,      3001 }, // kmcNCoth
      {0,0,0},        
      {0,0,0}  
    }
  } // end of RHC
};

//
// ---------------------------------------------------------------------------
// Specify how each ReacMode_t is mapped onto the ReacModeCoarse_t types.
// ---------------------------------------------------------------------------
//

static const ReacModeCoarse_t kMappingToCoarseModes[kNBeamConf][kNSamples][kNReacModes] = 
{
  //FHC
  {
    // selection: ksNuMuCC0pi1trk
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCIMD           
      kmcNuMuCCoth,   // kmNuMuCCoth 
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
       },
    // selection: ksNuMuCC0pi2trk
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCIMD           
      kmcNuMuCCoth,   // kmNuMuCCoth 
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNuMuCC0piNtrk
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCIMD           
      kmcNuMuCCoth,   // kmNuMuCCoth 
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNuMuCC3trkDelta
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCIMD           
      kmcNuMuCCoth,   // kmNuMuCCoth 
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNuMuCC1piC
    {
      kmcNuMuCCQEMEC,   // kmNuMuCCQE            
      kmcNuMuCCQEMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCIMD           
      kmcNuMuCCoth,   // kmNuMuCCoth 
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNuMuCC1pi0
    {
      kmcNuMuCCQEMEC,    // kmNuMuCCQE            
      kmcNuMuCCQEMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCIMD           
      kmcNuMuCCoth,   // kmNuMuCCoth 
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNuMuCC1piC1pi0
    {
      kmcNuMuCCQEMEC,    // kmNuMuCCQE            
      kmcNuMuCCQEMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCIMD           
      kmcNuMuCCoth,   // kmNuMuCCoth 
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNuMuCCoth
    {
      kmcNuMuCCQEMEC,    // kmNuMuCCQE            
      kmcNuMuCCQEMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCIMD           
      kmcNuMuCCoth,   // kmNuMuCCoth 
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNuMuCCWS0pi
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCCQEMEC,   // kmNuMuBarCCQE         
      kmcNuMuBarCCQEMEC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC1pi,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC1pi,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC2pi,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC2pi,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC2pi,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCCoth,   // kmNuMuBarCCcoh        
      kmcNuMuBarCCoth,   // kmNuMuBarCCoth
      kmcNuMuBarCCoth,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNuMuCCWS1piC
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCCQEMEC,   // kmNuMuBarCCQE         
      kmcNuMuBarCCQEMEC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC1pi,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC1pi,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC2pi,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC2pi,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC2pi,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCCoth,   // kmNuMuBarCCcoh        
      kmcNuMuBarCCoth,   // kmNuMuBarCCoth
      kmcNuMuBarCCoth,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNuMuCCWS1pi0
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCCQEMEC,   // kmNuMuBarCCQE         
      kmcNuMuBarCCQEMEC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC1pi,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC1pi,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC2pi,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC2pi,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC2pi,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCCoth,   // kmNuMuBarCCcoh        
      kmcNuMuBarCCoth,   // kmNuMuBarCCoth
      kmcNuMuBarCCoth,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNuMuCCWSoth
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCCQEMEC,   // kmNuMuBarCCQE         
      kmcNuMuBarCCQEMEC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC1pi,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC1pi,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC2pi,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC2pi,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC2pi,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCCoth,   // kmNuMuBarCCcoh        
      kmcNuMuBarCCoth,   // kmNuMuBarCCoth
      kmcNuMuBarCCoth,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNuECC0pi
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNCoth,          // kmNuMuNC1piC          
      kmcNC1pi0,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNCoth,          // kmNuMuBarNC1piC       
      kmcNC1pi0,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNCoth,          // kmNuENC1piC           
      kmcNC1pi0,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNCoth,          // kmNuEBarNC1piC        
      kmcNC1pi0,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNuECC1piC
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNCoth,          // kmNuMuNC1piC          
      kmcNC1pi0,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNCoth,          // kmNuMuBarNC1piC       
      kmcNC1pi0,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNCoth,          // kmNuENC1piC           
      kmcNC1pi0,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNCoth,          // kmNuEBarNC1piC        
      kmcNC1pi0,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNuECC1pi0
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNCoth,          // kmNuMuNC1piC          
      kmcNC1pi0,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNCoth,          // kmNuMuBarNC1piC       
      kmcNC1pi0,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNCoth,          // kmNuENC1piC           
      kmcNC1pi0,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNCoth,          // kmNuEBarNC1piC        
      kmcNC1pi0,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNuECCoth
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNCoth,          // kmNuMuNC1piC          
      kmcNC1pi0,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNCoth,          // kmNuMuBarNC1piC       
      kmcNC1pi0,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNCoth,          // kmNuENC1piC           
      kmcNC1pi0,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNCoth,          // kmNuEBarNC1piC        
      kmcNC1pi0,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNC0pi
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC1piC,      // kmNuMuNC1piC          
      kmcNC1pi0,      // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC1piC,      // kmNuMuBarNC1piC       
      kmcNC1pi0,      // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,       // kmNuMuBarNCcoh        
      kmcNCoth,       // kmNuMuBarNCoth        
      kmcNCoth,       // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
     //kmcNC,          // kmNuENCMEC           
      kmcNC1piC,     // kmNuENC1piC           
      kmcNC1pi0,     // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC1piC,      // kmNuEBarNC1piC        
      kmcNC1pi0,      // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNC1piC
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC1piC,       // kmNuMuNC1piC          
      kmcNC1pi0,       // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC1piC,      // kmNuMuBarNC1piC       
      kmcNC1pi0,      // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC1piC,          // kmNuENC1piC           
      kmcNC1pi0,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC1piC,      // kmNuEBarNC1piC        
      kmcNC1pi0,      // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNC1pi0
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC1piC,      // kmNuMuNC1piC          
      kmcNC1pi0,      // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC1piC,      // kmNuMuBarNC1piC       
      kmcNC1pi0,      // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNCoth,          // kmNuENC1piC           
      kmcNC1pi0,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC1piC,      // kmNuEBarNC1piC        
      kmcNC1pi0,      // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNCoth
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNCoth,          // kmNuMuNC1piC          
      kmcNC1pi0,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC1piC,      // kmNuMuBarNC1piC       
      kmcNC1pi0,      // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC1piC,      // kmNuENC1piC           
      kmcNC1pi0,      // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC1piC,      // kmNuEBarNC1piC        
      kmcNC1pi0,      // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNeutrinoElec
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCIMD           
      kmcNuMuCCoth,   // kmNuMuCCoth 
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksInvMuDecay
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCIMD           
      kmcNuMuCCoth,   // kmNuMuCCoth 
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNuECCWS
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNCoth,          // kmNuMuNC1piC          
      kmcNC1pi0,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNCoth,          // kmNuMuBarNC1piC       
      kmcNC1pi0,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNCoth,          // kmNuENC1piC           
      kmcNC1pi0,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNCoth,          // kmNuEBarNC1piC        
      kmcNC1pi0,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    //far detector
    //selection: NuMuCChigh
    {
      kmcNuMuCCQEMEC,    // kmNuMuCCQE            
      kmcNuMuCCQEMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCIMD           
      kmcNuMuCCoth,   // kmNuMuCCoth 
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuMuCCQEMEC, //kmNuEToNuMuCCQE
      kmcNuMuCCQEMEC, //kmNuEToNuMuCCMEC
      kmcNuMuCC1pi,   //kmNuEToNuMuCC1piC
      kmcNuMuCC1pi,   //kmNuEToNuMuCC1pi0
      kmcNuMuCC2pi,   //kmNuEToNuMuCC2piC
      kmcNuMuCC2pi,   //kmNuEToNuMuCC2pi0
      kmcNuMuCC2pi,   //kmNuEToNuMuCC1piC1pi0
      kmcNuMuCCoth,   //kmNuEToNuMuCCcoh
      kmcNuMuCCoth,   //kmNuEToNuMuCCIDM
      kmcNuMuCCoth,   //kmNuEToNuMuCCELScat
      kmcNuMuCCoth,   //kmNuEToNuMuCCoth
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCQE
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCMEC
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC1piC
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC1pi0
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC2piC
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC2pi0
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC1pi01piC
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCcoh
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCIDM
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCELScat
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCoth
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCMEC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1piC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC2piC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC2pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1piC1pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCcoh
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCELScat
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCoth
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC       //kmNuEBarToNuTauBarCCQE
    },
    //selection: NuMuCClow
    {
      kmcNuMuCCQEMEC,    // kmNuMuCCQE            
      kmcNuMuCCQEMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCIMD           
      kmcNuMuCCoth,   // kmNuMuCCoth 
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuMuCCQEMEC, //kmNuEToNuMuCCQE
      kmcNuMuCCQEMEC, //kmNuEToNuMuCCMEC
      kmcNuMuCC1pi,   //kmNuEToNuMuCC1piC
      kmcNuMuCC1pi,   //kmNuEToNuMuCC1pi0
      kmcNuMuCC2pi,   //kmNuEToNuMuCC2piC
      kmcNuMuCC2pi,   //kmNuEToNuMuCC2pi0
      kmcNuMuCC2pi,   //kmNuEToNuMuCC1piC1pi0
      kmcNuMuCCoth,   //kmNuEToNuMuCCcoh
      kmcNuMuCCoth,   //kmNuEToNuMuCCIDM
      kmcNuMuCCoth,   //kmNuEToNuMuCCELScat
      kmcNuMuCCoth,   //kmNuEToNuMuCCoth
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCQE
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCMEC
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC1piC
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC1pi0
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC2piC
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC2pi0
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC1pi01piC
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCcoh
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCIDM
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCELScat
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCoth
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCMEC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1piC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC2piC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC2pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1piC1pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCcoh
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCELScat
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCoth
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC       //kmNuEBarToNuTauBarCCQE
    },
    //selection: NuECChigh
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNCoth,          // kmNuMuNC1piC          
      kmcNC1pi0,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNCoth,          // kmNuMuBarNC1piC       
      kmcNC1pi0,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNCoth,          // kmNuENC1piC           
      kmcNC1pi0,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNCoth,          // kmNuEBarNC1piC        
      kmcNC1pi0,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuMuCC, //kmNuEToNuMuCCQE
      kmcNuMuCC, //kmNuEToNuMuCCMEC
      kmcNuMuCC,   //kmNuEToNuMuCC1piC
      kmcNuMuCC,   //kmNuEToNuMuCC1pi0
      kmcNuMuCC,   //kmNuEToNuMuCC2piC
      kmcNuMuCC,   //kmNuEToNuMuCC2pi0
      kmcNuMuCC,   //kmNuEToNuMuCC1piC1pi0
      kmcNuMuCC,   //kmNuEToNuMuCCcoh
      kmcNuMuCC,   //kmNuEToNuMuCCIDM
      kmcNuMuCC,   //kmNuEToNuMuCCELScat
      kmcNuMuCC,   //kmNuEToNuMuCCoth
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCQE
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCMEC
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC1piC
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC1pi0
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC2piC
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC2pi0
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC1pi01piC
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCcoh
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCIDM
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCELScat
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCoth
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCMEC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1piC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC2piC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC2pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1piC1pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCcoh
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCELScat
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCoth
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC       //kmNuEBarToNuTauBarCCQE
    },
    //selection: NuECClow
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNCoth,          // kmNuMuNC1piC          
      kmcNC1pi0,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNCoth,          // kmNuMuBarNC1piC       
      kmcNC1pi0,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNCoth,          // kmNuENC1piC           
      kmcNC1pi0,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNCoth,          // kmNuEBarNC1piC        
      kmcNC1pi0,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuMuCC, //kmNuEToNuMuCCQE
      kmcNuMuCC, //kmNuEToNuMuCCMEC
      kmcNuMuCC,   //kmNuEToNuMuCC1piC
      kmcNuMuCC,   //kmNuEToNuMuCC1pi0
      kmcNuMuCC,   //kmNuEToNuMuCC2piC
      kmcNuMuCC,   //kmNuEToNuMuCC2pi0
      kmcNuMuCC,   //kmNuEToNuMuCC1piC1pi0
      kmcNuMuCC,   //kmNuEToNuMuCCcoh
      kmcNuMuCC,   //kmNuEToNuMuCCIDM
      kmcNuMuCC,   //kmNuEToNuMuCCELScat
      kmcNuMuCC,   //kmNuEToNuMuCCoth
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCQE
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCMEC
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC1piC
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC1pi0
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC2piC
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC2pi0
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC1pi01piC
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCcoh
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCIDM
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCELScat
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCoth
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCMEC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1piC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC2piC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC2pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1piC1pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCcoh
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCELScat
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCoth
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC       //kmNuEBarToNuTauBarCCQE
    }
    },//end of FHC
  {  //RHC
    // selection: ksNuMuCC0pi1trk
    {
      kmcNuMuCC,      // kmNuMuCCQE
      kmcNuMuCC,      // kmNuMuCCMEC
      kmcNuMuCC,      // kmNuMuCC1piC
      kmcNuMuCC,      // kmNuMuCC1pi0
      kmcNuMuCC,      // kmNuMuCC2piC
      kmcNuMuCC,      // kmNuMuCC2pi0
      kmcNuMuCC,      // kmNuMuCCpiCpi0
      kmcNuMuCC,      // kmNuMuCCcoh
      kmcNuMuCC,      // kmNuMuCCIMD
      kmcNuMuCC,      // kmNuMuCCoth
      kmcNuMuCC,      // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL
    //kmcNC,          // kmNuMuNCMEC
      kmcNC,          // kmNuMuNC1piC
      kmcNC,          // kmNuMuNC1pi0
    //kmcNC,          // kmNuMuNC2piC
    //kmcNC,          // kmNuMuNC2pi0
    //kmcNC,          // kmNuMuNCpiCpi0
      kmcNC,          // kmNuMuNCcoh
      kmcNC,          // kmNuMuNCoth
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCCQE, // kmNuMuBarCCQE
      kmcNuMuBarCCMEC,// kmNuMuBarCCMEC
      kmcNuMuBarCC1pi,// kmNuMuBarCC1piC
      kmcNuMuBarCC1pi,// kmNuMuBarCC1pi0
      kmcNuMuBarCC2pi,// kmNuMuBarCC2piC
      kmcNuMuBarCC2pi,// kmNuMuBarCC2pi0
      kmcNuMuBarCC2pi,// kmNuMuBarCCpiCpi0
      kmcNuMuBarCCoth,// kmNuMuBarCCcoh
      kmcNuMuBarCCoth,// kmNuMuBarCCoth
      kmcNuMuBarCCoth,// kmNuMuBarCCELScat
    //kmcNC,          // kmNuMuBarNCEL
    //kmcNC,          // kmNuMuBarNCMEC
      kmcNC,          // kmNuMuBarNC1piC
      kmcNC,          // kmNuMuBarNC1pi0
    //kmcNC,          // kmNuMuBarNC2piC
    //kmcNC,          // kmNuMuBarNC2pi0
    //kmcNC,          // kmNuMuBarNCpiCpi0
      kmcNC,          // kmNuMuBarNCcoh
      kmcNC,          // kmNuMuBarNCoth
      kmcNC,          // kmNuMuBarNCELScat
      kmcNuENuEBarCC, // kmNuECCQE
      kmcNuENuEBarCC, // kmNuECCMEC
      kmcNuENuEBarCC, // kmNuECC1piC
      kmcNuENuEBarCC, // kmNuECC1pi0
      kmcNuENuEBarCC, // kmNuECC2piC
      kmcNuENuEBarCC, // kmNuECC2pi0
      kmcNuENuEBarCC, // kmNuECCpiCpi0
      kmcNuENuEBarCC, // kmNuECCcoh
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL
    //kmcNC,          // kmNuENCMEC
      kmcNC,          // kmNuENC1piC
      kmcNC,          // kmNuENC1pi0
    //kmcNC,          // kmNuENC2piC
    //kmcNC,          // kmNuENC2pi0
    //kmcNC,          // kmNuENCpiCpi0
      kmcNC,          // kmNuENCcoh
      kmcNC,          // kmNuENCoth
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE
      kmcNuENuEBarCC, // kmNuEBarCCMEC
      kmcNuENuEBarCC, // kmNuEBarCC1piC
      kmcNuENuEBarCC, // kmNuEBarCC1pi0
      kmcNuENuEBarCC, // kmNuEBarCC2piC
      kmcNuENuEBarCC, // kmNuEBarCC2pi0
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth
    //kmcNC,          // kmNuEBarNCEL
    //kmcNC,          // kmNuEBarNCMEC
      kmcNC,          // kmNuEBarNC1piC
      kmcNC,          // kmNuEBarNC1pi0
    //kmcNC,          // kmNuEBarNC2piC
    //kmcNC,          // kmNuEBarNC2pi0
    //kmcNC,          // kmNuEBarNCpiCpi0
      kmcNC,          // kmNuEBarNCcoh
      kmcNC,          // kmNuEBarNCoth
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined
    },
    // selection: ksNuMuCC0pi2trk
    {
      kmcNuMuCC,      // kmNuMuCCQE
      kmcNuMuCC,      // kmNuMuCCMEC
      kmcNuMuCC,      // kmNuMuCC1piC
      kmcNuMuCC,      // kmNuMuCC1pi0
      kmcNuMuCC,      // kmNuMuCC2piC
      kmcNuMuCC,      // kmNuMuCC2pi0
      kmcNuMuCC,      // kmNuMuCCpiCpi0
      kmcNuMuCC,      // kmNuMuCCcoh
      kmcNuMuCC,      // kmNuMuCCIMD
      kmcNuMuCC,      // kmNuMuCCoth
      kmcNuMuCC,      // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL
    //kmcNC,          // kmNuMuNCMEC
      kmcNC,          // kmNuMuNC1piC
      kmcNC,          // kmNuMuNC1pi0
    //kmcNC,          // kmNuMuNC2piC
    //kmcNC,          // kmNuMuNC2pi0
    //kmcNC,          // kmNuMuNCpiCpi0
      kmcNC,          // kmNuMuNCcoh
      kmcNC,          // kmNuMuNCoth
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCCQE, // kmNuMuBarCCQE
      kmcNuMuBarCCMEC,// kmNuMuBarCCMEC
      kmcNuMuBarCC1pi,// kmNuMuBarCC1piC
      kmcNuMuBarCC1pi,// kmNuMuBarCC1pi0
      kmcNuMuBarCC2pi,// kmNuMuBarCC2piC
      kmcNuMuBarCC2pi,// kmNuMuBarCC2pi0
      kmcNuMuBarCC2pi,// kmNuMuBarCCpiCpi0
      kmcNuMuBarCCoth,// kmNuMuBarCCcoh
      kmcNuMuBarCCoth,// kmNuMuBarCCoth
      kmcNuMuBarCCoth,// kmNuMuBarCCELScat
    //kmcNC,          // kmNuMuBarNCEL
    //kmcNC,          // kmNuMuBarNCMEC
      kmcNC,          // kmNuMuBarNC1piC
      kmcNC,          // kmNuMuBarNC1pi0
    //kmcNC,          // kmNuMuBarNC2piC
    //kmcNC,          // kmNuMuBarNC2pi0
    //kmcNC,          // kmNuMuBarNCpiCpi0
      kmcNC,          // kmNuMuBarNCcoh
      kmcNC,          // kmNuMuBarNCoth
      kmcNC,          // kmNuMuBarNCELScat
      kmcNuENuEBarCC, // kmNuECCQE
      kmcNuENuEBarCC, // kmNuECCMEC
      kmcNuENuEBarCC, // kmNuECC1piC
      kmcNuENuEBarCC, // kmNuECC1pi0
      kmcNuENuEBarCC, // kmNuECC2piC
      kmcNuENuEBarCC, // kmNuECC2pi0
      kmcNuENuEBarCC, // kmNuECCpiCpi0
      kmcNuENuEBarCC, // kmNuECCcoh
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL
    //kmcNC,          // kmNuENCMEC
      kmcNC,          // kmNuENC1piC
      kmcNC,          // kmNuENC1pi0
    //kmcNC,          // kmNuENC2piC
    //kmcNC,          // kmNuENC2pi0
    //kmcNC,          // kmNuENCpiCpi0
      kmcNC,          // kmNuENCcoh
      kmcNC,          // kmNuENCoth
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE
      kmcNuENuEBarCC, // kmNuEBarCCMEC
      kmcNuENuEBarCC, // kmNuEBarCC1piC
      kmcNuENuEBarCC, // kmNuEBarCC1pi0
      kmcNuENuEBarCC, // kmNuEBarCC2piC
      kmcNuENuEBarCC, // kmNuEBarCC2pi0
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth
    //kmcNC,          // kmNuEBarNCEL
    //kmcNC,          // kmNuEBarNCMEC
      kmcNC,          // kmNuEBarNC1piC
      kmcNC,          // kmNuEBarNC1pi0
    //kmcNC,          // kmNuEBarNC2piC
    //kmcNC,          // kmNuEBarNC2pi0
    //kmcNC,          // kmNuEBarNCpiCpi0
      kmcNC,          // kmNuEBarNCcoh
      kmcNC,          // kmNuEBarNCoth
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNuMuCC0piNtrk
    {
      kmcNuMuCC,      // kmNuMuCCQE
      kmcNuMuCC,      // kmNuMuCCMEC
      kmcNuMuCC,      // kmNuMuCC1piC
      kmcNuMuCC,      // kmNuMuCC1pi0
      kmcNuMuCC,      // kmNuMuCC2piC
      kmcNuMuCC,      // kmNuMuCC2pi0
      kmcNuMuCC,      // kmNuMuCCpiCpi0
      kmcNuMuCC,      // kmNuMuCCcoh
      kmcNuMuCC,      // kmNuMuCCIMD
      kmcNuMuCC,      // kmNuMuCCoth
      kmcNuMuCC,      // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL
    //kmcNC,          // kmNuMuNCMEC
      kmcNC,          // kmNuMuNC1piC
      kmcNC,          // kmNuMuNC1pi0
    //kmcNC,          // kmNuMuNC2piC
    //kmcNC,          // kmNuMuNC2pi0
    //kmcNC,          // kmNuMuNCpiCpi0
      kmcNC,          // kmNuMuNCcoh
      kmcNC,          // kmNuMuNCoth
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCCQE, // kmNuMuBarCCQE
      kmcNuMuBarCCMEC,// kmNuMuBarCCMEC
      kmcNuMuBarCC1pi,// kmNuMuBarCC1piC
      kmcNuMuBarCC1pi,// kmNuMuBarCC1pi0
      kmcNuMuBarCC2pi,// kmNuMuBarCC2piC
      kmcNuMuBarCC2pi,// kmNuMuBarCC2pi0
      kmcNuMuBarCC2pi,// kmNuMuBarCCpiCpi0
      kmcNuMuBarCCoth,// kmNuMuBarCCcoh
      kmcNuMuBarCCoth,// kmNuMuBarCCoth
      kmcNuMuBarCCoth,// kmNuMuBarCCELScat
    //kmcNC,          // kmNuMuBarNCEL
    //kmcNC,          // kmNuMuBarNCMEC
      kmcNC,          // kmNuMuBarNC1piC
      kmcNC,          // kmNuMuBarNC1pi0
    //kmcNC,          // kmNuMuBarNC2piC
    //kmcNC,          // kmNuMuBarNC2pi0
    //kmcNC,          // kmNuMuBarNCpiCpi0
      kmcNC,          // kmNuMuBarNCcoh
      kmcNC,          // kmNuMuBarNCoth
      kmcNC,          // kmNuMuBarNCELScat
      kmcNuENuEBarCC, // kmNuECCQE
      kmcNuENuEBarCC, // kmNuECCMEC
      kmcNuENuEBarCC, // kmNuECC1piC
      kmcNuENuEBarCC, // kmNuECC1pi0
      kmcNuENuEBarCC, // kmNuECC2piC
      kmcNuENuEBarCC, // kmNuECC2pi0
      kmcNuENuEBarCC, // kmNuECCpiCpi0
      kmcNuENuEBarCC, // kmNuECCcoh
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL
    //kmcNC,          // kmNuENCMEC
      kmcNC,          // kmNuENC1piC
      kmcNC,          // kmNuENC1pi0
    //kmcNC,          // kmNuENC2piC
    //kmcNC,          // kmNuENC2pi0
    //kmcNC,          // kmNuENCpiCpi0
      kmcNC,          // kmNuENCcoh
      kmcNC,          // kmNuENCoth
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE
      kmcNuENuEBarCC, // kmNuEBarCCMEC
      kmcNuENuEBarCC, // kmNuEBarCC1piC
      kmcNuENuEBarCC, // kmNuEBarCC1pi0
      kmcNuENuEBarCC, // kmNuEBarCC2piC
      kmcNuENuEBarCC, // kmNuEBarCC2pi0
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth
    //kmcNC,          // kmNuEBarNCEL
    //kmcNC,          // kmNuEBarNCMEC
      kmcNC,          // kmNuEBarNC1piC
      kmcNC,          // kmNuEBarNC1pi0
    //kmcNC,          // kmNuEBarNC2piC
    //kmcNC,          // kmNuEBarNC2pi0
    //kmcNC,          // kmNuEBarNCpiCpi0
      kmcNC,          // kmNuEBarNCcoh
      kmcNC,          // kmNuEBarNCoth
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNuMuCC3trkDelta
    {
      kmcNuMuCC,      // kmNuMuCCQE
      kmcNuMuCC,      // kmNuMuCCMEC
      kmcNuMuCC,      // kmNuMuCC1piC
      kmcNuMuCC,      // kmNuMuCC1pi0
      kmcNuMuCC,      // kmNuMuCC2piC
      kmcNuMuCC,      // kmNuMuCC2pi0
      kmcNuMuCC,      // kmNuMuCCpiCpi0
      kmcNuMuCC,      // kmNuMuCCcoh
      kmcNuMuCC,      // kmNuMuCCIMD
      kmcNuMuCC,      // kmNuMuCCoth
      kmcNuMuCC,      // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL
    //kmcNC,          // kmNuMuNCMEC
      kmcNC,          // kmNuMuNC1piC
      kmcNC,          // kmNuMuNC1pi0
    //kmcNC,          // kmNuMuNC2piC
    //kmcNC,          // kmNuMuNC2pi0
    //kmcNC,          // kmNuMuNCpiCpi0
      kmcNC,          // kmNuMuNCcoh
      kmcNC,          // kmNuMuNCoth
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCCQE, // kmNuMuBarCCQE
      kmcNuMuBarCCMEC,// kmNuMuBarCCMEC
      kmcNuMuBarCC1pi,// kmNuMuBarCC1piC
      kmcNuMuBarCC1pi,// kmNuMuBarCC1pi0
      kmcNuMuBarCC2pi,// kmNuMuBarCC2piC
      kmcNuMuBarCC2pi,// kmNuMuBarCC2pi0
      kmcNuMuBarCC2pi,// kmNuMuBarCCpiCpi0
      kmcNuMuBarCCoth,// kmNuMuBarCCcoh
      kmcNuMuBarCCoth,// kmNuMuBarCCoth
      kmcNuMuBarCCoth,// kmNuMuBarCCELScat
    //kmcNC,          // kmNuMuBarNCEL
    //kmcNC,          // kmNuMuBarNCMEC
      kmcNC,          // kmNuMuBarNC1piC
      kmcNC,          // kmNuMuBarNC1pi0
    //kmcNC,          // kmNuMuBarNC2piC
    //kmcNC,          // kmNuMuBarNC2pi0
    //kmcNC,          // kmNuMuBarNCpiCpi0
      kmcNC,          // kmNuMuBarNCcoh
      kmcNC,          // kmNuMuBarNCoth
      kmcNC,          // kmNuMuBarNCELScat
      kmcNuENuEBarCC, // kmNuECCQE
      kmcNuENuEBarCC, // kmNuECCMEC
      kmcNuENuEBarCC, // kmNuECC1piC
      kmcNuENuEBarCC, // kmNuECC1pi0
      kmcNuENuEBarCC, // kmNuECC2piC
      kmcNuENuEBarCC, // kmNuECC2pi0
      kmcNuENuEBarCC, // kmNuECCpiCpi0
      kmcNuENuEBarCC, // kmNuECCcoh
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL
    //kmcNC,          // kmNuENCMEC
      kmcNC,          // kmNuENC1piC
      kmcNC,          // kmNuENC1pi0
    //kmcNC,          // kmNuENC2piC
    //kmcNC,          // kmNuENC2pi0
    //kmcNC,          // kmNuENCpiCpi0
      kmcNC,          // kmNuENCcoh
      kmcNC,          // kmNuENCoth
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE
      kmcNuENuEBarCC, // kmNuEBarCCMEC
      kmcNuENuEBarCC, // kmNuEBarCC1piC
      kmcNuENuEBarCC, // kmNuEBarCC1pi0
      kmcNuENuEBarCC, // kmNuEBarCC2piC
      kmcNuENuEBarCC, // kmNuEBarCC2pi0
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth
    //kmcNC,          // kmNuEBarNCEL
    //kmcNC,          // kmNuEBarNCMEC
      kmcNC,          // kmNuEBarNC1piC
      kmcNC,          // kmNuEBarNC1pi0
    //kmcNC,          // kmNuEBarNC2piC
    //kmcNC,          // kmNuEBarNC2pi0
    //kmcNC,          // kmNuEBarNCpiCpi0
      kmcNC,          // kmNuEBarNCcoh
      kmcNC,          // kmNuEBarNCoth
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNuMuCC1piC
    {
      kmcNuMuCC,      // kmNuMuCCQE
      kmcNuMuCC,      // kmNuMuCCMEC
      kmcNuMuCC,      // kmNuMuCC1piC
      kmcNuMuCC,      // kmNuMuCC1pi0
      kmcNuMuCC,      // kmNuMuCC2piC
      kmcNuMuCC,      // kmNuMuCC2pi0
      kmcNuMuCC,      // kmNuMuCCpiCpi0
      kmcNuMuCC,      // kmNuMuCCcoh
      kmcNuMuCC,      // kmNuMuCCIMD
      kmcNuMuCC,      // kmNuMuCCoth
      kmcNuMuCC,      // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL
    //kmcNC,          // kmNuMuNCMEC
      kmcNC,          // kmNuMuNC1piC
      kmcNC,          // kmNuMuNC1pi0
    //kmcNC,          // kmNuMuNC2piC
    //kmcNC,          // kmNuMuNC2pi0
    //kmcNC,          // kmNuMuNCpiCpi0
      kmcNC,          // kmNuMuNCcoh
      kmcNC,          // kmNuMuNCoth
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCCQEMEC, // kmNuMuBarCCQE
      kmcNuMuBarCCQEMEC,// kmNuMuBarCCMEC
      kmcNuMuBarCC1pi,// kmNuMuBarCC1piC
      kmcNuMuBarCC1pi,// kmNuMuBarCC1pi0
      kmcNuMuBarCC2pi,// kmNuMuBarCC2piC
      kmcNuMuBarCC2pi,// kmNuMuBarCC2pi0
      kmcNuMuBarCC2pi,// kmNuMuBarCCpiCpi0
      kmcNuMuBarCCoth,// kmNuMuBarCCcoh
      kmcNuMuBarCCoth,// kmNuMuBarCCoth
      kmcNuMuBarCCoth,// kmNuMuBarCCELScat
    //kmcNC,          // kmNuMuBarNCEL
    //kmcNC,          // kmNuMuBarNCMEC
      kmcNC,          // kmNuMuBarNC1piC
      kmcNC,          // kmNuMuBarNC1pi0
    //kmcNC,          // kmNuMuBarNC2piC
    //kmcNC,          // kmNuMuBarNC2pi0
    //kmcNC,          // kmNuMuBarNCpiCpi0
      kmcNC,          // kmNuMuBarNCcoh
      kmcNC,          // kmNuMuBarNCoth
      kmcNC,          // kmNuMuBarNCELScat
      kmcNuENuEBarCC, // kmNuECCQE
      kmcNuENuEBarCC, // kmNuECCMEC
      kmcNuENuEBarCC, // kmNuECC1piC
      kmcNuENuEBarCC, // kmNuECC1pi0
      kmcNuENuEBarCC, // kmNuECC2piC
      kmcNuENuEBarCC, // kmNuECC2pi0
      kmcNuENuEBarCC, // kmNuECCpiCpi0
      kmcNuENuEBarCC, // kmNuECCcoh
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL
    //kmcNC,          // kmNuENCMEC
      kmcNC,          // kmNuENC1piC
      kmcNC,          // kmNuENC1pi0
    //kmcNC,          // kmNuENC2piC
    //kmcNC,          // kmNuENC2pi0
    //kmcNC,          // kmNuENCpiCpi0
      kmcNC,          // kmNuENCcoh
      kmcNC,          // kmNuENCoth
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE
      kmcNuENuEBarCC, // kmNuEBarCCMEC
      kmcNuENuEBarCC, // kmNuEBarCC1piC
      kmcNuENuEBarCC, // kmNuEBarCC1pi0
      kmcNuENuEBarCC, // kmNuEBarCC2piC
      kmcNuENuEBarCC, // kmNuEBarCC2pi0
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth
    //kmcNC,          // kmNuEBarNCEL
    //kmcNC,          // kmNuEBarNCMEC
      kmcNC,          // kmNuEBarNC1piC
      kmcNC,          // kmNuEBarNC1pi0
    //kmcNC,          // kmNuEBarNC2piC
    //kmcNC,          // kmNuEBarNC2pi0
    //kmcNC,          // kmNuEBarNCpiCpi0
      kmcNC,          // kmNuEBarNCcoh
      kmcNC,          // kmNuEBarNCoth
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNuMuCC1pi0
    {
      kmcNuMuCC,      // kmNuMuCCQE
      kmcNuMuCC,      // kmNuMuCCMEC
      kmcNuMuCC,      // kmNuMuCC1piC
      kmcNuMuCC,      // kmNuMuCC1pi0
      kmcNuMuCC,      // kmNuMuCC2piC
      kmcNuMuCC,      // kmNuMuCC2pi0
      kmcNuMuCC,      // kmNuMuCCpiCpi0
      kmcNuMuCC,      // kmNuMuCCcoh
      kmcNuMuCC,      // kmNuMuCCIMD
      kmcNuMuCC,      // kmNuMuCCoth
      kmcNuMuCC,      // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL
    //kmcNC,          // kmNuMuNCMEC
      kmcNC,          // kmNuMuNC1piC
      kmcNC,          // kmNuMuNC1pi0
    //kmcNC,          // kmNuMuNC2piC
    //kmcNC,          // kmNuMuNC2pi0
    //kmcNC,          // kmNuMuNCpiCpi0
      kmcNC,          // kmNuMuNCcoh
      kmcNC,          // kmNuMuNCoth
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCCQEMEC, // kmNuMuBarCCQE
      kmcNuMuBarCCQEMEC,// kmNuMuBarCCMEC
      kmcNuMuBarCC1pi,// kmNuMuBarCC1piC
      kmcNuMuBarCC1pi,// kmNuMuBarCC1pi0
      kmcNuMuBarCC2pi,// kmNuMuBarCC2piC
      kmcNuMuBarCC2pi,// kmNuMuBarCC2pi0
      kmcNuMuBarCC2pi,// kmNuMuBarCCpiCpi0
      kmcNuMuBarCCoth,// kmNuMuBarCCcoh
      kmcNuMuBarCCoth,// kmNuMuBarCCoth
      kmcNuMuBarCCoth,// kmNuMuBarCCELScat
    //kmcNC,          // kmNuMuBarNCEL
    //kmcNC,          // kmNuMuBarNCMEC
      kmcNC,          // kmNuMuBarNC1piC
      kmcNC,          // kmNuMuBarNC1pi0
    //kmcNC,          // kmNuMuBarNC2piC
    //kmcNC,          // kmNuMuBarNC2pi0
    //kmcNC,          // kmNuMuBarNCpiCpi0
      kmcNC,          // kmNuMuBarNCcoh
      kmcNC,          // kmNuMuBarNCoth
      kmcNC,          // kmNuMuBarNCELScat
      kmcNuENuEBarCC, // kmNuECCQE
      kmcNuENuEBarCC, // kmNuECCMEC
      kmcNuENuEBarCC, // kmNuECC1piC
      kmcNuENuEBarCC, // kmNuECC1pi0
      kmcNuENuEBarCC, // kmNuECC2piC
      kmcNuENuEBarCC, // kmNuECC2pi0
      kmcNuENuEBarCC, // kmNuECCpiCpi0
      kmcNuENuEBarCC, // kmNuECCcoh
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL
    //kmcNC,          // kmNuENCMEC
      kmcNC,          // kmNuENC1piC
      kmcNC,          // kmNuENC1pi0
    //kmcNC,          // kmNuENC2piC
    //kmcNC,          // kmNuENC2pi0
    //kmcNC,          // kmNuENCpiCpi0
      kmcNC,          // kmNuENCcoh
      kmcNC,          // kmNuENCoth
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE
      kmcNuENuEBarCC, // kmNuEBarCCMEC
      kmcNuENuEBarCC, // kmNuEBarCC1piC
      kmcNuENuEBarCC, // kmNuEBarCC1pi0
      kmcNuENuEBarCC, // kmNuEBarCC2piC
      kmcNuENuEBarCC, // kmNuEBarCC2pi0
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth
    //kmcNC,          // kmNuEBarNCEL
    //kmcNC,          // kmNuEBarNCMEC
      kmcNC,          // kmNuEBarNC1piC
      kmcNC,          // kmNuEBarNC1pi0
    //kmcNC,          // kmNuEBarNC2piC
    //kmcNC,          // kmNuEBarNC2pi0
    //kmcNC,          // kmNuEBarNCpiCpi0
      kmcNC,          // kmNuEBarNCcoh
      kmcNC,          // kmNuEBarNCoth
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNuMuCC1piC1pi0
    {
      kmcNuMuCC,      // kmNuMuCCQE
      kmcNuMuCC,      // kmNuMuCCMEC
      kmcNuMuCC,      // kmNuMuCC1piC
      kmcNuMuCC,      // kmNuMuCC1pi0
      kmcNuMuCC,      // kmNuMuCC2piC
      kmcNuMuCC,      // kmNuMuCC2pi0
      kmcNuMuCC,      // kmNuMuCCpiCpi0
      kmcNuMuCC,      // kmNuMuCCcoh
      kmcNuMuCC,      // kmNuMuCCIMD
      kmcNuMuCC,      // kmNuMuCCoth
      kmcNuMuCC,      // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL
    //kmcNC,          // kmNuMuNCMEC
      kmcNC,          // kmNuMuNC1piC
      kmcNC,          // kmNuMuNC1pi0
    //kmcNC,          // kmNuMuNC2piC
    //kmcNC,          // kmNuMuNC2pi0
    //kmcNC,          // kmNuMuNCpiCpi0
      kmcNC,          // kmNuMuNCcoh
      kmcNC,          // kmNuMuNCoth
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCCQEMEC, // kmNuMuBarCCQE
      kmcNuMuBarCCQEMEC,// kmNuMuBarCCMEC
      kmcNuMuBarCC1pi,// kmNuMuBarCC1piC
      kmcNuMuBarCC1pi,// kmNuMuBarCC1pi0
      kmcNuMuBarCC2pi,// kmNuMuBarCC2piC
      kmcNuMuBarCC2pi,// kmNuMuBarCC2pi0
      kmcNuMuBarCC2pi,// kmNuMuBarCCpiCpi0
      kmcNuMuBarCCoth,// kmNuMuBarCCcoh
      kmcNuMuBarCCoth,// kmNuMuBarCCoth
      kmcNuMuBarCCoth,// kmNuMuBarCCELScat
    //kmcNC,          // kmNuMuBarNCEL
    //kmcNC,          // kmNuMuBarNCMEC
      kmcNC,          // kmNuMuBarNC1piC
      kmcNC,          // kmNuMuBarNC1pi0
    //kmcNC,          // kmNuMuBarNC2piC
    //kmcNC,          // kmNuMuBarNC2pi0
    //kmcNC,          // kmNuMuBarNCpiCpi0
      kmcNC,          // kmNuMuBarNCcoh
      kmcNC,          // kmNuMuBarNCoth
      kmcNC,          // kmNuMuBarNCELScat
      kmcNuENuEBarCC, // kmNuECCQE
      kmcNuENuEBarCC, // kmNuECCMEC
      kmcNuENuEBarCC, // kmNuECC1piC
      kmcNuENuEBarCC, // kmNuECC1pi0
      kmcNuENuEBarCC, // kmNuECC2piC
      kmcNuENuEBarCC, // kmNuECC2pi0
      kmcNuENuEBarCC, // kmNuECCpiCpi0
      kmcNuENuEBarCC, // kmNuECCcoh
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL
    //kmcNC,          // kmNuENCMEC
      kmcNC,          // kmNuENC1piC
      kmcNC,          // kmNuENC1pi0
    //kmcNC,          // kmNuENC2piC
    //kmcNC,          // kmNuENC2pi0
    //kmcNC,          // kmNuENCpiCpi0
      kmcNC,          // kmNuENCcoh
      kmcNC,          // kmNuENCoth
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE
      kmcNuENuEBarCC, // kmNuEBarCCMEC
      kmcNuENuEBarCC, // kmNuEBarCC1piC
      kmcNuENuEBarCC, // kmNuEBarCC1pi0
      kmcNuENuEBarCC, // kmNuEBarCC2piC
      kmcNuENuEBarCC, // kmNuEBarCC2pi0
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth
    //kmcNC,          // kmNuEBarNCEL
    //kmcNC,          // kmNuEBarNCMEC
      kmcNC,          // kmNuEBarNC1piC
      kmcNC,          // kmNuEBarNC1pi0
    //kmcNC,          // kmNuEBarNC2piC
    //kmcNC,          // kmNuEBarNC2pi0
    //kmcNC,          // kmNuEBarNCpiCpi0
      kmcNC,          // kmNuEBarNCcoh
      kmcNC,          // kmNuEBarNCoth
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNuMuCCoth
    {
      kmcNuMuCC,      // kmNuMuCCQE
      kmcNuMuCC,      // kmNuMuCCMEC
      kmcNuMuCC,      // kmNuMuCC1piC
      kmcNuMuCC,      // kmNuMuCC1pi0
      kmcNuMuCC,      // kmNuMuCC2piC
      kmcNuMuCC,      // kmNuMuCC2pi0
      kmcNuMuCC,      // kmNuMuCCpiCpi0
      kmcNuMuCC,      // kmNuMuCCcoh
      kmcNuMuCC,      // kmNuMuCCIMD
      kmcNuMuCC,      // kmNuMuCCoth
      kmcNuMuCC,      // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL
    //kmcNC,          // kmNuMuNCMEC
      kmcNC,          // kmNuMuNC1piC
      kmcNC,          // kmNuMuNC1pi0
    //kmcNC,          // kmNuMuNC2piC
    //kmcNC,          // kmNuMuNC2pi0
    //kmcNC,          // kmNuMuNCpiCpi0
      kmcNC,          // kmNuMuNCcoh
      kmcNC,          // kmNuMuNCoth
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCCQEMEC, // kmNuMuBarCCQE
      kmcNuMuBarCCQEMEC,// kmNuMuBarCCMEC
      kmcNuMuBarCC1pi,// kmNuMuBarCC1piC
      kmcNuMuBarCC1pi,// kmNuMuBarCC1pi0
      kmcNuMuBarCC2pi,// kmNuMuBarCC2piC
      kmcNuMuBarCC2pi,// kmNuMuBarCC2pi0
      kmcNuMuBarCC2pi,// kmNuMuBarCCpiCpi0
      kmcNuMuBarCCoth,// kmNuMuBarCCcoh
      kmcNuMuBarCCoth,// kmNuMuBarCCoth
      kmcNuMuBarCCoth,// kmNuMuBarCCELScat
    //kmcNC,          // kmNuMuBarNCEL
    //kmcNC,          // kmNuMuBarNCMEC
      kmcNC,          // kmNuMuBarNC1piC
      kmcNC,          // kmNuMuBarNC1pi0
    //kmcNC,          // kmNuMuBarNC2piC
    //kmcNC,          // kmNuMuBarNC2pi0
    //kmcNC,          // kmNuMuBarNCpiCpi0
      kmcNC,          // kmNuMuBarNCcoh
      kmcNC,          // kmNuMuBarNCoth
      kmcNC,          // kmNuMuBarNCELScat
      kmcNuENuEBarCC, // kmNuECCQE
      kmcNuENuEBarCC, // kmNuECCMEC
      kmcNuENuEBarCC, // kmNuECC1piC
      kmcNuENuEBarCC, // kmNuECC1pi0
      kmcNuENuEBarCC, // kmNuECC2piC
      kmcNuENuEBarCC, // kmNuECC2pi0
      kmcNuENuEBarCC, // kmNuECCpiCpi0
      kmcNuENuEBarCC, // kmNuECCcoh
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL
    //kmcNC,          // kmNuENCMEC
      kmcNC,          // kmNuENC1piC
      kmcNC,          // kmNuENC1pi0
    //kmcNC,          // kmNuENC2piC
    //kmcNC,          // kmNuENC2pi0
    //kmcNC,          // kmNuENCpiCpi0
      kmcNC,          // kmNuENCcoh
      kmcNC,          // kmNuENCoth
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE
      kmcNuENuEBarCC, // kmNuEBarCCMEC
      kmcNuENuEBarCC, // kmNuEBarCC1piC
      kmcNuENuEBarCC, // kmNuEBarCC1pi0
      kmcNuENuEBarCC, // kmNuEBarCC2piC
      kmcNuENuEBarCC, // kmNuEBarCC2pi0
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth
    //kmcNC,          // kmNuEBarNCEL
    //kmcNC,          // kmNuEBarNCMEC
      kmcNC,          // kmNuEBarNC1piC
      kmcNC,          // kmNuEBarNC1pi0
    //kmcNC,          // kmNuEBarNC2piC
    //kmcNC,          // kmNuEBarNC2pi0
    //kmcNC,          // kmNuEBarNCpiCpi0
      kmcNC,          // kmNuEBarNCcoh
      kmcNC,          // kmNuEBarNCoth
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNuMuCCWS0pi
    {
      kmcNuMuCCQEMEC, // kmNuMuCCQE
      kmcNuMuCCQEMEC, // kmNuMuCCMEC
      kmcNuMuCC1pi,   // kmNuMuCC1piC
      kmcNuMuCC1pi,   // kmNuMuCC1pi0
      kmcNuMuCC2pi,   // kmNuMuCC2piC
      kmcNuMuCC2pi,   // kmNuMuCC2pi0
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0
      kmcNuMuCCoth,   // kmNuMuCCcoh
      kmcNuMuCCoth,   // kmNuMuCCIMD
      kmcNuMuCCoth,   // kmNuMuCCoth
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL
    //kmcNC,          // kmNuMuNCMEC
      kmcNC,          // kmNuMuNC1piC
      kmcNC,          // kmNuMuNC1pi0
    //kmcNC,          // kmNuMuNC2piC
    //kmcNC,          // kmNuMuNC2pi0
    //kmcNC,          // kmNuMuNCpiCpi0
      kmcNC,          // kmNuMuNCcoh
      kmcNC,          // kmNuMuNCoth
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE
      kmcNuMuBarCC,   // kmNuMuBarCCMEC
      kmcNuMuBarCC,   // kmNuMuBarCC1piC
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0
      kmcNuMuBarCC,   // kmNuMuBarCC2piC
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0
      kmcNuMuBarCC,   // kmNuMuBarCCcoh
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat
    //kmcNC,          // kmNuMuBarNCEL
    //kmcNC,          // kmNuMuBarNCMEC
      kmcNC,          // kmNuMuBarNC1piC
      kmcNC,          // kmNuMuBarNC1pi0
    //kmcNC,          // kmNuMuBarNC2piC
    //kmcNC,          // kmNuMuBarNC2pi0
    //kmcNC,          // kmNuMuBarNCpiCpi0
      kmcNC,          // kmNuMuBarNCcoh
      kmcNC,          // kmNuMuBarNCoth
      kmcNC,          // kmNuMuBarNCELScat
      kmcNuENuEBarCC, // kmNuECCQE
      kmcNuENuEBarCC, // kmNuECCMEC
      kmcNuENuEBarCC, // kmNuECC1piC
      kmcNuENuEBarCC, // kmNuECC1pi0
      kmcNuENuEBarCC, // kmNuECC2piC
      kmcNuENuEBarCC, // kmNuECC2pi0
      kmcNuENuEBarCC, // kmNuECCpiCpi0
      kmcNuENuEBarCC, // kmNuECCcoh
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL
    //kmcNC,          // kmNuENCMEC
      kmcNC,          // kmNuENC1piC
      kmcNC,          // kmNuENC1pi0
    //kmcNC,          // kmNuENC2piC
    //kmcNC,          // kmNuENC2pi0
    //kmcNC,          // kmNuENCpiCpi0
      kmcNC,          // kmNuENCcoh
      kmcNC,          // kmNuENCoth
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE
      kmcNuENuEBarCC, // kmNuEBarCCMEC
      kmcNuENuEBarCC, // kmNuEBarCC1piC
      kmcNuENuEBarCC, // kmNuEBarCC1pi0
      kmcNuENuEBarCC, // kmNuEBarCC2piC
      kmcNuENuEBarCC, // kmNuEBarCC2pi0
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth
    //kmcNC,          // kmNuEBarNCEL
    //kmcNC,          // kmNuEBarNCMEC
      kmcNC,          // kmNuEBarNC1piC
      kmcNC,          // kmNuEBarNC1pi0
    //kmcNC,          // kmNuEBarNC2piC
    //kmcNC,          // kmNuEBarNC2pi0
    //kmcNC,          // kmNuEBarNCpiCpi0
      kmcNC,          // kmNuEBarNCcoh
      kmcNC,           // kmNuEBarNCoth
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNuMuCCWS1piC
    {
      kmcNuMuCCQEMEC, // kmNuMuCCQE
      kmcNuMuCCQEMEC, // kmNuMuCCMEC
      kmcNuMuCC1pi,   // kmNuMuCC1piC
      kmcNuMuCC1pi,   // kmNuMuCC1pi0
      kmcNuMuCC2pi,   // kmNuMuCC2piC
      kmcNuMuCC2pi,   // kmNuMuCC2pi0
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0
      kmcNuMuCCoth,   // kmNuMuCCcoh
      kmcNuMuCCoth,   // kmNuMuCCIMD
      kmcNuMuCCoth,   // kmNuMuCCoth
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL
    //kmcNC,          // kmNuMuNCMEC
      kmcNC,          // kmNuMuNC1piC
      kmcNC,          // kmNuMuNC1pi0
    //kmcNC,          // kmNuMuNC2piC
    //kmcNC,          // kmNuMuNC2pi0
    //kmcNC,          // kmNuMuNCpiCpi0
      kmcNC,          // kmNuMuNCcoh
      kmcNC,          // kmNuMuNCoth
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE
      kmcNuMuBarCC,   // kmNuMuBarCCMEC
      kmcNuMuBarCC,   // kmNuMuBarCC1piC
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0
      kmcNuMuBarCC,   // kmNuMuBarCC2piC
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0
      kmcNuMuBarCC,   // kmNuMuBarCCcoh
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat
    //kmcNC,          // kmNuMuBarNCEL
    //kmcNC,          // kmNuMuBarNCMEC
      kmcNC,          // kmNuMuBarNC1piC
      kmcNC,          // kmNuMuBarNC1pi0
    //kmcNC,          // kmNuMuBarNC2piC
    //kmcNC,          // kmNuMuBarNC2pi0
    //kmcNC,          // kmNuMuBarNCpiCpi0
      kmcNC,          // kmNuMuBarNCcoh
      kmcNC,          // kmNuMuBarNCoth
      kmcNC,          // kmNuMuBarNCELScat
      kmcNuENuEBarCC, // kmNuECCQE
      kmcNuENuEBarCC, // kmNuECCMEC
      kmcNuENuEBarCC, // kmNuECC1piC
      kmcNuENuEBarCC, // kmNuECC1pi0
      kmcNuENuEBarCC, // kmNuECC2piC
      kmcNuENuEBarCC, // kmNuECC2pi0
      kmcNuENuEBarCC, // kmNuECCpiCpi0
      kmcNuENuEBarCC, // kmNuECCcoh
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL
    //kmcNC,          // kmNuENCMEC
      kmcNC,          // kmNuENC1piC
      kmcNC,          // kmNuENC1pi0
    //kmcNC,          // kmNuENC2piC
    //kmcNC,          // kmNuENC2pi0
    //kmcNC,          // kmNuENCpiCpi0
      kmcNC,          // kmNuENCcoh
      kmcNC,          // kmNuENCoth
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE
      kmcNuENuEBarCC, // kmNuEBarCCMEC
      kmcNuENuEBarCC, // kmNuEBarCC1piC
      kmcNuENuEBarCC, // kmNuEBarCC1pi0
      kmcNuENuEBarCC, // kmNuEBarCC2piC
      kmcNuENuEBarCC, // kmNuEBarCC2pi0
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth
    //kmcNC,          // kmNuEBarNCEL
    //kmcNC,          // kmNuEBarNCMEC
      kmcNC,          // kmNuEBarNC1piC
      kmcNC,          // kmNuEBarNC1pi0
    //kmcNC,          // kmNuEBarNC2piC
    //kmcNC,          // kmNuEBarNC2pi0
    //kmcNC,          // kmNuEBarNCpiCpi0
      kmcNC,          // kmNuEBarNCcoh
      kmcNC,           // kmNuEBarNCoth
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNuMuCCWS1pi0
    {
      kmcNuMuCCQEMEC, // kmNuMuCCQE
      kmcNuMuCCQEMEC, // kmNuMuCCMEC
      kmcNuMuCC1pi,   // kmNuMuCC1piC
      kmcNuMuCC1pi,   // kmNuMuCC1pi0
      kmcNuMuCC2pi,   // kmNuMuCC2piC
      kmcNuMuCC2pi,   // kmNuMuCC2pi0
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0
      kmcNuMuCCoth,   // kmNuMuCCcoh
      kmcNuMuCCoth,   // kmNuMuCCIMD
      kmcNuMuCCoth,   // kmNuMuCCoth
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL
    //kmcNC,          // kmNuMuNCMEC
      kmcNC,          // kmNuMuNC1piC
      kmcNC,          // kmNuMuNC1pi0
    //kmcNC,          // kmNuMuNC2piC
    //kmcNC,          // kmNuMuNC2pi0
    //kmcNC,          // kmNuMuNCpiCpi0
      kmcNC,          // kmNuMuNCcoh
      kmcNC,          // kmNuMuNCoth
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE
      kmcNuMuBarCC,   // kmNuMuBarCCMEC
      kmcNuMuBarCC,   // kmNuMuBarCC1piC
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0
      kmcNuMuBarCC,   // kmNuMuBarCC2piC
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0
      kmcNuMuBarCC,   // kmNuMuBarCCcoh
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat
    //kmcNC,          // kmNuMuBarNCEL
    //kmcNC,          // kmNuMuBarNCMEC
      kmcNC,          // kmNuMuBarNC1piC
      kmcNC,          // kmNuMuBarNC1pi0
    //kmcNC,          // kmNuMuBarNC2piC
    //kmcNC,          // kmNuMuBarNC2pi0
    //kmcNC,          // kmNuMuBarNCpiCpi0
      kmcNC,          // kmNuMuBarNCcoh
      kmcNC,          // kmNuMuBarNCoth
      kmcNC,          // kmNuMuBarNCELScat
      kmcNuENuEBarCC, // kmNuECCQE
      kmcNuENuEBarCC, // kmNuECCMEC
      kmcNuENuEBarCC, // kmNuECC1piC
      kmcNuENuEBarCC, // kmNuECC1pi0
      kmcNuENuEBarCC, // kmNuECC2piC
      kmcNuENuEBarCC, // kmNuECC2pi0
      kmcNuENuEBarCC, // kmNuECCpiCpi0
      kmcNuENuEBarCC, // kmNuECCcoh
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL
    //kmcNC,          // kmNuENCMEC
      kmcNC,          // kmNuENC1piC
      kmcNC,          // kmNuENC1pi0
    //kmcNC,          // kmNuENC2piC
    //kmcNC,          // kmNuENC2pi0
    //kmcNC,          // kmNuENCpiCpi0
      kmcNC,          // kmNuENCcoh
      kmcNC,          // kmNuENCoth
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE
      kmcNuENuEBarCC, // kmNuEBarCCMEC
      kmcNuENuEBarCC, // kmNuEBarCC1piC
      kmcNuENuEBarCC, // kmNuEBarCC1pi0
      kmcNuENuEBarCC, // kmNuEBarCC2piC
      kmcNuENuEBarCC, // kmNuEBarCC2pi0
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth
    //kmcNC,          // kmNuEBarNCEL
    //kmcNC,          // kmNuEBarNCMEC
      kmcNC,          // kmNuEBarNC1piC
      kmcNC,          // kmNuEBarNC1pi0
    //kmcNC,          // kmNuEBarNC2piC
    //kmcNC,          // kmNuEBarNC2pi0
    //kmcNC,          // kmNuEBarNCpiCpi0
      kmcNC,          // kmNuEBarNCcoh
      kmcNC,           // kmNuEBarNCoth
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNuMuCCWSoth
    {
      kmcNuMuCCQEMEC, // kmNuMuCCQE
      kmcNuMuCCQEMEC, // kmNuMuCCMEC
      kmcNuMuCC1pi,   // kmNuMuCC1piC
      kmcNuMuCC1pi,   // kmNuMuCC1pi0
      kmcNuMuCC2pi,   // kmNuMuCC2piC
      kmcNuMuCC2pi,   // kmNuMuCC2pi0
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0
      kmcNuMuCCoth,   // kmNuMuCCcoh
      kmcNuMuCCoth,   // kmNuMuCCIMD
      kmcNuMuCCoth,   // kmNuMuCCoth
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL
    //kmcNC,          // kmNuMuNCMEC
      kmcNC,          // kmNuMuNC1piC
      kmcNC,          // kmNuMuNC1pi0
    //kmcNC,          // kmNuMuNC2piC
    //kmcNC,          // kmNuMuNC2pi0
    //kmcNC,          // kmNuMuNCpiCpi0
      kmcNC,          // kmNuMuNCcoh
      kmcNC,          // kmNuMuNCoth
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE
      kmcNuMuBarCC,   // kmNuMuBarCCMEC
      kmcNuMuBarCC,   // kmNuMuBarCC1piC
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0
      kmcNuMuBarCC,   // kmNuMuBarCC2piC
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0
      kmcNuMuBarCC,   // kmNuMuBarCCcoh
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat
    //kmcNC,          // kmNuMuBarNCEL
    //kmcNC,          // kmNuMuBarNCMEC
      kmcNC,          // kmNuMuBarNC1piC
      kmcNC,          // kmNuMuBarNC1pi0
    //kmcNC,          // kmNuMuBarNC2piC
    //kmcNC,          // kmNuMuBarNC2pi0
    //kmcNC,          // kmNuMuBarNCpiCpi0
      kmcNC,          // kmNuMuBarNCcoh
      kmcNC,          // kmNuMuBarNCoth
      kmcNC,          // kmNuMuBarNCELScat
      kmcNuENuEBarCC, // kmNuECCQE
      kmcNuENuEBarCC, // kmNuECCMEC
      kmcNuENuEBarCC, // kmNuECC1piC
      kmcNuENuEBarCC, // kmNuECC1pi0
      kmcNuENuEBarCC, // kmNuECC2piC
      kmcNuENuEBarCC, // kmNuECC2pi0
      kmcNuENuEBarCC, // kmNuECCpiCpi0
      kmcNuENuEBarCC, // kmNuECCcoh
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL
    //kmcNC,          // kmNuENCMEC
      kmcNC,          // kmNuENC1piC
      kmcNC,          // kmNuENC1pi0
    //kmcNC,          // kmNuENC2piC
    //kmcNC,          // kmNuENC2pi0
    //kmcNC,          // kmNuENCpiCpi0
      kmcNC,          // kmNuENCcoh
      kmcNC,          // kmNuENCoth
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE
      kmcNuENuEBarCC, // kmNuEBarCCMEC
      kmcNuENuEBarCC, // kmNuEBarCC1piC
      kmcNuENuEBarCC, // kmNuEBarCC1pi0
      kmcNuENuEBarCC, // kmNuEBarCC2piC
      kmcNuENuEBarCC, // kmNuEBarCC2pi0
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth
    //kmcNC,          // kmNuEBarNCEL
    //kmcNC,          // kmNuEBarNCMEC
      kmcNC,          // kmNuEBarNC1piC
      kmcNC,          // kmNuEBarNC1pi0
    //kmcNC,          // kmNuEBarNC2piC
    //kmcNC,          // kmNuEBarNC2pi0
    //kmcNC,          // kmNuEBarNCpiCpi0
      kmcNC,          // kmNuEBarNCcoh
      kmcNC,           // kmNuEBarNCoth
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNuECC0pi
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNCoth,          // kmNuMuNC1piC          
      kmcNC1pi0,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNCoth,          // kmNuMuBarNC1piC       
      kmcNC1pi0,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNCoth,          // kmNuENC1piC           
      kmcNC1pi0,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNCoth,          // kmNuEBarNC1piC        
      kmcNC1pi0,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNuECC1piC
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNCoth,          // kmNuMuNC1piC          
      kmcNC1pi0,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNCoth,          // kmNuMuBarNC1piC       
      kmcNC1pi0,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNCoth,          // kmNuENC1piC           
      kmcNC1pi0,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNCoth,          // kmNuEBarNC1piC        
      kmcNC1pi0,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNuECC1pi0
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNCoth,       // kmNuMuNC1piC          
      kmcNC1pi0,      // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNCoth,          // kmNuMuBarNC1piC       
      kmcNC1pi0,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNCoth,          // kmNuENC1piC           
      kmcNC1pi0,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNCoth,          // kmNuEBarNC1piC        
      kmcNC1pi0,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNuECCoth
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNCoth,          // kmNuMuNC1piC          
      kmcNC1pi0,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNCoth,          // kmNuMuBarNC1piC       
      kmcNC1pi0,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNCoth,          // kmNuENC1piC           
      kmcNC1pi0,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNCoth,          // kmNuEBarNC1piC        
      kmcNC1pi0,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNC0pi
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC1piC,      // kmNuMuNC1piC          
      kmcNC1pi0,      // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC1piC,      // kmNuMuBarNC1piC       
      kmcNC1pi0,      // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC1piC,      // kmNuENC1piC           
      kmcNC1pi0,      // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNCoth,          // kmNuEBarNC1piC        
      kmcNC1pi0,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNC1piC
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC1piC,      // kmNuMuNC1piC          
      kmcNC1pi0,      // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC1piC,      // kmNuMuBarNC1piC       
      kmcNC1pi0,      // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC1piC,      // kmNuENC1piC           
      kmcNC1pi0,      // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC1piC,      // kmNuEBarNC1piC        
      kmcNC1pi0,      // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNC1pi0
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC1piC,      // kmNuMuNC1piC          
      kmcNC1pi0,      // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC1piC,      // kmNuMuBarNC1piC       
      kmcNC1pi0,      // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC1piC,      // kmNuENC1piC           
      kmcNC1pi0,      // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC1piC,      // kmNuEBarNC1piC        
      kmcNC1pi0,      // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNCoth
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC1piC,      // kmNuMuNC1piC          
      kmcNC1pi0,      // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC1piC,      // kmNuMuBarNC1piC       
      kmcNC1pi0,      // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC1piC,      // kmNuENC1piC           
      kmcNC1pi0,      // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC1piC,      // kmNuEBarNC1piC        
      kmcNC1pi0,      // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksNeutrinoElec
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCIMD           
      kmcNuMuCCoth,   // kmNuMuCCoth 
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },

    // selection: ksInvMuDecay
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCIMD           
      kmcNuMuCCoth,   // kmNuMuCCoth 
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined
    },
    // selection: ksNuECCWS
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNCoth,          // kmNuMuNC1piC          
      kmcNC1pi0,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNCoth,          // kmNuMuBarNC1piC       
      kmcNC1pi0,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNCoth,          // kmNuENC1piC           
      kmcNC1pi0,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNCoth,          // kmNuEBarNC1piC        
      kmcNC1pi0,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
      kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
	kmcUndefined,
      kmcUndefined                        
    },
    //far detector
    //selection: NuMuCChigh
    {
      kmcNuMuCCQEMEC,    // kmNuMuCCQE            
      kmcNuMuCCQEMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCIMD           
      kmcNuMuCCoth,   // kmNuMuCCoth 
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuMuCCQEMEC, //kmNuEToNuMuCCQE
      kmcNuMuCCQEMEC, //kmNuEToNuMuCCMEC
      kmcNuMuCC1pi,   //kmNuEToNuMuCC1piC
      kmcNuMuCC1pi,   //kmNuEToNuMuCC1pi0
      kmcNuMuCC2pi,   //kmNuEToNuMuCC2piC
      kmcNuMuCC2pi,   //kmNuEToNuMuCC2pi0
      kmcNuMuCC2pi,   //kmNuEToNuMuCC1piC1pi0
      kmcNuMuCCoth,   //kmNuEToNuMuCCcoh
      kmcNuMuCCoth,   //kmNuEToNuMuCCIDM
      kmcNuMuCCoth,   //kmNuEToNuMuCCELScat
      kmcNuMuCCoth,   //kmNuEToNuMuCCoth
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCQE
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCMEC
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC1piC
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC1pi0
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC2piC
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC2pi0
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC1pi01piC
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCcoh
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCIDM
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCELScat
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCoth
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCMEC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1piC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC2piC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC2pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1piC1pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCcoh
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCELScat
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCoth
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC       //kmNuEBarToNuTauBarCCQE
    },
    //selection: NuMuCClow
    {
      kmcNuMuCCQEMEC,    // kmNuMuCCQE            
      kmcNuMuCCQEMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCIMD           
      kmcNuMuCCoth,   // kmNuMuCCoth 
      kmcNuMuCCoth,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth   
      kmcNC,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
      kmcNC,          // kmNuMuBarNCELScat 
      kmcNuENuEBarCC, // kmNuECCQE             
      kmcNuENuEBarCC, // kmNuECCMEC            
      kmcNuENuEBarCC, // kmNuECC1piC           
      kmcNuENuEBarCC, // kmNuECC1pi0           
      kmcNuENuEBarCC, // kmNuECC2piC           
      kmcNuENuEBarCC, // kmNuECC2pi0           
      kmcNuENuEBarCC, // kmNuECCpiCpi0         
      kmcNuENuEBarCC, // kmNuECCcoh            
      kmcNuENuEBarCC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNC,          // kmNuENC1piC           
      kmcNC,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNC,          // kmNuENCcoh            
      kmcNC,          // kmNuENCoth            
      kmcNC,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC, // kmNuEBarCCQE          
      kmcNuENuEBarCC, // kmNuEBarCCMEC         
      kmcNuENuEBarCC, // kmNuEBarCC1piC        
      kmcNuENuEBarCC, // kmNuEBarCC1pi0        
      kmcNuENuEBarCC, // kmNuEBarCC2piC        
      kmcNuENuEBarCC, // kmNuEBarCC2pi0        
      kmcNuENuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC, // kmNuEBarCCcoh
      kmcNuENuEBarCC, // kmNuEBarCCIMD
      kmcNuENuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNC,          // kmNuEBarNC1piC        
      kmcNC,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNC,          // kmNuEBarNCcoh         
      kmcNC,           // kmNuEBarNCoth          
      kmcNC,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuENuEBarCC,    //kmNuMuToNuECCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuMuCCQEMEC, //kmNuEToNuMuCCQE
      kmcNuMuCCQEMEC, //kmNuEToNuMuCCMEC
      kmcNuMuCC1pi,   //kmNuEToNuMuCC1piC
      kmcNuMuCC1pi,   //kmNuEToNuMuCC1pi0
      kmcNuMuCC2pi,   //kmNuEToNuMuCC2piC
      kmcNuMuCC2pi,   //kmNuEToNuMuCC2pi0
      kmcNuMuCC2pi,   //kmNuEToNuMuCC1piC1pi0
      kmcNuMuCCoth,   //kmNuEToNuMuCCcoh
      kmcNuMuCCoth,   //kmNuEToNuMuCCIDM
      kmcNuMuCCoth,   //kmNuEToNuMuCCELScat
      kmcNuMuCCoth,   //kmNuEToNuMuCCoth
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCQE
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCMEC
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC1piC
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC1pi0
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC2piC
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC2pi0
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCC1pi01piC
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCcoh
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCIDM
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCELScat
      kmcNuENuEBarCC, //kmNuMuBarToNuEBarCCoth
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCMEC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1piC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC2piC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC2pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1piC1pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCcoh
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCELScat
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCoth
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC       //kmNuEBarToNuTauBarCCQE
    },
    //selection: NuECChigh
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNCoth,          // kmNuMuNC1piC          
      kmcNC1pi0,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNCoth,          // kmNuMuBarNC1piC       
      kmcNC1pi0,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNCoth,          // kmNuENC1piC           
      kmcNC1pi0,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNCoth,          // kmNuEBarNC1piC        
      kmcNC1pi0,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuMuCC, //kmNuEToNuMuCCQE
      kmcNuMuCC, //kmNuEToNuMuCCMEC
      kmcNuMuCC,   //kmNuEToNuMuCC1piC
      kmcNuMuCC,   //kmNuEToNuMuCC1pi0
      kmcNuMuCC,   //kmNuEToNuMuCC2piC
      kmcNuMuCC,   //kmNuEToNuMuCC2pi0
      kmcNuMuCC,   //kmNuEToNuMuCC1piC1pi0
      kmcNuMuCC,   //kmNuEToNuMuCCcoh
      kmcNuMuCC,   //kmNuEToNuMuCCIDM
      kmcNuMuCC,   //kmNuEToNuMuCCELScat
      kmcNuMuCC,   //kmNuEToNuMuCCoth
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCQE
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCMEC
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC1piC
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC1pi0
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC2piC
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC2pi0
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC1pi01piC
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCcoh
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCIDM
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCELScat
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCoth
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCMEC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1piC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC2piC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC2pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1piC1pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCcoh
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCELScat
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCoth
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC       //kmNuEBarToNuTauBarCCQE
    },
    //selection: NuECClow
    {
      kmcNuMuCC,    // kmNuMuCCQE            
      kmcNuMuCC,   // kmNuMuCCMEC           
      kmcNuMuCC,   // kmNuMuCC1piC          
      kmcNuMuCC,   // kmNuMuCC1pi0          
      kmcNuMuCC,   // kmNuMuCC2piC          
      kmcNuMuCC,   // kmNuMuCC2pi0          
      kmcNuMuCC,   // kmNuMuCCpiCpi0        
      kmcNuMuCC,   // kmNuMuCCcoh           
      kmcNuMuCC,   // kmNuMuCCIMD           
      kmcNuMuCC,   // kmNuMuCCoth 
      kmcNuMuCC,   // kmNuMuCCELScat
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNCoth,          // kmNuMuNC1piC          
      kmcNC1pi0,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNCoth,          // kmNuMuNCcoh           
      kmcNCoth,          // kmNuMuNCoth   
      kmcNCoth,          // kmNuMuNCELScat
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth
      kmcNuMuBarCC,   // kmNuMuBarCCELScat 
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNCoth,          // kmNuMuBarNC1piC       
      kmcNC1pi0,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNCoth,          // kmNuMuBarNCcoh        
      kmcNCoth,          // kmNuMuBarNCoth        
      kmcNCoth,          // kmNuMuBarNCELScat 
      kmcNuECC, // kmNuECCQE             
      kmcNuECC, // kmNuECCMEC            
      kmcNuECC, // kmNuECC1piC           
      kmcNuECC, // kmNuECC1pi0           
      kmcNuECC, // kmNuECC2piC           
      kmcNuECC, // kmNuECC2pi0           
      kmcNuECC, // kmNuECCpiCpi0         
      kmcNuECC, // kmNuECCcoh            
      kmcNuECC, // kmNuECCoth
      //kmcNC,          // kmNuENCEL             
    //kmcNC,          // kmNuENCMEC           
      kmcNCoth,          // kmNuENC1piC           
      kmcNC1pi0,          // kmNuENC1pi0           
    //kmcNC,          // kmNuENC2piC           
    //kmcNC,          // kmNuENC2pi0           
    //kmcNC,          // kmNuENCpiCpi0         
      kmcNCoth,          // kmNuENCcoh            
      kmcNCoth,          // kmNuENCoth            
      kmcNCoth,          // kmNuEELScat - caveat! this one contains both CC and NC contributions
      kmcNuEBarCC, // kmNuEBarCCQE          
      kmcNuEBarCC, // kmNuEBarCCMEC         
      kmcNuEBarCC, // kmNuEBarCC1piC        
      kmcNuEBarCC, // kmNuEBarCC1pi0        
      kmcNuEBarCC, // kmNuEBarCC2piC        
      kmcNuEBarCC, // kmNuEBarCC2pi0        
      kmcNuEBarCC, // kmNuEBarCCpiCpi0      
      kmcNuEBarCC, // kmNuEBarCCcoh
      kmcNuEBarCC, // kmNuEBarCCIMD
      kmcNuEBarCC, // kmNuEBarCCoth         
    //kmcNC,          // kmNuEBarNCEL          
    //kmcNC,          // kmNuEBarNCMEC         
      kmcNCoth,          // kmNuEBarNC1piC        
      kmcNC1pi0,          // kmNuEBarNC1pi0        
    //kmcNC,          // kmNuEBarNC2piC        
    //kmcNC,          // kmNuEBarNC2pi0        
    //kmcNC,          // kmNuEBarNCpiCpi0      
      kmcNCoth,          // kmNuEBarNCcoh         
      kmcNCoth,           // kmNuEBarNCoth          
      kmcNCoth,          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuECC,    //kmNuMuToNuECCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuMuToNuTauCCQE
      kmcNuMuCC, //kmNuEToNuMuCCQE
      kmcNuMuCC, //kmNuEToNuMuCCMEC
      kmcNuMuCC,   //kmNuEToNuMuCC1piC
      kmcNuMuCC,   //kmNuEToNuMuCC1pi0
      kmcNuMuCC,   //kmNuEToNuMuCC2piC
      kmcNuMuCC,   //kmNuEToNuMuCC2pi0
      kmcNuMuCC,   //kmNuEToNuMuCC1piC1pi0
      kmcNuMuCC,   //kmNuEToNuMuCCcoh
      kmcNuMuCC,   //kmNuEToNuMuCCIDM
      kmcNuMuCC,   //kmNuEToNuMuCCELScat
      kmcNuMuCC,   //kmNuEToNuMuCCoth
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuTauNuTauBarCC,//kmNuEToNuTauCCQE
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCQE
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCMEC
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC1piC
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC1pi0
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC2piC
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC2pi0
      kmcNuEBarCC, //kmNuMuBarToNuEBarCC1pi01piC
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCcoh
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCIDM
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCELScat
      kmcNuEBarCC, //kmNuMuBarToNuEBarCCoth
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCMEC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1piC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC2piC
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC2pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCC1piC1pi0
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCcoh
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCELScat
      kmcNuTauNuTauBarCC,      //kmNuMuBarToNuTauBarCCoth
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuMuBarCC, //kmNuEBarToNuMuBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC,       //kmNuEBarToNuTauBarCCQE
      kmcNuTauNuTauBarCC       //kmNuEBarToNuTauBarCCQE
    }
    }//end of RHC
};

} // conv
} // valor

#endif 

