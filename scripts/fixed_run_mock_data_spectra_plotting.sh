#models=("susav2" "smith" "lse" "plus50pctBE" "plus50pct2p2h" "minus50pctBE" "minus50pct2p2h" "v2Default" "v2Default" "v2Default" "v2Default")
#configs=("2_susav2" "2_smith" "2_lse" "2_plus50pctBE" "2_plus50pct2p2h" "2_minus50pctBE" "2_minus50pct2p2h" "2_08a2020" "2_08a2020" "2_08a2020" "2_08a2020")
#incexc=("exc" "exc" "exc" "exc" "exc" "exc" "exc" "exc" "inc" "inc" "inc")
#runs=("1" "1" "1" "1" "1" "1" "1" "11" "11" "11_2pct_escale" "11_5pct_escale")

models=("v2DefaultOrig" "v2DefaultOrig" "v2Default" "v2Default" "susav2" "smith" "lse" "plus50pctBE" "plus50pct2p2h" "minus50pctBE" "minus50pct2p2h")
configs=("08a2020" "08a2020" "2_08a2020" "2_08a2020" "2_susav2" "2_smith" "2_lse" "2_plus50pctBE" "2_plus50pct2p2h" "2_minus50pctBE" "2_minus50pct2p2h")
incexc=("exc" "inc" "exc" "inc" "exc" "exc" "exc" "exc" "exc" "exc" "exc")
runs=("11" "11" "11" "11" "1" "1" "1" "1" "1" "1" "1")

#models=("v2DefaultOrig2" "v2DefaultOrig2")
#configs=("08a2020" "08a2020")
#incexc=("inc" "exc")
#runs=("11" "11")

detectors=("nd" "fd")
detector_tags=("SBND" "ICARUS")
detector_enums=("1" "3")

#detectors=("nd")
#detector_tags=("SBND")
#detector_enums=("1")

cd $VALOR_SBN/mock_data_challenge/thesis/spectra/fixed

for i in ${!models[@]}; do
  m=${models[$i]}
  c=${configs[$i]}
  ie=${incexc[$i]}
  run=${runs[$i]}
  
  for j in ${!detectors[@]}; do
    d=${detectors[$j]}
    dt=${detector_tags[$j]}
    de=${detector_enums[$j]}

    printf "Model: ${m}, detector: ${d} \n"
    
    # Define relevant config
    config=""
    if [ $ie == "exc" ]; then
      config="analysis/sbn_numu_disapp_exclusive_1_2020a1_03c1_${c}_${d}_${run}.xml"

      #Write the inclusive PDF anyway
      valor-write_pdf \
        --config analysis/sbn_numu_disapp_2020a1_03c1_${c}_${d}_${run}.xml \
        --write-opt pdfts_rf+pdfcs_rf+SB \
        --output-name ${d}_mc_data_${m}_inc_pdf \
        --write-data

    else
      config="analysis/sbn_numu_disapp_2020a1_03c1_${c}_${d}_${run}.xml"
    fi
    printf `readlink -f $VALOR_SBN/config/${config}`
    printf "\n"

    # Make desired spectra
    valor-write_pdf \
      --config $config \
      --write-opt pdfts_rf+pdfcs_rf+SB \
      --output-name ${d}_mc_data_${m}_${ie}_pdf \
      --write-data

    valor-tweak_pdf_N \
      --config $config \
      --output ${d}_tweak_pdf_prefit_${m}_${ie}.root \
      --ntoys 1000 \
      --physics-hypothesis void
    
    valor-tweak_pdf_N \
      --config $config \
      --output ${d}_tweak_pdf_postfit_${m}_${ie}.root \
      --ntoys 1000 \
      --physics-hypothesis void \
      --load-prior-from-file $VALOR_SBN/mock_data_challenge/thesis/fits/sbn-mdc-${m}-${ie}_1.root
   
    # Combine exclusive spectra
    tweak_tag="${ie}"
    echo "$tweak_tag '\n'"
    
    if [ $ie == "exc" ]; then
      valor -b -q $VALOR_SBN/macros/mock_data_challenge/add_tweaks.C'("'${d}'_tweak_pdf_prefit_'${m}'_exc.root","'${d}'_tweak_pdf_prefit_'${m}'_exc_inc.root")'
      valor -b -q $VALOR_SBN/macros/mock_data_challenge/add_tweaks.C'("'${d}'_tweak_pdf_postfit_'${m}'_exc.root","'${d}'_tweak_pdf_postfit_'${m}'_exc_inc.root")'
      tweak_tag="exc_inc"
    fi
    # Now actually make the envelope overlays
    config="analysis/sbn_numu_disapp_2020a1_03c1_${c}_${d}_${run}.xml"

    $VALOR_SBN/macros/mock_data_challenge/draw_postfit_data_error_envelope.py \
      -c $config \
      -a ${d}_mc_data_${m}_inc_pdf.root \
      -b ${d}_tweak_pdf_postfit_${m}_${tweak_tag}.root \
      -p ${d}_tweak_pdf_prefit_${m}_${tweak_tag}.root \
      -f root \
      -t ${d}-data-postfit-prefit-${m}-${ie} \
      -e ${de} \
      -m True \
      --alabel "${dt} mock data" \
      --blabel "${dt} postfit #pm 1 #sigma" \
      --plabel "${dt} prefit #pm 1 #sigma" \
      --ratio 0 
    
    $VALOR_SBN/macros/mock_data_challenge/draw_postfit_data_error_envelope.py \
      -c $config \
      -a ${d}_mc_data_${m}_inc_pdf.root \
      -b ${d}_tweak_pdf_postfit_${m}_${tweak_tag}.root \
      -f root \
      -t ${d}-data-postfit-${m}-${ie} \
      -e ${de} \
      -m True \
      --alabel "${dt} mock data" \
      --blabel "${dt} postfit #pm 1 #sigma" \
      --ratio 0 
  
  done
done
