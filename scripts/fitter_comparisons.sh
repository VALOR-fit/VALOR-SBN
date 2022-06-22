#!/bin/bash

dm41sq=("0.2" "0.3" "100" "100" "1" "2")
sinsq2th=("6e-2" "0.1" "1.8e-3" "6e-3" "4e-3" "9e-3")

# Navigate to the output directory
cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/pdfs/sbn/overlays_and_ratios/2019b3_90pct_5sigma_points

#parameters
for i in ${!dm41sq[@]}; do
  dmsq=${dm41sq[$i]}
  sinsq=${sinsq2th[$i]}

  # Run the statistical comparison macro
  root -l -b -q $VALOR_SBN/macros/comparisons/fitter_statistics.C'("'${dmsq}'","'${sinsq}'")'

  # Run the spectral overlay macro
  root -l -b -q $VALOR_SBN/macros/comparisons/fitter_spectral_overlays.C'("'${dmsq}'","'${sinsq}'")'

  # Run the spectral ratio macro
  root -l -b -q $VALOR_SBN/macros/comparisons/fitter_spectral_ratios.C'("'${dmsq}'","'${sinsq}'")'

done
