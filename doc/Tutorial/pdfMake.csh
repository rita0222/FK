#!/bin/csh

dvipdfmx -d 5 -s 2-8 -o FK_Tutorial-01.pdf FK_Tutorial.dvi
dvipdfmx -d 5 -s 9-12 -o FK_Tutorial-02.pdf FK_Tutorial.dvi
dvipdfmx -d 5 -s 13-19 -o FK_Tutorial-03.pdf FK_Tutorial.dvi
dvipdfmx -d 5 -s 20-23 -o FK_Tutorial-04.pdf FK_Tutorial.dvi
dvipdfmx -d 5 -s 24-27 -o FK_Tutorial-05.pdf FK_Tutorial.dvi
dvipdfmx -d 5 -s 28-33 -o FK_Tutorial-06.pdf FK_Tutorial.dvi
dvipdfmx -d 5 -s 34-37 -o FK_Tutorial-07.pdf FK_Tutorial.dvi
dvipdfmx -d 5 -s 38-42 -o FK_Tutorial-08.pdf FK_Tutorial.dvi
dvipdfmx -d 5 -s 43-47 -o FK_Tutorial-09.pdf FK_Tutorial.dvi
dvipdfmx -d 5 -s 48-52 -o FK_Tutorial-10.pdf FK_Tutorial.dvi

mv *.pdf PDF
