//
// ------------------------------------------------------------------------------------------------
// The simple macro puts all plots produced by fit_param_scan_all.C into a single ps file
//
// Costas Andreopoulos
// ------------------------------------------------------------------------------------------------
//
	
void fit_param_scan_all_plot(const char * filename)
{
  using namespace std;
  using namespace valor;
  using namespace valor::conv;

  int nrows = 2;
  int ncols = 2;
  int nplots_page = nrows*ncols;

  TFile f(filename, "read");

  TCanvas * c = new TCanvas("c");
  TPostScript *ps = new TPostScript("file.ps",112);

  c->Divide(nrows,ncols);

  int ic = 100;
  for(int ip = 0; ip < kNNDFitParams; ip++) {
     PhysParamId_t p = kNDFitParam[ip];
     if(p == kPhypUndefined) continue;

     ic++;
     if(ic > nplots_page) { 
         c->Update();
         ps->NewPage();
         ic = 1; 
     }
     c->cd(ic);

     const char * hndc_name   = Form("nd_constraint_%s", util::AsString(p).c_str());
     const char * hprior_name = Form("prior_%s",         util::AsString(p).c_str());
 
     TH1D * hndc   = (TH1D*) f.Get(hndc_name);
     TH1D * hprior = (TH1D*) f.Get(hprior_name);

     hndc->GetXaxis()->SetTitle(util::AsStringTeX(p,true).c_str());
     hndc->GetYaxis()->SetTitle("-#Delta(lnL)");
     hndc->SetMarkerSize(1);
     hndc->SetMarkerStyle(20);
     hndc->Draw("LP");
     hprior->SetLineColor(kRed);
     hprior->Draw("LSAME");

     int pidx = util::NDArrIdx::Instance()->NDFitParamIdx(p);
     double sig = 100*kNDFitParamAPrioriFracError[pidx];


     TLegend * leg = new TLegend(0.5,0.6,0.8,0.9);
     leg->SetFillColor(0);
     leg->SetBorderSize(0);
     leg->AddEntry(hndc,   "DUNE ND constraint",     "LP");
     leg->AddEntry(hprior, Form("Prior %.1f%%",sig), "L");
     leg->Draw();
  }
 
  ps->Close();
}
