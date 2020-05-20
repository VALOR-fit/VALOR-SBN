#include <iostream>
#include <cmath>

#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPad.h"
#include "TString.h"
#include "TF1.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TAttFill.h"

using namespace std;
using namespace valor;
namespace vutil = valor::util;

// Naming structure of the tweak and universe-based files
TString splineFilePattern("valor_splines_[SAMPLE]_[PARAM]_[BEAM]_[DET]");
TString tweakFilePattern("[PARAM]_[NSIG]");

// Name filling functions
const TString GetTweaksFileName(const char* param, 
                                TString &tag,
                                const int &nsigma,
                                const TString &location,
                                const bool &all);
const TString GetSplineFileName(const char* param, 
                                const char* sample, 
                                const char* beam,
                                const char* detector,
                                const TString &location);
const TString GetStringReplacements(const TString &pattern, 
                                    const char* param="", 
                                    const char* sample="", 
                                    const char* beam="", 
                                    const char* detector="", 
                                    const int &nsigma=-999);

// Check if the files can be opened
void CheckFiles(TFile *f_univ,
                TFile *f_nom, 
                TFile *f_1sig, 
                TFile *f_2sig, 
                TFile *f_3sig,
                const std::string &universe_filename,
                const std::string &nominal_filename,
                const std::string &tweaks_1sig_filename,
                const std::string &tweaks_2sig_filename,
                const std::string &tweaks_3sig_filename,
                const bool &verbose = false);

// Function to fix histogram y-axis and improve appearance of binning
void FixBinning(TH1D *hist, 
                const double &per_energy_gev);

// For correct naming of histograms and pads, get the number of sigma from the iterator in the histogram vector
const int GetNSigmaFromIterator(const unsigned int &it,
                                const bool &verbose = false);

// Get errors in the ratio pad bins
void SetRatioBinErrors(const TH1D *h_un, 
                       const TH1D *h_tw, 
                       TH1D *h_ra, 
                       const bool &verbose = false);

// Set the ratio plot formatting
void SetRatioPlotFormatting(TH1D *h, 
                            const bool &fill    = false,
                            const bool &verbose = false);

// Set the spectra formatting
void SetSpectraFormatting(TH1D *h_tweak, 
                          TH1D *h_universe, 
                          const TString &detector,
                          const bool &verbose = false);

// Get the histogram titles
TString GetTitle(const char* param, 
                 const int &nsigma);
