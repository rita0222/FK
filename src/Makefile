SHELL	= /bin/sh

RM		= rm -f
CP		= cp
BASE		= base math material shape model scene graphics window util
AUDIO		= audio
OPENCL		= OpenCL
SHADER		= shader
AR		= AR

all:
	@echo "	FreeBSD:		make fb"
	@echo "	FreeBSD Dynamic:	make fb-d"
	@echo "	FreeBSD Debug:		make fb-g"
	@echo "	Linux:			make linux"
	@echo "	MingW:			make ming"
	@echo "	MingW Debug:		make ming-g"
	@echo "	MacOS X:		make mac"
	@echo "	MacOS X Dynamic:	make mac-d"
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
	for sd in $(BASE) $(AUDIO) $(OPENCL) $(SHADER); do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) fb TARGET=depend ; \
		$(MAKE) fb ; \
		cd .. ; done

fb-d:
	for sd in $(BASE) $(AUDIO) $(OPENCL) $(SHADER); do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) fb-d TARGET=depend ; \
		$(MAKE) fb-d ; \
		cd .. ; done

fb-g:
	for sd in $(BASE) $(AUDIO) $(OPENCL) $(SHADER); do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) fb-g TARGET=depend ; \
		$(MAKE) fb-g ; \
		cd .. ; done

linux:
	for sd in $(BASE) $(AUDIO) $(OPENCL) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) linux TARGET=depend ; \
		$(MAKE) linux ; \
		cd .. ; done

ming:
	for sd in $(BASE) $(AUDIO) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) ming TARGET=depend ; \
		$(MAKE) ming ; \
		cd .. ; done

ming-g:
	for sd in $(BASE) $(AUDIO) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) ming-g TARGET=depend ; \
		$(MAKE) ming-g ; \
		cd .. ; done

mac:
	for sd in $(BASE) $(AUDIO) $(OPENCL) $(SHADER) $(AR) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac TARGET=depend ; \
		$(MAKE) mac ; \
		cd .. ; done

mac-d:
	for sd in $(BASE) $(AUDIO) $(OPENCL) $(SHADER) $(AR) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac-d TARGET=depend ; \
		$(MAKE) mac-d ; \
		cd .. ; done

mac-g:
	for sd in $(BASE) $(AUDIO) $(OPENCL) $(SHADER) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac-g TARGET=depend ; \
		$(MAKE) mac-g ; \
		cd .. ; done

mac-gcc:
	for sd in $(BASE) $(AUDIO) $(OPENCL) $(SHADER) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac-gcc TARGET=depend ; \
		$(MAKE) mac-gcc ; \
		cd .. ; done

mac-gcc-g:
	for sd in $(BASE) $(AUDIO) $(OPENCL) $(SHADER) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac-gcc-g TARGET=depend ; \
		$(MAKE) mac-gcc-g ; \
		cd .. ; done

qt:
	cd qt; $(MAKE) release MAKE=$(MAKE)

qt-g:
	cd qt; $(MAKE) debug MAKE=$(MAKE)

mac-qt:
	cd qt; $(MAKE) mac-qt MAKE=$(MAKE)

mac-qt-g:
	cd qt; $(MAKE) mac-qt-g MAKE=$(MAKE)

clean:
	for sd in $(BASE) $(AUDIO) $(OPENCL) $(SHADER) ; do \
		cd $$sd ; \
		$(MAKE) clean -f Makefile.plane ; \
		$(RM) Makefile ; \
		cd .. ; done

clean-qt:
	cd qt; $(MAKE) clean

clean-mac:
	cd qt; $(MAKE) clean-mac

####################
