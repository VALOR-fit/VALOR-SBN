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
#include "valor/FitCore/PhysHypothesis.h"
#include "valor/Oscillation/NuOsc3Flavour.h"
#include "valor/FitCore/PhysParamList.h"
#include "valor/FitCore/CorrelatedSystematics.h"
#include "valor/VArray/VALORArray.h"
#include "valor/VArray/VALORArrayBin.h"

//dune
#include "valor/Conventions/Detector.h"
#include "valor/Conventions/BeamConf.h"
#include "valor/Conventions/Sample.h"
#include "dune/Conventions/SampleReacMode.h"
#include "dune/Conventions/FitParam.h"
#include "dune/Conventions/ArrIdx.h"
#include "dune/Utilities/DuneRFL.h"
#include "dune/Elements/SingleSampleFitModelABC.h"
#include "dune/Utilities/SingleSampleKineBinning.h"


using std::string;

namespace valor {

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

  string        Name                   (void) const;
  bool          Read                   (string file, Option_t * opt = 0);
  virtual bool Read(std::ifstream& stream, Option_t* read_opt = 0);
  bool          Generate               (const PhysHypothesis & ph, Option_t * opt = 0);
  void          RandomizeSystematics   (Option_t * opt = 0);
  void          RandomizeSystematics   (bool (*should_randomize)(conv::PhysParamId_t), Option_t * opt = 0);
  void          RandomizeSystematics   (std::map<valor::conv::PhysParamId_t, bool> should_randomize, Option_t * opt = 0);
  void          TweakSystematic        (string syst_name, double twkdial=0., Option_t * opt = 0); 
  void          TweakSystematic        (conv::PhysParamId_t syst, double twkdial=0., Option_t * opt = 0);
  void          ResetSystematics       (Option_t * opt = 0);  
  void          PrintSystematics       (ostream & stream = std::cout, Option_t * opt = 0) const;
  PhysParamList Tweaks                 (Option_t * opt = 0) const;
  bool          Generate               (const FitParamList & fp, Option_t * opt = 0);
  bool          Write                  (TObjArray * collection, const char * tag = "model", Option_t * write_opt = 0);
  bool          Write                  (const char * filename,  const char * tag = "model", Option_t * write_opt = 0, Option_t * file_opt = 0);
  virtual bool Write(std::ofstream& stream, Option_t* write_opt = 0);
  double        GetFitStatisticPenalty (Option_t * opt = 0) const;
  
  void          SetSystConf            (CorrelatedSystematics * syst, Option_t * opt = "");
  CorrelatedSystematics *       GetSystematics(Option_t * opt = "");
  const CorrelatedSystematics * GetSystematics(Option_t * opt = "") const;

  //
  // Auxiliary methods, not part of the  FitModelABC interface (needed?)
  //
  
  // Get the response function library and binning
  const util::DuneRFL * GetRFL(void) const;
  const SingleSampleKineBinning * GetBinning(void) const;
  
  PhysParamList OneSigmaErrors (Option_t * opt = "");
//  TMatrixD CovarianceMatrix(Option_t * opt = "");

  // Calculate the OB manually from the content of the simple bins. Can be used to verify the spectra are the same for SB/OB
  void UpdateObservableBinningFromSimple (Option_t * opt = 0);

private:

  void Init  (void);
  void Book  (void);
  void Clean (void);
  void Zero  (void);
  void FillFromDST  (TTree * t);
  bool FillFromTemplateFile (TFile * f, std::string tag, double desired_POT); // If desired_POT is a positive number, assume template being read is 1E21 and reweight accordingly.
  bool FillSplines(string file, Option_t * opt);

  void ApplyTuning                       (Option_t * opt = 0);
  void FluctuateMCStat                   (Option_t * opt = 0);
  void ApplySystematics                  (Option_t * opt = 0);
  void ApplyPhysics                      (Option_t * opt = 0);
  void ApplyOscProb                      (Option_t * opt = 0);
  void UpdatePDFs                        (Option_t * opt = 0);

  const util::ArrIdx * fArrIdx;
  
  // Keep track of the parameters we need to loop over
  std::vector<conv::PhysParamId_t> fParams;
  // Normalisation and spline parameters divided
  std::vector<conv::PhysParamId_t> fNormParams;
  std::vector<conv::PhysParamId_t> fSplineParams;
  
  // Cache whether each parameter is applied to each entry
  std::vector<bool> fParamIsAppliedTo      [conv::kNReacModes];
  std::vector<bool> fNormParamIsAppliedTo  [conv::kNReacModes];
  std::vector<bool> fSplineParamIsAppliedTo[conv::kNReacModes];
  
  NuOsc3Flavour  fNuOsc3Flavour;
  PhysHypothesis fPhysHypothesis;

  // Name of this VALOR fit model (see Conventions/Names.h)
  string fName;

  // Exposure for corresponding sample (in POT)
  double fPOT;

  // Fiducial mass (ktonnes)
  double fFiducialMass;

  // Input VALOR MC DSTs
  bool fUseMCDST;
  
  // MC templates (MCT) 
  // Each template is a 2D array, with (reco,true) bins linearised in whatever kinematic space we need.
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
  bool         fMCTNullOb [conv::kNReacModes];
  VALORArray * fMCTNomOb  [conv::kNReacModes]; 
  VALORArray * fMCTTunOb  [conv::kNReacModes]; 
  VALORArray * fMCTSysOb  [conv::kNReacModes]; 
  VALORArray * fMCTFinOb  [conv::kNReacModes]; 
  VALORArray * fMCStatOb  [conv::kNReacModes]; // MC statistics
  
  // We'll keep our response function pointers in a VALORArray of longs.
  // If we move to C++ 11, should use intptr_t instead.
  // This has an extra dimension above those  in the arrays above - parameter
  VALORArrayL * fRFPtr[conv::kNReacModes];
  
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
  bool         fPDFTotNullOb;                     //
  VALORArray * fPDFTotOb    ;                     // total
  VALORArray * fPDFCompOb    [conv::kNReacModes]; // components
  // Below are PDFs versions the use a simple (~fine and ~regular) binning throughout the whole range.
  bool         fPDFTotNullSb;                     // 
  VALORArray * fPDFTotSb;                         // total
  VALORArray * fPDFCompSb    [conv::kNReacModes]; // components
  
  // Binning
  SingleSampleKineBinning * fBinning;
  
  // Spline library
  util::DuneRFL * fRFL;
  
  // Pointer to our systematics
  CorrelatedSystematics * fSystematics;
  bool fOwnerOfSystematics;
};

} // valor

#endif

