SHELL	= /bin/sh

RM	= rm -f

doc:
	latexmk FK_Setup_Mac
	latexmk FK_Setup_VC
	latexmk FK_Setup_VS_CLI
	cp *.pdf ../Output

clean:
	$(RM) *.dvi *.log *.aux *.toc *.out *.lof *.lot *.bbl \
		*.blg *.fls *.fdb_latexmk *.synctex.gz *.pdf *~

####################
