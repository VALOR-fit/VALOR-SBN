#!/bin/bash

#
# T2KANA oscillation analysis code setup script for Steve Dennis' laptop
#
# Input argument: oscillation analysis code top-level directory
# If no argument given, just use the directory containing the script
#

if [ -z ${VALOR_FWMK} ] ; then
  if [ $USER == steve ] ; then 
    source "/home/steve/steve/analysis/github/VALOR-SDK/setup/setup_at_steve_laptop.sh"
  fi
  if [ $USER == phrhbq ] ; then 
    source "/storage/epp2/phrhbq/analysis/fmwk/setup/setup_at_steve_laptop.sh"
  fi
  if [ $USER == jat98257 ] ; then
    source "/opt/ppd/t2k/users/steve/valor/fmwk/trunk//setup/setup_at_cvmfs.sh"
  fi
fi

export VALOR_DUNE=$1

if [ -z $VALOR_DUNE ]; then
  source="$( readlink -m "${BASH_SOURCE[0]}" )"
  export VALOR_DUNE="$( dirname "$( dirname "${source}" )" )/" # Directory above the one containing this file
fi

export LD_LIBRARY_PATH="${VALOR_DUNE}/lib:${LD_LIBRARY_PATH}"
export PATH="${VALOR_DUNE}/bin:${VALOR_DUNE}/prod:${PATH}"

