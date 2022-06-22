#!/bin/bash

params=("horncurrent_FluxUnisim" "expskin_FluxUnisim" "nucleoninexsec_FluxUnisim" "nucleontotxsec_FluxUnisim" "nucleonqexsec_FluxUnisim" "pioninexsec_FluxUnisim" "piontotxsec_FluxUnisim" "pionqexsec_FluxUnisim")

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

      cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/02c1_2/flux/validation/$dir/

      spectra_filename="/sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/responses/02c1_2/${dir}/valor_splines_${s}_${p}_BNB_FHC_${d}_spectra.root"
      printf "Spectra filename: %s \n" $spectra_filename

      valor_sbn-tweak_pdf_nsigma_var \
        --config $config_filename_inc \
        --params $p \
        --sample $s \
        --physics-hypothesis void \
        --universe-spectra $spectra_filename

      if [ $? -ne 0 ]; then
        printf "Previous command failed, killing the jobs so you can debug \n"
        mail -s 'Tweaks flux script failed' rjones0211@hotmail.com <<< 'Failed in sample '$s', detector '$d', and parameter '$p''
        return
      fi

    done
  done
done
