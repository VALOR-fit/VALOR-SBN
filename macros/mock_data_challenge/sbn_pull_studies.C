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

#include <iostream>
#include <fstream>
#include "TPaveStats.h"

std::vector<std::string> params_tex =
{
  "f_{M_{A}^{CCQE}}",
  "f_{M_{A}^{CCRes}}",
  "f_{nR_{#nu n}^{CC1#pi}}",
  "f_{nR_{#nu p}^{NC2#pi}}",
  "f_{B_{HT}}",
  "f_{R^{Abs}_{#pi}}",
  "f_{R^{Inel}_{N}}",
  "f_{M_{V}^{NCRes}}",
  "f_{SkinEffect}",
  "f_{#sigma_{QE}^{N}}",
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
  91,
  595,
  633,
  210,
  618,
  802,
  859,
  835,
  903,
  886,
  211,
};

//int true_color = TColor::GetFreeColorIndex();
//int inc_color = TColor::GetFreeColorIndex();
int inc_color = 9358;
//int exc_color = TColor::GetFreeColorIndex();
int exc_color = 9369;

short true_color = kPink-7;
//short inc_color  = kAzure+5;
auto inc_color_set  = new TColor(inc_color, 0., 0.45, 0.7);
short inc_line   = kAzure-1;
//short exc_color  = kMagenta-3;
auto exc_color_set  = new TColor(exc_color, 0.9, 0.6, 0.);
short exc_line   = kOrange+2;

int inc_style  = 3017; 
int exc_style  = 3018; 

int inc_line_style  = 7; 
int exc_line_style  = 1; 

int true_marker = 21; 
int inc_marker  = 22; 
int exc_marker  = 23; 

std::string FixName(const std::string &name);
void FormatComparisonHists(TH1D* h_inc, TH1D *h_exc, const std::string &xlabel = "");
void SetupStats(TPaveStats *st_inc, TPaveStats *st_exc);

using namespace valor;
using namespace valor::conv;

