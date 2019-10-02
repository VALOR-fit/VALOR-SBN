#include "dune/Utilities/Marginalisation.h"

#include <limits>
#include <sstream>
#include <string>
#include "TMath.h"

#include "dune/Conventions/PhysicalParameterLimits.h"
#include "dune/Utilities/UtlOscillation.h"
#include "valor/Messenger/Messenger.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Utilities/NameRegistry.h"
#include "valor/Utilities/UtlStr.h"

//#define VALOR_DUNE_LOW_LEVEL_MESG_ENABLED

namespace valor
{

Marginalisation::Marginalisation(CompoundFitElements& elements, string filePrefix,  bool use_simple_binning,
                                 bool save_throws_to_tree, string va_format):
   Marginalisation(*elements.FitModel(), filePrefix, use_simple_binning, save_throws_to_tree, va_format)
{
}
//______________________________________________________________________________
Marginalisation::Marginalisation(FitModelABC& model, string filePrefix, bool use_simple_binning,
                                 bool save_throws_to_tree, string va_format):
   _filePrefix(filePrefix), _model(&model), _likelihood(0.0), _chi2(0.0),
   _isFit2D(false), _likelihood_1D(nullptr), _likelihood_2D(nullptr),
   _chi2_1D(nullptr), _chi2_2D(nullptr), _fitResult(nullptr),
   _use_simple_binning(use_simple_binning), _save_throws_to_tree(save_throws_to_tree),
   _tree_pars(nullptr), _param1_start_bin(0), _param2_start_bin(-1), _va_format(va_format)
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
   delete this->_tree_pars;
}
//______________________________________________________________________________
void Marginalisation::BuildToys(const int fitParamBin, const int batch,
      const int Ntoys, FitParamList& fpl, bool randomizeSystematics,
      const char* options, bool rethrowUnphysical,
      std::string toy_throw_file_to_read, std::string param_name_map_file)
{
   this->BuildToys(fitParamBin, -1, batch, Ntoys, fpl, randomizeSystematics,
         options, rethrowUnphysical, toy_throw_file_to_read, param_name_map_file);
}
//______________________________________________________________________________
void Marginalisation::BuildToys(const int fitParam1Bin, const int fitParam2Bin,
      const int batch, const int Ntoys, FitParamList& fpl,
      bool randomizeSystematics, const char* options, bool rethrowUnphysical,
      std::string toy_throw_file_to_read, std::string param_name_map_file)
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

   // Will we read throws from a pre-existing file instead of generating them? (This is used e.g. to convert
   // T2K legacy toy throws into SDK marginalisation toys)
   bool read_systematics (toy_throw_file_to_read != "" && toy_throw_file_to_read != "NONE" &&
                          param_name_map_file    != "" && param_name_map_file    != "NONE");

   unsigned int n_rethrows = 0;
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
         else if(read_systematics) {
            this->ReadParamsFromThrowFile(fpl, toy_throw_file_to_read, param_name_map_file, options, t);
            break;
         }

         if(!read_systematics) {
            PhysParamList tweaks = this->_model->Tweaks();
            fpl.FromPhysParamList(tweaks, "current silent");
         }

#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
         LOG("Marginalisation", pINFO) << fpl;
#endif

         // Check parameter name, maybe rethrow
         if(rethrowUnphysical && !limits->AllWithinLimits(fpl))
         {
            n_rethrows++;
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
            LOG("Marginalisation", pDEBUG) << "At least one parameter thrown " <<
               "outside expected limits. Rethrowing.";
#endif
         }
         else
         {
            break;
         }
      }
      PhysParamList true_params = fpl.AsPhysParamList("current");
       
      // Generate a toy-MC experiment
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
      LOG("Marginalisation", pDEBUG) << "Generating toy-MC data";
      LOG("Marginalisation", pDEBUG) << "Toy-MC generation uses true parameters: " << true_params;
