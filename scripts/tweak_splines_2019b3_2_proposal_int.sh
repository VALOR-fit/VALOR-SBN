#!/bin/bash

params=("genie_ccresAxial_Genie" "genie_ncresAxial_Genie" "genie_qema_Genie" "genie_NC_Genie" "genie_NonResRvp1pi_Genie" "genie_NonResRvp2pi_Genie" "genie_NonResRvbarp1pi_Genie" "genie_NonResRvbarp2pi_Genie")

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

      config_filename_inc="analysis/sbn_numu_disapp_2019b3_2_02c1_2_${config}.xml"

      cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/02c1_2/proposal_xsec/validation/$dir/

      spectra_filename="/sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/responses/02c1_2/${dir}/valor_splines_${s}_${p}_BNB_FHC_${d}_spectra.root"
      printf "Spectra filename: %s \n" $spectra_filename

      printf "Spectra filename: %s \n" $spectra_filename

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

    done
  done
done
