#!/bin/bash

#params=("all" "modern_xsec" "proposal_xsec" "flux" "all_xsec")

#param_tags=("all" "modern_xsec" "proposal_xsec" "flux_uncorr" "xsec")

#samples=("numuCCincl" "numuCC0piNtrk" "numuCCoth")

#sample_tags=("inc" "0pi" "oth")

#detectors=("nd" "ub" "fd")

#det_enums=(1 2 3)

#directories=("sbnd" "uboone" "icarus")

#det_names=("SBND" "MicroBooNE" "ICARUS")

params=("modern_xsec" "proposal_xsec" "flux")
param_tags=("modern_xsec" "proposal_xsec" "flux_uncorr")
samples=("numuCCincl" "numuCC0piNtrk" "numuCCoth")
sample_tags=("inc" "0pi" "oth")
detectors=("nd" "ub" "fd")
det_enums=(1 2 3)
directories=("sbnd" "uboone" "icarus")
det_names=("SBND" "MicroBooNE" "ICARUS")

#parameters
for i in ${!params[@]}; do
  p=${params[$i]}
  pt=${param_tags[$i]}

  # samples
  for j in ${!samples[@]}; do
    s=${samples[$j]}
    t=${sample_tags[$j]}

    # detectors
    for k in ${!detectors[@]}; do
      d=${detectors[$k]}
      dir=${directories[$k]}
      name=${det_names[$k]}
      enum=${det_enums[$k]}

      config_filename_inc="analysis/sbn_numu_disapp_2020a1_1_${d}.xml"
      config_filename_0pi="analysis/sbn_numu_disapp_2020a1_1_${d}_cc0pi.xml"
      config_filename_oth="analysis/sbn_numu_disapp_2020a1_1_${d}_ccoth.xml"

      tweak_file="/sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/${p}/validation/${dir}/all/tweaks_${pt}_${s}.root"
     
      if [ ! -d "/sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/validation/splines/$p/thesis" ]; then
        mkdir /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/validation/splines/$p/thesis
      fi
      cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/validation/splines/$p/thesis

      printf "Moving to: \n"
      printf `pwd`
      printf "\n"

      if [ $s == 'numuCCincl' ]
      then
        printf "Plotting CC Inclusive sample \n"
        /sbnd/app/users/rsjones/VALOR/VALOR-SBN/macros/mock_data_challenge/draw_postfit_data_error_envelope.py \
          --config $config_filename_inc \
          -p $tweak_file \
          -b ../valor_tweak_pdf_${t}_${d}.root \
          -f root \
          -t ${dir}-valor-universes \
          -e $enum \
          --ratio 1 \
          --plabel "${name} Universes #pm 1 #sigma" \
          --blabel "${name} Splines #pm 1 #sigma"

      elif [ $s == 'numuCC0piNtrk' ]
      then
        printf "Plotting CC 0Pi sample \n"
        /sbnd/app/users/rsjones/VALOR/VALOR-SBN/macros/mock_data_challenge/draw_postfit_data_error_envelope.py \
          --config $config_filename_0pi \
          -p $tweak_file \
          -b ../valor_tweak_pdf_${t}_${d}.root \
          -f root \
          -t ${dir}-valor-universes \
          -e $enum \
          --ratio 1 \
          --plabel "${name} Universes #pm 1 #sigma" \
          --blabel "${name} Splines #pm 1 #sigma"

      elif [ $s == 'numuCCoth' ]
      then
        printf "Plotting CC Other sample \n"
        /sbnd/app/users/rsjones/VALOR/VALOR-SBN/macros/mock_data_challenge/draw_postfit_data_error_envelope.py \
          --config $config_filename_oth \
          -p $tweak_file \
          -b ../valor_tweak_pdf_${t}_${d}.root \
          -f root \
          -t ${dir}-valor-universes \
          -e $enum \
          --ratio 1 \
          --plabel "${name} Universes #pm 1 #sigma" \
          --blabel "${name} Splines #pm 1 #sigma"
      fi
    done
  done
done
