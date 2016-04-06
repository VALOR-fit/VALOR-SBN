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

#include "Conventions/BeamConf.h"
#include "Conventions/Sample.h"
#include "Conventions/ReacMode.h"
#include "Conventions/ReacModeCoarse.h"

namespace valor {  
namespace conv {

//
// ---------------------------------------------------------------------------
// Define which true reaction modes are considered for each sample 
// included in the analysis
// ---------------------------------------------------------------------------
//

static const ReacMode_t kReactionModes[kNSamples][kNReacModes] = 
{
  // sample: ksNuMuCC1trkQE
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
  //kmNuMuNCEL,            
  //kmNuMuNCMEC,           
    kmNuMuNC1piC,          
    kmNuMuNC1pi0,          
  //kmNuMuNC2piC,          
  //kmNuMuNC2pi0,          
  //kmNuMuNCpiCpi0,        
    kmNuMuNCcoh,           
    kmNuMuNCoth,           
    kmNuMuBarCCQE,         
    kmNuMuBarCCMEC,        
    kmNuMuBarCC1piC,       
    kmNuMuBarCC1pi0,       
    kmNuMuBarCC2piC,       
    kmNuMuBarCC2pi0,       
    kmNuMuBarCCpiCpi0,     
    kmNuMuBarCCcoh,        
    kmNuMuBarCCoth,        
  //kmNuMuBarNCEL,         
  //kmNuMuBarNCMEC,        
    kmNuMuBarNC1piC,       
    kmNuMuBarNC1pi0,       
  //kmNuMuBarNC2piC,       
  //kmNuMuBarNC2pi0,       
  //kmNuMuBarNCpiCpi0,     
    kmNuMuBarNCcoh,        
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
    kmNuENCoth,            
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
    kmNuEBarNCoth          
  },

  // sample: ksNuMuCC2trkQE
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
  //kmNuMuNCEL,            
  //kmNuMuNCMEC,           
    kmNuMuNC1piC,          
    kmNuMuNC1pi0,          
  //kmNuMuNC2piC,          
  //kmNuMuNC2pi0,          
  //kmNuMuNCpiCpi0,        
    kmNuMuNCcoh,           
    kmNuMuNCoth,           
    kmNuMuBarCCQE,         
    kmNuMuBarCCMEC,        
    kmNuMuBarCC1piC,       
    kmNuMuBarCC1pi0,       
    kmNuMuBarCC2piC,       
    kmNuMuBarCC2pi0,       
    kmNuMuBarCCpiCpi0,     
    kmNuMuBarCCcoh,        
    kmNuMuBarCCoth,        
  //kmNuMuBarNCEL,         
  //kmNuMuBarNCMEC,        
    kmNuMuBarNC1piC,       
    kmNuMuBarNC1pi0,       
  //kmNuMuBarNC2piC,       
  //kmNuMuBarNC2pi0,       
  //kmNuMuBarNCpiCpi0,     
    kmNuMuBarNCcoh,        
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
    kmNuENCoth,            
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
    kmNuEBarNCoth          
  },

