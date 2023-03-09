location="${VALOR_SBN}/rebase_test/contours/"
pnfs=("2020a1_03c1_exc" "2020a1_03c3_exc_bias_only")
labels=("stat-syst-2020a1-03c1-exc" "stat-syst-2020a1-03c3-exc-bias-only")

cd ${location}

for i in ${!pnfs[@]}; do
  p=${pnfs[$i]}
  l=${labels[$i]}

  files=/pnfs/sbnd/persistent/users/rsjones/2022/valor_sbn_sensitivity_${p}/all/*

  python /sbnd/app/users/rsjones/VALOR/VALOR-SBN/macros/contours/fit_result_to_graphs.py "${files}" -l ${l} -t stat_syst -p MuMu --exclusion

done
