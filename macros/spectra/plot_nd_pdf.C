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
  
  double enu_reco_max = 21.; // 20 - 120 GeV is one bin, show only up to 21

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
             tag, "pdft_rt", util::AsString(b).c_str(), util::AsString(s).c_str(), izone);
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
  // Read-in and plot 1-D PDFs slices
  //
  TCanvas * c_pdf_slice[conv::kNBeamConf][conv::kNNDSamples];
  for(int ibeam = 0; ibeam <conv::kNBeamConf; ibeam++) {
    conv::BeamConf_t b = conv::kNDBeamConf[ibeam];
    if(b == conv::kbUndefined) continue;
    for(int isample = 0; isample < conv::kNNDSamples; isample++) {
      conv::NDSample_t s = conv::kNDSample[isample];
      if(s == conv::ksNDUndefined) continue;

          const char * c_name = Form("c_pdf_slice_%s_%s", util::AsString(b), util::AsString(s));
          c_pdf_slice[ibeam][isample] = new TCanvas(c_name,"",20,20,600,600);

          THStack * stack = new THStack("stack","spectrum contributions");

          TH1D * pdf_slice[conv::kNYrecoBinsSb];
          for(int iy = 0; iy < conv::kNYrecoBinsSb; iy++) {
             const char * name = Form("%s_%s_%s_%s_y%d",
                tag, "pdfsbts_rt", util::AsString(b).c_str(), util::AsString(s).c_str(), iy);
             pdf_slice[iy] = (TH1D*) fin->Get(name);
          }//iy
          const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(s);
          TLegend * leg = new TLegend(0.7,0.5,0.9,0.9);  
          leg->SetFillColor(0);
          leg->SetHeader( Form("%s / %s", util::AsString(b).c_str(), util::AsString(s).c_str()) );
          for(int iy = 0; iy < conv::kNYrecoBinsSb; iy++) {
            if(pdf_slice[iy]) {
//               pdf_slice[iy]->SetLineColor(pdf_slice_color[iy]); 
               pdf_slice[iy]->SetFillColor(pdf_slice_color[iy]); 
//             pdf_slice[iy]->SetFillStyle(3544); 
               stack->Add(pdf_slice[iy]);
               leg->AddEntry(pdf_slice[iy],Form("y = [%f,%f]", y_reco_bin_edges_sb[iy], y_reco_bin_edges_sb[iy+1]),"LF");
            }
          }
          stack->Draw();
          stack->GetHistogram()->GetXaxis()->SetTitle("reconstructed E_{#nu} (GeV)");
          stack->GetHistogram()->GetYaxis()->SetTitle("events /bin");
          leg->Draw();

    }//isample
  }//ibeam

}