  // sample: ksNuMuCC1piC
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
  //kmNuMuNCEL,            
  //kmNuMuNCMEC,           
    kmNuMuNC1piC,          
    kmNuMuNC1pi0,          
  //kmNuMuNC2piC,          
  //kmNuMuNC2pi0,          
  //kmNuMuNCpiCpi0,        
    kmNuMuNCcoh,           
    kmNuMuNCoth,           
    kmNuMuBarCCQE,         
    kmNuMuBarCCMEC,        
    kmNuMuBarCC1piC,       
    kmNuMuBarCC1pi0,       
    kmNuMuBarCC2piC,       
    kmNuMuBarCC2pi0,       
    kmNuMuBarCCpiCpi0,     
    kmNuMuBarCCcoh,        
    kmNuMuBarCCoth,        
  //kmNuMuBarNCEL,         
  //kmNuMuBarNCMEC,        
    kmNuMuBarNC1piC,       
    kmNuMuBarNC1pi0,       
  //kmNuMuBarNC2piC,       
  //kmNuMuBarNC2pi0,       
  //kmNuMuBarNCpiCpi0,     
    kmNuMuBarNCcoh,        
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
    kmNuENCoth,            
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
    kmNuEBarNCoth          
  },

  // sample: ksNuMuCC1pi0
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
  //kmNuMuNCEL,            
  //kmNuMuNCMEC,           
    kmNuMuNC1piC,          
    kmNuMuNC1pi0,          
  //kmNuMuNC2piC,          
  //kmNuMuNC2pi0,          
  //kmNuMuNCpiCpi0,        
    kmNuMuNCcoh,           
    kmNuMuNCoth,           
    kmNuMuBarCCQE,         
    kmNuMuBarCCMEC,        
    kmNuMuBarCC1piC,       
    kmNuMuBarCC1pi0,       
    kmNuMuBarCC2piC,       
    kmNuMuBarCC2pi0,       
    kmNuMuBarCCpiCpi0,     
    kmNuMuBarCCcoh,        
    kmNuMuBarCCoth,        
  //kmNuMuBarNCEL,         
  //kmNuMuBarNCMEC,        
    kmNuMuBarNC1piC,       
    kmNuMuBarNC1pi0,       
  //kmNuMuBarNC2piC,       
  //kmNuMuBarNC2pi0,       
  //kmNuMuBarNCpiCpi0,     
    kmNuMuBarNCcoh,        
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
    kmNuENCoth,            
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
    kmNuEBarNCoth          
  },

  // sample: ksNuMuCC1piC1pi0
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
  //kmNuMuNCEL,            
  //kmNuMuNCMEC,           
    kmNuMuNC1piC,          
    kmNuMuNC1pi0,          
  //kmNuMuNC2piC,          
  //kmNuMuNC2pi0,          
  //kmNuMuNCpiCpi0,        
    kmNuMuNCcoh,           
    kmNuMuNCoth,           
    kmNuMuBarCCQE,         
    kmNuMuBarCCMEC,        
    kmNuMuBarCC1piC,       
    kmNuMuBarCC1pi0,       
    kmNuMuBarCC2piC,       
    kmNuMuBarCC2pi0,       
    kmNuMuBarCCpiCpi0,     
    kmNuMuBarCCcoh,        
    kmNuMuBarCCoth,        
  //kmNuMuBarNCEL,         
  //kmNuMuBarNCMEC,        
    kmNuMuBarNC1piC,       
    kmNuMuBarNC1pi0,       
  //kmNuMuBarNC2piC,       
  //kmNuMuBarNC2pi0,       
  //kmNuMuBarNCpiCpi0,     
    kmNuMuBarNCcoh,        
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
    kmNuENCoth,            
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
    kmNuEBarNCoth          
  },

  // sample: ksNuMuCCoth
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
  //kmNuMuNCEL,            
  //kmNuMuNCMEC,           
    kmNuMuNC1piC,          
    kmNuMuNC1pi0,          
  //kmNuMuNC2piC,          
  //kmNuMuNC2pi0,          
  //kmNuMuNCpiCpi0,        
    kmNuMuNCcoh,           
    kmNuMuNCoth,           
    kmNuMuBarCCQE,         
    kmNuMuBarCCMEC,        
    kmNuMuBarCC1piC,       
    kmNuMuBarCC1pi0,       
    kmNuMuBarCC2piC,       
    kmNuMuBarCC2pi0,       
    kmNuMuBarCCpiCpi0,     
    kmNuMuBarCCcoh,        
    kmNuMuBarCCoth,        
  //kmNuMuBarNCEL,         
  //kmNuMuBarNCMEC,        
    kmNuMuBarNC1piC,       
    kmNuMuBarNC1pi0,       
  //kmNuMuBarNC2piC,       
  //kmNuMuBarNC2pi0,       
  //kmNuMuBarNCpiCpi0,     
    kmNuMuBarNCcoh,        
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
    kmNuENCoth,            
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
    kmNuEBarNCoth          
  },

  // sample: ksNuECC
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
  //kmNuMuNCEL,            
  //kmNuMuNCMEC,           
    kmNuMuNC1piC,          
    kmNuMuNC1pi0,          
  //kmNuMuNC2piC,          
  //kmNuMuNC2pi0,          
  //kmNuMuNCpiCpi0,        
    kmNuMuNCcoh,           
    kmNuMuNCoth,           
    kmNuMuBarCCQE,         
    kmNuMuBarCCMEC,        
    kmNuMuBarCC1piC,       
    kmNuMuBarCC1pi0,       
    kmNuMuBarCC2piC,       
    kmNuMuBarCC2pi0,       
    kmNuMuBarCCpiCpi0,     
    kmNuMuBarCCcoh,        
    kmNuMuBarCCoth,        
  //kmNuMuBarNCEL,         
  //kmNuMuBarNCMEC,        
    kmNuMuBarNC1piC,       
    kmNuMuBarNC1pi0,       
  //kmNuMuBarNC2piC,       
  //kmNuMuBarNC2pi0,       
  //kmNuMuBarNCpiCpi0,     
    kmNuMuBarNCcoh,        
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
    kmNuENCoth,            
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
    kmNuEBarNCoth          
  },

  // sample: ksNuMuCCWSgn
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
  //kmNuMuNCEL,            
  //kmNuMuNCMEC,           
    kmNuMuNC1piC,          
    kmNuMuNC1pi0,          
  //kmNuMuNC2piC,          
  //kmNuMuNC2pi0,          
  //kmNuMuNCpiCpi0,        
    kmNuMuNCcoh,           
    kmNuMuNCoth,           
    kmNuMuBarCCQE,         
    kmNuMuBarCCMEC,        
    kmNuMuBarCC1piC,       
    kmNuMuBarCC1pi0,       
    kmNuMuBarCC2piC,       
    kmNuMuBarCC2pi0,       
    kmNuMuBarCCpiCpi0,     
    kmNuMuBarCCcoh,        
    kmNuMuBarCCoth,        
  //kmNuMuBarNCEL,         
  //kmNuMuBarNCMEC,        
    kmNuMuBarNC1piC,       
    kmNuMuBarNC1pi0,       
  //kmNuMuBarNC2piC,       
  //kmNuMuBarNC2pi0,       
  //kmNuMuBarNCpiCpi0,     
    kmNuMuBarNCcoh,        
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
    kmNuENCoth,            
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
    kmNuEBarNCoth          
  },

  // sample: ksNC
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
  //kmNuMuNCEL,            
  //kmNuMuNCMEC,           
    kmNuMuNC1piC,          
    kmNuMuNC1pi0,          
  //kmNuMuNC2piC,          
  //kmNuMuNC2pi0,          
  //kmNuMuNCpiCpi0,        
    kmNuMuNCcoh,           
    kmNuMuNCoth,           
    kmNuMuBarCCQE,         
    kmNuMuBarCCMEC,        
    kmNuMuBarCC1piC,       
    kmNuMuBarCC1pi0,       
    kmNuMuBarCC2piC,       
    kmNuMuBarCC2pi0,       
    kmNuMuBarCCpiCpi0,     
    kmNuMuBarCCcoh,        
    kmNuMuBarCCoth,        
  //kmNuMuBarNCEL,         
  //kmNuMuBarNCMEC,        
    kmNuMuBarNC1piC,       
    kmNuMuBarNC1pi0,       
  //kmNuMuBarNC2piC,       
  //kmNuMuBarNC2pi0,       
  //kmNuMuBarNCpiCpi0,     
    kmNuMuBarNCcoh,        
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
    kmNuENCoth,            
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
    kmNuEBarNCoth          
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
    // sample: ksNuMuCC1trkQE
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
    // sample: ksNuMuCC2trkQE
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
    // sample: ksNuMuCCWSgn
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
    // sample: ksNuMuCC1trkQE
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
    // sample: ksNuMuCC2trkQE
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
    // sample: ksNuMuCCWSgn
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
    // sample: ksNuMuCC1trkQE
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
    // sample: ksNuMuCC2trkQE
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
    // sample: ksNuMuCCWSgn
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
    // sample: ksNuMuCC1trkQE
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
    // sample: ksNuMuCC2trkQE
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
    // sample: ksNuMuCCWSgn
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
    // sample: ksNuMuCC1trkQE
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
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth           
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth        
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
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
      kmcNC           // kmNuEBarNCoth          
    },

    // sample: ksNuMuCC2trkQE
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
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth           
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth        
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
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
      kmcNC           // kmNuEBarNCoth          
    },

    // sample: ksNuMuCC1piC
    {
      kmcNuMuCCQEMEC, // kmNuMuCCQE            
      kmcNuMuCCQEMEC, // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCoth           
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth           
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth        
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
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
      kmcNC           // kmNuEBarNCoth          
    },

    // sample: ksNuMuCC1pi0
    {
      kmcNuMuCCQEMEC, // kmNuMuCCQE            
      kmcNuMuCCQEMEC, // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCoth           
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth           
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth        
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
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
      kmcNC           // kmNuEBarNCoth          
    },

    // sample: ksNuMuCC1piC1pi0
    {
      kmcNuMuCCQEMEC, // kmNuMuCCQE            
      kmcNuMuCCQEMEC, // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCoth           
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth           
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth        
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
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
      kmcNC           // kmNuEBarNCoth          
    },

    // sample: ksNuMuCCoth
    {
      kmcNuMuCCQEMEC, // kmNuMuCCQE            
      kmcNuMuCCQEMEC, // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCoth           
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth           
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth        
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
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
      kmcNC           // kmNuEBarNCoth          
    },

    // sample: ksNuECC
    {
      kmcNuMuCC,      // kmNuMuCCQE            
      kmcNuMuCC,       // kmNuMuCCMEC           
      kmcNuMuCC,      // kmNuMuCC1piC          
      kmcNuMuCC,      // kmNuMuCC1pi0          
      kmcNuMuCC,      // kmNuMuCC2piC          
      kmcNuMuCC,      // kmNuMuCC2pi0          
      kmcNuMuCC,      // kmNuMuCCpiCpi0        
      kmcNuMuCC,      // kmNuMuCCcoh           
      kmcNuMuCC,      // kmNuMuCCoth           
    //kmcNCoth,       // kmNuMuNCEL            
    //kmcNCoth,       // kmNuMuNCMEC           
      kmcNCoth,       // kmNuMuNC1piC          
      kmcNC1pi0,      // kmNuMuNC1pi0          
    //kmcNCoth,       // kmNuMuNC2piC          
    //kmcNCoth,       // kmNuMuNC2pi0          
    //kmcNCoth,       // kmNuMuNCpiCpi0        
      kmcNCoth,       // kmNuMuNCcoh           
      kmcNCoth,       // kmNuMuNCoth           
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth        
    //kmcNCoth,       // kmNuMuBarNCEL         
    //kmcNothC,       // kmNuMuBarNCMEC        
      kmcNCoth,       // kmNuMuBarNC1piC       
      kmcNC1pi0,      // kmNuMuBarNC1pi0       
    //kmcNCoth,       // kmNuMuBarNC2piC       
    //kmcNCoth,       // kmNuMuBarNC2pi0       
    //kmcNCoth,       // kmNuMuBarNCpiCpi0     
      kmcNCoth,       // kmNuMuBarNCcoh        
      kmcNCoth,       // kmNuMuBarNCoth        
      kmcNuECC,       // kmNuECCQE             
      kmcNuECC,       // kmNuECCMEC            
      kmcNuECC,       // kmNuECC1piC           
      kmcNuECC,       // kmNuECC1pi0           
      kmcNuECC,       // kmNuECC2piC           
      kmcNuECC,       // kmNuECC2pi0           
      kmcNuECC,       // kmNuECCpiCpi0         
      kmcNuECC,       // kmNuECCcoh            
      kmcNuECC,       // kmNuECCoth            
    //kmcNCoth,       // kmNuENCEL             
    //kmcNCoth,       // kmNuENCMEC           
      kmcNCoth,       // kmNuENC1piC           
      kmcNC1pi0,      // kmNuENC1pi0           
    //kmcNCoth,       // kmNuENC2piC           
    //kmcNCoth,       // kmNuENC2pi0           
    //kmcNCoth,       // kmNuENCpiCpi0         
      kmcNCoth,       // kmNuENCcoh            
      kmcNCoth,       // kmNuENCoth            
      kmcNuEBarCC,    // kmNuEBarCCQE          
      kmcNuEBarCC,    // kmNuEBarCCMEC         
      kmcNuEBarCC,    // kmNuEBarCC1piC        
      kmcNuEBarCC,    // kmNuEBarCC1pi0        
      kmcNuEBarCC,    // kmNuEBarCC2piC        
      kmcNuEBarCC,    // kmNuEBarCC2pi0        
      kmcNuEBarCC,    // kmNuEBarCCpiCpi0      
      kmcNuEBarCC,    // kmNuEBarCCcoh         
      kmcNuEBarCC,    // kmNuEBarCCoth         
    //kmcNCoth,       // kmNuEBarNCEL          
    //kmcNCoth,       // kmNuEBarNCMEC         
      kmcNCoth,       // kmNuEBarNC1piC        
      kmcNC1pi0,      // kmNuEBarNC1pi0        
    //kmcNCoth,       // kmNuEBarNC2piC        
    //kmcNCoth,       // kmNuEBarNC2pi0        
    //kmcNCoth,       // kmNuEBarNCpiCpi0      
      kmcNCoth,       // kmNuEBarNCcoh         
      kmcNCoth        // kmNuEBarNCoth          
    },

    // sample: ksNuMuCCWSgn
    {
      kmcNuMuCC,           // kmNuMuCCQE            
      kmcNuMuCC,           // kmNuMuCCMEC           
      kmcNuMuCC,           // kmNuMuCC1piC          
      kmcNuMuCC,           // kmNuMuCC1pi0          
      kmcNuMuCC,           // kmNuMuCC2piC          
      kmcNuMuCC,           // kmNuMuCC2pi0          
      kmcNuMuCC,           // kmNuMuCCpiCpi0        
      kmcNuMuCC,           // kmNuMuCCcoh           
      kmcNuMuCC,           // kmNuMuCCoth           
    //kmcNC,               // kmNuMuNCEL            
    //kmcNC,               // kmNuMuNCMEC           
      kmcNC,               // kmNuMuNC1piC          
      kmcNC,               // kmNuMuNC1pi0          
    //kmcNC,               // kmNuMuNC2piC          
    //kmcNC,               // kmNuMuNC2pi0          
    //kmcNC,               // kmNuMuNCpiCpi0        
      kmcNC,               // kmNuMuNCcoh           
      kmcNC,               // kmNuMuNCoth           
      kmcNuMuBarCCQEMEC,   // kmNuMuBarCCQE         
      kmcNuMuBarCCQEMEC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC1pi,     // kmNuMuBarCC1piC       
      kmcNuMuBarCC1pi,     // kmNuMuBarCC1pi0       
      kmcNuMuBarCC2pi,     // kmNuMuBarCC2piC       
      kmcNuMuBarCC2pi,     // kmNuMuBarCC2pi0       
      kmcNuMuBarCC2pi,     // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCCoth,     // kmNuMuBarCCcoh        
      kmcNuMuBarCCoth,     // kmNuMuBarCCoth        
    //kmcNC,               // kmNuMuBarNCEL         
    //kmcNC,               // kmNuMuBarNCMEC        
      kmcNC,               // kmNuMuBarNC1piC       
      kmcNC,               // kmNuMuBarNC1pi0       
    //kmcNC,               // kmNuMuBarNC2piC       
    //kmcNC,               // kmNuMuBarNC2pi0       
    //kmcNC,               // kmNuMuBarNCpiCpi0     
      kmcNC,               // kmNuMuBarNCcoh        
      kmcNC,               // kmNuMuBarNCoth        
      kmcNuENuEBarCC,      // kmNuECCQE             
      kmcNuENuEBarCC,      // kmNuECCMEC            
      kmcNuENuEBarCC,      // kmNuECC1piC           
      kmcNuENuEBarCC,      // kmNuECC1pi0           
      kmcNuENuEBarCC,      // kmNuECC2piC           
      kmcNuENuEBarCC,      // kmNuECC2pi0           
      kmcNuENuEBarCC,      // kmNuECCpiCpi0         
      kmcNuENuEBarCC,      // kmNuECCcoh            
      kmcNuENuEBarCC,      // kmNuECCoth            
    //kmcNC,               // kmNuENCEL             
    //kmcNC,               // kmNuENCMEC           
      kmcNC,               // kmNuENC1piC           
      kmcNC,               // kmNuENC1pi0           
    //kmcNC,               // kmNuENC2piC           
    //kmcNC,               // kmNuENC2pi0           
    //kmcNC,               // kmNuENCpiCpi0         
      kmcNC,               // kmNuENCcoh            
      kmcNC,               // kmNuENCoth            
      kmcNuENuEBarCC,      // kmNuEBarCCQE          
      kmcNuENuEBarCC,      // kmNuEBarCCMEC         
      kmcNuENuEBarCC,      // kmNuEBarCC1piC        
      kmcNuENuEBarCC,      // kmNuEBarCC1pi0        
      kmcNuENuEBarCC,      // kmNuEBarCC2piC        
      kmcNuENuEBarCC,      // kmNuEBarCC2pi0        
      kmcNuENuEBarCC,      // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC,      // kmNuEBarCCcoh         
      kmcNuENuEBarCC,      // kmNuEBarCCoth         
    //kmcNC,               // kmNuEBarNCEL          
    //kmcNC,               // kmNuEBarNCMEC         
      kmcNC,               // kmNuEBarNC1piC        
      kmcNC,               // kmNuEBarNC1pi0        
    //kmcNC,               // kmNuEBarNC2piC        
    //kmcNC,               // kmNuEBarNC2pi0        
    //kmcNC,               // kmNuEBarNCpiCpi0      
      kmcNC,               // kmNuEBarNCcoh         
      kmcNC                // kmNuEBarNCoth          
    },

    // sample: ksNC
    {
      kmcNuMuCC,      // kmNuMuCCQE            
      kmcNuMuCC,      // kmNuMuCCMEC           
      kmcNuMuCC,      // kmNuMuCC1piC          
      kmcNuMuCC,      // kmNuMuCC1pi0          
      kmcNuMuCC,      // kmNuMuCC2piC          
      kmcNuMuCC,      // kmNuMuCC2pi0          
      kmcNuMuCC,      // kmNuMuCCpiCpi0        
      kmcNuMuCC,      // kmNuMuCCcoh           
      kmcNuMuCC,      // kmNuMuCCoth           
    //kmcNCoth,       // kmNuMuNCEL            
    //kmcNCoth,       // kmNuMuNCMEC           
      kmcNCoth,       // kmNuMuNC1piC          
      kmcNC1pi0,      // kmNuMuNC1pi0          
    //kmcNCoth,       // kmNuMuNC2piC          
    //kmcNCoth,       // kmNuMuNC2pi0          
    //kmcNCoth,       // kmNuMuNCpiCpi0        
      kmcNCoth,       // kmNuMuNCcoh           
      kmcNCoth,       // kmNuMuNCoth           
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth        
    //kmcNCoth,       // kmNuMuBarNCEL         
    //kmcNothC,       // kmNuMuBarNCMEC        
      kmcNCoth,       // kmNuMuBarNC1piC       
      kmcNC1pi0,      // kmNuMuBarNC1pi0       
    //kmcNCoth,       // kmNuMuBarNC2piC       
    //kmcNCoth,       // kmNuMuBarNC2pi0       
    //kmcNCoth,       // kmNuMuBarNCpiCpi0     
      kmcNCoth,       // kmNuMuBarNCcoh        
      kmcNCoth,       // kmNuMuBarNCoth        
      kmcNuECC,       // kmNuECCQE             
      kmcNuECC,       // kmNuECCMEC            
      kmcNuECC,       // kmNuECC1piC           
      kmcNuECC,       // kmNuECC1pi0           
      kmcNuECC,       // kmNuECC2piC           
      kmcNuECC,       // kmNuECC2pi0           
      kmcNuECC,       // kmNuECCpiCpi0         
      kmcNuECC,       // kmNuECCcoh            
      kmcNuECC,       // kmNuECCoth            
    //kmcNCoth,       // kmNuENCEL             
    //kmcNCoth,       // kmNuENCMEC           
      kmcNCoth,       // kmNuENC1piC           
      kmcNC1pi0,      // kmNuENC1pi0           
    //kmcNCoth,       // kmNuENC2piC           
    //kmcNCoth,       // kmNuENC2pi0           
    //kmcNCoth,       // kmNuENCpiCpi0         
      kmcNCoth,       // kmNuENCcoh            
      kmcNCoth,       // kmNuENCoth            
      kmcNuEBarCC,    // kmNuEBarCCQE          
      kmcNuEBarCC,    // kmNuEBarCCMEC         
      kmcNuEBarCC,    // kmNuEBarCC1piC        
      kmcNuEBarCC,    // kmNuEBarCC1pi0        
      kmcNuEBarCC,    // kmNuEBarCC2piC        
      kmcNuEBarCC,    // kmNuEBarCC2pi0        
      kmcNuEBarCC,    // kmNuEBarCCpiCpi0      
      kmcNuEBarCC,    // kmNuEBarCCcoh         
      kmcNuEBarCC,    // kmNuEBarCCoth         
    //kmcNCoth,       // kmNuEBarNCEL          
    //kmcNCoth,       // kmNuEBarNCMEC         
      kmcNCoth,       // kmNuEBarNC1piC        
      kmcNC1pi0,      // kmNuEBarNC1pi0        
    //kmcNCoth,       // kmNuEBarNC2piC        
    //kmcNCoth,       // kmNuEBarNC2pi0        
    //kmcNCoth,       // kmNuEBarNCpiCpi0      
      kmcNCoth,       // kmNuEBarNCcoh         
      kmcNCoth        // kmNuEBarNCoth          
    }

  }, // end of FHC

  // RHC
  {
    // sample: ksNuMuCC1trkQE
    {
      kmcNuMuCC,           // kmNuMuCCQE            
      kmcNuMuCC,           // kmNuMuCCMEC           
      kmcNuMuCC,           // kmNuMuCC1piC          
      kmcNuMuCC,           // kmNuMuCC1pi0          
      kmcNuMuCC,           // kmNuMuCC2piC          
      kmcNuMuCC,           // kmNuMuCC2pi0          
      kmcNuMuCC,           // kmNuMuCCpiCpi0        
      kmcNuMuCC,           // kmNuMuCCcoh           
      kmcNuMuCC,           // kmNuMuCCoth           
    //kmcNC,               // kmNuMuNCEL            
    //kmcNC,               // kmNuMuNCMEC           
      kmcNC,               // kmNuMuNC1piC          
      kmcNC,               // kmNuMuNC1pi0          
    //kmcNC,               // kmNuMuNC2piC          
    //kmcNC,               // kmNuMuNC2pi0          
    //kmcNC,               // kmNuMuNCpiCpi0        
      kmcNC,               // kmNuMuNCcoh           
      kmcNC,               // kmNuMuNCoth           
      kmcNuMuBarCCQE,      // kmNuMuBarCCQE         
      kmcNuMuBarCCMEC,     // kmNuMuBarCCMEC        
      kmcNuMuBarCC1pi,     // kmNuMuBarCC1piC       
      kmcNuMuBarCC1pi,     // kmNuMuBarCC1pi0       
      kmcNuMuBarCC2pi,     // kmNuMuBarCC2piC       
      kmcNuMuBarCC2pi,     // kmNuMuBarCC2pi0       
      kmcNuMuBarCC2pi,     // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCCoth,     // kmNuMuBarCCcoh        
      kmcNuMuBarCCoth,     // kmNuMuBarCCoth        
    //kmcNC,               // kmNuMuBarNCEL         
    //kmcNC,               // kmNuMuBarNCMEC        
      kmcNC,               // kmNuMuBarNC1piC       
      kmcNC,               // kmNuMuBarNC1pi0       
    //kmcNC,               // kmNuMuBarNC2piC       
    //kmcNC,               // kmNuMuBarNC2pi0       
    //kmcNC,               // kmNuMuBarNCpiCpi0     
      kmcNC,               // kmNuMuBarNCcoh        
      kmcNC,               // kmNuMuBarNCoth        
      kmcNuENuEBarCC,      // kmNuECCQE             
      kmcNuENuEBarCC,      // kmNuECCMEC            
      kmcNuENuEBarCC,      // kmNuECC1piC           
      kmcNuENuEBarCC,      // kmNuECC1pi0           
      kmcNuENuEBarCC,      // kmNuECC2piC           
      kmcNuENuEBarCC,      // kmNuECC2pi0           
      kmcNuENuEBarCC,      // kmNuECCpiCpi0         
      kmcNuENuEBarCC,      // kmNuECCcoh            
      kmcNuENuEBarCC,      // kmNuECCoth            
    //kmcNC,               // kmNuENCEL             
    //kmcNC,               // kmNuENCMEC           
      kmcNC,               // kmNuENC1piC           
      kmcNC,               // kmNuENC1pi0           
    //kmcNC,               // kmNuENC2piC           
    //kmcNC,               // kmNuENC2pi0           
    //kmcNC,               // kmNuENCpiCpi0         
      kmcNC,               // kmNuENCcoh            
      kmcNC,               // kmNuENCoth            
      kmcNuENuEBarCC,      // kmNuEBarCCQE          
      kmcNuENuEBarCC,      // kmNuEBarCCMEC         
      kmcNuENuEBarCC,      // kmNuEBarCC1piC        
      kmcNuENuEBarCC,      // kmNuEBarCC1pi0        
      kmcNuENuEBarCC,      // kmNuEBarCC2piC        
      kmcNuENuEBarCC,      // kmNuEBarCC2pi0        
      kmcNuENuEBarCC,      // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC,      // kmNuEBarCCcoh         
      kmcNuENuEBarCC,      // kmNuEBarCCoth         
    //kmcNC,               // kmNuEBarNCEL          
    //kmcNC,               // kmNuEBarNCMEC         
      kmcNC,               // kmNuEBarNC1piC        
      kmcNC,               // kmNuEBarNC1pi0        
    //kmcNC,               // kmNuEBarNC2piC        
    //kmcNC,               // kmNuEBarNC2pi0        
    //kmcNC,               // kmNuEBarNCpiCpi0      
      kmcNC,               // kmNuEBarNCcoh         
      kmcNC                // kmNuEBarNCoth          
    },

    // sample: ksNuMuCC2trkQE
    {
      kmcNuMuCC,           // kmNuMuCCQE            
      kmcNuMuCC,           // kmNuMuCCMEC           
      kmcNuMuCC,           // kmNuMuCC1piC          
      kmcNuMuCC,           // kmNuMuCC1pi0          
      kmcNuMuCC,           // kmNuMuCC2piC          
      kmcNuMuCC,           // kmNuMuCC2pi0          
      kmcNuMuCC,           // kmNuMuCCpiCpi0        
      kmcNuMuCC,           // kmNuMuCCcoh           
      kmcNuMuCC,           // kmNuMuCCoth           
    //kmcNC,               // kmNuMuNCEL            
    //kmcNC,               // kmNuMuNCMEC           
      kmcNC,               // kmNuMuNC1piC          
      kmcNC,               // kmNuMuNC1pi0          
    //kmcNC,               // kmNuMuNC2piC          
    //kmcNC,               // kmNuMuNC2pi0          
    //kmcNC,               // kmNuMuNCpiCpi0        
      kmcNC,               // kmNuMuNCcoh           
      kmcNC,               // kmNuMuNCoth           
      kmcNuMuBarCCQE,      // kmNuMuBarCCQE         
      kmcNuMuBarCCMEC,     // kmNuMuBarCCMEC        
      kmcNuMuBarCC1pi,     // kmNuMuBarCC1piC       
      kmcNuMuBarCC1pi,     // kmNuMuBarCC1pi0       
      kmcNuMuBarCC2pi,     // kmNuMuBarCC2piC       
      kmcNuMuBarCC2pi,     // kmNuMuBarCC2pi0       
      kmcNuMuBarCC2pi,     // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCCoth,     // kmNuMuBarCCcoh        
      kmcNuMuBarCCoth,     // kmNuMuBarCCoth        
    //kmcNC,               // kmNuMuBarNCEL         
    //kmcNC,               // kmNuMuBarNCMEC        
      kmcNC,               // kmNuMuBarNC1piC       
      kmcNC,               // kmNuMuBarNC1pi0       
    //kmcNC,               // kmNuMuBarNC2piC       
    //kmcNC,               // kmNuMuBarNC2pi0       
    //kmcNC,               // kmNuMuBarNCpiCpi0     
      kmcNC,               // kmNuMuBarNCcoh        
      kmcNC,               // kmNuMuBarNCoth        
      kmcNuENuEBarCC,      // kmNuECCQE             
      kmcNuENuEBarCC,      // kmNuECCMEC            
      kmcNuENuEBarCC,      // kmNuECC1piC           
      kmcNuENuEBarCC,      // kmNuECC1pi0           
      kmcNuENuEBarCC,      // kmNuECC2piC           
      kmcNuENuEBarCC,      // kmNuECC2pi0           
      kmcNuENuEBarCC,      // kmNuECCpiCpi0         
      kmcNuENuEBarCC,      // kmNuECCcoh            
      kmcNuENuEBarCC,      // kmNuECCoth            
    //kmcNC,               // kmNuENCEL             
    //kmcNC,               // kmNuENCMEC           
      kmcNC,               // kmNuENC1piC           
      kmcNC,               // kmNuENC1pi0           
    //kmcNC,               // kmNuENC2piC           
    //kmcNC,               // kmNuENC2pi0           
    //kmcNC,               // kmNuENCpiCpi0         
      kmcNC,               // kmNuENCcoh            
      kmcNC,               // kmNuENCoth            
      kmcNuENuEBarCC,      // kmNuEBarCCQE          
      kmcNuENuEBarCC,      // kmNuEBarCCMEC         
      kmcNuENuEBarCC,      // kmNuEBarCC1piC        
      kmcNuENuEBarCC,      // kmNuEBarCC1pi0        
      kmcNuENuEBarCC,      // kmNuEBarCC2piC        
      kmcNuENuEBarCC,      // kmNuEBarCC2pi0        
      kmcNuENuEBarCC,      // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC,      // kmNuEBarCCcoh         
      kmcNuENuEBarCC,      // kmNuEBarCCoth         
    //kmcNC,               // kmNuEBarNCEL          
    //kmcNC,               // kmNuEBarNCMEC         
      kmcNC,               // kmNuEBarNC1piC        
      kmcNC,               // kmNuEBarNC1pi0        
    //kmcNC,               // kmNuEBarNC2piC        
    //kmcNC,               // kmNuEBarNC2pi0        
    //kmcNC,               // kmNuEBarNCpiCpi0      
      kmcNC,               // kmNuEBarNCcoh         
      kmcNC                // kmNuEBarNCoth          
    },

    // sample: ksNuMuCC1piC
    {
      kmcNuMuCC,           // kmNuMuCCQE            
      kmcNuMuCC,           // kmNuMuCCMEC           
      kmcNuMuCC,           // kmNuMuCC1piC          
      kmcNuMuCC,           // kmNuMuCC1pi0          
      kmcNuMuCC,           // kmNuMuCC2piC          
      kmcNuMuCC,           // kmNuMuCC2pi0          
      kmcNuMuCC,           // kmNuMuCCpiCpi0        
      kmcNuMuCC,           // kmNuMuCCcoh           
      kmcNuMuCC,           // kmNuMuCCoth           
    //kmcNC,               // kmNuMuNCEL            
    //kmcNC,               // kmNuMuNCMEC           
      kmcNC,               // kmNuMuNC1piC          
      kmcNC,               // kmNuMuNC1pi0          
    //kmcNC,               // kmNuMuNC2piC          
    //kmcNC,               // kmNuMuNC2pi0          
    //kmcNC,               // kmNuMuNCpiCpi0        
      kmcNC,               // kmNuMuNCcoh           
      kmcNC,               // kmNuMuNCoth           
      kmcNuMuBarCCQEMEC,   // kmNuMuBarCCQE         
      kmcNuMuBarCCQEMEC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC1pi,     // kmNuMuBarCC1piC       
      kmcNuMuBarCC1pi,     // kmNuMuBarCC1pi0       
      kmcNuMuBarCC2pi,     // kmNuMuBarCC2piC       
      kmcNuMuBarCC2pi,     // kmNuMuBarCC2pi0       
      kmcNuMuBarCC2pi,     // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCCoth,     // kmNuMuBarCCcoh        
      kmcNuMuBarCCoth,     // kmNuMuBarCCoth        
    //kmcNC,               // kmNuMuBarNCEL         
    //kmcNC,               // kmNuMuBarNCMEC        
      kmcNC,               // kmNuMuBarNC1piC       
      kmcNC,               // kmNuMuBarNC1pi0       
    //kmcNC,               // kmNuMuBarNC2piC       
    //kmcNC,               // kmNuMuBarNC2pi0       
    //kmcNC,               // kmNuMuBarNCpiCpi0     
      kmcNC,               // kmNuMuBarNCcoh        
      kmcNC,               // kmNuMuBarNCoth        
      kmcNuENuEBarCC,      // kmNuECCQE             
      kmcNuENuEBarCC,      // kmNuECCMEC            
      kmcNuENuEBarCC,      // kmNuECC1piC           
      kmcNuENuEBarCC,      // kmNuECC1pi0           
      kmcNuENuEBarCC,      // kmNuECC2piC           
      kmcNuENuEBarCC,      // kmNuECC2pi0           
      kmcNuENuEBarCC,      // kmNuECCpiCpi0         
      kmcNuENuEBarCC,      // kmNuECCcoh            
      kmcNuENuEBarCC,      // kmNuECCoth            
    //kmcNC,               // kmNuENCEL             
    //kmcNC,               // kmNuENCMEC           
      kmcNC,               // kmNuENC1piC           
      kmcNC,               // kmNuENC1pi0           
    //kmcNC,               // kmNuENC2piC           
    //kmcNC,               // kmNuENC2pi0           
    //kmcNC,               // kmNuENCpiCpi0         
      kmcNC,               // kmNuENCcoh            
      kmcNC,               // kmNuENCoth            
      kmcNuENuEBarCC,      // kmNuEBarCCQE          
      kmcNuENuEBarCC,      // kmNuEBarCCMEC         
      kmcNuENuEBarCC,      // kmNuEBarCC1piC        
      kmcNuENuEBarCC,      // kmNuEBarCC1pi0        
      kmcNuENuEBarCC,      // kmNuEBarCC2piC        
      kmcNuENuEBarCC,      // kmNuEBarCC2pi0        
      kmcNuENuEBarCC,      // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC,      // kmNuEBarCCcoh         
      kmcNuENuEBarCC,      // kmNuEBarCCoth         
    //kmcNC,               // kmNuEBarNCEL          
    //kmcNC,               // kmNuEBarNCMEC         
      kmcNC,               // kmNuEBarNC1piC        
      kmcNC,               // kmNuEBarNC1pi0        
    //kmcNC,               // kmNuEBarNC2piC        
    //kmcNC,               // kmNuEBarNC2pi0        
    //kmcNC,               // kmNuEBarNCpiCpi0      
      kmcNC,               // kmNuEBarNCcoh         
      kmcNC                // kmNuEBarNCoth          
    },

    // sample: ksNuMuCC1pi0
    {
      kmcNuMuCC,           // kmNuMuCCQE            
      kmcNuMuCC,           // kmNuMuCCMEC           
      kmcNuMuCC,           // kmNuMuCC1piC          
      kmcNuMuCC,           // kmNuMuCC1pi0          
      kmcNuMuCC,           // kmNuMuCC2piC          
      kmcNuMuCC,           // kmNuMuCC2pi0          
      kmcNuMuCC,           // kmNuMuCCpiCpi0        
      kmcNuMuCC,           // kmNuMuCCcoh           
      kmcNuMuCC,           // kmNuMuCCoth           
    //kmcNC,               // kmNuMuNCEL            
    //kmcNC,               // kmNuMuNCMEC           
      kmcNC,               // kmNuMuNC1piC          
      kmcNC,               // kmNuMuNC1pi0          
    //kmcNC,               // kmNuMuNC2piC          
    //kmcNC,               // kmNuMuNC2pi0          
    //kmcNC,               // kmNuMuNCpiCpi0        
      kmcNC,               // kmNuMuNCcoh           
      kmcNC,               // kmNuMuNCoth           
      kmcNuMuBarCCQEMEC,   // kmNuMuBarCCQE         
      kmcNuMuBarCCQEMEC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC1pi,     // kmNuMuBarCC1piC       
      kmcNuMuBarCC1pi,     // kmNuMuBarCC1pi0       
      kmcNuMuBarCC2pi,     // kmNuMuBarCC2piC       
      kmcNuMuBarCC2pi,     // kmNuMuBarCC2pi0       
      kmcNuMuBarCC2pi,     // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCCoth,     // kmNuMuBarCCcoh        
      kmcNuMuBarCCoth,     // kmNuMuBarCCoth        
    //kmcNC,               // kmNuMuBarNCEL         
    //kmcNC,               // kmNuMuBarNCMEC        
      kmcNC,               // kmNuMuBarNC1piC       
      kmcNC,               // kmNuMuBarNC1pi0       
    //kmcNC,               // kmNuMuBarNC2piC       
    //kmcNC,               // kmNuMuBarNC2pi0       
    //kmcNC,               // kmNuMuBarNCpiCpi0     
      kmcNC,               // kmNuMuBarNCcoh        
      kmcNC,               // kmNuMuBarNCoth        
      kmcNuENuEBarCC,      // kmNuECCQE             
      kmcNuENuEBarCC,      // kmNuECCMEC            
      kmcNuENuEBarCC,      // kmNuECC1piC           
      kmcNuENuEBarCC,      // kmNuECC1pi0           
      kmcNuENuEBarCC,      // kmNuECC2piC           
      kmcNuENuEBarCC,      // kmNuECC2pi0           
      kmcNuENuEBarCC,      // kmNuECCpiCpi0         
      kmcNuENuEBarCC,      // kmNuECCcoh            
      kmcNuENuEBarCC,      // kmNuECCoth            
    //kmcNC,               // kmNuENCEL             
    //kmcNC,               // kmNuENCMEC           
      kmcNC,               // kmNuENC1piC           
      kmcNC,               // kmNuENC1pi0           
    //kmcNC,               // kmNuENC2piC           
    //kmcNC,               // kmNuENC2pi0           
    //kmcNC,               // kmNuENCpiCpi0         
      kmcNC,               // kmNuENCcoh            
      kmcNC,               // kmNuENCoth            
      kmcNuENuEBarCC,      // kmNuEBarCCQE          
      kmcNuENuEBarCC,      // kmNuEBarCCMEC         
      kmcNuENuEBarCC,      // kmNuEBarCC1piC        
      kmcNuENuEBarCC,      // kmNuEBarCC1pi0        
      kmcNuENuEBarCC,      // kmNuEBarCC2piC        
      kmcNuENuEBarCC,      // kmNuEBarCC2pi0        
      kmcNuENuEBarCC,      // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC,      // kmNuEBarCCcoh         
      kmcNuENuEBarCC,      // kmNuEBarCCoth         
    //kmcNC,               // kmNuEBarNCEL          
    //kmcNC,               // kmNuEBarNCMEC         
      kmcNC,               // kmNuEBarNC1piC        
      kmcNC,               // kmNuEBarNC1pi0        
    //kmcNC,               // kmNuEBarNC2piC        
    //kmcNC,               // kmNuEBarNC2pi0        
    //kmcNC,               // kmNuEBarNCpiCpi0      
      kmcNC,               // kmNuEBarNCcoh         
      kmcNC                // kmNuEBarNCoth          
    },

    // sample: ksNuMuCC1piC1pi0
    {
      kmcNuMuCC,           // kmNuMuCCQE            
      kmcNuMuCC,           // kmNuMuCCMEC           
      kmcNuMuCC,           // kmNuMuCC1piC          
      kmcNuMuCC,           // kmNuMuCC1pi0          
      kmcNuMuCC,           // kmNuMuCC2piC          
      kmcNuMuCC,           // kmNuMuCC2pi0          
      kmcNuMuCC,           // kmNuMuCCpiCpi0        
      kmcNuMuCC,           // kmNuMuCCcoh           
      kmcNuMuCC,           // kmNuMuCCoth           
    //kmcNC,               // kmNuMuNCEL            
    //kmcNC,               // kmNuMuNCMEC           
      kmcNC,               // kmNuMuNC1piC          
      kmcNC,               // kmNuMuNC1pi0          
    //kmcNC,               // kmNuMuNC2piC          
    //kmcNC,               // kmNuMuNC2pi0          
    //kmcNC,               // kmNuMuNCpiCpi0        
      kmcNC,               // kmNuMuNCcoh           
      kmcNC,               // kmNuMuNCoth           
      kmcNuMuBarCCQEMEC,   // kmNuMuBarCCQE         
      kmcNuMuBarCCQEMEC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC1pi,     // kmNuMuBarCC1piC       
      kmcNuMuBarCC1pi,     // kmNuMuBarCC1pi0       
      kmcNuMuBarCC2pi,     // kmNuMuBarCC2piC       
      kmcNuMuBarCC2pi,     // kmNuMuBarCC2pi0       
      kmcNuMuBarCC2pi,     // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCCoth,     // kmNuMuBarCCcoh        
      kmcNuMuBarCCoth,     // kmNuMuBarCCoth        
    //kmcNC,               // kmNuMuBarNCEL         
    //kmcNC,               // kmNuMuBarNCMEC        
      kmcNC,               // kmNuMuBarNC1piC       
      kmcNC,               // kmNuMuBarNC1pi0       
    //kmcNC,               // kmNuMuBarNC2piC       
    //kmcNC,               // kmNuMuBarNC2pi0       
    //kmcNC,               // kmNuMuBarNCpiCpi0     
      kmcNC,               // kmNuMuBarNCcoh        
      kmcNC,               // kmNuMuBarNCoth        
      kmcNuENuEBarCC,      // kmNuECCQE             
      kmcNuENuEBarCC,      // kmNuECCMEC            
      kmcNuENuEBarCC,      // kmNuECC1piC           
      kmcNuENuEBarCC,      // kmNuECC1pi0           
      kmcNuENuEBarCC,      // kmNuECC2piC           
      kmcNuENuEBarCC,      // kmNuECC2pi0           
      kmcNuENuEBarCC,      // kmNuECCpiCpi0         
      kmcNuENuEBarCC,      // kmNuECCcoh            
      kmcNuENuEBarCC,      // kmNuECCoth            
    //kmcNC,               // kmNuENCEL             
    //kmcNC,               // kmNuENCMEC           
      kmcNC,               // kmNuENC1piC           
      kmcNC,               // kmNuENC1pi0           
    //kmcNC,               // kmNuENC2piC           
    //kmcNC,               // kmNuENC2pi0           
    //kmcNC,               // kmNuENCpiCpi0         
      kmcNC,               // kmNuENCcoh            
      kmcNC,               // kmNuENCoth            
      kmcNuENuEBarCC,      // kmNuEBarCCQE          
      kmcNuENuEBarCC,      // kmNuEBarCCMEC         
      kmcNuENuEBarCC,      // kmNuEBarCC1piC        
      kmcNuENuEBarCC,      // kmNuEBarCC1pi0        
      kmcNuENuEBarCC,      // kmNuEBarCC2piC        
      kmcNuENuEBarCC,      // kmNuEBarCC2pi0        
      kmcNuENuEBarCC,      // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC,      // kmNuEBarCCcoh         
      kmcNuENuEBarCC,      // kmNuEBarCCoth         
    //kmcNC,               // kmNuEBarNCEL          
    //kmcNC,               // kmNuEBarNCMEC         
      kmcNC,               // kmNuEBarNC1piC        
      kmcNC,               // kmNuEBarNC1pi0        
    //kmcNC,               // kmNuEBarNC2piC        
    //kmcNC,               // kmNuEBarNC2pi0        
    //kmcNC,               // kmNuEBarNCpiCpi0      
      kmcNC,               // kmNuEBarNCcoh         
      kmcNC                // kmNuEBarNCoth          
    },

    // sample: ksNuMuCCoth
    {
      kmcNuMuCC,           // kmNuMuCCQE            
      kmcNuMuCC,           // kmNuMuCCMEC           
      kmcNuMuCC,           // kmNuMuCC1piC          
      kmcNuMuCC,           // kmNuMuCC1pi0          
      kmcNuMuCC,           // kmNuMuCC2piC          
      kmcNuMuCC,           // kmNuMuCC2pi0          
      kmcNuMuCC,           // kmNuMuCCpiCpi0        
      kmcNuMuCC,           // kmNuMuCCcoh           
      kmcNuMuCC,           // kmNuMuCCoth           
    //kmcNC,               // kmNuMuNCEL            
    //kmcNC,               // kmNuMuNCMEC           
      kmcNC,               // kmNuMuNC1piC          
      kmcNC,               // kmNuMuNC1pi0          
    //kmcNC,               // kmNuMuNC2piC          
    //kmcNC,               // kmNuMuNC2pi0          
    //kmcNC,               // kmNuMuNCpiCpi0        
      kmcNC,               // kmNuMuNCcoh           
      kmcNC,               // kmNuMuNCoth           
      kmcNuMuBarCCQEMEC,   // kmNuMuBarCCQE         
      kmcNuMuBarCCQEMEC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC1pi,     // kmNuMuBarCC1piC       
      kmcNuMuBarCC1pi,     // kmNuMuBarCC1pi0       
      kmcNuMuBarCC2pi,     // kmNuMuBarCC2piC       
      kmcNuMuBarCC2pi,     // kmNuMuBarCC2pi0       
      kmcNuMuBarCC2pi,     // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCCoth,     // kmNuMuBarCCcoh        
      kmcNuMuBarCCoth,     // kmNuMuBarCCoth        
    //kmcNC,               // kmNuMuBarNCEL         
    //kmcNC,               // kmNuMuBarNCMEC        
      kmcNC,               // kmNuMuBarNC1piC       
      kmcNC,               // kmNuMuBarNC1pi0       
    //kmcNC,               // kmNuMuBarNC2piC       
    //kmcNC,               // kmNuMuBarNC2pi0       
    //kmcNC,               // kmNuMuBarNCpiCpi0     
      kmcNC,               // kmNuMuBarNCcoh        
      kmcNC,               // kmNuMuBarNCoth        
      kmcNuENuEBarCC,      // kmNuECCQE             
      kmcNuENuEBarCC,      // kmNuECCMEC            
      kmcNuENuEBarCC,      // kmNuECC1piC           
      kmcNuENuEBarCC,      // kmNuECC1pi0           
      kmcNuENuEBarCC,      // kmNuECC2piC           
      kmcNuENuEBarCC,      // kmNuECC2pi0           
      kmcNuENuEBarCC,      // kmNuECCpiCpi0         
      kmcNuENuEBarCC,      // kmNuECCcoh            
      kmcNuENuEBarCC,      // kmNuECCoth            
    //kmcNC,               // kmNuENCEL             
    //kmcNC,               // kmNuENCMEC           
      kmcNC,               // kmNuENC1piC           
      kmcNC,               // kmNuENC1pi0           
    //kmcNC,               // kmNuENC2piC           
    //kmcNC,               // kmNuENC2pi0           
    //kmcNC,               // kmNuENCpiCpi0         
      kmcNC,               // kmNuENCcoh            
      kmcNC,               // kmNuENCoth            
      kmcNuENuEBarCC,      // kmNuEBarCCQE          
      kmcNuENuEBarCC,      // kmNuEBarCCMEC         
      kmcNuENuEBarCC,      // kmNuEBarCC1piC        
      kmcNuENuEBarCC,      // kmNuEBarCC1pi0        
      kmcNuENuEBarCC,      // kmNuEBarCC2piC        
      kmcNuENuEBarCC,      // kmNuEBarCC2pi0        
      kmcNuENuEBarCC,      // kmNuEBarCCpiCpi0      
      kmcNuENuEBarCC,      // kmNuEBarCCcoh         
      kmcNuENuEBarCC,      // kmNuEBarCCoth         
    //kmcNC,               // kmNuEBarNCEL          
    //kmcNC,               // kmNuEBarNCMEC         
      kmcNC,               // kmNuEBarNC1piC        
      kmcNC,               // kmNuEBarNC1pi0        
    //kmcNC,               // kmNuEBarNC2piC        
    //kmcNC,               // kmNuEBarNC2pi0        
    //kmcNC,               // kmNuEBarNCpiCpi0      
      kmcNC,               // kmNuEBarNCcoh         
      kmcNC                // kmNuEBarNCoth          
    },

    // sample: ksNuECC
    {
      kmcNuMuCC,           // kmNuMuCCQE            
      kmcNuMuCC,           // kmNuMuCCMEC           
      kmcNuMuCC,           // kmNuMuCC1piC          
      kmcNuMuCC,           // kmNuMuCC1pi0          
      kmcNuMuCC,           // kmNuMuCC2piC          
      kmcNuMuCC,           // kmNuMuCC2pi0          
      kmcNuMuCC,           // kmNuMuCCpiCpi0        
      kmcNuMuCC,           // kmNuMuCCcoh           
      kmcNuMuCC,           // kmNuMuCCoth           
    //kmcNCoth,            // kmNuMuNCEL            
    //kmcNCoth,            // kmNuMuNCMEC           
      kmcNCoth,            // kmNuMuNC1piC          
      kmcNC1pi0,           // kmNuMuNC1pi0          
    //kmcNCoth,            // kmNuMuNC2piC          
    //kmcNCoth,            // kmNuMuNC2pi0          
    //kmcNCoth,            // kmNuMuNCpiCpi0        
      kmcNCoth,            // kmNuMuNCcoh           
      kmcNCoth,            // kmNuMuNCoth           
      kmcNuMuBarCC,        // kmNuMuBarCCQE         
      kmcNuMuBarCC,        // kmNuMuBarCCMEC        
      kmcNuMuBarCC,        // kmNuMuBarCC1piC       
      kmcNuMuBarCC,        // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,        // kmNuMuBarCC2piC       
      kmcNuMuBarCC,        // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,        // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,        // kmNuMuBarCCcoh        
      kmcNuMuBarCC,        // kmNuMuBarCCoth        
    //kmcNCoth,            // kmNuMuBarNCEL         
    //kmcNothC,            // kmNuMuBarNCMEC        
      kmcNCoth,            // kmNuMuBarNC1piC       
      kmcNC1pi0,           // kmNuMuBarNC1pi0       
    //kmcNCoth,            // kmNuMuBarNC2piC       
    //kmcNCoth,            // kmNuMuBarNC2pi0       
    //kmcNCoth,            // kmNuMuBarNCpiCpi0     
      kmcNCoth,            // kmNuMuBarNCcoh        
      kmcNCoth,            // kmNuMuBarNCoth        
      kmcNuECC,            // kmNuECCQE             
      kmcNuECC,            // kmNuECCMEC            
      kmcNuECC,            // kmNuECC1piC           
      kmcNuECC,            // kmNuECC1pi0           
      kmcNuECC,            // kmNuECC2piC           
      kmcNuECC,            // kmNuECC2pi0           
      kmcNuECC,            // kmNuECCpiCpi0         
      kmcNuECC,            // kmNuECCcoh            
      kmcNuECC,            // kmNuECCoth            
    //kmcNCoth,            // kmNuENCEL             
    //kmcNCoth,            // kmNuENCMEC           
      kmcNCoth,            // kmNuENC1piC           
      kmcNC1pi0,           // kmNuENC1pi0           
    //kmcNCoth,            // kmNuENC2piC           
    //kmcNCoth,            // kmNuENC2pi0           
    //kmcNCoth,            // kmNuENCpiCpi0         
      kmcNCoth,            // kmNuENCcoh            
      kmcNCoth,            // kmNuENCoth            
      kmcNuEBarCC,         // kmNuEBarCCQE          
      kmcNuEBarCC,         // kmNuEBarCCMEC         
      kmcNuEBarCC,         // kmNuEBarCC1piC        
      kmcNuEBarCC,         // kmNuEBarCC1pi0        
      kmcNuEBarCC,         // kmNuEBarCC2piC        
      kmcNuEBarCC,         // kmNuEBarCC2pi0        
      kmcNuEBarCC,         // kmNuEBarCCpiCpi0      
      kmcNuEBarCC,         // kmNuEBarCCcoh         
      kmcNuEBarCC,         // kmNuEBarCCoth         
    //kmcNCoth,            // kmNuEBarNCEL          
    //kmcNCoth,            // kmNuEBarNCMEC         
      kmcNCoth,            // kmNuEBarNC1piC        
      kmcNC1pi0,           // kmNuEBarNC1pi0        
    //kmcNCoth,            // kmNuEBarNC2piC        
    //kmcNCoth,            // kmNuEBarNC2pi0        
    //kmcNCoth,            // kmNuEBarNCpiCpi0      
      kmcNCoth,            // kmNuEBarNCcoh         
      kmcNCoth             // kmNuEBarNCoth          
    },

    // sample: ksNuMuCCWSgn
    {
      kmcNuMuCCQEMEC, // kmNuMuCCQE            
      kmcNuMuCCQEMEC, // kmNuMuCCMEC           
      kmcNuMuCC1pi,   // kmNuMuCC1piC          
      kmcNuMuCC1pi,   // kmNuMuCC1pi0          
      kmcNuMuCC2pi,   // kmNuMuCC2piC          
      kmcNuMuCC2pi,   // kmNuMuCC2pi0          
      kmcNuMuCC2pi,   // kmNuMuCCpiCpi0        
      kmcNuMuCCoth,   // kmNuMuCCcoh           
      kmcNuMuCCoth,   // kmNuMuCCoth           
    //kmcNC,          // kmNuMuNCEL            
    //kmcNC,          // kmNuMuNCMEC           
      kmcNC,          // kmNuMuNC1piC          
      kmcNC,          // kmNuMuNC1pi0          
    //kmcNC,          // kmNuMuNC2piC          
    //kmcNC,          // kmNuMuNC2pi0          
    //kmcNC,          // kmNuMuNCpiCpi0        
      kmcNC,          // kmNuMuNCcoh           
      kmcNC,          // kmNuMuNCoth           
      kmcNuMuBarCC,   // kmNuMuBarCCQE         
      kmcNuMuBarCC,   // kmNuMuBarCCMEC        
      kmcNuMuBarCC,   // kmNuMuBarCC1piC       
      kmcNuMuBarCC,   // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,   // kmNuMuBarCC2piC       
      kmcNuMuBarCC,   // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,   // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,   // kmNuMuBarCCcoh        
      kmcNuMuBarCC,   // kmNuMuBarCCoth        
    //kmcNC,          // kmNuMuBarNCEL         
    //kmcNC,          // kmNuMuBarNCMEC        
      kmcNC,          // kmNuMuBarNC1piC       
      kmcNC,          // kmNuMuBarNC1pi0       
    //kmcNC,          // kmNuMuBarNC2piC       
    //kmcNC,          // kmNuMuBarNC2pi0       
    //kmcNC,          // kmNuMuBarNCpiCpi0     
      kmcNC,          // kmNuMuBarNCcoh        
      kmcNC,          // kmNuMuBarNCoth        
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
      kmcNC           // kmNuEBarNCoth          
    },

    // sample: ksNC
    {
      kmcNuMuCC,           // kmNuMuCCQE            
      kmcNuMuCC,           // kmNuMuCCMEC           
      kmcNuMuCC,           // kmNuMuCC1piC          
      kmcNuMuCC,           // kmNuMuCC1pi0          
      kmcNuMuCC,           // kmNuMuCC2piC          
      kmcNuMuCC,           // kmNuMuCC2pi0          
      kmcNuMuCC,           // kmNuMuCCpiCpi0        
      kmcNuMuCC,           // kmNuMuCCcoh           
      kmcNuMuCC,           // kmNuMuCCoth           
    //kmcNCoth,            // kmNuMuNCEL            
    //kmcNCoth,            // kmNuMuNCMEC           
      kmcNCoth,            // kmNuMuNC1piC          
      kmcNC1pi0,           // kmNuMuNC1pi0          
    //kmcNCoth,            // kmNuMuNC2piC          
    //kmcNCoth,            // kmNuMuNC2pi0          
    //kmcNCoth,            // kmNuMuNCpiCpi0        
      kmcNCoth,            // kmNuMuNCcoh           
      kmcNCoth,            // kmNuMuNCoth           
      kmcNuMuBarCC,        // kmNuMuBarCCQE         
      kmcNuMuBarCC,        // kmNuMuBarCCMEC        
      kmcNuMuBarCC,        // kmNuMuBarCC1piC       
      kmcNuMuBarCC,        // kmNuMuBarCC1pi0       
      kmcNuMuBarCC,        // kmNuMuBarCC2piC       
      kmcNuMuBarCC,        // kmNuMuBarCC2pi0       
      kmcNuMuBarCC,        // kmNuMuBarCCpiCpi0     
      kmcNuMuBarCC,        // kmNuMuBarCCcoh        
      kmcNuMuBarCC,        // kmNuMuBarCCoth        
    //kmcNCoth,            // kmNuMuBarNCEL         
    //kmcNothC,            // kmNuMuBarNCMEC        
      kmcNCoth,            // kmNuMuBarNC1piC       
      kmcNC1pi0,           // kmNuMuBarNC1pi0       
    //kmcNCoth,            // kmNuMuBarNC2piC       
    //kmcNCoth,            // kmNuMuBarNC2pi0       
    //kmcNCoth,            // kmNuMuBarNCpiCpi0     
      kmcNCoth,            // kmNuMuBarNCcoh        
      kmcNCoth,            // kmNuMuBarNCoth        
      kmcNuECC,            // kmNuECCQE             
      kmcNuECC,            // kmNuECCMEC            
      kmcNuECC,            // kmNuECC1piC           
      kmcNuECC,            // kmNuECC1pi0           
      kmcNuECC,            // kmNuECC2piC           
      kmcNuECC,            // kmNuECC2pi0           
      kmcNuECC,            // kmNuECCpiCpi0         
      kmcNuECC,            // kmNuECCcoh            
      kmcNuECC,            // kmNuECCoth            
    //kmcNCoth,            // kmNuENCEL             
    //kmcNCoth,            // kmNuENCMEC           
      kmcNCoth,            // kmNuENC1piC           
      kmcNC1pi0,           // kmNuENC1pi0           
    //kmcNCoth,            // kmNuENC2piC           
    //kmcNCoth,            // kmNuENC2pi0           
    //kmcNCoth,            // kmNuENCpiCpi0         
      kmcNCoth,            // kmNuENCcoh            
      kmcNCoth,            // kmNuENCoth            
      kmcNuEBarCC,         // kmNuEBarCCQE          
      kmcNuEBarCC,         // kmNuEBarCCMEC         
      kmcNuEBarCC,         // kmNuEBarCC1piC        
      kmcNuEBarCC,         // kmNuEBarCC1pi0        
      kmcNuEBarCC,         // kmNuEBarCC2piC        
      kmcNuEBarCC,         // kmNuEBarCC2pi0        
      kmcNuEBarCC,         // kmNuEBarCCpiCpi0      
      kmcNuEBarCC,         // kmNuEBarCCcoh         
      kmcNuEBarCC,         // kmNuEBarCCoth         
    //kmcNCoth,            // kmNuEBarNCEL          
    //kmcNCoth,            // kmNuEBarNCMEC         
      kmcNCoth,            // kmNuEBarNC1piC        
      kmcNC1pi0,           // kmNuEBarNC1pi0        
    //kmcNCoth,            // kmNuEBarNC2piC        
    //kmcNCoth,            // kmNuEBarNC2pi0        
    //kmcNCoth,            // kmNuEBarNCpiCpi0      
      kmcNCoth,            // kmNuEBarNCcoh         
      kmcNCoth             // kmNuEBarNCoth          
    }

  } // end of RHC

};

} // conv
} // valor
  
#endif 

