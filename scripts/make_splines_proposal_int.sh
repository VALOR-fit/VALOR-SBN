#!/bin/bash

params=("ccresAxial" "ncresAxial" "qema" "NC" "NonResRvpCC1pi" "NonResRvnCC1pi" "NonResRvbarnCC1pi" "NonResRvbarpCC1pi" "NonResRvpCC2pi" "NonResRvnCC2pi" "NonResRvbarnCC2pi" "NonResRvbarpCC2pi" "NonResRvpNC1pi" "NonResRvnNC1pi" "NonResRvbarnNC1pi" "NonResRvbarpNC1pi" "NonResRvpNC2pi" "NonResRvnNC2pi" "NonResRvbarnNC2pi" "NonResRvbarpNC2pi")

samples=("numuCCoth")
#samples=("numuCCincl" "numuCC0piNtrk" "numuCCoth")

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

      config_filename_inc="analysis/sbn_numu_disapp_2020a1_1_universes_${config}.xml"
      config_filename_0pi="analysis/sbn_numu_disapp_2020a1_1_universes_${config}_cc0pi.xml"
      config_filename_oth="analysis/sbn_numu_disapp_2020a1_1_universes_${config}_ccoth.xml"

      cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/proposal_xsec/$dir/

      if [ $s == 'numuCCincl' ]
      then
        printf "Making CC Inclusive sample splines"
        valor_sbn-make_xsec_splines \
          --config $config_filename_inc \
          --systematic $p \
          --sample $s \
          --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
          --store-spectra --save-modelist \
          --detector $d

        if [ $? -ne 0 ]; then
          printf "Previous command failed, killing the jobs so you can debug \n"
          mail -s 'Proposal splines script failed' rjones0211@hotmail.com <<< 'Failed in sample '$s', detector '$d', and parameter '$p''
          return
        fi

      elif [ $s == 'numuCC0piNtrk' ]
      then
        printf "Making CC 0Pi sample splines"
        valor_sbn-make_xsec_splines \
          --config $config_filename_0pi \
          --systematic $p \
          --sample $s \
          --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
          --store-spectra --save-modelist \
          --detector $d

        if [ $? -ne 0 ]; then
          printf "Previous command failed, killing the jobs so you can debug \n"
          mail -s 'Proposal splines script failed' rjones0211@hotmail.com <<< 'Failed in sample '$s', detector '$d', and parameter '$p''
          return
        fi

      elif [ $s == 'numuCCoth' ]
      then
        printf "Making CC Other sample splines"
        valor_sbn-make_xsec_splines \
          --config $config_filename_oth \
          --systematic $p \
          --sample $s \
          --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
          --store-spectra --save-modelist \
          --detector $d

        if [ $? -ne 0 ]; then
          printf "Previous command failed, killing the jobs so you can debug \n"
          mail -s 'Proposal splines script failed' rjones0211@hotmail.com <<< 'Failed in sample '$s', detector '$d', and parameter '$p''
          return
        fi

      fi
    done
  done
done
