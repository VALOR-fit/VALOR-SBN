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
#include "valor/Messenger/Messenger.h"
#include "valor/CmdLine/CmdLnArgList.h"
#include "valor/Utilities/Env.h"
#include "valor/Testing/MondrianKBTest.h"
#include "valor/Testing/PhysParamsTest.h"
#include "valor/Testing/TestSuite.h"

// dune
#include "dune/Testing/CubicEdge2EdgeKBTest.h"
#include "dune/Testing/UtlBinningTest.h"
#include "dune/Testing/UtlTest.h"

// genie
#include "Conventions/GBuild.h"
#include "Ntuple/NtpMCEventRecord.h"
#include "EVGCore/EventRecord.h"

// Root
#include <TFile.h>
#include <TTree.h>


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
   arg.Read(argc, argv, "$VALOR_DUNE/config/apps/run_tests.arg"
         ":$VALOR_DUNE/config/apps/seeds.arg");
   Messenger::Instance()->Configure(arg.GetString("mesg-thresholds"));

   // This block of code is here only to ensure that the GENIE banner doesn't
   // interfere with the test result output by invoking GENIE early.
   std::string filename = arg.GetString("mc-events-file");
   TFile file(filename.c_str(), "READ");
   TTree* tree = dynamic_cast<TTree*>(file.Get("gtree"));
   genie::NtpMCEventRecord* mcrec = nullptr;
   for(Long64_t i = 0; i < tree->GetEntries(); ++i)
   {
      tree->GetEntry(i);
      genie::EventRecord& event = *(mcrec->event);
   }
   delete tree;
}

/**
   Runs a set of unit tests.

   \param arg The command line arguments specified.
*/
void Tests(CmdLnArgList& arg)
{
   testing::TestSuite suite(arg);

   suite.Add("UtlTest", new testing::UtlTest);
   suite.Add("MondrianKBTest", new testing::MondrianKBTest);
   suite.Add("CubicEdge2EdgeKBTest", new testing::CubicEdge2EdgeKBTest);
   suite.Add("UtlBinningTest", new testing::UtlBinningTest);
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
