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


std::vector<TGraph*> plotGraphs(const std::vector<std::string>& files, const std::vector<std::string>& tags, bool override_03e2_2, bool override_03e2_3) {

  std::vector<TGraph*> plottedGraphs;

  if (files.size() != tags.size()) {
      std::cerr << "Error: Number of files does not match the number of tags." << std::endl;
      return plottedGraphs;
  }
  
  gStyle->SetOptLogz();
  
  TCanvas *canvas = new TCanvas("canvas", "Graphs", 800, 600);
  canvas->SetRightMargin(0.08);
  canvas->SetLeftMargin(0.12);
  canvas->SetTopMargin(0.08);
  canvas->SetBottomMargin(0.12);
  canvas->SetLogx();
  canvas->SetLogy();

  TLegend *legend = new TLegend(0.15, 0.15, 0.55, 0.45);
  legend->SetTextSize(0.03);
  legend->SetTextFont(132);
  legend->SetTextColor(1);
  legend->SetFillStyle(0);
  legend->SetLineWidth(0);
  TLatex *latex = new TLatex();
  latex->SetTextSize(0.02);
  
  for (size_t i = 0; i < files.size(); ++i) {
    TFile *file = TFile::Open(files[i].c_str());
    if (!file || file->IsZombie()) {
	std::cerr << "Error: Unable to open file " << files[i] << std::endl;
	continue;
    }

    TObject *obj;
    if(std::string(files[i]).find("rsj") != std::string::npos){
      obj = file->Get("stat_syst_5sigma_lin_0");
    }else {
      obj = file->Get("contour_5sigma_lin_0");
    }
    if (!obj) {
	std::cerr << "Error: Unable to retrieve object ``contour_5sigma_lin_0'' from file " << files[i] << std::endl;
	file->Close();
	continue;
    }

    TGraph *graph = dynamic_cast<TGraph*>(obj);
    if (!graph) {
	std::cerr << "Error: Object ``contour_5sigma_lin_0'' from file " << files[i] << " is not a TGraph." << std::endl;
	file->Close();
	continue;
    }
    graph->SetLineWidth(2);
    std::string syst_label;
    std::string version_label;
    if (std::string(files[i]).find("_stat") != std::string::npos){
      graph->SetLineStyle(7);
      syst_label = "stat-only";
    }
    else if (std::string(files[i]).find("03d1") != std::string::npos) {
      graph->SetLineStyle(1);
      syst_label = "03d1";
    }
    else if (std::string(files[i]).find("03e2_2") != std::string::npos) {
      graph->SetLineStyle(2);
      syst_label = "03e2_2";
    }
    else if (std::string(files[i]).find("03e2_3") != std::string::npos) {
      graph->SetLineStyle(5);
      syst_label = "03e2_3";
    }
    else if (std::string(files[i]).find("03e2") != std::string::npos) {
      graph->SetLineStyle(4);
      syst_label = "03e2";
    }
    else if (std::string(files[i]).find("03d2") != std::string::npos) {
      graph->SetLineStyle(6);
      syst_label = "03d2";
    }
    else if (std::string(files[i]).find("04a1") != std::string::npos) {
      graph->SetLineStyle(10);
      syst_label = "04a1";
    }else{
      std::cout << "Syst group not recognised for file "<< i << std::endl;
      std::cout << "Please enter syst_label:" << std::endl;
      std::cin >> syst_label;
      int style;
      std::cout << "Please enter number for SetLineStyle:" << std::endl;
      std::cin >> style;
      graph->SetLineStyle(style);
    }
    /*if (std::string(tags[i]).find("Reducedmodes") != std::string::npos){
      syst_label += " reduced modes";
    }*/
    if (std::string(tags[i]).find("equalstat") != std::string::npos){
      syst_label += " equal stat";
    }
    if (std::string(tags[i]).find("equalwidth") != std::string::npos){
      syst_label += " equal width";
    }
    //std::cout << "syst label " << i << " = " << syst_label << std::endl;

    if (std::string(tags[i]).find("2020a1_v6") != std::string::npos) version_label = " 2020a1 v6";
    if (std::string(tags[i]).find("2024b_v9") != std::string::npos){ 
      version_label = " 2024b v9";
      //graph->SetLineStyle(1);
    }
  
    if(std::string(files[i]).find("sbnd") != std::string::npos){
      graph->SetLineColor(kAzure-4);
      if (std::string(tags[i]).find("2020a1_v6") != std::string::npos) version_label = " 2020a1 v6";
      if (std::string(tags[i]).find("2024b_v9") != std::string::npos){ 
        version_label = " 2024b v9";
        graph->SetLineColor(kCyan+3);
      }
      legend->AddEntry(graph,("5#sigma SBND "+syst_label+version_label).c_str(),"L");
      /*if (std::string(files[i]).find("reducedmodes") != std::string::npos){
        graph->SetLineColor(kAzure-6);
      }*/
    } else if(std::string(files[i]).find("sbn") != std::string::npos){
      graph->SetLineColor(kTeal-6);
      legend->AddEntry(graph,("5#sigma SBN "+syst_label+version_label).c_str(),"L");
    } else if(std::string(files[i]).find("prism3") != std::string::npos){
      graph->SetLineColor(kViolet-4);
      if (std::string(files[i]).find("equalwidth") != std::string::npos){
        graph->SetLineColor(kViolet+4);
      }
      if (std::string(files[i]).find("03e2_2") != std::string::npos && override_03e2_2){
        graph->SetLineColor(kViolet-6);
      }
      if (std::string(files[i]).find("03e2_3") != std::string::npos && override_03e2_3){
        graph->SetLineColor(kViolet-2);
      }
      if (std::string(tags[i]).find("2020a1_v6") != std::string::npos) version_label = " 2020a1 v6";
      if (std::string(tags[i]).find("2024b_v9") != std::string::npos){ 
        version_label = " 2024b v9";
        graph->SetLineColor(kMagenta+3);
      }
      legend->AddEntry(graph,("5#sigma PRISM3 "+syst_label+version_label).c_str(),"L");
      //std::cout << "legend entry = " << ("5#sigma PRISM3 "+syst_label).c_str() << std::endl;
      /*if (std::string(files[i]).find("reducedmodes") != std::string::npos){
        graph->SetLineColor(kViolet-6);
      }*/
    } else if(std::string(files[i]).find("prism5") != std::string::npos){
      graph->SetLineColor(kPink-4);
      legend->AddEntry(graph,("5#sigma PRISM5 "+syst_label+version_label).c_str(),"L");
    } else if(std::string(files[i]).find("prism8_2") != std::string::npos){
      graph->SetLineColor(kSpring-6);
      legend->AddEntry(graph,("5#sigma PRISM8_2 "+syst_label+version_label).c_str(),"L");
      /*if (std::string(files[i]).find("reducedmodes") != std::string::npos){
        graph->SetLineColor(kOrange+4);
      }*/
    } else if(std::string(files[i]).find("prism8") != std::string::npos){
      graph->SetLineColor(kOrange-3);
      legend->AddEntry(graph,("5#sigma PRISM8 "+syst_label+version_label).c_str(),"L");
    } else graph->SetLineColor(kBlack);

    if (i == 0) {
      graph->Draw("AL");
      graph->SetTitle("");
      graph->GetXaxis()->SetTitle("sin^{2}#theta_{#mu#mu}");
      graph->GetYaxis()->SetTitle("#Delta m^{2}_{41}");
      graph->GetXaxis()->SetTitleFont(132);
      graph->GetYaxis()->SetTitleFont(132);
      graph->GetXaxis()->SetTitleSize(0.05);
      graph->GetYaxis()->SetTitleSize(0.05);
      graph->GetXaxis()->SetTitleOffset(0.9);
      graph->GetYaxis()->SetTitleOffset(0.9);
      graph->GetXaxis()->SetLabelFont(132);
      graph->GetYaxis()->SetLabelFont(132);
      graph->GetXaxis()->SetLimits(0.001,1);
      graph->GetYaxis()->SetRangeUser(0.01,100);
    } else {
      graph->Draw("L SAME");
    }
    plottedGraphs.push_back(graph);
    file->Close();
  }
  legend->Draw();
  latex->DrawLatex(0.35, 110, "SBND (6.6e+20 POT)");
  canvas->Update();
  std::string fileName = "5sigma_contours_";
  for (size_t i = 0; i < tags.size(); ++i) {
      fileName += tags[i];
      if (i < tags.size() - 1) {
	  fileName += "_";
      }
  }
  std::string fileName1 = fileName + ".png";
  std::string fileName2 = fileName + ".pdf";
  canvas->SaveAs(fileName1.c_str());
  canvas->SaveAs(fileName2.c_str());
  delete canvas;
  delete legend;

  return plottedGraphs;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TGraph* divideXValues(const TGraph* graph1, const TGraph* graph2) {
    if (!graph1 || !graph2) {
        return nullptr;
    }
    //graph1=_ref, graph2=_1
    int npoints = graph1->GetN();
    double Xvalue_ref       [npoints];
    double Xvalue_ref_ratio [npoints];
    double Yvalue_ref       [npoints];
    double Xvalue_1         [npoints];
    double Xvalue_1_ratio   [npoints];
    TGraph inv_1(graph2->GetN(), graph2->GetY(), graph2->GetX());
    for(int i = 0; i < npoints; i++){
      Xvalue_ref[i] = graph1->GetX()[i];
      Yvalue_ref[i] = graph1->GetY()[i];
      Xvalue_1[i] = inv_1.Eval(graph1->GetY()[i]);
      Xvalue_ref_ratio[i] = Xvalue_ref[i] / Xvalue_ref[i];
      Xvalue_1_ratio[i] = Xvalue_1[i] / Xvalue_ref[i];
    } 
    TGraph *graphRatio = new TGraph(npoints, Xvalue_1_ratio, Yvalue_ref);

/*
    TGraph *graphRatio;
    Int_t nPoints1 = graph1->GetN();
    Int_t nPoints2 = graph2->GetN();

    if (nPoints1 == nPoints2) {
      Double_t *xValues1 = graph1->GetX();
      Double_t *yValues1 = graph1->GetY();
      Double_t *xValues2 = graph2->GetX();

      Double_t *xValuesRatio = new Double_t[nPoints1];

      for (Int_t i = 0; i < nPoints1; ++i) {
	  if (xValues2[i] != 0.0) {
	      xValuesRatio[i] = xValues1[i] / xValues2[i];
	  } else {
	      // Avoid division by zero
	      xValuesRatio[i] = 0.0;
	  }
      }

      graphRatio = new TGraph(nPoints1, xValuesRatio, yValues1);
      std::cout << "Completed division" << std::endl;
    } else {
      std::cout << "nPoints1 != nPoints2" <<std::endl;

      Double_t *xValuesRatio = new Double_t[nPoints1];
      Double_t *yValues1 = graph1->GetY();

      for (int i = 0; i < nPoints1; i++){
        double x1, y1, x2;
        graph1->GetPoint(i, x1, y1);
        x2 = graph2->Eval(y1);

        if (x2 != 0.0){
          xValuesRatio[i] = x1/x2;
        } else{
          xValuesRatio[i] = 0.0;
        }
        graphRatio = new TGraph(nPoints1, xValuesRatio, yValues1);
      }
      std::cout << "Completed division" << std::endl;
    }*/
    return graphRatio;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void plot_contour_ratio(bool plt_ratio,
		        bool override_03e2_2,
		        bool override_03e2_3
) {
  int n_contours;
  std::vector<std::string> files;
  std::vector<std::string> tags;
  
  std::cout << "Enter number of contours" << std::endl;
  std::cin >> n_contours;
  for (int i = 1; i <= n_contours; i++){
    std::string curr_file, curr_tag;
    std::cout << "Enter file name " << i <<std::endl;
    std::cin >> curr_file;
    std::cout << "Enter tag " << i <<std::endl;
    std::cin >> curr_tag;
    files.push_back(curr_file);
    tags.push_back(curr_tag);
  }

  std::vector<TGraph*> graphs = plotGraphs(files, tags, override_03e2_2, override_03e2_3);

  if (plt_ratio){
    TCanvas *canvas = new TCanvas("canvas", "Graphs", 800, 600);
    canvas->SetRightMargin(0.08);
    canvas->SetLeftMargin(0.12);
    canvas->SetTopMargin(0.08);
    canvas->SetBottomMargin(0.12);
    canvas->SetLogy();
    TLegend *legend = new TLegend(0.15, 0.15, 0.55, 0.45);
    legend->SetTextSize(0.03);
    legend->SetTextFont(132);
    legend->SetTextColor(1);
    legend->SetFillStyle(0);
    legend->SetLineWidth(0);
    for (int i = 0; i < n_contours; i++){
      TGraph *ratio = divideXValues(graphs[0],graphs[i]);
      ratio->SetLineWidth(2);

      if(std::string(files[i]).find("03e2_2") != std::string::npos) ratio->SetLineStyle(2);
      else if(std::string(files[i]).find("03e2_3") != std::string::npos) ratio->SetLineStyle(5);
      else if(std::string(files[i]).find("03d1") != std::string::npos) ratio->SetLineStyle(9);
      else if(std::string(files[i]).find("03d2") != std::string::npos) ratio->SetLineStyle(6);
      else if(std::string(files[i]).find("stat") != std::string::npos) ratio->SetLineStyle(7);

      if(std::string(files[i]).find("sbnd") != std::string::npos) ratio->SetLineColor(kAzure-4);
      else if(std::string(files[i]).find("sbn") != std::string::npos) ratio->SetLineColor(kTeal-6);
      else if(std::string(files[i]).find("prism3") != std::string::npos && std::string(files[i]).find("equalstat") != std::string::npos) ratio->SetLineColor(kViolet-4);
      else if(std::string(files[i]).find("prism3") != std::string::npos && std::string(files[i]).find("equalwidth") != std::string::npos) ratio->SetLineColor(kViolet+4);
      else if(std::string(files[i]).find("prism3") != std::string::npos) ratio->SetLineColor(kViolet-4);
      else if(std::string(files[i]).find("prism5") != std::string::npos) ratio->SetLineColor(kPink-4);
      else if(std::string(files[i]).find("prism8_2") != std::string::npos) ratio->SetLineColor(kSpring-6);
      else if(std::string(files[i]).find("prism8") != std::string::npos) ratio->SetLineColor(kOrange-3);
      else ratio->SetLineColor(kBlack);
      if (i == 0) {
	ratio->Draw("AL");
        ratio->SetLineColor(kBlack);
        ratio->SetLineStyle(1);
	ratio->GetXaxis()->SetTitle("Relative sin^{2}#theta_{#mu#mu}");
	ratio->GetYaxis()->SetTitle("#Delta m^{2}_{41}");
	ratio->GetXaxis()->SetTitleFont(132);
	ratio->GetYaxis()->SetTitleFont(132);
	ratio->GetXaxis()->SetTitleSize(0.05);
	ratio->GetYaxis()->SetTitleSize(0.05);
	ratio->GetXaxis()->SetTitleOffset(0.9);
	ratio->GetYaxis()->SetTitleOffset(0.9);
	ratio->GetXaxis()->SetLabelFont(132);
	ratio->GetYaxis()->SetLabelFont(132);
	ratio->GetXaxis()->SetLimits(0.0,1.1);
	ratio->GetYaxis()->SetRangeUser(1.,100);
      } else {
	ratio->Draw("L SAME");
      }
      std::vector<std::string> new_tags;
      for (int i=0;i<tags.size();i++){
        std::string curr_tag(tags[i]);
	size_t pos = curr_tag.find("sbnd");
	while (pos != std::string::npos) {
	    curr_tag.replace(pos, 4, "SBND");
	    pos = curr_tag.find("sbnd", pos + 4); // Move to next occurrence
	}
	pos = curr_tag.find("sbn");
	while (pos != std::string::npos) {
	    curr_tag.replace(pos, 3, "SBN");
	    pos = curr_tag.find("sbn", pos + 3); // Move to next occurrence
	}
	// Replace "_reduced_modes"
	pos = curr_tag.find("_reducedmodes");
	while (pos != std::string::npos) {
	    curr_tag.replace(pos, 13, " reduced modes");
	    pos = curr_tag.find("_reducedmodes", pos + 13); // Move to next occurrence
	}
	// Replace "_equalwidth"
	pos = curr_tag.find("_equalwidth");
	while (pos != std::string::npos) {
	    curr_tag.replace(pos, 11, " equal-width");
	    pos = curr_tag.find("_equalwidth", pos + 11); // Move to next occurrence
	}
	// Replace "_equalstat"
	pos = curr_tag.find("_equalstat");
	while (pos != std::string::npos) {
	    curr_tag.replace(pos, 10, " equal-stat");
	    pos = curr_tag.find("_equalstat", pos + 10); // Move to next occurrence
	}
	// Replace "_" with a space
	pos = curr_tag.find("_0");
	while (pos != std::string::npos) {
	    curr_tag.replace(pos, 2, " 0");
	    pos = curr_tag.find("_0", pos + 2); // Move to next occurrence
	}
	// Replace "_" with a space
	pos = curr_tag.find("_s");
	while (pos != std::string::npos) {
	    curr_tag.replace(pos, 2, " s");
	    pos = curr_tag.find("_", pos + 2); // Move to next occurrence
	}
	// Replace "prism" with "PRISM"
	pos = curr_tag.find("prism");
	while (pos != std::string::npos) {
	    curr_tag.replace(pos, 5, "PRISM");
	    pos = curr_tag.find("prism", pos + 5); // Move to next occurrence
	}
        new_tags.push_back(curr_tag);
      }
      legend->AddEntry(ratio,("Ratio "+new_tags[i]+" to "+new_tags[0]).c_str(),"L");
    }
    legend->Draw();
    TLatex *latex = new TLatex();
    latex->SetTextSize(0.02);
    latex->DrawLatex(0.93, 105, "SBND (6.6e+20 POT)");
    canvas->Update();
    std::string fileName = "5sigma_ratios_";
    for (size_t i = 0; i < n_contours; ++i) {
	fileName += tags[i];
	if (i < tags.size() - 1) {
	    fileName += "_";
	}
    }
    std::string fileName1 = fileName + ".png";
    std::string fileName2 = fileName + ".pdf";
    canvas->SaveAs(fileName1.c_str());
    canvas->SaveAs(fileName2.c_str());
  }
}
