//____________________________________________________________________________
/*!

\app       valor_dune-universe_variation_tweaks

\brief     Vary the MC spectra by throwing sets of systematics

\options     --output              : Where to save tweaked histograms to. [def: tweaks_[PARAMS].root]
             --input               : Input DST file [required]
             --params              : Parameters to tweak - to name the output file [def: allsyst]
             --sample              : Topology [def: numulikeCChigh]
             --detector            : Detector [def: sbn_nd]
             --kinevar             : Kinematic paramter to parameterise in [def: ereco]
             --ntoys               : Number of toy-MC experiments [def: 1000]
             --config              : Analysis configuration file [required]
             --mesg-thresholds     : Message thresholds [def: "verbosity.xml"]
             

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory
           Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

\created   October 2016

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________
// cpp
#include <stdlib.h>

// root
#include "TCanvas.h"
#include "TFile.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TMath.h"
#include "TObjArray.h"
#include "TString.h"
#include "TSystem.h"
// fmwk
#include "valor/Conventions/Opt.h"
#include "valor/CmdLine/CmdLnArgList.h"
#include "valor/FitCore/CorrelatedSystematics.h"
#include "valor/FitCore/PhysParamList.h"
#include "valor/FitCore/FitParamList.h"
#include "valor/FitCore/FitModelABC.h"
#include "valor/FitCore/FitDataABC.h"
#include "valor/FitCore/FitInputs.h"
#include "valor/FitCore/FitterABC.h"
#include "valor/FitCore/UtlFit.h"
#include "valor/FitCore/CompoundFitElements.h"
#include "valor/FitCore/SingleSampleFitModelABC.h"
#include "valor/FitCore/UtlFitParamList.h"
#include "valor/Utilities/OscParamValues.h"
#include "valor/Utilities/UtlStyle.h"
#include "valor/Utilities/UtlStr.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Utilities/Rnd.h"
#include "valor/Utilities/Env.h"
#include "valor/Utilities/VThreadPool.h"
#include "valor/Utilities/UtlParam.h"
#include "valor/Utilities/SingleSampleKineBinning.h"
#include "valor/Messenger/Messenger.h"
#include "valor/Ntuple/StdFitNtp.h"
#include "valor/FitElements/GenericSingleSampleFitModel.h"
#include "valor/KineBinning/UtlBinning.h"

std::vector<std::string> xsec = 
{  "genie_ccresAxial_Genie",
   "genie_ncresAxial_Genie",
   "genie_qema_Genie",
   "genie_NC_Genie",
   "genie_NonResRvbarp1pi_Genie",
   "genie_NonResRvbarp2pi_Genie",
   "genie_NonResRvp1pi_Genie",
   "genie_NonResRvp2pi_Genie"
};
std::vector<std::string> flux_uncorr = 
{  "expskin_FluxUnisim",
   "horncurrent_FluxUnisim",
   "nucleoninexsec_FluxUnisim",
   "nucleonqexsec_FluxUnisim",
   "nucleontotxsec_FluxUnisim",
   "pioninexsec_FluxUnisim",
   "pionqexsec_FluxUnisim",
   "piontotxsec_FluxUnisim"
};
std::vector<std::string> flux_corr = 
{  "kminus_PrimaryHadronNormalization",
   "piminus_PrimaryHadronSWCentralSplineVariation",
   "kplus_PrimaryHadronFeynmanScaling",
   "piplus_PrimaryHadronSWCentralSplineVariation",
   "kzero_PrimaryHadronSanfordWang"
};
std::vector<std::string> piplus = 
{  
   "piplus_PrimaryHadronSWCentralSplineVariation"
};

std::vector<std::string> xsec_short = 
{  "ccresAxial",
   "ncresAxial",
   "qema",
   "NC",
   "NonResRvbarp1pi",
   "NonResRvbarp2pi",
   "NonResRvp1pi",
   "NonResRvp2pi"
};
std::vector<std::string> flux_uncorr_short = 
{  "expskin",
   "horncurrent",
   "nucleoninexsec",
   "nucleonqexsec",
   "nucleontotxsec",
   "pioninexsec",
   "pionqexsec",
   "piontotxsec"
};
std::vector<std::string> flux_corr_short = 
{  "kminus",
   "piminus",
   "kplus",
   "piplus",
   "kzero"
};
std::vector<std::string> piplus_short = 
{  
   "piplus"
};

double enu_reco_max = 10.;

using namespace std;
using namespace valor;
using namespace valor::conv;

int main(int argc, char ** argv)
{
  time_t scriptstartrawtime;
  struct tm * scriptstarttimeinfo;
  time (&scriptstartrawtime);
  scriptstarttimeinfo = localtime (&scriptstartrawtime);
  std::cout << "-----------------------------------------------------------" << std::endl;
  std::cout << " Script start local time and date:  " << asctime(scriptstarttimeinfo);
  std::cout << "-----------------------------------------------------------" << std::endl;


  valor::util::PrintBanner(Env::Instance()->Banner(),500);
 
  CmdLnArgList arg;
  arg.Read(argc,argv,"$VALOR_EXPT/config/apps/universe_variation_tweaks.arg");
  LOG("universe_variation_tweaks", pNOTICE) << arg;
  
  // Read and iterpret the command line
  int ntoys               = arg.GetInt("ntoys");
  string config_file      = arg.GetString("config");
  string input_rootfile   = arg.GetString("input");
  string input_var_file   = arg.GetString("variations");
  string output_rootfile  = arg.GetString("output");
  string params_to_tweak  = arg.GetString("params");
  string mesg_thresholds  = arg.GetString("mesg-thresholds");
  string arg_sample       = arg.GetString("sample");
  string arg_detector     = arg.GetString("detector");
  string arg_kine_var     = arg.GetString("kine-var");
  
  Messenger::Instance()->Configure(util::CompleteConfigPath(mesg_thresholds));
  LOG("universe_variation_tweaks", pNOTICE) << *Rnd::Instance();
  
  Sample_t   sample       = util::SampleFromString(arg_sample);
  Detector_t detector     = util::DetectorFromString(arg_detector);

  std::string elem_readopt("nomc nosplines");
  CompoundFitElements * elements = new CompoundFitElements();
  elements->Read(util::CompleteConfigPath(config_file),elem_readopt.c_str());
  FitModelABC * model = elements->FitModel();
  CompoundFitModel * cm = dynamic_cast<CompoundFitModel*>(model);
  assert(cm);
  
  GenericSingleSampleFitModel * gmodel = 0;
  bool got_appropriate_model = false;
  for(unsigned int imodel = 0; imodel < cm->GetNSubModels(); imodel++) {
    gmodel = dynamic_cast<GenericSingleSampleFitModel*>(cm->GetSubModel(imodel));
    if  (gmodel->GetDetector() == detector && 
         gmodel->GetSample()   == sample) 
      { got_appropriate_model = true; break; }
  }
  if (!got_appropriate_model) {
    LOG("universe_variation_tweaks", pFATAL) << "Failed to identify appropriate fit model to get binning.";
  }
  LOG("universe_variation_tweaks", pINFO) << " Successfully accessed the relevant model for binning information";
  
  std::vector<std::string> systematics, file_systematics;
  if (params_to_tweak == "int") {
    systematics      = xsec;
    file_systematics = xsec_short;
    LOG("universe_variation_tweaks", pNOTICE) << " Tweaking xsec systematics ";
    for(const std::string &s : file_systematics){
      LOG("universe_variation_tweaks", pINFO) << s;
    }
  }
  else if (params_to_tweak == "flux") {
    systematics      = flux_corr;
    systematics.insert(systematics.end(), flux_uncorr.begin(), flux_uncorr.end());
    file_systematics = flux_corr_short;
    file_systematics.insert(file_systematics.end(), flux_uncorr_short.begin(), flux_uncorr_short.end());
    LOG("universe_variation_tweaks", pNOTICE) << " Tweaking all flux systematics ";
    for(const std::string &s : file_systematics){
      LOG("universe_variation_tweaks", pINFO) << s;
    }
  }
  else if (params_to_tweak == "flux_corr") {
    systematics      = flux_corr;
    file_systematics = flux_corr_short;
    LOG("universe_variation_tweaks", pNOTICE) << " Tweaking correlated flux systematics ";
    for(const std::string &s : file_systematics){
      LOG("universe_variation_tweaks", pINFO) << s;
    }
  }
  else if (params_to_tweak == "flux_uncorr") {
    systematics      = flux_uncorr;
    file_systematics = flux_uncorr_short;
    LOG("universe_variation_tweaks", pNOTICE) << " Tweaking uncorrelated flux systematics ";
    for(const std::string &s : file_systematics){
      LOG("universe_variation_tweaks", pINFO) << s;
    }
  }
  else if (params_to_tweak == "pion") {
    systematics      = piplus;
    file_systematics = piplus_short;
    LOG("universe_variation_tweaks", pNOTICE) << " Tweaking piplus flux systematic ";
    for(const std::string &s : file_systematics){
      LOG("universe_variation_tweaks", pINFO) << s;
    }
  }
  else if (params_to_tweak == "all") {
    systematics      = flux_corr;
    file_systematics = flux_corr_short;
    systematics.insert(systematics.end(), flux_uncorr.begin(), flux_uncorr.end());
    systematics.insert(systematics.end(), xsec.begin(), xsec.end());
    file_systematics.insert(file_systematics.end(), flux_uncorr_short.begin(), flux_uncorr_short.end());
    file_systematics.insert(file_systematics.end(), xsec_short.begin(), xsec_short.end());
    LOG("universe_variation_tweaks", pNOTICE) << " Tweaking all systematics ";
    for(const std::string &s : file_systematics){
      LOG("universe_variation_tweaks", pINFO) << s;
    }
  }
  else {
    LOG("universe_variation_tweaks",pFATAL) << "Unknown systematics list: "<< params_to_tweak;
    util::Die(-1);
  }
  
  // Open input analysis file and get the DST
  TFile fin(input_rootfile.c_str(),"READ");
  if (!fin.IsOpen()) {
    LOG("universe_variation_tweaks", pFATAL) 
      << "Failed to open file "<<input_rootfile.c_str();
    util::Die(-1);
  }
  string tree_name = "valor_sbncode_mini_dst";
  TTree * analysis_tree = dynamic_cast <TTree *> (fin.Get(tree_name.c_str()));
  if(!analysis_tree) {
    LOG("universe_variation_tweaks", pFATAL) 
      << "No event tree " << tree_name 
      << " in " << " input analysis file: "
      << input_rootfile;
    util::Die(-1);
  }
  LOG("universe_variation_tweaks", pINFO) << " Successfully accessed analysis TTree with the name " << tree_name;

  // Get the branches we're interested in
  //
  // Universes
  const size_t max_n_universes = 10000;
  std::map<std::string,int> branch_n_universes;
  std::map<std::string,std::vector<float>> branch_universes;
  for (const string &variation_name : systematics) {
    branch_universes.emplace(variation_name,std::vector<float>(max_n_universes));
    std::string branch_name   = Form("variation_%s",variation_name.c_str());
    std::string branch_name_n = Form("variation_n_%s",variation_name.c_str());
    analysis_tree->SetBranchStatus (branch_name_n.c_str(),1);
    analysis_tree->SetBranchStatus (branch_name  .c_str(),1);
    bool bstat_univ_n = analysis_tree->SetBranchAddress(branch_name_n.c_str(),&branch_n_universes[variation_name]);
    bool bstat_univ   = analysis_tree->SetBranchAddress(branch_name.c_str(),branch_universes[variation_name].data());
    if (bstat_univ_n || bstat_univ) {
      LOG("universe_variation_tweaks",pFATAL) << " Failed to load needed universe branch.";
      util::Die(-1);
    }
  }
  LOG("universe_variation_tweaks", pINFO) << " Successfully loaded universe branches";

  // Only apply simple binning for now
  const SingleSampleKineBinning & binning = *(gmodel->GetBinning());
  const VALORBinning * reco_sb            = (binning.RecoSmpBinning());
  const int n_reco_bins                   = reco_sb->NBins();
  // Setup arrays to be used for constructing the histograms
  VALORArray *pdfuni[ntoys];
  VALORArray *pdfnom  = new VALORArray(n_reco_bins);
  pdfnom->SetAll(0.);
  for(int i = 0; i < ntoys; ++i){
    pdfuni[i] = new VALORArray(n_reco_bins);
    pdfuni[i]->SetAll(0.);
  }
  LOG("universe_variation_tweaks", pINFO) << " Successfully setup PDFs";

  // Now get the map of universe id for each throw and parameter
  std::map< std::string, std::vector<int> > syst_toy_universe;
  for(const std::string s : systematics){
    std::vector<int> universe_ids;
    LOG("universe_variation_tweaks",pDEBUG) << " For " << s << " with " << ntoys << " throws and 1000 possible universes";
    for(int itoy = 0; itoy < ntoys; ++itoy){
      int iuni = rand() % 1000;
      LOG("universe_variation_tweaks",pDEBUG) << " Throw " << itoy << " will access universe " << iuni;
      universe_ids.push_back(iuni);
    }
    syst_toy_universe.emplace(s,universe_ids);
  }

  // Ereco
  double enu_reco   = -999.;
  double weight     = -999.;
  double pot_weight = -999.;
  analysis_tree->SetBranchAddress("enu_reco", &enu_reco);
  analysis_tree->SetBranchAddress("wght",     &weight);
  analysis_tree->SetBranchAddress("wght_pot", &pot_weight);

  double data_pot = gmodel->GetPOT();
  int nev = analysis_tree->GetEntries();
  
  LOG("universe_variation_tweaks", pINFO) << " About to enter analysis tree loop with " << nev << " entries";
  
  for(int iev = 0; iev < nev; ++iev){
    analysis_tree->GetEntry(iev);
    
    // Exposure for assumed data - Weight MC templates to that exposure
    // Calculate POT weight (assumed data exposure) / (generated MC exposure)
    double pot_wght = pot_weight*data_pot;
    
    double this_entry = weight;
    this_entry *= pot_wght;

    // Get the current entry's bin
    std::vector<double> recovec;
    recovec.push_back(enu_reco);
    const int ireco = reco_sb->FindBin(recovec);

    // Ensure the bin is refilled until everything has been accounted for
    pdfnom->AddToEntry(this_entry, ireco);

    for(int itoy = 0; itoy < ntoys; ++itoy){
      // Setup universe arrays
      double uni_wght = this_entry;

      // Get the product of the 1 sigma weights for all sysematics
      for(const string &syst : systematics){
        // Get the total universe weight
        const std::vector<float> & universes = branch_universes.at(syst);
        const int &n = branch_n_universes.at(syst);
        const int iuni = syst_toy_universe.at(syst).at(itoy);
        if(iuni > n){
          LOG("universe_variation_tweaks",pFATAL) << " The universe that is being accessed: " << iuni << " exceeds the number available for this parameter: " << n << ", " << syst;
          util::Die(-1);
        }

        // Get the weight for this parameter at that universe
        uni_wght *= universes.at(iuni);
        LOG("universe_variation_tweaks", pDEBUG) << " The weight for systematic " << syst << ", universe " << iuni << " and throw " << itoy << " is " << universes.at(iuni);
      }// Systematic
      LOG("universe_variation_tweaks", pDEBUG) << " Total universe weight for entry " << iev << " : " << uni_wght;
      pdfuni[itoy]->AddToEntry(uni_wght,ireco);
    }// Throw 
  }// Events
  LOG("universe_variation_tweaks", pINFO) << " Finished analysis loop";

  // Now set the PDFs as histograms
  conv::KineVar_t   kv(util::KineVarFromString(arg_kine_var));
  conv::KineSpace_t ks(util::KineSpaceFromKineVar(kv));
  assert(ks != conv::kspUndefined);
  const char * nom_name = "h_nom_pdf";
  TH1D * nom_pdf = util::binning::Make1DHistogram(*pdfnom,binning,ks,true);
  nom_pdf->SetName(nom_name);

  LOG("universe_variation_tweaks", pINFO) << " Filled nominal histogram with " << nom_pdf->GetNbinsX() << " bins";

  std::vector<TH1D*> huni;
  for(int itoy = 0; itoy < ntoys; ++itoy){
    string name = "h_uni_var_pdf_"+itoy;
    huni.push_back(util::binning::Make1DHistogram(*pdfuni[itoy],binning,ks,true));
    huni.at(itoy)->SetName(name.c_str());
  }
  LOG("universe_variation_tweaks", pINFO) << " Translated PDFs to histograms";
  
  // Histograms to store the spectra for the default, +1 sigma and -1 sigma variations 
  // Setup the per-detector histograms for variations to determine sigma from nominal
  double max = -999.;
  TH1D * nom_pdf_werr = new TH1D(*nom_pdf);
  TH1D * err_m1 = new TH1D(*nom_pdf);
  TH1D * err_p1 = new TH1D(*nom_pdf);
  nom_pdf_werr->Reset();
  err_m1->Reset();
  err_p1->Reset();
  for(int ebin = 1; ebin <= nom_pdf->GetNbinsX(); ebin++) {
    double nom_val = nom_pdf->GetBinContent(ebin);
    double one_sigma = 1.;
    double sumsq     = 0;

    for(int itoy = 0; itoy < ntoys; itoy++) {
      double curr_val = huni[itoy]->GetBinContent(ebin);
      sumsq += TMath::Power(curr_val-nom_val,2.);
    }//itoy

    one_sigma = TMath::Sqrt(sumsq/static_cast<double>(ntoys));
    err_m1->SetBinContent(ebin, nom_val - one_sigma);
    err_p1->SetBinContent(ebin, nom_val + one_sigma);
    nom_pdf_werr->SetBinError(ebin,one_sigma);
    if( nom_pdf->GetBinCenter(ebin) < enu_reco_max ) {
      max = TMath::Max(max, nom_val + one_sigma);
    }
  }//ebin
  LOG("universe_variation_tweaks", pINFO) << " Filled histograms";
  
  // Draw and (if necessary), write to file
  TFile * outfile = NULL;
  if (output_rootfile!="-" && output_rootfile!="none") {
    output_rootfile = util::ReplaceAll(output_rootfile,"[PARAMS]",params_to_tweak);
    outfile = new TFile(output_rootfile.c_str(),"RECREATE");
    LOG("universe_variation_tweaks",pNOTICE)<<"Writing to file: "<<output_rootfile;
  }
  
  BeamConf_t beam = gmodel->GetBeam();
  if (outfile && outfile->IsOpen()) {
    TString name = TString::Format("env_sb_%s_%s", util::AsString(beam).c_str(), util::AsString(sample).c_str() );
    nom_pdf->Write((name+"_nom").Data());
    nom_pdf_werr->Write((name+"_nom_err").Data());
    err_p1 ->Write((name+"_p1" ).Data());
    err_m1 ->Write((name+"_m1" ).Data());
  }
  
  if (outfile) {
    outfile->Close();
    delete outfile;
  }
  
  std::cout <<"Done!"<<std::endl;
  
  time_t endrawtime;
  struct tm * endtimeinfo;
  time (&endrawtime);
  endtimeinfo = localtime (&endrawtime);
  time_t total_time = endrawtime-scriptstartrawtime;
  std::cout << "-----------------------------------------------------------" << std::endl;
  std::cout << " End local time and date  :  " << asctime(endtimeinfo);
  std::cout << " Total time taken         :  " << total_time/static_cast<double>(60) << " minutes" << std::endl;
  std::cout << "-----------------------------------------------------------" << std::endl;

}
