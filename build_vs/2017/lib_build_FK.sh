#!/bin/sh

source ./vsenv.sh

# VS2017へのパスを設定
#export VS15_DEVENV_PATH=$VS150COMNTOOLS/../IDE/devenv

## FK
"$VS15_DEVENV_PATH" FK.sln /Build "Debug|x86"
"$VS15_DEVENV_PATH" FK.sln /Build "Debug|x64"
"$VS15_DEVENV_PATH" FK.sln /Build "Release|x86"
"$VS15_DEVENV_PATH" FK.sln /Build "Release|x64"
