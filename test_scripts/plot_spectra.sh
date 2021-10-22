config_file=${VALOR_EXPT}/config/analysis/sbn_numu_disapp_2020a1_1.xml   # numu config
#config_file=${VALOR_EXPT}/config/analysis/sbn_nue_2020a1.xml              # nue config

input_file=mytest_spectra.root  #output file from generate_spectra

#overlay_file=mytest_spectra_overlay.root

tag="mytest"

valor $VALOR_EXPT/macros/contrib/tom/plot_pdf_tom.C'("'${config_file}'","'${input_file}'","valor",1,"","","","Ereco","valor_pdfts","","'${tag}'","pdf")'
#valor $VALOR_EXPT/macros/contrib/tom/plot_pdf_tom.C'("'${config_file}'","'${input_file}'","valor",1,"","'${overlay_file}'","","Ereco","valor_pdfts","","'${tag}'","pdf")'
