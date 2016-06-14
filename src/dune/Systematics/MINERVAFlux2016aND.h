//____________________________________________________________________________
/*!

\class     valor::MINERVAFlux2016a

\brief     MINERvA flux-binning (for DUNE) - near detector only

\author    Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

           Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_minerva_flux_systematics_2016a_nd_h_
#define _valor_minerva_flux_systematics_2016a_nd_h_

#include "valor/FitCore/CorrelatedSystematics.h"

namespace valor {

class MINERVAFlux2016aND: public CorrelatedSystematics
{
public:
  MINERVAFlux2016aND();
  virtual ~MINERVAFlux2016aND();

ClassDef(MINERVAFlux2016aND, 1)
};

} //valor

#endif
