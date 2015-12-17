#
# Makefile for VALOR/DUNE apps
#
# Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
#

SHELL = /bin/sh
NAME = all
MAKEFILE = Makefile

# Include machine specific flags and locations (inc. files & libs)
#
include $(VALOR_DUNE)/make/Make.include

TGT = run_nd_fit \
      fitnt_conv

all: $(TGT)

# Run ND fit
#
run_nd_fit: FORCE
	$(CXX) $(CXXFLAGS) -c run_nd_fit.cxx $(INCLUDES)
	$(LD) $(LDFLAGS) run_nd_fit.o $(LIBRARIES) -o $(VALOR_DUNE)/bin/valor_dune-run_nd_fit

# Pick info from the VALOR fit n-tuple and convert to bare ROOT format
#
fitnt_conv: FORCE
	$(CXX) $(CXXFLAGS) -c fitnt_conv.cxx $(INCLUDES)
	$(LD) $(LDFLAGS) fitnt_conv.o $(LIBRARIES) -o $(VALOR_DUNE)/bin/valor_dune-fitnt_conv

#################### CLEANING

purge: FORCE
	$(RM) *.o *~ core 

clean: FORCE
	$(RM) *.o *~ core
	$(RM) $(VALOR_DUNE)/bin/valor_dune-run_nd_fit
	$(RM) $(VALOR_DUNE)/bin/valor_dune-fitnt_conv

distclean: FORCE
	$(RM) $(VALOR_DUNE_INSTALLATION_PATH)/bin/valor_dune-run_nd_fit		
	$(RM) $(VALOR_DUNE_INSTALLATION_PATH)/bin/valor_dune-fitnt_conv

FORCE:

# DO NOT DELETE
