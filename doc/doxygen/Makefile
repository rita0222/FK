SHELL	= /bin/sh

RM		= rm -rf
CONFFILE	= user_ref.conf
REFDIR		= html_user

doc:
	cd Fig; ../../com/svg2png *.svg; ../../com/svg2eps *.svg
	doxygen $(CONFFILE)
	cp -r $(REFDIR) ../Output/FK_Reference

clean:
	$(RM) $(REFDIR) *~
	cd Fig; $(RM) *.eps *.png

####################
