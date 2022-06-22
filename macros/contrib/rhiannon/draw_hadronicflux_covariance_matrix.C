// Plots the output covariance matrix from the fit
// Lorena Escudero, March 2016

void draw_hadronicflux_covariance_matrix(
    const char * input_file,
    const char * prefit_flux = "",
    int nFlux = -1, // Number of flux bins 
    int entry = 0)
{

  if(nFlux < 0){
    std::cerr << "Number of flux bins hasn't been specified properly: " << nFlux << std::endl;
    std::exit(1);
  }

  // If we have not passed all initial systematic files, don't plot any
  bool plot_flux_prefit = true;
  if(prefit_flux!= NULL && prefit_flux[0] == '\0') {
    std::cout << " Prefit flux file not found at: " << prefit_flux << std::endl;
    plot_flux_prefit = false;
  }
  
  const int n_tot_flux = (nFlux < 0) ? 0 : nFlux*3;
  const int n_flux     = (nFlux < 0) ? 0 : nFlux;
  const int n_params   = n_tot_flux;

  // Global settings
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  TFile * tf = TFile::Open(input_file);

  valor::FitParamList *  best_fit_params = 0; // best-fit params

  TTree * tree = (TTree*)tf->Get("valor_fit_ntp");
  tree->SetBranchAddress("best_fit_params", &best_fit_params);

  assert(tree->()>entry);
  tree->GetEntry(entry);

  // Covariance matrix
  TMatrixD cov(*(best_fit_params->GetCovMatrix()));
  TVectorD cov_vector = valor::util::CovarianceMatrixToErrorVector(cov);

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

  TH2D * cov_flux_hist         = new TH2D("h_flux_cov","", n_tot_flux,0.,n_tot_flux,n_tot_flux,0,n_tot_flux);

  for(int i=0; i<n_flux; i++){
    double value_sbnd_flux   = cov_vector(i);
    double value_uboone_flux = cov_vector(i+n_flux);
    double value_icarus_flux = cov_vector(i+n_flux*2);

    error_sbnd_flux->SetBinContent(i+1,value_sbnd_flux);
    error_uboone_flux->SetBinContent(i+n_flux+1,value_uboone_flux);
    error_icarus_flux->SetBinContent(i+(n_flux*2)+1,value_icarus_flux);
  }
  double flux_min =  999;
  double flux_max = -999;
  for(int i=0; i<n_tot_flux; i++){
    for(int j=0; j<n_tot_flux; j++){
      double value = abs(cov(i,j));
      if(flux_min > value)
        flux_min = value;
      if(flux_max < value)
        flux_max = value;
      cov_flux_hist->SetBinContent(i+1,j+1,value);
    }
  }

  std::vector<std::string> bin_labels({"SBND Flux", "uBooNE Flux", "ICARUS Flux"});

  TLegend *l_error = new TLegend(0.28,0.68,0.63,0.88);
  l_error->AddEntry(error_sbnd_flux,   "SBND Flux", "L");
  l_error->AddEntry(error_uboone_flux, "#muBooNE Flux", "L");
  l_error->AddEntry(error_icarus_flux, "ICARUS Flux", "L");
  l_error->SetBorderSize(0);
  l_error->SetFillStyle(0);
  l_error->SetTextFont(132);

  error_sbnd_flux->SetLineColor(kGreen-3);
  error_uboone_flux->SetLineColor(kBlue-3);
  error_icarus_flux->SetLineColor(kViolet-3);

  error_sbnd_flux->Draw();
  error_uboone_flux->Draw("same");
  error_icarus_flux->Draw("same");
  error_sbnd_flux->GetXaxis()->SetTitle("Energy bin number");
  error_sbnd_flux->GetYaxis()->SetTitle("Parameter value");
  //error_sbnd_flux->GetYaxis()->SetRangeUser(0.028,0.11);
  l_error->Draw("same");

  errcanv->Print("errors.root");
  errcanv->Clear();

  // Raw covariance matrix
  TCanvas *canv = new TCanvas("canv","",900,800);
  canv->SetLeftMargin(0.2);
  canv->SetRightMargin(0.15);
  canv->SetBottomMargin(0.1);
  canv->SetTopMargin(0.1);

  cov.Draw("colz");
  canv->Print("raw_cov.root");
  canv->Clear();

  cov_flux_hist->Draw("colz");
  int label_bin = floor(n_flux/2);
  for(unsigned int i = 0; i < 3; ++i){
    cov_flux_hist->GetXaxis()->SetBinLabel(label_bin,bin_labels[i].c_str());
    cov_flux_hist->GetYaxis()->SetBinLabel(label_bin,bin_labels[i].c_str());
    label_bin += (n_flux+1)-floor(i/2);
  }
  cov_flux_hist->GetXaxis()->LabelsOption("h");
  cov_flux_hist->GetYaxis()->LabelsOption("v");
  cov_flux_hist->GetZaxis()->SetMaxDigits(3);
  cov_flux_hist->GetZaxis()->SetLabelSize(0.03);
  cov_flux_hist->SetMinimum(flux_min);
  cov_flux_hist->SetMaximum(flux_max);
  canv->Print("flux_cov.root");
  canv->Clear();

  // Correlation matrix
  TMatrixD corr = valor::util::CovarianceMatrixToCorrelationMatrix(cov);

  TH2D * corr_hist = (TH2D*)cov_flux_hist->Clone("corrhist");
  for(int i=0; i<n_params; i++){
    for(int j=0; j<n_params; j++){
      double value = corr(i,j);
      corr_hist->SetBinContent(i+1,j+1,value);
    }
  }

  const int nshades = 200;
  int red_blue_palette = valor::util::CreateRedToBlueColorPalette(nshades);
  corr_hist->Draw("colz");
  corr_hist->SetContour(nshades);
  corr_hist->GetZaxis()->SetRangeUser(-1.,1.);
  corr_hist->GetZaxis()->SetMaxDigits(3);
  corr_hist->GetZaxis()->SetLabelSize(0.03);
  canv->Update();
  canv->Print("corr.root");
  canv->Clear();

  if(plot_flux_prefit) {
    TFile *fp = TFile::Open(prefit_flux);
    std::cout << " Opened prefit flux file " << std::endl;

    TMatrixD *p_flux_cov  = (TMatrixD*)fp->Get("frac_cov");
    TMatrixD *p_flux_corr = (TMatrixD*)fp->Get("corr");
    TMatrixD &flux_cov = *p_flux_cov;
    TMatrixD &flux_corr = *p_flux_corr;

    if(flux_cov.GetNrows() == 0 || flux_corr.GetNrows() == 0){
      std::cerr << " An initial flux matrix is empty, giving up" << std::endl;
      exit(1);
    }

    TH2D * cov_flux_prefit_hist  = new TH2D("h_flux_prefit_cov","", n_tot_flux,0.,n_tot_flux,n_tot_flux,0,n_tot_flux);
    TH2D * corr_flux_prefit_hist = new TH2D("h_flux_prefit_corr","", n_tot_flux,0.,n_tot_flux,n_tot_flux,0,n_tot_flux);

    double pre_flux_min =  999;
    double pre_flux_max = -999;
    for(int i=0; i<n_tot_flux; i++){
      for(int j=0; j<n_tot_flux; j++){
        double prefit_value      = abs(flux_cov(i,j));
        double prefit_corr_value = flux_corr(i,j);
        if(pre_flux_min > prefit_value)
          pre_flux_min = prefit_value;
        if(pre_flux_max < prefit_value)
          pre_flux_max = prefit_value;
        cov_flux_prefit_hist->SetBinContent(i+1,j+1,prefit_value);
        corr_flux_prefit_hist->SetBinContent(i+1,j+1,prefit_corr_value);
      }
    }

    label_bin = floor(n_flux/2);
    for(unsigned int i = 0; i < 3; ++i){
      cov_flux_prefit_hist->GetXaxis()->SetBinLabel(label_bin,bin_labels[i].c_str());
      cov_flux_prefit_hist->GetYaxis()->SetBinLabel(label_bin,bin_labels[i].c_str());
      corr_flux_prefit_hist->GetXaxis()->SetBinLabel(label_bin,bin_labels[i].c_str());
      corr_flux_prefit_hist->GetYaxis()->SetBinLabel(label_bin,bin_labels[i].c_str());
      label_bin += (n_flux+1)-floor(i/2);
    }

    cov_flux_prefit_hist->Draw("colz");
    cov_flux_prefit_hist->GetXaxis()->LabelsOption("h");
    cov_flux_prefit_hist->GetYaxis()->LabelsOption("v");
    cov_flux_prefit_hist->GetZaxis()->SetMaxDigits(3);
    cov_flux_prefit_hist->GetZaxis()->SetLabelSize(0.03);
    cov_flux_prefit_hist->SetMinimum(pre_flux_min);
    cov_flux_prefit_hist->SetMaximum(pre_flux_max);
    canv->Print("flux_prefit_cov.root");
    canv->Clear();

    int flux_red_blue_palette = valor::util::CreateRedToBlueColorPalette(nshades);
    corr_flux_prefit_hist->Draw("colz");
    corr_flux_prefit_hist->GetXaxis()->LabelsOption("h");
    corr_flux_prefit_hist->GetYaxis()->LabelsOption("v");
    corr_flux_prefit_hist->SetContour(nshades);
    corr_flux_prefit_hist->GetZaxis()->SetRangeUser(-1.,1.);
    corr_flux_prefit_hist->GetZaxis()->SetMaxDigits(3);
    corr_flux_prefit_hist->GetZaxis()->SetLabelSize(0.03);
    canv->Update();
    canv->Print("corr_flux_prefit.root");
    canv->Clear();
  }

  delete canv;

}
