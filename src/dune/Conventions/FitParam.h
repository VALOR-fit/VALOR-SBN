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
#include "valor/FitCore/CorrelatedSystematics.h"
#include "valor/FitCore/FitParamList.h"
#include "valor/FitCore/PhysHypothesis.h"

//dune
#include "dune/Conventions/Detector.h"
#include "dune/Conventions/BeamConf.h"
#include "dune/Conventions/DuneBuild.h"
#include "dune/Conventions/ReacMode.h"
#include "dune/Conventions/SampleKineBinning.h"
#include "dune/Conventions/FitParamGroup.h"

using std::string;

namespace valor {
namespace conv {

static const int kNFitParamsNuFluxND = 104; // neutrino flux related 104 ND 
static const int kNFitParamsNuFluxFD = 104; // neutrino flux related 104 FD 
static const int kNFitParamsNuFlux   = kNFitParamsNuFluxND + kNFitParamsNuFluxFD;
static const int kNFitParamsNuDetND  =   9; // near detector related: cc1trk, cc2trk, 1pic, 1pi0, 1pic1pi0, ccoth, nuecc, wscc, nc
static const int kNFitParamsNuDetFD  =  4; // far detector related: one per sample for now
static const int kNFitParamsNuDet    = kNFitParamsNuDetND+ kNFitParamsNuDetFD;
static const int kNFitParamsNuInt  =  43; // neutrino interactions related
static const int kNFitParamsNuOsc  =   6; //usual 3-flavour suspects

static const int kNFitParams   = kNFitParamsNuFlux+kNFitParamsNuInt+kNFitParamsNuDet+kNFitParamsNuOsc;
static const int kNFitParamsND = kNFitParamsNuFluxND+kNFitParamsNuInt+kNFitParamsNuDetND;

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

static const PhysParamId_t kNuisIntPiMeanFreePath        = kNuis260;
static const PhysParamId_t kNuisIntNucMeanFreePath       = kNuis261;
static const PhysParamId_t kNuisIntFracPiChargeExchange  = kNuis262;
static const PhysParamId_t kNuisIntFracPiInelastic       = kNuis263;
static const PhysParamId_t kNuisIntFracPiAbsorb          = kNuis264;
static const PhysParamId_t kNuisIntFracPiProduction      = kNuis265;
static const PhysParamId_t kNuisIntFracNucChargeExchange = kNuis266;
static const PhysParamId_t kNuisIntFracNucInelastic      = kNuis267;
static const PhysParamId_t kNuisIntFracNucAbsorb         = kNuis268;
static const PhysParamId_t kNuisIntFracNucProduction     = kNuis269;

static const PhysParamId_t kNuisIntHadronization         = kNuis270;

// Boundaries between parameter types
static const PhysParamId_t kOscFirstParam          = kPhypMixing23; 
static const PhysParamId_t kOscLastParam           = kPhypDm12sq;
static const PhysParamId_t kNuisFluxFirstParameter = kNuisFHCNuMuFlux00;
static const PhysParamId_t kNuisFluxLastParameter  = kNuisRHCNuEBarFDFlux06;
static const PhysParamId_t kNuisNDFluxFirstParameter = kNuisFHCNuMuFlux00;
static const PhysParamId_t kNuisNDFluxLastParameter  = kNuisRHCNuEBarFlux06;
static const PhysParamId_t kNuisFDFluxFirstParameter = kNuisFHCNuMuFDFlux00;
static const PhysParamId_t kNuisFDFluxLastParameter  = kNuisRHCNuEBarFDFlux06;
static const PhysParamId_t kNuisIntFirstParameter  = kNuisIntNuCCQE1;
static const PhysParamId_t kNuisIntLastParameter   = kNuisIntHadronization;
static const PhysParamId_t kNuisDetFirstParameter  = kNuisEffNuMuCC0pi1trk;
static const PhysParamId_t kNuisDetLastParameter   = kNuisEffFDNuELikeCCLow;
static const PhysParamId_t kNuisNDDetFirstParameter= kNuisEffNuMuCC0pi1trk;
static const PhysParamId_t kNuisNDDetLastParameter = kNuisEffNC;
static const PhysParamId_t kNuisFDDetFirstParameter= kNuisEffFDNuMuLikeCCHigh;
static const PhysParamId_t kNuisFDDetLastParameter = kNuisEffFDNuELikeCCLow;


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
   // Detector systematics
   kNuisEffNuMuCC0pi1trk,
   kNuisEffNuMuCC0pi2trk,
   kNuisEffNuMuCC1piC,
   kNuisEffNuMuCC1pi0,
   kNuisEffNuMuCC1piC1pi0,
   kNuisEffNuMuCCoth,
   kNuisEffNuECC,
   kNuisEffNuMuCCWS,
   kNuisEffNC,
  // Far detector systematics
  kNuisEffFDNuMuLikeCCHigh,
  kNuisEffFDNuMuLikeCCLow,
  kNuisEffFDNuELikeCCHigh,
  kNuisEffFDNuELikeCCLow
};


// ...........................................................................
//  List of physics parameters considered in this analysis: ND + FD
// ...........................................................................
//

static const PhysParamId_t kFitParamND[kNFitParamsND] =
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
   // Detector systematics
   kNuisEffNuMuCC0pi1trk,
   kNuisEffNuMuCC0pi2trk,
   kNuisEffNuMuCC1piC,
   kNuisEffNuMuCC1pi0,
   kNuisEffNuMuCC1piC1pi0,
   kNuisEffNuMuCCoth,
   kNuisEffNuECC,
   kNuisEffNuMuCCWS,
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
  //oscillation parameters
  true,
  true,
  true,
  true,
  true,
  true,
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
   // Far detector flux
   // FHC flux
   true,   // kNuisFHCNuMuFDFlux00
   true,   // kNuisFHCNuMuFDFlux01
   true,   // kNuisFHCNuMuFDFlux02
   true,   // kNuisFHCNuMuFDFlux03
   true,   // kNuisFHCNuMuFDFlux04
   true,   // kNuisFHCNuMuFDFlux05
   true,   // kNuisFHCNuMuFDFlux06
   true,   // kNuisFHCNuMuFDFlux07
   true,   // kNuisFHCNuMuFDFlux08
   true,   // kNuisFHCNuMuFDFlux09
   true,   // kNuisFHCNuMuFDFlux10
   true,   // kNuisFHCNuMuFDFlux11
   true,   // kNuisFHCNuMuFDFlux12
   true,   // kNuisFHCNuMuFDFlux13
   true,   // kNuisFHCNuMuFDFlux14
   true,   // kNuisFHCNuMuFDFlux15
   true,   // kNuisFHCNuMuFDFlux16
   true,   // kNuisFHCNuMuFDFlux17
   true,   // kNuisFHCNuMuFDFlux18
   true,   // kNuisFHCNuMuBarFDFlux00
   true,   // kNuisFHCNuMuBarFDFlux01
   true,   // kNuisFHCNuMuBarFDFlux02
   true,   // kNuisFHCNuMuBarFDFlux03
   true,   // kNuisFHCNuMuBarFDFlux04
   true,   // kNuisFHCNuMuBarFDFlux05
   true,   // kNuisFHCNuMuBarFDFlux06
   true,   // kNuisFHCNuMuBarFDFlux07
   true,   // kNuisFHCNuMuBarFDFlux08
   true,   // kNuisFHCNuMuBarFDFlux09
   true,   // kNuisFHCNuMuBarFDFlux10
   true,   // kNuisFHCNuMuBarFDFlux11
   true,   // kNuisFHCNuMuBarFDFlux12
   true,   // kNuisFHCNuMuBarFDFlux13
   true,   // kNuisFHCNuMuBarFDFlux14
   true,   // kNuisFHCNuMuBarFDFlux15
   true,   // kNuisFHCNuMuBarFDFlux16
   true,   // kNuisFHCNuMuBarFDFlux17
   true,   // kNuisFHCNuMuBarFDFlux18
   true,   // kNuisFHCNuEFDFlux00
   true,   // kNuisFHCNuEFDFlux01
   true,   // kNuisFHCNuEFDFlux02
   true,   // kNuisFHCNuEFDFlux03
   true,   // kNuisFHCNuEFDFlux04
   true,   // kNuisFHCNuEFDFlux05
   true,   // kNuisFHCNuEFDFlux06
   true,   // kNuisFHCNuEBarFDFlux00
   true,   // kNuisFHCNuEBarFDFlux01
   true,   // kNuisFHCNuEBarFDFlux02
   true,   // kNuisFHCNuEBarFDFlux03
   true,   // kNuisFHCNuEBarFDFlux04
   true,   // kNuisFHCNuEBarFDFlux05
   true,   // kNuisFHCNuEBarFDFlux06
   // RHC flux
   true,   // kNuisRHCNuMuFDFlux00
   true,   // kNuisRHCNuMuFDFlux01
   true,   // kNuisRHCNuMuFDFlux02
   true,   // kNuisRHCNuMuFDFlux03
   true,   // kNuisRHCNuMuFDFlux04
   true,   // kNuisRHCNuMuFDFlux05
   true,   // kNuisRHCNuMuFDFlux06
   true,   // kNuisRHCNuMuFDFlux07
   true,   // kNuisRHCNuMuFDFlux08
   true,   // kNuisRHCNuMuFDFlux09
   true,   // kNuisRHCNuMuFDFlux10
   true,   // kNuisRHCNuMuFDFlux11
   true,   // kNuisRHCNuMuFDFlux12
   true,   // kNuisRHCNuMuFDFlux13
   true,   // kNuisRHCNuMuFDFlux14
   true,   // kNuisRHCNuMuFDFlux15
   true,   // kNuisRHCNuMuFDFlux16
   true,   // kNuisRHCNuMuFDFlux17
   true,   // kNuisRHCNuMuFDFlux18
   true,   // kNuisRHCNuMuBarFDFlux00
   true,   // kNuisRHCNuMuBarFDFlux01
   true,   // kNuisRHCNuMuBarFDFlux02
   true,   // kNuisRHCNuMuBarFDFlux03
   true,   // kNuisRHCNuMuBarFDFlux04
   true,   // kNuisRHCNuMuBarFDFlux05
   true,   // kNuisRHCNuMuBarFDFlux06
   true,   // kNuisRHCNuMuBarFDFlux07
   true,   // kNuisRHCNuMuBarFDFlux08
   true,   // kNuisRHCNuMuBarFDFlux09
   true,   // kNuisRHCNuMuBarFDFlux10
   true,   // kNuisRHCNuMuBarFDFlux11
   true,   // kNuisRHCNuMuBarFDFlux12
   true,   // kNuisRHCNuMuBarFDFlux13
   true,   // kNuisRHCNuMuBarFDFlux14
   true,   // kNuisRHCNuMuBarFDFlux15
   true,   // kNuisRHCNuMuBarFDFlux16
   true,   // kNuisRHCNuMuBarFDFlux17
   true,   // kNuisRHCNuMuBarFDFlux18
   true,   // kNuisRHCNuEFDFlux00
   true,   // kNuisRHCNuEFDFlux01
   true,   // kNuisRHCNuEFDFlux02
   true,   // kNuisRHCNuEFDFlux03
   true,   // kNuisRHCNuEFDFlux04
   true,   // kNuisRHCNuEFDFlux05
   true,   // kNuisRHCNuEFDFlux06
   true,   // kNuisRHCNuEBarFDFlux00
   true,   // kNuisRHCNuEBarFDFlux01
   true,   // kNuisRHCNuEBarFDFlux02
   true,   // kNuisRHCNuEBarFDFlux03
   true,   // kNuisRHCNuEBarFDFlux04
   true,   // kNuisRHCNuEBarFDFlux05
   true,   // kNuisRHCNuEBarFDFlux06
     // Cross-sections
   true ,  // kNuisIntNuCCQE1
   true ,  // kNuisIntNuCCQE2
   true ,  // kNuisIntNuCCQE3
   true ,  // kNuisIntNuBarCCQE1
   true ,  // kNuisIntNuBarCCQE2
   true ,  // kNuisIntNuBarCCQE3
   false,  // kNuisIntNuCCMEC
   false,  // kNuisIntNuBarCCMEC
   true ,  // kNuisIntNuCC1piz1
   true ,  // kNuisIntNuCC1piz2
   true ,  // kNuisIntNuCC1piz3
   true ,  // kNuisIntNuCC1pic1
   true ,  // kNuisIntNuCC1pic2
   true ,  // kNuisIntNuCC1pic3
   true ,  // kNuisIntNuBarCC1piz1
   true ,  // kNuisIntNuBarCC1piz2
   true ,  // kNuisIntNuBarCC1piz3
   true ,  // kNuisIntNuBarCC1pic1
   true ,  // kNuisIntNuBarCC1pic2
   true ,  // kNuisIntNuBarCC1pic3
   false,  // kNuisIntNuCC2Pi
   false,  // kNuisIntNuBarCC2Pi
   true ,  // kNuisIntNuDIS1
   true ,  // kNuisIntNuDIS2
   true ,  // kNuisIntNuDIS3
   true ,  // kNuisIntNuBarDIS1
   true ,  // kNuisIntNuBarDIS2
   true ,  // kNuisIntNuBarDIS3
   false,  // kNuisIntNormNuCoherent
   false,  // kNuisIntNormNuBarCoherent
   false,  // kNuisIntNuNormNC
   false,  // kNuisIntNuBarNormNC
   false,  // kNuisIntNormNuMuToNuE
   false,  // kNuisIntPiMeanFreePath
   false,  // kNuisIntNucMeanFreePath
   false,  // kNuisIntFracPiChargeExchange
   false,  // kNuisIntFracPiInelastic
   false,  // kNuisIntFracPiAbsorb
   false,  // kNuisIntFracPiProduction
   false,  // kNuisIntFracNucChargeExchange
   false,  // kNuisIntFracNucInelastic
   false,  // kNuisIntFracNucAbsorb
   false,  // kNuisIntFracNucProduction
   // Detector systematics
   false,  // kNuisEffNuMuCC0pi1trk
   false,  // kNuisEffNuMuCC0pi2trk
   false,  // kNuisEffNuMuCC1piC
   false,  // kNuisEffNuMuCC1pi0
   false,  // kNuisEffNuMuCC1piC1pi0
   false,  // kNuisEffNuMuCCoth
   false,  // kNuisEffNuECC
   false,  // kNuisEffNuMuCCWS
   false,  // kNuisEffNC
  // Far detector systematics
   false,  // kNuisEffFDNuMuCCHigh
   false,  // kNuisEffFDNuMuCCLow
   false,  // kNuisEffFDNuECCHigh
   false   // kNuisEffFDNuECCLow
};

