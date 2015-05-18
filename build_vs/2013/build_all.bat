@echo off
echo --- Create FK Package ---

::  VS2013Ç÷ÇÃÉpÉXÇê›íË
set VS12_DEVENV_PATH=%VS120COMNTOOLS%..\IDE\devenv.exe

echo Cleaning...

"%VS12_DEVENV_PATH%" FK.sln /Clean "Debug|Win32"
"%VS12_DEVENV_PATH%" FK.sln /Clean "Debug|x64"
"%VS12_DEVENV_PATH%" FK.sln /Clean "Release|Win32"
"%VS12_DEVENV_PATH%" FK.sln /Clean "Release|x64"

"%VS12_DEVENV_PATH%" ..\extlibs\fltk-1.3.2\ide\VisualC2013\fltk.sln /Clean "Debug|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\fltk-1.3.2\ide\VisualC2013\fltk.sln /Clean "Debug|x64"
"%VS12_DEVENV_PATH%" ..\extlibs\fltk-1.3.2\ide\VisualC2013\fltk.slnn /Clean "Release|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\fltk-1.3.2\ide\VisualC2013\fltk.sln /Clean "Release|x64"

"%VS12_DEVENV_PATH%" ..\extlibs\freetype-2.5.3\builds\windows\vc2013\freetype.sln /Clean "Debug Multithreaded|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\freetype-2.5.3\builds\windows\vc2013\freetype.sln /Clean "Debug Multithreaded|x64"
"%VS12_DEVENV_PATH%" ..\extlibs\freetype-2.5.3\builds\windows\vc2013\freetype.sln /Clean "Release Multithreaded|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\freetype-2.5.3\builds\windows\vc2013\freetype.sln /Clean "Release Multithreaded|x64"

"%VS12_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2013.sln /Clean "DebugStatic|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2013.sln /Clean "DebugStatic|x64"
"%VS12_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2013.sln /Clean "ReleaseStatic|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2013.sln /Clean "ReleaseStatic|x64"

"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\libogg_dynamic.sln /Clean "Debug|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\libogg_dynamic.sln /Clean "Debug|x64"
"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\libogg_dynamic.sln /Clean "Release|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\libogg_dynamic.sln /Clean "Release|x64"

"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\vorbis_dynamic.sln /Clean "Debug|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\vorbis_dynamic.sln /Clean "Debug|x64"
"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\vorbis_dynamic.sln /Clean "Release|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\vorbis_dynamic.sln /Clean "Release|x64"

echo Build started!

"%VS12_DEVENV_PATH%" FK.sln /Build "Debug|Win32"
"%VS12_DEVENV_PATH%" FK.sln /Build "Debug|x64"
"%VS12_DEVENV_PATH%" FK.sln /Build "Release|Win32"
"%VS12_DEVENV_PATH%" FK.sln /Build "Release|x64"

"%VS12_DEVENV_PATH%" ..\extlibs\fltk-1.3.2\ide\VisualC2013\fltk.sln /Build "Debug|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\fltk-1.3.2\ide\VisualC2013\fltk.sln /Build "Debug|x64"
"%VS12_DEVENV_PATH%" ..\extlibs\fltk-1.3.2\ide\VisualC2013\fltk.slnn /Build "Release|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\fltk-1.3.2\ide\VisualC2013\fltk.sln /Build "Release|x64"

"%VS12_DEVENV_PATH%" ..\extlibs\freetype-2.5.3\builds\windows\vc2013\freetype.sln /Build "Debug Multithreaded|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\freetype-2.5.3\builds\windows\vc2013\freetype.sln /Build "Debug Multithreaded|x64"
"%VS12_DEVENV_PATH%" ..\extlibs\freetype-2.5.3\builds\windows\vc2013\freetype.sln /Build "Release Multithreaded|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\freetype-2.5.3\builds\windows\vc2013\freetype.sln /Build "Release Multithreaded|x64"

"%VS12_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2013.sln /Build "DebugStatic|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2013.sln /Build "DebugStatic|x64"
"%VS12_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2013.sln /Build "ReleaseStatic|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libiconv\LibIconv_2013.sln /Build "ReleaseStatic|x64"

"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\libogg_dynamic.sln /Build "Debug|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\libogg_dynamic.sln /Build "Debug|x64"
"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\libogg_dynamic.sln /Build "Release|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\libogg_dynamic.sln /Build "Release|x64"

"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\vorbis_dynamic.sln /Build "Debug|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\vorbis_dynamic.sln /Build "Debug|x64"
"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\vorbis_dynamic.sln /Build "Release|Win32"
"%VS12_DEVENV_PATH%" ..\extlibs\libogg\win32\VS2013\vorbis_dynamic.sln /Build "Release|x64"

echo Copying...

echo Done!
