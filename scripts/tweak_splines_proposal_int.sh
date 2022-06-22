#!/bin/bash

params=("genie_ccresAxial_Genie" "genie_ncresAxial_Genie" "genie_qema_Genie" "genie_NC_Genie" "genie_NonResRvpCC1pi_Genie" "genie_NonResRvnCC1pi_Genie" "genie_NonResRvbarnCC1pi_Genie" "genie_NonResRvbarpCC1pi_Genie" "genie_NonResRvpCC2pi_Genie" "genie_NonResRvnCC2pi_Genie" "genie_NonResRvbarnCC2pi_Genie" "genie_NonResRvbarpCC2pi_Genie" "genie_NonResRvpNC1pi_Genie" "genie_NonResRvnNC1pi_Genie" "genie_NonResRvbarnNC1pi_Genie" "genie_NonResRvbarpNC1pi_Genie" "genie_NonResRvpNC2pi_Genie" "genie_NonResRvnNC2pi_Genie" "genie_NonResRvbarnNC2pi_Genie" "genie_NonResRvbarpNC2pi_Genie")

samples=("numuCCincl" "numuCC0piNtrk" "numuCCoth")

#detectors=("sbn_nd" "sbn_uboone" "sbn_icarus")

#directories=("sbnd" "uboone" "icarus")

#configs=("nd" "ub" "fd")

detectors=("sbn_uboone" "sbn_icarus")

directories=("uboone" "icarus")

configs=("ub" "fd")

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

      config_filename_inc="analysis/sbn_numu_disapp_2020a1_03c1_${config}_1.xml"
      config_filename_0pi="analysis/sbn_numu_disapp_2020a1_03c1_${config}_1_cc0pi.xml"
      config_filename_oth="analysis/sbn_numu_disapp_2020a1_03c1_${config}_1_ccoth.xml"

      cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/proposal_xsec/validation/$dir/

      spectra_filename="/sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/responses/03c1/${dir}/valor_splines_${s}_${p}_BNB_FHC_${d}_spectra.root"
      printf "Spectra filename: %s \n" $spectra_filename

      if [ $s == 'numuCCincl' ]
      then
        printf "Tweaking CC Inclusive sample \n"
        valor_sbn-tweak_pdf_nsigma_var \
          --config $config_filename_inc \
          --params $p \
          --sample $s \
          --physics-hypothesis void \
          --universe-spectra $spectra_filename

        if [ $? -ne 0 ]; then
          printf "Previous command failed, killing the jobs so you can debug \n"
          mail -s 'Tweaks proposal script failed' rjones0211@hotmail.com <<< 'Failed in sample '$s', detector '$d', and parameter '$p''
          return
        fi

      elif [ $s == 'numuCC0piNtrk' ]
      then
        printf "Tweaking CC 0Pi sample \n"
        valor_sbn-tweak_pdf_nsigma_var \
          --config $config_filename_0pi \
          --params $p \
          --sample $s \
          --physics-hypothesis void \
          --universe-spectra $spectra_filename

        if [ $? -ne 0 ]; then
          printf "Previous command failed, killing the jobs so you can debug \n"
          mail -s 'Tweaks proposal script failed' rjones0211@hotmail.com <<< 'Failed in sample '$s', detector '$d', and parameter '$p''
          return
        fi

      elif [ $s == 'numuCCoth' ]
      then
        printf "Tweaking CC Other sample \n"
        valor_sbn-tweak_pdf_nsigma_var \
          --config $config_filename_oth \
          --params $p \
          --sample $s \
          --physics-hypothesis void \
          --universe-spectra $spectra_filename

        if [ $? -ne 0 ]; then
          printf "Previous command failed, killing the jobs so you can debug \n"
          mail -s 'Tweaks proposal script failed' rjones0211@hotmail.com <<< 'Failed in sample '$s', detector '$d', and parameter '$p''
          return
        fi

      fi
    done
  done
done
