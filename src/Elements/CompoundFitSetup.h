//____________________________________________________________________________
/*!

\class     valor::CompoundFitSetup

\brief   

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\created   April 06, 2016

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_compound_fit_setup_h_
#define _valor_dune_compound_fit_setup_h_

#include <string>

#include <TXMLEngine.h>

//fmwk
#include "FitCore/FitDataABC.h"
#include "FitCore/FitModelABC.h"
//dune
#include "Conventions/BeamConf.h"
#include "Conventions/Sample.h"
#include "Conventions/Detector.h"

using namespace valor;

namespace valor {

class CompoundFitSetup
{
public:
  CompoundFitSetup();
 ~CompoundFitSetup();

  bool Read(string xmlconfig);

  FitDataABC *  AdoptFitData  (string config_file, conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s, string class_name = "valor::SingleSampleDataA"    );
  FitModelABC * AdoptFitModel (string config_file, conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s, string class_name = "valor::SingleSampleFitModelA");

private:

  bool ReadElementList (TXMLEngine* xmleng, XMLNodePointer_t top_node);
  bool ReadElement     (TXMLEngine* xmleng, XMLNodePointer_t top_node);

  void * InstantiateUsingDictionaryRegistration (string class_name);

};

} // valor

#endif

