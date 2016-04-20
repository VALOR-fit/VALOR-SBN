//____________________________________________________________________________
/*!

  \app       valor_dune-make_response_functions

  \brief     

  \syntax    valor_dune-make_response_functions         
               --input  input_analysis_file.root
               --output output_response_function_file.root
               --format format_of_the_input_file <hpgartpc, lartpc, fgt>
               --beam   beam_name
               --sample sample_name
               --systematic systematic_name

  \author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
             University of Liverpool & STFC Rutherford Appleton Laboratory

  \created   April 20, 2016

  \copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#include <string>

//
#include <TFile.h>
#include <TTree.h>
#include <TLeaf.h>
#include <TSpline.h>
#include <TMath.h>

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
#include "ReWeight/GReWeightI.h"
#include "ReWeight/GSystSet.h"
#include "ReWeight/GSyst.h"
#include "ReWeight/GReWeight.h"
#include "ReWeight/GReWeightINuke.h"

// valor
#include "VArray/VALORArray.h"
#include "CmdLine/CmdLnArgList.h"
#include "Conventions/Detector.h"
#include "Conventions/BeamConf.h"
#include "Conventions/Sample.h"
#include "Conventions/ReacMode.h"
#include "Conventions/KineVar.h"
#include "Conventions/SampleKineBinning.h"
#include "Conventions/SampleReacMode.h"
#include "Conventions/FitParam.h"
#include "Conventions/ArrIdx.h"

using std::string;
using genie::EventRecord;
using namespace valor;
using namespace valor::conv;

conv::ReacMode_t DetermineReactionMode(const EventRecord & event);

//___________________________________________________________________
int main(int argc, char ** argv)
{
  // Read command line arguments
  CmdLnArgList arg;
  arg.Read(argc,argv,"$VALOR_DUNE/config/apps/make_response_functions.arg");
  LOG("valor_dune", pNOTICE) << arg;

  // Number of tweaks for the specified systematic parameter
  const int   inom          = 5;
  const int   n_twks        = 11
  const float twk_dial_min  = -5.0;
  const float twk_dial_max  =  5.0;
  const float twk_dial_step = (twk_dial_max - twk_dial_min) / (n_twks-1);
  
  // Arrays to store the number of events in each MC template bin
  // for each systematic parameter tweak
  VALORArray * mc_templ_sb [n_twks] [kNReacModes]; 
  VALORArray * mc_templ_ob [n_twks] [kNReacModes][kNMaxBinZones]; 

  BeamConf_t beam   = util::BeamConfFromString (arg.GetString("beam")  );
  Sample_t   sample = util::SampleFromString   (arg.GetString("sample"));
  
  int isample = fArrIdx->SampleIdx(beam,sample);

  for(int itwk = 0; itwk < n_twks; itwk) {
    for(int imode = 0; imode < kNReacModes; imode++) {
      ReacMode_t m = kReactionModes[isample][imode];
      if(m == kmUndefined) continue;
      const int n_y_reco_bins_sb = util::NumYrecoBinsSb(sample);
      const int n_enu_true_bins  = util::NumEtrueBins(sample);
      mc_templ_sb [itwk][imode] = 
        new VALORArray(kNErecoBinsSb, n_y_reco_bins_sb, n_enu_true_bins);
      mc_templ_sb [itwk][imode] -> SetAll(0.);
      for(int izone = 0; izone < kNMaxBinZones; izone++) {
          const int n_enu_reco_bins = util::NumErecoBins(sample,izone);
          const int n_y_reco_bins   = util::NumYrecoBins(sample,izone);
          if(n_enu_reco_bins <= 0 || n_y_reco_bins <= 0) continue;
          mc_templ_ob [itwk][imode][izone] = 
            new VALORArray(n_enu_reco_bins, n_y_reco_bins, n_enu_true_bins);
          mc_templ_ob [itwk][imode][izone] -> SetAll(0.);
       }
    }
  }
  
  // Open input file and get the HPGArTPC, LArTPC or FGT event tree
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
      LOG("make_response_func", pFATAL) 
        << "Unknown input file format. Please specify one of hpgartpc, lartpc or fgt";
      exit(1);
  }
  TTree * analysis_tree = dynamic_cast <TTree *> (fin.Get(tree_name.c_str()));
  if(!analysis_tree) {
    LOG("make_response_func", pFATAL) 
      << "No event tree " << tree_name 
      << " in " << gOptInpFileFormat << "-format input file: "
      << gOptInpFileName;
    exit(1);
  }
  NtpMCEventRecord * curr_mcrec = 0;
  int    curr_sample   = -1;
  double curr_enu_reco =  0.;
  double curr_y_reco   =  0.;
  if(gOptInpFileFormat == "hpgartpc") {
    analysis_tree->SetBranchAddress("gmcrec",          &curr_mcrec);
    analysis_tree->SetBranchAddress("sample",          &curr_sample);
    analysis_tree->SetBranchAddress("Ev_reco",         &curr_enu_reco);
    analysis_tree->SetBranchAddress("y_reco",          &curr_y_reco);
  }
  else
  if(gOptInpFileFormat == "lartpc" || gOptInpFileFormat == "fgt") {
    analysis_tree->SetBranchAddress("genie_mc_truth",  &curr_mcrec);
    analysis_tree->SetBranchAddress("sample",          &curr_sample);
    analysis_tree->SetBranchAddress("Ev_reco",         &curr_enu_reco);
    analysis_tree->SetBranchAddress("y_reco",          &curr_y_reco);
  }

  // GENIE event reweighting interface
  ReWeight rw;
  rw.AdoptWghtCalc( "hadro_intranuke", new GReWeightINuke );
  GSystSet & syst_list = rw.Systematics();
  GSyst_t syst = GSyst::FromString(arg.GetString("systematic"));

  syst_list.Init(syst);

  // Systematic tweaks
  for(int itwk = 0; itwk < n_twks; itwk) {

     double twk_dial = twk_dial_min + ith_dial * twk_dial_step;  
     syst_list.Set(syst, twk_dial);
     rw.Reconfigure();
    
      // Event loop
      Long64_t nev = analysis_tree->GetEntries();
      for(Long64_t iev = 0; iev < nev; iev++) {
        LOG("make_response_func", pNOTICE) << "** Reading event: " << iev;
        analysis_tree->GetEntry(iev);

        // Consider only input sample
        if(curr_sample != (int)sample) {
          mcrec->Clear();
          continue;
        }
    
        // Retrieve GHEP event record and print it out.
        NtpMCRecHeader rec_header = curr_mcrec->hdr;
        EventRecord &  event = *(mcrec->event);
        LOG("make_response_func", pNOTICE) 
           << "GENIE MC truth info: " << event;

        // hpgartpc output in MeV, convert to GeV as in lartpc and fgt outputs
        if(gOptInpFileFormat == "hpgartpc") {
           curr_enu_reco = curr_enu_reco/1000.;
        }
        if(curr_enu_reco <= 0) {
           LOG("make_minidst", pNOTICE) << "- Rejecting event [Ev (reco) <= 0]";
           mcrec->Clear();
           continue;
        }
        if(curr_y_reco < 0) {
           LOG("make_minidst", pNOTICE) << "- Rejecting event [y (reco) < 0]";
           mcrec->Clear();
           continue;
        }

	// Get reaction mode
        ReacMode_t curr_mode = DetermineReactionMode(event, true);
        if(curr_mode == kmUndefined) {
           LOG("make_minidst", pNOTICE) << "- Rejecting event [Undefined mode]";
           mcrec->Clear();
           continue;
        }
        int imode = fArrIdx->ReacModeIdx(curr_sample, curr_mode);       

	// Get required true kinematical variables
        double curr_enu_true = event.Particle(0)->E();
        double curr_q2_true  = event.Summary()->KinePtr()->Q2();
	
        // Calculate event weight
        double wght = rw.CalcWeight(event);
      //if(wght <    0) wght = 1; // needed?
      //if(wght > 9999) wght = 1; // needed?

        // Get enu_true, enu_reco, y_reco array indices
        const int izone = util::BinZone(curr_sample, curr_enu_reco, curr_y_reco);
        if(izone < 0) {
	  LOG("make_minidst", pNOTICE) << "- Rejecting event [Negative zone!]";
          mcrec->Clear();
          continue;
        }
        const int n_enu_true_bins = util::NumEtrueBins(curr_sample);
        const int n_enu_reco_bins = util::NumErecoBins(curr_sample,izone);
        const int n_y_reco_bins   = util::NumYrecoBins(curr_sample,izone);
        const int n_y_reco_bins_sb = util::NumYrecoBinsSb(curr_sample);
        const double * enu_true_bin_edges  = util::EtrueBinEdges(curr_sample);
        const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(curr_sample);
        const double * enu_reco_bin_edges  = util::ErecoBinEdges(curr_sample,izone);
        const double * y_reco_bin_edges    = util::YrecoBinEdges(curr_sample,izone);

        // Protect against vars at upper limit (eg y_reco = 1, set by hand for NC events) as
        // the binary search below will give an index out of limits
        if(curr_enu_reco >= kErecoMax) { curr_enu_reco = curr_enu_reco - kASmallNum; }
        if(curr_y_reco   >= kYrecoMax) { curr_y_reco   = curr_y_reco - kASmallNum;   } 

        // Work-out the index using the bin-edge array defining the variable-size binning scheme
        int ienu_true    = TMath::BinarySearch(1+(Long_t)n_enu_true_bins, enu_true_bin_edges, curr_enu_true);
        int ienu_reco    = TMath::BinarySearch(1+(Long_t)n_enu_reco_bins, enu_reco_bin_edges, curr_enu_reco);
        int iy_reco      = TMath::BinarySearch(1+(Long_t)n_y_reco_bins,   y_reco_bin_edges,   curr_y_reco  );
        // Repeat, finding the indices for the template versions using a simple binning scheme
        int ienu_reco_sb = TMath::BinarySearch(1+(Long_t)kNErecoBinsSb,    kErecoBinEdgesSb,    curr_enu_reco);
        int iy_reco_sb   = TMath::BinarySearch(1+(Long_t)n_y_reco_bins_sb, y_reco_bin_edges_sb, curr_y_reco  );

        mc_templ_sb [itwk] [imode]        -> AddToEntry(wght, ienu_reco, iy_reco, ienu_true); 
        mc_templ_ob [itwk] [imode][izone] -> AddToEntry(wght, ienu_reco, iy_reco, ienu_true); 
	
        mcrec->Clear();
      }// event loop
  }//tweaks

  LOG("make_response_func", pNOTICE) << "Closing input file";

  fin.Close();

  // Saving splines in specified output file 
  LOG("make_response_func", pNOTICE) 
    << "Saving VALOR response functions to: "
    << arg.GetString("output");
  TFile fout(arg.GetString("output").c_str(),"recreate");

  for(int imode = 0; imode < kNReacModes; imode++) {
    ReacMode_t m = kReactionModes[isample][imode];
    if(m == kmUndefined) continue;
    const int n_y_reco_bins_sb = util::NumYrecoBinsSb(sample);
    const int n_enu_true_bins  = util::NumEtrueBins(sample);
    for(int ienu_reco = 0; ienu_reco < kNErecoBinsSb; ienu_reco) {
      for(int iy_reco = 0;  iy_reco <  n_y_reco_bins_sb; iy_reco) {
         for(int ienu_true = 0; ienu_true < n_enu_true_bins; ienu_true) {
              double y[n_twks] = { 0 };
              double x[n_twks] = { 0 };    
              for(int itwk = 0; itwk < n_twks; itwk) {
		 double twk_dial = twk_dial_min + ith_dial * twk_dial_step;  
		 double nevents  = mc_templ_sb [itwk][imode] -> Get(ienu_reco, iy_reco, ienu_true);
		 double nevents0 = mc_templ_sb [inom][imode] -> Get(ienu_reco, iy_reco, ienu_true);
                 y[itwk] = (nevents0 > 0) ? nevents/nevents0 : 1;
                 x[itwk] = twk_dial;                   
              }//itwk
	      cons char * name  = "blah";
	      cons char * title = "blah";
              TSpline3 * spl = new TSpline3(name, x, y, n_twks, "0");
	      spl->SetTitle(title);
	      spl->Write();
         }//ienu_true
      }//iy_reco
    }//ienu_reco    
    for(int izone = 0; izone < kNMaxBinZones; izone++) {
        const int n_enu_reco_bins = util::NumErecoBins(sample,izone);
        const int n_y_reco_bins   = util::NumYrecoBins(sample,izone);
        for(int ienu_reco = 0; ienu_reco < kNErecoBinsSb; ienu_reco) {
           for(int iy_reco = 0;  iy_reco <  n_y_reco_bins_sb; iy_reco) {
              for(int ienu_true = 0; ienu_true < n_enu_true_bins; ienu_true) {
                  double y[n_twks] = { 0 };
                  double x[n_twks] = { 0 };    
                  for(int itwk = 0; itwk < n_twks; itwk) {
		      double twk_dial = twk_dial_min + ith_dial * twk_dial_step;  
		      double nevents  = mc_templ_ob [itwk][imode][izone] -> Get(ienu_reco, iy_reco, ienu_true);
		      double nevents0 = mc_templ_ob [inom][imode][izone] -> Get(ienu_reco, iy_reco, ienu_true);
                      y[itwk] = (nevents0 > 0) ? nevents/nevents0 : 1;
                      x[itwk] = twk_dial;                   
                  }//itwk
	          cons char * name  = "blah";
	          cons char * title = "blah";
                  TSpline3 * spl = new TSpline3(name, x, y, n_twks, "0");
		  spl->SetTitle(title);
    	          spl->Write();
              }//ienu_true
           }//iy_reco
        }//ienu_reco    
    }//izone
  }//imode

  fout.Close();

  LOG("make_response_func", pNOTICE)  << "Done!";

  return 0;
}
//___________________________________________________________________








//
//
// This is common with make_minidst and should be factored out
//
//

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

