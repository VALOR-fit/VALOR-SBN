//____________________________________________________________________________
/*!

\class     valor::CompoundFitElements

\brief   

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\created   April 06, 2016

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_compound_fit_elements_h_
#define _valor_dune_compound_fit_elements_h_

#include <string>

#include <TXMLEngine.h>

//fmwk
#include "FitCore/FitDataABC.h"
#include "FitCore/FitModelABC.h"
//dune
#include "Conventions/BeamConf.h"
#include "Conventions/Sample.h"
#include "Conventions/Detector.h"
#include "Conventions/KineSpace.h"

using namespace valor;

namespace valor {

class CompoundFitElements
{
public:
  CompoundFitElements();
 ~CompoundFitElements();

  bool Read(string xmlconfig);

//FitDataABC *  FitData  (void) const { return fCompoundFitData;  }
  FitModelABC * FitModel (void) const { return fCompoundFitModel; }

private:

  void Init  (void);
  void Book  (void);
  void Clean (void);

  bool ReadElementList (TXMLEngine* xmleng, XMLNodePointer_t top_node);
  bool ReadElement     (TXMLEngine* xmleng, XMLNodePointer_t top_node);

  FitDataABC *  AdoptFitData  (string config_file, conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s, conv::KineSpace_t o, string class_name);
  FitModelABC * AdoptFitModel (string config_file, conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s, conv::KineSpace_t o, string class_name);
  void *        InstantiateUsingDictionaryRegistration (string class_name);

//FitDataABC *  fCompoundFitData;
  FitModelABC * fCompoundFitModel;
};

} // valor

#endif

