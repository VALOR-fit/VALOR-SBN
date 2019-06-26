//____________________________________________________________________________
/*!

  \app       valor_dune-make_sbncode_minidst

  \brief     Converts input SBNCode analysis DSTs to the VALOR mini-DST format.

  \syntax    valor_dune-make_sbncode_minidst 
  --input  input_analysis_file.root
  --output output_file_containing_valor_minidst.root
  --format format_of_the_input_file <hpgartpc, lartpc, fgt>
  [--disable-checks]

  \author    Rhiannon Jones <rhiannon.jones \at liverpool.ac.uk>
             University of Liverpool

  \created   March 2019

  \copyright (c) 2010-2019, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <utility>

//
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TBranch.h>
#include <TLeaf.h>
#include <TSystem.h>

// genie
#include "dune/GENIEUtilities/GENIEIncludes.h"

// valor/dune
#include "valor/Conventions/Constants.h"
#include "valor/Messenger/Messenger.h"
#include "valor/Utilities/Env.h"
#include "valor/CmdLine/CmdLnArgList.h"
#include "valor/Utilities/UtlNumStat.h"
#include "valor/Utilities/UtlStyle.h"
#include "valor/Utilities/UtlStr.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Utilities/Rnd.h"

#include "valor/Conventions/BeamConf.h"
#include "valor/Conventions/ReacMode.h"
#include "valor/Conventions/Sample.h"

#include "dune/GENIEUtilities/GENIEIncludes.h"
#include "dune/GENIEUtilities/UtlEventRec.h"

#include "core/Event.hh"

using std::string;
using std::ostringstream;

void GetCommandLineArgs (int /*argc*/, char ** /*argv*/);
static const string gTreeName = "sbnana";

static const int gPrintEveryNEvents   = 50000;

/***
 *
 * This is for the /pnfs/sbnd/persistent/users/gputnam/numu_simulation_reweight/processed_2.a sample
 *
 * Wiki is here: https://cdcvs.fnal.gov/redmine/projects/sbncode/wiki/Fitter_Validation_NuMu_sample
 *
 * POT calculated by adding together every subrun totgootpot value in the processed event file
 *
 */
static const double proposalPOTSBND   = 1.4182069e19; 
static const double modernPOTSBND     = 1.4182069e19; 
static const double proposalPOTUBOONE = 2.5698932e20; 
static const double modernPOTUBOONE   = 2.5698932e20; 
static const double proposalPOTICARUS = 2.8184718e19;
static const double modernPOTICARUS   = 2.8184718e19;

static const double appProposalPOTSBNDNumu   = 1.3896325e19;
static const double appProposalPOTSBNDInt    = 5.1225376e21;
static const double appProposalPOTSBNDOsc    = 3.3940737e19;
static const double appProposalPOTUBOONENumu = 2.5698932e20;
static const double appProposalPOTUBOONEInt  = 1.4193883e23;
static const double appProposalPOTUBOONEOsc  = 9.5440115e20;
static const double appProposalPOTICARUSNumu = 2.8184718e19;
static const double appProposalPOTICARUSInt  = 8.3903526e21;
static const double appProposalPOTICARUSOsc  = 9.8446183e19;

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

// enum definition for the sbn mc sample we are looking at
// For now, only important for accessing the correct POT from above
typedef enum EMCSample{
  kUnknownSample               = -1, 
  kSBNDDisappearanceProposal   = 0,
  kSBNDDisappearanceModern     = 1,
  kUBOONEDisappearanceProposal = 2,
  kUBOONEDisappearanceModern   = 3,
  kICARUSDisappearanceProposal = 4,
  kICARUSDisappearanceModern   = 5,

  kSBNDAppearanceNumuProposal   = 6,
  kSBNDAppearanceIntProposal    = 7,
  kSBNDAppearanceOscProposal    = 8,
  kUBOONEAppearanceNumuProposal = 9,
  kUBOONEAppearanceIntProposal  = 10,
  kUBOONEAppearanceOscProposal  = 11,
  kICARUSAppearanceNumuProposal = 12,
  kICARUSAppearanceIntProposal  = 13,
  kICARUSAppearanceOscProposal  = 14

} MCSample_t;

