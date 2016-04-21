//____________________________________________________________________________
/*!

\class     valor::MINERVAFlux2016a

\brief     MINERvA flux systematics

\author    Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

           Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_minerva_flux_systematics_2016a_h_
#define _valor_minerva_flux_systematics_2016a_h_

#include "valor/FitCore/CorrelatedSystematics.h"

namespace valor {

class MINERVAFlux2016a: public CorrelatedSystematics
{
public:
  MINERVAFlux2016a();
  virtual ~MINERVAFlux2016a();

ClassDef(MINERVAFlux2016a, 1)
};

} //valor

#endif
