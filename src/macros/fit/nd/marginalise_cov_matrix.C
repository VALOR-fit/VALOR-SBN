/*
This macro reads a covariance matrix from the input ROOT file, and marginalises it.
It does this by deleting the rows and columns that correspond to the parameters to be marginalised. 
This is equivalent to integrating over the parameters to be marginalised if the parameters have a multivariate 
Gaussian distribution - please see, for example 

section 3.1 in http://www.cs.uoi.gr/~arly/full/conferences/C69.pdf

and

section 3.1 in http://arxiv.org/pdf/0906.4123.pdf

The parameters to be marginalised are taken from the enum valor::conv::kNDFitParamMarginalize.

******* IMPORTANT NOTE ********

The input covariance matrix MUST have dimensions kNFitParams x kNFitParams, and the code will exit if the 
dimensions are not correct.  The covariance matrix is a TMatrixDSym, and its elements are accessed by a pointer 
to an array. Pointer arithmetic is used to find the elements, and this will go hopelessly wrong if the input 
matrix has the wrong dimensions. The problem is that, if the pointer goes beyond the memory holding the array, 
it will return whatever is in that memory. It will not give a segmentation fault as would be the case if an 
array goes out of bounds.

Nick Grant  14 July 2014 
*/

void marginalise_cov_matrix(
TString inputfile = "/opt/ppd/t2k/users/nick/DUNE/macros/fit/nd/fit51params/toymc_fhcflux_plus10.root",
)
{
  using namespace valor;
  using namespace valor::conv;

  // Open input file
  TFile f(inputfile, "read");

  PhysParamList * true_param_array     = 0; // input true params
  FitParamList *  best_fit_param_array = 0; // best-fit params
  TObjArray *     best_fit_model_array = 0; // an array of various best-fit model predictions for the current toy-MC experiment 
  TObjArray *     data_array           = 0; // an array of all fitted data distributions for the current toy-MC experiment

  TTree * fitnt = (TTree*)f.Get("fitnt");
  fitnt->SetBranchAddress("true_params",        &true_param_array);
  fitnt->SetBranchAddress("best_fit_params",    &best_fit_param_array);
  fitnt->SetBranchAddress("best_fit_model",     &best_fit_model_array);
  fitnt->SetBranchAddress("data",               &data_array);

  int i, j;
  double element;

  // Loop over entries (toy-MC experiments) in the tree
  for(Long_t toy=0; toy < fitnt->GetEntries(); toy++) 
    {
    fitnt->GetEntry(toy);

    cout<<endl;
    cout<<"Doing toy experiment "<<toy<<endl;
    cout<<endl;

    TMatrixDSym * cov = best_fit_param_array->GetCovMatrix();

    //check that input covariance matrix has correct dimensions
    if(cov->GetNrows() != kNFitParams || cov->GetNcols() != kNFitParams)
      {
      cerr<<"Input covariance matrix in experiment "<<toy<<" has wrong dimensions - it must be "<<kNFitParams<<" x "<<kNFitParams<<"."<<endl;
      exit(1);
      }

    cout<<"Input covariance matrix is: "<<endl;

    cov->Print();    

    double *covmat_array = cov->GetMatrixArray();
    //pointer will increment kNFitParams * kNFitParams times from start of array
    //hence input covariance matrix must have these dimensions
    double *end_covmat_array = covmat_array + kNFitParams * kNFitParams;
    cout<<endl;
    cout<<endl;

    //find number of parameters after marginalisation
    int kNNDFitParamsAfterMarg = 0;

    for(int i=0; i<kNFitParams; i++)
      {
      if(!kNDFitParamMarginalize[i])
        kNNDFitParamsAfterMarg++;
      }

    cout<<"Number of parameters after marginalisation is "<<kNNDFitParamsAfterMarg<<"."<<endl;

    TMatrixDSym cov_after_marg(kNNDFitParamsAfterMarg);
  
    i = -1;
    j = -1;

    for(; covmat_array<end_covmat_array; covmat_array++)
      { 
      //get element from input covariance matrix
      element = *covmat_array;
      //need to find 2D indices to write element to marginalised covariance matrix
      if((j+1)%kNFitParams==0)
	{
	 i++;
	 j = -1;
	}
      j++;
      //skip this element if it is in a row or column corresponding to a parameter to be marginalised
      if(kNDFitParamMarginalize[i] || kNDFitParamMarginalize[j])
        continue;
      //write element to marginalised covariance matrix
      cov_after_marg[i][j] = element;
      }

    cout<<endl;
    cout<<endl;

    cout<<"Covariance matrix after marginalisation is: "<<endl;
    cout<<endl;
    cov_after_marg.Print();

    cout<<endl;
    cout<<endl;

    }//end of for(Long_t toy; toy < fitnt->GetEntries(); toy++)

}//end of marginalise_cov_matrix
