//____________________________________________________________________________
/*!

\class     valor::NuDet

\brief     Info on DUNE neutrdeto detector correlations and prior errors

\author    Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

           Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_nu_det_h_
#define _valor_dune_nu_det_h_

#include <FitCore/CorrelatedSystematics.h>

namespace valor {

class NuDet: public CorrelatedSystematics
{
public:
  NuDet();
  virtual ~NuDet();

ClassDef(NuDet, 1)
};

} //valor

#endif
