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
TString splineFilePattern("valor_splines_[SAMPLE]_[PARAM]_[BEAM]");
TString tweakFilePattern("tweaks_[PARAM]_[NSIG]");

// Name filling functions
const TString GetTweaksFileName(const char* param, 
                               const int &nsigma,
                               const TString &location);
const TString GetSplineFileName(const char* param, 
                                const char* sample, 
                                const char* beam,
                                const TString &location);
const TString GetStringReplacements(const TString &pattern, 
                                    const char* param="", 
                                    const char* sample="", 
                                    const char* beam="", 
                                    const int &nsigma=1);

// Check if the files can be opened
void CheckFiles(TFile *f_univ,
                TFile *f_1sig, 
                TFile *f_2sig, 
                TFile *f_3sig,
                const std::string &universe_filename,
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
void SetRatioBinErrors(const TH1D* h_un, 
                       const TH1D* h_tw, 
                       TH1D* h_ra, 
                       const bool &verbose = false);

// Set the ratio plot formatting
void SetRatioPlotFormatting(TH1D* h, 
                            const bool &verbose = false);

// Set the spectra formatting
void SetSpectraFormatting(TH1D* h_tweak, 
                          TH1D* h_universe, 
                          const bool &verbose = false);

// Get the histogram titles
TString GetTitle(const char* param, 
                 const int &nsigma);
// Main
void spline_validation(const char* param, 
                       const char* sample="numulikeCChigh", 
                       const char* beam="BNB_FHC", 
                       const TString &tweaks_location="", 
                       const TString &spline_location="", 
                       const double &per_energy_gev=1.,
                       const bool &verbose=false,
                       const char* output_file="spline_validation_plots.root"){

  // Get spectra from various places
  // Universe spectra written directly from templates

  // Verbose output for file name getting
  if(verbose){
    std::cout << " 1 sigma tweak filename: " << GetTweaksFileName(param,1,tweaks_location) << std::endl;
    std::cout << " 2 sigma tweak filename: " << GetTweaksFileName(param,2,tweaks_location) << std::endl;
    std::cout << " 3 sigma tweak filename: " << GetTweaksFileName(param,3,tweaks_location) << std::endl;
    std::cout << " Universe filename:      " << GetSplineFileName(param,sample,beam,spline_location) << std::endl;
  }

  // Get filenames
  const std::string universe_filename   (GetSplineFileName(param,sample,beam,spline_location));
  const std::string tweaks_1sig_filename(GetTweaksFileName(param,1,tweaks_location));
  const std::string tweaks_2sig_filename(GetTweaksFileName(param,2,tweaks_location));
  const std::string tweaks_3sig_filename(GetTweaksFileName(param,3,tweaks_location));

  // Get TFiles and check they exist
  TFile *f_univ = new TFile(universe_filename.c_str(),"READ");
  TFile *f_1sig = new TFile(tweaks_1sig_filename.c_str(),"READ");
  TFile *f_2sig = new TFile(tweaks_2sig_filename.c_str(),"READ");
  TFile *f_3sig = new TFile(tweaks_3sig_filename.c_str(),"READ");

  CheckFiles(f_univ, f_1sig, f_2sig, f_3sig, universe_filename, tweaks_1sig_filename, tweaks_2sig_filename, tweaks_3sig_filename, verbose);
  std::cout << " All files opened successfully." << std::endl;

  // Tweaked spectra from splines
  TH1D *h_tweak_m3 = static_cast<TH1D*>(f_3sig->Get("env_sb_BNB_FHC_numulikeCChigh_m3")); // -3 sigma
  TH1D *h_tweak_m2 = static_cast<TH1D*>(f_2sig->Get("env_sb_BNB_FHC_numulikeCChigh_m2")); // -2 sigma
  TH1D *h_tweak_m1 = static_cast<TH1D*>(f_1sig->Get("env_sb_BNB_FHC_numulikeCChigh_m1")); // -1 sigma
  TH1D *h_tweak_n0 = static_cast<TH1D*>(f_1sig->Get("env_sb_BNB_FHC_numulikeCChigh_nom")); //  NOMINAL
  TH1D *h_tweak_p1 = static_cast<TH1D*>(f_1sig->Get("env_sb_BNB_FHC_numulikeCChigh_p1")); // +1 sigma
  TH1D *h_tweak_p2 = static_cast<TH1D*>(f_2sig->Get("env_sb_BNB_FHC_numulikeCChigh_p2")); // +2 sigma
  TH1D *h_tweak_p3 = static_cast<TH1D*>(f_3sig->Get("env_sb_BNB_FHC_numulikeCChigh_p3")); // +3 sigma

  std::vector<TH1D*> h_tweaks({h_tweak_m3, h_tweak_m2, h_tweak_m1, h_tweak_n0, h_tweak_p1, h_tweak_p2, h_tweak_p3});

  // Universe spectra for -3 -> +3 sigma
  TH1D *h_univ_m3 = static_cast<TH1D*>(f_univ->Get("spectra_var_0_pdfts_ob_rf_sbn_nd__BNB_FHC__numulikeCChigh_Ereco"));  // -3sigma
  TH1D *h_univ_m2 = static_cast<TH1D*>(f_univ->Get("spectra_var_2_pdfts_ob_rf_sbn_nd__BNB_FHC__numulikeCChigh_Ereco"));  // -2sigma
  TH1D *h_univ_m1 = static_cast<TH1D*>(f_univ->Get("spectra_var_4_pdfts_ob_rf_sbn_nd__BNB_FHC__numulikeCChigh_Ereco"));  // -1sigma
  TH1D *h_univ_n0 = static_cast<TH1D*>(f_univ->Get("spectra_var_6_pdfts_ob_rf_sbn_nd__BNB_FHC__numulikeCChigh_Ereco"));  //  NOMINAL
  TH1D *h_univ_p1 = static_cast<TH1D*>(f_univ->Get("spectra_var_8_pdfts_ob_rf_sbn_nd__BNB_FHC__numulikeCChigh_Ereco"));  // +1sigma
  TH1D *h_univ_p2 = static_cast<TH1D*>(f_univ->Get("spectra_var_10_pdfts_ob_rf_sbn_nd__BNB_FHC__numulikeCChigh_Ereco")); // +2sigma
  TH1D *h_univ_p3 = static_cast<TH1D*>(f_univ->Get("spectra_var_12_pdfts_ob_rf_sbn_nd__BNB_FHC__numulikeCChigh_Ereco")); // +3sigma

  std::vector<TH1D*> h_univs({h_univ_m3, h_univ_m2, h_univ_m1, h_univ_n0, h_univ_p1, h_univ_p2, h_univ_p3});

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
  TFile f_out(output_file,"RECREATE");
  for(unsigned int h = 0; h < h_univs.size(); ++h){

    // Translate iterator to number of sigma
    const int n_sigma = GetNSigmaFromIterator(h,verbose);

    // Get the histograms
    TH1D *h_universe = h_univs.at(h);
    TH1D *h_tweak    = h_tweaks.at(h);
    h_universe->GetXaxis()->SetRangeUser(0.,3.);
    h_tweak->GetXaxis()->SetRangeUser(0.,3.);

    // Now make the canvas, legend and sort out the pads
    TCanvas *c = new TCanvas("c","",600,1000);
    TLegend *l = new TLegend(0.45,0.62,0.86,0.87);
    l->SetBorderSize(0);
    l->SetTextFont(132);
    l->AddEntry(h_tweak, "Spectra from tweaks", "l");
    l->AddEntry(h_universe, "Spectra from universes", "l");
    
    // The upper pad (spectra)
    TPad *pad1 = new TPad("pad1","",0.0,0.35,1.0,1.0);
    pad1->SetBottomMargin(0.02);
    pad1->SetTopMargin(0.1);
    pad1->SetGridx();
    pad1->Draw();
    pad1->cd();

    // Format the spectra plots and draw
    SetSpectraFormatting(h_tweak,h_universe,verbose);
    TString title = GetTitle(param, n_sigma);
    TLatex * l_title = new TLatex(1.44,3.35e6,title.Data());
    l_title->SetTextSize(0.05);
    l_title->SetTextAlign(22);
    gStyle->SetLabelFont(132);
    h_tweak->Draw();
    h_universe->Draw("same");
    l->Draw("same");
    l_title->Draw("same");
    
    // Update pad and return to main canvas
    pad1->Modified();
    c->cd();
    
    // The lower pad (ratio plot)
    TPad *pad2 = new TPad("pad2","",0.0,0.0,1.0,0.35);
    pad2->SetTopMargin(0.02);
    pad2->SetBottomMargin(0.22);
    pad2->SetGridx();
    pad2->SetGridy();
    pad2->Draw();
    pad2->cd();
   
    // Construct the ratio plot
    TH1D *h_ratio = static_cast<TH1D*>(h_tweak->Clone("h_ratio"));
    h_ratio->Add(h_universe,-1);
    h_ratio->Divide(h_universe);

    // Set the errors and scale to percentage
    SetRatioBinErrors(h_universe, h_tweak, h_ratio, verbose);
    h_ratio->Scale(100);

    // Format the ratio plot and draw
    SetRatioPlotFormatting(h_ratio,verbose);
    h_ratio->Draw("e2");
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
  }

  f_out.Write();
  f_out.Close();
  return;
}
// ----------------------------------------------------------------------------------
const TString GetTweaksFileName(const char* param, 
                                const int &nsigma,
                                const TString &location){
  TString name(tweakFilePattern);
  name = GetStringReplacements(name,param,"","",nsigma);
  name.Append("sigma.root");
  name.Prepend(location);
  return name;
}
// ----------------------------------------------------------------------------------
const TString GetSplineFileName(const char* param, 
                                const char* sample, 
                                const char* beam,
                                const TString &location){
  TString name(splineFilePattern);
  name = GetStringReplacements(name,param,sample,beam);
  name.Append("_spectra.root");
  name.Prepend(location);
  return name;
}
// ----------------------------------------------------------------------------------
const TString GetStringReplacements(const TString &pattern, 
                                    const char* param="", 
                                    const char* sample="", 
                                    const char* beam="", 
                                    const int&  nsigma=1){
  TString name(pattern);
  name = name.ReplaceAll("[BEAM]",   beam);
  name = name.ReplaceAll("[SAMPLE]", sample);
  name = name.ReplaceAll("[PARAM]",  param);
  name = name.ReplaceAll("[NSIG]",   std::to_string(nsigma).c_str());  
  return name;
}
// ----------------------------------------------------------------------------------
void CheckFiles(TFile *f_univ,
                TFile *f_1sig, 
                TFile *f_2sig, 
                TFile *f_3sig,
                const std::string &universe_filename,
                const std::string &tweaks_1sig_filename,
                const std::string &tweaks_2sig_filename,
                const std::string &tweaks_3sig_filename,
                const bool &verbose = false){
  if(!f_univ->IsOpen()){
    std::cerr << " Error: Couldn't open universe file with name: " << universe_filename << std::endl;
    exit(1);
  }
  if(verbose) std::cout << " Successfully opened universe file with name: " << universe_filename << std::endl;

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

  // The ratio bins are filled as content = ((h_tw-h_un)/h_un)*100
  // The errors in the ratio bins are as follows
  // (sig_c/c)^2 = (sqrt(nt+nu)/(nt-nu))^2 + 1/nu
  // sig_c = c *sqrt((nt+nu)/pow(nt-nu,2) + 1/nu)
  
  // Loop over x bins and make the calculation
  // There should be the same number of bins in all histograms
  for (int ibin = 1 ; ibin <= h_tw->GetXaxis()->GetNbins(); ibin++) {
    double error_ratio = 0.;
    double content_tweak    = h_tw->GetBinContent(ibin);
    double content_universe = h_un->GetBinContent(ibin);
    double content_ratio    = h_ra->GetBinContent(ibin);

    error_ratio = abs( content_ratio * sqrt( ( content_tweak+content_universe ) 
                                             / pow(abs(content_tweak-content_universe),2) 
                                             + 1./static_cast<double>(content_universe) ) );
    h_ra->SetBinError(ibin,error_ratio);

    if(verbose)
      std::cout << " Setting the error on bin: " << ibin << " to be: " << error_ratio << std::endl;
  }
  return;
}
// ----------------------------------------------------------------------------------
void SetRatioPlotFormatting(TH1D* h, 
                            const bool &verbose = false){
  h->SetStats(0);
  h->SetTitle("");
  h->GetYaxis()->SetMaxDigits(3);
  h->GetYaxis()->SetTitle("#Delta Rate / Rate_{Universe}, %");
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
  h->SetLineColor(kPink+5);
  h->SetFillColor(kPink+5);
  h->SetFillStyle(3001);
  h->SetLineStyle(1);
  h->SetLineWidth(2);
  
  return;
}
// ----------------------------------------------------------------------------------

// Set the spectra formatting
void SetSpectraFormatting(TH1D* h_tweak, 
                          TH1D* h_universe, 
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

  return;
}
TString GetTitle(const char* param, 
                 const int &nsigma){

  // Construct the title
  // First remove anything after an underscore in the parameter name, this is usually more than we need to know for the title
  TString title(param);
  size_t underscore = title.Last('_');
  size_t length     = title.Length();
  title.Remove(underscore,length);
  title.Prepend("Spline validation for ");
  title.Append(" at ");
  title.Append(std::to_string(nsigma).c_str());
  title.Append(" #sigma");

  return title;
}
