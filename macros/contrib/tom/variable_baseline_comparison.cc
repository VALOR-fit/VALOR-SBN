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

void plot() {


// Read in DST's
TFile *SBND_dst   = new TFile("/sbnd/app/users/tham/VALOR_master/VALOR-DUNE-LBL/data/sbn/mock-data-challenge/version4/sbnd/mc/valor_sbncode_fhc_numuccinc_disappearance_nd_minidst_mc.root","read");
TFile *UB_dst     = new TFile("/sbnd/app/users/tham/VALOR/VALOR-DUNE-LBL/data/sbn/variable_baseline_test/uboone/mc/valor_sbncode_fhc_numuccinc_disappearance_ub_minidst_mc.root","read");
TFile *ICARUS_dst = new TFile("/sbnd/app/users/tham/VALOR/VALOR-DUNE-LBL/data/sbn/variable_baseline_test/icarus/mc/valor_sbncode_fhc_numuccinc_disappearance_fd_minidst_mc.root","read");
														
TTree *sbnd_mini_dst        = (TTree*) SBND_dst->Get("valor_sbncode_mini_dst");
TTree *ub_mini_dst          = (TTree*) UB_dst->Get("valor_sbncode_mini_dst");
TTree *icarus_mini_dst      = (TTree*) ICARUS_dst->Get("valor_sbncode_mini_dst");

int init_pdg;
double baseline, enu_true, enu_reco; 

// get stuff from VALOR dst
sbnd_mini_dst->SetBranchAddress("init_pdg", &init_pdg);
sbnd_mini_dst->SetBranchAddress("baseline", &baseline);
sbnd_mini_dst->SetBranchAddress("enu_true", &enu_true);
sbnd_mini_dst->SetBranchAddress("enu_reco", &enu_reco);


ub_mini_dst->SetBranchAddress("init_pdg", &init_pdg);
ub_mini_dst->SetBranchAddress("baseline", &baseline);
ub_mini_dst->SetBranchAddress("enu_true", &enu_true);

icarus_mini_dst->SetBranchAddress("init_pdg", &init_pdg);
icarus_mini_dst->SetBranchAddress("baseline", &baseline);
icarus_mini_dst->SetBranchAddress("enu_true", &enu_true);

// define Osc parameters
double dmsq = 50;
double sinsqthetamumu = 0.01;
//double dmsq = 50;
//double sinsqthetamumu = 1E-2;
double sinsqthetamue  = 1E-3;
//double dmsq = 1; // good params numu
//double dmsq = 0.5; // good params numu
//double sinsqthetamumu = 8E-3; // good params 
//double sinsqthetamue  = 8E-3; // good params

/*
double dmsq = 10; // good params numu
double sinsqthetamumu = 1E-2; // good params 
double sinsqthetamue  = 1E-2; // good params
*/

int i_pdg  = 14;
int f_pdg = 14;

double max_energy 			   = 1.5; // GeV
double min_energy 			   = 0.3; // GeV

int nbins = 500;


// define histograms
TH1F *h_nEvents_true_sbnd       		   = new TH1F("h_true_baseline_sbnd","h_true_baseline_sbnd",nbins, min_energy, max_energy);
TH1F *h_nEvents_spline_sbnd       		 = new TH1F("h_nEvents_spline_sbnd","h_nEvents_spline_sbnd",nbins, min_energy, max_energy);
TH1F *h_nEvents_average_sbnd     			 = new TH1F("h_average_baseline_sbnd","h_average_baseline_sbnd",nbins, min_energy, max_energy);
TH1F *h_nEvents_average_test_sbnd      = new TH1F("h_nEvents_average_test_sbnd","h_nEvents_average_test_sbnd",nbins, min_energy, max_energy);
TH1F *h_nEvents_spline_sbnd_proper     = new TH1F("h_nEvents_spline_sbnd_proper","h_nEvents_spline_sbnd_proper",nbins, min_energy, max_energy);
TH1F *h_nEvents_dom_sbnd     			     = new TH1F("h_VALOR_baseline_sbnd","h_VALOR_baseline_sbnd",nbins, min_energy, max_energy);

TH1F *h_nEvents_true_ub           		 = new TH1F("h_true_baseline_ub","h_true_baseline_ub",nbins, min_energy,max_energy);
TH1F *h_nEvents_spline_ub         		 = new TH1F("h_unosc_events_rate_ub","h_unosc_event_rate_ub",nbins, min_energy, max_energy);
TH1F *h_nEvents_average_ub        		 = new TH1F("h_average_baseline_ub","h_average_baseline_ub",nbins, min_energy, max_energy);
TH1F *h_nEvents_spline_ub_proper       = new TH1F("h_nEvents_spline_ub_proper","h_nEvents_spline_ub_proper",nbins, min_energy, max_energy);

TH1F *h_nEvents_true_icarus       		 = new TH1F("h_true_baseline_icarus","h_true_baseline_icarus",nbins, min_energy,max_energy);
TH1F *h_nEvents_spline_icarus     		 = new TH1F("h_unosc_events_rate_icarus","h_unosc_event_rate_icarus",nbins, min_energy,max_energy);
 TH1F *h_nEvents_average_icarus     		 = new TH1F("h_average_baseline_icarus","h_average_baseline_icarus",nbins, min_energy, max_energy);
TH1F *h_nEvents_spline_icarus_proper   = new TH1F("h_nEvents_spline_icarus_proper","h_nEvents_spline_icarus_proper",nbins, min_energy, max_energy);



// get the hacked splines (copy from GenericSingleSampleFitModel.cxx)
static double SBNDBaselineX[4] = {0.060 , 0.064  , 106 , 0.114};
static double SBNDBaselineY[4] = {256, 2388, 3229, 4.0};
TSpline3 *spl_sbnd = new TSpline3("SBND Baseline",SBNDBaselineX,SBNDBaselineY,4);
//static TSpline3 SBNDBaseline_ts("SBND Baseline",SBNDBaselineX,SBNDBaselineY,4);
//static const util::Interpolator SBNDBaseline(SBNDBaseline_ts,ROOT::Math::Interpolation::kLINEAR);

static double MicroBooNEBaselineX[4] = {0.415, 0.422 , 0.462, 0.472};
static double MicroBooNEBaselineY[4] = {386, 1567, 3188, 79};
TSpline3 *spl_ub = new TSpline3("MicroBooNE Baseline",MicroBooNEBaselineX,MicroBooNEBaselineY,4);

static double ICARUSBaselineX[4] = {0.540,0.556,0.586,0.602};
static double ICARUSBaselineY[4] = {122,875,1629,140};
TSpline3 *spl_icarus = new TSpline3("ICARUS Baseline",ICARUSBaselineX,ICARUSBaselineY,4);

//std::cout << "event rate at baseline = " << spl_sbnd->Eval(0.100) << std::endl;

// for the hacked splines
int NSplineEvalPoints      = 40;
double event_rate_sum      = 0.;
double sbnd_max_baseline   = 0.114;
double sbnd_min_baseline   = 0.06;
double ub_max_baseline     = 0.472;
double ub_min_baseline     = 0.415;
double icarus_max_baseline = 0.602;
double icarus_min_baseline = 0.540;

double baseline_interval_sbnd   = (sbnd_max_baseline-sbnd_min_baseline)/(NSplineEvalPoints-1);
double baseline_interval_ub     = (ub_max_baseline-ub_min_baseline)/(NSplineEvalPoints-1);
double baseline_interval_icarus = (icarus_max_baseline-icarus_min_baseline)/(NSplineEvalPoints-1);
double p_numu_numu       = 0;



// Get the proper spline
TFile *SBND_spline_proper 	= new TFile("/sbnd/app/users/tham/VALOR/baseline_comparison/SBND_spline_proper.root", "read");
TFile *UB_spline_proper 		= new TFile("/sbnd/app/users/tham/VALOR/baseline_comparison/UB_spline_proper.root", "read");
TFile *ICARUS_spline_proper = new TFile("/sbnd/app/users/tham/VALOR/baseline_comparison/ICARUS_spline_proper.root", "read");

// for proper splines
double sbnd_max_baseline_proper 	= 0.;
double sbnd_min_baseline_proper 	= 0.;
double ub_max_baseline_proper 		= 0.;
double ub_min_baseline_proper 		= 0.;
double icarus_max_baseline_proper = 0.;
double icarus_min_baseline_proper = 0.;

double baseline_spline_proper;

// access the splines in the files and get the min/max baseline
TIter next_sbnd(SBND_spline_proper->GetListOfKeys());
TKey *key_sbnd;
while ((key_sbnd = (TKey*)next_sbnd())){
TClass *cl = gROOT->GetClass(key_sbnd->GetClassName());
if (!cl->InheritsFrom("TSpline3")) continue;
TSpline3 *spl = (TSpline3*)key_sbnd->ReadObj();
sbnd_max_baseline_proper = spl->GetXmax();
sbnd_min_baseline_proper = spl->GetXmin();
}

TIter next_ub(UB_spline_proper->GetListOfKeys());
TKey *key_ub;
while ((key_ub = (TKey*)next_ub())){
TClass *cl = gROOT->GetClass(key_ub->GetClassName());
if (!cl->InheritsFrom("TSpline3")) continue;
TSpline3 *spl = (TSpline3*)key_ub->ReadObj();
ub_max_baseline_proper = spl->GetXmax();
ub_min_baseline_proper = spl->GetXmin();
}

TIter next_icarus(ICARUS_spline_proper->GetListOfKeys());
TKey *key_icarus;
while ((key_icarus = (TKey*)next_icarus())){
TClass *cl = gROOT->GetClass(key_icarus->GetClassName());
if (!cl->InheritsFrom("TSpline3")) continue;
TSpline3 *spl = (TSpline3*)key_icarus->ReadObj();
icarus_max_baseline_proper = spl->GetXmax();
icarus_min_baseline_proper = spl->GetXmin();
}

double baseline_interval_sbnd_proper    = (sbnd_max_baseline_proper-sbnd_min_baseline_proper)/(NSplineEvalPoints-1);
double baseline_interval_ub_proper      = (ub_max_baseline_proper-ub_min_baseline_proper)/(NSplineEvalPoints-1);
double baseline_interval_icarus_proper  = (icarus_max_baseline_proper-icarus_min_baseline_proper)/(NSplineEvalPoints-1);
double p_numu_numu_proper       = 0;

// get the event rate sum for proper spline - current method for doing this with hacked in the loop is inefficient since it is a constant 
// was breaking when trying that method with proper splines.. i think we were running out of memory 
std::vector<double> event_rate_at_baseline_proper_vec_sbnd; // store the event rate for each of the baseline points to access later 
double event_rate_at_baseline_proper = 0;
double event_rate_sum_proper_sbnd = 0;

// loop over the baseline intrevals and then all the splines from the file
for (int ibl = 0; ibl < NSplineEvalPoints; ibl++) {
	baseline_spline_proper = sbnd_min_baseline_proper + (ibl*baseline_interval_sbnd_proper);
	event_rate_at_baseline_proper = 0;

	next_sbnd.Reset(); // reset the iterator
	while ((key_sbnd = (TKey*)next_sbnd())){
		TClass *cl = gROOT->GetClass(key_sbnd->GetClassName());
		if (!cl->InheritsFrom("TSpline3")) continue;
		TSpline3 *spl = (TSpline3*)key_sbnd->ReadObj();
		event_rate_at_baseline_proper += spl->Eval(baseline_spline_proper);
		sbnd_max_baseline_proper = spl->GetXmax();
		sbnd_min_baseline_proper = spl->GetXmin();
	}
	event_rate_at_baseline_proper_vec_sbnd.push_back(event_rate_at_baseline_proper);
	event_rate_sum_proper_sbnd += event_rate_at_baseline_proper;
}

std::vector<double> event_rate_at_baseline_proper_vec_ub; // store the event rate for each of the baseline points to access later 
double event_rate_sum_proper_ub = 0;

// loop over the baseline intrevals and then all the splines from the file
for (int ibl = 0; ibl < NSplineEvalPoints; ibl++) {
	baseline_spline_proper = ub_min_baseline_proper + (ibl*baseline_interval_ub_proper);
	event_rate_at_baseline_proper = 0;

	next_ub.Reset(); // reset the iterator
	while ((key_ub = (TKey*)next_ub())){
		TClass *cl = gROOT->GetClass(key_ub->GetClassName());
		if (!cl->InheritsFrom("TSpline3")) continue;
		TSpline3 *spl = (TSpline3*)key_ub->ReadObj();
		event_rate_at_baseline_proper += spl->Eval(baseline_spline_proper);
		ub_max_baseline_proper = spl->GetXmax();
		ub_min_baseline_proper = spl->GetXmin();
	}
	event_rate_at_baseline_proper_vec_ub.push_back(event_rate_at_baseline_proper);
	event_rate_sum_proper_ub += event_rate_at_baseline_proper;
}


std::vector<double> event_rate_at_baseline_proper_vec_icarus; // store the event rate for each of the baseline points to access later 
double event_rate_sum_proper_icarus = 0;

// loop over the baseline intrevals and then all the splines from the file
for (int ibl = 0; ibl < NSplineEvalPoints; ibl++) {
	baseline_spline_proper = icarus_min_baseline_proper + (ibl*baseline_interval_icarus_proper);
	event_rate_at_baseline_proper = 0;

	next_icarus.Reset(); // reset the iterator
	while ((key_icarus = (TKey*)next_icarus())){
		TClass *cl = gROOT->GetClass(key_icarus->GetClassName());
		if (!cl->InheritsFrom("TSpline3")) continue;
		TSpline3 *spl = (TSpline3*)key_icarus->ReadObj();
		event_rate_at_baseline_proper += spl->Eval(baseline_spline_proper);
		icarus_max_baseline_proper = spl->GetXmax();
		icarus_min_baseline_proper = spl->GetXmin();
	}
	event_rate_at_baseline_proper_vec_icarus.push_back(event_rate_at_baseline_proper);
	event_rate_sum_proper_icarus += event_rate_at_baseline_proper;
}

typedef std::pair <double, double> double_pair;
std::vector<double_pair> pair_true_sbnd; 		// vectors to hold enu_true and osc. prob 
std::vector<double_pair> pair_spline_sbnd;
std::vector<double_pair> pair_spline_sbnd_proper;
std::vector<double_pair> pair_average_sbnd;
std::vector<double_pair> pair_true_ub; 		// vectors to hold enu_true and osc. prob 
std::vector<double_pair> pair_spline_ub;
std::vector<double_pair> pair_spline_ub_proper;
std::vector<double_pair> pair_average_ub;
std::vector<double_pair> pair_true_icarus; 		// vectors to hold enu_true and osc. prob 
std::vector<double_pair> pair_spline_icarus;
std::vector<double_pair> pair_average_icarus;
std::vector<double_pair> pair_spline_icarus_proper;


std::vector<double_pair> pair_sbnd_dom; 		// vectors to hold enu_true and osc. prob 

std::ofstream variable_file;
variable_file.open ("variable_file.txt");


////////////////////////////////////////////////////////////////////////////////////////////////////
// SBND
////////////////////////////////////////////////////////////////////////////////////////////////////
int nEvents_sbnd = sbnd_mini_dst->GetEntries();
// loop over all events
for(int i = 0; i < nEvents_sbnd; ++i){
//for(int i = 0; i < 2; ++i){
	sbnd_mini_dst->GetEntry(i);
	// Find only numu
	if(init_pdg == 14){
		// Get true osc. prob
		double lOverE = baseline/enu_true;
		// std::cout << lOverE << std::endl;
		double osc_prob_true = util::Calculate2FSterileOscMuE(i_pdg, f_pdg, lOverE, sinsqthetamue, sinsqthetamumu, dmsq);
		pair_true_sbnd.push_back(std::make_pair(enu_true, osc_prob_true));



		// get spline osc. prob
	  p_numu_numu = 0;
	  event_rate_sum = 0;
		for (int ibl = 0; ibl < NSplineEvalPoints; ibl++) {
			double baseline_spline = sbnd_min_baseline + (ibl*baseline_interval_sbnd);
  		double event_rate_at_baseline = spl_sbnd->Eval(baseline_spline);
			//std::cout << baseline_spline << "			" << event_rate_at_baseline << std::endl;
			event_rate_sum+=event_rate_at_baseline;
			double lOverE_spline = baseline_spline / enu_true;
			//std::cout << lOverE_spline << std::endl;
			p_numu_numu += event_rate_at_baseline * util::Calculate2FSterileOscMuE(i_pdg, f_pdg, lOverE_spline, sinsqthetamue, sinsqthetamumu, dmsq);
			
		}
		//std::cout << "hack spline = " << event_rate_sum << std::endl;;
		double osc_prob_spline = p_numu_numu/event_rate_sum;
		pair_spline_sbnd.push_back(std::make_pair(enu_true, osc_prob_spline));
		//std::cout << osc_prob_spline << std::endl;		

		// using average baseline
		double baseline_average = 0.08821; 
		double osc_prob_average = util::Calculate2FSterileOscMuE(i_pdg, f_pdg, baseline_average/enu_true, sinsqthetamue, sinsqthetamumu, dmsq);
		pair_average_sbnd.push_back(std::make_pair(enu_true, osc_prob_average));
		//std::cout << osc_prob_average << std::endl;

		// using proper splines
		p_numu_numu_proper = 0;
		for (int ibl = 0; ibl < NSplineEvalPoints; ibl++) {
			baseline_spline_proper = sbnd_min_baseline_proper + (ibl*baseline_interval_sbnd_proper);
 		
			//std::cout << event_rate_at_baseline_proper << std::endl;
			double lOverE_spline_proper = baseline_spline_proper/enu_true;
		  //	std::cout << lOverE_spline_proper << std::endl;
			p_numu_numu_proper += event_rate_at_baseline_proper_vec_sbnd.at(ibl) * util::Calculate2FSterileOscMuE(i_pdg, f_pdg, lOverE_spline_proper, sinsqthetamue, sinsqthetamumu, dmsq);
		}
		//std::cout << "test = " << event_rate_sum_proper_sbnd << std::endl;
		double osc_prob_spline_proper = p_numu_numu_proper/event_rate_sum_proper_sbnd;
		pair_spline_sbnd_proper.push_back(std::make_pair(enu_true, osc_prob_spline_proper));
		//std::cout << osc_prob_spline_proper << std::endl;	

		// Dom's method
		double lOverE_dom = baseline/enu_true;
	  double sinsqdm = util::Calculate2FSterileSinSqDM(lOverE_dom,dmsq);
		//double p_numu_numu_dom = util::Calculate2FSterileOscMuE(i_pdg, f_pdg, sinsqthetamue, sinsqthetamumu, sinsqdm);
		pair_sbnd_dom.push_back(std::make_pair(enu_true, sinsqdm));
		//pair_sbnd_dom.push_back(std::make_pair(enu_true, p_numu_numu_dom));
		//std::cout << "p_numu_numu_dom = " << p_numu_numu_dom << std::endl;
		//variable_file << p_numu_numu_dom << "\n";

	}
}

variable_file.close();
// order vector in ascending energy
std::cout << std::endl;
std::sort(pair_true_sbnd.begin(), pair_true_sbnd.end());
std::sort(pair_spline_sbnd.begin(), pair_spline_sbnd.end());


//bin increments
double bin_inc = (max_energy-min_energy)/(nbins-1);

// Get the avergae probability for each bin (truth)
double sum_true_sbnd = 0;
int N_true_sbnd = 0;
std::vector<double> p_average_true_sbnd;

// loop over bin increments
for(int i = 0; i < nbins; i++){
	double bin_min_energy = min_energy + (i*bin_inc);
	double bin_max_energy = min_energy + ((i+1)*bin_inc);
	
	// loop over vector
	for (auto iter = pair_true_sbnd.begin(); iter != pair_true_sbnd.end(); ++iter){
		//std::cout << iter->first << "     " << iter->second <<  std::endl;

		// get conditions for the bin
		if(iter->first < bin_max_energy && iter->first >= bin_min_energy){
			//std::cout << "i = " << i << "			"  << iter->first << "				" << iter->second << std::endl;
			sum_true_sbnd += iter->second;
			++N_true_sbnd;
		}
	}
	//std::cout << "average = " << sum/N1 << std::endl;
	p_average_true_sbnd.push_back(sum_true_sbnd/N_true_sbnd);
	N_true_sbnd = 0;
	sum_true_sbnd = 0;

}

// fill histogram with vector of averaged osc. prob
int i = 0;
for (auto iter = (p_average_true_sbnd.begin()); iter != p_average_true_sbnd.end(); ++iter){
	i++;
  //std::cout << j << "		" << *iter << std::endl;
	
	h_nEvents_true_sbnd->SetBinContent(i+1,*iter);
}



// Get the avergae probability for each bin (spline)
double sum_spline_sbnd = 0;
int N_spline_sbnd = 0;
std::vector<double> p_average_spline_sbnd;
// increase in bin increments
for(double i = min_energy; i < max_energy; (i+=bin_inc)){
	
	// loop over vector
	for (auto iter = pair_spline_sbnd.begin(); iter != pair_spline_sbnd.end(); ++iter){
	//std::cout << iter->first << "     " << iter->second <<  std::endl;
	
		if(iter->first < (i+bin_inc) && iter->first >= i){
			//std::cout << "i = " << i << "			"  << iter->first << "				" << iter->second << std::endl;
			sum_spline_sbnd += iter->second;
			++N_spline_sbnd;
		}
	}
	//std::cout << "average = " << sum/N1 << std::endl;
	p_average_spline_sbnd.push_back(sum_spline_sbnd/N_spline_sbnd);
	N_spline_sbnd = 0;
	sum_spline_sbnd = 0;

}

int ii = 0;
for (auto iter = (p_average_spline_sbnd.begin()); iter != p_average_spline_sbnd.end(); ++iter){
	ii++;
	//std::cout << k << "		" << *iter << std::endl;
	
	h_nEvents_spline_sbnd->SetBinContent(ii+1,*iter);
}


// Get the avergae probability for each bin (average)
double sum_average_sbnd = 0;
int N_average_sbnd = 0;
std::vector<double> p_average_average_sbnd;
// increase in bin increments
for(double i = min_energy; i < max_energy; (i+=bin_inc)){
	
	// loop over vector
	for (auto iter = pair_average_sbnd.begin(); iter != pair_average_sbnd.end(); ++iter){
	//std::cout << iter->first << "     " << iter->second <<  std::endl;
	
		if(iter->first < (i+bin_inc) && iter->first >= i){
			//std::cout << "i = " << i << "			"  << iter->first << "				" << iter->second << std::endl;
			sum_average_sbnd += iter->second;
			++N_average_sbnd;
		}
	}
	//std::cout << "average = " << sum/N1 << std::endl;
	p_average_average_sbnd.push_back(sum_average_sbnd/N_average_sbnd);
	N_average_sbnd = 0;
	sum_average_sbnd = 0;

}


int iii = 0;
for (auto iter = (p_average_average_sbnd.begin()); iter != p_average_average_sbnd.end(); ++iter){
	iii++;
	//std::cout << ii << "		" << *iter << std::endl;
	
	h_nEvents_average_sbnd->SetBinContent(iii+1,*iter);
}



// Get the avergae probability for each bin (spline proper)
double sum_spline_sbnd_proper = 0;
int N_spline_sbnd_proper = 0;
std::vector<double> p_average_spline_sbnd_proper;
// increase in bin increments
for(double i = min_energy; i < max_energy; (i+=bin_inc)){
	
	// loop over vector
	for (auto iter = pair_spline_sbnd_proper.begin(); iter != pair_spline_sbnd_proper.end(); ++iter){
	//std::cout << iter->first << "     " << iter->second <<  std::endl;
	
		if(iter->first < (i+bin_inc) && iter->first >= i){
			//std::cout << "i = " << i << "			"  << iter->first << "				" << iter->second << std::endl;
			sum_spline_sbnd_proper += iter->second;
			++N_spline_sbnd_proper;
		}
	}
	//std::cout << "average = " << sum/N1 << std::endl;
	p_average_spline_sbnd_proper.push_back(sum_spline_sbnd_proper/N_spline_sbnd_proper);
	N_spline_sbnd_proper = 0;
	sum_spline_sbnd_proper = 0;

}

int iiii = 0;
for (auto iter = (p_average_spline_sbnd_proper.begin()); iter != p_average_spline_sbnd_proper.end(); ++iter){
	iiii++;
	//std::cout << k << "		" << *iter << std::endl;
	
	h_nEvents_spline_sbnd_proper->SetBinContent(iiii+1,*iter);
}




// Get the avergae probability for each bin (dom's method)
double sum_sbnd_dom = 0;
int N_sbnd_dom = 0;
std::vector<double> p_average_sbnd_dom;
// increase in bin increments
for(double i = min_energy; i < max_energy; (i+=bin_inc)){
	
	// loop over vector
	for (auto iter = pair_sbnd_dom.begin(); iter != pair_sbnd_dom.end(); ++iter){
        //	std::cout << iter->first << "     " << iter->second <<  std::endl;
		
                double p_numu_numu_dom = util::Calculate2FSterileOscMuE(i_pdg, f_pdg, sinsqthetamue, sinsqthetamumu, iter->second);
		if(iter->first < (i+bin_inc) && iter->first >= i){
                        //std::cout << "i = " << i << "			"  << iter->first << "				" << iter->second << std::endl;
		        sum_sbnd_dom += p_numu_numu_dom; //iter->second;
			++N_sbnd_dom;
		}
	}
	//std::cout << "average = " << sum/N1 << std::endl;
	p_average_sbnd_dom.push_back(sum_sbnd_dom/N_sbnd_dom);
	N_sbnd_dom = 0;
        sum_sbnd_dom = 0;

}

int iiiii = 0;
for (auto iter = (p_average_sbnd_dom.begin()); iter != p_average_sbnd_dom.end(); ++iter){
	iiiii++;
	//std::cout << k << "		" << *iter << std::endl;
	
	h_nEvents_dom_sbnd->SetBinContent(iiiii+1,*iter);
}






////////////////////////////////////////////////////////////////////////////////////////////////////
// UB
////////////////////////////////////////////////////////////////////////////////////////////////////

int nEvents_ub = ub_mini_dst->GetEntries();
// loop over all events
for(int i = 0; i < nEvents_ub; ++i){
	ub_mini_dst->GetEntry(i);
	// Find only numu
	if(init_pdg == 14){
		// L/E
  	double lOverE = baseline/enu_true;
		double osc_prob_true = util::Calculate2FSterileOscMuE(i_pdg, f_pdg, lOverE, sinsqthetamue, sinsqthetamumu, dmsq);
		pair_true_ub.push_back(std::make_pair(enu_true, osc_prob_true));


		// get spline osc. prob
	  p_numu_numu = 0;
	  event_rate_sum = 0;
		for (int ibl = 0; ibl < NSplineEvalPoints; ibl++) {
			double baseline_spline = ub_min_baseline + (ibl*baseline_interval_ub);
  		double event_rate_at_baseline = spl_ub->Eval(baseline_spline);
			event_rate_sum+=event_rate_at_baseline;
			double lOverE_spline = baseline_spline / enu_true;
			p_numu_numu += event_rate_at_baseline * util::Calculate2FSterileOscMuE(i_pdg, f_pdg, lOverE_spline, sinsqthetamue, sinsqthetamumu, dmsq);
			
		}

		double osc_prob_spline = p_numu_numu/event_rate_sum;
		pair_spline_ub.push_back(std::make_pair(enu_true, osc_prob_spline));
	
		// using average baseline
		double baseline_average = 0.4661; 
		double osc_prob_average = util::Calculate2FSterileOscMuE(i_pdg, f_pdg, baseline_average/enu_true, sinsqthetamue, sinsqthetamumu, dmsq);
		pair_average_ub.push_back(std::make_pair(enu_true, osc_prob_average));

		// using proper splines
		p_numu_numu_proper = 0;
		for (int ibl = 0; ibl < NSplineEvalPoints; ibl++) {
			baseline_spline_proper = ub_min_baseline_proper + (ibl*baseline_interval_ub_proper);
 		
			double lOverE_spline_proper = baseline_spline_proper/enu_true;
			p_numu_numu_proper += event_rate_at_baseline_proper_vec_ub.at(ibl) * util::Calculate2FSterileOscMuE(i_pdg, f_pdg, lOverE_spline_proper, sinsqthetamue, sinsqthetamumu, dmsq);
		}
		double osc_prob_spline_proper = p_numu_numu_proper/event_rate_sum_proper_ub;
		pair_spline_ub_proper.push_back(std::make_pair(enu_true, osc_prob_spline_proper));



	}
}


// Get the avergae probability for each bin (truth) ub
double sum_true_ub = 0;
int N_true_ub = 0;
std::vector<double> p_average_true_ub;

// loop over bin increments
for(int i = 0; i < nbins; i++){
	double bin_min_energy = min_energy + (i*bin_inc);
	double bin_max_energy = min_energy + ((i+1)*bin_inc);
	
	// loop over vector
	for (auto iter = pair_true_ub.begin(); iter != pair_true_ub.end(); ++iter){
		//std::cout << iter->first << "     " << iter->second <<  std::endl;

		// get conditions for the bin
		if(iter->first < bin_max_energy && iter->first >= bin_min_energy){
			//std::cout << "i = " << i << "			"  << iter->first << "				" << iter->second << std::endl;
			sum_true_ub += iter->second;
			++N_true_ub;
		}
	}
	//std::cout << "average = " << sum/N1 << std::endl;
	p_average_true_ub.push_back(sum_true_ub/N_true_ub);
	N_true_ub	= 0;
	sum_true_ub = 0;

}

// fill histogram with vector of averaged osc. prob
int j = 0;
for (auto iter = (p_average_true_ub.begin()); iter != p_average_true_ub.end(); ++iter){
	j++;
  	
	h_nEvents_true_ub->SetBinContent(j+1,*iter);
}


// Get the avergae probability for each bin (spline) ub
double sum_spline_ub = 0;
int N_spline_ub = 0;
std::vector<double> p_average_spline_ub;
// increase in bin increments
for(double i = min_energy; i < max_energy; (i+=bin_inc)){
	
	// loop over vector
	for (auto iter = pair_spline_ub.begin(); iter != pair_spline_ub.end(); ++iter){
	
		if(iter->first < (i+bin_inc) && iter->first >= i){

			sum_spline_ub += iter->second;
			++N_spline_ub;
		}
	}
	
	p_average_spline_ub.push_back(sum_spline_ub/N_spline_ub);
	N_spline_ub = 0;
	sum_spline_ub = 0;

}

int jj = 0;
for (auto iter = (p_average_spline_ub.begin()); iter != p_average_spline_ub.end(); ++iter){
	jj++;
	h_nEvents_spline_ub->SetBinContent(jj+1,*iter);
}

// Get the avergae probability for each bin (average) ub
double sum_average_ub = 0;
int N_average_ub = 0;
std::vector<double> p_average_average_ub;
// increase in bin increments
for(double i = min_energy; i < max_energy; (i+=bin_inc)){
	
	// loop over vector
	for (auto iter = pair_average_ub.begin(); iter != pair_average_ub.end(); ++iter){
	
		if(iter->first < (i+bin_inc) && iter->first >= i){

			sum_average_ub += iter->second;
			++N_average_ub;
		}
	}
	
	p_average_average_ub.push_back(sum_average_ub/N_average_ub);
	N_average_ub = 0;
	sum_average_ub = 0;

}

int jjj = 0;
for (auto iter = (p_average_average_ub.begin()); iter != p_average_average_ub.end(); ++iter){
	jjj++;
	h_nEvents_average_ub->SetBinContent(jjj+1,*iter);
}

// Get the avergae probability for each bin (spline proper)
double sum_spline_ub_proper = 0;
int N_spline_ub_proper = 0;
std::vector<double> p_average_spline_ub_proper;
// increase in bin increments
for(double i = min_energy; i < max_energy; (i+=bin_inc)){
	
	// loop over vector
	for (auto iter = pair_spline_ub_proper.begin(); iter != pair_spline_ub_proper.end(); ++iter){
	
		if(iter->first < (i+bin_inc) && iter->first >= i){
			sum_spline_ub_proper += iter->second;
			++N_spline_ub_proper;
		}
	}
	p_average_spline_ub_proper.push_back(sum_spline_ub_proper/N_spline_ub_proper);
	N_spline_ub_proper = 0;
	sum_spline_ub_proper = 0;

}

int jjjj = 0;
for (auto iter = (p_average_spline_ub_proper.begin()); iter != p_average_spline_ub_proper.end(); ++iter){
	jjjj++;
	
	h_nEvents_spline_ub_proper->SetBinContent(jjjj+1,*iter);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
// icarus
////////////////////////////////////////////////////////////////////////////////////////////////////

int nEvents_icarus = icarus_mini_dst->GetEntries();
// loop over all events
for(int i = 0; i < nEvents_icarus; ++i){
	icarus_mini_dst->GetEntry(i);
	// Find only numu
	if(init_pdg == 14){
		// L/E
		double lOverE = baseline/enu_true;
		double osc_prob_true = util::Calculate2FSterileOscMuE(i_pdg, f_pdg, lOverE, sinsqthetamue, sinsqthetamumu, dmsq);
		
		h_nEvents_true_icarus->Fill(osc_prob_true);
		pair_true_icarus.push_back(std::make_pair(enu_true, osc_prob_true));


		// get spline osc. prob
	  p_numu_numu = 0;
	  event_rate_sum = 0;
		for (int ibl = 0; ibl < NSplineEvalPoints; ibl++) {
			double baseline_spline = icarus_min_baseline + (ibl*baseline_interval_icarus);
  		double event_rate_at_baseline = spl_icarus->Eval(baseline_spline);
			event_rate_sum+=event_rate_at_baseline;
			double lOverE_spline = baseline_spline / enu_true;
			p_numu_numu += event_rate_at_baseline * util::Calculate2FSterileOscMuE(i_pdg, f_pdg, lOverE_spline, sinsqthetamue, sinsqthetamumu, dmsq);
			
		}

		double osc_prob_spline = p_numu_numu/event_rate_sum;
		pair_spline_icarus.push_back(std::make_pair(enu_true, osc_prob_spline));

		// using average baseline
		double baseline_average = 0.5735; 
		double osc_prob_average = util::Calculate2FSterileOscMuE(i_pdg, f_pdg, baseline_average/enu_true, sinsqthetamue, sinsqthetamumu, dmsq);
		pair_average_icarus.push_back(std::make_pair(enu_true, osc_prob_average));

		// using proper splines
		p_numu_numu_proper = 0;
		for (int ibl = 0; ibl < NSplineEvalPoints; ibl++) {
			baseline_spline_proper = icarus_min_baseline_proper + (ibl*baseline_interval_icarus_proper);
 		
			double lOverE_spline_proper = baseline_spline_proper/enu_true;
			p_numu_numu_proper += event_rate_at_baseline_proper_vec_icarus.at(ibl) * util::Calculate2FSterileOscMuE(i_pdg, f_pdg, lOverE_spline_proper, sinsqthetamue, sinsqthetamumu, dmsq);
		}
		double osc_prob_spline_proper = p_numu_numu_proper/event_rate_sum_proper_icarus;
		pair_spline_icarus_proper.push_back(std::make_pair(enu_true, osc_prob_spline_proper));


	}
}


// Get the avergae probability for each bin (truth) icarus
double sum_true_icarus = 0;
int N_true_icarus = 0;
std::vector<double> p_average_true_icarus;

// loop over bin increments
for(int i = 0; i < nbins; i++){
	double bin_min_energy = min_energy + (i*bin_inc);
	double bin_max_energy = min_energy + ((i+1)*bin_inc);
	
	// loop over vector
	for (auto iter = pair_true_icarus.begin(); iter != pair_true_icarus.end(); ++iter){
		//std::cout << iter->first << "     " << iter->second <<  std::endl;

		// get conditions for the bin
		if(iter->first < bin_max_energy && iter->first >= bin_min_energy){
			//std::cout << "i = " << i << "			"  << iter->first << "				" << iter->second << std::endl;
			sum_true_icarus += iter->second;
			++N_true_icarus;
		}
	}
	
	p_average_true_icarus.push_back(sum_true_icarus/N_true_icarus);
	N_true_icarus	= 0;
	sum_true_icarus = 0;

}

// fill histogram with vector of averaged osc. prob
int k = 0;
for (auto iter = (p_average_true_icarus.begin()); iter != p_average_true_icarus.end(); ++iter){
	k++;
  	
	h_nEvents_true_icarus->SetBinContent(k+1,*iter);
}


// Get the avergae probability for each bin (spline) icarus
double sum_spline_icarus = 0;
int N_spline_icarus = 0;
std::vector<double> p_average_spline_icarus;
// increase in bin increments
for(double i = min_energy; i < max_energy; (i+=bin_inc)){
	
	// loop over vector
	for (auto iter = pair_spline_icarus.begin(); iter != pair_spline_icarus.end(); ++iter){
	
		if(iter->first < (i+bin_inc) && iter->first >= i){

			sum_spline_icarus += iter->second;
			++N_spline_icarus;
		}
	}
	
	p_average_spline_icarus.push_back(sum_spline_icarus/N_spline_icarus);
	N_spline_icarus = 0;
	sum_spline_icarus = 0;

}

int kk = 0;
for (auto iter = (p_average_spline_icarus.begin()); iter != p_average_spline_icarus.end(); ++iter){
	kk++;
	h_nEvents_spline_icarus->SetBinContent(kk+1,*iter);
}


// Get the avergae probability for each bin (average) icarus
double sum_average_icarus = 0;
int N_average_icarus = 0;
std::vector<double> p_average_average_icarus;
// increase in bin increments
for(double i = min_energy; i < max_energy; (i+=bin_inc)){
	
	// loop over vector
	for (auto iter = pair_average_icarus.begin(); iter != pair_average_icarus.end(); ++iter){
	
		if(iter->first < (i+bin_inc) && iter->first >= i){

			sum_average_icarus += iter->second;
			++N_average_icarus;
		}
	}
	
	p_average_average_icarus.push_back(sum_average_icarus/N_average_icarus);
	N_average_icarus = 0;
	sum_average_icarus = 0;

}

int kkk = 0;
for (auto iter = (p_average_average_icarus.begin()); iter != p_average_average_icarus.end(); ++iter){
	kkk++;
	h_nEvents_average_icarus->SetBinContent(kkk+1,*iter);
}

// Get the avergae probability for each bin (spline proper)
double sum_spline_icarus_proper = 0;
int N_spline_icarus_proper = 0;
std::vector<double> p_average_spline_icarus_proper;
// increase in bin increments
for(double i = min_energy; i < max_energy; (i+=bin_inc)){
	
	// loop over vector
	for (auto iter = pair_spline_icarus_proper.begin(); iter != pair_spline_icarus_proper.end(); ++iter){
	
		if(iter->first < (i+bin_inc) && iter->first >= i){
			sum_spline_icarus_proper += iter->second;
			++N_spline_icarus_proper;
		}
	}
	p_average_spline_icarus_proper.push_back(sum_spline_icarus_proper/N_spline_icarus_proper);
	N_spline_icarus_proper = 0;
	sum_spline_icarus_proper = 0;

}

int kkkk = 0;
for (auto iter = (p_average_spline_icarus_proper.begin()); iter != p_average_spline_icarus_proper.end(); ++iter){
	kkkk++;
	
	h_nEvents_spline_icarus_proper->SetBinContent(kkkk+1,*iter);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////

// averagae fixed baseline (bad) sbnd
double baseline_average_sbnd = 0.08755; //km
for(int i = 0; i < h_nEvents_average_sbnd->GetNbinsX(); i++){
	double E = h_nEvents_average_test_sbnd->GetXaxis()->GetBinCenter(i+1);
	double p = util::Calculate2FSterileOscMuE(i_pdg, f_pdg, baseline_average_sbnd/E, sinsqthetamue, sinsqthetamumu, dmsq);
	h_nEvents_average_test_sbnd->SetBinContent(i+1,p);
	}


/*
// averagae fixed baseline (bad) ub
double baseline_average_ub = 0.466; //km
for(int i = 0; i < h_nEvents_average_ub->GetNbinsX(); i++){
	double E = h_nEvents_average_ub->GetXaxis()->GetBinCenter(i+1);
	double p = util::Calculate2FSterileOscMuE(i_pdg, f_pdg, baseline_average_ub/E, sinsqthetamue, sinsqthetamumu, dmsq);
	h_nEvents_average_ub->SetBinContent(i+1,p);
	}


// averagae fixed baseline (bad) icarus
double baseline_average_icarus = 0.5735; //km
for(int i = 0; i < h_nEvents_average_icarus->GetNbinsX(); i++){
	double E = h_nEvents_average_icarus->GetXaxis()->GetBinCenter(i+1);
	double p = util::Calculate2FSterileOscMuE(i_pdg, f_pdg, baseline_average_icarus/E, sinsqthetamue, sinsqthetamumu, dmsq);
	h_nEvents_average_icarus->SetBinContent(i+1,p);
	}

*/


// sbnd
TCanvas *c1 = new TCanvas();
c1->cd(1);
TPad *pad1 = new TPad("pad1","This is pad1",0.04,0.05,0.85,0.95);
TPad *pad2 = new TPad("pad2","This is pad2",0.78,0.02,0.99,0.95);
pad1->Draw();
pad2->Draw();

pad1->cd();
h_nEvents_average_sbnd->Draw(); 
h_nEvents_average_sbnd->SetTitle("SBND");

h_nEvents_average_sbnd->SetLineColor(kRed);
h_nEvents_average_sbnd->GetXaxis()->SetTitle("E [GeV]");
h_nEvents_average_sbnd->GetYaxis()->SetTitle("Osc. prob");
h_nEvents_average_sbnd->GetYaxis()->SetTitleOffset(1.15);
h_nEvents_average_sbnd->GetYaxis()->SetRangeUser(0.,1.0);

//h_nEvents_spline_sbnd->Draw("same"); 
h_nEvents_spline_sbnd->SetLineColor(kBlue); 

//h_nEvents_average_test_sbnd->Draw("same"); 
//h_nEvents_average_test_sbnd->SetLineColor(kGreen); 

h_nEvents_true_sbnd->Draw("same");

//h_nEvents_spline_sbnd_proper->Draw("same");
h_nEvents_spline_sbnd_proper->SetLineColor(kGreen);

h_nEvents_dom_sbnd->Draw("same");
h_nEvents_dom_sbnd->SetLineColor(kYellow);
h_nEvents_dom_sbnd->SetLineStyle(7);


pad2->cd();
// add legend
TLegend *leg_sbnd = new TLegend(0.0,0.75,0.99,0.95);
leg_sbnd->SetHeader("SBND", "C");
leg_sbnd->SetTextSize(0.1);
leg_sbnd->SetFillStyle(0);
leg_sbnd->SetLineWidth(0);
leg_sbnd->AddEntry((TObject*)0, "(2E-3,1E2)", "");
leg_sbnd->AddEntry((TObject*)0, "", "");
leg_sbnd->AddEntry(h_nEvents_true_sbnd,"true","l");
//leg_sbnd->AddEntry(h_nEvents_spline_sbnd,"spline_toy","l");
leg_sbnd->AddEntry(h_nEvents_average_sbnd,"average","l");
//leg_sbnd->AddEntry(h_nEvents_spline_sbnd_proper,"spline_proper","l");
leg_sbnd->AddEntry(h_nEvents_dom_sbnd,"used in VALOR","l");
leg_sbnd->Draw("same");


// ub
TCanvas *c2 = new TCanvas; 
c2->cd(1);

TPad *pad3 = new TPad("pad1","This is pad1",0.04,0.05,0.85,0.95);
TPad *pad4 = new TPad("pad2","This is pad2",0.78,0.02,0.99,0.95);
pad3->Draw();
pad4->Draw();

pad3->cd();

h_nEvents_average_ub->Draw(); 
h_nEvents_average_ub->SetLineColor(kRed);
h_nEvents_average_ub->GetXaxis()->SetTitle("E [GeV]");
h_nEvents_average_ub->GetYaxis()->SetTitle("Osc. prob");
h_nEvents_average_ub->GetYaxis()->SetTitleOffset(1.15);
h_nEvents_average_ub->GetYaxis()->SetRangeUser(0.,1.0);

h_nEvents_true_ub->Draw("same");

//h_nEvents_spline_ub->Draw("same");
h_nEvents_spline_ub->SetLineColor(kBlue);

//h_nEvents_spline_ub_proper->Draw("same");
h_nEvents_spline_ub_proper->SetLineColor(kGreen);

pad4->cd();
// add legend
TLegend *leg_ub = new TLegend(0.0,0.75,0.9,0.95);
leg_ub->SetHeader("uboone", "C");
leg_ub->SetTextSize(0.1);
leg_ub->SetFillStyle(0);
leg_ub->SetLineWidth(0);
leg_ub->AddEntry((TObject*)0, "(2E-3,1E2)", "");
leg_ub->AddEntry((TObject*)0, "", "");
leg_ub->AddEntry(h_nEvents_true_ub,"true","l");
//leg_ub->AddEntry(h_nEvents_spline_ub,"spline_toy","l");
leg_ub->AddEntry(h_nEvents_average_ub,"average","l");
//leg_ub->AddEntry(h_nEvents_spline_ub_proper,"spline_proper","l");
leg_ub->Draw("same");


// icarus
TCanvas *c3 = new TCanvas;
c3->cd(1);

TPad *pad5 = new TPad("pad1","This is pad1",0.04,0.05,0.85,0.95);
TPad *pad6 = new TPad("pad2","This is pad2",0.78,0.02,0.99,0.95);
pad5->Draw();
pad6->Draw();

pad5->cd();

h_nEvents_average_icarus->Draw(); 
h_nEvents_average_icarus->SetLineColor(kRed);
h_nEvents_average_icarus->GetXaxis()->SetTitle("E [GeV]");
h_nEvents_average_icarus->GetYaxis()->SetTitle("Osc. prob");
h_nEvents_average_icarus->GetYaxis()->SetTitleOffset(1.15);
h_nEvents_average_icarus->GetYaxis()->SetRangeUser(0.,1.0);

h_nEvents_true_icarus->Draw("same");

//h_nEvents_spline_icarus->Draw("same");
h_nEvents_spline_icarus->SetLineColor(kBlue);

//h_nEvents_spline_icarus_proper->Draw("same");
h_nEvents_spline_icarus_proper->SetLineColor(kGreen);

pad6->cd();
// add legend
TLegend *leg_icarus = new TLegend(0.0,0.75,0.9,0.95);
leg_icarus->SetHeader("ICARUS", "C");
leg_icarus->SetTextSize(0.1);
leg_icarus->SetFillStyle(0);
leg_icarus->SetLineWidth(0);
leg_icarus->AddEntry((TObject*)0, "(2E-3,1E2)", "");
leg_icarus->AddEntry((TObject*)0, "", "");
leg_icarus->AddEntry(h_nEvents_true_icarus,"true","l");
//leg_icarus->AddEntry(h_nEvents_spline_icarus,"spline_toy","l");
leg_icarus->AddEntry(h_nEvents_average_icarus,"average","l");
//leg_icarus->AddEntry(h_nEvents_spline_icarus_proper,"spline_proper","l");
leg_icarus->Draw("same");






// File to write to
TFile *MyFile = new TFile("plot_for_rhiannon.root","RECREATE");

// write histograms to file
h_nEvents_true_sbnd->Write();
h_nEvents_average_sbnd->Write();
h_nEvents_dom_sbnd->Write();
h_nEvents_spline_sbnd->Write();
h_nEvents_spline_sbnd_proper->Write();
h_nEvents_true_ub->Write();
h_nEvents_average_ub->Write();
h_nEvents_spline_ub->Write();
h_nEvents_spline_ub_proper->Write();
h_nEvents_true_icarus->Write();
h_nEvents_average_icarus->Write();
h_nEvents_spline_icarus->Write();
h_nEvents_spline_icarus_proper->Write();

MyFile->Close();


















}



