#endif
      if(t % 100 == 0) { LOG("Marginalisation", pNOTICE) << "Generating toy-MC #" << t; }
      const char* write_opt = _va_format.c_str();
      if (_use_simple_binning) { write_opt = (_va_format + "+SB").c_str(); }
      this->_model->Generate(fpl, write_opt);
      this->_model->Write(os_toys, write_opt);
      this->SaveParamThrows(fpl, t == Ntoys-1, filename);
   }
   os_toys.close();
   LOG("Marginalisation", pNOTICE) << "Finished building marginalisation toys. Generated " << Ntoys
                              << ", re-threw " << n_rethrows;
}
//______________________________________________________________________________
void Marginalisation::SaveParamThrows(FitParamList& fpl, bool write_tree, std::string binary_file_name)
{
   if(!_save_throws_to_tree) { return; }

   // Set up an array to hold all of the parameter values that we'll save to the output tree
   double param_values[conv::knppmax];
   for(int ip = 0; ip < conv::knppmax; ip++){
      param_values[ip] = -999;
   }

   // Set up the tree, if we haven't done so already
   if(!_tree_pars) {
       _tree_pars = new TTree("marg_parameter_values","Input parameters used for marginalisation");
       for (int ip = 0 ; ip < conv::knppmax ; ip++) {
          conv::PhysParamId_t p = (conv::PhysParamId_t)ip;
          if(p == conv::kPhypUndefined) { continue; }
          std::string param_name = util::NameRegistry::Instance()->ParamAsStringVerySimple(p);
          std::string branch_info = param_name + "/D";
          if (fpl.Exists(p)) {
             _tree_pars->Branch(param_name.c_str(), &(param_values[ip]), branch_info.c_str() );
          }
       }
   }

   // Save this throw to the tree
   for (int ip = 0 ; ip < conv::knppmax ; ip++) {
      conv::PhysParamId_t p = (conv::PhysParamId_t)ip;
      if (fpl.Exists(p)) {
         param_values[ip] = fpl.CurrValue(p);
      }
   }
   _tree_pars->Fill();

   // If this is the final toy, write the tree to a new file
   if(write_tree) {
      // Construct the output file name
      std::string file_name = binary_file_name;
      std::string to_replace = ".bin";
      size_t start_pos = file_name.find(to_replace);
      if(start_pos == std::string::npos) {
         LOG("Marginalisation", pERROR) << "Could not construct output file name.";
         util::Die(-1);
      }
      file_name.replace(start_pos, to_replace.length(), "_toy_throws.root");

      TFile *out_file = new TFile(file_name.c_str(), "RECREATE");
      out_file->cd();
      _tree_pars->Write();
      out_file->Close();
      delete out_file;
   }
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
   const int N = Nbatches * Ntoys;
   vector<double> vec_chi2_toy(N);  // Index constructed (ibatch - firstBatch) * Ntoys + itoy
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
      LOG("Marginalisation", pINFO) << "Filename: " << filename;

      std::ifstream is_toys(filename, std::ios::binary | std::ios::in);
      for(int t = 0; t < Ntoys; ++t)
      {
         // Read the chi2 of each toy-MC experiment into a vector
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
         LOG("Marginalisation", pDEBUG) << "Reading toy-MC data";
#endif
         const char* read_opt = _va_format.c_str();
         if (_use_simple_binning) { read_opt = (_va_format + "+SB").c_str(); }
         this->_model->Read(is_toys, read_opt);
         double chi2 = data->GetFitStatistic(this->_model, "likelihood-ratio");
         vec_chi2_toy[(b - firstBatch) * Ntoys + t] = chi2;
#ifdef VALOR_DUNE_LOW_LEVEL_MESG_ENABLED
         LOG("Marginalisation", pDEBUG) << "chi2(" << t << "): " << chi2 <<
            " L(" << t << "): " << exp(-chi2/2.);
#endif
      }
      is_toys.close();
   }

   // Now sort the vector of chi2 values in descending order. This is so that the contributions from tiny
   // likelihood values are summed (and could become significant), instead of being lost when added to relatively
   // large likelihood values. (Note: rbegin/rend is the reverse beginning/end, i.e. the end/beginning).
   std::sort(vec_chi2_toy.rbegin(),vec_chi2_toy.rend());

   // Use the median chisq as a scale factor to guard against precision issues
   double median_index = (vec_chi2_toy.size() + 1) / 2.;
   double diff_chi2 = (vec_chi2_toy[(int)std::floor(median_index)] + vec_chi2_toy[(int)std::ceil(median_index)]) / 2.;
   double scale = diff_chi2;
   if(diff_chi2 > _scale_precision) scale = _scale_precision;
   scale = TMath::Min(_scale_precision, scale);

   // Calculate the scaled likelihood sum
   double likelihood_sum = 0.0;
   for (std::vector<double>::iterator it=vec_chi2_toy.begin(); it!=vec_chi2_toy.end(); ++it){
      double arg = -*it/2. + scale;
      likelihood_sum += exp(arg) / N;
   }
   this->_chi2 = 2*scale - 2*log(likelihood_sum);  // The scale cancels out at this stage of the calculation, so this is the un-scaled chi2
   this->_likelihood = exp(-this->_chi2/2.);
}

