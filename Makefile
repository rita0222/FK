SHELL	= /bin/sh

RM		= rm -f
CP		= cp

all:
	@echo "	FreeBSD:		make fb"
	@echo "	FreeBSD Dynamic:	make fb-d"
	@echo "	FreeBSD Debug:		make fb-g"
	@echo "	Linux: 			make linux"
	@echo "	MingW:			make ming"
	@echo "	MingW Debug:		make ming-g"
	@echo "	macOS:			make mac"
	@echo "	macOS Dynamic:		make mac-d"
	@echo "	macOS Debug:		make mac-g"
	@echo "	macOS gcc:		make mac-gcc"
	@echo "	macOS gcc Debug:	make mac-gcc-g"
	@echo "	macOS All:		make mac-all"
	@echo "	Qt:			make qt"
	@echo "	Qt Debug:		make qt-g"
	@echo "	Mac Qt:			make mac-qt"
	@echo "	Mac Qt Debug:		make mac-qt-g"
	@echo "	Clean:			make clean"
	@echo "	Qt-Clean:		make clean-qt"
	@echo "	Document:		make document"
	@echo "	Doc Clean:		make doc-clean"

fb:
	cd src; $(MAKE) fb
	cd samples; $(MAKE) fb

fb-d:
	cd src; $(MAKE) fb-d
	cd samples; $(MAKE) fb-d

fb-g:
	cd src; $(MAKE) fb-g
	cd samples; $(MAKE) fb-g

linux:
	cd src; $(MAKE) linux
	cd samples; $(MAKE) linux

ming:
	cd src; $(MAKE) ming MAKE=make
	cd samples; $(MAKE) ming MAKE=make

ming-g:
	cd src; $(MAKE) ming-g MAKE=make
	cd samples; $(MAKE) ming-g MAKE=make

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
	cd src; $(MAKE) mac-d

qt:
	cd src; $(MAKE) qt
	cd samples_qt; $(MAKE) release MAKE=$(MAKE)

qt-g:
	cd src; $(MAKE) qt-g
	cd samples_qt; $(MAKE) debug MAKE=$(MAKE)

mac-qt:
	cd src; $(MAKE) mac-qt MAKE=$(MAKE)
	cd samples_qt; $(MAKE) mac-qt MAKE=$(MAKE)

mac-qt-g:
	cd src; $(MAKE) mac-qt-g MAKE=$(MAKE)
	cd samples_qt; $(MAKE) mac-qt-g MAKE=$(MAKE)

document:
	cd doc; $(MAKE) doc MAKE=$(MAKE)

clean:
	cd src; $(MAKE) clean
	cd samples; $(MAKE) clean
	cd lib/dynamic; $(RM) lib*
	cd lib/static; $(RM) lib*
	$(RM) core *.core *.exe *~ #*# Makefile.bak
	cd FK; $(RM) *~

clean-qt:
	cd src; $(MAKE) clean-qt
	cd samples_qt; $(MAKE) clean

clean-mac:
	cd src; $(MAKE) clean-mac
	cd samples_qt; $(MAKE) clean-mac

doc-clean:
	cd doc; $(MAKE) clean

####################
# DO NOT DELETE
