//____________________________________________________________________________
/*!

\class     valor::NuFlux

\brief     Info on DUNE neutrino flux correlations and prior errors

\author    Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

           Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_nu_flux_h_
#define _valor_dune_nu_flux_h_

#include "valor/FitCore/CorrelatedSystematics.h"

namespace valor {

class NuFlux: public CorrelatedSystematics
{
public:
  NuFlux();
  virtual ~NuFlux();

ClassDef(NuFlux, 1)
};

} //valor

#endif
