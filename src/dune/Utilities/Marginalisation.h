//____________________________________________________________________________
/*!

\class     valor::Marginalisation

\brief     A class handling marginalisation toys.

           Provides the methods for building and storing the toy spectra, along
           with the computation of the marginal likelihood and chi2 statistic.

\author    Andy Chappell <A.Chappell \at warwick.ac.uk>
           University of Warwick

\created   January 22, 2019

\copyright (c) 2010-2019, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_marginalisation_h_
#define _valor_marginalisation_h_

#include <string>

#include "dune/Elements/CompoundFitElements.h"

#include "valor/FitCore/FitDataABC.h"
#include "valor/FitCore/FitModelABC.h"
#include "valor/FitCore/FitParamList.h"
#include "valor/FitCore/FitResult.h"

#include "TH1.h"
#include "TH2.h"

#include <TTree.h>

using std::string;
using namespace valor;

namespace valor
{

class Marginalisation
{
public:
   /**
      Constructs a Marginalisation object.

      \param elements The CompoundFitElements object used to generate the MC
             spectra.
      \param filePrefix The prefix to be used for the marginalisation toy files
             to be written.
   */
   Marginalisation(CompoundFitElements& elements, string filePrefix, bool use_simple_binning,
                   bool save_throws_to_tree = false);

   /**
      Constructs a Marginalisation object.

      \param model The FitModelABC object used to generate the MC spectra.
      \param filePrefix The prefix to be used for the marginalisation toy files
             to be written.
   */
   Marginalisation(FitModelABC& model, string filePrefix, bool use_simple_binning,
                   bool save_throws_to_tree = false);

   /**
      Destructor.

      This class does not own the FitModel object, so it does not destroy it.
   */
   virtual ~Marginalisation();

   /**
      Builds a batch of marginalisation toys.

      To facilitate incremental building of marginalisation toys, a complete set
      of marginalisation toys can be split into batches, each of which should
      have the same number of toys in it.

      \param fitParamBin The bin associated with the current unmarginalised
             oscillation parameter.
      \param batch The numeric ID for the batch of toys to be generated. This
             should start with batch 0.
      \param Ntoys The number of marginalisation toys to be created in *this*
             batch.
      \param fpl The FitParamList defining the parameters to be used in
             generating the marginalisation toys. This method will only throw
             those parameters that return true for FitParamList::IsMarginalized.
      \param randomizeSystematics Whether or not to randomize the systematics.
             Default true (kind of the point of marginalisation, but might be
             useful for testing).
      \param options The options associated with randomizing systematics.
      \param rethrowUnphysical Whether or not to rethrow parameters that exceed
             their physical boundaries (Cholesky decomposition can cause
             parameters to move beyond bounds even if they are thrown with
             limits). Default true.
      \param toy_throw_file_to_read Read throws from a pre-existing file instead of
             generating them. This is used e.g. to convert T2K legacy toy throws
             into SDK marginalisation toys.
             NOTE: As this reads thrown parameter values, statistical fluctuations
             are not copied
      \param param_name_map_file If using toy_throw_file_to_read, also specify this
             argument, which is used to convert SDK parameter names into the parameter
             names used by the toy_throw_file_to_read.
   */
   void BuildToys(const int fitParamBin, const int batch, const int Ntoys,
         FitParamList& fpl, bool randomizeSystematics = true,
         const char* options = "randomize-all;prefit-errors",
         bool rethrowUnphysical = true, std::string toy_throw_file_to_read = "",
         std::string param_name_map_file = "");

   /**
      Builds a batch of marginalisation toys.

      To facilitate incremental building of marginalisation toys, a complete set
      of marginalisation toys can be split into batches, each of which should
      have the same number of toys in it.

      \param fitParam1Bin The bin associated with the first unmarginalised
             oscillation parameter.
      \param fitParam2Bin The bin associated with the second unmarginalised
             oscillation parameter.
      \param batch The numeric ID for the batch of toys to be generated. This
             should start with batch 0.
      \param Ntoys The number of marginalisation toys to be created in *this*
             batch.
      \param fpl The FitParamList defining the parameters to be used in
             generating the marginalisation toys. This method will only throw
             those parameters that return true for FitParamList::IsMarginalized.
      \param randomizeSystematics Whether or not to randomize the systematics.
             Default true (kind of the point of marginalisation, but might be
             useful for testing).
      \param options The options associated with randomizing systematics.
      \param rethrowUnphysical Whether or not to rethrow parameters that exceed
             their physical boundaries (Cholesky decomposition can cause
             parameters to move beyond bounds even if they are thrown with
             limits). Default true.
      \param toy_throw_file_to_read Read throws from a pre-existing file instead of
             generating them. This is used e.g. to convert T2K legacy toy throws
             into SDK marginalisation toys.
             NOTE: As this reads thrown parameter values, statistical fluctuations
             are not copied
      \param param_name_map_file If using toy_throw_file_to_read, also specify this
             argument, which is used to convert SDK parameter names into the parameter
             names used by the toy_throw_file_to_read.
   */
   void BuildToys(const int fitParam1Bin, const int fitParam2Bin,
         const int batch, const int Ntoys, FitParamList& fpl,
         bool randomizeSystematics = true,
         const char* options = "randomize-all;prefit-errors",
         bool rethrowUnphysical = true, std::string toy_throw_file_to_read = "",
         std::string param_name_map_file = "");

   /**
      Computes the marginal likelihood and chi-squared statistics for a given
      data set relative to a set of marginalisation toys.

      \param fitParamBin The bin associated with the current unmarginalised
             oscillation parameter - zero indexed.
      \param data The data against which the statistic should be computed.
      \param Ntoys The number of marginalisation toys contained within each
             batch.
      \param Nbatches The number of batches to include
             (i.e. Nbatches * Ntoys = Ntoys total).
      \param firstBatch The numeric ID for the first batch of marginalisation
             toys to be included. Note, batches should be indexec from 0.
   */
   void ComputeStatistics(const int fitParamBin, FitDataABC* data,
         const int Ntoys, const int Nbatches, const int firstBatch = 0);

   /**
      Computes the marginal likelihood and chi-squared statistics for a given
      data set relative to a set of marginalisation toys.

      \param fitParam1Bin The bin associated with the first unmarginalised
             oscillation parameter - zero indexed.
      \param fitParam2Bin The bin associated with the second unmarginalised
             oscillation parameter - zero indexed.
      \param data The data against which the statistic should be computed.
      \param Ntoys The number of marginalisation toys contained within each
             batch.
      \param Nbatches The number of batches to include
             (i.e. Nbatches * Ntoys = Ntoys total).
      \param firstBatch The numeric ID for the first batch of marginalisation
             toys to be included. Note, batches should be indexec from 0.
   */
   void ComputeStatistics(const int fitParam1Bin, const int fitParam2Bin,
         FitDataABC* data, const int Ntoys, const int Nbatches,
         const int firstBatch = 0);

   /**
      Initialises the chi2 and likelihood surfaces for a fit.

      Specifying only the param1* arguments will initialise for a 1D fit,
      whereas specifying param2* arguments will initialise for a 2D fit.

      \param param1Nbins The number of bins for param1.
      \param param1MinValue The minimum value that param1 can take. Note that
             this should be the centre of the first bin.
      \param param1MaxValue The maximum value that param1 can take. Note that
             this should be the centre of the last bin (param1Nbins).
      \param param2Nbins The number of bins for param2. Default -1 (i.e. 1D fit).
      \param param2MinValue The minimum value that param2 can take. Note that
             this should be the centre of the first bin. Default -1 (i.e. 1D fit).
      \param param2MaxValue The maximum value that param2 can take. Note that
             this should be the centre of the last bin (param2Nbins). Default -1
             (i.e. 1D fit).

   */
   void InitFit(const int param1Nbins, const int param1StartBin, const double param1MinValue, const double param1MaxValue,
         const int param2Nbins = -1, const int param2StartBin = -1, const double param2MinValue = -1.0,
         const double param2MaxValue = -1.0);

   /**
      Find the best-fit along with the full chi2 surface for a given data set
      relative to a set of marginalisation toys.
      
      For some fits we want not only the best fit, but the entire chi2 surface;
      this method provides that capability. If you do not want the full chi2
      surface (for example, this may be the case when finding Feldman-Cousins
      critical values), then the alternative versions of this method should be
      called, specifying the starting bin(s) for the fit, which will use an
      optimized fitting procedure that will aim to find the best-fit without
      computing the entire chi2 surface.

      \param data The data against which the statistic should be computed.
      \param Ntoys The number of marginalisation toys contained within each
             batch.
      \param Nbatches The number of batches to include
             (i.e. Nbatches * Ntoys = Ntoys total).
      \param firstBatch The numeric ID for the first batch of marginalisation
             toys to be included. Note, batches should be indexec from 0.
   */
   FitResult* Fit(FitDataABC* data, const int Ntoys, const int Nbatches,
         const int firstBatch = 0);

   /**
      Find the best-fit for a given data set relative to a set of
      marginalisation toys.
      
      This version of Fit determines only the best fit and will only populate
      the chi2 surface to the extent necessary to find a satisfactory best-fit.
      As a result, this version of Fit should, in principle, provide superior
      computational performance to the version computing the entire chi2
      surface.

      \param initValue The initial value of the fit parameter at which the fit
             should begin.
      \param data The data against which the statistic should be computed.
      \param Ntoys The number of marginalisation toys contained within each
             batch.
      \param Nbatches The number of batches to include
             (i.e. Nbatches * Ntoys = Ntoys total).
      \param firstBatch The numeric ID for the first batch of marginalisation
             toys to be included. Note, batches should be indexec from 0.
   */
   FitResult* Fit(const double initValue, FitDataABC* data, const int Ntoys,
         const int Nbatches, const int firstBatch = 0);

   /**
      Find the best-fit for a given data set relative to a set of
      marginalisation toys.
      
      This version of Fit determines only the best fit and will only populate
      the chi2 surface to the extent necessary to find a satisfactory best-fit.
      As a result, this version of Fit should, in principle, provide superior
      computational performance to the version computing the entire chi2
      surface.

      \param initValue1 The initial value of the first fit parameter at which
             the fit should begin.
      \param initValue2 The initial value of the second fit parameter at which
             the fit should begin.
      \param data The data against which the statistic should be computed.
      \param Ntoys The number of marginalisation toys contained within each
             batch.
      \param Nbatches The number of batches to include
             (i.e. Nbatches * Ntoys = Ntoys total).
      \param firstBatch The numeric ID for the first batch of marginalisation
             toys to be included. Note, batches should be indexec from 0.
   */
   FitResult* Fit(const double initValue1, const double initValue2,
         FitDataABC* data, const int Ntoys, const int Nbatches,
         const int firstBatch = 0); 

   /**
      Retrieves the marginal likelihood computed by the most recent call to
      ComputeStatistics.

      \return The marginal likelihood for a data set.
   */
   double GetLikelihood() const { return this->_likelihood; }

   /**
      Retrieves the marginal chi-squared value computed by the most recent call
      to ComputeStatistics.

      \return The marginal chi-squared for a data set.
   */
   double GetChi2() const { return this->_chi2; }

