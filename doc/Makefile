SHELL	= /bin/sh

RM		= rm -f
CP		= cp

doc:
	cd UsersManual; $(MAKE) doc
	cd UsersManualCLI; $(MAKE) doc
	cd Tutorial; $(MAKE) doc
	cd Setup; $(MAKE) doc
	cd doxygen; $(MAKE) doc

clean:
	cd UsersManual; $(MAKE) clean
	cd UsersManualCLI; $(MAKE) clean
	cd Tutorial; $(MAKE) clean
	cd Setup; $(MAKE) clean
	cd doxygen; $(MAKE) clean

####################
