
void write_prefit_ntp(
  TString config = "fit/dune_ndfit.xml",
  TString outfilename = "prefit_ntp.root",
  TString fit_param_list = "standard"
)
{
  using namespace std;
  using namespace valor;
  Env::Instance()->AutoSet("dune");
  util::PrintBanner(Env::Instance()->Banner(),500);
  
  valor::StdFitNtp ntp;
  ntp.Create(outfilename.Data(), "valor_dune_nd_ntp", "VALOR DUNE / ND-Fit prior");
  
  string configpath = util::CompleteConfigPath(config.Data());
  // Get ND model & configure
  cout<< "Getting and configuring the fit elements"<<endl;
  CompoundFitElements * elements = new CompoundFitElements();
  elements->Read(configpath.c_str());
  FitModelABC * model = elements->FitModel();
  
  // Reset output tree variables
  ntp.Reset();
    
  // Get the specified fit parameter list (specifies which parameters are floated/fixed, 
  // parameter limits, initial values etc).
  FitParamList * fp = util::GetFitParameterList(fit_param_list.Data());
  PhysParamList true_params = fp->AsPhysParamList("current");
  ntp.TrueParamArr()->Append(true_params);
  
  // Copy prior errors
  const CompoundFitModel * cm = dynamic_cast<CompoundFitModel*>(model);
  assert(cm);
  
  TMatrixDSym prior_cov = util::MatrixToSymMatrix(cm->GetSystematics()->CovMatrix());
  fp->SetCovMatrix(prior_cov);

  // Copy best-fit params
  ntp.BestFitParamArr()->Copy(*fp);
  ntp.Fill();
  
  ntp.Save();
  
  cout<<"Done! Written to "<<outfilename<<endl;
}
  
