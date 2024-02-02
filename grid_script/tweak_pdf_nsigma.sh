#params=("horncurrent_FluxUnisim" "expskin_FluxUnisim" "nucleoninexsec_FluxUnisim" "nucleontotxsec_FluxUnisim" "nucleonqexsec_FluxUnisim" \
#        "pioninexsec_FluxUnisim" "piontotxsec_FluxUnisim" "pionqexsec_FluxUnisim") 

#params=("genie_ccresAxial_Genie" "genie_ncresAxial_Genie" "genie_qema_Genie" "genie_NC_Genie" \
#        "genie_NonResRvpCC1pi_Genie" "genie_NonResRvnCC1pi_Genie" "genie_NonResRvbarnCC1pi_Genie" "genie_NonResRvbarpCC1pi_Genie" \
#        "genie_NonResRvpCC2pi_Genie" "genie_NonResRvnCC2pi_Genie" "genie_NonResRvbarnCC2pi_Genie" "genie_NonResRvbarpCC2pi_Genie" \
#        "genie_NonResRvpNC1pi_Genie" "genie_NonResRvnNC1pi_Genie" "genie_NonResRvbarnNC1pi_Genie" "genie_NonResRvbarpNC1pi_Genie" \
#        "genie_NonResRvpNC2pi_Genie" "genie_NonResRvnNC2pi_Genie" "genie_NonResRvbarnNC2pi_Genie" "genie_NonResRvbarpNC2pi_Genie") 

#params=("genie_DISAth_Genie" "genie_DISBth_Genie" "genie_DISCv1u_Genie" "genie_DISCv2u_Genie" \
#        "genie_IntraNukeNabs_Genie" "genie_IntraNukeNcex_Genie" "genie_IntraNukeNinel_Genie" \
#        "genie_IntraNukeNmfp_Genie" "genie_IntraNukeNpi_Genie" "genie_IntraNukePIabs_Genie" \
#        "genie_IntraNukePIcex_Genie" "genie_IntraNukePIinel_Genie" "genie_IntraNukePImfp_Genie" "genie_IntraNukePIpi_Genie" \
#        "genie_ResDecayGamma_Genie" "genie_ccresVector_Genie" "genie_cohMA_Genie" "genie_cohR0_Genie" \
#        "genie_ncelAxial_Genie" "genie_ncelEta_Genie" "genie_ncresVector_Genie")               

#params=("horncurrent_FluxUnisim")
params=("pionqexsec_FluxUnisim")

#location=TEMP/xsec/numu/nd
location=03d1/sbnd

for param in ${params[@]}; do  
valor_sbn-tweak_pdf_nsigma_var \
    --config analysis/sbn_numu_disapp_2020a1_03d1_nd_1.xml \
    --params ${param} \
    --physics-hypothesis eff_sterile_osc \
    --universe-spectra $VALOR_EXPT/data/sbn_numu_inclusive/responses/${location}/valor_splines_numuCCincl_${param}_BNB_FHC_sbn_nd_spectra.root \
    --output nsigma_var_${param}_numuCCincl_all_sigma.root 

                                                                                                                                                                                  
if [ $? -ne 0 ]; then                                                                                                                                                           
    #curl -s -X POST -H 'Content-type: application/json' --data '{"text":"Error in spline validation :("}' https://hooks.slack.com/services/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 > /dev/null
    # Pause script when it errors                                                                                                                                               
    echo ""
    read -p "Script paused because something errored. Press enter to continue.."
fi

valor -l -q $VALOR_EXPT/macros/systematic_construction/spline_validation.C'("'${param}'","numuCCincl","BNB_FHC","sbn_nd","","/sbnd/app/users/tham/VALOR_master/VALOR-SBN/data/sbn_numu_inclusive/responses/'${location}'/",true,1,false,"nsigma_var","","'${param}'.root")'

done
