//____________________________________________________________________________
/*!

  \app       valor_sbn-make_mig_splines

  \brief

  \syntax    valor_sbn-make_mig_splines

  \options     --output              : Where to save splines to. [def: valor_splines_[SAMPLE]_[PARAM]_[BEAM].root]
               --input               : input_analysis_file.root
               --config              : Analysis configuration file [required]
               --sample              : Topology [def: numulikeCChigh]
               --detector            : Detector [def: sbn_nd]
               --beam                : Beam [def: BNB_FHC]
               --mesg-thresholds     : Message thresholds [def: "verbosity.xml"]

  \author    Beth Slater
  Rhiannon Jones <rjones@hep.ph.liv,ac,uk>
  University of Liverpool

  \created   March 15th, 2020 - 4/9/24

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
  arg.Read(argc,argv,"$VALOR_EXPT/config/apps/universes.arg:$VALOR_EXPT/config/apps/make_mig_splines.arg");
  VLOG("valor_sbn", pNOTICE) << arg;

  // Get arguments
  string arg_config_file   = arg.GetString("config");
  string arg_output_file   = arg.GetString("output");
  string arg_beam          = arg.GetString("beam");
  string arg_detector      = arg.GetString("detector");

  double arg_bin00         = arg.GetDouble("bin00");
  double arg_bin01         = arg.GetDouble("bin01");
  double arg_bin02         = arg.GetDouble("bin02");
  std::vector<double> bins = {0,arg_bin00,arg_bin01,arg_bin02};

  double arg_factor00         = arg.GetDouble("factor00");
  double arg_factor01         = arg.GetDouble("factor01");
  double arg_factor02         = arg.GetDouble("factor02");
  // From arguments
  string mesg_thresholds = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  string config_file     = util::CompleteConfigPath(arg_config_file);
  BeamConf_t beam        = util::BeamConfFromString (arg_beam    );
  Detector_t detector    = util::DetectorFromString (arg_detector);

  // Message thresholds
  valor::Messenger::Instance()->Configure(mesg_thresholds);

  // Get the POT of the sample from the subrun tree
  double mcsample_pot = -1.;
  /*TChain * subrun_tree = new TChain(gSubRunTreeName.c_str());
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
*/
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
  for(const auto &name : std::vector<std::string>({"trueOA00_recoOA01", 
                                                   "trueOA01_recoOA00",
                                                   "trueOA01_recoOA02",
                                                   "trueOA02_recoOA01",
                                                   "trueOA00",
                                                   "trueOA01",
                                                   "trueOA02",
                                                   "recoOA00",
                                                   "recoOA01",
                                                   "recoOA02"}))
  {
    eventHistogramMap.emplace(name, std::make_shared<TH2D>(name.c_str(), "", true_bin_edges.size()-1, true_bin_edges.data(), reco_bin_edges.size()-1, reco_bin_edges.data()));
  }

  // Now actually assign the histograms
  auto & trueOA00_recoOA01 = eventHistogramMap.at("trueOA00_recoOA01");
  auto & trueOA01_recoOA00 = eventHistogramMap.at("trueOA01_recoOA00");
  auto & trueOA01_recoOA02 = eventHistogramMap.at("trueOA01_recoOA02");
  auto & trueOA02_recoOA01 = eventHistogramMap.at("trueOA02_recoOA01");
  auto & trueOA00          = eventHistogramMap.at("trueOA00");
  auto & trueOA01          = eventHistogramMap.at("trueOA01");
  auto & trueOA02          = eventHistogramMap.at("trueOA02");
  auto & recoOA00          = eventHistogramMap.at("recoOA00");
  auto & recoOA01          = eventHistogramMap.at("recoOA01");
  auto & recoOA02          = eventHistogramMap.at("recoOA02");
  //Read DST to get true/shifted(reco) OAA values
  
  TTree* dst_in = gmodel->GetDST();
  Long64_t nev = dst_in->GetEntries();
  //dst in is overall 0-1.6 one, before it's split
  //just need to loop over each event and take the true oaa and shifted oaa adn plug them into prism bin definitions
  //have bin boundaries be an input
  //need to change prism dst maker to explicitly not double count boundary events
  for(Long64_t iev = 0; iev < nev; iev++){

    dst_in->GetEntry(iev);

    double e_true;
    double e_reco;
    double weight;
    double oa_true;
    double oa_reco;
    dst_in->SetBranchAddress("enu_true", &e_true);
    dst_in->SetBranchAddress("enu_reco", &e_reco);
    dst_in->SetBranchAddress("wght", &weight);
    dst_in->SetBranchAddress("offaxis_true", &oa_true);
    dst_in->SetBranchAddress("offaxis_shift", &oa_reco);

    if(iev == 0) dst_in->SetBranchAddress("wght_pot", &mcsample_pot);

    if(oa_true >= bins[0] && oa_true < bins[1]){
      trueOA00->Fill(e_true,e_reco,weight);
      if(oa_reco >= bins[1] && oa_reco < bins[2]) trueOA00_recoOA01->Fill(e_true,e_reco,weight);
    }
    if(oa_true >= bins[1] && oa_true < bins[2]){
      trueOA01->Fill(e_true,e_reco,weight);
      if(oa_reco >= bins[0] && oa_reco < bins[1]) trueOA01_recoOA00->Fill(e_true,e_reco,weight);
      if(oa_reco >= bins[2] && oa_reco < bins[3]) trueOA01_recoOA02->Fill(e_true,e_reco,weight);
    }
    if(oa_true >= bins[2] && oa_true < bins[3]){
      trueOA02->Fill(e_true,e_reco,weight);
      if(oa_reco >= bins[1] && oa_reco < bins[2]) trueOA02_recoOA01->Fill(e_true,e_reco,weight);
    }
    if(oa_reco >= bins[0] && oa_reco < bins[1]) recoOA00->Fill(e_true,e_reco,weight);
    if(oa_reco >= bins[1] && oa_reco < bins[2]) recoOA01->Fill(e_true,e_reco,weight);
    if(oa_reco >= bins[2] && oa_reco < bins[3]) recoOA02->Fill(e_true,e_reco,weight);
	  
  } //events

  /*// Read the SBNCode input file
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
  }// Events*/

  // Filename for is we choose to store the spectra
  TString hist_outfile_recoOA00_OA00Scaled = arg_output_file.c_str();
  TString hist_outfile_recoOA00_OA01Scaled = arg_output_file.c_str();
  TString hist_outfile_recoOA01_OA00Scaled = arg_output_file.c_str();
  TString hist_outfile_recoOA01_OA01Scaled = arg_output_file.c_str();
  TString hist_outfile_recoOA01_OA02Scaled = arg_output_file.c_str();
  TString hist_outfile_recoOA02_OA01Scaled = arg_output_file.c_str();
  TString hist_outfile_recoOA02_OA02Scaled = arg_output_file.c_str();

  HistFileName(hist_outfile_recoOA00_OA00Scaled, "numuCCinclOA00", beam, detector, "OA00_migration");
  HistFileName(hist_outfile_recoOA00_OA01Scaled, "numuCCinclOA00", beam, detector, "OA01_migration");
  HistFileName(hist_outfile_recoOA01_OA00Scaled, "numuCCinclOA01", beam, detector, "OA00_migration");
  HistFileName(hist_outfile_recoOA01_OA01Scaled, "numuCCinclOA01", beam, detector, "OA01_migration");
  HistFileName(hist_outfile_recoOA01_OA02Scaled, "numuCCinclOA01", beam, detector, "OA02_migration");
  HistFileName(hist_outfile_recoOA02_OA01Scaled, "numuCCinclOA02", beam, detector, "OA01_migration");
  HistFileName(hist_outfile_recoOA02_OA02Scaled, "numuCCinclOA02", beam, detector, "OA02_migration");

  TFile histout_recoOA00_OA00Scaled(hist_outfile_recoOA00_OA00Scaled, "RECREATE");
  TFile histout_recoOA00_OA01Scaled(hist_outfile_recoOA00_OA01Scaled, "RECREATE");
  TFile histout_recoOA01_OA00Scaled(hist_outfile_recoOA01_OA00Scaled, "RECREATE");
  TFile histout_recoOA01_OA01Scaled(hist_outfile_recoOA01_OA01Scaled, "RECREATE");
  TFile histout_recoOA01_OA02Scaled(hist_outfile_recoOA01_OA02Scaled, "RECREATE");
  TFile histout_recoOA02_OA01Scaled(hist_outfile_recoOA02_OA01Scaled, "RECREATE");
  TFile histout_recoOA02_OA02Scaled(hist_outfile_recoOA02_OA02Scaled, "RECREATE");

  // Scale to POT
  double scalePOT = nomPOT*static_cast<double>(mcsample_pot); //mcsample_pot from dst is 1/totgoodpot so * not / here
  VLOG("valor_sbn",pNOTICE) << "Scaling histograms by: " << scalePOT
                            << "\nfrom nominal:        " << nomPOT
                            << "\n and sample:         " << mcsample_pot;
  // Loop over the knots
  const std::vector<double> knots({-3.0,-2.0,-1.0,0.0,1.0,2.0,3.0});
  std::map< unsigned int, std::shared_ptr<TH2D> > knotHistMap_responseOA00_OA00Scaled;
  std::map< unsigned int, std::shared_ptr<TH2D> > knotHistMap_responseOA00_OA01Scaled;
  std::map< unsigned int, std::shared_ptr<TH2D> > knotHistMap_responseOA01_OA00Scaled;
  std::map< unsigned int, std::shared_ptr<TH2D> > knotHistMap_responseOA01_OA01Scaled;
  std::map< unsigned int, std::shared_ptr<TH2D> > knotHistMap_responseOA01_OA02Scaled;
  std::map< unsigned int, std::shared_ptr<TH2D> > knotHistMap_responseOA02_OA01Scaled;
  std::map< unsigned int, std::shared_ptr<TH2D> > knotHistMap_responseOA02_OA02Scaled;
  unsigned int knIt = 0;
  
  //define factor for prior uncertainty
  //factor=kn*N_reco0X,scaled/N_true_0X
  //N_reco00,scaled = N_reco00
