/*

This macro makes an optimised 2D binning scheme by attempting to set the bin edges so that the numbers of 
events in each bin are as equal as possible.

The parameter space is divided into zones, with each zone being in effect a separate 2D histogram. The 
boundaries of the zones in x are the (1/n_zones_x)*100 percentiles of the values of x in the whole parameter 
space (irrespective of the values of y). Similarly, the boundaries of the zones in y are the (1/n_zones_y)*100 
percentiles of the values of y in the whole parameter space (irrespective of the values of x).

Within each zone, strips in x are found such that the number of events in each strip is equal irrespective 
of the y values. Strips are found in y in a similar way. The x and y strips are found independently of each 
other.

After the bin edges have been found, they can be rounded so that they are multiples of the edges in a fine 
binning scheme. 

The numbers of bins, numbers of zones, the minimum and maximum values in x and y and the rounding values can 
be input by the user.  

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           George Christodoulou <georgios \at hep.ph.liv.ac.uk>
           University of Liverpool

           Nick Grant <nick.grant \at stfc.ac.uk>
           University of Warwick

\created   23 May 2014

\copyright (c) 2010-2015, The VALOR Fitting Group, All Rights Reserved

*/

#include <iomanip>
#include <vector>

double round(double bin_edge, double round_value);

void make_binning_scheme_2D
(
 TString sample_file_name = "NDEventSamples.root",
 const int event_sample = 2, //index number of event sample 
 const int n_bins_x = 6,   //this must be a multiple of n_zones_x to allow the division into zones
 const int n_bins_y = 6,   //this must be a multiple of n_zones_y to allow the division into zones
 const int n_zones_x = 3,  
 const int n_zones_y = 3,
 const double x_min = 0.0,
 const double x_max = 100.0,
 const double y_min = 0.0,
 const double y_max = 1.0,
 const double round_x_bin_edges_to_nearest = 0.2,  //round Ev_reco bin edges to this value; set this to -1 if you don't want rounding.
 const double round_y_bin_edges_to_nearest = 0.1,  //round y_reco bin edges to this value; set this to -1 if you don't want rounding.
)
{
  
  if(n_bins_x%n_zones_x != 0)
    {
    cerr<<"n_bins_x must be a multiple of n_zones_x to allow the division into zones - please modify the input values."<<endl;
    exit(1);
    }

  if(n_bins_y%n_zones_y != 0)
    {
    cerr<<"n_bins_y must be a multiple of n_zones_y to allow the division into zones - please modify the input values."<<endl;
    exit(1);
    }

  if((double)n_bins_x > ((x_max - x_min) / round_x_bin_edges_to_nearest))
    {
    cerr<<"Cannot fit "<<n_bins_x<<" bins of width "<<round_x_bin_edges_to_nearest<<" into x values between "<<x_min<<" and "<<x_max
	<<" - please modify the input values."<<endl;
    exit(1);
    }

  if((double)n_bins_y > ((y_max - y_min) / round_y_bin_edges_to_nearest))
    {
    cerr<<"Cannot fit "<<n_bins_y<<" bins of width "<<round_y_bin_edges_to_nearest<<" into y values between "<<y_min<<" and "<<y_max
        <<" - please modify the input values."<<endl;
    exit(1);
    }

  TFile *sampleFile = TFile::Open(sample_file_name);
  sampleFile->cd();

  int neu;
  //number of CC + NC interactions per kt per POT - according to https://cdcvs.fnal.gov/redmine/projects/fast_mc/wiki/Nominal_Flux_Normalizations
  //or number of CC + NC interactions per POT - according to comment in gNtpConv_FastMC.cxx
  double POTWeight;
  int sampleIndex;
  double y_reco;
  double Ev_reco;

  gst->SetBranchAddress("neu",&neu);
  gst->SetBranchAddress("POTWeight",&POTWeight);
  gst->SetBranchAddress("sampleIndex",&sampleIndex);
  gst->SetBranchAddress("y_reco",&y_reco);
  gst->SetBranchAddress("Ev_reco",&Ev_reco);

  //cout<<setprecision(3);

  vector<double> x_values;
  vector<double> y_values;

  vector<double> zone_x_values[n_zones_x][n_zones_y];
  vector<double> zone_y_values[n_zones_x][n_zones_y];

  vector<double>::iterator valueiter;

  double bin_edge_x[n_bins_x+1][n_bins_y];
  double bin_edge_y[n_bins_x][n_bins_y+1];
  double zone_bin_edge_x[n_bins_x+1][n_bins_y] = {0};
  double zone_bin_edge_y[n_bins_x][n_bins_y+1] = {0};

  int bin_content[n_bins_x][n_bins_y] = {0};
  int zone_bin_content[n_bins_x][n_bins_y] = {0};

  double x_zone_edge[n_zones_x+1];
  double y_zone_edge[n_zones_y+1];

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

  sort(x_values.begin(), x_values.end());
  sort(y_values.begin(), y_values.end());

  cout<<endl;
  cout<<"Calculating optimal binning scheme using "<<n_zones_x<<" zones in x and "<<n_zones_y<<" zones in y ......"<<endl;
  cout<<endl;
  cout<<endl;

  x_zone_edge[0] = x_min;
  y_zone_edge[0] = y_min;

  for(int x_zone=1; x_zone<n_zones_x; x_zone++)
    {
    valueiter = x_values.begin() + (int)(x_zone * x_values.size()) / n_zones_x;
    x_zone_edge[x_zone] = (*valueiter);
    }
  for(int y_zone=1; y_zone<n_zones_y; y_zone++)
    {
    valueiter = y_values.begin() + (int)(y_zone * y_values.size()) / n_zones_y;
    y_zone_edge[y_zone] = (*valueiter);
    }

  x_zone_edge[n_zones_x] = x_max;
  y_zone_edge[n_zones_y] = y_max;

  for(Long64_t i = 0; i < gst->GetEntries(); i++)
    {
    gst->GetEntry(i);

    if(sampleIndex == event_sample)
      {
      for(int x_zone=1; x_zone<=n_zones_x; x_zone++)
	{
	for(int y_zone=1;y_zone<=n_zones_y; y_zone++)
	  {
	  if(Ev_reco >= x_zone_edge[x_zone-1] && Ev_reco < x_zone_edge[x_zone]  && y_reco >= y_zone_edge[y_zone-1] && y_reco < y_zone_edge[y_zone])
	    {
	    zone_x_values[x_zone-1][y_zone-1].push_back(Ev_reco);
	    zone_y_values[x_zone-1][y_zone-1].push_back(y_reco);
	    }
	  }
	}
      }
    }//end of loop over events

  for(int x_zone=0; x_zone<=n_zones_x; x_zone++)
    {
    for(int y_bin=1; y_bin<=n_bins_y; y_bin++)
      zone_bin_edge_x[x_zone*n_bins_x/n_zones_x][y_bin-1] = x_zone_edge[x_zone];
    }

  for(int y_zone=0; y_zone<=n_zones_y; y_zone++)
    {
    for(int x_bin=1; x_bin<=n_bins_x; x_bin++)
      zone_bin_edge_y[x_bin-1][y_zone*n_bins_y/n_zones_y] = y_zone_edge[y_zone];
    }


  for(int x_zone=1; x_zone<=n_zones_x; x_zone++)
    {
    for(int y_zone=1;y_zone<=n_zones_y; y_zone++)
      {
      
      sort(zone_x_values[x_zone-1][y_zone-1].begin(), zone_x_values[x_zone-1][y_zone-1].end());
      for(int x_edge=1; x_edge<n_bins_x/n_zones_x; x_edge++)
	{
	valueiter = zone_x_values[x_zone-1][y_zone-1].begin() + (int)(x_edge * zone_x_values[x_zone-1][y_zone-1].size() * n_zones_x / n_bins_x);
	for(int y_bin=((y_zone-1)*n_bins_y/n_zones_y); y_bin<y_zone*n_bins_y/n_zones_y; y_bin++)
	  zone_bin_edge_x[x_edge+((x_zone-1)*n_bins_x/n_zones_x)][y_bin] = (*valueiter);
	}
	  
       sort(zone_y_values[x_zone-1][y_zone-1].begin(), zone_y_values[x_zone-1][y_zone-1].end());
       for(int y_edge=1; y_edge<n_bins_y/n_zones_y; y_edge++)
	 {
	 valueiter = zone_y_values[x_zone-1][y_zone-1].begin() + (int)(y_edge * zone_y_values[x_zone-1][y_zone-1].size() * n_zones_y / n_bins_y);
	 for(int x_bin=((x_zone-1)*n_bins_x/n_zones_x);x_bin<x_zone*n_bins_x/n_zones_x;x_bin++)
           zone_bin_edge_y[x_bin][y_edge+((y_zone-1)*n_bins_y/n_zones_y)] = (*valueiter);

	 }      
       }
    }

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

   cout<<"Exact bin edges in Ev_reco have "<<n_zones_y<<" zones with "<<n_bins_x<<" bins in each zone:"<<endl;
   cout<<endl;
   cout<<"static const int kNYrecoZones = "<<n_zones_y<<";"<<endl;
   cout<<"static const int kNErecoBins = "<<n_bins_x<<";"<<endl;
   cout<<"static const double kErecoBinEdges[kNYrecoZones][kNErecoBins+1] = "<<endl;
   cout<<"{"<<endl;
   for(int y_bin=0; y_bin<n_bins_y; y_bin+=n_bins_y / n_zones_y)
     {
     cout<<"{";
     for(int x_bin=0; x_bin<=n_bins_x; x_bin++)
       {
       if(x_bin==0)
	 cout<<zone_bin_edge_x[x_bin][y_bin];
       else
	 cout<<","<<zone_bin_edge_x[x_bin][y_bin];
       }
     if(y_bin>=(n_zones_y-1)*n_bins_y/n_zones_y)
       cout<<"}"<<endl;
     else
       cout<<"},"<<endl;
     }
   cout<<"};"<<endl;

   cout<<endl;
   cout<<endl;

   cout<<"Exact bin edges in y_reco have "<<n_zones_x<<" zones with "<<n_bins_y<<" bins in each zone:"<<endl;
   cout<<endl;

   cout<<"static const int kNErecoZones = "<<n_zones_x<<";"<<endl;
   cout<<"static const int kNYrecoBins = "<<n_bins_y<<";"<<endl;
   cout<<"static const double kErecoBinEdges[kNErecoZones][kNYrecoBins+1] = "<<endl;
   cout<<"{"<<endl;
   for(int x_bin=0; x_bin<n_bins_x; x_bin+=n_bins_x / n_zones_x)
     {
     cout<<"{";
     for(int y_bin=0; y_bin<=n_bins_y; y_bin++)
       {
       if(y_bin==0)
	 cout<<zone_bin_edge_y[x_bin][y_bin];
       else
	 cout<<","<<zone_bin_edge_y[x_bin][y_bin];
       }
     if(x_bin>=(n_zones_x-1)*n_bins_x/n_zones_x)
       cout<<"}"<<endl;
     else
       cout<<"},"<<endl;
     }
     cout<<"};"<<endl;

   cout<<endl;
   cout<<endl;

   if(round_x_bin_edges_to_nearest > 0.0)
     {
     for(int x_bin=0; x_bin<=n_bins_x; x_bin++)
       {
       for(int y_bin=0; y_bin<n_bins_y; y_bin++)
         {
         zone_bin_edge_x[x_bin][y_bin] = round(zone_bin_edge_x[x_bin][y_bin], round_x_bin_edges_to_nearest);
         //prevent successive bin edges being rounded to same value 
         if(x_bin > 0)
	   {
	   if(zone_bin_edge_x[x_bin][y_bin] - zone_bin_edge_x[x_bin-1][y_bin] < round_y_bin_edges_to_nearest / 100.0)
	     zone_bin_edge_x[x_bin][y_bin] = zone_bin_edge_x[x_bin-1][y_bin] + round_x_bin_edges_to_nearest;
	   }
         }
       }
     }

   if(round_y_bin_edges_to_nearest > 0.0)
     {
     for(int x_bin=0; x_bin<n_bins_x; x_bin++)
       {
       for(int y_bin=0; y_bin<=n_bins_y; y_bin++)
         {
         zone_bin_edge_y[x_bin][y_bin] = round(zone_bin_edge_y[x_bin][y_bin], round_y_bin_edges_to_nearest);
	 //prevent successive bin edges being rounded to same value
	 if(y_bin > 0)
           {
           if(zone_bin_edge_y[x_bin][y_bin] - zone_bin_edge_y[x_bin][y_bin-1] < round_y_bin_edges_to_nearest / 100.0)
             zone_bin_edge_y[x_bin][y_bin] = zone_bin_edge_y[x_bin][y_bin-1] + round_y_bin_edges_to_nearest;
           }
         }
       }
     }

   cout<<"After rounding, bin edges in Ev_reco have "<<n_zones_y<<" zones with "<<n_bins_x<<" bins in each zone:"<<endl;
   cout<<endl;
   cout<<"static const int kNYrecoZones = "<<n_zones_y<<";"<<endl;
   cout<<"static const int kNErecoBins = "<<n_bins_x<<";"<<endl;
   cout<<"static const double kErecoBinEdges[kNYrecoZones][kNErecoBins+1] = "<<endl;
   cout<<"{"<<endl;
   for(int y_bin=0; y_bin<n_bins_y; y_bin+=n_bins_y / n_zones_y)
     {
     cout<<"{";
     for(int x_bin=0; x_bin<=n_bins_x; x_bin++)
       {
       if(x_bin==0)
	 cout<<zone_bin_edge_x[x_bin][y_bin];
       else
	 cout<<","<<zone_bin_edge_x[x_bin][y_bin];
       }
     if(y_bin>=(n_zones_y-1)*n_bins_y/n_zones_y)
       cout<<"}"<<endl;
     else
       cout<<"},"<<endl;
     }
   cout<<"};"<<endl;

   cout<<endl;
   cout<<endl;

   cout<<"After rounding, bin edges in y_reco have "<<n_zones_x<<" zones with "<<n_bins_y<<" bins in each zone:"<<endl;
   cout<<endl;

   cout<<"static const int kNErecoZones = "<<n_zones_x<<";"<<endl;
   cout<<"static const int kNYrecoBins = "<<n_bins_y<<";"<<endl;
   cout<<"static const double kErecoBinEdges[kNErecoZones][kNYrecoBins+1] = "<<endl;
   cout<<"{"<<endl;
   for(int x_bin=0; x_bin<n_bins_x; x_bin+=n_bins_x / n_zones_x)
     {
     cout<<"{";
     for(int y_bin=0; y_bin<=n_bins_y; y_bin++)
       {
       if(y_bin==0)
	 cout<<zone_bin_edge_y[x_bin][y_bin];
       else
	 cout<<","<<zone_bin_edge_y[x_bin][y_bin];
       }
     if(x_bin>=(n_zones_x-1)*n_bins_x/n_zones_x)
       cout<<"}"<<endl;
     else
       cout<<"},"<<endl;
     }
   cout<<"};"<<endl;

   cout<<endl;
   cout<<endl;

   /*     
   cout<<"All the bin edges in x (ordered in the way they appear if the histogram is drawn) are:"<<endl;
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

   cout<<"All the bin edges in y (ordered in the way they appear if the histogram is drawn) are:"<<endl;
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
   */

   dev_sq_sum = 0.0;

   cout<<"Bin contents with "<<n_zones_x<<" zones in x and "<<n_zones_y<<" zones in y are:"<<endl;
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
   cout<<endl;
   cout<<"Standard deviation of bin contents with "<<n_zones_x<<" zones in x and "<<n_zones_y<<" zones in y is "<<sqrt(dev_sq_sum / ((n_bins_x * n_bins_y) - 1))<<endl;

   cout<<endl;
   cout<<endl;
  
}//end of make_binning_scheme_2D()

double round(double bin_edge, double round_value)
{
  double test_value = (((int)(bin_edge / round_value)) - 1) * round_value;
  while(test_value <= bin_edge + round_value)
    {
    test_value += round_value;
    if(fabs(bin_edge - test_value) <= 0.5 * round_value)
      return test_value;
    }
}
