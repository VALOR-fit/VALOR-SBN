#!/bin/bash

params=("horncurrent_FluxUnisim" "expskin_FluxUnisim" "pionqexsec_FluxUnisim" "nucleontotxsec_FluxUnisim" "genie_NonResRvpNC2pi_Genie" "genie_IntraNukeNmfp_Genie" "genie_ccresAxial_Genie" "genie_qema_Genie" "genie_ccresVector_Genie")
short_params=("horncurrent" "expskin" "pionqexsec" "nucleontotxsec" "NonResRvpNC2pi" "IntraNukeNmfp" "ccresaxial" "qema" "ccresvector")

cd /sbnd/app/users/rsjones/VALOR/VALOR-SBN/systematics/splines/plots/Feb2021

for i in ${!params[@]}; do
  p=${params[$i]}
  s=${short_params[$i]}

  spline_file="$VALOR_DATA/sbn_numu_disappearance/responses/03c1/sbnd/valor_splines_numuCCincl_${p}_BNB_FHC_sbn_nd.root"
  output_file="${s}_03c1_splines"
  valor -l -b -q $VALOR_SBN/macros/contrib/rhiannon/draw_splines.C'("'${spline_file}'","'${p}'","'${output_file}'")'
done

