#!/bin/bash

params=("all" "modern_xsec" "proposal_xsec" "flux" "hadronic" "all_xsec")

param_tags=("all" "modern_xsec" "proposal_xsec" "flux_uncorr" "flux_corr" "xsec")

#params=("all")

#param_tags=("all")

samples=("numuCCincl" "numuCC0piNtrk" "numuCCoth")

sample_tags=("inc" "0pi" "oth")

detectors=("nd" "ub" "fd")

directories=("sbnd" "uboone" "icarus")

#parameters
for i in ${!params[@]}; do
  p=${params[$i]}
  pt=${param_tags[$i]}

  if [ $p == "hadronic" ]; then
    ## For the correlated flux parameters
    hadronic_dir="/sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/validation/flux_corr/final_final"
    valor_file="$hadronic_dir/tweaks_valor_ereco.root"
    univ_file="$hadronic_dir/tweaks_univ_flux_corr.root"
    output_location="$hadronic_dir/tn"
    if [ ! -d $output_location ]; then
      mkdir -p $output_location
    fi

    tag="${pt}"
    echo $tag

    cd $output_location
    echo `pwd`

    root -l -b -q $VALOR_SBN/macros/systematic_construction/plot_envelope_ratios.C'("'$valor_file'","'$univ_file'","'$output_location'","'$tag'","numuCCincl")'
  fi
  # samples
  for j in ${!samples[@]}; do
    s=${samples[$j]}
    t=${sample_tags[$j]}

    # detectors
    for k in ${!detectors[@]}; do
      d=${detectors[$k]}
      dir=${directories[$k]}

      ## For spline parameters
      if [ $p != "hadronic" ]; then

        valor_file="/sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/validation/splines/$p/valor_tweak_pdf_${t}_${d}.root"
        univ_file="/sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/${p}/validation/${dir}/all/tweaks_${pt}_${s}.root"
        output_location="/sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/validation/splines/tn/$p/"
        if [ ! -d $output_location ]; then
          mkdir -p $output_location
        fi

        tag="${dir}_${t}"
        echo $tag

        cd $output_location
        echo `pwd`

        root -l -b -q $VALOR_SBN/macros/systematic_construction/plot_envelope_ratios.C'("'$valor_file'","'$univ_file'","'$output_location'","'$tag'","'$s'")'
     
      fi
      
    done
  done
done
