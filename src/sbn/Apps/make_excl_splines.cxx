//____________________________________________________________________________
/*!

  \app       valor_sbn-make_excl_splines

  \brief

  \syntax    valor_sbn-make_excl_splines

  \options     --output              : Where to save splines to. [def: valor_splines_[SAMPLE]_[PARAM]_[BEAM].root]
               --input               : input_analysis_file.root
               --config              : Analysis configuration file [required]
               --sample              : Topology [def: numulikeCChigh]
               --detector            : Detector [def: sbn_nd]
               --beam                : Beam [def: BNB_FHC]
               --spectra-write-opt   : Write options for spectra [def: pdfts_rf]
               --mesg-thresholds     : Message thresholds [def: "verbosity.xml"]

  \author    Rhiannon Jones <rjones@hep.ph.liv,ac,uk>
  University of Liverpool

  \created   March 15th, 2020

  \copyright Copyright (c) 2010-2020, The VALOR group. All rights reserved.

*/
//____________________________________________________________________________

// System
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
#include <utility>
#include <algorithm>
// ROOT
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TBranch.h>
#include <TLeaf.h>
#include <TSystem.h>
// ROOT
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1.h>
#include <TH2.h>
#include <TTree.h>
#include <TLeaf.h>
#include <TSpline.h>
#include <TString.h>
#include <TSystem.h>
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

using std::string;
using namespace valor;
using namespace valor::conv;

static const string gTreeName       = "sbnreco";
static const string gSubRunTreeName = "sbnsubrun";

TString splineNamePattern("spl_[BEAM]_[SAMPLE]_[MODE]_[PARAM]_[TRUE]_[RECO]");
TString objNamePattern("spl_[MODE]_[PARAM]");

TString BuildSplineName(const Sample_t &s,
    const BeamConf_t  &b,
    const ReacMode_t  &m,
    const std::string &p,
    const int         &itrue,
    const int         &ireco);
TString BuildObjName(const ReacMode_t &m,
    const std::string &p);
bool CheckSample(const event::RecoInteraction &reco, 
    const bool &numu, 
    const valor::conv::Sample_t &sample, 
    const bool &other);
valor::conv::Sample_t GetOtherSample(const valor::conv::Sample_t &s, 
    const bool &numu, 
    const bool &iscc);
bool CheckTrueFinalState(const std::vector<event::FinalStateParticle> &fsps, 
    const bool numu,
    const valor::conv::Sample_t &sample, 
    const bool &other);
void CheckNuFlav(const std::string &input,
    bool &is_nueint, 
    bool &is_nueosc,
    bool &is_nuenumu,
    bool &is_numu,
    bool &is_nue);

