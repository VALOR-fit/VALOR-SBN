#!/bin/bash

detectors=("nd" "fd")
pots=("100e20pot" "lowpot" "newpot")

location=/sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/envelopes/ 
cd ${location}

for i in ${!detectors[@]}; do
  d=${detectors[$i]}

  for j in ${!pots[@]}; do
    p=${pots[$j]}

    prefit_file="${d}_tweak_pdf_output_prefit_${p}.root"
    postfit_file="${d}_tweak_pdf_output_postfit_${p}.root"

    valor-tweak_pdf_N \
      --config analysis/sbn_numu_disapp_2020a1_03d1_${d}_1_${p}.xml \
      --load-prior-from-file sbn_2020a1_03d1-sinsq2thMuMu-0.0345510729459222-dm41sq-1.42510267030303_410_${p}.root \
      --output ${postfit_file} \
      --ntoys 10000 \
      --physics-hypothesis void

    valor-tweak_pdf_N \
      --config analysis/sbn_numu_disapp_2020a1_03d1_${d}_1_${p}.xml \
      --output ${prefit_file} \
      --ntoys 10000 \
      --physics-hypothesis void

    if [ ${d} == "nd" ]; then
      $VALOR_SBN/macros/mock_data_challenge/draw_postfit_data_error_envelope.py \
        -c analysis/sbn_numu_disapp_2020a1_03d1_${d}_1_${p}.xml \
        -b ${postfit_file} \
        -p ${prefit_file} \
        -f root \
        -t ${d}-prefit-postfit-${p} \
        -e 1 \
        --blabel 'SBND Postfit #pm 1 #sigma' \
        --plabel 'SBND Prefit #pm 1 #sigma' \
        --ratio 1
    
    elif [ ${d} == "fd" ]; then
      $VALOR_SBN/macros/mock_data_challenge/draw_postfit_data_error_envelope.py \
        -c analysis/sbn_numu_disapp_2020a1_03d1_${d}_1_${p}.xml \
        -b ${postfit_file} \
        -p ${prefit_file} \
        -f root \
        -t ${d}-prefit-postfit-${p} \
        -e 3 \
        --blabel 'ICARUS Postfit #pm 1 #sigma' \
        --plabel 'ICARUS Prefit #pm 1 #sigma' \
        --ratio 1
    
    fi
      
    root -l -b -q $VALOR_SBN/macros/systematic_construction/plot_envelope_ratios_prefit_postfit.C'("'$prefit_file'","'$postfit_file'","'${location}'","'${d}'_'${p}'","numuCCincl")'

  done
done
