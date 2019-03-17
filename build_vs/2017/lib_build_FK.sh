#!/bin/sh

source ./vsenv.sh

## FK

pushd ../../src/shader/GLSL
./glsl2out *.glsl
popd
pushd ../../src/graphics/GLSL
./glsl2out *.glsl
popd

"$VS15_DEVENV_PATH" FK.sln /Build "Release|x64"
"$VS15_DEVENV_PATH" FK.sln /Build "Debug|x64"
#"$VS15_DEVENV_PATH" FK.sln /Build "Debug|x86"
#"$VS15_DEVENV_PATH" FK.sln /Build "Release|x86"
