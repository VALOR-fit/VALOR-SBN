//____________________________________________________________________________
/*!

\app       valor_dune-run_tests

\brief     Tests for GENIE true kinematics.

\options     --mc-events-file   : The file containing the GENIE events [required]
             --mesg-thresholds  : Message thresholds [def: "verbosity.xml"]

\author    Andy Chappell <A.Chappell \at warwick.ac.uk>
           University of Warwick

\created   February 20, 2017

\copyright (c) 2010-2017, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#include <string>

// valor
#include "valor/Messenger/Messenger.h"
#include "valor/CmdLine/CmdLnArgList.h"
#include "valor/FitCore/PhysParams.h"
#include "valor/Utilities/Env.h"
#include "valor/KineBinning/KBCubHcmbMondrian.h"
#include "valor/Utilities/FitParamListFactory.h"
#include "valor/Utilities/UtlFile.h"
#include "valor/Testing/PhysParamsTest.h"
#include "valor/Testing/TestSuite.h"

// dune
#include "dune/Conventions/FitParam.h"
#include "dune/Conventions/BeamConf.h"
#include "dune/Conventions/Detector.h"
#include "dune/Conventions/Sample.h"
#include "dune/Utilities/UtlBinning.h"
#include "dune/Testing/UtlTest.h"

using namespace valor;
using namespace valor::conv;

/**
   Tests the equality of double-precision floating point numbers within a given
   arithmetic tolerance.

   \param obs The observed value.
   \param b The expected value.
   \param tol The tolerance of the comparison. Default 1E-6.

   \return True if the numbers are equal within tolerance, false otherwise.
*/
bool Equal(double obs, double exp, double tol = 1E-6)
{
   bool equal = (abs(obs - exp) < tol);
   if(!equal)
   {
      LOG("Test", pERROR) << "Test failed: Expected " << exp << ". Found " <<
         obs << ".";
   }
   return equal;
}

/**
   Tests the equality of integer values.

   \param obs The observed value.
   \param exp The expected value.

   \return True if the numbers are equal.
*/
bool Equal(int obs, int exp)
{
   bool equal = obs == exp;
   if(!equal)
   {
      LOG("Test", pERROR) << "Test failed: Expected " << exp << ". Found " <<
         obs << ".";
   }
   return equal;
}

/**
   Performs basic configuration.

   The environment is set to dune and the set of mandatory and optional command
   line arguments is loaded. Message thresholds are set.

   \param argc The number of command line arguments.
   \param argv The command line arguments.
   \param arg  An object to populate with the command line arguments as key
      value pairs.
*/
void Configure(int argc, char** argv, CmdLnArgList& arg)
{
   Env::Instance()->AutoSet("dune");
   arg.Read(argc, argv, "$VALOR_DUNE/config/apps/run_tests.arg"
         ":$VALOR_DUNE/config/apps/seeds.arg");
   Messenger::Instance()->Configure(arg.GetString("mesg-thresholds"));
}

/**
   Unit tests for KBCubHcmbMondrian::Contract.

   Checks that a known Mondrian binning of [Ereco,Yreco] contracted to [Ereco]
   produces the expected result.

   \param arg The set of command line arguments specified.
   \return True if all tests pass, fale otherwise.
*/
bool TestMondrianContraction(CmdLnArgList& arg)
{
   // Retrieve the location of the Mondrian XML file
   std::string filename = arg.GetString("reco-binning-file");
   KBCubHcmbMondrian binning;
   binning.Read(filename);

   bool passed = true;

   KBCubHcmbMondrian* newBinning = binning.Contract(conv::kspEreco);

   // This is not quite right yet, contraction can produce overlapping bins,
   // need to think about how to handle this
   // May be easiest to just run through the edges, and add them to an ordered
   // set and reconstruct the bins from that
   passed = passed && Equal(newBinning->NBins(), 5);

   // Check bin edges
   passed = passed && Equal(newBinning->BinMinimum(0, 0), 0.0) &&
      Equal(newBinning->BinMaximum(0, 0), 40.0);
   passed = passed && Equal(newBinning->BinMinimum(1, 0), 40.0) &&
      Equal(newBinning->BinMaximum(1, 0), 150.0);
   passed = passed && Equal(newBinning->BinMinimum(2, 0), 40.0) &&
      Equal(newBinning->BinMaximum(2, 0), 180.0);
   passed = passed && Equal(newBinning->BinMinimum(3, 0), 150.0) &&
      Equal(newBinning->BinMaximum(3, 0), 200.0);
   passed = passed && Equal(newBinning->BinMinimum(4, 0), 180.0) &&
      Equal(newBinning->BinMaximum(4, 0), 200.0);

   // Check minima and maxima
   passed = passed && Equal(newBinning->Minimum(0), 0.0);
   passed = passed && Equal(newBinning->Maximum(0), 200.0);

   delete newBinning;

   return passed;
}

