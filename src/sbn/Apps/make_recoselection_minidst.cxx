//____________________________________________________________________________
/*!

  \app       valor_sbn-make_recoselection_minidst

  \brief     Converts input recoselection analysis DSTs to the VALOR mini-DST format.

  \syntax    valor_sbn-make_recoselection_minidst
                --input  input_analysis_file.root
                --output output_file_containing_valor_minidst.root
                --format format_of_the_input_file <hpgartpc, lartpc, fgt>
               [--disable-checks]


  The enum simb::int_type_ from LarSoft (copied from MCNeutrino.h, in v06_05_00)
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
   
  The enum simb::int_type_ from LarSoft (copied from MCNeutrino.h, in v06_05_00)
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
 
  \author    Rhiannon Jones <rhiannon.jones \at liverpool.ac.uk>
  University of Liverpool

  \created   March 2019

  \copyright Copyright (c) 2010-2020, The VALOR group. All rights reserved.

*/
//____________________________________________________________________________

// System
#include <string>
#include <iostream>
#include <sstream>
#include <map>
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
//#include "core/Event.hh"

using std::string;
using std::ostringstream;

void GetCommandLineArgs (int /*argc*/, char ** /*argv*/);
static const string gTreeName = "valor_tree";
static const string gPOTTreeName = "subrun_tree";
static const int gPrintEveryNEvents   = 50000;

typedef enum ExclusiveTopology{

  kUnknownTopology              = -1,
  kCC0Pi                        =  0,
  kCC1Pi                        =  1,
  kCC2Pi                        =  2,
  kCCPi0                        =  3,
  kCCOther                      =  4

} ExclusiveTopology_t;

// The enum simb::int_type_ from LarSoft (copied from MCNeutrino.h, in v06_05_00)
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

typedef enum EScatCode{
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
  kScatIMDAnnihilation    = 14
} ScatCode_t;
 
bool CheckSample(const int &reco, 
                 const valor::conv::Sample_t &sample, 
                 const bool &other);

