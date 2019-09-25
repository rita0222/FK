#!/bin/sh

SHADERDIR="../../../src/shader/GLSL"
GRAPHICSDIR="../../../src/graphics/GLSL"

touch $SHADERDIR/tmp.out
rm $SHADERDIR/*.out
$SHADERDIR/glsl2out $SHADERDIR/*.glsl

touch $GRAPHICSDIR/tmp.out
rm $GRAPHICSDIR/*.out
$GRAPHICSDIR/glsl2out $GRAPHICSDIR/*.glsl
