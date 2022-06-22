#!/bin/bash

short_params=("DISAth" "DISBth" "DISCv1u" "DISCv2u" "IntraNukeNabs" "IntraNukeNcex" "IntraNukeNinel" "IntraNukeNmfp" "IntraNukeNpi" "IntraNukePIabs" "IntraNukePIcex" "IntraNukePIinel" "IntraNukePImfp" "IntraNukePIpi" "ResDecayGamma" "ccresVector" "cohMA" "cohR0" "ncelAxial" "ncelEta" "ncresVector")

params=("genie_DISAth_Genie" "genie_DISBth_Genie" "genie_DISCv1u_Genie" "genie_DISCv2u_Genie" "genie_IntraNukeNabs_Genie" "genie_IntraNukeNcex_Genie" "genie_IntraNukeNinel_Genie" "genie_IntraNukeNmfp_Genie" "genie_IntraNukeNpi_Genie" "genie_IntraNukePIabs_Genie" "genie_IntraNukePIcex_Genie" "genie_IntraNukePIinel_Genie" "genie_IntraNukePImfp_Genie" "genie_IntraNukePIpi_Genie" "genie_ResDecayGamma_Genie" "genie_ccresVector_Genie" "genie_cohMA_Genie" "genie_cohR0_Genie" "genie_ncelAxial_Genie" "genie_ncelEta_Genie" "genie_ncresVector_Genie")

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

      if [ ! -d "/sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/modern_xsec/validation/${dir}/${loc}" ]
      then
        mkdir /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/modern_xsec/validation/${dir}/${loc}
      fi

      cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/modern_xsec/validation/${dir}/

      valor -l -b -q $VALOR_SBN/macros/systematic_construction/spline_validation.C'("'${p}'","'${s}'","BNB_FHC","'${d}'","","/sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/responses/03c1/'${dir}'/",true,1,false,"nsigma_var","/sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/03c1/modern_xsec/validation/'${dir}'/'${loc}'/")'

      if [ $? -ne 0 ]; then
        printf "Previous command failed, killing the jobs so you can debug \n"
        mail -s 'Validate modern script failed' rjones0211@hotmail.com <<< 'Failed in sample '$s', detector '$d', and parameter '$p''
        return
      fi

      printf "\n Finshed running validation of ${p} and ${s} in ${d} \n"
    done 
  done
done