// Which is the true energy range?
static const double kFitParamEtrueRange[kNFitParams][2] =
{
  //oscillation parameters
  {0.0, kEtrueMax },
  {0.0, kEtrueMax },
  {0.0, kEtrueMax },
  {0.0, kEtrueMax },
  {0.0, kEtrueMax },
  {0.0, kEtrueMax },
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
   // Far detector flux
   // FHC flux
   {  0.0,  0.5},        // kNuisFHCNuMuFDFlux00
   {  0.5,  1.0},        // kNuisFHCNuMuFDFlux01
   {  1.0,  1.5},        // kNuisFHCNuMuFDFlux02
   {  1.5,  2.0},        // kNuisFHCNuMuFDFlux03
   {  2.0,  2.5},        // kNuisFHCNuMuFDFlux04
   {  2.5,  3.0},        // kNuisFHCNuMuFDFlux05
   {  3.0,  3.5},        // kNuisFHCNuMuFDFlux06
   {  3.5,  4.0},        // kNuisFHCNuMuFDFlux07
   {  4.0,  4.5},        // kNuisFHCNuMuFDFlux08
   {  4.5,  5.0},        // kNuisFHCNuMuFDFlux09
   {  5.0,  5.5},        // kNuisFHCNuMuFDFlux10
   {  5.5,  6.0},        // kNuisFHCNuMuFDFlux11
   {  6.0,  7.0},        // kNuisFHCNuMuFDFlux12
   {  7.0,  8.0},        // kNuisFHCNuMuFDFlux13
   {  8.0, 12.0},        // kNuisFHCNuMuFDFlux14
   { 12.0, 16.0},        // kNuisFHCNuMuFDFlux15
   { 16.0, 20.0},        // kNuisFHCNuMuFDFlux16
   { 20.0, 40.0},        // kNuisFHCNuMuFDFlux17
   { 40.0, kEtrueMax },  // kNuisFHCNuMuFDFlux18
   {  0.0,  0.5},        // kNuisFHCNuMuBarFDFlux00
   {  0.5,  1.0},        // kNuisFHCNuMuBarFDFlux01
   {  1.0,  1.5},        // kNuisFHCNuMuBarFDFlux02
   {  1.5,  2.0},        // kNuisFHCNuMuBarFDFlux03
   {  2.0,  2.5},        // kNuisFHCNuMuBarFDFlux04
   {  2.5,  3.0},        // kNuisFHCNuMuBarFDFlux05
   {  3.0,  3.5},        // kNuisFHCNuMuBarFDFlux06
   {  3.5,  4.0},        // kNuisFHCNuMuBarFDFlux07
   {  4.0,  4.5},        // kNuisFHCNuMuBarFDFlux08
   {  4.5,  5.0},        // kNuisFHCNuMuBarFDFlux09
   {  5.0,  5.5},        // kNuisFHCNuMuBarFDFlux10
   {  5.5,  6.0},        // kNuisFHCNuMuBarFDFlux11
   {  6.0,  7.0},        // kNuisFHCNuMuBarFDFlux12
   {  7.0,  8.0},        // kNuisFHCNuMuBarFDFlux13
   {  8.0, 12.0},        // kNuisFHCNuMuBarFDFlux14
   { 12.0, 16.0},        // kNuisFHCNuMuBarFDFlux15
   { 16.0, 20.0},        // kNuisFHCNuMuBarFDFlux16
   { 20.0, 40.0},        // kNuisFHCNuMuBarFDFlux17
   { 40.0, kEtrueMax },  // kNuisFHCNuMuBarFDFlux18
   {  0.0,  2.0},        // kNuisFHCNuEFDFlux00
   {  2.0,  4.0},        // kNuisFHCNuEFDFlux01
   {  4.0,  6.0},        // kNuisFHCNuEFDFlux02
   {  6.0,  8.0},        // kNuisFHCNuEFDFlux03
   {  8.0, 10.0},        // kNuisFHCNuEFDFlux04
   { 10.0, 20.0},        // kNuisFHCNuEFDFlux05
   { 20.0, kEtrueMax },  // kNuisFHCNuEFDFlux06
   {  0.0,  2.0},        // kNuisFHCNuEBarFDFlux00
   {  2.0,  4.0},        // kNuisFHCNuEBarFDFlux01
   {  4.0,  6.0},        // kNuisFHCNuEBarFDFlux02
   {  6.0,  8.0},        // kNuisFHCNuEBarFDFlux03
   {  8.0, 10.0},        // kNuisFHCNuEBarFDFlux04
   { 10.0, 20.0},        // kNuisFHCNuEBarFDFlux05
   { 20.0, kEtrueMax },  // kNuisFHCNuEBarFDFlux06
   // RHC flux
   {  0.0,  0.5},        // kNuisRHCNuMuFDFlux00
   {  0.5,  1.0},        // kNuisRHCNuMuFDFlux01
   {  1.0,  1.5},        // kNuisRHCNuMuFDFlux02
   {  1.5,  2.0},        // kNuisRHCNuMuFDFlux03
   {  2.0,  2.5},        // kNuisRHCNuMuFDFlux04
   {  2.5,  3.0},        // kNuisRHCNuMuFDFlux05
   {  3.0,  3.5},        // kNuisRHCNuMuFDFlux06
   {  3.5,  4.0},        // kNuisRHCNuMuFDFlux07
   {  4.0,  4.5},        // kNuisRHCNuMuFDFlux08
   {  4.5,  5.0},        // kNuisRHCNuMuFDFlux09
   {  5.0,  5.5},        // kNuisRHCNuMuFDFlux10
   {  5.5,  6.0},        // kNuisRHCNuMuFDFlux11
   {  6.0,  7.0},        // kNuisRHCNuMuFDFlux12
   {  7.0,  8.0},        // kNuisRHCNuMuFDFlux13
   {  8.0, 12.0},        // kNuisRHCNuMuFDFlux14
   { 12.0, 16.0},        // kNuisRHCNuMuFDFlux15
   { 16.0, 20.0},        // kNuisRHCNuMuFDFlux16
   { 20.0, 40.0},        // kNuisRHCNuMuFDFlux17
   { 40.0, kEtrueMax },  // kNuisRHCNuMuFDFlux18
   {  0.0,  0.5},        // kNuisRHCNuMuBarFDFlux00
   {  0.5,  1.0},        // kNuisRHCNuMuBarFDFlux01
   {  1.0,  1.5},        // kNuisRHCNuMuBarFDFlux02
   {  1.5,  2.0},        // kNuisRHCNuMuBarFDFlux03
   {  2.0,  2.5},        // kNuisRHCNuMuBarFDFlux04
   {  2.5,  3.0},        // kNuisRHCNuMuBarFDFlux05
   {  3.0,  3.5},        // kNuisRHCNuMuBarFDFlux06
   {  3.5,  4.0},        // kNuisRHCNuMuBarFDFlux07
   {  4.0,  4.5},        // kNuisRHCNuMuBarFDFlux08
   {  4.5,  5.0},        // kNuisRHCNuMuBarFDFlux09
   {  5.0,  5.5},        // kNuisRHCNuMuBarFDFlux10
   {  5.5,  6.0},        // kNuisRHCNuMuBarFDFlux11
   {  6.0,  7.0},        // kNuisRHCNuMuBarFDFlux12
   {  7.0,  8.0},        // kNuisRHCNuMuBarFDFlux13
   {  8.0, 12.0},        // kNuisRHCNuMuBarFDFlux14
   { 12.0, 16.0},        // kNuisRHCNuMuBarFDFlux15
   { 16.0, 20.0},        // kNuisRHCNuMuBarFDFlux16
   { 20.0, 40.0},        // kNuisRHCNuMuBarFDFlux17
   { 40.0, kEtrueMax },  // kNuisRHCNuMuBarFDFlux18
   {  0.0,  2.0},        // kNuisRHCNuEFDFlux00
   {  2.0,  4.0},        // kNuisRHCNuEFDFlux01
   {  4.0,  6.0},        // kNuisRHCNuEFDFlux02
   {  6.0,  8.0},        // kNuisRHCNuEFDFlux03
   {  8.0, 10.0},        // kNuisRHCNuEFDFlux04
   { 10.0, 20.0},        // kNuisRHCNuEFDFlux05
   { 20.0, kEtrueMax },  // kNuisRHCNuEFDFlux06
   {  0.0,  2.0},        // kNuisRHCNuEBarFDFlux00
   {  2.0,  4.0},        // kNuisRHCNuEBarFDFlux01
   {  4.0,  6.0},        // kNuisRHCNuEBarFDFlux02
   {  6.0,  8.0},        // kNuisRHCNuEBarFDFlux03
   {  8.0, 10.0},        // kNuisRHCNuEBarFDFlux04
   { 10.0, 20.0},        // kNuisRHCNuEBarFDFlux05
   { 20.0, kEtrueMax },  // kNuisRHCNuEBarFDFlux06
     // Cross-sections
   {  0.0 , kEtrueMax},  // kNuisIntNuCCQE1
   {  0.0 , kEtrueMax},  // kNuisIntNuCCQE2
   {  0.0 , kEtrueMax},  // kNuisIntNuCCQE3
   {  0.0 , kEtrueMax},  // kNuisIntNuBarCCQE1
   {  0.0 , kEtrueMax},  // kNuisIntNuBarCCQE2
   {  0.0 , kEtrueMax},  // kNuisIntNuBarCCQE3
   {  0.0 , kEtrueMax},  // kNuisIntNuCCMEC
   {  0.0 , kEtrueMax},  // kNuisIntNuBarCCMEC
   {  0.0 , kEtrueMax},  // kNuisIntNuCC1piz1
   {  0.0 , kEtrueMax},  // kNuisIntNuCC1piz2
   {  0.0 , kEtrueMax},  // kNuisIntNuCC1piz3
   {  0.0 , kEtrueMax},  // kNuisIntNuCC1pic1
   {  0.0 , kEtrueMax},  // kNuisIntNuCC1pic2
   {  0.0 , kEtrueMax},  // kNuisIntNuCC1pic3
   {  0.0 , kEtrueMax},  // kNuisIntNuBarCC1piz1
   {  0.0 , kEtrueMax},  // kNuisIntNuBarCC1piz2
   {  0.0 , kEtrueMax},  // kNuisIntNuBarCC1piz3
   {  0.0 , kEtrueMax},  // kNuisIntNuBarCC1pic1
   {  0.0 , kEtrueMax},  // kNuisIntNuBarCC1pic2
   {  0.0 , kEtrueMax},  // kNuisIntNuBarCC1pic3
   {  0.0 , kEtrueMax},  // kNuisIntNuCC2Pi
   {  0.0 , kEtrueMax},  // kNuisIntNuBarCC2Pi
   {  0.0 , 7.5      },  // kNuisIntNuDIS1
   {  7.5 , 15.      },  // kNuisIntNuDIS2
   {  15. , kEtrueMax},  // kNuisIntNuDIS3
   {  0.0 , 7.5      },  // kNuisIntNuBarDIS1
   {  7.5 , 15.      },  // kNuisIntNuBarDIS2
   {  15. , kEtrueMax},  // kNuisIntNuBarDIS3
   {  0.0 , kEtrueMax},  // kNuisIntNormNuCoherent
   {  0.0 , kEtrueMax},  // kNuisIntNormNuBarCoherent
   {  0.0 , kEtrueMax},  // kNuisIntNuNormNC
   {  0.0 , kEtrueMax},  // kNuisIntNuBarNormNC
   {  0.0 , kEtrueMax},  // kNuisIntNormNuMuToNuE
   {  0.0 , kEtrueMax},  // kNuisIntPiMeanFreePath
   {  0.0 , kEtrueMax},  // kNuisIntNucMeanFreePath
   {  0.0 , kEtrueMax},  // kNuisIntFracPiChargeExchange
   {  0.0 , kEtrueMax},  // kNuisIntFracPiInelastic
   {  0.0 , kEtrueMax},  // kNuisIntFracPiAbsorb
   {  0.0 , kEtrueMax},  // kNuisIntFracPiProduction
   {  0.0 , kEtrueMax},  // kNuisIntFracNucChargeExchange
   {  0.0 , kEtrueMax},  // kNuisIntFracNucInelastic
   {  0.0 , kEtrueMax},  // kNuisIntFracNucAbsorb
   {  0.0 , kEtrueMax},  // kNuisIntFracNucProduction
   // Detector systematics
   {  0.0, kEtrueMax},   // kNuisEffNuMuCC0pi1trk
   {  0.0, kEtrueMax},   // kNuisEffNuMuCC0pi2trk
   {  0.0, kEtrueMax},   // kNuisEffNuMuCC1piC
   {  0.0, kEtrueMax},   // kNuisEffNuMuCC1pi0
   {  0.0, kEtrueMax},   // kNuisEffNuMuCC1piC1pi0
   {  0.0, kEtrueMax},   // kNuisEffNuMuCCoth
   {  0.0, kEtrueMax},   // kNuisEffNuECC
   {  0.0, kEtrueMax},   // kNuisEffNuMuCCWS
   {  0.0, kEtrueMax},   // kNuisEffNC
  // Far detector systematics
   {  0.0, kEtrueMax},   // kNuisEffFDNuMuCCHigh
   {  0.0, kEtrueMax},   // kNuisEffFDNuMuCCLow
   {  0.0, kEtrueMax},   // kNuisEffFDNuECCHigh
   {  0.0, kEtrueMax}   // kNuisEffFDNuECCLow
};

