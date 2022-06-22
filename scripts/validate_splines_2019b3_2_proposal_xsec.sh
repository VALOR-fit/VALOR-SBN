#!/bin/bash

params=("genie_ccresAxial_Genie" "genie_ncresAxial_Genie" "genie_qema_Genie" "genie_NC_Genie" "genie_NonResRvp1pi_Genie" "genie_NonResRvp2pi_Genie" "genie_NonResRvbarp1pi_Genie" "genie_NonResRvbarp2pi_Genie")

short_params=("ccresAxial" "ncresAxial" "qema" "NC" "NonResRvp1pi" "NonResRvp2pi" "NonResRvbarp1pi" "NonResRvbarp2pi")

samples=("numuCCincl")

detectors=("sbn_nd" "sbn_uboone" "sbn_icarus")

directories=("sbnd" "uboone" "icarus")

#parameters
for i in ${!params[@]}; do
  p=${params[$i]}
  loc=${short_params[$i]}

  # samples
  for j in ${!samples[@]}; do
    s=${samples[$j]}

    # detectors
    for k in ${!detectors[@]}; do
      d=${detectors[$k]}
      dir=${directories[$k]}

      if [ ! -d "/sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/02c1_2/proposal_xsec/validation/${dir}/${loc}" ]
      then
        mkdir /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/02c1_2/proposal_xsec/validation/${dir}/${loc}
      fi

      cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/02c1_2/proposal_xsec/validation/${dir}/

      valor -l -b -q $VALOR_SBN/macros/systematic_construction/spline_validation.C'("'${p}'","'${s}'","BNB_FHC","'${d}'","","/sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/responses/02c1_2/'${dir}'/",true,1,false,"nsigma_var","/sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/02c1_2/proposal_xsec/validation/'${dir}'/'${loc}'/")'

      if [ $? -ne 0 ]; then
        printf "Previous command failed, killing the jobs so you can debug \n"
        mail -s 'Validate proposal script failed' rjones0211@hotmail.com <<< 'Failed in sample '$s', detector '$d', and parameter '$p''
        return
      fi

      printf "\n Finshed running validation of ${p} and ${s} in ${d} \n"
    done 
  done
done
