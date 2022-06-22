#!/bin/bash

valor_dune-make_sbncode_minidst --input /pnfs/sbnd/persistent/users/gputnam/numu_simulation_reweight2/processed_2.2/output_SBNOsc_NumuSelection_Modern_SBND.root --output data/sbn/modern/reco_weight_sample_2.2/valor_sbncode_fhc_numuccinc_disappearance_nd_minidst.root --beam BNB_FHC --sample numulikeCChigh

valor_dune-make_sbncode_minidst --input /pnfs/sbnd/persistent/users/gputnam/numu_simulation_reweight2/processed_2.2/output_SBNOsc_NumuSelection_Modern_Uboone.root --output data/sbn/modern/reco_weight_sample_2.2/valor_sbncode_fhc_numuccinc_disappearance_ub_minidst.root --beam BNB_FHC --sample numulikeCChigh

valor_dune-make_sbncode_minidst --input /pnfs/sbnd/persistent/users/gputnam/numu_simulation_reweight2/processed_2.2/output_SBNOsc_NumuSelection_Modern_Icarus.root --output data/sbn/modern/reco_weight_sample_2.2/valor_sbncode_fhc_numuccinc_disappearance_fd_minidst.root --beam BNB_FHC --sample numulikeCChigh

