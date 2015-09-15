//____________________________________________________________________________
/*!

\class     valor::NDData

\brief     LBNE ND Data class. Derives from FitDataABC

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           George Christodoulou <georgios \at hep.ph.liv.ac.uk>
           University of Liverpool

           Nick Grant <nick.grant \at stfc.ac.uk>
           University of Warwick

\created   March 27, 2014

\copyright (c) 2010-2015, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_lbnx_nd_data_h_
#define _valor_lbnx_nd_data_h_

#include <string>

//fmwk
#include "FitCore/FitDataABC.h"
#include "Utilities/VALORArray.h"

//lbnx
#include "Conventions/BeamConf.h"
#include "NDFit/NDArrIdx.h"
#include "NDFit/NDSample.h"
#include "NDFit/NDSampleBinning.h"
#include "NDFit/NDSampleModes.h"

class TObjArray;
class TH1D;

using namespace valor;

namespace valor {

class NDData: public FitDataABC
{
public:
  NDData();
  virtual ~NDData();

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

  // Data distributions:
  // Each distribution is (currently always) a 2-D Nev = Nev(Enu_reco, y_reco) array that can be directly compared with data.
  // There is a distribution for all beam/sample/bin_zone combinations.
  //
  // Distributions with binning heavily optimized to reduce the CPU intensity of the fit.
  bool         fDataNull   [conv::kNBeamConf][conv::kNNDSamples][conv::kNMaxBinZones]; 
  VALORArray * fData       [conv::kNBeamConf][conv::kNNDSamples][conv::kNMaxBinZones]; 
  // Below are versions the use a simple (~fine and ~regular) binning throughout the whole range.
  bool         fDataSbNull [conv::kNBeamConf][conv::kNNDSamples]; 
  VALORArray * fDataSb     [conv::kNBeamConf][conv::kNNDSamples]; 
};

} // valor

#endif

