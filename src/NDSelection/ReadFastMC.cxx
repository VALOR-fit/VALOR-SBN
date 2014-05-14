//________________________________________________________________________________________
/*

Copyright (c) 2010-2014, The VALOR group. All rights reserved.

ChangeLog:

*/
//________________________________________________________________________________________
#include "ReadFastMC.h"

#include <math.h>
#include <ostream>

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
      if(line.find("Detector") != string::npos){ // near or far detector
	size_t found = line.find(" ");
	detector = line.substr(found);
	detector.erase(detector.begin());
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
      if(line.find("ReconPiPMEnergyCut") != string::npos){ // recon particle energy
        size_t found = line.find(" ");
        string ene = line.substr(found);
        ene.erase(ene.begin());
        epionreconcut = atof(ene.c_str());
      }
      if(line.find("ReconProtonEnergyCut") != string::npos){ // recon particle energy
        size_t found = line.find(" ");
        string ene = line.substr(found);
        ene.erase(ene.begin());
        eprotonreconcut = atof(ene.c_str());
      }
      if(line.find("ReconGammaEnergyCut") != string::npos){ // recon particle energy
        size_t found = line.find(" ");
        string ene = line.substr(found);
        ene.erase(ene.begin());
        egammareconcut = atof(ene.c_str());
      }
      if(line.find("ReconElectronEnergyCut") != string::npos){ // recon particle energy
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
  XMLNodePointer_t root_node = xml->DocGetRootElement(xmldoc);
 
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
  FastMCTree->Branch("rectionmode", &reactionmode,"reactionmode/I");

  if(debugtree){
    FastMCTree->Branch("neut_code",           &neut_code,           "neut_code/I");
    FastMCTree->Branch("ys",                  &ys,                  "ys/D");
    FastMCTree->Branch("Q2",                  &Q2,                  "Q2/D");
    FastMCTree->Branch("Q2_reco",             &Q2_reco,             "Q2_reco/D");
    FastMCTree->Branch("NPionMisIDAsProton",  &NPionMisIDAsProton,  "NPionMisIDAsProton/I");
    FastMCTree->Branch("NProtonMisIDAsPion",  &NProtonMisIDAsPion,  "NProtonMisIDAsPion/I");
    FastMCTree->Branch("LeptonChargeFlip",    &LeptonChargeFlip,    "LeptonChargeFlip/O");
  }

  // Random generator
  TRandom3 *random = new TRandom3();

  // Functions for the charge flip parameterization
  TF1 *ft = new TF1("ft","expo");
  ft->SetParameter(0,ChargeConfTrLConst);
  ft->SetParameter(1,ChargeConfTrLSlope);
  TF1 *fp = new TF1("fp","expo");
  fp->SetParameter(0,ChargeConfMomConst);
  fp->SetParameter(1,ChargeConfMomSlope);

  const double pionmass   = 0.13957;
  const double pizeromass = 0.13498;

  FastMCTree->SetDirectory(0);
  for(int i = 0; i < gstTree->GetEntries(); i++){
    gstTree->GetEntry(i);

    // Initialize
    NPionMisIDAsProton = 0;
    NProtonMisIDAsPion = 0;
    LeptonChargeFlip = false;

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

    // Apply the charge flip cut only for CC selection
    if(EvClass_reco < 2){
      random->SetSeed(seed*seed + i);
      double lmom = sqrt(pxL_reco*pxL_reco + pyL_reco*pyL_reco + pzL_reco*pzL_reco);
      
      double cmisid = 0.0;
      int rcnum = random->Integer(1000);
      if(lmom > 0.8 && lmom < 5){
	cmisid = fp->Eval(lmom*1000);
      }
      else if(lmom >= 5){
	cmisid = fp->Eval(5*1000);
      }
      else if(lmom > 0.5 && lmom <= 0.8){
	cmisid = fp->Eval(0.8*1000)*1.5;
      }
      else if(lmom <= 0.5){
	cmisid = fp->Eval(0.8*1000)*5;
      }
      
      // Charge flip
      if(rcnum < cmisid*1000)
	LeptonChargeFlip = true;
      
      // For the selected neutrino type skip the event if the charge is flipped 
      if(neu == neutrinoPDG && LeptonChargeFlip){continue;}
      // For anti-nu keep only the events with the charge flipped
      if(neu == -neutrinoPDG && !LeptonChargeFlip){continue;}
    }

    // Number of final state pions and protons
    int npizero = 0; int npiplus = 0; int npiminus = 0; int nprotons = 0;
    // EM activity
    int nem = 0; int ngamma = 0;
    // Other stuff
    int nother = 0;
    // Other - this refers to regions where the PID can't separate pions from protons
    int otherpar = 0;

    for(int k = 0; k < nf; k++){
      random->SetSeed(i*i + k + nf + seed);
 
      // Pt
      //double pt = sqrt(pxf_reco[k]*pxf_reco[k] + pyf_reco[k]*pyf_reco[k]);

      // Momentum
      double momentum = sqrt(pxf_reco[k]*pxf_reco[k] + pyf_reco[k]*pyf_reco[k] + pzf_reco[k]*pzf_reco[k]);

      // Charge mis-id
      bool chargeflip = false;
      double chargemisid = 0.0;
      int rnum = random->Integer(1000);
      if(momentum > 0.8 && momentum < 5){
	chargemisid = fp->Eval(momentum*1000);
      }
      else if(momentum >= 5){
	chargemisid = fp->Eval(5*1000);
      }
      else if(momentum > 0.5 && momentum <= 0.8){
	chargemisid = fp->Eval(0.8*1000)*1.5;
      }
      else if(momentum <= 0.5){
	chargemisid = fp->Eval(0.8*1000)*5;
      }

      // Charge flip
      if(rnum < chargemisid*1000)
	chargeflip = true;

      // Change the random seed
      random->SetSeed(random->GetSeed() + seed);
      rnum = random->Integer(1000);

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
	    if(chargeflip == false)// has to be positive charged
	      nprotons++;
	  }
	  else
	    npiplus++;
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
	    if(chargeflip == true)// has to be positive charged
	    nprotons++;
	  }
	  else
	    npiminus++;
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
	    if(chargeflip == true)
	      npiminus++;
	    else
	    npiplus++;
	  }
	  else{// now check the charge
	    if(chargeflip == false)
	    nprotons++;
	  }
	}
      }
      else{
	// Minimum track length cut
	//if(Trkf_reco[k] < tracklengthcut){continue;}
	// Energy cut
	if(Ef_reco[k] < 100){continue;}
	if(momentum > MaxMomentumPID)
          otherpar++;
	else
	  nother++;
      }
    } // fs particle loop

    int npionscharge = npiplus + npiminus;
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
      if(npionscharge == 0 && npizero == 0 && nprotons == 0 && otherpar == 0 && nem == 0 && ngamma == 0 && nother == 0) {continue;}
      if(npionscharge == 0 && npizero == 1 && npizerorecon == 0 && nprotons == 0 && otherpar == 0 && nem == 0 && ngamma == 0 && nother == 0) {continue;}
    }

    // True reaction modes
    int nipipm  = nipip + nipim;
    int nipipm0 = nipip + nipim + nipi0;

    if(cc){
      if(coh)
	reactionmode = 10;
      else if(mec)
	reactionmode = 11;
      else if(qel)
	reactionmode = 110;
      else if(nipipm == 1 && nipi0 == 0)
	reactionmode = 111;
      else if(nipipm == 2 && nipi0 == 0)
        reactionmode = 112;
      else if(nipipm == 0 && nipi0 == 1)
        reactionmode = 121;
      else if(nipipm == 0 && nipi0 == 2)
        reactionmode = 122;
      else if(nipipm == 1 && nipi0 == 1)
        reactionmode = 123;
      else
	reactionmode = 125;
    }
    else if(nc){
      if(coh)
        reactionmode = 20;
      else if(nipipm == 1 && nipi0 == 0)
        reactionmode = 221;
      else if(nipipm == 0 && nipi0 == 1)
        reactionmode = 221;
      else
        reactionmode = 225;
    }

    // Selection
    if(EvClass_reco == 0){ // cc-numu
      if(npionscharge == 0      && npizerorecon == 0 && nprotons == 0 && otherpar == 0 && nem == 0 && ngamma == 0 && nother == 0) sample = 10000;
      else if(npionscharge == 0 && npizerorecon == 0 && nprotons == 1 && otherpar == 0 && nem == 0 && ngamma == 0 && nother == 0) sample = 10010;
      else if(npionscharge == 1 && npizerorecon == 0) sample = 11009;
      else if(npionscharge == 2 && npizerorecon == 0) sample = 12009;
      else if(npionscharge == 0 && npizerorecon == 1) sample = 10109;
      else if(npionscharge == 1 && npizerorecon == 1) sample = 11109;
      else sample = 19999;
    }
    else if(EvClass_reco == 1){ // cc-nue
      if(npionscharge == 0      && npizerorecon == 0 && nprotons == 0 && otherpar == 0 && nem == 0 && ngamma == 0 && nother == 0) sample = 20000;
      else if(npionscharge == 0 && npizerorecon == 0 && nprotons == 1 && otherpar == 0 && nem == 0 && ngamma == 0 && nother == 0) sample = 20010;
      else if(npionscharge == 1 && npizerorecon == 0) sample = 21009;
      else if(npionscharge == 2 && npizerorecon == 0) sample = 22009;
      else if(npionscharge == 0 && npizerorecon == 1) sample = 20109;
      else if(npionscharge == 1 && npizerorecon == 1) sample = 21109;
      else sample = 29999;
    }
    else if(EvClass_reco == 2){ // nc
      if(npionscharge == 1 && npizerorecon == 0) sample = 31009;
      else if(npionscharge == 2 && npizerorecon == 0) sample = 32009;
      else if(npionscharge == 0 && npizerorecon == 1) sample = 30109;
      else if(npionscharge == 1 && npizerorecon == 1) sample = 31109;
      else sample = 39999;
    }

    // Fill the tree
    FastMCTree->Fill();
  }

  return FastMCTree;
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
