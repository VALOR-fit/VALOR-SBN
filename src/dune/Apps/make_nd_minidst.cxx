//____________________________________________________________________________
/*!

  \app       valor_dune-make_nd_minidst

  \brief     Converts input ND analysis DSTs to the VALOR SDFit mini-DST format.

  \syntax    valor_dune-make_nd_minidst 
  --input  input_analysis_file.root
  --output output_file_containing_valor_minidst.root
  [--format format_of_the_input_file <hpgartpc, lartpc, fgt>]
  [--disable-checks]

  \author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
  University of Liverpool & STFC Rutherford Appleton Laboratory

  \created   March 27, 2014

  \copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#include <string>
#include <iostream>
#include <sstream>

//
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TSystem.h>

// valor/dune
#include "valor/Messenger/Messenger.h"
#include "valor/Conventions/BeamConf.h"
#include "valor/Conventions/ReacMode.h"
#include "valor/Conventions/Sample.h"

#include "dune/GENIEUtilities/GENIEIncludes.h"
#include "dune/GENIEUtilities/UtlEventRec.h"

using std::string;
using std::ostringstream;

string gOptInpFileFormat;
string gOptInpFileName;
string gOptOutFileName;
bool   gOptDisableChecks;

void GetCommandLineArgs (int /*argc*/, char ** /*argv*/);

static const int gPrintEveryNEvents = 50000;

