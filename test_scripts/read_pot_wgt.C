#include "TFile.h"
#include "TTree.h"
#include <iostream>

int read_pot_wgt(std::string finpath) {

  

  TFile * fin = TFile::Open(finpath.c_str());
  TTree * tree = dynamic_cast<TTree *>(fin->Get("valor_sbn_minidst"));
  tree->SetBranchStatus("*", 0);
  tree->SetBranchStatus("wght_pot", 1);
  double pw = 0.0;
  tree->SetBranchAddress("wght_pot", &pw);
  tree->GetEntry(0);
  std::cout << 1.0/pw << std::endl;
  fin->Close();
  delete fin;
  return 0;
}
