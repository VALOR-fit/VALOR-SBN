//________________________________________________________________________________________
/*

Copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include <vector>
#include <iostream>

#include "TObjArray.h"
#include "TString.h"
#include "TMath.h"

#include "Conventions/GBuild.h"
#include "EVGCore/EventRecord.h"
#include "GHEP/GHepParticle.h"
#include "PDG/PDGCodes.h"
#include "PDG/PDGUtils.h"
#include "PDG/PDGLibrary.h"

// valor/dune
#include "valor/Messenger/Messenger.h"

#include "dune/Conventions/BeamConf.h"
#include "dune/Conventions/ReacMode.h"
#include "dune/Conventions/Sample.h"

#include "dune/GENIEUtilities/UtlEventRec.h"

using namespace valor;
using namespace genie;

bool valor::util::GetHadronicSystems(const EventRecord * event, vector<int> & prim_had_syst, vector<int> & final_had_syst) 
{
  // Function adapted from GENIE app gNtpConv (GST).
  prim_had_syst .clear();
  final_had_syst.clear();
  
  // Process id
  const ProcessInfo &  proc_info = event->Summary()->ProcInfo();
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
  TObjArrayIter piter(event);
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
    //if(!is_coh && event->Particle(ip)->FirstMother()==0) continue;
    if(event->Particle(ip)->FirstMother()==0) continue;
    if(pdg::IsPseudoParticle(p->Pdg())) continue;
    int pdgc = p->Pdg();
    int ist  = p->Status();
    if(ist==kIStStableFinalState) {
      if (pdgc == kPdgGamma || pdgc == kPdgElectron || pdgc == kPdgPositron)  {
        int igmom = p->FirstMother();
        if(igmom!=-1) {
          // only count e+'s e-'s or gammas not from decay of pi0
          if(event->Particle(igmom)->Pdg() != kPdgPi0) { final_had_syst.push_back(ip); }
        }
      } else {
        final_had_syst.push_back(ip);
      }
    }
    // now add pi0's that were decayed as short lived particles
    else if(pdgc == kPdgPi0){
      int ifd = p->FirstDaughter();
      int fd_pdgc = event->Particle(ifd)->Pdg();
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
  TObjArrayIter piter_prim(event);
  
  if(study_hadsyst) {
    // if coherent or free nucleon target set primary states equal to final states
    GHepParticle * target = event->Particle(1);
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
        if(event->Particle(i)->Status()==kIStStableFinalState) { prim_had_syst.push_back(i); }
      }      
    }//freenuc?
  }//study_hadsystem?
  
  return study_hadsyst;
}
//_________________________________________________________________________________
conv::ReacMode_t valor::util::DetermineReactionMode(const EventRecord * event, bool use_final_state)
{
  int  nupdg       = event->Probe()->Pdg();
  bool is_nue      = (nupdg == kPdgNuE);
  bool is_numu     = (nupdg == kPdgNuMu);
  bool is_nuebar   = (nupdg == kPdgAntiNuE);
  bool is_numubar  = (nupdg == kPdgAntiNuMu);

  bool is_CC       = event->Summary()->ProcInfo().IsWeakCC();
  bool is_NC       = event->Summary()->ProcInfo().IsWeakNC();
  bool is_strange  = false;
  bool is_charm    = false;
  bool is_QE       = event->Summary()->ProcInfo().IsQuasiElastic() && !is_strange && !is_charm;
  bool is_MEC      = event->Summary()->ProcInfo().IsMEC();
  bool is_Coherent = event->Summary()->ProcInfo().IsCoherent();
  
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
    const GHepParticle * p = event->Particle(hadr_system[ip]);
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
