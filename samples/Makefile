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
GRAMOPT		= -pedantic -std=c++14
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
			-lFK3_audio.3.1 \
			-lFK3_util.3.1 \
			-lFK3_window.3.1 \
			-lFK3_graphics.3.1 \
			-lFK3_scene.3.1 \
			-lFK3_model.3.1 \
			-lFK3_shape.3.1 \
			-lFK3_material.3.1 \
			-lFK3_math.3.1 \
			-lFK3_base.3.1 \

FKLIB_G		= \
			-lFK3_audio_g \
			-lFK3_util_g \
			-lFK3_window_g \
			-lFK3_graphics_g \
			-lFK3_scene_g \
			-lFK3_model_g \
			-lFK3_shape_g \
			-lFK3_material_g \
			-lFK3_math_g \
			-lFK3_base_g \

FKAUDIO		= -lFK3_audio.3.1
FKAUDIO_G	= -lFK3_audio_g
FKOPENCL	= -lFK3_OpenCL.3.1
FKOPENCL_G	= -lFK3_OpenCL_g
FKSHADER	= -lFK3_shader.3.1
FKSHADER_G	= -lFK3_shader_g

FKLINK		= $(FKLIB)
LINK		= $(FKLINK) $(SYSLIBS)
TARGET		= target
OUTPUT		= -o $*

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

fb:
	$(MAKE) $(TARGET) \
	"GRAMOPT = -pedantic -std=c++1y" \
	"SYSOPS = -D_FREEBSD_ -DNO_GLU_LIBRARY" \
	"INCLDIRS = -I. -I.. -I../../FK_BSDPack/include -I$(LOCAL)/include" \
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
	"GRAMOPT = -pedantic -std=c++1y" \
	"OPTOPT = -g" \
	"SYSOPS = -D_FREEBSD_ -DNO_GLU_LIBRARY" \
	"INCLDIRS = -I. -I.. -I../../FK_BSDPack/include -I$(LOCAL)/include" \
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

linux:
	$(MAKE) $(TARGET) \
	"GRAMOPT = -pedantic -std=c++14" \
	"SYSOPS = -D_LINUX_ -DNO_GLU_LIBRARY" \
	"INCLDIRS = -I. -I.. -I$(LOCAL)/include" \
	"LFLAGS = -L../lib -L../../lib -L$(LOCAL)/lib" \
	"SYSLIBS = -liconv \
		-lopenal -lvorbisfile -lvorbis -logg \
		-lfltk_images -lfltk_forms -lfltk_gl -lfltk \
		-ljpeg -lpng -lfreetype -lGL -lpthread \
		-lXext -lX11 -lz -lm" \
	"RANLIB = ranlib"

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
	"LFLAGS = -L../lib/dynamic -L../../FK_MacPack/lib -L$(OPTLOCAL)/lib" \
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
	"FKLINK = $(FKLIB)" \
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
	"FKLINK = $(FKLIB_G)" \
	"SAMPLE = $(SAMPLEAPPS)" \
	"POSTLINK = ../FK/appmake.pl"

mac-gcc:
	$(MAKE) $(TARGET) \
	"CC = g++-mp-6" \
	"LINKCC = g++-mp-6" \
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
	"CC = g++-mp-6" \
	"LINKCC = g++-mp-6" \
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
