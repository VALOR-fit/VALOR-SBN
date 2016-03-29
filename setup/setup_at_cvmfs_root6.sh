#!/bin/sh

#
# VALOR_DUNE oscillation analysis code setup script for Steve Dennis' laptop
#
# Input arguments: experiment code, framework code
#
# Neither is necessary - if the framework has already been setup, it won't use that argument
# If experiment code isn't given, uses the folder containing the folder containing this setup file.
#

if [ -z "${VALOR_FMWK}" ] ; then
  if [ -z "${2}" ] ; then
    echo "VALOR framework must already be set up or specified in argument \$2 ($2)"
    return
  fi
  export VALOR_FMWK="$(readlink -m $2)" # Requires GNU readlink - should work on SL builds (but not Macs - try greadlink)
  
  . "${VALOR_FMWK}/setup/setup_at_cvmfs_root6.sh" "${VALOR_FMWK}"
fi

export VALOR_DUNE="$(readlink -m "$1")"

if [ -z "${VALOR_DUNE}" ]; then
  sdir="$( readlink -m "${BASH_SOURCE[0]}" )"
  export VALOR_DUNE="$( dirname "$( dirname "${sdir}" )" )/" # Directory above the one containing this file
fi

export LD_LIBRARY_PATH="${VALOR_DUNE}/lib:${LD_LIBRARY_PATH}"
export PATH="${VALOR_DUNE}/bin:${VALOR_DUNE}/prod:${PATH}"

