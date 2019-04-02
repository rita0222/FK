#!/bin/sh

source ./vsenv.sh

# FLTK
"$VS15_DEVENV_PATH" ..\\extlibs\\fltk-1.3.5\\ide\\VisualC2017\\fltk.sln /Build "Release|Win32"
"$VS15_DEVENV_PATH" ..\\extlibs\\fltk-1.3.5\\ide\\VisualC2017\\fltk.sln /Build "Debug|Win32"
"$VS15_DEVENV_PATH" ..\\extlibs\\fltk-1.3.5\\ide\\VisualC2017\\fltk.sln /Build "Release|x64"
"$VS15_DEVENV_PATH" ..\\extlibs\\fltk-1.3.5\\ide\\VisualC2017\\fltk.sln /Build "Debug|x64"

# freetype
"$VS15_DEVENV_PATH" ..\\extlibs\\freetype-2.10.0\\builds\\windows\\vc2017\\freetype.sln /Build "Release Static|Win32"
"$VS15_DEVENV_PATH" ..\\extlibs\\freetype-2.10.0\\builds\\windows\\vc2017\\freetype.sln /Build "Debug Static|Win32"
"$VS15_DEVENV_PATH" ..\\extlibs\\freetype-2.10.0\\builds\\windows\\vc2017\\freetype.sln /Build "Release Static|x64"
"$VS15_DEVENV_PATH" ..\\extlibs\\freetype-2.10.0\\builds\\windows\\vc2017\\freetype.sln /Build "Debug Static|x64"

# libiconv
"$VS15_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2017.sln /Build "ReleaseStatic|Win32"
"$VS15_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2017.sln /Build "DebugStatic|Win32"
"$VS15_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2017.sln /Build "ReleaseStatic|x64"
"$VS15_DEVENV_PATH" ..\\extlibs\\libiconv\\LibIconv_2017.sln /Build "DebugStatic|x64"

# ogg
"$VS15_DEVENV_PATH" ..\\extlibs\\libogg-1.3.3\\win32\\VS2017\\libogg_static.sln /Build "Release|Win32"
"$VS15_DEVENV_PATH" ..\\extlibs\\libogg-1.3.3\\win32\\VS2017\\libogg_static.sln /Build "Debug|Win32"
"$VS15_DEVENV_PATH" ..\\extlibs\\libogg-1.3.3\\win32\\VS2017\\libogg_static.sln /Build "Release|x64"
"$VS15_DEVENV_PATH" ..\\extlibs\\libogg-1.3.3\\win32\\VS2017\\libogg_static.sln /Build "Debug|x64"

# vorbis
"$VS15_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.6\\win32\\VS2017\\vorbis_static.sln /Build "Release|Win32"
"$VS15_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.6\\win32\\VS2017\\vorbis_static.sln /Build "Debug|Win32"
"$VS15_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.6\\win32\\VS2017\\vorbis_static.sln /Build "Release|x64"
"$VS15_DEVENV_PATH" ..\\extlibs\\libvorbis-1.3.6\\win32\\VS2017\\vorbis_static.sln /Build "Debug|x64"

# glew
"$VS15_DEVENV_PATH" ..\\extlibs\\glew-2.1.0\\build\\vc12\\glew.sln /Build "Release|Win32"
"$VS15_DEVENV_PATH" ..\\extlibs\\glew-2.1.0\\build\\vc12\\glew.sln /Build "Debug|Win32"
"$VS15_DEVENV_PATH" ..\\extlibs\\glew-2.1.0\\build\\vc12\\glew.sln /Build "Release|x64"
"$VS15_DEVENV_PATH" ..\\extlibs\\glew-2.1.0\\build\\vc12\\glew.sln /Build "Debug|x64"
