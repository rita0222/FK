#!/bin/sh

source ./vsenv.sh

## FK

# "$VS16_DEVENV_PATH" FK.sln /Build "Release|Win32"
# "$VS16_DEVENV_PATH" FK.sln /Build "Debug|Win32"
"$VS16_DEVENV_PATH" FK.sln /Build "Release|x64"
"$VS16_DEVENV_PATH" FK.sln /Build "Debug|x64"
