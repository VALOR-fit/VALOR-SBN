//
//------------------------------------------------------
// Macro to plot prefit systematic errors
// and posfit systematic paramter pulls
//
// Rhiannon Jones
// May 2020
//------------------------------------------------------
//

void FormatLatex(const double &b, const double &e, const double &w, const double &y, const char *s);

void sbn_parameter_pulls(const char * filename, 
    const int exp = -1,
    std::string  location = "",
    std::string  flux = "", 
    std::string  flux2 = "", 
    std::string  proposal_xsec = "", 
    std::string  modern_xsec = "", 
    const char * int_cov = "", 
    std::string  mec = "", 
    std::string  detector = "", 
    const char * sample = "",
    std::string  input_tag = "")
{
  using namespace valor;

  // If we have not passed all initial systematic files, don't plot any
  if(flux          == "" || 
     flux2         == "" ||
     proposal_xsec == "" ||
     modern_xsec   == ""    ) {
    std::cout << " Error: Not all the initial systematics have been specified, nothing to plot" << std::endl;
    exit(1);
  }

  // Add an underscore to the tag
  const char *tag = "";
  if(input_tag != "")
    tag = ("_"+input_tag).c_str();

  bool detector_systematics = true;
  if(detector == "") detector_systematics = false;
  else std::cout << " Including the detector systematics" << std::endl;

  bool mec_cov = true;
  if(mec == "") mec_cov = false;
  else std::cout << " Including the MEC systematic" << std::endl;

  // Open input file
  // Get full path if needed
  std::string fullpath     = filename;
  std::string expandedpath = "";

  std::size_t dollar = fullpath.find("$");
  if(dollar != std::string::npos)
    expandedpath = valor::util::file::GetFilename(fullpath);
  else
    expandedpath = fullpath;

  TFile f(expandedpath.c_str(), "read");

  short data_color = kPink+5;
  short prefit_color = kAzure+7;
  short prefit_line = kAzure-1;
  short postfit_color = kOrange-3;
  short postfit_line = kOrange+2;

  int data_style    = 3002; // Hatched;
  int prefit_style  = 3002; // Hatched;
  int postfit_style = 3002; // Solid;

  /*
  // Load Opt state from file, as interpretation of physics parameters depends on it.
  // Not having it may lead to oddities if Opt params were tweaked with respect to default.
  // Eg at fit time using and storing sintheta, but now thinking it is sin2theta.
  Opt::Persistable * optp = (Opt::Persistable *) f.Get("options");
  if(!optp) {
  cerr << "Can not find Opt::Persistable in input file!" << endl;
  exit(1);
  }
  Opt::Instance()->ReadFrom(*optp);
  cout << *Opt::Instance() << endl;
  */

  // Tree structure below is what is written out by run_osc_fit.C
  // Similar (or adapt trivially) for other macros

  FitParamList *  gbfparm = 0;   // global best-fit params
  PhysParamList * iparm = 0;     // input params
  TObjArray * bfmodel_array = 0; // an array of optimum FitParamList for all fits performed to each toy MC
  TObjArray * data_array = 0; // an array of all toy-MC data and best-fit predictions for all fits performed to each toy MC

  TTree * fitnt = (TTree*)f.Get("valor_fit_ntp");
  fitnt->SetBranchAddress("best_fit_params",        &gbfparm);
  fitnt->SetBranchAddress("true_params",            &iparm);
  fitnt->SetBranchAddress("best_fit_model",         &bfmodel_array);
  fitnt->SetBranchAddress("data",                   &data_array);

  TCanvas *c = new TCanvas("c","",0,20,1256,720);
  TLegend *l_bestfit = new TLegend(0.63,0.68,0.88,0.88);
  l_bestfit->SetBorderSize(0);

  for(int i=0; i<3; i++) {

    fitnt->GetEntry(i);
    if(exp >= 0 && i != exp) continue; // Only look at chosen experiment if defined

    std::string name = "";
    switch(i) {
      case (0) : name = "sbn_nd";     break;
      case (1) : name = "sbn_uboone"; break;
      case (2) : name = "sbn_icarus"; break;
      default  : name = "sbn_nd";  
    }

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

    unsigned int totalNumParams = gbfparm->GetNumberParameters();
    unsigned int freeParams     = gbfparm->GetNumberFreeParameters();
    unsigned int interestParams = gbfparm->GetNumberParametersOfInterest();
    unsigned int fixedParams    = totalNumParams - freeParams;
    unsigned int nuisanceParams = 0;

    // Full postfit matrix
    TMatrixDSym &cov = *gbfparm->GetCovMatrix();
    std::vector<double> postfit_errors, prefit_errors;
    prefit_errors.clear();
    postfit_errors.clear();

    int nRows         = cov.GetNrows();
    int nCols         = cov.GetNcols();

    // Flux and proposal_xsec prefit matrices
    TFile f_flux((location+"/"+flux).c_str(), "read");
    TFile f_fluxspline((location+"/"+flux2).c_str(), "read");
    TFile f_prop((location+"/"+proposal_xsec).c_str(), "read");
    TFile f_mod((location+"/"+modern_xsec).c_str(), "read");

    TMatrixD *flux_s          = static_cast<TMatrixD*>(f_flux.Get("frac_cov"));
    TMatrixD *fluxspline_s    = static_cast<TMatrixD*>(f_fluxspline.Get(int_cov));
    TMatrixD *prop_s          = static_cast<TMatrixD*>(f_prop.Get(int_cov));
    TMatrixD *mod_s           = static_cast<TMatrixD*>(f_mod.Get(int_cov));
    TMatrixD &flux_syst       = *flux_s;
    TMatrixD &fluxspline_syst = *fluxspline_s;
    TMatrixD &prop_syst       = *prop_s;
    TMatrixD &mod_syst        = *mod_s;

    int nFluxRows       = flux_syst.GetNrows();
    int nFluxCols       = flux_syst.GetNcols();
    int nFluxSplineRows = fluxspline_syst.GetNrows();
    int nFluxSplineCols = fluxspline_syst.GetNcols();
    int nPropRows       = prop_syst.GetNrows();
    int nPropCols       = prop_syst.GetNcols();
    int nModRows        = mod_syst.GetNrows();
    int nModCols        = mod_syst.GetNcols();
    double singleFlux   = nFluxRows/3.;

    // Initialise paramters incase we have a MEC systematics
    int nMECRows       = 0.;
    int nMECCols       = 0.;
    TMatrixD mec_syst(0,0);
    TMatrixD *mec_s    = nullptr;

    // If we have detector parameters, get the information now
    if(mec_cov){
      TFile f_mec((location+"/"+mec).c_str(), "read");
      mec_s    = (TMatrixD*)f_mec.Get("frac_cov");
      mec_syst.ResizeTo(mec_s->GetNrows(),mec_s->GetNcols());
      mec_syst = *mec_s;
      nMECRows = mec_syst.GetNrows();
      nMECCols = mec_syst.GetNcols();
    }

    // Initialise paramters incase we have detector systematics
    int nDetRows       = 0.;
    int nDetCols       = 0.;
    TMatrixD det_syst(0,0);
    TMatrixD *det_s    = nullptr;

    // If we have detector parameters, get the information now
    if(detector_systematics){
      TFile f_det((location+"/"+detector).c_str(), "read");
      det_s    = (TMatrixD*)f_det.Get("frac_cov_total");
      det_syst.ResizeTo(det_s->GetNrows(),det_s->GetNcols());
      det_syst = *det_s;
      nDetRows = det_syst.GetNrows();
      nDetCols = det_syst.GetNcols();
    }

    // Cumulative rows
    int nCumFluxRows = nFluxRows+nFluxSplineRows;
    int nCumPropRows = nCumFluxRows+nPropRows;
    int nCumModRows  = nCumPropRows+nModRows;
    int nCumMECRows  = nCumModRows+nMECRows;
    int nCumDetRows  = nCumMECRows+nDetRows;

    float total_postfit = 0.;
    float total_prefit  = 0.;

    unsigned int nPhysicsParams = 0;
    int n = 0;
    for(int j = 0; j < nRows; ++j){
      postfit_errors.push_back(sqrt(cov(j,j)));
      if(!gbfparm->IsNuisanceByIndex(j)){
        nPhysicsParams++;
        std::cout << " Physics parameter not nuisance parameter: " << gbfparm->NameByIndex(j) << std::endl;
        continue;
      }
      nuisanceParams++;
      total_postfit += abs(sqrt(cov(j,j)));

      // Fill vectors with prefit errors
      // Flux parameters
      if(n < nFluxRows){
        prefit_errors.push_back(sqrt(flux_syst(n,n)));
        total_prefit += abs(sqrt(flux_syst(n,n)));
      }
      // Flux spline parameters
      else if(n >= nFluxRows && n < (nCumFluxRows)){
        prefit_errors.push_back(sqrt(fluxspline_syst(n-nFluxRows,n-nFluxRows)));
        total_prefit += abs(sqrt(fluxspline_syst(n-nFluxRows,n-nFluxRows)));
      }
      // proposal_xsec parameters
      else if(n >= (nCumFluxRows) && n < (nCumPropRows)){
        prefit_errors.push_back(sqrt(prop_syst(n-(nCumFluxRows),n-(nCumFluxRows))));
        total_prefit += abs(sqrt(prop_syst(n-(nCumFluxRows),n-(nCumFluxRows))));
      }
      // modern_xsec parameters
      else if(n >= (nCumPropRows) && n < (nCumModRows)){
        prefit_errors.push_back(sqrt(mod_syst(n-(nCumPropRows),n-(nCumPropRows))));
        total_prefit += abs(sqrt(mod_syst(n-(nCumPropRows),n-(nCumPropRows))));
      }
      // MEC parameter 
      else if(n >= (nCumModRows) && n < (nCumMECRows)){
        prefit_errors.push_back(sqrt(mec_syst(n-(nCumModRows),n-(nCumModRows))));
        total_prefit += abs(sqrt(mec_syst(n-(nCumModRows),n-(nCumModRows))));
      }
      // Detector parameters
      else if(detector_systematics && n >= (nCumMECRows)){
        prefit_errors.push_back(sqrt(det_syst(n-(nCumMECRows),n-(nCumMECRows))));
        total_prefit += abs(sqrt(det_syst(n-(nCumMECRows),n-(nCumMECRows))));
      }
      n++;
    }

    std::cout << " ====================================================== " << std::endl;
    std::cout << " Error on the number of predicted events: +/- " << total_postfit   << std::endl;
    std::cout << " Error on the number of initial events  : +/- " << total_prefit << std::endl;
    std::cout << " ====================================================== " << std::endl;

    if(postfit_errors.size() != totalNumParams) 
      std::cout << " Error: The number of parameters and errors don't match. Params : " << totalNumParams << " vs. errors: " << postfit_errors.size() << std::endl;

    const char *name_prefit  = ("h_prefit_"+name).c_str();
    const char *name_postfit = ("h_postfit_"+name).c_str();

    // Neutrino flavour number of bins
    int n_numu         = 20;
    int n_numubar      = 5;
    int n_nue          = 6;
    int n_nuebar       = 2;
    int n_numubar_bins = n_numubar+n_numu;
    int n_nue_bins     = n_nue+n_numubar_bins;
    int n_nuebar_bins  = n_nuebar+n_nue_bins;

    // New canvas features 
    c->SetLeftMargin   (0.069); 
    c->SetRightMargin  (0.02);
    c->SetBottomMargin (0.22);
    c->SetTopMargin    (0.06);

    TH1D *h_prefit  = new TH1D(name_prefit,  "", nRows-nPhysicsParams, 0, nRows-nPhysicsParams);
    TH1D *h_postfit = new TH1D(name_postfit, "", nRows-nPhysicsParams, 0, nRows-nPhysicsParams);

    unsigned int nuisance_it = 0;

    for(unsigned int j = 0; j < totalNumParams; ++j){
      bool isNuisance = gbfparm->IsNuisanceByIndex(j);
      if(!isNuisance) continue; // Only want to plot nuisance parameters for now
      nuisance_it = j-nPhysicsParams; // Bin number for nuisance parameters
      int nuisanceBin = nuisance_it+1;

      double postfit_bin_content = 0.;
      double postfit_bin_error   = 0.;
      // Convert to units of nsigma
      postfit_bin_content = (gbfparm->BestFitValueByIndex(j)-gbfparm->InitValueByIndex(j))/static_cast<double>(prefit_errors.at(nuisance_it));
      postfit_bin_error   = postfit_errors.at(j)/static_cast<double>(prefit_errors.at(nuisance_it));

      // Prefit bin content is always 0 in order to only demonstrate the error in each bin
      h_prefit->SetBinContent(nuisanceBin,  gbfparm->InitValueByIndex(j));
      h_postfit->SetBinContent(nuisanceBin, postfit_bin_content);
      h_prefit->SetBinError(nuisanceBin,    prefit_errors.at(nuisance_it));
      h_postfit->SetBinError(nuisanceBin,   postfit_bin_error);

      // Define array of empty flux parameter bins
      // Corresponding to 
      //  bin expt.  flav.
      //
      //  14  SBND   nue00
      //  35  uBooNE nue00
      //  41  uBooNE nuebar00
      //  56  ICARUS nue00
      //  57  ICARUS nue01
      //  62  ICARUS nuebar00
      std::vector<int> empties      = {14,35,41,56,57,62};
      std::vector<int>::iterator it = std::find(empties.begin(),empties.end(),nuisanceBin); 
      if(it != empties.end()){
        h_prefit->SetBinError(nuisanceBin, 0);
        h_postfit->SetBinError(nuisanceBin, 0);
      }
      h_prefit->GetXaxis()->SetBinLabel(nuisanceBin,gbfparm->NameByIndex(j).c_str());
      h_postfit->GetXaxis()->SetBinLabel(nuisanceBin,gbfparm->NameByIndex(j).c_str());
    }
    TH1D *h_postfit_2 = (TH1D*)h_postfit->Clone("h_postfit_2");
    TH1D *h_prefit_2  = (TH1D*)h_prefit->Clone("h_prefit_2");

    double max_error = -999.;
    for(int i = 0; i < h_postfit_2->GetNbinsX(); ++i){
      if(h_postfit_2->GetBinError(i) > max_error)
        max_error = h_postfit_2->GetBinError(i);
    }
    double maxy = (h_postfit_2->GetMaximum() + max_error)*1.1;
    if(maxy < 0)
      maxy = maxy*0.9;
    else
      maxy = maxy*1.1;

    double miny = (h_postfit_2->GetMinimum() - max_error)*0.9;
    if(miny > 0)
      miny = miny*0.9;
    else
      miny = miny*1.1;

    //Temporaray for saving
    //miny = -4;
    //maxy = +7;

    // Solid lines for detector and proposal_xsec separation
    TLine line_sbnd  (singleFlux,   miny-0.02, singleFlux,   maxy+0.1);
    TLine line_uboone(singleFlux*2, miny-0.02, singleFlux*2, maxy+0.1);
    TLine line_icarus(nFluxRows,    miny-0.02, nFluxRows,    maxy+0.1);
    TLine line_fluxspline(nCumFluxRows, miny-0.02, nCumFluxRows, maxy+0.1);
    TLine line_propmod(nCumPropRows, miny-0.02, nCumPropRows, maxy+0.1);
    TLine line_moddet(nCumMECRows, miny-0.02, nCumMECRows, maxy+0.1);

    // Dashed neutrino flavour separation
    TLine line_sbnd_numu   (n_numu,         miny-0.02, n_numu,         maxy+0.02);
    TLine line_sbnd_numubar(n_numubar_bins, miny-0.02, n_numubar_bins, maxy+0.02);
    TLine line_sbnd_nue    (n_nue_bins,     miny-0.02, n_nue_bins,     maxy+0.02);
    TLine line_sbnd_nuebar (n_nuebar_bins,  miny-0.02, n_nuebar_bins,  maxy+0.02);

    TLine line_uboone_numu   (singleFlux+n_numu,         miny-0.02, singleFlux+n_numu,         maxy+0.02);
    TLine line_uboone_numubar(singleFlux+n_numubar_bins, miny-0.02, singleFlux+n_numubar_bins, maxy+0.02);
    TLine line_uboone_nue    (singleFlux+n_nue_bins,     miny-0.02, singleFlux+n_nue_bins,     maxy+0.02);
    TLine line_uboone_nuebar (singleFlux+n_nuebar_bins,  miny-0.02, singleFlux+n_nuebar_bins,  maxy+0.02);

    TLine line_icarus_numu   ((singleFlux*2)+n_numu,         miny-0.02, (singleFlux*2)+n_numu,         maxy+0.02);
    TLine line_icarus_numubar((singleFlux*2)+n_numubar_bins, miny-0.02, (singleFlux*2)+n_numubar_bins, maxy+0.02);
    TLine line_icarus_nue    ((singleFlux*2)+n_nue_bins,     miny-0.02, (singleFlux*2)+n_nue_bins,     maxy+0.02);
    TLine line_icarus_nuebar ((singleFlux*2)+n_nuebar_bins,  miny-0.02, (singleFlux*2)+n_nuebar_bins,  maxy+0.02);

    std::vector<TLine> lines_sbnd = {line_sbnd, line_sbnd_numu, line_sbnd_numubar, line_sbnd_nue, line_sbnd_nuebar};
    std::vector<TLine> lines_uboone = {line_uboone, line_uboone_numu, line_uboone_numubar, line_uboone_nue, line_uboone_nuebar};
    std::vector<TLine> lines_icarus = {line_icarus, line_icarus_numu, line_icarus_numubar, line_icarus_nue, line_icarus_nuebar};

    for(unsigned int i = 0; i < lines_sbnd.size(); ++i){
      lines_sbnd[i].SetLineColor(kAzure+7);
      lines_uboone[i].SetLineColor(kPink+5);
      lines_icarus[i].SetLineColor(kOrange-3);

      if(i == 0){
        lines_sbnd[i].SetLineWidth(2);
        lines_uboone[i].SetLineWidth(2);
        lines_icarus[i].SetLineWidth(2);
      }
      else{
        lines_sbnd[i].SetLineWidth(1);
        lines_uboone[i].SetLineWidth(1);
        lines_icarus[i].SetLineWidth(1);
        lines_sbnd[i].SetLineStyle(7);
        lines_uboone[i].SetLineStyle(7);
        lines_icarus[i].SetLineStyle(7);
      }
    }
    line_moddet.SetLineColor(kGray+2);
    line_moddet.SetLineWidth(2);
    line_moddet.SetLineStyle(1);

    line_propmod.SetLineColor(kTeal-5);
    line_propmod.SetLineWidth(2);
    line_propmod.SetLineStyle(1);

    line_fluxspline.SetLineColor(kYellow-3);
    line_fluxspline.SetLineWidth(2);
    line_fluxspline.SetLineStyle(1);

    h_postfit->Draw("E2");
    h_postfit->GetYaxis()->SetRangeUser(miny,maxy);
    h_postfit_2->Draw("same hist");
    for(unsigned int i = 0; i < lines_sbnd.size(); ++i){
      lines_sbnd[i].Draw("same");
      lines_uboone[i].Draw("same");
      lines_icarus[i].Draw("same");
    }
    line_fluxspline.Draw("same");
    line_propmod.Draw("same");
    if(detector_systematics)
      line_moddet.Draw("same");

    h_postfit->GetXaxis()->LabelsOption("v");
    h_postfit->GetXaxis()->SetLabelSize(0.025);
    h_postfit->GetXaxis()->SetTitleSize(0.035);
    h_postfit->GetXaxis()->SetTitleOffset(1.2);
    h_postfit->GetYaxis()->SetLabelSize(0.035);
    h_postfit->GetYaxis()->SetTitleSize(0.035);
    h_postfit->GetYaxis()->SetTitleOffset(1);
    h_postfit->GetXaxis()->SetTitle("");
    h_postfit->GetYaxis()->SetTitle("Parameter pull, n#sigma");
    h_postfit->SetMarkerSize(0);
    h_postfit->SetLineColor(postfit_line);
    h_postfit->SetFillColor(postfit_color);
    h_postfit->SetFillStyle(postfit_style);
    h_postfit_2->SetLineColor(postfit_line);
    h_postfit_2->SetFillStyle(0);
    h_postfit_2->SetLineWidth(1);

    // Sort latex
    FormatLatex(0,           singleFlux,  h_postfit->GetNbinsX(),maxy*1.05,"#color[867]{SBND Flux}");
    FormatLatex(singleFlux,  singleFlux*2,h_postfit->GetNbinsX(),maxy*1.05,"#color[905]{#muBooNE Flux}");
    FormatLatex(singleFlux*2,nFluxRows,   h_postfit->GetNbinsX(),maxy*1.05,"#color[797]{ICARUS Flux}");
    FormatLatex(nFluxRows,   nCumFluxRows,h_postfit->GetNbinsX(),maxy*1.05,"#color[397]{Flux}");
    FormatLatex(nCumFluxRows,nCumPropRows,h_postfit->GetNbinsX(),maxy*1.05,"#color[835]{Prop. #sigma}");
    FormatLatex(nCumPropRows,nCumMECRows, h_postfit->GetNbinsX(),maxy*1.05,"#color[923]{Modern #sigma}");
    if(detector_systematics)
      FormatLatex(nCumMECRows,nCumMECRows+nDetRows,h_postfit->GetNbinsX(),maxy*1.05,"#color[820]{Detector}");

    c->SetGridy();
    c->Update();
    c->Draw();
    c->SaveAs(("postfit-only_nuisance_params_mdc_"+name+"_"+sample+tag+".root").c_str());
    c->Clear();

    double max_in_error = -999.;
    for(int i = 0; i < h_prefit->GetNbinsX(); ++i){
      if(h_prefit->GetBinError(i) > max_in_error)
        max_in_error = h_prefit->GetBinError(i);
    }
    double maxiny = (h_prefit->GetMaximum() + max_in_error);
    if(maxiny < 0)
      maxiny = maxiny*0.9;
    else
      maxiny = maxiny*1.1;

    double mininy = (h_prefit->GetMinimum() - max_in_error);
    if(mininy > 0)
      mininy = mininy*0.9;
    else
      mininy = mininy*1.1;

    h_prefit->Draw("E2");
    h_prefit->GetYaxis()->SetRangeUser(mininy,maxiny);
    h_prefit_2->Draw("hist same l");
    h_prefit->GetXaxis()->LabelsOption("v");
    h_prefit->GetXaxis()->SetLabelSize(0.025);
    h_prefit->GetXaxis()->SetTitleSize(0.035);
    h_prefit->GetXaxis()->SetTitleOffset(1.2);
    h_prefit->GetYaxis()->SetLabelSize(0.035);
    h_prefit->GetYaxis()->SetTitleSize(0.035);
    h_prefit->GetYaxis()->SetTitleOffset(1);
    h_prefit->GetXaxis()->SetTitle("");
    h_prefit->GetYaxis()->SetTitle("Parameter pull, n#sigma");
    h_prefit_2->SetLineStyle(1);
    h_prefit_2->SetLineWidth(1);
    h_prefit_2->SetLineColor(prefit_line);
    h_prefit->SetMarkerStyle(0);
    h_prefit->SetLineColor(prefit_line);
    h_prefit->SetFillColor(prefit_color);
    h_prefit->SetLineWidth(1);
    h_prefit->SetFillStyle(prefit_style);

    for(unsigned int i = 0; i < lines_sbnd.size(); ++i){
      if(i == 0){
        lines_sbnd[i].SetY2(maxiny+0.05);
        lines_sbnd[i].SetY1(mininy-0.02);
        lines_uboone[i].SetY2(maxiny+0.05);
        lines_uboone[i].SetY1(mininy-0.02);
        lines_icarus[i].SetY2(maxiny+0.05);
        lines_icarus[i].SetY1(mininy-0.02);
      }
      else{
        lines_sbnd[i].SetY1(mininy-0.02);
        lines_sbnd[i].SetY2(maxiny);
        lines_uboone[i].SetY1(mininy-0.02);
        lines_uboone[i].SetY2(maxiny);
        lines_icarus[i].SetY1(mininy-0.02);
        lines_icarus[i].SetY2(maxiny);
      }
      lines_sbnd[i].Draw("same");
      lines_uboone[i].Draw("same");
      lines_icarus[i].Draw("same");
    }
    line_moddet.SetY2(maxiny+0.05);
    line_moddet.SetY1(mininy-0.02);
    line_moddet.Draw("same");

    line_propmod.SetY2(maxiny+0.05);
    line_propmod.SetY1(mininy-0.02);
    line_propmod.Draw("same");

    line_fluxspline.SetY2(maxiny+0.05);
    line_fluxspline.SetY1(mininy-0.02);
    line_fluxspline.Draw("same");

    FormatLatex(0,           singleFlux,  1,maxiny*1.05,"#color[867]{SBND Flux}");
    FormatLatex(singleFlux,  singleFlux*2,1,maxiny*1.05,"#color[905]{#muBooNE Flux}");
    FormatLatex(singleFlux*2,nFluxRows,   1,maxiny*1.05,"#color[797]{ICARUS Flux}");
    FormatLatex(nFluxRows,   nCumFluxRows,1,maxiny*1.05,"#color[397]{Flux}");
    FormatLatex(nCumFluxRows,nCumPropRows,1,maxiny*1.05,"#color[835]{Prop. #sigma}");
    FormatLatex(nCumPropRows,nCumMECRows, 1,maxiny*1.05,"#color[923]{Modern #sigma}");
    if(detector_systematics)
      FormatLatex(nCumMECRows,nCumMECRows+nDetRows,1,maxiny*1.05,"#color[820]{Detector}");

    c->SetGridy();
    c->Update();
    c->Draw();
    c->SaveAs(("prefit-only_nuisance_params_mdc_"+name+"_"+sample+tag+".root").c_str());
    c->Clear();

  }
}
void FormatLatex(const double &b, const double &e, const double &w, const double &y, const char *s){
  // Setup the Latex object
  TLatex l(0,0,s);
  l.SetTextAlign(11); // Align at bottom
  l.SetTextSize(0.03);

  // Get the positioning
  double x = 0;
  // Get the length of the Latex in the pad
  double l_length = l.GetXsize()*w;

  // Get the centre of the bins
  double c = (e-b);

  // Set the x-position of the latex to be half it's length left of the centre
  x = b+((c/2.)-(l_length/2.));
  
  // Asthetics
  l.DrawLatex(x,y,s);
}
