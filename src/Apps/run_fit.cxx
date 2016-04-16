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
#include "TSystem.h"
#include "TObjArray.h"
#include "TString.h"
#include "TVirtualFitter.h"
// fmwk
#include "CmdLine/CmdLnArgList.h"
#include "FitCore/PhysParamList.h"
#include "FitCore/FitParamList.h"
#include "FitCore/FitModelABC.h"
#include "FitCore/FitDataABC.h"
#include "FitCore/FitInputs.h"
#include "FitCore/FitterABC.h"
#include "FitCore/UtlFit.h"
#include "Utilities/UtlStyle.h"
#include "Utilities/Rnd.h"
#include "Utilities/Env.h"
#include "Messenger/Messenger.h"
#include "Ntuple/StdFitNtp.h"
// dune
#include "Conventions/FitParam.h"
#include "Elements/CompoundFitElements.h"

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
  
  Messenger::Instance()->Configure(arg.GetString("mesg-thresholds"));
  
  // Set DUNE param names inside framework
  util::PopulateNameRegistry();
  
  // Set the random seeds
  Rnd::Instance()->SetSeeds(arg);
  
  LOG("valor_dune", pNOTICE) << *Rnd::Instance();

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
  for(int itoymc = 0; itoymc < arg.GetInt("ntoymc"); itoymc++) {
    LOG("valor_dune", pNOTICE) << "\n\n *** Toy-MC experiment #" << itoymc;
    
    // Reset output tree variables
    ntp.Reset();
    
    // Get the specified fit parameter list (specifies which parameters are floated/fixed, 
    // parameter limits, initial values etc).
    FitParamList * fp = util::GetFitParameterList(arg.GetString("fit-param-list").c_str());
   
    model->ResetSystematics("all");
    // Randomise the systematics in the model, and copy them to the FPL
    if (arg.GetBool("with-stat-fluct")) {
      model->RandomizeSystematics(param_values_ts.Data());
    }
    fp->FromPhysParamList(model->Tweaks(),"current");
    
    if (fit_options_ts.Contains("start-at-true")) {
      LOG("valor_dune", pNOTICE) << "Copying current values to initial values to give the fitter some help.";
      fp->CopyCurrToInitValues();
    }
    
    PhysParamList true_params = fp->AsPhysParamList("current");

    // Generate a toy-MC experiment 
    LOG("valor_dune", pNOTICE) << "Generating toy-MC data";
    LOG("valor_dune", pNOTICE) << "Toy-MC generation uses true parameters: " << true_params;
    FitDataABC * data = elements->FitData();
    data->Generate(model,*fp,arg.GetBool("with-stat-fluct"));

    // The toy-MC was generated using the `current' values of the input parameter list.
    // These values will be overwritten during the fit.
    // Copy those values now so as to save them later in the output tree.
    ntp.TrueParamArr()->Append(true_params);
    
    // Set our current values back to the fitter start point.
    // This will be central values unless start-at-true is defined.
    fp->ResetCurrToInitValues();
        
    // Get fitter
    LOG("valor_dune", pNOTICE) << "Preparing the fitter";
    FitInputs * fit_inputs = new FitInputs(data,model,fp);
    FitterABC * fitter = util::GetFitter(fit_inputs, arg.GetString("fitter").c_str());

    // Do the fit
    LOG("valor_dune", pNOTICE) << "Running the fitter";
    LOG("valor_dune", pNOTICE) << "Fit starts with the following fit parameter list: " << *fp;
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

