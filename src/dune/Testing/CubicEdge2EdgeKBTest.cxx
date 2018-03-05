#include "dune/Testing/CubicEdge2EdgeKBTest.h"

// valor
#include "valor/Utilities/UtlFile.h"

namespace valor
{
namespace testing
{

bool CubicEdge2EdgeKBTestCase::TestContract()
{
   SingleSampleKineBinning& binning = 
      *(dynamic_cast<CubicEdge2EdgeKBTest*>(_test)->_binning);
      
   KBCubHcmbEdge2Edge * tmpb = dynamic_cast<KBCubHcmbEdge2Edge*>(binning.RecoSmpBinning());
   if (!tmpb) { return false; }
   KBCubHcmbEdge2Edge& recoBinning = *tmpb;

   bool passed = true;

   // Ereco
   KBCubHcmbEdge2Edge* newBinning = recoBinning.Contract(conv::kspEreco);

   passed = Test::Equal(newBinning->NBins(), 4) && passed;

   // Check bin edges
   passed = Test::Equal(newBinning->BinMinimum(0, 0), 0.0) &&
      Test::Equal(newBinning->BinMaximum(0, 0), 50.0) && passed;
   passed = Test::Equal(newBinning->BinMinimum(1, 0), 50.0) &&
      Test::Equal(newBinning->BinMaximum(1, 0), 100.0) && passed;
   passed = Test::Equal(newBinning->BinMinimum(2, 0), 100.0) &&
      Test::Equal(newBinning->BinMaximum(2, 0), 150.0) && passed;
   passed = Test::Equal(newBinning->BinMinimum(3, 0), 150.0) &&
      Test::Equal(newBinning->BinMaximum(3, 0), 200.0) && passed;

   // Check minima and maxima
   passed = Test::Equal(newBinning->Minimum(0), 0.0) && passed;
   passed = Test::Equal(newBinning->Maximum(0), 200.0) && passed;

   delete newBinning;

   // Yreco
   newBinning = recoBinning.Contract(conv::kspYreco);

   passed = Test::Equal(newBinning->NBins(), 3) && passed;

   // Check bin edges
   passed = Test::Equal(newBinning->BinMinimum(0, 0), 0.0) &&
      Test::Equal(newBinning->BinMaximum(0, 0), 1.0 / 3.0) && passed;
   passed = Test::Equal(newBinning->BinMinimum(1, 0), 1.0 / 3.0) &&
      Test::Equal(newBinning->BinMaximum(1, 0), 2.0 / 3.0) && passed;
   passed = Test::Equal(newBinning->BinMinimum(2, 0), 2.0 / 3.0) &&
      Test::Equal(newBinning->BinMaximum(2, 0), 1.0) && passed;

   // Check minima and maxima
   passed = Test::Equal(newBinning->Minimum(0), 0.0) && passed;
   passed = Test::Equal(newBinning->Maximum(0), 1.0) && passed;

   delete newBinning;

   return passed;
}

void CubicEdge2EdgeKBTest::Setup()
{
   // Retrieve the location of the Mondrian XML file
   std::string filename = _arg->GetString("binning-file");
   std::string fullFilename = util::file::GetConfigurationFilename(filename);
   
   _binning = new SingleSampleKineBinning(conv::kdDUNEFD1ph, conv::kbLBNF_FHC,
        conv::ksNuMuCC);
   _binning->Read(fullFilename);
}

void CubicEdge2EdgeKBTest::Teardown()
{
   delete _binning;
}

void CubicEdge2EdgeKBTest::AddTests()
{
   CubicEdge2EdgeKBTestCase* testCase = new CubicEdge2EdgeKBTestCase(this);

   Add(new TestKey("TestContract", testCase),
         [testCase](void) { return testCase->TestContract(); });
}

}
}
