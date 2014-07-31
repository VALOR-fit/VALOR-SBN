//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________
#include "MakeSplines.h"

#include <math.h>
#include <ostream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "TXMLEngine.h"

#include "Conventions/Opt.h"
#include "Messenger/Messenger.h"

using namespace valor;
using namespace valor::util;
using namespace valor::conv;

ClassImp(MakeSplines)

MakeSplines::MakeSplines()
{
  ndmodel = new NDModel();
}

MakeSplines::~MakeSplines()
{
  delete ndmodel;
}

void MakeSplines::ReadXMLDatacard(string datacard){

  LOG("MakeSplines",pNOTICE) << "Reading configuration from XML file [" << datacard << "]";

  TXMLEngine* xml = new TXMLEngine;
  XMLDocPointer_t xmldoc = xml->ParseFile(datacard.c_str());
  if (xmldoc==0) {
    cerr << "Exp >> " << "Can not parse input: " << datacard << endl;
    delete xml;
    return;
  }
  XMLNodePointer_t root_node = xml->DocGetRootElement(xmldoc);

  double lepton_ene_un  = util::XML2Dbl(xml,root_node,"syst/EnergyScale/Leptonic");
  double hadron_ene_un  = util::XML2Dbl(xml,root_node,"syst/EnergyScale/Hadronic");

  for(int i=-3; i<4; i++){
    ELScale[i+3]   = lepton_ene_un*i;
    EhadScale[i+3] = hadron_ene_un*i;
  }

  LOG("MakeSplines",pNOTICE) << "Leptonic Energy Scale uncertainty = " <<  lepton_ene_un;
  LOG("MakeSplines",pNOTICE) << "Hadronic Energy Scale uncertainty = " <<  hadron_ene_un;

  // Release memory
  xml->FreeDoc(xmldoc);
  delete xml;

}

TObjArray* MakeSplines::CreateArray(string inFile, string inTree, bool leptonic){

  // Open the files and access the trees
  TFile *File = new TFile(inFile.c_str(), "READ");
  TTree *FastMCTree = (TTree*)File->Get(inTree.c_str());

  LOG("MakeSplines",pNOTICE) << "Reading from file [" << File->GetName() << "]";
  LOG("MakeSplines",pNOTICE) << "Reading from tree [" << FastMCTree->GetName() << "]";

  // Acees the tree variables
  FastMCTree->SetBranchAddress("Ehad_reco",        &Ehad_reco);
  FastMCTree->SetBranchAddress("EL_reco",          &EL_reco);
  FastMCTree->SetBranchAddress("sample",           &sample);
  FastMCTree->SetBranchAddress("reactionmode",     &reactionmode);
  FastMCTree->SetBranchAddress("Ev",               &Ev);
  FastMCTree->SetBranchAddress("Ev_reco",          &Ev_reco);
  FastMCTree->SetBranchAddress("y_reco",           &y_reco);
  FastMCTree->SetBranchAddress("POTWeight",        &POTWeight);

  // Create array of trees to save the events after the energy scale has been applied
  const int ntrees = 7;
  TTree *treearray[ntrees];
  TTree *LBNETree1 = new TTree("LBNETree1","Minus 3 Sigma Tree");
  TTree *LBNETree2 = new TTree("LBNETree2","Minus 2 Sigma Tree");
  TTree *LBNETree3 = new TTree("LBNETree3","Minus 1 Sigma Tree");
  TTree *LBNETree4 = new TTree("LBNETree4","Zero  0 Sigma Tree");
  TTree *LBNETree5 = new TTree("LBNETree5","Plus  1 Sigma Tree");
  TTree *LBNETree6 = new TTree("LBNETree6","Plus  2 Sigma Tree");
  TTree *LBNETree7 = new TTree("LBNETree7","Plus  3 Sigma Tree");

  treearray[0] = LBNETree1;
  treearray[1] = LBNETree2;
  treearray[2] = LBNETree3;
  treearray[3] = LBNETree4;
  treearray[4] = LBNETree5;
  treearray[5] = LBNETree6;
  treearray[6] = LBNETree7;

  for(int i = 0; i < ntrees; i++){
    treearray[i]->Branch("Ev",          &Ev,          "Ev/D");
    treearray[i]->Branch("Ev_reco",     &Ev_reco,     "Ev_reco/D");
    treearray[i]->Branch("y_reco",      &y_reco,      "y_reco/D");
    treearray[i]->Branch("POTWeight",   &POTWeight,   "POTWeight/D");
    treearray[i]->Branch("sample",      &sample,      "sample/I");
    treearray[i]->Branch("reactionmode",&reactionmode,"reactionmode/I");

    treearray[i]->SetDirectory(0);
    for(int j = 0; j < FastMCTree->GetEntries(); j++){
      FastMCTree->GetEntry(j);
      if(sample < 1){continue;}
      if(leptonic){
	EL_reco   = EL_reco + ELScale[i]*EL_reco;
	Ev_reco   = EL_reco + Ehad_reco;
	y_reco    = 1 - EL_reco/Ev_reco;
      }
      else{
	Ehad_reco = Ehad_reco + EhadScale[i]*Ehad_reco; 
	Ev_reco   = EL_reco + Ehad_reco;
	y_reco    = 1 - EL_reco/Ev_reco;
      }
      
      treearray[i]->Fill();
    }
  }

  TObjArray* SplineArray = new TObjArray();

  for(int i = 0; i < ntrees; i++)
    SplineArray->Add(treearray[i]);

  FastMCTree->Delete();

  return SplineArray;
}

TMatrixD MakeSplines::MakeGraphs(string confile){

  ndmodel->Read(confile);
  TObjArray* NDModelArray = new TObjArray();
  ndmodel->Write(NDModelArray,"model","mct_vf");
  
  TObjArray* NDNomModelArray = new TObjArray();

  for(int i = 0; i < NDModelArray->GetEntries(); i++){
    VALORArray* array = (VALORArray*)NDModelArray->At(i);
    
    TString arrayname(array->GetName());
    if(arrayname.Contains("nom"))
      NDNomModelArray->Add(array);

    //delete array;

  }
  //cout << "sample number = " << NDNomModelArray->GetEntries() << endl;

  VALORArray* temparray = (VALORArray*)NDModelArray->At(0);
  int mdim = 0;
  for(int j = 0; j < temparray->GetSize(0); j++)
    for(int k = 0; k < temparray->GetSize(1); k++)
      for(int r = 0; r < temparray->GetSize(2); r++)
	mdim++;

  cout << "bin number = " << mdim << " , array dimensions = " << NDNomModelArray->GetEntries() << endl;
 
  TMatrixD MMatrix(NDNomModelArray->GetEntries(),mdim);

  for(int i = 0; i < NDNomModelArray->GetEntries(); i++){
    VALORArray* temparray = (VALORArray*)NDNomModelArray->At(i);
        
    int fdim = 0;
    for(int j = 0; j < temparray->GetSize(0); j++){
      for(int k = 0; k < temparray->GetSize(1); k++){
	for(int r = 0; r < temparray->GetSize(2); r++){
	  double temp = temparray->GetEntry(j,k,r);

	  MMatrix(i,fdim) = temp;
	  fdim++;
	}
      }
    }
  }

  delete NDNomModelArray;
  delete NDModelArray;

  return MMatrix;

}




