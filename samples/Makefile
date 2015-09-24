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
GRAMOPT		= -pedantic -std=c++1y
WARNOPT		= -Wall -Wextra -Wshadow -Wpointer-arith -Wconversion \
			-Wredundant-decls -Woverloaded-virtual -Wno-long-long
EXTOPT		= -Werror
OPS		= $(OPTOPT) $(GRAMOPT) $(WARNOPT) $(EXTOPT)
POSTLINK	= :
#

SAMPLESRCS = $(shell /usr/bin/find . -maxdepth 1 -name "*.cxx" -print)

SAMPLE	= $(SAMPLESRCS:.cxx=)
SAMPLEEXE = $(SAMPLESRCS:cxx=exe)
SAMPLEAPPS = $(SAMPLESRCS:cxx=app)

ALLSRCS = $(SAMPLESRCS)

###################

FKLIB		= \
			-lFK3_audio \
			-lFK3_util \
			-lFK3_fltkWin \
			-lFK3_graphics \
			-lFK3_scene \
			-lFK3_model \
			-lFK3_solid \
			-lFK3_shape \
			-lFK3_parser \
			-lFK3_material \
			-lFK3_math \
			-lFK3_base \
			-lFK3_fltkErr

FKLIB_G		= \
			-lFK3_audio_g \
			-lFK3_util_g \
			-lFK3_fltkWin_g \
			-lFK3_graphics_g \
			-lFK3_scene_g \
			-lFK3_model_g \
			-lFK3_solid_g \
			-lFK3_shape_g \
			-lFK3_parser_g \
			-lFK3_material_g \
			-lFK3_math_g \
			-lFK3_base_g \
			-lFK3_fltkErr_g

FKLINK		= $(FKLIB)
LINK		= $(FKLINK) $(SYSLIBS)
TARGET		= target
OUTPUT		= -o $*

all:
	@echo "	FreeBSD:		make fb"
	@echo "	FreeBSD Debug:		make fb-g"
	@echo "	MingW:			make ming"
	@echo "	MingW Debug:		make ming-g"
	@echo "	MacOS X:		make mac"
	@echo "	MacOS X Debug:		make mac-g"
	@echo "	MacOS X gcc:		make mac-gcc"
	@echo "	MacOS X gcc Debug:	make mac-gcc-g"

fb:
	$(MAKE) $(TARGET) \
	"SYSOPS = -D_FREEBSD_ -DNO_GLU_LIBRARY" \
	"INCLDIRS = -I. -I.. -I../../include -I$(LOCAL)/include" \
	"LFLAGS = -L../lib -L../../lib -L$(LOCAL)/lib" \
	"SYSLIBS = -liconv \
		-lopenal -lvorbisfile -lvorbis -logg \
		-lfltk_images -lfltk_forms -lfltk_gl -lfltk \
		-ljpeg -lpng \
		-lfreetype -lGL \
		-lXft -lfontconfig -lXinerama -lpthread \
		-lXext -lX11 -lz -lbz2 -lm" \
	"RANLIB = ranlib"

fb-g:
	$(MAKE) $(TARGET) \
	"OPTOPT = -g" \
	"SYSOPS = -D_FREEBSD_ -DNO_GLU_LIBRARY" \
	"INCLDIRS = -I. -I.. -I../../include -I$(LOCAL)/include" \
	"LFLAGS = -L../lib -L../../lib -L$(LOCAL)/lib" \
	"SYSLIBS = -liconv \
		-lopenal -lvorbisfile -lvorbis -logg \
		-lfltk_images -lfltk_forms -lfltk_gl -lfltk \
		-ljpeg -lpng \
		-lfreetype -lGL \
		-lXft -lfontconfig -lXinerama -lpthread \
		-lXext -lX11 -lz -lbz2 -lm" \
	"RANLIB = ranlib" \
	"FKLINK = $(FKLIB_G)"

ming:
	$(MAKE) $(TARGET) \
	"OPTOPT = " \
	"SYSOPS = -DWIN32 -D_MINGW_ -mwindows" \
	"INCLDIRS = -I.. -I../../FK_MingPack/include" \
	"LFLAGS = -L../lib -L../../FK_MingPack/lib \
		-Wl,--enable-auto-import" \
	"SYSLIBS = -lfltk_gl -lfltk_jpeg -lfltk_png -lfltk_images \
		-lfltk_forms -lfltk \
		-lfreetype -liconv \
		-lOpenAL32 -lvorbisfile -lvorbis -logg -lz \
		-lwinmm -lole32 -luuid -lglu32 -lopengl32 \
		-limm32 -lgdi32 -lcomctl32 -lwsock32 -lsupc++" \
	"RANLIB = ranlib" \
	"FKLINK = $(FKLIB) $(FKLIB)"

