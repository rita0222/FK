@echo off
echo --- Copying built files ---

rd /s /q ..\FK_VC13
md ..\FK_VC13
md ..\FK_VC13\bin
md ..\FK_VC13\bin_x64
md ..\FK_VC13\doc
md ..\FK_VC13\include
md ..\FK_VC13\lib
md ..\FK_VC13\lib_x64
md ..\FK_VC13\redist
md ..\FK_VC13\vs_wizard

copy lib_Win32\*.lib                                                   ..\FK_VC13\lib
copy ..\extlibs\fltk-1.3.2\ide\VisualC2013\lib_Win32\*.lib             ..\FK_VC13\lib
ren ..\FK_VC13\lib\fltkzlib.lib fltkz.lib
ren ..\FK_VC13\lib\fltkzlib_d.lib fltkz_d.lib
copy ..\extlibs\freetype-2.5.3\objs\win32\vc2013\freetype253MT.lib     ..\FK_VC13\lib\freetype2MT.lib
copy ..\extlibs\freetype-2.5.3\objs\win32\vc2013\freetype253MT_D.lib   ..\FK_VC13\lib\freetype2MT_d.lib
copy ..\extlibs\libiconv\ReleaseStatic_Win32\libiconv_2013Static.lib   ..\FK_VC13\lib\libiconv.lib
copy ..\extlibs\libiconv\DebugStatic_Win32\libiconv_2013StaticD.lib    ..\FK_VC13\lib\libiconv_d.lib
copy ..\extlibs\libogg\win32\VS2013\Win32\Release\libogg.lib           ..\FK_VC13\lib
copy ..\extlibs\libogg\win32\VS2013\Win32\Release\libogg.dll           ..\FK_VC13\bin
copy ..\extlibs\libvorbis\win32\VS2013\Win32\Release\libvorbis.lib     ..\FK_VC13\lib
copy ..\extlibs\libvorbis\win32\VS2013\Win32\Release\libvorbis.dll     ..\FK_VC13\bin
copy ..\extlibs\libvorbis\win32\VS2013\Win32\Release\libvorbisfile.lib ..\FK_VC13\lib
copy ..\extlibs\libvorbis\win32\VS2013\Win32\Release\libvorbisfile.dll ..\FK_VC13\bin
copy ..\extlibs\DirectInput\lib\*.lib                                  ..\FK_VC13\lib
copy ..\extlibs\OpenAL\lib\*.lib                                       ..\FK_VC13\lib
copy ..\extlibs\GLEW\lib\*.lib                                         ..\FK_VC13\lib
copy ..\extlibs\GLEW\bin\*.dll                                         ..\FK_VC13\bin
copy ..\extlibs\GLEW\bin\*.exe                                         ..\FK_VC13\bin

copy lib_x64\*.lib                                                     ..\FK_VC13\lib_x64
copy ..\extlibs\fltk-1.3.2\ide\VisualC2013\lib_x64\*.lib               ..\FK_VC13\lib_x64
ren ..\FK_VC13\lib_x64\fltkzlib.lib fltkz.lib
ren ..\FK_VC13\lib_x64\fltkzlib_d.lib fltkz_d.lib
copy ..\extlibs\freetype-2.5.3\objs\win64\vc2013\freetype253MT.lib     ..\FK_VC13\lib_x64\freetype2MT.lib
copy ..\extlibs\freetype-2.5.3\objs\win64\vc2013\freetype253MT_D.lib   ..\FK_VC13\lib_x64\freetype2MT_d.lib
copy ..\extlibs\libiconv\ReleaseStatic_x64\libiconv_2013Static.lib     ..\FK_VC13\lib_x64\libiconv.lib
copy ..\extlibs\libiconv\DebugStatic_x64\libiconv_2013StaticD.lib      ..\FK_VC13\lib_x64\libiconv_d.lib
copy ..\extlibs\libogg\win32\VS2013\x64\Release\libogg.lib             ..\FK_VC13\lib_x64
copy ..\extlibs\libogg\win32\VS2013\x64\Release\libogg.dll             ..\FK_VC13\bin_x64
copy ..\extlibs\libvorbis\win32\VS2013\x64\Release\libvorbis.lib       ..\FK_VC13\lib_x64
copy ..\extlibs\libvorbis\win32\VS2013\x64\Release\libvorbis.dll       ..\FK_VC13\bin_x64
copy ..\extlibs\libvorbis\win32\VS2013\x64\Release\libvorbisfile.lib   ..\FK_VC13\lib_x64
copy ..\extlibs\libvorbis\win32\VS2013\x64\Release\libvorbisfile.dll   ..\FK_VC13\bin_x64
copy ..\extlibs\DirectInput\lib_x64\*.lib                              ..\FK_VC13\lib_x64
copy ..\extlibs\OpenAL\lib_x64\*.lib                                   ..\FK_VC13\lib_x64
copy ..\extlibs\GLEW\lib_x64\*.lib                                     ..\FK_VC13\lib_x64
copy ..\extlibs\GLEW\bin_x64\*.dll                                     ..\FK_VC13\bin_x64
copy ..\extlibs\GLEW\bin_x64\*.exe                                     ..\FK_VC13\bin_x64

md ..\FK_VC13\include
md ..\FK_VC13\include\FK
copy ..\..\FK\*.h ..\FK_VC13\include\FK

md ..\FK_VC13\include\FL
copy ..\extlibs\fltk-1.3.2\FL\*.h ..\FK_VC13\include\FL

md ..\FK_VC13\include\DX
copy ..\extlibs\DirectInput\include\DX\*.h ..\FK_VC13\include\DX

md ..\FK_VC13\include\GL
copy ..\extlibs\GLEW\include\GL\*.h ..\FK_VC13\include\GL

copy ..\extlibs\OpenAL\redist\*.exe ..\FK_VC13\redist

md ..\FK_VC13\doc\glew
copy ..\extlibs\GLEW\doc\*.* ..\FK_VC13\doc\glew
xcopy /s /e ..\doc ..\FK_VC13\doc
xcopy /s /e vs_wizard ..\FK_VC13\vs_wizard

echo Done!
