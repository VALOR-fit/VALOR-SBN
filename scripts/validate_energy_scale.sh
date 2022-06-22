#!/bin/bash

#samples=("numuCCincl" "numuCC0piNtrk" "numuCCoth")

#config_tags=("" "_cc0pi" "_ccoth")

#detectors=("sbn_nd" "sbn_uboone" "sbn_icarus")

#directories=("sbnd" "uboone" "icarus")

#configs=("nd" "ub" "fd")

#other=(0 0 1)

#inputs=("SBND" "Uboone" "Icarus")

#scales=("1" "2" "5")

samples=("numuCCincl")

config_tags=("")

detectors=("sbn_nd")

directories=("sbnd")

configs=("nd")

other=(0)

inputs=("SBND")

for i in ${!samples[@]}; do
  s=${samples[$i]}

  # detectors
  for j in ${!detectors[@]}; do
    d=${detectors[$j]}
    dir=${directories[$j]}
    c=${configs[$j]}
    t=${config_tags[$j]}
    n=${inputs[$j]}
    o=${other[$j]}

    #for e in $(seq 0.01 0.02 0.05); do
    for e in 0.05; do

      if [ ! -d "/sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/energy_scale/validation/${dir}" ]
      then
        mkdir /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/energy_scale/validation/${dir}
      fi

      cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/energy_scale/validation/${dir}

      config="analysis/sbn_numu_disapp_2020a1_03c1_${c}_1${t}.xml"
      input="/sbnd/data/users/gputnam/NuMu/workshop-game-0320/211a/${dir}/mc/output_SBNOsc_NumuSelection_Modern_${n}.root"
      if [ $o == 0 ]; then 
        valor_sbn-energy_scale_check \
          --config ${config} \
          --input ${input} \
          --sample ${s} \
          --detector ${d} \
          --scale ${e}
      else
        valor_sbn-energy_scale_check \
          --config ${config} \
          --input ${input} \
          --sample ${s} \
          --detector ${d} \
          --scale ${e} \
          --other-sample
      fi

    done 
  done
done
