//____________________________________________________________________________ 
/*!

\class     valor::KBCuboidHoneycombEdge2Edge

\brief     Multi-dimensional kinematical binning 
           Adjacent bins share one full side (as in `edge-to-edge tiling',
           https://en.wikipedia.org/wiki/Tessellation)

           The binning is read from XML files.
           Th eXML schema is given by the following example:

           ...............................................
           <?xml version="1.0" encoding="ISO-8859-1"?>

           <binning>
              <type> edge-to-edge </type>
              <ndimensions> 5 </ndimensions>
              <dimension_0>
                 <bin_size> fixed </bin_size>
                 <nbins> 20 </nbins>
                 <range> 0.,40. </range>
              </dimension_0>
              <dimension_1>
                 <bin_size> variable </bin_size>
                 <nbins> 11 </nbins>
                 <bin_edges>
                     0.0,  1.2,   1.6,   2.0,   3.0,   5.0,
                    10.0, 20.0, 100.0, 110.0, 125.0, 200.0
                 </bin_edges>
              </dimension_1>
              ...
              ...
           </binning>
           ...............................................

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           Steve Dennis <s.r.dennis@liverpool.ac.uk>
           University of Liverpool

\created   May 27, 2016

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_kinematical_binning_cuboid_honeycomb_edge_to_edge_h_
#define _valor_kinematical_binning_cuboid_honeycomb_edge_to_edge_h_

#include <vector>
#include <map>

#include <TNamed.h>

#include "valor/VArray/VALORArray.h"
#include "valor/VArray/VALORArrayBin.h"
#include "dune/Conventions/KineSpace.h"

using std::vector;
using std::map;

namespace valor {

class KBCuboidHoneycombEdge2Edge: public TNamed
{
public:
  KBCuboidHoneycombEdge2Edge();
  KBCuboidHoneycombEdge2Edge(string name, string title, conv::KineSpace_t ksp);
  virtual ~KBCuboidHoneycombEdge2Edge();

  // Read binning from file
  bool Read(string file);

  // Number of bins by dimension or kinematical variable
  unsigned int NBins (unsigned int dimension ) const;
  unsigned int NBins (conv::KineVar_t kv     ) const;

  // Bin edge arrays by dimension or kinematical variable
  const double *      BinEdgeArr  (unsigned int dimension ) const;
  const double *      BinEdgeArr  (conv::KineVar_t kv     ) const;
  const VALORArray *  BinEdgeVArr (unsigned int dimension ) const;
  const VALORArray *  BinEdgeVArr (conv::KineVar_t kv     ) const;  

  // Find bin
  unsigned int         FindBin (double x, unsigned int dimension);
  unsigned int         FindBin (double x, conv::KineVar_t kv);
  vector<unsigned int> FindBin (vector<double> & x);

  unsigned int Dimension(conv::KineVar_t kv) const;

protected:

  conv::KineSpace_t                  fKineSpace;    // kinematical space
  unsigned int                       fNDimensions;  // number of dimensions
  vector<conv::KineVar_t>            fKineVars;     // kinematical variables in given space
  map<conv::KineVar_t, unsigned int> fKineVar2Dim;  // kinematical variable -> dimension
  vector<VALORArray*>                fBinEdges;     // bin edges
};

} // valor

#endif

