//____________________________________________________________________________
/*!

\app       valor_dune-make_nd_minidst

\brief     Converts input ND analysis DSTs to the VALOR NDFit mini-DST format.

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
string gOptOutFilename;

//___________________________________________________________________
int main(int argc, char ** argv)
{
  GetCommandLineArgs (argc, argv);

  // set print level
  GHepRecord::SetPrintLevel(RunOpt::Instance()->EventRecordPrintLevel());

  // Open output file & create output mini-DST 
  //
  LOG("make_minidst", pNOTICE) 
      << "*** Saving VALOR/DUNE mini-DST to: " << gOptOutFilename;
  TFile fout(gOptOutFilename.c_str(),"recreate");

  TTree * minidst = new TTree("valor_dune_ndfit_mini_dst","VALOR/DUNE NDFit mini-DST");

/*
  // Create tree branches
  //
  minidst->Branch("iev",           &brIev,           "iev/I"         );
  minidst->Branch("neu",           &brNeutrino,      "neu/I"         );
  minidst->Branch("fspl",          &brFSPrimLept,    "fspl/I"        );
  minidst->Branch("coh",           &brIsCoh,         "coh/O"         );
*/

  // open the ROOT file and get the TTree & its header
  //

  TFile fin(gOptInpFilename.c_str(),"READ");

  TTree * analysis_tree = 
     dynamic_cast <TTree *> (fin.Get("GasTPCTree"));
  if(!analysis_tree) {
    LOG("make_minidst", pFATAL) 
        << "No GHEP event tree in input file: " << gOptInpFilename;
//    gAbortingInErr=true;
    exit(1);
  }
  Long64_t nev = analysis_tree->GetEntries();
  LOG("make_minidst", pNOTICE) 
     << "Input analysis tree has " << nev << ((nev==1) ? " entry." : " entries.");

//  NtpMCTreeHeader * thdr = 
//     dynamic_cast <NtpMCTreeHeader *> ( fin.Get("header") );
//  LOG("make_minidst", pNOTICE) 
//     << "Input tree header: " << *thdr;

  NtpMCEventRecord * mcrec = 0;
  analysis_tree->SetBranchAddress("gmcrec", &mcrec);

  //
  // event loop
  //

  for(Long64_t iev = 0; iev <= nev; iev++) {
    analysis_tree->GetEntry(iev);

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

  fin.Close();

//  LOG("make_minidst", pNOTICE)  << "Done!";
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

  if ( parser.OptionExists("--input") ) {
    LOG("make_minidst", pINFO) << "Reading analysis file";
    gOptInpFilename = parser.ArgAsString("--input");
  } else {
    LOG("make_minidst", pFATAL) 
       << "Unspecified input file - Exiting";
    gAbortingInErr = true;
    exit(1);
  }

  if ( parser.OptionExists("--output") ) {
    LOG("make_minidst", pINFO) << "Reading output filename";
    gOptOutFilename = parser.ArgAsString("--output");
  } else {
    gOptOutFilename = "out.root";
  }

}
//_________________________________________________________________________________
