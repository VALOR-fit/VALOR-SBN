/*!

\app       valor_dune-batch_tests

\brief     Unit testing for the overnight build.

\options     --mc-events-file   : The file containing the GENIE events [required]
             --mesg-thresholds  : Message thresholds [def: "verbosity.xml"]

\author    Andy Chappell <A.Chappell \at warwick.ac.uk>
           University of Warwick

\created   February 20, 2017

\copyright (c) 2010-2017, The VALOR Fitting Group, All Rights Reserved

*/

#include <string>
#include <vector>

// valor
#include "valor/CmdLine/CmdLnArgList.h"
#include "valor/Utilities/Env.h"
#include "valor/Utilities/UtlFile.h"
#include "valor/Utilities/UtlSystem.h"

// dune
#include "dune/Testing/StandardTests.h"

// genie
#include "Messenger/Messenger.h"

using namespace valor;

/**
   Produces a mock set of command line arguments so nothing needs to be
   specified for the overnight build unit tests.

   \return A vector of command line arguments
*/
std::vector<std::string> BatchArgs()
{
   std::vector<std::string> args;
   args.push_back("valor_dune-batch_tests");
   args.push_back("--mc-events-file");
   args.push_back(util::file::GetDataFilename("test/gntp.test.ghep.root"));
   args.push_back("--reco-binning-file");
   args.push_back(util::file::GetDataFilename("test/reco_optimised_binning.xml"));
   args.push_back("--true-binning-file");
   args.push_back(util::file::GetDataFilename("test/true_binning.xml"));
   args.push_back("--binning-file");
   args.push_back(util::file::GetDataFilename("test/binning.xml"));
   args.push_back("--params-sel-file");
   args.push_back(util::CompleteConfigPath("dune_nd_fd_analysis_params.xml"));
   args.push_back("--params-spec-file");
   args.push_back(util::CompleteConfigPath("params_specification.xml"));

   return args;
}

/**
   Performs basic configuration.

   The environment is set to dune and the set of mandatory and optional command
   line arguments is loaded. Message thresholds are set.

   \param arg  An object to populate with the command line arguments as key
      value pairs.
*/
void Configure(CmdLnArgList& arg)
{
   Env::Instance()->AutoSet("dune");
   std::string appArgs = util::CompleteConfigPath("apps/run_tests.arg");
   std::string seedArgs = util::CompleteConfigPath("apps/seeds.arg");
   
   std::vector<string> args = BatchArgs();
   int argc = args.size();
   char* argv[argc];
   for(unsigned int i = 0; i < args.size(); ++i)
   {
      argv[i] = const_cast<char*>(args[i].c_str());
   }

   arg.Read(argc, argv, (appArgs + ":" + seedArgs).c_str());

   std::string thresholds = util::CompleteConfigPath(arg.GetString(
            "mesg-thresholds"));
   genie::Messenger::Instance()->SetPrioritiesFromXmlFile(thresholds);
}

int main()
{
   CmdLnArgList arg;
   Configure(arg);
   return (testing::BatchTests(arg) ? 0 : 1);
}
