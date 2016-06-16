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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
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
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
      },
      //2016a near detector
      // selection: ksNuECC
      /*{
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
      },
      // selection: ksNuMuCCWS
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
      },
      // selection: ksNC
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat
	},*/
      //far detector
      // selection: ksNuMuCClow
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat,
	kmNuMuToNuECCQE, 
	kmNuMuToNuECCMEC,
	kmNuMuToNuECC1piC,
	kmNuMuToNuECC1pi0,
	kmNuMuToNuECC2piC,
	kmNuMuToNuECC2pi0,
	kmNuMuToNuECCpiCpi0,
	kmNuMuToNuECCcoh,   
	kmNuMuToNuECCoth,   
	kmNuMuToNuEELScat,  
	kmNuMuToNuTauCCQE,  
	kmNuMuToNuTauCCMEC, 
	kmNuMuToNuTauCC1piC,
	kmNuMuToNuTauCC1pi0,
	kmNuMuToNuTauCC2piC,
	kmNuMuToNuTauCC2pi0,
	kmNuMuToNuTauCCpiCpi0,
	kmNuMuToNuTauCCcoh,   
	kmNuMuToNuTauCCoth,   
	kmNuMuToNuTauCCELScat,
	kmNuEToNuMuCCQE, 
	kmNuEToNuMuCCMEC,
	kmNuEToNuMuCC1piC,
	kmNuEToNuMuCC1pi0,
	kmNuEToNuMuCC2piC,
	kmNuEToNuMuCC2pi0,
	kmNuEToNuMuCCpiCpi0,
	kmNuEToNuMuCCcoh,   
	kmNuEToNuMuCCoth,   
	kmNuEToNuMuCCELScat,
	kmNuEToNuTauCCQE,   
	kmNuEToNuTauCCMEC,  
	kmNuEToNuTauCC1piC, 
	kmNuEToNuTauCC1pi0, 
	kmNuEToNuTauCC2piC, 
	kmNuEToNuTauCC2pi0, 
	kmNuEToNuTauCCpiCpi0, 
	kmNuEToNuTauCCcoh,    
	kmNuEToNuTauCCoth,    
	kmNuEToNuTauCCELScat, 
	kmNuMuBarToNuEBarCCQE,
	kmNuMuBarToNuEBarCCMEC, 
	kmNuMuBarToNuEBarCC1piC, 
	kmNuMuBarToNuEBarCC1pi0, 
	kmNuMuBarToNuEBarCC2piC, 
	kmNuMuBarToNuEBarCC2pi0, 
	kmNuMuBarToNuEBarCCpiCpi0,
	kmNuMuBarToNuEBarCCcoh,   
	kmNuMuBarToNuEBarCCoth,   
	kmNuMuBarToNuEBarELScat,  
	kmNuMuBarToNuTauBarCCQE,  
	kmNuMuBarToNuTauBarCCMEC, 
	kmNuMuBarToNuTauBarCC1piC,
	kmNuMuBarToNuTauBarCC1pi0, 
	kmNuMuBarToNuTauBarCC2piC, 
	kmNuMuBarToNuTauBarCC2pi0, 
	kmNuMuBarToNuTauBarCCpiCpi0,
	kmNuMuBarToNuTauBarCCcoh,   
	kmNuMuBarToNuTauBarCCoth,   
	kmNuMuBarToNuTauBarCCELScat,
	kmNuEBarToNuMuBarCCQE,      
	kmNuEBarToNuMuBarCCMEC,     
	kmNuEBarToNuMuBarCC1piC,    
	kmNuEBarToNuMuBarCC1pi0,    
	kmNuEBarToNuMuBarCC2piC,    
	kmNuEBarToNuMuBarCC2pi0,
	kmNuEBarToNuMuBarCCpiCpi0,
	kmNuEBarToNuMuBarCCcoh,
	kmNuEBarToNuMuBarCCoth,
	kmNuEBarToNuMuBarCCELScat,
	kmNuEBarToNuTauBarCCQE,
	kmNuEBarToNuTauBarCCMEC,
	kmNuEBarToNuTauBarCC1piC,
	kmNuEBarToNuTauBarCC1pi0,
	kmNuEBarToNuTauBarCC2piC,
	kmNuEBarToNuTauBarCC2pi0,
	kmNuEBarToNuTauBarCCpiCpi0,
	kmNuEBarToNuTauBarCCcoh,
	kmNuEBarToNuTauBarCCoth,
	kmNuEBarToNuTauBarCCELScat
      },
      // selection: ksNuMuCChigh
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat,
	kmNuMuToNuECCQE, 
	kmNuMuToNuECCMEC,
	kmNuMuToNuECC1piC,
	kmNuMuToNuECC1pi0,
	kmNuMuToNuECC2piC,
	kmNuMuToNuECC2pi0,
	kmNuMuToNuECCpiCpi0,
	kmNuMuToNuECCcoh,   
	kmNuMuToNuECCoth,   
	kmNuMuToNuEELScat,  
	kmNuMuToNuTauCCQE,  
	kmNuMuToNuTauCCMEC, 
	kmNuMuToNuTauCC1piC,
	kmNuMuToNuTauCC1pi0,
	kmNuMuToNuTauCC2piC,
	kmNuMuToNuTauCC2pi0,
	kmNuMuToNuTauCCpiCpi0,
	kmNuMuToNuTauCCcoh,   
	kmNuMuToNuTauCCoth,   
	kmNuMuToNuTauCCELScat,
	kmNuEToNuMuCCQE, 
	kmNuEToNuMuCCMEC,
	kmNuEToNuMuCC1piC,
	kmNuEToNuMuCC1pi0,
	kmNuEToNuMuCC2piC,
	kmNuEToNuMuCC2pi0,
	kmNuEToNuMuCCpiCpi0,
	kmNuEToNuMuCCcoh,   
	kmNuEToNuMuCCoth,   
	kmNuEToNuMuCCELScat,
	kmNuEToNuTauCCQE,   
	kmNuEToNuTauCCMEC,  
	kmNuEToNuTauCC1piC, 
	kmNuEToNuTauCC1pi0, 
	kmNuEToNuTauCC2piC, 
	kmNuEToNuTauCC2pi0, 
	kmNuEToNuTauCCpiCpi0, 
	kmNuEToNuTauCCcoh,    
	kmNuEToNuTauCCoth,    
	kmNuEToNuTauCCELScat, 
	kmNuMuBarToNuEBarCCQE,
	kmNuMuBarToNuEBarCCMEC, 
	kmNuMuBarToNuEBarCC1piC, 
	kmNuMuBarToNuEBarCC1pi0, 
	kmNuMuBarToNuEBarCC2piC, 
	kmNuMuBarToNuEBarCC2pi0, 
	kmNuMuBarToNuEBarCCpiCpi0,
	kmNuMuBarToNuEBarCCcoh,   
	kmNuMuBarToNuEBarCCoth,   
	kmNuMuBarToNuEBarELScat,  
	kmNuMuBarToNuTauBarCCQE,  
	kmNuMuBarToNuTauBarCCMEC, 
	kmNuMuBarToNuTauBarCC1piC,
	kmNuMuBarToNuTauBarCC1pi0, 
	kmNuMuBarToNuTauBarCC2piC, 
	kmNuMuBarToNuTauBarCC2pi0, 
	kmNuMuBarToNuTauBarCCpiCpi0,
	kmNuMuBarToNuTauBarCCcoh,   
	kmNuMuBarToNuTauBarCCoth,   
	kmNuMuBarToNuTauBarCCELScat,
	kmNuEBarToNuMuBarCCQE,      
	kmNuEBarToNuMuBarCCMEC,     
	kmNuEBarToNuMuBarCC1piC,    
	kmNuEBarToNuMuBarCC1pi0,    
	kmNuEBarToNuMuBarCC2piC,    
	kmNuEBarToNuMuBarCC2pi0,
	kmNuEBarToNuMuBarCCpiCpi0,
	kmNuEBarToNuMuBarCCcoh,
	kmNuEBarToNuMuBarCCoth,
	kmNuEBarToNuMuBarCCELScat,
	kmNuEBarToNuTauBarCCQE,
	kmNuEBarToNuTauBarCCMEC,
	kmNuEBarToNuTauBarCC1piC,
	kmNuEBarToNuTauBarCC1pi0,
	kmNuEBarToNuTauBarCC2piC,
	kmNuEBarToNuTauBarCC2pi0,
	kmNuEBarToNuTauBarCCpiCpi0,
	kmNuEBarToNuTauBarCCcoh,
	kmNuEBarToNuTauBarCCoth,
	kmNuEBarToNuTauBarCCELScat
      },
      // selection: ksNuMuBarCClow
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat,
	kmNuMuToNuECCQE, 
	kmNuMuToNuECCMEC,
	kmNuMuToNuECC1piC,
	kmNuMuToNuECC1pi0,
	kmNuMuToNuECC2piC,
	kmNuMuToNuECC2pi0,
	kmNuMuToNuECCpiCpi0,
	kmNuMuToNuECCcoh,   
	kmNuMuToNuECCoth,   
	kmNuMuToNuEELScat,  
	kmNuMuToNuTauCCQE,  
	kmNuMuToNuTauCCMEC, 
	kmNuMuToNuTauCC1piC,
	kmNuMuToNuTauCC1pi0,
	kmNuMuToNuTauCC2piC,
	kmNuMuToNuTauCC2pi0,
	kmNuMuToNuTauCCpiCpi0,
	kmNuMuToNuTauCCcoh,   
	kmNuMuToNuTauCCoth,   
	kmNuMuToNuTauCCELScat,
	kmNuEToNuMuCCQE, 
	kmNuEToNuMuCCMEC,
	kmNuEToNuMuCC1piC,
	kmNuEToNuMuCC1pi0,
	kmNuEToNuMuCC2piC,
	kmNuEToNuMuCC2pi0,
	kmNuEToNuMuCCpiCpi0,
	kmNuEToNuMuCCcoh,   
	kmNuEToNuMuCCoth,   
	kmNuEToNuMuCCELScat,
	kmNuEToNuTauCCQE,   
	kmNuEToNuTauCCMEC,  
	kmNuEToNuTauCC1piC, 
	kmNuEToNuTauCC1pi0, 
	kmNuEToNuTauCC2piC, 
	kmNuEToNuTauCC2pi0, 
	kmNuEToNuTauCCpiCpi0, 
	kmNuEToNuTauCCcoh,    
	kmNuEToNuTauCCoth,    
	kmNuEToNuTauCCELScat, 
	kmNuMuBarToNuEBarCCQE,
	kmNuMuBarToNuEBarCCMEC, 
	kmNuMuBarToNuEBarCC1piC, 
	kmNuMuBarToNuEBarCC1pi0, 
	kmNuMuBarToNuEBarCC2piC, 
	kmNuMuBarToNuEBarCC2pi0, 
	kmNuMuBarToNuEBarCCpiCpi0,
	kmNuMuBarToNuEBarCCcoh,   
	kmNuMuBarToNuEBarCCoth,   
	kmNuMuBarToNuEBarELScat,  
	kmNuMuBarToNuTauBarCCQE,  
	kmNuMuBarToNuTauBarCCMEC, 
	kmNuMuBarToNuTauBarCC1piC,
	kmNuMuBarToNuTauBarCC1pi0, 
	kmNuMuBarToNuTauBarCC2piC, 
	kmNuMuBarToNuTauBarCC2pi0, 
	kmNuMuBarToNuTauBarCCpiCpi0,
	kmNuMuBarToNuTauBarCCcoh,   
	kmNuMuBarToNuTauBarCCoth,   
	kmNuMuBarToNuTauBarCCELScat,
	kmNuEBarToNuMuBarCCQE,      
	kmNuEBarToNuMuBarCCMEC,     
	kmNuEBarToNuMuBarCC1piC,    
	kmNuEBarToNuMuBarCC1pi0,    
	kmNuEBarToNuMuBarCC2piC,    
	kmNuEBarToNuMuBarCC2pi0,
	kmNuEBarToNuMuBarCCpiCpi0,
	kmNuEBarToNuMuBarCCcoh,
	kmNuEBarToNuMuBarCCoth,
	kmNuEBarToNuMuBarCCELScat,
	kmNuEBarToNuTauBarCCQE,
	kmNuEBarToNuTauBarCCMEC,
	kmNuEBarToNuTauBarCC1piC,
	kmNuEBarToNuTauBarCC1pi0,
	kmNuEBarToNuTauBarCC2piC,
	kmNuEBarToNuTauBarCC2pi0,
	kmNuEBarToNuTauBarCCpiCpi0,
	kmNuEBarToNuTauBarCCcoh,
	kmNuEBarToNuTauBarCCoth,
	kmNuEBarToNuTauBarCCELScat
      },
      //selection: ksNuMuBarCChigh
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat,
	kmNuMuToNuECCQE, 
	kmNuMuToNuECCMEC,
	kmNuMuToNuECC1piC,
	kmNuMuToNuECC1pi0,
	kmNuMuToNuECC2piC,
	kmNuMuToNuECC2pi0,
	kmNuMuToNuECCpiCpi0,
	kmNuMuToNuECCcoh,   
	kmNuMuToNuECCoth,   
	kmNuMuToNuEELScat,  
	kmNuMuToNuTauCCQE,  
	kmNuMuToNuTauCCMEC, 
	kmNuMuToNuTauCC1piC,
	kmNuMuToNuTauCC1pi0,
	kmNuMuToNuTauCC2piC,
	kmNuMuToNuTauCC2pi0,
	kmNuMuToNuTauCCpiCpi0,
	kmNuMuToNuTauCCcoh,   
	kmNuMuToNuTauCCoth,   
	kmNuMuToNuTauCCELScat,
	kmNuEToNuMuCCQE, 
	kmNuEToNuMuCCMEC,
	kmNuEToNuMuCC1piC,
	kmNuEToNuMuCC1pi0,
	kmNuEToNuMuCC2piC,
	kmNuEToNuMuCC2pi0,
	kmNuEToNuMuCCpiCpi0,
	kmNuEToNuMuCCcoh,   
	kmNuEToNuMuCCoth,   
	kmNuEToNuMuCCELScat,
	kmNuEToNuTauCCQE,   
	kmNuEToNuTauCCMEC,  
	kmNuEToNuTauCC1piC, 
	kmNuEToNuTauCC1pi0, 
	kmNuEToNuTauCC2piC, 
	kmNuEToNuTauCC2pi0, 
	kmNuEToNuTauCCpiCpi0, 
	kmNuEToNuTauCCcoh,    
	kmNuEToNuTauCCoth,    
	kmNuEToNuTauCCELScat, 
	kmNuMuBarToNuEBarCCQE,
	kmNuMuBarToNuEBarCCMEC, 
	kmNuMuBarToNuEBarCC1piC, 
	kmNuMuBarToNuEBarCC1pi0, 
	kmNuMuBarToNuEBarCC2piC, 
	kmNuMuBarToNuEBarCC2pi0, 
	kmNuMuBarToNuEBarCCpiCpi0,
	kmNuMuBarToNuEBarCCcoh,   
	kmNuMuBarToNuEBarCCoth,   
	kmNuMuBarToNuEBarELScat,  
	kmNuMuBarToNuTauBarCCQE,  
	kmNuMuBarToNuTauBarCCMEC, 
	kmNuMuBarToNuTauBarCC1piC,
	kmNuMuBarToNuTauBarCC1pi0, 
	kmNuMuBarToNuTauBarCC2piC, 
	kmNuMuBarToNuTauBarCC2pi0, 
	kmNuMuBarToNuTauBarCCpiCpi0,
	kmNuMuBarToNuTauBarCCcoh,   
	kmNuMuBarToNuTauBarCCoth,   
	kmNuMuBarToNuTauBarCCELScat,
	kmNuEBarToNuMuBarCCQE,      
	kmNuEBarToNuMuBarCCMEC,     
	kmNuEBarToNuMuBarCC1piC,    
	kmNuEBarToNuMuBarCC1pi0,    
	kmNuEBarToNuMuBarCC2piC,    
	kmNuEBarToNuMuBarCC2pi0,
	kmNuEBarToNuMuBarCCpiCpi0,
	kmNuEBarToNuMuBarCCcoh,
	kmNuEBarToNuMuBarCCoth,
	kmNuEBarToNuMuBarCCELScat,
	kmNuEBarToNuTauBarCCQE,
	kmNuEBarToNuTauBarCCMEC,
	kmNuEBarToNuTauBarCC1piC,
	kmNuEBarToNuTauBarCC1pi0,
	kmNuEBarToNuTauBarCC2piC,
	kmNuEBarToNuTauBarCC2pi0,
	kmNuEBarToNuTauBarCCpiCpi0,
	kmNuEBarToNuTauBarCCcoh,
	kmNuEBarToNuTauBarCCoth,
	kmNuEBarToNuTauBarCCELScat
      },
      // selection: ksNuECClow
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat,
	kmNuMuToNuECCQE, 
	kmNuMuToNuECCMEC,
	kmNuMuToNuECC1piC,
	kmNuMuToNuECC1pi0,
	kmNuMuToNuECC2piC,
	kmNuMuToNuECC2pi0,
	kmNuMuToNuECCpiCpi0,
	kmNuMuToNuECCcoh,   
	kmNuMuToNuECCoth,   
	kmNuMuToNuEELScat,  
	kmNuMuToNuTauCCQE,  
	kmNuMuToNuTauCCMEC, 
	kmNuMuToNuTauCC1piC,
	kmNuMuToNuTauCC1pi0,
	kmNuMuToNuTauCC2piC,
	kmNuMuToNuTauCC2pi0,
	kmNuMuToNuTauCCpiCpi0,
	kmNuMuToNuTauCCcoh,   
	kmNuMuToNuTauCCoth,   
	kmNuMuToNuTauCCELScat,
	kmNuEToNuMuCCQE, 
	kmNuEToNuMuCCMEC,
	kmNuEToNuMuCC1piC,
	kmNuEToNuMuCC1pi0,
	kmNuEToNuMuCC2piC,
	kmNuEToNuMuCC2pi0,
	kmNuEToNuMuCCpiCpi0,
	kmNuEToNuMuCCcoh,   
	kmNuEToNuMuCCoth,   
	kmNuEToNuMuCCELScat,
	kmNuEToNuTauCCQE,   
	kmNuEToNuTauCCMEC,  
	kmNuEToNuTauCC1piC, 
	kmNuEToNuTauCC1pi0, 
	kmNuEToNuTauCC2piC, 
	kmNuEToNuTauCC2pi0, 
	kmNuEToNuTauCCpiCpi0, 
	kmNuEToNuTauCCcoh,    
	kmNuEToNuTauCCoth,    
	kmNuEToNuTauCCELScat, 
	kmNuMuBarToNuEBarCCQE,
	kmNuMuBarToNuEBarCCMEC, 
	kmNuMuBarToNuEBarCC1piC, 
	kmNuMuBarToNuEBarCC1pi0, 
	kmNuMuBarToNuEBarCC2piC, 
	kmNuMuBarToNuEBarCC2pi0, 
	kmNuMuBarToNuEBarCCpiCpi0,
	kmNuMuBarToNuEBarCCcoh,   
	kmNuMuBarToNuEBarCCoth,   
	kmNuMuBarToNuEBarELScat,  
	kmNuMuBarToNuTauBarCCQE,  
	kmNuMuBarToNuTauBarCCMEC, 
	kmNuMuBarToNuTauBarCC1piC,
	kmNuMuBarToNuTauBarCC1pi0, 
	kmNuMuBarToNuTauBarCC2piC, 
	kmNuMuBarToNuTauBarCC2pi0, 
	kmNuMuBarToNuTauBarCCpiCpi0,
	kmNuMuBarToNuTauBarCCcoh,   
	kmNuMuBarToNuTauBarCCoth,   
	kmNuMuBarToNuTauBarCCELScat,
	kmNuEBarToNuMuBarCCQE,      
	kmNuEBarToNuMuBarCCMEC,     
	kmNuEBarToNuMuBarCC1piC,    
	kmNuEBarToNuMuBarCC1pi0,    
	kmNuEBarToNuMuBarCC2piC,    
	kmNuEBarToNuMuBarCC2pi0,
	kmNuEBarToNuMuBarCCpiCpi0,
	kmNuEBarToNuMuBarCCcoh,
	kmNuEBarToNuMuBarCCoth,
	kmNuEBarToNuMuBarCCELScat,
	kmNuEBarToNuTauBarCCQE,
	kmNuEBarToNuTauBarCCMEC,
	kmNuEBarToNuTauBarCC1piC,
	kmNuEBarToNuTauBarCC1pi0,
	kmNuEBarToNuTauBarCC2piC,
	kmNuEBarToNuTauBarCC2pi0,
	kmNuEBarToNuTauBarCCpiCpi0,
	kmNuEBarToNuTauBarCCcoh,
	kmNuEBarToNuTauBarCCoth,
	kmNuEBarToNuTauBarCCELScat
      },
      // selection: ksNuECChigh
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat,
	kmNuMuToNuECCQE, 
	kmNuMuToNuECCMEC,
	kmNuMuToNuECC1piC,
	kmNuMuToNuECC1pi0,
	kmNuMuToNuECC2piC,
	kmNuMuToNuECC2pi0,
	kmNuMuToNuECCpiCpi0,
	kmNuMuToNuECCcoh,   
	kmNuMuToNuECCoth,   
	kmNuMuToNuEELScat,  
	kmNuMuToNuTauCCQE,  
	kmNuMuToNuTauCCMEC, 
	kmNuMuToNuTauCC1piC,
	kmNuMuToNuTauCC1pi0,
	kmNuMuToNuTauCC2piC,
	kmNuMuToNuTauCC2pi0,
	kmNuMuToNuTauCCpiCpi0,
	kmNuMuToNuTauCCcoh,   
	kmNuMuToNuTauCCoth,   
	kmNuMuToNuTauCCELScat,
	kmNuEToNuMuCCQE, 
	kmNuEToNuMuCCMEC,
	kmNuEToNuMuCC1piC,
	kmNuEToNuMuCC1pi0,
	kmNuEToNuMuCC2piC,
	kmNuEToNuMuCC2pi0,
	kmNuEToNuMuCCpiCpi0,
	kmNuEToNuMuCCcoh,   
	kmNuEToNuMuCCoth,   
	kmNuEToNuMuCCELScat,
	kmNuEToNuTauCCQE,   
	kmNuEToNuTauCCMEC,  
	kmNuEToNuTauCC1piC, 
	kmNuEToNuTauCC1pi0, 
	kmNuEToNuTauCC2piC, 
	kmNuEToNuTauCC2pi0, 
	kmNuEToNuTauCCpiCpi0, 
	kmNuEToNuTauCCcoh,    
	kmNuEToNuTauCCoth,    
	kmNuEToNuTauCCELScat, 
	kmNuMuBarToNuEBarCCQE,
	kmNuMuBarToNuEBarCCMEC, 
	kmNuMuBarToNuEBarCC1piC, 
	kmNuMuBarToNuEBarCC1pi0, 
	kmNuMuBarToNuEBarCC2piC, 
	kmNuMuBarToNuEBarCC2pi0, 
	kmNuMuBarToNuEBarCCpiCpi0,
	kmNuMuBarToNuEBarCCcoh,   
	kmNuMuBarToNuEBarCCoth,   
	kmNuMuBarToNuEBarELScat,  
	kmNuMuBarToNuTauBarCCQE,  
	kmNuMuBarToNuTauBarCCMEC, 
	kmNuMuBarToNuTauBarCC1piC,
	kmNuMuBarToNuTauBarCC1pi0, 
	kmNuMuBarToNuTauBarCC2piC, 
	kmNuMuBarToNuTauBarCC2pi0, 
	kmNuMuBarToNuTauBarCCpiCpi0,
	kmNuMuBarToNuTauBarCCcoh,   
	kmNuMuBarToNuTauBarCCoth,   
	kmNuMuBarToNuTauBarCCELScat,
	kmNuEBarToNuMuBarCCQE,      
	kmNuEBarToNuMuBarCCMEC,     
	kmNuEBarToNuMuBarCC1piC,    
	kmNuEBarToNuMuBarCC1pi0,    
	kmNuEBarToNuMuBarCC2piC,    
	kmNuEBarToNuMuBarCC2pi0,
	kmNuEBarToNuMuBarCCpiCpi0,
	kmNuEBarToNuMuBarCCcoh,
	kmNuEBarToNuMuBarCCoth,
	kmNuEBarToNuMuBarCCELScat,
	kmNuEBarToNuTauBarCCQE,
	kmNuEBarToNuTauBarCCMEC,
	kmNuEBarToNuTauBarCC1piC,
	kmNuEBarToNuTauBarCC1pi0,
	kmNuEBarToNuTauBarCC2piC,
	kmNuEBarToNuTauBarCC2pi0,
	kmNuEBarToNuTauBarCCpiCpi0,
	kmNuEBarToNuTauBarCCcoh,
	kmNuEBarToNuTauBarCCoth,
	kmNuEBarToNuTauBarCCELScat
      },
      // selection: ksNuEBarCClow
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat,
	kmNuMuToNuECCQE, 
	kmNuMuToNuECCMEC,
	kmNuMuToNuECC1piC,
	kmNuMuToNuECC1pi0,
	kmNuMuToNuECC2piC,
	kmNuMuToNuECC2pi0,
	kmNuMuToNuECCpiCpi0,
	kmNuMuToNuECCcoh,   
	kmNuMuToNuECCoth,   
	kmNuMuToNuEELScat,  
	kmNuMuToNuTauCCQE,  
	kmNuMuToNuTauCCMEC, 
	kmNuMuToNuTauCC1piC,
	kmNuMuToNuTauCC1pi0,
	kmNuMuToNuTauCC2piC,
	kmNuMuToNuTauCC2pi0,
	kmNuMuToNuTauCCpiCpi0,
	kmNuMuToNuTauCCcoh,   
	kmNuMuToNuTauCCoth,   
	kmNuMuToNuTauCCELScat,
	kmNuEToNuMuCCQE, 
	kmNuEToNuMuCCMEC,
	kmNuEToNuMuCC1piC,
	kmNuEToNuMuCC1pi0,
	kmNuEToNuMuCC2piC,
	kmNuEToNuMuCC2pi0,
	kmNuEToNuMuCCpiCpi0,
	kmNuEToNuMuCCcoh,   
	kmNuEToNuMuCCoth,   
	kmNuEToNuMuCCELScat,
	kmNuEToNuTauCCQE,   
	kmNuEToNuTauCCMEC,  
	kmNuEToNuTauCC1piC, 
	kmNuEToNuTauCC1pi0, 
	kmNuEToNuTauCC2piC, 
	kmNuEToNuTauCC2pi0, 
	kmNuEToNuTauCCpiCpi0, 
	kmNuEToNuTauCCcoh,    
	kmNuEToNuTauCCoth,    
	kmNuEToNuTauCCELScat, 
	kmNuMuBarToNuEBarCCQE,
	kmNuMuBarToNuEBarCCMEC, 
	kmNuMuBarToNuEBarCC1piC, 
	kmNuMuBarToNuEBarCC1pi0, 
	kmNuMuBarToNuEBarCC2piC, 
	kmNuMuBarToNuEBarCC2pi0, 
	kmNuMuBarToNuEBarCCpiCpi0,
	kmNuMuBarToNuEBarCCcoh,   
	kmNuMuBarToNuEBarCCoth,   
	kmNuMuBarToNuEBarELScat,  
	kmNuMuBarToNuTauBarCCQE,  
	kmNuMuBarToNuTauBarCCMEC, 
	kmNuMuBarToNuTauBarCC1piC,
	kmNuMuBarToNuTauBarCC1pi0, 
	kmNuMuBarToNuTauBarCC2piC, 
	kmNuMuBarToNuTauBarCC2pi0, 
	kmNuMuBarToNuTauBarCCpiCpi0,
	kmNuMuBarToNuTauBarCCcoh,   
	kmNuMuBarToNuTauBarCCoth,   
	kmNuMuBarToNuTauBarCCELScat,
	kmNuEBarToNuMuBarCCQE,      
	kmNuEBarToNuMuBarCCMEC,     
	kmNuEBarToNuMuBarCC1piC,    
	kmNuEBarToNuMuBarCC1pi0,    
	kmNuEBarToNuMuBarCC2piC,    
	kmNuEBarToNuMuBarCC2pi0,
	kmNuEBarToNuMuBarCCpiCpi0,
	kmNuEBarToNuMuBarCCcoh,
	kmNuEBarToNuMuBarCCoth,
	kmNuEBarToNuMuBarCCELScat,
	kmNuEBarToNuTauBarCCQE,
	kmNuEBarToNuTauBarCCMEC,
	kmNuEBarToNuTauBarCC1piC,
	kmNuEBarToNuTauBarCC1pi0,
	kmNuEBarToNuTauBarCC2piC,
	kmNuEBarToNuTauBarCC2pi0,
	kmNuEBarToNuTauBarCCpiCpi0,
	kmNuEBarToNuTauBarCCcoh,
	kmNuEBarToNuTauBarCCoth,
	kmNuEBarToNuTauBarCCELScat
      },
      // selection: ksNuEBarCChigh
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat,
	kmNuMuToNuECCQE, 
	kmNuMuToNuECCMEC,
	kmNuMuToNuECC1piC,
	kmNuMuToNuECC1pi0,
	kmNuMuToNuECC2piC,
	kmNuMuToNuECC2pi0,
	kmNuMuToNuECCpiCpi0,
	kmNuMuToNuECCcoh,   
	kmNuMuToNuECCoth,   
	kmNuMuToNuEELScat,  
	kmNuMuToNuTauCCQE,  
	kmNuMuToNuTauCCMEC, 
	kmNuMuToNuTauCC1piC,
	kmNuMuToNuTauCC1pi0,
	kmNuMuToNuTauCC2piC,
	kmNuMuToNuTauCC2pi0,
	kmNuMuToNuTauCCpiCpi0,
	kmNuMuToNuTauCCcoh,   
	kmNuMuToNuTauCCoth,   
	kmNuMuToNuTauCCELScat,
	kmNuEToNuMuCCQE, 
	kmNuEToNuMuCCMEC,
	kmNuEToNuMuCC1piC,
	kmNuEToNuMuCC1pi0,
	kmNuEToNuMuCC2piC,
	kmNuEToNuMuCC2pi0,
	kmNuEToNuMuCCpiCpi0,
	kmNuEToNuMuCCcoh,   
	kmNuEToNuMuCCoth,   
	kmNuEToNuMuCCELScat,
	kmNuEToNuTauCCQE,   
	kmNuEToNuTauCCMEC,  
	kmNuEToNuTauCC1piC, 
	kmNuEToNuTauCC1pi0, 
	kmNuEToNuTauCC2piC, 
	kmNuEToNuTauCC2pi0, 
	kmNuEToNuTauCCpiCpi0, 
	kmNuEToNuTauCCcoh,    
	kmNuEToNuTauCCoth,    
	kmNuEToNuTauCCELScat, 
	kmNuMuBarToNuEBarCCQE,
	kmNuMuBarToNuEBarCCMEC, 
	kmNuMuBarToNuEBarCC1piC, 
	kmNuMuBarToNuEBarCC1pi0, 
	kmNuMuBarToNuEBarCC2piC, 
	kmNuMuBarToNuEBarCC2pi0, 
	kmNuMuBarToNuEBarCCpiCpi0,
	kmNuMuBarToNuEBarCCcoh,   
	kmNuMuBarToNuEBarCCoth,   
	kmNuMuBarToNuEBarELScat,  
	kmNuMuBarToNuTauBarCCQE,  
	kmNuMuBarToNuTauBarCCMEC, 
	kmNuMuBarToNuTauBarCC1piC,
	kmNuMuBarToNuTauBarCC1pi0, 
	kmNuMuBarToNuTauBarCC2piC, 
	kmNuMuBarToNuTauBarCC2pi0, 
	kmNuMuBarToNuTauBarCCpiCpi0,
	kmNuMuBarToNuTauBarCCcoh,   
	kmNuMuBarToNuTauBarCCoth,   
	kmNuMuBarToNuTauBarCCELScat,
	kmNuEBarToNuMuBarCCQE,      
	kmNuEBarToNuMuBarCCMEC,     
	kmNuEBarToNuMuBarCC1piC,    
	kmNuEBarToNuMuBarCC1pi0,    
	kmNuEBarToNuMuBarCC2piC,    
	kmNuEBarToNuMuBarCC2pi0,
	kmNuEBarToNuMuBarCCpiCpi0,
	kmNuEBarToNuMuBarCCcoh,
	kmNuEBarToNuMuBarCCoth,
	kmNuEBarToNuMuBarCCELScat,
	kmNuEBarToNuTauBarCCQE,
	kmNuEBarToNuTauBarCCMEC,
	kmNuEBarToNuTauBarCC1piC,
	kmNuEBarToNuTauBarCC1pi0,
	kmNuEBarToNuTauBarCC2piC,
	kmNuEBarToNuTauBarCC2pi0,
	kmNuEBarToNuTauBarCCpiCpi0,
	kmNuEBarToNuTauBarCCcoh,
	kmNuEBarToNuTauBarCCoth,
	kmNuEBarToNuTauBarCCELScat
      },
      // selection: ksNuTauCClow
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat,
	kmNuMuToNuECCQE, 
	kmNuMuToNuECCMEC,
	kmNuMuToNuECC1piC,
	kmNuMuToNuECC1pi0,
	kmNuMuToNuECC2piC,
	kmNuMuToNuECC2pi0,
	kmNuMuToNuECCpiCpi0,
	kmNuMuToNuECCcoh,   
	kmNuMuToNuECCoth,   
	kmNuMuToNuEELScat,  
	kmNuMuToNuTauCCQE,  
	kmNuMuToNuTauCCMEC, 
	kmNuMuToNuTauCC1piC,
	kmNuMuToNuTauCC1pi0,
	kmNuMuToNuTauCC2piC,
	kmNuMuToNuTauCC2pi0,
	kmNuMuToNuTauCCpiCpi0,
	kmNuMuToNuTauCCcoh,   
	kmNuMuToNuTauCCoth,   
	kmNuMuToNuTauCCELScat,
	kmNuEToNuMuCCQE, 
	kmNuEToNuMuCCMEC,
	kmNuEToNuMuCC1piC,
	kmNuEToNuMuCC1pi0,
	kmNuEToNuMuCC2piC,
	kmNuEToNuMuCC2pi0,
	kmNuEToNuMuCCpiCpi0,
	kmNuEToNuMuCCcoh,   
	kmNuEToNuMuCCoth,   
	kmNuEToNuMuCCELScat,
	kmNuEToNuTauCCQE,   
	kmNuEToNuTauCCMEC,  
	kmNuEToNuTauCC1piC, 
	kmNuEToNuTauCC1pi0, 
	kmNuEToNuTauCC2piC, 
	kmNuEToNuTauCC2pi0, 
	kmNuEToNuTauCCpiCpi0, 
	kmNuEToNuTauCCcoh,    
	kmNuEToNuTauCCoth,    
	kmNuEToNuTauCCELScat, 
	kmNuMuBarToNuEBarCCQE,
	kmNuMuBarToNuEBarCCMEC, 
	kmNuMuBarToNuEBarCC1piC, 
	kmNuMuBarToNuEBarCC1pi0, 
	kmNuMuBarToNuEBarCC2piC, 
	kmNuMuBarToNuEBarCC2pi0, 
	kmNuMuBarToNuEBarCCpiCpi0,
	kmNuMuBarToNuEBarCCcoh,   
	kmNuMuBarToNuEBarCCoth,   
	kmNuMuBarToNuEBarELScat,  
	kmNuMuBarToNuTauBarCCQE,  
	kmNuMuBarToNuTauBarCCMEC, 
	kmNuMuBarToNuTauBarCC1piC,
	kmNuMuBarToNuTauBarCC1pi0, 
	kmNuMuBarToNuTauBarCC2piC, 
	kmNuMuBarToNuTauBarCC2pi0, 
	kmNuMuBarToNuTauBarCCpiCpi0,
	kmNuMuBarToNuTauBarCCcoh,   
	kmNuMuBarToNuTauBarCCoth,   
	kmNuMuBarToNuTauBarCCELScat,
	kmNuEBarToNuMuBarCCQE,      
	kmNuEBarToNuMuBarCCMEC,     
	kmNuEBarToNuMuBarCC1piC,    
	kmNuEBarToNuMuBarCC1pi0,    
	kmNuEBarToNuMuBarCC2piC,    
	kmNuEBarToNuMuBarCC2pi0,
	kmNuEBarToNuMuBarCCpiCpi0,
	kmNuEBarToNuMuBarCCcoh,
	kmNuEBarToNuMuBarCCoth,
	kmNuEBarToNuMuBarCCELScat,
	kmNuEBarToNuTauBarCCQE,
	kmNuEBarToNuTauBarCCMEC,
	kmNuEBarToNuTauBarCC1piC,
	kmNuEBarToNuTauBarCC1pi0,
	kmNuEBarToNuTauBarCC2piC,
	kmNuEBarToNuTauBarCC2pi0,
	kmNuEBarToNuTauBarCCpiCpi0,
	kmNuEBarToNuTauBarCCcoh,
	kmNuEBarToNuTauBarCCoth,
	kmNuEBarToNuTauBarCCELScat
      },
      // selection: ksNuTauCChigh
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat,
	kmNuMuToNuECCQE, 
	kmNuMuToNuECCMEC,
	kmNuMuToNuECC1piC,
	kmNuMuToNuECC1pi0,
	kmNuMuToNuECC2piC,
	kmNuMuToNuECC2pi0,
	kmNuMuToNuECCpiCpi0,
	kmNuMuToNuECCcoh,   
	kmNuMuToNuECCoth,   
	kmNuMuToNuEELScat,  
	kmNuMuToNuTauCCQE,  
	kmNuMuToNuTauCCMEC, 
	kmNuMuToNuTauCC1piC,
	kmNuMuToNuTauCC1pi0,
	kmNuMuToNuTauCC2piC,
	kmNuMuToNuTauCC2pi0,
	kmNuMuToNuTauCCpiCpi0,
	kmNuMuToNuTauCCcoh,   
	kmNuMuToNuTauCCoth,   
	kmNuMuToNuTauCCELScat,
	kmNuEToNuMuCCQE, 
	kmNuEToNuMuCCMEC,
	kmNuEToNuMuCC1piC,
	kmNuEToNuMuCC1pi0,
	kmNuEToNuMuCC2piC,
	kmNuEToNuMuCC2pi0,
	kmNuEToNuMuCCpiCpi0,
	kmNuEToNuMuCCcoh,   
	kmNuEToNuMuCCoth,   
	kmNuEToNuMuCCELScat,
	kmNuEToNuTauCCQE,   
	kmNuEToNuTauCCMEC,  
	kmNuEToNuTauCC1piC, 
	kmNuEToNuTauCC1pi0, 
	kmNuEToNuTauCC2piC, 
	kmNuEToNuTauCC2pi0, 
	kmNuEToNuTauCCpiCpi0, 
	kmNuEToNuTauCCcoh,    
	kmNuEToNuTauCCoth,    
	kmNuEToNuTauCCELScat, 
	kmNuMuBarToNuEBarCCQE,
	kmNuMuBarToNuEBarCCMEC, 
	kmNuMuBarToNuEBarCC1piC, 
	kmNuMuBarToNuEBarCC1pi0, 
	kmNuMuBarToNuEBarCC2piC, 
	kmNuMuBarToNuEBarCC2pi0, 
	kmNuMuBarToNuEBarCCpiCpi0,
	kmNuMuBarToNuEBarCCcoh,   
	kmNuMuBarToNuEBarCCoth,   
	kmNuMuBarToNuEBarELScat,  
	kmNuMuBarToNuTauBarCCQE,  
	kmNuMuBarToNuTauBarCCMEC, 
	kmNuMuBarToNuTauBarCC1piC,
	kmNuMuBarToNuTauBarCC1pi0, 
	kmNuMuBarToNuTauBarCC2piC, 
	kmNuMuBarToNuTauBarCC2pi0, 
	kmNuMuBarToNuTauBarCCpiCpi0,
	kmNuMuBarToNuTauBarCCcoh,   
	kmNuMuBarToNuTauBarCCoth,   
	kmNuMuBarToNuTauBarCCELScat,
	kmNuEBarToNuMuBarCCQE,      
	kmNuEBarToNuMuBarCCMEC,     
	kmNuEBarToNuMuBarCC1piC,    
	kmNuEBarToNuMuBarCC1pi0,    
	kmNuEBarToNuMuBarCC2piC,    
	kmNuEBarToNuMuBarCC2pi0,
	kmNuEBarToNuMuBarCCpiCpi0,
	kmNuEBarToNuMuBarCCcoh,
	kmNuEBarToNuMuBarCCoth,
	kmNuEBarToNuMuBarCCELScat,
	kmNuEBarToNuTauBarCCQE,
	kmNuEBarToNuTauBarCCMEC,
	kmNuEBarToNuTauBarCC1piC,
	kmNuEBarToNuTauBarCC1pi0,
	kmNuEBarToNuTauBarCC2piC,
	kmNuEBarToNuTauBarCC2pi0,
	kmNuEBarToNuTauBarCCpiCpi0,
	kmNuEBarToNuTauBarCCcoh,
	kmNuEBarToNuTauBarCCoth,
	kmNuEBarToNuTauBarCCELScat
      },
      // selection: ksNuTauBarCClow
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat,
	kmNuMuToNuECCQE, 
	kmNuMuToNuECCMEC,
	kmNuMuToNuECC1piC,
	kmNuMuToNuECC1pi0,
	kmNuMuToNuECC2piC,
	kmNuMuToNuECC2pi0,
	kmNuMuToNuECCpiCpi0,
	kmNuMuToNuECCcoh,   
	kmNuMuToNuECCoth,   
	kmNuMuToNuEELScat,  
	kmNuMuToNuTauCCQE,  
	kmNuMuToNuTauCCMEC, 
	kmNuMuToNuTauCC1piC,
	kmNuMuToNuTauCC1pi0,
	kmNuMuToNuTauCC2piC,
	kmNuMuToNuTauCC2pi0,
	kmNuMuToNuTauCCpiCpi0,
	kmNuMuToNuTauCCcoh,   
	kmNuMuToNuTauCCoth,   
	kmNuMuToNuTauCCELScat,
	kmNuEToNuMuCCQE, 
	kmNuEToNuMuCCMEC,
	kmNuEToNuMuCC1piC,
	kmNuEToNuMuCC1pi0,
	kmNuEToNuMuCC2piC,
	kmNuEToNuMuCC2pi0,
	kmNuEToNuMuCCpiCpi0,
	kmNuEToNuMuCCcoh,   
	kmNuEToNuMuCCoth,   
	kmNuEToNuMuCCELScat,
	kmNuEToNuTauCCQE,   
	kmNuEToNuTauCCMEC,  
	kmNuEToNuTauCC1piC, 
	kmNuEToNuTauCC1pi0, 
	kmNuEToNuTauCC2piC, 
	kmNuEToNuTauCC2pi0, 
	kmNuEToNuTauCCpiCpi0, 
	kmNuEToNuTauCCcoh,    
	kmNuEToNuTauCCoth,    
	kmNuEToNuTauCCELScat, 
	kmNuMuBarToNuEBarCCQE,
	kmNuMuBarToNuEBarCCMEC, 
	kmNuMuBarToNuEBarCC1piC, 
	kmNuMuBarToNuEBarCC1pi0, 
	kmNuMuBarToNuEBarCC2piC, 
	kmNuMuBarToNuEBarCC2pi0, 
	kmNuMuBarToNuEBarCCpiCpi0,
	kmNuMuBarToNuEBarCCcoh,   
	kmNuMuBarToNuEBarCCoth,   
	kmNuMuBarToNuEBarELScat,  
	kmNuMuBarToNuTauBarCCQE,  
	kmNuMuBarToNuTauBarCCMEC, 
	kmNuMuBarToNuTauBarCC1piC,
	kmNuMuBarToNuTauBarCC1pi0, 
	kmNuMuBarToNuTauBarCC2piC, 
	kmNuMuBarToNuTauBarCC2pi0, 
	kmNuMuBarToNuTauBarCCpiCpi0,
	kmNuMuBarToNuTauBarCCcoh,   
	kmNuMuBarToNuTauBarCCoth,   
	kmNuMuBarToNuTauBarCCELScat,
	kmNuEBarToNuMuBarCCQE,      
	kmNuEBarToNuMuBarCCMEC,     
	kmNuEBarToNuMuBarCC1piC,    
	kmNuEBarToNuMuBarCC1pi0,    
	kmNuEBarToNuMuBarCC2piC,    
	kmNuEBarToNuMuBarCC2pi0,
	kmNuEBarToNuMuBarCCpiCpi0,
	kmNuEBarToNuMuBarCCcoh,
	kmNuEBarToNuMuBarCCoth,
	kmNuEBarToNuMuBarCCELScat,
	kmNuEBarToNuTauBarCCQE,
	kmNuEBarToNuTauBarCCMEC,
	kmNuEBarToNuTauBarCC1piC,
	kmNuEBarToNuTauBarCC1pi0,
	kmNuEBarToNuTauBarCC2piC,
	kmNuEBarToNuTauBarCC2pi0,
	kmNuEBarToNuTauBarCCpiCpi0,
	kmNuEBarToNuTauBarCCcoh,
	kmNuEBarToNuTauBarCCoth,
	kmNuEBarToNuTauBarCCELScat
      },
      // selection: ksNuTauBarCChigh
      {
	kmNuMuCCQE,            
	kmNuMuCCMEC,           
	kmNuMuCC1piC,          
	kmNuMuCC1pi0,          
	kmNuMuCC2piC,          
	kmNuMuCC2pi0,          
	kmNuMuCCpiCpi0,        
	kmNuMuCCcoh,           
	kmNuMuCCoth,           
	kmNuMuCCELScat,
	//kmNuMuNCEL,            
	//kmNuMuNCMEC,           
	kmNuMuNC1piC,          
	kmNuMuNC1pi0,          
	//kmNuMuNC2piC,          
	//kmNuMuNC2pi0,          
	//kmNuMuNCpiCpi0,        
	kmNuMuNCcoh,           
	kmNuMuNCoth,
	kmNuMuNCELScat,
	kmNuMuBarCCQE,         
	kmNuMuBarCCMEC,        
	kmNuMuBarCC1piC,       
	kmNuMuBarCC1pi0,       
	kmNuMuBarCC2piC,       
	kmNuMuBarCC2pi0,       
	kmNuMuBarCCpiCpi0,     
	kmNuMuBarCCcoh,        
	kmNuMuBarCCoth,        
	kmNuMuBarCCELScat,
	//kmNuMuBarNCEL,         
	//kmNuMuBarNCMEC,        
	kmNuMuBarNC1piC,       
	kmNuMuBarNC1pi0,       
	//kmNuMuBarNC2piC,       
	//kmNuMuBarNC2pi0,       
	//kmNuMuBarNCpiCpi0,     
	kmNuMuBarNCcoh,        
	kmNuMuBarNCoth, 
	kmNuMuBarNCELScat,
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
	kmNuENCoth,            
	kmNuEELScat,
	kmNuEBarCCQE,          
	kmNuEBarCCMEC,         
	kmNuEBarCC1piC,        
	kmNuEBarCC1pi0,        
	kmNuEBarCC2piC,        
	kmNuEBarCC2pi0,        
	kmNuEBarCCpiCpi0,      
	kmNuEBarCCcoh,         
	kmNuEBarCCoth,         
	//kmNuEBarNCEL,          
	//kmNuEBarNCMEC,         
	kmNuEBarNC1piC,        
	kmNuEBarNC1pi0,        
	//kmNuEBarNC2piC,        
	//kmNuEBarNC2pi0,        
	//kmNuEBarNCpiCpi0,      
	kmNuEBarNCcoh,         
	kmNuEBarNCoth,
	kmNuEBarELScat,
	kmNuMuToNuECCQE, 
	kmNuMuToNuECCMEC,
	kmNuMuToNuECC1piC,
	kmNuMuToNuECC1pi0,
	kmNuMuToNuECC2piC,
	kmNuMuToNuECC2pi0,
	kmNuMuToNuECCpiCpi0,
	kmNuMuToNuECCcoh,   
	kmNuMuToNuECCoth,   
	kmNuMuToNuEELScat,  
	kmNuMuToNuTauCCQE,  
	kmNuMuToNuTauCCMEC, 
	kmNuMuToNuTauCC1piC,
	kmNuMuToNuTauCC1pi0,
	kmNuMuToNuTauCC2piC,
	kmNuMuToNuTauCC2pi0,
	kmNuMuToNuTauCCpiCpi0,
	kmNuMuToNuTauCCcoh,   
	kmNuMuToNuTauCCoth,   
	kmNuMuToNuTauCCELScat,
	kmNuEToNuMuCCQE, 
	kmNuEToNuMuCCMEC,
	kmNuEToNuMuCC1piC,
	kmNuEToNuMuCC1pi0,
	kmNuEToNuMuCC2piC,
	kmNuEToNuMuCC2pi0,
	kmNuEToNuMuCCpiCpi0,
	kmNuEToNuMuCCcoh,   
	kmNuEToNuMuCCoth,   
	kmNuEToNuMuCCELScat,
	kmNuEToNuTauCCQE,   
	kmNuEToNuTauCCMEC,  
	kmNuEToNuTauCC1piC, 
	kmNuEToNuTauCC1pi0, 
	kmNuEToNuTauCC2piC, 
	kmNuEToNuTauCC2pi0, 
	kmNuEToNuTauCCpiCpi0, 
	kmNuEToNuTauCCcoh,    
	kmNuEToNuTauCCoth,    
	kmNuEToNuTauCCELScat, 
	kmNuMuBarToNuEBarCCQE,
	kmNuMuBarToNuEBarCCMEC, 
	kmNuMuBarToNuEBarCC1piC, 
	kmNuMuBarToNuEBarCC1pi0, 
	kmNuMuBarToNuEBarCC2piC, 
	kmNuMuBarToNuEBarCC2pi0, 
	kmNuMuBarToNuEBarCCpiCpi0,
	kmNuMuBarToNuEBarCCcoh,   
	kmNuMuBarToNuEBarCCoth,   
	kmNuMuBarToNuEBarELScat,  
	kmNuMuBarToNuTauBarCCQE,  
	kmNuMuBarToNuTauBarCCMEC, 
	kmNuMuBarToNuTauBarCC1piC,
	kmNuMuBarToNuTauBarCC1pi0, 
	kmNuMuBarToNuTauBarCC2piC, 
	kmNuMuBarToNuTauBarCC2pi0, 
	kmNuMuBarToNuTauBarCCpiCpi0,
	kmNuMuBarToNuTauBarCCcoh,   
	kmNuMuBarToNuTauBarCCoth,   
	kmNuMuBarToNuTauBarCCELScat,
	kmNuEBarToNuMuBarCCQE,      
	kmNuEBarToNuMuBarCCMEC,     
	kmNuEBarToNuMuBarCC1piC,    
	kmNuEBarToNuMuBarCC1pi0,    
	kmNuEBarToNuMuBarCC2piC,    
	kmNuEBarToNuMuBarCC2pi0,
	kmNuEBarToNuMuBarCCpiCpi0,
	kmNuEBarToNuMuBarCCcoh,
	kmNuEBarToNuMuBarCCoth,
	kmNuEBarToNuMuBarCCELScat,
	kmNuEBarToNuTauBarCCQE,
	kmNuEBarToNuTauBarCCMEC,
	kmNuEBarToNuTauBarCC1piC,
	kmNuEBarToNuTauBarCC1pi0,
	kmNuEBarToNuTauBarCC2piC,
	kmNuEBarToNuTauBarCC2pi0,
	kmNuEBarToNuTauBarCCpiCpi0,
	kmNuEBarToNuTauBarCCcoh,
	kmNuEBarToNuTauBarCCoth,
	kmNuEBarToNuTauBarCCELScat
      },
};
  
  /* 
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
    // sample: ksNuECC
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
    // sample: ksNuMuCCWS
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
    // sample: ksNC
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

  // RHC
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
    // sample: ksNuECC
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
    // sample: ksNuMuCCWS
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
    // sample: ksNC
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
  }// end of RHC

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
    // sample: ksNuECC
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
    // sample: ksNuMuCCWS
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
    // sample: ksNC
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
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQE    
      { kBlack, kYellow,   3001 }, // kmcNuMuBarCCMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }  // kmcNC           
    },
    // sample: ksNuMuCC0pi2trk
    {
      { kBlack, kWhite,    3544 }, // kmcNuMuBarCCQE    
      { kBlack, kYellow,   3001 }, // kmcNuMuBarCCMEC    
      { kBlack, kAzure,    3004 }, // kmcNuMuBarCC1pi
      { kBlack, kBlue,     3005 }, // kmcNuMuBarCC2pi
      { kBlack, kGreen,    3007 }, // kmcNuMuBarCCoth
      { kBlack, kMagenta,  3001 }, // kmcNuMuCC  
      { kBlack, kViolet-1, 3001 }, // kmcNuENuEBarCC
      { kBlack, kRed,      3001 }  // kmcNC           
    },
    // sample: ksNuMuCC1piC
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
    // sample: ksNuMuCC1pi0
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
    // sample: ksNuMuCC1piC1pi0
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
    // sample: ksNuMuCCoth
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
    // sample: ksNuECC
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
    // sample: ksNuMuCCWS
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
    // sample: ksNC
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
  // FHC
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC          // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNuMuCC1piC
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNuMuCC1pi0
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNuMuCC1piC1pi0
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNuMuCCoth
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNuMuCCWS0pi
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNuMuCCWS1piC
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNuMuCCWS1pi0
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNuMuCCWSoth
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNuECC0pi
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNuECC1piC
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNuECC1pi0
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNuECCoth
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNC0pi
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNC1piC
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNC1pi0
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNCoth
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },
    // selection: ksNuECCWS
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNuECC
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNuMuCCWS
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
    },

    // selection: ksNC
    {
      kmcNuMuCCQE,    // kmNuMuCCQE            
      kmcNuMuCCMEC,   // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
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
      kmcNuMuCCoth,   // kmNuMuBarCCELScat 
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
      kmcNC,           // kmNuEBarELScat - caveat! this one contains both CC and NC contributions
      ,                //
    },




  }//end of FHC

  //RHC
  {

  }

};
*/
} // conv
} // valor
  
#endif 

