SHELL	= /bin/sh

RM		= rm -f
MAINNAME	= FK_Tutorial

doc:
	latexmk $(MAINNAME)
	cp $(MAINNAME).pdf ../Output

clean:
	$(RM) *.dvi *.log *.aux *.toc *.out *.lof *.lot *.bbl \
		*.blg *.fls *.fdb_latexmk *.synctex.gz *.pdf *~

####################
