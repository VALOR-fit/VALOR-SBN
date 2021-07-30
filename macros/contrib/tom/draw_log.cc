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
TFile *f_external_3p1_limits    = new TFile("/sbnd/app/users/tham/VALOR_master/VALOR-SDK/macros/external_limits/sterile_nu/sterile_3p1_limits.root");

//TFile*f_valor_numu_geniev3_rhiannon_stat  = new TFile("/sbnd/app/users/tham/VALOR_master/detector_stuff/April2021/stat-only-2020a1_contours_as_graphs.root","read");
//TFile*f_valor_numu_geniev3_rhiannon_syst  = new TFile("/sbnd/app/users/tham/VALOR_master/detector_stuff/April2021/stat-syst-2020a1-03c1_contours_as_graphs.root","read");

TFile*f_valor_numu_stat         = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_numu_statonly.root","read");
TFile*f_valor_numu_03d1         = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_numu_03d1.root","read");
TFile*f_valor_numu_03d1_1pctEscale         = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_numu_03d1_1pctEscale.root","read");
TFile*f_valor_numu_03d1_5pctEscale         = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_numu_03d1_5pctEscale.root","read");

TFile*f_CAFAna_numu_syst        = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/CAFAna_numu_disapp_exclusion_2021.root","read");
TFile*f_SBNfit_numu_syst        = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/SBNfit_numu_disappearance_2021.root","read");

TFile*f_valor_numu_stat_injected_0pt07_1pt32  = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_numu_stat_injected_0.07_1.32.root","read");
TFile*f_valor_numu_03d1_injected_0pt07_1pt32  = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_numu_03d1_injected_0.07_1.32.root","read");

// sbnd only
TFile*f_valor_numu_sbnd_stat         = new TFile("/sbnd/app/users/tham/VALOR_master/rhiannon_thesis/detectors/stat-only-2020a1-nd_contours_as_graphs.root","read");
TFile*f_valor_numu_sbnd_CAF_stat     = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_numu_stat_CAFs.root","read");

// icarus only
TFile*f_valor_numu_icarus_stat       = new TFile("/sbnd/app/users/tham/VALOR_master/rhiannon_thesis/detectors/stat-only-2020a1-fd_contours_as_graphs.root","read");
TFile*f_valor_numu_icarus_CAF_stat   = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_numu_ICARUS_CAFs.root","read");

// nue files
//TFile *f_sbnfit_nue             = new TFile("/sbnd/data/users/tham/fitter_data/nue_modern/SBNfit.root","read");
TFile *f_cafana_nue             = new TFile("/sbnd/data/users/tham/fitter_data/nue_modern/CAFAna_nue_modern.root","read");
//TFile *f_cafana_nue2             = new TFile("/sbnd/data/users/tham/fitter_data/nue_modern/CAFAna_nue_exclusion.root","read");


TFile*f_valor_nue2020            = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_2020.root","read");
//TFile*f_valor_nue2020_stat            = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_2020_stat.root","read");
TFile*f_valor_nue2020_geniev2_stat    = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/geniev2/output_contours_as_graphs_stat.root","read");
TFile*f_valor_nue2020_geniev2_stat2    = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/geniev2/output_contours_as_graphs_statv2.root","read");
TFile*f_valor_nue2020_geniev2_syst    = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/geniev2/output_contours_as_graphs_syst.root","read");
TFile*f_valor_nue2020_geniev2_splines    = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/geniev2/output_contours_as_graphs_splines.root","read");
//TFile*f_valor_nue2020_syst    = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/syst_temp/output_contours_as_graphs.root","read");

TFile*f_valor_geniev3_stat                                     = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_stat_fixed_params.root","read");
TFile*f_valor_geniev3_splines_proposal_fixed_params            = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_spline_proposal_fixed_params.root","read");
//TFile*f_valor_geniev3_splines_proposal_fixed_params_matrix     = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_spline_proposal_fixed_matrix.root","read");
TFile*f_valor_geniev3_splines_proposal_fixed_params_matrix     = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_spline_new_proposal.root","read");
//TFile*f_valor_geniev3_splines                                  = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_spline_fixed_matrix.root","read");
TFile*f_valor_geniev3_splines                                  = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_spline_new.root","read");
TFile*f_valor_geniev3_splines_POT                             = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_nue_app_27july.root","read");
TFile*f_valor_geniev3_splines_oldjobsub                        = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_spline_oldjobsub.root","read");
TFile*f_valor_nue_app_03d1_1pctEscale                             = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_nue_03d1_1pctEscale.root","read");
TFile*f_valor_nue_app_03d1_5pctEscale                             = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_nue_03d1_5pctEscale.root","read");

TFile*f_valor_geniev3_injected_sinsq2th_0pt003_dmsq_1pt2         = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_injected_sinsq2th_0.003_dmsq_1.2.root","read");
TFile*f_valor_geniev3_stat_injected_sinsq2th_0pt003_dmsq_1pt2    = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_stat_injected_sinsq2th_0.003_dmsq_1.2.root","read");
                                              
TFile*f_valor_nue_disapp_geniev3_stat                          = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_nue_disapp_stat.root","read");
TFile*f_valor_nue_disapp_geniev3_syst                          = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_nue_disapp_spline.root","read");

