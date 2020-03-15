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
void rj_mdc_contour_comparisons() {

  // tb = true baseline
  // sb = spline baseline
  TFile *f_stat_sb       = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/mock_data_challenge/refactor_validation/contours/stat-only_contours_as_graphs.root","read");
  TFile *f_stat_tb       = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/mock_data_challenge/true_baseline/contours/new-stat-only_contours_as_graphs.root","read");
  TFile *f_syst_etrue_sb = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/mock_data_challenge/refactor_validation/contours/syst-flux-etrue_contours_as_graphs.root","read");
  TFile *f_syst_ereco_sb = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/mock_data_challenge/refactor_validation/contours/syst-flux-ereco_contours_as_graphs.root","read");
  TFile *f_syst_etrue_tb = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/mock_data_challenge/true_baseline/contours/new-syst-etrue_contours_as_graphs.root","read");
  TFile *f_syst_ereco_tb = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/mock_data_challenge/true_baseline/contours/new-syst-ereco_contours_as_graphs.root","read");

  // Get contours from file
  // Check names in .root file
  TGraph *contour_90_stat_sb       = (TGraph*) f_stat_sb      ->Get("stat-only_90pct_lin_0");
  TGraph *contour_90_stat_tb       = (TGraph*) f_stat_tb      ->Get("stat-only_90pct_lin_0");
  TGraph *contour_90_syst_etrue_sb = (TGraph*) f_syst_etrue_sb->Get("syst-flux-etrue_90pct_lin_0");
  TGraph *contour_90_syst_ereco_sb = (TGraph*) f_syst_ereco_sb->Get("syst-flux-ereco_90pct_lin_0");
  TGraph *contour_90_syst_etrue_tb = (TGraph*) f_syst_etrue_tb->Get("new-syst-etrue_90pct_lin_0");
  TGraph *contour_90_syst_ereco_tb = (TGraph*) f_syst_ereco_tb->Get("new-syst-ereco_90pct_lin_0");
  
  gStyle->SetOptLogz();

  TCanvas *c1 = new TCanvas("c1","c1",20,20,700,900);
  c1->SetRightMargin(0.08);
  c1->SetLeftMargin(0.12);
  c1->SetTopMargin(0.08);
  c1->SetBottomMargin(0.12);
  c1->SetLogx();
  c1->SetLogy();
  
  // Add legend
  TLegend *leg = new TLegend(0.14,0.12,0.59,0.38);
  leg->SetEntrySeparation(0.01);
  leg->SetTextFont(132);
  leg->SetTextColor(1);
  leg->SetFillStyle(0);
  leg->SetLineWidth(0);
  leg->AddEntry(contour_90_stat_sb,"90\% stat-only, baseline (bl) splines","L");
  leg->AddEntry(contour_90_stat_tb,"90\% stat-only, baseline (bl) true","L");
  leg->AddEntry(contour_90_syst_etrue_sb,"90\% syst flux-E_{#mbox{True}}, bl splines","L");
  //leg->AddEntry(contour_90_syst_etrue_tb,"90\% syst flux-E_{#mbox{True}}, bl true","L");
  leg->AddEntry(contour_90_syst_ereco_sb,"90\% syst flux-E_{#mbox{Reco}}, bl splines","L");
  //leg->AddEntry(contour_90_syst_ereco_tb,"90\% syst flux-E_{#mbox{Reco}}, bl true","L");
  
  // Draw contours
  contour_90_stat_sb->Draw();
  contour_90_stat_sb->SetTitle("");
  contour_90_stat_sb->GetXaxis()->SetTitle("sin^{2}#theta_{#mu#mu}");
  contour_90_stat_sb->GetYaxis()->SetTitle("#Delta m^{2}_{41}");
  contour_90_stat_sb->GetXaxis()->SetTitleFont(132);
  contour_90_stat_sb->GetYaxis()->SetTitleFont(132);
  contour_90_stat_sb->GetXaxis()->SetTitleSize(0.04);
  contour_90_stat_sb->GetYaxis()->SetTitleSize(0.04);
  contour_90_stat_sb->GetXaxis()->SetTitleOffset(1.2);
  contour_90_stat_sb->GetYaxis()->SetTitleOffset(1.4);
  contour_90_stat_sb->GetXaxis()->SetLabelFont(132);
  contour_90_stat_sb->GetYaxis()->SetLabelFont(132);
  contour_90_stat_sb->GetXaxis()->SetLimits(0.001,1);
  contour_90_stat_sb->GetYaxis()->SetRangeUser(0.01,100);
  contour_90_stat_sb->SetMarkerStyle(0);
  contour_90_stat_sb->SetLineWidth(2);
  contour_90_stat_sb->SetLineColor(kAzure+7);
  contour_90_stat_tb->Draw("same");
  contour_90_stat_tb->SetMarkerStyle(0);
  contour_90_stat_tb->SetLineWidth(2);
  contour_90_stat_tb->SetLineStyle(5);
  contour_90_stat_tb->SetLineColor(kAzure+7);
  contour_90_syst_etrue_sb->Draw("same");
  contour_90_syst_etrue_sb->SetMarkerStyle(0);
  contour_90_syst_etrue_sb->SetLineWidth(2);
  contour_90_syst_etrue_sb->SetLineColor(kPink+5);
  contour_90_syst_ereco_sb->Draw("same");  
  contour_90_syst_ereco_sb->SetMarkerStyle(0);
  contour_90_syst_ereco_sb->SetLineWidth(2);
  contour_90_syst_ereco_sb->SetLineColor(kOrange+1);
  contour_90_syst_etrue_tb->Draw("same");
  contour_90_syst_etrue_tb->SetMarkerStyle(0);
  contour_90_syst_etrue_tb->SetLineWidth(2);
  contour_90_syst_etrue_tb->SetLineStyle(5);
  contour_90_syst_etrue_tb->SetLineColor(kPink+5);
  contour_90_syst_ereco_tb->Draw("same");  
  contour_90_syst_ereco_tb->SetMarkerStyle(0);
  contour_90_syst_ereco_tb->SetLineWidth(2);
  contour_90_syst_ereco_tb->SetLineStyle(5);
  contour_90_syst_ereco_tb->SetLineColor(kOrange+1);
  
  // add the legend
  leg->Draw("same");
  
  // Add label to colour legend
  c1->SaveAs("new-mdc_flux_etrue-ereco_overlay_contour.root");
}
