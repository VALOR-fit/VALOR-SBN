//
//------------------------------------------------------
// Macro to plot prefit systematic errors
// and posfit systematic paramter pulls
// Modified for the mock data analysis which only
// fits the ND data so don't want to present uB/FD
// flux tweaks
//
// Rhiannon Jones
// May 2020
//------------------------------------------------------
//

void FormatLatex(const double &b, const double &e, const double &w, const double &y, const char *s, const bool &thesis);

using namespace valor;
using namespace valor::conv;
namespace vutil = valor::util;

void sbn_param_pulls_ratio(const std::string &config,
                           const std::string &filename, 
                           const std::string &tag = "",
                           const bool &thesis=true)
{
  std::ofstream outputFile1(("postfit_errors_"+tag+".txt").c_str());
  std::ofstream outputFile2(("postfit_errors_allflux_"+tag+".txt").c_str());
  std::ofstream outputFile3(("postfit_errors_int_"+tag+".txt").c_str());
  std::vector<double> vec_postfit, vec_postfit_allflux, vec_postfit_int;
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

  int postfit_color = kPink+4;
  int postfit_line  = kPink+2;
  int postfit_style = 3002; // Solid;

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

  // First build a FitElements so we can get information about the systematics
  std::string config_path = vutil::CompleteConfigPath(config);
  CompoundFitElements elems;
  elems.Read(config_path.c_str(),"nomc nosplines");
  FitModelABC * modelabc = elems.FitModel();
  CompoundFitModel & model = *dynamic_cast<CompoundFitModel*>(modelabc);
  CorrelatedSystematics * syst = model.GetSystematics();
  const util::NameRegistry * nr = util::NameRegistry::Instance();
 
  //  TCanvas *c = new TCanvas("c","",0,20,1850,600);
  TCanvas *c = new TCanvas("c","",0,20,1380,800);

  TLegend *l_bestfit = new TLegend(0.63,0.68,0.88,0.88);
  l_bestfit->SetBorderSize(0);
  fitnt->GetEntry(0);

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
  unsigned int nPhysicsParams = 0;

  // Full postfit matrix
  TMatrixDSym &cov = *gbfparm->GetCovMatrix();
  std::vector<double> postfit_errors, prefit_errors;

  int nRows = cov.GetNrows();

  // All flux
  int nFluxRows       = util::GetParameterSet("flux").size();
  int nFluxSplineRows = util::GetParameterSet("flux_uncorr").size();

  // Single detector covariance rows
  int nFluxCovRows     = (nFluxRows-nFluxSplineRows)/3.;

  // Now get just the numu entries
  int nFluxCovNumuRows = util::GetParameterSet("ndfluxnumu").size();

  // Redefine for no MicroBooNE & ICARUS or other neutrino flavours
  int nFluxSBNDRows   = nFluxCovNumuRows+nFluxSplineRows;

  int nPropRows       = util::GetParameterSet("proposal").size();
  int nModRows        = util::GetParameterSet("modern").size();
  int nMECRows        = 1;
  int nSBNRows        = util::GetParameterSet("migration").size()+util::GetParameterSet("energy").size();
  int nDetRows        = util::GetParameterSet("detector").size();

  // Now add them up in such a way that we define the right locations for the lines
  int nCumFluxRows = nFluxSBNDRows;
  int nCumPropRows = nCumFluxRows+nPropRows;
  int nCumModRows  = nCumPropRows+nModRows;
  int nCumMECRows  = nCumModRows+nMECRows;
  int nCumSBNRows  = nCumMECRows+nSBNRows;
  int nCumDetRows  = nCumSBNRows+nDetRows;

  float total_postfit = 0.;

  for(int j = 0; j < nRows; ++j){
    if(!gbfparm->IsNuisanceByIndex(j)){
      nPhysicsParams++;
      std::cout << " Physics parameter not nuisance parameter: " << gbfparm->NameByIndex(j) << std::endl;
      continue;
    }
    // Skip the MicroBooNE and ICARUS entries 
    if((j-nPhysicsParams) >= nFluxCovNumuRows && (j-nPhysicsParams) < nFluxCovRows*3) continue;
    postfit_errors.push_back(sqrt(cov(j,j)));
    total_postfit += cov(j,j);
    nuisanceParams++;
  }
  total_postfit = sqrt(total_postfit);

  // Get the prefit errors to scale by
  for(int j = 0; j < syst->Size(); ++j){
    // Skip the MicroBooNE and ICARUS entries and non-numu
    if(j >= nFluxCovNumuRows && j < nFluxCovRows*3) continue;
    PhysParamId_t param = nr->PhysParamFromString(gbfparm->NameByIndex(nPhysicsParams+j));
    prefit_errors.push_back(syst->OneSigmaError(param));
  }

  std::cout << " ====================================================== " << std::endl;
  std::cout << " Error on the number of predicted events: +/- "           << total_postfit << std::endl;
  std::cout << " ====================================================== " << std::endl;

  unsigned int nuisanceParamsOfInterest = totalNumParams-nPhysicsParams-(nFluxCovRows*3-nFluxCovNumuRows);
  if(postfit_errors.size() != nuisanceParamsOfInterest) 
    std::cout << " Error: The number of parameters and errors don't match. Params : " << nuisanceParamsOfInterest << " vs. errors: " << postfit_errors.size() << std::endl;

  const char *name_postfit = "h_postfit";

  // New canvas features 
  if(thesis){
    c->SetTopMargin    (0.18);
    c->SetLeftMargin   (0.01);
    c->SetRightMargin  (0.055);
    c->SetBottomMargin (0.32);
  }
  else{
    c->SetLeftMargin   (0.055);
    c->SetRightMargin  (0.01);
    c->SetBottomMargin (0.32);
    c->SetTopMargin    (0.06);
  }

  TH1D *h_postfit = new TH1D(name_postfit, "", nuisanceParamsOfInterest, 0, nuisanceParamsOfInterest);

  unsigned int nuisance_it = 0;
  unsigned int printing_it = 1;

  for(unsigned int j = 0; j < totalNumParams; ++j){
    if(!gbfparm->IsNuisanceByIndex(j)){
      std::cout << " Physics parameter not nuisance parameter: " << gbfparm->NameByIndex(j) << std::endl;
      continue;
    }
    if((j-nPhysicsParams) >= nFluxCovNumuRows && (j-nPhysicsParams) < nFluxCovRows*3) continue;

    int nuisanceBin = nuisance_it+1;

    double postfit_bin_content = 0.;
    double postfit_bin_error   = 0.;

    // Convert to units of nsigma (postfit)
    postfit_bin_content = (gbfparm->BestFitValueByIndex(j)-gbfparm->InitValueByIndex(j))/static_cast<double>(prefit_errors.at(nuisance_it));
    postfit_bin_error   = postfit_errors.at(nuisance_it)/static_cast<double>(prefit_errors.at(nuisance_it));

    // Prefit bin content is always 0 in order to only demonstrate the error in each bin
    h_postfit->SetBinContent(nuisanceBin, postfit_bin_content);
    h_postfit->SetBinError(nuisanceBin,   postfit_bin_error);
    
    vec_postfit.push_back(postfit_bin_error);
    if(j<=27){
      vec_postfit_allflux.push_back(postfit_bin_error);
    }
    else vec_postfit_int.push_back(postfit_bin_error);
    // Define array of empty flux parameter bins
    // Corresponding to 
    //  bin expt.  flav.
    //  25  SBND   nue00
    /*
    std::vector<int> empties = {25};
    std::vector<int>::iterator it = std::find(empties.begin(),empties.end(),nuisanceBin); 
    if(it != empties.end()){
      h_postfit->SetBinError(nuisanceBin, 0);
    }*/
    const PhysParamId_t param = nr->PhysParamFromString(gbfparm->NameByIndex(j));
    const Parameter & parameter = ParameterPool::Instance()->GetParam(param);

    std::string rawParamLabel = parameter.GetRooTeXName();
    std::string paramLabel(rawParamLabel);
    if(printing_it % 2 == 0){
      paramLabel = rawParamLabel+"                ";
    }
   
    h_postfit->GetXaxis()->SetBinLabel(nuisanceBin,paramLabel.c_str());

    printing_it++;
    nuisance_it++;
  }
  if (outputFile1.is_open()&&outputFile2.is_open()&&outputFile3.is_open()) {
    for (const auto& value : vec_postfit) {
      outputFile1 << value << "\n";
    }
    for (const auto& value : vec_postfit_allflux) {
      outputFile2 << value << "\n";
    }
    for (const auto& value : vec_postfit_int) {
      outputFile3 << value << "\n";
    }
    outputFile1.close();
    outputFile2.close();
    outputFile3.close();
  } else {
    std::cerr << "Failed to open the file for writing." << std::endl;
  } 
  
  double max_error = -999.;
  for(int i = 0; i < h_postfit->GetNbinsX(); ++i){
    if(h_postfit->GetBinError(i) > max_error)
      max_error = h_postfit->GetBinError(i);
  }
  double maxy = (h_postfit->GetMaximum() + max_error)*1.1;
  if(maxy < 0)
    maxy = maxy*0.9;
  else
    maxy = maxy*1.1;

  double miny = (h_postfit->GetMinimum() - max_error)*0.9;
  if(miny > 0)
    miny = miny*0.9;
  else
    miny = miny*1.1;

  //Temporaray for saving
  miny = -5;
  maxy = 5;

  // Solid lines for detector and proposal_xsec separation
  TLine line_nominal   (0, 0, h_postfit->GetNbinsX(), 0);

  TLine line_zero      (0.5            ,  miny-0.025, 0.5            ,  maxy+0.1);
  TLine line_sbnd      (nFluxCovNumuRows, miny-0.025, nFluxCovNumuRows, maxy+0.1);
  TLine line_fluxspline(nCumFluxRows,     miny-0.025, nCumFluxRows,     maxy+0.1);
  TLine line_propmod   (nCumPropRows,     miny-0.025, nCumPropRows,     maxy+0.1);
  TLine line_modsbn    (nCumMECRows,      miny-0.025, nCumMECRows,      maxy+0.1);
  TLine line_sbndet    (nCumSBNRows,      miny-0.025, nCumSBNRows,      maxy+0.1);

  line_nominal.SetLineColor(kGray+2);
  line_nominal.SetLineWidth(1);
  line_nominal.SetLineStyle(2);

  line_zero.SetLineColor(kAzure-5);
  line_zero.SetLineWidth(2);
  line_zero.SetLineStyle(1);

  line_sbnd.SetLineColor(kRed-3);
  line_sbnd.SetLineWidth(2);
  line_sbnd.SetLineStyle(1);

  line_fluxspline.SetLineColor(kTeal-6);
  line_fluxspline.SetLineWidth(2);
  line_fluxspline.SetLineStyle(1);

  line_propmod.SetLineColor(kOrange+2);
  line_propmod.SetLineWidth(2);
  line_propmod.SetLineStyle(1);

  line_modsbn.SetLineColor(kViolet-7);
  line_modsbn.SetLineWidth(2);
  line_modsbn.SetLineStyle(1);

  line_sbndet.SetLineColor(kSpring+4);
  line_sbndet.SetLineWidth(2);
  line_sbndet.SetLineStyle(1);

  if(thesis)
    h_postfit->Draw("E1 X0 Y+");
  else
    h_postfit->Draw("E1 X0");

  h_postfit->SetLineWidth(1);
  gStyle->SetEndErrorSize(4);

  line_nominal.Draw("same");
  line_sbnd.Draw("same");
  line_fluxspline.Draw("same");
  line_propmod.Draw("same");
  if(nSBNRows)
    line_modsbn.Draw("same");
  if(nDetRows)
    line_sbndet.Draw("same");

  h_postfit->GetXaxis()->LabelsOption("v");
  h_postfit->GetXaxis()->SetLabelSize(0.054);
  h_postfit->GetXaxis()->SetTitleSize(0);
  h_postfit->GetXaxis()->SetTitleOffset(2.5);
  h_postfit->GetYaxis()->SetLabelSize(0.04);
  h_postfit->GetYaxis()->SetTitleSize(0.05);
  h_postfit->GetYaxis()->SetTitleOffset(0.5);
  h_postfit->GetXaxis()->SetTickLength(0.01);
  h_postfit->GetYaxis()->SetTickLength(0.01);
  h_postfit->GetYaxis()->SetRangeUser(miny,maxy);
  h_postfit->GetXaxis()->SetTitle("Parameter");
  h_postfit->GetYaxis()->SetTitle("Parameter Pull [#sigma]");
  h_postfit->SetMarkerSize(0.98);
  h_postfit->SetMarkerStyle(23);
  h_postfit->SetMarkerColor(1);
  h_postfit->SetLineColor(1);

  // Sort latex
  if(thesis){
    FormatLatex(0,                nFluxCovNumuRows, h_postfit->GetNbinsX(),maxy*1.05,"#color[855]{#splitline{Hadronic}{Flux}}",thesis);
    FormatLatex(nCumFluxRows,     nCumPropRows,     h_postfit->GetNbinsX(),maxy*1.05,"#color[834]{#splitline{Proposal}{#sigma}}",thesis);
    FormatLatex(nCumPropRows,     nCumMECRows,      h_postfit->GetNbinsX(),maxy*1.05,"#color[802]{#splitline{Modern}{#sigma}}",thesis);
  }
  else{
    FormatLatex(0,                nFluxCovNumuRows, h_postfit->GetNbinsX(),maxy*1.05,"#color[855]{Hadronic Flux}",thesis);
    FormatLatex(nCumFluxRows,     nCumPropRows,     h_postfit->GetNbinsX(),maxy*1.05,"#color[834]{Proposal #sigma}",thesis);
    FormatLatex(nCumPropRows,     nCumMECRows,      h_postfit->GetNbinsX(),maxy*1.05,"#color[802]{Modern #sigma}",thesis);
  }
  FormatLatex(nFluxCovNumuRows, nCumFluxRows,     h_postfit->GetNbinsX(),maxy*1.05,"#color[629]{Flux}",thesis);
  if(nSBNRows)
    FormatLatex(nCumMECRows,nCumMECRows+nSBNRows,h_postfit->GetNbinsX(),maxy*1.05,"#color[873]{SBN}",thesis);
  if(nDetRows)
    FormatLatex(nCumSBNRows,nCumSBNRows+nDetRows,h_postfit->GetNbinsX(),maxy*1.05,"#color[824]{Detector}",thesis);

  //c->SetGridy();
  c->SetGridx();
  c->Update();
  c->Draw();
  c->SaveAs(("postfit-only_nuisance_params_mdc_"+tag+".root").c_str());
  c->SaveAs(("postfit-only_nuisance_params_mdc_"+tag+".png").c_str());
}
void FormatLatex(const double &b, const double &e, const double &w, const double &y, const char *s, const bool &thesis){
  // Setup the Latex object
  TLatex l(0,0,s);
  l.SetTextAlign(11);
  l.SetTextSize(0.04);
  if(thesis){
    l.SetTextAngle(90);
    l.SetTextAlign(13);
  }

  // Get the positioning
  double x = 0;
  
  // Get the length of the Latex in the pad
  double l_length = l.GetYsize()*w*0.5;
  if(!thesis)
    l_length = l.GetXsize()*w;

  // Get the centre of the bins
  double c = (e-b);

  // Set the x-position of the latex to be half it's length left of the centre
  x = b+((c/2.)-(l_length/2.));

  // Asthetics
  l.DrawLatex(x,y,s);
}
