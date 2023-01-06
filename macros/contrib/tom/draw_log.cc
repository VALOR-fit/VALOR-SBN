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

TFile*f_valor_numu_stat         = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_numu_disapp_stat.root","read");
TFile*f_valor_numu_03d1         = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_numu_disapp_03d1.root","read");
TFile*f_valor_numu_03d1_1pctEscale         = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_numu_03d1_1pctEscale.root","read");
TFile*f_valor_numu_03d1_5pctEscale         = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_numu_03d1_5pctEscale.root","read");

TFile*f_CAFAna_numu_syst        = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/CAFAna_numu_disapp_exclusion_2021.root","read");
TFile*f_SBNfit_numu_syst        = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/SBNfit_NumuDis_sensitivity.root","read");

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

TFile*f_valor_geniev3_stat                                     = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_stat.root","read");
TFile*f_valor_geniev3_splines_proposal_fixed_params            = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_spline_proposal_fixed_params.root","read");
//TFile*f_valor_geniev3_splines_proposal_fixed_params_matrix     = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_spline_proposal_fixed_matrix.root","read");
TFile*f_valor_geniev3_splines_proposal_fixed_params_matrix     = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_spline_new_proposal.root","read");
//TFile*f_valor_geniev3_splines                                  = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_spline_fixed_matrix.root","read");
TFile*f_valor_geniev3_splines                                  = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_spline_new.root","read");
TFile*f_valor_geniev3_splines_POT                             = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_03d1.root","read");
TFile*f_valor_geniev3_splines_oldjobsub                        = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_spline_oldjobsub.root","read");
TFile*f_valor_nue_app_03d1_1pctEscale                             = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_nue_03d1_1pctEscale.root","read");
TFile*f_valor_nue_app_03d1_5pctEscale                             = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_nue_03d1_5pctEscale.root","read");

TFile*f_valor_nue_app_stat_sbnd        = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_stat_sbnd.root","read");
TFile*f_valor_nue_app_stat_ub          = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_stat_ub.root","read");
TFile*f_valor_nue_app_stat_icarus      = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_stat_icarus.root","read");
TFile*f_valor_nue_app_stat_sbnd_ub     = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_stat_sbnd_ub.root","read");
TFile*f_valor_nue_app_stat_sbnd_icarus = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_stat_sbnd_icarus.root","read");
TFile*f_valor_nue_app_stat_ub_icarus   = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_stat_ub_icarus.root","read");
TFile*f_valor_nue_app_03d1_sbnd        = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_03d1_sbnd.root","read");
TFile*f_valor_nue_app_03d1_ub          = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_03d1_ub.root","read");
TFile*f_valor_nue_app_03d1_icarus      = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_03d1_icarus.root","read");
TFile*f_valor_nue_app_03d1_sbnd_ub     = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_03d1_sbnd_ub.root","read");
TFile*f_valor_nue_app_03d1_sbnd_icarus = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_03d1_sbnd_icarus.root","read");
TFile*f_valor_nue_app_03d1_ub_icarus   = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_03d1_ub_icarus.root","read");
TFile*f_valor_nue_app_03d1_flux        = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_03d1_flux.root","read");
TFile*f_valor_nue_app_03d1_proposal    = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_03d1_proposal.root","read");
TFile*f_valor_nue_app_03d1_modern      = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_03d1_modern.root","read");
TFile*f_valor_nue_app_03d1_proposal_modern = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_03d1_proposal_modern.root","read");
TFile*f_valor_nue_app_03d2             = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_app_03d2.root","read");
TFile*f_valor_nue_app_03d2_detector    = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/efficiency_systematics/nue_app/output_contours_as_graphs_det_only_2pct_corr_2pct_uncorr.root","read");
TFile*f_valor_nue_disapp_stat_sbnd        = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_stat_sbnd.root","read");
TFile*f_valor_nue_disapp_stat_ub          = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_stat_ub.root","read");
TFile*f_valor_nue_disapp_stat_icarus      = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_stat_icarus.root","read");
TFile*f_valor_nue_disapp_stat_sbnd_ub     = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_stat_sbnd_ub.root","read");
TFile*f_valor_nue_disapp_stat_sbnd_icarus = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_stat_sbnd_icarus.root","read");
TFile*f_valor_nue_disapp_stat_ub_icarus   = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_stat_ub_icarus.root","read");
TFile*f_valor_nue_disapp_03d1_sbnd        = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_03d1_sbnd.root","read");
TFile*f_valor_nue_disapp_03d1_ub          = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_03d1_ub.root","read");
TFile*f_valor_nue_disapp_03d1_icarus      = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_03d1_icarus.root","read");
TFile*f_valor_nue_disapp_03d1_sbnd_ub     = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_03d1_sbnd_ub.root","read");
TFile*f_valor_nue_disapp_03d1_sbnd_icarus = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_03d1_sbnd_icarus.root","read");
TFile*f_valor_nue_disapp_03d1_ub_icarus   = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_03d1_ub_icarus.root","read");
TFile*f_valor_nue_disapp_03d1_flux        = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_03d1_flux.root","read");
TFile*f_valor_nue_disapp_03d1_proposal    = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_03d1_proposal.root","read");
TFile*f_valor_nue_disapp_03d1_modern      = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_03d1_modern.root","read");
TFile*f_valor_nue_disapp_03d1_proposal_modern = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_03d1_proposal_modern.root","read");
TFile*f_valor_nue_disapp_03d2             = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_03d2.root","read");
TFile*f_valor_nue_disapp_03d2_detector    = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/efficiency_systematics/nue_disapp/output_contours_as_graphs_det_only_2pct_corr_2pct_uncorr.root","read");

//TFile*f_valor_nue_app_injected_stat         = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/allowed_regions/output_contours_as_graphs_nue_app_stat_dmsq_1.32_sinsq2th_0.003.root","read");
TFile*f_valor_nue_app_injected_stat         = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/allowed_regions/output_contours_as_graphs_nue_app_stat_injected.root","read");
TFile*f_valor_nue_app_injected_03d1         = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/allowed_regions/output_contours_as_graphs_nue_app_03d1_dmsq_1.32_sinsq2th_0.003.root","read");
                                              
TFile*f_valor_nue_disapp_geniev3_stat                          = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_stat.root","read");
//TFile*f_valor_nue_disapp_geniev3_stat                          = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs.root","read");
//TFile*f_valor_nue_disapp_geniev3_syst                          = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_nue_disapp_spline.root","read");
TFile*f_valor_nue_disapp_geniev3_syst                          = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/output_contours_as_graphs_nue_disapp_03d1.root","read");

TFile*f_valor_nue_disapp_injected_stat               = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/allowed_regions/output_contours_as_graphs_nue_disapp_stat_injected.root","read");
TFile*f_valor_nue_disapp_injected_03d1               = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/allowed_regions/output_contours_as_graphs_nue_disapp_03d1_dmsq_3_sinsq2th_0.4.root","read");

TFile*f_cafana_nue2020            = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/CAFAna_nue_app_exclusion_2021.root","read");
TFile*f_cafana_nue2020_injected            = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/CAFAna_nue_app_allowed.root","read");

TFile *f_sbnfit_nue_app_geniev2             = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/geniev2/SBNfit_NueApp_sensitivity_NoMCIntrinsicError.root","read");
TFile *f_sbnfit_nue_app_geniev3_updated     = new TFile("/sbnd/app/users/tham/VALOR_master/nue_2020/SBNfit_NueAppear_sensitivity_updated.root","read");
TFile *f_sbnfit_nue_app_geniev3_2021        = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/SBNfit_NueApp_sensitivity.root","read");

TFile *f_sbnfit_nue_disapp                  = new TFile("/sbnd/app/users/tham/VALOR_master/blessed_plots/exclusion_contours/SBNfit_NueDis_sensitivity.root","read");


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

