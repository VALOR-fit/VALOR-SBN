#
# Author: Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
#

SHELL    = /bin/sh
NAME     = all
MAKEFILE = Makefile

# Include machine specific flags and locations (inc. files & libs)
#
include $(VALOR_EXPT)/make/Make.include

PACKAGE           = ValorDuneConv
DICTIONARY        = _RootDict_$(PACKAGE)
LIBNAME           = lib$(PACKAGE)

all : rootcint lib lib-link

# Include standard package makefile targets
#
include $(VALOR_EXPT)/make/Make.template

FORCE:

