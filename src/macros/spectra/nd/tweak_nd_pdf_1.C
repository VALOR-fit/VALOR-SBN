//
// ------------------------------------------------------------------------------------------------
// Simple program to test tweaking of DUNE/ND PDFs and MC templates
// Tweak 1 param at a time by +/- 1 sigma
//
// Costas Andreopoulos
// ------------------------------------------------------------------------------------------------
//
	
void tweak_nd_pdf_1
(
  const char * param              = 0,                                     /* parameter name, see NDFitParams.cxx */
  int          plot_type          = 0,                                     /* 0: spectra, 1: spectrum ratios */
  const char * model_param_list   = "standard",                            /* list of params included in model, see NDFitParams.cxx */
  const char * model_param_values = "nominal",                             /* specify param values included in model, see NDFitParams.cxx */
  const char * config_file        = "dune_ndfit-2015v1-FGTv1.xml"    /* analysis configuration file */
)
{
  using namespace std;
  using namespace valor;
  using namespace valor::conv;

  double enu_reco_max = 20;

  // Analysis configuration
  TString config = Form("%s/config/%s", gSystem->Getenv("VALOR_DUNE"), config_file);

  // Print settings
  cout << "\n[Job inputs]" << endl;
  cout << "- Reading analysis configuration from: " << config << endl;
  cout << "- Model parameter list used : " << model_param_list << endl;
  cout << "- Setting parameter values: " << model_param_values << endl;
  cout << "- Tweaking parameter: " << ((param) ? param : " ** undefined ** ") << endl;
  cout << endl;

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
   c[ibeam] = new TCanvas(Form("c%d",ibeam),"",10,10,700,700);
 //c[ibeam] -> Divide(kNNDSamples);
   c[ibeam] -> Divide(3,3);
  }

  // Get ND model & configure
  FitModelABC * model = new NDModel;
  model->Read(config.Data());

  // Arrays to store the spectra for the default, +1 sigma and -1 sigma variations
  const int nspectra = 5;
  const int kdefault = 0;
  const int kpls1sig = 1;
  const int kmin1sig = 2;
  const int kpls2sig = 3;
  const int kmin2sig = 4;
  double pdf_max  [kNBeamConf][kNNDSamples]           = { -999 };
  TH1D * pdf      [kNBeamConf][kNNDSamples][nspectra] = { 0 };
  TH1D * pdf_ratio[kNBeamConf][kNNDSamples][nspectra] = { 0 };

  // Generate pdfs
  for(int i = 0; i < nspectra; i++) {
    cout << "** Iteration: #" << i << endl;

    // Get a nominal physics hypothesis
    PhysHypothesis ph = util::GetPhysHypothesis(model_param_list,model_param_values);
    // Tweak if needed
    if(i != kdefault) {
      int ip = util::NDArrIdx::Instance()->NDFitParamIdx(p); // find param idx
      assert(ip>=0 && ip<conv::kNNDFitParams);
      // ----
      // improve this
      double sig = 0.2;
      if(conv::kNDFitIsFluxRelated[ip]) { sig = ((NDModel*)model)->GetNuFlux()->OneSigmaError((conv::PhysParamId_t)p); }
      // -----
      if(i == kpls1sig) { ph.SetCurrValue(p, 1 +   sig); }
      if(i == kmin1sig) { ph.SetCurrValue(p, 1 -   sig); }
      if(i == kpls2sig) { ph.SetCurrValue(p, 1 + 2*sig); }
      if(i == kmin2sig) { ph.SetCurrValue(p, 1 - 2*sig); }
    }
    cout << "Physics hypothesis: " << ph;

    // Generate predictions
    model->Generate(ph,"+SB");

    // Array to store results
    TObjArray * array = new TObjArray();
    array->SetOwner(true);

    // Write stuff out
    model->Write(array,"curr","pdfts_rf +SB");
    array->Print();

    // Pick results wanted 
    for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
      BeamConf_t b = kNDBeamConf[ibeam];
      if(b == kbUndefined) continue;
      for(int isample = 0; isample < kNNDSamples; isample++) {
        NDSample_t s = kNDSample[ibeam][isample];
        if(s == ksNDUndefined) continue;
        const char * name = Form("curr_pdfts_sb_rf_%s_%s",
           util::AsString(b).c_str(), util::AsString(s).c_str());
        cout << "Retrieving (beam #" << ibeam << ", sample #" << isample << "): " << name << endl;
        TH1D * curr_pdf = (TH1D*) array->FindObject(name);
        assert(curr_pdf);       
        pdf[ibeam][isample][i] = new TH1D(*curr_pdf);
      }//isample
    }//ibeam   
    array->Clear("C");
    delete array;  
  }//i

  // Form ratios and scan for max value in input Ereco range
  for(int ibeam = 0; ibeam < kNBeamConf; ibeam++) {
    BeamConf_t b = kNDBeamConf[ibeam];
    if(b == kbUndefined) continue;
    for(int isample = 0; isample < kNNDSamples; isample++) {
      NDSample_t s = kNDSample[isample];
      if(s == ksNDUndefined) continue;
      for(int i=0; i < nspectra; i++) {
          pdf_ratio[ibeam][isample][i] = new TH1D(* pdf[ibeam][isample][kdefault]); // create with correct binning
          pdf_ratio[ibeam][isample][i] -> Reset(); // reset contents
      }//i
      for(int ebin = 1; ebin <= pdf[ibeam][isample][kdefault]->GetNbinsX(); ebin++) {
         // update max
         if(pdf[ibeam][isample][kdefault]->GetBinCenter(ebin) < enu_reco_max ) {
           for(int i=0; i < nspectra; i++) {
              double val = pdf[ibeam][isample][i]->GetBinContent(ebin);         
              pdf_max[ibeam][isample] = TMath::Max(pdf_max[ibeam][isample], val);
           }//i
         }//<emax
         // form ratios
         for(int i=0; i < nspectra; i++) {
            double val_def = pdf[ibeam][isample][kdefault]->GetBinContent(ebin);         
            if(i==kdefault) {
               pdf_ratio[ibeam][isample][kdefault] -> SetBinContent(ebin, 1);
            } else {
              double val_twk = pdf[ibeam][isample][i]->GetBinContent(ebin);         
              double ratio   = (val_def > 0) ? val_twk/val_def : 1;
              pdf_ratio[ibeam][isample][i] -> SetBinContent(ebin, ratio);
            }
         }//i
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
      const char * title_str = Form("%s / %s", util::AsString(b).c_str(), util::AsStringTeX(s,true).c_str());
      if(plot_type == 0) {
         TH1F * hframe = (TH1F*) c[ibeam]->GetPad(ic)->DrawFrame(0,0,enu_reco_max,1.2*pdf_max[ibeam][isample]);
         hframe->GetXaxis()->SetTitle("Reco. E_{#nu} (GeV)");
         hframe->GetYaxis()->SetTitle("Events in bin");
         for(int i=0; i < nspectra; i++) {
           pdf[ibeam][isample][i]->SetLineWidth(1);
           if(i == kdefault) {
              pdf[ibeam][isample][i]->SetLineColor(kBlack);
           } else {
              pdf[ibeam][isample][i]->SetLineColor(kRed);
           }
         }
         pdf[ibeam][isample][kpls2sig]->SetLineStyle(kDashed);
         pdf[ibeam][isample][kmin2sig]->SetLineStyle(kDashed);
         hframe->Draw();
         pdf[ibeam][isample][kdefault]->Draw("same");
         pdf[ibeam][isample][kpls1sig]->Draw("same");
         pdf[ibeam][isample][kmin1sig]->Draw("same");
         pdf[ibeam][isample][kpls2sig]->Draw("same");
         pdf[ibeam][isample][kmin2sig]->Draw("same");
         TLatex * title = new TLatex(1,1.1*pdf_max[ibeam][isample],title_str);
         title->Draw();
         TLegend * leg = new TLegend(0.50, 0.56, 0.92, 0.86);
         leg->SetFillColor(0);
         leg->SetHeader(util::AsStringTeX(p,true).c_str());
         leg->AddEntry(pdf[ibeam][isample][kdefault], "nominal",     "L");
         leg->AddEntry(pdf[ibeam][isample][kpls1sig], "#pm 1#sigma", "L");
         leg->AddEntry(pdf[ibeam][isample][kpls2sig], "#pm 2#sigma", "L");
         leg->Draw();
      }//0
      if(plot_type == 1) {
         TH1F * hframe = (TH1F*) c[ibeam]->GetPad(ic)->DrawFrame(0,0.7,enu_reco_max,1.3);
         hframe->GetXaxis()->SetTitle("Reco. E_{#nu} (GeV)");
         hframe->GetYaxis()->SetTitle("ratio (tweaked/nominal)");
         for(int i=0; i < nspectra; i++) {
           pdf_ratio[ibeam][isample][i]->SetLineWidth(1);
         }
         pdf_ratio[ibeam][isample][kpls2sig]->SetLineStyle(kDashed);
         pdf_ratio[ibeam][isample][kmin2sig]->SetLineStyle(kDashed);
         hframe->Draw();
       //pdf_ratio[ibeam][isample][kdefault]->Draw("same");
         pdf_ratio[ibeam][isample][kpls1sig]->Draw("same");
         pdf_ratio[ibeam][isample][kmin1sig]->Draw("same");
         pdf_ratio[ibeam][isample][kpls2sig]->Draw("same");
         pdf_ratio[ibeam][isample][kmin2sig]->Draw("same");
         TLatex * title = new TLatex(1,1.24,title_str);
         title->Draw();
         TLegend * leg = new TLegend(0.50, 0.56, 0.92, 0.86);
         leg->SetFillColor(0);
         leg->SetHeader(util::AsStringTeX(p,true).c_str());
         leg->AddEntry(pdf_ratio[ibeam][isample][kpls1sig], "#pm 1#sigma", "L");
         leg->AddEntry(pdf_ratio[ibeam][isample][kpls2sig], "#pm 2#sigma", "L");
         leg->Draw();
       }//1             
    }//isample
    c[ibeam]->Update(); 
  }//ibeam   

  // Write out
}
