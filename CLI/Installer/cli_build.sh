#!/bin/sh

source ./vsenv.sh

"$VS15_DEVENV_PATH" ..\\FK_CLI_Build_2017.sln /Build "Release|x86"
#"$VS15_DEVENV_PATH" ..\\FK_CLI_Build_2017.sln /Build "Debug|x86"
"$VS15_DEVENV_PATH" ..\\FK_CLI_Build_2017.sln /Build "Release|x64"
#"$VS15_DEVENV_PATH" ..\\FK_CLI_Build_2017.sln /Build "Debug|x64"