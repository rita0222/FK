#!/bin/sh

# VS2013へのパスを設定
export VS12_DEVENV_PATH=$VS120COMNTOOLS/../IDE/devenv

# FK
"$VS12_DEVENV_PATH" FK.sln /Build "Debug|Win32"
"$VS12_DEVENV_PATH" FK.sln /Build "Debug|x64"
"$VS12_DEVENV_PATH" FK.sln /Build "Release|Win32"
"$VS12_DEVENV_PATH" FK.sln /Build "Release|x64"

# FLTK
"$VS12_DEVENV_PATH" ..\\extlibs\\fltk-1.3.3\\ide\\VisualC2013\\fltk.sln /Build "Debug|Win32"
"$VS12_DEVENV_PATH" ..\\extlibs\\fltk-1.3.3\\ide\\VisualC2013\\fltk.sln /Build "Debug|x64"
"$VS12_DEVENV_PATH" ..\\extlibs\\fltk-1.3.3\\ide\\VisualC2013\\fltk.sln /Build "Release|Win32"
"$VS12_DEVENV_PATH" ..\\extlibs\\fltk-1.3.3\\ide\\VisualC2013\\fltk.sln /Build "Release|x64"

# freetype
"$VS12_DEVENV_PATH" ..\\extlibs\\freetype-2.6\\builds\\windows\\vc2013\\freetype.sln /Build "Debug Multithreaded|Win32"
"$VS12_DEVENV_PATH" ..\\extlibs\\freetype-2.6\\builds\\windows\\vc2013\\freetype.sln /Build "Debug Multithreaded|x64"
"$VS12_DEVENV_PATH" ..\\extlibs\\freetype-2.6\\builds\\windows\\vc2013\\freetype.sln /Build "Release Multithreaded|Win32"
"$VS12_DEVENV_PATH" ..\\extlibs\\freetype-2.6\\builds\\windows\\vc2013\\freetype.sln /Build "Release Multithreaded|x64"

# libiconv
"$VS12_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2013.sln /Build "DebugStatic|Win32"
"$VS12_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2013.sln /Build "DebugStatic|x64"
"$VS12_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2013.sln /Build "ReleaseStatic|Win32"
"$VS12_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2013.sln /Build "ReleaseStatic|x64"

# ogg
"%VS12_DEVENV_PATH%" ..\\extlibs\\libogg-1.3.2\\win32\\VS2013\\libogg_static.sln /Build "Debug|Win32"
"%VS12_DEVENV_PATH%" ..\\extlibs\\libogg-1.3.2\\win32\\VS2013\\libogg_static.sln /Build "Debug|x64"
"%VS12_DEVENV_PATH%" ..\\extlibs\\libogg-1.3.2\\win32\\VS2013\\libogg_static.sln /Build "Release|Win32"
"%VS12_DEVENV_PATH%" ..\\extlibs\\libogg-1.3.2\\win32\\VS2013\\libogg_static.sln /Build "Release|x64"

# vorbis
"%VS12_DEVENV_PATH%" ..\\extlibs\libvorbis-1.3.5\\win32\\VS2013\\vorbis_static.sln /Build "Debug|Win32"
"%VS12_DEVENV_PATH%" ..\\extlibs\libvorbis-1.3.5\\win32\\VS2013\\vorbis_static.sln /Build "Debug|x64"
"%VS12_DEVENV_PATH%" ..\\extlibs\libvorbis-1.3.5\\win32\\VS2013\\vorbis_static.sln /Build "Release|Win32"
"%VS12_DEVENV_PATH%" ..\\extlibs\libvorbis-1.3.5\\win32\\VS2013\\vorbis_static.sln /Build "Release|x64"
