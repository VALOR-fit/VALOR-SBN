//____________________________________________________________________________ 
/*!

\class     valor::SimpleKineBinning

\brief     Simple multi-dimensional kinematical binning 

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           Steve Dennis <s.r.dennis@liverpool.ac.uk>
           University of Liverpool

\created   May 27, 2016

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_simple_multidimensional_kinematical_binning_h_
#define _valor_simple_multidimensional_kinematical_binning_h_

#include <TNamed.h>

#include "valor/VArray/VALORArray.h"
#include "valor/VArray/VALORArrayBin.h"
#include "dune/Conventions/KineSpace.h"

namespace valor {

class SimpleKineBinning: public TNamed
{
public:
  SimpleKineBinning();
  SimpleKineBinning(string name, string title);
  SimpleKineBinning(string name, string title, conv::KineSpace_t ksp, bool reco);
  virtual ~SimpleKineBinning();

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
//.................

  // Number of bins by dimension or kinematical variable
  int NBins (int dimension     ) const;
  int NBins (conv::KineVar_t kv) const;

  // Bin edge arrays by dimension or kinematical variable
  const double *      BinEdgeArr  (int dimension     ) const;
  const double *      BinEdgeArr  (conv::KineVar_t kv) const;
  const VALORArray *  BinEdgeVArr (int dimension     ) const;
  const VALORArray *  BinEdgeVArr (conv::KineVar_t kv) const;  

  // Find bin
  int         FindBin (double x, int dimension);
  int         FindBin (double x, conv::KineVar_t kv);
  vector<int> FindBin (vector<double> & x);

protected:


};

} // valor

#endif