// Which is the true Q2 range?
static const double kFitParamQ2trueRange[kNFitParams][2] =
{
   // Q2 min, Q2 max
  //oscillation parameters
  { 0.0, kQ2trueMax },
  { 0.0, kQ2trueMax },
  { 0.0, kQ2trueMax },
  { 0.0, kQ2trueMax },
  { 0.0, kQ2trueMax },
  { 0.0, kQ2trueMax },
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
   //Far detector flux
   // FHC flux
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux00
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux01
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux02
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux03
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux04
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux05
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux06
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux07
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux08
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux09
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux10
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux11
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux12
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux13
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux14
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux15
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux16
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux17
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuFDFlux18
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux00
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux01
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux02
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux03
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux04
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux05
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux06
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux07
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux08
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux09
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux10
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux11
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux12
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux13
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux14
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux15
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux16
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux17
   { 0.0, kQ2trueMax }, // kNuisFHCNuMuBarFDFlux18
   { 0.0, kQ2trueMax }, // kNuisFHCNuEFDFlux00
   { 0.0, kQ2trueMax }, // kNuisFHCNuEFDFlux01
   { 0.0, kQ2trueMax }, // kNuisFHCNuEFDFlux02
   { 0.0, kQ2trueMax }, // kNuisFHCNuEFDFlux03
   { 0.0, kQ2trueMax }, // kNuisFHCNuEFDFlux04
   { 0.0, kQ2trueMax }, // kNuisFHCNuEFDFlux05
   { 0.0, kQ2trueMax }, // kNuisFHCNuEFDFlux06
   { 0.0, kQ2trueMax }, // kNuisFHCNuEBarFDFlux00
   { 0.0, kQ2trueMax }, // kNuisFHCNuEBarFDFlux01
   { 0.0, kQ2trueMax }, // kNuisFHCNuEBarFDFlux02
   { 0.0, kQ2trueMax }, // kNuisFHCNuEBarFDFlux03
   { 0.0, kQ2trueMax }, // kNuisFHCNuEBarFDFlux04
   { 0.0, kQ2trueMax }, // kNuisFHCNuEBarFDFlux05
   { 0.0, kQ2trueMax }, // kNuisFHCNuEBarFDFlux06
   // RHC flux
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux00
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux01
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux02
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux03
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux04
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux05
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux06
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux07
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux08
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux09
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux10
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux11
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux12
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux13
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux14
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux15
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux16
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux17
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuFDFlux18
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux00
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux01
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux02
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux03
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux04
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux05
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux06
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux07
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux08
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux09
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux10
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux11
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux12
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux13
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux14
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux15
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux16
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux17
   { 0.0, kQ2trueMax },  // kNuisRHCNuMuBarFDFlux18
   { 0.0, kQ2trueMax },  // kNuisRHCNuEFDFlux00
   { 0.0, kQ2trueMax },  // kNuisRHCNuEFDFlux01
   { 0.0, kQ2trueMax },  // kNuisRHCNuEFDFlux02
   { 0.0, kQ2trueMax },  // kNuisRHCNuEFDFlux03
   { 0.0, kQ2trueMax },  // kNuisRHCNuEFDFlux04
   { 0.0, kQ2trueMax },  // kNuisRHCNuEFDFlux05
   { 0.0, kQ2trueMax },  // kNuisRHCNuEFDFlux06
   { 0.0, kQ2trueMax },  // kNuisRHCNuEBarFDFlux00
   { 0.0, kQ2trueMax },  // kNuisRHCNuEBarFDFlux01
   { 0.0, kQ2trueMax },  // kNuisRHCNuEBarFDFlux02
   { 0.0, kQ2trueMax },  // kNuisRHCNuEBarFDFlux03
   { 0.0, kQ2trueMax },  // kNuisRHCNuEBarFDFlux04
   { 0.0, kQ2trueMax },  // kNuisRHCNuEBarFDFlux05
   { 0.0, kQ2trueMax },  // kNuisRHCNuEBarFDFlux06
     // Cross-sections
   { kQ2trueBinEdgesCCQE[0] , kQ2trueBinEdgesCCQE[1] },  // kNuisIntNuCCQE1
   { kQ2trueBinEdgesCCQE[1] , kQ2trueBinEdgesCCQE[2] },  // kNuisIntNuCCQE2
   { kQ2trueBinEdgesCCQE[2] , kQ2trueBinEdgesCCQE[3] },  // kNuisIntNuCCQE3
   { kQ2trueBinEdgesCCQE[0] , kQ2trueBinEdgesCCQE[1] },  // kNuisIntNuBarCCQE1
   { kQ2trueBinEdgesCCQE[1] , kQ2trueBinEdgesCCQE[2] },  // kNuisIntNuBarCCQE2
   { kQ2trueBinEdgesCCQE[2] , kQ2trueBinEdgesCCQE[3] },  // kNuisIntNuBarCCQE3
   {  0.0 , kQ2trueMax},  // kNuisIntNuCCMEC
   {  0.0 , kQ2trueMax},  // kNuisIntNuBarCCMEC
   { kQ2trueBinEdgesCC1pi0[0] , kQ2trueBinEdgesCC1pi0[1] },  // kNuisIntNuCC1piz1
   { kQ2trueBinEdgesCC1pi0[1] , kQ2trueBinEdgesCC1pi0[2] },  // kNuisIntNuCC1piz2
   { kQ2trueBinEdgesCC1pi0[2] , kQ2trueBinEdgesCC1pi0[3] },  // kNuisIntNuCC1piz3
   { kQ2trueBinEdgesCC1piC[0] , kQ2trueBinEdgesCC1piC[1] },  // kNuisIntNuCC1pic1
   { kQ2trueBinEdgesCC1piC[1] , kQ2trueBinEdgesCC1piC[2] },  // kNuisIntNuCC1pic2
   { kQ2trueBinEdgesCC1piC[2] , kQ2trueBinEdgesCC1piC[3] },  // kNuisIntNuCC1pic3
   { kQ2trueBinEdgesCC1pi0[0] , kQ2trueBinEdgesCC1pi0[1] },  // kNuisIntNuBarCC1piz1
   { kQ2trueBinEdgesCC1pi0[1] , kQ2trueBinEdgesCC1pi0[2] },  // kNuisIntNuBarCC1piz2
   { kQ2trueBinEdgesCC1pi0[2] , kQ2trueBinEdgesCC1pi0[3] },  // kNuisIntNuBarCC1piz3
   { kQ2trueBinEdgesCC1piC[0] , kQ2trueBinEdgesCC1piC[1] },  // kNuisIntNuBarCC1pic1
   { kQ2trueBinEdgesCC1piC[1] , kQ2trueBinEdgesCC1piC[2] },  // kNuisIntNuBarCC1pic2
   { kQ2trueBinEdgesCC1piC[2] , kQ2trueBinEdgesCC1piC[3] },  // kNuisIntNuBarCC1pic3
   {  0.0 , kQ2trueMax},  // kNuisIntNuCC2Pi
   {  0.0 , kQ2trueMax},  // kNuisIntNuBarCC2Pi
   {  0.0 , kQ2trueMax},  // kNuisIntNuDIS1
   {  0.0 , kQ2trueMax},  // kNuisIntNuDIS2
   {  0.0 , kQ2trueMax},  // kNuisIntNuDIS3
   {  0.0 , kQ2trueMax},  // kNuisIntNuBarDIS1
   {  0.0 , kQ2trueMax},  // kNuisIntNuBarDIS2
   {  0.0 , kQ2trueMax},  // kNuisIntNuBarDIS3
   {  0.0 , kQ2trueMax},  // kNuisIntNormNuCoherent
   {  0.0 , kQ2trueMax},  // kNuisIntNormNuBarCoherent
   {  0.0 , kQ2trueMax},  // kNuisIntNuNormNC
   {  0.0 , kQ2trueMax},  // kNuisIntNuBarNormNC
   {  0.0 , kQ2trueMax},  // kNuisIntNormNuMuToNuE
   {  0.0 , kQ2trueMax},  // kNuisIntPiMeanFreePath
   {  0.0 , kQ2trueMax},  // kNuisIntNucMeanFreePath
   {  0.0 , kQ2trueMax},  // kNuisIntFracPiChargeExchange
   {  0.0 , kQ2trueMax},  // kNuisIntFracPiInelastic
   {  0.0 , kQ2trueMax},  // kNuisIntFracPiAbsorb
   {  0.0 , kQ2trueMax},  // kNuisIntFracPiProduction
   {  0.0 , kQ2trueMax},  // kNuisIntFracNucChargeExchange
   {  0.0 , kQ2trueMax},  // kNuisIntFracNucInelastic
   {  0.0 , kQ2trueMax},  // kNuisIntFracNucAbsorb
   {  0.0 , kQ2trueMax},  // kNuisIntFracNucProduction
   // Detector systematics
   {  0.0, kQ2trueMax},   // kNuisEffNuMuCC0pi1trk
   {  0.0, kQ2trueMax},   // kNuisEffNuMuCC0pi2trk
   {  0.0, kQ2trueMax},   // kNuisEffNuMuCC1piC
   {  0.0, kQ2trueMax},   // kNuisEffNuMuCC1pi0
   {  0.0, kQ2trueMax},   // kNuisEffNuMuCC1piC1pi0
   {  0.0, kQ2trueMax},   // kNuisEffNuMuCCoth
   {  0.0, kQ2trueMax},   // kNuisEffNuECC
   {  0.0, kQ2trueMax},   // kNuisEffNuMuCCWS
   {  0.0, kQ2trueMax},    // kNuisEffNC
  // Far detector systematics
   {  0.0, kQ2trueMax},   // kNuisEffFDNuMuCCHigh
   {  0.0, kQ2trueMax},   // kNuisEffFDNuMuCCLow
   {  0.0, kQ2trueMax},   // kNuisEffFDNuECCHigh
   {  0.0, kQ2trueMax}    // kNuisEffFDNuECCLow
};

//
// ...........................................................................
// The following arrays help classify physics parameters in groups
// ...........................................................................
//

static const FitParamGroup_t kFitParamGroup[kNFitParams] =
{
  //oscillation parameters
  kpgOscillations,
  kpgOscillations,
  kpgOscillations,
  kpgOscillations,
  kpgOscillations,
  kpgOscillations,
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
   // Far detector flux
   // FHC flux
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux00
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux01
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux02
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux03
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux04
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux05
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux06
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux07
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux08
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux09
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux10
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux11
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux12
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux13
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux14
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux15
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux16
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux17
   kpgFHCNuMuFlux,     // kNuisFHCNuMuFDFlux18
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux00
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux01
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux02
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux03
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux04
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux05
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux06
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux07
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux08
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux09
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux10
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux11
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux12
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux13
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux14
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux15
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux16
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux17
   kpgFHCNuMuBarFlux,  // kNuisFHCNuMuBarFDFlux18
   kpgFHCNuEFlux,      // kNuisFHCNuEFDFlux00
   kpgFHCNuEFlux,      // kNuisFHCNuEFDFlux01
   kpgFHCNuEFlux,      // kNuisFHCNuEFDFlux02
   kpgFHCNuEFlux,      // kNuisFHCNuEFDFlux03
   kpgFHCNuEFlux,      // kNuisFHCNuEFDFlux04
   kpgFHCNuEFlux,      // kNuisFHCNuEFDFlux05
   kpgFHCNuEFlux,      // kNuisFHCNuEFDFlux06
   kpgFHCNuEBarFlux,   // kNuisFHCNuEBarFDFlux00
   kpgFHCNuEBarFlux,   // kNuisFHCNuEBarFDFlux01
   kpgFHCNuEBarFlux,   // kNuisFHCNuEBarFDFlux02
   kpgFHCNuEBarFlux,   // kNuisFHCNuEBarFDFlux03
   kpgFHCNuEBarFlux,   // kNuisFHCNuEBarFDFlux04
   kpgFHCNuEBarFlux,   // kNuisFHCNuEBarFDFlux05
   kpgFHCNuEBarFlux,   // kNuisFHCNuEBarFDFlux06
   // RHC flux
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux00
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux01
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux02
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux03
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux04
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux05
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux06
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux07
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux08
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux09
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux10
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux11
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux12
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux13
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux14
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux15
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux16
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux17
   kpgRHCNuMuFlux,     // kNuisRHCNuMuFDFlux18
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux00
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux01
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux02
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux03
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux04
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux05
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux06
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux07
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux08
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux09
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux10
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux11
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux12
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux13
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux14
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux15
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux16
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux17
   kpgRHCNuMuBarFlux,  // kNuisRHCNuMuBarFDFlux18
   kpgRHCNuEFlux,      // kNuisRHCNuEFDFlux00
   kpgRHCNuEFlux,      // kNuisRHCNuEFDFlux01
   kpgRHCNuEFlux,      // kNuisRHCNuEFDFlux02
   kpgRHCNuEFlux,      // kNuisRHCNuEFDFlux03
   kpgRHCNuEFlux,      // kNuisRHCNuEFDFlux04
   kpgRHCNuEFlux,      // kNuisRHCNuEFDFlux05
   kpgRHCNuEFlux,      // kNuisRHCNuEFDFlux06
   kpgRHCNuEBarFlux,   // kNuisRHCNuEBarFDFlux00
   kpgRHCNuEBarFlux,   // kNuisRHCNuEBarFDFlux01
   kpgRHCNuEBarFlux,   // kNuisRHCNuEBarFDFlux02
   kpgRHCNuEBarFlux,   // kNuisRHCNuEBarFDFlux03
   kpgRHCNuEBarFlux,   // kNuisRHCNuEBarFDFlux04
   kpgRHCNuEBarFlux,   // kNuisRHCNuEBarFDFlux05
   kpgRHCNuEBarFlux,   // kNuisRHCNuEBarFDFlux06
   // Cross-sections
   kpgXSec,            // kNuisIntNuCCQE1
   kpgXSec,            // kNuisIntNuCCQE2
   kpgXSec,            // kNuisIntNuCCQE3
   kpgXSec,            // kNuisIntNuBarCCQE1
   kpgXSec,            // kNuisIntNuBarCCQE2
   kpgXSec,            // kNuisIntNuBarCCQE3
   kpgXSec,            // kNuisIntNuCCMEC
   kpgXSec,            // kNuisIntNuBarCCMEC
   kpgXSec,            // kNuisIntNuCC1piz1
   kpgXSec,            // kNuisIntNuCC1piz2
   kpgXSec,            // kNuisIntNuCC1piz3
   kpgXSec,            // kNuisIntNuCC1pic1
   kpgXSec,            // kNuisIntNuCC1pic2
   kpgXSec,            // kNuisIntNuCC1pic3
   kpgXSec,            // kNuisIntNuBarCC1piz1
   kpgXSec,            // kNuisIntNuBarCC1piz2
   kpgXSec,            // kNuisIntNuBarCC1piz3
   kpgXSec,            // kNuisIntNuBarCC1pic1
   kpgXSec,            // kNuisIntNuBarCC1pic2
   kpgXSec,            // kNuisIntNuBarCC1pic3
   kpgXSec,            // kNuisIntNuCC2Pi
   kpgXSec,            // kNuisIntNuBarCC2Pi
   kpgXSec,            // kNuisIntNuDIS1
   kpgXSec,            // kNuisIntNuDIS2
   kpgXSec,            // kNuisIntNuDIS3
   kpgXSec,            // kNuisIntNuBarDIS1
   kpgXSec,            // kNuisIntNuBarDIS2
   kpgXSec,            // kNuisIntNuBarDIS3
   kpgXSec,            // kNuisIntNormNuCoherent
   kpgXSec,            // kNuisIntNormNuBarCoherent
   kpgXSec,            // kNuisIntNuNormNC
   kpgXSec,            // kNuisIntNuBarNormNC
   kpgXSec,            // kNuisIntNormNuMuToNuE
   kpgXSec,            // kNuisIntPiMeanFreePath
   kpgXSec,            // kNuisIntNucMeanFreePath
   kpgXSec,            // kNuisIntFracPiChargeExchange
   kpgXSec,            // kNuisIntFracPiInelastic
   kpgXSec,            // kNuisIntFracPiAbsorb
   kpgXSec,            // kNuisIntFracPiProduction
   kpgXSec,            // kNuisIntFracNucChargeExchange
   kpgXSec,            // kNuisIntFracNucInelastic
   kpgXSec,            // kNuisIntFracNucAbsorb
   kpgXSec,            // kNuisIntFracNucProduction
   // Detector systematics
   kpgDetector,        // kNuisEffNuMuCC0pi1trk
   kpgDetector,        // kNuisEffNuMuCC0pi2trk
   kpgDetector,        // kNuisEffNuMuCC1piC
   kpgDetector,        // kNuisEffNuMuCC1pi0
   kpgDetector,        // kNuisEffNuMuCC1piC1pi0
   kpgDetector,        // kNuisEffNuMuCCoth
   kpgDetector,        // kNuisEffNuECC
   kpgDetector,        // kNuisEffNuMuCCWS
   kpgDetector,        // kNuisEffNC
  // Far detector systematics
   kpgDetector,        //  kNuisEffFDNuMuCCHigh
   kpgDetector,        //  kNuisEffFDNuMuCCLow
   kpgDetector,        //  kNuisEffFDNuECCHigh
   kpgDetector        //  kNuisEffFDNuECCLow
};

