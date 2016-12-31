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

SAMPLESRCS	= $(shell /usr/bin/find . -maxdepth 1 -name "*.cxx" -print)

SAMPLE		= $(SAMPLESRCS:.cxx=)
SAMPLEEXE	= $(SAMPLESRCS:cxx=exe)
SAMPLEAPPS	= $(SAMPLESRCS:cxx=app)
ALLSRCS		= $(SAMPLESRCS)

VERNAME		= 3.1.1

###################

FKLIB_S		= \
			-lFK3_util \
			-lFK3_window \
			-lFK3_graphics \
			-lFK3_scene \
			-lFK3_model \
			-lFK3_shape \
			-lFK3_material \
			-lFK3_math \
			-lFK3_base \

FKLIB_SG		= \
			-lFK3_util_g \
			-lFK3_window_g \
			-lFK3_graphics_g \
			-lFK3_scene_g \
			-lFK3_model_g \
			-lFK3_shape_g \
			-lFK3_material_g \
			-lFK3_math_g \
			-lFK3_base_g \

FKLIB_D		= \
			-lFK3_util.$(VERNAME) \
			-lFK3_window.$(VERNAME) \
			-lFK3_graphics.$(VERNAME) \
			-lFK3_scene.$(VERNAME) \
			-lFK3_model.$(VERNAME) \
			-lFK3_shape.$(VERNAME) \
			-lFK3_material.$(VERNAME) \
			-lFK3_math.$(VERNAME) \
			-lFK3_base.$(VERNAME) \

FKLIB_SG		= \
			-lFK3_util_g.$(VERNAME) \
			-lFK3_window_g.$(VERNAME) \
			-lFK3_graphics_g.$(VERNAME) \
			-lFK3_scene_g.$(VERNAME) \
			-lFK3_model_g.$(VERNAME) \
			-lFK3_shape_g.$(VERNAME) \
			-lFK3_material_g.$(VERNAME) \
			-lFK3_math_g.$(VERNAME) \
			-lFK3_base_g.$(VERNAME) \

FKAUDIO_S	= -lFK3_audio
FKAUDIO_SG	= -lFK3_audio_g
FKAUDIO_D	= -lFK3_audio.$(VERNAME)
FKAUDIO_DG	= -lFK3_audio_g.$(VERNAME)

FKOPENCL_S	= -lFK3_OpenCL
FKOPENCL_SG	= -lFK3_OpenCL_g
FKOPENCL_D	= -lFK3_OpenCL.$(VERNAME)
FKOPENCL_DG	= -lFK3_OpenCL_g.$(VERNAME)

FKSHADER_S	= -lFK3_shader
FKSHADER_SG	= -lFK3_shader_g
FKSHADER_D	= -lFK3_shader.$(VERNAME)
FKSHADER_DG	= -lFK3_shader_g.$(VERNAME)

FKLINK		= $(FKLIB_S)
LINK		= $(FKLINK) $(SYSLIBS)
TARGET		= target
OUTPUT		= -o $*

FKTOP		= ..
MACPACK		= $(FKTOP)/../FK_MacPack
MACINCLUDE	= $(MACPACK)/include
MACSYSLIB_S	= $(MACPACK)/lib/static
MACSYSLIB_D	= $(MACPACK)/lib/dynamic


all:
	@echo "	FreeBSD:		make fb"
	@echo "	FreeBSD Debug:		make fb-g"
	@echo "	Linux:			make linux"
	@echo "	MingW:			make ming"
	@echo "	MacOS X:		make mac"
	@echo "	MacOS X Dynamic:	make mac-d"
	@echo "	MacOS X Debug:		make mac-g"
	@echo "	MacOS X gcc:		make mac-gcc"
	@echo "	MacOS X gcc Debug:	make mac-gcc-g"

