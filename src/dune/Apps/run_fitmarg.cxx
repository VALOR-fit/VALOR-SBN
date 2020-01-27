//____________________________________________________________________________
/*!

\app       valor_dune-run_nd_fitmarg

\brief     Generate and fit ensembles of toy-MC experiments.

\options     --tag                 : Tag for output file [def: "toymc"]
             --run                 : Run # [def: 0]
             --ntoymc              : Number of toy-MC experiments [def: 1]
             --fit-param-list      : Fit parameter list (see UtlParam.cxx)
                                     [def: "standard"]
             --param-values-option : Decide how to set the values of physics 
                                     params used for toy-MC generation 
                                    [def:"randomize-all;prefit-errors"]
             --fit-opt             : Fitter option [def: "minuit"]
             --config              : Analysis configuration file [required]
             --mesg-thresholds     : Message thresholds [def: "verbosity.xml"]
            [--with-stat-fluct |   : Include statistical fluctuation in toy 
                                     MC generation? [def: yes]
             --without-stat-fluct] 
            [--store-spectra   |   : Store toy-MC/best-fit spectra? [def: no]
             --discard-spectra   ] 

\author    Andy Chappell <A.Chappell \at warwick.ac.uk>
           University of Warwick

\created   July 28, 2016

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

// root
#include "TFile.h"
#include "TSystem.h"
#include "TObjArray.h"
#include "TString.h"
#include "TVirtualFitter.h"
#include "TMath.h"

#include "cmath"

// fmwk
#include "valor/CmdLine/CmdLnArgList.h"
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
#include "valor/Marginalisation/MCMarginaliser.h"
// dune

#include "dune/Utilities/UtlParam.h"
#include "dune/Conventions/PhysicalParameterLimits.h"
#include "valor/FitCore/CompoundFitElements.h"

#include "valor/FitCore/CompoundFitData.h"
#include "valor/FitCore/CompoundFitModel.h"
#include "valor/Conventions/Opt.h"

using namespace valor;
using namespace valor::conv;
using namespace valor::marginalisation;

void Validate(CmdLnArgList& arg);
void Fit(CmdLnArgList& arg);
PhysParamList* GetPhysParamList(const CmdLnArgList&);
void Fit1D(const CmdLnArgList&, FitInputs*, PhysParamId_t);
void Fit2D(const CmdLnArgList&, FitInputs*, PhysParamId_t, PhysParamId_t);
PhysParamId_t GetPhysParamId(const std::string&);
void SetPriors(FitParamList& fp, double nSigma);
void SetFlatPrior(FitParamList& fp, conv::PhysParamId_t p,
      double min, double max);
void SetGausPrior(FitParamList& fp, conv::PhysParamId_t p,
      double mean, double sigma, double nSigma);
void SetUserPrior(FitParamList& fp, conv::PhysParamId_t p, TH1D* h);
TVectorD CholeskyGenerateTruncatedParams(double sigma);
void NormalHierarchyOscillationParameters(FitParamList& fp,
      conv::PhysParamId_t param0, conv::PhysParamId_t param1);
void InvertedHierarchyOscillationParameters(FitParamList& fp,
      conv::PhysParamId_t param0, conv::PhysParamId_t param1);

int main(int argc, char** argv)
{
   
   CmdLnArgList arg;
   arg.Read(argc,argv,
      "$VALOR_EXPT/config/apps/run_fitmarg.arg"
      ":$VALOR_EXPT/config/apps/seeds.arg");
   LOG("valor_dune", pNOTICE) << arg;  
   Fit(arg);
   //Validate(arg);
  
   return 0;
}

void Fit(CmdLnArgList& arg)
{
   //   valor::util::PrintBanner(Env::Instance()->Banner(),500);
 
   Messenger::Instance()->Configure(arg.GetString("mesg-thresholds"));

   Opt::Instance()->gMassHierarchyAssumed = util::HierarchyFromString("normal");
   Opt::Instance()->gOscDmsqScheme = util::DmsqSchemeFromString("abs23");
   Opt::Instance()->gOscMixingParamChoice = util::MixingTypeFromString(
         "sinsq2theta");
   Opt::Instance()->gOscOctantChoice = util::OctantFromString("one");

   // Set the random seeds
   Rnd::Instance()->SetSeeds(arg);

   LOG("valor_dune", pNOTICE) << *Rnd::Instance();

   // Check if we have a PParm to read from file containing true values
   PhysParamList* trueValuesFromFile = GetPhysParamList(arg);

   // Create file and tree to store outputs
   /*
   TString outfilename = TString::Format("%s_%d.root",
      arg.GetString("tag").c_str(), arg.GetInt("run"));
   StdFitNtp ntp;
   ntp.Create(outfilename.Data(), "valor_dune_nd_ntp",
      "VALOR DUNE / ND-Fit n-tuple");
   */
  
   // Get model & configure
   LOG("valor_dune", pNOTICE) << "Getting and configuring the fit elements";
   CompoundFitElements * elements = new CompoundFitElements();
   elements->Read(arg.GetString("config"));
   FitDataABC* data = elements->FitData();
   FitModelABC* model = elements->FitModel();

   // Get the specified fit parameter list