TGraph *VALOR_nue_5s_geniev3_stat_sbnd              = (TGraph*) f_valor_nue_app_stat_sbnd->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_stat_ub                = (TGraph*) f_valor_nue_app_stat_ub->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_stat_icarus            = (TGraph*) f_valor_nue_app_stat_icarus->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_stat_sbnd_ub           = (TGraph*) f_valor_nue_app_stat_sbnd_ub->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_stat_sbnd_icarus       = (TGraph*) f_valor_nue_app_stat_sbnd_icarus->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_stat_ub_icarus         = (TGraph*) f_valor_nue_app_stat_ub_icarus->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_03d1_sbnd              = (TGraph*) f_valor_nue_app_03d1_sbnd->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_03d1_ub                = (TGraph*) f_valor_nue_app_03d1_ub->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_03d1_icarus            = (TGraph*) f_valor_nue_app_03d1_icarus->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_03d1_sbnd_ub           = (TGraph*) f_valor_nue_app_03d1_sbnd_ub->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_03d1_sbnd_icarus       = (TGraph*) f_valor_nue_app_03d1_sbnd_icarus->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_03d1_ub_icarus         = (TGraph*) f_valor_nue_app_03d1_ub_icarus->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_03d1_flux              = (TGraph*) f_valor_nue_app_03d1_flux->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_03d1_proposal          = (TGraph*) f_valor_nue_app_03d1_proposal->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_03d1_modern            = (TGraph*) f_valor_nue_app_03d1_modern->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_03d1_proposal_modern   = (TGraph*) f_valor_nue_app_03d1_proposal_modern->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_03d2                   = (TGraph*) f_valor_nue_app_03d2->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_5s_geniev3_03d2_detector          = (TGraph*) f_valor_nue_app_03d2_detector->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_stat_sbnd              = (TGraph*) f_valor_nue_disapp_stat_sbnd->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_stat_ub                = (TGraph*) f_valor_nue_disapp_stat_ub->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_stat_icarus            = (TGraph*) f_valor_nue_disapp_stat_icarus->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_stat_sbnd_ub           = (TGraph*) f_valor_nue_disapp_stat_sbnd_ub->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_stat_sbnd_icarus       = (TGraph*) f_valor_nue_disapp_stat_sbnd_icarus->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_stat_ub_icarus         = (TGraph*) f_valor_nue_disapp_stat_ub_icarus->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_03d1_sbnd              = (TGraph*) f_valor_nue_disapp_03d1_sbnd->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_03d1_ub                = (TGraph*) f_valor_nue_disapp_03d1_ub->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_03d1_icarus            = (TGraph*) f_valor_nue_disapp_03d1_icarus->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_03d1_sbnd_ub           = (TGraph*) f_valor_nue_disapp_03d1_sbnd_ub->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_03d1_sbnd_icarus       = (TGraph*) f_valor_nue_disapp_03d1_sbnd_icarus->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_03d1_ub_icarus         = (TGraph*) f_valor_nue_disapp_03d1_ub_icarus->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_03d1_flux              = (TGraph*) f_valor_nue_disapp_03d1_flux->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_03d1_proposal          = (TGraph*) f_valor_nue_disapp_03d1_proposal->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_03d1_modern            = (TGraph*) f_valor_nue_disapp_03d1_modern->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_03d1_proposal_modern   = (TGraph*) f_valor_nue_disapp_03d1_proposal_modern->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_03d2                   = (TGraph*) f_valor_nue_disapp_03d2->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_03d2_detector          = (TGraph*) f_valor_nue_disapp_03d2_detector->Get("contour_5sigma_lin_0");

TGraph *VALOR_nue_5s_injected_stat          = (TGraph*) f_valor_nue_app_injected_stat->Get("contour_5sigma_lin_1");
TGraph *VALOR_nue_5s_injected_03d1          = (TGraph*) f_valor_nue_app_injected_03d1->Get("contour_5sigma_lin_5");

TGraph *VALOR_nue_disapp_5s_geniev3_stat                       = (TGraph*) f_valor_nue_disapp_geniev3_stat->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_geniev3_03d1                     = (TGraph*) f_valor_nue_disapp_geniev3_syst->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_injected_stat            = (TGraph*) f_valor_nue_disapp_injected_stat->Get("contour_5sigma_lin_0");
TGraph *VALOR_nue_disapp_5s_injected_03d1            = (TGraph*) f_valor_nue_disapp_injected_03d1->Get("contour_5sigma_lin_2");

TGraph *CAFAna_nue_5s_2020                   = (TGraph*) f_cafana_nue2020->Get("all_stat_5sig");
TGraph *CAFAna_nue_5s_2020_syst                   = (TGraph*) f_cafana_nue2020->Get("all_syst_5sig");

TGraph *CAFAna_nue_5s_2020_injected                   = (TGraph*) f_cafana_nue2020_injected->Get("all_stat_5sig_10");
TGraph *CAFAna_nue_5s_2020_injected_syst                   = (TGraph*) f_cafana_nue2020_injected->Get("all_syst_5sig_1");

TGraph *SBNfit_nue_app_geniev2_5s_stat                   = (TGraph*) f_sbnfit_nue_app_geniev2->Get("STATONLY_5sigma");
TGraph *SBNfit_nue_app_geniev2_5s_syst                   = (TGraph*) f_sbnfit_nue_app_geniev2->Get("g5sigma");

TGraph *SBNfit_nue_app_geniev3_5s_stat                   = (TGraph*) f_sbnfit_nue_app_geniev3_2021->Get("STATONLY_5sigma");
TGraph *SBNfit_nue_app_geniev3_5s_syst_2021              = (TGraph*) f_sbnfit_nue_app_geniev3_2021->Get("g5sigma");
TGraph *SBNfit_nue_app_geniev3_5s_syst_updated           = (TGraph*) f_sbnfit_nue_app_geniev3_updated->Get("g5sigma");

TGraph *SBNfit_nue_disapp_5s_syst                        = (TGraph*) f_sbnfit_nue_disapp->Get("g5sigma");
TGraph *SBNfit_nue_disapp_5s_stat                        = (TGraph*) f_sbnfit_nue_disapp->Get("STATONLY_5sigma");

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

TGraph *lim_numudis_3p1_icecube_90pctCL   = (TGraph*) f_external_3p1_limits->Get("lim_numudis_3p1_icecube_90pctCL");
TGraph *lim_numudis_3p1_icecube_99pctCL   = (TGraph*) f_external_3p1_limits->Get("lim_numudis_3p1_icecube_99pctCL");

// nue app Geniev3
TCanvas * nue_geniev3 = new TCanvas("nue_geniev3","",20,20,900,900);
nue_geniev3->Draw();

TH2F * hnue_geniev3 = (TH2F*) nue_geniev3->DrawFrame(1E-4,1E-2,1,1E+2);
hnue_geniev3->Draw();
nue_geniev3->SetLogx();
nue_geniev3->SetLogy();
hnue_geniev3->GetXaxis()->SetTitle("sin^{2}2#theta_{#mue}");
hnue_geniev3->GetXaxis()->SetTitleSize(0.03);
hnue_geniev3->GetXaxis()->SetLabelSize(0.03);
hnue_geniev3->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnue_geniev3->GetYaxis()->SetTitleSize(0.03);
hnue_geniev3->GetYaxis()->SetLabelSize(0.03);
hnue_geniev3->GetYaxis()->SetTitleOffset(1.3);

VALOR_nue_5s_geniev3_stat->SetLineColor(kRed+2);
VALOR_nue_5s_geniev3_stat->SetLineWidth(4);
//VALOR_nue_5s_geniev3_stat->SetLineStyle(9);
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

VALOR_nue_5s_geniev3_03d2->SetLineColor(kMagenta);
VALOR_nue_5s_geniev3_03d2->SetLineWidth(4);
VALOR_nue_5s_geniev3_03d2->SetLineStyle(7);
//VALOR_nue_5s_geniev3_03d2->Draw("l");

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


TLegend * lnue_geniev3 = new TLegend(0.12,0.14,0.5,0.32);
lnue_geniev3->SetFillStyle(0);
lnue_geniev3->SetBorderSize(0);
lnue_geniev3->SetTextFont(132);
lnue_geniev3->SetTextSize(0.025);
lnue_geniev3->AddEntry(VALOR_nue_5s_geniev3_stat, "VALOR 5#sigma CL #nu_{e} app stat-only uncertainty ","L");
//lnue_geniev3->AddEntry(VALOR_nue_5s_2020_syst, "VALOR Modern 5#sigma CL syst Geniev3","L");
lnue_geniev3->AddEntry(VALOR_nue_5s_geniev3_POT, "VALOR 5#sigma CL #nu_{e} app stat+syst uncertainty ","L");
//lnue_geniev3->AddEntry(VALOR_nue_5s_geniev3_03d2, "5#sigma CL #nu_{e} app flux+interaction+detector uncertainty ","L");
//lnue_geniev3->AddEntry(VALOR_nue_5s_03d1_1pctEscale, "5#sigma CL #nu_{e} app stat + syst + 1%  Energy Scale","L");
lnue_geniev3->AddEntry(CAFAna_nue_5s_2020, "CAFAna 5#sigma CL #nu_{e} app stat-only uncertainty","L");
lnue_geniev3->AddEntry(CAFAna_nue_5s_2020_syst, "CAFAna 5#sigma CL #nu_{e} app stat+syst uncertainty","L");
lnue_geniev3->AddEntry(SBNfit_nue_app_geniev3_5s_stat, "SBNfit 5#sigma CL #nu_{e} app stat-only uncertainty","L");
lnue_geniev3->AddEntry(SBNfit_nue_app_geniev3_5s_syst_2021, "SBNfit 5#sigma CL #nu_{e} app stat+syst uncertainty","L");
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

VALOR_nue_disapp_5s_geniev3_stat->SetLineColor(kOrange+1);
VALOR_nue_disapp_5s_geniev3_stat->SetLineWidth(4);
//VALOR_nue_disapp_5s_geniev3_stat->SetLineStyle(9);
VALOR_nue_disapp_5s_geniev3_stat->Draw("l");

//VALOR_nue_disapp_5s_geniev3_03d1->SetLineColor(kRed+2);
VALOR_nue_disapp_5s_geniev3_03d1->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_03d1->Draw("l");

VALOR_nue_disapp_5s_geniev3_03d2->SetLineColor(kMagenta);
VALOR_nue_disapp_5s_geniev3_03d2->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_03d2->SetLineStyle(7);
//VALOR_nue_disapp_5s_geniev3_03d2->Draw("l");

SBNfit_nue_disapp_5s_stat->SetLineColor(kBlue);
SBNfit_nue_disapp_5s_stat->SetLineWidth(4);
SBNfit_nue_disapp_5s_stat->SetLineStyle(9);
SBNfit_nue_disapp_5s_stat->Draw("l");

SBNfit_nue_disapp_5s_syst->SetLineColor(kBlue);
SBNfit_nue_disapp_5s_syst->SetLineWidth(4);
SBNfit_nue_disapp_5s_syst->Draw("l");

