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
#include "valor/Conventions/ParameterPool.h"
#include "valor/Conventions/FitParamApply.h"
#include "valor/Utilities/UtlSystem.h"
// dune
#include "dune/Conventions/OscParams.h"
#include "dune/Conventions/FitParam.h"
#include "dune/Conventions/PhysicalParameterLimits.h"

using namespace valor;
using namespace valor::conv;
//________________________________________________________________________________________
FitParamList * util::GetFitParameterList(Option_t * param_list, /*const PhysHypothesis & ph,*/ const CorrelatedSystematics * syst)
{
// Create a FitParamList object, adding all physics (from the PhysHypothesis) + nuisance (from the ParameterPool) params.
// The input option specifies both the set of parameters (eg "standard")

  PhysHypothesis ph = PhysHypothesis("3f_osc");   // TODO: this line is temporary, instead the osc params should be taken from a config file (or less desirable: take the PhysHypothesis as an input and hard-code all the osc param init values priors etc. for every hypothesis)

  string param_list_opt   = ((param_list)   ? param_list   : "standard");

  LOG("FitParams", pNOTICE)
    << "Instantiating a fit parameter list object with option: " << param_list_opt;

  const std::vector<conv::PhysParamId_t> osc_params = ph.GetParams();
  const std::vector<Parameter> & pool_params = ParameterPool::Instance()->GetParams();
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

    // Set the number of osc + syst parameters
    int nparams = 0;
    if (syst) {
      nparams = syst->Size();
    }
    else{
      nparams = pool_params.size();
    }
    if (!no_osc) {
      nparams += osc_params.size();
    }

    fparm = new FitParamList(nparams);
    int ipc = 0; //counter with no gaps, in case of `kPhypUndefined' params

    //if osc params constrained, set priors
    if(cons_osc_params) {
      util::InitializeOAPriors();   // TODO: This is DUNE specific and needs moving to a config file, but can be left in for now
    }

    //now separately loop over the parameters from the ParameterPool, CorrelatedSystematics and PhysHypothesis to add them to the list

    // Add osc params from the PhysHypothesis:
    for (conv::PhysParamId_t p : osc_params) {
      if(p == kPhypUndefined) {
        LOG("FitParams", pFATAL) << "Found an undefined parameter in the PhysParamList";
        util::Die(-1);
      }

      // set parameter range, current and init value, etc
      double init = 1.0;
      double curr = 1.0;
      double min  = 0.0;
      double max  = 2.0;
      double step = 1E-4;
      bool   fix  = false;
      bool   nuis = true;

      if (no_osc) {continue;}
      init = util::OscParamInitValue(p);  // TODO: This is DUNE specific and needs moving to a config file
      curr = util::OscParamInitValue(p);  // TODO: This is DUNE specific and needs moving to a config file
      min  = util::OscParamMinValue(p);   // TODO: This is DUNE specific and needs moving to a config file
      max  = util::OscParamMaxValue(p);   // TODO: This is DUNE specific and needs moving to a config file
      step = util::OscParamStepSize(p);   // TODO: This is DUNE specific and needs moving to a config file
      nuis = false;

      // Check we're not going behind physical region
      min = PhysicalParameterLimits::Instance()->GetNearestPhysicalValue(p,min);
      max = PhysicalParameterLimits::Instance()->GetNearestPhysicalValue(p,max);

      fparm->AddParam(ipc, p, init, min, max, step, fix, nuis);
      ipc++;
      fparm->Update(p, curr);

      // toggle oscillation params on/off
      if(fix_osc_params && util::IsOscParam(p)){
        double init_value = util::OscParamInitValue(p);   // TODO: This is DUNE specific and needs moving to a config file
        fparm->Update(p, init_value);
        fparm->SetInitValue(p, init_value);
        fparm->FixParameter(p);
      }

      //constrain osc params
      if(cons_osc_params && util::IsOscParam(p)){
        fparm->SetNuisance(p,true);
      }
    } // osc pars in PhysHyPothesis

    // If necessary, add the systematics from the model
    if (syst) {
      syst->AppendParamsTo(*fparm);
      // And update their limits`
      for (unsigned int ip = 0 ; ip < syst->Size(); ip++) {
        conv::PhysParamId_t p = syst->WhichParam(ip);
        fparm->SetMinValue(p, PhysicalParameterLimits::Instance()->GetNearestPhysicalValue(p,0.));  // TODO: Do we want these hard-coded values in a config file?
        fparm->SetMaxValue(p, PhysicalParameterLimits::Instance()->GetNearestPhysicalValue(p,2.));
      }
    }
    // Or add parameters from the ParameterPool
    else {
      for (const Parameter & param : pool_params) {
        PhysParamId_t p = param.GetID();
        if(p == kPhypUndefined) {
          LOG("FitParams", pFATAL) << "Found an undefined parameter in the ParameterPool";
          util::Die(-1);
        }

        // set parameter range, current and init value, etc
        // TODO: It would be better to have the option of getting non-default values of the following params from a config file, but this is fine for now
        double init = 1.0;
        double curr = 1.0;
        double min  = 0.0;
        double max  = 2.0;
        double step = 1E-4;
        bool   fix  = false;
        bool   nuis = true;

        // Check we're not going behind physical region
        min = param.GetNearestPhysicalValue(min);
        max = param.GetNearestPhysicalValue(min);

        fparm->AddParam(ipc, p, init, min, max, step, fix, nuis);
        ipc++;
        fparm->Update(p, curr);
      } // Params in ParameterPool
    }

    // Now that we have all the params we want in the FitParamList, fix/set parameters as necessary
    for(int ip = 0; ip < nparams; ip++) {
      conv::PhysParamId_t p = fparm->WhichParam(ip);
      if(util::IsOscParam(p)) { continue; }
      if(!ParameterPool::Instance()->IsParamInPool(p)) {
        LOG("FitParams",pERROR)<<"When attempting to fix/set systematic parameters, parameter \'"
                               << NameRegistry::Instance()->AsString(p)
                               << "\' was not found in the ParameterPool so could not be categorised.";
        util::Die(-1); return fparm;
      }
      Parameter param = ParameterPool::Instance()->GetParam(p);

      // toggle detector related params on/off
      if(fix_detector_params && param.SearchCategories("det")) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      if(fix_nd_detector_params && param.SearchCategories("det") && param.SearchCategories("ND")) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      if(fix_fd_detector_params && param.SearchCategories("det") && param.SearchCategories("FD")) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      // toggle flux related params on/off
      if(fix_flux_params && param.SearchCategories("flux")) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      // toggle nd flux related params on/off
      if(fix_nd_flux_params && param.SearchCategories("ND") && param.SearchCategories("flux")){
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      // toggle fd flux related params on/off
      if(fix_fd_flux_params && param.SearchCategories("FD") && param.SearchCategories("flux")){
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      // toggle int related params on/off
      if(fix_int_params && param.SearchCategories("int")) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      // toggle mec related params on/off
      if(fix_mec_params && (util::ToLowerCase(param.GetName()).find("mec")  != std::string::npos ||
                            util::ToLowerCase(param.GetName()).find("2p2h") != std::string::npos)) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }

      // toggle FSI related params on/off
      if(fix_fsi_params && param.SearchCategories("FSI")) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
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

  }
    //now we also defined a ND only fit params list
  else  if(param_list_opt.find("only-nd") != string::npos) {

    int n_nd_params = 0;
    // Count the number of params we need:
    for (const Parameter & param : pool_params) {
      PhysParamId_t p = param.GetID();
      if(p == kPhypUndefined) continue;
      if(!param.SearchCategories("ND")) {
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
    for (const Parameter & param : pool_params) {
      PhysParamId_t p = param.GetID();
      if(p == kPhypUndefined) continue;

      // If not ND, move on
      if(!param.SearchCategories("ND")) {
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

      // Check we're not going behind physical region
      min = param.GetNearestPhysicalValue(min);
      max = param.GetNearestPhysicalValue(min);

      fparm->AddParam(ipc, p, init, min, max, step, fix, nuis);
      ipc++;
      fparm->Update(p, curr);

      // toggle detector params on/off

      if(fix_detector_params && param.SearchCategories("det")) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      // toggle flux related params on/off
      if(fix_flux_params && param.SearchCategories("flux")) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      // toggle int related params on/off
      if(fix_int_params && param.SearchCategories("int")) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      // toggle mec related params on/off
      if(fix_mec_params && (util::ToLowerCase(param.GetName()).find("mec") != std::string::npos ||
                            util::ToLowerCase(param.GetName()).find("2p2h") != std::string::npos)) {
        fparm->Update(p, 1.);
        fparm->SetInitValue(p, 1.);
        fparm->FixParameter(p);
      }
      // toggle FSI related params on/off
      if(fix_fsi_params && param.SearchCategories("FSI")) {
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
conv::FitParamGroup_t util::GetParameterGroup(conv::PhysParamId_t p)
{
  const ParameterPool * pool = ParameterPool::Instance();
  if (p==conv::kPhypUndefined) {return conv::kpgUndefined;}
  else if(util::IsOscParam(p)) {return conv::kpgOscillations;}
  else if(pool->IsParamInPool(p)) {

    const Parameter & param = pool->GetParam(p);
    conv::ApplyMask_t mask = param.GetApplyMask();

    bool apply_numu_only =     (conv::kfApplyToNuMu      & mask.flav).any() &&
                              !(conv::kfApplyToNuMuBar  & mask.flav).any() &&
                              !(conv::kfApplyToNuE      & mask.flav).any() &&
                              !(conv::kfApplyToNuEBar   & mask.flav).any();

    bool apply_numubar_only = !(conv::kfApplyToNuMu    & mask.flav).any() &&
                               (conv::kfApplyToNuMuBar & mask.flav).any() &&
                              !(conv::kfApplyToNuE     & mask.flav).any() &&
                              !(conv::kfApplyToNuEBar  & mask.flav).any();

    bool apply_nue_only =     !(conv::kfApplyToNuMu    & mask.flav).any() &&
                              !(conv::kfApplyToNuMuBar & mask.flav).any() &&
                               (conv::kfApplyToNuE     & mask.flav).any() &&
                              !(conv::kfApplyToNuEBar  & mask.flav).any();

    bool apply_nuebar_only =  !(conv::kfApplyToNuMu    & mask.flav).any() &&
                              !(conv::kfApplyToNuMuBar & mask.flav).any() &&
                              !(conv::kfApplyToNuE     & mask.flav).any() &&
                               (conv::kfApplyToNuEBar  & mask.flav).any();

    bool apply_fhc_only = (conv::kbApplyToFHC & mask.beam).any() &&
                         !(conv::kbApplyToRHC & mask.beam).any();

    bool apply_rhc_only = !(conv::kbApplyToFHC & mask.beam).any() &&
                           (conv::kbApplyToRHC & mask.beam).any();

    if(param.SearchCategories("flux") && apply_fhc_only && apply_numu_only)    {return conv::kpgFHCNuMuFlux;}
    if(param.SearchCategories("flux") && apply_fhc_only && apply_numubar_only) {return conv::kpgFHCNuMuBarFlux;}
    if(param.SearchCategories("flux") && apply_fhc_only && apply_nue_only)     {return conv::kpgFHCNuEFlux;}
    if(param.SearchCategories("flux") && apply_fhc_only && apply_nuebar_only)  {return conv::kpgFHCNuEBarFlux;}
    if(param.SearchCategories("flux") && apply_rhc_only && apply_numu_only)    {return conv::kpgRHCNuMuFlux;}
    if(param.SearchCategories("flux") && apply_rhc_only && apply_numubar_only) {return conv::kpgRHCNuMuBarFlux;}
    if(param.SearchCategories("flux") && apply_rhc_only && apply_nue_only)     {return conv::kpgRHCNuEFlux;}
    if(param.SearchCategories("flux") && apply_rhc_only && apply_nuebar_only)  {return conv::kpgRHCNuEBarFlux;}
    if(param.SearchCategories("xsec"))                                         {return conv::kpgXSec;}
    if(param.SearchCategories("had"))                                          {return conv::kpgHadronization;}
    if(param.SearchCategories("fsi"))                                          {return conv::kpgFSI;}
    if(param.SearchCategories("det"))                                          {return conv::kpgDetector;}
  }
  return conv::kpgUndefined;
}
//____________________________________________________________________________
std::pair<double,double> util::GetKineRange(conv::PhysParamId_t p, conv::KineVar_t k)
{
  // Init with the ranges used for osc params
  std::pair<double,double> range = util::PhysicalLimits(k);
  // If it's not an osc param, get the kine range from the parameter pool
  if(!util::IsOscParam(p)) {
    Parameter param = ParameterPool::Instance()->GetParam(p);
    if(!param.HasKinematicRange()) {
      LOG("FitParams",pERROR)<<"Parameter " << param.GetName() << " has no kinematic range";
      util::Die(-1);
    }
    range = param.GetKineRange(k);
  }
  return range;
}
//____________________________________________________________________________
bool util::HasKinematicDependence(conv::PhysParamId_t p)
{
  if(util::IsOscParam(p)) { return true; }
  else {
    Parameter param = ParameterPool::Instance()->GetParam(p);
    if(!param.HasKinematicRange()) { return false; }
    return true;
  }
}
//____________________________________________________________________________
std::vector<PhysParamId_t> util::GetParameterSet(std::string set_name)
{
  vector<PhysParamId_t> vec;
  set_name = util::ToLowerCase(set_name);

  if(set_name == "all" || set_name != "3fosc") {
    const std::vector<Parameter> & params = ParameterPool::Instance()->GetParams();
    for (const Parameter & param : params) {
      // Search both the param name and categories
      if(param.GetName().find(set_name) != string::npos ||                                           // Search param name
         param.SearchCategories(set_name) ||                                                         // Search param category for a direct match
         // Special cases:
         set_name == "ndflux"  && param.SearchCategories("nd") && param.SearchCategories("flux") ||  // ND flux
         set_name == "fdflux"  && param.SearchCategories("fd") && param.SearchCategories("flux") ||  // FD flux
         set_name == "nddet"   && param.SearchCategories("nd") && param.SearchCategories("det")  ||  // ND Detector
         set_name == "fddet"   && param.SearchCategories("fd") && param.SearchCategories("det")  ||  // FD Detector
         set_name == "allsyst"                                                                       // All systematic params
        ) {
        vec.push_back(param.GetID());
      }
    }
  }

  // OA parameters
  if (set_name == "all" || set_name == "3fosc") {
    vec.push_back(kPhypMixing23);
    vec.push_back(kPhypMixing13);
    vec.push_back(kPhypMixing12);
    vec.push_back(kPhypCPV     );
    vec.push_back(kPhypDm23sq  );
    vec.push_back(kPhypDm12sq  );
  }
  
  if (vec.size()==0) {
    LOG("FitParams",pWARN)<<"No parameters added to set: "<<set_name;
  }
  return vec;
}
//____________________________________________________________________________
std::vector<conv::PhysParamId_t> util::GetActiveParameters(const PhysHypothesis & ph)
{
  // Get the osc params
  std::vector<conv::PhysParamId_t> vec = ph.GetParams();
  if(vec.size() == 0) {
    LOG("FitParams",pWARN) << "No parameters in the PhysHypothesis";
  }
  // Get the syst params
  const std::vector<Parameter> & syst_params = ParameterPool::Instance()->GetParams();
  if(syst_params.size() == 0) {
    LOG("FitParams",pWARN)
      << "No parameters in the ParameterPool. If this is unintended then read in a config file to populate it";
  }
  for (const Parameter & param : syst_params) {
    if(param.GetID() != conv::kPhypUndefined) { vec.push_back(param.GetID()); }
  }
  return vec;
}
//____________________________________________________________________________
