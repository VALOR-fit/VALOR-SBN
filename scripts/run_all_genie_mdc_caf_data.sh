#!/bin/bash

flux=("Nue_Int")

model_inputs=("COHGamma") #"Nieves") 
model_outputs=("COHGamma") #"Nieves")
datasets=(1) # 1)
nfiles=(310) #561 icarus) #310 # sbnd COHGAMMA) # 322 SBNDNieves) MUST BE THE TOTAL NUMBER RUN IN ORDER TO SCALE TO THE 'GOOD' EVENT RATE

#sample_tags=("numuccinc" "numucc0pi" "numuccoth")
#samples=("numuCCincl" "numuCC0piNtrk" "numuCC0piNtrk")
#other=(0 0 1)
#detector_names=("SBND" "Uboone" "Icarus")
#detector_tags=("nd" "ub" "fd")
#directories=("sbnd" "uboone" "icarus")

sample_tags=("nuelikecchigh")
samples=("nuelikeCChigh")
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

    for l in ${!model_inputs[@]}; do
      mi=${model_inputs[$l]}
      mo=${model_outputs[$l]}
      m=${datasets[$l]}
      f=${nfiles[$l]}

      output_dir=/sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/mock_data/${mo}

      for p in ${!flux[@]}; do
        fl=${flux[$p]}

        if [ ! -d ${output_dir} ]; then
          mkdir -p ${output_dir}
        fi

        if [ $o == 0 ]
        then
          valor_sbn-make_caf_minidst \
            --input /sbnd/data/users/rsjones/GEVGEN/mockdata_samples_2023/artFiles/cafs/${mi}/genie2art_${dir}_*${fl}*.flat.caf.root \
            --output ${output_dir}/valor_caf_fhc_${t}_disappearance_${d}_minidst_${fl}_1.root \
            --sample $s \
            --n-gen-files $f \
            --no-truth
        else
          valor_sbn-make_caf_minidst \
            --input /sbnd/data/users/rsjones/GEVGEN/mockdata_samples_2023/artFiles/cafs/${mi}/genie2art_${dir}_*${fl}*.flat.caf.root \
            --output ${output_dir}/valor_caf_fhc_${t}_disappearance_${d}_minidst_${fl}_1.root \
            --sample $s \
            --other-sample \
            --n-gen-files $f \
            --no-truth
        fi

      done
    done
  done
done
