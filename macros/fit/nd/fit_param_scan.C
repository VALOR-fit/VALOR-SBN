//
// ------------------------------------------------------------------------------------------------
// The macro studies how the value of the fit statistic changes as function a single fit 
// (flux or cross-section) parameter. The fit statistic is calcuated for fixed values of all
// other fit parameters (i.e. they are not marginalized). For a similar macro that marginalizes
// all other parameters see: fit_param_sensitivity.C
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
  cout << "- Scanning parameter: " << pname << " in range [" << pmin << ", " << pmax << "] using " << npv << " points" << endl;
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

  PhysParamId_t p = util::NDPhysParamFromString(pname);

  // Get ND model & configure
  cout << "Getting and configuring fit model" << endl;
  FitModelABC * model = new NDModel;
  model->Read(config.Data());

  // Create histogram to plot \Delta{fit statistic} vs parameter
  // Arrange so that the first bin is centered at pmin and the last bin is centered at pmax
  
  //
  double pstep = (pmax - pmin) / (npv-1);
  TH1D * h = new TH1D("h","",npv,pmin-0.5*pstep,pmax+0.5*pstep);

  for(int ipv = 0; ipv < npv; ipv++) {
    double pcurr = pmin + ipv * pstep;
    cout << "Parameter: " << util::AsString(p) << " -> value = " << pcurr << endl;

    double avg_fit_statistic = 0;

    cout << "Averaging over " << ntoymc << " toy-MC experiments" << endl;
    for(int itoy = 0; itoy < ntoymc; itoy++) {
       cout << "Toy-MC #" << itoy << endl;

       // Get the fit param list ith nominal values and generate a toy-MC experiment
       Option_t * toymcopt = ((tweak_syst == 0) ? "apriori-default" : "apriori-randomize");
       cout << "Generating toy-MC data (option = " << toymcopt << ")" << endl;
       FitParamList * fp = util::GetFitParameterList(toymcopt);        
       fp->ShowOnlyCurrValuesInNextPrint();
       cout << *fp;
       FitDataABC * data = new NDData;
       data->Generate(model,*fp,stat_fluct);

       // Set input param to current value and calculate the fit statistic
       cout << "Calculating fit-statistic" << endl;
       FitParamList * fp2 = util::GetFitParameterList("apriori-default");
       fp2->Update(p, pcurr);
       //fp2->ShowOnlyCurrValuesInNextPrint();
       //cout << *fp2;
       double fit_statistic = data->Statistic(model,*fp2,"likelihood-ratio");

       avg_fit_statistic += fit_statistic;

       delete fp;
       delete fp2;
       delete data;
    }//itoy

    avg_fit_statistic /= ntoymc;
    h->Fill(pcurr, avg_fit_statistic);
  }//ipv

  double min = h->GetMinimum();
  for(int ibin=1; ibin <= h->GetXaxis()->GetNbins(); ibin++) {
    double val = h->GetBinContent(ibin);
    double valnew = val-min;
    h->SetBinContent(ibin,valnew);
  }

  delete model;

  h->GetXaxis()->SetTitle(util::AsStringTeX(p,true).c_str());
  h->GetYaxis()->SetTitle("-#Delta(lnL)");
  h->SetMarkerSize(1.3);
  h->SetMarkerStyle(20);
  h->Draw("LP");
}
