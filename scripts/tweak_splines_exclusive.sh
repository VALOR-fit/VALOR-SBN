#!/bin/bash

params=("ccother_migration")

#samples=("numuCC0piNtrk")
samples=("numuCC0piNtrk" "numuCCoth")

#detectors=("sbn_nd")
detectors=("sbn_nd" "sbn_uboone" "sbn_icarus")

#directories=("sbnd")
directories=("sbnd" "uboone" "icarus")

#configs=("nd")
configs=("nd" "ub" "fd")

#parameters
for i in ${!params[@]}; do
  p=${params[$i]}
  for j in ${!samples[@]}; do
    s=${samples[$j]}

    # detectors
    for k in ${!detectors[@]}; do
      d=${detectors[$k]}
      dir=${directories[$k]}
      config=${configs[$k]}

      config_filename_inc="analysis/sbn_numu_disapp_2020a1_03c1_${config}_1.xml"
      config_filename_0pi="analysis/sbn_numu_disapp_2020a1_03c1_${config}_1_cc0pi.xml"
      config_filename_oth="analysis/sbn_numu_disapp_2020a1_03c1_${config}_1_ccoth.xml"

      cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/exclusive25pctGOOD/validation/$dir/

      if [ $s == 'numuCCincl' ]
      then
        printf "Tweaking CC Inclusive sample \n"
        valor_sbn-tweak_pdf_nsigma_var \
          --config $config_filename_inc \
          --params $p \
          --sample $s \
          --physics-hypothesis void

        if [ $? -ne 0 ]; then
          printf "Previous command failed, killing the jobs so you can debug \n"
          mail -s 'Tweaks exclusive script failed' rjones0211@hotmail.com <<< 'Failed in sample '$s', detector '$d', and parameter '$p''
          return
        fi

      elif [ $s == 'numuCC0piNtrk' ]
      then
        printf "Tweaking CC 0Pi sample \n"
        valor_sbn-tweak_pdf_nsigma_var \
          --config $config_filename_0pi \
          --params $p \
          --sample $s \
          --physics-hypothesis void

        if [ $? -ne 0 ]; then
          printf "Previous command failed, killing the jobs so you can debug \n"
          mail -s 'Tweaks exclusive script failed' rjones0211@hotmail.com <<< 'Failed in sample '$s', detector '$d', and parameter '$p''
          return
        fi

      elif [ $s == 'numuCCoth' ]
      then
        printf "Tweaking CC Other sample \n"
        valor_sbn-tweak_pdf_nsigma_var \
          --config $config_filename_oth \
          --params $p \
          --sample $s \
          --physics-hypothesis void

        if [ $? -ne 0 ]; then
          printf "Previous command failed, killing the jobs so you can debug \n"
          mail -s 'Tweaks exclusive script failed' rjones0211@hotmail.com <<< 'Failed in sample '$s', detector '$d', and parameter '$p''
          return
        fi

      fi
    done
  done
done
