@echo off
echo --- Clean solutions ---

::  VS2015へのパスを設定
set VS14_DEVENV_PATH=%VS140COMNTOOLS%..\IDE\devenv

:: cli
"%VS14_DEVENV_PATH%" ..\..\CLI\FK_CLI_Build_2015.sln /Clean "Release|Mixed Platforms"

echo Done!
