//____________________________________________________________________________
/*!

\class     valor::SimpleDet2016b

\brief     Simple detector error model used in early VALOR DUNE/NDTF analyses.

\author    Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

           Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_simple_detector_systematics_2016b_h_
#define _valor_simple_detector_systematics_2016b_h_

#include "valor/FitCore/CorrelatedSystematics.h"

namespace valor {

class SimpleDet2016b: public CorrelatedSystematics
{
public:
  SimpleDet2016b();
  virtual ~SimpleDet2016b();

ClassDef(SimpleDet2016b, 1)
};

} //valor

#endif