// Is this a neutrino flux related parameter?
//
static const bool kFitIsNuFluxRelated[kNFitParams] =
{
  //oscillation parameters
  false,
  false,
  false,
  false,
  false,
  false,
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
  // FHC flux
   true,  // kNuisFHCNuMuFDFlux00
   true,  // kNuisFHCNuMuFDFlux01
   true,  // kNuisFHCNuMuFDFlux02
   true,  // kNuisFHCNuMuFDFlux03
   true,  // kNuisFHCNuMuFDFlux04
   true,  // kNuisFHCNuMuFDFlux05
   true,  // kNuisFHCNuMuFDFlux06
   true,  // kNuisFHCNuMuFDFlux07
   true,  // kNuisFHCNuMuFDFlux08
   true,  // kNuisFHCNuMuFDFlux09
   true,  // kNuisFHCNuMuFDFlux10
   true,  // kNuisFHCNuMuFDFlux11
   true,  // kNuisFHCNuMuFDFlux12
   true,  // kNuisFHCNuMuFDFlux13
   true,  // kNuisFHCNuMuFDFlux14
   true,  // kNuisFHCNuMuFDFlux15
   true,  // kNuisFHCNuMuFDFlux16
   true,  // kNuisFHCNuMuFDFlux17
   true,  // kNuisFHCNuMuFDFlux18
   true,  // kNuisFHCNuMuBarFDFlux00
   true,  // kNuisFHCNuMuBarFDFlux01
   true,  // kNuisFHCNuMuBarFDFlux02
   true,  // kNuisFHCNuMuBarFDFlux03
   true,  // kNuisFHCNuMuBarFDFlux04
   true,  // kNuisFHCNuMuBarFDFlux05
   true,  // kNuisFHCNuMuBarFDFlux06
   true,  // kNuisFHCNuMuBarFDFlux07
   true,  // kNuisFHCNuMuBarFDFlux08
   true,  // kNuisFHCNuMuBarFDFlux09
   true,  // kNuisFHCNuMuBarFDFlux10
   true,  // kNuisFHCNuMuBarFDFlux11
   true,  // kNuisFHCNuMuBarFDFlux12
   true,  // kNuisFHCNuMuBarFDFlux13
   true,  // kNuisFHCNuMuBarFDFlux14
   true,  // kNuisFHCNuMuBarFDFlux15
   true,  // kNuisFHCNuMuBarFDFlux16
   true,  // kNuisFHCNuMuBarFDFlux17
   true,  // kNuisFHCNuMuBarFDFlux18
   true,  // kNuisFHCNuEFDFlux00
   true,  // kNuisFHCNuEFDFlux01
   true,  // kNuisFHCNuEFDFlux02
   true,  // kNuisFHCNuEFDFlux03
   true,  // kNuisFHCNuEFDFlux04
   true,  // kNuisFHCNuEFDFlux05
   true,  // kNuisFHCNuEFDFlux06
   true,  // kNuisFHCNuEBarFDFlux00
   true,  // kNuisFHCNuEBarFDFlux01
   true,  // kNuisFHCNuEBarFDFlux02
   true,  // kNuisFHCNuEBarFDFlux03
   true,  // kNuisFHCNuEBarFDFlux04
   true,  // kNuisFHCNuEBarFDFlux05
   true,  // kNuisFHCNuEBarFDFlux06
   // RHC flux
   true,  // kNuisRHCNuMuFDFlux00
   true,  // kNuisRHCNuMuFDFlux01
   true,  // kNuisRHCNuMuFDFlux02
   true,  // kNuisRHCNuMuFDFlux03
   true,  // kNuisRHCNuMuFDFlux04
   true,  // kNuisRHCNuMuFDFlux05
   true,  // kNuisRHCNuMuFDFlux06
   true,  // kNuisRHCNuMuFDFlux07
   true,  // kNuisRHCNuMuFDFlux08
   true,  // kNuisRHCNuMuFDFlux09
   true,  // kNuisRHCNuMuFDFlux10
   true,  // kNuisRHCNuMuFDFlux11
   true,  // kNuisRHCNuMuFDFlux12
   true,  // kNuisRHCNuMuFDFlux13
   true,  // kNuisRHCNuMuFDFlux14
   true,  // kNuisRHCNuMuFDFlux15
   true,  // kNuisRHCNuMuFDFlux16
   true,  // kNuisRHCNuMuFDFlux17
   true,  // kNuisRHCNuMuFDFlux18
   true,  // kNuisRHCNuMuBarFDFlux00
   true,  // kNuisRHCNuMuBarFDFlux01
   true,  // kNuisRHCNuMuBarFDFlux02
   true,  // kNuisRHCNuMuBarFDFlux03
   true,  // kNuisRHCNuMuBarFDFlux04
   true,  // kNuisRHCNuMuBarFDFlux05
   true,  // kNuisRHCNuMuBarFDFlux06
   true,  // kNuisRHCNuMuBarFDFlux07
   true,  // kNuisRHCNuMuBarFDFlux08
   true,  // kNuisRHCNuMuBarFDFlux09
   true,  // kNuisRHCNuMuBarFDFlux10
   true,  // kNuisRHCNuMuBarFDFlux11
   true,  // kNuisRHCNuMuBarFDFlux12
   true,  // kNuisRHCNuMuBarFDFlux13
   true,  // kNuisRHCNuMuBarFDFlux14
   true,  // kNuisRHCNuMuBarFDFlux15
   true,  // kNuisRHCNuMuBarFDFlux16
   true,  // kNuisRHCNuMuBarFDFlux17
   true,  // kNuisRHCNuMuBarFDFlux18
   true,  // kNuisRHCNuEFDFlux00
   true,  // kNuisRHCNuEFDFlux01
   true,  // kNuisRHCNuEFDFlux02
   true,  // kNuisRHCNuEFDFlux03
   true,  // kNuisRHCNuEFDFlux04
   true,  // kNuisRHCNuEFDFlux05
   true,  // kNuisRHCNuEFDFlux06
   true,  // kNuisRHCNuEBarFDFlux00
   true,  // kNuisRHCNuEBarFDFlux01
   true,  // kNuisRHCNuEBarFDFlux02
   true,  // kNuisRHCNuEBarFDFlux03
   true,  // kNuisRHCNuEBarFDFlux04
   true,  // kNuisRHCNuEBarFDFlux05
   true,  // kNuisRHCNuEBarFDFlux06
  // Cross-sections
   false, // kNuisIntNuCCQE1
   false, // kNuisIntNuCCQE2
   false, // kNuisIntNuCCQE3
   false, // kNuisIntNuBarCCQE1
   false, // kNuisIntNuBarCCQE2
   false, // kNuisIntNuBarCCQE3
   false, // kNuisIntNuCCMEC
   false, // kNuisIntNuBarCCMEC
   false, // kNuisIntNuCC1piz1
   false, // kNuisIntNuCC1piz2
   false, // kNuisIntNuCC1piz3
   false, // kNuisIntNuCC1pic1
   false, // kNuisIntNuCC1pic2
   false, // kNuisIntNuCC1pic3
   false, // kNuisIntNuBarCC1piz1
   false, // kNuisIntNuBarCC1piz2
   false, // kNuisIntNuBarCC1piz3
   false, // kNuisIntNuBarCC1pic1
   false, // kNuisIntNuBarCC1pic2
   false, // kNuisIntNuBarCC1pic3
   false, // kNuisIntNuCC2Pi
   false, // kNuisIntNuBarCC2Pi
   false, // kNuisIntNuDIS1
   false, // kNuisIntNuDIS2
   false, // kNuisIntNuDIS3
   false, // kNuisIntNuBarDIS1
   false, // kNuisIntNuBarDIS2
   false, // kNuisIntNuBarDIS3
   false, // kNuisIntNormNuCoherent
   false, // kNuisIntNormNuBarCoherent
   false, // kNuisIntNuNormNC
   false, // kNuisIntNuBarNormNC
   false, // kNuisIntNormNuMuToNuE
   false, // kNuisIntPiMeanFreePath
   false, // kNuisIntNucMeanFreePath
   false, // kNuisIntFracPiChargeExchange
   false, // kNuisIntFracPiInelastic
   false, // kNuisIntFracPiAbsorb
   false, // kNuisIntFracPiProduction
   false, // kNuisIntFracNucChargeExchange
   false, // kNuisIntFracNucInelastic
   false, // kNuisIntFracNucAbsorb
   false, // kNuisIntFracNucProduction
   // Detector systematics
   false, // kNuisEffNuMuCC0pi1trk
   false, // kNuisEffNuMuCC0pi2trk
   false, // kNuisEffNuMuCC1piC
   false, // kNuisEffNuMuCC1pi0
   false, // kNuisEffNuMuCC1piC1pi0
   false, // kNuisEffNuMuCCoth
   false, // kNuisEffNuECC
   false, // kNuisEffNuMuCCWS
   false, // kNuisEffNC
  // far detector systematics
   false, //kNuisEffFDNuMuCCHigh  
   false, //kNuisEffFDNuMuCCLow  
   false, //kNuisEffFDNuECCHigh  
   false  //kNuisEffFDNuECCLow  
};

