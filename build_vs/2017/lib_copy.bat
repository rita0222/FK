@echo off
echo --- Copying built files ---

rd /s /q ..\FK_VC17
md ..\FK_VC17
md ..\FK_VC17\bin
md ..\FK_VC17\bin_x64
md ..\FK_VC17\doc
md ..\FK_VC17\include
md ..\FK_VC17\lib
md ..\FK_VC17\lib_x64
md ..\FK_VC17\redist
md ..\FK_VC17\vs_wizard

copy lib_Win32\*.lib                                                                    ..\FK_VC17\lib
copy ..\extlibs\fltk-1.3.3\ide\VisualC2017\bin\Win32\*.lib                              ..\FK_VC17\lib
ren ..\FK_VC17\lib\fltkzlib.lib fltkz.lib
ren ..\FK_VC17\lib\fltkzlib_d.lib fltkz_d.lib
copy ..\extlibs\freetype-2.6\objs\vc2017\Win32\freetype26MT.lib                         ..\FK_VC17\lib\freetype2MT.lib
copy ..\extlibs\freetype-2.6\objs\vc2017\Win32\freetype26MTd.lib                        ..\FK_VC17\lib\freetype2MT_d.lib
copy ..\extlibs\libiconv\ReleaseStatic_Win32\libiconv_2017Static.lib                    ..\FK_VC17\lib\libiconv.lib
copy ..\extlibs\libiconv\DebugStatic_Win32\libiconv_2017StaticD.lib                     ..\FK_VC17\lib\libiconv_d.lib
copy ..\extlibs\libogg-1.3.2\win32\VS2017\bin\Win32\Release\libogg_static.lib           ..\FK_VC17\lib\libogg.lib
copy ..\extlibs\libogg-1.3.2\win32\VS2017\bin\Win32\Debug\libogg_static.lib             ..\FK_VC17\lib\libogg_d.lib
copy ..\extlibs\libvorbis-1.3.5\win32\VS2017\bin\Win32\Release\libvorbis_static.lib     ..\FK_VC17\lib\libvorbis.lib
copy ..\extlibs\libvorbis-1.3.5\win32\VS2017\bin\Win32\Debug\libvorbis_static.lib       ..\FK_VC17\lib\libvorbis_d.lib
copy ..\extlibs\libvorbis-1.3.5\win32\VS2017\bin\Win32\Release\libvorbisfile_static.lib ..\FK_VC17\lib\libvorbisfile.lib
copy ..\extlibs\libvorbis-1.3.5\win32\VS2017\bin\Win32\Debug\libvorbisfile_static.lib   ..\FK_VC17\lib\libvorbisfile_d.lib
copy ..\extlibs\DirectInput\lib\*.lib                                                   ..\FK_VC17\lib
copy ..\extlibs\OpenAL\lib\*.lib                                                        ..\FK_VC17\lib
copy ..\extlibs\glew-1.12.0\lib\Release\Win32\*.lib                                     ..\FK_VC17\lib
copy ..\extlibs\glew-1.12.0\bin\Release\Win32\*.*                                       ..\FK_VC17\bin

copy lib_x64\*.lib                                                                      ..\FK_VC17\lib_x64
copy ..\extlibs\fltk-1.3.3\ide\VisualC2017\bin\x64\*.lib                                ..\FK_VC17\lib_x64
ren ..\FK_VC17\lib_x64\fltkzlib.lib fltkz.lib
ren ..\FK_VC17\lib_x64\fltkzlib_d.lib fltkz_d.lib
copy ..\extlibs\freetype-2.6\objs\vc2017\x64\freetype26MT.lib                           ..\FK_VC17\lib_x64\freetype2MT.lib
copy ..\extlibs\freetype-2.6\objs\vc2017\x64\freetype26MTd.lib                          ..\FK_VC17\lib_x64\freetype2MT_d.lib
copy ..\extlibs\libiconv\ReleaseStatic_x64\libiconv_2017Static.lib                      ..\FK_VC17\lib_x64\libiconv.lib
copy ..\extlibs\libiconv\DebugStatic_x64\libiconv_2017StaticD.lib                       ..\FK_VC17\lib_x64\libiconv_d.lib
copy ..\extlibs\libogg-1.3.2\win32\VS2017\bin\x64\Release\libogg_static.lib             ..\FK_VC17\lib_x64\libogg.lib
copy ..\extlibs\libogg-1.3.2\win32\VS2017\bin\x64\Debug\libogg_static.lib               ..\FK_VC17\lib_x64\libogg_d.lib
copy ..\extlibs\libvorbis-1.3.5\win32\VS2017\bin\x64\Release\libvorbis_static.lib       ..\FK_VC17\lib_x64\libvorbis.lib
copy ..\extlibs\libvorbis-1.3.5\win32\VS2017\bin\x64\Debug\libvorbis_static.lib         ..\FK_VC17\lib_x64\libvorbis_d.lib
copy ..\extlibs\libvorbis-1.3.5\win32\VS2017\bin\x64\Release\libvorbisfile_static.lib   ..\FK_VC17\lib_x64\libvorbisfile.lib
copy ..\extlibs\libvorbis-1.3.5\win32\VS2017\bin\x64\Debug\libvorbisfile_static.lib     ..\FK_VC17\lib_x64\libvorbisfile_d.lib
copy ..\extlibs\DirectInput\lib_x64\*.lib                                               ..\FK_VC17\lib_x64
copy ..\extlibs\OpenAL\lib_x64\*.lib                                                    ..\FK_VC17\lib_x64
copy ..\extlibs\glew-1.12.0\lib\Release\x64\*.lib                                       ..\FK_VC17\lib_x64
copy ..\extlibs\glew-1.12.0\bin\Release\x64\*.*                                         ..\FK_VC17\bin_x64

md ..\FK_VC17\include
md ..\FK_VC17\include\FK
copy ..\..\FK\*.h ..\FK_VC17\include\FK

md ..\FK_VC17\include\FL
copy ..\extlibs\fltk-1.3.3\FL\*.h ..\FK_VC17\include\FL

md ..\FK_VC17\include\DX
copy ..\extlibs\DirectInput\include\DX\*.h ..\FK_VC17\include\DX

md ..\FK_VC17\include\GL
copy ..\extlibs\glew-1.12.0\include\GL\*.h ..\FK_VC17\include\GL

copy ..\extlibs\OpenAL\redist\*.exe ..\FK_VC17\redist

md ..\FK_VC17\doc\glew
copy ..\extlibs\glew-1.12.0\LICENSE.txt ..\FK_VC17\doc\glew
copy ..\doc\JapaneseStringInFLTK.txt ..\FK_VC17\doc
copy ..\doc\License.txt ..\FK_VC17\doc
copy ..\doc\RelativeLibraries.txt ..\FK_VC17\doc
copy ..\doc\Version_2017.txt ..\FK_VC17\doc\Version.txt

xcopy /s /e vs_wizard ..\FK_VC17\vs_wizard

echo Done!
