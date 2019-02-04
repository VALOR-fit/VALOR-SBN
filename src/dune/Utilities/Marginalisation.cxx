#include "dune/Utilities/Marginalisation.h"

#include <limits>
#include <sstream>
#include <string>
#include "TMath.h"

#include "dune/Conventions/PhysicalParameterLimits.h"
#include "dune/Utilities/UtlOscillation.h"
#include "valor/Messenger/Messenger.h"

namespace valor
{

Marginalisation::Marginalisation(CompoundFitElements& elements,
      string filePrefix):
   Marginalisation(*elements.FitModel(), filePrefix)
{
}
//______________________________________________________________________________
Marginalisation::Marginalisation(FitModelABC& model, string filePrefix):
   _filePrefix(filePrefix), _model(&model), _likelihood(0.0), _chi2(0.0),
   _isFit2D(false), _likelihood_1D(nullptr), _likelihood_2D(nullptr),
   _chi2_1D(nullptr), _chi2_2D(nullptr), _fitResult(nullptr)
{
}
//______________________________________________________________________________
Marginalisation::~Marginalisation()
{
   this->_model = nullptr;
   delete this->_likelihood_1D;
   delete this->_likelihood_2D;
   delete this->_chi2_1D;
   delete this->_chi2_2D;
   delete this->_fitResult;
}
//______________________________________________________________________________
void Marginalisation::BuildToys(const int fitParamBin, const int batch,
      const int Ntoys, FitParamList& fpl, bool randomizeSystematics,
      const char* options, bool rethrowUnphysical)
{
   this->BuildToys(fitParamBin, -1, batch, Ntoys, fpl, randomizeSystematics,
         options, rethrowUnphysical);
}
//______________________________________________________________________________
void Marginalisation::BuildToys(const int fitParam1Bin, const int fitParam2Bin,
      const int batch, const int Ntoys, FitParamList& fpl,
      bool randomizeSystematics, const char* options, bool rethrowUnphysical)
{
   std::ostringstream oss;
   oss << this->_filePrefix << "_" << fitParam1Bin;
   if(fitParam2Bin > -1)
   {  // Filename for 2D fit
      oss << "_v_" << fitParam2Bin;
   }
   oss << "_" << batch << "_" << Ntoys << ".bin";

   std::string filename = oss.str();

   PhysicalParameterLimits* limits = PhysicalParameterLimits::Instance();

   // Create a file to store this batch of marginalisation toys
   std::ofstream os_toys(filename, std::ios::binary | std::ios::out);

   for(int t = 0; t < Ntoys; ++t)
   {
      for( ; ; )
      {
         this->_model->ResetSystematics("all");
         // Randomise the systematics in the model
         if(randomizeSystematics)
         {
            this->_model->RandomizeSystematics(options);
            util::oscillation::ThrowOscillationParameters(fpl);
         }

         PhysParamList tweaks = this->_model->Tweaks();
         fpl.FromPhysParamList(tweaks, "current silent");

         LOG("Marginalisation", pINFO) << fpl;

         // Check parameter name, maybe rethrow
         if(rethrowUnphysical && !limits->AllWithinLimits(fpl))
         {
            LOG("valor_dune", pDEBUG) << "At least one parameter thrown " <<
               "outside expected limits. Rethrowing.";
         }
         else
         {
            break;
         }
      }
      PhysParamList true_params = fpl.AsPhysParamList("current");
       
      // Generate a toy-MC experiment 
      LOG("valor_dune", pDEBUG) << "Generating toy-MC data";
      LOG("valor_dune", pDEBUG) << "Toy-MC generation uses true parameters: " << true_params;
      this->_model->Generate(fpl, "+SB");
      this->_model->Write(os_toys, "pdft+SB");
   }
   os_toys.close();
}
//______________________________________________________________________________
void Marginalisation::ComputeStatistics(const int fitParamBin, FitDataABC* data,
      const int Ntoys, const int Nbatches, const int firstBatch)
{
   this->ComputeStatistics(fitParamBin, -1, data, Ntoys, Nbatches, firstBatch);
}
//______________________________________________________________________________
void Marginalisation::ComputeStatistics(const int fitParam1Bin,
      const int fitParam2Bin, FitDataABC* data, const int Ntoys,
      const int Nbatches, const int firstBatch)
{
   const int lastBatch = firstBatch + Nbatches - 1;
   double likelihood_sum = 0.0;
   for(int b = firstBatch; b <= lastBatch; ++b)
   {
      std::ostringstream oss;
      oss << this->_filePrefix << "_" << fitParam1Bin;
      if(fitParam2Bin > -1)
      {  // File name for 2D fit
         oss << "_v_" << fitParam2Bin;
      }
      oss << "_" << b << "_" << Ntoys << ".bin";
      std::string filename = oss.str();
      LOG("valor_dune", pINFO) << "Filename: " << filename;

      std::ifstream is_toys(filename, std::ios::binary | std::ios::in);
      for(int t = 0; t < Ntoys; ++t)
      {
         // Read a toy-MC experiment 
         LOG("valor_dune", pDEBUG) << "Reading toy-MC data";
         this->_model->Read(is_toys, "pdft+SB");
         double chi2 = data->GetFitStatistic(this->_model, "likelihood-ratio");
         double likelihood = TMath::Exp(-chi2 * 0.5);
         likelihood_sum += likelihood;

         LOG("valor_dune", pDEBUG) << "chi2(" << t << "): " << chi2 <<
            " L(" << t << "): " << likelihood;
      }
      is_toys.close();
   }
   const int N = Nbatches * Ntoys;
   this->_likelihood = likelihood_sum / N;
   this->_chi2 = -2 * TMath::Log(this->_likelihood);
}

void Marginalisation::InitFit(const int param1Nbins,
      const double param1MinValue, const double param1MaxValue,
      const int param2Nbins, const double param2MinValue,
      const double param2MaxValue)
{
   if(param2Nbins > 0)
   {
      this->_isFit2D = true;
      double step = (param1MaxValue - param1MinValue) / (param1Nbins - 1);
      double shift = 0.5 * step;
      double xMin = param1MinValue - shift;
      double xMax = param1MaxValue + shift;
      step = (param2MaxValue - param2MinValue) / (param2Nbins - 1);
      shift = 0.5 * step;
      double yMin = param2MinValue - shift;
      double yMax = param2MaxValue + shift;
      this->_likelihood_2D = new TH2D("likelihood_2d", "Likelihood 2D",
            param1Nbins, xMin, xMax, param2Nbins, yMin, yMax);
      this->_chi2_2D = new TH2D("chi2_2d", "#chi^{2} 2D", param1Nbins, xMin,
            xMax, param2Nbins, yMin, yMax);

      // Initialise chi2 grid to maximum value - likelihood initialised to zero
      // by default
      for(int i = 1; i <= param1Nbins; ++i)
      {
         for(int j = 1; j <= param2Nbins; ++j)
         {
            this->_chi2_2D->SetBinContent(i, j, std::numeric_limits<double>::max());
         }
      }
   }
   else
   {
      this->_isFit2D = false;
      double step = (param1MaxValue - param1MinValue) / (param1Nbins - 1);
      double shift = 0.5 * step;
      double xMin = param1MinValue - shift;
      double xMax = param1MaxValue + shift;
      this->_likelihood_1D = new TH1D("likelihood_1d", "Likelihood 1D",
            param1Nbins, xMin, xMax);
      this->_chi2_1D = new TH1D("chi2_1d", "#chi^{2} 1D", param1Nbins, xMin,
            xMax);

      // Initialise chi2 grid to maximum value - likelihood initialised to zero
      // by default
      for(int i = 1; i <= param1Nbins; ++i)
      {
         this->_chi2_1D->SetBinContent(i, std::numeric_limits<double>::max());
      }
   }
}

FitResult* Marginalisation::Fit(FitDataABC* data, const int Ntoys, const int Nbatches,
      const int firstBatch)
{
   if(this->_isFit2D)
   {
      const int Nx =  this->_chi2_2D->GetXaxis()->GetNbins();
      const int Ny =  this->_chi2_2D->GetYaxis()->GetNbins();
      // Get the likelihood and chi2 statistics for the entire grid
      for(int i = 0; i < Nx; ++i)
      {
         for(int j = 0; j < Ny; ++j)
         {
            this->ComputeStatistics(i, j, data, Ntoys, Nbatches, firstBatch);
            this->_likelihood_2D->SetBinContent(i + 1, j + 1, this->_likelihood);
            this->_chi2_2D->SetBinContent(i + 1, j + 1, this->_chi2);
         }
      }

      // Store the result of the fit
      this->_fitResult = new FitResult(*this->_chi2_2D, *this->_likelihood_2D);

      return this->_fitResult;
   }
   else
   {
      const int N =  this->_chi2_1D->GetXaxis()->GetNbins();
      // Get the likelihood and chi2 statistics for the entire grid
      for(int i = 0; i < N; ++i)
      {
         this->ComputeStatistics(i, data, Ntoys, Nbatches, firstBatch);
         this->_likelihood_1D->SetBinContent(i + 1, this->_likelihood);
         this->_chi2_1D->SetBinContent(i + 1, this->_chi2);
      }

      // Store the result of the fit
      this->_fitResult = new FitResult(*this->_chi2_1D, *this->_likelihood_1D);

      return this->_fitResult;
   }
}

FitResult* Marginalisation::Fit(const double initValue, FitDataABC* data,
      const int Ntoys, const int Nbatches, const int firstBatch)
{
   double value = initValue;
   int binInit = this->_chi2_1D->FindBin(value);
   const int N =  this->_chi2_1D->GetXaxis()->GetNbins();
   bool minimised = false;

   while(!minimised)
   {
      // Get the likelihood and chi2 statistics for the local grid (3x3 region
      // around the current bin)
      int binMin = CheckLocalMinimum(binInit, 3, N, data, Ntoys, Nbatches,
            firstBatch);
      if(binMin == binInit)
      {  // This is the (very) local minimum, check a larger region to see if
         // this is likely to be the true global minimum
         binMin = CheckLocalMinimum(binInit, 7, N, data, Ntoys, Nbatches,
               firstBatch);
         if(binMin == binInit)
         {  // Global minimum probably found, we're done
            minimised = true;
         }
         else
         {  // Update central bin and iterate, minimum not found.
            binInit = binMin;
         }
      }
      else
      {  // Update central bin and iterate, minimum not found.
         binInit = binMin;
      }
   }

   // Store the result of the fit
   this->_fitResult = new FitResult(*this->_chi2_1D, *this->_likelihood_1D);

   return this->_fitResult;
}

FitResult* Marginalisation::Fit(const double initValue1,
      const double initValue2, FitDataABC* data, const int Ntoys,
      const int Nbatches, const int firstBatch)
{
   double valueX = initValue1;
   double valueY = initValue2;
   int binInitX = this->_chi2_2D->GetXaxis()->FindBin(valueX);
   int binInitY = this->_chi2_2D->GetYaxis()->FindBin(valueY);
   const int Nx =  this->_chi2_2D->GetXaxis()->GetNbins();
   const int Ny =  this->_chi2_2D->GetYaxis()->GetNbins();
   bool minimised = false;

   while(!minimised)
   {
      // Get the likelihood and chi2 statistics for the local grid (3x3 region
      // around the current bin)
      int binMinX = binInitX;
      int binMinY = binInitY;
      CheckLocalMinimum(binMinX, binMinY, 3, Nx, Ny, data, Ntoys, Nbatches,
            firstBatch);
      if(binMinX == binInitX && binMinY == binInitY)
      {  // This is the (very) local minimum, check a larger region to see if
         // this is likely to be the true global minimum
         CheckLocalMinimum(binMinX, binMinY, 7, Nx, Ny, data, Ntoys, Nbatches,
               firstBatch);
         if(binMinX == binInitX && binMinY == binInitY)
         {  // Global minimum probably found, we're done
            minimised = true;
         }
         else
         {  // Update central bin and iterate, minimum not found.
            binInitX = binMinX;
            binInitY = binMinY;
         }
      }
      else
      {  // Update central bin and iterate, minimum not found.
         binInitX = binMinX;
         binInitY = binMinY;
      }
   }

   // Store the result of the fit
   this->_fitResult = new FitResult(*this->_chi2_2D, *this->_likelihood_2D);

   return this->_fitResult;
}

int Marginalisation::CheckLocalMinimum(const int binInit, const int windowSize,
      const int gridSize, FitDataABC* data, const int Ntoys, const int Nbatches,
      const int firstBatch)
{
   int binMin = binInit;
   const int limit = (windowSize - 1) / 2;
   double chi2Min = std::numeric_limits<double>::max();
   for(int di = -limit; di <= limit; ++di)
   {
      int i = binInit + di;
      // Check still within fit bounds
      if(i < 1 || i > gridSize)
      {
         continue;
      }
      // Check if the chi2 value has already been loaded
      if(this->_likelihood_1D->GetBinContent(i) == 0.0)
      {  // Load the chi2 value from file
         this->ComputeStatistics(i - 1, data, Ntoys, Nbatches, firstBatch);
         this->_likelihood_1D->SetBinContent(i, this->_likelihood);
         this->_chi2_1D->SetBinContent(i, this->_chi2);
      }
      else
      {  // Load the chi2 value from the existing surface
         this->_chi2 = this->_chi2_1D->GetBinContent(i);
      }
      if(this->_chi2 < chi2Min)
      {
         chi2Min = this->_chi2;
         binMin = i;
      }
   }

   return binMin;
}

void Marginalisation::CheckLocalMinimum(int& binX, int& binY,
      const int windowSize, const int gridSizeX, const int gridSizeY,
      FitDataABC* data, const int Ntoys, const int Nbatches,
      const int firstBatch)
{
   int binMinX = binX;
   int binMinY = binY;
   const int limit = (windowSize - 1) / 2;
   double chi2Min = std::numeric_limits<double>::max();
   for(int di = -limit; di <= limit; ++di)
   {
      int i = binX + di;
      // Check still within fit bounds
      if(i < 1 || i > gridSizeX)
      {
         continue;
      }
      for(int dj = -limit; dj <= limit; ++dj)
      {
         int j = binY + di;
         // Check still within fit bounds
         if(j < 1 || j > gridSizeY)
         {
            continue;
         }
         // Check if the chi2 value has already been loaded
         if(this->_likelihood_2D->GetBinContent(i, j) == 0.0)
         {  // Load the chi2 value from file
            this->ComputeStatistics(i - 1, j - 1, data, Ntoys, Nbatches,
                  firstBatch);
            this->_likelihood_2D->SetBinContent(i, j, this->_likelihood);
            this->_chi2_2D->SetBinContent(i, j, this->_chi2);
         }
         else
         {  // Load the chi2 value from the existing surface
            this->_chi2 = this->_chi2_2D->GetBinContent(i, j);
         }
         if(this->_chi2 < chi2Min)
         {
            chi2Min = this->_chi2;
            binMinX = i;
            binMinY = j;
         }
      }
   }

   // Set the location of the minimum bin in the reference variables
   binX = binMinX;
   binY = binMinY;
}

} // valor

