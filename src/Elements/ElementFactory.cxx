//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include <cassert>

#include <TClass.h>

#include "Messenger/Messenger.h"

#include "Elements/ElementFactory.h"
#include "Elements/SingleSampleFitDataABC.h"
#include "Elements/SingleSampleFitModelABC.h"

using namespace valor;

//________________________________________________________________________________________
ElementFactory * ElementFactory::fgInstance = 0;
//________________________________________________________________________________________
ElementFactory::ElementFactory(void)
{
  fgInstance =  0;
}
//________________________________________________________________________________________
ElementFactory::~ElementFactory(void)
{
  fgInstance = 0;
}
//________________________________________________________________________________________
ElementFactory * ElementFactory::Instance()
{
  if(fgInstance == 0) {
    static ElementFactory::Cleaner cleaner;
    cleaner.DummyMethodAndSilentCompiler();
    fgInstance = new ElementFactory;
  }
  return fgInstance;
}
//________________________________________________________________________________________
FitDataABC * ElementFactory::AdoptFitData(
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
FitModelABC * ElementFactory::AdoptFitModel(
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
void * ElementFactory::InstantiateUsingDictionaryRegistration(string class_name)
{
  TClass * tclass = TClass::GetClass(class_name.c_str());
  if(!tclass) {
     LOG("ElementFactory", pERROR) 
         << "Failed getting class = " << class_name;
     return 0;
  }
  void * vbase = tclass->New();
  if(!vbase) {
     LOG("ElementFactory", pERROR) 
         << "Failed instantiating class = " << class_name;
     return 0;
  }
  return vbase;
}
//________________________________________________________________________________________


