#!/bin/bash

#sample_tags=("numuccinc" "numucc0pi" "numuccoth")
#samples=("numuCCincl" "numuCC0piNtrk" "numuCC0piNtrk")
#other=(0 0 1)
#detector_names=("SBND" "Uboone" "Icarus")
#detector_tags=("nd" "ub" "fd")
#directories=("sbnd" "uboone" "icarus")

sample_tags=("numuccinc")
samples=("numuCCincl")
other=(0)
detector_names=("SBND")
detector_tags=("nd")
directories=("sbnd")

# samples
for j in ${!samples[@]}; do
  s=${samples[$j]}
  t=${sample_tags[$j]}
  o=${other[$j]}

  # detectors
  for k in ${!detector_names[@]}; do
    d=${detector_tags[$k]}
    n=${detector_names[$k]}
    dir=${directories[$k]}

    if [ $o == 0 ]
    then
      valor_sbn-make_caf_minidst \
        --input /sbnd/data/users/rsjones/GEVGEN/mockdata_samples_2023/artFiles/cafs/${m}/genie2art_${dir}_2023_1001_GenieGen-20230215T162839_G4-20230220T155723.flat.caf.root \
        --output /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/dsts/2020a1/valor_caf_fhc_${t}_disappearance_${d}_minidst_mc.root \
        --sample $s
    else
      valor_sbn-make_caf_minidst \
        --input /sbnd/data/users/rsjones/GEVGEN/mockdata_samples_2023/artFiles/cafs/${m}/genie2art_${dir}_2023_1001_GenieGen-20230215T162839_G4-20230220T155723.flat.caf.root \
        --output /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/dsts/2020a1/valor_caf_fhc_${t}_disappearance_${d}_minidst_mc.root \
        --sample $s \
        --other-sample
    fi

  done
done
