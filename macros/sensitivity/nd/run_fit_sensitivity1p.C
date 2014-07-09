//
// ------------------------------------------------------------------------------------------------
// Generate and fit ensembles of toy-MC experiments.
//
// Costas Andreopoulos
// ------------------------------------------------------------------------------------------------
//
	
void run_fit_sensitivity1p
(
  const char * tag                   = "toymc",                               /* tag for output file */
  int          run                   = 0,                                     /* run # */
  int          ntoymc                = 1,                                     /* number of toy-MC experiments */
  const char * fit_param_list        = "standard",                            /* fit parameter list (see NDFitParams.cxx) */
  const char * param_values          = "randomize-all;prefit-errors",         /* decide how to set the values of params used for toy-MC generation */
  const char * s_param_name          = 0,                                     /* specify the param name (see NDFitParams.cxx) whose sensitivity to is studied */
  double       s_param_value_gen     = 1,                                     /* value for above param for toy-MC generation */
  int          nfits                 = 11,                                    /* number of fits for each toy-MC (for different fixed values of above param) */
  double       s_param_value_fit_min = 0.9,                                   /* min fixed value of above param */
  double       s_param_value_fit_max = 1.1,                                   /* max fixed value of above param */
  bool         stat_fluct            = true,                                  /* include statistical fluctuation in toy MC generation? */
  const char * fit_option            = "minuit",                              /* fitter option */
  bool         store_spectra         = false,                                 /* store toy-MC and best-fit spectra? (default: store only true and best-fit parameters) */
  const char * config_file           = "lbne_ndfit-2014a-STT_baseline.xml"    /* analysis configuration file */
)

