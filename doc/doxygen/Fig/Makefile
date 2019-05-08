SHELL	= /bin/sh
RM	= rm -f

SVGFILE	= $(wildcard *.svg)
PNGFILE = $(SVGFILE:.svg=.png)
EPSFILE = $(SVGFILE:.svg=.eps)

clean:
	$(RM) *.eps *.png

doc: $(PNGFILE) $(EPSFILE)

%.png : %.svg
	../../com/svg2png $<

%.eps : %.svg
	../../com/svg2eps $<

####################
