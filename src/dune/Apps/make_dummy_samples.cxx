//____________________________________________________________________________
/*!

\app       valor_dune-make_dummy_samples

\brief     Create a dummy MC sample.

\options     
             --config              : Analysis configuration file [required]
             --mesg-thresholds     : Message thresholds [def: "verbosity.xml"]

\author    Andy Chappell <A.Chappell \at warwick.ac.uk>
           University of Warwick

\created   December 17, 2018

\copyright (c) 2010-2018, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

// root
#include "TFile.h"
#include "TSystem.h"
#include "TObjArray.h"
#include "TRandom.h"
#include "TString.h"
#include "TVirtualFitter.h"
#include "TMath.h"
#include "TStopwatch.h"

#include "cmath"

// fmwk
#include "valor/VArray/VALORArray.h"

#include "valor/Utilities/UtlStyle.h"
#include "valor/Utilities/UtlStr.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Conventions/Opt.h"

using namespace valor;
using namespace valor::conv;

void MakeMCSample();
void MakeCovarianceMatrices();

int main(int argc, char** argv)
{
   MakeMCSample();
   MakeCovarianceMatrices();
  
   return 0;
}

void MakeMCSample()
{
   TFile f("dummy_templates.root", "RECREATE");
   VALORArray* opt_fhc_sample = new VALORArray(3, 12);
   VALORArray* simple_fhc_sample = new VALORArray(5, 12);
   VALORArray* opt_rhc_sample = new VALORArray(3, 12);
   VALORArray* simple_rhc_sample = new VALORArray(5, 12);

   // Populate the bins with dummy data
   TRandom random;
   for(int x = 0; x < 5; ++x)
   {
      for(int y = 0; y < 12; ++y)
      {
         if(x >= 2)
         {
            double fhc_val = random.Uniform(1.0);
            double rhc_val = random.Uniform(0.4);
            simple_fhc_sample->SetEntry(fhc_val, x, y);
            simple_rhc_sample->SetEntry(rhc_val, x, y);

            opt_fhc_sample->SetEntry(fhc_val, x - 2, y);
            opt_rhc_sample->SetEntry(rhc_val, x - 2, y);
         }
         else
         {
            double fhc_val = random.Uniform(1.0);
            double rhc_val = random.Uniform(0.4);
            simple_fhc_sample->SetEntry(fhc_val, x, y);
            simple_rhc_sample->SetEntry(rhc_val, x, y);

            opt_fhc_sample->SetEntry(fhc_val + opt_fhc_sample->GetEntry(0, y), 0, y);
            opt_rhc_sample->SetEntry(rhc_val + opt_rhc_sample->GetEntry(0, y), 0, y);
         }
      }
   }

   opt_fhc_sample->Write("valor_mctnom_ob_vf_dune_nd:LBNF_FHC:numuCC0pi1trk");
   simple_fhc_sample->Write("valor_mctnom_sb_vf_dune_nd:LBNF_FHC:numuCC0pi1trk");
   opt_rhc_sample->Write("valor_mctnom_ob_vf_dune_nd:LBNF_RHC:numuCC0pi1trk");
   simple_rhc_sample->Write("valor_mctnom_sb_vf_dune_nd:LBNF_RHC:numuCC0pi1trk");


   f.Close();

   delete opt_fhc_sample;
   delete simple_fhc_sample;
   delete opt_rhc_sample;
   delete simple_rhc_sample;
}

void MakeCovarianceMatrices()
{
   TRandom random;
   TFile f_flux("flux.root", "RECREATE");
   int Nflux = 8;
   TMatrixD flux_cov(Nflux, Nflux);
   for(int i = 0; i < Nflux; ++i)
   {
      flux_cov(i, i) = random.Uniform(2.5e-3);
   }
   flux_cov.Write("flux_cov");
   f_flux.Close();

   TFile f_det("detector.root", "RECREATE");
   int Ndet = 4;
   TMatrixD det_cov(Ndet, Ndet);
   for(int i = 0; i < Ndet; ++i)
   {
      det_cov(i, i) = random.Uniform(4.0e-2);
   }
   det_cov.Write("det_cov");
   f_det.Close();

   TFile f_int("interaction.root", "RECREATE");
   int Nint = 6;
   TMatrixD int_cov(Nint, Nint);
   for(int i = 0; i < Nint; ++i)
   {
      int_cov(i, i) = random.Uniform(1.0e-1);
   }
   int_cov.Write("int_cov");
   f_int.Close();
}

