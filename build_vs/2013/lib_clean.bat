@echo off
echo --- Clean solutions ---

::  VS2013Ç÷ÇÃÉpÉXÇê›íË
set VS12_DEVENV_PATH=%VS120COMNTOOLS%..\IDE\devenv

:: FK
"%VS12_DEVENV_PATH%" FK.sln /Clean "Debug|Win32"
"%VS12_DEVENV_PATH%" FK.sln /Clean "Debug|x64"
"%VS12_DEVENV_PATH%" FK.sln /Clean "Release|Win32"
"%VS12_DEVENV_PATH%" FK.sln /Clean "Release|x64"

:: FLTK
"%VS12_DEVENV_PATH%" ..\extlibs\fltk-1.3.3\ide\VisualC2013\fltk.sln /Clean "Debug|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\fltk-1.3.3\ide\VisualC2013\fltk.sln /Clean "Debug|x64"
"%VS12_DEVENV_PATH%" ..\extlibs\fltk-1.3.3\ide\VisualC2013\fltk.sln /Clean "Release|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\fltk-1.3.3\ide\VisualC2013\fltk.sln /Clean "Release|x64"

:: freetype
"%VS12_DEVENV_PATH%" ..\extlibs\freetype-2.6\builds\windows\vc2013\freetype.sln /Clean "Debug Multithreaded|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\freetype-2.6\builds\windows\vc2013\freetype.sln /Clean "Debug Multithreaded|x64"
"%VS12_DEVENV_PATH%" ..\extlibs\freetype-2.6\builds\windows\vc2013\freetype.sln /Clean "Release Multithreaded|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\freetype-2.6\builds\windows\vc2013\freetype.sln /Clean "Release Multithreaded|x64"

:: libiconv
"%VS12_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2013.sln /Clean "DebugStatic|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2013.sln /Clean "DebugStatic|x64"
"%VS12_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2013.sln /Clean "ReleaseStatic|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2013.sln /Clean "ReleaseStatic|x64"

:: ogg
"%VS12_DEVENV_PATH%" ..\extlibs\libogg-1.3.2\win32\VS2013\libogg_static.sln /Clean "Debug|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libogg-1.3.2\win32\VS2013\libogg_static.sln /Clean "Debug|x64"
"%VS12_DEVENV_PATH%" ..\extlibs\libogg-1.3.2\win32\VS2013\libogg_static.sln /Clean "Release|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libogg-1.3.2\win32\VS2013\libogg_static.sln /Clean "Release|x64"

:: vorbis
"%VS12_DEVENV_PATH%" ..\extlibs\libvorbis-1.3.5\win32\VS2013\vorbis_static.sln /Clean "Debug|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libvorbis-1.3.5\win32\VS2013\vorbis_static.sln /Clean "Debug|x64"
"%VS12_DEVENV_PATH%" ..\extlibs\libvorbis-1.3.5\win32\VS2013\vorbis_static.sln /Clean "Release|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libvorbis-1.3.5\win32\VS2013\vorbis_static.sln /Clean "Release|x64"

echo Done!