/**
   Unit tests for KBCubHcmbEdge2Edge::Contract.

   Checks that a known Edge2Edge binning of [Ereco,Yreco] contracted to [Ereco]
   and [Yreco] produces the expected results.

   \param arg The set of command line arguments specified.
   \return True if all tests pass, fale otherwise.
*/
bool TestEdge2EdgeContraction(CmdLnArgList& arg)
{
   std::string filename = arg.GetString("binning-file");
   SingleSampleKineBinning binning(conv::kdDUNEFD1ph, conv::kbLBNF_FHC,
        conv::ksNuMuCC);
   binning.Read(filename);

   KBCubHcmbEdge2Edge& recoBinning = (*binning.RecoSmpBinning());

   bool passed = true;

   // Ereco
   KBCubHcmbEdge2Edge* newBinning = recoBinning.Contract(conv::kspEreco);

   passed = passed && Equal(newBinning->NBins(), 4);

   // Check bin edges
   passed = passed && Equal(newBinning->BinMinimum(0, 0), 0.0) &&
      Equal(newBinning->BinMaximum(0, 0), 50.0);
   passed = passed && Equal(newBinning->BinMinimum(1, 0), 50.0) &&
      Equal(newBinning->BinMaximum(1, 0), 100.0);
   passed = passed && Equal(newBinning->BinMinimum(2, 0), 100.0) &&
      Equal(newBinning->BinMaximum(2, 0), 150.0);
   passed = passed && Equal(newBinning->BinMinimum(3, 0), 150.0) &&
      Equal(newBinning->BinMaximum(3, 0), 200.0);

   // Check minima and maxima
   passed = passed && Equal(newBinning->Minimum(0), 0.0);
   passed = passed && Equal(newBinning->Maximum(0), 200.0);

   delete newBinning;

   // Yreco
   newBinning = recoBinning.Contract(conv::kspYreco);

   passed = passed && Equal(newBinning->NBins(), 3);

   // Check bin edges
   passed = passed && Equal(newBinning->BinMinimum(0, 0), 0.0) &&
      Equal(newBinning->BinMaximum(0, 0), 1.0 / 3.0);
   passed = passed && Equal(newBinning->BinMinimum(1, 0), 1.0 / 3.0) &&
      Equal(newBinning->BinMaximum(1, 0), 2.0 / 3.0);
   passed = passed && Equal(newBinning->BinMinimum(2, 0), 2.0 / 3.0) &&
      Equal(newBinning->BinMaximum(2, 0), 1.0);

   // Check minima and maxima
   passed = passed && Equal(newBinning->Minimum(0), 0.0);
   passed = passed && Equal(newBinning->Maximum(0), 1.0);

   return passed;
}

