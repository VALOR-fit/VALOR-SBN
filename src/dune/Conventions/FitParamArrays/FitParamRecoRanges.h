#ifndef valor_dune_fit_param_reco_ranges_h
#define valor_dune_fit_param_reco_ranges_h

//
// ...........................................................................
// The following arrays specify the Ereco dependence of each systematic
// ...........................................................................
//

// Has true kinematic dependence
static const bool kFitParamRecoKinematicDependence[kNFitParams] =
{
  //oscillation parameters
  false,
  false,
  false,
  false,
  false,
  false,
  // FHC flux
  false,   // kNuisFHCNuMuFlux00
  false,   // kNuisFHCNuMuFlux01
  false,   // kNuisFHCNuMuFlux02
  false,   // kNuisFHCNuMuFlux03
  false,   // kNuisFHCNuMuFlux04
  false,   // kNuisFHCNuMuFlux05
  false,   // kNuisFHCNuMuFlux06
  false,   // kNuisFHCNuMuFlux07
  false,   // kNuisFHCNuMuFlux08
  false,   // kNuisFHCNuMuFlux09
  false,   // kNuisFHCNuMuFlux10
  false,   // kNuisFHCNuMuFlux11
  false,   // kNuisFHCNuMuFlux12
  false,   // kNuisFHCNuMuFlux13
  false,   // kNuisFHCNuMuFlux14
  false,   // kNuisFHCNuMuFlux15
  false,   // kNuisFHCNuMuFlux16
  false,   // kNuisFHCNuMuFlux17
  false,   // kNuisFHCNuMuFlux18
  false,   // kNuisFHCNuMuBarFlux00
  false,   // kNuisFHCNuMuBarFlux01
  false,   // kNuisFHCNuMuBarFlux02
  false,   // kNuisFHCNuMuBarFlux03
  false,   // kNuisFHCNuMuBarFlux04
  false,   // kNuisFHCNuMuBarFlux05
  false,   // kNuisFHCNuMuBarFlux06
  false,   // kNuisFHCNuMuBarFlux07
  false,   // kNuisFHCNuMuBarFlux08
  false,   // kNuisFHCNuMuBarFlux09
  false,   // kNuisFHCNuMuBarFlux10
  false,   // kNuisFHCNuMuBarFlux11
  false,   // kNuisFHCNuMuBarFlux12
  false,   // kNuisFHCNuMuBarFlux13
  false,   // kNuisFHCNuMuBarFlux14
  false,   // kNuisFHCNuMuBarFlux15
  false,   // kNuisFHCNuMuBarFlux16
  false,   // kNuisFHCNuMuBarFlux17
  false,   // kNuisFHCNuMuBarFlux18
  false,   // kNuisFHCNuEFlux00
  false,   // kNuisFHCNuEFlux01
  false,   // kNuisFHCNuEFlux02
  false,   // kNuisFHCNuEFlux03
  false,   // kNuisFHCNuEFlux04
  false,   // kNuisFHCNuEFlux05
  false,   // kNuisFHCNuEFlux06
  false,   // kNuisFHCNuEBarFlux00
  false,   // kNuisFHCNuEBarFlux01
  false,   // kNuisFHCNuEBarFlux02
  false,   // kNuisFHCNuEBarFlux03
  false,   // kNuisFHCNuEBarFlux04
  false,   // kNuisFHCNuEBarFlux05
  false,   // kNuisFHCNuEBarFlux06
  // RHC flux
  false,   // kNuisRHCNuMuFlux00
  false,   // kNuisRHCNuMuFlux01
  false,   // kNuisRHCNuMuFlux02
  false,   // kNuisRHCNuMuFlux03
  false,   // kNuisRHCNuMuFlux04
  false,   // kNuisRHCNuMuFlux05
  false,   // kNuisRHCNuMuFlux06
  false,   // kNuisRHCNuMuFlux07
  false,   // kNuisRHCNuMuFlux08
  false,   // kNuisRHCNuMuFlux09
  false,   // kNuisRHCNuMuFlux10
  false,   // kNuisRHCNuMuFlux11
  false,   // kNuisRHCNuMuFlux12
  false,   // kNuisRHCNuMuFlux13
  false,   // kNuisRHCNuMuFlux14
  false,   // kNuisRHCNuMuFlux15
  false,   // kNuisRHCNuMuFlux16
  false,   // kNuisRHCNuMuFlux17
  false,   // kNuisRHCNuMuFlux18
  false,   // kNuisRHCNuMuBarFlux00
  false,   // kNuisRHCNuMuBarFlux01
  false,   // kNuisRHCNuMuBarFlux02
  false,   // kNuisRHCNuMuBarFlux03
  false,   // kNuisRHCNuMuBarFlux04
  false,   // kNuisRHCNuMuBarFlux05
  false,   // kNuisRHCNuMuBarFlux06
  false,   // kNuisRHCNuMuBarFlux07
  false,   // kNuisRHCNuMuBarFlux08
  false,   // kNuisRHCNuMuBarFlux09
  false,   // kNuisRHCNuMuBarFlux10
  false,   // kNuisRHCNuMuBarFlux11
  false,   // kNuisRHCNuMuBarFlux12
  false,   // kNuisRHCNuMuBarFlux13
  false,   // kNuisRHCNuMuBarFlux14
  false,   // kNuisRHCNuMuBarFlux15
  false,   // kNuisRHCNuMuBarFlux16
  false,   // kNuisRHCNuMuBarFlux17
  false,   // kNuisRHCNuMuBarFlux18
  false,   // kNuisRHCNuEFlux00
  false,   // kNuisRHCNuEFlux01
  false,   // kNuisRHCNuEFlux02
  false,   // kNuisRHCNuEFlux03
  false,   // kNuisRHCNuEFlux04
  false,   // kNuisRHCNuEFlux05
  false,   // kNuisRHCNuEFlux06
  false,   // kNuisRHCNuEBarFlux00
  false,   // kNuisRHCNuEBarFlux01
  false,   // kNuisRHCNuEBarFlux02
  false,   // kNuisRHCNuEBarFlux03
  false,   // kNuisRHCNuEBarFlux04
  false,   // kNuisRHCNuEBarFlux05
  false,   // kNuisRHCNuEBarFlux06
  // Far detector flux
  // FHC flux
  false,   // kNuisFHCNuMuFDFlux00
  false,   // kNuisFHCNuMuFDFlux01
  false,   // kNuisFHCNuMuFDFlux02
  false,   // kNuisFHCNuMuFDFlux03
  false,   // kNuisFHCNuMuFDFlux04
  false,   // kNuisFHCNuMuFDFlux05
  false,   // kNuisFHCNuMuFDFlux06
  false,   // kNuisFHCNuMuFDFlux07
  false,   // kNuisFHCNuMuFDFlux08
  false,   // kNuisFHCNuMuFDFlux09
  false,   // kNuisFHCNuMuFDFlux10
  false,   // kNuisFHCNuMuFDFlux11
  false,   // kNuisFHCNuMuFDFlux12
  false,   // kNuisFHCNuMuFDFlux13
  false,   // kNuisFHCNuMuFDFlux14
  false,   // kNuisFHCNuMuFDFlux15
  false,   // kNuisFHCNuMuFDFlux16
  false,   // kNuisFHCNuMuFDFlux17
  false,   // kNuisFHCNuMuFDFlux18
  false,   // kNuisFHCNuMuBarFDFlux00
  false,   // kNuisFHCNuMuBarFDFlux01
  false,   // kNuisFHCNuMuBarFDFlux02
  false,   // kNuisFHCNuMuBarFDFlux03
  false,   // kNuisFHCNuMuBarFDFlux04
  false,   // kNuisFHCNuMuBarFDFlux05
  false,   // kNuisFHCNuMuBarFDFlux06
  false,   // kNuisFHCNuMuBarFDFlux07
  false,   // kNuisFHCNuMuBarFDFlux08
  false,   // kNuisFHCNuMuBarFDFlux09
  false,   // kNuisFHCNuMuBarFDFlux10
  false,   // kNuisFHCNuMuBarFDFlux11
  false,   // kNuisFHCNuMuBarFDFlux12
  false,   // kNuisFHCNuMuBarFDFlux13
  false,   // kNuisFHCNuMuBarFDFlux14
  false,   // kNuisFHCNuMuBarFDFlux15
  false,   // kNuisFHCNuMuBarFDFlux16
  false,   // kNuisFHCNuMuBarFDFlux17
  false,   // kNuisFHCNuMuBarFDFlux18
  false,   // kNuisFHCNuEFDFlux00
  false,   // kNuisFHCNuEFDFlux01
  false,   // kNuisFHCNuEFDFlux02
  false,   // kNuisFHCNuEFDFlux03
  false,   // kNuisFHCNuEFDFlux04
  false,   // kNuisFHCNuEFDFlux05
  false,   // kNuisFHCNuEFDFlux06
  false,   // kNuisFHCNuEBarFDFlux00
  false,   // kNuisFHCNuEBarFDFlux01
  false,   // kNuisFHCNuEBarFDFlux02
  false,   // kNuisFHCNuEBarFDFlux03
  false,   // kNuisFHCNuEBarFDFlux04
  false,   // kNuisFHCNuEBarFDFlux05
  false,   // kNuisFHCNuEBarFDFlux06
  // RHC flux
  false,   // kNuisRHCNuMuFDFlux00
  false,   // kNuisRHCNuMuFDFlux01
  false,   // kNuisRHCNuMuFDFlux02
  false,   // kNuisRHCNuMuFDFlux03
  false,   // kNuisRHCNuMuFDFlux04
  false,   // kNuisRHCNuMuFDFlux05
  false,   // kNuisRHCNuMuFDFlux06
  false,   // kNuisRHCNuMuFDFlux07
  false,   // kNuisRHCNuMuFDFlux08
  false,   // kNuisRHCNuMuFDFlux09
  false,   // kNuisRHCNuMuFDFlux10
  false,   // kNuisRHCNuMuFDFlux11
  false,   // kNuisRHCNuMuFDFlux12
  false,   // kNuisRHCNuMuFDFlux13
  false,   // kNuisRHCNuMuFDFlux14
  false,   // kNuisRHCNuMuFDFlux15
  false,   // kNuisRHCNuMuFDFlux16
  false,   // kNuisRHCNuMuFDFlux17
  false,   // kNuisRHCNuMuFDFlux18
  false,   // kNuisRHCNuMuBarFDFlux00
  false,   // kNuisRHCNuMuBarFDFlux01
  false,   // kNuisRHCNuMuBarFDFlux02
  false,   // kNuisRHCNuMuBarFDFlux03
  false,   // kNuisRHCNuMuBarFDFlux04
  false,   // kNuisRHCNuMuBarFDFlux05
  false,   // kNuisRHCNuMuBarFDFlux06
  false,   // kNuisRHCNuMuBarFDFlux07
  false,   // kNuisRHCNuMuBarFDFlux08
  false,   // kNuisRHCNuMuBarFDFlux09
  false,   // kNuisRHCNuMuBarFDFlux10
  false,   // kNuisRHCNuMuBarFDFlux11
  false,   // kNuisRHCNuMuBarFDFlux12
  false,   // kNuisRHCNuMuBarFDFlux13
  false,   // kNuisRHCNuMuBarFDFlux14
  false,   // kNuisRHCNuMuBarFDFlux15
  false,   // kNuisRHCNuMuBarFDFlux16
  false,   // kNuisRHCNuMuBarFDFlux17
  false,   // kNuisRHCNuMuBarFDFlux18
  false,   // kNuisRHCNuEFDFlux00
  false,   // kNuisRHCNuEFDFlux01
  false,   // kNuisRHCNuEFDFlux02
  false,   // kNuisRHCNuEFDFlux03
  false,   // kNuisRHCNuEFDFlux04
  false,   // kNuisRHCNuEFDFlux05
  false,   // kNuisRHCNuEFDFlux06
  false,   // kNuisRHCNuEBarFDFlux00
  false,   // kNuisRHCNuEBarFDFlux01
  false,   // kNuisRHCNuEBarFDFlux02
  false,   // kNuisRHCNuEBarFDFlux03
  false,   // kNuisRHCNuEBarFDFlux04
  false,   // kNuisRHCNuEBarFDFlux05
  false,   // kNuisRHCNuEBarFDFlux06
    // Cross-sections
  false,  // kNuisIntNuCCQE1
  false,  // kNuisIntNuCCQE2
  false,  // kNuisIntNuCCQE3
  false,  // kNuisIntNuBarCCQE1
  false,  // kNuisIntNuBarCCQE2
  false,  // kNuisIntNuBarCCQE3
  false,  // kNuisIntNuCCMEC
  false,  // kNuisIntNuBarCCMEC
  false,  // kNuisIntNuCC1piz1
  false,  // kNuisIntNuCC1piz2
  false,  // kNuisIntNuCC1piz3
  false,  // kNuisIntNuCC1pic1
  false,  // kNuisIntNuCC1pic2
  false,  // kNuisIntNuCC1pic3
  false,  // kNuisIntNuBarCC1piz1
  false,  // kNuisIntNuBarCC1piz2
  false,  // kNuisIntNuBarCC1piz3
  false,  // kNuisIntNuBarCC1pic1
  false,  // kNuisIntNuBarCC1pic2
  false,  // kNuisIntNuBarCC1pic3
  false,  // kNuisIntNuCC2Pi
  false,  // kNuisIntNuBarCC2Pi
  false,  // kNuisIntNuDIS1
  false,  // kNuisIntNuDIS2
  false,  // kNuisIntNuDIS3
  false,  // kNuisIntNuBarDIS1
  false,  // kNuisIntNuBarDIS2
  false,  // kNuisIntNuBarDIS3
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
  true ,  // kNuisEffFHCnumuCC0pi1trk01        
  true ,  // kNuisEffFHCnumuCC0pi1trk02        
  true ,  // kNuisEffFHCnumuCC0pi1trk03        
  true ,  // kNuisEffFHCnumuCC0pi1trk04        
  true ,  // kNuisEffFHCnumuCC0pi1trk05        
  true ,  // kNuisEffFHCnumuCC0pi1trk06        
  true ,  // kNuisEffFHCnumuCC0pi1trk07        
  true ,  // kNuisEffFHCnumuCC0pi1trk08        
  true ,  // kNuisEffFHCnumuCC0pi1trk09        
  true ,  // kNuisEffFHCnumuCC0pi2trk01        
  true ,  // kNuisEffFHCnumuCC0pi2trk02        
  true ,  // kNuisEffFHCnumuCC0pi2trk03        
  true ,  // kNuisEffFHCnumuCC0pi2trk04        
  true ,  // kNuisEffFHCnumuCC0pi2trk05        
  true ,  // kNuisEffFHCnumuCC0pi2trk06        
  true ,  // kNuisEffFHCnumuCC0pi2trk07        
  true ,  // kNuisEffFHCnumuCC0pi2trk08        
  true ,  // kNuisEffFHCnumuCC0pi2trk09        
  true ,  // kNuisEffFHCnumuCC0piNtrk01        
  true ,  // kNuisEffFHCnumuCC0piNtrk02        
  true ,  // kNuisEffFHCnumuCC0piNtrk03        
  true ,  // kNuisEffFHCnumuCC0piNtrk04        
  true ,  // kNuisEffFHCnumuCC0piNtrk05        
  true ,  // kNuisEffFHCnumuCC0piNtrk06        
  true ,  // kNuisEffFHCnumuCC0piNtrk07        
  true ,  // kNuisEffFHCnumuCC0piNtrk08        
  true ,  // kNuisEffFHCnumuCC0piNtrk09        
  true ,  // kNuisEffFHCnumuCC0piNtrk10        
  true ,  // kNuisEffFHCnumuCC0piNtrk11        
  true ,  // kNuisEffFHCnumuCC0piNtrk12        
  true ,  // kNuisEffFHCnumuCC0piNtrk13        
  true ,  // kNuisEffFHCnumuCC0piNtrk14        
  true ,  // kNuisEffFHCnumuCC0piNtrk15        
  true ,  // kNuisEffFHCnumuCC1pi3trkDelta01   
  true ,  // kNuisEffFHCnumuCC1pi3trkDelta02   
  true ,  // kNuisEffFHCnumuCC1pi3trkDelta03   
  true ,  // kNuisEffFHCnumuCC1pi3trkDelta04   
  true ,  // kNuisEffFHCnumuCC1pi3trkDelta05   
  true ,  // kNuisEffFHCnumuCC1pi3trkDelta06   
  true ,  // kNuisEffFHCnumuCC1pi3trkDelta07   
  true ,  // kNuisEffFHCnumuCC1pi3trkDelta08   
  true ,  // kNuisEffFHCnumuCC1pi3trkDelta09   
  true ,  // kNuisEffFHCnumuCC1pi3trkDelta10   
  true ,  // kNuisEffFHCnumuCC1pi3trkDelta11   
  true ,  // kNuisEffFHCnumuCC1pi3trkDelta12   
  true ,  // kNuisEffFHCnumuCC1pi3trkDelta13   
  true ,  // kNuisEffFHCnumuCC1pi3trkDelta14   
  true ,  // kNuisEffFHCnumuCC1pi3trkDelta15   
  true ,  // kNuisEffFHCnumuCC1pic01           
  true ,  // kNuisEffFHCnumuCC1pic02           
  true ,  // kNuisEffFHCnumuCC1pic03           
  true ,  // kNuisEffFHCnumuCC1pic04           
  true ,  // kNuisEffFHCnumuCC1pic05           
  true ,  // kNuisEffFHCnumuCC1pic06           
  true ,  // kNuisEffFHCnumuCC1pic07           
  true ,  // kNuisEffFHCnumuCC1pic08           
  true ,  // kNuisEffFHCnumuCC1pic09           
  true ,  // kNuisEffFHCnumuCC1piz01           
  true ,  // kNuisEffFHCnumuCC1piz02           
  true ,  // kNuisEffFHCnumuCC1piz03           
  true ,  // kNuisEffFHCnumuCC1piz04           
  true ,  // kNuisEffFHCnumuCC1piz05           
  true ,  // kNuisEffFHCnumuCC1piz06           
  true ,  // kNuisEffFHCnumuCC1piz07           
  true ,  // kNuisEffFHCnumuCC1piz08           
  true ,  // kNuisEffFHCnumuCC1piz09           
  true ,  // kNuisEffFHCnumuCC1pic1piz01       
  true ,  // kNuisEffFHCnumuCC1pic1piz02       
  true ,  // kNuisEffFHCnumuCC1pic1piz03       
  true ,  // kNuisEffFHCnumuCC1pic1piz04       
  true ,  // kNuisEffFHCnumuCC1pic1piz05       
  true ,  // kNuisEffFHCnumuCC1pic1piz06       
  true ,  // kNuisEffFHCnumuCC1pic1piz07       
  true ,  // kNuisEffFHCnumuCC1pic1piz08       
  true ,  // kNuisEffFHCnumuCC1pic1piz09       
  true ,  // kNuisEffFHCnumuCCother01          
  true ,  // kNuisEffFHCnumuCCother02          
  true ,  // kNuisEffFHCnumuCCother03          
  true ,  // kNuisEffFHCnumuCCother04          
  true ,  // kNuisEffFHCnumuCCother05          
  true ,  // kNuisEffFHCnumuCCother06          
  true ,  // kNuisEffFHCnumuCCother07          
  true ,  // kNuisEffFHCnumuCCother08          
  true ,  // kNuisEffFHCnumuCCother09          
  true ,  // kNuisEffFHCnumuCCother10          
  true ,  // kNuisEffFHCnumuCCother11          
  true ,  // kNuisEffFHCnumuCCWS0pi01          
  true ,  // kNuisEffFHCnumuCCWS0pi02          
  true ,  // kNuisEffFHCnumuCCWS0pi03          
  true ,  // kNuisEffFHCnumuCCWS0pi04          
  true ,  // kNuisEffFHCnumuCCWS0pi05          
  true ,  // kNuisEffFHCnumuCCWS1pic01         
  true ,  // kNuisEffFHCnumuCCWS1pic02         
  true ,  // kNuisEffFHCnumuCCWS1pic03         
  true ,  // kNuisEffFHCnumuCCWS1pic04         
  true ,  // kNuisEffFHCnumuCCWS1pic05         
  true ,  // kNuisEffFHCnumuCCWS1pic06         
  true ,  // kNuisEffFHCnumuCCWS1pic07         
  true ,  // kNuisEffFHCnumuCCWS1pic08         
  true ,  // kNuisEffFHCnumuCCWS1piz01         
  true ,  // kNuisEffFHCnumuCCWS1piz02         
  true ,  // kNuisEffFHCnumuCCWS1piz03         
  true ,  // kNuisEffFHCnumuCCWSother01        
  true ,  // kNuisEffFHCnueCC0pi01             
  true ,  // kNuisEffFHCnueCC0pi02             
  true ,  // kNuisEffFHCnueCC0pi03             
  true ,  // kNuisEffFHCnueCC0pi04             
  true ,  // kNuisEffFHCnueCC0pi05             
  true ,  // kNuisEffFHCnueCC0pi06             
  true ,  // kNuisEffFHCnueCC0pi07             
  true ,  // kNuisEffFHCnueCC0pi08             
  true ,  // kNuisEffFHCnueCC0pi09             
  true ,  // kNuisEffFHCnueCC1pic01            
  true ,  // kNuisEffFHCnueCC1pic02            
  true ,  // kNuisEffFHCnueCC1pic03            
  true ,  // kNuisEffFHCnueCC1pic04            
  true ,  // kNuisEffFHCnueCC1pic05            
  true ,  // kNuisEffFHCnueCC1pic06            
  true ,  // kNuisEffFHCnueCC1pic07            
  true ,  // kNuisEffFHCnueCC1pic08            
  true ,  // kNuisEffFHCnueCC1pic09            
  true ,  // kNuisEffFHCnueCC1piz01            
  true ,  // kNuisEffFHCnueCC1piz02            
  true ,  // kNuisEffFHCnueCC1piz03            
  true ,  // kNuisEffFHCnueCC1piz04            
  true ,  // kNuisEffFHCnueCC1piz05            
  true ,  // kNuisEffFHCnueCC1piz06            
  true ,  // kNuisEffFHCnueCC1piz07            
  true ,  // kNuisEffFHCnueCC1piz08            
  true ,  // kNuisEffFHCnueCC1piz09            
  true ,  // kNuisEffFHCnueCCother01           
  true ,  // kNuisEffFHCnueCCother02           
  true ,  // kNuisEffFHCnueCCother03           
  true ,  // kNuisEffFHCnueCCother04           
  true ,  // kNuisEffFHCnueCCother05           
  true ,  // kNuisEffFHCnueCCother06           
  true ,  // kNuisEffFHCnueCCother07           
  true ,  // kNuisEffFHCnueCCother08           
  true ,  // kNuisEffFHCnueCCother09           
  true ,  // kNuisEffFHCnueCCother10           
  true ,  // kNuisEffFHCnueCCother11           
  true ,  // kNuisEffFHCnueCCWS01              
  true ,  // kNuisEffFHCnueCCWS02              
  true ,  // kNuisEffFHCNC0pi01                
  true ,  // kNuisEffFHCNC0pi02                
  true ,  // kNuisEffFHCNC0pi03                
  true ,  // kNuisEffFHCNC1pic01               
  true ,  // kNuisEffFHCNC1pic02               
  true ,  // kNuisEffFHCNC1pic03               
  true ,  // kNuisEffFHCNC1piz01               
  true ,  // kNuisEffFHCNC1piz02               
  true ,  // kNuisEffFHCNC1piz03               
  true ,  // kNuisEffFHCNCother01              
  true ,  // kNuisEffFHCNCother02              
  true ,  // kNuisEffFHCNCother03              
  true ,  // kNuisEffFHCNeutrinoElec           
  true ,  // kNuisEffFHCIMD                    
  true ,  // kNuisEffRHCnumuCC0pi1trk01        
  true ,  // kNuisEffRHCnumuCC0pi1trk02        
  true ,  // kNuisEffRHCnumuCC0pi1trk03        
  true ,  // kNuisEffRHCnumuCC0pi1trk04        
  true ,  // kNuisEffRHCnumuCC0pi1trk05        
  true ,  // kNuisEffRHCnumuCC0pi1trk06        
  true ,  // kNuisEffRHCnumuCC0pi1trk07        
  true ,  // kNuisEffRHCnumuCC0pi1trk08        
  true ,  // kNuisEffRHCnumuCC0pi1trk09        
  true ,  // kNuisEffRHCnumuCC0pi2trk01        
  true ,  // kNuisEffRHCnumuCC0pi2trk02        
  true ,  // kNuisEffRHCnumuCC0pi2trk03        
  true ,  // kNuisEffRHCnumuCC0pi2trk04        
  true ,  // kNuisEffRHCnumuCC0pi2trk05        
  true ,  // kNuisEffRHCnumuCC0pi2trk06        
  true ,  // kNuisEffRHCnumuCC0pi2trk07        
  true ,  // kNuisEffRHCnumuCC0pi2trk08        
  true ,  // kNuisEffRHCnumuCC0pi2trk09        
  true ,  // kNuisEffRHCnumuCC0piNtrk01        
  true ,  // kNuisEffRHCnumuCC0piNtrk02        
  true ,  // kNuisEffRHCnumuCC0piNtrk03        
  true ,  // kNuisEffRHCnumuCC0piNtrk04        
  true ,  // kNuisEffRHCnumuCC0piNtrk05        
  true ,  // kNuisEffRHCnumuCC0piNtrk06        
  true ,  // kNuisEffRHCnumuCC0piNtrk07        
  true ,  // kNuisEffRHCnumuCC0piNtrk08        
  true ,  // kNuisEffRHCnumuCC0piNtrk09        
  true ,  // kNuisEffRHCnumuCC0piNtrk10        
  true ,  // kNuisEffRHCnumuCC0piNtrk11        
  true ,  // kNuisEffRHCnumuCC0piNtrk12        
  true ,  // kNuisEffRHCnumuCC0piNtrk13        
  true ,  // kNuisEffRHCnumuCC0piNtrk14        
  true ,  // kNuisEffRHCnumuCC0piNtrk15        
  true ,  // kNuisEffRHCnumuCC1pi3trkDelta01   
  true ,  // kNuisEffRHCnumuCC1pi3trkDelta02   
  true ,  // kNuisEffRHCnumuCC1pi3trkDelta03   
  true ,  // kNuisEffRHCnumuCC1pi3trkDelta04   
  true ,  // kNuisEffRHCnumuCC1pi3trkDelta05   
  true ,  // kNuisEffRHCnumuCC1pi3trkDelta06   
  true ,  // kNuisEffRHCnumuCC1pi3trkDelta07   
  true ,  // kNuisEffRHCnumuCC1pi3trkDelta08   
  true ,  // kNuisEffRHCnumuCC1pi3trkDelta09   
  true ,  // kNuisEffRHCnumuCC1pi3trkDelta10   
  true ,  // kNuisEffRHCnumuCC1pi3trkDelta11   
  true ,  // kNuisEffRHCnumuCC1pi3trkDelta12   
  true ,  // kNuisEffRHCnumuCC1pi3trkDelta13   
  true ,  // kNuisEffRHCnumuCC1pi3trkDelta14   
  true ,  // kNuisEffRHCnumuCC1pi3trkDelta15   
  true ,  // kNuisEffRHCnumuCC1pic01           
  true ,  // kNuisEffRHCnumuCC1pic02           
  true ,  // kNuisEffRHCnumuCC1pic03           
  true ,  // kNuisEffRHCnumuCC1pic04           
  true ,  // kNuisEffRHCnumuCC1pic05           
  true ,  // kNuisEffRHCnumuCC1pic06           
  true ,  // kNuisEffRHCnumuCC1pic07           
  true ,  // kNuisEffRHCnumuCC1pic08           
  true ,  // kNuisEffRHCnumuCC1pic09           
  true ,  // kNuisEffRHCnumuCC1piz01           
  true ,  // kNuisEffRHCnumuCC1piz02           
  true ,  // kNuisEffRHCnumuCC1piz03           
  true ,  // kNuisEffRHCnumuCC1piz04           
  true ,  // kNuisEffRHCnumuCC1piz05           
  true ,  // kNuisEffRHCnumuCC1piz06           
  true ,  // kNuisEffRHCnumuCC1piz07           
  true ,  // kNuisEffRHCnumuCC1piz08           
  true ,  // kNuisEffRHCnumuCC1piz09           
  true ,  // kNuisEffRHCnumuCC1pic1piz01       
  true ,  // kNuisEffRHCnumuCC1pic1piz02       
  true ,  // kNuisEffRHCnumuCC1pic1piz03       
  true ,  // kNuisEffRHCnumuCC1pic1piz04       
  true ,  // kNuisEffRHCnumuCC1pic1piz05       
  true ,  // kNuisEffRHCnumuCC1pic1piz06       
  true ,  // kNuisEffRHCnumuCC1pic1piz07       
  true ,  // kNuisEffRHCnumuCC1pic1piz08       
  true ,  // kNuisEffRHCnumuCC1pic1piz09       
  true ,  // kNuisEffRHCnumuCCother01          
  true ,  // kNuisEffRHCnumuCCother02          
  true ,  // kNuisEffRHCnumuCCother03          
  true ,  // kNuisEffRHCnumuCCother04          
  true ,  // kNuisEffRHCnumuCCother05          
  true ,  // kNuisEffRHCnumuCCother06          
  true ,  // kNuisEffRHCnumuCCother07          
  true ,  // kNuisEffRHCnumuCCother08          
  true ,  // kNuisEffRHCnumuCCother09          
  true ,  // kNuisEffRHCnumuCCother10          
  true ,  // kNuisEffRHCnumuCCother11          
  true ,  // kNuisEffRHCnumuCCWS0pi01          
  true ,  // kNuisEffRHCnumuCCWS0pi02          
  true ,  // kNuisEffRHCnumuCCWS0pi03          
  true ,  // kNuisEffRHCnumuCCWS0pi04          
  true ,  // kNuisEffRHCnumuCCWS0pi05          
  true ,  // kNuisEffRHCnumuCCWS1pic01         
  true ,  // kNuisEffRHCnumuCCWS1pic02         
  true ,  // kNuisEffRHCnumuCCWS1pic03         
  true ,  // kNuisEffRHCnumuCCWS1pic04         
  true ,  // kNuisEffRHCnumuCCWS1pic05         
  true ,  // kNuisEffRHCnumuCCWS1pic06         
  true ,  // kNuisEffRHCnumuCCWS1pic07         
  true ,  // kNuisEffRHCnumuCCWS1pic08         
  true ,  // kNuisEffRHCnumuCCWS1piz01         
  true ,  // kNuisEffRHCnumuCCWS1piz02         
  true ,  // kNuisEffRHCnumuCCWS1piz03         
  true ,  // kNuisEffRHCnumuCCWSother01        
  true ,  // kNuisEffRHCnueCC0pi01             
  true ,  // kNuisEffRHCnueCC0pi02             
  true ,  // kNuisEffRHCnueCC0pi03             
  true ,  // kNuisEffRHCnueCC0pi04             
  true ,  // kNuisEffRHCnueCC0pi05             
  true ,  // kNuisEffRHCnueCC0pi06             
  true ,  // kNuisEffRHCnueCC0pi07             
  true ,  // kNuisEffRHCnueCC0pi08             
  true ,  // kNuisEffRHCnueCC0pi09             
  true ,  // kNuisEffRHCnueCC1pic01            
  true ,  // kNuisEffRHCnueCC1pic02            
  true ,  // kNuisEffRHCnueCC1pic03            
  true ,  // kNuisEffRHCnueCC1pic04            
  true ,  // kNuisEffRHCnueCC1pic05            
  true ,  // kNuisEffRHCnueCC1pic06            
  true ,  // kNuisEffRHCnueCC1pic07            
  true ,  // kNuisEffRHCnueCC1pic08            
  true ,  // kNuisEffRHCnueCC1pic09            
  true ,  // kNuisEffRHCnueCC1piz01            
  true ,  // kNuisEffRHCnueCC1piz02            
  true ,  // kNuisEffRHCnueCC1piz03            
  true ,  // kNuisEffRHCnueCC1piz04            
  true ,  // kNuisEffRHCnueCC1piz05            
  true ,  // kNuisEffRHCnueCC1piz06            
  true ,  // kNuisEffRHCnueCC1piz07            
  true ,  // kNuisEffRHCnueCC1piz08            
  true ,  // kNuisEffRHCnueCC1piz09            
  true ,  // kNuisEffRHCnueCCother01           
  true ,  // kNuisEffRHCnueCCother02           
  true ,  // kNuisEffRHCnueCCother03           
  true ,  // kNuisEffRHCnueCCother04           
  true ,  // kNuisEffRHCnueCCother05           
  true ,  // kNuisEffRHCnueCCother06           
  true ,  // kNuisEffRHCnueCCother07           
  true ,  // kNuisEffRHCnueCCother08           
  true ,  // kNuisEffRHCnueCCother09           
  true ,  // kNuisEffRHCnueCCother10           
  true ,  // kNuisEffRHCnueCCother11           
  true ,  // kNuisEffRHCnueCCWS01              
  true ,  // kNuisEffRHCnueCCWS02              
  true ,  // kNuisEffRHCNC0pi01                
  true ,  // kNuisEffRHCNC0pi02                
  true ,  // kNuisEffRHCNC0pi03                
  true ,  // kNuisEffRHCNC1pic01               
  true ,  // kNuisEffRHCNC1pic02               
  true ,  // kNuisEffRHCNC1pic03               
  true ,  // kNuisEffRHCNC1piz01               
  true ,  // kNuisEffRHCNC1piz02               
  true ,  // kNuisEffRHCNC1piz03               
  true ,  // kNuisEffRHCNCother01              
  true ,  // kNuisEffRHCNCother02              
  true ,  // kNuisEffRHCNCother03              
  true ,  // kNuisEffRHCNeutrinoElec           
  true ,  // kNuisEffRHCIMD                    
  // Far detector systematics
  false,  // kNuisEffFDNuMuCCHigh
  false,  // kNuisEffFDNuMuCCLow
  false,  // kNuisEffFDNuECCHigh
  false,  // kNuisEffFDNuECCLow
};