//   FitParamList* fp = util::GetFitParameterList(
//      arg.GetString("fit-param-list").c_str());
   CorrelatedSystematics* syst =
      dynamic_cast<CompoundFitModel*>(model)->GetSystematics();
   int numOscParams = 6;
   FitParamList* fp = new FitParamList(syst->Size() + numOscParams);
   // These values will be adjusted for nuisance parameters in SetPriors
   fp->AddParam(0, conv::kPhypMixing23, 0, 0, 1, 0.0001);
   fp->AddParam(1, conv::kPhypMixing13, 0, 0, 1, 0.0001);
   fp->AddParam(2, conv::kPhypMixing12, 0, 0, 1, 0.0001);
   fp->AddParam(3, conv::kPhypCPV, 0, 0, 1, 0.0001);
   fp->AddParam(4, conv::kPhypDm23sq, 0, 0, 1, 0.0001);
   fp->AddParam(5, conv::kPhypDm12sq, 0, 0, 1, 0.0001);
   for(int i = 0; i < syst->Size(); ++i)
   {
      fp->AddParam(numOscParams + i, syst->Idx2Param(i), 1, 0, 2, 0.0001);
   }

   conv::PhysParamId_t param0 = MCMarginaliser::GetPhysParamId(arg.GetString(
            "fit-param-0"));
   conv::PhysParamId_t param1 = MCMarginaliser::GetPhysParamId(arg.GetString(
            "fit-param-1"));
   int numDimensions = (param1 == conv::kPhypUndefined) ? 1 : 2;
   for(int i = 0; i < fp->Size(); ++i)
   {
       conv::PhysParamId_t p = fp->WhichParam(i);
      if(p == param0 || (numDimensions == 2 && p == param1))
      {
         fp->SetNuisance(p, false);
         fp->FreeParameter(p);
      }
      else
      {
         fp->SetNuisance(p, true);
         fp->SetDoMarg(p, true);
         fp->FixParameter(p);
      }
  }

   // Restrict systematics to N sigma range
   bool rethrowUnphysical = arg.GetBool("rethrow-unphysical");
   if(rethrowUnphysical)
   {
      double nSigma = arg.GetDouble("n-sigma-limit");
      LOG("valor_dune", pNOTICE) << "Rethrowing to " << nSigma << "-sigma";
      syst->SetRethrowUnphysical(true);
      syst->SetNSigmaLimit(nSigma);
      for(int i = 0; i < syst->Size(); ++i)
      {
         conv::PhysParamId_t p = syst->Idx2Param(i);
         fp->SetMinValue(p, 1 - nSigma * syst->OneSigmaError(p));
         fp->SetMaxValue(p, 1 + nSigma * syst->OneSigmaError(p));
      }
   }

   // Set oscillation parameter priors
   SetPriors(*fp, arg.GetDouble("n-sigma-limit"));

   // Override prior for fit parameter to use full physical range
   SetFlatPrior(*fp, param0, 0.0, 1.0);
   // Set an initial value for fit parameter to generate fake data
   fp->SetInitValue(param0, 0.524);
   Rnd::Instance()->SetSeeds(arg);
   // Generate fake data
   data->Generate(model, *fp, false);

   // Fit/Marginalisation here
   LOG("valor_dune", pNOTICE) << "Preparing the fitter";
   MarginaliserABC* marginaliser = new MCMarginaliser(data, model, fp);
   marginaliser->Configure(arg);
   // Perform marginalisation
   LOG("valor_dune", pNOTICE) << "Retrieving marginaliser";
   marginaliser->Marginalise();
   LOG("Minuit", pNOTICE) << "Done marginalising";
  
   LOG("valor_dune", pNOTICE) << "Setting inputs";
   FitInputs* fitInputs = new FitInputs(data, model, fp, marginaliser);
   LOG("valor_dune", pNOTICE) << "Creating fitter";
   FitterABC* fitter = util::GetFitter(fitInputs,
         arg.GetString("fitter").c_str());
   LOG("valor_dune", pNOTICE) << "Fitting";