TLegend * lnue_disapp_geniev3 = new TLegend(0.12,0.14,0.5,0.32);
lnue_disapp_geniev3->SetFillStyle(0);
lnue_disapp_geniev3->SetBorderSize(0);
lnue_disapp_geniev3->SetTextFont(132);
lnue_disapp_geniev3->SetTextSize(0.025);
lnue_disapp_geniev3->AddEntry(VALOR_nue_disapp_5s_geniev3_stat, "VALOR 5#sigma CL #nu_{e} disapp stat-only uncertainty","L");
lnue_disapp_geniev3->AddEntry(VALOR_nue_disapp_5s_geniev3_03d1, "VALOR 5#sigma CL #nu_{e} disapp flux+interaction uncertainty","L");
lnue_disapp_geniev3->AddEntry(SBNfit_nue_disapp_5s_stat, "SBNFit 5#sigma CL #nu_{e} disapp stat-only uncertainty","L");
lnue_disapp_geniev3->AddEntry(SBNfit_nue_disapp_5s_syst, "SBNFit 5#sigma CL #nu_{e} disapp flux+interaction uncertainty","L");
//lnue_disapp_geniev3->AddEntry(VALOR_nue_disapp_5s_geniev3_03d2, "5#sigma CL #nu_{e} disapp flux+interaction+detector uncertainty","L");
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
TCanvas * nue_injected = new TCanvas("nue_injected","",20,20,900,900);
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


VALOR_nue_5s_injected_03d1->SetLineColor(kRed+2);
VALOR_nue_5s_injected_03d1->SetFillColor(kRed+2);
VALOR_nue_5s_injected_03d1->SetFillStyle(3001);
VALOR_nue_5s_injected_03d1->SetLineWidth(4);
VALOR_nue_5s_injected_03d1->Draw("lf");

VALOR_nue_5s_injected_stat->SetLineColor(kOrange+1);
VALOR_nue_5s_injected_stat->SetFillColor(kOrange+1);
VALOR_nue_5s_injected_stat->SetFillStyle(3001);
VALOR_nue_5s_injected_stat->SetLineStyle(9);
VALOR_nue_5s_injected_stat->SetLineWidth(4);
VALOR_nue_5s_injected_stat->Draw("lf");

//injected point
TMarker *m = new TMarker(0.003, 1.32, 29);
m->SetMarkerSize(2);
m->Draw();



CAFAna_nue_5s_2020_injected->SetLineColor(kOrange);
CAFAna_nue_5s_2020_injected->SetLineStyle(9);
CAFAna_nue_5s_2020_injected->SetLineWidth(4);
//CAFAna_nue_5s_2020_injected->Draw("l");

CAFAna_nue_5s_2020_injected_syst->SetLineColor(kOrange);
CAFAna_nue_5s_2020_injected_syst->SetLineWidth(4);
//CAFAna_nue_5s_2020_injected_syst->Draw("l");

TLegend * lnue_injected = new TLegend(0.12,0.14,0.5,0.32);
lnue_injected->SetFillStyle(0);
lnue_injected->SetBorderSize(0);
lnue_injected->SetTextFont(132);
lnue_injected->SetTextSize(0.025);
lnue_injected->AddEntry(m, "Injected Signal: sin^{2}2#theta_{#mue} = 0.003, #Delta m^{2} = 1.32 eV^{2}", "p");
lnue_injected->AddEntry(VALOR_nue_5s_injected_stat, "5#sigma CL #nu_{e} app stat-only uncertainty","L");
lnue_injected->AddEntry(VALOR_nue_5s_injected_03d1, "5#sigma CL #nu_{e} app flux+interaction uncertainty","L");
//lnue_injected->AddEntry(CAFAna_nue_5s_2020_injected, "CAFAna Modern 5#sigma CL nue_app stat-only Geniev3","L");
//lnue_injected->AddEntry(CAFAna_nue_5s_2020_injected_syst, "CAFAna Modern 5#sigma CL nue_app stat+proposal_syst Geniev3","L");
lnue_injected->Draw();

// nue disapp Geniev3 injected
TCanvas * nue_disapp_injected = new TCanvas("nue_disapp_injected","",20,20,900,900);
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

VALOR_nue_disapp_5s_injected_03d1->SetLineColor(kRed+2);
VALOR_nue_disapp_5s_injected_03d1->SetFillColor(kRed+2);
VALOR_nue_disapp_5s_injected_03d1->SetFillStyle(3001);
VALOR_nue_disapp_5s_injected_03d1->SetLineWidth(4);
VALOR_nue_disapp_5s_injected_03d1->Draw("lf");

VALOR_nue_disapp_5s_injected_stat->SetLineColor(kOrange+1);
VALOR_nue_disapp_5s_injected_stat->SetFillColor(kOrange+1);
VALOR_nue_disapp_5s_injected_stat->SetFillStyle(3001);
VALOR_nue_disapp_5s_injected_stat->SetLineWidth(4);
VALOR_nue_disapp_5s_injected_stat->SetLineStyle(9);
VALOR_nue_disapp_5s_injected_stat->Draw("lf");

//injected point
TMarker *m2 = new TMarker(0.4, 3, 29);
m2->SetMarkerSize(2);
m2->Draw();

TLegend * lnuedisapp_injected = new TLegend(0.12,0.14,0.5,0.32);
lnuedisapp_injected->SetFillStyle(0);
lnuedisapp_injected->SetBorderSize(0);
lnuedisapp_injected->SetTextFont(132);
lnuedisapp_injected->SetTextSize(0.025);
lnuedisapp_injected->AddEntry(m2, "Injected Signal: sin^{2}2#theta_{ee} = 0.4, #Delta m^{2} = 3 eV^{2}", "p");
lnuedisapp_injected->AddEntry(VALOR_nue_disapp_5s_injected_stat, "5#sigma CL #nu_{e} disapp stat-only uncertainty","L");
lnuedisapp_injected->AddEntry(VALOR_nue_disapp_5s_injected_03d1, "5#sigma CL #nu_{e} disapp flux+interaction uncertainty","L");
lnuedisapp_injected->Draw();

// numu disapp Geniev3
TCanvas * numu_geniev3 = new TCanvas("numu_geniev3","",20,20,900,900);
numu_geniev3->Draw();

TH2F * hnumu_geniev3 = (TH2F*) numu_geniev3->DrawFrame(1E-3,1E-2,1,1E+2);
hnumu_geniev3->Draw();
numu_geniev3->SetLogx();
numu_geniev3->SetLogy();
hnumu_geniev3->GetXaxis()->SetTitle("sin^{2}2#theta_{#mu#mu}");
hnumu_geniev3->GetXaxis()->SetTitleSize(0.03);
hnumu_geniev3->GetXaxis()->SetLabelSize(0.03);
hnumu_geniev3->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnumu_geniev3->GetYaxis()->SetTitleSize(0.03);
hnumu_geniev3->GetYaxis()->SetLabelSize(0.03);
hnumu_geniev3->GetYaxis()->SetTitleOffset(1.3);

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
CAFAna_numu_stat->Draw("l");
CAFAna_numu_syst->SetLineColor(kOrange);
CAFAna_numu_syst->SetLineWidth(4);
//CAFAna_numu_syst->SetLineStyle(9);
CAFAna_numu_syst->Draw("l");

SBNfit_numu_stat->SetLineColor(kBlue);
SBNfit_numu_stat->SetLineWidth(4);
SBNfit_numu_stat->SetLineStyle(9);
SBNfit_numu_stat->Draw("l");
SBNfit_numu_syst->SetLineColor(kBlue);
SBNfit_numu_syst->SetLineWidth(4);
//SBNfit_numu_syst->SetLineStyle(9);
SBNfit_numu_syst->Draw("l");




//lim_numudis_3p1_minosp_90pctCL->Draw("l");
lim_numudis_3p1_minosp_90pctCL->SetLineColor(kGreen-7);
//lim_numudis_3p1_minisciboone_90pctCL->Draw("l");
lim_numudis_3p1_minisciboone_90pctCL->SetLineColor(kViolet+2);


TLegend * lnumu_geniev3 = new TLegend(0.12,0.14,0.5,0.32);
lnumu_geniev3->SetFillStyle(0);
lnumu_geniev3->SetBorderSize(0);
lnumu_geniev3->SetTextFont(132);
lnumu_geniev3->SetTextSize(0.025);
lnumu_geniev3->AddEntry(VALOR_numu_stat, "VALOR 5#sigma CL #nu_{#mu} disapp stat-only uncertainty","L");
lnumu_geniev3->AddEntry(VALOR_numu_03d1, "VALOR 5#sigma CL #nu_{#mu} disapp stat+syst uncertainty","L");
//lnumu_geniev3->AddEntry(VALOR_numu_03d1_1pctEscale, "5#sigma CL #nu_{#mu} disapp stat + syst + 1% Energy Scale","L");
lnumu_geniev3->AddEntry(CAFAna_numu_stat, "CAFAna 5#sigma CL #nu_{#mu} disapp stat-only uncertainty","L");
lnumu_geniev3->AddEntry(CAFAna_numu_syst, "CAFAna 5#sigma CL #nu_{#mu} disapp stat+syst uncertainty","L");
lnumu_geniev3->AddEntry(SBNfit_numu_stat, "SBNfit 5#sigma CL #nu_{#mu} disapp stat-only uncertainty","L");
lnumu_geniev3->AddEntry(SBNfit_numu_syst, "SBNfit 5#sigma CL #nu_{#mu} disapp stat+syst uncertainty","L");
//lnumu_geniev3->AddEntry(lim_numudis_3p1_minosp_90pctCL, "MINOS/MINOS+ 90% CL","L");
//lnumu_geniev3->AddEntry(lim_numudis_3p1_minisciboone_90pctCL, "MiniBooNE/SciBooNE 90% CL","L");
lnumu_geniev3->Draw();