TFile*f_valor_nue_disapp_geniev3_injected_0pt4_3               = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_nue_disapp_injected_0.4_3.root","read");

TFile*f_cafana_nue2020            = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/CAFAna_nue_app_exclusion_2021.root","read");
TFile*f_cafana_nue2020_injected            = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/CAFAna_nue_app_allowed.root","read");

TFile *f_sbnfit_nue_app_geniev2             = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/geniev2/SBNfit_NueApp_sensitivity_NoMCIntrinsicError.root","read");
TFile *f_sbnfit_nue_app_geniev3_updated     = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/SBNfit_NueAppear_sensitivity_updated.root","read");
TFile *f_sbnfit_nue_app_geniev3_2021        = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/SBNfit_NueAppear_sensitivity_2021.root","read");


// get numu contours
TGraph *VALOR_numu_stat                      = (TGraph*) f_valor_numu_stat->Get("contour_5sigma_lin_0;1");
TGraph *VALOR_numu_03d1                      = (TGraph*) f_valor_numu_03d1->Get("contour_5sigma_lin_0;1");
TGraph *VALOR_numu_03d1_1pctEscale           = (TGraph*) f_valor_numu_03d1_1pctEscale->Get("contour_5sigma_lin_0;1");
TGraph *VALOR_numu_03d1_5pctEscale           = (TGraph*) f_valor_numu_03d1_5pctEscale->Get("contour_5sigma_lin_0;1");

TGraph *VALOR_numu_stat_injected_0pt07_1pt32 = (TGraph*) f_valor_numu_stat_injected_0pt07_1pt32->Get("contour_5sigma_lin_0;1");
TGraph *VALOR_numu_03d1_injected_0pt07_1pt32 = (TGraph*) f_valor_numu_03d1_injected_0pt07_1pt32->Get("contour_5sigma_lin_0;1");

TGraph *VALOR_numu_sbnd_CAF_stat             = (TGraph*) f_valor_numu_sbnd_CAF_stat->Get("contour_5sigma_lin_0;1");
TGraph *VALOR_numu_icarus_CAF_stat           = (TGraph*) f_valor_numu_icarus_CAF_stat->Get("contour_5sigma_lin_0;1");
TGraph *VALOR_numu_sbnd_stat                 = (TGraph*) f_valor_numu_sbnd_stat->Get("stat_only_5sigma_lin_0;1");
TGraph *VALOR_numu_icarus_stat               = (TGraph*) f_valor_numu_icarus_stat->Get("stat_only_5sigma_lin_0;1");

TGraph *lim_numudis_3p1_sbnproposal_90pctCL  = (TGraph*) f_external_3p1_limits->Get("lim_numudis_3p1_sbnproposal_90pctCL");
TGraph *lim_numudis_3p1_sbnproposal_3sigCL   = (TGraph*) f_external_3p1_limits->Get("lim_numudis_3p1_sbnproposal_3sigCL");
TGraph *lim_numudis_3p1_sbnproposal_5sigCL   = (TGraph*) f_external_3p1_limits->Get("lim_numudis_3p1_sbnproposal_5sigCL");

TGraph *SBNfit_numu_stat                     = (TGraph*) f_SBNfit_numu_syst->Get("STATONLY_5sigma");
TGraph *SBNfit_numu_syst                     = (TGraph*) f_SBNfit_numu_syst->Get("g5sigma");
TGraph *CAFAna_numu_stat                     = (TGraph*) f_CAFAna_numu_syst->Get("all_stat_5sig");
TGraph *CAFAna_numu_syst                     = (TGraph*) f_CAFAna_numu_syst->Get("all_syst_5sig");

/////////////////////
// get nue contours
/////////////////////

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
TGraph *VALOR_nue_5s_geniev3_POT                     = (TGraph*) f_valor_geniev3_splines_POT->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_03d1_1pctEscale                     = (TGraph*) f_valor_nue_app_03d1_1pctEscale->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_03d1_5pctEscale                     = (TGraph*) f_valor_nue_app_03d1_5pctEscale->Get("contour_5sigma_lin_0");

TGraph *VALOR_nue_5s_geniev3_injected_sinsq2th_0pt003_dmsq_1pt2          = (TGraph*) f_valor_geniev3_injected_sinsq2th_0pt003_dmsq_1pt2->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_stat_injected_sinsq2th_0pt003_dmsq_1pt2     = (TGraph*) f_valor_geniev3_stat_injected_sinsq2th_0pt003_dmsq_1pt2->Get("contour_5sigma_lin_8");

TGraph *VALOR_nue_disapp_5s_geniev3_stat                       = (TGraph*) f_valor_nue_disapp_geniev3_stat->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_spline                     = (TGraph*) f_valor_nue_disapp_geniev3_syst->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_injected_0pt4_3                   = (TGraph*) f_valor_nue_disapp_geniev3_injected_0pt4_3->Get("contour_5sigma_lin_0");

TGraph *CAFAna_nue_5s_2020                   = (TGraph*) f_cafana_nue2020->Get("all_stat_5sig");
TGraph *CAFAna_nue_5s_2020_syst                   = (TGraph*) f_cafana_nue2020->Get("all_syst_5sig");

