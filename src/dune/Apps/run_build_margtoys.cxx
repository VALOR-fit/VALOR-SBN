//____________________________________________________________________________
/*!

\app       valor_dune-run_build_margtoys

\brief     Generate marginalisation toys.

\options     --tag                 : Tag for output file [def: "margtoy"]
             --run                 : Run # [def: 0]
             --nmargtoy            : Number of marginalisation toys [def: 1]
             --fit-param-list      : Fit parameter list (see FitParam.cxx) 
                                     [def: "standard"]
             --param-values-option : Decide how to set the values of physics 
                                     params used for toy-MC generation 
                                    [def:"randomize-all;prefit-errors"]
             --config              : Analysis configuration file [required]
             --mesg-thresholds     : Message thresholds [def: "verbosity.xml"]
            [--with-stat-fluct |   : Include statistical fluctuation in toy 
                                     MC generation? [def: yes]
             --without-stat-fluct] 
            [--store-spectra   |   : Store toy-MC/best-fit spectra? [def: no]
             --discard-spectra   ] 
             --n-sigma-limit       : The limit to apply to systematic parameter
                                     throws

\author    Andy Chappell <A.Chappell \at warwick.ac.uk>
           University of Warwick

\created   October 10, 2018

\copyright (c) 2010-2018, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

// root
#include "TFile.h"
#include "TSystem.h"
#include "TObjArray.h"
#include "TString.h"
#include "TVirtualFitter.h"
#include "TMath.h"
#include "TStopwatch.h"

#include "cmath"
#include "fstream"      // std::ofstream

// fmwk
#include "valor/CmdLine/CmdLnArgList.h"

#include "valor/Conventions/KineSpace.h"
#include "valor/FitCore/PhysParamList.h"
#include "valor/FitCore/FitParamList.h"
#include "valor/FitCore/FitModelABC.h"
#include "valor/FitCore/FitDataABC.h"
#include "valor/FitCore/FitInputs.h"
#include "valor/FitCore/FitterABC.h"
#include "valor/FitCore/UtlFit.h"
#include "valor/Utilities/UtlStyle.h"
#include "valor/Utilities/UtlStr.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Utilities/Rnd.h"
#include "valor/Utilities/Env.h"
#include "valor/Messenger/Messenger.h"
#include "valor/Ntuple/StdFitNtp.h"
//#include "valor/Marginalisation/MCMarginaliser.h"
//#include "valor/FitCore/LikelihoodABC.h"
//#include "valor/Marginalisation/MarginalLikelihood.h"
// dune
#include "dune/Conventions/FitParam.h"
#include "dune/Conventions/OscParams.h"
#include "dune/Conventions/PhysicalParameterLimits.h"
#include "dune/Elements/CompoundFitElements.h"

#include "valor/FitCore/CompoundFitData.h"
#include "valor/FitCore/CompoundFitModel.h"
#include "valor/Conventions/Opt.h"

#include "dune/Utilities/UtlOscillation.h"
#include "dune/Utilities/Marginalisation.h"

using namespace valor;
using namespace valor::conv;
//using namespace valor::marginalisation;

void BuildToys(CmdLnArgList& arg);
void Init(CmdLnArgList& arg);

int main(int argc, char** argv)
{
   Env::Instance()->AutoSet("dune");
   CmdLnArgList arg;
   arg.Read(argc,argv,
      "$VALOR_DUNE/config/apps/run_build_margtoys.arg"
      ":$VALOR_DUNE/config/apps/seeds.arg");
   LOG("valor_dune", pNOTICE) << arg;  
   BuildToys(arg);
   LOG("valor_dune", pNOTICE) << "Finished";
  
   return 0;
}

void BuildToys(CmdLnArgList& arg)
{
   Init(arg);

   // Get arguments
   string fpl_name = arg.GetString("fit-param-list");
   string param_val_opts = arg.GetString("param-values-option");
   bool rethrow_unphysical = arg.GetBool("rethrow-unphysical");

   CompoundFitElements * elements = new CompoundFitElements();
   elements->Read(arg.GetString("config"), "nosplines");
   FitModelABC* model = elements->FitModel();

   // GetSystematics will be added to CorrelatedSystematics in the future
   CorrelatedSystematics* systematics =
      dynamic_cast<CompoundFitModel*>(model)->GetSystematics();
   FitParamList* fpl = util::GetFitParameterList(fpl_name.c_str(), systematics);
   // Set the priors
   util::oscillation::SetOscillationParameterPriors(arg, *fpl);
   // Fix or set marginalisation flag for oscillation parameters
   util::oscillation::SetOscillationParameters(arg, *fpl);
   // Test of oscillation parameter throwing
   // ThrowOscillationParameters(*fpl);

   // Initialize non delta M squared oscillation parameters to zero
   util::oscillation::SetUnoscillated(*fpl);

   // Get the requested batch number and number of marginalisation toys for the
   // batch
   int batch = arg.GetInt("batch");
   int Ntoys = arg.GetInt("nmargtoy");

   TStopwatch clock;
   clock.Start();
   Marginalisation marginalisation(*elements, "temporary");
   marginalisation.BuildToys(batch, Ntoys, *fpl);
   clock.Stop();

   LOG("valor_dune", pNOTICE) << "Generate batch " << batch << ": " << Ntoys <<
      " spectra. Real time: " << clock.RealTime() << "   CPU time: " <<
      clock.CpuTime();
   // The toy-MC was generated using the `current' values of the input parameter list.
   // These values will be overwritten during the fit.
   // Copy those values now so as to save them later in the output tree.
   // ntp.TrueParamArr()->Append(true_params);
}

void Init(CmdLnArgList& arg)
{
   Messenger::Instance()->Configure(arg.GetString("mesg-thresholds"));

   Opt::Instance()->gMassHierarchyAssumed = util::HierarchyFromString("normal");
   Opt::Instance()->gOscDmsqScheme = util::DmsqSchemeFromString("abs23");
   Opt::Instance()->gOscMixingParamChoice = util::MixingTypeFromString(
         "sinsqtheta");
   Opt::Instance()->gOscOctantChoice = util::OctantFromString("one");

   // Set DUNE param names inside framework
   util::PopulateNameRegistry();

   util::InitializeOAPriors();

   Rnd::Instance()->SetSeeds(arg);
}

