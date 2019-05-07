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
#include "dune/Conventions/OscParamValues.h"
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
string util::AsString(conv::PhysParamId_t p)
{
  //  if (!util::IsSystematic(p)) return util::RawParamAsString(p);

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

    case (kNuisFHCNuMuFDFlux00   ) : return "f_fhc_fd_flux_numu00";    break;
    case (kNuisFHCNuMuFDFlux01   ) : return "f_fhc_fd_flux_numu01";    break;
    case (kNuisFHCNuMuFDFlux02   ) : return "f_fhc_fd_flux_numu02";    break;
    case (kNuisFHCNuMuFDFlux03   ) : return "f_fhc_fd_flux_numu03";    break;
    case (kNuisFHCNuMuFDFlux04   ) : return "f_fhc_fd_flux_numu04";    break;
    case (kNuisFHCNuMuFDFlux05   ) : return "f_fhc_fd_flux_numu05";    break;
    case (kNuisFHCNuMuFDFlux06   ) : return "f_fhc_fd_flux_numu06";    break;
    case (kNuisFHCNuMuFDFlux07   ) : return "f_fhc_fd_flux_numu07";    break;
    case (kNuisFHCNuMuFDFlux08   ) : return "f_fhc_fd_flux_numu08";    break;
    case (kNuisFHCNuMuFDFlux09   ) : return "f_fhc_fd_flux_numu09";    break;
    case (kNuisFHCNuMuFDFlux10   ) : return "f_fhc_fd_flux_numu10";    break;
    case (kNuisFHCNuMuFDFlux11   ) : return "f_fhc_fd_flux_numu11";    break;
    case (kNuisFHCNuMuFDFlux12   ) : return "f_fhc_fd_flux_numu12";    break;
    case (kNuisFHCNuMuFDFlux13   ) : return "f_fhc_fd_flux_numu13";    break;
    case (kNuisFHCNuMuFDFlux14   ) : return "f_fhc_fd_flux_numu14";    break;
    case (kNuisFHCNuMuFDFlux15   ) : return "f_fhc_fd_flux_numu15";    break;
    case (kNuisFHCNuMuFDFlux16   ) : return "f_fhc_fd_flux_numu16";    break;
    case (kNuisFHCNuMuFDFlux17   ) : return "f_fhc_fd_flux_numu17";    break;
    case (kNuisFHCNuMuFDFlux18   ) : return "f_fhc_fd_flux_numu18";    break;
    case (kNuisFHCNuMuBarFDFlux00) : return "f_fhc_fd_flux_numubar00"; break;
    case (kNuisFHCNuMuBarFDFlux01) : return "f_fhc_fd_flux_numubar01"; break;
    case (kNuisFHCNuMuBarFDFlux02) : return "f_fhc_fd_flux_numubar02"; break;
    case (kNuisFHCNuMuBarFDFlux03) : return "f_fhc_fd_flux_numubar03"; break;
    case (kNuisFHCNuMuBarFDFlux04) : return "f_fhc_fd_flux_numubar04"; break;
    case (kNuisFHCNuMuBarFDFlux05) : return "f_fhc_fd_flux_numubar05"; break;
    case (kNuisFHCNuMuBarFDFlux06) : return "f_fhc_fd_flux_numubar06"; break;
    case (kNuisFHCNuMuBarFDFlux07) : return "f_fhc_fd_flux_numubar07"; break;
    case (kNuisFHCNuMuBarFDFlux08) : return "f_fhc_fd_flux_numubar08"; break;
    case (kNuisFHCNuMuBarFDFlux09) : return "f_fhc_fd_flux_numubar09"; break;
    case (kNuisFHCNuMuBarFDFlux10) : return "f_fhc_fd_flux_numubar10"; break;
    case (kNuisFHCNuMuBarFDFlux11) : return "f_fhc_fd_flux_numubar11"; break;
    case (kNuisFHCNuMuBarFDFlux12) : return "f_fhc_fd_flux_numubar12"; break;
    case (kNuisFHCNuMuBarFDFlux13) : return "f_fhc_fd_flux_numubar13"; break;
    case (kNuisFHCNuMuBarFDFlux14) : return "f_fhc_fd_flux_numubar14"; break;
    case (kNuisFHCNuMuBarFDFlux15) : return "f_fhc_fd_flux_numubar15"; break;
    case (kNuisFHCNuMuBarFDFlux16) : return "f_fhc_fd_flux_numubar16"; break;
    case (kNuisFHCNuMuBarFDFlux17) : return "f_fhc_fd_flux_numubar17"; break;
    case (kNuisFHCNuMuBarFDFlux18) : return "f_fhc_fd_flux_numubar18"; break;
    case (kNuisFHCNuEFDFlux00    ) : return "f_fhc_fd_flux_nue00";     break;
    case (kNuisFHCNuEFDFlux01    ) : return "f_fhc_fd_flux_nue01";     break;
    case (kNuisFHCNuEFDFlux02    ) : return "f_fhc_fd_flux_nue02";     break;
    case (kNuisFHCNuEFDFlux03    ) : return "f_fhc_fd_flux_nue03";     break;
    case (kNuisFHCNuEFDFlux04    ) : return "f_fhc_fd_flux_nue04";     break;
    case (kNuisFHCNuEFDFlux05    ) : return "f_fhc_fd_flux_nue05";     break;
    case (kNuisFHCNuEFDFlux06    ) : return "f_fhc_fd_flux_nue06";     break;
    case (kNuisFHCNuEBarFDFlux00 ) : return "f_fhc_fd_flux_nuebar00";  break;
    case (kNuisFHCNuEBarFDFlux01 ) : return "f_fhc_fd_flux_nuebar01";  break;
    case (kNuisFHCNuEBarFDFlux02 ) : return "f_fhc_fd_flux_nuebar02";  break;
    case (kNuisFHCNuEBarFDFlux03 ) : return "f_fhc_fd_flux_nuebar03";  break;
    case (kNuisFHCNuEBarFDFlux04 ) : return "f_fhc_fd_flux_nuebar04";  break;
    case (kNuisFHCNuEBarFDFlux05 ) : return "f_fhc_fd_flux_nuebar05";  break;
    case (kNuisFHCNuEBarFDFlux06 ) : return "f_fhc_fd_flux_nuebar06";  break;

    case (kNuisRHCNuMuFDFlux00   ) : return "f_rhc_fd_flux_numu00";    break;
    case (kNuisRHCNuMuFDFlux01   ) : return "f_rhc_fd_flux_numu01";    break;
    case (kNuisRHCNuMuFDFlux02   ) : return "f_rhc_fd_flux_numu02";    break;
    case (kNuisRHCNuMuFDFlux03   ) : return "f_rhc_fd_flux_numu03";    break;
    case (kNuisRHCNuMuFDFlux04   ) : return "f_rhc_fd_flux_numu04";    break;
    case (kNuisRHCNuMuFDFlux05   ) : return "f_rhc_fd_flux_numu05";    break;
    case (kNuisRHCNuMuFDFlux06   ) : return "f_rhc_fd_flux_numu06";    break;
    case (kNuisRHCNuMuFDFlux07   ) : return "f_rhc_fd_flux_numu07";    break;
    case (kNuisRHCNuMuFDFlux08   ) : return "f_rhc_fd_flux_numu08";    break;
    case (kNuisRHCNuMuFDFlux09   ) : return "f_rhc_fd_flux_numu09";    break;
    case (kNuisRHCNuMuFDFlux10   ) : return "f_rhc_fd_flux_numu10";    break;
    case (kNuisRHCNuMuFDFlux11   ) : return "f_rhc_fd_flux_numu11";    break;
    case (kNuisRHCNuMuFDFlux12   ) : return "f_rhc_fd_flux_numu12";    break;
    case (kNuisRHCNuMuFDFlux13   ) : return "f_rhc_fd_flux_numu13";    break;
    case (kNuisRHCNuMuFDFlux14   ) : return "f_rhc_fd_flux_numu14";    break;
    case (kNuisRHCNuMuFDFlux15   ) : return "f_rhc_fd_flux_numu15";    break;
    case (kNuisRHCNuMuFDFlux16   ) : return "f_rhc_fd_flux_numu16";    break;
    case (kNuisRHCNuMuFDFlux17   ) : return "f_rhc_fd_flux_numu17";    break;
    case (kNuisRHCNuMuFDFlux18   ) : return "f_rhc_fd_flux_numu18";    break;
    case (kNuisRHCNuMuBarFDFlux00) : return "f_rhc_fd_flux_numubar00"; break;
    case (kNuisRHCNuMuBarFDFlux01) : return "f_rhc_fd_flux_numubar01"; break;
    case (kNuisRHCNuMuBarFDFlux02) : return "f_rhc_fd_flux_numubar02"; break;
    case (kNuisRHCNuMuBarFDFlux03) : return "f_rhc_fd_flux_numubar03"; break;
    case (kNuisRHCNuMuBarFDFlux04) : return "f_rhc_fd_flux_numubar04"; break;
    case (kNuisRHCNuMuBarFDFlux05) : return "f_rhc_fd_flux_numubar05"; break;
    case (kNuisRHCNuMuBarFDFlux06) : return "f_rhc_fd_flux_numubar06"; break;
    case (kNuisRHCNuMuBarFDFlux07) : return "f_rhc_fd_flux_numubar07"; break;
    case (kNuisRHCNuMuBarFDFlux08) : return "f_rhc_fd_flux_numubar08"; break;
    case (kNuisRHCNuMuBarFDFlux09) : return "f_rhc_fd_flux_numubar09"; break;
    case (kNuisRHCNuMuBarFDFlux10) : return "f_rhc_fd_flux_numubar10"; break;
    case (kNuisRHCNuMuBarFDFlux11) : return "f_rhc_fd_flux_numubar11"; break;
    case (kNuisRHCNuMuBarFDFlux12) : return "f_rhc_fd_flux_numubar12"; break;
    case (kNuisRHCNuMuBarFDFlux13) : return "f_rhc_fd_flux_numubar13"; break;
    case (kNuisRHCNuMuBarFDFlux14) : return "f_rhc_fd_flux_numubar14"; break;
    case (kNuisRHCNuMuBarFDFlux15) : return "f_rhc_fd_flux_numubar15"; break;
    case (kNuisRHCNuMuBarFDFlux16) : return "f_rhc_fd_flux_numubar16"; break;
    case (kNuisRHCNuMuBarFDFlux17) : return "f_rhc_fd_flux_numubar17"; break;
    case (kNuisRHCNuMuBarFDFlux18) : return "f_rhc_fd_flux_numubar18"; break;
    case (kNuisRHCNuEFDFlux00    ) : return "f_rhc_fd_flux_nue00";     break;
    case (kNuisRHCNuEFDFlux01    ) : return "f_rhc_fd_flux_nue01";     break;
    case (kNuisRHCNuEFDFlux02    ) : return "f_rhc_fd_flux_nue02";     break;
    case (kNuisRHCNuEFDFlux03    ) : return "f_rhc_fd_flux_nue03";     break;
    case (kNuisRHCNuEFDFlux04    ) : return "f_rhc_fd_flux_nue04";     break;
    case (kNuisRHCNuEFDFlux05    ) : return "f_rhc_fd_flux_nue05";     break;
    case (kNuisRHCNuEFDFlux06    ) : return "f_rhc_fd_flux_nue06";     break;
    case (kNuisRHCNuEBarFDFlux00 ) : return "f_rhc_fd_flux_nuebar00";  break;
    case (kNuisRHCNuEBarFDFlux01 ) : return "f_rhc_fd_flux_nuebar01";  break;
    case (kNuisRHCNuEBarFDFlux02 ) : return "f_rhc_fd_flux_nuebar02";  break;
    case (kNuisRHCNuEBarFDFlux03 ) : return "f_rhc_fd_flux_nuebar03";  break;
    case (kNuisRHCNuEBarFDFlux04 ) : return "f_rhc_fd_flux_nuebar04";  break;
    case (kNuisRHCNuEBarFDFlux05 ) : return "f_rhc_fd_flux_nuebar05";  break;
    case (kNuisRHCNuEBarFDFlux06 ) : return "f_rhc_fd_flux_nuebar06";  break;
      
    case (kNuisNormCCQE        ) : return "f_ccqe";               break;
    case (kNuisNormCC1piC      ) : return "f_cc1pic";             break;
    case (kNuisNormCC1pi0      ) : return "f_cc1pi0";             break;
    case (kNuisNormCCoth       ) : return "f_ccoth";              break;
    case (kNuisNormNC          ) : return "f_nc";                 break;
    case (kNuisRatioNuENuMu    ) : return "f_nuecc_numucc";       break;

    case (kNuisEffNuMuCC0pi1trk ) : return "f_eff_numucc0pi1trk";  break;
    case (kNuisEffNuMuCC0pi2trk ) : return "f_eff_numucc0pi2trk";  break;
    case (kNuisEffNuMuCC1piC    ) : return "f_eff_numucc1pic";     break;
    case (kNuisEffNuMuCC1pi0    ) : return "f_eff_numucc1pi0";     break;
    case (kNuisEffNuMuCC1piC1pi0) : return "f_eff_numucc1pic1piz"; break;
    case (kNuisEffNuMuCCoth     ) : return "f_eff_numuccoth";      break;
    case (kNuisEffNuECC         ) : return "f_eff_nuecc";          break;
    case (kNuisEffNuMuCCWS      ) : return "f_eff_numuccwsgn";     break;
    case (kNuisEffNC            ) : return "f_eff_nc";             break;
    
    case (kNuisEffFHCnumuCC0pi1trk01        ) : return "f_eff_fhc_numucc_0pi_1trk_01" ; break;
    case (kNuisEffFHCnumuCC0pi1trk02        ) : return "f_eff_fhc_numucc_0pi_1trk_02" ; break;
    case (kNuisEffFHCnumuCC0pi1trk03        ) : return "f_eff_fhc_numucc_0pi_1trk_03" ; break;
    case (kNuisEffFHCnumuCC0pi1trk04        ) : return "f_eff_fhc_numucc_0pi_1trk_04" ; break;
    case (kNuisEffFHCnumuCC0pi1trk05        ) : return "f_eff_fhc_numucc_0pi_1trk_05" ; break;
    case (kNuisEffFHCnumuCC0pi1trk06        ) : return "f_eff_fhc_numucc_0pi_1trk_06" ; break;
    case (kNuisEffFHCnumuCC0pi1trk07        ) : return "f_eff_fhc_numucc_0pi_1trk_07" ; break;
    case (kNuisEffFHCnumuCC0pi1trk08        ) : return "f_eff_fhc_numucc_0pi_1trk_08" ; break;
    case (kNuisEffFHCnumuCC0pi1trk09        ) : return "f_eff_fhc_numucc_0pi_1trk_09" ; break;
    case (kNuisEffFHCnumuCC0pi2trk01        ) : return "f_eff_fhc_numucc_0pi_2trk_01" ; break;
    case (kNuisEffFHCnumuCC0pi2trk02        ) : return "f_eff_fhc_numucc_0pi_2trk_02" ; break;
    case (kNuisEffFHCnumuCC0pi2trk03        ) : return "f_eff_fhc_numucc_0pi_2trk_03" ; break;
    case (kNuisEffFHCnumuCC0pi2trk04        ) : return "f_eff_fhc_numucc_0pi_2trk_04" ; break;
    case (kNuisEffFHCnumuCC0pi2trk05        ) : return "f_eff_fhc_numucc_0pi_2trk_05" ; break;
    case (kNuisEffFHCnumuCC0pi2trk06        ) : return "f_eff_fhc_numucc_0pi_2trk_06" ; break;
    case (kNuisEffFHCnumuCC0pi2trk07        ) : return "f_eff_fhc_numucc_0pi_2trk_07" ; break;
    case (kNuisEffFHCnumuCC0pi2trk08        ) : return "f_eff_fhc_numucc_0pi_2trk_08" ; break;
    case (kNuisEffFHCnumuCC0pi2trk09        ) : return "f_eff_fhc_numucc_0pi_2trk_09" ; break;
    case (kNuisEffFHCnumuCC0piNtrk01        ) : return "f_eff_fhc_numucc_0pi_ntrk_01" ; break;
    case (kNuisEffFHCnumuCC0piNtrk02        ) : return "f_eff_fhc_numucc_0pi_ntrk_02" ; break;
    case (kNuisEffFHCnumuCC0piNtrk03        ) : return "f_eff_fhc_numucc_0pi_ntrk_03" ; break;
    case (kNuisEffFHCnumuCC0piNtrk04        ) : return "f_eff_fhc_numucc_0pi_ntrk_04" ; break;
    case (kNuisEffFHCnumuCC0piNtrk05        ) : return "f_eff_fhc_numucc_0pi_ntrk_05" ; break;
    case (kNuisEffFHCnumuCC0piNtrk06        ) : return "f_eff_fhc_numucc_0pi_ntrk_06" ; break;
    case (kNuisEffFHCnumuCC0piNtrk07        ) : return "f_eff_fhc_numucc_0pi_ntrk_07" ; break;
    case (kNuisEffFHCnumuCC0piNtrk08        ) : return "f_eff_fhc_numucc_0pi_ntrk_08" ; break;
    case (kNuisEffFHCnumuCC0piNtrk09        ) : return "f_eff_fhc_numucc_0pi_ntrk_09" ; break;
    case (kNuisEffFHCnumuCC0piNtrk10        ) : return "f_eff_fhc_numucc_0pi_ntrk_10" ; break;
    case (kNuisEffFHCnumuCC0piNtrk11        ) : return "f_eff_fhc_numucc_0pi_ntrk_11" ; break;
    case (kNuisEffFHCnumuCC0piNtrk12        ) : return "f_eff_fhc_numucc_0pi_ntrk_12" ; break;
    case (kNuisEffFHCnumuCC0piNtrk13        ) : return "f_eff_fhc_numucc_0pi_ntrk_13" ; break;
    case (kNuisEffFHCnumuCC0piNtrk14        ) : return "f_eff_fhc_numucc_0pi_ntrk_14" ; break;
    case (kNuisEffFHCnumuCC0piNtrk15        ) : return "f_eff_fhc_numucc_0pi_ntrk_15" ; break;
    case (kNuisEffFHCnumuCC1pi3trkDelta01   ) : return "f_eff_fhc_numucc_1pi3trk_delta_01" ; break;
    case (kNuisEffFHCnumuCC1pi3trkDelta02   ) : return "f_eff_fhc_numucc_1pi3trk_delta_02" ; break;
    case (kNuisEffFHCnumuCC1pi3trkDelta03   ) : return "f_eff_fhc_numucc_1pi3trk_delta_03" ; break;
    case (kNuisEffFHCnumuCC1pi3trkDelta04   ) : return "f_eff_fhc_numucc_1pi3trk_delta_04" ; break;
    case (kNuisEffFHCnumuCC1pi3trkDelta05   ) : return "f_eff_fhc_numucc_1pi3trk_delta_05" ; break;
    case (kNuisEffFHCnumuCC1pi3trkDelta06   ) : return "f_eff_fhc_numucc_1pi3trk_delta_06" ; break;
    case (kNuisEffFHCnumuCC1pi3trkDelta07   ) : return "f_eff_fhc_numucc_1pi3trk_delta_07" ; break;
    case (kNuisEffFHCnumuCC1pi3trkDelta08   ) : return "f_eff_fhc_numucc_1pi3trk_delta_08" ; break;
    case (kNuisEffFHCnumuCC1pi3trkDelta09   ) : return "f_eff_fhc_numucc_1pi3trk_delta_09" ; break;
    case (kNuisEffFHCnumuCC1pi3trkDelta10   ) : return "f_eff_fhc_numucc_1pi3trk_delta_10" ; break;
    case (kNuisEffFHCnumuCC1pi3trkDelta11   ) : return "f_eff_fhc_numucc_1pi3trk_delta_11" ; break;
    case (kNuisEffFHCnumuCC1pi3trkDelta12   ) : return "f_eff_fhc_numucc_1pi3trk_delta_12" ; break;
    case (kNuisEffFHCnumuCC1pi3trkDelta13   ) : return "f_eff_fhc_numucc_1pi3trk_delta_13" ; break;
    case (kNuisEffFHCnumuCC1pi3trkDelta14   ) : return "f_eff_fhc_numucc_1pi3trk_delta_14" ; break;
    case (kNuisEffFHCnumuCC1pi3trkDelta15   ) : return "f_eff_fhc_numucc_1pi3trk_delta_15" ; break;
    case (kNuisEffFHCnumuCC1pic01           ) : return "f_eff_fhc_numucc_1pic_01" ; break;
    case (kNuisEffFHCnumuCC1pic02           ) : return "f_eff_fhc_numucc_1pic_02" ; break;
    case (kNuisEffFHCnumuCC1pic03           ) : return "f_eff_fhc_numucc_1pic_03" ; break;
    case (kNuisEffFHCnumuCC1pic04           ) : return "f_eff_fhc_numucc_1pic_04" ; break;
    case (kNuisEffFHCnumuCC1pic05           ) : return "f_eff_fhc_numucc_1pic_05" ; break;
    case (kNuisEffFHCnumuCC1pic06           ) : return "f_eff_fhc_numucc_1pic_06" ; break;
    case (kNuisEffFHCnumuCC1pic07           ) : return "f_eff_fhc_numucc_1pic_07" ; break;
    case (kNuisEffFHCnumuCC1pic08           ) : return "f_eff_fhc_numucc_1pic_08" ; break;
    case (kNuisEffFHCnumuCC1pic09           ) : return "f_eff_fhc_numucc_1pic_09" ; break;
    case (kNuisEffFHCnumuCC1piz01           ) : return "f_eff_fhc_numucc_1piz01" ; break;
    case (kNuisEffFHCnumuCC1piz02           ) : return "f_eff_fhc_numucc_1piz02" ; break;
    case (kNuisEffFHCnumuCC1piz03           ) : return "f_eff_fhc_numucc_1piz03" ; break;
    case (kNuisEffFHCnumuCC1piz04           ) : return "f_eff_fhc_numucc_1piz04" ; break;
    case (kNuisEffFHCnumuCC1piz05           ) : return "f_eff_fhc_numucc_1piz05" ; break;
    case (kNuisEffFHCnumuCC1piz06           ) : return "f_eff_fhc_numucc_1piz06" ; break;
    case (kNuisEffFHCnumuCC1piz07           ) : return "f_eff_fhc_numucc_1piz07" ; break;
    case (kNuisEffFHCnumuCC1piz08           ) : return "f_eff_fhc_numucc_1piz08" ; break;
    case (kNuisEffFHCnumuCC1piz09           ) : return "f_eff_fhc_numucc_1piz09" ; break;
    case (kNuisEffFHCnumuCC1pic1piz01       ) : return "f_eff_fhc_numucc_1pic_1piz01" ; break;
    case (kNuisEffFHCnumuCC1pic1piz02       ) : return "f_eff_fhc_numucc_1pic_1piz02" ; break;
    case (kNuisEffFHCnumuCC1pic1piz03       ) : return "f_eff_fhc_numucc_1pic_1piz03" ; break;
    case (kNuisEffFHCnumuCC1pic1piz04       ) : return "f_eff_fhc_numucc_1pic_1piz04" ; break;
    case (kNuisEffFHCnumuCC1pic1piz05       ) : return "f_eff_fhc_numucc_1pic_1piz05" ; break;
    case (kNuisEffFHCnumuCC1pic1piz06       ) : return "f_eff_fhc_numucc_1pic_1piz06" ; break;
    case (kNuisEffFHCnumuCC1pic1piz07       ) : return "f_eff_fhc_numucc_1pic_1piz07" ; break;
    case (kNuisEffFHCnumuCC1pic1piz08       ) : return "f_eff_fhc_numucc_1pic_1piz08" ; break;
    case (kNuisEffFHCnumuCC1pic1piz09       ) : return "f_eff_fhc_numucc_1pic_1piz09" ; break;
    case (kNuisEffFHCnumuCCother01          ) : return "f_eff_fhc_numucc_other_01" ; break;
    case (kNuisEffFHCnumuCCother02          ) : return "f_eff_fhc_numucc_other_02" ; break;
    case (kNuisEffFHCnumuCCother03          ) : return "f_eff_fhc_numucc_other_03" ; break;
    case (kNuisEffFHCnumuCCother04          ) : return "f_eff_fhc_numucc_other_04" ; break;
    case (kNuisEffFHCnumuCCother05          ) : return "f_eff_fhc_numucc_other_05" ; break;
    case (kNuisEffFHCnumuCCother06          ) : return "f_eff_fhc_numucc_other_06" ; break;
    case (kNuisEffFHCnumuCCother07          ) : return "f_eff_fhc_numucc_other_07" ; break;
    case (kNuisEffFHCnumuCCother08          ) : return "f_eff_fhc_numucc_other_08" ; break;
    case (kNuisEffFHCnumuCCother09          ) : return "f_eff_fhc_numucc_other_09" ; break;
    case (kNuisEffFHCnumuCCother10          ) : return "f_eff_fhc_numucc_other_10" ; break;
    case (kNuisEffFHCnumuCCother11          ) : return "f_eff_fhc_numucc_other_11" ; break;
    case (kNuisEffFHCnumuCCWS0pi01          ) : return "f_eff_fhc_numucc_ws_0pi_01" ; break;
    case (kNuisEffFHCnumuCCWS0pi02          ) : return "f_eff_fhc_numucc_ws_0pi_02" ; break;
    case (kNuisEffFHCnumuCCWS0pi03          ) : return "f_eff_fhc_numucc_ws_0pi_03" ; break;
    case (kNuisEffFHCnumuCCWS0pi04          ) : return "f_eff_fhc_numucc_ws_0pi_04" ; break;
    case (kNuisEffFHCnumuCCWS0pi05          ) : return "f_eff_fhc_numucc_ws_0pi_05" ; break;
    case (kNuisEffFHCnumuCCWS1pic01         ) : return "f_eff_fhc_numucc_ws_1pic_01" ; break;
    case (kNuisEffFHCnumuCCWS1pic02         ) : return "f_eff_fhc_numucc_ws_1pic_02" ; break;
    case (kNuisEffFHCnumuCCWS1pic03         ) : return "f_eff_fhc_numucc_ws_1pic_03" ; break;
    case (kNuisEffFHCnumuCCWS1pic04         ) : return "f_eff_fhc_numucc_ws_1pic_04" ; break;
    case (kNuisEffFHCnumuCCWS1pic05         ) : return "f_eff_fhc_numucc_ws_1pic_05" ; break;
    case (kNuisEffFHCnumuCCWS1pic06         ) : return "f_eff_fhc_numucc_ws_1pic_06" ; break;
    case (kNuisEffFHCnumuCCWS1pic07         ) : return "f_eff_fhc_numucc_ws_1pic_07" ; break;
    case (kNuisEffFHCnumuCCWS1pic08         ) : return "f_eff_fhc_numucc_ws_1pic_08" ; break;
    case (kNuisEffFHCnumuCCWS1piz01         ) : return "f_eff_fhc_numucc_ws_1piz_01" ; break;
    case (kNuisEffFHCnumuCCWS1piz02         ) : return "f_eff_fhc_numucc_ws_1piz_02" ; break;
    case (kNuisEffFHCnumuCCWS1piz03         ) : return "f_eff_fhc_numucc_ws_1piz_03" ; break;
    case (kNuisEffFHCnumuCCWSother01        ) : return "f_eff_fhc_numucc_ws_other_01" ; break;
    case (kNuisEffFHCnueCC0pi01             ) : return "f_eff_fhc_nuecc_0pi_01" ; break;
    case (kNuisEffFHCnueCC0pi02             ) : return "f_eff_fhc_nuecc_0pi_02" ; break;
    case (kNuisEffFHCnueCC0pi03             ) : return "f_eff_fhc_nuecc_0pi_03" ; break;
    case (kNuisEffFHCnueCC0pi04             ) : return "f_eff_fhc_nuecc_0pi_04" ; break;
    case (kNuisEffFHCnueCC0pi05             ) : return "f_eff_fhc_nuecc_0pi_05" ; break;
    case (kNuisEffFHCnueCC0pi06             ) : return "f_eff_fhc_nuecc_0pi_06" ; break;
    case (kNuisEffFHCnueCC0pi07             ) : return "f_eff_fhc_nuecc_0pi_07" ; break;
    case (kNuisEffFHCnueCC0pi08             ) : return "f_eff_fhc_nuecc_0pi_08" ; break;
    case (kNuisEffFHCnueCC0pi09             ) : return "f_eff_fhc_nuecc_0pi_09" ; break;
    case (kNuisEffFHCnueCC1pic01            ) : return "f_eff_fhc_nuecc_1pic_01" ; break;
    case (kNuisEffFHCnueCC1pic02            ) : return "f_eff_fhc_nuecc_1pic_02" ; break;
    case (kNuisEffFHCnueCC1pic03            ) : return "f_eff_fhc_nuecc_1pic_03" ; break;
    case (kNuisEffFHCnueCC1pic04            ) : return "f_eff_fhc_nuecc_1pic_04" ; break;
    case (kNuisEffFHCnueCC1pic05            ) : return "f_eff_fhc_nuecc_1pic_05" ; break;
    case (kNuisEffFHCnueCC1pic06            ) : return "f_eff_fhc_nuecc_1pic_06" ; break;
    case (kNuisEffFHCnueCC1pic07            ) : return "f_eff_fhc_nuecc_1pic_07" ; break;
    case (kNuisEffFHCnueCC1pic08            ) : return "f_eff_fhc_nuecc_1pic_08" ; break;
    case (kNuisEffFHCnueCC1pic09            ) : return "f_eff_fhc_nuecc_1pic_09" ; break;
    case (kNuisEffFHCnueCC1piz01            ) : return "f_eff_fhc_nuecc_1piz_01" ; break;
    case (kNuisEffFHCnueCC1piz02            ) : return "f_eff_fhc_nuecc_1piz_02" ; break;
    case (kNuisEffFHCnueCC1piz03            ) : return "f_eff_fhc_nuecc_1piz_03" ; break;
    case (kNuisEffFHCnueCC1piz04            ) : return "f_eff_fhc_nuecc_1piz_04" ; break;
    case (kNuisEffFHCnueCC1piz05            ) : return "f_eff_fhc_nuecc_1piz_05" ; break;
    case (kNuisEffFHCnueCC1piz06            ) : return "f_eff_fhc_nuecc_1piz_06" ; break;
    case (kNuisEffFHCnueCC1piz07            ) : return "f_eff_fhc_nuecc_1piz_07" ; break;
    case (kNuisEffFHCnueCC1piz08            ) : return "f_eff_fhc_nuecc_1piz_08" ; break;
    case (kNuisEffFHCnueCC1piz09            ) : return "f_eff_fhc_nuecc_1piz_09" ; break;
    case (kNuisEffFHCnueCCother01           ) : return "f_eff_fhc_nuecc_other_01" ; break;
    case (kNuisEffFHCnueCCother02           ) : return "f_eff_fhc_nuecc_other_02" ; break;
    case (kNuisEffFHCnueCCother03           ) : return "f_eff_fhc_nuecc_other_03" ; break;
    case (kNuisEffFHCnueCCother04           ) : return "f_eff_fhc_nuecc_other_04" ; break;
    case (kNuisEffFHCnueCCother05           ) : return "f_eff_fhc_nuecc_other_05" ; break;
    case (kNuisEffFHCnueCCother06           ) : return "f_eff_fhc_nuecc_other_06" ; break;
    case (kNuisEffFHCnueCCother07           ) : return "f_eff_fhc_nuecc_other_07" ; break;
    case (kNuisEffFHCnueCCother08           ) : return "f_eff_fhc_nuecc_other_08" ; break;
    case (kNuisEffFHCnueCCother09           ) : return "f_eff_fhc_nuecc_other_09" ; break;
    case (kNuisEffFHCnueCCother10           ) : return "f_eff_fhc_nuecc_other_10" ; break;
    case (kNuisEffFHCnueCCother11           ) : return "f_eff_fhc_nuecc_other_11" ; break;
    case (kNuisEffFHCnueCCWS01              ) : return "f_eff_fhc_nuecc_ws_01" ; break;
    case (kNuisEffFHCnueCCWS02              ) : return "f_eff_fhc_nuecc_ws_02" ; break;
    case (kNuisEffFHCNC0pi01                ) : return "f_eff_fhc_nc_0pi_01" ; break;
    case (kNuisEffFHCNC0pi02                ) : return "f_eff_fhc_nc_0pi_02" ; break;
    case (kNuisEffFHCNC0pi03                ) : return "f_eff_fhc_nc_0pi_03" ; break;
    case (kNuisEffFHCNC1pic01               ) : return "f_eff_fhc_nc_1pic_01" ; break;
    case (kNuisEffFHCNC1pic02               ) : return "f_eff_fhc_nc_1pic_02" ; break;
    case (kNuisEffFHCNC1pic03               ) : return "f_eff_fhc_nc_1pic_03" ; break;
    case (kNuisEffFHCNC1piz01               ) : return "f_eff_fhc_nc_1piz_01" ; break;
    case (kNuisEffFHCNC1piz02               ) : return "f_eff_fhc_nc_1piz_02" ; break;
    case (kNuisEffFHCNC1piz03               ) : return "f_eff_fhc_nc_1piz_03" ; break;
    case (kNuisEffFHCNCother01              ) : return "f_eff_fhc_nc_other_01" ; break;
    case (kNuisEffFHCNCother02              ) : return "f_eff_fhc_nc_other_02" ; break;
    case (kNuisEffFHCNCother03              ) : return "f_eff_fhc_nc_other_03" ; break;
    case (kNuisEffFHCNeutrinoElec           ) : return "f_eff_fhc_neutrinoelec" ; break;
    case (kNuisEffFHCIMD                    ) : return "f_eff_fhc_imd" ; break;
    case (kNuisEffRHCnumuCC0pi1trk01        ) : return "f_eff_rhc_numucc_0pi_1trk_01" ; break;
    case (kNuisEffRHCnumuCC0pi1trk02        ) : return "f_eff_rhc_numucc_0pi_1trk_02" ; break;
    case (kNuisEffRHCnumuCC0pi1trk03        ) : return "f_eff_rhc_numucc_0pi_1trk_03" ; break;
    case (kNuisEffRHCnumuCC0pi1trk04        ) : return "f_eff_rhc_numucc_0pi_1trk_04" ; break;
    case (kNuisEffRHCnumuCC0pi1trk05        ) : return "f_eff_rhc_numucc_0pi_1trk_05" ; break;
    case (kNuisEffRHCnumuCC0pi1trk06        ) : return "f_eff_rhc_numucc_0pi_1trk_06" ; break;
    case (kNuisEffRHCnumuCC0pi1trk07        ) : return "f_eff_rhc_numucc_0pi_1trk_07" ; break;
    case (kNuisEffRHCnumuCC0pi1trk08        ) : return "f_eff_rhc_numucc_0pi_1trk_08" ; break;
    case (kNuisEffRHCnumuCC0pi1trk09        ) : return "f_eff_rhc_numucc_0pi_1trk_09" ; break;
    case (kNuisEffRHCnumuCC0pi2trk01        ) : return "f_eff_rhc_numucc_0pi_2trk_01" ; break;
    case (kNuisEffRHCnumuCC0pi2trk02        ) : return "f_eff_rhc_numucc_0pi_2trk_02" ; break;
    case (kNuisEffRHCnumuCC0pi2trk03        ) : return "f_eff_rhc_numucc_0pi_2trk_03" ; break;
    case (kNuisEffRHCnumuCC0pi2trk04        ) : return "f_eff_rhc_numucc_0pi_2trk_04" ; break;
    case (kNuisEffRHCnumuCC0pi2trk05        ) : return "f_eff_rhc_numucc_0pi_2trk_05" ; break;
    case (kNuisEffRHCnumuCC0pi2trk06        ) : return "f_eff_rhc_numucc_0pi_2trk_06" ; break;
    case (kNuisEffRHCnumuCC0pi2trk07        ) : return "f_eff_rhc_numucc_0pi_2trk_07" ; break;
    case (kNuisEffRHCnumuCC0pi2trk08        ) : return "f_eff_rhc_numucc_0pi_2trk_08" ; break;
    case (kNuisEffRHCnumuCC0pi2trk09        ) : return "f_eff_rhc_numucc_0pi_2trk_09" ; break;
    case (kNuisEffRHCnumuCC0piNtrk01        ) : return "f_eff_rhc_numucc_0pi_ntrk_01" ; break;
    case (kNuisEffRHCnumuCC0piNtrk02        ) : return "f_eff_rhc_numucc_0pi_ntrk_02" ; break;
    case (kNuisEffRHCnumuCC0piNtrk03        ) : return "f_eff_rhc_numucc_0pi_ntrk_03" ; break;
    case (kNuisEffRHCnumuCC0piNtrk04        ) : return "f_eff_rhc_numucc_0pi_ntrk_04" ; break;
    case (kNuisEffRHCnumuCC0piNtrk05        ) : return "f_eff_rhc_numucc_0pi_ntrk_05" ; break;
    case (kNuisEffRHCnumuCC0piNtrk06        ) : return "f_eff_rhc_numucc_0pi_ntrk_06" ; break;
    case (kNuisEffRHCnumuCC0piNtrk07        ) : return "f_eff_rhc_numucc_0pi_ntrk_07" ; break;
    case (kNuisEffRHCnumuCC0piNtrk08        ) : return "f_eff_rhc_numucc_0pi_ntrk_08" ; break;
    case (kNuisEffRHCnumuCC0piNtrk09        ) : return "f_eff_rhc_numucc_0pi_ntrk_09" ; break;
    case (kNuisEffRHCnumuCC0piNtrk10        ) : return "f_eff_rhc_numucc_0pi_ntrk_10" ; break;
    case (kNuisEffRHCnumuCC0piNtrk11        ) : return "f_eff_rhc_numucc_0pi_ntrk_11" ; break;
    case (kNuisEffRHCnumuCC0piNtrk12        ) : return "f_eff_rhc_numucc_0pi_ntrk_12" ; break;
    case (kNuisEffRHCnumuCC0piNtrk13        ) : return "f_eff_rhc_numucc_0pi_ntrk_13" ; break;
    case (kNuisEffRHCnumuCC0piNtrk14        ) : return "f_eff_rhc_numucc_0pi_ntrk_14" ; break;
    case (kNuisEffRHCnumuCC0piNtrk15        ) : return "f_eff_rhc_numucc_0pi_ntrk_15" ; break;
    case (kNuisEffRHCnumuCC1pi3trkDelta01   ) : return "f_eff_rhc_numucc_1pi3trk_delta_01" ; break;
    case (kNuisEffRHCnumuCC1pi3trkDelta02   ) : return "f_eff_rhc_numucc_1pi3trk_delta_02" ; break;
    case (kNuisEffRHCnumuCC1pi3trkDelta03   ) : return "f_eff_rhc_numucc_1pi3trk_delta_03" ; break;
    case (kNuisEffRHCnumuCC1pi3trkDelta04   ) : return "f_eff_rhc_numucc_1pi3trk_delta_04" ; break;
    case (kNuisEffRHCnumuCC1pi3trkDelta05   ) : return "f_eff_rhc_numucc_1pi3trk_delta_05" ; break;
    case (kNuisEffRHCnumuCC1pi3trkDelta06   ) : return "f_eff_rhc_numucc_1pi3trk_delta_06" ; break;
    case (kNuisEffRHCnumuCC1pi3trkDelta07   ) : return "f_eff_rhc_numucc_1pi3trk_delta_07" ; break;
    case (kNuisEffRHCnumuCC1pi3trkDelta08   ) : return "f_eff_rhc_numucc_1pi3trk_delta_08" ; break;
    case (kNuisEffRHCnumuCC1pi3trkDelta09   ) : return "f_eff_rhc_numucc_1pi3trk_delta_09" ; break;
    case (kNuisEffRHCnumuCC1pi3trkDelta10   ) : return "f_eff_rhc_numucc_1pi3trk_delta_10" ; break;
    case (kNuisEffRHCnumuCC1pi3trkDelta11   ) : return "f_eff_rhc_numucc_1pi3trk_delta_11" ; break;
    case (kNuisEffRHCnumuCC1pi3trkDelta12   ) : return "f_eff_rhc_numucc_1pi3trk_delta_12" ; break;
    case (kNuisEffRHCnumuCC1pi3trkDelta13   ) : return "f_eff_rhc_numucc_1pi3trk_delta_13" ; break;
    case (kNuisEffRHCnumuCC1pi3trkDelta14   ) : return "f_eff_rhc_numucc_1pi3trk_delta_14" ; break;
    case (kNuisEffRHCnumuCC1pi3trkDelta15   ) : return "f_eff_rhc_numucc_1pi3trk_delta_15" ; break;
    case (kNuisEffRHCnumuCC1pic01           ) : return "f_eff_rhc_numucc_1pic_01" ; break;
    case (kNuisEffRHCnumuCC1pic02           ) : return "f_eff_rhc_numucc_1pic_02" ; break;
    case (kNuisEffRHCnumuCC1pic03           ) : return "f_eff_rhc_numucc_1pic_03" ; break;
    case (kNuisEffRHCnumuCC1pic04           ) : return "f_eff_rhc_numucc_1pic_04" ; break;
    case (kNuisEffRHCnumuCC1pic05           ) : return "f_eff_rhc_numucc_1pic_05" ; break;
    case (kNuisEffRHCnumuCC1pic06           ) : return "f_eff_rhc_numucc_1pic_06" ; break;
    case (kNuisEffRHCnumuCC1pic07           ) : return "f_eff_rhc_numucc_1pic_07" ; break;
    case (kNuisEffRHCnumuCC1pic08           ) : return "f_eff_rhc_numucc_1pic_08" ; break;
    case (kNuisEffRHCnumuCC1pic09           ) : return "f_eff_rhc_numucc_1pic_09" ; break;
    case (kNuisEffRHCnumuCC1piz01           ) : return "f_eff_rhc_numucc_1piz_01" ; break;
    case (kNuisEffRHCnumuCC1piz02           ) : return "f_eff_rhc_numucc_1piz_02" ; break;
    case (kNuisEffRHCnumuCC1piz03           ) : return "f_eff_rhc_numucc_1piz_03" ; break;
    case (kNuisEffRHCnumuCC1piz04           ) : return "f_eff_rhc_numucc_1piz_04" ; break;
    case (kNuisEffRHCnumuCC1piz05           ) : return "f_eff_rhc_numucc_1piz_05" ; break;
    case (kNuisEffRHCnumuCC1piz06           ) : return "f_eff_rhc_numucc_1piz_06" ; break;
    case (kNuisEffRHCnumuCC1piz07           ) : return "f_eff_rhc_numucc_1piz_07" ; break;
    case (kNuisEffRHCnumuCC1piz08           ) : return "f_eff_rhc_numucc_1piz_08" ; break;
    case (kNuisEffRHCnumuCC1piz09           ) : return "f_eff_rhc_numucc_1piz_09" ; break;
    case (kNuisEffRHCnumuCC1pic1piz01       ) : return "f_eff_rhc_numucc_1pic_1piz_01" ; break;
    case (kNuisEffRHCnumuCC1pic1piz02       ) : return "f_eff_rhc_numucc_1pic_1piz_02" ; break;
    case (kNuisEffRHCnumuCC1pic1piz03       ) : return "f_eff_rhc_numucc_1pic_1piz_03" ; break;
    case (kNuisEffRHCnumuCC1pic1piz04       ) : return "f_eff_rhc_numucc_1pic_1piz_04" ; break;
    case (kNuisEffRHCnumuCC1pic1piz05       ) : return "f_eff_rhc_numucc_1pic_1piz_05" ; break;
    case (kNuisEffRHCnumuCC1pic1piz06       ) : return "f_eff_rhc_numucc_1pic_1piz_06" ; break;
    case (kNuisEffRHCnumuCC1pic1piz07       ) : return "f_eff_rhc_numucc_1pic_1piz_07" ; break;
    case (kNuisEffRHCnumuCC1pic1piz08       ) : return "f_eff_rhc_numucc_1pic_1piz_08" ; break;
    case (kNuisEffRHCnumuCC1pic1piz09       ) : return "f_eff_rhc_numucc_1pic_1piz_09" ; break;
    case (kNuisEffRHCnumuCCother01          ) : return "f_eff_rhc_numucc_other_01" ; break;
    case (kNuisEffRHCnumuCCother02          ) : return "f_eff_rhc_numucc_other_02" ; break;
    case (kNuisEffRHCnumuCCother03          ) : return "f_eff_rhc_numucc_other_03" ; break;
    case (kNuisEffRHCnumuCCother04          ) : return "f_eff_rhc_numucc_other_04" ; break;
    case (kNuisEffRHCnumuCCother05          ) : return "f_eff_rhc_numucc_other_05" ; break;
    case (kNuisEffRHCnumuCCother06          ) : return "f_eff_rhc_numucc_other_06" ; break;
    case (kNuisEffRHCnumuCCother07          ) : return "f_eff_rhc_numucc_other_07" ; break;
    case (kNuisEffRHCnumuCCother08          ) : return "f_eff_rhc_numucc_other_08" ; break;
    case (kNuisEffRHCnumuCCother09          ) : return "f_eff_rhc_numucc_other_09" ; break;
    case (kNuisEffRHCnumuCCother10          ) : return "f_eff_rhc_numucc_other_10" ; break;
    case (kNuisEffRHCnumuCCother11          ) : return "f_eff_rhc_numucc_other_11" ; break;
    case (kNuisEffRHCnumuCCWS0pi01          ) : return "f_eff_rhc_numucc_ws_0pi_01" ; break;
    case (kNuisEffRHCnumuCCWS0pi02          ) : return "f_eff_rhc_numucc_ws_0pi_02" ; break;
    case (kNuisEffRHCnumuCCWS0pi03          ) : return "f_eff_rhc_numucc_ws_0pi_03" ; break;
    case (kNuisEffRHCnumuCCWS0pi04          ) : return "f_eff_rhc_numucc_ws_0pi_04" ; break;
    case (kNuisEffRHCnumuCCWS0pi05          ) : return "f_eff_rhc_numucc_ws_0pi_05" ; break;
    case (kNuisEffRHCnumuCCWS1pic01         ) : return "f_eff_rhc_numucc_ws_1pic_01" ; break;
    case (kNuisEffRHCnumuCCWS1pic02         ) : return "f_eff_rhc_numucc_ws_1pic_02" ; break;
    case (kNuisEffRHCnumuCCWS1pic03         ) : return "f_eff_rhc_numucc_ws_1pic_03" ; break;
    case (kNuisEffRHCnumuCCWS1pic04         ) : return "f_eff_rhc_numucc_ws_1pic_04" ; break;
    case (kNuisEffRHCnumuCCWS1pic05         ) : return "f_eff_rhc_numucc_ws_1pic_05" ; break;
    case (kNuisEffRHCnumuCCWS1pic06         ) : return "f_eff_rhc_numucc_ws_1pic_06" ; break;
    case (kNuisEffRHCnumuCCWS1pic07         ) : return "f_eff_rhc_numucc_ws_1pic_07" ; break;
    case (kNuisEffRHCnumuCCWS1pic08         ) : return "f_eff_rhc_numucc_ws_1pic_08" ; break;
    case (kNuisEffRHCnumuCCWS1piz01         ) : return "f_eff_rhc_numucc_ws_1piz_01" ; break;
    case (kNuisEffRHCnumuCCWS1piz02         ) : return "f_eff_rhc_numucc_ws_1piz_02" ; break;
    case (kNuisEffRHCnumuCCWS1piz03         ) : return "f_eff_rhc_numucc_ws_1piz_03" ; break;
    case (kNuisEffRHCnumuCCWSother01        ) : return "f_eff_rhc_numucc_ws_other_01" ; break;
    case (kNuisEffRHCnueCC0pi01             ) : return "f_eff_rhc_nuecc_0pi_01" ; break;
    case (kNuisEffRHCnueCC0pi02             ) : return "f_eff_rhc_nuecc_0pi_02" ; break;
    case (kNuisEffRHCnueCC0pi03             ) : return "f_eff_rhc_nuecc_0pi_03" ; break;
    case (kNuisEffRHCnueCC0pi04             ) : return "f_eff_rhc_nuecc_0pi_04" ; break;
    case (kNuisEffRHCnueCC0pi05             ) : return "f_eff_rhc_nuecc_0pi_05" ; break;
    case (kNuisEffRHCnueCC0pi06             ) : return "f_eff_rhc_nuecc_0pi_06" ; break;
    case (kNuisEffRHCnueCC0pi07             ) : return "f_eff_rhc_nuecc_0pi_07" ; break;
    case (kNuisEffRHCnueCC0pi08             ) : return "f_eff_rhc_nuecc_0pi_08" ; break;
    case (kNuisEffRHCnueCC0pi09             ) : return "f_eff_rhc_nuecc_0pi_09" ; break;
    case (kNuisEffRHCnueCC1pic01            ) : return "f_eff_rhc_nuecc_1pic_01" ; break;
    case (kNuisEffRHCnueCC1pic02            ) : return "f_eff_rhc_nuecc_1pic_02" ; break;
    case (kNuisEffRHCnueCC1pic03            ) : return "f_eff_rhc_nuecc_1pic_03" ; break;
    case (kNuisEffRHCnueCC1pic04            ) : return "f_eff_rhc_nuecc_1pic_04" ; break;
    case (kNuisEffRHCnueCC1pic05            ) : return "f_eff_rhc_nuecc_1pic_05" ; break;
    case (kNuisEffRHCnueCC1pic06            ) : return "f_eff_rhc_nuecc_1pic_06" ; break;
    case (kNuisEffRHCnueCC1pic07            ) : return "f_eff_rhc_nuecc_1pic_07" ; break;
    case (kNuisEffRHCnueCC1pic08            ) : return "f_eff_rhc_nuecc_1pic_08" ; break;
    case (kNuisEffRHCnueCC1pic09            ) : return "f_eff_rhc_nuecc_1pic_09" ; break;
    case (kNuisEffRHCnueCC1piz01            ) : return "f_eff_rhc_nuecc_1piz_01" ; break;
    case (kNuisEffRHCnueCC1piz02            ) : return "f_eff_rhc_nuecc_1piz_02" ; break;
    case (kNuisEffRHCnueCC1piz03            ) : return "f_eff_rhc_nuecc_1piz_03" ; break;
    case (kNuisEffRHCnueCC1piz04            ) : return "f_eff_rhc_nuecc_1piz_04" ; break;
    case (kNuisEffRHCnueCC1piz05            ) : return "f_eff_rhc_nuecc_1piz_05" ; break;
    case (kNuisEffRHCnueCC1piz06            ) : return "f_eff_rhc_nuecc_1piz_06" ; break;
    case (kNuisEffRHCnueCC1piz07            ) : return "f_eff_rhc_nuecc_1piz_07" ; break;
    case (kNuisEffRHCnueCC1piz08            ) : return "f_eff_rhc_nuecc_1piz_08" ; break;
    case (kNuisEffRHCnueCC1piz09            ) : return "f_eff_rhc_nuecc_1piz_09" ; break;
    case (kNuisEffRHCnueCCother01           ) : return "f_eff_rhc_nuecc_other_01" ; break;
    case (kNuisEffRHCnueCCother02           ) : return "f_eff_rhc_nuecc_other_02" ; break;
    case (kNuisEffRHCnueCCother03           ) : return "f_eff_rhc_nuecc_other_03" ; break;
    case (kNuisEffRHCnueCCother04           ) : return "f_eff_rhc_nuecc_other_04" ; break;
    case (kNuisEffRHCnueCCother05           ) : return "f_eff_rhc_nuecc_other_05" ; break;
    case (kNuisEffRHCnueCCother06           ) : return "f_eff_rhc_nuecc_other_06" ; break;
    case (kNuisEffRHCnueCCother07           ) : return "f_eff_rhc_nuecc_other_07" ; break;
    case (kNuisEffRHCnueCCother08           ) : return "f_eff_rhc_nuecc_other_08" ; break;
    case (kNuisEffRHCnueCCother09           ) : return "f_eff_rhc_nuecc_other_09" ; break;
    case (kNuisEffRHCnueCCother10           ) : return "f_eff_rhc_nuecc_other_10" ; break;
    case (kNuisEffRHCnueCCother11           ) : return "f_eff_rhc_nuecc_other_11" ; break;
    case (kNuisEffRHCnueCCWS01              ) : return "f_eff_rhc_nuecc_ws_01" ; break;
    case (kNuisEffRHCnueCCWS02              ) : return "f_eff_rhc_nuecc_ws_02" ; break;
    case (kNuisEffRHCNC0pi01                ) : return "f_eff_rhc_nc_0pi_01" ; break;
    case (kNuisEffRHCNC0pi02                ) : return "f_eff_rhc_nc_0pi_02" ; break;
    case (kNuisEffRHCNC0pi03                ) : return "f_eff_rhc_nc_0pi_03" ; break;
    case (kNuisEffRHCNC1pic01               ) : return "f_eff_rhc_nc_1pic_01" ; break;
    case (kNuisEffRHCNC1pic02               ) : return "f_eff_rhc_nc_1pic_02" ; break;
    case (kNuisEffRHCNC1pic03               ) : return "f_eff_rhc_nc_1pic_03" ; break;
    case (kNuisEffRHCNC1piz01               ) : return "f_eff_rhc_nc_1piz_01" ; break;
    case (kNuisEffRHCNC1piz02               ) : return "f_eff_rhc_nc_1piz_02" ; break;
    case (kNuisEffRHCNC1piz03               ) : return "f_eff_rhc_nc_1piz_03" ; break;
    case (kNuisEffRHCNCother01              ) : return "f_eff_rhc_nc_other_01" ; break;
    case (kNuisEffRHCNCother02              ) : return "f_eff_rhc_nc_other_02" ; break;
    case (kNuisEffRHCNCother03              ) : return "f_eff_rhc_nc_other_03" ; break;
    case (kNuisEffRHCNeutrinoElec           ) : return "f_eff_rhc_neutrinoelec" ; break;
    case (kNuisEffRHCIMD                    ) : return "f_eff_rhc_imd" ; break;
    
    
    
    
  
    case (kNuisEffFDNuMuLikeCCHigh ) : return "f_eff_fd_numulike_cchigh";     break;  
    case (kNuisEffFDNuMuLikeCCLow  ) : return "f_eff_fd_numulike_cclow";      break;  
      //    case (kNuisEffFDNuMuBarCCHigh  ) : return "f_eff_fd_numubar_cchigh";  break;  
      //    case (kNuisEffFDNuMuBarCCLow   ) : return "f_eff_fd_numubar_cclow";   break;  
    case (kNuisEffFDNuELikeCCHigh  ) : return "f_eff_fd_nuelike_cchigh";      break;  
    case (kNuisEffFDNuELikeCCLow   ) : return "f_eff_fd_nuelike_cclow";       break;  
      //    case (kNuisEffFDNuEBarCCHigh   ) : return "f_eff_fd_nuebar_cchigh";   break;  
      //    case (kNuisEffFDNuEBarCCLow    ) : return "f_eff_fd_nuebar_cclow";    break;  
      //    case (kNuisEffFDNuTauCCHigh    ) : return "f_eff_fd_nutau_cchigh";    break;  
      //    case (kNuisEffFDNuTauCCLow     ) : return "f_eff_fd_nutau_cclow";     break;  
      //    case (kNuisEffFDNuTauBarCCHigh ) : return "f_eff_fd_nutaubar_cchigh"; break;  
      //    case (kNuisEffFDNuTauBarCCLow  ) : return "f_eff_fd_nutaubar_cclow";  break;  

    case ( kNuisIntNuCCQE1         ) : return "f_int_nu_ccqe_1"; 
    case ( kNuisIntNuCCQE2         ) : return "f_int_nu_ccqe_2"; 
    case ( kNuisIntNuCCQE3         ) : return "f_int_nu_ccqe_3"; 
    case ( kNuisIntNuBarCCQE1      ) : return "f_int_nubar_ccqe_1"; 
    case ( kNuisIntNuBarCCQE2      ) : return "f_int_nubar_ccqe_2"; 
    case ( kNuisIntNuBarCCQE3      ) : return "f_int_nubar_ccqe_3"; 
    
    case ( kNuisIntNuCCMEC         ) : return "f_int_nu_mec"; 
    case ( kNuisIntNuBarCCMEC      ) : return "f_int_nubar_mec"; 
    
    case ( kNuisIntNuCC1piz1       ) : return "f_int_nu_cc1piz_1"; 
    case ( kNuisIntNuCC1piz2       ) : return "f_int_nu_cc1piz_2"; 
    case ( kNuisIntNuCC1piz3       ) : return "f_int_nu_cc1piz_3"; 
    case ( kNuisIntNuCC1pic1       ) : return "f_int_nu_cc1pic_1"; 
    case ( kNuisIntNuCC1pic2       ) : return "f_int_nu_cc1pic_2"; 
    case ( kNuisIntNuCC1pic3       ) : return "f_int_nu_cc1pic_3"; 
    
    case ( kNuisIntNuBarCC1piz1    ) : return "f_int_nubar_1piz_1"; 
    case ( kNuisIntNuBarCC1piz2    ) : return "f_int_nubar_1piz_2"; 
    case ( kNuisIntNuBarCC1piz3    ) : return "f_int_nubar_1piz_3"; 
    case ( kNuisIntNuBarCC1pic1    ) : return "f_int_nubar_1pic_1"; 
    case ( kNuisIntNuBarCC1pic2    ) : return "f_int_nubar_1pic_2"; 
    case ( kNuisIntNuBarCC1pic3    ) : return "f_int_nubar_1pic_3"; 
    
    case ( kNuisIntNuCC2Pi         ) : return "f_int_nu_2pi"; 
    case ( kNuisIntNuBarCC2Pi      ) : return "f_int_nubar_2pi"; 
    
    case ( kNuisIntNuDIS1          ) : return "f_int_nu_dis_1"; 
    case ( kNuisIntNuDIS2          ) : return "f_int_nu_dis_2"; 
    case ( kNuisIntNuDIS3          ) : return "f_int_nu_dis_3"; 
    case ( kNuisIntNuBarDIS1       ) : return "f_int_nubar_dis_1"; 
    case ( kNuisIntNuBarDIS2       ) : return "f_int_nubar_dis_2"; 
    case ( kNuisIntNuBarDIS3       ) : return "f_int_nubar_dis_3"; 
    
    case (kNuisIntNormNuCoherent        ) : return "f_int_nu_coh";
    case (kNuisIntNormNuBarCoherent     ) : return "f_int_nubar_coh";
    case (kNuisIntNuNormNC              ) : return "f_int_nu_nc";
    case (kNuisIntNuBarNormNC           ) : return "f_int_nubar_nc";
    case (kNuisIntNormNuMuToNuE         ) : return "f_int_nuenumu";
    case (kNuisIntNormNuMuBarToNuEBar   ) : return "f_int_nuebarnumubar";
    case (kNuisIntPiMeanFreePath        ) : return "f_int_pi_mfp";
    case (kNuisIntNucMeanFreePath       ) : return "f_int_n_mfp";
    case (kNuisIntFracPiChargeExchange  ) : return "f_int_pi_cex";
    case (kNuisIntFracPiInelastic       ) : return "f_int_pi_inel";
    case (kNuisIntFracPiAbsorb          ) : return "f_int_pi_abs";
    case (kNuisIntFracPiProduction      ) : return "f_int_pi_prod";
    case (kNuisIntFracNucChargeExchange ) : return "f_int_n_cex";
    case (kNuisIntFracNucInelastic      ) : return "f_int_n_inel";
    case (kNuisIntFracNucAbsorb         ) : return "f_int_n_abs";
    case (kNuisIntFracNucProduction     ) : return "f_int_n_prod";
    case (kNuisIntTarget                ) : return "f_int_target";

    case (kPhypMixing12                 ) : return "f_osc_mixing12";
    case (kPhypMixing23                 ) : return "f_osc_mixing23";
    case (kPhypMixing13                 ) : return "f_osc_mixing13";
    case (kPhypDm23sq                   ) : return "f_osc_dm23sq";  
    case (kPhypDm12sq                   ) : return "f_osc_dm12sq"; 
    case (kPhypCPV                      ) : return "f_osc_cpv";  
    
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
string util::ParamAsString      (conv::PhysParamId_t p)            {return util::AsString      (p)  ;};
string util::ParamAsStringSimple(conv::PhysParamId_t p)            {return util::AsStringSimple(p)  ;};
string util::ParamAsStringTeX   (conv::PhysParamId_t p, bool root) {return util::AsStringTeX(p,root);};
//________________________________________________________________________________________
PhysParamId_t util::PhysParamFromString(string inp_name)
{
  for(int ip = 0; ip < knppmax; ip++) {
     PhysParamId_t p = (PhysParamId_t)ip;
     string name = util::AsString(p);
     if(IsOscParam(p)){  
       string name_simple = util::AsStringSimple(p);
       if((name == inp_name) || (name_simple == inp_name))
         return p;
       }
     else{
       if(name == inp_name) 
         return p;
     }
  }
  return kPhypUndefined;
}
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
    fparm = FitParamList::NamedParameterList(param_list_opt);
    //LOG("FitParams",pERROR)<<"Unrecognised fit parameter list name: "<<param_list_opt;
    //util::Die(-1); return fparm;
  }

  if(!fparm->IsComplete()) {
    LOG("FitParams",pERROR)<<"Fit parameter list is not complete";
    fparm->Print();
    util::Die(-1); return fparm;
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
//____________________________________________________________________________
conv::PhysParamId_t util::GetFitParam(int index)
{
  if(index < 0 || index >= conv::kNFitParams) {
    return conv::kPhypUndefined;
  }
  return conv::kFitParam[index];
}
//____________________________________________________________________________
bool util::ParamHasRecoDependence(int index)
{
  if(index < 0 || index >= conv::kNFitParams) {
    LOG("FitParams",pERROR)<<"Index out of bounds: "<< index;
    util::Die(-1);
  }
  return conv::kFitParamRecoKinematicDependence[index];
}
//____________________________________________________________________________
bool util::ParamHasTrueDependence(int index)
{
  if(index < 0 || index >= conv::kNFitParams) {
    LOG("FitParams",pERROR)<<"Index out of bounds: "<< index;
    util::Die(-1);
  }
  return conv::kFitParamTrueKinematicDependence[index];
}
//____________________________________________________________________________
const double * util::ParamErecoRange(int index)
{
  if(index < 0 || index >= conv::kNFitParams) {
    LOG("FitParams",pERROR)<<"Index out of bounds: "<< index;
    util::Die(-1);
  }
  return conv::kFitParamErecoRange[index];
}
//___________________________________________________________________________
const double* util::ParamYrecoRange(int index)
{
  if(index < 0 || index >= conv::kNFitParams) {
    LOG("FitParams",pERROR)<<"Index out of bounds: "<< index;
    util::Die(-1);
  }
  return conv::kFitParamYrecoRange[index];
}
//___________________________________________________________________________
const double* util::ParamEtrueRange(int index)
{
  if(index < 0 || index >= conv::kNFitParams) {
    LOG("FitParams",pERROR)<<"Index out of bounds: "<< index;
    util::Die(-1);
  }
  return conv::kFitParamEtrueRange[index];
}

//___________________________________________________________________________
const double* util::ParamQ2trueRange(int index)
{
  if(index < 0 || index >= conv::kNFitParams) {
    LOG("FitParams",pERROR)<<"Index out of bounds: "<< index;
    util::Die(-1);
  }
  return conv::kFitParamQ2trueRange[index];
}
//___________________________________________________________________________
