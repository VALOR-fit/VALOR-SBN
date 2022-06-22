#!/bin/bash

model_inputs=("v2")

model_outputs=("v2Default")

datasets=(11)

sample_tags=("numuccinc" "numucc0pi" "numuccoth")

samples=("numuCCincl" "numuCC0piNtrk" "numuCC0piNtrk")

other=(0 0 1)

detector_names=("SBND" "Icarus")

detector_tags=("nd" "fd")

directories=("sbnd" "icarus")

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

    for l in ${!model_inputs[@]}; do
      mi=${model_inputs[$l]}
      mo=${model_outputs[$l]}
      m=${datasets[$l]}

      if [ ! -d "/sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/dsts/genie/${mo}" ]; then
        mkdir -p /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/dsts/genie/${mo}
      fi

      if [ $o == 0 ]
      then
        valor_sbn-make_sbncode_minidst \
          --input /sbnd/data/users/rsjones/NuMu/workshop-game-0320/211a/${dir}/data_full/${mi}/output_SBNOsc_NumuSelection_Modern_${n}${m}.root \
          --output /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/dsts/genie/${mo}/valor_sbncode_fhc_${t}_disappearance_${d}_minidst_mc.root \
          --sample $s
      else
        valor_sbn-make_sbncode_minidst \
          --input /sbnd/data/users/rsjones/NuMu/workshop-game-0320/211a/${dir}/data_full/${mi}/output_SBNOsc_NumuSelection_Modern_${n}${m}.root \
          --output /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/dsts/genie/${mo}/valor_sbncode_fhc_${t}_disappearance_${d}_minidst_mc.root \
          --sample $s \
          --other-sample
      fi

    done
  done
done
