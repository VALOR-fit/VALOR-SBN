//____________________________________________________________________________
/*!

\app       valor_dune-make_minidst

\brief     Converts the input analysis DST to the VALOR mini DST format.

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\created   March 27, 2014

\copyright (c) 2010-2015, The VALOR Fitting Group, All Rights Reserved

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
#include "Ntuple/NtpMCFormat.h"
#include "Ntuple/NtpMCTreeHeader.h"
#include "Ntuple/NtpMCEventRecord.h"
#include "Messenger/Messenger.h"
#include "Utils/CmdLnArgParser.h"
#include "Utils/RunOpt.h"

using std::string;
using namespace genie;

void GetCommandLineArgs (int argc, char ** argv);

string gOptInpFilename;

//___________________________________________________________________
int main(int argc, char ** argv)
{
  GetCommandLineArgs (argc, argv);

  // set print level
  GHepRecord::SetPrintLevel(RunOpt::Instance()->EventRecordPrintLevel());

  // Open output file & create output mini-DST 
  //
  LOG("make_minidst", pNOTICE) 
      << "*** Saving VALOR/DUNE mini-DST to: " << gOptOutFileName;
  TFile fout(gOptOutFileName.c_str(),"recreate");

  TTree * minidst = new TTree("valor_dune_mini_dst","VALOR/DUNE mini-DST);

  // Create tree branches
  //
  minidst->Branch("iev",           &brIev,           "iev/I"         );
  minidst->Branch("neu",           &brNeutrino,      "neu/I"         );
  minidst->Branch("fspl",          &brFSPrimLept,    "fspl/I"        );
  minidst->Branch("coh",           &brIsCoh,         "coh/O"         );

  // open the ROOT file and get the TTree & its header
  //

  TFile fin(gOptInpFilename.c_str(),"READ");

  TTree * input_ghep_tree = 
     dynamic_cast <TTree *> (fin.Get("gtree"));
  if(!input_ghep_tree) {
    LOG("make_minidst", pFATAL) 
        << "No GHEP event tree in input file: " << gOptInpFilename;
    gAbortingInErr=true;
    exit(1);
  }
  Long64_t nev = input_ghep_tree->GetEntries();
  LOG("make_minidst", pFATAL) 
     << "Input GHEP event tree has " << nev 
     << ((nev==1) ? " entry." : " entries.");

  NtpMCTreeHeader * thdr = 
     dynamic_cast <NtpMCTreeHeader *> ( fin.Get("header") );
  LOG("make_minidst", pNOTICE) 
     << "Input tree header: " << *thdr;

  NtpMCEventRecord * mcrec = 0;
  input_ghep_tree->SetBranchAddress("gmcrec", &mcrec);

  //
  // event loop
  //

  for(Long64_t iev = 0; iev <= nev; iev++) {
    input_ghep_tree->GetEntry(iev);

    // retrieve GHEP event record abd print it out.
    NtpMCRecHeader rec_header = mcrec->hdr;
    EventRecord &  event = *(mcrec->event);
    LOG("make_minidst", pNOTICE) 
       << " ** Event: " << rec_header.ievent 
       << event;

    // ...
    // ...
    // ...
    // ...
    // ...
    // ...
    // ...


    minidst->Fill();

    mcrec->Clear();
  }

  // clean-up

  file.Close();

  LOG("make_minidst", pNOTICE)  << "Done!";
  return 0;
}
//___________________________________________________________________
void GetCommandLineArgs(int argc, char ** argv)
{
  LOG("make_minidst", pINFO) << "*** Parsing command line arguments";

  // Common run options.
  RunOpt::Instance()->ReadFromCommandLine(argc,argv);

  // Parse run options for this app

  CmdLnArgParser parser(argc,argv);

  // get GENIE event sample
  if ( parser.OptionExists('f') ) {
    LOG("make_minidst", pINFO) << "Reading event sample filename";
    gOptInpFilename = parser.ArgAsString('f');
  } else {
    LOG("make_minidst", pFATAL) 
       << "Unspecified input filename - Exiting";
    gAbortingInErr = true;
    exit(1);
  }

}
//_________________________________________________________________________________
