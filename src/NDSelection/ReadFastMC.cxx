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
#include "TGraphAsymmErrors.h"
#include "TXMLEngine.h"

#include "Conventions/Opt.h"
#include "Messenger/Messenger.h"

using namespace valor;
using namespace valor::util;
using namespace valor::conv;

ClassImp(ReadFastMC)

ReadFastMC::ReadFastMC()
{
  min = 0;
  max = 50;
  bin = 150;

  npionnum = 2;

}

ReadFastMC::~ReadFastMC(){
  //File->Delete();
}
// ----------------------------------------------------------------------------
void ReadFastMC::ReadDatacard(string datacard){

  LOG("ReadFastMC",pNOTICE) << "Reading configuration from file [" << datacard << "]";

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
      if(line.find("ReconEfficiency") != string::npos){ // recon efficiency
        size_t found = line.find(" ");
        string par = line.substr(found);
        par.erase(par.begin());
        ReconEfficiency = atof(par.c_str());
      }
      if(line.find("EVisibleCut") != string::npos){ // Visible neutrino energy cut
        size_t found = line.find(" ");
        string par = line.substr(found);
        par.erase(par.begin());
        EVisibleCut = atof(par.c_str());
      }
      if(line.find("EReconCut") != string::npos){ // Neutrino enrgy cut for nue-cc events
        size_t found = line.find(" ");
        string par = line.substr(found);
        par.erase(par.begin());
        EReconCut = atof(par.c_str());
      }
    }
  }
  empFile.close();

  if(verbose > 0){
    LOG("ReadFastMC",pNOTICE) << "Input File = "                             <<  inFile;
    LOG("ReadFastMC",pNOTICE) << "Number of events to run = "                <<  nevents;
    LOG("ReadFastMC",pNOTICE) << "FHC or RHC = "                             <<  neutrinoPDG;
    LOG("ReadFastMC",pNOTICE) << "Neutrino energy cut = "                    <<  enureconcut;
    LOG("ReadFastMC",pNOTICE) << "Pion energy cut = "                        <<  epionreconcut;
    LOG("ReadFastMC",pNOTICE) << "Kaon energy cut = "                        <<  ekaonreconcut;
    LOG("ReadFastMC",pNOTICE) << "Proton energy cut = "                      <<  eprotonreconcut;
    LOG("ReadFastMC",pNOTICE) << "Gamma energy cut = "                       <<  egammareconcut;
    LOG("ReadFastMC",pNOTICE) << "Electron energy cut = "                    <<  eelectronreconcut;
    LOG("ReadFastMC",pNOTICE) << "Pi0 invariant mass cut = "                 <<  pi0invmass;
    LOG("ReadFastMC",pNOTICE) << "Pion mis-id probability as a proton = "    <<  PionMisIDAsProton;
    LOG("ReadFastMC",pNOTICE) << "Pion mis-id probability as a kaon = "      <<  PionMisIDAsKaon;
    LOG("ReadFastMC",pNOTICE) << "Proton mis-id probability as a pion = "    <<  ProtonMisIDAsPion;
    LOG("ReadFastMC",pNOTICE) << "Proton mis-id probability as a kaon = "    <<  ProtonMisIDAsKaon;
    LOG("ReadFastMC",pNOTICE) << "Kaon mis-id probability as a pion = "      <<  KaonMisIDAsPion;
    LOG("ReadFastMC",pNOTICE) << "Kaon mis-id probability as a proton = "    <<  KaonMisIDAsProton;
    LOG("ReadFastMC",pNOTICE) << "Charge confusion momentum slope = "        <<  ChargeConfMomSlope;
    LOG("ReadFastMC",pNOTICE) << "Charge confusion momentum constant = "     <<  ChargeConfMomConst;
    LOG("ReadFastMC",pNOTICE) << "Charge confusion track length slope = "    <<  ChargeConfTrLSlope;
    LOG("ReadFastMC",pNOTICE) << "Charge confusion track length constant = " <<  ChargeConfTrLConst;
    LOG("ReadFastMC",pNOTICE) << "Maximum momentum to apply the PID = "      <<  MaxMomentumPID;
    LOG("ReadFastMC",pNOTICE) << "Track length cut = "                       <<  tracklengthcut;
    LOG("ReadFastMC",pNOTICE) << "Visible neutrino energy cut = "            <<  EVisibleCut;
    LOG("ReadFastMC",pNOTICE) << "Reconstructed neutrino energy cut = "      <<  EReconCut;
    LOG("ReadFastMC",pNOTICE) << "Reconstructed efficiency cut = "           <<  ReconEfficiency;
  }
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

  LOG("ReadFastMC",pNOTICE) << "Reading configuration from XML file [" << datacard << "]";

  TXMLEngine* xml = new TXMLEngine; 
  XMLDocPointer_t xmldoc = xml->ParseFile(datacard.c_str());
  if (xmldoc==0) {
    cerr << "Exp >> " << "Can not parse input: " << datacard << endl;
    delete xml;
    return;  
  }
  XMLNodePointer_t root_node = xml->DocGetRootElement(xmldoc);
 
  inFile             = util::XML2String(xml,root_node,"DetConfig/InFile");
  nevents            = util::XML2Dbl(xml,root_node,"DetConfig/Events");
  neutrinoPDG        = util::XML2Dbl(xml,root_node,"DetConfig/NeutrinoPDG");

  enureconcut        = util::XML2Dbl(xml,root_node,"DetConfig/ReconNeutrinoEnergyCut");
  epionreconcut      = util::XML2Dbl(xml,root_node,"DetConfig/ReconPiPMEnergyCut");
  ekaonreconcut      = util::XML2Dbl(xml,root_node,"DetConfig/ReconKaonPMEnergyCut");
  eprotonreconcut    = util::XML2Dbl(xml,root_node,"DetConfig/ReconProtonEnergyCut");
  egammareconcut     = util::XML2Dbl(xml,root_node,"DetConfig/ReconGammaEnergyCut");
  eelectronreconcut  = util::XML2Dbl(xml,root_node,"DetConfig/ReconElectronEnergyCut");
  pi0invmass         = util::XML2Dbl(xml,root_node,"DetConfig/Pi0InvariantMassCut");

  PionMisIDAsProton  = util::XML2Dbl(xml,root_node,"DetConfig/PionMisIDAsProton");
  PionMisIDAsKaon    = util::XML2Dbl(xml,root_node,"DetConfig/PionMisIDAsKaon");
  ProtonMisIDAsPion  = util::XML2Dbl(xml,root_node,"DetConfig/ProtonMisIDAsPion");
  ProtonMisIDAsKaon  = util::XML2Dbl(xml,root_node,"DetConfig/ProtonMisIDAsKaon");
  KaonMisIDAsPion    = util::XML2Dbl(xml,root_node,"DetConfig/KaonMisIDAsPion");
  KaonMisIDAsProton  = util::XML2Dbl(xml,root_node,"DetConfig/KaonMisIDAsProton");

  ChargeConfMomSlope = util::XML2Dbl(xml,root_node,"DetConfig/ChargeConfMomSlope");
  ChargeConfMomConst = util::XML2Dbl(xml,root_node,"DetConfig/ChargeConfMomConst");
  ChargeConfTrLSlope = util::XML2Dbl(xml,root_node,"DetConfig/ChargeConfTrLSlope");
  ChargeConfTrLConst = util::XML2Dbl(xml,root_node,"DetConfig/ChargeConfTrLConst");

  MaxMomentumPID     = util::XML2Dbl(xml,root_node,"DetConfig/MaxMomentumPID");
  tracklengthcut     = util::XML2Dbl(xml,root_node,"DetConfig/TrackLengthCut");
  EVisibleCut        = util::XML2Dbl(xml,root_node,"DetConfig/EVisibleCut");
  EReconCut          = util::XML2Dbl(xml,root_node,"DetConfig/EReconCut");

  ReconEfficiency    = util::XML2Dbl(xml,root_node,"DetConfig/ReconEfficiency");

  verbose            = util::XML2Dbl(xml,root_node,"DetConfig/Verbose");

  if(verbose > 0){
    LOG("ReadFastMC",pNOTICE) << "Input File = "                             <<  inFile;
    LOG("ReadFastMC",pNOTICE) << "Number of events to run = "                <<  nevents;
    LOG("ReadFastMC",pNOTICE) << "FHC or RHC = "                             <<  neutrinoPDG;
    LOG("ReadFastMC",pNOTICE) << "Neutrino energy cut = "                    <<  enureconcut;
    LOG("ReadFastMC",pNOTICE) << "Pion energy cut = "                        <<  epionreconcut;
    LOG("ReadFastMC",pNOTICE) << "Kaon energy cut = "                        <<  ekaonreconcut;
    LOG("ReadFastMC",pNOTICE) << "Proton energy cut = "                      <<  eprotonreconcut;
    LOG("ReadFastMC",pNOTICE) << "Gamma energy cut = "                       <<  egammareconcut;
    LOG("ReadFastMC",pNOTICE) << "Electron energy cut = "                    <<  eelectronreconcut;
    LOG("ReadFastMC",pNOTICE) << "Pi0 invariant mass cut = "                 <<  pi0invmass;
    LOG("ReadFastMC",pNOTICE) << "Pion mis-id probability as a proton = "    <<  PionMisIDAsProton;
    LOG("ReadFastMC",pNOTICE) << "Pion mis-id probability as a kaon = "      <<  PionMisIDAsKaon;
    LOG("ReadFastMC",pNOTICE) << "Proton mis-id probability as a pion = "    <<  ProtonMisIDAsPion;
    LOG("ReadFastMC",pNOTICE) << "Proton mis-id probability as a kaon = "    <<  ProtonMisIDAsKaon;
    LOG("ReadFastMC",pNOTICE) << "Kaon mis-id probability as a pion = "      <<  KaonMisIDAsPion;
    LOG("ReadFastMC",pNOTICE) << "Kaon mis-id probability as a proton = "    <<  KaonMisIDAsProton;
    LOG("ReadFastMC",pNOTICE) << "Charge confusion momentum slope = "        <<  ChargeConfMomSlope;
    LOG("ReadFastMC",pNOTICE) << "Charge confusion momentum constant = "     <<  ChargeConfMomConst;
    LOG("ReadFastMC",pNOTICE) << "Charge confusion track length slope = "    <<  ChargeConfTrLSlope;
    LOG("ReadFastMC",pNOTICE) << "Charge confusion track length constant = " <<  ChargeConfTrLConst;
    LOG("ReadFastMC",pNOTICE) << "Maximum momentum to apply the PID = "      <<  MaxMomentumPID;
    LOG("ReadFastMC",pNOTICE) << "Track length cut = "                       <<  tracklengthcut;
    LOG("ReadFastMC",pNOTICE) << "Visible neutrino energy cut = "            <<  EVisibleCut;
    LOG("ReadFastMC",pNOTICE) << "Reconstructed neutrino energy cut = "      <<  EReconCut;
    LOG("ReadFastMC",pNOTICE) << "Reconstructed efficiency cut = "           <<  ReconEfficiency;
  }

  // Release memory
  xml->FreeDoc(xmldoc);
  delete xml;
}
// ----------------------------------------------------------------------------
double ReadFastMC::FluxWeight(){

  double nusel  = 1.0;
  double anusel = 1.0;

  double ratio = 1.0;

  // POT normalization
  double potnorm = (double)1.0/nevents;
  // FHC number of interactions / POT / kt in near detector
  const double fhcnumucc  = 2.20470814946438192e-12;
  const double fhcnumunc  = 7.44097783570827432e-13;
  const double fhcanumucc = 2.40172755208848353e-13;
  const double fhcanumunc = 9.94691414573208180e-14;
  const double fhcnuecc   = 3.93836306563397024e-14;
  const double fhcnuenc   = 1.28277349032322958e-14;
  const double fhcanuecc  = 8.90001130526597293e-15;
  const double fhcanuenc  = 3.56767548734831866e-15;
  // RHC number of interactions / POT / kt in near detector
  const double rhcnumucc  = 7.13519775915776830e-13;
  const double rhcnumunc  = 2.32947135468662667e-13;
  const double rhcanumucc = 7.25899675039850760e-13;
  const double rhcanumunc = 3.23041943142292877e-13;
  const double rhcnuecc   = 2.47793150219174462e-14;
  const double rhcnuenc   = 7.95950835278876701e-15;
  const double rhcanuecc  = 1.30149006424548413e-14;
  const double rhcanuenc  = 5.38102770838081824e-15;

  double fhcnumuweight  = (fhcnumucc  + fhcnumunc )*potnorm;
  double fhcanumuweight = (fhcanumucc + fhcanumunc)*potnorm;
  double rhcnumuweight  = (rhcnumucc  + rhcnumunc )*potnorm;
  double rhcanumuweight = (rhcanumucc + rhcanumunc)*potnorm;
  double fhcnueweight   = (fhcnuecc   + fhcnuenc  )*potnorm;
  double fhcanueweight  = (fhcanuecc  + fhcanuenc )*potnorm;
  double rhcnueweight   = (rhcnuecc   + rhcnuenc  )*potnorm;
  double rhcanueweight  = (rhcanuecc  + rhcanuenc )*potnorm;

  TTree *gstTree = ReadTree(inFile);

  // Need to loop over the events
  for(int i = 0; i < gstTree->GetEntries(); i++){
    gstTree->GetEntry(i);

    if(neutrinoPDG == 14 || neutrinoPDG == 12){
      if(neu == 14)
	nusel = fhcnumuweight;
      else if(neu == -14)
	anusel = fhcanumuweight;
      else if(neu == 12)
	anusel = fhcnueweight;
      else if(neu == -12)
	anusel = fhcanueweight;

      // Temporary
      if(nusel != 1.0 && anusel != 1.0){
	ratio = anusel/nusel;
      break;
      }
    }
    else if(neutrinoPDG == -14 || neutrinoPDG == -12){
      if(neu == 14)
	nusel = rhcnumuweight;
      else if(neu == -14)
	anusel = rhcanumuweight;
      else if(neu == 12)
	anusel = rhcnueweight;
      else if(neu == -12)
	anusel = rhcanueweight;

      // Temporary
      if(nusel != 1.0 && anusel != 1.0){
	ratio = nusel/anusel;
      break;
      }
    }
  }

  gstTree->Delete();

  return ratio;

}
// ----------------------------------------------------------------------------
TTree* ReadFastMC::FastMCTree(int seed, bool debugtree){

  // FastMC Tree
  TTree *gstTree = ReadTree(inFile);
  // Number of events to select
  int numuevents = 0; int anumuevents = 0;
  // Output tree
  TTree *FastMCTree = new TTree("FastMCTree","FastMC Output Tree");
  // Event sample
  int sample = -1;
  // True reaction mode
  int reactionmode = -1;
  // Number of misidentified pions as protons
  int NPionMisIDAsProton = 0;
  // Number of misidentified pions as kaons
  int NPionMisIDAsKaon = 0;
  // Number of misidentified protons as pions
  int NProtonMisIDAsPion = 0;
  // Number of misidentified protons as kaons
  int NProtonMisIDAsKaon = 0;
  // Number of misidentified kaons as protons
  int NKaonMisIDAsProton = 0;
  // Number of misidentified kaons as pions
  int NKaonMisIDAsPion = 0;
  // Charge flip for selected lepton
  bool LeptonChargeFlip = false;
  // Energy of the electron selected as nc
  double Electronenergy = -1.0;
  // Number of nc events with only photons reconstructed
  int NPhotonNC = -1;

  // Tree branches
  FastMCTree->Branch("Ev",          &Ev,          "Ev/D");
  FastMCTree->Branch("Ev_reco",     &Ev_reco,     "Ev_reco/D");
  FastMCTree->Branch("y_reco",      &y_reco,      "y_reco/D");
  FastMCTree->Branch("POTWeight",   &POTWeight,   "POTWeight/D");
  FastMCTree->Branch("sample",      &sample,      "sample/I");
  FastMCTree->Branch("reactionmode",&reactionmode,"reactionmode/I");

  if(debugtree){
    FastMCTree->Branch("neu",                 &neu,                 "neu/I");
    FastMCTree->Branch("neut_code",           &neut_code,           "neut_code/I");
    FastMCTree->Branch("ys",                  &ys,                  "ys/D");
    FastMCTree->Branch("Q2",                  &Q2,                  "Q2/D");
    FastMCTree->Branch("Q2_reco",             &Q2_reco,             "Q2_reco/D");
    FastMCTree->Branch("NPionMisIDAsProton",  &NPionMisIDAsProton,  "NPionMisIDAsProton/I");
    FastMCTree->Branch("NPionMisIDAsKaon",    &NPionMisIDAsKaon,    "NPionMisIDAsKaon/I");
    FastMCTree->Branch("NProtonMisIDAsPion",  &NProtonMisIDAsPion,  "NProtonMisIDAsPion/I");
    FastMCTree->Branch("NProtonMisIDAsKaon",  &NProtonMisIDAsKaon,  "NProtonMisIDAsKaon/I");
    FastMCTree->Branch("NKaonMisIDAsProton",  &NKaonMisIDAsProton,  "NKaonMisIDAsProton/I");
    FastMCTree->Branch("NKaonMisIDAsPion",    &NKaonMisIDAsPion,    "NKaonMisIDAsPion/I");
    FastMCTree->Branch("LeptonChargeFlip",    &LeptonChargeFlip,    "LeptonChargeFlip/O");
    FastMCTree->Branch("Electronenergy",      &Electronenergy,      "Electronenergy/D");
    FastMCTree->Branch("NPhotonNC",           &NPhotonNC,           "NPhotonNC/I");
  }

  //const double pionmass   = 0.13957;
  const double pizeromass = 0.13498;

  // Random generator
  TRandom3 *rand = new TRandom3();

  // POT normalization
  double potnorm = (double)1.0/nevents;
  // FHC number of interactions / POT / kt in near detector
  const double fhcnumucc  = 2.20470814946438192e-12;
  const double fhcnumunc  = 7.44097783570827432e-13;
  const double fhcanumucc = 2.40172755208848353e-13;
  const double fhcanumunc = 9.94691414573208180e-14;
  const double fhcnuecc   = 3.93836306563397024e-14;
  const double fhcnuenc   = 1.28277349032322958e-14;
  const double fhcanuecc  = 8.90001130526597293e-15;
  const double fhcanuenc  = 3.56767548734831866e-15;
  // RHC number of interactions / POT / kt in near detector
  const double rhcnumucc  = 7.13519775915776830e-13;
  const double rhcnumunc  = 2.32947135468662667e-13;
  const double rhcanumucc = 7.25899675039850760e-13;
  const double rhcanumunc = 3.23041943142292877e-13;
  const double rhcnuecc   = 2.47793150219174462e-14;
  const double rhcnuenc   = 7.95950835278876701e-15;
  const double rhcanuecc  = 1.30149006424548413e-14;
  const double rhcanuenc  = 5.38102770838081824e-15;

  double fhcnumuweight  = (fhcnumucc  + fhcnumunc )*potnorm;
  double fhcanumuweight = (fhcanumucc + fhcanumunc)*potnorm;
  double rhcnumuweight  = (rhcnumucc  + rhcnumunc )*potnorm;
  double rhcanumuweight = (rhcanumucc + rhcanumunc)*potnorm;
  double fhcnueweight   = (fhcnuecc   + fhcnuenc  )*potnorm;
  double fhcanueweight  = (fhcanuecc  + fhcanuenc )*potnorm;
  double rhcnueweight   = (rhcnuecc   + rhcnuenc  )*potnorm;
  double rhcanueweight  = (rhcanuecc  + rhcanuenc )*potnorm;

  FastMCTree->SetDirectory(0);
  for(int i = 0; i < gstTree->GetEntries(); i++){
    gstTree->GetEntry(i);

    // Initialize
    NPionMisIDAsProton = 0;
    NPionMisIDAsKaon   = 0;
    NProtonMisIDAsPion = 0;
    NProtonMisIDAsKaon = 0;
    NKaonMisIDAsProton = 0;
    NKaonMisIDAsPion   = 0;
    LeptonChargeFlip   = false;
    NPhotonNC          = -1;
    Electronenergy     = -1.0;

    // For undefined events
    bool undefined = false;

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
    if(neutrinoPDG == 14 || neutrinoPDG == 12){
      if(neu == 14)
	POTWeight = fhcnumuweight;
      else if(neu == -14)
	POTWeight = fhcanumuweight;
      else if(neu == 12)
	POTWeight = fhcnueweight;
      else if(neu == -12)
	POTWeight = fhcanueweight;
    }
    else if(neutrinoPDG == -14 || neutrinoPDG == -12){
      if(neu == 14)
	POTWeight = rhcnumuweight;
      else if(neu == -14)
	POTWeight = rhcanumuweight;
      else if(neu == 12)
	POTWeight = rhcnueweight;
      else if(neu == -12)
	POTWeight = rhcanueweight;
    }

    // True reaction modes
    int nipipm  = nipip + nipim;
    int nipipm0 = nipip + nipim + nipi0;

    // Start the selection
    // No recon neutrino energy?
    if(Ev_reco < enureconcut){undefined = true;}

    // Apply the charge flip cut only for CC selection
    if(EvClass_reco < 2){
      newseed = seed*seed + i;
      // Is reconstructed?
      //bool recontrack = IsReconTrack(newseed*newseed);

      double lmom = sqrt(pxL_reco*pxL_reco + pyL_reco*pyL_reco + pzL_reco*pzL_reco);
      
      LeptonChargeFlip = ChargeFlip(newseed, lmom);

      // For the selected neutrino type skip the event if the charge is flipped
      if(neutrinoPDG == 14 || neutrinoPDG == 12){
	if(neu > 0 && LeptonChargeFlip){undefined = true;}
	// For anti-nu keep only the events with the charge flipped
	if(neu < 0 && !LeptonChargeFlip){undefined = true;}
      }
      else if(neutrinoPDG == -14 || neutrinoPDG == -12){
	if(neu < 0 && LeptonChargeFlip){undefined = true;}
	// For anti-nu keep only the events with the charge flipped
	if(neu > 0 && !LeptonChargeFlip){undefined = true;}
      }
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

      // Is reconstructed?
      //bool recontrack = IsReconTrack(newseed*newseed);

      // Pt
      //double pt = sqrt(pxf_reco[k]*pxf_reco[k] + pyf_reco[k]*pyf_reco[k]);

      // Has to be different from the reconstucted lepton - otherwise double counting
      if(Trkf_reco[k] == TrkL_reco){continue;}

      // Momentum
      double momentum = sqrt(pxf_reco[k]*pxf_reco[k] + pyf_reco[k]*pyf_reco[k] + pzf_reco[k]*pzf_reco[k]);
      // No momentum? - skip
      //if(momentum == 0){continue;}

      // Charge mis-id
      bool chargeflip = ChargeFlip(newseed, momentum);

      rand->SetSeed(newseed + k + nf + i + seed);
      int rnum = rand->Integer(1000);

      if(pdgf[k] == 22){  // photons
	if(Ef_reco[k] < egammareconcut){continue;}
	//ngamma++;
      }
      else if(abs(pdgf[k]) == 11){ // e-/e+
	// Minimum track length cut
	if(Trkf_reco[k] < tracklengthcut){continue;}
	// Energy cut
	if(Ef_reco[k] < eelectronreconcut){continue;}
	//nem++;
      }
      else if(pdgf[k] == 211 || pdgf[k] == 13){ // pi+, muons and pions are not separatable
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
	    NPionMisIDAsKaon++;
	    if(!chargeflip)
	      nkaonplus++;
	    else
	      nkaonminus++;
	  }  
	  else{
	    if(chargeflip)
	      npiminus++;
	    else
	      npiplus++;
	  }
	}
      }
      else if(pdgf[k] == -211 || pdgf[k] == -13){ // pi-, muons and pions are not separatable
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
	    NPionMisIDAsKaon++;
            if(chargeflip)
	      nkaonplus++;
	    else
	      nkaonminus++;
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
	    NProtonMisIDAsKaon++;
            if(!chargeflip)
	      nkaonplus++;
	    else
	      nkaonminus++;
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
	    NKaonMisIDAsPion++;
	    if(chargeflip)
              npiminus++;
            else
              npiplus++;
	  }
	  else if(rnum > KaonMisIDAsPion*1000 && rnum < (KaonMisIDAsPion+KaonMisIDAsProton)*1000){ // mis-id as proton
	    NKaonMisIDAsProton++;
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
	    NKaonMisIDAsPion++;
            if(!chargeflip)
              npiminus++;
            else
              npiplus++;
          }
          else if(rnum > KaonMisIDAsPion*1000 && rnum < (KaonMisIDAsPion+KaonMisIDAsProton)*1000){ // mis-id as proton
	    NKaonMisIDAsProton++;
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
        if(Ef_reco[k] < 0.25){continue;}

	nneutrons++;
      }
      else{
	// Minimum track length cut
	//if(Trkf_reco[k] < tracklengthcut){continue;}
	// Energy cut
	if(Ef_reco[k] < 0.25){continue;}
	nother++;
      }
    } // fs particle loop

    int npionscharge = npiplus + npiminus;
    int nkaons = nkaonplus + nkaonminus;
    int npizerorecon = 0;

    // Check events with multiple EM objects
    int nEMf_recon = 0; int pos[50] = {-1};
    // First check for photons
    for(int k = 0; k < nEMf; k++){
      if(EMpdgf[k] == 22){
	// Energy cut
	if(EMEf_reco[k]  < egammareconcut){continue;}
	pos[nEMf_recon] = k;
	nEMf_recon++;
      }
    }
 
    // Only for single pi0 events
    if(nEMf_recon == 2){
      int pos1 = pos[0]; int pos2 = pos[1];
 
      double par = sqrt(EMpxf_reco[pos1]*EMpxf_reco[pos1] + EMpyf_reco[pos1]*EMpyf_reco[pos1] + EMpzf_reco[pos1]*EMpzf_reco[pos1]);
      double pbr = sqrt(EMpxf_reco[pos2]*EMpxf_reco[pos2] + EMpyf_reco[pos2]*EMpyf_reco[pos2] + EMpzf_reco[pos2]*EMpzf_reco[pos2]);
      
      double aDOTbr = EMpxf_reco[pos1]*EMpxf_reco[pos2] + EMpyf_reco[pos1]*EMpyf_reco[pos2] + EMpzf_reco[pos1]*EMpzf_reco[pos2];
      double costhr = aDOTbr / (par * pbr);
      double imr = sqrt(2.0 *EMEf_reco[pos1]  *EMEf_reco[pos2]  * ( 1.0 - costhr));
      
      // Invariant mass cut
      if(fabs(imr - pizeromass) < pi0invmass)
	npizerorecon++;
    }
    
    if(nEMf_recon == 3){
      double pizerodiff = -1e20;
      for(int j = 0; j < nEMf_recon-1; j++){
	for(int k = 1; k < nEMf_recon; k++){
	  if(k == j){continue;}
	  int pos1 = pos[j]; int pos2 = pos[k];
	  
	  double par = sqrt(EMpxf_reco[pos1]*EMpxf_reco[pos1] + EMpyf_reco[pos1]*EMpyf_reco[pos1] + EMpzf_reco[pos1]*EMpzf_reco[pos1]);
	  double pbr = sqrt(EMpxf_reco[pos2]*EMpxf_reco[pos2] + EMpyf_reco[pos2]*EMpyf_reco[pos2] + EMpzf_reco[pos2]*EMpzf_reco[pos2]);
	  
	  double aDOTbr = EMpxf_reco[pos1]*EMpxf_reco[pos2] + EMpyf_reco[pos1]*EMpyf_reco[pos2] + EMpzf_reco[pos1]*EMpzf_reco[pos2];
	  double costhr = aDOTbr / (par * pbr);
	  double imr = sqrt(2.0 *EMEf_reco[pos1]  *EMEf_reco[pos2]  * ( 1.0 - costhr));
	  
	  double diff = fabs(imr - pizeromass);
	  if(pizerodiff < diff)
	    pizerodiff = diff;
	}
      }

      if(pizerodiff < pi0invmass){
	npizerorecon++;
	// We are also left with an extra gamma
	ngamma++;
      }
    }
    
    // EM objects when no pizero reconstructed
    int elecpos = -1; double energeticelectron = 0.0;
    if(npizerorecon == 0){
      for(int k = 0; k < nEMf; k++){
	if(EMpdgf[k] == 22){
	  // Energy cut
	  if(EMEf_reco[k]  < egammareconcut){continue;}
	  ngamma++;
	}
      }
    }

    // Check for electrons
    for(int k = 0; k < nEMf; k++){
      if(EMpdgf[k] == 11 || EMpdgf[k] == -11){
	// Minimum track length cut
	if(EMTrkf_reco[k] < tracklengthcut){continue;}
	// Energy cut
	if(EMEf_reco[k] < eelectronreconcut){continue;}
	nem++;
	if(EMEf_reco[k] > energeticelectron){
	  energeticelectron = EMEf_reco[k];
	  elecpos = k;
	}
      }
    }

    // All recon tracks
    int ntotal = npiplus+npiminus+nprotons+nkaonplus+nkaonminus+nem+ngamma+nother+otherpar+npizerorecon;
    // Other EM activity
    //int otherem = nem+ngamma;

    if(neu == 14){
      if(cc){
	if(qel)
	  reactionmode = 0;
	else if(mec)
	  reactionmode = 1;
	else if(coh)
	  reactionmode = 7; // odd
	else if(nipipm == 1 && nipi0 == 0)
	  reactionmode = 2;
	else if(nipipm == 0 && nipi0 == 1)
	  reactionmode = 3;
	else if(nipipm == 2 && nipi0 == 0)
	  reactionmode = 4;
	else if(nipipm == 0 && nipi0 == 2)
	  reactionmode = 5;
	else if(nipipm == 1 && nipi0 == 1)
	  reactionmode = 6;
	else
	  reactionmode = 8;
      }
      else if(nc){
	if(coh)
	  reactionmode = 11; // odd
	else if(nipipm == 1 && nipi0 == 0)
	  reactionmode = 9;
	else if(nipipm == 0 && nipi0 == 1)
	  reactionmode = 10;
	else
	  reactionmode = 12;
      }
      else{
	LOG("ReadFastMC",pNOTICE) << "Event which is not CC or NC: " << i;
      }
    }
    else if(neu == -14){
      if(cc){
	if(qel)
	  reactionmode = 13;
	else if(mec)
	  reactionmode = 14;
	else if(coh)
	  reactionmode = 20; // odd
	else if(nipipm == 1 && nipi0 == 0)
	  reactionmode = 15;
	else if(nipipm == 0 && nipi0 == 1)
	  reactionmode = 16;
	else if(nipipm == 2 && nipi0 == 0)
	  reactionmode = 17;
	else if(nipipm == 0 && nipi0 == 2)
	  reactionmode = 18;
	else if(nipipm == 1 && nipi0 == 1)
	  reactionmode = 19;
	else
	  reactionmode = 21;
      }
      else if(nc){
	if(coh)
	  reactionmode = 24; // odd
	else if(nipipm == 1 && nipi0 == 0)
	  reactionmode = 22;
	else if(nipipm == 0 && nipi0 == 1)
	  reactionmode = 23;
	else
	  reactionmode = 25;
      }
      else{
	LOG("ReadFastMC",pNOTICE) << "Event which is not CC or NC: " << i;
      }
    }
    else if(neu == 12){
      if(cc){
	if(qel)
	  reactionmode = 26;
	else if(mec)
	  reactionmode = 27;
	else if(coh)
	  reactionmode = 33; // odd
	else if(nipipm == 1 && nipi0 == 0)
	  reactionmode = 28;
	else if(nipipm == 0 && nipi0 == 1)
	  reactionmode = 29;
	else if(nipipm == 2 && nipi0 == 0)
	  reactionmode = 30;
	else if(nipipm == 0 && nipi0 == 2)
	  reactionmode = 31;
	else if(nipipm == 1 && nipi0 == 1)
	  reactionmode = 32;
	else
	  reactionmode = 34;
      }
      else if(nc){
	if(coh)
	  reactionmode = 37; // odd
	else if(nipipm == 1 && nipi0 == 0)
	  reactionmode = 35;
	else if(nipipm == 0 && nipi0 == 1)
	  reactionmode = 36;
	else
	  reactionmode = 38;
      }
      else{
	LOG("ReadFastMC",pNOTICE) << "Event which is not CC or NC: " << i;
      }
    }
    else if(neu == -12){
      if(cc){
	if(qel)
	  reactionmode = 39;
	else if(mec)
	  reactionmode = 40;
	else if(coh)
	  reactionmode = 46; // odd
	else if(nipipm == 1 && nipi0 == 0)
	  reactionmode = 41;
	else if(nipipm == 0 && nipi0 == 1)
	  reactionmode = 42;
	else if(nipipm == 2 && nipi0 == 0)
	  reactionmode = 43;
	else if(nipipm == 0 && nipi0 == 2)
	  reactionmode = 44;
	else if(nipipm == 1 && nipi0 == 1)
	  reactionmode = 45;
	else
	  reactionmode = 47;
      }
      else if(nc){
	if(coh)
	  reactionmode = 50; // odd
	else if(nipipm == 1 && nipi0 == 0)
	  reactionmode = 48;
	else if(nipipm == 0 && nipi0 == 1)
	  reactionmode = 49;
	else
	  reactionmode = 51;
      }
      else{
	LOG("ReadFastMC",pNOTICE) << "Event which is not CC or NC: " << i;
      }
    }
    else{
	LOG("ReadFastMC",pNOTICE) << "Unknown neutrino species: " << neu;
    }

    // If the only recon particle we have from a nc is an electron, downgrade the event to cc-nue
    if(EvClass_reco == 2){
      if(npionscharge == 0 && npizerorecon == 0 && otherpar == 0 && nprotons == 0 && nkaons == 0 && nother == 0 && nem > 0 /*&& TrkL_reco < tracklengthcut*/){
	EvClass_reco = 1;
	y_reco = 1 - EMEf_reco[elecpos]/Ev_reco;
	Electronenergy = EMEf_reco[elecpos];
	bool chargeflip = ChargeFlip(newseed*newseed+elecpos, Electronenergy);
	if(neutrinoPDG == 14 || neutrinoPDG == 12){
	  if(EMpdgf[elecpos] == 11 && chargeflip){undefined = true;}
	  // For anti-nu keep only the events with the charge flipped
	  if(EMpdgf[elecpos] == -11 && !chargeflip){undefined = true;}
	}
	else if(neutrinoPDG == -14 || neutrinoPDG == -12){
	  if(EMpdgf[elecpos] == -11 && chargeflip){undefined = true;}
	  // For anti-nu keep only the events with the charge flipped
	  if(EMpdgf[elecpos] == 11 && !chargeflip){undefined = true;}
	}
      }
    }
    
    // Select opposite sign numu  
    if(undefined){
      if(EvClass_reco == 0 && Ev_reco > EReconCut)
	sample = 9;
      else{
	if(debugtree)
	  sample = -1;
	else // do not save the event
	  continue;
      }
    }
    else{
      // Selection
      if(EvClass_reco == 0){ // cc-numu
	if(Ev_reco > EReconCut){
	  if(npionscharge == 0      && npizerorecon == 0 && nprotons == 0 && otherpar == 0 && nem == 0 && ngamma == 0 && nkaons == 0 && nother == 0) sample = 1;
	  else if(npionscharge == 0 && npizerorecon == 0 && nprotons == 1 && otherpar == 0 && nem == 0 && ngamma == 0 && nkaons == 0 && nother == 0) sample = 2;
	  else if(npionscharge == 1 && npizerorecon == 0 && otherpar == 0 && nem == 0 && ngamma == 0) sample = 3;
	  else if(npionscharge == 2 && npizerorecon == 0 && otherpar == 0 && nem == 0 && ngamma == 0) sample = 4;
	  else if(npionscharge == 0 && npizerorecon == 1 && otherpar == 0 && nem == 0 && ngamma == 0) sample = 5;
	  else if(npionscharge == 1 && npizerorecon == 1 && otherpar == 0 && nem == 0 && ngamma == 0) sample = 6;
	  else sample = 7; 
	}
	else{
	  if(debugtree)
            sample = -1;
          else // do not save the event
            continue;
	}
      }// cc-numu
      else if(EvClass_reco == 1){ // cc-nue
	if(Ev_reco > EReconCut)
	  sample = 8;
	else{
	  if(debugtree)
            sample = -1;
          else // do not save the event
            continue;
	}
      } // cc-nue
      else if(EvClass_reco == 2){ // nc
	// If the muon is reconstructed, but not selected in the CC selection, count it as an extra pion: - no muon-pion separation at the moment
	if(TrkL_reco > tracklengthcut){
	  npionscharge++;
	  ntotal++;
	}
	if(ntotal > 0){ 
	  if(npionscharge == 1 && npizerorecon == 0 && otherpar == 0 && nem == 0 && ngamma == 0){
	    if(Ev_reco < EVisibleCut)
	      sample = 11;
	    else{
	      if(debugtree)
		sample = -1;
	      else // do not save the event
		continue;
	    }
	  }
	  else if(npionscharge == 0 && npizerorecon == 1 && otherpar == 0 && nem == 0 && ngamma == 0){
	    if(Ev_reco < EVisibleCut)
	      sample = 12;
	    else{
	      if(debugtree)
		sample = -1;
	      else // do not save the event
		continue;
	    }
	  }
	  else if(npionscharge == 0 && npizerorecon == 0 && otherpar == 0 && nprotons == 0 && nkaons == 0 && nother == 0 && nem == 0 && ngamma > 0){ // events with only one gamma in the fs -> do not select
	    NPhotonNC = ngamma;
	    // No sample here
	    if(debugtree)
	      sample = -1;
	    else // do not save the event
	      continue;
	  }
	  else sample = 13;
	} // ntotal 
	else{
	  if(debugtree)
	    sample = -1;
	  else // do not save the event
	    continue;
	}
      }// nc
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
TObjArray* ReadFastMC::StoreHistograms(){

  // The histogram array
  TObjArray* histarray = new TObjArray();
  // Histograms
  TH1D* MuonMomentumCC       = new TH1D("MuonMomentumCC"    ,"",100,min,10);
  TH1D* PionMomentumCC       = new TH1D("PionMomentumCC"    ,"",100,min,10);
  TH1D* ProtonMomentumCC     = new TH1D("ProtonMomentumCC"  ,"",100,min,10);
  TH1D* ElectronMomentumCC   = new TH1D("ElectronMomentumCC","",100,min,10);
  TH1D* OtherMomentumCC      = new TH1D("OtherMomentumCC"   ,"",100,min,10);

  TH1D* MuonMomentum         = new TH1D("MuonMomentum"    ,"",50,min,3);
  TH1D* PionMomentum         = new TH1D("PionMomentum"    ,"",50,min,3);
  TH1D* ProtonMomentum       = new TH1D("ProtonMomentum"  ,"",50,min,3);
  TH1D* ElectronMomentum     = new TH1D("ElectronMomentum","",50,min,3);
  TH1D* OtherMomentum        = new TH1D("OtherMomentum"   ,"",50,min,3);

  TH1D* MuonTrackLength      = new TH1D("MuonTrackLength"    ,"",200,min,10);
  TH1D* PionTrackLength      = new TH1D("PionTrackLength"    ,"",200,min,10);
  TH1D* ProtonTrackLength    = new TH1D("ProtonTrackLength"  ,"",200,min,10);
  TH1D* ElectronTrackLength  = new TH1D("ElectronTrackLength","",200,min,10);
  TH1D* OtherTrackLength     = new TH1D("OtherTrackLength"   ,"",200,min,10);

  TH1D* PiZGammaEAsymm       = new TH1D("PiZGammaEAssym"     ,"",200,-1,1);
  TH1D* PiZGammaAAsymm       = new TH1D("PiZGammaAAssym"     ,"",200,0,1);
  TH2D* PiZGammaEAAsymm      = new TH2D("PiZGammaEAAssym"    ,"",200,-1,1,200,0,1);
  TH2D* PiZGammaEnergy       = new TH2D("PiZGammaEnergy"     ,"",200,0,2,200,0,2);

  TH2D* PiZDGammaElec1Energy = new TH2D("PiZDGammaElec1Energy","",200,0,1,200,0,1);
  TH2D* PiZDGammaElec2Energy = new TH2D("PiZDGammaElec2Energy","",200,0,1,200,0,1);
  TH2D* PiZDelectElecEnergy  = new TH2D("PiZDElectElecEnergy" ,"",200,0,1,200,0,1);

  TH1D* SingleGammaEnergy    = new TH1D("SingleGammaEnergy"   ,"",200,0,1);
  //TH1D* SingleGammaEnergyNC  = new TH1D("SingleGammaEnergyNC" ,"",200,0,1);


  const double pizeromass = 0.13498;
 
  TTree *gstTree = ReadTree(inFile);

  for(int i = 0; i < gstTree->GetEntries(); i++){
    gstTree->GetEntry(i);

    // No recon neutrino energy? -> continue
    if(Ev_reco < enureconcut){continue;}

    if(EvClass_reco == 0){
      // Find if the selected lepton is not actually a lepton
      for(int k = 0; k < nf; k++){
	if(Trkf_reco[k] == TrkL_reco){
	  PdgL_reco = pdgf[k];
	  break;
	}
      }
      
      // Momentum
      double lmom = sqrt(pxL_reco*pxL_reco + pyL_reco*pyL_reco + pzL_reco*pzL_reco);
      if(lmom > 0){
	if(PdgL_reco == 13 || PdgL_reco == -13)
	  MuonMomentumCC->Fill(lmom);
	else if(PdgL_reco == 11 || PdgL_reco == -11)
	  ElectronMomentumCC->Fill(lmom);
	else if(PdgL_reco == 211 || PdgL_reco == -211)
	  PionMomentumCC->Fill(lmom);
	else if(PdgL_reco == 2212)
	  ProtonMomentumCC->Fill(lmom);
	else
	  OtherMomentumCC->Fill(lmom);
      }
    }

    // Loop over the fs particles
    for(int k = 0; k < nf; k++){
      // Reco momentum
      double momentum = sqrt(pxf_reco[k]*pxf_reco[k] + pyf_reco[k]*pyf_reco[k] + pzf_reco[k]*pzf_reco[k]);
      if(momentum < 0.0005 || Trkf_reco[k] < 0.05){continue;}

      if(Trkf_reco[k] == TrkL_reco){continue;}

      if(abs(pdgf[k]) == 11){
	ElectronMomentum->Fill(momentum);
	ElectronTrackLength->Fill(Trkf_reco[k]);
      }
      else if(abs(pdgf[k]) == 13){
	MuonMomentum->Fill(momentum);
	MuonTrackLength->Fill(Trkf_reco[k]);
      }
      else if(abs(pdgf[k]) == 211){
	PionMomentum->Fill(momentum);
	PionTrackLength->Fill(Trkf_reco[k]);
      }
      else if(pdgf[k] == 2212){
	ProtonMomentum->Fill(momentum);
	ProtonTrackLength->Fill(Trkf_reco[k]);
      }
      else{
	OtherMomentum->Fill(momentum);
	OtherTrackLength->Fill(Trkf_reco[k]);
      }
    }

    /*
    // Tracker boundaries
    const double xmin = -1.5; const double xmax = 1.5;
    const double ymin = -1.5; const double ymax = 1.5;
    const double zmin = 0.25; const double zmax = 5.5;
    */

    if(nEMf == 1)
      SingleGammaEnergy->Fill(EMEf[0]);

    // Dalitz decay events
    if(nEMf == 3 && nfpi0==1){
      int ngamma  = 0; int nelec = 0;
      double gene = 0; double eene = 0; double pene = 0;
      for(int k = 0; k < nEMf; k++){
	if(EMpdgf[k] == 22){
	  ngamma++;
	  gene = EMEf[k];
	}
	else if(EMpdgf[k] == 11){
	  nelec++;
	  eene = EMEf[k];
	}
	else if(EMpdgf[k] == -11){
	  nelec++;
	  pene = EMEf[k];
	}
      }
      if(ngamma == 1 && nelec == 2){
	PiZDelectElecEnergy->Fill(eene,pene);
	PiZDGammaElec1Energy->Fill(gene,eene);
	PiZDGammaElec2Energy->Fill(gene,pene);
      }
    }

    // Loop over EMobjects
    if(nEMf == 2 && nfpi0==1){
      bool twogammas = true;
      for(int k = 0; k < nEMf; k++){
	if(EMpdgf[k] != 22)
	  twogammas = false;
      }

      if(twogammas){
	double emasymmetry = (EMEf[0] - EMEf[1])/(EMEf[0] + EMEf[1]);
	//double angularasymmetry = (EMcthf[0] - EMcthf[1]);

	double par = sqrt(EMpxf_reco[0]*EMpxf_reco[0] + EMpyf_reco[0]*EMpyf_reco[0] + EMpzf_reco[0]*EMpzf_reco[0]);
	double pbr = sqrt(EMpxf_reco[1]*EMpxf_reco[1] + EMpyf_reco[1]*EMpyf_reco[1] + EMpzf_reco[1]*EMpzf_reco[1]);
	
	double aDOTbr = EMpxf_reco[0]*EMpxf_reco[1] + EMpyf_reco[0]*EMpyf_reco[1] + EMpzf_reco[0]*EMpzf_reco[1];
	double costhr = aDOTbr / (par * pbr);
	//double imr = sqrt(2.0 *EMEf_reco[0]  *EMEf_reco[1]  * ( 1.0 - costhr));
	/*
	// Invariant mass cut
	if( fabs(imr - pizeromass) < pi0invmass)
	npizerorecon++;
	*/

	PiZGammaEAsymm->Fill(emasymmetry);
	PiZGammaAAsymm->Fill(costhr);
	PiZGammaEAAsymm->Fill(emasymmetry,costhr);
	if(EMEf[0] > EMEf[1])
	  PiZGammaEnergy->Fill(EMEf[0],EMEf[1]);
	else
	  PiZGammaEnergy->Fill(EMEf[1],EMEf[0]);

	/*
	// Going in the Ecal?
	double sinthf[2] = {sqrt(1-EMcthf[0]*EMcthf[0]),sqrt(1-EMcthf[1]*EMcthf[1])};
	if(EMcthf[0] > 0){
	  double ydist  = ymax - vtxy;
	  double xdist  = xmax - vtxx;
	  //double xydist = sqrt(xdist*xdist + ydist*ydist);
	  double hyp = ydist/sinthf[0];
	  double zhyp = hyp*EMcthf[0];
	  double zdist = zmax - vtxz;

	  if(zhyp < zdist){ // escapes at the side
	    double ldist = hyp - EMTrkf_reco[0];
	    //cout << "Side: " << ldist << " , " << hyp << " , " << EMTrkf_reco[0] << endl;
	  }
	  else{ // escapes at the front
	    hyp = zdist/EMcthf[0];
	    double ldist = hyp - EMTrkf_reco[0];
	    //cout << "Front: " << ldist << " , " << hyp << " , " << EMTrkf_reco[0] << endl;
	  }
	}
	*/

      }
    }

  } // event loop

  // Store the histograms
  histarray->Add(MuonMomentumCC);
  histarray->Add(PionMomentumCC);
  histarray->Add(ProtonMomentumCC);
  histarray->Add(ElectronMomentumCC);
  histarray->Add(OtherMomentumCC);
  histarray->Add(MuonMomentum);
  histarray->Add(PionMomentum);
  histarray->Add(ProtonMomentum);
  histarray->Add(ElectronMomentum);
  histarray->Add(OtherMomentum);
  histarray->Add(MuonTrackLength);
  histarray->Add(PionTrackLength);
  histarray->Add(ProtonTrackLength);
  histarray->Add(ElectronTrackLength);
  histarray->Add(OtherTrackLength);

  histarray->Add(PiZGammaEAsymm);
  histarray->Add(PiZGammaAAsymm);
  histarray->Add(PiZGammaEAAsymm);
  histarray->Add(PiZGammaEnergy);
  histarray->Add(PiZDelectElecEnergy);
  histarray->Add(PiZDGammaElec1Energy);
  histarray->Add(PiZDGammaElec2Energy);
  histarray->Add(SingleGammaEnergy);
  //histarray->Add();

  gstTree->Delete();

  return histarray;
}
// ----------------------------------------------------------------------------
TObjArray* ReadFastMC::SelectCCnPi(int npions, int npi0, int seed){

  // Maximum number of charge pion to select
  bool limit = false;
  if(npions > npionnum){
    limit = true;
    cout << "You choose to select " <<  npions << " final state charge pions."
	 << "The maximum number to select should be 2."
	 << " This will go in the > 2 category." << endl;
  }

  // The histogram array
  TObjArray* histarray = new TObjArray();
  // The selection - choose true for nc events
  int whattoselect = WhatToSelect();
  // The ratio of neutrino-antineutrino in the beam
  double fluxweight = FluxWeight();

  //const double pionmass   = 0.13957;
  const double pizeromass = 0.13498;

  // Random generator
  TRandom3 *rand = new TRandom3();

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

    // Initialize
    int NPionMisIDAsProton = 0;
    int NProtonMisIDAsPion = 0;
    bool LeptonChargeFlip = false;

    int newseed = seed;

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
        if(Ef_reco[k] < 0.25){continue;}

	nneutrons++;
      }
      else{
	// Minimum track length cut
	//if(Trkf_reco[k] < tracklengthcut){continue;}
	// Energy cut
	if(Ef_reco[k] < 0.25){continue;}
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

    // Select the number of charged pions
    if(!limit && npionscharge != npions){continue;}
    if(limit) npions = npionnum + 1; // odd!!!!
    if(limit  && npionscharge <  npions){continue;}
    // Select the number of pi0s
    if(npizerorecon != npi0){continue;}

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

  histarray->Add(ERecoNeutrinoANuCC);
  histarray->Add(ERecoNeutrinoNCALL);
  histarray->Add(ERecoNeutrinoCCOTH);
  histarray->Add(ERecoNeutrinoCCCOH);
  histarray->Add(ERecoNeutrinoCCDIS);
  histarray->Add(ERecoNeutrinoCCRES);
  histarray->Add(ERecoNeutrinoCCQEL);

  gstTree->Delete();

  return histarray;
}
// ----------------------------------------------------------------------------
TObjArray* ReadFastMC::SelectNCnPi(int npions, int npi0, int seed){

  // Maximum number of charge pion to select
  bool limit = false;
  if(npions > npionnum){
    limit = true;
    cout << "You choose to select " <<  npions << " final state charge pions."
	 << "The maximum number to select should be 2."
	 << " This will go in the > 2 category." << endl;
  }

  // The histogram array
  TObjArray*  histarray = new TObjArray();
  // The selection - choose true for nc events
  int whattoselect = WhatToSelect(true);
  // The ratio of neutrino-antineutrino in the beam
  double fluxweight = FluxWeight();

  //const double pionmass   = 0.13957;
  const double pizeromass = 0.13498;

  // Random generator
  TRandom3 *rand = new TRandom3();

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

    // Initialize
    int NPionMisIDAsProton = 0;
    int NProtonMisIDAsPion = 0;
    bool LeptonChargeFlip = false;

    int newseed = seed;

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
        if(Ef_reco[k] < 0.25){continue;}

	nneutrons++;
      }
      else{
	// Minimum track length cut
	//if(Trkf_reco[k] < tracklengthcut){continue;}
	// Energy cut
	if(Ef_reco[k] < 0.25){continue;}
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

    // Select the number of charged pions
    if(!limit && npionscharge != npions){continue;}
    if(limit) npions = npionnum + 1; // odd!!!!
    if(limit  && npionscharge <  npions){continue;}
    // Select the number of pi0s
    if(npizerorecon != npi0){continue;}

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
 
  histarray->Add(ERecoNeutrinoANuNA);
  histarray->Add(ERecoNeutrinoANuCA);
  histarray->Add(ERecoNeutrinoCCALL);
  histarray->Add(ERecoNeutrinoNCOTH);
  histarray->Add(ERecoNeutrinoNCCOH);
  histarray->Add(ERecoNeutrinoNCDIS);
  histarray->Add(ERecoNeutrinoNCRES);
  histarray->Add(ERecoNeutrinoNCQEL);

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
  if(momentum > 0.8 && momentum < 8){
    cmisid = fp->Eval(momentum*1000);
  }
  else if(momentum >= 8){
    cmisid = fp->Eval(8*1000);
    if(momentum > 20 && momentum < 30)
      cmisid = cmisid*2;
    if(momentum > 30)
      cmisid = cmisid*2.5;
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
bool ReadFastMC::IsReconTrack(int seed){

  // Random generator
  TRandom3 *random = new TRandom3();
  random->SetSeed(seed);

  int rcnum = random->Integer(1000);
  if(rcnum < ReconEfficiency*1000)
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
  gstTree->SetBranchAddress("EMTrkf_reco",     &EMTrkf_reco);

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
