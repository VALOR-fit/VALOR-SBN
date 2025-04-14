 //____________________________________________________________________________
/*!

  \app       valor_sbn-make_recoselection_minidst

  \brief     Converts input cafana trees to the VALOR mini-DST format.

  \syntax    valor_sbn-make_recoselection_minidst
                --input  input_analysis_file.root
                --output output_file_containing_valor_minidst.root
                --format format_of_the_input_file <hpgartpc, lartpc, fgt>
               [--disable-checks]

  \author    Shweta Yadav <sxy1439 \at mavs.uta.edu>
  University of Texas at Arlington

  \based on Rhinnon's make_sbncode_minidst.cxx

  \created   March 2025

  \copyright Copyright (c) 2010-2020, The VALOR group. All rights reserved.

*/
//____________________________________________________________________________

// System
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <utility>
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
//?
#include "core/Event.hh"

using std::string;
using std::ostringstream;

//const char* input_tree_name[6] = {"/reco_events/numuCCinc", "/reco_events/numuCC0p0pi", "/reco_events/numuCC1p0pi", "/reco_events/numuCCNp0pi",
//				  "/reco_events/numuCC1pi", "/reco_events/numuCCOther"}; 

const char* input_tree_name[6] = {"/selected_true/numuCCinc", "/selected_true/numuCC0p0pi", "/selected_true/numuCC1p0pi", "/selected_true/numuCCNp0pi",
				  "/selected_true/numuCC1pi", "/selected_true/numuCCOther"};

const char* input_systtree[2] = {"/selected_true/multisigmaTree_inclusive", "/selected_true/multisimTree_inclusive"};


void GetCommandLineArgs (int /*argc*/, char ** /*argv*/);
static const string gTreeName = input_tree_name[0];      // change this according to the file you are running
static const string gSystTreeName = input_systtree[1];

static const string gPOTTreeName = "subrun_tree";
static const int gPrintEveryNEvents   = 5;

//static const float thisPOT = 2.7E19;
static const float thisPOT = 6.96733E+18;

// The enum simb::int_type_ from LarSoft (copied from MCNeutrino.h, in v06_05_00)
typedef enum ScatterCode{     // similar to ELarMode in "make_sbncode_minidst.cxx" 

  kScatUnknownInteraction = -1,
  kNULL                   =  0,
  kScatQE                 =  1,
  kScatSingleKaon         =  2,
  kScatDIS                =  3,
  kScatRes                =  4,
  kScatCoh                =  5,
  kScatDiffractive        =  6,
  kScatElectronScattering =  7,
  kScatInverseMuonDecay   =  8,
  kScatAMNuGamma          =  9,
  kScatMEC                = 10,
  kScatCohElastic         = 11,
  kScatInverseBetaDecay   = 12,
  kScatGlashowResonance   = 13,
  kScatIMDAnnihilation    = 14,

} ScatterCode_t;

// enum definition for the sbn mc sample we are looking at
// For now, only important for accessing the correct POT from above
typedef enum EMCSample{

  kUnknownSample                = -1,
  kSBNDDisappearanceProposal    =  0,
  kSBNDDisappearanceModern      =  1,
  kUBOONEDisappearanceProposal  =  2,
  kUBOONEDisappearanceModern    =  3,
  kICARUSDisappearanceProposal  =  4,
  kICARUSDisappearanceModern    =  5,

  kSBNDAppearanceNumuProposal   =  6,
  kSBNDAppearanceIntProposal    =  7,
  kSBNDAppearanceOscProposal    =  8,
  kUBOONEAppearanceNumuProposal =  9,
  kUBOONEAppearanceIntProposal  = 10,
  kUBOONEAppearanceOscProposal  = 11,
  kICARUSAppearanceNumuProposal = 12,
  kICARUSAppearanceIntProposal  = 13,
  kICARUSAppearanceOscProposal  = 14

} MCSample_t;

typedef enum NuMuCCExclusiveTopology{

  kUnknownTopology              = -1,
  kCC0Pi                        =  0,
  kCC1Pi                        =  1,
  kCC2Pi                        =  2,
  kCCPi0                        =  3,
  kCCOther                      =  4

} ExclusiveTopology_t;


/*
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

*/

inline std::vector<std::string> GetGENIEDependentKnobNames(){   
  return {
    "ZExpAVariationResponse",
    "NCELVariationResponse",
    "CCRESVariationResponse",
    "NCRESVariationResponse",
    "DISBYVariationResponse",
    "FSI_pi_VariationResponse",
    "COHVariationResponse",
    "FSI_N_VariationResponse",
    "RPA_CCQE",
    "CoulombCCQE",
    "NormCCMEC",
    "NormNCMEC",
    "NonRESBGvpCC1pi",
    "NonRESBGvpCC2pi",
    "NonRESBGvpNC1pi",
    "NonRESBGvpNC2pi",
    "NonRESBGvnCC1pi",
    "NonRESBGvnCC2pi",
    "NonRESBGvnNC1pi",
    "NonRESBGvnNC2pi",
    "NonRESBGvbarpCC1pi",
    "NonRESBGvbarpCC2pi",
    "NonRESBGvbarpNC1pi",
    "NonRESBGvbarpNC2pi",
    "NonRESBGvbarnCC1pi",
    "NonRESBGvbarnCC2pi",
    "NonRESBGvbarnNC1pi",
    "NonRESBGvbarnNC2pi",
  };
}


