//____________________________________________________________________________ 
/*!

\class     valor::LinearizedKineBinning

\brief     Linearized multi-dimensional kinematical binning 

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           Steve Dennis <s.r.dennis@liverpool.ac.uk>
           University of Liverpool

\created   May 27, 2016

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_linearized_multidimensional_kinematical_binning_h_
#define _valor_linearized_multidimensional_kinematical_binning_h_

#include <TNamed.h>

#include "valor/VArray/VALORArray.h"
#include "valor/VArray/VALORArrayBin.h"
#include "dune/Conventions/KineSpace.h"
#include "dune/Binning/SimpleKineBinning.h"

namespace valor {

class LinearizedKineBinning: public TNamed
{
public:
  LinearizedKineBinning();
  LinearizedKineBinning(string name, string title);
  LinearizedKineBinning(string name, string title, conv::KineSpace_t ksp, bool reco);
  virtual ~LinearizedKineBinning();

  // Read binning from file
  bool Read(string file);

  // Subspace (true or reco) of the original space for which binning is specified
  conv::KineSpace_t KineSpace(void) const;

// .................
// Perhaps next two redundant since can be obtained from above KineSpace_t 
// But could be faster to return stored result rather than recreating answer each time
// Should check how often the following two are likely to be called.

  // Number of dimensions Nd
  int NDimensions(void) const;

  // Binned kinematical variables (0, ..., Nd-1)
  vector<conv::KineVar_t> KineVar(void) const;
// ..................

  // Number of multi-dimensional bins 
  int NBins (void) const;

  // Find bin
  int FindBin (vector<double> & xarr);

  // An alternative simple binning of the same kinematical space.
  // If given, a mapping will be worked out between the `simple' and `linearized' binning schemes

  void UsingAlternativeSimpleBinningScheme(const SimpleKineBinning * alt_simple_scheme);
  int BinMapping (vector<int> & bin_in_alt_simple_scheme);

protected:


  const SimpleKineBinning * fAltSimpleKineBinning;
};

} // valor

#endif

