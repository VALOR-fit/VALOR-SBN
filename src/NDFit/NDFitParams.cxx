//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include "NDFit/NDFitParams.h"

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
    case (kNuisFHCNuMuBarFlux00) : return "f_fhc_flux_numubar00"; break;
    case (kNuisFHCNuMuBarFlux01) : return "f_fhc_flux_numubar01"; break;
    case (kNuisFHCNuMuBarFlux02) : return "f_fhc_flux_numubar02"; break;
    case (kNuisFHCNuMuBarFlux03) : return "f_fhc_flux_numubar03"; break;
    case (kNuisFHCNuMuBarFlux04) : return "f_fhc_flux_numubar04"; break;
    case (kNuisFHCNuEFlux00    ) : return "f_fhc_flux_nue00";     break;
    case (kNuisFHCNuEFlux01    ) : return "f_fhc_flux_nue01";     break;
    case (kNuisFHCNuEFlux02    ) : return "f_fhc_flux_nue02";     break;
    case (kNuisNormCCQE        ) : return "f_ccqe";               break;
    case (kNuisNormCC1piC      ) : return "f_cc1pic";             break;
    case (kNuisNormCC1pi0      ) : return "f_cc1pi0";             break;
    case (kNuisNormCCoth       ) : return "f_ccoth";              break;
    case (kNuisNormNC          ) : return "f_nc";                 break;
    default                      : return "--";    
  }
  return "";
}
//________________________________________________________________________________________
string util::AsStringTeX(conv::PhysParamId_t p, bool /*root*/)
{
 // for now
 return AsString(p);
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
PhysHypothesis util::GetPhysHypothesis (Option_t * /*opt*/)
{
// Create a PhysHypothesis object
// Add all physics + nuisance params (depending on input option) with nominal values
//
  PhysHypothesis ph(kHypVoid); 

  ph.SetCurrValue(kNuisFHCNuMuFlux00,    1.); 
  ph.SetCurrValue(kNuisFHCNuMuFlux01,    1.);
  ph.SetCurrValue(kNuisFHCNuMuFlux02,    1.);
  ph.SetCurrValue(kNuisFHCNuMuFlux03,    1.);
  ph.SetCurrValue(kNuisFHCNuMuFlux04,    1.);
  ph.SetCurrValue(kNuisFHCNuMuFlux05,    1.);
  ph.SetCurrValue(kNuisFHCNuMuFlux06,    1.);
  ph.SetCurrValue(kNuisFHCNuMuFlux07,    1.);
  ph.SetCurrValue(kNuisFHCNuMuFlux08,    1.);
  ph.SetCurrValue(kNuisFHCNuMuFlux09,    1.);
  ph.SetCurrValue(kNuisFHCNuMuBarFlux00, 1.);
  ph.SetCurrValue(kNuisFHCNuMuBarFlux01, 1.);
  ph.SetCurrValue(kNuisFHCNuMuBarFlux02, 1.);
  ph.SetCurrValue(kNuisFHCNuMuBarFlux03, 1.);
  ph.SetCurrValue(kNuisFHCNuMuBarFlux04, 1.);
  ph.SetCurrValue(kNuisFHCNuEFlux00,     1.);
  ph.SetCurrValue(kNuisFHCNuEFlux01,     1.);
  ph.SetCurrValue(kNuisFHCNuEFlux02,     1.);
  ph.SetCurrValue(kNuisNormCCQE,         1.);
  ph.SetCurrValue(kNuisNormCC1piC,       1.);
  ph.SetCurrValue(kNuisNormCC1pi0,       1.);
  ph.SetCurrValue(kNuisNormCCoth,        1.);
  ph.SetCurrValue(kNuisNormNC,           1.);

  return ph;
}
//________________________________________________________________________________________
