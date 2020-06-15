//____________________________________________________________________________
/*!

\app       valor_sbn-universe_variation_tweaks

\brief     Vary the MC spectra by throwing sets of systematics

\options     --output              : Where to save tweaked histograms to. [def: tweaks_[PARAMS].root]
             --input               : Input DST file [required]
             --params              : Parameters to tweak - to name the output file [def: allsyst]
             --sample              : Topology [def: numulikeCChigh]
             --detector            : Detector [def: sbn_nd]
             --kinevar             : Kinematic paramter to parameterise in [def: ereco]
             --ntoys               : Number of toy-MC experiments [def: 1000]
             --config              : Analysis configuration file [required]
             --syst-from-quantiles : Whether to calculate systematics from rms or cherry-pick from universes [def: --syst-from-rms]
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
 { /*
   "genie_ccresAxial_Genie",
   "genie_ncresAxial_Genie",
   "genie_qema_Genie",
   "genie_NC_Genie",
   "genie_NonResRvbarp1pi_Genie",
   "genie_NonResRvbarp2pi_Genie",
   "genie_NonResRvp1pi_Genie",
   "genie_NonResRvp2pi_Genie",
   */
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
std::vector<std::string> file_systematics =
 { /*
   "genie_ccresAxial",
   "genie_ncresAxial",
   "genie_qema",
   "genie_NC",
   "genie_NonResRvbarp1pi",
   "genie_NonResRvbarp2pi",
   "genie_NonResRvp1pi",
   "genie_NonResRvp2pi",
   */
   "expskin",
   "horncurrent",
   "kminus",
   "kplus",
   "kzero",
   "nucleoninexsec",
   "nucleonqexsec",
   "nucleontotxsec",
   "piminus",
   "pioninexsec",
   "pionqexsec",
   "piontotxsec",
   "piplus"
 };

void GetVariations(std::map< std::string, std::vector<double> > &vs, 
                   const std::string &in, 
                   const std::vector<std::string> &sy);

