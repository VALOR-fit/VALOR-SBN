//____________________________________________________________________________
/*!
   
\class     valor::ParameterSet
      
\brief     A singleton to hold the set of parameters currently being used.
   
\author   Steve Dennis <s.r.dennis \at liverpool.ac.uk>
          University of Liverpool

\created  May 2016

\copyright (c) 2010-2016, The VALOR group.

*/
//____________________________________________________________________________
   
#ifndef _valor_parameter_set_h_
#define _valor_parameter_set_h_

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "dune/Conventions/FitParamNew.h"

namespace valor {

class ParameterSet
{
public:

  static ParameterSet * MutableInstance();
  static const ParameterSet * Instance();
  
  void ReadXML(std::string xml_path);
  
  const std::vector<FitParamNew> & GetParams() const;
  
  
private:
  
  std::vector<FitParamNew> fParams;
  
  ParameterSet();
  ParameterSet(const ParameterSet &) {};
 ~ParameterSet() {};

  static ParameterSet * fInstance;

  struct Cleaner {
      void DummyMethodAndSilentCompiler() { }
      ~Cleaner() {
         if (ParameterSet::fInstance !=0) {
            delete ParameterSet::fInstance;
            ParameterSet::fInstance = 0;
         }
      }
  };
  friend struct Cleaner;
  
};

} // valor

#endif
