#!/bin/bash

model_inputs=("2020a1_6" "2020a1_7")

model_outputs=("plus50pct2p2h_nieves" "minus50pct2p2h_nieves")

datasets=(6 7)

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
      m=${datasets[$l]}
      mi=${model_inputs[$l]}
      mo=${model_outputs[$l]}

      if [ ! -d "/sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/mock_data/${mo}" ]; then
        mkdir -p /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/mock_data/${mo}
      fi

      if [ $o == 0 ]
      then
        valor_sbn-make_sbncode_minidst \
          --input /sbnd/data/users/rsjones/NuMu/workshop-game-0320/211a/${dir}/data_full/v3_${mi}/output_SBNOsc_NumuSelection_Modern_${n}${m}.root \
          --output /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/mock_data/${mo}/valor_sbncode_fhc_${t}_disappearance_${d}_minidst_1.root \
          --sample $s \
          --no-truth
      else
        valor_sbn-make_sbncode_minidst \
          --input /sbnd/data/users/rsjones/NuMu/workshop-game-0320/211a/${dir}/data_full/v3_${mi}/output_SBNOsc_NumuSelection_Modern_${n}${m}.root \
          --output /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/mock_data/${mo}/valor_sbncode_fhc_${t}_disappearance_${d}_minidst_1.root \
          --sample $s \
          --other-sample \
          --no-truth
      fi

    done
  done
done
