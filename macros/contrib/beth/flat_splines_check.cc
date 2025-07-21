#include "TObjArray.h"
#include "TSpline.h"
#include <iostream>

void flat_splines_check(
		std::string sample,
		std::string param,
		std::string input_directory,
		std::string output_tag = ""
		){

    // spline locataion
    std::string spline_loc  = input_directory;
    std::string spline_name = "valor_splines_"+sample+"_"+param+"_BNB_FHC_sbn_nd.root";
    std::string modelist_name = "valor_splines_"+sample+"_"+param+"_BNB_FHC_sbn_nd_modelist.root";

    TFile * f = new TFile((spline_loc+spline_name).c_str(),"read");
    if (!f || f->IsZombie()) {
        std::cerr << "Error: Cannot open input file: " <<(spline_loc+spline_name).c_str() << std::endl;
        return;
    }

    //TFile * fout = new TFile(("flat_splines_"+sample+"_"+param+output_tag+".txt").c_str(),"recreate");

    TFile * fmode = new TFile((input_directory+modelist_name).c_str(),"read");
    if (!fmode || fmode->IsZombie()) {
        std::cerr << "Error: Cannot open input file: " << modelist_name << std::endl;
        return;
    }

    //TObjArray *dir = (TObjArray*)f->Get(("spl_"+mode+"_"+param).c_str()); 

    std::vector<std::string> flat_modes;
    std::vector<std::string> *modelist = nullptr;
    TTree *modes = (TTree*)fmode->Get("ModeList");
    if(std::string(param.c_str()).find("migration") != std::string::npos) {
	    modes->SetBranchAddress("horncurrent_FluxUnisim", &modelist);
    }else{
	    modes->SetBranchAddress(param.c_str(), &modelist);
    }
    int n = modes->GetEntries();
    for(int i=0; i<n; i++) {
      modes->GetEntry(i);
      for(int m=0; m<modelist[0].size(); m++){
	//std::cout << modelist[0][j] << std::endl;
	TObjArray *dir = (TObjArray*)f->Get(("spl_"+modelist[0][m]+"_"+param).c_str());
        if(!dir){
	  std::cout << "skipping dir = " << ("spl_"+modelist[0][m]+"_"+param).c_str() << std::endl;
          continue;
	} else std::cout << "looking at dir = " << ("spl_"+modelist[0][m]+"_"+param).c_str() << std::endl;	  
	//std::cout << "dir name = " << ("spl_"+modelist[0][m]+"_"+param).c_str() <<std::endl;
	//numu:
	int true_bins = 22;
	int reco_bins = 21;
	//nue:
	//int true_bins = 33;
	//int reco_bins = 12;
	bool is_flat = true; //do you want this to start as true or false??
	for(auto i = 0; i < true_bins; i++){
	    for(auto j = 0; j < reco_bins; j++){
		std::string str_i = std::to_string(i);
		std::string str_j = std::to_string(j);

		//std::cout << "spline name = " << ("spl_BNB_FHC_"+sample+"_"+modelist[0][m]+"_"+param+"_" + str_i + "_" + str_j).c_str() <<std::endl;

		TSpline3 *sp = (TSpline3*)(dir->FindObject(("spl_BNB_FHC_"+sample+"_"+modelist[0][m]+"_"+param+"_" + str_i + "_" + str_j).c_str()));
		
		std::vector<double> spline;
		for(int k = -3; k <= 3; k++){
		    double curr_value = sp->Eval(k);
		    /*if(std::abs(curr_value - 1.0) > 1e-8){
			    std::cout << "mode = " << modelist[0][m] << " bin = " << i << ", " << j << " k = " << k << std::setprecision(15) << " eval = " << curr_value << std::endl;
		    }*/
		    if(curr_value < 0) std::cout << "mode = " << modelist[0][m] << " bin = " << i << ", " << j << " k = " << k << std::setprecision(15) << " eval = " << curr_value << std::endl;
		    if(std::abs(curr_value - 1.0) > 1e-8){
			is_flat = false;
			break;
		    }
		}
		if(!is_flat) break;
	      }
	      if(!is_flat) break;
	    }
	if(is_flat) flat_modes.push_back(modelist[0][m]);
	//if all bins have all curr_value==1 then is_flat=true
	//add in loop over modes in modelist (change argument mode->modelist)
	//save txt file with list of modes that have all flat splines
	//name = flat_splines_sample_param.txt
      }
    }
    if(flat_modes.size()>0){
      ofstream of;
      of.open(("flat_splines_"+sample+"_"+param+output_tag+".txt").c_str(), ios::app);
      of << "==========================================" << std::endl;
      for(int i = 0; i<flat_modes.size(); i++){
	of << flat_modes[i] << std::endl;
      }
      of.close();
    }
    delete modelist;
}
