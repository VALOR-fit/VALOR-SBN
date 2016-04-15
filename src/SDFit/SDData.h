//____________________________________________________________________________
/*!

\class     valor::SDData

\brief     VALOR single detector data class. 
           Derives from FitDataABC

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\created   March 27, 2014

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_single_detector_data_h_
#define _valor_single_detector_data_h_

// system
#include <string>
// fmwk
#include "FitCore/FitDataABC.h"
#include "VArray/VALORArray.h"
// dune
#include "Conventions/BeamConf.h"
#include "Conventions/Sample.h"
#include "Conventions/SampleKineBinning.h"
#include "Conventions/SampleReacMode.h"

class TObjArray;
class TH1D;

using namespace valor;

namespace valor {

class SDData: public FitDataABC
{
public:
  SDData();
  virtual ~SDData();

  //
  // Implement the FitDataABC interface
  // See FitDataABC for method decription
  //

  string Name            (void) const;
  bool   Read            (string file, Option_t * opt = 0);
  bool   Generate        (FitModelABC * pred, const FitParamList & fp,   bool fluctuate=true);
  bool   Generate        (FitModelABC * pred, const PhysHypothesis & ph, bool fluctuate=true);
  bool   Generate        (FitModelABC * pred, bool fluctuate=true);
  bool   Write           (TObjArray * data_collection, const char * tag = "data", Option_t * write_opt = 0);
  bool   Write           (const char * filename, const char * tag = "data", const char * option_file="update", Option_t * file_opt = 0);
  int    NumOfBins       (Option_t * opt = 0) const;
  double GetFitStatistic (FitModelABC * pred, const FitParamList & fp,   Option_t * opt = "likelihood-ratio");
  double GetFitStatistic (FitModelABC * pred, const PhysHypothesis & ph, Option_t * opt = "likelihood-ratio");
  double GetFitStatistic (FitModelABC * pred, Option_t * opt = "likelihood-ratio");

private:

  void Init  (void);
  void Book  (void);
  void Clean (void);
  void Zero  (Option_t * opt);

  // Data distributions:
  // Each distribution is (currently always) a 2-D Nev = Nev(Enu_reco, y_reco) array that can be directly compared with data.
  // There is a distribution for all beam/sample/bin_zone combinations.
  //
  // Distributions with binning heavily optimized to reduce the CPU intensity of the fit.
  bool         fDataNull   [conv::kNBeamConf][conv::kNSamples][conv::kNMaxBinZones]; 
  VALORArray * fData       [conv::kNBeamConf][conv::kNSamples][conv::kNMaxBinZones]; 
  // Below are versions the use a simple (~fine and ~regular) binning throughout the whole range.
  bool         fDataSbNull [conv::kNBeamConf][conv::kNSamples]; 
  VALORArray * fDataSb     [conv::kNBeamConf][conv::kNSamples]; 
};

} // valor

#endif