// Which is the true energy range?
static const double kFitParamErecoRange[kNFitParams][2] =
{
  //oscillation parameters
  { 0.0 , kErecoMax },
  { 0.0 , kErecoMax },
  { 0.0 , kErecoMax },
  { 0.0 , kErecoMax },
  { 0.0 , kErecoMax },
  { 0.0 , kErecoMax },
  // Emin, Emax
   // FHC flux
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux00
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux01
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux02
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux03
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux04
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux05
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux06
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux07
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux08
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux09
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux10
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux11
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux12
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux13
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux14
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux15
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux16
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux17
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFlux18
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux00
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux01
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux02
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux03
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux04
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux05
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux06
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux07
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux08
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux09
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux10
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux11
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux12
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux13
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux14
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux15
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux16
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux17
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFlux18
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEFlux00
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEFlux01
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEFlux02
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEFlux03
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEFlux04
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEFlux05
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEFlux06
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEBarFlux00
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEBarFlux01
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEBarFlux02
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEBarFlux03
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEBarFlux04
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEBarFlux05
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEBarFlux06
  
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux00
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux01
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux02
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux03
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux04
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux05
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux06
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux07
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux08
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux09
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux10
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux11
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux12
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux13
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux14
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux15
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux16
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux17
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuFlux18
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux00
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux01
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux02
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux03
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux04
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux05
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux06
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux07
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux08
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux09
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux10
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux11
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux12
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux13
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux14
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux15
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux16
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux17
  { 0.0 , kErecoMax } ,   // kNuisRHCNuMuBarFlux18
  { 0.0 , kErecoMax } ,   // kNuisRHCNuEFlux00
  { 0.0 , kErecoMax } ,   // kNuisRHCNuEFlux01
  { 0.0 , kErecoMax } ,   // kNuisRHCNuEFlux02
  { 0.0 , kErecoMax } ,   // kNuisRHCNuEFlux03
  { 0.0 , kErecoMax } ,   // kNuisRHCNuEFlux04
  { 0.0 , kErecoMax } ,   // kNuisRHCNuEFlux05
  { 0.0 , kErecoMax } ,   // kNuisRHCNuEFlux06
  { 0.0 , kErecoMax } ,   // kNuisRHCNuEBarFlux00
  { 0.0 , kErecoMax } ,   // kNuisRHCNuEBarFlux01
  { 0.0 , kErecoMax } ,   // kNuisRHCNuEBarFlux02
  { 0.0 , kErecoMax } ,   // kNuisRHCNuEBarFlux03
  { 0.0 , kErecoMax } ,   // kNuisRHCNuEBarFlux04
  { 0.0 , kErecoMax } ,   // kNuisRHCNuEBarFlux05
  { 0.0 , kErecoMax } ,   // kNuisRHCNuEBarFlux06
    
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux00
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux01
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux02
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux03
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux04
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux05
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux06
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux07
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux08
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux09
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux10
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux11
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux12
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux13
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux14
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux15
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux16
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux17
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuFDFlux18
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux00
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux01
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux02
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux03
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux04
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux05
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux06
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux07
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux08
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux09
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux10
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux11
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux12
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux13
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux14
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux15
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux16
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux17
  { 0.0 , kErecoMax } ,   // kNuisFHCNuMuBarFDFlux18
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEFDFlux00
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEFDFlux01
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEFDFlux02
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEFDFlux03
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEFDFlux04
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEFDFlux05
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEFDFlux06
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEBarFDFlux00
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEBarFDFlux01
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEBarFDFlux02
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEBarFDFlux03
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEBarFDFlux04
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEBarFDFlux05
  { 0.0 , kErecoMax } ,   // kNuisFHCNuEBarFDFlux06
   // RHC flux
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux00
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux01
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux02
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux03
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux04
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux05
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux06
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux07
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux08
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux09
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux10
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux11
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux12
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux13
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux14
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux15
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux16
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux17
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuFDFlux18
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux00
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux01
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux02
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux03
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux04
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux05
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux06
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux07
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux08
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux09
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux10
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux11
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux12
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux13
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux14
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux15
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux16
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux17
  { 0.0 , kErecoMax } ,  // kNuisRHCNuMuBarFDFlux18
  { 0.0 , kErecoMax } ,  // kNuisRHCNuEFDFlux00
  { 0.0 , kErecoMax } ,  // kNuisRHCNuEFDFlux01
  { 0.0 , kErecoMax } ,  // kNuisRHCNuEFDFlux02
  { 0.0 , kErecoMax } ,  // kNuisRHCNuEFDFlux03
  { 0.0 , kErecoMax } ,  // kNuisRHCNuEFDFlux04
  { 0.0 , kErecoMax } ,  // kNuisRHCNuEFDFlux05
  { 0.0 , kErecoMax } ,  // kNuisRHCNuEFDFlux06
  { 0.0 , kErecoMax } ,  // kNuisRHCNuEBarFDFlux00
  { 0.0 , kErecoMax } ,  // kNuisRHCNuEBarFDFlux01
  { 0.0 , kErecoMax } ,  // kNuisRHCNuEBarFDFlux02
  { 0.0 , kErecoMax } ,  // kNuisRHCNuEBarFDFlux03
  { 0.0 , kErecoMax } ,  // kNuisRHCNuEBarFDFlux04
  { 0.0 , kErecoMax } ,  // kNuisRHCNuEBarFDFlux05
  { 0.0 , kErecoMax } ,  // kNuisRHCNuEBarFDFlux06
  // Cross-sections
  { 0.0 , kErecoMax } ,  // kNuisIntNuCCQE1
  { 0.0 , kErecoMax } ,  // kNuisIntNuCCQE2
  { 0.0 , kErecoMax } ,  // kNuisIntNuCCQE3
  { 0.0 , kErecoMax } ,  // kNuisIntNuBarCCQE1
  { 0.0 , kErecoMax } ,  // kNuisIntNuBarCCQE2
  { 0.0 , kErecoMax } ,  // kNuisIntNuBarCCQE3
  { 0.0 , kErecoMax } ,  // kNuisIntNuCCMEC
  { 0.0 , kErecoMax } ,  // kNuisIntNuBarCCMEC
  { 0.0 , kErecoMax } ,  // kNuisIntNuCC1piz1
  { 0.0 , kErecoMax } ,  // kNuisIntNuCC1piz2
  { 0.0 , kErecoMax } ,  // kNuisIntNuCC1piz3
  { 0.0 , kErecoMax } ,  // kNuisIntNuCC1pic1
  { 0.0 , kErecoMax } ,  // kNuisIntNuCC1pic2
  { 0.0 , kErecoMax } ,  // kNuisIntNuCC1pic3
  { 0.0 , kErecoMax } ,  // kNuisIntNuBarCC1piz1
  { 0.0 , kErecoMax } ,  // kNuisIntNuBarCC1piz2
  { 0.0 , kErecoMax } ,  // kNuisIntNuBarCC1piz3
  { 0.0 , kErecoMax } ,  // kNuisIntNuBarCC1pic1
  { 0.0 , kErecoMax } ,  // kNuisIntNuBarCC1pic2
  { 0.0 , kErecoMax } ,  // kNuisIntNuBarCC1pic3
  { 0.0 , kErecoMax } ,  // kNuisIntNuCC2Pi
  { 0.0 , kErecoMax } ,  // kNuisIntNuBarCC2Pi
  { 0.0 , kErecoMax } ,  // kNuisIntNuDIS1
  { 0.0 , kErecoMax } ,  // kNuisIntNuDIS2
  { 0.0 , kErecoMax } ,  // kNuisIntNuDIS3
  { 0.0 , kErecoMax } ,  // kNuisIntNuBarDIS1
  { 0.0 , kErecoMax } ,  // kNuisIntNuBarDIS2
  { 0.0 , kErecoMax } ,  // kNuisIntNuBarDIS3
  { 0.0 , kErecoMax } ,  // kNuisIntNormNuCoherent
  { 0.0 , kErecoMax } ,  // kNuisIntNormNuBarCoherent
  { 0.0 , kErecoMax } ,  // kNuisIntNuNormNC
  { 0.0 , kErecoMax } ,  // kNuisIntNuBarNormNC
  { 0.0 , kErecoMax } ,  // kNuisIntNormNuMuToNuE
  { 0.0 , kErecoMax } ,  // kNuisIntPiMeanFreePath
  { 0.0 , kErecoMax } ,  // kNuisIntNucMeanFreePath
  { 0.0 , kErecoMax } ,  // kNuisIntFracPiChargeExchange
  { 0.0 , kErecoMax } ,  // kNuisIntFracPiInelastic
  { 0.0 , kErecoMax } ,  // kNuisIntFracPiAbsorb
  { 0.0 , kErecoMax } ,  // kNuisIntFracPiProduction
  { 0.0 , kErecoMax } ,  // kNuisIntFracNucChargeExchange
  { 0.0 , kErecoMax } ,  // kNuisIntFracNucInelastic
  { 0.0 , kErecoMax } ,  // kNuisIntFracNucAbsorb
  { 0.0 , kErecoMax } ,  // kNuisIntFracNucProduction
  // Detector systematics
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0pi1trk01        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0pi1trk02        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0pi1trk03        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0pi1trk04        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0pi1trk05        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0pi1trk06        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0pi1trk07        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0pi1trk08        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0pi1trk09        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0pi2trk01        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0pi2trk02        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0pi2trk03        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0pi2trk04        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0pi2trk05        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0pi2trk06        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0pi2trk07        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0pi2trk08        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0pi2trk09        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0piNtrk01        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0piNtrk02        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0piNtrk03        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0piNtrk04        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0piNtrk05        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0piNtrk06        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0piNtrk07        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0piNtrk08        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0piNtrk09        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0piNtrk10        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0piNtrk11        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0piNtrk12        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0piNtrk13        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0piNtrk14        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC0piNtrk15        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pi3trkDelta01   
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pi3trkDelta02   
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pi3trkDelta03   
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pi3trkDelta04   
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pi3trkDelta05   
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pi3trkDelta06   
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pi3trkDelta07   
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pi3trkDelta08   
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pi3trkDelta09   
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pi3trkDelta10   
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pi3trkDelta11   
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pi3trkDelta12   
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pi3trkDelta13   
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pi3trkDelta14   
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pi3trkDelta15   
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pic01           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pic02           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pic03           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pic04           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pic05           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pic06           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pic07           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pic08           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pic09           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1piz01           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1piz02           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1piz03           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1piz04           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1piz05           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1piz06           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1piz07           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1piz08           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1piz09           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pic1piz01       
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pic1piz02       
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pic1piz03       
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pic1piz04       
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pic1piz05       
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pic1piz06       
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pic1piz07       
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pic1piz08       
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCC1pic1piz09       
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCother01          
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCother02          
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCother03          
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCother04          
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCother05          
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCother06          
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCother07          
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCother08          
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCother09          
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCother10          
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCother11          
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCWS0pi01          
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCWS0pi02          
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCWS0pi03          
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCWS0pi04          
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCWS0pi05          
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCWS1pic01         
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCWS1pic02         
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCWS1pic03         
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCWS1pic04         
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCWS1pic05         
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCWS1pic06         
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCWS1pic07         
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCWS1pic08         
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCWS1piz01         
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCWS1piz02         
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCWS1piz03         
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnumuCCWSother01        
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC0pi01             
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC0pi02             
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC0pi03             
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC0pi04             
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC0pi05             
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC0pi06             
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC0pi07             
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC0pi08             
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC0pi09             
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC1pic01            
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC1pic02            
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC1pic03            
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC1pic04            
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC1pic05            
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC1pic06            
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC1pic07            
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC1pic08            
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC1pic09            
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC1piz01            
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC1piz02            
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC1piz03            
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC1piz04            
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC1piz05            
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC1piz06            
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC1piz07            
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC1piz08            
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCC1piz09            
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCCother01           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCCother02           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCCother03           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCCother04           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCCother05           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCCother06           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCCother07           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCCother08           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCCother09           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCCother10           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCCother11           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCCWS01              
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCnueCCWS02              
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCNC0pi01                
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCNC0pi02                
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCNC0pi03                
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCNC1pic01               
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCNC1pic02               
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCNC1pic03               
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCNC1piz01               
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCNC1piz02               
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCNC1piz03               
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCNCother01              
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCNCother02              
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCNCother03              
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCNeutrinoElec           
  {  0.0 , kEtrueMax} ,  // kNuisEffFHCIMD                    
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0pi1trk01        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0pi1trk02        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0pi1trk03        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0pi1trk04        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0pi1trk05        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0pi1trk06        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0pi1trk07        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0pi1trk08        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0pi1trk09        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0pi2trk01        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0pi2trk02        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0pi2trk03        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0pi2trk04        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0pi2trk05        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0pi2trk06        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0pi2trk07        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0pi2trk08        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0pi2trk09        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0piNtrk01        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0piNtrk02        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0piNtrk03        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0piNtrk04        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0piNtrk05        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0piNtrk06        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0piNtrk07        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0piNtrk08        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0piNtrk09        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0piNtrk10        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0piNtrk11        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0piNtrk12        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0piNtrk13        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0piNtrk14        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC0piNtrk15        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pi3trkDelta01   
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pi3trkDelta02   
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pi3trkDelta03   
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pi3trkDelta04   
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pi3trkDelta05   
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pi3trkDelta06   
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pi3trkDelta07   
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pi3trkDelta08   
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pi3trkDelta09   
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pi3trkDelta10   
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pi3trkDelta11   
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pi3trkDelta12   
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pi3trkDelta13   
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pi3trkDelta14   
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pi3trkDelta15   
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pic01           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pic02           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pic03           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pic04           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pic05           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pic06           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pic07           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pic08           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pic09           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1piz01           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1piz02           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1piz03           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1piz04           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1piz05           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1piz06           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1piz07           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1piz08           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1piz09           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pic1piz01       
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pic1piz02       
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pic1piz03       
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pic1piz04       
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pic1piz05       
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pic1piz06       
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pic1piz07       
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pic1piz08       
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCC1pic1piz09       
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCother01          
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCother02          
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCother03          
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCother04          
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCother05          
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCother06          
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCother07          
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCother08          
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCother09          
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCother10          
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCother11          
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCWS0pi01          
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCWS0pi02          
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCWS0pi03          
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCWS0pi04          
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCWS0pi05          
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCWS1pic01         
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCWS1pic02         
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCWS1pic03         
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCWS1pic04         
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCWS1pic05         
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCWS1pic06         
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCWS1pic07         
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCWS1pic08         
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCWS1piz01         
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCWS1piz02         
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCWS1piz03         
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnumuCCWSother01        
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC0pi01             
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC0pi02             
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC0pi03             
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC0pi04             
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC0pi05             
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC0pi06             
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC0pi07             
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC0pi08             
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC0pi09             
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC1pic01            
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC1pic02            
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC1pic03            
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC1pic04            
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC1pic05            
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC1pic06            
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC1pic07            
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC1pic08            
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC1pic09            
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC1piz01            
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC1piz02            
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC1piz03            
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC1piz04            
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC1piz05            
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC1piz06            
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC1piz07            
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC1piz08            
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCC1piz09            
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCCother01           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCCother02           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCCother03           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCCother04           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCCother05           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCCother06           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCCother07           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCCother08           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCCother09           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCCother10           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCCother11           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCCWS01              
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCnueCCWS02              
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCNC0pi01                
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCNC0pi02                
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCNC0pi03                
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCNC1pic01               
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCNC1pic02               
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCNC1pic03               
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCNC1piz01               
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCNC1piz02               
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCNC1piz03               
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCNCother01              
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCNCother02              
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCNCother03              
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCNeutrinoElec           
  {  0.0 , kEtrueMax} ,  // kNuisEffRHCIMD                    
  // Far detector systematics
   {  0.0, kErecoMax} ,  // kNuisEffFDNuMuCCHigh
   {  0.0, kErecoMax} ,  // kNuisEffFDNuMuCCLow
   {  0.0, kErecoMax} ,  // kNuisEffFDNuECCHigh
   {  0.0, kErecoMax}    // kNuisEffFDNuECCLow
};

