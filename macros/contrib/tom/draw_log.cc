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

TFile *f_sbn_proposal           = new TFile("/sbnd/app/users/tham/VALOR_master/sterile_3p1_limits.root");

// nue files
//TFile *f_sbnfit_nue             = new TFile("/sbnd/data/users/tham/fitter_data/nue_modern/SBNfit.root","read");
TFile *f_cafana_nue             = new TFile("/sbnd/data/users/tham/fitter_data/nue_modern/CAFAna_nue_modern.root","read");
//TFile *f_cafana_nue2             = new TFile("/sbnd/data/users/tham/fitter_data/nue_modern/CAFAna_nue_exclusion.root","read");

//TFile*f_valor_nue               = new TFile("/sbnd/app/users/tham/VALOR_master/nueTEST/sensitivities/nue_modern_1E-5_fix_vb2.root","read");
TFile*f_valor_nue               = new TFile("/sbnd/app/users/tham/VALOR_master/VALOR-SBN/nue_files/test_11sept/output_contours_as_graphs_fix.root","read");
TFile*f_valor_nue2               = new TFile("/sbnd/app/users/tham/VALOR_master/VALOR-SBN/nue_files/test_9sept/output_contour_oldbug.root","read");

TFile*f_valor_nue2020            = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_2020.root","read");
//TFile*f_valor_nue2020_stat            = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_2020_stat.root","read");
TFile*f_valor_nue2020_geniev2_stat    = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/geniev2/output_contours_as_graphs_stat.root","read");
TFile*f_valor_nue2020_geniev2_stat2    = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/geniev2/output_contours_as_graphs_statv2.root","read");
TFile*f_valor_nue2020_geniev2_syst    = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/geniev2/output_contours_as_graphs_syst.root","read");
TFile*f_valor_nue2020_geniev2_splines    = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/geniev2/output_contours_as_graphs_splines.root","read");
//TFile*f_valor_nue2020_syst    = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/syst_temp/output_contours_as_graphs.root","read");

TFile*f_valor_geniev3_stat                                     = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_stat_fixed_params.root","read");
TFile*f_valor_geniev3_splines_proposal_fixed_params            = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_spline_proposal_fixed_params.root","read");
TFile*f_valor_geniev3_splines_proposal_fixed_params_matrix     = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_spline_proposal_fixed_matrix.root","read");
TFile*f_valor_geniev3_splines                                  = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_spline_fixed_matrix.root","read");
TFile*f_valor_geniev3_splines_oldjobsub                        = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_spline_oldjobsub.root","read");
                                              
TFile*f_valor_nue_disapp_geniev3_stat                          = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_nue_disapp_stat.root","read");
TFile*f_valor_nue_disapp_geniev3_syst                          = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_nue_disapp_spline.root","read");

TFile*f_cafana_nue2020            = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/CAFAna_nue_app_exclusion.root","read");
TFile*f_cafana_nue2020_mec            = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/CAFAna_nue_app_exclusion_mec.root","read");
TFile*f_cafana_nue2020_injected            = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/CAFAna_nue_app_allowed.root","read");

TFile *f_sbnfit_nue_app_geniev2             = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/geniev2/SBNfit_NueApp_sensitivity_NoMCIntrinsicError.root","read");
TFile *f_sbnfit_nue_app_geniev3             = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/SBNfit_NueApp_sensitivity_Geniev3.root","read"); //proposal syst no mec


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

/////////////////////
// get nue contours
/////////////////////

//TGraph *SBNfit_nue_90pctC                    = (TGraph*) f_sbnfit_nue->Get("Nue_stats_90CL");
TGraph *CAFAna_nue_5sig                    = (TGraph*) f_cafana_nue->Get("nue_exclusion_all_stat_5sig");
TGraph *CAFAna_nue_5sig_syst                    = (TGraph*) f_cafana_nue->Get("nue_exclusion_all_syst_5sig;1");
//TGraph *CAFAna_nue_90pctC2                    = (TGraph*) f_cafana_nue2->Get("all_stat_90pct");

