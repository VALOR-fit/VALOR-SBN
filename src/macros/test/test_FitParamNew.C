
// For testing the Parameter and ParameterPool class

// Francis Bench


#include "valor/Conventions/ParameterPool.h"
#include "valor/Conventions/Parameter.h"

void test_FitParamNew
(
  const char * param_file    = "params/params_test.xml"
)
{
  using std::cout;
  using std::endl;
  using namespace valor;
  using namespace valor::conv;

  // Analysis configuration
  TString param_file_full = Form("%s/config/%s", gSystem->Getenv("VALOR_EXPT"), param_file);

  ParameterPool::MutableInstance()->ReadXML(param_file_full.Data());
  ParameterPool::Instance()->CheckForCollisions();
  ParameterPool::Instance()->Print(std::cout);

}
