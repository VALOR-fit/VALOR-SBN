//________________________________________________________________________________________
/*

Copyright (c) 2010-2019, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include <cstring>

#include "TXMLEngine.h"

#include "valor/Messenger/Messenger.h"
#include "valor/Utilities/UtlSystem.h"
#include "dune/Conventions/ParameterSet.h"

using namespace valor;


//________________________________________________________________________________________
valor::ParameterSet * valor::ParameterSet::fInstance = 0;
//________________________________________________________________________________________
valor::ParameterSet::ParameterSet()
{
  fInstance = 0;
}
//________________________________________________________________________________________
void ParameterSet::ReadXML(std::string xml_path)
{
  // Analysis configuration
  std::string param_file_full = util::CompleteConfigPath(xml_path);

  // Parse the input XML param file
  TXMLEngine* xmleng = new TXMLEngine;
  XMLDocPointer_t xmldoc = xmleng->ParseFile(param_file_full.c_str());
  if (xmldoc==0) {
    LOG("ParameterSet",pFATAL)<< "Can not parse input XML file [" << param_file_full << "]";
    util::Die(1);
  }
  XMLNodePointer_t root_node = xmleng->DocGetRootElement(xmldoc);
  
  std::string root_node_name = xmleng->GetNodeName(root_node);
  if (strcmp(root_node_name.c_str(),"param_list")!=0) {
    LOG("ParameterSet",pFATAL)<< "root node in XML file "<<param_file_full<<" is "<<root_node_name<<", expected param_list";
    util::Die(-1);
  }

  XMLNodePointer_t curr_node = xmleng->GetChild(root_node);
  while(curr_node) {
    string curr_node_name = xmleng->GetNodeName(curr_node);
    if(curr_node_name == "param") {
      fParams.emplace_back(xmleng, curr_node);
    }
    else {
      LOG("ParameterSet",pWARN)<< "Found a node, " << curr_node_name << ", which does not correspond to a parameter";
    }

    curr_node = xmleng->GetNext(curr_node);
  }

  xmleng->FreeDoc(xmldoc);
  delete xmleng;
}
//________________________________________________________________________________________
const std::vector<FitParamNew> & ParameterSet::GetParams() const
{
  return fParams;
}
//________________________________________________________________________________________
const valor::ParameterSet * valor::ParameterSet::Instance()
{
  return MutableInstance();
}
//________________________________________________________________________________________
valor::ParameterSet * valor::ParameterSet::MutableInstance()
{
  if(fInstance == 0) {
    static valor::ParameterSet::Cleaner cleaner;
    cleaner.DummyMethodAndSilentCompiler();
    fInstance = new valor::ParameterSet;
  }
  return fInstance;
}
//________________________________________________________________________________________
