#!/bin/bash

params=("horncurrent" "expskin" "nucleoninexsec" "nucleontotxsec" "nucleonqexsec" "pioninexsec" "piontotxsec" "pionqexsec")

samples=("numuCCincl")

detectors=("sbn_nd" "sbn_uboone" "sbn_icarus")

directories=("sbnd" "uboone" "icarus")

configs=("nd" "ub" "fd")

#parameters
for i in ${!params[@]}; do
  p=${params[$i]}

  # samples
  for j in ${!samples[@]}; do
    s=${samples[$j]}

    # detectors
    for k in ${!detectors[@]}; do
      d=${detectors[$k]}
      dir=${directories[$k]}
      config=${configs[$k]}

      config_filename_inc="analysis/sbn_numu_disapp_2019b3_2_universes_${config}.xml"

      if [ ! -d "/sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/02c1_2/flux/${dir}" ]
      then
        mkdir -p /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/02c1_2/flux/${dir}
      fi

      cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/02c1_2/flux/$dir/

      valor_sbn-make_flux_splines \
        --config $config_filename_inc \
        --systematic $p \
        --sample $s \
        --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2019b3/sbn_universe_variations_from_mastbaum.txt \
        --store-spectra \
        --save-modelist \
        --detector $d

      if [ $? -ne 0 ]; then
        printf "Previous command failed, killing the jobs so you can debug \n"
        mail -s 'Flux splines script failed' rjones0211@hotmail.com <<< 'Failed in sample '$s', detector '$d', and parameter '$p''
        return
      fi

    done
  done
done
