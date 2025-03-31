#include "sbnana/CAFAna/Core/Cut.h"
#include "sbnana/CAFAna/Core/ISyst.h"
#include "sbnana/CAFAna/Core/SpectrumLoader.h"
#include "sbnana/CAFAna/Core/Tree.h"
#include "sbnana/CAFAna/Core/Utilities.h"
#include "sbnana/CAFAna/Core/Var.h"

#include "sbnana/CAFAna/Systs/SBNWeightSysts.h"
#include "sbnana/CAFAna/Systs/SBNOnOffSysts.h"
#include "sbnana/CAFAna/Systs/UniverseOracle.h"
#include "sbnana/CAFAna/Systs/DetectorSysts.h"

#include "sbnana/SBNAna/Cuts/NumuCutsIcarus202401.h"
#include "sbnana/SBNAna/Vars/NumuVarsIcarus202401.h"

#include "sbnanaobj/StandardRecord/Proxy/SRProxy.h"

#include "TDirectory.h"
#include "TFile.h"
#include "Math/Vector3D.h"
#include "Math/VectorUtil.h"

#include <string>
#include <utility>
#include <vector>

using namespace ana;

std::vector<std::string> bound_at_neg2{
        "GENIEReWeight_SBN_v1_multisigma_NonRESBGvbarnCC1pi",
        "GENIEReWeight_SBN_v1_multisigma_NonRESBGvbarnCC2pi",
        "GENIEReWeight_SBN_v1_multisigma_NonRESBGvbarnNC1pi",
        "GENIEReWeight_SBN_v1_multisigma_NonRESBGvbarnNC2pi",
        "GENIEReWeight_SBN_v1_multisigma_NonRESBGvbarpCC1pi",
        "GENIEReWeight_SBN_v1_multisigma_NonRESBGvbarpCC2pi",
        "GENIEReWeight_SBN_v1_multisigma_NonRESBGvbarpNC1pi",
        "GENIEReWeight_SBN_v1_multisigma_NonRESBGvbarpNC2pi",
        "GENIEReWeight_SBN_v1_multisigma_NonRESBGvnCC1pi",
        "GENIEReWeight_SBN_v1_multisigma_NonRESBGvnCC2pi",
        "GENIEReWeight_SBN_v1_multisigma_NonRESBGvnNC1pi",
        "GENIEReWeight_SBN_v1_multisigma_NonRESBGvnNC2pi",
        "GENIEReWeight_SBN_v1_multisigma_NonRESBGvpCC1pi",
        "GENIEReWeight_SBN_v1_multisigma_NonRESBGvpCC2pi",
        "GENIEReWeight_SBN_v1_multisigma_NonRESBGvpNC1pi",
        "GENIEReWeight_SBN_v1_multisigma_NonRESBGvpNC2pi",
        "GENIEReWeight_SBN_v1_multisigma_NormCCMEC",
        "GENIEReWeight_SBN_v1_multisigma_NormNCMEC",
};


const Var kICARUS202401TrueLeadingProtonMomentum([] (const caf::SRSliceProxy* slc) {
  double protonE = -9999.;
  double protonMom = -9999.;
  for (auto& prim: slc->truth.prim) {
    if (prim.pdg==2212) {
      if (prim.startE > protonE) {
	protonMom = sqrt(prim.startp.x*prim.startp.x + prim.startp.y*prim.startp.y + prim.startp.z*prim.startp.z);
	protonE = prim.startE;
      }
    }
  }
  return protonMom;
});
  
const Var kICARUS202401TrueLeadingProtonCosTheta([] (const caf::SRSliceProxy* slc) {
  double protonE = -9999.;
  int nproton = 0;
  //Get neutrino direction
  ROOT::Math::XYZVector nuvec = ROOT::Math::XYZVector(slc->truth.momentum.x,slc->truth.momentum.y,slc->truth.momentum.z);
  ROOT::Math::XYZVector pvec(0.,0.,0.);
  for (auto& prim: slc->truth.prim) {
    if (prim.pdg==2212) {
      nproton++;
      if (prim.startE > protonE) {
	protonE = prim.startE;
	pvec = ROOT::Math::XYZVector(prim.startp.x,prim.startp.y,prim.startp.z);
      }
    }
  }
  double protoncosth = ROOT::Math::VectorUtil::CosTheta(nuvec,pvec);
  if (nproton < 1) {
    protoncosth = -9999.;
  }
  return protoncosth;
});


