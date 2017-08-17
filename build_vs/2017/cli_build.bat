@echo off
echo --- Build solutions ---

::  VS2015Ç÷ÇÃÉpÉXÇê›íË
set VS14_DEVENV_PATH=%VS140COMNTOOLS%..\IDE\devenv

:: cli
"%VS14_DEVENV_PATH%" ..\..\CLI\FK_CLI_Build_2015.sln /Build "Release|Mixed Platforms"

echo Done!
