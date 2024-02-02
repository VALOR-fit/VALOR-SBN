#!/bin/bash

flux=("_Nue_Int" "_Nue_Numu") #"" "_Nue_Int" "_Nue_Numu")

model_inputs=("COHGamma") #"Nieves/test/debuggingStep4") #"COHGamma") 
model_outputs=("COHGamma") #"Nieves2023") #
datasets=(1) # 1)
nfiles=(310) #561) #310 # sbnd COHGAMMA) # 322 SBNDNieves) MUST BE THE TOTAL NUMBER RUN IN ORDER TO SCALE TO THE 'GOOD' EVENT RATE

#sample_tags=("numuccinc" "numucc0pi" "numuccoth")
#samples=("numuCCincl" "numuCC0piNtrk" "numuCC0piNtrk")
#other=(0 0 1)
#detector_names=("SBND" "Uboone" "Icarus")
#detector_tags=("nd" "ub" "fd")
#directories=("sbnd" "uboone" "icarus")

sample_tags=("nuelikecchigh") #"numuccinc")
samples=("nuelikeCChigh") #numuCCincl")
other=(0)

detector_names=("SBND") #"ICARUS") #SBND")
detector_tags=("nd") #"fd") #"nd")
directories=("sbnd") #"icarus") # "SBND") "sbnd")

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

      output_dir=/sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/dsts/genie/${mo}

      for p in ${!flux[@]}; do
        fl=${flux[$p]}

        if [ ! -d ${output_dir} ]; then
          mkdir -p ${output_dir}
        fi

        if [ $o == 0 ]
        then
          valor_sbn-make_caf_minidst \
            --input /sbnd/data/users/rsjones/GEVGEN/mockdata_samples_2023/artFiles/cafs/${mi}/*${dir}*${fl}*.flat.caf.root \
            --output ${output_dir}/valor_caf_fhc_${t}_disappearance_${d}_minidst${fl}_mc.root \
            --sample $s \
            --n-gen-files $f
        else
          valor_sbn-make_caf_minidst \
            --input /sbnd/data/users/rsjones/GEVGEN/mockdata_samples_2023/artFiles/cafs/${mi}/*${dir}*${fl}*.flat.caf.root \
            --output ${output_dir}/valor_caf_fhc_${t}_disappearance_${d}_minidst${fl}_mc.root \
            --sample $s \
            --other-sample \
            --n-gen-files $f
        fi

      done
    done
  done
done
