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
	@echo "	MacOS X:		make mac"
	@echo "	MacOS X Dynamic:	make mac-d"
	@echo "	MacOS X Debug:		make mac-g"
	@echo "	MacOS X gcc:		make mac-gcc"
	@echo "	MacOS X gcc Debug:	make mac-gcc-g"
	@echo "	Clean:			make clean"

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

mac:
	cd graphics ; $(CP) Makefile.plane Makefile ; $(MAKE) mac TARGET=glsl ; cd ..
	cd shader; $(CP) Makefile.plane Makefile ; $(MAKE) mac TARGET=glsl ; cd ..
	for sd in $(BASE) $(AUDIO) $(OPENCL) $(SHADER) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac TARGET=depend ; \
		$(MAKE) mac ; \
		cd .. ; done

mac-d:
	cd graphics ; $(CP) Makefile.plane Makefile ; $(MAKE) mac TARGET=glsl ; cd ..
	cd shader; $(CP) Makefile.plane Makefile ; $(MAKE) mac-d TARGET=glsl ; cd ..
	for sd in $(BASE) $(AUDIO) $(OPENCL) $(SHADER) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac-d TARGET=depend ; \
		$(MAKE) mac-d ; \
		cd .. ; done

mac-g:
	cd graphics ; $(CP) Makefile.plane Makefile ; $(MAKE) mac TARGET=glsl ; cd ..
	cd shader; $(CP) Makefile.plane Makefile ; $(MAKE) mac-g TARGET=glsl ; cd ..
	for sd in $(BASE) $(AUDIO) $(OPENCL) $(SHADER) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac-g TARGET=depend ; \
		$(MAKE) mac-g ; \
		cd .. ; done

mac-gcc:
	cd graphics ; $(CP) Makefile.plane Makefile ; $(MAKE) mac TARGET=glsl ; cd ..
	cd shader; $(CP) Makefile.plane Makefile ; $(MAKE) mac-gcc TARGET=glsl ; cd ..
	for sd in $(BASE) $(AUDIO) $(OPENCL) $(SHADER) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac-gcc TARGET=depend ; \
		$(MAKE) mac-gcc ; \
		cd .. ; done

mac-gcc-g:
	cd graphics ; $(CP) Makefile.plane Makefile ; $(MAKE) mac TARGET=glsl ; cd ..
	cd shader; $(CP) Makefile.plane Makefile ; $(MAKE) mac-gcc-g TARGET=glsl ; cd ..
	for sd in $(BASE) $(AUDIO) $(OPENCL) $(SHADER) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac-gcc-g TARGET=depend ; \
		$(MAKE) mac-gcc-g ; \
		cd .. ; done

clean:
	for sd in $(BASE) $(AUDIO) $(OPENCL) $(SHADER) $(AR) ; do \
		cd $$sd ; \
		$(MAKE) clean -f Makefile.plane ; \
		$(RM) Makefile ; \
		cd .. ; done

####################
