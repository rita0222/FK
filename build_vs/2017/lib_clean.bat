@echo off
echo --- Clean solutions ---

::  VS2017Ç÷ÇÃÉpÉXÇê›íË
FOR /f "DELIMS=" %%A IN ('vswhere -format value -property installationPath') DO SET VS150COMNTOOLS=%%A
set VS15_DEVENV_PATH=%VS150COMNTOOLS%\Common7\IDE\devenv

:: FK
"%VS15_DEVENV_PATH%" FK.sln /Clean "Debug|x86"
"%VS15_DEVENV_PATH%" FK.sln /Clean "Debug|x64"
"%VS15_DEVENV_PATH%" FK.sln /Clean "Release|x86"
"%VS15_DEVENV_PATH%" FK.sln /Clean "Release|x64"

:: FLTK
"%VS15_DEVENV_PATH%" ..\extlibs\fltk-1.3.3\ide\VisualC2017\fltk.sln /Clean "Debug|x86"
"%VS15_DEVENV_PATH%" ..\extlibs\fltk-1.3.3\ide\VisualC2017\fltk.sln /Clean "Debug|x64"
"%VS15_DEVENV_PATH%" ..\extlibs\fltk-1.3.3\ide\VisualC2017\fltk.sln /Clean "Release|x86"
"%VS15_DEVENV_PATH%" ..\extlibs\fltk-1.3.3\ide\VisualC2017\fltk.sln /Clean "Release|x64"

:: freetype
"%VS15_DEVENV_PATH%" ..\extlibs\freetype-2.6\builds\windows\vc2017\freetype.sln /Clean "Debug Multithreaded|x86"
"%VS15_DEVENV_PATH%" ..\extlibs\freetype-2.6\builds\windows\vc2017\freetype.sln /Clean "Debug Multithreaded|x64"
"%VS15_DEVENV_PATH%" ..\extlibs\freetype-2.6\builds\windows\vc2017\freetype.sln /Clean "Release Multithreaded|x86"
"%VS15_DEVENV_PATH%" ..\extlibs\freetype-2.6\builds\windows\vc2017\freetype.sln /Clean "Release Multithreaded|x64"

:: libiconv
"%VS15_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2017.sln /Clean "DebugStatic|x86"
"%VS15_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2017.sln /Clean "DebugStatic|x64"
"%VS15_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2017.sln /Clean "ReleaseStatic|x86"
"%VS15_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2017.sln /Clean "ReleaseStatic|x64"

:: ogg
"%VS15_DEVENV_PATH%" ..\extlibs\libogg-1.3.2\win32\VS2017\libogg_static.sln /Clean "Debug|x86"
"%VS15_DEVENV_PATH%" ..\extlibs\libogg-1.3.2\win32\VS2017\libogg_static.sln /Clean "Debug|x64"
"%VS15_DEVENV_PATH%" ..\extlibs\libogg-1.3.2\win32\VS2017\libogg_static.sln /Clean "Release|x86"
"%VS15_DEVENV_PATH%" ..\extlibs\libogg-1.3.2\win32\VS2017\libogg_static.sln /Clean "Release|x64"

:: vorbis
"%VS15_DEVENV_PATH%" ..\extlibs\libvorbis-1.3.5\win32\VS2017\vorbis_static.sln /Clean "Debug|x86"
"%VS15_DEVENV_PATH%" ..\extlibs\libvorbis-1.3.5\win32\VS2017\vorbis_static.sln /Clean "Debug|x64"
"%VS15_DEVENV_PATH%" ..\extlibs\libvorbis-1.3.5\win32\VS2017\vorbis_static.sln /Clean "Release|x86"
"%VS15_DEVENV_PATH%" ..\extlibs\libvorbis-1.3.5\win32\VS2017\vorbis_static.sln /Clean "Release|x64"

echo Done!