TGraph *CAFAna_nue_5s_2020_injected                   = (TGraph*) f_cafana_nue2020_injected->Get("all_stat_5sig_10");
TGraph *CAFAna_nue_5s_2020_injected_syst                   = (TGraph*) f_cafana_nue2020_injected->Get("all_syst_5sig_1");

TGraph *SBNfit_nue_app_geniev2_5s_stat                   = (TGraph*) f_sbnfit_nue_app_geniev2->Get("STATONLY_5sigma");
TGraph *SBNfit_nue_app_geniev2_5s_syst                   = (TGraph*) f_sbnfit_nue_app_geniev2->Get("g5sigma");

TGraph *SBNfit_nue_app_geniev3_5s_stat                   = (TGraph*) f_sbnfit_nue_app_geniev3_2021->Get("STATONLY_5sigma");
TGraph *SBNfit_nue_app_geniev3_5s_syst_2021              = (TGraph*) f_sbnfit_nue_app_geniev3_2021->Get("g5sigma");
TGraph *SBNfit_nue_app_geniev3_5s_syst_updated           = (TGraph*) f_sbnfit_nue_app_geniev3_updated->Get("g5sigma");

TGraph *lim_nueapp_3p1_sbnproposal_5sigCL        = (TGraph*) f_external_3p1_limits->Get("lim_nueapp_3p1_sbnproposal_5sigCL");
TGraph *lim_nueapp_3p1_nomad_99pctCL             = (TGraph*) f_external_3p1_limits->Get("lim_nueapp_3p1_nomad_99pctCL");
TGraph *lim_nueapp_3p1_bnl776_99pctCL            = (TGraph*) f_external_3p1_limits->Get("lim_nueapp_3p1_bnl776_99pctCL");
TGraph *lim_nueapp_3p1_karmen_99pctCL            = (TGraph*) f_external_3p1_limits->Get("lim_nueapp_3p1_karmen_99pctCL");
TGraph *lim_nueapp_3p1_icarus_99pctCL            = (TGraph*) f_external_3p1_limits->Get("lim_nueapp_3p1_icarus_99pctCL");
TGraph *lim_nueapp_3p1_opera_99pctCL             = (TGraph*) f_external_3p1_limits->Get("lim_nueapp_3p1_opera_99pctCL");
TGraph *lim_nueapp_3p1_miniboonenu_99pctCL       = (TGraph*) f_external_3p1_limits->Get("lim_nueapp_3p1_miniboonenu_99pctCL");
TGraph *lim_nueapp_3p1_lsndr1_99pctCL            = (TGraph*) f_external_3p1_limits->Get("lim_nueapp_3p1_lsndr1_99pctCL");
TGraph *lim_nueapp_3p1_lsndr2_99pctCL            = (TGraph*) f_external_3p1_limits->Get("lim_nueapp_3p1_lsndr2_99pctCL");
TGraph *lim_nueapp_3p1_lsndr3_99pctCL            = (TGraph*) f_external_3p1_limits->Get("lim_nueapp_3p1_lsndr3_99pctCL");
TGraph *lim_nueapp_3p1_solar_excluded_95pctCL    = (TGraph*) f_external_3p1_limits->Get("lim_nueapp_3p1_solar_excluded_95pctCL");
TGraph *lim_nueapp_3p1_nueC_excluded_95pctCL     = (TGraph*) f_external_3p1_limits->Get("lim_nueapp_3p1_nueC_excluded_95pctCL");

TGraph *lim_nuedis_3p1_t2knd280excluded_95pctCL  = (TGraph*) f_external_3p1_limits->Get("lim_nuedis_3p1_t2knd280excluded_95pctCL");
TGraph *lim_nuedis_3p1_t2knd280allowed_90pctCL   = (TGraph*) f_external_3p1_limits->Get("lim_nuedis_3p1_t2knd280allowed_90pctCL");
TGraph *lim_nuedis_3p1_t2knd280allowed_68pctCL   = (TGraph*) f_external_3p1_limits->Get("lim_nuedis_3p1_t2knd280allowed_68pctCL");

TGraph *lim_numudis_3p1_minosp_90pctCL   = (TGraph*) f_external_3p1_limits->Get("lim_numudis_3p1_minosp_90pctCL");
TGraph *lim_numudis_3p1_minisciboone_90pctCL   = (TGraph*) f_external_3p1_limits->Get("lim_numudis_3p1_minisciboone_90pctCL");

// nue app Geniev3
TCanvas * nue_geniev3 = new TCanvas("nue_geniev3","",20,20,900,900);
nue_geniev3->Draw();

TH2F * hnue_geniev3 = (TH2F*) nue_geniev3->DrawFrame(8E-5,1E-2,1,1E+2);
hnue_geniev3->Draw();
nue_geniev3->SetLogx();
nue_geniev3->SetLogy();
hnue_geniev3->GetXaxis()->SetTitle("sin^{2}2#theta_{#mue}");
hnue_geniev3->GetXaxis()->SetTitleSize(0.04);
hnue_geniev3->GetXaxis()->SetLabelSize(0.04);
hnue_geniev3->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnue_geniev3->GetYaxis()->SetTitleSize(0.04);
hnue_geniev3->GetYaxis()->SetLabelSize(0.04);
hnue_geniev3->GetYaxis()->SetTitleOffset(1.2);

