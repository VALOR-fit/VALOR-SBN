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
#include "TFrame.h"
#include "TF1.h"

#include "TGraph.h"
#include "TStyle.h"
#include "TAxis.h"
#include "TColor.h"
 
void draw_log(){
//TFile *f_valor = new TFile("output_contours_as_graphs_A.root","read");
//TFile *f_valor_B = new TFile("output_contours_as_graphs_B.root","read");
//TFile *f_valor_C = new TFile("output_contours_as_graphs_C.root","read");
//TFile *f_valor_D = new TFile("output_contours_as_graphs_D.root","read");
//TFile *f_valor_old = new TFile("rhiannon_stat-only_contours_as_graphs.root","read");
//TFile *f_valor_60x60 = new TFile("output_contours_as_graphs_60x60.root","read");
TFile *f_valor_nodet            = new TFile("/sbnd/app/users/tham/VALOR_master/detector_stuff/output_contours_as_graphs_nodet_simplex.root", "read");
TFile *f_valor_det              = new TFile("/sbnd/app/users/tham/VALOR_master/detector_stuff/output_contours_as_graphs_det_simplex.root", "read");
TFile *f_valor_det_2_1          = new TFile("/sbnd/app/users/tham/VALOR_master/detector_stuff/output_contours_as_graphs_det_21_simplex.root", "read");
TFile *f_valor_det_2_05         = new TFile("/sbnd/app/users/tham/VALOR_master/detector_stuff/output_contours_as_graphs_det_205_simplex.root", "read");

TFile *f_sbnfit                 = new TFile("/sbnd/data/users/tham/fitter_data/SBNfit_numu_modern_25var.root","read");
TFile *f_cafana                 = new TFile("/sbnd/data/users/tham/fitter_data/CAFAna_numu_modern.root","read");

TFile *f_sbn_proposal           = new TFile("$VALOR_FMWk/data/contours/sterile_nu/sterile_3p1_limits.root");

// nue files
TFile *f_sbnfit_nue             = new TFile("/sbnd/data/users/tham/fitter_data/nue_modern/SBNfit.root","read");
TFile *f_cafana_nue             = new TFile("/sbnd/data/users/tham/fitter_data/nue_modern/CAFAna_nue_modern.root","read");
//TFile *f_cafana_nue2             = new TFile("/sbnd/data/users/tham/fitter_data/nue_modern/CAFAna_nue_exclusion.root","read");

//TFile*f_valor_nue               = new TFile("/sbnd/app/users/tham/VALOR_master/nueTEST/sensitivities/nue_modern_1E-5_fix_vb2.root","read");
TFile*f_valor_nue               = new TFile("/sbnd/app/users/tham/VALOR_master/VALOR-SBN/nue_files/test_11sept/output_contours_as_graphs_fix.root","read");
TFile*f_valor_nue2               = new TFile("/sbnd/app/users/tham/VALOR_master/VALOR-SBN/nue_files/test_9sept/output_contour_oldbug.root","read");

TFile*f_valor_nue2020            = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_2020.root","read");
TFile*f_valor_nue2020_geniev2    = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/geniev2/output_contours_as_graphs.root","read");
                                              

// get numu contours
TGraph *VALOR_SBN_90pctC_det                 = (TGraph*) f_valor_det->Get("contour_90pct_lin_0;1");
TGraph *VALOR_SBN_3SC_det                    = (TGraph*) f_valor_det->Get("contour_3sigma_lin_0;1");
TGraph *VALOR_SBN_5SC_det                    = (TGraph*) f_valor_det->Get("contour_5sigma_lin_0;1");

TGraph *VALOR_SBN_90pctC_nodet               = (TGraph*) f_valor_nodet->Get("contour_90pct_lin_0;1");
TGraph *VALOR_SBN_3SC_nodet                  = (TGraph*) f_valor_nodet->Get("contour_3sigma_lin_0;1");
TGraph *VALOR_SBN_5SC_nodet                  = (TGraph*) f_valor_nodet->Get("contour_5sigma_lin_0;1");

TGraph *VALOR_SBN_90pctC_det_2_1             = (TGraph*) f_valor_det_2_1->Get("contour_90pct_lin_0;1");
TGraph *VALOR_SBN_3SC_det_2_1                = (TGraph*) f_valor_det_2_1->Get("contour_3sigma_lin_0;1");
TGraph *VALOR_SBN_5SC_det_2_1                = (TGraph*) f_valor_det_2_1->Get("contour_5sigma_lin_0;1");

TGraph *VALOR_SBN_90pctC_det_2_05            = (TGraph*) f_valor_det_2_05->Get("contour_90pct_lin_0;1");
TGraph *VALOR_SBN_3SC_det_2_05               = (TGraph*) f_valor_det_2_05->Get("contour_3sigma_lin_0;1");
TGraph *VALOR_SBN_5SC_det_2_05               = (TGraph*) f_valor_det_2_05->Get("contour_5sigma_lin_0;1");

TGraph *lim_numudis_3p1_sbnproposal_90pctCL  = (TGraph*) f_sbn_proposal->Get("lim_numudis_3p1_sbnproposal_90pctCL");
TGraph *lim_numudis_3p1_sbnproposal_3sigCL   = (TGraph*) f_sbn_proposal->Get("lim_numudis_3p1_sbnproposal_3sigCL");
TGraph *lim_numudis_3p1_sbnproposal_5sigCL   = (TGraph*) f_sbn_proposal->Get("lim_numudis_3p1_sbnproposal_5sigCL");

/*
TGraph *VALOR_SBN_90pctC      = (TGraph*) f_valor->Get("contour_90pct_log_0");
TGraph *VALOR_SBN_90pctC_B      = (TGraph*) f_valor_B->Get("contour_90pct_log_0");
TGraph *VALOR_SBN_90pctC_C      = (TGraph*) f_valor_C->Get("contour_90pct_log_0");
TGraph *VALOR_SBN_90pctC_D      = (TGraph*) f_valor_D->Get("contour_90pct_log_0");
TGraph *VALOR_SBN_90pctC_old      = (TGraph*) f_valor_old->Get("stat-only_90pct_log_0");
TGraph *VALOR_SBN_90pctC_60x60     = (TGraph*) f_valor_60x60->Get("contour_90pct_log_0");
*/
TGraph *SBNfit_SBN_90pctC                    = (TGraph*) f_sbnfit->Get("STATONLY_90CL");
TGraph *CAFAna_SBN_90pctC                    = (TGraph*) f_cafana->Get("numu_exclusion_all_stat_90pct");
TGraph *CAFAna_SBN_90pctC_syst               = (TGraph*) f_cafana->Get("numu_exclusion_all_syst_90pct");

// get nue contours
TGraph *SBNfit_nue_90pctC                    = (TGraph*) f_sbnfit_nue->Get("Nue_stats_90CL");
TGraph *CAFAna_nue_90pctC                    = (TGraph*) f_cafana_nue->Get("nue_exclusion_all_stat_5sig");
//TGraph *CAFAna_nue_90pctC2                    = (TGraph*) f_cafana_nue2->Get("all_stat_90pct");

TGraph *VALOR_nue_90pctC                     = (TGraph*) f_valor_nue->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_90pctC2                     = (TGraph*) f_valor_nue2->Get("contour_5sigma_lin_0");

TGraph *VALOR_nue_5s_2020                     = (TGraph*) f_valor_nue2020->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_2020_geniev2                     = (TGraph*) f_valor_nue2020_geniev2->Get("contour_5sigma_lin_0");

// Choose contour aesthetics 

//lim_numudis_3p1_sbnproposal_90pctCL     -> SetLineWidth(2);

VALOR_SBN_90pctC_nodet                  -> SetLineColor(kPink+5);
VALOR_SBN_90pctC_nodet                  -> SetLineStyle(1);
VALOR_SBN_90pctC_nodet                  -> SetLineWidth(2);
VALOR_SBN_3SC_nodet                     -> SetLineColor(kPink+5);
VALOR_SBN_3SC_nodet                     -> SetLineStyle(9);
VALOR_SBN_3SC_nodet                     -> SetLineWidth(2);
VALOR_SBN_5SC_nodet                     -> SetLineColor(kPink+5);
VALOR_SBN_5SC_nodet                     -> SetLineStyle(10);
VALOR_SBN_5SC_nodet                     -> SetLineWidth(2);

VALOR_SBN_90pctC_det                    -> SetLineColor(kRed);
VALOR_SBN_90pctC_det                    -> SetLineStyle(1);
VALOR_SBN_90pctC_det                    -> SetLineWidth(2);
VALOR_SBN_3SC_det                       -> SetLineColor(kRed);
VALOR_SBN_3SC_det                       -> SetLineStyle(9);
VALOR_SBN_3SC_det                       -> SetLineWidth(2);
VALOR_SBN_5SC_det                       -> SetLineColor(kRed);
VALOR_SBN_5SC_det                       -> SetLineStyle(10);
VALOR_SBN_5SC_det                       -> SetLineWidth(2);

VALOR_SBN_90pctC_det_2_1                -> SetLineColor(kBlue);
VALOR_SBN_90pctC_det_2_1                -> SetLineStyle(1);
VALOR_SBN_90pctC_det_2_1                -> SetLineWidth(2);
VALOR_SBN_3SC_det_2_1                   -> SetLineColor(kBlue);
VALOR_SBN_3SC_det_2_1                   -> SetLineStyle(9);
VALOR_SBN_3SC_det_2_1                   -> SetLineWidth(2);
VALOR_SBN_5SC_det_2_1                   -> SetLineColor(kBlue);
VALOR_SBN_5SC_det_2_1                   -> SetLineStyle(10);
VALOR_SBN_5SC_det_2_1                   -> SetLineWidth(2);

VALOR_SBN_90pctC_det_2_05               -> SetLineColor(kGreen);
VALOR_SBN_90pctC_det_2_05               -> SetLineStyle(1);
VALOR_SBN_90pctC_det_2_05               -> SetLineWidth(2);
VALOR_SBN_3SC_det_2_05                  -> SetLineColor(kGreen);
VALOR_SBN_3SC_det_2_05                  -> SetLineStyle(9);
VALOR_SBN_3SC_det_2_05                  -> SetLineWidth(2);
VALOR_SBN_5SC_det_2_05                  -> SetLineColor(kGreen);
VALOR_SBN_5SC_det_2_05                  -> SetLineStyle(10);
VALOR_SBN_5SC_det_2_05                  -> SetLineWidth(2);


TCanvas *c1 = new TCanvas("c1","",20,20,700,900);
TPad *pad = new TPad("pad","",0,0,1,1);

pad->SetLogx();
pad->SetLogy();
pad->SetTickx();
pad->SetTicky();
pad->Draw();
pad->cd();


TH1F *hr = c1->DrawFrame(0.001,0.01,1,100);
hr->SetXTitle("sin^{2}2#theta_{#mu#mu}");
hr->GetXaxis()->SetTitleSize(0.03);
hr->GetXaxis()->SetTitleOffset(1.4);
hr->GetXaxis()->SetLabelSize(0.03);
 
hr->SetYTitle("#Deltam^{2}_{41} [eV^{2}]");
hr->GetYaxis()->SetTitleSize(0.03);
hr->GetYaxis()->SetTitleOffset(1.4);
hr->GetYaxis()->SetLabelSize(0.03);

pad->GetFrame()->SetBorderSize(12);


//lim_numudis_3p1_sbnproposal_90pctCL->Draw();


//SBNfit_SBN_90pctC->Draw();
SBNfit_SBN_90pctC->SetLineColor(kRed);
SBNfit_SBN_90pctC->SetLineStyle(9);

//CAFAna_SBN_90pctC->Draw("same");
CAFAna_SBN_90pctC->SetLineColor(kBlue);
CAFAna_SBN_90pctC->SetLineStyle(9);

//CAFAna_SBN_90pctC_syst->Draw("same");
CAFAna_SBN_90pctC_syst->SetLineColor(kBlue);
CAFAna_SBN_90pctC_syst->SetLineStyle(9);



// create a transparent pad drawn on top of the main pad
// These curves are for a log plot, so have the corresponding log range
c1->cd();
TPad *overlay = new TPad("overlay","",0,0,1,1);
overlay->SetFillStyle(4000);
overlay->SetFillColor(0);
overlay->SetFrameFillStyle(4000);
overlay->Draw();
overlay->cd();
 
// same values as for the frame, but in log scale
Double_t xmin = -3;
Double_t ymin = -2;
Double_t xmax = 0;
Double_t ymax = 2;
TH1F *hframe = overlay->DrawFrame(xmin,ymin,xmax,ymax);
hframe->GetXaxis()->SetLabelOffset(99);
hframe->GetYaxis()->SetLabelOffset(99);
hframe->GetXaxis()->SetTickLength(0);
hframe->GetYaxis()->SetTickLength(0);



    

VALOR_SBN_90pctC_det->Draw("same");
//VALOR_SBN_3SC_det->Draw("same");
//VALOR_SBN_5SC_det->Draw("same");
VALOR_SBN_90pctC_nodet->Draw("same");
//VALOR_SBN_3SC_nodet->Draw("same");
//VALOR_SBN_5SC_nodet->Draw("same");

/*
VALOR_SBN_90pctC->Draw("same");
VALOR_SBN_90pctC->SetLineStyle(9);

VALOR_SBN_90pctC_B->Draw("same");
VALOR_SBN_90pctC_B->SetLineStyle(9);

VALOR_SBN_90pctC_C->Draw("same");
VALOR_SBN_90pctC_C->SetLineStyle(9);

VALOR_SBN_90pctC_D->Draw("same");
VALOR_SBN_90pctC_D->SetLineStyle(9);



//VALOR_SBN_90pctC_old->Draw("same");
VALOR_SBN_90pctC_old->SetLineStyle(9);
VALOR_SBN_90pctC_old->SetLineColor(kGreen);

//VALOR_SBN_90pctC_60x60->Draw("same");
VALOR_SBN_90pctC_60x60->SetLineStyle(9);
VALOR_SBN_90pctC_60x60->SetLineColor(kMagenta);
*/


// Add legend
TLegend *leg = new TLegend(0.2,0.15,0.5,0.3);
leg->SetTextSize(0.03);
//leg->SetTextColor(kAzure-4);
leg->SetFillStyle(0);
leg->SetBorderSize(0);
leg->AddEntry(lim_numudis_3p1_sbnproposal_90pctCL, "proposal 90%","l");
leg->AddEntry(VALOR_SBN_90pctC_det,"VALOR w. detector 90%","l");
leg->AddEntry(VALOR_SBN_90pctC_nodet,"VALOR w/o detector 90%","l");
//leg->AddEntry(contour_5_sigma,"5#sigma","l");
leg->Draw("same");






TCanvas * cnumudetcompare = new TCanvas("cnumudetcompare","",20,20,700,900);
cnumudetcompare->Draw();

TH2F * hfnumudetcompare = (TH2F*) cnumudetcompare->DrawFrame(1E-3,1E-2,1,1E+2);
hfnumudetcompare->Draw();
hfnumudetcompare->GetYaxis()->SetTitleOffset(1.3);
hfnumudetcompare->GetXaxis()->SetTitle("sin^{2}2#theta_{#mu#mu}");
hfnumudetcompare->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hfnumudetcompare->GetXaxis()->SetTitleFont(132);
hfnumudetcompare->GetYaxis()->SetTitleFont(132);
hfnumudetcompare->GetXaxis()->SetLabelFont(132);
hfnumudetcompare->GetYaxis()->SetLabelFont(132);
cnumudetcompare->SetLogx();
cnumudetcompare->SetLogy();


//lim_numudis_3p1_sbnproposal_90pctCL->GetYaxis()->SetRangeUser(1E-2,1E2);
//lim_numudis_3p1_sbnproposal_90pctCL->Draw("l");
VALOR_SBN_90pctC_nodet->Draw("l");
VALOR_SBN_90pctC_det->Draw("l");
VALOR_SBN_90pctC_det_2_1->Draw("l");
VALOR_SBN_90pctC_det_2_05->Draw("l");

TLegend * lgnumudetcompare = new TLegend(0.12,0.12,0.67,0.38);
lgnumudetcompare->SetFillStyle(0);
lgnumudetcompare->SetBorderSize(0);
lgnumudetcompare->SetTextFont(132);
lgnumudetcompare->AddEntry(lim_numudis_3p1_sbnproposal_90pctCL, "Proposal 90\% CL","L");
lgnumudetcompare->AddEntry(VALOR_SBN_90pctC_nodet, "VALOR 90\% CL - No Detector",  "L");
lgnumudetcompare->AddEntry(VALOR_SBN_90pctC_det, "VALOR 90\% CL - Detector (5\%cor,0.5\%uncor)", "L");
lgnumudetcompare->AddEntry(VALOR_SBN_90pctC_det_2_1, "VALOR 90\% CL - Detector (2\%cor,1\%uncor)", "L");
lgnumudetcompare->AddEntry(VALOR_SBN_90pctC_det_2_05, "VALOR 90\% CL - Detector (2\%cor,0.5\%uncor)", "L");
lgnumudetcompare->Draw();






// nue stat only
TCanvas * nue_stat = new TCanvas("nue_stat","",20,20,700,900);
nue_stat->Draw();

TH2F * hnue_stat = (TH2F*) nue_stat->DrawFrame(8E-5,1E-2,1,1E+2);
hnue_stat->Draw();
nue_stat->SetLogx();
nue_stat->SetLogy();
hnue_stat->GetXaxis()->SetTitle("sin^{2}2#theta_{#mue}");
hnue_stat->GetXaxis()->SetTitleSize(0.03);
hnue_stat->GetXaxis()->SetLabelSize(0.03);
hnue_stat->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnue_stat->GetYaxis()->SetTitleSize(0.03);
hnue_stat->GetYaxis()->SetLabelSize(0.03);



CAFAna_nue_90pctC->SetLineColor(kOrange);
CAFAna_nue_90pctC->SetLineStyle(9);
//CAFAna_nue_90pctC->Draw("l");

//CAFAna_nue_90pctC2->SetLineColor(kRed);
//CAFAna_nue_90pctC2->SetLineStyle(9);
//CAFAna_nue_90pctC2->Draw("l");



//SBNfit_nue_90pctC->SetLineColor(kCyan);
//SBNfit_nue_90pctC->SetLineStyle(9);
//SBNfit_nue_90pctC->Draw("l");

VALOR_nue_90pctC->SetLineStyle(9);
//VALOR_nue_90pctC->Draw("l");

VALOR_nue_5s_2020->SetLineColor(kGreen);
VALOR_nue_5s_2020->SetLineStyle(9);
VALOR_nue_5s_2020->Draw("l");

VALOR_nue_5s_2020_geniev2->SetLineColor(kBlue);
VALOR_nue_5s_2020_geniev2->SetLineStyle(9);
VALOR_nue_5s_2020_geniev2->Draw("l");



//VALOR_nue_90pctC2->SetLineColor(kCyan);
//VALOR_nue_90pctC2->SetLineStyle(9);
//VALOR_nue_90pctC2->Draw("l");

TLegend * lnue_stat = new TLegend(0.15,0.2,0.67,0.3);
lnue_stat->SetFillStyle(0);
lnue_stat->SetBorderSize(0);
lnue_stat->SetTextFont(132);
lnue_stat->AddEntry(VALOR_nue_5s_2020, "VALOR Modern 5#sigma CL stat-only Geniev3","L");
lnue_stat->AddEntry(VALOR_nue_5s_2020_geniev2, "VALOR Modern 5#sigma CL stat-only Geniev2","L");
//lnue_stat->AddEntry(CAFAna_nue_90pctC, "CAFAna Modern 5sigma CL","L");
lnue_stat->Draw();

// save plot 
nue_stat->SaveAs("/sbnd/app/users/tham/VALOR_master/nue_2020/images/nue_sensitivity_stat_only.eps");

}
