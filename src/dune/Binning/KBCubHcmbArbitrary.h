//____________________________________________________________________________ 
/*!

\class     valor::KBCubHcmbArbitrary

\brief     Linearized multi-dimensional kinematical binning 

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           Steve Dennis <s.r.dennis@liverpool.ac.uk>
           University of Liverpool

\created   May 27, 2016

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_kinematical_binning_cuboid_honeycomb_non_edge_to_edge_h_
#define _valor_kinematical_binning_cuboid_honeycomb_non_edge_to_edge_h_

#include <TNamed.h>

#include "valor/VArray/VALORArray.h"
#include "valor/VArray/VALORArrayBin.h"
#include "dune/Conventions/KineSpace.h"

namespace valor {

class KBCubHcmbEdge2Edge;

class KBCubHcmbArbitrary: public TNamed
{
public:
  KBCubHcmbArbitrary();
  KBCubHcmbArbitrary(string name, string title, conv::KineSpace_t ksp);
  virtual ~KBCubHcmbArbitrary();

  // Read binning from file
  bool Read(string file);

  // Number of multi-dimensional bins 
  int NBins (void) const;

  // Find bin
  int FindBin (vector<double> & xarr);

  // An alternative simple binning of the same kinematical space.
  // If given, a mapping will be worked out between the `simple' and `linearized' binning schemes

  void UseEdge2EdgeBinning(const KBCubHcmbEdge2Edge * kbe2e);
  int BinMapping (vector<int> & bin_in_alt_simple_scheme);

protected:

  const KBCubHcmbEdge2Edge * fKBE2E;
};

} // valor

#endif

