//
// This macro reads in envelopes produced by Prefit 
// and those produced directly from the universes to 
// compare between the two
//
// *********************************************************
//
// July 2020
// R.J.
//

void SetStyle(TH1D *h);

void plot_envelope_ratios_prefit_postfit(const char *prefit, const char *postfit, const char *output, const std::string &name_tag, const std::string &sample){

  TFile * f_pre  = new TFile(prefit,"read");
  TFile * f_post = new TFile(postfit,"read");
  
  std::string location(output);

  std::string tag = "";
  if(name_tag != "")
    tag = name_tag+"_";
  
  // 
  // All graphs
  //

  TH1D * h_post_nom = static_cast<TH1D*>(f_post->Get(("env_sb_BNB_FHC_"+sample+"_nom").c_str()));
  TH1D * h_post_p1  = static_cast<TH1D*>(f_post->Get(("env_sb_BNB_FHC_"+sample+"_p1").c_str()));
  TH1D * h_post_m1  = static_cast<TH1D*>(f_post->Get(("env_sb_BNB_FHC_"+sample+"_m1").c_str()));
  std::cout << " Got posfit histograms " << std::endl;
 
  TH1D * h_pre_nom = static_cast<TH1D*>(f_pre->Get(("env_sb_BNB_FHC_"+sample+"_nom").c_str()));
  TH1D * h_pre_p1  = static_cast<TH1D*>(f_pre->Get(("env_sb_BNB_FHC_"+sample+"_p1").c_str()));
  TH1D * h_pre_m1  = static_cast<TH1D*>(f_pre->Get(("env_sb_BNB_FHC_"+sample+"_m1").c_str()));
  std::cout << " Got prefit histograms" << std::endl;
 
  // Get the event rates and write them
  double pre_nom = h_pre_nom->Integral();
  double pre_p1  = h_pre_p1->Integral();
  double pre_m1  = h_pre_m1->Integral();
  double pre_pm1 = (pre_p1-pre_m1)/2.;
  double pre_frac_pm1 = pre_pm1/pre_nom;

  double post_nom = h_post_nom->Integral();
  double post_p1  = h_post_p1->Integral();
  double post_m1  = h_post_m1->Integral();
  double post_pm1 = (post_p1-post_m1)/2.;
  double post_frac_pm1 = post_pm1/post_nom;

  // Open stats file for writing
  ofstream of;
  std::string out = location+tag+"rates.txt";
  of.open(out.c_str(), ios::app);
  of << "==========================================" << std::endl;
  of << " Prefit Rates     " << std::endl;
  of << " Nominal       : " << std::setprecision(6) << pre_nom << std::endl;
  of << " +1sig         : " << std::setprecision(6) << pre_p1 << std::endl;
  of << " -1sig         : " << std::setprecision(6) << pre_m1 << std::endl;
  of << " +/-1sig error : " << std::setprecision(6) << pre_pm1 << std::endl;
  of << " +/-1sig error : " << std::setprecision(6) << pre_frac_pm1*100 << " %" << std::endl;
  of << "------------------------------------------" << std::endl;
  of << " Postfit Rates  " << std::endl;
  of << " Nominal       : " << std::setprecision(6) << post_nom << std::endl;
  of << " +1sig         : " << std::setprecision(6) << post_p1 << std::endl;
  of << " -1sig         : " << std::setprecision(6) << post_m1 << std::endl;
  of << " +/-1sig error : " << std::setprecision(6) << post_pm1 << std::endl;
  of << " +/-1sig error : " << std::setprecision(6) << post_frac_pm1*100 << " %" << std::endl;
  of << "------------------------------------------" << std::endl;
  of << " Comparison    " << std::endl;
  of << " Nominal       : " << std::setprecision(6) << abs(pre_nom-post_nom)/(0.5*(pre_nom+post_nom))*100 << " % " << std::endl;
  of << " +/-1sig error : " << std::setprecision(6) << abs(pre_pm1-post_pm1)/(0.5*(pre_nom+post_nom))*100 << " % " << std::endl;
  of << "==========================================" << std::endl;
  of.close();

  // All ratios
  TH1D *h_p1_ratio_pre = static_cast<TH1D*>(h_pre_p1->Clone("h_p1_ratio_pre"));
  TH1D *h_m1_ratio_pre = static_cast<TH1D*>(h_pre_m1->Clone("h_m1_ratio_pre"));

  TH1D *h_p1_ratio_post = static_cast<TH1D*>(h_post_p1->Clone("h_p1_ratio_post"));
  TH1D *h_m1_ratio_post = static_cast<TH1D*>(h_post_m1->Clone("h_m1_ratio_post"));

  TH1D *h_nom_ratio    = static_cast<TH1D*>(h_pre_nom->Clone("h_nom_ratio_nom"));

  h_nom_ratio->Divide(h_post_nom);
  
  h_p1_ratio_pre->Divide(h_pre_nom);
  h_m1_ratio_pre->Divide(h_pre_nom);

  h_p1_ratio_post->Divide(h_post_nom);
  h_m1_ratio_post->Divide(h_post_nom);

  // Double ratios
  TH1D *h_p1_ratio = static_cast<TH1D*>(h_p1_ratio_pre->Clone("h_p1_ratio"));
  TH1D *h_m1_ratio = static_cast<TH1D*>(h_m1_ratio_pre->Clone("h_m1_ratio"));

  h_p1_ratio->Divide(h_p1_ratio_post);
  h_m1_ratio->Divide(h_m1_ratio_post);

  // Formatting
  h_nom_ratio -> SetLineColor(kPink+5);
  h_nom_ratio -> SetLineStyle(1);
  h_nom_ratio -> SetLineWidth(2);
  h_nom_ratio -> SetMarkerStyle(0);

  h_p1_ratio_pre -> SetLineColor(kPink+5);
  h_p1_ratio_pre -> SetLineStyle(7);
  h_p1_ratio_pre -> SetLineWidth(2);
  h_p1_ratio_pre -> SetMarkerStyle(0);

  h_m1_ratio_pre -> SetLineColor(kPink+5);
  h_m1_ratio_pre -> SetLineStyle(5);
  h_m1_ratio_pre -> SetLineWidth(2);
  h_m1_ratio_pre -> SetMarkerStyle(0);

  h_p1_ratio_post -> SetLineColor(kOrange+1);
  h_p1_ratio_post -> SetLineStyle(5);
  h_p1_ratio_post -> SetLineWidth(2);
  h_p1_ratio_post -> SetMarkerStyle(0);

  h_m1_ratio_post -> SetLineColor(kOrange+1);
  h_m1_ratio_post -> SetLineStyle(7);
  h_m1_ratio_post -> SetLineWidth(2);
  h_m1_ratio_post -> SetMarkerStyle(0);

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
  h_nom_ratio->GetYaxis()->SetTitle("Nominal event rate ratio, Prefit/Postfit");
  SetStyle(h_nom_ratio);

  h_nom_ratio-> Draw();

  c->SaveAs((location+tag+"prefit_postfit_nominal_ratios.root").c_str());
  c->SaveAs((location+tag+"prefit_postfit_nominal_ratios.png").c_str());
  c->Clear();

  h_p1_ratio_pre->SetStats(0);
  h_p1_ratio_pre->GetYaxis()->SetTitleOffset(1.1);
  h_p1_ratio_pre->GetXaxis()->SetRangeUser(0.2,3);
  h_p1_ratio_pre->GetYaxis()->SetRangeUser(0.5,1.5);
  h_p1_ratio_pre->SetTitle("");
  h_p1_ratio_pre->GetXaxis()->SetTitle("Reconstructed neutrino energy [GeV]");
  h_p1_ratio_pre->GetYaxis()->SetTitle("Event rate ratio");
  SetStyle(h_p1_ratio_pre);

  h_p1_ratio_pre -> Draw();
  h_m1_ratio_pre -> Draw("same");
  h_p1_ratio_post -> Draw("same");
  h_m1_ratio_post -> Draw("same");
  
  TLegend * l = new TLegend(0.178,0.166,0.934,0.343);
  l->SetFillStyle(0);
  l->SetBorderSize(0);
  l->SetTextFont(132);
  l->AddEntry(h_p1_ratio_pre, "Prefit +1#sigma/nominal", "L");
  l->AddEntry(h_p1_ratio_post, "Postfit +1#sigma/nominal", "L");
  l->AddEntry(h_m1_ratio_pre, "Prefit -1#sigma/nominal", "L");
  l->AddEntry(h_m1_ratio_post, "Postfit -1#sigma/nominal", "L");
  l->Draw();

  c->SaveAs((location+tag+"prefit_postfit_single_ratios.root").c_str());
  c->SaveAs((location+tag+"prefit_postfit_single_ratios.png").c_str());
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
 
  l->AddEntry(h_p1_ratio, "(Prefit/Postfit)_{+1#sigma/nominal}", "L");
  l->AddEntry(h_m1_ratio, "(Prefit/Postfit)_{-1#sigma/nominal}", "L");
  l->Draw();

  c->SaveAs((location+tag+"prefit_postfit_double_ratios.root").c_str());
  c->SaveAs((location+tag+"prefit_postfit_double_ratios.png").c_str());
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
