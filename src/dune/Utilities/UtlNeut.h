/*!

\brief     Contains utility functions for converting between neut and VALOR reaction mode codes

\author    Francis Bench <F.Bench \at liverpool.ac.uk
           University of Liverpool

\created   April 10, 2019

\copyright (c) 2010-2019, The VALOR group

*/

#ifndef valor_util_neut
#define valor_util_neut

// dune
#include "dune/Conventions/ReacMode.h"

// valor
#include "valor/Conventions/NuFlavour.h"

namespace valor {
  namespace util {

    valor::conv::ReacMode_t NeutModeToValorMode(int neut_mode, valor::conv::NuFlavour_t flav, bool is_oscillated);

    // See https://t2k.org/docs/technotes/351/v02 tables 5 and 6 (p105) for an explanation of what each neut reac mode number is (for the 2018 analysis)
    bool NeutIsCCQE     (int neut_reaction_mode);
    bool NeutIsCC1piC   (int neut_reaction_mode);
    bool NeutIsCC1pi0   (int neut_reaction_mode);
    bool NeutIs2p2h     (int neut_reaction_mode);
    bool NeutIsCCcoh    (int neut_reaction_mode);
    bool NeutIsCCoth    (int neut_reaction_mode); // this is a catch all. if new categories are added, please alter this method too
    bool NeutIsCC       (int neut_reaction_mode);
    bool NeutIsNC1pi0   (int neut_reaction_mode);
    bool NeutIsNC1piC   (int neut_reaction_mode);
    bool NeutIsNCcoh    (int neut_reaction_mode);
    bool NeutIsNCoth    (int neut_reaction_mode);
    bool NeutIsNC1Gamma (int neut_reaction_mode);
    bool NeutIsNC       (int neut_reaction_mode);
  }
}


#endif //valor_util_neut
