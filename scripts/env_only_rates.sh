#!/bin/bash
samples=("numuCCincl")
detectors=("sbn_nd" "sbn_uboone" "sbn_icarus")
short_names=("nd" "ub" "fd")

for j in ${!samples[@]}; do
  s=${samples[$j]}
  tag="inc"
  a="inclusive"
  if [ ${s} != "numuCCincl" ]; then
    a="exclusive"
    tag="exc_inc"
  fi
for l in ${!detectors[@]}; do
  d=${detectors[$l]}
  n=${short_names[$l]}

  spectra_dir=${VALOR_SBN}/pdfs/sbn/2020a1/Feb2022
  pf_file="${spectra_dir}/${n}_tweak_pdf_03c1_${tag}.root"
  
  cd $spectra_dir

  valor -l -b -q $VALOR_SBN/macros/mock_data_challenge/env_only_rates.C'("'${pf_file}'","'${d}'","'${s}'","'${a}'","'${tag}'_rates.txt")'

  cd -

  done
done
