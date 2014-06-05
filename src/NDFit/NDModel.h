//____________________________________________________________________________
/*!

\class     valor::NDModel

\brief     LBNE ND Model class. Derives from FitModelABC

\author    Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
           University of Liverpool & STFC Rutherford Appleton Laboratory

           George Christodoulou <georgios \at hep.ph.liv.ac.uk>
           University of Liverpool

           Nick Grant <n.grant \at lancaster.ac.uk>
           University of Lancaster

\copyright (c) 2010-2014, The VALOR group

*/
//____________________________________________________________________________

#ifndef _valor_lbnx_nd_model_h_
#define _valor_lbnx_nd_model_h_

#include <string>
#include <TObjArray.h>
#include <TTree.h>

//fmwk
#include "FitCore/FitModelABC.h"
#include "FitCore/PhysHypothesis.h"
#include "FitCore/PhysParamList.h"
#include "Utilities/VALORArray.h"
//lbnx
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
  bool          Generate               (const PhysHypothesis & ph);
  void          RandomizeSystematics   (void);
  void          TweakSystematic        (string syst_name, double twkdial=0., Option_t * opt = 0); 
  void          TweakSystematic        (conv::PhysParamId_t syst, double twkdial=0., Option_t * opt = 0);
  void          ResetSystematics       (void);  
  void          PrintSystematics       (ostream & stream = std::cout) const;
  PhysParamList Tweaks                 (void);
  bool          Generate               (const FitParamList & fp);
  bool          Write                  (TObjArray * collection, const char * tag = "model", Option_t * write_opt = 0);
  bool          Write                  (const char * filename,  const char * tag = "model", Option_t * write_opt = 0, Option_t * file_opt = 0);
  double        GetFitStatisticPenalty (Option_t * opt = 0) const;

private:

  void Init  (void);
  void Book  (void);
  void Clean (void);
  void Zero  (void);

  void FillTemplates    (TTree * t, int ibeam);
  void ApplyTuning      (void);
  void ApplySystematics (void);
  void ApplyPhysics     (void);
  void CalcPDFs         (void);

  util::NDArrIdx * fArrIdx;

  PhysHypothesis fPhysHypothesis;

  // Exposure (assumed) for each beam configuration (in POT)
  double fPOT [conv::kNBeamConf];

  // MC templates (MCT) 
  // Each template is (currently always) a 3-D Nev = Nev(Enu_reco, y_reco, Enu_true) array.
  // There is a template for all beams/samples/reac_modes/bin_zone combinations.
  // Four types of MC templates are constructed:
  // - nom: Nominal MC 
  // - tun: Nominal MC + Ext. tuning (eg tuning based on *external* hadro-production or neutrino cross-section data)
  // - sys: Nominal MC + Ext. tuning + Systematic param variations
  // - fin: Nominal MC + Ext. tuning + Systematic param variations + Physics param variations
  // Note: 
  // The language/convention above (nom, tun, sys, fin) derives from our oscillation analysis.
  // All parameters we are handling here are "systematics" from the oscilation analysis point of view.
  // However, the following distrinction is made:
  // - Systematics "systematics". These are the ones we marginalize (eg detector systematics, uncorrelated cross-sections). 
  //   The effect of their variation is included in the sys templates.
  // - Physics "systematics" are the ones we attempt to constrain and are included in the output covariance matrix (eg. 
  //   correlated flux and cross-sections). The effect of their variation is included in the fin templates.
  VALORArray * fMCTNom  [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones]; 
  VALORArray * fMCTTun  [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones]; 
  VALORArray * fMCTSys  [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones]; 
  VALORArray * fMCTFin  [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones]; 

  // MC PDFs
  // Each PDF is (currently always) a 2-D Nev = Nev(Enu_reco, y_reco) array that can be directly compared with data.
  // The PDFs are computed from the `fin' MC templates, integrated over true kinematic variables, and include all effects.
  // There is a PDF for all beams/samples/reac_modes/bin_zones combinations.
  // The `Tot' versions are integrated over the true reac_modes and can be used for comparisons with data.
  VALORArray * fMCPDFTot  [conv::kNBeamConf][conv::kNNDSamples][conv::kNMaxBinZones];                    // total
  VALORArray * fMCPDFComp [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones]; // reac_mode components

  // Keep track of null MC templates and total PDFs
  bool fNullMC     [conv::kNBeamConf][conv::kNNDSamples][conv::kNReacModes][conv::kNMaxBinZones];
  bool fNullPDFTot [conv::kNBeamConf][conv::kNNDSamples][conv::kNMaxBinZones];

  //
  double fSystCurrValues[];

  // Input VALOR MC DSTs
  bool fUseMCDST;
  TTree * fMCDST[conv::kNBeamConf];
};

} // valor

#endif

