//
// ------------------------------------------------------------------------------------------------
// Simple program to plot DUNE/ND PDFs and MC templates written out by write_nd_pdf.C
//
// Costas Andreopoulos
// ------------------------------------------------------------------------------------------------
//

#include <vector>

void plot_pdf(
  const char * config_file,
  const char * filename,
  const char * tag = "valor",
  TString   option = "",
  const char * out_tag = "valor",
  const char * image_save_format = "",
  int canv_size_x = 700,
  int canv_size_y = 700
)
{
  using namespace std;
  using namespace valor;
  
  double enu_reco_max = 12.; 

  const int n_pdf_slices = 10; //
  
  const int max_plots_per_canv = 12;

  int pdf_slice_color[n_pdf_slices] = 
  {
     kRed+1,   kOrange+7,   kYellow, kGreen+2,  kAzure+1, kViolet-1
  };
  
  bool write_image(image_save_format[0]);

  TFile * fin = new TFile(filename, "read");
  assert(fin);
  
  const char * binning = (option.Contains("OB")?"ob":"sb");
  
  
  // Couple of vectors to keep all our objects
  vector<TCanvas*> all_canvases;
  vector<TH1*> all_hists;
  
  // First build a FitElements to tell us which samples we're plotting
  std::string config_path = util::CompleteConfigPath(config_file);
  CompoundFitElements elems;
  elems.Read(config_path.c_str(),"nomc nosplines");
  CompoundFitModel & model = *(elems.FitModel());
  
  // A vector storing the list of submodels to plot on each canvas
  // Outer vector is per canvas, inner vector is plots on said canvas
  vector<vector<int>> canvas_content;
  canvas_content.push_back(vector<int>());
  
  conv::Detector_t last_det  = conv::kdUndefined;
  conv::BeamConf_t last_beam = conv::kbUndefined;
  
  // First loop over our selections to work out how many canvases we're drawing
  // We'll do a new canvas every time the detector changes, the beam current changes or we go above max_plots_per_canv
  for (int isubmodel = 0 ; isubmodel < model.GetNSubModels() ; isubmodel++) {
    GenericSingleSampleFitModel & submodel = *(model.GetSubModel(isubmodel));
    conv::Detector_t d = submodel.GetDetector();
    conv::BeamConf_t b = submodel.GetBeam();
    if (d == conv::kdUndefined) {continue;}
    if (b == conv::kbUndefined) {continue;}
    
    // If we don't match the last detector/beam start a new TCanvas
    if ((d!=last_det || b!= last_beam) && isubmodel) {
      canvas_content.push_back(vector<int>());
    }
    
    last_det  = d;
    last_beam = b;
    
    // If our canvas is full, start a new one
    if (canvas_content.back().size() == max_plots_per_canv) {
      canvas_content.push_back(vector<int>());
    }
    
    // Append the submodel number to the canvas' list
    canvas_content.back().push_back(isubmodel);
  }
  
  // Loop over the canvases we'll be drawing
  for (int icanvas = 0 ; icanvas < canvas_content.size() ; icanvas++) {
    // Calculate number of vertical and horizontal plots we need
    int plots_on_this_canv = canvas_content[icanvas].size();
    int nrows = 1;
    int ncols = 1;
    while (nrows * ncols < plots_on_this_canv) {
      if (nrows < ncols) {nrows++;}
      else {ncols++;}
    }
    
    // make a canvas
    TString c_name = TString::Format("c_pdf_tot_%s_%s_%u",
      util::AsString(d),util::AsString(b).c_str(),icanvas);
    TCanvas * c_pdf_tot = new TCanvas(c_name.Data(),"",20,20,canv_size_x,canv_size_y);
    c_pdf_tot->Divide(nrows,ncols);
    all_canvases.push_back(c_pdf_tot);
    
    for (int iplot = 0 ; iplot < canvas_content[icanvas].size() ; iplot++) {
      int isubmodel = canvas_content[icanvas][iplot];
      GenericSingleSampleFitData & submodel = *(model.GetSubModel(isubmodel));
      conv::Detector_t d = submodel.GetDetector();
      conv::BeamConf_t b = submodel.GetBeam();
      conv::Sample_t   s = submodel.GetSample();
      
      TString pdf_tot_name = TString::Format("%s_%s_%s_%s_%s_%s", 
         tag, "pdft",binning,"rf", util::AsString(b).c_str(), util::AsString(s).c_str());
      TObject * tmp_obj = fin->Get(pdf_tot_name.Data());
      assert(tmp_obj);
      TH2D * pdf_tot = new TH2D(*((TH2D*)tmp_obj));
      all_hists.push_back(pdf_tot);
      
      TVirtualPad * this_pad = c_pdf_tot->cd(iplot+1); // Pad for this plot
      TH1F * hframe = (TH1F*)this_pad->DrawFrame(0,0,enu_reco_max,1);
      hframe->Draw();
      pdf_tot->Draw("colzsame");
    }
    
    c_pdf_tot->Update();
    if (write_image) {
      TString pdf_tot_filename = c_name+"."+image_save_format;
      c_pdf_tot->Write(pdf_tot_filename.Data());
    }
  }
  return;
}
    //~ 
    //~ int ic=0;
    //~ for(int isample = 0; isample < conv::kNSamples; isample++) {
      //~ conv::Sample_t s = conv::kSample[ibeam][isample];
      //~ if(s == conv::ksUndefined) continue;