numu_geniev3->SaveAs("/sbnd/app/users/tham/VALOR_master/nue_2020/images/numu_external.pdf");

// numu disapp Geniev3 injected
TCanvas * numu_injected = new TCanvas("numu_injected","",20,20,900,900);
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

VALOR_numu_stat_injected_0pt07_1pt32->SetLineColor(kOrange+1);
VALOR_numu_stat_injected_0pt07_1pt32->SetLineWidth(4);
VALOR_numu_stat_injected_0pt07_1pt32->SetLineStyle(9);
VALOR_numu_stat_injected_0pt07_1pt32->SetFillStyle(3001);
VALOR_numu_stat_injected_0pt07_1pt32->SetFillColor(kOrange+1);
VALOR_numu_stat_injected_0pt07_1pt32->Draw("l");

VALOR_numu_03d1_injected_0pt07_1pt32->SetLineColor(kRed+2);
VALOR_numu_03d1_injected_0pt07_1pt32->SetFillColor(kRed+2);
VALOR_numu_03d1_injected_0pt07_1pt32->SetFillStyle(3001);
VALOR_numu_03d1_injected_0pt07_1pt32->SetLineWidth(4);
VALOR_numu_03d1_injected_0pt07_1pt32->Draw("l");


TLegend * lnumu_injected_geniev3 = new TLegend(0.12,0.14,0.5,0.32);
lnumu_injected_geniev3->SetFillStyle(0);
lnumu_injected_geniev3->SetBorderSize(0);
lnumu_injected_geniev3->SetTextFont(132);
lnumu_injected_geniev3->SetTextSize(0.025);
lnumu_injected_geniev3->AddEntry(m3, "Injected Signal: sin^{2}2#theta_{#mu#mu} = 0.07, #Delta m^{2} = 1.32 eV^{2}", "p");
lnumu_injected_geniev3->AddEntry(VALOR_numu_stat_injected_0pt07_1pt32, "VALOR 5#sigma CL #nu_{#mu} disapp stat-only uncertainty","L");
lnumu_injected_geniev3->AddEntry(VALOR_numu_03d1_injected_0pt07_1pt32, "VALOR 5#sigma CL #nu_{#mu} disapp stat+syst uncertainty","L");
lnumu_injected_geniev3->Draw();

numu_injected->SaveAs("/sbnd/app/users/tham/VALOR_master/nue_2020/images/numu_injected.pdf");

// numu disapp overlays
TCanvas * numu_overlay = new TCanvas("numu_overlay","",20,20,900,900);
numu_overlay->Draw();

TH2F * hnumu_overlay = (TH2F*) numu_overlay->DrawFrame(1E-3,1E-2,1,1E2);
hnumu_overlay->Draw();
numu_overlay->SetLogx();
numu_overlay->SetLogy();
hnumu_overlay->GetXaxis()->SetTitle("sin^{2}2#theta_{#mu#mu}");
hnumu_overlay->GetXaxis()->SetTitleSize(0.03);
hnumu_overlay->GetXaxis()->SetLabelSize(0.03);
hnumu_overlay->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnumu_overlay->GetYaxis()->SetTitleSize(0.03);
hnumu_overlay->GetYaxis()->SetLabelSize(0.03);

lim_numudis_3p1_icecube_90pctCL->Draw("l");
lim_numudis_3p1_icecube_90pctCL->SetFillColor(kWhite);
lim_numudis_3p1_icecube_90pctCL->SetLineStyle(0);
lim_numudis_3p1_icecube_99pctCL->Draw("l");
lim_numudis_3p1_icecube_99pctCL->SetLineColor(kAzure-8);
lim_numudis_3p1_minosp_90pctCL->Draw("l");
lim_numudis_3p1_minosp_90pctCL->SetLineColor(kGreen-7);
lim_numudis_3p1_minisciboone_90pctCL->Draw("l");
lim_numudis_3p1_minisciboone_90pctCL->SetLineColor(kViolet+2);

VALOR_numu_stat->SetLineColor(kOrange+1);
VALOR_numu_stat->SetLineWidth(4);
VALOR_numu_stat->SetLineStyle(9);
VALOR_numu_stat->Draw("l");
VALOR_numu_03d1->SetLineColor(kRed+2);
VALOR_numu_03d1->SetLineWidth(4);
VALOR_numu_03d1->Draw("l");

VALOR_numu_03d1_injected_0pt07_1pt32->SetFillColor(kRed+2);
VALOR_numu_03d1_injected_0pt07_1pt32->SetLineColor(kRed+2);
VALOR_numu_03d1_injected_0pt07_1pt32->SetFillStyle(3001);
//VALOR_numu_03d1_injected_0pt07_1pt32->SetLineWidth(2);
VALOR_numu_03d1_injected_0pt07_1pt32->Draw("lf");

VALOR_numu_stat_injected_0pt07_1pt32->SetLineColor(kOrange+1);
VALOR_numu_stat_injected_0pt07_1pt32->SetFillStyle(3001);
VALOR_numu_stat_injected_0pt07_1pt32->SetFillColor(kOrange+1);
//VALOR_numu_stat_injected_0pt07_1pt32->SetLineWidth(2);
VALOR_numu_stat_injected_0pt07_1pt32->SetLineStyle(9);
VALOR_numu_stat_injected_0pt07_1pt32->Draw("lf");

//injected point
//TMarker *m3 = new TMarker(0.07, 1.32, 29);
//m3->SetMarkerSize(1);
m3->Draw();

TLegend * lnumu_overlay = new TLegend(0.12,0.14,0.5,0.32);
lnumu_overlay->SetFillStyle(0);
lnumu_overlay->SetBorderSize(0);
lnumu_overlay->SetTextFont(132);
lnumu_overlay->SetTextSize(0.02);
lnumu_overlay->AddEntry(lim_numudis_3p1_minosp_90pctCL, "MINOS/MINOS+ 90% CL","L");
lnumu_overlay->AddEntry(lim_numudis_3p1_minisciboone_90pctCL, "MiniBooNE/SciBooNE 90% CL","L");
lnumu_overlay->AddEntry(lim_numudis_3p1_icecube_90pctCL, "IceCube 90% CL","L");
lnumu_overlay->AddEntry(lim_numudis_3p1_icecube_99pctCL, "IceCube 99% CL","L");
lnumu_overlay->AddEntry((TObject*)0, "", "");
lnumu_overlay->AddEntry(m3, "Injected Signal: sin^{2}2#theta_{#mu#mu} = 0.07, #Delta m^{2} = 1.32 eV^{2}", "p");
lnumu_overlay->AddEntry(VALOR_numu_stat_injected_0pt07_1pt32, "SBN 5#sigma CL #nu_{#mu} disapp stat-only allowed region","F");
lnumu_overlay->AddEntry(VALOR_numu_03d1_injected_0pt07_1pt32, "SBN 5#sigma CL #nu_{#mu} disapp stat+syst allowed region","F");
lnumu_overlay->AddEntry(VALOR_numu_stat, "SBN 5#sigma CL #nu_{#mu} disapp stat-only exclusion contour","L");
lnumu_overlay->AddEntry(VALOR_numu_03d1, "SBN 5#sigma CL #nu_{#mu} disapp stat+syst exclusion contour","L");
lnumu_overlay->Draw();

// nue_app app overlays
TCanvas * nue_app_overlay = new TCanvas("nue_app_overlay","",20,20,900,900);
nue_app_overlay->Draw();

TH2F * hnue_app_overlay = (TH2F*) nue_app_overlay->DrawFrame(1E-4,1E-2,1,1E2);
hnue_app_overlay->Draw();
nue_app_overlay->SetLogx();
nue_app_overlay->SetLogy();
hnue_app_overlay->GetXaxis()->SetTitle("sin^{2}2#theta_{#mue}");
hnue_app_overlay->GetXaxis()->SetTitleSize(0.03);
hnue_app_overlay->GetXaxis()->SetLabelSize(0.03);
hnue_app_overlay->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnue_app_overlay->GetYaxis()->SetTitleSize(0.03);
hnue_app_overlay->GetYaxis()->SetLabelSize(0.03);

VALOR_nue_5s_geniev3_stat->SetLineColor(kOrange+1);
VALOR_nue_5s_geniev3_stat->SetLineWidth(4);
//VALOR_nue_5s_geniev3_stat->SetLineStyle(9);
VALOR_nue_5s_geniev3_stat->Draw("l");

VALOR_nue_5s_geniev3_POT->SetLineColor(kRed+2);
VALOR_nue_5s_geniev3_POT->SetLineWidth(4);
//VALOR_nue_5s_geniev3_POT->SetLineStyle(9);
//VALOR_nue_5s_geniev3_POT->Draw("l");

//lim_nueapp_3p1_lsndr1_99pctCL->Draw("l");
lim_nueapp_3p1_lsndr1_99pctCL->SetLineColor(kGreen-7);
lim_nueapp_3p1_lsndr1_99pctCL->SetFillColor(kGreen-7);
//lim_nueapp_3p1_lsndr2_99pctCL->Draw("l");
lim_nueapp_3p1_lsndr2_99pctCL->SetLineColor(kGreen-7);
lim_nueapp_3p1_lsndr2_99pctCL->SetFillColor(kGreen-7);
//lim_nueapp_3p1_lsndr3_99pctCL->Draw("l");
lim_nueapp_3p1_lsndr3_99pctCL->SetLineColor(kGreen-7);
lim_nueapp_3p1_lsndr3_99pctCL->SetFillColor(kGreen-7);
lim_nueapp_3p1_karmen_99pctCL->SetLineWidth(2);
lim_nueapp_3p1_karmen_99pctCL->SetLineColor(kViolet+2);
//lim_nueapp_3p1_karmen_99pctCL->Draw("l");

