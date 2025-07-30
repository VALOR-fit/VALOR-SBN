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

short true_color = kPink-7;
short ana1_color  = kAzure+5;
short ana2_color  = kMagenta-3;
short ana3_color  = kPink-2;

int ana1_line_style  = 1; 
int ana2_line_style  = 1; 
int ana3_line_style  = 1; 

int true_marker = 21; 
int ana1_marker  = 22; 
int ana2_marker  = 23; 
int ana3_marker  = 33; 

std::string FixName(const std::string &name);
void FormatComparisonHists(TH1D* h_ana1, TH1D *h_ana2, TH1D *h_ana3, const std::string &xlabel = "");
void SetupStats(TPaveStats *st_ana1, TPaveStats *st_ana2, TPaveStats *st_ana3);

using namespace valor;
using namespace valor::conv;

void sbn_pull_studies_3(const char * ana1_filename, 
                      const char * ana2_filename, 
                      const char * ana3_filename, 
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
  std::string fullpathana1     = ana1_filename;
  std::string fullpathana2     = ana2_filename;
  std::string fullpathana3     = ana3_filename;
  std::string expandedpathana1 = "";
  std::string expandedpathana2 = "";
  std::string expandedpathana3 = "";

  std::size_t dollarana1 = fullpathana1.find("$");
  std::size_t dollarana2 = fullpathana2.find("$");
  std::size_t dollarana3 = fullpathana3.find("$");

  // SBND input file path
  if(dollarana1 != std::string::npos){
    expandedpathana1 = valor::util::file::GetFilename(fullpathana1);
  }
  else
    expandedpathana1 = fullpathana1;

  // PRISM3 input file path
  if(dollarana2 != std::string::npos){
    expandedpathana2 = valor::util::file::GetFilename(fullpathana2);
  }
  else
    expandedpathana2 = fullpathana2;

  // PRISM5 input file path
  if(dollarana3 != std::string::npos){
    expandedpathana3 = valor::util::file::GetFilename(fullpathana3);
  }
  else
    expandedpathana3 = fullpathana3;

  // BF params from inclusive and exclusive fits
  FitParamList  *  gbfparm_ana1 = 0; // global best-fit params, analysis1
  FitParamList  *  gbfparm_ana2 = 0; // global best-fit params, analysis2
  FitParamList  *  gbfparm_ana3 = 0; // global best-fit params, analysis3

  // Get ana1 fit results
  TFile f_ana1(expandedpathana1.c_str(), "read");
  TTree * fitnt_ana1 = (TTree*)f_ana1.Get("valor_fit_ntp");
  fitnt_ana1->SetBranchAddress("best_fit_params", &gbfparm_ana1);

  // Get ana2 fit results
  TFile f_ana2(expandedpathana2.c_str(), "read");
  TTree * fitnt_ana2 = (TTree*)f_ana2.Get("valor_fit_ntp");
  fitnt_ana2->SetBranchAddress("best_fit_params", &gbfparm_ana2);

  // Get ana3 fit results
  TFile f_ana3(expandedpathana3.c_str(), "read");
  TTree * fitnt_ana3 = (TTree*)f_ana3.Get("valor_fit_ntp");
  fitnt_ana3->SetBranchAddress("best_fit_params", &gbfparm_ana3);

  // Get the number of toys to construct plots and comparisons for
  int nentries = fitnt_ana1->GetEntries();

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
  l_bestfit->SetNColumns(4);
  l_bestfit->SetBorderSize(0);
  l_bestfit->SetFillStyle(0);
  l_bestfit->SetTextFont(132);

  // Input and proposal_xsec prefit matrices
  TFile f_inputs((inputs).c_str(), "read");

  TMatrixD *input_s    = static_cast<TMatrixD*>(f_inputs.Get("cov"));
  TMatrixD &input_syst = *input_s;

  int nInputRows = input_syst.GetNrows();
  int nInputCols = input_syst.GetNcols();

  TFile *f_outputs = new TFile(("sbnd_prism3_prism5_pull_studies"+tag+".root").c_str(),"RECREATE");
  f_outputs->cd();

  // Histograms to hold the comparisons between true and postfit values
  TH1D *h_true_ana1 = new TH1D("h_true_ana1","",100,-3,3);
  TH1D *h_true_ana2 = new TH1D("h_true_ana2","",100,-3,3);
  TH1D *h_true_ana3 = new TH1D("h_true_ana3","",100,-3,3);

  // Histograms to overlay the fit statistics
  TH1D *h_stat_ana1    = new TH1D("h_stat_ana1","",60,0,30);
  TH1D *h_stat_ana2    = new TH1D("h_stat_ana2","",60,0,30);
  TH1D *h_stat_ana3    = new TH1D("h_stat_ana3","",60,0,30);
  TH1D *h_perndof_ana1 = new TH1D("h_perndof_ana1","",60,0,3);
  TH1D *h_perndof_ana2 = new TH1D("h_perndof_ana2","",60,0,3);
  TH1D *h_perndof_ana3 = new TH1D("h_perndof_ana3","",60,0,3);

  std::vector<TH1D*> h_comparisons_ana1;
  std::vector<TH1D*> h_comparisons_ana2;
  std::vector<TH1D*> h_comparisons_ana3;
  std::vector<TH1D*> h_chisq_ana1;
  std::vector<TH1D*> h_chisq_ana2;
  std::vector<TH1D*> h_chisq_ana3;
  for(unsigned int h = 0; h < params_tex.size(); ++h){
    h_comparisons_ana1.push_back(new TH1D(("h_true_ana1_"+params.at(h)).c_str(),"",60,-3,3));
    h_comparisons_ana2.push_back(new TH1D(("h_true_ana2_"+params.at(h)).c_str(),"",60,-3,3));
    h_comparisons_ana3.push_back(new TH1D(("h_true_ana3_"+params.at(h)).c_str(),"",60,-3,3));
    h_chisq_ana1.push_back(new TH1D(("h_chisq_ana1_"+params.at(h)).c_str(),"",60,-3,3));
    h_chisq_ana2.push_back(new TH1D(("h_chisq_ana2_"+params.at(h)).c_str(),"",60,-3,3));
    h_chisq_ana3.push_back(new TH1D(("h_chisq_ana3_"+params.at(h)).c_str(),"",60,-3,3));
  }


  // Counters to determine the percentage of the time the fit gets the true value within the error
  // Repeat for all parameters individually and then sum for the total
  std::vector<unsigned int> correct_ana1(params.size(),0);
  std::vector<unsigned int> correct_ana2(params.size(),0);
  std::vector<unsigned int> correct_ana3(params.size(),0);

  TString pdf_filename(("sbnd_prism3_prism5_pull_studies"+tag+".pdf").c_str());

  unsigned int ndof_ana1 = 0;
  unsigned int ndof_ana2 = 0;
  unsigned int ndof_ana3 = 0;

  // Loop over number of toys run in the fit
  for(int i=0; i<nentries; i++) {
//  for(int i=0; i<12; i++) {
    std::cout << " Running entry " << i << '\r' << flush;

    fitnt_ana1->GetEntry(i);
    fitnt_ana2->GetEntry(i);
    fitnt_ana3->GetEntry(i);

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

    unsigned int totalNumParams_ana1 = gbfparm_ana1->GetNumberParameters();
    unsigned int freeParams_ana1     = gbfparm_ana1->GetNumberFreeParameters();
    unsigned int totalNumParams_ana2 = gbfparm_ana2->GetNumberParameters();
    unsigned int freeParams_ana2     = gbfparm_ana2->GetNumberFreeParameters();
    unsigned int totalNumParams_ana3 = gbfparm_ana3->GetNumberParameters();
    unsigned int freeParams_ana3     = gbfparm_ana3->GetNumberFreeParameters();
    unsigned int nuisanceParams     = 0;

    // NDOF = total number of parameters - number of fixed parameters
    //ndof_inc = freeParams_inc;
    //ndof_exc = freeParams_exc;
    //std::cout<<"ndof_inc = "<<ndof_inc<<", ndof_exc = "<<ndof_exc<<std::endl;
    ndof_ana1 = 21;
    ndof_ana2 = 21;
    ndof_ana3 = 21;
    // Full postfit matrix
    TMatrixDSym &cov_ana1 = *gbfparm_ana1->GetCovMatrix();
    TMatrixDSym &cov_ana2 = *gbfparm_ana2->GetCovMatrix();
    TMatrixDSym &cov_ana3 = *gbfparm_ana3->GetCovMatrix();
    std::vector<double> ana1_errors, ana2_errors, ana3_errors, input_errors;

    int nRows = cov_ana1.GetNrows();
    int nCols = cov_ana1.GetNcols();

    unsigned int nPhysicsParams = 0;
    int n = 0;
    for(int j = 0; j < nRows; ++j){
      ana1_errors.push_back(sqrt(cov_ana1(j,j)));
      ana2_errors.push_back(sqrt(cov_ana2(j,j)));
      ana3_errors.push_back(sqrt(cov_ana3(j,j)));
      if(!gbfparm_ana1->IsNuisanceByIndex(j)){
        nPhysicsParams++;
        std::cout << " Physics parameter not nuisance parameter: " << gbfparm_ana1->NameByIndex(j) << std::endl;
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
    if(ana1_errors.size() != totalNumParams_ana1) 
      std::cout << " Error: The number of parameters and errors don't match. Params : " << totalNumParams_ana1 << " vs. errors: " << ana1_errors.size() << std::endl;

    const std::string name_input     = "h_input_"+std::to_string(i);
    const std::string name_ana1 = "h_ana1_"+std::to_string(i);
    const std::string name_ana2 = "h_ana2_"+std::to_string(i);
    const std::string name_ana3 = "h_ana3_"+std::to_string(i);

    TH1D *h_input = new TH1D(name_input.c_str(),     "", nRows-nPhysicsParams, 0, nRows-nPhysicsParams);
    TH1D *h_ana1  = new TH1D(name_ana1.c_str(), "", nRows-nPhysicsParams, 0, nRows-nPhysicsParams);
    TH1D *h_ana2  = new TH1D(name_ana2.c_str(), "", nRows-nPhysicsParams, 0, nRows-nPhysicsParams);
    TH1D *h_ana3  = new TH1D(name_ana3.c_str(), "", nRows-nPhysicsParams, 0, nRows-nPhysicsParams);

    unsigned int nuisance_it = 0;

    for(unsigned int j = 0; j < totalNumParams_ana1; ++j){
      bool isNuisance = gbfparm_ana1->IsNuisanceByIndex(j);
      if(!isNuisance) continue; // Only want to plot nuisance parameters for now
      nuisance_it = j-nPhysicsParams; // Bin number for nuisance parameters
      int nuisanceBin = nuisance_it+1;

      double input_bin_content     = 0.;
      double ana1_bin_content = 0.;
      double ana2_bin_content = 0.;
      double ana3_bin_content = 0.;

      double ana1_bin_error   = 0.;
      double ana2_bin_error   = 0.;
      double ana3_bin_error   = 0.;

      // Convert to units of nsigma
      // Check the initial values are the same in the inclusive and exclusive fit outputs
      if((std::abs(gbfparm_ana1->InitValueByIndex(j) - gbfparm_ana2->InitValueByIndex(j)) > std::numeric_limits<float>::epsilon())||(std::abs(gbfparm_ana1->InitValueByIndex(j) - gbfparm_ana3->InitValueByIndex(j)) > std::numeric_limits<float>::epsilon())||(std::abs(gbfparm_ana3->InitValueByIndex(j) - gbfparm_ana2->InitValueByIndex(j)) > std::numeric_limits<float>::epsilon())){
        std::cerr << " Error: The initial values in the 3 fits don't match, can't compare!" << std::endl;
        util::Die(-1);
      }

      input_bin_content     = gbfparm_ana1->InitValueByIndex(j);
      ana1_bin_content = gbfparm_ana1->BestFitValueByIndex(j);
      ana2_bin_content = gbfparm_ana2->BestFitValueByIndex(j);
      ana3_bin_content = gbfparm_ana3->BestFitValueByIndex(j);
      ana1_bin_error   = ana1_errors.at(j);
      ana2_bin_error   = ana2_errors.at(j);
      ana3_bin_error   = ana3_errors.at(j);

      // Pull comparisons
      h_true_ana1->Fill(ana1_bin_content-input_bin_content);
      h_true_ana2->Fill(ana2_bin_content-input_bin_content);
      h_true_ana3->Fill(ana3_bin_content-input_bin_content);
      h_comparisons_ana1.at(j)->Fill(ana1_bin_content-input_bin_content);
      h_comparisons_ana2.at(j)->Fill(ana2_bin_content-input_bin_content);
      h_comparisons_ana3.at(j)->Fill(ana3_bin_content-input_bin_content);
      h_chisq_ana1.at(j)->Fill((ana1_bin_content-input_bin_content)/static_cast<double>(ana1_errors.at(j)));
      h_chisq_ana2.at(j)->Fill((ana2_bin_content-input_bin_content)/static_cast<double>(ana2_errors.at(j)));
      h_chisq_ana3.at(j)->Fill((ana3_bin_content-input_bin_content)/static_cast<double>(ana3_errors.at(j)));

      // Now check if the true value sits within each of the errors and add to the counters if necessary
      if(input_bin_content >= (ana1_bin_content-ana1_errors.at(j)) && input_bin_content <= (ana1_bin_content+ana1_errors.at(j)))
        correct_ana1.at(j)++;
      if(input_bin_content >= (ana2_bin_content-ana2_errors.at(j)) && input_bin_content <= (ana2_bin_content+ana2_errors.at(j)))
        correct_ana2.at(j)++;
      if(input_bin_content >= (ana3_bin_content-ana3_errors.at(j)) && input_bin_content <= (ana3_bin_content+ana3_errors.at(j)))
        correct_ana3.at(j)++;

      // Prefit bin content is always 0 in order to only demonstrate the error in each bin
      h_input->SetBinContent(nuisanceBin,     input_bin_content);
      h_ana1->SetBinContent(nuisanceBin, ana1_bin_content);
      h_ana2->SetBinContent(nuisanceBin, ana2_bin_content);
      h_ana3->SetBinContent(nuisanceBin, ana3_bin_content);
      h_ana1->SetBinError(nuisanceBin,   ana1_bin_error);
      h_ana2->SetBinError(nuisanceBin,   ana2_bin_error);
      h_ana3->SetBinError(nuisanceBin,   ana3_bin_error);

      std::string label = "#color["+std::to_string(pal.at(j))+"]{"+params_tex.at(j)+"}";
      h_ana1->GetXaxis()->SetBinLabel(nuisanceBin,label.c_str());
    }
    // Fit statistic comparisons
    h_stat_ana1->Fill(gbfparm_ana1->GetBestFitStatistic());
    h_stat_ana2->Fill(gbfparm_ana2->GetBestFitStatistic());
    h_stat_ana3->Fill(gbfparm_ana3->GetBestFitStatistic());
    h_perndof_ana1->Fill(gbfparm_ana1->GetBestFitStatistic()/static_cast<double>(ndof_ana1));
    h_perndof_ana2->Fill(gbfparm_ana2->GetBestFitStatistic()/static_cast<double>(ndof_ana2));
    h_perndof_ana3->Fill(gbfparm_ana3->GetBestFitStatistic()/static_cast<double>(ndof_ana3));

    // If we have reached the limit of universes to plot individually, move onto the next one
    if(i >= ntorun) continue;
    
    double max_error = -999.;
    for(int i = 0; i < h_ana1->GetNbinsX(); ++i){
      double curr_error_test = std::max(h_ana1->GetBinError(i), h_ana2->GetBinError(i));
      double curr_error = std::max(curr_error_test, h_ana3->GetBinError(i));
      if(curr_error > max_error)
        max_error = curr_error;
    }
    double maxy_test = (std::max(h_ana1->GetMaximum(),h_ana2->GetMaximum()));
    double maxy = (std::max(maxy_test,h_ana3->GetMaximum())+max_error);
    if(maxy < 0)
      maxy = maxy*0.9;
    else
      maxy = maxy*1.1;

    double miny = (std::min(h_ana1->GetMinimum(),h_ana2->GetMinimum()));
    miny = (std::min(miny,h_ana3->GetMinimum())-max_error);
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

    h_ana1->GetYaxis()->SetRangeUser(-5,5);
    h_ana1->Draw("E1 X0");
    h_ana2->Draw("same E1 X0");
    h_ana3->Draw("same E1 X0");
    h_input->Draw("same p");

    h_ana1->GetXaxis()->LabelsOption("v");
    h_ana1->GetXaxis()->SetLabelSize(0.08);
    h_ana1->GetXaxis()->SetLabelFont(132);
    h_ana1->GetYaxis()->SetLabelSize(0.045);
    h_ana1->GetYaxis()->SetLabelFont(132);
    h_ana1->GetYaxis()->SetTitleSize(0.055);
    h_ana1->GetYaxis()->SetTitleFont(132);
    h_ana1->GetYaxis()->SetTitleOffset(0.6);
    h_ana1->GetYaxis()->SetMaxDigits(3);
    h_ana1->GetXaxis()->SetTitle("");
    h_ana1->GetYaxis()->SetTitle("Parameter pull [#sigma]");
    h_ana1->SetLineColor(ana1_color);
    h_ana1->SetLineWidth(2);
    h_ana1->SetMarkerStyle(ana1_marker);
    h_ana1->SetMarkerColor(ana1_color);
    h_ana1->SetMarkerSize(1.5);

    h_ana2->SetLineColor(ana2_color);
    h_ana2->SetLineWidth(2);
    h_ana2->SetMarkerStyle(ana2_marker);
    h_ana2->SetMarkerColor(ana2_color);
    h_ana2->SetMarkerSize(1.5);

    h_ana3->SetLineColor(ana3_color);
    h_ana3->SetLineWidth(2);
    h_ana3->SetMarkerStyle(ana3_marker);
    h_ana3->SetMarkerColor(ana3_color);
    h_ana3->SetMarkerSize(1.8);

    h_input->SetMarkerColor(true_color);
    h_input->SetMarkerStyle(true_marker);

    l_bestfit->AddEntry(h_input,("#color["+std::to_string(true_color)+"]{True value}").c_str(), "p");
    l_bestfit->AddEntry(h_ana1,("#color["+std::to_string(ana1_color)+"]{SBND postfit value}").c_str(), "ep");
    l_bestfit->AddEntry(h_ana2,("#color["+std::to_string(ana2_color)+"]{PRISM3 postfit value}").c_str(), "ep");
    l_bestfit->AddEntry(h_ana3,("#color["+std::to_string(ana3_color)+"]{PRISM5 postfit value}").c_str(), "ep");
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

    c->SaveAs(("pngs/sbnd_prism3_prism5_pull_studies_universe_"+std::to_string(i)+tag+".png").c_str());
    c->SaveAs(("pdfs/sbnd_prism3_prism5_pull_studies_universe_"+std::to_string(i)+tag+".pdf").c_str());
    c->Clear();
    l_bestfit->Clear();
  }
  std::cout << std::endl;
  
  // Now for the global comparison
  // Pull comparison canvas and legend
  TCanvas *c_comp = new TCanvas("c_comp","",20,20,880,900);
  c_comp->SetTopMargin(0.07);
  c_comp->SetBottomMargin(0.12);
  c_comp->SetLeftMargin(0.14);
  c_comp->SetRightMargin(0.025);
    
  FormatComparisonHists(h_true_ana1,h_true_ana2,h_true_ana3);
  gStyle->SetOptStat();

  TLegend *l_comp = new TLegend(0.27,0.94,0.99,0.98);
  //TLegend *l_comp = new TLegend(0.25,0.9,0.99,0.98);
  l_comp->SetNColumns(3);
  l_comp->SetBorderSize(0);
  l_comp->SetFillStyle(0);
  l_comp->SetTextFont(132);
  l_comp->SetTextSize(0.05);

  double max_comp_y_test = std::max(h_true_ana1->GetMaximum(),h_true_ana2->GetMaximum());
  double max_comp_y = std::max(max_comp_y_test,h_true_ana3->GetMaximum());
  h_true_ana1->GetYaxis()->SetRangeUser(0.,max_comp_y*1.1);
  h_true_ana1->SetName(("#color["+std::to_string(ana1_color)+"]{SBND}").c_str());
  h_true_ana2->SetName(("#color["+std::to_string(ana2_color)+"]{PRISM3}").c_str());
  h_true_ana3->SetName(("#color["+std::to_string(ana3_color)+"]{PRISM5}").c_str());
  h_true_ana1->Draw("hist");
  h_true_ana2->Draw("sames hist");
  h_true_ana3->Draw("sames hist");
  h_true_ana1->SetStats(1);
  h_true_ana2->SetStats(1);
  h_true_ana3->SetStats(1);
  c_comp->Update();

  TPaveStats *st_ana1 = static_cast<TPaveStats*>(h_true_ana1->FindObject("stats"));
  TPaveStats *st_ana2 = static_cast<TPaveStats*>(h_true_ana2->FindObject("stats"));
  TPaveStats *st_ana3 = static_cast<TPaveStats*>(h_true_ana3->FindObject("stats"));

  SetupStats(st_ana1,st_ana2,st_ana3);
  
  c_comp->Modified();

  l_comp->AddEntry(h_true_ana1, ("#color["+std::to_string(ana1_color)+"]{SBND}").c_str(), "l");
  l_comp->AddEntry(h_true_ana2, ("#color["+std::to_string(ana2_color)+"]{PRISM3}").c_str(), "l");
  l_comp->AddEntry(h_true_ana3, ("#color["+std::to_string(ana3_color)+"]{PRISM5}").c_str(), "l");
  l_comp->Draw();

  TLatex latex;
  latex.SetTextAlign(11);
  latex.SetTextSize(0.06);
  latex.SetTextColor(611);
  latex.DrawLatex(-2.56,max_comp_y,"All parameters");

  c_comp->SaveAs(("pngs/sbnd_prism3_prism5_comparison_all_parameters"+tag+".png").c_str());
  c_comp->SaveAs(("pdfs/sbnd_prism3_prism5_comparison_all_parameters"+tag+".pdf").c_str());
  c_comp->Write();
  c_comp->Clear();
  l_comp->Clear();
  max_comp_y_test=0.;
  max_comp_y=0.;
  // Now plot the individual parameter histograms
  for(unsigned int p = 0; p < params_tex.size(); ++p){
    TH1D *h_ana1(h_comparisons_ana1.at(p));
    TH1D *h_ana2(h_comparisons_ana2.at(p));
    TH1D *h_ana3(h_comparisons_ana3.at(p));

    FormatComparisonHists(h_ana1,h_ana2,h_ana3);
    max_comp_y_test = std::max(h_ana1->GetMaximum(),h_ana2->GetMaximum());
    max_comp_y = std::max(max_comp_y_test,h_ana3->GetMaximum());
    h_ana1->GetYaxis()->SetRangeUser(0.,max_comp_y*1.1);
    h_ana1->SetName(("#color["+std::to_string(ana1_color)+"]{SBND}").c_str());
    h_ana2->SetName(("#color["+std::to_string(ana2_color)+"]{PRISM3}").c_str());
    h_ana3->SetName(("#color["+std::to_string(ana3_color)+"]{PRISM5}").c_str());
    h_ana1->Draw("hist");
    h_ana2->Draw("sames hist");
    h_ana3->Draw("sames hist");
    h_ana1->SetStats(1);
    h_ana2->SetStats(1);
    h_ana3->SetStats(1);
    c_comp->Update();

    TPaveStats *st_param_ana1 = static_cast<TPaveStats*>(h_ana1->FindObject("stats"));
    TPaveStats *st_param_ana2 = static_cast<TPaveStats*>(h_ana2->FindObject("stats"));
    TPaveStats *st_param_ana3 = static_cast<TPaveStats*>(h_ana3->FindObject("stats"));

    SetupStats(st_param_ana1,st_param_ana2,st_param_ana3);
    
    c_comp->Modified();

    TLatex latex1;
    latex1.SetTextAlign(11);
    latex1.SetTextSize(0.06);
    latex1.SetTextColor(pal.at(p));
    latex1.DrawLatex(-2.56,max_comp_y,params_tex.at(p).c_str());

    l_comp->AddEntry(h_ana1, ("#color["+std::to_string(ana1_color)+"]{SBND}").c_str(), "l");
    l_comp->AddEntry(h_ana2, ("#color["+std::to_string(ana2_color)+"]{PRISM3}").c_str(), "l");
    l_comp->AddEntry(h_ana2, ("#color["+std::to_string(ana3_color)+"]{PRISM5}").c_str(), "l");
    l_comp->Draw();

    c_comp->SaveAs(("pngs/sbnd_prism3_prism5_comparison_parameter_"+params.at(p)+tag+".png").c_str());
    c_comp->SaveAs(("pdfs/sbnd_prism3_prism5_comparison_parameter_"+params.at(p)+tag+".pdf").c_str());
    c_comp->Write(("c_comp_"+params.at(p)).c_str());
    c_comp->Clear();
    l_comp->Clear();
    max_comp_y_test=0.;
    max_comp_y=0.;
    
    // Chisq version
    TH1D *h_chi_ana1(h_chisq_ana1.at(p));
    TH1D *h_chi_ana2(h_chisq_ana2.at(p));
    TH1D *h_chi_ana3(h_chisq_ana3.at(p));

    FormatComparisonHists(h_chi_ana1,h_chi_ana2,h_chi_ana3,"(Pull_{Bestfit} - Pull_{True}) / #sigma_{Bestfit}");
    
    max_comp_y_test = std::max(h_chi_ana1->GetMaximum(),h_chi_ana2->GetMaximum());
    max_comp_y = std::max(max_comp_y_test,h_chi_ana3->GetMaximum());
    h_chi_ana1->GetYaxis()->SetRangeUser(0.,max_comp_y*1.1);
    h_chi_ana1->SetName(("#color["+std::to_string(ana1_color)+"]{SBND}").c_str());
    h_chi_ana2->SetName(("#color["+std::to_string(ana2_color)+"]{PRISM3}").c_str());
    h_chi_ana3->SetName(("#color["+std::to_string(ana3_color)+"]{PRISM5}").c_str());
    h_chi_ana1->Draw("hist");
    h_chi_ana2->Draw("sames hist");
    h_chi_ana3->Draw("sames hist");
    h_chi_ana1->SetStats(1);
    h_chi_ana2->SetStats(1);
    h_chi_ana3->SetStats(1);
    c_comp->Update();

    TPaveStats *st_param_chisq_ana1 = static_cast<TPaveStats*>(h_chi_ana1->FindObject("stats"));
    TPaveStats *st_param_chisq_ana2 = static_cast<TPaveStats*>(h_chi_ana2->FindObject("stats"));
    TPaveStats *st_param_chisq_ana3 = static_cast<TPaveStats*>(h_chi_ana3->FindObject("stats"));

    SetupStats(st_param_chisq_ana1,st_param_chisq_ana2,st_param_chisq_ana3);
    
    c_comp->Modified();

    latex1.DrawLatex(-2.56,max_comp_y,params_tex.at(p).c_str());

    l_comp->AddEntry(h_chi_ana1, ("#color["+std::to_string(ana1_color)+"]{SBND}").c_str(), "l");
    l_comp->AddEntry(h_chi_ana2, ("#color["+std::to_string(ana2_color)+"]{PRISM3}").c_str(), "l");
    l_comp->AddEntry(h_chi_ana3, ("#color["+std::to_string(ana3_color)+"]{PRISM5}").c_str(), "l");
    l_comp->Draw();

    c_comp->SaveAs(("pngs/sbnd_prism3_prism5_chisq_parameter_"+params.at(p)+tag+".png").c_str());
    c_comp->SaveAs(("pdfs/sbnd_prism3_prism5_chisq_parameter_"+params.at(p)+tag+".pdf").c_str());
    c_comp->Write(("c_comp_chisq_"+params.at(p)).c_str());
    c_comp->Clear();
    l_comp->Clear();
    max_comp_y_test=0.;
    max_comp_y=0.;
  }
  // Now plot the fit statistic
  FormatComparisonHists(h_stat_ana1,h_stat_ana2,h_stat_ana3, "Fit statistic");
  max_comp_y_test = std::max(h_stat_ana1->GetMaximum(),h_stat_ana2->GetMaximum());
  max_comp_y = std::max(max_comp_y_test,h_stat_ana3->GetMaximum());
  h_stat_ana1->GetYaxis()->SetRangeUser(0.,max_comp_y*1.1);
  h_stat_ana1->SetName(("#color["+std::to_string(ana1_color)+"]{SBND}").c_str());
  h_stat_ana2->SetName(("#color["+std::to_string(ana2_color)+"]{PRISM3}").c_str());
  h_stat_ana3->SetName(("#color["+std::to_string(ana3_color)+"]{PRISM5}").c_str());
  h_stat_ana1->Draw("hist");
  h_stat_ana2->Draw("sames hist");
  h_stat_ana3->Draw("sames hist");
  h_stat_ana1->SetStats(1);
  h_stat_ana2->SetStats(1);
  h_stat_ana3->SetStats(1);
  c_comp->Update();

  TPaveStats *st_stat_ana1 = static_cast<TPaveStats*>(h_stat_ana1->FindObject("stats"));
  TPaveStats *st_stat_ana2 = static_cast<TPaveStats*>(h_stat_ana2->FindObject("stats"));
  TPaveStats *st_stat_ana3 = static_cast<TPaveStats*>(h_stat_ana3->FindObject("stats"));

  SetupStats(st_stat_ana1,st_stat_ana2,st_stat_ana3);

  c_comp->Modified();

  l_comp->AddEntry(h_stat_ana1, ("#color["+std::to_string(ana1_color)+"]{SBND}").c_str(), "l");
  l_comp->AddEntry(h_stat_ana2, ("#color["+std::to_string(ana2_color)+"]{PRISM3}").c_str(), "l");
  l_comp->AddEntry(h_stat_ana3, ("#color["+std::to_string(ana3_color)+"]{PRISM5}").c_str(), "l");
  l_comp->Draw();

  c_comp->SaveAs(("pdfs/sbnd_prism3_prism5_comparison_fit_statistic"+tag+".pdf").c_str());
  c_comp->SaveAs(("pngs/sbnd_prism3_prism5_comparison_fit_statistic"+tag+".png").c_str());
  c_comp->Write("c_comp_stat");
  c_comp->Clear();
  l_comp->Clear();

  FormatComparisonHists(h_perndof_ana1,h_perndof_ana2,h_perndof_ana3, "Fit statistic / NDOF");
  max_comp_y_test = std::max(h_perndof_ana1->GetMaximum(),h_perndof_ana2->GetMaximum());
  max_comp_y = std::max(max_comp_y_test,h_perndof_ana3->GetMaximum());
  h_perndof_ana1->GetYaxis()->SetRangeUser(0.,max_comp_y*1.1);
  h_perndof_ana1->SetName(("#color["+std::to_string(ana1_color)+"]{SBND}").c_str());
  h_perndof_ana2->SetName(("#color["+std::to_string(ana2_color)+"]{PRISM3}").c_str());
  h_perndof_ana3->SetName(("#color["+std::to_string(ana3_color)+"]{PRISM5}").c_str());
  h_perndof_ana1->Draw("hist");
  h_perndof_ana2->Draw("sames hist");
  h_perndof_ana3->Draw("sames hist");
  h_perndof_ana1->SetStats(1);
  h_perndof_ana2->SetStats(1);
  h_perndof_ana3->SetStats(1);
  c_comp->Update();

  TPaveStats *st_perndof_ana1 = static_cast<TPaveStats*>(h_perndof_ana1->FindObject("stats"));
  TPaveStats *st_perndof_ana2 = static_cast<TPaveStats*>(h_perndof_ana2->FindObject("stats"));
  TPaveStats *st_perndof_ana3 = static_cast<TPaveStats*>(h_perndof_ana3->FindObject("stats"));

  SetupStats(st_perndof_ana1,st_perndof_ana2,st_perndof_ana3);

  c_comp->Modified();

  l_comp->AddEntry(h_perndof_ana1, ("#color["+std::to_string(ana1_color)+"]{SBND}").c_str(), "l");
  l_comp->AddEntry(h_perndof_ana2, ("#color["+std::to_string(ana2_color)+"]{PRISM3}").c_str(), "l");
  l_comp->AddEntry(h_perndof_ana3, ("#color["+std::to_string(ana3_color)+"]{PRISM5}").c_str(), "l");
  l_comp->Draw();

  c_comp->SaveAs(("pdfs/sbnd_prism3_prism5_comparison_fit_statistic_per_ndof"+tag+".pdf").c_str());
  c_comp->SaveAs(("pngs/sbnd_prism3_prism5_comparison_fit_statistic_per_ndof"+tag+".png").c_str());
  c_comp->Write("c_comp_stat_perndof");
  c_comp->Clear();
  l_comp->Clear();

  f_outputs->Close();

  // Now the stats:
  ofstream file;
  file.open(("rates"+tag+"_3.txt").c_str());
  file << std::endl;
  file << " Rate of fits which find the true systematic value to within the postfit uncertainty: " << std::endl;
  file << std::endl;
  file << std::setw(16) << "Parameter" << std::setw(16) << "SBND " << std::setw(16) << "PRISM3 " << std::setw(16) << "PRISM5 " << std::endl;
  unsigned int total_correct_ana1 = 0;
  unsigned int total_correct_ana2 = 0;
  unsigned int total_correct_ana3 = 0;
  for(unsigned int i = 0; i < params.size(); ++i){
    total_correct_ana1 += correct_ana1.at(i);
    total_correct_ana2 += correct_ana2.at(i);
    total_correct_ana3 += correct_ana3.at(i);
    file << std::setw(16) << params.at(i) << std::setw(16) << correct_ana1.at(i) << std::setw(16) << correct_ana2.at(i) << std::setw(16) << correct_ana3.at(i) << std::endl;
  }
  file << std::endl;
  file << std::setw(16) << "Total " << std::setw(16) << total_correct_ana1 << std::setw(16) << total_correct_ana2 << std::setw(16) << total_correct_ana3 << std::endl;
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

void FormatComparisonHists(TH1D* h_ana1, TH1D *h_ana2, TH1D *h_ana3, const std::string &xlabel = ""){
  h_ana1->GetXaxis()->SetLabelSize(0.055);
  h_ana1->GetXaxis()->SetLabelFont(132);
  h_ana1->GetXaxis()->SetTitleSize(0.055);
  h_ana1->GetXaxis()->SetTitleFont(132);
  h_ana1->GetXaxis()->SetTitleOffset(1);
  h_ana1->GetYaxis()->SetLabelSize(0.055);
  h_ana1->GetYaxis()->SetLabelFont(132);
  h_ana1->GetYaxis()->SetTitleSize(0.055);
  h_ana1->GetYaxis()->SetTitleFont(132);
  h_ana1->GetYaxis()->SetTitleOffset(1.3);
  h_ana1->GetYaxis()->SetMaxDigits(3);
  if(xlabel == "")
    h_ana1->GetXaxis()->SetTitle("Pull_{Bestfit} - Pull_{True}, [#sigma]");
  else
    h_ana1->GetXaxis()->SetTitle(xlabel.c_str());
  h_ana1->GetYaxis()->SetTitle("Number of toys");
  h_ana1->SetLineColor(ana1_color);
  h_ana2->SetLineColor(ana2_color);
  h_ana3->SetLineColor(ana3_color);
  h_ana1->SetLineStyle(ana1_line_style);
  h_ana2->SetLineStyle(ana2_line_style);
  h_ana3->SetLineStyle(ana3_line_style);
  h_ana1->SetLineWidth(2);
  h_ana2->SetLineWidth(2);
  h_ana3->SetLineWidth(2);
}
void SetupStats(TPaveStats *st_ana1, TPaveStats *st_ana2, TPaveStats *st_ana3){
  st_ana1->SetX1NDC(0.68);
  st_ana1->SetX2NDC(0.95);
  st_ana1->SetY1NDC(0.72);
  st_ana1->SetY2NDC(0.90);
  st_ana2->SetX1NDC(0.68);
  st_ana2->SetX2NDC(0.95);
  st_ana2->SetY1NDC(0.50);
  st_ana2->SetY2NDC(0.68);
  st_ana3->SetX1NDC(0.68);
  st_ana3->SetX2NDC(0.95);
  st_ana3->SetY1NDC(0.28);
  st_ana3->SetY2NDC(0.46);
  st_ana1->SetTextFont(132);
  st_ana2->SetTextFont(132);
  st_ana3->SetTextFont(132);
  st_ana1->SetTextSize(0.036);
  st_ana2->SetTextSize(0.036);
  st_ana3->SetTextSize(0.036);
  st_ana1->SetTextColor(ana1_color);
  st_ana2->SetTextColor(ana2_color);
  st_ana3->SetTextColor(ana3_color);
  st_ana1->SetLineColor(0);
  st_ana2->SetLineColor(0);
  st_ana3->SetLineColor(0);
  st_ana1->SetBorderSize(0);
  st_ana2->SetBorderSize(0);
  st_ana3->SetBorderSize(0);
}
