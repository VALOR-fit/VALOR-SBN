//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include <cassert>

#include <TXMLEngine.h>
#include <TClass.h>

// fmwk
#include "Messenger/Messenger.h"
#include "Utilities/UtlSystem.h"
#include "Utilities/UtlStr.h"
//#include "FitCore/CompoundFitData.h"
#include "FitCore/CompoundFitModel.h"
// dune
#include "Elements/CompoundFitElements.h"
#include "Elements/SingleSampleFitDataABC.h"
#include "Elements/SingleSampleFitModelABC.h"

using namespace valor;

//________________________________________________________________________________________
CompoundFitElements::CompoundFitElements(void)
{
  this->Init();
}
//________________________________________________________________________________________
CompoundFitElements::~CompoundFitElements(void)
{
  this->Clean();
}
//________________________________________________________________________________________
bool CompoundFitElements::Read(string xmlfile)
{
// It reads a list of fit datasets and models and setups compound datasets and fit models.
// The following XML schema is expected.
// 
// .....................................................................
// <?xml version="1.0"?>
//
// <valor>
//   <element_list name="DUNE-NDFit">
//
//      <element name="blah">
//         <detector>     dunend                       </detector>
//         <beam>         fhc                          </beam>
//         <sample>       numuccincl                   </sample>
//         <observable>   Ereco,yreco                  </observable>
//         <data>         data.xml                     </data>
//         <mc>           mc_production.xml            </mc>
//         <data_class>   valor::GenericSingleSampleData     </data_class>
//         <model_class>  valor::GenericSingleSampleFitModel </model_class>
//      </element>
//
//   </element_list>
// </valor>
// ......................................................................
//

  this->Book();

  LOG("CompoundFitElements", pNOTICE) 
    << "Reading compound fit setup from XML file [" << xmlfile << "]";

  // Parse the input XML configuration file
  TXMLEngine* xmleng = new TXMLEngine;   
  XMLDocPointer_t xmldoc = xmleng->ParseFile(xmlfile.c_str());
  if (xmldoc==0) {
    LOG("CompoundFitElements", pERROR) 
      << "Can not parse input XML file [" << xmlfile << "]";
    delete xmleng;
    util::Die(1); return false;
  }
  XMLNodePointer_t root_node = xmleng->DocGetRootElement(xmldoc);

  XMLNodePointer_t curr_node = xmleng->GetChild(root_node);
  while(curr_node) {
    string curr_node_name = xmleng->GetNodeName(curr_node);
    if(curr_node_name == "element_list") {
       string list_name = xmleng->GetAttr(curr_node,"name");
       LOG("CompoundFitElements", pNOTICE) << "Found element list named: " << list_name;
       this->ReadElementList(xmleng,curr_node);
    }
    curr_node = xmleng->GetNext(curr_node);
  }

  delete xmleng;

  return true;
}
//________________________________________________________________________________________
bool CompoundFitElements::ReadElementList(TXMLEngine* xmleng, XMLNodePointer_t top_node)
{
  XMLNodePointer_t curr_node = xmleng->GetChild(top_node);
  while(curr_node) {
      string curr_node_name = xmleng->GetNodeName(curr_node);
      if(curr_node_name == "element") {
        string element_name = xmleng->GetAttr(curr_node,"name");
        LOG("CompoundFitElements", pNOTICE) << "Found element named: " << element_name;	
        bool ok = this->ReadElement(xmleng,curr_node);
        if(!ok) return false;
      }
      curr_node = xmleng->GetNext(curr_node);
  }
  return true;
}
//________________________________________________________________________________________
bool CompoundFitElements::ReadElement(TXMLEngine* xmleng, XMLNodePointer_t top_node)
{
  string detector_name    = "";
  string beam_name        = "";
  string sample_name      = "";
  string observable_name  = "";
  string data_file        = "";
  string mc_file          = "";
  string data_class       = "";
  string model_class      = "";

  XMLNodePointer_t curr_node = xmleng->GetChild(top_node);
  while(curr_node) {
      string curr_node_name = xmleng->GetNodeName(curr_node);
      if(xmleng->GetNodeContent(curr_node)) {
        string content = util::TrimSpaces(xmleng->GetNodeContent(curr_node));
        LOG("CompoundFitElements", pNOTICE) << curr_node_name << " --> " << content;
        if(curr_node_name == "detector"   ) { detector_name   = content; }
        if(curr_node_name == "beam"       ) { beam_name       = content; }
        if(curr_node_name == "sample"     ) { sample_name     = content; }
        if(curr_node_name == "observable" ) { observable_name = content; }
        if(curr_node_name == "data"       ) { data_file       = content; }
        if(curr_node_name == "mc"         ) { mc_file         = content; }
        if(curr_node_name == "data_class" ) { data_class      = content; }
        if(curr_node_name == "model_class") { model_class     = content; }
      }
      curr_node = xmleng->GetNext(curr_node);
  }

  conv::Detector_t  detector   = util::DetectorFromString(detector_name);
  conv::BeamConf_t  beam       = util::BeamConfFromString(beam_name);
  conv::Sample_t    sample     = util::SampleFromString(sample_name);
  conv::KineSpace_t observable = util::KineSpaceFromString(observable_name);

  bool success = true;
  if (detector   == conv::kdUndefined ) {
    LOG("CompoundFitElements",pERROR)<<"Unknown detector: "<<detector_name;
    success = false;
  }
  if (beam       == conv::kbUndefined ) {
    LOG("CompoundFitElements",pERROR)<<"Unknown beam conf: "<<beam_name;
    success = false;
  }
  if (sample     == conv::ksUndefined ) {
    LOG("CompoundFitElements",pERROR)<<"Unknown sample: "<<sample_name;
    success = false;
  }
  if (observable == conv::kspUndefined) {
    LOG("CompoundFitElements",pERROR)<<"Unknown observable: "<<observable_name;
    success = false;
  }
  
  if (success) {
    FitDataABC *  fit_data  = 
       this->AdoptFitData (data_file, detector, beam, sample, observable, data_class );
    FitModelABC * fit_model = 
       this->AdoptFitModel(mc_file,   detector, beam, sample, observable, model_class);

    assert(fit_data);
    assert(fit_model);
    
    fCompoundFitModel->AddSubModel(fit_model);
    //~ fCompoundFitData ->AddSubData (fit_data);
  }

  return success;
}
//________________________________________________________________________________________
void CompoundFitElements::Init(void)
{
//fCompoundFitData  = 0;
  fCompoundFitModel = 0;
}
//________________________________________________________________________________________
void CompoundFitElements::Book(void)
{
//fCompoundFitData  = new CompoundFitData;
  fCompoundFitModel = new CompoundFitModel;
}
//________________________________________________________________________________________
void CompoundFitElements::Clean(void)
{
//if(fCompoundFitData ) delete fCompoundFitData;
  if(fCompoundFitModel) delete fCompoundFitModel;
}
//________________________________________________________________________________________
FitDataABC * CompoundFitElements::AdoptFitData(
  string config_file, 
  conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s, conv::KineSpace_t o, 
  string class_name)
{
  void * vbase = this->InstantiateUsingDictionaryRegistration(class_name);
  SingleSampleFitDataABC * s_dataset = (SingleSampleFitDataABC *) (vbase);
  s_dataset->Configure(d,b,s,o);
  s_dataset->Read(config_file);
  FitDataABC * dataset = (FitDataABC *) (s_dataset);
  return dataset;
}
//________________________________________________________________________________________
FitModelABC * CompoundFitElements::AdoptFitModel(
  string config_file, 
  conv::Detector_t d, conv::BeamConf_t b, conv::Sample_t s, conv::KineSpace_t o,
  string class_name)
{
  void * vbase = this->InstantiateUsingDictionaryRegistration(class_name);
  SingleSampleFitModelABC * s_model = (SingleSampleFitModelABC *) (vbase);
  s_model->Configure(d,b,s,o);
  s_model->Read(config_file);
  FitModelABC * model = (FitModelABC *) (s_model);
  return model;
}
//________________________________________________________________________________________
void * CompoundFitElements::InstantiateUsingDictionaryRegistration(string class_name)
{
  TClass * tclass = TClass::GetClass(class_name.c_str());
  if(!tclass) {
     LOG("CompoundFitElements", pERROR) 
         << "Failed getting class = " << class_name;
     return 0;
  }
  void * vbase = tclass->New();
  if(!vbase) {
     LOG("CompoundFitElements", pERROR) 
         << "Failed instantiating class = " << class_name;
     return 0;
  }
  return vbase;
}
//________________________________________________________________________________________