TGraph *VALOR_nue_90pctC                     = (TGraph*) f_valor_nue->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_90pctC2                     = (TGraph*) f_valor_nue2->Get("contour_5sigma_lin_0");

TGraph *VALOR_nue_5s_2020                     = (TGraph*) f_valor_nue2020->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_2020_geniev2_stat                     = (TGraph*) f_valor_nue2020_geniev2_stat->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_2020_geniev2_stat2                     = (TGraph*) f_valor_nue2020_geniev2_stat2->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_2020_geniev2_syst                     = (TGraph*) f_valor_nue2020_geniev2_syst->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_2020_geniev2_splines                     = (TGraph*) f_valor_nue2020_geniev2_splines->Get("contour_5sigma_lin_0");
//TGraph *VALOR_nue_5s_2020_syst                     = (TGraph*) f_valor_nue2020_syst->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_stat                     = (TGraph*) f_valor_geniev3_stat->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_spline                     = (TGraph*) f_valor_geniev3_splines->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_spline_oldjobsub                     = (TGraph*) f_valor_geniev3_splines_oldjobsub->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_spline_proposal_fixed_params                     = (TGraph*) f_valor_geniev3_splines_proposal_fixed_params->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_spline_proposal_fixed_params_matrix                     = (TGraph*) f_valor_geniev3_splines_proposal_fixed_params_matrix->Get("contour_5sigma_lin_0");

TGraph *VALOR_nue_disapp_5s_geniev3_stat                       = (TGraph*) f_valor_nue_disapp_geniev3_stat->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_spline                     = (TGraph*) f_valor_nue_disapp_geniev3_syst->Get("contour_5sigma_lin_0");

TGraph *CAFAna_nue_5s_2020                   = (TGraph*) f_cafana_nue2020->Get("all_stat_5sig");
TGraph *CAFAna_nue_5s_2020_syst                   = (TGraph*) f_cafana_nue2020->Get("all_syst_5sig");
TGraph *CAFAna_nue_5s_2020_syst_mec                   = (TGraph*) f_cafana_nue2020_mec->Get("all_syst_5sig");

TGraph *CAFAna_nue_5s_2020_injected                   = (TGraph*) f_cafana_nue2020_injected->Get("all_stat_5sig_10");
TGraph *CAFAna_nue_5s_2020_injected_syst                   = (TGraph*) f_cafana_nue2020_injected->Get("all_syst_5sig_1");

TGraph *SBNfit_nue_app_geniev2_5s_stat                   = (TGraph*) f_sbnfit_nue_app_geniev2->Get("STATONLY_5sigma");
TGraph *SBNfit_nue_app_geniev2_5s_syst                   = (TGraph*) f_sbnfit_nue_app_geniev2->Get("g5sigma");

TGraph *SBNfit_nue_app_geniev3_5s_stat                   = (TGraph*) f_sbnfit_nue_app_geniev3->Get("STATONLY_5sigma");
TGraph *SBNfit_nue_app_geniev3_5s_syst                   = (TGraph*) f_sbnfit_nue_app_geniev3->Get("g5sigma");

TGraph *lim_nueapp_3p1_sbnproposal_5sigCL   = (TGraph*) f_sbn_proposal->Get("lim_nueapp_3p1_sbnproposal_5sigCL");
TGraph *lim_nueapp_3p1_nomad_99pctCL          = (TGraph*) f_sbn_proposal->Get("lim_nueapp_3p1_nomad_99pctCL");
TGraph *lim_nueapp_3p1_bnl776_99pctCL         = (TGraph*) f_sbn_proposal->Get("lim_nueapp_3p1_bnl776_99pctCL");
TGraph *lim_nueapp_3p1_karmen_99pctCL       = (TGraph*) f_sbn_proposal->Get("lim_nueapp_3p1_karmen_99pctCL");
TGraph *lim_nueapp_3p1_icarus_99pctCL       = (TGraph*) f_sbn_proposal->Get("lim_nueapp_3p1_icarus_99pctCL");
TGraph *lim_nueapp_3p1_opera_99pctCL       = (TGraph*) f_sbn_proposal->Get("lim_nueapp_3p1_opera_99pctCL");
TGraph *lim_nueapp_3p1_miniboonenu_99pctCL       = (TGraph*) f_sbn_proposal->Get("lim_nueapp_3p1_miniboonenu_99pctCL");
TGraph *lim_nueapp_3p1_lsndr1_99pctCL       = (TGraph*) f_sbn_proposal->Get("lim_nueapp_3p1_lsndr1_99pctCL");
TGraph *lim_nueapp_3p1_lsndr2_99pctCL       = (TGraph*) f_sbn_proposal->Get("lim_nueapp_3p1_lsndr2_99pctCL");
TGraph *lim_nueapp_3p1_lsndr3_99pctCL       = (TGraph*) f_sbn_proposal->Get("lim_nueapp_3p1_lsndr3_99pctCL");
TGraph *lim_nueapp_3p1_solar_excluded_95pctCL       = (TGraph*) f_sbn_proposal->Get("lim_nueapp_3p1_solar_excluded_95pctCL");
TGraph *lim_nueapp_3p1_nueC_excluded_95pctCL       = (TGraph*) f_sbn_proposal->Get("lim_nueapp_3p1_nueC_excluded_95pctCL");

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






