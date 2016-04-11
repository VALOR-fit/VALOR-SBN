//____________________________________________________________________________
/*!

\file      FitParams

\brief     Typedef specific systematics to free PhysParamId_t slots
           of the VALOR framework

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

\created   March 20, 2014

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_fit_param_definition_h_
#define _valor_dune_fit_param_definition_h_

#include <string>

//fmwk
#include "Conventions/PhysParamId.h"
#include "FitCore/FitParamList.h"
#include "FitCore/PhysHypothesis.h"

//dune
#include "Conventions/BeamConf.h"
#include "Conventions/DuneBuild.h"
#include "Conventions/ReacMode.h"
#include "Conventions/SampleKineBinning.h"
#include "Conventions/FitParamGroup.h"

using std::string;

namespace valor {
namespace conv {

// If we don't have an interaction model defined, use the simple one.
#ifndef INT_MODEL
#define INT_MODEL 1
#endif

static const int kNFitParamsNuFlux = 104; // neutrino flux related
static const int kNFitParamsNuDet  =   9; // neutrino detector related
#if INT_MODEL == 1 // The simple sample normalisaation xsec model
static const int kNFitParamsNuInt  =   6; // neutrino interactions related
#elif INT_MODEL == 2 // The GENIE-based model with responses
static const int kNFitParamsNuInt  =  21; // neutrino interactions related
//~ static const int kNFitParamsNuInt  =  37; // neutrino interactions related
#endif //INT_MODEL

static const int kNFitParams = kNFitParamsNuFlux+kNFitParamsNuInt+kNFitParamsNuDet;


//
// FHC flux
//
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
static const PhysParamId_t kNuisFHCNuMuFlux10    = kNuis010; 
static const PhysParamId_t kNuisFHCNuMuFlux11    = kNuis011; 
static const PhysParamId_t kNuisFHCNuMuFlux12    = kNuis012; 
static const PhysParamId_t kNuisFHCNuMuFlux13    = kNuis013; 
static const PhysParamId_t kNuisFHCNuMuFlux14    = kNuis014; 
static const PhysParamId_t kNuisFHCNuMuFlux15    = kNuis015; 
static const PhysParamId_t kNuisFHCNuMuFlux16    = kNuis016; 
static const PhysParamId_t kNuisFHCNuMuFlux17    = kNuis017; 
static const PhysParamId_t kNuisFHCNuMuFlux18    = kNuis018;
static const PhysParamId_t kNuisFHCNuMuBarFlux00 = kNuis019; 
static const PhysParamId_t kNuisFHCNuMuBarFlux01 = kNuis020; 
static const PhysParamId_t kNuisFHCNuMuBarFlux02 = kNuis021; 
static const PhysParamId_t kNuisFHCNuMuBarFlux03 = kNuis022; 
static const PhysParamId_t kNuisFHCNuMuBarFlux04 = kNuis023; 
static const PhysParamId_t kNuisFHCNuMuBarFlux05 = kNuis024; 
static const PhysParamId_t kNuisFHCNuMuBarFlux06 = kNuis025; 
static const PhysParamId_t kNuisFHCNuMuBarFlux07 = kNuis026; 
static const PhysParamId_t kNuisFHCNuMuBarFlux08 = kNuis027; 
static const PhysParamId_t kNuisFHCNuMuBarFlux09 = kNuis028; 
static const PhysParamId_t kNuisFHCNuMuBarFlux10 = kNuis029; 
static const PhysParamId_t kNuisFHCNuMuBarFlux11 = kNuis030; 
static const PhysParamId_t kNuisFHCNuMuBarFlux12 = kNuis031; 
static const PhysParamId_t kNuisFHCNuMuBarFlux13 = kNuis032; 
static const PhysParamId_t kNuisFHCNuMuBarFlux14 = kNuis033; 
static const PhysParamId_t kNuisFHCNuMuBarFlux15 = kNuis034; 
static const PhysParamId_t kNuisFHCNuMuBarFlux16 = kNuis035; 
static const PhysParamId_t kNuisFHCNuMuBarFlux17 = kNuis036; 
static const PhysParamId_t kNuisFHCNuMuBarFlux18 = kNuis037;
static const PhysParamId_t kNuisFHCNuEFlux00     = kNuis038; 
static const PhysParamId_t kNuisFHCNuEFlux01     = kNuis039; 
static const PhysParamId_t kNuisFHCNuEFlux02     = kNuis040; 
static const PhysParamId_t kNuisFHCNuEFlux03     = kNuis041; 
static const PhysParamId_t kNuisFHCNuEFlux04     = kNuis042; 
static const PhysParamId_t kNuisFHCNuEFlux05     = kNuis043; 
static const PhysParamId_t kNuisFHCNuEFlux06     = kNuis044; 
static const PhysParamId_t kNuisFHCNuEBarFlux00  = kNuis045; 
static const PhysParamId_t kNuisFHCNuEBarFlux01  = kNuis046; 
static const PhysParamId_t kNuisFHCNuEBarFlux02  = kNuis047; 
static const PhysParamId_t kNuisFHCNuEBarFlux03  = kNuis048; 
static const PhysParamId_t kNuisFHCNuEBarFlux04  = kNuis049; 
static const PhysParamId_t kNuisFHCNuEBarFlux05  = kNuis050; 
static const PhysParamId_t kNuisFHCNuEBarFlux06  = kNuis051; 
//
// RHC flux
//
static const PhysParamId_t kNuisRHCNuMuFlux00    = kNuis052; 
static const PhysParamId_t kNuisRHCNuMuFlux01    = kNuis053; 
static const PhysParamId_t kNuisRHCNuMuFlux02    = kNuis054; 
static const PhysParamId_t kNuisRHCNuMuFlux03    = kNuis055; 
static const PhysParamId_t kNuisRHCNuMuFlux04    = kNuis056; 
static const PhysParamId_t kNuisRHCNuMuFlux05    = kNuis057; 
static const PhysParamId_t kNuisRHCNuMuFlux06    = kNuis058; 
static const PhysParamId_t kNuisRHCNuMuFlux07    = kNuis059; 
static const PhysParamId_t kNuisRHCNuMuFlux08    = kNuis060; 
static const PhysParamId_t kNuisRHCNuMuFlux09    = kNuis061; 
static const PhysParamId_t kNuisRHCNuMuFlux10    = kNuis062; 
static const PhysParamId_t kNuisRHCNuMuFlux11    = kNuis063; 
static const PhysParamId_t kNuisRHCNuMuFlux12    = kNuis064; 
static const PhysParamId_t kNuisRHCNuMuFlux13    = kNuis065; 
static const PhysParamId_t kNuisRHCNuMuFlux14    = kNuis066; 
static const PhysParamId_t kNuisRHCNuMuFlux15    = kNuis067; 
static const PhysParamId_t kNuisRHCNuMuFlux16    = kNuis068; 
static const PhysParamId_t kNuisRHCNuMuFlux17    = kNuis069; 
static const PhysParamId_t kNuisRHCNuMuFlux18    = kNuis070;
static const PhysParamId_t kNuisRHCNuMuBarFlux00 = kNuis071; 
static const PhysParamId_t kNuisRHCNuMuBarFlux01 = kNuis072; 
static const PhysParamId_t kNuisRHCNuMuBarFlux02 = kNuis073; 
static const PhysParamId_t kNuisRHCNuMuBarFlux03 = kNuis074; 
static const PhysParamId_t kNuisRHCNuMuBarFlux04 = kNuis075; 
static const PhysParamId_t kNuisRHCNuMuBarFlux05 = kNuis076; 
static const PhysParamId_t kNuisRHCNuMuBarFlux06 = kNuis077; 
static const PhysParamId_t kNuisRHCNuMuBarFlux07 = kNuis078; 
static const PhysParamId_t kNuisRHCNuMuBarFlux08 = kNuis079; 
static const PhysParamId_t kNuisRHCNuMuBarFlux09 = kNuis080; 
static const PhysParamId_t kNuisRHCNuMuBarFlux10 = kNuis081; 
static const PhysParamId_t kNuisRHCNuMuBarFlux11 = kNuis082; 
static const PhysParamId_t kNuisRHCNuMuBarFlux12 = kNuis083; 
static const PhysParamId_t kNuisRHCNuMuBarFlux13 = kNuis084; 
static const PhysParamId_t kNuisRHCNuMuBarFlux14 = kNuis085; 
static const PhysParamId_t kNuisRHCNuMuBarFlux15 = kNuis086; 
static const PhysParamId_t kNuisRHCNuMuBarFlux16 = kNuis087; 
static const PhysParamId_t kNuisRHCNuMuBarFlux17 = kNuis088; 
static const PhysParamId_t kNuisRHCNuMuBarFlux18 = kNuis089;
static const PhysParamId_t kNuisRHCNuEFlux00     = kNuis090; 
static const PhysParamId_t kNuisRHCNuEFlux01     = kNuis091; 
static const PhysParamId_t kNuisRHCNuEFlux02     = kNuis092; 
static const PhysParamId_t kNuisRHCNuEFlux03     = kNuis093; 
static const PhysParamId_t kNuisRHCNuEFlux04     = kNuis094; 
static const PhysParamId_t kNuisRHCNuEFlux05     = kNuis095; 
static const PhysParamId_t kNuisRHCNuEFlux06     = kNuis096; 
static const PhysParamId_t kNuisRHCNuEBarFlux00  = kNuis097; 
static const PhysParamId_t kNuisRHCNuEBarFlux01  = kNuis098; 
static const PhysParamId_t kNuisRHCNuEBarFlux02  = kNuis099; 
static const PhysParamId_t kNuisRHCNuEBarFlux03  = kNuis100; 
static const PhysParamId_t kNuisRHCNuEBarFlux04  = kNuis101; 
static const PhysParamId_t kNuisRHCNuEBarFlux05  = kNuis102; 
static const PhysParamId_t kNuisRHCNuEBarFlux06  = kNuis103; 
//
// Cross-section
//
static const PhysParamId_t kNuisNormCCQE         = kNuis104; 
static const PhysParamId_t kNuisNormCC1piC       = kNuis105; 
static const PhysParamId_t kNuisNormCC1pi0       = kNuis106; 
static const PhysParamId_t kNuisNormCCoth        = kNuis107; 
static const PhysParamId_t kNuisNormNC           = kNuis108; 
static const PhysParamId_t kNuisRatioNuENuMu     = kNuis109; 
//
// Detector systematics
//
static const PhysParamId_t kNuisEffNuMuCC1trkQE  = kNuis110;
static const PhysParamId_t kNuisEffNuMuCC2trkQE  = kNuis111;
static const PhysParamId_t kNuisEffNuMuCC1piC    = kNuis112;
static const PhysParamId_t kNuisEffNuMuCC1pi0    = kNuis113;
static const PhysParamId_t kNuisEffNuMuCC1piC1pi0= kNuis114;
static const PhysParamId_t kNuisEffNuMuCCoth     = kNuis115;
static const PhysParamId_t kNuisEffNuECC         = kNuis116;
static const PhysParamId_t kNuisEffNuMuCCWSgn    = kNuis117;
static const PhysParamId_t kNuisEffNC            = kNuis118;

//
// Interaction model, more complex
//
static const PhysParamId_t kNuisIntNuCCQE1          = kNuis119;
static const PhysParamId_t kNuisIntNuCCQE2          = kNuis120;
static const PhysParamId_t kNuisIntNuCCQE3          = kNuis121;
static const PhysParamId_t kNuisIntNuBarCCQE1       = kNuis122;
static const PhysParamId_t kNuisIntNuBarCCQE2       = kNuis123;
static const PhysParamId_t kNuisIntNuBarCCQE3       = kNuis124;

static const PhysParamId_t kNuisIntNuCC1piz1        = kNuis125;
static const PhysParamId_t kNuisIntNuCC1piz2        = kNuis126;
static const PhysParamId_t kNuisIntNuCC1piz3        = kNuis127;
static const PhysParamId_t kNuisIntNuCC1pic1        = kNuis128;
static const PhysParamId_t kNuisIntNuCC1pic2        = kNuis129;
static const PhysParamId_t kNuisIntNuCC1pic3        = kNuis130;

static const PhysParamId_t kNuisIntNuBarCC1piz1     = kNuis131;
static const PhysParamId_t kNuisIntNuBarCC1piz2     = kNuis132;
static const PhysParamId_t kNuisIntNuBarCC1piz3     = kNuis133;
static const PhysParamId_t kNuisIntNuBarCC1pic1     = kNuis134;
static const PhysParamId_t kNuisIntNuBarCC1pic2     = kNuis135;
static const PhysParamId_t kNuisIntNuBarCC1pic3     = kNuis136;

static const PhysParamId_t kNuisIntNuMultiPi1       = kNuis137;
static const PhysParamId_t kNuisIntNuMultiPi2       = kNuis138;
static const PhysParamId_t kNuisIntNuMultiPi3       = kNuis139;
static const PhysParamId_t kNuisIntNuBarMultiPi1    = kNuis140;
static const PhysParamId_t kNuisIntNuBarMultiPi2    = kNuis141;
static const PhysParamId_t kNuisIntNuBarMultiPi3    = kNuis142;

static const PhysParamId_t kNuisIntNormMEC          = kNuis143;
static const PhysParamId_t kNuisIntNormCoherent     = kNuis144;
static const PhysParamId_t kNuisIntNormCCOther      = kNuis145;
static const PhysParamId_t kNuisIntNormNC           = kNuis146;
static const PhysParamId_t kNuisIntNormNuMuToNuE    = kNuis147;
static const PhysParamId_t kNuisIntNormNuBarToNu    = kNuis148;

static const PhysParamId_t kNuisIntNucMeanFreePath  = kNuis150;
static const PhysParamId_t kNuisIntPiMeanFreePath   = kNuis151;
static const PhysParamId_t kNuisIntPiChargeExchange = kNuis152;
static const PhysParamId_t kNuisIntPiAbsorb         = kNuis153;
static const PhysParamId_t kNuisIntPiInelastic      = kNuis154;

static const PhysParamId_t kNuisIntHadronization    = kNuis155;

// Boundaries between parameter types
static const PhysParamId_t kNuisFluxFirstParameter = kNuisFHCNuMuFlux00;
static const PhysParamId_t kNuisFluxLastParameter  = kNuisRHCNuEBarFlux06;
#if INT_MODEL == 1
static const PhysParamId_t kNuisIntFirstParameter  = kNuisNormCCQE;
static const PhysParamId_t kNuisIntLastParameter   = kNuisRatioNuENuMu;
#elif INT_MODEL == 2
static const PhysParamId_t kNuisIntFirstParameter  = kNuisIntNuCCQE1;
static const PhysParamId_t kNuisIntLastParameter   = kNuisIntHadronization;
#endif
static const PhysParamId_t kNuisDetFirstParameter  = kNuisEffNuMuCC1trkQE;
static const PhysParamId_t kNuisDetLastParameter   = kNuisEffNC;


// ...........................................................................
//  List of physics parameters considered in this analysis
// ...........................................................................
//

static const PhysParamId_t kFitParam[kNFitParams] = 
{
   // FHC flux
   kNuisFHCNuMuFlux00,
   kNuisFHCNuMuFlux01,
   kNuisFHCNuMuFlux02,
   kNuisFHCNuMuFlux03,
   kNuisFHCNuMuFlux04,
   kNuisFHCNuMuFlux05,
   kNuisFHCNuMuFlux06,
   kNuisFHCNuMuFlux07,
   kNuisFHCNuMuFlux08,
   kNuisFHCNuMuFlux09,
   kNuisFHCNuMuFlux10,
   kNuisFHCNuMuFlux11,
   kNuisFHCNuMuFlux12,
   kNuisFHCNuMuFlux13,
   kNuisFHCNuMuFlux14,
   kNuisFHCNuMuFlux15,
   kNuisFHCNuMuFlux16,
   kNuisFHCNuMuFlux17,
   kNuisFHCNuMuFlux18,
   kNuisFHCNuMuBarFlux00,
   kNuisFHCNuMuBarFlux01,
   kNuisFHCNuMuBarFlux02,
   kNuisFHCNuMuBarFlux03,
   kNuisFHCNuMuBarFlux04,
   kNuisFHCNuMuBarFlux05,
   kNuisFHCNuMuBarFlux06,
   kNuisFHCNuMuBarFlux07,
   kNuisFHCNuMuBarFlux08,
   kNuisFHCNuMuBarFlux09,
   kNuisFHCNuMuBarFlux10,
   kNuisFHCNuMuBarFlux11,
   kNuisFHCNuMuBarFlux12,
   kNuisFHCNuMuBarFlux13,
   kNuisFHCNuMuBarFlux14,
   kNuisFHCNuMuBarFlux15,
   kNuisFHCNuMuBarFlux16,
   kNuisFHCNuMuBarFlux17,
   kNuisFHCNuMuBarFlux18,
   kNuisFHCNuEFlux00,
   kNuisFHCNuEFlux01,
   kNuisFHCNuEFlux02,
   kNuisFHCNuEFlux03,
   kNuisFHCNuEFlux04,
   kNuisFHCNuEFlux05,
   kNuisFHCNuEFlux06,
   kNuisFHCNuEBarFlux00,
   kNuisFHCNuEBarFlux01,
   kNuisFHCNuEBarFlux02,
   kNuisFHCNuEBarFlux03,
   kNuisFHCNuEBarFlux04,
   kNuisFHCNuEBarFlux05,
   kNuisFHCNuEBarFlux06,
   // RHC flux
   kNuisRHCNuMuFlux00,
   kNuisRHCNuMuFlux01,
   kNuisRHCNuMuFlux02,
   kNuisRHCNuMuFlux03,
   kNuisRHCNuMuFlux04,
   kNuisRHCNuMuFlux05,
   kNuisRHCNuMuFlux06,
   kNuisRHCNuMuFlux07,
   kNuisRHCNuMuFlux08,
   kNuisRHCNuMuFlux09,
   kNuisRHCNuMuFlux10,
   kNuisRHCNuMuFlux11,
   kNuisRHCNuMuFlux12,
   kNuisRHCNuMuFlux13,
   kNuisRHCNuMuFlux14,
   kNuisRHCNuMuFlux15,
   kNuisRHCNuMuFlux16,
   kNuisRHCNuMuFlux17,
   kNuisRHCNuMuFlux18,
   kNuisRHCNuMuBarFlux00,
   kNuisRHCNuMuBarFlux01,
   kNuisRHCNuMuBarFlux02,
   kNuisRHCNuMuBarFlux03,
   kNuisRHCNuMuBarFlux04,
   kNuisRHCNuMuBarFlux05,
   kNuisRHCNuMuBarFlux06,
   kNuisRHCNuMuBarFlux07,
   kNuisRHCNuMuBarFlux08,
   kNuisRHCNuMuBarFlux09,
   kNuisRHCNuMuBarFlux10,
   kNuisRHCNuMuBarFlux11,
   kNuisRHCNuMuBarFlux12,
   kNuisRHCNuMuBarFlux13,
   kNuisRHCNuMuBarFlux14,
   kNuisRHCNuMuBarFlux15,
   kNuisRHCNuMuBarFlux16,
   kNuisRHCNuMuBarFlux17,
   kNuisRHCNuMuBarFlux18,
   kNuisRHCNuEFlux00,
   kNuisRHCNuEFlux01,
   kNuisRHCNuEFlux02,
   kNuisRHCNuEFlux03,
   kNuisRHCNuEFlux04,
   kNuisRHCNuEFlux05,
   kNuisRHCNuEFlux06,
   kNuisRHCNuEBarFlux00,
   kNuisRHCNuEBarFlux01,
   kNuisRHCNuEBarFlux02,
   kNuisRHCNuEBarFlux03,
   kNuisRHCNuEBarFlux04,
   kNuisRHCNuEBarFlux05,
   kNuisRHCNuEBarFlux06,
   // Cross-sections
#if INT_MODEL == 1
   kNuisNormCCQE, 
   kNuisNormCC1piC,
   kNuisNormCC1pi0,
#elif INT_MODEL == 2
   kNuisIntNuCCQE1       ,
   kNuisIntNuCCQE2       ,
   kNuisIntNuCCQE3       ,
   kNuisIntNuBarCCQE1    ,
   kNuisIntNuBarCCQE2    ,
   kNuisIntNuBarCCQE3    ,
   kNuisIntNuCC1piz1     ,
   kNuisIntNuCC1piz2     ,
   kNuisIntNuCC1piz3     ,
   kNuisIntNuCC1pic1     ,
   kNuisIntNuCC1pic2     ,
   kNuisIntNuCC1pic3     ,
   kNuisIntNuBarCC1piz1  ,
   kNuisIntNuBarCC1piz2  ,
   kNuisIntNuBarCC1piz3  ,
   kNuisIntNuBarCC1pic1  ,
   kNuisIntNuBarCC1pic2  ,
   kNuisIntNuBarCC1pic3  ,
#else
  static_assert(!"FitParams: INT_MODEL not supported.");
#endif //INT_MODEL
   kNuisNormCCoth, 
   kNuisNormNC,
   kNuisRatioNuENuMu,
   // Detector systematics
   kNuisEffNuMuCC1trkQE,
   kNuisEffNuMuCC2trkQE,
   kNuisEffNuMuCC1piC,
   kNuisEffNuMuCC1pi0,
   kNuisEffNuMuCC1piC1pi0,
   kNuisEffNuMuCCoth,  
   kNuisEffNuECC,      
   kNuisEffNuMuCCWSgn, 
   kNuisEffNC            
};

//
// ...........................................................................
// The following arrays specify the Etrue dependence of each systematic
// ...........................................................................
//

// Has true kinematic dependence
static const bool kFitParamTrueKinematicDependence[kNFitParams] = 
{
   // FHC flux
   true,   // kNuisFHCNuMuFlux00
   true,   // kNuisFHCNuMuFlux01
   true,   // kNuisFHCNuMuFlux02
   true,   // kNuisFHCNuMuFlux03
   true,   // kNuisFHCNuMuFlux04
   true,   // kNuisFHCNuMuFlux05
   true,   // kNuisFHCNuMuFlux06
   true,   // kNuisFHCNuMuFlux07
   true,   // kNuisFHCNuMuFlux08
   true,   // kNuisFHCNuMuFlux09
   true,   // kNuisFHCNuMuFlux10
   true,   // kNuisFHCNuMuFlux11
   true,   // kNuisFHCNuMuFlux12
   true,   // kNuisFHCNuMuFlux13
   true,   // kNuisFHCNuMuFlux14
   true,   // kNuisFHCNuMuFlux15
   true,   // kNuisFHCNuMuFlux16
   true,   // kNuisFHCNuMuFlux17
   true,   // kNuisFHCNuMuFlux18
   true,   // kNuisFHCNuMuBarFlux00
   true,   // kNuisFHCNuMuBarFlux01
   true,   // kNuisFHCNuMuBarFlux02
   true,   // kNuisFHCNuMuBarFlux03
   true,   // kNuisFHCNuMuBarFlux04
   true,   // kNuisFHCNuMuBarFlux05
   true,   // kNuisFHCNuMuBarFlux06
   true,   // kNuisFHCNuMuBarFlux07
   true,   // kNuisFHCNuMuBarFlux08
   true,   // kNuisFHCNuMuBarFlux09
   true,   // kNuisFHCNuMuBarFlux10
   true,   // kNuisFHCNuMuBarFlux11
   true,   // kNuisFHCNuMuBarFlux12
   true,   // kNuisFHCNuMuBarFlux13
   true,   // kNuisFHCNuMuBarFlux14
   true,   // kNuisFHCNuMuBarFlux15
   true,   // kNuisFHCNuMuBarFlux16
   true,   // kNuisFHCNuMuBarFlux17
   true,   // kNuisFHCNuMuBarFlux18
   true,   // kNuisFHCNuEFlux00
   true,   // kNuisFHCNuEFlux01
   true,   // kNuisFHCNuEFlux02
   true,   // kNuisFHCNuEFlux03
   true,   // kNuisFHCNuEFlux04
   true,   // kNuisFHCNuEFlux05
   true,   // kNuisFHCNuEFlux06
   true,   // kNuisFHCNuEBarFlux00
   true,   // kNuisFHCNuEBarFlux01
   true,   // kNuisFHCNuEBarFlux02
   true,   // kNuisFHCNuEBarFlux03
   true,   // kNuisFHCNuEBarFlux04
   true,   // kNuisFHCNuEBarFlux05
   true,   // kNuisFHCNuEBarFlux06
   // RHC flux
   true,   // kNuisRHCNuMuFlux00
   true,   // kNuisRHCNuMuFlux01
   true,   // kNuisRHCNuMuFlux02
   true,   // kNuisRHCNuMuFlux03
   true,   // kNuisRHCNuMuFlux04
   true,   // kNuisRHCNuMuFlux05
   true,   // kNuisRHCNuMuFlux06
   true,   // kNuisRHCNuMuFlux07
   true,   // kNuisRHCNuMuFlux08
   true,   // kNuisRHCNuMuFlux09
   true,   // kNuisRHCNuMuFlux10
   true,   // kNuisRHCNuMuFlux11
   true,   // kNuisRHCNuMuFlux12
   true,   // kNuisRHCNuMuFlux13
   true,   // kNuisRHCNuMuFlux14
   true,   // kNuisRHCNuMuFlux15
   true,   // kNuisRHCNuMuFlux16
   true,   // kNuisRHCNuMuFlux17
   true,   // kNuisRHCNuMuFlux18
   true,   // kNuisRHCNuMuBarFlux00
   true,   // kNuisRHCNuMuBarFlux01
   true,   // kNuisRHCNuMuBarFlux02
   true,   // kNuisRHCNuMuBarFlux03
   true,   // kNuisRHCNuMuBarFlux04
   true,   // kNuisRHCNuMuBarFlux05
   true,   // kNuisRHCNuMuBarFlux06
   true,   // kNuisRHCNuMuBarFlux07
   true,   // kNuisRHCNuMuBarFlux08
   true,   // kNuisRHCNuMuBarFlux09
   true,   // kNuisRHCNuMuBarFlux10
   true,   // kNuisRHCNuMuBarFlux11
   true,   // kNuisRHCNuMuBarFlux12
   true,   // kNuisRHCNuMuBarFlux13
   true,   // kNuisRHCNuMuBarFlux14
   true,   // kNuisRHCNuMuBarFlux15
   true,   // kNuisRHCNuMuBarFlux16
   true,   // kNuisRHCNuMuBarFlux17
   true,   // kNuisRHCNuMuBarFlux18
   true,   // kNuisRHCNuEFlux00
   true,   // kNuisRHCNuEFlux01
   true,   // kNuisRHCNuEFlux02
   true,   // kNuisRHCNuEFlux03
   true,   // kNuisRHCNuEFlux04
   true,   // kNuisRHCNuEFlux05
   true,   // kNuisRHCNuEFlux06
   true,   // kNuisRHCNuEBarFlux00
   true,   // kNuisRHCNuEBarFlux01
   true,   // kNuisRHCNuEBarFlux02
   true,   // kNuisRHCNuEBarFlux03
   true,   // kNuisRHCNuEBarFlux04
   true,   // kNuisRHCNuEBarFlux05
   true,   // kNuisRHCNuEBarFlux06
   // Cross-sections
#if INT_MODEL==1
   false,  // kNuisNormCCQE 
   false,  // kNuisNormCC1piC
   false,  // kNuisNormCC1pi0
#elif INT_MODEL==2
   true,   //kNuisIntNuCCQE1       
   true,   //kNuisIntNuCCQE2       
   true,   //kNuisIntNuCCQE3       
   true,   //kNuisIntNuBarCCQE1    
   true,   //kNuisIntNuBarCCQE2    
   true,   //kNuisIntNuBarCCQE3    
   true,   //kNuisIntNuCC1piz1     
   true,   //kNuisIntNuCC1piz2     
   true,   //kNuisIntNuCC1piz3     
   true,   //kNuisIntNuCC1pic1     
   true,   //kNuisIntNuCC1pic2     
   true,   //kNuisIntNuCC1pic3     
   true,   //kNuisIntNuBarCC1piz1  
   true,   //kNuisIntNuBarCC1piz2  
   true,   //kNuisIntNuBarCC1piz3  
   true,   //kNuisIntNuBarCC1pic1  
   true,   //kNuisIntNuBarCC1pic2  
   true,   //kNuisIntNuBarCC1pic3  
#else
  static_assert(!"FitParams: INT_MODEL not supported.");
#endif //INT_MODEL
   false,  // kNuisNormCCoth
   false,  // kNuisNormNC
   false,  // kNuisRatioNuENuMu
   // Detector systematics
   false,  // kNuisEffNuMuCC1trkQE
   false,  // kNuisEffNuMuCC2trkQE
   false,  // kNuisEffNuMuCC1piC
   false,  // kNuisEffNuMuCC1pi0
   false,  // kNuisEffNuMuCC1piC1pi0
   false,  // kNuisEffNuMuCCoth  
   false,  // kNuisEffNuECC      
   false,  // kNuisEffNuMuCCWSgn 
   false   // kNuisEffNC            
};

#if INT_MODEL==2
static const double kIntBinEdgeQ2true1 = kQ2trueBinEdges[1];
static const double kIntBinEdgeQ2true2 = kQ2trueBinEdges[2];
#endif
static const double kQ2trueMax      = kQ2trueBinEdges[3];

// Which is the true energy range?
static const double kFitParamEtrueRange[kNFitParams][2] = 
{
  // Emin, Emax
   // FHC flux
   {  0.0,  0.5},        // kNuisFHCNuMuFlux00
   {  0.5,  1.0},        // kNuisFHCNuMuFlux01
   {  1.0,  1.5},        // kNuisFHCNuMuFlux02
   {  1.5,  2.0},        // kNuisFHCNuMuFlux03
   {  2.0,  2.5},        // kNuisFHCNuMuFlux04
   {  2.5,  3.0},        // kNuisFHCNuMuFlux05
   {  3.0,  3.5},        // kNuisFHCNuMuFlux06
   {  3.5,  4.0},        // kNuisFHCNuMuFlux07
   {  4.0,  4.5},        // kNuisFHCNuMuFlux08
   {  4.5,  5.0},        // kNuisFHCNuMuFlux09
   {  5.0,  5.5},        // kNuisFHCNuMuFlux10
   {  5.5,  6.0},        // kNuisFHCNuMuFlux11
   {  6.0,  7.0},        // kNuisFHCNuMuFlux12
   {  7.0,  8.0},        // kNuisFHCNuMuFlux13
   {  8.0, 12.0},        // kNuisFHCNuMuFlux14
   { 12.0, 16.0},        // kNuisFHCNuMuFlux15
   { 16.0, 20.0},        // kNuisFHCNuMuFlux16
   { 20.0, 40.0},        // kNuisFHCNuMuFlux17
   { 40.0, kEtrueMax },  // kNuisFHCNuMuFlux18
   {  0.0,  0.5},        // kNuisFHCNuMuBarFlux00
   {  0.5,  1.0},        // kNuisFHCNuMuBarFlux01
   {  1.0,  1.5},        // kNuisFHCNuMuBarFlux02
   {  1.5,  2.0},        // kNuisFHCNuMuBarFlux03
   {  2.0,  2.5},        // kNuisFHCNuMuBarFlux04
   {  2.5,  3.0},        // kNuisFHCNuMuBarFlux05
   {  3.0,  3.5},        // kNuisFHCNuMuBarFlux06
   {  3.5,  4.0},        // kNuisFHCNuMuBarFlux07
   {  4.0,  4.5},        // kNuisFHCNuMuBarFlux08
   {  4.5,  5.0},        // kNuisFHCNuMuBarFlux09
   {  5.0,  5.5},        // kNuisFHCNuMuBarFlux10
   {  5.5,  6.0},        // kNuisFHCNuMuBarFlux11
   {  6.0,  7.0},        // kNuisFHCNuMuBarFlux12
   {  7.0,  8.0},        // kNuisFHCNuMuBarFlux13
   {  8.0, 12.0},        // kNuisFHCNuMuBarFlux14
   { 12.0, 16.0},        // kNuisFHCNuMuBarFlux15
   { 16.0, 20.0},        // kNuisFHCNuMuBarFlux16
   { 20.0, 40.0},        // kNuisFHCNuMuBarFlux17
   { 40.0, kEtrueMax },  // kNuisFHCNuMuBarFlux18
   {  0.0,  2.0},        // kNuisFHCNuEFlux00
   {  2.0,  4.0},        // kNuisFHCNuEFlux01
   {  4.0,  6.0},        // kNuisFHCNuEFlux02
   {  6.0,  8.0},        // kNuisFHCNuEFlux03
   {  8.0, 10.0},        // kNuisFHCNuEFlux04
   { 10.0, 20.0},        // kNuisFHCNuEFlux05
   { 20.0, kEtrueMax },  // kNuisFHCNuEFlux06
   {  0.0,  2.0},        // kNuisFHCNuEBarFlux00
   {  2.0,  4.0},        // kNuisFHCNuEBarFlux01
   {  4.0,  6.0},        // kNuisFHCNuEBarFlux02
   {  6.0,  8.0},        // kNuisFHCNuEBarFlux03
   {  8.0, 10.0},        // kNuisFHCNuEBarFlux04
   { 10.0, 20.0},        // kNuisFHCNuEBarFlux05
   { 20.0, kEtrueMax },  // kNuisFHCNuEBarFlux06
   // RHC flux
   {  0.0,  0.5},        // kNuisRHCNuMuFlux00
   {  0.5,  1.0},        // kNuisRHCNuMuFlux01
   {  1.0,  1.5},        // kNuisRHCNuMuFlux02
   {  1.5,  2.0},        // kNuisRHCNuMuFlux03
   {  2.0,  2.5},        // kNuisRHCNuMuFlux04
   {  2.5,  3.0},        // kNuisRHCNuMuFlux05
   {  3.0,  3.5},        // kNuisRHCNuMuFlux06
   {  3.5,  4.0},        // kNuisRHCNuMuFlux07
   {  4.0,  4.5},        // kNuisRHCNuMuFlux08
   {  4.5,  5.0},        // kNuisRHCNuMuFlux09
   {  5.0,  5.5},        // kNuisRHCNuMuFlux10
   {  5.5,  6.0},        // kNuisRHCNuMuFlux11
   {  6.0,  7.0},        // kNuisRHCNuMuFlux12
   {  7.0,  8.0},        // kNuisRHCNuMuFlux13
   {  8.0, 12.0},        // kNuisRHCNuMuFlux14
   { 12.0, 16.0},        // kNuisRHCNuMuFlux15
   { 16.0, 20.0},        // kNuisRHCNuMuFlux16
   { 20.0, 40.0},        // kNuisRHCNuMuFlux17
   { 40.0, kEtrueMax },  // kNuisRHCNuMuFlux18
   {  0.0,  0.5},        // kNuisRHCNuMuBarFlux00
   {  0.5,  1.0},        // kNuisRHCNuMuBarFlux01
   {  1.0,  1.5},        // kNuisRHCNuMuBarFlux02
   {  1.5,  2.0},        // kNuisRHCNuMuBarFlux03
   {  2.0,  2.5},        // kNuisRHCNuMuBarFlux04
   {  2.5,  3.0},        // kNuisRHCNuMuBarFlux05
   {  3.0,  3.5},        // kNuisRHCNuMuBarFlux06
   {  3.5,  4.0},        // kNuisRHCNuMuBarFlux07
   {  4.0,  4.5},        // kNuisRHCNuMuBarFlux08
   {  4.5,  5.0},        // kNuisRHCNuMuBarFlux09
   {  5.0,  5.5},        // kNuisRHCNuMuBarFlux10
   {  5.5,  6.0},        // kNuisRHCNuMuBarFlux11
   {  6.0,  7.0},        // kNuisRHCNuMuBarFlux12
   {  7.0,  8.0},        // kNuisRHCNuMuBarFlux13
   {  8.0, 12.0},        // kNuisRHCNuMuBarFlux14
   { 12.0, 16.0},        // kNuisRHCNuMuBarFlux15
   { 16.0, 20.0},        // kNuisRHCNuMuBarFlux16
   { 20.0, 40.0},        // kNuisRHCNuMuBarFlux17
   { 40.0, kEtrueMax },  // kNuisRHCNuMuBarFlux18
   {  0.0,  2.0},        // kNuisRHCNuEFlux00
   {  2.0,  4.0},        // kNuisRHCNuEFlux01
   {  4.0,  6.0},        // kNuisRHCNuEFlux02
   {  6.0,  8.0},        // kNuisRHCNuEFlux03
   {  8.0, 10.0},        // kNuisRHCNuEFlux04
   { 10.0, 20.0},        // kNuisRHCNuEFlux05
   { 20.0, kEtrueMax },  // kNuisRHCNuEFlux06
   {  0.0,  2.0},        // kNuisRHCNuEBarFlux00
   {  2.0,  4.0},        // kNuisRHCNuEBarFlux01
   {  4.0,  6.0},        // kNuisRHCNuEBarFlux02
   {  6.0,  8.0},        // kNuisRHCNuEBarFlux03
   {  8.0, 10.0},        // kNuisRHCNuEBarFlux04
   { 10.0, 20.0},        // kNuisRHCNuEBarFlux05
   { 20.0, kEtrueMax },  // kNuisRHCNuEBarFlux06
   // Cross-sections
#if INT_MODEL==1
   {  0.0, kEtrueMax},   // kNuisNormCCQE 
   {  0.0, kEtrueMax},   // kNuisNormCC1piC
   {  0.0, kEtrueMax},   // kNuisNormCC1pi0
#elif INT_MODEL==2
   {  0.0   , kEtrueMax }, //kNuisIntNuCCQE1       
   {  0.0   , kEtrueMax }, //kNuisIntNuCCQE2       
   {  0.0   , kEtrueMax }, //kNuisIntNuCCQE3       
   {  0.0   , kEtrueMax }, //kNuisIntNuBarCCQE1    
   {  0.0   , kEtrueMax }, //kNuisIntNuBarCCQE2    
   {  0.0   , kEtrueMax }, //kNuisIntNuBarCCQE3    
   {  0.0   , kEtrueMax }, //kNuisIntNuCC1piz1     
   {  0.0   , kEtrueMax }, //kNuisIntNuCC1piz2     
   {  0.0   , kEtrueMax }, //kNuisIntNuCC1piz3     
   {  0.0   , kEtrueMax }, //kNuisIntNuCC1pic1     
   {  0.0   , kEtrueMax }, //kNuisIntNuCC1pic2     
   {  0.0   , kEtrueMax }, //kNuisIntNuCC1pic3     
   {  0.0   , kEtrueMax }, //kNuisIntNuBarCC1piz1  
   {  0.0   , kEtrueMax }, //kNuisIntNuBarCC1piz2  
   {  0.0   , kEtrueMax }, //kNuisIntNuBarCC1piz3  
   {  0.0   , kEtrueMax }, //kNuisIntNuBarCC1pic1  
   {  0.0   , kEtrueMax }, //kNuisIntNuBarCC1pic2  
   {  0.0   , kEtrueMax }, //kNuisIntNuBarCC1pic3  
#else
  static_assert(!"FitParams: INT_MODEL not supported.");
#endif //INT_MODEL
   {  0.0, kEtrueMax},   // kNuisNormCCoth
   {  0.0, kEtrueMax},   // kNuisNormNC
   {  0.0, kEtrueMax},   // kNuisRatioNuENuMu
   // Detector systematics
   {  0.0, kEtrueMax},   // kNuisEffNuMuCC1trkQE
   {  0.0, kEtrueMax},   // kNuisEffNuMuCC2trkQE
   {  0.0, kEtrueMax},   // kNuisEffNuMuCC1piC
   {  0.0, kEtrueMax},   // kNuisEffNuMuCC1pi0
   {  0.0, kEtrueMax},   // kNuisEffNuMuCC1piC1pi0
   {  0.0, kEtrueMax},   // kNuisEffNuMuCCoth  
   {  0.0, kEtrueMax},   // kNuisEffNuECC      
   {  0.0, kEtrueMax},   // kNuisEffNuMuCCWSgn 
   {  0.0, kEtrueMax}    // kNuisEffNC                        
};

// Which is the true Q2 range?
static const double kFitParamQ2Range[kNFitParams][2] = 
{
   // Q2 min, Q2 max
   // FHC flux
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux00
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux01
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux02
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux03
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux04
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux05
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux06
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux07
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux08
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux09
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux10
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux11
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux12
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux13
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux14
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux15
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux16
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux17
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFlux18
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux00
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux01
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux02
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux03
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux04
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux05
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux06
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux07
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux08
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux09
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux10
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux11
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux12
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux13
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux14
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux15
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux16
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux17
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFlux18
   { 0.0, kQ2trueMax }, // kNuisFHCNuEFlux00
   { 0.0, kQ2trueMax }, // kNuisFHCNuEFlux01
   { 0.0, kQ2trueMax }, // kNuisFHCNuEFlux02
   { 0.0, kQ2trueMax }, // kNuisFHCNuEFlux03
   { 0.0, kQ2trueMax }, // kNuisFHCNuEFlux04
   { 0.0, kQ2trueMax }, // kNuisFHCNuEFlux05
   { 0.0, kQ2trueMax }, // kNuisFHCNuEFlux06
   { 0.0, kQ2trueMax }, // kNuisFHCNuEBarFlux00
   { 0.0, kQ2trueMax }, // kNuisFHCNuEBarFlux01
   { 0.0, kQ2trueMax }, // kNuisFHCNuEBarFlux02
   { 0.0, kQ2trueMax }, // kNuisFHCNuEBarFlux03
   { 0.0, kQ2trueMax }, // kNuisFHCNuEBarFlux04
   { 0.0, kQ2trueMax }, // kNuisFHCNuEBarFlux05
   { 0.0, kQ2trueMax }, // kNuisFHCNuEBarFlux06
   // RHC flux
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux00
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux01
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux02
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux03
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux04
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux05
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux06
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux07
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux08
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux09
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux10
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux11
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux12
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux13
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux14
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux15
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux16
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux17
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFlux18
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux00
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux01
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux02
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux03
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux04
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux05
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux06
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux07
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux08
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux09
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux10
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux11
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux12
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux13
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux14
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux15
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux16
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux17
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFlux18
   { 0.0, kQ2trueMax },  // kNuisRHCNuEFlux00
   { 0.0, kQ2trueMax },  // kNuisRHCNuEFlux01
   { 0.0, kQ2trueMax },  // kNuisRHCNuEFlux02
   { 0.0, kQ2trueMax },  // kNuisRHCNuEFlux03
   { 0.0, kQ2trueMax },  // kNuisRHCNuEFlux04
   { 0.0, kQ2trueMax },  // kNuisRHCNuEFlux05
   { 0.0, kQ2trueMax },  // kNuisRHCNuEFlux06
   { 0.0, kQ2trueMax },  // kNuisRHCNuEBarFlux00
   { 0.0, kQ2trueMax },  // kNuisRHCNuEBarFlux01
   { 0.0, kQ2trueMax },  // kNuisRHCNuEBarFlux02
   { 0.0, kQ2trueMax },  // kNuisRHCNuEBarFlux03
   { 0.0, kQ2trueMax },  // kNuisRHCNuEBarFlux04
   { 0.0, kQ2trueMax },  // kNuisRHCNuEBarFlux05
   { 0.0, kQ2trueMax },  // kNuisRHCNuEBarFlux06
   // Cross-sections
#if INT_MODEL==1
   {  0.0, kQ2trueMax},   // kNuisNormCCQE 
   {  0.0, kQ2trueMax},   // kNuisNormCC1piC
   {  0.0, kQ2trueMax},   // kNuisNormCC1pi0
#elif INT_MODEL==2
   {  0.0               , kIntBinEdgeQ2true1}, //kNuisIntNuCCQE1       
   {  kIntBinEdgeQ2true1, kIntBinEdgeQ2true2}, //kNuisIntNuCCQE2       
   {  kIntBinEdgeQ2true2, kQ2trueMax        }, //kNuisIntNuCCQE3       
   {  0.0               , kIntBinEdgeQ2true1}, //kNuisIntNuBarCCQE1    
   {  kIntBinEdgeQ2true1, kIntBinEdgeQ2true2}, //kNuisIntNuBarCCQE2    
   {  kIntBinEdgeQ2true2, kQ2trueMax        }, //kNuisIntNuBarCCQE3    
   {  0.0               , kIntBinEdgeQ2true1}, //kNuisIntNuCC1piz1     
   {  kIntBinEdgeQ2true1, kIntBinEdgeQ2true2}, //kNuisIntNuCC1piz2     
   {  kIntBinEdgeQ2true2, kQ2trueMax        }, //kNuisIntNuCC1piz3     
   {  0.0               , kIntBinEdgeQ2true1}, //kNuisIntNuCC1pic1     
   {  kIntBinEdgeQ2true1, kIntBinEdgeQ2true2}, //kNuisIntNuCC1pic2     
   {  kIntBinEdgeQ2true2, kQ2trueMax        }, //kNuisIntNuCC1pic3     
   {  0.0               , kIntBinEdgeQ2true1}, //kNuisIntNuBarCC1piz1  
   {  kIntBinEdgeQ2true1, kIntBinEdgeQ2true2}, //kNuisIntNuBarCC1piz2  
   {  kIntBinEdgeQ2true2, kQ2trueMax        }, //kNuisIntNuBarCC1piz3  
   {  0.0               , kIntBinEdgeQ2true1}, //kNuisIntNuBarCC1pic1  
   {  kIntBinEdgeQ2true1, kIntBinEdgeQ2true2}, //kNuisIntNuBarCC1pic2  
   {  kIntBinEdgeQ2true2, kQ2trueMax        }, //kNuisIntNuBarCC1pic3  
#else
  static_assert(!"FitParams: INT_MODEL not supported.");
#endif //INT_MODEL
   {  0.0, kQ2trueMax},   // kNuisNormCCoth
   {  0.0, kQ2trueMax},   // kNuisNormNC
   {  0.0, kQ2trueMax},   // kNuisRatioNuENuMu
   // Detector systematics
   {  0.0, kQ2trueMax},   // kNuisEffNuMuCC1trkQE
   {  0.0, kQ2trueMax},   // kNuisEffNuMuCC2trkQE
   {  0.0, kQ2trueMax},   // kNuisEffNuMuCC1piC
   {  0.0, kQ2trueMax},   // kNuisEffNuMuCC1pi0
   {  0.0, kQ2trueMax},   // kNuisEffNuMuCC1piC1pi0
   {  0.0, kQ2trueMax},   // kNuisEffNuMuCCoth  
   {  0.0, kQ2trueMax},   // kNuisEffNuECC      
   {  0.0, kQ2trueMax},   // kNuisEffNuMuCCWSgn 
   {  0.0, kQ2trueMax}    // kNuisEffNC                        
};

//
// ...........................................................................
// The following arrays help classify physics parameters in groups
// ...........................................................................
//

static const FitParamGroup_t kFitParamGroup[kNFitParams] =
{
   // FHC flux
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux00
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux01
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux02
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux03
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux04
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux05
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux06
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux07
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux08
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux09
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux10
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux11
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux12
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux13
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux14
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux15
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux16
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux17
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFlux18
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux00
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux01
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux02
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux03
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux04
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux05
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux06
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux07
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux08
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux09
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux10
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux11
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux12
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux13
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux14
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux15
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux16
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux17
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFlux18
   kpgFHCNuEFlux,      // kNuisFHCNuEFlux00
   kpgFHCNuEFlux,      // kNuisFHCNuEFlux01
   kpgFHCNuEFlux,      // kNuisFHCNuEFlux02
   kpgFHCNuEFlux,      // kNuisFHCNuEFlux03
   kpgFHCNuEFlux,      // kNuisFHCNuEFlux04
   kpgFHCNuEFlux,      // kNuisFHCNuEFlux05
   kpgFHCNuEFlux,      // kNuisFHCNuEFlux06
   kpgFHCNuEBarFlux,   // kNuisFHCNuEBarFlux00
   kpgFHCNuEBarFlux,   // kNuisFHCNuEBarFlux01
   kpgFHCNuEBarFlux,   // kNuisFHCNuEBarFlux02
   kpgFHCNuEBarFlux,   // kNuisFHCNuEBarFlux03
   kpgFHCNuEBarFlux,   // kNuisFHCNuEBarFlux04
   kpgFHCNuEBarFlux,   // kNuisFHCNuEBarFlux05
   kpgFHCNuEBarFlux,   // kNuisFHCNuEBarFlux06
   // RHC flux
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux00
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux01
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux02
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux03
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux04
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux05
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux06
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux07
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux08
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux09
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux10
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux11
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux12
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux13
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux14
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux15
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux16
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux17
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFlux18
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux00
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux01
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux02
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux03
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux04
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux05
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux06
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux07
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux08
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux09
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux10
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux11
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux12
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux13
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux14
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux15
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux16
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux17
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFlux18
   kpgRHCNuEFlux,      // kNuisRHCNuEFlux00
   kpgRHCNuEFlux,      // kNuisRHCNuEFlux01
   kpgRHCNuEFlux,      // kNuisRHCNuEFlux02
   kpgRHCNuEFlux,      // kNuisRHCNuEFlux03
   kpgRHCNuEFlux,      // kNuisRHCNuEFlux04
   kpgRHCNuEFlux,      // kNuisRHCNuEFlux05
   kpgRHCNuEFlux,      // kNuisRHCNuEFlux06
   kpgRHCNuEBarFlux,   // kNuisRHCNuEBarFlux00
   kpgRHCNuEBarFlux,   // kNuisRHCNuEBarFlux01
   kpgRHCNuEBarFlux,   // kNuisRHCNuEBarFlux02
   kpgRHCNuEBarFlux,   // kNuisRHCNuEBarFlux03
   kpgRHCNuEBarFlux,   // kNuisRHCNuEBarFlux04
   kpgRHCNuEBarFlux,   // kNuisRHCNuEBarFlux05
   kpgRHCNuEBarFlux,   // kNuisRHCNuEBarFlux06
   // Cross-sections
#if INT_MODEL==1
   kpgXSec,            // kNuisNormCCQE 
   kpgXSec,            // kNuisNormCC1piC
   kpgXSec,            // kNuisNormCC1pi0
#elif INT_MODEL==2
   kpgXSec,            //kNuisIntNuCCQE1      
   kpgXSec,            //kNuisIntNuCCQE2      
   kpgXSec,            //kNuisIntNuCCQE3      
   kpgXSec,            //kNuisIntNuBarCCQE1   
   kpgXSec,            //kNuisIntNuBarCCQE2   
   kpgXSec,            //kNuisIntNuBarCCQE3   
   kpgXSec,            //kNuisIntNuCC1piz1    
   kpgXSec,            //kNuisIntNuCC1piz2    
   kpgXSec,            //kNuisIntNuCC1piz3    
   kpgXSec,            //kNuisIntNuCC1pic1    
   kpgXSec,            //kNuisIntNuCC1pic2    
   kpgXSec,            //kNuisIntNuCC1pic3    
   kpgXSec,            //kNuisIntNuBarCC1piz1 
   kpgXSec,            //kNuisIntNuBarCC1piz2 
   kpgXSec,            //kNuisIntNuBarCC1piz3 
   kpgXSec,            //kNuisIntNuBarCC1pic1 
   kpgXSec,            //kNuisIntNuBarCC1pic2 
   kpgXSec,            //kNuisIntNuBarCC1pic3 
#else
  static_assert(!"FitParams: INT_MODEL not supported.");
#endif //INT_MODEL
   kpgXSec,            // kNuisNormCCoth
   kpgXSec,            // kNuisNormNC
   kpgXSec,            // kNuisRatioNuENuMu
   // Detector systematics
   kpgDetector,        // kNuisEffNuMuCC1trkQE
   kpgDetector,        // kNuisEffNuMuCC2trkQE
   kpgDetector,        // kNuisEffNuMuCC1piC
   kpgDetector,        // kNuisEffNuMuCC1pi0
   kpgDetector,        // kNuisEffNuMuCC1piC1pi0
   kpgDetector,        // kNuisEffNuMuCCoth  
   kpgDetector,        // kNuisEffNuECC      
   kpgDetector,        // kNuisEffNuMuCCWSgn 
   kpgDetector         // kNuisEffNC            
};

// Is this a neutrino flux related parameter?
//
static const bool kFitIsNuFluxRelated[kNFitParams] = 
{
   // FHC flux
   true,  // kNuisFHCNuMuFlux00
   true,  // kNuisFHCNuMuFlux01
   true,  // kNuisFHCNuMuFlux02
   true,  // kNuisFHCNuMuFlux03
   true,  // kNuisFHCNuMuFlux04
   true,  // kNuisFHCNuMuFlux05
   true,  // kNuisFHCNuMuFlux06
   true,  // kNuisFHCNuMuFlux07
   true,  // kNuisFHCNuMuFlux08
   true,  // kNuisFHCNuMuFlux09
   true,  // kNuisFHCNuMuFlux10
   true,  // kNuisFHCNuMuFlux11
   true,  // kNuisFHCNuMuFlux12
   true,  // kNuisFHCNuMuFlux13
   true,  // kNuisFHCNuMuFlux14
   true,  // kNuisFHCNuMuFlux15
   true,  // kNuisFHCNuMuFlux16
   true,  // kNuisFHCNuMuFlux17
   true,  // kNuisFHCNuMuFlux18
   true,  // kNuisFHCNuMuBarFlux00
   true,  // kNuisFHCNuMuBarFlux01
   true,  // kNuisFHCNuMuBarFlux02
   true,  // kNuisFHCNuMuBarFlux03
   true,  // kNuisFHCNuMuBarFlux04
   true,  // kNuisFHCNuMuBarFlux05
   true,  // kNuisFHCNuMuBarFlux06
   true,  // kNuisFHCNuMuBarFlux07
   true,  // kNuisFHCNuMuBarFlux08
   true,  // kNuisFHCNuMuBarFlux09
   true,  // kNuisFHCNuMuBarFlux10
   true,  // kNuisFHCNuMuBarFlux11
   true,  // kNuisFHCNuMuBarFlux12
   true,  // kNuisFHCNuMuBarFlux13
   true,  // kNuisFHCNuMuBarFlux14
   true,  // kNuisFHCNuMuBarFlux15
   true,  // kNuisFHCNuMuBarFlux16
   true,  // kNuisFHCNuMuBarFlux17
   true,  // kNuisFHCNuMuBarFlux18
   true,  // kNuisFHCNuEFlux00
   true,  // kNuisFHCNuEFlux01
   true,  // kNuisFHCNuEFlux02
   true,  // kNuisFHCNuEFlux03
   true,  // kNuisFHCNuEFlux04
   true,  // kNuisFHCNuEFlux05
   true,  // kNuisFHCNuEFlux06
   true,  // kNuisFHCNuEBarFlux00
   true,  // kNuisFHCNuEBarFlux01
   true,  // kNuisFHCNuEBarFlux02
   true,  // kNuisFHCNuEBarFlux03
   true,  // kNuisFHCNuEBarFlux04
   true,  // kNuisFHCNuEBarFlux05
   true,  // kNuisFHCNuEBarFlux06
   // RHC flux
   true,  // kNuisRHCNuMuFlux00
   true,  // kNuisRHCNuMuFlux01
   true,  // kNuisRHCNuMuFlux02
   true,  // kNuisRHCNuMuFlux03
   true,  // kNuisRHCNuMuFlux04
   true,  // kNuisRHCNuMuFlux05
   true,  // kNuisRHCNuMuFlux06
   true,  // kNuisRHCNuMuFlux07
   true,  // kNuisRHCNuMuFlux08
   true,  // kNuisRHCNuMuFlux09
   true,  // kNuisRHCNuMuFlux10
   true,  // kNuisRHCNuMuFlux11
   true,  // kNuisRHCNuMuFlux12
   true,  // kNuisRHCNuMuFlux13
   true,  // kNuisRHCNuMuFlux14
   true,  // kNuisRHCNuMuFlux15
   true,  // kNuisRHCNuMuFlux16
   true,  // kNuisRHCNuMuFlux17
   true,  // kNuisRHCNuMuFlux18
   true,  // kNuisRHCNuMuBarFlux00
   true,  // kNuisRHCNuMuBarFlux01
   true,  // kNuisRHCNuMuBarFlux02
   true,  // kNuisRHCNuMuBarFlux03
   true,  // kNuisRHCNuMuBarFlux04
   true,  // kNuisRHCNuMuBarFlux05
   true,  // kNuisRHCNuMuBarFlux06
   true,  // kNuisRHCNuMuBarFlux07
   true,  // kNuisRHCNuMuBarFlux08
   true,  // kNuisRHCNuMuBarFlux09
   true,  // kNuisRHCNuMuBarFlux10
   true,  // kNuisRHCNuMuBarFlux11
   true,  // kNuisRHCNuMuBarFlux12
   true,  // kNuisRHCNuMuBarFlux13
   true,  // kNuisRHCNuMuBarFlux14
   true,  // kNuisRHCNuMuBarFlux15
   true,  // kNuisRHCNuMuBarFlux16
   true,  // kNuisRHCNuMuBarFlux17
   true,  // kNuisRHCNuMuBarFlux18
   true,  // kNuisRHCNuEFlux00
   true,  // kNuisRHCNuEFlux01
   true,  // kNuisRHCNuEFlux02
   true,  // kNuisRHCNuEFlux03
   true,  // kNuisRHCNuEFlux04
   true,  // kNuisRHCNuEFlux05
   true,  // kNuisRHCNuEFlux06
   true,  // kNuisRHCNuEBarFlux00
   true,  // kNuisRHCNuEBarFlux01
   true,  // kNuisRHCNuEBarFlux02
   true,  // kNuisRHCNuEBarFlux03
   true,  // kNuisRHCNuEBarFlux04
   true,  // kNuisRHCNuEBarFlux05
   true,  // kNuisRHCNuEBarFlux06
   // Cross-sections
#if INT_MODEL==1
   false, // kNuisNormCCQE 
   false, // kNuisNormCC1piC
   false, // kNuisNormCC1pi0
#elif INT_MODEL==2
   false, //kNuisIntNuCCQE1      
   false, //kNuisIntNuCCQE2      
   false, //kNuisIntNuCCQE3      
   false, //kNuisIntNuBarCCQE1   
   false, //kNuisIntNuBarCCQE2   
   false, //kNuisIntNuBarCCQE3   
   false, //kNuisIntNuCC1piz1    
   false, //kNuisIntNuCC1piz2    
   false, //kNuisIntNuCC1piz3    
   false, //kNuisIntNuCC1pic1    
   false, //kNuisIntNuCC1pic2    
   false, //kNuisIntNuCC1pic3    
   false, //kNuisIntNuBarCC1piz1 
   false, //kNuisIntNuBarCC1piz2 
   false, //kNuisIntNuBarCC1piz3 
   false, //kNuisIntNuBarCC1pic1 
   false, //kNuisIntNuBarCC1pic2 
   false, //kNuisIntNuBarCC1pic3 
#else
  static_assert(!"FitParams: INT_MODEL not supported.");
#endif //INT_MODEL
   false, // kNuisNormCCoth
   false, // kNuisNormNC
   false, // kNuisRatioNuENuMu
   // Detector systematics
   false, // kNuisEffNuMuCC1trkQE
   false, // kNuisEffNuMuCC2trkQE
   false, // kNuisEffNuMuCC1piC
   false, // kNuisEffNuMuCC1pi0
   false, // kNuisEffNuMuCC1piC1pi0
   false, // kNuisEffNuMuCCoth  
   false, // kNuisEffNuECC      
   false, // kNuisEffNuMuCCWSgn 
   false  // kNuisEffNC            
};

// Is this a neutrino interaction model related parameter?
//
static const bool kFitIsNuIntRelated[kNFitParams] = 
{
   // FHC flux
   false, // kNuisFHCNuMuFlux00
   false, // kNuisFHCNuMuFlux01
   false, // kNuisFHCNuMuFlux02
   false, // kNuisFHCNuMuFlux03
   false, // kNuisFHCNuMuFlux04
   false, // kNuisFHCNuMuFlux05
   false, // kNuisFHCNuMuFlux06
   false, // kNuisFHCNuMuFlux07
   false, // kNuisFHCNuMuFlux08
   false, // kNuisFHCNuMuFlux09
   false, // kNuisFHCNuMuFlux10
   false, // kNuisFHCNuMuFlux11
   false, // kNuisFHCNuMuFlux12
   false, // kNuisFHCNuMuFlux13
   false, // kNuisFHCNuMuFlux14
   false, // kNuisFHCNuMuFlux15
   false, // kNuisFHCNuMuFlux16
   false, // kNuisFHCNuMuFlux17
   false, // kNuisFHCNuMuFlux18
   false, // kNuisFHCNuMuBarFlux00
   false, // kNuisFHCNuMuBarFlux01
   false, // kNuisFHCNuMuBarFlux02
   false, // kNuisFHCNuMuBarFlux03
   false, // kNuisFHCNuMuBarFlux04
   false, // kNuisFHCNuMuBarFlux05
   false, // kNuisFHCNuMuBarFlux06
   false, // kNuisFHCNuMuBarFlux07
   false, // kNuisFHCNuMuBarFlux08
   false, // kNuisFHCNuMuBarFlux09
   false, // kNuisFHCNuMuBarFlux10
   false, // kNuisFHCNuMuBarFlux11
   false, // kNuisFHCNuMuBarFlux12
   false, // kNuisFHCNuMuBarFlux13
   false, // kNuisFHCNuMuBarFlux14
   false, // kNuisFHCNuMuBarFlux15
   false, // kNuisFHCNuMuBarFlux16
   false, // kNuisFHCNuMuBarFlux17
   false, // kNuisFHCNuMuBarFlux18
   false, // kNuisFHCNuEFlux00
   false, // kNuisFHCNuEFlux01
   false, // kNuisFHCNuEFlux02
   false, // kNuisFHCNuEFlux03
   false, // kNuisFHCNuEFlux04
   false, // kNuisFHCNuEFlux05
   false, // kNuisFHCNuEFlux06
   false, // kNuisFHCNuEBarFlux00
   false, // kNuisFHCNuEBarFlux01
   false, // kNuisFHCNuEBarFlux02
   false, // kNuisFHCNuEBarFlux03
   false, // kNuisFHCNuEBarFlux04
   false, // kNuisFHCNuEBarFlux05
   false, // kNuisFHCNuEBarFlux06
   // RHC flux
   false, // kNuisRHCNuMuFlux00
   false, // kNuisRHCNuMuFlux01
   false, // kNuisRHCNuMuFlux02
   false, // kNuisRHCNuMuFlux03
   false, // kNuisRHCNuMuFlux04
   false, // kNuisRHCNuMuFlux05
   false, // kNuisRHCNuMuFlux06
   false, // kNuisRHCNuMuFlux07
   false, // kNuisRHCNuMuFlux08
   false, // kNuisRHCNuMuFlux09
   false, // kNuisRHCNuMuFlux10
   false, // kNuisRHCNuMuFlux11
   false, // kNuisRHCNuMuFlux12
   false, // kNuisRHCNuMuFlux13
   false, // kNuisRHCNuMuFlux14
   false, // kNuisRHCNuMuFlux15
   false, // kNuisRHCNuMuFlux16
   false, // kNuisRHCNuMuFlux17
   false, // kNuisRHCNuMuFlux18
   false, // kNuisRHCNuMuBarFlux00
   false, // kNuisRHCNuMuBarFlux01
   false, // kNuisRHCNuMuBarFlux02
   false, // kNuisRHCNuMuBarFlux03
   false, // kNuisRHCNuMuBarFlux04
   false, // kNuisRHCNuMuBarFlux05
   false, // kNuisRHCNuMuBarFlux06
   false, // kNuisRHCNuMuBarFlux07
   false, // kNuisRHCNuMuBarFlux08
   false, // kNuisRHCNuMuBarFlux09
   false, // kNuisRHCNuMuBarFlux10
   false, // kNuisRHCNuMuBarFlux11
   false, // kNuisRHCNuMuBarFlux12
   false, // kNuisRHCNuMuBarFlux13
   false, // kNuisRHCNuMuBarFlux14
   false, // kNuisRHCNuMuBarFlux15
   false, // kNuisRHCNuMuBarFlux16
   false, // kNuisRHCNuMuBarFlux17
   false, // kNuisRHCNuMuBarFlux18
   false, // kNuisRHCNuEFlux00
   false, // kNuisRHCNuEFlux01
   false, // kNuisRHCNuEFlux02
   false, // kNuisRHCNuEFlux03
   false, // kNuisRHCNuEFlux04
   false, // kNuisRHCNuEFlux05
   false, // kNuisRHCNuEFlux06
   false, // kNuisRHCNuEBarFlux00
   false, // kNuisRHCNuEBarFlux01
   false, // kNuisRHCNuEBarFlux02
   false, // kNuisRHCNuEBarFlux03
   false, // kNuisRHCNuEBarFlux04
   false, // kNuisRHCNuEBarFlux05
   false, // kNuisRHCNuEBarFlux06
   // Cross-sections
#if INT_MODEL==1
   true,  // kNuisNormCCQE 
   true,  // kNuisNormCC1piC
   true,  // kNuisNormCC1pi0
#elif INT_MODEL==2
   true,  //kNuisIntNuCCQE1     
   true,  //kNuisIntNuCCQE2     
   true,  //kNuisIntNuCCQE3     
   true,  //kNuisIntNuBarCCQE1  
   true,  //kNuisIntNuBarCCQE2  
   true,  //kNuisIntNuBarCCQE3  
   true,  //kNuisIntNuCC1piz1   
   true,  //kNuisIntNuCC1piz2   
   true,  //kNuisIntNuCC1piz3   
   true,  //kNuisIntNuCC1pic1   
   true,  //kNuisIntNuCC1pic2   
   true,  //kNuisIntNuCC1pic3   
   true,  //kNuisIntNuBarCC1piz1
   true,  //kNuisIntNuBarCC1piz2
   true,  //kNuisIntNuBarCC1piz3
   true,  //kNuisIntNuBarCC1pic1
   true,  //kNuisIntNuBarCC1pic2
   true,  //kNuisIntNuBarCC1pic3
#else
  static_assert(!"AppliedConv: INT_MODEL not supported.");
#endif //INT_MODEL
   true,  // kNuisNormCCoth
   true,  // kNuisNormNC
   true,  // kNuisRatioNuENuMu
   // Detector systematics
   false, // kNuisEffNuMuCC1trkQE
   false, // kNuisEffNuMuCC2trkQE
   false, // kNuisEffNuMuCC1piC
   false, // kNuisEffNuMuCC1pi0
   false, // kNuisEffNuMuCC1piC1pi0
   false, // kNuisEffNuMuCCoth  
   false, // kNuisEffNuECC      
   false, // kNuisEffNuMuCCWSgn 
   false  // kNuisEffNC            
};

// Is this a neutrino detector related parameter?
//
static const bool kFitIsNuDetRelated[kNFitParams] = 
{
   // FHC flux
   false, // kNuisFHCNuMuFlux00
   false, // kNuisFHCNuMuFlux01
   false, // kNuisFHCNuMuFlux02
   false, // kNuisFHCNuMuFlux03
   false, // kNuisFHCNuMuFlux04
   false, // kNuisFHCNuMuFlux05
   false, // kNuisFHCNuMuFlux06
   false, // kNuisFHCNuMuFlux07
   false, // kNuisFHCNuMuFlux08
   false, // kNuisFHCNuMuFlux09
   false, // kNuisFHCNuMuFlux10
   false, // kNuisFHCNuMuFlux11
   false, // kNuisFHCNuMuFlux12
   false, // kNuisFHCNuMuFlux13
   false, // kNuisFHCNuMuFlux14
   false, // kNuisFHCNuMuFlux15
   false, // kNuisFHCNuMuFlux16
   false, // kNuisFHCNuMuFlux17
   false, // kNuisFHCNuMuFlux18
   false, // kNuisFHCNuMuBarFlux00
   false, // kNuisFHCNuMuBarFlux01
   false, // kNuisFHCNuMuBarFlux02
   false, // kNuisFHCNuMuBarFlux03
   false, // kNuisFHCNuMuBarFlux04
   false, // kNuisFHCNuMuBarFlux05
   false, // kNuisFHCNuMuBarFlux06
   false, // kNuisFHCNuMuBarFlux07
   false, // kNuisFHCNuMuBarFlux08
   false, // kNuisFHCNuMuBarFlux09
   false, // kNuisFHCNuMuBarFlux10
   false, // kNuisFHCNuMuBarFlux11
   false, // kNuisFHCNuMuBarFlux12
   false, // kNuisFHCNuMuBarFlux13
   false, // kNuisFHCNuMuBarFlux14
   false, // kNuisFHCNuMuBarFlux15
   false, // kNuisFHCNuMuBarFlux16
   false, // kNuisFHCNuMuBarFlux17
   false, // kNuisFHCNuMuBarFlux18
   false, // kNuisFHCNuEFlux00
   false, // kNuisFHCNuEFlux01
   false, // kNuisFHCNuEFlux02
   false, // kNuisFHCNuEFlux03
   false, // kNuisFHCNuEFlux04
   false, // kNuisFHCNuEFlux05
   false, // kNuisFHCNuEFlux06
   false, // kNuisFHCNuEBarFlux00
   false, // kNuisFHCNuEBarFlux01
   false, // kNuisFHCNuEBarFlux02
   false, // kNuisFHCNuEBarFlux03
   false, // kNuisFHCNuEBarFlux04
   false, // kNuisFHCNuEBarFlux05
   false, // kNuisFHCNuEBarFlux06
   // RHC flux
   false, // kNuisRHCNuMuFlux00
   false, // kNuisRHCNuMuFlux01
   false, // kNuisRHCNuMuFlux02
   false, // kNuisRHCNuMuFlux03
   false, // kNuisRHCNuMuFlux04
   false, // kNuisRHCNuMuFlux05
   false, // kNuisRHCNuMuFlux06
   false, // kNuisRHCNuMuFlux07
   false, // kNuisRHCNuMuFlux08
   false, // kNuisRHCNuMuFlux09
   false, // kNuisRHCNuMuFlux10
   false, // kNuisRHCNuMuFlux11
   false, // kNuisRHCNuMuFlux12
   false, // kNuisRHCNuMuFlux13
   false, // kNuisRHCNuMuFlux14
   false, // kNuisRHCNuMuFlux15
   false, // kNuisRHCNuMuFlux16
   false, // kNuisRHCNuMuFlux17
   false, // kNuisRHCNuMuFlux18
   false, // kNuisRHCNuMuBarFlux00
   false, // kNuisRHCNuMuBarFlux01
   false, // kNuisRHCNuMuBarFlux02
   false, // kNuisRHCNuMuBarFlux03
   false, // kNuisRHCNuMuBarFlux04
   false, // kNuisRHCNuMuBarFlux05
   false, // kNuisRHCNuMuBarFlux06
   false, // kNuisRHCNuMuBarFlux07
   false, // kNuisRHCNuMuBarFlux08
   false, // kNuisRHCNuMuBarFlux09
   false, // kNuisRHCNuMuBarFlux10
   false, // kNuisRHCNuMuBarFlux11
   false, // kNuisRHCNuMuBarFlux12
   false, // kNuisRHCNuMuBarFlux13
   false, // kNuisRHCNuMuBarFlux14
   false, // kNuisRHCNuMuBarFlux15
   false, // kNuisRHCNuMuBarFlux16
   false, // kNuisRHCNuMuBarFlux17
   false, // kNuisRHCNuMuBarFlux18
   false, // kNuisRHCNuEFlux00
   false, // kNuisRHCNuEFlux01
   false, // kNuisRHCNuEFlux02
   false, // kNuisRHCNuEFlux03
   false, // kNuisRHCNuEFlux04
   false, // kNuisRHCNuEFlux05
   false, // kNuisRHCNuEFlux06
   false, // kNuisRHCNuEBarFlux00
   false, // kNuisRHCNuEBarFlux01
   false, // kNuisRHCNuEBarFlux02
   false, // kNuisRHCNuEBarFlux03
   false, // kNuisRHCNuEBarFlux04
   false, // kNuisRHCNuEBarFlux05
   false, // kNuisRHCNuEBarFlux06
   // Cross-sections
#if INT_MODEL == 1
   false, // kNuisNormCCQE 
   false, // kNuisNormCC1piC
   false, // kNuisNormCC1pi0
#elif INT_MODEL == 2
   false, //kNuisIntNuCCQE1     
   false, //kNuisIntNuCCQE2     
   false, //kNuisIntNuCCQE3     
   false, //kNuisIntNuBarCCQE1  
   false, //kNuisIntNuBarCCQE2  
   false, //kNuisIntNuBarCCQE3  
   false, //kNuisIntNuCC1piz1   
   false, //kNuisIntNuCC1piz2   
   false, //kNuisIntNuCC1piz3   
   false, //kNuisIntNuCC1pic1   
   false, //kNuisIntNuCC1pic2   
   false, //kNuisIntNuCC1pic3   
   false, //kNuisIntNuBarCC1piz1
   false, //kNuisIntNuBarCC1piz2
   false, //kNuisIntNuBarCC1piz3
   false, //kNuisIntNuBarCC1pic1
   false, //kNuisIntNuBarCC1pic2
   false, //kNuisIntNuBarCC1pic3
#else
  static_assert(!"AppliedConv: INT_MODEL not supported.");
#endif //INT_MODEL
   false, // kNuisNormCCoth
   false, // kNuisNormNC
   false, // kNuisRatioNuENuMu
   // Detector systematics
   true,  // kNuisEffNuMuCC1trkQE
   true,  // kNuisEffNuMuCC2trkQE
   true,  // kNuisEffNuMuCC1piC
   true,  // kNuisEffNuMuCC1pi0
   true,  // kNuisEffNuMuCC1piC1pi0
   true,  // kNuisEffNuMuCCoth  
   true,  // kNuisEffNuECC      
   true,  // kNuisEffNuMuCCWSgn 
   true   // kNuisEffNC                       
};

} // conv

//
// utility methods
//

namespace util {

  string  AsString    (conv::PhysParamId_t p);
  string  AsStringTeX (conv::PhysParamId_t p, bool root = false);
  
  // Aliases for above
  string  ParamAsString    (conv::PhysParamId_t p) ;
  string  ParamAsStringTeX (conv::PhysParamId_t p, bool root = false);

  conv::PhysParamId_t PhysParamFromString(string p);

  PhysHypothesis GetPhysHypothesis   (Option_t * param_list = "standard" /*, Option_t * param_values = "nominal"*/);
  FitParamList * GetFitParameterList (Option_t * param_list = "standard" /*, Option_t * param_values = "nominal"*/);
  
  bool IsNuFluxRelated(conv::PhysParamId_t p);
  bool IsNuIntRelated (conv::PhysParamId_t p);
  bool IsNuDetRelated (conv::PhysParamId_t p);
  
  conv::FitParamGroup_t GetParameterGroup(conv::PhysParamId_t p);
  
  bool ParamIsAppliedTo(conv::BeamConf_t b, conv::Sample_t s,
                        conv::ReacMode_t m, conv::PhysParamId_t p);
  
  // Tell the framework classes what our parameter names are
  void PopulateNameRegistry(void);

} //util

} // valor
  
#endif 

