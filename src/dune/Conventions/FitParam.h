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
#include "valor/Conventions/PhysParamId.h"
#include "valor/Conventions/Detector.h"
#include "valor/Conventions/BeamConf.h"
#include "valor/FitCore/CorrelatedSystematics.h"
#include "valor/FitCore/FitParamList.h"
#include "valor/FitCore/PhysHypothesis.h"

//dune
#include "dune/Conventions/DuneBuild.h"
#include "valor/Conventions/ReacMode.h"
#include "dune/Conventions/FitParamGroup.h"

#include "dune/Conventions/SampleKineBinning.h"

using std::string;

namespace valor {
namespace conv {

static const int kNFitParamsNuFluxND = 104; // neutrino flux related 104 ND 
static const int kNFitParamsNuFluxFD = 104; // neutrino flux related 104 FD 
static const int kNFitParamsNuFlux   = kNFitParamsNuFluxND + kNFitParamsNuFluxFD;
static const int kNFitParamsNuDetND  = 323; // near detector related
static const int kNFitParamsNuDetFD  =  4; // far detector related: one per sample for now
static const int kNFitParamsNuDet    = kNFitParamsNuDetND+ kNFitParamsNuDetFD;
static const int kNFitParamsNuInt  =  45; // neutrino interactions related
static const int kNFitParamsNuOsc  =   6; //usual 3-flavour suspects

static const int kNFitParams   = kNFitParamsNuFlux+kNFitParamsNuInt+kNFitParamsNuDet+kNFitParamsNuOsc;
//~ static const int kNFitParamsND = kNFitParamsNuFluxND+kNFitParamsNuInt+kNFitParamsNuDetND;

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

//Far detector flux
//
// FHC flux
//
static const PhysParamId_t kNuisFHCNuMuFDFlux00    = kNuis104;
static const PhysParamId_t kNuisFHCNuMuFDFlux01    = kNuis105;
static const PhysParamId_t kNuisFHCNuMuFDFlux02    = kNuis106;
static const PhysParamId_t kNuisFHCNuMuFDFlux03    = kNuis107;
static const PhysParamId_t kNuisFHCNuMuFDFlux04    = kNuis108;
static const PhysParamId_t kNuisFHCNuMuFDFlux05    = kNuis109;
static const PhysParamId_t kNuisFHCNuMuFDFlux06    = kNuis110;
static const PhysParamId_t kNuisFHCNuMuFDFlux07    = kNuis111;
static const PhysParamId_t kNuisFHCNuMuFDFlux08    = kNuis112;
static const PhysParamId_t kNuisFHCNuMuFDFlux09    = kNuis113;
static const PhysParamId_t kNuisFHCNuMuFDFlux10    = kNuis114;
static const PhysParamId_t kNuisFHCNuMuFDFlux11    = kNuis115;
static const PhysParamId_t kNuisFHCNuMuFDFlux12    = kNuis116;
static const PhysParamId_t kNuisFHCNuMuFDFlux13    = kNuis117;
static const PhysParamId_t kNuisFHCNuMuFDFlux14    = kNuis118;
static const PhysParamId_t kNuisFHCNuMuFDFlux15    = kNuis119;
static const PhysParamId_t kNuisFHCNuMuFDFlux16    = kNuis120;
static const PhysParamId_t kNuisFHCNuMuFDFlux17    = kNuis121;
static const PhysParamId_t kNuisFHCNuMuFDFlux18    = kNuis122;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux00 = kNuis123;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux01 = kNuis124;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux02 = kNuis125;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux03 = kNuis126;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux04 = kNuis127;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux05 = kNuis128;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux06 = kNuis129;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux07 = kNuis130;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux08 = kNuis131;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux09 = kNuis132;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux10 = kNuis133;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux11 = kNuis134;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux12 = kNuis135;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux13 = kNuis136;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux14 = kNuis137;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux15 = kNuis138;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux16 = kNuis139;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux17 = kNuis140;
static const PhysParamId_t kNuisFHCNuMuBarFDFlux18 = kNuis141;
static const PhysParamId_t kNuisFHCNuEFDFlux00     = kNuis142;
static const PhysParamId_t kNuisFHCNuEFDFlux01     = kNuis143;
static const PhysParamId_t kNuisFHCNuEFDFlux02     = kNuis144;
static const PhysParamId_t kNuisFHCNuEFDFlux03     = kNuis145;
static const PhysParamId_t kNuisFHCNuEFDFlux04     = kNuis146;
static const PhysParamId_t kNuisFHCNuEFDFlux05     = kNuis147;
static const PhysParamId_t kNuisFHCNuEFDFlux06     = kNuis148;
static const PhysParamId_t kNuisFHCNuEBarFDFlux00  = kNuis149;
static const PhysParamId_t kNuisFHCNuEBarFDFlux01  = kNuis150;
static const PhysParamId_t kNuisFHCNuEBarFDFlux02  = kNuis151;
static const PhysParamId_t kNuisFHCNuEBarFDFlux03  = kNuis152;
static const PhysParamId_t kNuisFHCNuEBarFDFlux04  = kNuis153;
static const PhysParamId_t kNuisFHCNuEBarFDFlux05  = kNuis154;
static const PhysParamId_t kNuisFHCNuEBarFDFlux06  = kNuis155;
//
// RHC flux
//
static const PhysParamId_t kNuisRHCNuMuFDFlux00    = kNuis156;
static const PhysParamId_t kNuisRHCNuMuFDFlux01    = kNuis157;
static const PhysParamId_t kNuisRHCNuMuFDFlux02    = kNuis158;
static const PhysParamId_t kNuisRHCNuMuFDFlux03    = kNuis159;
static const PhysParamId_t kNuisRHCNuMuFDFlux04    = kNuis160;
static const PhysParamId_t kNuisRHCNuMuFDFlux05    = kNuis161;
static const PhysParamId_t kNuisRHCNuMuFDFlux06    = kNuis162;
static const PhysParamId_t kNuisRHCNuMuFDFlux07    = kNuis163;
static const PhysParamId_t kNuisRHCNuMuFDFlux08    = kNuis164;
static const PhysParamId_t kNuisRHCNuMuFDFlux09    = kNuis165;
static const PhysParamId_t kNuisRHCNuMuFDFlux10    = kNuis166;
static const PhysParamId_t kNuisRHCNuMuFDFlux11    = kNuis167;
static const PhysParamId_t kNuisRHCNuMuFDFlux12    = kNuis168;
static const PhysParamId_t kNuisRHCNuMuFDFlux13    = kNuis169;
static const PhysParamId_t kNuisRHCNuMuFDFlux14    = kNuis170;
static const PhysParamId_t kNuisRHCNuMuFDFlux15    = kNuis171;
static const PhysParamId_t kNuisRHCNuMuFDFlux16    = kNuis172;
static const PhysParamId_t kNuisRHCNuMuFDFlux17    = kNuis173;
static const PhysParamId_t kNuisRHCNuMuFDFlux18    = kNuis174;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux00 = kNuis175;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux01 = kNuis176;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux02 = kNuis177;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux03 = kNuis178;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux04 = kNuis179;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux05 = kNuis180;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux06 = kNuis181;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux07 = kNuis182;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux08 = kNuis183;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux09 = kNuis184;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux10 = kNuis185;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux11 = kNuis186;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux12 = kNuis187;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux13 = kNuis188;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux14 = kNuis189;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux15 = kNuis190;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux16 = kNuis191;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux17 = kNuis192;
static const PhysParamId_t kNuisRHCNuMuBarFDFlux18 = kNuis193;
static const PhysParamId_t kNuisRHCNuEFDFlux00     = kNuis194;
static const PhysParamId_t kNuisRHCNuEFDFlux01     = kNuis195;
static const PhysParamId_t kNuisRHCNuEFDFlux02     = kNuis196;
static const PhysParamId_t kNuisRHCNuEFDFlux03     = kNuis197;
static const PhysParamId_t kNuisRHCNuEFDFlux04     = kNuis198;
static const PhysParamId_t kNuisRHCNuEFDFlux05     = kNuis199;
static const PhysParamId_t kNuisRHCNuEFDFlux06     = kNuis200;
static const PhysParamId_t kNuisRHCNuEBarFDFlux00  = kNuis201;
static const PhysParamId_t kNuisRHCNuEBarFDFlux01  = kNuis202;
static const PhysParamId_t kNuisRHCNuEBarFDFlux02  = kNuis203;
static const PhysParamId_t kNuisRHCNuEBarFDFlux03  = kNuis204;
static const PhysParamId_t kNuisRHCNuEBarFDFlux04  = kNuis205;
static const PhysParamId_t kNuisRHCNuEBarFDFlux05  = kNuis206;
static const PhysParamId_t kNuisRHCNuEBarFDFlux06  = kNuis207;

//
// Cross-section
//
static const PhysParamId_t kNuisNormCCQE         = kNuis208;
static const PhysParamId_t kNuisNormCC1piC       = kNuis209;
static const PhysParamId_t kNuisNormCC1pi0       = kNuis210;
static const PhysParamId_t kNuisNormCCoth        = kNuis211;
static const PhysParamId_t kNuisNormNC           = kNuis212;
static const PhysParamId_t kNuisRatioNuENuMu     = kNuis213;
//
// Detector systematics
//
static const PhysParamId_t kNuisEffNuMuCC0pi1trk = kNuis214;
static const PhysParamId_t kNuisEffNuMuCC0pi2trk = kNuis215;
static const PhysParamId_t kNuisEffNuMuCC1piC    = kNuis216;
static const PhysParamId_t kNuisEffNuMuCC1pi0    = kNuis217;
static const PhysParamId_t kNuisEffNuMuCC1piC1pi0= kNuis218;
static const PhysParamId_t kNuisEffNuMuCCoth     = kNuis219;
static const PhysParamId_t kNuisEffNuECC         = kNuis220;
static const PhysParamId_t kNuisEffNuMuCCWS      = kNuis221;
static const PhysParamId_t kNuisEffNC            = kNuis222;

//
// Far detector systematics
//
static const PhysParamId_t kNuisEffFDNuMuLikeCCHigh     = kNuis223;
static const PhysParamId_t kNuisEffFDNuMuLikeCCLow      = kNuis224;
//static const PhysParamId_t kNuisEffFDNuMuBarCCHigh  = kNuis225;
//static const PhysParamId_t kNuisEffFDNuMuBarCCLow   = kNuis226;
static const PhysParamId_t kNuisEffFDNuELikeCCHigh      = kNuis225;
static const PhysParamId_t kNuisEffFDNuELikeCCLow       = kNuis226;
/*static const PhysParamId_t kNuisEffFDNuEBarCCHigh   = kNuis229;
static const PhysParamId_t kNuisEffFDNuEBarCCLow    = kNuis230;
static const PhysParamId_t kNuisEffFDNuTauCCHigh    = kNuis231;
static const PhysParamId_t kNuisEffFDNuTauCCLow     = kNuis232;
static const PhysParamId_t kNuisEffFDNuTauBarCCHigh = kNuis233;
static const PhysParamId_t kNuisEffFDNuTauBarCCLow  = kNuis234;*/

//
// Interaction model, more complex
//
static const PhysParamId_t kNuisIntNuCCQE1               = kNuis227;
static const PhysParamId_t kNuisIntNuCCQE2               = kNuis228;
static const PhysParamId_t kNuisIntNuCCQE3               = kNuis229;
static const PhysParamId_t kNuisIntNuBarCCQE1            = kNuis230;
static const PhysParamId_t kNuisIntNuBarCCQE2            = kNuis231;
static const PhysParamId_t kNuisIntNuBarCCQE3            = kNuis232;

static const PhysParamId_t kNuisIntNuCCMEC               = kNuis233;
static const PhysParamId_t kNuisIntNuBarCCMEC            = kNuis234;

static const PhysParamId_t kNuisIntNuCC1piz1             = kNuis235;
static const PhysParamId_t kNuisIntNuCC1piz2             = kNuis236;
static const PhysParamId_t kNuisIntNuCC1piz3             = kNuis237;
static const PhysParamId_t kNuisIntNuCC1pic1             = kNuis238;
static const PhysParamId_t kNuisIntNuCC1pic2             = kNuis239;
static const PhysParamId_t kNuisIntNuCC1pic3             = kNuis240;

static const PhysParamId_t kNuisIntNuBarCC1piz1          = kNuis241;
static const PhysParamId_t kNuisIntNuBarCC1piz2          = kNuis242;
static const PhysParamId_t kNuisIntNuBarCC1piz3          = kNuis243;
static const PhysParamId_t kNuisIntNuBarCC1pic1          = kNuis244;
static const PhysParamId_t kNuisIntNuBarCC1pic2          = kNuis245;
static const PhysParamId_t kNuisIntNuBarCC1pic3          = kNuis246;

static const PhysParamId_t kNuisIntNuCC2Pi               = kNuis247;
static const PhysParamId_t kNuisIntNuBarCC2Pi            = kNuis248;

static const PhysParamId_t kNuisIntNuDIS1                = kNuis249;
static const PhysParamId_t kNuisIntNuDIS2                = kNuis250;
static const PhysParamId_t kNuisIntNuDIS3                = kNuis251;
static const PhysParamId_t kNuisIntNuBarDIS1             = kNuis252;
static const PhysParamId_t kNuisIntNuBarDIS2             = kNuis253;
static const PhysParamId_t kNuisIntNuBarDIS3             = kNuis254;

static const PhysParamId_t kNuisIntNormNuCoherent        = kNuis255;
static const PhysParamId_t kNuisIntNormNuBarCoherent     = kNuis256;
static const PhysParamId_t kNuisIntNuNormNC              = kNuis257;
static const PhysParamId_t kNuisIntNuBarNormNC           = kNuis258;
static const PhysParamId_t kNuisIntNormNuMuToNuE         = kNuis259;
static const PhysParamId_t kNuisIntNormNuMuBarToNuEBar   = kNuis260;

static const PhysParamId_t kNuisIntPiMeanFreePath        = kNuis261;
static const PhysParamId_t kNuisIntNucMeanFreePath       = kNuis262;
static const PhysParamId_t kNuisIntFracPiChargeExchange  = kNuis263;
static const PhysParamId_t kNuisIntFracPiInelastic       = kNuis264;
static const PhysParamId_t kNuisIntFracPiAbsorb          = kNuis265;
static const PhysParamId_t kNuisIntFracPiProduction      = kNuis266;
static const PhysParamId_t kNuisIntFracNucChargeExchange = kNuis267;
static const PhysParamId_t kNuisIntFracNucInelastic      = kNuis268;
static const PhysParamId_t kNuisIntFracNucAbsorb         = kNuis269;
static const PhysParamId_t kNuisIntFracNucProduction     = kNuis270;

static const PhysParamId_t kNuisIntHadronization         = kNuis271;
static const PhysParamId_t kNuisIntTarget                = kNuis272;

// Big detector parameterisation
static const PhysParamId_t kNuisEffFHCnumuCC0pi1trk01        = kNuis300;
static const PhysParamId_t kNuisEffFHCnumuCC0pi1trk02        = kNuis301;
static const PhysParamId_t kNuisEffFHCnumuCC0pi1trk03        = kNuis302;
static const PhysParamId_t kNuisEffFHCnumuCC0pi1trk04        = kNuis303;
static const PhysParamId_t kNuisEffFHCnumuCC0pi1trk05        = kNuis304;
static const PhysParamId_t kNuisEffFHCnumuCC0pi1trk06        = kNuis305;
static const PhysParamId_t kNuisEffFHCnumuCC0pi1trk07        = kNuis306;
static const PhysParamId_t kNuisEffFHCnumuCC0pi1trk08        = kNuis307;
static const PhysParamId_t kNuisEffFHCnumuCC0pi1trk09        = kNuis308; //
static const PhysParamId_t kNuisEffFHCnumuCC0pi2trk01        = kNuis309;
static const PhysParamId_t kNuisEffFHCnumuCC0pi2trk02        = kNuis310;
static const PhysParamId_t kNuisEffFHCnumuCC0pi2trk03        = kNuis311;
static const PhysParamId_t kNuisEffFHCnumuCC0pi2trk04        = kNuis312;
static const PhysParamId_t kNuisEffFHCnumuCC0pi2trk05        = kNuis313;
static const PhysParamId_t kNuisEffFHCnumuCC0pi2trk06        = kNuis314;
static const PhysParamId_t kNuisEffFHCnumuCC0pi2trk07        = kNuis315;
static const PhysParamId_t kNuisEffFHCnumuCC0pi2trk08        = kNuis316;
static const PhysParamId_t kNuisEffFHCnumuCC0pi2trk09        = kNuis317; //
static const PhysParamId_t kNuisEffFHCnumuCC0piNtrk01        = kNuis318;
static const PhysParamId_t kNuisEffFHCnumuCC0piNtrk02        = kNuis319;
static const PhysParamId_t kNuisEffFHCnumuCC0piNtrk03        = kNuis320;
static const PhysParamId_t kNuisEffFHCnumuCC0piNtrk04        = kNuis321;
static const PhysParamId_t kNuisEffFHCnumuCC0piNtrk05        = kNuis322;
static const PhysParamId_t kNuisEffFHCnumuCC0piNtrk06        = kNuis323;
static const PhysParamId_t kNuisEffFHCnumuCC0piNtrk07        = kNuis324;
static const PhysParamId_t kNuisEffFHCnumuCC0piNtrk08        = kNuis325;
static const PhysParamId_t kNuisEffFHCnumuCC0piNtrk09        = kNuis326;
static const PhysParamId_t kNuisEffFHCnumuCC0piNtrk10        = kNuis327;
static const PhysParamId_t kNuisEffFHCnumuCC0piNtrk11        = kNuis328;
static const PhysParamId_t kNuisEffFHCnumuCC0piNtrk12        = kNuis329;
static const PhysParamId_t kNuisEffFHCnumuCC0piNtrk13        = kNuis330;
static const PhysParamId_t kNuisEffFHCnumuCC0piNtrk14        = kNuis331;
static const PhysParamId_t kNuisEffFHCnumuCC0piNtrk15        = kNuis332; //
static const PhysParamId_t kNuisEffFHCnumuCC1pi3trkDelta01   = kNuis333;
static const PhysParamId_t kNuisEffFHCnumuCC1pi3trkDelta02   = kNuis334;
static const PhysParamId_t kNuisEffFHCnumuCC1pi3trkDelta03   = kNuis335;
static const PhysParamId_t kNuisEffFHCnumuCC1pi3trkDelta04   = kNuis336;
static const PhysParamId_t kNuisEffFHCnumuCC1pi3trkDelta05   = kNuis337;
static const PhysParamId_t kNuisEffFHCnumuCC1pi3trkDelta06   = kNuis338;
static const PhysParamId_t kNuisEffFHCnumuCC1pi3trkDelta07   = kNuis339;
static const PhysParamId_t kNuisEffFHCnumuCC1pi3trkDelta08   = kNuis340;
static const PhysParamId_t kNuisEffFHCnumuCC1pi3trkDelta09   = kNuis341;
static const PhysParamId_t kNuisEffFHCnumuCC1pi3trkDelta10   = kNuis342;
static const PhysParamId_t kNuisEffFHCnumuCC1pi3trkDelta11   = kNuis343;
static const PhysParamId_t kNuisEffFHCnumuCC1pi3trkDelta12   = kNuis344;
static const PhysParamId_t kNuisEffFHCnumuCC1pi3trkDelta13   = kNuis345;
static const PhysParamId_t kNuisEffFHCnumuCC1pi3trkDelta14   = kNuis346;
static const PhysParamId_t kNuisEffFHCnumuCC1pi3trkDelta15   = kNuis347; //
static const PhysParamId_t kNuisEffFHCnumuCC1pic01           = kNuis348;
static const PhysParamId_t kNuisEffFHCnumuCC1pic02           = kNuis349;
static const PhysParamId_t kNuisEffFHCnumuCC1pic03           = kNuis350;
static const PhysParamId_t kNuisEffFHCnumuCC1pic04           = kNuis351;
static const PhysParamId_t kNuisEffFHCnumuCC1pic05           = kNuis352;
static const PhysParamId_t kNuisEffFHCnumuCC1pic06           = kNuis353;
static const PhysParamId_t kNuisEffFHCnumuCC1pic07           = kNuis354;
static const PhysParamId_t kNuisEffFHCnumuCC1pic08           = kNuis355;
static const PhysParamId_t kNuisEffFHCnumuCC1pic09           = kNuis356; //
static const PhysParamId_t kNuisEffFHCnumuCC1piz01           = kNuis357;
static const PhysParamId_t kNuisEffFHCnumuCC1piz02           = kNuis358;
static const PhysParamId_t kNuisEffFHCnumuCC1piz03           = kNuis359;
static const PhysParamId_t kNuisEffFHCnumuCC1piz04           = kNuis360;
static const PhysParamId_t kNuisEffFHCnumuCC1piz05           = kNuis361;
static const PhysParamId_t kNuisEffFHCnumuCC1piz06           = kNuis362;
static const PhysParamId_t kNuisEffFHCnumuCC1piz07           = kNuis363;
static const PhysParamId_t kNuisEffFHCnumuCC1piz08           = kNuis364;
static const PhysParamId_t kNuisEffFHCnumuCC1piz09           = kNuis365; //
static const PhysParamId_t kNuisEffFHCnumuCC1pic1piz01       = kNuis366;
static const PhysParamId_t kNuisEffFHCnumuCC1pic1piz02       = kNuis367;
static const PhysParamId_t kNuisEffFHCnumuCC1pic1piz03       = kNuis368;
static const PhysParamId_t kNuisEffFHCnumuCC1pic1piz04       = kNuis369;
static const PhysParamId_t kNuisEffFHCnumuCC1pic1piz05       = kNuis370;
static const PhysParamId_t kNuisEffFHCnumuCC1pic1piz06       = kNuis371;
static const PhysParamId_t kNuisEffFHCnumuCC1pic1piz07       = kNuis372;
static const PhysParamId_t kNuisEffFHCnumuCC1pic1piz08       = kNuis373;
static const PhysParamId_t kNuisEffFHCnumuCC1pic1piz09       = kNuis374; //
static const PhysParamId_t kNuisEffFHCnumuCCother01          = kNuis375;
static const PhysParamId_t kNuisEffFHCnumuCCother02          = kNuis376;
static const PhysParamId_t kNuisEffFHCnumuCCother03          = kNuis377;
static const PhysParamId_t kNuisEffFHCnumuCCother04          = kNuis378;
static const PhysParamId_t kNuisEffFHCnumuCCother05          = kNuis379;
static const PhysParamId_t kNuisEffFHCnumuCCother06          = kNuis380;
static const PhysParamId_t kNuisEffFHCnumuCCother07          = kNuis381;
static const PhysParamId_t kNuisEffFHCnumuCCother08          = kNuis382;
static const PhysParamId_t kNuisEffFHCnumuCCother09          = kNuis383;
static const PhysParamId_t kNuisEffFHCnumuCCother10          = kNuis384;
static const PhysParamId_t kNuisEffFHCnumuCCother11          = kNuis385; //
static const PhysParamId_t kNuisEffFHCnumuCCWS0pi01          = kNuis386;
static const PhysParamId_t kNuisEffFHCnumuCCWS0pi02          = kNuis387;
static const PhysParamId_t kNuisEffFHCnumuCCWS0pi03          = kNuis388;
static const PhysParamId_t kNuisEffFHCnumuCCWS0pi04          = kNuis389;
static const PhysParamId_t kNuisEffFHCnumuCCWS0pi05          = kNuis390; //
static const PhysParamId_t kNuisEffFHCnumuCCWS1pic01         = kNuis391;
static const PhysParamId_t kNuisEffFHCnumuCCWS1pic02         = kNuis392;
static const PhysParamId_t kNuisEffFHCnumuCCWS1pic03         = kNuis393;
static const PhysParamId_t kNuisEffFHCnumuCCWS1pic04         = kNuis394;
static const PhysParamId_t kNuisEffFHCnumuCCWS1pic05         = kNuis395;
static const PhysParamId_t kNuisEffFHCnumuCCWS1pic06         = kNuis396;
static const PhysParamId_t kNuisEffFHCnumuCCWS1pic07         = kNuis397;
static const PhysParamId_t kNuisEffFHCnumuCCWS1pic08         = kNuis398; //
static const PhysParamId_t kNuisEffFHCnumuCCWS1piz01         = kNuis399;
static const PhysParamId_t kNuisEffFHCnumuCCWS1piz02         = kNuis400;
static const PhysParamId_t kNuisEffFHCnumuCCWS1piz03         = kNuis401; //
static const PhysParamId_t kNuisEffFHCnumuCCWSother01        = kNuis402; //
static const PhysParamId_t kNuisEffFHCnueCC0pi01             = kNuis403;
static const PhysParamId_t kNuisEffFHCnueCC0pi02             = kNuis404;
static const PhysParamId_t kNuisEffFHCnueCC0pi03             = kNuis405;
static const PhysParamId_t kNuisEffFHCnueCC0pi04             = kNuis406;
static const PhysParamId_t kNuisEffFHCnueCC0pi05             = kNuis407;
static const PhysParamId_t kNuisEffFHCnueCC0pi06             = kNuis408;
static const PhysParamId_t kNuisEffFHCnueCC0pi07             = kNuis409;
static const PhysParamId_t kNuisEffFHCnueCC0pi08             = kNuis410;
static const PhysParamId_t kNuisEffFHCnueCC0pi09             = kNuis411; //
static const PhysParamId_t kNuisEffFHCnueCC1pic01            = kNuis412;
static const PhysParamId_t kNuisEffFHCnueCC1pic02            = kNuis413;
static const PhysParamId_t kNuisEffFHCnueCC1pic03            = kNuis414;
static const PhysParamId_t kNuisEffFHCnueCC1pic04            = kNuis415;
static const PhysParamId_t kNuisEffFHCnueCC1pic05            = kNuis416;
static const PhysParamId_t kNuisEffFHCnueCC1pic06            = kNuis417;
static const PhysParamId_t kNuisEffFHCnueCC1pic07            = kNuis418;
static const PhysParamId_t kNuisEffFHCnueCC1pic08            = kNuis419;
static const PhysParamId_t kNuisEffFHCnueCC1pic09            = kNuis420; //
static const PhysParamId_t kNuisEffFHCnueCC1piz01            = kNuis421;
static const PhysParamId_t kNuisEffFHCnueCC1piz02            = kNuis422;
static const PhysParamId_t kNuisEffFHCnueCC1piz03            = kNuis423;
static const PhysParamId_t kNuisEffFHCnueCC1piz04            = kNuis424;
static const PhysParamId_t kNuisEffFHCnueCC1piz05            = kNuis425;
static const PhysParamId_t kNuisEffFHCnueCC1piz06            = kNuis426;
static const PhysParamId_t kNuisEffFHCnueCC1piz07            = kNuis427;
static const PhysParamId_t kNuisEffFHCnueCC1piz08            = kNuis428;
static const PhysParamId_t kNuisEffFHCnueCC1piz09            = kNuis429; //
static const PhysParamId_t kNuisEffFHCnueCCother01           = kNuis430;
static const PhysParamId_t kNuisEffFHCnueCCother02           = kNuis431;
static const PhysParamId_t kNuisEffFHCnueCCother03           = kNuis432;
static const PhysParamId_t kNuisEffFHCnueCCother04           = kNuis433;
static const PhysParamId_t kNuisEffFHCnueCCother05           = kNuis434;
static const PhysParamId_t kNuisEffFHCnueCCother06           = kNuis435;
static const PhysParamId_t kNuisEffFHCnueCCother07           = kNuis436;
static const PhysParamId_t kNuisEffFHCnueCCother08           = kNuis437;
static const PhysParamId_t kNuisEffFHCnueCCother09           = kNuis438;
static const PhysParamId_t kNuisEffFHCnueCCother10           = kNuis439;
static const PhysParamId_t kNuisEffFHCnueCCother11           = kNuis440; //
static const PhysParamId_t kNuisEffFHCnueCCWS01              = kNuis441;
static const PhysParamId_t kNuisEffFHCnueCCWS02              = kNuis442; //
static const PhysParamId_t kNuisEffFHCNC0pi01                = kNuis443;
static const PhysParamId_t kNuisEffFHCNC0pi02                = kNuis444;
static const PhysParamId_t kNuisEffFHCNC0pi03                = kNuis445;
static const PhysParamId_t kNuisEffFHCNC1pic01               = kNuis446;
static const PhysParamId_t kNuisEffFHCNC1pic02               = kNuis447;
static const PhysParamId_t kNuisEffFHCNC1pic03               = kNuis448;
static const PhysParamId_t kNuisEffFHCNC1piz01               = kNuis449;
static const PhysParamId_t kNuisEffFHCNC1piz02               = kNuis450;
static const PhysParamId_t kNuisEffFHCNC1piz03               = kNuis451;
static const PhysParamId_t kNuisEffFHCNCother01              = kNuis452;
static const PhysParamId_t kNuisEffFHCNCother02              = kNuis453;
static const PhysParamId_t kNuisEffFHCNCother03              = kNuis454;
static const PhysParamId_t kNuisEffFHCNeutrinoElec           = kNuis455;
static const PhysParamId_t kNuisEffFHCIMD                    = kNuis456; //
static const PhysParamId_t kNuisEffRHCnumuCC0pi1trk01        = kNuis500;
static const PhysParamId_t kNuisEffRHCnumuCC0pi1trk02        = kNuis501;
static const PhysParamId_t kNuisEffRHCnumuCC0pi1trk03        = kNuis502;
static const PhysParamId_t kNuisEffRHCnumuCC0pi1trk04        = kNuis503;
static const PhysParamId_t kNuisEffRHCnumuCC0pi1trk05        = kNuis504;
static const PhysParamId_t kNuisEffRHCnumuCC0pi1trk06        = kNuis505;
static const PhysParamId_t kNuisEffRHCnumuCC0pi1trk07        = kNuis506;
static const PhysParamId_t kNuisEffRHCnumuCC0pi1trk08        = kNuis507;
static const PhysParamId_t kNuisEffRHCnumuCC0pi1trk09        = kNuis508; //
static const PhysParamId_t kNuisEffRHCnumuCC0pi2trk01        = kNuis509;
static const PhysParamId_t kNuisEffRHCnumuCC0pi2trk02        = kNuis510;
static const PhysParamId_t kNuisEffRHCnumuCC0pi2trk03        = kNuis511;
static const PhysParamId_t kNuisEffRHCnumuCC0pi2trk04        = kNuis512;
static const PhysParamId_t kNuisEffRHCnumuCC0pi2trk05        = kNuis513;
static const PhysParamId_t kNuisEffRHCnumuCC0pi2trk06        = kNuis514;
static const PhysParamId_t kNuisEffRHCnumuCC0pi2trk07        = kNuis515;
static const PhysParamId_t kNuisEffRHCnumuCC0pi2trk08        = kNuis516;
static const PhysParamId_t kNuisEffRHCnumuCC0pi2trk09        = kNuis517; //
static const PhysParamId_t kNuisEffRHCnumuCC0piNtrk01        = kNuis518;
static const PhysParamId_t kNuisEffRHCnumuCC0piNtrk02        = kNuis519;
static const PhysParamId_t kNuisEffRHCnumuCC0piNtrk03        = kNuis520;
static const PhysParamId_t kNuisEffRHCnumuCC0piNtrk04        = kNuis521;
static const PhysParamId_t kNuisEffRHCnumuCC0piNtrk05        = kNuis522;
static const PhysParamId_t kNuisEffRHCnumuCC0piNtrk06        = kNuis523;
static const PhysParamId_t kNuisEffRHCnumuCC0piNtrk07        = kNuis524;
static const PhysParamId_t kNuisEffRHCnumuCC0piNtrk08        = kNuis525;
static const PhysParamId_t kNuisEffRHCnumuCC0piNtrk09        = kNuis526;
static const PhysParamId_t kNuisEffRHCnumuCC0piNtrk10        = kNuis527;
static const PhysParamId_t kNuisEffRHCnumuCC0piNtrk11        = kNuis528;
static const PhysParamId_t kNuisEffRHCnumuCC0piNtrk12        = kNuis529;
static const PhysParamId_t kNuisEffRHCnumuCC0piNtrk13        = kNuis530;
static const PhysParamId_t kNuisEffRHCnumuCC0piNtrk14        = kNuis531;
static const PhysParamId_t kNuisEffRHCnumuCC0piNtrk15        = kNuis532; //
static const PhysParamId_t kNuisEffRHCnumuCC1pi3trkDelta01   = kNuis533;
static const PhysParamId_t kNuisEffRHCnumuCC1pi3trkDelta02   = kNuis534;
static const PhysParamId_t kNuisEffRHCnumuCC1pi3trkDelta03   = kNuis535;
static const PhysParamId_t kNuisEffRHCnumuCC1pi3trkDelta04   = kNuis536;
static const PhysParamId_t kNuisEffRHCnumuCC1pi3trkDelta05   = kNuis537;
static const PhysParamId_t kNuisEffRHCnumuCC1pi3trkDelta06   = kNuis538;
static const PhysParamId_t kNuisEffRHCnumuCC1pi3trkDelta07   = kNuis539;
static const PhysParamId_t kNuisEffRHCnumuCC1pi3trkDelta08   = kNuis540;
static const PhysParamId_t kNuisEffRHCnumuCC1pi3trkDelta09   = kNuis541;
static const PhysParamId_t kNuisEffRHCnumuCC1pi3trkDelta10   = kNuis542;
static const PhysParamId_t kNuisEffRHCnumuCC1pi3trkDelta11   = kNuis543;
static const PhysParamId_t kNuisEffRHCnumuCC1pi3trkDelta12   = kNuis544;
static const PhysParamId_t kNuisEffRHCnumuCC1pi3trkDelta13   = kNuis545;
static const PhysParamId_t kNuisEffRHCnumuCC1pi3trkDelta14   = kNuis546;
static const PhysParamId_t kNuisEffRHCnumuCC1pi3trkDelta15   = kNuis547; //
static const PhysParamId_t kNuisEffRHCnumuCC1pic01           = kNuis548;
static const PhysParamId_t kNuisEffRHCnumuCC1pic02           = kNuis549;
static const PhysParamId_t kNuisEffRHCnumuCC1pic03           = kNuis550;
static const PhysParamId_t kNuisEffRHCnumuCC1pic04           = kNuis551;
static const PhysParamId_t kNuisEffRHCnumuCC1pic05           = kNuis552;
static const PhysParamId_t kNuisEffRHCnumuCC1pic06           = kNuis553;
static const PhysParamId_t kNuisEffRHCnumuCC1pic07           = kNuis554;
static const PhysParamId_t kNuisEffRHCnumuCC1pic08           = kNuis555;
static const PhysParamId_t kNuisEffRHCnumuCC1pic09           = kNuis556; //
static const PhysParamId_t kNuisEffRHCnumuCC1piz01           = kNuis557;
static const PhysParamId_t kNuisEffRHCnumuCC1piz02           = kNuis558;
static const PhysParamId_t kNuisEffRHCnumuCC1piz03           = kNuis559;
static const PhysParamId_t kNuisEffRHCnumuCC1piz04           = kNuis560;
static const PhysParamId_t kNuisEffRHCnumuCC1piz05           = kNuis561;
static const PhysParamId_t kNuisEffRHCnumuCC1piz06           = kNuis562;
static const PhysParamId_t kNuisEffRHCnumuCC1piz07           = kNuis563;
static const PhysParamId_t kNuisEffRHCnumuCC1piz08           = kNuis564;
static const PhysParamId_t kNuisEffRHCnumuCC1piz09           = kNuis565; //
static const PhysParamId_t kNuisEffRHCnumuCC1pic1piz01       = kNuis566;
static const PhysParamId_t kNuisEffRHCnumuCC1pic1piz02       = kNuis567;
static const PhysParamId_t kNuisEffRHCnumuCC1pic1piz03       = kNuis568;
static const PhysParamId_t kNuisEffRHCnumuCC1pic1piz04       = kNuis569;
static const PhysParamId_t kNuisEffRHCnumuCC1pic1piz05       = kNuis570;
static const PhysParamId_t kNuisEffRHCnumuCC1pic1piz06       = kNuis571;
static const PhysParamId_t kNuisEffRHCnumuCC1pic1piz07       = kNuis572;
static const PhysParamId_t kNuisEffRHCnumuCC1pic1piz08       = kNuis573;
static const PhysParamId_t kNuisEffRHCnumuCC1pic1piz09       = kNuis574; //
static const PhysParamId_t kNuisEffRHCnumuCCother01          = kNuis575;
static const PhysParamId_t kNuisEffRHCnumuCCother02          = kNuis576;
static const PhysParamId_t kNuisEffRHCnumuCCother03          = kNuis577;
static const PhysParamId_t kNuisEffRHCnumuCCother04          = kNuis578;
static const PhysParamId_t kNuisEffRHCnumuCCother05          = kNuis579;
static const PhysParamId_t kNuisEffRHCnumuCCother06          = kNuis580;
static const PhysParamId_t kNuisEffRHCnumuCCother07          = kNuis581;
static const PhysParamId_t kNuisEffRHCnumuCCother08          = kNuis582;
static const PhysParamId_t kNuisEffRHCnumuCCother09          = kNuis583;
static const PhysParamId_t kNuisEffRHCnumuCCother10          = kNuis584;
static const PhysParamId_t kNuisEffRHCnumuCCother11          = kNuis585; //
static const PhysParamId_t kNuisEffRHCnumuCCWS0pi01          = kNuis586;
static const PhysParamId_t kNuisEffRHCnumuCCWS0pi02          = kNuis587;
static const PhysParamId_t kNuisEffRHCnumuCCWS0pi03          = kNuis588;
static const PhysParamId_t kNuisEffRHCnumuCCWS0pi04          = kNuis589;
static const PhysParamId_t kNuisEffRHCnumuCCWS0pi05          = kNuis590; //
static const PhysParamId_t kNuisEffRHCnumuCCWS1pic01         = kNuis591;
static const PhysParamId_t kNuisEffRHCnumuCCWS1pic02         = kNuis592;
static const PhysParamId_t kNuisEffRHCnumuCCWS1pic03         = kNuis593;
static const PhysParamId_t kNuisEffRHCnumuCCWS1pic04         = kNuis594;
static const PhysParamId_t kNuisEffRHCnumuCCWS1pic05         = kNuis595;
static const PhysParamId_t kNuisEffRHCnumuCCWS1pic06         = kNuis596;
static const PhysParamId_t kNuisEffRHCnumuCCWS1pic07         = kNuis597;
static const PhysParamId_t kNuisEffRHCnumuCCWS1pic08         = kNuis598; //
static const PhysParamId_t kNuisEffRHCnumuCCWS1piz01         = kNuis599;
static const PhysParamId_t kNuisEffRHCnumuCCWS1piz02         = kNuis600;
static const PhysParamId_t kNuisEffRHCnumuCCWS1piz03         = kNuis601; //
static const PhysParamId_t kNuisEffRHCnumuCCWSother01        = kNuis602; //
static const PhysParamId_t kNuisEffRHCnueCC0pi01             = kNuis603;
static const PhysParamId_t kNuisEffRHCnueCC0pi02             = kNuis604;
static const PhysParamId_t kNuisEffRHCnueCC0pi03             = kNuis605;
static const PhysParamId_t kNuisEffRHCnueCC0pi04             = kNuis606;
static const PhysParamId_t kNuisEffRHCnueCC0pi05             = kNuis607;
static const PhysParamId_t kNuisEffRHCnueCC0pi06             = kNuis608;
static const PhysParamId_t kNuisEffRHCnueCC0pi07             = kNuis609;
static const PhysParamId_t kNuisEffRHCnueCC0pi08             = kNuis610;
static const PhysParamId_t kNuisEffRHCnueCC0pi09             = kNuis611; //
static const PhysParamId_t kNuisEffRHCnueCC1pic01            = kNuis612;
static const PhysParamId_t kNuisEffRHCnueCC1pic02            = kNuis613;
static const PhysParamId_t kNuisEffRHCnueCC1pic03            = kNuis614;
static const PhysParamId_t kNuisEffRHCnueCC1pic04            = kNuis615;
static const PhysParamId_t kNuisEffRHCnueCC1pic05            = kNuis616;
static const PhysParamId_t kNuisEffRHCnueCC1pic06            = kNuis617;
static const PhysParamId_t kNuisEffRHCnueCC1pic07            = kNuis618;
static const PhysParamId_t kNuisEffRHCnueCC1pic08            = kNuis619;
static const PhysParamId_t kNuisEffRHCnueCC1pic09            = kNuis620; //
static const PhysParamId_t kNuisEffRHCnueCC1piz01            = kNuis621;
static const PhysParamId_t kNuisEffRHCnueCC1piz02            = kNuis622;
static const PhysParamId_t kNuisEffRHCnueCC1piz03            = kNuis623;
static const PhysParamId_t kNuisEffRHCnueCC1piz04            = kNuis624;
static const PhysParamId_t kNuisEffRHCnueCC1piz05            = kNuis625;
static const PhysParamId_t kNuisEffRHCnueCC1piz06            = kNuis626;
static const PhysParamId_t kNuisEffRHCnueCC1piz07            = kNuis627;
static const PhysParamId_t kNuisEffRHCnueCC1piz08            = kNuis628;
static const PhysParamId_t kNuisEffRHCnueCC1piz09            = kNuis629; //
static const PhysParamId_t kNuisEffRHCnueCCother01           = kNuis630;
static const PhysParamId_t kNuisEffRHCnueCCother02           = kNuis631;
static const PhysParamId_t kNuisEffRHCnueCCother03           = kNuis632;
static const PhysParamId_t kNuisEffRHCnueCCother04           = kNuis633;
static const PhysParamId_t kNuisEffRHCnueCCother05           = kNuis634;
static const PhysParamId_t kNuisEffRHCnueCCother06           = kNuis635;
static const PhysParamId_t kNuisEffRHCnueCCother07           = kNuis636;
static const PhysParamId_t kNuisEffRHCnueCCother08           = kNuis637;
static const PhysParamId_t kNuisEffRHCnueCCother09           = kNuis638;
static const PhysParamId_t kNuisEffRHCnueCCother10           = kNuis639;
static const PhysParamId_t kNuisEffRHCnueCCother11           = kNuis640; //
static const PhysParamId_t kNuisEffRHCnueCCWS01              = kNuis641;
static const PhysParamId_t kNuisEffRHCnueCCWS02              = kNuis642; //
static const PhysParamId_t kNuisEffRHCNC0pi01                = kNuis643;
static const PhysParamId_t kNuisEffRHCNC0pi02                = kNuis644;
static const PhysParamId_t kNuisEffRHCNC0pi03                = kNuis645;
static const PhysParamId_t kNuisEffRHCNC1pic01               = kNuis646;
static const PhysParamId_t kNuisEffRHCNC1pic02               = kNuis647;
static const PhysParamId_t kNuisEffRHCNC1pic03               = kNuis648;
static const PhysParamId_t kNuisEffRHCNC1piz01               = kNuis649;
static const PhysParamId_t kNuisEffRHCNC1piz02               = kNuis650;
static const PhysParamId_t kNuisEffRHCNC1piz03               = kNuis651;
static const PhysParamId_t kNuisEffRHCNCother01              = kNuis652;
static const PhysParamId_t kNuisEffRHCNCother02              = kNuis653;
static const PhysParamId_t kNuisEffRHCNCother03              = kNuis654;
static const PhysParamId_t kNuisEffRHCNeutrinoElec           = kNuis655;
static const PhysParamId_t kNuisEffRHCIMD                    = kNuis656; //


// Boundaries between parameter types
static const PhysParamId_t kOscFirstParam            = kPhypMixing23; 
static const PhysParamId_t kOscLastParam             = kPhypDm12sq;
static const PhysParamId_t kNuisFluxFirstParameter   = kNuisFHCNuMuFlux00;
static const PhysParamId_t kNuisFluxLastParameter    = kNuisRHCNuEBarFDFlux06;
static const PhysParamId_t kNuisNDFluxFirstParameter = kNuisFHCNuMuFlux00;
static const PhysParamId_t kNuisNDFluxLastParameter  = kNuisRHCNuEBarFlux06;
static const PhysParamId_t kNuisFDFluxFirstParameter = kNuisFHCNuMuFDFlux00;
static const PhysParamId_t kNuisFDFluxLastParameter  = kNuisRHCNuEBarFDFlux06;
static const PhysParamId_t kNuisIntFirstParameter    = kNuisIntNuCCQE1;
static const PhysParamId_t kNuisIntLastParameter     = kNuisIntTarget;
static const PhysParamId_t kNuisDetFirstParameter    = kNuisEffFHCnumuCC0pi1trk01; // Wrong - does not include FD
static const PhysParamId_t kNuisDetLastParameter     = kNuisEffRHCIMD;             // Wrong - does not include FD
static const PhysParamId_t kNuisNDDetFirstParameter  = kNuisEffFHCnumuCC0pi1trk01;
static const PhysParamId_t kNuisNDDetLastParameter   = kNuisEffRHCIMD;
static const PhysParamId_t kNuisFDDetFirstParameter  = kNuisEffFDNuMuLikeCCHigh;
static const PhysParamId_t kNuisFDDetLastParameter   = kNuisEffFDNuELikeCCLow;


// ...........................................................................
//  List of physics parameters considered in this analysis: ND + FD
// ...........................................................................
//

static const PhysParamId_t kFitParam[kNFitParams] =
{
  //Oscillation parameters
  kPhypMixing23,
  kPhypMixing13,
  kPhypMixing12,
  kPhypCPV,
  kPhypDm23sq,
  kPhypDm12sq,
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
  
   //Far detector flux
   // FHC flux
   kNuisFHCNuMuFDFlux00,
   kNuisFHCNuMuFDFlux01,
   kNuisFHCNuMuFDFlux02,
   kNuisFHCNuMuFDFlux03,
   kNuisFHCNuMuFDFlux04,
   kNuisFHCNuMuFDFlux05,
   kNuisFHCNuMuFDFlux06,
   kNuisFHCNuMuFDFlux07,
   kNuisFHCNuMuFDFlux08,
   kNuisFHCNuMuFDFlux09,
   kNuisFHCNuMuFDFlux10,
   kNuisFHCNuMuFDFlux11,
   kNuisFHCNuMuFDFlux12,
   kNuisFHCNuMuFDFlux13,
   kNuisFHCNuMuFDFlux14,
   kNuisFHCNuMuFDFlux15,
   kNuisFHCNuMuFDFlux16,
   kNuisFHCNuMuFDFlux17,
   kNuisFHCNuMuFDFlux18,
   kNuisFHCNuMuBarFDFlux00,
   kNuisFHCNuMuBarFDFlux01,
   kNuisFHCNuMuBarFDFlux02,
   kNuisFHCNuMuBarFDFlux03,
   kNuisFHCNuMuBarFDFlux04,
   kNuisFHCNuMuBarFDFlux05,
   kNuisFHCNuMuBarFDFlux06,
   kNuisFHCNuMuBarFDFlux07,
   kNuisFHCNuMuBarFDFlux08,
   kNuisFHCNuMuBarFDFlux09,
   kNuisFHCNuMuBarFDFlux10,
   kNuisFHCNuMuBarFDFlux11,
   kNuisFHCNuMuBarFDFlux12,
   kNuisFHCNuMuBarFDFlux13,
   kNuisFHCNuMuBarFDFlux14,
   kNuisFHCNuMuBarFDFlux15,
   kNuisFHCNuMuBarFDFlux16,
   kNuisFHCNuMuBarFDFlux17,
   kNuisFHCNuMuBarFDFlux18,
   kNuisFHCNuEFDFlux00,
   kNuisFHCNuEFDFlux01,
   kNuisFHCNuEFDFlux02,
   kNuisFHCNuEFDFlux03,
   kNuisFHCNuEFDFlux04,
   kNuisFHCNuEFDFlux05,
   kNuisFHCNuEFDFlux06,
   kNuisFHCNuEBarFDFlux00,
   kNuisFHCNuEBarFDFlux01,
   kNuisFHCNuEBarFDFlux02,
   kNuisFHCNuEBarFDFlux03,
   kNuisFHCNuEBarFDFlux04,
   kNuisFHCNuEBarFDFlux05,
   kNuisFHCNuEBarFDFlux06,
   // RHC flux
   kNuisRHCNuMuFDFlux00,
   kNuisRHCNuMuFDFlux01,
   kNuisRHCNuMuFDFlux02,
   kNuisRHCNuMuFDFlux03,
   kNuisRHCNuMuFDFlux04,
   kNuisRHCNuMuFDFlux05,
   kNuisRHCNuMuFDFlux06,
   kNuisRHCNuMuFDFlux07,
   kNuisRHCNuMuFDFlux08,
   kNuisRHCNuMuFDFlux09,
   kNuisRHCNuMuFDFlux10,
   kNuisRHCNuMuFDFlux11,
   kNuisRHCNuMuFDFlux12,
   kNuisRHCNuMuFDFlux13,
   kNuisRHCNuMuFDFlux14,
   kNuisRHCNuMuFDFlux15,
   kNuisRHCNuMuFDFlux16,
   kNuisRHCNuMuFDFlux17,
   kNuisRHCNuMuFDFlux18,
   kNuisRHCNuMuBarFDFlux00,
   kNuisRHCNuMuBarFDFlux01,
   kNuisRHCNuMuBarFDFlux02,
   kNuisRHCNuMuBarFDFlux03,
   kNuisRHCNuMuBarFDFlux04,
   kNuisRHCNuMuBarFDFlux05,
   kNuisRHCNuMuBarFDFlux06,
   kNuisRHCNuMuBarFDFlux07,
   kNuisRHCNuMuBarFDFlux08,
   kNuisRHCNuMuBarFDFlux09,
   kNuisRHCNuMuBarFDFlux10,
   kNuisRHCNuMuBarFDFlux11,
   kNuisRHCNuMuBarFDFlux12,
   kNuisRHCNuMuBarFDFlux13,
   kNuisRHCNuMuBarFDFlux14,
   kNuisRHCNuMuBarFDFlux15,
   kNuisRHCNuMuBarFDFlux16,
   kNuisRHCNuMuBarFDFlux17,
   kNuisRHCNuMuBarFDFlux18,
   kNuisRHCNuEFDFlux00,
   kNuisRHCNuEFDFlux01,
   kNuisRHCNuEFDFlux02,
   kNuisRHCNuEFDFlux03,
   kNuisRHCNuEFDFlux04,
   kNuisRHCNuEFDFlux05,
   kNuisRHCNuEFDFlux06,
   kNuisRHCNuEBarFDFlux00,
   kNuisRHCNuEBarFDFlux01,
   kNuisRHCNuEBarFDFlux02,
   kNuisRHCNuEBarFDFlux03,
   kNuisRHCNuEBarFDFlux04,
   kNuisRHCNuEBarFDFlux05,
   kNuisRHCNuEBarFDFlux06,
  
   // Cross-sections
   kNuisIntNuCCQE1               ,
   kNuisIntNuCCQE2               ,
   kNuisIntNuCCQE3               ,
   kNuisIntNuBarCCQE1            ,
   kNuisIntNuBarCCQE2            ,
   kNuisIntNuBarCCQE3            ,
   kNuisIntNuCCMEC               ,
   kNuisIntNuBarCCMEC            ,
   kNuisIntNuCC1piz1             ,
   kNuisIntNuCC1piz2             ,
   kNuisIntNuCC1piz3             ,
   kNuisIntNuCC1pic1             ,
   kNuisIntNuCC1pic2             ,
   kNuisIntNuCC1pic3             ,
   kNuisIntNuBarCC1piz1          ,
   kNuisIntNuBarCC1piz2          ,
   kNuisIntNuBarCC1piz3          ,
   kNuisIntNuBarCC1pic1          ,
   kNuisIntNuBarCC1pic2          ,
   kNuisIntNuBarCC1pic3          ,
   kNuisIntNuCC2Pi               ,
   kNuisIntNuBarCC2Pi            ,
   kNuisIntNuDIS1                ,
   kNuisIntNuDIS2                ,
   kNuisIntNuDIS3                ,
   kNuisIntNuBarDIS1             ,
   kNuisIntNuBarDIS2             ,
   kNuisIntNuBarDIS3             ,
   kNuisIntNormNuCoherent        ,
   kNuisIntNormNuBarCoherent     ,
   kNuisIntNuNormNC              ,
   kNuisIntNuBarNormNC           ,
   kNuisIntNormNuMuToNuE         ,
   kNuisIntNormNuMuBarToNuEBar   ,
   kNuisIntPiMeanFreePath        ,
   kNuisIntNucMeanFreePath       ,
   kNuisIntFracPiChargeExchange  ,
   kNuisIntFracPiInelastic       ,
   kNuisIntFracPiAbsorb          ,
   kNuisIntFracPiProduction      ,
   kNuisIntFracNucChargeExchange ,
   kNuisIntFracNucInelastic      ,
   kNuisIntFracNucAbsorb         ,
   kNuisIntFracNucProduction     ,
   kNuisIntTarget                ,
   // Detector systematics
  kNuisEffFHCnumuCC0pi1trk01     ,
  kNuisEffFHCnumuCC0pi1trk02     ,
  kNuisEffFHCnumuCC0pi1trk03     ,
  kNuisEffFHCnumuCC0pi1trk04     ,
  kNuisEffFHCnumuCC0pi1trk05     ,
  kNuisEffFHCnumuCC0pi1trk06     ,
  kNuisEffFHCnumuCC0pi1trk07     ,
  kNuisEffFHCnumuCC0pi1trk08     ,
  kNuisEffFHCnumuCC0pi1trk09     ,
  kNuisEffFHCnumuCC0pi2trk01     ,
  kNuisEffFHCnumuCC0pi2trk02     ,
  kNuisEffFHCnumuCC0pi2trk03     ,
  kNuisEffFHCnumuCC0pi2trk04     ,
  kNuisEffFHCnumuCC0pi2trk05     ,
  kNuisEffFHCnumuCC0pi2trk06     ,
  kNuisEffFHCnumuCC0pi2trk07     ,
  kNuisEffFHCnumuCC0pi2trk08     ,
  kNuisEffFHCnumuCC0pi2trk09     ,
  kNuisEffFHCnumuCC0piNtrk01     ,
  kNuisEffFHCnumuCC0piNtrk02     ,
  kNuisEffFHCnumuCC0piNtrk03     ,
  kNuisEffFHCnumuCC0piNtrk04     ,
  kNuisEffFHCnumuCC0piNtrk05     ,
  kNuisEffFHCnumuCC0piNtrk06     ,
  kNuisEffFHCnumuCC0piNtrk07     ,
  kNuisEffFHCnumuCC0piNtrk08     ,
  kNuisEffFHCnumuCC0piNtrk09     ,
  kNuisEffFHCnumuCC0piNtrk10     ,
  kNuisEffFHCnumuCC0piNtrk11     ,
  kNuisEffFHCnumuCC0piNtrk12     ,
  kNuisEffFHCnumuCC0piNtrk13     ,
  kNuisEffFHCnumuCC0piNtrk14     ,
  kNuisEffFHCnumuCC0piNtrk15     ,
  kNuisEffFHCnumuCC1pi3trkDelta01,
  kNuisEffFHCnumuCC1pi3trkDelta02,
  kNuisEffFHCnumuCC1pi3trkDelta03,
  kNuisEffFHCnumuCC1pi3trkDelta04,
  kNuisEffFHCnumuCC1pi3trkDelta05,
  kNuisEffFHCnumuCC1pi3trkDelta06,
  kNuisEffFHCnumuCC1pi3trkDelta07,
  kNuisEffFHCnumuCC1pi3trkDelta08,
  kNuisEffFHCnumuCC1pi3trkDelta09,
  kNuisEffFHCnumuCC1pi3trkDelta10,
  kNuisEffFHCnumuCC1pi3trkDelta11,
  kNuisEffFHCnumuCC1pi3trkDelta12,
  kNuisEffFHCnumuCC1pi3trkDelta13,
  kNuisEffFHCnumuCC1pi3trkDelta14,
  kNuisEffFHCnumuCC1pi3trkDelta15,
  kNuisEffFHCnumuCC1pic01        ,
  kNuisEffFHCnumuCC1pic02        ,
  kNuisEffFHCnumuCC1pic03        ,
  kNuisEffFHCnumuCC1pic04        ,
  kNuisEffFHCnumuCC1pic05        ,
  kNuisEffFHCnumuCC1pic06        ,
  kNuisEffFHCnumuCC1pic07        ,
  kNuisEffFHCnumuCC1pic08        ,
  kNuisEffFHCnumuCC1pic09        ,
  kNuisEffFHCnumuCC1piz01        ,
  kNuisEffFHCnumuCC1piz02        ,
  kNuisEffFHCnumuCC1piz03        ,
  kNuisEffFHCnumuCC1piz04        ,
  kNuisEffFHCnumuCC1piz05        ,
  kNuisEffFHCnumuCC1piz06        ,
  kNuisEffFHCnumuCC1piz07        ,
  kNuisEffFHCnumuCC1piz08        ,
  kNuisEffFHCnumuCC1piz09        ,
  kNuisEffFHCnumuCC1pic1piz01    ,
  kNuisEffFHCnumuCC1pic1piz02    ,
  kNuisEffFHCnumuCC1pic1piz03    ,
  kNuisEffFHCnumuCC1pic1piz04    ,
  kNuisEffFHCnumuCC1pic1piz05    ,
  kNuisEffFHCnumuCC1pic1piz06    ,
  kNuisEffFHCnumuCC1pic1piz07    ,
  kNuisEffFHCnumuCC1pic1piz08    ,
  kNuisEffFHCnumuCC1pic1piz09    ,
  kNuisEffFHCnumuCCother01       ,
  kNuisEffFHCnumuCCother02       ,
  kNuisEffFHCnumuCCother03       ,
  kNuisEffFHCnumuCCother04       ,
  kNuisEffFHCnumuCCother05       ,
  kNuisEffFHCnumuCCother06       ,
  kNuisEffFHCnumuCCother07       ,
  kNuisEffFHCnumuCCother08       ,
  kNuisEffFHCnumuCCother09       ,
  kNuisEffFHCnumuCCother10       ,
  kNuisEffFHCnumuCCother11       ,
  kNuisEffFHCnumuCCWS0pi01       ,
  kNuisEffFHCnumuCCWS0pi02       ,
  kNuisEffFHCnumuCCWS0pi03       ,
  kNuisEffFHCnumuCCWS0pi04       ,
  kNuisEffFHCnumuCCWS0pi05       ,
  kNuisEffFHCnumuCCWS1pic01      ,
  kNuisEffFHCnumuCCWS1pic02      ,
  kNuisEffFHCnumuCCWS1pic03      ,
  kNuisEffFHCnumuCCWS1pic04      ,
  kNuisEffFHCnumuCCWS1pic05      ,
  kNuisEffFHCnumuCCWS1pic06      ,
  kNuisEffFHCnumuCCWS1pic07      ,
  kNuisEffFHCnumuCCWS1pic08      ,
  kNuisEffFHCnumuCCWS1piz01      ,
  kNuisEffFHCnumuCCWS1piz02      ,
  kNuisEffFHCnumuCCWS1piz03      ,
  kNuisEffFHCnumuCCWSother01     ,
  kNuisEffFHCnueCC0pi01          ,
  kNuisEffFHCnueCC0pi02          ,
  kNuisEffFHCnueCC0pi03          ,
  kNuisEffFHCnueCC0pi04          ,
  kNuisEffFHCnueCC0pi05          ,
  kNuisEffFHCnueCC0pi06          ,
  kNuisEffFHCnueCC0pi07          ,
  kNuisEffFHCnueCC0pi08          ,
  kNuisEffFHCnueCC0pi09          ,
  kNuisEffFHCnueCC1pic01         ,
  kNuisEffFHCnueCC1pic02         ,
  kNuisEffFHCnueCC1pic03         ,
  kNuisEffFHCnueCC1pic04         ,
  kNuisEffFHCnueCC1pic05         ,
  kNuisEffFHCnueCC1pic06         ,
  kNuisEffFHCnueCC1pic07         ,
  kNuisEffFHCnueCC1pic08         ,
  kNuisEffFHCnueCC1pic09         ,
  kNuisEffFHCnueCC1piz01         ,
  kNuisEffFHCnueCC1piz02         ,
  kNuisEffFHCnueCC1piz03         ,
  kNuisEffFHCnueCC1piz04         ,
  kNuisEffFHCnueCC1piz05         ,
  kNuisEffFHCnueCC1piz06         ,
  kNuisEffFHCnueCC1piz07         ,
  kNuisEffFHCnueCC1piz08         ,
  kNuisEffFHCnueCC1piz09         ,
  kNuisEffFHCnueCCother01        ,
  kNuisEffFHCnueCCother02        ,
  kNuisEffFHCnueCCother03        ,
  kNuisEffFHCnueCCother04        ,
  kNuisEffFHCnueCCother05        ,
  kNuisEffFHCnueCCother06        ,
  kNuisEffFHCnueCCother07        ,
  kNuisEffFHCnueCCother08        ,
  kNuisEffFHCnueCCother09        ,
  kNuisEffFHCnueCCother10        ,
  kNuisEffFHCnueCCother11        ,
  kNuisEffFHCnueCCWS01           ,
  kNuisEffFHCnueCCWS02           ,
  kNuisEffFHCNC0pi01             ,
  kNuisEffFHCNC0pi02             ,
  kNuisEffFHCNC0pi03             ,
  kNuisEffFHCNC1pic01            ,
  kNuisEffFHCNC1pic02            ,
  kNuisEffFHCNC1pic03            ,
  kNuisEffFHCNC1piz01            ,
  kNuisEffFHCNC1piz02            ,
  kNuisEffFHCNC1piz03            ,
  kNuisEffFHCNCother01           ,
  kNuisEffFHCNCother02           ,
  kNuisEffFHCNCother03           ,
  kNuisEffFHCNeutrinoElec        ,
  kNuisEffFHCIMD                 ,
  kNuisEffRHCnumuCC0pi1trk01     ,
  kNuisEffRHCnumuCC0pi1trk02     ,
  kNuisEffRHCnumuCC0pi1trk03     ,
  kNuisEffRHCnumuCC0pi1trk04     ,
  kNuisEffRHCnumuCC0pi1trk05     ,
  kNuisEffRHCnumuCC0pi1trk06     ,
  kNuisEffRHCnumuCC0pi1trk07     ,
  kNuisEffRHCnumuCC0pi1trk08     ,
  kNuisEffRHCnumuCC0pi1trk09     ,
  kNuisEffRHCnumuCC0pi2trk01     ,
  kNuisEffRHCnumuCC0pi2trk02     ,
  kNuisEffRHCnumuCC0pi2trk03     ,
  kNuisEffRHCnumuCC0pi2trk04     ,
  kNuisEffRHCnumuCC0pi2trk05     ,
  kNuisEffRHCnumuCC0pi2trk06     ,
  kNuisEffRHCnumuCC0pi2trk07     ,
  kNuisEffRHCnumuCC0pi2trk08     ,
  kNuisEffRHCnumuCC0pi2trk09     ,
  kNuisEffRHCnumuCC0piNtrk01     ,
  kNuisEffRHCnumuCC0piNtrk02     ,
  kNuisEffRHCnumuCC0piNtrk03     ,
  kNuisEffRHCnumuCC0piNtrk04     ,
  kNuisEffRHCnumuCC0piNtrk05     ,
  kNuisEffRHCnumuCC0piNtrk06     ,
  kNuisEffRHCnumuCC0piNtrk07     ,
  kNuisEffRHCnumuCC0piNtrk08     ,
  kNuisEffRHCnumuCC0piNtrk09     ,
  kNuisEffRHCnumuCC0piNtrk10     ,
  kNuisEffRHCnumuCC0piNtrk11     ,
  kNuisEffRHCnumuCC0piNtrk12     ,
  kNuisEffRHCnumuCC0piNtrk13     ,
  kNuisEffRHCnumuCC0piNtrk14     ,
  kNuisEffRHCnumuCC0piNtrk15     ,
  kNuisEffRHCnumuCC1pi3trkDelta01,
  kNuisEffRHCnumuCC1pi3trkDelta02,
  kNuisEffRHCnumuCC1pi3trkDelta03,
  kNuisEffRHCnumuCC1pi3trkDelta04,
  kNuisEffRHCnumuCC1pi3trkDelta05,
  kNuisEffRHCnumuCC1pi3trkDelta06,
  kNuisEffRHCnumuCC1pi3trkDelta07,
  kNuisEffRHCnumuCC1pi3trkDelta08,
  kNuisEffRHCnumuCC1pi3trkDelta09,
  kNuisEffRHCnumuCC1pi3trkDelta10,
  kNuisEffRHCnumuCC1pi3trkDelta11,
  kNuisEffRHCnumuCC1pi3trkDelta12,
  kNuisEffRHCnumuCC1pi3trkDelta13,
  kNuisEffRHCnumuCC1pi3trkDelta14,
  kNuisEffRHCnumuCC1pi3trkDelta15,
  kNuisEffRHCnumuCC1pic01        ,
  kNuisEffRHCnumuCC1pic02        ,
  kNuisEffRHCnumuCC1pic03        ,
  kNuisEffRHCnumuCC1pic04        ,
  kNuisEffRHCnumuCC1pic05        ,
  kNuisEffRHCnumuCC1pic06        ,
  kNuisEffRHCnumuCC1pic07        ,
  kNuisEffRHCnumuCC1pic08        ,
  kNuisEffRHCnumuCC1pic09        ,
  kNuisEffRHCnumuCC1piz01        ,
  kNuisEffRHCnumuCC1piz02        ,
  kNuisEffRHCnumuCC1piz03        ,
  kNuisEffRHCnumuCC1piz04        ,
  kNuisEffRHCnumuCC1piz05        ,
  kNuisEffRHCnumuCC1piz06        ,
  kNuisEffRHCnumuCC1piz07        ,
  kNuisEffRHCnumuCC1piz08        ,
  kNuisEffRHCnumuCC1piz09        ,
  kNuisEffRHCnumuCC1pic1piz01    ,
  kNuisEffRHCnumuCC1pic1piz02    ,
  kNuisEffRHCnumuCC1pic1piz03    ,
  kNuisEffRHCnumuCC1pic1piz04    ,
  kNuisEffRHCnumuCC1pic1piz05    ,
  kNuisEffRHCnumuCC1pic1piz06    ,
  kNuisEffRHCnumuCC1pic1piz07    ,
  kNuisEffRHCnumuCC1pic1piz08    ,
  kNuisEffRHCnumuCC1pic1piz09    ,
  kNuisEffRHCnumuCCother01       ,
  kNuisEffRHCnumuCCother02       ,
  kNuisEffRHCnumuCCother03       ,
  kNuisEffRHCnumuCCother04       ,
  kNuisEffRHCnumuCCother05       ,
  kNuisEffRHCnumuCCother06       ,
  kNuisEffRHCnumuCCother07       ,
  kNuisEffRHCnumuCCother08       ,
  kNuisEffRHCnumuCCother09       ,
  kNuisEffRHCnumuCCother10       ,
  kNuisEffRHCnumuCCother11       ,
  kNuisEffRHCnumuCCWS0pi01       ,
  kNuisEffRHCnumuCCWS0pi02       ,
  kNuisEffRHCnumuCCWS0pi03       ,
  kNuisEffRHCnumuCCWS0pi04       ,
  kNuisEffRHCnumuCCWS0pi05       ,
  kNuisEffRHCnumuCCWS1pic01      ,
  kNuisEffRHCnumuCCWS1pic02      ,
  kNuisEffRHCnumuCCWS1pic03      ,
  kNuisEffRHCnumuCCWS1pic04      ,
  kNuisEffRHCnumuCCWS1pic05      ,
  kNuisEffRHCnumuCCWS1pic06      ,
  kNuisEffRHCnumuCCWS1pic07      ,
  kNuisEffRHCnumuCCWS1pic08      ,
  kNuisEffRHCnumuCCWS1piz01      ,
  kNuisEffRHCnumuCCWS1piz02      ,
  kNuisEffRHCnumuCCWS1piz03      ,
  kNuisEffRHCnumuCCWSother01     ,
  kNuisEffRHCnueCC0pi01          ,
  kNuisEffRHCnueCC0pi02          ,
  kNuisEffRHCnueCC0pi03          ,
  kNuisEffRHCnueCC0pi04          ,
  kNuisEffRHCnueCC0pi05          ,
  kNuisEffRHCnueCC0pi06          ,
  kNuisEffRHCnueCC0pi07          ,
  kNuisEffRHCnueCC0pi08          ,
  kNuisEffRHCnueCC0pi09          ,
  kNuisEffRHCnueCC1pic01         ,
  kNuisEffRHCnueCC1pic02         ,
  kNuisEffRHCnueCC1pic03         ,
  kNuisEffRHCnueCC1pic04         ,
  kNuisEffRHCnueCC1pic05         ,
  kNuisEffRHCnueCC1pic06         ,
  kNuisEffRHCnueCC1pic07         ,
  kNuisEffRHCnueCC1pic08         ,
  kNuisEffRHCnueCC1pic09         ,
  kNuisEffRHCnueCC1piz01         ,
  kNuisEffRHCnueCC1piz02         ,
  kNuisEffRHCnueCC1piz03         ,
  kNuisEffRHCnueCC1piz04         ,
  kNuisEffRHCnueCC1piz05         ,
  kNuisEffRHCnueCC1piz06         ,
  kNuisEffRHCnueCC1piz07         ,
  kNuisEffRHCnueCC1piz08         ,
  kNuisEffRHCnueCC1piz09         ,
  kNuisEffRHCnueCCother01        ,
  kNuisEffRHCnueCCother02        ,
  kNuisEffRHCnueCCother03        ,
  kNuisEffRHCnueCCother04        ,
  kNuisEffRHCnueCCother05        ,
  kNuisEffRHCnueCCother06        ,
  kNuisEffRHCnueCCother07        ,
  kNuisEffRHCnueCCother08        ,
  kNuisEffRHCnueCCother09        ,
  kNuisEffRHCnueCCother10        ,
  kNuisEffRHCnueCCother11        ,
  kNuisEffRHCnueCCWS01           ,
  kNuisEffRHCnueCCWS02           ,
  kNuisEffRHCNC0pi01             ,
  kNuisEffRHCNC0pi02             ,
  kNuisEffRHCNC0pi03             ,
  kNuisEffRHCNC1pic01            ,
  kNuisEffRHCNC1pic02            ,
  kNuisEffRHCNC1pic03            ,
  kNuisEffRHCNC1piz01            ,
  kNuisEffRHCNC1piz02            ,
  kNuisEffRHCNC1piz03            ,
  kNuisEffRHCNCother01           ,
  kNuisEffRHCNCother02           ,
  kNuisEffRHCNCother03           ,
  kNuisEffRHCNeutrinoElec        ,
  kNuisEffRHCIMD                 ,
  // Far detector systematics
  kNuisEffFDNuMuLikeCCHigh,
  kNuisEffFDNuMuLikeCCLow,
  kNuisEffFDNuELikeCCHigh,
  kNuisEffFDNuELikeCCLow ,
  kNuisEffNuMuCC0pi1trk  ,
  kNuisEffNuMuCC0pi2trk  ,
  kNuisEffNuMuCC1piC     ,
  kNuisEffNuMuCC1pi0     ,
  kNuisEffNuMuCC1piC1pi0 ,
  kNuisEffNuMuCCoth      ,
  kNuisEffNuECC          ,
  kNuisEffNuMuCCWS       ,
  kNuisEffNC            
  
  
};

// Shifted these big arrays off into their own little files to keep this a bit tidier.
#include "dune/Conventions/FitParamArrays/FitParamTrueRanges.h"
#include "dune/Conventions/FitParamArrays/FitParamRecoRanges.h"
#include "dune/Conventions/FitParamArrays/FitParamTypes.h"

static const int kNFitParamsWithSplines = 10;
static const PhysParamId_t kFitParamsWithSplines[kNFitParamsWithSplines] = 
{
   kNuisIntPiMeanFreePath       ,
   kNuisIntNucMeanFreePath      ,
   kNuisIntFracPiChargeExchange ,
   kNuisIntFracPiInelastic      ,
   kNuisIntFracPiAbsorb         ,
   kNuisIntFracPiProduction     ,
   kNuisIntFracNucChargeExchange,
   kNuisIntFracNucInelastic     ,
   kNuisIntFracNucAbsorb        ,
   kNuisIntFracNucProduction    
};

} // conv

//
// utility methods
//

namespace util {
  // If you give a CorrelatedSystematics object, it'll ignore your list's standard systematics and use this set instead
  FitParamList * GetFitParameterList (Option_t * param_list = "standard", const CorrelatedSystematics * syst = 0);