VALOR_nue_5s_geniev3_stat->SetLineColor(kRed+2);
VALOR_nue_5s_geniev3_stat->SetLineWidth(4);
VALOR_nue_5s_geniev3_stat->SetLineStyle(9);
VALOR_nue_5s_geniev3_stat->Draw("l");



//VALOR_nue_5s_2020_syst->SetLineColor(kGreen+2);
//VALOR_nue_5s_2020_syst->SetLineWidth(2);
//VALOR_nue_5s_2020_syst->Draw("l");

VALOR_nue_5s_geniev3_spline->SetLineColor(kRed+2);
VALOR_nue_5s_geniev3_spline->SetLineWidth(4);
VALOR_nue_5s_geniev3_spline->SetLineStyle(7);
//VALOR_nue_5s_geniev3_spline->Draw("l");

VALOR_nue_5s_geniev3_POT->SetLineColor(kRed+2);
VALOR_nue_5s_geniev3_POT->SetLineWidth(4);
//VALOR_nue_5s_geniev3_POT->SetLineStyle(9);
VALOR_nue_5s_geniev3_POT->Draw("l");

VALOR_nue_5s_03d1_1pctEscale->SetLineColor(kRed);
VALOR_nue_5s_03d1_1pctEscale->SetLineWidth(4);
//VALOR_nue_5s_03d1_1pctEscale->Draw("l");
VALOR_nue_5s_03d1_5pctEscale->SetLineColor(kBlue);
VALOR_nue_5s_03d1_5pctEscale->SetLineWidth(4);
//VALOR_nue_5s_03d1_5pctEscale->Draw("l");




CAFAna_nue_5s_2020->SetLineColor(kOrange);
CAFAna_nue_5s_2020->SetLineWidth(4);
CAFAna_nue_5s_2020->SetLineStyle(9);
CAFAna_nue_5s_2020->Draw("l");

CAFAna_nue_5s_2020_syst->SetLineColor(kOrange);
//CAFAna_nue_5s_2020_syst->SetLineStyle(9);
CAFAna_nue_5s_2020_syst->SetLineWidth(4);
CAFAna_nue_5s_2020_syst->Draw("l");

SBNfit_nue_app_geniev3_5s_stat->SetLineColor(kBlue);
SBNfit_nue_app_geniev3_5s_stat->SetLineWidth(4);
SBNfit_nue_app_geniev3_5s_stat->SetLineStyle(9);
SBNfit_nue_app_geniev3_5s_stat->Draw("l");
SBNfit_nue_app_geniev3_5s_syst_2021->SetLineColor(kBlue);
//SBNfit_nue_app_geniev3_5s_syst_2021->SetLineStyle(9);
SBNfit_nue_app_geniev3_5s_syst_2021->SetLineWidth(4);
SBNfit_nue_app_geniev3_5s_syst_2021->Draw("l");

//lim_nueapp_3p1_sbnproposal_5sigCL->Draw("l");


TLegend * lnue_geniev3 = new TLegend(0.12,0.12,0.5,0.32);
lnue_geniev3->SetFillStyle(0);
lnue_geniev3->SetBorderSize(0);
lnue_geniev3->SetTextFont(132);
lnue_geniev3->SetTextSize(0.03);
lnue_geniev3->AddEntry(VALOR_nue_5s_geniev3_stat, "VALOR 5#sigma CL #nu_{e} app stat-only ","L");
//lnue_geniev3->AddEntry(VALOR_nue_5s_2020_syst, "VALOR Modern 5#sigma CL syst Geniev3","L");
lnue_geniev3->AddEntry(VALOR_nue_5s_geniev3_POT, "VALOR 5#sigma CL #nu_{e} app stat+syst ","L");
//lnue_geniev3->AddEntry(VALOR_nue_5s_03d1_1pctEscale, "5#sigma CL #nu_{e} app stat + syst + 1%  Energy Scale","L");
lnue_geniev3->AddEntry(CAFAna_nue_5s_2020, "CAFAna 5#sigma CL #nu_{e} stat-only","L");
lnue_geniev3->AddEntry(CAFAna_nue_5s_2020_syst, "CAFAna 5#sigma CL #nu_{e} app stat+syst","L");
lnue_geniev3->AddEntry(SBNfit_nue_app_geniev3_5s_stat, "SBNfit 5#sigma CL #nu_{e} app stat-only","L");
lnue_geniev3->AddEntry(SBNfit_nue_app_geniev3_5s_syst_2021, "SBNfit 5#sigma CL #nu_{e} app stat+syst","L");
lnue_geniev3->Draw();

// save plot 
//nue_geniev3->SaveAs("/sbnd/app/users/tham/VALOR_master/nue_2020/images/nue_app_03d1_1pctEscale.pdf");

// nue app Geniev3 with externals
TCanvas * nue_geniev3_external = new TCanvas("nue_geniev3_external","",20,20,900,900);
nue_geniev3_external->Draw();

