#
# Makefile for VALOR/LBNX apps
#
# Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
# Sep 10, 2015
#

SHELL = /bin/sh
NAME = all
MAKEFILE = Makefile

# Include machine specific flags and locations (inc. files & libs)
#
include $(VALOR_LBNX)/make/Make.include

TGT = valor_lbnx-run_nd_fit

all: $(TGT)

# 
#
valor_lbnx-run_nd_fit: FORCE
	$(CXX) $(CXXFLAGS) -c run_fit_exe.C $(INCLUDES)
	$(LD) $(LDFLAGS) run_fit_exe.o $(LIBRARIES) -o $(VALOR_LBNX)/bin/valor_lbnx-run_nd_fit

#################### CLEANING

purge: FORCE
	$(RM) *.o *~ core 

clean: FORCE
	$(RM) *.o *~ core
	$(RM) $(VALOR_LBNX)/bin/valor_lbnx-run_nd_fit

distclean: FORCE
	$(RM) $(VALOR_LBNX_INSTALLATION_PATH)/bin/valor_lbnx-run_nd_fit		

FORCE:

# DO NOT DELETE
