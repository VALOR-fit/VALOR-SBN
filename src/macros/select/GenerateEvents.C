/*
Macro to generate additional events for the near detector.
At the moment this is used to generate external background which is not simulated in the fastmc

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
#include "TRandom3.h"
#include "TString.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooArgSet.h"
#include "RooNDKeysPdf.h"

using namespace std;

void GenerateEvents(string inFile      = "FHC_LBNE_ND_Tree_v25.root",
		    string outFile     = "FHC_LBNE_ND_Tree_v26.root",
		    double eventweight = 1e-18,
		    double ccnumufrac  = 0.005,
		    double ccnuefrac   = 0.05,
		    int reacmode       = 52,
		    int seed           = 199900,
		    bool verbose       = true
		    )
{

  // Open the files and access the trees
  const char* valor_dir = getenv("VALOR_LBNX");
  string inFilefhc = string(valor_dir) + "/data/" + inFile;
  TFile *File = new TFile(inFilefhc.c_str(), "READ");
  TTree *Tree = (TTree*)File->Get("LBNETree");
  Tree->SetNameTitle("Tree","Tree");
  // New tree
  double fEv, fEv_reco, fy_reco, fPOTWeight, fEhad_reco, fEL_reco;
  int fsample, freactionmode;
  TTree *LBNETree = new TTree("LBNETree","LBNETree");

  LBNETree->Branch("fEv",           &fEv,           "fEv/D");
  LBNETree->Branch("fEv_reco",      &fEv_reco,      "fEv_reco/D");
  LBNETree->Branch("fy_reco",       &fy_reco,       "fy_reco/D");
  LBNETree->Branch("fPOTWeight",    &fPOTWeight,    "fPOTWeight/D");
  LBNETree->Branch("fsample",       &fsample,       "fsample/I");
  LBNETree->Branch("freactionmode", &freactionmode, "freactionmode/I");
  LBNETree->Branch("fEhad_reco",    &fEhad_reco,    "fEhad_reco/D");
  LBNETree->Branch("fEL_reco",      &fEL_reco,      "fEL_reco/D");

  RooRealVar Ev("Ev","Ev",0,120,"GeV"); 
  RooRealVar Ev_reco("Ev_reco","Ev_reco",0,120,"GeV");
  RooRealVar y_reco("y_reco","y_reco",0,1);
  RooRealVar POTWeight("POTWeight","POTWeight",0,1);
  RooRealVar sample("sample","sample",1,13); 
  RooRealVar reactionmode("reactionmode","reactionmode",0,52);
  RooRealVar Ehad_reco("Ehad_reco","Ehad_reco",0,120,"GeV");
  RooRealVar EL_reco("EL_reco","EL_reco",0,120,"GeV");

  RooDataSet *Dataset = new RooDataSet("Dataset","Dataset",Tree,RooArgSet(Ev,Ev_reco,y_reco,sample,reactionmode,POTWeight,EL_reco,Ehad_reco));
  if(verbose)
    Dataset->Print("v");

  TString selection = "sample==8 && ((reactionmode >= 9 && reactionmode < 13) || (reactionmode >= 22 && reactionmode < 26) || (reactionmode >= 35 && reactionmode < 39) || (reactionmode >= 48 && reactionmode < 52))";

  // Make a smaller dataset for the nc background in the cc-nue selection 
  RooDataSet *DatasetList   = (RooDataSet*)Dataset->reduce(RooArgSet(Ev_reco,y_reco),selection.Data());
  if(verbose)
    DatasetList->Print("v");

  // Options for the pdf build
  TString options("amd");//advm
  Double_t rho = 1;
  Double_t nSigma = 3;

  RooNDKeysPdf *Pdf = new RooNDKeysPdf("Pdf","Pdf",RooArgSet(Ev_reco,y_reco),*DatasetList,options,rho,nSigma);

  const int samp = 12;
  double samples[samp];
  double wsamples[samp];
  double w[samp];
  double togenerate[samp];

  TRandom3 *rand = new TRandom3();

  // First loop to count number of good events
  for(Int_t j = 1; j <= samp; j++){

    for(Int_t i = 0; i < Dataset->numEntries(); i++){
      RooArgSet *set = Dataset->get(i);
      double sam = set->getRealValue("sample");
      double wei = set->getRealValue("POTWeight");

      if(sam != j){continue;}
      samples[j-1]++;
      wsamples[j-1] += wei;
    }

    if(samples[j-1] < 1){continue;}

    rand->SetSeed(j+samples[j-1]*samples[j-1]+seed);

    if(verbose)
      cout << "Events for sample " << j << " = " << samples[j-1]  << " , Weight = " << wsamples[j-1] << endl;

    if(j == 7){
      ccnuefrac  = rand->Gaus(ccnuefrac,ccnuefrac*0.15);
      samples[j-1] = samples[j-1] * ccnuefrac;
      rand->SetSeed(rand->GetSeed()*1000+seed);
      wsamples[j-1]= rand->Gaus(wsamples[j-1],wsamples[j-1]*0.2);
      w[j-1] = wsamples[j-1]*ccnuefrac;
    }
    else if(j > 9){
      ccnumufrac = rand->Gaus(ccnumufrac,ccnumufrac*0.15);
      samples[j-1] = samples[j-1] * ccnumufrac*5;
      rand->SetSeed(rand->GetSeed()*1000+seed);
      wsamples[j-1]= rand->Gaus(wsamples[j-1],wsamples[j-1]*0.15);
      w[j-1] = wsamples[j-1]*ccnumufrac*5;
    }
    else{
      ccnumufrac = rand->Gaus(ccnumufrac,ccnumufrac*0.1);
      samples[j-1] = samples[j-1] * ccnumufrac;
      rand->SetSeed(rand->GetSeed()*1000+seed);
      wsamples[j-1]= rand->Gaus(wsamples[j-1],wsamples[j-1]*0.1);
      w[j-1] = wsamples[j-1]*ccnumufrac;
    }

    togenerate[j-1] = w[j-1]/eventweight;
    if(verbose)
      cout << "Background events for sample " << j << " = " << samples[j-1]  << " , Weight = " << w[j-1] << " , Events to generate = " << togenerate[j-1] << endl;
  }

  // Now fill the new tree
  LBNETree->SetDirectory(0);
  for(Int_t i = 0; i < Dataset->numEntries(); i++){
    RooArgSet *set = Dataset->get(i);
    fEv           = set->getRealValue("Ev");
    fEv_reco      = set->getRealValue("Ev_reco");
    fy_reco       = set->getRealValue("y_reco");
    fsample       = (int)set->getRealValue("sample");
    fPOTWeight    = set->getRealValue("POTWeight");
    freactionmode = (int)set->getRealValue("reactionmode");
    fEhad_reco    = set->getRealValue("Ehad_reco");
    fEL_reco      = set->getRealValue("EL_reco");

    LBNETree->Fill();
  }

  // And add the background
  for(Int_t j = 1; j <= samp; j++){
    if(samples[j-1] < 1){continue;}

    RooDataSet *data = Pdf->generate(RooArgSet(Ev_reco,y_reco),togenerate[j-1]);
    for(Int_t i = 0; i < data->numEntries(); i++){
      RooArgSet *set = data->get(i);
      fEv_reco = set->getRealValue("Ev_reco");
      fy_reco  = set->getRealValue("y_reco");
      fEv     = 0.0;
      fsample = j;
      fPOTWeight = eventweight;
      freactionmode = reacmode;
      fEL_reco = (1 - fy_reco)*fEv_reco;
      fEhad_reco = fEv_reco - fEL_reco;

      LBNETree->Fill();
    }

  } 

  // Save the new tree
  TFile* out = new TFile(outFile.c_str(), "RECREATE");
  out->cd();
  LBNETree->Write();
  out->Close();
  
  
  return;


}
