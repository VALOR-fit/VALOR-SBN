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
#include "valor/Conventions/GBuild.h"
#include "EVGCore/EventRecord.h"
#include "GHEP/GHepParticle.h"
#include "valor/Ntuple/NtpMCFormat.h"
#include "valor/Ntuple/NtpMCTreeHeader.h"
#include "valor/Ntuple/NtpMCEventRecord.h"
#include "valor/Messenger/Messenger.h"
#include "PDG/PDGCodes.h"
#include "PDG/PDGUtils.h"
#include "PDG/PDGLibrary.h"
#include "Utils/CmdLnArgParser.h"
#include "Utils/RunOpt.h"
// valor/dune
#include "dune/Conventions/BeamConf.h"
#include "dune/Conventions/ReacMode.h"
#include "dune/Conventions/Sample.h"

using std::string;
using namespace genie;
using namespace valor;

string gOptInpFileFormat;
string gOptInpFileName;
string gOptOutFileName;
bool   gOptDisableChecks;

void GetCommandLineArgs (int /*argc*/, char ** /*argv*/);

conv::ReacMode_t DetermineReactionMode(const EventRecord &  event);

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

  TFile fin(gOptInpFileName.c_str(),"READ");

  string tree_name = "";

  if(gOptInpFileFormat == "hpgartpc") {
    tree_name = "GasTPCTree";
  } 
  else {
    if(gOptInpFileFormat == "lartpc" || gOptInpFileFormat == "fgt") {
      tree_name = "dune_dst";
    }
    else {
      LOG("make_minidst", pFATAL) 
        << "Unknown input file format. Please specify one of hpgartpc, lartpc or fgt";
      exit(1);
    }
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
    valor_minidst_Q2_true   = mcrec->event->Summary()->KinePtr()->Q2();

    LOG("make_minidst", pNOTICE) 
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
bool GetHadronicSystems(const EventRecord & event, vector<int> & prim_had_syst, vector<int> & final_had_syst) 
{
  // Function copied from GENIE app gNtpConv (GST).
  prim_had_syst .clear();
  final_had_syst.clear();
  
  // Process id
  const ProcessInfo &  proc_info = event.Summary()->ProcInfo();
  bool is_qel     = proc_info.IsQuasiElastic();
  bool is_res     = proc_info.IsResonant();
  bool is_dis     = proc_info.IsDeepInelastic();
  bool is_coh     = proc_info.IsCoherent();
  bool is_dfr     = proc_info.IsDiffractive();
  bool is_singlek = proc_info.IsSingleKaon();    
  bool is_mec     = proc_info.IsMEC();

  // Extract more info on the hadronic system
  // Only for QEL/RES/DIS/COH/MEC events
  //
  bool study_hadsyst = (is_qel || is_res || is_dis || is_coh || is_dfr || is_mec || is_singlek);
  if (!study_hadsyst) {return false;}

  //
  TObjArrayIter piter(&event);
  GHepParticle * p = 0;
  int ip=-1;

  //
  // Extract the final state system originating from the hadronic vertex 
  // (after the intranuclear rescattering step)
  //

  LOG("gntpc", pDEBUG) << "Extracting final state hadronic system";

  while( (p = (GHepParticle *) piter.Next()) && study_hadsyst)
  {
    ip++;
    // don't count final state lepton as part hadronic system 
    //if(!is_coh && event.Particle(ip)->FirstMother()==0) continue;
    if(event.Particle(ip)->FirstMother()==0) continue;
    if(pdg::IsPseudoParticle(p->Pdg())) continue;
    int pdgc = p->Pdg();
    int ist  = p->Status();
    if(ist==kIStStableFinalState) {
      if (pdgc == kPdgGamma || pdgc == kPdgElectron || pdgc == kPdgPositron)  {
        int igmom = p->FirstMother();
        if(igmom!=-1) {
          // only count e+'s e-'s or gammas not from decay of pi0
          if(event.Particle(igmom)->Pdg() != kPdgPi0) { final_had_syst.push_back(ip); }
        }
      } else {
        final_had_syst.push_back(ip);
      }
    }
    // now add pi0's that were decayed as short lived particles
    else if(pdgc == kPdgPi0){
      int ifd = p->FirstDaughter();
      int fd_pdgc = event.Particle(ifd)->Pdg();
      // just require that first daughter is one of gamma, e+ or e-  
      if(fd_pdgc == kPdgGamma || fd_pdgc == kPdgElectron || fd_pdgc == kPdgPositron){
        final_had_syst.push_back(ip);
      }
    }
  }//particle-loop

  //~ if( count(final_had_syst.begin(), final_had_syst.end(), -1) > 0) {
    //~ mcrec->Clear();
    //~ continue;
  //~ }

  //
  // Extract info on the primary hadronic system (before any intranuclear rescattering)
  // looking for particles with status_code == kIStHadronInTheNucleus 
  // An exception is the coherent production and scattering off free nucleon targets 
  // (no intranuclear rescattering) in which case primary hadronic system is set to be 
  // 'identical' with the final  state hadronic system
  //

  LOG("gntpc", pDEBUG) << "Extracting primary hadronic system";

  ip = -1;
  TObjArrayIter piter_prim(&event);
  
  if(study_hadsyst) {
    // if coherent or free nucleon target set primary states equal to final states
    GHepParticle * target = event.Particle(1);
    if(!pdg::IsIon(target->Pdg()) || (is_coh)) {
      vector<int>::const_iterator hiter = final_had_syst.begin();
      for( ; hiter != final_had_syst.end(); ++hiter) {
        prim_had_syst.push_back(*hiter);
      }
    } 
    // otherwise loop over all particles and store indices of those which are hadrons
    // created within the nucleus
    else {
      while( (p = (GHepParticle *) piter_prim.Next()) ){
        ip++;      
        int ist_comp  = p->Status();
        if(ist_comp==kIStHadronInTheNucleus) {
          prim_had_syst.push_back(ip); 
        }
      }//particle-loop   
      //
      // also include gammas from nuclear de-excitations (appearing in the daughter list of the 
      // hit nucleus, earlier than the primary hadronic system extracted above)
      for(int i = target->FirstDaughter(); i <= target->LastDaughter(); i++) {
        if(i<0) continue;
        if(event.Particle(i)->Status()==kIStStableFinalState) { prim_had_syst.push_back(i); }
      }      
    }//freenuc?
  }//study_hadsystem?
  
  return study_hadsyst;
}
//_________________________________________________________________________________
conv::ReacMode_t DetermineReactionMode(const EventRecord & event, bool use_final_state = false)
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
  
  vector<int> primary_hadr_system;
  vector<int> final_hadr_system;
  
  GetHadronicSystems(event,primary_hadr_system,final_hadr_system);
  
  // Set up variables for counting particles
  int nP   = 0;
  int nN   = 0;
  int nPip = 0;
  int nPim = 0;
  int nPi0 = 0;
  int nKp  = 0;
  int nKm  = 0;
  int nK0  = 0;
  int nEM  = 0;
  
  const vector<int> & hadr_system = (use_final_state ? final_hadr_system : primary_hadr_system);
  // We exclude states with the right number of pions but other mesons.
  
  for (unsigned int ip = 0 ; ip < hadr_system.size(); ip++) {
    const GHepParticle * p = event.Particle(hadr_system[ip]);
    if      (p->Pdg() == kPdgProton  || p->Pdg() == kPdgAntiProton)                         { nP++;   }
    else if (p->Pdg() == kPdgNeutron || p->Pdg() == kPdgAntiNeutron)                        { nN++;   }
    else if (p->Pdg() == kPdgPiP)                                                           { nPip++; }
    else if (p->Pdg() == kPdgPiM)                                                           { nPim++; }
    else if (p->Pdg() == kPdgPi0)                                                           { nPi0++; }
    else if (p->Pdg() == kPdgKP)                                                            { nKp++;  }
    else if (p->Pdg() == kPdgKM)                                                            { nKm++;  }
    else if (p->Pdg() == kPdgK0    || p->Pdg() == kPdgAntiK0)                               { nK0++;  }
    else if (p->Pdg() == kPdgGamma || p->Pdg() == kPdgElectron || p->Pdg() == kPdgPositron) { nEM++;  }
      
  }
  
  int nPiC = nPip+nPim;
  int nK   = nKp+nKm+nK0;
  
  bool is_1piC     = (!is_Coherent) && (nPiC==1) && (nPi0==0) && (nK==0);
  bool is_1pi0     = (!is_Coherent) && (nPiC==0) && (nPi0==1) && (nK==0); 
  bool is_2piC     = (!is_Coherent) && (nPiC==2) && (nPi0==0) && (nK==0); 
  bool is_2pi0     = (!is_Coherent) && (nPiC==0) && (nPi0==2) && (nK==0); 
  bool is_1piC1pi0 = (!is_Coherent) && (nPiC==1) && (nPi0==1) && (nK==0); 
  
  vector<conv::ReacMode_t> modes;
  
  // First do exclusive modes
  if(is_numu) {
    if(is_CC) {
      if (is_QE)       { modes.push_back(conv::kmNuMuCCQE    ); } // numu    CC QE
      if (is_MEC)      { modes.push_back(conv::kmNuMuCCMEC   ); } // numu    CC MEC
      if (is_1piC)     { modes.push_back(conv::kmNuMuCC1piC  ); } // numu    CC 1 pi+/-
      if (is_1pi0)     { modes.push_back(conv::kmNuMuCC1pi0  ); } // numu    CC 1 pi0
      if (is_2piC)     { modes.push_back(conv::kmNuMuCC2piC  ); } // numu    CC 2 pi+/-
      if (is_2pi0)     { modes.push_back(conv::kmNuMuCC2pi0  ); } // numu    CC 2 pi0
      if (is_1piC1pi0) { modes.push_back(conv::kmNuMuCCpiCpi0); } // numu    CC 1 pi0 + 1 pi+/-
      if (is_Coherent) { modes.push_back(conv::kmNuMuCCcoh   ); } // numu    CC coherent
    }
    if(is_NC) {
      if (is_1piC)     { modes.push_back(conv::kmNuMuNC1piC  ); } // numu    NC 1 pi+/-
      if (is_1pi0)     { modes.push_back(conv::kmNuMuNC1pi0  ); } // numu    NC 1 pi0
      if (is_Coherent) { modes.push_back(conv::kmNuMuNCcoh   ); } // numu    NC coherent
    }
  }

  if(is_numubar) {
    if(is_CC) {
      if (is_QE)       { modes.push_back(conv::kmNuMuBarCCQE    ); } // numubar CC QE
      if (is_MEC)      { modes.push_back(conv::kmNuMuBarCCMEC   ); } // numubar CC MEC
      if (is_1piC)     { modes.push_back(conv::kmNuMuBarCC1piC  ); } // numubar CC 1 pi+/-
      if (is_1pi0)     { modes.push_back(conv::kmNuMuBarCC1pi0  ); } // numubar CC 1 pi0
      if (is_2piC)     { modes.push_back(conv::kmNuMuBarCC2piC  ); } // numubar CC 2 pi+/-
      if (is_2pi0)     { modes.push_back(conv::kmNuMuBarCC2pi0  ); } // numubar CC 2 pi0
      if (is_1piC1pi0) { modes.push_back(conv::kmNuMuBarCCpiCpi0); } // numubar CC 1 pi0 + 1 pi+/-
      if (is_Coherent) { modes.push_back(conv::kmNuMuBarCCcoh   ); } // numubar CC coherent
    }
    if(is_NC) {
      if (is_1piC)     { modes.push_back(conv::kmNuMuBarNC1piC ); } // numubar NC 1 pi+/-
      if (is_1pi0)     { modes.push_back(conv::kmNuMuBarNC1pi0 ); } // numubar NC 1 pi0
      if (is_Coherent) { modes.push_back(conv::kmNuMuBarNCcoh  ); } // numubar NC coherent
    }
  }

  //
  if(is_nue) {
    if(is_CC) {
      if (is_QE)       { modes.push_back(conv::kmNuECCQE       );}     // nue     CC QE
      if (is_MEC)      { modes.push_back(conv::kmNuECCMEC      );}     // nue     CC MEC
      if (is_1piC)     { modes.push_back(conv::kmNuECC1piC     );}     // nue     CC 1 pi+/-
      if (is_1pi0)     { modes.push_back(conv::kmNuECC1pi0     );}     // nue     CC 1 pi0
      if (is_2piC)     { modes.push_back(conv::kmNuECC2piC     );}     // nue     CC 2 pi+/-
      if (is_2pi0)     { modes.push_back(conv::kmNuECC2pi0     );}     // nue     CC 2 pi0
      if (is_1piC1pi0) { modes.push_back(conv::kmNuECCpiCpi0   );}     // nue     CC 1 pi0 + 1 pi+/-
      if (is_Coherent) { modes.push_back(conv::kmNuECCcoh      );}     // nue     CC coherent
    }
    if(is_NC) {
      if (is_1piC)     { modes.push_back(conv::kmNuENC1piC     );}     // nue     NC 1 pi+/-
      if (is_1pi0)     { modes.push_back(conv::kmNuENC1pi0     );}     // nue     NC 1 pi0
      if (is_Coherent) { modes.push_back(conv::kmNuENCcoh      );}     // nue     NC coherent
    }
  }
  
  //
  if(is_nuebar) {
    if(is_CC) {
      if (is_QE)       { modes.push_back(conv::kmNuEBarCCQE    );}     // nuebar  CC QE
      if (is_MEC)      { modes.push_back(conv::kmNuEBarCCMEC   );}     // nuebar  CC MEC
      if (is_1piC)     { modes.push_back(conv::kmNuEBarCC1piC  );}     // nuebar  CC 1 pi+/-
      if (is_1pi0)     { modes.push_back(conv::kmNuEBarCC1pi0  );}     // nuebar  CC 1 pi0
      if (is_2piC)     { modes.push_back(conv::kmNuEBarCC2piC  );}     // nuebar  CC 2 pi+/-
      if (is_2pi0)     { modes.push_back(conv::kmNuEBarCC2pi0  );}     // nuebar  CC 2 pi0
      if (is_1piC1pi0) { modes.push_back(conv::kmNuEBarCCpiCpi0);}     // nuebar  CC 1 pi0 + 1 pi+/-
      if (is_Coherent) { modes.push_back(conv::kmNuEBarCCcoh   );}     // nuebar  CC coherent
    }
    if(is_NC) {
      if (is_1piC)     { modes.push_back(conv::kmNuEBarNC1piC );}     // nuebar  NC 1 pi+/-
      if (is_1pi0)     { modes.push_back(conv::kmNuEBarNC1pi0 );}     // nuebar  NC 1 pi0
      if (is_Coherent) { modes.push_back(conv::kmNuEBarNCcoh  );}     // nuebar  NC coherent
    }
  }
  
  // If we've got one exclusive mode, we did well.
  if (modes.size() == 1) {
    return modes[0];
  }
  // Otherwise look for inclusive
  else if (modes.size() == 0) {
    if (is_numu) {
      if (is_CC) {return conv::kmNuMuCCoth;}
      if (is_NC) {return conv::kmNuMuNCoth;}
    }
    if (is_numubar) {
      if (is_CC) {return conv::kmNuMuBarCCoth;}
      if (is_NC) {return conv::kmNuMuBarNCoth;}
    }
    if (is_nue) {
      if (is_CC) {return conv::kmNuECCoth;}
      if (is_NC) {return conv::kmNuENCoth;}
    }
    if (is_nuebar) {
      if (is_CC) {return conv::kmNuEBarCCoth;}
      if (is_NC) {return conv::kmNuEBarNCoth;}
    }
  }
  else {
    std::ostringstream mode_names;
    for (unsigned int ii = 0 ; ii < modes.size(); ii++) {
      mode_names << "\n "<<util::AsString(modes[ii]);
    }
    LOG("make_minidst",pERROR)<<"Event filed into multiple exclusive modes: "
      <<mode_names
      <<"\nFull record: "<<event;
  }

  return conv::kmUndefined;
}
//_________________________________________________________________________________

