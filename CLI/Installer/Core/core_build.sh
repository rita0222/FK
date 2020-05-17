#!/bin/sh

source ./vsenv.sh

"$VS16_DEVENV_PATH" ..\\..\\Core2019\\FK_Core_Build.sln /Build "Release|x86"
# "$VS16_DEVENV_PATH" ..\\..\\Core2019\\FK_Core_Build.sln /Build "Debug|x86"
"$VS16_DEVENV_PATH" ..\\..\\Core2019\\FK_Core_Build.sln /Build "Release|x64"
# "$VS16_DEVENV_PATH" ..\\..\\Core2019\\FK_Core_Build.sln /Build "Debug|x64"