void make_tree()
{
  SpectrumLoader mc("/exp/icarus/data/users/jlarkin/updated_cv_*.flat.caf.root");
  SpectrumLoader offbeam("/pnfs/icarus/persistent/users/jlarkin/cafs/run2_offbeam_maj_*.flat.caf.root");
  
  const Var kTrueE = SIMPLEVAR(truth.E);
  const Var kTrueL = SIMPLEVAR(truth.baseline);
  const Var kTruePDG = SIMPLEVAR(truth.pdg);
  const Var kTrueCC = SIMPLEVAR(truth.iscc);
  const Var kRecoE = kIcarus202401RecoENu;
  const Var kPmu   = kIcarus202401RecoMuonP;
  const Var kCostmu([](const caf::SRSliceProxy *slc)->double{
    if(kIcarus202401MuonIdx(slc) < 0) return -2.0;
    return slc->reco.pfp.at(kIcarus202401MuonIdx(slc)).trk.costh;
  });

  const Cut kTrueNu = SIMPLEVAR(truth.index) >= 0;

  const SpillCut kSpillSelection = kIcarus202401CRTPMTVeto;
  const Cut kSliceSelection = kIcarus202401Contained1muNp;

  Tree nutree("selectedNu", {"trueE", "trueL", "truePDG", "CC", "recoE", "recoPmu", "recoCosthetamu", "trueLeadingPMom", "trueLeadingPCosTheta"}, mc, {kTrueE, kTrueL, kTruePDG, kTrueCC, kRecoE, kPmu, kCostmu, kICARUS202401TrueLeadingProtonMomentum, kICARUS202401TrueLeadingProtonCosTheta}, kSpillSelection, kSliceSelection && kTrueNu, kNoShift, true, true);
  Tree costree("selectedCos", {"recoE", "recoPmu", "recoCosthetamu"}, mc, {kRecoE, kPmu, kCostmu}, kSpillSelection, kSliceSelection && !kTrueNu, kNoShift, true, true);
  Tree offbeamTree("offbeam", {"recoE", "recoPmu", "recoCosthetamu"}, offbeam, {kRecoE, kPmu, kCostmu}, kSpillSelection, kSliceSelection, kNoShift, true, true);

  std::vector<std::string> genie_names = GetSBNGenieWeightNames();
  genie_names.push_back("ZExpPCAWeighter_SBNNuSyst_ZExpPCA_multisigma_b1");
  genie_names.push_back("ZExpPCAWeighter_SBNNuSyst_ZExpPCA_multisigma_b2");
  genie_names.push_back("ZExpPCAWeighter_SBNNuSyst_ZExpPCA_multisigma_b3");
  genie_names.push_back("ZExpPCAWeighter_SBNNuSyst_ZExpPCA_multisigma_b4");
  SBNWeightSyst b1("ZExpPCAWeighter_SBNNuSyst_ZExpPCA_multisigma_b1");
  SBNWeightSyst b2("ZExpPCAWeighter_SBNNuSyst_ZExpPCA_multisigma_b2");
  SBNWeightSyst b3("ZExpPCAWeighter_SBNNuSyst_ZExpPCA_multisigma_b3");
  SBNWeightSyst b4("ZExpPCAWeighter_SBNNuSyst_ZExpPCA_multisigma_b4");
  std::vector<const ISyst*> genie_systs = GetSBNGenieWeightSysts();
  genie_systs.push_back(&b1);
  genie_systs.push_back(&b2);
  genie_systs.push_back(&b3);
  genie_systs.push_back(&b4);
  std::vector<std::string> onoff_names = GetSBNOnOffNames();
  std::vector<const ISyst*> onoff_systs = GetSBNOnOffSysts();
  onoff_names.push_back("GENIEReWeight_SBNNuSyst_GENIE_multisigma_XSecShape_CCMEC");
  SBNOnOffSyst mecshape("GENIEReWeight_SBNNuSyst_GENIE_multisigma_XSecShape_CCMEC");
  onoff_systs.push_back(&mecshape);
  std::vector<std::string> nsigma_names = genie_names;
  std::vector<const ISyst*> nsigma_systs = genie_systs;
  for(const std::string &name: onoff_names) nsigma_names.push_back(name);
  for(const ISyst *s: onoff_systs) nsigma_systs.push_back(s);
  std::vector<std::pair<int, int>> min_max;
  for(size_t i = 0; i < genie_names.size(); ++i) min_max.emplace_back(-3, 3);
  for(size_t i = 0; i < onoff_names.size(); ++i) min_max.emplace_back(0, 1);
  for(size_t i = 0; i < genie_names.size(); ++i) {
    if(std::find(bound_at_neg2.begin(), bound_at_neg2.end(), genie_names[i]) != bound_at_neg2.end())
      min_max[i] = std::make_pair(-2, 3);
  }

  NSigmasTree nsigtree("multisigmaTree", nsigma_names, mc, nsigma_systs, min_max, kSpillSelection, kSliceSelection && kTrueNu, kNoShift, true, true);

  const std::vector<std::string> flux_names{ "expskin_Flux", "horncurrent_Flux", "nucleoninexsec_Flux", "nucleonqexsec_Flux", "nucleontotxsec_Flux", "pioninexsec_Flux", "pionqexsec_Flux", "piontotxsec_Flux", "piplus_Flux", "piminus_Flux", "kplus_Flux", "kminus_Flux", "kzero_Flux" };
  const std::vector<std::string> xsec_multisim_names{
    "GENIEReWeight_SBN_v1_multisim_ZExpAVariationResponse",
    "GENIEReWeight_SBN_v1_multisim_RPA_CCQE",
    "GENIEReWeight_SBN_v1_multisim_CoulombCCQE",
    "GENIEReWeight_SBN_v1_multisim_NormCCMEC",
    "GENIEReWeight_SBN_v1_multisim_NormNCMEC",
    "GENIEReWeight_SBN_v1_multisim_NCELVariationResponse",
    "GENIEReWeight_SBN_v1_multisim_CCRESVariationResponse",
    "GENIEReWeight_SBN_v1_multisim_NCRESVariationResponse",
    "GENIEReWeight_SBN_v1_multisim_NonRESBGvpCC1pi",
    "GENIEReWeight_SBN_v1_multisim_NonRESBGvpCC2pi",
    "GENIEReWeight_SBN_v1_multisim_NonRESBGvpNC1pi",
    "GENIEReWeight_SBN_v1_multisim_NonRESBGvpNC2pi",
    "GENIEReWeight_SBN_v1_multisim_NonRESBGvnCC1pi",
    "GENIEReWeight_SBN_v1_multisim_NonRESBGvnCC2pi",
    "GENIEReWeight_SBN_v1_multisim_NonRESBGvnNC1pi",
    "GENIEReWeight_SBN_v1_multisim_NonRESBGvnNC2pi",
    "GENIEReWeight_SBN_v1_multisim_NonRESBGvbarpCC1pi",
    "GENIEReWeight_SBN_v1_multisim_NonRESBGvbarpCC2pi",
    "GENIEReWeight_SBN_v1_multisim_NonRESBGvbarpNC1pi",
    "GENIEReWeight_SBN_v1_multisim_NonRESBGvbarpNC2pi",
    "GENIEReWeight_SBN_v1_multisim_NonRESBGvbarnCC1pi",
    "GENIEReWeight_SBN_v1_multisim_NonRESBGvbarnCC2pi",
    "GENIEReWeight_SBN_v1_multisim_NonRESBGvbarnNC1pi",
    "GENIEReWeight_SBN_v1_multisim_NonRESBGvbarnNC2pi",
    "GENIEReWeight_SBN_v1_multisim_COHVariationResponse",
    "GENIEReWeight_SBN_v1_multisim_DISBYVariationResponse",
    "GENIEReWeight_SBN_v1_multisim_FSI_pi_VariationResponse",
    "GENIEReWeight_SBN_v1_multisim_FSI_N_VariationResponse",
  };
  std::vector<std::string> multisim_names;
  std::vector<std::vector<Var>> univsKnobs;
  std::vector<unsigned int> nuniverses;
  //TFile* hack = TFile::Open(pnfs2xrootd("/pnfs/icarus/scratch/users/jlarkin/cafs/mc2024_1d_01.flat.caf.root").c_str());
  //UniverseOracle& oracle = UniverseOracle::Instance();
  for(const auto& name: flux_names) {
    //size_t nuniv = oracle.ShiftsForSyst(name).size();
    // Hard code nuniv at 1000 for now since asking UniverseOracle breaks for 
    // piplus, piminus, kplus, kminus, and kzero.
    multisim_names.push_back(name);
    size_t nuniv = 1000;
    nuniverses.push_back(nuniv);
    univsKnobs.emplace_back();
    for(size_t i = 0; i < nuniv; ++i) 
      univsKnobs.back().push_back(GetUniverseWeight(name, i));
  }
  for(const auto& name: xsec_multisim_names) {
    multisim_names.push_back(name);
    size_t nuniv = 100;
    nuniverses.push_back(nuniv);
    univsKnobs.emplace_back();
    for(size_t i = 0; i < nuniv; ++i) 
      univsKnobs.back().push_back(GetUniverseWeight(name, i));
  }
  //hack->Close();

  const std::vector<const ISyst*> detsysts = GetDetectorSysts();
  std::vector<std::string> detsyst_names;
  std::vector<std::pair<int,int>> min_max_det;
  for(size_t i = 0; i < detsysts.size(); ++i)
    {
      min_max_det.emplace_back(-3,3);
      const ISyst* detsyst = detsysts[i];
      detsyst_names.push_back(detsyst->ShortName()+"_multisigma");
    }
  NSigmasTree detsysttree("detsystTree", detsyst_names, mc, detsysts, min_max_det, kSpillSelection, kSliceSelection && kTrueNu, kNoShift, true, true);


  NUniversesTree nunivtree("multisimTree", multisim_names, mc, univsKnobs, nuniverses, kSpillSelection, kSliceSelection && kTrueNu, kNoShift, true, true);

  mc.Go();

  //nsigtree.MergeTree(nutree);
  //nunivtree.MergeTree(nsigtree);

  TFile fout("selected_events.root", "RECREATE");
  TDirectory* dir = fout.mkdir("events");
  nutree.SaveTo(dir); 
  costree.SaveTo(dir);
  nsigtree.SaveTo(dir);
  nunivtree.SaveTo(dir);
  detsysttree.SaveTo(dir);
  TDirectory *offbeamDir = fout.mkdir("offbeamEvents");
  offbeamTree.SaveTo(offbeamDir);
}
