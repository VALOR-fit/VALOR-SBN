//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include "Utilities/NameRegistry.h"
#include "Utilities/Rnd.h"
#include "Utilities/UtlStr.h"
#include "Utilities/UtlSystem.h"
#include "NDFit/NDFitParams.h"
#include "Messenger/Messenger.h"

#include "NDFit/NDArrIdx.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
string util::AsString(conv::PhysParamId_t p)
{
  switch(p) {
    case (kNuisFHCNuMuFlux00   ) : return "f_fhc_flux_numu00";    break;
    case (kNuisFHCNuMuFlux01   ) : return "f_fhc_flux_numu01";    break;
    case (kNuisFHCNuMuFlux02   ) : return "f_fhc_flux_numu02";    break;
    case (kNuisFHCNuMuFlux03   ) : return "f_fhc_flux_numu03";    break;
    case (kNuisFHCNuMuFlux04   ) : return "f_fhc_flux_numu04";    break;
    case (kNuisFHCNuMuFlux05   ) : return "f_fhc_flux_numu05";    break;
    case (kNuisFHCNuMuFlux06   ) : return "f_fhc_flux_numu06";    break;
    case (kNuisFHCNuMuFlux07   ) : return "f_fhc_flux_numu07";    break;
    case (kNuisFHCNuMuFlux08   ) : return "f_fhc_flux_numu08";    break;
    case (kNuisFHCNuMuFlux09   ) : return "f_fhc_flux_numu09";    break;
    case (kNuisFHCNuMuFlux10   ) : return "f_fhc_flux_numu10";    break;
    case (kNuisFHCNuMuFlux11   ) : return "f_fhc_flux_numu11";    break;
    case (kNuisFHCNuMuFlux12   ) : return "f_fhc_flux_numu12";    break;
    case (kNuisFHCNuMuFlux13   ) : return "f_fhc_flux_numu13";    break;
    case (kNuisFHCNuMuFlux14   ) : return "f_fhc_flux_numu14";    break;
    case (kNuisFHCNuMuFlux15   ) : return "f_fhc_flux_numu15";    break;
    case (kNuisFHCNuMuFlux16   ) : return "f_fhc_flux_numu16";    break;
    case (kNuisFHCNuMuFlux17   ) : return "f_fhc_flux_numu17";    break;
    case (kNuisFHCNuMuFlux18   ) : return "f_fhc_flux_numu18";    break;
    case (kNuisFHCNuMuBarFlux00) : return "f_fhc_flux_numubar00"; break;
    case (kNuisFHCNuMuBarFlux01) : return "f_fhc_flux_numubar01"; break;
    case (kNuisFHCNuMuBarFlux02) : return "f_fhc_flux_numubar02"; break;
    case (kNuisFHCNuMuBarFlux03) : return "f_fhc_flux_numubar03"; break;
    case (kNuisFHCNuMuBarFlux04) : return "f_fhc_flux_numubar04"; break;
    case (kNuisFHCNuMuBarFlux05) : return "f_fhc_flux_numubar05"; break;
    case (kNuisFHCNuMuBarFlux06) : return "f_fhc_flux_numubar06"; break;
    case (kNuisFHCNuMuBarFlux07) : return "f_fhc_flux_numubar07"; break;
    case (kNuisFHCNuMuBarFlux08) : return "f_fhc_flux_numubar08"; break;
    case (kNuisFHCNuMuBarFlux09) : return "f_fhc_flux_numubar09"; break;
    case (kNuisFHCNuMuBarFlux10) : return "f_fhc_flux_numubar10"; break;
    case (kNuisFHCNuMuBarFlux11) : return "f_fhc_flux_numubar11"; break;
    case (kNuisFHCNuMuBarFlux12) : return "f_fhc_flux_numubar12"; break;
    case (kNuisFHCNuMuBarFlux13) : return "f_fhc_flux_numubar13"; break;
    case (kNuisFHCNuMuBarFlux14) : return "f_fhc_flux_numubar14"; break;
    case (kNuisFHCNuMuBarFlux15) : return "f_fhc_flux_numubar15"; break;
    case (kNuisFHCNuMuBarFlux16) : return "f_fhc_flux_numubar16"; break;
    case (kNuisFHCNuMuBarFlux17) : return "f_fhc_flux_numubar17"; break;
    case (kNuisFHCNuMuBarFlux18) : return "f_fhc_flux_numubar18"; break;
    case (kNuisFHCNuEFlux00    ) : return "f_fhc_flux_nue00";     break;
    case (kNuisFHCNuEFlux01    ) : return "f_fhc_flux_nue01";     break;
    case (kNuisFHCNuEFlux02    ) : return "f_fhc_flux_nue02";     break;
    case (kNuisFHCNuEFlux03    ) : return "f_fhc_flux_nue03";     break;
    case (kNuisFHCNuEFlux04    ) : return "f_fhc_flux_nue04";     break;
    case (kNuisFHCNuEFlux05    ) : return "f_fhc_flux_nue05";     break;
    case (kNuisFHCNuEFlux06    ) : return "f_fhc_flux_nue06";     break;
    case (kNuisFHCNuEBarFlux00 ) : return "f_fhc_flux_nuebar00";  break;
    case (kNuisFHCNuEBarFlux01 ) : return "f_fhc_flux_nuebar01";  break;
    case (kNuisFHCNuEBarFlux02 ) : return "f_fhc_flux_nuebar02";  break;
    case (kNuisFHCNuEBarFlux03 ) : return "f_fhc_flux_nuebar03";  break;
    case (kNuisFHCNuEBarFlux04 ) : return "f_fhc_flux_nuebar04";  break;
    case (kNuisFHCNuEBarFlux05 ) : return "f_fhc_flux_nuebar05";  break;
    case (kNuisFHCNuEBarFlux06 ) : return "f_fhc_flux_nuebar06";  break;

    case (kNuisRHCNuMuFlux00   ) : return "f_rhc_flux_numu00";    break;
    case (kNuisRHCNuMuFlux01   ) : return "f_rhc_flux_numu01";    break;
    case (kNuisRHCNuMuFlux02   ) : return "f_rhc_flux_numu02";    break;
    case (kNuisRHCNuMuFlux03   ) : return "f_rhc_flux_numu03";    break;
    case (kNuisRHCNuMuFlux04   ) : return "f_rhc_flux_numu04";    break;
    case (kNuisRHCNuMuFlux05   ) : return "f_rhc_flux_numu05";    break;
    case (kNuisRHCNuMuFlux06   ) : return "f_rhc_flux_numu06";    break;
    case (kNuisRHCNuMuFlux07   ) : return "f_rhc_flux_numu07";    break;
    case (kNuisRHCNuMuFlux08   ) : return "f_rhc_flux_numu08";    break;
    case (kNuisRHCNuMuFlux09   ) : return "f_rhc_flux_numu09";    break;
    case (kNuisRHCNuMuFlux10   ) : return "f_rhc_flux_numu10";    break;
    case (kNuisRHCNuMuFlux11   ) : return "f_rhc_flux_numu11";    break;
    case (kNuisRHCNuMuFlux12   ) : return "f_rhc_flux_numu12";    break;
    case (kNuisRHCNuMuFlux13   ) : return "f_rhc_flux_numu13";    break;
    case (kNuisRHCNuMuFlux14   ) : return "f_rhc_flux_numu14";    break;
    case (kNuisRHCNuMuFlux15   ) : return "f_rhc_flux_numu15";    break;
    case (kNuisRHCNuMuFlux16   ) : return "f_rhc_flux_numu16";    break;
    case (kNuisRHCNuMuFlux17   ) : return "f_rhc_flux_numu17";    break;
    case (kNuisRHCNuMuFlux18   ) : return "f_rhc_flux_numu18";    break;
    case (kNuisRHCNuMuBarFlux00) : return "f_rhc_flux_numubar00"; break;
    case (kNuisRHCNuMuBarFlux01) : return "f_rhc_flux_numubar01"; break;
    case (kNuisRHCNuMuBarFlux02) : return "f_rhc_flux_numubar02"; break;
    case (kNuisRHCNuMuBarFlux03) : return "f_rhc_flux_numubar03"; break;
    case (kNuisRHCNuMuBarFlux04) : return "f_rhc_flux_numubar04"; break;
    case (kNuisRHCNuMuBarFlux05) : return "f_rhc_flux_numubar05"; break;
    case (kNuisRHCNuMuBarFlux06) : return "f_rhc_flux_numubar06"; break;
    case (kNuisRHCNuMuBarFlux07) : return "f_rhc_flux_numubar07"; break;
    case (kNuisRHCNuMuBarFlux08) : return "f_rhc_flux_numubar08"; break;
    case (kNuisRHCNuMuBarFlux09) : return "f_rhc_flux_numubar09"; break;
    case (kNuisRHCNuMuBarFlux10) : return "f_rhc_flux_numubar10"; break;
    case (kNuisRHCNuMuBarFlux11) : return "f_rhc_flux_numubar11"; break;
    case (kNuisRHCNuMuBarFlux12) : return "f_rhc_flux_numubar12"; break;
    case (kNuisRHCNuMuBarFlux13) : return "f_rhc_flux_numubar13"; break;
    case (kNuisRHCNuMuBarFlux14) : return "f_rhc_flux_numubar14"; break;
    case (kNuisRHCNuMuBarFlux15) : return "f_rhc_flux_numubar15"; break;
    case (kNuisRHCNuMuBarFlux16) : return "f_rhc_flux_numubar16"; break;
    case (kNuisRHCNuMuBarFlux17) : return "f_rhc_flux_numubar17"; break;
    case (kNuisRHCNuMuBarFlux18) : return "f_rhc_flux_numubar18"; break;
    case (kNuisRHCNuEFlux00    ) : return "f_rhc_flux_nue00";     break;
    case (kNuisRHCNuEFlux01    ) : return "f_rhc_flux_nue01";     break;
    case (kNuisRHCNuEFlux02    ) : return "f_rhc_flux_nue02";     break;
    case (kNuisRHCNuEFlux03    ) : return "f_rhc_flux_nue03";     break;
    case (kNuisRHCNuEFlux04    ) : return "f_rhc_flux_nue04";     break;
    case (kNuisRHCNuEFlux05    ) : return "f_rhc_flux_nue05";     break;
    case (kNuisRHCNuEFlux06    ) : return "f_rhc_flux_nue06";     break;
    case (kNuisRHCNuEBarFlux00 ) : return "f_rhc_flux_nuebar00";  break;
    case (kNuisRHCNuEBarFlux01 ) : return "f_rhc_flux_nuebar01";  break;
    case (kNuisRHCNuEBarFlux02 ) : return "f_rhc_flux_nuebar02";  break;
    case (kNuisRHCNuEBarFlux03 ) : return "f_rhc_flux_nuebar03";  break;
    case (kNuisRHCNuEBarFlux04 ) : return "f_rhc_flux_nuebar04";  break;
    case (kNuisRHCNuEBarFlux05 ) : return "f_rhc_flux_nuebar05";  break;
    case (kNuisRHCNuEBarFlux06 ) : return "f_rhc_flux_nuebar06";  break;

    case (kNuisNormCCQE        ) : return "f_ccqe";               break;
    case (kNuisNormCC1piC      ) : return "f_cc1pic";             break;
    case (kNuisNormCC1pi0      ) : return "f_cc1pi0";             break;
    case (kNuisNormCCoth       ) : return "f_ccoth";              break;
    case (kNuisNormNC          ) : return "f_nc";                 break;
    case (kNuisRatioNuENuMu    ) : return "f_nuecc_numucc";       break;

    case (kNuisEffNuMuCC1trkQE  ) : return "f_eff_numucc1trkqe";   break;
    case (kNuisEffNuMuCC2trkQE  ) : return "f_eff_numucc2trkqe";   break;
    case (kNuisEffNuMuCC1piC    ) : return "f_eff_numucc1pic";     break;
    case (kNuisEffNuMuCC1pi0    ) : return "f_eff_numucc1pi0";     break;
    case (kNuisEffNuMuCC1piC1pi0) : return "f_eff_numucc1pic1pi0"; break;
    case (kNuisEffNuMuCCoth     ) : return "f_eff_numuccoth";      break;
    case (kNuisEffNuECC         ) : return "f_eff_nuecc";          break;
    case (kNuisEffNuMuCCWSgn    ) : return "f_eff_numuccwsgn";     break;
    case (kNuisEffNC            ) : return "f_eff_nc";             break;
    
    case ( kNuisIntNuCCQE1         ) : return "f_int_nu_ccqe_1"; 
    case ( kNuisIntNuCCQE2         ) : return "f_int_nu_ccqe_2"; 
    case ( kNuisIntNuCCQE3         ) : return "f_int_nu_ccqe_3"; 
    case ( kNuisIntNuBarCCQE1      ) : return "f_int_nubar_ccqe_1"; 
    case ( kNuisIntNuBarCCQE2      ) : return "f_int_nubar_ccqe_2"; 
    case ( kNuisIntNuBarCCQE3      ) : return "f_int_nubar_ccqe_3"; 
    
    case ( kNuisIntNuCC1piz1       ) : return "f_int_nu_cc1piz1"; 
    case ( kNuisIntNuCC1piz2       ) : return "f_int_nu_cc1piz2"; 
    case ( kNuisIntNuCC1piz3       ) : return "f_int_nu_cc1piz3"; 
    case ( kNuisIntNuCC1pic1       ) : return "f_int_nu_cc1pic1"; 
    case ( kNuisIntNuCC1pic2       ) : return "f_int_nu_cc1pic2"; 
    case ( kNuisIntNuCC1pic3       ) : return "f_int_nu_cc1pic3"; 
    
    case ( kNuisIntNuBarCC1piz1    ) : return "f_int_nubar_1piz1"; 
    case ( kNuisIntNuBarCC1piz2    ) : return "f_int_nubar_1piz2"; 
    case ( kNuisIntNuBarCC1piz3    ) : return "f_int_nubar_1piz3"; 
    case ( kNuisIntNuBarCC1pic1    ) : return "f_int_nubar_1pic1"; 
    case ( kNuisIntNuBarCC1pic2    ) : return "f_int_nubar_1pic2"; 
    case ( kNuisIntNuBarCC1pic3    ) : return "f_int_nubar_1pic3"; 
    
    case ( kNuisIntNuMultiPi1      ) : return "f_int_nu_npi1"; 
    case ( kNuisIntNuMultiPi2      ) : return "f_int_nu_npi2"; 
    case ( kNuisIntNuMultiPi3      ) : return "f_int_nu_npi3"; 
    case ( kNuisIntNuBarMultiPi1   ) : return "f_int_nubar_npi1"; 
    case ( kNuisIntNuBarMultiPi2   ) : return "f_int_nubar_npi2"; 
    case ( kNuisIntNuBarMultiPi3   ) : return "f_int_nubar_npi3"; 
    
    case ( kNuisIntNormMEC         ) : return "f_int_mec"; 
    case ( kNuisIntNormCoherent    ) : return "f_int_coh"; 
    case ( kNuisIntNormCCOther     ) : return "f_int_ccoth"; 
    case ( kNuisIntNormNC          ) : return "f_int_nc"; 
    case ( kNuisIntNormNuMuToNuE   ) : return "f_int_numutonue"; 
    case ( kNuisIntNormNuBarToNu   ) : return "f_int_nubartonu"; 
    case ( kNuisIntNucMeanFreePath ) : return "f_int_nucmfp"; 
    case ( kNuisIntPiMeanFreePath  ) : return "f_int_pimfp"; 
    case ( kNuisIntPiChargeExchange) : return "f_int_pichargeex"; 
    case ( kNuisIntPiAbsorb        ) : return "f_int_piabsorb"; 
    case ( kNuisIntPiInelastic     ) : return "f_int_piinelastic"; 
    case ( kNuisIntHadronization   ) : return "f_int_hadron";    
    
    default                       : return util::RawParamAsString(p);   
  }
  return "";
}
//________________________________________________________________________________________
string util::AsStringTeX(conv::PhysParamId_t p, bool root)
{
  string name = "";

  switch(p) {
    case (kNuisFHCNuMuFlux00   ) : name = "f_{FHC;\\nu_{\\mu};00}";                        break;
    case (kNuisFHCNuMuFlux01   ) : name = "f_{FHC;\\nu_{\\mu};01}";                        break;
    case (kNuisFHCNuMuFlux02   ) : name = "f_{FHC;\\nu_{\\mu};02}";                        break;
    case (kNuisFHCNuMuFlux03   ) : name = "f_{FHC;\\nu_{\\mu};03}";                        break;
    case (kNuisFHCNuMuFlux04   ) : name = "f_{FHC;\\nu_{\\mu};04}";                        break;
    case (kNuisFHCNuMuFlux05   ) : name = "f_{FHC;\\nu_{\\mu};05}";                        break;
    case (kNuisFHCNuMuFlux06   ) : name = "f_{FHC;\\nu_{\\mu};06}";                        break;
    case (kNuisFHCNuMuFlux07   ) : name = "f_{FHC;\\nu_{\\mu};07}";                        break;
    case (kNuisFHCNuMuFlux08   ) : name = "f_{FHC;\\nu_{\\mu};08}";                        break;
    case (kNuisFHCNuMuFlux09   ) : name = "f_{FHC;\\nu_{\\mu};09}";                        break;
    case (kNuisFHCNuMuFlux10   ) : name = "f_{FHC;\\nu_{\\mu};10}";                        break;
    case (kNuisFHCNuMuFlux11   ) : name = "f_{FHC;\\nu_{\\mu};11}";                        break;
    case (kNuisFHCNuMuFlux12   ) : name = "f_{FHC;\\nu_{\\mu};12}";                        break;
    case (kNuisFHCNuMuFlux13   ) : name = "f_{FHC;\\nu_{\\mu};13}";                        break;
    case (kNuisFHCNuMuFlux14   ) : name = "f_{FHC;\\nu_{\\mu};14}";                        break;
    case (kNuisFHCNuMuFlux15   ) : name = "f_{FHC;\\nu_{\\mu};15}";                        break;
    case (kNuisFHCNuMuFlux16   ) : name = "f_{FHC;\\nu_{\\mu};16}";                        break;
    case (kNuisFHCNuMuFlux17   ) : name = "f_{FHC;\\nu_{\\mu};17}";                        break;
    case (kNuisFHCNuMuFlux18   ) : name = "f_{FHC;\\nu_{\\mu};18}";                        break;
    case (kNuisFHCNuMuBarFlux00) : name = "f_{FHC;\\bar{\\nu_{\\mu}};00}";                 break;
    case (kNuisFHCNuMuBarFlux01) : name = "f_{FHC;\\bar{\\nu_{\\mu}};01}";                 break;
    case (kNuisFHCNuMuBarFlux02) : name = "f_{FHC;\\bar{\\nu_{\\mu}};02}";                 break;
    case (kNuisFHCNuMuBarFlux03) : name = "f_{FHC;\\bar{\\nu_{\\mu}};03}";                 break;
    case (kNuisFHCNuMuBarFlux04) : name = "f_{FHC;\\bar{\\nu_{\\mu}};04}";                 break;
    case (kNuisFHCNuMuBarFlux05) : name = "f_{FHC;\\bar{\\nu_{\\mu}};05}";                 break;
    case (kNuisFHCNuMuBarFlux06) : name = "f_{FHC;\\bar{\\nu_{\\mu}};06}";                 break;
    case (kNuisFHCNuMuBarFlux07) : name = "f_{FHC;\\bar{\\nu_{\\mu}};07}";                 break;
    case (kNuisFHCNuMuBarFlux08) : name = "f_{FHC;\\bar{\\nu_{\\mu}};08}";                 break;
    case (kNuisFHCNuMuBarFlux09) : name = "f_{FHC;\\bar{\\nu_{\\mu}};09}";                 break;
    case (kNuisFHCNuMuBarFlux10) : name = "f_{FHC;\\bar{\\nu_{\\mu}};10}";                 break;
    case (kNuisFHCNuMuBarFlux11) : name = "f_{FHC;\\bar{\\nu_{\\mu}};11}";                 break;
    case (kNuisFHCNuMuBarFlux12) : name = "f_{FHC;\\bar{\\nu_{\\mu}};12}";                 break;
    case (kNuisFHCNuMuBarFlux13) : name = "f_{FHC;\\bar{\\nu_{\\mu}};13}";                 break;
    case (kNuisFHCNuMuBarFlux14) : name = "f_{FHC;\\bar{\\nu_{\\mu}};14}";                 break;
    case (kNuisFHCNuMuBarFlux15) : name = "f_{FHC;\\bar{\\nu_{\\mu}};15}";                 break;
    case (kNuisFHCNuMuBarFlux16) : name = "f_{FHC;\\bar{\\nu_{\\mu}};16}";                 break;
    case (kNuisFHCNuMuBarFlux17) : name = "f_{FHC;\\bar{\\nu_{\\mu}};17}";                 break;
    case (kNuisFHCNuMuBarFlux18) : name = "f_{FHC;\\bar{\\nu_{\\mu}};18}";                 break;
    case (kNuisFHCNuEFlux00    ) : name = "f_{FHC;\\nu_{e};00}";                           break;
    case (kNuisFHCNuEFlux01    ) : name = "f_{FHC;\\nu_{e};01}";                           break;
    case (kNuisFHCNuEFlux02    ) : name = "f_{FHC;\\nu_{e};02}";                           break;
    case (kNuisFHCNuEFlux03    ) : name = "f_{FHC;\\nu_{e};03}";                           break;
    case (kNuisFHCNuEFlux04    ) : name = "f_{FHC;\\nu_{e};04}";                           break;
    case (kNuisFHCNuEFlux05    ) : name = "f_{FHC;\\nu_{e};05}";                           break;
    case (kNuisFHCNuEFlux06    ) : name = "f_{FHC;\\nu_{e};06}";                           break;
    case (kNuisFHCNuEBarFlux00 ) : name = "f_{FHC;\\bar{\\nu_{e}};00}";                    break;
    case (kNuisFHCNuEBarFlux01 ) : name = "f_{FHC;\\bar{\\nu_{e}};01}";                    break;
    case (kNuisFHCNuEBarFlux02 ) : name = "f_{FHC;\\bar{\\nu_{e}};02}";                    break;
    case (kNuisFHCNuEBarFlux03 ) : name = "f_{FHC;\\bar{\\nu_{e}};03}";                    break;
    case (kNuisFHCNuEBarFlux04 ) : name = "f_{FHC;\\bar{\\nu_{e}};04}";                    break;
    case (kNuisFHCNuEBarFlux05 ) : name = "f_{FHC;\\bar{\\nu_{e}};05}";                    break;
    case (kNuisFHCNuEBarFlux06 ) : name = "f_{FHC;\\bar{\\nu_{e}};06}";                    break;
    
    case (kNuisRHCNuMuFlux00   ) : name = "f_{RHC;\\nu_{\\mu};00}";                        break;
    case (kNuisRHCNuMuFlux01   ) : name = "f_{RHC;\\nu_{\\mu};01}";                        break;
    case (kNuisRHCNuMuFlux02   ) : name = "f_{RHC;\\nu_{\\mu};02}";                        break;
    case (kNuisRHCNuMuFlux03   ) : name = "f_{RHC;\\nu_{\\mu};03}";                        break;
    case (kNuisRHCNuMuFlux04   ) : name = "f_{RHC;\\nu_{\\mu};04}";                        break;
    case (kNuisRHCNuMuFlux05   ) : name = "f_{RHC;\\nu_{\\mu};05}";                        break;
    case (kNuisRHCNuMuFlux06   ) : name = "f_{RHC;\\nu_{\\mu};06}";                        break;
    case (kNuisRHCNuMuFlux07   ) : name = "f_{RHC;\\nu_{\\mu};07}";                        break;
    case (kNuisRHCNuMuFlux08   ) : name = "f_{RHC;\\nu_{\\mu};08}";                        break;
    case (kNuisRHCNuMuFlux09   ) : name = "f_{RHC;\\nu_{\\mu};09}";                        break;
    case (kNuisRHCNuMuFlux10   ) : name = "f_{RHC;\\nu_{\\mu};10}";                        break;
    case (kNuisRHCNuMuFlux11   ) : name = "f_{RHC;\\nu_{\\mu};11}";                        break;
    case (kNuisRHCNuMuFlux12   ) : name = "f_{RHC;\\nu_{\\mu};12}";                        break;
    case (kNuisRHCNuMuFlux13   ) : name = "f_{RHC;\\nu_{\\mu};13}";                        break;
    case (kNuisRHCNuMuFlux14   ) : name = "f_{RHC;\\nu_{\\mu};14}";                        break;
    case (kNuisRHCNuMuFlux15   ) : name = "f_{RHC;\\nu_{\\mu};15}";                        break;
    case (kNuisRHCNuMuFlux16   ) : name = "f_{RHC;\\nu_{\\mu};16}";                        break;
    case (kNuisRHCNuMuFlux17   ) : name = "f_{RHC;\\nu_{\\mu};17}";                        break;
    case (kNuisRHCNuMuFlux18   ) : name = "f_{RHC;\\nu_{\\mu};18}";                        break;
    case (kNuisRHCNuMuBarFlux00) : name = "f_{RHC;\\bar{\\nu_{\\mu}};00}";                 break;
    case (kNuisRHCNuMuBarFlux01) : name = "f_{RHC;\\bar{\\nu_{\\mu}};01}";                 break;
    case (kNuisRHCNuMuBarFlux02) : name = "f_{RHC;\\bar{\\nu_{\\mu}};02}";                 break;
    case (kNuisRHCNuMuBarFlux03) : name = "f_{RHC;\\bar{\\nu_{\\mu}};03}";                 break;
    case (kNuisRHCNuMuBarFlux04) : name = "f_{RHC;\\bar{\\nu_{\\mu}};04}";                 break;
    case (kNuisRHCNuMuBarFlux05) : name = "f_{RHC;\\bar{\\nu_{\\mu}};05}";                 break;
    case (kNuisRHCNuMuBarFlux06) : name = "f_{RHC;\\bar{\\nu_{\\mu}};06}";                 break;
    case (kNuisRHCNuMuBarFlux07) : name = "f_{RHC;\\bar{\\nu_{\\mu}};07}";                 break;
    case (kNuisRHCNuMuBarFlux08) : name = "f_{RHC;\\bar{\\nu_{\\mu}};08}";                 break;
    case (kNuisRHCNuMuBarFlux09) : name = "f_{RHC;\\bar{\\nu_{\\mu}};09}";                 break;
    case (kNuisRHCNuMuBarFlux10) : name = "f_{RHC;\\bar{\\nu_{\\mu}};10}";                 break;
    case (kNuisRHCNuMuBarFlux11) : name = "f_{RHC;\\bar{\\nu_{\\mu}};11}";                 break;
    case (kNuisRHCNuMuBarFlux12) : name = "f_{RHC;\\bar{\\nu_{\\mu}};12}";                 break;
    case (kNuisRHCNuMuBarFlux13) : name = "f_{RHC;\\bar{\\nu_{\\mu}};13}";                 break;
    case (kNuisRHCNuMuBarFlux14) : name = "f_{RHC;\\bar{\\nu_{\\mu}};14}";                 break;
    case (kNuisRHCNuMuBarFlux15) : name = "f_{RHC;\\bar{\\nu_{\\mu}};15}";                 break;
    case (kNuisRHCNuMuBarFlux16) : name = "f_{RHC;\\bar{\\nu_{\\mu}};16}";                 break;
    case (kNuisRHCNuMuBarFlux17) : name = "f_{RHC;\\bar{\\nu_{\\mu}};17}";                 break;
    case (kNuisRHCNuMuBarFlux18) : name = "f_{RHC;\\bar{\\nu_{\\mu}};18}";                 break;
    case (kNuisRHCNuEFlux00    ) : name = "f_{RHC;\\nu_{e};00}";                           break;
    case (kNuisRHCNuEFlux01    ) : name = "f_{RHC;\\nu_{e};01}";                           break;
    case (kNuisRHCNuEFlux02    ) : name = "f_{RHC;\\nu_{e};02}";                           break;
    case (kNuisRHCNuEFlux03    ) : name = "f_{RHC;\\nu_{e};03}";                           break;
    case (kNuisRHCNuEFlux04    ) : name = "f_{RHC;\\nu_{e};04}";                           break;
    case (kNuisRHCNuEFlux05    ) : name = "f_{RHC;\\nu_{e};05}";                           break;
    case (kNuisRHCNuEFlux06    ) : name = "f_{RHC;\\nu_{e};06}";                           break;
    case (kNuisRHCNuEBarFlux00 ) : name = "f_{RHC;\\bar{\\nu_{e}};00}";                    break;
    case (kNuisRHCNuEBarFlux01 ) : name = "f_{RHC;\\bar{\\nu_{e}};01}";                    break;
    case (kNuisRHCNuEBarFlux02 ) : name = "f_{RHC;\\bar{\\nu_{e}};02}";                    break;
    case (kNuisRHCNuEBarFlux03 ) : name = "f_{RHC;\\bar{\\nu_{e}};03}";                    break;
    case (kNuisRHCNuEBarFlux04 ) : name = "f_{RHC;\\bar{\\nu_{e}};04}";                    break;
    case (kNuisRHCNuEBarFlux05 ) : name = "f_{RHC;\\bar{\\nu_{e}};05}";                    break;
    case (kNuisRHCNuEBarFlux06 ) : name = "f_{RHC;\\bar{\\nu_{e}};06}";                    break;
    
    case (kNuisNormCCQE        ) : name = "f_{CCQE}";                                      break;
    case (kNuisNormCC1piC      ) : name = "f_{CC1\\pi^{\\pm}}";                            break;
    case (kNuisNormCC1pi0      ) : name = "f_{CC1\\pi^{0}}";                               break;
    case (kNuisNormCCoth       ) : name = "f_{CCother}";                                   break;
    case (kNuisNormNC          ) : name = "f_{NC}";                                        break;
    case (kNuisRatioNuENuMu    ) : name = "f_{\\nu_{e}/\\nu_{\\mu}}";                      break;
    
    case (kNuisEffNuMuCC1trkQE  ) : name = "f_{eff;\\nu_{\\mu}CC;1trkQE}";                 break;
    case (kNuisEffNuMuCC2trkQE  ) : name = "f_{eff;\\nu_{\\mu}CC;2trkQE}";                 break;
    case (kNuisEffNuMuCC1piC    ) : name = "f_{eff;\\nu_{\\mu}CC;1\\pi^{\\pm}}";           break;
    case (kNuisEffNuMuCC1pi0    ) : name = "f_{eff;\\nu_{\\mu}CC;1\\pi^{0}}";              break;
    case (kNuisEffNuMuCC1piC1pi0) : name = "f_{eff;\\nu_{\\mu}CC;1\\pi^{\\pm}1\\pi^{0}}";  break;
    case (kNuisEffNuMuCCoth     ) : name = "f_{eff;\\nu_{\\mu}CC;other}";                  break;
    case (kNuisEffNuECC         ) : name = "f_{eff;\\nu_{e}CC}";                           break;
    case (kNuisEffNuMuCCWSgn    ) : name = "f_{eff;\\nu_{\\mu}CC;wsgn}";                   break;
    case (kNuisEffNC            ) : name = "f_{eff;NC}";                                   break;
    
    case ( kNuisIntNuCCQE1         ) : name =  "f_{\\nu CCQE 1}";                          break;
    case ( kNuisIntNuCCQE2         ) : name =  "f_{\\nu CCQE 2}";                          break;
    case ( kNuisIntNuCCQE3         ) : name =  "f_{\\nu CCQE 3}";                          break;
    case ( kNuisIntNuBarCCQE1      ) : name =  "f_{\\bar{\\nu} CCQE 1}";                   break;
    case ( kNuisIntNuBarCCQE2      ) : name =  "f_{\\bar{\\nu} CCQE 2}";                   break;
    case ( kNuisIntNuBarCCQE3      ) : name =  "f_{\\bar{\\nu} CCQE 3}";                   break;
    
    case ( kNuisIntNuCC1piz1       ) : name =  "f_{\\nu CC1\\pi^{0} 1}";                   break;
    case ( kNuisIntNuCC1piz2       ) : name =  "f_{\\nu CC1\\pi^{0} 2}";                   break;
    case ( kNuisIntNuCC1piz3       ) : name =  "f_{\\nu CC1\\pi^{0} 3}";                   break;
    case ( kNuisIntNuCC1pic1       ) : name =  "f_{\\nu CC1\\pi^{\\pm} 1}";                 break;
    case ( kNuisIntNuCC1pic2       ) : name =  "f_{\\nu CC1\\pi^{\\pm} 2}";                 break;
    case ( kNuisIntNuCC1pic3       ) : name =  "f_{\\nu CC1\\pi^{\\pm} 3}";                 break;
    
    case ( kNuisIntNuBarCC1piz1    ) : name =  "f_{\\bar{\\nu} CC1\\pi^{0} 1}";             break;
    case ( kNuisIntNuBarCC1piz2    ) : name =  "f_{\\bar{\\nu} CC1\\pi^{0} 2}";             break;
    case ( kNuisIntNuBarCC1piz3    ) : name =  "f_{\\bar{\\nu} CC1\\pi^{0} 3}";             break;
    case ( kNuisIntNuBarCC1pic1    ) : name =  "f_{\\bar{\\nu} CC1\\pi^{\\pm} 1}";           break;
    case ( kNuisIntNuBarCC1pic2    ) : name =  "f_{\\bar{\\nu} CC1\\pi^{\\pm} 2}";           break;
    case ( kNuisIntNuBarCC1pic3    ) : name =  "f_{\\bar{\\nu} CC1\\pi^{\\pm} 3}";           break;
    
    case ( kNuisIntNuMultiPi1      ) : name =  "f_{\\nu n\\pi 1}";                         break;
    case ( kNuisIntNuMultiPi2      ) : name =  "f_{\\nu n\\pi 2}";                         break;
    case ( kNuisIntNuMultiPi3      ) : name =  "f_{\\nu n\\pi 3}";                         break;
    case ( kNuisIntNuBarMultiPi1   ) : name =  "f_{\\bar{\\nu} n\\pi 1}";                  break;
    case ( kNuisIntNuBarMultiPi2   ) : name =  "f_{\\bar{\\nu} n\\pi 2}";                  break;
    case ( kNuisIntNuBarMultiPi3   ) : name =  "f_{\\bar{\\nu} n\\pi 3}";                  break;
    
    case ( kNuisIntNormMEC         ) : name =  "f_{MEC}";                                  break;
    case ( kNuisIntNormCoherent    ) : name =  "f_{Coh}";                                  break;
    case ( kNuisIntNormCCOther     ) : name =  "f_{CC other}";                             break;
    case ( kNuisIntNormNC          ) : name =  "f_{NC}";                                   break;
    case ( kNuisIntNormNuMuToNuE   ) : name =  "f_{\\nu_{\\mu} \\rightarrow \\nu_{e}}";    break;
    case ( kNuisIntNormNuBarToNu   ) : name =  "f_{\\bar{\\nu} \\rightarrow \\nu}";        break;
    case ( kNuisIntNucMeanFreePath ) : name =  "f_{n \\lambda}";                           break;
    case ( kNuisIntPiMeanFreePath  ) : name =  "f_{\\pi \\lambda}";                        break;
    case ( kNuisIntPiChargeExchange) : name =  "f_{\\pi charge ex}";                       break;
    case ( kNuisIntPiAbsorb        ) : name =  "f_{\\pi absorb}";                          break;
    case ( kNuisIntPiInelastic     ) : name =  "f_{\\pi inelastic}";                       break;
    case ( kNuisIntHadronization   ) : name =  "f_{\\eta}";                                break;

    default                       : name = "--";    
  }
  
  if(root) {
    replace( name.begin(), name.end(), '\\', '#' ); // Make slashes hashes for RooTeX
    // Get rid of hashes preceding sin
    size_t ind = name.find("#sin",0);
    if (ind !=  string::npos) (name.replace(ind,4," sin"));
    return util::TrimSpaces(name);
  }
  
  return name;
}
//________________________________________________________________________________________
string util::ParamAsString    (conv::PhysParamId_t p)            {return util::AsString   (p);     };
string util::ParamAsStringTeX (conv::PhysParamId_t p, bool root) {return util::AsStringTeX(p,root);};
//________________________________________________________________________________________
PhysParamId_t util::NDPhysParamFromString(string inp_name)
{
  for(int ip = 0; ip < kNNDFitParams; ip++) {
     PhysParamId_t p = kNDFitParam[ip];
     string name = util::AsString(p);
     if(name == inp_name) return p;
  }
  return kPhypUndefined;
}
//________________________________________________________________________________________
PhysHypothesis util::GetPhysHypothesis(Option_t * param_list)
{
// Create a PhysHypothesis object, adding all physics + nuisance params
// The input option specifies both the set of parameters (eg "standard") 

  PhysHypothesis ph(kHypVoid); 

  string param_list_opt   = ((param_list)   ? param_list   : "standard");

  LOG("NDFitParams", pNOTICE) 
    << "Instantiating a physics hypothesis object with option: " << param_list_opt;

  //
  // Get the standard set of parameters
  //

  if(param_list_opt.find("standard") != string::npos) {
    for(int ip = 0; ip < kNNDFitParams; ip++) {
      PhysParamId_t p = kNDFitParam[ip];
      if(p == kPhypUndefined) continue;

      // skip detector params?
      bool skip_detector_params = (param_list_opt.find("no-detector-systematics") != string::npos);
      if(skip_detector_params && kNDFitIsNuDetRelated[ip]) continue;

    }//ip
  }

  return ph;
}
//________________________________________________________________________________________
FitParamList * util::GetFitParameterList (Option_t * param_list)
{
// Create a FitParamList object, adding all physics + nuisance params.
// The input option specifies both the set of parameters (eg "standard") 

  string param_list_opt   = ((param_list)   ? param_list   : "standard");

  LOG("NDFitParams", pNOTICE)
    << "Instantiating a  fit parameter list object with option: " << param_list_opt;

  FitParamList * fparm = 0;

  //
  // Get the standard set of parameters
  //

  // include params 
  if(param_list_opt.find("standard") != string::npos) {

    fparm = new FitParamList(kNNDFitParams); // NOTE: If params are undefined, we initialize the array with more elements than used --- 

    int ipc = 0; //counter with no gaps, in case of `kPhypUndefined' params
    for(int ip = 0; ip < kNNDFitParams; ip++) {
      PhysParamId_t p = kNDFitParam[ip];
      if(p == kPhypUndefined) continue;

      // set parameter range, current and init value, etc
      double init = 1.0;
      double curr = 1.0;
      double min  = 0.0;
      double max  = 2.0;
      double step = 1E-4;
      bool   fix  = false;
      bool   nuis = true;

      fparm->AddParam(ipc, p, init, min, max, step, fix, nuis);    
      ipc++; 
      fparm->Update(p, curr);

      // toggle detector related params on/off
      bool no_detector_params = (param_list_opt.find("fix-det-syst") != string::npos);
      if(no_detector_params && kNDFitIsNuDetRelated[ip]) {
       fparm->Update(p, 1.);
       fparm->SetInitValue(p, 1.);
       fparm->FixParameter(p);
      }
      // toggle flux related params on/off
      bool no_flux_params = (param_list_opt.find("fix-flux-syst") != string::npos);
      if(no_flux_params && kNDFitIsNuFluxRelated[ip]) {
       fparm->Update(p, 1.);
       fparm->SetInitValue(p, 1.);
       fparm->FixParameter(p);
      }
      // toggle int related params on/off
      bool no_int_params = (param_list_opt.find("fix-int-syst") != string::npos);
      if(no_int_params && kNDFitIsNuIntRelated[ip]) {
       fparm->Update(p, 1.);
       fparm->SetInitValue(p, 1.);
       fparm->FixParameter(p);
      }

    }//ip
  }
  
  if(!fparm->IsComplete()) {
    LOG("NDFitParams",pERROR)<<"Fit parameter list is not complete";
    fparm->Print();
    util::Die(-1);
  }

  return fparm;
}
//________________________________________________________________________________________
void valor::util::PopulateNameRegistry(void)
{
  NameRegistry * nr = util::NameRegistry::MutableInstance();
  
  for (int ip = -1 ; ip < conv::kLastNuisParam; ip++) {
    conv::PhysParamId_t p = (conv::PhysParamId_t)ip;
    nr->fParamNames      [p] = util::AsString(p);
    nr->fParamNamesSimple[p] = util::AsString(p); // If we start using proper names, will change this.
  }
  return;
}
//____________________________________________________________________________
bool valor::util::IsNuFluxRelated(conv::PhysParamId_t p)
{
  int nd_index = NDArrIdx::Instance()->NDFitParamIdx(p);
  if (nd_index==-1) {
    return false;
  }
  return conv::kNDFitIsNuFluxRelated[nd_index];
}
//____________________________________________________________________________
bool valor::util::IsNuIntRelated(conv::PhysParamId_t p)
{
  int nd_index = NDArrIdx::Instance()->NDFitParamIdx(p);
  if (nd_index==-1) {
    return false;
  }
  return conv::kNDFitIsNuIntRelated[nd_index];
}
//____________________________________________________________________________
bool valor::util::IsNuDetRelated(conv::PhysParamId_t p)
{
  int nd_index = NDArrIdx::Instance()->NDFitParamIdx(p);
  if (nd_index==-1) {
    return false;
  }
  return conv::kNDFitIsNuDetRelated[nd_index];
}
//____________________________________________________________________________
