//____________________________________________________________________________
/*!

\class     valor::NuInt

\brief     Info on DUNE neutrino interaction correlations and prior errors

\author    Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

           Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_nu_int_h_
#define _valor_dune_nu_int_h_

#include <FitCore/CorrelatedSystematics.h>

namespace valor {

class NuInt: public CorrelatedSystematics
{
public:
  NuInt();
  virtual ~NuInt();

ClassDef(NuInt, 1)
};

} //valor

#endif
