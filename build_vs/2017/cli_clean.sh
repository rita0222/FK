#!/bin/sh

source ./vsenv.sh

"$VS15_DEVENV_PATH" ..\\..\\CLI\\FK_CLI_Build_2017.sln /Clean "Release|x86"
"$VS15_DEVENV_PATH" ..\\..\\CLI\\FK_CLI_Build_2017.sln /Clean "Debug|x86"
"$VS15_DEVENV_PATH" ..\\..\\CLI\\FK_CLI_Build_2017.sln /Clean "Release|x64"
"$VS15_DEVENV_PATH" ..\\..\\CLI\\FK_CLI_Build_2017.sln /Clean "Debug|x64"

echo "Done!"
