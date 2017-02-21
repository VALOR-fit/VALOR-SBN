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
      \param k The kinematic variable for which the histogram is to be produced.
      \return A 1D histogram of the specified kinematic variable.

   */
   static TH1D* Make1DHistogram(VALORArray v, SingleSampleKineBinning b,
        conv::KineVar_t k);

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
   static TH2D* Make2DOptimisedHistogram(VALORArray v, SingleSampleKineBinning b,
        std::vector<conv::KineVar_t> ks);

   /**
      Produce a 2D ROOT-compatible, simple histogram of specified kinematic
      variables from a VALORArray with a specified binning.

      \param v The VALORArray containing the spectrum to be plotted.
      \param b The binning used by the VALORArray.
      \param ks The kinematic variables for which the histogram is to be produced.
      \return A 2D histogram of the specified kinematic variables.

   */
   static TH2D* Make2DSimpleHistogram(VALORArray v, SingleSampleKineBinning b,
        std::vector<conv::KineVar_t> ks);

private:
   /**
      Integrate a VALORArray with a specified binning such that only the
      specified kinematic variables remain.

      \param v The VALORArray containing the data to be integrated.
      \param b The binning used by the VALORArray.
      \param k The kinematic variables to retain.
      \return The contracted VALORArray containing only the specified kinematic
         variables.
   */
   static VALORArray* Contract(VALORArray v, SingleSampleKineBinning b,
        std::vector<conv::KineVar_t> ks);

   /**
      Maps the bins of the specified VALORArray to a 1D ROOT-compatible histogram
      for the specified kinematic variable.

      This function assumes that the VALORArray has already been contracted to
      contain only the specified kinematic variable.

      \param v The VALORArray containing the spectrum to be plotted.
      \param b The binning used by the VALORArray.
      \param k The kinematic variable for which the histogram is to be produced.
      \return A 1D histogram of the specified kinematic variable.
   */
   static TH1D* Remap1D(VALORArray v, SingleSampleKineBinning b,
         conv::KineVar_t k);

   /**
      Maps the bins of the specified VALORArray to a 2D ROOT-compatible histogram
      for the specified kinematic variable.

      This function assumes that the VALORArray has already been contracted to
      contain only the specified kinematic variable.

      Note that the ROOT histogram produced by this function should be used only
      for plotting purposes, as mapping from optimised to ROOT-compatible binning
      is not guaranteed to conserve total event counts.

      \param v The VALORArray containing the spectrum to be plotted.
      \param b The binning used by the VALORArray.
      \param ks The kinematic variables for which the histogram is to be produced.
      \return A 2D histogram of the specified kinematic variables.
   */
   static TH2D* RemapOptimised2D(VALORArray v, SingleSampleKineBinning b,
         std::vector<conv::KineVar_t> ks);

   /**
      Maps the bins of the specified VALORArray to a 2D ROOT-compatible histogram
      for the specified kinematic variable.

      This function assumes that the VALORArray has already been contracted to
      contain only the specified kinematic variable.

      \param v The VALORArray containing the spectrum to be plotted.
      \param b The binning used by the VALORArray.
      \param ks The kinematic variables for which the histogram is to be produced.
      \return A 2D histogram of the specified kinematic variables.
   */
   static TH2D* RemapSimple2D(VALORArray v, SingleSampleKineBinning b,
         std::vector<conv::KineVar_t> ks);

private:
   UtlBinning(){ }
};

}
}

#endif

