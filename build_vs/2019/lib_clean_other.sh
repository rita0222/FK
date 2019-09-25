#!/bin/sh

source ./vsenv.sh

# FLTK
"$VS16_DEVENV_PATH" ..\\extlibs\\fltk-1.3.5\\ide\\VisualC2017\\fltk.sln /Clean "Release|Win32"
"$VS16_DEVENV_PATH" ..\\extlibs\\fltk-1.3.5\\ide\\VisualC2017\\fltk.sln /Clean "Debug|Win32"
"$VS16_DEVENV_PATH" ..\\extlibs\\fltk-1.3.5\\ide\\VisualC2017\\fltk.sln /Clean "Release|x64"
"$VS16_DEVENV_PATH" ..\\extlibs\\fltk-1.3.5\\ide\\VisualC2017\\fltk.sln /Clean "Debug|x64"

# freetype
"$VS16_DEVENV_PATH" ..\\extlibs\\freetype-2.10.0\\builds\\windows\\vc2017\\freetype.sln /Clean "Release Static|Win32"
"$VS16_DEVENV_PATH" ..\\extlibs\\freetype-2.10.0\\builds\\windows\\vc2017\\freetype.sln /Clean "Debug Static|Win32"
"$VS16_DEVENV_PATH" ..\\extlibs\\freetype-2.10.0\\builds\\windows\\vc2017\\freetype.sln /Clean "Release Static|x64"
"$VS16_DEVENV_PATH" ..\\extlibs\\freetype-2.10.0\\builds\\windows\\vc2017\\freetype.sln /Clean "Debug Static|x64"

# libiconv
"$VS16_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2017.sln /Clean "ReleaseStatic|Win32"
"$VS16_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2017.sln /Clean "DebugStatic|Win32"
"$VS16_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2017.sln /Clean "ReleaseStatic|x64"
"$VS16_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2017.sln /Clean "DebugStatic|x64"

# ogg
"$VS16_DEVENV_PATH" ..\\extlibs\\libogg-1.3.3\\win32\\VS2017\\libogg_static.sln /Clean "Release|Win32"
"$VS16_DEVENV_PATH" ..\\extlibs\\libogg-1.3.3\\win32\\VS2017\\libogg_static.sln /Clean "Debug|Win32"
"$VS16_DEVENV_PATH" ..\\extlibs\\libogg-1.3.3\\win32\\VS2017\\libogg_static.sln /Clean "Release|x64"
"$VS16_DEVENV_PATH" ..\\extlibs\\libogg-1.3.3\\win32\\VS2017\\libogg_static.sln /Clean "Debug|x64"

# vorbis
"$VS16_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.6\\win32\\VS2017\\vorbis_static.sln /Clean "Release|Win32"
"$VS16_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.6\\win32\\VS2017\\vorbis_static.sln /Clean "Debug|Win32"
"$VS16_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.6\\win32\\VS2017\\vorbis_static.sln /Clean "Release|x64"
"$VS16_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.6\\win32\\VS2017\\vorbis_static.sln /Clean "Debug|x64"
