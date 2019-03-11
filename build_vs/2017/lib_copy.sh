#!/bin/sh

rm -rf ../FK_VC17

mkdir ../FK_VC17
mkdir ../FK_VC17/bin
#mkdir ../FK_VC17/bin_x64
mkdir ../FK_VC17/doc
mkdir ../FK_VC17/include
mkdir ../FK_VC17/lib
#mkdir ../FK_VC17/lib_x64
mkdir ../FK_VC17/redist

cp lib_x64/*.lib ../FK_VC17/lib
cp ../extlibs/fltk-1.3.5/lib/*.lib ../FK_VC17/lib
mv ../FK_VC17/lib/fltkzlib.lib ../FK_VC17/lib/fltkz.lib
cp ../extlibs/freetype-2.6/objs/vc2017/x64/freetype26MT.lib ../FK_VC17/lib/freetype2MT.lib
cp ../extlibs/libiconv/ReleaseStatic_x64/libiconv_2017Static.lib ../FK_VC17/lib/libiconv.lib
cp ../extlibs/libogg-1.3.2/win32/VS2017/bin/x64/Release/libogg_static.lib ../FK_VC17/lib/libogg.lib
cp ../extlibs/libvorbis-1.3.5/win32/VS2017/bin/x64/Release/libvorbis_static.lib ../FK_VC17/lib/libvorbis.lib
cp ../extlibs/libvorbis-1.3.5/win32/VS2017/bin/x64/Release/libvorbisfile_static.lib ../FK_VC17/lib/libvorbisfile.lib
cp ../extlibs/OpenAL/lib_x64/*.lib ../FK_VC17/lib
cp ../extlibs/glew-2.1.0/lib/Release/x64/*.lib ../FK_VC17/lib
cp ../extlibs/glew-2.1.0/bin/Release/x64/*.* ../FK_VC17/bin

mkdir ../FK_VC17/include/FK
cp ../../FK/*.[h,H] ../FK_VC17/include/FK

mkdir ../FK_VC17/include/FL
cp ../extlibs/fltk-1.3.5/FL/*.[h,H] ../FK_VC17/include/FL

mkdir ../FK_VC17/include/GL
cp ../extlibs/glew-2.1.0/include/GL/*.h ../FK_VC17/include/GL

cp ../extlibs/OpenAL/redist/*.exe ../FK_VC17/redist

mkdir ../FK_VC17/doc/glew
cp ../extlibs/glew-2.1.0/LICENSE.txt ../FK_VC17/doc/glew
cp ../doc/License.txt ../FK_VC17/doc
cp ../doc/RelativeLibraries.txt ../FK_VC17/doc
cp ../doc/Version_2017.txt ../FK_VC17/doc/Version.txt

cp -r vs_wizard ../FK_VC17
