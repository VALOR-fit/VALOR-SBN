/*!

\class     valor::util::UtlBinning

\brief     Contains utility functions for integrating and plotting VALORArrays
           based on Mondrian and Edge2Edge binning.

\author    Andy Chappell <A.Chappell \t warwick.ac.uk
           University of Warwick
          
\created   Feb 21, 2017

\copyright (c) 2010-2017, The VALOR group

*/

#ifndef valor_util_binning
#define valor_util_binning

#include <vector>

#include "TH1D.h"
#include "TH2D.h"

// valor
#include "valor/Conventions/KineSpace.h"

// dune
#include "dune/Utilities/SingleSampleKineBinning.h"

namespace valor
{
namespace util
{

class UtlBinning
{
public:
   /**
      Produce a 1D ROOT-compatible histogram of the specified kinematic variable
      from a VALORArray with a specified binning.

      \param v The VALORArray containing the spectrum to be plotted.
      \param b The binning used by the VALORArray.
      \param ks The kinematic space for which the histogram is to be produced.
      \return A 1D histogram of the specified kinematic variable.

   */
   static TH1D* Make1DHistogram(const VALORArray& v,
         const SingleSampleKineBinning& b, const conv::KineSpace_t ks);

   /**
      Produce a 2D ROOT-compatible, optimised histogram of specified kinematic
      variables from a VALORArray with a specified binning.

      Note that the ROOT histogram produced by this function should be used only
      for plotting purposes, as mapping from optimised to ROOT-compatible binning
      is not guaranteed to conserve total event counts.

      \param v The VALORArray containing the spectrum to be plotted.
      \param b The binning used by the VALORArray.
      \param ks The kinematic variables for which the histogram is to be produced.
      \return A 2D histogram of the specified kinematic variables.

   */
   static TH2D* Make2DOptimisedHistogram(const VALORArray& v,
         const SingleSampleKineBinning& b,
         const std::vector<conv::KineVar_t>& ks);

   /**
      Produce a 2D ROOT-compatible, simple histogram of specified kinematic
      variables from a VALORArray with a specified binning.

      \param v The VALORArray containing the spectrum to be plotted.
      \param b The binning used by the VALORArray.
      \param ks The kinematic variables for which the histogram is to be produced.
      \return A 2D histogram of the specified kinematic variables.

   */
   static TH2D* Make2DSimpleHistogram(const VALORArray& v,
         const SingleSampleKineBinning& b,
         const std::vector<conv::KineVar_t>& ks);

private:
   /**
      Integrate a VALORArray with a specified binning such that only the
      specified kinematic variables remain.

      \param v The VALORArray containing the data to be integrated.
      \param currentBinning The current binning used by the VALORArray.
      \param targetBinning The target binning to be used by the new VALORArray.
      \param k The kinematic variables to retain.
      \return The contracted VALORArray containing only the specified kinematic
         variables.
   */
   static VALORArray* Contract(const VALORArray& v,
         const SingleSampleKineBinning& curentBinning,
         const KBCubHcmbEdge2Edge& targetBinning);

   /**
      Maps the events associated with the specified binning to a 1D
      ROOT-compatible histogram.

      \param events The spectrum corresponding to the simple binning.
      \param b The simple binning.
      \return A ROOT-compatible 1D histogram representing the simple binning.
   */
   static TH1D* Remap1D(const double* events, const KBCubHcmbEdge2Edge& b);

   /**
      Maps the events associated with the specified binning to a 2D
      ROOT-compatible histogram.

      Note that the ROOT histogram produced by this function should be used only
      for plotting purposes, as mapping from optimised to ROOT-compatible binning
      is not guaranteed to conserve total event counts.

      \param events The spectrum corresponding to the optimised binning.
      \param b The optimised binning.
      \return A ROOT-compatible 2D histogram representing the optimised binning.
   */
   static TH2D* RemapOptimised2D(const double* events,
         const KBCubHcmbMondrian& b);

   /**
      Maps the events associated with the specified binning to a 2D
      ROOT-compatible histogram.

      \param events The spectrum corresponding to the optimised binning.
      \param b The optimised binning.
      \return A ROOT-compatible 2D histogram representing the simple binning.
   */
   static TH2D* RemapSimple2D(const double* events, const KBCubHcmbEdge2Edge& b);

   /**
      Returns a permutation of all of the bin indices within the specified
      kinematic space.

      This method is a helper method for performing integration within
      multidimensional  kinematic variables, because VALORArray can only
      integrate over entire reconstructed or true space.

      \param binning The kinematic binning for which the permutation will be
         applied.
      \param ks The kinematic space for which bin indices are to be permuted.
      \return The permutation of all bins in the kinematic space.
   */
   static std::vector<std::vector<int>> BinPermutation(
         const KBCubHcmbEdge2Edge& binning, const conv::KineSpace_t ks);

   /**
      Returns a permutation of all of the bin indices within the specified
      kinematic space.

      This method is a helper method for performing integration within
      multidimensional  kinematic variables, because VALORArray can only
      integrate over entire reconstructed or true space.

      \param binning The kinematic binning for which the permutation will be
         applied.
      \param kvs The kinematic variables for which bin indices are to be permuted.
      \return The permutation of all bins in the kinematic space.
   */
   static std::vector<std::vector<int>> BinPermutation(
         const KBCubHcmbEdge2Edge& binning,
         const std::vector<conv::KineVar_t>& kvs);

private:
   UtlBinning(){ }
};

}
}

#endif

