#!/bin/sh

source ./vsenv.sh

# VS2015へのパスを設定
export VS14_DEVENV_PATH=$VS140COMNTOOLS/../IDE/devenv

# FK
"$VS14_DEVENV_PATH" FK.sln /Build "Debug|Win32"
"$VS14_DEVENV_PATH" FK.sln /Build "Debug|x64"
"$VS14_DEVENV_PATH" FK.sln /Build "Release|Win32"
"$VS14_DEVENV_PATH" FK.sln /Build "Release|x64"

# FLTK
"$VS14_DEVENV_PATH" ..\\extlibs\\fltk-1.3.3\\ide\\VisualC2015\\fltk.sln /Build "Debug|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\fltk-1.3.3\\ide\\VisualC2015\\fltk.sln /Build "Debug|x64"
"$VS14_DEVENV_PATH" ..\\extlibs\\fltk-1.3.3\\ide\\VisualC2015\\fltk.sln /Build "Release|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\fltk-1.3.3\\ide\\VisualC2015\\fltk.sln /Build "Release|x64"

# freetype
"$VS14_DEVENV_PATH" ..\\extlibs\\freetype-2.6\\builds\\windows\\vc2015\\freetype.sln /Build "Debug Multithreaded|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\freetype-2.6\\builds\\windows\\vc2015\\freetype.sln /Build "Debug Multithreaded|x64"
"$VS14_DEVENV_PATH" ..\\extlibs\\freetype-2.6\\builds\\windows\\vc2015\\freetype.sln /Build "Release Multithreaded|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\freetype-2.6\\builds\\windows\\vc2015\\freetype.sln /Build "Release Multithreaded|x64"

# libiconv
"$VS14_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2015.sln /Build "DebugStatic|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2015.sln /Build "DebugStatic|x64"
"$VS14_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2015.sln /Build "ReleaseStatic|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2015.sln /Build "ReleaseStatic|x64"

# ogg
"$VS14_DEVENV_PATH" ..\\extlibs\\libogg-1.3.2\\win32\\VS2015\\libogg_static.sln /Build "Debug|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\libogg-1.3.2\\win32\\VS2015\\libogg_static.sln /Build "Debug|x64"
"$VS14_DEVENV_PATH" ..\\extlibs\\libogg-1.3.2\\win32\\VS2015\\libogg_static.sln /Build "Release|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\libogg-1.3.2\\win32\\VS2015\\libogg_static.sln /Build "Release|x64"

# vorbis
"$VS14_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.5\\win32\\VS2015\\vorbis_static.sln /Build "Debug|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.5\\win32\\VS2015\\vorbis_static.sln /Build "Debug|x64"
"$VS14_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.5\\win32\\VS2015\\vorbis_static.sln /Build "Release|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.5\\win32\\VS2015\\vorbis_static.sln /Build "Release|x64"
