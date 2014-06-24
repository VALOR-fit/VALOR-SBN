//
// ------------------------------------------------------------------------------------------------
//
// Costas Andreopoulos
// ------------------------------------------------------------------------------------------------
//
	
void run_fit
(
  const char * tag            = "toymc",                               /* tag for output file */
  bool         stat_fluct     = false,                                 /* include statistical fluctuation in toy MC expts? */
  int          tweak_syst     = 0,                                     /* generate toy MC with randomized systematics? (0: none, 1: all)*/
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
  cout << "- Job: " << tag << endl;
//cout << "- Job: " << tag << "/" << run << endl;
  cout << "- Reading analysis configuration from: " << config << endl;
  cout << "- Toy-MC generation" << endl;
//cout << "   - Number of toy experiments: " << nexperiments << endl;
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

  // 
  cout << "Getting a fit parameter list" << endl;
  FitParamList * fp = util::GetFitParameterList("apriori-default");

  // Get ND data or generate toy-MC experiment
  cout << "Generating toy-MC data" << endl;
  FitDataABC * data = new NDData;
  data->Generate(model,*fp,stat_fluct);
  
  // Get fitter
  cout << "Preparing fitter" << endl;
  FitInputs * fit_inputs = new FitInputs(data,model,fp);
  FitterABC * fitter = util::GetFitter(fit_inputs,fit_option);

  // Do the fit
  cout << "Running fitter" << endl;
  fitter->DoTheFit();

  fp->GetCovMatrix()->Print();

  TFile f("cov.root","recreate");
  TMatrixDSym * cov = new TMatrixDSym(*fp->GetCovMatrix());
  cov->Write("cov");
  f.Close();
}
