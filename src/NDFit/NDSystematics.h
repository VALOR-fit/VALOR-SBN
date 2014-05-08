//____________________________________________________________________________
/*!

\file      NDSystDef

\brief     Typedef specific LBNx ND systematics to free PhysParamId_t slots
           of the VALOR framework

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

#ifndef _valor_lbnx_nd_syst_def_h_
#define _valor_lbnx_nd_syst_def_h_

#include <string>

#include "Conventions/PhysParamId.h"

using std::string;

namespace valor {
namespace conv {

//
// A very simple set of systematics for the 1st iteration
//

static const int kNumOfSystematics = 23;

// FHC flux
static const PhysParamId_t kNuisFHCNuMuFlux00    = kNuis000; 
static const PhysParamId_t kNuisFHCNuMuFlux01    = kNuis001; 
static const PhysParamId_t kNuisFHCNuMuFlux02    = kNuis002; 
static const PhysParamId_t kNuisFHCNuMuFlux03    = kNuis003; 
static const PhysParamId_t kNuisFHCNuMuFlux04    = kNuis004; 
static const PhysParamId_t kNuisFHCNuMuFlux05    = kNuis005; 
static const PhysParamId_t kNuisFHCNuMuFlux06    = kNuis006; 
static const PhysParamId_t kNuisFHCNuMuFlux07    = kNuis007; 
static const PhysParamId_t kNuisFHCNuMuFlux08    = kNuis008; 
static const PhysParamId_t kNuisFHCNuMuFlux09    = kNuis009; 
static const PhysParamId_t kNuisFHCNuMuBarFlux00 = kNuis010; 
static const PhysParamId_t kNuisFHCNuMuBarFlux01 = kNuis011; 
static const PhysParamId_t kNuisFHCNuMuBarFlux02 = kNuis012; 
static const PhysParamId_t kNuisFHCNuMuBarFlux03 = kNuis013; 
static const PhysParamId_t kNuisFHCNuMuBarFlux04 = kNuis014; 
static const PhysParamId_t kNuisFHCNuEFlux00     = kNuis015; 
static const PhysParamId_t kNuisFHCNuEFlux01     = kNuis016; 
static const PhysParamId_t kNuisFHCNuEFlux02     = kNuis017; 
// Cross-section
static const PhysParamId_t kNuisNormCCQE         = kNuis018; 
static const PhysParamId_t kNuisNormCC1piC       = kNuis019; 
static const PhysParamId_t kNuisNormCC1pi0       = kNuis020; 
static const PhysParamId_t kNuisNormCCoth        = kNuis021; 
static const PhysParamId_t kNuisNormNC           = kNuis022; 


//
// This array fully specifies which systematics are applied to which template,
// for all samples considered in this analysis
//
//for the time-being this does not need to be function of the sample id
//static const bool kApplySystToTemplate[kNNDSamples][kNReacModes][kNumOfSystematics] = 

static const bool kApplySystToTemplate[kNReacModes][kNumOfSystematics] = 
{
  // sample: any
  //{
    // Systematics
    //                      FHC flux                            XSec
    //|--------------------------------------------------|  |-----------|
    //            numu                numubar       nue/b 
    //|--------------------------|  |-----------|  |-----|  
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 }, // kmNuMuCCQE
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 }, // kmNuMuCCMEC
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 }, // kmNuMuCC1piC
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 }, // kmNuMuCC1pi0
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 }, // kmNuMuCC2piC
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 }, // kmNuMuCC2pi0
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 }, // kmNuMuCCpiCpi0
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 }, // kmNuMuCCcoh
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 }, // kmNuMuCCoth
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, // kmNuMuNC1piC
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, // kmNuMuNC1pi0
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, // kmNuMuNCcoh
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, // kmNuMuNCoth
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0 }, // kmNuMuBarCCQE
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0 }, // kmNuMuBarCCMEC
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0 }, // kmNuMuBarCC1piC
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0 }, // kmNuMuBarCC1pi0
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0 }, // kmNuMuBarCC2piC
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0 }, // kmNuMuBarCC2pi0
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0 }, // kmNuMuBarCCpiCpi0
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0 }, // kmNuMuBarCCcoh
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0 }, // kmNuMuBarCCoth
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 }, // kmNuMuBarNC1piC
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 }, // kmNuMuBarNC1pi0
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 }, // kmNuMuBarNCcoh
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 }, // kmNuMuBarNCoth
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 }, // kmNuECCQE
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 }, // kmNuECCMEC
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0 }, // kmNuECC1piC
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0 }, // kmNuECC1pi0
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0 }, // kmNuECC2piC
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0 }, // kmNuECC2pi0
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0 }, // kmNuECCpiCpi0
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0 }, // kmNuECCcoh
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0 }, // kmNuECCoth
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1 }, // kmNuENC1piC
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1 }, // kmNuENC1pi0
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1 }, // kmNuENCcoh
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1 }, // kmNuENCoth
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 }, // kmNuEBarCCQE
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 }, // kmNuEBarCCMEC
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0 }, // kmNuEBarCC1piC
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0 }, // kmNuEBarCC1pi0
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0 }, // kmNuEBarCC2piC
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0 }, // kmNuEBarCC2pi0
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0 }, // kmNuEBarCCpiCpi0
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0 }, // kmNuEBarCCcoh
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0 }, // kmNuEBarCCoth
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1 }, // kmNuEBarNC1piC
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1 }, // kmNuEBarNC1pi0
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1 }, // kmNuEBarNCcoh
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1 }  // kmNuEBarNCoth
  //}
};

//
// This array fully specifies the true energy of each systematic
//

static const double kSystEtrueRange[kNumOfSystematics][2] = 
{
  // Emin, Emax
   {  0.0,  1.0},       // kNuisFHCNuMuFlux00
   {  1.0,  1.5},       // kNuisFHCNuMuFlux01
   {  1.5,  2.0},       // kNuisFHCNuMuFlux02
   {  2.0,  2.5},       // kNuisFHCNuMuFlux03
   {  2.5,  3.0},       // kNuisFHCNuMuFlux04
   {  3.0,  4.0},       // kNuisFHCNuMuFlux05
   {  4.0,  5.0},       // kNuisFHCNuMuFlux06
   {  5.0, 10.0},       // kNuisFHCNuMuFlux07
   { 10.0, 25.0},       // kNuisFHCNuMuFlux08
   { 25.0, kMaxEtrue }, // kNuisFHCNuMuFlux09 
   {  0.0,  1.5},       // kNuisFHCNuMuBarFlux00
   {  1.5,  3.0},       // kNuisFHCNuMuBarFlux01
   {  3.0,  6.0},       // kNuisFHCNuMuBarFlux02
   {  6.0, 10.0},       // kNuisFHCNuMuBarFlux03
   { 10.0, kMaxEtrue},  // kNuisFHCNuMuBarFlux04
   {  0.0,  3.0},       // kNuisFHCNuEFlux00 
   {  3.0, 10.0},       // kNuisFHCNuEFlux01 
   { 10.0, kMaxEtrue},  // kNuisFHCNuEFlux02 
   {  0.0, kMaxEtrue},  // kNuisNormCCQE 
   {  0.0, kMaxEtrue},  // kNuisNormCC1piC
   {  0.0, kMaxEtrue},  // kNuisNormCC1pi0
   {  0.0, kMaxEtrue},  // kNuisNormCCoth 
   {  0.0, kMaxEtrue}   // kNuisNormNC 
};


//
// This array fully specifies which of the systematics are to me marginalised (profiled-out)
// and which are the ones we try to constrain and output in the systematic covariance matrix
//
static const double kSystMarginalize[kNumOfSystematics] = 
{
   false,  // kNuisFHCNuMuFlux00
   false,  // kNuisFHCNuMuFlux01
   false,  // kNuisFHCNuMuFlux02
   false,  // kNuisFHCNuMuFlux03
   false,  // kNuisFHCNuMuFlux04
   false,  // kNuisFHCNuMuFlux05
   false,  // kNuisFHCNuMuFlux06
   false,  // kNuisFHCNuMuFlux07
   false,  // kNuisFHCNuMuFlux08
   false,  // kNuisFHCNuMuFlux09 
   false,  // kNuisFHCNuMuBarFlux00
   false,  // kNuisFHCNuMuBarFlux01
   false,  // kNuisFHCNuMuBarFlux02
   false,  // kNuisFHCNuMuBarFlux03
   false,  // kNuisFHCNuMuBarFlux04
   false,  // kNuisFHCNuEFlux00 
   false,  // kNuisFHCNuEFlux01 
   false,  // kNuisFHCNuEFlux02 
   false,  // kNuisNormCCQE 
   false,  // kNuisNormCC1piC
   false,  // kNuisNormCC1pi0
   false,  // kNuisNormCCoth 
   false   // kNuisNormNC 
};


} // conv
} // valor
  
#endif 

