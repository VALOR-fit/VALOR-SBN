//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________
#include "ReadFastMC.h"

#include <math.h>
#include <ostream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "TH2.h"
#include "TAxis.h"
#include "TRandom3.h"
#include "TF1.h"

#include "TXMLEngine.h"

using namespace valor;
using namespace valor::util;

ClassImp(ReadFastMC)

ReadFastMC::ReadFastMC()
{
  min = 0;
  max = 30;
  bin = 90;

  npionnum = 2;

}

ReadFastMC::~ReadFastMC(){
  //File->Delete();
}
// ----------------------------------------------------------------------------
void ReadFastMC::ReadDatacard(string datacard){

  // Open the datacard file
  ifstream empFile;
  empFile.open(datacard.c_str());
  // Read the datacard line by line
  string line;

  while(!empFile.eof()){
    getline(empFile,line);
    // Do not read empty lines or comments
    if(line.length() == 0 || line[0] == '#' || line[0] == '/'){continue;}
    else{
      if(line.find("InFile") != string::npos){ // input root file
	size_t found = line.find(" ");
	inFile = line.substr(found);
	inFile.erase(inFile.begin());
      }
      if(line.find("Events") != string::npos){ // events to run
	size_t found = line.find(" ");
	string events = line.substr(found);
	events.erase(events.begin());
	nevents = atoi(events.c_str());
      }
      if(line.find("NeutrinoPDG") != string::npos){ // neutrino pdg
	size_t found = line.find(" ");
	string neut = line.substr(found);
	neut.erase(neut.begin());
	neutrinoPDG = atoi(neut.c_str());
      }
      if(line.find("Years") != string::npos){ // years to run
	size_t found = line.find(" ");
	string expo = line.substr(found);
	expo.erase(expo.begin());
	years = atof(expo.c_str());
      }
      if(line.find("Exposure") != string::npos){ // POT/year
	size_t found = line.find(" ");
	string expo = line.substr(found);
	expo.erase(expo.begin());
	exposure = atof(expo.c_str());
	exposure = exposure*1e20;
      }
      if(line.find("Detector") != string::npos){ // near or far detector
	size_t found = line.find(" ");
	detector = line.substr(found);
	detector.erase(detector.begin());
      }
      if(line.find("DetectorMass") != string::npos){ // detector mass
	size_t found = line.find(" ");
	string expo = line.substr(found);
	expo.erase(expo.begin());
	detmass = atof(expo.c_str());
      }
      if(line.find("Reweight") != string::npos){ // do reweighting
        size_t found = line.find(" ");
        string rw = line.substr(found);
        rw.erase(rw.begin());
	if(rw == "0")
	  reweight = false;
	else
	  reweight = true;
      }
      if(line.find("Verbose") != string::npos){ // verbosity level
        size_t found = line.find(" ");
        string verb = line.substr(found);
        verb.erase(verb.begin());
        verbose = atoi(verb.c_str());
      }
      if(line.find("ReconNeutrinoEnergyCut") != string::npos){ // recon neutrino energy
        size_t found = line.find(" ");
        string ene = line.substr(found);
        ene.erase(ene.begin());
        enureconcut = atof(ene.c_str());
      }
      if(line.find("ReconPiPMEnergyCut") != string::npos){ // recon pion energy
        size_t found = line.find(" ");
        string ene = line.substr(found);
        ene.erase(ene.begin());
        epionreconcut = atof(ene.c_str());
      }
      if(line.find("ReconKaonPMEnergyCut") != string::npos){ // recon kaon energy
	size_t found = line.find(" ");
	string ene = line.substr(found);
	ene.erase(ene.begin());
	ekaonreconcut = atof(ene.c_str());
      }
      if(line.find("ReconProtonEnergyCut") != string::npos){ // recon proton energy
        size_t found = line.find(" ");
        string ene = line.substr(found);
        ene.erase(ene.begin());
        eprotonreconcut = atof(ene.c_str());
      }
      if(line.find("ReconGammaEnergyCut") != string::npos){ // recon gamma energy
        size_t found = line.find(" ");
        string ene = line.substr(found);
        ene.erase(ene.begin());
        egammareconcut = atof(ene.c_str());
      }
      if(line.find("ReconElectronEnergyCut") != string::npos){ // recon electron energy
        size_t found = line.find(" ");
        string ene = line.substr(found);
        ene.erase(ene.begin());
        eelectronreconcut = atof(ene.c_str());
      }
      if(line.find("Pi0InvariantMassCut") != string::npos){ // pi0 inv mass
        size_t found = line.find(" ");
        string im = line.substr(found);
        im.erase(im.begin());
        pi0invmass = atof(im.c_str());
      }
      if(line.find("PionMisIDAsProton") != string::npos){ // pion mis id as proton
        size_t found = line.find(" ");
        string misid = line.substr(found);
        misid.erase(misid.begin());
        PionMisIDAsProton = atof(misid.c_str());
      }
      if(line.find("PionMisIDAsKaon") != string::npos){ // pion mis id as kaon
        size_t found = line.find(" ");
        string misid = line.substr(found);
        misid.erase(misid.begin());
        PionMisIDAsKaon = atof(misid.c_str());
      }
      if(line.find("ProtonMisIDAsPion") != string::npos){ // proton mis id as pion
        size_t found = line.find(" ");
        string misid = line.substr(found);
        misid.erase(misid.begin());
        ProtonMisIDAsPion = atof(misid.c_str());
      }
      if(line.find("ProtonMisIDAsKaon") != string::npos){ // proton mis id as kaon
        size_t found = line.find(" ");
        string misid = line.substr(found);
        misid.erase(misid.begin());
        ProtonMisIDAsKaon = atof(misid.c_str());
      }
      if(line.find("KaonMisIDAsPion") != string::npos){ // kaon mis id as pion
        size_t found = line.find(" ");
        string misid = line.substr(found);
        misid.erase(misid.begin());
        KaonMisIDAsPion = atof(misid.c_str());
      }
      if(line.find("KaonMisIDAsProton") != string::npos){ // kaon mis id as proton
        size_t found = line.find(" ");
        string misid = line.substr(found);
        misid.erase(misid.begin());
        KaonMisIDAsProton = atof(misid.c_str());
      }
      if(line.find("ChargeConfMomSlope") != string::npos){ // mom slope
        size_t found = line.find(" ");
        string par = line.substr(found);
        par.erase(par.begin());
        ChargeConfMomSlope = atof(par.c_str());
      }
      if(line.find("ChargeConfMomConst") != string::npos){ // mom const
        size_t found = line.find(" ");
        string par = line.substr(found);
        par.erase(par.begin());
        ChargeConfMomConst = atof(par.c_str());
      }
      if(line.find("ChargeConfTrLSlope") != string::npos){ // track length slope
        size_t found = line.find(" ");
        string par = line.substr(found);
        par.erase(par.begin());
        ChargeConfTrLSlope = atof(par.c_str());
      }
      if(line.find("ChargeConfTrLConst") != string::npos){ // track length const
        size_t found = line.find(" ");
        string par = line.substr(found);
        par.erase(par.begin());
        ChargeConfTrLConst = atof(par.c_str());
      }
      if(line.find("MaxMomentumPID") != string::npos){ // max momentum for pid
        size_t found = line.find(" ");
        string par = line.substr(found);
        par.erase(par.begin());
        MaxMomentumPID = atof(par.c_str());
      }
      if(line.find("TrackLengthCut") != string::npos){ // track length cut
        size_t found = line.find(" ");
        string par = line.substr(found);
        par.erase(par.begin());
        tracklengthcut = atof(par.c_str());
      }
    }
  }
  empFile.close();
}
// ----------------------------------------------------------------------------
int ReadFastMC::WhatToSelect(bool nc){

  int whattoselect = -1;
  if(TMath::Abs(neutrinoPDG) == 14)
    whattoselect = 0;
  else if(TMath::Abs(neutrinoPDG) == 12)
    whattoselect = 1;

  if(nc)
    whattoselect = 2;

  return whattoselect;
}
// ----------------------------------------------------------------------------
void ReadFastMC::ReadXMLDatacard(string datacard){

  TXMLEngine* xml = new TXMLEngine; 
  XMLDocPointer_t xmldoc = xml->ParseFile(datacard.c_str());
  if (xmldoc==0) {
    cerr << "Exp >> " << "Can not parse input: " << datacard << endl;
    delete xml;
    return;  
  }
  //XMLNodePointer_t root_node = xml->DocGetRootElement(xmldoc);
 
  //enureconcut = util::XML2Dbl(xml,root_node,"DetConfig/ReconNeutrinoEnergyCut");
  // Release memory
  xml->FreeDoc(xmldoc);
  delete xml;
}
// ----------------------------------------------------------------------------
double ReadFastMC::FluxWeight(int neutpdg, int otherneutpdg){

  // No neutrino? ->skip
  if( abs(neutpdg) != 12 && abs(neutpdg) != 14 && abs(neutpdg) != 16)
    return 0.0;

  double nusel  = 1.0;
  double anusel = 1.0;

  TTree *gstTree = ReadTree(inFile);

  // Need to loop over the events
  for(int i = 0; i < gstTree->GetEntries(); i++){
    gstTree->GetEntry(i);

    if(neu == neutpdg)
      nusel = POTWeight;
    if(neu == otherneutpdg)
      anusel = POTWeight;
   
    // Temporary
    if(nusel != 1.0 && anusel != 1.0)
      break;
  }

  gstTree->Delete();

  return anusel/nusel;

}
// ----------------------------------------------------------------------------
TTree* ReadFastMC::FastMCTree(int seed, bool debugtree){

  // The ratio of neutrino-antineutrino in the beam
  //double fluxweight = FluxWeight(neutrinoPDG, -neutrinoPDG);
  // FastMC Tree
  TTree *gstTree = ReadTree(inFile);
  // Number of events to select
  int numuevents = 0; int anumuevents = 0;
  // Output tree
  TTree *FastMCTree = new TTree("FastMCTree","FastMC Output Tree");
  // Event weight for the neutrino-antineutrino ratio in the beam
  //double EventWeight = 1.0;
  // Event sample
  int sample = -1;
  // True reaction mode
  int reactionmode = -1;
  // Number of misidentified pions as protons
  int NPionMisIDAsProton = 0;
  // Number of misidentified protons as pions
  int NProtonMisIDAsPion = 0;
  // Charge flip for selected lepton
  bool LeptonChargeFlip = false;

  // Tree branches
  FastMCTree->Branch("Ev",          &Ev,          "Ev/D");
  FastMCTree->Branch("Ev_reco",     &Ev_reco,     "Ev_reco/D");
  FastMCTree->Branch("neu",         &neu,         "neu/I");
  FastMCTree->Branch("y_reco",      &y_reco,      "y_reco/D");
  FastMCTree->Branch("POTWeight",   &POTWeight,   "POTWeight/D");
  FastMCTree->Branch("sample",      &sample,      "sample/I");
  FastMCTree->Branch("reactionmode",&reactionmode,"reactionmode/I");

  if(debugtree){
    FastMCTree->Branch("neut_code",           &neut_code,           "neut_code/I");
    FastMCTree->Branch("ys",                  &ys,                  "ys/D");
    FastMCTree->Branch("Q2",                  &Q2,                  "Q2/D");
    FastMCTree->Branch("Q2_reco",             &Q2_reco,             "Q2_reco/D");
    FastMCTree->Branch("NPionMisIDAsProton",  &NPionMisIDAsProton,  "NPionMisIDAsProton/I");
    FastMCTree->Branch("NProtonMisIDAsPion",  &NProtonMisIDAsPion,  "NProtonMisIDAsPion/I");
    FastMCTree->Branch("LeptonChargeFlip",    &LeptonChargeFlip,    "LeptonChargeFlip/O");
  }

  //const double pionmass   = 0.13957;
  const double pizeromass = 0.13498;

  // Random generator
  TRandom3 *rand = new TRandom3();

  // POT normalization
  double potnorm = years*exposure*detmass/nevents;

  FastMCTree->SetDirectory(0);
  for(int i = 0; i < gstTree->GetEntries(); i++){
    gstTree->GetEntry(i);

    // Initialize
    NPionMisIDAsProton = 0;
    NProtonMisIDAsPion = 0;
    LeptonChargeFlip = false;

    int newseed = seed;

    if(neu == neutrinoPDG){
      if(numuevents == nevents){continue;}
      numuevents++;
    }
    else if(neu == -neutrinoPDG){
      if(anumuevents == nevents){continue;}
      anumuevents++;
    }

    // Normalized POT weight potnorm=(mass*years*exposure/years)/nevents
    POTWeight = POTWeight*potnorm;

    // No recon neutrino energy? -> continue
    if(Ev_reco < enureconcut){continue;}

    // Apply the charge flip cut only for CC selection
    if(EvClass_reco < 2){
      newseed = seed*seed + i;
      double lmom = sqrt(pxL_reco*pxL_reco + pyL_reco*pyL_reco + pzL_reco*pzL_reco);
      
      LeptonChargeFlip = ChargeFlip(newseed, lmom);
  
      // For the selected neutrino type skip the event if the charge is flipped 
      if(neu == neutrinoPDG && LeptonChargeFlip){continue;}
      // For anti-nu keep only the events with the charge flipped
      if(neu == -neutrinoPDG && !LeptonChargeFlip){continue;}
    }

    // Number of final state pions and protons
    int npizero = 0; int npiplus = 0; int npiminus = 0; int nprotons = 0; int nneutrons = 0; int nkaonplus = 0; int nkaonminus = 0;
    // EM activity
    int nem = 0; int ngamma = 0;
    // Other stuff
    int nother = 0;
    // Other - this refers to regions where the PID can't separate pions from protons
    int otherpar = 0;

    for(int k = 0; k < nf; k++){
      newseed = i*i + k + nf + seed*seed; 
      // Pt
      //double pt = sqrt(pxf_reco[k]*pxf_reco[k] + pyf_reco[k]*pyf_reco[k]);

      // Momentum
      double momentum = sqrt(pxf_reco[k]*pxf_reco[k] + pyf_reco[k]*pyf_reco[k] + pzf_reco[k]*pzf_reco[k]);

      // Charge mis-id
      bool chargeflip = ChargeFlip(newseed, momentum);

      rand->SetSeed(newseed + k + nf + i + seed);
      int rnum = rand->Integer(1000);

      if(pdgf[k] == 22){  // photons
	if(Ef_reco[k] < egammareconcut){continue;}
	ngamma++;
      }
      else if(abs(pdgf[k]) == 11){ // e-/e+
	// Minimum track length cut
	if(Trkf_reco[k] < tracklengthcut){continue;}
	// Energy cut
	if(Ef_reco[k] < eelectronreconcut){continue;}
	  nem++;
      }
      else if(pdgf[k] == 211){ // pi+
	// Minimum track length cut
	if(Trkf_reco[k] < tracklengthcut){continue;}
	// Energy cut
	if(Ef_reco[k] < epionreconcut){continue;}

	if(momentum > MaxMomentumPID)
	  otherpar++;
	else{
	  if(rnum < PionMisIDAsProton*1000){ // Mis-identified as proton?
	    NPionMisIDAsProton++;
	    if(!chargeflip)// has to be positive charged
	      nprotons++;
	  }
	  else if(rnum > PionMisIDAsProton*1000 && rnum < (PionMisIDAsProton+PionMisIDAsKaon)*1000){
	    nother++;
	  }  
	  else{
	    if(chargeflip)
	      npiminus++;
	    else
	      npiplus++;
	  }
	}
      }
      else if(pdgf[k] == -211){ // pi-
	// Minimum track length cut
	if(Trkf_reco[k] < tracklengthcut){continue;}
	// Energy cut
	if(Ef_reco[k] < epionreconcut){continue;}

	if(momentum > MaxMomentumPID)
	  otherpar++;
	else{
	  if(rnum < PionMisIDAsProton*1000){ // Mis-identified as proton?
	    NPionMisIDAsProton++;
	    if(chargeflip)// has to be positive charged
	      nprotons++;
	  }
	  else if(rnum > PionMisIDAsProton*1000 && rnum < (PionMisIDAsProton+PionMisIDAsKaon)*1000){
            nother++;
          }
	  else{
	    if(chargeflip)
	      npiplus++;
	    else
	      npiminus++;
	  }
	}
      }
      else if(pdgf[k] == 111){ // pi0
	if(Ef_reco[k] < egammareconcut){continue;}
	npizero++;
      }
      else if(pdgf[k] == 2212){ // proton
	// Minimum track length cut
	if(Trkf_reco[k] < tracklengthcut){continue;}
	// Energy cut
	if(Ef_reco[k] < eprotonreconcut){continue;}

	if(momentum > MaxMomentumPID)
	  otherpar++;
	else{
	  if(rnum < ProtonMisIDAsPion*1000){ // mis-id as pion
	    NProtonMisIDAsPion++;
	    if(chargeflip)
	      npiminus++;
	    else
	      npiplus++;
	  }
	  else if(rnum > ProtonMisIDAsPion*1000 && rnum < (ProtonMisIDAsPion+ProtonMisIDAsKaon)*1000){ // mis-id as proton
            nother++;
          }
	  else{// now check the charge
	    if(!chargeflip)
	      nprotons++;
	  }
	}
      }
      else if(pdgf[k] == 321){ // kaon+
	// Minimum track length cut
        if(Trkf_reco[k] < tracklengthcut){continue;}
        // Energy cut
        if(Ef_reco[k] < ekaonreconcut){continue;}

	if(momentum > MaxMomentumPID)
          otherpar++;
        else{
	  if(rnum < KaonMisIDAsPion*1000){ // mis-id as pion
	    if(chargeflip)
              npiminus++;
            else
              npiplus++;
	  }
	  else if(rnum > KaonMisIDAsPion*1000 && rnum < (KaonMisIDAsPion+KaonMisIDAsProton)*1000){
	    if(!chargeflip)
	      nprotons++;
	  }
	  else
	    nkaonplus++;
	}
      }
      else if(pdgf[k] == -321){ // kaon-
	// Minimum track length cut
        if(Trkf_reco[k] < tracklengthcut){continue;}
        // Energy cut
        if(Ef_reco[k] < ekaonreconcut){continue;}

	if(momentum > MaxMomentumPID)
          otherpar++;
        else{
          if(rnum < KaonMisIDAsPion*1000){ // mis-id as pion
            if(!chargeflip)
              npiminus++;
            else
              npiplus++;
          }
          else if(rnum > KaonMisIDAsPion*1000 && rnum < (KaonMisIDAsPion+KaonMisIDAsProton)*1000){ // mis-id as proton
            if(chargeflip)
              nprotons++;
          }
          else
            nkaonminus++;
        }
      }
      if(pdgf[k] == 2112){
	// Minimum track length cut
        if(Trkf_reco[k] < tracklengthcut){continue;}
        // Energy cut
        if(Ef_reco[k] < 0.1){continue;}

	nneutrons++;
      }
      else{
	// Minimum track length cut
	//if(Trkf_reco[k] < tracklengthcut){continue;}
	// Energy cut
	if(Ef_reco[k] < 0.1){continue;}
	if(momentum > MaxMomentumPID)
          otherpar++;
	else
	  nother++;
      }
    } // fs particle loop

    int npionscharge = npiplus + npiminus;
    int nkaons = nkaonplus + nkaonminus;
    int npizerorecon = 0;

    // Only for single pi0 events
    if(npizero == 1 && nEMf == 2){
      double par = sqrt(EMpxf_reco[0]*EMpxf_reco[0] + EMpyf_reco[0]*EMpyf_reco[0] + EMpzf_reco[0]*EMpzf_reco[0]);
      double pbr = sqrt(EMpxf_reco[1]*EMpxf_reco[1] + EMpyf_reco[1]*EMpyf_reco[1] + EMpzf_reco[1]*EMpzf_reco[1]);
      
      double aDOTbr = EMpxf_reco[0]*EMpxf_reco[1] + EMpyf_reco[0]*EMpyf_reco[1] + EMpzf_reco[0]*EMpzf_reco[1];
      double costhr = aDOTbr / (par * pbr);
      double imr = sqrt(2.0 *EMEf_reco[0]  *EMEf_reco[1]  * ( 1.0 - costhr));
      
      // Invariant mass cut
      if( fabs(imr - pizeromass) < pi0invmass)
	npizerorecon++;
    }

    // NC Non-visible events - do not put them on the output tree
    if(EvClass_reco == 2){
      if(npionscharge == 0 && npizero < 2 && npizerorecon == 0 && nprotons == 0 && otherpar == 0 && nem == 0 && ngamma == 0 && nkaons == 0 && nother == 0) {continue;}
    }

    // True reaction modes
    int nipipm  = nipip + nipim;
    //int nipipm0 = nipip + nipim + nipi0;

    if(cc){
      if(qel)
	reactionmode = 0;
      else if(coh)
	reactionmode = 1;
      else if(nipipm == 1 && nipi0 == 0)
	reactionmode = 2;
      else if(nipipm == 2 && nipi0 == 0)
        reactionmode = 3;
      else if(nipipm == 0 && nipi0 == 1)
        reactionmode = 4;
      else if(nipipm == 0 && nipi0 == 2)
        reactionmode = 5;
      else if(nipipm == 1 && nipi0 == 1)
        reactionmode = 6;
      else
	reactionmode = 7;
    }
    else if(nc){
      if(coh)
        reactionmode = 8;
      else if(nipipm == 1 && nipi0 == 0)
        reactionmode = 9;
      else if(nipipm == 0 && nipi0 == 1)
        reactionmode = 10;
      else
        reactionmode = 11;
    }

    // Selection
    if(EvClass_reco == 0){ // cc-numu
      if(npionscharge == 0      && npizerorecon == 0 && nprotons == 0 && otherpar == 0 && nem == 0 && ngamma == 0 && nkaons == 0 && nother == 0) sample = 1;
      else if(npionscharge == 0 && npizerorecon == 0 && nprotons == 1 && otherpar == 0 && nem == 0 && ngamma == 0 && nkaons == 0 && nother == 0) sample = 2;
      else if(npionscharge == 1 && npizerorecon == 0) sample = 3;
      else if(npionscharge == 2 && npizerorecon == 0) sample = 4;
      else if(npionscharge == 0 && npizerorecon == 1) sample = 5;
      else if(npionscharge == 1 && npizerorecon == 1) sample = 6;
      else sample = 7;
    }
    else if(EvClass_reco == 1){ // cc-nue
      sample = 8;
    }
    else if(EvClass_reco == 2){ // nc
      if(npionscharge == 1 && npizerorecon == 0) sample = 10;
      else if(npionscharge == 0 && npizerorecon == 1) sample = 11;
      else sample = 12;
    }

    // Fill the tree
    FastMCTree->Fill();
  }

  return FastMCTree;
}
// ----------------------------------------------------------------------------
void ReadFastMC::make_binning_scheme_2D(){
  // FastMC Tree
  TTree *gstTree = ReadTree(inFile);

  //const int event_sample = 2; //index number of event sample as in enum in NDFit/NDSample.h
  //const int sampleIndex = 2;
  const int n_bins_x = 10;   //this must be an even number in this version of the macro to allow the division into zones
  const int n_bins_y = 8;   //this must be an even number in this version of the macro to allow the division into zones
  const double x_min = 0.0;
  const double x_max = 50.0;
  const double y_min = 0.0;
  const double y_max = 1.0;

  vector<double> x_values;
  vector<double> y_values;

  const int n_zone = 4;

  vector<double> zone_x_values[n_zone];
  vector<double> zone_y_values[n_zone];

  vector<double>::iterator valueiter;

  double bin_edge_x[n_bins_x+1][n_bins_y];
  double bin_edge_y[n_bins_x][n_bins_y+1];
  double zone_bin_edge_x[n_bins_x+1][n_bins_y] = {{0},{0}};
  double zone_bin_edge_y[n_bins_x][n_bins_y+1] = {{0},{0}};

  int bin_content[n_bins_x][n_bins_y] = {{0},{0}};
  int zone_bin_content[n_bins_x][n_bins_y] = {{0},{0}};

  double x_median, y_median;

  //TString selection = "sampleIndex==";
  //selection += Form("%d", event_sample);
  TString selection = "Ev_reco>=";
  //selection += "&&Ev_reco>=";
  selection += Form("%f", x_min);
  selection += "&&Ev_reco<=";
  selection += Form("%f", x_max);
  selection += "&&y_reco>=";
  selection += Form("%f", y_min);
  selection += "&&y_reco<=";
  selection += Form("%f", y_max);
  cout << "Selection = " << selection.Data() << endl;
  double mean_bin_content = gstTree->GetEntries(selection) / (n_bins_x * n_bins_y);

  double dev_sq_sum;

  cout<<endl;
  cout<<"Calculating optimal binning scheme in a single rectangular grid......"<<endl;
  cout<<endl;

  //put all x values into one vector and all y values into another vector
  for(Long64_t i = 0; i < gstTree->GetEntries(); i++)
    {
      gstTree->GetEntry(i);

      //if(sampleIndex == event_sample)
      //{
      if(Ev_reco >= x_min && Ev_reco <= x_max)
	x_values.push_back(Ev_reco);
      if(y_reco >=y_min && y_reco <= y_max)
	y_values.push_back(y_reco);
      //}
      
    }//end of loop over events

  //sort x values and make x bin edges such that each bin in x has equal number of x values (irrespective of y values)
  sort(x_values.begin(), x_values.end());

  for(int y_bin=0; y_bin<n_bins_y; y_bin++)
    bin_edge_x[0][y_bin] = 0.0;

  for(int x_edge=1; x_edge<n_bins_x; x_edge++)
    {
    valueiter = x_values.begin() + (int)(x_edge * x_values.size() / n_bins_x);
    for(int y_bin=0; y_bin<n_bins_y; y_bin++)
      bin_edge_x[x_edge][y_bin] = (*valueiter);
    }

  for(int y_bin=0; y_bin<n_bins_y; y_bin++)
    bin_edge_x[n_bins_x][y_bin] = x_max;
  
  //sort y values and make y bin edges such that each bin in y has equal number of y values (irrespective of x values)
  sort(y_values.begin(), y_values.end());

  for(int x_bin=0; x_bin<n_bins_x; x_bin++)
    bin_edge_y[x_bin][0] = 0.0;

  for(int y_edge=1; y_edge<n_bins_y; y_edge++)
    {
    valueiter = y_values.begin() + (int)(y_edge * y_values.size() / n_bins_y);
    for(int x_bin=0; x_bin<n_bins_x; x_bin++)
      bin_edge_y[x_bin][y_edge] = (*valueiter);
    }

  for(int x_bin=0; x_bin<n_bins_x; x_bin++)
    bin_edge_y[x_bin][n_bins_y] = y_max;

  //get bin contents for initial binning scheme which is a rectangular grid
  for(Long64_t i = 0; i < gstTree->GetEntries(); i++)
    {
    gstTree->GetEntry(i);

    //if(sampleIndex == event_sample)
    // {
    for(int x_bin = 1; x_bin <= n_bins_x; x_bin++)
      {
        for(int y_bin= 1; y_bin <= n_bins_y;y_bin++)
          {
	    if(Ev_reco > bin_edge_x[x_bin-1][y_bin-1] && Ev_reco <= bin_edge_x[x_bin][y_bin-1]
	       && y_reco > bin_edge_y[x_bin-1][y_bin-1] && y_reco <= bin_edge_y[x_bin-1][y_bin])
	      bin_content[x_bin-1][y_bin-1]++;
	  }
      }
    //}
    }//end of loop over events

  cout<<"Bin edges in x with single rectangular grid are:"<<endl;
  cout<<endl;
  cout<<"{";
  for(int j=0; j<=n_bins_x; j++)
    {
      if(j == n_bins_x)
        cout<<bin_edge_x[j][0];
      else
	cout<<bin_edge_x[j][0]<<",";
    }
  cout<<"};";
  
  cout<<endl;
  cout<<endl;
  
  cout<<"Bin edges in y with single rectangular grid are:"<<endl;
  cout<<endl;
  
  cout<<"{";
  for(int k=0; k<=n_bins_y; k++)
    { 
      if(k == n_bins_y)
	cout<<bin_edge_y[0][k];
      else    
	cout<<bin_edge_y[0][k]<<",";
    } 
  cout<<"};";
  
  cout<<endl;
  cout<<endl;
  
  dev_sq_sum = 0.0;

  cout<<"Bin contents with single rectangular grid are:"<<endl;
  cout<<endl;

  for(int k=n_bins_y; k>=1; k--)
      {
	for(int j=1; j<=n_bins_x; j++)
	  {
	    cout<<"    "<<bin_content[j-1][k-1];
	    dev_sq_sum += (bin_content[j-1][k-1] - mean_bin_content) * (bin_content[j-1][k-1] - mean_bin_content);
	  }
	cout<<endl;
      }

  cout<<endl;
  cout<<endl;
  
  cout<<"Mean bin content is "<<mean_bin_content<<endl;
  cout<<endl;
  cout<<"Standard deviation of bin contents with single rectangular grid is "<<sqrt(dev_sq_sum / ((n_bins_x * n_bins_y) - 1))<<endl;
  
  cout<<endl;
  cout<<endl;

  cout<<endl;
  cout<<"Calculating optimal binning scheme using 4 equal-sized zones......"<<endl;
  cout<<endl;
  cout<<endl;

  valueiter = x_values.begin() + (int)(0.5 * x_values.size());
  x_median = (*valueiter);
  valueiter = y_values.begin() + (int)(0.5 * y_values.size());
  y_median = (*valueiter);

  cout << "x_median = " << x_median << " ,  y_median = " <<  y_median << endl;
  cout<<endl;

  for(Long64_t i = 0; i < gstTree->GetEntries(); i++)
    {
      gstTree->GetEntry(i);

      //if(sampleIndex == event_sample)
      //{
      if(Ev_reco >= x_min && Ev_reco <= x_median && y_reco >= y_min && y_reco <= y_median)
	{
	  zone_x_values[0].push_back(Ev_reco);
	  zone_y_values[0].push_back(y_reco);
	}
      if(Ev_reco > x_median && Ev_reco <= x_max && y_reco >= y_min && y_reco <= y_median)
	{
	  zone_x_values[1].push_back(Ev_reco);
	  zone_y_values[1].push_back(y_reco);
	}
      if(Ev_reco >= x_min && Ev_reco <= x_median && y_reco > y_median && y_reco <= y_max)
	{
	  zone_x_values[2].push_back(Ev_reco);
	  zone_y_values[2].push_back(y_reco);
	}
      if(Ev_reco > x_median && Ev_reco <= x_max && y_reco > y_median && y_reco <= y_max)
	{
	  zone_x_values[3].push_back(Ev_reco);
	  zone_y_values[3].push_back(y_reco);
	}
      //}
    }//end of loop over events
  
  sort(zone_x_values[0].begin(), zone_x_values[0].end());

  for(int y_bin=0; y_bin<n_bins_y/2; y_bin++)
    zone_bin_edge_x[0][y_bin] = x_min; //0.0;

  for(int x_edge=1; x_edge<n_bins_x/2; x_edge++)
    {
    valueiter = zone_x_values[0].begin() + (int)(x_edge * zone_x_values[0].size() / (n_bins_x/2));
    for(int y_bin=0; y_bin<n_bins_y/2; y_bin++)
      zone_bin_edge_x[x_edge][y_bin] = (*valueiter);
    }

  for(int y_bin=0; y_bin<n_bins_y/2; y_bin++)
    zone_bin_edge_x[n_bins_x/2][y_bin] = x_median;

  sort(zone_x_values[1].begin(), zone_x_values[1].end());

  for(int y_bin=0; y_bin<n_bins_y/2; y_bin++)
    zone_bin_edge_x[n_bins_x/2][y_bin] = x_median;

  for(int x_edge=(n_bins_x/2)+1; x_edge<=n_bins_x; x_edge++)
    {
    valueiter = zone_x_values[1].begin() + (int)((x_edge-n_bins_x/2) * zone_x_values[1].size() / (n_bins_x/2));
    for(int y_bin=0; y_bin<n_bins_y/2; y_bin++)
      zone_bin_edge_x[x_edge][y_bin] = (*valueiter);
    }

  for(int y_bin=0; y_bin<n_bins_y/2; y_bin++)
    zone_bin_edge_x[n_bins_x][y_bin] = x_max;

  sort(zone_x_values[2].begin(), zone_x_values[2].end());

  for(int y_bin=n_bins_y/2; y_bin<n_bins_y; y_bin++)
    zone_bin_edge_x[0][y_bin] = x_min;

  for(int x_edge=1; x_edge<n_bins_x/2; x_edge++)
    {
    valueiter = zone_x_values[2].begin() + (int)(x_edge * zone_x_values[2].size() / (n_bins_x/2));
    for(int y_bin=n_bins_y/2; y_bin<n_bins_y; y_bin++)
      zone_bin_edge_x[x_edge][y_bin] = (*valueiter);
    }

  for(int y_bin=n_bins_y/2; y_bin<n_bins_y; y_bin++)
    zone_bin_edge_x[n_bins_x/2][y_bin] = x_median;

  sort(zone_x_values[3].begin(), zone_x_values[3].end());

  for(int y_bin=n_bins_y/2; y_bin<n_bins_y; y_bin++)
    zone_bin_edge_x[n_bins_x/2][y_bin] = x_median;

  for(int x_edge=(n_bins_x/2)+1; x_edge<=n_bins_x; x_edge++)
    {
    valueiter = zone_x_values[3].begin() + (int)((x_edge-n_bins_x/2) * zone_x_values[3].size() / (n_bins_x/2));
    for(int y_bin=n_bins_y/2; y_bin<n_bins_y; y_bin++)
      zone_bin_edge_x[x_edge][y_bin] = (*valueiter);
    }

  for(int y_bin=n_bins_y/2; y_bin<n_bins_y; y_bin++)
    zone_bin_edge_x[n_bins_x][y_bin] = x_max;

  sort(zone_y_values[0].begin(), zone_y_values[0].end());

  for(int x_bin=0; x_bin<n_bins_x/2; x_bin++)
    zone_bin_edge_y[x_bin][0] = y_min;

  for(int y_edge=1; y_edge<=n_bins_y/2; y_edge++)
    {
    valueiter = zone_y_values[0].begin() + (int)(y_edge * zone_y_values[0].size() / (n_bins_y/2));
    for(int x_bin=0; x_bin<n_bins_x/2; x_bin++)
      zone_bin_edge_y[x_bin][y_edge] = (*valueiter);
    }

  for(int x_bin=0; x_bin<n_bins_x/2; x_bin++)
    zone_bin_edge_y[x_bin][n_bins_y/2] = y_median;

  sort(zone_y_values[1].begin(), zone_y_values[1].end());

  for(int x_bin=n_bins_x/2; x_bin<n_bins_x; x_bin++)
    zone_bin_edge_y[x_bin][0] = y_min;

  for(int y_edge=1; y_edge<n_bins_y/2; y_edge++)
    {
    valueiter = zone_y_values[1].begin() + (int)(y_edge * zone_y_values[1].size() / (n_bins_y/2));
    for(int x_bin=n_bins_x/2; x_bin<n_bins_x; x_bin++)
      zone_bin_edge_y[x_bin][y_edge] = (*valueiter);
    }

  for(int x_bin=n_bins_x/2; x_bin<n_bins_x; x_bin++)
    zone_bin_edge_y[x_bin][n_bins_y/2] = y_median;

  sort(zone_y_values[2].begin(), zone_y_values[2].end());

  for(int x_bin=0; x_bin<n_bins_x/2; x_bin++)
    zone_bin_edge_y[x_bin][(n_bins_y/2)+1] = y_median;

  for(int y_edge=(n_bins_y/2)+1; y_edge<=n_bins_y; y_edge++)
    {
    valueiter = zone_y_values[2].begin() + (int)((y_edge-n_bins_y/2) * zone_y_values[2].size() / (n_bins_y/2));
    for(int x_bin=0; x_bin<n_bins_x/2; x_bin++)
      zone_bin_edge_y[x_bin][y_edge] = (*valueiter);
    }

  for(int x_bin=0; x_bin<n_bins_x/2; x_bin++)
    zone_bin_edge_y[x_bin][n_bins_y] = y_max;

  sort(zone_y_values[3].begin(), zone_y_values[3].end());

  for(int x_bin=n_bins_x/2; x_bin<n_bins_x; x_bin++)
    zone_bin_edge_y[x_bin][n_bins_y/2] = y_median;

  for(int y_edge=(n_bins_y/2)+1; y_edge<n_bins_y; y_edge++)
    {
    valueiter = zone_y_values[3].begin() + (int)((y_edge-n_bins_y/2) * zone_y_values[3].size() / (n_bins_y/2));
    for(int x_bin=n_bins_x/2; x_bin<n_bins_x; x_bin++)
      zone_bin_edge_y[x_bin][y_edge] = (*valueiter);
    }

  for(int x_bin=n_bins_x/2; x_bin<n_bins_x; x_bin++)
    zone_bin_edge_y[x_bin][n_bins_y] = y_max;

  for(Long64_t i = 0; i < gstTree->GetEntries(); i++)
    {
      gstTree->GetEntry(i);
      
      //if(sampleIndex == event_sample)
      //{
      for(int x_bin = 1; x_bin <= n_bins_x; x_bin++)
	{
	  for(int y_bin= 1; y_bin <= n_bins_y;y_bin++)
	    {
	      if(Ev_reco > zone_bin_edge_x[x_bin-1][y_bin-1] && Ev_reco <= zone_bin_edge_x[x_bin][y_bin-1]
		 && y_reco > zone_bin_edge_y[x_bin-1][y_bin-1] && y_reco <= zone_bin_edge_y[x_bin-1][y_bin])
		zone_bin_content[x_bin-1][y_bin-1]++;
	    }
	}
      //}
    }//end of loop over events

  cout<<"Bin edges in x with 4 zones are:"<<endl;
  cout<<endl;
  for(int k=n_bins_y-1; k>=0; k--)
    {
      for(int j=0; j<=n_bins_x; j++)
	{
	  cout<<"    "<<zone_bin_edge_x[j][k];
	}
      cout<<endl;
    }

  cout<<endl;
  cout<<endl;
  
  cout<<"Bin edges in y with 4 zones are:"<<endl;
  cout<<endl;
  
  for(int k=n_bins_y; k>=0; k--)
    {
      for(int j=0; j<n_bins_x; j++)// -1 George
	{
	  cout<<"    "<<zone_bin_edge_y[j][k];
	}
      cout<<endl;
    }
  
  cout<<endl;
  cout<<endl;
  
  dev_sq_sum = 0.0;

  cout<<"Bin contents with 4 zones are:"<<endl;
  cout<<endl;

  for(int k=n_bins_y; k>=1; k--)
    {
      for(int j=1; j<=n_bins_x; j++)
	{
	  cout<<"    "<<zone_bin_content[j-1][k-1];
	  dev_sq_sum += (zone_bin_content[j-1][k-1] - mean_bin_content) * (zone_bin_content[j-1][k-1] - mean_bin_content);
	}
      cout<<endl;
    }
  
  cout<<endl;
  cout<<endl;
  
  cout<<"Mean bin content is "<<mean_bin_content<<endl;
  cout<<endl;
  cout<<"Standard deviation of bin contents with 4 zones is "<<sqrt(dev_sq_sum / ((n_bins_x * n_bins_y) - 1))<<endl;
  
  cout<<endl;
  cout<<endl;
  
}
// ----------------------------------------------------------------------------
vector<TH1*> ReadFastMC::SelectCCnPi(int npions, int npi0){

  // Maximum number of charge pion to select
  bool limit = false;
  if(npions > npionnum){
    limit = true;
    cout << "You choose to select " <<  npions << " final state charge pions."
	 << "The maximum number to select should be 2."
	 << " This will go in the > 2 category." << endl;
  }

  // The histogram array
  vector<TH1*> histarray;
  // The selection - choose true for nc events
  int whattoselect = WhatToSelect();
  // The ratio of neutrino-antineutrino in the beam
  double fluxweight = FluxWeight(neutrinoPDG, -neutrinoPDG);

  // Histogram name
  stringstream ss, sspi0;
  ss << npions;
  string strnpions = ss.str();
  sspi0 << npi0;
  string strnpi0 = sspi0.str();

  string ccqel = "ERecoNeutrinoCCQEL_" + strnpions + "_" + strnpi0;
  string ccres = "ERecoNeutrinoCCRES_" + strnpions + "_" + strnpi0;
  string ccdis = "ERecoNeutrinoCCDIS_" + strnpions + "_" + strnpi0;
  string cccoh = "ERecoNeutrinoCCCOH_" + strnpions + "_" + strnpi0;
  string ccoth = "ERecoNeutrinoCCOTH_" + strnpions + "_" + strnpi0;
  string ncall = "ERecoNeutrinoNCALL_" + strnpions + "_" + strnpi0;
  string anucc = "ERecoNeutrinoANuCC_" + strnpions + "_" + strnpi0;

  string histarrayname = "ERecoNeutrino_" + strnpions + "_" + strnpi0;

  // Histograms
  TH1D* ERecoNeutrinoCCQEL = new TH1D(ccqel.c_str(),"",bin,min,max);
  TH1D* ERecoNeutrinoCCRES = new TH1D(ccres.c_str(),"",bin,min,max);
  TH1D* ERecoNeutrinoCCDIS = new TH1D(ccdis.c_str(),"",bin,min,max);
  TH1D* ERecoNeutrinoCCCOH = new TH1D(cccoh.c_str(),"",bin,min,max);
  TH1D* ERecoNeutrinoCCOTH = new TH1D(ccoth.c_str(),"",bin,min,max);
  TH1D* ERecoNeutrinoNCALL = new TH1D(ncall.c_str(),"",bin,min,max);
  TH1D* ERecoNeutrinoANuCC = new TH1D(anucc.c_str(),"",bin,min,max);

  TTree *gstTree = ReadTree(inFile);

  int numuevents = 0; int anumuevents = 0;

  for(int i = 0; i < gstTree->GetEntries(); i++){
    gstTree->GetEntry(i);

    if(neu == neutrinoPDG){
      if(numuevents == nevents){continue;}
      numuevents++;
    }
    else if(neu == -neutrinoPDG){
      if(anumuevents == nevents){continue;}
      anumuevents++;
    }

    // No recon neutrino energy? -> continue
    if(Ev_reco < enureconcut){continue;}

    // Number of final state pion
    int npizero = 0; int npiplus = 0; int npiminus = 0;
    // Other em activity
    int nem = 0; int ngamma = 0;
    for(int k = 0; k < nf; k++){
      if(pdgf[k] == 22 && Ef_reco[k] > egammareconcut) // photons
	ngamma++;
      else if(abs(pdgf[k]) == 11 && Ef_reco[k] > eelectronreconcut) // e-/e+
	nem++;
      else if(pdgf[k] == 211  && Ef_reco[k] > epionreconcut) // pi+
	npiplus++;
      else if(pdgf[k] == -211 && Ef_reco[k] > epionreconcut) // pi-
	npiminus++;
      else if(pdgf[k] == 111  && Ef_reco[k] > egammareconcut) // pi0
	npizero++;
    }

    int npionscharge = npiplus + npiminus;

    // Select the number of charged pions
    if(!limit && npionscharge != npions){continue;}
    if(limit) npions = npionnum + 1; // odd!!!!
    if(limit  && npionscharge <  npions){continue;}
    // Select the number of pi0s
    if(npizero != npi0){continue;}
    // No other EM activity - temporary
    if(nem > 0){continue;}
    if(ngamma  > 0){continue;}
    // For pi0 
    //if(npi0 !=0 && nEMf != 2*npi0){continue;}

    // This works only for single pi0 events
    if(npizero == 1 && nEMf == 2){
      double par = sqrt(EMpxf_reco[0]*EMpxf_reco[0] + EMpyf_reco[0]*EMpyf_reco[0] + EMpzf_reco[0]*EMpzf_reco[0]);
      double pbr = sqrt(EMpxf_reco[1]*EMpxf_reco[1] + EMpyf_reco[1]*EMpyf_reco[1] + EMpzf_reco[1]*EMpzf_reco[1]);
      
      double aDOTbr = EMpxf_reco[0]*EMpxf_reco[1] + EMpyf_reco[0]*EMpyf_reco[1] + EMpzf_reco[0]*EMpzf_reco[1];
      double costhr = aDOTbr / (par * pbr);
      double imr = sqrt(2.0 *EMEf_reco[0]  *EMEf_reco[1]  * ( 1.0 - costhr));
      
      // Invariant mass cut
      if( fabs(imr - 0.13498) > pi0invmass){continue;}
    }
 
    if(neu == neutrinoPDG){ // selection
      if(EvClass_reco == whattoselect){ // cc-numu, cc-nue or nc
	if(cc){
	  if(qel)
	    ERecoNeutrinoCCQEL->Fill(Ev_reco);
	  else if(res)
	    ERecoNeutrinoCCRES->Fill(Ev_reco);
	  else if(dis)
	    ERecoNeutrinoCCDIS->Fill(Ev_reco);
	  else if(coh)
	    ERecoNeutrinoCCCOH->Fill(Ev_reco);
	  else
	    ERecoNeutrinoCCOTH->Fill(Ev_reco);
	} // cc
	else if(nc)
	  ERecoNeutrinoNCALL->Fill(Ev_reco);
      } // n-pions
    } // selection
    else if(neu == -neutrinoPDG){ // bkg selection same neutrino species
      if(EvClass_reco == whattoselect){ // cc-numu or cc-nue
	if(cc)
	  ERecoNeutrinoANuCC->Fill(Ev_reco,fluxweight);
	else if(nc) // nc go all in the same histogram
	  ERecoNeutrinoNCALL->Fill(Ev_reco,fluxweight);
      }
    }
  } // event loop

  histarray.push_back(ERecoNeutrinoANuCC);
  histarray.push_back(ERecoNeutrinoNCALL);
  histarray.push_back(ERecoNeutrinoCCOTH);
  histarray.push_back(ERecoNeutrinoCCCOH);
  histarray.push_back(ERecoNeutrinoCCDIS);
  histarray.push_back(ERecoNeutrinoCCRES);
  histarray.push_back(ERecoNeutrinoCCQEL);

  gstTree->Delete();

  return histarray;
}
// ----------------------------------------------------------------------------
vector<TH1*> ReadFastMC::SelectNCnPi(int npions, int npi0){

  // Maximum number of charge pion to select
  bool limit = false;
  if(npions > npionnum){
    limit = true;
    cout << "You choose to select " <<  npions << " final state charge pions."
	 << "The maximum number to select should be 2."
	 << " This will go in the > 2 category." << endl;
  }

  // The histogram array
  vector<TH1*> histarray;
  // The selection - choose true for nc events
  int whattoselect = WhatToSelect(true);
  // The ratio of neutrino-antineutrino in the beam
  double fluxweight = FluxWeight(neutrinoPDG, -neutrinoPDG);

  // Histogram name
  stringstream ss, sspi0;
  ss << npions;
  string strnpions = ss.str();
  sspi0 << npi0;
  string strnpi0 = sspi0.str();

  string ncqel = "ERecoNeutrinoNCQEL_" + strnpions + "_" + strnpi0;
  string ncres = "ERecoNeutrinoNCRES_" + strnpions + "_" + strnpi0;
  string ncdis = "ERecoNeutrinoNCDIS_" + strnpions + "_" + strnpi0;
  string nccoh = "ERecoNeutrinoNCCOH_" + strnpions + "_" + strnpi0;
  string ncoth = "ERecoNeutrinoNCOTH_" + strnpions + "_" + strnpi0;
  string ccall = "ERecoNeutrinoCCALL_" + strnpions + "_" + strnpi0;
  string anuca = "ERecoNeutrinoANuCA_" + strnpions + "_" + strnpi0;
  string anuna = "ERecoNeutrinoANuNA_" + strnpions + "_" + strnpi0;

  string histarrayname = "ERecoNeutrino_" + strnpions + "_" + strnpi0;

  // Histograms
  TH1D* ERecoNeutrinoNCQEL = new TH1D(ncqel.c_str(),"",bin,min,max);
  TH1D* ERecoNeutrinoNCRES = new TH1D(ncres.c_str(),"",bin,min,max);
  TH1D* ERecoNeutrinoNCDIS = new TH1D(ncdis.c_str(),"",bin,min,max);
  TH1D* ERecoNeutrinoNCCOH = new TH1D(nccoh.c_str(),"",bin,min,max);
  TH1D* ERecoNeutrinoNCOTH = new TH1D(ncoth.c_str(),"",bin,min,max);
  TH1D* ERecoNeutrinoCCALL = new TH1D(ccall.c_str(),"",bin,min,max);
  TH1D* ERecoNeutrinoANuCA = new TH1D(anuca.c_str(),"",bin,min,max);
  TH1D* ERecoNeutrinoANuNA = new TH1D(anuna.c_str(),"",bin,min,max);

  TTree *gstTree = ReadTree(inFile);

  int numuevents = 0; int anumuevents = 0; 

  for(int i = 0; i < gstTree->GetEntries(); i++){
    gstTree->GetEntry(i);

    if(neu == neutrinoPDG){
      if(numuevents == nevents){continue;}
      numuevents++;
    }
    else if(neu == -neutrinoPDG){
      if(anumuevents == nevents){continue;}
      anumuevents++;
    }

    // No recon neutrino energy? -> continue
    if(Ev_reco < enureconcut){continue;}

    // Number of final state pion
    int npizero = 0; int npiplus = 0; int npiminus = 0;
    // Other em activity
    int nem = 0; int ngamma = 0;
    for(int k = 0; k < nf; k++){
      if(pdgf[k] == 22 && Ef_reco[k] > egammareconcut) // photons
	ngamma++;
      else if(abs(pdgf[k]) == 11 && Ef_reco[k] > eelectronreconcut) // e-/e+
	nem++;
      else if(pdgf[k] == 211  && Ef_reco[k] > epionreconcut) // pi+
	npiplus++;
      else if(pdgf[k] == -211 && Ef_reco[k] > epionreconcut) // pi-
	npiminus++;
      else if(pdgf[k] == 111  && Ef_reco[k] > egammareconcut) // pi0
	npizero++;
    }

    int npionscharge = npiplus + npiminus;

    // Select the number of charged pions
    if(!limit && npionscharge != npions){continue;}
    if(limit) npions = npionnum + 1; // odd!!!!
    if(limit  && npionscharge <  npions){continue;}
    // Select the number of pi0s
    if(npizero != npi0){continue;}
    // No other EM activity - temporary
    if(nem > 0){continue;}
    if(ngamma  > 0){continue;}
    // For pi0 
    //if(npi0 !=0 && nEMf != 2*npi0){continue;}

    // This works only for single pi0 events
    if(npizero == 1 && nEMf == 2){
      double par = sqrt(EMpxf_reco[0]*EMpxf_reco[0] + EMpyf_reco[0]*EMpyf_reco[0] + EMpzf_reco[0]*EMpzf_reco[0]);
      double pbr = sqrt(EMpxf_reco[1]*EMpxf_reco[1] + EMpyf_reco[1]*EMpyf_reco[1] + EMpzf_reco[1]*EMpzf_reco[1]);
      
      double aDOTbr = EMpxf_reco[0]*EMpxf_reco[1] + EMpyf_reco[0]*EMpyf_reco[1] + EMpzf_reco[0]*EMpzf_reco[1];
      double costhr = aDOTbr / (par * pbr);
      double imr = sqrt(2.0 *EMEf_reco[0]  *EMEf_reco[1]  * ( 1.0 - costhr));
      
      // Invariant mass cut
      if( fabs(imr - 0.13498) > pi0invmass){continue;}
    }
 
    if(neu == neutrinoPDG){ // selection
      if(EvClass_reco == whattoselect){ // nc
	if(nc){
	  if(qel)
	    ERecoNeutrinoNCQEL->Fill(Ev_reco);
	  else if(res)
	    ERecoNeutrinoNCRES->Fill(Ev_reco);
	  else if(dis)
	    ERecoNeutrinoNCDIS->Fill(Ev_reco);
	  else if(coh)
	    ERecoNeutrinoNCCOH->Fill(Ev_reco);
	  else
	    ERecoNeutrinoNCOTH->Fill(Ev_reco);
	} // nc
	else if(cc)
	  ERecoNeutrinoCCALL->Fill(Ev_reco);
      } // n-pions
    } // selection
    else if(neu == -neutrinoPDG){ // bkg selection same neutrino species
      if(EvClass_reco == whattoselect){ // nc
	if(cc)
	  ERecoNeutrinoANuCA->Fill(Ev_reco,fluxweight);
	else if(nc)
	  ERecoNeutrinoANuNA->Fill(Ev_reco,fluxweight);
      }
    }
  } // event loop
 
  histarray.push_back(ERecoNeutrinoANuNA);
  histarray.push_back(ERecoNeutrinoANuCA);
  histarray.push_back(ERecoNeutrinoCCALL);
  histarray.push_back(ERecoNeutrinoNCOTH);
  histarray.push_back(ERecoNeutrinoNCCOH);
  histarray.push_back(ERecoNeutrinoNCDIS);
  histarray.push_back(ERecoNeutrinoNCRES);
  histarray.push_back(ERecoNeutrinoNCQEL);

  gstTree->Delete();

  return histarray;

}
// ----------------------------------------------------------------------------
bool ReadFastMC::ChargeFlip(int seed, double momentum){

  if(momentum == 0)
    return false;

  // Random generator
  TRandom3 *random = new TRandom3();

  // Functions for the charge flip parameterization
  TF1 *ft = new TF1("ft","expo");
  ft->SetParameter(0,ChargeConfTrLConst);
  ft->SetParameter(1,ChargeConfTrLSlope);
  TF1 *fp = new TF1("fp","expo");
  fp->SetParameter(0,ChargeConfMomConst);
  fp->SetParameter(1,ChargeConfMomSlope);

  random->SetSeed(seed);

  double cmisid = 0.0;
  int rcnum = random->Integer(1000);
  if(momentum > 0.8 && momentum < 5){
    cmisid = fp->Eval(momentum*1000);
  }
  else if(momentum >= 5){
    cmisid = fp->Eval(5*1000);
  }
  else if(momentum > 0.5 && momentum <= 0.8){
    cmisid = fp->Eval(0.8*1000)*1.5;
  }
  else if(momentum <= 0.5){
    cmisid = fp->Eval(0.8*1000)*5;
  }

  random->Delete();
  ft->Delete();
  fp->Delete();

  // Charge flip
  if(rcnum < cmisid*1000)
    return true;
  else
    return false;

}
// ----------------------------------------------------------------------------
TTree* ReadFastMC::ReadTree(string f){

  // Access the fast mc tree
  TFile *File = new TFile(f.c_str(),"READ");
  TTree *gstTree = (TTree*)File->Get("gst");
  // Tree branches
  gstTree->SetBranchAddress("iev",         &iev);
  gstTree->SetBranchAddress("neu",         &neu);
  gstTree->SetBranchAddress("neut_code",   &neut_code);
  gstTree->SetBranchAddress("qel",         &qel);
  gstTree->SetBranchAddress("mec",         &mec);
  gstTree->SetBranchAddress("res",         &res);
  gstTree->SetBranchAddress("dis",         &dis);
  gstTree->SetBranchAddress("coh",         &coh);
  gstTree->SetBranchAddress("cohe",        &cohe);
  gstTree->SetBranchAddress("dfr",         &dfr);
  gstTree->SetBranchAddress("imd",         &imd);
  gstTree->SetBranchAddress("imda",        &imda);
  gstTree->SetBranchAddress("nuel",        &nuel);
  gstTree->SetBranchAddress("em",          &em);
  gstTree->SetBranchAddress("cc",          &cc);
  gstTree->SetBranchAddress("nc",          &nc);
  gstTree->SetBranchAddress("charm",       &charm);

  gstTree->SetBranchAddress("Ev_reco",     &Ev_reco);
  gstTree->SetBranchAddress("Ev",          &Ev);
  gstTree->SetBranchAddress("Ehad",        &Ehad);
  gstTree->SetBranchAddress("EvB_reco",    &EvB_reco);
  gstTree->SetBranchAddress("EvUB_reco",   &EvUB_reco);
  gstTree->SetBranchAddress("Ehad_reco",   &Ehad_reco);
  gstTree->SetBranchAddress("EhadB_reco",  &EhadB_reco);
  gstTree->SetBranchAddress("EhadUB_reco", &EhadUB_reco);
  gstTree->SetBranchAddress("pxv_reco",    &pxv_reco);
  gstTree->SetBranchAddress("pyv_reco",    &pyv_reco);
  gstTree->SetBranchAddress("pzv_reco",    &pzv_reco);

  gstTree->SetBranchAddress("wght",        &wght);
  gstTree->SetBranchAddress("POTWeight",   &POTWeight);
  gstTree->SetBranchAddress("EvClass_reco",&EvClass_reco);
  gstTree->SetBranchAddress("isQE_reco",   &isQE_reco);
  gstTree->SetBranchAddress("hasElikeEM",  &hasElikeEM);
  gstTree->SetBranchAddress("IsContv_reco",&IsContv_reco);

  gstTree->SetBranchAddress("Pdgl",        &Pdgl);
  gstTree->SetBranchAddress("El",          &El);
  gstTree->SetBranchAddress("pxl",         &pxl);
  gstTree->SetBranchAddress("pyl",         &pyl);
  gstTree->SetBranchAddress("pzl",         &pzl);
  gstTree->SetBranchAddress("pl",          &pl);
  gstTree->SetBranchAddress("cthl",        &cthl);
  gstTree->SetBranchAddress("PdgL",        &PdgL);
  gstTree->SetBranchAddress("EL",          &EL);
  gstTree->SetBranchAddress("pxL",         &pxL);
  gstTree->SetBranchAddress("pyL",         &pyL);
  gstTree->SetBranchAddress("pzL",         &pzL);
  gstTree->SetBranchAddress("pL",          &pL);
  gstTree->SetBranchAddress("cthL",        &cthL);

  gstTree->SetBranchAddress("PdgL_reco",   &PdgL_reco);
  gstTree->SetBranchAddress("EL_reco",     &EL_reco);
  gstTree->SetBranchAddress("pxL_reco",    &pxL_reco);
  gstTree->SetBranchAddress("pyL_reco",    &pyL_reco);
  gstTree->SetBranchAddress("pzL_reco",    &pzL_reco);
  gstTree->SetBranchAddress("pL_reco",     &pL_reco);
  gstTree->SetBranchAddress("cthL_reco",   &cthL_reco);
  gstTree->SetBranchAddress("TrkL_reco",   &TrkL_reco);
  gstTree->SetBranchAddress("IsContL_reco",&IsContL_reco);
 
  gstTree->SetBranchAddress("nf",          &nf);
  gstTree->SetBranchAddress("nfp",         &nfp);
  gstTree->SetBranchAddress("nfn",         &nfn);
  gstTree->SetBranchAddress("nfpip",       &nfpip);
  gstTree->SetBranchAddress("nfpim",       &nfpim);
  gstTree->SetBranchAddress("nfpi0",       &nfpi0);

  gstTree->SetBranchAddress("ni",          &ni);
  gstTree->SetBranchAddress("nip",         &nip);
  gstTree->SetBranchAddress("nin",         &nin);
  gstTree->SetBranchAddress("nipip",       &nipip);
  gstTree->SetBranchAddress("nipim",       &nipim);
  gstTree->SetBranchAddress("nipi0",       &nipi0);

  gstTree->SetBranchAddress("pdgi",   &pdgi);
  
  gstTree->SetBranchAddress("pdgf",   &pdgf);
  gstTree->SetBranchAddress("pf",   &pf);
  gstTree->SetBranchAddress("Ef",   &Ef);
  gstTree->SetBranchAddress("p0f",   &p0f);
  gstTree->SetBranchAddress("pxf",   &pxf);
  gstTree->SetBranchAddress("pyf",   &pyf);
  gstTree->SetBranchAddress("pzf",   &pzf);
  gstTree->SetBranchAddress("cthf",   &cthf);
  gstTree->SetBranchAddress("Ef_reco",   &Ef_reco);
  gstTree->SetBranchAddress("p0f_reco",   &p0f_reco);
  gstTree->SetBranchAddress("pxf_reco",   &pxf_reco);
  gstTree->SetBranchAddress("pyf_reco",   &pyf_reco);
  gstTree->SetBranchAddress("pzf_reco",   &pzf_reco);
  gstTree->SetBranchAddress("Trkf_reco",   &Trkf_reco);
  gstTree->SetBranchAddress("cthf_reco",   &cthf_reco);

  gstTree->SetBranchAddress("nEMf",            &nEMf);
  gstTree->SetBranchAddress("EMEf_reco",       &EMEf_reco);
  gstTree->SetBranchAddress("EMpdgf",          &EMpdgf);
  gstTree->SetBranchAddress("EMcthf_reco",     &EMcthf_reco);
  gstTree->SetBranchAddress("EMPizMass_reco",  &EMPizMass_reco);
  gstTree->SetBranchAddress("EMpxf_reco",      &EMpxf_reco);
  gstTree->SetBranchAddress("EMpyf_reco",      &EMpyf_reco);
  gstTree->SetBranchAddress("EMpzf_reco",      &EMpzf_reco);

  gstTree->SetBranchAddress("EMEf",            &EMEf);
  gstTree->SetBranchAddress("EMcthf",          &EMcthf);
  gstTree->SetBranchAddress("EMpxf",           &EMpxf);
  gstTree->SetBranchAddress("EMpyf",           &EMpyf);
  gstTree->SetBranchAddress("EMpzf",           &EMpzf);

  gstTree->SetBranchAddress("Q2",            &Q2);
  gstTree->SetBranchAddress("Q2s",           &Q2s);
  gstTree->SetBranchAddress("Q2_reco",       &Q2_reco);
  gstTree->SetBranchAddress("W",             &W);
  gstTree->SetBranchAddress("W_reco",        &W_reco);
  gstTree->SetBranchAddress("y",             &y);
  gstTree->SetBranchAddress("ys",            &ys);
  gstTree->SetBranchAddress("y_reco",        &y_reco);

  gstTree->SetBranchAddress("vtxx",          &vtxx);
  gstTree->SetBranchAddress("vtxy",          &vtxy);
  gstTree->SetBranchAddress("vtxz",          &vtxz);

  //gstTree->SetBranchAddress("",            &);
  
  if(reweight){
    gstTree->SetBranchAddress("frw7",   &frw7);
    gstTree->SetBranchAddress("rw7",    &rw7);

    gstTree->SetBranchAddress("rw7_qelCCma",   &rw7_qelCCma);
    gstTree->SetBranchAddress("rw7_resCCma",   &rw7_resCCma);
  }

  return gstTree;

}