{
  using namespace std;
  using namespace valor;
  using namespace valor::conv;

  // Analysis configuration
  TString config = Form("%s/config/%s", gSystem->Getenv("VALOR_LBNX"), config_file);
 
  assert(s_param_name);    

  PhysParamId_t sp = util::NDPhysParamFromString(s_param_name);
  cout << util::AsString(sp) << endl;
  if(sp == kPhypUndefined) {
    cerr << "Undefined parameter: " << s_param_name << endl;
    exit(1);
  }

  //
  // Print settings
  //

  cout << "\n[Job inputs]" << endl;
  cout << "- Job: " << tag << "/" << run << endl;
  cout << "- Reading analysis configuration from: " << config << endl;
  cout << "- Studying sensitivity to parameter: " << s_param_name << endl;
  cout << "- Toy-MC generation" << endl;
  cout << "   - Number of toy experiments: " << ntoymc << endl;
  cout << "   - Statistical fluctuations: "  << ((stat_fluct) ? "YES " : "NO") << endl;
  cout << "   - Option for setting parameter values: " << param_values << endl;
  cout << "   - *Fixing* parameter: " << s_param_name << " to value = " << s_param_value_gen << endl;
  cout << "- Fit" << endl;
  cout << "   - Fit Parameter List: " << fit_param_list << endl;
  cout << "   - Will perform " << nfits << " fits per toy-MC, fixing " 
       << s_param_name << " at regularly distributed values in range [" << s_param_value_fit_min << ", " << s_param_value_fit_max << "]" << endl;
  cout << "   - Fitter option: " << fit_option << endl;
  cout << endl;
  cout << *Rnd::Instance() << endl;

  //
  // Create file and tree to store outputs
  //

  const char * outfilename = Form("%s_%d.root",tag,run);
  TFile * outfile = new TFile(outfilename,"recreate");

  PhysParamList * true_param_array     = new PhysParamList;
  FitParamList *  best_fit_param_array = new FitParamList;
  TObjArray *     best_fit_model_array = new TObjArray;
  TObjArray *     data_array           = new TObjArray;
  best_fit_model_array -> SetOwner(false);
  data_array           -> SetOwner(false);

  TTree * fitnt = new TTree("fitnt","VALOR toy-MC experiment fit results");
  fitnt->Branch("true_params",     "valor::PhysParamList", &true_param_array,     1280000,0);
  fitnt->Branch("best_fit_params", "valor::FitParamList",  &best_fit_param_array, 1280000,0);
  fitnt->Branch("best_fit_model",  "TObjArray",            &best_fit_model_array, 1280000,0);
  fitnt->Branch("data",            "TObjArray",            &data_array,           1280000,0);

  // Get ND model & configure
  cout << "Getting and configuring fit model" << endl;
  FitModelABC * model = new NDModel;
  model->Read(config.Data());

  // Use ND model to generate toy-MC experiments & fit
  for(int itoymc = 0; itoymc < ntoymc; itoymc++) {
    cout << "\n\n *** Toy-MC experiment #" << itoymc << endl;

    // Reset arrays
    true_param_array     -> Clear();
    best_fit_param_array -> Clear();
    best_fit_model_array -> Clear();
    data_array           -> Clear();

    // Getting the fit parameter list that corresponds to the input option.
    // The secondd option determined the `current' values which are used for toy-MC generatio below.
    FitParamList * fp = util::GetFitParameterList(fit_param_list, param_values);

    // Make sure the specified parameter exists in the specified list of parameters
    if(! fp->Exists(sp)) {
       cerr << "Parameter: " << s_param_name << " does not exist in list named: " << fit_param_list << endl;
       exit(1);
    }

    // If user wants to generate toy-MC for fixed values of a parameter 
    // (but, potentially, with all other params randomized, eg for sensitivity studies) do it here
    fp->Update      (sp, s_param_value_gen); // matters when I call NDModel::Generate()
    fp->SetInitValue(sp, s_param_value_gen); // matters when the fitter starts calling NDModel::Generate()
    cout << "Toy-MC generated for a fixed value of parameter: " << s_param_name << " (= " << s_param_value_gen << ")" << endl;
    //cout << *fp << endl;

    // Generate a toy-MC experiment 
    cout << "Generating toy-MC data" << endl;
    FitDataABC * data = new NDData;
    data->Generate(model,*fp,stat_fluct);

    // The toy-MC was generated using the `current' values of the input parameter list.
    // Copy those values now (and they will be overwritten during the fit) to save 
    // them in the output fit file.
    true_param_array->Append(fp->AsPhysParamList("current"));
    cout << "Toy-MC #" << itoymc << " was generated with true parameters: " << *true_param_array; 

    //
    // Perform the fit several times, fixing the specified parameter to a set of values
    // and fitting the remaining params in the specified list
    //

    for(int ifit = 0; ifit < nfits; ifit++) {

       cout << " Toy-MC #" << itoymc << ", fit #" << ifit+1 << "/" << nfits << endl;

       // Set specified param to a value in given range and fix
       double s_param_value_fit = s_param_value_fit_min + ifit * (s_param_value_fit_max - s_param_value_fit_min)/(nfits-1);
       cout << "The fit fixes the value of parameter: " << s_param_name << " (= " << s_param_value_fit 
            << ") and allows all the remaining params to float" << endl;

       FitParamList * fp2 = new FitParamList(*fp);
       fp2->Update      (sp, s_param_value_fit); // matters when I call NDModel::Generate()
       fp2->SetInitValue(sp, s_param_value_fit); // matters when the fitter starts calling NDModel::Generate()
       fp2->FixParameter(sp);

       // Get fitter
       cout << "Preparing fitter" << endl;
       FitInputs * fit_inputs = new FitInputs(data,model,fp2);
       FitterABC * fitter = util::GetFitter(fit_inputs,fit_option);

       // Do the fit
       cout << "Running fitter" << endl;
       cout << "Fit parameter list before running the fitter: " << *fp2;
       fitter->DoTheFit();

       // Copy best-fit params
       best_fit_param_array->Copy(*fp2);

       if(store_spectra) {
         // Copy best-fit to current values and re-generate the best-fit prediction
         // with special option (not used in the fit) to generate versions of the fit model
         // using a fine binning scheme (for plots).
         // Then, write-out the best-fit predictions
         fp2->CopyBestFitToCurrValues();
         model->Generate(*fp2,"+SB");
         model->Write(best_fit_model_array,"best_fit","pdfc_rf,pdft_rf,pdfts_rf,pdfcs_rf +SB");
         // Write-out the toy-MC
         data->Write(data_array,"toymc","all");
       }

       // Write to tree
       fitnt->Fill();

       delete fit_inputs;
       delete fp2;
       delete fitter;

    }//ifit

    delete fp;
    delete data;

  }//itoymc

  delete model;

  outfile->cd();
  fitnt->Write();
  outfile->Close();
}
