#!/bin/bash

valor_dune-make_sbncode_minidst \
  --input /pnfs/sbn/persistent/users/dbarker/sbnoutput/Modern_6thNov2019/output_SBNOsc_NueSelection_Modern_SBND_Numu.root \
  --output data/sbn/modern/reco_weight_sample_2.2/nue/disappearance/all/valor_sbncode_fhc_nueccinc_nue_disappearance_nd_numu_minidst.root \
  --beam BNB_FHC \
  --sample nuelikeCChigh \
  --oscillation nue-disappearance

valor_dune-make_sbncode_minidst \
  --input /pnfs/sbn/persistent/users/dbarker/sbnoutput/Modern_6thNov2019/output_SBNOsc_NueSelection_Modern_SBND_Int.root \
  --output data/sbn/modern/reco_weight_sample_2.2/nue/disappearance/all/valor_sbncode_fhc_nueccinc_nue_disappearance_nd_int_minidst.root \
  --beam BNB_FHC \
  --sample nuelikeCChigh \
  --oscillation nue-disappearance

valor_dune-make_sbncode_minidst \
  --input /pnfs/sbn/persistent/users/dbarker/sbnoutput/Modern_6thNov2019/output_SBNOsc_NueSelection_Modern_SBND_Osc.root \
  --output data/sbn/modern/reco_weight_sample_2.2/nue/disappearance/all/valor_sbncode_fhc_nueccinc_nue_disappearance_nd_osc_minidst.root \
  --beam BNB_FHC \
  --sample nuelikeCChigh \
  --oscillation nue-disappearance

