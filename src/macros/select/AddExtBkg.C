/*
Macro to add out of tracker background to the event selection

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
#include "TCanvas.h"
#include "TRandom.h"

using namespace std;

void AddExtBkg(string inFile      = "FHC_LBNE_ND_Tree_v25.root",
	       string outFile     = "FHC_LBNE_ND_Tree_WBkg_v25.root",
	       bool   addbkg      = true)
{

  const char* valor_dir = getenv("VALOR_LBNX");
  string inf = string(valor_dir) + + "/data/" + inFile;

  // Open the files and access the trees
  TFile *File = new TFile(inf.c_str(), "READ");
  TTree *FastMCTree = (TTree*)File->Get("LBNETree");

  double Ev, Ev_reco, y_reco, POTWeight, Ehad_reco, EL_reco;
  int sample, reactionmode;

  FastMCTree->SetBranchAddress("Ev",           &Ev);
  FastMCTree->SetBranchAddress("Ev_reco",      &Ev_reco);
  FastMCTree->SetBranchAddress("y_reco",       &y_reco);
  FastMCTree->SetBranchAddress("POTWeight",    &POTWeight);
  FastMCTree->SetBranchAddress("sample",       &sample);
  FastMCTree->SetBranchAddress("reactionmode", &reactionmode);
  FastMCTree->SetBranchAddress("Ehad_reco",    &Ehad_reco);
  FastMCTree->SetBranchAddress("EL_reco",      &EL_reco);

  TTree *LBNETree = new TTree("LBNETree","LBNETree");

  LBNETree->Branch("Ev",           &Ev,           "Ev/D");
  LBNETree->Branch("Ev_reco",      &Ev_reco,      "Ev_reco/D");
  LBNETree->Branch("y_reco",       &y_reco,       "y_reco/D");
  LBNETree->Branch("POTWeight",    &POTWeight,    "POTWeight/D");
  LBNETree->Branch("sample",       &sample,       "sample/I");
  LBNETree->Branch("reactionmode", &reactionmode, "reactionmode/I");
  LBNETree->Branch("Ehad_reco",    &Ehad_reco,    "Ehad_reco/D");
  LBNETree->Branch("EL_reco",      &EL_reco,      "EL_reco/D");

  const double pot = 1e21;
  const double fv = 0.005; // in kt

  if(addbkg){
    const int samp = 12;
    double samples[samp];
    double wsamples[samp];
    double w[samp];

    // First loop to count number of good events
    for(Int_t i = 0; i < FastMCTree->GetEntries(); i++){
      FastMCTree->GetEntry(i);
      if(sample < 0){continue;}

      if(sample == 1){
	samples[0]++;
	wsamples[0] += POTWeight;
      }
      else if(sample == 2){
	samples[1]++;
	wsamples[1] += POTWeight;
      }
      else if(sample == 3){
	samples[2]++;
	wsamples[2] += POTWeight;
      }
      else if(sample == 4){
	samples[3]++;
	wsamples[3] += POTWeight;
      }
      else if(sample == 5){
	samples[4]++;
	wsamples[4] += POTWeight;
      }
      else if(sample == 6){
	samples[5]++;
	wsamples[5] += POTWeight;
      }
      else if(sample == 7){
	samples[6]++;
	wsamples[6] += POTWeight;
      }
      else if(sample == 8){
	samples[7]++;
	wsamples[7] += POTWeight;
      }
      else if(sample == 9){
	samples[8]++;
	wsamples[8] += POTWeight;
      }
      else if(sample == 11){
	samples[9]++;
	wsamples[9] += POTWeight;
      }
      else if(sample == 12){
	samples[10]++;
	wsamples[10] += POTWeight;
      }
      else if(sample == 13){
	samples[11]++;
	wsamples[11] += POTWeight;
      }
    }

    for(Int_t i = 0; i < samp; i++)
      cout << samples[i]  << " , ";

      cout << endl;

      for(Int_t i = 0; i < samp; i++)
	cout << wsamples[i] << " , ";

      cout << endl;
 


    // events to add
    double ccnumufrac = 0.01, ccnumubarfrac = 0.01, ccnuefrac = 0.1, ncfrac = 0.01;
    for(Int_t i = 0; i < samp; i++){
      if(i < 7){
	samples[i] = samples[i] * ccnumufrac;
	w[i] = wsamples[i]*ccnumufrac;
	//w[i] = wsamples[i]*ccnumufrac/samples[i];
      }
      else if(i == 7){
	samples[i] = samples[i] * ccnuefrac;
	w[i] = wsamples[i]*ccnuefrac;
	//w[i] = wsamples[i]*ccnuefrac/samples[i];
      }
      else if(i == 8){
	samples[i] = samples[i] * ccnumubarfrac;
	w[i] = wsamples[i]*ccnumubarfrac;
	//w[i] = wsamples[i]*ccnumubarfrac/samples[i];
      }
      else{
	samples[i] = samples[i] * ncfrac;
	w[i] = wsamples[i]*ncfrac;
	//w[i] = wsamples[i]*ncfrac/samples[i];
      }
    }

    for(Int_t i = 0; i < samp; i++)
      cout << samples[i]  << " , ";

      cout << endl;

      for(Int_t i = 0; i < samp; i++)
	cout << w[i] << " , ";
	//cout << w[i]*samples[i]*pot*fv << " , ";

      cout << endl;

      double sweight = 3.5e-19;
      for(Int_t i = 0; i < samp; i++){
	samples[i] =  w[i]/sweight;
	cout << w[i]/sweight << " , ";
	//cout << wsamples[i]*pot*fv << " , ";
      }

      cout << endl;


    TRandom3 *rand = new TRandom3();
    double sig = 0.1;
    for(int i = 0; i < samp; i++){
      rand->SetSeed(i+samples[i]*samples[i]);
      samples[i] = rand->Gaus(samples[i],(double)samples[i]*sig);
  
    }
 
    
    for(Int_t i = 0; i < samp; i++)
      cout << samples[i]  << " , ";

    cout << endl;
    
    int insample[samp] = {1,2,3,4,5,6,7,8,9,11,12,13};
    double count[samp+1];
    count[0] = 0.0;
    count[1] = samples[0];
    for(Int_t i = 2; i <= samp; i++)
      count[i] = count[i-1]+samples[i-1];

    for(Int_t i = 0; i <= samp; i++)
      cout << count[i]  << " , ";

    cout << endl;

    cout << samples[0] << " , " << samples[0]+samples[1] << " , " << samples[0]+samples[1]+samples[2] << " , " << samples[0]+samples[1]+samples[2]+samples[3] << endl;
    
    // This was generated using the generatebkg.C macro
    TFile *BkgFile = new TFile("bkg.root", "READ");
    TTree *BkgFastMCTree = (TTree*)File->Get("Tree");
    double E, y;
    Tree->SetBranchAddress("E",      &E);
    Tree->SetBranchAddress("y",      &y);
    LBNETree->SetDirectory(0);

    for(Int_t j = 0; j < samp; j++){
      for(Int_t i = count[j]; i < count[j+1]; i++){
	Tree->GetEntry(i);

	if(insample[j] < 10 && E < 0.4){continue;}
	if(insample[j] == 11 || insample[j] == 12 && E > 1){continue;}
	
	Ev = 0;
	reactionmode = 52;
	Ev_reco = E;
	y_reco  = y;
	sample = insample[j];
	POTWeight = sweight;
	//POTWeight = w[j];
	
	LBNETree->Fill();
      }
    }

  } // addbkg

  LBNETree->SetDirectory(0);
  for(Int_t i = 0; i < FastMCTree->GetEntries(); i++){
    FastMCTree->GetEntry(i);
    if(sample < 0){continue;}

    //POTWeight = POTWeight*pot*fv;

    LBNETree->Fill();
  }
  TFile* out = new TFile(outFile.c_str(), "RECREATE");
  out->cd();
  LBNETree->Write();

  out->Close();

}
