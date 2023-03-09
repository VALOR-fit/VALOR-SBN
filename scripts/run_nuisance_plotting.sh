detectors=("nd" "sbn")

thesis=(0 1)

for t in ${thesis[@]}; do
  for j in ${!detectors[@]}; do
    d=${detectors[$j]}

    tag="2020a1_03d1"

    config="analysis/sbn_numu_disapp_${tag}_${d}_1.xml"
    fit="../fits/sbn_sterile_gbf_${tag}_${d}_1.root"
    if [ ${d} == "sbn" ]; then
      config="analysis/sbn_numu_disapp_${tag}_1.xml"
      fit="../fits/sbn_sterile_gbf_${tag}_1.root"
    fi
    
    valor -b -q $VALOR_SBN/macros/mock_data_challenge/sbn_mdc_postfit_parameter_pulls.C'("'${config}'","'${fit}'","'${tag}'_'${t}'","'${d}'",'${t}')'

  done
done
