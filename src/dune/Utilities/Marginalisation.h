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
   Marginalisation(CompoundFitElements& elements, string filePrefix);

   /**
      Constructs a Marginalisation object.

      \param model The FitModelABC object used to generate the MC spectra.
      \param filePrefix The prefix to be used for the marginalisation toy files
             to be written.
   */
   Marginalisation(FitModelABC& model, string filePrefix);

   /**
      Destructor.

      This class does not own any of the objects assigned to class variables,
      so it does not destroy them.
   */
   virtual ~Marginalisation();

   /**
      Builds a batch of marginalisation toys.

      To facilitate incremental building of marginalisation toys, a complete set
      of marginalisation toys can be split into batches, each of which should
      have the same number of toys in it.

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
   */
   void BuildToys(const int batch, const int Ntoys, FitParamList& fpl,
         bool randomizeSystematics = true,
         const char* options = "randomize-all;prefit-errors",
         bool rethrowUnphysical = true);

   /**
      Computes the marginal likelihood and chi-squared statistics for a given
      data set relative to a set of marginalisation toys.

      \param data The data against which the statistic should be computed.
      \param Ntoys The number of marginalisation toys contained within each
             batch.
      \param Nbatches The number of batches to include
             (i.e. Nbatches * Ntoys = Ntoys total).
      \param firstBatch The numeric ID for the first batch of marginalisation
             toys to be included. Note, batches should be indexec from 0.
   */
   void ComputeStatistics(FitDataABC* data, const int Ntoys, const int Nbatches,
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
   string _filePrefix; 
   FitModelABC* _model;
   double _likelihood;
   double _chi2;
};

} // valor

#endif