// Which is the true Q2 range?
static const double kFitParamYrecoRange[kNFitParams][2] =
{
   // Q2 min, Q2 max
  //oscillation parameters
  { 0.0, kYrecoMax },
  { 0.0, kYrecoMax },
  { 0.0, kYrecoMax },
  { 0.0, kYrecoMax },
  { 0.0, kYrecoMax },
  { 0.0, kYrecoMax },
  // FHC flux
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux00
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux01
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux02
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux03
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux04
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux05
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux06
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux07
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux08
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux09
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux10
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux11
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux12
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux13
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux14
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux15
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux16
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux17
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFlux18
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux00
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux01
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux02
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux03
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux04
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux05
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux06
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux07
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux08
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux09
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux10
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux11
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux12
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux13
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux14
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux15
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux16
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux17
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFlux18
  { 0.0, kYrecoMax }, // kNuisFHCNuEFlux00
  { 0.0, kYrecoMax }, // kNuisFHCNuEFlux01
  { 0.0, kYrecoMax }, // kNuisFHCNuEFlux02
  { 0.0, kYrecoMax }, // kNuisFHCNuEFlux03
  { 0.0, kYrecoMax }, // kNuisFHCNuEFlux04
  { 0.0, kYrecoMax }, // kNuisFHCNuEFlux05
  { 0.0, kYrecoMax }, // kNuisFHCNuEFlux06
  { 0.0, kYrecoMax }, // kNuisFHCNuEBarFlux00
  { 0.0, kYrecoMax }, // kNuisFHCNuEBarFlux01
  { 0.0, kYrecoMax }, // kNuisFHCNuEBarFlux02
  { 0.0, kYrecoMax }, // kNuisFHCNuEBarFlux03
  { 0.0, kYrecoMax }, // kNuisFHCNuEBarFlux04
  { 0.0, kYrecoMax }, // kNuisFHCNuEBarFlux05
  { 0.0, kYrecoMax }, // kNuisFHCNuEBarFlux06
  // RHC flux
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux00
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux01
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux02
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux03
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux04
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux05
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux06
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux07
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux08
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux09
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux10
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux11
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux12
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux13
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux14
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux15
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux16
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux17
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFlux18
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux00
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux01
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux02
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux03
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux04
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux05
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux06
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux07
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux08
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux09
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux10
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux11
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux12
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux13
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux14
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux15
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux16
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux17
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFlux18
  { 0.0, kYrecoMax },  // kNuisRHCNuEFlux00
  { 0.0, kYrecoMax },  // kNuisRHCNuEFlux01
  { 0.0, kYrecoMax },  // kNuisRHCNuEFlux02
  { 0.0, kYrecoMax },  // kNuisRHCNuEFlux03
  { 0.0, kYrecoMax },  // kNuisRHCNuEFlux04
  { 0.0, kYrecoMax },  // kNuisRHCNuEFlux05
  { 0.0, kYrecoMax },  // kNuisRHCNuEFlux06
  { 0.0, kYrecoMax },  // kNuisRHCNuEBarFlux00
  { 0.0, kYrecoMax },  // kNuisRHCNuEBarFlux01
  { 0.0, kYrecoMax },  // kNuisRHCNuEBarFlux02
  { 0.0, kYrecoMax },  // kNuisRHCNuEBarFlux03
  { 0.0, kYrecoMax },  // kNuisRHCNuEBarFlux04
  { 0.0, kYrecoMax },  // kNuisRHCNuEBarFlux05
  { 0.0, kYrecoMax },  // kNuisRHCNuEBarFlux06
  //Far detector flux
  // FHC flux
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux00
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux01
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux02
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux03
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux04
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux05
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux06
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux07
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux08
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux09
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux10
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux11
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux12
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux13
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux14
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux15
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux16
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux17
  { 0.0, kYrecoMax }, // kNuisFHCNuMuFDFlux18
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux00
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux01
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux02
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux03
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux04
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux05
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux06
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux07
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux08
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux09
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux10
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux11
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux12
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux13
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux14
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux15
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux16
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux17
  { 0.0, kYrecoMax }, // kNuisFHCNuMuBarFDFlux18
  { 0.0, kYrecoMax }, // kNuisFHCNuEFDFlux00
  { 0.0, kYrecoMax }, // kNuisFHCNuEFDFlux01
  { 0.0, kYrecoMax }, // kNuisFHCNuEFDFlux02
  { 0.0, kYrecoMax }, // kNuisFHCNuEFDFlux03
  { 0.0, kYrecoMax }, // kNuisFHCNuEFDFlux04
  { 0.0, kYrecoMax }, // kNuisFHCNuEFDFlux05
  { 0.0, kYrecoMax }, // kNuisFHCNuEFDFlux06
  { 0.0, kYrecoMax }, // kNuisFHCNuEBarFDFlux00
  { 0.0, kYrecoMax }, // kNuisFHCNuEBarFDFlux01
  { 0.0, kYrecoMax }, // kNuisFHCNuEBarFDFlux02
  { 0.0, kYrecoMax }, // kNuisFHCNuEBarFDFlux03
  { 0.0, kYrecoMax }, // kNuisFHCNuEBarFDFlux04
  { 0.0, kYrecoMax }, // kNuisFHCNuEBarFDFlux05
  { 0.0, kYrecoMax }, // kNuisFHCNuEBarFDFlux06
  // RHC flux
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux00
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux01
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux02
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux03
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux04
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux05
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux06
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux07
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux08
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux09
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux10
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux11
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux12
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux13
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux14
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux15
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux16
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux17
  { 0.0, kYrecoMax },  // kNuisRHCNuMuFDFlux18
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux00
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux01
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux02
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux03
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux04
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux05
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux06
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux07
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux08
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux09
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux10
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux11
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux12
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux13
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux14
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux15
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux16
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux17
  { 0.0, kYrecoMax },  // kNuisRHCNuMuBarFDFlux18
  { 0.0, kYrecoMax },  // kNuisRHCNuEFDFlux00
  { 0.0, kYrecoMax },  // kNuisRHCNuEFDFlux01
  { 0.0, kYrecoMax },  // kNuisRHCNuEFDFlux02
  { 0.0, kYrecoMax },  // kNuisRHCNuEFDFlux03
  { 0.0, kYrecoMax },  // kNuisRHCNuEFDFlux04
  { 0.0, kYrecoMax },  // kNuisRHCNuEFDFlux05
  { 0.0, kYrecoMax },  // kNuisRHCNuEFDFlux06
  { 0.0, kYrecoMax },  // kNuisRHCNuEBarFDFlux00
  { 0.0, kYrecoMax },  // kNuisRHCNuEBarFDFlux01
  { 0.0, kYrecoMax },  // kNuisRHCNuEBarFDFlux02
  { 0.0, kYrecoMax },  // kNuisRHCNuEBarFDFlux03
  { 0.0, kYrecoMax },  // kNuisRHCNuEBarFDFlux04
  { 0.0, kYrecoMax },  // kNuisRHCNuEBarFDFlux05
  { 0.0, kYrecoMax },  // kNuisRHCNuEBarFDFlux06
  // Cross-sections
  { 0.0 , kYrecoMax },  // kNuisIntNuCCQE1
  { 0.0 , kYrecoMax },  // kNuisIntNuCCQE2
  { 0.0 , kYrecoMax },  // kNuisIntNuCCQE3
  { 0.0 , kYrecoMax },  // kNuisIntNuBarCCQE1
  { 0.0 , kYrecoMax },  // kNuisIntNuBarCCQE2
  { 0.0 , kYrecoMax },  // kNuisIntNuBarCCQE3
  { 0.0 , kYrecoMax },  // kNuisIntNuCCMEC
  { 0.0 , kYrecoMax },  // kNuisIntNuBarCCMEC
  { 0.0 , kYrecoMax },  // kNuisIntNuCC1piz1
  { 0.0 , kYrecoMax },  // kNuisIntNuCC1piz2
  { 0.0 , kYrecoMax },  // kNuisIntNuCC1piz3
  { 0.0 , kYrecoMax },  // kNuisIntNuCC1pic1
  { 0.0 , kYrecoMax },  // kNuisIntNuCC1pic2
  { 0.0 , kYrecoMax },  // kNuisIntNuCC1pic3
  { 0.0 , kYrecoMax },  // kNuisIntNuBarCC1piz1
  { 0.0 , kYrecoMax },  // kNuisIntNuBarCC1piz2
  { 0.0 , kYrecoMax },  // kNuisIntNuBarCC1piz3
  { 0.0 , kYrecoMax },  // kNuisIntNuBarCC1pic1
  { 0.0 , kYrecoMax },  // kNuisIntNuBarCC1pic2
  { 0.0 , kYrecoMax },  // kNuisIntNuBarCC1pic3
  { 0.0 , kYrecoMax },  // kNuisIntNuCC2Pi
  { 0.0 , kYrecoMax },  // kNuisIntNuBarCC2Pi
  { 0.0 , kYrecoMax },  // kNuisIntNuDIS1
  { 0.0 , kYrecoMax },  // kNuisIntNuDIS2
  { 0.0 , kYrecoMax },  // kNuisIntNuDIS3
  { 0.0 , kYrecoMax },  // kNuisIntNuBarDIS1
  { 0.0 , kYrecoMax },  // kNuisIntNuBarDIS2
  { 0.0 , kYrecoMax },  // kNuisIntNuBarDIS3
  { 0.0 , kYrecoMax },  // kNuisIntNormNuCoherent
  { 0.0 , kYrecoMax },  // kNuisIntNormNuBarCoherent
  { 0.0 , kYrecoMax },  // kNuisIntNuNormNC
  { 0.0 , kYrecoMax },  // kNuisIntNuBarNormNC
  { 0.0 , kYrecoMax },  // kNuisIntNormNuMuToNuE
  { 0.0 , kYrecoMax },  // kNuisIntPiMeanFreePath
  { 0.0 , kYrecoMax },  // kNuisIntNucMeanFreePath
  { 0.0 , kYrecoMax },  // kNuisIntFracPiChargeExchange
  { 0.0 , kYrecoMax },  // kNuisIntFracPiInelastic
  { 0.0 , kYrecoMax },  // kNuisIntFracPiAbsorb
  { 0.0 , kYrecoMax },  // kNuisIntFracPiProduction
  { 0.0 , kYrecoMax },  // kNuisIntFracNucChargeExchange
  { 0.0 , kYrecoMax },  // kNuisIntFracNucInelastic
  { 0.0 , kYrecoMax },  // kNuisIntFracNucAbsorb
  { 0.0 , kYrecoMax },  // kNuisIntFracNucProduction
  // Detector systematics
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0pi1trk01        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0pi1trk02        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0pi1trk03        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0pi1trk04        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0pi1trk05        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0pi1trk06        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0pi1trk07        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0pi1trk08        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0pi1trk09        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0pi2trk01        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0pi2trk02        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0pi2trk03        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0pi2trk04        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0pi2trk05        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0pi2trk06        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0pi2trk07        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0pi2trk08        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0pi2trk09        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0piNtrk01        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0piNtrk02        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0piNtrk03        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0piNtrk04        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0piNtrk05        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0piNtrk06        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0piNtrk07        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0piNtrk08        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0piNtrk09        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0piNtrk10        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0piNtrk11        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0piNtrk12        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0piNtrk13        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0piNtrk14        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC0piNtrk15        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pi3trkDelta01   
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pi3trkDelta02   
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pi3trkDelta03   
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pi3trkDelta04   
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pi3trkDelta05   
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pi3trkDelta06   
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pi3trkDelta07   
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pi3trkDelta08   
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pi3trkDelta09   
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pi3trkDelta10   
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pi3trkDelta11   
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pi3trkDelta12   
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pi3trkDelta13   
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pi3trkDelta14   
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pi3trkDelta15   
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pic01           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pic02           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pic03           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pic04           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pic05           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pic06           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pic07           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pic08           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pic09           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1piz01           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1piz02           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1piz03           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1piz04           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1piz05           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1piz06           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1piz07           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1piz08           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1piz09           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pic1piz01       
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pic1piz02       
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pic1piz03       
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pic1piz04       
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pic1piz05       
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pic1piz06       
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pic1piz07       
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pic1piz08       
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCC1pic1piz09       
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCother01          
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCother02          
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCother03          
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCother04          
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCother05          
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCother06          
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCother07          
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCother08          
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCother09          
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCother10          
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCother11          
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCWS0pi01          
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCWS0pi02          
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCWS0pi03          
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCWS0pi04          
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCWS0pi05          
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCWS1pic01         
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCWS1pic02         
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCWS1pic03         
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCWS1pic04         
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCWS1pic05         
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCWS1pic06         
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCWS1pic07         
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCWS1pic08         
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCWS1piz01         
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCWS1piz02         
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCWS1piz03         
  { 0.0  , kYrecoMax},  // kNuisEffFHCnumuCCWSother01        
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC0pi01             
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC0pi02             
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC0pi03             
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC0pi04             
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC0pi05             
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC0pi06             
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC0pi07             
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC0pi08             
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC0pi09             
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC1pic01            
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC1pic02            
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC1pic03            
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC1pic04            
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC1pic05            
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC1pic06            
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC1pic07            
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC1pic08            
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC1pic09            
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC1piz01            
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC1piz02            
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC1piz03            
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC1piz04            
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC1piz05            
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC1piz06            
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC1piz07            
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC1piz08            
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCC1piz09            
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCCother01           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCCother02           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCCother03           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCCother04           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCCother05           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCCother06           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCCother07           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCCother08           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCCother09           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCCother10           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCCother11           
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCCWS01              
  { 0.0  , kYrecoMax},  // kNuisEffFHCnueCCWS02              
  { 0.0  , kYrecoMax},  // kNuisEffFHCNC0pi01                
  { 0.0  , kYrecoMax},  // kNuisEffFHCNC0pi02                
  { 0.0  , kYrecoMax},  // kNuisEffFHCNC0pi03                
  { 0.0  , kYrecoMax},  // kNuisEffFHCNC1pic01               
  { 0.0  , kYrecoMax},  // kNuisEffFHCNC1pic02               
  { 0.0  , kYrecoMax},  // kNuisEffFHCNC1pic03               
  { 0.0  , kYrecoMax},  // kNuisEffFHCNC1piz01               
  { 0.0  , kYrecoMax},  // kNuisEffFHCNC1piz02               
  { 0.0  , kYrecoMax},  // kNuisEffFHCNC1piz03               
  { 0.0  , kYrecoMax},  // kNuisEffFHCNCother01              
  { 0.0  , kYrecoMax},  // kNuisEffFHCNCother02              
  { 0.0  , kYrecoMax},  // kNuisEffFHCNCother03              
  { 0.0  , kYrecoMax},  // kNuisEffFHCNeutrinoElec           
  { 0.0  , kYrecoMax},  // kNuisEffFHCIMD                    
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0pi1trk01        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0pi1trk02        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0pi1trk03        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0pi1trk04        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0pi1trk05        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0pi1trk06        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0pi1trk07        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0pi1trk08        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0pi1trk09        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0pi2trk01        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0pi2trk02        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0pi2trk03        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0pi2trk04        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0pi2trk05        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0pi2trk06        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0pi2trk07        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0pi2trk08        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0pi2trk09        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0piNtrk01        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0piNtrk02        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0piNtrk03        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0piNtrk04        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0piNtrk05        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0piNtrk06        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0piNtrk07        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0piNtrk08        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0piNtrk09        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0piNtrk10        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0piNtrk11        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0piNtrk12        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0piNtrk13        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0piNtrk14        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC0piNtrk15        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pi3trkDelta01   
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pi3trkDelta02   
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pi3trkDelta03   
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pi3trkDelta04   
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pi3trkDelta05   
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pi3trkDelta06   
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pi3trkDelta07   
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pi3trkDelta08   
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pi3trkDelta09   
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pi3trkDelta10   
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pi3trkDelta11   
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pi3trkDelta12   
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pi3trkDelta13   
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pi3trkDelta14   
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pi3trkDelta15   
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pic01           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pic02           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pic03           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pic04           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pic05           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pic06           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pic07           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pic08           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pic09           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1piz01           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1piz02           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1piz03           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1piz04           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1piz05           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1piz06           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1piz07           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1piz08           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1piz09           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pic1piz01       
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pic1piz02       
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pic1piz03       
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pic1piz04       
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pic1piz05       
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pic1piz06       
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pic1piz07       
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pic1piz08       
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCC1pic1piz09       
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCother01          
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCother02          
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCother03          
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCother04          
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCother05          
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCother06          
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCother07          
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCother08          
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCother09          
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCother10          
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCother11          
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCWS0pi01          
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCWS0pi02          
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCWS0pi03          
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCWS0pi04          
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCWS0pi05          
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCWS1pic01         
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCWS1pic02         
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCWS1pic03         
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCWS1pic04         
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCWS1pic05         
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCWS1pic06         
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCWS1pic07         
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCWS1pic08         
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCWS1piz01         
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCWS1piz02         
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCWS1piz03         
  { 0.0  , kYrecoMax},  // kNuisEffRHCnumuCCWSother01        
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC0pi01             
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC0pi02             
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC0pi03             
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC0pi04             
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC0pi05             
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC0pi06             
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC0pi07             
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC0pi08             
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC0pi09             
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC1pic01            
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC1pic02            
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC1pic03            
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC1pic04            
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC1pic05            
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC1pic06            
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC1pic07            
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC1pic08            
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC1pic09            
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC1piz01            
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC1piz02            
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC1piz03            
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC1piz04            
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC1piz05            
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC1piz06            
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC1piz07            
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC1piz08            
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCC1piz09            
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCCother01           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCCother02           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCCother03           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCCother04           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCCother05           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCCother06           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCCother07           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCCother08           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCCother09           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCCother10           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCCother11           
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCCWS01              
  { 0.0  , kYrecoMax},  // kNuisEffRHCnueCCWS02              
  { 0.0  , kYrecoMax},  // kNuisEffRHCNC0pi01                
  { 0.0  , kYrecoMax},  // kNuisEffRHCNC0pi02                
  { 0.0  , kYrecoMax},  // kNuisEffRHCNC0pi03                
  { 0.0  , kYrecoMax},  // kNuisEffRHCNC1pic01               
  { 0.0  , kYrecoMax},  // kNuisEffRHCNC1pic02               
  { 0.0  , kYrecoMax},  // kNuisEffRHCNC1pic03               
  { 0.0  , kYrecoMax},  // kNuisEffRHCNC1piz01               
  { 0.0  , kYrecoMax},  // kNuisEffRHCNC1piz02               
  { 0.0  , kYrecoMax},  // kNuisEffRHCNC1piz03               
  { 0.0  , kYrecoMax},  // kNuisEffRHCNCother01              
  { 0.0  , kYrecoMax},  // kNuisEffRHCNCother02              
  { 0.0  , kYrecoMax},  // kNuisEffRHCNCother03              
  { 0.0  , kYrecoMax},  // kNuisEffRHCNeutrinoElec           
  { 0.0  , kYrecoMax},  // kNuisEffRHCIMD                    
  // Far detector systematics
  { 0.0  , kYrecoMax},  // kNuisEffFDNuMuCCHigh
  { 0.0  , kYrecoMax},  // kNuisEffFDNuMuCCLow
  { 0.0  , kYrecoMax},  // kNuisEffFDNuECCHigh
  { 0.0  , kYrecoMax}   // kNuisEffFDNuECCLow
};

#endif // valor_dune_fit_param_reco_ranges_h