//   fitter->DoTheFit();

   // ntp.Save();

   delete marginaliser;
}

void Validate(CmdLnArgList& arg)
{
//   valor::util::PrintBanner(Env::Instance()->Banner(),500);
   Messenger::Instance()->Configure(arg.GetString("mesg-thresholds"));

   Opt::Instance()->gMassHierarchyAssumed = util::HierarchyFromString("normal");
   Opt::Instance()->gOscDmsqScheme = util::DmsqSchemeFromString("abs23");
   Opt::Instance()->gOscMixingParamChoice = util::MixingTypeFromString(
         "sinsq2theta");
   Opt::Instance()->gOscOctantChoice = util::OctantFromString("one");

   // Set the random seeds
   Rnd::Instance()->SetSeeds(arg);

   // Get model & configure
   LOG("valor_dune", pNOTICE) << "Getting and configuring the fit elements";
   CompoundFitElements * elements = new CompoundFitElements();
   elements->Read(arg.GetString("config"));
   FitDataABC* data = elements->FitData();
   FitModelABC* model = elements->FitModel();

   conv::PhysParamId_t param0 = conv::kPhypCPV;
   conv::PhysParamId_t param1 = conv::kPhypUndefined;

   // Get the specified fit parameter list
   CorrelatedSystematics* syst =
      dynamic_cast<CompoundFitModel*>(model)->GetSystematics();
   int numOscParams = 6;
   FitParamList* fp = new FitParamList(syst->Size() + numOscParams);
   NormalHierarchyOscillationParameters(*fp, param0, param1);
   for(int i = 0; i < syst->Size(); ++i)
   {
      fp->AddParam(numOscParams + i, syst->Idx2Param(i), 1, 0, 2, 0.0001);
   }

   int numDimensions = (param1 == conv::kPhypUndefined) ? 1 : 2;
   for(int i = 0; i < fp->Size(); ++i)
   {
      conv::PhysParamId_t p = fp->WhichParam(i);
      if(p == param0 || (numDimensions == 2 && p == param1))
      {
         fp->SetNuisance(p, false);
         fp->FreeParameter(p);
      }
      else
      {
         fp->SetNuisance(p, true);
         fp->SetDoMarg(p, true);
         fp->FixParameter(p);
      }
  }

   // Restrict systematics to N sigma range
   bool rethrowUnphysical = arg.GetBool("rethrow-unphysical");
   if(rethrowUnphysical)
   {
      double nSigma = arg.GetDouble("n-sigma-limit");
      syst->SetRethrowUnphysical(true);
      syst->SetNSigmaLimit(nSigma);
      for(int i = 0; i < syst->Size(); ++i)
      {
         conv::PhysParamId_t p = syst->Idx2Param(i);
         fp->SetMinValue(p, 1 - nSigma * syst->OneSigmaError(p));
         fp->SetMaxValue(p, 1 + nSigma * syst->OneSigmaError(p));
      }
   }

   // Set oscillation parameter priors
   LOG("valor_dune", pNOTICE) << "Setting oscillation parameter priors";
   SetPriors(*fp, arg.GetDouble("n-sigma-limit"));
   LOG("valor_dune", pNOTICE) << "FP:\n" << *fp;

   // Generate fake data with statistical fluctuations
   // Ensemble of (eventually) 5000 toys
   int i = 0;
   const int ensemble = 10;
   double** pull = new double*[3];
   for(int row = 0; row < 3; ++row)
   {
      pull[row] = new double[ensemble];
   }
   for(double val = fp->MinValue(param0); val <= fp->MaxValue(param0);
         val += fp->StepSize(param0), ++i)
   {
      for(int toy = 0; toy < ensemble; ++toy)
      {
         fp->SetCurrentValue(param0, val);
         Rnd::Instance()->SetSeeds(arg);
         data->Generate(model, *fp, true);

         MarginaliserABC* marginaliser = new MCMarginaliser(data, model, fp);
         marginaliser->Configure(arg);
         marginaliser->Marginalise();
 
         FitInputs* fitInputs = new FitInputs(data, model, fp, marginaliser);
         FitterABC* fitter = util::GetFitter(fitInputs,
               arg.GetString("fitter").c_str());
         fitter->DoTheFit();
         fp->CopyBestFitToCurrValues();
         double x = fp->CurrValue(param0);
         double xtrue = val;
         double hesse = fp->HesseError(param0);
         pull[i][toy] = (x - xtrue) / hesse;
         delete marginaliser;
      }
   }

   for(int row = 0; row < 3; ++row)
   {
      delete[] pull[row];
   }
   delete[] pull;
}

