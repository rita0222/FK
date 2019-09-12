SHELL	= /bin/sh

RM		= rm -f
CP		= cp

all:
	@echo "	macOS:			make mac"
	@echo "	macOS Dynamic:		make mac-d"
	@echo "	macOS Debug:		make mac-g"
	@echo "	macOS All:		make mac-all"
	@echo "	Linux:			make linux"
	@echo "	Clean:			make clean"
	@echo "	Document:		make document"
	@echo "	Doc Clean:		make doc-clean"

mac:
	cd src; $(MAKE) mac
	cd samples; $(MAKE) mac

mac-d:
	cd src; $(MAKE) mac-d
	cd samples; $(MAKE) mac-d

mac-g:
	cd src; $(MAKE) mac-g
	cd samples; $(MAKE) mac-g

mac-gcc:
	cd src; $(MAKE) mac-gcc
	cd samples; $(MAKE) mac-gcc

mac-gcc-g:
	cd src; $(MAKE) mac-gcc-g
	cd samples; $(MAKE) mac-gcc-g

mac-all:
	cd src; $(MAKE) clean
	cd lib/dynamic; $(RM) lib*
	cd lib/static; $(RM) lib*
	cd src; $(MAKE) mac
	cd src; $(MAKE) clean
	cd src; $(MAKE) mac-g

linux:
	cd src; $(MAKE) linux
	cd samples; $(MAKE) linux

document:
	cd doc; $(MAKE) doc MAKE=$(MAKE)

clean:
	cd src; $(MAKE) clean
	cd samples; $(MAKE) clean
	cd lib/dynamic; $(RM) lib*
	cd lib/static; $(RM) lib*
	$(RM) core *.core *.exe *~ #*# Makefile.bak
	cd FK; $(RM) *~

doc-clean:
	cd doc; $(MAKE) clean

####################
# DO NOT DELETE
