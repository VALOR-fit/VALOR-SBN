#
# Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
#

SHELL = /bin/sh
NAME = all
MAKEFILE = Makefile

# Include machine specific flags and locations (inc. files & libs)
#
include $(GENIE)/src/make/Make.include

GENIE_LIBS  = $(shell $(GENIE)/src/scripts/setup/genie-config --libs)

LIBRARIES  := $(GENIE_LIBS) $(LIBRARIES) 

TGT = valor_dune-make_minidst

all: $(TGT)

# 
#
valor_dune-make_minidst: FORCE
	@echo "** Building valor_dune-make_minidst"
ifeq ($(strip $(GOPT_ENABLE_GENIE)),YES)
	$(CXX) $(CXXFLAGS) -c make_minidst.cxx $(INCLUDES)
	$(LD) $(LDFLAGS) make_minidst.o $(LIBRARIES) -o $(VALOR_DUNE)/bin/valor_dune-make_minidst
else
	@echo "valor_dune-make_minidst requires GENIE"
endif

#
# clean-up
#

purge: FORCE
	$(RM) *.o *~ core 

clean: FORCE
	$(RM) *.o *~ core
	$(RM) $(VALOR_DUNE)/bin/valor_dune-make_minidst

distclean: FORCE
	$(RM) $(VALOR_DUNE_INSTALLATION_PATH)/bin/valor_dune-make_minidst

FORCE:

# DO NOT DELETE
