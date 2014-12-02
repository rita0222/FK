SHELL	= /bin/sh

RM			= rm -rf
MAKE			= make
QMAKE			= qmake
QT_BOX_PRO		= Box.pro
QT_BOX_PRO_G		= Box_g.pro
QT_BALL_PRO		= Ball.pro
QT_BALL_PRO_G		= Ball_g.pro
QT_TEXTIMAGE_PRO	= TextImage.pro
QT_TEXTIMAGE_PRO_G	= TextImage_g.pro

all:
	@echo "	Release:		make release"
	@echo "	Debug:			make debug"
	@echo "	Mac-Release:		make mac-qt"
	@echo "	Mac-Debug:		make mac-qt-g"
	@echo "	Clean:			make clean"
	@echo "	Mac-Clean:		make clean-mac"

release:
	cd box; $(QMAKE) $(QT_BOX_PRO); make
	cd ball; $(QMAKE) $(QT_BALL_PRO); make
	cd textimage; $(QMAKE) $(QT_TEXTIMAGE_PRO); make

debug:
	cd box; $(QMAKE) $(QT_BOX_PRO_G); make
	cd ball; $(QMAKE) $(QT_BALL_PRO_G); make
	cd textimage; $(QMAKE) $(QT_TEXTIMAGE_PRO_G); make

mac-qt:
	cd box; $(QMAKE) -spec macx-g++ $(QT_BOX_PRO); make
	cd ball; $(QMAKE) -spec macx-g++ $(QT_BALL_PRO); make
	cd textimage; $(QMAKE) -spec macx-g++ $(QT_TEXTIMAGE_PRO); make

mac-qt-g:
	cd box; $(QMAKE) -spec macx-g++ $(QT_BOX_PRO_G); make
	cd ball; $(QMAKE) -spec macx-g++ $(QT_BALL_PRO_G); make
	cd textimage; $(QMAKE) -spec macx-g++ $(QT_TEXTIMAGE_PRO_G); make

clean:
	cd box; $(QMAKE) $(QT_BOX_PRO); $(MAKE) distclean
	cd box; $(RM) Makefile.* *.o debug release *~
	cd ball; $(QMAKE) $(QT_BALL_PRO); $(MAKE) distclean
	cd ball; $(RM) Makefile.* *.o debug release *~
	cd textimage; $(QMAKE) $(QT_TEXTIMAGE_PRO); $(MAKE) distclean
	cd textimage; $(RM) Makefile.* *.o debug release *~

clean-mac:
	cd box; $(QMAKE) -spec macx-g++ $(QT_BOX_PRO); $(MAKE) distclean
	cd box; $(RM) Makefile.* *.o debug release *~
	cd ball; $(QMAKE) -spec macx-g++ $(QT_BALL_PRO); $(MAKE) distclean
	cd ball; $(RM) Makefile.* *.o debug release *~
	cd textimage; $(QMAKE) -spec macx-g++ $(QT_TEXTIMAGE_PRO); $(MAKE) distclean
	cd textimage; $(RM) Makefile.* *.o debug release *~

####################
