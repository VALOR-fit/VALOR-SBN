//____________________________________________________________________________
/*!

\class     valor::DuneND2017a

\brief     Detector error model used in VALOR DUNE/NDTF PT4 analysis.

\author    Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

           Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\copyright (c) 2010-2017, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_nd_detector_systematics_2017a_h_
#define _valor_dune_nd_detector_systematics_2017a_h_

#include "valor/FitCore/CorrelatedSystematics.h"

namespace valor {

class DuneND2017a: public CorrelatedSystematics
{
public:
  DuneND2017a();
  virtual ~DuneND2017a();

ClassDef(DuneND2017a, 1)
};

} //valor

#endif
