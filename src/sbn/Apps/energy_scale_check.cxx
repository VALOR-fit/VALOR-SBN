//____________________________________________________________________________
/*!

  \app       valor_sbn-energy_scale_check

  \brief

  \syntax    valor_sbn-energy_scale_check

  \options     --output              : Where to save histograms to
               --input               : input pre-DST file (SBNCode)
               --config              : Analysis configuration file [required]
               --sample              : Topology [def: numuCCincl]
               --detector            : Detector [def: sbn_nd]
               --scale               : Amount by which to scale the bin edges
               --mesg-thresholds     : Message thresholds [def: "verbosity.xml"]

  \author    Rhiannon Jones <rjones@hep.ph.liv.ac.uk>
  University of Liverpool

  \created   Feb 22nd, 2021

  \copyright Copyright (c) 2010-2021, The VALOR group. All rights reserved.

*/
//____________________________________________________________________________

// System
#include <string>
#include <iostream>

// ROOT
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TBranch.h>
#include <TLeaf.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1.h>
#include <TString.h>
#include <TMath.h>

// VALOR/SDK
#include "valor/Messenger/Messenger.h"
#include "valor/Utilities/Env.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Utilities/NameRegistry.h"
#include "valor/VArray/VALORArray.h"
#include "valor/CmdLine/CmdLnArgList.h"
#include "valor/Conventions/BeamConf.h"
#include "valor/Conventions/Sample.h"
#include "valor/Conventions/Detector.h"
#include "valor/Conventions/ParameterPool.h"
#include "valor/Conventions/Parameter.h"
#include "valor/Conventions/ModeList.h"
#include "valor/KineBinning/KBCubHcmbEdge2Edge.h"
#include "valor/KineBinning/VALORBinning.h"
#include "valor/Conventions/Parameter.h"
#include "valor/Conventions/ReacMode.h"
#include "valor/Conventions/ParameterPool.h"
#include "valor/GENIEUtilities/GENIEIncludes.h"
#include "valor/GENIEUtilities/UtlEventRec.h"
#include "valor/Utilities/SingleSampleKineBinning.h"
#include "valor/Utilities/RFL.h"
#include "valor/Utilities/KinematicBin.h"
#include "valor/FitCore/CompoundFitElements.h"
#include "valor/FitElements/GenericSingleSampleFitModel.h"
#include "valor/FitCore/UtlFitParamList.h"
#include "core/Event.hh"

static const std::string gTreeName       = "sbnreco";
static const std::string gSubRunTreeName = "sbnsubrun";

using namespace valor;
using namespace valor::conv;

std::vector<double> GetBinEdges(const valor::VALORBinning *vb);
std::vector<double> GetPlus1SigmaEdges (const std::vector<double> &b, const double scale);
std::vector<double> GetMinus1SigmaEdges(const std::vector<double> &b, const double scale);
std::vector<double> GetScaledBinEdges  (const std::vector<double> &b, const double scale);

bool CheckSample(const Sample_t &s, const bool &cc0pi, const bool &ccoth);

