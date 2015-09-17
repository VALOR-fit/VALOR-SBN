/*
This is a macro to plot fit parameter pulls and residuals from the fits of an ensemble of toy MC experiments at 
the LBNE near detector. 

You need to generate and fit some toy experiments using run_fit.C. Then run this macro over the output ROOT files.

An extra plot is drawn of the last fit with a default canvas. This is because ROOT draws fitted histograms by default. 
It is possible to suppress this extra plot (which is not needed) by adding the option "0" to the line

hPull[param]->Fit("gauss", "R");

But this option also suppresses the appearance of the fitted Gaussians on the pull plots (which are needed). 
There doesn't seem to be a way of suppressing the extra plot without also suppressing all the fitted Gaussians.

Nick Grant 11 July 2014
*/

void FormatGraph(TGraph *graph, int style, int colour, int size);

void plot_pulls(
const int nParams = 42
)
{
  using namespace valor;
  using namespace valor::conv;

  TChain *toymcchain = new TChain("fitnt");
  toymcchain->Add("/opt/ppd/t2k/users/nick/LBNX/macros/fit/nd/pull_migrad_mcstatfluc/toymc*.root");

  PhysParamList * true_param_array     = 0; // input true params
  FitParamList *  best_fit_param_array = 0; // best-fit params
  TObjArray *     best_fit_model_array = 0; // an array of various best-fit model predictions for the current toy-MC experiment 
  TObjArray *     data_array           = 0; // an array of all fitted data distributions for the current toy-MC experiment
  int migradmin, migraderr, j;
  double pull, residual;
  double pull_mean[nParams];
  double pull_sigma[nParams];
  double residual_mean[nParams];
  double residual_sigma[nParams];
  double param_x[nParams];
  for(int param=0; param<nParams; param++)
    param_x[param] = (double)(param+1);

  fitnt->SetBranchAddress("true_params",        &true_param_array);
  fitnt->SetBranchAddress("best_fit_params",    &best_fit_param_array);
  fitnt->SetBranchAddress("best_fit_model",     &best_fit_model_array);
  fitnt->SetBranchAddress("data",               &data_array);
  fitnt->SetBranchAddress("migradmin",          &migradmin);
  fitnt->SetBranchAddress("migraderr",          &migraderr);

  TH1D *hPull[nParams] = {0};
  TH1D *hResidual[nParams] = {0};
  TPaveText *tPullSummary[nParams] = {0};
  TPaveText *tPull[nParams] = {0};
  TPaveText *tResidualSummary[nParams] = {0};
  TPaveText *tResidual[nParams] = {0};
  TText *axislabel[nParams] = {0};
  TText *histtitle[nParams] = {0};

  for(int hist=0; hist<nParams; hist++)
    {
    hPull[hist] = new TH1D(Form("hPull%02i", hist), "", 50, -5.0, 5.0);
    hResidual[hist] = new TH1D(Form("hResidual%02i", hist), "", 250, -2.5, 2.5);
    } 

  double x_low, x_high;

  for(Long_t i; i < fitnt->GetEntries(); i++) 
    {
    fitnt->GetEntry(i);

    if(migradmin == 0 && migraderr == 3)
      {
      j = -1;
      for(PhysParamId_t p = kNuis000; p<kNuis000+nParams; p++)
        {
        j++;
	pull = (best_fit_param_array->BestFitValue(p) - 1.0)
	  / sqrt(kNDFitParamAPrioriFracError[j]*kNDFitParamAPrioriFracError[j] - best_fit_param_array->MigradError(p)*best_fit_param_array->MigradError(p));
        hPull[j]->Fill(pull);
        residual = best_fit_param_array->BestFitValue(p) - true_param_array->Value(p);
        hResidual[j]->Fill(residual);
        }
      }
    }

  TF1 *gauss = new TF1("gauss", "gaus", -4.0, 4.0);
  for(int param=0; param<nParams; param++)
    {
    hPull[param]->Fit("gauss", "R");
    pull_mean[param] = gauss->GetParameter(1);
    pull_sigma[param] = gauss->GetParameter(2);
    hResidual[param]->Fit("gauss", "R");
    residual_mean[param] = gauss->GetParameter(1);
    residual_sigma[param] = gauss->GetParameter(2);
    }
  
  TCanvas *Pull1 = new TCanvas("Pull1", "Pull1", 800, 600);
  Pull1->Divide(5, 4);
  for(int hist=0; hist<20; hist++)
    {
    Pull1->cd(hist+1);
    gPad->SetTopMargin(0.15);
    PhysParamId_t p = kNDFitParam[hist];
    const char * label = util::AsString(p).c_str();
    hPull[hist]->Draw();
    tPull[hist] = new TPaveText(0.05,0.85,1.0,0.95,"NDC");
    histtitle[hist] = tPull[hist]->AddText(label);
    //SetTextAlign(11) to left justify, 21 to centre and 31 to right justify 
    histtitle[hist]->SetTextAlign(21);
    histtitle[hist]->SetTextSize(0.12);
    tPull[hist]->SetFillColor(0);
    tPull[hist]->SetBorderSize(0);
    tPull[hist]->Draw();
    }

  Pull1->SaveAs("Pull1.png");

  TCanvas *Pull2 = new TCanvas("Pull2", "Pull2", 800, 600);
  Pull2->Divide(5, 4);
  for(int hist=0; hist<20; hist++)
    {
    Pull2->cd(hist+1);
    gPad->SetTopMargin(0.15);
    PhysParamId_t p = kNDFitParam[hist+20];
    const char * label = util::AsString(p).c_str();
    hPull[hist+20]->Draw();
    tPull[hist+20] = new TPaveText(0.05,0.85,1.0,0.95,"NDC");
    histtitle[hist+20] = tPull[hist+20]->AddText(label);
    //SetTextAlign(11) to left justify, 21 to centre and 31 to right justify
    histtitle[hist+20]->SetTextAlign(21);
    histtitle[hist+20]->SetTextSize(0.12);
    tPull[hist+20]->SetFillColor(0);
    tPull[hist+20]->SetBorderSize(0);
    tPull[hist+20]->Draw();
    }

  Pull2->SaveAs("Pull2.png");
    
  TCanvas *Residual1 = new TCanvas("Residual1", "Residual1", 800, 600);
  Residual1->Divide(5, 4);
  for(int hist=0; hist<20; hist++)
    {
    Residual1->cd(hist+1);
    gPad->SetTopMargin(0.15);
    PhysParamId_t p = kNDFitParam[hist];
    const char * label = util::AsString(p).c_str();
    hResidual[hist]->Draw();
    tResidual[hist] = new TPaveText(0.05,0.85,1.0,0.95,"NDC");
    histtitle[hist] = tResidual[hist]->AddText(label);
    //SetTextAlign(11) to left justify, 21 to centre and 31 to right justify
    histtitle[hist]->SetTextAlign(21);
    histtitle[hist]->SetTextSize(0.12);
    tResidual[hist]->SetFillColor(0);
    tResidual[hist]->SetBorderSize(0);
    tResidual[hist]->Draw();
    }

  Residual1->SaveAs("Residual1.png");

  TCanvas *Residual2 = new TCanvas("Residual2", "Residual2", 800, 600);
  Residual2->Divide(5, 4);
  for(int hist=0; hist<20; hist++)
    {
    Residual2->cd(hist+1);
    gPad->SetTopMargin(0.15);
    PhysParamId_t p = kNDFitParam[hist+20];
    const char * label = util::AsString(p).c_str();
    hResidual[hist+20]->Draw();
    tResidual[hist+20] = new TPaveText(0.05,0.85,1.0,0.95,"NDC");
    histtitle[hist+20] = tResidual[hist+20]->AddText(label);
    //SetTextAlign(11) to left justify, 21 to centre and 31 to right justify
    histtitle[hist+20]->SetTextAlign(21);
    histtitle[hist+20]->SetTextSize(0.12);
    tResidual[hist+20]->SetFillColor(0);
    tResidual[hist+20]->SetBorderSize(0);
    tResidual[hist+20]->Draw();
    }

  Residual2->SaveAs("Residual2.png");
   
  TGraph *g_pull_mean = new TGraph(nParams, param_x, pull_mean);
  TGraph *g_pull_sigma = new TGraph(nParams, param_x, pull_sigma);

  TCanvas *PullSummary = new TCanvas("PullSummary", "PullSummary", 800, 600);
  PullSummary->Divide(1);
  PullSummary->cd(1);
  gPad->SetBottomMargin(0.35);
  g_pull_mean->GetXaxis()->SetNdivisions(000);
  g_pull_mean->GetYaxis()->SetRangeUser(-1.0, 3.0);
  FormatGraph(g_pull_mean, 20, 2, 1);
  g_pull_mean->Draw("AP");
  FormatGraph(g_pull_sigma, 20, 4, 1);
  g_pull_sigma->Draw("P");

  TLegend *lpull = new TLegend(0.71, 0.74, 0.85, 0.88);
  lpull->AddEntry(g_pull_mean, "Mean", "P");
  lpull->AddEntry(g_pull_sigma, "Sigma", "P");
  lpull->SetFillColor(0);
  lpull->SetBorderSize(0);
  lpull->Draw();

  for(int param=0; param<nParams; param++)
    {
    PhysParamId_t p = kNDFitParam[param];
    //const char * label = util::AsStringTeX(p,true).c_str();
    const char * label = util::AsString(p).c_str();
    x_low = param + 0.5;
    x_high = x_low + 1.0;
    tPullSummary[param] = new TPaveText(x_low,-1.45,x_high,-1.05);
    axislabel[param] = tPullSummary[param]->AddText(label);
    axislabel[param]->SetTextAngle(90);
    //SetTextAlign(11) to left justify, 21 to centre and 31 to right justify
    axislabel[param]->SetTextAlign(31);
    axislabel[param]->SetTextSize(0.03);
    tPullSummary[param]->SetFillColor(0);
    tPullSummary[param]->SetBorderSize(0);
    tPullSummary[param]->Draw();
    }

  PullSummary->SaveAs("PullSummary.png");
    
  
  TGraph *g_residual_mean = new TGraph(nParams, param_x, residual_mean);
  TGraph *g_residual_sigma = new TGraph(nParams, param_x, residual_sigma);

  TCanvas *ResidualSummary = new TCanvas("ResidualSummary", "ResidualSummary", 800, 600);
  ResidualSummary->Divide(1);
  ResidualSummary->cd(1);
  gPad->SetBottomMargin(0.35);
  g_pull_mean->GetXaxis()->SetNdivisions(000);
  g_residual_mean->GetYaxis()->SetRangeUser(-1.0, 2.0);
  FormatGraph(g_residual_mean, 20, 2, 1);
  g_residual_mean->Draw("AP");
  FormatGraph(g_residual_sigma, 20, 4, 1);
  g_residual_sigma->Draw("P");

  TLegend *lresidual = new TLegend(0.71, 0.74, 0.85, 0.88);
  lresidual->AddEntry(g_residual_mean, "Mean", "P");
  lresidual->AddEntry(g_residual_sigma, "Sigma", "P");
  lresidual->SetBorderSize(0);
  lresidual->SetFillColor(0);
  lresidual->Draw();

  for(int param=0; param<nParams; param++)
    {
    PhysParamId_t p = kNDFitParam[param];
    //const char * label = util::AsStringTeX(p,true).c_str();
    const char * label = util::AsString(p).c_str();
    x_low = param + 0.5;
    x_high = x_low + 1.0;
    tResidualSummary[param] = new TPaveText(x_low,-1.45,x_high,-1.05);
    axislabel[param] = tResidualSummary[param]->AddText(label);
    axislabel[param]->SetTextAngle(90);
    //SetTextAlign(11) to left justify, 21 to centre and 31 to right justify
    axislabel[param]->SetTextAlign(31);
    axislabel[param]->SetTextSize(0.03);
    tResidualSummary[param]->SetFillColor(0);
    tResidualSummary[param]->SetBorderSize(0);
    tResidualSummary[param]->Draw();
    }

  ResidualSummary->SaveAs("ResidualSummary.png");
  

}//end of plot_pulls()


void FormatGraph(TGraph *graph, int style, int colour, int size)
{
  graph->SetTitle("");
  graph->SetMarkerStyle(style);
  graph->SetMarkerColor(colour);
  graph->SetMarkerSize(size);
}
