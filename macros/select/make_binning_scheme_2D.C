/*
This macro makes optimised 2D binning schemes by attempting to set the bin edges so that the numbers of 
events in each bin are as equal as possible. 

The ranges and numbers of bins in x and y can be set. 

Two binning schemes are made:

1. Strips in x are found such that the number of events in each strip is equal irrespective of the y values.  
   For example, if there are 10560 events and 10 bins in x, the bin edges are set such that there are 1056 
   events in each strip. Strips are found in y in a similar way. The x and y strips are found independently 
   of each other.  

2. The 2D space is split into 4 zones, with the divisions between the zones being the median values of 
   x and y. For example, the bottom left zone covers x_min - x_median and y_min to y_median. Within each 
   zone, the bin edges are set in the same way as in method 1. In effect, this divides the 2D space into 4 
   separate histograms. 

Nick Grant 23 May 2014

*/

#include <iomanip>
#include <vector>

void make_binning_scheme_2D
(
 TString sample_file_name = "NDEventSamples.root",
 const int event_sample = 2, //index number of event sample as in enum in NDFit/NDSample.h
 const int n_bins_x = 10,   //this must be an even number in this version of the macro to allow the division into zones
 const int n_bins_y = 8,   //this must be an even number in this version of the macro to allow the division into zones
 const double x_min = 0.0,
 const double x_max = 50.0,
 const double y_min = 0.0,
 const double y_max = 1.0
)
{

  TFile *sampleFile = TFile::Open(sample_file_name);
  sampleFile->cd();

  int neu;
  bool cc;
  bool nc;
  //number of CC + NC interactions per kt per POT - according to https://cdcvs.fnal.gov/redmine/projects/fast_mc/wiki/Nominal_Flux_Normalizations
  //or number of CC + NC interactions per POT - according to comment in gNtpConv_FastMC.cxx
  double POTWeight;
  bool qel;
  bool res;
  bool dis;
  bool coh;
  int sampleIndex;
  double y_reco;
  double Ev_reco;

  gst->SetBranchAddress("neu",&neu);
  gst->SetBranchAddress("cc",&cc);
  gst->SetBranchAddress("nc",&nc);
  gst->SetBranchAddress("POTWeight",&POTWeight);
  gst->SetBranchAddress("qel",&qel);
  gst->SetBranchAddress("res",&res);
  gst->SetBranchAddress("dis",&dis);
  gst->SetBranchAddress("coh",&coh);
  gst->SetBranchAddress("sampleIndex",&sampleIndex);
  gst->SetBranchAddress("y_reco",&y_reco);
  gst->SetBranchAddress("Ev_reco",&Ev_reco);

  cout<<setprecision(3);

  vector<double> x_values;
  vector<double> y_values;

  const int n_zone = 4;

  vector<double> zone_x_values[n_zone];
  vector<double> zone_y_values[n_zone];

  vector<double>::iterator valueiter;

  double bin_edge_x[n_bins_x+1][n_bins_y];
  double bin_edge_y[n_bins_x][n_bins_y+1];
  double zone_bin_edge_x[n_bins_x+1][n_bins_y] = {0};
  double zone_bin_edge_y[n_bins_x][n_bins_y+1] = {0};

  int bin_content[n_bins_x][n_bins_y] = {0};
  int zone_bin_content[n_bins_x][n_bins_y] = {0};

  double x_median, y_median;

  TString selection = "sampleIndex==";
  selection += Form("%d", event_sample);
  selection += "&&Ev_reco>=";
  selection += Form("%f", x_min);
  selection += "&&Ev_reco<=";
  selection += Form("%f", x_max);
  selection += "&&y_reco>=";
  selection += Form("%f", y_min);
  selection += "&&y_reco<=";
  selection += Form("%f", y_max);
  double mean_bin_content = gst->GetEntries(selection) / (n_bins_x * n_bins_y);

  double dev_sq_sum;

  cout<<endl;
  cout<<endl;
  cout<<"Calculating optimal binning scheme in a single rectangular grid......"<<endl;
  cout<<endl;
  cout<<endl;

  //put all x values into one vector and all y values into another vector
  for(Long64_t i = 0; i < gst->GetEntries(); i++)
    {
    gst->GetEntry(i);

    if(sampleIndex == event_sample)
      {
      if(Ev_reco >= x_min && Ev_reco <= x_max)
	x_values.push_back(Ev_reco);
      if(y_reco >=y_min && y_reco <= y_max)
	y_values.push_back(y_reco);
      }

    }//end of loop over events

  //sort x values and make x bin edges such that each bin in x has equal number of x values (irrespective of y values)
  sort(x_values.begin(), x_values.end());

  for(int y_bin=0; y_bin<n_bins_y; y_bin++)
    bin_edge_x[0][y_bin] = 0.0;

  for(int x_edge=1; x_edge<n_bins_x; x_edge++)
    {
    valueiter = x_values.begin() + (int)(x_edge * x_values.size() / n_bins_x);
    for(int y_bin=0; y_bin<n_bins_y; y_bin++)
      bin_edge_x[x_edge][y_bin] = (*valueiter);
    }

  for(int y_bin=0; y_bin<n_bins_y; y_bin++)
    bin_edge_x[n_bins_x][y_bin] = x_max;
  
  //sort y values and make y bin edges such that each bin in y has equal number of y values (irrespective of x values)
  sort(y_values.begin(), y_values.end());

  for(int x_bin=0; x_bin<n_bins_x; x_bin++)
    bin_edge_y[x_bin][0] = 0.0;

  for(int y_edge=1; y_edge<n_bins_y; y_edge++)
    {
    valueiter = y_values.begin() + (int)(y_edge * y_values.size() / n_bins_y);
    for(int x_bin=0; x_bin<n_bins_x; x_bin++)
      bin_edge_y[x_bin][y_edge] = (*valueiter);
    }

  for(int x_bin=0; x_bin<n_bins_x; x_bin++)
    bin_edge_y[x_bin][n_bins_y] = y_max;

  //get bin contents for initial binning scheme which is a rectangular grid
  for(Long64_t i = 0; i < gst->GetEntries(); i++)
    {
    gst->GetEntry(i);

    if(sampleIndex == event_sample)
      {
      for(int x_bin = 1; x_bin <= n_bins_x; x_bin++)
        {
        for(int y_bin= 1; y_bin <= n_bins_y;y_bin++)
          {
          if(Ev_reco > bin_edge_x[x_bin-1][y_bin-1] && Ev_reco <= bin_edge_x[x_bin][y_bin-1]
             && y_reco > bin_edge_y[x_bin-1][y_bin-1] && y_reco <= bin_edge_y[x_bin-1][y_bin])
	     bin_content[x_bin-1][y_bin-1]++;
	  }
        }
      }
    }//end of loop over events

    cout<<"Bin edges in x with single rectangular grid are:"<<endl;
    cout<<endl;
    cout<<"{";
    for(int j=0; j<=n_bins_x; j++)
      {
      if(j == n_bins_x)
        cout<<bin_edge_x[j][0];
      else
	cout<<bin_edge_x[j][0]<<",";
      }
    cout<<"};";
	 
    cout<<endl;
    cout<<endl;



    cout<<"Bin edges in y with single rectangular grid are:"<<endl;
    cout<<endl;

    cout<<"{";
    for(int k=0; k<=n_bins_y; k++)
      { 
	if(k == n_bins_y)
	  cout<<bin_edge_y[0][k];
	else    
	  cout<<bin_edge_y[0][k]<<",";
      } 
    cout<<"};";

    cout<<endl;
    cout<<endl;

    dev_sq_sum = 0.0;

    cout<<"Bin contents with single rectangular grid are:"<<endl;
    cout<<endl;

    for(int k=n_bins_y; k>=1; k--)
      {
      for(int j=1; j<=n_bins_x; j++)
	{
	cout<<"    "<<bin_content[j-1][k-1];
        dev_sq_sum += (bin_content[j-1][k-1] - mean_bin_content) * (bin_content[j-1][k-1] - mean_bin_content);
	}
      cout<<endl;
      }

    cout<<endl;
    cout<<endl;

    cout<<"Mean bin content is "<<mean_bin_content<<endl;
    cout<<endl;
    cout<<"Standard deviation of bin contents with single rectangular grid is "<<sqrt(dev_sq_sum / ((n_bins_x * n_bins_y) - 1))<<endl;

    cout<<endl;
    cout<<endl;

  

  cout<<endl;
  cout<<"Calculating optimal binning scheme using 4 equal-sized zones......"<<endl;
  cout<<endl;
  cout<<endl;

  valueiter = x_values.begin() + (int)(0.5 * x_values.size());
  x_median = (*valueiter);
  valueiter = y_values.begin() + (int)(0.5 * y_values.size());
  y_median = (*valueiter);

  for(Long64_t i = 0; i < gst->GetEntries(); i++)
    {
    gst->GetEntry(i);

    if(sampleIndex == event_sample)
      {
      if(Ev_reco >= x_min && Ev_reco <= x_median && y_reco >= y_min && y_reco <= y_median)
	{
	zone_x_values[0].push_back(Ev_reco);
	zone_y_values[0].push_back(y_reco);
	}
      if(Ev_reco > x_median && Ev_reco <= x_max && y_reco >= y_min && y_reco <= y_median)
        {
	zone_x_values[1].push_back(Ev_reco);
	zone_y_values[1].push_back(y_reco);
        }
      if(Ev_reco >= x_min && Ev_reco <= x_median && y_reco > y_median && y_reco <= y_max)
        {
	zone_x_values[2].push_back(Ev_reco);
	zone_y_values[2].push_back(y_reco);
        }
      if(Ev_reco > x_median && Ev_reco <= x_max && y_reco > y_median && y_reco <= y_max)
        {
	zone_x_values[3].push_back(Ev_reco);
	zone_y_values[3].push_back(y_reco);
        }
      }
    }//end of loop over events

  sort(zone_x_values[0].begin(), zone_x_values[0].end());

  for(int y_bin=0; y_bin<n_bins_y/2; y_bin++)
    zone_bin_edge_x[0][y_bin] = 0.0;

  for(int x_edge=1; x_edge<n_bins_x/2; x_edge++)
    {
    valueiter = zone_x_values[0].begin() + (int)(x_edge * zone_x_values[0].size() / (n_bins_x/2));
    for(int y_bin=0; y_bin<n_bins_y/2; y_bin++)
      zone_bin_edge_x[x_edge][y_bin] = (*valueiter);
    }

  for(int y_bin=0; y_bin<n_bins_y/2; y_bin++)
    zone_bin_edge_x[n_bins_x/2][y_bin] = x_median;

  sort(zone_x_values[1].begin(), zone_x_values[1].end());

  for(int y_bin=0; y_bin<n_bins_y/2; y_bin++)
    zone_bin_edge_x[n_bins_x/2][y_bin] = x_median;

  for(int x_edge=(n_bins_x/2)+1; x_edge<=n_bins_x; x_edge++)
    {
    valueiter = zone_x_values[1].begin() + (int)((x_edge-n_bins_x/2) * zone_x_values[1].size() / (n_bins_x/2));
    for(int y_bin=0; y_bin<n_bins_y/2; y_bin++)
      zone_bin_edge_x[x_edge][y_bin] = (*valueiter);
    }

  for(int y_bin=0; y_bin<n_bins_y/2; y_bin++)
    zone_bin_edge_x[n_bins_x][y_bin] = x_max;

  sort(zone_x_values[2].begin(), zone_x_values[2].end());

  for(int y_bin=n_bins_y/2; y_bin<n_bins_y; y_bin++)
    zone_bin_edge_x[0][y_bin] = x_min;

  for(int x_edge=1; x_edge<n_bins_x/2; x_edge++)
    {
    valueiter = zone_x_values[2].begin() + (int)(x_edge * zone_x_values[2].size() / (n_bins_x/2));
    for(int y_bin=n_bins_y/2; y_bin<n_bins_y; y_bin++)
      zone_bin_edge_x[x_edge][y_bin] = (*valueiter);
    }

  for(int y_bin=n_bins_y/2; y_bin<n_bins_y; y_bin++)
    zone_bin_edge_x[n_bins_x/2][y_bin] = x_median;

  sort(zone_x_values[3].begin(), zone_x_values[3].end());

  for(int y_bin=n_bins_y/2; y_bin<n_bins_y; y_bin++)
    zone_bin_edge_x[n_bins_x/2][y_bin] = x_median;

  for(int x_edge=(n_bins_x/2)+1; x_edge<=n_bins_x; x_edge++)
    {
    valueiter = zone_x_values[3].begin() + (int)((x_edge-n_bins_x/2) * zone_x_values[3].size() / (n_bins_x/2));
    for(int y_bin=n_bins_y/2; y_bin<n_bins_y; y_bin++)
      zone_bin_edge_x[x_edge][y_bin] = (*valueiter);
    }

  for(int y_bin=n_bins_y/2; y_bin<n_bins_y; y_bin++)
    zone_bin_edge_x[n_bins_x][y_bin] = x_max;

  sort(zone_y_values[0].begin(), zone_y_values[0].end());

  for(int x_bin=0; x_bin<n_bins_x/2; x_bin++)
    zone_bin_edge_y[x_bin][0] = y_min;

  for(int y_edge=1; y_edge<=n_bins_y/2; y_edge++)
    {
    valueiter = zone_y_values[0].begin() + (int)(y_edge * zone_y_values[0].size() / (n_bins_y/2));
    for(int x_bin=0; x_bin<n_bins_x/2; x_bin++)
      zone_bin_edge_y[x_bin][y_edge] = (*valueiter);
    }

  for(int x_bin=0; x_bin<n_bins_x/2; x_bin++)
    zone_bin_edge_y[x_bin][n_bins_y/2] = y_median;

  sort(zone_y_values[1].begin(), zone_y_values[1].end());

  for(int x_bin=n_bins_x/2; x_bin<=n_bins_x; x_bin++)
    zone_bin_edge_y[x_bin][0] = y_min;

  for(int y_edge=1; y_edge<n_bins_y/2; y_edge++)
    {
    valueiter = zone_y_values[1].begin() + (int)(y_edge * zone_y_values[1].size() / (n_bins_y/2));
    for(int x_bin=n_bins_x/2; x_bin<n_bins_x; x_bin++)
      zone_bin_edge_y[x_bin][y_edge] = (*valueiter);
    }

  for(int x_bin=n_bins_x/2; x_bin<n_bins_x; x_bin++)
    zone_bin_edge_y[x_bin][n_bins_y/2] = y_median;

  sort(zone_y_values[2].begin(), zone_y_values[2].end());

  for(int x_bin=0; x_bin<n_bins_x/2; x_bin++)
    zone_bin_edge_y[x_bin][(n_bins_y/2)+1] = y_median;

  for(int y_edge=(n_bins_y/2)+1; y_edge<=n_bins_y; y_edge++)
    {
    valueiter = zone_y_values[2].begin() + (int)((y_edge-n_bins_y/2) * zone_y_values[2].size() / (n_bins_y/2));
    for(int x_bin=0; x_bin<n_bins_x/2; x_bin++)
      zone_bin_edge_y[x_bin][y_edge] = (*valueiter);
    }

  for(int x_bin=0; x_bin<n_bins_x/2; x_bin++)
    zone_bin_edge_y[x_bin][n_bins_y] = y_max;

  sort(zone_y_values[3].begin(), zone_y_values[3].end());

  for(int x_bin=n_bins_x/2; x_bin<n_bins_x; x_bin++)
    zone_bin_edge_y[x_bin][n_bins_y/2] = y_median;

  for(int y_edge=(n_bins_y/2)+1; y_edge<n_bins_y; y_edge++)
    {
    valueiter = zone_y_values[3].begin() + (int)((y_edge-n_bins_y/2) * zone_y_values[3].size() / (n_bins_y/2));
    for(int x_bin=n_bins_x/2; x_bin<n_bins_x; x_bin++)
      zone_bin_edge_y[x_bin][y_edge] = (*valueiter);
    }

  for(int x_bin=n_bins_x/2; x_bin<n_bins_x; x_bin++)
    zone_bin_edge_y[x_bin][n_bins_y] = y_max;

  for(Long64_t i = 0; i < gst->GetEntries(); i++)
    {
    gst->GetEntry(i);

    if(sampleIndex == event_sample)
      {
      for(int x_bin = 1; x_bin <= n_bins_x; x_bin++)
	{
	for(int y_bin= 1; y_bin <= n_bins_y;y_bin++)
	  {
	  if(Ev_reco > zone_bin_edge_x[x_bin-1][y_bin-1] && Ev_reco <= zone_bin_edge_x[x_bin][y_bin-1]
	     && y_reco > zone_bin_edge_y[x_bin-1][y_bin-1] && y_reco <= zone_bin_edge_y[x_bin-1][y_bin])
	     zone_bin_content[x_bin-1][y_bin-1]++;
	  }
        }
      }
    }//end of loop over events

  cout<<"Bin edges in x with 4 zones are:"<<endl;
  cout<<endl;
  for(int k=n_bins_y-1; k>=0; k--)
    {
    for(int j=0; j<=n_bins_x; j++)
      {
      cout<<"    "<<zone_bin_edge_x[j][k];
      }
    cout<<endl;
    }

   cout<<endl;
   cout<<endl;

   cout<<"Bin edges in y with 4 zones are:"<<endl;
   cout<<endl;

   for(int k=n_bins_y; k>=0; k--)
     {
     for(int j=0; j<n_bins_x; j++)
       {
       cout<<"    "<<zone_bin_edge_y[j][k];
       }
     cout<<endl;
     }

   cout<<endl;
   cout<<endl;

   dev_sq_sum = 0.0;

   cout<<"Bin contents with 4 zones are:"<<endl;
   cout<<endl;

   for(int k=n_bins_y; k>=1; k--)
     {
     for(int j=1; j<=n_bins_x; j++)
       {
       cout<<"    "<<zone_bin_content[j-1][k-1];
       dev_sq_sum += (zone_bin_content[j-1][k-1] - mean_bin_content) * (zone_bin_content[j-1][k-1] - mean_bin_content);
       }
     cout<<endl;
     }

   cout<<endl;
   cout<<endl;

   cout<<"Mean bin content is "<<mean_bin_content<<endl;
   cout<<endl;
   cout<<"Standard deviation of bin contents with 4 zones is "<<sqrt(dev_sq_sum / ((n_bins_x * n_bins_y) - 1))<<endl;

   cout<<endl;
   cout<<endl;

}//end of make_binning_scheme_2D()
