//
// ------------------------------------------------------------------------------------------------
// Simple program to test tweaking of DUNE/ND PDFs and MC templates.
// The PDF error envelopes are computed by generating N toy-MC experiments throwing 
// all parameters simultaneously.
//
// Costas Andreopoulos
// ------------------------------------------------------------------------------------------------
//
	
void tweak_nd_pdf_N
(
  const char * model_param_list   = "standard",                            /* list of params included in model, see FitParam.cxx */
  const char * config_file        = "dune_ndfit-2015v1-FGTv1.xml"    /* analysis configuration file */
)
{
  using namespace std;
  using namespace valor;
  using namespace valor::conv;

  const int    ntoys        = 200;
  const double enu_reco_max = 10;

  // Analysis configuration
  TString config = Form("%s/config/%s", gSystem->Getenv("VALOR_DUNE"), config_file);

  // Print settings
  cout << "\n[Job inputs]" << endl;
  cout << "- Reading analysis configuration from: " << config << endl;
  cout << "- Model parameter list used : " << model_param_list << endl;

  TCanvas * c  [kNBeamConf];
  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
   c[ibeam] = new TCanvas(Form("c%d",ibeam),"",10,10,700,700);
 //c[ibeam] -> Divide(kNSamples);
   c[ibeam] -> Divide(3,3);
  }

  // Get ND model & configure
  FitModelABC * model = new SDModel;
  model->Read(config.Data());

  // Arrays to store the spectra for the default, +1 sigma and -1 sigma variations
  TH1D * nom_pdf_werr [kNBeamConf][kNSamples]        = { 0 };
  TH1D * nom_pdf      [kNBeamConf][kNSamples]        = { 0 };
  TH1D * twk_pdf      [kNBeamConf][kNSamples][ntoys] = { 0 };
  TH1D * err          [kNBeamConf][kNSamples][2]     = { 0 };
  double max          [kNBeamConf][kNSamples]        = { -999 };

  // Generate pdfs
  for(int itoy = -1; itoy < ntoys; itoy++) {
    cout << "** Toy-MC: #" << itoy << endl;

    // Get a physics hypothesis by randomizing all params
    // (toy-MC #-1 is special: default)
    Option_t * model_param_values = (itoy<0) ? "nominal" : "randomize-all;prefit-errors";
    PhysHypothesis ph = util::GetPhysHypothesis(model_param_list, model_param_values);

    // Generate predictions
    model->Generate(ph,"+SB");

    // Array to store results
    TObjArray * array = new TObjArray();
    array->SetOwner(true);

    // Write stuff out
    model->Write(array,"curr","pdfts_rf +SB");

    // Pick results wanted 
    for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
      BeamConf_t b = kBeamConf[ibeam];
      if(b == kbUndefined) continue;
      for(int isample = 0; isample < kNSamples; isample++) {
        Sample_t s = kSample[isample];
        if(s == ksUndefined) continue;
        const char * name = Form("curr_pdfts_sb_rf_%s_%s",
           util::AsString(b).c_str(), util::AsString(s).c_str());
        TH1D * curr_pdf = (TH1D*) array->FindObject(name);
        assert(curr_pdf);       
        if(itoy < 0) {
           nom_pdf_werr [ibeam][isample] = new TH1D(*curr_pdf);
           nom_pdf      [ibeam][isample] = new TH1D(*curr_pdf);
        } else {
           twk_pdf[ibeam][isample][itoy] = new TH1D(*curr_pdf);
        }
      }//isample
    }//ibeam   
    array->Clear("C");
    delete array;  
  }//itoy

  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
    BeamConf_t b = kBeamConf[ibeam];
    if(b == kbUndefined) continue;
    for(int isample = 0; isample < kNSamples; isample++) {
      Sample_t s = kSample[isample];
      if(s == ksUndefined) continue;
      err [ibeam][isample][0] = new TH1D(*nom_pdf[ibeam][isample]);
      err [ibeam][isample][1] = new TH1D(*nom_pdf[ibeam][isample]);
      err [ibeam][isample][0] -> Reset();
      err [ibeam][isample][1] -> Reset();
      for(int ebin = 1; ebin <= nom_pdf[ibeam][isample]->GetNbinsX(); ebin++) {
         double nom_val = nom_pdf[ibeam][isample]->GetBinContent(ebin);
         double sumsq   = 0;
         for(int itoy = 0; itoy < ntoys; itoy++) {
            double curr_val = twk_pdf[ibeam][isample][itoy]->GetBinContent(ebin);
            sumsq += TMath::Power(curr_val-nom_val,2.);
         }//itoy
         double one_sigma = TMath::Sqrt(sumsq/ntoys);
         err [ibeam][isample][0]->SetBinContent(ebin, nom_val + one_sigma);
         err [ibeam][isample][1]->SetBinContent(ebin, nom_val - one_sigma);
         nom_pdf_werr [ibeam][isample] -> SetBinError(ebin,one_sigma);
         if( nom_pdf[ibeam][isample]->GetBinCenter(ebin) < enu_reco_max ) {
            max [ibeam][isample] = TMath::Max(max[ibeam][isample], nom_val + one_sigma);
         }
      }//ebin
    }//isample
  }//ibeam   


  // Draw
  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
    BeamConf_t b = kBeamConf[ibeam];
    if(b == kbUndefined) continue;
    int ic = 0;
    for(int isample = 0; isample < kNSamples; isample++) {
      Sample_t s = kSample[isample];
      if(s == ksUndefined) continue;
      ic++;
      c[ibeam]->cd(ic);
      TH1F * hframe = c[ibeam]->GetPad(ic)->DrawFrame(0.,0.,enu_reco_max, 1.24*max[ibeam][isample]);
      hframe -> GetXaxis() -> SetTitle("Reco. E_{#nu} (GeV)");
      hframe -> GetYaxis() -> SetTitle("");      
    //hframe -> GetYaxis() -> SetTitle("Events per bin");      
      hframe -> Draw();
      nom_pdf_werr [ibeam][isample] -> SetFillColor(kRed);
      nom_pdf_werr [ibeam][isample] -> SetLineColor(kRed);
      nom_pdf_werr [ibeam][isample] -> SetLineWidth(0);
      nom_pdf_werr [ibeam][isample] -> SetMarkerSize(0);
      nom_pdf_werr [ibeam][isample] -> Draw("E2SAME");
      nom_pdf      [ibeam][isample] -> SetLineColor(kBlack);
      nom_pdf      [ibeam][isample] -> SetMarkerSize(0);
      nom_pdf      [ibeam][isample] -> SetLineWidth(1);
      nom_pdf      [ibeam][isample] -> Draw("SAME");
      TLatex * title = new TLatex(1,1.03*max[ibeam][isample],Form("%s / %s", util::AsString(b).c_str(), util::AsStringTeX(s,true).c_str()));
      title->SetTextSize(0.08);
      title->Draw();
      TLegend * leg = new TLegend(0.50, 0.50, 0.92, 0.80);
      leg->SetFillColor(0);
      //leg->SetHeader(Form("%s / %s", util::AsString(b).c_str(), util::AsStringTeX(s,true).c_str()));
      leg->AddEntry(nom_pdf     [ibeam][isample], "nominal",        "L");
      leg->AddEntry(nom_pdf_werr[ibeam][isample], "a-priori error", "F");
      leg->Draw();
    }//isample
    c[ibeam]->Update();
  }//ibeam   

}
