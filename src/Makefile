SHELL	= /bin/sh

RM		= rm -f
CP		= cp
BASE		= base math material parser shape solid model scene graphics util
AUDIO		= audio
OPENCL		= OpenCL

all:
	@echo "	FreeBSD:		make fb"
	@echo "	FreeBSD Debug:		make fb-g"
	@echo "	Linux:			make linux"
	@echo "	MingW:			make ming"
	@echo "	MingW Debug:		make ming-g"
	@echo "	MacOS X:		make mac"
	@echo "	MacOS X Debug:		make mac-g"
	@echo "	MacOS X gcc:		make mac-gcc"
	@echo "	MacOS X gcc Debug:	make mac-gcc-g"
	@echo "	Qt:			make qt"
	@echo "	Qt Debug:		make qt-g"
	@echo "	Mac Qt:			make mac-qt"
	@echo "	Mac Qt Debug:		make mac-qt-g"
	@echo "	Clean:			make clean"
	@echo "	Qt-Clean:		make clean-qt"
	@echo "	Qt-Mac-Clean:		make clean-mac"

fb:
	for sd in $(BASE) $(AUDIO) $(OPENCL) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) fb TARGET=depend ; \
		$(MAKE) fb ; \
		cd .. ; done
	cd fltk; $(MAKE) fb

fb-g:
	for sd in $(BASE) $(AUDIO) $(OPENCL) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) fb-g TARGET=depend ; \
		$(MAKE) fb-g ; \
		cd .. ; done
	cd fltk; $(MAKE) fb-g

linux:
	for sd in $(BASE) $(AUDIO) $(OPENCL) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) linux TARGET=depend ; \
		$(MAKE) linux ; \
		cd .. ; done
	cd fltk; $(MAKE) linux

ming:
	for sd in $(BASE) $(AUDIO) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) ming TARGET=depend ; \
		$(MAKE) ming ; \
		cd .. ; done
	cd fltk; $(MAKE) ming

ming-g:
	for sd in $(BASE) $(AUDIO) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) ming-g TARGET=depend ; \
		$(MAKE) ming-g ; \
		cd .. ; done
	cd fltk; $(MAKE) ming-g

mac:
	for sd in $(BASE) $(AUDIO) $(OPENCL) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac TARGET=depend ; \
		$(MAKE) mac ; \
		cd .. ; done
	cd fltk; $(MAKE) mac

mac-g:
	for sd in $(BASE) $(AUDIO) $(OPENCL) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac-g TARGET=depend ; \
		$(MAKE) mac-g ; \
		cd .. ; done
	cd fltk; $(MAKE) mac-g

mac-gcc:
	for sd in $(BASE) $(AUDIO) $(OPENCL) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac-gcc TARGET=depend ; \
		$(MAKE) mac-gcc ; \
		cd .. ; done
	cd fltk; $(MAKE) mac-gcc

mac-gcc-g:
	for sd in $(BASE) $(AUDIO) $(OPENCL) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac-gcc-g TARGET=depend ; \
		$(MAKE) mac-gcc-g ; \
		cd .. ; done
	cd fltk; $(MAKE) mac-gcc-g

qt:
	cd qt; $(MAKE) release MAKE=$(MAKE)

qt-g:
	cd qt; $(MAKE) debug MAKE=$(MAKE)

mac-qt:
	cd qt; $(MAKE) mac-qt MAKE=$(MAKE)

mac-qt-g:
	cd qt; $(MAKE) mac-qt-g MAKE=$(MAKE)

clean:
	for sd in $(BASE) $(AUDIO) $(OPENCL) ; do \
		cd $$sd ; \
		$(MAKE) clean -f Makefile.plane ; \
		$(RM) Makefile ; \
		cd .. ; done
	cd fltk; $(MAKE) clean

clean-qt:
	cd qt; $(MAKE) clean

clean-mac:
	cd qt; $(MAKE) clean-mac

####################
