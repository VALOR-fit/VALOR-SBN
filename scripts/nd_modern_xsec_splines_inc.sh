#!/bin/bash

starttime=$(date)

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic DISAth \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic DISBth \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic DISCv1u \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic DISCv2u \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic IntraNukeNabs \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic IntraNukeNcex \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic IntraNukeNinel \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic IntraNukeNmfp \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic IntraNukeNpi \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic IntraNukePIabs \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic IntraNukePIcex \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic IntraNukePIinel \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic IntraNukePImfp \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic IntraNukePIpi \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic ResDecayGamma \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic ccresVector \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic cohMA \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic cohR0 \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic ncelAxial \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic ncelEta \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_nd.xml \
  --systematic ncresVector \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_nd

endtime=$(date)

echo "Started running splines at ${starttime} finished at ${endtime} \n"