VALOR_nue_5s_injected_03d1->SetLineColor(kRed+2);
VALOR_nue_5s_injected_03d1->SetFillColor(kRed+2);
VALOR_nue_5s_injected_03d1->SetFillStyle(3001);
VALOR_nue_5s_injected_03d1->SetLineWidth(4);
//VALOR_nue_5s_injected_03d1->Draw("lf");

VALOR_nue_5s_injected_stat->SetLineColor(kOrange+1);
VALOR_nue_5s_injected_stat->SetFillColor(kOrange+1);
VALOR_nue_5s_injected_stat->SetFillStyle(3001);
VALOR_nue_5s_injected_stat->SetLineStyle(9);
VALOR_nue_5s_injected_stat->SetLineWidth(4);
VALOR_nue_5s_injected_stat->Draw("lf");

TMarker *m_b = new TMarker(0.001376656, 1, 41);
TMarker *m_c = new TMarker(0.000511058, 100, 41);
m_b->SetMarkerSize(2);
m_c->SetMarkerSize(2);

m_b->Draw();
m_c->Draw();
m->Draw();

//TLegend * lnue_app_overlay = new TLegend(0.12,0.15,0.5,0.32);
TLegend * lnue_app_overlay = new TLegend(0.12,0.13,0.5,0.38);
lnue_app_overlay->SetFillStyle(0);
lnue_app_overlay->SetBorderSize(0);
lnue_app_overlay->SetTextFont(132);
lnue_app_overlay->SetTextSize(0.02);
//lnue_app_overlay->AddEntry(lim_nueapp_3p1_lsndr1_99pctCL, "LSND 99% CL","F");
//lnue_app_overlay->AddEntry(lim_nueapp_3p1_karmen_99pctCL, "KARMEN 99% CL","L");
lnue_app_overlay->AddEntry((TObject*)0, "", "");
lnue_app_overlay->AddEntry(m, "Injected Signal: sin^{2}2#theta_{#mue} = 0.003, #Deltam^{2} = 1.32 eV^{2}", "p");
lnue_app_overlay->AddEntry(m_b, "Osc Point: #splitline{sin^{2}2#theta_{#mue} = 0.0014, #Deltam^{2} = 1 eV^{2}}{sin^{2}2#theta_{#mue} = 0.0005, #Deltam^{2} = 100 eV^{2}}" , "p");
lnue_app_overlay->AddEntry(VALOR_nue_5s_injected_stat, "SBN 5#sigma CL #nu_{e} app stat-only allowed region","F");
//lnue_app_overlay->AddEntry(VALOR_nue_5s_injected_03d1, "SBN 5#sigma CL #nu_{e} app stat+syst allowed region","F");
lnue_app_overlay->AddEntry(VALOR_nue_5s_geniev3_stat, "SBN 5#sigma CL #nu_{e} app stat-only exclusion contour","L");
//lnue_app_overlay->AddEntry(VALOR_nue_5s_geniev3_POT, "SBN 5#sigma CL #nu_{e} app stsat+syst exclusion contour","L");
lnue_app_overlay->Draw();


// nue_disapp disapp overlays
TCanvas * nue_disapp_overlay = new TCanvas("nue_disapp_overlay","",20,20,900,900);
nue_disapp_overlay->Draw();

TH2F * hnue_disapp_overlay = (TH2F*) nue_disapp_overlay->DrawFrame(1E-2,1E-2,1,1E2);
hnue_disapp_overlay->Draw();
nue_disapp_overlay->SetLogx();
nue_disapp_overlay->SetLogy();
hnue_disapp_overlay->GetXaxis()->SetTitle("sin^{2}2#theta_{ee}");
hnue_disapp_overlay->GetXaxis()->SetTitleSize(0.03);
hnue_disapp_overlay->GetXaxis()->SetLabelSize(0.03);
hnue_disapp_overlay->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnue_disapp_overlay->GetYaxis()->SetTitleSize(0.03);
hnue_disapp_overlay->GetYaxis()->SetLabelSize(0.03);

VALOR_nue_disapp_5s_geniev3_stat->SetLineColor(kOrange+1);
VALOR_nue_disapp_5s_geniev3_stat->SetLineWidth(4);
//VALOR_nue_disapp_5s_geniev3_stat->SetLineStyle(9);
VALOR_nue_disapp_5s_geniev3_stat->Draw("l");

VALOR_nue_disapp_5s_geniev3_03d1->SetLineColor(kRed+2);
VALOR_nue_disapp_5s_geniev3_03d1->SetLineWidth(4);
//VALOR_nue_disapp_5s_geniev3_03d1->Draw("l");

//lim_nuedis_3p1_t2knd280excluded_95pctCL->Draw("l");
lim_nuedis_3p1_t2knd280excluded_95pctCL->SetLineColor(kViolet+2);
//lim_nuedis_3p1_t2knd280allowed_90pctCL->Draw("l");
lim_nuedis_3p1_t2knd280allowed_90pctCL->SetLineColor(kGreen+3);
lim_nuedis_3p1_t2knd280allowed_90pctCL->SetFillColor(kGreen+3);
//lim_nuedis_3p1_t2knd280allowed_68pctCL->Draw("l");
lim_nuedis_3p1_t2knd280allowed_68pctCL->SetLineColor(kGreen-7);
lim_nuedis_3p1_t2knd280allowed_68pctCL->SetFillColor(kGreen-7);

VALOR_nue_disapp_5s_injected_03d1->SetLineColor(kRed+2);
VALOR_nue_disapp_5s_injected_03d1->SetFillColor(kRed+2);
VALOR_nue_disapp_5s_injected_03d1->SetFillStyle(3001);
VALOR_nue_disapp_5s_injected_03d1->SetLineWidth(4);
//VALOR_nue_disapp_5s_injected_03d1->Draw("lf");

VALOR_nue_disapp_5s_injected_stat->SetLineColor(kOrange+1);
VALOR_nue_disapp_5s_injected_stat->SetFillColor(kOrange+1);
VALOR_nue_disapp_5s_injected_stat->SetLineWidth(4);
VALOR_nue_disapp_5s_injected_stat->SetLineStyle(9);
VALOR_nue_disapp_5s_injected_stat->SetFillStyle(3001);
VALOR_nue_disapp_5s_injected_stat->Draw("lf");

TMarker *m_b2 = new TMarker(0.29099199, 1, 41);
TMarker *m_c2 = new TMarker(0.0849134, 100, 41);
m_b2->SetMarkerSize(2);
m_c2->SetMarkerSize(2);

m_b2->Draw();
m_c2->Draw();
m2->Draw();

//TLegend * lnue_disapp_overlay = new TLegend(0.12,0.14,0.5,0.32);
TLegend * lnue_disapp_overlay = new TLegend(0.12,0.13,0.5,0.38);
lnue_disapp_overlay->SetFillStyle(0);
lnue_disapp_overlay->SetBorderSize(0);
lnue_disapp_overlay->SetTextFont(132);
lnue_disapp_overlay->SetTextSize(0.022);
//lnue_disapp_overlay->AddEntry(lim_nuedis_3p1_t2knd280excluded_95pctCL, "T2K/ND280 exclusion 95% CL","L");
//lnue_disapp_overlay->AddEntry(lim_nuedis_3p1_t2knd280allowed_90pctCL, "T2K/ND280 allowed 90% CL","F");
//lnue_disapp_overlay->AddEntry(lim_nuedis_3p1_t2knd280allowed_68pctCL, "T2K/ND280 allowed 68% CL","F");
lnue_disapp_overlay->AddEntry((TObject*)0, "", "");
lnue_disapp_overlay->AddEntry(m2, "Injected Signal: sin^{2}2#theta_{ee} = 0.4, #Deltam^{2} = 3 eV^{2}", "p");
lnue_disapp_overlay->AddEntry(m_b2, "Osc Point: #splitline{sin^{2}2#theta_{ee} = 0.290, #Deltam^{2} = 1 eV^{2}}{sin^{2}2#theta_{ee} = 0.085, #Deltam^{2} = 100 eV^{2}}" , "p");
lnue_disapp_overlay->AddEntry(VALOR_nue_disapp_5s_injected_stat, "SBN 5#sigma CL #nu_{e} disapp stat-only allowed region","F");
//lnue_disapp_overlay->AddEntry(VALOR_nue_disapp_5s_injected_03d1, "SBN 5#sigma CL #nu_{e} disapp stat+syst allowed region","F");
lnue_disapp_overlay->AddEntry(VALOR_nue_disapp_5s_geniev3_stat, "SBN 5#sigma CL #nu_{e} disapp stat-only exclusion contour","L");
//lnue_disapp_overlay->AddEntry(VALOR_nue_disapp_5s_geniev3_03d1, "SBN 5#sigma CL #nu_{e} disapp stat+syst exclusion contour","L");
lnue_disapp_overlay->Draw();


// nue_app detector combos
TCanvas * nue_app_detector_combos = new TCanvas("nue_app_detector_combos","",20,20,900,900);
nue_app_detector_combos->Draw();

