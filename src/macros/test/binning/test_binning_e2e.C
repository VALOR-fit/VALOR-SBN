void test_binning_e2e(const char * binning_file)
{
  using namespace std;
  using namespace valor;

  KBCubHcmbEdge2Edge binning("test","A test binning scheme");
  binning.Read(binning_file);

  conv::KineSpace_t ksp = binning.KineSpace();
  cout << "> Kine space: " << util::AsString(ksp) << endl;

  unsigned int ndim = binning.NDimensions();
  cout << "> Number of dimensions: " << ndim << endl;

  for(unsigned int idim = 0; idim < ndim; idim++) {
     conv::KineVar_t kv = binning.KineVar(idim);
     cout << "\t Dimension: #" << idim << " -> variable: " << util::AsString(kv) << endl;

     unsigned int nbins = binning.NBins(idim);
     cout << "\t\t NBins: " << nbins << endl;

     bool fixed_width = binning.FixedWidth(idim);
     cout << "\t\t Fixed width? " << ((fixed_width) ? "true" : "false") << endl;

     double min = binning.Minimum(idim);
     double max = binning.Maximum(idim);
     cout << "\t\t Range: [" << min << ", " << max << "]" << endl;

     const double * bin_edges = binning.BinEdgeArr(idim);
     for(unsigned int i = 0; i <= nbins; i++) {
       if(i == 0) cout << "\t\t Bin edges: [";
       cout << bin_edges[i];
       if(i < nbins) cout << ", ";
       if(i == nbins) cout << "]" << endl;
     }

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

}
