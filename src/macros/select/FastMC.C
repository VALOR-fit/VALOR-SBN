#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include <string>
#include <sstream>

#include "TFile.h"
#include "TTree.h"

#ifndef __CINT__
#include "ReadFastMC.h"
#endif

using namespace std;
using namespace valor;

void FastMC(string outFile  = "fmctree.root",
	    string datacard = "FastMC_Datacard.txt",
	    int seed(2229999) )
{

  // Read the datacard and access the fastmc tree
  ReadFastMC *rfmc = new ReadFastMC();
  
  rfmc->ReadDatacard(datacard);
  
  TTree* ReadFastMCTree =  rfmc->FastMCTree(seed);

  //string xmlfile = "/hepstore/georgios/lbne/valor/softw/lbnx/trunk/config/FastMC_NDSelection_1.xml";
  //rfmc->ReadXMLDatacard(xmlfile);
  
  TFile* out = new TFile(outFile.c_str(), "RECREATE");
  out->cd();
  ReadFastMCTree->Write();

  out->Close();
  
  
  return;
}
