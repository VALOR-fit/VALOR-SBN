//____________________________________________________________________________
/*!

  \app       valor_sbn-make_caf_sbruce_dst

  \brief     Converts sbncode sbruce trees made from CAFs with SBNAna to VALOR DSTs.
             The DSTs contain additional variables that are not used for fitting.

	     Selections are handled at the sbruce tree level.
	     This file has support for multi-topology and PRISM bins.

  \syntax    valor_sbn-make_caf_sbruce_dst
                --input  input_analysis_file.root
                --output output_file_containing_valor_dst.root
               [--write-systematics] optionally write out the systematic variations
	       [--systematics-output] output_systematics_file.h5

  \author    John Plows <kplows \at liverpool.ac.uk>
             University of Liverpool

  \created   March 2026

  \copyright Copyright (c) 2010-2026, The VALOR group. All rights reserved.

*/

#pragma once
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-copy" // No custom copy operator in HDF5 so suppress this

// System
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
#include <unordered_map>
#include <array>
#include <utility>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <sstream>
// ROOT
#include "TFile.h"
#include "TH1D.h"
#include "TChain.h"
#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TSystem.h"
// GENIE
#include "Framework/GHEP/GHepRecord.h"
#include "Framework/GHEP/GHepParticle.h"
#include "Framework/GHEP/GHepStatus.h"
#include "Framework/Ntuple/NtpMCEventRecord.h"
#include "Framework/ParticleData/PDGCodes.h"
// VALOR/SDK
#include "valor/Conventions/Constants.h"
#include "valor/Conventions/BeamConf.h"
#include "valor/Conventions/ReacMode.h"
#include "valor/Conventions/Sample.h"
#include "valor/Messenger/Messenger.h"
#include "valor/Utilities/Env.h"
#include "valor/CmdLine/CmdLnArgList.h"
#include "valor/Utilities/UtlNumStat.h"
#include "valor/Utilities/UtlStyle.h"
#include "valor/Utilities/UtlStr.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Utilities/Rnd.h"
#include "valor/GENIEUtilities/GENIEIncludes.h"
#include "valor/GENIEUtilities/GENIEIncludes.h"
#include "valor/GENIEUtilities/UtlEventRec.h"
#include "valor/FitCore/CompoundFitElements.h"
#include "valor/FitElements/GenericSingleSampleFitModel.h"
#include "valor/KineBinning/UtlBinning.h"

using std::string;
using std::ostringstream;
using namespace valor;
using namespace valor::conv;
using namespace valor::util;

static constexpr double vPI = 3.14159265358979;

// -------------------------------------------------------------------------------------------
// Implementation
// -------------------------------------------------------------------------------------------

// A really neat helper to print a progress bar in the main loop.
// See https://stackoverflow.com/questions/14539867/
#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

void printProgress(double percentage) {
  int val = (int) (percentage * 100);
  int lpad = (int) (percentage * PBWIDTH);
  int rpad = PBWIDTH - lpad;
  printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
  fflush(stdout);
}

// Some constants to transform vertex from detector coordinates to beamline coordinates. All in cm
// Information grabbed from G4BNB, https://github.com/SBNSoftware/G4BNB
static std::unordered_map<std::string, std::array<double, 3>> detector_origins = {
  { "SBND",   { 73.78, 0.0, 11000.0 } },
  { "ICARUS", {  0.0 , 0.0, 60000.0 } }
};
// And a simple utility to grab that and output beamline-coord vertices, in m
std::array<double, 3> calc_vertex(std::string det, double vx, double vy, double vz) {
  const auto & ori = detector_origins[det];
  return { 0.01 * (vx + ori[0]), 0.01 * (vy + ori[1]), 0.01 * (vz + ori[2]) };
}

// Some further duplication from $SBNANAOBJ_INC/sbnanaobj/StandardRecord/SREnums.h .
// Keep this in sync with the sbnanaobj version *of the sample you're analysing*.
// If unsure, ask the SBND or ICARUS production teams to help you figure out which version that is.

typedef enum EInteractionMode {
  kUnknownInteractionMode    =   -1,
  kQE                        =    0,
  kRes                       =    1,
  kDIS                       =    2,
  kCoh                       =    3,
  kCohElastic                =    4,
  kElectronScattering        =    5,
  kIMDAnnihilation           =    6,
  kInverseBetaDecay          =    7,
  kGlashowResonance          =    8,
  kAMNuGamma                 =    9,
  kMEC                       =   10,
  kDiffractive               =   11,
  kEM                        =   12,
  kWeakMix                   =   13
} VInteractionMode_t;

