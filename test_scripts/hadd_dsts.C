#include "TFile.h"
#include "TTree.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TList.h"
#include "TString.h"
#include "TSystem.h"
#include "TChain.h"

#include <iostream>
#include <iomanip>
#include <algorithm>

void print_progress_bar(size_t current, size_t total) {
  static const int bar_width = 50;
  double ratio = static_cast<double>(current) / total;
  int pos = static_cast<int>(bar_width * ratio);

  std::cout << "\r[";
  for( int i = 0; i < bar_width; i++ ){
    if( i < pos ) std::cout << "=";
    else if(i == pos) std::cout << ">";
    else std::cout << " ";
  }
  std::cout << "] " << std::fixed << std::setprecision(1) << (100.0 * ratio) << "% done";
  std::cout.flush();
}

int hadd_dsts(std::string directory, std::string output_path, double totPOT) 
{
  TSystemDirectory dir(gSystem->BaseName(TString(directory)), directory.c_str());
  TList * files = dir.GetListOfFiles();
  TIter next(files);
  TSystemFile * file;
  std::vector<std::string> files_to_hadd;

  while( (file = dynamic_cast<TSystemFile *>(next())) ) {
    TString fname = file->GetName();
    if( !file->IsDirectory() && fname.Contains("minidst") && fname.EndsWith(".root") ) {
      files_to_hadd.emplace_back( std::string( Form("%s/%s", directory.c_str(), fname.Data())) );
    }
  }

  std::sort( files_to_hadd.begin(), files_to_hadd.end(), 
	     [](std::string a, std::string b){
	       TObjString as(a.c_str());
	       TObjString bs(b.c_str());
	       return as.GetString() < bs.GetString();
	     } );

  TFile fout(output_path.c_str(), "recreate"); fout.cd();
  TTree * outTree = 0; 

  TChain * chain = new TChain("valor_sbn_minidst");

  for( std::vector<std::string>::iterator it_fl = files_to_hadd.begin();
       it_fl != files_to_hadd.end(); ++it_fl )
    chain->Add((*it_fl).c_str());

  outTree = dynamic_cast<TTree *>(chain->CloneTree(0));
  chain->SetBranchStatus("wght_pot", 0);
  outTree->SetBranchAddress("wght_pot", &totPOT);

  size_t step = std::max<size_t>(1, chain->GetEntries()/1000);
  for(int iEntry = 0; iEntry < chain->GetEntries(); iEntry++) {
    if (iEntry % step == 0 || iEntry == chain->GetEntries() - 1)
      print_progress_bar( iEntry+1, chain->GetEntries() );
    chain->GetEntry(iEntry);
    outTree->Fill();
  }
  std::cout << "" << std::endl;
  
  fout.cd();
  outTree->Write();
  fout.Close();

  return 0;
}
