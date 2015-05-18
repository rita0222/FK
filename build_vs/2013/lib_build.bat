@echo off
echo --- Build solutions ---

::  VS2013へのパスを設定
set VS12_DEVENV_PATH=%VS120COMNTOOLS%..\IDE\devenv.exe

echo FK
"%VS12_DEVENV_PATH%" FK.sln /Build "Debug|Win32"
"%VS12_DEVENV_PATH%" FK.sln /Build "Debug|x64"
"%VS12_DEVENV_PATH%" FK.sln /Build "Release|Win32"
"%VS12_DEVENV_PATH%" FK.sln /Build "Release|x64"

echo FLTK
"%VS12_DEVENV_PATH%" ..\extlibs\fltk-1.3.2\ide\VisualC2013\fltk.sln /Build "Debug|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\fltk-1.3.2\ide\VisualC2013\fltk.sln /Build "Debug|x64"
"%VS12_DEVENV_PATH%" ..\extlibs\fltk-1.3.2\ide\VisualC2013\fltk.sln /Build "Release|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\fltk-1.3.2\ide\VisualC2013\fltk.sln /Build "Release|x64"

echo freetype
"%VS12_DEVENV_PATH%" ..\extlibs\freetype-2.5.3\builds\windows\vc2013\freetype.sln /Build "Debug Multithreaded|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\freetype-2.5.3\builds\windows\vc2013\freetype.sln /Build "Debug Multithreaded|x64"
"%VS12_DEVENV_PATH%" ..\extlibs\freetype-2.5.3\builds\windows\vc2013\freetype.sln /Build "Release Multithreaded|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\freetype-2.5.3\builds\windows\vc2013\freetype.sln /Build "Release Multithreaded|x64"

echo libiconv
"%VS12_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2013.sln /Build "DebugStatic|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2013.sln /Build "DebugStatic|x64"
"%VS12_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2013.sln /Build "ReleaseStatic|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2013.sln /Build "ReleaseStatic|x64"

echo ogg
"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\libogg_dynamic.sln /Build "Release|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\libogg_dynamic.sln /Build "Release|x64"

echo vorbis
"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\vorbis_dynamic.sln /Build "Release|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\vorbis_dynamic.sln /Build "Release|x64"

echo Done!
