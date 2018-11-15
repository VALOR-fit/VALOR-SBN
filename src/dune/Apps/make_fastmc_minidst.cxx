//____________________________________________________________________________
/*!

  \app       valor_dune-make_fastmc_minidst

  \brief     Converts input DUNE FD analysis DSTs to the VALOR mini-DST format.

  \syntax    valor_dune-make_nd_minidst 
  --input  input_analysis_file.root
  --output output_file_containing_valor_minidst.root
  --format format_of_the_input_file <hpgartpc, lartpc, fgt>
  [--disable-checks]

  \author    Steve Dennis <s.r.dennis \at liverpool.ac.uk>
             University of Liverpool

  \created   August 2016

  \copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

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
#include <TSystem.h>

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
#include "valor/Conventions/Sample.h"

#include "dune/Conventions/ReacMode.h"

using std::string;
using std::ostringstream;

static const string gTreeName = "gst";

void GetCommandLineArgs (int /*argc*/, char ** /*argv*/);

static const int gPrintEveryNEvents = 50000;

// Cuts from Dan Cherdack for extra rejection
double NC_Prob_numu_cut  = 0.20;
double Tau_Prob_numu_cut = 0.20;
double NC_Prob_nue_cut   = 0.75;
double Tau_Prob_nue_cut  = 0.60;

