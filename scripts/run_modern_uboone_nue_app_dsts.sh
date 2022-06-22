#!/bin/bash

valor_dune-make_sbncode_minidst \
  --input /pnfs/sbn/persistent/users/dbarker/sbnoutput/Modern_6thNov2019/output_SBNOsc_NueSelection_Modern_Uboone_Numu.root \
  --output data/sbn/modern/reco_weight_sample_2.2/nue/appearance/valor_sbncode_fhc_nueccinc_nue_appearance_ub_numu_minidst.root \
  --beam BNB_FHC \
  --sample nuelikeCChigh

valor_dune-make_sbncode_minidst \
  --input /pnfs/sbn/persistent/users/dbarker/sbnoutput/Modern_6thNov2019/output_SBNOsc_NueSelection_Modern_Uboone_Int.root \
  --output data/sbn/modern/reco_weight_sample_2.2/nue/appearance/valor_sbncode_fhc_nueccinc_nue_appearance_ub_int_minidst.root \
  --beam BNB_FHC \
  --sample nuelikeCChigh

valor_dune-make_sbncode_minidst \
  --input /pnfs/sbn/persistent/users/dbarker/sbnoutput/Modern_6thNov2019/output_SBNOsc_NueSelection_Modern_Uboone_Osc.root \
  --output data/sbn/modern/reco_weight_sample_2.2/nue/appearance/valor_sbncode_fhc_nueccinc_nue_appearance_ub_osc_minidst.root \
  --beam BNB_FHC \
  --sample nuelikeCChigh

