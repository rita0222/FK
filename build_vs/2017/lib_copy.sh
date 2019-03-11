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

cp lib/*.lib ../FK_VC17/lib
cp ../extlibs/fltk-1.3.5/ide/VisualC2017/bin/x64/*.lib ../FK_VC17/lib_x64
mv ../FK_VC17/lib_x64/fltkzlib.lib ../FK_VC17/lib_x64/fltkz.lib
mv ../FK_VC17/lib_x64/fltkzlib_d.lib ../FK_VC17/lib_x64/fltkz_d.lib
cp ../extlibs/freetype-2.6/objs/vc2017/x64/freetype26MT.lib ../FK_VC17/lib_x64/freetype2MT.lib
cp ../extlibs/freetype-2.6/objs/vc2017/x64/freetype26MTd.lib ../FK_VC17/lib_x64/freetype2MT_d.lib
cp ../extlibs/libiconv/ReleaseStatic_x64/libiconv_2017Static.lib ../FK_VC17/lib_x64/libiconv.lib
cp ../extlibs/libiconv/DebugStatic_x64/libiconv_2017StaticD.lib ../FK_VC17/lib_x64/libiconv_d.lib
cp ../extlibs/libogg-1.3.2/win32/VS2017/bin/x64/Release/libogg_static.lib ../FK_VC17/lib_x64/libogg.lib
cp ../extlibs/libogg-1.3.2/win32/VS2017/bin/x64/Debug/libogg_static.lib ../FK_VC17/lib_x64/libogg_d.lib
cp ../extlibs/libvorbis-1.3.5/win32/VS2017/bin/x64/Release/libvorbis_static.lib ../FK_VC17/lib_x64/libvorbis.lib
cp ../extlibs/libvorbis-1.3.5/win32/VS2017/bin/x64/Debug/libvorbis_static.lib ../FK_VC17/lib_x64/libvorbis_d.lib
cp ../extlibs/libvorbis-1.3.5/win32/VS2017/bin/x64/Release/libvorbisfile_static.lib ../FK_VC17/lib_x64/libvorbisfile.lib
cp ../extlibs/libvorbis-1.3.5/win32/VS2017/bin/x64/Debug/libvorbisfile_static.lib ../FK_VC17/lib_x64/libvorbisfile_d.lib
cp ../extlibs/DirectInput/lib_x64/*.lib ../FK_VC17/lib_x64
cp ../extlibs/OpenAL/lib_x64/*.lib ../FK_VC17/lib_x64
cp ../extlibs/ARToolKit/lib_x64/*.lib ../FK_VC17/lib_x64
cp ../extlibs/ARToolKit/lib_x64/*.dll ../FK_VC17/bin_x64
cp ../extlibs/glew-1.12.0/lib/Release/x64/*.lib ../FK_VC17/lib_x64
cp ../extlibs/glew-1.12.0/bin/Release/x64/*.* ../FK_VC17/bin_x64

mkdir ../FK_VC17/include/FK
cp ../../FK/*.[h,H] ../FK_VC17/include/FK

mkdir ../FK_VC17/include/FL
cp ../extlibs/fltk-1.3.3/FL/*.[h,H] ../FK_VC17/include/FL

mkdir ../FK_VC17/include/DX
cp ../extlibs/DirectInput/include/DX/*.h ../FK_VC17/include/DX

mkdir ../FK_VC17/include/GL
cp ../extlibs/glew-1.12.0/include/GL/*.h ../FK_VC17/include/GL

cp -r ../extlibs/ARToolKit/include/AR ../FK_VC17/include

cp ../extlibs/OpenAL/redist/*.exe ../FK_VC17/redist

mkdir ../FK_VC17/doc/glew
cp ../extlibs/glew-1.12.0/LICENSE.txt ../FK_VC17/doc/glew
cp ../doc/JapaneseStringInFLTK.txt ../FK_VC17/doc
cp ../doc/License.txt ../FK_VC17/doc
cp ../doc/RelativeLibraries.txt ../FK_VC17/doc
cp ../doc/Version_2017.txt ../FK_VC17/doc/Version.txt

cp -r vs_wizard ../FK_VC17
