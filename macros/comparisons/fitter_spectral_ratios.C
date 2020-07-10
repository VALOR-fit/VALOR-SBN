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

  TFile *f_val = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/pdfs/sbn/mdc/dmsq_2_sinsqmumu_3e-3_hists.root","read");
  TFile *f_sbn = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/pdfs/sbn/mdc/fitters/SBNfit_dmsq_2_sinsq2mumu_3e-3_hists.root","read");
  TFile *f_caf = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/pdfs/sbn/mdc/fitters/CAFAna_dmsq_2_ss2thmm_3e-3.root","read");

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

  // SBNFit
  TH1D *sbn_sbnd_cc   = static_cast<TH1D*>(f_sbn->Get("nu_SBND_numu_cc"));
  TH1D *sbn_sbnd_nc   = static_cast<TH1D*>(f_sbn->Get("nu_SBND_numu_nc"));
  TH1D *sbn_uboone_cc = static_cast<TH1D*>(f_sbn->Get("nu_uBooNE_numu_cc"));
  TH1D *sbn_uboone_nc = static_cast<TH1D*>(f_sbn->Get("nu_uBooNE_numu_nc"));
  TH1D *sbn_icarus_cc = static_cast<TH1D*>(f_sbn->Get("nu_ICARUS_numu_cc"));
  TH1D *sbn_icarus_nc = static_cast<TH1D*>(f_sbn->Get("nu_ICARUS_numu_nc"));

  // Now get the totals
  TH1D *sbn_sbnd_osc_noscale    = static_cast<TH1D*>(sbn_sbnd_cc->Clone("nu_SBND_numu_osc"));
  TH1D *sbn_uboone_osc_noscale  = static_cast<TH1D*>(sbn_uboone_cc->Clone("nu_uBooNE_numu_osc"));
  TH1D *sbn_icarus_osc_noscale  = static_cast<TH1D*>(sbn_icarus_cc->Clone("nu_ICARUS_numu_osc"));
  sbn_sbnd_osc_noscale->Add(sbn_sbnd_nc);
  sbn_uboone_osc_noscale->Add(sbn_uboone_nc);
  sbn_icarus_osc_noscale->Add(sbn_icarus_nc);

  // Scale the SBNFit hist by width
  TH1D * sbn_sbnd_osc   = new TH1D(*sbn_sbnd_osc_noscale);
  TH1D * sbn_uboone_osc = new TH1D(*sbn_uboone_osc_noscale);
  TH1D * sbn_icarus_osc = new TH1D(*sbn_icarus_osc_noscale);
  
  // Get a vector of each fitter's histograms
  std::vector<TH1D*> sbnfit = {sbn_sbnd_osc, sbn_uboone_osc, sbn_icarus_osc};
  std::vector<TH1D*> cafana = {caf_sbnd_osc, caf_uboone_osc, caf_icarus_osc};
  std::vector<TH1D*> valor  = {val_sbnd_osc, val_uboone_osc, val_icarus_osc};
  for(TH1D* hist : sbnfit){
    for (int ibin = 1 ; ibin <= hist->GetXaxis()->GetNbins(); ibin++) {
      double old_bin_content = hist->GetBinContent(ibin);
      double bin_width       = hist->GetXaxis()->GetBinWidth(ibin);
      double new_bin_content = old_bin_content / bin_width;
      hist->SetBinContent(ibin,new_bin_content);
    }
  }

  // Now get the ratios
  // First, unoscillated
  TH1D *val_caf_sbnd_unosc   = static_cast<TH1D*>(val_sbnd_unosc  ->Clone("val_caf_sbnd_unosc  "));
  TH1D *val_caf_uboone_unosc = static_cast<TH1D*>(val_uboone_unosc->Clone("val_caf_uboone_unosc"));
  TH1D *val_caf_icarus_unosc = static_cast<TH1D*>(val_icarus_unosc->Clone("val_caf_icarus_unosc"));
  
  val_caf_sbnd_unosc  ->Divide(caf_sbnd_unosc  );
  val_caf_uboone_unosc->Divide(caf_uboone_unosc);
  val_caf_icarus_unosc->Divide(caf_icarus_unosc);

  // Then, oscillated
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

  // Finally, (VALOR oscillated/unoscillated) / (CAFAna oscillated/unoscillated)
  TH1D *val_caf_osc_unosc_sbnd   = static_cast<TH1D*>(val_osc_unosc_sbnd  ->Clone("val_caf_osc_unosc_sbnd  "));
  TH1D *val_caf_osc_unosc_uboone = static_cast<TH1D*>(val_osc_unosc_uboone->Clone("val_caf_osc_unosc_uboone"));
  TH1D *val_caf_osc_unosc_icarus = static_cast<TH1D*>(val_osc_unosc_icarus->Clone("val_caf_osc_unosc_icarus"));
  
  val_caf_osc_unosc_sbnd  ->Divide(caf_osc_unosc_sbnd  );
  val_caf_osc_unosc_uboone->Divide(caf_osc_unosc_uboone);
  val_caf_osc_unosc_icarus->Divide(caf_osc_unosc_icarus);

  std::vector<TH1D*> unosc_ratios   = {val_caf_sbnd_unosc, val_caf_uboone_unosc, val_caf_icarus_unosc};
  std::vector<TH1D*> osc_ratios     = {val_caf_sbnd_osc,   val_caf_uboone_osc,   val_caf_icarus_osc};
  std::vector<TH1D*> osc_ratios2    = {sbn_caf_sbnd_osc,   sbn_caf_uboone_osc,   sbn_caf_icarus_osc};
  std::vector<TH1D*> osc_ratios3    = {sbn_val_sbnd_osc,   sbn_val_uboone_osc,   sbn_val_icarus_osc};
  std::vector<TH1D*> val_ratios     = {val_osc_unosc_sbnd, val_osc_unosc_uboone, val_osc_unosc_icarus};
  std::vector<TH1D*> caf_ratios     = {caf_osc_unosc_sbnd, caf_osc_unosc_uboone, caf_osc_unosc_icarus};
  std::vector<TH1D*> val_caf_ratios = {val_caf_osc_unosc_sbnd, val_caf_osc_unosc_uboone, val_caf_osc_unosc_icarus};

  val_caf_ratios[0]->SetLineColor(kPink+5);
  val_caf_ratios[0]->SetLineWidth(2);
  val_caf_ratios[0]->SetLineStyle(2);

  val_caf_ratios[1]->SetLineColor(kOrange+1);
  val_caf_ratios[1]->SetLineWidth(2);
  val_caf_ratios[1]->SetLineStyle(5);

  val_caf_ratios[2]->SetLineColor(kAzure+7);
  val_caf_ratios[2]->SetLineWidth(2);
  val_caf_ratios[2]->SetLineStyle(9);

  // Now format the histograms
  for(unsigned int i = 0; i < unosc_ratios.size(); ++i){

    val_ratios    [i]->SetLineColor(kPink+5);
    caf_ratios    [i]->SetLineColor(kOrange+1);
    unosc_ratios  [i]->SetLineColor(kOrange+1);
    osc_ratios    [i]->SetLineColor(kAzure+7);
    osc_ratios2   [i]->SetLineColor(kPink+5);
    osc_ratios3   [i]->SetLineColor(kOrange+1);

    val_ratios    [i]->SetLineWidth(2);
    caf_ratios    [i]->SetLineWidth(2);
    unosc_ratios  [i]->SetLineWidth(2);
    osc_ratios    [i]->SetLineWidth(2);
    osc_ratios2   [i]->SetLineWidth(2);
    osc_ratios3   [i]->SetLineWidth(2);

    val_ratios    [i]->SetLineStyle(2);
    caf_ratios    [i]->SetLineStyle(5);
    unosc_ratios  [i]->SetLineStyle(2);
    osc_ratios    [i]->SetLineStyle(2);
    osc_ratios2   [i]->SetLineStyle(5);
    osc_ratios3   [i]->SetLineStyle(9);
  
    unosc_ratios[i]->SetStats(0);
    unosc_ratios[i]->SetTitle("");
    unosc_ratios[i]->GetXaxis()->SetTitle("E_{Reco} [GeV]");
    unosc_ratios[i]->GetYaxis()->SetTitle("Event rate ratio");
    unosc_ratios[i]->GetXaxis()->SetTitleFont(132);
    unosc_ratios[i]->GetYaxis()->SetTitleFont(132);
    unosc_ratios[i]->GetXaxis()->SetLabelFont(132);
    unosc_ratios[i]->GetYaxis()->SetLabelFont(132);
    unosc_ratios[i]->GetXaxis()->SetTitleSize(0.035);
    unosc_ratios[i]->GetYaxis()->SetTitleSize(0.035);
    unosc_ratios[i]->GetXaxis()->SetLabelSize(0.03);
    unosc_ratios[i]->GetYaxis()->SetLabelSize(0.03);
    unosc_ratios[i]->GetXaxis()->SetTitleOffset(1.2);
    unosc_ratios[i]->GetYaxis()->SetTitleOffset(1.2);
    unosc_ratios[i]->GetXaxis()->SetMaxDigits(3);
    unosc_ratios[i]->GetYaxis()->SetMaxDigits(3);
    
    osc_ratios[i]->SetStats(0);
    osc_ratios[i]->SetTitle("");
    osc_ratios[i]->GetXaxis()->SetTitle("E_{Reco} [GeV]");
    osc_ratios[i]->GetYaxis()->SetTitle("Event rate ratio");
    osc_ratios[i]->GetXaxis()->SetTitleFont(132);
    osc_ratios[i]->GetYaxis()->SetTitleFont(132);
    osc_ratios[i]->GetXaxis()->SetLabelFont(132);
    osc_ratios[i]->GetYaxis()->SetLabelFont(132);
    osc_ratios[i]->GetXaxis()->SetTitleSize(0.035);
    osc_ratios[i]->GetYaxis()->SetTitleSize(0.035);
    osc_ratios[i]->GetXaxis()->SetLabelSize(0.03);
    osc_ratios[i]->GetYaxis()->SetLabelSize(0.03);
    osc_ratios[i]->GetXaxis()->SetTitleOffset(1.2);
    osc_ratios[i]->GetYaxis()->SetTitleOffset(1.2);
    osc_ratios[i]->GetXaxis()->SetMaxDigits(3);
    osc_ratios[i]->GetYaxis()->SetMaxDigits(3);
    
    val_ratios[i]->SetStats(0);
    val_ratios[i]->SetTitle("");
    val_ratios[i]->GetXaxis()->SetTitle("E_{Reco} [GeV]");
    val_ratios[i]->GetYaxis()->SetTitle("Event rate ratio");
    val_ratios[i]->GetXaxis()->SetTitleFont(132);
    val_ratios[i]->GetYaxis()->SetTitleFont(132);
    val_ratios[i]->GetXaxis()->SetLabelFont(132);
    val_ratios[i]->GetYaxis()->SetLabelFont(132);
    val_ratios[i]->GetXaxis()->SetTitleSize(0.035);
    val_ratios[i]->GetYaxis()->SetTitleSize(0.035);
    val_ratios[i]->GetXaxis()->SetLabelSize(0.03);
    val_ratios[i]->GetYaxis()->SetLabelSize(0.03);
    val_ratios[i]->GetXaxis()->SetTitleOffset(1.2);
    val_ratios[i]->GetYaxis()->SetTitleOffset(1.2);
    val_ratios[i]->GetXaxis()->SetMaxDigits(3);
    val_ratios[i]->GetYaxis()->SetMaxDigits(3);
    
    val_caf_ratios[i]->SetStats(0);
    val_caf_ratios[i]->SetTitle("");
    val_caf_ratios[i]->GetXaxis()->SetTitle("E_{Reco} [GeV]");
    val_caf_ratios[i]->GetYaxis()->SetTitle("Event rate ratio");
    val_caf_ratios[i]->GetXaxis()->SetTitleFont(132);
    val_caf_ratios[i]->GetYaxis()->SetTitleFont(132);
    val_caf_ratios[i]->GetXaxis()->SetLabelFont(132);
    val_caf_ratios[i]->GetYaxis()->SetLabelFont(132);
    val_caf_ratios[i]->GetXaxis()->SetTitleSize(0.035);
    val_caf_ratios[i]->GetYaxis()->SetTitleSize(0.035);
    val_caf_ratios[i]->GetXaxis()->SetLabelSize(0.03);
    val_caf_ratios[i]->GetYaxis()->SetLabelSize(0.03);
    val_caf_ratios[i]->GetXaxis()->SetTitleOffset(1.2);
    val_caf_ratios[i]->GetYaxis()->SetTitleOffset(1.6);
    val_caf_ratios[i]->GetXaxis()->SetMaxDigits(3);
    val_caf_ratios[i]->GetYaxis()->SetMaxDigits(3);
  }

  TCanvas *c = new TCanvas("c","c",20,20,900,900);
  c->SetRightMargin(0.08);
  c->SetLeftMargin(0.12);
  c->SetTopMargin(0.08);
  c->SetBottomMargin(0.12);

  // Add legend
  TLegend *leg = new TLegend(0.547884, 0.152838, 0.997773, 0.305677);
  leg->SetEntrySeparation(0.01);
  leg->SetTextFont(132);
  leg->SetTextColor(1);
  leg->SetFillStyle(0);
  leg->SetLineWidth(0);

  // SBND VALOR and CAFAna single ratios
  leg->AddEntry(caf_osc_unosc_sbnd,"CAFAna SBND osc/unosc", "l");
  leg->AddEntry(val_osc_unosc_sbnd,"VALOR SBND osc/unosc", "l");
 
  double max_single_sbnd = 1.0001 * std::max(caf_osc_unosc_sbnd->GetMaximum(), val_osc_unosc_sbnd->GetMaximum());
  double min_single_sbnd = std::min(caf_osc_unosc_sbnd->GetMinimum(), val_osc_unosc_sbnd->GetMinimum());
  if(min_single_sbnd < 0)
    min_single_sbnd *= 1.0001;
  else
    min_single_sbnd *= 0.9999;

  // Draw
  val_osc_unosc_sbnd->GetYaxis()->SetRangeUser(min_single_sbnd,max_single_sbnd);
  val_osc_unosc_sbnd->Draw(); 
  caf_osc_unosc_sbnd->Draw("same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("caf_val_osc_unosc_ratios_sbnd_dmsq-2_sinsqmumu-3e-3.root");
  c->SaveAs("caf_val_osc_unosc_ratios_sbnd_dmsq-2_sinsqmumu-3e-3.png");
  c->Clear();
  leg->Clear();

  // uBooNE VALOR and CAFAna single ratios
  leg->AddEntry(caf_osc_unosc_uboone,"CAFAna #muBooNE osc/unosc", "l");
  leg->AddEntry(val_osc_unosc_uboone,"VALOR #muBooNE osc/unosc", "l");
 
  leg->SetX1NDC(0.374165);
  leg->SetY1NDC(0.697234);
  leg->SetX2NDC(0.906459);
  leg->SetY2NDC(0.889374);

  double max_single_uboone = 1.0001 * std::max(caf_osc_unosc_uboone->GetMaximum(), val_osc_unosc_uboone->GetMaximum());
  double min_single_uboone = std::min(caf_osc_unosc_uboone->GetMinimum(), val_osc_unosc_uboone->GetMinimum());
  if(min_single_uboone < 0)
    min_single_uboone *= 1.0001;
  else
    min_single_uboone *= 0.9999;

  // Draw
  val_osc_unosc_uboone->GetYaxis()->SetRangeUser(min_single_uboone,max_single_uboone);
  val_osc_unosc_uboone->Draw(); 
  caf_osc_unosc_uboone->Draw("same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("caf_val_osc_unosc_ratios_uboone_dmsq-2_sinsqmumu-3e-3.root");
  c->SaveAs("caf_val_osc_unosc_ratios_uboone_dmsq-2_sinsqmumu-3e-3.png");
  c->Clear();
  leg->Clear();

  // icarus VALOR and CAFAna single ratios
  leg->AddEntry(caf_osc_unosc_icarus,"CAFAna ICARUS osc/unosc", "l");
  leg->AddEntry(val_osc_unosc_icarus,"VALOR ICARUS osc/unosc", "l");
 
  double max_single_icarus = 1.0001 * std::max(caf_osc_unosc_icarus->GetMaximum(), val_osc_unosc_icarus->GetMaximum());
  double min_single_icarus = std::min(caf_osc_unosc_icarus->GetMinimum(), val_osc_unosc_icarus->GetMinimum());
  if(min_single_icarus < 0)
    min_single_icarus *= 1.0001;
  else
    min_single_icarus *= 0.9999;

  // Draw
  val_osc_unosc_icarus->GetYaxis()->SetRangeUser(min_single_icarus,max_single_icarus);
  val_osc_unosc_icarus->Draw(); 
  caf_osc_unosc_icarus->Draw("same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("caf_val_osc_unosc_ratios_icarus_dmsq-2_sinsqmumu-3e-3.root");
  c->SaveAs("caf_val_osc_unosc_ratios_icarus_dmsq-2_sinsqmumu-3e-3.png");
  c->Clear();
  leg->Clear();

  // All SBN VALOR and CAFAna double ratios
  leg->AddEntry(val_caf_osc_unosc_sbnd,  "VALOR_{osc/unosc}/CAFAna_{osc/unosc} SBND", "l");
  leg->AddEntry(val_caf_osc_unosc_uboone,"VALOR_{osc/unosc}/CAFAna_{osc/unosc} #muBooNE", "l");
  leg->AddEntry(val_caf_osc_unosc_icarus,"VALOR_{osc/unosc}/CAFAna_{osc/unosc} ICARUS", "l");

  double max_double = 1.00001 * std::max(val_caf_osc_unosc_sbnd->GetMaximum(), std::max(val_caf_osc_unosc_uboone->GetMaximum(), val_caf_osc_unosc_icarus->GetMaximum()));
  double min_double = 0.99999 * std::min(val_caf_osc_unosc_sbnd->GetMinimum(), std::min(val_caf_osc_unosc_uboone->GetMinimum(), val_caf_osc_unosc_icarus->GetMinimum()));
  
  // Draw
  val_caf_osc_unosc_sbnd->GetYaxis()->SetRangeUser(min_double,max_double);
  val_caf_osc_unosc_sbnd  ->Draw("hist");       
  val_caf_osc_unosc_uboone->Draw("hist same");
  val_caf_osc_unosc_icarus->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("caf_val_osc_unosc_double_ratios_sbn_dmsq-2_sinsqmumu-3e-3.root");
  c->SaveAs("caf_val_osc_unosc_double_ratios_sbn_dmsq-2_sinsqmumu-3e-3.png");
  c->Clear();
  leg->Clear();

  // SBND VALOR and CAFAna single ratios
  leg->AddEntry(val_caf_sbnd_osc,  "VALOR/CAFAna oscillated SBND", "l");
  leg->AddEntry(val_caf_sbnd_unosc,"VALOR/CAFAna unoscillated SBND", "l");
 
  // Draw
  val_caf_sbnd_osc->GetYaxis()->SetRangeUser(0.993,1.007);
  val_caf_sbnd_osc->Draw("hist"); 
  val_caf_sbnd_unosc->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("caf_val_osc_unosc_single_ratios_sbnd_dmsq-2_sinsqmumu-3e-3.root");
  c->SaveAs("caf_val_osc_unosc_single_ratios_sbnd_dmsq-2_sinsqmumu-3e-3.png");
  c->Clear();
  leg->Clear();

  // uBooNE VALOR and CAFAna single ratios
  leg->AddEntry(val_caf_uboone_osc,  "VALOR/CAFAna oscillated #muBooNE", "l");
  leg->AddEntry(val_caf_uboone_unosc,"VALOR/CAFAna unoscillated #muBooNE", "l");
 
  // Draw
  val_caf_uboone_osc->GetYaxis()->SetRangeUser(0.998,1.002);
  val_caf_uboone_osc->Draw("hist"); 
  val_caf_uboone_unosc->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("caf_val_osc_unosc_single_ratios_uboone_dmsq-2_sinsqmumu-3e-3.root");
  c->SaveAs("caf_val_osc_unosc_single_ratios_uboone_dmsq-2_sinsqmumu-3e-3.png");
  c->Clear();
  leg->Clear();

  // ICARUS VALOR and CAFAna single ratios
  leg->AddEntry(val_caf_icarus_osc,  "VALOR/CAFAna oscillated ICARUS", "l");
  leg->AddEntry(val_caf_icarus_unosc,"VALOR/CAFAna unoscillated ICARUS", "l");
 
  // Draw
  val_caf_icarus_osc->GetYaxis()->SetRangeUser(0.994,1.006);
  val_caf_icarus_osc->Draw("hist"); 
  val_caf_icarus_unosc->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("caf_val_osc_unosc_single_ratios_icarus_dmsq-2_sinsqmumu-3e-3.root");
  c->SaveAs("caf_val_osc_unosc_single_ratios_icarus_dmsq-2_sinsqmumu-3e-3.png");
  c->Clear();
  leg->Clear();

  // SBND VALOR & SBNFit / CAFAna single ratios
  leg->AddEntry(val_caf_sbnd_osc,"VALOR/CAFAna oscillated SBND", "l");
  leg->AddEntry(sbn_caf_sbnd_osc,"SBNFit/CAFAna oscillated SBND", "l");
  leg->AddEntry(sbn_val_sbnd_osc,"SBNFit/VALOR oscillated SBND", "l");
 
  // Draw
  val_caf_sbnd_osc->GetYaxis()->SetRangeUser(0.993,1.007);
  val_caf_sbnd_osc->Draw("hist"); 
  sbn_caf_sbnd_osc->Draw("hist same");
  sbn_val_sbnd_osc->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("caf_val_sbn_osc_single_ratios_sbnd_dmsq-2_sinsqmumu-3e-3.root");
  c->SaveAs("caf_val_sbn_osc_single_ratios_sbnd_dmsq-2_sinsqmumu-3e-3.png");
  c->Clear();
  leg->Clear();

  // uBooNE VALOR and CAFAna single ratios
  leg->AddEntry(val_caf_uboone_osc,"VALOR/CAFAna oscillated #muBooNE", "l");
  leg->AddEntry(sbn_caf_uboone_osc,"SBNFit/CAFAna oscillated #muBooNE", "l");
  leg->AddEntry(sbn_val_uboone_osc,"SBNFit/VALOR oscillated #muBooNE", "l");
 
  // Draw
  val_caf_uboone_osc->GetYaxis()->SetRangeUser(0.993,1.007);
  val_caf_uboone_osc->Draw("hist"); 
  sbn_caf_uboone_osc->Draw("hist same");
  sbn_val_uboone_osc->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("caf_val_sbn_osc_single_ratios_uboone_dmsq-2_sinsqmumu-3e-3.root");
  c->SaveAs("caf_val_sbn_osc_single_ratios_uboone_dmsq-2_sinsqmumu-3e-3.png");
  c->Clear();
  leg->Clear();

  // ICARUS VALOR and CAFAna single ratios
  leg->AddEntry(val_caf_icarus_osc,"VALOR/CAFAna oscillated ICARUS", "l");
  leg->AddEntry(sbn_caf_icarus_osc,"SBNFit/CAFAna oscillated ICARUS", "l");
  leg->AddEntry(sbn_val_icarus_osc,"SBNFit/VALOR oscillated ICARUS", "l");
 
  // Draw
  val_caf_icarus_osc->GetYaxis()->SetRangeUser(0.993,1.007);
  val_caf_icarus_osc->Draw("hist"); 
  sbn_caf_icarus_osc->Draw("hist same");
  sbn_val_icarus_osc->Draw("hist same");
  leg->Draw("same");
  
  // Add label to colour legend
  c->SaveAs("caf_val_sbn_osc_single_ratios_icarus_dmsq-2_sinsqmumu-3e-3.root");
  c->SaveAs("caf_val_sbn_osc_single_ratios_icarus_dmsq-2_sinsqmumu-3e-3.png");
  c->Clear();
  leg->Clear();

}
