//____________________________________________________________________________
/*!

  \app       valor_sbn-make_caf_minidst

  \brief     Converts input SBNCode analysis DSTs to the VALOR mini-DST format.

  \note      There are two formats for CAF files (.flat.root and .caf.root)
             Will write this code assuming input is in .flat.root format (looks easier)
             If needed will look at making it deal with .caf.root format at some point. 

  \syntax    valor_sbn-make_sbncode_minidst
                --input  input_analysis_file.root
                --output output_file_containing_valor_minidst.root
               [--write-universes] optionally write out the systematic variations
               [--disable-checks]

  \author    Rhiannon Jones <rhiannon.jones \at liverpool.ac.uk>
             University of Liverpool

  \created   March 2019

  \copyright Copyright (c) 2010-2020, The VALOR group. All rights reserved.

*/
//____________________________________________________________________________

// --------------------------------------
//
// Systematic uncertaities aren't yet included in the CAF files - hence all the stuff
// about universes is commented out (hopefully i got all the relevent bits).
// The "status_code" variable (used e.g. for particle counting) is now called "gstatus" (genie_status).
// At the moment the sbncode develop branch isn't filling it (true_particles.gstatus) 
// correctly so the variable is filled with gibberish.
// Think I've fixed it now and added the fsp bit as seen in the old files (ask for my branch)
//
// The CAFMaker produces a .caf.root file.
// Use the executable 'flatten_caf' to convert to .flat.root format
// (command: flatten_caf input_file.caf.root output_file.flat.root)
//
//
// --------------------------------------

// System
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
#include <utility>
#include <algorithm>
#include <iterator>
// ROOT
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TBranch.h>
#include <TLeaf.h>
#include <TSystem.h>
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
// SBNcode - See for example Gray or Rhiannon's branch (not the default)
//#include "core/Event.hh"

using std::string;
using std::ostringstream;

void GetCommandLineArgs (int /*argc*/, char ** /*argv*/);
// The trees we need to access (in the gobal "recTree" folder)
//static const string grec_tree           = "recTree/rec";
//static const string grec_mcnu_tree      = "recTree/rec.mc.nu";
//static const string grec_fake_reco_tree = "recTree/rec.fake_reco";
static const string global_tree = "recTree";
static const string genie_tree  = "GenieEvtRecTree";

static const int gPrintEveryNEvents   = 50000;

static const int max_n_universes = 10000;

// control constants for array sizes.. CAFs store arrays not vectors. Ugh.
static const unsigned int kMaxNFRHadrons = 50;
static const unsigned int kMaxNFSParticles = 50;
static const unsigned int kMaxNFRSlices = 20;
static const unsigned int kMaxNTrueInteractions = 20;
static const unsigned int kMaxNStackParticles = 250;

// I add a control variable to check which entry of the CAF we read. Want to compare hadron types
int fEntryNo = -1;

// Should move this to a header file (eg DSTTypes or something).
//~ typedef Double_t variation_output_type;
//~ const char variation_output_type_root = 'D';
typedef Float_t variation_output_type;
const char variation_output_type_root = 'F';

// The enum simb::int_type_ from LarSoft (copied from MCNeutrino.h, in v06_05_00)
// Still in v09_23_02_01, SREnums.h:enum genie_interaction_mode_

typedef enum ELarMode{
  kLArUnknownInteraction = -1,
  kLArQE                 =  0,
  kLArRes                =  1,
  kLArDIS                =  2,
  kLArCoh                =  3,
  kLArCohElastic         =  4,
  kLArElectronScattering =  5,
  kLArIMDAnnihilation    =  6,
  kLArInverseBetaDecay   =  7,
  kLArGlashowResonance   =  8,
  kLArAMNuGamma          =  9,
  kLArMEC                = 10,
  kLArDiffractive        = 11,
  kLArEM                 = 12,
  kLArWeakMix            = 13
} LArMode_t;

std::vector<TString> nonResVariations = 
{
"genie_NonResRvpCC1pi_Genie",
"genie_NonResRvnCC1pi_Genie",
"genie_NonResRvbarnCC1pi_Genie",
"genie_NonResRvbarpCC1pi_Genie",
"genie_NonResRvpCC2pi_Genie",
"genie_NonResRvnCC2pi_Genie",
"genie_NonResRvbarnCC2pi_Genie",
"genie_NonResRvbarpCC2pi_Genie",
"genie_NonResRvpNC1pi_Genie",
"genie_NonResRvnNC1pi_Genie",
"genie_NonResRvbarnNC1pi_Genie",
"genie_NonResRvbarpNC1pi_Genie",
"genie_NonResRvpNC2pi_Genie",
"genie_NonResRvnNC2pi_Genie",
"genie_NonResRvbarnNC2pi_Genie",
"genie_NonResRvbarpNC2pi_Genie",
};

valor::conv::Sample_t GetOtherSample(const valor::conv::Sample_t &s, const bool &numu);
void FillVariationBranches(const TString &vname,
                           const size_t &n_universes,
                           TObjArray &variation_names,
                           std::map<TString,int> &variation_nentries,
                           std::map<TString,variation_output_type *> &variation_entries,
                           TTree *valor_minidst);
void GetCorrectVariationName(const int nuc_pdg, const bool iscc, TString &vname);
void GetPair(const TString &vname, std::pair<TString,TString> &new_vnames);

// Utility function: Get all permutations recursively
template <typename T>
void ConstructRecursion( std::vector<T> left, std::vector<T> right, 
			 std::vector<std::vector<std::pair<T, T>>> & perms,
			 bool summarise = false);