//___________________________________________________________________
int main(int argc, char ** argv)
{
  
  using namespace valor;
  
  Env::Instance()->AutoSet("dune");
 
  CmdLnArgList arg;
  arg.Read(argc,argv,"$VALOR_DUNE/config/apps/make_fastmc_minidst.arg");
  LOG("valor_dune", pNOTICE) << arg;
  
  std::string thresholds = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  Messenger::Instance()->Configure(thresholds);
  
  string opt_beam_name         = arg.GetString("beam");
  string opt_output_name       = arg.GetString("output");
  string opt_input_name        = arg.GetString("input");
  bool   opt_disable_checks    = arg.GetBool("disable-checks");
  int    opt_beam_pdg          = arg.GetInt("beam-pdg");
  bool   disable_extra_cuts    = arg.GetBool("disable-extra-cuts");
  bool   split_sample_by_res   = arg.GetBool("split-sample-by-res");
  bool   optimised_beam        = arg.GetBool("optimised-beam");
   
  int    valor_minidst_sample       = -1;
  int    valor_minidst_beam         = util::BeamConfFromString(opt_beam_name);  // see Conventions/BeamConf.h 
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
    new TTree("valor_dune_nd_mini_dst","Mini-DST input for VALOR/DUNE FD Fit");

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
    VLOG("make_fastmc_minidst", pFATAL) 
      << "Unable to read " << gTreeName
      <<" from "<< opt_input_name;
    exit(1);
  }

  Long64_t nev = analysis_tree->GetEntries();
  VLOG("make_fastmc_minidst", pNOTICE) 
    << "Input analysis tree has " << nev << ((nev==1) ? " entry." : " entries.");
  analysis_tree->GetEntry(0);
  
  int run = -1;
  double enu_true       =  -999.;
  double enu_reco       =  -999.;
  double y_reco         =  -999.;
  double Q2s            =  -999.;
  double POTweight      =  -999.;
  
  int final_pdg  = -1;
  
  int nin      = -1;
  int nip      = -1;
  int nipip    = -1;
  int nipim    = -1;
  int nipi0    = -1;
  int nikp     = -1;
  int nikm     = -1;
  int nik0     = -1;
  int niem     = -1;
  int niother  = -1;
  
  int tgt = -1;
  
  bool iscc   = false;
  bool isnc   = false;
  bool isIMD  = -1;
  bool isQEL  = -1;
  bool isMEC  = -1;
  bool isRES  = -1;
  bool isDIS  = -1;
  bool isCOH  = -1;
  bool isNuEl = -1;
  
  int EvClass_reco = -1;
  
  double NC_Prob_numu  = -1;
  double Tau_Prob_numu = -1;
  double NC_Prob_nue   = -1;
  double Tau_Prob_nue  = -1;
  
  double Ehad_reco  = -1;
  double QE_Ev_reco = -1;
  
  double AllOptimizations[7];
  
  TBranch * branchptr = 0;
  vector<TBranch*> active_branches;
    
  analysis_tree->SetBranchAddress("Ev"           ,  &enu_true    , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("Ev_reco"      ,  &enu_reco    , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("y_reco"       ,  &y_reco      , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("Q2s"          ,  &Q2s         , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("neu"          ,  &final_pdg   , &branchptr); active_branches.push_back(branchptr);
  //~ analysis_tree->SetBranchAddress("nP"           ,  &nip         , &branchptr); active_branches.push_back(branchptr);
  //~ analysis_tree->SetBranchAddress("nN"           ,  &nin         , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("nipip"        ,  &nipip       , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("nipim"        ,  &nipim       , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("nipi0"        ,  &nipi0       , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("nikp"         ,  &nikp        , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("nikm"         ,  &nikm        , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("nik0"         ,  &nik0        , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("niem"         ,  &niem        , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("niother"      ,  &niother     , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("cc"           ,  &iscc        , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("nc"           ,  &isnc        , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("imd"          ,  &isIMD       , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("qel"          ,  &isQEL       , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("mec"          ,  &isMEC       , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("res"          ,  &isRES       , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("dis"          ,  &isDIS       , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("coh"          ,  &isCOH       , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("nuel"         ,  &isNuEl      , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("tgt"          ,  &tgt         , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("EvClass_reco" ,  &EvClass_reco, &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("POTWeight"    ,  &POTweight   , &branchptr); active_branches.push_back(branchptr);
  
  analysis_tree->SetBranchAddress("NC_Prob_numu" ,  &NC_Prob_numu  , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("Tau_Prob_numu", &Tau_Prob_numu  , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("NC_Prob_nue"  ,  &NC_Prob_nue   , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("Tau_Prob_nue" , &Tau_Prob_nue   , &branchptr); active_branches.push_back(branchptr);
  
  // Optimisation branch
  analysis_tree->SetBranchAddress("frw7_AllOptimizations",&AllOptimizations  , &branchptr); active_branches.push_back(branchptr);

  
  // Variable used to cut for QE
  analysis_tree->SetBranchAddress("Ehad_reco"  ,  &Ehad_reco  , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("QE_Ev_reco" ,  &QE_Ev_reco  , &branchptr); active_branches.push_back(branchptr);
  
  // Only read the branches we're using and their sub-branches
  analysis_tree->SetBranchStatus("*",0);
  for (unsigned int ib = 0 ; ib < active_branches.size(); ib++) {
    active_branches[ib]->SetStatus(1);
    TObjArray * bar = active_branches[ib]->GetListOfBranches();
    for (int ie = 0 ; ie < bar->GetEntries(); ie++) {
      TBranch * b = dynamic_cast<TBranch*>(bar->At(ie));
      assert(b);
      b->SetStatus(1);
    }
  }
  
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

    if (gPrintEveryNEvents && !(iev%gPrintEveryNEvents)) {
      VLOG("make_fastmc_minidst", pNOTICE) << "** Reading event: " << iev;
    }
    else {
      VLOG("make_fastmc_minidst", pDEBUG) << "** Reading event: " << iev;
    }

    analysis_tree->GetEntry(iev);
    
    VLOG("make_fastmc_minidst",pDEBUG) << "Read event: "
      << "Etrue         = "<<enu_true  << " GeV; "
      << "Ereco         = "<<enu_reco  << " GeV; "
      << "Yreco         = "<<y_reco  << ";";
    
      
      
    // Construct the reaction mode
    conv::ReacType_t t = conv::kmtUndefined;
    if (iscc) {
      if      (isQEL       ) { t = conv::kmtCCQE;    }
      else if (isMEC       ) { t = conv::kmtCCMEC;   }
      else if (isCOH       ) { t = conv::kmtCCcoh;   }
      else if (isIMD       ) { t = conv::kmtCCIMD;   }
      else if (isNuEl      ) { t = conv::kmtCCELScat;}
      
      else { // start counting pions
        if      (nikp || nik0 || nikm || niother) { t = conv::kmtCCoth;}
        else if (nipip+nipim == 1 && nipi0 == 0)  { t = conv::kmtCC1piC;}
        else if (nipip+nipim == 0 && nipi0 == 1)  { t = conv::kmtCC1pi0;}
        else if (nipip+nipim == 2 && nipi0 == 0)  { t = conv::kmtCC2piC;}
        else if (nipip+nipim == 0 && nipi0 == 2)  { t = conv::kmtCC2pi0;}
        else if (nipip+nipim == 1 && nipi0 == 1)  { t = conv::kmtCCpiCpi0;}
        else                                      { t = conv::kmtCCoth;}
      }
    }
    else if (isnc) {
      if      (isQEL   ) { t = conv::kmtNCEL;    }
    //else if (isMEC   ) { t = conv::kmtNCMEC;   }
      else if (isCOH   ) { t = conv::kmtNCcoh;   }
    //else if (isNuEl  ) { t = conv::kmtNCELScat;}
      
      else { // start counting pions
        if      (nikp || nik0 || nikm || niother) { t = conv::kmtNCoth;}
        else if (nipip+nipim == 1 && nipi0 == 0)  { t = conv::kmtNC1piC;}
        else if (nipip+nipim == 0 && nipi0 == 1)  { t = conv::kmtNC1pi0;}
      //else if (nipip+nipim == 2 && nipi0 == 0)  { t = conv::kmtNC2piC;}
      //else if (nipip+nipim == 0 && nipi0 == 2)  { t = conv::kmtNC2pi0;}
      //else if (nipip+nipim == 1 && nipi0 == 1)  { t = conv::kmtNCpiCpi0;}
        else                                      { t = conv::kmtNCoth;}
      }
    }
    else if (isNuEl) {
      t = conv::kmtELScat;
    }
    
    conv::NuFlavour_t init_flav  = valor::util::FlavourFromPDG(opt_beam_pdg);
    conv::NuFlavour_t final_flav = valor::util::FlavourFromPDG(final_pdg);
    
    // If it's NC, we'll ignore oscillated events (to avoid triple counting)
    if (isnc) {
      if (final_flav != init_flav) {continue;}
    }
    
    // Only have the combination mode for final state nues
    if (t == conv::kmtCCELScat && (final_flav == conv::kNuE || final_flav == conv::kNuEBar)) {
      t = conv::kmtELScat;
    }
    // NCel is not in play yet
    if (t == conv::kmtNCEL) {
      if (final_flav == conv::kNuE || final_flav == conv::kNuEBar) {
        t = conv::kmtELScat;
      }
      else {
        t = conv::kmtNCoth;
      }
    }
    
    // Get the real valor mode
    conv::ReacMode_t  reac_mode  = valor::util::ReacTypeToMode(t,init_flav,final_flav);
    
    if(!opt_disable_checks) {
      //
      // ignore events that can not be used in the VALOR analysis
      //
      if(reac_mode == valor::conv::kmUndefined) {
        VLOG("make_fastmc_minidst", pWARN) << "- Rejecting event [bad mode]\n"
        << util::AsString(init_flav)<<" -> "<<util::AsString(final_flav)<<"\t"<<util::AsString(t);
        //~ std::cout<<iscc<<"\t"<<isnc<<"\t"<<"\t"<<larsoft_mode<<std::endl;
        continue;
      }
    }
    
    last_tree_number = analysis_tree->GetTreeNumber();
    
    conv::Sample_t sample = conv::ksUndefined;
    if (EvClass_reco == 0) {
      sample = conv::ksNuMuLikeCChigh;
      if (split_sample_by_res) {
        if (!isQEL) {
          sample = conv::ksNuMuLikeCClow;
        }
        else {
          enu_reco = QE_Ev_reco;
        }
      }
      
      if (!disable_extra_cuts) {
        if ( (NC_Prob_numu  <= NC_Prob_numu_cut ) ||
             (Tau_Prob_numu <= Tau_Prob_numu_cut) ) {
          continue;
        }
      }

        
    }
    else if (EvClass_reco == 1) {
      sample = conv::ksNuELikeCChigh;
      if (split_sample_by_res) {
        if (!isQEL) {
          sample = conv::ksNuELikeCClow;
        }
        else {
          enu_reco = QE_Ev_reco;
        }
      }
      
      if (!disable_extra_cuts) {
        if ( (NC_Prob_nue   <= NC_Prob_nue_cut  ) ||
             (Tau_Prob_nue  <= Tau_Prob_nue_cut ) ) {
          continue;
        }
      }
    }
    
    if(!opt_disable_checks) {
      
      //
      // ignore events that can not be used in the VALOR analysis
      //
      if(enu_reco <= 0.) {
        VLOG("make_fastmc_minidst", pNOTICE) << "- Rejecting event [Ev (reco) <= 0]: "<<enu_reco;
        continue;
      }
      
      if(sample == conv::ksUndefined) {
        VLOG("make_fastmc_minidst", pINFO) << "- Rejecting event not in one of our samples";
        continue;
      }

      VLOG("make_fastmc_minidst", pINFO) << "+ Accepting event";
    }
      
    nev_accept++;
    nev_accept_by_mode[reac_mode]++;

      //~ VLOG("make_fastmc_minidst", pDEBUG) 
        //~ << "GENIE MC truth info: " << event;
        
    double wght = 1.;
    if (optimised_beam) {
      wght *= AllOptimizations[4];
    }
    
    valor_minidst_sample    = sample; 
    valor_minidst_reac_mode = reac_mode;
    valor_minidst_enu_true  = enu_true; 
    valor_minidst_enu_reco  = enu_reco; 
    valor_minidst_y_reco    = y_reco;
    valor_minidst_wght      = wght;
    valor_minidst_wght_pot  = POTweight/nev; 
    valor_minidst_wght_smear= 1.; 
    valor_minidst_Q2_true   = Q2s;
      
    valor_minidst_target    = tgt;
      
    VLOG("make_fastmc_minidst", pINFO) 
      << "\n Information copied to VALOR DUNE/ND Mini-DST: "
      << "\n Beam          = " << valor_minidst_beam   
      << "\n Sample        = " << valor_minidst_sample    
      << "\n Reaction mode = " << valor_minidst_reac_mode 
      << "\n Target        = " << valor_minidst_target
      << "\n Q2 (true)     = " << valor_minidst_Q2_true << " GeV^2"
      << "\n Ev (true)     = " << valor_minidst_enu_true << " GeV"
      << "\n Ev (reco)     = " << valor_minidst_enu_reco << " GeV" 
      << "\n y (reco)      = " << valor_minidst_y_reco    
      << "\n POT weight    = " << valor_minidst_wght_pot
      << "\n Smear weight  = " << valor_minidst_wght_smear;
    
    valor_minidst->Fill();
  } // event loop
  
  for (unsigned int im = 0 ; im < nev_accept_by_mode.size(); im++) {
    valor::conv::ReacMode_t m = (valor::conv::ReacMode_t)im;
    VLOG("make_fastmc_minidst", pNOTICE) << "Selected "<<nev_accept_by_mode[im]<<" events of mode "<<valor::util::AsString(m);
  }
  
  double f = 100. * (double)nev_accept / (double)nev;
  VLOG("make_fastmc_minidst", pNOTICE) <<
    "Used " << f << "% (" << nev_accept << "/" << nev 
    << ") of input events.";
    
  //~ VLOG("make_fastmc_minidst", pNOTICE) <<
    //~ "Total POT read: "<<total_pot_read;

  // Saving VALOR mini-FST to output file 
  VLOG("make_fastmc_minidst", pNOTICE) 
    << "Saving VALOR/DUNE mini-DST to: " << opt_output_name;
  valor_minidst->Write();  
  fout.Close();

  VLOG("make_fastmc_minidst", pNOTICE)  << "Done!";

  return 0;
}
//___________________________________________________________________
