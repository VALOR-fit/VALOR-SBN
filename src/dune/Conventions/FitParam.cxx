//________________________________________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

options for the fit param list:
        - standard: all nd + fd + osc parameters
        - only-nd:  only nd parameters

additional options
        - no-int-systematics: skipping neutrino interaction systematics in the list construction
        - no-flux-systematics, no-nd-flux-systematics, no-fd-flux-systematics: as above for flux
        - no-detector-systematics, no-nd-detector-systematics, no-fd-detector-systematics: as above for efficiencies
        - no-osc-params: skipping oscillation parameters in the list construction

options after list construction
        - no-osc-params     : 
        - fix-osc-params    : fix all oscillation parameters
        - cons-osc-params   : set all osc params as nuisance - Note: to constrain only one (i.e. theta13, usual reactor)
                              use this one and fix other osc params independently (see run_fit options)
        - cons-atm-params   : set the 23 parameters as nuisance
        - cons-solar-params : set the 12 parameters as nuisance
        - fix-det-syst      : fix all detector params included in the list
        - fix-nd-det-syst   : 
        - fix-fd-det-syst   : 
        - fix-flux-syst     : fix all flux params included in the list
        - fix-nd-flux-syst  : 
        - fix-fd-flux-syst  : 
        - fix-int-syst      : fix all neutrino interaction systematic parameters
        - fix-mec-syst      : fix mec params
        - fix-fsi-syst      : fix the FSI params
        - fix-osc-param: 
        - cons_osc_params: 
        - cons_atm_params:     
        - cons_solar_params:   
        - fix_detector_params: 
        - fix_flux_params:     
        - fix_int_params:      
        - fix_mec_params:      
        - fix_fsi_params:      
*/
//____________________________________________________________________________________________________________________

#include <algorithm>

// fmwk
#include "valor/Utilities/NameRegistry.h"
#include "valor/Utilities/Rnd.h"
#include "valor/Utilities/UtlStr.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Messenger/Messenger.h"
// dune
#include "dune/Conventions/OscParams.h"
#include "dune/Conventions/FitParam.h"
#include "dune/Conventions/FitParamApply.h"
#include "dune/Conventions/ArrIdx.h"
#include "dune/Conventions/PhysicalParameterLimits.h"

using namespace valor;
using namespace valor::conv;


