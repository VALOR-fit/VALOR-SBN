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
		   make-bin-lib-dir    \
		   copy-scripts-to-bin \
		   build-conventions   \
		   build-nd-fit        \
		   copy-rootdict-to-lib \
		   build-nd-fit-apps   

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
	$(MAKE) -C ${VALOR_DUNE}/src/Conventions;

build-nd-fit: make-bin-lib-dir FORCE
	@echo " "
	@echo "** Building NDFit package..."
	$(MAKE) -C ${VALOR_DUNE}/src/NDFit;

build-nd-fit-apps: make-bin-lib-dir FORCE
	@echo " "
	@echo "** Building NDFit package apps..."
	$(MAKE) -C ${VALOR_DUNE}/src/Apps;

make-bin-lib-dir: FORCE
	@echo " "
	@echo "** Creating VALOR/DUNE lib and bin directories..."
	cd ${VALOR_DUNE}; \
	[ -d bin ] || mkdir bin; chmod 755 bin;\
	[ -d lib ] || mkdir lib; chmod 755 lib;

copy-rootdict-to-lib: make-bin-lib-dir FORCE
	@echo " "
	@echo "** Copying ROOT dictionary PCM files to ${VALOR_DUNE}/lib"
	$(shell find "${VALOR_DUNE}/src/" -name "_RootDict*_rdict.pcm" | xargs -n 1 -I_ cp _ "${VALOR_DUNE}/lib/" )

purge: FORCE
	@echo " "
	@echo "** Purging..."
	cd ${VALOR_DUNE}/src;\
	cd Apps;                      $(MAKE) purge; cd ..; \
	cd Conventions;               $(MAKE) purge; cd ..; \
	cd NDFit;                     $(MAKE) purge; cd ..; \
	cd ${VALOR_DUNE}

clean: clean-files clean-dir clean-etc

force-clean: clean-files force-clean-dir clean-etc

clean-files: FORCE
	@echo " "
	@echo "** Cleaning..."
	rm -f ${VALOR_DUNE}/bin/valor_dune-config; \
	cd ${VALOR_DUNE}/src;\
	cd Apps;                    $(MAKE) clean; cd ..; \
	cd Conventions;             $(MAKE) clean; cd ..; \
	cd NDFit;                   $(MAKE) clean; cd ..; \
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