// nue app Geniev3
TCanvas * nue_geniev3 = new TCanvas("nue_geniev3","",20,20,900,900);
nue_geniev3->Draw();

TH2F * hnue_geniev3 = (TH2F*) nue_geniev3->DrawFrame(8E-5,1E-2,1,1E+2);
hnue_geniev3->Draw();
nue_geniev3->SetLogx();
nue_geniev3->SetLogy();
hnue_geniev3->GetXaxis()->SetTitle("sin^{2}2#theta_{#mue}");
hnue_geniev3->GetXaxis()->SetTitleSize(0.03);
hnue_geniev3->GetXaxis()->SetLabelSize(0.03);
hnue_geniev3->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnue_geniev3->GetYaxis()->SetTitleSize(0.03);
hnue_geniev3->GetYaxis()->SetLabelSize(0.03);



//CAFAna_nue_90pctC->SetLineColor(kOrange);
//CAFAna_nue_90pctC->SetLineStyle(9);
//CAFAna_nue_90pctC->Draw("l");

//CAFAna_nue_90pctC2->SetLineColor(kRed);
//CAFAna_nue_90pctC2->SetLineStyle(9);
//CAFAna_nue_90pctC2->Draw("l");



//SBNfit_nue_90pctC->SetLineColor(kCyan);
//SBNfit_nue_90pctC->SetLineStyle(9);
//SBNfit_nue_90pctC->Draw("l");

VALOR_nue_90pctC->SetLineStyle(9);
//VALOR_nue_90pctC->Draw("l");

VALOR_nue_5s_2020->SetLineColor(kGreen+2);
VALOR_nue_5s_2020->SetLineStyle(9);
VALOR_nue_5s_2020->SetLineWidth(2);
//VALOR_nue_5s_2020->Draw("l");

VALOR_nue_5s_geniev3_stat->SetLineColor(kRed+2);
VALOR_nue_5s_geniev3_stat->SetLineStyle(9);
VALOR_nue_5s_geniev3_stat->SetLineWidth(2);
VALOR_nue_5s_geniev3_stat->Draw("l");



//VALOR_nue_5s_2020_syst->SetLineColor(kGreen+2);
//VALOR_nue_5s_2020_syst->SetLineWidth(2);
//VALOR_nue_5s_2020_syst->Draw("l");

VALOR_nue_5s_geniev3_spline->SetLineColor(kRed+2);
VALOR_nue_5s_geniev3_spline->SetLineWidth(2);
VALOR_nue_5s_geniev3_spline->SetLineStyle(7);
VALOR_nue_5s_geniev3_spline->Draw("l");

//VALOR_nue_5s_geniev3_spline_oldjobsub->SetLineColor(kGreen+2);
//VALOR_nue_5s_geniev3_spline_oldjobsub->SetLineWidth(2);
//VALOR_nue_5s_geniev3_spline_oldjobsub->Draw("l");

