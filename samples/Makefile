SHELL	= /bin/sh

.SUFFIXES : .cxx .o
.SUFFIXES : .c .o

CC		= c++
LINKCC		= c++
RM		= rm -rf
TOUCH		= touch
AR		= ar
AROPS		= cru
LODER		= $(AR) $(AROPS)
LOCAL		= /usr/local
OPTLOCAL	= /opt/local
OPTOPT		= -O
GRAMOPT		= -pedantic -std=c++17
WARNOPT		= -Wall -Wextra -Wshadow -Wpointer-arith -Wconversion \
			-Wredundant-decls -Woverloaded-virtual -Wno-long-long
EXTOPT		= -Werror
OPS		= $(OPTOPT) $(GRAMOPT) $(WARNOPT) $(EXTOPT)
POSTLINK	= :
#

SAMPLESRCS	= $(shell /usr/bin/find . -maxdepth 1 -name "*.cxx" -print)

SAMPLE		= $(SAMPLESRCS:.cxx=)
SAMPLEEXE	= $(SAMPLESRCS:cxx=exe)
SAMPLEAPPS	= $(SAMPLESRCS:cxx=app)
ALLSRCS		= $(SAMPLESRCS)

VERNAME		= 4.2.0

###################

FKLIB_S		= -lFK4
FKLIB_SG	= -lFK4_g
FKLIB_D		= -lFK4.$(VERNAME)
FKLIB_DG	= -lFK4_g.$(VERNAME)

FKLINK		= $(FKLIB_S)
LINK		= $(FKLINK) $(SYSLIBS)
TARGET		= target
OUTPUT		= -o $*

FKTOP		= ..
MACPACK		= $(FKTOP)/MacPack
MACINCLUDE	= $(MACPACK)/include
MACSYSLIB_S	= $(MACPACK)/lib/static
MACSYSLIB_D	= $(MACPACK)/lib/dynamic


all:
	@echo "	Linux:			make linux"
	@echo "	macOS:			make mac"
	@echo "	macOS Dynamic:		make mac-d"
	@echo "	macOS Debug:		make mac-g"

linux:
	$(MAKE) $(TARGET) \
	"GRAMOPT = -pedantic -std=c++17" \
	"SYSOPS = -D_LINUX_ -DNO_GLU_LIBRARY" \
	"INCLDIRS = -I. -I.. -I$(LOCAL)/include" \
	"LFLAGS = -L../lib/static -L$(LOCAL)/lib" \
	"SYSLIBS = -liconv_hook \
		-lopenal -lvorbisfile -lvorbis -logg \
		-lfltk_images -lfltk_forms -lfltk_gl -lfltk \
		-ljpeg -lpng -lfreetype -lGL -lpthread -lOpenCL \
		-lXext -lX11 -lz -lm" \
	"RANLIB = ranlib" \
	"FKLINK = $(FKLIB_S)"

mac:
	$(MAKE) $(TARGET) \
	"OPTOPT = -O -pipe" \
	"SYSOPS = -D_MACOSX_" \
	"INCLDIRS = -I. -I.. -I$(MACINCLUDE)" \
	"LFLAGS = -L../lib/static -L$(MACSYSLIB_S) -L/opt/local/lib" \
	"SYSLIBS = \
		-licuuc -licudata \
		-lfltk_gl -lfltk \
		-lopenal -lvorbisfile -lvorbis -logg \
		-lpng  -ljpeg -lfreetype -lz -lbz2 \
		-framework QTKit \
		-framework CoreVideo \
		-framework AGL \
		-framework OpenGL \
		-framework Cocoa \
		-framework ApplicationServices \
		-framework OpenCL \
		-framework Foundation \
		-framework Accelerate \
		-framework CoreAudio \
		-framework AudioToolBox" \
	"RANLIB = ranlib" \
	"FKLINK = $(FKLIB_S)" \
	"SAMPLE = $(SAMPLEAPPS)" \
	"POSTLINK = ../FK/appmake.pl"

mac-d:
	$(MAKE) $(TARGET) \
	"OPTOPT = -O -pipe" \
	"SYSOPS = -D_MACOSX_" \
	"INCLDIRS = -I. -I.. -I$(MACINCLUDE)" \
	"LFLAGS = -L../lib/dynamic -L$(MACSYSLIB_D)" \
	"SYSLIBS = -lfltk_gl.1.3 -lfltk.1.3 -liconv.8 \
		-lvorbisfile.3 -lvorbis.0 -logg.0 \
		-lpng16.16 -ljpeg.9 -lfreetype.6 \
		-lz.1 -lbz2.1.0.6 \
		-framework AGL -framework OpenGL \
		-framework Cocoa -framework OpenAL \
		-framework ApplicationServices \
		-framework OpenCL \
		-framework Foundation \
		-framework AudioToolBox" \
	"RANLIB = ranlib" \
	"FKLINK = $(FKOPENCL_D) $(FKAUDIO_D) $(FKSHADER_D) $(FKLIB_D)" \
	"SAMPLE = $(SAMPLEAPPS)" \
	"POSTLINK = ../FK/appmake.pl -s $(MACSYSLIB_D)"

mac-g:
	$(MAKE) $(TARGET) \
	"OPTOPT = -g" \
	"SYSOPS = -D_MACOSX_" \
	"INCLDIRS = -I. -I.. -I$(MACINCLUDE)" \
	"LFLAGS = -L../lib/static -L$(MACSYSLIB_S)" \
	"SYSLIBS = -liconv -lfltk_gl -lfltk \
		-lopenal -lvorbisfile -lvorbis -logg \
		-lpng  -ljpeg -lfreetype -lz -lbz2 \
		-framework QTKit \
		-framework CoreVideo \
		-framework AGL \
		-framework OpenGL \
		-framework Cocoa \
		-framework ApplicationServices \
		-framework OpenCL \
		-framework Foundation \
		-framework Accelerate \
		-framework CoreAudio \
		-framework AudioToolBox" \
	"RANLIB = ranlib" \
	"FKLINK = $(FKOPENCL_SG) $(FKAUDIO_SG) $(FKSHADER_SG) $(FKLIB_SG)" \
	"SAMPLE = $(SAMPLEAPPS)" \
	"POSTLINK = ../FK/appmake.pl"

CFLAGS = $(OPS) $(SYSOPS) $(INCLDIRS)

target : $(SAMPLE)

depend:: $(SAMPLESRCS)
	@:

clean:
	$(RM) $(SAMPLE) $(SAMPLEEXE) Makefile.bak \
		$(SAMPLESRCS:cxx=o) $(SAMPLEAPPS) \
		*.out core *.core *~ #*# 
###
%.app : %.cxx
	$(CC) -c $(CFLAGS) $< -o $*.o
	$(LINKCC) $(SYSOPS) $(LFLAGS) $*.o $(LINK) -o $*
	$(POSTLINK) $*

.cxx :
	$(CC) $(CFLAGS) $(LFLAGS) $< $(OUTPUT) $(LINK)

####################
