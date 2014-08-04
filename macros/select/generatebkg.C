/*
Macro to generate of tracker background

Georgios Christodoulou

*/

#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include <string>
#include <sstream>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooWorkspace.h"
#include "RooNDKeysPdf.h"

using namespace std;

void generatebkg(string inFile  = "FHC_LBNE_ND_Tree_v25.root",
		 string outFile = "bkg.root"
		 )
{

  const char* valor_dir = getenv("VALOR_LBNX");
  string inf = string(valor_dir) + + "/data/" + inFile;

  // Open the files and access the trees
  TFile *File = new TFile(inf.c_str(), "READ");
  TTree *LBNETree = (TTree*)File->Get("LBNETree");

  RooRealVar Ev("Ev","Ev",0,120,"GeV"); 
  RooRealVar Ev_reco("Ev_reco","Ev_reco",0,120,"GeV");
  RooRealVar y_reco("y_reco","y_reco",0,1);
  RooRealVar POTWeight("POTWeight","POTWeight",0,1);
  RooRealVar sample("sample","sample",1,13); 
  RooRealVar reactionmode("reactionmode","reactionmode",0,52);

  RooDataSet *Dataset = new RooDataSet("Dataset","Dataset",LBNETree,RooArgSet(Ev,Ev_reco,y_reco,sample,reactionmode));
  Dataset->Print("v");

  TString selection = "sample==8 && ((reactionmode >= 9 && reactionmode < 13) || (reactionmode >= 22 && reactionmode < 26) || (reactionmode >= 35 && reactionmode < 39) || (reactionmode >= 48 && reactionmode < 52))";

  RooDataSet *DatasetList   = (RooDataSet*)Dataset->reduce(RooArgSet(Ev_reco,y_reco),selection.Data());
  DatasetList->Print("v");

  // Options for the pdf build
  TString options("amd");//advm
  Double_t rho = 1;
  Double_t nSigma = 3;

  RooNDKeysPdf *Pdf = new RooNDKeysPdf("Pdf","Pdf",RooArgSet(Ev_reco,y_reco),*DatasetList,options,rho,nSigma);

  RooDataSet *dataset = Pdf->generate(RooArgSet(Ev_reco,y_reco),100000);

  TTree *Tree = new TTree("Tree","Tree");
  double E, y;
  Tree->Branch("E",           &E,           "E/D");
  Tree->Branch("y",           &y,           "y/D");
  Tree->SetDirectory(0);
  for(Int_t i = 0; i < dataset->numEntries(); i++){
    RooArgSet *set = dataset->get(i);
    E = set->getRealValue("Ev_reco");
    y = set->getRealValue("y_reco");

    Tree->Fill();
  }

  TFile* out = new TFile(outFile.c_str(), "RECREATE");
  out->cd();
  Tree->Write();
  out->Close();
  
  
  return;


}