void Marginalisation::InitFit(const int param1Nbins, const int param1StartBin,
      const double param1MinValue, const double param1MaxValue,
      const int param2Nbins, const int param2StartBin,
      const double param2MinValue, const double param2MaxValue)
{
   if(param2Nbins > 0)
   {
      this->_isFit2D = true;
      double step = 0.0;
      if(param1Nbins > 1) { step = (param1MaxValue - param1MinValue) / (param1Nbins - 1); }
      double shift = 0.5 * step;
      double xMin = param1MinValue - shift;
      double xMax = param1MaxValue + shift;
      step = 0.0;
      if(param2Nbins > 1) { step = (param2MaxValue - param2MinValue) / (param2Nbins - 1); }
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
      _param1_start_bin = param1StartBin;
      _param2_start_bin = param2StartBin;
   }
   else
   {
      this->_isFit2D = false;
      double step = 0.0;
      if(param1Nbins > 1) { step = (param1MaxValue - param1MinValue) / (param1Nbins - 1); }
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
      _param1_start_bin = param1StartBin;
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
      for(int i = _param1_start_bin; i < _param1_start_bin + Nx; ++i)
      {
         for(int j = _param2_start_bin; j < _param2_start_bin + Ny; ++j)
         {
            this->ComputeStatistics(i, j, data, Ntoys, Nbatches, firstBatch);
            this->_likelihood_2D->SetBinContent(i + 1 - _param1_start_bin, j + 1 - _param2_start_bin, this->_likelihood);
            this->_chi2_2D->SetBinContent(i + 1 - _param1_start_bin, j + 1 - _param2_start_bin, this->_chi2);
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
      for(int i = _param1_start_bin; i < _param1_start_bin + N; ++i)
      {
         this->ComputeStatistics(i, data, Ntoys, Nbatches, firstBatch);
         this->_likelihood_1D->SetBinContent(i + 1 - _param1_start_bin, this->_likelihood);
         this->_chi2_1D->SetBinContent(i + 1 - _param1_start_bin, this->_chi2);
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
         int j = binY + dj;
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

void Marginalisation::ReadParamsFromThrowFile(FitParamList& fpl, std::string toy_throw_file_to_read,
                                              std::string param_name_map_file, const char* options, int toy_number)
{
  if(toy_throw_file_to_read == "" || param_name_map_file == "") {
     LOG("valor_dune", pERROR) << "No input toy throw file or parameter name map file was specified.";
     util::Die(-1);
  }

  TString ts(options);

  // Opening the tree file for every toy is horribly inefficient, but this function will likely just be used
  // to debug a few events, so it's fine for now, as I'd rather have this as self-contained as possible, since
  // it's related to a specific analysis rather than being generic.
  TFile * in_file = new TFile(toy_throw_file_to_read.c_str(), "READ");
  in_file->cd();
  TTree * tree_input_pars = (TTree*) in_file->Get("marg_parameter_values");

  // Set up an array to hold all of the parameter values that we'll read
  double read_params[conv::knppmax];
  for(int ip = 0; ip < conv::knppmax; ip++){
     read_params[ip] = -999;
  }

  // Set up the branches to read
  //std::map<conv::PhysParamId_t, double> read_params;
  for (int ip = 0 ; ip < conv::knppmax ; ip++) {
     conv::PhysParamId_t p = (conv::PhysParamId_t)ip;
     if (p == conv::kPhypUndefined) { continue; }
     if (!fpl.Exists(p)) { continue; }
     std::string sdk_param_name = util::NameRegistry::Instance()->ParamAsStringVerySimple(p);
     std::string read_param_name = "";

     // Put in special cases here, where we may need to skip params
     if (ts.Contains("compare-t2k-legacy") &&
         (p == util::NameRegistry::Instance()->PhysParamFromString("SCCA") ||
          p == util::NameRegistry::Instance()->PhysParamFromString("SCCV"))) {
        read_params[ip] = 1.0;
        continue;
     }

     // Open the parameter map file
     std::ifstream map(param_name_map_file);
     std::string arg_file_line = "";
     while (std::getline(map, arg_file_line))
     {
        // Find the read parameter name that corresponds to this parameter
        vector<std::string> tokens = util::Tokens(arg_file_line, ",");
        std::string search_sdk_name    = util::GetStringBetweenDelimiters(util::RemoveAllWhitespace(tokens[0]), "'", "'");
        std::string search_read_name = util::GetStringBetweenDelimiters(util::RemoveAllWhitespace(tokens[1]), "'", "'");
        if (search_sdk_name == sdk_param_name) {
           read_param_name = search_read_name;
           break;
        }
     }
     bool branch_okay = tree_input_pars->SetBranchAddress(read_param_name.c_str(), &(read_params[p]));
  }

  // Read the toy from the tree and fill the FPL
  FitParamList * free_par_list = fpl.ParameterOfInterestSubset();
  tree_input_pars->GetEntry(toy_number);
  for (int ip = 0 ; ip < conv::knppmax ; ip++) {
     conv::PhysParamId_t p = (conv::PhysParamId_t)ip;
     if (p == conv::kPhypUndefined) { continue; }
     if (!fpl.Exists(p)) { continue; }

     // Keep the parameter(s) of interest at their initial values
     if(free_par_list->Exists(p)) {
        fpl.SetCurrentValue(p, free_par_list->InitValue(p));
        continue;
     }

     if (read_params[p] + 999 < conv::kASmallNum) {
        LOG("valor_dune", pERROR) << "The thrown value for param ["
                                  << util::NameRegistry::Instance()->ParamAsStringVerySimple(p)
                                  << "] could not be found.";
        util::Die(-1);
     }

     double param_value = read_params[p];

     // Put in special cases here, where the param value needs changing too
     if (ts.Contains("compare-t2k-legacy") && p == util::NameRegistry::Instance()->PhysParamFromString("sk_e_scale")) {
        param_value += 1;
     }

     fpl.SetCurrentValue(p, param_value);
  }

  LOG("valor_dune", pFATAL) << "Reading toy from input throw file with FPL = " << fpl;   // TODO: demote back to pDEBUG when done testing

  in_file->Close();
  delete in_file;
}

} // valor

