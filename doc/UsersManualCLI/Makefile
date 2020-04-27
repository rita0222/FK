SHELL	= /bin/sh

RM		= rm -f
MAINNAME	= FK_UsersManual_CLI

doc:
	../com/svg2eps ./Fig/*.svg
	latexmk $(MAINNAME)
	cp $(MAINNAME).pdf ../Output

clean:
	touch tmp.dvi
	$(RM) *.dvi *.log *.aux *.toc *.out *.lof *.lot *.bbl \
		*.blg *.fls *.fdb_latexmk *.synctex.gz *.pdf *~ \
		./Fig/*.eps

####################
