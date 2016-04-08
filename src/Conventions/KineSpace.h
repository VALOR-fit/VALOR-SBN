//____________________________________________________________________________
/*!

\class     valor::conv::KineSpace_t

\brief     Kinematic variable space enumeration (set of KineVar_t)

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory
          
\created   April 08, 2016

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_kine_space_h_
#define _valor_dune_kine_space_h_

#include <TROOT.h>
//
#include "Conventions/KineVar.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace valor {
namespace conv {

typedef enum EKineSpace
{
   kspUndefined = -1, 
   kspEtrue,           // 1D: true neutrino energy
   kspEreco,           // 1D: reconstructed neutrino energy
   kspEvis,            // 1D: visible neutrino energy
   kspYreco,           // 1D: reconstructed inelasticity (y)
   kspErecoYreco       // 2D: reconstructed energy, inelasticity
   // ...
   // ...
   // ...
} 
KineSpace_t; 

} // conv


//
// Associated utilities
//
namespace util {

  string                  AsString        (conv::KineSpace_t ks);
  string                  AsStringTeX     (conv::KineSpace_t ks, bool root);
  bool                    IsPureReco      (conv::KineSpace_t ks);
  bool                    IsPureTrue      (conv::KineSpace_t ks);
  bool                    IsMixedRecoTrue (conv::KineSpace_t ks);
  int                     NDim            (conv::KineSpace_t ks);
  int                     NDimReco        (conv::KineSpace_t ks);
  int                     NDimTrue        (conv::KineSpace_t ks);
  vector<conv::KineVar_t> KineVar         (conv::KineSpace_t ks);
  vector<conv::KineVar_t> KineVarReco     (conv::KineSpace_t ks);
  vector<conv::KineVar_t> KineVarTrue     (conv::KineSpace_t ks);

} // util

} // valor
  
#endif 

