//____________________________________________________________________________
/*!

\file      DoExperimentSetup

\brief     Sets up the experiment-specific configuration for DUNE

\author    Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

\created   September 2019

\copyright (c) 2010-2019, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_expt_specific_setup_h_
#define _valor_expt_specific_setup_h_

#include "valor/Conventions/ExperimentSetup.h"


namespace valor {
  
  // Dumb hacked class because Cling didn't play nice with the externally linked function
  // Just calls DoExperimentSetup when constructed, nothing else
  class ExperimentInitialiser {
    public:
      ExperimentInitialiser();
  };

  bool DoExperimentSetup(); // Defined as extern in SDK ExperimentSetup.h

} // valor

#endif