//~ //    for(int izone = 0; izone < conv::kNMaxBinZones; izone++) {
//~ //       TString name = TString::Format("%s_%s_%s_%s_z%d", 
//~ //           tag, "pdft_ob_rf", util::AsString(b).c_str(), util::AsString(s).c_str(), izone);
//~ //       pdf_tot[ibeam][isample][izone] = (TH2D*) fin->Get(name.Data()); 
//~ //    }//izone
//~ 
      //~ TString name = TString::Format("%s_%s_%s_%s_%s_%s", 
           //~ tag, "pdft",binning,"rf", util::AsString(b).c_str(), util::AsString(s).c_str());
      //~ pdf_tot[ibeam][isample] = (TH2D*) fin->Get(name.Data());
      //~ ic++;
      //~ c_pdf_tot[ibeam]->cd(ic);
      //~ TH1F * hframe = (TH1F*)c_pdf_tot[ibeam]->GetPad(ic)->DrawFrame(0,0,enu_reco_max,1);
      //~ hframe->Draw();
//~ //    for(int izone = 0; izone < conv::kNMaxBinZones; izone++) {
//~ //       if(!pdf_tot[ibeam][isample][izone]) continue;
//~ //       pdf_tot[ibeam][isample][izone]->Draw("colzsame");
//~ //    }//izone
      //~ pdf_tot[ibeam][isample]->Draw("colzsame");
    //~ }//isample
  //~ }//ibeam
//~ 
  //~ //
  //~ // Read-in and plot 1-D PDFs slices for different y ranges
  //~ //..............................................................................................
  //~ //
