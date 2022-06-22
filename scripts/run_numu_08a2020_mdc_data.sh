#!/bin/bash

datasets=(11 12 13 14 15)

sample_tags=("numuccinc" "numucc0pi" "numuccoth")

samples=("numuCCincl" "numuCC0piNtrk" "numuCC0piNtrk")

other=(0 0 1)

detector_names=("SBND" "Uboone" "Icarus")

detector_tags=("nd" "ub" "fd")

directories=("sbnd" "uboone" "icarus")

#mock dataset enums
for i in ${!datasets[@]}; do
  m=${datasets[$i]}

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
          --input /sbnd/data/users/rsjones/NuMu/workshop-game-0320/211a/${dir}/data/output_SBNOsc_NumuSelection_Modern_${n}${m}.root \
          --output /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/mock_data/08a2020/valor_sbncode_fhc_${t}_disappearance_${d}_minidst_${m}.root \
          --sample $s \
          --no-truth
      else
        valor_sbn-make_sbncode_minidst \
          --input /sbnd/data/users/rsjones/NuMu/workshop-game-0320/211a/${dir}/data/output_SBNOsc_NumuSelection_Modern_${n}${m}.root \
          --output /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/mock_data/08a2020/valor_sbncode_fhc_${t}_disappearance_${d}_minidst_${m}.root \
          --sample $s \
          --other-sample \
          --no-truth
      fi

    done
  done
done
