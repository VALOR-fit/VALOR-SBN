#models=("susav2" "smith" "lse" "plus50pctBE" "plus50pct2p2h" "minus50pctBE" "minus50pct2p2h" "2020a1" "v2Default")
#configs=("v3_susav2" "v3_smith" "v3_lse" "v3_plus50pctBE" "v3_plus50pct2p2h" "v3_minus50pctBE" "v3_minus50pct2p2h" "v3_2020a1" "v2_default")

analysis=("numu_disapp") #"nue_app")
models=("Nieves2023") #"cohgamma") #Nieves2023")
configs=("2023a1") #genie_v3_cohgamma")
detectors=("nd")

#cd $VALOR_SBN/caf_test/pdfs/nieves2023/orig
#cd $VALOR_SBN/caf_test/pdfs/nieves2023/geom
cd $VALOR_SBN/caf_test/pdfs/nieves2023/prop
#cd $VALOR_SBN/caf_test/pdfs/cohgamma/nue

for i in ${!models[@]}; do
  m=${models[$i]}
  c=${configs[$i]}
  a=${analysis[$i]}
  
  printf "Model: ${m} \n"
  
  for i in ${!detectors[@]}; do
    d=${detectors[$i]}

    # Define relevant config
    if [ ${d} == "all" ]; then
      config="analysis/sbn_${a}_${c}_1.xml"
    else
      config="analysis/sbn_${a}_${c}_${d}_1.xml"
    fi

    # Define relevant config
    #config="analysis/sbn_numu_disapp_genie_${c}.xml"

    #Write the PDFs
    valor-write_pdf \
      --config $config \
      --write-opt pdfts_rf+pdfcs_rf+SB \
      --output-name stacked_${m}_pdf

    spectra_file=stacked_${m}_spectra.root

    #Plot and save the spectra
    valor -l -b -q $VALOR_SBN/macros/spectra/rj_plot_pdf.C'("'${config}'","stacked_'${m}'_pdf.root","valor",1,"stacked","","'${spectra_file}'")'

  done
done