// Main
void spline_validation(const char* param, 
                       const char* sample="numulikeCChigh", 
                       const char* beam="BNB_FHC", 
                       const TString &detector="sbn_nd", 
                       const TString &tweaks_location="", 
                       const TString &spline_location="",
                       const bool &all_in_one = false,
                       const double &per_energy_gev=1.,
                       const bool &verbose=false,
                       TString tag="tweaks",
                       const char* output_file="spline_validation_plots.root"){

  // Get spectra from various places
  // Universe spectra written directly from templates
  size_t len = tag.Length();
  if(tag.Last('_') != len) tag.Append("_");

  // Get filenames
  const std::string universe_filename   (GetSplineFileName(param,sample,beam,detector,spline_location));
  const std::string tweaks_nom_filename (GetTweaksFileName(param,tag,0,tweaks_location,all_in_one));
  const std::string tweaks_1sig_filename(GetTweaksFileName(param,tag,1,tweaks_location,all_in_one));
  const std::string tweaks_2sig_filename(GetTweaksFileName(param,tag,2,tweaks_location,all_in_one));
  const std::string tweaks_3sig_filename(GetTweaksFileName(param,tag,3,tweaks_location,all_in_one));

  // Verbose output for file name getting
  if(verbose){
    std::cout << " Universe filename:      " << universe_filename    << std::endl;
    std::cout << " 0 sigma tweak filename: " << tweaks_nom_filename  << std::endl;
    std::cout << " 1 sigma tweak filename: " << tweaks_1sig_filename << std::endl;
    std::cout << " 2 sigma tweak filename: " << tweaks_2sig_filename << std::endl;
    std::cout << " 3 sigma tweak filename: " << tweaks_3sig_filename << std::endl;
  }

  // Get TFiles and check they exist
  TFile *f_univ = new TFile(universe_filename.c_str(),"READ");
  TFile *f_nom  = new TFile(tweaks_nom_filename.c_str(),"READ");
  TFile *f_1sig = new TFile(tweaks_1sig_filename.c_str(),"READ");
  TFile *f_2sig = new TFile(tweaks_2sig_filename.c_str(),"READ");
  TFile *f_3sig = new TFile(tweaks_3sig_filename.c_str(),"READ");

  CheckFiles(f_univ, f_nom, f_1sig, f_2sig, f_3sig, universe_filename, tweaks_nom_filename, tweaks_1sig_filename, tweaks_2sig_filename, tweaks_3sig_filename, verbose);
  std::cout << " All files opened successfully." << std::endl;

  
  // Tweaked spectra from splines
  TH1D *h_tweak_m3 = static_cast<TH1D*>(f_3sig->Get("env_sb_BNB_FHC_numulikeCChigh_m3")); // -3 sigma
  TH1D *h_tweak_m2 = static_cast<TH1D*>(f_2sig->Get("env_sb_BNB_FHC_numulikeCChigh_m2")); // -2 sigma
  TH1D *h_tweak_m1 = static_cast<TH1D*>(f_1sig->Get("env_sb_BNB_FHC_numulikeCChigh_m1")); // -1 sigma
  TH1D *h_tweak_n0 = static_cast<TH1D*>(f_nom->Get("env_sb_BNB_FHC_numulikeCChigh_p0")); //  NOMINAL
  TH1D *h_tweak_p1 = static_cast<TH1D*>(f_1sig->Get("env_sb_BNB_FHC_numulikeCChigh_p1")); // +1 sigma
  TH1D *h_tweak_p2 = static_cast<TH1D*>(f_2sig->Get("env_sb_BNB_FHC_numulikeCChigh_p2")); // +2 sigma
  TH1D *h_tweak_p3 = static_cast<TH1D*>(f_3sig->Get("env_sb_BNB_FHC_numulikeCChigh_p3")); // +3 sigma

  std::vector<TH1D*> h_tweaks({h_tweak_m3, h_tweak_m2, h_tweak_m1, h_tweak_n0, h_tweak_p1, h_tweak_p2, h_tweak_p3});

  // Universe spectra for -3 -> +3 sigma
  TH1D *h_univ_m3 = static_cast<TH1D*>(f_univ->Get("spectra_var_m3_pdfts_ob_rf_sbn_nd__BNB_FHC__numulikeCChigh_Ereco"));  // -3sigma
  TH1D *h_univ_m2 = static_cast<TH1D*>(f_univ->Get("spectra_var_m2_pdfts_ob_rf_sbn_nd__BNB_FHC__numulikeCChigh_Ereco"));  // -2sigma
  TH1D *h_univ_m1 = static_cast<TH1D*>(f_univ->Get("spectra_var_m1_pdfts_ob_rf_sbn_nd__BNB_FHC__numulikeCChigh_Ereco"));  // -1sigma
  TH1D *h_univ_n0 = static_cast<TH1D*>(f_univ->Get("spectra_var_0_pdfts_ob_rf_sbn_nd__BNB_FHC__numulikeCChigh_Ereco"));  //  NOMINAL
  TH1D *h_univ_p1 = static_cast<TH1D*>(f_univ->Get("spectra_var_1_pdfts_ob_rf_sbn_nd__BNB_FHC__numulikeCChigh_Ereco"));  // +1sigma
  TH1D *h_univ_p2 = static_cast<TH1D*>(f_univ->Get("spectra_var_2_pdfts_ob_rf_sbn_nd__BNB_FHC__numulikeCChigh_Ereco")); // +2sigma
  TH1D *h_univ_p3 = static_cast<TH1D*>(f_univ->Get("spectra_var_3_pdfts_ob_rf_sbn_nd__BNB_FHC__numulikeCChigh_Ereco")); // +3sigma

  std::vector<TH1D*> h_univs({h_univ_m3, h_univ_m2, h_univ_m1, h_univ_n0, h_univ_p1, h_univ_p2, h_univ_p3});

  TVectorD knot_vals(*static_cast<TVectorD*>(f_univ->Get("actual_knot_values")));

  // Make sure the vectors are the same size for making ratio plots later
  if(h_univs.size() != h_tweaks.size()){
    std::cerr << " Error: Number of entries in the universe histogram is: " << h_univs.size() << " and doesn't match the number in the tweaks vector: " << h_tweaks.size() << std::endl;
    exit(1);
  }
  // If necessary normalise to some energy range
  if (per_energy_gev > 0) {
    // Fix the binning if necessary
    for(TH1D *h : h_tweaks){
      FixBinning(h,per_energy_gev);
    } 
    for(TH1D *h : h_univs){
      FixBinning(h,per_energy_gev);
    } 
  }

  // Now loop over the size of the vectors and make the canvases and subpads then save each into a root file
  // Append parameter name to output filename and open
  std::string s_param(param);
  std::string s_output_file(output_file);
  std::string param_filename = s_param+"_"+s_output_file; 
  TFile f_out(param_filename.c_str(),"RECREATE");
  
  for(unsigned int h = 0; h < h_univs.size(); ++h){

    // Translate iterator to number of sigma
    const int n_sigma = GetNSigmaFromIterator(h,verbose);

    // Find the closest actual universe value to the current integer knot 
    double min_sigma_diff = 999;
    for(unsigned int i = 0; i < knot_vals.GetNrows(); ++i){
      double sigma_diff = abs(knot_vals[i]-n_sigma);
      if(sigma_diff < min_sigma_diff)
        min_sigma_diff = sigma_diff;
    }

    // Get the histograms
    TH1D *h_universe = h_univs.at(h);
    TH1D *h_tweak    = h_tweaks.at(h);
    h_universe->GetXaxis()->SetRangeUser(0.,3.);
    h_tweak->GetXaxis()->SetRangeUser(0.,3.);

    // Now make the canvas, legend and sort out the pads
    TCanvas *c = new TCanvas("c","",600,1000);
    TLegend *l = new TLegend(0.49,0.46,0.94,0.72);
    l->SetBorderSize(0);
    l->SetTextFont(132);
    l->AddEntry(h_tweak, "Spectra from tweaks", "l");
    l->AddEntry(h_universe, "Spectra from universes", "l");
    
    // The upper pad (spectra)
    TPad *pad1 = new TPad("pad1","",0.0,0.35,1.0,1.0);
    pad1->SetBottomMargin(0.02);
    pad1->SetTopMargin(0.05);
    pad1->SetRightMargin(0.02);
    pad1->Draw();
    pad1->cd();

    // Format the spectra plots and draw
    SetSpectraFormatting(h_tweak,h_universe,detector,verbose);
    TString title = GetTitle(param, n_sigma);
    TLatex * l_title = new TLatex();
    l_title->SetTextSize(0.05);
    l_title->SetTextAlign(22);
    h_tweak->Draw();
    h_universe->Draw("same");
    l->Draw("same");
    if(detector.Contains("nd"))
      l_title->DrawLatex(1.49,3.58e6,title.Data());
    else if(detector.Contains("ub"))
      l_title->DrawLatex(1.49,0.09e6,title.Data());
    else if(detector.Contains("ic"))
      l_title->DrawLatex(1.49,0.1e6,title.Data());
   
    double perc_rate_diff = (1-abs(h_tweak->Integral()/static_cast<double>(h_universe->Integral())))*100;
    std::cout << " For " << n_sigma << " sigma: " << std::endl;
    std::cout << " Percentage rate difference between universe spectra and VALOR-generated spectra is: " << perc_rate_diff << std::endl;
    std::cout << " Difference between universe variation and closest N-Sigma is:                       " << min_sigma_diff << std::endl;

    // Update pad and return to main canvas
    pad1->Modified();
    c->cd();
    
    // The lower pad (ratio plot)
    TPad *pad2 = new TPad("pad2","",0.0,0.0,1.0,0.35);
    pad2->SetTopMargin(0.02);
    pad2->SetBottomMargin(0.22);
    pad2->SetRightMargin(0.02);
    pad2->SetGridy();
    pad2->Draw();
    pad2->cd();
   
    // Construct the ratio plot
    TH1D *h_ratio   = static_cast<TH1D*>(h_tweak->Clone("h_ratio"));
    TH1D *h_average = static_cast<TH1D*>(h_tweak->Clone("h_average"));
    h_ratio->Add(h_universe,-1);
    h_average->Add(h_universe);
    h_average->Scale(1/2.);
    h_ratio->Divide(h_average);
    h_ratio->Scale(100);
    TH1D *h_ratio_band = static_cast<TH1D*>(h_ratio->Clone("h_ratio_band"));

    // Set the errors and scale to percentage
    SetRatioBinErrors(h_universe, h_tweak, h_ratio_band, verbose);
   
    // Format the ratio plot and error bands and draw
    SetRatioPlotFormatting(h_ratio_band,true,verbose);
    h_ratio_band->Draw("e2");
    
    // Draw the ratio plot
    SetRatioPlotFormatting(h_ratio,false,verbose);
    h_ratio->Draw("hist same");

    // Update the pad and canvas
    pad2->Modified();
    c->Update();

    // Write the canvas to the TFile
    TString canvas_name = "canv_";
    canvas_name+=std::to_string(n_sigma);
    canvas_name+="_sigma";
    canvas_name = canvas_name.ReplaceAll("-","m");
    std::string canvas_str(canvas_name);
    c->Write(canvas_str.c_str());
    
    // Safely delete canvas and legend, this isn't possible for pads
    delete c;
    delete l;
    delete l_title;

    // Reset histograms
    h_universe->Reset();
    h_tweak->Reset();
    h_ratio->Reset();
    h_average->Reset();
  }

  f_out.Write();
  f_out.Close();
  return;
}
// ----------------------------------------------------------------------------------
const TString GetTweaksFileName(const char* param, 
                                TString &tag,
                                const int &nsigma,
                                const TString &location,
                                const bool &all){
  TString name(tweakFilePattern);
  if(!all){
    std::cout << " Not looking at a file with all tweaks included" << std::endl;
    name = GetStringReplacements(name,param,"","","",nsigma);
    name.Append("sigma.root");
    name.Prepend(tag);
    name.Prepend(location);
  }
  else{
    std::cout << " Looking at a file with all tweaks included" << std::endl;
    name = GetStringReplacements(name,param);
    name.Append("sigma.root");
    name.Prepend(tag);
    name.Prepend(location);
  }
  return name;
}
// ----------------------------------------------------------------------------------
const TString GetSplineFileName(const char* param, 
                                const char* sample, 
                                const char* beam,
                                const char* detector,
                                const TString &location){
  TString name(splineFilePattern);
  name = GetStringReplacements(name,param,sample,beam,detector);
  name.Append("_spectra.root");
  name.Prepend(location);
  return name;
}
// ----------------------------------------------------------------------------------
const TString GetStringReplacements(const TString &pattern, 
                                    const char* param="", 
                                    const char* sample="", 
                                    const char* beam="", 
                                    const char* detector="",
                                    const int&  nsigma=-999){
  TString name(pattern);
  name = name.ReplaceAll("[BEAM]",   beam);
  name = name.ReplaceAll("[DET]",   detector);
  name = name.ReplaceAll("[SAMPLE]", sample);
  name = name.ReplaceAll("[PARAM]",  param);
  if(nsigma == -999)
    name = name.ReplaceAll("[NSIG]", "all_");
  else
    name = name.ReplaceAll("[NSIG]", std::to_string(nsigma).c_str());  
  return name;
}
// ----------------------------------------------------------------------------------
void CheckFiles(TFile *f_univ,
                TFile *f_nom, 
                TFile *f_1sig, 
                TFile *f_2sig, 
                TFile *f_3sig,
                const std::string &universe_filename,
                const std::string &nominal_filename,
                const std::string &tweaks_1sig_filename,
                const std::string &tweaks_2sig_filename,
                const std::string &tweaks_3sig_filename,
                const bool &verbose = false){
  if(!f_univ->IsOpen()){
    std::cerr << " Error: Couldn't open universe file with name: " << universe_filename << std::endl;
    exit(1);
  }
  if(verbose) std::cout << " Successfully opened universe file with name: " << universe_filename << std::endl;

  if(!f_nom->IsOpen()){
    std::cerr << " Error: Couldn't open nominal file with name: " << nominal_filename << std::endl;
    exit(1);
  }
  if(verbose) std::cout << " Successfully opened nominal file with name: " << nominal_filename << std::endl;

  if(!f_1sig->IsOpen()){
    std::cerr << " Error: Couldn't open 1 sigma tweaked file with name: " << tweaks_1sig_filename << std::endl;
    exit(1);
  }
  if(verbose) std::cout << " Successfully opened 1 sigma tweaked file with name: " << tweaks_1sig_filename << std::endl;

  if(!f_2sig->IsOpen()){
    std::cerr << " Error: Couldn't open 2 sigma tweaked file with name: " << tweaks_2sig_filename << std::endl;
    exit(1);
  }
  if(verbose) std::cout << " Successfully opened 2 sigma tweaked file with name: " << tweaks_2sig_filename << std::endl;

  if(!f_3sig->IsOpen()){
    std::cerr << " Error: Couldn't open 3 sigma tweaked file with name: " << tweaks_3sig_filename << std::endl;
    exit(1);
  }
  if(verbose) std::cout << " Successfully opened 3 sigma tweaked file with name: " << tweaks_3sig_filename << std::endl;

  return;
}
// ----------------------------------------------------------------------------------
void FixBinning(TH1D *hist,
                const double &per_energy_gev){
  // Loop over bins and scale
  for (int ibin = 1 ; ibin <= hist->GetXaxis()->GetNbins(); ibin++) {
    double old_bin_content = hist->GetBinContent(ibin);
    double bin_width = hist->GetXaxis()->GetBinWidth(ibin);
    double new_bin_content = old_bin_content * per_energy_gev / bin_width;
    hist->SetBinContent(ibin,new_bin_content);
  }
  return;
}
// ----------------------------------------------------------------------------------
const int GetNSigmaFromIterator(const unsigned int &it, 
                                const bool &verbose = false){
  int sigma = -999;
  switch(it){
    case 0:
      sigma = -3;
      break;
    case 1:
      sigma = -2;
      break;
    case 2:
      sigma = -1;
      break;
    case 3:
      sigma = 0;
      break;
    case 4:
      sigma = 1;
      break;
    case 5:
      sigma = 2;
      break;
    case 6:
      sigma = 3;
      break;
    default:
      sigma = 0;
      std::cout << " No iterator given therefore default sigma used: " << sigma << std::endl;
  }
  if(verbose)
    std::cout << " Iterator = " << it << ", therefore the number of sigma we are looking at is: " << sigma << std::endl;
  if(sigma == -999){
    std::cerr << " Error: No iterator recognised, number of sigma is being returned as: " << sigma << std::endl;
  }
  return sigma;
}
// ----------------------------------------------------------------------------------
void SetRatioBinErrors(const TH1D* h_un, const TH1D* h_tw, TH1D* h_ra, const bool &verbose = false){

  // The ratio bins are filled as content R = ((h_tw-h_un)/((h_un+h_tw)/2))*100
  // The errors in the ratio bins are as follows
  // sigR/R = sqrt( pow(sigDN/DN,2) + pow(sigAVN/AVN,2))
  // sigDN = sigAVN = sigN
  
  // Loop over x bins and make the calculation
  // There should be the same number of bins in all histograms
  for (int ibin = 1 ; ibin <= h_tw->GetXaxis()->GetNbins(); ibin++) {
    double N_tweak    = h_tw->GetBinContent(ibin);
    double N_universe = h_un->GetBinContent(ibin);
    double R          = h_ra->GetBinContent(ibin);
    double sigN       = sqrt(N_tweak + N_universe);
    double deltaN     = abs(N_tweak-N_universe);
    double averageN   = (N_tweak+N_universe)/2.;

    double sigR = R * sqrt( pow(sigN/deltaN,2) + pow(sigN/averageN,2));
    h_ra->SetBinError(ibin,sigR);

    if(verbose)
      std::cout << " Setting the bin content of bin " << ibin << " to be: " << R << " +/- " << sigR << std::endl;
  }
  return;
}
// ----------------------------------------------------------------------------------
void SetRatioPlotFormatting(TH1D* h, 
                            const bool &fill    = false,
                            const bool &verbose = false){
  h->SetStats(0);
  h->SetTitle("");
  h->GetYaxis()->SetMaxDigits(3);
  h->GetYaxis()->SetTitle("#Delta Rate / Rate_{Average}, %");
  h->GetYaxis()->SetTitleFont(132);
  h->GetYaxis()->SetLabelFont(132);
  h->GetYaxis()->SetTitleSize(0.1);
  h->GetYaxis()->SetTitleOffset(0.55);
  h->GetYaxis()->SetLabelSize(0.075);
  h->GetXaxis()->SetTitle("Reconstructed E_{#nu} [GeV]");
  h->GetXaxis()->SetTitleFont(132);
  h->GetXaxis()->SetLabelFont(132);
  h->GetXaxis()->SetTitleSize(0.1);
  h->GetXaxis()->SetTitleOffset(0.9);
  h->GetXaxis()->SetLabelSize(0.075);
  if(fill){
    if(verbose)
      std::cout << " Filling the error band plot" << std::endl;
    h->SetFillColor(kPink+5);
    h->SetFillStyle(3001);
    h->SetLineWidth(0);
  }
  else{
    if(verbose)
      std::cout << " Drawing the ratio plot with no errors" << std::endl;
    h->SetLineColor(kPink+5);
    h->SetLineStyle(1);
    h->SetLineWidth(2);
  } 
  return;
}
// ----------------------------------------------------------------------------------
void SetSpectraFormatting(TH1D* h_tweak, 
                          TH1D* h_universe, 
                          const TString &detector,
                          const bool &verbose = false){
  // Now set everything
  h_tweak->SetStats(0);
  h_tweak->SetTitle("");
  h_tweak->GetXaxis()->SetLabelSize(0);
  h_tweak->GetYaxis()->SetMaxDigits(3);
  h_tweak->GetYaxis()->SetTitle("Event rate / 1 GeV");
  h_tweak->GetYaxis()->SetTitleFont(132);
  h_tweak->GetYaxis()->SetLabelFont(132);
  h_tweak->GetYaxis()->SetTitleSize(0.05);
  h_tweak->GetYaxis()->SetLabelSize(0.04);
  h_tweak->GetYaxis()->SetTitleOffset(1.2);
  h_tweak->SetLineColor(kAzure+7);
  h_tweak->SetLineStyle(7);
  h_tweak->SetLineWidth(2);
  h_universe->SetLineColor(kOrange+2);
  h_universe->SetLineStyle(5);
  h_universe->SetLineWidth(2);
  if(detector.Contains("nd"))
    h_tweak->GetYaxis()->SetRangeUser(0,4.0e6);
  else if(detector.Contains("ub"))
    h_tweak->GetYaxis()->SetRangeUser(0,0.19e6);
  else if(detector.Contains("ic"))
    h_tweak->GetYaxis()->SetRangeUser(0,0.35e6);

  return;
}
// ----------------------------------------------------------------------------------
TString GetTitle(const char* param, 
                 const int &nsigma){

  // Construct the title
  // First remove anything after an underscore in the parameter name, this is usually more than we need to know for the title
  TString title(param);
  size_t underscore = title.Last('_');
  size_t length     = title.Length();
  title.Remove(underscore,length);
  if(nsigma != 0){
    title.Prepend("Spline validation for ");
    title.Append(" at ");
    title.Append(std::to_string(nsigma).c_str());
    title.Append(" #sigma");
  }
  else{
    title.Prepend("Nominal spline validation for ");
  }

  return title;
}
// ----------------------------------------------------------------------------------
