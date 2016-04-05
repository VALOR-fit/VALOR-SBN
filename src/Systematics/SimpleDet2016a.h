//____________________________________________________________________________
/*!

\class     valor::SimpleDet2016a

\brief     Simple detector error model used in early VALOR DUNE/NDTF analyses.

\author    Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

           Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_simple_detector_systematics_2016a_h_
#define _valor_simple_detector_systematics_2016a_h_

#include <FitCore/CorrelatedSystematics.h>

namespace valor {

class SimpleDet2016a: public CorrelatedSystematics
{
public:
  SimpleDet2016a();
  virtual ~SimpleDet2016a();

ClassDef(SimpleDet2016a, 1)
};

} //valor

#endif
