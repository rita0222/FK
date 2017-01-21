@echo off
echo --- Clean solutions ---

::  VS2013Ç÷ÇÃÉpÉXÇê›íË
set VS12_DEVENV_PATH=%VS120COMNTOOLS%..\IDE\devenv

:: cli
"%VS12_DEVENV_PATH%" ..\..\CLI\FK_CLI_Build.sln /Clean "Release|Mixed Platforms"

rd /s /q ..\FK_CLI

echo Done!