//___________________________________________________________________
int main(int argc, char ** argv)
{
  // Set GENIE print level
  genie::GHepRecord::SetPrintLevel(genie::RunOpt::Instance()->EventRecordPrintLevel());

  using namespace valor;

  CmdLnArgList arg;
  arg.Read(argc,argv, "$VALOR_EXPT/config/apps/make_recoselection_minidst.arg");
  LOG("valor_sbn", pNOTICE) << arg;

  std::string thresholds = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  Messenger::Instance()->Configure(thresholds);

  string opt_beam_name         = arg.GetString("beam");
  string opt_sample_name       = arg.GetString("sample");
  string opt_output_name       = arg.GetString("output");
  string opt_input_name        = arg.GetString("input");
  bool   opt_disable_checks    = arg.GetBool("disable-checks");
  bool   other_sample          = arg.GetBool("other-sample");

  // Get the POT
  // open the ROOT file and get the TTree & its header
  TChain * subrun_tree = new TChain(gPOTTreeName.c_str());
  subrun_tree->Add(opt_input_name.c_str());
  if(!subrun_tree || !subrun_tree->GetEntries()) {
    LOG("make_recoselection_minidst", pFATAL) 
      << "Unable to read " << gPOTTreeName
      <<" from "<< opt_input_name;
    exit(1);
  }

  Long64_t nsub = subrun_tree->GetEntries();
  LOG("make_recoselection_minidst", pNOTICE) 
    << "Input subrun tree has " << nsub << ((nsub==1) ? " entry." : " entries.");

  double mcsample_pot       = -1.;
  double pot_entry = -1.;
  subrun_tree->SetBranchAddress("pot", &pot_entry);
  for(Long64_t n = 0; n < nsub; ++n){
    subrun_tree->GetEntry(n);
    mcsample_pot += pot_entry;
  }

  if(mcsample_pot < 1)
    LOG("make_recoselection_minidst", pNOTICE) << "POT in file is less than 1 ";

  if(mcsample_pot == -1.){
    LOG("make_recoselection_minidst", pFATAL) 
      << "Not able to access MCSample POT from " << opt_input_name;
    exit(1);
  }

  LOG("make_recoselection_minidst",pINFO) << " POT in file : " << mcsample_pot << "\n";

  conv::Sample_t sample = util::SampleFromString(opt_sample_name);
  assert(sample != conv::ksUndefined);

  // If we want to define 'other' as anything but the sample defined in the arguments, set this to true
  if(other_sample)
    VLOG("valor_sbn", pNOTICE) << " Chosen to look for events which do NOT fall under the definition of the sample, "
                               << util::AsString(sample);

  conv::BeamConf_t beam = util::BeamConfFromString(opt_beam_name);
  assert(beam != conv::kbUndefined);

  int    valor_minidst_sample         = sample;
  int    valor_minidst_beam           = -1;  // see Conventions/BeamConf.h
  int    valor_minidst_reac_mode      = -1;  // see Conventions/ReacMode.h
  int    valor_minidst_target         = -1;  // nuclear target -  GENIE PDG convention
  double valor_minidst_baseline       = -1.;
  double valor_minidst_enu_true       = -1.; // true neutrino energy, in GeV
  double valor_minidst_Q2_true        = -1.; // true neutrino Q2
  double valor_minidst_enu_reco       = -1.; // reco neutrino energy, in GeV
  double valor_minidst_mu_momentum    = -1.; // reco muon momentum
  double valor_minidst_mu_cos_z       = -1.; // reco muon cos(angle to z)
  double valor_minidst_y_reco         = -1.; // inelasticity
  double valor_minidst_wght_pot       = -1.; // POT weight
  double valor_minidst_wght           = -1.; // misc weight
  double valor_minidst_wght_smear     = -1.; // energy smearing weight
  double valor_minidst_reco_exclusive = -1.; // exclusive reconstructed topology
  double valor_minidst_true_exclusive = -1.; // exclusive true topology

  TFile fout(opt_output_name.c_str(),"recreate");
  fout.cd();

  TTree * valor_minidst =
    new TTree("valor_sbn_minidst","Mini-DST input for VALOR/SBN fit");

  valor_minidst->Branch("beam"          , &valor_minidst_beam          ,"beam/I"           );
  valor_minidst->Branch("sample"        , &valor_minidst_sample        ,"sample/I"         );
  valor_minidst->Branch("reac_mode"     , &valor_minidst_reac_mode     ,"reac_mode/I"      );
  valor_minidst->Branch("target"        , &valor_minidst_target        ,"target/I"         );
  valor_minidst->Branch("baseline"      , &valor_minidst_baseline      ,"baseline/D"       );
  valor_minidst->Branch("enu_true"      , &valor_minidst_enu_true      ,"enu_true/D"       );
  valor_minidst->Branch("Q2_true"       , &valor_minidst_Q2_true       ,"q2_true/D"        );
  valor_minidst->Branch("enu_reco"      , &valor_minidst_enu_reco      ,"enu_reco/D"       );
  valor_minidst->Branch("enu_reco"      , &valor_minidst_enu_reco      ,"enu_reco/D"       );
  valor_minidst->Branch("mu_momentum"   , &valor_minidst_mu_momentum   ,"mu_momentum/D"    );
  valor_minidst->Branch("mu_cos_z"      , &valor_minidst_mu_cos_z      ,"mu_cos_z/D"       );
  valor_minidst->Branch("y_reco"        , &valor_minidst_y_reco        ,"y_reco/D"         );
  valor_minidst->Branch("wght_pot"      , &valor_minidst_wght_pot      ,"wght_pot/D"       );
  valor_minidst->Branch("wght"          , &valor_minidst_wght          ,"wght/D"           );
  valor_minidst->Branch("wght_smear"    , &valor_minidst_wght_smear    ,"wght_smear/D"     );
  valor_minidst->Branch("reco_exclusive", &valor_minidst_reco_exclusive,"reco_exclusive/D" );
  valor_minidst->Branch("true_exclusive", &valor_minidst_true_exclusive,"true_exclusive/D" );


  // open the ROOT file and get the TTree & its header
  TChain * analysis_tree = new TChain(gTreeName.c_str());
  analysis_tree->Add(opt_input_name.c_str());
  if(!analysis_tree || !analysis_tree->GetEntries()) {
    VLOG("valor_sbn", pFATAL)
      << "Unable to read " << gTreeName
      <<" from "<< opt_input_name;
    exit(1);
  }

  Long64_t nev = analysis_tree->GetEntries();
  VLOG("valor_sbn", pNOTICE)
    << "Input analysis tree has " << nev << ((nev==1) ? " entry." : " entries.");
  analysis_tree->GetEntry(0);


  // Variables to get from analysis tree
  bool iscc           = false;
  bool isnc           = false;
  double baseline     = -999.;
  double enu_true     = -999.;
  double enu_reco     = -999.;
  double qsqr         = -999.;
  double mu_momentum  = -999.;
  double mu_cos_z     = -999.;
  int nu_pdg          = -1;
  int larsoft_mode    = -1;
  int nkaons          = -1;
  int npip            = -1;
  int npim            = -1;
  int npi0            = -1;
  int true_exclusive  = -1;
  int reco_exclusive  = -1;

  analysis_tree->SetBranchAddress("iscc",           &iscc            );
  analysis_tree->SetBranchAddress("isnc",           &isnc            );
  analysis_tree->SetBranchAddress("baseline",       &baseline        );
  analysis_tree->SetBranchAddress("nu_pdg",         &nu_pdg          );
  analysis_tree->SetBranchAddress("enu_true",       &enu_true        );
  analysis_tree->SetBranchAddress("enu_reco",       &enu_reco        );
  analysis_tree->SetBranchAddress("mu_momentum",    &mu_momentum     );
  analysis_tree->SetBranchAddress("mu_cos_z",       &mu_cos_z        );
  analysis_tree->SetBranchAddress("qsqr",           &qsqr            );
  analysis_tree->SetBranchAddress("mode",           &larsoft_mode    );
  analysis_tree->SetBranchAddress("nkaons",         &nkaons          );
  analysis_tree->SetBranchAddress("npip",           &npip            );
  analysis_tree->SetBranchAddress("npim",           &npim            );
  analysis_tree->SetBranchAddress("npi0",           &npi0            );
  analysis_tree->SetBranchAddress("true_topology",  &true_exclusive  );
  analysis_tree->SetBranchAddress("reco_topology",  &reco_exclusive  );

  //
  // event loop
  //

  std::vector<int> nev_accept_by_mode;
  for (int im = 0 ; im < valor::conv::kNReacModes; im++) {
    nev_accept_by_mode.push_back(0);
  }

  Long64_t nev_accept = 0;
  Long64_t nev_reject = 0;

  for(Long64_t iev = 0; iev < nev; iev++) {

    if (gPrintEveryNEvents && !(iev%gPrintEveryNEvents)) {
      VLOG("valor_sbn", pNOTICE) << "** Reading event: " << iev
        <<" - so far accepted " << nev_accept;
    }
    else {
      VLOG("valor_sbn", pDEBUG) << "** Reading event: " << iev
        <<" - so far accepted " << nev_accept;
    }

    analysis_tree->GetEntry(iev);

    // Before we do anything, make sure the current event fits the description of the sample
    if(!CheckSample(reco_exclusive,sample,other_sample)){
      LOG("valor_sbn",pINFO)   << "Current event has \n" 
                               << npip << " charged pions, \n " 
                               << npi0 << " pi0s and does not match the desired sample type: " 
                               << util::AsString(sample) << "\n Skipping.";
      nev_reject++;
      continue;
    }

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

    conv::NuFlavour_t final_flav = valor::util::FlavourFromPDG(nu_pdg);
    conv::NuFlavour_t init_flav = final_flav;

    // Get the real valor mode
    conv::ReacMode_t  reac_mode  = valor::util::ReacTypeToMode(reac,init_flav,final_flav);

    if(!opt_disable_checks) {
      //
      // ignore events that can not be used in the VALOR analysis
      //
      if(reac_mode == conv::kmUndefined) {
        VLOG("valor_sbn", pWARN) << "- Rejecting event [bad mode]\n";
        continue;
      }
    }

    VLOG("valor_sbn",pDEBUG) << "Read event: "
      << "Etrue         = "<< enu_true  << " GeV; "
      << "LArSoft mode  = "<< larsoft_mode  << "; ";

    // Only ever dealing with numuCC here, change if this app becomes more universal
    if(other_sample)
      valor_minidst_sample = valor::util::SampleFromString("numuCCoth");
    else
      valor_minidst_sample     = sample;

    valor_minidst_beam           = beam;
    valor_minidst_baseline       = baseline/1000.; 
    valor_minidst_reac_mode      = reac_mode;
    valor_minidst_enu_true       = enu_true;
    valor_minidst_wght           = 1.;
    valor_minidst_Q2_true        = qsqr;
    valor_minidst_wght_pot       = 1./mcsample_pot;
    valor_minidst_target         = 1000180400; // Argon40
    valor_minidst_y_reco         = 0.5; // FORCE y=0.5 for now
    valor_minidst_mu_momentum    = mu_momentum;
    valor_minidst_mu_cos_z       = mu_cos_z;
    valor_minidst_true_exclusive = true_exclusive;
    valor_minidst_reco_exclusive = reco_exclusive;

    VLOG("valor_sbn", pINFO)
      << "\n Information copied to VALOR SBN recoselection Mini-DST: "
      << "\n Beam          = " << valor_minidst_beam
      << "\n Baseline      = " << valor_minidst_baseline   
      << "\n Sample        = " << valor_minidst_sample
      << "\n Reaction mode = " << valor_minidst_reac_mode
      << "\n Target        = " << valor_minidst_target
      << "\n Q2 (true)     = " << valor_minidst_Q2_true << " GeV^2"
      << "\n Ev (true)     = " << valor_minidst_enu_true << " GeV"
      << "\n Pmu (reco)    = " << valor_minidst_mu_momentum << "GeV/c^2"
      << "\n P cosZ (reco) = " << valor_minidst_mu_cos_z
      << "\n y (reco)      = " << valor_minidst_y_reco
      << "\n POT weight    = " << valor_minidst_wght_pot
      << "\n Smear weight  = " << valor_minidst_wght_smear
      << "\n Reco topology = " << valor_minidst_reco_exclusive
      << "\n True topology = " << valor_minidst_true_exclusive;

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
    VLOG("valor_sbn", pINFO)
      << "\n Ev (reco)     = " << valor_minidst_enu_reco << " GeV";

    valor_minidst->Fill();
    nev_accept += 1;
  } // event loop

  double f = 100. * (double)nev_accept / (double)nev;
  double r = 100. * (double)nev_reject / (double)nev;
  VLOG("valor_sbn", pNOTICE) <<
    "Used " << f << "% (" << nev_accept << "/" << nev
    << ") of input events.";
  VLOG("valor_sbn", pNOTICE) <<
    "Rejected " << r << "% (" << nev_reject << "/" << nev
    << ") of input events.";

  std::cout << " Number in valor tree : " << valor_minidst->GetEntries() << std::endl;
  
  // Saving VALOR mini-FST to output file
  VLOG("valor_sbn", pNOTICE)
    << "Saving VALOR/SBN mini-DST to: " << opt_output_name;
  valor_minidst->Write();
  fout.Close();

  VLOG("valor_sbn", pNOTICE)  << "Done!";

  return 0;
}
bool CheckSample(const int &reco, 
                 const valor::conv::Sample_t &sample, 
                 const bool &other){
  
  if(sample == valor::conv::ksNuMuCC || sample == valor::conv::ksNuMuLikeCChigh) return true;
  else if(sample == valor::conv::ksNuMuCC0piNtrk){
    if(reco == kCC0Pi)
      return ((other) ? false : true);
    else return ((other) ? true : false);
  }
  else if(sample == valor::conv::ksNuMuCC1piC){
    if(reco == kCC1Pi)
      return ((other) ? false : true);
    else return ((other) ? true : false);
  }
  else if(sample == valor::conv::ksNuMuCC1pi0){
    if(reco == kCCPi0)
      return ((other) ? false : true);
    else return ((other) ? true : false);
  }
  else if(sample == valor::conv::ksNuMuCC2piC){
    if(reco == kCC2Pi)
      return ((other) ? false : true);
    else return ((other) ? true : false);
  }
  else if(sample == valor::conv::ksNuMuCCoth){
    if(reco == kCCOther)
      return ((other) ? false : true);
    else return ((other) ? true : false);
  }
  else{
    LOG("valor_sbn",pFATAL) << "Error: Desired sample " << valor::util::AsString(sample) << " is not distinguishable from the information in this set of events ";
    return false;
  }
}