/**
   Unit tests for production of plotting histograms.

   Checks that a known binning of [Ereco,Yreco, Etrue] produces an [Ereco,Yreco]
   ROOT compatible plot.

   \param arg The set of command line arguments specified.
   \return True if all tests pass, fale otherwise.
*/
bool TestOptimisedPlot(CmdLnArgList& arg)
{
   // Retrieve the location of the true and reco binning XML files
   std::string filename = arg.GetString("binning-file");
   SingleSampleKineBinning binning(conv::kdDUNEFD1ph, conv::kbLBNF_FHC,
        conv::ksNuMuCC);
   std::vector<KineVar_t> ks = util::KineVar(conv::kspErecoYreco);
   binning.Read(filename);

   KBCubHcmbMondrian& recoBinning = (*binning.RecoOptBinning());
   KBCubHcmbEdge2Edge& trueBinning = (*binning.TrueSmpBinning(0));
   VALORArray v(recoBinning.NBins(), trueBinning.NBins());

   for(int i = 0; i < recoBinning.NBins(); ++i)
   {
      for(unsigned int j = 0; j < trueBinning.NBins(); ++j)
      {
         v.SetEntry(j * 10 + (i + 1), i, j);
      }
   }

   TH2D* histo = util::UtlBinning::Make2DOptimisedHistogram(v, binning, ks);

   bool passed = true;

   // Bin 0 in Mondrian contains 105, so bins (1, 1) to (1, 5) should be 105
   passed = passed && Equal(histo->GetBinContent(1, 1), 105.0);
   passed = passed && Equal(histo->GetBinContent(1, 5), 105.0);

   // Bin 4 in Mondrian contains 125, so bins (2, 8) to (3, 8) should be 125
   passed = passed && Equal(histo->GetBinContent(2, 8), 125.0);
   passed = passed && Equal(histo->GetBinContent(3, 8), 125.0);

   // Bin 6 in Mondrian contains 135, so bins (3, 1) to (4, 1) should be 135
   passed = passed && Equal(histo->GetBinContent(3, 1), 135.0);
   passed = passed && Equal(histo->GetBinContent(4, 1), 135.0);

   // Bin 11 in Mondrian contains 160, so bins (4, 8) to (4, 9) should be 160
   passed = passed && Equal(histo->GetBinContent(4, 8), 160.0);
   passed = passed && Equal(histo->GetBinContent(4, 9), 160.0);

   delete histo;

   return passed;
}

/**
   Unit tests for production of plotting histograms.

   Checks that a known binning of [Ereco,Yreco, Etrue] produces an [Ereco,Yreco]
   ROOT compatible plot.

   \param arg The set of command line arguments specified.
   \return True if all tests pass, fale otherwise.
*/
bool TestSimple2DPlot(CmdLnArgList& arg)
{
   // Retrieve the location of the true and reco binning XML files
   std::string filename = arg.GetString("binning-file");
   SingleSampleKineBinning binning(conv::kdDUNEFD1ph, conv::kbLBNF_FHC,
        conv::ksNuMuCC);
   std::vector<KineVar_t> ks = util::KineVar(conv::kspErecoYreco);
   binning.Read(filename);

   KBCubHcmbEdge2Edge& recoBinning = (*binning.RecoSmpBinning());
   KBCubHcmbEdge2Edge& trueBinning = (*binning.TrueSmpBinning(0));
   VALORArray v(recoBinning.NBins(), trueBinning.NBins());

   for(unsigned int i = 0; i < recoBinning.NBins(); ++i)
   {
      for(unsigned int j = 0; j < trueBinning.NBins(); ++j)
      {
         v.SetEntry(j * 10 + (i + 1), i, j);
      }
   }

   TH2D* histo = util::UtlBinning::Make2DSimpleHistogram(v, binning, ks);

   bool passed = true;

   // Bin 0 in Edge2Edge contains 105, so bin (1, 1) should be 105
   passed = passed && Equal(histo->GetBinContent(1, 1), 105.0);

   // Bin 3 in Edge2Edge contains 120, so bin (4, 1) should be 120
   passed = passed && Equal(histo->GetBinContent(4, 1), 120.0);

   // Bin 8 in Edge2Edge contains 145, so bin (1, 3) should be 145
   passed = passed && Equal(histo->GetBinContent(1, 3), 145.0);

   // Bin 5 in Edge2Edge contains 130, so bin (2, 2) should be 130
   passed = passed && Equal(histo->GetBinContent(2, 2), 130.0);

   // Bin 11 in Edge2Edge contains 160, so bin (4, 3) should be 160
   passed = passed && Equal(histo->GetBinContent(4, 3), 160.0);

   delete histo;

   return passed;
}

