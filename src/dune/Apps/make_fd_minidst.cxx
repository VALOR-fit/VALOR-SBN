//____________________________________________________________________________
/*!

  \app       valor_dune-make_fd_minidst

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

// genie
#include "Conventions/GBuild.h"
#include "EVGCore/EventRecord.h"
#include "GHEP/GHepParticle.h"
#include "Ntuple/NtpMCFormat.h"
#include "Ntuple/NtpMCTreeHeader.h"
#include "Ntuple/NtpMCEventRecord.h"
#include "Messenger/Messenger.h"
#include "PDG/PDGCodes.h"
#include "PDG/PDGUtils.h"
#include "PDG/PDGLibrary.h"
#include "Utils/CmdLnArgParser.h"
#include "Utils/RunOpt.h"

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

#include "dune/Conventions/BeamConf.h"
#include "dune/Conventions/ReacMode.h"
#include "dune/Conventions/Sample.h"

#include "dune/GENIEUtilities/UtlEventRec.h"

using std::string;
using std::ostringstream;

static const double gMVACut = 0.8;
static const string gTreeName = "mvaselect/MVASelection";
//~ static const string gTreeName = "MVASelection";

void GetCommandLineArgs (int /*argc*/, char ** /*argv*/);

static const int gPrintEveryNEvents = 50000;

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

// Function to add up the POT
double GetTotalPOT(std::string filename, int runno);

