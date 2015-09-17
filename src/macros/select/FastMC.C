#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>

#include <string>
#include <sstream>

#include "TFile.h"
#include "TTree.h"

#ifndef __CINT__
#include "ReadFastMC.h"
#endif

using namespace std;
using namespace valor;

void FastMC(string outFile    = "FastMCFile.root",
	    string datacard   = "FastMC_NDSelection.xml",
	    int seed(288888) )
{

  const char* valor_dir = getenv("VALOR_LBNX");
  string fdatacard = string(valor_dir) + "/config/" + datacard;
 
  // Read the datacard and access the fastmc tree
  ReadFastMC *rfmc = new ReadFastMC();
  
  rfmc->ReadXMLDatacard(fdatacard);
  
  TTree* LBNEMCTree =  rfmc->FastMCTree(seed,true);
 
  TFile* out = new TFile(outFile.c_str(), "RECREATE");
  out->cd();
  LBNEMCTree->Write();

  out->Close();
  
  
  return;
}