//___________________________________________________________________
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
  arg.Read(argc,argv,"$VALOR_EXPT/config/apps/universes.arg:$VALOR_EXPT/config/apps/make_excl_splines.arg");
  VLOG("valor_sbn", pNOTICE) << arg;

  // Get arguments
  string arg_config_file   = arg.GetString("config");
  string arg_input_name    = arg.GetString("input");
  string arg_output_file   = arg.GetString("output");
  string arg_sample        = arg.GetString("sample");
  string arg_beam          = arg.GetString("beam");
  string arg_detector      = arg.GetString("detector");
  string arg_systematic    = arg.GetString("systematic");
  string arg_write_opt     = arg.GetString("spectra-write-opt");
  bool   other_sample      = arg.GetBool("other-sample");

  // From arguments
  string mesg_thresholds = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  string config_file     = util::CompleteConfigPath(arg_config_file);
  BeamConf_t beam        = util::BeamConfFromString (arg_beam    );
  Sample_t   sample      = util::SampleFromString   (arg_sample  );
  Detector_t detector    = util::DetectorFromString (arg_detector);

  // Message thresholds
  Messenger::Instance()->Configure(mesg_thresholds);

  // If the write options for the spectra are empty, fill with pdfts_rf
  if(arg_write_opt == "")
    arg_write_opt = "pdfts_rf";

  // Determine sample-types
  bool is_nueint  = false;
  bool is_nueosc  = false;
  bool is_nuenumu = false;
  bool is_numu    = false;
  bool is_nue     = false;

  CheckNuFlav(arg_input_name, is_nueint, is_nueosc, is_nuenumu, is_numu, is_nue);

  // Get the POT of the sample from the subrun tree
  double mcsample_pot = -1.;
  TChain * subrun_tree = new TChain(gSubRunTreeName.c_str());
  subrun_tree->Add(arg_input_name.c_str());
  if(!subrun_tree || !subrun_tree->GetEntries()) {
    VLOG("valor_sbn", pFATAL)
      << "Error: Unable to read " << gSubRunTreeName
      <<" from "<< arg_input_name;
    exit(1);
  }

  Long64_t nev_subrun = subrun_tree->GetEntries();
  VLOG("valor_sbn", pNOTICE)
    << "Input subrun tree has " << nev_subrun << ((nev_subrun==1) ? " entry." : " entries.");

  //  TBranch *b = subrun_tree->GetBranch("totgoodpot");
  TBranch *b = subrun_tree->GetBranch("totpot"); // TEMP FOR BROKEN FILE
  unsigned int npot = subrun_tree->GetEntries();
  for(unsigned int i = 0; i < npot; ++i){
    b->GetEntry(i);
    mcsample_pot += b->GetLeaf("totpot")->GetValue(); // TEMP FOR BROKEN FILE
  }

  if(mcsample_pot == -1.){
    VLOG("valor_sbn", pFATAL)
      << "Error: Not able to access MCSample POT from " << gSubRunTreeName;
    exit(1);
  }
  VLOG("valor_sbn", pNOTICE)
    << "POT in the input file is " << mcsample_pot;
  // Setup the spline definition
  const std::string syst           = arg_systematic;
  const std::vector<double> &knots = {-3.0,-2.0,-1.0,0.0,1.0,2.0,3.0};
  const int   n_knots              = knots.size();

  // Get model & configure
  // Make an elements without reading the MC
  std::string elem_readopt("nomc nosplines");
  CompoundFitElements * elements = new CompoundFitElements();
  elements->Read(util::CompleteConfigPath(config_file),elem_readopt.c_str());

  // Then tell it about the universes and read the MC
  FitModelABC * model = elements->FitModel();
  CompoundFitModel * cmodel = dynamic_cast<CompoundFitModel*>(model);
  assert(cmodel);
  GenericSingleSampleFitModel * gmodel = 0;
  bool got_appropriate_model = false;
  for (unsigned int ism = 0 ; ism < cmodel->GetNSubModels() ; ism++) {
    gmodel = dynamic_cast<GenericSingleSampleFitModel*>(cmodel->GetSubModel(ism));
    if  (gmodel->GetDetector() == detector &&
        gmodel->GetBeam()     == beam)
    { got_appropriate_model = true; break; }
  }
  if (!got_appropriate_model) {
    VLOG("valor_sbn", pFATAL) << "Failed to identify appropriate fit model to get binning.";
  }
  assert(gmodel);

  // Get the nominal POT
  double nomPOT = gmodel->GetPOT();

  // And finally read the MC properly
  std::string model_readopt("forcedst nosplines");
  gmodel->Read(gmodel->GetLastConfigFileRead().c_str(),model_readopt.c_str());

  //
  // 6) Build the splines with the universe ID list passed to the tweaked GSSFM universe-based functions
  //
  const SingleSampleKineBinning & binning = *(gmodel->GetBinning());

  // Get the modelist from the model configuration
  const std::vector<conv::ReacMode_t> & reac_modes = gmodel->GetReactionModes();

  // Binning choice needs to be made carefully, likely that stats will be very low in
  // some bins in the standard 2D ereco-etrue param space so will need to redefine
  //
  // Redefinition needs to be along the edges of existing bins in the analysis so as to
  // not cause leakage
  //
  const VALORBinning * reco_ob = binning.RecoOptBinning();
  const int n_reco_bins_ob     = reco_ob->NBins();

  // Get the true, standard binning for mode 0
  // Given that we are summing them all together, have to assume true binning
  // is the same across all modes
  //
  const VALORBinning * true_sb = binning.TrueSmpBinning(0);
  const int n_true_bins_sb = true_sb->NBins();

  // Read the SBNCode input file
  TChain * analysis_tree = new TChain(gTreeName.c_str());
  analysis_tree->Add(arg_input_name.c_str());
  if(!analysis_tree || !analysis_tree->GetEntries()) {
    VLOG("valor_sbn", pFATAL)
      << "Error: Unable to read " << gTreeName
      <<" from "<< arg_input_name;
    exit(1);
  }

  Long64_t nev = analysis_tree->GetEntries();
  VLOG("valor_sbn", pNOTICE)
    << "Input analysis tree has " << nev << ((nev==1) ? " entry." : " entries.");


  event::RecoEvent *pevent = nullptr;
  analysis_tree->SetBranchAddress("reco_events", &pevent);

  // Output file - first make the substitutions for sample/parameter
  // Modelist to save any modes which result in non-zero splines
  std::vector<std::string> applied_to_modes;

  conv::Sample_t print_sample = sample;
  
  if(other_sample)
    print_sample = GetOtherSample(sample,!is_nue,true);
  else
    print_sample = sample;

  // Get the true event rate for the final state and the reco event rate for the final state
  // in every true:reco bin
  // This will be used in the spline construction later
  // Summing over all modes
  std::vector< std::vector< int > > bins_true_count, bins_reco_count;

  // Initialise histogram for validation
  std::vector<double> bin_edges(n_reco_bins_ob+1,0.);

  // Initialise counters
  for(int itrue = 0; itrue < n_true_bins_sb; itrue++) {
    std::vector< int > bin_true_count, bin_reco_count;
    for(int ireco = 0; ireco < n_reco_bins_ob; ireco++) {
      bin_edges.at(ireco) = reco_ob->BinMinimum(ireco,0);
      bin_true_count.push_back(0);
      bin_reco_count.push_back(0);
    }
    bins_true_count.push_back(bin_true_count);
    bins_reco_count.push_back(bin_reco_count);
  }
  bin_edges.at(n_reco_bins_ob) = reco_ob->BinMaximum(n_reco_bins_ob-1,0);
  
  TH1D *h_reco_nom = new TH1D("h_reco_nom", "", n_reco_bins_ob, bin_edges.data());
  TH1D *h_reco_m1  = new TH1D("h_reco_m1", "", n_reco_bins_ob, bin_edges.data());
  
  // Filename for is we choose to store the spectra
  TString hist_outfile = arg_output_file.c_str();
  hist_outfile = hist_outfile.ReplaceAll("[BEAM]"   , util::AsString(beam).c_str());
  hist_outfile = hist_outfile.ReplaceAll("[DET]"    , util::AsString(detector).c_str());
  hist_outfile = hist_outfile.ReplaceAll("[SAMPLE]" , util::AsString(print_sample).c_str());
  hist_outfile = hist_outfile.ReplaceAll("[PARAM]"  , syst.c_str());
  hist_outfile = hist_outfile.ReplaceAll(".root","_spectra.root");
  VLOG("valor_sbn", pNOTICE) << "Saving spectra to: "<< hist_outfile;
  TFile histout(hist_outfile.Data(),"RECREATE");
 
  // Loop over events
  // For testing
  for(Long64_t iev = 0; iev < nev; iev++) {

    analysis_tree->GetEntry(iev);

    event::RecoEvent & event = *pevent;
    event::RecoInteraction &reco = event.reco;
    event::Interaction * ptruth = event.GetTruth();
    event::Interaction & truth = *ptruth;

    // Before we do anything, make sure the current event fits the description of the sample
    if(!CheckSample(reco,is_numu,sample,other_sample)){
      LOG("valor_sbn",pINFO)   << "Current event has \n"
        << "Numu: " << is_numu << "\n"
        << reco.npion << " pions, \n " 
        << reco.npi0 << " pi0s and \n " 
        << reco.nproton << " protons and does not match the desired sample type: " 
        << util::AsString(print_sample) << "\n Skipping.";
      continue;
    }
    if(ptruth==nullptr) {
      VLOG("valor_sbn", pNOTICE)
        << "The number of truth entries is 0, skipping event "<<iev;
      continue;
    }

    std::vector<event::FinalStateParticle> &fsps = truth.finalstate;
    bool true_numu                               = ((abs(truth.neutrino.pdg) == 14) ? 1 : 0);
    double enu_true                              = truth.neutrino.energy;
    double enu_reco                              = reco.reco_energy;

    // Loop over the reco and true bins
    // Check current event and count if necessary
    for(int itrue = 0; itrue < n_true_bins_sb; itrue++) {
      for(int ireco = 0; ireco < n_reco_bins_ob; ireco++) {
        if(enu_true > true_sb->BinMinimum(itrue,0)  &&
            enu_true <= true_sb->BinMaximum(itrue,0) &&
            enu_reco > reco_ob->BinMinimum(ireco,0)  &&
            enu_reco <= reco_ob->BinMaximum(ireco,0)){
          bins_reco_count.at(itrue).at(ireco)++;
          h_reco_nom->Fill(enu_reco,reco.weight);
          if(CheckTrueFinalState(fsps, true_numu, sample, other_sample)){
            bins_true_count.at(itrue).at(ireco)++;
            h_reco_m1->Fill(enu_reco,reco.weight);
          }
        } // Current bin
      } // Reco bin
    } // True bin
  }// Events
  histout.cd();

  // Construct p1 from m1 as they are defined to be symmetric
  // Scale to POT
  double scalePOT = nomPOT/static_cast<double>(mcsample_pot);
  VLOG("valor_sbn",pNOTICE) << "Scaling histograms by: " << scalePOT
                            << "\nfrom nominal:        " << nomPOT
                            << "\n and sample:         " << mcsample_pot;

  h_reco_m1->Scale(scalePOT);
  h_reco_nom->Scale(scalePOT);
  TH1D *h_reco_diff = static_cast<TH1D*>(h_reco_nom->Clone("h_reco_diff"));
  TH1D *h_reco_p1   = static_cast<TH1D*>(h_reco_nom->Clone("h_reco_p1"));
  h_reco_diff->Add(h_reco_m1,-1);
  h_reco_p1->Add(h_reco_diff);

  VLOG("valor_sbn",pNOTICE) << "From input: "
                            << "\nNominal rate: " << h_reco_nom->Integral()
                            << "\n+1sigma rate: " << h_reco_p1->Integral()
                            << "\n-1sigma rate: " << h_reco_m1->Integral();
  h_reco_nom->Write();
  h_reco_p1->Write();
  h_reco_m1->Write();
  histout.Close();

  // Now define the spline file
  TString ts_outfile = arg_output_file.c_str();
  ts_outfile = ts_outfile.ReplaceAll("[BEAM]"   , util::AsString(beam).c_str());
  ts_outfile = ts_outfile.ReplaceAll("[DET]"    , util::AsString(detector).c_str());
  ts_outfile = ts_outfile.ReplaceAll("[SAMPLE]" , util::AsString(print_sample).c_str());
  ts_outfile = ts_outfile.ReplaceAll("[PARAM]"  , syst.c_str());
  VLOG("valor_sbn", pNOTICE) << "Saving VALOR response functions to: "<<ts_outfile;
  TFile fout(ts_outfile.Data(),"RECREATE");

  int n_splines_written = 0;
  for(const ReacMode_t &mode : reac_modes){

    // TObjArray for the current parameter and mode
    TString objname = BuildObjName(mode,syst);
    TObjArray *spline_array = new TObjArray();
    spline_array->SetName(objname.Data());

    for(int itrue = 0; itrue < n_true_bins_sb; itrue++) {
      for(int ireco = 0; ireco < n_reco_bins_ob; ireco++) {
        std::vector<double> x,y;
        for(int iknot = 0; iknot < n_knots; ++iknot){
          double knot = knots.at(iknot);
          int n_reco  = bins_reco_count.at(itrue).at(ireco);
          int n_true  = bins_true_count.at(itrue).at(ireco);
          double migration = (n_reco > 4) ? (n_reco+knot*abs(n_reco-n_true))/static_cast<double>(n_reco) : 1;
          if(std::isnan(migration)){
            VLOG("valor_sbn",pDEBUG)<<"Migration value is not a number, setting to 1";
            migration = 1;
          }
          x.push_back(knot);
          y.push_back(migration);
        }
        assert((x.size() == y.size()));// && (x.size() == knots.size())); Not the case when there are repeated points
        TString name  = BuildSplineName(print_sample, beam, mode, syst, itrue, ireco);
        TString title = name; // Make this contain real kinematic ranges
        TSpline3 *spl = new TSpline3(title.Data(), x.data(), y.data(), x.size());
        spl->SetName(name.Data());
        spline_array->Add(spl);
        n_splines_written++;
        if (n_splines_written%1000==0) {
          VLOG("valor_sbn",pNOTICE)<<"Written "<<n_splines_written<<" splines so far.";
        }

      } // True bin
    } // Reco bin
    spline_array->Write(objname.Data(),TObject::kSingleKey);
  } // Mode

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
//___________________________________________________________________
TString BuildSplineName(const Sample_t    &s,
    const BeamConf_t  &b,
    const ReacMode_t  &m,
    const std::string &p,
    const int         &itrue,
    const int         &ireco){

  TString name = splineNamePattern;

  name = name.ReplaceAll("[BEAM]"   , util::AsString(b).c_str());
  name = name.ReplaceAll("[SAMPLE]" , util::AsString(s).c_str());

  name = name.ReplaceAll("[MODE]"   , util::AsString(m).c_str());
  name = name.ReplaceAll("[PARAM]"  , p.c_str());

  name = name.ReplaceAll("[TRUE]" , TString::Format("%d", itrue ));
  name = name.ReplaceAll("[RECO]" , TString::Format("%d", ireco ));

  return name;

}//___________________________________________________________________
TString BuildObjName(const ReacMode_t  &m,
    const std::string &p){

  TString name = objNamePattern;

  name = name.ReplaceAll("[MODE]"   , util::AsString(m).c_str());
  name = name.ReplaceAll("[PARAM]"  , p.c_str());

  return name;

}
//___________________________________________________________________
bool CheckSample(const event::RecoInteraction &reco, const bool &numu, const valor::conv::Sample_t &sample, const bool &other){
  if(numu){
    if(sample == valor::conv::ksNuMuCC || sample == valor::conv::ksNuMuLikeCChigh) return true;
    else if(sample == valor::conv::ksNuMuCC0piNtrk){
      if((reco.npion+reco.npi0) == 0)
        return ((other) ? false : true);
      else {
        return ((other) ? true : false);
      }
    }
    else if(sample == valor::conv::ksNuMuCC0pi1trk){
      if((reco.npion+reco.npi0) == 0 && reco.nproton == 0)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuMuCC0pi2trk){
      if((reco.npion+reco.npi0) == 0 && reco.nproton == 1)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuMuCC1piC){
      if(reco.npion == 1 && reco.npi0 == 0)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuMuCC1pi0){
      if(reco.npion == 0 && reco.npi0 == 1)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuMuCC1piC1pi0){
      if(reco.npion == 1 && reco.npi0 == 1)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuMuCC2piC){
      if(reco.npion == 2 && reco.npi0 == 0)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuMuCCoth){
      if((reco.npion + reco.npi0) >= 2)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else{
      LOG("valor_sbn",pFATAL) << "Error: Desired sample " << valor::util::AsString(sample) << " is not distinguishable from the information in this set of events ";
      return false;
    }
  }
  if(!numu){
    if(sample == valor::conv::ksNuECC || sample == valor::conv::ksNuELikeCChigh) return true;
    else if(sample == valor::conv::ksNuECC0pi){
      if((reco.npion+reco.npi0) == 0)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuECC1piC){
      if(reco.npion == 1 && reco.npi0 == 0)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else if(sample == valor::conv::ksNuECCoth){
      if((reco.npion+reco.npi0) >= 2)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else{
      LOG("valor_sbn",pFATAL) << "Error: Desired sample " << valor::util::AsString(sample) << " is not distinguishable from the information in this set of events ";
      return false;
    }
  }
  return false; 
}
void CheckNuFlav(const std::string &input,
    bool &is_nueint, 
    bool &is_nueosc,
    bool &is_nuenumu,
    bool &is_numu,
    bool &is_nue){

  string str_numu = "Numu";
  string str_nue  = "Nue";
  string str_int  = "_Int";
  string str_osc  = "_Osc";

  //Find substrings and check the selected nuE sample-type if necessary
  size_t found_nue  = input.find(str_nue);
  size_t found_numu = input.find(str_numu);

  // Get selected nuMu from sample name
  if(found_nue == string::npos && found_numu != string::npos)
    is_numu = true;

  if(found_nue != string::npos){
    is_nue = true;
    // We are looking at a nue sample, check if osc, intrinsic or numu
    size_t found_nueosc  = input.find(str_osc);
    size_t found_nueint  = input.find(str_int);
    size_t found_nuenumu = input.find(str_numu);
    if(found_nueosc != string::npos && found_nueint == string::npos && found_nuenumu == string::npos)
      is_nueosc = true;
    else if(found_nueosc != string::npos){
      VLOG("valor_sbn", pFATAL)
        << "Error: Found selected nuE oscillated file with hint of intrinsic and/or numu in the name - misleading: " << input;
      exit(1);
    }
    if(found_nueint != string::npos && found_nueosc == string::npos && found_nuenumu == string::npos)
      is_nueint = true;
    else if(found_nueint != string::npos){
      VLOG("valor_sbn", pFATAL)
        << "Error: Found selected nuE intrinsic file with hint of oscillated and/or numu in the name - misleading: " << input;
      exit(1);
    }
    if(found_nuenumu != string::npos && found_nueosc == string::npos && found_nueint == string::npos)
      is_nuenumu = true;
    else if(found_nuenumu != string::npos){
      VLOG("valor_sbn", pFATAL)
        << "Error: Found selected nuE numu file with hint of oscillated and/or intrinsic in the name - misleading: " << input;
      exit(1);
    }
  }
  bool found_nues[] = {is_nueosc, is_nueint, is_nuenumu};
  if(found_nue && std::count(found_nues, found_nues+sizeof(found_nues), 1) > 1){
    VLOG("valor_sbn", pFATAL)
      << "Error: Found multiple selected nuE types in filename - misleading: " << input;
    exit(1);
  }
  // Make sure we are finding at least 1 of numu or nue in the name
  bool found[] = {is_numu, is_nueosc, is_nueint, is_nuenumu};
  if(std::count(found, found+sizeof(found), 1) == 0){
    VLOG("valor_sbn", pFATAL)
      << "Error: Found hint of neither selected nuE (" << str_nue << ", " << str_int << ", " << str_osc << ") nor selected nuMu ( " << str_numu << ") in filename - misleading: " << input;
    exit(1);
  }

  std::cout << " Input filename : " << input << " - ";
  if(is_nueosc)
    std::cout << " Selected NuE, Oscillated " << std::endl;
  if(is_nueint)
    std::cout << " Selected NuE, Intrinsic " << std::endl;
  if(is_nuenumu)
    std::cout << " Selected NuE, NuMu " << std::endl;
  if(is_numu)
    std::cout << " Selected NuMu, NuMu " << std::endl;
}
valor::conv::Sample_t GetOtherSample(const valor::conv::Sample_t &s, const bool &numu, const bool &iscc){

  // Numu CC
  if(iscc && numu){
    valor::conv::Sample_t new_s = valor::util::SampleFromString("numuCCoth");
    assert(new_s != valor::conv::ksUndefined);
    return new_s;
  }

  // Numu NC
  else if(!iscc && numu){
    valor::conv::Sample_t new_s = valor::util::SampleFromString("NCoth");
    assert(new_s != valor::conv::ksUndefined);
    return new_s;
  }

  // Nue CC
  else if(iscc && !numu){
    valor::conv::Sample_t new_s = valor::util::SampleFromString("nueCCoth");
    assert(new_s != valor::conv::ksUndefined);
    return new_s;
  }

  // Nue NC
  else if(!iscc && !numu){
    valor::conv::Sample_t new_s = valor::util::SampleFromString("NCoth");
    assert(new_s != valor::conv::ksUndefined);
    return new_s;
  }
  else{
    LOG("valor_sbn",pNOTICE) << "The 'other' version of this sample cannot be determined, returning the input, " << valor::util::AsString(s);
    return s;
  }
}
bool CheckTrueFinalState(const std::vector<event::FinalStateParticle> &fsps,
    const bool numu,
    const valor::conv::Sample_t &sample, 
    const bool &other){

  // Just count pions for now
  unsigned int npip = 0;
  unsigned int npim = 0;
  unsigned int npi0 = 0;
  unsigned int np   = 0;

  for(unsigned int p = 0; p < fsps.size(); ++p){
    // Final state particles need counting
    if (fsps[p].status_code != 1) {continue;}
    else if(fsps[p].pdg == genie::kPdgPiP)    npip++;
    else if(fsps[p].pdg == genie::kPdgPiM)    npim++;
    else if(fsps[p].pdg == genie::kPdgPi0)    npi0++;
    else if(fsps[p].pdg == genie::kPdgProton) np++;
  }
  unsigned int npiC = npip+npim;
  
  if(sample == valor::conv::ksNuMuCC || sample == valor::conv::ksNuMuLikeCChigh) return true;
  else if(sample == valor::conv::ksNuMuCC0piNtrk){
    if(numu){
      if((npiC+npi0) == 0)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else return false;
  }
  else if(sample == valor::conv::ksNuMuCC0pi1trk){
    if(numu){
      if((npiC+npi0) == 0 && np == 0)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else return false;
  }
  else if(sample == valor::conv::ksNuMuCC0pi2trk){
    if(numu){
      if((npiC+npi0) == 0 && np == 1)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else return false;
  }
  else if(sample == valor::conv::ksNuMuCC1piC){
    if(numu){
      if(npiC == 1 && npi0 == 0)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else return false;
  }
  else if(sample == valor::conv::ksNuMuCC1pi0){
    if(numu){
      if(npiC == 0 && npi0 == 1)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else return false;
  }
  else if(sample == valor::conv::ksNuMuCC1piC1pi0){
    if(numu){
      if(npiC == 1 && npi0 == 1)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else return false;
  }
  else if(sample == valor::conv::ksNuMuCC2piC){
    if(numu){
      if(npiC == 2 && npi0 == 0)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else return false;
  }
  else if(sample == valor::conv::ksNuMuCCoth){
    if(numu){
      if((npiC + npi0) >= 2)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else return false;
  }
  else{
    LOG("valor_sbn",pNOTICE) << "Error: Desired sample " << valor::util::AsString(sample) << " is not distinguishable from the information in this set of events ";
    return false;
  }
  if(sample == valor::conv::ksNuECC || sample == valor::conv::ksNuELikeCChigh) return true;
  else if(sample == valor::conv::ksNuECC0pi){
    if(!numu){
      if((npiC+npi0) == 0)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else return false;
  }
  else if(sample == valor::conv::ksNuECC1piC){
    if(!numu){
      if(npiC == 1 && npi0 == 0)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else return false;
  }
  else if(sample == valor::conv::ksNuECCoth){
    if(!numu){
      if((npiC+npi0) >= 2)
        return ((other) ? false : true);
      else return ((other) ? true : false);
    }
    else return false;
  }
  else{
    LOG("valor_sbn",pINFO) << "Error: Desired sample " << valor::util::AsString(sample) << " is not distinguishable from the information in this set of events";
    return false;
  }
  return false;                  
}
