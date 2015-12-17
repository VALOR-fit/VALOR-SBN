#
# Makefile for VALOR/DUNE apps
#
# Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
# Sep 10, 2015
#

SHELL = /bin/sh
NAME = all
MAKEFILE = Makefile

# Include machine specific flags and locations (inc. files & libs)
#
include $(VALOR_DUNE)/make/Make.include

TGT = valor_dune-run_nd_fit

all: $(TGT)

# 
#
valor_dune-run_nd_fit: FORCE
	$(CXX) $(CXXFLAGS) -c run_nd_fit.cxx $(INCLUDES)
	$(LD) $(LDFLAGS) run_nd_fit.o $(LIBRARIES) -o $(VALOR_DUNE)/bin/valor_dune-run_nd_fit

#################### CLEANING

purge: FORCE
	$(RM) *.o *~ core 

clean: FORCE
	$(RM) *.o *~ core
	$(RM) $(VALOR_DUNE)/bin/valor_dune-run_nd_fit

distclean: FORCE
	$(RM) $(VALOR_DUNE_INSTALLATION_PATH)/bin/valor_dune-run_nd_fit		

FORCE:

# DO NOT DELETE