TH2F * hnue_geniev3_external = (TH2F*) nue_geniev3_external->DrawFrame(8E-5,1E-2,1,1E+2);
hnue_geniev3_external->Draw();
nue_geniev3_external->SetLogx();
nue_geniev3_external->SetLogy();
hnue_geniev3_external->GetXaxis()->SetTitle("sin^{2}2#theta_{#mue}");
hnue_geniev3_external->GetXaxis()->SetTitleSize(0.03);
hnue_geniev3_external->GetXaxis()->SetLabelSize(0.03);
hnue_geniev3_external->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnue_geniev3_external->GetYaxis()->SetTitleSize(0.03);
hnue_geniev3_external->GetYaxis()->SetLabelSize(0.03);

VALOR_nue_5s_geniev3_stat->SetLineColor(kRed+2);
VALOR_nue_5s_geniev3_stat->SetLineWidth(4);
VALOR_nue_5s_geniev3_stat->Draw("l");

VALOR_nue_5s_geniev3_spline->SetLineColor(kRed+2);
VALOR_nue_5s_geniev3_spline->SetLineWidth(4);
VALOR_nue_5s_geniev3_spline->SetLineStyle(1);
VALOR_nue_5s_geniev3_spline->Draw("l");

lim_nueapp_3p1_lsndr1_99pctCL->Draw("l");
lim_nueapp_3p1_lsndr1_99pctCL->SetLineColor(kGreen+1);
lim_nueapp_3p1_lsndr1_99pctCL->SetFillColor(kGreen+1);
lim_nueapp_3p1_lsndr2_99pctCL->Draw("l");
lim_nueapp_3p1_lsndr2_99pctCL->SetLineColor(kGreen+1);
lim_nueapp_3p1_lsndr2_99pctCL->SetFillColor(kGreen+1);
lim_nueapp_3p1_lsndr3_99pctCL->Draw("l");
lim_nueapp_3p1_lsndr3_99pctCL->SetLineColor(kGreen+1);
lim_nueapp_3p1_lsndr3_99pctCL->SetFillColor(kGreen+1);
lim_nueapp_3p1_karmen_99pctCL->SetLineWidth(2);
lim_nueapp_3p1_karmen_99pctCL->Draw("l");

TLegend * lnue_geniev3_external = new TLegend(0.12,0.12,0.5,0.32);
lnue_geniev3_external->SetFillStyle(0);
lnue_geniev3_external->SetBorderSize(0);
lnue_geniev3_external->SetTextFont(132);
lnue_geniev3_external->SetTextSize(0.025);
lnue_geniev3_external->AddEntry(VALOR_nue_5s_geniev3_stat, "SBN VALOR 5#sigma CL stat-only uncertainty","L");
lnue_geniev3_external->AddEntry(VALOR_nue_5s_geniev3_spline, "SBN VALOR 5#sigma CL w. flux + xsection uncertainty","L");
lnue_geniev3_external->AddEntry(lim_nueapp_3p1_lsndr1_99pctCL, "LSND 99% CL","L");
lnue_geniev3_external->AddEntry(lim_nueapp_3p1_karmen_99pctCL, "KARMEN 99% CL","L");
lnue_geniev3_external->Draw();

// save plot 
nue_geniev3_external->SaveAs("/sbnd/app/users/tham/VALOR_master/nue_2020/images/nue_app_geniev3_external.pdf");


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
VALOR_nue_disapp_5s_geniev3_stat->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_stat->SetLineStyle(9);
VALOR_nue_disapp_5s_geniev3_stat->Draw("l");

VALOR_nue_disapp_5s_geniev3_spline->SetLineColor(kRed+2);
VALOR_nue_disapp_5s_geniev3_spline->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_spline->Draw("l");

lim_nuedis_3p1_t2knd280excluded_95pctCL->Draw("l");
lim_nuedis_3p1_t2knd280allowed_90pctCL->Draw("l");
lim_nuedis_3p1_t2knd280allowed_68pctCL->Draw("l");


TLegend * lnue_disapp_geniev3 = new TLegend(0.12,0.12,0.5,0.32);
lnue_disapp_geniev3->SetFillStyle(0);
lnue_disapp_geniev3->SetBorderSize(0);
lnue_disapp_geniev3->SetTextFont(132);
lnue_disapp_geniev3->SetTextSize(0.025);
lnue_disapp_geniev3->AddEntry(VALOR_nue_disapp_5s_geniev3_stat, "SBN VALOR 5#sigma CL stat-only uncertainty","L");
lnue_disapp_geniev3->AddEntry(VALOR_nue_disapp_5s_geniev3_spline, "SBN VALOR 5#sigma CL w. flux + xsection uncertainty","L");
lnue_disapp_geniev3->AddEntry(lim_nuedis_3p1_t2knd280excluded_95pctCL, "T2K/ND280 excluded 95% CL","L");
lnue_disapp_geniev3->AddEntry(lim_nuedis_3p1_t2knd280allowed_90pctCL, "T2K/ND280 allowed 90% CL","L");
lnue_disapp_geniev3->AddEntry(lim_nuedis_3p1_t2knd280allowed_68pctCL, "T2K/ND280 allowed 68% CL","L");
lnue_disapp_geniev3->Draw();