TH2F * hnue_app_detector_combos = (TH2F*) nue_app_detector_combos->DrawFrame(1E-4,1E-2,1,1E2);
hnue_app_detector_combos->Draw();
nue_app_detector_combos->SetLogx();
nue_app_detector_combos->SetLogy();
hnue_app_detector_combos->GetXaxis()->SetTitle("sin^{2}2#theta_{#mue}");
hnue_app_detector_combos->GetXaxis()->SetTitleSize(0.03);
hnue_app_detector_combos->GetXaxis()->SetLabelSize(0.03);
hnue_app_detector_combos->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnue_app_detector_combos->GetYaxis()->SetTitleSize(0.03);
hnue_app_detector_combos->GetYaxis()->SetLabelSize(0.03);

//VALOR_nue_5s_geniev3_stat->SetLineColor(kBlack);
VALOR_nue_5s_geniev3_stat->SetLineWidth(4);
VALOR_nue_5s_geniev3_stat->Draw("l");

VALOR_nue_5s_geniev3_stat_sbnd->SetLineColor(kAzure+1);
VALOR_nue_5s_geniev3_stat_sbnd->SetLineWidth(4);
VALOR_nue_5s_geniev3_stat_sbnd->Draw("l");

VALOR_nue_5s_geniev3_stat_ub->SetLineColor(kOrange+1);
VALOR_nue_5s_geniev3_stat_ub->SetLineWidth(4);
VALOR_nue_5s_geniev3_stat_ub->Draw("l");

VALOR_nue_5s_geniev3_stat_icarus->SetLineColor(kGreen+1);
VALOR_nue_5s_geniev3_stat_icarus->SetLineWidth(4);
VALOR_nue_5s_geniev3_stat_icarus->Draw("l");

VALOR_nue_5s_geniev3_stat_sbnd_ub->SetLineColor(kMagenta);
VALOR_nue_5s_geniev3_stat_sbnd_ub->SetLineWidth(4);
VALOR_nue_5s_geniev3_stat_sbnd_ub->SetLineStyle(9);
VALOR_nue_5s_geniev3_stat_sbnd_ub->Draw("l");

VALOR_nue_5s_geniev3_stat_sbnd_icarus->SetLineColor(kRed+1);
VALOR_nue_5s_geniev3_stat_sbnd_icarus->SetLineWidth(4);
VALOR_nue_5s_geniev3_stat_sbnd_icarus->SetLineStyle(9);
VALOR_nue_5s_geniev3_stat_sbnd_icarus->Draw("l");

VALOR_nue_5s_geniev3_stat_ub_icarus->SetLineColor(kCyan+1);
VALOR_nue_5s_geniev3_stat_ub_icarus->SetLineWidth(4);
VALOR_nue_5s_geniev3_stat_ub_icarus->SetLineStyle(9);
VALOR_nue_5s_geniev3_stat_ub_icarus->Draw("l");

TLegend * lnue_app_detector_combo = new TLegend(0.12,0.14,0.5,0.32);
lnue_app_detector_combo->SetFillStyle(0);
lnue_app_detector_combo->SetBorderSize(0);
lnue_app_detector_combo->SetTextFont(132);
lnue_app_detector_combo->SetTextSize(0.025);
lnue_app_detector_combo->AddEntry(VALOR_nue_5s_geniev3_stat, "SBN 5#sigma CL #nu_{e} app stat-only","L");
lnue_app_detector_combo->AddEntry(VALOR_nue_5s_geniev3_stat_sbnd, "SBND 5#sigma CL #nu_{e} app stat-only","L");
lnue_app_detector_combo->AddEntry(VALOR_nue_5s_geniev3_stat_ub, "#muBooNE 5#sigma CL #nu_{e} app stat-only","L");
lnue_app_detector_combo->AddEntry(VALOR_nue_5s_geniev3_stat_icarus, "ICARUS 5#sigma CL #nu_{e} app stat-only","L");
lnue_app_detector_combo->AddEntry(VALOR_nue_5s_geniev3_stat_sbnd_ub, "SBND + #muBooNE 5#sigma CL #nu_{e} app stat-only","L");
lnue_app_detector_combo->AddEntry(VALOR_nue_5s_geniev3_stat_sbnd_icarus, "SBND + ICARUS 5#sigma CL #nu_{e} app stat-only","L");
lnue_app_detector_combo->AddEntry(VALOR_nue_5s_geniev3_stat_ub_icarus, "#muBooNE + ICARUS 5#sigma CL #nu_{e} app stat-only","L");
lnue_app_detector_combo->Draw();

// nue_app detector combos syst
TCanvas * nue_app_detector_combos_syst = new TCanvas("nue_app_detector_combos_syst","",20,20,900,900);
nue_app_detector_combos_syst->Draw();

TH2F * hnue_app_detector_combos_syst = (TH2F*) nue_app_detector_combos_syst->DrawFrame(1E-4,1E-2,1,1E2);
hnue_app_detector_combos_syst->Draw();
nue_app_detector_combos_syst->SetLogx();
nue_app_detector_combos_syst->SetLogy();
hnue_app_detector_combos_syst->GetXaxis()->SetTitle("sin^{2}2#theta_{#mue}");
hnue_app_detector_combos_syst->GetXaxis()->SetTitleSize(0.03);
hnue_app_detector_combos_syst->GetXaxis()->SetLabelSize(0.03);
hnue_app_detector_combos_syst->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnue_app_detector_combos_syst->GetYaxis()->SetTitleSize(0.03);
hnue_app_detector_combos_syst->GetYaxis()->SetLabelSize(0.03);

//VALOR_nue_5s_geniev3_stat->SetLineColor(kBlack);
VALOR_nue_5s_geniev3_stat->SetLineWidth(4);
//VALOR_nue_5s_geniev3_stat->SetLineStyle(9);
VALOR_nue_5s_geniev3_stat->Draw("l");

//VALOR_nue_5s_geniev3_POT->SetLineColor(kBlack);
VALOR_nue_5s_geniev3_POT->SetLineWidth(4);
VALOR_nue_5s_geniev3_POT->Draw("l");

VALOR_nue_5s_geniev3_03d1_sbnd->SetLineColor(kAzure+1);
VALOR_nue_5s_geniev3_03d1_sbnd->SetLineWidth(4);
VALOR_nue_5s_geniev3_03d1_sbnd->Draw("l");

VALOR_nue_5s_geniev3_03d1_ub->SetLineColor(kOrange+1);
VALOR_nue_5s_geniev3_03d1_ub->SetLineWidth(4);
VALOR_nue_5s_geniev3_03d1_ub->Draw("l");

VALOR_nue_5s_geniev3_03d1_icarus->SetLineColor(kGreen+1);
VALOR_nue_5s_geniev3_03d1_icarus->SetLineWidth(4);
VALOR_nue_5s_geniev3_03d1_icarus->Draw("l");

VALOR_nue_5s_geniev3_03d1_sbnd_ub->SetLineColor(kMagenta);
VALOR_nue_5s_geniev3_03d1_sbnd_ub->SetLineWidth(4);
VALOR_nue_5s_geniev3_03d1_sbnd_ub->SetLineStyle(9);
VALOR_nue_5s_geniev3_03d1_sbnd_ub->Draw("l");

VALOR_nue_5s_geniev3_03d1_sbnd_icarus->SetLineColor(kRed+1);
VALOR_nue_5s_geniev3_03d1_sbnd_icarus->SetLineWidth(4);
VALOR_nue_5s_geniev3_03d1_sbnd_icarus->SetLineStyle(9);
VALOR_nue_5s_geniev3_03d1_sbnd_icarus->Draw("l");

VALOR_nue_5s_geniev3_03d1_ub_icarus->SetLineColor(kCyan+1);
VALOR_nue_5s_geniev3_03d1_ub_icarus->SetLineWidth(4);
VALOR_nue_5s_geniev3_03d1_ub_icarus->SetLineStyle(9);
VALOR_nue_5s_geniev3_03d1_ub_icarus->Draw("l");

TLegend * lnue_app_detector_combo_syst = new TLegend(0.12,0.14,0.5,0.32);
lnue_app_detector_combo_syst->SetFillStyle(0);
lnue_app_detector_combo_syst->SetBorderSize(0);
lnue_app_detector_combo_syst->SetTextFont(132);
lnue_app_detector_combo_syst->SetTextSize(0.02);
lnue_app_detector_combo_syst->AddEntry(VALOR_nue_5s_geniev3_stat, "SBN 5#sigma CL #nu_{e} app stat-only","L");
lnue_app_detector_combo_syst->AddEntry(VALOR_nue_5s_geniev3_POT,  "SBN 5#sigma CL #nu_{e} app stat+syst","L");
lnue_app_detector_combo_syst->AddEntry(VALOR_nue_5s_geniev3_stat_sbnd, "SBND 5#sigma CL #nu_{e} app stat+syst","L");
lnue_app_detector_combo_syst->AddEntry(VALOR_nue_5s_geniev3_stat_ub, "#muBooNE 5#sigma CL #nu_{e} app stat+syst","L");
lnue_app_detector_combo_syst->AddEntry(VALOR_nue_5s_geniev3_stat_icarus, "ICARUS 5#sigma CL #nu_{e} app stat+syst","L");
lnue_app_detector_combo_syst->AddEntry(VALOR_nue_5s_geniev3_stat_sbnd_ub, "SBND + #muBooNE 5#sigma CL #nu_{e} app stat+syst","L");
lnue_app_detector_combo_syst->AddEntry(VALOR_nue_5s_geniev3_stat_sbnd_icarus, "SBND + ICARUS 5#sigma CL #nu_{e} app stat+syst","L");
lnue_app_detector_combo_syst->AddEntry(VALOR_nue_5s_geniev3_stat_ub_icarus, "#muBooNE + ICARUS 5#sigma CL #nu_{e} app stat+syst","L");
lnue_app_detector_combo_syst->Draw();


