#!/bin/sh

source ./vsenv.sh

# VS2017へのパスを設定
#export VS15_DEVENV_PATH=$VS150COMNTOOLS/../IDE/devenv

# FLTK
"$VS15_DEVENV_PATH" ..\\extlibs\\fltk-1.3.3\\ide\\VisualC2017\\fltk.sln /Build "Debug|x86"
"$VS15_DEVENV_PATH" ..\\extlibs\\fltk-1.3.3\\ide\\VisualC2017\\fltk.sln /Build "Debug|x64"
"$VS15_DEVENV_PATH" ..\\extlibs\\fltk-1.3.3\\ide\\VisualC2017\\fltk.sln /Build "Release|x86"
"$VS15_DEVENV_PATH" ..\\extlibs\\fltk-1.3.3\\ide\\VisualC2017\\fltk.sln /Build "Release|x64"

# freetype
"$VS15_DEVENV_PATH" ..\\extlibs\\freetype-2.6\\builds\\windows\\vc2017\\freetype.sln /Build "Debug Multithreaded|x86"
"$VS15_DEVENV_PATH" ..\\extlibs\\freetype-2.6\\builds\\windows\\vc2017\\freetype.sln /Build "Debug Multithreaded|x64"
"$VS15_DEVENV_PATH" ..\\extlibs\\freetype-2.6\\builds\\windows\\vc2017\\freetype.sln /Build "Release Multithreaded|x86"
"$VS15_DEVENV_PATH" ..\\extlibs\\freetype-2.6\\builds\\windows\\vc2017\\freetype.sln /Build "Release Multithreaded|x64"

# libiconv
"$VS15_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2017.sln /Build "DebugStatic|x86"
"$VS15_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2017.sln /Build "DebugStatic|x64"
"$VS15_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2017.sln /Build "ReleaseStatic|x86"
"$VS15_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2017.sln /Build "ReleaseStatic|x64"

# ogg
"$VS15_DEVENV_PATH" ..\\extlibs\\libogg-1.3.2\\win32\\VS2017\\libogg_static.sln /Build "Debug|x86"
"$VS15_DEVENV_PATH" ..\\extlibs\\libogg-1.3.2\\win32\\VS2017\\libogg_static.sln /Build "Debug|x64"
"$VS15_DEVENV_PATH" ..\\extlibs\\libogg-1.3.2\\win32\\VS2017\\libogg_static.sln /Build "Release|x86"
"$VS15_DEVENV_PATH" ..\\extlibs\\libogg-1.3.2\\win32\\VS2017\\libogg_static.sln /Build "Release|x64"

# vorbis
"$VS15_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.5\\win32\\VS2017\\vorbis_static.sln /Build "Debug|x86"
"$VS15_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.5\\win32\\VS2017\\vorbis_static.sln /Build "Debug|x64"
"$VS15_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.5\\win32\\VS2017\\vorbis_static.sln /Build "Release|x86"
"$VS15_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.5\\win32\\VS2017\\vorbis_static.sln /Build "Release|x64"
