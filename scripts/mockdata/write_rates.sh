#!/bin/bash

#models=("susav2" "smith" "lse" "plus50pctBE" "plus50pct2p2h" "minus50pctBE" "minus50pct2p2h" "v2Default" "susav2" "smith" "lse" "plus50pctBE" "plus50pct2p2h" "minus50pctBE" "minus50pct2p2h" "v2Default" "susav2Orig" "smithOrig" "lseOrig" "plus50pctBEOrig" "plus50pct2p2hOrig" "minus50pctBEOrig" "minus50pct2p2hOrig" "v2DefaultOrig" "v2DefaultOrig2" "susav2Orig" "smithOrig" "lseOrig" "plus50pctBEOrig" "plus50pct2p2hOrig" "minus50pctBEOrig" "minus50pct2p2hOrig" "v2DefaultOrig" "v2DefaultOrig2")
#incexc=("exc" "exc" "exc" "exc" "exc" "exc" "exc" "exc" "inc" "inc" "inc" "inc" "inc" "inc" "inc" "inc" "exc" "exc" "exc" "exc" "exc" "exc" "exc" "exc" "exc" "inc" "inc" "inc" "inc" "inc" "inc" "inc" "inc" "inc")
models=("v2DefaultOrig" "v2DefaultOrig" "v2Default" "v2Default" "susav2" "smith" "lse" "plus50pctBE" "plus50pct2p2h" "minus50pctBE" "minus50pct2p2h")
incexc=("exc" "inc" "exc" "inc" "exc" "exc" "exc" "exc" "exc" "exc" "exc")
#models=("susav2")
#incexc=("exc")

s="numuCCincl"

detectors=("sbn_nd" "sbn_icarus")
short_names=("nd" "fd")
#detectors=("sbn_nd")
#short_names=("nd")

if [ ! -d "${VALOR_SBN}/mock_data_challenge/thesis/rates/fixed" ]; then
  mkdir ${VALOR_SBN}/mock_data_challenge/thesis/rates/fixed
fi
cd ${VALOR_SBN}/mock_data_challenge/thesis/rates/fixed

for j in ${!models[@]}; do
  m=${models[$j]}
  ie=${incexc[$j]}
  tag="inc"
  a="inclusive"
  if [ ${ie} == "exc" ]; then
    a="exclusive"
    tag="exc_inc"
  fi
  for l in ${!detectors[@]}; do
    d=${detectors[$l]}
    n=${short_names[$l]}

    spectra_dir=${VALOR_SBN}/mock_data_challenge/thesis/spectra/fixed/
    fit_dir=${VALOR_SBN}/mock_data_challenge/thesis/fits/
    md_file="${spectra_dir}/${n}_mc_data_${m}_inc_pdf.root"
    pf_file="${spectra_dir}/${n}_tweak_pdf_postfit_${m}_${tag}.root"
    fit_file="${fit_dir}/sbn-mdc-${m}-${ie}_1.root"

    valor -l -b -q $VALOR_SBN/macros/mock_data_challenge/rates.C'("'${md_file}'","'${pf_file}'","'${fit_file}'","'${d}'","'${s}'","'${a}'","'${m}'","'${n}'_'${ie}'_rates.txt")'

  done
done
