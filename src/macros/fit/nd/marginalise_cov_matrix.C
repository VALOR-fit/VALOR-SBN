/*
This macro reads a covariance matrix from the input ROOT file, and marginalises it.
It does this by deleting the rows and columns that correspond to the parameters to be marginalised. 
This is equivalent to integrating over the parameters to be marginalised if the parameters have a multivariate 
Gaussian distribution - please see, for example 

section 3.1 in http://www.cs.uoi.gr/~arly/full/conferences/C69.pdf

and

section 3.1 in http://arxiv.org/pdf/0906.4123.pdf

The parameters to be marginalised are taken from the enum valor::conv::kNDFitParamMarginalize.

Nick Grant  14 July 2014

Rewritten for Dune second passthrough - Steve Dennis, April 2016
*/

bool isMarginalised(PhysParamId_t p) {
  return util::IsDetRelated(p);
}

void marginalise_cov_matrix(
TString inputfile = "/opt/ppd/t2k/users/nick/DUNE/macros/fit/nd/fit51params/toymc_fhcflux_plus10.root",
)
{
  using namespace valor;
  using namespace valor::conv;

  // Open input file
  TFile f(inputfile, "read");

  PhysParamList * true_params          = 0; // input true params
  FitParamList *  best_fit_params      = 0; // best-fit params
  TObjArray *     best_fit_model_array = 0; // an array of various best-fit model predictions for the current toy-MC experiment 
  TObjArray *     data_array           = 0; // an array of all fitted data distributions for the current toy-MC experiment

  TTree * fitnt = (TTree*)f.Get("valor_dune_nd_ntp");
  fitnt->SetBranchAddress("true_params",        &true_params);
  fitnt->SetBranchAddress("best_fit_params",    &best_fit_params);
  fitnt->SetBranchAddress("best_fit_model",     &best_fit_model_array);
  fitnt->SetBranchAddress("data",               &data_array);
  
  // Loop over entries (toy-MC experiments) in the tree
  for(Long_t toy=0; toy < fitnt->GetEntries(); toy++) 
  {
    fitnt->GetEntry(toy);

    cout<<endl;
    cout<<"Doing toy experiment "<<toy<<endl;
    cout<<endl;

    TMatrixDSym * cov = best_fit_params->GetCovMatrix();
    int n_params = best_fit_params->Size();

    //check that input covariance matrix has correct dimensions
    if(cov->GetNrows() != n_params || cov->GetNcols() != n_params)
    {
      cerr<<"Input covariance matrix in experiment "<<toy<<" has wrong dimensions - it must be "<<n_params<<" x "<<n_params<<"."<<endl;
      exit(1);
    }

    cout<<"Input covariance matrix is: "<<endl;

    cov->Print();    
    
    cout<<endl;
    cout<<endl;

    //find number of parameters after marginalisation
    PhysParamId_t * unmarginalised_parameters = new PhysParamId_t[n_params];
    int n_final_params = 0;
    for (int ipar = 0 ; ipar < n_params ; ipar++) {
      PhysParamId_t p = best_fit_params->WhichParam(ipar);
      if (!isMarginalised(p)) {
        unmarginalised_parameters[n_final_params] = p;
        n_final_params++;
      }
    }

    cout<<"Number of parameters after marginalisation is "<<n_final_params<<"."<<endl;

    TMatrixDSym cov_after_marg(n_final_params);
    
    // Array storing parameter names

    
    // Get marginalised matrix out.
    for(int ipar1 = 0; ipar1 < n_final_params; ipar1++) 
    {
      PhysParamId_t p1 = unmarginalised_parameters[ipar1];
      assert(p1!=kPhypUndefined);
      int idx_in_orig_matrix1 = best_fit_params->Id(p1);
      for (int ipar2 = 0 ; ipar2 < n_final_params; ipar2++) {
        PhysParamId_t p2 = unmarginalised_parameters[ipar2];
        assert(p2!=kPhypUndefined);
        int idx_in_orig_matrix2 = best_fit_params->Id(p2);
        cov_after_marg[ipar1][ipar2] = (*cov)[idx_in_orig_matrix1][idx_in_orig_matrix2];
      } //ipar2
      param_names[ipar1].Add(new TObjAString(best_fit_params->Name(p)));
    } //ipar1

    cout<<endl;
    cout<<endl;

    cout<<"Covariance matrix after marginalisation is: "<<endl;
    cout<<endl;
    cov_after_marg.Print();

    cout<<endl;
    cout<<endl;

  }//end of for(Long_t toy; toy < fitnt->GetEntries(); toy++)

}//end of marginalise_cov_matrix
