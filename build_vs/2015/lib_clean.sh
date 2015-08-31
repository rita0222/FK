#!/bin/sh

# VS2015へのパスを設定
export VS14_DEVENV_PATH=$VS140COMNTOOLS/../IDE/devenv

# FK
"$VS14_DEVENV_PATH" FK.sln /Clean "Debug|Win32"
"$VS14_DEVENV_PATH" FK.sln /Clean "Debug|x64"
"$VS14_DEVENV_PATH" FK.sln /Clean "Release|Win32"
"$VS14_DEVENV_PATH" FK.sln /Clean "Release|x64"

# FLTK
"$VS14_DEVENV_PATH" ..\\extlibs\\fltk-1.3.3\\ide\\VisualC2015\\fltk.sln /Clean "Debug|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\fltk-1.3.3\\ide\\VisualC2015\\fltk.sln /Clean "Debug|x64"
"$VS14_DEVENV_PATH" ..\\extlibs\\fltk-1.3.3\\ide\\VisualC2015\\fltk.sln /Clean "Release|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\fltk-1.3.3\\ide\\VisualC2015\\fltk.sln /Clean "Release|x64"

# freetype
"$VS14_DEVENV_PATH" ..\\extlibs\\freetype-2.6\\builds\\windows\\vc2015\\freetype.sln /Clean "Debug Multithreaded|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\freetype-2.6\\builds\\windows\\vc2015\\freetype.sln /Clean "Debug Multithreaded|x64"
"$VS14_DEVENV_PATH" ..\\extlibs\\freetype-2.6\\builds\\windows\\vc2015\\freetype.sln /Clean "Release Multithreaded|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\freetype-2.6\\builds\\windows\\vc2015\\freetype.sln /Clean "Release Multithreaded|x64"

# libiconv
"$VS14_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2015.sln /Clean "DebugStatic|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2015.sln /Clean "DebugStatic|x64"
"$VS14_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2015.sln /Clean "ReleaseStatic|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2015.sln /Clean "ReleaseStatic|x64"

# ogg
"$VS14_DEVENV_PATH" ..\\extlibs\\libogg-1.3.2\\win32\\VS2015\\libogg_static.sln /Clean "Debug|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\libogg-1.3.2\\win32\\VS2015\\libogg_static.sln /Clean "Debug|x64"
"$VS14_DEVENV_PATH" ..\\extlibs\\libogg-1.3.2\\win32\\VS2015\\libogg_static.sln /Clean "Release|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\libogg-1.3.2\\win32\\VS2015\\libogg_static.sln /Clean "Release|x64"

# vorbis
"$VS14_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.5\\win32\\VS2015\\vorbis_static.sln /Clean "Release|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.5\\win32\\VS2015\\vorbis_static.sln /Clean "Release|x64"
"$VS14_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.5\\win32\\VS2015\\vorbis_static.sln /Clean "Release|Win32"
"$VS14_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.5\\win32\\VS2015\\vorbis_static.sln /Clean "Release|x64"
