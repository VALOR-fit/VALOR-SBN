#
# Main VALOR/DUNE project Makefile.
# 
# Author: Costas Andreopoulos <costas.andreopoulos \at stfc.ac.uk>
#

SHELL = /bin/sh
NAME = all
MAKEFILE = Makefile

# Include machine specific flags and locations (inc. files & libs)
#
include $(VALOR_DUNE)/make/Make.include

# define composite targets
#
BUILD_TARGETS =    print-make-info     \
		   make-bin-lib-dir                \
		   copy-scripts-to-bin             \
		   build-conventions               \
		   build-binning                   \
		   build-systematics               \
		   build-utilities                 \
		   build-genie-utilities           \
		   build-elements                  \
		   build-sd-fit                    \
		   copy-rootdict-to-lib            \
		   build-apps   

# define targets

all:     $(BUILD_TARGETS)
install: 

print-make-info: FORCE
	@echo " "
	@echo " "
	@echo "***** Building VALOR/DUNE from source tree at: $(VALOR_DUNE)"
	@echo "***** The source tree corresponds to VALOR version $(VALOR_VERSION)"
	@echo " "

copy-scripts-to-bin: make-bin-lib-dir FORCE
	@echo " "
	@echo "** Copying scripts to bin..."
	cp ${VALOR_DUNE}/make/valor_dune-config ${VALOR_DUNE}/bin
	cp ${VALOR_DUNE}/root/valor_dune        ${VALOR_DUNE}/bin
	cp ${VALOR_DUNE}/root/pydune            ${VALOR_DUNE}/bin
	
build-conventions: make-bin-lib-dir FORCE
	@echo " "
	@echo "** Building Conventions package..."
	$(MAKE) -C ${VALOR_DUNE}/src/dune/Conventions;
	
build-binning: make-bin-lib-dir FORCE
	@echo " "
	@echo "** Building Conventions package..."
	$(MAKE) -C ${VALOR_DUNE}/src/dune/Binning;

build-systematics: make-bin-lib-dir FORCE
	@echo " "
	@echo "** Building Systematics package..."
	$(MAKE) -C ${VALOR_DUNE}/src/dune/Systematics;
	
build-utilities: make-bin-lib-dir FORCE
	@echo " "
	@echo "** Building DUNE Utilities package..."
	$(MAKE) -C ${VALOR_DUNE}/src/dune/Utilities;
	
build-genie-utilities: make-bin-lib-dir FORCE
ifdef GENIE
	@echo " "
	@echo "** Building DUNE GENIE Utilities package..."
	$(MAKE) -C ${VALOR_DUNE}/src/dune/GENIEUtilities;
else
	@echo " "
	@echo "** GENIE not set up - skipping GENIEUtilities"
endif

build-elements: make-bin-lib-dir FORCE
	@echo " "
	@echo "** Building Elements package..."
	$(MAKE) -C ${VALOR_DUNE}/src/dune/Elements;

build-sd-fit: make-bin-lib-dir FORCE
	@echo " "
	@echo "** Building SDFit package..."
	$(MAKE) -C ${VALOR_DUNE}/src/dune/SDFit;

build-apps: make-bin-lib-dir FORCE
	@echo " "
	@echo "** Building apps..."
	$(MAKE) -C ${VALOR_DUNE}/src/dune/Apps;

make-bin-lib-dir: FORCE
	@echo " "
	@echo "** Creating VALOR/DUNE lib and bin directories..."
	cd ${VALOR_DUNE}; \
	[ -d bin ] || mkdir bin; chmod 755 bin;\
	[ -d lib ] || mkdir lib; chmod 755 lib;

copy-rootdict-to-lib: make-bin-lib-dir FORCE
	@echo " "
	@echo "** Copying ROOT dictionary PCM files to ${VALOR_DUNE}/lib"
	$(shell find "${VALOR_DUNE}/src/dune/" -name "_RootDict*_rdict.pcm" | xargs -n 1 -I{} cp {} "${VALOR_DUNE}/lib/" )

purge: FORCE
	@echo " "
	@echo "** Purging..."
	$(MAKE) -C src/dune/Apps             purge && \
	$(MAKE) -C src/dune/Binning          purge && \
	$(MAKE) -C src/dune/Conventions      purge && \
	$(MAKE) -C src/dune/Utilities        purge && \
	$(MAKE) -C src/dune/GENIEUtilities   purge && \
	$(MAKE) -C src/dune/Elements         purge && \
	$(MAKE) -C src/dune/SDFit            purge && \
	$(MAKE) -C src/dune/Systematics      purge; \

clean: clean-files clean-dir clean-etc

force-clean: clean-files force-clean-dir clean-etc

clean-files: FORCE
	@echo " "
	@echo "** Cleaning..."
	rm -f ${VALOR_DUNE}/bin/valor_dune-config; \
	$(MAKE) -C src/dune/Apps            clean && \
	$(MAKE) -C src/dune/Binning         clean && \
	$(MAKE) -C src/dune/Conventions     clean && \
	$(MAKE) -C src/dune/Utilities       clean && \
	$(MAKE) -C src/dune/GENIEUtilities  clean && \
	$(MAKE) -C src/dune/Elements        clean && \
	$(MAKE) -C src/dune/SDFit           clean && \
	$(MAKE) -C src/dune/Systematics     clean; \
	cd $(VALOR_DUNE);\
    [ ! -d ./bin ] || rm ./bin/*;\
	cd $(VALOR_DUNE)

clean-dir: FORCE
	@echo "Deleting VALOR/DUNE lib and bin directories...";\
	cd $(VALOR_DUNE);\
	[ ! -d ./bin ] || rmdir ./bin;\
	[ ! -d ./lib ] || rmdir ./lib 

force-clean-dir: FORCE
	@echo "Deleting VALOR/DUNE lib and bin directories...";\
	cd $(VALOR_DUNE);\
	[ ! -d ./bin ] || rm -rf ./bin;\
	[ ! -d ./lib ] || rm -rf ./lib 

clean-etc: FORCE
	cd $(VALOR_DUNE); \
	rm -f ./*log; \
	cd ${VALOR_DUNE}

FORCE:

