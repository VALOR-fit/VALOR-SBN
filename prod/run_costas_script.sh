
VAL1=-2.564
VAL2=5512

VAL1A=${VAL1}
VAL2A=${VAL2}

echo "VAL1A: $VAL1A"                                                                                                                                                                
echo "VAL2A: $VAL2A"   

#root -b -q /sbnd/app/users/tham/VALOR_master/VALOR-SBN/prod/bin_is_narrowly_excluded.cxx'("/sbnd/app/users/tham/VALOR_master/nue_2020/output_contours_as_graphs_geniev3_spline_fixed_matrix.root","contour_log_hist",23.66,'${VAL1A}','${VAL2A}',8)'

valorcommand="valor-run_fit --tag sbn_modern_nue_app-sinsq2thMuE-4.37547937507417e-05-dm41sq-0.0203091762090474 --first-octant  --run 20 --ntoymc 1
   --physics-hypothesis eff_sterile_osc     --param-values-option prefit-errors --fitter minuit+with_simplex_fallback     --config ../config/analysis/sbn_nue_2020a1.xml --mesg-thresholds verbosity.xml
   --without-stat-fluct     --store-spectra --normal --load-prior-from-file -     --pot-override -999 --osc-prior-file ../config/priors/void.xml  --input-sinsq2thMuE 0       --fix-at-sinsq2thMuE 4.37547937507417e-05 
   --fix-sinsq2thMuE  --input-dm41sq 0         --fix-at-dm41sq 0.0203091762090474         --fix-dm41sq  --input-sinsq2thMuMu 0           --fix-at-sinsq2thMuMu 0          
    --fix-sinsq2thMuMu  --input-sinsq2thEE 0           --fix-at-sinsq2thEE 0           --fix-sinsq2thEE"

# only bother to run VALOR if we're close to the contour - speeds things up                                                                                                           
#root -q bin_is_narrowly_excluded.cxx'("output_contours_as_graphs_geniev3_spline_fixed_matrix.root","contour_log_hist",23.66,'${VAL1A}','${VAL2A}',8)'  

if [ $? -ne 0 ]; then 
    echo "calculate bin"
#    eval $valorcommand
fi

chisqsurface="output_contours_as_graphs_geniev3_spline_fixed_matrix.root"

echo "here"
# only bother to run VALOR if we're close to the contour - speeds things up                                                                                                           
#root -q -b -n bin_is_narrowly_excluded.cxx++'("'${chisqsurface}'","contour_log_hist",23.66,'${VAL1A}','${VAL2A}',8)'
root -q -b -n bin_is_narrowly_excluded.cxx'("output_contours_as_graphs_geniev3_spline_fixed_matrix.root","contour_log_hist",23.66,-2.43589743589744,-0.0512820512820426,8)'

#eval $rootcommand
if [ $? -ne 0 ]; then                                                                                                                                                                 
    #Run Valor                                                                                                                                                                          
    echo "Running: $valorcommand";  
    eval $valorcommand 
fi

