SHELL	= /bin/sh
RM	= rm -f

SVGFILE	= $(wildcard *.svg)
PNGFILE = $(SVGFILE:.svg=.png)
EPSFILE = $(SVGFILE:.svg=.eps)

clean:
	$(RM) *.eps *.png

#doc: $(PNGFILE)
doc: $(PNGFILE) $(EPSFILE)

.SUFFIXES : .svg .png
.SUFFIXES : .svg .eps

%.png : %.svg
	../../com/svg2png -i 144 $<

%.eps : %.svg
	../../com/svg2eps $<

####################
