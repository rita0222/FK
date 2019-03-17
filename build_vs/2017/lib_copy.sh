#!/bin/sh

FKPATH="../Installer/FK_VC17"

rm -rf $FKPATH

mkdir $FKPATH
mkdir $FKPATH/bin
mkdir $FKPATH/doc
mkdir $FKPATH/include
mkdir $FKPATH/lib
mkdir $FKPATH/lib/release
mkdir $FKPATH/lib/debug
mkdir $FKPATH/redist

# for FK
cp lib/release/*.lib $FKPATH/lib/release
cp lib/debug/*.lib $FKPATH/lib/debug

# for FLTK
cp ../extlibs/fltk-1.3.5/lib/release/*.lib $FKPATH/lib/release
cp ../extlibs/fltk-1.3.5/lib/debug/*.lib $FKPATH/lib/debug

# for freetype
cp ../extlibs/freetype-2.10.0/lib/Release\ Static/freetype.lib $FKPATH/lib/release/freetype.lib
cp ../extlibs/freetype-2.10.0/lib/Debug\ Static/freetype.lib $FKPATH/lib/debug/freetype_d.lib

# for iconv
cp ../extlibs/libiconv/ReleaseStatic_x64/libiconv_2017Static.lib $FKPATH/lib/release/libiconv.lib
cp ../extlibs/libiconv/DebugStatic_x64/libiconv_2017StaticD.lib $FKPATH/lib/debug/libiconv_d.lib

# for ogg
cp ../extlibs/libogg-1.3.3/lib/release/libogg.lib $FKPATH/lib/release
cp ../extlibs/libogg-1.3.3/lib/debug/libogg_d.lib $FKPATH/lib/debug

# for vorbis
cp ../extlibs/libvorbis-1.3.6/lib/release/libvorbis_static.lib $FKPATH/lib/release/libvorbis.lib
cp ../extlibs/libvorbis-1.3.6/lib/release/libvorbisfile.lib $FKPATH/lib/release
cp ../extlibs/libvorbis-1.3.6/lib/debug/libvorbis_static_d.lib $FKPATH/lib/debug/libvorbis_d.lib
cp ../extlibs/libvorbis-1.3.6/lib/debug/libvorbisfile_d.lib $FKPATH/lib/debug

# for OpenAL
cp ../extlibs/OpenAL/lib_x64/OpenAL32.lib $FKPATH/lib/release
cp ../extlibs/OpenAL/lib_x64/OpenAL32.lib $FKPATH/lib/debug

# for glew
cp ../extlibs/glew-2.1.0/lib/Release/x64/*.lib $FKPATH/lib/release
cp ../extlibs/glew-2.1.0/lib/Release/x64/*.lib $FKPATH/lib/debug
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
