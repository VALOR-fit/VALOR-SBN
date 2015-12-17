//____________________________________________________________________________
/*!

\app       valor_dune-run_nd_fit

\brief     Generate and fit ensembles of toy-MC experiments.

\options     --tag                 : Tag for output file [def: "toymc"]
             --run                 : Run # [def: 0]
             --ntoymc              : Number of toy-MC experiments [def: 1]
             --fit-param-list      : Fit parameter list (see NDFitParams.cxx) 
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
// dune
#include "NDFit/NDModel.h"
#include "NDFit/NDData.h"
#include "NDFit/NDNtp.h"
#include "NDFit/NDXArg.h"

using namespace std;
using namespace valor;
using namespace valor::conv;

int main(int argc, char ** argv)
{
  Env::Instance()->AutoSet("dune");

  NDXArg arg;
  arg.SetDefaults(); 
  arg.ParseFromCmdLine(argc,argv);
  LOG("valor_dune", pNOTICE) << arg;

//  cout << *Rnd::Instance() << endl;

  Messenger::Instance()->Configure(arg.VerbosityFile());

  // Create file and tree to store outputs
  const char * outfilename = Form("%s_%d.root", arg.JobTag(), (int) arg.RunNu());
  NDNtp ntp;
  ntp.Create(outfilename);

//  fitnt->Branch("migradmin", &migradmin); // <-- arent't these within FitParamsList?
//  fitnt->Branch("migraderr", &migraderr);

  // Get ND model & configure
  cout << "Getting and configuring fit model" << endl;
  FitModelABC * model = new NDModel;
  model->Read(arg.ConfigFile());

  // Use ND model to generate toy-MC experiments & fit
  for(int itoymc = 0; itoymc < arg.NToyMC(); itoymc++) {
    cout << "\n\n *** Toy-MC experiment #" << itoymc << endl;
	
    // Reset output tree variables
    ntp.Reset();

    // Getting the fit parameter list that corresponds to the input option.
    // The secondd option determined the `current' values which are used for toy-MC generation below.
    FitParamList * fp = util::GetFitParameterList(arg.FitParamList(), arg.ParamValuesOption());

    // Generate a toy-MC experiment 
    cout << "Generating toy-MC data" << endl;
    FitDataABC * data = new NDData;
    data->Generate(model,*fp,arg.StatFluct());

    // The toy-MC was generated using the `current' values of the input parameter list.
    // These values will be overwritten during the fit.
    // Copy those values now so as to save them later in the output tree.
    ntp.TrueParamArr()->Append(fp->AsPhysParamList("current"));

    // Get fitter
    cout << "Preparing fitter" << endl;
    FitInputs * fit_inputs = new FitInputs(data,model,fp);
    FitterABC * fitter = util::GetFitter(fit_inputs, arg.FitOption());

    // Do the fit
    cout << "Running fitter" << endl;
    fitter->DoTheFit();

//  migradmin = fitter->FitStatusCode("migrad_min");
//  migraderr = fitter->FitStatusCode("migrad_err");

    // Copy best-fit params
    ntp.BestFitParamArr()->Copy(*fp);  

    if(arg.StoreSpectra()) {
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

  return 0;
}

