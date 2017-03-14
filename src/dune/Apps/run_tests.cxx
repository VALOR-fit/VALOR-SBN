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

// dune
#include "dune/Testing/StandardTests.h"

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

int main(int argc, char** argv)
{
   CmdLnArgList arg;
   Configure(argc, argv, arg);
   return testing::BatchTests(arg);
}
