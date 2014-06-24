//
// ------------------------------------------------------------------------------------------------
// The macro studies a single fit (flux or cross-section) parameter sensitivity.
//
// The macro takes an input fit parameter list (N parameters) and fixes the specified parameter 
// to a number (npv) of values between a minimum (fit_param_min) and a maximum (fit_param_max) one.
// For each value, it generates a number (ntoymc) of toy-MC experiments and, for each experiment,
// performs a fits of N-1 parameters. The program stored the marginalized fit-statistic for each
// toy-MC experiment and averages it over ntoymc toy-MC experiments.
// The output data from several similar jobs can be combined to construct the averaged (over several 
// experiments) marginalised delta(fit-statistic) as a function of the input parameter value.
//
// Costas Andreopoulos
// ------------------------------------------------------------------------------------------------
//
	
void fit_param_scan
(
  const char * tag            = "fpsens",                              /* tag for output file */
  int          run            = 0,                                     /* run number */
  const char * pname          = 0,                                     /* parameter name */
  double       pmin           = 0,                                     /* min parameter value */
  double       pmax           = 2,                                     /* max parameter value */
  int          npv            = 10,                                    /* number of points between minimum and maximum */
  int          ntoymc         = 20,                                    /* number of toy-MC experiments */
  bool         stat_fluct     = true,                                  /* include statistical fluctuation in toy MC expts? */
  bool         tweak_syst     = 1,                                     /* generate toy MC with randomized systematics? (0: none, 1: all but input one set at fixed value)*/
  const char * fit_param_list = "default",                             /* fit parameter list for the given physics hypothesis (see ?) */
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
  cout << "- Scanning parameter: " << pname << " in range [" << pmin << ", " << pmax << "] using " << npv << " points";
  cout << "- Reading analysis configuration from: " << config << endl;
  cout << "- Toy-MC generation" << endl;
  cout << "   - Number of toy experiments: " << ntoymc << endl;
  cout << "   - Randomize systematics : "      << ((tweak_syst) ? "YES " : "NO") << endl;
  cout << "   - Statistical fluctuations: "    << ((stat_fluct) ? "YES " : "NO") << endl;
  cout << "- Fit" << endl;
  cout << "   - Fit Parameter List: " << fit_param_list << endl;
  cout << "   - Fitter option: " << fit_option << endl;
  cout << endl;
  cout << *Rnd::Instance() << endl;

  // Get ND model & configure
  cout << "Getting and configuring fit model" << endl;
  FitModelABC * model = new NDModel;
  model->Read(config.Data());

  // Get input fit param list and fix the parameter for which we are studying
  // our analysis sensitivity (this parameter will be set by hand to several values)
  cout << "Getting a fit parameter list" << endl;
  FitParamList * fp = util::GetFitParameterList("apriori-default");

  PhysParamId_t p = util::NDPhysParamFromString(pname);
  fp->FixParameter(p);
  cout << "Fixed parameter: " << util::AsString(p) << endl;
  
  //
  double pstep = (pmax - pmin) / (npv-1);

  for(int ipv = 0; ipv < npv; ipv++) {
    double pcurr = pmin + ipv * pstep;
    fp->Update(p, pcurr);
    cout << "Setting fixed parameter: " << util::AsString(p) << " to value = " << pcurr << endl;

    cout << "Averaging likelihod over " << ntoymc << " toy-MC experiments" << endl;
    for(int itoy = 0; itoy < ntoymc; itoy++) {
       cout << "Toy-MC #" << itoy << endl;

      // Get ND data or generate toy-MC experiment
      cout << "Generating toy-MC data" << endl;
      FitDataABC * data = new NDData;
      data->Generate(model,*fp,stat_fluct);
  
      // Get fitter & perform fit
      cout << "Fitting ..." << endl;
      FitInputs * fit_inputs = new FitInputs(data,model,fp);
      FitterABC * fitter = util::GetFitter(fit_inputs,fit_option);
      fitter->DoTheFit();

      delete data;
      delete fit_inputs;
    }//itoy
  }//ipv

}
