#!/bin/bash
valor_sbn-make_sbncode_minidst \
  --input /sbnd/data/users/gputnam/NuMu/workshop-game-0320/211a/sbnd/mc/output_SBNOsc_NumuSelection_Modern_SBND.root \
  --output /sbnd/data/users/rsjones/VALOR/VALOR-DUNE-LBL/data/sbn/data_archive/data/sbn_numu_disappearance/universes/2020a1/valor_sbncode_fhc_numuccinc_disappearance_nd_minidst_mc.root \
  --sample numuCCincl \
  --write-universes

valor_sbn-make_sbncode_minidst \
  --input /sbnd/data/users/gputnam/NuMu/workshop-game-0320/211a/uboone/mc/output_SBNOsc_NumuSelection_Modern_Uboone.root \
  --output /sbnd/data/users/rsjones/VALOR/VALOR-DUNE-LBL/data/sbn/data_archive/data/sbn_numu_disappearance/universes/2020a1/valor_sbncode_fhc_numuccinc_disappearance_ub_minidst_mc.root \
  --sample numuCCincl \
  --write-universes

valor_sbn-make_sbncode_minidst \
  --input /sbnd/data/users/gputnam/NuMu/workshop-game-0320/211a/icarus/mc/output_SBNOsc_NumuSelection_Modern_Icarus.root \
  --output /sbnd/data/users/rsjones/VALOR/VALOR-DUNE-LBL/data/sbn/data_archive/data/sbn_numu_disappearance/universes/2020a1/valor_sbncode_fhc_numuccinc_disappearance_fd_minidst_mc.root \
  --sample numuCCincl \
  --write-universes

valor_sbn-make_sbncode_minidst \
  --input /sbnd/data/users/gputnam/NuMu/workshop-game-0320/211a/sbnd/mc/output_SBNOsc_NumuSelection_Modern_SBND.root \
  --output /sbnd/data/users/rsjones/VALOR/VALOR-DUNE-LBL/data/sbn/data_archive/data/sbn_numu_disappearance/universes/2020a1/valor_sbncode_fhc_numucc0pi_disappearance_nd_minidst_mc.root \
  --sample numuCC0piNtrk \
  --write-universes

valor_sbn-make_sbncode_minidst \
  --input /sbnd/data/users/gputnam/NuMu/workshop-game-0320/211a/uboone/mc/output_SBNOsc_NumuSelection_Modern_Uboone.root \
  --output /sbnd/data/users/rsjones/VALOR/VALOR-DUNE-LBL/data/sbn/data_archive/data/sbn_numu_disappearance/universes/2020a1/valor_sbncode_fhc_numucc0pi_disappearance_ub_minidst_mc.root \
  --sample numuCC0piNtrk \
  --write-universes

valor_sbn-make_sbncode_minidst \
  --input /sbnd/data/users/gputnam/NuMu/workshop-game-0320/211a/icarus/mc/output_SBNOsc_NumuSelection_Modern_Icarus.root \
  --output /sbnd/data/users/rsjones/VALOR/VALOR-DUNE-LBL/data/sbn/data_archive/data/sbn_numu_disappearance/universes/2020a1/valor_sbncode_fhc_numucc0pi_disappearance_fd_minidst_mc.root \
  --sample numuCC0piNtrk \
  --write-universes

valor_sbn-make_sbncode_minidst \
  --input /sbnd/data/users/gputnam/NuMu/workshop-game-0320/211a/sbnd/mc/output_SBNOsc_NumuSelection_Modern_SBND.root \
  --output /sbnd/data/users/rsjones/VALOR/VALOR-DUNE-LBL/data/sbn/data_archive/data/sbn_numu_disappearance/universes/2020a1/valor_sbncode_fhc_numuccoth_disappearance_nd_minidst_mc.root \
  --sample numuCC0piNtrk \
  --other-sample \
  --write-universes

valor_sbn-make_sbncode_minidst \
  --input /sbnd/data/users/gputnam/NuMu/workshop-game-0320/211a/uboone/mc/output_SBNOsc_NumuSelection_Modern_Uboone.root \
  --output /sbnd/data/users/rsjones/VALOR/VALOR-DUNE-LBL/data/sbn/data_archive/data/sbn_numu_disappearance/universes/2020a1/valor_sbncode_fhc_numuccoth_disappearance_ub_minidst_mc.root \
  --sample numuCC0piNtrk \
  --other-sample \
  --write-universes

valor_sbn-make_sbncode_minidst \
  --input /sbnd/data/users/gputnam/NuMu/workshop-game-0320/211a/icarus/mc/output_SBNOsc_NumuSelection_Modern_Icarus.root \
  --output /sbnd/data/users/rsjones/VALOR/VALOR-DUNE-LBL/data/sbn/data_archive/data/sbn_numu_disappearance/universes/2020a1/valor_sbncode_fhc_numuccoth_disappearance_fd_minidst_mc.root \
  --sample numuCC0piNtrk \
  --other-sample \
  --write-universes

