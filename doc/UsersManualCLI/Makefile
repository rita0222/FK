SHELL	= /bin/sh

RM		= rm -f
MAINNAME	= FK_UsersManual

doc:
	cd Fig; ../../com/svg2eps *.svg
	platex $(MAINNAME); platex $(MAINNAME); platex $(MAINNAME)
	dvipdfmx -d 5 $(MAINNAME)
	cp $(MAINNAME).pdf ../Output

clean:
	$(RM) *.dvi *.log *.aux *.toc *.out *.lof *.lot *.bbl *.blg *.pdf *~
	cd Fig; $(RM) *.eps

####################
