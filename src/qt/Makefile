SHELL	= /bin/sh

RM		= rm -f
MAKE		= make
QMAKE		= qmake
QT_WIN_PRO	= FK_QtWin.pro
QT_WIN_PRO_G	= FK_QtWin_g.pro
QT_ERROR_PRO	= FK_QtError.pro
QT_ERROR_PRO_G	= FK_QtError_g.pro

all:
	@echo "	Release:		make release"
	@echo "	Debug:			make debug"
	@echo "	Mac-Release:		make mac-qt"
	@echo "	Mac-Debug:		make mac-qt-g"
	@echo "	Clean:			make clean"
	@echo "	Mac Clean:		make clean-mac"

release:
	cd Window; $(QMAKE) $(QT_WIN_PRO); make
	cd Error; $(QMAKE) $(QT_ERROR_PRO); make

debug:
	cd Window; $(QMAKE) $(QT_WIN_PRO_G); make
	cd Error; $(QMAKE) $(QT_ERROR_PRO_G); make

mac-qt:
	cd Window; $(QMAKE) -spec macx-g++ $(QT_WIN_PRO); make
	cd Error; $(QMAKE) -spec macx-g++ $(QT_ERROR_PRO); make

mac-qt-g:
	cd Window; $(QMAKE) -spec macx-g++ $(QT_WIN_PRO_G); make
	cd Error; $(QMAKE) -spec macx-g++ $(QT_ERROR_PRO_G); make

clean:
	cd Window; $(QMAKE) $(QT_WIN_PRO); $(MAKE) distclean; $(RM) *.o
	cd Error; $(QMAKE) $(QT_ERROR_PRO); $(MAKE) distclean; $(RM) *.o

clean-mac:
	cd Window; $(QMAKE) -spec macx-g++ $(QT_WIN_PRO)
	cd Window; $(MAKE) distclean; $(RM) *.o
	cd Error; $(QMAKE) -spec macx-g++ $(QT_ERROR_PRO)
	cd Error; $(MAKE) distclean; $(RM) *.o

####################
