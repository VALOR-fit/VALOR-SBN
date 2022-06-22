models=("susav2" "smith" "lse" "plus50pctBE" "plus50pct2p2h" "minus50pctBE" "minus50pct2p2h" "2020a1" "v2Default")
configs=("v3_susav2" "v3_smith" "v3_lse" "v3_plus50pctBE" "v3_plus50pct2p2h" "v3_minus50pctBE" "v3_minus50pct2p2h" "v3_2020a1" "v2_default")

#models=("2020a1" "v2Default")
#configs=("v3_2020a1" "v2_default")

cd $VALOR_SBN/mock_data_challenge/thesis/contributions

for i in ${!models[@]}; do
  m=${models[$i]}
  c=${configs[$i]}
  
  printf "Model: ${m} \n"
  
  # Define relevant config
  config="analysis/sbn_numu_disapp_genie_${c}.xml"

  #Write the PDFs
  valor-write_pdf \
    --config $config \
    --write-opt pdfts_rf+pdfcs_rf+SB \
    --output-name mda_${m}_pdf

  spectra_file=mda_${m}_spectra.root

  #Plot and save the spectra
  valor -l -b -q $VALOR_SBN/macros/spectra/rj_plot_pdf.C'("'${config}'","mda_'${m}'_pdf.root","valor",1,"stacked","","'${spectra_file}'")'

done