// save plot 
nue_disapp_geniev3->SaveAs("/sbnd/app/users/tham/VALOR_master/nue_2020/images/nue_disapp_geniev3_external.pdf");




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


//nue_Geniev2->SaveAs("/sbnd/app/users/tham/VALOR_master/nue_2020/images/nue_sensitivity_geniev2.pdf");


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

VALOR_nue_5s_geniev3_stat_injected_sinsq2th_0pt003_dmsq_1pt2->SetLineColor(kRed+2);
VALOR_nue_5s_geniev3_stat_injected_sinsq2th_0pt003_dmsq_1pt2->SetLineStyle(9);
VALOR_nue_5s_geniev3_stat_injected_sinsq2th_0pt003_dmsq_1pt2->SetLineWidth(4);
VALOR_nue_5s_geniev3_stat_injected_sinsq2th_0pt003_dmsq_1pt2->Draw("l");


VALOR_nue_5s_geniev3_injected_sinsq2th_0pt003_dmsq_1pt2->SetLineColor(kRed+2);
VALOR_nue_5s_geniev3_injected_sinsq2th_0pt003_dmsq_1pt2->SetLineWidth(4);
VALOR_nue_5s_geniev3_injected_sinsq2th_0pt003_dmsq_1pt2->Draw("l");



CAFAna_nue_5s_2020_injected->SetLineColor(kOrange);
CAFAna_nue_5s_2020_injected->SetLineStyle(9);
CAFAna_nue_5s_2020_injected->SetLineWidth(4);
CAFAna_nue_5s_2020_injected->Draw("l");

CAFAna_nue_5s_2020_injected_syst->SetLineColor(kOrange);
CAFAna_nue_5s_2020_injected_syst->SetLineWidth(4);
CAFAna_nue_5s_2020_injected_syst->Draw("l");

TLegend * lnue_injected = new TLegend(0.1,0.12,0.65,0.29);
lnue_injected->SetFillStyle(0);
lnue_injected->SetBorderSize(0);
lnue_injected->SetTextFont(132);
lnue_injected->SetTextSize(0.02);
lnue_injected->AddEntry(m, "Injected Signal: sin^{2}2#theta_{#mue} = 0.003, #Delta m^{2} = 1.2 eV^{2}", "p");
lnue_injected->AddEntry(VALOR_nue_5s_geniev3_stat_injected_sinsq2th_0pt003_dmsq_1pt2, "VALOR Modern 5#sigma CL nue_app stat-only Geniev3","L");
lnue_injected->AddEntry(VALOR_nue_5s_geniev3_injected_sinsq2th_0pt003_dmsq_1pt2, "VALOR Modern 5#sigma CL nue_app stat+syst Geniev3","L");
lnue_injected->AddEntry(CAFAna_nue_5s_2020_injected, "CAFAna Modern 5#sigma CL nue_app stat-only Geniev3","L");
lnue_injected->AddEntry(CAFAna_nue_5s_2020_injected_syst, "CAFAna Modern 5#sigma CL nue_app stat+proposal_syst Geniev3","L");
lnue_injected->Draw();

// nue disapp Geniev3 injected
TCanvas * nue_disapp_injected = new TCanvas("nue_disapp_injected","",20,20,700,900);
nue_disapp_injected->Draw();

TH2F * hnue_disapp_injected = (TH2F*) nue_disapp_injected->DrawFrame(1E-1,1E-1,1,1E+1);
hnue_disapp_injected->Draw();
nue_disapp_injected->SetLogx();
nue_disapp_injected->SetLogy();
hnue_disapp_injected->GetXaxis()->SetTitle("sin^{2}2#theta_{ee}");
hnue_disapp_injected->GetXaxis()->SetTitleSize(0.03);
hnue_disapp_injected->GetXaxis()->SetLabelSize(0.03);
hnue_disapp_injected->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnue_disapp_injected->GetYaxis()->SetTitleSize(0.03);
hnue_disapp_injected->GetYaxis()->SetLabelSize(0.03);


//injected point
TMarker *m2 = new TMarker(0.4, 3, 29);
m2->SetMarkerSize(2);
m2->Draw();

VALOR_nue_disapp_5s_geniev3_injected_0pt4_3->SetLineColor(kRed+2);
VALOR_nue_disapp_5s_geniev3_injected_0pt4_3->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_injected_0pt4_3->Draw("l");

TLegend * lnuedisapp_injected = new TLegend(0.1,0.12,0.65,0.29);
lnuedisapp_injected->SetFillStyle(0);
lnuedisapp_injected->SetBorderSize(0);
lnuedisapp_injected->SetTextFont(132);
lnuedisapp_injected->SetTextSize(0.02);
lnuedisapp_injected->AddEntry(m2, "Injected Signal: sin^{2}2#theta_{#mue} = 0.4, #Delta m^{2} = 3 eV^{2}", "p");
lnuedisapp_injected->AddEntry(VALOR_nue_disapp_5s_geniev3_injected_0pt4_3, "VALOR Modern 5#sigma CL nue_disapp stat+syst Geniev3","L");
lnuedisapp_injected->Draw();

// numu disapp Geniev3
TCanvas * numu_geniev3 = new TCanvas("numu_geniev3","",20,20,900,900);
numu_geniev3->Draw();