VALOR_nue_5s_geniev3_spline_proposal_fixed_params->SetLineColor(kBlack);
VALOR_nue_5s_geniev3_spline_proposal_fixed_params->SetLineWidth(2);
//VALOR_nue_5s_geniev3_spline_proposal_fixed_params->Draw("l");

VALOR_nue_5s_geniev3_spline_proposal_fixed_params_matrix->SetLineColor(kRed+2);
VALOR_nue_5s_geniev3_spline_proposal_fixed_params_matrix->SetLineWidth(2);
VALOR_nue_5s_geniev3_spline_proposal_fixed_params_matrix->Draw("l");

CAFAna_nue_5s_2020->SetLineColor(kOrange);
CAFAna_nue_5s_2020->SetLineStyle(9);
CAFAna_nue_5s_2020->SetLineWidth(2);
CAFAna_nue_5s_2020->Draw("l");

CAFAna_nue_5s_2020_syst->SetLineColor(kOrange);
CAFAna_nue_5s_2020_syst->SetLineWidth(2);
CAFAna_nue_5s_2020_syst->Draw("l");

CAFAna_nue_5s_2020_syst_mec->SetLineColor(kOrange);
CAFAna_nue_5s_2020_syst_mec->SetLineStyle(7);
CAFAna_nue_5s_2020_syst_mec->SetLineWidth(2);
CAFAna_nue_5s_2020_syst_mec->Draw("l");


SBNfit_nue_app_geniev3_5s_stat->SetLineColor(kBlue);
SBNfit_nue_app_geniev3_5s_stat->SetLineStyle(9);
SBNfit_nue_app_geniev3_5s_stat->SetLineWidth(2);
//SBNfit_nue_app_geniev3_5s_stat->Draw("l");
SBNfit_nue_app_geniev3_5s_syst->SetLineColor(kBlue);
SBNfit_nue_app_geniev3_5s_syst->SetLineWidth(2);
//SBNfit_nue_app_geniev3_5s_syst->Draw("l");

//lim_nueapp_3p1_sbnproposal_5sigCL->Draw("l");

//VALOR_nue_90pctC2->SetLineColor(kCyan);
//VALOR_nue_90pctC2->SetLineStyle(9);
//VALOR_nue_90pctC2->Draw("l");

TLegend * lnue_geniev3 = new TLegend(0.12,0.12,0.5,0.32);
lnue_geniev3->SetFillStyle(0);
lnue_geniev3->SetBorderSize(0);
lnue_geniev3->SetTextFont(132);
lnue_geniev3->SetTextSize(0.025);
lnue_geniev3->AddEntry(VALOR_nue_5s_geniev3_stat, "VALOR Modern 5#sigma CL stat-only Geniev3","L");
//lnue_geniev3->AddEntry(VALOR_nue_5s_2020_syst, "VALOR Modern 5#sigma CL syst Geniev3","L");
lnue_geniev3->AddEntry(VALOR_nue_5s_geniev3_spline, "VALOR Modern 5#sigma CL spline modern Geniev3","L");
//lnue_geniev3->AddEntry(VALOR_nue_5s_geniev3_spline_oldjobsub, "VALOR Modern 5#sigma CL spline oldjobsub Geniev3","L");
//lnue_geniev3->AddEntry(VALOR_nue_5s_geniev3_spline_proposal_fixed_params, "VALOR Modern 5#sigma CL spline proposal Geniev3","L");
lnue_geniev3->AddEntry(VALOR_nue_5s_geniev3_spline_proposal_fixed_params_matrix, "VALOR Modern 5#sigma CL spline proposal Geniev3","L");
lnue_geniev3->AddEntry(CAFAna_nue_5s_2020, "CAFAna Modern 5#sigma CL stat-only Geniev3","L");
lnue_geniev3->AddEntry(CAFAna_nue_5s_2020_syst, "CAFAna Modern 5#sigma CL proposal syst Geniev3","L");
lnue_geniev3->AddEntry(CAFAna_nue_5s_2020_syst_mec, "CAFAna Modern 5#sigma CL proposal syst + mec Geniev3","L");
//lnue_geniev3->AddEntry(SBNfit_nue_app_geniev3_5s_stat, "SBNfit Modern 5#sigma CL stat Geniev3","L");
//lnue_geniev3->AddEntry(SBNfit_nue_app_geniev3_5s_syst, "SBNfit Modern 5#sigma CL proposal syst Geniev3","L");
lnue_geniev3->Draw();