private:
   /**
      Finds the minimum chi2 within a local 1D window.

      \param binInit The central bin of the window - 1 indexed.
      \param windowSize The size of the window to explore
             (windowSize x 1).
      \param gridSize The size of the full grid from which the window is
             extracted (gridSize x 1).

      \return The bin at which the minimum of this window occurs.
   */
   int CheckLocalMinimum(const int binInit, const int windowSize,
         const int gridSize, FitDataABC* data, const int Ntoys,
         const int Nbatches, const int firstBatch = 0);

   /**
      Finds the minimum chi2 within a local 2D window.

      \param binInitX A reference to the X bin at the centre of the window. This
             value will be updated with the X bin found to be the minimum of the
             window - 1 indexed.
      \param binInitY A reference to the Y bin at the centre of the window. This
             value will be updated with the X bin found to be the minimum of the
             window - 1 indexed.
      \param windowSize The size of the window to explore
             (windowSize x windowSize).
      \param gridSizeX The size of the full grid from which the window is
             extracted (gridSizeX x gridSizeY).
      \param gridSizeY The size of the full grid from which the window is
             extracted (gridSizeX x gridSizeY).

      \return The bin at which the minimum of this window occurs.
   */
   void CheckLocalMinimum(int& binX, int& binY, const int windowSize,
         const int gridSizeX, const int gridSizeY, FitDataABC* data,
         const int Ntoys, const int Nbatches, const int firstBatch = 0);

   /**
      Saves all parameter values in the input FitParamList to a tree.

      \param fpl The fit param list to save.

      \param write_tree Write the tree to an output file
   */
   void SaveParamThrows(FitParamList& fpl, bool write_tree, std::string binary_file_name);

  /**
     Read a single set of parameter throws from a T2K legacy toy throw file into the input FitParamList.

     \param fpl Store the read parameter throws in this FitParamList
     \param toy_throw_file_to_read Read throws from a pre-existing file instead of
            generating them. This is used e.g. to convert T2K legacy toy throws
            into SDK marginalisation toys.
            NOTE: As this reads thrown parameter values, statistical fluctuations
            are not copied
     \param param_name_map_file This file is used to convert SDK parameter names
            into the parameter names used by the toy_throw_file_to_read.
  */
  void ReadParamsFromThrowFile(FitParamList& fpl, std::string toy_throw_file_to_read,
                               std::string param_name_map_file, const char* options, int toy_number);

private:
   string _filePrefix; 
   FitModelABC* _model;
   double _likelihood;
   double _chi2;
   bool _isFit2D;
   TH1D* _likelihood_1D;
   TH2D* _likelihood_2D;
   TH1D* _chi2_1D;
   TH2D* _chi2_2D;
   FitResult* _fitResult;
   bool _use_simple_binning;
   bool _save_throws_to_tree;
   TTree* _tree_pars;
   int _param1_start_bin;
   int _param2_start_bin;

  // TODO: update this description - the stuff about floats is not relevant anymore
  // When calculating the marginal likelihood:
  // Rescale the likelihood by exp(scale) when sum over the toys, then scale back at the end (of ComputeStatistics())
  // Avoid precision problems w/ floats or double when chisq~200 and like=exp(-0.5*chisq) becomes too small
  // floats support numbers until exp(+88). The likelihood becomes like=exp(-0.5*chisq+88) >= exp(+88)
  // When chisq gets larger, the scaling factor can be increased, paying attention that -200 < -0.5*chisq+scale < 89
  // Now double are used for chisq and likelihood, but the scale factor could be needed anyway
   double _scale_precision = 80.;
};

} // valor

#endif

