//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include <cassert>

#include <TClass.h>

#include "Messenger/Messenger.h"

#include "Elements/CompoundFitSetup.h"
#include "Elements/SingleSampleFitDataABC.h"
#include "Elements/SingleSampleFitModelABC.h"

using namespace valor;

//________________________________________________________________________________________
CompoundFitSetup::CompoundFitSetup(void)
{

}
//________________________________________________________________________________________
CompoundFitSetup::~CompoundFitSetup(void)
{

}
//________________________________________________________________________________________
bool CompoundFitSetup::Read(string xmlconfig)
{
// It reads a list of "elements" (sample
// 
// .....................................................................
// <?xml version="1.0"?>
//
// <element_list name="DUNE-NDFit">
//
//    <element>
//        <detector>     dunend                       </detector>
//        <beam>         fhc                          </beam>
//        <sample>       numuccincl                   </sample>
//        <data>         data.xml                     </data>
//        <mc>           mc_production.xml            </mc>
//        <data_class>   valor::SingleSampleDataA     </data_class>
//        <model_class>  valor::SingleSampleFitModelA </model_class>
//    </element>
//
// </element_list>
//
// ......................................................................
//


}
//________________________________________________________________________________________
FitDataABC * CompoundFitSetup::AdoptFitData(
  string config_file, 
  conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s, string class_name)
{
  void * vbase = this->InstantiateUsingDictionaryRegistration(class_name);
  SingleSampleFitDataABC * s_dataset = (SingleSampleFitDataABC *) (vbase);
  s_dataset->Configure(d,b,s);
  s_dataset->Read(config_file);
  FitDataABC * dataset = (FitDataABC *) (s_dataset);
  return dataset;
}
//________________________________________________________________________________________
FitModelABC * CompoundFitSetup::AdoptFitModel(
  string config_file, 
  conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s, string class_name)
{
  void * vbase = this->InstantiateUsingDictionaryRegistration(class_name);
  SingleSampleFitModelABC * s_model = (SingleSampleFitModelABC *) (vbase);
  s_model->Configure(d,b,s);
  s_model->Read(config_file);
  FitModelABC * model = (FitModelABC *) (s_model);
  return model;
}
//________________________________________________________________________________________
void * CompoundFitSetup::InstantiateUsingDictionaryRegistration(string class_name)
{
  TClass * tclass = TClass::GetClass(class_name.c_str());
  if(!tclass) {
     LOG("CompoundFitSetup", pERROR) 
         << "Failed getting class = " << class_name;
     return 0;
  }
  void * vbase = tclass->New();
  if(!vbase) {
     LOG("CompoundFitSetup", pERROR) 
         << "Failed instantiating class = " << class_name;
     return 0;
  }
  return vbase;
}
//________________________________________________________________________________________


