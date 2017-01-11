//____________________________________________________________________________
/*!

\class     valor::VALORInt2017a

\brief     VALOR neutrino interaction model systematics

\author    Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

           Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\copyright (c) 2010-2017, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_neutrino_interaction_systematics_2017a_h_
#define _valor_neutrino_interaction_systematics_2017a_h_

#include "valor/FitCore/CorrelatedSystematics.h"

namespace valor {

class VALORInt2017a: public CorrelatedSystematics
{
public:
  VALORInt2017a();
  virtual ~VALORInt2017a();

ClassDef(VALORInt2017a, 1)
};

} //valor

#endif
