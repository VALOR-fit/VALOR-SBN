#include <iostream>
//#include <limits>
 
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPad.h"
#include "TString.h"
#include "TFrame.h"
#include "TF1.h"

#include "TGraph.h"
#include "TStyle.h"
#include "TAxis.h"
#include "TColor.h"


void contour_ratios(        
  const char *reference_file,          // The reference contour we will be comparing against
  const char *dirname,                 // Directory containing the other contours, require trailing /
  std::string analysis_sample = "MuE"  // Set the analysis sample used for labelling etc (use, MuE, MuMu or EE)
  ){

// can define more if needed
std::vector<Color_t> colors = {kBlue, kGreen+1, kRed, kCyan,  kMagenta+1, kOrange-1, kPink-9, kGray+2, kGreen+3};

std::vector<TString> contour_list;
std::vector<TString> contour_short_name;
const char *ext=".root"; 
TSystemDirectory dir(dirname, dirname); 
TList *files = dir.GetListOfFiles(); 
if (files) { 
 TSystemFile *file; TString fname; 
 TIter next(files); 
 while ((file=(TSystemFile*)next())) { fname = file->GetName(); 
   if (!file->IsDirectory() && fname.EndsWith(ext)) {
     auto file_path = dirname+fname; 
     auto short_name = fname.ReplaceAll("output_contours_as_graphs_","");
     //std::cout << short_name << std::endl; 
     contour_list.push_back(file_path);
     contour_short_name.push_back(short_name);
    } 
  } 
}

int N_contours = contour_list.size();

if(N_contours > colors.size()){
    std::cout << "Found more files than there are defined colours - feel free to add more colours. Stopping." << std::endl;
    std::exit(-1);
}

// Get the reference contour 
std::cout << std::endl << "Looking for reference file: " << reference_file << std::endl;
TFile *freference_file     = new TFile(reference_file, "read");
TGraph *reference_contour  = (TGraph*)freference_file->Get("contour_5sigma_lin_0;1");

// check the directory we specified has some root files
std::cout << "Looking for contour files in: " << dirname << std::endl;
if(N_contours != 0){
  std::cout << "Found " << N_contours << " files." << std::endl;
  for(int i = 0; i < N_contours; i++){
    std::cout << contour_short_name[i] << std::endl;
  }
}
else{
  std::cout << "Didn't find any root file in this directory. Stopping." << std::endl;
  std::exit(-1);
}

// Get number of points in reference_contour
int ref_cont_points = reference_contour->GetN();

double Xvalue_ref       [ref_cont_points];
double Xvalue_ref_ratio [ref_cont_points];
double Yvalue_ref       [ref_cont_points];

// Get all other contours and create arrays to hold the points
TFile *f[N_contours];
TGraph *contour[N_contours];
TGraph inv_contour[N_contours];
std::vector<std::vector<double>> Xvalue_cont_vec;
std::vector<std::vector<double>> Xvalue_cont_ratio_vec;

for(int j = 0; j < N_contours ; j++){
  f[j] = new TFile(contour_list[j]);
  contour[j] = (TGraph*)f[j]->Get("contour_5sigma_lin_0;1");

  TGraph inv(contour[j]->GetN(), contour[j]->GetY(), contour[j]->GetX());

  std::vector<double> temp_vec;
  for(int i = 0; i < ref_cont_points; i++){
    Xvalue_ref[i] = reference_contour->GetX()[i];
    Yvalue_ref[i] = reference_contour->GetY()[i];
    Xvalue_ref_ratio[i] = Xvalue_ref[i]/reference_contour->GetX()[i];
    double Ratio = inv.Eval(reference_contour->GetY()[i]) / Xvalue_ref[i];
    temp_vec.push_back(Ratio);

  }
  Xvalue_cont_vec.push_back(temp_vec);
  temp_vec.clear();
}


// Displaying the 2D vector
/*
for (int i = 0; i < Xvalue_cont_vec.size(); i++) {
  for (int j = 0; j < Xvalue_cont_vec[i].size(); j++)
    cout << Xvalue_cont_vec[i][j] << " ";
  cout << endl;
}
*/

double max_ref = reference_contour->GetY()[ref_cont_points-1];
double min_ref = reference_contour->GetY()[0];

double max_x = std::numeric_limits<double>::min();
for(const auto& v: Xvalue_cont_vec) {
  for(const auto& e: v) {   
    max_x = std::max(max_x, e);
  }
}

// cont_ratio
TCanvas * cont_ratio = new TCanvas("cont_ratio","",20,20,900,900);
cont_ratio->Draw();

TH2F * hcont_ratio = (TH2F*)cont_ratio->DrawFrame(0.9,0.01,max_x*1.2,100);
hcont_ratio->Draw();
cont_ratio->SetLogy();
if(analysis_sample == "MuE"){
  hcont_ratio->GetXaxis()->SetTitle("sin^{2}2#theta_{#mue_X}/sin^{2}2#theta_{#mue_reference_value}");
}
else if(analysis_sample == "MuMu"){
  hcont_ratio->GetXaxis()->SetTitle("sin^{2}2#theta_{#mu#mu_X}/sin^{2}2#theta_{#mu#mu_reference_value}");
}
else if(analysis_sample == "EE"){
  hcont_ratio->GetXaxis()->SetTitle("sin^{2}2#theta_{ee_X}/sin^{2}2#theta_{ee_reference_value}");
}
else{
  std::cout << "Didn't recognise analysis sample (use one of, MuE, MuMu or EE)." << std::endl;
  std::cout << "Will keep the labelling vague." << std::endl;
  hcont_ratio->GetXaxis()->SetTitle("sin^{2}2#theta_{X}/sin^{2}2#theta_{reference_value}");
}

hcont_ratio->GetXaxis()->SetTitleSize(0.03);
hcont_ratio->GetXaxis()->SetLabelSize(0.03);
hcont_ratio->GetYaxis()->SetTitle("#Delta m^{2}_{41} (eV^{2})");
hcont_ratio->GetYaxis()->SetTitleSize(0.03);
hcont_ratio->GetYaxis()->SetLabelSize(0.03);

//TLegend * lratio = new TLegend(0.2,0.65,0.9,0.9);
TLegend * lratio = new TLegend(0.65,0.2);

TGraph *ref_cont = new TGraph(ref_cont_points, Xvalue_ref_ratio, Yvalue_ref);
ref_cont->SetLineWidth(4);
ref_cont->SetLineColor(kBlack);
ref_cont->Draw("l");

lratio->AddEntry(ref_cont, "Reference Contour", "L");

for(int i = 0; i < N_contours; i++){
  TGraph *cont = new TGraph(ref_cont_points, &Xvalue_cont_vec[i][0], Yvalue_ref);
  cont->SetLineWidth(4);
  cont->SetLineColor(colors[i]);
  cont->Draw("l");

  // add legend entries
  lratio->AddEntry(cont, contour_short_name[i], "L");

}

//lratio->SetFillStyle();
//lratio->SetFillColor(22);
lratio->SetBorderSize(1);
lratio->SetTextFont(132);
lratio->SetTextSize(0.02);
lratio->Draw();

}