  bool IsNuFluxRelated  (conv::PhysParamId_t p);
  bool IsNuIntRelated   (conv::PhysParamId_t p);
  bool IsNuDetRelated   (conv::PhysParamId_t p);
  bool IsFSI            (conv::PhysParamId_t p);
  
  bool IsNDFluxRelated  (conv::PhysParamId_t p);
  bool IsFDFluxRelated  (conv::PhysParamId_t p);
  bool IsNuNDDetRelated (conv::PhysParamId_t p);
  bool IsNuFDDetRelated (conv::PhysParamId_t p);

  conv::FitParamGroup_t GetParameterGroup(conv::PhysParamId_t p);
  // Get the list of parameters associated with a set name (eg flux, int, ccqe, fsi, 3fosc)
  std::vector<conv::PhysParamId_t> GetParameterSet(std::string set_name);

  bool ParamIsAppliedTo(conv::BeamConf_t b, conv::Sample_t s, conv::Detector_t d, 
                        conv::ReacMode_t m, conv::PhysParamId_t p);
  bool OscProbIsAppliedTo(conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s,
                          conv::ReacMode_t m);
  bool ParamHasSplines(conv::PhysParamId_t p);
  
  // Return pointer to array of min/max                      
  const double * EtrueRange (conv::PhysParamId_t p);
  const double * Q2trueRange(conv::PhysParamId_t p);

} //util

} // valor

#endif

