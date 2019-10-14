//____________________________________________________________________________
/*!

  \app       valor_dune-make_sbncode_minidst

  \brief     Converts input SBNCode analysis DSTs to the VALOR mini-DST format.

  \syntax    valor_dune-make_sbncode_minidst 
  --input  input_analysis_file.root
  --output output_file_containing_valor_minidst.root
  [--write-universes] optionally write out the systematic variations
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

#include "dune/Utilities/DoExperimentSetup.h"
#include "dune/GENIEUtilities/GENIEIncludes.h"
#include "dune/GENIEUtilities/UtlEventRec.h"

#include "core/Event.hh"

using std::string;
using std::ostringstream;

void GetCommandLineArgs (int /*argc*/, char ** /*argv*/);
static const string gTreeName       = "sbnreco";
static const string gSubRunTreeName = "sbnsubrun";

static const int gPrintEveryNEvents   = 50000;

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

//___________________________________________________________________
int main(int argc, char ** argv)
{
  // Set GENIE print level
  genie::GHepRecord::SetPrintLevel(genie::RunOpt::Instance()->EventRecordPrintLevel());

  using namespace valor;

  valor::ExperimentInitialiser();

  CmdLnArgList arg;
  arg.Read(argc,argv, "$VALOR_EXPT/config/apps/make_sbncode_minidst.arg");
  LOG("make_sbncode_minidst", pNOTICE) << arg;

  std::string thresholds = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  Messenger::Instance()->Configure(thresholds);

  string opt_beam_name      = arg.GetString("beam");
  string opt_sample_name    = arg.GetString("sample");
  string opt_output_name    = arg.GetString("output");
  string opt_input_name     = arg.GetString("input");
  bool   opt_disable_checks = arg.GetBool("disable-checks");
  bool   write_universes    = arg.GetBool("write-universes");

  // Determine sample-types
  bool is_nueint  = false;
  bool is_nueosc  = false;
  bool is_nuenumu = false;
  bool is_numu    = false;
  bool is_nue     = false;
  string str_numu = "Numu";
  string str_nue  = "Nue";
  string str_int  = "_Int";
  string str_osc  = "_Osc";

  //Find substrings and check the appearance sample-type if necessary
  size_t found_nue  = opt_input_name.find(str_nue);
  size_t found_numu = opt_input_name.find(str_numu);

  // Get disappearance from sample name
  if(found_nue == string::npos && found_numu != string::npos)
    is_numu = true;

  if(found_nue != string::npos){
    is_nue = true;
    // We are looking at a nue sample, check if osc, intrinsic or numu
    size_t found_nueosc  = opt_input_name.find(str_osc);
    size_t found_nueint  = opt_input_name.find(str_int);
    size_t found_nuenumu = opt_input_name.find(str_numu);
    if(found_nueosc != string::npos && found_nueint == string::npos && found_nuenumu == string::npos)
      is_nueosc = true;
    else if(found_nueosc != string::npos){
      VLOG("make_sbncode_minidst", pFATAL) 
        << "Error: Found appearance oscillated file with hint of intrinsic and/or numu in the name - misleading: " << opt_input_name;
      exit(1);
    }
    if(found_nueint != string::npos && found_nueosc == string::npos && found_nuenumu == string::npos)
      is_nueint = true;
    else if(found_nueint != string::npos){
      VLOG("make_sbncode_minidst", pFATAL) 
        << "Error: Found appearance intrinsic file with hint of oscillated and/or numu in the name - misleading: " << opt_input_name;
      exit(1);
    }
    if(found_nuenumu != string::npos && found_nueosc == string::npos && found_nueint == string::npos)
      is_nuenumu = true;
    else if(found_nuenumu != string::npos){
      VLOG("make_sbncode_minidst", pFATAL) 
        << "Error: Found appearance numu file with hint of oscillated and/or intrinsic in the name - misleading: " << opt_input_name;
      exit(1);
    }
  }

  bool found_nues[] = {is_nueosc, is_nueint, is_nuenumu};
  if(found_nue && std::count(found_nues, found_nues+sizeof(found_nues), 1) > 1){
      VLOG("make_sbncode_minidst", pFATAL) 
        << "Error: Found multiple appearance types in filename - misleading: " << opt_input_name;
      exit(1);
  }
  
  // Make sure we are finding at least 1 of numu or nue in the name
  bool found[] = {is_numu, is_nueosc, is_nueint, is_nuenumu};
  if(std::count(found, found+sizeof(found), 1) == 0){
    VLOG("make_sbncode_minidst", pFATAL) 
      << "Error: Found hint of neither appearance (" << str_nue << ", " << str_int << ", " << str_osc << ") nor disappearance ( " << str_numu << ") in filename - misleading: " << opt_input_name;
    exit(1);
  }

  // CHECKING OUTPUT OF NEW CODE
  std::cout << " Input filename : " << opt_input_name << " - ";
  if(is_nueosc)
    std::cout << " Appearance Oscillated " << std::endl;
  if(is_nueint)
    std::cout << " Appearance Intrinsic " << std::endl;
  if(is_nuenumu)
    std::cout << " Appearance NuMu " << std::endl;
  if(is_numu)
    std::cout << " Disappearance NuMu " << std::endl;

  // Get the POT of the sample from the subrun tree
  double mcsample_pot = -1.;
  TChain * subrun_tree = new TChain(gSubRunTreeName.c_str());
  subrun_tree->Add(opt_input_name.c_str());
  if(!subrun_tree || !subrun_tree->GetEntries()) {
    VLOG("make_sbncode_minidst", pFATAL) 
      << "Error: Unable to read " << gSubRunTreeName
      <<" from "<< opt_input_name;
    exit(1);
  }

  Long64_t nev_subrun = subrun_tree->GetEntries();
  VLOG("make_sbncode_minidst", pNOTICE) 
    << "Input subrun tree has " << nev_subrun << ((nev_subrun==1) ? " entry." : " entries.");
  
  TBranch *b = subrun_tree->GetBranch("totgoodpot"); 
  unsigned int npot = subrun_tree->GetEntries();
  for(unsigned int i = 0; i < npot; ++i){
    b->GetEntry(i);
    mcsample_pot += b->GetLeaf("totgoodpot")->GetValue();
  }
  
  if(mcsample_pot == -1.){
    VLOG("make_sbncode_minidst", pFATAL) 
      << "Error: Not able to access MCSample POT from " << gSubRunTreeName;
    exit(1);
  }
  VLOG("make_sbncode_minidst", pNOTICE) 
    << "POT in the input file is " << mcsample_pot;


  // Get the sample and beam configuration
  conv::Sample_t sample = util::SampleFromString(opt_sample_name);
  assert(sample != conv::ksUndefined);

  conv::BeamConf_t beam = util::BeamConfFromString(opt_beam_name);
  assert(beam != conv::kbUndefined);
  
  int    valor_minidst_sample       = sample;
  int    valor_minidst_beam         = -1;  // see Conventions/BeamConf.h 
  int    valor_minidst_reac_mode    = -1;  // see Conventions/ReacMode.h 
  int    valor_minidst_reac_type    = -1;  // see Conventions/ReacMode.h 
  int    valor_minidst_target       = -1;  // nuclear target -  GENIE PDG convention
  int    valor_minidst_init_nupdg   = -1;  // Initial PDG
  int    valor_minidst_final_nupdg  = -1;  // Final PDG
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
  valor_minidst->Branch("reac_type" , &valor_minidst_reac_type   ,"reac_type/I"  );
  valor_minidst->Branch("init_pdg"  , &valor_minidst_init_nupdg  ,"init_pdg/I"   );
  valor_minidst->Branch("final_pdg" , &valor_minidst_final_nupdg ,"final_pdg/I"  );
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
      << "Error: Unable to read " << gTreeName
      <<" from "<< opt_input_name;
    exit(1);
  }

  Long64_t nev = analysis_tree->GetEntries();
  VLOG("make_sbncode_minidst", pNOTICE) 
    << "Input analysis tree has " << nev << ((nev==1) ? " entry." : " entries.");

  event::RecoEvent *pevent = nullptr;
  analysis_tree->SetBranchAddress("reco_events", &pevent);
  
  std::map<std::string,float *> variation_entries;
  std::map<std::string,size_t>  variation_nentries;
  //~ std::map<std::string,TBranch *> variation_branches;
  // First, let's read one true event map to get the universe details
  if (write_universes) {
    analysis_tree->GetEntry(0);
    event::Interaction * ptruth = pevent->GetTruth();
    assert(ptruth);
    const auto & weights = ptruth->weights; // map<string,whatever>
    TObjArray variation_names;
    for (const auto & variation : weights) {
      // make a list of the variation names
      const std::string & vname = variation.first;
      variation_names.AddLast(new TObjString(vname.c_str()));
      
      // Get the number of universes
      const size_t n_universes = variation.second.size();
      // and a branch to store them all in
      variation_entries[vname] = new float[n_universes];
      for (size_t ii = 0 ; ii < n_universes ; ii++) {
        variation_entries[vname][ii] = conv::kBadResult;
      }
      std::string branch_name (Form("variation_%s"  ,vname.c_str()));
      std::string branch_nameF(Form("variation_%s[%lu]/F",vname.c_str(),n_universes));
      valor_minidst->Branch(branch_name.c_str(),&variation_entries[vname],branch_nameF.c_str());
      
    }
    variation_names.Write("variation_names",TObject::kSingleKey);
  }
  

  //
  // event loop
  //

  Long64_t nev_accept = 0;

  std::vector<int> nev_accept_by_mode;
  for (int im = 0 ; im < valor::conv::kNReacModes; im++) {
    nev_accept_by_mode.push_back(0);
  }
  
  // Commented out now we only have one tree per sample. But remember if that changes!
  //~ int last_tree_number = -1; // store which number file we're in, so we can count each tree's weight once

  for(Long64_t iev = 0; iev < nev; iev++) {

    analysis_tree->GetEntry(iev);

    if (gPrintEveryNEvents && !(iev%gPrintEveryNEvents)) {
      VLOG("make_sbncode_minidst", pNOTICE) << "** Reading event: " << iev
        <<" - so far accepted " << nev_accept;
    }
    else {
      VLOG("make_sbncode_minidst", pDEBUG) << "** Reading event: " << iev
        <<" - so far accepted " << nev_accept;
    }
    
    // reset the systematic universes
    if (write_universes) {
      for (const auto & entry : variation_entries) {
        const std::string & name = entry.first;
        float * arr = entry.second;
        for (size_t ii = 0 ; ii < variation_nentries[name] ; ii++) {
          arr[ii] = conv::kBadResult;
        }
      }
    }

    int iscc           = false;
    int isnc           = false;
    int nu_pdg         = -1;
    int init_pdg       = -1;

    //int init_pdg    = -1;
    double enu_true    =  -999.;
    double enu_reco    =  -999.;
    double reco_weight = 1.;
    double Q2s         =  -999.;

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

    analysis_tree->GetEntry(iev);

    event::RecoEvent & event = *pevent;
    event::RecoInteraction &reco = event.reco;
    event::Interaction * ptruth = event.GetTruth();

    if(ptruth==nullptr) {
      VLOG("make_sbncode_minidst", pNOTICE) 
        << "The number of truth entries is 0, skipping event "<<iev;
      continue;      
    }

    event::Interaction & truth = *ptruth;

    std::vector<event::FinalStateParticle> &fsps = truth.finalstate;
    iscc = truth.neutrino.iscc;
    isnc = truth.neutrino.isnc;
    nu_pdg = truth.neutrino.pdg;
    enu_true = truth.neutrino.energy;
    Q2s = truth.neutrino.Q2;
    larsoft_mode = truth.neutrino.genie_intcode;
    // Particle counting
    for(unsigned int p = 0; p < fsps.size(); ++p){
      if (fsps[p].status_code != 1) {continue;}
      if     (fsps[p].pdg == genie::kPdgProton      ) nip++;
      else if(fsps[p].pdg == genie::kPdgAntiProton  ) niap++;
      else if(fsps[p].pdg == genie::kPdgNeutron     ) nin++;
      else if(fsps[p].pdg == genie::kPdgAntiNeutron ) nian++;
      else if(fsps[p].pdg == genie::kPdgPiP         ) nipip++;
      else if(fsps[p].pdg == genie::kPdgPiM         ) nipim++;
      else if(fsps[p].pdg == genie::kPdgPi0         ) nipi0++;
      else if(fsps[p].pdg == genie::kPdgKP          ) nikp++;
      else if(fsps[p].pdg == genie::kPdgKM          ) nikm++;
      else if(fsps[p].pdg == genie::kPdgK0          ) nik0++;
      else if(fsps[p].pdg == genie::kPdgAntiK0      ) niak0++;
      else if(fsps[p].pdg == genie::kPdgGamma       ) nig++;
      else if(fsps[p].pdg == genie::kPdgElectron    ) niem++;
      else if(fsps[p].pdg == genie::kPdgPositron    ) niep++;
      else if(fsps[p].pdg == genie::kPdgMuon        ) nimu++;
      else if(fsps[p].pdg == genie::kPdgAntiMuon    ) nimup++;
      else if(fsps[p].pdg == genie::kPdgAntiMuon    ) nimup++;
      else if(fsps[p].pdg == 14 || fsps[p].pdg == -14 || fsps[p].pdg == 12 || fsps[p].pdg == -12) ninu++;
      else if(fsps[p].pdg > 1e4) ninuc++;
      else niother++; 
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
        else                                       { reac = conv::kmtCCoth;}
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
    init_pdg  = truth.neutrino.initpdg;
    init_flav = valor::util::FlavourFromPDG(init_pdg);

    // Get the real valor mode - this will only be defined for modes turned on right now
    conv::ReacMode_t  reac_mode  = valor::util::ReacTypeToMode(reac,init_flav,final_flav);
    // If we have any events that are in disabled modes, put them into other
    if (reac_mode==conv::kmUndefined) {
      if (isnc) {reac = conv::kmtNCoth;}
      if (iscc) {reac = conv::kmtCCoth;}
      reac_mode  = valor::util::ReacTypeToMode(reac,init_flav,final_flav);
    }

    if(!opt_disable_checks) {
      //
      // ignore events that can not be used in the VALOR analysis
      //
      if(reac_mode == conv::kmUndefined) {
        VLOG("make_sbncode_minidst", pWARN) << "- Rejecting event [bad mode] "<<iev;
        VLOG("make_sbncode_minidst", pNOTICE)
          <<"\n larsoft_mode = "<<larsoft_mode
          <<"\n iscc="<<iscc<<" and isnc="<<isnc
          <<"\n initpdg="<<init_pdg<<" and finalpdg="<<nu_pdg
          <<"\n valor reaction="<<reac<<" which is "<<util::AsString(reac);
        continue;
      }
      if(isnc && init_flav != final_flav){
        VLOG("make_sbncode_minidst", pWARN) << "- Rejecting event [oscillated nc] "<<iev; 
        continue;
      }
      if(is_nue && (init_pdg == 12 || init_pdg == -12) && (!is_nueint)){
        VLOG("make_sbncode_minidst", pWARN) << "- Rejecting event [nue not from intrinsic] "<<iev;
        VLOG("make_sbncode_minidst", pINFO)
          <<"\n is_nueint = "<<is_nueint
          <<"\n larsoft_mode = "<<larsoft_mode
          <<"\n iscc="<<iscc<<" and isnc="<<isnc
          <<"\n initpdg="<<init_pdg<<" and finalpdg="<<nu_pdg
          <<"\n valor mode="<<reac_mode<<" which is "<<util::AsString(reac_mode); 
        continue;
      }
      if(is_nueosc && init_flav == final_flav){
        VLOG("make_sbncode_minidst", pWARN) << "- Rejecting event [non-oscillated event in oscillated file] "<<iev; 
        continue;
      }
      if(is_numu && init_flav != final_flav){
        VLOG("make_sbncode_minidst", pWARN) << "- Rejecting event [oscillated event in non-oscillated file] "<<iev; 
        continue;
      }
    }

    VLOG("make_sbncode_minidst",pDEBUG) << "Read event: "
      << "Etrue         = "<< enu_true  << " GeV; "
      << "LArSoft mode  = "<< larsoft_mode  << "; ";

    valor_minidst_sample       = sample; 
    valor_minidst_beam         = beam; 
    valor_minidst_reac_mode    = reac_mode;
    valor_minidst_enu_true     = enu_true; 
    valor_minidst_wght_smear   = 1.;
    valor_minidst_Q2_true      = Q2s;
    valor_minidst_wght_pot     = 1./mcsample_pot; 
    valor_minidst_target       = 1000180400; // Argon40
    //valor_minidst_y_reco      = 0.5; // FORCE y=0.5 for now
    valor_minidst_reac_type    = reac;
    valor_minidst_init_nupdg   = init_pdg;
    valor_minidst_final_nupdg  = nu_pdg;

    VLOG("make_sbncode_minidst", pINFO) 
      << "\n Information copied to VALOR DUNE/SBNCode Mini-DST: "
      << "\n Beam          = " << valor_minidst_beam   
      << "\n Sample        = " << valor_minidst_sample    
      << "\n Reaction mode = " << valor_minidst_reac_mode 
      << "\n Target        = " << valor_minidst_target
      << "\n Q2 (true)     = " << valor_minidst_Q2_true << " GeV^2"
      << "\n Ev (true)     = " << valor_minidst_enu_true << " GeV"
      << "\n y (reco)      = " << valor_minidst_y_reco    
      << "\n POT weight    = " << valor_minidst_wght_pot;


    enu_reco = reco.reco_energy;
    reco_weight = reco.weight;

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
    }

    VLOG("make_sbncode_minidst", pINFO) << "+ Accepting event";
    
    // Copy the systematic universes across
    if (write_universes) {
      for (const auto & entry : truth.weights) {
        const std::string & name = entry.first;
        const auto & vec = truth.weights[name];
        for (size_t ii = 0 ; ii < vec.size() ; ii++) {
          variation_entries[name][ii] = static_cast<float>(vec[ii]);
        }
      }
    }

    valor_minidst_enu_reco  = enu_reco;
    valor_minidst_wght      = reco_weight;
    //~ VLOG("make_sbncode_minidst", pNOTICE) 
      //~ << "\n Ev (reco)     = " << valor_minidst_enu_reco << ", GeV" << " weight : " << valor_minidst_wght; 
      

    valor_minidst->Fill();
      
    nev_accept += 1;
    nev_accept_by_mode[valor_minidst_reac_mode] += 1;
  } // event loop
    
  for (unsigned int im = 0 ; im < nev_accept_by_mode.size(); im++) {
    valor::conv::ReacMode_t m = (valor::conv::ReacMode_t)im;
    VLOG("make_sbncode_minidst", pNOTICE) << "Selected "<<nev_accept_by_mode[im]<<" events of mode "<<valor::util::AsString(m);
  }

  double f = 100. * (double)nev_accept / (double)nev;
  VLOG("make_sbncode_minidst", pNOTICE) <<
    "Used " << f << "% (" << nev_accept << "/" << nev 
    << ") of input events.";

  //~ VLOG("make_sbncode_minidst", pNOTICE) <<"Total POT read: "<<total_pot_read;
  
  // Saving VALOR mini-FST to output file 
  VLOG("make_sbncode_minidst", pNOTICE) 
    << "Saving VALOR/DUNE mini-DST to: " << opt_output_name;
  valor_minidst->Write();  
  fout.Close();

  VLOG("make_sbncode_minidst", pNOTICE)  << "Done!";

  return 0;
}
