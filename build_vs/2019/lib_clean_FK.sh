#!/bin/sh

source ./vsenv.sh

# FK
"$VS15_DEVENV_PATH" FK.sln /Clean "Release|Win32"
"$VS15_DEVENV_PATH" FK.sln /Clean "Debug|Win32"
"$VS15_DEVENV_PATH" FK.sln /Clean "Release|x64"
"$VS15_DEVENV_PATH" FK.sln /Clean "Debug|x64"
