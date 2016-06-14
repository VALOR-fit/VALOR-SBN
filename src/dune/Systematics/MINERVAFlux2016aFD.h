//____________________________________________________________________________
/*!

\class     valor::MINERVAFlux2016aFD

\brief     MINERvA flux-binning (for DUNE) - far detector only

\author    Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

           Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_minerva_flux_systematics_2016a_fd_h_
#define _valor_minerva_flux_systematics_2016a_fd_h_

#include "valor/FitCore/CorrelatedSystematics.h"

namespace valor {

class MINERVAFlux2016aFD: public CorrelatedSystematics
{
public:
  MINERVAFlux2016aFD();
  virtual ~MINERVAFlux2016aFD();

ClassDef(MINERVAFlux2016aFD, 1)
};

} //valor

#endif
