#!/usr/bin/bash

# get the total POT
totPOT=$(root -b -l -q "read_pot_wgt_wrapper.C++(\"${1}\")" | grep -v 'int' | grep 'total POT' | awk -F "= " '{print $2}')
echo "I found ${totPOT} POT total"
totPOT=$(printf "%.0f" ${totPOT})

invTotPOT=$(awk "BEGIN {print 1.0 / $totPOT}")
echo "The total number of inverted POT is ${invTotPOT}"

# now do hadd.
root -b -l -q "hadd_dsts.C+(\"$1\", \"$2\", $invTotPOT)"
