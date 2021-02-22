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

TString BuildSplineName(const std::string &s,
                        const BeamConf_t  &b,
                        const ReacMode_t  &m,
                        const std::string &p,
                        const int         &itrue,
                        const int         &ireco);
TString BuildObjName(const ReacMode_t &m,
                     const std::string &p);
std::vector<double> GetBinEdges(const VALORBinning *vb);
bool IsCC0Pi(const event::Interaction &truth);
std::shared_ptr<TH2D> GetHistRatio(const std::shared_ptr<TH2D> &num, 
                                   const std::shared_ptr<TH2D> &den);
std::shared_ptr<TH1D> Get1DHistFrom2D(const std::shared_ptr<TH2D> &h2D, 
                                      const std::string &name, 
                                      const std::vector<double> &reco_be);
void HistFileName(TString           &name,
                  const std::string &s,
                  const BeamConf_t  &b,
                  const Detector_t  &d,
                  const std::string &p);
void SplineFileName(TString           &name,
                    const std::string &s,
                    const BeamConf_t  &b,
                    const Detector_t  &d,
                    const std::string &p);

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
  string arg_beam          = arg.GetString("beam");
  string arg_detector      = arg.GetString("detector");

  // From arguments
  string mesg_thresholds = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  string config_file     = util::CompleteConfigPath(arg_config_file);
  BeamConf_t beam        = util::BeamConfFromString (arg_beam    );
  Detector_t detector    = util::DetectorFromString (arg_detector);

  // Message thresholds
  Messenger::Instance()->Configure(mesg_thresholds);

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
    if (gmodel->GetDetector() == detector &&
        gmodel->GetBeam()     == beam)
    { got_appropriate_model = true; break; }
  }
  if (!got_appropriate_model) {
    VLOG("valor_sbn", pFATAL) << "Failed to identify appropriate fit model to get binning.";
  }
  assert(gmodel);
  
  // And finally read the MC properly
  std::string model_readopt("forcedst nosplines");
  gmodel->Read(gmodel->GetLastConfigFileRead().c_str(),model_readopt.c_str());

  // Get the nominal POT
  double nomPOT = gmodel->GetPOT();

  // Get the modelist from the model configuration
  const std::vector<conv::ReacMode_t> & reac_modes = gmodel->GetReactionModes();
  
  // 1) Get binning from configuration
  // 2) Get the true, standard binning for mode 0
  // Given that we are summing them all together, have to assume true binning
  // is the same across all modes
  // 3) Get the reco bins 
  // 4) Get the bin edges
  const SingleSampleKineBinning & binning = *(gmodel->GetBinning());
  const VALORBinning * true_sb            = binning.TrueSmpBinning(0);
  const VALORBinning * reco_ob            = binning.RecoOptBinning();
  const std::vector<double> true_bin_edges = GetBinEdges(true_sb);
  const std::vector<double> reco_bin_edges = GetBinEdges(reco_ob);
  const int n_true_bins = true_bin_edges.size()-1;
  const int n_reco_bins = reco_bin_edges.size()-1;

  // Various event histograms
  std::map<std::string, std::shared_ptr<TH2D> > eventHistogramMap;
  for(const auto &name : std::vector<std::string>({"trueCC0Pi_recoCCOth", 
                                                   "trueCCOth_recoCC0Pi",
                                                   "trueCC0Pi", 
                                                   "trueCCOth", 
                                                   "recoCC0Pi", 
                                                   "recoCCOth"}))
  {
    eventHistogramMap.emplace(name, std::make_shared<TH2D>(name.c_str(), "", true_bin_edges.size()-1, true_bin_edges.data(), reco_bin_edges.size()-1, reco_bin_edges.data()));
  }

  // Now actually assign the histograms
  auto & trueCC0Pi_recoCCOth = eventHistogramMap.at("trueCC0Pi_recoCCOth");
  auto & trueCCOth_recoCC0Pi = eventHistogramMap.at("trueCCOth_recoCC0Pi");
  auto & trueCC0Pi           = eventHistogramMap.at("trueCC0Pi");
  auto & trueCCOth           = eventHistogramMap.at("trueCCOth");
  auto & recoCC0Pi           = eventHistogramMap.at("recoCC0Pi");
  auto & recoCCOth           = eventHistogramMap.at("recoCCOth");
  
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

  // Loop over events
  // For testing
  for(Long64_t iev = 0; iev < nev; iev++) {

    analysis_tree->GetEntry(iev);

    event::RecoEvent & event = *pevent;
    event::RecoInteraction &reco = event.reco;
    event::Interaction * ptruth = event.GetTruth();
    event::Interaction & truth = *ptruth;

    if(ptruth==nullptr) {
      VLOG("valor_sbn", pNOTICE)
        << "The number of truth entries is 0, skipping event "<<iev;
      continue;
    }

    // Get reco sample
    const int nPiReco = reco.npion + reco.npi0;
    const bool isRecoCC0Pi = (nPiReco == 0);
    const bool isRecoCCOth = !isRecoCC0Pi;
  
    // Get true sample
    const bool isTrueCC0Pi = IsCC0Pi(truth);
    const bool isTrueCCOth = (truth.neutrino.iscc && !isTrueCC0Pi);
    const bool isTrueNC    = (!truth.neutrino.iscc);
  
    if(!isTrueCC0Pi && !isTrueCCOth && !isTrueNC)
      VLOG("valor_sbn", pFATAL) << " Error: Somehow not categorised the event as CC or NC, failing.";

    // Get the energies
    const double enu_true = truth.neutrino.energy;
    const double enu_reco = reco.reco_energy;
    if(enu_reco <= 0) continue;

    // Fill the histograms
    if(isTrueCC0Pi && isRecoCCOth){
      trueCC0Pi_recoCCOth->Fill(enu_true, enu_reco, reco.weight);
    }
    
    if(isTrueCCOth && isRecoCC0Pi){
      trueCCOth_recoCC0Pi->Fill(enu_true, enu_reco, reco.weight);
    }
    
    if(isTrueCC0Pi){
      trueCC0Pi->Fill(enu_true, enu_reco, reco.weight);
    }
    
    if(isTrueCCOth){
      trueCCOth->Fill(enu_true, enu_reco, reco.weight);
    }

    if(isRecoCCOth){
      recoCCOth->Fill(enu_true, enu_reco, reco.weight);
    }
    
    if(isRecoCC0Pi){
      recoCC0Pi->Fill(enu_true, enu_reco, reco.weight);
    }
  }// Events

  // Filename for is we choose to store the spectra
  TString hist_outfile_recoCC0Pi_CCOthScaled = arg_output_file.c_str();
  TString hist_outfile_recoCC0Pi_CC0PiScaled = arg_output_file.c_str();
  TString hist_outfile_recoCCOth_CCOthScaled = arg_output_file.c_str();
  TString hist_outfile_recoCCOth_CC0PiScaled = arg_output_file.c_str();

  HistFileName(hist_outfile_recoCC0Pi_CCOthScaled, "numuCC0piNtrk", beam, detector, "ccother_migration");
  HistFileName(hist_outfile_recoCC0Pi_CC0PiScaled, "numuCC0piNtrk", beam, detector, "cc0pi_migration");
  HistFileName(hist_outfile_recoCCOth_CCOthScaled, "numuCCoth",     beam, detector, "ccother_migration");
  HistFileName(hist_outfile_recoCCOth_CC0PiScaled, "numuCCoth",     beam, detector, "cc0pi_migration");

  TFile histout_recoCC0Pi_CCOthScaled(hist_outfile_recoCC0Pi_CCOthScaled, "RECREATE");
  TFile histout_recoCC0Pi_CC0PiScaled(hist_outfile_recoCC0Pi_CC0PiScaled, "RECREATE");
  TFile histout_recoCCOth_CCOthScaled(hist_outfile_recoCCOth_CCOthScaled, "RECREATE");
  TFile histout_recoCCOth_CC0PiScaled(hist_outfile_recoCCOth_CC0PiScaled, "RECREATE");

  // Scale to POT
  double scalePOT = nomPOT/static_cast<double>(mcsample_pot);
  VLOG("valor_sbn",pNOTICE) << "Scaling histograms by: " << scalePOT
                            << "\nfrom nominal:        " << nomPOT
                            << "\n and sample:         " << mcsample_pot;
  // Loop over the knots
  const std::vector<double> knots({-3.0,-2.0,-1.0,0.0,1.0,2.0,3.0});
  std::map< unsigned int, std::shared_ptr<TH2D> > knotHistMap_responseCC0Pi_CC0PiScaled;
  std::map< unsigned int, std::shared_ptr<TH2D> > knotHistMap_responseCC0Pi_CCOthScaled;
  std::map< unsigned int, std::shared_ptr<TH2D> > knotHistMap_responseCCOth_CCOthScaled;
  std::map< unsigned int, std::shared_ptr<TH2D> > knotHistMap_responseCCOth_CC0PiScaled;
  unsigned int knIt = 0;
  for(const double &kn : knots){
    // The number of CC0Pi events in the CCOther sample is trueCC0Pi_recoCCOth, 
    // This defines the 'nominal' amount of CC0Pi->CCOther migration
    // To define a nsigma variation, scale this migration by (1+kn) (100% uncertainty)
    //
    // The number of extra events to add to the CCOther sample is: trueCC0Pi_recoCCOth*(kn)
    // So we need to subtract these events away from the reco CC0Pi sample to balance it
    //
    // Define the magnitude by which to scale the migration to account for the prior 
    // uncertainty, default: 100% = 1*(knot value)
    double factor = 0.2458*kn;

    std::shared_ptr<TH2D> diffCC0Pi(static_cast<TH2D*>(trueCC0Pi_recoCCOth->Clone()));
    diffCC0Pi->Scale(factor);
   
    std::shared_ptr<TH2D> recoCCOth_CC0PiScaled(static_cast<TH2D*>(recoCCOth->Clone()));
    recoCCOth_CC0PiScaled->Add(diffCC0Pi.get());
    
    std::shared_ptr<TH2D> recoCC0Pi_CC0PiScaled(static_cast<TH2D*>(recoCC0Pi->Clone()));
    recoCC0Pi_CC0PiScaled->Add(diffCC0Pi.get(),-1.);
  
    // Repeat this for the CCOth->CC0Pi migration
    std::shared_ptr<TH2D> diffCCOth(static_cast<TH2D*>(trueCCOth_recoCC0Pi->Clone()));
    diffCCOth->Scale(factor);
    
    std::shared_ptr<TH2D> recoCC0Pi_CCOthScaled(static_cast<TH2D*>(recoCC0Pi->Clone()));
    recoCC0Pi_CCOthScaled->Add(diffCCOth.get());
    
    std::shared_ptr<TH2D> recoCCOth_CCOthScaled(static_cast<TH2D*>(recoCCOth->Clone()));
    recoCCOth_CCOthScaled->Add(diffCCOth.get(),-1.);
  
    // Now get the ratio of the scaled event rate to the total number of reconstructed events of the relevant type
    const std::shared_ptr<TH2D> responseCC0Pi_CC0PiScaled = GetHistRatio(recoCC0Pi_CC0PiScaled, recoCC0Pi);
    const std::shared_ptr<TH2D> responseCC0Pi_CCOthScaled = GetHistRatio(recoCC0Pi_CCOthScaled, recoCC0Pi);
    const std::shared_ptr<TH2D> responseCCOth_CCOthScaled = GetHistRatio(recoCCOth_CCOthScaled, recoCCOth);
    const std::shared_ptr<TH2D> responseCCOth_CC0PiScaled = GetHistRatio(recoCCOth_CC0PiScaled, recoCCOth);

    // Now push to the relevant map
    knotHistMap_responseCC0Pi_CC0PiScaled.emplace(knIt,responseCC0Pi_CC0PiScaled);
    knotHistMap_responseCC0Pi_CCOthScaled.emplace(knIt,responseCC0Pi_CCOthScaled);
    knotHistMap_responseCCOth_CCOthScaled.emplace(knIt,responseCCOth_CCOthScaled);
    knotHistMap_responseCCOth_CC0PiScaled.emplace(knIt,responseCCOth_CC0PiScaled);
    knIt++;

    // Now flatten the 4 scaled histograms (by integrating out the true bins) 
    // Print to a file for validation with the relevant sample and parameter name
    const int knotInt = std::round(kn);
    const std::string name_1D = "h_reco_" + (knotInt == 0 ? "nom" : (( knotInt > 0 ? "p" : "m" ) + std::to_string(std::abs(knotInt))));

    histout_recoCC0Pi_CCOthScaled.cd();
    const std::shared_ptr<TH1D> recoCC0Pi_CCOthScaled_1D = Get1DHistFrom2D(recoCC0Pi_CCOthScaled, name_1D, reco_bin_edges);
    recoCC0Pi_CCOthScaled_1D->Scale(scalePOT);
    recoCC0Pi_CCOthScaled_1D->Write();

    histout_recoCC0Pi_CC0PiScaled.cd();
    const std::shared_ptr<TH1D> recoCC0Pi_CC0PiScaled_1D = Get1DHistFrom2D(recoCC0Pi_CC0PiScaled, name_1D, reco_bin_edges);
    recoCC0Pi_CC0PiScaled_1D->Scale(scalePOT);
    recoCC0Pi_CC0PiScaled_1D->Write();

    histout_recoCCOth_CCOthScaled.cd();
    const std::shared_ptr<TH1D> recoCCOth_CCOthScaled_1D = Get1DHistFrom2D(recoCCOth_CCOthScaled, name_1D, reco_bin_edges);
    recoCCOth_CCOthScaled_1D->Scale(scalePOT);
    recoCCOth_CCOthScaled_1D->Write();

    histout_recoCCOth_CC0PiScaled.cd();
    const std::shared_ptr<TH1D> recoCCOth_CC0PiScaled_1D = Get1DHistFrom2D(recoCCOth_CC0PiScaled, name_1D, reco_bin_edges);
    recoCCOth_CC0PiScaled_1D->Scale(scalePOT);
    recoCCOth_CC0PiScaled_1D->Write();
  }
  VLOG("valor_sbn", pNOTICE) << "Filled and written histogram files";

  // Now define the spline files
  TString spl_outfile_recoCC0Pi_CCOthScaled = arg_output_file.c_str();
  TString spl_outfile_recoCC0Pi_CC0PiScaled = arg_output_file.c_str();
  TString spl_outfile_recoCCOth_CCOthScaled = arg_output_file.c_str();
  TString spl_outfile_recoCCOth_CC0PiScaled = arg_output_file.c_str();

  SplineFileName(spl_outfile_recoCC0Pi_CCOthScaled, "numuCC0piNtrk", beam, detector, "ccother_migration");
  SplineFileName(spl_outfile_recoCC0Pi_CC0PiScaled, "numuCC0piNtrk", beam, detector, "cc0pi_migration");
  SplineFileName(spl_outfile_recoCCOth_CCOthScaled, "numuCCoth", beam, detector, "ccother_migration");
  SplineFileName(spl_outfile_recoCCOth_CC0PiScaled, "numuCCoth", beam, detector, "cc0pi_migration");

  TFile splout_recoCC0Pi_CCOthScaled(spl_outfile_recoCC0Pi_CCOthScaled, "RECREATE");
  TFile splout_recoCC0Pi_CC0PiScaled(spl_outfile_recoCC0Pi_CC0PiScaled, "RECREATE");
  TFile splout_recoCCOth_CCOthScaled(spl_outfile_recoCCOth_CCOthScaled, "RECREATE");
  TFile splout_recoCCOth_CC0PiScaled(spl_outfile_recoCCOth_CC0PiScaled, "RECREATE");
  
  int n_splines_written = 0;
  for(const ReacMode_t &mode : reac_modes){

    // TObjArray for the current parameter and mode
    TString objname_recoCC0Pi_CCOth = BuildObjName(mode,"ccother_migration");
    TString objname_recoCC0Pi_CC0Pi = BuildObjName(mode,"cc0pi_migration");
    TString objname_recoCCOth_CCOth = BuildObjName(mode,"ccother_migration");
    TString objname_recoCCOth_CC0Pi = BuildObjName(mode,"cc0pi_migration");

    TObjArray *spline_array_recoCC0Pi_CCOth = new TObjArray();
    TObjArray *spline_array_recoCC0Pi_CC0Pi = new TObjArray();
    TObjArray *spline_array_recoCCOth_CCOth = new TObjArray();
    TObjArray *spline_array_recoCCOth_CC0Pi = new TObjArray();

    spline_array_recoCC0Pi_CCOth->SetName(objname_recoCC0Pi_CCOth.Data());
    spline_array_recoCC0Pi_CC0Pi->SetName(objname_recoCC0Pi_CC0Pi.Data());
    spline_array_recoCCOth_CCOth->SetName(objname_recoCCOth_CCOth.Data());
    spline_array_recoCCOth_CC0Pi->SetName(objname_recoCCOth_CC0Pi.Data());

    for(int itrue = 0; itrue < n_true_bins; itrue++) {
      for(int ireco = 0; ireco < n_reco_bins; ireco++) {
        std::vector<double> x;
        std::vector<double> y_recoCC0Pi_CCOth;
        std::vector<double> y_recoCC0Pi_CC0Pi;
        std::vector<double> y_recoCCOth_CCOth;
        std::vector<double> y_recoCCOth_CC0Pi;

        for(unsigned int k = 0; k < knots.size(); ++k){
          x.push_back(knots.at(k));
          y_recoCC0Pi_CCOth.push_back(knotHistMap_responseCC0Pi_CCOthScaled.at(k)->GetBinContent(itrue+1,ireco+1));
          y_recoCC0Pi_CC0Pi.push_back(knotHistMap_responseCC0Pi_CC0PiScaled.at(k)->GetBinContent(itrue+1,ireco+1));
          y_recoCCOth_CCOth.push_back(knotHistMap_responseCCOth_CCOthScaled.at(k)->GetBinContent(itrue+1,ireco+1));
          y_recoCCOth_CC0Pi.push_back(knotHistMap_responseCCOth_CC0PiScaled.at(k)->GetBinContent(itrue+1,ireco+1));
        }
        assert((x.size() == y_recoCC0Pi_CCOth.size()));
        assert((x.size() == y_recoCC0Pi_CC0Pi.size()));
        assert((x.size() == y_recoCCOth_CCOth.size()));
        assert((x.size() == y_recoCCOth_CC0Pi.size()));
        
        TString name_recoCC0Pi_CCOth = BuildSplineName("numuCC0piNtrk", beam, mode, "ccother_migration", itrue, ireco);
        TString name_recoCC0Pi_CC0Pi = BuildSplineName("numuCC0piNtrk", beam, mode, "cc0pi_migration", itrue, ireco);
        TString name_recoCCOth_CCOth = BuildSplineName("numuCCoth",     beam, mode, "ccother_migration", itrue, ireco);
        TString name_recoCCOth_CC0Pi = BuildSplineName("numuCCoth",     beam, mode, "cc0pi_migration", itrue, ireco);
        
        TSpline3 *spl_recoCC0Pi_CCOth = new TSpline3(name_recoCC0Pi_CCOth.Data(), x.data(), y_recoCC0Pi_CCOth.data(), x.size());
        TSpline3 *spl_recoCC0Pi_CC0Pi = new TSpline3(name_recoCC0Pi_CC0Pi.Data(), x.data(), y_recoCC0Pi_CC0Pi.data(), x.size());
        TSpline3 *spl_recoCCOth_CCOth = new TSpline3(name_recoCCOth_CCOth.Data(), x.data(), y_recoCCOth_CCOth.data(), x.size());
        TSpline3 *spl_recoCCOth_CC0Pi = new TSpline3(name_recoCCOth_CC0Pi.Data(), x.data(), y_recoCCOth_CC0Pi.data(), x.size());
        
        spl_recoCC0Pi_CCOth->SetName(name_recoCC0Pi_CCOth.Data());
        spl_recoCC0Pi_CC0Pi->SetName(name_recoCC0Pi_CC0Pi.Data());
        spl_recoCCOth_CCOth->SetName(name_recoCCOth_CCOth.Data());
        spl_recoCCOth_CC0Pi->SetName(name_recoCCOth_CC0Pi.Data());
        
        spline_array_recoCC0Pi_CCOth->Add(spl_recoCC0Pi_CCOth);
        spline_array_recoCC0Pi_CC0Pi->Add(spl_recoCC0Pi_CC0Pi);
        spline_array_recoCCOth_CCOth->Add(spl_recoCCOth_CCOth);
        spline_array_recoCCOth_CC0Pi->Add(spl_recoCCOth_CC0Pi);
        
        n_splines_written++;
        if (n_splines_written%1000==0) {
          VLOG("valor_sbn",pNOTICE)<<"Written "<<n_splines_written<<" splines so far.";
        }
      } // True bin
    } // Reco bin
    splout_recoCC0Pi_CCOthScaled.cd();
    spline_array_recoCC0Pi_CCOth->Write(objname_recoCC0Pi_CCOth.Data(),TObject::kSingleKey);
    
    splout_recoCC0Pi_CC0PiScaled.cd();
    spline_array_recoCC0Pi_CC0Pi->Write(objname_recoCC0Pi_CC0Pi.Data(),TObject::kSingleKey);
    
    splout_recoCCOth_CCOthScaled.cd();
    spline_array_recoCCOth_CCOth->Write(objname_recoCCOth_CCOth.Data(),TObject::kSingleKey);
    
    splout_recoCCOth_CC0PiScaled.cd();
    spline_array_recoCCOth_CC0Pi->Write(objname_recoCCOth_CC0Pi.Data(),TObject::kSingleKey);
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
std::vector<double> GetBinEdges(const VALORBinning *vb){
  const int n = vb->NBins();
  std::vector<double> edges(n+1,0.);
  for(int i = 0; i < n; ++i){
    edges.at(i) = vb->BinMinimum(i,0);
  }
  edges.at(n) = vb->BinMaximum(n-1,0);
  return edges;
}
//___________________________________________________________________
bool IsCC0Pi(const event::Interaction &truth){
  // If it's not truely CC don't even bother
  if(!truth.neutrino.iscc){
    VLOG("valor_sbn", pDEBUG) << "NC, not 0Pi. Not selecting. ";
    return false;
  }

  // Return false if any pions are found
  for(const event::FinalStateParticle &fsp : truth.finalstate){
    // Final state particles need counting
    if (fsp.status_code != 1) {continue;}
    if(fsp.pdg == genie::kPdgPiP || fsp.pdg == genie::kPdgPiM || fsp.pdg == genie::kPdgPi0) return false;
  }
  VLOG("valor_sbn", pDEBUG) << "CC 0Pi. Selecting. ";
  return true;
}
//___________________________________________________________________
std::shared_ptr<TH2D> GetHistRatio(const std::shared_ptr<TH2D> &num, const std::shared_ptr<TH2D> &den){
  // Clone the numerator
  std::shared_ptr<TH2D> div(static_cast<TH2D*>(num->Clone()));

  // Get the binning
  const unsigned int nBinsX = num->GetNbinsX();
  const unsigned int nBinsY = num->GetNbinsY();

  // Fill the content of the division
  for(unsigned int bX = 1; bX <= nBinsX; ++bX){
    for(unsigned int bY = 1; bY <= nBinsY; ++bY){
      const double numContent = num->GetBinContent(bX,bY);
      const double denContent = den->GetBinContent(bX,bY);

      // If the number of reconstructed events in the bin is < 4, 
      // set the weight to be 1 as this is too few to construct a valid weight
      if(denContent < 4) div->SetBinContent(bX,bY,1);
      else {
        if((numContent/denContent) < 0)
          div->SetBinContent(bX,bY,0);
        else
          div->SetBinContent(bX,bY,(numContent/denContent));

      }
    }
  }
  return div;
}
//___________________________________________________________________
std::shared_ptr<TH1D> Get1DHistFrom2D(const std::shared_ptr<TH2D> &h2D, 
                                      const std::string &name, 
                                      const std::vector<double> &reco_be){ 
  // Get the binning
  const unsigned int nBinsT = h2D->GetNbinsX();
  const unsigned int nBinsR = h2D->GetNbinsY();

  // Sanity
  assert(nBinsR == reco_be.size()-1);

  // Define the flattened 1D histogram
  std::shared_ptr<TH1D> h1D = std::make_shared<TH1D>(name.c_str(), "", nBinsR, reco_be.data());

  // Fill the content of the division
  for(unsigned int bR = 1; bR <= nBinsR; ++bR){
    double recoContent = 0.;
    for(unsigned int bT = 1; bT <= nBinsT; ++bT){
      recoContent += h2D->GetBinContent(bT,bR);
    }
    h1D->SetBinContent(bR, recoContent);
  }
  return h1D;
}
//___________________________________________________________________
void HistFileName(TString           &name,
                  const std::string &s,
                  const BeamConf_t  &b,
                  const Detector_t  &d,
                  const std::string &p){
  SplineFileName(name,s,b,d,p);
  name = name.ReplaceAll(".root","_spectra.root");
}
//___________________________________________________________________
void SplineFileName(TString           &name,
                    const std::string &s,
                    const BeamConf_t  &b,
                    const Detector_t  &d,
                    const std::string &p){
  name = name.ReplaceAll("[BEAM]"  , util::AsString(b).c_str());
  name = name.ReplaceAll("[DET]"   , util::AsString(d).c_str());
  name = name.ReplaceAll("[SAMPLE]", s.c_str());
  name = name.ReplaceAll("[PARAM]" , p.c_str());
}
//___________________________________________________________________
TString BuildSplineName(const std::string &s,
                        const BeamConf_t  &b,
                        const ReacMode_t  &m,
                        const std::string &p,
                        const int         &itrue,
                        const int         &ireco){

  TString name = splineNamePattern;

  name = name.ReplaceAll("[BEAM]"   , util::AsString(b).c_str());
  name = name.ReplaceAll("[SAMPLE]" , s.c_str());

  name = name.ReplaceAll("[MODE]"   , util::AsString(m).c_str());
  name = name.ReplaceAll("[PARAM]"  , p.c_str());

  name = name.ReplaceAll("[TRUE]" , TString::Format("%d", itrue ));
  name = name.ReplaceAll("[RECO]" , TString::Format("%d", ireco ));

  return name;

}
//___________________________________________________________________
TString BuildObjName(const ReacMode_t  &m,
    const std::string &p){

  TString name = objNamePattern;

  name = name.ReplaceAll("[MODE]"   , util::AsString(m).c_str());
  name = name.ReplaceAll("[PARAM]"  , p.c_str());

  return name;

}
