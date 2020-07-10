//
// This macro reads in envelopes produced by VALOR 
// and those produced directly from the universes to 
// compare between the two
//
// *********************************************************
//
// July 2020
// R.J.
//

{

  TFile * f_uni = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/response/systematic_validation/02c1/xsec_splines/tweaks_int.root","read");
  TFile * f_val = new TFile("/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/response/systematic_validation/02c1/xsec_splines/tweaks_valor_xsec_splines_large_prefit.root","read");
  
  std::string location = "/sbnd/app/users/rsjones/VALOR/VALOR-DUNE-LBL/response/systematic_validation/02c1/xsec_splines/";
  
  // 
  // Global style settings
  //
  gStyle->SetTitleSize(0.04,"X");
  gStyle->SetTitleSize(0.04,"Y");
  gStyle->SetLabelSize(0.03,"X");
  gStyle->SetLabelSize(0.03,"Y");

  // 
  // All graphs
  //

  TH1D * h_uni_nom = static_cast<TH1D*>(f_uni->Get("env_sb_BNB_FHC_numulikeCChigh_nom"));
  TH1D * h_uni_p1  = static_cast<TH1D*>(f_uni->Get("env_sb_BNB_FHC_numulikeCChigh_p1"));
  TH1D * h_uni_m1  = static_cast<TH1D*>(f_uni->Get("env_sb_BNB_FHC_numulikeCChigh_m1"));
 
  TH1D * h_val_nom = static_cast<TH1D*>(f_val->Get("env_sb_BNB_FHC_numulikeCChigh_nom"));
  TH1D * h_val_p1  = static_cast<TH1D*>(f_val->Get("env_sb_BNB_FHC_numulikeCChigh_p1"));
  TH1D * h_val_m1  = static_cast<TH1D*>(f_val->Get("env_sb_BNB_FHC_numulikeCChigh_m1"));
 
  std::cout << " N bins valor : " << h_val_nom->GetNbinsX() << " uni: " << h_uni_nom->GetNbinsX() << std::endl;

  // All ratios
  TH1D *h_p1_ratio_val = static_cast<TH1D*>(h_val_p1->Clone("h_p1_ratio_val"));
  TH1D *h_m1_ratio_val = static_cast<TH1D*>(h_val_m1->Clone("h_m1_ratio_val"));

  TH1D *h_p1_ratio_uni = static_cast<TH1D*>(h_uni_p1->Clone("h_p1_ratio_uni"));
  TH1D *h_m1_ratio_uni = static_cast<TH1D*>(h_uni_m1->Clone("h_m1_ratio_uni"));

  h_p1_ratio_val->Divide(h_val_nom);
  h_m1_ratio_val->Divide(h_val_nom);

  h_p1_ratio_uni->Divide(h_uni_nom);
  h_m1_ratio_uni->Divide(h_uni_nom);

  // Double ratios
  TH1D *h_p1_ratio = static_cast<TH1D*>(h_p1_ratio_val->Clone("h_p1_ratio"));
  TH1D *h_m1_ratio = static_cast<TH1D*>(h_m1_ratio_val->Clone("h_m1_ratio"));

  h_p1_ratio->Divide(h_p1_ratio_uni);
  h_m1_ratio->Divide(h_m1_ratio_uni);

  // Formatting
  h_p1_ratio_val -> SetLineColor(kPink+5);
  h_p1_ratio_val -> SetLineStyle(7);
  h_p1_ratio_val -> SetLineWidth(2);
  h_p1_ratio_val -> SetMarkerStyle(0);

  h_m1_ratio_val -> SetLineColor(kPink+5);
  h_m1_ratio_val -> SetLineStyle(5);
  h_m1_ratio_val -> SetLineWidth(2);
  h_m1_ratio_val -> SetMarkerStyle(0);

  h_p1_ratio_uni -> SetLineColor(kOrange+1);
  h_p1_ratio_uni -> SetLineStyle(5);
  h_p1_ratio_uni -> SetLineWidth(2);
  h_p1_ratio_uni -> SetMarkerStyle(0);

  h_m1_ratio_uni -> SetLineColor(kOrange+1);
  h_m1_ratio_uni -> SetLineStyle(7);
  h_m1_ratio_uni -> SetLineWidth(2);
  h_m1_ratio_uni -> SetMarkerStyle(0);

  h_p1_ratio     -> SetLineColor(kPink+5);
  h_p1_ratio     -> SetLineStyle(7);
  h_p1_ratio     -> SetLineWidth(2);
  h_p1_ratio     -> SetMarkerStyle(0);

  h_m1_ratio     -> SetLineColor(kOrange+1);
  h_m1_ratio     -> SetLineStyle(5);
  h_m1_ratio     -> SetLineWidth(2);
  h_m1_ratio     -> SetMarkerStyle(0);

  // 
  // No stat all external all fitters 
  //
  TCanvas * c = new TCanvas("c","",20,20,700,900);
  c->SetTopMargin(0.044);
  c->SetBottomMargin(0.1);
  c->SetLeftMargin(0.1);
  c->SetRightMargin(0.044);
  c->Draw();

  h_p1_ratio_val->SetStats(0);
  h_p1_ratio_val->GetYaxis()->SetTitleOffset(1.3);
  h_p1_ratio_val->GetXaxis()->SetRangeUser(0.2,3);
  h_p1_ratio_val->GetYaxis()->SetRangeUser(0.5,1.5);
  h_p1_ratio_val->SetTitle("");
  h_p1_ratio_val->GetXaxis()->SetTitle("E_{#nu, Reco}");
  h_p1_ratio_val->GetYaxis()->SetTitle("Event rate ratio");
  h_p1_ratio_val->GetXaxis()->SetTitleFont(132);
  h_p1_ratio_val->GetYaxis()->SetTitleFont(132);
  h_p1_ratio_val->GetXaxis()->SetLabelFont(132);
  h_p1_ratio_val->GetYaxis()->SetLabelFont(132);
  h_p1_ratio_val->GetYaxis()->SetMaxDigits(3);

  h_p1_ratio_val -> Draw();
  h_m1_ratio_val -> Draw("same");
  h_p1_ratio_uni -> Draw("same");
  h_m1_ratio_uni -> Draw("same");
  
  TLegend * l = new TLegend(0.122,0.137,0.878,0.313);
  l->SetFillStyle(0);
  l->SetBorderSize(0);
  l->SetTextFont(132);
  l->AddEntry(h_p1_ratio_val, "VALOR +1#sigma/nominal", "L");
  l->AddEntry(h_p1_ratio_uni, "Universes +1#sigma/nominal", "L");
  l->AddEntry(h_m1_ratio_val, "VALOR -1#sigma/nominal", "L");
  l->AddEntry(h_m1_ratio_uni, "Universes -1#sigma/nominal", "L");
  l->Draw();

  c->SaveAs((location+"xsec_large_universe_valor_single_ratios.root").c_str());
  c->Clear();
  l->Clear();

  h_p1_ratio->SetStats(0);
  h_p1_ratio->GetYaxis()->SetTitleOffset(1.3);
  h_p1_ratio->GetXaxis()->SetRangeUser(0.2,3);
  h_p1_ratio->GetYaxis()->SetRangeUser(0.85,1.15);
  h_p1_ratio->SetTitle("");
  h_p1_ratio->GetXaxis()->SetTitle("E_{#nu, Reco}");
  h_p1_ratio->GetYaxis()->SetTitle("Event rate ratio");
  h_p1_ratio->GetXaxis()->SetTitleFont(132);
  h_p1_ratio->GetYaxis()->SetTitleFont(132);
  h_p1_ratio->GetXaxis()->SetLabelFont(132);
  h_p1_ratio->GetYaxis()->SetLabelFont(132);
  h_p1_ratio->GetYaxis()->SetMaxDigits(3);

  h_p1_ratio -> Draw();
  h_m1_ratio -> Draw("same");
  
  l->AddEntry(h_p1_ratio, "(VALOR/Universes)_{+1#sigma/nominal}", "L");
  l->AddEntry(h_m1_ratio, "(VALOR/Universes)_{-1#sigma/nominal}", "L");
  l->Draw();

  c->SaveAs((location+"xsec_large_universe_valor_double_ratios.root").c_str());
  c->Clear();
  l->Clear();
}
