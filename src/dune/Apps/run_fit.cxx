//____________________________________________________________________________
/*!

\app       valor_dune-run_nd_fit

\brief     Generate and fit ensembles of toy-MC experiments.

\options     --tag                 : Tag for output file [def: "toymc"]
             --run                 : Run # [def: 0]
             --ntoymc              : Number of toy-MC experiments [def: 1]
             --fit-param-list      : Fit parameter list (see FitParam.cxx) 
                                     [def: "standard"]
             --param-values-option : Decide how to set the values of physics 
                                     params used for toy-MC generation 
                                    [def:"randomize-all;prefit-errors"]
             --fit-opt             : Fitter option [def: "minuit"]
             --config              : Analysis configuration file [required]
             --mesg-thresholds     : Message thresholds [def: "verbosity.xml"]
            [--with-stat-fluct |   : Include statistical fluctuation in toy 
                                     MC generation? [def: yes]
             --without-stat-fluct] 
            [--store-spectra   |   : Store toy-MC/best-fit spectra? [def: no]
             --discard-spectra   ] 

	     --input-mixing12,etc  : Option to give input values to osc params (in .arg)
	     --fix-mixing12,etc    : Option to fix osc params (in .arg)
	     --fix-at-mixing12,etc : Option to fix osc params to a different value than true/central for the fit

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\created   March 27, 2014

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

// root
#include "TFile.h"
#include "TSystem.h"
#include "TObjArray.h"
#include "TString.h"
#include "TVirtualFitter.h"
// fmwk
#include "valor/Conventions/Opt.h"
#include "valor/CmdLine/CmdLnArgList.h"
#include "valor/FitCore/PhysParamList.h"
#include "valor/FitCore/FitParamList.h"
#include "valor/FitCore/FitModelABC.h"
#include "valor/FitCore/FitDataABC.h"
#include "valor/FitCore/FitInputs.h"
#include "valor/FitCore/FitterABC.h"
#include "valor/FitCore/UtlFit.h"
#include "valor/Utilities/UtlStyle.h"
#include "valor/Utilities/UtlStr.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Utilities/Rnd.h"
#include "valor/Utilities/Env.h"
#include "valor/Messenger/Messenger.h"
#include "valor/Ntuple/StdFitNtp.h"
// dune
#include "dune/Conventions/FitParam.h"
#include "dune/Conventions/OscParams.h"
#include "dune/Conventions/PhysicalParameterLimits.h"
#include "dune/Elements/CompoundFitElements.h"

using namespace std;
using namespace valor;
using namespace valor::conv;

int main(int argc, char ** argv)
{  
  Env::Instance()->AutoSet("dune");
  valor::util::PrintBanner(Env::Instance()->Banner(),500);
 
  CmdLnArgList arg;
  arg.Read(argc,argv,"$VALOR_DUNE/config/apps/run_fit.arg:$VALOR_DUNE/config/apps/seeds.arg");
  LOG("valor_dune", pNOTICE) << arg;

  TString param_values_ts(arg.GetString("param-values-option"));
  TString fit_options_ts (arg.GetString("fitter"));
  
  bool with_stat_fluct    = arg.GetBool("with-stat-fluct");
  bool start_at_true      = arg.GetBool("start-at-true");
  bool rethrow_unphysical = arg.GetBool("rethrow-unphysical");
  int  ntoymc             = arg.GetInt("ntoymc");
  string fplname          = arg.GetString("fit-param-list");
  string fittername       = arg.GetString("fitter");
  string true_values_file = arg.GetString("true-from-filename");
  string true_values_obj  = arg.GetString("true-from-objname"); // a physparamlist
  
  // If pot_override is set to a positive number, every sample will be initialised with the same POT - this number
  double pot_override     = arg.GetDouble("pot-override");
  if (pot_override > 0 ) {
    Opt::Instance()->MutableGlobalRegistry().Set("pot_override",pot_override);
  }
  
  std::string mesg_thresholds = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  Messenger::Instance()->Configure(mesg_thresholds);
  
  // Set DUNE param names inside framework
  util::PopulateNameRegistry();
  
  // Set the random seeds
  Rnd::Instance()->SetSeeds(arg);
  
  LOG("valor_dune", pNOTICE) << *Rnd::Instance();
  
  // Check if we have a PParm to read from file containing true values
  PhysParamList * true_values_from_file = 0;
  if (true_values_file.size() && util::ToLowerCase(true_values_file)!="none") {
    TFile tvf(true_values_file.c_str());
    if (!tvf.IsOpen()) {
      LOG("valor_dune", pERROR)<<"Could not read true values file "<<true_values_file;
      util::Die(-1);
    }
    true_values_from_file = dynamic_cast<PhysParamList*>(tvf.Get(true_values_obj.c_str()));
    if (!true_values_from_file) {
      LOG("valor_dune", pERROR)<<"Could not read true values object "<<true_values_obj<<" from file "<<true_values_file;
      util::Die(-1);
    }
  }

  // Create file and tree to store outputs
  TString outfilename = TString::Format("%s_%d.root", arg.GetString("tag").c_str(), arg.GetInt("run"));
  StdFitNtp ntp;
  ntp.Create(outfilename.Data(), "valor_dune_nd_ntp", "VALOR DUNE / ND-Fit n-tuple");
  
  // Get ND model & configure
  LOG("valor_dune", pNOTICE) << "Getting and configuring the fit elements";
  CompoundFitElements * elements = new CompoundFitElements();
  std::string config_path = util::CompleteConfigPath(arg.GetString("config"));
  elements->Read(config_path);
  FitModelABC * model = elements->FitModel();
  
  // Use ND model to generate toy-MC experiments & fit
  for(int itoymc = 0; itoymc < ntoymc; itoymc++) {
    LOG("valor_dune", pNOTICE) << "\n\n *** Toy-MC experiment #" << itoymc;
    
    // Reset output tree variables
    ntp.Reset();
    
    // Get the specified fit parameter list (specifies which parameters are floated/fixed, 
    // parameter limits, initial values etc).
    FitParamList * fp = util::GetFitParameterList(fplname.c_str());

    model->ResetSystematics("all");
    // Randomise the systematics in the model, and copy them to the FPL
    if (param_values_ts.Contains("randomize")) {
      model->RandomizeSystematics(param_values_ts.Data());
    }

    PhysParamList tweaks = model->Tweaks();

    //~ // Don't randomise fixed parameters
    //~ for (int ip = 0; ip < conv::knppmax ; ip++) {
      //~ PhysParamId_t p = (PhysParamId_t)ip;
      //~ if (tweaks.Contains(p) and fp->IsFixed(p) ) {
        //~ double init = fp->InitValue(p);
        //~ tweaks.SetValue(p,init);
      //~ }
    //~ }
    
    fp->FromPhysParamList(tweaks,"current");

    // Check parameter name, maybe rethrow
    if (!PhysicalParameterLimits::Instance()->AllWithinLimits(*fp)) {
      LOG("valor_dune", pNOTICE) << "At least one parameter thrown outside expected limits.";
      if (rethrow_unphysical) {
        LOG("valor_dune", pNOTICE) << "Regenerating...";
        itoymc--;
        continue;
      }
    }
    
    // If we have a set of true values read from file, use those.
    if (true_values_from_file) {
      fp->FromPhysParamList(*true_values_from_file,"current");
    }
    
    // Update values of oscillation parameters 
    if(fplname != "only-nd"){

      //change if something different to default (i.e. normal, sinsqtheta, first octant and dmsq12abs23)
      Opt::Instance()->gMassHierarchyAssumed = ( (arg.GetBool("inverted"))     ? conv::kNmhInverted      : conv::kNmhNormal);
      Opt::Instance()->gOscMixingParamChoice = ( (arg.GetBool("sinsq2theta"))  ? conv::kNuMixSinsq2Theta : conv::kNuMixSinsqTheta);
      Opt::Instance()->gOscOctantChoice      = ( (arg.GetBool("second-octant"))? conv::kNuOctantTwo      : conv::kNuOctantOne);
      Opt::Instance()->gOscDmsqScheme        = ( (arg.GetBool("foglilisi"))    ? conv::kNuDmsqFogliLisi  : conv::kNuDmsq12andAbs23);
      
      double mixing12 = arg.GetDouble("input-mixing12");
      fp->Update(util::PhysParamFromString("mixing12"), mixing12);
      fp->SetInitValue(util::PhysParamFromString("mixing12"), mixing12);

      double mixing23 = arg.GetDouble("input-mixing23");
      fp->Update(util::PhysParamFromString("mixing23"), mixing23);
      fp->SetInitValue(util::PhysParamFromString("mixing23"), mixing23);

      double mixing13 = arg.GetDouble("input-mixing13");
      fp->Update(util::PhysParamFromString("mixing13"), mixing13);
      fp->SetInitValue(util::PhysParamFromString("mixing13"), mixing13);

      double dm23sq = arg.GetDouble("input-dm23sq");
      fp->Update(util::PhysParamFromString("dm23sq"), dm23sq);
      fp->SetInitValue(util::PhysParamFromString("dm23sq"), dm23sq);

      double dm12sq = arg.GetDouble("input-dm12sq");
      fp->Update(util::PhysParamFromString("dm12sq"), dm12sq);
      fp->SetInitValue(util::PhysParamFromString("dm12sq"), dm12sq);

      double deltacp = arg.GetDouble("input-deltaCP");
      fp->Update(util::PhysParamFromString("cpv"), deltacp);
      fp->SetInitValue(util::PhysParamFromString("cpv"), deltacp);

      // fix them? randomize them? 
      if(arg.GetBool("fix-mixing12")){
	fp->FixParameter(util::PhysParamFromString("mixing12"));
      }
      else if(param_values_ts.Contains("randomize-all")){
	string mode = ( (arg.GetBool("flat-prior-mixing12")) ? "flat" : "gaus" );
	double rnd_value = util::GetRandomizedOscParam(util::PhysParamFromString("mixing12"),mode);
	fp->Update(util::PhysParamFromString("mixing12"), rnd_value);
	fp->SetInitValue(util::PhysParamFromString("mixing12"), rnd_value);
      }
	
      if(arg.GetBool("fix-mixing13")) {
	fp->FixParameter(util::PhysParamFromString("mixing13"));
      }
      else if(param_values_ts.Contains("randomize-all")){
        string mode = ( (arg.GetBool("flat-prior-mixing13")) ? "flat" : "gaus" );
        double rnd_value = util::GetRandomizedOscParam(util::PhysParamFromString("mixing13"),mode);
	fp->Update(util::PhysParamFromString("mixing13"), rnd_value);
        fp->SetInitValue(util::PhysParamFromString("mixing13"), rnd_value);
      }

      if(arg.GetBool("fix-mixing23")) {
	fp->FixParameter(util::PhysParamFromString("mixing23"));
      }
      else if(param_values_ts.Contains("randomize-all")){
        string mode = ( (arg.GetBool("flat-prior-mixing23")) ? "flat" : "gaus" );
        double rnd_value = util::GetRandomizedOscParam(util::PhysParamFromString("mixing23"),mode);
        fp->Update(util::PhysParamFromString("mixing23"), rnd_value);
        fp->SetInitValue(util::PhysParamFromString("mixing23"), rnd_value);
      }

      if(arg.GetBool("fix-dm23sq")){
	fp->FixParameter(util::PhysParamFromString("dm23sq"));
      }
      else if(param_values_ts.Contains("randomize-all")){
        string mode = ( (arg.GetBool("flat-prior-dm23sq")) ? "flat" : "gaus" );
        double rnd_value = util::GetRandomizedOscParam(util::PhysParamFromString("dm23sq"),mode);
        fp->Update(util::PhysParamFromString("dm23sq"), rnd_value);
        fp->SetInitValue(util::PhysParamFromString("dm23sq"), rnd_value);
      }

      if(arg.GetBool("fix-dm12sq")) {
	fp->FixParameter(util::PhysParamFromString("dm12sq"));
      }
      else if(param_values_ts.Contains("randomize-all")){
        string mode = ( (arg.GetBool("flat-prior-dm12sq")) ? "flat" : "gaus" );
        double rnd_value = util::GetRandomizedOscParam(util::PhysParamFromString("dm12sq"),mode);
        fp->Update(util::PhysParamFromString("dm12sq"), rnd_value);
        fp->SetInitValue(util::PhysParamFromString("dm12sq"), rnd_value);
      }

      if(arg.GetBool("fix-deltaCP")) {
	fp->FixParameter(util::PhysParamFromString("cpv"));
      }
      else if(param_values_ts.Contains("randomize-all")){
        string mode = ( (arg.GetBool("flat-prior-deltaCP")) ? "flat" : "gaus" );
        double rnd_value = util::GetRandomizedOscParam(util::PhysParamFromString("cpv"),mode);
        fp->Update(util::PhysParamFromString("cpv"), rnd_value);
        fp->SetInitValue(util::PhysParamFromString("cpv"), rnd_value);
      }
      
    }

    PhysParamList true_params = fp->AsPhysParamList("current");
    
    // Generate a toy-MC experiment 
    LOG("valor_dune", pNOTICE) << "Generating toy-MC data";
    LOG("valor_dune", pNOTICE) << "Toy-MC generation uses true parameters: " << true_params;
    FitDataABC * data = elements->FitData();
    data->Generate(model,*fp,with_stat_fluct);
    
    // The toy-MC was generated using the `current' values of the input parameter list.
    // These values will be overwritten during the fit.
    // Copy those values now so as to save them later in the output tree.
    ntp.TrueParamArr()->Append(true_params);
    
    if (start_at_true) {
      // Before we do our start-at-true, we'll reset our fixed parameters to 1.
      for (int ip = 0 ; ip < fp->GetNumberParameters() ; ip++) {
        if (fp->IsFixedByIndex(ip)) {
          fp->SetCurrentValueByIndex(ip,fp->InitValueByIndex(ip));
        }
      }
      LOG("valor_dune", pNOTICE) << "Copying current values to initial values to give the fitter some help.";
      fp->CopyCurrToInitValues();
    }
           
    
    //before reset for the fit, fix to a different value? 
    double fix_deltacp = arg.GetDouble("fix-at-deltaCP");
    if((fix_deltacp > util::OscParamMinValue(util::PhysParamFromString("cpv"))) && 
       (fix_deltacp < util::OscParamMaxValue(util::PhysParamFromString("cpv"))))
      {
	fp->Update(util::PhysParamFromString("cpv"), fix_deltacp);
	fp->SetInitValue(util::PhysParamFromString("cpv"), fix_deltacp);
      }
    // Set our current values back to the fitter start point.
    // This will be central values unless start-at-true is defined.
    fp->ResetCurrToInitValues();

    // Get fitter
    LOG("valor_dune", pNOTICE) << "Preparing the fitter";
    FitInputs * fit_inputs = new FitInputs(data,model,fp);
    FitterABC * fitter = util::GetFitter(fit_inputs, fittername.c_str());

    // Do the fit
    LOG("valor_dune", pNOTICE) << "Running the fitter";
    LOG("valor_dune", pNOTICE) << "Fit starts with the following fit parameter list: " << *fp;
    LOG("valor_dune", pNOTICE) << "Fit starts with statistic: " << fit_inputs->Statistic();
    fitter->DoTheFit();

//  migradmin = fitter->FitStatusCode("migrad_min");
//  migraderr = fitter->FitStatusCode("migrad_err");

    // Copy best-fit params
    ntp.BestFitParamArr()->Copy(*fp);  

    if(arg.GetBool("store-spectra")) {
      // Copy best-fit to current values and re-generate the best-fit prediction
      // with special option (not used in the fit) to generate versions of the fit model
      // using a fine binning scheme (for plots).
      // Then, write-out the best-fit predictions
      fp->CopyBestFitToCurrValues();
      model->Generate(*fp,"+SB");
      TObjArray * best_fit_model_array = ntp.BestFitModelArr();
      model->Write(best_fit_model_array,"best_fit","pdfc_rf,pdft_rf,pdfts_rf,pdfcs_rf +SB");

      // Write-out the toy-MC
      TObjArray * data_array = ntp.DataArr();
      data->Write(data_array,"toymc","all");
    }

    // Write results to the output tree
    ntp.Fill();

    delete fp;
    delete fit_inputs;
    delete fitter;

  }//itoymc

  ntp.Save();
  
  //~ // Write a PPL with the prior uncertainties used
  //~ SDModel * ndm =  dynamic_cast<SDModel*>(model);
  //~ PhysParamList ppl = ndm->OneSigmaErrors();
  //~ ppl.Write("initial_errors");
  
  std::cout<<"Done."<< std::endl << " GO VALOR!!!" << std::endl;
  
  return 0;
}

