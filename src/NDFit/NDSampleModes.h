//____________________________________________________________________________
/*!

\file      NDSampleModes

\brief     Define which true reaction modes to consider for each ND sample

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           George Christodoulou <georgios \at hep.ph.liv.ac.uk>
           University of Liverpool

           Nick Grant <n.grant \at lancaster.ac.uk>
           University of Lancaster

\created   March 20, 2014

\copyright (c) 2010-2014, The VALOR group

*/
//____________________________________________________________________________

#ifndef _valor_lbnx_nd_sample_modes_h_
#define _valor_lbnx_nd_sample_modes_h_

#include "Conventions/ReacMode.h"
#include "Conventions/ReacModeCoarse.h"
#include "NDFit/NDSample.h"

namespace valor {  
namespace conv {

//
// ---------------------------------------------------------------------------
// Define which true reaction modes are considered for each ND sample 
// included in the analysis
// ---------------------------------------------------------------------------
//

static const ReacMode_t kNDReactionModes[kNNDSamples][kNReacModes] = 
{
  // sample: ksNDNuMuCC1trkQE
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

  // sample: ksNDNuMuCC2trkQE
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

  // sample: ksNDNuMuCC1piC
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

  // sample: ksNDNuMuCC1pi0
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

  // sample: ksNDNuMuCCoth
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

static const ReacModeCoarse_t kNDReactionModesCoarse[kNNDSamples][kNReacModesCoarse] = 
{
  // sample: ksNDNuMuCC1trkQE
  {
    kmcNuMuCCQE,    
    kmcNuMuCCMEC,    
    kmcNuMuCC1pi,   
    kmcNuMuCC2pi,   
    kmcNuMuCCoth,   
    kmcNuMuBarCC,   
    kmcNuENueBarCC, 
    kmcNC           
  },

  // sample: ksNDNuMuCC2trkQE
  {
    kmcNuMuCCQE,    
    kmcNuMuCCMEC,    
    kmcNuMuCC1pi,   
    kmcNuMuCC2pi,   
    kmcNuMuCCoth,   
    kmcNuMuBarCC,   
    kmcNuENueBarCC, 
    kmcNC           
  },

  // sample: ksNDNuMuCC1piC
  {
    kmcNuMuCCQE,    
    kmcNuMuCC1pi,   
    kmcNuMuCC2pi,   
    kmcNuMuCCoth,   
    kmcNuMuBarCC,   
    kmcNuENueBarCC, 
    kmcNC,
    kmcUndefined
  },

  // sample: ksNDNuMuCC1pi0
  {
    kmcNuMuCCQE,    
    kmcNuMuCC1pi,   
    kmcNuMuCC2pi,   
    kmcNuMuCCoth,   
    kmcNuMuBarCC,   
    kmcNuENueBarCC, 
    kmcNC,
    kmcUndefined           
  },

  // sample: ksNDNuMuCCoth
  {
    kmcNuMuCCQE,    
    kmcNuMuCC1pi,   
    kmcNuMuCC2pi,   
    kmcNuMuCCoth,   
    kmcNuMuBarCC,   
    kmcNuENueBarCC, 
    kmcNC,
    kmcUndefined          
  }

};

//
// Also, specify formatting (line color, fill color, fill style)
//

static const int kNDReactionModesCoarseFormatting[kNNDSamples][kNReacModesCoarse][3] = 
{
  // sample: ksNDNuMuCC1trkQE
  {
    { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
    { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC    
    { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
    { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
    { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
    { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
    { kBlack, kViolet-1, 3001 }, // kmcNuENueBarCC
    { kBlack, kRed,      3001 }  // kmcNC           
  },

  // sample: ksNDNuMuCC2trkQE
  {
    { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
    { kBlack, kYellow,   3001 }, // kmcNuMuCCMEC    
    { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
    { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
    { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
    { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
    { kBlack, kViolet-1, 3001 }, // kmcNuENueBarCC
    { kBlack, kRed,      3001 }  // kmcNC           
  },

  // sample: ksNDNuMuCC1piC
  {
    { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
    { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
    { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
    { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
    { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
    { kBlack, kViolet-1, 3001 }, // kmcNuENueBarCC
    { kBlack, kRed,      3001 }, // kmcNC           
    {0,0,0}
  },

  // sample: ksNDNuMuCC1pi0
  {
    { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
    { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
    { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
    { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
    { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
    { kBlack, kViolet-1, 3001 }, // kmcNuENueBarCC
    { kBlack, kRed,      3001 }, // kmcNC           
    {0,0,0}
  },

  // sample: ksNDNuMuCCoth
  {
    { kBlack, kWhite,    3544 }, // kmcNuMuCCQE    
    { kBlack, kAzure,    3004 }, // kmcNuMuCC1pi
    { kBlack, kBlue,     3005 }, // kmcNuMuCC2pi
    { kBlack, kGreen,    3007 }, // kmcNuMuCCoth
    { kBlack, kMagenta,  3001 }, // kmcNuMuBarCC  
    { kBlack, kViolet-1, 3001 }, // kmcNuENueBarCC
    { kBlack, kRed,      3001 }, // kmcNC         
    {0,0,0}  
  }

};

//
// ---------------------------------------------------------------------------
// Specify how each ReacMode_t is mapped onto the ReacModeCoarse_t types.
// ---------------------------------------------------------------------------
//
static const ReacModeCoarse_t kNDMappingToCoarseModes[kNNDSamples][kNReacModes] = 
{
  // sample: ksNDNuMuCC1trkQE
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
    kmcNuENueBarCC, // kmNuECCQE             
    kmcNuENueBarCC, // kmNuECCMEC            
    kmcNuENueBarCC, // kmNuECC1piC           
    kmcNuENueBarCC, // kmNuECC1pi0           
    kmcNuENueBarCC, // kmNuECC2piC           
    kmcNuENueBarCC, // kmNuECC2pi0           
    kmcNuENueBarCC, // kmNuECCpiCpi0         
    kmcNuENueBarCC, // kmNuECCcoh            
    kmcNuENueBarCC, // kmNuECCoth            
  //kmcNC,          // kmNuENCEL             
  //kmcNC,          // kmNuENCMEC           
    kmcNC,          // kmNuENC1piC           
    kmcNC,          // kmNuENC1pi0           
  //kmcNC,          // kmNuENC2piC           
  //kmcNC,          // kmNuENC2pi0           
  //kmcNC,          // kmNuENCpiCpi0         
    kmcNC,          // kmNuENCcoh            
    kmcNC,          // kmNuENCoth            
    kmcNuENueBarCC, // kmNuEBarCCQE          
    kmcNuENueBarCC, // kmNuEBarCCMEC         
    kmcNuENueBarCC, // kmNuEBarCC1piC        
    kmcNuENueBarCC, // kmNuEBarCC1pi0        
    kmcNuENueBarCC, // kmNuEBarCC2piC        
    kmcNuENueBarCC, // kmNuEBarCC2pi0        
    kmcNuENueBarCC, // kmNuEBarCCpiCpi0      
    kmcNuENueBarCC, // kmNuEBarCCcoh         
    kmcNuENueBarCC, // kmNuEBarCCoth         
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

  // sample: ksNDNuMuCC2trkQE
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
    kmcNuENueBarCC, // kmNuECCQE             
    kmcNuENueBarCC, // kmNuECCMEC            
    kmcNuENueBarCC, // kmNuECC1piC           
    kmcNuENueBarCC, // kmNuECC1pi0           
    kmcNuENueBarCC, // kmNuECC2piC           
    kmcNuENueBarCC, // kmNuECC2pi0           
    kmcNuENueBarCC, // kmNuECCpiCpi0         
    kmcNuENueBarCC, // kmNuECCcoh            
    kmcNuENueBarCC, // kmNuECCoth            
  //kmcNC,          // kmNuENCEL             
  //kmcNC,          // kmNuENCMEC           
    kmcNC,          // kmNuENC1piC           
    kmcNC,          // kmNuENC1pi0           
  //kmcNC,          // kmNuENC2piC           
  //kmcNC,          // kmNuENC2pi0           
  //kmcNC,          // kmNuENCpiCpi0         
    kmcNC,          // kmNuENCcoh            
    kmcNC,          // kmNuENCoth            
    kmcNuENueBarCC, // kmNuEBarCCQE          
    kmcNuENueBarCC, // kmNuEBarCCMEC         
    kmcNuENueBarCC, // kmNuEBarCC1piC        
    kmcNuENueBarCC, // kmNuEBarCC1pi0        
    kmcNuENueBarCC, // kmNuEBarCC2piC        
    kmcNuENueBarCC, // kmNuEBarCC2pi0        
    kmcNuENueBarCC, // kmNuEBarCCpiCpi0      
    kmcNuENueBarCC, // kmNuEBarCCcoh         
    kmcNuENueBarCC, // kmNuEBarCCoth         
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

  // sample: ksNDNuMuCC1piC
  {
    kmcNuMuCCQE,    // kmNuMuCCQE            
    kmcNuMuCCQE,    // kmNuMuCCMEC           
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
    kmcNuENueBarCC, // kmNuECCQE             
    kmcNuENueBarCC, // kmNuECCMEC            
    kmcNuENueBarCC, // kmNuECC1piC           
    kmcNuENueBarCC, // kmNuECC1pi0           
    kmcNuENueBarCC, // kmNuECC2piC           
    kmcNuENueBarCC, // kmNuECC2pi0           
    kmcNuENueBarCC, // kmNuECCpiCpi0         
    kmcNuENueBarCC, // kmNuECCcoh            
    kmcNuENueBarCC, // kmNuECCoth            
  //kmcNC,          // kmNuENCEL             
  //kmcNC,          // kmNuENCMEC           
    kmcNC,          // kmNuENC1piC           
    kmcNC,          // kmNuENC1pi0           
  //kmcNC,          // kmNuENC2piC           
  //kmcNC,          // kmNuENC2pi0           
  //kmcNC,          // kmNuENCpiCpi0         
    kmcNC,          // kmNuENCcoh            
    kmcNC,          // kmNuENCoth            
    kmcNuENueBarCC, // kmNuEBarCCQE          
    kmcNuENueBarCC, // kmNuEBarCCMEC         
    kmcNuENueBarCC, // kmNuEBarCC1piC        
    kmcNuENueBarCC, // kmNuEBarCC1pi0        
    kmcNuENueBarCC, // kmNuEBarCC2piC        
    kmcNuENueBarCC, // kmNuEBarCC2pi0        
    kmcNuENueBarCC, // kmNuEBarCCpiCpi0      
    kmcNuENueBarCC, // kmNuEBarCCcoh         
    kmcNuENueBarCC, // kmNuEBarCCoth         
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

  // sample: ksNDNuMuCC1pi0
  {
    kmcNuMuCCQE,    // kmNuMuCCQE            
    kmcNuMuCCQE,    // kmNuMuCCMEC           
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
    kmcNuENueBarCC, // kmNuECCQE             
    kmcNuENueBarCC, // kmNuECCMEC            
    kmcNuENueBarCC, // kmNuECC1piC           
    kmcNuENueBarCC, // kmNuECC1pi0           
    kmcNuENueBarCC, // kmNuECC2piC           
    kmcNuENueBarCC, // kmNuECC2pi0           
    kmcNuENueBarCC, // kmNuECCpiCpi0         
    kmcNuENueBarCC, // kmNuECCcoh            
    kmcNuENueBarCC, // kmNuECCoth            
  //kmcNC,          // kmNuENCEL             
  //kmcNC,          // kmNuENCMEC           
    kmcNC,          // kmNuENC1piC           
    kmcNC,          // kmNuENC1pi0           
  //kmcNC,          // kmNuENC2piC           
  //kmcNC,          // kmNuENC2pi0           
  //kmcNC,          // kmNuENCpiCpi0         
    kmcNC,          // kmNuENCcoh            
    kmcNC,          // kmNuENCoth            
    kmcNuENueBarCC, // kmNuEBarCCQE          
    kmcNuENueBarCC, // kmNuEBarCCMEC         
    kmcNuENueBarCC, // kmNuEBarCC1piC        
    kmcNuENueBarCC, // kmNuEBarCC1pi0        
    kmcNuENueBarCC, // kmNuEBarCC2piC        
    kmcNuENueBarCC, // kmNuEBarCC2pi0        
    kmcNuENueBarCC, // kmNuEBarCCpiCpi0      
    kmcNuENueBarCC, // kmNuEBarCCcoh         
    kmcNuENueBarCC, // kmNuEBarCCoth         
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

  // sample: ksNDNuMuCCoth
  {
    kmcNuMuCCQE,    // kmNuMuCCQE            
    kmcNuMuCCQE,    // kmNuMuCCMEC           
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
    kmcNuENueBarCC, // kmNuECCQE             
    kmcNuENueBarCC, // kmNuECCMEC            
    kmcNuENueBarCC, // kmNuECC1piC           
    kmcNuENueBarCC, // kmNuECC1pi0           
    kmcNuENueBarCC, // kmNuECC2piC           
    kmcNuENueBarCC, // kmNuECC2pi0           
    kmcNuENueBarCC, // kmNuECCpiCpi0         
    kmcNuENueBarCC, // kmNuECCcoh            
    kmcNuENueBarCC, // kmNuECCoth            
  //kmcNC,          // kmNuENCEL             
  //kmcNC,          // kmNuENCMEC           
    kmcNC,          // kmNuENC1piC           
    kmcNC,          // kmNuENC1pi0           
  //kmcNC,          // kmNuENC2piC           
  //kmcNC,          // kmNuENC2pi0           
  //kmcNC,          // kmNuENCpiCpi0         
    kmcNC,          // kmNuENCcoh            
    kmcNC,          // kmNuENCoth            
    kmcNuENueBarCC, // kmNuEBarCCQE          
    kmcNuENueBarCC, // kmNuEBarCCMEC         
    kmcNuENueBarCC, // kmNuEBarCC1piC        
    kmcNuENueBarCC, // kmNuEBarCC1pi0        
    kmcNuENueBarCC, // kmNuEBarCC2piC        
    kmcNuENueBarCC, // kmNuEBarCC2pi0        
    kmcNuENueBarCC, // kmNuEBarCCpiCpi0      
    kmcNuENueBarCC, // kmNuEBarCCcoh         
    kmcNuENueBarCC, // kmNuEBarCCoth         
  //kmcNC,          // kmNuEBarNCEL          
  //kmcNC,          // kmNuEBarNCMEC         
    kmcNC,          // kmNuEBarNC1piC        
    kmcNC,          // kmNuEBarNC1pi0        
  //kmcNC,          // kmNuEBarNC2piC        
  //kmcNC,          // kmNuEBarNC2pi0        
  //kmcNC,          // kmNuEBarNCpiCpi0      
    kmcNC,          // kmNuEBarNCcoh         
    kmcNC           // kmNuEBarNCoth          
  }

};

} // conv
} // valor
  
#endif 

