#include "TObjArray.h"
#include "TSpline.h"

void view_splines(){

    std::string interaction = "nueCCQE";
    std::string systematic  = "genie_ResDecayGamma_Genie";
    std::string analysis    = "nuelikeCChigh";

    // spline locataion
    std::string spline_loc  = "/sbnd/app/users/tham/VALOR_master/VALOR-SBN/data/sbn_nue_inclusive/responses/TEMP/xsec/intrinsic/nd/";
    std::string spline_name = "valor_splines_"+analysis+"_"+systematic+"_BNB_FHC_sbn_nd.root";

    // output location
    std::string output_loc = "/sbnd/app/users/tham/VALOR_master/VALOR-SBN/data/sbn_nue_inclusive/responses/TEMP/xsec";

    TFile * f = new TFile((spline_loc+spline_name).c_str(),"read");
    TObjArray *dir = (TObjArray*)f->Get(("spl_"+interaction+"_"+systematic).c_str()); 

    TCanvas * splines = new TCanvas("","",20,20,700,900); 
    TH2F * hsplines = (TH2F*) splines->DrawFrame(-3,0.5,3,1.5);  

    // mkdir where we'll store the splines
    std::string command = "mkdir -p "+output_loc+"/spline_"+interaction+"_"+systematic;
    system((command).c_str());

    int true_bins = 33;
    int reco_bins = 12;
    for(auto i = 0; i < true_bins; i++){
        for(auto j = 0; j < reco_bins; j++){
            std::string str_i = std::to_string(i);
            std::string str_j = std::to_string(j);

            TSpline3 *sp = (TSpline3*)(dir->FindObject(("spl_BNB_FHC_"+analysis+"_"+interaction+"_"+systematic+"_" + str_i + "_" + str_j).c_str()));
            splines->Draw();                                                                                                                                                                      
            hsplines->Draw();
            sp->Draw("same");
            splines->SaveAs(("spline_"+interaction+"_"+systematic+"/spl_BNB_FHC_"+analysis+"_"+interaction+"_"+systematic+"_"+str_i+"_"+str_j+".pdf").c_str());
            splines->Delete();

        }
    }
}
