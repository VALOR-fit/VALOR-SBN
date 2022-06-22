#!/bin/bash

valor_dune-make_sbncode_minidst --input /sbnd/data/users/gputnam/NuMu/workshop-game/sbnd/mc/output_SBNOsc_NumuSelection_Modern_SBND.root --output /sbnd/data/users/rsjones/VALOR/VALOR-DUNE-LBL/data/sbn/data_archive/data/sbn_numu_disappearance/universes/2019b3/valor_sbncode_fhc_numuccinc_disappearance_nd_minidst_mc.root --sample numulikeCChigh --write-universes

valor_dune-make_sbncode_minidst --input /sbnd/data/users/gputnam/NuMu/workshop-game/uboone/mc/output_SBNOsc_NumuSelection_Modern_Uboone.root --output /sbnd/data/users/rsjones/VALOR/VALOR-DUNE-LBL/data/sbn/data_archive/data/sbn_numu_disappearance/universes/2019b3/valor_sbncode_fhc_numuccinc_disappearance_ub_minidst_mc.root --sample numulikeCChigh --write-universes

valor_dune-make_sbncode_minidst --input /sbnd/data/users/gputnam/NuMu/workshop-game/icarus/mc/output_SBNOsc_NumuSelection_Modern_Icarus.root --output /sbnd/data/users/rsjones/VALOR/VALOR-DUNE-LBL/data/sbn/data_archive/data/sbn_numu_disappearance/universes/2019b3/valor_sbncode_fhc_numuccinc_disappearance_fd_minidst_mc.root --sample numulikeCChigh --write-universes 
