#!/bin/sh

source ./vsenv.sh

# FK
# "$VS16_DEVENV_PATH" FK.sln /Clean "Release|Win32"
# "$VS16_DEVENV_PATH" FK.sln /Clean "Debug|Win32"
"$VS16_DEVENV_PATH" FK.sln /Clean "Release|x64"
"$VS16_DEVENV_PATH" FK.sln /Clean "Debug|x64"