// Is this a neutrino flux related parameter?
//
static const bool kFitIsNDNuFluxRelated[kNFitParams] =
{
  //oscillation parameters
  false,
  false,
  false,
  false,
  false,
  false,
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
  // FHC flux
   false,  // kNuisFHCNuMuFDFlux00
   false,  // kNuisFHCNuMuFDFlux01
   false,  // kNuisFHCNuMuFDFlux02
   false,  // kNuisFHCNuMuFDFlux03
   false,  // kNuisFHCNuMuFDFlux04
   false,  // kNuisFHCNuMuFDFlux05
   false,  // kNuisFHCNuMuFDFlux06
   false,  // kNuisFHCNuMuFDFlux07
   false,  // kNuisFHCNuMuFDFlux08
   false,  // kNuisFHCNuMuFDFlux09
   false,  // kNuisFHCNuMuFDFlux10
   false,  // kNuisFHCNuMuFDFlux11
   false,  // kNuisFHCNuMuFDFlux12
   false,  // kNuisFHCNuMuFDFlux13
   false,  // kNuisFHCNuMuFDFlux14
   false,  // kNuisFHCNuMuFDFlux15
   false,  // kNuisFHCNuMuFDFlux16
   false,  // kNuisFHCNuMuFDFlux17
   false,  // kNuisFHCNuMuFDFlux18
   false,  // kNuisFHCNuMuBarFDFlux00
   false,  // kNuisFHCNuMuBarFDFlux01
   false,  // kNuisFHCNuMuBarFDFlux02
   false,  // kNuisFHCNuMuBarFDFlux03
   false,  // kNuisFHCNuMuBarFDFlux04
   false,  // kNuisFHCNuMuBarFDFlux05
   false,  // kNuisFHCNuMuBarFDFlux06
   false,  // kNuisFHCNuMuBarFDFlux07
   false,  // kNuisFHCNuMuBarFDFlux08
   false,  // kNuisFHCNuMuBarFDFlux09
   false,  // kNuisFHCNuMuBarFDFlux10
   false,  // kNuisFHCNuMuBarFDFlux11
   false,  // kNuisFHCNuMuBarFDFlux12
   false,  // kNuisFHCNuMuBarFDFlux13
   false,  // kNuisFHCNuMuBarFDFlux14
   false,  // kNuisFHCNuMuBarFDFlux15
   false,  // kNuisFHCNuMuBarFDFlux16
   false,  // kNuisFHCNuMuBarFDFlux17
   false,  // kNuisFHCNuMuBarFDFlux18
   false,  // kNuisFHCNuEFDFlux00
   false,  // kNuisFHCNuEFDFlux01
   false,  // kNuisFHCNuEFDFlux02
   false,  // kNuisFHCNuEFDFlux03
   false,  // kNuisFHCNuEFDFlux04
   false,  // kNuisFHCNuEFDFlux05
   false,  // kNuisFHCNuEFDFlux06
   false,  // kNuisFHCNuEBarFDFlux00
   false,  // kNuisFHCNuEBarFDFlux01
   false,  // kNuisFHCNuEBarFDFlux02
   false,  // kNuisFHCNuEBarFDFlux03
   false,  // kNuisFHCNuEBarFDFlux04
   false,  // kNuisFHCNuEBarFDFlux05
   false,  // kNuisFHCNuEBarFDFlux06
   // RHC flux
   false,  // kNuisRHCNuMuFDFlux00
   false,  // kNuisRHCNuMuFDFlux01
   false,  // kNuisRHCNuMuFDFlux02
   false,  // kNuisRHCNuMuFDFlux03
   false,  // kNuisRHCNuMuFDFlux04
   false,  // kNuisRHCNuMuFDFlux05
   false,  // kNuisRHCNuMuFDFlux06
   false,  // kNuisRHCNuMuFDFlux07
   false,  // kNuisRHCNuMuFDFlux08
   false,  // kNuisRHCNuMuFDFlux09
   false,  // kNuisRHCNuMuFDFlux10
   false,  // kNuisRHCNuMuFDFlux11
   false,  // kNuisRHCNuMuFDFlux12
   false,  // kNuisRHCNuMuFDFlux13
   false,  // kNuisRHCNuMuFDFlux14
   false,  // kNuisRHCNuMuFDFlux15
   false,  // kNuisRHCNuMuFDFlux16
   false,  // kNuisRHCNuMuFDFlux17
   false,  // kNuisRHCNuMuFDFlux18
   false,  // kNuisRHCNuMuBarFDFlux00
   false,  // kNuisRHCNuMuBarFDFlux01
   false,  // kNuisRHCNuMuBarFDFlux02
   false,  // kNuisRHCNuMuBarFDFlux03
   false,  // kNuisRHCNuMuBarFDFlux04
   false,  // kNuisRHCNuMuBarFDFlux05
   false,  // kNuisRHCNuMuBarFDFlux06
   false,  // kNuisRHCNuMuBarFDFlux07
   false,  // kNuisRHCNuMuBarFDFlux08
   false,  // kNuisRHCNuMuBarFDFlux09
   false,  // kNuisRHCNuMuBarFDFlux10
   false,  // kNuisRHCNuMuBarFDFlux11
   false,  // kNuisRHCNuMuBarFDFlux12
   false,  // kNuisRHCNuMuBarFDFlux13
   false,  // kNuisRHCNuMuBarFDFlux14
   false,  // kNuisRHCNuMuBarFDFlux15
   false,  // kNuisRHCNuMuBarFDFlux16
   false,  // kNuisRHCNuMuBarFDFlux17
   false,  // kNuisRHCNuMuBarFDFlux18
   false,  // kNuisRHCNuEFDFlux00
   false,  // kNuisRHCNuEFDFlux01
   false,  // kNuisRHCNuEFDFlux02
   false,  // kNuisRHCNuEFDFlux03
   false,  // kNuisRHCNuEFDFlux04
   false,  // kNuisRHCNuEFDFlux05
   false,  // kNuisRHCNuEFDFlux06
   false,  // kNuisRHCNuEBarFDFlux00
   false,  // kNuisRHCNuEBarFDFlux01
   false,  // kNuisRHCNuEBarFDFlux02
   false,  // kNuisRHCNuEBarFDFlux03
   false,  // kNuisRHCNuEBarFDFlux04
   false,  // kNuisRHCNuEBarFDFlux05
   false,  // kNuisRHCNuEBarFDFlux06
  // Cross-sections
   false, // kNuisIntNuCCQE1
   false, // kNuisIntNuCCQE2
   false, // kNuisIntNuCCQE3
   false, // kNuisIntNuBarCCQE1
   false, // kNuisIntNuBarCCQE2
   false, // kNuisIntNuBarCCQE3
   false, // kNuisIntNuCCMEC
   false, // kNuisIntNuBarCCMEC
   false, // kNuisIntNuCC1piz1
   false, // kNuisIntNuCC1piz2
   false, // kNuisIntNuCC1piz3
   false, // kNuisIntNuCC1pic1
   false, // kNuisIntNuCC1pic2
   false, // kNuisIntNuCC1pic3
   false, // kNuisIntNuBarCC1piz1
   false, // kNuisIntNuBarCC1piz2
   false, // kNuisIntNuBarCC1piz3
   false, // kNuisIntNuBarCC1pic1
   false, // kNuisIntNuBarCC1pic2
   false, // kNuisIntNuBarCC1pic3
   false, // kNuisIntNuCC2Pi
   false, // kNuisIntNuBarCC2Pi
   false, // kNuisIntNuDIS1
   false, // kNuisIntNuDIS2
   false, // kNuisIntNuDIS3
   false, // kNuisIntNuBarDIS1
   false, // kNuisIntNuBarDIS2
   false, // kNuisIntNuBarDIS3
   false, // kNuisIntNormNuCoherent
   false, // kNuisIntNormNuBarCoherent
   false, // kNuisIntNuNormNC
   false, // kNuisIntNuBarNormNC
   false, // kNuisIntNormNuMuToNuE
   false, // kNuisIntPiMeanFreePath
   false, // kNuisIntNucMeanFreePath
   false, // kNuisIntFracPiChargeExchange
   false, // kNuisIntFracPiInelastic
   false, // kNuisIntFracPiAbsorb
   false, // kNuisIntFracPiProduction
   false, // kNuisIntFracNucChargeExchange
   false, // kNuisIntFracNucInelastic
   false, // kNuisIntFracNucAbsorb
   false, // kNuisIntFracNucProduction
   // Detector systematics
   false, // kNuisEffNuMuCC0pi1trk
   false, // kNuisEffNuMuCC0pi2trk
   false, // kNuisEffNuMuCC1piC
   false, // kNuisEffNuMuCC1pi0
   false, // kNuisEffNuMuCC1piC1pi0
   false, // kNuisEffNuMuCCoth
   false, // kNuisEffNuECC
   false, // kNuisEffNuMuCCWS
   false, // kNuisEffNC
  // far detector systematics
   false, //kNuisEffFDNuMuCCHigh  
   false, //kNuisEffFDNuMuCCLow
   false, //kNuisEffFDNuECCHigh  
   false //kNuisEffFDNuECCLow
};

// Is this a neutrino flux related parameter?
//
static const bool kFitIsFDNuFluxRelated[kNFitParams] =
{
  //oscillation parameters
  false,
  false,
  false,
  false,
  false,
  false,
   // FHC flux
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
   false,  // kNuisFHCNuMuFlux10
   false,  // kNuisFHCNuMuFlux11
   false,  // kNuisFHCNuMuFlux12
   false,  // kNuisFHCNuMuFlux13
   false,  // kNuisFHCNuMuFlux14
   false,  // kNuisFHCNuMuFlux15
   false,  // kNuisFHCNuMuFlux16
   false,  // kNuisFHCNuMuFlux17
   false,  // kNuisFHCNuMuFlux18
   false,  // kNuisFHCNuMuBarFlux00
   false,  // kNuisFHCNuMuBarFlux01
   false,  // kNuisFHCNuMuBarFlux02
   false,  // kNuisFHCNuMuBarFlux03
   false,  // kNuisFHCNuMuBarFlux04
   false,  // kNuisFHCNuMuBarFlux05
   false,  // kNuisFHCNuMuBarFlux06
   false,  // kNuisFHCNuMuBarFlux07
   false,  // kNuisFHCNuMuBarFlux08
   false,  // kNuisFHCNuMuBarFlux09
   false,  // kNuisFHCNuMuBarFlux10
   false,  // kNuisFHCNuMuBarFlux11
   false,  // kNuisFHCNuMuBarFlux12
   false,  // kNuisFHCNuMuBarFlux13
   false,  // kNuisFHCNuMuBarFlux14
   false,  // kNuisFHCNuMuBarFlux15
   false,  // kNuisFHCNuMuBarFlux16
   false,  // kNuisFHCNuMuBarFlux17
   false,  // kNuisFHCNuMuBarFlux18
   false,  // kNuisFHCNuEFlux00
   false,  // kNuisFHCNuEFlux01
   false,  // kNuisFHCNuEFlux02
   false,  // kNuisFHCNuEFlux03
   false,  // kNuisFHCNuEFlux04
   false,  // kNuisFHCNuEFlux05
   false,  // kNuisFHCNuEFlux06
   false,  // kNuisFHCNuEBarFlux00
   false,  // kNuisFHCNuEBarFlux01
   false,  // kNuisFHCNuEBarFlux02
   false,  // kNuisFHCNuEBarFlux03
   false,  // kNuisFHCNuEBarFlux04
   false,  // kNuisFHCNuEBarFlux05
   false,  // kNuisFHCNuEBarFlux06
   // RHC flux
   false,  // kNuisRHCNuMuFlux00
   false,  // kNuisRHCNuMuFlux01
   false,  // kNuisRHCNuMuFlux02
   false,  // kNuisRHCNuMuFlux03
   false,  // kNuisRHCNuMuFlux04
   false,  // kNuisRHCNuMuFlux05
   false,  // kNuisRHCNuMuFlux06
   false,  // kNuisRHCNuMuFlux07
   false,  // kNuisRHCNuMuFlux08
   false,  // kNuisRHCNuMuFlux09
   false,  // kNuisRHCNuMuFlux10
   false,  // kNuisRHCNuMuFlux11
   false,  // kNuisRHCNuMuFlux12
   false,  // kNuisRHCNuMuFlux13
   false,  // kNuisRHCNuMuFlux14
   false,  // kNuisRHCNuMuFlux15
   false,  // kNuisRHCNuMuFlux16
   false,  // kNuisRHCNuMuFlux17
   false,  // kNuisRHCNuMuFlux18
   false,  // kNuisRHCNuMuBarFlux00
   false,  // kNuisRHCNuMuBarFlux01
   false,  // kNuisRHCNuMuBarFlux02
   false,  // kNuisRHCNuMuBarFlux03
   false,  // kNuisRHCNuMuBarFlux04
   false,  // kNuisRHCNuMuBarFlux05
   false,  // kNuisRHCNuMuBarFlux06
   false,  // kNuisRHCNuMuBarFlux07
   false,  // kNuisRHCNuMuBarFlux08
   false,  // kNuisRHCNuMuBarFlux09
   false,  // kNuisRHCNuMuBarFlux10
   false,  // kNuisRHCNuMuBarFlux11
   false,  // kNuisRHCNuMuBarFlux12
   false,  // kNuisRHCNuMuBarFlux13
   false,  // kNuisRHCNuMuBarFlux14
   false,  // kNuisRHCNuMuBarFlux15
   false,  // kNuisRHCNuMuBarFlux16
   false,  // kNuisRHCNuMuBarFlux17
   false,  // kNuisRHCNuMuBarFlux18
   false,  // kNuisRHCNuEFlux00
   false,  // kNuisRHCNuEFlux01
   false,  // kNuisRHCNuEFlux02
   false,  // kNuisRHCNuEFlux03
   false,  // kNuisRHCNuEFlux04
   false,  // kNuisRHCNuEFlux05
   false,  // kNuisRHCNuEFlux06
   false,  // kNuisRHCNuEBarFlux00
   false,  // kNuisRHCNuEBarFlux01
   false,  // kNuisRHCNuEBarFlux02
   false,  // kNuisRHCNuEBarFlux03
   false,  // kNuisRHCNuEBarFlux04
   false,  // kNuisRHCNuEBarFlux05
   false,  // kNuisRHCNuEBarFlux06
  // FHC flux
   true,  // kNuisFHCNuMuFDFlux00
   true,  // kNuisFHCNuMuFDFlux01
   true,  // kNuisFHCNuMuFDFlux02
   true,  // kNuisFHCNuMuFDFlux03
   true,  // kNuisFHCNuMuFDFlux04
   true,  // kNuisFHCNuMuFDFlux05
   true,  // kNuisFHCNuMuFDFlux06
   true,  // kNuisFHCNuMuFDFlux07
   true,  // kNuisFHCNuMuFDFlux08
   true,  // kNuisFHCNuMuFDFlux09
   true,  // kNuisFHCNuMuFDFlux10
   true,  // kNuisFHCNuMuFDFlux11
   true,  // kNuisFHCNuMuFDFlux12
   true,  // kNuisFHCNuMuFDFlux13
   true,  // kNuisFHCNuMuFDFlux14
   true,  // kNuisFHCNuMuFDFlux15
   true,  // kNuisFHCNuMuFDFlux16
   true,  // kNuisFHCNuMuFDFlux17
   true,  // kNuisFHCNuMuFDFlux18
   true,  // kNuisFHCNuMuBarFDFlux00
   true,  // kNuisFHCNuMuBarFDFlux01
   true,  // kNuisFHCNuMuBarFDFlux02
   true,  // kNuisFHCNuMuBarFDFlux03
   true,  // kNuisFHCNuMuBarFDFlux04
   true,  // kNuisFHCNuMuBarFDFlux05
   true,  // kNuisFHCNuMuBarFDFlux06
   true,  // kNuisFHCNuMuBarFDFlux07
   true,  // kNuisFHCNuMuBarFDFlux08
   true,  // kNuisFHCNuMuBarFDFlux09
   true,  // kNuisFHCNuMuBarFDFlux10
   true,  // kNuisFHCNuMuBarFDFlux11
   true,  // kNuisFHCNuMuBarFDFlux12
   true,  // kNuisFHCNuMuBarFDFlux13
   true,  // kNuisFHCNuMuBarFDFlux14
   true,  // kNuisFHCNuMuBarFDFlux15
   true,  // kNuisFHCNuMuBarFDFlux16
   true,  // kNuisFHCNuMuBarFDFlux17
   true,  // kNuisFHCNuMuBarFDFlux18
   true,  // kNuisFHCNuEFDFlux00
   true,  // kNuisFHCNuEFDFlux01
   true,  // kNuisFHCNuEFDFlux02
   true,  // kNuisFHCNuEFDFlux03
   true,  // kNuisFHCNuEFDFlux04
   true,  // kNuisFHCNuEFDFlux05
   true,  // kNuisFHCNuEFDFlux06
   true,  // kNuisFHCNuEBarFDFlux00
   true,  // kNuisFHCNuEBarFDFlux01
   true,  // kNuisFHCNuEBarFDFlux02
   true,  // kNuisFHCNuEBarFDFlux03
   true,  // kNuisFHCNuEBarFDFlux04
   true,  // kNuisFHCNuEBarFDFlux05
   true,  // kNuisFHCNuEBarFDFlux06
   // RHC flux
   true,  // kNuisRHCNuMuFDFlux00
   true,  // kNuisRHCNuMuFDFlux01
   true,  // kNuisRHCNuMuFDFlux02
   true,  // kNuisRHCNuMuFDFlux03
   true,  // kNuisRHCNuMuFDFlux04
   true,  // kNuisRHCNuMuFDFlux05
   true,  // kNuisRHCNuMuFDFlux06
   true,  // kNuisRHCNuMuFDFlux07
   true,  // kNuisRHCNuMuFDFlux08
   true,  // kNuisRHCNuMuFDFlux09
   true,  // kNuisRHCNuMuFDFlux10
   true,  // kNuisRHCNuMuFDFlux11
   true,  // kNuisRHCNuMuFDFlux12
   true,  // kNuisRHCNuMuFDFlux13
   true,  // kNuisRHCNuMuFDFlux14
   true,  // kNuisRHCNuMuFDFlux15
   true,  // kNuisRHCNuMuFDFlux16
   true,  // kNuisRHCNuMuFDFlux17
   true,  // kNuisRHCNuMuFDFlux18
   true,  // kNuisRHCNuMuBarFDFlux00
   true,  // kNuisRHCNuMuBarFDFlux01
   true,  // kNuisRHCNuMuBarFDFlux02
   true,  // kNuisRHCNuMuBarFDFlux03
   true,  // kNuisRHCNuMuBarFDFlux04
   true,  // kNuisRHCNuMuBarFDFlux05
   true,  // kNuisRHCNuMuBarFDFlux06
   true,  // kNuisRHCNuMuBarFDFlux07
   true,  // kNuisRHCNuMuBarFDFlux08
   true,  // kNuisRHCNuMuBarFDFlux09
   true,  // kNuisRHCNuMuBarFDFlux10
   true,  // kNuisRHCNuMuBarFDFlux11
   true,  // kNuisRHCNuMuBarFDFlux12
   true,  // kNuisRHCNuMuBarFDFlux13
   true,  // kNuisRHCNuMuBarFDFlux14
   true,  // kNuisRHCNuMuBarFDFlux15
   true,  // kNuisRHCNuMuBarFDFlux16
   true,  // kNuisRHCNuMuBarFDFlux17
   true,  // kNuisRHCNuMuBarFDFlux18
   true,  // kNuisRHCNuEFDFlux00
   true,  // kNuisRHCNuEFDFlux01
   true,  // kNuisRHCNuEFDFlux02
   true,  // kNuisRHCNuEFDFlux03
   true,  // kNuisRHCNuEFDFlux04
   true,  // kNuisRHCNuEFDFlux05
   true,  // kNuisRHCNuEFDFlux06
   true,  // kNuisRHCNuEBarFDFlux00
   true,  // kNuisRHCNuEBarFDFlux01
   true,  // kNuisRHCNuEBarFDFlux02
   true,  // kNuisRHCNuEBarFDFlux03
   true,  // kNuisRHCNuEBarFDFlux04
   true,  // kNuisRHCNuEBarFDFlux05
   true,  // kNuisRHCNuEBarFDFlux06
  // Cross-sections
   false, // kNuisIntNuCCQE1
   false, // kNuisIntNuCCQE2
   false, // kNuisIntNuCCQE3
   false, // kNuisIntNuBarCCQE1
   false, // kNuisIntNuBarCCQE2
   false, // kNuisIntNuBarCCQE3
   false, // kNuisIntNuCCMEC
   false, // kNuisIntNuBarCCMEC
   false, // kNuisIntNuCC1piz1
   false, // kNuisIntNuCC1piz2
   false, // kNuisIntNuCC1piz3
   false, // kNuisIntNuCC1pic1
   false, // kNuisIntNuCC1pic2
   false, // kNuisIntNuCC1pic3
   false, // kNuisIntNuBarCC1piz1
   false, // kNuisIntNuBarCC1piz2
   false, // kNuisIntNuBarCC1piz3
   false, // kNuisIntNuBarCC1pic1
   false, // kNuisIntNuBarCC1pic2
   false, // kNuisIntNuBarCC1pic3
   false, // kNuisIntNuCC2Pi
   false, // kNuisIntNuBarCC2Pi
   false, // kNuisIntNuDIS1
   false, // kNuisIntNuDIS2
   false, // kNuisIntNuDIS3
   false, // kNuisIntNuBarDIS1
   false, // kNuisIntNuBarDIS2
   false, // kNuisIntNuBarDIS3
   false, // kNuisIntNormNuCoherent
   false, // kNuisIntNormNuBarCoherent
   false, // kNuisIntNuNormNC
   false, // kNuisIntNuBarNormNC
   false, // kNuisIntNormNuMuToNuE
   false, // kNuisIntPiMeanFreePath
   false, // kNuisIntNucMeanFreePath
   false, // kNuisIntFracPiChargeExchange
   false, // kNuisIntFracPiInelastic
   false, // kNuisIntFracPiAbsorb
   false, // kNuisIntFracPiProduction
   false, // kNuisIntFracNucChargeExchange
   false, // kNuisIntFracNucInelastic
   false, // kNuisIntFracNucAbsorb
   false, // kNuisIntFracNucProduction
   // Detector systematics
   false, // kNuisEffNuMuCC0pi1trk
   false, // kNuisEffNuMuCC0pi2trk
   false, // kNuisEffNuMuCC1piC
   false, // kNuisEffNuMuCC1pi0
   false, // kNuisEffNuMuCC1piC1pi0
   false, // kNuisEffNuMuCCoth
   false, // kNuisEffNuECC
   false, // kNuisEffNuMuCCWS
   false,  // kNuisEffNC
  //far detector systematics
   false, //kNuisEffFDNuMuCCHigh  
   false, //kNuisEffFDNuMuCCLow
   false, //kNuisEffFDNuECCHigh  
   false //kNuisEffFDNuECCLow
};

