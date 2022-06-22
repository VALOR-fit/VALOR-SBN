configs=("08a2020" "08a2020")
fits=("v2DefaultOrig2" "v2DefaultOrig2")
incexc=("inc" "exc")
runs=("11" "11")

detectors=("nd")

cd $VALOR_SBN/mock_data_challenge/thesis/fits

for i in ${!configs[@]}; do
  c=${configs[$i]}
  f=${fits[$i]}
  ie=${incexc[$i]}
  run=${runs[$i]}
  
  for j in ${!detectors[@]}; do
    d=${detectors[$j]}

    # Define relevant config
    config="analysis/sbn_numu_disapp_2020a1_03c1_${c}_${d}_${run}.xml"
    if [ $ie == "exc" ]; then
      config="analysis/sbn_numu_disapp_exclusive_1_2020a1_03c1_${c}_${d}_${run}.xml"
    fi
    
    printf `readlink -f $VALOR_SBN/config/${config}`
    printf "\n"
    
    nohup \
      valor-run_fit \
      --tag sbn-mdc-${f}-${ie} \
      --first-octant \
      --run 1 \
      --ntoymc 1 \
      --param-values-option prefit-errors \
      --fitter minuit+with_simplex_fallback \
      --config $config \
      --mesg-thresholds verbosity.xml \
      --without-stat-fluct \
      --normal \
      --load-prior-from-file - \
      --pot-override -999 \
      --store-spectra \
      --physics-hypothesis void \
      --osc-prior-file priors/void_priors.xml \
      --read-data \
      > ${f}-${ie}.out 2> ${f}-${ie}.err < /dev/null &
  
  done
done
