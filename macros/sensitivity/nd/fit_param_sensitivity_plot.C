//
// ------------------------------------------------------------------------------------------------
// Processes fit data produced by fit_param_sensitivity.C
// For each toy-MC experiment fit, it extracts the best-fit statistic as function of pv_fit (see
// comments in fit_param_sensitivity.C) and then averages over all toy-MC experiments.
//
// Costas Andreopoulos
// ------------------------------------------------------------------------------------------------
//

#include <algorithm>
#include <multimap>
#include <vector>

void fit_param_sensitivity_plot
(
  const char * filename,        /* run_fit.C output ROOT file with fit results (run `hadd' if there are many) */
  const char * pname            /* parameter name */
)
{
  using namespace valor;

  conv::PhysParamId_t p = util::NDPhysParamFromString(pname);
  assert(p != conv::kPhypUndefined);
  
  cout << "Plotting sensitivity to parameter: " << pname << " using toy-MC fit results stored in: " << filename << endl;
  
  // Open input file
  TFile f(filename, "read");

  // Get tree
  // Tree structure below is what is written out by run_fit.C
  // Similar (or adapt trivially) for other macros

  PhysParamList * true_param_array     = 0; // input true params
  FitParamList *  best_fit_param_array = 0; // best-fit params
//TObjArray *     best_fit_model_array = 0; // an array of various best-fit model predictions for the current toy-MC experiment 
//TObjArray *     data_array           = 0; // an array of all fitted data distributions for the current toy-MC experiment

  TTree * fitnt = (TTree*)f.Get("fitnt");
  fitnt->SetBranchAddress("true_params",        &true_param_array);
  fitnt->SetBranchAddress("best_fit_params",    &best_fit_param_array);
//fitnt->SetBranchAddress("best_fit_model",     &best_fit_model_array);
//fitnt->SetBranchAddress("data",               &data_array);

  // Get entries
  Long_t ntoymc = fitnt->GetEntries();
  cout << "Found " << ntoymc << " toy-MC experiment fits in the input tree" << endl;

  // Use a multimap to store "param value (fixed in fit)" --> "best-fit statistic" 
  // mappings for all toy-MC experiments included in the input ROOT file.
  multimap<double, double> inpfitdata;

  // Loop over entries (toy-MC experiments) in the tree
  for(Long_t itoymc; itoymc < ntoymc; itoymc++) {
    fitnt->GetEntry(itoymc);
    double p_true   = true_param_array->Value(p); // not checking, but this should always be the same - we are studying sensitivity at a particular point
    double p_bf     = best_fit_param_array->BestFitValue(p); // this param was fixed, it was the other N-1 that were fitted
    double chisq_bf = best_fit_param_array->GetBestFitStatistic();
    cout << "> Toy-MC: #" << itoymc << " : true param = " << p_true 
         << ", best-fit param = " << p_bf << ", best-fit \chi^2 = " << chisq_bf << endl;
    inpfitdata.insert(pair<double,double>(p_bf,chisq_bf));
  }//itoy

  //
  // Now process the input fit data
  //

  // Get a sorted vector of all unique paramerer values
  cout << "Getting unique param values (keys)" << endl;
  vector<double> p_vec;
  for(multimap<double, double>::iterator it_mmp = inpfitdata.begin(); it_mmp != inpfitdata.end(); ++it_mmp) {
     double p_value = it_mmp->first;
   //cout << "Parameter value: " << p_value << endl;
     if(count(p_vec.begin(), p_vec.end(), p_value) == 0) {
         p_vec.push_back(p_value);
         cout << "Adding new value (" << p_value << ")" << endl;
     }
  }
  sort(p_vec.begin(), p_vec.end());

  // For each true value, get all toy-MC results and average the best-fit statistic
  cout << "Averaging best-fit statistic for each true param value" << endl;
  map<double,double> chisq_avg_mp; // true param value -> average chi^2
  double chisq_avg_min = 9999999;
  for(vector<double>::iterator it_v = p_vec.begin(); it_v != p_vec.end(); ++it_v) {
    double p_value = *it_v;
    cout << "Averaging best-fit statistic for true value = " << p_value << endl;
    cout << "There are " << inpfitdata.count(p_value) << " toy-MC experiments with that true value" << endl;
    double chisq_sum = 0;
    double n = 0;   
    for(multimap<double, double>::iterator it_mmp2 = inpfitdata.begin(); it_mmp2 != inpfitdata.end(); ++it_mmp2) {
      double p_value_curr = it_mmp2->first;
      if(TMath::Abs(p_value-p_value_curr) > 1E-5 ) {
          continue;
      }
      double chisq = it_mmp2->second;
      cout << "  toy-MC #" << (int)n  << ", true value = " << p_value_curr << " --> chi^2 = " << chisq << endl;
      n = n+1;
      chisq_sum = chisq_sum + chisq;
    }
    double chisq_avg = chisq_sum/n;
    cout << "Average chisq (true param value = " << p_value << ") =" << chisq_avg << endl;
    chisq_avg_min = TMath::Min(chisq_avg_min, chisq_avg);
    chisq_avg_mp.insert(pair<double,double>(p_value,chisq_avg));
  }//unique keys

  // Subtract the minimum best-fit statistic
  map<double,double> delta_chisq_avg_mp;  // true param value -> \delta {average chi^2}
  for(map<double,double>::iterator it_mp = chisq_avg_mp.begin(); it_mp != chisq_avg_mp.end(); ++it_mp) {
    double p_value = it_mp->first;
    double chisq_avg = it_mp->second;
    double delta_chisq_avg = TMath::Max(0., chisq_avg-chisq_avg_min);
    delta_chisq_avg_mp.insert(pair<double,double>(p_value,delta_chisq_avg));
  }

  // Print
  for(map<double,double>::iterator it_mp = delta_chisq_avg_mp.begin(); it_mp != delta_chisq_avg_mp.end(); ++it_mp) {
    cout << "*** True value = " << it_mp->first << " ==> \delta{average \chi^2} = " << it_mp->second << endl;
  }

  // Format as TGraphs
  int pidx = util::NDArrIdx::Instance()->NDFitParamIdx(p);
  double sig = conv::kNDFitParamAPrioriFracError[pidx];
  int np = delta_chisq_avg_mp.size();
  double * p_value_array = new double[np];
  double * dchisq_array = new double[np];
  double * dchisq_penalty_array = new double[np];
  int ip = 0;
  for(map<double,double>::iterator it_mp = delta_chisq_avg_mp.begin(); it_mp != delta_chisq_avg_mp.end(); ++it_mp) {
    p_value_array[ip] = it_mp->first;
    dchisq_array[ip] = it_mp->second;
    dchisq_penalty_array[ip] =  TMath::Power((p_value_array[ip]-1.)/sig, 2.);
    ip++;
  }

  // Draw
  TGraph * sensitivity = new TGraph(np,p_value_array,dchisq_array);
  TGraph * prior = new TGraph(np,p_value_array,dchisq_penalty_array);
  prior->SetLineColor(kRed);
  sensitivity->Draw("alp");
  prior->Draw("l");
}
