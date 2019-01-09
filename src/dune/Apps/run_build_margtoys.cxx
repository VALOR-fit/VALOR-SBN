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

using namespace valor;
using namespace valor::conv;
//using namespace valor::marginalisation;

void BuildToys(CmdLnArgList& arg);
void Init(CmdLnArgList& arg);
void SetOscillationParameters(CmdLnArgList& arg, FitParamList& fpl);
void SetOscillationParameterPriors(CmdLnArgList& arg, FitParamList& fpl);
void ThrowOscillationParameters(FitParamList& fpl);
void SetUnoscillated(FitParamList& fpl);

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
   SetOscillationParameterPriors(arg, *fpl);
   // Fix or set marginalisation flag for oscillation parameters
   SetOscillationParameters(arg, *fpl);
   // Test of oscillation parameter throwing
   // ThrowOscillationParameters(*fpl);

   // Initialize non delta M squared oscillation parameters to zero
   SetUnoscillated(*fpl);

   // Get the requested batch number and number of marginalisation toys for the
   // batch
   int batch = arg.GetInt("batch");
   int Ntoys = arg.GetInt("nmargtoy");

   TStopwatch clock;
   clock.Start();
   for(int t = 0; t < Ntoys; ++t)
   {
      model->ResetSystematics("all");
      // Randomise the systematics in the model
      if (param_val_opts.find("randomize") != std::string::npos)
      {
         model->RandomizeSystematics(param_val_opts.c_str());
      }

      PhysParamList tweaks = model->Tweaks();
      fpl->FromPhysParamList(tweaks,"current silent");

      // Check parameter name, maybe rethrow
      if (!PhysicalParameterLimits::Instance()->AllWithinLimits(*fpl))
      {
         LOG("valor_dune", pDEBUG) << "At least one parameter thrown outside expected limits.";
         if (rethrow_unphysical)
         {
            LOG("valor_dune", pDEBUG) << "Regenerating (not really at the moment)...";
         }
      }
      PhysParamList true_params = fpl->AsPhysParamList("current");
       
      // Generate a toy-MC experiment 
      LOG("valor_dune", pDEBUG) << "Generating toy-MC data";
      LOG("valor_dune", pDEBUG) << "Toy-MC generation uses true parameters: " << true_params;
      FitDataABC* data = elements->FitData();
      data->Generate(model, *fpl, with_stat_fluct);
   }
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

void SetOscillationParameters(CmdLnArgList& arg, FitParamList& fpl)
{
   string osc_parameters[7] = { "mixing12", "mixing13", "mixing23", "dm23sq",
      "dm12sq", "dm13sq", "cpv" };

   for(int i = 0; i < 7; ++i)
   {
      valor::conv::PhysParamId_t p = util::PhysParamFromString(
            osc_parameters[i].c_str());
      if(fpl.Exists(p))
      {
         double fix_value = arg.GetDouble(TString::Format("fix-at-%s",
                  osc_parameters[i].c_str()).Data());
         double min_value = util::OscParamMinValue(p);
         double max_value = util::OscParamMaxValue(p);
         if(fix_value >= min_value && fix_value < max_value)
         {
            fpl.Update(p, fix_value);
            fpl.SetInitValue(p, fix_value);
            fpl.FixParameter(p);
         }
         else
         {
            fpl.SetDoMarg(p, true);
         }
      }
   }
}

void SetOscillationParameterPriors(CmdLnArgList& arg, FitParamList& fpl)
{
   // This should all be done from xml
   valor::conv::PhysParamId_t p = util::PhysParamFromString("mixing12");
   fpl.SetPriorMode(p, "gaus");
   fpl.SetMeanGaus(p, 0.307); fpl.SetSigmaGaus(p, 0.013);

   p = util::PhysParamFromString("dm12sq");
   fpl.SetPriorMode(p, "gaus");
   fpl.SetMeanGaus(p, 7.53e-5); fpl.SetSigmaGaus(p, 0.18e-5);

   p = util::PhysParamFromString("mixing13");
   fpl.SetPriorMode(p, "gaus");
   fpl.SetMeanGaus(p, 2.12e-3); fpl.SetSigmaGaus(p, 0.8e-3);

   p = util::PhysParamFromString("mixing23");
   fpl.SetPriorMode(p, "flat");
   fpl.SetMinValueFlat(p, 0.3); fpl.SetMaxValueFlat(p, 0.7);

   p = util::PhysParamFromString("dm23sq");
   fpl.SetPriorMode(p, "flat");
   fpl.SetMinValueFlat(p, 2.3e-3); fpl.SetMaxValueFlat(p, 2.7e-3);

   p = util::PhysParamFromString("cpv");
   fpl.SetPriorMode(p, "flat");
   fpl.SetMinValueFlat(p, -3.14159265358979312); fpl.SetMaxValueFlat(p, +3.14159265358979312);
}

void ThrowOscillationParameters(FitParamList& fpl)
{
   string osc_parameters[7] = { "mixing12", "mixing13", "mixing23", "dm23sq",
      "dm12sq", "dm13sq", "cpv" };

   for(int i = 0; i < 7; ++i)
   {
      valor::conv::PhysParamId_t p = util::PhysParamFromString(
            osc_parameters[i].c_str());
      if(fpl.Exists(p) && fpl.IsMarginalized(p))
      {
         double value = util::GetRandomizedOscParam(p, fpl.GetPriorModeName(p));
         LOG("valor_dune", pDEBUG) << osc_parameters[i] << " " << fpl.GetPriorModeName(p) << " " << value;
         LOG("valor_dune", pDEBUG) << "I think GetRandomizedOscParam ignores the prior in the FPL";
         double min_value = util::OscParamMinValue(p);
         double max_value = util::OscParamMaxValue(p);
         if(value >= min_value && value < max_value)
         {
            fpl.Update(p, value);
            fpl.SetInitValue(p, value);
         }
         else
         {
            // Rethrow if not in physical range
            --i;
            continue;
         }
      }
   }
}

void SetUnoscillated(FitParamList& fpl)
{
   string osc_parameters[4] = { "mixing12", "mixing13", "mixing23", "cpv" };
   string dm_parameters[3] = {"dm23sq", "dm12sq", "dm13sq" };

   for(int i = 0; i < 4; ++i)
   {
      valor::conv::PhysParamId_t p = util::PhysParamFromString(
            osc_parameters[i].c_str());
      if(fpl.Exists(p))
      {
         fpl.Update(p, 0.0);
         fpl.SetInitValue(p, 0.0);
      }
   }

   for(int i = 0; i < 3; ++i)
   {
      valor::conv::PhysParamId_t p = util::PhysParamFromString(
            dm_parameters[i].c_str());
      if(fpl.Exists(p))
      {
         double value = fpl.InitValue(p);
         fpl.Update(p, value);
         fpl.SetInitValue(p, value);
      }
   }
}