ming-g:
	$(MAKE) $(TARGET) \
	"OPTOPT = -g" \
	"SYSOPS = -DWIN32 -D_MINGW_ -mwindows" \
	"INCLDIRS = -I.. -I../../FK_MingPack/include" \
	"LFLAGS = -L../lib -L../../FK_MingPack/lib \
		-Wl,--enable-auto-import" \
	"SYSLIBS = -lfltk_gl -lfltk_jpeg -lfltk_png -lfltk_images \
		-lfltk_forms -lfltk -lfltk_z \
		-lfreetype -liconv \
		-lOpenAL32 -lvorbisfile -lvorbis -logg \
		-lwinmm -lole32 -luuid -lglu32 -lopengl32 \
		-limm32 -lgdi32 -lcomctl32 -lwsock32 -lsupc++" \
	"RANLIB = ranlib" \
	"FKLINK = $(FKLIB_G)"

mac:
	$(MAKE) $(TARGET) \
	"OPTOPT = -O -pipe" \
	"SYSOPS = -D_MACOSX_" \
	"INCLDIRS = -I. -I.. -I../../FK_MacPack/include -I$(OPTLOCAL)/include" \
	"LFLAGS = -L../lib -L../../FK_MacPack/lib -L$(OPTLOCAL)/lib" \
	"SYSLIBS = -liconv -lfltk_gl -lfltk \
		-lvorbisfile -lvorbis -logg \
		-lpng  -ljpeg -lfreetype -lz -lbz2 \
		-framework AGL -framework OpenGL \
		-framework Cocoa -framework OpenAL \
		-framework ApplicationServices \
		-framework OpenCL \
		-framework Foundation \
		-framework AudioToolBox" \
	"RANLIB = ranlib" \
	"FKLINK = -lFK3_OpenCL $(FKLIB)" \
	"SAMPLE = $(SAMPLEAPPS)" \
	"POSTLINK = ../FK/appmake.pl"

mac-g:
	$(MAKE) $(TARGET) \
	"OPTOPT = -g" \
	"SYSOPS = -D_MACOSX_" \
	"INCLDIRS = -I. -I.. -I../../FK_MacPack/include -I$(OPTLOCAL)/include" \
	"LFLAGS = -L../lib -L../../FK_MacPack/lib -L$(OPTLOCAL)/lib" \
	"SYSLIBS = -liconv -lfltk_gl -lfltk \
		-lvorbisfile -lvorbis -logg \
		-lpng  -ljpeg -lfreetype -lz -lbz2 \
		-framework AGL -framework OpenGL \
		-framework Cocoa -framework OpenAL \
		-framework ApplicationServices \
		-framework OpenCL \
		-framework Foundation \
		-framework AudioToolBox" \
	"RANLIB = ranlib" \
	"FKLINK = -lFK3_OpenCL_g $(FKLIB_G)" \
	"SAMPLE = $(SAMPLEAPPS)" \
	"POSTLINK = ../FK/appmake.pl"

mac-gcc:
	$(MAKE) $(TARGET) \
	"CC = g++-mp-5" \
	"LINKCC = g++-mp-5" \
	"OPTOPT = -O -pipe" \
	"SYSOPS = -D_MACOSX_" \
	"INCLDIRS = -I. -I.. -I../../FK_MacPack/include -I$(OPTLOCAL)/include" \
	"LFLAGS = -L../lib -L../../FK_MacPack/lib -L$(OPTLOCAL)/lib" \
	"SYSLIBS = -liconv -lfltk_gl -lfltk \
		-lvorbisfile -lvorbis -logg \
		-lpng  -ljpeg -lfreetype -lz -lbz2 \
		-framework AGL -framework OpenGL \
		-framework Cocoa -framework OpenAL \
		-framework ApplicationServices \
		-framework Foundation \
		-framework AudioToolBox" \
	"RANLIB = ranlib" \
	"FKLINK = $(FKLIB)" \
	"SAMPLE = $(SAMPLEAPPS)" \
	"POSTLINK = ../FK/appmake.pl"

mac-gcc-g:
	$(MAKE) $(TARGET) \
	"CC = g++-mp-5" \
	"LINKCC = g++-mp-5" \
	"OPTOPT = -g" \
	"SYSOPS = -D_MACOSX_" \
	"INCLDIRS = -I. -I.. -I../../FK_MacPack/include -I$(OPTLOCAL)/include" \
	"LFLAGS = -L../lib -L../../FK_MacPack/lib -L$(OPTLOCAL)/lib" \
	"SYSLIBS = -liconv -lfltk_gl -lfltk \
		-lvorbisfile -lvorbis -logg \
		-lpng  -ljpeg -lfreetype -lz -lbz2 \
		-framework AGL -framework OpenGL \
		-framework Cocoa -framework OpenAL \
		-framework ApplicationServices \
		-framework Foundation \
		-framework AudioToolBox" \
	"RANLIB = ranlib" \
	"FKLINK = $(FKLIB_G)" \
	"SAMPLE = $(SAMPLEAPPS)" \
	"POSTLINK = ../FK/appmake.pl"

CFLAGS = $(OPS) $(SYSOPS) $(INCLDIRS)

target : $(SAMPLE)

clean:
	$(RM) $(SAMPLE) $(SAMPLEEXE) Makefile.bak \
		$(SAMPLESRCS:cxx=obj) $(SAMPLESRCS:cxx=tds) \
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
