//____________________________________________________________________________
/*!

\class     valor::ReadFastMC - Tools to read the fast MC output

\brief     LBNE ND ReadFastMC class.

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           George Christodoulou <georgios \at hep.ph.liv.ac.uk>
           University of Liverpool

           Nick Grant <n.grant \at lancaster.ac.uk>
           University of Lancaster

\created   May 9, 2014

\copyright (c) 2010-2014, The VALOR group

*/
//____________________________________________________________________________
#ifndef READFASTMC
#define READFASTMC

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "TFile.h"
#include "TTree.h"
#include "TObjArray.h"
#include "TGraph.h"
#include "TH1.h"

#include "Utilities/UtlXML.h"

using namespace std;
// --------------------------------------------------------------------------
namespace valor {

class ReadFastMC
{
 public:

  ReadFastMC();

  virtual ~ReadFastMC();

  // Get the neutrino
  int GetNeutrino() {return neutrinoPDG;};

  // Get the verbosity level
  int GetVerbose() {return verbose;};

  // Set the histogram binning and range
  void SetHistogramRange(int minimum, int maximum) {min = minimum; max = maximum;};
  void SetHistogramBinning(int nbins) {bin = nbins;};

  // Read the datacard
  void ReadDatacard(string datacard);
  void ReadXMLDatacard(string datacard);

  // Set the maximum number of pions to select in the final state
  // If the number of pions requested is bigger than this number then all 
  // the events with npions > npionnum will be returned
  void SetMaxPionNumber(int npion) {npionnum = npion;};

  // This is based on the fastmc selection- 0 for muon-like, 1 for nue-like events, 2 for nc
  int WhatToSelect(bool nc=false);

  // Flux Weight, first put the neutrino pdg your are selecting and then the 
  // pdg of the neutrino you want to find the weight
  // The ratio of neutrino-antineutrino in the beam
  double FluxWeight(int neutpdg, int otherneutpdg);
  
  // Return a histogram array for CC/NC-npi selection.
  // First argument is the number of charge pions, second is the number of pi0
  // Only for single pi0 is working at the moment
  vector<TH1*> SelectCCnPi(int npions, int npi0);
  // And for the nc
  vector<TH1*> SelectNCnPi(int npions, int npi0);

  // FastMC tree
  TTree* FastMCTree(int seed, bool debugtree=false); 

 protected:
  // The input root file from FastMC
  string inFile;
  // Neutrino pdg for the selection
  int neutrinoPDG;
  // Recon neutrino energy cut
  double enureconcut;
  // Recon partcile energy cut
  double epionreconcut, egammareconcut, eelectronreconcut, eprotonreconcut;
  // Track length cut
  double tracklengthcut;
  // Pi0 invariant mass cut
  double pi0invmass;
  // Particle mis-identification probabilities
  double PionMisIDAsProton, PionMisIDAsKaon, ProtonMisIDAsPion, ProtonMisIDAsKaon, KaonMisIDAsPion, KaonMisIDAsProton;
  // Parameters for the charge mis-identification for the momentum and track length parameterazion
  double ChargeConfMomSlope, ChargeConfMomConst, ChargeConfTrLSlope, ChargeConfTrLConst;
  // Max momentum to apply the PID
  double MaxMomentumPID;
  // Apply the reweight
  bool reweight;
  // Set the verbosity level
  int verbose;
  // Near or far detector
  string detector;
  // Events to run
  int nevents;

  // Maximum number of pions to select in an event
  int npionnum;

  //Read the root tree from the fastmc
  TTree* ReadTree(string f);

  // Global histogram binning and range
  int min; int max; int bin;

  // The FastMC tree variables - not a complete list
  int iev, neu, neut_code;
  bool qel, mec, res, dis, coh, cohe, dfr, imd, imda, nuel, em, cc, nc, charm;

  double Ev_reco,  EvB_reco, EvUB_reco, Ehad_reco, EhadB_reco, EhadUB_reco, pxv_reco, pyv_reco, pzv_reco, Ev, Ehad;
  double wght, POTWeight;
  int EvClass_reco, isQE_reco, hasElikeEM;
  bool IsContv_reco;

  int Pdgl;
  double El, pxl, pyl, pzl, pl, cthl;

  int PdgL;
  double EL, pxL, pyL, pzL, pL, cthL;

  int PdgL_reco;
  double EL_reco, pxL_reco, pyL_reco, pzL_reco, pL_reco, cthL_reco, TrkL_reco;
  bool IsContL_reco;

  int nfp, nfn, nfpip, nfpim, nfpi0, nf;

  int nEMf;

  double Q2, Q2s, Q2_reco, W, W_reco, y, ys, y_reco;

  double vtxx, vtxy, vtxz;

  int pdgf[100], EMpdgf[100];
  double EMEf[100], EMcthf[100], EMpxf[100], EMpyf[100], EMpzf[100];
  
  double pf[100], Ef[100], p0f[100], pxf[100], pyf[100], pzf[100], cthf[100];
  double Ef_reco[100], p0f_reco[100], pxf_reco[100], pyf_reco[100], pzf_reco[100], Trkf_reco[100], cthf_reco[100];
  double EMEf_reco[100], EMcthf_reco[100], EMpxf_reco[100], EMpyf_reco[100], EMpzf_reco[100], EMPizMass_reco[100];
  
  int frw7; int rw7; double rw7_qelCCma[7]; double rw7_resCCma[7];

 private:
  ClassDef(ReadFastMC,1)
};

} // valor
#endif
