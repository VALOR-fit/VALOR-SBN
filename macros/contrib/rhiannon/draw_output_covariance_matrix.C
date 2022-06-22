// Plots the output covariance matrix from the fit
// Lorena Escudero, March 2016

void draw_output_covariance_matrix(
    const char * input_file,
    const char * prefit_flux = "",
    const char * prefit_int = "",
    int nFlux = -1, // Number of flux bins
    int nFluxSplines = -1, // Number of flux spline bins
    int nInt  = -1, // Number of interaction bins
    int entry = 0)
{

  if(nFlux < 0 && nInt < 0){
    std::cerr << "Neither of the number of flux bins or the number of interaction bins have been specified properly, flux: " << nFlux << ", interaction: " << nInt << std::endl;
    std::exit(1);
  }

  // If we have not passed all initial systematic files, don't plot any
  bool plot_flux_prefit = true;
  if(prefit_flux!= NULL && prefit_flux[0] == '\0') {
    std::cout << " Prefit flux file not found at: " << prefit_flux << std::endl;
    plot_flux_prefit = false;
  }
  bool plot_int_prefit = true;
  if(prefit_int != NULL && prefit_int[0] == '\0') {
    std::cout << " Prefit interaction file not found at: " << prefit_int << std::endl;
    plot_int_prefit = false;
  }

  const int n_flux        = (nFlux < 0) ? 0 : nFlux;
  const int n_spline_flux = (nFluxSplines < 0) ? 0 : nFluxSplines;
  const int n_tot_flux    = n_flux*3. + n_spline_flux;
  const int n_int         = (nInt < 0) ? 0 : nInt;
  const int n_det         = 0;

  const int n_params = n_tot_flux+n_int+n_det;

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
  TH1D * error_spline_flux = new TH1D("h_spline_flux","",n_spline_flux, 0., n_spline_flux);
  TH1D * error_int         = new TH1D("h_int","",n_int, 0., n_int);

  TH2D * cov_hist              = new TH2D("h_cov",     "", n_params,0.,n_params,n_params,0,n_params);
  TH2D * cov_flux_hist         = new TH2D("h_flux_cov","", n_tot_flux,0.,n_tot_flux,n_tot_flux,0,n_tot_flux);
  TH2D * cov_int_hist          = new TH2D("h_int_cov", "", n_int,0.,n_int,n_int,0,n_int);

  for(int i=0; i<n_int; i++){
    double value_int = cov_vector(i+n_tot_flux);
    error_int->SetBinContent(i+1,value_int);
  }
  for(int i=0; i<n_flux; i++){
    double value_sbnd_flux   = cov_vector(i);
    double value_uboone_flux = cov_vector(i+n_flux);
    double value_icarus_flux = cov_vector(i+n_flux*2);
    double value_spline_flux = cov_vector(i+n_tot_flux);

    error_sbnd_flux->SetBinContent(i+1,value_sbnd_flux);
    error_uboone_flux->SetBinContent(i+n_flux+1,value_uboone_flux);
    error_icarus_flux->SetBinContent(i+(n_flux*2)+1,value_icarus_flux);
    error_spline_flux->SetBinContent(i+(n_tot_flux)+1,value_spline_flux);
  }
  for(int i=0; i<n_params; i++){
    for(int j=0; j<n_params; j++){
      double value = abs(cov(i,j));
      cov_hist->SetBinContent(i+1,j+1,value);
    }
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
  double int_min =  999;
  double int_max = -999;
  for(int i=0; i<n_int; i++){
    for(int j=0; j<n_int; j++){
      double value = abs(cov(n_tot_flux+i,n_tot_flux+j));
      if(int_min > value)
        int_min = value;
      if(int_max < value)
        int_max = value;
      cov_int_hist->SetBinContent(i+1,j+1,value);
    }
  }

  double all_min = std::min(flux_min, int_min);
  double all_max = std::max(flux_max, int_max);

  // Labels for bin groups and number of bins to skip before printing each label
  std::vector<std::string> bin_labels({"SBND Flux", "uBooNE Flux", "ICARUS Flux", "Spline flux", "Interaction"});
  std::vector<int> bin_skip({n_flux, n_flux, n_flux, n_spline_flux, n_int});

  // Raw covariance matrix
  TCanvas *canv = new TCanvas("canv","",900,800);
  canv->SetLeftMargin(0.17);
  canv->SetRightMargin(0.1);
  canv->SetBottomMargin(0.2);
  canv->SetTopMargin(0.01);

  cov.Draw("colz");
  canv->Print("raw_cov.root");
  canv->Clear();

  cov_hist->Draw("colz");
  unsigned int label_bin = floor(n_flux/2);
  unsigned int line_bin  = n_flux+1;
  for(unsigned int i = 0; i < bin_labels.size(); ++i){
    // Draw diving lines 
    TLine *lineV = new TLine(line_bin,0,line_bin,n_params);
    TLine *lineH = new TLine(0, line_bin, n_params, line_bin);
    lineV->SetLineColor(kWhite);
    lineH->SetLineColor(kWhite);
    lineV->SetLineStyle(7);
    lineH->SetLineStyle(7);
    lineV->Draw();
    lineH->Draw();

    cov_hist->GetXaxis()->SetBinLabel(label_bin,bin_labels.at(i).c_str());
    cov_hist->GetYaxis()->SetBinLabel(label_bin,bin_labels.at(i).c_str());
    if(i == bin_labels.size()-1) break;
    label_bin += (bin_skip.at(i)/2.+1)-floor(i/2);
    label_bin += (bin_skip.at(i+1)/2.+1)-floor(i/2);
    line_bin  += bin_skip.at(i+1);
  }
  cov_hist->GetXaxis()->LabelsOption("v");
  cov_hist->GetYaxis()->LabelsOption("h");
  cov_hist->GetZaxis()->SetMaxDigits(3);
  cov_hist->GetZaxis()->SetLabelSize(0.03);
  cov_hist->SetMinimum(all_min);
  cov_hist->SetMaximum(all_max);
  canv->Print("cov.root");
  canv->Clear();

  cov_flux_hist->Draw("colz");
  label_bin = floor(n_flux/2);
  line_bin  = n_flux;
  for(unsigned int i = 0; i < (bin_labels.size()-1); ++i){
    // Draw diving lines 
    TLine *lineV = new TLine(line_bin,0,line_bin,n_tot_flux);
    TLine *lineH = new TLine(0, line_bin, n_tot_flux, line_bin);
    lineV->SetLineColor(kWhite);
    lineH->SetLineColor(kWhite);
    lineV->SetLineStyle(7);
    lineH->SetLineStyle(7);
    lineV->Draw();
    lineH->Draw();

    cov_flux_hist->GetXaxis()->SetBinLabel(label_bin,bin_labels.at(i).c_str());
    cov_flux_hist->GetYaxis()->SetBinLabel(label_bin,bin_labels.at(i).c_str());
    label_bin += (bin_skip.at(i)/2.+1)-floor(i/2);
    label_bin += (bin_skip.at(i+1)/2.+1)-floor(i/2);
    line_bin  += bin_skip.at(i+1);
  }
  cov_flux_hist->GetXaxis()->LabelsOption("v");
  cov_flux_hist->GetYaxis()->LabelsOption("h");
  cov_flux_hist->GetZaxis()->SetMaxDigits(3);
  cov_flux_hist->GetZaxis()->SetLabelSize(0.03);
  cov_flux_hist->SetMinimum(flux_min);
  cov_flux_hist->SetMaximum(flux_max);
  canv->Print("flux_cov.root");
  canv->Clear();

  cov_int_hist->Draw("colz");
  label_bin = floor(n_int/2);
  cov_int_hist->GetXaxis()->SetBinLabel(label_bin,bin_labels.at(4).c_str());
  cov_int_hist->GetYaxis()->SetBinLabel(label_bin,bin_labels.at(4).c_str());
  cov_int_hist->GetXaxis()->LabelsOption("v");
  cov_int_hist->GetYaxis()->LabelsOption("h");
  cov_int_hist->GetZaxis()->SetMaxDigits(3);
  cov_int_hist->GetZaxis()->SetLabelSize(0.03);
  cov_int_hist->SetMinimum(int_min);
  cov_int_hist->SetMaximum(int_max);
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

  if(plot_int_prefit){
    TFile *ip = TFile::Open(prefit_int);
    std::cout << " Opened prefit int file " << std::endl;

    TMatrixD *p_int_cov  = (TMatrixD*)ip->Get("frac_cov");
    TMatrixD *p_int_corr = (TMatrixD*)ip->Get("corr");
    TMatrixD &int_cov = *p_int_cov;
    TMatrixD &int_corr = *p_int_corr;

    if(int_cov.GetNrows() == 0 || int_corr.GetNrows() == 0){
      std::cerr << " An initial interaction matrix is empty, giving up" << std::endl;
      exit(1);
    }

    TH2D * cov_int_prefit_hist   = new TH2D("h_int_prefit_cov","", n_int,0.,n_int,n_int,0,n_int);
    TH2D * corr_int_prefit_hist  = new TH2D("h_int_prefit_corr","", n_int,0.,n_int,n_int,0,n_int);

    double pre_int_min =  999;
    double pre_int_max = -999;
    for(int i=0; i<n_int; i++){
      for(int j=0; j<n_int; j++){
        double prefit_value      = abs(int_cov(i,j));
        double prefit_corr_value = int_corr(i,j);
        if(pre_int_min > prefit_value)
          pre_int_min = prefit_value;
        if(pre_int_max < prefit_value)
          pre_int_max = prefit_value;
        cov_int_prefit_hist->SetBinContent(i+1,j+1,prefit_value);
        corr_int_prefit_hist->SetBinContent(i+1,j+1,prefit_corr_value);
      }
    }

    label_bin = floor(n_int/2);
    cov_int_prefit_hist->GetXaxis()->SetBinLabel(label_bin,bin_labels[3].c_str());
    cov_int_prefit_hist->GetYaxis()->SetBinLabel(label_bin,bin_labels[3].c_str());
    corr_int_prefit_hist->GetXaxis()->SetBinLabel(label_bin,bin_labels[3].c_str());
    corr_int_prefit_hist->GetYaxis()->SetBinLabel(label_bin,bin_labels[3].c_str());

    cov_int_prefit_hist->Draw("colz");
    cov_int_prefit_hist->GetXaxis()->LabelsOption("h");
    cov_int_prefit_hist->GetYaxis()->LabelsOption("v");
    cov_int_prefit_hist->GetZaxis()->SetMaxDigits(3);
    cov_int_prefit_hist->GetZaxis()->SetLabelSize(0.03);
    cov_int_prefit_hist->SetMinimum(pre_int_min);
    cov_int_prefit_hist->SetMaximum(pre_int_max);
    canv->Print("int_prefit_cov.root");
    canv->Clear();

    int int_red_blue_palette = valor::util::CreateRedToBlueColorPalette(nshades);
    corr_int_prefit_hist->Draw("colz");
    corr_int_prefit_hist->GetXaxis()->LabelsOption("h");
    corr_int_prefit_hist->GetYaxis()->LabelsOption("v");
    corr_int_prefit_hist->SetContour(nshades);
    corr_int_prefit_hist->GetZaxis()->SetRangeUser(-1.,1.);
    corr_int_prefit_hist->GetZaxis()->SetMaxDigits(3);
    corr_int_prefit_hist->GetZaxis()->SetLabelSize(0.03);
    canv->Update();
    canv->Print("corr_int_prefit.root");
    canv->Clear();
  }
  delete canv;

}