//~ 
  //~ TCanvas * c_pdf_slice[conv::kNBeamConf];
  //~ for(int ibeam = 0; ibeam <conv::kNBeamConf; ibeam++) {
    //~ conv::BeamConf_t b = conv::kBeamConf[ibeam];
    //~ if(b == conv::kbUndefined) continue;
    //~ TString c_name  = TString::Format("c_pdf_slice_%s", util::AsString(b).c_str());
    //~ c_pdf_slice[ibeam] = new TCanvas(c_name.Data(),"",20,20,canv_size_x,canv_size_y);
  //~ //c_pdf_slice[ibeam]->Divide(conv::kNSamples);
    //~ c_pdf_slice[ibeam]->Divide(3,3);
    //~ double max[conv::kNSamples] = { -999 };
    //~ int ic = 0;   
    //~ for(int isample = 0; isample < conv::kNSamples; isample++) {
      //~ conv::Sample_t s = conv::kSample[ibeam][isample];
      //~ if(s == conv::ksUndefined) continue;
      //~ THStack * stack = new THStack("stack","spectrum contributions");
      //~ const int n_y_reco_bins_sb = util::NumYrecoBinsSb(s);
      //~ TH1D * pdf_slice[n_pdf_slices] = {0};
      //~ for(int iy = 0; iy < n_y_reco_bins_sb; iy++) {
        //~ TString name = TString::Format("%s_%s_%s_%s_%s_%s_y%d",
                //~ tag, "pdfts",binning,"rf", util::AsString(b).c_str(), util::AsString(s).c_str(), iy);
             //~ cout << "getting TH1D * object: " << name << endl;
             //~ pdf_slice[iy] = (TH1D*) fin->Get(name);
      //~ }//iy
      //~ // Scan for max in desired Erange
      //~ for(int ebin = 1; ebin <= pdf_slice[0]->GetNbinsX(); ebin++) {
         //~ if(pdf_slice[0]->GetBinCenter(ebin) < enu_reco_max ) {
           //~ double sum = 0;
           //~ for(int iy = 0; iy < n_y_reco_bins_sb; iy++) {
              //~ double val = pdf_slice[iy]->GetBinContent(ebin);
              //~ sum += val;
           //~ }
           //~ max[isample] = TMath::Max(max[isample], sum);           
         //~ }//<emax
      //~ }//ebin
      //~ // Start drawing
      //~ ic++;
      //~ const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(s);
      //~ TLegend * leg = new TLegend(0.50,0.40,0.88,0.80);  
      //~ leg->SetFillColor(0);
      //~ for(int iy = 0; iy < n_y_reco_bins_sb; iy++) {
          //~ if(pdf_slice[iy]) {
               //~ pdf_slice[iy]->SetFillColor(pdf_slice_color[iy]); 
               //~ pdf_slice[iy]->SetLineWidth(1); 
               //~ stack->Add(pdf_slice[iy]);
               //~ leg->AddEntry(pdf_slice[iy],Form("y = [%.2f,%.2f]", y_reco_bin_edges_sb[iy], y_reco_bin_edges_sb[iy+1]),"LF");
          //~ }
      //~ }
      //~ c_pdf_slice[ibeam]->cd(ic);
      //~ TH1F * hframe = (TH1F*)c_pdf_slice[ibeam]->GetPad(ic)->DrawFrame(0,0,enu_reco_max,1.2*max[isample]);
      //~ hframe->Draw();
      //~ TString title_str = TString::Format("%s / %s", util::AsString(b).c_str(), util::AsStringTeX(s,true).c_str());
      //~ TLatex * title = new TLatex(1,1.07*max[isample],title_str.Data());
      //~ title->Draw(); 
      //~ if(util::IsCC(s)) {
        //~ hframe->GetXaxis()->SetTitle("Reco. E_{#nu} (GeV)");
      //~ } else {
        //~ hframe->GetXaxis()->SetTitle("Visible Energy (GeV)");
      //~ }
      //~ hframe->GetYaxis()->SetTitle("Events /bin");
      //~ stack->Draw("same");
      //~ leg->Draw();
       //~ 
    //~ }//isample
    //~ if (write_image) {
      //~ TString imgname = TString::Format("%s_spectrum_%s_y.%s",
        //~ out_tag, util::AsString(b).c_str(),image_save_format);
      //~ c_pdf_slice[ibeam]->Print(imgname.Data());
    //~ }
  //~ }//ibeam
//~ 
//~ 
  //~ //
  //~ // Read-in and plot Ereco spectra and contributions from various modes
  //~ //..............................................................................................
  //~ //
