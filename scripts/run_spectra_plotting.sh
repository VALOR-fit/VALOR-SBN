#!/bin/bash 

sinsq=("free")
dmsq=("free")
postfit=("y")

configs=("2020a1_03c1_lse_nd" "2020a1_03c1_lse_fd")
fits=("free_2020a1_03c1_lse" "free_2020a1_03c1_lse")
tag=("nd_lse" "fd_lse")
detector_tags=("SBND" "ICARUS")
detector_enums=("1" "3")

location="rebase_test"

cd $VALOR_SBN/rebase_test/envelopes/free_params/from_gbf/

for j in ${!configs[@]}; do
  f=${fits[$j]}
  t=${tag[$j]}
  c=${configs[$j]}
  dt=${detector_tags[$j]}
  de=${detector_enums[$j]}

  printf "Detector: ${dt} \n"
  
  # Define relevant config
  config="analysis/sbn_numu_disapp_${c}_1.xml"
  
  printf `readlink -f $VALOR_SBN/config/${config}`
  printf "\n"

  # Make desired spectra
  valor-tweak_pdf_N \
    --config $config \
    --output ${t}_tweak_pdf_prefit.root \
    --ntoys 1000 \
    --physics-hypothesis void
  
  $VALOR_SBN/macros/mock_data_challenge/draw_postfit_data_error_envelope.py \
    -c $config \
    -p ${t}_tweak_pdf_prefit.root \
    -f root \
    -t ${t}-prefit \
    -e ${de} \
    --plabel "${dt} prefit #pm 1 #sigma" \

  for j in ${!sinsq[@]}; do
    s=${sinsq[$j]}
    dm=${dmsq[$j]}
    pf=${postfit[$j]}

    printf "\nDetector: ${dt}, sinsq2theta: ${s}, dmsq: ${dm} \n\n"

    if [ ${s} == "unosc" ]; then
      #Write the PDFs
      valor-write_pdf \
        --config ${config} \
        --write-opt pdfts_rf+pdfcs_rf+SB \
        --output-name ${t}_VALOR_unosc_pdf \
        --physics-hypothesis void
    
      $VALOR_SBN/macros/mock_data_challenge/draw_postfit_data_error_envelope.py \
        -c $config \
        -a ${t}_VALOR_unosc_pdf.root \
        -p ${t}_tweak_pdf_prefit.root \
        -f root \
        -t ${t}-prefit \
        -e ${de} \
        --plabel "${dt} prefit #pm 1 #sigma" \
        --alabel "${dt} unoscillated spectra" 
      
      if [ ${pf} == "y" ]; then
        
        valor-tweak_pdf_N \
          --config $config \
          --output ${t}_tweak_pdf_postfit.root \
          --ntoys 1000 \
          --load-prior-from-file $VALOR_SBN/${location}/fits/sbn_sterile_${f}_1.root \
          --physics-hypothesis void
  
        $VALOR_SBN/macros/mock_data_challenge/draw_postfit_data_error_envelope.py \
          -c $config \
          -p ${t}_tweak_pdf_postfit.root \
          -f root \
          -t ${t}-postfit \
          -e ${de} \
          --plabel "${dt} postfit #pm 1 #sigma"
      fi
        
    elif [ ${s} == "free" ]; then
      #Write the PDFs
      valor-write_pdf \
        --config ${config} \
        --write-opt pdfts_rf+pdfcs_rf+SB \
        --output-name ${t}_VALOR_free_pdf \
        --physics-hypothesis void
    
      $VALOR_SBN/macros/mock_data_challenge/draw_postfit_data_error_envelope.py \
        -c $config \
        -p ${t}_tweak_pdf_prefit.root \
        -f root \
        -t ${t}-prefit \
        -e ${de} \
        --plabel "${dt} prefit #pm 1 #sigma" \
      
      if [ ${pf} == "y" ]; then
        
        valor-tweak_pdf_N \
          --config $config \
          --output ${t}_tweak_pdf_postfit.root \
          --ntoys 1000 \
          --load-prior-from-file $VALOR_SBN/${location}/fits/sbn_sterile_${f}_1.root \
          --physics-hypothesis eff_sterile_osc
  
        $VALOR_SBN/macros/mock_data_challenge/draw_postfit_data_error_envelope.py \
          -c $config \
          -a ${t}_VALOR_free_pdf.root \
          -p ${t}_tweak_pdf_postfit.root \
          -f root \
          -t ${t}-postfit \
          -e ${de} \
          --plabel "${dt} postfit #pm 1 #sigma" \
          --alabel "Unoscillated spectra" 
        
      fi
        
    else
      #Write the PDFs
      valor-write_pdf \
        --config ${config} \
        --write-opt pdfts_rf+pdfcs_rf+SB \
        --output-name VALOR_${t}_sinsq_${s}_dmsq_${dm}_pdf \
        --physics-hypothesis eff_sterile_osc \
        --input-sinsq2thMuMu ${s} \
        --input-dm41sq ${dm}
    
      $VALOR_SBN/macros/mock_data_challenge/draw_postfit_data_error_envelope.py \
        -c $config \
        -a VALOR_${t}_sinsq_${s}_dmsq_${dm}_pdf.root \
        -p ${t}_tweak_pdf_prefit.root \
        -f root \
        -t ${t}-prefit-sinsq2themumu-${s}-dmsq41-${dm} \
        -e ${de} \
        --plabel "${dt} prefit #pm 1 #sigma" \
        --alabel "sin^{2}2#theta = ${s}, #Delta m_{41}^{2} = ${dm}" \
    
      if [ ${pf} == "y" ]; then
        
        valor-tweak_pdf_N \
          --config $config \
          --output ${t}_tweak_pdf_postfit.root \
          --ntoys 1000 \
          --load-prior-from-file $VALOR_SBN/${location}/fits/sbn_sterile_${f}_1.root \
          --physics-hypothesis eff_sterile_osc
  
        $VALOR_SBN/macros/mock_data_challenge/draw_postfit_data_error_envelope.py \
          -c $config \
          -a VALOR_${t}_sinsq_${s}_dmsq_${dm}_pdf.root \
          -p ${t}_tweak_pdf_postfit.root \
          -f root \
          -t ${t}-postfit \
          -e ${de} \
          --plabel "${dt} postfit #pm 1 #sigma" \
          --alabel "sin^{2}2#theta = ${s}, #Delta m_{41}^{2} = ${dm}" 
        
      fi
    fi
  done
done
