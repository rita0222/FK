SHELL	= /bin/sh

RM		= rm -f
CP		= cp
BASE		= \
			base \
			material \
			math \
			shape \
			graph \
			texture \
			solid \
			model \
			scene \
			shader \
			graphics \
			window \
			util

AUDIO		= audio
OPENCL		= OpenCL

all:
	@echo "	macOS:			make mac"
	@echo "	macOS Dynamic:		make mac-d"
	@echo "	macOS Debug:		make mac-g"
	@echo "	Linux:			make linux"
	@echo "	Clean:			make clean"

mac:
	cd graphics ; $(CP) Makefile.plane Makefile ; $(MAKE) mac TARGET=glsl ; cd ..
	cd shader; $(CP) Makefile.plane Makefile ; $(MAKE) mac TARGET=glsl ; cd ..
	for sd in $(BASE) $(AUDIO) $(OPENCL) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac TARGET=depend ; \
		$(MAKE) mac ; \
		cd .. ; done

mac-d:
	cd graphics ; $(CP) Makefile.plane Makefile ; $(MAKE) mac TARGET=glsl ; cd ..
	cd shader; $(CP) Makefile.plane Makefile ; $(MAKE) mac-d TARGET=glsl ; cd ..
	for sd in $(BASE) $(AUDIO) $(OPENCL) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac-d TARGET=depend ; \
		$(MAKE) mac-d ; \
		cd .. ; done

mac-g:
	cd graphics ; $(CP) Makefile.plane Makefile ; $(MAKE) mac TARGET=glsl ; cd ..
	cd shader; $(CP) Makefile.plane Makefile ; $(MAKE) mac-g TARGET=glsl ; cd ..
	for sd in $(BASE) $(AUDIO) $(OPENCL) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) mac-g TARGET=depend ; \
		$(MAKE) mac-g ; \
		cd .. ; done

linux:
	cd graphics ; $(CP) Makefile.plane Makefile ; $(MAKE) linux TARGET=glsl ; cd ..
	cd shader; $(CP) Makefile.plane Makefile ; $(MAKE) linux TARGET=glsl ; cd ..
	for sd in $(BASE) $(AUDIO) $(OPENCL) ; do \
		cd $$sd ; \
		$(CP) Makefile.plane Makefile ; \
		$(MAKE) linux TARGET=depend ; \
		$(MAKE) linux ; \
		cd .. ; done

clean:
	for sd in $(BASE) $(AUDIO) $(OPENCL) ; do \
		cd $$sd ; \
		$(MAKE) clean -f Makefile.plane ; \
		$(RM) Makefile ; \
		cd .. ; done

####################
