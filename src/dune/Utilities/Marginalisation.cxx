#include "dune/Utilities/Marginalisation.h"

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
   _filePrefix(filePrefix), _model(&model), _likelihood(0.0), _chi2(0.0)
{
}
//______________________________________________________________________________
Marginalisation::~Marginalisation()
{
   this->_model = nullptr;
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
      LOG("valor_dune", pNOTICE) << "Filename: " << filename;

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

} // valor