void SetupVariationBranches( TTree* xsecsyst_tree,
			     TTree* valor_minidst,
			     std::map<std::string, std::vector<double>*>& input_variation_vectors,
			     std::map<std::string, Float_t*>& variation_arrays,
			     std::map<std::string, Int_t>& variation_counts,
			     int max_n_universes );

void FillVariationBranches( const std::map<std::string, std::vector<double>*>& input_variation_vectors,
			    std::map<std::string, Float_t*>& variation_arrays,
			    std::map<std::string, Int_t>& variation_counts,
			    int max_n_universes );


bool CheckSample(const int &reco_top, const int &reco_npiPM, const bool &numu, const valor::conv::Sample_t &sample, const bool &other);  
valor::conv::Sample_t GetOtherSample(const valor::conv::Sample_t &s, const bool &numu);

//___________________________________________________________________
int main(int argc, char ** argv)
{
  // Set GENIE print level
  genie::GHepRecord::SetPrintLevel(genie::RunOpt::Instance()->EventRecordPrintLevel());

  using namespace valor;

  CmdLnArgList arg;
  arg.Read(argc,argv, "$VALOR_EXPT/config/apps/make_recoselection_minidst_shweta.arg");
  LOG("valor_sbn", pNOTICE) << arg;

  std::string thresholds = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  Messenger::Instance()->Configure(thresholds);

  string opt_beam_name         = arg.GetString("beam");
  string opt_sample_name       = arg.GetString("sample");
  string opt_output_name       = arg.GetString("output");
  string opt_input_name        = arg.GetString("input");
  string opt_oscillation       = arg.GetString("oscillation");
  bool   opt_disable_checks    = arg.GetBool("disable-checks");
  bool   write_universes       = arg.GetBool("write-universes");
  bool   apply_weights         = !(arg.GetBool("dont-apply-weights"));
  bool   no_truth              = arg.GetBool("no-truth");
  bool   other_sample          = arg.GetBool("other-sample");
  bool   fix_nonres            = arg.GetBool("fix-nonres");
  bool   status_code_set       = arg.GetBool("status-code-set");
  int    max_n_events          = arg.GetInt("max-n-events");


  conv::Sample_t sample = util::SampleFromString(opt_sample_name);  // gets sample from the string while generating dst. Defined in "VALOR-SDK/../Conventions/Sample.cxx"
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
  if(std::count(found, found+sizeof(found), 1) == 0){
    VLOG("valor_sbn", pFATAL)
      << "Error: Found hint of neither selected nuE (" << str_nue << ", " << str_int << ", " << str_osc << ", " << str_dirt << "," << str_cosmic << ") nor selected nuMu ( " << str_numu << ") in filename - misleading: " << opt_input_name;
    exit(1);
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
  
  

  // Get the POT
  // open the ROOT file and get the TTree & its header
  /*
  TChain * subrun_tree = new TChain(gPOTTreeName.c_str());
  subrun_tree->Add(opt_input_name.c_str());
  if(!subrun_tree || !subrun_tree->GetEntries()) {
    VLOG("valor_sbn", pFATAL)
      << "Unable to read " << gPOTTreeName
      <<" from "<< opt_input_name;
    exit(1);
  }

  Long64_t nsub = subrun_tree->GetEntries();
  VLOG("valor_sbn", pNOTICE)
    << "Input subrun tree has " << nsub << ((nsub==1) ? " entry." : " entries.");

  double mcsample_pot = -1.;
  subrun_tree->SetBranchAddress("pot", &mcsample_pot);
  subrun_tree->GetEntry(0);
  
  */

  double mcsample_pot = -1.;
  //mcsample_pot = hist_pot->Integral();  // Sum over all bins to get total POT
  mcsample_pot = thisPOT; // for now (later have to save in a branch of the input) 
  std::cout << "Total POT from histogram: " << mcsample_pot << std::endl;

  if(mcsample_pot < 1)
    VLOG("valor_sbn", pNOTICE) << "POT in file is less than 1 ";

  if(mcsample_pot == -1.){
    VLOG("valor_sbn", pFATAL)
      << "Not able to access MCSample POT from " << opt_input_name;
    exit(1);
  }

  VLOG("valor_sbn",pINFO) << " POT in file : " << mcsample_pot << "\n";


  int    valor_minidst_sample          = sample;    // will be input into this
  int    valor_minidst_beam            = -1;  // see Conventions/BeamConf.h
  int    valor_minidst_reac_mode       = -1;  // see Conventions/ReacMode.h
  int    valor_minidst_reac_type       = -1;  // see Conventions/ReacMode.h
  int    valor_minidst_target          = -1;  // nuclear target -  GENIE PDG convention
  int    valor_minidst_init_nupdg      = -1;  // Initial PDG
  int    valor_minidst_final_nupdg     = -1;  // Final PDG
  double valor_minidst_baseline        = -1.; // true baseline of the event
  double valor_minidst_enu_true        = -1.; // true neutrino energy, in GeV
  double valor_minidst_Q2_true         = -1.; // true neutrino Q2
  double valor_minidst_enu_reco        = -1.; // reco neutrino energy, in GeV
  double valor_minidst_mu_momentum     = -1.; // reco muon momentum
  double valor_minidst_mu_cos_z        = -1.; // reco muon cos(angle to z)
  double valor_minidst_q0_reco         = -1.; // reco lepton energy, in GeV
  double valor_minidst_Theta_reco      = -1.; // reco lepton opening angle
  double valor_minidst_y_reco          = -1.; // inelasticity
  double valor_minidst_wght_pot        = -1.; // POT weight
  double valor_minidst_wght            = -1.; // misc weight
  //double valor_minidst_wght_smear      = -1.; // energy smearing weight
  double valor_minidst_reco_topology   = -1.; // exclusive reconstructed topology
  double valor_minidst_true_topology   = -1.; // exclusive true topology


  TFile fout(opt_output_name.c_str(),"recreate");
  fout.cd();

  TTree * valor_minidst =
    new TTree("valor_sbn_minidst","Mini-DST input for VALOR/SBN fit");

  valor_minidst->Branch("beam"             , &valor_minidst_beam             ,"beam/I"                );
  valor_minidst->Branch("sample"           , &valor_minidst_sample           ,"sample/I"              );
  valor_minidst->Branch("reac_mode"        , &valor_minidst_reac_mode        ,"reac_mode/I"           );
  valor_minidst->Branch("reac_type"        , &valor_minidst_reac_type        ,"reac_type/I"           );
  valor_minidst->Branch("target"           , &valor_minidst_target           ,"target/I"              );
  valor_minidst->Branch("init_pdg"         , &valor_minidst_init_nupdg       ,"init_pdg/I"            );
  valor_minidst->Branch("final_pdg"        , &valor_minidst_final_nupdg      ,"final_pdg/I"           );
  valor_minidst->Branch("baseline"         , &valor_minidst_baseline         ,"baseline/D"            );
  valor_minidst->Branch("enu_true"         , &valor_minidst_enu_true         ,"enu_true/D"            );
  valor_minidst->Branch("Q2_true"          , &valor_minidst_Q2_true          ,"q2_true/D"             );
  valor_minidst->Branch("enu_reco"         , &valor_minidst_enu_reco         ,"enu_reco/D"            );
  valor_minidst->Branch("mu_momentum"      , &valor_minidst_mu_momentum      ,"mu_momentum/D"         );
  valor_minidst->Branch("mu_cos_z"         , &valor_minidst_mu_cos_z         ,"mu_cos_z/D"            );
  valor_minidst->Branch("q0_reco"          , &valor_minidst_q0_reco          ,"q0_reco/D"             );
  valor_minidst->Branch("Theta_reco"       , &valor_minidst_Theta_reco       ,"Theta_reco/D"          );
  valor_minidst->Branch("y_reco"           , &valor_minidst_y_reco           ,"y_reco/D"              );
  valor_minidst->Branch("wght_pot"         , &valor_minidst_wght_pot         ,"wght_pot/D"            );
  valor_minidst->Branch("wght"             , &valor_minidst_wght             ,"wght/D"                );
  //valor_minidst->Branch("wght_smear"       , &valor_minidst_wght_smear       ,"wght_smear/D"        );
  valor_minidst->Branch("reco_topology"    , &valor_minidst_reco_topology    ,"reco_topology/I"       );
  valor_minidst->Branch("true_topology"    , &valor_minidst_true_topology    ,"true_topology/I"       );

  

  // 20 dst branches to fill

  // open the ROOT file and get the TTree & its header
  TChain * analysis_tree = new TChain(gTreeName.c_str());
  analysis_tree->Add((opt_input_name + gTreeName).c_str());
  if(!analysis_tree || !analysis_tree->GetEntries()) {
    VLOG("valor_sbn", pFATAL)
      << "Unable to read " << gTreeName
      <<" from "<< opt_input_name;
    exit(1);
  }

  // gSystTreeName
  TChain * xsecsyst_tree = new TChain(gSystTreeName.c_str());
  xsecsyst_tree->Add((opt_input_name + gSystTreeName).c_str());
  if(!xsecsyst_tree || !xsecsyst_tree->GetEntries()) {
    VLOG("valor_sbn", pFATAL)
      << "Unable to read " << gSystTreeName
      <<" from "<< opt_input_name;
    exit(1);
  }

  if (xsecsyst_tree->GetEntries() != analysis_tree->GetEntries()) {
    std::cout << "Entry mismatch between analysis_tree and xsecsyst_tree" << std::endl;
    exit(1);
  }


  Long64_t nev = analysis_tree->GetEntries();
  VLOG("valor_sbn", pNOTICE)
    << "Input analysis tree has " << nev << ((nev==1) ? " entry." : " entries.");
  analysis_tree->GetEntry(0);
  
  
  // Variables to get from analysis tree
  int iscc                = false;
  int isnc                = false;
  double enu_true         = -999.;
  double enu_reco         = -999.;
  double enu_reco_inc     = -999.;
  double enu_reco_0p0pi   = -999.;
  double enu_reco_1p0pi   = -999.;
  double enu_reco_Np0pi   = -999.;
  double enu_reco_1pi     = -999.;
  double enu_reco_Other   = -999.;
  double qsqr             = -999.;
  double mu_momentum      = -999.;
  double mu_cos_z         = -999.;
  double q0_reco          = -999.;
  double Theta_reco       = -999.;
  double baseline         = -999.;
  int nu_pdg              = -1;
  int init_pdg            = -1;
  int larsoft_mode        = -1;
  int nkaons              = -1;
  int npip                = -1;
  int npim                = -1;
  int npi0                = -1;
  int npro                = -1;
  int npio                = -1;
  int true_topology      = -1;
  int reco_topology      = -1;

  analysis_tree->SetBranchAddress("iscc",                &iscc               );
  analysis_tree->SetBranchAddress("isnc",                &isnc               );
  analysis_tree->SetBranchAddress("nu_pdg",              &nu_pdg             );
  analysis_tree->SetBranchAddress("init_pdg",            &init_pdg           );
  analysis_tree->SetBranchAddress("enu_true",            &enu_true           );
  analysis_tree->SetBranchAddress("enu_reco_inc",        &enu_reco_inc       );
  analysis_tree->SetBranchAddress("enu_reco_0p0pi",      &enu_reco_0p0pi     );
  analysis_tree->SetBranchAddress("enu_reco_1p0pi",      &enu_reco_1p0pi     );
  analysis_tree->SetBranchAddress("enu_reco_Np0pi",      &enu_reco_Np0pi     );
  analysis_tree->SetBranchAddress("enu_reco_1pi",        &enu_reco_1pi       );
  analysis_tree->SetBranchAddress("enu_reco_Other",      &enu_reco_Other     );
  analysis_tree->SetBranchAddress("mu_momentum",         &mu_momentum        );
  analysis_tree->SetBranchAddress("mu_costh",            &mu_cos_z           );
  analysis_tree->SetBranchAddress("baseline",            &baseline           );
  analysis_tree->SetBranchAddress("qsqr",                &qsqr               );
  analysis_tree->SetBranchAddress("larsoft_mode",        &larsoft_mode       );
  analysis_tree->SetBranchAddress("nkaons",              &nkaons             );
  analysis_tree->SetBranchAddress("npip",                &npip               );   
  analysis_tree->SetBranchAddress("npim",                &npim               );
  analysis_tree->SetBranchAddress("npi0",                &npi0               );
  //analysis_tree->SetBranchAddress("npio",                &npio             );
  analysis_tree->SetBranchAddress("npro",                &npro               );
  analysis_tree->SetBranchAddress("true_topology",       &true_topology      );
  analysis_tree->SetBranchAddress("reco_topology",       &reco_topology      );


  // systematic variations

  std::map<std::string, std::vector<double>*> input_variation_vectors;
  std::map<std::string, Float_t*> variation_arrays;
  std::map<std::string, Int_t> variation_counts;

  if(!no_truth && write_universes){
    xsecsyst_tree->GetEntry(0);
    SetupVariationBranches(xsecsyst_tree, valor_minidst, input_variation_vectors, variation_arrays, variation_counts, 1000);
    
  }
 

  //
  // event loop
  //
  
  std::vector<int> nev_accept_by_mode;
  for (int im = 0 ; im < valor::conv::kNReacModes; im++) {
    nev_accept_by_mode.push_back(0);
  }


  for(Long64_t iev = 0; iev < nev; iev++) {
  //for(Long64_t iev = 0; iev < 22000; iev++) {
 
    if (gPrintEveryNEvents && !(iev%gPrintEveryNEvents)) {
      VLOG("valor_sbn", pNOTICE) << "** Reading event: " << iev;
    }
    else {
      VLOG("valor_sbn", pDEBUG) << "** Reading event: " << iev;
    }

    analysis_tree->GetEntry(iev);

    q0_reco = sqrt(pow(mu_momentum, 2) + pow(conv::kMuonMassGeV, 2)); // lepton energy
    Theta_reco = acos(mu_cos_z);

    // Get reco Enu
    if      (sample == conv::ksNuMuCC0p0pi) enu_reco = enu_reco_0p0pi;   // exclusive
    else if (sample == conv::ksNuMuCC1p0pi) enu_reco = enu_reco_1p0pi;
    else if (sample == conv::ksNuMuCCNp0pi) enu_reco = enu_reco_Np0pi;
    else if (sample == conv::ksNuMuCC1pi)   enu_reco = enu_reco_1pi;
    else if (sample == conv::ksNuMuCCOther) enu_reco = enu_reco_Other;
    else if (sample == conv::ksNuMuCC)      enu_reco = enu_reco_inc;    // inclusive
    else{
      VLOG("valor_sbn",pFATAL) << "Error: Desired sample " << util::AsString(sample) << " is not distinguishable from the information in this set of events ";
      exit(1);
    }

    // Just for making sure
    if      (sample == conv::ksNuMuCC0p0pi) std::cout<<"sample numuCC 0p0pi"<<std::endl;   // exclusive
    else if (sample == conv::ksNuMuCC1p0pi) std::cout<<"sample numuCC 1p0pi"<<std::endl;
    else if (sample == conv::ksNuMuCCNp0pi) std::cout<<"sample numuCC Np0pi"<<std::endl;
    else if (sample == conv::ksNuMuCC1pi)   std::cout<<"sample numuCC 1pi"<<std::endl;
    else if (sample == conv::ksNuMuCCOther) std::cout<<"sample numuCC Other"<<std::endl;
    else if (sample == conv::ksNuMuCC)      std::cout<<"sample numuCC incl"<<std::endl;    // inclusive 
    

    // Construct the reaction mode
    conv::ReacType_t reac = conv::kmtUndefined;   
    if (iscc) {
      if      (larsoft_mode==kScatQE                ) {reac = conv::kmtCCQE;    }
      else if (larsoft_mode==kScatMEC               ) {reac = conv::kmtCCMEC;   }
      else if (larsoft_mode==kScatCoh               ) {reac = conv::kmtCCcoh;   }
      else if (larsoft_mode==kScatIMDAnnihilation   ) {reac = conv::kmtCCIMD;   }
      else if (larsoft_mode==kScatElectronScattering) {reac = conv::kmtCCELScat;}

      else { // start counting pions
	if      (nkaons )                      {reac = conv::kmtCCoth;}
        else if (npio == 1 && npi0 == 0)  {reac = conv::kmtCC1piC;}      // modes assigned from number of true particles in the selection
        else if (npip == 0 && npi0 == 1)  {reac = conv::kmtCC1pi0;}
        else if (npip == 2 && npi0 == 0)  {reac = conv::kmtCC2piC;}
        else if (npip == 0 && npi0 == 2)  {reac = conv::kmtCC2pi0;}
        else if (npip == 1 && npi0 == 1)  {reac = conv::kmtCCpiCpi0;}
        else                              {reac = conv::kmtCCoth;}
        if      (nkaons )                      {reac = conv::kmtCCoth;}
        else if (npip+npim == 1 && npi0 == 0)  {reac = conv::kmtCC1piC;}
        else if (npip+npim == 0 && npi0 == 1)  {reac = conv::kmtCC1pi0;}
        else if (npip+npim == 2 && npi0 == 0)  {reac = conv::kmtCC2piC;}
        else if (npip+npim == 0 && npi0 == 2)  {reac = conv::kmtCC2pi0;}
        else if (npip+npim == 1 && npi0 == 1)  {reac = conv::kmtCCpiCpi0;}
        else                                   {reac = conv::kmtCCoth;}
      }
    }
    else if (isnc) {
      if      (larsoft_mode==kScatQE                ) {reac = conv::kmtNCEL;    }
      else if (larsoft_mode==kScatMEC               ) {reac = conv::kmtNCMEC;   }
      else if (larsoft_mode==kScatCoh               ) {reac = conv::kmtNCcoh;   }
      else if (larsoft_mode==kScatElectronScattering) {reac = conv::kmtNCELScat;}

      else { // start counting pions
        if      (nkaons)                       {reac = conv::kmtNCoth;}
        else if (npip+npim == 1 && npi0 == 0)  {reac = conv::kmtNC1piC;}
        else if (npip+npim == 0 && npi0 == 1)  {reac = conv::kmtNC1pi0;}
        else if (npip+npim == 2 && npi0 == 0)  {reac = conv::kmtNC2piC;}
        else if (npip+npim == 0 && npi0 == 2)  {reac = conv::kmtNC2pi0;}
        else if (npip+npim == 1 && npi0 == 1)  {reac = conv::kmtNCpiCpi0;}
        else                                   {reac = conv::kmtNCoth;}
      }
    }
    else if (larsoft_mode == kScatElectronScattering) {
      reac = conv::kmtELScat;
    }

    else reac = conv::kmtOther;

    conv::NuFlavour_t final_flav = valor::util::FlavourFromPDG(nu_pdg);    // initial flavor of neutrino    ("FlavourFromPDG" is defined here "valor/Conventions/NuFlavour.cxx")
    conv::NuFlavour_t init_flav = valor::util::FlavourFromPDG(init_pdg);   // final nu flavor (will be same as "init_flav" for disapperance and different for appearance)
    //conv::NuFlavour_t init_flav = final_flav;

    // If we are looking at the selected nuE samples, get the initial neutrino pdg from the file
    //init_pdg  = truth.neutrino.initpdg;
    //init_flav = valor::util::FlavourFromPDG(init_pdg);

    // Get the real valor mode
    conv::ReacMode_t  reac_mode  = valor::util::ReacTypeToMode(reac,init_flav,final_flav);
    
    if(!opt_disable_checks) {
      //
      // ignore events that can not be used in the VALOR analysis
      //
      if(reac_mode == conv::kmUndefined) {
        VLOG("valor_sbn", pWARN) << "- Rejecting event [bad mode]\n";
	VLOG("valor_sbn", pNOTICE)
            <<"\n larsoft_mode = "<<larsoft_mode
            <<"\n baseline = "<< baseline << " m"
            <<"\n iscc="<<iscc<<" and isnc="<<isnc
            <<"\n initpdg="<<init_pdg<<" and finalpdg="<<nu_pdg
            <<"\n valor reaction="<<reac<<" which is "<<util::AsString(reac);
        continue;
      }
    }

    VLOG("valor_sbn",pDEBUG) << "Read event: "
      << "Etrue         = "<< enu_true  << " GeV; "
      << "Ereco         = "<< enu_reco  << " GeV; "
      << "LArSoft mode  = "<< larsoft_mode  << "; ";

    valor_minidst_sample              = sample;
    valor_minidst_beam                = beam;
    valor_minidst_reac_mode           = reac_mode;    
    valor_minidst_reac_type           = reac;
    valor_minidst_init_nupdg          = init_pdg;
    valor_minidst_final_nupdg         = nu_pdg;
    valor_minidst_enu_true            = enu_true;
    valor_minidst_enu_reco            = enu_reco;
    //valor_minidst_enu_reco            = enu_reco*qsqr;
    //valor_minidst_enu_reco            = enu_reco*sin(qsqr);
    //valor_minidst_enu_reco            = enu_reco*(sin(qsqr)/qsqr);
    valor_minidst_wght                = 1.;
    valor_minidst_Q2_true             = qsqr;
    valor_minidst_wght_pot            = 1./mcsample_pot;
    valor_minidst_target              = 1000180400; // Argon40
    valor_minidst_baseline            = baseline/1000.;
    valor_minidst_y_reco              = 0.5; // FORCE y=0.5 for now
    valor_minidst_mu_momentum         = mu_momentum;
    valor_minidst_mu_cos_z            = mu_cos_z;
    valor_minidst_q0_reco             = q0_reco;
    valor_minidst_Theta_reco          = Theta_reco;
    valor_minidst_true_topology       = true_topology;
    valor_minidst_reco_topology       = reco_topology;

    VLOG("valor_sbn", pINFO)
      << "\n Information copied to VALOR SBN recoselection Mini-DST: "
      << "\n Beam              = " << valor_minidst_beam
      << "\n Sample            = " << valor_minidst_sample
      << "\n Reaction mode     = " << valor_minidst_reac_mode
      << "\n Target            = " << valor_minidst_target
      << "\n Baseline          = " << valor_minidst_baseline << " m"
      << "\n Q2 (true)         = " << valor_minidst_Q2_true << " GeV^2"
      << "\n Ev (true)         = " << valor_minidst_enu_true << " GeV"
      << "\n Pmu (reco)        = " << valor_minidst_mu_momentum << "GeV/c^2"
      << "\n P cosZ (reco)     = " << valor_minidst_mu_cos_z
      << "\n Reco lepton E     = "<< q0_reco  << " GeV; "
      << "\n Reco lepton angle = "<< Theta_reco
      << "\n y (reco)          = " << valor_minidst_y_reco
      << "\n POT weight        = " << valor_minidst_wght_pot
      //<< "\n Smear weight    = " << valor_minidst_wght_smear
      << "\n Reco topology     = " << valor_minidst_reco_topology
      << "\n True topology     = " << valor_minidst_true_topology;

    VLOG("valor_sbn",pDEBUG) << "Read event: "
      << "Ereco         = "<< enu_reco  << " GeV; ";
    if(!opt_disable_checks) {

      //
      // ignore events that can not be used in the VALOR analysis
      //
      if(enu_reco <= 0) {
        VLOG("valor_sbn", pINFO) << "- Rejecting event [Ev (reco) <= 0]: "<< enu_reco;
        continue;
      }

      VLOG("valor_sbn", pINFO) << "+ Accepting event";
    }

    valor_minidst_enu_reco  = enu_reco;
    VLOG("valor_sbn", pNOTICE)
      << "\n Ev (reco)     = " << valor_minidst_enu_reco << " GeV";


    // systematic variations
    
    if(write_universes){
      
      xsecsyst_tree->GetEntry(iev);
      FillVariationBranches(input_variation_vectors, variation_arrays, variation_counts, 1000);
      
    }

    

    valor_minidst->Fill();
  } // event loop

  std::cout << " Number in valor tree : " << valor_minidst->GetEntries() << std::endl;
  /*
  for (unsigned int im = 0 ; im < nev_accept_by_mode.size(); im++) {
    valor::conv::ReacMode_t m = (valor::conv::ReacMode_t)im;
    VLOG("valor_sbn", pNOTICE) << "Selected "<<nev_accept_by_mode[im]<<" events of mode "<<valor::util::AsString(m);
  }

  double f = 100. * (double)nev_accept / (double)nev;
  VLOG("valor_sbn", pNOTICE) <<
    "Used " << f << "% (" << nev_accept << "/" << nev
    << ") of input events.";

  //~ VLOG("valor_sbn", pNOTICE) <<
    //~ "Total POT read: "<<total_pot_read;
*/
  // Saving VALOR mini-DST to output file
  VLOG("valor_sbn", pNOTICE)
    << "Saving VALOR/SBN mini-DST to: " << opt_output_name;
  valor_minidst->Write();
  fout.Close();

  VLOG("valor_sbn", pNOTICE)  << "Done!";

  return 0;
}


void SetupVariationBranches(
    TTree* xsecsyst_tree,
    TTree* valor_minidst,
    std::map<std::string, std::vector<double>*>& input_variation_vectors,
    std::map<std::string, Float_t*>& variation_arrays,
    std::map<std::string, Int_t>& variation_counts,
    int max_n_universes = 1000
) {
  TObjArray* branches = xsecsyst_tree->GetListOfBranches();

  //std::set<std::string> valid_systs(GetGENIEDependentKnobNames().begin(), GetGENIEDependentKnobNames().end());

  std::vector<std::string> test_knobs = GetGENIEDependentKnobNames();  
  std::set<std::string> valid_systs(test_knobs.begin(), test_knobs.end());

  for (int i = 0; i < branches->GetEntries(); ++i) {
    TBranch* br = (TBranch*)branches->At(i);
    std::string base_name = br->GetName();
   
    if (valid_systs.count(base_name) == 0){ // to skip non-variation branches
      std::cout << "skipping non-variation branches: " << base_name << std::endl;
      continue;  
    }

    // input vector point and branch address set 
    input_variation_vectors[base_name] = nullptr;
    xsecsyst_tree->SetBranchAddress(base_name.c_str(), &input_variation_vectors[base_name]);

    // for valor dst output
    variation_arrays[base_name] = new Float_t[max_n_universes];
    variation_counts[base_name] = 0;

    std::string nbranch = "variation_n_genie_" + base_name + "_Genie";
    std::string arbranch = "variation_genie_" + base_name + "_Genie";
    std::string leaflist = arbranch + "[" + nbranch + "]/F";

    valor_minidst->Branch(nbranch.c_str(), &variation_counts[base_name], (nbranch + "/I").c_str());
    valor_minidst->Branch(arbranch.c_str(), variation_arrays[base_name], leaflist.c_str());

    std::cout << "valor minidst branch saved : " << base_name << " with " << arbranch << std::endl;
  }
}


void FillVariationBranches(
    const std::map<std::string, std::vector<double>*>& input_variation_vectors,
    std::map<std::string, Float_t*>& variation_arrays,
    std::map<std::string, Int_t>& variation_counts,
    int max_n_universes = 1000
) {
  
  for (const auto& [name, vec_ptr] : input_variation_vectors) {
    if (!vec_ptr) {
      std::cerr << "Null vector for " << name << std::endl;
      variation_counts[name] = 0;
      continue;
    }

    int nuniv = vec_ptr->size();
    /*
    if (nuniv > max_n_universes) {
      std::cout << "too many universes for " << name << ": " << nuniv << " (max = " << max_n_universes << ")" << std::endl;
      nuniv = max_n_universes;
    }
    */
    if (nuniv > max_n_universes) {
      std::cerr << "too many universes for " << name << ": " << nuniv << std::endl;
      variation_counts[name] = 0;
      continue;
    }

    variation_counts[name] = nuniv;
    for (int i = 0; i < nuniv; ++i) {
      variation_arrays[name][i] = static_cast<Float_t>(vec_ptr->at(i));
    }
  }
}



bool CheckSample(const int &reco_top, const int &reco_npiPM, const bool &numu, const valor::conv::Sample_t &sample, const bool &other){
  if(numu){
    if(sample == valor::conv::ksNuMuCC || sample == valor::conv::ksNuMuLikeCChigh) return true;
    else if(sample == valor::conv::ksNuMuCC0p0pi){
      if(reco_top == 0)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuMuCC1p0pi){
      if(reco_top == 1)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuMuCCNp0pi){
      if(reco_top == 2)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuMuCC1pi){
      if(reco_top == 3)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuMuCCOther){
      if(reco_top == 4)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else{
      LOG("valor_sbn",pFATAL) << "Error: Desired sample " << valor::util::AsString(sample) << " is not distinguishable from the information in this set of events ";
      return false;
    }
  }
  if(!numu){
    if(sample == valor::conv::ksNuECC || sample == valor::conv::ksNuELikeCChigh) return true;
    else if(sample == valor::conv::ksNuECC0pi){
      if(reco_npiPM == 0)       // has to be this "reco.npion+reco.npi0"
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuECC1piC){
      if(reco_npiPM == 1)     // has to be this "reco.npion == 1 && reco.npi0 == "
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuECCoth){
      if((reco_npiPM) >= 2)         // has to be this "reco.npion+reco.npi0"
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else{
      LOG("valor_sbn",pFATAL) << "Error: Desired sample " << valor::util::AsString(sample) << " is not distinguishable from the information in this set of events ";
      return false;
    }
  }
  return false; 
}

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
    LOG("valor_sbn",pNOTICE) << "The 'other' version of this sample cannot be determined, returning the input, " << valor::util::AsString(s);
    return s;
  }
}


/*

  int nuniv = 100;
  
  int variation_n_genie_NonRESBGvpCC1pi_Genie = 0;
  int variation_n_genie_NonRESBGvpCC2pi_Genie = 0;
  int variation_n_genie_NonRESBGvpNC1pi_Genie = 0;
  int variation_n_genie_NonRESBGvpNC2pi_Genie = 0;
  int variation_n_genie_NonRESBGvnCC1pi_Genie = 0;
  int variation_n_genie_NonRESBGvnCC2pi_Genie = 0;
  int variation_n_genie_NonRESBGvnNC1pi_Genie = 0;
  int variation_n_genie_NonRESBGvnNC2pi_Genie = 0;
  int variation_n_genie_NonRESBGvbarpCC1pi_Genie = 0;
  int variation_n_genie_NonRESBGvbarpCC2pi_Genie = 0;
  int variation_n_genie_NonRESBGvbarpNC1pi_Genie = 0;
  int variation_n_genie_NonRESBGvbarpNC2pi_Genie = 0;
  int variation_n_genie_NonRESBGvbarnCC1pi_Genie = 0;
  int variation_n_genie_NonRESBGvbarnCC2pi_Genie = 0;
  int variation_n_genie_NonRESBGvbarnNC1pi_Genie = 0;
  int variation_n_genie_NonRESBGvbarnNC2pi_Genie = 0;
  
  double variation_genie_NonRESBGvpCC1pi_Genie[nuniv];
  double variation_genie_NonRESBGvpCC2pi_Genie[nuniv];
  double variation_genie_NonRESBGvpNC1pi_Genie[nuniv];
  double variation_genie_NonRESBGvpNC2pi_Genie[nuniv];
  double variation_n_genie_NonRESBGvnCC1pi_Genie[nuniv];
  double variation_genie_NonRESBGvnCC2pi_Genie[nuniv];
  double variation_genie_NonRESBGvnNC1pi_Genie[nuniv];
  double variation_genie_NonRESBGvnNC2pi_Genie[nuniv];
  double variation_genie_NonRESBGvbarpCC1pi_Genie[nuniv];
  double variation_genie_NonRESBGvbarpCC2pi_Genie[nuniv];
  double variation_genie_NonRESBGvbarpNC1pi_Genie[nuniv];
  double variation_genie_NonRESBGvbarpNC2pi_Genie[nuniv];
  double variation_genie_NonRESBGvbarnCC1pi_Genie[nuniv];
  double variation_genie_NonRESBGvbarnCC2pi_Genie[nuniv];
  double variation_genie_NonRESBGvbarnNC1pi_Genie[nuniv];
  double variation_genie_NonRESBGvbarnNC2pi_Genie[nuniv];
  
  
  


// Parameters to get from xsec systematics tree (incomplete list)
  std::vector<double> NonRESBGvpCC1pi = {};  
  std::vector<double> NonRESBGvpCC2pi = {};
  std::vector<double> NonRESBGvpNC1pi = {};
  std::vector<double> NonRESBGvpNC2pi = {};
  std::vector<double> NonRESBGvnCC1pi = {};
  std::vector<double> NonRESBGvnCC2pi = {};
  std::vector<double> NonRESBGvnNC1pi = {};
  std::vector<double> NonRESBGvnNC2pi = {};
  std::vector<double> NonRESBGvbarpCC1pi = {};
  std::vector<double> NonRESBGvbarpCC2pi = {};
  std::vector<double> NonRESBGvbarpNC1pi = {};
  std::vector<double> NonRESBGvbarpNC2pi = {};
  std::vector<double> NonRESBGvbarnCC1pi = {};
  std::vector<double> NonRESBGvbarnCC2pi = {};
  std::vector<double> NonRESBGvbarnNC1pi = {};
  std::vector<double> NonRESBGvbarnNC2pi = {};

  xsecsyst_tree->SetBranchAddress("NonRESBGvpCC1pi",  &NonRESBGvpCC1pi   );
  xsecsyst_tree->SetBranchAddress("NonRESBGvpCC2pi",  &NonRESBGvpCC2pi   );
  xsecsyst_tree->SetBranchAddress("NonRESBGvpNC1pi",  &NonRESBGvpNC1pi   );
  xsecsyst_tree->SetBranchAddress("NonRESBGvpNC2pi",  &NonRESBGvpNC2pi   );
  xsecsyst_tree->SetBranchAddress("NonRESBGvnCC1pi",  &NonRESBGvnCC1pi   );
  xsecsyst_tree->SetBranchAddress("NonRESBGvnCC2pi",  &NonRESBGvnCC2pi   );
  xsecsyst_tree->SetBranchAddress("NonRESBGvnNC1pi",  &NonRESBGvnNC1pi   );
  xsecsyst_tree->SetBranchAddress("NonRESBGvnNC2pi",  &NonRESBGvnNC2pi   );
  xsecsyst_tree->SetBranchAddress("NonRESBGvbarpCC1pi",  &NonRESBGvbarpCC1pi   );
  xsecsyst_tree->SetBranchAddress("NonRESBGvbarpCC2pi",  &NonRESBGvbarpCC2pi   );
  xsecsyst_tree->SetBranchAddress("NonRESBGvbarpNC1pi",  &NonRESBGvbarpNC1pi   );
  xsecsyst_tree->SetBranchAddress("NonRESBGvbarpNC2pi",  &NonRESBGvbarpNC2pi   );
  xsecsyst_tree->SetBranchAddress("NonRESBGvbarnCC1pi",  &NonRESBGvbarnCC1pi   );
  xsecsyst_tree->SetBranchAddress("NonRESBGvbarnCC2pi",  &NonRESBGvbarnCC2pi   );
  xsecsyst_tree->SetBranchAddress("NonRESBGvbarnNC1pi",  &NonRESBGvbarnNC1pi   );
  xsecsyst_tree->SetBranchAddress("NonRESBGvbarnNC2pi",  &NonRESBGvbarnNC2pi   );


*/
