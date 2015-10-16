//____________________________________________________________________________
/*!

\class     valor::NDModel

\brief     VALOR?DUNE ND Model class. Derives from FitModelABC

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

\copyright (c) 2010-2015, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_dune_nd_model_h_
#define _valor_dune_nd_model_h_

#include <string>
#include <TObjArray.h>
#include <TTree.h>

//fmwk
#include "FitCore/FitModelABC.h"
#include "FitCore/PhysHypothesis.h"
#include "FitCore/PhysParamList.h"
#include "Utilities/VALORArray.h"
//dune
#include "Conventions/BeamConf.h"
#include "NDFit/NDArrIdx.h"
#include "NDFit/NDSample.h"
#include "NDFit/NDSampleBinning.h"
#include "NDFit/NDSampleModes.h"
#include "NDFit/NDFitParams.h"

namespace valor {

class NDModel: public FitModelABC
{
public:
  NDModel();
 ~NDModel();

  //
  // Implement the FitModelABC interface
  // See FitModelABC for method decription
  //

  string        Name                   (void);
  bool          Read                   (string file, Option_t * opt = 0);
  bool          Generate               (const PhysHypothesis & ph, Option_t * opt = 0);
  void          RandomizeSystematics   (void);
  void          TweakSystematic        (string syst_name, double twkdial=0., Option_t * opt = 0); 
  void          TweakSystematic        (conv::PhysParamId_t syst, double twkdial=0., Option_t * opt = 0);
  void          ResetSystematics       (void);  
  void          PrintSystematics       (ostream & stream = std::cout) const;
  PhysParamList Tweaks                 (void);
  bool          Generate               (const FitParamList & fp, Option_t * opt = 0);
  bool          Write                  (TObjArray * collection, const char * tag = "model", Option_t * write_opt = 0);
  bool          Write                  (const char * filename,  const char * tag = "model", Option_t * write_opt = 0, Option_t * file_opt = 0);
  double        GetFitStatisticPenalty (Option_t * opt = 0) const;

private:

  void Init  (void);
  void Book  (void);
  void Clean (void);
  void Zero  (void);
  void Fill  (TTree * t, int ibeam);

  void ApplyTuning      (void);
  void FluctuateMCStat  (Option_t * opt = 0);
  void ApplySystematics (Option_t * opt = 0);
  void ApplyPhysics     (Option_t * opt = 0);
  void UpdatePDFs       (Option_t * opt = 0);

  util::NDArrIdx * fArrIdx;

  PhysHypothesis fPhysHypothesis;

  // Exposure (assumed) for each beam configuration (in POT)
  double fPOT [conv::kNBeamConf];

  // Near detector fiducial mass (ktonnes)
  double fNDFiducialMass;

  // MC templates (MCT) 
  // Each template is (currently always) a 3-D Nev = Nev(Enu_reco, y_reco, Enu_true) array.
  // There is a template for all beam/sample/reac_mode combinations.
  // Four types of MC templates are constructed:
  // - nom: Nominal MC 
  // - tun: Nominal MC + Ext. tuning (eg tuning based on *external* hadro-production or neutrino cross-section data)
  // - sys: Nominal MC + Ext. tuning + Systematic param variations
  // - fin: Nominal MC + Ext. tuning + Systematic param variations + Physics param variations
  // All MC template contents are scaled to the desired data statistics.
  // We also construct an additional template with the MC statistics.
  // Note: 
  // The language/convention above (nom, tun, sys, fin) derives from our oscillation analysis.
  // All parameters we are handling here are "systematics" from the oscilation analysis point of view.
  // However, the following distrinction is made:
  // - Systematics "systematics". These are the ones we marginalize (eg detector systematics, uncorrelated cross-sections). 
  //   The effect of their variation is included in the sys templates.
  // - Physics "systematics" are the ones we attempt to constrain and are included in the output covariance matrix (eg. 
  //   correlated flux and cross-sections). The effect of their variation is included in the fin templates.
  //
  // Below are MCT with binning heavily optimized to reduce the CPU intensity of the fit.
  // A number of binning zones are defined, and in each zone a variable-size binning scheme is used.
  bool         fMCTNullOb [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones];
  VALORArray * fMCTNomOb  [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones]; 
  VALORArray * fMCTTunOb  [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones]; 
  VALORArray * fMCTSysOb  [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones]; 
  VALORArray * fMCTFinOb  [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones]; 
  VALORArray * fMCStatOb  [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones]; // MC statistics 
  // Below are MCT versions the use a simple (~fine and ~regular) binning throughout the whole range.
  // These templates are not used in the fit, but mainly for the visualization of the fit results.
  // As such, they are not all filled-in in each iteration of the fit but, typically, at the end of the fit or upon request.
  bool         fMCTNullSb [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes];
  VALORArray * fMCTNomSb  [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes]; 
  VALORArray * fMCTTunSb  [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes]; 
  VALORArray * fMCTSysSb  [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes]; 
  VALORArray * fMCTFinSb  [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes]; 
  VALORArray * fMCStatSb  [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes]; // MC statistics

  // MC PDFs
  // Each PDF is (currently always) a 2-D Nev = Nev(Enu_reco, y_reco) array that can be directly compared with data.
  // The PDFs are computed from the `fin' MC templates, integrated over true kinematic variables, and include all effects.
  // There is a PDF for all beams/samples/reac_modes/bin_zones combinations.
  // The `Tot' versions are integrated over the true reac_modes and can be used for comparisons with data.
  //
  // Below are PDFs with binning heavily optimized to reduce the CPU intensity of the fit.
  bool         fPDFTotNullOb [conv::kNBeamConf][conv::kNNDSamples][conv::kNMaxBinZones];                    //
  VALORArray * fPDFTotOb     [conv::kNBeamConf][conv::kNNDSamples][conv::kNMaxBinZones];                    // total
  VALORArray * fPDFCompOb    [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones]; // components
  // Below are PDFs versions the use a simple (~fine and ~regular) binning throughout the whole range.
  bool         fPDFTotNullSb [conv::kNBeamConf][conv::kNNDSamples];                    // 
  VALORArray * fPDFTotSb     [conv::kNBeamConf][conv::kNNDSamples];                    // total
  VALORArray * fPDFCompSb    [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes]; // components

  // Input VALOR MC DSTs
  bool fUseMCDST;
  TTree * fMCDST[conv::kNBeamConf];
};

} // valor

#endif

