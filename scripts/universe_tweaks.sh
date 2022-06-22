#!/bin/bash

params=("xsec")

param_locations=("all_xsec")

samples=("numuCCincl" "numuCC0piNtrk" "numuCCoth")

l_samples=("numuccinc" "numucc0pi" "numuccoth")

detectors=("nd" "ub" "fd")

directories=("sbnd" "uboone" "icarus")

det_configs=("sbn_nd" "sbn_uboone" "sbn_icarus")

# samples=("numuCCincl")

# l_samples=("numuccinc")

# detectors=("nd")

# directories=("sbnd")

# det_configs=("sbn_nd")

#parameters
for i in ${!params[@]}; do
  p=${params[$i]}
  l=${param_locations[$i]}

  # samples
  for j in ${!samples[@]}; do
    s=${samples[$j]}
    sample=${l_samples[$j]}

    # detectors
    for k in ${!detectors[@]}; do
      d=${detectors[$k]}
      dir=${directories[$k]}
      conf=${det_configs[$k]}

      config_filename_inc="analysis/sbn_numu_disapp_2020a1_1_${d}.xml"
      config_filename_0pi="analysis/sbn_numu_disapp_2020a1_1_${d}_cc0pi.xml"
      config_filename_oth="analysis/sbn_numu_disapp_2020a1_1_${d}_ccoth.xml"

      if [ ! -d "/sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/$l/validation/$dir/all/" ]
      then
        mkdir -p /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/$l/validation/$dir/all/
      fi

      cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/$l/validation/$dir/all/
      printf "Moving to: \n"
      printf `pwd`
      printf "\n"

      if [ $s == 'numuCCincl' ]
      then
        printf "Tweaking CC Inclusive sample \n"
        valor_sbn-universe_variation_tweaks \
          --config $config_filename_inc \
          --input /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/valor_sbncode_fhc_${sample}_disappearance_${d}_minidst_mc.root \
          --params $p \
          --kine-var ereco \
          --sample $s \
          --detector $conf \
          --ntoys 500

      elif [ $s == 'numuCC0piNtrk' ]
      then
        printf "Tweaking CC 0Pi sample \n"
        valor_sbn-universe_variation_tweaks \
          --config $config_filename_0pi \
          --input /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/valor_sbncode_fhc_${sample}_disappearance_${d}_minidst_mc.root \
          --params $p \
          --kine-var ereco \
          --sample $s \
          --detector $conf \
          --ntoys 500


      elif [ $s == 'numuCCoth' ]
      then
        printf "Tweaking CC Other sample \n"
        valor_sbn-universe_variation_tweaks \
          --config $config_filename_oth \
          --input /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/valor_sbncode_fhc_${sample}_disappearance_${d}_minidst_mc.root \
          --params $p \
          --kine-var ereco \
          --sample $s \
          --detector $conf \
          --ntoys 500

      fi
    done
  done
done