typedef enum EInteractionType {
  kUnknownInteractionType    = -1,
  kNuanceOffset              = 1000,                ///< offset to account for adding in Nuance codes to this enum
  kCCQE                      = kNuanceOffset +  1,  ///< charged current quasi-elastic
  kNCQE                      = kNuanceOffset +  2,  ///< neutral current quasi-elastic
  kResCCNuProtonPiPlus       = kNuanceOffset +  3,  ///< resonant charged current, nu p -> l- p pi+ 
  kResCCNuNeutronPi0         = kNuanceOffset +  4,  ///< resonant charged current, nu n -> l- p pi0 
  kResCCNuNeutronPiPlus      = kNuanceOffset +  5,  ///< resonant charged current, nu n -> l- n pi+ 
  kResNCNuProtonPi0          = kNuanceOffset +  6,  ///< resonant neutral current, nu p -> nu p pi0 
  kResNCNuProtonPiPlus       = kNuanceOffset +  7,  ///< resonant neutral current, nu p -> nu p pi+ 
  kResNCNuNeutronPi0         = kNuanceOffset +  8,  ///< resonant neutral current, nu n -> nu n pi0 
  kResNCNuNeutronPiMinus     = kNuanceOffset +  9,  ///< resonant neutral current, nu n -> nu p pi- 
  kResCCNuBarNeutronPiMinus  = kNuanceOffset + 10,  ///< resonant charged current, nubar n -> l+ n pi-    
  kResCCNuBarProtonPi0       = kNuanceOffset + 11,  ///< resonant charged current, nubar p -> l+ n pi0    
  kResCCNuBarProtonPiMinus   = kNuanceOffset + 12,  ///< resonant charged current, nubar p -> l+ p pi-    
  kResNCNuBarProtonPi0       = kNuanceOffset + 13,  ///< resonant charged current, nubar p -> nubar p pi0 
  kResNCNuBarProtonPiPlus    = kNuanceOffset + 14,  ///< resonant charged current, nubar p -> nubar n pi+ 
  kResNCNuBarNeutronPi0      = kNuanceOffset + 15,  ///< resonant charged current, nubar n -> nubar n pi0 
  kResNCNuBarNeutronPiMinus  = kNuanceOffset + 16,  ///< resonant charged current, nubar n -> nubar p pi- 
  kResCCNuDeltaPlusPiPlus    = kNuanceOffset + 17,
  kResCCNuDelta2PlusPiMinus  = kNuanceOffset + 21,
  kResCCNuBarDelta0PiMinus   = kNuanceOffset + 28,
  kResCCNuBarDeltaMinusPiPlus= kNuanceOffset + 32,
  kResCCNuProtonRhoPlus      = kNuanceOffset + 39,
  kResCCNuNeutronRhoPlus     = kNuanceOffset + 41,
  kResCCNuBarNeutronRhoMinus = kNuanceOffset + 46,
  kResCCNuBarNeutronRho0     = kNuanceOffset + 48,
  kResCCNuSigmaPlusKaonPlus  = kNuanceOffset + 53,
  kResCCNuSigmaPlusKaon0     = kNuanceOffset + 55,
  kResCCNuBarSigmaMinusKaon0 = kNuanceOffset + 60,
  kResCCNuBarSigma0Kaon0     = kNuanceOffset + 62,
  kResCCNuProtonEta          = kNuanceOffset + 67,
  kResCCNuBarNeutronEta      = kNuanceOffset + 70,
  kResCCNuKaonPlusLambda0    = kNuanceOffset + 73,
  kResCCNuBarKaon0Lambda0    = kNuanceOffset + 76,
  kResCCNuProtonPiPlusPiMinus= kNuanceOffset + 79,
  kResCCNuProtonPi0Pi0       = kNuanceOffset + 80,
  kResCCNuBarNeutronPiPlusPiMinus = kNuanceOffset + 85,
  kResCCNuBarNeutronPi0Pi0   = kNuanceOffset + 86,
  kResCCNuBarProtonPi0Pi0    = kNuanceOffset + 90,
  kCCDIS                     = kNuanceOffset + 91,  ///< charged current deep inelastic scatter
  kNCDIS                     = kNuanceOffset + 92,  ///< charged current deep inelastic scatter
  kUnUsed1                   = kNuanceOffset + 93,
  kUnUsed2                   = kNuanceOffset + 94,
  kCCQEHyperon               = kNuanceOffset + 95,
  kNCCOH                     = kNuanceOffset + 96,
  kCCCOH                     = kNuanceOffset + 97,  ///< charged current coherent pion
  kNuElectronElastic         = kNuanceOffset + 98,  ///< neutrino electron elastic scatter
  kInverseMuDecay            = kNuanceOffset + 99,  ///< inverse muon decay
  kMEC2p2h                   = kNuanceOffset + 100  ///< extension of nuance encoding for MEC / 2p2h
} VInteractionType_t;

