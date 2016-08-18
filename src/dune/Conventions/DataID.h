//____________________________________________________________________________
/*!

\class     valor::DataID

\brief     Simple struct, to bundle together the information needed identify a fitted sample: detector+beam+selection
           I am far from wedded to that name - we can update it when we have a better idea.

\author    Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool
          
\created   August 2016

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_dataid_h_
#define _valor_dune_dataid_h_

#include <string>

#include <TObject.h>

#include "dune/Conventions/DuneBuild.h"

#include "dune/Conventions/Sample.h"
#include "dune/Conventions/Detector.h"
#include "dune/Conventions/BeamConf.h"

namespace valor {
  
struct DataID
{
  public:
    conv::Detector_t detector;
    conv::BeamConf_t beamconf;
    conv::Sample_t   sample;
    
    DataID(conv::Detector_t d = conv::kdUndefined, conv::BeamConf_t b = conv::kbUndefined, conv::Sample_t s = conv::ksUndefined);
    
  ClassDef(DataID,1);
};

// Comparison
bool operator==(const DataID& lhs, const DataID& rhc);

namespace util {
  std::string AsString      (const DataID & obj);
  std::string DataIDAsString(const DataID & obj);
}

} // valor
  
#endif  //_valor_dune_dataid_h_

