#!/bin/bash

detector_names=("SBND" "Uboone" "Icarus")

detector_tags=("nd" "ub" "fd")

directories=("sbnd" "uboone" "icarus")

# detectors
for k in ${!detector_names[@]}; do
  d=${detector_tags[$k]}
  n=${detector_names[$k]}
  dir=${directories[$k]}

  valor_sbn-make_sbncode_minidst \
    --input /sbnd/data/users/gputnam/NuMu/workshop-game/${dir}/mc/output_SBNOsc_NumuSelection_Modern_${n}.root \
    --output /sbnd/data/users/rsjones/VALOR/VALOR-DUNE-LBL/data/sbn/data_archive/data/sbn_numu_disappearance/universes/2019b3_1/valor_sbncode_fhc_numulikeCChigh_disappearance_${d}_minidst_mc.root \
    --sample numulikeCChigh \
    --write-universes

  if [ $? -ne 0 ]; then
    printf "Previous command failed, killing the jobs so you can debug \n"
    mail -s 'Universes DST script failed' rjones0211@hotmail.com <<< 'Failed in detector '$d''
    return
  fi
done
