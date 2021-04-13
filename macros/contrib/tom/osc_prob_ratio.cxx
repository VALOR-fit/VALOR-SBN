// Check the variable baseline approximation

#include <iostream>
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPad.h"
#include "TString.h"
#include "TF1.h"
#include "TGraph.h"
#include "TStyle.h"
#include "TMath.h"
#include "TSpline.h"

// valor includes 
#include "valor/Oscillation/SimpleOsc.h"
#include "valor/Utilities/Interpolator.h"
#include "valor/FitElements/GenericSingleSampleFitModel.h"


using namespace valor;
using namespace valor::conv;

void osc_prob_ratio(
        const char* file
        ){

// read in root file
TFile *osc_prob  = new TFile(file,"read");
TH1F *true_sbnd  = (TH1F*) osc_prob->Get("h_true_baseline_sbnd");
TH1F *VALOR_sbnd = (TH1F*) osc_prob->Get("h_VALOR_baseline_sbnd");
TH1F *ratio_sbnd = new TH1F(*true_sbnd);

true_sbnd->GetYaxis()->SetRangeUser(0.998,1.0005);
true_sbnd->Draw();
VALOR_sbnd->Draw("same");




ratio_sbnd->SetLineColor(kBlue);
ratio_sbnd->Divide(VALOR_sbnd);
ratio_sbnd->Draw("same");


TLegend *leg = new TLegend(0.65,0.2,0.85,0.4);                                                                                                                   
leg->AddEntry(true_sbnd, "true_sbnd","l");
leg->AddEntry(VALOR_sbnd, "VALOR_sbnd","l");
leg->AddEntry(ratio_sbnd, "ratio_sbnd","l");
leg->SetFillStyle(0);                                                                                                                                            
leg->SetLineWidth(0);                                                                                                                                            
leg->Draw("same");  


}



















