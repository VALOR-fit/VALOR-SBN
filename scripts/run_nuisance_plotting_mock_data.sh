#models=("susav2" "smith" "lse" "plus50pctBE" "plus50pct2p2h" "minus50pctBE" "minus50pct2p2h" "v2Default" "v2Default" "v2Default" "v2Default")
#configs=("2_susav2" "2_smith" "2_lse" "2_plus50pctBE" "2_plus50pct2p2h" "2_minus50pctBE" "2_minus50pct2p2h" "2_08a2020" "2_08a2020" "2_08a2020" "2_08a2020")
#incexc=("exc" "exc" "exc" "exc" "exc" "exc" "exc" "exc" "inc" "inc" "inc")
#runs=("1" "1" "1" "1" "1" "1" "1" "11" "11" "11_2pct_escale" "11_5pct_escale")

models=("v2DefaultOrig2" "v2DefaultOrig2")
configs=("08a2020" "08a2020")
incexc=("inc" "exc")
runs=("11" "11")

detectors=("nd")
detector_tags=("SBND")

thesis=(0 1)

#models=("susav2")
#configs=("2_susav2")
#incexc=("exc")
#runs=("1")

for t in ${thesis[@]}; do

  if [ $t == 1 ]; then
    cd $VALOR_SBN/mock_data_challenge/thesis/nuisance
    echo `pwd` 
  else 
    cd $VALOR_SBN/mock_data_challenge/thesis/nuisance/pres
    echo `pwd` 
  fi

  for i in ${!models[@]}; do
    m=${models[$i]}
    c=${configs[$i]}
    ie=${incexc[$i]}
    run=${runs[$i]}
    
    for j in ${!detectors[@]}; do
      d=${detectors[$j]}
      dt=${detector_tags[$j]}

      tag="numuCCincl"
      config="analysis/sbn_numu_disapp_2020a1_03c1_${c}_${d}_${run}.xml"
      if [ $t == 1 ]; then 
        fit="../fits/sbn-mdc-${m}-${ie}_1.root"
      else
        fit="../../fits/sbn-mdc-${m}-${ie}_1.root"
      fi
      
      # Exclusive-specific naming
      if [ ${ie} == "exc" ]; then
        tag="numuCCexcl"
        config="analysis/sbn_numu_disapp_exclusive_1_2020a1_03c1_${c}_${d}_${run}.xml"
      fi

      valor -b -q $VALOR_SBN/macros/mock_data_challenge/sbn_mdc_postfit_parameter_pulls.C'("'${config}'","'${fit}'","'${tag}'","'${d}'_'${m}'",'${t}')'

    done
  done
done
