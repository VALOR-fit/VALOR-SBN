//
// ------------------------------------------------------------------------------------------------
// The macro studies a single fit (flux or cross-section) parameter sensitivity.
//
// The macro takes an input fit parameter list (N parameters) and fixes the specified parameter 
// to a number (npv) of values between a minimum (fit_param_min) and a maximum (fit_param_max) one.
// For each value, it generates a number (ntoymc) of toy-MC experiments. 
// For each toy-MC, the other N-1 parameters could be randomized (or not) in a pattern described
// by an input parameter (param_values). 
// Statistical fluctuations may or may not included depending on an input parameter (stat_fluct).
// A fit is performed for each toy-MC. The list of fit parameters (all N, or subset) is
// specified by an input parameter (fit_param_list).
// A tree with the true and best-fit params for each toy-MC is written out.
// The output data from several similar jobs can be combined to construct the averaged (over several 
// experiments) marginalised -\Delta(lnL) as a function of the true input parameter value.
//
// Costas Andreopoulos
// ------------------------------------------------------------------------------------------------
//
	
void fit_param_sensitivity
(
  const char * tag            = "sensitivity",                         /* tag for output file */
  int          run            = 0,                                     /* run number */
  const char * pname          = 0,                                     /* parameter name */
  double       pval           = 0,                                     /* parameter value */
  int          ntoymc         = 20,                                    /* number of toy-MC experiments */
  bool         stat_fluct     = true,                                  /* include statistical fluctuation in toy MC expts? */
  const char * param_values   = "randomize-all;prefit-errors",         /* decide how to set the values of params used for toy-MC generation (see NDFitParams.cxx) */
  const char * fit_param_list = "standard",                            /* fit parameter list (see NDFitParams.cxx) */
  const char * fit_option     = "minuit",                              /* fitter option */
  const char * config_file    = "lbne_ndfit-2014a-STT_baseline.xml"    /* analysis configuration file */
)
{
  using namespace std;
  using namespace valor;
  using namespace valor::conv;

  // Analysis configuration
  TString config = Form("%s/config/%s", gSystem->Getenv("VALOR_LBNX"), config_file);

  // Print settings
  cout << "\n[Job inputs]" << endl;
  cout << "- Job: " << tag << "/" << run << endl;
  cout << "- Studying sensitivity for parameter: " << pname << " at true value = " << pval << endl;
  cout << "- Reading analysis configuration from: " << config << endl;
  cout << "- Toy-MC generation" << endl;
  cout << "   - Number of toy experiments: " << ntoymc << endl;
  cout << "   - Statistical fluctuations: "    << ((stat_fluct) ? "YES " : "NO") << endl;
  cout << "   - Option for setting parameter values: " << param_values << endl;
  cout << "- Fit" << endl;
  cout << "   - Fit parameter list: " << fit_param_list << endl;
  cout << "   - Fitter option: " << fit_option << endl;
  cout << endl;
  cout << *Rnd::Instance() << endl;

  // Get studied param ID and step size
  PhysParamId_t p = util::NDPhysParamFromString(pname);

  // Open output file and create output TTree
  const char * outfilename = Form("%s-%s-%d.root",tag,pname,run);
  TFile * outfile = new TFile(outfilename,"recreate");
  PhysParamList * true_param_array     = new PhysParamList;
  FitParamList *  best_fit_param_array = new FitParamList;
  TTree * fitnt = new TTree("fitnt","VALOR toy-MC experiment fit results");
  fitnt->Branch("true_params",     "valor::PhysParamList", &true_param_array,     1280000,0);
  fitnt->Branch("best_fit_params", "valor::FitParamList",  &best_fit_param_array, 1280000,0);

  // Get ND model & configure
  cout << "Getting and configuring fit model" << endl;
  FitModelABC * model = new NDModel;
  model->Read(config.Data());

  for(int itoy = 0; itoy < ntoymc; itoy++) {
     cout << "Toy-MC #" << itoy << endl;

     // Reset arrays
     true_param_array     -> Clear();
     best_fit_param_array -> Clear();

     // Get input fit param list and set the current parameter values
     // according to the input option (ie params can be randomized).
     cout << "Getting a fit parameter list" << endl;
     FitParamList * fp = util::GetFitParameterList(fit_param_list,param_values);

     cout << "Fixing parameter: " << util::AsString(p) << " to value = " << pval << endl;
     fp->Update(p, pval);

     // Store current params used as true params for toy-MC generation below
     true_param_array->Append(fp->AsPhysParamList("current"));

     // Generate toy-MC experiment
     cout << "Generating toy-MC data" << endl;
     FitDataABC * data = new NDData;
     data->Generate(model,*fp,stat_fluct);

     // Get fitter & perform fit
     cout << "Fitting ..." << endl;
     FitInputs * fit_inputs = new FitInputs(data,model,fp);
     FitterABC * fitter = util::GetFitter(fit_inputs,fit_option);
     fitter->DoTheFit();

     // Store params from current fit
     best_fit_param_array->Copy(*fp);

     // Write to tree
     fitnt->Fill();

     // Clean-up
     delete fit_inputs;
     delete fitter;
     delete data;
     delete fp;

  }//itoy

  // Clean-up
  delete model;

  // Write output tree to file
  outfile->cd();
  fitnt->Write();
  outfile->Close();
}
