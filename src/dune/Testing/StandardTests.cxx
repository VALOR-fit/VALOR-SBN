#include "dune/Testing/StandardTests.h"

namespace valor
{
namespace testing
{

bool BatchTests(CmdLnArgList& arg)
{
   testing::TestSuite suite(arg);

   suite.Add("UtlTest", new testing::UtlTest);
   suite.Add("MondrianKBTest", new testing::MondrianKBTest);
   suite.Add("CubicEdge2EdgeKBTest", new testing::CubicEdge2EdgeKBTest);
   suite.Add("UtlBinningTest", new testing::UtlBinningTest);
   suite.Add("PhysParamsTest", new testing::PhysParamsTest);

   return suite.Run();
}

}
}

