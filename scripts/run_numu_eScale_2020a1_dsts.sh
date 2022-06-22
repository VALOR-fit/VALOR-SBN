#!/bin/bash

sample_tags=("numuccinc" "numucc0pi" "numuccoth")

samples=("numuCCincl" "numuCC0piNtrk" "numuCC0piNtrk")

other=(0 0 1)

# samples
for j in ${!samples[@]}; do
  s=${samples[$j]}
  t=${sample_tags[$j]}
  o=${other[$j]}

  if [ $o == 0 ]
  then
    valor_sbn-make_sbncode_minidst \
      --input /sbnd/data/users/rsjones/NuMu/workshop-game-0320/211a/sbnd/data_full/v3_nieves_uBooNEThresh/output_SBNOsc_NumuSelection_Modern_SBND_uB_Thresh.root \
      --output /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/dsts/2020a1/valor_sbncode_fhc_${t}_disappearance_nd_minidst_mc_escale.root \
      --sample $s
  else
    valor_sbn-make_sbncode_minidst \
      --input /sbnd/data/users/rsjones/NuMu/workshop-game-0320/211a/sbnd/data_full/v3_nieves_uBooNEThresh/output_SBNOsc_NumuSelection_Modern_SBND_uB_Thresh.root \
      --output /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/dsts/2020a1/valor_sbncode_fhc_${t}_disappearance_nd_minidst_mc_escale.root \
      --sample $s \
      --other-sample
  fi

done
