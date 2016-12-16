#ifndef valor_dune_fit_param_true_ranges_h
#define valor_dune_fit_param_true_ranges_h

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
   false,  // kNuisEffFHCnumuCC0pi1trk01        
   false,  // kNuisEffFHCnumuCC0pi1trk02        
   false,  // kNuisEffFHCnumuCC0pi1trk03        
   false,  // kNuisEffFHCnumuCC0pi1trk04        
   false,  // kNuisEffFHCnumuCC0pi1trk05        
   false,  // kNuisEffFHCnumuCC0pi1trk06        
   false,  // kNuisEffFHCnumuCC0pi1trk07        
   false,  // kNuisEffFHCnumuCC0pi1trk08        
   false,  // kNuisEffFHCnumuCC0pi1trk09        
   false,  // kNuisEffFHCnumuCC0pi2trk01        
   false,  // kNuisEffFHCnumuCC0pi2trk02        
   false,  // kNuisEffFHCnumuCC0pi2trk03        
   false,  // kNuisEffFHCnumuCC0pi2trk04        
   false,  // kNuisEffFHCnumuCC0pi2trk05        
   false,  // kNuisEffFHCnumuCC0pi2trk06        
   false,  // kNuisEffFHCnumuCC0pi2trk07        
   false,  // kNuisEffFHCnumuCC0pi2trk08        
   false,  // kNuisEffFHCnumuCC0pi2trk09        
   false,  // kNuisEffFHCnumuCC0piNtrk01        
   false,  // kNuisEffFHCnumuCC0piNtrk02        
   false,  // kNuisEffFHCnumuCC0piNtrk03        
   false,  // kNuisEffFHCnumuCC0piNtrk04        
   false,  // kNuisEffFHCnumuCC0piNtrk05        
   false,  // kNuisEffFHCnumuCC0piNtrk06        
   false,  // kNuisEffFHCnumuCC0piNtrk07        
   false,  // kNuisEffFHCnumuCC0piNtrk08        
   false,  // kNuisEffFHCnumuCC0piNtrk09        
   false,  // kNuisEffFHCnumuCC0piNtrk10        
   false,  // kNuisEffFHCnumuCC0piNtrk11        
   false,  // kNuisEffFHCnumuCC0piNtrk12        
   false,  // kNuisEffFHCnumuCC0piNtrk13        
   false,  // kNuisEffFHCnumuCC0piNtrk14        
   false,  // kNuisEffFHCnumuCC0piNtrk15        
   false,  // kNuisEffFHCnumuCC1pi3trkDelta01   
   false,  // kNuisEffFHCnumuCC1pi3trkDelta02   
   false,  // kNuisEffFHCnumuCC1pi3trkDelta03   
   false,  // kNuisEffFHCnumuCC1pi3trkDelta04   
   false,  // kNuisEffFHCnumuCC1pi3trkDelta05   
   false,  // kNuisEffFHCnumuCC1pi3trkDelta06   
   false,  // kNuisEffFHCnumuCC1pi3trkDelta07   
   false,  // kNuisEffFHCnumuCC1pi3trkDelta08   
   false,  // kNuisEffFHCnumuCC1pi3trkDelta09   
   false,  // kNuisEffFHCnumuCC1pi3trkDelta10   
   false,  // kNuisEffFHCnumuCC1pi3trkDelta11   
   false,  // kNuisEffFHCnumuCC1pi3trkDelta12   
   false,  // kNuisEffFHCnumuCC1pi3trkDelta13   
   false,  // kNuisEffFHCnumuCC1pi3trkDelta14   
   false,  // kNuisEffFHCnumuCC1pi3trkDelta15   
   false,  // kNuisEffFHCnumuCC1pic01           
   false,  // kNuisEffFHCnumuCC1pic02           
   false,  // kNuisEffFHCnumuCC1pic03           
   false,  // kNuisEffFHCnumuCC1pic04           
   false,  // kNuisEffFHCnumuCC1pic05           
   false,  // kNuisEffFHCnumuCC1pic06           
   false,  // kNuisEffFHCnumuCC1pic07           
   false,  // kNuisEffFHCnumuCC1pic08           
   false,  // kNuisEffFHCnumuCC1pic09           
   false,  // kNuisEffFHCnumuCC1pi001           
   false,  // kNuisEffFHCnumuCC1pi002           
   false,  // kNuisEffFHCnumuCC1pi003           
   false,  // kNuisEffFHCnumuCC1pi004           
   false,  // kNuisEffFHCnumuCC1pi005           
   false,  // kNuisEffFHCnumuCC1pi006           
   false,  // kNuisEffFHCnumuCC1pi007           
   false,  // kNuisEffFHCnumuCC1pi008           
   false,  // kNuisEffFHCnumuCC1pi009           
   false,  // kNuisEffFHCnumuCC1pic1pi001       
   false,  // kNuisEffFHCnumuCC1pic1pi002       
   false,  // kNuisEffFHCnumuCC1pic1pi003       
   false,  // kNuisEffFHCnumuCC1pic1pi004       
   false,  // kNuisEffFHCnumuCC1pic1pi005       
   false,  // kNuisEffFHCnumuCC1pic1pi006       
   false,  // kNuisEffFHCnumuCC1pic1pi007       
   false,  // kNuisEffFHCnumuCC1pic1pi008       
   false,  // kNuisEffFHCnumuCC1pic1pi009       
   false,  // kNuisEffFHCnumuCCother01          
   false,  // kNuisEffFHCnumuCCother02          
   false,  // kNuisEffFHCnumuCCother03          
   false,  // kNuisEffFHCnumuCCother04          
   false,  // kNuisEffFHCnumuCCother05          
   false,  // kNuisEffFHCnumuCCother06          
   false,  // kNuisEffFHCnumuCCother07          
   false,  // kNuisEffFHCnumuCCother08          
   false,  // kNuisEffFHCnumuCCother09          
   false,  // kNuisEffFHCnumuCCother10          
   false,  // kNuisEffFHCnumuCCother11          
   false,  // kNuisEffFHCnumuCCWS0pi01          
   false,  // kNuisEffFHCnumuCCWS0pi02          
   false,  // kNuisEffFHCnumuCCWS0pi03          
   false,  // kNuisEffFHCnumuCCWS0pi04          
   false,  // kNuisEffFHCnumuCCWS0pi05          
   false,  // kNuisEffFHCnumuCCWS1pic01         
   false,  // kNuisEffFHCnumuCCWS1pic02         
   false,  // kNuisEffFHCnumuCCWS1pic03         
   false,  // kNuisEffFHCnumuCCWS1pic04         
   false,  // kNuisEffFHCnumuCCWS1pic05         
   false,  // kNuisEffFHCnumuCCWS1pic06         
   false,  // kNuisEffFHCnumuCCWS1pic07         
   false,  // kNuisEffFHCnumuCCWS1pic08         
   false,  // kNuisEffFHCnumuCCWS1piz01         
   false,  // kNuisEffFHCnumuCCWS1piz02         
   false,  // kNuisEffFHCnumuCCWS1piz03         
   false,  // kNuisEffFHCnumuCCWSother01        
   false,  // kNuisEffFHCnueCC0pi01             
   false,  // kNuisEffFHCnueCC0pi02             
   false,  // kNuisEffFHCnueCC0pi03             
   false,  // kNuisEffFHCnueCC0pi04             
   false,  // kNuisEffFHCnueCC0pi05             
   false,  // kNuisEffFHCnueCC0pi06             
   false,  // kNuisEffFHCnueCC0pi07             
   false,  // kNuisEffFHCnueCC0pi08             
   false,  // kNuisEffFHCnueCC0pi09             
   false,  // kNuisEffFHCnueCC1pic01            
   false,  // kNuisEffFHCnueCC1pic02            
   false,  // kNuisEffFHCnueCC1pic03            
   false,  // kNuisEffFHCnueCC1pic04            
   false,  // kNuisEffFHCnueCC1pic05            
   false,  // kNuisEffFHCnueCC1pic06            
   false,  // kNuisEffFHCnueCC1pic07            
   false,  // kNuisEffFHCnueCC1pic08            
   false,  // kNuisEffFHCnueCC1pic09            
   false,  // kNuisEffFHCnueCC1piz01            
   false,  // kNuisEffFHCnueCC1piz02            
   false,  // kNuisEffFHCnueCC1piz03            
   false,  // kNuisEffFHCnueCC1piz04            
   false,  // kNuisEffFHCnueCC1piz05            
   false,  // kNuisEffFHCnueCC1piz06            
   false,  // kNuisEffFHCnueCC1piz07            
   false,  // kNuisEffFHCnueCC1piz08            
   false,  // kNuisEffFHCnueCC1piz09            
   false,  // kNuisEffFHCnueCCother01           
   false,  // kNuisEffFHCnueCCother02           
   false,  // kNuisEffFHCnueCCother03           
   false,  // kNuisEffFHCnueCCother04           
   false,  // kNuisEffFHCnueCCother05           
   false,  // kNuisEffFHCnueCCother06           
   false,  // kNuisEffFHCnueCCother07           
   false,  // kNuisEffFHCnueCCother08           
   false,  // kNuisEffFHCnueCCother09           
   false,  // kNuisEffFHCnueCCother10           
   false,  // kNuisEffFHCnueCCother11           
   false,  // kNuisEffFHCnueCCWS01              
   false,  // kNuisEffFHCnueCCWS02              
   false,  // kNuisEffFHCNC0pi01                
   false,  // kNuisEffFHCNC0pi02                
   false,  // kNuisEffFHCNC0pi03                
   false,  // kNuisEffFHCNC1pic01               
   false,  // kNuisEffFHCNC1pic02               
   false,  // kNuisEffFHCNC1pic03               
   false,  // kNuisEffFHCNC1piz01               
   false,  // kNuisEffFHCNC1piz02               
   false,  // kNuisEffFHCNC1piz03               
   false,  // kNuisEffFHCNCother01              
   false,  // kNuisEffFHCNCother02              
   false,  // kNuisEffFHCNCother03              
   false,  // kNuisEffFHCNeutrinoElec           
   false,  // kNuisEffFHCIMD                    
   false,  // kNuisEffRHCnumuCC0pi1trk01        
   false,  // kNuisEffRHCnumuCC0pi1trk02        
   false,  // kNuisEffRHCnumuCC0pi1trk03        
   false,  // kNuisEffRHCnumuCC0pi1trk04        
   false,  // kNuisEffRHCnumuCC0pi1trk05        
   false,  // kNuisEffRHCnumuCC0pi1trk06        
   false,  // kNuisEffRHCnumuCC0pi1trk07        
   false,  // kNuisEffRHCnumuCC0pi1trk08        
   false,  // kNuisEffRHCnumuCC0pi1trk09        
   false,  // kNuisEffRHCnumuCC0pi2trk01        
   false,  // kNuisEffRHCnumuCC0pi2trk02        
   false,  // kNuisEffRHCnumuCC0pi2trk03        
   false,  // kNuisEffRHCnumuCC0pi2trk04        
   false,  // kNuisEffRHCnumuCC0pi2trk05        
   false,  // kNuisEffRHCnumuCC0pi2trk06        
   false,  // kNuisEffRHCnumuCC0pi2trk07        
   false,  // kNuisEffRHCnumuCC0pi2trk08        
   false,  // kNuisEffRHCnumuCC0pi2trk09        
   false,  // kNuisEffRHCnumuCC0piNtrk01        
   false,  // kNuisEffRHCnumuCC0piNtrk02        
   false,  // kNuisEffRHCnumuCC0piNtrk03        
   false,  // kNuisEffRHCnumuCC0piNtrk04        
   false,  // kNuisEffRHCnumuCC0piNtrk05        
   false,  // kNuisEffRHCnumuCC0piNtrk06        
   false,  // kNuisEffRHCnumuCC0piNtrk07        
   false,  // kNuisEffRHCnumuCC0piNtrk08        
   false,  // kNuisEffRHCnumuCC0piNtrk09        
   false,  // kNuisEffRHCnumuCC0piNtrk10        
   false,  // kNuisEffRHCnumuCC0piNtrk11        
   false,  // kNuisEffRHCnumuCC0piNtrk12        
   false,  // kNuisEffRHCnumuCC0piNtrk13        
   false,  // kNuisEffRHCnumuCC0piNtrk14        
   false,  // kNuisEffRHCnumuCC0piNtrk15        
   false,  // kNuisEffRHCnumuCC1pi3trkDelta01   
   false,  // kNuisEffRHCnumuCC1pi3trkDelta02   
   false,  // kNuisEffRHCnumuCC1pi3trkDelta03   
   false,  // kNuisEffRHCnumuCC1pi3trkDelta04   
   false,  // kNuisEffRHCnumuCC1pi3trkDelta05   
   false,  // kNuisEffRHCnumuCC1pi3trkDelta06   
   false,  // kNuisEffRHCnumuCC1pi3trkDelta07   
   false,  // kNuisEffRHCnumuCC1pi3trkDelta08   
   false,  // kNuisEffRHCnumuCC1pi3trkDelta09   
   false,  // kNuisEffRHCnumuCC1pi3trkDelta10   
   false,  // kNuisEffRHCnumuCC1pi3trkDelta11   
   false,  // kNuisEffRHCnumuCC1pi3trkDelta12   
   false,  // kNuisEffRHCnumuCC1pi3trkDelta13   
   false,  // kNuisEffRHCnumuCC1pi3trkDelta14   
   false,  // kNuisEffRHCnumuCC1pi3trkDelta15   
   false,  // kNuisEffRHCnumuCC1pic01           
   false,  // kNuisEffRHCnumuCC1pic02           
   false,  // kNuisEffRHCnumuCC1pic03           
   false,  // kNuisEffRHCnumuCC1pic04           
   false,  // kNuisEffRHCnumuCC1pic05           
   false,  // kNuisEffRHCnumuCC1pic06           
   false,  // kNuisEffRHCnumuCC1pic07           
   false,  // kNuisEffRHCnumuCC1pic08           
   false,  // kNuisEffRHCnumuCC1pic09           
   false,  // kNuisEffRHCnumuCC1pi001           
   false,  // kNuisEffRHCnumuCC1pi002           
   false,  // kNuisEffRHCnumuCC1pi003           
   false,  // kNuisEffRHCnumuCC1pi004           
   false,  // kNuisEffRHCnumuCC1pi005           
   false,  // kNuisEffRHCnumuCC1pi006           
   false,  // kNuisEffRHCnumuCC1pi007           
   false,  // kNuisEffRHCnumuCC1pi008           
   false,  // kNuisEffRHCnumuCC1pi009           
   false,  // kNuisEffRHCnumuCC1pic1pi001       
   false,  // kNuisEffRHCnumuCC1pic1pi002       
   false,  // kNuisEffRHCnumuCC1pic1pi003       
   false,  // kNuisEffRHCnumuCC1pic1pi004       
   false,  // kNuisEffRHCnumuCC1pic1pi005       
   false,  // kNuisEffRHCnumuCC1pic1pi006       
   false,  // kNuisEffRHCnumuCC1pic1pi007       
   false,  // kNuisEffRHCnumuCC1pic1pi008       
   false,  // kNuisEffRHCnumuCC1pic1pi009       
   false,  // kNuisEffRHCnumuCCother01          
   false,  // kNuisEffRHCnumuCCother02          
   false,  // kNuisEffRHCnumuCCother03          
   false,  // kNuisEffRHCnumuCCother04          
   false,  // kNuisEffRHCnumuCCother05          
   false,  // kNuisEffRHCnumuCCother06          
   false,  // kNuisEffRHCnumuCCother07          
   false,  // kNuisEffRHCnumuCCother08          
   false,  // kNuisEffRHCnumuCCother09          
   false,  // kNuisEffRHCnumuCCother10          
   false,  // kNuisEffRHCnumuCCother11          
   false,  // kNuisEffRHCnumuCCWS0pi01          
   false,  // kNuisEffRHCnumuCCWS0pi02          
   false,  // kNuisEffRHCnumuCCWS0pi03          
   false,  // kNuisEffRHCnumuCCWS0pi04          
   false,  // kNuisEffRHCnumuCCWS0pi05          
   false,  // kNuisEffRHCnumuCCWS1pic01         
   false,  // kNuisEffRHCnumuCCWS1pic02         
   false,  // kNuisEffRHCnumuCCWS1pic03         
   false,  // kNuisEffRHCnumuCCWS1pic04         
   false,  // kNuisEffRHCnumuCCWS1pic05         
   false,  // kNuisEffRHCnumuCCWS1pic06         
   false,  // kNuisEffRHCnumuCCWS1pic07         
   false,  // kNuisEffRHCnumuCCWS1pic08         
   false,  // kNuisEffRHCnumuCCWS1piz01         
   false,  // kNuisEffRHCnumuCCWS1piz02         
   false,  // kNuisEffRHCnumuCCWS1piz03         
   false,  // kNuisEffRHCnumuCCWSother01        
   false,  // kNuisEffRHCnueCC0pi01             
   false,  // kNuisEffRHCnueCC0pi02             
   false,  // kNuisEffRHCnueCC0pi03             
   false,  // kNuisEffRHCnueCC0pi04             
   false,  // kNuisEffRHCnueCC0pi05             
   false,  // kNuisEffRHCnueCC0pi06             
   false,  // kNuisEffRHCnueCC0pi07             
   false,  // kNuisEffRHCnueCC0pi08             
   false,  // kNuisEffRHCnueCC0pi09             
   false,  // kNuisEffRHCnueCC1pic01            
   false,  // kNuisEffRHCnueCC1pic02            
   false,  // kNuisEffRHCnueCC1pic03            
   false,  // kNuisEffRHCnueCC1pic04            
   false,  // kNuisEffRHCnueCC1pic05            
   false,  // kNuisEffRHCnueCC1pic06            
   false,  // kNuisEffRHCnueCC1pic07            
   false,  // kNuisEffRHCnueCC1pic08            
   false,  // kNuisEffRHCnueCC1pic09            
   false,  // kNuisEffRHCnueCC1piz01            
   false,  // kNuisEffRHCnueCC1piz02            
   false,  // kNuisEffRHCnueCC1piz03            
   false,  // kNuisEffRHCnueCC1piz04            
   false,  // kNuisEffRHCnueCC1piz05            
   false,  // kNuisEffRHCnueCC1piz06            
   false,  // kNuisEffRHCnueCC1piz07            
   false,  // kNuisEffRHCnueCC1piz08            
   false,  // kNuisEffRHCnueCC1piz09            
   false,  // kNuisEffRHCnueCCother01           
   false,  // kNuisEffRHCnueCCother02           
   false,  // kNuisEffRHCnueCCother03           
   false,  // kNuisEffRHCnueCCother04           
   false,  // kNuisEffRHCnueCCother05           
   false,  // kNuisEffRHCnueCCother06           
   false,  // kNuisEffRHCnueCCother07           
   false,  // kNuisEffRHCnueCCother08           
   false,  // kNuisEffRHCnueCCother09           
   false,  // kNuisEffRHCnueCCother10           
   false,  // kNuisEffRHCnueCCother11           
   false,  // kNuisEffRHCnueCCWS01              
   false,  // kNuisEffRHCnueCCWS02              
   false,  // kNuisEffRHCNC0pi01                
   false,  // kNuisEffRHCNC0pi02                
   false,  // kNuisEffRHCNC0pi03                
   false,  // kNuisEffRHCNC1pic01               
   false,  // kNuisEffRHCNC1pic02               
   false,  // kNuisEffRHCNC1pic03               
   false,  // kNuisEffRHCNC1piz01               
   false,  // kNuisEffRHCNC1piz02               
   false,  // kNuisEffRHCNC1piz03               
   false,  // kNuisEffRHCNCother01              
   false,  // kNuisEffRHCNCother02              
   false,  // kNuisEffRHCNCother03              
   false,  // kNuisEffRHCNeutrinoElec           
   false,  // kNuisEffRHCIMD                    
  // Far detector systematics
   false,  // kNuisEffFDNuMuCCHigh
   false,  // kNuisEffFDNuMuCCLow
   false,  // kNuisEffFDNuECCHigh
   false,   // kNuisEffFDNuECCLow
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
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0pi1trk01        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0pi1trk02        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0pi1trk03        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0pi1trk04        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0pi1trk05        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0pi1trk06        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0pi1trk07        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0pi1trk08        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0pi1trk09        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0pi2trk01        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0pi2trk02        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0pi2trk03        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0pi2trk04        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0pi2trk05        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0pi2trk06        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0pi2trk07        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0pi2trk08        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0pi2trk09        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0piNtrk01        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0piNtrk02        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0piNtrk03        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0piNtrk04        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0piNtrk05        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0piNtrk06        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0piNtrk07        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0piNtrk08        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0piNtrk09        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0piNtrk10        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0piNtrk11        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0piNtrk12        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0piNtrk13        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0piNtrk14        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC0piNtrk15        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi3trkDelta01   
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi3trkDelta02   
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi3trkDelta03   
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi3trkDelta04   
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi3trkDelta05   
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi3trkDelta06   
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi3trkDelta07   
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi3trkDelta08   
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi3trkDelta09   
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi3trkDelta10   
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi3trkDelta11   
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi3trkDelta12   
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi3trkDelta13   
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi3trkDelta14   
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi3trkDelta15   
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pic01           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pic02           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pic03           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pic04           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pic05           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pic06           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pic07           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pic08           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pic09           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi001           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi002           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi003           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi004           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi005           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi006           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi007           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi008           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pi009           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pic1pi001       
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pic1pi002       
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pic1pi003       
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pic1pi004       
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pic1pi005       
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pic1pi006       
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pic1pi007       
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pic1pi008       
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCC1pic1pi009       
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCother01          
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCother02          
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCother03          
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCother04          
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCother05          
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCother06          
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCother07          
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCother08          
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCother09          
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCother10          
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCother11          
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCWS0pi01          
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCWS0pi02          
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCWS0pi03          
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCWS0pi04          
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCWS0pi05          
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCWS1pic01         
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCWS1pic02         
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCWS1pic03         
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCWS1pic04         
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCWS1pic05         
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCWS1pic06         
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCWS1pic07         
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCWS1pic08         
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCWS1piz01         
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCWS1piz02         
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCWS1piz03         
   {  0.0 , kEtrueMax},  // kNuisEffFHCnumuCCWSother01        
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC0pi01             
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC0pi02             
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC0pi03             
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC0pi04             
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC0pi05             
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC0pi06             
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC0pi07             
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC0pi08             
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC0pi09             
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC1pic01            
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC1pic02            
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC1pic03            
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC1pic04            
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC1pic05            
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC1pic06            
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC1pic07            
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC1pic08            
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC1pic09            
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC1piz01            
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC1piz02            
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC1piz03            
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC1piz04            
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC1piz05            
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC1piz06            
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC1piz07            
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC1piz08            
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCC1piz09            
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCCother01           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCCother02           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCCother03           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCCother04           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCCother05           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCCother06           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCCother07           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCCother08           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCCother09           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCCother10           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCCother11           
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCCWS01              
   {  0.0 , kEtrueMax},  // kNuisEffFHCnueCCWS02              
   {  0.0 , kEtrueMax},  // kNuisEffFHCNC0pi01                
   {  0.0 , kEtrueMax},  // kNuisEffFHCNC0pi02                
   {  0.0 , kEtrueMax},  // kNuisEffFHCNC0pi03                
   {  0.0 , kEtrueMax},  // kNuisEffFHCNC1pic01               
   {  0.0 , kEtrueMax},  // kNuisEffFHCNC1pic02               
   {  0.0 , kEtrueMax},  // kNuisEffFHCNC1pic03               
   {  0.0 , kEtrueMax},  // kNuisEffFHCNC1piz01               
   {  0.0 , kEtrueMax},  // kNuisEffFHCNC1piz02               
   {  0.0 , kEtrueMax},  // kNuisEffFHCNC1piz03               
   {  0.0 , kEtrueMax},  // kNuisEffFHCNCother01              
   {  0.0 , kEtrueMax},  // kNuisEffFHCNCother02              
   {  0.0 , kEtrueMax},  // kNuisEffFHCNCother03              
   {  0.0 , kEtrueMax},  // kNuisEffFHCNeutrinoElec           
   {  0.0 , kEtrueMax},  // kNuisEffFHCIMD                    
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0pi1trk01        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0pi1trk02        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0pi1trk03        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0pi1trk04        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0pi1trk05        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0pi1trk06        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0pi1trk07        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0pi1trk08        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0pi1trk09        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0pi2trk01        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0pi2trk02        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0pi2trk03        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0pi2trk04        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0pi2trk05        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0pi2trk06        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0pi2trk07        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0pi2trk08        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0pi2trk09        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0piNtrk01        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0piNtrk02        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0piNtrk03        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0piNtrk04        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0piNtrk05        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0piNtrk06        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0piNtrk07        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0piNtrk08        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0piNtrk09        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0piNtrk10        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0piNtrk11        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0piNtrk12        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0piNtrk13        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0piNtrk14        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC0piNtrk15        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi3trkDelta01   
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi3trkDelta02   
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi3trkDelta03   
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi3trkDelta04   
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi3trkDelta05   
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi3trkDelta06   
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi3trkDelta07   
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi3trkDelta08   
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi3trkDelta09   
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi3trkDelta10   
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi3trkDelta11   
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi3trkDelta12   
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi3trkDelta13   
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi3trkDelta14   
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi3trkDelta15   
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pic01           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pic02           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pic03           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pic04           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pic05           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pic06           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pic07           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pic08           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pic09           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi001           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi002           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi003           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi004           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi005           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi006           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi007           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi008           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pi009           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pic1pi001       
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pic1pi002       
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pic1pi003       
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pic1pi004       
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pic1pi005       
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pic1pi006       
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pic1pi007       
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pic1pi008       
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCC1pic1pi009       
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCother01          
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCother02          
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCother03          
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCother04          
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCother05          
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCother06          
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCother07          
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCother08          
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCother09          
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCother10          
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCother11          
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCWS0pi01          
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCWS0pi02          
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCWS0pi03          
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCWS0pi04          
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCWS0pi05          
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCWS1pic01         
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCWS1pic02         
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCWS1pic03         
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCWS1pic04         
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCWS1pic05         
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCWS1pic06         
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCWS1pic07         
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCWS1pic08         
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCWS1piz01         
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCWS1piz02         
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCWS1piz03         
   {  0.0 , kEtrueMax},  // kNuisEffRHCnumuCCWSother01        
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC0pi01             
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC0pi02             
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC0pi03             
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC0pi04             
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC0pi05             
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC0pi06             
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC0pi07             
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC0pi08             
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC0pi09             
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC1pic01            
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC1pic02            
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC1pic03            
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC1pic04            
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC1pic05            
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC1pic06            
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC1pic07            
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC1pic08            
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC1pic09            
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC1piz01            
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC1piz02            
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC1piz03            
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC1piz04            
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC1piz05            
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC1piz06            
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC1piz07            
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC1piz08            
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCC1piz09            
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCCother01           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCCother02           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCCother03           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCCother04           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCCother05           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCCother06           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCCother07           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCCother08           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCCother09           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCCother10           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCCother11           
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCCWS01              
   {  0.0 , kEtrueMax},  // kNuisEffRHCnueCCWS02              
   {  0.0 , kEtrueMax},  // kNuisEffRHCNC0pi01                
   {  0.0 , kEtrueMax},  // kNuisEffRHCNC0pi02                
   {  0.0 , kEtrueMax},  // kNuisEffRHCNC0pi03                
   {  0.0 , kEtrueMax},  // kNuisEffRHCNC1pic01               
   {  0.0 , kEtrueMax},  // kNuisEffRHCNC1pic02               
   {  0.0 , kEtrueMax},  // kNuisEffRHCNC1pic03               
   {  0.0 , kEtrueMax},  // kNuisEffRHCNC1piz01               
   {  0.0 , kEtrueMax},  // kNuisEffRHCNC1piz02               
   {  0.0 , kEtrueMax},  // kNuisEffRHCNC1piz03               
   {  0.0 , kEtrueMax},  // kNuisEffRHCNCother01              
   {  0.0 , kEtrueMax},  // kNuisEffRHCNCother02              
   {  0.0 , kEtrueMax},  // kNuisEffRHCNCother03              
   {  0.0 , kEtrueMax},  // kNuisEffRHCNeutrinoElec           
   {  0.0 , kEtrueMax},  // kNuisEffRHCIMD                    
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
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0pi1trk01        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0pi1trk02        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0pi1trk03        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0pi1trk04        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0pi1trk05        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0pi1trk06        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0pi1trk07        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0pi1trk08        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0pi1trk09        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0pi2trk01        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0pi2trk02        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0pi2trk03        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0pi2trk04        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0pi2trk05        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0pi2trk06        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0pi2trk07        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0pi2trk08        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0pi2trk09        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0piNtrk01        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0piNtrk02        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0piNtrk03        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0piNtrk04        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0piNtrk05        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0piNtrk06        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0piNtrk07        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0piNtrk08        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0piNtrk09        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0piNtrk10        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0piNtrk11        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0piNtrk12        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0piNtrk13        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0piNtrk14        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC0piNtrk15        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi3trkDelta01   
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi3trkDelta02   
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi3trkDelta03   
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi3trkDelta04   
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi3trkDelta05   
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi3trkDelta06   
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi3trkDelta07   
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi3trkDelta08   
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi3trkDelta09   
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi3trkDelta10   
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi3trkDelta11   
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi3trkDelta12   
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi3trkDelta13   
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi3trkDelta14   
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi3trkDelta15   
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pic01           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pic02           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pic03           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pic04           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pic05           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pic06           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pic07           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pic08           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pic09           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi001           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi002           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi003           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi004           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi005           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi006           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi007           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi008           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pi009           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pic1pi001       
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pic1pi002       
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pic1pi003       
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pic1pi004       
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pic1pi005       
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pic1pi006       
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pic1pi007       
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pic1pi008       
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCC1pic1pi009       
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCother01          
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCother02          
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCother03          
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCother04          
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCother05          
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCother06          
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCother07          
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCother08          
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCother09          
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCother10          
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCother11          
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCWS0pi01          
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCWS0pi02          
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCWS0pi03          
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCWS0pi04          
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCWS0pi05          
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCWS1pic01         
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCWS1pic02         
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCWS1pic03         
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCWS1pic04         
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCWS1pic05         
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCWS1pic06         
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCWS1pic07         
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCWS1pic08         
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCWS1piz01         
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCWS1piz02         
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCWS1piz03         
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnumuCCWSother01        
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC0pi01             
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC0pi02             
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC0pi03             
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC0pi04             
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC0pi05             
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC0pi06             
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC0pi07             
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC0pi08             
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC0pi09             
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC1pic01            
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC1pic02            
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC1pic03            
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC1pic04            
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC1pic05            
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC1pic06            
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC1pic07            
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC1pic08            
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC1pic09            
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC1piz01            
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC1piz02            
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC1piz03            
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC1piz04            
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC1piz05            
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC1piz06            
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC1piz07            
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC1piz08            
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCC1piz09            
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCCother01           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCCother02           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCCother03           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCCother04           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCCother05           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCCother06           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCCother07           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCCother08           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCCother09           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCCother10           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCCother11           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCCWS01              
   { 0.0  , kQ2trueMax},  // kNuisEffFHCnueCCWS02              
   { 0.0  , kQ2trueMax},  // kNuisEffFHCNC0pi01                
   { 0.0  , kQ2trueMax},  // kNuisEffFHCNC0pi02                
   { 0.0  , kQ2trueMax},  // kNuisEffFHCNC0pi03                
   { 0.0  , kQ2trueMax},  // kNuisEffFHCNC1pic01               
   { 0.0  , kQ2trueMax},  // kNuisEffFHCNC1pic02               
   { 0.0  , kQ2trueMax},  // kNuisEffFHCNC1pic03               
   { 0.0  , kQ2trueMax},  // kNuisEffFHCNC1piz01               
   { 0.0  , kQ2trueMax},  // kNuisEffFHCNC1piz02               
   { 0.0  , kQ2trueMax},  // kNuisEffFHCNC1piz03               
   { 0.0  , kQ2trueMax},  // kNuisEffFHCNCother01              
   { 0.0  , kQ2trueMax},  // kNuisEffFHCNCother02              
   { 0.0  , kQ2trueMax},  // kNuisEffFHCNCother03              
   { 0.0  , kQ2trueMax},  // kNuisEffFHCNeutrinoElec           
   { 0.0  , kQ2trueMax},  // kNuisEffFHCIMD                    
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0pi1trk01        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0pi1trk02        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0pi1trk03        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0pi1trk04        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0pi1trk05        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0pi1trk06        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0pi1trk07        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0pi1trk08        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0pi1trk09        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0pi2trk01        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0pi2trk02        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0pi2trk03        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0pi2trk04        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0pi2trk05        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0pi2trk06        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0pi2trk07        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0pi2trk08        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0pi2trk09        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0piNtrk01        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0piNtrk02        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0piNtrk03        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0piNtrk04        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0piNtrk05        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0piNtrk06        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0piNtrk07        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0piNtrk08        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0piNtrk09        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0piNtrk10        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0piNtrk11        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0piNtrk12        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0piNtrk13        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0piNtrk14        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC0piNtrk15        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi3trkDelta01   
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi3trkDelta02   
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi3trkDelta03   
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi3trkDelta04   
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi3trkDelta05   
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi3trkDelta06   
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi3trkDelta07   
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi3trkDelta08   
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi3trkDelta09   
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi3trkDelta10   
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi3trkDelta11   
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi3trkDelta12   
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi3trkDelta13   
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi3trkDelta14   
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi3trkDelta15   
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pic01           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pic02           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pic03           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pic04           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pic05           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pic06           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pic07           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pic08           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pic09           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi001           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi002           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi003           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi004           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi005           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi006           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi007           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi008           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pi009           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pic1pi001       
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pic1pi002       
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pic1pi003       
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pic1pi004       
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pic1pi005       
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pic1pi006       
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pic1pi007       
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pic1pi008       
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCC1pic1pi009       
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCother01          
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCother02          
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCother03          
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCother04          
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCother05          
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCother06          
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCother07          
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCother08          
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCother09          
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCother10          
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCother11          
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCWS0pi01          
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCWS0pi02          
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCWS0pi03          
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCWS0pi04          
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCWS0pi05          
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCWS1pic01         
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCWS1pic02         
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCWS1pic03         
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCWS1pic04         
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCWS1pic05         
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCWS1pic06         
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCWS1pic07         
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCWS1pic08         
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCWS1piz01         
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCWS1piz02         
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCWS1piz03         
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnumuCCWSother01        
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC0pi01             
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC0pi02             
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC0pi03             
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC0pi04             
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC0pi05             
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC0pi06             
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC0pi07             
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC0pi08             
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC0pi09             
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC1pic01            
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC1pic02            
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC1pic03            
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC1pic04            
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC1pic05            
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC1pic06            
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC1pic07            
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC1pic08            
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC1pic09            
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC1piz01            
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC1piz02            
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC1piz03            
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC1piz04            
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC1piz05            
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC1piz06            
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC1piz07            
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC1piz08            
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCC1piz09            
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCCother01           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCCother02           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCCother03           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCCother04           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCCother05           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCCother06           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCCother07           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCCother08           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCCother09           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCCother10           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCCother11           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCCWS01              
   { 0.0  , kQ2trueMax},  // kNuisEffRHCnueCCWS02              
   { 0.0  , kQ2trueMax},  // kNuisEffRHCNC0pi01                
   { 0.0  , kQ2trueMax},  // kNuisEffRHCNC0pi02                
   { 0.0  , kQ2trueMax},  // kNuisEffRHCNC0pi03                
   { 0.0  , kQ2trueMax},  // kNuisEffRHCNC1pic01               
   { 0.0  , kQ2trueMax},  // kNuisEffRHCNC1pic02               
   { 0.0  , kQ2trueMax},  // kNuisEffRHCNC1pic03               
   { 0.0  , kQ2trueMax},  // kNuisEffRHCNC1piz01               
   { 0.0  , kQ2trueMax},  // kNuisEffRHCNC1piz02               
   { 0.0  , kQ2trueMax},  // kNuisEffRHCNC1piz03               
   { 0.0  , kQ2trueMax},  // kNuisEffRHCNCother01              
   { 0.0  , kQ2trueMax},  // kNuisEffRHCNCother02              
   { 0.0  , kQ2trueMax},  // kNuisEffRHCNCother03              
   { 0.0  , kQ2trueMax},  // kNuisEffRHCNeutrinoElec           
   { 0.0  , kQ2trueMax},  // kNuisEffRHCIMD                    
  // Far detector systematics
   {  0.0, kQ2trueMax},   // kNuisEffFDNuMuCCHigh
   {  0.0, kQ2trueMax},   // kNuisEffFDNuMuCCLow
   {  0.0, kQ2trueMax},   // kNuisEffFDNuECCHigh
   {  0.0, kQ2trueMax}    // kNuisEffFDNuECCLow
};


#endif // valor_dune_fit_param_true_ranges_h
