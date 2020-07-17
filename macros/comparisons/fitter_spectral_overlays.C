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
void fitter_spectral_overlays(const std::string &dmsq, const std::string &sinsq) {

  TFile *f_val_osc   = new TFile(("/sbnd/app/users/rsjones/VALOR/VALOR-SBN/pdfs/sbn/raw_files/VALOR_dmsq_"+dmsq+"_sinsq2thmumu_"+sinsq+"_osc_breakdown_hists.root").c_str(),"read");
  TFile *f_val_unosc = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-SBN/pdfs/sbn/raw_files/VALOR_unosc_breakdown_hists.root","read");
  TFile *f_sbn_osc   = new TFile(("/sbnd/app/users/rsjones/VALOR/VALOR-SBN/pdfs/sbn/raw_files/SBNfit_sinsq_"+sinsq+"_dmsq_"+dmsq+".SBNspec.root").c_str(),"read");
  TFile *f_sbn_unosc = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-SBN/pdfs/sbn/raw_files/SBNfit_CV.SBNspec.root","read");
  TFile *f_caf       = new TFile(("/sbnd/app/users/rsjones/VALOR/VALOR-SBN/pdfs/sbn/raw_files/CAFAna_dmsq_"+dmsq+"_ss2thmm_"+sinsq+".root").c_str(),"read");

  // Get the relevant histograms
  // VALOR
  TH1D *val_sbnd_osc     = static_cast<TH1D*>(f_val_osc->Get("sbn_nd_total"));
  TH1D *val_sbnd_unosc   = static_cast<TH1D*>(f_val_unosc->Get("sbn_nd_total"));
  TH1D *val_uboone_osc   = static_cast<TH1D*>(f_val_osc->Get("sbn_uboone_total"));
  TH1D *val_uboone_unosc = static_cast<TH1D*>(f_val_unosc->Get("sbn_uboone_total"));
  TH1D *val_icarus_osc   = static_cast<TH1D*>(f_val_osc->Get("sbn_icarus_total"));
  TH1D *val_icarus_unosc = static_cast<TH1D*>(f_val_unosc->Get("sbn_icarus_total"));


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

  // Now format the histograms
  for(unsigned int i = 0; i < sbnfit.size(); ++i){

    cafana[i]->SetLineColor(kOrange+1);
    sbnfit[i]->SetLineColor(kAzure+7);
    valor [i]->SetLineColor(kPink+5);

    cafana[i]->SetLineWidth(2);
    sbnfit[i]->SetLineWidth(2);
    valor [i]->SetLineWidth(2);

    cafana[i]->SetLineStyle(2);
    sbnfit[i]->SetLineStyle(5);
    valor [i]->SetLineStyle(8);
  
    // Always draw CAFAna first
    cafana[i]->SetStats(0);
    cafana[i]->GetXaxis()->SetTitle("E_{Reco} [GeV]");
    cafana[i]->GetYaxis()->SetTitle("Event rate / 1 GeV");
    cafana[i]->GetXaxis()->SetTitleFont(132);
    cafana[i]->GetYaxis()->SetTitleFont(132);
    cafana[i]->GetXaxis()->SetLabelFont(132);
    cafana[i]->GetYaxis()->SetLabelFont(132);
    cafana[i]->GetXaxis()->SetTitleSize(0.035);
    cafana[i]->GetYaxis()->SetTitleSize(0.035);
    cafana[i]->GetXaxis()->SetLabelSize(0.03);
    cafana[i]->GetYaxis()->SetLabelSize(0.03);
    cafana[i]->GetXaxis()->SetTitleOffset(1.2);
    cafana[i]->GetYaxis()->SetTitleOffset(1.2);
    cafana[i]->GetXaxis()->SetMaxDigits(3);
    cafana[i]->GetYaxis()->SetMaxDigits(3);
  }

  TCanvas *c1 = new TCanvas("c1","c1",20,20,900,900);
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

  // Oscillated
  // SBND
  leg->AddEntry(caf_sbnd_osc,"CAFAna SBND", "l");
  leg->AddEntry(sbn_sbnd_osc,"SBNFit SBND", "l");
  leg->AddEntry(val_sbnd_osc,"VALOR SBND", "l");
 
  // Draw
  caf_sbnd_osc->Draw();
  sbn_sbnd_osc->Draw("same");
  val_sbnd_osc->Draw("same"); 
  leg->Draw("same");
  
  // Add label to colour legend
  c1->SaveAs(("fitter_overlays_sbnd_dmsq-"+dmsq+"_sinsqmumu-"+sinsq+".root").c_str());
  c1->SaveAs(("fitter_overlays_sbnd_dmsq-"+dmsq+"_sinsqmumu-"+sinsq+".png").c_str());
  c1->Clear();
  leg->Clear();

  // MicroBooNE
  leg->AddEntry(caf_uboone_osc,"CAFAna #muBooNE", "l");
  leg->AddEntry(sbn_uboone_osc,"SBNFit #muBooNE", "l");
  leg->AddEntry(val_uboone_osc,"VALOR #muBooNE", "l");
 
  // Draw
  caf_uboone_osc->Draw();
  sbn_uboone_osc->Draw("same");
  val_uboone_osc->Draw("same"); 
  leg->Draw("same");
  
  // Add label to colour legend
  c1->SaveAs(("fitter_overlays_uboone_dmsq-"+dmsq+"_sinsqmumu-"+sinsq+".root").c_str());
  c1->SaveAs(("fitter_overlays_uboone_dmsq-"+dmsq+"_sinsqmumu-"+sinsq+".png").c_str());
  c1->Clear();
  leg->Clear();

  // ICARUS
  leg->AddEntry(caf_icarus_osc,"CAFAna ICARUS", "l");
  leg->AddEntry(sbn_icarus_osc,"SBNFit ICARUS", "l");
  leg->AddEntry(val_icarus_osc,"VALOR ICARUS", "l");
 
  // Draw
  caf_icarus_osc->Draw();
  sbn_icarus_osc->Draw("same");
  val_icarus_osc->Draw("same"); 
  leg->Draw("same");
  
  // Add label to colour legend
  c1->SaveAs(("fitter_overlays_icarus_dmsq-"+dmsq+"_sinsqmumu-"+sinsq+".root").c_str());
  c1->SaveAs(("fitter_overlays_icarus_dmsq-"+dmsq+"_sinsqmumu-"+sinsq+".png").c_str());
  c1->Clear();
  leg->Clear();
  
  // Unoscillated
  // SBND
  leg->AddEntry(caf_sbnd_unosc,"CAFAna SBND", "l");
  leg->AddEntry(sbn_sbnd_unosc,"SBNFit SBND", "l");
  leg->AddEntry(val_sbnd_unosc,"VALOR SBND", "l");
 
  // Draw
  caf_sbnd_unosc->Draw();
  sbn_sbnd_unosc->Draw("same");
  val_sbnd_unosc->Draw("same"); 
  leg->Draw("same");
  
  // Add label to colour legend
  c1->SaveAs("fitter_overlays_sbnd_unoscillated.root");
  c1->SaveAs("fitter_overlays_sbnd_unoscillated.png");
  c1->Clear();
  leg->Clear();

  // MicroBooNE
  leg->AddEntry(caf_uboone_unosc,"CAFAna #muBooNE", "l");
  leg->AddEntry(sbn_uboone_unosc,"SBNFit #muBooNE", "l");
  leg->AddEntry(val_uboone_unosc,"VALOR #muBooNE", "l");
 
  // Draw
  caf_uboone_unosc->Draw();
  sbn_uboone_unosc->Draw("same");
  val_uboone_unosc->Draw("same"); 
  leg->Draw("same");
  
  // Add label to colour legend
  c1->SaveAs("fitter_overlays_uboone_unoscillated.root");
  c1->SaveAs("fitter_overlays_uboone_unoscillated.png");
  c1->Clear();
  leg->Clear();

  // ICARUS
  leg->AddEntry(caf_icarus_unosc,"CAFAna ICARUS", "l");
  leg->AddEntry(sbn_icarus_unosc,"SBNFit ICARUS", "l");
  leg->AddEntry(val_icarus_unosc,"VALOR ICARUS", "l");
 
  // Draw
  caf_icarus_unosc->Draw();
  sbn_icarus_unosc->Draw("same");
  val_icarus_unosc->Draw("same"); 
  leg->Draw("same");
  
  // Add label to colour legend
  c1->SaveAs("fitter_overlays_icarus_unoscillated.root");
  c1->SaveAs("fitter_overlays_icarus_unoscillated.png");
  c1->Clear();
  leg->Clear();
}
