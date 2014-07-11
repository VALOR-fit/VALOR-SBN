
void FormatGraph(TGraph *graph, int style, int colour, int size);

void plot_pulls(
const int nParams = 42
)
{
  using namespace valor;
  using namespace valor::conv;
 
  TChain *toymcchain = new TChain("fitnt");
  toymcchain->Add("/opt/ppd/t2k/users/nick/LBNX/macros/fit/nd/pull_migraderrors/toymc*.root");

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

  TH1D *hPull[nParams];
  TH1D *hResidual[nParams];

  for(int hist=0; hist<nParams; hist++)
    {
    hPull[hist] = new TH1D(Form("hPull%02i", hist), "", 25, -2.5, 2.5);
    hResidual[hist] = new TH1D(Form("hResidual%02i", hist), "", 250, -2.5, 2.5);
    } 

  // Loop over entries (toy-MC experiments) in the tree
  for(Long_t i; i < fitnt->GetEntries(); i++) 
    {
    fitnt->GetEntry(i);

    cout<<"migraderr =    "<<migraderr;

    if(migradmin == 0 && migraderr == 3)
      {
      j = -1;
      for(PhysParamId_t p = kNuis000; p<kNuis000+nParams; p++)
        {
        j++;
        pull = (best_fit_param_array->BestFitValue(p) - true_param_array->Value(p)) 
	     / sqrt(kNDFitParamAPrioriFracError[j]*kNDFitParamAPrioriFracError[j] - best_fit_param_array->MigradError(p)*best_fit_param_array->MigradError(p));
        hPull[j]->Fill(pull);
        residual = best_fit_param_array->BestFitValue(p) - true_param_array->Value(p);
        hResidual[j]->Fill(residual);
        }
      }
    }
  
  TF1 *gauss = new TF1("gauss", "gaus", -2.0, 2.0);
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
    hPull[hist]->Draw();
    }

  Pull1->SaveAs("Pull1.png");

  TCanvas *Pull2 = new TCanvas("Pull2", "Pull2", 800, 600);
  Pull2->Divide(5, 4);
  for(int hist=0; hist<20; hist++)
    {
    Pull2->cd(hist+1);
    hPull[hist+20]->Draw();
    }

  Pull2->SaveAs("Pull2.png");

  TCanvas *Residual1 = new TCanvas("Residual1", "Residual1", 800, 600);
  Residual1->Divide(5, 4);
  for(int hist=0; hist<20; hist++)
    {
    Residual1->cd(hist+1);
    hResidual[hist]->Draw();
    }

  Residual1->SaveAs("Residual1.png");

  TCanvas *Residual2 = new TCanvas("Residual2", "Residual2", 800, 600);
  Residual2->Divide(5, 4);
  for(int hist=0; hist<20; hist++)
    {
    Residual2->cd(hist+1);
    hResidual[hist+20]->Draw();
    }

  Residual2->SaveAs("Residual2.png");

  TGraph *g_pull_mean = new TGraph(nParams, param_x, pull_mean);
  TGraph *g_pull_sigma = new TGraph(nParams, param_x, pull_sigma);

  TCanvas *PullSummary = new TCanvas("PullSummary", "PullSummary", 800, 600);
  g_pull_mean->GetXaxis()->SetTitle("Parameter");
  g_pull_mean->GetYaxis()->SetRangeUser(-1.0, 3.0);
  FormatGraph(g_pull_mean, 20, 2, 1);
  g_pull_mean->Draw("AP");
  FormatGraph(g_pull_sigma, 20, 1, 1);
  g_pull_sigma->Draw("P");

  TLegend *lpull = new TLegend(0.25, 0.7, 0.4, 0.85);
  lpull->AddEntry(g_pull_mean, "Mean", "P");
  lpull->AddEntry(g_pull_sigma, "Sigma", "P");
  lpull->SetBorderSize(0);
  lpull->Draw();

  PullSummary->SaveAs("PullSummary.png");

  TGraph *g_residual_mean = new TGraph(nParams, param_x, residual_mean);
  TGraph *g_residual_sigma = new TGraph(nParams, param_x, residual_sigma);

  TCanvas *ResidualSummary = new TCanvas("ResidualSummary", "ResidualSummary", 800, 600);
  g_residual_mean->GetXaxis()->SetTitle("Parameter");
  g_residual_mean->GetYaxis()->SetRangeUser(-1.0, 2.0);
  FormatGraph(g_residual_mean, 20, 2, 1);
  g_residual_mean->Draw("AP");
  FormatGraph(g_residual_sigma, 20, 1, 1);
  g_residual_sigma->Draw("P");

  TLegend *lresidual = new TLegend(0.7, 0.7, 0.85, 0.85);
  lresidual->AddEntry(g_residual_mean, "Mean", "P");
  lresidual->AddEntry(g_residual_sigma, "Sigma", "P");
  lresidual->SetBorderSize(0);
  lresidual->Draw();

  ResidualSummary->SaveAs("ResidualSummary.png");
    
}//end of plot_pulls()


void FormatGraph(TGraph *graph, int style, int colour, int size)
{
  graph->SetMarkerStyle(style);
  graph->SetMarkerColor(colour);
  graph->SetMarkerSize(size);
  graph->GetXaxis()->SetTitleOffset(1.2);
  graph->GetXaxis()->CenterTitle();
}
