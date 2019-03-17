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

cp lib_x64/*.lib $FKPATH/lib

# for FLTK
cp ../extlibs/fltk-1.3.5/lib/release/*.lib $FKPATH/lib/release
cp ../extlibs/fltk-1.3.5/lib/debug/*.lib $FKPATH/lib/debug

# for freetype
cp ../extlibs/freetype-2.6/objs/vc2017/x64/freetype26MT.lib $FKPATH/lib/freetype2MT.lib


cp ../extlibs/libiconv/ReleaseStatic_x64/libiconv_2017Static.lib $FKPATH/lib/libiconv.lib
cp ../extlibs/libogg-1.3.2/win32/VS2017/bin/x64/Release/libogg_static.lib $FKPATH/lib/libogg.lib
cp ../extlibs/libvorbis-1.3.5/win32/VS2017/bin/x64/Release/libvorbis_static.lib $FKPATH/lib/libvorbis.lib
cp ../extlibs/libvorbis-1.3.5/win32/VS2017/bin/x64/Release/libvorbisfile_static.lib $FKPATH/lib/libvorbisfile.lib
cp ../extlibs/OpenAL/lib_x64/*.lib $FKPATH/lib
cp ../extlibs/glew-2.1.0/lib/Release/x64/*.lib $FKPATH/lib
cp ../extlibs/glew-2.1.0/bin/Release/x64/*.* $FKPATH/bin

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
