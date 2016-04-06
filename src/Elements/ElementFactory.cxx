//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include <cassert>

#include <TClass.h>

#include "Messenger/Messenger.h"
#include "Elements/ElementFactory.h"

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
  conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s, string class_name)
{
  void * vbase = this->InstantiateUsingDictionaryRegistration(d,b,s,class_name);
  FitDataABC * dataset = (FitDataABC *) (vbase);
  return dataset;
}
//________________________________________________________________________________________
FitModelABC * ElementFactory::AdoptFitModel(
  conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s, string class_name)
{
  void * vbase = this->InstantiateUsingDictionaryRegistration(d,b,s,class_name);
  FitModelABC * model = (FitModelABC *) (vbase);
  return model;
}
//________________________________________________________________________________________
void * ElementFactory::InstantiateUsingDictionaryRegistration(
  conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s, string class_name)
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


