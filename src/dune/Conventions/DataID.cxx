//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

ChangeLog:

*/
//________________________________________________________________________________________

#include "TString.h"
//dune
#include "dune/Conventions/DataID.h"

using namespace valor;
using namespace valor::conv;

//________________________________________________________________________________________
valor::DataID::DataID(Detector_t d, BeamConf_t b, Sample_t s)
 : detector(d),beamconf(b),sample(s)
{
  
}
//________________________________________________________________________________________
std::string util::AsString(const DataID & o)
{
  TString total = TString::Format("%s_%s_%s",
    util::AsString(o.detector).c_str(),
    util::AsString(o.beamconf).c_str(),
    util::AsString(o.sample  ).c_str());
  
  return std::string(total.Data());
}
//________________________________________________________________________________________
std::string util::DataIDAsString(const DataID & o)
{return util::AsString(o);}
//________________________________________________________________________________________
bool valor::operator==(const DataID & lhs, const DataID & rhs)
{
  return ( (lhs.detector == rhs.detector) && 
           (lhs.beamconf == rhs.beamconf) && 
           (lhs.sample   == rhs.sample  ) );
}
//________________________________________________________________________________________
