//
//------------------------------------------------------
// Macro to plot prefit systematic errors
// and posfit systematic paramter pulls
// This follows SBN pulls studies for selected 
// systematic parameters 
// Comparing between inclusive and exclusive fits
//
// Rhiannon Jones
// October 2020
//------------------------------------------------------
//

std::string FixName(const std::string &name);

void sbn_pull_studies(const char * inc_filename, 
                      const char * exc_filename, 
                      std::string  inputs = "", // Input covariance from the fits
                      const int ntoys = 1, // Number of toys to plot from the output, default only 1, if [-1] run number in file
                      std::string  output_tag = "") 
{
  using namespace valor;

  // If we have not passed all initial systematic files, don't plot any
  if(inputs == ""){
    std::cout << " Error: No initial systematics have been specified, nothing to plot" << std::endl;
    exit(1);
  }

  // Add an underscore to the tag
  std::string tag = "";
  if(output_tag != "")
    tag = "_"+output_tag;

  // Open input file
  // Get full path if needed
  std::string fullpathinc     = inc_filename;
  std::string fullpathexc     = exc_filename;
  std::string expandedpathinc = "";
  std::string expandedpathexc = "";

  std::size_t dollarinc = fullpathinc.find("$");
  std::size_t dollarexc = fullpathexc.find("$");
  
  // Inclusive input file path
  if(dollarinc != std::string::npos){
    expandedpathinc = valor::util::file::GetFilename(fullpathinc);
  }
  else
    expandedpathinc = fullpathinc;

  // Exclusive input file path
  if(dollarexc != std::string::npos){
    expandedpathexc = valor::util::file::GetFilename(fullpathexc);
  }
  else
    expandedpathexc = fullpathexc;

  short true_color = kPink+5;
  short inc_color  = kAzure+7;
  short inc_line   = kAzure-1;
  short exc_color  = kOrange-3;
  short exc_line   = kOrange+2;

  int inc_style  = 3017; 
  int exc_style  = 3018; 

  int true_marker = 33; 
  int inc_marker  = 22; 
  int exc_marker  = 23; 

  // BF params from inclusive and exclusive fits
  FitParamList  *  gbfparm_inc = 0; // global best-fit params, inclusive
  FitParamList  *  gbfparm_exc = 0; // global best-fit params, exclusive

  // Get inclusive fit results
  TFile f_inc(expandedpathinc.c_str(), "read");
  TTree * fitnt_inc = (TTree*)f_inc.Get("valor_fit_ntp");
  fitnt_inc->SetBranchAddress("best_fit_params", &gbfparm_inc);

  // Get exclusive fit results
  TFile f_exc(expandedpathexc.c_str(), "read");
  TTree * fitnt_exc = (TTree*)f_exc.Get("valor_fit_ntp");
  fitnt_exc->SetBranchAddress("best_fit_params", &gbfparm_exc);

  // Get the number of toys to construct plots and comparisons for
  int nentries = fitnt_inc->GetEntries();

  // If ntoys is greater than 0, run that number
  // If ntoys == -1, run nentries
  int ntorun = ntoys;
  if(ntoys == -1)
    ntorun = nentries;

  if(ntoys > nentries){
    std::cerr << " Error: Number of toys requested, " << ntoys << ", exceeds the number available in the fit, " << nentries << std::endl;
    util::Die(-1);
  }

  if(ntorun == 0){
    std::cerr << " Error: Running over 0 toys, this is a bit pointless..." << std::endl;
    util::Die(-1);
  }

  // Setup things which don't need to be defined in every toymc
  // Pull plot legends
  TLegend *l_bestfit = new TLegend(0.21,0.95,0.82,0.999);
  l_bestfit->SetNColumns(3);
  l_bestfit->SetBorderSize(0);
  l_bestfit->SetFillStyle(0);
  l_bestfit->SetTextFont(132);

  // Input and proposal_xsec prefit matrices
  TFile f_inputs((inputs).c_str(), "read");

  TMatrixD *input_s    = static_cast<TMatrixD*>(f_inputs.Get("cov"));
  TMatrixD &input_syst = *input_s;

  int nInputRows = input_syst.GetNrows();
  int nInputCols = input_syst.GetNcols();

  // Histograms to hold the comparisons between true and postfit values
  TH1D *h_true_inc = new TH1D("h_true_inc","",50,-3,3);
  TH1D *h_true_exc = new TH1D("h_true_exc","",50,-3,3);

  TFile *f_outputs = new TFile(("inclusive_exclusive_pull_studies"+tag+".root").c_str(),"RECREATE");
  f_outputs->cd();

  TString pdf_filename("inclusive_exclusive_pull_studies.pdf");

  // Loop over number of toys run in the fit
  for(int i=0; i<ntorun; i++) {
    fitnt_inc->GetEntry(i);
    fitnt_exc->GetEntry(i);

    // Setup canvas for pull comparisons in this universe
    std::string pull_canv_name = "c_"+std::to_string(i);
    TCanvas *c = new TCanvas(pull_canv_name.c_str(),"",0,20,1256,720);

    /**************************************************
     *            FITPARAMLIST
     **************************************************/
    // GetNumberParameters()
    // GetNumberFreeParameters() 'if Not fixed'
    // GetNumberParametersOfInterest() -- should be osc params, 'if Do Marginalisation'
    //
    // What's the relationship between these 3 values?
    //
    // Probably want to plot all of the parameters
    // But then highlight the fixed parameters later
    // NameByIndex(i)
    // BestFitValueByIndex(i)
    // InitValueByIndex(i)
    // IsNuisanceByIndex(i)

    unsigned int totalNumParams = gbfparm_inc->GetNumberParameters();
    unsigned int freeParams     = gbfparm_inc->GetNumberFreeParameters();
    unsigned int interestParams = gbfparm_inc->GetNumberParametersOfInterest();
    unsigned int fixedParams    = totalNumParams - freeParams;
    unsigned int nuisanceParams = 0;

    // Full postfit matrix
    TMatrixDSym &cov_inc = *gbfparm_inc->GetCovMatrix();
    TMatrixDSym &cov_exc = *gbfparm_exc->GetCovMatrix();
    std::vector<double> inclusive_errors, exclusive_errors, input_errors;

    int nRows = cov_inc.GetNrows();
    int nCols = cov_inc.GetNcols();

    unsigned int nPhysicsParams = 0;
    int n = 0;
    for(int j = 0; j < nRows; ++j){
      inclusive_errors.push_back(sqrt(cov_inc(j,j)));
      exclusive_errors.push_back(sqrt(cov_exc(j,j)));
      if(!gbfparm_inc->IsNuisanceByIndex(j)){
        nPhysicsParams++;
        std::cout << " Physics parameter not nuisance parameter: " << gbfparm_inc->NameByIndex(j) << std::endl;
        continue;
      }
      nuisanceParams++;

      // Fill vectors with prefit errors
      // Input parameters
      if(n < nInputRows){
        input_errors.push_back(sqrt(input_syst(n,n)));
      }
      else {
        std::cerr << " Error: Current iterator exceeds number in the input" << std::endl;
        util::Die(-1);
      }
      n++;
    }
    if(inclusive_errors.size() != totalNumParams) 
      std::cout << " Error: The number of parameters and errors don't match. Params : " << totalNumParams << " vs. errors: " << inclusive_errors.size() << std::endl;

    const char *name_input     = ("h_input_"+to_string(i)).c_str();
    const char *name_inclusive = ("h_inclusive_"+to_string(i)).c_str();
    const char *name_exclusive = ("h_exclusive_"+to_string(i)).c_str();

    // New canvas features 
    c->SetLeftMargin   (0.069); 
    c->SetRightMargin  (0.02);
    c->SetBottomMargin (0.20);
    c->SetTopMargin    (0.06);

    TH1D *h_input     = new TH1D(name_input,     "", nRows-nPhysicsParams, 0, nRows-nPhysicsParams);
    TH1D *h_inclusive = new TH1D(name_inclusive, "", nRows-nPhysicsParams, 0, nRows-nPhysicsParams);
    TH1D *h_exclusive = new TH1D(name_exclusive, "", nRows-nPhysicsParams, 0, nRows-nPhysicsParams);

    unsigned int nuisance_it = 0;

    for(unsigned int j = 0; j < totalNumParams; ++j){
      bool isNuisance = gbfparm_inc->IsNuisanceByIndex(j);
      if(!isNuisance) continue; // Only want to plot nuisance parameters for now
      nuisance_it = j-nPhysicsParams; // Bin number for nuisance parameters
      int nuisanceBin = nuisance_it+1;

      double input_bin_content     = 0.;
      double inclusive_bin_content = 0.;
      double exclusive_bin_content = 0.;

      double inclusive_bin_error   = 0.;
      double exclusive_bin_error   = 0.;

      // Convert to units of nsigma
      // Check the initial values are the same in the inclusive and exclusive fit outputs
      if(std::abs(gbfparm_inc->InitValueByIndex(j) - gbfparm_exc->InitValueByIndex(j)) > std::numeric_limits<float>::epsilon()){
        std::cerr << " Error: The initial values in the inclusive and exclusive fits don't match, can't compare!" << std::endl;
        util::Die(-1);
      }

      input_bin_content     = gbfparm_inc->InitValueByIndex(j);
      inclusive_bin_content = gbfparm_inc->BestFitValueByIndex(j);
      exclusive_bin_content = gbfparm_exc->BestFitValueByIndex(j);
      inclusive_bin_error   = inclusive_errors.at(j);
      exclusive_bin_error   = exclusive_errors.at(j);

      h_true_inc->Fill(inclusive_bin_content-input_bin_content);
      h_true_exc->Fill(exclusive_bin_content-input_bin_content);

      // Prefit bin content is always 0 in order to only demonstrate the error in each bin
      h_input->SetBinContent(nuisanceBin,     input_bin_content);
      h_inclusive->SetBinContent(nuisanceBin, inclusive_bin_content);
      h_exclusive->SetBinContent(nuisanceBin, exclusive_bin_content);
      h_inclusive->SetBinError(nuisanceBin,   inclusive_bin_error);
      h_exclusive->SetBinError(nuisanceBin,   exclusive_bin_error);

      std::string curr_name = FixName(gbfparm_inc->NameByIndex(j));
      h_inclusive->GetXaxis()->SetBinLabel(nuisanceBin,curr_name.c_str());
    }
    
    double max_error = -999.;
    for(int i = 0; i < h_inclusive->GetNbinsX(); ++i){
      double curr_error = std::max(h_inclusive->GetBinError(i), h_exclusive->GetBinError(i));
      if(curr_error > max_error)
        max_error = curr_error;
    }
    double maxy = (std::max(h_inclusive->GetMaximum(),h_exclusive->GetMaximum())+max_error);
    if(maxy < 0)
      maxy = maxy*0.9;
    else
      maxy = maxy*1.1;

    double miny = (std::min(h_inclusive->GetMinimum(),h_exclusive->GetMinimum())-max_error);
    if(miny > 0)
      miny = miny*0.9;
    else
      miny = miny*1.1;

    h_inclusive->GetYaxis()->SetRangeUser(miny,maxy);
    h_inclusive->Draw("E2");
    h_exclusive->Draw("same E2");
    h_input->Draw("same p");

    h_inclusive->GetXaxis()->LabelsOption("v");
    h_inclusive->GetXaxis()->SetLabelSize(0.035);
    h_inclusive->GetXaxis()->SetLabelFont(132);
    h_inclusive->GetYaxis()->SetLabelSize(0.035);
    h_inclusive->GetYaxis()->SetLabelFont(132);
    h_inclusive->GetYaxis()->SetTitleSize(0.035);
    h_inclusive->GetYaxis()->SetTitleFont(132);
    h_inclusive->GetYaxis()->SetTitleOffset(1);
    h_inclusive->GetXaxis()->SetTitle("");
    h_inclusive->GetYaxis()->SetTitle("Parameter pull [#sigma]");
    h_inclusive->SetFillColor(inc_color);
    h_inclusive->SetFillStyle(inc_style);
    h_inclusive->SetLineWidth(0);
    h_inclusive->SetMarkerStyle(inc_marker);
    h_inclusive->SetMarkerColor(inc_color);

    h_exclusive->SetFillColor(exc_color);
    h_exclusive->SetFillStyle(exc_style);
    h_exclusive->SetLineWidth(0);
    h_exclusive->SetMarkerStyle(exc_marker);
    h_exclusive->SetMarkerColor(exc_color);

    h_input->SetMarkerColor(true_color);
    h_input->SetMarkerStyle(true_marker);

    l_bestfit->AddEntry(h_input,"True value", "p");
    l_bestfit->AddEntry(h_inclusive,"Inclusive postfit value", "fp");
    l_bestfit->AddEntry(h_exclusive,"Exclusive postfit value", "fp");
    l_bestfit->Draw("same");
    c->SetGridy();
    c->Update();
    c->Draw();
    c->Write();
    l_bestfit->Clear();
    c->Clear();
    
    h_inclusive->Draw();
    h_exclusive->Draw("same");
    h_input->Draw("same p");
    l_bestfit->AddEntry(h_input,"True value", "p");
    l_bestfit->AddEntry(h_inclusive,"Inclusive postfit value", "p");
    l_bestfit->AddEntry(h_exclusive,"Exclusive postfit value", "p");
    l_bestfit->Draw("same");
    c->Update();
    c->Draw();
    // Now append to pdf 
    if(i == 0){
      TString tempPDF(pdf_filename);
      tempPDF.Append("(");
      c->Print(tempPDF.Data(),"pdf");
    }

    else if(i == ntorun-1){
      TString tempPDF(pdf_filename);
      tempPDF.Append(")");
      c->Print(tempPDF.Data(),"pdf");
    }

    else
      c->Print(pdf_filename.Data(),"pdf");

    c->SaveAs(("pngs/inclusive_exclusive_pull_studies_universe_"+std::to_string(i)+".png").c_str());
    c->Clear();
    l_bestfit->Clear();
  }
  
  // Now for the global comparison
  // Pull comparison canvas and legend
  TCanvas *c_comp = new TCanvas("c_comp","",20,20,700,900);
  c_comp->SetTopMargin(0.044);
  c_comp->SetBottomMargin(0.1);
  c_comp->SetLeftMargin(0.1);
  c_comp->SetRightMargin(0.044);
  TLegend *l_comp = new TLegend(0.26,0.95,0.87,0.999);
  l_comp->SetNColumns(2);
  l_comp->SetBorderSize(0);
  l_comp->SetFillStyle(0);
  l_comp->SetTextFont(132);

  double max_comp_y = std::max(h_true_inc->GetMaximum(),h_true_exc->GetMaximum());
  h_true_inc->GetYaxis()->SetRangeUser(0.,max_comp_y*1.1);
  h_true_inc->Draw("hist");
  h_true_exc->Draw("same hist");

  h_true_inc->GetXaxis()->SetLabelSize(0.035);
  h_true_inc->GetXaxis()->SetLabelFont(132);
  h_true_inc->GetXaxis()->SetTitleSize(0.035);
  h_true_inc->GetXaxis()->SetTitleFont(132);
  h_true_inc->GetXaxis()->SetTitleOffset(1.2);
  h_true_inc->GetYaxis()->SetLabelSize(0.035);
  h_true_inc->GetYaxis()->SetLabelFont(132);
  h_true_inc->GetYaxis()->SetTitleSize(0.035);
  h_true_inc->GetYaxis()->SetTitleFont(132);
  h_true_inc->GetYaxis()->SetTitleOffset(1.2);
  h_true_inc->GetXaxis()->SetTitle("(Bestfit-true) #sigma");
  h_true_inc->GetYaxis()->SetTitle("Number of toys, all parameters");
  h_true_inc->SetLineColor(inc_color);
  h_true_exc->SetLineColor(exc_color);

  l_comp->AddEntry(h_true_inc,"Inclusive fits", "l");
  l_comp->AddEntry(h_true_exc,"Exclusive fits", "l");
  l_comp->Draw();

  c_comp->Write();
  f_outputs->Close();
}

std::string FixName(const std::string &name){
  TString t_name(name);
  t_name.ReplaceAll("genie_","");
  t_name.ReplaceAll("_Genie","");
  t_name.ReplaceAll("_FluxUnisim","");
  return std::string(t_name.Data());
}
