
// For testing the FitParamNew class

// Francis Bench

void test_FitParamNew
(
  const char * param_file    = "params/params_test.xml"
)
{
  using std::cout;
  using std::endl;
  using namespace valor;
  using namespace valor::conv;

  // Analysis configuration
  TString param_file_full = Form("%s/config/%s", gSystem->Getenv("VALOR_EXPT"), param_file);

  // Parse the input XML param file file
  TXMLEngine* xmleng = new TXMLEngine;
  XMLDocPointer_t xmldoc = xmleng->ParseFile(param_file_full);
  if (xmldoc==0) {
    cout << "Can not parse input XML file [" << param_file_full << "]" << endl;
    util::Die(1);
  }
  XMLNodePointer_t root_node = xmleng->DocGetRootElement(xmldoc);
  cout << "root node name is " << xmleng->GetNodeName(root_node) << endl;

  XMLNodePointer_t curr_node = xmleng->GetChild(root_node);
  while(curr_node) {
    string curr_node_name = xmleng->GetNodeName(curr_node);
    if(curr_node_name == "param") {
      FitParamNew fp(xmleng, curr_node);
      fp.Print(std::cout);
    }
    else {
      cout << "Found a node, " << curr_node_name << ", which does not correspond to a parameter" << endl;
    }

    curr_node = xmleng->GetNext(curr_node);
  }

  xmleng->FreeDoc(xmldoc);
  delete xmleng;

}
