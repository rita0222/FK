TEMPLATE	=	lib
DESTDIR		=	../../../lib
CONFIG		+= 	staticlib qt release
QT		+=	opengl
DEPENDPATH	+=	.
INCLUDEPATH	+=	. \
			../../..

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
}

macx {
	DEFINES		+=	_MACOSX_
}

unix {
	DEFINES		+=	NO_GLU_LIBRARY
}
