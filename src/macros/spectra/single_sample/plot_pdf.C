//
// ------------------------------------------------------------------------------------------------
// Simple program to plot DUNE/ND PDFs and MC templates written out by write_nd_pdf.C
//
// Costas Andreopoulos
// ------------------------------------------------------------------------------------------------
//

#ifndef __CINT__
#include "ValorInc.h"
#include "DuneInc.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLatex.h"
#include "TLegend.h"
#endif

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
  
#ifndef __CINT__
  valor::Env * env = valor::Env::Instance();
  env->AutoSet("dune");
  valor::util::PopulateNameRegistry();
#endif
  
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
  FitModelABC * modelabc = elems.FitModel();
  CompoundFitModel & model = *dynamic_cast<CompoundFitModel*>(modelabc);
  
  // A vector storing the list of submodels to plot on each canvas
  // Outer vector is per canvas, inner vector is plots on said canvas
  vector<vector<int> > canvas_content;
  canvas_content.push_back(vector<int>());
  
  conv::Detector_t last_det  = conv::kdUndefined;
  conv::BeamConf_t last_beam = conv::kbUndefined;
  
  // First loop over our selections to work out how many canvases we're drawing
  // We'll do a new canvas every time the detector changes, the beam current changes or we go above max_plots_per_canv
  for (unsigned int isubmodel = 0 ; isubmodel < model.GetNSubModels() ; isubmodel++) {
    FitModelABC * submodelabc = model.GetSubModel(isubmodel);
    GenericSingleSampleFitModel & submodel = *dynamic_cast<GenericSingleSampleFitModel*>(submodelabc);
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
  for (unsigned int icanvas = 0 ; icanvas < canvas_content.size() ; icanvas++) {
    // Calculate number of vertical and horizontal plots we need
    int plots_on_this_canv = canvas_content[icanvas].size();
    int nrows = 1;
    int ncols = 1;
    while (nrows * ncols < plots_on_this_canv) {
      if (nrows < ncols) {nrows++;}
      else {ncols++;}
    }
    
    // Get the first submodel so we can get beam/detector info
    unsigned int isubmodel = canvas_content[icanvas][0];
    FitModelABC * submodelabc = model.GetSubModel(isubmodel);
    GenericSingleSampleFitModel & submodel = *dynamic_cast<GenericSingleSampleFitModel*>(submodelabc);
    conv::Detector_t d = submodel.GetDetector();
    conv::BeamConf_t b = submodel.GetBeam();
    conv::Sample_t   s = submodel.GetSample();
    
    // make a canvas for the 2d plots
    TString c_name_pdf_tot  = TString::Format("c_pdf_tot_%s_%s_%u",
      util::AsString(d).c_str(),util::AsString(b).c_str(),icanvas);
    TString c_title_pdf_tot = TString::Format("Total PDF %s %s %u",
      util::AsString(d).c_str(),util::AsString(b).c_str(),icanvas);
    TCanvas * c_pdf_tot = new TCanvas(c_name_pdf_tot.Data(),c_title_pdf_tot.Data(),20,20,canv_size_x,canv_size_y);
    c_pdf_tot->Divide(nrows,ncols);
    all_canvases.push_back(c_pdf_tot);
    
    // Make a canvas for the 1D y-sliced plots
    TString c_name_pdf_slice  = TString::Format("c_pdf_slice_%s_%s_%u",
      util::AsString(d).c_str(),util::AsString(b).c_str(),icanvas);
    TString c_title_pdf_slice = TString::Format("PDF (by y_reco) %s %s %u",
      util::AsString(d).c_str(),util::AsString(b).c_str(),icanvas);
    TCanvas * c_pdf_slice = new TCanvas(c_name_pdf_slice.Data(),c_title_pdf_slice.Data(),20,20,canv_size_x,canv_size_y);
    c_pdf_slice->Divide(nrows,ncols);
    all_canvases.push_back(c_pdf_slice);
    
    // Make a canvas for the mode plots
    TString c_name_contrib  = TString::Format("c_pdf_contrib_%s_%s_%u",
      util::AsString(d).c_str(),util::AsString(b).c_str(),icanvas);
    TString c_title_contrib = TString::Format("PDF (by mode) %s %s %u",
      util::AsString(d).c_str(),util::AsString(b).c_str(),icanvas);
    TCanvas * c_pdf_contrib = new TCanvas(c_name_contrib.Data(),c_title_contrib.Data(),20,20,canv_size_x,canv_size_y);
    c_pdf_contrib->Divide(nrows,ncols);
    all_canvases.push_back(c_pdf_contrib);
    
    
    // Actually read the PDFs
    for (unsigned int iplot = 0 ; iplot < canvas_content[icanvas].size() ; iplot++) {
      isubmodel = canvas_content[icanvas][iplot];
      submodelabc = model.GetSubModel(isubmodel);
      submodel = *dynamic_cast<GenericSingleSampleFitModel*>(submodelabc);
      d = submodel.GetDetector();
      b = submodel.GetBeam();
      s = submodel.GetSample();
      
      int isample = util::ArrIdx::Instance()->SampleIdx(b, s);
      int ibeam   = util::ArrIdx::Instance()->BeamConfIdx(b);
      
      { // 2D PDF
        TString pdf_tot_name = TString::Format("%s_%s_%s_%s_%s_%s", 
           tag, "pdft",binning,"rf", util::AsString(b).c_str(), util::AsString(s).c_str());
           
        TObject * tmp_obj = fin->Get(pdf_tot_name.Data());
        assert(tmp_obj);
        TH2D * pdf_tot = new TH2D(*((TH2D*)tmp_obj));
        all_hists.push_back(pdf_tot);
        
        // Draw the 2D plots
        TVirtualPad * this_pad = c_pdf_tot->cd(iplot+1); // Pad for this plot
        TH1F * pdf_frame = (TH1F*)this_pad->DrawFrame(0,0,enu_reco_max,1);
        pdf_frame->Draw();
        pdf_tot->Draw("colzsame");
      }
      
      
      { // Sliced in Y
        THStack * slice_stack = new THStack("stack","spectrum contributions");
        const int n_y_reco_bins_sb = util::NumYrecoBinsSb(s);
        const double * y_reco_bin_edges_sb = util::YrecoBinEdgesSb(s);
        vector<TH1*> pdf_slice;
        for(int iy = 0; iy < n_y_reco_bins_sb; iy++) {
          TString slice_name = TString::Format("%s_%s_%s_%s_%s_%s_y%d",
            tag, "pdfts",binning,"rf", util::AsString(b).c_str(), util::AsString(s).c_str(), iy);
            TObject * tmp_obj = fin->Get( slice_name );
            pdf_slice.push_back((TH1D*)tmp_obj);
        }//iy
        
        double max_n = 0.;
        // Scan for max in desired Erange
        for(int ebin = 1; ebin <= pdf_slice[0]->GetNbinsX(); ebin++) {
           if(pdf_slice[0]->GetBinCenter(ebin) < enu_reco_max ) {
             double sum = 0;
             for(int iy = 0; iy < n_y_reco_bins_sb; iy++) {
                double val = pdf_slice[iy]->GetBinContent(ebin);
                sum += val;
             }
             max_n = TMath::Max(max_n, sum);           
            }//<emax
        }//ebin
        
        // Make slice legend
        TLegend * slice_legend = new TLegend(0.50,0.40,0.88,0.80);
        slice_legend->SetFillColor(0);
        for(int iy = 0; iy < n_y_reco_bins_sb; iy++) {
          pdf_slice[iy]->SetFillColor(pdf_slice_color[iy]); 
          pdf_slice[iy]->SetLineWidth(1); 
          slice_stack->Add(pdf_slice[iy]);
          slice_legend->AddEntry(pdf_slice[iy],Form("y = [%.2f,%.2f]", y_reco_bin_edges_sb[iy], y_reco_bin_edges_sb[iy+1]),"LF");
        }
        
        // Draw the slice plots
        TVirtualPad * this_pad = c_pdf_slice->cd(iplot+1); // Pad for this plot
        TH1F * slice_frame = (TH1F*)this_pad->DrawFrame(0,0,enu_reco_max,1.2*max_n);
        slice_frame->Draw();
        TString slice_title_str = TString::Format("%s / %s", util::AsString(b).c_str(), util::AsStringTeX(s,true).c_str());
        TLatex * slice_title = new TLatex(1,1.07*max_n,slice_title_str.Data());
        slice_title->Draw(); 
        if(util::IsCC(s)) {
          slice_frame->GetXaxis()->SetTitle("Reco. E_{#nu} (GeV)");
        } else {
          slice_frame->GetXaxis()->SetTitle("Visible Energy (GeV)");
        }
        slice_frame->GetYaxis()->SetTitle("Events /bin");
        slice_stack->Draw("same");
        slice_legend->Draw();
      } // end slice in y
      
      
      { // Divided by mode
        THStack * contrib_stack = new THStack("stack","spectrum contributions");
        TH1D * pdf_contrib        [conv::kNReacModes]       = { 0 };
        TH1D * pdf_contrib_coarse [conv::kNReacModesCoarse] = { 0 };
        for(int imode = 0; imode < conv::kNReacModes; imode++) {
          conv::ReacMode_t m = conv::kReactionModes[isample][imode];
          if(m == conv::kmUndefined) continue;
          cout << "Taking mode: " << util::AsString(m) << endl;
          cout << "ibeam : " << ibeam << ", isample: " << isample << ", imode: " << imode << endl;
          TString contrib_name = TString::Format("%s_%s_%s_%s_%s_%s_%s",
            tag, "pdfcs",binning,"rf", util::AsString(b).c_str(), util::AsString(s).c_str(), util::AsString(m).c_str());
          TObject * tmp_obj = fin->Get(contrib_name.Data());
          pdf_contrib[imode] = (TH1D*) tmp_obj;
          if(pdf_contrib[imode]) {
            conv::ReacModeCoarse_t mc = conv::kmcUndefined;
            bool found = false;
            for (int imcp = 0 ; imcp < conv::kMaxCoarseReacOptions ; imcp++) {
              conv::ReacModeCoarse_t mc = conv::kCoarseReacPriority[m][imcp];;
              if(mc == conv::kmcUndefined) continue; 
              for(int imodec = 0; imodec < conv::kNReacModesCoarse; imodec++) {
                if(mc == conv::kReactionModesCoarse[ibeam][isample][imodec]) {
                    found = true;
                    cout << "Mode: " << util::AsString(m) << " is mapped to plot type: " << util::AsString(mc) << endl;
                    break;
                }
              }
              if (found) break;
            }
            if(!found) {
              cout << "WTF! Did not find coarse reaction mode for mode: " << util::AsString(m) 
                   << " beam: " << util::AsString(b) << " / sample: " << util::AsString(s) << endl;
              exit(1);
            }                  
            for(int imodec = 0; imodec < conv::kNReacModesCoarse; imodec++) {
              if(mc != conv::kReactionModesCoarse[ibeam][isample][imodec]) continue;
              if(pdf_contrib_coarse[imodec] == 0) {
                 pdf_contrib_coarse[imodec] = new TH1D(*pdf_contrib[imode]);
              } else {
                 pdf_contrib_coarse[imodec]->Add(pdf_contrib[imode]);
              }           
            }//imodec
          }//!null
          else {
            cerr << "Null [" << contrib_name << "]" << endl;
          }
        }//imode
        
        // Scan for max in desired Erange
        double max_n = 0.;
        for(int ebin = 1; ebin <= pdf_contrib[0]->GetNbinsX(); ebin++) {
           if(pdf_contrib[0]->GetBinCenter(ebin) < enu_reco_max ) {
             double sum = 0;
             for(int imode = 0; imode < conv::kNReacModes; imode++) {
                if (pdf_contrib[imode]) {
                  double val = pdf_contrib[imode]->GetBinContent(ebin);
                  sum += val;
                }
             }
             max_n = TMath::Max(max_n, sum);           
           }//<emax
        }//ebin
        
        // Start drawing
        TLegend * contrib_legend = new TLegend(0.5,0.3,0.9,0.8);  
        contrib_legend->SetFillColor(0);
        for(int imodec = 0; imodec < conv::kNReacModesCoarse; imodec++) {
            conv::ReacModeCoarse_t mc = conv::kReactionModesCoarse[ibeam][isample][imodec];
            //~ cout<<"Drawing: "<<util::AsString(b)<<" "<<util::AsString(s)<<"\t"<<imodec<<"\t"<<util::AsString(mc)<<"\t"<<pdf_contrib_coarse[imodec]<<std::endl;
            if(mc == conv::kmcUndefined) continue;
            pdf_contrib_coarse[imodec]->SetLineWidth(1); 
            pdf_contrib_coarse[imodec]->SetLineColor(conv::kReactionModesCoarseFormatting[ibeam][isample][imodec][0]); 
            pdf_contrib_coarse[imodec]->SetFillColor(conv::kReactionModesCoarseFormatting[ibeam][isample][imodec][1]); 
            pdf_contrib_coarse[imodec]->SetFillStyle(conv::kReactionModesCoarseFormatting[ibeam][isample][imodec][2]); 
            contrib_stack->Add(pdf_contrib_coarse[imodec]);
            contrib_legend->AddEntry(pdf_contrib_coarse[imodec],Form("%s",util::AsStringTex(mc,true).c_str()), "LF");
        }//imodec
        
        TVirtualPad * this_pad = c_pdf_contrib->cd(iplot+1); // Pad for this plot
        TH1F * contrib_frame = (TH1F*)this_pad->DrawFrame(0,0,enu_reco_max,1.2*max_n);
        contrib_frame->Draw();
        TString contrib_title_str = TString::Format("%s / %s", util::AsString(b).c_str(), util::AsStringTeX(s,true).c_str());
        TLatex * contrib_title = new TLatex(1,1.07*max_n,contrib_title_str.Data());
        contrib_title->Draw(); 
        if(util::IsCC(s)) {  
           contrib_frame->GetXaxis()->SetTitle("Reco. E_{#nu} (GeV)");
        } else {
           contrib_frame->GetXaxis()->SetTitle("Visible Energy (GeV)");
        }
        contrib_frame->GetYaxis()->SetTitle("Events /bin");
        contrib_stack->Draw("same");
        contrib_legend->Draw();
      }
      
    
    } //iplot
    
    // Update the canvases
    c_pdf_tot    ->Update();
    c_pdf_slice  ->Update();
    c_pdf_contrib->Update();
    
    // And write to files if needed
    if (write_image) {
      TString pdf_tot_filename = TString::Format("%s_spectrum_%s_%s_%u_2D.%s",
          out_tag, util::AsString(d).c_str(), util::AsString(b).c_str(),icanvas,image_save_format);
      c_pdf_tot->SaveAs(pdf_tot_filename.Data());
      
      TString slice_filename = TString::Format("%s_spectrum_%s_%s_%u_y.%s",
          out_tag, util::AsString(d).c_str(), util::AsString(b).c_str(),icanvas,image_save_format);
      c_pdf_slice->Print(slice_filename.Data());
      
      TString contrib_filename = TString::Format("%s_spectrum_%s_%s_%u_modes.%s",
        out_tag, util::AsString(d).c_str(), util::AsString(b).c_str(),icanvas, image_save_format);
      c_pdf_contrib->Print(contrib_filename.Data());
    } //write_image
      
  } // icanvas
  return;
}

#ifndef __CINT__
int main() {
  plot_pdf("fit/dunend_ndtf_lartpc_3passthrough_46selection_toymc_fit.xml","lar_pdfs.root");
  return 0;
}
#endif