int main(int argc, char ** argv)
{

  time_t scriptstartrawtime;
  struct tm * scriptstarttimeinfo;
  time (&scriptstartrawtime);
  scriptstarttimeinfo = localtime (&scriptstartrawtime);
  std::cout << "-----------------------------------------------------------" << std::endl;
  std::cout << " Script start local time and date:  " << asctime(scriptstarttimeinfo);
  std::cout << "-----------------------------------------------------------" << std::endl;

  // Read command line arguments
  CmdLnArgList arg;
  arg.Read(argc,argv,"$VALOR_EXPT/config/apps/energy_scale_check.arg");
  VLOG("valor_sbn", pNOTICE) << arg;

  // Get arguments
  std::string arg_config       = arg.GetString("config");
  std::string arg_input_name   = arg.GetString("input");
  std::string arg_output_file  = arg.GetString("output");
  std::string arg_detector     = arg.GetString("detector");
  std::string arg_sample       = arg.GetString("sample");

  // From arguments
  std::string mesg_thresholds = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  std::string config_file     = util::CompleteConfigPath(arg_config);
  Detector_t detector         = util::DetectorFromString(arg_detector);
  Sample_t sample             = util::SampleFromString(arg_sample);
  double scale                = arg.GetDouble("scale");
  bool other_sample           = arg.GetBool("other-sample");

  // Get model & configure
  // Make an elements without reading the MC
  std::string elem_readopt("nomc nosplines");
  CompoundFitElements * elements = new CompoundFitElements();
  elements->Read(util::CompleteConfigPath(config_file),elem_readopt.c_str());

  // Read the models for all in the file, we'll use the information from this to name the output
  FitModelABC * model = elements->FitModel();
  CompoundFitModel * cmodel = dynamic_cast<CompoundFitModel*>(model);
  assert(cmodel);
  GenericSingleSampleFitModel * gmodel = 0;
  bool found_appropriate_model = true;
  for (unsigned int ism = 0 ; ism < cmodel->GetNSubModels() ; ism++) {
    gmodel = dynamic_cast<GenericSingleSampleFitModel*>(cmodel->GetSubModel(ism));
    if(gmodel->GetDetector() != detector || gmodel->GetSample() != sample){
      VLOG("valor_sbn",pNOTICE) << " Looking for detector: " << arg_detector << ", sample: " << arg_sample;
      VLOG("valor_sbn",pNOTICE) << " From model: " << util::AsString(gmodel->GetDetector()) << ", " << util::AsString(gmodel->GetSample());
      found_appropriate_model = false;
    }
  }
  assert(gmodel);
  assert(found_appropriate_model);
  
  // And finally read the MC properly
  std::string model_readopt("forcedst nosplines");
  gmodel->Read(gmodel->GetLastConfigFileRead().c_str(),model_readopt.c_str());

  // Get the POT of the sample from the subrun tree
  double mcsample_pot = -1.;
  TChain * subrun_tree = new TChain(gSubRunTreeName.c_str());
  subrun_tree->Add(arg_input_name.c_str());
  if(!subrun_tree || !subrun_tree->GetEntries()) {
    VLOG("valor_sbn",pERROR) << "Error: Unable to read " << gSubRunTreeName  <<" from "<< arg_input_name;
    std::exit(1);
  }

  Long64_t nev_subrun = subrun_tree->GetEntries();
  VLOG("valor_sbn",pNOTICE) << "Input subrun tree has " << nev_subrun << ((nev_subrun==1) ? " entry." : " entries.");

  //  TBranch *b = subrun_tree->GetBranch("totgoodpot");
  TBranch *b = subrun_tree->GetBranch("totpot"); // TEMP FOR BROKEN FILE
  unsigned int npot = subrun_tree->GetEntries();
  for(unsigned int i = 0; i < npot; ++i){
    b->GetEntry(i);
    mcsample_pot += b->GetLeaf("totpot")->GetValue(); // TEMP FOR BROKEN FILE
  }

  if(mcsample_pot == -1.){
    VLOG("valor_sbn",pERROR) << "Error: Not able to access MCSample POT from " << gSubRunTreeName;
    std::exit(1);
  }
  VLOG("valor_sbn",pNOTICE) << "POT in the input file is " << mcsample_pot;

  // Get the nominal POT
  double nomPOT = gmodel->GetPOT();
  VLOG("valor_sbn",pNOTICE) << "Nominal POT in the sample is " << nomPOT;

  // 1) Get binning from configuration
  // 2) Get the reco bins 
  // 3) Get the bin edges
  // 3) Get the scaled bin edges
  const SingleSampleKineBinning & binning = *(gmodel->GetBinning());
  const VALORBinning * reco_bins          = binning.RecoOptBinning();
  const std::vector<double> bin_edges     = GetBinEdges(reco_bins);
  const std::vector<double> p1_bin_edges  = GetPlus1SigmaEdges(bin_edges,scale);
  const std::vector<double> m1_bin_edges  = GetMinus1SigmaEdges(bin_edges,scale);
  const int n_bins                        = bin_edges.size()-1;
  VLOG("valor_sbn",pINFO) << " ------------------------------- ";
  VLOG("valor_sbn",pINFO) << " Bin edges, scaled and unscaled.";
  VLOG("valor_sbn",pINFO) << std::setw(8) << " Nominal " <<  std::setw(8) << " +1Sigma " <<  std::setw(8) << " -1Sigma ";
  for(int n = 0; n <= n_bins; ++n){
    VLOG("valor_sbn",pINFO) << std::setw(8) << bin_edges.at(n) <<  std::setw(8) << p1_bin_edges.at(n) <<  std::setw(8) << m1_bin_edges.at(n);
  }
  VLOG("valor_sbn",pINFO) << " ------------------------------- ";

  // Define the histograms
  // Want to use the nominal bin edge defintions across the board
  TH1D *h_nom = new TH1D("h_nom", "", n_bins, bin_edges.data());
  TH1D *h_p1  = new TH1D("h_p1",  "", n_bins, bin_edges.data());
  TH1D *h_m1  = new TH1D("h_m1",  "", n_bins, bin_edges.data());

  // Setup vectors for the plus and minus 1 sigma bin content
  std::vector<double> p1_content(n_bins, 0.);
  std::vector<double> m1_content(n_bins, 0.);

  // Now we want to fill the relevant histograms
  // Read the SBNCode input file
  TChain * analysis_tree = new TChain(gTreeName.c_str());
  analysis_tree->Add(arg_input_name.c_str());
  if(!analysis_tree || !analysis_tree->GetEntries()) {
    VLOG("valor_sbn",pERROR) << "Error: Unable to read " << gTreeName <<" from "<< arg_input_name;
    std::exit(1);
  }

  Long64_t nev = analysis_tree->GetEntries();
  VLOG("valor_sbn",pNOTICE) << "Input analysis tree has " << nev << ((nev==1) ? " entry." : " entries.");

  event::RecoEvent *pevent = nullptr;
  analysis_tree->SetBranchAddress("reco_events", &pevent);

  // Loop over events
  // For testing
  for(Long64_t iev = 0; iev < nev; iev++) {
    analysis_tree->GetEntry(iev);
    
    event::RecoEvent & event     = *pevent;
    event::RecoInteraction &reco = event.reco;
    event::Interaction * ptruth  = event.GetTruth();

    if(ptruth==nullptr) {
      VLOG("valor_sbn", pNOTICE)
        << "The number of truth entries is 0, skipping event "<<iev;
      continue;
    }

    // Get reco sample
    const int nPiReco = reco.npion + reco.npi0;
    const bool isRecoCC0Pi = (nPiReco == 0);
    const bool isRecoCCOth = !isRecoCC0Pi;

    // Check we are looking at the sample we want
    if(!CheckSample(sample,isRecoCC0Pi, isRecoCCOth)) continue;
  
    // Get the parameter we want
    const double enu_reco = reco.reco_energy;
    
    // Skip unphysical events
    if(enu_reco <= 0) continue;

    h_nom->Fill(enu_reco,reco.weight);
    
    // Now check the bin edges, add up and then set the bin contents
    for(int n = 0; n < n_bins; ++n){
      if(enu_reco > p1_bin_edges.at(n) && enu_reco < p1_bin_edges.at(n+1)){
        p1_content.at(n) += reco.weight;
      }
      if(enu_reco > m1_bin_edges.at(n) && enu_reco < m1_bin_edges.at(n+1)){
        m1_content.at(n) += reco.weight;
      }
    }
  } // Events
  std::vector<TH1D*> h_scaled{h_p1,h_m1};
  std::vector<std::vector<double> > content{p1_content, m1_content};
  for(unsigned int i = 0; i < h_scaled.size(); ++i){
    TH1D *h               = h_scaled.at(i);
    std::vector<double> v = content.at(i);
    for(int n = 0; n < n_bins; ++n){
      h->SetBinContent(n+1,v.at(n));
    }
  }

  // Scale to POT
  double scalePOT = nomPOT/static_cast<double>(mcsample_pot);
  VLOG("valor_sbn",pNOTICE) << "Scaling histograms by: " << scalePOT
                            << "\nfrom nominal:        " << nomPOT
                            << "\n and sample:         " << mcsample_pot;
  h_nom->Scale(scalePOT);
  h_p1->Scale(scalePOT);
  h_m1->Scale(scalePOT);
  std::cout << " Nominal rate: " << h_nom->Integral() << ", +1: " << h_p1->Integral() << ", -1: " << h_m1->Integral() << std::endl;

  // Now make the output file and write like we do the normal tweaks
  TFile fout(arg_output_file.c_str(),"RECREATE");
  std::string name = "env_sb_BNB_FHC_"+util::AsString(sample);
  h_nom->Write((name+"_nom").c_str());
  h_p1->Write((name+"_p1" ).c_str());
  h_m1->Write((name+"_m1" ).c_str());

  time_t endrawtime;
  struct tm * endtimeinfo;
  time (&endrawtime);
  endtimeinfo = localtime (&endrawtime);
  time_t total_time = endrawtime-scriptstartrawtime;
  std::cout << "-----------------------------------------------------------" << std::endl;
  std::cout << " End local time and date  :  " << asctime(endtimeinfo);
  std::cout << " Total time taken         :  " << total_time/static_cast<double>(60) << " minutes" << std::endl;
  std::cout << "-----------------------------------------------------------" << std::endl;

  return 0;
}
//--------------------------------------------------------------------
std::vector<double> GetBinEdges(const valor::VALORBinning *vb){
  const int n = vb->NBins();
  std::vector<double> edges(n+1,0.);
  for(int i = 0; i < n; ++i){
    edges.at(i) = vb->BinMinimum(i,0);
  }
  edges.at(n) = vb->BinMaximum(n-1,0);
  return edges;
}
//--------------------------------------------------------------------
std::vector<double> GetPlus1SigmaEdges(const std::vector<double> &b, const double scale){
  std::vector<double> edges;
  double scalePlus1 = 1+scale;
  edges = GetScaledBinEdges(b,scalePlus1);
  return edges;
}
//--------------------------------------------------------------------
std::vector<double> GetMinus1SigmaEdges(const std::vector<double> &b, const double scale){
  std::vector<double> edges;
  double scalePlus1 = 1-scale;
  edges = GetScaledBinEdges(b,scalePlus1);
  return edges;
}
//--------------------------------------------------------------------
std::vector<double> GetScaledBinEdges(const std::vector<double> &b, const double scale){
  std::vector<double> edges(b);
  // Don't modify the first and last edge, 
  // such that the total number of events remains constant
  for(unsigned int i = 1; i < edges.size()-1; ++i){
    edges.at(i) *= scale;
  }
  return edges;
}
//--------------------------------------------------------------------
bool CheckSample(const Sample_t &s, const bool &cc0pi, const bool &ccoth){
  
  if(s == ksNuMuCC) return true;
  else if(s == ksNuMuCC0piNtrk && cc0pi) return true;
  else if(s == ksNuMuCCoth && ccoth) return true;

  VLOG("valor_sbn",pINFO) << " Sample: " << util::AsString(s) << "does not match current event where CC0Pi: " << cc0pi << " and other: " << ccoth;

  return false;
}
//--------------------------------------------------------------------
