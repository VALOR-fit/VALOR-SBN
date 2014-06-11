//
// ------------------------------------------------------------------------------------------------
// Simple program to test tweaking of LBNx/ND PDFs and MC templates.
// The PDF error envelopes are computed by generating N toy-MC experiments throwing 
// all parameters simultaneously.
//
// Costas Andreopoulos
// ------------------------------------------------------------------------------------------------
//
	
void tweak_nd_pdf_N
(
  const char * config_file = "lbne_ndfit-2014a-STT_baseline.xml"    /* analysis configuration file */
)
{
  using namespace std;
  using namespace valor;
  using namespace valor::conv;

  const int    ntoys        = 5;
  const double enu_reco_max = 10;

  // Analysis configuration
  TString config = Form("%s/config/%s", gSystem->Getenv("VALOR_LBNX"), config_file);

  // Print settings
  cout << "\n[Job inputs]" << endl;
  cout << "- Reading analysis configuration from: " << config << endl;

  TCanvas * c  [kNBeamConf];
  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
   c[ibeam] = new TCanvas(Form("c%d",ibeam),"",10,10,1400,400);
   c[ibeam] -> Divide(kNNDSamples);
  }

  // Get ND model & configure
  FitModelABC * model = new NDModel;
  model->Read(config.Data());

  // Arrays to store the spectra for the default, +1 sigma and -1 sigma variations
  TH1D * nom_pdf_werr [kNBeamConf][kNNDSamples]        = { 0 };
  TH1D * nom_pdf      [kNBeamConf][kNNDSamples]        = { 0 };
  TH1D * twk_pdf      [kNBeamConf][kNNDSamples][ntoys] = { 0 };
  TH1D * err          [kNBeamConf][kNNDSamples][2]     = { 0 };
  double max          [kNBeamConf][kNNDSamples]        = { -999 };

  // Generate pdfs
  for(int itoy = -1; itoy < ntoys; itoy++) {
    cout << "** Toy-MC: #" << itoy << endl;

    // Get a physics hypothesis by randomizing all params
    // (toy-MC #-1 is special: default)
    Option_t * opt = (itoy<0) ? "default" : "randomize";
    PhysHypothesis ph = util::GetPhysHypothesis(opt);

    // Generate predictions
    model->Generate(ph);

    // Array to store results
    TObjArray * array = new TObjArray();
    array->SetOwner(true);

    // Write stuff out
    model->Write(array,"curr","pdfts_rf +SB");

    // Pick results wanted 
    for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
      BeamConf_t b = kNDBeamConf[ibeam];
      if(b == kbUndefined) continue;
      for(int isample = 0; isample < kNNDSamples; isample++) {
        NDSample_t s = kNDSample[isample];
        if(s == ksNDUndefined) continue;
        const char * name = Form("curr_pdfsbts_rf_%s_%s",
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
    BeamConf_t b = kNDBeamConf[ibeam];
    if(b == kbUndefined) continue;
    for(int isample = 0; isample < kNNDSamples; isample++) {
      NDSample_t s = kNDSample[isample];
      if(s == ksNDUndefined) continue;
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
    BeamConf_t b = kNDBeamConf[ibeam];
    if(b == kbUndefined) continue;
    int ic = 0;
    for(int isample = 0; isample < kNNDSamples; isample++) {
      NDSample_t s = kNDSample[isample];
      if(s == ksNDUndefined) continue;
      ic++;
      c[ibeam]->cd(ic);
      TH1F * hframe = c[ibeam]->GetPad(ic)->DrawFrame(0.,0.,enu_reco_max, 1.2*max[ibeam][isample]);
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
      TLatex * title = new TLatex(1,1.1*max[ibeam][isample],Form("%s / %s", util::AsString(b).c_str(), util::AsStringTeX(s,true).c_str()));
      title->Draw();
      TLegend * leg = new TLegend(0.50, 0.56, 0.92, 0.86);
      leg->SetFillColor(0);
      //leg->SetHeader(Form("%s / %s", util::AsString(b).c_str(), util::AsStringTeX(s,true).c_str()));
      leg->AddEntry(nom_pdf     [ibeam][isample], "nominal",        "L");
      leg->AddEntry(nom_pdf_werr[ibeam][isample], "a-priori error", "F");
      leg->Draw();
    }//isample
    c[ibeam]->Update();
  }//ibeam   

}
