#!/bin/sh

FKPATH="../Installer/FK_VC17"
FK32R="$FKPATH/lib/Win32/release"
FK32D="$FKPATH/lib/Win32/debug"
FK64R="$FKPATH/lib/x64/release"
FK64D="$FKPATH/lib/x64/debug"

rm -rf $FKPATH

mkdir -p $FKPATH/bin
mkdir -p $FKPATH/doc
mkdir -p $FKPATH/include
mkdir -p $FKPATH/lib
mkdir -p $FK32R
mkdir -p $FK32D
mkdir -p $FK64R
mkdir -p $FK64D
mkdir -p $FKPATH/redist

# for FK
cp lib/Win32/Release/*.lib $FK32R
cp lib/Win32/Debug/*.lib $FK32D
cp lib/x64/Release/*.lib $FK64R
cp lib/x64/Debug/*.lib $FK64D

# for FLTK
cp ../extlibs/fltk-1.3.5/lib/win32/release/*.lib $FK32R
cp ../extlibs/fltk-1.3.5/lib/win32/debug/*.lib $FK32D
cp ../extlibs/fltk-1.3.5/lib/x64/release/*.lib $FK64R
cp ../extlibs/fltk-1.3.5/lib/x64/debug/*.lib $FK64D

# for freetype
cp ../extlibs/freetype-2.10.0/lib/Win32/Release\ Static/freetype.lib $FK32R/freetype.lib
cp ../extlibs/freetype-2.10.0/lib/Win32/Debug\ Static/freetype.lib $FK32D/freetype_d.lib
cp ../extlibs/freetype-2.10.0/lib/x64/Release\ Static/freetype.lib $FK64R/freetype.lib
cp ../extlibs/freetype-2.10.0/lib/x64/Debug\ Static/freetype.lib $FK64D/freetype_d.lib

# for iconv
cp ../extlibs/libiconv/output/Win32/ReleaseStatic/libiconv.lib $FK32R
cp ../extlibs/libiconv/output/Win32/DebugStatic/libiconv_d.lib $FK32D
cp ../extlibs/libiconv/output/x64/ReleaseStatic/libiconv.lib $FK64R
cp ../extlibs/libiconv/output/x64/DebugStatic/libiconv_d.lib $FK64D

# for ogg
cp ../extlibs/libogg-1.3.3/lib/Win32/Release/*.lib $FK32R
cp ../extlibs/libogg-1.3.3/lib/Win32/Debug/*.lib $FK32D
cp ../extlibs/libogg-1.3.3/lib/x64/Release/*.lib $FK64R
cp ../extlibs/libogg-1.3.3/lib/x64/Debug/*.lib $FK64D


# for vorbis
cp ../extlibs/libvorbis-1.3.6/output/Win32/Release/*.lib $FK32R
cp ../extlibs/libvorbis-1.3.6/output/Win32/Debug/*.lib $FK32D
cp ../extlibs/libvorbis-1.3.6/output/x64/Release/*.lib $FK64R
cp ../extlibs/libvorbis-1.3.6/output/x64/Debug/*.lib $FK64D

# for OpenAL
cp ../extlibs/OpenAL/lib/*.lib $FK32R
cp ../extlibs/OpenAL/lib/*.lib $FK32D
cp ../extlibs/OpenAL/lib_x64/*.lib $FK64R
cp ../extlibs/OpenAL/lib_x64/*.lib $FK64D

# for glew
cp ../extlibs/glew-2.1.0/lib/Release/Win32/*.lib $FK32R
cp ../extlibs/glew-2.1.0/lib/Release/Win32/*.lib $FK32D
cp ../extlibs/glew-2.1.0/lib/Release/x64/*.lib $FK64R
cp ../extlibs/glew-2.1.0/lib/Release/x64/*.lib $FK64D
cp ../extlibs/glew-2.1.0/bin/Release/x64/glew32.dll $FKPATH/bin
cp ../extlibs/glew-2.1.0/bin/Release/x64/glewinfo.exe $FKPATH/bin
cp ../extlibs/glew-2.1.0/bin/Release/x64/visualinfo.exe $FKPATH/bin


mkdir $FKPATH/include/FK
cp ../../FK/*.[h,H] $FKPATH/include/FK

mkdir $FKPATH/include/FL
cp ../extlibs/fltk-1.3.5/FL/*.[h,H] $FKPATH/include/FL

mkdir $FKPATH/include/GL
cp ../extlibs/glew-2.1.0/include/GL/*.h $FKPATH/include/GL

cp ../extlibs/OpenAL/redist/*.exe $FKPATH/redist

mkdir $FKPATH/doc/glew
cp ../extlibs/glew-2.1.0/LICENSE.txt $FKPATH/doc/glew
cp ../doc/License.txt $FKPATH/doc
cp ../doc/RelativeLibraries.txt $FKPATH/doc
cp ../doc/Version_2017.txt $FKPATH/doc/Version.txt
