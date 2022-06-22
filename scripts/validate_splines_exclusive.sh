#!/bin/bash

params=("ccother_migration")

short_params=("ccother_migration")

samples=("numuCC0piNtrk" "numuCCoth")

detectors=("sbn_nd" "sbn_uboone" "sbn_icarus")
#detectors=("sbn_nd")

directories=("sbnd" "uboone" "icarus")
#directories=("sbnd")

#parameters
for i in ${!params[@]}; do
  p=${params[$i]}
  loc=${short_params[$i]}

  for j in ${!samples[@]}; do
    s=${samples[$j]}

    # detectors
    for k in ${!detectors[@]}; do
      d=${detectors[$k]}
      dir=${directories[$k]}

      if [ ! -d "/sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/exclusive25pctGOOD/validation/${dir}/${loc}" ]
      then
        mkdir /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/exclusive25pctGOOD/validation/${dir}/${loc}
      fi

      cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/exclusive25pctGOOD/validation/${dir}/

      valor -l -b -q $VALOR_SBN/macros/systematic_construction/exclusive_spline_validation.C'("'${p}'","'${s}'","BNB_FHC","'${d}'","","/sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/responses/03c1/'${dir}'/",1,false,"nsigma_var","/sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/exclusive25pctGOOD/validation/'${dir}'/'${loc}'/")'

      if [ $? -ne 0 ]; then
        printf "Previous command failed, killing the jobs so you can debug \n"
        mail -s 'Validate proposal script failed' rjones0211@hotmail.com <<< 'Failed in sample '$s', detector '$d', and parameter '$p''
        return
      fi

      printf "\n Finshed running validation of ${p} and ${s} in ${d} \n"
    done 
  done
done
