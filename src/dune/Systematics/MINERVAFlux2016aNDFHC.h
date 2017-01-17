//____________________________________________________________________________
/*!

\class     valor::MINERVAFlux2016aNDFHC

\brief     MINERvA flux-binning (for DUNE) - near detector FHC only

\author    Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

           Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_minerva_flux_systematics_2016a_nd_fhc_h_
#define _valor_minerva_flux_systematics_2016a_nd_fhc_h_

#include "valor/FitCore/CorrelatedSystematics.h"

namespace valor {

class MINERVAFlux2016aNDFHC: public CorrelatedSystematics
{
public:
  MINERVAFlux2016aNDFHC();
  virtual ~MINERVAFlux2016aNDFHC();

ClassDef(MINERVAFlux2016aNDFHC, 1)
};

} //valor

#endif
