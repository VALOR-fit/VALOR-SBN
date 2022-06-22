#!/bin/bash

: << 'END'
datasets=("2020a1_03c1_nd_fd" "2020a1_03c1_nd_ub" "2020a1_03c1_ub_fd" "2020a1_03c1_nd" "2020a1_03c1_ub" "2020a1_03c1_fd" "inj_2020a1_03c1" "inj_2020a1") 
labels=("2020a1-03c1-nd-fd" "2020a1-03c1-nd-ub" "2020a1-03c1-ub-fd" "2020a1-03c1-nd" "2020a1-03c1-ub" "2020a1-03c1-fd" "inj-2020a1-03c1" "inj-2020a1")
stat=(0 0 0 0 0 0 0 1)
exclusion=(1 1 1 1 1 1 0 0)
END

datasets=("inj_2020a1_03c1" "inj_2020a1")
labels=("inj-2020a1-03c1" "inj-2020a1")
stat=(0 1)
exclusion=(0 0)

cd $VALOR_SBN/contours/thesis/allowed/test 

for data in ${!datasets[@]}
do
  d=${datasets[$data]}
  l=${labels[$data]}
  s=${stat[$data]}

  label="stat-only-$l"
  tag="stat_only"
  if [ $s == 0 ]; then
    label="stat-syst-$l"
    tag="stat_syst"
  fi

  for dir in /pnfs/sbnd/persistent/users/rsjones/valor_sbn_sensitivity_${d}/all
  do
    if [ $exclusion == 1 ]; then
      python /sbnd/app/users/rsjones/VALOR/VALOR-SBN/macros/contours/fit_result_to_graphs.py \
        ''$dir'/*' \
        -l $label \
        -t $tag \
        --exclusion
    else
      python /sbnd/app/users/rsjones/VALOR/VALOR-SBN/macros/contours/fit_result_to_graphs.py \
        ''$dir'/*' \
        -l $label \
        -t $tag 
    fi
  done
done
