//#define _debug_
#include "TFile.h"
#include "TH2D.h"
#include <iostream>
using namespace std;
// The macro takes a \Delta\chi^2 surface, as a function of (x,y) from the
// input ROOT file, finds the bin that corresponds to the input (xin,yin),
// applies the input \Delta\chi^2_{critical} to find an exlusion limit
// (at the desired CL) in (x,y), and checks whether the current bin is within
// a distance of nbins bins on the right of that line (along the x axis).
// It return 1 if yes, 0 if not.
//

int bin_is_narrowly_excluded(
  string dchisqsurf_filename, // name of ROOT file containing a \Delta\chi^2 surface
  string dchisqsurf_th2dname, // name of TH2D object representing a \Delta\chi^2 surface
  double dchisq_critical,     // \Delta\chi^2 critical: specifies CL for exclusion limit
  double xin,                 // input x value (in)
  double yin,
  int    nbins
)
{
  // Get \Delta\chi^2 surface
  TFile f(dchisqsurf_filename.c_str(),"READ");
  TH2D * dchisqsurf = (TH2D*) f.Get(dchisqsurf_th2dname.c_str());
  if(!dchisqsurf) {
    cerr << "No T2HD object named: " << dchisqsurf_th2dname
         << ", in: " << dchisqsurf_filename << endl;
    return 0;
  }

  // Find bin correponding to input (x,y) point
  int ixin = dchisqsurf->GetXaxis()->FindBin(xin);
  int iyin = dchisqsurf->GetYaxis()->FindBin(yin);
#ifdef _debug_
  cout << "Input x = " << xin << " is at x-axis bin = " << ixin << endl;
  cout << "Input y = " << yin << " is at y-axis bin = " << iyin << endl;
#endif

  // Check whether the current bin in narrowly excluded
  // (and, therefore, keep to investigate again, as it likely to be included
  //  in an analysis variant with degraded sensitivity)
  int keep = 0;

  int nx = dchisqsurf->GetXaxis()->GetNbins();
#ifdef _debug_
  cout << "Scanning: " << nx
       << " x-axis bins (at fixed y-axis bin " << iyin << ")"<< endl;
#endif
  int nbins_dist=-1;
  for(int ix=1; ix <= nx; ix++) {
    double dchisq = dchisqsurf->GetBinContent(ix,iyin);
#ifdef _debug_
    cout << "Delta\\chisq(" << ix << ", " << iyin << ") =  " << dchisq << endl;
#endif
    if(dchisq >= dchisq_critical) {
      // once in excluded region, start counting bins
      nbins_dist++;
#ifdef _debug_
      cout << "... in excluded region (distance from bin of exclusion limit = "
           << nbins_dist << " bins)" << endl;
#endif
      // if you find the input bin, check distance from the start of exclusion zone
      if(ix==ixin) {
        if(nbins_dist < nbins) {
           keep = 1;
           break;
        }
      }
    }
  }

  cout << "Keeping current bin (" << ixin << ", " << iyin
       << ") as a \"narrowly excluded\" one? "
       << ((keep == 1) ? "True" : "False") << endl;

  return keep;
}
//------------------------------------------------------------------------------


