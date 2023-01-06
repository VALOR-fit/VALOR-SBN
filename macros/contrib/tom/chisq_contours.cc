////////////////////////////////////////////////////////////
//                                                        //
// Scrip to draw sensitivity contours onto a coloured     //
// background giving the chi-squared values.              //
//                                                        //
// Use the output of the macro "fit_results_to_graphs.py" //
//                                                        //
////////////////////////////////////////////////////////////

#include <iostream>
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPad.h"
#include "TString.h"
#include "TF1.h"
#include "TGraph.h"
#include "TStyle.h"

void chisq_contours(
    const char *file, 
    const char *sample = "mumu"         // choose the inputs sample - "mumu", "mue" or "ee"
){

// Read in output file from fit_results_to_graphs.py
TFile *f = new TFile(file,"read");

// Get contours from file
// Check names in .root file
TGraph *contour_90              = (TGraph*) f->Get("contour_90pct_log_0");
TGraph *contour_3_sigma         = (TGraph*) f->Get("contour_3sigma_log_0");
TGraph *contour_5_sigma         = (TGraph*) f->Get("contour_5sigma_log_0");

// Get chisq surface 
TH2D *chisq_surface = (TH2D*) f->Get("contour_log_hist");

// Get dimensions of TH2D
double xmax = chisq_surface->GetXaxis()->GetXmax();
double xmin = chisq_surface->GetXaxis()->GetXmin();

// feel like there should be an easier way to get max/min y, but hey ho..
double ymax = chisq_surface->GetYaxis()->GetBinUpEdge(chisq_surface->GetYaxis()->GetNbins());
double ymin = chisq_surface->GetYaxis()->GetBinLowEdge(1);
std::cout << xmin << std::endl;
std::cout << xmax << std::endl;
double zmax = chisq_surface->GetMaximum();
double zmin = chisq_surface->GetMinimum();

// Set colour palette for background
gStyle->SetPalette(56);
// Set log colour scale 
gStyle->SetOptLogz();

// Set plot title
gStyle->SetOptTitle(1); // set hist title
gStyle->SetTitleX(0.2); //title X location
gStyle->SetTitleY(1); //title Y location
gStyle->SetTitleW(0.6); //title width
gStyle->SetTitleH(0.05); //title height
gStyle->SetTitleBorderSize(0);

// Get the number of different colours - pick a large number to get smooth transitions
chisq_surface->SetContour(1000);

std::string sample_s = sample;
if(sample_s == "mumu"){
    // Set title and axis
    chisq_surface->SetTitle("#nu_{#mu} disappearance");

    chisq_surface->GetXaxis()->SetRangeUser(xmin,xmax);
    chisq_surface->GetXaxis()->SetTitle("log_{10}(sin^{2}2#theta_{#mu#mu})");
}
else if(sample_s == "mue"){
    //chisq_surface->SetTitle("#nu_{e} appearance");
    
    chisq_surface->GetXaxis()->SetRangeUser(xmin,xmax);
    chisq_surface->GetXaxis()->SetTitle("log_{10}(sin^{2}2#theta_{#mue})");
}
else if(sample_s == "ee"){
    chisq_surface->SetTitle("#nu_{e} disappearance");
    
    chisq_surface->GetXaxis()->SetRangeUser(xmin,xmax);
    chisq_surface->GetXaxis()->SetTitle("log_{10}(sin^{2}2#theta_{ee})");
}
else{
    std::cerr << "Did not recognise input sample. Stopping" << std::endl;
    exit(1);
}

chisq_surface->GetXaxis()->SetRangeUser(xmin,0);
chisq_surface->GetYaxis()->SetRangeUser(ymin,ymax);
chisq_surface->GetYaxis()->SetTitle("log_{10}(#Deltam^{2}_{41})");
chisq_surface->GetYaxis()->SetTitleOffset(0.8);

// Have to manually set range so that entire graph is filled
chisq_surface->GetZaxis()->SetRangeUser(zmin,zmax);

// Edit canvas so axis titles etc. fit on properly
TCanvas *c1 = new TCanvas("c1","c1");
c1->SetRightMargin(0.2);
c1->SetLeftMargin(0.15);
c1->SetBottomMargin(0.15);

// Draw chisq surface 
chisq_surface->Draw("colz");

// Draw contours
contour_90->SetLineColor(kAzure-4);
contour_90->Draw("same");
contour_3_sigma->SetLineStyle(2);
contour_3_sigma->SetLineColor(kAzure-4);
contour_3_sigma->Draw("same");
contour_5_sigma->SetLineColor(kAzure-4);
contour_5_sigma->SetLineStyle(7);  
contour_5_sigma->Draw("same");  

// Add legend
TLegend *leg = new TLegend(0.65,0.65,0.8,0.85);
leg->SetTextSize(0.05);
leg->SetTextColor(kAzure-4);
leg->SetFillStyle(0);
leg->SetBorderSize(0);
leg->AddEntry(contour_90,"90%","l");
leg->AddEntry(contour_3_sigma,"3#sigma","l");
leg->AddEntry(contour_5_sigma,"5#sigma","l");
leg->Draw("same");

// Add label to colour legend
TLatex *latex = new TLatex();
latex->DrawLatexNDC(0.92,0.88,"#Delta#chi^{2}");

}