//___________________________________________________________________
int main(int argc, char ** argv)
{
  // Set GENIE print level
  genie::Messenger::Instance();
  genie::GHepRecord::SetPrintLevel(genie::RunOpt::Instance()->EventRecordPrintLevel());
  
  using namespace valor;
  
  Env::Instance()->AutoSet("dune");
 
  CmdLnArgList arg;
  arg.Read(argc,argv,"$VALOR_DUNE/config/apps/make_fd_minidst.arg");
  LOG("valor_dune", pNOTICE) << arg;
  
  std::string thresholds = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  Messenger::Instance()->Configure(thresholds);
  
  string opt_sample_name       = arg.GetString("sample");
  string opt_output_name       = arg.GetString("output");
  string opt_input_name        = arg.GetString("input");
  bool   opt_disable_checks    = arg.GetBool("disable-checks");
  
  conv::Sample_t sample = util::SampleFromString(opt_sample_name);
  assert(sample != conv::ksUndefined);
  
  // Read the smearing histograms - ugly hack for now, but best option while we're still using these files of Dan's.
  TString smearing_path = "$VALOR_DUNE/data/dune/fdfit/2016b/smearing_histograms.root";
  gSystem->ExpandPathName(smearing_path);
  TFile smearing_file(smearing_path.Data());
  TObject * obj = smearing_file.Get(Form("smearing_NC_%s",opt_sample_name.c_str()));
  TH2D * nc_smearing = new TH2D(*(TH2D*)obj);
  TH2D * cc_smearing[6];
  for (int i = 0 ; i < 6; i++) {
    conv::NuFlavour_t flav = (conv::NuFlavour_t)i;
    obj = smearing_file.Get(Form("smearing_%s_%s",util::AsString(flav).c_str(),opt_sample_name.c_str()));
    cc_smearing[flav] = new TH2D(*(TH2D*)obj);
  }
   

  int    valor_minidst_beam         = -1; // see Conventions/BeamConf.h 
  int    valor_minidst_sample       = sample;
  int    valor_minidst_reac_mode    = -1; // see Conventions/ReacMode.h 
  int    valor_minidst_target       = -1; // nuclear target -  GENIE PDG convention
  double valor_minidst_enu_true     = -1; // true neutrino energy, in GeV
  double valor_minidst_Q2_true      = -1; // true neutrino energy, in GeV
  double valor_minidst_enu_reco     = -1; // reco neutrino energy, in GeV
  double valor_minidst_y_reco       = -1; // inelasticity
  double valor_minidst_wght_pot     = -1; // POT weight 
  double valor_minidst_wght         = -1.; // misc weight 
  double valor_minidst_wght_smear   = -1; // energy smearing weight 
  
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
    VLOG("make_fd_minidst", pFATAL) 
      << "Unable to read " << gTreeName
      <<" from "<< opt_input_name;
    exit(1);
  }

  Long64_t nev = analysis_tree->GetEntries();
  VLOG("make_fd_minidst", pNOTICE) 
    << "Input analysis tree has " << nev << ((nev==1) ? " entry." : " entries.");
  analysis_tree->GetEntry(0);
  
  int run = -1;
  int iscc   = false;
  int isnc   = false;
  double enu_true       =  -999.;
  double enu_reco       =  -999.;
  double Q2s            =  -999.;
  double mvaresult      =  -1.; // The selection variable to cut on
  
  int init_pdg   = -1;
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
  
  int larsoft_mode = -1;
  
  // The POT weighting scheme here seems insane...
  // Just ask me on Slack if you need it explained - this should be temporary I hope - Steve
  std::map<int,double> total_pot_read_per_run;
  total_pot_read_per_run.insert( std::make_pair(20000001, GetTotalPOT(opt_input_name, 20000001)));
  total_pot_read_per_run.insert( std::make_pair(20000002, GetTotalPOT(opt_input_name, 20000002)));
  total_pot_read_per_run.insert( std::make_pair(20000003, GetTotalPOT(opt_input_name, 20000003)));
  total_pot_read_per_run.insert( std::make_pair(20000004, GetTotalPOT(opt_input_name, 20000004)));
  total_pot_read_per_run.insert( std::make_pair(20000005, GetTotalPOT(opt_input_name, 20000005)));
  total_pot_read_per_run.insert( std::make_pair(20000006, GetTotalPOT(opt_input_name, 20000006)));
  
  TBranch * branchptr = 0;
  vector<TBranch*> active_branches;
    
  analysis_tree->SetBranchAddress("run"      ,  &run         , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("Ev"       ,  &enu_true    , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("Q2"       ,  &Q2s         , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("beamPdg"  ,  &init_pdg    , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("neu"      ,  &final_pdg   , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("nP"       ,  &nip         , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("nN"       ,  &nin         , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("nipip"    ,  &nipip       , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("nipim"    ,  &nipim       , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("nipi0"    ,  &nipi0       , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("nikp"     ,  &nikp        , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("nikm"     ,  &nikm        , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("nik0"     ,  &nik0        , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("niem"     ,  &niem        , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("niother"  ,  &niother     , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("cc"       ,  &iscc        , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("nc"       ,  &isnc        , &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("mode"     ,  &larsoft_mode, &branchptr); active_branches.push_back(branchptr);
  analysis_tree->SetBranchAddress("mvaresult",  &mvaresult   , &branchptr); active_branches.push_back(branchptr);
  
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
      VLOG("make_fd_minidst", pNOTICE) << "** Reading event: " << iev;
    }
    else {
      VLOG("make_fd_minidst", pDEBUG) << "** Reading event: " << iev;
    }

    analysis_tree->GetEntry(iev);
    
    VLOG("make_fd_minidst",pDEBUG) << "Read event: "
      << "Etrue         = "<<enu_true  << " GeV; "
      << "Ereco         = "<<enu_reco  << " GeV; "
      << "LArSoft mode  = "<<larsoft_mode  << "; "
      << "MVA result    = "<<mvaresult  << "; ";
      
    if (mvaresult < gMVACut) {
      VLOG("make_fd_minidst",pDEBUG) << "MVA value too low, not selecting.";
      continue;
    }
    
      
      
    // Construct the reaction mode
    conv::ReacType_t t = conv::kmtUndefined;
    if (iscc) {
      if      (larsoft_mode==kLArQE                ) { t = conv::kmtCCQE;    }
      else if (larsoft_mode==kLArMEC               ) { t = conv::kmtCCMEC;   }
      else if (larsoft_mode==kLArCoh               ) { t = conv::kmtCCcoh;   }
      else if (larsoft_mode==kLArIMDAnnihilation   ) { t = conv::kmtCCIMD;   }
      else if (larsoft_mode==kLArElectronScattering) { t = conv::kmtCCELScat;}
      
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
      if      (larsoft_mode==kLArQE                ) { t = conv::kmtNCEL;    }
    //else if (larsoft_mode==kLArMEC               ) { t = conv::kmtNCMEC;   }
      else if (larsoft_mode==kLArCoh               ) { t = conv::kmtNCcoh;   }
    //else if (larsoft_mode==kLArElectronScattering) { t = conv::kmtNCELScat;}
      
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
    else if (larsoft_mode == kLArElectronScattering) {
      t = conv::kmtELScat;
    }
    
    conv::NuFlavour_t init_flav  = valor::util::FlavourFromPDG(init_pdg);
    conv::NuFlavour_t final_flav = valor::util::FlavourFromPDG(final_pdg);
    
    // If it's NC, we'll treat all events as unoscillated
    if (isnc) {
      final_flav = init_flav;
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
        VLOG("make_fd_minidst", pWARN) << "- Rejecting event [bad mode]\n"
        << util::AsString(init_flav)<<" -> "<<util::AsString(final_flav)<<"\t"<<util::AsString(t);
        //~ std::cout<<iscc<<"\t"<<isnc<<"\t"<<"\t"<<larsoft_mode<<std::endl;
        continue;
      }
    }
    
    last_tree_number = analysis_tree->GetTreeNumber();
    
    // Do ereco smearing here
    TH2D * smearing_hist = nc_smearing;
    if (iscc) {
      smearing_hist = cc_smearing[final_flav];
    }
    
    // The regime for smearing is that we fill the tree once for every ereco bin in the smearing histogram
    // These are weighted by the entry in the histogram, so the N entries add up to a single weighted event
    // Spread across all the ereco bins
    TAxis * true_axis = smearing_hist->GetXaxis();
    TAxis * reco_axis = smearing_hist->GetYaxis();
    int true_energy_bin = true_axis->FindBin(enu_true);
    
    for (int irecobin = 1 ; irecobin <= reco_axis->GetNbins(); irecobin++) {
      
      double reco_low_edge  = reco_axis->GetBinLowEdge(irecobin);
      double reco_high_edge = reco_low_edge + reco_axis->GetBinWidth(irecobin);
      enu_reco = Rnd::Instance()->RndOther().Uniform(reco_low_edge,reco_high_edge);
      
      valor_minidst_wght_smear = smearing_hist->GetBinContent(true_energy_bin,irecobin);
      
      if (valor_minidst_wght_smear < conv::kASmallNum) {continue;}
      
      //~ std::cout<<reco_axis->GetBinWidth(irecobin)<<"\t"<<reco_low_edge<<"\t"<<reco_high_edge<<"\t"<<enu_reco<<"\t"<<std::endl;
      //~ std::cout<<enu_true<<"\t"<<enu_reco<<"\t"<<valor_minidst_wght_smear<<std::endl;
      
      if(!opt_disable_checks) {
        
        //
        // ignore events that can not be used in the VALOR analysis
        //
        if(enu_reco <= 0) {
          VLOG("make_fd_minidst", pNOTICE) << "- Rejecting event [Ev (reco) <= 0]: "<<enu_reco;
          continue;
        }

        VLOG("make_fd_minidst", pINFO) << "+ Accepting event";
      }
      
      nev_accept++;
      nev_accept_by_mode[reac_mode]++;

      //~ VLOG("make_fd_minidst", pDEBUG) 
        //~ << "GENIE MC truth info: " << event;
        
      valor_minidst_sample    = sample; 
      valor_minidst_reac_mode = reac_mode;
      valor_minidst_enu_true  = enu_true; 
      valor_minidst_enu_reco  = enu_reco; 
      valor_minidst_wght_pot  = 1./total_pot_read_per_run[run]; 
      valor_minidst_Q2_true   = Q2s;
      
      valor_minidst_target    = 1000180400; // FORCE ARGON40 FOR NOW
      valor_minidst_y_reco    = 0.5; // FORCE y=0.5 for now
      
      VLOG("make_fd_minidst", pINFO) 
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
    }//smearing histogram loop
  } // event loop
  
  for (unsigned int im = 0 ; im < nev_accept_by_mode.size(); im++) {
    valor::conv::ReacMode_t m = (valor::conv::ReacMode_t)im;
    VLOG("make_fd_minidst", pNOTICE) << "Selected "<<nev_accept_by_mode[im]<<" events of mode "<<valor::util::AsString(m);
  }
  
  double f = 100. * (double)nev_accept / (double)nev;
  VLOG("make_fd_minidst", pNOTICE) <<
    "Used " << f << "% (" << nev_accept << "/" << nev 
    << ") of input events.";
    
  //~ VLOG("make_fd_minidst", pNOTICE) <<
    //~ "Total POT read: "<<total_pot_read;

  // Saving VALOR mini-FST to output file 
  VLOG("make_fd_minidst", pNOTICE) 
    << "Saving VALOR/DUNE mini-DST to: " << opt_output_name;
  valor_minidst->Write();  
  fout.Close();

  VLOG("make_fd_minidst", pNOTICE)  << "Done!";

  return 0;
}
//___________________________________________________________________
double GetTotalPOT(std::string filename, int runno)
{
  TChain pot_tree("mvaselect/pottree");
  double totpot = 0.;
  double thispot = -9E99;
  int this_runno = -1;
  pot_tree.Add(filename.c_str());
  pot_tree.SetBranchAddress("pot",&thispot);
  pot_tree.SetBranchAddress("run",&this_runno);
  for (int iev = 0 ; iev < pot_tree.GetEntries() ; iev++) {
    pot_tree.GetEntry(iev);
    if (this_runno == runno) {
      totpot += thispot;
    }
  }
  return totpot;
}
//___________________________________________________________________
