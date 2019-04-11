//________________________________________________________________________________________
/*

Copyright (c) 2010-2019, The VALOR Fitting Group, All Rights Reserved.

*/
//________________________________________________________________________________________

#include "dune/Utilities/UtlNeut.h"

#include "valor/Messenger/Messenger.h"

#include <TMath.h>

using namespace valor;


//___________________________________________________________________________
bool valor::util::NeutIsCCQE(int neut_reaction_mode)
{
  return neut_reaction_mode ==  1;
}
//___________________________________________________________________________
bool valor::util::NeutIsCC1piC(int neut_reaction_mode)
{
  bool is_cc1piC = (neut_reaction_mode == 11 ||
                    neut_reaction_mode == 13);
  return is_cc1piC;
}
//___________________________________________________________________________
bool valor::util::NeutIsCC1pi0(int neut_reaction_mode)
{
  bool is_cc1pi0 = (neut_reaction_mode == 12);
  return is_cc1pi0;
}
//___________________________________________________________________________
bool valor::util::NeutIsCCcoh(int neut_reaction_mode)
{
  return neut_reaction_mode ==  16;
}
//___________________________________________________________________________
bool valor::util::NeutIs2p2h(int neut_reaction_mode)
{
  return neut_reaction_mode ==  2;
}
//___________________________________________________________________________
bool valor::util::NeutIsCCoth(int neut_reaction_mode)
//this is a catch all for everything CC that is not QE, 1pi, or coh
// needs to be updated if another subcategory is added
{
  bool is_ccoth = ( neut_reaction_mode == 17 ||
                    neut_reaction_mode == 21 ||
                    neut_reaction_mode == 22 ||
                    neut_reaction_mode == 23 ||
                    neut_reaction_mode == 26 );
  return is_ccoth;
}
//___________________________________________________________________________
bool valor::util::NeutIsNC1pi0(int neut_reaction_mode)
{
  bool is_cc1pi0 = (neut_reaction_mode == 31 ||
                    neut_reaction_mode == 32);
  return is_cc1pi0;
}
//___________________________________________________________________________
bool valor::util::NeutIsNC1Gamma(int neut_reaction_mode)
{
  bool is_nc1gamma= (neut_reaction_mode == 38 ||
                     neut_reaction_mode == 39);
  return is_nc1gamma;
}
//___________________________________________________________________________
bool valor::util::NeutIsNC1piC(int neut_reaction_mode)
{
  bool is_cc1pi0 = (neut_reaction_mode == 33 ||
                    neut_reaction_mode == 34);
  return is_cc1pi0;
}
//___________________________________________________________________________
bool valor::util::NeutIsNCcoh(int neut_reaction_mode)
{
  return neut_reaction_mode == 36;
}
//___________________________________________________________________________
bool valor::util::NeutIsNCoth(int neut_reaction_mode)
//this is a catch all for everything NC that is not 1pi0, 1piC or coh
// needs to be updated if another subcategory is added
{
  bool is_ncoth = (
    neut_reaction_mode == 41 ||
    neut_reaction_mode == 42 ||
    neut_reaction_mode == 43 ||
    neut_reaction_mode == 44 ||
    neut_reaction_mode == 45 ||
    neut_reaction_mode == 46 ||
    neut_reaction_mode == 51 ||
    neut_reaction_mode == 52);
  return is_ncoth;
}
//___________________________________________________________________________
bool valor::util::NeutIsCC(int neut_reaction_mode)
{
  return NeutIsCCQE(neut_reaction_mode) || NeutIsCC1piC(neut_reaction_mode) || NeutIsCC1pi0(neut_reaction_mode) || 
         NeutIs2p2h(neut_reaction_mode) || NeutIsCCcoh(neut_reaction_mode) || NeutIsCCoth(neut_reaction_mode);
}
//___________________________________________________________________________
bool valor::util::NeutIsNC(int neut_reaction_mode)
{
  return NeutIsNC1piC(neut_reaction_mode) || NeutIsNC1pi0(neut_reaction_mode) || NeutIsNC1Gamma(neut_reaction_mode) ||
         NeutIsNCcoh(neut_reaction_mode) || NeutIsNCoth(neut_reaction_mode);
}
//___________________________________________________________________________
conv::ReacMode_t valor::util::NeutModeToValorMode(int neut_mode, conv::NuFlavour_t flav, bool is_oscillated)
{
  conv::ReacMode_t valor_mode = conv::kmUndefined;

  int abs_mode = TMath::Abs(neut_mode);   // +ve neut modes are for neutrinos, -ve neut modes are the equivalent antineutrino modes

  if (flav == conv::kNuFlavourUndefined) {
    LOG("InputMC", pWARN) << "Tried to convert a neut reac mode to a valor reac mode, but the input flavour was undefined!";
    return conv::kmUndefined;
  }
  else if (flav == conv::kNuTau || flav == conv::kNuTauBar) {
    LOG("InputMC", pWARN) << "NuTau and NuTauBar not supported when converting from neut reac mode to valor reac mode";
    return conv::kmUndefined;
  }

  if (NeutIsCCQE(abs_mode)) {
    if(flav == conv::kNuMu   ) valor_mode = conv::kmNuMuCCQE;
    if(flav == conv::kNuE    ) valor_mode = conv::kmNuECCQE;
    if(flav == conv::kNuMuBar) valor_mode = conv::kmNuMuBarCCQE;
    if(flav == conv::kNuEBar ) valor_mode = conv::kmNuEBarCCQE;
  }
  else if (NeutIsCC1piC(abs_mode)) {
    if(flav == conv::kNuMu   ) valor_mode = conv::kmNuMuCC1piC;
    if(flav == conv::kNuE    ) valor_mode = conv::kmNuECC1piC;
    if(flav == conv::kNuMuBar) valor_mode = conv::kmNuMuBarCC1piC;
    if(flav == conv::kNuEBar ) valor_mode = conv::kmNuEBarCC1piC;
  }
  else if (NeutIsCC1pi0(abs_mode)) {
    if(flav == conv::kNuMu   ) valor_mode = conv::kmNuMuCC1pi0;
    if(flav == conv::kNuE    ) valor_mode = conv::kmNuECC1pi0;
    if(flav == conv::kNuMuBar) valor_mode = conv::kmNuMuBarCC1pi0;
    if(flav == conv::kNuEBar ) valor_mode = conv::kmNuEBarCC1pi0;
  }
  else if (NeutIs2p2h(abs_mode)) {
    if(flav == conv::kNuMu   ) valor_mode = conv::kmNuMuCCMEC;
    if(flav == conv::kNuE    ) valor_mode = conv::kmNuECCMEC;
    if(flav == conv::kNuMuBar) valor_mode = conv::kmNuMuBarCCMEC;
    if(flav == conv::kNuEBar ) valor_mode = conv::kmNuEBarCCMEC;
  }
  else if (NeutIsCCcoh(abs_mode)) {
    if(flav == conv::kNuMu   ) valor_mode = conv::kmNuMuCCcoh;
    if(flav == conv::kNuE    ) valor_mode = conv::kmNuECCcoh;
    if(flav == conv::kNuMuBar) valor_mode = conv::kmNuMuBarCCcoh;
    if(flav == conv::kNuEBar ) valor_mode = conv::kmNuEBarCCcoh;
  }
  else if (NeutIsCCoth(abs_mode)) {
    if(flav == conv::kNuMu   ) valor_mode = conv::kmNuMuCCoth;
    if(flav == conv::kNuE    ) valor_mode = conv::kmNuECCoth;
    if(flav == conv::kNuMuBar) valor_mode = conv::kmNuMuBarCCoth;
    if(flav == conv::kNuEBar ) valor_mode = conv::kmNuEBarCCoth;
  }
  else if (NeutIsNC1piC(abs_mode)) {
    if(flav == conv::kNuMu   ) valor_mode = conv::kmNuMuNC1piC;
    if(flav == conv::kNuE    ) valor_mode = conv::kmNuENC1piC;
    if(flav == conv::kNuMuBar) valor_mode = conv::kmNuMuBarNC1piC;
    if(flav == conv::kNuEBar ) valor_mode = conv::kmNuEBarNC1piC;
  }
  else if (NeutIsNC1pi0(abs_mode)) {
    if(flav == conv::kNuMu   ) valor_mode = conv::kmNuMuNC1pi0;
    if(flav == conv::kNuE    ) valor_mode = conv::kmNuENC1pi0;
    if(flav == conv::kNuMuBar) valor_mode = conv::kmNuMuBarNC1pi0;
    if(flav == conv::kNuEBar ) valor_mode = conv::kmNuEBarNC1pi0;
  }
  else if (NeutIsNCcoh(abs_mode)) {
    if(flav == conv::kNuMu   ) valor_mode = conv::kmNuMuNCcoh;
    if(flav == conv::kNuE    ) valor_mode = conv::kmNuENCcoh;
    if(flav == conv::kNuMuBar) valor_mode = conv::kmNuMuBarNCcoh;
    if(flav == conv::kNuEBar ) valor_mode = conv::kmNuEBarNCcoh;
  }
  else if (NeutIsNC1Gamma(abs_mode)) {
    if(flav == conv::kNuMu   ) valor_mode = conv::kmNuMuNC1Gamma;
    if(flav == conv::kNuE    ) valor_mode = conv::kmNuENC1Gamma;
    if(flav == conv::kNuMuBar) valor_mode = conv::kmNuMuBarNC1Gamma;
    if(flav == conv::kNuEBar ) valor_mode = conv::kmNuEBarNC1Gamma;
  }
  else if (NeutIsNCoth(abs_mode)) {
    if(flav == conv::kNuMu   ) valor_mode = conv::kmNuMuNCoth;
    if(flav == conv::kNuE    ) valor_mode = conv::kmNuENCoth;
    if(flav == conv::kNuMuBar) valor_mode = conv::kmNuMuBarNCoth;
    if(flav == conv::kNuEBar ) valor_mode = conv::kmNuEBarNCoth;
  }
  else {
    LOG("InputMC", pWARN) << "Could not convert a neut reac mode with code " << neut_mode << ", to a valor reac mode";
    return conv::kmUndefined;
  }

  if (is_oscillated && (flav == conv::kNuE || flav == conv::kNuEBar) && !NeutIsNC(abs_mode)) {
    // We don't keep track of NC oscillated modes, so lump those events in with the NC un-oscillated modes
    valor_mode = util::NuEModeToOscNuEMode(valor_mode);
  }

  return valor_mode;
}


