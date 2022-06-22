#!/bin/bash

starttime=$(date)

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic horncurrent \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic expskin \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic nucleoninexsec \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic nucleontotxsec \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic nucleonqexsec \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic pioninexsec \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic piontotxsec \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic pionqexsec \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

endtime=$(date)

echo "Started running splines at ${starttime} finished at ${endtime} \n"
