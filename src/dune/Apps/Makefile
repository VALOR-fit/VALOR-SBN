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

# Add GENIE includes and libaries for apps that depend both on GENIE and VALOR
# GENIE needs to be enabled to compile those apps
#

#ifeq(, $(shell which genie-config))
ifdef GENIE
 GLIBRARIES = $(shell genie-config --libs)
 GINCLUDES  = $(shell genie-config --topsrcdir)
 GINCLUDES  := -I$(GINCLUDES) $(INCLUDES)
 GLIBRARIES := $(LIBRARIES) $(GLIBRARIES) $(LIBRARIES)
endif

TGT = make_nd_minidst \
      run_fit \
      fitnt_conv

all: $(TGT)

# Generate DSTs for ND fit
#
make_nd_minidst: FORCE
ifdef GENIE
	$(CXX) $(CXXFLAGS) -c make_nd_minidst.cxx $(GINCLUDES)
	$(LD) $(LDFLAGS) make_nd_minidst.o $(GLIBRARIES) -o $(VALOR_DUNE)/bin/valor_dune-make_nd_minidst
endif
	

# Generate GENIE response functions
#
make_response_functions: FORCE
ifdef GENIE
	$(CXX) $(CXXFLAGS) -c make_response_functions.cxx $(GINCLUDES)
	$(LD) $(LDFLAGS) make_response_functions.o $(GLIBRARIES) -o $(VALOR_DUNE)/bin/valor_dune-make_response_functions
endif
	
# Run a generic fit
#
run_fit: FORCE
	$(CXX) $(CXXFLAGS) -c run_fit.cxx $(INCLUDES)
	$(LD) $(LDFLAGS) run_fit.o $(LIBRARIES) -o $(VALOR_DUNE)/bin/valor_dune-run_fit
	
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
	$(RM) $(VALOR_DUNE)/bin/valor_dune-make_nd_minidst
	$(RM) $(VALOR_DUNE)/bin/valor_dune-make_response_functions
	$(RM) $(VALOR_DUNE)/bin/valor_dune-run_fit
	$(RM) $(VALOR_DUNE)/bin/valor_dune-fitnt_conv

distclean: FORCE
	$(RM) $(VALOR_DUNE_INSTALLATION_PATH)/bin/valor_dune-make_nd_minidst
	$(RM) $(VALOR_DUNE_INSTALLATION_PATH)/bin/valor_dune-make_response_functions
	$(RM) $(VALOR_DUNE_INSTALLATION_PATH)/bin/valor_dune-run_fit
	$(RM) $(VALOR_DUNE_INSTALLATION_PATH)/bin/valor_dune-fitnt_conv

FORCE:

# DO NOT DELETE
