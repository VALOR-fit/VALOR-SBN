//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include "Utilities/Rnd.h"
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

    case (kNuisRHCNuMuFlux00   ) : return "f_rhc_flux_numu00";    break;
    case (kNuisRHCNuMuFlux01   ) : return "f_rhc_flux_numu01";    break;
    case (kNuisRHCNuMuFlux02   ) : return "f_rhc_flux_numu02";    break;
    case (kNuisRHCNuMuFlux03   ) : return "f_rhc_flux_numu03";    break;
    case (kNuisRHCNuMuFlux04   ) : return "f_rhc_flux_numu04";    break;
    case (kNuisRHCNuMuFlux05   ) : return "f_rhc_flux_numu05";    break;
    case (kNuisRHCNuMuFlux06   ) : return "f_rhc_flux_numu06";    break;
    case (kNuisRHCNuMuBarFlux00) : return "f_rhc_flux_numubar00"; break;
    case (kNuisRHCNuMuBarFlux01) : return "f_rhc_flux_numubar01"; break;
    case (kNuisRHCNuMuBarFlux02) : return "f_rhc_flux_numubar02"; break;
    case (kNuisRHCNuMuBarFlux03) : return "f_rhc_flux_numubar03"; break;
    case (kNuisRHCNuMuBarFlux04) : return "f_rhc_flux_numubar04"; break;
    case (kNuisRHCNuMuBarFlux05) : return "f_rhc_flux_numubar05"; break;
    case (kNuisRHCNuMuBarFlux06) : return "f_rhc_flux_numubar06"; break;
    case (kNuisRHCNuMuBarFlux07) : return "f_rhc_flux_numubar07"; break;
    case (kNuisRHCNuEFlux00    ) : return "f_rhc_flux_nue00";     break;
    case (kNuisRHCNuEFlux01    ) : return "f_rhc_flux_nue01";     break;
    case (kNuisRHCNuEFlux02    ) : return "f_rhc_flux_nue02";     break;

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
    case (kNuisFHCNuMuBarFlux00) : name = "f_{FHC;#bar{#nu_{#mu}};00}"; break;
    case (kNuisFHCNuMuBarFlux01) : name = "f_{FHC;#bar{#nu_{#mu}};01}"; break;
    case (kNuisFHCNuMuBarFlux02) : name = "f_{FHC;#bar{#nu_{#mu}};02}"; break;
    case (kNuisFHCNuMuBarFlux03) : name = "f_{FHC;#bar{#nu_{#mu}};03}"; break;
    case (kNuisFHCNuMuBarFlux04) : name = "f_{FHC;#bar{#nu_{#mu}};04}"; break;
    case (kNuisFHCNuEFlux00    ) : name = "f_{FHC;#nu_{e};00}";         break;
    case (kNuisFHCNuEFlux01    ) : name = "f_{FHC;#nu_{e};01}";         break;
    case (kNuisFHCNuEFlux02    ) : name = "f_{FHC;#nu_{e};02}";         break;

    case (kNuisRHCNuMuFlux00   ) : name = "f_{RHC;#nu_{#mu};00}";       break;
    case (kNuisRHCNuMuFlux01   ) : name = "f_{RHC;#nu_{#mu};01}";       break;
    case (kNuisRHCNuMuFlux02   ) : name = "f_{RHC;#nu_{#mu};02}";       break;
    case (kNuisRHCNuMuFlux03   ) : name = "f_{RHC;#nu_{#mu};03}";       break;
    case (kNuisRHCNuMuFlux04   ) : name = "f_{RHC;#nu_{#mu};04}";       break;
    case (kNuisRHCNuMuFlux05   ) : name = "f_{RHC;#nu_{#mu};05}";       break;
    case (kNuisRHCNuMuFlux06   ) : name = "f_{RHC;#nu_{#mu};06}";       break;
    case (kNuisRHCNuMuBarFlux00) : name = "f_{RHC;#bar{#nu_{#mu}};00}"; break;
    case (kNuisRHCNuMuBarFlux01) : name = "f_{RHC;#bar{#nu_{#mu}};01}"; break;
    case (kNuisRHCNuMuBarFlux02) : name = "f_{RHC;#bar{#nu_{#mu}};02}"; break;
    case (kNuisRHCNuMuBarFlux03) : name = "f_{RHC;#bar{#nu_{#mu}};03}"; break;
    case (kNuisRHCNuMuBarFlux04) : name = "f_{RHC;#bar{#nu_{#mu}};04}"; break;
    case (kNuisRHCNuMuBarFlux05) : name = "f_{RHC;#bar{#nu_{#mu}};05}"; break;
    case (kNuisRHCNuMuBarFlux06) : name = "f_{RHC;#bar{#nu_{#mu}};06}"; break;
    case (kNuisRHCNuMuBarFlux07) : name = "f_{RHC;#bar{#nu_{#mu}};07}"; break;
    case (kNuisRHCNuEFlux00    ) : name = "f_{RHC;#nu_{e};00}";         break;
    case (kNuisRHCNuEFlux01    ) : name = "f_{RHC;#nu_{e};01}";         break;
    case (kNuisRHCNuEFlux02    ) : name = "f_{RHC;#nu_{e};02}";         break;

    case (kNuisNormCCQE        ) : name = "f_{CCQE}";                   break;
    case (kNuisNormCC1piC      ) : name = "f_{CC1#pi^{#pm}}";           break;
    case (kNuisNormCC1pi0      ) : name = "f_{CC1#pi^{0}}";             break;
    case (kNuisNormCCoth       ) : name = "f_{CCother}";                break;
    case (kNuisNormNC          ) : name = "f_{NC}";                     break;
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
PhysHypothesis util::GetPhysHypothesis (Option_t * opt)
{
// Create a PhysHypothesis object
// Add all physics + nuisance params (depending on input option) with nominal values
//
  PhysHypothesis ph(kHypVoid); 

  string option = ((opt) ? opt : "default");

  if(option.find("default") != string::npos) {
    for(int ip = 0; ip < kNNDFitParams; ip++) {
      PhysParamId_t p = kNDFitParam[ip];
      if(p == kPhypUndefined) continue;
      ph.SetCurrValue(p,1.); 
    }//ip
  }
  else
  if(option.find("randomize") != string::npos) {
    Rnd * r = Rnd::Instance();
    for(int ip = 0; ip < kNNDFitParams; ip++) {
      PhysParamId_t p = kNDFitParam[ip];
      if(p == kPhypUndefined) continue;
      double sig = kNDFitParamAPrioriFracError[ip];
      double val = r->RndToyMCsyst().Gaus(1,sig);
      ph.SetCurrValue(p,val); 
    }//ip
  }

  return ph;
}
//________________________________________________________________________________________
FitParamList * util::GetFitParameterList (Option_t * opt)
{
  string option = ((opt) ? opt : "default");

  if(option.find("default") != string::npos) {
     FitParamList * fparm = new FitParamList(kNNDFitParams);
     for(int ip = 0; ip < kNNDFitParams; ip++) {
        PhysParamId_t p = kNDFitParam[ip];
        if(p == kPhypUndefined) continue; // note that if in fact there were gaps in the list the logic would be screwed - fix later
        double init = 1.0;
        double min  = 0.0;
        double max  = 2.0;
        double step = 1E-4;
        bool   fix  = false;
        bool   nuis = false;
        fparm->AddParam(ip, p, init, min, max, step, fix, nuis);
     }//ip
     return fparm;
  }

  return 0;
}
//________________________________________________________________________________________

