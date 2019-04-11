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

    conv::ReacMode_t NeutModeToValorMode(int neut_mode, conv::NuFlavour_t flav, bool is_oscillated);

    // See https://t2k.org/docs/technotes/351/v02 tables 5 and 6 (p105) for an explanation of what each neut reac mode number is (for the 2018 analysis)
    bool IsCCQE     (int neut_reaction_mode);
    bool IsCC1piC   (int neut_reaction_mode);
    bool IsCC1pi0   (int neut_reaction_mode);
    bool Is2p2h     (int neut_reaction_mode);
    bool IsCCcoh    (int neut_reaction_mode);
    bool IsCCoth    (int neut_reaction_mode); // this is a catch all. if new categories are added, please alter this method too
    bool IsNC1pi0   (int neut_reaction_mode);
    bool IsNC1piC   (int neut_reaction_mode);
    bool IsNCcoh    (int neut_reaction_mode);
    bool IsNCoth    (int neut_reaction_mode);
    bool IsNC1Gamma (int neut_reaction_mode);
  }
}


#endif //valor_util_neut