// nue_app syst group
TCanvas * nue_app_syst_groups = new TCanvas("nue_app_syst_groups","",20,20,900,900);
nue_app_syst_groups->Draw();

TH2F * hnue_app_syst_groups = (TH2F*) nue_app_syst_groups->DrawFrame(1E-4,1E-2,1,1E2);
hnue_app_syst_groups->Draw();
nue_app_syst_groups->SetLogx();
nue_app_syst_groups->SetLogy();
hnue_app_syst_groups->GetXaxis()->SetTitle("sin^{2}2#theta_{#mue}");
hnue_app_syst_groups->GetXaxis()->SetTitleSize(0.03);
hnue_app_syst_groups->GetXaxis()->SetLabelSize(0.03);
hnue_app_syst_groups->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnue_app_syst_groups->GetYaxis()->SetTitleSize(0.03);
hnue_app_syst_groups->GetYaxis()->SetLabelSize(0.03);

//VALOR_nue_5s_geniev3_stat->SetLineColor(kBlack);
VALOR_nue_5s_geniev3_stat->SetLineWidth(4);
//VALOR_nue_5s_geniev3_stat->SetLineStyle(0);
VALOR_nue_5s_geniev3_stat->Draw("l");

VALOR_nue_5s_geniev3_03d1_flux->SetLineColor(kRed+1);
VALOR_nue_5s_geniev3_03d1_flux->SetLineWidth(4);
VALOR_nue_5s_geniev3_03d1_flux->Draw("l");

VALOR_nue_5s_geniev3_03d1_proposal->SetLineColor(kAzure+1);
VALOR_nue_5s_geniev3_03d1_proposal->SetLineWidth(4);
VALOR_nue_5s_geniev3_03d1_proposal->Draw("l");

VALOR_nue_5s_geniev3_03d1_modern->SetLineColor(kOrange+1);
VALOR_nue_5s_geniev3_03d1_modern->SetLineWidth(4);
VALOR_nue_5s_geniev3_03d1_modern->Draw("l");

VALOR_nue_5s_geniev3_03d1_proposal_modern->SetLineColor(kGreen+1);
VALOR_nue_5s_geniev3_03d1_proposal_modern->SetLineWidth(4);
VALOR_nue_5s_geniev3_03d1_proposal_modern->Draw("l");

VALOR_nue_5s_geniev3_03d2_detector->SetLineColor(kMagenta);
VALOR_nue_5s_geniev3_03d2_detector->SetLineWidth(4);
VALOR_nue_5s_geniev3_03d2_detector->Draw("l");

TLegend * lnue_app_syst_group = new TLegend(0.12,0.14,0.5,0.32);
lnue_app_syst_group->SetFillStyle(0);
lnue_app_syst_group->SetBorderSize(0);
lnue_app_syst_group->SetTextFont(132);
lnue_app_syst_group->SetTextSize(0.02);
lnue_app_syst_group->AddEntry(VALOR_nue_5s_geniev3_stat, "SBN 5#sigma CL #nu_{e} app stat-only","L");
lnue_app_syst_group->AddEntry(VALOR_nue_5s_geniev3_03d1_flux, "SBN 5#sigma CL #nu_{e} app flux syst","L");
lnue_app_syst_group->AddEntry(VALOR_nue_5s_geniev3_03d1_proposal, "SBN 5#sigma CL #nu_{e} app proposal interaction syst","L");
lnue_app_syst_group->AddEntry(VALOR_nue_5s_geniev3_03d1_modern, "SBN 5#sigma CL #nu_{e} app modern interaction syst","L");
lnue_app_syst_group->AddEntry(VALOR_nue_5s_geniev3_03d1_proposal_modern, "SBN 5#sigma CL #nu_{e} app proposal + modern interaction syst","L");
lnue_app_syst_group->AddEntry(VALOR_nue_5s_geniev3_03d2_detector, "SBN 5#sigma CL #nu_{e} app efficiency(2% corr + 2% uncorr) syst","L");
lnue_app_syst_group->Draw();


// nue_disapp syst group
TCanvas * nue_disapp_syst_groups = new TCanvas("nue_disapp_syst_groups","",20,20,900,900);
nue_disapp_syst_groups->Draw();

TH2F * hnue_disapp_syst_groups = (TH2F*) nue_disapp_syst_groups->DrawFrame(1E-2,1E-2,1,1E2);
hnue_disapp_syst_groups->Draw();
nue_disapp_syst_groups->SetLogx();
nue_disapp_syst_groups->SetLogy();
hnue_disapp_syst_groups->GetXaxis()->SetTitle("sin^{2}2#theta_{ee}");
hnue_disapp_syst_groups->GetXaxis()->SetTitleSize(0.03);
hnue_disapp_syst_groups->GetXaxis()->SetLabelSize(0.03);
hnue_disapp_syst_groups->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnue_disapp_syst_groups->GetYaxis()->SetTitleSize(0.03);
hnue_disapp_syst_groups->GetYaxis()->SetLabelSize(0.03);

//VALOR_nue_disapp_5s_geniev3_stat->SetLineColor(kBlack);
VALOR_nue_disapp_5s_geniev3_stat->SetLineWidth(4);
//VALOR_nue_disapp_5s_geniev3_stat->SetLineStyle(9);
VALOR_nue_disapp_5s_geniev3_stat->Draw("l");

VALOR_nue_disapp_5s_geniev3_03d1_flux->SetLineColor(kRed+1);
VALOR_nue_disapp_5s_geniev3_03d1_flux->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_03d1_flux->Draw("l");

VALOR_nue_disapp_5s_geniev3_03d1_proposal->SetLineColor(kAzure+1);
VALOR_nue_disapp_5s_geniev3_03d1_proposal->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_03d1_proposal->Draw("l");

VALOR_nue_disapp_5s_geniev3_03d1_modern->SetLineColor(kOrange+1);
VALOR_nue_disapp_5s_geniev3_03d1_modern->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_03d1_modern->Draw("l");

VALOR_nue_disapp_5s_geniev3_03d1_proposal_modern->SetLineColor(kGreen+1);
VALOR_nue_disapp_5s_geniev3_03d1_proposal_modern->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_03d1_proposal_modern->Draw("l");

VALOR_nue_disapp_5s_geniev3_03d2_detector->SetLineColor(kMagenta);
VALOR_nue_disapp_5s_geniev3_03d2_detector->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_03d2_detector->Draw("l");

TLegend * lnue_disapp_syst_group = new TLegend(0.12,0.14,0.5,0.32);
lnue_disapp_syst_group->SetFillStyle(0);
lnue_disapp_syst_group->SetBorderSize(0);
lnue_disapp_syst_group->SetTextFont(132);
lnue_disapp_syst_group->SetTextSize(0.02);
lnue_disapp_syst_group->AddEntry(VALOR_nue_disapp_5s_geniev3_stat, "SBN 5#sigma CL #nu_{e} disapp stat-only","L");
lnue_disapp_syst_group->AddEntry(VALOR_nue_disapp_5s_geniev3_03d1_flux, "SBN 5#sigma CL #nu_{e} disapp flux syst","L");
lnue_disapp_syst_group->AddEntry(VALOR_nue_disapp_5s_geniev3_03d1_proposal, "SBN 5#sigma CL #nu_{e} disapp proposal interaction syst","L");
lnue_disapp_syst_group->AddEntry(VALOR_nue_disapp_5s_geniev3_03d1_modern, "SBN 5#sigma CL #nu_{e} disapp modern interaction syst","L");
lnue_disapp_syst_group->AddEntry(VALOR_nue_disapp_5s_geniev3_03d1_proposal_modern, "SBN 5#sigma CL #nu_{e} disapp proposal + modern interaction syst","L");
lnue_disapp_syst_group->AddEntry(VALOR_nue_disapp_5s_geniev3_03d2_detector, "SBN 5#sigma CL #nu_{e} disapp efficiency(2% corr + 2% uncorr) syst","L");
lnue_disapp_syst_group->Draw();


// nue_disapp detector combos stat
TCanvas * nue_disapp_detector_combos = new TCanvas("nue_disapp_detector_combos","",20,20,900,900);
nue_disapp_detector_combos->Draw();

TH2F * hnue_disapp_detector_combos = (TH2F*) nue_disapp_detector_combos->DrawFrame(1E-2,1E-2,1,1E2);
hnue_disapp_detector_combos->Draw();
nue_disapp_detector_combos->SetLogx();
nue_disapp_detector_combos->SetLogy();
hnue_disapp_detector_combos->GetXaxis()->SetTitle("sin^{2}2#theta_{ee}");
hnue_disapp_detector_combos->GetXaxis()->SetTitleSize(0.03);
hnue_disapp_detector_combos->GetXaxis()->SetLabelSize(0.03);
hnue_disapp_detector_combos->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnue_disapp_detector_combos->GetYaxis()->SetTitleSize(0.03);
hnue_disapp_detector_combos->GetYaxis()->SetLabelSize(0.03);

