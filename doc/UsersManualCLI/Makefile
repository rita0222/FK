SHELL	= /bin/sh

RM		= rm -f
MAINNAME	= FK_UsersManual_CLI

doc:
	cd Fig; ../../com/svg2eps -i *.svg
	latexmk $(MAINNAME)
	cp $(MAINNAME).pdf ../Output

clean:
	$(RM) *.dvi *.log *.aux *.toc *.out *.lof *.lot *.bbl \
		*.blg *.fls *.fdb_latexmk *.synctex.gz *.pdf *~
	cd Fig; $(RM) *.eps

####################
