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
void fitter_spectral_ratios() {

  TFile *f_val       = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-SBN/pdfs/sbn/raw_files/VALOR_dmsq_1e2_sinsq2thmumu_2e-3_hists.root","read");
  TFile *f_sbn_osc   = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-SBN/pdfs/sbn/raw_files/SBNfit_sinsq_2e-3_dmsq_1e2.SBNspec.root","read");
  TFile *f_sbn_unosc = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-SBN/pdfs/sbn/raw_files/SBNfit_CV.SBNspec.root","read");
  TFile *f_caf       = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-SBN/pdfs/sbn/raw_files/CAFAna_dmsq_1e2_ss2thmm_2e-3.root","read");

  // Get the relevant histograms
  // VALOR
  TH1D *val_sbnd_osc     = static_cast<TH1D*>(f_val->Get("sbn_nd_oscillated"));
  TH1D *val_sbnd_unosc   = static_cast<TH1D*>(f_val->Get("sbn_nd_integrated"));
  TH1D *val_uboone_osc   = static_cast<TH1D*>(f_val->Get("sbn_uboone_oscillated"));
  TH1D *val_uboone_unosc = static_cast<TH1D*>(f_val->Get("sbn_uboone_integrated"));
  TH1D *val_icarus_osc   = static_cast<TH1D*>(f_val->Get("sbn_icarus_oscillated"));
  TH1D *val_icarus_unosc = static_cast<TH1D*>(f_val->Get("sbn_icarus_integrated"));

  // CAFAna
  TH1D *caf_sbnd_osc     = static_cast<TH1D*>(f_caf->Get("nd_total_osc"));
  TH1D *caf_sbnd_unosc   = static_cast<TH1D*>(f_caf->Get("nd_total_unosc"));
  TH1D *caf_uboone_osc   = static_cast<TH1D*>(f_caf->Get("ub_total_osc"));
  TH1D *caf_uboone_unosc = static_cast<TH1D*>(f_caf->Get("ub_total_unosc"));
  TH1D *caf_icarus_osc   = static_cast<TH1D*>(f_caf->Get("fd_total_osc"));
  TH1D *caf_icarus_unosc = static_cast<TH1D*>(f_caf->Get("fd_total_unosc"));

  // SBNFit osc
  TH1D *sbn_sbnd_cc_osc    = static_cast<TH1D*>(f_sbn_osc->Get("nu_SBND_numu_cc"));
  TH1D *sbn_sbnd_nc_osc    = static_cast<TH1D*>(f_sbn_osc->Get("nu_SBND_numu_nc"));
  TH1D *sbn_sbnd_nue_osc   = static_cast<TH1D*>(f_sbn_osc->Get("nu_SBND_numu_nue"));
  TH1D *sbn_uboone_cc_osc  = static_cast<TH1D*>(f_sbn_osc->Get("nu_uBooNE_numu_cc"));
  TH1D *sbn_uboone_nc_osc  = static_cast<TH1D*>(f_sbn_osc->Get("nu_uBooNE_numu_nc"));
  TH1D *sbn_uboone_nue_osc = static_cast<TH1D*>(f_sbn_osc->Get("nu_uBooNE_numu_nue"));
  TH1D *sbn_icarus_cc_osc  = static_cast<TH1D*>(f_sbn_osc->Get("nu_ICARUS_numu_cc"));
  TH1D *sbn_icarus_nc_osc  = static_cast<TH1D*>(f_sbn_osc->Get("nu_ICARUS_numu_nc"));
  TH1D *sbn_icarus_nue_osc = static_cast<TH1D*>(f_sbn_osc->Get("nu_ICARUS_numu_nue"));

  // SBNFit unosc
  TH1D *sbn_sbnd_cc_unosc    = static_cast<TH1D*>(f_sbn_unosc->Get("nu_SBND_numu_cc"));
  TH1D *sbn_sbnd_nc_unosc    = static_cast<TH1D*>(f_sbn_unosc->Get("nu_SBND_numu_nc"));
  TH1D *sbn_sbnd_nue_unosc   = static_cast<TH1D*>(f_sbn_unosc->Get("nu_SBND_numu_nue"));
  TH1D *sbn_uboone_cc_unosc  = static_cast<TH1D*>(f_sbn_unosc->Get("nu_uBooNE_numu_cc"));
  TH1D *sbn_uboone_nc_unosc  = static_cast<TH1D*>(f_sbn_unosc->Get("nu_uBooNE_numu_nc"));
  TH1D *sbn_uboone_nue_unosc = static_cast<TH1D*>(f_sbn_unosc->Get("nu_uBooNE_numu_nue"));
  TH1D *sbn_icarus_cc_unosc  = static_cast<TH1D*>(f_sbn_unosc->Get("nu_ICARUS_numu_cc"));
  TH1D *sbn_icarus_nc_unosc  = static_cast<TH1D*>(f_sbn_unosc->Get("nu_ICARUS_numu_nc"));
  TH1D *sbn_icarus_nue_unosc = static_cast<TH1D*>(f_sbn_unosc->Get("nu_ICARUS_numu_nue"));
  
  // Now get the totals
  TH1D *sbn_sbnd_osc_noscale     = static_cast<TH1D*>(sbn_sbnd_cc_osc->Clone("nu_SBND_numu_osc"));
  TH1D *sbn_uboone_osc_noscale   = static_cast<TH1D*>(sbn_uboone_cc_osc->Clone("nu_uBooNE_numu_osc"));
  TH1D *sbn_icarus_osc_noscale   = static_cast<TH1D*>(sbn_icarus_cc_osc->Clone("nu_ICARUS_numu_osc"));
  TH1D *sbn_sbnd_unosc_noscale   = static_cast<TH1D*>(sbn_sbnd_cc_unosc->Clone("nu_SBND_numu_unosc"));
  TH1D *sbn_uboone_unosc_noscale = static_cast<TH1D*>(sbn_uboone_cc_unosc->Clone("nu_uBooNE_numu_unosc"));
  TH1D *sbn_icarus_unosc_noscale = static_cast<TH1D*>(sbn_icarus_cc_unosc->Clone("nu_ICARUS_numu_unosc"));

  sbn_sbnd_osc_noscale->Add(sbn_sbnd_nc_osc);
  sbn_uboone_osc_noscale->Add(sbn_uboone_nc_osc);
  sbn_icarus_osc_noscale->Add(sbn_icarus_nc_osc);
  sbn_sbnd_unosc_noscale->Add(sbn_sbnd_nc_unosc);
  sbn_uboone_unosc_noscale->Add(sbn_uboone_nc_unosc);
  sbn_icarus_unosc_noscale->Add(sbn_icarus_nc_unosc);

  sbn_sbnd_osc_noscale->Add(sbn_sbnd_nue_osc);
  sbn_uboone_osc_noscale->Add(sbn_uboone_nue_osc);
  sbn_icarus_osc_noscale->Add(sbn_icarus_nue_osc);
  sbn_sbnd_unosc_noscale->Add(sbn_sbnd_nue_unosc);
  sbn_uboone_unosc_noscale->Add(sbn_uboone_nue_unosc);
  sbn_icarus_unosc_noscale->Add(sbn_icarus_nue_unosc);

  // Scale the SBNFit hist by width
  TH1D * sbn_sbnd_osc     = new TH1D(*sbn_sbnd_osc_noscale);
  TH1D * sbn_uboone_osc   = new TH1D(*sbn_uboone_osc_noscale);
  TH1D * sbn_icarus_osc   = new TH1D(*sbn_icarus_osc_noscale);
  TH1D * sbn_sbnd_unosc   = new TH1D(*sbn_sbnd_unosc_noscale);
  TH1D * sbn_uboone_unosc = new TH1D(*sbn_uboone_unosc_noscale);
  TH1D * sbn_icarus_unosc = new TH1D(*sbn_icarus_unosc_noscale);
  
  // Get a vector of each fitter's histograms
  std::vector<TH1D*> sbnfit = {sbn_sbnd_osc, sbn_uboone_osc, sbn_icarus_osc, sbn_sbnd_unosc, sbn_uboone_unosc, sbn_icarus_unosc};
  std::vector<TH1D*> cafana = {caf_sbnd_osc, caf_uboone_osc, caf_icarus_osc, caf_sbnd_unosc, caf_uboone_unosc, caf_icarus_unosc};
  std::vector<TH1D*> valor  = {val_sbnd_osc, val_uboone_osc, val_icarus_osc, val_sbnd_unosc, val_uboone_unosc, val_icarus_unosc};

  for(TH1D* hist : sbnfit){
    for (int ibin = 1 ; ibin <= hist->GetXaxis()->GetNbins(); ibin++) {
      double old_bin_content = hist->GetBinContent(ibin);
      double bin_width       = hist->GetXaxis()->GetBinWidth(ibin);
      double new_bin_content = old_bin_content / bin_width;
      hist->SetBinContent(ibin,new_bin_content);
    }
  }

  // Now get the ratios
  // 
  // UNOSCILLATED
  //
  // VALOR/CAFAna unoscillated
  TH1D *val_caf_sbnd_unosc   = static_cast<TH1D*>(val_sbnd_unosc  ->Clone("val_caf_sbnd_unosc  "));
  TH1D *val_caf_uboone_unosc = static_cast<TH1D*>(val_uboone_unosc->Clone("val_caf_uboone_unosc"));
  TH1D *val_caf_icarus_unosc = static_cast<TH1D*>(val_icarus_unosc->Clone("val_caf_icarus_unosc"));
  
  val_caf_sbnd_unosc  ->Divide(caf_sbnd_unosc  );
  val_caf_uboone_unosc->Divide(caf_uboone_unosc);
  val_caf_icarus_unosc->Divide(caf_icarus_unosc);

  // Then, SBNFit/CAFAna unoscillated
  TH1D *sbn_caf_sbnd_unosc   = static_cast<TH1D*>(sbn_sbnd_unosc  ->Clone("sbn_caf_sbnd_unosc  "));
  TH1D *sbn_caf_uboone_unosc = static_cast<TH1D*>(sbn_uboone_unosc->Clone("sbn_caf_uboone_unosc"));
  TH1D *sbn_caf_icarus_unosc = static_cast<TH1D*>(sbn_icarus_unosc->Clone("sbn_caf_icarus_unosc"));
  
  sbn_caf_sbnd_unosc  ->Divide(caf_sbnd_unosc  );
  sbn_caf_uboone_unosc->Divide(caf_uboone_unosc);
  sbn_caf_icarus_unosc->Divide(caf_icarus_unosc);

  // Then, SBNFit/valor unoscillated
  TH1D *sbn_val_sbnd_unosc   = static_cast<TH1D*>(sbn_sbnd_unosc  ->Clone("sbn_val_sbnd_unosc  "));
  TH1D *sbn_val_uboone_unosc = static_cast<TH1D*>(sbn_uboone_unosc->Clone("sbn_val_uboone_unosc"));
  TH1D *sbn_val_icarus_unosc = static_cast<TH1D*>(sbn_icarus_unosc->Clone("sbn_val_icarus_unosc"));
  
  sbn_val_sbnd_unosc  ->Divide(val_sbnd_unosc  );
  sbn_val_uboone_unosc->Divide(val_uboone_unosc);
  sbn_val_icarus_unosc->Divide(val_icarus_unosc);

  // 
  // OSCILLATED
  //
  // VALOR/CAFAna oscillated
  TH1D *val_caf_sbnd_osc   = static_cast<TH1D*>(val_sbnd_osc  ->Clone("val_caf_sbnd_osc  "));
  TH1D *val_caf_uboone_osc = static_cast<TH1D*>(val_uboone_osc->Clone("val_caf_uboone_osc"));
  TH1D *val_caf_icarus_osc = static_cast<TH1D*>(val_icarus_osc->Clone("val_caf_icarus_osc"));
  
  val_caf_sbnd_osc  ->Divide(caf_sbnd_osc  );
  val_caf_uboone_osc->Divide(caf_uboone_osc);
  val_caf_icarus_osc->Divide(caf_icarus_osc);

  // Then, SBNFit/CAFAna oscillated
  TH1D *sbn_caf_sbnd_osc   = static_cast<TH1D*>(sbn_sbnd_osc  ->Clone("sbn_caf_sbnd_osc  "));
  TH1D *sbn_caf_uboone_osc = static_cast<TH1D*>(sbn_uboone_osc->Clone("sbn_caf_uboone_osc"));
  TH1D *sbn_caf_icarus_osc = static_cast<TH1D*>(sbn_icarus_osc->Clone("sbn_caf_icarus_osc"));
  
  sbn_caf_sbnd_osc  ->Divide(caf_sbnd_osc  );
  sbn_caf_uboone_osc->Divide(caf_uboone_osc);
  sbn_caf_icarus_osc->Divide(caf_icarus_osc);

  // Then, SBNFit/valor oscillated
  TH1D *sbn_val_sbnd_osc   = static_cast<TH1D*>(sbn_sbnd_osc  ->Clone("sbn_val_sbnd_osc  "));
  TH1D *sbn_val_uboone_osc = static_cast<TH1D*>(sbn_uboone_osc->Clone("sbn_val_uboone_osc"));
  TH1D *sbn_val_icarus_osc = static_cast<TH1D*>(sbn_icarus_osc->Clone("sbn_val_icarus_osc"));
  
  sbn_val_sbnd_osc  ->Divide(val_sbnd_osc  );
  sbn_val_uboone_osc->Divide(val_uboone_osc);
  sbn_val_icarus_osc->Divide(val_icarus_osc);

  // 
  // OSCILLATED/UNOSCILLATED
  //
  // Then, VALOR oscillated/unoscillated
  TH1D *val_osc_unosc_sbnd   = static_cast<TH1D*>(val_sbnd_osc  ->Clone("val_osc_unosc_sbnd  "));
  TH1D *val_osc_unosc_uboone = static_cast<TH1D*>(val_uboone_osc->Clone("val_osc_unosc_uboone"));
  TH1D *val_osc_unosc_icarus = static_cast<TH1D*>(val_icarus_osc->Clone("val_osc_unosc_icarus"));
  
  val_osc_unosc_sbnd  ->Divide(val_sbnd_unosc  );
  val_osc_unosc_uboone->Divide(val_uboone_unosc);
  val_osc_unosc_icarus->Divide(val_icarus_unosc);

  // Then, CAFAna oscillated/unoscillated
  TH1D *caf_osc_unosc_sbnd   = static_cast<TH1D*>(caf_sbnd_osc  ->Clone("caf_osc_unosc_sbnd  "));
  TH1D *caf_osc_unosc_uboone = static_cast<TH1D*>(caf_uboone_osc->Clone("caf_osc_unosc_uboone"));
  TH1D *caf_osc_unosc_icarus = static_cast<TH1D*>(caf_icarus_osc->Clone("caf_osc_unosc_icarus"));
  
  caf_osc_unosc_sbnd  ->Divide(caf_sbnd_unosc  );
  caf_osc_unosc_uboone->Divide(caf_uboone_unosc);
  caf_osc_unosc_icarus->Divide(caf_icarus_unosc);

  // Then, SBNFit oscillated/unoscillated
  TH1D *sbn_osc_unosc_sbnd   = static_cast<TH1D*>(sbn_sbnd_osc  ->Clone("sbn_osc_unosc_sbnd  "));
  TH1D *sbn_osc_unosc_uboone = static_cast<TH1D*>(sbn_uboone_osc->Clone("sbn_osc_unosc_uboone"));
  TH1D *sbn_osc_unosc_icarus = static_cast<TH1D*>(sbn_icarus_osc->Clone("sbn_osc_unosc_icarus"));
  
  sbn_osc_unosc_sbnd  ->Divide(sbn_sbnd_unosc  );
  sbn_osc_unosc_uboone->Divide(sbn_uboone_unosc);
  sbn_osc_unosc_icarus->Divide(sbn_icarus_unosc);

  //
  // OSCILLATED/UNOSCILLATED DOUBLE RATIOS
  //
  // (VALOR oscillated/unoscillated) / (CAFAna oscillated/unoscillated)
  TH1D *val_caf_osc_unosc_sbnd   = static_cast<TH1D*>(val_osc_unosc_sbnd  ->Clone("val_caf_osc_unosc_sbnd  "));
  TH1D *val_caf_osc_unosc_uboone = static_cast<TH1D*>(val_osc_unosc_uboone->Clone("val_caf_osc_unosc_uboone"));
  TH1D *val_caf_osc_unosc_icarus = static_cast<TH1D*>(val_osc_unosc_icarus->Clone("val_caf_osc_unosc_icarus"));
  
  val_caf_osc_unosc_sbnd  ->Divide(caf_osc_unosc_sbnd  );
  val_caf_osc_unosc_uboone->Divide(caf_osc_unosc_uboone);
  val_caf_osc_unosc_icarus->Divide(caf_osc_unosc_icarus);

  // (SBNFit oscillated/unoscillated) / (CAFAna oscillated/unoscillated)
  TH1D *sbn_caf_osc_unosc_sbnd   = static_cast<TH1D*>(sbn_osc_unosc_sbnd  ->Clone("sbn_caf_osc_unosc_sbnd  "));
  TH1D *sbn_caf_osc_unosc_uboone = static_cast<TH1D*>(sbn_osc_unosc_uboone->Clone("sbn_caf_osc_unosc_uboone"));
  TH1D *sbn_caf_osc_unosc_icarus = static_cast<TH1D*>(sbn_osc_unosc_icarus->Clone("sbn_caf_osc_unosc_icarus"));
  
  sbn_caf_osc_unosc_sbnd  ->Divide(caf_osc_unosc_sbnd  );
  sbn_caf_osc_unosc_uboone->Divide(caf_osc_unosc_uboone);
  sbn_caf_osc_unosc_icarus->Divide(caf_osc_unosc_icarus);

  // (SBNFit oscillated/unoscillated) / (VALOR oscillated/unoscillated)
  TH1D *sbn_val_osc_unosc_sbnd   = static_cast<TH1D*>(sbn_osc_unosc_sbnd  ->Clone("sbn_val_osc_unosc_sbnd  "));
  TH1D *sbn_val_osc_unosc_uboone = static_cast<TH1D*>(sbn_osc_unosc_uboone->Clone("sbn_val_osc_unosc_uboone"));
  TH1D *sbn_val_osc_unosc_icarus = static_cast<TH1D*>(sbn_osc_unosc_icarus->Clone("sbn_val_osc_unosc_icarus"));
  
  sbn_val_osc_unosc_sbnd  ->Divide(val_osc_unosc_sbnd  );
  sbn_val_osc_unosc_uboone->Divide(val_osc_unosc_uboone);
  sbn_val_osc_unosc_icarus->Divide(val_osc_unosc_icarus);

  //
  // OSCILLATED RATE DIFFERENCES
  //
  // VALOR difference for the denominator
  TH1D *val_diff_sbnd   = static_cast<TH1D*>(val_sbnd_unosc  ->Clone("val_diff_sbnd  "));
  TH1D *val_diff_uboone = static_cast<TH1D*>(val_uboone_unosc->Clone("val_diff_uboone"));
  TH1D *val_diff_icarus = static_cast<TH1D*>(val_icarus_unosc->Clone("val_diff_icarus"));

  val_diff_sbnd  ->Add(val_sbnd_osc,  -1);
  val_diff_uboone->Add(val_uboone_osc,-1);
  val_diff_icarus->Add(val_icarus_osc,-1);

  // SBNFit  difference for the denominator
  TH1D *sbn_diff_sbnd   = static_cast<TH1D*>(sbn_sbnd_unosc  ->Clone("sbn_diff_sbnd  "));
  TH1D *sbn_diff_uboone = static_cast<TH1D*>(sbn_uboone_unosc->Clone("sbn_diff_uboone"));
  TH1D *sbn_diff_icarus = static_cast<TH1D*>(sbn_icarus_unosc->Clone("sbn_diff_icarus"));

  sbn_diff_sbnd  ->Add(sbn_sbnd_osc,  -1);
  sbn_diff_uboone->Add(sbn_uboone_osc,-1);
  sbn_diff_icarus->Add(sbn_icarus_osc,-1);

  // CAFAna difference for the denominator
  TH1D *caf_diff_sbnd   = static_cast<TH1D*>(caf_sbnd_unosc  ->Clone("caf_diff_sbnd  "));
  TH1D *caf_diff_uboone = static_cast<TH1D*>(caf_uboone_unosc->Clone("caf_diff_uboone"));
  TH1D *caf_diff_icarus = static_cast<TH1D*>(caf_icarus_unosc->Clone("caf_diff_icarus"));

  caf_diff_sbnd  ->Add(caf_sbnd_osc,  -1);
  caf_diff_uboone->Add(caf_uboone_osc,-1);
  caf_diff_icarus->Add(caf_icarus_osc,-1);

  // VALOR-CAFAna difference
  TH1D *val_caf_diff_sbnd_osc   = static_cast<TH1D*>(val_sbnd_osc  ->Clone("val_caf_diff_sbnd_osc  "));
  TH1D *val_caf_diff_uboone_osc = static_cast<TH1D*>(val_uboone_osc->Clone("val_caf_diff_uboone_osc"));
  TH1D *val_caf_diff_icarus_osc = static_cast<TH1D*>(val_icarus_osc->Clone("val_caf_diff_icarus_osc"));
  
  val_caf_diff_sbnd_osc  ->Add(caf_sbnd_osc,   -1);
  val_caf_diff_uboone_osc->Add(caf_uboone_osc, -1);
  val_caf_diff_icarus_osc->Add(caf_icarus_osc, -1);

  TH1D *val_caf_diff_sbnd   = static_cast<TH1D*>(val_caf_diff_sbnd_osc  ->Clone("val_caf_diff_sbnd  "));
  TH1D *val_caf_diff_uboone = static_cast<TH1D*>(val_caf_diff_uboone_osc->Clone("val_caf_diff_uboone"));
  TH1D *val_caf_diff_icarus = static_cast<TH1D*>(val_caf_diff_icarus_osc->Clone("val_caf_diff_icarus"));

  val_caf_diff_sbnd  ->Divide(val_diff_sbnd);
  val_caf_diff_uboone->Divide(val_diff_uboone);
  val_caf_diff_icarus->Divide(val_diff_icarus);

  // VALOR-SBNFit difference
  TH1D *val_sbn_diff_sbnd_osc   = static_cast<TH1D*>(val_sbnd_osc  ->Clone("val_sbn_diff_sbnd_osc  "));
  TH1D *val_sbn_diff_uboone_osc = static_cast<TH1D*>(val_uboone_osc->Clone("val_sbn_diff_uboone_osc"));
  TH1D *val_sbn_diff_icarus_osc = static_cast<TH1D*>(val_icarus_osc->Clone("val_sbn_diff_icarus_osc"));
  
  val_sbn_diff_sbnd_osc  ->Add(sbn_sbnd_osc,   -1);
  val_sbn_diff_uboone_osc->Add(sbn_uboone_osc, -1);
  val_sbn_diff_icarus_osc->Add(sbn_icarus_osc, -1);

  TH1D *val_sbn_diff_sbnd   = static_cast<TH1D*>(val_sbn_diff_sbnd_osc  ->Clone("val_sbn_diff_sbnd  "));
  TH1D *val_sbn_diff_uboone = static_cast<TH1D*>(val_sbn_diff_uboone_osc->Clone("val_sbn_diff_uboone"));
  TH1D *val_sbn_diff_icarus = static_cast<TH1D*>(val_sbn_diff_icarus_osc->Clone("val_sbn_diff_icarus"));

  val_sbn_diff_sbnd  ->Divide(val_diff_sbnd);
  val_sbn_diff_uboone->Divide(val_diff_uboone);
  val_sbn_diff_icarus->Divide(val_diff_icarus);

  // SBNFit-CAFAna difference
  TH1D *sbn_caf_diff_sbnd_osc   = static_cast<TH1D*>(sbn_sbnd_osc  ->Clone("sbn_caf_diff_sbnd_osc  "));
  TH1D *sbn_caf_diff_uboone_osc = static_cast<TH1D*>(sbn_uboone_osc->Clone("sbn_caf_diff_uboone_osc"));
  TH1D *sbn_caf_diff_icarus_osc = static_cast<TH1D*>(sbn_icarus_osc->Clone("sbn_caf_diff_icarus_osc"));
  
  sbn_caf_diff_sbnd_osc  ->Add(caf_sbnd_osc,   -1);
  sbn_caf_diff_uboone_osc->Add(caf_uboone_osc, -1);
  sbn_caf_diff_icarus_osc->Add(caf_icarus_osc, -1);

  TH1D *sbn_caf_diff_sbnd   = static_cast<TH1D*>(sbn_caf_diff_sbnd_osc  ->Clone("sbn_caf_diff_sbnd  "));
  TH1D *sbn_caf_diff_uboone = static_cast<TH1D*>(sbn_caf_diff_uboone_osc->Clone("sbn_caf_diff_uboone"));
  TH1D *sbn_caf_diff_icarus = static_cast<TH1D*>(sbn_caf_diff_icarus_osc->Clone("sbn_caf_diff_icarus"));

  sbn_caf_diff_sbnd  ->Divide(val_diff_sbnd);
  sbn_caf_diff_uboone->Divide(val_diff_uboone);
  sbn_caf_diff_icarus->Divide(val_diff_icarus);

  val_diff_sbnd->Divide(sbn_diff_sbnd);
  val_diff_sbnd->Draw("hist");

  // Put them in relevant vectors for ease of formatting
  std::vector<TH1D*> unosc_ratios1  = {val_caf_sbnd_unosc, val_caf_uboone_unosc, val_caf_icarus_unosc};
  std::vector<TH1D*> unosc_ratios2  = {sbn_caf_sbnd_unosc, sbn_caf_uboone_unosc, sbn_caf_icarus_unosc};
  std::vector<TH1D*> unosc_ratios3  = {sbn_val_sbnd_unosc, sbn_val_uboone_unosc, sbn_val_icarus_unosc};

  std::vector<TH1D*> osc_ratios1    = {val_caf_sbnd_osc,   val_caf_uboone_osc,   val_caf_icarus_osc};
  std::vector<TH1D*> osc_ratios2    = {sbn_caf_sbnd_osc,   sbn_caf_uboone_osc,   sbn_caf_icarus_osc};
  std::vector<TH1D*> osc_ratios3    = {sbn_val_sbnd_osc,   sbn_val_uboone_osc,   sbn_val_icarus_osc};

  std::vector<TH1D*> val_ratios     = {val_osc_unosc_sbnd, val_osc_unosc_uboone, val_osc_unosc_icarus};
  std::vector<TH1D*> caf_ratios     = {caf_osc_unosc_sbnd, caf_osc_unosc_uboone, caf_osc_unosc_icarus};
  std::vector<TH1D*> sbn_ratios     = {sbn_osc_unosc_sbnd, sbn_osc_unosc_uboone, sbn_osc_unosc_icarus};

  std::vector<TH1D*> double_ratios1 = {val_caf_osc_unosc_sbnd, val_caf_osc_unosc_uboone, val_caf_osc_unosc_icarus};
  std::vector<TH1D*> double_ratios2 = {sbn_caf_osc_unosc_sbnd, sbn_caf_osc_unosc_uboone, sbn_caf_osc_unosc_icarus};
  std::vector<TH1D*> double_ratios3 = {sbn_val_osc_unosc_sbnd, sbn_val_osc_unosc_uboone, sbn_val_osc_unosc_icarus};

  std::vector<TH1D*> osc_diffs1     = {val_caf_diff_sbnd, val_caf_diff_uboone, val_caf_diff_icarus};
  std::vector<TH1D*> osc_diffs2     = {sbn_caf_diff_sbnd, sbn_caf_diff_uboone, sbn_caf_diff_icarus};
  std::vector<TH1D*> osc_diffs3     = {val_sbn_diff_sbnd, val_sbn_diff_uboone, val_sbn_diff_icarus};

  // Now format the histograms
  for(unsigned int i = 0; i < unosc_ratios1.size(); ++i){

    unosc_ratios1  [i]->SetLineColor(kAzure+7);
    unosc_ratios2  [i]->SetLineColor(kPink+5);
    unosc_ratios3  [i]->SetLineColor(kOrange+1);
    osc_ratios1    [i]->SetLineColor(kAzure+7);
    osc_ratios2    [i]->SetLineColor(kPink+5);
    osc_ratios3    [i]->SetLineColor(kOrange+1);
    double_ratios1 [i]->SetLineColor(kAzure+7);
    double_ratios2 [i]->SetLineColor(kPink+5);
    double_ratios3 [i]->SetLineColor(kOrange+1);
    osc_diffs1     [i]->SetLineColor(kAzure+7);
    osc_diffs2     [i]->SetLineColor(kPink+5);
    osc_diffs3     [i]->SetLineColor(kOrange+1);

    unosc_ratios1  [i]->SetLineWidth(2);
    unosc_ratios2  [i]->SetLineWidth(2);
    unosc_ratios3  [i]->SetLineWidth(2);
    osc_ratios1    [i]->SetLineWidth(2);
    osc_ratios2    [i]->SetLineWidth(2);
    osc_ratios3    [i]->SetLineWidth(2);
    double_ratios1 [i]->SetLineWidth(2);
    double_ratios2 [i]->SetLineWidth(2);
    double_ratios3 [i]->SetLineWidth(2);
    osc_diffs1     [i]->SetLineWidth(2);
    osc_diffs2     [i]->SetLineWidth(2);
    osc_diffs3     [i]->SetLineWidth(2);

    unosc_ratios1  [i]->SetLineStyle(2);
    unosc_ratios2  [i]->SetLineStyle(5);
    unosc_ratios3  [i]->SetLineStyle(9);
    osc_ratios1    [i]->SetLineStyle(2);
    osc_ratios2    [i]->SetLineStyle(5);
    osc_ratios3    [i]->SetLineStyle(9);
    double_ratios1 [i]->SetLineStyle(2);
    double_ratios2 [i]->SetLineStyle(5);
    double_ratios3 [i]->SetLineStyle(9);
    osc_diffs1     [i]->SetLineStyle(2);
    osc_diffs2     [i]->SetLineStyle(5);
    osc_diffs3     [i]->SetLineStyle(9);
  
    unosc_ratios1[i]->SetStats(0);
    unosc_ratios1[i]->SetTitle("");
    unosc_ratios1[i]->GetXaxis()->SetTitle("E_{Reco} [GeV]");
    unosc_ratios1[i]->GetYaxis()->SetTitle("Unoscillated event rate ratio");
    unosc_ratios1[i]->GetXaxis()->SetTitleFont(132);
    unosc_ratios1[i]->GetYaxis()->SetTitleFont(132);
    unosc_ratios1[i]->GetXaxis()->SetLabelFont(132);
    unosc_ratios1[i]->GetYaxis()->SetLabelFont(132);
    unosc_ratios1[i]->GetXaxis()->SetTitleSize(0.035);
    unosc_ratios1[i]->GetYaxis()->SetTitleSize(0.035);
    unosc_ratios1[i]->GetXaxis()->SetLabelSize(0.03);
    unosc_ratios1[i]->GetYaxis()->SetLabelSize(0.03);
    unosc_ratios1[i]->GetXaxis()->SetTitleOffset(1.2);
    unosc_ratios1[i]->GetYaxis()->SetTitleOffset(1.8);
    unosc_ratios1[i]->GetXaxis()->SetMaxDigits(3);
    unosc_ratios1[i]->GetYaxis()->SetMaxDigits(3);
    
    osc_ratios1[i]->SetStats(0);
    osc_ratios1[i]->SetTitle("");
    osc_ratios1[i]->GetXaxis()->SetTitle("E_{Reco} [GeV]");
    osc_ratios1[i]->GetYaxis()->SetTitle("Oscillated event rate ratio");
    osc_ratios1[i]->GetXaxis()->SetTitleFont(132);
    osc_ratios1[i]->GetYaxis()->SetTitleFont(132);
    osc_ratios1[i]->GetXaxis()->SetLabelFont(132);
    osc_ratios1[i]->GetYaxis()->SetLabelFont(132);
    osc_ratios1[i]->GetXaxis()->SetTitleSize(0.035);
    osc_ratios1[i]->GetYaxis()->SetTitleSize(0.035);
    osc_ratios1[i]->GetXaxis()->SetLabelSize(0.03);
    osc_ratios1[i]->GetYaxis()->SetLabelSize(0.03);
    osc_ratios1[i]->GetXaxis()->SetTitleOffset(1.2);
    osc_ratios1[i]->GetYaxis()->SetTitleOffset(1.8);
    osc_ratios1[i]->GetXaxis()->SetMaxDigits(3);
    osc_ratios1[i]->GetYaxis()->SetMaxDigits(3);
    
    double_ratios1[i]->SetStats(0);
    double_ratios1[i]->SetTitle("");
    double_ratios1[i]->GetXaxis()->SetTitle("E_{Reco} [GeV]");
    double_ratios1[i]->GetYaxis()->SetTitle("Event rate ratio");
    double_ratios1[i]->GetXaxis()->SetTitleFont(132);
    double_ratios1[i]->GetYaxis()->SetTitleFont(132);
    double_ratios1[i]->GetXaxis()->SetLabelFont(132);
    double_ratios1[i]->GetYaxis()->SetLabelFont(132);
    double_ratios1[i]->GetXaxis()->SetTitleSize(0.035);
    double_ratios1[i]->GetYaxis()->SetTitleSize(0.035);
    double_ratios1[i]->GetXaxis()->SetLabelSize(0.03);
    double_ratios1[i]->GetYaxis()->SetLabelSize(0.03);
    double_ratios1[i]->GetXaxis()->SetTitleOffset(1.2);
    double_ratios1[i]->GetYaxis()->SetTitleOffset(1.8);
    double_ratios1[i]->GetXaxis()->SetMaxDigits(3);
    double_ratios1[i]->GetYaxis()->SetMaxDigits(3);
    
    osc_diffs1[i]->SetStats(0);
    osc_diffs1[i]->SetTitle("");
    osc_diffs1[i]->GetXaxis()->SetTitle("E_{Reco} [GeV]");
    osc_diffs1[i]->GetYaxis()->SetTitle("Oscillated event rate difference");
    osc_diffs1[i]->GetXaxis()->SetTitleFont(132);
    osc_diffs1[i]->GetYaxis()->SetTitleFont(132);
    osc_diffs1[i]->GetXaxis()->SetLabelFont(132);
    osc_diffs1[i]->GetYaxis()->SetLabelFont(132);
    osc_diffs1[i]->GetXaxis()->SetTitleSize(0.035);
    osc_diffs1[i]->GetYaxis()->SetTitleSize(0.035);
    osc_diffs1[i]->GetXaxis()->SetLabelSize(0.03);
    osc_diffs1[i]->GetYaxis()->SetLabelSize(0.03);
    osc_diffs1[i]->GetXaxis()->SetTitleOffset(1.2);
    osc_diffs1[i]->GetYaxis()->SetTitleOffset(1.8);
    osc_diffs1[i]->GetXaxis()->SetMaxDigits(3);
    osc_diffs1[i]->GetYaxis()->SetMaxDigits(3);
    
  }

  TCanvas *c = new TCanvas("c","c",20,20,900,900);
  c->SetRightMargin(0.08);
  c->SetLeftMargin(0.12);
  c->SetTopMargin(0.08);
  c->SetBottomMargin(0.12);

  // Add legend
  TLegend *leg = new TLegend(0.44098, 0.723435, 0.891982, 0.877729);
  leg->SetEntrySeparation(0.01);
  leg->SetTextFont(132);
  leg->SetTextColor(1);
  leg->SetFillStyle(0);
  leg->SetLineWidth(0);

  // SBND double ratios
  leg->AddEntry(val_caf_osc_unosc_sbnd,"VALOR_{osc/unosc}/CAFAna_{osc/unosc} SBND", "l");
  leg->AddEntry(sbn_caf_osc_unosc_sbnd,"SBNFit_{osc/unosc}/CAFAna_{osc/unosc} SBND", "l");
  leg->AddEntry(sbn_val_osc_unosc_sbnd,"SBNFit_{osc/unosc}/VALOR_{osc/unosc} SBND", "l");

  double max_double_sbnd = 1.00001 * std::max(val_caf_osc_unosc_sbnd->GetMaximum(), std::max(sbn_caf_osc_unosc_sbnd->GetMaximum(), sbn_val_osc_unosc_sbnd->GetMaximum()));
  double min_double_sbnd = 0.99999 * std::min(val_caf_osc_unosc_sbnd->GetMinimum(), std::min(sbn_caf_osc_unosc_sbnd->GetMinimum(), sbn_val_osc_unosc_sbnd->GetMinimum()));
  
  // Draw
  val_caf_osc_unosc_sbnd->GetYaxis()->SetRangeUser(min_double_sbnd,max_double_sbnd);
  val_caf_osc_unosc_sbnd->Draw("hist");       
  sbn_caf_osc_unosc_sbnd->Draw("hist same");
  sbn_val_osc_unosc_sbnd->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("all_fitters_osc_unosc_double_ratios_sbnd_dmsq-1e2_sinsqmumu-2e-3.root");
  c->SaveAs("all_fitters_osc_unosc_double_ratios_sbnd_dmsq-1e2_sinsqmumu-2e-3.png");
  c->Clear();
  leg->Clear();

  // MicroBooNE double ratios
  leg->AddEntry(val_caf_osc_unosc_uboone,"VALOR_{osc/unosc}/CAFAna_{osc/unosc} #muBooNE", "l");
  leg->AddEntry(sbn_caf_osc_unosc_uboone,"SBNFit_{osc/unosc}/CAFAna_{osc/unosc} #muBooNE", "l");
  leg->AddEntry(sbn_val_osc_unosc_uboone,"SBNFit_{osc/unosc}/VALOR_{osc/unosc} #muBooNE", "l");

  double max_double_uboone = 1.00001 * std::max(val_caf_osc_unosc_uboone->GetMaximum(), std::max(sbn_caf_osc_unosc_uboone->GetMaximum(), sbn_val_osc_unosc_uboone->GetMaximum()));
  double min_double_uboone = 0.99999 * std::min(val_caf_osc_unosc_uboone->GetMinimum(), std::min(sbn_caf_osc_unosc_uboone->GetMinimum(), sbn_val_osc_unosc_uboone->GetMinimum()));
  
  // Draw
  val_caf_osc_unosc_uboone->GetYaxis()->SetRangeUser(min_double_uboone,max_double_uboone);
  val_caf_osc_unosc_uboone->Draw("hist");       
  sbn_caf_osc_unosc_uboone->Draw("hist same");
  sbn_val_osc_unosc_uboone->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("all_fitters_osc_unosc_double_ratios_uboone_dmsq-1e2_sinsqmumu-2e-3.root");
  c->SaveAs("all_fitters_osc_unosc_double_ratios_uboone_dmsq-1e2_sinsqmumu-2e-3.png");
  c->Clear();
  leg->Clear();

  // ICARUS double ratios
  leg->AddEntry(val_caf_osc_unosc_icarus,"VALOR_{osc/unosc}/CAFAna_{osc/unosc} ICARUS", "l");
  leg->AddEntry(sbn_caf_osc_unosc_icarus,"SBNFit_{osc/unosc}/CAFAna_{osc/unosc} ICARUS", "l");
  leg->AddEntry(sbn_val_osc_unosc_icarus,"SBNFit_{osc/unosc}/VALOR_{osc/unosc} ICARUS", "l");

  double max_double_icarus = 1.00001 * std::max(val_caf_osc_unosc_icarus->GetMaximum(), std::max(sbn_caf_osc_unosc_icarus->GetMaximum(), sbn_val_osc_unosc_icarus->GetMaximum()));
  double min_double_icarus = 0.99999 * std::min(val_caf_osc_unosc_icarus->GetMinimum(), std::min(sbn_caf_osc_unosc_icarus->GetMinimum(), sbn_val_osc_unosc_icarus->GetMinimum()));
  
  // Draw
  val_caf_osc_unosc_icarus->GetYaxis()->SetRangeUser(min_double_icarus,max_double_icarus);
  val_caf_osc_unosc_icarus->Draw("hist");       
  sbn_caf_osc_unosc_icarus->Draw("hist same");
  sbn_val_osc_unosc_icarus->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("all_fitters_osc_unosc_double_ratios_icarus_dmsq-1e2_sinsqmumu-2e-3.root");
  c->SaveAs("all_fitters_osc_unosc_double_ratios_icarus_dmsq-1e2_sinsqmumu-2e-3.png");
  c->Clear();
  leg->Clear();

  // SBND VALOR & SBNFit / CAFAna single ratios
  leg->SetX1NDC(0.416481);
  leg->SetY1NDC(0.187773);
  leg->SetX2NDC(0.994432);
  leg->SetY2NDC(0.375546);

  leg->AddEntry(val_caf_sbnd_osc,"VALOR/CAFAna oscillated SBND", "l");
  leg->AddEntry(sbn_caf_sbnd_osc,"SBNFit/CAFAna oscillated SBND", "l");
  leg->AddEntry(sbn_val_sbnd_osc,"SBNFit/VALOR oscillated SBND", "l");
 
  double max_osc_single_sbnd = 1.001 * std::max(val_caf_sbnd_osc->GetMaximum(), std::max(sbn_caf_sbnd_osc->GetMaximum(), sbn_val_sbnd_osc->GetMaximum()));
  double min_osc_single_sbnd = 0.999 * std::min(val_caf_sbnd_osc->GetMinimum(), std::min(sbn_caf_sbnd_osc->GetMinimum(), sbn_val_sbnd_osc->GetMinimum()));
  
  // Draw
  val_caf_sbnd_osc->GetYaxis()->SetRangeUser(min_osc_single_sbnd,max_osc_single_sbnd);
  val_caf_sbnd_osc->Draw("hist"); 
  sbn_caf_sbnd_osc->Draw("hist same");
  sbn_val_sbnd_osc->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("all_fitters_osc_single_ratios_sbnd_dmsq-1e2_sinsqmumu-2e-3.root");
  c->SaveAs("all_fitters_osc_single_ratios_sbnd_dmsq-1e2_sinsqmumu-2e-3.png");
  c->Clear();
  leg->Clear();

  // uBooNE VALOR and CAFAna single ratios
  leg->SetX2NDC(0.939866);

  leg->AddEntry(val_caf_uboone_osc,"VALOR/CAFAna oscillated #muBooNE", "l");
  leg->AddEntry(sbn_caf_uboone_osc,"SBNFit/CAFAna oscillated #muBooNE", "l");
  leg->AddEntry(sbn_val_uboone_osc,"SBNFit/VALOR oscillated #muBooNE", "l");
  
  double max_osc_single_uboone = 1.001 * std::max(val_caf_uboone_osc->GetMaximum(), std::max(sbn_caf_uboone_osc->GetMaximum(), sbn_val_uboone_osc->GetMaximum()));
  double min_osc_single_uboone = 0.999 * std::min(val_caf_uboone_osc->GetMinimum(), std::min(sbn_caf_uboone_osc->GetMinimum(), sbn_val_uboone_osc->GetMinimum()));
  
  // Draw
  val_caf_uboone_osc->GetYaxis()->SetRangeUser(min_osc_single_uboone,max_osc_single_uboone);
  val_caf_uboone_osc->Draw("hist"); 
  sbn_val_uboone_osc->Draw("hist same");
  sbn_caf_uboone_osc->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("all_fitters_osc_single_ratios_uboone_dmsq-1e2_sinsqmumu-2e-3.root");
  c->SaveAs("all_fitters_osc_single_ratios_uboone_dmsq-1e2_sinsqmumu-2e-3.png");
  c->Clear();
  leg->Clear();

  // ICARUS VALOR and CAFAna single ratios
  leg->AddEntry(val_caf_icarus_osc,"VALOR/CAFAna oscillated ICARUS", "l");
  leg->AddEntry(sbn_caf_icarus_osc,"SBNFit/CAFAna oscillated ICARUS", "l");
  leg->AddEntry(sbn_val_icarus_osc,"SBNFit/VALOR oscillated ICARUS", "l");
  
  double max_osc_single_icarus = 1.001 * std::max(val_caf_icarus_osc->GetMaximum(), std::max(sbn_caf_icarus_osc->GetMaximum(), sbn_val_icarus_osc->GetMaximum()));
  double min_osc_single_icarus = 0.999 * std::min(val_caf_icarus_osc->GetMinimum(), std::min(sbn_caf_icarus_osc->GetMinimum(), sbn_val_icarus_osc->GetMinimum()));
  
  // Draw
  val_caf_icarus_osc->GetYaxis()->SetRangeUser(min_osc_single_icarus,max_osc_single_icarus);
  val_caf_icarus_osc->Draw("hist"); 
  sbn_val_icarus_osc->Draw("hist same");
  sbn_caf_icarus_osc->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("all_fitters_osc_single_ratios_icarus_dmsq-1e2_sinsqmumu-2e-3.root");
  c->SaveAs("all_fitters_osc_single_ratios_icarus_dmsq-1e2_sinsqmumu-2e-3.png");
  c->Clear();
  leg->Clear();

  // SBND VALOR & SBNFit / CAFAna single ratios
  leg->AddEntry(val_caf_sbnd_unosc,"VALOR/CAFAna unoscillated SBND", "l");
  leg->AddEntry(sbn_caf_sbnd_unosc,"SBNFit/CAFAna unoscillated SBND", "l");
  leg->AddEntry(sbn_val_sbnd_unosc,"SBNFit/VALOR unoscillated SBND", "l");
 
  // Draw
  val_caf_sbnd_unosc->GetYaxis()->SetRangeUser(0.9,1.1);
  val_caf_sbnd_unosc->Draw("hist"); 
  sbn_caf_sbnd_unosc->Draw("hist same");
  sbn_val_sbnd_unosc->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("all_fitters_unosc_single_ratios_sbnd.root");
  c->SaveAs("all_fitters_unosc_single_ratios_sbnd.png");
  c->Clear();
  leg->Clear();

  // uBooNE VALOR and CAFAna single ratios
  leg->SetX1NDC(0.415367);
  leg->SetY1NDC(0.189229);
  leg->SetX2NDC(0.928731);
  leg->SetY2NDC(0.377001);

  leg->AddEntry(val_caf_uboone_unosc,"VALOR/CAFAna unoscillated #muBooNE", "l");
  leg->AddEntry(sbn_caf_uboone_unosc,"SBNFit/CAFAna unoscillated #muBooNE", "l");
  leg->AddEntry(sbn_val_uboone_unosc,"SBNFit/VALOR unoscillated #muBooNE", "l");
 
  // Draw
  val_caf_uboone_unosc->GetYaxis()->SetRangeUser(0.9,1.1);
  val_caf_uboone_unosc->Draw("hist"); 
  sbn_val_uboone_unosc->Draw("hist same");
  sbn_caf_uboone_unosc->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("all_fitters_unosc_single_ratios_uboone.root");
  c->SaveAs("all_fitters_unosc_single_ratios_uboone.png");
  c->Clear();
  leg->Clear();

  // ICARUS VALOR and CAFAna single ratios
  leg->AddEntry(val_caf_icarus_unosc,"VALOR/CAFAna unoscillated ICARUS", "l");
  leg->AddEntry(sbn_caf_icarus_unosc,"SBNFit/CAFAna unoscillated ICARUS", "l");
  leg->AddEntry(sbn_val_icarus_unosc,"SBNFit/VALOR unoscillated ICARUS", "l");
 
  // Draw
  val_caf_icarus_unosc->GetYaxis()->SetRangeUser(0.9,1.1);
  val_caf_icarus_unosc->Draw("hist"); 
  sbn_val_icarus_unosc->Draw("hist same");
  sbn_caf_icarus_unosc->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("all_fitters_unosc_single_ratios_icarus.root");
  c->SaveAs("all_fitters_unosc_single_ratios_icarus.png");
  c->Clear();
  leg->Clear();

  // SBND Oscillated event rate differences
  leg->SetX1NDC(0.336303);
  leg->SetY1NDC(0.688501);
  leg->SetX2NDC(0.851893);
  leg->SetY2NDC(0.874818);

  leg->AddEntry(val_caf_diff_sbnd,"(VAL_{osc}-CAF_{osc})/(VAL_{nom}-VAL_{osc}) SBND", "l");
  leg->AddEntry(val_sbn_diff_sbnd,"(VAL_{osc}-SBN_{osc})/(VAL_{nom}-VAL_{osc}) SBND", "l");
  leg->AddEntry(sbn_caf_diff_sbnd,"(SBN_{osc}-CAF_{osc})/(VAL_{nom}-VAL_{osc}) SBND", "l");
 
  // Draw
  val_caf_diff_sbnd->GetYaxis()->SetRangeUser(-0.1,0.22);
  val_caf_diff_sbnd->Draw("hist"); 
  sbn_caf_diff_sbnd->Draw("hist same"); 
  val_sbn_diff_sbnd->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("all_fitters_osc_diffs_sbnd_dmsq-1e2_sinsqmumu-2e-3.root");
  c->SaveAs("all_fitters_osc_diffs_sbnd_dmsq-1e2_sinsqmumu-2e-3.png");
  c->Clear();
  leg->Clear();

  // uboone Oscillated event rate differences
  leg->AddEntry(val_caf_diff_uboone,"(VAL_{osc}-CAF_{osc})/(VAL_{nom}-VAL_{osc}) #muBooNE", "l");
  leg->AddEntry(val_sbn_diff_uboone,"(VAL_{osc}-SBN_{osc})/(VAL_{nom}-VAL_{osc}) #muBooNE", "l");
  leg->AddEntry(sbn_caf_diff_uboone,"(SBN_{osc}-CAF_{osc})/(VAL_{nom}-VAL_{osc}) #muBooNE", "l");
 
  // Draw
  val_caf_diff_uboone->GetYaxis()->SetRangeUser(-0.1,0.45);
  val_caf_diff_uboone->Draw("hist"); 
  sbn_caf_diff_uboone->Draw("hist same"); 
  val_sbn_diff_uboone->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("all_fitters_osc_diffs_uboone_dmsq-1e2_sinsqmumu-2e-3.root");
  c->SaveAs("all_fitters_osc_diffs_uboone_dmsq-1e2_sinsqmumu-2e-3.png");
  c->Clear();
  leg->Clear();

  // icarus Oscillated event rate differences
  leg->AddEntry(val_caf_diff_icarus,"(VAL_{osc}-CAF_{osc})/(VAL_{nom}-VAL_{osc}) ICARUS", "l");
  leg->AddEntry(val_sbn_diff_icarus,"(VAL_{osc}-SBN_{osc})/(VAL_{nom}-VAL_{osc}) ICARUS", "l");
  leg->AddEntry(sbn_caf_diff_icarus,"(SBN_{osc}-CAF_{osc})/(VAL_{nom}-VAL_{osc}) ICARUS", "l");
 
  // Draw
  val_caf_diff_icarus->GetYaxis()->SetRangeUser(-0.1,0.6);
  val_caf_diff_icarus->Draw("hist"); 
  sbn_caf_diff_icarus->Draw("hist same"); 
  val_sbn_diff_icarus->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("all_fitters_osc_diffs_icarus_dmsq-1e2_sinsqmumu-2e-3.root");
  c->SaveAs("all_fitters_osc_diffs_icarus_dmsq-1e2_sinsqmumu-2e-3.png");
  c->Clear();
  leg->Clear();

}
