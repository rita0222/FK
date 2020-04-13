#!/bin/sh

SRCDIR="../../../src"
SCRIPTDIR="../../../FK"

find $SRCDIR -name \*.out -exec rm {} \;
$SCRIPTDIR/glsl2out
