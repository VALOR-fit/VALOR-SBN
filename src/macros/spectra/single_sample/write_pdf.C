//
// ------------------------------------------------------------------------------------------------
// Simple program to write out the generic single sample PDFs and MC templates.
//
// Steve Dennis
// ------------------------------------------------------------------------------------------------
//
	
void write_pdf
(
  const char * model_param_list   = "standard",                             /* list of params included in model, see FitParam.cxx */
  //~ const char * model_param_values = "nominal",                              /* specify param values included in model, see FitParam.cxx */
  const char * config_file        = "fit/dune_ndfit.xml",    /* analysis configuration file */
  const char * write_opt          = "all"                                   /* define what to write-out, see SDModel::Write() for options */
)
{
  using namespace std;
  using namespace valor;
  using namespace valor::conv;

  // Analysis configuration
  TString config = Form("%s/config/%s", gSystem->Getenv("VALOR_DUNE"), config_file);

  // Print settings
  cout << "\n[Job inputs]" << endl;
  cout << "- Model parameter list used : " << model_param_list << endl;
  //~ cout << "- Setting parameter values: " << model_param_values << endl;
  cout << "- Reading analysis configuration from: " << config << endl;
  cout << endl;

  // Get ND model & configure
  CompoundFitElements * elements = new CompoundFitElements();
  elements->Read(config.Data());
  FitModelABC * model = elements->FitModel();

  // Get an initialized physics hypothesis  
  FitParamList * fp = util::GetFitParameterList(model_param_list);

  // Generate predictions
  Option_t * generate_opt = "+SB"; // also generate non-default (for fitting) predictions in extra binning schemes
  model->Generate(*fp,generate_opt);

  // Write stuff out
  model->Write("valor.root","valor",write_opt);
}
