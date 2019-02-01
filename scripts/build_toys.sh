maxbin=100
for ((i=0; i<=maxbin; i++)); do
   echo $i
   step=$(echo "2 * 3.141592654 / ${maxbin}" | bc -l)
   cpv=$(bc <<< "-3.141592654+${i}*${step}")
   valor_dune-run_build_margtoys \
      --config $VALOR_DUNE/config/test/marginalisation/analysis.xml \
      --seed-toys-syst 1 \
      --seed-toys-osc 1 \
      --seed-other 1 \
      --nmargtoy 50 \
      --batch 0 \
      --fit-param1 cpv \
      --fit-param-value1 $cpv \
      --fit-param-bin1 $i
done