PhysParamList* GetPhysParamList(const CmdLnArgList& arg)
{
   std::string trueValuesFile = arg.GetString("true-from-filename");
   std::string trueValuesObj = arg.GetString("true-from-objname");
   
   PhysParamList* trueValues = 0;
   if (trueValuesFile.size() && util::ToLowerCase(trueValuesFile) != "none")
   {
      TFile tvf(trueValuesFile.c_str());
      if(!tvf.IsOpen())
      {
         LOG("valor_dune", pERROR) << "Could not read true values file " <<
            trueValuesFile;
         util::Die(-1);
      }

      trueValues = dynamic_cast<PhysParamList*>(tvf.Get(
         trueValuesObj.c_str()));

      if (!trueValues)
      {
         LOG("valor_dune", pERROR) << "Could not read true values object " <<
            trueValuesObj << " from file " << trueValuesFile;
         util::Die(-1);
      }
   }

   return trueValues;
}

void SetPriors(FitParamList& fp, double nSigma)
{
   if(fp.Exists(conv::kPhypCPV))
   {
      SetFlatPrior(fp, conv::kPhypCPV, -TMath::Pi(), TMath::Pi());
   }
   if(fp.Exists(conv::kPhypMixing23))
   {
      SetFlatPrior(fp, conv::kPhypMixing23, 0.888, 1.0);
   }
   if(fp.Exists(conv::kPhypMixing13))
   {
      SetGausPrior(fp, conv::kPhypMixing13, 0.093, 0.008, nSigma);
   }
   if(fp.Exists(conv::kPhypDm23sq))
   {
      SetFlatPrior(fp, conv::kPhypDm23sq, 2e-3, 3e-3);
   }
   if(fp.Exists(conv::kPhypDm12sq))
   {
      SetGausPrior(fp, conv::kPhypDm12sq, 7.53e-5, 1.8e-6, nSigma);
   }
   if(fp.Exists(conv::kPhypMixing12))
   {
      SetGausPrior(fp, conv::kPhypMixing12, 0.846, 0.021, nSigma);
   }
   if(fp.Exists(conv::kPhypCPVBar))
   {
      SetFlatPrior(fp, conv::kPhypCPVBar, -TMath::Pi(), TMath::Pi());
   }
   if(fp.Exists(conv::kPhypMixing23Bar))
   {
      SetFlatPrior(fp, conv::kPhypMixing23Bar, 0.888, 1.0);
   }
   if(fp.Exists(conv::kPhypMixing13Bar))
   {
      SetGausPrior(fp, conv::kPhypMixing13Bar, 0.093, 0.008, nSigma);
   }
   if(fp.Exists(conv::kPhypDm23sqBar))
   {
      SetFlatPrior(fp, conv::kPhypDm23sqBar, 2e-3, 3e-3);
   }
   if(fp.Exists(conv::kPhypDm12sqBar))
   {
      SetGausPrior(fp, conv::kPhypDm12sqBar, 7.53e-5, 1.8e-6, nSigma);
   }
   if(fp.Exists(conv::kPhypMixing12Bar))
   {
      SetGausPrior(fp, conv::kPhypMixing12Bar, 0.846, 0.021, nSigma);
   }
}

void SetFlatPrior(FitParamList& fp, conv::PhysParamId_t p,
      double min, double max)
{
   fp.SetPriorMode(p, "flat");
   fp.SetInitValue(p, (min + max) / 2.0);
   fp.SetMinValueFlat(p, min);
   fp.SetMaxValueFlat(p, max);
   fp.SetMinValue(p, min);
   fp.SetMaxValue(p, max);
   fp.SetStepSize(p, (max - min) / 9999.0);
}

void SetGausPrior(FitParamList& fp, conv::PhysParamId_t p,
      double mean, double sigma, double nSigma)
{
   fp.SetPriorMode(p, "gaus");
   fp.SetInitValue(p, mean);
   fp.SetMeanGaus(p, mean);
   fp.SetSigmaGaus(p, sigma);
   fp.SetMinValue(p, mean - nSigma * sigma);
   fp.SetMaxValue(p, mean + nSigma * sigma);
   fp.SetStepSize(p, (fp.MaxValue(p) - fp.MinValue(p)) / 9999.0);
}

void SetUserPrior(FitParamList& fp, conv::PhysParamId_t p, TH1D* h)
{
   fp.SetPriorMode(p, "user");
   fp.SetPriorHisto(p, h);
   fp.SetToyHisto(p, h);
}