// Is this a neutrino interaction model related parameter?
//
static const bool kFitIsNuIntRelated[kNFitParams] =
{
  //oscillation parameters
  false,
  false,
  false,
  false,
  false,
  false,
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
  // FHC flux
   false, // kNuisFHCNuMuFDFlux00
   false, // kNuisFHCNuMuFDFlux01
   false, // kNuisFHCNuMuFDFlux02
   false, // kNuisFHCNuMuFDFlux03
   false, // kNuisFHCNuMuFDFlux04
   false, // kNuisFHCNuMuFDFlux05
   false, // kNuisFHCNuMuFDFlux06
   false, // kNuisFHCNuMuFDFlux07
   false, // kNuisFHCNuMuFDFlux08
   false, // kNuisFHCNuMuFDFlux09
   false, // kNuisFHCNuMuFDFlux10
   false, // kNuisFHCNuMuFDFlux11
   false, // kNuisFHCNuMuFDFlux12
   false, // kNuisFHCNuMuFDFlux13
   false, // kNuisFHCNuMuFDFlux14
   false, // kNuisFHCNuMuFDFlux15
   false, // kNuisFHCNuMuFDFlux16
   false, // kNuisFHCNuMuFDFlux17
   false, // kNuisFHCNuMuFDFlux18
   false, // kNuisFHCNuMuBarFDFlux00
   false, // kNuisFHCNuMuBarFDFlux01
   false, // kNuisFHCNuMuBarFDFlux02
   false, // kNuisFHCNuMuBarFDFlux03
   false, // kNuisFHCNuMuBarFDFlux04
   false, // kNuisFHCNuMuBarFDFlux05
   false, // kNuisFHCNuMuBarFDFlux06
   false, // kNuisFHCNuMuBarFDFlux07
   false, // kNuisFHCNuMuBarFDFlux08
   false, // kNuisFHCNuMuBarFDFlux09
   false, // kNuisFHCNuMuBarFDFlux10
   false, // kNuisFHCNuMuBarFDFlux11
   false, // kNuisFHCNuMuBarFDFlux12
   false, // kNuisFHCNuMuBarFDFlux13
   false, // kNuisFHCNuMuBarFDFlux14
   false, // kNuisFHCNuMuBarFDFlux15
   false, // kNuisFHCNuMuBarFDFlux16
   false, // kNuisFHCNuMuBarFDFlux17
   false, // kNuisFHCNuMuBarFDFlux18
   false, // kNuisFHCNuEFDFlux00
   false, // kNuisFHCNuEFDFlux01
   false, // kNuisFHCNuEFDFlux02
   false, // kNuisFHCNuEFDFlux03
   false, // kNuisFHCNuEFDFlux04
   false, // kNuisFHCNuEFDFlux05
   false, // kNuisFHCNuEFDFlux06
   false, // kNuisFHCNuEBarFDFlux00
   false, // kNuisFHCNuEBarFDFlux01
   false, // kNuisFHCNuEBarFDFlux02
   false, // kNuisFHCNuEBarFDFlux03
   false, // kNuisFHCNuEBarFDFlux04
   false, // kNuisFHCNuEBarFDFlux05
   false, // kNuisFHCNuEBarFDFlux06
   // RHC flux
   false, // kNuisRHCNuMuFDFlux00
   false, // kNuisRHCNuMuFDFlux01
   false, // kNuisRHCNuMuFDFlux02
   false, // kNuisRHCNuMuFDFlux03
   false, // kNuisRHCNuMuFDFlux04
   false, // kNuisRHCNuMuFDFlux05
   false, // kNuisRHCNuMuFDFlux06
   false, // kNuisRHCNuMuFDFlux07
   false, // kNuisRHCNuMuFDFlux08
   false, // kNuisRHCNuMuFDFlux09
   false, // kNuisRHCNuMuFDFlux10
   false, // kNuisRHCNuMuFDFlux11
   false, // kNuisRHCNuMuFDFlux12
   false, // kNuisRHCNuMuFDFlux13
   false, // kNuisRHCNuMuFDFlux14
   false, // kNuisRHCNuMuFDFlux15
   false, // kNuisRHCNuMuFDFlux16
   false, // kNuisRHCNuMuFDFlux17
   false, // kNuisRHCNuMuFDFlux18
   false, // kNuisRHCNuMuBarFDFlux00
   false, // kNuisRHCNuMuBarFDFlux01
   false, // kNuisRHCNuMuBarFDFlux02
   false, // kNuisRHCNuMuBarFDFlux03
   false, // kNuisRHCNuMuBarFDFlux04
   false, // kNuisRHCNuMuBarFDFlux05
   false, // kNuisRHCNuMuBarFDFlux06
   false, // kNuisRHCNuMuBarFDFlux07
   false, // kNuisRHCNuMuBarFDFlux08
   false, // kNuisRHCNuMuBarFDFlux09
   false, // kNuisRHCNuMuBarFDFlux10
   false, // kNuisRHCNuMuBarFDFlux11
   false, // kNuisRHCNuMuBarFDFlux12
   false, // kNuisRHCNuMuBarFDFlux13
   false, // kNuisRHCNuMuBarFDFlux14
   false, // kNuisRHCNuMuBarFDFlux15
   false, // kNuisRHCNuMuBarFDFlux16
   false, // kNuisRHCNuMuBarFDFlux17
   false, // kNuisRHCNuMuBarFDFlux18
   false, // kNuisRHCNuEFDFlux00
   false, // kNuisRHCNuEFDFlux01
   false, // kNuisRHCNuEFDFlux02
   false, // kNuisRHCNuEFDFlux03
   false, // kNuisRHCNuEFDFlux04
   false, // kNuisRHCNuEFDFlux05
   false, // kNuisRHCNuEFDFlux06
   false, // kNuisRHCNuEBarFDFlux00
   false, // kNuisRHCNuEBarFDFlux01
   false, // kNuisRHCNuEBarFDFlux02
   false, // kNuisRHCNuEBarFDFlux03
   false, // kNuisRHCNuEBarFDFlux04
   false, // kNuisRHCNuEBarFDFlux05
   false, // kNuisRHCNuEBarFDFlux06
  // Cross-sections
   true, // kNuisIntNuCCQE1
   true, // kNuisIntNuCCQE2
   true, // kNuisIntNuCCQE3
   true, // kNuisIntNuBarCCQE1
   true, // kNuisIntNuBarCCQE2
   true, // kNuisIntNuBarCCQE3
   true, // kNuisIntNuCCMEC
   true, // kNuisIntNuBarCCMEC
   true, // kNuisIntNuCC1piz1
   true, // kNuisIntNuCC1piz2
   true, // kNuisIntNuCC1piz3
   true, // kNuisIntNuCC1pic1
   true, // kNuisIntNuCC1pic2
   true, // kNuisIntNuCC1pic3
   true, // kNuisIntNuBarCC1piz1
   true, // kNuisIntNuBarCC1piz2
   true, // kNuisIntNuBarCC1piz3
   true, // kNuisIntNuBarCC1pic1
   true, // kNuisIntNuBarCC1pic2
   true, // kNuisIntNuBarCC1pic3
   true, // kNuisIntNuCC2Pi
   true, // kNuisIntNuBarCC2Pi
   true, // kNuisIntNuDIS1
   true, // kNuisIntNuDIS2
   true, // kNuisIntNuDIS3
   true, // kNuisIntNuBarDIS1
   true, // kNuisIntNuBarDIS2
   true, // kNuisIntNuBarDIS3
   true, // kNuisIntNormNuCoherent
   true, // kNuisIntNormNuBarCoherent
   true, // kNuisIntNuNormNC
   true, // kNuisIntNuBarNormNC
   true, // kNuisIntNormNuMuToNuE
   true, // kNuisIntPiMeanFreePath
   true, // kNuisIntNucMeanFreePath
   true, // kNuisIntFracPiChargeExchange
   true, // kNuisIntFracPiInelastic
   true, // kNuisIntFracPiAbsorb
   true, // kNuisIntFracPiProduction
   true, // kNuisIntFracNucChargeExchange
   true, // kNuisIntFracNucInelastic
   true, // kNuisIntFracNucAbsorb
   true, // kNuisIntFracNucProduction
   // Detector systematics
   false, // kNuisEffNuMuCC0pi1trk
   false, // kNuisEffNuMuCC0pi2trk
   false, // kNuisEffNuMuCC1piC
   false, // kNuisEffNuMuCC1pi0
   false, // kNuisEffNuMuCC1piC1pi0
   false, // kNuisEffNuMuCCoth
   false, // kNuisEffNuECC
   false, // kNuisEffNuMuCCWS
   false,  // kNuisEffNC
  //Far detector systematics
   false, //kNuisEffFDNuMuCCHigh  
   false, //kNuisEffFDNuMuCCLow  
   false, //kNuisEffFDNuECCHigh  
   false //kNuisEffFDNuECCLow  
};