//________________________________________________________________________________________
string util::AsStringSimple(conv::PhysParamId_t p)
{
  switch(p) {

    case (kPhypMixing12                 ) : return "mixing12";
    case (kPhypMixing23                 ) : return "mixing23";
    case (kPhypMixing13                 ) : return "mixing13";
    case (kPhypDm23sq                   ) : return "dm23sq";  
    case (kPhypDm12sq                   ) : return "dm12sq"; 
    case (kPhypCPV                      ) : return "cpv";
    
    case (kPhypDm41sq                   ) : return "dm41sq"; 
    case (kPhypMixingEE                 ) : return "sinsq2thEE";
    case (kPhypMixingMuE                ) : return "sinsq2thMuE";
    case (kPhypMixingMuMu               ) : return "sinsq2thMuMu";

    default                       : return util::RawParamAsString(p);   
  }
  return "";

}
//________________________________________________________________________________________
string util::AsStringTeX(conv::PhysParamId_t p, bool root)
{
  string name = "";
  if (!util::IsSystematic(p)) return RawParamAsStringTex(p);
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
    case (kNuisFHCNuMuBarFlux00) : name = "f_{FHC;\\bar{\\nu}_{\\mu};00}";                 break;
    case (kNuisFHCNuMuBarFlux01) : name = "f_{FHC;\\bar{\\nu}_{\\mu};01}";                 break;
    case (kNuisFHCNuMuBarFlux02) : name = "f_{FHC;\\bar{\\nu}_{\\mu};02}";                 break;
    case (kNuisFHCNuMuBarFlux03) : name = "f_{FHC;\\bar{\\nu}_{\\mu};03}";                 break;
    case (kNuisFHCNuMuBarFlux04) : name = "f_{FHC;\\bar{\\nu}_{\\mu};04}";                 break;
    case (kNuisFHCNuMuBarFlux05) : name = "f_{FHC;\\bar{\\nu}_{\\mu};05}";                 break;
    case (kNuisFHCNuMuBarFlux06) : name = "f_{FHC;\\bar{\\nu}_{\\mu};06}";                 break;
    case (kNuisFHCNuMuBarFlux07) : name = "f_{FHC;\\bar{\\nu}_{\\mu};07}";                 break;
    case (kNuisFHCNuMuBarFlux08) : name = "f_{FHC;\\bar{\\nu}_{\\mu};08}";                 break;
    case (kNuisFHCNuMuBarFlux09) : name = "f_{FHC;\\bar{\\nu}_{\\mu};09}";                 break;
    case (kNuisFHCNuMuBarFlux10) : name = "f_{FHC;\\bar{\\nu}_{\\mu};10}";                 break;
    case (kNuisFHCNuMuBarFlux11) : name = "f_{FHC;\\bar{\\nu}_{\\mu};11}";                 break;
    case (kNuisFHCNuMuBarFlux12) : name = "f_{FHC;\\bar{\\nu}_{\\mu};12}";                 break;
    case (kNuisFHCNuMuBarFlux13) : name = "f_{FHC;\\bar{\\nu}_{\\mu};13}";                 break;
    case (kNuisFHCNuMuBarFlux14) : name = "f_{FHC;\\bar{\\nu}_{\\mu};14}";                 break;
    case (kNuisFHCNuMuBarFlux15) : name = "f_{FHC;\\bar{\\nu}_{\\mu};15}";                 break;
    case (kNuisFHCNuMuBarFlux16) : name = "f_{FHC;\\bar{\\nu}_{\\mu};16}";                 break;
    case (kNuisFHCNuMuBarFlux17) : name = "f_{FHC;\\bar{\\nu}_{\\mu};17}";                 break;
    case (kNuisFHCNuMuBarFlux18) : name = "f_{FHC;\\bar{\\nu}_{\\mu};18}";                 break;
    case (kNuisFHCNuEFlux00    ) : name = "f_{FHC;\\nu_{e};00}";                           break;
    case (kNuisFHCNuEFlux01    ) : name = "f_{FHC;\\nu_{e};01}";                           break;
    case (kNuisFHCNuEFlux02    ) : name = "f_{FHC;\\nu_{e};02}";                           break;
    case (kNuisFHCNuEFlux03    ) : name = "f_{FHC;\\nu_{e};03}";                           break;
    case (kNuisFHCNuEFlux04    ) : name = "f_{FHC;\\nu_{e};04}";                           break;
    case (kNuisFHCNuEFlux05    ) : name = "f_{FHC;\\nu_{e};05}";                           break;
    case (kNuisFHCNuEFlux06    ) : name = "f_{FHC;\\nu_{e};06}";                           break;
    case (kNuisFHCNuEBarFlux00 ) : name = "f_{FHC;\\bar{\\nu}_{e};00}";                    break;
    case (kNuisFHCNuEBarFlux01 ) : name = "f_{FHC;\\bar{\\nu}_{e};01}";                    break;
    case (kNuisFHCNuEBarFlux02 ) : name = "f_{FHC;\\bar{\\nu}_{e};02}";                    break;
    case (kNuisFHCNuEBarFlux03 ) : name = "f_{FHC;\\bar{\\nu}_{e};03}";                    break;
    case (kNuisFHCNuEBarFlux04 ) : name = "f_{FHC;\\bar{\\nu}_{e};04}";                    break;
    case (kNuisFHCNuEBarFlux05 ) : name = "f_{FHC;\\bar{\\nu}_{e};05}";                    break;
    case (kNuisFHCNuEBarFlux06 ) : name = "f_{FHC;\\bar{\\nu}_{e};06}";                    break;
    
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
    case (kNuisRHCNuMuBarFlux00) : name = "f_{RHC;\\bar{\\nu}_{\\mu};00}";                 break;
    case (kNuisRHCNuMuBarFlux01) : name = "f_{RHC;\\bar{\\nu}_{\\mu};01}";                 break;
    case (kNuisRHCNuMuBarFlux02) : name = "f_{RHC;\\bar{\\nu}_{\\mu};02}";                 break;
    case (kNuisRHCNuMuBarFlux03) : name = "f_{RHC;\\bar{\\nu}_{\\mu};03}";                 break;
    case (kNuisRHCNuMuBarFlux04) : name = "f_{RHC;\\bar{\\nu}_{\\mu};04}";                 break;
    case (kNuisRHCNuMuBarFlux05) : name = "f_{RHC;\\bar{\\nu}_{\\mu};05}";                 break;
    case (kNuisRHCNuMuBarFlux06) : name = "f_{RHC;\\bar{\\nu}_{\\mu};06}";                 break;
    case (kNuisRHCNuMuBarFlux07) : name = "f_{RHC;\\bar{\\nu}_{\\mu};07}";                 break;
    case (kNuisRHCNuMuBarFlux08) : name = "f_{RHC;\\bar{\\nu}_{\\mu};08}";                 break;
    case (kNuisRHCNuMuBarFlux09) : name = "f_{RHC;\\bar{\\nu}_{\\mu};09}";                 break;
    case (kNuisRHCNuMuBarFlux10) : name = "f_{RHC;\\bar{\\nu}_{\\mu};10}";                 break;
    case (kNuisRHCNuMuBarFlux11) : name = "f_{RHC;\\bar{\\nu}_{\\mu};11}";                 break;
    case (kNuisRHCNuMuBarFlux12) : name = "f_{RHC;\\bar{\\nu}_{\\mu};12}";                 break;
    case (kNuisRHCNuMuBarFlux13) : name = "f_{RHC;\\bar{\\nu}_{\\mu};13}";                 break;
    case (kNuisRHCNuMuBarFlux14) : name = "f_{RHC;\\bar{\\nu}_{\\mu};14}";                 break;
    case (kNuisRHCNuMuBarFlux15) : name = "f_{RHC;\\bar{\\nu}_{\\mu};15}";                 break;
    case (kNuisRHCNuMuBarFlux16) : name = "f_{RHC;\\bar{\\nu}_{\\mu};16}";                 break;
    case (kNuisRHCNuMuBarFlux17) : name = "f_{RHC;\\bar{\\nu}_{\\mu};17}";                 break;
    case (kNuisRHCNuMuBarFlux18) : name = "f_{RHC;\\bar{\\nu}_{\\mu};18}";                 break;
    case (kNuisRHCNuEFlux00    ) : name = "f_{RHC;\\nu_{e};00}";                           break;
    case (kNuisRHCNuEFlux01    ) : name = "f_{RHC;\\nu_{e};01}";                           break;
    case (kNuisRHCNuEFlux02    ) : name = "f_{RHC;\\nu_{e};02}";                           break;
    case (kNuisRHCNuEFlux03    ) : name = "f_{RHC;\\nu_{e};03}";                           break;
    case (kNuisRHCNuEFlux04    ) : name = "f_{RHC;\\nu_{e};04}";                           break;
    case (kNuisRHCNuEFlux05    ) : name = "f_{RHC;\\nu_{e};05}";                           break;
    case (kNuisRHCNuEFlux06    ) : name = "f_{RHC;\\nu_{e};06}";                           break;
    case (kNuisRHCNuEBarFlux00 ) : name = "f_{RHC;\\bar{\\nu}_{e};00}";                    break;
    case (kNuisRHCNuEBarFlux01 ) : name = "f_{RHC;\\bar{\\nu}_{e};01}";                    break;
    case (kNuisRHCNuEBarFlux02 ) : name = "f_{RHC;\\bar{\\nu}_{e};02}";                    break;
    case (kNuisRHCNuEBarFlux03 ) : name = "f_{RHC;\\bar{\\nu}_{e};03}";                    break;
    case (kNuisRHCNuEBarFlux04 ) : name = "f_{RHC;\\bar{\\nu}_{e};04}";                    break;
    case (kNuisRHCNuEBarFlux05 ) : name = "f_{RHC;\\bar{\\nu}_{e};05}";                    break;
    case (kNuisRHCNuEBarFlux06 ) : name = "f_{RHC;\\bar{\\nu}_{e};06}";                    break;
      
    case (kNuisFHCNuMuFDFlux00   ) : name = "f_{FHC;FD;\\nu_{\\mu};00}";                        break;
    case (kNuisFHCNuMuFDFlux01   ) : name = "f_{FHC;FD;\\nu_{\\mu};01}";                        break;
    case (kNuisFHCNuMuFDFlux02   ) : name = "f_{FHC;FD;\\nu_{\\mu};02}";                        break;
    case (kNuisFHCNuMuFDFlux03   ) : name = "f_{FHC;FD;\\nu_{\\mu};03}";                        break;
    case (kNuisFHCNuMuFDFlux04   ) : name = "f_{FHC;FD;\\nu_{\\mu};04}";                        break;
    case (kNuisFHCNuMuFDFlux05   ) : name = "f_{FHC;FD;\\nu_{\\mu};05}";                        break;
    case (kNuisFHCNuMuFDFlux06   ) : name = "f_{FHC;FD;\\nu_{\\mu};06}";                        break;
    case (kNuisFHCNuMuFDFlux07   ) : name = "f_{FHC;FD;\\nu_{\\mu};07}";                        break;
    case (kNuisFHCNuMuFDFlux08   ) : name = "f_{FHC;FD;\\nu_{\\mu};08}";                        break;
    case (kNuisFHCNuMuFDFlux09   ) : name = "f_{FHC;FD;\\nu_{\\mu};09}";                        break;
    case (kNuisFHCNuMuFDFlux10   ) : name = "f_{FHC;FD;\\nu_{\\mu};10}";                        break;
    case (kNuisFHCNuMuFDFlux11   ) : name = "f_{FHC;FD;\\nu_{\\mu};11}";                        break;
    case (kNuisFHCNuMuFDFlux12   ) : name = "f_{FHC;FD;\\nu_{\\mu};12}";                        break;
    case (kNuisFHCNuMuFDFlux13   ) : name = "f_{FHC;FD;\\nu_{\\mu};13}";                        break;
    case (kNuisFHCNuMuFDFlux14   ) : name = "f_{FHC;FD;\\nu_{\\mu};14}";                        break;
    case (kNuisFHCNuMuFDFlux15   ) : name = "f_{FHC;FD;\\nu_{\\mu};15}";                        break;
    case (kNuisFHCNuMuFDFlux16   ) : name = "f_{FHC;FD;\\nu_{\\mu};16}";                        break;
    case (kNuisFHCNuMuFDFlux17   ) : name = "f_{FHC;FD;\\nu_{\\mu};17}";                        break;
    case (kNuisFHCNuMuFDFlux18   ) : name = "f_{FHC;FD;\\nu_{\\mu};18}";                        break;
    case (kNuisFHCNuMuBarFDFlux00) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};00}";                 break;
    case (kNuisFHCNuMuBarFDFlux01) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};01}";                 break;
    case (kNuisFHCNuMuBarFDFlux02) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};02}";                 break;
    case (kNuisFHCNuMuBarFDFlux03) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};03}";                 break;
    case (kNuisFHCNuMuBarFDFlux04) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};04}";                 break;
    case (kNuisFHCNuMuBarFDFlux05) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};05}";                 break;
    case (kNuisFHCNuMuBarFDFlux06) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};06}";                 break;
    case (kNuisFHCNuMuBarFDFlux07) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};07}";                 break;
    case (kNuisFHCNuMuBarFDFlux08) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};08}";                 break;
    case (kNuisFHCNuMuBarFDFlux09) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};09}";                 break;
    case (kNuisFHCNuMuBarFDFlux10) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};10}";                 break;
    case (kNuisFHCNuMuBarFDFlux11) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};11}";                 break;
    case (kNuisFHCNuMuBarFDFlux12) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};12}";                 break;
    case (kNuisFHCNuMuBarFDFlux13) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};13}";                 break;
    case (kNuisFHCNuMuBarFDFlux14) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};14}";                 break;
    case (kNuisFHCNuMuBarFDFlux15) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};15}";                 break;
    case (kNuisFHCNuMuBarFDFlux16) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};16}";                 break;
    case (kNuisFHCNuMuBarFDFlux17) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};17}";                 break;
    case (kNuisFHCNuMuBarFDFlux18) : name = "f_{FHC;FD;\\bar{\\nu}_{\\mu};18}";                 break;
    case (kNuisFHCNuEFDFlux00    ) : name = "f_{FHC;FD;\\nu_{e};00}";                           break;
    case (kNuisFHCNuEFDFlux01    ) : name = "f_{FHC;FD;\\nu_{e};01}";                           break;
    case (kNuisFHCNuEFDFlux02    ) : name = "f_{FHC;FD;\\nu_{e};02}";                           break;
    case (kNuisFHCNuEFDFlux03    ) : name = "f_{FHC;FD;\\nu_{e};03}";                           break;
    case (kNuisFHCNuEFDFlux04    ) : name = "f_{FHC;FD;\\nu_{e};04}";                           break;
    case (kNuisFHCNuEFDFlux05    ) : name = "f_{FHC;FD;\\nu_{e};05}";                           break;
    case (kNuisFHCNuEFDFlux06    ) : name = "f_{FHC;FD;\\nu_{e};06}";                           break;
    case (kNuisFHCNuEBarFDFlux00 ) : name = "f_{FHC;FD;\\bar{\\nu}_{e};00}";                    break;
    case (kNuisFHCNuEBarFDFlux01 ) : name = "f_{FHC;FD;\\bar{\\nu}_{e};01}";                    break;
    case (kNuisFHCNuEBarFDFlux02 ) : name = "f_{FHC;FD;\\bar{\\nu}_{e};02}";                    break;
    case (kNuisFHCNuEBarFDFlux03 ) : name = "f_{FHC;FD;\\bar{\\nu}_{e};03}";                    break;
    case (kNuisFHCNuEBarFDFlux04 ) : name = "f_{FHC;FD;\\bar{\\nu}_{e};04}";                    break;
    case (kNuisFHCNuEBarFDFlux05 ) : name = "f_{FHC;FD;\\bar{\\nu}_{e};05}";                    break;
    case (kNuisFHCNuEBarFDFlux06 ) : name = "f_{FHC;FD;\\bar{\\nu}_{e};06}";                    break;
    
    case (kNuisRHCNuMuFDFlux00   ) : name = "f_{RHC;FD;\\nu_{\\mu};00}";                        break;
    case (kNuisRHCNuMuFDFlux01   ) : name = "f_{RHC;FD;\\nu_{\\mu};01}";                        break;
    case (kNuisRHCNuMuFDFlux02   ) : name = "f_{RHC;FD;\\nu_{\\mu};02}";                        break;
    case (kNuisRHCNuMuFDFlux03   ) : name = "f_{RHC;FD;\\nu_{\\mu};03}";                        break;
    case (kNuisRHCNuMuFDFlux04   ) : name = "f_{RHC;FD;\\nu_{\\mu};04}";                        break;
    case (kNuisRHCNuMuFDFlux05   ) : name = "f_{RHC;FD;\\nu_{\\mu};05}";                        break;
    case (kNuisRHCNuMuFDFlux06   ) : name = "f_{RHC;FD;\\nu_{\\mu};06}";                        break;
    case (kNuisRHCNuMuFDFlux07   ) : name = "f_{RHC;FD;\\nu_{\\mu};07}";                        break;
    case (kNuisRHCNuMuFDFlux08   ) : name = "f_{RHC;FD;\\nu_{\\mu};08}";                        break;
    case (kNuisRHCNuMuFDFlux09   ) : name = "f_{RHC;FD;\\nu_{\\mu};09}";                        break;
    case (kNuisRHCNuMuFDFlux10   ) : name = "f_{RHC;FD;\\nu_{\\mu};10}";                        break;
    case (kNuisRHCNuMuFDFlux11   ) : name = "f_{RHC;FD;\\nu_{\\mu};11}";                        break;
    case (kNuisRHCNuMuFDFlux12   ) : name = "f_{RHC;FD;\\nu_{\\mu};12}";                        break;
    case (kNuisRHCNuMuFDFlux13   ) : name = "f_{RHC;FD;\\nu_{\\mu};13}";                        break;
    case (kNuisRHCNuMuFDFlux14   ) : name = "f_{RHC;FD;\\nu_{\\mu};14}";                        break;
    case (kNuisRHCNuMuFDFlux15   ) : name = "f_{RHC;FD;\\nu_{\\mu};15}";                        break;
    case (kNuisRHCNuMuFDFlux16   ) : name = "f_{RHC;FD;\\nu_{\\mu};16}";                        break;
    case (kNuisRHCNuMuFDFlux17   ) : name = "f_{RHC;FD;\\nu_{\\mu};17}";                        break;
    case (kNuisRHCNuMuFDFlux18   ) : name = "f_{RHC;FD;\\nu_{\\mu};18}";                        break;
    case (kNuisRHCNuMuBarFDFlux00) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};00}";                 break;
    case (kNuisRHCNuMuBarFDFlux01) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};01}";                 break;
    case (kNuisRHCNuMuBarFDFlux02) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};02}";                 break;
    case (kNuisRHCNuMuBarFDFlux03) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};03}";                 break;
    case (kNuisRHCNuMuBarFDFlux04) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};04}";                 break;
    case (kNuisRHCNuMuBarFDFlux05) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};05}";                 break;
    case (kNuisRHCNuMuBarFDFlux06) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};06}";                 break;
    case (kNuisRHCNuMuBarFDFlux07) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};07}";                 break;
    case (kNuisRHCNuMuBarFDFlux08) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};08}";                 break;
    case (kNuisRHCNuMuBarFDFlux09) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};09}";                 break;
    case (kNuisRHCNuMuBarFDFlux10) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};10}";                 break;
    case (kNuisRHCNuMuBarFDFlux11) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};11}";                 break;
    case (kNuisRHCNuMuBarFDFlux12) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};12}";                 break;
    case (kNuisRHCNuMuBarFDFlux13) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};13}";                 break;
    case (kNuisRHCNuMuBarFDFlux14) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};14}";                 break;
    case (kNuisRHCNuMuBarFDFlux15) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};15}";                 break;
    case (kNuisRHCNuMuBarFDFlux16) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};16}";                 break;
    case (kNuisRHCNuMuBarFDFlux17) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};17}";                 break;
    case (kNuisRHCNuMuBarFDFlux18) : name = "f_{RHC;FD;\\bar{\\nu}_{\\mu};18}";                 break;
    case (kNuisRHCNuEFDFlux00    ) : name = "f_{RHC;FD;\\nu_{e};00}";                           break;
    case (kNuisRHCNuEFDFlux01    ) : name = "f_{RHC;FD;\\nu_{e};01}";                           break;
    case (kNuisRHCNuEFDFlux02    ) : name = "f_{RHC;FD;\\nu_{e};02}";                           break;
    case (kNuisRHCNuEFDFlux03    ) : name = "f_{RHC;FD;\\nu_{e};03}";                           break;
    case (kNuisRHCNuEFDFlux04    ) : name = "f_{RHC;FD;\\nu_{e};04}";                           break;
    case (kNuisRHCNuEFDFlux05    ) : name = "f_{RHC;FD;\\nu_{e};05}";                           break;
    case (kNuisRHCNuEFDFlux06    ) : name = "f_{RHC;FD;\\nu_{e};06}";                           break;
    case (kNuisRHCNuEBarFDFlux00 ) : name = "f_{RHC;FD;\\bar{\\nu}_{e};00}";                    break;
    case (kNuisRHCNuEBarFDFlux01 ) : name = "f_{RHC;FD;\\bar{\\nu}_{e};01}";                    break;
    case (kNuisRHCNuEBarFDFlux02 ) : name = "f_{RHC;FD;\\bar{\\nu}_{e};02}";                    break;
    case (kNuisRHCNuEBarFDFlux03 ) : name = "f_{RHC;FD;\\bar{\\nu}_{e};03}";                    break;
    case (kNuisRHCNuEBarFDFlux04 ) : name = "f_{RHC;FD;\\bar{\\nu}_{e};04}";                    break;
    case (kNuisRHCNuEBarFDFlux05 ) : name = "f_{RHC;FD;\\bar{\\nu}_{e};05}";                    break;
    case (kNuisRHCNuEBarFDFlux06 ) : name = "f_{RHC;FD;\\bar{\\nu}_{e};06}";                    break;
          
    case (kNuisNormCCQE        ) : name = "f_{CCQE}";                                      break;
    case (kNuisNormCC1piC      ) : name = "f_{CC1\\pi^{\\pm}}";                            break;
    case (kNuisNormCC1pi0      ) : name = "f_{CC1\\pi^{0}}";                               break;
    case (kNuisNormCCoth       ) : name = "f_{CCother}";                                   break;
    case (kNuisNormNC          ) : name = "f_{NC}";                                        break;
    case (kNuisRatioNuENuMu    ) : name = "f_{\\nu_{e}/\\nu_{\\mu}}";                      break;
    
    case (kNuisEffNuMuCC0pi1trk ) : name = "f_{eff;\\nu_{\\mu}CC;0pi1trk}";                break;
    case (kNuisEffNuMuCC0pi2trk ) : name = "f_{eff;\\nu_{\\mu}CC;0pi2trk}";                break;
    case (kNuisEffNuMuCC1piC    ) : name = "f_{eff;\\nu_{\\mu}CC;1\\pi^{\\pm}}";           break;
    case (kNuisEffNuMuCC1pi0    ) : name = "f_{eff;\\nu_{\\mu}CC;1\\pi^{0}}";              break;
    case (kNuisEffNuMuCC1piC1pi0) : name = "f_{eff;\\nu_{\\mu}CC;1\\pi^{\\pm}1\\pi^{0}}";  break;
    case (kNuisEffNuMuCCoth     ) : name = "f_{eff;\\nu_{\\mu}CC;other}";                  break;
    case (kNuisEffNuECC         ) : name = "f_{eff;\\nu_{e}CC}";                           break;
    case (kNuisEffNuMuCCWS      ) : name = "f_{eff;\\nu_{\\mu}CC;wsgn}";                   break;
    case (kNuisEffNC            ) : name = "f_{eff;NC}";                                   break;
    
    case (kNuisEffFDNuMuLikeCCHigh  ) : name = "f_{eff;FD;\\nu_{\\mu}CC;high}";                break;  
    case (kNuisEffFDNuMuLikeCCLow   ) : name = "f_{eff;FD;\\nu_{\\mu}CC;low}";                 break;  
      //    case (kNuisEffFDNuMuBarCCHigh  ) : name = "f_{eff;FD;\\bar{\\nu}_{\\mu}CC;high}";      break;  
      //    case (kNuisEffFDNuMuBarCCLow   ) : name = "f_{eff;FD;\\bar{\\nu}_{\\mu}CC;low}";       break;  
    case (kNuisEffFDNuELikeCCHigh  ) : name = "f_{eff;FD;\\nu_{e}CC;high}";                break;  
    case (kNuisEffFDNuELikeCCLow   ) : name = "f_{eff;FD;\\nu_{e}CC;low}";                 break;  
      //    case (kNuisEffFDNuEBarCCHigh  ) : name = "f_{eff;FD;\\bar{\\nu}_{e}CC;high}";      break;  
      //    case (kNuisEffFDNuEBarCCLow   ) : name = "f_{eff;FD;\\bar{\\nu}_{e}CC;low}";       break;  
      //    case (kNuisEffFDNuTauCCHigh  ) : name = "f_{eff;FD;\\nu_{\\tau}CC;high}";                break;  
      //    case (kNuisEffFDNuTauCCLow   ) : name = "f_{eff;FD;\\nu_{\\tau}CC;low}";                 break;  
      //    case (kNuisEffFDNuTauBarCCHigh  ) : name = "f_{eff;FD;\\bar{\\nu}_{\\tau}CC;high}";      break;  
      //    case (kNuisEffFDNuTauBarCCLow   ) : name = "f_{eff;FD;\\bar{\\nu}_{\\tau}CC;low}";       break;  

    case ( kNuisIntNuCCQE1         ) : name =  "f_{\\nu CCQE ; 1}";                        break;
    case ( kNuisIntNuCCQE2         ) : name =  "f_{\\nu CCQE ; 2}";                        break;
    case ( kNuisIntNuCCQE3         ) : name =  "f_{\\nu CCQE ; 3}";                        break;
    case ( kNuisIntNuBarCCQE1      ) : name =  "f_{\\bar{\\nu} CCQE ; 1}";                 break;
    case ( kNuisIntNuBarCCQE2      ) : name =  "f_{\\bar{\\nu} CCQE ; 2}";                 break;
    case ( kNuisIntNuBarCCQE3      ) : name =  "f_{\\bar{\\nu} CCQE ; 3}";                 break;
    
    case ( kNuisIntNuCCMEC         ) : name =  "f_{\\nu CC MEC}";                          break;
    case ( kNuisIntNuBarCCMEC      ) : name =  "f_{\\bar{\\nu} CC MEC}";                   break;
    
    case ( kNuisIntNuCC1piz1       ) : name =  "f_{\\nu CC1\\pi^{0} ; 1}";                 break;
    case ( kNuisIntNuCC1piz2       ) : name =  "f_{\\nu CC1\\pi^{0} ; 2}";                 break;
    case ( kNuisIntNuCC1piz3       ) : name =  "f_{\\nu CC1\\pi^{0} ; 3}";                 break;
    case ( kNuisIntNuCC1pic1       ) : name =  "f_{\\nu CC1\\pi^{\\pm} ; 1}";              break;
    case ( kNuisIntNuCC1pic2       ) : name =  "f_{\\nu CC1\\pi^{\\pm} ; 2}";              break;
    case ( kNuisIntNuCC1pic3       ) : name =  "f_{\\nu CC1\\pi^{\\pm} ; 3}";              break;
    
    case ( kNuisIntNuBarCC1piz1    ) : name =  "f_{\\bar{\\nu} CC1\\pi^{0} ; 1}";          break;
    case ( kNuisIntNuBarCC1piz2    ) : name =  "f_{\\bar{\\nu} CC1\\pi^{0} ; 2}";          break;
    case ( kNuisIntNuBarCC1piz3    ) : name =  "f_{\\bar{\\nu} CC1\\pi^{0} ; 3}";          break;
    case ( kNuisIntNuBarCC1pic1    ) : name =  "f_{\\bar{\\nu} CC1\\pi^{\\pm} ; 1}";       break;
    case ( kNuisIntNuBarCC1pic2    ) : name =  "f_{\\bar{\\nu} CC1\\pi^{\\pm} ; 2}";       break;
    case ( kNuisIntNuBarCC1pic3    ) : name =  "f_{\\bar{\\nu} CC1\\pi^{\\pm} ; 3}";       break;
    
    case ( kNuisIntNuCC2Pi         ) : name =  "f_{\\nu CC 2\\pi}";                        break;
    case ( kNuisIntNuBarCC2Pi      ) : name =  "f_{\\bar{\\nu} CC 2\\pi}";                 break;
    
    case ( kNuisIntNuDIS1          ) : name =  "f_{\\nu CC DIS ; 1}";                      break;
    case ( kNuisIntNuDIS2          ) : name =  "f_{\\nu CC DIS ; 2}";                      break;
    case ( kNuisIntNuDIS3          ) : name =  "f_{\\nu CC DIS ; 3}";                      break;
    case ( kNuisIntNuBarDIS1       ) : name =  "f_{\\bar{\\nu} CC DIS ; 1}";               break;
    case ( kNuisIntNuBarDIS2       ) : name =  "f_{\\bar{\\nu} CC DIS ; 2}";               break;
    case ( kNuisIntNuBarDIS3       ) : name =  "f_{\\bar{\\nu} CC DIS ; 3}";               break;
    
    case (kNuisIntNormNuCoherent        ) : name = "f_{\\nu CC Coh}";                      break;
    case (kNuisIntNormNuBarCoherent     ) : name = "f_{\\bar{\\nu} CC Coh}";               break;
    case (kNuisIntNuNormNC              ) : name = "f_{\\nu NC}";                          break;
    case (kNuisIntNuBarNormNC           ) : name = "f_{\\bar{\\nu} NC}";                   break;
    case (kNuisIntNormNuMuToNuE         ) : name = "f_{\\nu_{e} / \\nu_{\\mu}}";           break;
    case (kNuisIntNormNuMuBarToNuEBar   ) : name = "f_{\\bar{\\nu}_{e} / \\bar{\\nu}_{\\mu}}";           break;
    case (kNuisIntPiMeanFreePath        ) : name = "f_{FSI ; \\pi ; MFP}";                 break;
    case (kNuisIntNucMeanFreePath       ) : name = "f_{FSI ; N ; MFP}";                    break;
    case (kNuisIntFracPiChargeExchange  ) : name = "f_{FSI ; \\pi ; CEx}";                 break;
    case (kNuisIntFracPiInelastic       ) : name = "f_{FSI ; \\pi ; Inel}";                break;
    case (kNuisIntFracPiAbsorb          ) : name = "f_{FSI ; \\pi ; Abs}";                 break;
    case (kNuisIntFracPiProduction      ) : name = "f_{FSI ; \\pi ; \\pi Prod}";           break;
    case (kNuisIntFracNucChargeExchange ) : name = "f_{FSI ; N ; CEx}";                    break;
    case (kNuisIntFracNucInelastic      ) : name = "f_{FSI ; N ; Inel}";                   break;
    case (kNuisIntFracNucAbsorb         ) : name = "f_{FSI ; N ; Abs}";                    break;
    case (kNuisIntFracNucProduction     ) : name = "f_{FSI ; N ; \\pi Prod}";              break;

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
string util::ParamAsStringTeX (conv::PhysParamId_t p, bool root) {return util::AsStringTeX(p,root);};
//________________________________________________________________________________________
FitParamList * util::GetFitParameterList (Option_t * param_list, const CorrelatedSystematics * syst)
{
// Create a FitParamList object, adding all physics + nuisance params.
// The input option specifies both the set of parameters (eg "standard") 

  string param_list_opt   = ((param_list)   ? param_list   : "standard");

  LOG("FitParams", pNOTICE)
    << "Instantiating a  fit parameter list object with option: " << param_list_opt;

  FitParamList * fparm = 0;

  //
  // Get the standard set of parameters
  //

  // include params 
  if(param_list_opt.find("standard") != string::npos) {
    
    //get the extra options here:
    bool no_osc                 = (param_list_opt.find("no-osc-params"    ) != string::npos);
    bool fix_osc_params         = (param_list_opt.find("fix-osc-params"   ) != string::npos);
    bool cons_osc_params        = (param_list_opt.find("cons-osc-params"  ) != string::npos);
    bool cons_atm_params        = (param_list_opt.find("cons-atm-params"  ) != string::npos);
    bool cons_solar_params      = (param_list_opt.find("cons-solar-params") != string::npos);
    bool cons_theta13           = (param_list_opt.find("cons-theta13"     ) != string::npos);
    bool fix_detector_params    = (param_list_opt.find("fix-det-syst"     ) != string::npos);
    bool fix_nd_detector_params = (param_list_opt.find("fix-nd-det-syst"  ) != string::npos);
    bool fix_fd_detector_params = (param_list_opt.find("fix-fd-det-syst"  ) != string::npos);
    bool fix_flux_params        = (param_list_opt.find("fix-flux-syst"    ) != string::npos);
    bool fix_nd_flux_params     = (param_list_opt.find("fix-nd-flux-syst" ) != string::npos);
    bool fix_fd_flux_params     = (param_list_opt.find("fix-fd-flux-syst" ) != string::npos);
    bool fix_int_params         = (param_list_opt.find("fix-int-syst"     ) != string::npos);
    bool fix_mec_params         = (param_list_opt.find("fix-mec-syst"     ) != string::npos);
    bool fix_fsi_params         = (param_list_opt.find("fix-fsi-syst"     ) != string::npos);
    
    int nparams = 0;
    if (syst) {
      nparams = syst->Size(); 
      if (!no_osc) {nparams+=6;} //3fosc
    }
    else{
      for(int ip = 0; ip < kNFitParams; ip++) {
        PhysParamId_t p = kFitParam[ip];
        if (p == kPhypUndefined) {continue;}
        if (no_osc && util::IsOscParam(p)) {continue;}
        nparams++;
      }
    }

    fparm = new FitParamList(nparams);
    int ipc = 0; //counter with no gaps, in case of `kPhypUndefined' params

    //if osc params constrained, set priors
    if(cons_osc_params) {
      util::InitializeOAPriors();
    }

    //now loop over parameters to add them to the list
    for(int ip = 0; ip < kNFitParams; ip++) {
      PhysParamId_t p = kFitParam[ip];
      if(p == kPhypUndefined) continue;

      // set parameter range, current and init value, etc
      double init = 1.0;
      double curr = 1.0;
      double min  = 0.0;
      double max  = 2.0;
      double step = 1E-4;
      bool   fix  = false;
      bool   nuis = true;
      
      if(IsOscParam(p)) {
        if (no_osc) {continue;}
        init = util::OscParamInitValue(p);
        curr = util::OscParamInitValue(p);
        min  = util::OscParamMinValue(p);
        max  = util::OscParamMaxValue(p);
        step = util::OscParamStepSize(p);
        nuis = false;
      }
      
      if(not (util::IsSystematic(p)&&syst) ) {
        // Check we're not going behind physical region
        min = PhysicalParameterLimits::Instance()->GetNearestPhysicalValue(p,min);
        max = PhysicalParameterLimits::Instance()->GetNearestPhysicalValue(p,max);
        
        fparm->AddParam(ipc, p, init, min, max, step, fix, nuis);    
        ipc++; 
        fparm->Update(p, curr);
      }
    } //ip
    
    // If necessary, add the systematics from the model
    if (syst) {
      syst->AppendParamsTo(*fparm);
      // And update their limits
      for (unsigned int ip = 0 ; ip < syst->Size(); ip++) {
        conv::PhysParamId_t p = syst->WhichParam(ip);
        fparm->SetMinValue(p, PhysicalParameterLimits::Instance()->GetNearestPhysicalValue(p,0.));
        fparm->SetMaxValue(p, PhysicalParameterLimits::Instance()->GetNearestPhysicalValue(p,2.));
      }
    }
    
    // Fix/set parameters as necessary
    for(int ip = 0; ip < nparams; ip++) {
      conv::PhysParamId_t p = fparm->WhichParam(ip);
      // toggle oscillation params on/off
      if(fix_osc_params && IsOscParam(p)){
        double init_value = util::OscParamInitValue(p);
        fparm->Update(p, init_value);
        fparm->SetInitValue(p, init_value);
        fparm->FixParameter(p);
      }     
          
      //constrain osc params
      if(cons_osc_params && IsOscParam(p)){
        fparm->SetNuisance(p,true);
      }
      
      //constrain solar params
      if(cons_solar_params){
        fparm->SetNuisance(conv::kPhypMixing12,true);
        fparm->SetNuisance(conv::kPhypDm12sq  ,true);
      }
      
      //constrain atmospheric params
      if(cons_atm_params){
        fparm->SetNuisance(conv::kPhypMixing23,true);
        fparm->SetNuisance(conv::kPhypDm23sq  ,true);
      }
      
      if (cons_theta13) {
        fparm->SetNuisance(conv::kPhypMixing13,true);
      }

      // toggle detector related params on/off
      if(fix_detector_params && kFitIsNuDetRelated[ip]) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      if(fix_nd_detector_params && util::IsNuNDDetRelated(p)) {
        fparm->Update(p, 1.);      
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      if(fix_fd_detector_params && util::IsNuFDDetRelated(p)) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      // toggle flux related params on/off
      if(fix_flux_params && kFitIsNuFluxRelated[ip]) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      // toggle nd flux related params on/off
      if(fix_nd_flux_params && kFitIsNDNuFluxRelated[ip]){
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      // toggle fd flux related params on/off
      if(fix_fd_flux_params && kFitIsFDNuFluxRelated[ip]){
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      // toggle int related params on/off
      if(fix_int_params && kFitIsNuIntRelated[ip]) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
        // toggle mec related params on/off
      if(fix_mec_params && (p==kNuisIntNuCCMEC || p==kNuisIntNuBarCCMEC)) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      
      // toggle FSI related params on/off
      if(fix_fsi_params && util::IsFSI(p)) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }

    }//ip
  }
  //now we also defined a ND only fit params list
  else  if(param_list_opt.find("only-nd") != string::npos) {
    
    int n_nd_params = 0;
    // Count the number of params we need:
    for(int ip = 0; ip < kNFitParams; ip++) {
      PhysParamId_t p = kFitParam[ip];
      if(p == kPhypUndefined) continue;
      if(!kFitIsNDNuFluxRelated[ip] && !kFitIsNuNDDetRelated[ip] && !kFitIsNuIntRelated[ip]) {
        continue;
      }
      n_nd_params++;
    }
    fparm = new FitParamList(n_nd_params);
    

    //get other options
    bool fix_detector_params = (param_list_opt.find("fix-det-syst")  != string::npos);
    bool fix_flux_params     = (param_list_opt.find("fix-flux-syst") != string::npos);
    bool fix_int_params      = (param_list_opt.find("fix-int-syst")  != string::npos);
    bool fix_mec_params      = (param_list_opt.find("fix-mec-syst")  != string::npos);
    bool fix_fsi_params      = (param_list_opt.find("fix-fsi-syst")  != string::npos);

    //now loop over parameters
    int ipc = 0; //counter with no gaps, in case of `kPhypUndefined' params
    for(int ip = 0; ip < kNFitParams; ip++) {
      PhysParamId_t p = kFitParam[ip];
      if(p == kPhypUndefined) continue;
      
      // If not ND, move on
      if(!kFitIsNDNuFluxRelated[ip] && !kFitIsNuNDDetRelated[ip] && !kFitIsNuIntRelated[ip]) {
        continue;
      }

      // set parameter range, current and init value, etc
      double init = 1.0;
      double curr = 1.0;
      double min  = 0.0;
      double max  = 2.0;
      double step = 1E-4;
      bool   fix  = false;
      bool   nuis = true;

      //~ if(IsSystematic(p) {
      // Check we're not going behind physical region
      min = PhysicalParameterLimits::Instance()->GetNearestPhysicalValue(p,min);
      max = PhysicalParameterLimits::Instance()->GetNearestPhysicalValue(p,max);

      fparm->AddParam(ipc, p, init, min, max, step, fix, nuis);
      ipc++;
      fparm->Update(p, curr);

      // toggle detector params on/off
      if(fix_detector_params && kFitIsNuDetRelated[ip]) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      // toggle flux related params on/off
      if(fix_flux_params && kFitIsNuFluxRelated[ip]) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      // toggle int related params on/off                                                                                        
      if(fix_int_params && kFitIsNuIntRelated[ip]) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      // toggle mec related params on/off                                                                                           
      if(fix_mec_params && (p==kNuisIntNuCCMEC || p==kNuisIntNuBarCCMEC)) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      // toggle FSI related params on/off                                                                                      
      if(fix_fsi_params && util::IsFSI(p)) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }

    }//ip
  
  }
  else {
    LOG("FitParams",pERROR)<<"Unrecognised fit parameter list name: "<<param_list_opt;
    util::Die(-1); return fparm;
  }

  if(!fparm->IsComplete()) {
    LOG("FitParams",pERROR)<<"Fit parameter list is not complete";
    fparm->Print();
    util::Die(-1); return fparm;
  }

  return fparm;
}
//____________________________________________________________________________
bool valor::util::IsOscParam(conv::PhysParamId_t p)
{
  if(util::IsMixingAngle(p) || util::IsMassSplitting(p) || util::IsPhase(p)) return true;
  else return false;
}
//____________________________________________________________________________
bool valor::util::IsSystematic(conv::PhysParamId_t p)
{
  return (!util::IsOscParam(p));
}
//____________________________________________________________________________
bool valor::util::IsNuFluxRelated(conv::PhysParamId_t p)
{
  int nd_index = ArrIdx::Instance()->FitParamIdx(p);
  if (nd_index==-1) {
    return false;
  }
  return conv::kFitIsNuFluxRelated[nd_index];
}
//____________________________________________________________________________
bool valor::util::IsNuIntRelated(conv::PhysParamId_t p)
{
  int nd_index = ArrIdx::Instance()->FitParamIdx(p);
  if (nd_index==-1) {
    return false;
  }
  return conv::kFitIsNuIntRelated[nd_index];
}
//____________________________________________________________________________
bool valor::util::IsNuDetRelated(conv::PhysParamId_t p)
{
  int nd_index = ArrIdx::Instance()->FitParamIdx(p);
  if (nd_index==-1) {
    return false;
  }
  return conv::kFitIsNuDetRelated[nd_index];
}
//____________________________________________________________________________
bool valor::util::IsNuNDDetRelated(conv::PhysParamId_t p)
{
  int nd_index = ArrIdx::Instance()->FitParamIdx(p);
  if (nd_index==-1) {
    return false;
  }
  return conv::kFitIsNuNDDetRelated[nd_index];
}
//____________________________________________________________________________
bool valor::util::IsNuFDDetRelated(conv::PhysParamId_t p)
{
  int nd_index = ArrIdx::Instance()->FitParamIdx(p);
  if (nd_index==-1) {
    return false;
  }
  return conv::kFitIsNuFDDetRelated[nd_index];
}
//____________________________________________________________________________
bool valor::util::IsNDFluxRelated(conv::PhysParamId_t p)
{
  return (p >= kNuisNDFluxFirstParameter && p<=kNuisNDFluxLastParameter);
}
//____________________________________________________________________________
bool valor::util::IsFDFluxRelated(conv::PhysParamId_t p)
{
  return (p >= kNuisFDFluxFirstParameter && p<=kNuisFDFluxLastParameter);
  }
//____________________________________________________________________________
bool valor::util::IsFSI(conv::PhysParamId_t p)
{
  return (p >= kNuisIntPiMeanFreePath && p<=kNuisIntFracNucProduction);
}
//____________________________________________________________________________        
bool util::OscProbIsAppliedTo(conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s, conv::ReacMode_t m)
{
  static const ArrIdx * arridx = ArrIdx::Instance();

  if (d==conv::kdUndefined   ) {return false;}
  if (b==conv::kbUndefined   ) {return false;}
  if (m==conv::kmUndefined   ) {return false;}
  if (s==conv::ksUndefined   ) {return false;}

  // loop over osc param ids - check if any is applied to the sample+mode+beam
 
  int ip_min = arridx->FitParamIdx(kOscFirstParam);
  int ip_max = arridx->FitParamIdx(kOscLastParam);
  bool apply = false;
  for(int ip = ip_min; ip<=ip_max; ip++){
    conv::ApplyMask_t pmask = conv::kApplyParamToTemplates[ip];
    bool apply_to_detector = (kApplyToDetector [d] & pmask.detector).any();
    if(apply_to_detector) apply = true;
  }
  return apply;
}
//____________________________________________________________________________
bool util::ParamIsAppliedTo(
  conv::BeamConf_t b, conv::Sample_t s, conv::Detector_t d, conv::ReacMode_t m, conv::PhysParamId_t p)
{
  static const ArrIdx * arridx = ArrIdx::Instance();
  
  NuclearTarget_t nt = conv::kntInclusive; // Make this an argument
  
  if (b ==conv::kbUndefined   ) {return false;}
  if (m ==conv::kmUndefined   ) {return false;}
  if (s ==conv::ksUndefined   ) {return false;}
  if (d ==conv::kdUndefined   ) {return false;}
  if (nt==conv::kntUndefined  ) {return false;}
  if (p ==conv::kPhypUndefined) {return false;}
  
  // Get parameter mask
  int ip = arridx->FitParamIdx(p);
  if (ip<0) {return false;}
  conv::ApplyMask_t pmask = conv::kApplyParamToTemplates[ip];
  
  NuFlavour_t f = conv::kReacModeToInitFlavour[m];
  ReacType_t  t = conv::kReacModeToType[m];
  
  // Check whether or not to apply the param to this
  bool apply_to_beam     = (kApplyToBeamMode     [b]  & pmask.beam    ).any();
  bool apply_to_sample   = (kApplyToSample       [s]  & pmask.selec   ).any();
  bool apply_to_flavour  = (kApplyToFlavour      [f]  & pmask.flav    ).any();
  bool apply_to_type     = (kApplyToReacType     [t]  & pmask.reactype).any();
  bool apply_to_detector = (kApplyToDetector     [d]  & pmask.detector).any();
  bool apply_to_target   = (kApplyToNuclearTarget[nt] & pmask.target  ).any();
  
  bool apply_to_mode = apply_to_flavour && apply_to_type;
  bool apply = (apply_to_beam && apply_to_sample && apply_to_mode && apply_to_detector && apply_to_target);
  
  //~ std::cerr<<"Param    : "  <<util::AsString(p)<<std::endl;
  //~ std::cerr<<"Beam     : "  <<apply_to_beam    <<"\t("<<util::AsString(b)<<")"<<std::endl;
  //~ std::cerr<<"Sample   : "  <<apply_to_sample  <<"\t("<<util::AsString(s)<<")"<<std::endl;
  //~ std::cerr<<"Detector : "  <<apply_to_detector<<"\t("<<util::AsString(d)<<")"<<std::endl;
  //~ std::cerr<<"Mode     : "  <<apply_to_mode    <<"\t("<<util::AsString(m)<<")"<<std::endl;
  //~ std::cerr<<"Returning: "  <<(apply?"true":"false")<<std::endl;
  
  return apply;
}
//____________________________________________________________________________
bool util::ParamHasSplines(conv::PhysParamId_t p)
{
  for (int ip = 0 ; ip < kNFitParamsWithSplines ; ip++) {
    if (kFitParamsWithSplines[ip]==p) {return true;}
  }
  return false;
}
//____________________________________________________________________________
conv::FitParamGroup_t util::GetParameterGroup(conv::PhysParamId_t p)
{
  if (p==conv::kPhypUndefined) {return conv::kpgUndefined;}
  int ip = ArrIdx::Instance()->FitParamIdx(p);
  if (ip<0) {return conv::kpgUndefined;}
  return conv::kFitParamGroup[ip];
}
//____________________________________________________________________________
const double * util::EtrueRange (conv::PhysParamId_t p)
{
  int idx = util::ArrIdx::Instance()->FitParamIdx(p);
  if (idx < 0 ) {return NULL;}
  return conv::kFitParamEtrueRange[idx];
}
//____________________________________________________________________________
const double * util::Q2trueRange(conv::PhysParamId_t p)
{
  int idx = util::ArrIdx::Instance()->FitParamIdx(p);
  if (idx < 0 ) {return NULL;}
  return conv::kFitParamQ2trueRange[idx];
}
//____________________________________________________________________________
std::vector<PhysParamId_t> util::GetParameterSet(std::string set_name)
{
  vector<PhysParamId_t> vec;
  set_name = util::ToLowerCase(set_name);
  if (set_name == "ccqe") {
    vec.push_back(kNuisIntNuCCQE1   );
    vec.push_back(kNuisIntNuCCQE2   );
    vec.push_back(kNuisIntNuCCQE3   );
    vec.push_back(kNuisIntNuBarCCQE1);
    vec.push_back(kNuisIntNuBarCCQE2);
    vec.push_back(kNuisIntNuBarCCQE3);
  }
  if(set_name == "mec") {
    vec.push_back(kNuisIntNuCCMEC   );
    vec.push_back(kNuisIntNuBarCCMEC);
  }
  if (set_name == "cc1piz") {
    vec.push_back(kNuisIntNuCC1piz1   );
    vec.push_back(kNuisIntNuCC1piz2   );
    vec.push_back(kNuisIntNuCC1piz3   );
    vec.push_back(kNuisIntNuBarCC1piz1);
    vec.push_back(kNuisIntNuBarCC1piz2);
    vec.push_back(kNuisIntNuBarCC1piz3);
  }
  if (set_name == "cc1pic") {
    vec.push_back(kNuisIntNuCC1pic1   );
    vec.push_back(kNuisIntNuCC1pic2   );
    vec.push_back(kNuisIntNuCC1pic3   );
    vec.push_back(kNuisIntNuBarCC1pic1);
    vec.push_back(kNuisIntNuBarCC1pic2);
    vec.push_back(kNuisIntNuBarCC1pic3);
  }
  if (set_name == "res") {
    vec.push_back(kNuisIntNuCC1piz1   );
    vec.push_back(kNuisIntNuCC1piz2   );
    vec.push_back(kNuisIntNuCC1piz3   );
    vec.push_back(kNuisIntNuBarCC1piz1);
    vec.push_back(kNuisIntNuBarCC1piz2);
    vec.push_back(kNuisIntNuBarCC1piz3);
    vec.push_back(kNuisIntNuCC1pic1   );
    vec.push_back(kNuisIntNuCC1pic2   );
    vec.push_back(kNuisIntNuCC1pic3   );
    vec.push_back(kNuisIntNuBarCC1pic1);
    vec.push_back(kNuisIntNuBarCC1pic2);
    vec.push_back(kNuisIntNuBarCC1pic3);
  }
  if (set_name == "cc2pi") {
    vec.push_back(kNuisIntNuCC2Pi   );
    vec.push_back(kNuisIntNuBarCC2Pi);
  }
  if (set_name == "dis") {
    vec.push_back(kNuisIntNuDIS1   );
    vec.push_back(kNuisIntNuDIS2   );
    vec.push_back(kNuisIntNuDIS3   );
    vec.push_back(kNuisIntNuBarDIS1);
    vec.push_back(kNuisIntNuBarDIS2);
    vec.push_back(kNuisIntNuBarDIS3);
  }
  if (set_name == "nc") {
    vec.push_back(kNuisIntNuNormNC   );
    vec.push_back(kNuisIntNuBarNormNC);
  }
  if (set_name == "fsi") {
    vec.push_back(kNuisIntPiMeanFreePath       );
    vec.push_back(kNuisIntNucMeanFreePath      );
    vec.push_back(kNuisIntFracPiChargeExchange );
    vec.push_back(kNuisIntFracPiInelastic      );
    vec.push_back(kNuisIntFracPiAbsorb         );
    vec.push_back(kNuisIntFracPiProduction     );
    vec.push_back(kNuisIntFracNucChargeExchange);
    vec.push_back(kNuisIntFracNucInelastic     );
    vec.push_back(kNuisIntFracNucAbsorb        );
    vec.push_back(kNuisIntFracNucProduction    );
  }
  // All interactions
  if (set_name == "int") {
  for (int ip = kNuisIntFirstParameter; ip <= kNuisIntLastParameter; ip++) {
      vec.push_back((PhysParamId_t)(ip));
    }
  }
  // Fluxes
  if (set_name == "flux") {
    for (int ip = kNuisFluxFirstParameter; ip <= kNuisFluxLastParameter; ip++) {
      vec.push_back((PhysParamId_t)(ip));
    }
  }
  if (set_name == "ndflux") {
    for (int ip = kNuisNDFluxFirstParameter; ip <= kNuisNDFluxLastParameter; ip++) {
      vec.push_back((PhysParamId_t)(ip));
    }
  }
  if (set_name == "fdflux") {
    for (int ip = kNuisFDFluxFirstParameter; ip <= kNuisFDFluxLastParameter; ip++) {
      vec.push_back((PhysParamId_t)(ip));
    }
  }
  // Detector efficiencies
  if (set_name == "det") {
    for (int ip = kNuisDetFirstParameter; ip <= kNuisDetLastParameter; ip++) {
      vec.push_back((PhysParamId_t)(ip));
    }
  }
  if (set_name == "nddet") {
    for (int ip = kNuisNDDetFirstParameter; ip <= kNuisNDDetLastParameter; ip++) {
      vec.push_back((PhysParamId_t)(ip));
    }
  }
  if (set_name == "fddet") {
    for (int ip = kNuisFDDetFirstParameter; ip <= kNuisFDDetLastParameter; ip++) {
      vec.push_back((PhysParamId_t)(ip));
    }
  }
  // OA parameters
  if (set_name == "3fosc") {
    vec.push_back(kPhypMixing23);
    vec.push_back(kPhypMixing13);
    vec.push_back(kPhypMixing12);
    vec.push_back(kPhypCPV     );
    vec.push_back(kPhypDm23sq  );
    vec.push_back(kPhypDm12sq  );
  }
  
  if (set_name == "allsyst") {
    for (int ip = conv::kNuis000 ; ip < conv::knppmax ; ip++) {
      vec.push_back((PhysParamId_t)(ip));
    }
  }
  
  if (set_name == "all") {
    for (int ip = 0 ; ip < conv::knppmax ; ip++) {
      vec.push_back((PhysParamId_t)(ip));
    }
  }
  
  if (vec.size()==0) {
    LOG("FitParams",pWARN)<<"No parameters added to set: "<<set_name;
  }
  return vec;
}
