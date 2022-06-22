#!/bin/bash

starttime=$(date)

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic DISAth \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic DISBth \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic DISCv1u \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic DISCv2u \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic IntraNukeNabs \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic IntraNukeNcex \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic IntraNukeNinel \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic IntraNukeNmfp \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic IntraNukeNpi \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic IntraNukePIabs \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic IntraNukePIcex \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic IntraNukePIinel \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic IntraNukePImfp \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic IntraNukePIpi \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic ResDecayGamma \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic ccresVector \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic cohMA \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic cohR0 \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic ncelAxial \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic ncelEta \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

valor_sbn-make_splines \
  --config analysis/sbn_numu_disapp_2020a1_1_universes_ub.xml \
  --systematic ncresVector \
  --variations /sbnd/app/users/rsjones/VALOR/VALOR-SBN/data/sbn_numu_disappearance/universes/2020a1/all_uboone_combined_params_2020a.txt \
  --store-spectra --save-modelist \
  --detector sbn_uboone

endtime=$(date)

echo "Started running splines at ${starttime} finished at ${endtime} \n"
