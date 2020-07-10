#
# Makefile for VALOR/SBN apps
#
# Costas Andreopoulos <constantinos.andreopoulos \at cern.ch>
#

SHELL = /bin/sh
NAME = all
MAKEFILE = Makefile

# Include machine specific flags and locations (inc. files & libs)
#
include $(VALOR_EXPT)/make/Make.include

SBN_LIBRARIES =

TGT = make_sbncode_minidst \
      make_interaction_splines \
      make_flux_splines \
      universe_variation_tweaks \
      write_spectra_using_universes

all: $(TGT)

# Generate DSTs for SBNCode fit
#
make_sbncode_minidst: FORCE
ifeq ($(SBNANALYSIS_ENABLED),1)
ifdef GENIE
	$(CXX) $(CXXFLAGS) -c make_sbncode_minidst.cxx $(GINCLUDES) $(SBNANALYSIS_INC) $(LARSOFT_INCLUDES)
	$(LD) $(LDFLAGS) make_sbncode_minidst.o $(GLIBRARIES) $(VALOR_GLIBRARIES) $(SBNANALYSIS_LIB) -o $(VALOR_EXPT)/bin/valor_sbn-make_sbncode_minidst
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
	$(LD) $(LDFLAGS) make_recoselection_minidst.o $(GLIBRARIES)  $(VALOR_GLIBRARIES) $(SBNANALYSIS_LIB)  -o $(VALOR_EXPT)/bin/valor_sbn-make_recoselection_minidst
else
	@echo "Skipping make_recoselection_minidst due to no GENIE"
endif
else
	@echo "Skipping make_recoselection_minidst due to no SBNanalysis"
endif

# Generate SBN flux splines
# Probably don't require the GENIE dependence but method isn't finalised yet so keeping just in case
#
make_flux_splines: FORCE
ifdef GENIE
	$(CXX) $(CXXFLAGS) -c make_flux_splines.cxx $(GINCLUDES)
	$(LD) $(LDFLAGS) make_flux_splines.o $(GLIBRARIES) $(VALOR_GLIBRARIES) -o $(VALOR_EXPT)/bin/valor_sbn-make_flux_splines
else
	@echo "Skipping make_flux_splines due to no GENIE"
endif

# Generate SBN interaction splines
# Probably don't require the GENIE dependence but method isn't finalised yet so keeping just in case
#
make_interaction_splines: FORCE
ifdef GENIE
	$(CXX) $(CXXFLAGS) -c make_interaction_splines.cxx $(GINCLUDES)
	$(LD) $(LDFLAGS) make_interaction_splines.o $(GLIBRARIES) $(VALOR_GLIBRARIES) -o $(VALOR_EXPT)/bin/valor_sbn-make_interaction_splines
else
	@echo "Skipping make_interaction_splines due to no GENIE"
endif

# Tweaks taken directly from universe variations to validate VALOR systematic parameterisation
#
universe_variation_tweaks: FORCE
ifdef GENIE
	$(CXX) $(CXXFLAGS) -c universe_variation_tweaks.cxx $(GINCLUDES)
	$(LD) $(LDFLAGS) universe_variation_tweaks.o $(GLIBRARIES) $(VALOR_GLIBRARIES) -o $(VALOR_EXPT)/bin/valor_sbn-universe_variation_tweaks
else
	@echo "Skipping universe_variation_tweaks due to no GENIE"
endif

write_spectra_using_universes: FORCE
ifdef GENIE
	$(CXX) $(CXXFLAGS) -c write_spectra_using_universes.cxx $(GINCLUDES)
	$(LD) $(LDFLAGS) write_spectra_using_universes.o $(GLIBRARIES) $(VALOR_GLIBRARIES) -o $(VALOR_EXPT)/bin/valor_sbn-write_spectra_using_universes
else
	@echo "Skipping write_spectra_using_universes due to no GENIE"
endif


#################### CLEANING

purge: FORCE
	$(RM) *.o *~ core

clean: FORCE
	$(RM) *.o *~ core
	$(RM) $(VALOR_EXPT)/bin/valor_sbn-make_sbncode_minidst
	$(RM) $(VALOR_EXPT)/bin/valor_sbn-make_recoselection_minidst
	$(RM) $(VALOR_EXPT)/bin/valor_sbn-make_interaction_splines
	$(RM) $(VALOR_EXPT)/bin/valor_sbn-make_flux_splines
	$(RM) $(VALOR_EXPT)/bin/valor_sbn-universe_variation_tweaks
	$(RM) $(VALOR_EXPT)/bin/valor_sbn-write_spectra_using_universes

distclean: FORCE
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_sbn-make_sbncode_minidst
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_sbn-make_recoselection_minidst
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_sbn-make_interaction_splines
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_sbn-make_flux_splines
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_sbn-universe_variation_tweaks
	$(RM) $(VALOR_EXPT_INSTALLATION_PATH)/bin/valor_sbn-write_spectra_using_universes

FORCE:

# DO NOT DELETE