//___________________________________________________________________
int main(int argc, char ** argv)
{
  time_t scriptstartrawtime;
  struct tm * scriptstarttimeinfo;
  time (&scriptstartrawtime);
  scriptstarttimeinfo = localtime (&scriptstartrawtime);
  std::cout << "-----------------------------------------------------------" << std::endl;
  std::cout << " Script start local time and date:  " << asctime(scriptstarttimeinfo);
  std::cout << "-----------------------------------------------------------" << std::endl;

  // Set GENIE print level
  genie::GHepRecord::SetPrintLevel(genie::RunOpt::Instance()->EventRecordPrintLevel());

  using namespace valor;

  CmdLnArgList arg;
  arg.Read(argc,argv, "$VALOR_EXPT/config/apps/make_sbncode_minidst.arg");
  VLOG("valor_sbn", pNOTICE) << arg;

  std::string thresholds = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  valor::Messenger::Instance()->Configure(thresholds);

  string opt_beam_name      = arg.GetString("beam");
  string opt_sample_name    = arg.GetString("sample");
  string opt_output_name    = arg.GetString("output");
  string opt_input_name     = arg.GetString("input");
  string opt_oscillation    = arg.GetString("oscillation");
  bool   opt_disable_checks = arg.GetBool("disable-checks");
  bool   write_universes    = arg.GetBool("write-universes");
  bool   apply_weights      = !(arg.GetBool("dont-apply-weights"));
  bool   no_truth           = arg.GetBool("no-truth");
  bool   other_sample       = arg.GetBool("other-sample");
  bool   fix_nonres         = arg.GetBool("fix-nonres");
  bool   status_code_set    = arg.GetBool("status-code-set");
  int    max_n_events       = arg.GetInt("max-n-events");
  //bool   use_fake_reco      = arg.GetBool("use-fake-reco");
  bool   dummy_mode         = arg.GetBool("dummy-mode");
  double pot                = arg.GetDouble("pot");

  // Get the sample and beam configuration
  conv::Sample_t sample = util::SampleFromString(opt_sample_name);
  assert(sample != conv::ksUndefined);

  conv::BeamConf_t beam = util::BeamConfFromString(opt_beam_name);
  assert(beam != conv::kbUndefined);

  if(no_truth && write_universes)
    VLOG("valor_sbn", pFATAL) << " Error: Cannot write universes if there is no truth information supplied ";

  if(apply_weights)
    VLOG("valor_sbn", pNOTICE) << " Chosen to apply valor_minidst_wght ";
  else
    VLOG("valor_sbn", pNOTICE) << " Chosen not to apply valor_minidst_wght";

  // If we want to define 'other' as anything but the sample defined in the arguments, set this to true
  if(other_sample)
    VLOG("valor_sbn", pNOTICE) << " Chosen to look for events which do NOT fall under the definition of the sample, "
                               << util::AsString(sample);

  // Check if we are looking at nue_disappearance from the opt_oscillation argument
  // so that we reject the nue appearance oscillated events later
  string nue_dis = "nue-disappearance";
  size_t found_nue_dis = opt_oscillation.find(nue_dis);
  bool nue_disappearance = false;
  if(found_nue_dis != string::npos){
    nue_disappearance = true;
    VLOG("valor_sbn", pINFO)
        << "Looking at a nue disappearance event from the oscillation option: " << opt_oscillation;
  }
  else
    VLOG("valor_sbn", pINFO)
        << "NOT looking at a nue disappearance event from the oscillation option: " << opt_oscillation;

  // Determine sample-types
  bool is_nueint        = false;
  bool is_nueosc        = false;
  bool is_nuenumu       = false;
  bool is_numu          = false;
  bool is_nue           = false;
  bool is_dirt          = false;
  bool is_cosmic        = false;
  string str_numu       = "Numu";
  string str_nue        = "Nue";
  string str_int        = "_Int";
  string str_osc        = "_Osc";
  string str_dirt       = "_Dirt";
  string str_cosmic     = "_Nu_Cosmic_Dirt";

  //Find substrings and check the selected nuE sample-type if necessary
  size_t found_nue  = opt_input_name.find(str_nue);
  size_t found_numu = opt_input_name.find(str_numu);

  // Get selected nuMu from sample name
  if(found_nue == string::npos && found_numu != string::npos)
    is_numu = true;

  if(found_nue != string::npos){
    is_nue = true;
    // We are looking at a nue sample, check if osc, intrinsic or numu
    size_t found_nueosc  = opt_input_name.find(str_osc);
    size_t found_nueint  = opt_input_name.find(str_int);
    size_t found_nuenumu = opt_input_name.find(str_numu);
    size_t found_nuedirt = opt_input_name.find(str_dirt);                                                                                                          
    size_t found_cosmic  = opt_input_name.find(str_cosmic); 
    
    if(found_cosmic != string::npos){                                                                                                                                    
      is_cosmic = true;  
    } 
    if(found_nueosc != string::npos && found_nueint == string::npos && found_nuenumu == string::npos)
      is_nueosc = true;
    else if(found_nueosc != string::npos){
      VLOG("valor_sbn", pFATAL)
        << "Error: Found selected nuE oscillated file with hint of intrinsic and/or numu in the name - misleading: " << opt_input_name;
      exit(1);
    }
    if(found_nueint != string::npos && found_nueosc == string::npos && found_nuenumu == string::npos)
      is_nueint = true;
    else if(found_nueint != string::npos){
      VLOG("valor_sbn", pFATAL)
        << "Error: Found selected nuE intrinsic file with hint of oscillated and/or numu in the name - misleading: " << opt_input_name;
      exit(1);
    }
    if(found_nuenumu != string::npos && found_nueosc == string::npos && found_nueint == string::npos)
      is_nuenumu = true;
    else if(found_nuenumu != string::npos){
      VLOG("valor_sbn", pFATAL)
        << "Error: Found selected nuE numu file with hint of oscillated and/or intrinsic in the name - misleading: " << opt_input_name;
      exit(1);
    }
    if(found_nuedirt != string::npos && found_nueosc == string::npos && found_nueint == string::npos && found_nuenumu == string::npos)                                
      is_dirt = true;                                                                                                                                                 
    else if(found_nuedirt != string::npos){                                                                                                                           
      VLOG("make_sbncode_minidst", pFATAL)                                                                                                                               
        << "Error: Found appearance dirt file with hint of oscillated and/or intrinsic and/or numu in the name - misleading: " << opt_input_name;                     
      exit(1);                                                                                                                                                           
    }
  }
  

  bool found_nues[] = {is_nueosc, is_nueint, is_nuenumu, is_dirt};
  if(found_nue && std::count(found_nues, found_nues+sizeof(found_nues), 1) > 1){
    VLOG("valor_sbn", pFATAL)
      << "Error: Found multiple selected nuE types in filename - misleading: " << opt_input_name;
    exit(1);
  }

  // Make sure we are finding at least 1 of numu or nue in the name
  bool found[] = {is_numu, is_nueosc, is_nueint, is_nuenumu, is_dirt, is_cosmic};
  // Manually select the type of file we're looking at since CAF files have unhelpful names atm
  // Make this a smarter at somepoint (command line arg?)
  if(std::count(found, found+sizeof(found), 1) == 0){
    //VLOG("valor_sbn", pFATAL)
      //<< "Error: Found hint of neither selected nuE (" << str_nue << ", " << str_int << ", " << str_osc << ", " << str_dirt << "," << str_cosmic << ") nor selected nuMu ( " << str_numu << ") in filename - misleading: " << opt_input_name;
    //exit(1);
    VLOG("valor_sbn", pNOTICE)
      << "Didn't recognise the events types from the file name, gonna assume it's numu and continue.";
    is_numu = true;
  }

  // CHECKING OUTPUT OF NEW CODE
  std::cout << " Input filename : " << opt_input_name << " - ";
  if(is_nueosc)
    std::cout << " Selected NuE, Oscillated " << std::endl;
  if(is_nueint)
    std::cout << " Selected NuE, Intrinsic " << std::endl;
  if(is_nuenumu)
    std::cout << " Selected NuE, NuMu " << std::endl;
  if(is_numu)
    std::cout << " Selected NuMu, NuMu " << std::endl;
  if(is_dirt && !is_cosmic)
    std::cout << " Dirt " << std::endl;
  if(is_dirt && is_cosmic)
    std::cout << " Cosmics with Dirt" << std::endl;

  // Get the POT of the sample from the subrun tree
  double mcsample_pot = -1.;
  TChain * recTree = new TChain(global_tree.c_str());
  TChain * gTree;
  if(!dummy_mode) gTree   = new TChain(genie_tree.c_str());
  recTree->Add(opt_input_name.c_str());
  if(!dummy_mode)gTree->Add(opt_input_name.c_str());
  if(!recTree || !recTree->GetEntries()) {
    VLOG("valor_sbn", pFATAL)
      << "Error: Unable to read " << global_tree
      <<" from "<< opt_input_name;
    exit(1);
  }
  if(!dummy_mode) {
    if(!gTree || !gTree->GetEntries()) {
      VLOG("valor_sbn", pFATAL)
	<< "Error: Unable to read " << genie_tree
	<<" from "<< opt_input_name;
      exit(1);
    }
  }

  Long64_t nev_subrun = recTree->GetEntries();
  VLOG("valor_sbn", pNOTICE)
    << "Input tree has " << nev_subrun << ((nev_subrun==1) ? " entry." : " entries.");

  unsigned int npot = nev_subrun;
  if(pot==-999) {
    for(unsigned int i = 0; i < npot; ++i){
      recTree->GetEntry(i);
      mcsample_pot += recTree->GetLeaf("rec.hdr.pot")->GetValue();
    }

    if(mcsample_pot == -1.){
      VLOG("valor_sbn", pFATAL)
	<< "Error: Not able to access MCSample POT from " << global_tree;
      exit(1);
    }
    VLOG("valor_sbn", pNOTICE)
      << "POT in the input file is " << mcsample_pot;
  }else{
    mcsample_pot = pot;
    VLOG("valor_sbn", pNOTICE)
      << "POT from argument is " << mcsample_pot;
  }

  int    valor_minidst_sample       = sample;
  int    valor_minidst_beam         = -1;  // see Conventions/BeamConf.h
  int    valor_minidst_reac_mode    = -1;  // see Conventions/ReacMode.h
  int    valor_minidst_reac_type    = -1;  // see Conventions/ReacMode.h
  int    valor_minidst_target       = -1;  // nuclear target -  GENIE PDG convention
  double valor_minidst_baseline     = -1.; // true baseline of the event
  int    valor_minidst_init_nupdg   = -1;  // Initial PDG
  int    valor_minidst_final_nupdg  = -1;  // Final PDG
  double valor_minidst_enu_true     = -1.; // true neutrino energy, in GeV
  double valor_minidst_Q2_true      = -1.; // true neutrino energy, in GeV
  double valor_minidst_enu_reco     = -1.; // reco neutrino energy, in GeV
  double valor_minidst_q0_reco      = -1.; // reco lepton energy, in GeV // kinetic energy? Not massless
  double valor_minidst_Costheta_reco = -1.; // reco cos(lepton opening angle)
  double valor_minidst_Theta_reco   = -1.; // reco lepton opening angle, in deg
  double valor_minidst_y_reco       = -1.; // inelasticity
  int    valor_minidst_npion        = -1;  // N pions in reco
  int    valor_minidst_npi0         = -1;  // N pi0 in reco
  int    valor_minidst_nproton      = -1;  // N protons in reco
  double valor_minidst_wght_pot     = -1.; // POT weight
  double valor_minidst_wght         = -1.; // misc weight
  double valor_minidst_posx_true    = -999.; // true vertex x position
  double valor_minidst_posy_true    = -999.; // true vertex y position
  double valor_minidst_posz_true    = -999.; // true vertex z position
  double valor_minidst_offaxis_true = -999.; // true offaxis angle to beam centre

  TFile fout(opt_output_name.c_str(),"recreate");
  fout.cd();

  TTree * valor_minidst =
    new TTree("valor_sbn_minidst","Mini-DST input for VALOR/SBN fit");

  valor_minidst->Branch("beam"      , &valor_minidst_beam        ,"beam/I"       );
  valor_minidst->Branch("sample"    , &valor_minidst_sample      ,"sample/I"     );
  valor_minidst->Branch("reac_mode" , &valor_minidst_reac_mode   ,"reac_mode/I"  );
  valor_minidst->Branch("reac_type" , &valor_minidst_reac_type   ,"reac_type/I"  );
  valor_minidst->Branch("init_pdg"  , &valor_minidst_init_nupdg  ,"init_pdg/I"   );
  valor_minidst->Branch("final_pdg" , &valor_minidst_final_nupdg ,"final_pdg/I"  );
  valor_minidst->Branch("baseline"  , &valor_minidst_baseline    ,"baseline/D"   );
  valor_minidst->Branch("target"    , &valor_minidst_target      ,"target/I"     );
  valor_minidst->Branch("enu_true"  , &valor_minidst_enu_true    ,"enu_true/D"   );
  valor_minidst->Branch("Q2_true"   , &valor_minidst_Q2_true     ,"q2_true/D"    );
  valor_minidst->Branch("enu_reco"  , &valor_minidst_enu_reco    ,"enu_reco/D"   );
  valor_minidst->Branch("q0_reco"   , &valor_minidst_q0_reco     ,"q0_reco/D"    );
  valor_minidst->Branch("Theta_reco", &valor_minidst_Theta_reco  ,"Theta_reco/D" );
  valor_minidst->Branch("Costheta_reco", &valor_minidst_Costheta_reco  ,"Costheta_reco/D" );
  valor_minidst->Branch("y_reco"    , &valor_minidst_y_reco      ,"y_reco/D"     );
  valor_minidst->Branch("npion"     , &valor_minidst_npion       ,"npion/I"      );
  valor_minidst->Branch("npi0"      , &valor_minidst_npi0        ,"npi0/I"       );
  valor_minidst->Branch("nproton"   , &valor_minidst_nproton     ,"nproton/I"    );
  valor_minidst->Branch("wght_pot"  , &valor_minidst_wght_pot    ,"wght_pot/D"   );
  valor_minidst->Branch("wght"      , &valor_minidst_wght        ,"wght/D"       );
  valor_minidst->Branch("caf_entry" , &fEntryNo                  ,"caf_entry/I"  );
  valor_minidst->Branch("posx_true" , &valor_minidst_posx_true   ,"posx_true/D"  );
  valor_minidst->Branch("posy_true" , &valor_minidst_posy_true   ,"posy_true/D"  );
  valor_minidst->Branch("posz_true" , &valor_minidst_posz_true   ,"posz_true/D"  );
  valor_minidst->Branch("offaxis_true", &valor_minidst_offaxis_true,"offaxis_true/D");

  Long64_t nev = recTree->GetEntries();

   //event::RecoEvent *pevent = nullptr;
   //analysis_tree->SetBranchAddress("reco_events", &pevent);
/*
  std::map<TString,variation_output_type *> variation_entries;
  std::map<TString,int>     variation_nentries;
  //~ std::map<std::string,TBranch *> variation_branches;
  // First, let's read one true event map to get the universe details
  if (!no_truth && write_universes) {
    analysis_tree->GetEntry(0);
    event::Interaction * ptruth = pevent->GetTruth();
    assert(ptruth);
    const auto & weights = ptruth->weights; // map<string,whatever>
    TObjArray variation_names;

    // Boolean for if we have already added the replacement non-res branches
    bool replacedNonRes = false;
    for (const auto & variation : weights) {
      // make a list of the variation names
      const TString & vname(variation.first);
      
      // Get the number of universes
      const size_t n_universes = variation.second.size();
     
      // If the variation is a non-resonant background parameter, add 4 branches to the tree
      if(vname.Contains("NonRes") && fix_nonres){
        if(!replacedNonRes){
          for(const TString &new_vname : nonResVariations){
            // Now translate to the new list of parameters, conversion table is here: https://github.com/VALOR-fit/VALOR-SBN/wiki/XSec-systematics-2020a
            FillVariationBranches(new_vname,n_universes,variation_names,variation_nentries,variation_entries,valor_minidst);
            replacedNonRes = true;
            VLOG("valor_sbn",pINFO) << "Adding new parameter: " << new_vname << " branches in replacement of the current non-resonant branch definitions";
          }
        }
        else continue;
      }
      // Otherwise add the branches as-named
      else{
        FillVariationBranches(vname,n_universes,variation_names,variation_nentries,variation_entries,valor_minidst);
      }
    }
    variation_names.Write("variation_names",TObject::kSingleKey);
  }
*/
  //
  // event loop
  //

  Long64_t nev_accept = 0;
  Long64_t nev_rejected_position = 0;

  std::vector<int> nev_accept_by_mode;
  for (int im = 0 ; im < valor::conv::kNReacModes; im++) {
    nev_accept_by_mode.push_back(0);
  }

  // Commented out now we only have one tree per sample. But remember if that changes!
  //~ int last_tree_number = -1; // store which number file we're in, so we can count each tree's weight once

  Int_t nFRHadrons = 0;
  Int_t nFRHadronsInSlice[kMaxNFRSlices] = {};
  Int_t fake_reco_hadron_pids[kMaxNFRHadrons] = {};
  recTree->SetBranchAddress( "rec.fake_reco.hadrons..totarraysize", &nFRHadrons );
  recTree->SetBranchAddress( "rec.fake_reco.hadrons..length", nFRHadronsInSlice );
  recTree->SetBranchAddress( "rec.fake_reco.hadrons.pid", fake_reco_hadron_pids );

  Int_t nFakeRecoSlices = 0;
  recTree->SetBranchAddress( "rec.fake_reco..length", &nFakeRecoSlices );
  Float_t fake_reco_energies[kMaxNFRSlices] = {};
  Float_t fake_reco_KEs     [kMaxNFRSlices] = {};
  Float_t fake_reco_cosths  [kMaxNFRSlices] = {};
  Float_t fake_reco_weights [kMaxNFRSlices] = {};
  Int_t   fake_reco_lep_pids[kMaxNFRSlices] = {};
  recTree->SetBranchAddress( "rec.fake_reco.nuE",          fake_reco_energies );
  recTree->SetBranchAddress( "rec.fake_reco.lepton.ke",    fake_reco_KEs );
  recTree->SetBranchAddress( "rec.fake_reco.lepton.costh", fake_reco_cosths );
  recTree->SetBranchAddress( "rec.fake_reco.wgt",          fake_reco_weights );
  recTree->SetBranchAddress( "rec.fake_reco.lepton.pid",   fake_reco_lep_pids );

  

  Int_t nTrueSliceInteractions = 0;
  float true_slice_interaction_baselines[kMaxNTrueInteractions] = {};
  float true_slice_interaction_energies[kMaxNTrueInteractions] = {};
  recTree->SetBranchAddress( "rec.slc..length", &nTrueSliceInteractions ); 
  recTree->SetBranchAddress( "rec.slc.truth.baseline", true_slice_interaction_baselines );
  recTree->SetBranchAddress( "rec.slc.truth.E", true_slice_interaction_energies );

  Int_t nTrueInteractions = 0;
  Char_t   true_branch_iscc    [kMaxNTrueInteractions] = {};
  Char_t   true_branch_isnc    [kMaxNTrueInteractions] = {};
  Float_t true_branch_baseline [kMaxNTrueInteractions] = {};
  Int_t    true_branch_nu_pdg  [kMaxNTrueInteractions] = {};
  Int_t  true_branch_nu_initpdg[kMaxNTrueInteractions] = {};
  Float_t true_branch_enu_true [kMaxNTrueInteractions] = {};
  Float_t true_branch_Q2s      [kMaxNTrueInteractions] = {};
  Short_t  true_branch_larmode [kMaxNTrueInteractions] = {};
  Float_t  true_branch_posx    [kMaxNTrueInteractions] = {};
  Float_t  true_branch_posy    [kMaxNTrueInteractions] = {};
  Float_t  true_branch_posz    [kMaxNTrueInteractions] = {};
  //Short_t  true_branch_larint  [kMaxNTrueInteractions] = {};

  recTree->SetBranchAddress( "rec.mc.nu..length",      &nTrueInteractions );
  recTree->SetBranchAddress( "rec.mc.nu.iscc",          true_branch_iscc );
  recTree->SetBranchAddress( "rec.mc.nu.isnc",          true_branch_isnc );
  recTree->SetBranchAddress( "rec.mc.nu.baseline",      true_branch_baseline );
  recTree->SetBranchAddress( "rec.mc.nu.pdg",           true_branch_nu_pdg );
  recTree->SetBranchAddress( "rec.mc.nu.initpdg",       true_branch_nu_initpdg );
  recTree->SetBranchAddress( "rec.mc.nu.E",             true_branch_enu_true );
  recTree->SetBranchAddress( "rec.mc.nu.Q2",            true_branch_Q2s );
  recTree->SetBranchAddress( "rec.mc.nu.genie_mode",    true_branch_larmode );
  recTree->SetBranchAddress( "rec.mc.nu.position.x",         true_branch_posx );
  recTree->SetBranchAddress( "rec.mc.nu.position.y",         true_branch_posy );
  recTree->SetBranchAddress( "rec.mc.nu.position.z",         true_branch_posz );

  // These branches contain the primary daughters per interaction.
  // According to SRTrueInteraction.h the lepton comes first.
  // These are the post-FSI final state particles
  // These would correspond closer to a Sample_t

  Int_t   true_branch_nFSParticles = 0;
  Int_t   true_branch_nFSParticlesInInteraction[kMaxNTrueInteractions] = {};
  Short_t true_branch_FSParticle_StatusCodes   [kMaxNFSParticles]      = {};
  Int_t   true_branch_FSParticle_PDGs          [kMaxNFSParticles]      = {};

  recTree->SetBranchAddress( "rec.mc.nu.prim..totarraysize", &true_branch_nFSParticles       );
  recTree->SetBranchAddress( "rec.mc.nu.prim..length", true_branch_nFSParticlesInInteraction );
  recTree->SetBranchAddress( "rec.mc.nu.prim.gstatus", true_branch_FSParticle_StatusCodes    );
  recTree->SetBranchAddress( "rec.mc.nu.prim.pdg",     true_branch_FSParticle_PDGs           );

  // The recTree doesn't save the full particle stack. The gTree does!
  
  Int_t    evtrec_branch_nStackParticles = 0;
  Int_t    evtrec_branch_stack_StatusCodes [kMaxNStackParticles]   = {};
  Int_t    evtrec_branch_stack_PDGs        [kMaxNStackParticles]   = {};
  //Double_t evtrec_branch_stack_P4s         [4*kMaxNStackParticles] = {};
  if(!dummy_mode){
    gTree->SetBranchAddress( "GenieEvtRec.StdHepN",     &evtrec_branch_nStackParticles   );
    gTree->SetBranchAddress( "GenieEvtRec.StdHepStatus", evtrec_branch_stack_StatusCodes );
    gTree->SetBranchAddress( "GenieEvtRec.StdHepPdg",    evtrec_branch_stack_PDGs        );
    //gTree->SetBranchAddress( "GenieEvtRec.StdHepP4",     evtrec_branch_stack_P4s         );
  }
  
  int irec = 0; // to keep track of which GENIE interaction we're looking at.
  // Each interaction makes one slice in a subrun. This variable will point to the index of
  // the first interaction corresponding to vector of true interactions, for this entry in recTree.

  for(Long64_t iev = 0; iev < nev; iev++) {

    fEntryNo = iev;
    std::fill_n( true_slice_interaction_baselines, kMaxNTrueInteractions,
		 std::numeric_limits<float>::quiet_NaN() );
    std::fill_n( true_slice_interaction_energies, kMaxNTrueInteractions,
		 std::numeric_limits<float>::quiet_NaN() );

    int irec_static = irec;
    recTree->GetEntry(iev);
    // Irrespective of if we kept the event or not, we move forward the interaction index
    // Do it here, before the event gets processed
    irec += nTrueInteractions;

    if (gPrintEveryNEvents && !(iev%gPrintEveryNEvents)) {
      VLOG("valor_sbn", pNOTICE) << "** Reading event: " << iev
        <<" - so far accepted " << nev_accept;
    }
    else {
      VLOG("valor_sbn", pDEBUG) << "** Reading event: " << iev
        <<" - so far accepted " << nev_accept;
    }
    /*
    // reset the systematic universes
    if (!no_truth && write_universes) {
      for (const auto & entry : variation_entries) {
        variation_output_type * arr = entry.second;
        for (int ii = 0 ; ii < max_n_universes ; ii++) {
          arr[ii] = static_cast<variation_output_type>(conv::kBadResult);
        }
      }
      for (auto & entry : variation_nentries) {
        int & nentries = entry.second;
        nentries = -1;
      }
    } // Variations
    */
    double enu_reco    =  -999.;
    double q0_reco     =  -999.;
    double Costheta_reco = -999.;
    double Theta_reco  =  -999.;
    double reco_weight = 1.;

    int    npion_reco   = 0;
    int    npi0_reco    = 0;
    int    nproton_reco = 0;

/*
    // Before we do anything, make sure the current event fits the description of the sample
    if(!CheckSample(reco,is_numu,sample,other_sample)){
      VLOG("valor_sbn",pINFO)   << "Current event has \n" 
                               << reco.npion << " pions, \n " 
                               << reco.npi0 << " pi0s and \n " 
                               << reco.nproton << " protons and does not match the desired sample type: " 
                               << util::AsString(sample) << "\n Skipping.";
      continue;
    }
*/

    // If there is truth in the file, access the variables
    if(!no_truth){
      int iscc           = false;
      int isnc           = false;
      int nu_pdg         = -1;
      int init_pdg       = -1;
      int nuc_pdg        = -1; // PDG of the struck nucleon
      double baseline    = -999.;
      double enu_true    = -999.;
      double Q2s         = -999.;
      double posx_true   = -999.;
      double posy_true   = -999.;
      double posz_true   = -999.;
      double offaxis_true= -999.;

      int nipip    = 0;
      int nipim    = 0;
      int nipi0    = 0;
      int nikp     = 0; 
      int nikm     = 0; 
      int nik0     = 0; 
      int niak0    = 0; 
      int nin      = 0;
      int nian     = 0; 
      int nip      = 0;
      int niap     = 0; 
      int niem     = 0; 
      int niep     = 0; 
      int ninu     = 0; 
      int nimu     = 0; 
      int nimup    = 0; 
      int nig      = 0; 
      int niother  = 0; 
      int ninuc    = 0; 

      int larsoft_mode = -1;
/*
      if(ptruth==nullptr) {
        VLOG("valor_sbn", pNOTICE)
          << "The number of truth entries is 0, skipping event "<<iev;
        continue;
      }
*/
      // Ask the SRSlice which interaction we should look at...
      // As of sbndcode v9_93_01_01 (sbnanaobj 09_23_02_01) baseline is filled with nan if not good
      // There is possibly > 1 interaction that matches the slice information. Keep these in vecs.

      //double matched_baseline = -1.0; double matched_energy = -1.0;
      std::vector<double> matched_baselines, matched_energies;
      std::vector<int> matching_indices;
      for( int isl = 0; isl < nTrueSliceInteractions; isl++ ) {
	VLOG( "valor_sbn", pDEBUG )
	 << "read baseline " << true_slice_interaction_baselines[isl];

	if( ! std::isnan( true_slice_interaction_baselines[isl] ) ) {
	  matching_indices.emplace_back( isl );
	  matched_baselines.emplace_back( true_slice_interaction_baselines[isl] );
	  matched_energies.emplace_back( true_slice_interaction_energies[isl] );

	  VLOG("valor_sbn", pDEBUG) 
	    << "I am making a candidate from element " << isl << ", with baseline "
	    << true_slice_interaction_baselines[isl] << " and energy "
	    << true_slice_interaction_energies[isl];
	}
      }

      // Reject event, if no match
      if( matching_indices.size() == 0 ) {
	VLOG("valor_sbn", pINFO) << "- Rejecting event [no match between true slice and interactions] "<<iev;
	continue;
      }

      // Construct a vector of pairs -- (slc.truth, mc.nu) indices. 
      // Normally this will have size 1, but it could have size > 1
      // In the latter case, we'll ask fake_reco for its Enu and pick the closest truth value
      std::vector< std::pair<int, int> > matched_pairs;

      // Find the interaction with that baseline and energy
      // don't make a match if the interaction is taken
      std::vector<int> used_true_interactions;
      for( int i = 0; i < nTrueInteractions; i++ ) {
	iscc     = true_branch_iscc[i];
	isnc     = true_branch_isnc[i];
	baseline = true_branch_baseline[i];
	nu_pdg   = true_branch_nu_pdg[i];
	enu_true = true_branch_enu_true[i];
	Q2s      = true_branch_Q2s[i];
	larsoft_mode = true_branch_larmode[i];
	posx_true = static_cast<double>(true_branch_posx[i]/100.);
	posy_true = static_cast<double>(true_branch_posy[i]/100.);
	posz_true = static_cast<double>(true_branch_posz[i]/100.);
	//larsoft_inttype = true_branch_larint[i];

        //Calculate the off angle position
        double beamx = 0.7378; //read this from somewhere sensible! this is for v9 updated geometry in m not cm
        double beamy = 0.0;
        double exp_baseline = 110.0; //m
        double offaxis_true_m = sqrt( (posx_true-beamx)*(posx_true-beamx) + (posy_true-beamy)*(posy_true-beamy));
        offaxis_true = atan(offaxis_true_m/exp_baseline) * (180/M_PI);	

	VLOG("valor_sbn", pDEBUG)  << "true baseline at " << i
				   << " = " << baseline << ", energy = " << enu_true;
	

	for( int isl = 0; isl < matched_baselines.size(); isl++ ) {
	  if( matched_baselines.at(isl) == baseline && matched_energies.at(isl) == enu_true
	      && std::find(used_true_interactions.begin(), used_true_interactions.end(), i) ==
	      used_true_interactions.end() ) {
	    matched_pairs.push_back( std::pair<int, int>( matching_indices.at(isl), i ) );
	    used_true_interactions.emplace_back(i);
	  }
	} // loop over slice truth
      } // loop over interaction truth

      /*
      VLOG("valor_sbn", pDEBUG) << "There are " << matched_pairs.size()
				<< " pairs between slc and mc";
      for( int im = 0; im < matched_pairs.size(); im++ ) {
	VLOG("valor_sbn", pDEBUG) << "the " << im << "th pair is (slc, nu) = ("
				  << matched_pairs.at(im).first << ", "
				  << matched_pairs.at(im).second << ")";
      }
      */

      // Find the way to do optimal matching between fake reco and truth pairs.
      // Get all the possible combinations, and find the minimum \sum(|FR - truth|)
      //VLOG("valor_sbn", pDEBUG) << "There are " << nFakeRecoSlices << " fake reco slices and " << matched_pairs.size() << " truth pairs";

      // Reject the event if no fake_reco slices
      if( nFakeRecoSlices == 0 ) {
	VLOG( "valor_sbn", pINFO ) << "- Rejecting event [no fake reco] " << iev;
	continue;
      }
      
      std::vector<std::pair<int, int>> best_combo;
      double best_badness = 99999.9;
      // First, construct all the possible ways we can match FR indices to matched-truth indices
      std::vector<std::vector<std::pair<int, int>>> index_matches;
      std::vector<int> fr_copied_idcs, mat_copied_idcs;
      for( int ifr = 0; ifr < nFakeRecoSlices; ifr++ ) fr_copied_idcs.emplace_back(ifr);
      for( int im = 0; im < matched_pairs.size(); im++  ) mat_copied_idcs.emplace_back(im);
      ConstructRecursion( fr_copied_idcs, mat_copied_idcs, index_matches );

      //VLOG( "valor_sbn", pDEBUG ) << "index_matches has " << index_matches.size() << " elements";
      for( typename std::vector<std::vector<std::pair<int, int>>>::iterator it_prm = index_matches.begin() ;
	   it_prm != index_matches.end() ; ++it_prm ) {

	// The elements of this vec-of-vecs are all the combinations of this universe
	// A combination is a pair of FR index with matched-truth index
	// So the slice truth is matched_pairs.at(matched-truth index).first
	// and the mc interaction truth is matched_pairs.at(matched-truth index).second

	/*
	std::ostringstream asts, bsts, csts;
	asts << "Outputting element at index " << it_prm - index_matches.begin() << "\n";
	bsts << "This corresponds to the following matches:\n";
	csts << "And the following energies:\n";
	*/
	double curr_badness = 0;
	for( typename std::vector<std::pair<int, int>>::iterator it_elm = (*it_prm).begin(); 
	     it_elm != (*it_prm).end(); ++it_elm ) {
	  int FR_index    = (*it_elm).first;
	  int match_index = (*it_elm).second;
	  int slc_index   = matched_pairs.at(match_index).first;
	  int mc_nu_index = matched_pairs.at(match_index).second;

	  double FR_enu  = fake_reco_energies[FR_index];
	  double slc_enu = true_slice_interaction_energies[slc_index];
	  double mcv_enu = true_branch_enu_true[mc_nu_index];

	  curr_badness += std::abs(slc_enu - FR_enu);

	  /*
	  asts << "( " << (*it_elm).first << ", " << (*it_elm).second << " )";
	  bsts << "( " << FR_index << ", (" << slc_index << ", " << mc_nu_index
	       << ") )";
	  csts << "( " << Form("%4.3f", FR_enu) << ", (" << Form("%4.3f", slc_enu)
	       << ", " << Form("%4.3f", mcv_enu) << ") )";
	  */
	}
	/*
	VLOG("valor_sbn", pDEBUG) << asts.str();
	VLOG("valor_sbn", pDEBUG) << bsts.str();
	VLOG("valor_sbn", pDEBUG) << csts.str();
	*/

	if( curr_badness < best_badness ) {
	  best_combo = *it_prm;
	  best_badness = curr_badness;
	}
      } 

      // We now have a vector of interactions. We must calll Fill() on the DST that many times.
      std::ostringstream wsts;
      wsts << "Winning combo (badness " << best_badness << "):";

      int curr_position_of_hadron_array = 0;
      for( std::vector<std::pair<int, int>>::iterator it_elm = best_combo.begin();
	   it_elm != best_combo.end(); ++it_elm ) {
	int FR_index    = (*it_elm).first;
	int match_index = (*it_elm).second;
	int slc_index   = matched_pairs.at(match_index).first;
	int mcv_index   = matched_pairs.at(match_index).second;
	int current_interaction_index = irec_static + mcv_index;

	wsts << "\nElement " << it_elm - best_combo.begin() << ": "
	     << "indices " << (*it_elm).first << ", " << (*it_elm).second
	     << " - energies " << fake_reco_energies[FR_index] << ", " << true_slice_interaction_energies[slc_index];

	// Set the true variables
	iscc         = true_branch_iscc[mcv_index];
	isnc         = true_branch_isnc[mcv_index];
	baseline     = true_branch_baseline[mcv_index];
	nu_pdg       = true_branch_nu_pdg[mcv_index];
	enu_true     = true_branch_enu_true[mcv_index];
	Q2s          = true_branch_Q2s[mcv_index];
	larsoft_mode = true_branch_larmode[mcv_index];
	posx_true    = static_cast<double>(true_branch_posx[mcv_index]/100.);
	posy_true    = static_cast<double>(true_branch_posy[mcv_index]/100.);
	posz_true    = static_cast<double>(true_branch_posz[mcv_index]/100.);
	//larsoft_inttype = true_branch_larint[mcv_index];

        if(posx_true < -2 || posx_true > 2 || posy_true < -2 || posy_true > 2){
            VLOG("valor_sbn", pINFO) << "- Rejecting event as position out of range " << iev;
	    nev_rejected_position++;
            continue;
	}

        //Calculate the off angle position
        double beamx = 0.7378; //read this from somewhere sensible! this is for v9 updated geometry but in m
        double beamy = 0.0;
        double exp_baseline = 110.0;
        double offaxis_true_m = sqrt( (posx_true-beamx)*(posx_true-beamx) + (posy_true-beamy)*(posy_true-beamy));
        offaxis_true = atan(offaxis_true_m/exp_baseline) * (180/M_PI);	

	// Load the true interaction from the GENIE event record
	if(!dummy_mode) gTree->GetEntry(current_interaction_index);

	/*
	VLOG("valor_sbn", pDEBUG) << "WOLOLINT - My current interaction idx = " 
				  << current_interaction_index << ", and the true energy is "
				  << evtrec_branch_stack_P4s[3] << " GeV (cf. "
				  << enu_true << " GeV)";
	*/
	
	std::ostringstream lsts;
	lsts << "The larsoft mode int is " << larsoft_mode << ", which is ";
	switch( larsoft_mode ) {
	case kLArUnknownInteraction: lsts << "kLArUnknownInteraction"; break;
	case kLArQE: lsts << "kLArQE"; break;
	case kLArRes: lsts << "kLArRes"; break;
	case kLArDIS: lsts << "kLArDIS"; break;
	case kLArCoh: lsts << "kLArCoh"; break;
	case kLArCohElastic: lsts << "kLArCohElastic"; break;
	case kLArElectronScattering: lsts << "kLArElectronScattering"; break;
	case kLArIMDAnnihilation: lsts << "kLArIMDAnnihilation"; break;
	case kLArInverseBetaDecay: lsts << "kLArInverseBetaDecay"; break;
	case kLArGlashowResonance: lsts << "kLArGlashowResonance"; break;
	case kLArAMNuGamma: lsts << "kLArAMNuGamma"; break;
	case kLArMEC: lsts << "kLArMEC"; break;
	case kLArDiffractive: lsts << "kLArDiffractive"; break;
	case kLArEM: lsts << "kLArEM"; break;
	case kLArWeakMix: lsts << "kLArWeakMix"; break;
	default: lsts << "NONE"; break;
	}
	
	// Set the reco variables
	enu_reco  = fake_reco_energies[FR_index];
	double lepton_ke_reco = fake_reco_KEs[FR_index];
	// q0 is a misnomer - the branch actually wants final-state lepton energy. Right
	// RETHERE: If we wanted a sterile neutrino at some mass... We'd need more cases. And masses.
	int    lepton_pid_reco = fake_reco_lep_pids[FR_index];
	double lepton_m_reco = 0.0;
	if( std::abs(lepton_pid_reco) == 11 ) lepton_m_reco = 0.000511;
	else if( std::abs(lepton_pid_reco) == 13 ) lepton_m_reco = 0.10566;
	q0_reco = lepton_ke_reco + lepton_m_reco;
	Costheta_reco = fake_reco_cosths[FR_index];
	Theta_reco = std::acos(Costheta_reco) * 180.0 / M_PI;
	reco_weight = fake_reco_weights[FR_index];

	// And setup the hadrons...
	nproton_reco = 0; npion_reco = 0; npi0_reco = 0;
	std::vector<int> FR_hadrons_in_slice;
	for( int ifrh = curr_position_of_hadron_array ; 
	     ifrh < curr_position_of_hadron_array + nFRHadronsInSlice[FR_index] ; 
	     ifrh++ ) {
	  FR_hadrons_in_slice.emplace_back( fake_reco_hadron_pids[ifrh] );
	}
	
	for( std::vector<int>::iterator it_frh = FR_hadrons_in_slice.begin();
	     it_frh != FR_hadrons_in_slice.end(); ++it_frh ) {
	  VLOG( "valor_sbn", pINFO ) << "Reading fake reco hadron (indexed in slice as "
				     << it_frh - FR_hadrons_in_slice.begin()
				     << " and globally as "
				     << it_frh - FR_hadrons_in_slice.begin() + curr_position_of_hadron_array
				     << ") with PID: " << *it_frh;
	  
	  switch( *it_frh ) {
	  case 2212: nproton_reco++; break;
	  case  211:
	  case -211: npion_reco++;   break;
	  case  111: npi0_reco++;    break;
	  }
	}
	curr_position_of_hadron_array += nFRHadronsInSlice[FR_index];

	VLOG("valor_sbn",pDEBUG) << "Read slice in event: "
				 << "\n Ereco             = "<< enu_reco  << " GeV; "
				 << "\n Reco lepton E     = "<< q0_reco  << " GeV; "
				 << "\n Reco cos(lepton angle) = "<< Costheta_reco << " ;"
				 << "\n N reco pions = " << npion_reco << "; "
				 << "N reco pi0 = " << npi0_reco << "; "
				 << "N reco protons = " << nproton_reco;
	conv::ReacMode_t  reac_mode;
	conv::ReacType_t reac;
	conv::NuFlavour_t final_flav;
	conv::NuFlavour_t init_flav;
	if(!dummy_mode){
	  // Setup complete. We must now construct modes, fill trees.
	  
	  VLOG("valor_sbn", pDEBUG) << "Slice " << it_elm - best_combo.begin() << " of "
				    << best_combo.size()-1 << ":\t"
				    << "iscc: " << iscc 
				    << "\tEnu_true: " << enu_true
				    << "\tbaseline: " << baseline;

	  // Count intrinsic interaction daughters to obtain the reaction mode

	  bool nucleonPDGSet = false;
	  for( unsigned int p = 0; p < evtrec_branch_nStackParticles; p++ ) {
	    if(status_code_set) {
	      if( evtrec_branch_stack_StatusCodes[p] == 11 ) {
		
		if(nucleonPDGSet) {
		  VLOG("valor_sbn",pNOTICE) << "\nIn interaction " << current_interaction_index
					    << "\nThe struck nucleon pdg has already been set as: " 
					    << nuc_pdg << ", will take the first answer."
					    << "\nThis nucleon has pdg: " 
					    << evtrec_branch_stack_PDGs[p];
		} else{
		  VLOG("valor_sbn",pINFO) << "\nIn interaction " << current_interaction_index
					  << "\nThe struck nucleon has pdg: " 
					  << evtrec_branch_stack_PDGs[p];
		  nuc_pdg = evtrec_branch_stack_PDGs[p];
		  nucleonPDGSet = true;
		}
	      } // if(stable final state particle)
	    } // if(status_code_set)

	    // Make sure we are counting initial states for the interaction definition
	    // See $GENIE/src/GHEP/GHepStatus.h for the enumeration

	    if (status_code_set && 
		evtrec_branch_stack_StatusCodes[p] != genie::kIStHadronInTheNucleus && 
		evtrec_branch_stack_StatusCodes[p] != genie::kIStDISPreFragmHadronicState) {continue;}
	    if     (evtrec_branch_stack_PDGs[p] == genie::kPdgProton      ) nip++;
	    else if(evtrec_branch_stack_PDGs[p] == genie::kPdgAntiProton  ) niap++;
	    else if(evtrec_branch_stack_PDGs[p] == genie::kPdgNeutron     ) nin++;
	    else if(evtrec_branch_stack_PDGs[p] == genie::kPdgAntiNeutron ) nian++;
	    else if(evtrec_branch_stack_PDGs[p] == genie::kPdgPiP         ) nipip++;
	    else if(evtrec_branch_stack_PDGs[p] == genie::kPdgPiM         ) nipim++;
	    else if(evtrec_branch_stack_PDGs[p] == genie::kPdgPi0         ) nipi0++;
	    else if(evtrec_branch_stack_PDGs[p] == genie::kPdgKP          ) nikp++;
	    else if(evtrec_branch_stack_PDGs[p] == genie::kPdgKM          ) nikm++;
	    else if(evtrec_branch_stack_PDGs[p] == genie::kPdgK0          ) nik0++;
	    else if(evtrec_branch_stack_PDGs[p] == genie::kPdgAntiK0      ) niak0++;
	    else if(evtrec_branch_stack_PDGs[p] == genie::kPdgGamma       ) nig++;
	    else if(evtrec_branch_stack_PDGs[p] == genie::kPdgElectron    ) niem++;
	    else if(evtrec_branch_stack_PDGs[p] == genie::kPdgPositron    ) niep++;
	    else if(evtrec_branch_stack_PDGs[p] == genie::kPdgMuon        ) nimu++;
	    else if(evtrec_branch_stack_PDGs[p] == genie::kPdgAntiMuon    ) nimup++;
	    else if(evtrec_branch_stack_PDGs[p] == genie::kPdgAntiMuon    ) nimup++;
	    else if(evtrec_branch_stack_PDGs[p] == genie::kPdgNuMu || 
		    evtrec_branch_stack_PDGs[p] == genie::kPdgAntiNuMu || 
		    evtrec_branch_stack_PDGs[p] == genie::kPdgNuE || 
		    evtrec_branch_stack_PDGs[p] == genie::kPdgAntiNuE) ninu++;
	    else if(evtrec_branch_stack_PDGs[p] > 1e4) ninuc++;
	    else niother++;

	  } // loop over particles in event record

	  if((nuc_pdg > 5000 && (nuc_pdg != genie::kPdgClusterNN &&
				 nuc_pdg != genie::kPdgClusterNP &&
				 nuc_pdg != genie::kPdgClusterPP)) && 
	     (nipip+nipim+nipi0 == 1 || nipip+nipim+nipi0 == 2)){
	    VLOG("valor_sbn",pERROR) << "The number of pions in this event is: " << nipip+nipim+nipi0 << " and the struck nucleon is neither a proton nor a neutron: " << nuc_pdg;
	    util::Die(-1);
	  }

	  VLOG("valor_sbn", pDEBUG) << "I have these multiplicities from GENIE entry " 
				    << current_interaction_index << ":"
				    << "\npip, pi0, pim = " << nipip << ", " << nipi0 << ", " << nipim
				    << "\nnip, nin = " << nip << ", " << nin
				    << "\nkp, k0, km = " << nikp << ", " << nik0 << ", " << nikm;
	  
	  // Construct the reaction mode
	  reac = conv::kmtUndefined;
	  if (is_dirt){
	    reac = conv::kmtDirt; 
	    if(is_cosmic) reac = conv::kmtCosmic;
	  }   
	  else if (iscc) {
	    if      (larsoft_mode==kLArQE                ) { reac = conv::kmtCCQE;    }
	    else if (larsoft_mode==kLArMEC               ) { reac = conv::kmtCCMEC;   }
	    else if (larsoft_mode==kLArCoh               ) { reac = conv::kmtCCcoh;   }
	    else if (larsoft_mode==kLArIMDAnnihilation   ) { reac = conv::kmtCCELScat;}
	    else if (larsoft_mode==kLArElectronScattering) { reac = conv::kmtCCELScat;}

	    else { // start counting pions
	      if      (nikp || nik0 || nikm           )  { reac = conv::kmtCCoth;}
	      else if (nipip+nipim == 1 && nipi0 == 0 )  { reac = conv::kmtCC1piC;}
	      else if (nipip+nipim == 0 && nipi0 == 1 )  { reac = conv::kmtCC1pi0;}
	      else if (nipip+nipim == 2 && nipi0 == 0 )  { reac = conv::kmtCC2piC;}
	      else if (nipip+nipim == 0 && nipi0 == 2 )  { reac = conv::kmtCC2pi0;}
	      else if (nipip+nipim == 1 && nipi0 == 1 )  { reac = conv::kmtCCpiCpi0;}
	      else                                       { reac = conv::kmtCCoth;}
	    }
	  }
	  else if (isnc) {
	    if      (larsoft_mode==kLArQE                ) { reac = conv::kmtNCEL;    }
	    else if (larsoft_mode==kLArMEC               ) { reac = conv::kmtNCMEC;   }
	    else if (larsoft_mode==kLArCoh               ) { reac = conv::kmtNCcoh;   }
	    else if (larsoft_mode==kLArElectronScattering) { reac = conv::kmtNCELScat;}

	    else { // start counting pions
	      if      (nikp || nik0 || nikm          )  { reac = conv::kmtNCoth;}
	      else if (nipip+nipim == 1 && nipi0 == 0 )  { reac = conv::kmtNC1piC;}
	      else if (nipip+nipim == 0 && nipi0 == 1 )  { reac = conv::kmtNC1pi0;}
	      else if (nipip+nipim == 2 && nipi0 == 0 )  { reac = conv::kmtNC2piC;}
	      else if (nipip+nipim == 0 && nipi0 == 2 )  { reac = conv::kmtNC2pi0;}
	      else if (nipip+nipim == 1 && nipi0 == 1 )  { reac = conv::kmtNCpiCpi0;}
	      else                                       { reac = conv::kmtNCoth;}
	    }
	  }
	  else if (larsoft_mode == kLArElectronScattering) {
	    reac = conv::kmtELScat;
	  }
	
	  else if(is_cosmic) reac = conv::kmtCosmic;
	  else reac = conv::kmtOther;
      
	  final_flav = valor::util::FlavourFromPDG(nu_pdg);
	  init_flav;
	  // If we are looking at the selected nuE samples, get the initial neutrino pdg from the file
	  //init_pdg  = recTree->GetLeaf("rec.mc.nu.initpdg")->GetValue();
	  init_pdg  = true_branch_nu_initpdg[mcv_index];
	  init_flav = valor::util::FlavourFromPDG(init_pdg);

	  // Get the real valor mode - this will only be defined for modes turned on right now
	  reac_mode  = valor::util::ReacTypeToMode(reac,init_flav,final_flav);
	  // If we have any events that are in disabled modes, put them into other
	  if (reac_mode==conv::kmUndefined) {
	    if (isnc) {reac = conv::kmtNCoth;}
	    if (iscc) {reac = conv::kmtCCoth;}
	    reac_mode  = valor::util::ReacTypeToMode(reac,init_flav,final_flav);
	  }
	}else reac_mode = conv::kmUndefined; 

	VLOG( "valor_sbn", pDEBUG )
	  << "Here is my reac_mode int: " << static_cast<int>(reac_mode)
	  << ". Its string is " << util::AsString(reac_mode);

	if(!opt_disable_checks) {
	  //
	  // ignore events that can not be used in the VALOR analysis
	  //
	  if(reac_mode == conv::kmUndefined) {
	    VLOG("valor_sbn", pINFO) << "- Rejecting event [bad mode] "<<iev;
	    VLOG("valor_sbn", pNOTICE)
	      <<"\n larsoft_mode = "<<larsoft_mode
	      <<"\n baseline = "<< baseline << " m"
	      <<"\n iscc="<<iscc<<" and isnc="<<isnc
	      <<"\n initpdg="<<init_pdg<<" and finalpdg="<<nu_pdg
	      <<"\n valor reaction="<<reac<<" which is "<<util::AsString(reac);
	    continue;
	  }
	  if(isnc && init_flav != final_flav){
	    VLOG("valor_sbn", pINFO) << "- Rejecting event [oscillated nc] "<<iev;
	    VLOG("valor_sbn", pINFO)
	      <<"\n larsoft_mode = "<<larsoft_mode
	      <<"\n baseline = "<< baseline << " m"
	      <<"\n iscc="<<iscc<<" and isnc="<<isnc
	      <<"\n initpdg="<<init_pdg<<" and finalpdg="<<nu_pdg
	      <<"\n valor mode="<<reac_mode<<" which is "<<util::AsString(reac_mode);
	    continue;
	  }
	  if(is_nue && (init_pdg == 12 || init_pdg == -12) && (!is_nueint)){
	    VLOG("valor_sbn", pINFO) << "- Rejecting event [nue not from intrinsic] "<<iev;
	    VLOG("valor_sbn", pINFO)
	      <<"\n is_nueint = "<<is_nueint
	      <<"\n larsoft_mode = "<<larsoft_mode
	      <<"\n baseline = "<< baseline << " m"
	      <<"\n iscc="<<iscc<<" and isnc="<<isnc
	      <<"\n initpdg="<<init_pdg<<" and finalpdg="<<nu_pdg
	      <<"\n valor mode="<<reac_mode<<" which is "<<util::AsString(reac_mode);
	    continue;
	  }
	  if(is_nueosc && init_flav == final_flav){
	    VLOG("valor_sbn", pINFO) << "- Rejecting event [non-oscillated event in oscillated file] "<<iev;
	    VLOG("valor_sbn", pINFO)
	      <<"\n larsoft_mode = "<<larsoft_mode
	      <<"\n baseline = "<< baseline << " m"
	      <<"\n iscc="<<iscc<<" and isnc="<<isnc
	      <<"\n initpdg="<<init_pdg<<" and finalpdg="<<nu_pdg
	      <<"\n valor mode="<<reac_mode<<" which is "<<util::AsString(reac_mode);
	    continue;
	  }
	  if(is_numu && init_flav != final_flav){
	    VLOG("valor_sbn", pINFO) << "- Rejecting event [oscillated event in non-oscillated file] "<<iev;
	    VLOG("valor_sbn", pINFO)
	      <<"\n larsoft_mode = "<<larsoft_mode
	      <<"\n baseline = "<< baseline << " m"
	      <<"\n iscc="<<iscc<<" and isnc="<<isnc
	      <<"\n initpdg="<<init_pdg<<" and finalpdg="<<nu_pdg
	      <<"\n valor mode="<<reac_mode<<" which is "<<util::AsString(reac_mode);
	    continue;
	  }
	  if(nue_disappearance && is_nueosc){
	    VLOG("valor_sbn", pINFO) << "- Rejecting event [appearance oscillated event in nue disappearance template construction] "<<iev;
	    VLOG("valor_sbn", pINFO)
	      <<"\n larsoft_mode = "<<larsoft_mode
	      <<"\n baseline = "<< baseline << " m"
	      <<"\n iscc="<<iscc<<" and isnc="<<isnc
	      <<"\n initpdg="<<init_pdg<<" and finalpdg="<<nu_pdg
	      <<"\n valor mode="<<reac_mode<<" which is "<<util::AsString(reac_mode);
	    continue;

	  }
	}

	VLOG("valor_sbn",pDEBUG) << "Read event: "
				 << "Etrue         = "<< enu_true  << " GeV; "
				 << "LArSoft mode  = "<< larsoft_mode  << "; ";
	valor_minidst_reac_mode  = reac_mode;
	valor_minidst_enu_true   = enu_true;
	valor_minidst_baseline   = baseline/1000.; // why in km?
	valor_minidst_Q2_true    = Q2s;
	valor_minidst_reac_type    = reac;
	valor_minidst_init_nupdg   = init_pdg;
	valor_minidst_final_nupdg  = nu_pdg;
	valor_minidst_target       = 1000180400; // Argon40
	valor_minidst_posx_true    = posx_true;
	valor_minidst_posy_true    = posy_true;
	valor_minidst_posz_true    = posz_true;
	valor_minidst_offaxis_true = offaxis_true;
	/*
	// Copy the systematic universes across
	if (write_universes) {
        // Sort out the NonRes parameters
        for (const auto & entry : truth.weights) {
	TString vname = entry.first;
	TString input_vname(vname);
	if(!vname.Contains("NonRes") || !fix_nonres) continue;
	VLOG("valor_sbn",pINFO) << " Current input parameter: " << vname;

	const auto & in_vec = entry.second;
	const int nentries = in_vec.size();
	assert(nentries<=max_n_universes);

	// If we are looking at a CC event and an Alt paramater, set all the NC NonRes param entries to be 1
	// Vice-versa for NC !Alt
	if((iscc && input_vname.Contains("Alt")) || (!iscc && !input_vname.Contains("Alt"))){
	for(const TString &new_vname : nonResVariations){
	if((iscc && new_vname.Contains("CC")) || (!iscc && new_vname.Contains("NC"))) continue;
	VLOG("valor_sbn",pINFO) << " Setting all NC parameter entries to be 1.0 in a CC event and vice versa";
	for (size_t ii = 0 ; ii < in_vec.size() ; ii++) {
	variation_entries[new_vname][ii] = 1.f;
	}
	variation_nentries[new_vname] = nentries;
	}
	}
	else{ 
	// Get the corresponding variation name if possible
	// Get also the pair of variations this parameter should be split into
	std::pair<TString,TString> new_vnames;
	GetPair(vname,new_vnames);
	std::cout << vname << std::endl;
	std::cout << nuc_pdg << std::endl;
	// std::cin.get();
	GetCorrectVariationName(nuc_pdg, iscc, vname);
	if(vname != ""){
	if(vname != new_vnames.first && vname != new_vnames.second){
	VLOG("valor_sbn",pERROR) << "Associated parameter name does not match one of the expected names:" 
	<< "\n Parameter : " << vname 
	<< "\n Expected names: " << new_vnames.first << ", " << new_vnames.second;
	util::Die(-1);
	}
	// Now get the other name from the pair
	TString other_name = (vname == new_vnames.first) ? new_vnames.second : new_vnames.first;
	for (size_t ii = 0 ; ii < in_vec.size() ; ii++) {
	VLOG("valor_sbn",pINFO) << " New parameter: " << vname << ", other parameter option: " << other_name << " (setting entries to 1.f)";
	// Set the second element of the pair to be 1.f
	variation_entries[other_name][ii] = 1.f;

	// Set the matched name properly
	variation_output_type val = static_cast<variation_output_type>(in_vec[ii]);
	variation_entries[vname][ii] = val;
	}
	variation_nentries[vname] = nentries;
	variation_nentries[other_name] = nentries;
	}
	// Otherwise, get the two parameters it should be split into and set the entries to be 1.0 for this event
	else{
	for (size_t ii = 0 ; ii < in_vec.size() ; ii++) {
	if(abs(in_vec.at(ii)-1)>std::numeric_limits<float>::epsilon()){
	VLOG("valor_sbn",pERROR) << " Setting alternate parameters for " << input_vname << " to be 1 when this parameter isn't always 1, this value: " << in_vec.at(ii);
	util::Die(-1);
	}
	variation_entries[new_vnames.first][ii]  = 1.f;
	variation_entries[new_vnames.second][ii] = 1.f;
	}
	variation_nentries[new_vnames.first]  = nentries;
	variation_nentries[new_vnames.second] = nentries;
	}
	}
        }

        // For the rest of the parameters, copy the input values to the ouput TTree
        for (const auto & entry : truth.weights) {
	TString vname = entry.first;
	if(vname.Contains("NonRes") && fix_nonres) continue;

	const auto & in_vec = entry.second;
	const int nentries = in_vec.size();
	assert(nentries<=max_n_universes);

	// Now fill the branch
	for (size_t ii = 0 ; ii < in_vec.size() ; ii++) {
	variation_output_type val = static_cast<variation_output_type>(in_vec[ii]);
	variation_output_type & destination = variation_entries[vname][ii];
	if (val < 0.0) {
	VLOG("valor_sbn",pINFO) << "Setting negative event weight to zero: "
	<<vname<<"\tEvent="<<iev<<" ; Universe="<<ii
	<<" ; wght = "<<std::scientific << std::setprecision(6)<<val;
	val = 0.0;
	}
	destination = val;
	}
	variation_nentries[vname] = nentries;
        }
	}*/
	//}// !no-truth
      
	// If we are finding everything 'other' than the sample defined, label the DST sample 'other'
	if(other_sample) valor_minidst_sample = GetOtherSample(sample,is_numu);
	else             valor_minidst_sample = sample;

	valor_minidst_beam       = beam;
	valor_minidst_wght_pot   = 1./mcsample_pot;
	//valor_minidst_y_reco    = 0.5; // FORCE y=0.5 for now

	VLOG("valor_sbn", pINFO)
	  << "\n Information copied to VALOR/SBN Mini-DST: "
	  << "\n Beam          = " << valor_minidst_beam
	  << "\n Sample        = " << valor_minidst_sample
	  << "\n Reaction mode = " << valor_minidst_reac_mode
	  << "\n Target        = " << valor_minidst_target
	  << "\n Baseline      = " << valor_minidst_baseline << " km"
	  << "\n Q2 (true)     = " << valor_minidst_Q2_true << " GeV^2"
	  << "\n Ev (true)     = " << valor_minidst_enu_true << " GeV"
	  << "\n y (reco)      = " << valor_minidst_y_reco
	  << "\n POT weight    = " << valor_minidst_wght_pot
	  << "\n posx (true)   = " << valor_minidst_posx_true << " cm"
	  << "\n posy (true)   = " << valor_minidst_posy_true << " cm"
	  << "\n posz (true)   = " << valor_minidst_posz_true << " cm"
	  << "\n offaxis (true)= " << valor_minidst_offaxis_true << " deg";

	if(!opt_disable_checks) {

	  //
	  // ignore events that can not be used in the VALOR analysis
	  //
	  if(enu_reco <= 0) {
	    VLOG("valor_sbn", pINFO) << "- Rejecting event [Ev (reco) <= 0]: "<<enu_reco;
	    continue;
	  }
	}

	VLOG("valor_sbn", pINFO) << "+ Accepting event";

	valor_minidst_enu_reco    = enu_reco;
	valor_minidst_q0_reco     = q0_reco;
	valor_minidst_Costheta_reco  = Costheta_reco;
	valor_minidst_Theta_reco  = Theta_reco;
	valor_minidst_npion       = npion_reco;
	valor_minidst_npi0        = npi0_reco;
	valor_minidst_nproton     = nproton_reco;
	if(apply_weights)
	  valor_minidst_wght = reco_weight;
	else
	  valor_minidst_wght = 1.;
    

	valor_minidst->Fill();
      
	nev_accept += 1;
	if(!no_truth)
	  nev_accept_by_mode[valor_minidst_reac_mode] += 1;
	
      } // loop over the elements of the best FR <--> truth combo
      VLOG("valor_sbn", pDEBUG) << wsts.str();

    } //if( ! no_truth )

    else { // no truth so just fill in fake reco
      // just fill in one entry for each slice
      int curr_position_of_hadron_array = 0;
      for( int ifr = 0; ifr < nFakeRecoSlices; ifr++ ) {
	
	double enu_reco    =  -999.;
	double q0_reco     =  -999.;
	double Costheta_reco = -999.;
	double Theta_reco  =  -999.;
	double reco_weight = 1.;

	int    npion_reco   = 0;
	int    npi0_reco    = 0;
	int    nproton_reco = 0;

	enu_reco = fake_reco_energies[ifr];
	double lepton_ke_reco = fake_reco_KEs[ifr];
	// q0 is a misnomer - the branch actually wants final-state lepton energy. Right
	// RETHERE: If we wanted a sterile neutrino at some mass... We'd need more cases. And masses.
	int    lepton_pid_reco = fake_reco_lep_pids[ifr];
	double lepton_m_reco = 0.0;
	if( std::abs(lepton_pid_reco) == 11 ) lepton_m_reco = 0.000511;
	else if( std::abs(lepton_pid_reco) == 13 ) lepton_m_reco = 0.10566;
	q0_reco = lepton_ke_reco + lepton_m_reco;

	Costheta_reco = fake_reco_cosths[ifr];
	Theta_reco = std::acos(Costheta_reco) * 180.0 / M_PI;
	reco_weight = fake_reco_weights[ifr];

	// And setup the hadrons...
	nproton_reco = 0; npion_reco = 0; npi0_reco = 0;
	std::vector<int> FR_hadrons_in_slice;
	for( int ifrh = curr_position_of_hadron_array ; 
	     ifrh < curr_position_of_hadron_array + nFRHadronsInSlice[ifr] ; 
	     ifrh++ ) {
	  FR_hadrons_in_slice.emplace_back( fake_reco_hadron_pids[ifrh] );
	}
	
	for( std::vector<int>::iterator it_frh = FR_hadrons_in_slice.begin();
	     it_frh != FR_hadrons_in_slice.end(); ++it_frh ) {
	  VLOG( "valor_sbn", pINFO ) << "Reading fake reco hadron (indexed in slice as "
				     << it_frh - FR_hadrons_in_slice.begin()
				     << " and globally as "
				     << it_frh - FR_hadrons_in_slice.begin() + curr_position_of_hadron_array
				     << ") with PID: " << *it_frh;
	  
	  switch( *it_frh ) {
	  case 2212: nproton_reco++; break;
	  case  211:
	  case -211: npion_reco++;   break;
	  case  111: npi0_reco++;    break;
	  }
	}
	curr_position_of_hadron_array += nFRHadronsInSlice[ifr];

	VLOG("valor_sbn",pDEBUG) << "Read slice in event: "
				 << "\n Ereco             = "<< enu_reco  << " GeV; "
				 << "\n Reco lepton E     = "<< q0_reco  << " GeV; "
				 << "\n Reco cos(lepton angle) = "<< Costheta_reco << " ;"
				 << "\n N reco pions = " << npion_reco << "; "
				 << "N reco pi0 = " << npi0_reco << "; "
				 << "N reco protons = " << nproton_reco;

	valor_minidst_beam       = beam;
	valor_minidst_wght_pot   = 1./mcsample_pot;
	valor_minidst_enu_reco    = enu_reco;
	valor_minidst_q0_reco     = q0_reco;
	valor_minidst_Costheta_reco  = Costheta_reco;
	valor_minidst_Theta_reco  = Theta_reco;
	valor_minidst_npion       = npion_reco;
	valor_minidst_npi0        = npi0_reco;
	valor_minidst_nproton     = nproton_reco;
	if(apply_weights)
	  valor_minidst_wght = reco_weight;
	else
	  valor_minidst_wght = 1.;
    
	VLOG("valor_sbn",pDEBUG) << "Event weights: "
		                 << "\n  wght           = "<< valor_minidst_wght  << "; "
		                 << "\n 1./mcsample_pot = "<< valor_minidst_wght_pot; 
				  

	valor_minidst->Fill();
      
	nev_accept += 1;
      } // loop over all fake reco slices
    }
  } // event loop

  if(!no_truth){
    for (unsigned int im = 0 ; im < nev_accept_by_mode.size(); im++) {
      valor::conv::ReacMode_t m = (valor::conv::ReacMode_t)im;
      VLOG("valor_sbn", pNOTICE) << "Selected "<<nev_accept_by_mode[im]<<" events of mode "<<valor::util::AsString(m);
    }
  }

  double f = 100. * (double)nev_accept / (double)nev;
  VLOG("valor_sbn", pNOTICE) <<
    "Used " << f << "% (" << nev_accept << "/" << nev
    << ") of input events.";

  double fpos = 100. * (double)nev_rejected_position / (double)nev;
  VLOG("valor_sbn", pNOTICE) <<
    "Rejected " << fpos << "% (" << nev_rejected_position << "/" << nev
    << ") of input events due to position.";
  //~ VLOG("valor_sbn", pNOTICE) <<"Total POT read: "<<total_pot_read;

  // Saving VALOR mini-DST to output file
  VLOG("valor_sbn", pNOTICE)
    << "Saving VALOR/SBN mini-DST to: " << opt_output_name;
  valor_minidst->Write();
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

/*bool CheckSample(const event::RecoInteraction &reco, const bool &numu, const valor::conv::Sample_t &sample, const bool &other){
  if(numu){
    if(sample == valor::conv::ksNuMuCC || sample == valor::conv::ksNuMuLikeCChigh) return true;
    else if(sample == valor::conv::ksNuMuCC0piNtrk){
      if((reco.npion+reco.npi0) == 0)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuMuCC0pi1trk){
      if((reco.npion+reco.npi0) == 0 && reco.nproton == 0)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuMuCC0pi2trk){
      if((reco.npion+reco.npi0) == 0 && reco.nproton == 1)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuMuCC1piC){
      if(reco.npion == 1 && reco.npi0 == 0)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuMuCC1pi0){
      if(reco.npion == 0 && reco.npi0 == 1)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuMuCC1piC1pi0){
      if(reco.npion == 1 && reco.npi0 == 1)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuMuCC2piC){
      if(reco.npion == 2 && reco.npi0 == 0)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuMuCCoth){
      if((reco.npion + reco.npi0) >= 2)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else{
      VLOG("valor_sbn",pFATAL) << "Error: Desired sample " << valor::util::AsString(sample) << " is not distinguishable from the information in this set of events ";
      return false;
    }
  }
  if(!numu){
    if(sample == valor::conv::ksNuECC || sample == valor::conv::ksNuELikeCChigh) return true;
    else if(sample == valor::conv::ksNuECC0pi){
      if((reco.npion+reco.npi0) == 0)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuECC1piC){
      if(reco.npion == 1 && reco.npi0 == 0)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuECCoth){
      if((reco.npion+reco.npi0) >= 2)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else{
      VLOG("valor_sbn",pFATAL) << "Error: Desired sample " << valor::util::AsString(sample) << " is not distinguishable from the information in this set of events ";
      return false;
    }
  }
  return false; 
}
*/
valor::conv::Sample_t GetOtherSample(const valor::conv::Sample_t &s, const bool &numu){

  // Numu CC
  if(valor::util::IsCC(s) && numu){
    valor::conv::Sample_t new_s = valor::util::SampleFromString("numuCCoth");
    assert(new_s != valor::conv::ksUndefined);
    return new_s;
  }

  // Numu NC
  else if(!valor::util::IsCC(s) && numu){
    valor::conv::Sample_t new_s = valor::util::SampleFromString("numuNCoth");
    assert(new_s != valor::conv::ksUndefined);
    return new_s;
  }

  // Nue CC
  else if(valor::util::IsCC(s) && !numu){
    valor::conv::Sample_t new_s = valor::util::SampleFromString("nueCCoth");
    assert(new_s != valor::conv::ksUndefined);
    return new_s;
  }
  
  // Nue NC
  else if(!valor::util::IsCC(s) && !numu){
    valor::conv::Sample_t new_s = valor::util::SampleFromString("nueNCoth");
    assert(new_s != valor::conv::ksUndefined);
    return new_s;
  }
  else{
    VLOG("valor_sbn",pNOTICE) << "The 'other' version of this sample cannot be determined, returning the input, " << valor::util::AsString(s);
    return s;
  }
}
void FillVariationBranches(const TString &vname,
                           const size_t &n_universes,
                           TObjArray &variation_names,
                           std::map<TString,int> &variation_nentries,
                           std::map<TString,variation_output_type *> &variation_entries,
                           TTree *valor_minidst){

  // Fill the variation names object for writing
  variation_names.AddLast(new TObjString(vname.Data()));

  // Make a branch to store the number of universes
  std::string branch_name_n (Form("variation_n_%s"  ,vname.Data()));
  std::string branch_name_nI(Form("variation_n_%s/I",vname.Data()));
  variation_nentries[vname] = -999;
  valor_minidst->Branch(branch_name_n.c_str(),&variation_nentries[vname],branch_name_nI.c_str());
  VLOG("valor_sbn",pNOTICE) << "Branch constructed with name: " << branch_name_n;

  assert(n_universes <= max_n_universes);

  // and a branch to store them all in
  variation_entries[vname] = new variation_output_type[max_n_universes];
  for (size_t ii = 0 ; ii < n_universes ; ii++) {
    variation_entries[vname][ii] = static_cast<variation_output_type>(valor::conv::kBadResult);
  }
  std::string branch_name (Form("variation_%s"  ,vname.Data()));
  std::string branch_nameF(Form("variation_%s[%s]/%c",vname.Data(),branch_name_n.c_str(),variation_output_type_root));
  VLOG("valor_sbn",pNOTICE) << "Branch constructed with name: " << branch_name;
  valor_minidst->Branch(branch_name.c_str(),variation_entries[vname],branch_nameF.c_str());
}
void GetCorrectVariationName(const int nuc_pdg, const bool iscc, TString &vname){

  TString name("");
  if(iscc){
    if(!vname.Contains("Alt")){
      if(!vname.Contains("bar")){
        if(vname.Contains("p1pi")){
          if(nuc_pdg == 2212)
            name = "genie_NonResRvpCC1pi_Genie";
          else if(nuc_pdg == 2112)
            name = "genie_NonResRvbarnCC1pi_Genie";
        }
        else if(vname.Contains("p2pi")){
          if(nuc_pdg == 2212)
            name = "genie_NonResRvpCC2pi_Genie";
          else if(nuc_pdg == 2112)
            name = "genie_NonResRvbarnCC2pi_Genie";
        }
      }
      else if(vname.Contains("bar")){
        if(vname.Contains("p1pi")){
          if(nuc_pdg == 2212)
            name = "genie_NonResRvbarpCC1pi_Genie";
          else if(nuc_pdg == 2112)
            name = "genie_NonResRvnCC1pi_Genie";
        }
        else if(vname.Contains("p2pi")){
          if(nuc_pdg == 2212)
            name = "genie_NonResRvbarpCC2pi_Genie";
          else if(nuc_pdg == 2112)
            name = "genie_NonResRvnCC2pi_Genie";
        }
      }
    }
  } 
  else{
    if(vname.Contains("Alt")){
      if(!vname.Contains("bar")){
        if(vname.Contains("p1pi")){
          if(nuc_pdg == 2212)
            name = "genie_NonResRvpNC1pi_Genie";
          else if(nuc_pdg == 2112)
            name = "genie_NonResRvbarnNC1pi_Genie";
        }
        else if(vname.Contains("p2pi")){
          if(nuc_pdg == 2212)
            name = "genie_NonResRvpNC2pi_Genie";
          else if(nuc_pdg == 2112)
            name = "genie_NonResRvbarnNC2pi_Genie";
        }
      }
      else if(vname.Contains("bar")){
        if(vname.Contains("p1pi")){
          if(nuc_pdg == 2212)
            name = "genie_NonResRvbarpNC1pi_Genie";
          else if(nuc_pdg == 2112)
            name = "genie_NonResRvnNC1pi_Genie";
        }
        else if(vname.Contains("p2pi")){
          if(nuc_pdg == 2212)
            name = "genie_NonResRvbarpNC2pi_Genie";
          else if(nuc_pdg == 2112)
            name = "genie_NonResRvnNC2pi_Genie";
        }
      }
    }
  }
  if(name == ""){
    VLOG("valor_sbn",pINFO) << " No alternative variation name was found for this event in which:" 
      << " \n  CC:            " << iscc
      << " \n  Nucleon PDG:   " << nuc_pdg
      << " \n  Original name: " << vname
      << " \n  --> Will set variation = 1 for all associated NonRes parameters ";
    vname = name;
  }
  else{
    VLOG("valor_sbn",pINFO) << " Alternative variation name for: " << vname << " is: " << name << " where: "
      << " \n  CC:            " << iscc
      << " \n  Nucleon PDG:   " << nuc_pdg;

    vname = name;
  }
}
void GetPair(const TString &vname, std::pair<TString,TString> &new_vnames){
  std::pair<TString,TString> names;
  if(vname == "genie_NonResRvp1pi_Genie"){
    names = std::make_pair("genie_NonResRvpCC1pi_Genie","genie_NonResRvbarnCC1pi_Genie");
  }
  else if(vname == "genie_NonResRvbarp1pi_Genie"){
    names = std::make_pair("genie_NonResRvbarpCC1pi_Genie","genie_NonResRvnCC1pi_Genie");
  }
  else if(vname == "genie_NonResRvp2pi_Genie"){
    names = std::make_pair("genie_NonResRvpCC2pi_Genie","genie_NonResRvbarnCC2pi_Genie");
  }
  else if(vname == "genie_NonResRvbarp2pi_Genie"){
    names = std::make_pair("genie_NonResRvbarpCC2pi_Genie","genie_NonResRvnCC2pi_Genie");
  }
  else if(vname == "genie_NonResRvp1piAlt_Genie"){
    names = std::make_pair("genie_NonResRvpNC1pi_Genie","genie_NonResRvbarnNC1pi_Genie");
  }
  else if(vname == "genie_NonResRvbarp1piAlt_Genie"){
    names = std::make_pair("genie_NonResRvbarpNC1pi_Genie","genie_NonResRvnNC1pi_Genie");
  }
  else if(vname == "genie_NonResRvp2piAlt_Genie"){
    names = std::make_pair("genie_NonResRvpNC2pi_Genie","genie_NonResRvbarnNC2pi_Genie");
  }
  else if(vname == "genie_NonResRvbarp2piAlt_Genie"){
    names = std::make_pair("genie_NonResRvbarpNC2pi_Genie","genie_NonResRvnNC2pi_Genie");
  }
  else{
    VLOG("valor_sbn",pERROR) << "No alternative parameter set found for input variation: " << vname;
    valor::util::Die(-1);
  }
  new_vnames = names;
}
//___________________________________________________________________
// Constructs all permutations of (left <--> right) combinations.
// Returns always in (left, right) notation
template <typename T>
void ConstructRecursion( std::vector<T> left, std::vector<T> right,
			 std::vector<std::vector<std::pair<T, T>>> & perms,
			 bool summarise )
{
  const int size_left  = left.size();
  const int size_right = right.size();

  const int size_min = std::min( size_left, size_right );
  const int size_max = std::max( size_left, size_right );

  std::vector<T> copy_small = ( size_min == size_left ) ? std::move(left) : std::move(right);
  std::vector<T> copy_large = ( size_min == size_left ) ? std::move(right) : std::move(left);

  std::vector<std::vector<std::pair<T, T>>> ret_perms;

  if( size_min == 0 ) return;
  if( size_min == 1 ) { // permutations are trivial
    for( const auto & r : copy_large ) {
      std::vector<std::pair<T, T>> elem; 
      if( size_left == size_min ) elem.emplace_back( std::pair<T, T>( copy_small.at(0), r ) ); 
      else elem.emplace_back( std::pair<T, T>( r, copy_small.at(0) ) );
      ret_perms.emplace_back( elem );
    }
  } else { /* recurse downwards. Grab the 0th element of copy_small,
	      make size_max elements, and populate each of them with
	      one pair (l0, r) and one new vector which considers 1 less elem on left and right */
    
    std::vector<T> small_less;
    for( typename std::vector<T>::iterator it_sml = copy_small.begin()+1 ;
	 it_sml != copy_small.end() ; ++it_sml ) small_less.emplace_back(*it_sml);
    for( typename std::vector<T>::iterator it_lrg = copy_large.begin() ; 
	 it_lrg != copy_large.end() ; ++it_lrg ) {

      // emplace back the *(copy_small.begin()) with this element, and pass the others to be recursed
      //std::vector<std::pair<T, T>> root_elem = {
      //	std::pair<T, T>( *(copy_small.begin()), *it_lrg ) }; // this will be added to

      std::vector<T> large_less;
      std::vector<std::vector<std::pair<T, T>>> recursed_perms;

      for( typename std::vector<T>::iterator it_lar = copy_large.begin() ;
	   it_lar != copy_large.end() ; ++it_lar ) {
	if( it_lar != it_lrg ) large_less.emplace_back( *it_lar );
      }
      ConstructRecursion( small_less, large_less, recursed_perms );

      //for( const auto & rp : recursed_perms ) ret_perms.emplace_back( rp );
      // Unpack the recursed_perms and for each member construct one element chain
      for( const auto & rp : recursed_perms ) {
	std::vector<std::pair<T, T>> ins_elem; 
	if( size_left == size_min ) 
	  ins_elem.emplace_back( std::pair<T, T>( *(copy_small.begin()), *it_lrg ) );
	else ins_elem.emplace_back( std::pair<T, T>( *it_lrg, *(copy_small.begin()) ) );
	for( const auto & ep : rp ) ins_elem.emplace_back( ep );

	ret_perms.emplace_back( ins_elem );
      }

    } // loop over the large
  } // not trivial

  if( summarise ) {
    VLOG( "valor_sbn", pDEBUG ) << "ret_perms has " << ret_perms.size() << " elements";
    for( typename std::vector<std::vector<std::pair<T, T>>>::iterator it_prm = ret_perms.begin() ;
	 it_prm != ret_perms.end() ; ++it_prm ) {
      std::ostringstream asts;
      asts << "Outputting element at index " << it_prm - ret_perms.begin() << "\n";
      for( typename std::vector<std::pair<T, T>>::iterator it_elm = (*it_prm).begin(); it_elm != (*it_prm).end();
	   ++it_elm ) {
	asts << "( " << (*it_elm).first << ", " << (*it_elm).second << " )";
      }
      VLOG("valor_sbn", pDEBUG) << asts.str();
    }
  } // output contents of vector

  perms = ret_perms;
}
//___________________________________________________________________
