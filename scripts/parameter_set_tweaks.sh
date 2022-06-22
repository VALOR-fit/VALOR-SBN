#!/bin/bash

#categories=("allsyst" "modern" "proposal" "flux_uncorr" "allxsecsplines")

#param_locations=("all" "modern_xsec" "proposal_xsec" "flux" "all_xsec")

samples=("numuCCincl" "numuCC0piNtrk" "numuCCoth")

detectors=("nd" "ub" "fd")

categories=("univ")

param_locations=("all")

#parameters
for i in ${!categories[@]}; do
  c=${categories[$i]}
  l=${param_locations[$i]}

  # samples
  for j in ${!samples[@]}; do
    s=${samples[$j]}

    # detectors
    for k in ${!detectors[@]}; do
      d=${detectors[$k]}

      config_filename_inc="analysis/sbn_numu_disapp_2020a1_03c1_${d}_1.xml"
      config_filename_0pi="analysis/sbn_numu_disapp_2020a1_03c1_${d}_1_cc0pi.xml"
      config_filename_oth="analysis/sbn_numu_disapp_2020a1_03c1_${d}_1_ccoth.xml"

      cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/validation/splines/$l/

      printf "Moving to: \n"
      printf `pwd`
      printf "\n"

      if [ $s == 'numuCCincl' ]
      then
        printf "Tweaking CC Inclusive sample \n"
        valor-tweak_pdf_N \
          --config $config_filename_inc \
          --output valor_tweak_pdf_inc_${d}.root \
          --ntoys 5000 \
          --params $c \
          --physics-hypothesis void

      elif [ $s == 'numuCC0piNtrk' ]
      then
        printf "Tweaking CC 0Pi sample \n"
        valor-tweak_pdf_N \
          --config $config_filename_0pi \
          --output valor_tweak_pdf_0pi_${d}.root \
          --ntoys 5000 \
          --params $c \
          --physics-hypothesis void


      elif [ $s == 'numuCCoth' ]
      then
        printf "Tweaking CC Other sample \n"
        valor-tweak_pdf_N \
          --config $config_filename_oth \
          --output valor_tweak_pdf_oth_${d}.root \
          --ntoys 5000 \
          --params $c \
          --physics-hypothesis void

      fi
    done
  done
done
