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
// dune
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
bool CompoundFitSetup::Read(string xmlfile)
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
//         <data>         data.xml                     </data>
//         <mc>           mc_production.xml            </mc>
//         <data_class>   valor::SingleSampleDataA     </data_class>
//         <model_class>  valor::SingleSampleFitModelA </model_class>
//      </element>
//
//   </element_list>
// </valor>
// ......................................................................
//

  LOG("CompoundFitSetup", pNOTICE) 
    << "Reading compound fit setup from XML file [" << xmlfile << "]";

  // Parse the input XML configuration file
  TXMLEngine* xmleng = new TXMLEngine;   
  XMLDocPointer_t xmldoc = xmleng->ParseFile(xmlfile.c_str());
  if (xmldoc==0) {
    LOG("CompoundFitSetup", pERROR) 
      << "Can not parse input XML file [" << xmlfile << "]";
    delete xmleng;
    util::Die(1); return false;
  }
  XMLNodePointer_t root_node = xmleng->DocGetRootElement(xmldoc);

  XMLNodePointer_t curr_node = xmleng->GetChild(root_node);
  while(curr_node) {
    string curr_node_name = xmleng->GetNodeName(curr_node);
    if(curr_node_name == "element_list") {
       LOG("CompoundFitSetup", pNOTICE) << "Found element list named: ";
       this->ReadElementList(xmleng,curr_node);
    }
    curr_node = xmleng->GetNext(curr_node);
  }

  delete xmleng;

  return true;
}
//________________________________________________________________________________________
bool CompoundFitSetup::ReadElementList(TXMLEngine* xmleng, XMLNodePointer_t top_node)
{
  XMLNodePointer_t curr_node = xmleng->GetChild(top_node);
  while(curr_node) {
      string curr_node_name = xmleng->GetNodeName(curr_node);
      if(curr_node_name == "element") {
        LOG("CompoundFitSetup", pNOTICE) << "Found element named: ";
        bool ok = this->ReadElement(xmleng,curr_node);
        if(!ok) return false;
      }
      curr_node = xmleng->GetNext(curr_node);
  }
  return true;
}
//________________________________________________________________________________________
bool CompoundFitSetup::ReadElement(TXMLEngine* xmleng, XMLNodePointer_t top_node)
{
//        <detector>     dunend                       </detector>
//        <beam>         fhc                          </beam>
//        <sample>       numuccincl                   </sample>
//        <data>         data.xml                     </data>
//        <mc>           mc_production.xml            </mc>
//        <data_class>   valor::SingleSampleDataA     </data_class>
//        <model_class>  valor::SingleSampleFitModelA </model_class>

  string detector_name = "";
  string beam_name     = "";
  string sample_name   = "";
  string data_file     = "";
  string mc_file       = "";
  string data_class    = "";
  string model_class   = "";

  XMLNodePointer_t curr_node = xmleng->GetChild(top_node);
  while(curr_node) {
      string curr_node_name = xmleng->GetNodeName(curr_node);
      if(xmleng->GetNodeContent(curr_node)) {
        string content = util::TrimSpaces(xmleng->GetNodeContent(curr_node));
        LOG("CompoundFitSetup", pNOTICE) << curr_node_name << " --> " << content;
        if(curr_node_name == "detector"   ) { detector_name = content; }
        if(curr_node_name == "beam"       ) { beam_name     = content; }
        if(curr_node_name == "sample"     ) { sample_name   = content; }
        if(curr_node_name == "data"       ) { data_file     = content; }
        if(curr_node_name == "mc"         ) { mc_file       = content; }
        if(curr_node_name == "data_class" ) { data_class    = content; }
        if(curr_node_name == "model_class") { model_class   = content; }
      }
      curr_node = xmleng->GetNext(curr_node);
  }

  conv::Detector_t detector = util::DetectorFromString(detector_name);
  conv::BeamConf_t beam     = util::BeamConfFromString(beam_name);
  conv::Sample_t   sample   = util::SampleFromString(sample_name);

  if (detector == conv::kdUndefined) return false;
  if (beam     == conv::kbUndefined) return false;
  if (sample   == conv::ksUndefined) return false;

  FitDataABC *  fit_data  = 
     this->AdoptFitData (data_file, detector, beam, sample, data_class );
  FitModelABC * fit_model = 
     this->AdoptFitModel(mc_file,   detector, beam, sample, model_class);

  //
  //
  // ... add to compound fit data and fit model
  //
  //

  return true;
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


