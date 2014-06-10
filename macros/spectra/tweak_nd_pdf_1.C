//
// ------------------------------------------------------------------------------------------------
// Simple program to test tweaking of LBNx/ND PDFs and MC templates
// Tweak 1 param at a time by +/- 1 sigma
//
// Costas Andreopoulos
// ------------------------------------------------------------------------------------------------
//
	
void tweak_nd_pdf_1
(
  const char * param       = 0,                                     /* parameter name, see NDFitParams.cxx */
  int          plot_type   = 0,                                     /* 0: spectra, 1: spectrum ratios */
  const char * config_file = "lbne_ndfit-2014a-STT_baseline.xml"    /* analysis configuration file */
)
{
  using namespace std;
  using namespace valor;
  using namespace valor::conv;

  double enu_reco_max = 20;

  // Analysis configuration
  TString config = Form("%s/config/%s", gSystem->Getenv("VALOR_LBNX"), config_file);

  // Print settings
  cout << "\n[Job inputs]" << endl;
  cout << "- Reading analysis configuration from: " << config << endl;
  cout << "- Tweaking parameter: " << ((param) ? param : " ** undefined ** ") << endl;

  if(!param) {
    cerr << "** Specify an input parameter!";
    exit(1);
  }

  PhysParamId_t p = util::NDPhysParamFromString(param);
  if(p == kPhypUndefined) {
    cerr << "** Specify an correct ND input parameter!";
    exit(1);
  }

  TCanvas * c  [kNBeamConf];
  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
   c[ibeam] = new TCanvas(Form("c%d",ibeam),"",10,10,1400,400);
   c[ibeam] -> Divide(kNNDSamples);
  }

  // Get ND model & configure
  FitModelABC * model = new NDModel;
  model->Read(config.Data());

  // Arrays to store the spectra for the default, +1 sigma and -1 sigma variations
  const int nspectra = 3;
  const int kdefault = 0;
  const int kpls1sig = 1;
  const int kmin1sig = 2;
  TH1D * pdf     [kNBeamConf][kNNDSamples][nspectra] = { 0 };
  TH1D * pdfratio[kNBeamConf][kNNDSamples][nspectra] = { 0 };

  // Generate pdfs
  for(int i = 0; i < nspectra; i++) {

    cout << "** Iteration: #" << i << endl;

    // Get a nominal physics hypothesis
    PhysHypothesis ph = util::GetPhysHypothesis();

    // Tweak if needed
    if(i == kpls1sig) {
       ph.SetCurrValue(p, 1.5); 
    }
    else 
    if(i == kmin1sig) {
       ph.SetCurrValue(p, 0.5); 
    }
    cout << "Physics hypothesis: " << ph;

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
        pdf[ibeam][isample][i] = new TH1D(*curr_pdf);
/*
        if(i == kpls1sig || i == kmin1sig) {
           TH1D * ratio = new TH1D(*pdf[ibeam][isample][i]);
           ratio->Divide(pdf[ibeam][isample][kdefault]);
           pdf_ratio[ibeam][isample][i] = ratio;
        }
*/
      }//isample
    }//ibeam   

    array->Clear("C");
    delete array;  
  }//i

  // Draw
  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
    BeamConf_t b = kNDBeamConf[ibeam];
    if(b == kbUndefined) continue;
    int ic = 0;
    for(int isample = 0; isample < kNNDSamples; isample++) {
      NDSample_t s = kNDSample[isample];
      if(s == ksNDUndefined) continue;
      c[ibeam]->cd(ic+1);

//      pdf[ibeam][isample][i]->SetTitle(Form("%s/%s",util::AsString(b),util::AsStringTeX(s,true)));
//      pdf[ibeam][isample][i]->SetLineWidth(1);
//      pdf[ibeam][isample][i]->SetLineStyle(kSolid);        

      if(plot_type == 0) {
         double max = -999;
         for(int i=0; i < nspectra; i++) {
          max = TMath::Max(max, pdf[ibeam][isample][kdefault]->GetMaximum());
         }         
         TH1F * hframe = (TH1F*) c[ibeam]->GetPad(ic+1)->DrawFrame(0,0,enu_reco_max,1.2*max);
         hframe->GetXaxis()->SetTitle("Reco. E_{#nu} (GeV)");
         hframe->GetYaxis()->SetTitle("Events in bin");
         pdf[ibeam][isample][kpls1sig]->SetLineColor(kRed);
         pdf[ibeam][isample][kmin1sig]->SetLineColor(kRed);
         hframe->Draw();
         pdf[ibeam][isample][kdefault]->Draw("same");
         pdf[ibeam][isample][kpls1sig]->Draw("same");
         pdf[ibeam][isample][kmin1sig]->Draw("same");
      }//0
      if(plot_type == 1) {
         TH1F * hframe = (TH1F*) c[ibeam]->GetPad(ic+1)->DrawFrame(0,0,enu_reco_max,1.8);
         hframe->GetXaxis()->SetTitle("Reco. E_{#nu} (GeV)");
         hframe->GetYaxis()->SetTitle("ratio (tweaked/nominal)");
         hframe->Draw();
         pdf_ratio[ibeam][isample][kpls1sig]->Draw("same");
         pdf_ratio[ibeam][isample][kmin1sig]->Draw("same");
       }//1             
      ic++;
    }//isample
    c[ibeam]->Update(); 
  }//ibeam   

  // Write out
}
