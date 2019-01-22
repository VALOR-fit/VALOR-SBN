//____________________________________________________________________________
/*!

\app       valor_dune-run_fit_marg

\brief     Fit a set of marginalisation toys.

\options     --tag                 : Tag for input marginalisation toy file [def: "margtoy"]
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

\created   January 14, 2019

\copyright (c) 2010-2019, The VALOR Fitting Group, All Rights Reserved

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

using namespace valor;
using namespace valor::conv;
//using namespace valor::marginalisation;

void Fit(CmdLnArgList& arg);
void Init(CmdLnArgList& arg);

int main(int argc, char** argv)
{
   Env::Instance()->AutoSet("dune");
   CmdLnArgList arg;
   arg.Read(argc,argv,
      "$VALOR_DUNE/config/apps/run_fit_marg.arg"
      ":$VALOR_DUNE/config/apps/seeds.arg");
   LOG("valor_dune", pNOTICE) << arg;  
   Fit(arg);
   LOG("valor_dune", pNOTICE) << "Finished";
  
   return 0;
}

void Fit(CmdLnArgList& arg)
{
   Init(arg);

   // Get arguments
   string fpl_name = arg.GetString("fit-param-list");
   string param_val_opts = arg.GetString("param-values-option");
   string fitter_name = arg.GetString("fitter");
   bool with_stat_fluct = arg.GetBool("with-stat-fluct");
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

   // Initialize non delta M squared oscillation parameters to zero
   util::oscillation::SetUnoscillated(*fpl);

   FitDataABC* data = elements->FitData();
   // Call Generate - forces a call to Book as well as providing the fake data
   data->Generate(model, *fpl, with_stat_fluct);

   // Get the requested batch number and number of marginalisation toys for the
   // batch
   int batch = arg.GetInt("batch");
   int Ntoys = arg.GetInt("nmargtoy");

   // Setup the stream to read this batch of marginalisation toys
   std::ifstream is_toys("temporary.bin", std::ios::binary | std::ios::in);

   TStopwatch clock;
   clock.Start();
   for(int t = 0; t < Ntoys; ++t)
   {
      // Read a toy-MC experiment 
      LOG("valor_dune", pDEBUG) << "Reading toy-MC data";
      //data->Read(is_toys, "+SB");
      model->Read(is_toys, "pdft+SB");

      LOG("valor_dune", pNOTICE) << "Stat(" << t << "): " << data->GetFitStatistic(model, "likelihood-ratio");

/*      // Temp test
      model->ResetSystematics("all");
      // Randomise the systematics in the model
      if (param_val_opts.find("randomize") != std::string::npos)
      {
         model->RandomizeSystematics(param_val_opts.c_str());
      }

      PhysParamList tweaks = model->Tweaks();
      fpl->FromPhysParamList(tweaks,"current silent");
      // End temp test*/

//      FitInputs fit_inputs(data, model, fpl);
//      FitterABC* fitter = util::GetFitter(&fit_inputs, fitter_name.c_str());
//      LOG("valor_dune", pNOTICE) << "Stat(" << t << "): " << fit_inputs.Statistic();
   }
   clock.Stop();

   is_toys.close();
    
   LOG("valor_dune", pNOTICE) << "Read batch " << batch << ": " << Ntoys <<
      " spectra. Real time: " << clock.RealTime() << "   CPU time: " <<
      clock.CpuTime();
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

