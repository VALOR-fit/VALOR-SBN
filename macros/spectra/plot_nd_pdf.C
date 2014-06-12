//
// ------------------------------------------------------------------------------------------------
// Simple program to write out the LBNx/ND PDFs and MC templates.
//
// Costas Andreopoulos
// ------------------------------------------------------------------------------------------------
//

void plot_nd_pdf(const char * filename, const char * tag = "valor")
{
  using namespace std;
  using namespace valor;
  
  double enu_reco_max = 12.; // 20 - 120 GeV is one bin, show only up to 21

  const int n_pdf_slices = 6;
  assert(n_pdf_slices >= conv::kNYrecoBinsSb);

  int pdf_slice_color[n_pdf_slices] = 
  {
     kRed+1,   kOrange+7,   kYellow, kGreen+2,  kAzure+1, kViolet-1
  };

  TFile * fin = new TFile(filename, "read");
/*
  //
  // Read-in and plot 2-D PDFs
  // This does not seem to be too useful, because of the very variable binning.
  // 2-D PDFs will need to translated back to a uniform fine binning to show here.
  // Showing 2-D plots with variable binning may be more informative if, what is plotted
  // is something like the error in each bin, of the level of agreement between toyMC and bestfit.
  //
  TH2D * pdf_tot[conv::kNBeamConf][conv::kNNDSamples][conv::kNMaxBinZones]; 
  TCanvas * c_pdf_tot[conv::kNBeamConf][conv::kNNDSamples];
  for(int ibeam = 0; ibeam <conv::kNBeamConf; ibeam++) {
    conv::BeamConf_t b = conv::kNDBeamConf[ibeam];
    if(b == conv::kbUndefined) continue;
    for(int isample = 0; isample < conv::kNNDSamples; isample++) {
      conv::NDSample_t s = conv::kNDSample[isample];
      if(s == conv::ksNDUndefined) continue;
      for(int izone = 0; izone < conv::kNMaxBinZones; izone++) {
         const char * name = Form("%s_%s_%s_%s_z%d", 
             tag, "pdft_rf", util::AsString(b).c_str(), util::AsString(s).c_str(), izone);
         pdf_tot[ibeam][isample][izone] = (TH2D*) fin->Get(name); 
      }//izone
    }//isample
  }//ibeam
  for(int ibeam = 0; ibeam <conv::kNBeamConf; ibeam++) {
    conv::BeamConf_t b = conv::kNDBeamConf[ibeam];
    if(b == conv::kbUndefined) continue;
    for(int isample = 0; isample < conv::kNNDSamples; isample++) {
      conv::NDSample_t s = conv::kNDSample[isample];
      if(s == conv::ksNDUndefined) continue;
      const char * c_name = Form("c_pdf_tot_%s_%s", util::AsString(b), util::AsString(s));
      c_pdf_tot[ibeam][isample] = new TCanvas(c_name,"",20,20,600,600);
      TH2F * hframe = (TH2F *) c_pdf_tot[ibeam][isample]->DrawFrame(enu_reco_min,y_reco_min,enu_reco_max,y_reco_max);
      hframe->Draw();
      for(int izone = 0; izone < conv::kNMaxBinZones; izone++) {
         if(!pdf_tot[ibeam][isample][izone]) continue;
         pdf_tot[ibeam][isample][izone]->Draw("colzsame");
      }//izone
      c_pdf_tot[ibeam][isample]->Update();
    }//isample
  }//ibeam
*/

  //
  // Read-in and plot 1-D total PDFs slices
  //
  TCanvas * c_pdf_slice[conv::kNBeamConf];
  for(int ibeam = 0; ibeam <conv::kNBeamConf; ibeam++) {
    conv::BeamConf_t b = conv::kNDBeamConf[ibeam];
    if(b == conv::kbUndefined) continue;
    const char * c_name  = Form("c_pdf_slice_%s", util::AsString(b));
    c_pdf_slice[ibeam] = new TCanvas(c_name,"",20,20,700,700);
  //c_pdf_slice[ibeam]->Divide(conv::kNNDSamples);
    c_pdf_slice[ibeam]->Divide(2,3);
    double max[conv::kNNDSamples] = { -999 };
    int ic = 0;   
    for(int isample = 0; isample < conv::kNNDSamples; isample++) {
      conv::NDSample_t s = conv::kNDSample[isample];
      if(s == conv::ksNDUndefined) continue;
      THStack * stack = new THStack("stack","spectrum contributions");
      TH1D * pdf_slice[conv::kNYrecoBinsSb];
      for(int iy = 0; iy < conv::kNYrecoBinsSb; iy++) {
             const char * name = Form("%s_%s_%s_%s_y%d",
                tag, "pdfsbts_rf", util::AsString(b).c_str(), util::AsString(s).c_str(), iy);
             pdf_slice[iy] = (TH1D*) fin->Get(name);
      }//iy
      // Scan for max in desired Erange
      for(int ebin = 1; ebin <= pdf_slice[0]->GetNbinsX(); ebin++) {
         if(pdf_slice[0]->GetBinCenter(ebin) < enu_reco_max ) {
           double sum = 0;
           for(int iy = 0; iy < conv::kNYrecoBinsSb; iy++) {
              double val = pdf_slice[iy]->GetBinContent(ebin);
              sum += val;
           }
           max[isample] = TMath::Max(max[isample], sum);           
         }//<emax
      }//ebin
      // Start drawing
      ic++;
      const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(s);
      TLegend * leg = new TLegend(0.50,0.40,0.88,0.80);  
      leg->SetFillColor(0);
      for(int iy = 0; iy < conv::kNYrecoBinsSb; iy++) {
          if(pdf_slice[iy]) {
               pdf_slice[iy]->SetFillColor(pdf_slice_color[iy]); 
               pdf_slice[iy]->SetLineWidth(1); 
               stack->Add(pdf_slice[iy]);
               leg->AddEntry(pdf_slice[iy],Form("y = [%.2f,%.2f]", y_reco_bin_edges_sb[iy], y_reco_bin_edges_sb[iy+1]),"LF");
          }
       }
       c_pdf_slice[ibeam]->cd(ic);
       TH1F * hframe = (TH1F*)c_pdf_slice[ibeam]->GetPad(ic)->DrawFrame(0,0,enu_reco_max,1.2*max[isample]);
       hframe->Draw();
       const char * title_str = Form("%s / %s", util::AsString(b).c_str(), util::AsStringTeX(s,true).c_str());
       TLatex * title = new TLatex(1,1.07*max[isample],title_str);
       title->Draw(); 
       hframe->GetXaxis()->SetTitle("Reco. E_{#nu} (GeV)");
       hframe->GetYaxis()->SetTitle("Events /bin");
       stack->Draw("same");
       leg->Draw();
    }//isample
  }//ibeam


  //
  // Read-in and plot Ereco spectra and contributions from various modes
  //

  TCanvas * c_pdf_contrib[conv::kNBeamConf];
  for(int ibeam = 0; ibeam <conv::kNBeamConf; ibeam++) {
    conv::BeamConf_t b = conv::kNDBeamConf[ibeam];
    if(b == conv::kbUndefined) continue;
    const char * c_name = Form("c_pdf_contrib_%s", util::AsString(b));
    c_pdf_contrib[ibeam] = new TCanvas(c_name,"",20,20,700,700);
  //c_pdf_contrib[ibeam]->Divide(conv::kNNDSamples);
    c_pdf_contrib[ibeam]->Divide(2,3);
    int ic = 0;
    double max[conv::kNNDSamples] = { -999 };
    for(int isample = 0; isample < conv::kNNDSamples; isample++) {
      conv::NDSample_t s = conv::kNDSample[isample];
      if(s == conv::ksNDUndefined) continue;
      THStack * stack = new THStack("stack","spectrum contributions");
      TH1D * pdf_contrib        [conv::kNReacModes]       = { 0 };
      TH1D * pdf_contrib_coarse [conv::kNReacModesCoarse] = { 0 };
      for(int imode = 0; imode < conv::kNReacModes; imode++) {
           conv::ReacMode_t m = conv::kNDReactionModes[isample][imode];
           if(m == conv::kmUndefined) continue;
            const char * name = Form("%s_%s_%s_%s_%s",
              tag, "pdfsbcs_rf", util::AsString(b).c_str(), util::AsString(s).c_str(), util::AsString(m).c_str());
            pdf_contrib[imode] = (TH1D*) fin->Get(name);
            if(pdf_contrib[imode]) {
                conv:: ReacModeCoarse_t mc = conv::kNDMappingToCoarseModes[isample][imode];
                if(mc == conv::kmcUndefined) continue;
                for(int imodec = 0; imodec < conv::kNReacModesCoarse; imodec++) {
                  if(mc != conv::kNDReactionModesCoarse[isample][imodec]) continue;
                  if(pdf_contrib_coarse[imodec] == 0) {
                     pdf_contrib_coarse[imodec] = new TH1D(*pdf_contrib[imode]);
                  } else {
                     pdf_contrib_coarse[imodec]->Add(pdf_contrib[imode]);
                  }           
                }//imodec
            }//!null
            else {
              cerr << "Null [" << name << "]" << endl;
            }
      }//imode
      // Scan for max in desired Erange
      for(int ebin = 1; ebin <= pdf_contrib[0]->GetNbinsX(); ebin++) {
         if(pdf_contrib[0]->GetBinCenter(ebin) < enu_reco_max ) {
           double sum = 0;
           for(int imode = 0; imode < conv::kNReacModes; imode++) {
              double val = pdf_contrib[imode]->GetBinContent(ebin);
              sum += val;
           }
           max[isample] = TMath::Max(max[isample], sum);           
         }//<emax
      }//ebin
      // Start drawing
      ic++;
      TLegend * leg = new TLegend(0.5,0.3,0.9,0.8);  
      leg->SetFillColor(0);
      for(int imodec = 0; imodec < conv::kNReacModesCoarse; imodec++) {
          conv:: ReacModeCoarse_t mc = conv::kNDReactionModesCoarse[isample][imodec];
          if(mc == conv::kmcUndefined) continue;
          pdf_contrib_coarse[imodec]->SetLineWidth(1); 
          pdf_contrib_coarse[imodec]->SetLineColor(conv::kNDReactionModesCoarseFormatting[isample][imodec][0]); 
          pdf_contrib_coarse[imodec]->SetFillColor(conv::kNDReactionModesCoarseFormatting[isample][imodec][1]); 
          pdf_contrib_coarse[imodec]->SetFillStyle(conv::kNDReactionModesCoarseFormatting[isample][imodec][2]); 
          stack->Add(pdf_contrib_coarse[imodec]);
          leg->AddEntry(pdf_contrib_coarse[imodec],Form("%s",util::AsStringTex(mc,true).c_str()), "LF");
      }//imodec
      c_pdf_contrib[ibeam]->cd(ic);
      TH1F * hframe = (TH1F*)c_pdf_contrib[ibeam]->GetPad(ic)->DrawFrame(0,0,enu_reco_max,1.2*max[isample]);
      hframe->Draw();
      const char * title_str = Form("%s / %s", util::AsString(b).c_str(), util::AsStringTeX(s,true).c_str());
      TLatex * title = new TLatex(1,1.07*max[isample],title_str);
      title->Draw(); 
      hframe->GetXaxis()->SetTitle("Reco. E_{#nu} (GeV)");
      hframe->GetYaxis()->SetTitle("Events /bin");
      stack->Draw("same");
      leg->Draw();
    }//isample
  }//ibeam

}
