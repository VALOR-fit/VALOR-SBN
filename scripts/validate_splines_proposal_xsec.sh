#!/bin/bash

params=("genie_ccresAxial_Genie" "genie_ncresAxial_Genie" "genie_qema_Genie" "genie_NC_Genie" "genie_NonResRvpCC1pi_Genie" "genie_NonResRvnCC1pi_Genie" "genie_NonResRvbarnCC1pi_Genie" "genie_NonResRvbarpCC1pi_Genie" "genie_NonResRvpCC2pi_Genie" "genie_NonResRvnCC2pi_Genie" "genie_NonResRvbarnCC2pi_Genie" "genie_NonResRvbarpCC2pi_Genie" "genie_NonResRvpNC1pi_Genie" "genie_NonResRvnNC1pi_Genie" "genie_NonResRvbarnNC1pi_Genie" "genie_NonResRvbarpNC1pi_Genie" "genie_NonResRvpNC2pi_Genie" "genie_NonResRvnNC2pi_Genie" "genie_NonResRvbarnNC2pi_Genie" "genie_NonResRvbarpNC2pi_Genie")

short_params=("ccresAxial" "ncresAxial" "qema" "NC" "NonResRvpCC1pi" "NonResRvnCC1pi" "NonResRvbarnCC1pi" "NonResRvbarpCC1pi" "NonResRvpCC2pi" "NonResRvnCC2pi" "NonResRvbarnCC2pi" "NonResRvbarpCC2pi" "NonResRvpNC1pi" "NonResRvnNC1pi" "NonResRvbarnNC1pi" "NonResRvbarpNC1pi" "NonResRvpNC2pi" "NonResRvnNC2pi" "NonResRvbarnNC2pi" "NonResRvbarpNC2pi")

samples=("numuCCincl" "numuCC0piNtrk" "numuCCoth")

#detectors=("sbn_nd" "sbn_uboone" "sbn_icarus")

#directories=("sbnd" "uboone" "icarus")

detectors=("sbn_uboone" "sbn_icarus")

directories=("uboone" "icarus")

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

      if [ ! -d "/sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/proposal_xsec/validation/${dir}/${loc}" ]
      then
        mkdir /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/proposal_xsec/validation/${dir}/${loc}
      fi

      cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/proposal_xsec/validation/${dir}/

      valor -l -b -q $VALOR_SBN/macros/systematic_construction/spline_validation.C'("'${p}'","'${s}'","BNB_FHC","'${d}'","","/sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/responses/03c1/'${dir}'/",true,1,false,"nsigma_var","/sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/proposal_xsec/validation/'${dir}'/'${loc}'/")'

      if [ $? -ne 0 ]; then
        printf "Previous command failed, killing the jobs so you can debug \n"
        mail -s 'Validate proposal script failed' rjones0211@hotmail.com <<< 'Failed in sample '$s', detector '$d', and parameter '$p''
        return
      fi

      printf "\n Finshed running validation of ${p} and ${s} in ${d} \n"
    done 
  done
done
