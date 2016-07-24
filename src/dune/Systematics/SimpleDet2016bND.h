//____________________________________________________________________________
/*!

\class     valor::SimpleDet2016bND

\brief     Simple detector error model used in early VALOR DUNE/NDTF analyses.

\author    Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

           Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_simple_detector_systematics_2016bND_h_
#define _valor_simple_detector_systematics_2016bND_h_

#include "valor/FitCore/CorrelatedSystematics.h"

namespace valor {

class SimpleDet2016bND: public CorrelatedSystematics
{
public:
  SimpleDet2016bND();
  virtual ~SimpleDet2016bND();

ClassDef(SimpleDet2016bND, 1)
};

} //valor

#endif
