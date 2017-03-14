#include "dune/Testing/StandardTests.h"

// valor
#include "valor/Testing/ConfigurationTest.h"
#include "valor/Testing/MondrianKBTest.h"
#include "valor/Testing/PhysParamsTest.h"
#include "valor/Testing/TestSuite.h"

// dune
#include "dune/Testing/CubicEdge2EdgeKBTest.h"
#include "dune/Testing/UtlBinningTest.h"
#include "dune/Testing/UtlTest.h"

namespace valor
{
namespace testing
{

bool BatchTests(CmdLnArgList& arg)
{
   testing::TestSuite suite(arg);

   suite.Add("UtlTest", new UtlTest);
   suite.Add("MondrianKBTest", new MondrianKBTest);
   suite.Add("CubicEdge2EdgeKBTest", new CubicEdge2EdgeKBTest);
   suite.Add("UtlBinningTest", new UtlBinningTest);
   suite.Add("PhysParamsTest", new PhysParamsTest);
   suite.Add("ConfigurationTest", new ConfigurationTest);

   return suite.Run();
}

}
}

