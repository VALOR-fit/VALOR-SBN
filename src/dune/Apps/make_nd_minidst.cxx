//____________________________________________________________________________
/*!

  \app       valor_dune-make_nd_minidst

  \brief     Converts input ND analysis DSTs to the VALOR SDFit mini-DST format.

  \syntax    valor_dune-make_nd_minidst 
  --input  input_analysis_file.root
  --output output_file_containing_valor_minidst.root
  --format format_of_the_input_file <hpgartpc, lartpc, fgt>
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
#include "valor/Messenger/Messenger.h"
#include "dune/Conventions/BeamConf.h"
#include "dune/Conventions/ReacMode.h"
#include "dune/Conventions/Sample.h"

#include "dune/GENIEUtilities/UtlEventRec.h"

using std::string;
using std::ostringstream;
using namespace valor;

string gOptInpFileFormat;
string gOptInpFileName;
string gOptOutFileName;
bool   gOptDisableChecks;

void GetCommandLineArgs (int /*argc*/, char ** /*argv*/);

//___________________________________________________________________
int main(int argc, char ** argv)
{
  TString messenger_config("$VALOR_DUNE/config/verbosity.xml");
  gSystem->ExpandPathName(messenger_config);
  valor::Messenger::Instance()->Configure(messenger_config.Data());
  
  GetCommandLineArgs (argc, argv);

  // Set print level
  genie::GHepRecord::SetPrintLevel(genie::RunOpt::Instance()->EventRecordPrintLevel());

  // Create output mini-DST   

  int    valor_minidst_beam      = -1; // see Conventions/BeamConf.h 
  int    valor_minidst_sample    = -1; // see SDFit/NDSample.h 
  int    valor_minidst_reac_mode = -1; // see Conventions/ReacMode.h 
  double valor_minidst_enu_true  = -1; // true neutrino energy, in GeV
  double valor_minidst_Q2_true   = -1; // true neutrino energy, in GeV
  double valor_minidst_enu_reco  = -1; // reco neutrino energy, in GeV
  double valor_minidst_y_reco    = -1; // inelasticity, in GeV
  double valor_minidst_wght_pot  = -1; // POT weight 

  TTree * valor_minidst = 
    new TTree("valor_dune_nd_mini_dst","Mini-DST input for VALOR/DUNE ND Fit");

  valor_minidst->Branch("beam",      &valor_minidst_beam,      "beam/I"     );
  valor_minidst->Branch("sample",    &valor_minidst_sample,    "sample/I"   );
  valor_minidst->Branch("reac_mode", &valor_minidst_reac_mode, "reac_mode/I");
  valor_minidst->Branch("enu_true",  &valor_minidst_enu_true,  "enu_true/D" );
  valor_minidst->Branch("Q2_true" ,  &valor_minidst_Q2_true,   "q2_true/D"  );
  valor_minidst->Branch("enu_reco",  &valor_minidst_enu_reco,  "enu_reco/D" );
  valor_minidst->Branch("y_reco",    &valor_minidst_y_reco,    "y_reco/D"   );
  valor_minidst->Branch("wght_pot",  &valor_minidst_wght_pot,  "wght_pot/D" );

  // open the ROOT file and get the TTree & its header
  
  string tree_name = "";

  if(gOptInpFileFormat == "hpgartpc") {
    tree_name = "GasTPCTree";
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

  genie::NtpMCEventRecord * mcrec = 0;
  int    sample         = -1;
  int    reac_mode      = -1;
  double enu_true       =  -999.;
  double enu_reco       =  -999.;
  double y_reco         =  -999.;
  double wght_pot       =  -999.;
  
  float enu_true_float =  -999.;
  float enu_reco_float =  -999.;
  float y_reco_float   =  -999.;
  float wght_pot_float =  -999.;
  
  TBranch * branchptr = 0;

  if(gOptInpFileFormat == "hpgartpc") {
    analysis_tree->SetBranchAddress("gmcrec",          &mcrec          , &branchptr);
    analysis_tree->SetBranchAddress("sample",          &sample         , &branchptr);
    analysis_tree->SetBranchAddress("reactionmode",    &reac_mode      , &branchptr);
    //  analysis_tree->SetBranchAddress("Ev_All",          &enu_true   , &branchptr);
    analysis_tree->SetBranchAddress("Ev",              &enu_true       , &branchptr);
    analysis_tree->SetBranchAddress("Ev_reco",         &enu_reco       , &branchptr);
    analysis_tree->SetBranchAddress("y_reco",          &y_reco         , &branchptr);
    analysis_tree->SetBranchAddress("POTWeight",       &wght_pot       , &branchptr);
  }
  else if (gOptInpFileFormat == "lartpc" || gOptInpFileFormat == "fgt") {
    analysis_tree->SetBranchAddress("genie_mc_truth",  &mcrec          , &branchptr);
    //~ analysis_tree->SetBranchAddress("sample_reco",          &sample         , &branchptr);
    analysis_tree->SetBranchAddress("sample",          &sample         , &branchptr);
    analysis_tree->SetBranchAddress("reactionmode",    &reac_mode      , &branchptr);
    analysis_tree->SetBranchAddress("Ev",              &enu_true_float , &branchptr);
    analysis_tree->SetBranchAddress("Ev_reco",         &enu_reco_float , &branchptr);
    analysis_tree->SetBranchAddress("y_reco",          &y_reco_float   , &branchptr);
    analysis_tree->SetBranchAddress("POTWeight",       &wght_pot_float , &branchptr);
  }
  else {
    VLOG("make_minidst",pFATAL) << "Unknown input format: "<<gOptInpFileFormat;
    exit(-1);
  }
  
  //
  // event loop
  //

  Long64_t nev_accept = 0;

  for(Long64_t iev = 0; iev < nev; iev++) {

    VLOG("make_minidst", pINFO) << "** Reading event: " << iev;

    analysis_tree->GetEntry(iev);

    // hpgartpc output in MeV, convert to GeV as in lartpc and fgt outputs
    if(gOptInpFileFormat == "hpgartpc") {
      enu_true = enu_true/1000.;
      enu_reco = enu_reco/1000.;
    }
    
    // FGT output uses floats instead. Copy into the doubles we use
    if (gOptInpFileFormat == "lartpc" || gOptInpFileFormat == "fgt") {
      enu_true   = enu_true_float;
      enu_reco   = enu_reco_float;
      y_reco     = y_reco_float;
      wght_pot   = wght_pot_float;
    }
    
    VLOG("make_minidist",pDEBUG) << "Read event: "
      << "Sample   = "<<sample    << "; "
      << "Etrue    = "<<enu_true  << " GeV; "
      << "Ereco    = "<<enu_reco  << " GeV; "
      << "Yreco    = "<<y_reco    << "; "
      << "POTwght  = "<<wght_pot  << "; "
      << "MCRecPtr = "<< mcrec;
      
    if(!gOptDisableChecks) {
      //
      // ignore events that can not be used in the VALOR analysis
      //
      if(sample == conv::ksUndefined) {
        VLOG("make_minidst", pNOTICE) << "- Rejecting event [undefined sample]";
        mcrec->Clear();
        continue;
      }
      if(enu_reco <= 0) {
        VLOG("make_minidst", pNOTICE) << "- Rejecting event [Ev (reco) <= 0]";
        mcrec->Clear();
        continue;
      }
      if(y_reco < 0) {
        VLOG("make_minidst", pNOTICE) << "- Rejecting event [y (reco) < 0]";
        mcrec->Clear();
        continue;
      }

      VLOG("make_minidst", pINFO) << "+ Accepting event";
    }
    nev_accept++;

    // retrieve GHEP event record and print it out.
    genie::NtpMCRecHeader rec_header = mcrec->hdr;
    genie::EventRecord &  event = *(mcrec->event);
    VLOG("make_minidst", pDEBUG) 
      << "GENIE MC truth info: " << event;
      
    valor_minidst_sample    = sample; 
    //~ valor_minidst_reac_mode = reac_mode; 
    valor_minidst_reac_mode = valor::util::DetermineReactionMode(mcrec->event);
    valor_minidst_enu_true  = enu_true; 
    valor_minidst_enu_reco  = enu_reco; 
    valor_minidst_y_reco    = y_reco; 
    valor_minidst_wght_pot  = wght_pot; 
    valor_minidst_Q2_true   = mcrec->event->Summary()->KinePtr()->Q2(true);
    
    if(!gOptDisableChecks) {
      //
      // ignore events that can not be used in the VALOR analysis
      //
      if(valor_minidst_reac_mode == conv::kmUndefined) {
        ostringstream eventlog;
        event.Print(eventlog);
        VLOG("make_minidst", pWARN) << "- Rejecting event [bad mode]\n";
        VLOG("make_minidst", pINFO) << eventlog.str();
        mcrec->Clear();
        continue;
      }
    }

    VLOG("make_minidst", pINFO) 
      << "\n Information copied to VALOR DUNE/ND Mini-DST: "
      << "\n Beam          = " << valor_minidst_beam   
      << "\n Sample        = " << valor_minidst_sample    
      << "\n Reaction mode = " << valor_minidst_reac_mode 
      << "\n Q2 (true)     = " << valor_minidst_Q2_true << " GeV^2"
      << "\n Ev (true)     = " << valor_minidst_enu_true << " GeV"
      << "\n Ev (reco)     = " << valor_minidst_enu_reco << " GeV" 
      << "\n y (reco)      = " << valor_minidst_y_reco    
      << "\n weight        = " << valor_minidst_wght_pot;

    valor_minidst->Fill();

    mcrec->Clear();
  }
  
  double f = 100. * (double)nev_accept / (double)nev;
  VLOG("make_minidst", pNOTICE) 
    "Used " << f << "% (" << nev_accept << "/" << nev 
    << ") of input events.";

  // Saving VALOR mini-FST to output file 
  VLOG("make_minidst", pNOTICE) 
    << "Saving VALOR/DUNE mini-DST to: " << gOptOutFileName;
  TFile fout(gOptOutFileName.c_str(),"recreate");
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
    VLOG("make_minidst", pFATAL) 
      << "Unspecified input file format - Exiting";
    genie::gAbortingInErr = true;
    exit(1);
  }

  if ( parser.OptionExists("input") ) {
    VLOG("make_minidst", pNOTICE) << "Reading analysis file";
    gOptInpFileName = parser.ArgAsString("input");
  } else {
    VLOG("make_minidst", pFATAL) 
      << "Unspecified input file - Exiting";
    genie::gAbortingInErr = true;
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

