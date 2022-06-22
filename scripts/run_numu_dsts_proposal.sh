#!/bin/bash

valor_dune-make_sbncode_minidst --input /pnfs/sbnd/persistent/users/gputnam/numu_simulation_reweight2/processed_2.2/output_SBNOsc_NumuSelection_Proposal_SBND.root --output /sbnd/data/users/rsjones/VALOR/VALOR-DUNE-LBL/data/sbn/proposal/reco_weight_sample_2.2/valor_sbncode_fhc_numuccinc_disappearance_nd_minidst.root --sample numulikeCChigh

valor_dune-make_sbncode_minidst --input /pnfs/sbnd/persistent/users/gputnam/numu_simulation_reweight2/processed_2.2/output_SBNOsc_NumuSelection_Proposal_Uboone.root --output /sbnd/data/users/rsjones/VALOR/VALOR-DUNE-LBL/data/sbn/proposal/reco_weight_sample_2.2/valor_sbncode_fhc_numuccinc_disappearance_ub_minidst.root --sample numulikeCChigh --write-universes

valor_dune-make_sbncode_minidst --input /pnfs/sbnd/persistent/users/gputnam/numu_simulation_reweight2/processed_2.2/output_SBNOsc_NumuSelection_Proposal_Icarus.root --output /sbnd/data/users/rsjones/VALOR/VALOR-DUNE-LBL/data/sbn/proposal/reco_weight_sample_2.2/valor_sbncode_fhc_numuccinc_disappearance_fd_minidst.root --sample numulikeCChigh --write-universes

