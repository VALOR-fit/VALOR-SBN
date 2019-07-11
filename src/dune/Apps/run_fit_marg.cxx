//____________________________________________________________________________
/*!

\app       valor_dune-run_fit_marg

\brief     Fit a set of marginalisation toys.

\options     --tag                 : Tag for input marginalisation toy file [def: "margtoy"]
             --run                 : Run # [def: 0]
             --nmargtoy            : Number of marginalisation toys [def: 1]
             --fit-param-list      : Fit parameter list (see UtlParam.cxx)
                                     [def: "nuosc3f"]
             --fit-param-opt       : Options used when setting up the FitParamList
                                     [def: "NONE"]
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
#include "valor/Utilities/NameRegistry.h"
#include "valor/Messenger/Messenger.h"
#include "valor/Ntuple/StdFitNtp.h"
//#include "valor/Marginalisation/MCMarginaliser.h"
//#include "valor/FitCore/LikelihoodABC.h"
//#include "valor/Marginalisation/MarginalLikelihood.h"
// dune
#include "dune/Utilities/UtlParam.h"
#include "dune/Conventions/OscParamValues.h"
#include "dune/Conventions/PhysicalParameterLimits.h"
#include "dune/Elements/CompoundFitElements.h"

#include "valor/FitCore/CompoundFitData.h"
#include "valor/FitCore/CompoundFitModel.h"
#include "valor/Conventions/Opt.h"

#include "dune/Utilities/Marginalisation.h"
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
   string fpl_name         = arg.GetString("fit-param-list");
   string fplopt           = arg.GetString("fit-param-opt");
   string param_val_opts   = arg.GetString("param-values-option");
   string fitter_name      = arg.GetString("fitter");
   bool with_stat_fluct    = arg.GetBool("with-stat-fluct");
   bool rethrow_unphysical = arg.GetBool("rethrow-unphysical");

   string fp1_name         = arg.GetString("fit-param1");
   const double fp1_val    = arg.GetDouble("fit-param1-value");
   const int fp1_bin       = arg.GetInt("fit-param1-bin");
   const double fp1_minval = arg.GetDouble("fit-param1-min-value");
   const double fp1_maxval = arg.GetDouble("fit-param1-max-value");
   const int fp1_nbins     = arg.GetInt("fit-param1-nbins");

   string fp2_name;
   double fp2_val = 0.0;
   int fp2_bin = 0;
   double fp2_minval = 0.0;
   double fp2_maxval = 0.0;
   int fp2_nbins = 0;

   LOG("valor_dune", pNOTICE) << "Fit parameter " << fp1_name << "(" <<
      fp1_bin << ") = " << fp1_val << " [" << fp1_nbins << ": " << fp1_minval <<
      ", " << fp1_maxval << "]";

   if(arg.Exists("fit-param2"))
   {
      fp2_name   = arg.GetString("fit-param2");
      fp2_val    = arg.GetDouble("fit-param2-value");
      fp2_bin    = arg.GetInt("fit-param2-bin");
      fp2_minval = arg.GetDouble("fit-param2-min-value");
      fp2_maxval = arg.GetDouble("fit-param2-max-value");
      fp2_nbins  = arg.GetInt("fit-param2-nbins");
      LOG("valor_dune", pNOTICE) << "Fit parameter " << fp2_name << "(" <<
         fp2_bin << ") = " << fp2_val << " [" << fp2_nbins << ": " <<
         fp2_minval << ", " << fp2_maxval << "]";
   }

   CompoundFitElements* elements = new CompoundFitElements();
   elements->Read(arg.GetString("config"));
   FitModelABC* model = elements->FitModel();

   // GetSystematics will be added to CorrelatedSystematics in the future
   CorrelatedSystematics* systematics =
      dynamic_cast<CompoundFitModel*>(model)->GetSystematics();
   FitParamList* fpl = util::GetFitParameterList(fpl_name.c_str(), fplopt.c_str(), systematics);

   // Set the priors
   util::oscillation::SetOscillationParameterPriors(arg, *fpl);
   // Fix or set marginalisation flag for oscillation parameters
   util::oscillation::SetOscillationParameters(arg, *fpl);
   // Overwrite the free parameters with fixed values for the fake data
   // TODO: This shouldn't be hard-coded, we need an option to read in a data file too.
   valor::conv::PhysParamId_t p = util::NameRegistry::Instance()->PhysParamFromString("cpv");
   fpl->Update(p, -1.570796327);
   fpl->SetInitValue(p, -1.570796327);
   p = util::NameRegistry::Instance()->PhysParamFromString("mixing23");
   fpl->Update(p, 0.53);
   fpl->SetInitValue(p, 0.53);

   // Initialize non delta M squared oscillation parameters to zero
   // util::oscillation::SetUnoscillated(*fpl);
   LOG("valor_dune", pNOTICE) << *fpl;

   FitDataABC* data = elements->FitData();
   // Call Generate - forces a call to Book as well as providing the fake data
   data->Generate(model, *fpl, with_stat_fluct);

   // Get the requested batch number and number of marginalisation toys for the
   // batch
   int Nbatches = arg.GetInt("nbatches");
   int firstBatch = arg.GetInt("first-batch");
   int Ntoys = arg.GetInt("nmargtoy");

   TStopwatch clock;
   clock.Start();
   Marginalisation marginalisation(*elements, arg.GetString("margtoy-tag"));
   if(!arg.Exists("fit-param2"))
   {  // Initialise for 1D fit
      marginalisation.InitFit(fp1_nbins, fp1_minval, fp1_maxval);
   }
   else
   {  // Initalise for 2D fit
      marginalisation.InitFit(fp1_nbins, fp1_minval, fp1_maxval, fp2_nbins,
            fp2_minval, fp2_maxval);
   }
   FitResult* result = nullptr;
   // Perform a fit and populate the entire chi2 and likelihood surfaces
   // This version of the fit works for both 1D and 2D
   result = marginalisation.Fit(data, Ntoys, Nbatches, firstBatch);
   // Perform an optimised fit starting at the specified value
/*   if(!arg.Exists("fit-param2"))
   {
      result = marginalisation.Fit(fp1_val, data, Ntoys, Nbatches, firstBatch);
   }
   else
   {
      result = marginalisation.Fit(fp1_val, fp2_val, data, Ntoys, Nbatches,
            firstBatch);
   }*/

   if(!arg.Exists("fit-param2"))
   {
      LOG("valor_dune", pNOTICE) << "Best fit: cpv = " <<
         result->GetParam1BestFit() << " Chi^2 = " << result->GetChi2BestFit() <<
         " " << " L = " << result->GetLikelihoodBestFit();
   }
   else
   {
      LOG("valor_dune", pNOTICE) << "Best fit: cpv = " <<
         result->GetParam1BestFit() << " mixing23 = " <<
         result->GetParam2BestFit() << " Chi^2 = " << result->GetChi2BestFit() <<
         " " << " L = " << result->GetLikelihoodBestFit();
   }

   std::ostringstream oss;
   oss << arg.GetString("tag");
   oss << "_result.root";
   string filename = oss.str();
   TFile* fitFile = new TFile(filename.c_str(), "RECREATE");
   if(!arg.Exists("fit-param2"))
   {
      TH1D* chi2Surface = result->GetChi2Surface1D();
      TH1D* likelihoodSurface = result->GetLikelihoodSurface1D();
      chi2Surface->Write("chi2");
      likelihoodSurface->Write("likelihood");
   }
   else
   {
      TH2D* chi2Surface = result->GetChi2Surface2D();
      TH2D* likelihoodSurface = result->GetLikelihoodSurface2D();
      chi2Surface->Write("chi2");
      likelihoodSurface->Write("likelihood");
   }
   fitFile->Close();
   delete fitFile;

/*   marginalisation.ComputeStatistics(fp1_bin, data, Ntoys, Nbatches, firstBatch);
   double likelihood = marginalisation.GetLikelihood();
   double chi2 = marginalisation.GetChi2();
   LOG("valor_dune", pNOTICE) << "chi2(marg): " << chi2 << " L(marg): " <<
      likelihood;*/
   clock.Stop();

   LOG("valor_dune", pNOTICE) << "Read: " << Ntoys <<
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
   Opt::Instance()->gOscOctantChoice = util::OctantFromString("one");      // TODO: remember to set this to the 2nd octant for T2K

   util::InitializeOAPriors();      // TODO: this should be read from XML files

   Rnd::Instance()->SetSeeds(arg);
}

