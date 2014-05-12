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
  
  // 0 for numucandidates, 1 for nue candidates, 2 for nc candidates
  TTree* ReadFastMCTree =  rfmc->FastMCTree(0,seed);
  
  TFile* out = new TFile(outFile.c_str(), "RECREATE");
  out->cd();
  ReadFastMCTree->Write();

  out->Close();
  
  
  return;
}