// Is this a neutrino detector related parameter?
//
static const bool kFitIsNuDetRelated[kNFitParams] =
{
  //oscillation parameters
  false,
  false,
  false,
  false,
  false,
  false,
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
  // FHC flux
   false, // kNuisFHCNuMuFDFlux00
   false, // kNuisFHCNuMuFDFlux01
   false, // kNuisFHCNuMuFDFlux02
   false, // kNuisFHCNuMuFDFlux03
   false, // kNuisFHCNuMuFDFlux04
   false, // kNuisFHCNuMuFDFlux05
   false, // kNuisFHCNuMuFDFlux06
   false, // kNuisFHCNuMuFDFlux07
   false, // kNuisFHCNuMuFDFlux08
   false, // kNuisFHCNuMuFDFlux09
   false, // kNuisFHCNuMuFDFlux10
   false, // kNuisFHCNuMuFDFlux11
   false, // kNuisFHCNuMuFDFlux12
   false, // kNuisFHCNuMuFDFlux13
   false, // kNuisFHCNuMuFDFlux14
   false, // kNuisFHCNuMuFDFlux15
   false, // kNuisFHCNuMuFDFlux16
   false, // kNuisFHCNuMuFDFlux17
   false, // kNuisFHCNuMuFDFlux18
   false, // kNuisFHCNuMuBarFDFlux00
   false, // kNuisFHCNuMuBarFDFlux01
   false, // kNuisFHCNuMuBarFDFlux02
   false, // kNuisFHCNuMuBarFDFlux03
   false, // kNuisFHCNuMuBarFDFlux04
   false, // kNuisFHCNuMuBarFDFlux05
   false, // kNuisFHCNuMuBarFDFlux06
   false, // kNuisFHCNuMuBarFDFlux07
   false, // kNuisFHCNuMuBarFDFlux08
   false, // kNuisFHCNuMuBarFDFlux09
   false, // kNuisFHCNuMuBarFDFlux10
   false, // kNuisFHCNuMuBarFDFlux11
   false, // kNuisFHCNuMuBarFDFlux12
   false, // kNuisFHCNuMuBarFDFlux13
   false, // kNuisFHCNuMuBarFDFlux14
   false, // kNuisFHCNuMuBarFDFlux15
   false, // kNuisFHCNuMuBarFDFlux16
   false, // kNuisFHCNuMuBarFDFlux17
   false, // kNuisFHCNuMuBarFDFlux18
   false, // kNuisFHCNuEFDFlux00
   false, // kNuisFHCNuEFDFlux01
   false, // kNuisFHCNuEFDFlux02
   false, // kNuisFHCNuEFDFlux03
   false, // kNuisFHCNuEFDFlux04
   false, // kNuisFHCNuEFDFlux05
   false, // kNuisFHCNuEFDFlux06
   false, // kNuisFHCNuEBarFDFlux00
   false, // kNuisFHCNuEBarFDFlux01
   false, // kNuisFHCNuEBarFDFlux02
   false, // kNuisFHCNuEBarFDFlux03
   false, // kNuisFHCNuEBarFDFlux04
   false, // kNuisFHCNuEBarFDFlux05
   false, // kNuisFHCNuEBarFDFlux06
   // RHC flux
   false, // kNuisRHCNuMuFDFlux00
   false, // kNuisRHCNuMuFDFlux01
   false, // kNuisRHCNuMuFDFlux02
   false, // kNuisRHCNuMuFDFlux03
   false, // kNuisRHCNuMuFDFlux04
   false, // kNuisRHCNuMuFDFlux05
   false, // kNuisRHCNuMuFDFlux06
   false, // kNuisRHCNuMuFDFlux07
   false, // kNuisRHCNuMuFDFlux08
   false, // kNuisRHCNuMuFDFlux09
   false, // kNuisRHCNuMuFDFlux10
   false, // kNuisRHCNuMuFDFlux11
   false, // kNuisRHCNuMuFDFlux12
   false, // kNuisRHCNuMuFDFlux13
   false, // kNuisRHCNuMuFDFlux14
   false, // kNuisRHCNuMuFDFlux15
   false, // kNuisRHCNuMuFDFlux16
   false, // kNuisRHCNuMuFDFlux17
   false, // kNuisRHCNuMuFDFlux18
   false, // kNuisRHCNuMuBarFDFlux00
   false, // kNuisRHCNuMuBarFDFlux01
   false, // kNuisRHCNuMuBarFDFlux02
   false, // kNuisRHCNuMuBarFDFlux03
   false, // kNuisRHCNuMuBarFDFlux04
   false, // kNuisRHCNuMuBarFDFlux05
   false, // kNuisRHCNuMuBarFDFlux06
   false, // kNuisRHCNuMuBarFDFlux07
   false, // kNuisRHCNuMuBarFDFlux08
   false, // kNuisRHCNuMuBarFDFlux09
   false, // kNuisRHCNuMuBarFDFlux10
   false, // kNuisRHCNuMuBarFDFlux11
   false, // kNuisRHCNuMuBarFDFlux12
   false, // kNuisRHCNuMuBarFDFlux13
   false, // kNuisRHCNuMuBarFDFlux14
   false, // kNuisRHCNuMuBarFDFlux15
   false, // kNuisRHCNuMuBarFDFlux16
   false, // kNuisRHCNuMuBarFDFlux17
   false, // kNuisRHCNuMuBarFDFlux18
   false, // kNuisRHCNuEFDFlux00
   false, // kNuisRHCNuEFDFlux01
   false, // kNuisRHCNuEFDFlux02
   false, // kNuisRHCNuEFDFlux03
   false, // kNuisRHCNuEFDFlux04
   false, // kNuisRHCNuEFDFlux05
   false, // kNuisRHCNuEFDFlux06
   false, // kNuisRHCNuEBarFDFlux00
   false, // kNuisRHCNuEBarFDFlux01
   false, // kNuisRHCNuEBarFDFlux02
   false, // kNuisRHCNuEBarFDFlux03
   false, // kNuisRHCNuEBarFDFlux04
   false, // kNuisRHCNuEBarFDFlux05
   false, // kNuisRHCNuEBarFDFlux06
  // Cross-sections
   false, // kNuisIntNuCCQE1
   false, // kNuisIntNuCCQE2
   false, // kNuisIntNuCCQE3
   false, // kNuisIntNuBarCCQE1
   false, // kNuisIntNuBarCCQE2
   false, // kNuisIntNuBarCCQE3
   false, // kNuisIntNuCCMEC
   false, // kNuisIntNuBarCCMEC
   false, // kNuisIntNuCC1piz1
   false, // kNuisIntNuCC1piz2
   false, // kNuisIntNuCC1piz3
   false, // kNuisIntNuCC1pic1
   false, // kNuisIntNuCC1pic2
   false, // kNuisIntNuCC1pic3
   false, // kNuisIntNuBarCC1piz1
   false, // kNuisIntNuBarCC1piz2
   false, // kNuisIntNuBarCC1piz3
   false, // kNuisIntNuBarCC1pic1
   false, // kNuisIntNuBarCC1pic2
   false, // kNuisIntNuBarCC1pic3
   false, // kNuisIntNuCC2Pi
   false, // kNuisIntNuBarCC2Pi
   false, // kNuisIntNuDIS1
   false, // kNuisIntNuDIS2
   false, // kNuisIntNuDIS3
   false, // kNuisIntNuBarDIS1
   false, // kNuisIntNuBarDIS2
   false, // kNuisIntNuBarDIS3
   false, // kNuisIntNormNuCoherent
   false, // kNuisIntNormNuBarCoherent
   false, // kNuisIntNuNormNC
   false, // kNuisIntNuBarNormNC
   false, // kNuisIntNormNuMuToNuE
   false, // kNuisIntPiMeanFreePath
   false, // kNuisIntNucMeanFreePath
   false, // kNuisIntFracPiChargeExchange
   false, // kNuisIntFracPiInelastic
   false, // kNuisIntFracPiAbsorb
   false, // kNuisIntFracPiProduction
   false, // kNuisIntFracNucChargeExchange
   false, // kNuisIntFracNucInelastic
   false, // kNuisIntFracNucAbsorb
   false, // kNuisIntFracNucProduction
   // Detector systematics
   true,  // kNuisEffNuMuCC0pi1trk
   true,  // kNuisEffNuMuCC0pi2trk
   true,  // kNuisEffNuMuCC1piC
   true,  // kNuisEffNuMuCC1pi0
   true,  // kNuisEffNuMuCC1piC1pi0
   true,  // kNuisEffNuMuCCoth
   true,  // kNuisEffNuECC
   true,  // kNuisEffNuMuCCWS
  true,   // kNuisEffNC
  //far detector systematics
   true, //kNuisEffFDNuMuCCHigh  
   true, //kNuisEffFDNuMuCCLow  
   true, //kNuisEffFDNuECCHigh  
   true //kNuisEffFDNuECCLow  
};

// Is this a neutrino detector related parameter?
//
static const bool kFitIsNuNDDetRelated[kNFitParams] =
{
  //oscillation parameters
  false,
  false,
  false,
  false,
  false,
  false,
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
  // FHC flux
   false, // kNuisFHCNuMuFDFlux00
   false, // kNuisFHCNuMuFDFlux01
   false, // kNuisFHCNuMuFDFlux02
   false, // kNuisFHCNuMuFDFlux03
   false, // kNuisFHCNuMuFDFlux04
   false, // kNuisFHCNuMuFDFlux05
   false, // kNuisFHCNuMuFDFlux06
   false, // kNuisFHCNuMuFDFlux07
   false, // kNuisFHCNuMuFDFlux08
   false, // kNuisFHCNuMuFDFlux09
   false, // kNuisFHCNuMuFDFlux10
   false, // kNuisFHCNuMuFDFlux11
   false, // kNuisFHCNuMuFDFlux12
   false, // kNuisFHCNuMuFDFlux13
   false, // kNuisFHCNuMuFDFlux14
   false, // kNuisFHCNuMuFDFlux15
   false, // kNuisFHCNuMuFDFlux16
   false, // kNuisFHCNuMuFDFlux17
   false, // kNuisFHCNuMuFDFlux18
   false, // kNuisFHCNuMuBarFDFlux00
   false, // kNuisFHCNuMuBarFDFlux01
   false, // kNuisFHCNuMuBarFDFlux02
   false, // kNuisFHCNuMuBarFDFlux03
   false, // kNuisFHCNuMuBarFDFlux04
   false, // kNuisFHCNuMuBarFDFlux05
   false, // kNuisFHCNuMuBarFDFlux06
   false, // kNuisFHCNuMuBarFDFlux07
   false, // kNuisFHCNuMuBarFDFlux08
   false, // kNuisFHCNuMuBarFDFlux09
   false, // kNuisFHCNuMuBarFDFlux10
   false, // kNuisFHCNuMuBarFDFlux11
   false, // kNuisFHCNuMuBarFDFlux12
   false, // kNuisFHCNuMuBarFDFlux13
   false, // kNuisFHCNuMuBarFDFlux14
   false, // kNuisFHCNuMuBarFDFlux15
   false, // kNuisFHCNuMuBarFDFlux16
   false, // kNuisFHCNuMuBarFDFlux17
   false, // kNuisFHCNuMuBarFDFlux18
   false, // kNuisFHCNuEFDFlux00
   false, // kNuisFHCNuEFDFlux01
   false, // kNuisFHCNuEFDFlux02
   false, // kNuisFHCNuEFDFlux03
   false, // kNuisFHCNuEFDFlux04
   false, // kNuisFHCNuEFDFlux05
   false, // kNuisFHCNuEFDFlux06
   false, // kNuisFHCNuEBarFDFlux00
   false, // kNuisFHCNuEBarFDFlux01
   false, // kNuisFHCNuEBarFDFlux02
   false, // kNuisFHCNuEBarFDFlux03
   false, // kNuisFHCNuEBarFDFlux04
   false, // kNuisFHCNuEBarFDFlux05
   false, // kNuisFHCNuEBarFDFlux06
   // RHC flux
   false, // kNuisRHCNuMuFDFlux00
   false, // kNuisRHCNuMuFDFlux01
   false, // kNuisRHCNuMuFDFlux02
   false, // kNuisRHCNuMuFDFlux03
   false, // kNuisRHCNuMuFDFlux04
   false, // kNuisRHCNuMuFDFlux05
   false, // kNuisRHCNuMuFDFlux06
   false, // kNuisRHCNuMuFDFlux07
   false, // kNuisRHCNuMuFDFlux08
   false, // kNuisRHCNuMuFDFlux09
   false, // kNuisRHCNuMuFDFlux10
   false, // kNuisRHCNuMuFDFlux11
   false, // kNuisRHCNuMuFDFlux12
   false, // kNuisRHCNuMuFDFlux13
   false, // kNuisRHCNuMuFDFlux14
   false, // kNuisRHCNuMuFDFlux15
   false, // kNuisRHCNuMuFDFlux16
   false, // kNuisRHCNuMuFDFlux17
   false, // kNuisRHCNuMuFDFlux18
   false, // kNuisRHCNuMuBarFDFlux00
   false, // kNuisRHCNuMuBarFDFlux01
   false, // kNuisRHCNuMuBarFDFlux02
   false, // kNuisRHCNuMuBarFDFlux03
   false, // kNuisRHCNuMuBarFDFlux04
   false, // kNuisRHCNuMuBarFDFlux05
   false, // kNuisRHCNuMuBarFDFlux06
   false, // kNuisRHCNuMuBarFDFlux07
   false, // kNuisRHCNuMuBarFDFlux08
   false, // kNuisRHCNuMuBarFDFlux09
   false, // kNuisRHCNuMuBarFDFlux10
   false, // kNuisRHCNuMuBarFDFlux11
   false, // kNuisRHCNuMuBarFDFlux12
   false, // kNuisRHCNuMuBarFDFlux13
   false, // kNuisRHCNuMuBarFDFlux14
   false, // kNuisRHCNuMuBarFDFlux15
   false, // kNuisRHCNuMuBarFDFlux16
   false, // kNuisRHCNuMuBarFDFlux17
   false, // kNuisRHCNuMuBarFDFlux18
   false, // kNuisRHCNuEFDFlux00
   false, // kNuisRHCNuEFDFlux01
   false, // kNuisRHCNuEFDFlux02
   false, // kNuisRHCNuEFDFlux03
   false, // kNuisRHCNuEFDFlux04
   false, // kNuisRHCNuEFDFlux05
   false, // kNuisRHCNuEFDFlux06
   false, // kNuisRHCNuEBarFDFlux00
   false, // kNuisRHCNuEBarFDFlux01
   false, // kNuisRHCNuEBarFDFlux02
   false, // kNuisRHCNuEBarFDFlux03
   false, // kNuisRHCNuEBarFDFlux04
   false, // kNuisRHCNuEBarFDFlux05
   false, // kNuisRHCNuEBarFDFlux06
  // Cross-sections
   false, // kNuisIntNuCCQE1
   false, // kNuisIntNuCCQE2
   false, // kNuisIntNuCCQE3
   false, // kNuisIntNuBarCCQE1
   false, // kNuisIntNuBarCCQE2
   false, // kNuisIntNuBarCCQE3
   false, // kNuisIntNuCCMEC
   false, // kNuisIntNuBarCCMEC
   false, // kNuisIntNuCC1piz1
   false, // kNuisIntNuCC1piz2
   false, // kNuisIntNuCC1piz3
   false, // kNuisIntNuCC1pic1
   false, // kNuisIntNuCC1pic2
   false, // kNuisIntNuCC1pic3
   false, // kNuisIntNuBarCC1piz1
   false, // kNuisIntNuBarCC1piz2
   false, // kNuisIntNuBarCC1piz3
   false, // kNuisIntNuBarCC1pic1
   false, // kNuisIntNuBarCC1pic2
   false, // kNuisIntNuBarCC1pic3
   false, // kNuisIntNuCC2Pi
   false, // kNuisIntNuBarCC2Pi
   false, // kNuisIntNuDIS1
   false, // kNuisIntNuDIS2
   false, // kNuisIntNuDIS3
   false, // kNuisIntNuBarDIS1
   false, // kNuisIntNuBarDIS2
   false, // kNuisIntNuBarDIS3
   false, // kNuisIntNormNuCoherent
   false, // kNuisIntNormNuBarCoherent
   false, // kNuisIntNuNormNC
   false, // kNuisIntNuBarNormNC
   false, // kNuisIntNormNuMuToNuE
   false, // kNuisIntPiMeanFreePath
   false, // kNuisIntNucMeanFreePath
   false, // kNuisIntFracPiChargeExchange
   false, // kNuisIntFracPiInelastic
   false, // kNuisIntFracPiAbsorb
   false, // kNuisIntFracPiProduction
   false, // kNuisIntFracNucChargeExchange
   false, // kNuisIntFracNucInelastic
   false, // kNuisIntFracNucAbsorb
   false, // kNuisIntFracNucProduction
   // Detector systematics
   true,  // kNuisEffNuMuCC0pi1trk
   true,  // kNuisEffNuMuCC0pi2trk
   true,  // kNuisEffNuMuCC1piC
   true,  // kNuisEffNuMuCC1pi0
   true,  // kNuisEffNuMuCC1piC1pi0
   true,  // kNuisEffNuMuCCoth
   true,  // kNuisEffNuECC
   true,  // kNuisEffNuMuCCWS
  true,   // kNuisEffNC
  //far detector systematics
   false, //kNuisEffFDNuMuCCHigh  
   false, //kNuisEffFDNuMuCCLow  
   false, //kNuisEffFDNuECCHigh  
   false //kNuisEffFDNuECCLow  
};

