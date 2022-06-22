#!/bin/bash

detectors=("sbn_nd" "sbn_uboone" "sbn_icarus")
#detectors=("sbn_nd")

directories=("sbnd" "uboone" "icarus")
#directories=("sbnd")

inputs=("SBND" "Uboone" "Icarus")
#inputs=("SBND")

configs=("nd" "ub" "fd")
#configs=("nd")

# detectors
for k in ${!detectors[@]}; do
  d=${detectors[$k]}
  dir=${directories[$k]}
  config=${configs[$k]}
  n=${inputs[$k]}

  config_filename="analysis/sbn_numu_disapp_2020a1_1_${config}.xml"

  cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/exclusive25pctGOOD/$dir/

  valor_sbn-make_excl_splines \
    --input /sbnd/data/users/gputnam/NuMu/workshop-game-0320/211a/${dir}/mc/output_SBNOsc_NumuSelection_Modern_${n}.root \
    --config $config_filename \
    --detector $d

#  if [ $? -ne 0 ]; then
#    printf "Previous command failed, killing the jobs so you can debug \n"
#    mail -s 'Exclusive splines script failed' rjones0211@hotmail.com <<< 'Failed in sample '$s' and detector '$d''
#    return
#  fi

done
#