fb:
	$(MAKE) $(TARGET) \
	"OPTOPT = -O -pipe" \
	"GRAMOPT = -pedantic -std=c++1y" \
	"SYSOPS = -D_FREEBSD_ -DNO_GLU_LIBRARY -DGL_GLEXT_PROTOTYPES \
		-DHAVE_NANOSLEEP -DHAVE_TIME_H" \
	"INCLDIRS = -I. -I.. -I../../FK_BSDPack/include -I$(LOCAL)/include" \
	"LFLAGS = -L../lib/static -L../../FK_BSDPack/lib -L$(LOCAL)/lib" \
	"SYSLIBS = -liconv -lopenal -lvorbisfile -lvorbis -logg \
		-lfltk_gl -lfltk \
		-ljpeg -lpng \
		-lfreetype -lGL \
		-lXft -lfontconfig -lXinerama -lpthread \
		-lXext -lX11 -lz -lbz2 -lm" \
	"FKLINK = $(FKAUDIO_S) $(FKSHADER_S) $(FKLIB_S)"

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
	"FKLINK = $(FKLIB_S) $(FKLIB_S)"

mac:
	$(MAKE) $(TARGET) \
	"OPTOPT = -O -pipe" \
	"SYSOPS = -D_MACOSX_" \
	"INCLDIRS = -I. -I.. -I$(MACINCLUDE)" \
	"LFLAGS = -L../lib/static -L$(MACSYSLIB_S) -L/opt/local/lib" \
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
	"FKLINK = $(FKAUDIO_S) $(FKSHADER_S) $(FKLIB_S)" \
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
	"FKLINK = $(FKAUDIO_D) $(FKSHADER_D) $(FKLIB_D)" \
	"SAMPLE = $(SAMPLEAPPS)" \
	"POSTLINK = ../FK/appmake.pl"

mac-g:
	$(MAKE) $(TARGET) \
	"OPTOPT = -g" \
	"SYSOPS = -D_MACOSX_" \
	"INCLDIRS = -I. -I.. -I$(MACINCLUDE)" \
	"LFLAGS = -L../lib/static -L$(MACSYSLIB_S)" \
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
	"FKLINK = $(FKLIB_SG)" \
	"SAMPLE = $(SAMPLEAPPS)" \
	"POSTLINK = ../FK/appmake.pl"

mac-gcc:
	$(MAKE) $(TARGET) \
	"CC = g++-mp-6" \
	"LINKCC = g++-mp-6" \
	"OPTOPT = -O -pipe" \
	"SYSOPS = -D_MACOSX_" \
	"INCLDIRS = -I. -I.. -I$(MACINCLUDE)" \
	"LFLAGS = -L../lib/static -L$(MACSYSLIB_S)" \
	"SYSLIBS = -liconv -lfltk_gl -lfltk \
		-lvorbisfile -lvorbis -logg \
		-lpng  -ljpeg -lfreetype -lz -lbz2 \
		-framework AGL -framework OpenGL \
		-framework Cocoa -framework OpenAL \
		-framework ApplicationServices \
		-framework Foundation \
		-framework AudioToolBox" \
	"RANLIB = ranlib" \
	"FKLINK = $(FKLIB_S)" \
	"SAMPLE = $(SAMPLEAPPS)" \
	"POSTLINK = ../FK/appmake.pl"

mac-gcc-g:
	$(MAKE) $(TARGET) \
	"CC = g++-mp-6" \
	"LINKCC = g++-mp-6" \
	"OPTOPT = -g" \
	"SYSOPS = -D_MACOSX_" \
	"INCLDIRS = -I. -I.. -I$(MACINCLUDE)" \
	"LFLAGS = -L../lib/static -L$(MACSYSLIB_S)" \
	"SYSLIBS = -liconv -lfltk_gl -lfltk \
		-lvorbisfile -lvorbis -logg \
		-lpng  -ljpeg -lfreetype -lz -lbz2 \
		-framework AGL -framework OpenGL \
		-framework Cocoa -framework OpenAL \
		-framework ApplicationServices \
		-framework Foundation \
		-framework AudioToolBox" \
	"RANLIB = ranlib" \
	"FKLINK = $(FKLIB_SG)" \
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
	cp -r ../lib/dynamic $*.app/Contents/MacOS/lib
	cp $(MACSYSLIB_D)/*.dylib $*.app/Contents/MacOS/lib

.cxx :
	$(CC) $(CFLAGS) $(LFLAGS) $< $(OUTPUT) $(LINK)

####################