//___________________________________________________________________
int main(int argc, char ** argv)
{
  // Set GENIE print level
  genie::GHepRecord::SetPrintLevel(genie::RunOpt::Instance()->EventRecordPrintLevel());
  
  TString messenger_config("$VALOR_EXPT/config/verbosity.xml");
  gSystem->ExpandPathName(messenger_config);
  valor::Messenger::Instance()->Configure(messenger_config.Data());
  
  GetCommandLineArgs (argc, argv);

  // Create output mini-DST   

  int    valor_minidst_beam       = -99; // see Conventions/BeamConf.h 
  int    valor_minidst_sample     = -99; // see SDFit/NDSample.h 
  int    valor_minidst_reac_mode  = -99; // see Conventions/ReacMode.h 
  int    valor_minidst_target     = -99; // nuclear target -  GENIE PDG convention
  double valor_minidst_enu_true   = -99; // true neutrino energy, in GeV
  double valor_minidst_Q2_true    = -99; // true neutrino energy, in GeV
  double valor_minidst_enu_reco   = -99; // reco neutrino energy, in GeV
  double valor_minidst_y_reco     = -99; // inelasticity, in GeV
  double valor_minidst_wght       = 1.; // misc weight 
  double valor_minidst_wght_pot   = 1.; // POT weight 
  double valor_minidst_wght_smear = 1.; // Kinematic smearing weight (always 1 in the ND since our files are already smeared)
  
  TFile fout(gOptOutFileName.c_str(),"recreate");
  fout.cd();
  TTree * valor_minidst = 
    new TTree("valor_dune_nd_mini_dst","Mini-DST input for VALOR/DUNE ND Fit");

  valor_minidst->Branch("beam"        , &valor_minidst_beam,       "beam/I"      );
  valor_minidst->Branch("sample"      , &valor_minidst_sample,     "sample/I"    );
  valor_minidst->Branch("reac_mode"   , &valor_minidst_reac_mode,  "reac_mode/I" );
  valor_minidst->Branch("target"      , &valor_minidst_target,     "target/I"    );
  valor_minidst->Branch("enu_true"    , &valor_minidst_enu_true,   "enu_true/D"  );
  valor_minidst->Branch("Q2_true"     , &valor_minidst_Q2_true,    "q2_true/D"   );
  valor_minidst->Branch("enu_reco"    , &valor_minidst_enu_reco,   "enu_reco/D"  );
  valor_minidst->Branch("y_reco"      , &valor_minidst_y_reco,     "y_reco/D"    );
  valor_minidst->Branch("wght"        , &valor_minidst_wght,       "wght/D"      );
  valor_minidst->Branch("wght_pot"    , &valor_minidst_wght_pot,   "wght_pot/D"  );
  valor_minidst->Branch("wght_smear"  , &valor_minidst_wght_smear, "wght_smear/D");
  
  // Tmp - while we still have 2 reco variables, save both
  int    valor_minidst_sample_o    = -999; // see SDFit/NDSample.h 
  int    valor_minidst_sample_r    = -999; // see SDFit/NDSample.h 
  valor_minidst->Branch("sample_orig", &valor_minidst_sample_o,    "sample_orig/I");
  valor_minidst->Branch("sample_reco", &valor_minidst_sample_r,    "sample_reco/I");

  // open the ROOT file and get the TTree & its header
  
  string tree_name = "";
  bool gar_format = false;

  if(gOptInpFileFormat == "hpgartpc") {
    tree_name = "NdtfDst";
    gar_format = true;
  } 
  else {
    if(gOptInpFileFormat == "lartpc" || gOptInpFileFormat == "fgt") {
      tree_name = "dune_dst";
    }
    else {
      VLOG("make_minidst", pFATAL) 
        << "Unknown input file format: "<<gOptInpFileFormat<<" - please specify one of hpgartpc, lartpc or fgt";
      exit(1);
    }
  }

  TChain * analysis_tree = new TChain(tree_name.c_str());
  analysis_tree->Add(gOptInpFileName.c_str());
  if(!analysis_tree || !analysis_tree->GetEntries()) {
    VLOG("make_minidst", pFATAL) 
      << "Unable to read " << tree_name 
      << " in " << gOptInpFileFormat << "-format input file: "
      << gOptInpFileName;
    exit(1);
  }

  Long64_t nev = analysis_tree->GetEntries();
  VLOG("make_minidst", pNOTICE) 
    << "Input analysis tree has " << nev << ((nev==1) ? " entry." : " entries.");
  analysis_tree->GetEntry(0);

  genie::NtpMCEventRecord * mcrec = new genie::NtpMCEventRecord;
  int    sample         = -1;
  int    sample_orig    = -1;
  int    sample_reco    = -1;
  int    reac_mode      = -1;
  double enu_true       =  -999.;
  double enu_reco       =  -999.;
  double y_reco         =  -999.;
  double wght           =  1.;
  double wght_pot       =  1.;
  
  float enu_true_float =  -999.;
  float enu_reco_float =  -999.;
  float y_reco_float   =  -999.;
  float wght_pot_float =  -999.;
  float wght_tgt_float =  -999.;
  
  double total_pot_read = 0.;
  
  TBranch * branchptr = 0;
  
  vector<TBranch*> active_branches;
  if(gOptInpFileFormat == "hpgartpc") {
    analysis_tree->SetBranchAddress("gmcrec",          &mcrec          , &branchptr); active_branches.push_back(branchptr);
    analysis_tree->SetBranchAddress("Sample",          &sample_orig    , &branchptr); active_branches.push_back(branchptr);
    //~ analysis_tree->SetBranchAddress("reactionmode",    &reac_mode      , &branchptr); active_branches.push_back(branchptr);
    //  analysis_tree->SetBranchAddress("Ev_All",          &enu_true   , &branchptr); active_branches.push_back(branchptr);
    analysis_tree->SetBranchAddress("Ev",              &enu_true       , &branchptr); active_branches.push_back(branchptr);
    analysis_tree->SetBranchAddress("Ev_reco",         &enu_reco       , &branchptr); active_branches.push_back(branchptr);
    analysis_tree->SetBranchAddress("Y",          &y_reco         , &branchptr); active_branches.push_back(branchptr);
    //~ analysis_tree->SetBranchAddress("POTWeight",       &wght_pot       , &branchptr); active_branches.push_back(branchptr);
  }
  else if (gOptInpFileFormat == "lartpc" || gOptInpFileFormat == "fgt") {
    analysis_tree->SetBranchAddress("sample",          &sample_orig    , &branchptr); active_branches.push_back(branchptr);
    analysis_tree->SetBranchAddress("sample_reco",     &sample_reco    , &branchptr); active_branches.push_back(branchptr);
    //~ analysis_tree->SetBranchAddress("reactionmode",    &reac_mode  , &branchptr); active_branches.push_back(branchptr);
    analysis_tree->SetBranchAddress("Ev",              &enu_true_float , &branchptr); active_branches.push_back(branchptr);
    analysis_tree->SetBranchAddress("Ev_reco",         &enu_reco_float , &branchptr); active_branches.push_back(branchptr);
    analysis_tree->SetBranchAddress("y_reco",          &y_reco_float   , &branchptr); active_branches.push_back(branchptr);
    analysis_tree->SetBranchAddress("POTWeight",       &wght_pot_float , &branchptr); active_branches.push_back(branchptr);
    analysis_tree->SetBranchAddress("TGTWeight",       &wght_tgt_float , &branchptr); active_branches.push_back(branchptr);
    analysis_tree->SetBranchAddress("genie_mc_truth",  &mcrec          , &branchptr); active_branches.push_back(branchptr);
  }
  else {
    VLOG("make_minidst",pFATAL) << "Unknown input format: "<<gOptInpFileFormat;
    exit(-1);
  }


  Long64_t nev_accept = 0;
  
  std::vector<int> nev_accept_by_mode;
  for (int im = 0 ; im < valor::conv::kNReacModes; im++) {
    nev_accept_by_mode.push_back(0);
  }
  
  
    
  //
  // event loop to get total POT
  //
  
  // Disable all branches except POT weight
  analysis_tree->SetBranchStatus("*",0);
  analysis_tree->SetBranchStatus("POTWeight",1);
    
  VLOG("make_minidst", pNOTICE) << "Doing loop to calculate total POT";
  int last_tree_number = -1; // store which number file we're in, so we can count each tree's weight once
  for(Long64_t iev = 0; iev < nev; iev++) {
    analysis_tree->GetEntry(iev);
    if (gPrintEveryNEvents && !(iev%gPrintEveryNEvents)) {
      VLOG("make_minidst", pNOTICE) << "** Reading event: " << iev;
    }
    // Add to total POT - currently doing this BEFORE checks
    if (gOptInpFileFormat == "lartpc" || gOptInpFileFormat == "fgt") {
      total_pot_read += wght_pot_float;
    }
    else {
      if (last_tree_number!=analysis_tree->GetTreeNumber()) {
        total_pot_read+=analysis_tree->GetWeight();
      }
    }
    last_tree_number = analysis_tree->GetTreeNumber();
  }
  VLOG("make_minidst", pNOTICE) << "Total POT read: "<<total_pot_read;
  
  // Enable all the branches we actually care about
  for (unsigned int ib = 0 ; ib < active_branches.size(); ib++) {
    assert(active_branches[ib]);
    active_branches[ib]->SetStatus(1);
    TObjArray * bar = active_branches[ib]->GetListOfBranches();
    if (bar) {
      for (int ie = 0 ; ie < bar->GetEntries(); ie++) {
        TBranch * b = dynamic_cast<TBranch*>(bar->At(ie));
        assert(b);
        b->SetStatus(1);
      }
    }
  }
  
  
  //
  // event loop to fill my output tree
  //
  for(Long64_t iev = 0; iev < nev; iev++) {
    
    if (mcrec) {mcrec->Clear();}

    if (gPrintEveryNEvents && !(iev%gPrintEveryNEvents)) {
      VLOG("make_minidst", pNOTICE) << "** Reading event: " << iev;
    }
    else {
      VLOG("make_minidst", pINFO) << "** Reading event: " << iev;
    }

    analysis_tree->GetEntry(iev);

    // hpgartpc output in MeV, convert to GeV as in lartpc and fgt outputs
    if(gOptInpFileFormat == "hpgartpc") {
      enu_true = enu_true/1000.;
      enu_reco = enu_reco/1000.;
      sample = sample_orig;
    }
    
    // FGT output uses floats instead. Copy into the doubles we use
    if (gOptInpFileFormat == "lartpc" || gOptInpFileFormat == "fgt") {
      enu_true   = enu_true_float;
      enu_reco   = enu_reco_float;
      y_reco     = y_reco_float;
      //~ wght_pot   = wght_pot_float;
      sample = sample_reco;
    }
    
    VLOG("make_minidist",pDEBUG) << "Read event: "
      << "Sample   = "<<sample    << "; "
      << "Etrue    = "<<enu_true  << " GeV; "
      << "Ereco    = "<<enu_reco  << " GeV; "
      << "Yreco    = "<<y_reco    << "; "
      << "POTwght  = "<<wght_pot  << "; "
      << "MCRecPtr = "<< mcrec;
      
    if(!gOptDisableChecks) {
      
      if(mcrec->event == NULL) {
        VLOG("make_minidst", pNOTICE) << "- Rejecting event [null GENIE record]";
        continue;
      }
      
      //
      // ignore events that can not be used in the VALOR analysis
      //
      if(sample == valor::conv::ksUndefined) {
        VLOG("make_minidst", pNOTICE) << "- Rejecting event [undefined sample]: "<<sample;
        continue;
      }
      if(enu_reco <= 0) {
        VLOG("make_minidst", pNOTICE) << "- Rejecting event [Ev (reco) <= 0]: "<<enu_reco;
        continue;
      }
      if( (y_reco < 0 || y_reco > 1) ) {
        if (valor::util::IsCC((valor::conv::Sample_t)sample)) {
          VLOG("make_minidst", pNOTICE) << "- Rejecting CC event [y (reco) < 0]: "<<y_reco;
          continue;
        }
        else {
          y_reco = 0.5; //arbitary value for samples without y defined
        }
      }

      VLOG("make_minidst", pINFO) << "+ Accepting event";
    }
    
    //    valor::conv::ReacMode_t reac_mode = valor::util::DetermineReactionMode(mcrec->event, false);
    
    nev_accept++;
    nev_accept_by_mode[reac_mode]++;

    // retrieve GHEP event record and print it out.
    genie::NtpMCRecHeader rec_header = mcrec->hdr;
    genie::EventRecord &  event = *(mcrec->event);

    std::vector<double> vars1 = valor::util::GetTrueKinematics(&event,
          valor::conv::kspEtrue);
    VLOG("make_minidst", pERROR) << "Etrue " << vars1[0];
    std::vector<double> vars2 = valor::util::GetTrueKinematics(&event,
          valor::conv::kspEtrueQ2true);
    VLOG("make_minidst", pERROR) << "Etrue " << vars2[0] << " Q2 " << vars2[1];

    VLOG("make_minidst", pDEBUG) 
      << "GENIE MC truth info: " << event;
      
    valor_minidst_sample    = sample; 
    //    valor_minidst_reac_mode = reac_mode;
    valor_minidst_reac_mode = valor::util::DetermineReactionMode(mcrec->event, false); 
    valor_minidst_enu_true  = enu_true; 
    valor_minidst_enu_reco  = enu_reco; 
    valor_minidst_y_reco    = y_reco; 
    valor_minidst_wght_pot  = 1./total_pot_read; 
    valor_minidst_Q2_true   = mcrec->event->Summary()->KinePtr()->Q2(true);
    valor_minidst_target    = mcrec->event->Summary()->InitState().TgtPdg();
    
    valor_minidst_sample_o  = sample_orig; 
    valor_minidst_sample_r  = sample_reco; 
    
    valor_minidst_wght = 1.;
    valor_minidst_wght *= wght_tgt_float;
    
    if(!gOptDisableChecks) {
      //
      // ignore events that can not be used in the VALOR analysis
      //
      if(valor_minidst_reac_mode == valor::conv::kmUndefined) {
        VLOG("make_minidst", pWARN) << "- Rejecting event [bad mode]";
        VLOG("make_minidst", pINFO) << event;
        continue;
      }
    }

    VLOG("make_minidst", pINFO) 
      << "\n Information copied to VALOR DUNE/ND Mini-DST: "
      << "\n Beam          = " << valor_minidst_beam   
      << "\n Sample        = " << valor_minidst_sample    
      << "\n Reaction mode = " << valor_minidst_reac_mode 
      << "\n Target        = " << valor_minidst_target
      << "\n Q2 (true)     = " << valor_minidst_Q2_true << " GeV^2"
      << "\n Ev (true)     = " << valor_minidst_enu_true << " GeV"
      << "\n Ev (reco)     = " << valor_minidst_enu_reco << " GeV" 
      << "\n y (reco)      = " << valor_minidst_y_reco    
      << "\n weight        = " << valor_minidst_wght_pot;
    
    valor_minidst->Fill();
  }
  
  for (unsigned int im = 0 ; im < nev_accept_by_mode.size(); im++) {
    valor::conv::ReacMode_t m = (valor::conv::ReacMode_t)im;
    VLOG("make_minidst", pNOTICE) << "Selected "<<nev_accept_by_mode[im]<<" events of mode "<<valor::util::AsString(m);
  }
  
  double f = 100. * (double)nev_accept / (double)nev;
  VLOG("make_minidst", pNOTICE) <<
    "Used " << f << "% (" << nev_accept << "/" << nev 
    << ") of input events.";
    
  VLOG("make_minidst", pNOTICE) <<
    "Total POT read: "<<total_pot_read;
  
  //~ if (total_pot_read>1) {
    //~ valor_minidst->SetWeight(1./total_pot_read);
  //~ }

  // Saving VALOR mini-FST to output file 
  VLOG("make_minidst", pNOTICE) 
    << "Saving VALOR/DUNE mini-DST to: " << fout.GetName();
  fout.cd();
  valor_minidst->Write();  
  fout.Close();

  VLOG("make_minidst", pNOTICE)  << "Done!";

  return 0;
}
//___________________________________________________________________
void GetCommandLineArgs(int argc, char ** argv)
{
  //  VLOG("make_minidst", pINFO) << "*** Parsing command line arguments";

  // Common run options.
  genie::RunOpt::Instance()->ReadFromCommandLine(argc,argv);

  // Parse run options for this app

  genie::CmdLnArgParser parser(argc,argv);

  if ( parser.OptionExists("format") ) {
    VLOG("make_minidst", pNOTICE) << "Reading input format";
    gOptInpFileFormat = parser.ArgAsString("format");
  } else {
    VLOG("make_minidst", pWARN) 
      << "Unspecified input file format - using FGT";
    gOptInpFileFormat = "fgt";
  }

  if ( parser.OptionExists("input") ) {
    VLOG("make_minidst", pNOTICE) << "Reading analysis file";
    gOptInpFileName = parser.ArgAsString("input");
  } else {
    VLOG("make_minidst", pFATAL) 
      << "Unspecified input file - Exiting";
    //~ genie::gAbortingInErr = true;
    exit(1);
  }

  if ( parser.OptionExists("output") ) {
    VLOG("make_minidst", pINFO) << "Reading output file name";
    gOptOutFileName = parser.ArgAsString("output");
  } else {
    gOptOutFileName = "out.root";
  }

  gOptDisableChecks = false;
  if ( parser.OptionExists("disable-checks") ) {
    VLOG("make_minidst", pINFO) << "Disabling checks and accepting all input events";
    gOptDisableChecks = true;
  } 

}
//_________________________________________________________________________________

