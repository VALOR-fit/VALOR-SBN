//____________________________________________________________________________
/*!

\app       valor_lbnx-run_nd_fit

\brief     Generate and fit ensembles of toy-MC experiments.

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\created   March 27, 2014

\copyright (c) 2010-2015, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

// system
#include <iostream>
// root
#include "TSystem.h"
#include "TObjArray.h"
#include "TString.h"
#include "TVirtualFitter.h"
// fmwk
#include "FitCore/PhysParamList.h"
#include "FitCore/FitParamList.h"
#include "FitCore/FitModelABC.h"
#include "FitCore/FitDataABC.h"
#include "FitCore/FitInputs.h"
#include "FitCore/FitterABC.h"
#include "FitCore/UtlFit.h"
#include "Utilities/Rnd.h"
#include "Utilities/Env.h"
#include "Messenger/Messenger.h"
// lbnx
#include "NDFit/NDModel.h"
#include "NDFit/NDData.h"
#include "NDFit/NDNtp.h"
#include "NDFit/NDXArg.h"

using namespace std;
using namespace valor;
using namespace valor::conv;

//void run_fit
//(
//  const char * tag              = "toymc",                               /* tag for output file */
//  int          run              = 0,                                     /* run # */
//  int          ntoymc           = 1,                                     /* number of toy-MC experiments */
//  const char * fit_param_list   = "standard",                            /* fit parameter list (see NDFitParams.cxx) */
//  const char * param_values     = "randomize-all;prefit-errors",         /* decide how to set the values of params used for toy-MC generation */
//  bool         stat_fluct       = true,                                  /* include statistical fluctuation in toy MC generation? */
//  const char * fit_option       = "minuit",                              /* fitter option */
//  bool         store_spectra    = false,                                 /* store toy-MC and best-fit spectra? (default: store only true and best-fit parameters) */
//  const char * config_file      = "lbne_ndfit-2014a-STT_baseline.xml",   /* analysis configuration file */
//  const char * verbosity_file   = "verbosity.xml"                        /* message thresholds */
//);

/*
void run_fit
(
  const char * tag,
  int          run,
  int          ntoymc,
  const char * fit_param_list,
  const char * param_values,
  bool         stat_fluct,
  const char * fit_option,
  bool         store_spectra,
  const char * config_file,
  const char * verbosity_file
)
*/


int main(int argc, char ** argv)
{
  Env::Instance()->AutoSet("lbnx");

  NDXArg arg;
  arg.SetDefaults(); 
  arg.ParseFromCmdLine(argc,argv);

  LOG("valor_lbnx", pNOTICE) << arg;
  



  return 0;
}

/*

{
  // Analysis configuration
  TString config    = Form("%s/%s", Env::Instance()->TopLevelConfDir().c_str(), config_file   );
  TString verbosity = Form("%s/%s", Env::Instance()->TopLevelConfDir().c_str(), verbosity_file);

  Messenger::Instance()->Configure(verbosity.Data());

  //
  // Print settings
  //

  cout << "\n[Job inputs]" << endl;
  cout << "- Job: " << tag << "/" << run << endl;
  cout << "- Reading analysis configuration from: " << config << endl;
  cout << "- Toy-MC generation" << endl;
  cout << "   - Number of toy experiments: " << ntoymc << endl;
  cout << "   - Statistical fluctuations: "  << ((stat_fluct) ? "YES " : "NO") << endl;
  cout << "   - Option for setting parameter values: " << param_values << endl;
  cout << "- Fit" << endl;
  cout << "   - Fit Parameter List: " << fit_param_list << endl;
  cout << "   - Fitter option: " << fit_option << endl;
  cout << endl;
  cout << *Rnd::Instance() << endl;

  //
  // Create file and tree to store outputs
  //

  const char * outfilename = Form("%s_%d.root",tag,run);

  NDNtp ntp;
  ntp.Create(outfilename);

//  fitnt->Branch("migradmin",                               &migradmin);
//  fitnt->Branch("migraderr",                               &migraderr);

  // Get ND model & configure
  cout << "Getting and configuring fit model" << endl;
  FitModelABC * model = new NDModel;
  model->Read(config.Data());

  // Use ND model to generate toy-MC experiments & fit
  for(int itoymc = 0; itoymc < ntoymc; itoymc++) {
    cout << "\n\n *** Toy-MC experiment #" << itoymc << endl;

    // Reset output tree variables
    ntp.Reset();

    // Getting the fit parameter list that corresponds to the input option.
    // The secondd option determined the `current' values which are used for toy-MC generatio below.
    FitParamList * fp = util::GetFitParameterList(fit_param_list, param_values);

    // Generate a toy-MC experiment 
    cout << "Generating toy-MC data" << endl;
    FitDataABC * data = new NDData;
    data->Generate(model,*fp,stat_fluct);

    // The toy-MC was generated using the `current' values of the input parameter list.
    // These values will be overwritten during the fit.
    // Copy those values now so as to save them later in the output tree.
    ntp.TrueParamArr()->Append(fp->AsPhysParamList("current"));

    // Get fitter
    cout << "Preparing fitter" << endl;
    FitInputs * fit_inputs = new FitInputs(data,model,fp);
    FitterABC * fitter = util::GetFitter(fit_inputs,fit_option);

    // Do the fit
    cout << "Running fitter" << endl;
    fitter->DoTheFit();

//    migradmin = fitter->FitStatusCode("migrad_min");
//    migraderr = fitter->FitStatusCode("migrad_err");

    // Copy best-fit params
    ntp.BestFitParamArr()->Copy(*fp);  

    if(store_spectra) {
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

    delete data;
    delete fp;
    delete fit_inputs;
    delete fitter;

  }//itoymc

  ntp.Save();
}

*/
