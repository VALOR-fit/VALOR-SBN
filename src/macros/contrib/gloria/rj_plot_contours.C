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
void rj_plot_contours() {

//  TFile *f_stat = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/contours/december_2019/stat_3_det_contours_as_graphs.root","read");
//  TFile *f_syst = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/contours/december_2019/syst_3_det_contours_as_graphs.root","read");
  TFile *f_val = new TFile("/opt/ppd/t2k/users/gloria/VALOR-DUNE-LBL/outfiles_big_job/rootfiles/stat-only_contours_as_graphs.root","read");
//  TFile *f_caf = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/data/sbn/CAFAna/december_2019/CAFAna_numu_graphs_modern.root","read");

  // Get contours from file
  // Check names in .root file
  TGraph *contour_90_val      = (TGraph*) f_val->Get("stat-only_90pct_lin_0");
  TGraph *contour_3_sigma_val = (TGraph*) f_val->Get("stat-only_3sigma_lin_0");
 // TGraph *contour_5_sigma_val = (TGraph*) f_val->Get("stat-only_90pct_lin_2");
  
 // TGraph *contour_90_caf      = (TGraph*) f_val->Get("stat-only_90pct_lin_3");
 /* TGraph *contour_3_sigma_caf = (TGraph*) f_caf->Get("numu_exclusion_fd_stat_3sig");
  TGraph *contour_5_sigma_caf = (TGraph*) f_caf->Get("numu_exclusion_fd_stat_5sig");
  */
  gStyle->SetOptLogz();

  TCanvas *c1 = new TCanvas("c1","c1");
  c1->SetRightMargin(0.08);
  c1->SetLeftMargin(0.12);
  c1->SetTopMargin(0.08);
  c1->SetBottomMargin(0.12);
  c1->SetLogx();
  c1->SetLogy();
  
  // Add legend
  TLegend *leg = new TLegend(0.15,0.15,0.55,0.45);
  leg->SetTextSize(0.05);
  leg->SetTextFont(132);
  leg->SetTextColor(1);
  leg->SetFillStyle(0);
  leg->SetLineWidth(0);
  leg->AddEntry(contour_90_val,"90% stat-only VALOR","L");
  leg->AddEntry(contour_3_sigma_val,"3#sigma stat-only VALOR","L");
  //leg->AddEntry(contour_5_sigma_val,"5#sigma stat-only VALOR","L");
  /*
  leg->AddEntry(contour_90_caf,"90% stat-only CAFAna","L");
  leg->AddEntry(contour_3_sigma_caf,"3#sigma stat-only CAFAna ","L");
  leg->AddEntry(contour_5_sigma_caf,"5#sigma stat-only CAFAna","L");
  */
  // Draw contours
  contour_90_val->Draw();
  contour_90_val->GetXaxis()->SetTitle("sin^{2}(2#theta_{ee})");
  contour_90_val->GetYaxis()->SetTitle("#Delta m^{2}_{41}");
  contour_90_val->GetXaxis()->SetTitleFont(132);
  contour_90_val->GetYaxis()->SetTitleFont(132);
  contour_90_val->GetXaxis()->SetTitleSize(0.05);
  contour_90_val->GetYaxis()->SetTitleSize(0.05);
  contour_90_val->GetXaxis()->SetTitleOffset(0.9);
  contour_90_val->GetYaxis()->SetTitleOffset(0.9);
  contour_90_val->GetXaxis()->SetLabelFont(132);
  contour_90_val->GetYaxis()->SetLabelFont(132);
  contour_90_val->GetXaxis()->SetLimits(0.01,1);
  contour_90_val->GetYaxis()->SetRangeUser(0.01,100); 
  contour_90_val->SetMarkerStyle(0);
  contour_90_val->SetLineWidth(2);
  contour_90_val->SetLineColor(kOrange+10);
  contour_3_sigma_val->SetMarkerStyle(0);
  contour_3_sigma_val->SetLineStyle(2);
  contour_3_sigma_val->SetLineWidth(2);
  contour_3_sigma_val->SetLineColor(kOrange+10);
  contour_3_sigma_val->Draw("same");
 /* contour_5_sigma_val->SetMarkerStyle(0);
  contour_5_sigma_val->SetLineStyle(7);  
  contour_5_sigma_val->SetLineWidth(2);
  contour_5_sigma_val->SetLineColor(kAzure-4);
  contour_5_sigma_val->Draw("same");  
  */
 // contour_90_caf->SetMarkerStyle(0);
 // contour_90_caf->SetLineWidth(2);
 // contour_90_caf->SetLineColor(kOrange+2);
 // contour_90_caf->Draw("same");
  /*contour_3_sigma_caf->SetMarkerStyle(0);
  contour_3_sigma_caf->SetLineStyle(2);
  contour_3_sigma_caf->SetLineWidth(2);
  contour_3_sigma_caf->SetLineColor(kOrange+2);
  contour_3_sigma_caf->Draw("same");
  contour_5_sigma_caf->SetMarkerStyle(0);
  contour_5_sigma_caf->SetLineStyle(7);  
  contour_5_sigma_caf->SetLineWidth(2);
  contour_5_sigma_caf->SetLineColor(kOrange+2);
  contour_5_sigma_caf->Draw("same");  
 */ 
  // add the legend
  leg->Draw("same");
  
  // Add label to colour legend
  c1->SaveAs("fd-only_valor_contour.root");
 c1->Print("fd-only_valor_contour.pdf","pdf");


}