void sbn_pull_studies(const char * inc_filename,
                      const char * exc_filename,
		      std::string tag1 = "SBND", 
		      std::string tag2 = "PRISM3", 
                      std::string  inputs = "", // Input covariance from the fits
                      const int ntoys = 1, // Number of toys to plot from the output, default only 1, if [-1] run number in file
                      std::string  output_tag = "") 
{

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

  // SBND input file path
  if(dollarinc != std::string::npos){
    expandedpathinc = valor::util::file::GetFilename(fullpathinc);
  }
  else
    expandedpathinc = fullpathinc;

  // PRISM3 input file path
  if(dollarexc != std::string::npos){
    expandedpathexc = valor::util::file::GetFilename(fullpathexc);
  }
  else
    expandedpathexc = fullpathexc;

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

  if(ntoys > 50){
    int n = ntoys;
    std::cout << " Are you sure you want to draw more than 50 individual plots? " << std::endl;
    std::cout << " If not, reduce ntoys. All universes will still contribute to the comparison histogram" << std::endl;
    std::cout << " Please enter the number of histograms you'd like to plot: ";
    std::cin >> n;
    ntorun = n;
    if(ntorun >= ntoys)
      std::cout << " You're sticking with it, fair enough!" << std::endl;
    else
      std::cout << " You've chosen to reduce the number, probably a good idea" << std::endl;
  }
  if(ntorun == 0){
    std::cerr << " Error: Running over 0 toys, this is a bit pointless..." << std::endl;
    util::Die(-1);
  }

  // Setup things which don't need to be defined in every toymc
  // Pull plot legends
  TLegend *l_bestfit = new TLegend(0.063,0.92,0.98,0.999);
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

  TFile *f_outputs = new TFile(("pull_studies"+tag+".root").c_str(),"RECREATE");
  f_outputs->cd();

  // Histograms to hold the comparisons between true and postfit values
  TH1D *h_true_inc = new TH1D("h_true_inc","",100,-3,3);
  TH1D *h_true_exc = new TH1D("h_true_exc","",100,-3,3);

  // Histograms to overlay the fit statistics
  TH1D *h_stat_inc    = new TH1D("h_stat_inc","",60,0,30);
  TH1D *h_stat_exc    = new TH1D("h_stat_exc","",60,0,30);
  TH1D *h_perndof_inc = new TH1D("h_perndof_inc","",60,0,3);
  TH1D *h_perndof_exc = new TH1D("h_perndof_exc","",60,0,3);

  std::vector<TH1D*> h_comparisons_inc;
  std::vector<TH1D*> h_comparisons_exc;
  std::vector<TH1D*> h_chisq_inc;
  std::vector<TH1D*> h_chisq_exc;
  for(unsigned int h = 0; h < params_tex.size(); ++h){
    h_comparisons_inc.push_back(new TH1D(("h_true_inc_"+params.at(h)).c_str(),"",60,-3,3));
    h_comparisons_exc.push_back(new TH1D(("h_true_exc_"+params.at(h)).c_str(),"",60,-3,3));
    h_chisq_inc.push_back(new TH1D(("h_chisq_inc_"+params.at(h)).c_str(),"",60,-3,3));
    h_chisq_exc.push_back(new TH1D(("h_chisq_exc_"+params.at(h)).c_str(),"",60,-3,3));
  }


  // Counters to determine the percentage of the time the fit gets the true value within the error
  // Repeat for all parameters individually and then sum for the total
  std::vector<unsigned int> correct_inc(params.size(),0);
  std::vector<unsigned int> correct_exc(params.size(),0);

  TString pdf_filename(("pull_studies"+tag+".pdf").c_str());

  unsigned int ndof_inc = 0;
  unsigned int ndof_exc = 0;

  // Loop over number of toys run in the fit
  for(int i=0; i<nentries; i++) {
//  for(int i=0; i<12; i++) {
    std::cout << " Running entry " << i << '\r' << flush;

    fitnt_inc->GetEntry(i);
    fitnt_exc->GetEntry(i);

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

    unsigned int totalNumParams_inc = gbfparm_inc->GetNumberParameters();
    unsigned int freeParams_inc     = gbfparm_inc->GetNumberFreeParameters();
    unsigned int totalNumParams_exc = gbfparm_exc->GetNumberParameters();
    unsigned int freeParams_exc     = gbfparm_exc->GetNumberFreeParameters();
    unsigned int nuisanceParams     = 0;

    // NDOF = total number of parameters - number of fixed parameters
    //ndof_inc = freeParams_inc;
    //ndof_exc = freeParams_exc;
    //std::cout<<"ndof_inc = "<<ndof_inc<<", ndof_exc = "<<ndof_exc<<std::endl;
    ndof_inc = 21;
    ndof_exc = 21;
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
    if(inclusive_errors.size() != totalNumParams_inc) 
      std::cout << " Error: The number of parameters and errors don't match. Params : " << totalNumParams_inc << " vs. errors: " << inclusive_errors.size() << std::endl;

    const std::string name_input     = "h_input_"+std::to_string(i);
    const std::string name_inclusive = "h_inclusive_"+std::to_string(i);
    const std::string name_exclusive = "h_exclusive_"+std::to_string(i);

    TH1D *h_input     = new TH1D(name_input.c_str(),     "", nRows-nPhysicsParams, 0, nRows-nPhysicsParams);
    TH1D *h_inclusive = new TH1D(name_inclusive.c_str(), "", nRows-nPhysicsParams, 0, nRows-nPhysicsParams);
    TH1D *h_exclusive = new TH1D(name_exclusive.c_str(), "", nRows-nPhysicsParams, 0, nRows-nPhysicsParams);

    unsigned int nuisance_it = 0;

    for(unsigned int j = 0; j < totalNumParams_inc; ++j){
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

      // Pull comparisons
      h_true_inc->Fill(inclusive_bin_content-input_bin_content);
      h_true_exc->Fill(exclusive_bin_content-input_bin_content);
      h_comparisons_inc.at(j)->Fill(inclusive_bin_content-input_bin_content);
      h_comparisons_exc.at(j)->Fill(exclusive_bin_content-input_bin_content);
      h_chisq_inc.at(j)->Fill((inclusive_bin_content-input_bin_content)/static_cast<double>(inclusive_errors.at(j)));
      h_chisq_exc.at(j)->Fill((exclusive_bin_content-input_bin_content)/static_cast<double>(exclusive_errors.at(j)));

      // Now check if the true value sits within each of the errors and add to the counters if necessary
      if(input_bin_content >= (inclusive_bin_content-inclusive_errors.at(j)) && input_bin_content <= (inclusive_bin_content+inclusive_errors.at(j)))
        correct_inc.at(j)++;
      if(input_bin_content >= (exclusive_bin_content-exclusive_errors.at(j)) && input_bin_content <= (exclusive_bin_content+exclusive_errors.at(j)))
        correct_exc.at(j)++;

      // Prefit bin content is always 0 in order to only demonstrate the error in each bin
      h_input->SetBinContent(nuisanceBin,     input_bin_content);
      h_inclusive->SetBinContent(nuisanceBin, inclusive_bin_content);
      h_exclusive->SetBinContent(nuisanceBin, exclusive_bin_content);
      h_inclusive->SetBinError(nuisanceBin,   inclusive_bin_error);
      h_exclusive->SetBinError(nuisanceBin,   exclusive_bin_error);

      std::string label = "#color["+std::to_string(pal.at(j))+"]{"+params_tex.at(j)+"}";
      h_inclusive->GetXaxis()->SetBinLabel(nuisanceBin,label.c_str());
    }
    // Fit statistic comparisons
    h_stat_inc->Fill(gbfparm_inc->GetBestFitStatistic());
    h_stat_exc->Fill(gbfparm_exc->GetBestFitStatistic());
    h_perndof_inc->Fill(gbfparm_inc->GetBestFitStatistic()/static_cast<double>(ndof_inc));
    h_perndof_exc->Fill(gbfparm_exc->GetBestFitStatistic()/static_cast<double>(ndof_exc));

    // If we have reached the limit of universes to plot individually, move onto the next one
    if(i >= ntorun) continue;
    
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

    // Setup canvas for pull comparisons in this universe
    std::string pull_canv_name = "c_"+std::to_string(i);
    TCanvas *c = new TCanvas(pull_canv_name.c_str(),"",0,20,1350,1080);

    // New canvas features 
    c->SetLeftMargin   (0.07); 
    c->SetRightMargin  (0.008);
    c->SetBottomMargin (0.187);
    c->SetTopMargin    (0.08);
    gStyle->SetEndErrorSize(4);

    h_inclusive->GetYaxis()->SetRangeUser(-5,5);
    h_inclusive->Draw("E1 X0");
    h_exclusive->Draw("same E1 X0");
    h_input->Draw("same p");

    h_inclusive->GetXaxis()->LabelsOption("v");
    h_inclusive->GetXaxis()->SetLabelSize(0.08);
    h_inclusive->GetXaxis()->SetLabelFont(132);
    h_inclusive->GetYaxis()->SetLabelSize(0.045);
    h_inclusive->GetYaxis()->SetLabelFont(132);
    h_inclusive->GetYaxis()->SetTitleSize(0.055);
    h_inclusive->GetYaxis()->SetTitleFont(132);
    h_inclusive->GetYaxis()->SetTitleOffset(0.6);
    h_inclusive->GetYaxis()->SetMaxDigits(3);
    h_inclusive->GetXaxis()->SetTitle("");
    h_inclusive->GetYaxis()->SetTitle("Parameter pull [#sigma]");
    h_inclusive->SetLineColor(inc_color);
    h_inclusive->SetLineWidth(2);
    h_inclusive->SetMarkerStyle(inc_marker);
    h_inclusive->SetMarkerColor(inc_color);
    h_inclusive->SetMarkerSize(1.5);

    h_exclusive->SetLineColor(exc_color);
    h_exclusive->SetLineWidth(2);
    h_exclusive->SetMarkerStyle(exc_marker);
    h_exclusive->SetMarkerColor(exc_color);
    h_exclusive->SetMarkerSize(1.5);

    h_input->SetMarkerColor(true_color);
    h_input->SetMarkerStyle(true_marker);

    l_bestfit->AddEntry(h_input,("#color["+std::to_string(true_color)+"]{True value}").c_str(), "p");
    l_bestfit->AddEntry(h_inclusive,("#color["+std::to_string(inc_color)+"]{"+tag1+" postfit value}").c_str(), "ep");
    l_bestfit->AddEntry(h_exclusive,("#color["+std::to_string(exc_color)+"]{"+tag2+" postfit value}").c_str(), "ep");
    l_bestfit->Draw("same");
    c->SetGridx();
    c->SetGridy();
    c->Update();
    c->Draw();
    c->Write();
    
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

    c->SaveAs(("pngs/pull_studies_universe_"+std::to_string(i)+tag+".png").c_str());
    c->SaveAs(("pdfs/pull_studies_universe_"+std::to_string(i)+tag+".pdf").c_str());
    c->Clear();
    l_bestfit->Clear();
  }
  std::cout << std::endl;
  
  // Now for the global comparison
  // Pull comparison canvas and legend
  TCanvas *c_comp = new TCanvas("c_comp","",20,20,880,900);
  c_comp->SetTopMargin(0.06);
  c_comp->SetBottomMargin(0.12);
  c_comp->SetLeftMargin(0.14);
  c_comp->SetRightMargin(0.025);
    
  FormatComparisonHists(h_true_inc,h_true_exc);
  gStyle->SetOptStat(1111);

  TLegend *l_comp = new TLegend(0.27,0.94,0.99,0.98);
  l_comp->SetNColumns(2);
  l_comp->SetBorderSize(0);
  l_comp->SetFillStyle(0);
  l_comp->SetTextFont(132);
  l_comp->SetTextSize(0.05);

  double max_comp_y = std::max(h_true_inc->GetMaximum(),h_true_exc->GetMaximum());
  h_true_exc->GetYaxis()->SetRangeUser(0.,max_comp_y*1.1);
  h_true_inc->SetName(("#color["+std::to_string(inc_color)+"]{"+tag1+"}").c_str());
  h_true_exc->SetName(("#color["+std::to_string(exc_color)+"]{"+tag2+"}").c_str());
  //h_true_inc->SetLineStyle(7);
  h_true_exc->Draw("hist");
  h_true_inc->Draw("sames hist");
  h_true_inc->SetStats(1);
  h_true_exc->SetStats(1);
  c_comp->Update();

  TPaveStats *st_inc = static_cast<TPaveStats*>(h_true_inc->FindObject("stats"));
  TPaveStats *st_exc = static_cast<TPaveStats*>(h_true_exc->FindObject("stats"));

  SetupStats(st_inc,st_exc);
  
  c_comp->Modified();

  l_comp->AddEntry(h_true_inc, ("#color["+std::to_string(inc_color)+"]{"+tag1+"}").c_str(), "l");
  l_comp->AddEntry(h_true_exc, ("#color["+std::to_string(exc_color)+"]{"+tag2+"}").c_str(), "l");
  l_comp->Draw();

  TLatex latex;
  latex.SetTextAlign(11);
  latex.SetTextSize(0.06);
  latex.SetTextColor(611);
  latex.DrawLatex(-2.56,max_comp_y,"All parameters");

  c_comp->SaveAs(("pngs/comparison_all_parameters"+tag+".png").c_str());
  c_comp->SaveAs(("pdfs/comparison_all_parameters"+tag+".pdf").c_str());
  c_comp->SaveAs(("pdfs/comparison_all_parameters"+tag+".eps").c_str());
  c_comp->Write();
  c_comp->Clear();
  l_comp->Clear();

  // Now plot the individual parameter histograms
  for(unsigned int p = 0; p < params_tex.size(); ++p){
    TH1D *h_inc(h_comparisons_inc.at(p));
    TH1D *h_exc(h_comparisons_exc.at(p));

    FormatComparisonHists(h_inc,h_exc);
    
    max_comp_y = std::max(h_inc->GetMaximum(),h_exc->GetMaximum());
    h_exc->GetYaxis()->SetRangeUser(0.,max_comp_y*1.1);
    h_inc->SetName(("#color["+std::to_string(inc_color)+"]{"+tag1+"}").c_str());
    h_exc->SetName(("#color["+std::to_string(exc_color)+"]{"+tag2+"}").c_str());
    h_exc->Draw("hist");
    h_inc->Draw("sames hist");
    h_inc->SetStats(1);
    h_exc->SetStats(1);
    c_comp->Update();

    TPaveStats *st_param_inc = static_cast<TPaveStats*>(h_inc->FindObject("stats"));
    TPaveStats *st_param_exc = static_cast<TPaveStats*>(h_exc->FindObject("stats"));

    SetupStats(st_param_inc,st_param_exc);
    
    c_comp->Modified();

    TLatex latex1;
    latex1.SetTextAlign(11);
    latex1.SetTextSize(0.06);
    latex1.SetTextColor(pal.at(p));
    latex1.DrawLatex(-2.56,max_comp_y,params_tex.at(p).c_str());

    l_comp->AddEntry(h_inc, ("#color["+std::to_string(inc_color)+"]{"+tag1+"}").c_str(), "l");
    l_comp->AddEntry(h_exc, ("#color["+std::to_string(exc_color)+"]{"+tag2+"}").c_str(), "l");
    l_comp->Draw();

    c_comp->SaveAs(("pngs/comparison_parameter_"+params.at(p)+tag+".png").c_str());
    c_comp->SaveAs(("pdfs/comparison_parameter_"+params.at(p)+tag+".pdf").c_str());
    c_comp->Write(("c_comp_"+params.at(p)).c_str());
    c_comp->Clear();
    l_comp->Clear();
    
    // Chisq version
    TH1D *h_chi_inc(h_chisq_inc.at(p));
    TH1D *h_chi_exc(h_chisq_exc.at(p));

    FormatComparisonHists(h_chi_inc,h_chi_exc,"(Pull_{Bestfit} - Pull_{True}) / #sigma_{Bestfit}");
    
    max_comp_y = std::max(h_chi_inc->GetMaximum(),h_chi_exc->GetMaximum());
    h_chi_exc->GetYaxis()->SetRangeUser(0.,max_comp_y*1.1);
    h_chi_inc->SetName(("#color["+std::to_string(inc_color)+"]{"+tag1+"}").c_str());
    h_chi_exc->SetName(("#color["+std::to_string(exc_color)+"]{"+tag2+"}").c_str());
    h_chi_exc->Draw("hist");
    h_chi_inc->Draw("sames hist");
    h_chi_inc->SetStats(1);
    h_chi_exc->SetStats(1);
    c_comp->Update();

    TPaveStats *st_param_chisq_inc = static_cast<TPaveStats*>(h_chi_inc->FindObject("stats"));
    TPaveStats *st_param_chisq_exc = static_cast<TPaveStats*>(h_chi_exc->FindObject("stats"));

    SetupStats(st_param_chisq_inc,st_param_chisq_exc);
    
    c_comp->Modified();

    latex1.DrawLatex(-2.56,max_comp_y,params_tex.at(p).c_str());

    l_comp->AddEntry(h_chi_inc, ("#color["+std::to_string(inc_color)+"]{"+tag1+"}").c_str(), "l");
    l_comp->AddEntry(h_chi_exc, ("#color["+std::to_string(exc_color)+"]{"+tag2+"}").c_str(), "l");
    l_comp->Draw();

    c_comp->SaveAs(("pngs/chisq_parameter_"+params.at(p)+tag+".png").c_str());
    c_comp->SaveAs(("pdfs/chisq_parameter_"+params.at(p)+tag+".pdf").c_str());
    c_comp->Write(("c_comp_chisq_"+params.at(p)).c_str());
    c_comp->Clear();
    l_comp->Clear();
  }
  // Now plot the fit statistic
  FormatComparisonHists(h_stat_inc,h_stat_exc, "Fit statistic");
  max_comp_y = std::max(h_stat_inc->GetMaximum(),h_stat_exc->GetMaximum());
  h_stat_exc->GetYaxis()->SetRangeUser(0.,max_comp_y*1.1);
  h_stat_inc->SetName(("#color["+std::to_string(inc_color)+"]{"+tag1+"}").c_str());
  h_stat_exc->SetName(("#color["+std::to_string(exc_color)+"]{"+tag2+"}").c_str());
  h_stat_exc->Draw("hist");
  h_stat_inc->Draw("sames hist");
  h_stat_inc->SetStats(1);
  h_stat_exc->SetStats(1);
  c_comp->Update();

  TPaveStats *st_stat_inc = static_cast<TPaveStats*>(h_stat_inc->FindObject("stats"));
  TPaveStats *st_stat_exc = static_cast<TPaveStats*>(h_stat_exc->FindObject("stats"));

  SetupStats(st_stat_inc,st_stat_exc);

  c_comp->Modified();

  l_comp->AddEntry(h_stat_inc, ("#color["+std::to_string(inc_color)+"]{"+tag1+"}").c_str(), "l");
  l_comp->AddEntry(h_stat_exc, ("#color["+std::to_string(exc_color)+"]{"+tag2+"}").c_str(), "l");
  l_comp->Draw();

  c_comp->SaveAs(("pngs/comparison_fit_statistic"+tag+".png").c_str());
  c_comp->SaveAs(("pdfs/comparison_fit_statistic"+tag+".pdf").c_str());
  c_comp->Write("c_comp_stat");
  c_comp->Clear();
  l_comp->Clear();

  FormatComparisonHists(h_perndof_inc,h_perndof_exc, "Fit statistic / NDOF");
  h_perndof_exc->GetYaxis()->SetRangeUser(0.,max_comp_y*1.1);
  h_perndof_inc->SetName(("#color["+std::to_string(inc_color)+"]{"+tag1+"}").c_str());
  h_perndof_exc->SetName(("#color["+std::to_string(exc_color)+"]{"+tag2+"}").c_str());
  h_perndof_exc->Draw("hist");
  h_perndof_inc->Draw("sames hist");
  h_perndof_inc->SetStats(1);
  h_perndof_exc->SetStats(1);
  c_comp->Update();

  TPaveStats *st_perndof_inc = static_cast<TPaveStats*>(h_perndof_inc->FindObject("stats"));
  TPaveStats *st_perndof_exc = static_cast<TPaveStats*>(h_perndof_exc->FindObject("stats"));

  SetupStats(st_perndof_inc,st_perndof_exc);

  c_comp->Modified();

  l_comp->AddEntry(h_perndof_inc, ("#color["+std::to_string(inc_color)+"]{"+tag1+"}").c_str(), "l");
  l_comp->AddEntry(h_perndof_exc, ("#color["+std::to_string(exc_color)+"]{"+tag2+"}").c_str(), "l");
  l_comp->Draw();

  c_comp->SaveAs(("pngs/comparison_fit_statistic_per_ndof"+tag+".png").c_str());
  c_comp->SaveAs(("pdfs/comparison_fit_statistic_per_ndof"+tag+".pdf").c_str());
  c_comp->Write("c_comp_stat_perndof");
  c_comp->Clear();
  l_comp->Clear();

  f_outputs->Close();

  // Now the stats:
  ofstream file;
  file.open(("rates"+tag+"_2.txt").c_str());
  file << std::endl;
  file << " Rate of fits which find the true systematic value to within the postfit uncertainty: " << std::endl;
  file << std::endl;
  file << std::setw(16) << "Parameter" << std::setw(16) << tag1 << std::setw(16) << tag2 << std::endl;
  unsigned int total_correct_inc = 0;
  unsigned int total_correct_exc = 0;
  for(unsigned int i = 0; i < params.size(); ++i){
    total_correct_inc += correct_inc.at(i);
    total_correct_exc += correct_exc.at(i);
    file << std::setw(16) << params.at(i) << std::setw(16) << correct_inc.at(i) << std::setw(16) << correct_exc.at(i) << std::endl;
  }
  file << std::endl;
  file << std::setw(16) << "Total " << std::setw(16) << total_correct_inc << std::setw(16) << total_correct_exc << std::endl;
  file << std::endl;
  file << " Total number of fits: " << nentries << std::endl;
  file << std::endl;
  file.close();
}

