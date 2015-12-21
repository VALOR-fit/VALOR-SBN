//________________________________________________________________________________________
/*

Copyright (c) 2010-2015, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include "Utilities/NameRegistry.h"
#include "Utilities/Rnd.h"
#include "NDFit/NDFitParams.h"
#include "Messenger/Messenger.h"

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

    default                      : return "--";    
  }
  return "";
}
//________________________________________________________________________________________
string util::AsStringTeX(conv::PhysParamId_t p, bool root)
{
  string name = "";

  switch(p) {
    case (kNuisFHCNuMuFlux00   ) : name = "f_{FHC;#nu_{#mu};00}";       break;
    case (kNuisFHCNuMuFlux01   ) : name = "f_{FHC;#nu_{#mu};01}";       break;
    case (kNuisFHCNuMuFlux02   ) : name = "f_{FHC;#nu_{#mu};02}";       break;
    case (kNuisFHCNuMuFlux03   ) : name = "f_{FHC;#nu_{#mu};03}";       break;
    case (kNuisFHCNuMuFlux04   ) : name = "f_{FHC;#nu_{#mu};04}";       break;
    case (kNuisFHCNuMuFlux05   ) : name = "f_{FHC;#nu_{#mu};05}";       break;
    case (kNuisFHCNuMuFlux06   ) : name = "f_{FHC;#nu_{#mu};06}";       break;
    case (kNuisFHCNuMuFlux07   ) : name = "f_{FHC;#nu_{#mu};07}";       break;
    case (kNuisFHCNuMuFlux08   ) : name = "f_{FHC;#nu_{#mu};08}";       break;
    case (kNuisFHCNuMuFlux09   ) : name = "f_{FHC;#nu_{#mu};09}";       break;
    case (kNuisFHCNuMuFlux10   ) : name = "f_{FHC;#nu_{#mu};10}";       break;
    case (kNuisFHCNuMuFlux11   ) : name = "f_{FHC;#nu_{#mu};11}";       break;
    case (kNuisFHCNuMuFlux12   ) : name = "f_{FHC;#nu_{#mu};12}";       break;
    case (kNuisFHCNuMuFlux13   ) : name = "f_{FHC;#nu_{#mu};13}";       break;
    case (kNuisFHCNuMuFlux14   ) : name = "f_{FHC;#nu_{#mu};14}";       break;
    case (kNuisFHCNuMuFlux15   ) : name = "f_{FHC;#nu_{#mu};15}";       break;
    case (kNuisFHCNuMuFlux16   ) : name = "f_{FHC;#nu_{#mu};16}";       break;
    case (kNuisFHCNuMuFlux17   ) : name = "f_{FHC;#nu_{#mu};17}";       break;
    case (kNuisFHCNuMuFlux18   ) : name = "f_{FHC;#nu_{#mu};18}";       break;
    case (kNuisFHCNuMuBarFlux00) : name = "f_{FHC;#bar{#nu_{#mu}};00}"; break;
    case (kNuisFHCNuMuBarFlux01) : name = "f_{FHC;#bar{#nu_{#mu}};01}"; break;
    case (kNuisFHCNuMuBarFlux02) : name = "f_{FHC;#bar{#nu_{#mu}};02}"; break;
    case (kNuisFHCNuMuBarFlux03) : name = "f_{FHC;#bar{#nu_{#mu}};03}"; break;
    case (kNuisFHCNuMuBarFlux04) : name = "f_{FHC;#bar{#nu_{#mu}};04}"; break;
    case (kNuisFHCNuMuBarFlux05) : name = "f_{FHC;#bar{#nu_{#mu}};05}"; break;
    case (kNuisFHCNuMuBarFlux06) : name = "f_{FHC;#bar{#nu_{#mu}};06}"; break;
    case (kNuisFHCNuMuBarFlux07) : name = "f_{FHC;#bar{#nu_{#mu}};07}"; break;
    case (kNuisFHCNuMuBarFlux08) : name = "f_{FHC;#bar{#nu_{#mu}};08}"; break;
    case (kNuisFHCNuMuBarFlux09) : name = "f_{FHC;#bar{#nu_{#mu}};09}"; break;
    case (kNuisFHCNuMuBarFlux10) : name = "f_{FHC;#bar{#nu_{#mu}};10}"; break;
    case (kNuisFHCNuMuBarFlux11) : name = "f_{FHC;#bar{#nu_{#mu}};11}"; break;
    case (kNuisFHCNuMuBarFlux12) : name = "f_{FHC;#bar{#nu_{#mu}};12}"; break;
    case (kNuisFHCNuMuBarFlux13) : name = "f_{FHC;#bar{#nu_{#mu}};13}"; break;
    case (kNuisFHCNuMuBarFlux14) : name = "f_{FHC;#bar{#nu_{#mu}};14}"; break;
    case (kNuisFHCNuMuBarFlux15) : name = "f_{FHC;#bar{#nu_{#mu}};15}"; break;
    case (kNuisFHCNuMuBarFlux16) : name = "f_{FHC;#bar{#nu_{#mu}};16}"; break;
    case (kNuisFHCNuMuBarFlux17) : name = "f_{FHC;#bar{#nu_{#mu}};17}"; break;
    case (kNuisFHCNuMuBarFlux18) : name = "f_{FHC;#bar{#nu_{#mu}};18}"; break;
    case (kNuisFHCNuEFlux00    ) : name = "f_{FHC;#nu_{e};00}";         break;
    case (kNuisFHCNuEFlux01    ) : name = "f_{FHC;#nu_{e};01}";         break;
    case (kNuisFHCNuEFlux02    ) : name = "f_{FHC;#nu_{e};02}";         break;
    case (kNuisFHCNuEFlux03    ) : name = "f_{FHC;#nu_{e};03}";         break;
    case (kNuisFHCNuEFlux04    ) : name = "f_{FHC;#nu_{e};04}";         break;
    case (kNuisFHCNuEFlux05    ) : name = "f_{FHC;#nu_{e};05}";         break;
    case (kNuisFHCNuEFlux06    ) : name = "f_{FHC;#nu_{e};06}";         break;
    case (kNuisFHCNuEBarFlux00 ) : name = "f_{FHC;#bar{#nu_{e}};00}";   break;
    case (kNuisFHCNuEBarFlux01 ) : name = "f_{FHC;#bar{#nu_{e}};01}";   break;
    case (kNuisFHCNuEBarFlux02 ) : name = "f_{FHC;#bar{#nu_{e}};02}";   break;
    case (kNuisFHCNuEBarFlux03 ) : name = "f_{FHC;#bar{#nu_{e}};03}";   break;
    case (kNuisFHCNuEBarFlux04 ) : name = "f_{FHC;#bar{#nu_{e}};04}";   break;
    case (kNuisFHCNuEBarFlux05 ) : name = "f_{FHC;#bar{#nu_{e}};05}";   break;
    case (kNuisFHCNuEBarFlux06 ) : name = "f_{FHC;#bar{#nu_{e}};06}";   break;

    case (kNuisRHCNuMuFlux00   ) : name = "f_{RHC;#nu_{#mu};00}";       break;
    case (kNuisRHCNuMuFlux01   ) : name = "f_{RHC;#nu_{#mu};01}";       break;
    case (kNuisRHCNuMuFlux02   ) : name = "f_{RHC;#nu_{#mu};02}";       break;
    case (kNuisRHCNuMuFlux03   ) : name = "f_{RHC;#nu_{#mu};03}";       break;
    case (kNuisRHCNuMuFlux04   ) : name = "f_{RHC;#nu_{#mu};04}";       break;
    case (kNuisRHCNuMuFlux05   ) : name = "f_{RHC;#nu_{#mu};05}";       break;
    case (kNuisRHCNuMuFlux06   ) : name = "f_{RHC;#nu_{#mu};06}";       break;
    case (kNuisRHCNuMuFlux07   ) : name = "f_{RHC;#nu_{#mu};07}";       break;
    case (kNuisRHCNuMuFlux08   ) : name = "f_{RHC;#nu_{#mu};08}";       break;
    case (kNuisRHCNuMuFlux09   ) : name = "f_{RHC;#nu_{#mu};09}";       break;
    case (kNuisRHCNuMuFlux10   ) : name = "f_{RHC;#nu_{#mu};10}";       break;
    case (kNuisRHCNuMuFlux11   ) : name = "f_{RHC;#nu_{#mu};11}";       break;
    case (kNuisRHCNuMuFlux12   ) : name = "f_{RHC;#nu_{#mu};12}";       break;
    case (kNuisRHCNuMuFlux13   ) : name = "f_{RHC;#nu_{#mu};13}";       break;
    case (kNuisRHCNuMuFlux14   ) : name = "f_{RHC;#nu_{#mu};14}";       break;
    case (kNuisRHCNuMuFlux15   ) : name = "f_{RHC;#nu_{#mu};15}";       break;
    case (kNuisRHCNuMuFlux16   ) : name = "f_{RHC;#nu_{#mu};16}";       break;
    case (kNuisRHCNuMuFlux17   ) : name = "f_{RHC;#nu_{#mu};17}";       break;
    case (kNuisRHCNuMuFlux18   ) : name = "f_{RHC;#nu_{#mu};18}";       break;
    case (kNuisRHCNuMuBarFlux00) : name = "f_{RHC;#bar{#nu_{#mu}};00}"; break;
    case (kNuisRHCNuMuBarFlux01) : name = "f_{RHC;#bar{#nu_{#mu}};01}"; break;
    case (kNuisRHCNuMuBarFlux02) : name = "f_{RHC;#bar{#nu_{#mu}};02}"; break;
    case (kNuisRHCNuMuBarFlux03) : name = "f_{RHC;#bar{#nu_{#mu}};03}"; break;
    case (kNuisRHCNuMuBarFlux04) : name = "f_{RHC;#bar{#nu_{#mu}};04}"; break;
    case (kNuisRHCNuMuBarFlux05) : name = "f_{RHC;#bar{#nu_{#mu}};05}"; break;
    case (kNuisRHCNuMuBarFlux06) : name = "f_{RHC;#bar{#nu_{#mu}};06}"; break;
    case (kNuisRHCNuMuBarFlux07) : name = "f_{RHC;#bar{#nu_{#mu}};07}"; break;
    case (kNuisRHCNuMuBarFlux08) : name = "f_{RHC;#bar{#nu_{#mu}};08}"; break;
    case (kNuisRHCNuMuBarFlux09) : name = "f_{RHC;#bar{#nu_{#mu}};09}"; break;
    case (kNuisRHCNuMuBarFlux10) : name = "f_{RHC;#bar{#nu_{#mu}};10}"; break;
    case (kNuisRHCNuMuBarFlux11) : name = "f_{RHC;#bar{#nu_{#mu}};11}"; break;
    case (kNuisRHCNuMuBarFlux12) : name = "f_{RHC;#bar{#nu_{#mu}};12}"; break;
    case (kNuisRHCNuMuBarFlux13) : name = "f_{RHC;#bar{#nu_{#mu}};13}"; break;
    case (kNuisRHCNuMuBarFlux14) : name = "f_{RHC;#bar{#nu_{#mu}};14}"; break;
    case (kNuisRHCNuMuBarFlux15) : name = "f_{RHC;#bar{#nu_{#mu}};15}"; break;
    case (kNuisRHCNuMuBarFlux16) : name = "f_{RHC;#bar{#nu_{#mu}};16}"; break;
    case (kNuisRHCNuMuBarFlux17) : name = "f_{RHC;#bar{#nu_{#mu}};17}"; break;
    case (kNuisRHCNuMuBarFlux18) : name = "f_{RHC;#bar{#nu_{#mu}};18}"; break;
    case (kNuisRHCNuEFlux00    ) : name = "f_{RHC;#nu_{e};00}";         break;
    case (kNuisRHCNuEFlux01    ) : name = "f_{RHC;#nu_{e};01}";         break;
    case (kNuisRHCNuEFlux02    ) : name = "f_{RHC;#nu_{e};02}";         break;
    case (kNuisRHCNuEFlux03    ) : name = "f_{RHC;#nu_{e};03}";         break;
    case (kNuisRHCNuEFlux04    ) : name = "f_{RHC;#nu_{e};04}";         break;
    case (kNuisRHCNuEFlux05    ) : name = "f_{RHC;#nu_{e};05}";         break;
    case (kNuisRHCNuEFlux06    ) : name = "f_{RHC;#nu_{e};06}";         break;
    case (kNuisRHCNuEBarFlux00 ) : name = "f_{RHC;#bar{#nu_{e}};00}";   break;
    case (kNuisRHCNuEBarFlux01 ) : name = "f_{RHC;#bar{#nu_{e}};01}";   break;
    case (kNuisRHCNuEBarFlux02 ) : name = "f_{RHC;#bar{#nu_{e}};02}";   break;
    case (kNuisRHCNuEBarFlux03 ) : name = "f_{RHC;#bar{#nu_{e}};03}";   break;
    case (kNuisRHCNuEBarFlux04 ) : name = "f_{RHC;#bar{#nu_{e}};04}";   break;
    case (kNuisRHCNuEBarFlux05 ) : name = "f_{RHC;#bar{#nu_{e}};05}";   break;
    case (kNuisRHCNuEBarFlux06 ) : name = "f_{RHC;#bar{#nu_{e}};06}";   break;
      
    case (kNuisNormCCQE        ) : name = "f_{CCQE}";                   break;
    case (kNuisNormCC1piC      ) : name = "f_{CC1#pi^{#pm}}";           break;
    case (kNuisNormCC1pi0      ) : name = "f_{CC1#pi^{0}}";             break;
    case (kNuisNormCCoth       ) : name = "f_{CCother}";                break;
    case (kNuisNormNC          ) : name = "f_{NC}";                     break;
    case (kNuisRatioNuENuMu    ) : name = "f_{#nu_{e}/#nu_{#mu}}";      break;

    case (kNuisEffNuMuCC1trkQE  ) : name = "f_{eff;#nu_{#mu}CC;1trkQE}";             break;
    case (kNuisEffNuMuCC2trkQE  ) : name = "f_{eff;#nu_{#mu}CC;2trkQE}";             break;
    case (kNuisEffNuMuCC1piC    ) : name = "f_{eff;#nu_{#mu}CC;1#pi^{#pm}}";         break;
    case (kNuisEffNuMuCC1pi0    ) : name = "f_{eff;#nu_{#mu}CC;1#pi^{0}}";           break;
    case (kNuisEffNuMuCC1piC1pi0) : name = "f_{eff;#nu_{#mu}CC;1#pi^{#pm}1#pi^{0}}"; break;
    case (kNuisEffNuMuCCoth     ) : name = "f_{eff;#nu_{#mu}CC;other}";              break;
    case (kNuisEffNuECC         ) : name = "f_{eff;#nu_{e}CC}";                      break;
    case (kNuisEffNuMuCCWSgn    ) : name = "f_{eff;#nu_{#mu}CC;wsgn}";               break;
    case (kNuisEffNC            ) : name = "f_{eff;NC}";                             break;

    default                      : name = "--";    
  }

  if(root) return name;

  // replace # with \ -- later

  return name;
}
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
PhysHypothesis util::GetPhysHypothesis(Option_t * param_list, Option_t * param_values)
{
// Create a PhysHypothesis object, adding all physics + nuisance params
// The input option specifies both the set of parameters (eg "standard") and their set
// values (eg "nominal", or "randomize-all;prefit-errors" etc).

  PhysHypothesis ph(kHypVoid); 

  string param_list_opt   = ((param_list)   ? param_list   : "standard");
  string param_values_opt = ((param_values) ? param_values : "nominal");

  LOG("NDFitParams", pNOTICE) 
    << "Instantiating a physics hypothesis object with option: " 
    << param_list_opt << " / " << param_values_opt;

  //
  // Get the standard set of parameters
  //

  if(param_list_opt.find("standard") != string::npos) {
    for(int ip = 0; ip < kNNDFitParams; ip++) {
      PhysParamId_t p = kNDFitParam[ip];
      if(p == kPhypUndefined) continue;

      // skip detector params?
      bool skip_detector_params = (param_list_opt.find("no-detector-systematics") != string::npos);
      if(skip_detector_params && kNDFitIsDetectorRelated[ip]) continue;

      double val = -9999;
      // "nominal", a-priori defaults
      if(param_values_opt.find("nominal") != string::npos) {
        val = 1;
      } 
      // "tuned", based on input ND best-fit params
      else 
      if(param_values_opt.find("tuned") != string::npos) {
        LOG("NDFitParams", pFATAL) << "`tuned' option not implemented";
        exit(1);
      } 
      // randomize all parameters using pre-fit errors
      else 
      if(param_values_opt.find("randomize-all;prefit-errors") != string::npos) {
        Rnd * r = Rnd::Instance();
        double sig = 0.2; // kNDFitParamAPrioriFracError[ip]; // HERE
        val = r->RndToyMCsyst().Gaus(1,sig);
      }
      // randomize all parameters using post-fit errors
      else 
      if(param_values_opt.find("randomize-all;postfit-errors") != string::npos) {
        LOG("NDFitParams", pFATAL) << "`randomize-all;postfit-errors' option not implemented";
        exit(1);
      }
      else {
        LOG("NDFitParams", pFATAL) << "You didn't specify how to set the parameter values";
        exit(1);
      }

      ph.SetCurrValue(p,val); 
    }//ip
  }

  return ph;
}
//________________________________________________________________________________________
FitParamList * util::GetFitParameterList (Option_t * param_list, Option_t * param_values)
{
// Create a FitParamList object, adding all physics + nuisance params.
// The input option specifies both the set of parameters (eg "standard") and their set
// values (eg "nominal", or "randomize-all;prefit-errors" etc).


  string param_list_opt   = ((param_list)   ? param_list   : "standard");
  string param_values_opt = ((param_values) ? param_values : "nominal");

  LOG("NDFitParams", pNOTICE)
    << "Instantiating a  fit parameter list object with option: " 
    << param_list_opt << " / " << param_values_opt;

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

/*
// THIS CREATES PROBLEMS because in NDModel we loop over all kNNDFitParams and only checks for undefined ones -
// It does not expect that params will be excluded via some other mechanism.
// So, fix instead

      // skip detector params?
      bool skip_detector_params = (param_list_opt.find("no-detector-systematics") != string::npos);
      if(skip_detector_params && kNDFitIsDetectorRelated[ip]) continue;
      // toggle flux related params on/off
      bool skip_flux_params = (param_list_opt.find("no-flux-systematics") != string::npos);
      if(skip_flux_params && kNDFitIsFluxRelated[ip]) continue;
*/
      // set parameter range, current and init value, etc
      double init = 1.0;
      double curr = -99999;
      double min  = 0.0;
      double max  = 2.0;
      double step = 1E-4;
      bool   fix  = false;
      bool   nuis = true;

      // "nominal", a-priori defaults
      if(param_values_opt.find("nominal") != string::npos) {
        curr = init;
      } 
      // "tuned", based on input ND best-fit params
      else 
      if(param_values_opt.find("tuned") != string::npos) {
        LOG("NDFitParams", pFATAL) << "`tuned' option not implemented";
        exit(1);
      } 
      // randomize all parameters using pre-fit errors
      else 
      if(param_values_opt.find("randomize-all;prefit-errors") != string::npos) {
        Rnd * r = Rnd::Instance();
        double sig = 0.2; // kNDFitParamAPrioriFracError[ip]; // HERE
        curr = r->RndToyMCsyst().Gaus(1,sig);
        curr = TMath::Min(curr,max);
        curr = TMath::Max(curr,min);
        // help fitter by setting init to curr (curr values may be used as true values for toy-MC generation before fitting)
        init = curr;
      }
      // randomize all parameters using post-fit errors
      else 
      if(param_values_opt.find("randomize-all;postfit-errors") != string::npos) {
        LOG("NDFitParams", pFATAL) << "`randomize-all;postfit-errors' option not implemented";
        exit(1);
      }
      else {
        LOG("NDFitParams", pFATAL) << "You didn't specify how to set the parameter values";
        exit(1);
      }

      fparm->AddParam(ipc, p, init, min, max, step, fix, nuis);    
      ipc++; 
      fparm->Update(p, curr);


      // toggle detector related params on/off
      bool no_detector_params = (param_list_opt.find("no-detector-systematics") != string::npos);
      if(no_detector_params && kNDFitIsDetectorRelated[ip]) {
       fparm->Update(p, 1.);
       fparm->SetInitValue(p, 1.);
       fparm->FixParameter(p);
      }
      // toggle flux related params on/off
      bool no_flux_params = (param_list_opt.find("no-flux-systematics") != string::npos);
      if(no_flux_params && kNDFitIsFluxRelated[ip]) {
       fparm->Update(p, 1.);
       fparm->SetInitValue(p, 1.);
       fparm->FixParameter(p);
      }

    }//ip
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