//~ 
  //~ TCanvas * c_pdf_contrib[conv::kNBeamConf];
  //~ for(int ibeam = 0; ibeam <conv::kNBeamConf; ibeam++) {
    //~ conv::BeamConf_t b = conv::kBeamConf[ibeam];
    //~ if(b == conv::kbUndefined) continue;
    //~ TString c_name = TString::Format("c_pdf_contrib_%s", util::AsString(b).c_str());
    //~ c_pdf_contrib[ibeam] = new TCanvas(c_name.Data(),"",20,20,canv_size_x,canv_size_y);
  //~ //c_pdf_contrib[ibeam]->Divide(conv::kNSamples);
    //~ c_pdf_contrib[ibeam]->Divide(3,3);
    //~ int ic = 0;
    //~ double max[conv::kNSamples] = { -999 };
    //~ for(int isample = 0; isample < conv::kNSamples; isample++) {
      //~ conv::Sample_t s = conv::kSample[ibeam][isample];
      //~ if(s == conv::ksUndefined) continue;
      //~ cout << "Creating stack for beam: " << util::AsString(b) << " / sample: " << util::AsString(s) << endl;
      //~ THStack * stack = new THStack("stack","spectrum contributions");
      //~ TH1D * pdf_contrib        [conv::kNReacModes]       = { 0 };
      //~ TH1D * pdf_contrib_coarse [conv::kNReacModesCoarse] = { 0 };
      //~ for(int imode = 0; imode < conv::kNReacModes; imode++) {
        //~ conv::ReacMode_t m = conv::kReactionModes[isample][imode];
        //~ if(m == conv::kmUndefined) continue;
        //~ cout << "Taking mode: " << util::AsString(m) << endl;
        //~ cout << "ibeam : " << ibeam << ", isample: " << isample << ", imode: " << imode << endl;
        //~ TString name = TString::Format("%s_%s_%s_%s_%s_%s_%s",
          //~ tag, "pdfcs",binning,"rf", util::AsString(b).c_str(), util::AsString(s).c_str(), util::AsString(m).c_str());
        //~ pdf_contrib[imode] = (TH1D*) fin->Get(name.Data());
        //~ if(pdf_contrib[imode]) {
            //~ conv::ReacModeCoarse_t mc = conv::kMappingToCoarseModes[ibeam][isample][imode];
            //~ if(mc == conv::kmcUndefined) continue; 
            //~ cout << "Mode: " << util::AsString(m) << " is mapped to plot type: " << util::AsString(mc) << endl;
            //~ bool found = false;
            //~ for(int imodec = 0; imodec < conv::kNReacModesCoarse; imodec++) {
              //~ if(mc == conv::kReactionModesCoarse[ibeam][isample][imodec]) {
                  //~ found = true;
                  //~ break;
              //~ }
            //~ }           
            //~ if(!found) {
              //~ cout << "WTF! Plot type (coarse reaction mode): " << util::AsString(mc) 
                   //~ << " not in the list of modes considered for"
                   //~ << " beam: " << util::AsString(b) << " / sample: " << util::AsString(s) << endl;
              //~ exit(1);
            //~ }                  
            //~ for(int imodec = 0; imodec < conv::kNReacModesCoarse; imodec++) {
              //~ cout << "imodec = " << imodec << endl;
              //~ if(mc != conv::kReactionModesCoarse[ibeam][isample][imodec]) continue;
              //~ if(pdf_contrib_coarse[imodec] == 0) {
                 //~ pdf_contrib_coarse[imodec] = new TH1D(*pdf_contrib[imode]);
              //~ } else {
                 //~ pdf_contrib_coarse[imodec]->Add(pdf_contrib[imode]);
              //~ }           
            //~ }//imodec
        //~ }//!null
        //~ else {
          //~ cerr << "Null [" << name << "]" << endl;
        //~ }
      //~ }//imode
      //~ // Scan for max in desired Erange
      //~ for(int ebin = 1; ebin <= pdf_contrib[0]->GetNbinsX(); ebin++) {
         //~ if(pdf_contrib[0]->GetBinCenter(ebin) < enu_reco_max ) {
           //~ double sum = 0;
           //~ for(int imode = 0; imode < conv::kNReacModes; imode++) {
              //~ double val = pdf_contrib[imode]->GetBinContent(ebin);
              //~ sum += val;
           //~ }
           //~ max[isample] = TMath::Max(max[isample], sum);           
         //~ }//<emax
      //~ }//ebin
      //~ // Start drawing
      //~ ic++;
      //~ TLegend * leg = new TLegend(0.5,0.3,0.9,0.8);  
      //~ leg->SetFillColor(0);
      //~ for(int imodec = 0; imodec < conv::kNReacModesCoarse; imodec++) {
          //~ conv::ReacModeCoarse_t mc = conv::kReactionModesCoarse[ibeam][isample][imodec];
          //~ if(mc == conv::kmcUndefined) continue;
          //~ pdf_contrib_coarse[imodec]->SetLineWidth(1); 
          //~ pdf_contrib_coarse[imodec]->SetLineColor(conv::kReactionModesCoarseFormatting[ibeam][isample][imodec][0]); 
          //~ pdf_contrib_coarse[imodec]->SetFillColor(conv::kReactionModesCoarseFormatting[ibeam][isample][imodec][1]); 
          //~ pdf_contrib_coarse[imodec]->SetFillStyle(conv::kReactionModesCoarseFormatting[ibeam][isample][imodec][2]); 
          //~ stack->Add(pdf_contrib_coarse[imodec]);
          //~ leg->AddEntry(pdf_contrib_coarse[imodec],Form("%s",util::AsStringTex(mc,true).c_str()), "LF");
      //~ }//imodec
      //~ c_pdf_contrib[ibeam]->cd(ic);
      //~ TH1F * hframe = (TH1F*)c_pdf_contrib[ibeam]->GetPad(ic)->DrawFrame(0,0,enu_reco_max,1.2*max[isample]);
      //~ hframe->Draw();
      //~ TString title_str = TString::Format("%s / %s", util::AsString(b).c_str(), util::AsStringTeX(s,true).c_str());
      //~ TLatex * title = new TLatex(1,1.07*max[isample],title_str.Data());
      //~ title->Draw(); 
      //~ if(util::IsCC(s)) {  
         //~ hframe->GetXaxis()->SetTitle("Reco. E_{#nu} (GeV)");
      //~ } else {
         //~ hframe->GetXaxis()->SetTitle("Visible Energy (GeV)");
      //~ }
      //~ hframe->GetYaxis()->SetTitle("Events /bin");
      //~ stack->Draw("same");
      //~ leg->Draw();
      //~ 
      //~ //
      //~ // Now write out tables
      //~ //  
      //~ double ntot_sample = 0;
      //~ for(int imode = 0; imode < conv::kNReacModes; imode++) {
         //~ conv::ReacMode_t m = conv::kReactionModes[isample][imode];
         //~ if(m == conv::kmUndefined) continue;
            //~ cout << "Taking mode: " << util::AsString(m) << endl;
         //~ ntot_sample += pdf_contrib[imode]->Integral();
      //~ }
      //~ for(int imode = 0; imode < conv::kNReacModes; imode++) {
         //~ conv::ReacMode_t m = conv::kReactionModes[isample][imode];
         //~ if(m == conv::kmUndefined) continue;
         //~ double ntot = pdf_contrib[imode]->Integral();
         //~ double frac = 100*ntot/ntot_sample;
         //~ cout << util::AsStringTeX(m,false) << "\t & " << frac << "\\" << endl;
      //~ }
//~ 
    //~ }//isample
    //~ if (write_image) {
      //~ TString imgname = TString::Format("%s_spectrum_%s_modes.%s",
        //~ out_tag, util::AsString(b).c_str(),image_save_format);
      //~ c_pdf_contrib[ibeam]->Print(imgname.Data());
    //~ }
  //~ }//ibeam
//~ 
//~ }
