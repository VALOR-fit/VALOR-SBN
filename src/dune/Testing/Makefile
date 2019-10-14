#
# Author: Andy Chappell <A.Chappell \at warwick.ac.uk>
#

SHELL    = /bin/sh
NAME     = all
MAKEFILE = Makefile

# Include machine specific flags and locations (inc. files & libs)
#
include $(VALOR_EXPT)/make/Make.include

PACKAGE           = ValorDuneTesting
DICTIONARY        = _RootDict_$(PACKAGE)
LIBNAME           = lib$(PACKAGE)

# We need the GENIE includes added for this folder
INCLUDES := $(GENIE_INCLUDES) $(INCLUDES)

all : rootcint lib lib-link

# Include standard package makefile targets
#
include $(VALOR_EXPT)/make/Make.template

FORCE:

