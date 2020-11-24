// Plots the output covariance matrix from the fit
// Lorena Escudero, March 2016

std::vector<std::string> params_tex =
{
  "QE M_{A}",
  "CC Res_{A}",
  "NonRes R^{#nu n CC 1 #pi}",
  "NonRes R^{#nu p NC 2 #pi}",
  "DIS Bth",
  "IntraNuke PI Abs",
  "IntraNuke N Inel",
  "NC Res_{V}",
  "Skin Effect",
  "Nucleon QE #sigma",
};
std::vector<std::string> params =
{
  "qema",
  "ccresAxial",
  "NonResRvnCC1pi",
  "NonResRvpNC2pi",
  "DISBth",
  "IntraNukePIabs",
  "IntraNukeNinel",
  "ncresVector",
  "expskin",
  "nucleonqexsec",
};

std::vector<unsigned int> pal = 
{
  397,
  595,
  633,
  825,
  618,
  802,
  859,
  835,
  903,
  886,
  611,
};

void draw_pull_studies_matrices(
    const char * input_file,       // Output of the fit
    const std::string &output_tag, // Tag for the output files
    const int &nentries=1          // Number of matrices to make, default 1
    )
{
  using namespace valor;

  TFile * tf = TFile::Open(input_file);
  std::cout << " Opened input file: " << input_file << std::endl;
  tf->ls();

  valor::FitParamList *  best_fit_params = nullptr; // best-fit params

  TTree * tree = static_cast<TTree*>(tf->Get("valor_fit_ntp"));
  tree->SetBranchAddress("best_fit_params", &best_fit_params);

  assert(nentries < tree->GetEntries());
  int n = nentries;
  if(nentries > 50){
    std::cout << " Are you sure you want to draw more than 50 individual plots? " << std::endl;
    std::cout << " If not, reduce nentries." << std::endl;
    std::cout << " Please re-enter the number of histograms you'd like to plot: ";
    std::cin >> n;
    if(n >= nentries)
      std::cout << " You're sticking with it, fair enough!" << std::endl;
    else
      std::cout << " You've chosen to reduce the number, probably a good idea" << std::endl;
  }

  std::string tag = output_tag;
  if(output_tag != "")
    tag = output_tag+"_";

  TFile *f_out = new TFile((tag+"postfit_matrices.root").c_str(),"RECREATE");

  for(int m = 0; m < n; ++m){
    tree->GetEntry(m);

    //--------------------------------------------------------------------------------
    //                             Covariance matrix
    //--------------------------------------------------------------------------------
    
    // Covariance matrix
    TMatrixD cov(*(best_fit_params->GetCovMatrix()));
    int n_params = cov.GetNrows();

    // Global settings
    gStyle->SetOptStat(0);
    gStyle->SetPalette(kBird);
    gStyle->SetOptTitle(0);
    gStyle->SetTextFont(132);
    gStyle->SetTextAlign(22);
    gStyle->SetTextSize(0.001);

    TLatex latex;
    latex.SetTextAlign(11);
    latex.SetTextSize(0.035);
    latex.SetTextColor(611);

    const int nshades = 200;

    // Formatted covariance matrix
    TH2D * cov_hist     = new TH2D(("h_cov_"+std::to_string(m)).c_str(),    "", n_params,0.,n_params,n_params,0,n_params);
    TH2D * abs_cov_hist = new TH2D(("h_abs_cov_"+std::to_string(m)).c_str(),"", n_params,0.,n_params,n_params,0,n_params);

    for(int i=0; i<n_params; i++){
      for(int j=0; j<n_params; j++){
        double value = cov(i,j);
        cov_hist->SetBinContent(i+1,j+1,value);
        abs_cov_hist->SetBinContent(i+1,j+1,abs(value));
      }
      std::string label = "#color["+std::to_string(pal.at(i))+"]{"+params_tex.at(i)+"}";

      cov_hist->GetXaxis()->SetBinLabel(i+1,label.c_str());
      cov_hist->GetYaxis()->SetBinLabel(i+1,label.c_str());
      abs_cov_hist->GetXaxis()->SetBinLabel(i+1,label.c_str());
      abs_cov_hist->GetYaxis()->SetBinLabel(i+1,label.c_str());
    }

    TCanvas *canv = new TCanvas(("canv_"+std::to_string(m)).c_str(),"",1260,900);
    canv->SetLeftMargin(0.18);
    canv->SetRightMargin(0.1);
    canv->SetBottomMargin(0.24);
    canv->SetTopMargin(0.017);
    canv->SetGridx();
    canv->SetGridy();

    cov_hist->Draw("colz text");
    cov_hist->GetXaxis()->LabelsOption("v");
    cov_hist->GetYaxis()->LabelsOption("h");
    cov_hist->GetZaxis()->SetMaxDigits(3);
    cov_hist->GetZaxis()->SetLabelSize(0.03);
    cov_hist->SetContour(nshades);

    latex.DrawLatex(-2.4,-2.68,"Covariance matrix");

    canv->Write(("cov_"+std::to_string(m)).c_str());
    canv->SaveAs(("pngs/"+tag+"cov_"+std::to_string(m)+".png").c_str());
    canv->Clear();

    abs_cov_hist->Draw("colz text");
    abs_cov_hist->GetXaxis()->LabelsOption("v");
    abs_cov_hist->GetYaxis()->LabelsOption("h");
    abs_cov_hist->GetZaxis()->SetMaxDigits(3);
    abs_cov_hist->GetZaxis()->SetLabelSize(0.03);
    abs_cov_hist->SetContour(nshades);

    latex.DrawLatex(-2.4,-2.68,"Abs. covariance matrix");

    canv->Write(("abs_cov_"+std::to_string(m)).c_str());
    canv->SaveAs(("pngs/"+tag+"abs_cov_"+std::to_string(m)+".png").c_str());
    canv->Clear();

    //--------------------------------------------------------------------------------
    //                             Correlation matrix
    //--------------------------------------------------------------------------------
    
    TMatrixD corr = valor::util::CovarianceMatrixToCorrelationMatrix(cov);

    TH2D * corr_hist     = static_cast<TH2D*>(cov_hist->Clone(("corrhist_"+std::to_string(m)).c_str()));
    TH2D * abs_corr_hist = static_cast<TH2D*>(cov_hist->Clone(("abscorrhist_"+std::to_string(m)).c_str()));

    for(int i=0; i<n_params; i++){
      for(int j=0; j<n_params; j++){
        float value = corr(i,j);
        corr_hist->SetBinContent(i+1,j+1,value);
        abs_corr_hist->SetBinContent(i+1,j+1,abs(value));
      }
      std::string label = "#color["+std::to_string(pal.at(i))+"]{"+params_tex.at(i)+"}";

      corr_hist->GetXaxis()->SetBinLabel(i+1,label.c_str());
      corr_hist->GetYaxis()->SetBinLabel(i+1,label.c_str());
      abs_corr_hist->GetXaxis()->SetBinLabel(i+1,label.c_str());
      abs_corr_hist->GetYaxis()->SetBinLabel(i+1,label.c_str());
    }

    int red_blue_palette = valor::util::CreateRedToBlueColorPalette(nshades);
  
    corr_hist->Draw("colz text");
    corr_hist->SetContour(nshades);
    corr_hist->GetXaxis()->LabelsOption("v");
    corr_hist->GetYaxis()->LabelsOption("h");
    corr_hist->GetZaxis()->SetRangeUser(-1.,1.);
    corr_hist->GetZaxis()->SetMaxDigits(3);
    corr_hist->GetZaxis()->SetLabelSize(0.03);
    
    latex.DrawLatex(-2.4,-2.68,"Correlation matrix");

    canv->Update();
    canv->Write(("corr_"+std::to_string(m)).c_str());
    canv->SaveAs(("pngs/"+tag+"corr_"+std::to_string(m)+".png").c_str());
    canv->Clear();

    abs_corr_hist->Draw("colz text");
    abs_corr_hist->SetContour(nshades);
    abs_corr_hist->GetXaxis()->LabelsOption("v");
    abs_corr_hist->GetYaxis()->LabelsOption("h");
    abs_corr_hist->GetZaxis()->SetRangeUser(0,1.);
    abs_corr_hist->GetZaxis()->SetMaxDigits(3);
    abs_corr_hist->GetZaxis()->SetLabelSize(0.03);
    
    latex.DrawLatex(-2.4,-2.68,"Abs. correlation matrix");

    canv->Update();
    canv->Write(("abs_corr_"+std::to_string(m)).c_str());
    canv->SaveAs(("pngs/"+tag+"abs_corr_"+std::to_string(m)+".png").c_str());
    canv->Clear();
  }
  f_out->Close();

}
