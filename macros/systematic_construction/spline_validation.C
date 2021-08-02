/**
 *
 * Macro to overlay n-sigma variations of individual parameter tweaks 
 * from universes vs produced by the splines for validation
 *
 * R.J 2020
 *
 **/

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
TString tweakFilePattern("[PARAM]_[SAMPLE]_[NSIG]");

// Name filling functions
const TString GetTweaksFileName(const char* param, 
                                const char* sample, 
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
                            const bool &verbose = false,
                            std::string format  = "pdf");

// Set the spectra formatting
void SetSpectraFormatting(TH1D *h_tweak, 
                          TH1D *h_universe, 
                          const TString &detector,
                          const double &max,
                          const bool &verbose = false,
                          std::string format  = "pdf");

// Get the histogram titles
TString GetTitle(const char* param, 
                 const int &nsigma);
// Main
void spline_validation(const char* param, 
                       const char* sample="numuCCincl", 
                       const char* beam="BNB_FHC", 
                       const TString &detector="sbn_nd", 
                       const TString &tweaks_location="", 
                       const TString &spline_location="",
                       const bool &all_in_one = false, // If all the sigma variations were produced in a single file
                       const double &per_energy_gev=1., // y-axis scaling
                       const bool &verbose=false,
                       TString tag="tweaks", // This is the tag from your filename
                       const char* png_location="./",
                       const char* output_file="spline_validation_plots.root"){

  // Get spectra from various places
  // Universe spectra written directly from templates
  size_t len = tag.Length();
  if(tag.Last('_') != len) tag.Append("_");

  // Get filenames
  const std::string universe_filename   (GetSplineFileName(param,sample,beam,detector,spline_location));
  const std::string tweaks_nom_filename (GetTweaksFileName(param,sample,tag,0,tweaks_location,all_in_one));
  const std::string tweaks_1sig_filename(GetTweaksFileName(param,sample,tag,1,tweaks_location,all_in_one));
  const std::string tweaks_2sig_filename(GetTweaksFileName(param,sample,tag,2,tweaks_location,all_in_one));
  const std::string tweaks_3sig_filename(GetTweaksFileName(param,sample,tag,3,tweaks_location,all_in_one));

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

  // Cast the parameter and sample names to strings
  std::string s_param(param);
  std::string s_sample(sample);
  std::string s_detector(detector);
  std::string s_location(png_location);
  
  // Tweaked spectra from splines
  TH1D *h_tweak_m3 = static_cast<TH1D*>(f_3sig->Get(("env_sb_BNB_FHC_"+s_sample+"_m3;1").c_str())); // -3 sigma
  TH1D *h_tweak_m2 = static_cast<TH1D*>(f_2sig->Get(("env_sb_BNB_FHC_"+s_sample+"_m2;1").c_str())); // -2 sigma
  TH1D *h_tweak_m1 = static_cast<TH1D*>(f_1sig->Get(("env_sb_BNB_FHC_"+s_sample+"_m1;1").c_str())); // -1 sigma
  //TH1D *h_tweak_n0 = static_cast<TH1D*>(f_nom->Get(("env_sb_BNB_FHC_"+s_sample+"_p0;1").c_str())); //  NOMINAL
  TH1D *h_tweak_n0 = static_cast<TH1D*>(f_nom->Get(("env_sb_BNB_FHC_"+s_sample+"_nom;1").c_str())); //  NOMINAL
  TH1D *h_tweak_p1 = static_cast<TH1D*>(f_1sig->Get(("env_sb_BNB_FHC_"+s_sample+"_p1;1").c_str())); // +1 sigma
  TH1D *h_tweak_p2 = static_cast<TH1D*>(f_2sig->Get(("env_sb_BNB_FHC_"+s_sample+"_p2;1").c_str())); // +2 sigma
  TH1D *h_tweak_p3 = static_cast<TH1D*>(f_3sig->Get(("env_sb_BNB_FHC_"+s_sample+"_p3;1").c_str())); // +3 sigma

  // There is no +3 sigma universe variation for expskin so it is a duplicate of +2 sigma for now

  std::vector<TH1D*> h_tweaks({h_tweak_m3, h_tweak_m2, h_tweak_m1, h_tweak_n0, h_tweak_p1, h_tweak_p2, h_tweak_p3});
  std::vector<bool> h_valid;
  unsigned int n_hist = 0;
  for(TH1D* h : h_tweaks){
    if(h != nullptr){
      h_valid.push_back(true);
      if(verbose)
        std::cout << " Current histogram: " << h->GetName() << " exists, so will plot" << std::endl;
    }
    else{
      h_valid.push_back(false);
      std::cout << " Current histogram: " << n_hist << " does not exist, so cannot plot" << std::endl;
    }
    n_hist++;
  }

  // Universe spectra for -3 -> +3 sigma
  TH1D *h_univ_m3 = static_cast<TH1D*>(f_univ->Get(("spectra_var_m3_pdfts_ob_rf_"+s_detector+"__BNB_FHC__"+s_sample+"_Ereco").c_str()));  // -3sigma
  TH1D *h_univ_m2 = static_cast<TH1D*>(f_univ->Get(("spectra_var_m2_pdfts_ob_rf_"+s_detector+"__BNB_FHC__"+s_sample+"_Ereco").c_str()));  // -2sigma
  TH1D *h_univ_m1 = static_cast<TH1D*>(f_univ->Get(("spectra_var_m1_pdfts_ob_rf_"+s_detector+"__BNB_FHC__"+s_sample+"_Ereco").c_str()));  // -1sigma
  TH1D *h_univ_n0 = static_cast<TH1D*>(f_univ->Get(("spectra_var_0_pdfts_ob_rf_"+s_detector+"__BNB_FHC__"+s_sample+"_Ereco").c_str()));  //  NOMINAL
  TH1D *h_univ_p1 = static_cast<TH1D*>(f_univ->Get(("spectra_var_1_pdfts_ob_rf_"+s_detector+"__BNB_FHC__"+s_sample+"_Ereco").c_str()));  // +1sigma
  TH1D *h_univ_p2 = static_cast<TH1D*>(f_univ->Get(("spectra_var_2_pdfts_ob_rf_"+s_detector+"__BNB_FHC__"+s_sample+"_Ereco").c_str())); // +2sigma
  TH1D *h_univ_p3 = static_cast<TH1D*>(f_univ->Get(("spectra_var_3_pdfts_ob_rf_"+s_detector+"__BNB_FHC__"+s_sample+"_Ereco").c_str())); // +3sigma

  std::vector<TH1D*> h_univs({h_univ_m3, h_univ_m2, h_univ_m1, h_univ_n0, h_univ_p1, h_univ_p2, h_univ_p3});

  double nom_univ_rate  = h_univ_n0->Integral();
  double nom_valor_rate = h_tweak_n0->Integral();

  TVectorD knot_vals(*static_cast<TVectorD*>(f_univ->Get("actual_knot_values")));

  // Make sure the vectors are the same size for making ratio plots later
  if(h_univs.size() != h_tweaks.size()){
    std::cerr << " Error: Number of entries in the universe histogram is: " << h_univs.size() << " and doesn't match the number in the tweaks vector: " << h_tweaks.size() << std::endl;
    exit(1);
  }
  // If necessary normalise to some energy range
  // Make sure the histogram is valid
  if (per_energy_gev > 0) {
    // Fix the binning if necessary
    unsigned int n = 0;
    for(TH1D *h : h_tweaks){
      if(!h_valid.at(n)) continue;
      FixBinning(h,per_energy_gev);
      n++;
    }
    n = 0;
    for(TH1D *h : h_univs){
      if(!h_valid.at(n)) continue;
      FixBinning(h,per_energy_gev);
      n++;
    }
  }
  // Get the maxium value of the +3sigma spectra to set the maximum value on the y-axis of all the plots
  const double max_y = std::max(h_univs.at(h_univs.size()-1)->GetMaximum(),h_tweaks.at(h_tweaks.size()-1)->GetMaximum()) * 1.5;

  // Now loop over the size of the vectors and make the canvases and subpads then save each into a root file
  // Append parameter name to output filename and open
  std::string s_output_file(output_file);
  std::string param_filename = "root/"+s_param+"_"+s_sample+"_"+s_output_file; 
  TFile f_out(param_filename.c_str(),"RECREATE");
 
  // For the PDF
  TString pdf_filename(output_file);
  pdf_filename.ReplaceAll(".root",".pdf");
  pdf_filename.Prepend("_");
  pdf_filename.Prepend(s_sample);
  pdf_filename.Prepend("_");
  pdf_filename.Prepend(s_param);
  pdf_filename.Prepend("pdfs/");

  for(unsigned int h = 0; h < h_univs.size(); ++h){

    // Make sure the current histogram exists
    if(!h_valid.at(h)) continue;

    // Translate iterator to number of sigma
    const int n_sigma     = GetNSigmaFromIterator(h,verbose);
    double var_univ_rate  = h_univs.at(h)->Integral("width");
    double var_valor_rate = h_tweaks.at(h)->Integral("width");

    // For the PNG
    TString png_filename(output_file);
    png_filename.ReplaceAll(".root",".png");
    png_filename.Prepend("sigma_");
    png_filename.Prepend(std::to_string(n_sigma));
    png_filename.ReplaceAll("-","m");
    png_filename.Prepend("_");
    png_filename.Prepend(s_sample);
    png_filename.Prepend("_");
    png_filename.Prepend(s_param);
    png_filename.Prepend(s_location);

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
    TCanvas *c = new TCanvas("c","",800,1000);
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
    SetSpectraFormatting(h_tweak,h_universe,detector,max_y,verbose,"png");
    TString title = GetTitle(param, n_sigma);
    TLatex * l_title = new TLatex();
    l_title->SetTextSize(0.05);
    l_title->SetTextAlign(22);
    h_tweak->Draw();
    h_universe->Draw("same");
    l->Draw("same");
    l_title->DrawLatex(1.49,max_y*0.9,title.Data());

    // Now write integrated universe rate difference from nominal
    TString var("Total universe variation from nominal: ");
    int var_univ_nom = static_cast<int>(std::abs(var_univ_rate-nom_univ_rate));
    var.Append(std::to_string(var_univ_nom));
    TLatex * l_var = new TLatex();
    l_var->SetTextSize(0.035);
    l_var->SetTextAlign(22);
    l_var->DrawLatex(1.49,max_y*0.86,var.Data());
   
    TString var_val("Total VALOR variation from nominal: ");
    int var_val_nom = static_cast<int>(std::abs(var_valor_rate-nom_valor_rate));
    var_val.Append(std::to_string(var_val_nom));
    TLatex * l_var_val = new TLatex();
    l_var_val->SetTextSize(0.035);
    l_var_val->SetTextAlign(22);
    l_var_val->DrawLatex(1.49,max_y*0.82,var_val.Data());
   
    TString diff("Total universe variation from VALOR: ");
    int diff_val_univ = static_cast<int>(std::abs(var_univ_rate-var_valor_rate));
    diff.Append(std::to_string(diff_val_univ));
    TLatex * l_diff = new TLatex();
    l_diff->SetTextSize(0.035);
    l_diff->SetTextAlign(22);
    l_diff->DrawLatex(1.49,max_y*0.78,diff.Data());
   
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
    SetRatioPlotFormatting(h_ratio_band,true,verbose,"pdf");
    h_ratio_band->Draw("e2");
    
    // Draw the ratio plot
    SetRatioPlotFormatting(h_ratio,false,verbose,"pdf");
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

    // Now write to a PDF
    if(h == 0){
      TString tempPDF(pdf_filename);
      tempPDF.Append("(");
      c->Print(tempPDF.Data(),"pdf");
    }

    else if(h == h_univs.size()-1){
      TString tempPDF(pdf_filename);
      tempPDF.Append(")");
      c->Print(tempPDF.Data(),"pdf");
    }

    else
      c->Print(pdf_filename.Data(),"pdf");

    // Update the formatting for the pngs and redraw before saving
    // Format the spectra plots and draw
    pad1->cd();
    SetSpectraFormatting(h_tweak,h_universe,detector,max_y,verbose,"png");
    pad1->Modified();
    c->cd();

    // Format the ratio plot and error bands and draw
    pad2->cd();
    SetRatioPlotFormatting(h_ratio_band,true,verbose,"png");
    
    // Draw the ratio plot
    SetRatioPlotFormatting(h_ratio,false,verbose,"png");
    pad2->Modified();

    // Update the canvas
    c->Update();

    c->SaveAs(png_filename.Data());
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
                                const char* sample, 
                                TString &tag,
                                const int &nsigma,
                                const TString &location,
                                const bool &all){
  TString name(tweakFilePattern);
  if(!all){
    std::cout << " Not looking at a file with all tweaks included" << std::endl;
    name = GetStringReplacements(name,param,sample,"","",nsigma);
    name.Append("sigma.root");
    name.Prepend(tag);
    name.Prepend(location);
  }
  else{
    std::cout << " Looking at a file with all tweaks included" << std::endl;
    name = GetStringReplacements(name,param,sample);
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
    double deltaN     = abs(N_tweak-N_universe)+0.00001; // Add a small number so we don't end up dividing by zero when our agreement is just too good..
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
                            const bool &verbose = false,
                            std::string format  = "pdf"){
  h->SetStats(0);
  h->SetTitle("");
  h->GetYaxis()->SetMaxDigits(3);

  if(format == "pdf"){
    h->GetYaxis()->SetTitle("\\Delta Rate / Rate_{Average}, %");
    h->GetXaxis()->SetTitle("Reconstructed E_{\\nu} [GeV]");
  }
  else if(format  == "png"){
    h->GetYaxis()->SetTitle("#Delta Rate / Rate_{Average}, %");
    h->GetXaxis()->SetTitle("Reconstructed E_{#nu} [GeV]");
  }

  h->GetYaxis()->SetTitleFont(132);
  h->GetYaxis()->SetLabelFont(132);
  h->GetYaxis()->SetTitleSize(0.1);
  h->GetYaxis()->SetTitleOffset(0.55);
  h->GetYaxis()->SetLabelSize(0.075);
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
                          const double &max,
                          const bool &verbose = false,
                          std::string format  = "pdf"){
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
  h_tweak->GetYaxis()->SetRangeUser(0,max);

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
