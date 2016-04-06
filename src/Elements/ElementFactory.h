//____________________________________________________________________________
/*!

\class     valor::ElementFactory

\brief   

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\created   April 06, 2016

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_element_factory_h_
#define _valor_dune_element_factory_h_

#include <string>

//fmwk
#include "FitCore/FitDataABC.h"
#include "FitCore/FitModelABC.h"
//dune
#include "Conventions/BeamConf.h"
#include "Conventions/Sample.h"
#include "Conventions/Detector.h"

using namespace valor;

namespace valor {

class ElementFactory
{
public:
  static ElementFactory * Instance();

  FitDataABC *  AdoptFitData  (conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s, string class_name = "valor::SingleSampleDataA"    );
  FitModelABC * AdoptFitModel (conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s, string class_name = "valor::SingleSampleFitModelA");

private:
  ElementFactory(void);
  ElementFactory(const ElementFactory & elf);
  virtual ~ElementFactory();

  // self
  static ElementFactory * fgInstance;

  //
  void * InstantiateUsingDictionaryRegistration (conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s, string class_name);

  // singleton cleaner
  struct Cleaner {
      void DummyMethodAndSilentCompiler() { }
      ~Cleaner() {
         if (ElementFactory::fgInstance !=0) {
            delete ElementFactory::fgInstance;
            ElementFactory::fgInstance = 0;
         }
      }
  };
  friend struct Cleaner;
};

} // valor

#endif

