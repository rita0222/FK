SHELL	= /bin/sh

RM		= rm -rf
BASECONFFILE	= user_ref.conf
CLICONFFILE	= CLI_ref.conf
BASEREFDIR	= html_user
CLIREFDIR	= html_CLI
BASECOPYDIR	= ../Output/FK_Ref_Base
CLICOPYDIR	= ../Output/FK_Ref_CLI

doc:
	cd Fig; $(MAKE) doc
	doxygen $(BASECONFFILE)
	doxygen $(CLICONFFILE)
	rm -rf $(BASECOPYDIR)
	rm -rf $(CLICOPYDIR)
	cp -r $(BASEREFDIR) $(BASECOPYDIR)
	cp -r $(CLIREFDIR) $(CLICOPYDIR)

clean:
	$(RM) $(BASEREFDIR) $(CLIREFDIR) *~
	cd Fig; $(MAKE) clean

####################