// save plot 
//nue_stat->SaveAs("/sbnd/app/users/tham/VALOR_master/nue_2020/images/nue_sensitivity_stat_only.eps");

// nue disapp Geniev3
TCanvas * nue_disapp_geniev3 = new TCanvas("nue_disapp_geniev3","",20,20,900,900);
nue_disapp_geniev3->Draw();

TH2F * hnue_disapp_geniev3 = (TH2F*) nue_disapp_geniev3->DrawFrame(1E-2,1E-2,1,1E+2);
hnue_disapp_geniev3->Draw();
nue_disapp_geniev3->SetLogx();
nue_disapp_geniev3->SetLogy();
hnue_disapp_geniev3->GetXaxis()->SetTitle("sin^{2}2#theta_{ee}");
hnue_disapp_geniev3->GetXaxis()->SetTitleSize(0.03);
hnue_disapp_geniev3->GetXaxis()->SetLabelSize(0.03);
hnue_disapp_geniev3->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnue_disapp_geniev3->GetYaxis()->SetTitleSize(0.03);
hnue_disapp_geniev3->GetYaxis()->SetLabelSize(0.03);

VALOR_nue_disapp_5s_geniev3_stat->SetLineColor(kRed+2);
VALOR_nue_disapp_5s_geniev3_stat->SetLineWidth(2);
VALOR_nue_disapp_5s_geniev3_stat->SetLineStyle(9);
VALOR_nue_disapp_5s_geniev3_stat->Draw("l");

VALOR_nue_disapp_5s_geniev3_spline->SetLineColor(kRed+2);
VALOR_nue_disapp_5s_geniev3_spline->SetLineWidth(2);
VALOR_nue_disapp_5s_geniev3_spline->Draw("l");

TLegend * lnue_disapp_geniev3 = new TLegend(0.12,0.12,0.5,0.32);
lnue_disapp_geniev3->SetFillStyle(0);
lnue_disapp_geniev3->SetBorderSize(0);
lnue_disapp_geniev3->SetTextFont(132);
lnue_disapp_geniev3->SetTextSize(0.025);
lnue_disapp_geniev3->AddEntry(VALOR_nue_disapp_5s_geniev3_stat, "VALOR Modern 5#sigma CL nue_disapp stat-only Geniev3","L");
lnue_disapp_geniev3->AddEntry(VALOR_nue_disapp_5s_geniev3_spline, "VALOR Modern 5#sigma CL nue_disapp spline modern Geniev3","L");
lnue_disapp_geniev3->Draw();




// nue only Geniev2
TCanvas * nue_Geniev2 = new TCanvas("nue_Geniev2","",20,20,900,900);
nue_Geniev2->Draw();

TH2F * hnue_Geniev2 = (TH2F*) nue_Geniev2->DrawFrame(8E-5,1E-2,1,1E+2);
hnue_Geniev2->Draw();
nue_Geniev2->SetLogx();
nue_Geniev2->SetLogy();
hnue_Geniev2->GetXaxis()->SetTitle("sin^{2}2#theta_{#mue}");
hnue_Geniev2->GetXaxis()->SetTitleSize(0.03);
hnue_Geniev2->GetXaxis()->SetLabelSize(0.03);
hnue_Geniev2->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnue_Geniev2->GetYaxis()->SetTitleSize(0.03);
hnue_Geniev2->GetYaxis()->SetLabelSize(0.03);

//VALOR_nue_5s_2020_geniev2_stat->SetLineColor(kMagenta+1);
VALOR_nue_5s_2020_geniev2_stat->SetLineColor(kBlack);
VALOR_nue_5s_2020_geniev2_stat->SetLineStyle(7);
VALOR_nue_5s_2020_geniev2_stat->SetLineWidth(3);
VALOR_nue_5s_2020_geniev2_stat->Draw("l");

