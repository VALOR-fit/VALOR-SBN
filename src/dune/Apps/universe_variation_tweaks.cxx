//____________________________________________________________________________
/*!

\app       valor_dune-universe_variation_tweaks

\brief     Vary the MC spectra by throwing sets of systematics

\options     --output              : Where to save tweaked histograms to. [def: tweaks_[PARAMS].root]
             --input               : Input DST file [required]
             --params              : Parameters to tweak [def: allsyst]
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

std::vector<std::string> systematics =
 { "genie_ccresAxial_Genie",
   "genie_ncresAxial_Genie",
   "genie_qema_Genie",
   "genie_NC_Genie",
   "genie_NonResRvbarp1pi_Genie",
   "genie_NonResRvbarp2pi_Genie",
   "genie_NonResRvp1pi_Genie",
   "genie_NonResRvp2pi_Genie",
   "expskin_FluxUnisim",
   "horncurrent_FluxUnisim",
   "kminus_PrimaryHadronNormalization",
   "kplus_PrimaryHadronFeynmanScaling",
   "kzero_PrimaryHadronSanfordWang",
   "nucleoninexsec_FluxUnisim",
   "nucleonqexsec_FluxUnisim",
   "nucleontotxsec_FluxUnisim",
   "piminus_PrimaryHadronSWCentralSplineVariation",
   "pioninexsec_FluxUnisim",
   "pionqexsec_FluxUnisim",
   "piontotxsec_FluxUnisim",
   "piplus_PrimaryHadronSWCentralSplineVariation"
 };

double enu_reco_max = 10.;

using namespace std;
using namespace valor;
using namespace valor::conv;

int main(int argc, char ** argv)
{

  valor::util::PrintBanner(Env::Instance()->Banner(),500);
 
  CmdLnArgList arg;
  arg.Read(argc,argv,"$VALOR_EXPT/config/apps/universe_variation_tweaks.arg");
  VLOG("universe_variation_tweaks", pNOTICE) << arg;
  
  // Read and iterpret the command line
  int ntoys               = arg.GetInt("ntoys");
  string input_rootfile   = arg.GetString("input");
  string output_rootfile  = arg.GetString("output");
  string params_to_tweak  = arg.GetString("params");
  string arg_sample       = arg.GetString("sample");
  string arg_detector     = arg.GetString("detector");
  string arg_kine_var     = arg.GetString("kine-var");
  
  string mesg_thresholds  = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  Sample_t   sample       = util::SampleFromString(arg_sample);
  Detector_t detector     = util::DetectorFromString(arg_detector);
  
  // Message thresholds
  Messenger::Instance()->Configure(mesg_thresholds);
  
  // Config
  std::string config_path = util::CompleteConfigPath(arg.GetString("config"));

  // Print settings
  cout << "- Reading analysis configuration from: " << config_path << endl;
  
  CompoundFitElements * elements = new CompoundFitElements();
  elements->Read(config_path.c_str());
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
    VLOG("universe_variation_tweaks", pFATAL) << "Failed to identify appropriate fit model to get binning.";
  }
  VLOG("universe_variation_tweaks", pINFO) << " Successfully accessed the relevant model for binning information";
  
  // Open input analysis file and get the DST
  TFile fin(input_rootfile.c_str(),"READ");
  if (!fin.IsOpen()) {
    VLOG("universe_variation_tweaks", pFATAL) 
      << "Failed to open file "<<input_rootfile.c_str();
    util::Die(-1);
  }
  string tree_name = "valor_sbncode_mini_dst";
  TTree * analysis_tree = dynamic_cast <TTree *> (fin.Get(tree_name.c_str()));
  if(!analysis_tree) {
    VLOG("universe_variation_tweaks", pFATAL) 
      << "No event tree " << tree_name 
      << " in " << " input analysis file: "
      << input_rootfile;
    util::Die(-1);
  }
  VLOG("universe_variation_tweaks", pINFO) << " Successfully accessed analysis TTree with the name " << tree_name;

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
      VLOG("universe_variation_tweaks",pFATAL) << " Failed to load needed universe branch.";
      util::Die(-1);
    }
  }
  VLOG("universe_variation_tweaks", pINFO) << " Successfully loaded universe branches";

  // Only apply simple binning for now
  const SingleSampleKineBinning & binning = *(gmodel->GetBinning());
  const VALORBinning * reco_sb            = (binning.RecoSmpBinning());
  const int n_reco_bins                   = reco_sb->NBins();
  // Setup arrays to be used for constructing the histograms
  VALORArray *pdfuni[ntoys];
  VALORArray *pdfnom = new VALORArray(n_reco_bins);
  pdfnom->SetAll(0.);
  for(int i = 0; i < ntoys; ++i){
    pdfuni[i] = new VALORArray(n_reco_bins);
    pdfuni[i]->SetAll(0.);
  }
  VLOG("universe_variation_tweaks", pINFO) << " Successfully setup PDFs";

  // Ereco
  double enu_reco   = -999.;
  double weight     = -999.;
  double pot_weight = -999.;
  analysis_tree->SetBranchAddress("enu_reco", &enu_reco);
  analysis_tree->SetBranchAddress("wght",     &weight);
  analysis_tree->SetBranchAddress("wght_pot", &pot_weight);

  double data_pot = gmodel->GetPOT();
  int nev = analysis_tree->GetEntries();
  
  VLOG("universe_variation_tweaks", pINFO) << " About to enter analysis tree loop with " << nev << " entries";
  
  for(int iev = 0; iev < nev; ++iev){
    analysis_tree->GetEntry(iev);
    
    // Exposure for assumed data - Weight MC templates to that exposure

    // Calculate POT weight (assumed data exposure) / (generated MC exposure)
    double pot_wght = pot_weight*data_pot;
    
    double this_entry = weight;
    this_entry *= pot_wght;

    VLOG("universe_variation_tweaks",pDEBUG) << " Nominal weight to apply to entry " << iev << " : " << this_entry;

    // Get the current entry's bin
    std::vector<double> recovec;
    recovec.push_back(enu_reco);
    const int ireco = reco_sb->FindBin(recovec);

    // Setup the nominal histogram
    double curr_wght = pdfnom->GetEntry(ireco);
    // Ensure the bin is refilled until everything has been accounted for
    curr_wght += this_entry;
    pdfnom->SetEntry(curr_wght, ireco);

    for(int itoy = 0; itoy < ntoys; ++itoy){
      // Setup universe arrays
      pdfuni[itoy]->SetEntry(curr_wght, ireco);
      double uni_wght = curr_wght;

      // Get the product of all the systematic entries for this universe
      for(const string &syst : systematics){
        // Get the total universe weight
        const std::vector<float> & universes = branch_universes.at(syst);
        // Get the nominal, weighted by the current universe
        uni_wght *= universes.at(itoy);
      }// Systematics
      // Set the universe weights
      VLOG("universe_variation_tweaks", pDEBUG) << " Total universe weight for entry " << iev << " : " << uni_wght;
      pdfuni[itoy]->SetEntry(uni_wght,ireco);
    }// Universes
  }// Events
  VLOG("universe_variation_tweaks", pINFO) << " Finished analysis loop";

  // Now set the PDFs as histograms
  conv::KineVar_t   kv(util::KineVarFromString(arg_kine_var));
  conv::KineSpace_t ks(util::KineSpaceFromKineVar(kv));
  assert(ks != conv::kspUndefined);
  const char * nom_name = "h_nom_pdf";
  TH1D * nom_pdf = util::binning::Make1DHistogram(*pdfnom,binning,ks,true);
  nom_pdf->SetName(nom_name);
  VLOG("universe_variation_tweaks", pINFO) << " Filled nominal histogram with " << nom_pdf->GetNbinsX() << " bins";
  TH1D * huni[ntoys];
  for(int itoy = 0; itoy < ntoys; ++itoy){
    huni[itoy] = new TH1D(*nom_pdf);
    string name = "h_uni_var_pdf_"+itoy;
    huni[itoy] = util::binning::Make1DHistogram(*pdfuni[itoy],binning,ks,true);
    huni[itoy]->SetName(name.c_str());
  }
  VLOG("universe_variation_tweaks", pINFO) << " Translated PDFs to histograms";
  
  // Histograms to store the spectra for the default, +1 sigma and -1 sigma variations 
  // Setup the per-detector histograms for variations to determine sigma from nominal
  double max = -999.;
  TH1D * nom_pdf_werr = new TH1D(*nom_pdf);
  TH1D * err_m1 = new TH1D(*nom_pdf);
  TH1D * err_p1 = new TH1D(*nom_pdf);
  nom_pdf_werr->Reset();
  err_m1->Reset();
  err_p1->Reset();
  VLOG("universe_variation_tweaks", pINFO) << " About to loop over bins";
  for(int ebin = 1; ebin <= nom_pdf->GetNbinsX(); ebin++) {
    double nom_val = nom_pdf->GetBinContent(ebin);
    double sumsq   = 0;
    VLOG("universe_variation_tweaks", pINFO) << " About to loop over universes";
    for(int itoy = 0; itoy < ntoys; itoy++) {
      double curr_val = huni[itoy]->GetBinContent(ebin);
      sumsq += TMath::Power(curr_val-nom_val,2.);
    }//itoy
    VLOG("universe_variation_tweaks", pINFO) << " Finished looping over universes";
    double one_sigma = TMath::Sqrt(sumsq/ntoys);
    err_p1->SetBinContent(ebin, nom_val + one_sigma);
    err_m1->SetBinContent(ebin, nom_val - one_sigma);
    nom_pdf_werr->SetBinError(ebin,one_sigma);
    if( nom_pdf->GetBinCenter(ebin) < enu_reco_max ) {
      max = TMath::Max(max, nom_val + one_sigma);
    }
  }//ebin
  VLOG("universe_variation_tweaks", pINFO) << " Filled histograms";
  
  // Draw and (if necessary), write to file
  TFile * outfile = NULL;
  if (output_rootfile!="-" && output_rootfile!="none") {
    output_rootfile = util::ReplaceAll(output_rootfile,"[PARAMS]",params_to_tweak);
    outfile = new TFile(output_rootfile.c_str(),"RECREATE");
    VLOG("universe_variation_tweaks",pNOTICE)<<"Writing to file: "<<output_rootfile;
  }
  
    //~ ic++;
    //~ c[ibeam]->cd(ic);
    //~ TH1F * hframe = c[ibeam]->GetPad(ic)->DrawFrame(0.,0.,enu_reco_max, 1.24*max[imodel]);
    //~ hframe -> GetXaxis() -> SetTitle("Reco. E_{#nu} (GeV)");
    //~ hframe -> GetYaxis() -> SetTitle("");      
  //~ //hframe -> GetYaxis() -> SetTitle("Events per bin");      
    //~ hframe -> Draw();
    //~ nom_pdf_werr [imodel] -> SetFillColor(kRed);
    //~ nom_pdf_werr [imodel] -> SetLineColor(kRed);
    //~ nom_pdf_werr [imodel] -> SetLineWidth(0);
    //~ nom_pdf_werr [imodel] -> SetMarkerSize(0);
    //~ nom_pdf_werr [imodel] -> Draw("E2SAME");
    //~ nom_pdf      [imodel] -> SetLineColor(kBlack);
    //~ nom_pdf      [imodel] -> SetMarkerSize(0);
    //~ nom_pdf      [imodel] -> SetLineWidth(1);
    //~ nom_pdf      [imodel] -> Draw("SAME");
    //~ TLatex * title = new TLatex(1,1.03*max[imodel],Form("%s / %s", util::AsString(b).c_str(), util::AsStringTeX(s,true).c_str()));
    //~ title->SetTextSize(0.08);
    //~ title->Draw();
    //~ TLegend * leg = new TLegend(0.50, 0.50, 0.92, 0.80);
    //~ leg->SetFillColor(0);
    //~ //leg->SetHeader(Form("%s / %s", util::AsString(b).c_str(), util::AsStringTeX(s,true).c_str()));
    //~ leg->AddEntry(nom_pdf     [imodel], "nominal",        "L");
    //~ leg->AddEntry(nom_pdf_werr[imodel], "a-priori error", "F");
    //~ leg->Draw();
    
    BeamConf_t beam = gmodel->GetBeam();
    if (outfile && outfile->IsOpen()) {
      TString name = TString::Format("env_sb_%s_%s", util::AsString(beam).c_str(), util::AsString(sample).c_str() );
      nom_pdf->Write((name+"_nom").Data());
      nom_pdf_werr->Write((name+"_nom_err").Data());
      err_p1 ->Write((name+"_p1" ).Data());
      err_m1 ->Write((name+"_m1" ).Data());
    }
  //~ c[ibeam]->Update();
  
  if (outfile) {
    outfile->Close();
    delete outfile;
  }
  
  std::cout <<"Done!"<<std::endl;
}
