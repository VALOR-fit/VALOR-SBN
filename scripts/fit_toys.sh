for i in {0..8}; do
   step=$(echo "3.141592654 / 4.0" | bc -l)
   cpv=$(bc <<< "-3.141592654+${i}*${step}")
   valor_dune-run_fit_marg \
      --config $VALOR_DUNE/config/test/marginalisation/analysis.xml \
      --seed-toys-syst 1 \
      --seed-toys-osc 1 \
      --seed-other 1 \
      --nmargtoy 100 \
      --nbatches 1 \
      --fit-param1 cpv \
      --fit-param-value1 $cpv \
      --fit-param-bin1 $i
done

