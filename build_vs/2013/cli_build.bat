@echo off
echo --- Build solutions ---

::  VS2013Ç÷ÇÃÉpÉXÇê›íË
set VS12_DEVENV_PATH=%VS120COMNTOOLS%..\IDE\devenv

:: cli
"%VS12_DEVENV_PATH%" ..\..\CLI\FK_CLI_Build.sln /Build "Release|Mixed Platforms"

echo Done!
