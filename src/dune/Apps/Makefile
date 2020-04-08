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
include $(VALOR_EXPT)/make/Make.include

DUNE_LIBRARIES = 

TGT = make_nd_minidst \
      make_fd_minidst \
      make_sbncode_minidst \
      make_fastmc_minidst \
      make_caf_minidst \
      make_nd_caf_minidst \
      make_response_functions \
      make_sbn_interaction_splines \
      make_table_systematic_effects \
      run_fit \
      write_pdf \
      tweak_pdf_N \
      tweak_pdf_sigma_var \
      fitnt_conv \
      adaptive_mcmc \
      run_tests \
      run_build_toys \
      run_fit_marg \
      make_dummy_samples \
      batch_tests \
      write_sbn_spectra_using_universes

all: $(TGT)

# Generate DSTs for ND fit
#
make_nd_minidst: FORCE
ifdef GENIE
	$(CXX) $(CXXFLAGS) -c make_nd_minidst.cxx $(GINCLUDES)
	$(LD) $(LDFLAGS) make_nd_minidst.o $(GLIBRARIES)  $(VALOR_GLIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-make_nd_minidst
else
	@echo "Skipping make_nd_minidst due to no GENIE"
endif

# Generate DSTs for FD fit
#
make_fd_minidst: FORCE
ifdef GENIE
	$(CXX) $(CXXFLAGS) -c make_fd_minidst.cxx $(GINCLUDES)
	$(LD) $(LDFLAGS) make_fd_minidst.o $(GLIBRARIES)  $(VALOR_GLIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-make_fd_minidst
else
	@echo "Skipping make_fd_minidst due to no GENIE"
endif

# Generate DSTs for fast MC FD fit
#
make_fastmc_minidst: FORCE
	$(CXX) $(CXXFLAGS) -c make_fastmc_minidst.cxx $(INCLUDES)
	$(LD) $(LDFLAGS) make_fastmc_minidst.o $(LIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-make_fastmc_minidst

# Generate DSTs for SBNCode fit
#
make_sbncode_minidst: FORCE
ifeq ($(SBNANALYSIS_ENABLED),1)
ifdef GENIE
	$(CXX) $(CXXFLAGS) -c make_sbncode_minidst.cxx $(GINCLUDES) $(SBNANALYSIS_INC) $(LARSOFT_INCLUDES)
	$(LD) $(LDFLAGS) make_sbncode_minidst.o $(GLIBRARIES) $(VALOR_GLIBRARIES) $(SBNANALYSIS_LIB) -o $(VALOR_EXPT)/bin/valor_dune-make_sbncode_minidst
else
	@echo "Skipping make_sbncode_minidst due to no GENIE"
endif
else
	@echo "Skipping make_sbncode_minidst due to no SBNanalysis"
endif

# Generate DSTs for RecoSelection fit
#
make_recoselection_minidst: FORCE
ifeq ($(SBNANALYSIS_ENABLED),1)
ifdef GENIE
	$(CXX) $(CXXFLAGS) -c make_recoselection_minidst.cxx $(GINCLUDES) $(SBNANALYSIS_INC) $(LARSOFT_INCLUDES)
	$(LD) $(LDFLAGS) make_recoselection_minidst.o $(GLIBRARIES)  $(VALOR_GLIBRARIES) $(SBNANALYSIS_LIB)  -o $(VALOR_EXPT)/bin/valor_dune-make_recoselection_minidst
else
	@echo "Skipping make_recoselection_minidst due to no GENIE"
endif
else
	@echo "Skipping make_recoselection_minidst due to no SBNanalysis"
endif

# Generate GENIE response functions
#
make_response_functions: FORCE
ifdef GENIE
	$(CXX) $(CXXFLAGS) -c make_response_functions.cxx $(GINCLUDES)
	$(LD) $(LDFLAGS) make_response_functions.o $(GLIBRARIES) $(VALOR_GLIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-make_response_functions
else
	@echo "Skipping make_response_functions due to no GENIE"
endif

# Generate SBN interaction splines
# Probably don't require the GENIE dependence but method isn't finalised yet so keeping just in case
#
make_sbn_interaction_splines: FORCE
ifdef GENIE
	$(CXX) $(CXXFLAGS) -c make_sbn_interaction_splines.cxx $(GINCLUDES)
	$(LD) $(LDFLAGS) make_sbn_interaction_splines.o $(GLIBRARIES) $(VALOR_GLIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-make_sbn_interaction_splines
else
	@echo "Skipping make_sbn_interaction_splines due to no GENIE"
endif

# Throw a user-specified parameter set N times and output a table containing the mean, RMS and RMS/mean for all samples
#
make_table_systematic_effects: FORCE
	$(CXX) $(CXXFLAGS) -c make_table_systematic_effects.cxx $(INCLUDES)
	$(LD) $(LDFLAGS) make_table_systematic_effects.o $(LIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-make_table_systematic_effects

# Generate CAFs based DSTs
#
make_caf_minidst: FORCE
ifdef GENIE
	$(CXX) $(CXXFLAGS) -c make_caf_minidst.cxx $(GINCLUDES)
	$(LD) $(LDFLAGS) make_caf_minidst.o $(GLIBRARIES) $(VALOR_GLIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-make_caf_minidst
else
	@echo "Skipping make_caf_minidst due to no GENIE"
endif

make_nd_caf_minidst: FORCE
ifdef GENIE
	$(CXX) $(CXXFLAGS) -c make_nd_caf_minidst.cxx $(GINCLUDES)
	$(LD) $(LDFLAGS) make_nd_caf_minidst.o $(GLIBRARIES) $(VALOR_GLIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-make_nd_caf_minidst
else
	@echo "Skipping make_nd_caf_minidst due to no GENIE"
endif

# Run a generic fit
#
run_fit: FORCE
	$(CXX) $(CXXFLAGS) -c run_fit.cxx $(INCLUDES)
	$(LD) $(LDFLAGS) run_fit.o $(LIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-run_fit

# Write out pdf
# 
write_pdf: FORCE
	$(CXX) $(CXXFLAGS) -c write_pdf.cxx $(INCLUDES)
	$(LD) $(LDFLAGS) write_pdf.o $(LIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-write_pdf
	
# Randomly throw the pdf t o make envelopes
# 
tweak_pdf_N: FORCE
	$(CXX) $(CXXFLAGS) -c tweak_pdf_N.cxx $(INCLUDES)
	$(LD) $(LDFLAGS) tweak_pdf_N.o $(LIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-tweak_pdf_N

# Make +/- 1 and 3 sigma variations for each param
#
tweak_pdf_sigma_var: FORCE
	$(CXX) $(CXXFLAGS) -c tweak_pdf_sigma_var.cxx $(INCLUDES)
	$(LD) $(LDFLAGS) tweak_pdf_sigma_var.o $(LIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-tweak_pdf_sigma_var

# Run an Adaptive Metropolis Hastings around the results of a fit
#
adaptive_mcmc: FORCE
	$(CXX) $(CXXFLAGS) -c adaptive_mcmc.cxx $(INCLUDES)
	$(LD) $(LDFLAGS) adaptive_mcmc.o $(LIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-adaptive_mcmc

# Pick info from the VALOR fit n-tuple and convert to bare ROOT format
#
fitnt_conv: FORCE
	$(CXX) $(CXXFLAGS) -c fitnt_conv.cxx $(INCLUDES)
	$(LD) $(LDFLAGS) fitnt_conv.o $(LIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-fitnt_conv

run_build_toys: FORCE
	$(CXX) $(CXXFLAGS) -c run_build_toys.cxx $(INCLUDES)
	$(LD) $(LDFLAGS) run_build_toys.o $(LIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-run_build_toys

run_fit_marg: FORCE
	$(CXX) $(CXXFLAGS) -c run_fit_marg.cxx $(INCLUDES)
	$(LD) $(LDFLAGS) run_fit_marg.o $(LIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-run_fit_marg

make_dummy_samples: FORCE
	$(CXX) $(CXXFLAGS) -c make_dummy_samples.cxx $(INCLUDES)
	$(LD) $(LDFLAGS) make_dummy_samples.o $(LIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-make_dummy_samples

write_sbn_spectra_using_universes: FORCE
	$(CXX) $(CXXFLAGS) -c write_sbn_spectra_using_universes.cxx $(INCLUDES)
	$(LD) $(LDFLAGS) write_sbn_spectra_using_universes.o $(LIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-write_sbn_spectra_using_universes

run_tests: FORCE
ifdef GENIE
	$(CXX) $(CXXFLAGS) -c run_tests.cxx $(GINCLUDES)
	$(LD) $(LDFLAGS) run_tests.o $(GLIBRARIES)  $(VALOR_GLIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-run_tests
else
	@echo "Skipping run_tests due to no GENIE"
endif

batch_tests: FORCE
ifdef GENIE
	$(CXX) $(CXXFLAGS) -c batch_tests.cxx $(GINCLUDES)
	$(LD) $(LDFLAGS) batch_tests.o $(GLIBRARIES)  $(VALOR_GLIBRARIES) -o $(VALOR_EXPT)/bin/valor_dune-batch_tests
else
	@echo "Skipping run_tests due to no GENIE"
endif

#################### CLEANING

purge: FORCE
	$(RM) *.o *~ core 

clean: FORCE
	$(RM) *.o *~ core
	$(RM) $(VALOR_EXPT)/bin/valor_dune-make_nd_minidst
	$(RM) $(VALOR_EXPT)/bin/valor_dune-make_fd_minidst
	$(RM) $(VALOR_EXPT)/bin/valor_dune-make_sbncode_minidst
	$(RM) $(VALOR_EXPT)/bin/valor_dune-make_recoselection_minidst
	$(RM) $(VALOR_EXPT)/bin/valor_dune-make_fastmc_minidst
	$(RM) $(VALOR_EXPT)/bin/valor_dune-make_response_functions
	$(RM) $(VALOR_EXPT)/bin/valor_dune-make_sbn_interaction_splines
	$(RM) $(VALOR_EXPT)/bin/valor_dune-make_table_systematic_effects
	$(RM) $(VALOR_EXPT)/bin/valor_dune-run_fit
	$(RM) $(VALOR_EXPT)/bin/valor_dune-write_pdf
	$(RM) $(VALOR_EXPT)/bin/valor_dune-tweak_pdf_N
	$(RM) $(VALOR_EXPT)/bin/valor_dune-tweak_pdf_sigma_var
	$(RM) $(VALOR_EXPT)/bin/valor_dune-fitnt_conv
	$(RM) $(VALOR_EXPT)/bin/valor_dune-adaptive_mcmc
	$(RM) $(VALOR_EXPT)/bin/valor_dune-run_tests
	$(RM) $(VALOR_EXPT)/bin/valor_dune-run_build_toys
	$(RM) $(VALOR_EXPT)/bin/valor_dune-run_fit_marg
	$(RM) $(VALOR_EXPT)/bin/valor_dune-make_dummy_samples
	$(RM) $(VALOR_EXPT)/bin/valor_dune-batch_tests
	$(RM) $(VALOR_EXPT)/bin/valor_dune-write_sbn_spectra_using_universes

distclean: FORCE
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_dune-make_nd_minidst
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_dune-make_fd_minidst
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_dune-make_sbncode_minidst
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_dune-make_recoselection_minidst
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_dune-make_fastmc_minidst
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_dune-make_response_functions
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_dune-make_sbn_interaction_splines
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_dune-make_table_systematic_effects
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_dune-run_fit
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/write_pdf
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/tweak_pdf_N
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/tweak_pdf_sigma_var
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_dune-fitnt_conv
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_dune-adaptive_mcmc
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_dune-run_tests
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_dune-run_build_toys
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_dune-run_fit_marg
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_dune-make_dummy_samples
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_dune-batch_tests
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_dune-write_sbn_spectra_using_universes

FORCE:
	
# DO NOT DELETE
