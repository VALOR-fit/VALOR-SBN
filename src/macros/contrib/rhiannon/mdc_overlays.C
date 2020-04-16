#include <iostream>
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
void mdc_overlays() {

  // tb = true baseline
  // sb = spline baseline
  TFile *f_mdc1     = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/mock_data_challenge/true_baseline/spectra/mdc1-nd-data-postfit-prefit_sb_BNB_FHC_numulikeCChigh_envelope.root","read");
  TFile *f_mdc2     = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/mock_data_challenge/dataset_2/spectra/mdc2-nd-data-postfit-prefit_sb_BNB_FHC_numulikeCChigh_envelope.root","read");
  TFile *f_mdc_caf = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/mock_data_challenge/overlays/CAFAna/mock_spec_scaled.root","read");

  TH1D *mdc1_postfit_hist     = (TH1D*) f_mdc1->Get("postfit_hist");
  TH1D *mdc2_postfit_hist     = (TH1D*) f_mdc2->Get("postfit_hist");
  TH1D *mdc1_prefit_hist      = (TH1D*) f_mdc1->Get("prefit_hist");
  TH1D *mdc2_prefit_hist      = (TH1D*) f_mdc2->Get("prefit_hist");
  TH1D *mdc1_data_hist        = (TH1D*) f_mdc1->Get("data_hist");
  TH1D *mdc2_data_hist        = (TH1D*) f_mdc2->Get("data_hist");
  TH1D *mdc1_postfit_hist_caf = (TH1D*) f_mdc_caf->Get("sbnd_postfit_1");
  TH1D *mdc2_postfit_hist_caf = (TH1D*) f_mdc_caf->Get("sbnd_postfit_2");

  TCanvas *c1 = new TCanvas("c1","c1",20,20,700,900);
  c1->SetRightMargin(0.08);
  c1->SetLeftMargin(0.12);
  c1->SetTopMargin(0.08);
  c1->SetBottomMargin(0.12);
  
  // Add legend
  TLegend *leg = new TLegend(0.49,0.62,0.94,0.87);
  leg->SetEntrySeparation(0.01);
  leg->SetTextFont(132);
  leg->SetTextColor(1);
  leg->SetFillStyle(0);
  leg->SetLineWidth(0);

  leg->AddEntry(mdc1_data_hist,"Mock data 1", "l");
  leg->AddEntry(mdc1_postfit_hist,"VALOR Postfit 1", "l");
  leg->AddEntry(mdc1_postfit_hist_caf,"CAFAna Postfit 1", "l");
  mdc1_postfit_hist->Draw();
  mdc1_data_hist->Draw("same");
  mdc1_postfit_hist_caf->Draw("same");
  mdc1_data_hist->SetLineStyle(1);
  mdc1_data_hist->SetLineWidth(1);
  mdc1_postfit_hist->SetLineStyle(2);
  mdc1_postfit_hist->SetLineWidth(2);
  mdc1_postfit_hist_caf->SetLineStyle(7);
  mdc1_postfit_hist_caf->SetLineWidth(2);
  mdc1_postfit_hist_caf->SetLineColor(kAzure+7);

  // add the legend
  leg->Draw("same");
  
  // Add label to colour legend
  c1->SaveAs("valor_cafana_overlays_1.root");
  c1->Clear();

  leg->Clear();
  
  leg->AddEntry(mdc2_data_hist,"Mock data 2", "l");
  leg->AddEntry(mdc2_postfit_hist,"VALOR Postfit 2", "l");
  leg->AddEntry(mdc2_postfit_hist_caf,"CAFAna Postfit 2", "l");

  mdc2_postfit_hist->Draw();
  mdc2_data_hist->Draw("same");
  mdc2_postfit_hist_caf->Draw("same");
  mdc2_data_hist->SetLineStyle(1);
  mdc2_data_hist->SetLineWidth(1);
  mdc2_postfit_hist->SetLineStyle(2);
  mdc2_postfit_hist->SetLineWidth(2);
  mdc2_postfit_hist_caf->SetLineStyle(7);
  mdc2_postfit_hist_caf->SetLineWidth(2);
  mdc2_postfit_hist_caf->SetLineColor(kAzure+7);

  // add the legend
  leg->Draw("same");
  
  // Add label to colour legend
  c1->SaveAs("valor_cafana_overlays_2.root");
  c1->Clear();

  leg->Clear();
  // Normal ratios
  TH1D *mdc1_nominal_ratio = (TH1D*)mdc1_data_hist->Clone("mdc1_nominal_ratio");
  TH1D *mdc2_nominal_ratio = (TH1D*)mdc2_data_hist->Clone("mdc2_nominal_ratio");
  mdc1_nominal_ratio->Divide(mdc1_prefit_hist);
  mdc2_nominal_ratio->Divide(mdc2_prefit_hist);

  double maxn = std::max(mdc1_nominal_ratio->GetMaximum(), mdc2_nominal_ratio->GetMaximum());
  double minn = std::min(mdc1_nominal_ratio->GetMinimum(), mdc2_nominal_ratio->GetMinimum());

  leg->AddEntry(mdc1_nominal_ratio, "Mock Data/Prefit 1", "L");
  leg->AddEntry(mdc2_nominal_ratio, "Mock Data/Prefit 2", "L");

  // Draw histograms
  mdc1_nominal_ratio->Draw("hist");
  mdc2_nominal_ratio->Draw("hist same");
  mdc1_nominal_ratio->GetYaxis()->SetRangeUser(minn*0.9,maxn*1.1);
  mdc1_nominal_ratio->GetYaxis()->SetTitle("Event rate ratios");
  mdc1_nominal_ratio->SetLineColor(kAzure+7);
  mdc1_nominal_ratio->SetLineStyle(1);
  mdc2_nominal_ratio->SetLineColor(kOrange+2);
  mdc2_nominal_ratio->SetLineStyle(2);
  mdc2_nominal_ratio->SetLineWidth(2);

  // add the legend
  leg->Draw("same");
  
  // Add label to colour legend
  c1->SaveAs("mdc_nominal_ratio_overlays.root");
  c1->Clear();

  leg->Clear();
  
  // Ratios
  TH1D *mdc1_postfit_ratio = (TH1D*)mdc1_data_hist->Clone("mdc1_ratio");
  TH1D *mdc2_postfit_ratio = (TH1D*)mdc2_data_hist->Clone("mdc2_ratio");
  mdc1_postfit_ratio->Divide(mdc1_postfit_hist);
  mdc2_postfit_ratio->Divide(mdc2_postfit_hist);

  double max = std::max(mdc1_postfit_ratio->GetMaximum(), mdc2_postfit_ratio->GetMaximum());
  double min = std::min(mdc1_postfit_ratio->GetMinimum(), mdc2_postfit_ratio->GetMinimum());

  leg->AddEntry(mdc1_postfit_ratio, "Mock Data/Postfit 1", "L");
  leg->AddEntry(mdc2_postfit_ratio, "Mock Data/Postfit 2", "L");
  
  // Draw histograms
  mdc1_postfit_ratio->Draw("hist");
  mdc2_postfit_ratio->Draw("hist same");
  mdc1_postfit_ratio->GetYaxis()->SetRangeUser(min*0.9,max*1.1);
  mdc1_postfit_ratio->GetYaxis()->SetTitle("Event rate ratios");
  mdc1_postfit_ratio->SetLineColor(kAzure+7);
  mdc1_postfit_ratio->SetLineStyle(1);
  mdc2_postfit_ratio->SetLineColor(kOrange+2);
  mdc2_postfit_ratio->SetLineStyle(2);
  mdc2_postfit_ratio->SetLineWidth(2);

  // add the legend
  leg->Draw("same");
  
  // Add label to colour legend
  c1->SaveAs("mdc_postfit_ratio_overlays.root");
  c1->Clear();

  leg->Clear();
  
  // Mock data ratios
  TH1D *mdc1_mdc2_ratio         = (TH1D*)mdc1_data_hist->Clone("mdc1_mdc2_ratio");
  mdc1_mdc2_ratio->Add(mdc2_data_hist,-1);
  
  mdc1_mdc2_ratio->Divide(mdc1_data_hist);

  leg->AddEntry(mdc1_mdc2_ratio, "(Mock Data 1 - Mock Data 2)/Mock Data 2", "L");

  // Draw histograms
  mdc1_mdc2_ratio->Draw();
  mdc1_mdc2_ratio->GetYaxis()->SetTitle("(MDC1-MDC2)/MDC1 Event rate ratio");
  mdc1_mdc2_ratio->SetLineColor(kAzure+7);
  mdc1_mdc2_ratio->SetLineStyle(1);
  mdc1_mdc2_ratio->SetMarkerStyle(0);

  // add the legend
  leg->Draw("same");
  
  // Add label to colour legend
  c1->SaveAs("mdc1_mdc2_ratio_overlays.root");
  c1->Clear();

  leg->Clear();
}
