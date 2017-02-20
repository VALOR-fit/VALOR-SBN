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

// root
#include <TFile.h>
#include <TTree.h>

// genie
#include "Conventions/GBuild.h"
#include "EVGCore/EventRecord.h"
#include "Ntuple/NtpMCEventRecord.h"

// valor
#include "valor/Messenger/Messenger.h"
#include "valor/CmdLine/CmdLnArgList.h"
#include "valor/Utilities/Env.h"


// dune
#include "dune/GENIEUtilities/UtlEventRec.h"
#include "dune/Conventions/FitParam.h"

using namespace valor;
using namespace valor::conv;

/**
   Tests the equality of double-precision floating point numbers within a given
   arithmetic tolerance.

   \param a The first number to be compared.
   \param b The second number to be compared.
   \param tol The tolerance of the comparison. Default 1E-6.

   \return True if the numbers are equal within tolerance, false otherwise.
*/
bool Equal(double a, double b, double tol = 1E-6)
{
   return (abs(a - b) < tol);
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
   Unit tests for UtlEventRec::GetTrueKinematics.

   Compares kinematic variables retrieved from a GENIE vertex to a known set of
   kinematic variables.

   \param arg The set of command line arguments specified.
   \return True if all tests pass, fale otherwise.
*/
bool TestTrueKinematics(CmdLnArgList& arg)
{
   // Retrieve the location of the GENIE MC events
   std::string filename = arg.GetString("mc-events-file");
   TFile file(filename.c_str(), "READ");

   // Load the tree containing the events and specify the n-tuple to load events
   // into
   TTree* tree = dynamic_cast<TTree*>(file.Get("gtree"));
   genie::NtpMCEventRecord* mcrec = 0;
   tree->SetBranchAddress("gmcrec", &mcrec);

   // The expected truth values of E and Q2 - gntp.test.ghep.root
   double Eexp[10] = {0.577132, 0.701179, 4.43347, 0.564247, 0.456497,
      0.621421, 0.329308, 1.20505, 0.688733, 0.512196};
   double Q2exp[10] = {0.539777, 0.212278, 0.273801, 0.469212, 0.106599,
      0.484452, 0.151665, 0.157586, 0.184618, 0.364481};

   // Test retrieval of Etrue values
   bool passed = true;
   for(Long64_t i = 0; i < tree->GetEntries(); ++i)
   {
      tree->GetEntry(i);
      genie::EventRecord& event = *(mcrec->event);

      conv::KineSpace_t kv = conv::kspEtrue;
      std::vector<double> vals = valor::util::GetTrueKinematics(&event, kv);
      
      passed = passed && vals.size() == 1;
      if(!passed)
      {
         LOG("Test", pERROR) << "Test failed: Expected 1 kinematic variable"
            " Etrue. Found " << vals.size() << ".";
         return passed;
      }
      
      passed = passed && Equal(Eexp[i], vals[0]);
      if(!passed)
      {
         LOG("Test", pERROR) << "Test failed: Expected Etrue = " << Eexp[i] <<
            ". Found " << vals[0] << ". ";
         return passed;
      }
   }

   // Test retrieval of Etrue and Q2true values
   for(Long64_t i = 0; i < tree->GetEntries(); ++i)
   {
      tree->GetEntry(i);
      genie::EventRecord& event = *(mcrec->event);

      conv::KineSpace_t kv = conv::kspEtrueQ2true;
      std::vector<double> vals = valor::util::GetTrueKinematics(&event, kv);

      passed = passed && vals.size() == 2;
      if(!passed)
      {
         LOG("Test", pERROR) << "Test failed: Expected 2 kinematic variables"
            " Etrue, Q2. Found " << vals.size() << ".";
         return passed;
      }
      
      passed = passed && Equal(Eexp[i], vals[0]);
      if(!passed)
      {
         LOG("Test", pERROR) << "Test failed: Expected Etrue = " << Eexp[i] <<
            ". Found " << vals[0] << ".";
         return passed;
      }

      passed = passed && Equal(Q2exp[i], vals[1]);
      if(!passed)
      {
         LOG("Test", pERROR) << "Test failed: Expected Q2true = " << Q2exp[i] <<
            ". Found " << vals[1] << ".";
         return passed;
      }

      mcrec->Clear();
   }

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
   int failed = 0;
   int tests = 0;
   if(TestTrueKinematics(arg))
   {
      ++tests;
      LOG("Test", pINFO) << "TestTrueKinematics passed.";
   }
   else
   {
      ++tests;
      ++failed;
      LOG("Test", pINFO) << "TestTrueKinematics failed.";
   }

   if(!failed)
   {
      LOG("Test", pINFO) << "All tests passed.";
   }
   else
   {
      LOG("Test", pINFO) << failed << " of " << tests << " tests failed.";
   }
}

int main(int argc, char** argv)
{
   CmdLnArgList arg;
   Configure(argc, argv, arg);
   Tests(arg);
  
   return 0;
}
