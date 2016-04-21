//____________________________________________________________________________
/*!

\class     valor::VALORInt2016a

\brief     VALOR neutrino interaction model systematics

\author    Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

           Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_neutrino_interaction_systematics_2016a_h_
#define _valor_neutrino_interaction_systematics_2016a_h_

#include "valor/FitCore/CorrelatedSystematics.h"

namespace valor {

class VALORInt2016a: public CorrelatedSystematics
{
public:
  VALORInt2016a();
  virtual ~VALORInt2016a();

ClassDef(VALORInt2016a, 1)
};

} //valor

#endif