/*  double N_true00_reco01 = trueOA00_recoOA01->Integral();
  double N_true01_reco00 = trueOA01_recoOA00->Integral();
  double N_true01_reco02 = trueOA01_recoOA02->Integral();
  double N_true02_reco01 = trueOA02_recoOA01->Integral();
  double N_recoOA00_scaled = recoOA00->Integral() + N_true01_reco00 - N_true00_reco01;
  double N_recoOA01_scaled = recoOA01->Integral() + N_true00_reco01 + N_true02_reco01 - N_true01_reco00 - N_true01_reco02;
  double N_recoOA02_scaled = recoOA02->Integral() + N_true01_reco02 - N_true02_reco01;
  double N_true00 = trueOA00->Integral();
  double N_true01 = trueOA01->Integral();
  double N_true02 = trueOA02->Integral();
*/
  for(const double &kn : knots){
    // The number of OA01 events in the OA00 sample is trueOA01_recoOA00, 
    // This defines the 'nominal' amount of OA01->OA00 migration
    // To define a nsigma variation, scale this migration by (1+kn) (100% uncertainty)
    //
    // The number of extra events to add to the OA00 sample is: trueOA01_recoOA00*(kn)
    // So we need to subtract these events away from the reco OA01 sample to balance it
    //
    // Define the magnitude by which to scale the migration to account for the prior 
    // uncertainty, default: 100% = 1*(knot value)
    /*double factor00 = (N_recoOA00_scaled/N_true00)*kn;
    double factor01 = (N_recoOA01_scaled/N_true01)*kn;
    double factor02 = (N_recoOA02_scaled/N_true02)*kn;*/
    double f00 = arg_factor00;
    double f01 = arg_factor01;
    double f02 = arg_factor02;
    //double f00 = 0.5;
    //double f01 = 0.5;
    //double f02 = 0.5;
    double F00 = f00*kn;
    double F01 = f01*kn;
    double F02 = f02*kn;

    //OA01->OA00
    std::shared_ptr<TH2D> diffOA01_00(static_cast<TH2D*>(trueOA01_recoOA00->Clone()));
    diffOA01_00->Scale(F01);
   
    std::shared_ptr<TH2D> recoOA00_OA01Scaled(static_cast<TH2D*>(recoOA00->Clone()));
    recoOA00_OA01Scaled->Add(diffOA01_00.get());
    
    std::shared_ptr<TH2D> recoOA01_OA01Scaled(static_cast<TH2D*>(recoOA01->Clone()));
    recoOA01_OA01Scaled->Add(diffOA01_00.get(),-1.);


    //OA01->OA02
    std::shared_ptr<TH2D> diffOA01_02(static_cast<TH2D*>(trueOA01_recoOA02->Clone()));
    diffOA01_02->Scale(F01);
   
    std::shared_ptr<TH2D> recoOA02_OA01Scaled(static_cast<TH2D*>(recoOA02->Clone()));
    recoOA02_OA01Scaled->Add(diffOA01_02.get());

    recoOA01_OA01Scaled->Add(diffOA01_02.get(),-1.);


    //OA00->OA01
    std::shared_ptr<TH2D> diffOA00_01(static_cast<TH2D*>(trueOA00_recoOA01->Clone()));
    diffOA00_01->Scale(F00);
   
    std::shared_ptr<TH2D> recoOA01_OA00Scaled(static_cast<TH2D*>(recoOA01->Clone()));
    recoOA01_OA00Scaled->Add(diffOA00_01.get());
    
    std::shared_ptr<TH2D> recoOA00_OA00Scaled(static_cast<TH2D*>(recoOA00->Clone()));
    recoOA00_OA00Scaled->Add(diffOA00_01.get(),-1.);


    //OA02->OA01
    std::shared_ptr<TH2D> diffOA02_01(static_cast<TH2D*>(trueOA02_recoOA01->Clone()));
    diffOA02_01->Scale(F02);
   
    std::shared_ptr<TH2D> recoOA02_OA02Scaled(static_cast<TH2D*>(recoOA02->Clone()));
    recoOA02_OA02Scaled->Add(diffOA02_01.get());
    
    std::shared_ptr<TH2D> recoOA01_OA02Scaled(static_cast<TH2D*>(recoOA01->Clone()));
    recoOA01_OA02Scaled->Add(diffOA02_01.get(),-1.);
  
    // Now get the ratio of the scaled event rate to the total number of reconstructed events of the relevant type
    const std::shared_ptr<TH2D> responseOA00_OA00Scaled = GetHistRatio(recoOA00_OA00Scaled, recoOA00);
    const std::shared_ptr<TH2D> responseOA00_OA01Scaled = GetHistRatio(recoOA00_OA01Scaled, recoOA00);
    const std::shared_ptr<TH2D> responseOA01_OA00Scaled = GetHistRatio(recoOA01_OA00Scaled, recoOA01);
    const std::shared_ptr<TH2D> responseOA01_OA01Scaled = GetHistRatio(recoOA01_OA01Scaled, recoOA01);
    const std::shared_ptr<TH2D> responseOA01_OA02Scaled = GetHistRatio(recoOA01_OA02Scaled, recoOA01);
    const std::shared_ptr<TH2D> responseOA02_OA01Scaled = GetHistRatio(recoOA02_OA01Scaled, recoOA02);
    const std::shared_ptr<TH2D> responseOA02_OA02Scaled = GetHistRatio(recoOA02_OA02Scaled, recoOA02);

    // Now push to the relevant map
    knotHistMap_responseOA00_OA00Scaled.emplace(knIt,responseOA00_OA00Scaled);
    knotHistMap_responseOA00_OA01Scaled.emplace(knIt,responseOA00_OA01Scaled);
    knotHistMap_responseOA01_OA00Scaled.emplace(knIt,responseOA01_OA00Scaled);
    knotHistMap_responseOA01_OA01Scaled.emplace(knIt,responseOA01_OA01Scaled);
    knotHistMap_responseOA01_OA02Scaled.emplace(knIt,responseOA01_OA02Scaled);
    knotHistMap_responseOA02_OA01Scaled.emplace(knIt,responseOA02_OA01Scaled);
    knotHistMap_responseOA02_OA02Scaled.emplace(knIt,responseOA02_OA02Scaled);
    knIt++;

    // Now flatten the 4 scaled histograms (by integrating out the true bins) 
    // Print to a file for validation with the relevant sample and parameter name
    const int knotInt = std::round(kn);
    const std::string name_1D = "h_reco_" + (knotInt == 0 ? "nom" : (( knotInt > 0 ? "p" : "m" ) + std::to_string(std::abs(knotInt))));

    histout_recoOA00_OA00Scaled.cd();
    const std::shared_ptr<TH1D> recoOA00_OA00Scaled_1D = Get1DHistFrom2D(recoOA00_OA00Scaled, name_1D, reco_bin_edges);
    recoOA00_OA00Scaled_1D->Scale(scalePOT);
    recoOA00_OA00Scaled_1D->Write();

    histout_recoOA00_OA01Scaled.cd();
    const std::shared_ptr<TH1D> recoOA00_OA01Scaled_1D = Get1DHistFrom2D(recoOA00_OA01Scaled, name_1D, reco_bin_edges);
    recoOA00_OA01Scaled_1D->Scale(scalePOT);
    recoOA00_OA01Scaled_1D->Write();

    histout_recoOA01_OA00Scaled.cd();
    const std::shared_ptr<TH1D> recoOA01_OA00Scaled_1D = Get1DHistFrom2D(recoOA01_OA00Scaled, name_1D, reco_bin_edges);
    recoOA01_OA00Scaled_1D->Scale(scalePOT);
    recoOA01_OA00Scaled_1D->Write();

    histout_recoOA01_OA01Scaled.cd();
    const std::shared_ptr<TH1D> recoOA01_OA01Scaled_1D = Get1DHistFrom2D(recoOA01_OA01Scaled, name_1D, reco_bin_edges);
    recoOA01_OA01Scaled_1D->Scale(scalePOT);
    recoOA01_OA01Scaled_1D->Write();

    histout_recoOA01_OA02Scaled.cd();
    const std::shared_ptr<TH1D> recoOA01_OA02Scaled_1D = Get1DHistFrom2D(recoOA01_OA02Scaled, name_1D, reco_bin_edges);
    recoOA01_OA02Scaled_1D->Scale(scalePOT);
    recoOA01_OA02Scaled_1D->Write();

    histout_recoOA02_OA01Scaled.cd();
    const std::shared_ptr<TH1D> recoOA02_OA01Scaled_1D = Get1DHistFrom2D(recoOA02_OA01Scaled, name_1D, reco_bin_edges);
    recoOA02_OA01Scaled_1D->Scale(scalePOT);
    recoOA02_OA01Scaled_1D->Write();

    histout_recoOA02_OA02Scaled.cd();
    const std::shared_ptr<TH1D> recoOA02_OA02Scaled_1D = Get1DHistFrom2D(recoOA02_OA02Scaled, name_1D, reco_bin_edges);
    recoOA02_OA02Scaled_1D->Scale(scalePOT);
    recoOA02_OA02Scaled_1D->Write();

  }
  VLOG("valor_sbn", pNOTICE) << "Filled and written histogram files";

  // Now define the spline files
  TString spl_outfile_recoOA00_OA00Scaled = arg_output_file.c_str();
  TString spl_outfile_recoOA00_OA01Scaled = arg_output_file.c_str();
  TString spl_outfile_recoOA01_OA00Scaled = arg_output_file.c_str();
  TString spl_outfile_recoOA01_OA01Scaled = arg_output_file.c_str();
  TString spl_outfile_recoOA01_OA02Scaled = arg_output_file.c_str();
  TString spl_outfile_recoOA02_OA01Scaled = arg_output_file.c_str();
  TString spl_outfile_recoOA02_OA02Scaled = arg_output_file.c_str();

  //SplineFileName(spl_outfile_recoCCInc_CCOthScaled, "numuCCincl", beam, detector, "ccother_migration");
  //SplineFileName(spl_outfile_recoCCInc_CC0PiScaled, "numuCCincl", beam, detector, "cc0pi_migration");
  SplineFileName(spl_outfile_recoOA00_OA00Scaled, "numuCCinclOA00", beam, detector, "OA00_migration");
  SplineFileName(spl_outfile_recoOA00_OA01Scaled, "numuCCinclOA00", beam, detector, "OA01_migration");
  SplineFileName(spl_outfile_recoOA01_OA00Scaled, "numuCCinclOA01", beam, detector, "OA00_migration");
  SplineFileName(spl_outfile_recoOA01_OA01Scaled, "numuCCinclOA01", beam, detector, "OA01_migration");
  SplineFileName(spl_outfile_recoOA01_OA02Scaled, "numuCCinclOA01", beam, detector, "OA02_migration");
  SplineFileName(spl_outfile_recoOA02_OA01Scaled, "numuCCinclOA02", beam, detector, "OA01_migration");
  SplineFileName(spl_outfile_recoOA02_OA02Scaled, "numuCCinclOA02", beam, detector, "OA02_migration");

  //TFile splout_recoCCInc_CCOthScaled(spl_outfile_recoCCInc_CCOthScaled, "RECREATE");
  //TFile splout_recoCCInc_CC0PiScaled(spl_outfile_recoCCInc_CC0PiScaled, "RECREATE");
  TFile splout_recoOA00_OA00Scaled(spl_outfile_recoOA00_OA00Scaled, "RECREATE");
  TFile splout_recoOA00_OA01Scaled(spl_outfile_recoOA00_OA01Scaled, "RECREATE");
  TFile splout_recoOA01_OA00Scaled(spl_outfile_recoOA01_OA00Scaled, "RECREATE");
  TFile splout_recoOA01_OA01Scaled(spl_outfile_recoOA01_OA01Scaled, "RECREATE");
  TFile splout_recoOA01_OA02Scaled(spl_outfile_recoOA01_OA02Scaled, "RECREATE");
  TFile splout_recoOA02_OA01Scaled(spl_outfile_recoOA02_OA01Scaled, "RECREATE");
  TFile splout_recoOA02_OA02Scaled(spl_outfile_recoOA02_OA02Scaled, "RECREATE");
  
  int n_splines_written = 0;
  for(const ReacMode_t &mode : reac_modes){

    // TObjArray for the current parameter and mode
    //TString objname_recoCCInc_CCOth = BuildObjName(mode,"ccother_migration");
    //TString objname_recoCCInc_CC0Pi = BuildObjName(mode,"cc0pi_migration");
    TString objname_recoOA00_OA00 = BuildObjName(mode,"OA00_migration");
    TString objname_recoOA00_OA01 = BuildObjName(mode,"OA01_migration");
    TString objname_recoOA01_OA00 = BuildObjName(mode,"OA00_migration");
    TString objname_recoOA01_OA01 = BuildObjName(mode,"OA01_migration");
    TString objname_recoOA01_OA02 = BuildObjName(mode,"OA02_migration");
    TString objname_recoOA02_OA01 = BuildObjName(mode,"OA01_migration");
    TString objname_recoOA02_OA02 = BuildObjName(mode,"OA02_migration");

    //TObjArray *spline_array_recoCCInc_CC0Pi = new TObjArray();
    //TObjArray *spline_array_recoCCInc_CCOth = new TObjArray();
    TObjArray *spline_array_recoOA00_OA00 = new TObjArray();
    TObjArray *spline_array_recoOA00_OA01 = new TObjArray();
    TObjArray *spline_array_recoOA01_OA00 = new TObjArray();
    TObjArray *spline_array_recoOA01_OA01 = new TObjArray();
    TObjArray *spline_array_recoOA01_OA02 = new TObjArray();
    TObjArray *spline_array_recoOA02_OA01 = new TObjArray();
    TObjArray *spline_array_recoOA02_OA02 = new TObjArray();

    //spline_array_recoCCInc_CCOth->SetName(objname_recoCCInc_CCOth.Data());
    //spline_array_recoCCInc_CC0Pi->SetName(objname_recoCCInc_CC0Pi.Data());
    spline_array_recoOA00_OA00->SetName(objname_recoOA00_OA00.Data());
    spline_array_recoOA00_OA01->SetName(objname_recoOA00_OA01.Data());
    spline_array_recoOA01_OA00->SetName(objname_recoOA01_OA00.Data());
    spline_array_recoOA01_OA01->SetName(objname_recoOA01_OA01.Data());
    spline_array_recoOA01_OA02->SetName(objname_recoOA01_OA02.Data());
    spline_array_recoOA02_OA01->SetName(objname_recoOA02_OA01.Data());
    spline_array_recoOA02_OA02->SetName(objname_recoOA02_OA02.Data());

    for(int itrue = 0; itrue < n_true_bins; itrue++) {
      for(int ireco = 0; ireco < n_reco_bins; ireco++) {
        std::vector<double> x;
        std::vector<double> y_recoOA00_OA00;
        std::vector<double> y_recoOA00_OA01;
        std::vector<double> y_recoOA01_OA00;
        std::vector<double> y_recoOA01_OA01;
        std::vector<double> y_recoOA01_OA02;
        std::vector<double> y_recoOA02_OA01;
        std::vector<double> y_recoOA02_OA02;
        // Inclusive for downstream analyses: These splines are flat
        //std::vector<double> y_recoCCInc_CCOth;
        //std::vector<double> y_recoCCInc_CC0Pi;

        for(unsigned int k = 0; k < knots.size(); ++k){
          x.push_back(knots.at(k));
          //y_recoCCInc_CCOth.push_back(1);
          //y_recoCCInc_CC0Pi.push_back(1);
          y_recoOA00_OA00.push_back(knotHistMap_responseOA00_OA00Scaled.at(k)->GetBinContent(itrue+1,ireco+1));
          y_recoOA00_OA01.push_back(knotHistMap_responseOA00_OA01Scaled.at(k)->GetBinContent(itrue+1,ireco+1));
          y_recoOA01_OA00.push_back(knotHistMap_responseOA01_OA00Scaled.at(k)->GetBinContent(itrue+1,ireco+1));
          y_recoOA01_OA01.push_back(knotHistMap_responseOA01_OA01Scaled.at(k)->GetBinContent(itrue+1,ireco+1));
          y_recoOA01_OA02.push_back(knotHistMap_responseOA01_OA02Scaled.at(k)->GetBinContent(itrue+1,ireco+1));
          y_recoOA02_OA01.push_back(knotHistMap_responseOA02_OA01Scaled.at(k)->GetBinContent(itrue+1,ireco+1));
          y_recoOA02_OA02.push_back(knotHistMap_responseOA02_OA02Scaled.at(k)->GetBinContent(itrue+1,ireco+1));
        }
        assert((x.size() == y_recoOA00_OA00.size()));
        assert((x.size() == y_recoOA00_OA01.size()));
        assert((x.size() == y_recoOA01_OA00.size()));
        assert((x.size() == y_recoOA01_OA01.size()));
        assert((x.size() == y_recoOA01_OA02.size()));
        assert((x.size() == y_recoOA02_OA01.size()));
        assert((x.size() == y_recoOA02_OA02.size()));
        //assert((x.size() == y_recoCCInc_CC0Pi.size()));
        //assert((x.size() == y_recoCCInc_CCOth.size()));
        
        //TString name_recoCCInc_CCOth = BuildSplineName("numuCCincl",    beam, mode, "ccother_migration", itrue, ireco);
        //TString name_recoCCInc_CC0Pi = BuildSplineName("numuCCincl",    beam, mode, "cc0pi_migration", itrue, ireco);
        TString name_recoOA00_OA00 = BuildSplineName("numuCCinclOA00", beam, mode, "OA00_migration", itrue, ireco);
        TString name_recoOA00_OA01 = BuildSplineName("numuCCinclOA00", beam, mode, "OA01_migration", itrue, ireco);
        TString name_recoOA01_OA00 = BuildSplineName("numuCCinclOA01", beam, mode, "OA00_migration", itrue, ireco);
        TString name_recoOA01_OA01 = BuildSplineName("numuCCinclOA01", beam, mode, "OA01_migration", itrue, ireco);
        TString name_recoOA01_OA02 = BuildSplineName("numuCCinclOA01", beam, mode, "OA02_migration", itrue, ireco);
        TString name_recoOA02_OA01 = BuildSplineName("numuCCinclOA02", beam, mode, "OA01_migration", itrue, ireco);
        TString name_recoOA02_OA02 = BuildSplineName("numuCCinclOA02", beam, mode, "OA02_migration", itrue, ireco);
        
        //TSpline3 *spl_recoCCInc_CCOth = new TSpline3(name_recoCCInc_CCOth.Data(), x.data(), y_recoCCInc_CCOth.data(), x.size());
        //TSpline3 *spl_recoCCInc_CC0Pi = new TSpline3(name_recoCCInc_CC0Pi.Data(), x.data(), y_recoCCInc_CC0Pi.data(), x.size());
        TSpline3 *spl_recoOA00_OA00 = new TSpline3(name_recoOA00_OA00.Data(), x.data(), y_recoOA00_OA00.data(), x.size());
        TSpline3 *spl_recoOA00_OA01 = new TSpline3(name_recoOA00_OA01.Data(), x.data(), y_recoOA00_OA01.data(), x.size());
        TSpline3 *spl_recoOA01_OA00 = new TSpline3(name_recoOA00_OA00.Data(), x.data(), y_recoOA01_OA00.data(), x.size());
        TSpline3 *spl_recoOA01_OA01 = new TSpline3(name_recoOA01_OA01.Data(), x.data(), y_recoOA01_OA01.data(), x.size());
        TSpline3 *spl_recoOA01_OA02 = new TSpline3(name_recoOA01_OA02.Data(), x.data(), y_recoOA01_OA02.data(), x.size());
        TSpline3 *spl_recoOA02_OA01 = new TSpline3(name_recoOA02_OA01.Data(), x.data(), y_recoOA02_OA01.data(), x.size());
        TSpline3 *spl_recoOA02_OA02 = new TSpline3(name_recoOA02_OA02.Data(), x.data(), y_recoOA02_OA02.data(), x.size());
        
        //spl_recoCCInc_CCOth->SetName(name_recoCCInc_CCOth.Data());
        //spl_recoCCInc_CC0Pi->SetName(name_recoCCInc_CC0Pi.Data());
        spl_recoOA00_OA00->SetName(name_recoOA00_OA00.Data());
        spl_recoOA00_OA01->SetName(name_recoOA00_OA01.Data());
        spl_recoOA01_OA00->SetName(name_recoOA01_OA00.Data());
        spl_recoOA01_OA01->SetName(name_recoOA01_OA01.Data());
        spl_recoOA01_OA02->SetName(name_recoOA01_OA02.Data());
        spl_recoOA02_OA01->SetName(name_recoOA02_OA01.Data());
        spl_recoOA02_OA02->SetName(name_recoOA02_OA02.Data());
        
        //spline_array_recoCCInc_CCOth->Add(spl_recoCCInc_CCOth);
        //spline_array_recoCCInc_CC0Pi->Add(spl_recoCCInc_CC0Pi);
        spline_array_recoOA00_OA00->Add(spl_recoOA00_OA00);
        spline_array_recoOA00_OA01->Add(spl_recoOA00_OA01);
        spline_array_recoOA01_OA00->Add(spl_recoOA01_OA00);
        spline_array_recoOA01_OA01->Add(spl_recoOA01_OA01);
        spline_array_recoOA01_OA02->Add(spl_recoOA01_OA02);
        spline_array_recoOA02_OA01->Add(spl_recoOA02_OA01);
        spline_array_recoOA02_OA02->Add(spl_recoOA02_OA02);
        
        n_splines_written++;
        if (n_splines_written%1000==0) {
          VLOG("valor_sbn",pNOTICE)<<"Written "<<n_splines_written<<" splines so far.";
        }
      } // True bin
    } // Reco bin
    /*splout_recoCCInc_CCOthScaled.cd();
    spline_array_recoCCInc_CCOth->Write(objname_recoCCInc_CCOth.Data(),TObject::kSingleKey);
    
    splout_recoCCInc_CC0PiScaled.cd();
    spline_array_recoCCInc_CC0Pi->Write(objname_recoCCInc_CC0Pi.Data(),TObject::kSingleKey);
    */
    splout_recoOA00_OA00Scaled.cd();
    spline_array_recoOA00_OA00->Write(objname_recoOA00_OA00.Data(),TObject::kSingleKey);
    
    splout_recoOA00_OA01Scaled.cd();
    spline_array_recoOA00_OA01->Write(objname_recoOA00_OA01.Data(),TObject::kSingleKey);
    
    splout_recoOA01_OA00Scaled.cd();
    spline_array_recoOA01_OA00->Write(objname_recoOA01_OA00.Data(),TObject::kSingleKey);
    
    splout_recoOA01_OA01Scaled.cd();
    spline_array_recoOA01_OA01->Write(objname_recoOA01_OA01.Data(),TObject::kSingleKey);
    
    splout_recoOA01_OA02Scaled.cd();
    spline_array_recoOA01_OA02->Write(objname_recoOA01_OA02.Data(),TObject::kSingleKey);
    
    splout_recoOA02_OA01Scaled.cd();
    spline_array_recoOA02_OA01->Write(objname_recoOA02_OA01.Data(),TObject::kSingleKey);
    
    splout_recoOA02_OA02Scaled.cd();
    spline_array_recoOA02_OA02->Write(objname_recoOA02_OA02.Data(),TObject::kSingleKey);
    
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