TH2F * hnumu_geniev3 = (TH2F*) numu_geniev3->DrawFrame(1E-3,1E-2,1,1E+2);
hnumu_geniev3->Draw();
numu_geniev3->SetLogx();
numu_geniev3->SetLogy();
hnumu_geniev3->GetXaxis()->SetTitle("sin^{2}2#theta_{#mu#mu}");
hnumu_geniev3->GetXaxis()->SetTitleSize(0.04);
hnumu_geniev3->GetXaxis()->SetLabelSize(0.04);
hnumu_geniev3->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnumu_geniev3->GetYaxis()->SetTitleSize(0.04);
hnumu_geniev3->GetYaxis()->SetLabelSize(0.04);
hnumu_geniev3->GetYaxis()->SetTitleOffset(1.2);

VALOR_numu_stat->SetLineColor(kRed+2);
VALOR_numu_stat->SetLineWidth(4);
VALOR_numu_stat->SetLineStyle(9);
VALOR_numu_stat->Draw("l");
VALOR_numu_03d1->SetLineColor(kRed+2);
VALOR_numu_03d1->SetLineWidth(4);
//VALOR_numu_03d1->SetLineStyle(9);
VALOR_numu_03d1->Draw("l");


VALOR_numu_03d1_1pctEscale->SetLineColor(kRed);
VALOR_numu_03d1_1pctEscale->SetLineWidth(4);
//VALOR_numu_03d1_1pctEscale->Draw("L");
//VALOR_numu_03d1_5pctEscale->SetLineColor(kGreen+1);
//VALOR_numu_03d1_5pctEscale->SetLineStyle(7);
//VALOR_numu_03d1_5pctEscale->SetLineWidth(4);
//VALOR_numu_03d1_5pctEscale->Draw("L");

CAFAna_numu_stat->SetLineColor(kOrange);
CAFAna_numu_stat->SetLineWidth(4);
CAFAna_numu_stat->SetLineStyle(9);
//CAFAna_numu_stat->Draw("l");
CAFAna_numu_syst->SetLineColor(kOrange);
CAFAna_numu_syst->SetLineWidth(4);
//CAFAna_numu_syst->SetLineStyle(9);
//CAFAna_numu_syst->Draw("l");

SBNfit_numu_stat->SetLineColor(kBlue);
SBNfit_numu_stat->SetLineWidth(4);
SBNfit_numu_stat->SetLineStyle(9);
//SBNfit_numu_stat->Draw("l");
SBNfit_numu_syst->SetLineColor(kBlue);
SBNfit_numu_syst->SetLineWidth(4);
//SBNfit_numu_syst->SetLineStyle(9);
//SBNfit_numu_syst->Draw("l");




lim_numudis_3p1_minosp_90pctCL->Draw("l");
lim_numudis_3p1_minosp_90pctCL->SetLineColor(kGreen-7);
lim_numudis_3p1_minisciboone_90pctCL->Draw("l");
lim_numudis_3p1_minisciboone_90pctCL->SetLineColor(kViolet+2);


TLegend * lnumu_geniev3 = new TLegend(0.12,0.12,0.5,0.32);
lnumu_geniev3->SetFillStyle(0);
lnumu_geniev3->SetBorderSize(0);
lnumu_geniev3->SetTextFont(132);
lnumu_geniev3->SetTextSize(0.025);
lnumu_geniev3->AddEntry(VALOR_numu_stat, "SBN VALOR 5#sigma CL stat-only uncertainty","L");
lnumu_geniev3->AddEntry(VALOR_numu_03d1, "SBN VALOR 5#sigma CL w. flux + xsection uncertainty","L");
//lnumu_geniev3->AddEntry(VALOR_numu_03d1_1pctEscale, "5#sigma CL #nu_{#mu} disapp stat + syst + 1% Energy Scale","L");
//lnumu_geniev3->AddEntry(CAFAna_numu_stat, "CAFAna Modern 5#sigma CL numu_disapp stat-only Geniev3","L");
//lnumu_geniev3->AddEntry(CAFAna_numu_syst, "CAFAna Modern 5#sigma CL numu_disapp stat+syst Geniev3","L");
//lnumu_geniev3->AddEntry(SBNfit_numu_stat, "SBNfit Modern 5#sigma CL numu_disapp stat-only Geniev3","L");
//lnumu_geniev3->AddEntry(SBNfit_numu_syst, "SBNfit Modern 5#sigma CL numu_disapp stat+syst Geniev3","L");
lnumu_geniev3->AddEntry(lim_numudis_3p1_minosp_90pctCL, "MINOS/MINOS+ 90% CL","L");
lnumu_geniev3->AddEntry(lim_numudis_3p1_minisciboone_90pctCL, "MiniBooNE/SciBooNE 90% CL","L");
lnumu_geniev3->Draw();

numu_geniev3->SaveAs("/sbnd/app/users/tham/VALOR_master/nue_2020/images/numu_external.pdf");

// numu disapp Geniev3 injected
TCanvas * numu_injected = new TCanvas("numu_injected","",20,20,700,900);
numu_injected->Draw();

