#!/bin/bash

sample_tags=("numuccinc")

samples=("numuCCincl")

detector_names=("SBND" "Uboone" "Icarus")

detector_tags=("nd" "ub" "fd")

directories=("sbnd" "uboone" "icarus")

# samples
for j in ${!samples[@]}; do
  s=${samples[$j]}
  t=${sample_tags[$j]}

  # detectors
  for k in ${!detector_names[@]}; do
    d=${detector_tags[$k]}
    n=${detector_names[$k]}
    dir=${directories[$k]}

    valor_sbn-make_sbncode_minidst \
      --input /sbnd/data/users/gputnam/NuMu/workshop-game/${dir}/mc/output_SBNOsc_NumuSelection_Modern_${n}.root \
      --output /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/dsts/2019b3_2/valor_sbncode_fhc_${t}_disappearance_${d}_minidst_mc.root \
      --no-status-code \
      --sample $s

  done
done