/**
   Unit tests for production of plotting histograms.

   Checks that a known binning of [Ereco, Etrue] produces an [Ereco]
   ROOT compatible plot.

   \param arg The set of command line arguments specified.
   \return True if all tests pass, fale otherwise.
*/
bool TestSimple1DPlot(CmdLnArgList& arg)
{
   // Retrieve the location of the true and reco binning XML files
   std::string filename = arg.GetString("binning-file");
   SingleSampleKineBinning binning(conv::kdDUNEFD1ph, conv::kbLBNF_FHC,
        conv::ksNuMuCC);
   KineSpace_t ks = conv::kspEreco;
   binning.Read(filename);

   KBCubHcmbEdge2Edge& recoBinning = (*binning.RecoSmpBinning());
   KBCubHcmbEdge2Edge& trueBinning = (*binning.TrueSmpBinning(0));
   VALORArray v(recoBinning.NBins(), trueBinning.NBins());

   for(unsigned int i = 0; i < recoBinning.NBins(); ++i)
   {
      for(unsigned int j = 0; j < trueBinning.NBins(); ++j)
      {
         v.SetEntry(j * 10 + (i + 1), i, j);
      }
   }

   TH1D* histo = util::UtlBinning::Make1DHistogram(v, binning, ks);

   bool passed = true;

   // Bins 0, 4, 8 in Edge2Edge contains 375, so bin (1) should be 375
   passed = passed && Equal(histo->GetBinContent(1), 375.0);

   // Bin 1, 5, 9 in Edge2Edge contains 390, so bin (2) should be 390
   passed = passed && Equal(histo->GetBinContent(2), 390.0);

   // Bin 2, 6, 10 in Edge2Edge contains 405, so bin (3) should be 405
   passed = passed && Equal(histo->GetBinContent(3), 405.0);

   // Bin 3, 7, 11 in Edge2Edge contains 420, so bin (4) should be 420
   passed = passed && Equal(histo->GetBinContent(4), 420.0);

   delete histo;

   return passed;
}

/**
   Runs a set of unit tests.

   Currently the only test is of UtlEventRec::GetTrueKinematics. Eventually this
   will be partitioned into test classes and ideally make use of cppunit or
   similar.

   \param arg The command line arguments specified.
*/
void Tests(CmdLnArgList& arg)
{
   testing::TestSuite suite(arg);
   int failed = 0;
   int tests = 0;

   suite.Add("UtlTest", new testing::UtlTest);

   if(TestMondrianContraction(arg))
   {
      ++tests;
      LOG("Test", pINFO) << "TestMondrianContraction passed.";
   }
   else
   {
      ++tests;
      ++failed;
      LOG("Test", pINFO) << "TestMondrianContraction failed.";
   }

   if(TestEdge2EdgeContraction(arg))
   {
      ++tests;
      LOG("Test", pINFO) << "TestEdge2EdgeContraction passed.";
   }
   else
   {
      ++tests;
      ++failed;
      LOG("Test", pINFO) << "TestEdge2EdgeContraction failed.";
   }

   if(TestOptimisedPlot(arg))
   {
      ++tests;
      LOG("Test", pINFO) << "TestOptimisedPlot passed.";
   }
   else
   {
      ++tests;
      ++failed;
      LOG("Test", pINFO) << "TestOptimisedPlot failed.";
   }

   if(TestSimple2DPlot(arg))
   {
      ++tests;
      LOG("Test", pINFO) << "TestSimple2DPlot passed.";
   }
   else
   {
      ++tests;
      ++failed;
      LOG("Test", pINFO) << "TestSimple2DPlot failed.";
   }

   if(TestSimple1DPlot(arg))
   {
      ++tests;
      LOG("Test", pINFO) << "TestSimple1DPlot passed.";
   }
   else
   {
      ++tests;
      ++failed;
      LOG("Test", pINFO) << "TestSimple1DPlot failed.";
   }

   suite.Add("PhysParamsTest", new testing::PhysParamsTest);
   suite.Run();
}

int main(int argc, char** argv)
{
   CmdLnArgList arg;
   Configure(argc, argv, arg);
   Tests(arg);
  
   return 0;
}
