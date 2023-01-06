#include <iostream>
#include <algorithm>
#include <iterator>

#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPad.h"
#include "TString.h"
#include "TFrame.h"
#include "TF1.h"

#include "TGraph.h"
#include "TStyle.h"
#include "TAxis.h"
#include "TColor.h"
 
void spectra_drawer(
    const char *nom_spectra,
    const char *osc_spectra = ""){

// get files
TFile *fnom_spectra   = new TFile(nom_spectra, "read");
bool osc_file(osc_spectra[0]);
TFile *fosc_spectra;
if(osc_file){
  fosc_spectra   = new TFile(osc_spectra, "read");
}

// get tweaked files
TFile *fprefit   = new TFile("/sbnd/app/users/tham/VALOR_master/pre_post_fit/fd_tweak_pdf_output_prefit.root", "read");
TH1D *hp1    = (TH1D*) fprefit->Get("env_sb_BNB_FHC_numuCCincl_p1");
TH1D *hm1    = (TH1D*) fprefit->Get("env_sb_BNB_FHC_numuCCincl_m1");

std::cout << fosc_spectra->GetName() << std::endl;
//Find substrings and check the selected nuE sample-type if necessary
string str_numu       = "numu";
string str_nue        = "nue";
std::string input_file(nom_spectra);
size_t found_nue  = input_file.find(str_nue);
size_t found_numu = input_file.find(str_numu);

const char*  spectrum_sbnd; const char* spectrum_ub; const char* spectrum_icarus;
// found numu
if(found_nue == string::npos && found_numu != string::npos){
  spectrum_sbnd   = "valor_pdft_sb_rf_sbn_nd__BNB_FHC__numuCCincl_Ereco;1";
  spectrum_ub     = "valor_pdft_sb_rf_sbn_uboone__BNB_FHC__numuCCincl_Ereco;1";
  spectrum_icarus = "valor_pdft_sb_rf_sbn_icarus__BNB_FHC__numuCCincl_Ereco;1";
}
// found nue
else if(found_nue != string::npos){
  spectrum_sbnd   = "valor_pdft_sb_rf_sbn_nd__BNB_FHC__nuelikeCChigh_Ereco;1";
  spectrum_ub     = "valor_pdft_sb_rf_sbn_uboone__BNB_FHC__nuelikeCChigh_Ereco;1";
  spectrum_icarus = "valor_pdft_sb_rf_sbn_icarus__BNB_FHC__nuelikeCChigh_Ereco;1";
}
// found 
else{std::cerr << "file not recognized" << std::endl;}
 
TH1D *h_nom_sbnd   = (TH1D*) fnom_spectra->Get(spectrum_sbnd);
TH1D *h_nom_ub     = (TH1D*) fnom_spectra->Get(spectrum_ub);
TH1D *h_nom_icarus = (TH1D*) fnom_spectra->Get(spectrum_icarus);

std::cout << h_nom_sbnd->Integral() << std::endl;
TH1D *h_osc_sbnd; TH1D *h_osc_ub; TH1D *h_osc_icarus;
if(osc_file){
  h_osc_sbnd   = (TH1D*) fosc_spectra->Get(spectrum_sbnd);
  h_osc_ub     = (TH1D*) fosc_spectra->Get(spectrum_ub);
  h_osc_icarus = (TH1D*) fosc_spectra->Get(spectrum_icarus);
}

int nbins = h_nom_sbnd->GetNbinsX();

// Divide hist by bin energy
for(auto i = 1; i < nbins; i++){
  double bin_content_nom_sbnd   = h_nom_sbnd->GetBinContent(i);
  double bin_content_nom_ub     = h_nom_ub->GetBinContent(i);
  double bin_content_nom_icarus = h_nom_icarus->GetBinContent(i);
  double bin_content_osc_sbnd   = h_osc_sbnd->GetBinContent(i);
  double bin_content_osc_ub     = h_osc_ub->GetBinContent(i);
  double bin_content_osc_icarus = h_osc_icarus->GetBinContent(i);

  h_nom_sbnd  ->SetBinContent(i, bin_content_nom_sbnd/h_nom_sbnd->GetBinWidth(i));
  h_nom_ub    ->SetBinContent(i, bin_content_nom_ub/h_nom_ub->GetBinWidth(i));
  h_nom_icarus->SetBinContent(i, bin_content_nom_icarus/h_nom_icarus->GetBinWidth(i));
  
  if(osc_file){
  h_osc_sbnd  ->SetBinContent(i, bin_content_osc_sbnd/h_osc_sbnd->GetBinWidth(i));
  h_osc_ub    ->SetBinContent(i, bin_content_osc_ub/h_osc_ub->GetBinWidth(i));
  h_osc_icarus->SetBinContent(i, bin_content_osc_icarus/h_osc_icarus->GetBinWidth(i));
  }
}

TCanvas *c_sbnd = new TCanvas();
h_nom_sbnd->SetLineWidth(3);
h_nom_sbnd->GetXaxis()->SetRangeUser(0,3);
h_nom_sbnd->GetXaxis()->SetTitle("Reco. E_{#nu} (GeV)");
h_nom_sbnd->Draw();


TCanvas *c_ub = new TCanvas();
h_nom_ub->SetLineWidth(3);
h_nom_ub->GetXaxis()->SetRangeUser(0,3);
h_nom_ub->GetXaxis()->SetTitle("Reco. E_{#nu} (GeV)");
h_nom_ub->Draw();

TCanvas *c_icarus = new TCanvas();
h_nom_icarus->SetLineWidth(3);
h_nom_icarus->GetXaxis()->SetRangeUser(0,3);
h_nom_icarus->GetXaxis()->SetTitle("Reco. E_{#nu} (GeV)");
h_nom_icarus->Draw();

c_sbnd->cd();
h_osc_sbnd->SetLineColor(kRed);
h_osc_sbnd->SetLineStyle(7);
h_osc_sbnd->SetLineWidth(3);
h_osc_sbnd->Draw("same");
TLegend *l_sbnd = new TLegend(0.7,0.7);
l_sbnd->AddEntry(h_nom_sbnd, "Nominal SBND", "L");
l_sbnd->AddEntry(h_osc_sbnd, "Oscillated SBND", "L");
l_sbnd->SetBorderSize(0);
l_sbnd->Draw("same");

c_ub->cd();
h_osc_ub->SetLineColor(kRed);
h_osc_ub->SetLineStyle(7);
h_osc_ub->SetLineWidth(3);
h_osc_ub->Draw("same");

c_icarus->cd();
h_osc_icarus->SetLineColor(kRed);
h_osc_icarus->SetLineStyle(7);
h_osc_icarus->SetLineWidth(3);
h_osc_icarus->GetXaxis()->SetRangeUser(0,2.99);
h_osc_icarus->Draw("same");
TLegend *l_icarus = new TLegend(0.7,0.7);
l_icarus->AddEntry(h_nom_icarus, "Nominal ICARUS", "L");
l_icarus->AddEntry(h_osc_icarus, "#splitline{Oscillated ICARUS}{sin^{2}2#theta_{#mue} = 0.003, #Deltam^{2}_{41} = 1.32 eV^{2}}", "L");
l_icarus->SetBorderSize(0);
l_icarus->Draw("same");

TH1D *h_nom_icarus_clone = (TH1D*) h_nom_icarus->Clone();
TGraphAsymmErrors *h_errors = new TGraphAsymmErrors(h_nom_icarus_clone);

for(auto i = 0; i < nbins; i++){
  double bin_content_hp1   = hp1->GetBinContent(i);
  double bin_content_hm1   = hm1->GetBinContent(i);

  hp1  ->SetBinContent(i, bin_content_hp1/hp1->GetBinWidth(i));
  hm1  ->SetBinContent(i, bin_content_hm1/hm1->GetBinWidth(i));
  
  double yp = hp1->GetBinContent(i) - h_nom_icarus->GetBinContent(i);
  double ym = h_nom_icarus->GetBinContent(i) - hm1->GetBinContent(i); 
    
  h_errors->SetPointEYhigh(i, yp);
  h_errors->SetPointEYlow(i, ym);

}







TCanvas *c = new TCanvas();
h_nom_icarus->Draw();
//h_errors->GetXaxis()->SetRangeUser(0,3);
h_errors->Draw("E2, same");
h_errors->SetFillColor(kAzure+7);
h_errors->SetFillStyle(3017);

}