//VALOR_nue_5s_2020_geniev2_stat2->SetLineColor(kGreen);
//VALOR_nue_5s_2020_geniev2_stat2->SetLineStyle(9);
//VALOR_nue_5s_2020_geniev2_stat2->Draw("l");



//VALOR_nue_5s_2020_geniev2_syst->SetLineColor(kMagenta+1);
VALOR_nue_5s_2020_geniev2_syst->SetLineColor(kBlack);
VALOR_nue_5s_2020_geniev2_syst->SetLineWidth(3);
VALOR_nue_5s_2020_geniev2_syst->Draw("l");


// Splines look like shit atm..
//VALOR_nue_5s_2020_geniev2_splines->SetLineWidth(2);
//VALOR_nue_5s_2020_geniev2_splines->Draw("l");



CAFAna_nue_5sig->SetLineColor(kOrange);
CAFAna_nue_5sig->SetLineStyle(7);
CAFAna_nue_5sig->SetLineWidth(3);
//CAFAna_nue_5sig->Draw("l");

CAFAna_nue_5sig_syst->SetLineColor(kOrange);
CAFAna_nue_5sig_syst->SetLineWidth(3);
//CAFAna_nue_5sig_syst->Draw("l");

SBNfit_nue_app_geniev2_5s_stat->SetLineColor(kBlue);
SBNfit_nue_app_geniev2_5s_stat->SetLineStyle(9);
SBNfit_nue_app_geniev2_5s_stat->SetLineWidth(2);
//SBNfit_nue_app_geniev2_5s_stat->Draw("l");

SBNfit_nue_app_geniev2_5s_syst->SetLineColor(kBlue);
SBNfit_nue_app_geniev2_5s_syst->SetLineWidth(2);
//SBNfit_nue_app_geniev2_5s_syst->Draw("l");

//external stuff
lim_nueapp_3p1_nomad_99pctCL->Draw("l");
lim_nueapp_3p1_bnl776_99pctCL->Draw("l");
lim_nueapp_3p1_karmen_99pctCL->Draw("l");
lim_nueapp_3p1_icarus_99pctCL->Draw("l");
lim_nueapp_3p1_opera_99pctCL->Draw("l");
lim_nueapp_3p1_miniboonenu_99pctCL->Draw("l");
lim_nueapp_3p1_lsndr1_99pctCL->Draw("l");
lim_nueapp_3p1_lsndr2_99pctCL->Draw("l");
lim_nueapp_3p1_lsndr3_99pctCL->Draw("l");
lim_nueapp_3p1_solar_excluded_95pctCL->Draw("l");
lim_nueapp_3p1_nueC_excluded_95pctCL->Draw("l");

TLegend * lnue_geniev2 = new TLegend(0.15,0.13,0.67,0.4);
lnue_geniev2->SetFillStyle(0);
lnue_geniev2->SetBorderSize(0);
lnue_geniev2->SetTextFont(132);
lnue_geniev2->SetTextSize(0.02);
lnue_geniev2->AddEntry(VALOR_nue_5s_2020_geniev2_stat, "SBN 5#sigma CL stat-only","L");
lnue_geniev2->AddEntry(VALOR_nue_5s_2020_geniev2_syst, "SBN 5#sigma CL stat+syst","L");
//lnue_geniev2->AddEntry(VALOR_nue_5s_2020_geniev2_stat, "VALOR Modern 5#sigma CL stat-only","L");
//lnue_geniev2->AddEntry(VALOR_nue_5s_2020_geniev2_syst, "VALOR Modern 5#sigma CL stat+syst","L");
//lnue_geniev2->AddEntry(CAFAna_nue_5sig, "CAFAna Modern 5#sigma CL stat-only","L");
//lnue_geniev2->AddEntry(CAFAna_nue_5sig_syst, "CAFAna Modern 5#sigma CL stat+syst","L");
//lnue_geniev2->AddEntry(SBNfit_nue_app_geniev2_5s_stat, "SBNfit Modern 5#sigma CL stat-only","L");
//lnue_geniev2->AddEntry(SBNfit_nue_app_geniev2_5s_syst, "SBNfit Modern 5#sigma CL stat+syst","L");
lnue_geniev2->AddEntry(lim_nueapp_3p1_nomad_99pctCL, "Nomad 99pct CL","L");
lnue_geniev2->AddEntry(lim_nueapp_3p1_bnl776_99pctCL, "bnl776 99pct CL","L");
lnue_geniev2->AddEntry(lim_nueapp_3p1_karmen_99pctCL, "Karmen 99pct CL","L");
lnue_geniev2->AddEntry(lim_nueapp_3p1_icarus_99pctCL, "ICARUS 99pct CL","L");
lnue_geniev2->AddEntry(lim_nueapp_3p1_opera_99pctCL, "Opera 99pct CL","L");
lnue_geniev2->AddEntry(lim_nueapp_3p1_miniboonenu_99pctCL, "MiniBooNE 99pct CL","L");
lnue_geniev2->AddEntry(lim_nueapp_3p1_lsndr1_99pctCL, "LSND 99pct CL","L");
lnue_geniev2->AddEntry(lim_nueapp_3p1_solar_excluded_95pctCL, "solar_excluded 95pct CL","L");
lnue_geniev2->AddEntry(lim_nueapp_3p1_nueC_excluded_95pctCL, "nueC_excluded 95pct CL","L");
lnue_geniev2->Draw();


