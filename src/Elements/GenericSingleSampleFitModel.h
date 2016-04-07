//____________________________________________________________________________
/*!

\class     valor::GenericSingleSampleFitModel

brief      A generic implementation of the fit model for a single sample,
           in a specific beam configuration and for a specific detector.
           //
           // Some description about what info is stored for the sample
           //
           Derives from FitModelABC

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           Steve Dennis <s.r.dennis@liverpool.ac.uk>
           University of Liverpool

\copyright (c) 2010-2016, The VALOR Fitting Group, All Rights Reserved

*/
//____________________________________________________________________________

#ifndef _valor_generic_single_sample_model_h_
#define _valor_generic_single_sample_model_h_

#include <string>

#include <TMatrixD.h>
#include <TObjArray.h>
#include <TTree.h>

//fmwk
#include "FitCore/PhysHypothesis.h"
#include "FitCore/PhysParamList.h"
#include "FitCore/CorrelatedSystematics.h"
#include "Utilities/VALORArray.h"
//dune
#include "Conventions/Detector.h"
#include "Conventions/BeamConf.h"
#include "Conventions/Sample.h"
#include "Conventions/SampleKineBinning.h"
#include "Conventions/SampleReacMode.h"
#include "Conventions/FitParam.h"
#include "Conventions/ArrIdx.h"
#include "Elements/SingleSampleFitModelABC.h"

using std::string;

namespace valor {

// --------------------------------------
// abstract this  
//class NuFlux; // neutrino flux model systematics
//class NuInt;  // neutrino interaction model systematics
//class NuDet;  // neutrino detector model systematics
// --------------------------------------

class GenericSingleSampleFitModel: public SingleSampleFitModelABC
{
public:

  GenericSingleSampleFitModel();
  virtual ~GenericSingleSampleFitModel();

  //
  // Implement the FitModelABC interface
  // See FitModelABC for method decription
  //

  string        Name                   (void);
  bool          Read                   (string file, Option_t * opt = 0);
  bool          Generate               (const PhysHypothesis & ph, Option_t * opt = 0);
  void          RandomizeSystematics   (Option_t * opt = 0);
  void          TweakSystematic        (string syst_name, double twkdial=0., Option_t * opt = 0); 
  void          TweakSystematic        (conv::PhysParamId_t syst, double twkdial=0., Option_t * opt = 0);
  void          ResetSystematics       (Option_t * opt = 0);  
  void          PrintSystematics       (ostream & stream = std::cout, Option_t * opt = 0) const;
  PhysParamList Tweaks                 (void);
  bool          Generate               (const FitParamList & fp, Option_t * opt = 0);
  bool          Write                  (TObjArray * collection, const char * tag = "model", Option_t * write_opt = 0);
  bool          Write                  (const char * filename,  const char * tag = "model", Option_t * write_opt = 0, Option_t * file_opt = 0);
  double        GetFitStatisticPenalty (Option_t * opt = 0) const;

  //
  // Auxiliary methods, not part of the  FitModelABC interface (needed?)
  //
  
  PhysParamList OneSigmaErrors (Option_t * opt = "");
//  TMatrixD CovarianceMatrix(Option_t * opt = "");

  // ----------remove / using CorrelatedSystematics
  // NuFlux *       GetNuFlux (void);
  // const NuFlux * GetNuFlux (void) const;
  // NuInt *        GetNuInt  (void);
  // const NuInt *  GetNuInt  (void) const;
  // NuDet *        GetNuDet  (void);
  // const NuDet *  GetNuDet  (void) const;
  //-----------

private:

  void Init  (void);
  void Book  (void);
  void Clean (void);
  void Zero  (void);
  void FillFromDST  (TTree * t);
  bool FillFromTemplateFile (TFile * f, std::string tag);

  void ApplyTuning      (void);
  void FluctuateMCStat  (Option_t * opt = 0);
  void ApplySystematics (Option_t * opt = 0);
  void ApplyPhysics     (Option_t * opt = 0);
  void UpdatePDFs       (Option_t * opt = 0);

  const util::ArrIdx * fArrIdx;

  PhysHypothesis fPhysHypothesis;

  // Name of this VALOR fit model (see Conventions/Names.h)
  string fName;

  // Exposure for corresponding sample (in POT)
  double fPOT;

  // Fiducial mass (ktonnes)
  double fFiducialMass;

  // Input VALOR MC DSTs
  bool fUseMCDST;
  TTree * fMCDST;
  
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
  bool         fMCTNullOb [conv::kNReacModes][conv::kNMaxBinZones];
  VALORArray * fMCTNomOb  [conv::kNReacModes][conv::kNMaxBinZones]; 
  VALORArray * fMCTTunOb  [conv::kNReacModes][conv::kNMaxBinZones]; 
  VALORArray * fMCTSysOb  [conv::kNReacModes][conv::kNMaxBinZones]; 
  VALORArray * fMCTFinOb  [conv::kNReacModes][conv::kNMaxBinZones]; 
  VALORArray * fMCStatOb  [conv::kNReacModes][conv::kNMaxBinZones]; // MC statistics 
  // Below are MCT versions the use a simple (~fine and ~regular) binning throughout the whole range.
  // These templates are not used in the fit, but mainly for the visualization of the fit results.
  // As such, they are not all filled-in in each iteration of the fit but, typically, at the end of the fit or upon request.
  bool         fMCTNullSb [conv::kNReacModes];
  VALORArray * fMCTNomSb  [conv::kNReacModes]; 
  VALORArray * fMCTTunSb  [conv::kNReacModes]; 
  VALORArray * fMCTSysSb  [conv::kNReacModes]; 
  VALORArray * fMCTFinSb  [conv::kNReacModes]; 
  VALORArray * fMCStatSb  [conv::kNReacModes]; // MC statistics

  // MC PDFs
  // Each PDF is (currently always) a 2-D Nev = Nev(Enu_reco, y_reco) array that can be directly compared with data.
  // The PDFs are computed from the `fin' MC templates, integrated over true kinematic variables, and include all effects.
  // There is a PDF for all beams/samples/reac_modes/bin_zones combinations.
  // The `Tot' versions are integrated over the true reac_modes and can be used for comparisons with data.
  //
  // Below are PDFs with binning heavily optimized to reduce the CPU intensity of the fit.
  bool         fPDFTotNullOb [conv::kNMaxBinZones];                    //
  VALORArray * fPDFTotOb     [conv::kNMaxBinZones];                    // total
  VALORArray * fPDFCompOb    [conv::kNReacModes][conv::kNMaxBinZones]; // components
  // Below are PDFs versions the use a simple (~fine and ~regular) binning throughout the whole range.
  bool         fPDFTotNullSb;                     // 
  VALORArray * fPDFTotSb;                         // total
  VALORArray * fPDFCompSb    [conv::kNReacModes]; // components
  
  // Systematics
  //---------------- remove
  //valor::NuFlux * fNuFlux;
  //valor::NuInt *  fNuInt;
  //valor::NuDet *  fNuDet;
  //----------------
  CorrelatedSystematics * fSyst;
};

} // valor

#endif

