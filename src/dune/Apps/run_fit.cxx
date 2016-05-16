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
  
  Messenger::Instance()->Configure(arg.GetString("mesg-thresholds"));
  
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
  elements->Read(arg.GetString("config"));
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
  
  return 0;
}