void GetKnots(const std::map< std::string, std::vector<double> > &vars, 
              const std::vector<double> &knots, 
              std::map< std::string, std::map<unsigned int, double> >&vs, 
              std::map< std::string, std::map<unsigned int, double> > &kns);

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
  string input_var_file   = arg.GetString("variations");
  string output_rootfile  = arg.GetString("output");
  string params_to_tweak  = arg.GetString("params");
  string arg_sample       = arg.GetString("sample");
  string arg_detector     = arg.GetString("detector");
  string arg_kine_var     = arg.GetString("kine-var");
  bool   arg_quantile     = arg.GetBool("syst-from-quantiles");
  
  string mesg_thresholds  = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  Sample_t   sample       = util::SampleFromString(arg_sample);
  Detector_t detector     = util::DetectorFromString(arg_detector);
  
  // 
  // Read in the universe-variation txt file and use it to determine the best universes
  // for -1sigma / +1sigma variations
  //
  // 1) Read in the text file
  // 2) Find the row which starts with the name of the variation we want
  // 3) Pass the space-delimeted values to a vector
  //
  // If we want to use the quantile method, get the variations and knots
  std::map< string, std::vector<double> > variations;
  const std::vector<double> &knots = {-1.0,0.0,1.0};

  // Chosen universe specifications
  std::map< std::string, std::vector<unsigned int> > ids;
  std::map< std::string, std::map<unsigned int, double> > vars;
  std::map< std::string, std::map<unsigned int, double> > kns;

  if(arg_quantile){
    variations.clear();
    GetVariations(variations, input_var_file, file_systematics);
    // Check the variations
    if(!variations.size()){
      VLOG("universe_variation_tweaks",pFATAL) << "Variations came back empty";
      util::Die(-1);
    }
    VLOG("universe_variation_tweaks",pNOTICE) << "Variations in vector form of size " << variations.size();
  
    ids.clear(); vars.clear(); kns.clear();
    // 
    // 4) Find the entries which most closely match the knot positions
    // 5) Pass the universe entry (integer) and value (double) corresponding to these knots to a map
    //
    // Number of knots for the specified systematic parameter
    GetKnots(variations,knots,vars,kns);
    VLOG("universe_variation_tweaks",pNOTICE) << "Universe ID and variation value for knots and systematics: ";
    for(const std::string &sy : file_systematics){
      std::vector<unsigned int> tmp_ids;
      std::map<unsigned int, double> tmp_vars = vars.at(sy);
      std::map<unsigned int, double> tmp_kns  = kns.at(sy);
      std::map<unsigned int, double>::iterator tmp_itr;
      tmp_ids.clear();
      for(tmp_itr = tmp_vars.begin(); tmp_itr != tmp_vars.end(); ++tmp_itr) {
        VLOG("universe_variation_tweaks",pNOTICE) << "ID: " << tmp_itr->first << ", variation: " << tmp_itr->second << " for knot: " << tmp_kns.at(tmp_itr->first) << " and systematic: " << sy;
        tmp_ids.push_back(tmp_itr->first);
      }
      ids.insert({sy,tmp_ids});
    }
  } // arg_quantile
  
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
  VALORArray *pdfuniq = new VALORArray(n_reco_bins);
  VALORArray *pdfnom  = new VALORArray(n_reco_bins);
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

    // Weights for single universes found for pm 1sigma variations
    double uni_wght_p1 = -999.;
    double uni_wght_m1 = -999.;
    double uni_wght_av = -999.;
    for(int itoy = 0; itoy < ntoys; ++itoy){
      // Setup universe arrays
      pdfuni[itoy]->SetEntry(curr_wght, ireco);
      double uni_wght    = curr_wght;
      uni_wght_p1 = curr_wght;
      uni_wght_m1 = curr_wght;
      uni_wght_av = curr_wght;

      // Get the product of all the systematic entries for this universe
      for(const string &syst : systematics){
        // Get the total universe weight
        const std::vector<float> & universes = branch_universes.at(syst);
        // Get the nominal, weighted by the current universe
        if(arg_quantile){
          std::vector<unsigned int> curr_ids(ids.at(syst));
          std::vector<unsigned int>::iterator it = std::find(curr_ids.begin(),curr_ids.end(),itoy);
          if(it != curr_ids.end() && knots[itoy] == 1)
            uni_wght_p1 *= universes.at(itoy);
          else if(it != curr_ids.end() && knots[itoy] == -1)
            uni_wght_m1 *= universes.at(itoy);
        }
        else{
          uni_wght *= universes.at(itoy);
        }
        // If we are looking at 
      }// Systematics
      // Set the universe weights
      // Fill the PDF
      if(!arg_quantile){
        VLOG("universe_variation_tweaks", pDEBUG) << " Total universe weight for entry " << iev << " : " << uni_wght;
        pdfuni[itoy]->SetEntry(uni_wght,ireco);
      }
    }// Universes

    // If we're using quantiles, average the pm 1sigma values (they should be symmetric)
    if(arg_quantile){
      uni_wght_av = abs(uni_wght_p1 - uni_wght_m1)/2.;
      pdfuniq->SetEntry(uni_wght_av,ireco);
    }

  }// Events
  VLOG("universe_variation_tweaks", pINFO) << " Finished analysis loop";

  // Now set the PDFs as histograms
  conv::KineVar_t   kv(util::KineVarFromString(arg_kine_var));
  conv::KineSpace_t ks(util::KineSpaceFromKineVar(kv));
  assert(ks != conv::kspUndefined);
  const char * nom_name = "h_nom_pdf";
  const char * uni_name = "h_uniq_pdf";
  TH1D * nom_pdf = util::binning::Make1DHistogram(*pdfnom,binning,ks,true);
  nom_pdf->SetName(nom_name);
  VLOG("universe_variation_tweaks", pINFO) << " Filled nominal histogram with " << nom_pdf->GetNbinsX() << " bins";
  TH1D * uni_pdf = util::binning::Make1DHistogram(*pdfuniq,binning,ks,true);
  uni_pdf->SetName(uni_name);
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
  for(int ebin = 1; ebin <= nom_pdf->GetNbinsX(); ebin++) {
    double nom_val = nom_pdf->GetBinContent(ebin);
    double one_sigma = 1.;
    if(!arg_quantile){
      double sumsq   = 0;
      for(int itoy = 0; itoy < ntoys; itoy++) {
        double curr_val = huni[itoy]->GetBinContent(ebin);
        sumsq += TMath::Power(curr_val-nom_val,2.);
      }//itoy
      one_sigma = TMath::Sqrt(sumsq/ntoys);
    }// Quantile?
    else{
      double curr_val = uni_pdf->GetBinContent(ebin);
      one_sigma       = abs(nom_val - curr_val);  
    }
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
//___________________________________________________________________
void GetVariations(std::map< std::string, std::vector<double> > &vs, 
                   const std::string &in, 
                   const std::vector<std::string> &sy){

  VLOG("universe_variation_tweaks",pINFO) << "IN VARIATIONS";
  std::ifstream uFile;
  uFile.open(in);
  if(!uFile){
    VLOG("universe_variation_tweaks",pFATAL) << "Unable to open universe file: " << in;
    util::Die(-1);
  }
  if(vs.size()){
    VLOG("universe_variation_tweaks",pFATAL) << "Vector to hold variations is not empty";
    return;
  }

  for(const std::string &syst : sy){
    VLOG("universe_variation_tweaks",pINFO) << "SYST LOOP AT:" << syst;
    std::vector<double> vars;
    vars.clear();
    while(!uFile.eof()){
    VLOG("universe_variation_tweaks",pINFO) << "IN FILE LOOP";
      std::string line = "";
      std::getline(uFile,line);
      size_t found_v = line.find(syst);
      if(found_v != std::string::npos){
      VLOG("universe_variation_tweaks",pINFO) << "FOUND SYST";
        // Clean up the line to pass the variations to the vector
        VLOG("universe_variation_tweaks",pINFO) << "Found line containing " << syst << " parameters: \n" << line;
        VLOG("universe_variation_tweaks",pINFO) << "Removing systematic name from line";
        line.erase(0, found_v+syst.length());
        VLOG("universe_variation_tweaks",pINFO) << "Line now contains: \n" << line;

        // Pass the remaining contents of the line to a vector of doubles
        double value;
        std::stringstream lineValue(line);
        while(lineValue >> value){
          VLOG("universe_variation_tweaks",pINFO) << "Variation: " << value;
          vars.push_back(value);
        }
        break;
      } // Found the current systematic
    } // variations text file
    vs.insert({syst,vars});
  } // Loop over the systematics 
} // GetVariations
//___________________________________________________________________
void GetKnots(const std::map< std::string, std::vector<double> > &vars, 
              const std::vector<double> &knots, 
              std::map< std::string, std::map<unsigned int, double> >&vs, 
              std::map< std::string, std::map<unsigned int, double> > &kns){

  for(const std::pair<std::string, std::vector<double> > &v : vars){
    std::string syst = v.first;
    std::cout << " Current syst in GetKnots : " << syst << std::endl;
    std::map<unsigned int, double> tmp_vs, tmp_kns;
    for(const double &kn : knots){
      double min_diff     = 999.;
      double best_var     = -999.;
      unsigned int min_id = 999; 
      unsigned int it = 0;
      std::vector<double> tmp_vars = v.second;
      std::cout << " Number of variations: " << tmp_vars.size() << std::endl;
      for(const double & var : tmp_vars){ 
        //Check if the current variation is closest to the current knot
        //At the end of the loop, push back the closest variation and it's location in the vector
        if(abs(kn-var) < abs(min_diff)){
          min_diff  = abs(kn-var);
          best_var  = var;
          min_id    = it;
          ++it;
        }
      }
      tmp_vs.insert({min_id,best_var});
      tmp_kns.insert({min_id,kn});
    } // Syst-variation map
    vs.insert({syst, tmp_vs});
    kns.insert({syst, tmp_kns});
  }
  if(vs.size() != kns.size()){
    VLOG("universe_variation_tweaks",pFATAL) << "Number of entries in knots and variation lists don't match";
    VLOG("universe_variation_tweaks",pFATAL) << "NKnots: " << kns.size() << ", NVariations: " << vs.size();
    util::Die(-1);
  }
}
