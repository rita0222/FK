SHELL	= /bin/sh

RM	= rm -f

doc:
	platex FK_Setup_Ming; platex FK_Setup_Ming; platex FK_Setup_Ming; dvipdfmx -d 5 FK_Setup_Ming
	platex FK_Setup_Mac; platex FK_Setup_Mac; platex FK_Setup_Mac; dvipdfmx -d 5 FK_Setup_Mac
	platex FK_Setup_VC; platex FK_Setup_VC; platex FK_Setup_VC; dvipdfmx -d 5 FK_Setup_VC
	cp *.pdf ../Output

clean:
	$(RM) *.dvi *.log *.aux *.toc *.out *.lof *.lot *.bbl *.blg *.pdf *~

####################
