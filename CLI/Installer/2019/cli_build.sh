#!/bin/sh

source ./vsenv.sh

"$VS16_DEVENV_PATH" ..\\..\\2019\\FK_CLI_Build_2019.sln /Build "Release|x86"
#"$VS16_DEVENV_PATH" ..\\FK_CLI_Build_2019.sln /Build "Debug|x86"
"$VS16_DEVENV_PATH" ..\\..\\2019\\FK_CLI_Build_2019.sln /Build "Release|x64"
#"$VS16_DEVENV_PATH" ..\\FK_CLI_Build_2019.sln /Build "Debug|x64"