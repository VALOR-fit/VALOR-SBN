/*
This is a macro to plot fit parameter pulls and residuals from the fits of an ensemble of toy MC experiments at 
the DUNE near detector. 

You need to generate and fit some toy experiments using run_fit.C. Then run this macro over the output ROOT files.

Originally by Nick Grant 11 July 2014

Major rewrite, Steve Dennis, Feb 2016
*/

void FormatGraph(TGraph *graph, int style, int colour, int size);
void FormatPave(TPaveText * pave);

int resolution_x = 1024;
int resolution_y = 768;

void plot_pulls(
  const char * input_pattern = "/opt/ppd/t2k/users/nick/DUNE/macros/fit/nd/pull_migrad_mcstatfluc/toymc*.root",
  const int nParams = 119,
  const int nParamsPerPage = 40,
  const char * options = "",
  const char * img_format = "png"
)
{
  using namespace valor;
  using namespace valor::conv;
  
  TString ts_options(options);
  
  bool plot_errors                 = ts_options.Contains("showerrors" );
  bool ignore_hesse                = ts_options.Contains("ignorehesse");
  bool save_all_plotted_histograms = ts_options.Contains("saveall"    );
  
  bool batchmode = gROOT->IsBatch();

  TChain *toymcchain = new TChain("valor_dune_nd_ntp");
  toymcchain->Add(input_pattern);
  
  assert(toymcchain->GetEntries());
  
  int nfits = toymcchain->GetEntries();
  int nsigma = 5;
  
  int nbins_pull = valor::util::EstimateOptimalNumberOfBinsForGaussian(nfits,nsigma);
  int nbins_res  = valor::util::EstimateOptimalNumberOfBinsForGaussian(nfits,nsigma);
  
  PhysParamList * true_param_array     = 0; // input true params
  FitParamList *  best_fit_param_array = 0; // best-fit params
  TObjArray *     best_fit_model_array = 0; // an array of various best-fit model predictions for the current toy-MC experiment 
  TObjArray *     data_array           = 0; // an array of all fitted data distributions for the current toy-MC experiment
  //~ int migradmin, migraderr;
  
  double * pull_mean          = new double[nParams];
  double * pull_mean_err      = new double[nParams];
  double * pull_sigma         = new double[nParams];
  double * pull_sigma_err     = new double[nParams];
  double * pull_const         = new double[nParams];
  double * pull_const_err     = new double[nParams];
  double * residual_mean      = new double[nParams];
  double * residual_mean_err  = new double[nParams];
  double * residual_sigma     = new double[nParams];
  double * residual_sigma_err = new double[nParams];
  double * residual_const     = new double[nParams];
  double * residual_const_err = new double[nParams];

  toymcchain->SetBranchAddress("true_params",        &true_param_array);
  toymcchain->SetBranchAddress("best_fit_params",    &best_fit_param_array);
  toymcchain->SetBranchAddress("best_fit_model",     &best_fit_model_array);
  toymcchain->SetBranchAddress("data",               &data_array);
  //~ toymcchain->SetBranchAddress("migradmin",          &migradmin);
  //~ toymcchain->SetBranchAddress("migraderr",          &migraderr);

  TH1D ** hPull                 = new TH1D*     [nParams];
  TH1D ** hResidual             = new TH1D*     [nParams];
  TPaveText ** tPullSummary     = new TPaveText*[nParams];
  TPaveText ** tPull            = new TPaveText*[nParams];
  TPaveText ** tResidualSummary = new TPaveText*[nParams];
  TPaveText ** tResidual        = new TPaveText*[nParams];
  TText ** axislabel            = new TText*    [nParams];
  TText ** histtitle            = new TText*    [nParams];
  
  TH1 ** fitPull                 = new TH1*[nParams];
  TH1 ** fitResidual             = new TH1*[nParams];
  
  TLine * line_at_y_is_1 = new TLine(0,1,nParamsPerPage,1);
  TLine * line_at_y_is_0 = new TLine(0,0,nParamsPerPage,0);

  for(int iparam=0; iparam<nParams; iparam++)
  {
    hPull    [iparam] = new TH1D(Form("hPull%02i"    , iparam), "", nbins_pull, -nsigma, +nsigma);
    hResidual[iparam] = new TH1D(Form("hResidual%02i", iparam), "", nbins_res , -nsigma, +nsigma);
  }

  for(Long_t i = 0; i < toymcchain->GetEntries(); i++) 
  {
    toymcchain->GetEntry(i);
    
    //~ if(best_fit_param_array->GetStatusCode("migradmin") == 0 && best_fit_param_array->GetStatusCode("migraderr")==0) {
    if (true){
      for(int ip = kNuis000; ip < kNuis000+nParams; ip++)
      {
        PhysParamId_t p = (PhysParamId_t)ip;
        int iparam = util::NDArrIdx::Instance()->NDFitParamIdx(p);
        double fitted_errors = best_fit_param_array->MigradError(p);
        if (!ignore_hesse && best_fit_param_array->HesseErrorsSet()) {
          fitted_errors = best_fit_param_array->HesseError(p);
        }
        
        //~ double pull_numerator = best_fit_param_array->BestFitValue(p) - 1;
        double pull_numerator = best_fit_param_array->BestFitValue(p) - true_param_array->Value(p);
        double pull_denominator = fitted_errors;
        //~ double pull_denominator = sqrt(0.2*0.2 - best_fit_param_array->MigradError(p)*best_fit_param_array->MigradError(p));
        hPull[iparam]->Fill(pull_numerator/pull_denominator);
        double residual = best_fit_param_array->BestFitValue(p) - true_param_array->Value(p);
        hResidual[iparam]->Fill(residual);
      }
    }
  }
    
  TF1 *gauss = new TF1("mygaus", "gaus(0)", -nsigma, +nsigma);
  for(int iparam=0; iparam<nParams; iparam++)
  {
    hPull[iparam]->Fit(gauss, "RM0");
    pull_const    [iparam] = gauss->GetParameter(0);
    pull_mean     [iparam] = gauss->GetParameter(1);
    pull_sigma    [iparam] = gauss->GetParameter(2);
    pull_const_err[iparam] = gauss->GetParError(0);
    pull_mean_err [iparam] = gauss->GetParError(1);
    pull_sigma_err[iparam] = gauss->GetParError(2);
    fitPull       [iparam] = valor::util::MakeFittedHistogramShowingFittedValues(hPull[iparam],gauss,10000);
    
    hResidual[iparam]->Fit(gauss, "RM0");
    residual_const    [iparam] = gauss->GetParameter(0);
    residual_mean     [iparam] = gauss->GetParameter(1);
    residual_sigma    [iparam] = gauss->GetParameter(2);
    residual_const_err[iparam] = gauss->GetParError(0);
    residual_mean_err [iparam] = gauss->GetParError(1);
    residual_sigma_err[iparam] = gauss->GetParError(2);
    fitResidual       [iparam] = valor::util::MakeFittedHistogramShowingFittedValues(hPull[iparam],gauss,10000);
    
    //~ pull_const    [iparam] = fitPull    [iparam]->Integral();
    //~ residual_const[iparam] = fitResidual[iparam]->Integral();
    
    fitPull       [iparam]->SetLineColor(kRed);
    fitResidual   [iparam]->SetLineColor(kRed);
  }
  
  // Calculate how many pages worth of plots we'll need and how to divide up the canvas
  int npages = TMath::CeilNint((double)nParams/nParamsPerPage);
  
  int n_plots_horizontal = 1;
  int n_plots_vertical   = 1;
  
  while (n_plots_horizontal * n_plots_vertical < nParamsPerPage) {
    n_plots_horizontal++;
    if (n_plots_horizontal * n_plots_vertical > nParamsPerPage) {break;}
    n_plots_vertical++;
  }
  
  int iparam = 0;
  
  for (int ipage = 0 ; ipage < npages ; ipage++) {
    
    double * param_x              = new double[nParamsPerPage];
    double * param_x_err          = new double[nParamsPerPage];
    double * graph_pull_mean      = new double[nParamsPerPage];
    double * graph_pull_sigma     = new double[nParamsPerPage];
    double * graph_pull_mean_err  = new double[nParamsPerPage];
    double * graph_pull_sigma_err = new double[nParamsPerPage];
    
    TH1D * label_hist    = new TH1D("label_hist","label_hist",nParamsPerPage,0,nParamsPerPage);
    
    // Individual pull histograms
    TString canvname = TString::Format("Pull%i",ipage);
    TString imgname = canvname+"."+img_format;
    
    TCanvas *PullCanv = new TCanvas(canvname.Data(), canvname.Data(), resolution_x, resolution_y);
    PullCanv->Divide(n_plots_horizontal, n_plots_vertical);
    for(int ihist=0; ihist<nParamsPerPage; ihist++)
    {
      iparam = ihist + ipage*nParamsPerPage;
      if (iparam >= nParams) {continue;}
      PullCanv->cd(ihist+1);
      gPad->SetTopMargin(0.15);
      PhysParamId_t p = kNDFitParam[iparam];
      string label = util::AsString(p);
      tPull[iparam] = new TPaveText(0.05,0.85,1.0,0.95,"NDC");
      histtitle[iparam] = tPull[iparam]->AddText(label.c_str());
      //SetTextAlign(11) to left justify, 21 to centre and 31 to right justify 
      histtitle[iparam]->SetTextAlign(21);
      histtitle[iparam]->SetTextSize(0.12);
      tPull[iparam]->SetFillColor(0);
      tPull[iparam]->SetBorderSize(0);
      
      // Draw
      hPull  [iparam]->Draw();
      fitPull[iparam]->Draw("LSAME");
      tPull  [iparam]->Draw();
      
      // Fill the graph arrays
      param_x             [ihist] = label_hist->GetXaxis()->GetBinCenter(ihist+1);
      param_x_err         [ihist] = 0;
      graph_pull_mean     [ihist] = pull_mean     [iparam];
      graph_pull_sigma    [ihist] = pull_sigma    [iparam];
      graph_pull_mean_err [ihist] = pull_mean_err [iparam];
      graph_pull_sigma_err[ihist] = pull_sigma_err[iparam];
      
      label_hist->GetXaxis()->SetBinLabel(ihist+1,label.c_str());
      
      if (save_all_plotted_histograms) {
        //~ if (!batchmode) {gROOT->SetBatch(1);} // We'll want to be in batch mode for making all these histograms.
        TCanvas c("pull_canv_tmp","pull_canv_tmp");
        c.cd();
        TPaveText * stats = new TPaveText(0.65,0.7,0.85,0.9,"NDC");
        TString  mean_label = TString::Format("Mean  = %.3lf",pull_mean [iparam]);
        TString sigma_label = TString::Format("Sigma = %.3lf",pull_sigma[iparam]);
        stats->SetTextSize(0.05);
        stats->AddText( mean_label.Data());
        stats->AddText(sigma_label.Data());
        FormatPave(stats);
        hPull[iparam]->Draw();
        fitPull[iparam]->Draw("LSAME");
        stats->Draw();
        c.SaveAs(TString::Format("PullFitted_%s.%s",label.c_str(),img_format));
        if (batchmode) {gROOT->SetBatch(0);}
      }
    }
      
    PullCanv->SaveAs(imgname.Data());
    
    // Pull summary.
    TString canvname_summary = TString::Format("PullSummary%i",ipage);
    TString imgname_summary  = canvname_summary+"."+img_format;
    
    TGraph * g_pull_mean ; 
    TGraph * g_pull_sigma;
    
    if (plot_errors) {
      g_pull_mean  = new TGraphErrors(nParamsPerPage, param_x, graph_pull_mean , param_x_err, graph_pull_mean_err );
      g_pull_sigma = new TGraphErrors(nParamsPerPage, param_x, graph_pull_sigma, param_x_err, graph_pull_sigma_err);
    }
    else {
      g_pull_mean  = new TGraph(nParamsPerPage, param_x, graph_pull_mean );
      g_pull_sigma = new TGraph(nParamsPerPage, param_x, graph_pull_sigma);
    }
    
    TCanvas *PullSummary = new TCanvas(canvname_summary.Data(), canvname_summary.Data(), resolution_x, resolution_y);
    PullSummary->SetGridx(1);
    PullSummary->SetBottomMargin(0.35);
    PullSummary->SetLeftMargin(0.08);
    PullSummary->SetRightMargin(0.12);
    PullSummary->SetTopMargin(0.03);
    
    // Draw the axis
    label_hist->GetXaxis()->SetNdivisions(000);
    label_hist->GetYaxis()->SetRangeUser(-1.0, 3.0);
    label_hist->GetXaxis()->LabelsOption("v"); // Vertical labels
    label_hist->SetTitle("");
    label_hist->Draw("AXIS");
    
    // Draw the lines at the expected values
    line_at_y_is_1->Draw();
    line_at_y_is_0->Draw();
    
    FormatGraph(g_pull_mean , kFullCircle    , kRed , 1.);
    FormatGraph(g_pull_sigma, kFullTriangleUp, kBlue, 1.);
    g_pull_mean ->Draw("P");
    g_pull_sigma->Draw("P");

    //~ TLegend *lpull = new TLegend(0.71, 0.74, 0.85, 0.88);
    //~ lpull->AddEntry(g_pull_mean, "Mean", "P");
    //~ lpull->AddEntry(g_pull_sigma, "Sigma", "P");
    //~ lpull->SetFillColor(0);
    //~ lpull->SetBorderSize(0);
    //~ lpull->Draw();
    
    TLatex * mean_label  = new TLatex(nParamsPerPage+0.3, 0., "Mean" );
    TLatex * sigma_label = new TLatex(nParamsPerPage+0.3, 1., "Sigma");
    
    mean_label ->SetTextColor(g_pull_mean ->GetMarkerColor());
    sigma_label->SetTextColor(g_pull_sigma->GetMarkerColor());
    
    mean_label ->SetTextSize(0.05);
    sigma_label->SetTextSize(0.05);
    
    mean_label ->Draw();
    sigma_label->Draw();
    
    PullSummary->SaveAs(imgname_summary);
  }
//~ 
  //~ for(int param=0; param<nParams; param++)
  //~ {
    //~ PhysParamId_t p = kNDFitParam[param];
    //~ //const char * label = util::AsStringTeX(p,true).c_str();
    //~ const char * label = util::AsString(p).c_str();
    //~ x_low = param + 0.5;
    //~ x_high = x_low + 1.0;
    //~ tPullSummary[param] = new TPaveText(x_low,-1.45,x_high,-1.05);
    //~ axislabel[param] = tPullSummary[param]->AddText(label);
    //~ axislabel[param]->SetTextAngle(90);
    //~ //SetTextAlign(11) to left justify, 21 to centre and 31 to right justify
    //~ axislabel[param]->SetTextAlign(31);
    //~ axislabel[param]->SetTextSize(0.03);
    //~ tPullSummary[param]->SetFillColor(0);
    //~ tPullSummary[param]->SetBorderSize(0);
    //~ tPullSummary[param]->Draw();
  //~ }
//~ 
  //~ PullSummary->SaveAs("PullSummary.png");
  //~ 
  //~ TGraph *g_residual_mean = new TGraph(nParams, param_x, residual_mean);
  //~ TGraph *g_residual_sigma = new TGraph(nParams, param_x, residual_sigma);
//~ 
  //~ TCanvas *ResidualSummary = new TCanvas("ResidualSummary", "ResidualSummary", resolution_x, resolution_y);
  //~ ResidualSummary->Divide(1);
  //~ ResidualSummary->cd(1);
  //~ gPad->SetBottomMargin(0.35);
  //~ g_pull_mean->GetXaxis()->SetNdivisions(000);
  //~ g_residual_mean->GetYaxis()->SetRangeUser(-1.0, 2.0);
  //~ FormatGraph(g_residual_mean, 20, 2, 1);
  //~ g_residual_mean->Draw("AP");
  //~ FormatGraph(g_residual_sigma, 20, 4, 1);
  //~ g_residual_sigma->Draw("P");
//~ 
  //~ TLegend *lresidual = new TLegend(0.71, 0.74, 0.85, 0.88);
  //~ lresidual->AddEntry(g_residual_mean, "Mean", "P");
  //~ lresidual->AddEntry(g_residual_sigma, "Sigma", "P");
  //~ lresidual->SetBorderSize(0);
  //~ lresidual->SetFillColor(0);
  //~ lresidual->Draw();
//~ 
  //~ for(int param=0; param<nParams; param++)
    //~ {
    //~ PhysParamId_t p = kNDFitParam[param];
    //~ //const char * label = util::AsStringTeX(p,true).c_str();
    //~ const char * label = util::AsString(p).c_str();
    //~ x_low = param + 0.5;
    //~ x_high = x_low + 1.0;
    //~ tResidualSummary[param] = new TPaveText(x_low,-1.45,x_high,-1.05);
    //~ axislabel[param] = tResidualSummary[param]->AddText(label);
    //~ axislabel[param]->SetTextAngle(90);
    //~ //SetTextAlign(11) to left justify, 21 to centre and 31 to right justify
    //~ axislabel[param]->SetTextAlign(31);
    //~ axislabel[param]->SetTextSize(0.03);
    //~ tResidualSummary[param]->SetFillColor(0);
    //~ tResidualSummary[param]->SetBorderSize(0);
    //~ tResidualSummary[param]->Draw();
    //~ }
//~ 
  //~ ResidualSummary->SaveAs("ResidualSummary.png");
  

}//end of plot_pulls()


void FormatGraph(TGraph *graph, int style, int colour, int size)
{
  graph->SetTitle("");
  graph->SetMarkerStyle(style);
  graph->SetMarkerColor(colour);
  graph->SetMarkerSize(size);
  graph->SetLineColor(colour);
}

void FormatPave(TPaveText * pave)
{
  pave->SetTextFont(22)   ;
  pave->SetShadowColor(0) ;
  pave->SetFillColor(0)   ;
  pave->SetFillStyle(0)   ;
  pave->SetLineColor(0)   ;
}