//VALOR_nue_disapp_5s_geniev3_stat->SetLineColor(kBlack);
VALOR_nue_disapp_5s_geniev3_stat->SetLineWidth(4);
//VALOR_nue_disapp_5s_geniev3_stat->SetLineStyle(2);
VALOR_nue_disapp_5s_geniev3_stat->Draw("l");

//VALOR_nue_disapp_5s_geniev3_stat->SetLineColor(kBlack);
VALOR_nue_disapp_5s_geniev3_stat->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_stat->Draw("l");

VALOR_nue_disapp_5s_geniev3_stat_sbnd->SetLineColor(kAzure+1);
VALOR_nue_disapp_5s_geniev3_stat_sbnd->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_stat_sbnd->Draw("l");

VALOR_nue_disapp_5s_geniev3_stat_ub->SetLineColor(kOrange+1);
VALOR_nue_disapp_5s_geniev3_stat_ub->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_stat_ub->Draw("l");

VALOR_nue_disapp_5s_geniev3_stat_icarus->SetLineColor(kGreen+1);
VALOR_nue_disapp_5s_geniev3_stat_icarus->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_stat_icarus->Draw("l");

VALOR_nue_disapp_5s_geniev3_stat_sbnd_ub->SetLineColor(kMagenta);
VALOR_nue_disapp_5s_geniev3_stat_sbnd_ub->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_stat_sbnd_ub->SetLineStyle(9);
VALOR_nue_disapp_5s_geniev3_stat_sbnd_ub->Draw("l");

VALOR_nue_disapp_5s_geniev3_stat_sbnd_icarus->SetLineColor(kRed+1);
VALOR_nue_disapp_5s_geniev3_stat_sbnd_icarus->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_stat_sbnd_icarus->SetLineStyle(9);
VALOR_nue_disapp_5s_geniev3_stat_sbnd_icarus->Draw("l");

VALOR_nue_disapp_5s_geniev3_stat_ub_icarus->SetLineColor(kCyan+1);
VALOR_nue_disapp_5s_geniev3_stat_ub_icarus->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_stat_ub_icarus->SetLineStyle(9);
VALOR_nue_disapp_5s_geniev3_stat_ub_icarus->Draw("l");

TLegend * lnue_disapp_detector_combo = new TLegend(0.12,0.14,0.5,0.32);
lnue_disapp_detector_combo->SetFillStyle(0);
lnue_disapp_detector_combo->SetBorderSize(0);
lnue_disapp_detector_combo->SetTextFont(132);
lnue_disapp_detector_combo->SetTextSize(0.02);
lnue_disapp_detector_combo->AddEntry(VALOR_nue_disapp_5s_geniev3_stat, "SBN 5#sigma CL #nu_{e} disapp stat-only","L");
lnue_disapp_detector_combo->AddEntry(VALOR_nue_disapp_5s_geniev3_stat_sbnd, "SBND 5#sigma CL #nu_{e} disapp stat-only","L");
lnue_disapp_detector_combo->AddEntry(VALOR_nue_disapp_5s_geniev3_stat_ub, "#muBooNE 5#sigma CL #nu_{e} disapp stat-only","L");
lnue_disapp_detector_combo->AddEntry(VALOR_nue_disapp_5s_geniev3_stat_icarus, "ICARUS 5#sigma CL #nu_{e} disapp stat-only","L");
lnue_disapp_detector_combo->AddEntry(VALOR_nue_disapp_5s_geniev3_stat_sbnd_ub, "SBND + #muBooNE 5#sigma CL #nu_{e} disapp stat-only","L");
lnue_disapp_detector_combo->AddEntry(VALOR_nue_disapp_5s_geniev3_stat_sbnd_icarus, "SBND + ICARUS 5#sigma CL #nu_{e} disapp stat-only","L");
lnue_disapp_detector_combo->AddEntry(VALOR_nue_disapp_5s_geniev3_stat_ub_icarus, "#muBooNE + ICARUS 5#sigma CL #nu_{e} disapp stat-only","L");
lnue_disapp_detector_combo->Draw();

// nue_disapp detector combos syst
TCanvas * nue_disapp_detector_combos_syst = new TCanvas("nue_disapp_detector_combos_syst","",20,20,900,900);
nue_disapp_detector_combos_syst->Draw();

TH2F * hnue_disapp_detector_combos_syst = (TH2F*) nue_disapp_detector_combos_syst->DrawFrame(1E-2,1E-2,1,1E2);
hnue_disapp_detector_combos_syst->Draw();
nue_disapp_detector_combos_syst->SetLogx();
nue_disapp_detector_combos_syst->SetLogy();
hnue_disapp_detector_combos_syst->GetXaxis()->SetTitle("sin^{2}2#theta_{ee}");
hnue_disapp_detector_combos_syst->GetXaxis()->SetTitleSize(0.03);
hnue_disapp_detector_combos_syst->GetXaxis()->SetLabelSize(0.03);
hnue_disapp_detector_combos_syst->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hnue_disapp_detector_combos_syst->GetYaxis()->SetTitleSize(0.03);
hnue_disapp_detector_combos_syst->GetYaxis()->SetLabelSize(0.03);

//VALOR_nue_disapp_5s_geniev3_stat->SetLineColor(kBlack);
VALOR_nue_disapp_5s_geniev3_stat->SetLineWidth(4);
//VALOR_nue_disapp_5s_geniev3_stat->SetLineStyle(2);
VALOR_nue_disapp_5s_geniev3_stat->Draw("l");

//VALOR_nue_disapp_5s_geniev3_03d1->SetLineColor(kBlack);
VALOR_nue_disapp_5s_geniev3_03d1->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_03d1->Draw("l");

VALOR_nue_disapp_5s_geniev3_03d1_sbnd->SetLineColor(kAzure+1);
VALOR_nue_disapp_5s_geniev3_03d1_sbnd->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_03d1_sbnd->Draw("l");

VALOR_nue_disapp_5s_geniev3_03d1_ub->SetLineColor(kOrange+1);
VALOR_nue_disapp_5s_geniev3_03d1_ub->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_03d1_ub->Draw("l");

VALOR_nue_disapp_5s_geniev3_03d1_icarus->SetLineColor(kGreen+1);
VALOR_nue_disapp_5s_geniev3_03d1_icarus->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_03d1_icarus->Draw("l");

VALOR_nue_disapp_5s_geniev3_03d1_sbnd_ub->SetLineColor(kMagenta);
VALOR_nue_disapp_5s_geniev3_03d1_sbnd_ub->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_03d1_sbnd_ub->SetLineStyle(9);
VALOR_nue_disapp_5s_geniev3_03d1_sbnd_ub->Draw("l");

VALOR_nue_disapp_5s_geniev3_03d1_sbnd_icarus->SetLineColor(kRed+1);
VALOR_nue_disapp_5s_geniev3_03d1_sbnd_icarus->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_03d1_sbnd_icarus->SetLineStyle(9);
VALOR_nue_disapp_5s_geniev3_03d1_sbnd_icarus->Draw("l");

VALOR_nue_disapp_5s_geniev3_03d1_ub_icarus->SetLineColor(kCyan+1);
VALOR_nue_disapp_5s_geniev3_03d1_ub_icarus->SetLineWidth(4);
VALOR_nue_disapp_5s_geniev3_03d1_ub_icarus->SetLineStyle(9);
VALOR_nue_disapp_5s_geniev3_03d1_ub_icarus->Draw("l");

TLegend * lnue_disapp_detector_combo_syst = new TLegend(0.12,0.14,0.5,0.32);
lnue_disapp_detector_combo_syst->SetFillStyle(0);
lnue_disapp_detector_combo_syst->SetBorderSize(0);
lnue_disapp_detector_combo_syst->SetTextFont(132);
lnue_disapp_detector_combo_syst->SetTextSize(0.025);
lnue_disapp_detector_combo_syst->AddEntry(VALOR_nue_disapp_5s_geniev3_stat, "SBN 5#sigma CL #nu_{e} disapp stat-only","L");
lnue_disapp_detector_combo_syst->AddEntry(VALOR_nue_disapp_5s_geniev3_03d1, "SBN 5#sigma CL #nu_{e} disapp stat+syst","L");
lnue_disapp_detector_combo_syst->AddEntry(VALOR_nue_disapp_5s_geniev3_03d1_sbnd, "SBND 5#sigma CL #nu_{e} disapp stat+syst","L");
lnue_disapp_detector_combo_syst->AddEntry(VALOR_nue_disapp_5s_geniev3_03d1_ub, "#muBooNE 5#sigma CL #nu_{e} disapp stat+syst","L");
lnue_disapp_detector_combo_syst->AddEntry(VALOR_nue_disapp_5s_geniev3_03d1_icarus, "ICARUS 5#sigma CL #nu_{e} disapp stat+syst","L");
lnue_disapp_detector_combo_syst->AddEntry(VALOR_nue_disapp_5s_geniev3_03d1_sbnd_ub, "SBND + #muBooNE 5#sigma CL #nu_{e} disapp stat+syst","L");
lnue_disapp_detector_combo_syst->AddEntry(VALOR_nue_disapp_5s_geniev3_03d1_sbnd_icarus, "SBND + ICARUS 5#sigma CL #nu_{e} disapp stat+syst","L");
lnue_disapp_detector_combo_syst->AddEntry(VALOR_nue_disapp_5s_geniev3_03d1_ub_icarus, "#muBooNE + ICARUS 5#sigma CL #nu_{e} disapp stat+syst","L");
lnue_disapp_detector_combo_syst->Draw();



/*
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
*/


}
