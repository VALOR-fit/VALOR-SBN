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
void rj_plot_data_contours() {

  // VALOR modern numu files
  TFile *f_stat = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/contours/december_2019/stat_3_det_contours_as_graphs.root","read");
  TFile *f_syst = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/contours/december_2019/syst_3_det_contours_as_graphs.root","read");

  // CAFAna modern numu files
  TFile *f_caf  = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/data/sbn/CAFAna/december_2019/CAFAna_numu_graphs_modern.root","read");

  // Get contours from file
  // Check names in .root file
  TGraph * contour_90_stat        = (TGraph*) f_stat->Get("contour_90pct_lin_0");
  TGraph * contour_90_syst        = (TGraph*) f_syst->Get("contour_90pct_lin_0");
  TGraph * cafana_contour_90_stat = (TGraph *) f_caf->Get("numu_exclusion_all_stat_90pct"); 
  TGraph * cafana_contour_90_syst = (TGraph *) f_caf->Get("numu_exclusion_all_syst_90pct"); 
  
 // gStyle->SetOptLogz();
  TCanvas *c1 = new TCanvas("c1","c1");
  c1->SetRightMargin(0.08);
  c1->SetLeftMargin(0.12);
  c1->SetTopMargin(0.08);
  c1->SetBottomMargin(0.12);
  c1->Draw();

  TH2F * hfnumudis = (TH2F*) c1->DrawFrame(1E-3,1E-2,1,1E+2);
  hfnumudis->Draw();
  hfnumudis->GetXaxis()->SetTitle("sin^{2}2#theta_{#mu #mu}");
  hfnumudis->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2}/c^{4})");
  hfnumudis->GetXaxis()->SetTitleFont(132);
  hfnumudis->GetYaxis()->SetTitleFont(132);
  hfnumudis->GetXaxis()->SetLabelFont(132);
  hfnumudis->GetYaxis()->SetLabelFont(132);
  hfnumudis->GetXaxis()->SetTitleSize(0.05);
  hfnumudis->GetYaxis()->SetTitleSize(0.05);
  hfnumudis->GetXaxis()->SetTitleOffset(0.9);
  hfnumudis->GetYaxis()->SetTitleOffset(0.9);
  c1->SetLogx();
  c1->SetLogy();
  
  // Add legend
  TLegend *leg = new TLegend(0.15,0.15,0.55,0.45);
  leg->SetTextSize(0.05);
  leg->SetTextFont(132);
  leg->SetTextColor(1);
  leg->SetFillStyle(0);
  leg->SetLineWidth(0);
  leg->AddEntry(contour_90_stat,"VALOR 90% stat-only","L");
  leg->AddEntry(contour_90_syst,"VALOR 90% stat+syst","L");
  leg->AddEntry(cafana_contour_90_stat,"CAFAna 90% stat-only","L");
  leg->AddEntry(cafana_contour_90_syst,"CAFAna 90% stat+syst","L");
  
  
  // Draw contours
  contour_90_stat->Draw("l");
  contour_90_syst->Draw("l");
  cafana_contour_90_stat->Draw("l");
  cafana_contour_90_syst->Draw("l");

  contour_90_stat->SetMarkerStyle(0);
  contour_90_stat->SetLineWidth(2);
  contour_90_stat->SetLineColor(kAzure-4);
  contour_90_syst->SetMarkerStyle(0);
  contour_90_syst->SetLineWidth(3);
  contour_90_syst->SetLineStyle(7);
  contour_90_syst->SetLineColor(kAzure-4);
  cafana_contour_90_stat->SetMarkerStyle(0);
  cafana_contour_90_stat->SetLineWidth(2);
  cafana_contour_90_stat->SetLineColor(kOrange+1);
  cafana_contour_90_syst->SetMarkerStyle(0);
  cafana_contour_90_syst->SetLineWidth(3);
  cafana_contour_90_syst->SetLineStyle(7);
  cafana_contour_90_syst->SetLineColor(kOrange+1); 
  
  // add the legend
  leg->Draw("same");
  
  // Add label to colour legend
  c1->SaveAs("$VALOR_DUNE/contours/december_2019/valor_cafana_exclusion_disappearance_3_detector_contour.root");
}