std::string FixName(const std::string &name){
  TString t_name(name);
  t_name.ReplaceAll("genie_","");
  t_name.ReplaceAll("_Genie","");
  t_name.ReplaceAll("_FluxUnisim","");
  return std::string(t_name.Data());
}

void FormatComparisonHists(TH1D* h_inc, TH1D *h_exc, const std::string &xlabel = ""){
  h_exc->GetXaxis()->SetLabelSize(0.055);
  h_exc->GetXaxis()->SetLabelFont(132);
  h_exc->GetXaxis()->SetTitleSize(0.055);
  h_exc->GetXaxis()->SetTitleFont(132);
  h_exc->GetXaxis()->SetTitleOffset(1);
  h_exc->GetYaxis()->SetLabelSize(0.055);
  h_exc->GetYaxis()->SetLabelFont(132);
  h_exc->GetYaxis()->SetTitleSize(0.055);
  h_exc->GetYaxis()->SetTitleFont(132);
  h_exc->GetYaxis()->SetTitleOffset(1.3);
  h_exc->GetYaxis()->SetMaxDigits(3);
  if(xlabel == "")
    h_exc->GetXaxis()->SetTitle("Pull_{Bestfit} - Pull_{True}, [#sigma]");
  else
    h_exc->GetXaxis()->SetTitle(xlabel.c_str());
  h_exc->GetYaxis()->SetTitle("Number of toys");
  h_inc->SetLineColor(inc_color);
  h_exc->SetLineColor(exc_color);
  h_inc->SetLineStyle(inc_line_style);
  h_exc->SetLineStyle(exc_line_style);
  h_inc->SetLineWidth(2);
  h_exc->SetLineWidth(2);
}
void SetupStats(TPaveStats *st_inc, TPaveStats *st_exc){
  st_inc->SetX1NDC(0.68);
  st_inc->SetX2NDC(0.95);
  st_inc->SetY1NDC(0.72);
  st_inc->SetY2NDC(0.90);
  st_exc->SetX1NDC(0.68);
  st_exc->SetX2NDC(0.95);
  st_exc->SetY1NDC(0.50);
  st_exc->SetY2NDC(0.68);
  st_inc->SetTextFont(132);
  st_exc->SetTextFont(132);
  st_inc->SetTextSize(0.036);
  st_exc->SetTextSize(0.036);
  st_inc->SetTextColor(inc_color);
  st_exc->SetTextColor(exc_color);
  st_inc->SetLineColor(0);
  st_exc->SetLineColor(0);
  st_inc->SetBorderSize(0);
  st_exc->SetBorderSize(0);
  st_inc->SetStatFormat("1.2g");
  st_exc->SetStatFormat("1.2g");
}
