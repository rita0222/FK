#!/bin/sh

source ./vsenv.sh

## FK

"$VS15_DEVENV_PATH" FK.sln /Build "Release|Win32"
"$VS15_DEVENV_PATH" FK.sln /Build "Debug|Win32"
"$VS15_DEVENV_PATH" FK.sln /Build "Release|x64"
"$VS15_DEVENV_PATH" FK.sln /Build "Debug|x64"
