SHELL	= /bin/sh

RM		= rm -rf
BASECONFFILE	= user_ref.conf
CLICONFFILE	= CLI_ref.conf
BASEREFDIR	= html_user
CLIREFDIR	= html_CLI

doc:
	cd Fig; ../../com/svg2png *.svg; ../../com/svg2eps *.svg
	doxygen $(BASECONFFILE)
	doxygen $(CLICONFFILE)
	cp -r $(BASEREFDIR) ../Output/FK_Reference
	cp -r $(CLIREFDIR) ../Output/FK_Reference

clean:
	$(RM) $(BASEREFDIR) $(CLIREFDIR) *~
	cd Fig; $(RM) *.eps *.png

####################
