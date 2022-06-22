#!/bin/bash

sample_tags=("numuccinc" "numucc0pi" "numuccoth")

samples=("numuCCincl" "numuCC0piNtrk" "numuCC0piNtrk")

other=(0 0 1)

detector_names=("SBND" "Uboone" "Icarus")

detector_tags=("nd" "ub" "fd")

directories=("sbnd" "uboone" "icarus")

# samples
for j in ${!samples[@]}; do
  s=${samples[$j]}
  t=${sample_tags[$j]}
  o=${other[$j]}

  # detectors
  for k in ${!detector_names[@]}; do
    d=${detector_tags[$k]}
    n=${detector_names[$k]}
    dir=${directories[$k]}

    if [ $o == 0 ]
    then
      valor_sbn-make_sbncode_minidst \
        --input /sbnd/data/users/gputnam/NuMu/workshop-game-0320/211a/${dir}/mc/output_SBNOsc_NumuSelection_Modern_${n}.root \
        --output /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/dsts/2020a1/valor_sbncode_fhc_${t}_disappearance_${d}_minidst_mc.root \
        --sample $s
    else
      valor_sbn-make_sbncode_minidst \
        --input /sbnd/data/users/gputnam/NuMu/workshop-game-0320/211a/${dir}/mc/output_SBNOsc_NumuSelection_Modern_${n}.root \
        --output /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/dsts/2020a1/valor_sbncode_fhc_${t}_disappearance_${d}_minidst_mc.root \
        --sample $s \
        --other-sample
    fi

  done
done
