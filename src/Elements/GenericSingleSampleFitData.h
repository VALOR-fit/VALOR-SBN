//____________________________________________________________________________
/*!

\class     valor::GenericSingleSampleFitData

\brief     A generic class for storing data for a single sample, 
           in a specific beam configuration and for a specific detector.
           //
           // Some description about what info is stored for the sample
           //
           Derives from FitDataABC

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           Steve Dennis <s.r.dennis@liverpool.ac.uk>
           University of Liverpool

\created   March 27, 2014

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_generic_single_sample_data_h_
#define _valor_generic_single_sample_data_h_

#include <string>

//fmwk
#include "VArray/VALORArray.h"
//dune
#include "Conventions/BeamConf.h"
#include "Conventions/Sample.h"
#include "Conventions/Detector.h"
#include "Conventions/SampleKineBinning.h"
#include "Conventions/SampleReacMode.h"
#include "Conventions/ArrIdx.h"
#include "Elements/SingleSampleFitDataABC.h"

class TObjArray;
class TH1D;

using std::string;
using namespace valor;

namespace valor {

class GenericSingleSampleFitData: public SingleSampleFitDataABC
{
public:
  GenericSingleSampleFitData(void);
  virtual ~GenericSingleSampleFitData();

  //
  // Implement the FitDataABC interface
  // See FitDataABC for method decription
  //

  string Name           (void);
  bool   Read           (string file, Option_t * opt = 0);
  bool   Generate       (FitModelABC * pred, const FitParamList & fp,   bool fluctuate=true);
  bool   Generate       (FitModelABC * pred, const PhysHypothesis & ph, bool fluctuate=true);
  bool   Generate       (FitModelABC * pred, bool fluctuate=true);
  bool   Write          (TObjArray * data_collection, const char * tag = "data", Option_t * write_opt = 0);
  bool   Write          (const char * filename, const char * tag = "data", const char * option_file="update", Option_t * file_opt = 0);
  int    NumOfBins      (void);
  double Statistic      (FitModelABC * pred, const FitParamList & fp,   Option_t * opt = "likelihood-ratio");
  double Statistic      (FitModelABC * pred, const PhysHypothesis & ph, Option_t * opt = "likelihood-ratio");
  double Statistic      (FitModelABC * pred, Option_t * opt = "likelihood-ratio");

private:

  void Init  (void);
  void Book  (void);
  void Clean (void);
  void Zero  (Option_t * opt);

  // Name of this VALOR fit dataset (see Conventions/Names.h)
  string fName;

  // Data distributions:
  // Each distribution is (currently always) a 2-D Nev = Nev(Enu_reco, y_reco) array that can be directly compared with data.
  // There is a distribution for all beam/sample/bin_zone combinations.
  //
  // Distributions with binning heavily optimized to reduce the CPU intensity of the fit.
  bool         fDataObNull   [conv::kNMaxBinZones]; 
  VALORArray * fDataOb       [conv::kNMaxBinZones]; 
  // Below are versions the use a simple (~fine and ~regular) binning throughout the whole range.
  bool         fDataSbNull; 
  VALORArray * fDataSb; 
};

} // valor

#endif

