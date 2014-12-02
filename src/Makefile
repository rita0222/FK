SHELL	= /bin/sh

RM		= rm -f
CP		= cp

all:
	@echo "	FreeBSD:		make fb"
	@echo "	FreeBSD Debug:		make fb-g"
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
	cd base; $(CP) Makefile.plane Makefile
	cd base; $(MAKE) fb TARGET=depend; $(MAKE) fb
	cd util; $(CP) Makefile.plane Makefile
	cd util; $(MAKE) fb TARGET=depend; $(MAKE) fb
	cd audio; $(CP) Makefile.plane Makefile
	cd audio; $(MAKE) fb TARGET=depend; $(MAKE) fb
	cd fltk; $(MAKE) fb
	cd OpenCL; $(CP) Makefile.plane Makefile
	cd OpenCL; $(MAKE) fb TARGET=depend; $(MAKE) fb

fb-g:
	cd base; $(CP) Makefile.plane Makefile
	cd base; $(MAKE) fb-g TARGET=depend; $(MAKE) fb-g
	cd util; $(CP) Makefile.plane Makefile
	cd util; $(MAKE) fb-g TARGET=depend; $(MAKE) fb-g
	cd audio; $(CP) Makefile.plane Makefile
	cd audio; $(MAKE) fb-g TARGET=depend; $(MAKE) fb-g
	cd fltk; $(MAKE) fb-g
	cd OpenCL; $(CP) Makefile.plane Makefile
	cd OpenCL; $(MAKE) fb-g TARGET=depend; $(MAKE) fb-g

cw-gcc:
	cd base; $(CP) Makefile.plane Makefile;
	cd base; $(MAKE) cw-gcc
	cd util; $(CP) Makefile.plane Makefile
	cd util; $(MAKE) cw-gcc
	cd fltk; $(MAKE) cw-gcc

ming:
	cd base; $(CP) Makefile.plane Makefile;
	cd base; $(MAKE) ming MAKE=make
	cd util; $(CP) Makefile.plane Makefile
	cd util; $(MAKE) ming MAKE=make
	cd audio; $(CP) Makefile.plane Makefile
	cd audio; $(MAKE) ming TARGET=depend; $(MAKE) ming
	cd fltk; $(MAKE) ming MAKE=make

ming-g:
	cd base; $(CP) Makefile.plane Makefile;
	cd base; $(MAKE) ming-g MAKE=make
	cd util; $(CP) Makefile.plane Makefile
	cd util; $(MAKE) ming-g MAKE=make
	cd audio; $(CP) Makefile.plane Makefile
	cd audio; $(MAKE) ming TARGET=depend; $(MAKE) ming-g
	cd fltk; $(MAKE) ming-g MAKE=make

mac:
	cd base; $(CP) Makefile.plane Makefile
	cd base; $(MAKE) mac TARGET=depend; $(MAKE) mac
	cd util; $(CP) Makefile.plane Makefile
	cd util; $(MAKE) mac TARGET=depend; $(MAKE) mac
	cd audio; $(CP) Makefile.plane Makefile
	cd audio; $(MAKE) mac TARGET=depend; $(MAKE) mac
	cd fltk; $(MAKE) mac
	cd OpenCL; $(CP) Makefile.plane Makefile
	cd OpenCL; $(MAKE) mac TARGET=depend; $(MAKE) mac

mac-g:
	cd base; $(CP) Makefile.plane Makefile;
	cd base; $(MAKE) mac-g TARGET=depend; $(MAKE) mac-g
	cd util; $(CP) Makefile.plane Makefile
	cd util; $(MAKE) mac-g TARGET=depend; $(MAKE) mac-g
	cd audio; $(CP) Makefile.plane Makefile
	cd audio; $(MAKE) mac-g TARGET=depend; $(MAKE) mac-g
	cd fltk; $(MAKE) mac-g
	cd OpenCL; $(CP) Makefile.plane Makefile
	cd OpenCL; $(MAKE) mac TARGET=depend; $(MAKE) mac-g

mac-gcc:
	cd base; $(CP) Makefile.plane Makefile
	cd base; $(MAKE) mac-gcc TARGET=depend; $(MAKE) mac-gcc
	cd util; $(CP) Makefile.plane Makefile
	cd util; $(MAKE) mac-gcc TARGET=depend; $(MAKE) mac-gcc
	cd audio; $(CP) Makefile.plane Makefile
	cd audio; $(MAKE) mac-gcc TARGET=depend; $(MAKE) mac-gcc
	cd fltk; $(MAKE) mac-gcc
	cd OpenCL; $(CP) Makefile.plane Makefile
	cd OpenCL; $(MAKE) mac TARGET=depend; $(MAKE) mac-gcc

mac-gcc-g:
	cd base; $(CP) Makefile.plane Makefile;
	cd base; $(MAKE) mac-gcc-g TARGET=depend; $(MAKE) mac-gcc-g
	cd util; $(CP) Makefile.plane Makefile
	cd util; $(MAKE) mac-gcc-g TARGET=depend; $(MAKE) mac-gcc-g
	cd audio; $(CP) Makefile.plane Makefile
	cd audio; $(MAKE) mac-gcc-g TARGET=depend; $(MAKE) mac-gcc-g
	cd fltk; $(MAKE) mac-gcc-g
	cd OpenCL; $(CP) Makefile.plane Makefile
	cd OpenCL; $(MAKE) mac TARGET=depend; $(MAKE) mac-gcc-g

qt:
	cd qt; $(MAKE) release MAKE=$(MAKE)

qt-g:
	cd qt; $(MAKE) debug MAKE=$(MAKE)

mac-qt:
	cd qt; $(MAKE) mac-qt MAKE=$(MAKE)

mac-qt-g:
	cd qt; $(MAKE) mac-qt-g MAKE=$(MAKE)

clean:
	cd base; $(MAKE) clean -f Makefile.plane; $(RM) Makefile
	cd util; $(MAKE) clean -f Makefile.plane; $(RM) Makefile
	cd audio; $(MAKE) clean -f Makefile.plane; $(RM) Makefile
	cd fltk; $(MAKE) clean

clean-qt:
	cd qt; $(MAKE) clean

clean-mac:
	cd qt; $(MAKE) clean-mac

####################