// Is this a neutrino detector related parameter?
//
static const bool kFitIsNuFDDetRelated[kNFitParams] =
{
  //oscillation parameters
  false,
  false,
  false,
  false,
  false,
  false,
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
  // FHC flux
   false, // kNuisFHCNuMuFDFlux00
   false, // kNuisFHCNuMuFDFlux01
   false, // kNuisFHCNuMuFDFlux02
   false, // kNuisFHCNuMuFDFlux03
   false, // kNuisFHCNuMuFDFlux04
   false, // kNuisFHCNuMuFDFlux05
   false, // kNuisFHCNuMuFDFlux06
   false, // kNuisFHCNuMuFDFlux07
   false, // kNuisFHCNuMuFDFlux08
   false, // kNuisFHCNuMuFDFlux09
   false, // kNuisFHCNuMuFDFlux10
   false, // kNuisFHCNuMuFDFlux11
   false, // kNuisFHCNuMuFDFlux12
   false, // kNuisFHCNuMuFDFlux13
   false, // kNuisFHCNuMuFDFlux14
   false, // kNuisFHCNuMuFDFlux15
   false, // kNuisFHCNuMuFDFlux16
   false, // kNuisFHCNuMuFDFlux17
   false, // kNuisFHCNuMuFDFlux18
   false, // kNuisFHCNuMuBarFDFlux00
   false, // kNuisFHCNuMuBarFDFlux01
   false, // kNuisFHCNuMuBarFDFlux02
   false, // kNuisFHCNuMuBarFDFlux03
   false, // kNuisFHCNuMuBarFDFlux04
   false, // kNuisFHCNuMuBarFDFlux05
   false, // kNuisFHCNuMuBarFDFlux06
   false, // kNuisFHCNuMuBarFDFlux07
   false, // kNuisFHCNuMuBarFDFlux08
   false, // kNuisFHCNuMuBarFDFlux09
   false, // kNuisFHCNuMuBarFDFlux10
   false, // kNuisFHCNuMuBarFDFlux11
   false, // kNuisFHCNuMuBarFDFlux12
   false, // kNuisFHCNuMuBarFDFlux13
   false, // kNuisFHCNuMuBarFDFlux14
   false, // kNuisFHCNuMuBarFDFlux15
   false, // kNuisFHCNuMuBarFDFlux16
   false, // kNuisFHCNuMuBarFDFlux17
   false, // kNuisFHCNuMuBarFDFlux18
   false, // kNuisFHCNuEFDFlux00
   false, // kNuisFHCNuEFDFlux01
   false, // kNuisFHCNuEFDFlux02
   false, // kNuisFHCNuEFDFlux03
   false, // kNuisFHCNuEFDFlux04
   false, // kNuisFHCNuEFDFlux05
   false, // kNuisFHCNuEFDFlux06
   false, // kNuisFHCNuEBarFDFlux00
   false, // kNuisFHCNuEBarFDFlux01
   false, // kNuisFHCNuEBarFDFlux02
   false, // kNuisFHCNuEBarFDFlux03
   false, // kNuisFHCNuEBarFDFlux04
   false, // kNuisFHCNuEBarFDFlux05
   false, // kNuisFHCNuEBarFDFlux06
   // RHC flux
   false, // kNuisRHCNuMuFDFlux00
   false, // kNuisRHCNuMuFDFlux01
   false, // kNuisRHCNuMuFDFlux02
   false, // kNuisRHCNuMuFDFlux03
   false, // kNuisRHCNuMuFDFlux04
   false, // kNuisRHCNuMuFDFlux05
   false, // kNuisRHCNuMuFDFlux06
   false, // kNuisRHCNuMuFDFlux07
   false, // kNuisRHCNuMuFDFlux08
   false, // kNuisRHCNuMuFDFlux09
   false, // kNuisRHCNuMuFDFlux10
   false, // kNuisRHCNuMuFDFlux11
   false, // kNuisRHCNuMuFDFlux12
   false, // kNuisRHCNuMuFDFlux13
   false, // kNuisRHCNuMuFDFlux14
   false, // kNuisRHCNuMuFDFlux15
   false, // kNuisRHCNuMuFDFlux16
   false, // kNuisRHCNuMuFDFlux17
   false, // kNuisRHCNuMuFDFlux18
   false, // kNuisRHCNuMuBarFDFlux00
   false, // kNuisRHCNuMuBarFDFlux01
   false, // kNuisRHCNuMuBarFDFlux02
   false, // kNuisRHCNuMuBarFDFlux03
   false, // kNuisRHCNuMuBarFDFlux04
   false, // kNuisRHCNuMuBarFDFlux05
   false, // kNuisRHCNuMuBarFDFlux06
   false, // kNuisRHCNuMuBarFDFlux07
   false, // kNuisRHCNuMuBarFDFlux08
   false, // kNuisRHCNuMuBarFDFlux09
   false, // kNuisRHCNuMuBarFDFlux10
   false, // kNuisRHCNuMuBarFDFlux11
   false, // kNuisRHCNuMuBarFDFlux12
   false, // kNuisRHCNuMuBarFDFlux13
   false, // kNuisRHCNuMuBarFDFlux14
   false, // kNuisRHCNuMuBarFDFlux15
   false, // kNuisRHCNuMuBarFDFlux16
   false, // kNuisRHCNuMuBarFDFlux17
   false, // kNuisRHCNuMuBarFDFlux18
   false, // kNuisRHCNuEFDFlux00
   false, // kNuisRHCNuEFDFlux01
   false, // kNuisRHCNuEFDFlux02
   false, // kNuisRHCNuEFDFlux03
   false, // kNuisRHCNuEFDFlux04
   false, // kNuisRHCNuEFDFlux05
   false, // kNuisRHCNuEFDFlux06
   false, // kNuisRHCNuEBarFDFlux00
   false, // kNuisRHCNuEBarFDFlux01
   false, // kNuisRHCNuEBarFDFlux02
   false, // kNuisRHCNuEBarFDFlux03
   false, // kNuisRHCNuEBarFDFlux04
   false, // kNuisRHCNuEBarFDFlux05
   false, // kNuisRHCNuEBarFDFlux06
  // Cross-sections
   false, // kNuisIntNuCCQE1
   false, // kNuisIntNuCCQE2
   false, // kNuisIntNuCCQE3
   false, // kNuisIntNuBarCCQE1
   false, // kNuisIntNuBarCCQE2
   false, // kNuisIntNuBarCCQE3
   false, // kNuisIntNuCCMEC
   false, // kNuisIntNuBarCCMEC
   false, // kNuisIntNuCC1piz1
   false, // kNuisIntNuCC1piz2
   false, // kNuisIntNuCC1piz3
   false, // kNuisIntNuCC1pic1
   false, // kNuisIntNuCC1pic2
   false, // kNuisIntNuCC1pic3
   false, // kNuisIntNuBarCC1piz1
   false, // kNuisIntNuBarCC1piz2
   false, // kNuisIntNuBarCC1piz3
   false, // kNuisIntNuBarCC1pic1
   false, // kNuisIntNuBarCC1pic2
   false, // kNuisIntNuBarCC1pic3
   false, // kNuisIntNuCC2Pi
   false, // kNuisIntNuBarCC2Pi
   false, // kNuisIntNuDIS1
   false, // kNuisIntNuDIS2
   false, // kNuisIntNuDIS3
   false, // kNuisIntNuBarDIS1
   false, // kNuisIntNuBarDIS2
   false, // kNuisIntNuBarDIS3
   false, // kNuisIntNormNuCoherent
   false, // kNuisIntNormNuBarCoherent
   false, // kNuisIntNuNormNC
   false, // kNuisIntNuBarNormNC
   false, // kNuisIntNormNuMuToNuE
   false, // kNuisIntPiMeanFreePath
   false, // kNuisIntNucMeanFreePath
   false, // kNuisIntFracPiChargeExchange
   false, // kNuisIntFracPiInelastic
   false, // kNuisIntFracPiAbsorb
   false, // kNuisIntFracPiProduction
   false, // kNuisIntFracNucChargeExchange
   false, // kNuisIntFracNucInelastic
   false, // kNuisIntFracNucAbsorb
   false, // kNuisIntFracNucProduction
   // Detector systematics
   false,  // kNuisEffNuMuCC0pi1trk
   false,  // kNuisEffNuMuCC0pi2trk
   false,  // kNuisEffNuMuCC1piC
   false,  // kNuisEffNuMuCC1pi0
   false,  // kNuisEffNuMuCC1piC1pi0
   false,  // kNuisEffNuMuCCoth
   false,  // kNuisEffNuECC
   false,  // kNuisEffNuMuCCWS
  false,   // kNuisEffNC
  //far detector systematics
   true, //kNuisEffFDNuMuCCHigh  
   true, //kNuisEffFDNuMuCCLow  
   true, //kNuisEffFDNuECCHigh  
   true //kNuisEffFDNuECCLow  
};

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

  string  AsString    (conv::PhysParamId_t p);
  string  AsStringSimple(conv::PhysParamId_t p);
  string  AsStringTeX (conv::PhysParamId_t p, bool root = false);

  // Aliases for above
  string  ParamAsString    (conv::PhysParamId_t p) ;
  string  ParamAsStringTeX (conv::PhysParamId_t p, bool root = false);

  conv::PhysParamId_t PhysParamFromString(string p);

  // If you give a CorrelatedSystematics object, it'll ignore your list's standard systematics and use this set instead
  PhysHypothesis GetPhysHypothesis   (Option_t * param_list = "standard" /*, Option_t * param_values = "nominal"*/);
  FitParamList * GetFitParameterList (Option_t * param_list = "standard", const CorrelatedSystematics * syst = 0);

  bool IsOscParam  (conv::PhysParamId_t p);
  bool IsSystematic(conv::PhysParamId_t p);

  bool IsNuFluxRelated  (conv::PhysParamId_t p);
  bool IsNuIntRelated   (conv::PhysParamId_t p);
  bool IsNuDetRelated   (conv::PhysParamId_t p);
  bool IsFSI            (conv::PhysParamId_t p);
  
  bool IsNDFluxRelated  (conv::PhysParamId_t p);
  bool IsFDFluxRelated  (conv::PhysParamId_t p);
  bool IsNuNDDetRelated (conv::PhysParamId_t p);
  bool IsNuFDDetRelated (conv::PhysParamId_t p);

  conv::FitParamGroup_t GetParameterGroup(conv::PhysParamId_t p);

  bool ParamIsAppliedTo(conv::BeamConf_t b, conv::Sample_t s, conv::Detector_t d, 
                        conv::ReacMode_t m, conv::PhysParamId_t p);
  bool OscProbIsAppliedTo(conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s,
                          conv::ReacMode_t m);
  bool ParamHasSplines(conv::PhysParamId_t p);
  
  // Return pointer to array of min/max                      
  const double * EtrueRange (conv::PhysParamId_t p);
  const double * Q2trueRange(conv::PhysParamId_t p);

  // Tell the framework classes what our parameter names are
  void PopulateNameRegistry(void);

} //util

} // valor

#endif

