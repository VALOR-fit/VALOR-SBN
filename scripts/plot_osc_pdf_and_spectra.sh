detectors=("all") # "nd" "ub" "fd" "nd_fd"
sinsq=("unosc" "0.07" "0.0065" "0.0185")
dmsq=("unosc" "1.32" "100" "1")

cd $VALOR_SBN/rebase_test/pdfs
rm -f *.root*
rm -f *.list*

spectraFile="spectraFiles.list"

for i in ${!detectors[@]}; do
  d=${detectors[$i]}

  # Define relevant config
  if [ ${d} == "all" ]; then
    config="analysis/sbn_numu_disapp_2020a1_1.xml"
  else
    config="analysis/sbn_numu_disapp_2020a1_${d}_1.xml"
  fi

  for j in ${!sinsq[@]}; do
    s=${sinsq[$j]}
    dm=${dmsq[$j]}

    printf "\nDetector: ${d}, sinsq2theta: ${s}, dmsq: ${dm} \n\n"

    if [ ${s} == "unosc" ]; then
      #Write the PDFs
      valor-write_pdf \
        --config ${config} \
        --write-opt pdfts_rf+pdfcs_rf+SB \
        --output-name VALOR_unosc_pdf \
        --physics-hypothesis void
      
      # Now write the spectra
      valor -l -b -q $VALOR_SBN/macros/spectra/rj_plot_pdf.C'("'${config}'","VALOR_unosc_pdf.root","valor",1,"total","","VALOR_unosc_spectra.root")'
    
    else
      #Write the PDFs
      valor-write_pdf \
        --config ${config} \
        --write-opt pdfts_rf+pdfcs_rf+SB \
        --output-name VALOR_${d}_sinsq_${s}_dmsq_${dm}_pdf \
        --physics-hypothesis eff_sterile_osc \
        --input-sinsq2thMuMu ${s} \
        --input-dm41sq ${dm}
    
      # Now write the spectra
      valor -l -b -q $VALOR_SBN/macros/spectra/rj_plot_pdf.C'("'${config}'","VALOR_'${d}'_sinsq_'${s}'_dmsq_'${dm}'_pdf.root","valor",1,"total","","VALOR_'${d}'_sinsq_'${s}'_dmsq_'${dm}'_spectra.root")'
    
      ## Now append the file to the list
      echo "VALOR_${d}_sinsq_${s}_dmsq_${dm}_spectra.root ${s} ${dm}" >> ${spectraFile}

    fi
  

  done

  ## Now overlay the ratios 
  root -l -b -q ${VALOR_SBN}/macros/spectra/spectral_comparisons.C'("'${spectraFile}'", "ratio", "total", 1)'


  ## Now overlay the spectra
  root -l -b -q ${VALOR_SBN}/macros/spectra/spectral_comparisons.C'("'${spectraFile}'", "spectra", "total", 0)'

done
