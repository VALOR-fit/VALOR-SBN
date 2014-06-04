//
// ------------------------------------------------------------------------------------------------
// Simple program to test the LBNx/ND PDFs
//
// Costas Andreopoulos
// ------------------------------------------------------------------------------------------------
//
	
void test_nd_pdf
(
  const char * config_file = "lbne_ndfit-2014a-STT_baseline.xml",    /* analysis configuration file */
  const char * tag         = "ND_STT_baseline"                       /* tag for output file */
)
{
  using namespace std;
  using namespace valor;
  using namespace valor::conv;

  // Analysis configuration
  TString config = Form("%s/config/%s", gSystem->Getenv("VALOR_LBNX"), config_file);

  // Print settings
  cout << "\n[Job inputs]" << endl;
  cout << "- Tag: " << tag << endl;
  cout << "- Reading analysis configuration from: " << config << endl;

  // Get ND model & configure
  FitModelABC * model = new NDModel;
  model->Read(config.Data());
}
