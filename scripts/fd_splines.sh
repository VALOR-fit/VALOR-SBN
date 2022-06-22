#!/bin/bash

cd $VALOR_SBN/systematics/splines/03c1/flux/icarus

source $VALOR_SBN/scripts/fd_flux_splines_inc.sh
source $VALOR_SBN/scripts/fd_flux_splines_0pi.sh
source $VALOR_SBN/scripts/fd_flux_splines_oth.sh

cd $VALOR_SBN/systematics/splines/03c1/proposal_xsec/icarus

source $VALOR_SBN/scripts/fd_proposal_xsec_splines_inc.sh
source $VALOR_SBN/scripts/fd_proposal_xsec_splines_0pi.sh
source $VALOR_SBN/scripts/fd_proposal_xsec_splines_oth.sh

cd $VALOR_SBN/systematics/splines/03c1/modern_xsec/icarus

source $VALOR_SBN/scripts/fd_modern_xsec_splines_inc.sh
source $VALOR_SBN/scripts/fd_modern_xsec_splines_0pi.sh
source $VALOR_SBN/scripts/fd_modern_xsec_splines_oth.sh

cd -
