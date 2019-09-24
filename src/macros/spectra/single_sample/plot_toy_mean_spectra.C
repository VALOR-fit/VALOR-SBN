//
// ------------------------------------------------------------------------------------------------
// Read in N fake data toys and plot the mean total PDF spectra
//
// Francis Bench
// Sept. 2019
// ------------------------------------------------------------------------------------------------
//

double get_max_in_range_1D(TH1D* hist, double xmax);


void plot_toy_mean_spectra(
  const char * config_file,
  const char * filename,
  int ntoys = 10000,
  const char * out_tag = "mean_spectra",
  const char * image_save_format = "pdf",
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

  const char * opt = "data_rf";       // TODO: have the option to use simple binning instead!
  const char * read_opt = "pdft";     // TODO: have the option to use simple binning instead!
  const char * tag = "fakedata";

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

  for(int itoy = 0; itoy < ntoys; ++itoy) {
    // TODO: I don't like reading the input toy stream into a CFM first, then converting to a CFD. Instead save the toys as a CFD stream.
    // Read a fakedata toy from the input file and write hists to an array
    model->Read(*is_fakedata, read_opt);   // The input fakedata toy stream must be first read into the model, as they were generated as models.
    data->Generate(model, true, opt);
    TObjArray * data_array = new TObjArray();
    data->Write(data_array, tag, opt);

    // Extract the histogram for each subdata and add to the mean histogram
    for(int isubdata = 0; isubdata < cd->GetNSubData(); ++isubdata) {
      GenericSingleSampleFitData * subdata = dynamic_cast<GenericSingleSampleFitData*>(cd->GetSubData(isubdata));
      TString ob_name = TString::Format("%s_data_ob_rf_%s", tag, subdata->Name().c_str());
      TH1 * hist_ob = (TH1*) data_array->FindObject(ob_name.Data());

      // Initilise the vector of mean histograms
      if(itoy == 0) { mean_hists.at(isubdata) = (TH1*) hist_ob->Clone(subdata->Name().c_str()); }
      // Add the spectrum for this toy
      else { mean_hists.at(isubdata)->Add(hist_ob); }

      // Convert sum to mean
      if(itoy == ntoys -1) { mean_hists.at(isubdata)->Scale(1.0/((double)ntoys)); }
    } // isubdata

    delete data_array;
  } // itoy

  // Draw and save plots of the mean spectra to the output file
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
    bool is_1D = ( reco_vars.size() == 1 );

    TCanvas* canv = new TCanvas(subdata->Name().c_str(), subdata->Name().c_str(), canv_size_x, canv_size_y);

    // Draw hists
    double max_y = 0.;
    double min_x = 0.;
    double max_x = 0.;
    if(is_1D) {
      TH1D* mean_hist = (TH1D*) mean_hists.at(isubdata)->Clone();

      // Draw within the limits given at the command line
      max_y = 1.2 * get_max_in_range_1D(mean_hist, kinevar_x_max_1D);
      min_x = mean_hist->GetXaxis()->GetBinLowEdge(1);
      max_x = kinevar_x_max_1D;
      TVirtualPad * this_pad = canv->cd(1);
      this_pad->SetLeftMargin(0.2);
      TH1F * pdf_frame = (TH1F*)this_pad->DrawFrame(0, 0, kinevar_x_max_1D, max_y);
      pdf_frame->GetXaxis()->SetTitle(title_x);
      pdf_frame->GetYaxis()->SetTitle("Number of Events");
      pdf_frame->Draw();
      mean_hist->DrawClone("hist,same");
      
      delete mean_hist;
    }
    else {
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

    // TODO: Draw legend, if it exists

    std::string save_name = ((std::string)out_tag) + "." + image_save_format;
    if(isubdata == 0                    && cd->GetNSubData() > 1) { save_name += "("; }
    if(isubdata == cd->GetNSubData() -1 && cd->GetNSubData() > 1) { save_name += ")"; }
    canv->SaveAs(save_name.c_str());
  } // isubdata
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