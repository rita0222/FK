SHELL	= /bin/sh

RM		= rm -f
CP		= cp

all:
	@echo "	FreeBSD:		make fb"
	@echo "	FreeBSD Debug:		make fb-g"
	@echo "	Linux:			make linux"
	@echo "	MinGW:			make ming"
	@echo "	MinGW Debug:		make ming-g"
	@echo "	MacOS X:		make mac"
	@echo "	MacOS X Debug:		make mac-g"
	@echo "	MacOS X gcc:		make mac-gcc"
	@echo "	MacOS X gcc Debug:	make mac-gcc-g"

fb:
	cd Window; $(CP) Makefile.plane Makefile
	cd Window; $(MAKE) fb TARGET=depend; $(MAKE) fb
	cd Error; $(CP) Makefile.plane Makefile
	cd Error; $(MAKE) fb TARGET=depend; $(MAKE) fb

fb-g:
	cd Window; $(CP) Makefile.plane Makefile
	cd Window; $(MAKE) fb-g TARGET=depend; $(MAKE) fb-g
	cd Error; $(CP) Makefile.plane Makefile
	cd Error; $(MAKE) fb-g TARGET=depend; $(MAKE) fb-g

linux:
	cd Window; $(CP) Makefile.plane Makefile
	cd Window; $(MAKE) linux TARGET=depend; $(MAKE) linux
	cd Error; $(CP) Makefile.plane Makefile
	cd Error; $(MAKE) linux TARGET=depend; $(MAKE) linux

ming:
	cd Window; $(CP) Makefile.plane Makefile
	cd Window; $(MAKE) ming TARGET=depend; $(MAKE) ming
	cd Error; $(CP) Makefile.plane Makefile
	cd Error; $(MAKE) ming TARGET=depend; $(MAKE) ming

ming-g:
	cd Window; $(CP) Makefile.plane Makefile
	cd Window; $(MAKE) ming-g TARGET=depend; $(MAKE) ming-g
	cd Error; $(CP) Makefile.plane Makefile
	cd Error; $(MAKE) ming-g TARGET=depend; $(MAKE) ming-g

mac:
	cd Window; $(CP) Makefile.plane Makefile
	cd Window; $(MAKE) mac TARGET=depend; $(MAKE) mac
	cd Error; $(CP) Makefile.plane Makefile
	cd Error; $(MAKE) mac TARGET=depend; $(MAKE) mac

mac-g:
	cd Window; $(CP) Makefile.plane Makefile
	cd Window; $(MAKE) mac-g TARGET=depend; $(MAKE) mac-g
	cd Error; $(CP) Makefile.plane Makefile
	cd Error; $(MAKE) mac-g TARGET=depend; $(MAKE) mac-g

mac-gcc:
	cd Window; $(CP) Makefile.plane Makefile
	cd Window; $(MAKE) mac-gcc TARGET=depend; $(MAKE) mac-gcc
	cd Error; $(CP) Makefile.plane Makefile
	cd Error; $(MAKE) mac-gcc TARGET=depend; $(MAKE) mac-gcc

mac-gcc-g:
	cd Window; $(CP) Makefile.plane Makefile
	cd Window; $(MAKE) mac-gcc-g TARGET=depend; $(MAKE) mac-gcc-g
	cd Error; $(CP) Makefile.plane Makefile
	cd Error; $(MAKE) mac-gcc-g TARGET=depend; $(MAKE) mac-gcc-g

clean:
	cd Window; $(MAKE) clean -f Makefile.plane; $(RM) Makefile
	cd Error; $(MAKE) clean -f Makefile.plane; $(RM) Makefile

####################
