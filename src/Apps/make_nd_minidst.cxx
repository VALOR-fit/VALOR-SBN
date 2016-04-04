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

//
#include <TFile.h>
#include <TTree.h>
#include <TLeaf.h>

// genie
#include "Conventions/GBuild.h"
#include "EVGCore/EventRecord.h"
#include "GHEP/GHepParticle.h"
#include "Ntuple/NtpMCFormat.h"
#include "Ntuple/NtpMCTreeHeader.h"
#include "Ntuple/NtpMCEventRecord.h"
#include "Messenger/Messenger.h"
#include "PDG/PDGCodes.h"
#include "Utils/CmdLnArgParser.h"
#include "Utils/RunOpt.h"
// valor/dune
#include "Conventions/BeamConf.h"
#include "Conventions/ReacMode.h"
#include "SDFit/NDSample.h"

using std::string;
using namespace genie;
using namespace valor;

string gOptInpFileFormat;
string gOptInpFileName;
string gOptOutFileName;
bool   gOptDisableChecks;

void GetCommandLineArgs (int argc, char ** argv);

conv::ReacMode_t DetermineReactionMode(EventRecord &  event);

//___________________________________________________________________
int main(int argc, char ** argv)
{
  GetCommandLineArgs (argc, argv);

  // Set print level
  GHepRecord::SetPrintLevel(RunOpt::Instance()->EventRecordPrintLevel());

  // Create output mini-DST   

  int    valor_minidst_beam      = -1; // see Conventions/BeamConf.h 
  int    valor_minidst_sample    = -1; // see SDFit/NDSample.h 
  int    valor_minidst_reac_mode = -1; // see Conventions/ReacMode.h 
  double valor_minidst_enu_true  = -1; // true neutrino energy, in GeV
  double valor_minidst_enu_reco  = -1; // reco neutrino energy, in GeV
  double valor_minidst_y_reco    = -1; // inelasticity, in GeV
  double valor_minidst_wght_pot  = -1; // POT weight 

  TTree * valor_minidst = 
   new TTree("valor_dune_nd_mini_dst","Mini-DST input for VALOR/DUNE ND Fit");

  valor_minidst->Branch("beam",      &valor_minidst_beam,      "beam/I"     );
  valor_minidst->Branch("sample",    &valor_minidst_sample,    "sample/I"   );
  valor_minidst->Branch("reac_mode", &valor_minidst_reac_mode, "reac_mode/I");
  valor_minidst->Branch("enu_true",  &valor_minidst_enu_true,  "enu_true/D" );
  valor_minidst->Branch("enu_reco",  &valor_minidst_enu_reco,  "enu_reco/D" );
  valor_minidst->Branch("y_reco",    &valor_minidst_y_reco,    "y_reco/D"   );
  valor_minidst->Branch("wght_pot",  &valor_minidst_wght_pot,  "wght_pot/D" );

  // open the ROOT file and get the TTree & its header

  TFile fin(gOptInpFileName.c_str(),"READ");

  string tree_name = "";

  if(gOptInpFileFormat == "hpgartpc") {
     tree_name = "GasTPCTree";
  } 
  else
  if(gOptInpFileFormat == "lartpc" || gOptInpFileFormat == "fgt") {
     tree_name = "dune_dst";
  }
  else {
      LOG("make_minidst", pFATAL) 
          << "Unknown input file format. Please specify one of hpgartpc, lartpc or fgt";
      exit(1);
  }

  TTree * analysis_tree = dynamic_cast <TTree *> (fin.Get(tree_name.c_str()));
  if(!analysis_tree) {
    LOG("make_minidst", pFATAL) 
        << "No event tree " << tree_name 
        << " in " << gOptInpFileFormat << "-format input file: "
        << gOptInpFileName;
    exit(1);
  }

  Long64_t nev = analysis_tree->GetEntries();
  LOG("make_minidst", pNOTICE) 
     << "Input analysis tree has " << nev << ((nev==1) ? " entry." : " entries.");

  NtpMCEventRecord * mcrec = 0;
  int    sample        = -1;
  int    reac_mode     = -1;
  double enu_true      =  0.;
  double enu_reco      =  0.;
  double y_reco        =  0.;
  double wght_pot      =  0.;

  if(gOptInpFileFormat == "hpgartpc") {
    analysis_tree->SetBranchAddress("gmcrec",          &mcrec);
    analysis_tree->SetBranchAddress("sample",          &sample);
    analysis_tree->SetBranchAddress("reactionmode",    &reac_mode);
//  analysis_tree->SetBranchAddress("Ev_All",          &enu_true);
    analysis_tree->SetBranchAddress("Ev",              &enu_true);
    analysis_tree->SetBranchAddress("Ev_reco",         &enu_reco);
    analysis_tree->SetBranchAddress("y_reco",          &y_reco);
    analysis_tree->SetBranchAddress("POTWeight",       &wght_pot);
  }
  else
  if(gOptInpFileFormat == "lartpc" || gOptInpFileFormat == "fgt") {
    analysis_tree->SetBranchAddress("genie_mc_truth",  &mcrec);
    analysis_tree->SetBranchAddress("sample",          &sample);
    analysis_tree->SetBranchAddress("reactionmode",    &reac_mode);
    analysis_tree->SetBranchAddress("Ev",              &enu_true);
    analysis_tree->SetBranchAddress("Ev_reco",         &enu_reco);
    analysis_tree->SetBranchAddress("y_reco",          &y_reco);
    analysis_tree->SetBranchAddress("POTWeight",       &wght_pot);
  }

  //
  // event loop
  //

  Long64_t nev_accept = 0;

  for(Long64_t iev = 0; iev < nev; iev++) {

    LOG("make_minidst", pNOTICE) << "** Reading event: " << iev;

    analysis_tree->GetEntry(iev);

    // hpgartpc output in MeV, convert to GeV as in lartpc and fgt outputs
    if(gOptInpFileFormat == "hpgartpc") {
      enu_true = enu_true/1000.;
      enu_reco = enu_reco/1000.;
    }

    if(!gOptDisableChecks) {
      //
      // ignore events that can not be used in the VALOR analysis
      //
      if(sample == conv::ksUndefined) {
        LOG("make_minidst", pNOTICE) << "- Rejecting event [undefined sample]";
        mcrec->Clear();
        continue;
      }
      if(enu_reco <= 0) {
        LOG("make_minidst", pNOTICE) << "- Rejecting event [Ev (reco) <= 0]";
        mcrec->Clear();
        continue;
      }
      if(y_reco < 0) {
        LOG("make_minidst", pNOTICE) << "- Rejecting event [y (reco) < 0]";
        mcrec->Clear();
        continue;
      }

      LOG("make_minidst", pNOTICE) << "+ Accepting event";
    }
    nev_accept++;

    // retrieve GHEP event record and print it out.
    NtpMCRecHeader rec_header = mcrec->hdr;
    EventRecord &  event = *(mcrec->event);
    LOG("make_minidst", pNOTICE) 
       << "GENIE MC truth info: " << event;

    valor_minidst_sample    = sample; 
    valor_minidst_reac_mode = reac_mode; 
    valor_minidst_enu_true  = enu_true; 
    valor_minidst_enu_reco  = enu_reco; 
    valor_minidst_y_reco    = y_reco; 
    valor_minidst_wght_pot  = wght_pot; 

    LOG("make_minidst", pNOTICE) 
       << "\n Information copied to VALOR DUNE/ND Mini-DST: "
       << "\n Beam          = " << valor_minidst_beam   
       << "\n Sample        = " << valor_minidst_sample    
       << "\n Reaction mode = " << valor_minidst_reac_mode 
       << "\n Ev (true)     = " << valor_minidst_enu_true << " GeV"
       << "\n Ev (reco)     = " << valor_minidst_enu_reco << " GeV" 
       << "\n y (reco)      = " << valor_minidst_y_reco    
       << "\n weight        = " << valor_minidst_wght_pot;

    valor_minidst->Fill();

    mcrec->Clear();
  }

  LOG("make_minidst", pNOTICE) << "Closing input file";
  fin.Close();

  double f = 100. * (double)nev_accept / (double)nev;
  LOG("make_minidst", pNOTICE) 
     "Used " << f << "% (" << nev_accept << "/" << nev 
     << ") of input events.";

  // Saving VALOR mini-FST to output file 
  LOG("make_minidst", pNOTICE) 
      << "Saving VALOR/DUNE mini-DST to: " << gOptOutFileName;
  TFile fout(gOptOutFileName.c_str(),"recreate");
  valor_minidst->Write();  
  fout.Close();

  LOG("make_minidst", pNOTICE)  << "Done!";

  return 0;
}
//___________________________________________________________________
void GetCommandLineArgs(int argc, char ** argv)
{
//  LOG("make_minidst", pINFO) << "*** Parsing command line arguments";

  // Common run options.
  RunOpt::Instance()->ReadFromCommandLine(argc,argv);

  // Parse run options for this app

  CmdLnArgParser parser(argc,argv);

  if ( parser.OptionExists("format") ) {
    LOG("make_minidst", pNOTICE) << "Reading input format";
    gOptInpFileFormat = parser.ArgAsString("format");
  } else {
    LOG("make_minidst", pFATAL) 
       << "Unspecified input file format - Exiting";
    gAbortingInErr = true;
    exit(1);
  }

  if ( parser.OptionExists("input") ) {
    LOG("make_minidst", pNOTICE) << "Reading analysis file";
    gOptInpFileName = parser.ArgAsString("input");
  } else {
    LOG("make_minidst", pFATAL) 
       << "Unspecified input file - Exiting";
    gAbortingInErr = true;
    exit(1);
  }

  if ( parser.OptionExists("output") ) {
    LOG("make_minidst", pINFO) << "Reading output file name";
    gOptOutFileName = parser.ArgAsString("output");
  } else {
    gOptOutFileName = "out.root";
  }

  gOptDisableChecks = false;
  if ( parser.OptionExists("disable-checks") ) {
    LOG("make_minidst", pINFO) << "Disabling checks and accepting all input events";
    gOptDisableChecks = true;
  } 

}
//_________________________________________________________________________________
conv::ReacMode_t DetermineReactionMode(EventRecord & event)
{
   int  nupdg       = event.Probe()->Pdg();
   bool is_nue      = (nupdg == kPdgNuE);
   bool is_numu     = (nupdg == kPdgNuMu);
   bool is_nuebar   = (nupdg == kPdgAntiNuE);
   bool is_numubar  = (nupdg == kPdgAntiNuMu);

   bool is_CC       = event.Summary()->ProcInfo().IsWeakCC();
   bool is_NC       = event.Summary()->ProcInfo().IsWeakNC();
   bool is_strange  = false;
   bool is_charm    = false;
   bool is_QE       = event.Summary()->ProcInfo().IsQuasiElastic() && !is_strange && !is_charm;
   bool is_MEC      = event.Summary()->ProcInfo().IsMEC();
   bool is_Coherent = event.Summary()->ProcInfo().IsCoherent();

   int npiC = 0; // count them
   int npi0 = 0;

   bool is_1piC     = (!is_Coherent) && (npiC==1) && (npi0==0);
   bool is_1pi0     = (!is_Coherent) && (npiC==0) && (npi0==1); 
   bool is_2piC     = (!is_Coherent) && (npiC==2) && (npi0==0); 
   bool is_2pi0     = (!is_Coherent) && (npiC==0) && (npi0==2); 
   bool is_1piC1pi0 = (!is_Coherent) && (npiC==1) && (npi0==1); 

   //
   if(is_numu) {
    if(is_CC) {
      if      (is_QE)       return conv::kmNuMuCCQE;            // numu    CC QE
      else if (is_MEC)      return conv::kmNuMuCCMEC;           // numu    CC MEC
      else if (is_1piC)     return conv::kmNuMuCC1piC;          // numu    CC 1 pi+/-
      else if (is_1pi0)     return conv::kmNuMuCC1pi0;          // numu    CC 1 pi0
      else if (is_2piC)     return conv::kmNuMuCC2piC;          // numu    CC 2 pi+/-
      else if (is_2pi0)     return conv::kmNuMuCC2pi0;          // numu    CC 2 pi0
      else if (is_1piC1pi0) return conv::kmNuMuCCpiCpi0;        // numu    CC 1 pi0 + 1 pi+/-
      else if (is_Coherent) return conv::kmNuMuCCcoh;           // numu    CC coherent
      else                  return conv::kmNuMuCCoth;           // numu    CC other
    }
    if(is_NC) {
      if      (is_1piC)     return conv::kmNuMuNC1piC;          // numu    NC 1 pi+/-
      else if (is_1pi0)     return conv::kmNuMuNC1pi0;          // numu    NC 1 pi0
      else if (is_Coherent) return conv::kmNuMuNCcoh;           // numu    NC coherent
      else                  return conv::kmNuMuNCoth;           // numu    NC other
    }
   }

   //
   if(is_numubar) {
    if(is_CC) {
      if      (is_QE)       return conv::kmNuMuBarCCQE;         // numubar CC QE
      else if (is_MEC)      return conv::kmNuMuBarCCMEC;        // numubar CC MEC
      else if (is_1piC)     return conv::kmNuMuBarCC1piC;       // numubar CC 1 pi+/-
      else if (is_1pi0)     return conv::kmNuMuBarCC1pi0;       // numubar CC 1 pi0
      else if (is_2piC)     return conv::kmNuMuBarCC2piC;       // numubar CC 2 pi+/-
      else if (is_2pi0)     return conv::kmNuMuBarCC2pi0;       // numubar CC 2 pi0
      else if (is_1piC1pi0) return conv::kmNuMuBarCCpiCpi0;     // numubar CC 1 pi0 + 1 pi+/-
      else if (is_Coherent) return conv::kmNuMuBarCCcoh;        // numubar CC coherent
      else                  return conv::kmNuMuBarCCoth;        // numubar CC other
    }
    if(is_NC) {
      if      (is_1piC)     return conv::kmNuMuBarNC1piC;       // numubar NC 1 pi+/-
      else if (is_1pi0)     return conv::kmNuMuBarNC1pi0;       // numubar NC 1 pi0
      else if (is_Coherent) return conv::kmNuMuBarNCcoh;        // numubar NC coherent
      else                  return conv::kmNuMuBarNCoth;        // numubar NC other
    }
   }

   //
   if(is_nue) {
    if(is_CC) {
      if      (is_QE)       return conv::kmNuECCQE;             // nue     CC QE
      else if (is_MEC)      return conv::kmNuECCMEC;            // nue     CC MEC
      else if (is_1piC)     return conv::kmNuECC1piC;           // nue     CC 1 pi+/-
      else if (is_1pi0)     return conv::kmNuECC1pi0;           // nue     CC 1 pi0
      else if (is_2piC)     return conv::kmNuECC2piC;           // nue     CC 2 pi+/-
      else if (is_2pi0)     return conv::kmNuECC2pi0;           // nue     CC 2 pi0
      else if (is_1piC1pi0) return conv::kmNuECCpiCpi0;         // nue     CC 1 pi0 + 1 pi+/-
      else if (is_Coherent) return conv::kmNuECCcoh;            // nue     CC coherent
      else                  return conv::kmNuECCoth;            // nue     CC other
    }
    if(is_NC) {
      if      (is_1piC)     return conv::kmNuENC1piC;           // nue     NC 1 pi+/-
      else if (is_1pi0)     return conv::kmNuENC1pi0;           // nue     NC 1 pi0
      else if (is_Coherent) return conv::kmNuENCcoh;            // nue     NC coherent
      else                  return conv::kmNuENCoth;            // nue     NC other
    }
   }

   //
   if(is_nuebar) {
    if(is_CC) {
      if      (is_QE)       return conv::kmNuEBarCCQE;          // nuebar  CC QE
      else if (is_MEC)      return conv::kmNuEBarCCMEC;         // nuebar  CC MEC
      else if (is_1piC)     return conv::kmNuEBarCC1piC;        // nuebar  CC 1 pi+/-
      else if (is_1pi0)     return conv::kmNuEBarCC1pi0;        // nuebar  CC 1 pi0
      else if (is_2piC)     return conv::kmNuEBarCC2piC;        // nuebar  CC 2 pi+/-
      else if (is_2pi0)     return conv::kmNuEBarCC2pi0;        // nuebar  CC 2 pi0
      else if (is_1piC1pi0) return conv::kmNuEBarCCpiCpi0;      // nuebar  CC 1 pi0 + 1 pi+/-
      else if (is_Coherent) return conv::kmNuEBarCCcoh;         // nuebar  CC coherent
      else                  return conv::kmNuEBarCCoth;         // nuebar  CC other
    }
    if(is_NC) {
      if      (is_1piC)     return conv::kmNuEBarNC1piC;        // nuebar  NC 1 pi+/-
      else if (is_1pi0)     return conv::kmNuEBarNC1pi0;        // nuebar  NC 1 pi0
      else if (is_Coherent) return conv::kmNuEBarNCcoh;         // nuebar  NC coherent
      else                  return conv::kmNuEBarNCoth;         // nuebar  NC other
    }
   }

   return conv::kmUndefined;
}
//_________________________________________________________________________________

