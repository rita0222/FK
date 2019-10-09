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

VERNAME		= 4.1.0

###################

FKLIB_S		= \
			-lFK4_util \
			-lFK4_window \
			-lFK4_graphics \
			-lFK4_scene \
			-lFK4_model \
			-lFK4_shape \
			-lFK4_material \
			-lFK4_math \
			-lFK4_base \

FKLIB_SG		= \
			-lFK4_util_g \
			-lFK4_window_g \
			-lFK4_graphics_g \
			-lFK4_scene_g \
			-lFK4_model_g \
			-lFK4_shape_g \
			-lFK4_material_g \
			-lFK4_math_g \
			-lFK4_base_g \

FKLIB_D		= \
			-lFK4_util.$(VERNAME) \
			-lFK4_window.$(VERNAME) \
			-lFK4_graphics.$(VERNAME) \
			-lFK4_scene.$(VERNAME) \
			-lFK4_model.$(VERNAME) \
			-lFK4_shape.$(VERNAME) \
			-lFK4_material.$(VERNAME) \
			-lFK4_math.$(VERNAME) \
			-lFK4_base.$(VERNAME) \

FKLIB_DG		= \
			-lFK4_util_g.$(VERNAME) \
			-lFK4_window_g.$(VERNAME) \
			-lFK4_graphics_g.$(VERNAME) \
			-lFK4_scene_g.$(VERNAME) \
			-lFK4_model_g.$(VERNAME) \
			-lFK4_shape_g.$(VERNAME) \
			-lFK4_material_g.$(VERNAME) \
			-lFK4_math_g.$(VERNAME) \
			-lFK4_base_g.$(VERNAME) \

FKAUDIO_S	= -lFK4_audio
FKAUDIO_SG	= -lFK4_audio_g
FKAUDIO_D	= -lFK4_audio.$(VERNAME)
FKAUDIO_DG	= -lFK4_audio_g.$(VERNAME)

FKOPENCL_S	= -lFK4_OpenCL
FKOPENCL_SG	= -lFK4_OpenCL_g
FKOPENCL_D	= -lFK4_OpenCL.$(VERNAME)
FKOPENCL_DG	= -lFK4_OpenCL_g.$(VERNAME)

FKSHADER_S	= -lFK4_shader
FKSHADER_SG	= -lFK4_shader_g
FKSHADER_D	= -lFK4_shader.$(VERNAME)
FKSHADER_DG	= -lFK4_shader_g.$(VERNAME)

FKAR_S		= -lFK4_AR
FKAR_SG		= -lFK4_AR_g
FKAR_D		= -lFK4_AR.$(VERNAME)
FKAR_DG		= -lFK4_AR_g.$(VERNAME)

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
	"FKLINK = $(FKOPENCL_S) $(FKAUDIO_S) $(FKLIB_S) $(FKSHADER_S)"

mac:
	$(MAKE) $(TARGET) \
	"OPTOPT = -O -pipe" \
	"SYSOPS = -D_MACOSX_" \
	"INCLDIRS = -I. -I.. -I$(MACINCLUDE)" \
	"LFLAGS = -L../lib/static -L$(MACSYSLIB_S) -L/opt/local/lib" \
	"SYSLIBS = \
		-liconv \
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
	"FKLINK = $(FKOPENCL_S) $(FKAUDIO_S) $(FKSHADER_S) $(FKLIB_S)" \
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
