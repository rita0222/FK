TEMPLATE	=	app
DEPENDPATH	+=	.
INCLUDEPATH	+= 	. \
			../.. \
                        ../../../include

LIBS		+=	-L../../lib -L../../../lib \
			-lFK2_QtWin_g \
			-lFK2_base_g \
			-lFK2_QtError_g \
			-lfreetype -limdkcv -ljpeg -lpng -lbz2 -lz

QT		+=	opengl
CONFIG		+=	qt debug

macx {
	LIBS		+=	-lz
	DEFINES		+=	_MACOSX_
#	CONFIG		+=	x86
}

win32 {
	QMAKE_MOC	=	moc.exe
	QMAKE_DIR_SEP	=	/
	QMAKE_COPY	=	cp
	QMAKE_COPY_DIR	=	xcopy /s /q /y /i
	QMAKE_MOVE	=	mv
	QMAKE_DEL_FILE	=	rm -f
	QMAKE_MKDIR	=	mkdir
	QMAKE_DEL_DIR	=	rmdir
        DEFINES		+=	WIN32 _MINGW_
	LIBS		+=	-L../../../FK_Ming/lib \
				-lglu32 -lopengl32 -lfltk_png -lfltk_z
}
