void test_binning_arbitrary(const char * binning_file)
{
  using namespace std;
  using namespace valor;

  KBCubHcmbArbitrary binning("test","A test binning scheme");
  binning.Read(binning_file);

  conv::KineSpace_t ksp = binning.KineSpace();
  cout << "> Kine space: " << util::AsString(ksp) << endl;

  unsigned int ndim = binning.NDimensions();
  cout << "> Number of dimensions: " << ndim << endl;

  unsigned int nbin = binning.NBins();
  cout << "> Number of bins: " << nbin << endl;

  for(unsigned int idim = 0; idim < ndim; idim++) {
     conv::KineVar_t kv = binning.KineVar(idim);
     cout << "\t Dimension: #" << idim << " -> variable: " << util::AsString(kv) << endl;

     double min = binning.Minimum(idim);
     double max = binning.Maximum(idim);
     cout << "\t\t Range: [" << min << ", " << max << "]" << endl;
  }

  cout << "> Bin edges: " << endl;

  for(unsigned int ibin = 0; ibin < nbin; ibin++) {
     cout << "\t Bin: " << ibin << endl;
     for(unsigned int idim = 0; idim < ndim; idim++) {
       conv::KineVar_t kv = binning.KineVar(idim);
       if(idim == 0) cout << "\t\t Edges: ";
       cout << util::AsString(kv) << " = [" 
            << binning.BinMinimum(ibin,idim) << ", " 
            << binning.BinMaximum(ibin,idim) << "] "
       if(idim < ndim-1) cout << " - ";
     }
     cout << endl;
  }

/*
     unsigned int idim_test = binning.Dimension(kv);
     assert(idim == idim_test);
     unsigned int nbins_test = binning.NBins(kv);
     assert(nbins == nbins_test);
  }

  cout << "Testing bin finding: " << endl;
  const unsigned int np = 20;
  TRandom3 rand(0);
  for(unsigned int ip = 0; ip < np; ip++) {
     cout << "\t Random point = " << ip << endl;
     for(unsigned int idim = 0; idim < ndim; idim++) {
        conv::KineVar_t kv = binning.KineVar(idim);
        double min = binning.Minimum(idim);
        double max = binning.Maximum(idim);
        double x = min + (max - min) * rand.Uniform();
        unsigned int bin = binning.FindBin(x,idim);
        cout << "\t\t " << util::AsString(kv) << " = " << x << " --> bin = " << bin << endl;
     }
  }
*/

}
