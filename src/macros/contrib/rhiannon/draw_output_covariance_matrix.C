// Plots the output covariance matrix from the fit
// Lorena Escudero, March 2016

void draw_output_covariance_matrix(
  const char * input_file,
  int entry = 0)
{
  const int n_tot_flux = 21*3;
  const int n_flux     = 21;
  const int n_int      = 19;
  const int n_det      = 0;
  
  const int n_params = n_tot_flux+n_int+n_det;
  
  TFile * tf = TFile::Open(input_file);
  
  valor::FitParamList *  best_fit_params = 0; // best-fit params

  TTree * tree = (TTree*)tf->Get("valor_dune_nd_ntp");
  tree->SetBranchAddress("best_fit_params", &best_fit_params);
  
  assert(tree->GetEntries()>entry);
  tree->GetEntry(entry);
  // Covariance matrix
  TMatrixD cov(*(best_fit_params->GetCovMatrix()));
  TVectorD cov_vector = valor::util::CovarianceMatrixToErrorVector(cov);
 
  // Global settings
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  TCanvas *errcanv = new TCanvas("errcanv","",600,800);
  errcanv->SetLeftMargin(0.2);
  errcanv->SetRightMargin(0.1);
  errcanv->SetBottomMargin(0.15);
  errcanv->SetTopMargin(0.05);

  // Covariance vector
  cov_vector.Draw();
  errcanv->Print("error_cov.root");
  errcanv->Clear();

  // Formatted covariance matrix
  TH1D * error_sbnd_flux   = new TH1D("h_sbnd_flux","",n_flux, 0., n_flux);
  TH1D * error_uboone_flux = new TH1D("h_uboone_flux","",n_flux, 0., n_flux);
  TH1D * error_icarus_flux = new TH1D("h_icarus_flux","",n_flux, 0., n_flux);
  TH1D * error_int         = new TH1D("h_int","",n_int, 0., n_int);

  TH2D * cov_hist      = new TH2D("h_cov",     "", n_params,0.,n_params,n_params,0,n_params);
  TH2D * cov_flux_hist = new TH2D("h_flux_cov","", n_tot_flux,0.,n_tot_flux,n_tot_flux,0,n_tot_flux);
  TH2D * cov_int_hist  = new TH2D("h_int_cov", "", n_int,0.,n_int,n_int,0,n_int);

  for(int i=0; i<n_int; i++){
    double value_sbnd_flux   = cov_vector(i);
    double value_uboone_flux = cov_vector(i+n_flux);
    double value_icarus_flux = cov_vector(i+n_flux*2);
    double value_int         = cov_vector(i+n_tot_flux);

    error_sbnd_flux->SetBinContent(i+1,value_sbnd_flux);
    error_uboone_flux->SetBinContent(i+1,value_uboone_flux);
    error_icarus_flux->SetBinContent(i+1,value_icarus_flux);
    error_int->SetBinContent(i+1,value_int);
  }
  for(int i=0; i<n_params; i++){
    for(int j=0; j<n_params; j++){
      double value = cov(i,j);
      cov_hist->SetBinContent(i+1,j+1,abs(value));
    }
  }
  for(int i=0; i<n_tot_flux; i++){
    for(int j=0; j<n_tot_flux; j++){
      double value = cov(i,j);
      cov_flux_hist->SetBinContent(i+1,j+1,abs(value));
    }
  }
  for(int i=0; i<n_int; i++){
    for(int j=0; j<n_int; j++){
      double value = cov(i,j);
      cov_int_hist->SetBinContent(i+1,j+1,value);
    }
  }

  std::vector<std::string> bin_labels({"SBND Flux", "uBooNE Flux", "ICARUS Flux", "Interaction"});

  TLegend *l_error = new TLegend(0.28,0.68,0.63,0.88);
  l_error->AddEntry(error_sbnd_flux,   "SBND Flux", "L");
  l_error->AddEntry(error_uboone_flux, "#muBooNE Flux", "L");
  l_error->AddEntry(error_icarus_flux, "ICARUS Flux", "L");
  l_error->AddEntry(error_int,         "Interaction", "L");
  l_error->SetBorderSize(0);
  l_error->SetFillStyle(0);
  l_error->SetTextFont(132);

  error_sbnd_flux->SetLineColor(kGreen-3);
  error_uboone_flux->SetLineColor(kBlue-3);
  error_icarus_flux->SetLineColor(kViolet-3);
  error_int->SetLineColor(kOrange-3);
  error_int->SetLineStyle(7);
  error_int->SetLineWidth(2);

  error_sbnd_flux->GetXaxis()->SetTitle("Energy bin number");
  error_sbnd_flux->GetYaxis()->SetTitle("Parameter value");
  error_sbnd_flux->GetYaxis()->SetRangeUser(0.028,0.11);
  error_sbnd_flux->Draw();
  error_uboone_flux->Draw("same");
  error_icarus_flux->Draw("same");
  error_int->Draw("same");
  l_error->Draw("same");

  errcanv->Print("errors.root");
  errcanv->Clear();

  TCanvas *canv = new TCanvas("canv","",750,750);
  canv->SetLeftMargin(0.2);
  canv->SetRightMargin(0.15);
  canv->SetBottomMargin(0.1);
  canv->SetTopMargin(0.1);
  
  // Raw covariance matrix
  cov.Draw("colz");
  canv->Print("raw_cov.root");
  canv->Clear();
  
  unsigned int label_bin = floor(n_flux/2);
  for(unsigned int i = 0; i < 4; ++i){
    cov_hist->GetXaxis()->SetBinLabel(label_bin,bin_labels[i].c_str());
    cov_hist->GetYaxis()->SetBinLabel(label_bin,bin_labels[i].c_str());
    label_bin += n_flux+1-floor(i/2);
  }
  cov_hist->GetXaxis()->LabelsOption("h");
  cov_hist->GetYaxis()->LabelsOption("v");
  cov_hist->GetZaxis()->SetMaxDigits(3);
//  cov_flux_hist->GetZaxis()->SetRangeUser(-0.1,0.1);
  cov_hist->Draw("colz");
  canv->Print("cov.root");
  canv->Clear();
  
  label_bin = floor(n_flux/2);
  for(unsigned int i = 0; i < 3; ++i){
    cov_flux_hist->GetXaxis()->SetBinLabel(label_bin,bin_labels[i].c_str());
    cov_flux_hist->GetYaxis()->SetBinLabel(label_bin,bin_labels[i].c_str());
    label_bin += 20-floor(i/2);
  }
  cov_flux_hist->GetXaxis()->LabelsOption("h");
  cov_flux_hist->GetYaxis()->LabelsOption("v");
  cov_flux_hist->GetZaxis()->SetMaxDigits(3);
//  cov_flux_hist->GetZaxis()->SetRangeUser(-0.1,0.1);
//  cov_flux_hist->SetMinimum(0.001);
//  cov_flux_hist->SetMaximum(0.01);
  cov_flux_hist->Draw("colz");
  canv->Print("flux_cov.root");
  canv->Clear();
  
  label_bin = floor(n_flux/2);
  for(unsigned int i = 3; i < 4; ++i){
    cov_int_hist->GetXaxis()->SetBinLabel(label_bin,bin_labels[i].c_str());
    cov_int_hist->GetYaxis()->SetBinLabel(label_bin,bin_labels[i].c_str());
  }
  cov_int_hist->GetXaxis()->LabelsOption("h");
  cov_int_hist->GetYaxis()->LabelsOption("v");
  cov_int_hist->GetZaxis()->SetMaxDigits(3);
//  cov_int_hist->GetZaxis()->SetRangeUser(0.001,0.01);
  cov_int_hist->Draw("colz");
  canv->Print("int_cov.root");
  canv->Clear();

  // Correlation matrix
  TMatrixD corr = valor::util::CovarianceMatrixToCorrelationMatrix(cov);
  
  TH2D * corr_hist = (TH2D*)cov_hist->Clone("corrhist");
  for(int i=0; i<n_params; i++){
    for(int j=0; j<n_params; j++){
      double value = corr(i,j);
      corr_hist->SetBinContent(i+1,j+1,value);
    }
  }

  /*
  std::vector<std::string> bin_labels({"SBND Flux", "uBooNE Flux", "ICARUS Flux", "Interaction"});
  unsigned int label_bin = floor(19/2);
  for(unsigned int i = 0; i < 4; ++i){
    corr_hist->GetXaxis()->SetBinLabel(label_bin,bin_labels[i].c_str());
    corr_hist->GetYaxis()->SetBinLabel(label_bin,bin_labels[i].c_str());
    label_bin += 20-floor(i/2);
  }
  corr_hist->GetXaxis()->LabelsOption("h");
  corr_hist->GetYaxis()->LabelsOption("v");
  corr_hist->GetZaxis()->SetRangeUser(-1.,1.);
  corr_hist->GetZaxis()->SetMaxDigits(3);
  */
  const int nshades = 200;
  int red_blue_palette = valor::util::CreateRedToBlueColorPalette(nshades);
  corr_hist->SetContour(nshades);
  corr_hist->GetZaxis()->SetRangeUser(-1.,1.);
  corr_hist->Draw("colz");
  canv->Update();
  canv->Print("corr.root");
  canv->Clear();

 
  delete canv;

}
