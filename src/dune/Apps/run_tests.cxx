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

// valor
#include "valor/CmdLine/CmdLnArgList.h"
#include "valor/Utilities/Env.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Testing/MondrianKBTest.h"
#include "valor/Testing/PhysParamsTest.h"
#include "valor/Testing/TestSuite.h"

// dune
#include "dune/Testing/CubicEdge2EdgeKBTest.h"
#include "dune/Testing/UtlBinningTest.h"
#include "dune/Testing/UtlTest.h"

// genie
#include "Messenger/Messenger.h"

using namespace valor;

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
   std::string appArgs = util::CompleteConfigPath("apps/run_tests.arg");
   std::string seedArgs = util::CompleteConfigPath("apps/seeds.arg");
   arg.Read(argc, argv, (appArgs + ":" + seedArgs).c_str());

   std::string thresholds = util::CompleteConfigPath(arg.GetString(
            "mesg-thresholds"));
   genie::Messenger::Instance()->SetPrioritiesFromXmlFile(thresholds);
}

/**
   Runs a set of unit tests, returning the result.

   \param arg The command line arguments specified.
   \return The pass/failure status of the tests.
*/
bool Tests(CmdLnArgList& arg)
{
   testing::TestSuite suite(arg);

   suite.Add("UtlTest", new testing::UtlTest);
   suite.Add("MondrianKBTest", new testing::MondrianKBTest);
   suite.Add("CubicEdge2EdgeKBTest", new testing::CubicEdge2EdgeKBTest);
   suite.Add("UtlBinningTest", new testing::UtlBinningTest);
   suite.Add("PhysParamsTest", new testing::PhysParamsTest);

   return suite.Run();
}

int main(int argc, char** argv)
{

   CmdLnArgList arg;
   Configure(argc, argv, arg);
   return Tests(arg);
}
