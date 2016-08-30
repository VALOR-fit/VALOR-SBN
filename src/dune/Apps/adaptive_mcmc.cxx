//____________________________________________________________________________
/*!

\app       valor_dune-adaptive_mcmc

\brief     Generate and fit ensembles of toy-MC experiments.

\options    --input                    : File containing VALOR ND Tree of fit result
            --output                   : Output file name
            --config                   : Analysis configuration
           [--nsteps ]                 : Number of steps to process [ 30000 ]
           [--fit-number ]             : Entry in the input tree to use [ 0 ]
           [--disable-adaptive]        : Do not update the proposal function over time
           [--proposal-step]           : Proposal step size factor. Smaller makes it it more likely to accept a given step, but slows mixing. [0.3]
           [--burn-in]                 : Number of iterations to ignore in final covariance
           [--start-at-bestfit]        : Don't throw a random start point
           [--mesg-thresholds]         : Message thresholds [ "verbosity.xml" ]
           [--use-prefit-correlations] : Use correlations from prefit rather than postfit matrix for proposal
           [--use-no-correlations]     : Use diagonal matrix for proposals
           [--use-prefit-errors]       : Use errors from prefit rather than postfit matrix for proposal
           [--write-expanded-tree]     : Write each parameter value in its own branch. No extra info, just easier to browse.
           [--pot-override ]           : Use this POT for every sample (ignoring the one in config) [off]

\author    Steve Dennis <s.r.dennis \at liverpool.ac.uk>
           University of Liverpool

\created   July 2016

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

// root
#include "TFile.h"
#include "TSystem.h"
#include "TObjArray.h"
#include "TString.h"
#include "TVectorD.h"
#include "TPrincipal.h"
#include "TStopwatch.h"
// fmwk
#include "valor/Conventions/Opt.h"
#include "valor/CmdLine/CmdLnArgList.h"
#include "valor/FitCore/PhysParamList.h"
#include "valor/FitCore/FitParamList.h"
#include "valor/FitCore/FitModelABC.h"
#include "valor/FitCore/FitDataABC.h"
#include "valor/FitCore/FitInputs.h"
#include "valor/FitCore/FitterABC.h"
#include "valor/FitCore/UtlFit.h"
#include "valor/Utilities/UtlNumStat.h"
#include "valor/Utilities/UtlStyle.h"
#include "valor/Utilities/UtlStr.h"
#include "valor/Utilities/UtlSystem.h"
#include "valor/Utilities/Rnd.h"
#include "valor/Utilities/Env.h"
#include "valor/Messenger/Messenger.h"
#include "valor/Ntuple/StdFitNtp.h"
// dune
#include "dune/Conventions/FitParam.h"
#include "dune/Conventions/PhysicalParameterLimits.h"
#include "dune/Elements/CompoundFitElements.h"

using namespace std;
using namespace valor;
using namespace valor::conv;

int main(int argc, char ** argv)
{  
  Env::Instance()->AutoSet("dune");
  valor::util::PrintBanner(Env::Instance()->Banner(),500);
 
  CmdLnArgList arg;
  arg.Read(argc,argv,"$VALOR_DUNE/config/apps/adaptive_mcmc.arg:$VALOR_DUNE/config/apps/seeds.arg");
  LOG("valor_dune", pNOTICE) << arg;
  
  std::string thresholds = util::CompleteConfigPath(arg.GetString("mesg-thresholds"));
  Messenger::Instance()->Configure(thresholds);
  
  string input_filename        = arg.GetString("input");
  string output_filename       = arg.GetString("output");
  string config                = arg.GetString("config");
  int nsteps                   = arg.GetInt("nsteps");
  int fitnumber                = arg.GetInt("fit-number");
  int burn_in                  = arg.GetInt("burn-in");
  double proposal_step         = arg.GetDouble("proposal-step");
  bool start_at_bestfit        = arg.GetBool("start-at-bestfit");
  bool write_expanded_tree     = arg.GetBool("write-expanded-tree");
  bool disable_adaptive        = arg.GetBool("disable-adaptive");
  bool use_prefit_correlations = arg.GetBool("use-prefit-correlations");
  bool use_no_correlations     = arg.GetBool("use-no-correlations");
  bool use_prefit_errors       = arg.GetBool("use-prefit-errors");
  
  // If pot_override is set to a positive number, every sample will be initialised with the same POT - this number
  double pot_override     = arg.GetDouble("pot-override");
  if (pot_override > 0 ) {
    Opt::Instance()->MutableGlobalRegistry().Set("pot_override",pot_override);
  }
  
  int target_n_attempts = 5;
  int recalc_chol_every = 500;
  int recalculate_step_every = 10;
  
  // Set DUNE param names inside framework
  util::PopulateNameRegistry();
  
  // Set the random seeds
  Rnd::Instance()->SetSeeds(arg);
  LOG("valor_dune", pNOTICE) << *Rnd::Instance();
  
  // Set up the model
  config = util::CompleteConfigPath(config);
  LOG("valor_dune", pNOTICE) << "Getting and configuring the fit elements";
  CompoundFitElements * elements = new CompoundFitElements();
  elements->Read(config);
  FitDataABC  * data     = elements->FitData();
  FitModelABC * modelabc = elements->FitModel();
  CompoundFitModel * model = dynamic_cast<CompoundFitModel*>(modelabc); assert(model);
  
  // Get the input FPL
  TFile * input_file = new TFile(input_filename.c_str()); assert(input_file->IsOpen());
  TTree * in_tr = dynamic_cast<TTree*>(input_file->Get("valor_dune_nd_ntp")); assert(in_tr);
  FitParamList *  best_fit_params      = 0; // best-fit params
  in_tr->SetBranchAddress("best_fit_params",    &best_fit_params);
  assert(in_tr->GetEntries() > fitnumber);
  in_tr->GetEntry(fitnumber); assert(best_fit_params);
  best_fit_params->CopyBestFitToCurrValues();
  
  // Param list size
  const int npar = best_fit_params->Size();
  
  // Make the BF data
  data->Generate(model,*best_fit_params,false);
  
  // Setup the output tree
  TFile * output_file = new TFile(output_filename.c_str(),"RECREATE");
  output_file->cd();
  TTree * out_tr = new TTree("mcsteps","mcsteps");
  double o_chisq = -999;
  TVectorD o_params(npar);
  out_tr->Branch("params",&o_params);
  out_tr->Branch("chisq" ,&o_chisq,"chisq/D");
  if (write_expanded_tree) {
    for (int ip = 0 ; ip < npar ; ip++) {
      std::string pname  = best_fit_params->NameByIndex(ip);
      std::string pnameD = pname+"/D";
      out_tr->Branch(pname.c_str(),&(o_params[ip]),pnameD.c_str());
    }
  }
  
  // Build a Cholesky matrix we can use for throws
  CorrelatedSystematics * syst = model->GetSystematics();
  const TMatrixD & prefit_cov = syst->CovMatrix();
  assert(best_fit_params);
  assert(best_fit_params->Size()==(int)syst->Size());
  const TMatrixD fitted_cov(*best_fit_params->GetCovMatrix());
  
  TMatrixD corr(util::CovarianceMatrixToCorrelationMatrix(fitted_cov));
  TVectorD err (util::CovarianceMatrixToErrorVector(fitted_cov));
  if (use_prefit_errors) {
    err = util::CovarianceMatrixToErrorVector(prefit_cov);
  }
  if (use_prefit_correlations) {
    corr = util::CovarianceMatrixToCorrelationMatrix(prefit_cov);
  }
  else if (use_no_correlations) {
    for (int i = 0 ; i < npar ; i++) {
      for (int j = 0 ; j < npar ; j++ ) {
        corr[i][j] = (i==j);
      }
    }
  }
  
  TMatrixD init_proposal_cov(util::CorrelationAndErrorToCovarianceMatrix(corr,err));
  
  TMatrixD chol_matrix(util::CholeskyDecomposition(init_proposal_cov));
  
  // Throw a random start point, unless told not to
  if (!start_at_bestfit) {
    TRandom3 & rnd = Rnd::Instance()->RndOther();
    TVectorD throwvec(npar);
    bool bad_throw = true;
    while (bad_throw) {
      bad_throw = false;
      for (int ip = 0 ; ip < npar ; ip++) {
        throwvec[ip] = rnd.Gaus();
      }
      // Correlate the throws
      throwvec *= (chol_matrix);
      // Check they're valid, then copy into FPL
      for (int ip = 0 ; ip < npar ; ip++) {
        if (best_fit_params->IsFixedByIndex(ip)) {continue;}
        double min   = best_fit_params->MinValueByIndex(ip);
        double start = best_fit_params->BestFitValueByIndex(ip);
        double max   = best_fit_params->MaxValueByIndex(ip);
        double val  = start+throwvec[ip];
        if (val > max || val < min) {
          bad_throw=true;
          break;
        }
        best_fit_params->SetCurrentValueByIndex(ip,val);
      }
    }
  }
  
  // Setup fitinputs
  FitInputs fitinputs(data,model,best_fit_params);
  
  best_fit_params->Print();
  
  // Get starting statistic
  double current_chisq = fitinputs.Statistic();
  //~ std::cout<<current_chisq<<"\t"<<best_fit_params->GetBestFitStatistic()<<std::endl;
  if (start_at_bestfit) {
    assert(std::fabs(current_chisq - best_fit_params->GetBestFitStatistic()) < 1E-5);
  }
  
  // Make the covariance matrix we'll update as we go along (to be used for adaptive)
  TVectorD parameter_means(best_fit_params->AsTVector());
  TMatrixD adaptive_covariance(npar,npar);
  int n_entries_in_matrix = 1;
  
  // Write start point
  o_chisq = current_chisq;
  o_params.SetSub(0,best_fit_params->AsTVector());
  out_tr->Fill();
  
  double mean_n_attempts = 0;
  int n_steps_in_mean = 0;
  
  // Record time
  TStopwatch clock;
  
  for (int istep = 1 ; istep < nsteps ; istep++) {
    // Every N steps, print out a status
    // And redo the Chol matrix if we're adapting
    if (istep%recalc_chol_every == 0 && istep) {
      std::cout<<istep<<"\t"<<clock.RealTime()<<"\t"<<std::endl;
      //~ std::cout<<proposal_step<<std::endl;
      out_tr->AutoSave();
      
      if (!disable_adaptive) {
        // Make a new cholesky matrix from the fit results so far
        chol_matrix = util::CholeskyDecomposition(util::LowerTriangularMatrixToSymMatrix(adaptive_covariance));
      }
      
      clock.Start();
    }
    
    // Every N steps, recalculate the step size so we're trying ~target_n_attempts throws per evaluation
    if (!disable_adaptive && istep%recalculate_step_every == 0) {
      if (mean_n_attempts > target_n_attempts * 1.5) {
        proposal_step *= 0.8;
      }
      else if (mean_n_attempts < target_n_attempts * 0.6) {
        proposal_step *= 1.2;
      }
      mean_n_attempts = 0.;
      n_steps_in_mean = 0;
    }
    
    int n_attempts;
    bool success = util::AttemptMCMCStep(fitinputs,current_chisq,n_attempts,proposal_step,&chol_matrix);
    
    // Recalculate mean attempts
    n_steps_in_mean++;
    mean_n_attempts *= 1. - 1./(n_steps_in_mean);
    mean_n_attempts += ((double)n_attempts)/(n_steps_in_mean);
    
    if (!success) {
      if (!disable_adaptive) {
        proposal_step *= 0.1; // If we failed, do smaller steps
        LOG("adaptive_mcmc",pNOTICE)<<"New proposal step is "<<proposal_step;
      }
      continue;
    }
    o_chisq = current_chisq;
    o_params.SetSub(0,best_fit_params->AsTVector());
    out_tr->Fill();
    
    // Update the adaptive covariance
    n_entries_in_matrix ++;
    double cor = 1. - 1./n_entries_in_matrix;
    for (int ip = 0; ip < npar; ip++) {
      parameter_means[ip] *= cor;
      parameter_means[ip] += o_params[ip] / n_entries_in_matrix;
      double t1 = (o_params[ip] - parameter_means[ip]) / (n_entries_in_matrix - 1);
      // Setting Matrix (lower triangle) elements
      for (int jp = 0; jp < ip + 1; jp++) {
        adaptive_covariance(ip,jp) *= cor;
        adaptive_covariance(ip,jp) += t1 * (o_params[jp] - parameter_means[jp]);
      }//j
    } //ip
  } //istep
  
  
  // Write the ttree
  output_file->cd();
  out_tr->Write();
  
  // Variable to store the total value in
  TVectorD total(npar);
  
  // Then do the PCA
  std::cout<<"Steps complete. Doing PCA."<<std::endl;
  TPrincipal pca(npar);
  for (int i = burn_in ; i < out_tr->GetEntries() ; i++) {
    out_tr->GetEntry(i);
    pca.AddRow(o_params.GetMatrixArray());
    total += o_params;
  }
  TMatrixD cov_out(util::LowerTriangularMatrixToSymMatrix(*(pca.GetCovarianceMatrix())));
  cov_out.Write("cov");
  
  prefit_cov.Write("cov_in");
  
  // Write out the ratio of mean to best_fit
  cout<<"\n\n"<<"Mean from chain / best fit: "<<endl;
  for (int ip = 0 ; ip < npar; ip++ ) {
    double mean = total[ip] / (out_tr->GetEntries()-burn_in);
    cout<<best_fit_params->NameByIndex(ip)<<"\t"<< mean / best_fit_params->BestFitValueByIndex(ip)<<endl;
  }
  
  return 0;
}