// A quick map to take base samples to sbruce topologies
static std::unordered_map<Sample_t, int> sbn_samples = {
  { ksNearNuMuCC,        0 } ,
  { ksNearNuMuCC_0p0pi,  1 } ,
  { ksNearNuMuCC_1p0pi,  2 } ,
  { ksNearNuMuCC_Np0pi,  3 } ,
  { ksNearNuMuCC_1pi,    4 } ,
  { ksNearNuMuCC_Other,  5 } ,
  { ksFarNuMuCC,        10 } ,
  { ksFarNuMuCC_0pi,    11 } ,
  { ksFarNuMuCC_1pi,    12 } ,
  { ksFarNuMuCC_Npi,    13 }
};

// and to sbruce trees
static std::unordered_map<Sample_t, std::string> sbn_sbruces = {
  { ksNearNuMuCC,        "numuCCinc" } ,
  { ksNearNuMuCC_0p0pi,  "numuCC0p0pi" } ,
  { ksNearNuMuCC_1p0pi,  "numuCC1p0pi" } ,
  { ksNearNuMuCC_Np0pi,  "numuCCNp0pi" } ,
  { ksNearNuMuCC_1pi,    "numuCC1pi" } ,
  { ksNearNuMuCC_Other,  "numuCCOther" } ,
  { ksFarNuMuCC,         "numuCCinc-far" } ,
  { ksFarNuMuCC_0pi,     "numuCC0pi-far" } ,
  { ksFarNuMuCC_1pi,     "numuCC1pi-far" } ,
  { ksFarNuMuCC_Npi,     "numuCCNpi-far" }
};

