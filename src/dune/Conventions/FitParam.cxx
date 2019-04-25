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
