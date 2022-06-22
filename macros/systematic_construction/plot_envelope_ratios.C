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

void SetStyle(TH1D *h);

void plot_envelope_ratios(const char *valor, const char *univ, const char *output, const std::string &name_tag, const std::string &sample){

  TFile * f_val = new TFile(valor,"read");
  TFile * f_uni = new TFile(univ,"read");
  
  std::string location(output);

  std::string tag = "";
  if(name_tag != "")
    tag = name_tag+"_";
  
  // 
  // All graphs
  //

  TH1D * h_uni_nom = static_cast<TH1D*>(f_uni->Get(("env_sb_BNB_FHC_"+sample+"_nom").c_str()));
  TH1D * h_uni_p1  = static_cast<TH1D*>(f_uni->Get(("env_sb_BNB_FHC_"+sample+"_p1").c_str()));
  TH1D * h_uni_m1  = static_cast<TH1D*>(f_uni->Get(("env_sb_BNB_FHC_"+sample+"_m1").c_str()));
  std::cout << " Got universe histograms " << std::endl;
 
  TH1D * h_val_nom = static_cast<TH1D*>(f_val->Get(("env_sb_BNB_FHC_"+sample+"_nom").c_str()));
  TH1D * h_val_p1  = static_cast<TH1D*>(f_val->Get(("env_sb_BNB_FHC_"+sample+"_p1").c_str()));
  TH1D * h_val_m1  = static_cast<TH1D*>(f_val->Get(("env_sb_BNB_FHC_"+sample+"_m1").c_str()));
  std::cout << " Got VALOR histograms" << std::endl;
 
  // Get the event rates and write them
  double valor_nom = h_val_nom->Integral();
  double valor_p1  = h_val_p1->Integral();
  double valor_m1  = h_val_m1->Integral();
  double valor_pm1 = (valor_p1-valor_m1)/2.;
  double valor_frac_pm1 = valor_pm1/valor_nom;

  double univ_nom = h_uni_nom->Integral();
  double univ_p1  = h_uni_p1->Integral();
  double univ_m1  = h_uni_m1->Integral();
  double univ_pm1 = (univ_p1-univ_m1)/2.;
  double univ_frac_pm1 = univ_pm1/univ_nom;

  // Open stats file for writing
  ofstream of;
  std::string out = location+tag+"rates.txt";
  of.open(out.c_str(), ios::app);
  of << "==========================================" << std::endl;
  of << " VALOR Rates     " << std::endl;
  of << " Nominal       : " << std::setprecision(6) << valor_nom << std::endl;
  of << " +1sig         : " << std::setprecision(6) << valor_p1 << std::endl;
  of << " -1sig         : " << std::setprecision(6) << valor_m1 << std::endl;
  of << " +/-1sig error : " << std::setprecision(6) << valor_pm1 << std::endl;
  of << " +/-1sig error : " << std::setprecision(6) << valor_frac_pm1*100 << " %" << std::endl;
  of << "------------------------------------------" << std::endl;
  of << " Universe Rates  " << std::endl;
  of << " Nominal       : " << std::setprecision(6) << univ_nom << std::endl;
  of << " +1sig         : " << std::setprecision(6) << univ_p1 << std::endl;
  of << " -1sig         : " << std::setprecision(6) << univ_m1 << std::endl;
  of << " +/-1sig error : " << std::setprecision(6) << univ_pm1 << std::endl;
  of << " +/-1sig error : " << std::setprecision(6) << univ_frac_pm1*100 << " %" << std::endl;
  of << "------------------------------------------" << std::endl;
  of << " Comparison    " << std::endl;
  of << " Nominal       : " << std::setprecision(6) << abs(valor_nom-univ_nom)/(0.5*(valor_nom+univ_nom))*100 << " % " << std::endl;
  of << " +/-1sig error : " << std::setprecision(6) << abs(valor_pm1-univ_pm1)/(0.5*(valor_nom+univ_nom))*100 << " % " << std::endl;
  of << "==========================================" << std::endl;
  of.close();

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
  TCanvas * c = new TCanvas("c","",20,20,900,900);
  c->SetLeftMargin  (0.126);
  c->SetRightMargin (0.015);
  c->SetBottomMargin(0.123);
  c->SetTopMargin   (0.018);
  
  // Nominal ratio
  h_nom_ratio->SetStats(0);
  h_nom_ratio->GetYaxis()->SetTitleOffset(1.1);
  h_nom_ratio->GetXaxis()->SetRangeUser(0.2,3);
  h_nom_ratio->GetYaxis()->SetRangeUser(0.,2.);
  h_nom_ratio->SetTitle("");
  h_nom_ratio->GetXaxis()->SetTitle("Reconstructed neutrino energy [GeV]");
  h_nom_ratio->GetYaxis()->SetTitle("Nominal event rate ratio, VALOR/Universes");
  SetStyle(h_nom_ratio);

  h_nom_ratio-> Draw();

  c->SaveAs((location+tag+"universe_valor_nominal_ratios.root").c_str());
  c->Clear();

  h_p1_ratio_val->SetStats(0);
  h_p1_ratio_val->GetYaxis()->SetTitleOffset(1.1);
  h_p1_ratio_val->GetXaxis()->SetRangeUser(0.2,3);
  h_p1_ratio_val->GetYaxis()->SetRangeUser(0.5,1.5);
  h_p1_ratio_val->SetTitle("");
  h_p1_ratio_val->GetXaxis()->SetTitle("Reconstructed neutrino energy [GeV]");
  h_p1_ratio_val->GetYaxis()->SetTitle("Event rate ratio");
  SetStyle(h_p1_ratio_val);

  h_p1_ratio_val -> Draw();
  h_m1_ratio_val -> Draw("same");
  h_p1_ratio_uni -> Draw("same");
  h_m1_ratio_uni -> Draw("same");
  
  TLegend * l = new TLegend(0.178,0.166,0.934,0.343);
  l->SetFillStyle(0);
  l->SetBorderSize(0);
  l->SetTextFont(132);
  l->AddEntry(h_p1_ratio_val, "Splines +1#sigma/nominal", "L");
  l->AddEntry(h_p1_ratio_uni, "Universes +1#sigma/nominal", "L");
  l->AddEntry(h_m1_ratio_val, "Splines -1#sigma/nominal", "L");
  l->AddEntry(h_m1_ratio_uni, "Universes -1#sigma/nominal", "L");
  l->Draw();

  c->SaveAs((location+tag+"universe_valor_single_ratios.root").c_str());
  c->Clear();
  l->Clear();

  h_p1_ratio->SetStats(0);
  h_p1_ratio->GetYaxis()->SetTitleOffset(1.1);
  h_p1_ratio->GetXaxis()->SetRangeUser(0.2,3);
  h_p1_ratio->GetYaxis()->SetRangeUser(0.85,1.15);
  h_p1_ratio->SetTitle("");
  h_p1_ratio->GetXaxis()->SetTitle("Reconstructed neutrino energy [GeV]");
  h_p1_ratio->GetYaxis()->SetTitle("Event rate ratio");
  SetStyle(h_p1_ratio);
  h_p1_ratio -> Draw();
  h_m1_ratio -> Draw("same");
 
  l->AddEntry(h_p1_ratio, "(Splines/Universes)_{+1#sigma/nominal}", "L");
  l->AddEntry(h_m1_ratio, "(Splines/Universes)_{-1#sigma/nominal}", "L");
  l->Draw();

  c->SaveAs((location+tag+"universe_valor_double_ratios.root").c_str());
  c->Clear();
  l->Clear();

  // Get bin content in +1sigma variation
  TFile f((location+tag+"scale.root").c_str(),"RECREATE");
  TVectorD scales(h_p1_ratio->GetNbinsX()-3);
  for(int ibin = 0; ibin < h_p1_ratio->GetNbinsX()-3; ++ibin){
    scales[ibin] = 1/static_cast<double>(h_p1_ratio->GetBinContent(ibin+2));
  }
  scales.Write("scales");
  f.Close();

}
void SetStyle(TH1D *h){
  h->GetXaxis()->SetTitleFont(132);
  h->GetYaxis()->SetTitleFont(132);
  h->GetXaxis()->SetLabelFont(132);
  h->GetYaxis()->SetLabelFont(132);
  h->GetYaxis()->SetMaxDigits(3);
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetLabelSize(0.05);
  h->GetYaxis()->SetLabelSize(0.05);
}