// -------------------------------------------------------------------------------------------
// Main method
// -------------------------------------------------------------------------------------------
int main(int argc, char ** argv)
{
  time_t scriptstartrawtime;
  struct tm * scriptstarttimeinfo;
  time (&scriptstartrawtime);
  scriptstarttimeinfo = localtime (&scriptstartrawtime);
  VLOG("valor_sbn", pNOTICE) << "-----------------------------------------------------------";
  VLOG("valor_sbn", pNOTICE) << " Script start local time and date:  " << asctime(scriptstarttimeinfo);
  VLOG("valor_sbn", pNOTICE) << "-----------------------------------------------------------";

  // Get arguments from command line
  CmdLnArgList arg;
  arg.Read(argc,argv, "$VALOR_EXPT/config/apps/make_caf_sbruce_dst.arg");
  VLOG("valor_sbn", pNOTICE) << arg;

  std::string thresholds = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  valor::Messenger::Instance()->Configure(thresholds);

  string opt_input_name     = arg.GetString("input");
  string opt_effs_name      = arg.GetString("efficiencies");
  bool   opt_input_is_list  = arg.GetBool("use-file-list");
  string opt_output_name    = arg.GetString("output");
  string opt_beam_name      = arg.GetString("beam");
  string opt_sample_name    = arg.GetString("sample");
  string opt_oscillation    = arg.GetString("oscillation");
  string config_file        = arg.GetString("config");
  bool   is_data            = arg.GetBool("is-data");
  std::vector<double> oaa_bin_edges = arg.GetDoubleVec("off-axis-bins");
  int    max_n_events       = arg.GetInt("max-n-events");

  // Get the beam configuration  
  // Sample is going to be determined by the topology and the off beam axis
  // Off beam bins will be passed to this macro.
  conv::BeamConf_t beam = util::BeamConfFromString(opt_beam_name);
  assert(beam != conv::kbUndefined);

  // TODO: make sbruces write out target.. For now the selection enforces almost 100% Ar40
  int tgtpdg = 1000180400;

  // Figure out the sample. 
  // If it's got Far in the name, it won't have OAA
  // If it's got Near in the name, check if the arg has OAA. If it does, complain (we'll figure it out)
  // Do not tokenise this!
  
  bool doing_oaa = false;
  if( opt_sample_name.find("ND,") != std::string::npos && 
      (oaa_bin_edges.size() > 2 || (oaa_bin_edges.size() == 2 && 
				    (oaa_bin_edges[0] > 0.0 || oaa_bin_edges[1] < 180.0)) ) ) {
    doing_oaa = true;
    if( opt_sample_name.find("OAA") != std::string::npos ) {
      VLOG("valor_sbn", pWARN) << "You asked for this OAA sample: " << opt_sample_name
			       << " . I'll ignore it, and assign off-axis bins."
			       << " You should use 'off-axis-bins' to control this behaviour.";
      
      opt_sample_name = opt_sample_name.substr(0, opt_sample_name.find(",OAA"));
    }
  }
  // RETHERE: if more than 9 OAA bins, too fine. Complain and revert to not using OAA
  if( oaa_bin_edges.size() < 2 || oaa_bin_edges.size() > 10 ) {
    VLOG("valor_sbn", pWARN) << "Too many (or too few) OAA bin edges. Reverting to no OAA.";
    doing_oaa = false;
  }
  static const Sample_t     vsample = SampleFromString(opt_sample_name);
  static const int         visample = sbn_samples[vsample];
  static const std::string vssample = sbn_sbruces[vsample];

  static const bool discriminate_topo = (vsample != ksNearNuMuCC && vsample != ksFarNuMuCC);
  VLOG("valor_sbn", pINFO) << "Using sample: " << AsString(vsample)
			   << " with doing_oaa = " << (int) doing_oaa
			   << ", discriminate_topo = " << (int) discriminate_topo;
  
  // Get the trees. If asking for a particular topology, load in that tree
  TChain * selections = new TChain(Form("Selections/%s", vssample.c_str()));

  // If we're getting efficiencies, we need to know which to use.
  // Doing some bad hard-coding to SBND, assuming I know the structure... I made that histo so I do.
  TH1D * heff = 0;
  std::unique_ptr<TFile> feff = std::unique_ptr<TFile>( TFile::Open(opt_effs_name.c_str()) );
  if( strcmp(opt_effs_name.c_str(), "None") != 0 ) {
    if( opt_sample_name.find("ND,") != std::string::npos ) {
      std::string effname;
      switch( visample ) {
      case 0 : effname = "heff_inc";   break;
      case 1 : effname = "heff_0p0pi"; break;
      case 2 : effname = "heff_1p0pi"; break;
      case 3 : effname = "heff_Np0pi"; break;
      case 4 : effname = "heff_1pi"  ; break;
      case 5 : effname = "heff_Other"; break;
      default: effname = "heff_inc"; break;
      }
      TH1D * heffile = dynamic_cast<TH1D *>( feff->Get(effname.c_str()) );
      // copy to heff
      heff = dynamic_cast<TH1D *>( heffile->Clone(0) );
      for( int i = 1; i <= heffile->GetNbinsX(); i++ ){
	heff->SetBinContent(i, heffile->GetBinContent(i));
      }
    } // directly load this in from the appropriate histogram
  } // efficiency histogram loaded. It's binned in pmu_true
  
  double NPOT = 0.0;
  if( ! opt_input_is_list ) {
    try {
      std::string dest = opt_input_name;
      selections->Add(dest.c_str());
      // open the file and get the POT now.
      // unique_ptr releases mem when out of scope! yay for good memory mgmt :)
      auto fin = std::unique_ptr<TFile>( TFile::Open(dest.c_str()) );
      NPOT += (dynamic_cast<TH1D *>( fin->Get("Selections/POT") ))->Integral();
      fin->Close();
    } catch (const std::exception & e) {
      VLOG("valor_sbn", pFATAL) << "Caught exception when processing input file: " << e.what();
    } // catch exception
  } else {
    // Add files to the chain. Check files exist, check all inputs OK
    try {
      std::ifstream input_stream(opt_input_name.c_str());
      std::string line; std::string count_line;
      int iFile = 0; int nFiles = 0;
      while( std::getline(input_stream, count_line) ) {
	nFiles++;
      }
      input_stream.clear();
      input_stream.seekg(0, std::ios::beg);
      
      while( std::getline(input_stream, line) ) {
	try {
	  std::string dest = line;
	  selections->Add(dest.c_str());

	  printProgress(static_cast<double>(iFile+1)/static_cast<double>(nFiles));
	  auto fin = std::unique_ptr<TFile>( TFile::Open(line.c_str()) );
	  NPOT += (dynamic_cast<TH1D *>( fin->Get("Selections/POT") ))->Integral();
	  fin->Close();
	} catch (const std::exception & ex) {
	  VLOG("valor_sbn", pFATAL) << "Caught exception when processing single input file " << line.c_str() << " in list: " << ex.what();
	} // catch exception in line of input list
	
	iFile++;
      } // loop over lines
      input_stream.close();
    } catch (const std::exception & e) {
      VLOG("valor_sbn", pFATAL) << "Caught exception when processing input file list: " << e.what();
    } // catch input list exception
  }

  std::ostringstream asts;
  asts << "I successfully opened " << selections->GetNtrees() 
       << " sbruce files, with " << NPOT << " POT.";
  asts << "\nThere are " << selections->GetEntries() << " events.";

  VLOG("valor_sbn", pNOTICE) << asts.str();

  // Start setting out the structure
  int    valor_dst_sample       = -1;
  int    valor_dst_beam         = -1;   // see Conventions/BeamConf.h
  int    valor_dst_reac_mode    = -1;   // see Conventions/ReacMode.h
  int    valor_dst_reac_type    = -1;   // see Conventions/ReacMode.h
  int    valor_dst_target       = -1;   // nuclear target -  GENIE PDG convention
  double valor_dst_baseline     = -1.0; // true baseline of the event
  int    valor_dst_init_nupdg   = -1;   // Initial PDG
  int    valor_dst_final_nupdg  = -1;   // Final PDG
  double valor_dst_oaa          = -1.0; // Off axis angle wrt beam z axis, in degrees
  double valor_dst_enu_true     = -1.0; // true neutrino energy, in GeV
  double valor_dst_enu_reco     = -1.0; // reco neutrino energy, in GeV
  double valor_dst_pmu_true     = -1.0; // true muon momentum, in GeV/c
  double valor_dst_pmu_reco     = -1.0; // reco muon momentum, in GeV/c
  double valor_dst_costhmu_true = -1.0; // true cos(theta) mu
  double valor_dst_costhmu_reco = -1.0; // reco cos(theta) mu
  double valor_dst_wgt_pot      = -1.0; // POT weight in 1e20 POT units
  double valor_dst_wgt_eff      = -1.0; // weight from efficiency correction

  TFile fout(opt_output_name.c_str(),"recreate");
  fout.cd();

  TTree * valor_dst =
    new TTree("valor_sbn_dst","DST input for VALOR/SBN fit");
  
  Long64_t nev = selections->GetEntries();
  if( max_n_events > 0 ) nev = std::min( nev, static_cast<Long64_t>(max_n_events) );
  Long64_t nev_accept = 0;
  std::vector<Long64_t> nev_accept_by_mode;
  for (int im = 0 ; im < valor::conv::kNReacModes; im++) {
    nev_accept_by_mode.push_back(0);
  }
  
  valor_dst->Branch("beam"          , &valor_dst_beam         ,"beam/I"          );
  valor_dst->Branch("sample"        , &valor_dst_sample       ,"sample/I"        );
  valor_dst->Branch("reac_mode"     , &valor_dst_reac_mode    ,"reac_mode/I"     );
  valor_dst->Branch("reac_type"     , &valor_dst_reac_type    ,"reac_type/I"     );
  valor_dst->Branch("init_pdg"      , &valor_dst_init_nupdg   ,"init_pdg/I"      );
  valor_dst->Branch("final_pdg"     , &valor_dst_final_nupdg  ,"final_pdg/I"     );
  valor_dst->Branch("baseline"      , &valor_dst_baseline     ,"baseline/D"      );
  valor_dst->Branch("off_axis_angle", &valor_dst_oaa          ,"off_axis_angle/D");
  valor_dst->Branch("target"        , &valor_dst_target       ,"target/I"        );
  valor_dst->Branch("enu_true"      , &valor_dst_enu_true     ,"enu_true/D"      );
  valor_dst->Branch("enu_reco"      , &valor_dst_enu_reco     ,"enu_reco/D"      );
  valor_dst->Branch("pmu_true"      , &valor_dst_pmu_true     ,"pmu_true/D"      );
  valor_dst->Branch("pmu_reco"      , &valor_dst_pmu_reco     ,"pmu_reco/D"      );
  valor_dst->Branch("costhmu_true"  , &valor_dst_costhmu_true ,"costhmu_true/D"  );
  valor_dst->Branch("costhmu_reco"  , &valor_dst_costhmu_reco ,"costhmu_reco/D"  );
  valor_dst->Branch("wght_pot"      , &valor_dst_wgt_pot      ,"wght_pot/D"      );
  valor_dst->Branch("wght"          , &valor_dst_wgt_eff      ,"wght/D"          );

  // Get the branch addresses from sbruce.
  int iscc, isnc;
  int nupdg, initpdg;
  int genie_mode, genie_type;
  int reco_topology;
  double baseline; 
  double enu_true, enu_reco; // using the inclusive enu_reco
  double pmu_true, pmu_reco;
  double costhmu_true, costhmu_reco;
  double vtx_x, vtx_y, vtx_z;
  double wgt;
  
  selections->SetBranchAddress("iscc", &iscc);
  selections->SetBranchAddress("isnc", &isnc);
  selections->SetBranchAddress("nu_pdg", &nupdg);
  selections->SetBranchAddress("init_pdg", &initpdg);
  selections->SetBranchAddress("genie_mode", &genie_mode);
  selections->SetBranchAddress("genie_type", &genie_type);
  selections->SetBranchAddress("reco_topology", &reco_topology);
  selections->SetBranchAddress("baseline", &baseline);
  selections->SetBranchAddress("enu_true", &enu_true);
  selections->SetBranchAddress("enu_reco_inc", &enu_reco);
  selections->SetBranchAddress("pmu_true", &pmu_true);
  selections->SetBranchAddress("pmu_reco", &pmu_reco);
  selections->SetBranchAddress("costhmu_true", &costhmu_true);
  selections->SetBranchAddress("costhmu_reco", &costhmu_reco);
  selections->SetBranchAddress("vtx_x", &vtx_x);
  selections->SetBranchAddress("vtx_y", &vtx_y);
  selections->SetBranchAddress("vtx_z", &vtx_z);
  selections->SetBranchAddress("weight", &wgt); // this will contain the efficiecy correction

  // Set constant variables.
  valor_dst_beam    = beam;
  valor_dst_target  = tgtpdg;
  valor_dst_wgt_pot = 1.0 / NPOT;

  for( Long64_t iev = 0; iev < nev; iev++ ) {
    if( nev > 100 ) { printProgress(static_cast<double>(iev+1)/static_cast<double>(nev)); }

    Sample_t valor_sample = vsample;
    int  isample = static_cast<int>(vsample);
    selections->GetEntry(iev);
    
    // We'll fix the sample based on what was asked for.
    // If the sample is inclusive, just keep anything.
    // Otherwise, specify the topology and keep it if it matches.
    if( discriminate_topo && reco_topology != visample ) { continue; } // Skip this event.

    std::array<double, 3> vertex = calc_vertex( "SBND", vtx_x, vtx_y, vtx_z );
    valor_dst_oaa = std::atan2( std::sqrt(vertex[0]*vertex[0] + vertex[1]*vertex[1]), vertex[2] );
    valor_dst_oaa *= 180.0 / vPI;

    if( doing_oaa ) { // Determine the sample based on the OAA bin
      isample++; // start at OAA bin 0
      if( valor_dst_oaa < oaa_bin_edges.front() || valor_dst_oaa > oaa_bin_edges.back() ) {
	VLOG("valor_sbn", pNOTICE) << "Skipping event with OAA = : " << valor_dst_oaa
				   << " (outside range [" << oaa_bin_edges.front()
				   << ", " << oaa_bin_edges.back() << "]. Consider increasing OAA range";
	continue;
      }
      std::vector<double>::iterator it_oaa = oaa_bin_edges.begin()+1;
      while( it_oaa < oaa_bin_edges.end() && *it_oaa < valor_dst_oaa ) { ++it_oaa; isample++; }
      valor_sample = SampleFromInt(isample);
      VLOG("valor_sbn", pDEBUG) << "At an angle " << valor_dst_oaa << " I get sample "
				<< AsString(valor_sample);
    } // if doing OAA
    valor_dst_sample = valor_sample;

    valor_dst_init_nupdg = initpdg;
    valor_dst_final_nupdg = nupdg;
    valor_dst_baseline = baseline;
    
    valor_dst_enu_true = enu_true;
    valor_dst_enu_reco = enu_reco;
    valor_dst_pmu_true = pmu_true;
    valor_dst_pmu_reco = pmu_reco;
    valor_dst_costhmu_true = costhmu_true;
    valor_dst_costhmu_reco = costhmu_reco;

    // Determine the reaction mode and reaction type
    // These will be mapped from GENIE mode and type (see the enums dropped in this file's preamble)
    // We'll need to think more about cosmic/dirt separation, though.

    // Also, for now I'll assume no 3-flavour oscillation (this is a short baseline expt!)
    
    switch( static_cast<VInteractionMode_t>( genie_mode ) ) {
    case kUnknownInteractionMode: 
      valor_dst_reac_mode = kmCosmic; 
      valor_dst_reac_type = kmtCosmic; 
      break;

    case kQE: 
      switch( nupdg ) {
      case  14: valor_dst_reac_mode = (iscc) ? kmNuMuCCQE    : kmNuMuNCQE    ; break;
      case -14: valor_dst_reac_mode = (iscc) ? kmNuMuBarCCQE : kmNuMuBarNCQE ; break;
      case  12: valor_dst_reac_mode = (iscc) ? kmNuECCQE     : kmNuENCQE     ; break;
      case -12: valor_dst_reac_mode = (iscc) ? kmNuEBarCCQE  : kmNuEBarNCQE  ; break;
      }
      valor_dst_reac_type = (iscc) ? kmtCCQE : kmtNCQE;
      break;

    case kDIS: 
      switch( nupdg ) {
      case  14: valor_dst_reac_mode = (iscc) ? kmNuMuCCDIS    : kmNuMuNCDIS    ; break;
      case -14: valor_dst_reac_mode = (iscc) ? kmNuMuBarCCDIS : kmNuMuBarNCDIS ; break;
      case  12: valor_dst_reac_mode = (iscc) ? kmNuECCDIS     : kmNuENCDIS     ; break;
      case -12: valor_dst_reac_mode = (iscc) ? kmNuEBarCCDIS  : kmNuEBarNCDIS  ; break;
      }
      valor_dst_reac_type = (iscc) ? kmtCCDIS : kmtNCDIS;
      break;

    case kCoh: 
      switch( nupdg ) {
      case  14: valor_dst_reac_mode = (iscc) ? kmNuMuCCCOH    : kmNuMuNCCOH    ; break;
      case -14: valor_dst_reac_mode = (iscc) ? kmNuMuBarCCCOH : kmNuMuBarNCCOH ; break;
      case  12: valor_dst_reac_mode = (iscc) ? kmNuECCCOH     : kmNuENCCOH     ; break;
      case -12: valor_dst_reac_mode = (iscc) ? kmNuEBarCCCOH  : kmNuEBarNCCOH  ; break;
      }
      valor_dst_reac_type = (iscc) ? kmtCCCOH : kmtNCCOH;
      break;

    case kMEC: 
      switch( nupdg ) {
      case  14: valor_dst_reac_mode = (iscc) ? kmNuMuCCMEC    : kmNuMuNCMEC    ; break;
      case -14: valor_dst_reac_mode = (iscc) ? kmNuMuBarCCMEC : kmNuMuBarNCMEC ; break;
      case  12: valor_dst_reac_mode = (iscc) ? kmNuECCMEC     : kmNuENCMEC     ; break;
      case -12: valor_dst_reac_mode = (iscc) ? kmNuEBarCCMEC  : kmNuEBarNCMEC  ; break;
      }
      valor_dst_reac_type = (iscc) ? kmtCCMEC : kmtNCMEC;
      break;

    case kRes:
      // From here, we need to figure out based on the genie type.
      // The larsoft mode and type let us figure out which mode this is without looking at particle counts
      switch( static_cast<VInteractionType_t>( genie_type ) ) {
      case kNuanceOffset: // this is SPP
	switch( nupdg ) {
	case 14: 
	  valor_dst_reac_mode = (iscc) ? kmNuMuCCRESSPP : kmNuMuNCRESSPP; 
	  valor_dst_reac_type = (iscc) ? kmtCCRESvSPP : kmtNCRESvSPP; 
	  break;
	case -14:
	  valor_dst_reac_mode = (iscc) ? kmNuMuBarCCRESSPP : kmNuMuBarNCRESSPP; 
	  valor_dst_reac_type = (iscc) ? kmtCCRESvbSPP : kmtNCRESvbSPP; 
	  break;
	case 12: 
	  valor_dst_reac_mode = (iscc) ? kmNuECCRESSPP : kmNuENCRESSPP; 
	  valor_dst_reac_type = (iscc) ? kmtCCRESvSPP : kmtNCRESvSPP; 
	  break;
	case -12:
	  valor_dst_reac_mode = (iscc) ? kmNuEBarCCRESSPP : kmNuEBarNCRESSPP; 
	  valor_dst_reac_type = (iscc) ? kmtCCRESvbSPP : kmtNCRESvbSPP; 
	  break;
	}
	break;

      case kResCCNuProtonPiPlus:
      case kResNCNuProtonPiPlus:
	switch( nupdg ) {
	case 14: 
	  valor_dst_reac_mode = (iscc) ? kmNuMuCCRESpPiP : kmNuMuNCRESpPiP;
	  break;
	case 12:
	  valor_dst_reac_mode = (iscc) ? kmNuECCRESpPiP : kmNuENCRESpPiP;
	}
	valor_dst_reac_type = (iscc) ? kmtCCRESvpPiP : kmtNCRESvpPiP;
	break;

      case kResCCNuNeutronPiPlus:
	valor_dst_reac_mode = (nupdg == 14) ? kmNuMuCCRESnPiP : kmNuECCRESnPiP;
	valor_dst_reac_type = kmtCCRESvnPiP;
	break;

      case kResCCNuNeutronPi0:
      case kResNCNuNeutronPi0:
	switch( nupdg ) {
	case 14: 
	  valor_dst_reac_mode = (iscc) ? kmNuMuCCRESnPi0 : kmNuMuNCRESnPi0;
	  break;
	case 12:
	  valor_dst_reac_mode = (iscc) ? kmNuECCRESnPi0 : kmNuENCRESnPi0;
	}
	valor_dst_reac_type = (iscc) ? kmtCCRESvnPi0 : kmtNCRESvnPi0;
	break;

      case kResNCNuProtonPi0:
	valor_dst_reac_mode = (nupdg == 14) ? kmNuMuNCRESpPi0 : kmNuENCRESpPi0;
	valor_dst_reac_type = kmtNCRESvpPi0;
	break;

      case kResNCNuNeutronPiMinus:
	valor_dst_reac_mode = (nupdg == 14) ? kmNuMuNCRESnPiM : kmNuENCRESnPiM;
	valor_dst_reac_type = kmtNCRESvnPiM;
	break;

      case kResCCNuBarNeutronPiMinus:
      case kResNCNuBarNeutronPiMinus:
	switch( nupdg ) {
	case -14:
	  valor_dst_reac_mode = (iscc) ? kmNuMuBarCCRESnPiM : kmNuMuBarNCRESnPiM;
	  break;
	case -12:
	  valor_dst_reac_mode = (iscc) ? kmNuEBarCCRESnPiM : kmNuEBarNCRESnPiM;
	}
	valor_dst_reac_type = (iscc) ? kmtCCRESvbnPiM : kmtNCRESvbnPiM;
	break;

      case kResNCNuBarNeutronPi0:
	valor_dst_reac_mode = (nupdg == -14) ? kmNuMuBarNCRESnPi0 : kmNuEBarNCRESnPi0;
	valor_dst_reac_type = kmtNCRESvbnPi0;
	break;

      case kResCCNuBarProtonPi0:
      case kResNCNuBarProtonPi0:
	switch( nupdg ) {
	case -14:
	  valor_dst_reac_mode = (iscc) ? kmNuMuBarCCRESpPi0 : kmNuMuBarNCRESpPi0;
	  break;
	case -12:
	  valor_dst_reac_mode = (iscc) ? kmNuEBarCCRESpPi0 : kmNuEBarNCRESpPi0;
	}
	valor_dst_reac_type = (iscc) ? kmtCCRESvbpPi0 : kmtNCRESvbpPi0;
	break;

      case kResCCNuBarProtonPiMinus:
	valor_dst_reac_mode = (nupdg == -14) ? kmNuMuBarCCRESpPiM : kmNuEBarCCRESpPiM;
	valor_dst_reac_type = kmtCCRESvbpPiM;
	break;

      case kResNCNuBarProtonPiPlus:
	valor_dst_reac_mode = (nupdg == -14) ? kmNuMuBarNCRESpPiP : kmNuEBarNCRESpPiP;
	valor_dst_reac_type = kmtNCRESvbpPiP;
	break;

      default:
	valor_dst_reac_mode = kmtUndefined; // if undefined type, that's an issue...
	valor_dst_reac_type = kmtUndefined;
      } // switch genie type
      break;
    default:
      valor_dst_reac_mode = kmUndefined;
      valor_dst_reac_type = kmtUndefined;
    } // switch genie mode

    // Shweta says this should be efficiency not 1/efficiency, so we'll fill that.
    valor_dst_wgt_eff = 1.0;
    if( heff ) {
      valor_dst_wgt_eff = heff->GetBinContent(heff->FindBin(pmu_true));
    }

    if(valor_dst_enu_true >= 0.){ valor_dst->Fill(); }
  } // loop over entries in chain
  
  std::cout << "" << std::endl;
  
  // Saving VALOR DST to output file
  VLOG("valor_sbn", pNOTICE)
    << "Saving VALOR/SBN DST to: " << opt_output_name;
  valor_dst->Write();
  fout.Close();
  
  VLOG("valor_sbn", pNOTICE)  << "Done!";
  
  time_t endrawtime;
  struct tm * endtimeinfo;
  time (&endrawtime);
  endtimeinfo = localtime (&endrawtime);
  time_t total_time = endrawtime-scriptstartrawtime;
  std::cout << "-----------------------------------------------------------" << std::endl;
  std::cout << " End local time and date  :  " << asctime(endtimeinfo);
  std::cout << " Total time taken         :  " << total_time/static_cast<double>(60) << " minutes" << std::endl;
  std::cout << "-----------------------------------------------------------" << std::endl;

  return 0;
}

#pragma diagnostic pop