void NormalHierarchyOscillationParameters(FitParamList& fp,
      conv::PhysParamId_t param0, conv::PhysParamId_t param1)
{
   if(param0 != conv::kPhypMixing23 && param1 != conv::kPhypMixing23)
   {
      fp.AddParam(0, conv::kPhypMixing23, 0.524, 0, 1, 0.0001);
   }
   else
   {
      fp.AddParam(0, conv::kPhypMixing23, 0.35, 0.35, 0.65, 0.15);
   }
   if(param0 != conv::kPhypMixing13 && param1 != conv::kPhypMixing13)
   {
      fp.AddParam(1, conv::kPhypMixing13, 0.0422, 0, 1, 0.0001);
   }
   else
   {
      fp.AddParam(1, conv::kPhypMixing13, 0.03, 0.03, 0.11, 0.04);
   }
   if(param0 != conv::kPhypMixing12 && param1 != conv::kPhypMixing12)
   {
      fp.AddParam(2, conv::kPhypMixing12, 0.304, 0, 1, 0.0001);
   }
   else
   {
      fp.AddParam(2, conv::kPhypMixing12, 0.200, 0.2, 0.4, 0.1);
   }
   if(param0 != conv::kPhypCPV && param1 != conv::kPhypCPV)
   {
      fp.AddParam(3, conv::kPhypCPV, 1.91, 0, 2, 0.0001);
   }
   else
   {
      fp.AddParam(3, conv::kPhypCPV, 1.0, 1.0, 2.0, 0.5);
   }
   if(param0 != conv::kPhypDm23sq && param1 != conv::kPhypDm23sq)
   {
      fp.AddParam(4, conv::kPhypDm23sq, 2.51E-3, 0, 1, 0.0001);
   }
   else
   {
      fp.AddParam(4, conv::kPhypDm23sq, 2.3E-3, 2.3E-3, 2.7E-3, 2.0E-4);
   }
   if(param0 != conv::kPhypDm12sq && param1 != conv::kPhypDm12sq)
   {
      fp.AddParam(5, conv::kPhypDm12sq, 7.53E-5, 0, 1, 0.0001);
   }
   else
   {
      fp.AddParam(5, conv::kPhypDm12sq, 7.4E-5, 7.4E-5, 7.6E-5, 1.0E-6);
   }
}

void InvertedHierarchyOscillationParameters(FitParamList& fp,
      conv::PhysParamId_t param0, conv::PhysParamId_t param1)
{
   if(param0 != conv::kPhypMixing23 && param1 != conv::kPhypMixing23)
   {
      fp.AddParam(0, conv::kPhypMixing23, 0.534, 0, 1, 0.0001);
   }
   else
   {
      fp.AddParam(0, conv::kPhypMixing23, 0.35, 0.35, 0.65, 0.15);
   }
   if(param0 != conv::kPhypMixing13 && param1 != conv::kPhypMixing13)
   {
      fp.AddParam(1, conv::kPhypMixing13, 0.0491, 0, 1, 0.0001);
   }
   else
   {
      fp.AddParam(1, conv::kPhypMixing13, 0.03, 0.03, 0.11, 0.04);
   }
   if(param0 != conv::kPhypMixing12 && param1 != conv::kPhypMixing12)
   {
      fp.AddParam(2, conv::kPhypMixing12, 0.304, 0, 1, 0.0001);
   }
   else
   {
      fp.AddParam(2, conv::kPhypMixing12, 0.200, 0.2, 0.4, 0.1);
   }
   if(param0 != conv::kPhypCPV && param1 != conv::kPhypCPV)
   {
      fp.AddParam(3, conv::kPhypCPV, 1.01, 0, 1, 0.0001);
   }
   else
   {
      fp.AddParam(3, conv::kPhypCPV, 1.0, 1.0, 2.0, 0.5);
   }
   if(param0 != conv::kPhypDm23sq && param1 != conv::kPhypDm23sq)
   {
      fp.AddParam(4, conv::kPhypDm23sq, 2.49E-3, 0, 1, 0.0001);
   }
   else
   {
      fp.AddParam(4, conv::kPhypDm23sq, 2.3E-3, 2.3E-3, 2.7E-3, 2.0E-4);
   }
   if(param0 != conv::kPhypDm12sq && param1 != conv::kPhypDm12sq)
   {
      fp.AddParam(5, conv::kPhypDm12sq, 7.53E-5, 0, 1, 0.0001);
   }
   else
   {
      fp.AddParam(5, conv::kPhypDm12sq, 7.4E-5, 7.4E-5, 7.6E-5, 1.0E-6);
   }
}

