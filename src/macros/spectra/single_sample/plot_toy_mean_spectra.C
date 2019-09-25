//
// ------------------------------------------------------------------------------------------------
// Read in N fake data toys and plot the mean total PDF spectra
// Optionally project to 1D and plot RMS stat+syst error envelopes
//
// Francis Bench
// Sept. 2019
// ------------------------------------------------------------------------------------------------
//

double get_max_in_range_1D(TH1D* hist, double xmax);

//___________________________________________________________________________
void plot_toy_mean_spectra(
  const char * config_file,
  const char * filename,
  int ntoys = 10000,
  bool plot_1sigma_1D_error = true,           // If true, projects all spectra to 1D (according to project_to_kinevar) and plots RMS error bands
  const char * project_to_kinevar = "Ereco",  // Only used if plot_1sigma_1D_error = true. See KineSpace.cxx
  const char * out_tag = "mean_spectra",
  const char * image_save_format = "pdf",
  bool stat_fluct = true,
  int canv_size_x = 700,
  int canv_size_y = 700,
  double kinevar_x_max_1D = 3.,      // Max value of the kinematic variable drawn on the x-axis (1D plots)
  double kinevar_x_max_2D = 1.25,    // Max value of the kinematic variable drawn on the x-axis (2D plots)
  double kinevar_y_max_2D = 180.,    // Max value of the kinematic variable drawn on the y-axis (2D plots)
  const char * title_x = "#nu Reconstructed Energy (GeV)",
  const char * title_y = "#theta (degrees)"                 // Used for 2D plots only
)
{
  using std::cout;
  using std::endl;
  using std::vector;
  using namespace valor;
  using namespace valor::conv;
  namespace vutil = valor::util;

  gStyle->SetPalette(56);   // Palette 56 is "inverted dark-body radiator"

  const char * write_opt = "data_rf+slices";  // TODO: have the option to use simple binning instead!
  const char * gen_opt   = "";                // TODO: have the option to use simple binning instead!
  const char * read_opt  = "pdft";            // TODO: have the option to use simple binning instead!
  const char * tag       = "fakedata";

  std::string save_name = ((std::string)out_tag);
  if(plot_1sigma_1D_error) {
    save_name += "_error_band";
  }

  // TODO: Want the option of comparing to another hist too

  CompoundFitElements* elements = new CompoundFitElements();
  elements->Read(vutil::CompleteConfigPath(config_file));
  FitModelABC* model = elements->FitModel();
  FitDataABC* data = elements->FitData();
  //CompoundFitModel * cm = dynamic_cast<CompoundFitModel*>(model);
  CompoundFitData  * cd = dynamic_cast<CompoundFitData*> (data);

  cout << "Reading fake data from file [" << filename << "]" << endl;
  std::ifstream * is_fakedata = new std::ifstream(filename, std::ios::binary | std::ios::in);

  vector<TH1*> mean_hists(cd->GetNSubData(), nullptr);

  // Vector which we'll use to store the content of each bin for each toy in order to generate error bands
  vector<vector<vector<double>>> toy_bin_content;   // 1st index = subdata; 2nd index = bin; 3rd index = toy

  for(int itoy = 0; itoy < ntoys; ++itoy) {
    if(itoy % 1000 == 0) { cout << "Reading toy #" << itoy << endl; }

    // TODO: I don't like reading the input toy stream into a CFM first, then converting to a CFD. Instead save the toys as a CFD stream.
    // Read a fakedata toy from the input file and write hists to an array
    model->Read(*is_fakedata, read_opt);   // The input fakedata toy stream must be first read into the model, as they were generated as models.
    data->Generate(model, stat_fluct, gen_opt);
    TObjArray * data_array = new TObjArray();
    data->Write(data_array, tag, write_opt);

    // Extract the histogram for each subdata and add to the mean histogram
    for(int isubdata = 0; isubdata < cd->GetNSubData(); ++isubdata) {
      GenericSingleSampleFitData * subdata = dynamic_cast<GenericSingleSampleFitData*>(cd->GetSubData(isubdata));

      TString ob_name;
      if(plot_1sigma_1D_error) { ob_name = TString::Format("%s_data_ob_rf_slice_%s_%s", tag, subdata->Name().c_str(), project_to_kinevar); }
      else {                     ob_name = TString::Format("%s_data_ob_rf_%s", tag, subdata->Name().c_str()); }

      TH1 * hist_ob = (TH1*) data_array->FindObject(ob_name.Data());
      if(!hist_ob) {
        cerr << "ERROR: could not find hist named [" << ob_name << "] in the array with contents:" << endl;
        data_array->Print();
        vutil::Die(-1);
      }

      if(itoy == 0) {
        // Initialise the vector of mean histograms
        mean_hists.at(isubdata) = (TH1*) hist_ob->Clone(subdata->Name().c_str());

        // Initialise a vector which we'll use to store the content of each bin for each toy in order to generate error bands
        if(plot_1sigma_1D_error) {
          toy_bin_content.push_back( vector<vector<double>>( hist_ob->GetNbinsX(), vector<double>(ntoys) ) );
        }
      }
      else {
        // Add the spectrum for this toy
        mean_hists.at(isubdata)->Add(hist_ob);
      }

      if(plot_1sigma_1D_error) {
        for(int ibin_1D = 0; ibin_1D < hist_ob->GetNbinsX(); ++ibin_1D) {
          toy_bin_content[isubdata][ibin_1D][itoy] = hist_ob->GetBinContent(ibin_1D +1);  // +1 because the 1st hist bin is an underflow
        }
      }

      // Convert sum to mean
      if(itoy == ntoys -1) { mean_hists.at(isubdata)->Scale(1.0/((double)ntoys)); }
    } // isubdata

    delete data_array;
  } // itoy
  cout << "Finished reading fakedata toys. Will start plotting" << endl;

  // Draw and save plots of the mean spectra to the output file
  std::string root_save_name = save_name + ".root";
  TFile* root_file_out = new TFile(root_save_name.c_str(), "recreate");
  for(int isubdata = 0; isubdata < cd->GetNSubData(); ++isubdata) {
    // Get the kinematic variables used for binning to decide whether to plot in 1D or 2D
    GenericSingleSampleFitData * subdata = dynamic_cast<GenericSingleSampleFitData*>(cd->GetSubData(isubdata));
    const SingleSampleKineBinning* sskb = subdata->GetBinning();
    const VALORBinning * reco_opt = sskb->RecoOptBinning();
    const vector<KineVar_t> & reco_vars = reco_opt->KineVars();
    if(!(reco_vars.size() == 1 || reco_vars.size() == 2)) {
      std::cerr << "ERROR: The number of reco dimensions to plot was != 1 or 2." << endl;
      vutil::Die(-1);
    }
    bool is_1D = ( reco_vars.size() == 1 || plot_1sigma_1D_error );

    TCanvas* canv = new TCanvas(subdata->Name().c_str(), subdata->Name().c_str(), canv_size_x, canv_size_y);

    // Draw and save hists
    double max_y = 0.;
    double min_x = 0.;
    double max_x = 0.;
    if(is_1D) {
      canv->cd();
      TH1D* mean_hist     = (TH1D*) mean_hists.at(isubdata)->Clone();
      TH1D* err_up_hist   = (TH1D*) mean_hist->Clone();
      TH1D* err_down_hist = (TH1D*) mean_hist->Clone();
      TLegend* leg = new TLegend(0.70, 0.80, 0.90, 0.95);
      err_up_hist  ->Reset();
      err_down_hist->Reset();

      if(plot_1sigma_1D_error) {
        // Calculate the RMS error for each bin
        for(int ibin = 0; ibin < mean_hist->GetNbinsX(); ++ibin) {
          double err = TMath::RMS(toy_bin_content[isubdata][ibin].begin(), toy_bin_content[isubdata][ibin].end());
          err_up_hist  ->SetBinContent(ibin +1, mean_hist->GetBinContent(ibin +1) + err);  // +1 because the 1st hist bin is an underflow
          err_down_hist->SetBinContent(ibin +1, mean_hist->GetBinContent(ibin +1) - err);  // +1 because the 1st hist bin is an underflow
        }
      }

      // Draw within the limits given at the command line
      max_y = 1.2 * TMath::Max(get_max_in_range_1D(mean_hist  , kinevar_x_max_1D),
                               get_max_in_range_1D(err_up_hist, kinevar_x_max_1D));
      min_x = mean_hist->GetXaxis()->GetBinLowEdge(1);
      if(reco_vars.size() == 1) { max_x = kinevar_x_max_1D; }
      else { max_x = kinevar_x_max_2D; }
      TVirtualPad * this_pad = canv->cd(1);
      this_pad->SetLeftMargin(0.2);
      TH1F * pdf_frame = (TH1F*)this_pad->DrawFrame(0, 0, max_x, max_y);
      pdf_frame->GetXaxis()->SetTitle(title_x);
      pdf_frame->GetYaxis()->SetTitle("Number of Events");
      pdf_frame->Draw();

      if(plot_1sigma_1D_error) {
        err_up_hist  ->SetFillColor(kRed);
        err_up_hist  ->SetFillStyle(1001);
        err_up_hist  ->SetLineWidth(1);
        err_up_hist  ->DrawClone("hist,same");
        err_down_hist->SetFillColor(10);
        err_down_hist->SetFillStyle(1001);
        err_down_hist->SetLineWidth(1);
        err_down_hist->DrawClone("hist,same");

        leg->AddEntry(mean_hist  , "Mean"     , "l");
        leg->AddEntry(err_up_hist, "RMS Error", "f");
        leg->DrawClone();
      }

      mean_hist->DrawClone("hist,same");

      root_file_out->cd();
      root_file_out  ->WriteObject(mean_hist    , TString::Format("%s_%s", subdata->Name().c_str(), "mean_PDF").Data());
      if(plot_1sigma_1D_error) {
        root_file_out->WriteObject(err_up_hist  , TString::Format("%s_%s", subdata->Name().c_str(), "mean_PDF_err_up").Data());
        root_file_out->WriteObject(err_down_hist, TString::Format("%s_%s", subdata->Name().c_str(), "mean_PDF_err_down").Data());
      }

      delete mean_hist;
      delete err_up_hist;
      delete err_down_hist;
      delete leg;
    }
    else {
      canv->cd();
      TH2D* mean_hist = (TH2D*) mean_hists.at(isubdata)->Clone();

      max_y = kinevar_y_max_2D;
      min_x = mean_hist->GetXaxis()->GetBinLowEdge(1);
      max_x = kinevar_x_max_2D;
      TVirtualPad *this_pad = canv->cd(1);
      this_pad->SetLeftMargin(0.16);
      this_pad->SetRightMargin(0.12);
      TH1F *pdf_frame = (TH1F *) this_pad->DrawFrame(0, 0, kinevar_x_max_2D, kinevar_y_max_2D);
      pdf_frame->GetXaxis()->SetTitle(title_x);
      pdf_frame->GetYaxis()->SetTitle(title_y);
      pdf_frame->GetZaxis()->SetTitle("Number of Events");
      pdf_frame->Draw();
      mean_hist->DrawClone("colz,same");

      root_file_out->cd();
      root_file_out->WriteObject(mean_hist, TString::Format("%s_%s", subdata->Name().c_str(), "mean_PDF").Data());

      delete mean_hist;
    }

    // Draw title
    TString title_str = TString::Format("%s", subdata->Name().c_str());
    TPaveText * title = new TPaveText(min_x * 1.05, max_y, max_x, max_y * 1.07 );
    title->SetShadowColor(0);
    title->SetFillColor(0);
    title->SetFillStyle(0);
    title->SetLineColor(0);
    title->AddText(title_str);
    title->SetTextSize(0.035);
    title->Draw("NB,same");

    // Save canvas to the output file
    std::string canv_save_name = save_name + "." + ((std::string)image_save_format);
    if(isubdata == 0                    && cd->GetNSubData() > 1) { canv_save_name += "("; }
    if(isubdata == cd->GetNSubData() -1 && cd->GetNSubData() > 1) { canv_save_name += ")"; }
    canv->SaveAs(canv_save_name.c_str());
  } // isubdata

  root_file_out->Close();
  delete root_file_out;

}

//___________________________________________________________________________
double get_max_in_range_1D(TH1D* hist, double xmax)
{
  double max_n = 0.;
  for(int xbin = 1; xbin <= hist->GetNbinsX(); xbin++) {
    if(hist->GetBinCenter(xbin) < xmax ) {
      max_n = TMath::Max(max_n, hist->GetBinContent(xbin));
    } //<xmax
  } //xbin
  return max_n;
}
//___________________________________________________________________________