nue_Geniev2->SaveAs("/sbnd/app/users/tham/VALOR_master/nue_2020/images/nue_sensitivity_geniev2.pdf");


// nue Geniev3 injected
TCanvas * nue_injected = new TCanvas("nue_injected","",20,20,700,900);
nue_injected->Draw();

TH2F * hnue_injected = (TH2F*) nue_injected->DrawFrame(1E-4,1E-1,1E-1,1E+1);
hnue_injected->Draw();
nue_injected->SetLogx();
nue_injected->SetLogy();
hnue_injected->GetXaxis()->SetTitle("sin^{2}2#theta_{#mue}");
hnue_injected->GetXaxis()->SetTitleSize(0.03);
hnue_injected->GetXaxis()->SetLabelSize(0.03);
hnue_injected->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnue_injected->GetYaxis()->SetTitleSize(0.03);
hnue_injected->GetYaxis()->SetLabelSize(0.03);


//injected point
TMarker *m = new TMarker(0.003, 1.2, 29);
m->SetMarkerSize(2);
m->Draw();

//VALOR_nue_5s_2020_injected->SetLineColor(kGreen+2);
//VALOR_nue_5s_2020_injected->SetLineStyle(9);
//VALOR_nue_5s_2020_injected->Draw("l");

//VALOR_nue_5s_2020_injected2->SetLineColor(kRed);
//VALOR_nue_5s_2020_injected2->SetLineStyle(9);
//VALOR_nue_5s_2020_injected2->Draw("l");


CAFAna_nue_5s_2020_injected->SetLineColor(kOrange);
CAFAna_nue_5s_2020_injected->SetLineStyle(9);
CAFAna_nue_5s_2020_injected->Draw("l");

CAFAna_nue_5s_2020_injected_syst->SetLineColor(kOrange);
CAFAna_nue_5s_2020_injected_syst->Draw("l");

TLegend * lnue_injected = new TLegend(0.15,0.2,0.67,0.3);
lnue_injected->SetFillStyle(0);
lnue_injected->SetBorderSize(0);
lnue_injected->SetTextFont(132);
lnue_injected->AddEntry(m, "Injected Signal: sin^{2}2#theta_{#mue} = 0.003, #Delta m^{2} = 1.2 eV^{2}", "p");
//lnue_injected->AddEntry(VALOR_nue_5s_2020_injected, "VALOR Modern 99pct CL stat-only Geniev3","L");
lnue_injected->AddEntry(CAFAna_nue_5s_2020_injected, "CAFAna Modern 99pct CL stat-only Geniev3","L");
lnue_injected->AddEntry(CAFAna_nue_5s_2020_injected_syst, "CAFAna Modern 99pct CL syst Geniev3","L");
//lnue_injected->AddEntry(CAFAna_nue_90pctC, "CAFAna Modern 5sigma CL","L");
lnue_injected->Draw();






}
