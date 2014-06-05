//
// ------------------------------------------------------------------------------------------------
// Simple program to write out the LBNx/ND PDFs and MC templates.
//
// Costas Andreopoulos
// ------------------------------------------------------------------------------------------------
//
	
void write_nd_pdf
(
  const char * config_file = "lbne_ndfit-2014a-STT_baseline.xml",    /* analysis configuration file */
  const char * write_opt   = "all"                                   /* define what to write-out, see NDModel::Write() for options */
)
{
  using namespace std;
  using namespace valor;
  using namespace valor::conv;

  // Analysis configuration
  TString config = Form("%s/config/%s", gSystem->Getenv("VALOR_LBNX"), config_file);

  // Print settings
  cout << "\n[Job inputs]" << endl;
  cout << "- Reading analysis configuration from: " << config << endl;

  // Get ND model & configure
  FitModelABC * model = new NDModel;
  model->Read(config.Data());

  PhysHypothesis ph; // null, get default predictions

  // Generate predictions
  model->Generate(ph);

  // Write stuff out
  model->Write("valor.root","valor",write_opt);
}