//___________________________________________________________________
int main(int argc, char ** argv)
{
  // Set GENIE print level
  genie::GHepRecord::SetPrintLevel(genie::RunOpt::Instance()->EventRecordPrintLevel());
  
  using namespace valor;
  
  Env::Instance()->AutoSet("dune");
 
  CmdLnArgList arg;
  arg.Read(argc,argv, "$VALOR_DUNE/config/apps/make_sbncode_minidst.arg");
  LOG("make_sbncode_minidst", pNOTICE) << arg;
  
  std::string thresholds = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  Messenger::Instance()->Configure(thresholds);
  
  string opt_beam_name         = arg.GetString("beam");
  string opt_sample_name       = arg.GetString("sample");
  string opt_output_name       = arg.GetString("output");
  string opt_input_name        = arg.GetString("input");
  int    opt_mcsample          = arg.GetInt("mcsample");
  bool   opt_disable_checks    = arg.GetBool("disable-checks");

  double mcsample_pot = -1.;
  if(opt_mcsample == kUnknownSample){
    VLOG("make_sbncode_minidst", pFATAL) 
      << "MCSample not defined ";
    exit(1);
  }
  
  bool is_appearance = false;
  bool is_intrinsic  = false;
  
  // Get the POT
  // Disappearance
  if(opt_mcsample == kSBNDDisappearanceProposal)
    mcsample_pot = proposalPOTSBND;
  if(opt_mcsample == kSBNDDisappearanceModern)
    mcsample_pot = modernPOTSBND;
  
  if(opt_mcsample == kUBOONEDisappearanceProposal)
    mcsample_pot = proposalPOTUBOONE;
  if(opt_mcsample == kUBOONEDisappearanceModern)
    mcsample_pot = modernPOTUBOONE;

  if(opt_mcsample == kICARUSDisappearanceProposal)
    mcsample_pot = proposalPOTICARUS;
  if(opt_mcsample == kICARUSDisappearanceModern)
    mcsample_pot = modernPOTICARUS;


  // Appearance POTs
  if(opt_mcsample == kSBNDAppearanceNumuProposal){
    mcsample_pot = appProposalPOTSBNDNumu;
    is_appearance = true;
  }
  if(opt_mcsample == kSBNDAppearanceIntProposal){
    mcsample_pot = appProposalPOTSBNDInt;
    is_appearance = true;
    is_intrinsic = true;
  }
  if(opt_mcsample == kSBNDAppearanceOscProposal){
    mcsample_pot = appProposalPOTSBNDOsc;
    is_appearance = true;
  }
  
  if(opt_mcsample == kUBOONEAppearanceNumuProposal){
    mcsample_pot = appProposalPOTUBOONENumu;
    is_appearance = true;
  }
  if(opt_mcsample == kUBOONEAppearanceIntProposal){
    mcsample_pot = appProposalPOTUBOONEInt;
    is_appearance = true;
    is_intrinsic = true;
  }
  if(opt_mcsample == kUBOONEAppearanceOscProposal){
    mcsample_pot = appProposalPOTUBOONEOsc;
    is_appearance = true;
  }
  
  if(opt_mcsample == kICARUSAppearanceNumuProposal){
    mcsample_pot = appProposalPOTICARUSNumu;
    is_appearance = true;
  }
  if(opt_mcsample == kICARUSAppearanceIntProposal){
    mcsample_pot = appProposalPOTICARUSInt;
    is_appearance = true;
    is_intrinsic = true;
  }
  if(opt_mcsample == kICARUSAppearanceOscProposal){
    mcsample_pot = appProposalPOTICARUSOsc;
    is_appearance = true;
  }
  
  if(mcsample_pot == -1.){
    VLOG("make_sbncode_minidst", pFATAL) 
      << "Not able to access MCSample POT from " << opt_mcsample;
    exit(1);
  }

  conv::Sample_t sample = util::SampleFromString(opt_sample_name);
  assert(sample != conv::ksUndefined);
 
  conv::BeamConf_t beam = util::BeamConfFromString(opt_beam_name);
  assert(beam != conv::kbUndefined);

  int    valor_minidst_sample       = sample;
  int    valor_minidst_beam         = -1;  // see Conventions/BeamConf.h 
  int    valor_minidst_reac_mode    = -1;  // see Conventions/ReacMode.h 
  int    valor_minidst_target       = -1;  // nuclear target -  GENIE PDG convention
  double valor_minidst_enu_true     = -1.; // true neutrino energy, in GeV
  double valor_minidst_Q2_true      = -1.; // true neutrino energy, in GeV
  double valor_minidst_enu_reco     = -1.; // reco neutrino energy, in GeV
  double valor_minidst_y_reco       = -1.; // inelasticity
  double valor_minidst_wght_pot     = -1.; // POT weight 
  double valor_minidst_wght         = -1.; // misc weight 
  double valor_minidst_wght_smear   = -1.; // energy smearing weight 
  
  TFile fout(opt_output_name.c_str(),"recreate");
  fout.cd();

  TTree * valor_minidst = 
    new TTree("valor_sbncode_mini_dst","Mini-DST input for VALOR/DUNE SBNCode Fit");

  valor_minidst->Branch("beam"      , &valor_minidst_beam        ,"beam/I"       );
  valor_minidst->Branch("sample"    , &valor_minidst_sample      ,"sample/I"     );
  valor_minidst->Branch("reac_mode" , &valor_minidst_reac_mode   ,"reac_mode/I"  );
  valor_minidst->Branch("target"    , &valor_minidst_target      ,"target/I"     );
  valor_minidst->Branch("enu_true"  , &valor_minidst_enu_true    ,"enu_true/D"   );
  valor_minidst->Branch("Q2_true"   , &valor_minidst_Q2_true     ,"q2_true/D"    );
  valor_minidst->Branch("enu_reco"  , &valor_minidst_enu_reco    ,"enu_reco/D"   );
  valor_minidst->Branch("y_reco"    , &valor_minidst_y_reco      ,"y_reco/D"     );
  valor_minidst->Branch("wght_pot"  , &valor_minidst_wght_pot    ,"wght_pot/D"   );
  valor_minidst->Branch("wght"      , &valor_minidst_wght        ,"wght/D"       );
  valor_minidst->Branch("wght_smear", &valor_minidst_wght_smear  ,"wght_smear/D" );

  // open the ROOT file and get the TTree & its header

  TChain * analysis_tree = new TChain(gTreeName.c_str());
  analysis_tree->Add(opt_input_name.c_str());
  if(!analysis_tree || !analysis_tree->GetEntries()) {
    VLOG("make_sbncode_minidst", pFATAL) 
      << "Unable to read " << gTreeName
      <<" from "<< opt_input_name;
    exit(1);
  }

  Long64_t nev = analysis_tree->GetEntries();
  VLOG("make_sbncode_minidst", pNOTICE) 
    << "Input analysis tree has " << nev << ((nev==1) ? " entry." : " entries.");
  analysis_tree->GetEntry(0);
  
  Event *pevent;
  analysis_tree->SetBranchAddress("events", &pevent);
  Event &event = *pevent;

/*  TLeaf *l_initpdg;
  if(is_appearance)
    l_initpdg = analysis_tree->GetBranch("truth.neutrino.initpdg")->GetLeaf("truth.neutrino.initpdg");*/
      
  //
  // event loop
  //

  Long64_t nev_accept = 0;
  
  std::vector<int> nev_accept_by_mode;
  for (int im = 0 ; im < valor::conv::kNReacModes; im++) {
    nev_accept_by_mode.push_back(0);
  }
  
  int last_tree_number = -1; // store which number file we're in, so we can count each tree's weight once

  for(Long64_t iev = 0; iev < nev; iev++) {
    
    analysis_tree->GetEntry(iev);

    if (gPrintEveryNEvents && !(iev%gPrintEveryNEvents)) {
      VLOG("make_sbncode_minidst", pNOTICE) << "** Reading event: " << iev;
    }
    else {
      VLOG("make_sbncode_minidst", pDEBUG) << "** Reading event: " << iev;
    }
    
    int iscc        = false;
    int isnc        = false;
    int nu_pdg      = -1;
    int init_pdg    = -1;

    //int init_pdg    = -1;
    double enu_true =  -999.;
    double enu_reco =  -999.;
    double Q2s      =  -999.;

    int nipip    = 0;
    int nipim    = 0;
    int nipi0    = 0;
    int nikp     = 0;
    int nikm     = 0;
    int nik0     = 0;
    int niak0    = 0;
    /*int nin      = 0;
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
    int ninuc    = 0;*/

    int larsoft_mode = -1;

    std::vector<Event::Interaction> &truth = event.truth;
    std::vector<Event::RecoInteraction> &reco = event.reco;

    if(truth.size() == 0 || reco.size() == 0){
      VLOG("make_sbncode_minidst", pNOTICE) 
        << "The number of truth entries is " << truth.size() << " and reco " << reco.size() << ", neither should be 0";
      continue;      
    }

    //for(unsigned int t = 0; t < truth.size(); ++t){
      std::vector<Event::FinalStateParticle> &fsps = truth[0].finalstate;
      iscc = truth[0].neutrino.iscc;
      isnc = truth[0].neutrino.isnc;
      nu_pdg = truth[0].neutrino.pdg;
      enu_true = truth[0].neutrino.energy;
      Q2s = truth[0].neutrino.Q2;
      larsoft_mode = truth[0].neutrino.genie_intcode;

      if(fsps.size() == 0){
        VLOG("make_sbncode_minidst", pNOTICE) 
          << "The number of final state particles is " << fsps.size() << ", this shouldn't be 0, skipping truth block [no particles]";
        continue;      
      }
      // Particle counting
      for(unsigned int p = 0; p < fsps.size(); ++p){
  //      if(fsps[p].status_code != 1) continue;
        if(     fsps[p].pdg == genie::kPdgPiP         ) nipip++;
        else if(fsps[p].pdg == genie::kPdgPiM         ) nipim++;
        else if(fsps[p].pdg == genie::kPdgPi0         ) nipi0++;
        else if(fsps[p].pdg == genie::kPdgKP          ) nikp++;
        else if(fsps[p].pdg == genie::kPdgKM          ) nikm++;
        else if(fsps[p].pdg == genie::kPdgK0          ) nik0++;
       /* else if(fsps[p].pdg == genie::kPdgProton      ) nip++;
        else if(fsps[p].pdg == genie::kPdgAntiProton  ) niap++;
        else if(fsps[p].pdg == genie::kPdgNeutron     ) nin++;
        else if(fsps[p].pdg == genie::kPdgAntiNeutron ) nian++;
        else if(fsps[p].pdg == genie::kPdgAntiK0      ) niak0++;
        else if(fsps[p].pdg == genie::kPdgGamma       ) nig++;
        else if(fsps[p].pdg == genie::kPdgElectron    ) niem++;
        else if(fsps[p].pdg == genie::kPdgPositron    ) niep++;
        else if(fsps[p].pdg == genie::kPdgMuon        ) nimu++;
        else if(fsps[p].pdg == genie::kPdgAntiMuon    ) nimup++;
        else if(fsps[p].pdg == genie::kPdgAntiMuon    ) nimup++;
        else if(fsps[p].pdg == 14 || fsps[p].pdg == -14 || fsps[p].pdg == 12 || fsps[p].pdg == -12) ninu++;
        else if(fsps[p].pdg > 1e4) ninuc++;
        else niother++; */
        // Currently not using niother as the only others seem to be deltas and etas
        // These will eventually be removed when isStableFinalState variable is available in the analysis trees
      }
      
      // Construct the reaction mode
      conv::ReacType_t reac = conv::kmtUndefined;
      if (iscc) {
        if      (larsoft_mode==kLArQE                ) { reac = conv::kmtCCQE;    }
        else if (larsoft_mode==kLArMEC               ) { reac = conv::kmtCCMEC;   }
        else if (larsoft_mode==kLArCoh               ) { reac = conv::kmtCCcoh;   }
        else if (larsoft_mode==kLArIMDAnnihilation   ) { reac = conv::kmtCCIMD;   }
        else if (larsoft_mode==kLArElectronScattering) { reac = conv::kmtCCELScat;}

        else { // start counting pions
          if      (nikp || nik0 || nikm           )  { reac = conv::kmtCCoth;}
          else if (nipip+nipim == 1 && nipi0 == 0 )  { reac = conv::kmtCC1piC;}
          else if (nipip+nipim == 0 && nipi0 == 1 )  { reac = conv::kmtCC1pi0;}
          else if (nipip+nipim == 2 && nipi0 == 0 )  { reac = conv::kmtCC2piC;}
          else if (nipip+nipim == 0 && nipi0 == 2 )  { reac = conv::kmtCC2pi0;}
          else if (nipip+nipim == 1 && nipi0 == 1 )  { reac = conv::kmtCCpiCpi0;}
          else                                      { reac = conv::kmtCCoth;}
        }
      }
      else if (isnc) {
        if      (larsoft_mode==kLArQE                ) { reac = conv::kmtNCEL;    }
        else if (larsoft_mode==kLArMEC               ) { reac = conv::kmtNCMEC;   }
        else if (larsoft_mode==kLArCoh               ) { reac = conv::kmtNCcoh;   }
        else if (larsoft_mode==kLArElectronScattering) { reac = conv::kmtNCELScat;}

        else { // start counting pions
          if      (nikp || nik0 || nikm           )  { reac = conv::kmtNCoth;}
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

      else reac = conv::kmtOther;

      conv::NuFlavour_t final_flav = valor::util::FlavourFromPDG(nu_pdg);
      conv::NuFlavour_t init_flav;
      
      // If we are looking at the appearance samples, get the initial neutrino pdg from the file
      if(is_appearance){
        init_pdg = truth[0].neutrino.initpdg;
        init_flav = valor::util::FlavourFromPDG(init_pdg);
      }

      // If we are looking at the disappearance samples, initial flavour = final flavour
      else init_flav = final_flav;
      
      // Get the real valor mode
      conv::ReacMode_t  reac_mode  = valor::util::ReacTypeToMode(reac,init_flav,final_flav);

      if(!opt_disable_checks) {
        //
        // ignore events that can not be used in the VALOR analysis
        //
        if(reac_mode == conv::kmUndefined) {
          VLOG("make_sbncode_minidst", pWARN) << "- Rejecting event [bad mode]\n"; 
          continue;
        }
        if(is_appearance && isnc && init_flav != final_flav){
          VLOG("make_sbncode_minidst", pWARN) << "- Rejecting event [oscillated nc]\n"; 
          continue;
        }
        if(is_appearance && (init_pdg == 12 || init_pdg == -12) && (!is_intrinsic)){
          VLOG("make_sbncode_minidst", pWARN) << "- Rejecting event [nue not from intrinsic]\n"; 
          continue;
        }
      }

      VLOG("make_sbncode_minidst",pDEBUG) << "Read event: "
        << "Etrue         = "<< enu_true  << " GeV; "
        << "LArSoft mode  = "<< larsoft_mode  << "; ";

      valor_minidst_sample    = sample; 
      valor_minidst_beam      = beam; 
      valor_minidst_reac_mode = reac_mode;
      valor_minidst_enu_true  = enu_true; 
      valor_minidst_wght      = 1.;
      valor_minidst_Q2_true   = Q2s;
      valor_minidst_wght_pot  = 1./mcsample_pot; 
      valor_minidst_target    = 1000180400; // Argon40
      //valor_minidst_y_reco    = 0.5; // FORCE y=0.5 for now

      VLOG("make_sbncode_minidst", pINFO) 
        << "\n Information copied to VALOR DUNE/SBNCode Mini-DST: "
        << "\n Beam          = " << valor_minidst_beam   
        << "\n Sample        = " << valor_minidst_sample    
        << "\n Reaction mode = " << valor_minidst_reac_mode 
        << "\n Target        = " << valor_minidst_target
        << "\n Q2 (true)     = " << valor_minidst_Q2_true << " GeV^2"
        << "\n Ev (true)     = " << valor_minidst_enu_true << " GeV"
        << "\n y (reco)      = " << valor_minidst_y_reco    
        << "\n POT weight    = " << valor_minidst_wght_pot
        << "\n Smear weight  = " << valor_minidst_wght_smear;

    //} // true loop

    //for(unsigned int r = 0; r < reco.size(); ++r){
      enu_reco = reco[0].reco_energy;
      
      VLOG("make_sbncode_minidst",pDEBUG) << "Read event: "
        << "Ereco         = "<< enu_reco  << " GeV; ";
      if(!opt_disable_checks) {
        
        //
        // ignore events that can not be used in the VALOR analysis
        //
        if(enu_reco <= 0) {
          VLOG("make_sbncode_minidst", pINFO) << "- Rejecting event [Ev (reco) <= 0]: "<<enu_reco;
          continue;
        }

        VLOG("make_sbncode_minidst", pINFO) << "+ Accepting event";
      }
      
      valor_minidst_enu_reco  = enu_reco; 
      VLOG("make_sbncode_minidst", pNOTICE) 
        << "\n Ev (reco)     = " << valor_minidst_enu_reco << " GeV"; 
      
    //} // reco loop 
    valor_minidst->Fill();
  } // event loop

  std::cout << " Number in valor tree : " << valor_minidst->GetEntries() << std::endl;
  /*
  for (unsigned int im = 0 ; im < nev_accept_by_mode.size(); im++) {
    valor::conv::ReacMode_t m = (valor::conv::ReacMode_t)im;
    VLOG("make_sbncode_minidst", pNOTICE) << "Selected "<<nev_accept_by_mode[im]<<" events of mode "<<valor::util::AsString(m);
  }
  
  double f = 100. * (double)nev_accept / (double)nev;
  VLOG("make_sbncode_minidst", pNOTICE) <<
    "Used " << f << "% (" << nev_accept << "/" << nev 
    << ") of input events.";
    
  //~ VLOG("make_sbncode_minidst", pNOTICE) <<
    //~ "Total POT read: "<<total_pot_read;
*/
  // Saving VALOR mini-FST to output file 
  VLOG("make_sbncode_minidst", pNOTICE) 
    << "Saving VALOR/DUNE mini-DST to: " << opt_output_name;
  valor_minidst->Write();  
  fout.Close();

  VLOG("make_sbncode_minidst", pNOTICE)  << "Done!";

  return 0;
}
