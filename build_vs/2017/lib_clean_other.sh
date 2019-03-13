#!/bin/sh

source ./vsenv.sh

# FLTK
"$VS15_DEVENV_PATH" ..\\extlibs\\fltk-1.3.5\\ide\\VisualC2017\\fltk.sln /Clean "Release|x64"
#"$VS15_DEVENV_PATH" ..\\extlibs\\fltk-1.3.5\\ide\\VisualC2017\\fltk.sln /Clean "Debug|x64"

# freetype
"$VS15_DEVENV_PATH" ..\\extlibs\\freetype-2.6\\builds\\windows\\vc2017\\freetype.sln /Clean "Release Multithreaded|x64"
#"$VS15_DEVENV_PATH" ..\\extlibs\\freetype-2.6\\builds\\windows\\vc2017\\freetype.sln /Clean "Debug Multithreaded|x64"

# libiconv
"$VS15_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2017.sln /Clean "ReleaseStatic|x64"
#"$VS15_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2017.sln /Clean "DebugStatic|x64"

# ogg
"$VS15_DEVENV_PATH" ..\\extlibs\\libogg-1.3.2\\win32\\VS2017\\libogg_static.sln /Clean "Release|x64"
#"$VS15_DEVENV_PATH" ..\\extlibs\\libogg-1.3.2\\win32\\VS2017\\libogg_static.sln /Clean "Debug|x64"

# vorbis
"$VS15_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.5\\win32\\VS2017\\vorbis_static.sln /Clean "Release|x64"
#"$VS15_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.5\\win32\\VS2017\\vorbis_static.sln /Clean "Debug|x64"
