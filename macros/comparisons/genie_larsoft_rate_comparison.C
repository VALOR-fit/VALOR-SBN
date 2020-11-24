#include "TFile.h"
#include "TH1.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TStyle.h"

#include <cmath>
#include <iostream>

void SetSpectraFormatting(TH1D* hGen, 
                          TH1D* hLAr);

void SetRatioPlotFormatting(TH1D* h);

void genie_larsoft_rate_comparison(
    const char *genie="/sbnd/app/users/rsjones/VALOR/VALOR-SBN/mock_data_challenge/inclusive/Nov2020/spectra/spectra_genie_g1810a0211a_1000flux_active_totals.root", 
    //const char *larsoft="/sbnd/app/users/rsjones/VALOR/VALOR-SBN/mock_data_challenge/inclusive/Nov2020/spectra/spectra_genie_g1810a0211a_100flux_totals.root", 
    const char *larsoft="/sbnd/app/users/rsjones/VALOR/VALOR-SBN/mock_data_challenge/inclusive/Sept2020/spectra/spectra_total_nd_2020a1.root",
    const char *output="genie_larsoft_spectral_comparisons.root"
    ){

  TFile *fGen = new TFile(genie,"READ");
  TFile *fLAr = new TFile(larsoft,"READ");

  TH1D *hGen = static_cast<TH1D*>(fGen->Get("sbn_nd_total"));
  TH1D *hLAr = static_cast<TH1D*>(fLAr->Get("sbn_nd_total"));

  TH1D *hRatio = static_cast<TH1D*>(hGen->Clone("sbn_nd_ratio"));
  hRatio->Divide(hLAr);

  TCanvas *c = new TCanvas("c","",600,1000);
  TLegend *l = new TLegend(0.54,0.59,0.94,0.89);
  l->SetBorderSize(0);
  l->SetFillStyle(0);
  l->SetTextFont(132);
  l->SetTextSize(0.05);
  l->AddEntry(hGen, "LArSoft Generation", "l");
  l->AddEntry(hLAr, "GENIE Generation", "l");

  // The upper pad (spectra)
  TPad *pad1 = new TPad("pad1","",0.0,0.35,1.0,1.0);
  pad1->SetBottomMargin(0.02);
  pad1->SetTopMargin(0.05);
  pad1->SetRightMargin(0.02);
  pad1->Draw();
  pad1->cd();

  SetSpectraFormatting(hGen,hLAr);
  hGen->Draw();
  hLAr->Draw("same");
  l->Draw("same");

  double perc_rate_diff = (abs(hGen->Integral("width")-hLAr->Integral("width"))/static_cast<double>(hLAr->Integral("width")))*100;
  std::cout << " Percentage rate difference between GENIE and LArSoft-generated spectra is: " << perc_rate_diff << std::endl;
  std::cout << " GENIE integrated rate:   " << hGen->Integral("width") << std::endl;
  std::cout << " LArSoft integrated rate: " << hLAr->Integral("width") << std::endl;

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

  SetRatioPlotFormatting(hRatio);
  hRatio->Draw("hist same");
   
  // Update the pad and canvas
  pad2->Modified();
  c->Update();

  // Write to the file
  TFile *fOut = new TFile(output,"RECREATE");
  c->Write();
  fOut->Close();

}
void SetSpectraFormatting(TH1D* hGen, 
                          TH1D* hLAr){ 
  // Now set everything
  hGen->SetStats(0);
  hGen->SetTitle("");
  hGen->GetXaxis()->SetLabelSize(0);
  hGen->GetYaxis()->SetMaxDigits(3);
  hGen->GetYaxis()->SetTitle("Event rate / 1 GeV");
  hGen->GetYaxis()->SetTitleFont(132);
  hGen->GetYaxis()->SetLabelFont(132);
  hGen->GetYaxis()->SetTitleSize(0.05);
  hGen->GetYaxis()->SetLabelSize(0.04);
  hGen->GetYaxis()->SetTitleOffset(1);
  hGen->SetLineColor(kAzure+7);
  hGen->SetLineStyle(7);
  hGen->SetLineWidth(2);
  hLAr->SetLineColor(kOrange+2);
  hLAr->SetLineStyle(5);
  hLAr->SetLineWidth(2);

  const double max = std::max(hGen->GetMaximum(),hLAr->GetMaximum()) * 1.1;
  hGen->GetXaxis()->SetRangeUser(0,3.);
  hGen->GetYaxis()->SetRangeUser(0,max);

  return;
}
void SetRatioPlotFormatting(TH1D* h){ 
  h->SetStats(0);
  h->SetTitle("");
  h->GetYaxis()->SetMaxDigits(3);
  h->GetYaxis()->SetTitleFont(132);
  h->GetYaxis()->SetLabelFont(132);
  h->GetYaxis()->SetTitleSize(0.075);
  h->GetYaxis()->SetTitleOffset(0.65);
  h->GetYaxis()->SetLabelSize(0.075);
  h->GetXaxis()->SetTitleFont(132);
  h->GetXaxis()->SetLabelFont(132);
  h->GetXaxis()->SetTitleSize(0.1);
  h->GetXaxis()->SetTitleOffset(0.9);
  h->GetXaxis()->SetLabelSize(0.075);
  h->SetLineColor(kPink+5);
  h->SetLineStyle(1);
  h->SetLineWidth(2);
  h->GetXaxis()->SetTitle("Reconstructed neutrino energy [GeV]");
  h->GetYaxis()->SetTitle("GENIE/LArSoft");

  double min = 0;
  double max = 0;
  if(h->GetMinimum() < 0)
    min = h->GetMinimum() * 1.2;
  else
    min = h->GetMinimum() * 0.8;

  if(h->GetMaximum() > 0)
    max = h->GetMaximum() * 1.2;
  else
    max = h->GetMaximum() * 0.8;

  h->GetXaxis()->SetRangeUser(0,3);
  h->GetYaxis()->SetRangeUser(min,max);
  return;
}
