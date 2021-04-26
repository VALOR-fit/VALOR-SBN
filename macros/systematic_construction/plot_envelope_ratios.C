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

void plot_envelope_ratios(
  const char *valor_tweak_files,
  const char *universe_tweak_files,
  const char *file_name = "output_file_name"
){

 // TFile * f_val = new TFile("/sbnd/app/users/tham/VALOR_master/VALOR-SBN/geniev3_syst/envelope_test/nd_tweak_flux_horncurrent.root","read");
 // TFile * f_uni = new TFile("/sbnd/app/users/tham/VALOR_master/VALOR-SBN/geniev3_syst/envelope_test/tweaks_universes_horncurrent.root","read");
  
 // std::string file_name = "horncurrent";

  TFile *f_val = new TFile(valor_tweak_files,"read");
  TFile *f_uni = new TFile(universe_tweak_files,"read");

  //std::string file_name = file_name;
  std::string location = "/sbnd/app/users/tham/VALOR_master/VALOR-SBN/geniev3_syst/envelope_test/";

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

  TH1D * h_uni_nom = static_cast<TH1D*>(f_uni->Get("env_sb_BNB_FHC_nueCCincl_nom"));
  TH1D * h_uni_p1  = static_cast<TH1D*>(f_uni->Get("env_sb_BNB_FHC_nueCCincl_p1"));
  TH1D * h_uni_m1  = static_cast<TH1D*>(f_uni->Get("env_sb_BNB_FHC_nueCCincl_m1"));
  std::cout << " Got universe histograms" << std::endl;
 
  TH1D * h_val_nom = static_cast<TH1D*>(f_val->Get("env_sb_BNB_FHC_nuelikeCChigh_nom"));
  TH1D * h_val_p1  = static_cast<TH1D*>(f_val->Get("env_sb_BNB_FHC_nuelikeCChigh_p1"));
  TH1D * h_val_m1  = static_cast<TH1D*>(f_val->Get("env_sb_BNB_FHC_nuelikeCChigh_m1"));
  std::cout << " Got VALOR histograms" << std::endl;
 
  
  // All ratios
  TH1D *h_p1_ratio_val = static_cast<TH1D*>(h_val_p1->Clone("h_p1_ratio_val"));
  TH1D *h_m1_ratio_val = static_cast<TH1D*>(h_val_m1->Clone("h_m1_ratio_val"));

  TH1D *h_p1_ratio_uni = static_cast<TH1D*>(h_uni_p1->Clone("h_p1_ratio_uni"));
  TH1D *h_m1_ratio_uni = static_cast<TH1D*>(h_uni_m1->Clone("h_m1_ratio_uni"));

  TH1D *h_nom_ratio    = static_cast<TH1D*>(h_val_nom->Clone("h_nom_ratio_nom"));

  h_nom_ratio->Divide(h_uni_nom);
  
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
  h_nom_ratio -> SetLineColor(kPink+5);
  h_nom_ratio -> SetLineStyle(1);
  h_nom_ratio -> SetLineWidth(2);
  h_nom_ratio -> SetMarkerStyle(0);

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

  TLatex *latex = new TLatex();
  latex->SetTextSize(0.04);

  // Nominal ratio
  h_nom_ratio->SetStats(0);
  h_nom_ratio->GetYaxis()->SetTitleOffset(1.3);
  h_nom_ratio->GetXaxis()->SetRangeUser(0.2,3);
  h_nom_ratio->GetYaxis()->SetRangeUser(0.,2.);
  h_nom_ratio->SetTitle("");
  h_nom_ratio->GetXaxis()->SetTitle("E_{#nu, Reco}");
  h_nom_ratio->GetYaxis()->SetTitle("Nominal event rate ratio, VALOR/Universes");
  h_nom_ratio->GetXaxis()->SetTitleFont(132);
  h_nom_ratio->GetYaxis()->SetTitleFont(132);
  h_nom_ratio->GetXaxis()->SetLabelFont(132);
  h_nom_ratio->GetYaxis()->SetLabelFont(132);
  h_nom_ratio->GetYaxis()->SetMaxDigits(3);
  h_nom_ratio-> Draw();

  latex->DrawLatex(0.3, 1.8, file_name);
  
  c->SaveAs((location+"universe_valor_nominal_ratios_"+file_name+".root").c_str());
  c->Clear();

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

  latex->DrawLatex(0.3, 1.4, file_name);

  c->SaveAs((location+"universe_valor_single_ratios_"+file_name+".root").c_str());
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

  latex->DrawLatex(0.3, 1.13, file_name);

  c->SaveAs((location+"universe_valor_double_ratios_"+file_name+".root").c_str());
  c->Clear();
  l->Clear();

  // Get bin content in +1sigma variation
  TFile f("new_scale.root","RECREATE");
  TVectorD scales(h_p1_ratio->GetNbinsX()-3);
  for(int ibin = 0; ibin < h_p1_ratio->GetNbinsX()-3; ++ibin){
    scales[ibin] = 1/static_cast<double>(h_p1_ratio->GetBinContent(ibin+2));
  }
  scales.Write("scales");
  f.Close();

}