TH2F * hnumu_injected = (TH2F*) numu_injected->DrawFrame(2E-2,4E-1,0.3,3E+0);
hnumu_injected->Draw();
numu_injected->SetLogx();
numu_injected->SetLogy();
hnumu_injected->GetXaxis()->SetTitle("sin^{2}2#theta_{#mu#mu}");
hnumu_injected->GetXaxis()->SetTitleSize(0.03);
hnumu_injected->GetXaxis()->SetLabelSize(0.03);
hnumu_injected->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnumu_injected->GetYaxis()->SetTitleSize(0.03);
hnumu_injected->GetYaxis()->SetLabelSize(0.03);


//injected point
TMarker *m3 = new TMarker(0.07, 1.32, 29);
m3->SetMarkerSize(2);
m3->Draw();

VALOR_numu_stat_injected_0pt07_1pt32->SetLineColor(kRed+2);
VALOR_numu_stat_injected_0pt07_1pt32->SetLineWidth(4);
VALOR_numu_stat_injected_0pt07_1pt32->SetLineStyle(9);
VALOR_numu_stat_injected_0pt07_1pt32->Draw("l");

VALOR_numu_03d1_injected_0pt07_1pt32->SetLineColor(kRed+2);
VALOR_numu_03d1_injected_0pt07_1pt32->SetLineWidth(4);
VALOR_numu_03d1_injected_0pt07_1pt32->Draw("l");


TLegend * lnumu_injected_geniev3 = new TLegend(0.12,0.12,0.5,0.32);
lnumu_injected_geniev3->SetFillStyle(0);
lnumu_injected_geniev3->SetBorderSize(0);
lnumu_injected_geniev3->SetTextFont(132);
lnumu_injected_geniev3->SetTextSize(0.025);
lnumu_injected_geniev3->AddEntry(m3, "Injected Signal: sin^{2}2#theta_{#mu#mu} = 0.07, #Delta m^{2} = 1.32 eV^{2}", "p");
lnumu_injected_geniev3->AddEntry(VALOR_numu_stat_injected_0pt07_1pt32, "SBN VALOR 5#sigma CL stat-only uncertainty","L");
lnumu_injected_geniev3->AddEntry(VALOR_numu_03d1_injected_0pt07_1pt32, "SBN VALOR 5#sigma CL w. flux + xsection uncertainty","L");
lnumu_injected_geniev3->Draw();

numu_injected->SaveAs("/sbnd/app/users/tham/VALOR_master/nue_2020/images/numu_injected.pdf");

// numu disapp CAF
TCanvas * numu_CAF = new TCanvas("numu_CAF","",20,20,900,900);
numu_CAF->Draw();

TH2F * hnumu_CAF = (TH2F*) numu_CAF->DrawFrame(1E-3,1E-2,1,1E+2);
hnumu_CAF->Draw();
numu_CAF->SetLogx();
numu_CAF->SetLogy();
hnumu_CAF->GetXaxis()->SetTitle("sin^{2}2#theta_{#mu#mu}");
hnumu_CAF->GetXaxis()->SetTitleSize(0.03);
hnumu_CAF->GetXaxis()->SetLabelSize(0.03);
hnumu_CAF->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnumu_CAF->GetYaxis()->SetTitleSize(0.03);
hnumu_CAF->GetYaxis()->SetLabelSize(0.03);

VALOR_numu_stat->SetLineColor(kRed+2);
VALOR_numu_stat->SetLineWidth(4);
VALOR_numu_stat->Draw("l");

VALOR_numu_sbnd_stat->SetLineColor(kRed+2);
VALOR_numu_sbnd_stat->SetLineWidth(4);
VALOR_numu_sbnd_stat->SetLineStyle(9);
//VALOR_numu_sbnd_stat->Draw("l");

VALOR_numu_icarus_stat->SetLineColor(kRed+2);
VALOR_numu_icarus_stat->SetLineWidth(4);
VALOR_numu_icarus_stat->SetLineStyle(7);
VALOR_numu_icarus_stat->Draw("l");



VALOR_numu_icarus_CAF_stat->SetLineColor(kBlack);
VALOR_numu_icarus_CAF_stat->SetLineWidth(4);
VALOR_numu_icarus_CAF_stat->SetLineStyle(7);
VALOR_numu_icarus_CAF_stat->Draw("l");

TLegend * lnumu_CAF = new TLegend(0.12,0.12,0.5,0.32);
lnumu_CAF->SetFillStyle(0);
lnumu_CAF->SetBorderSize(0);
lnumu_CAF->SetTextFont(132);
lnumu_CAF->SetTextSize(0.025);
lnumu_CAF->AddEntry(VALOR_numu_stat, "VALOR 5#sigma CL numu_disapp SBN stat-only Geniev3","L");
//lnumu_CAF->AddEntry(VALOR_numu_sbnd_stat, "VALOR Modern 5#sigma CL numu_disapp sbnd-only stat-only Geniev3","L");
lnumu_CAF->AddEntry(VALOR_numu_icarus_stat, "VALOR 5#sigma CL numu_disapp ICARUS-only stat-only Geniev3","L");
lnumu_CAF->AddEntry(VALOR_numu_icarus_CAF_stat, "VALOR 5#sigma CL numu_disapp CAF ICARUS-only stat-only Geniev3","L");
lnumu_CAF->Draw();



}
