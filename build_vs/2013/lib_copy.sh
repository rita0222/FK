#!/bin/sh

rm -rf ../FK_VC13

mkdir ../FK_VC13
mkdir ../FK_VC13/bin
mkdir ../FK_VC13/bin_x64
mkdir ../FK_VC13/doc
mkdir ../FK_VC13/include
mkdir ../FK_VC13/lib
mkdir ../FK_VC13/lib_x64
mkdir ../FK_VC13/redist
mkdir ../FK_VC13/vs_wizard

cp lib_Win32/*.lib                                       ../FK_VC13/lib
cp ../extlibs/fltk-1.3.2/ide/VisualC2013/lib_Win32/*.lib ../FK_VC13/lib
mv ../FK_VC13/lib/fltkzlib.lib ../FK_VC13/lib/fltkz.lib
mv ../FK_VC13/lib/fltkzlib_d.lib ../FK_VC13/lib/fltkzlib_d.lib/fltkz_d.lib
cp ../extlibs/freetype-2.5.3/objs/win32/vc2013/freetype253MT.lib     ../FK_VC13/lib/freetype2MT.lib
cp ../extlibs/freetype-2.5.3/objs/win32/vc2013/freetype253MT_D.lib   ../FK_VC13/lib/freetype2MT_d.lib
cp ../extlibs/libiconv/ReleaseStatic_Win32/libiconv_2013Static.lib   ../FK_VC13/lib/libiconv.lib
cp ../extlibs/libiconv/DebugStatic_Win32/libiconv_2013StaticD.lib    ../FK_VC13/lib/libiconv_d.lib
cp ../extlibs/libogg/win32/VS2013/Win32/Release/libogg.lib           ../FK_VC13/lib
cp ../extlibs/libogg/win32/VS2013/Win32/Release/libogg.dll           ../FK_VC13/bin
cp ../extlibs/libvorbis/win32/VS2013/Win32/Release/libvorbis.lib     ../FK_VC13/lib
cp ../extlibs/libvorbis/win32/VS2013/Win32/Release/libvorbis.dll     ../FK_VC13/bin
cp ../extlibs/libvorbis/win32/VS2013/Win32/Release/libvorbisfile.lib ../FK_VC13/lib
cp ../extlibs/libvorbis/win32/VS2013/Win32/Release/libvorbisfile.dll ../FK_VC13/bin
cp ../extlibs/DirectInput/lib/*.lib                                  ../FK_VC13/lib
cp ../extlibs/OpenAL/lib/*.lib                                       ../FK_VC13/lib
cp ../extlibs/GLEW/lib/*.lib                                         ../FK_VC13/lib
cp ../extlibs/GLEW/bin/*.dll                                         ../FK_VC13/bin
cp ../extlibs/GLEW/bin/*.exe                                         ../FK_VC13/bin

cp lib_x64/*.lib                                                     ../FK_VC13/lib_x64
cp ../extlibs/fltk-1.3.2/ide/VisualC2013/lib_x64/*.lib               ../FK_VC13/lib_x64
mv ../FK_VC13/lib_x64/fltkzlib.lib ../FK_VC13/lib_x64/fltkz.lib
mv ../FK_VC13/lib_x64/fltkzlib_d.lib ../FK_VC13/lib_x64/fltkz_d.lib
cp ../extlibs/freetype-2.5.3/objs/win64/vc2013/freetype253MT.lib     ../FK_VC13/lib_x64/freetype2MT.lib
cp ../extlibs/freetype-2.5.3/objs/win64/vc2013/freetype253MT_D.lib   ../FK_VC13/lib_x64/freetype2MT_d.lib
cp ../extlibs/libiconv/ReleaseStatic_x64/libiconv_2013Static.lib     ../FK_VC13/lib_x64/libiconv.lib
cp ../extlibs/libiconv/DebugStatic_x64/libiconv_2013StaticD.lib      ../FK_VC13/lib_x64/libiconv_d.lib
cp ../extlibs/libogg/win32/VS2013/x64/Release/libogg.lib             ../FK_VC13/lib_x64
cp ../extlibs/libogg/win32/VS2013/x64/Release/libogg.dll             ../FK_VC13/bin_x64
cp ../extlibs/libvorbis/win32/VS2013/x64/Release/libvorbis.lib       ../FK_VC13/lib_x64
cp ../extlibs/libvorbis/win32/VS2013/x64/Release/libvorbis.dll       ../FK_VC13/bin_x64
cp ../extlibs/libvorbis/win32/VS2013/x64/Release/libvorbisfile.lib   ../FK_VC13/lib_x64
cp ../extlibs/libvorbis/win32/VS2013/x64/Release/libvorbisfile.dll   ../FK_VC13/bin_x64
cp ../extlibs/DirectInput/lib_x64/*.lib                              ../FK_VC13/lib_x64
cp ../extlibs/OpenAL/lib_x64/*.lib                                   ../FK_VC13/lib_x64
cp ../extlibs/GLEW/lib_x64/*.lib                                     ../FK_VC13/lib_x64
cp ../extlibs/GLEW/bin_x64/*.dll                                     ../FK_VC13/bin_x64
cp ../extlibs/GLEW/bin_x64/*.exe                                     ../FK_VC13/bin_x64

mkdir ../FK_VC13/include
mkdir ../FK_VC13/include/FK
cp ../../FK/*.h ../FK_VC13/include/FK

mkdir ../FK_VC13/include/FL
cp ../extlibs/fltk-1.3.2/FL/*.h ../FK_VC13/include/FL

mkdir ../FK_VC13/include/DX
cp ../extlibs/DirectInput/include/DX/*.h ../FK_VC13/include/DX

mkdir ../FK_VC13/include/GL
cp ../extlibs/GLEW/include/GL/*.h ../FK_VC13/include/GL

cp ../extlibs/OpenAL/redist/*.exe ../FK_VC13/redist

mkdir ../FK_VC13/doc/glew
cp ../extlibs/GLEW/doc/*.* ../FK_VC13/doc/glew
cp -r ../doc ../FK_VC13/doc
cp -r vs_wizard ../FK_VC13/vs_wizard
