#!/bin/sh

source ./vsenv.sh

# FK
"$VS15_DEVENV_PATH" FK.sln /Clean "Release|x64"

#"$VS15_DEVENV_PATH" FK.sln /Clean "Debug|x86"
#"$VS15_DEVENV_PATH" FK.sln /Clean "Debug|x64"
#"$VS15_DEVENV_PATH" FK.sln /Clean "Release|x86"
