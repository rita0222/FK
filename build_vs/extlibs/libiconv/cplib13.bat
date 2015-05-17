@echo off

copy ReleaseStatic_Win32\libiconv_2013Static.lib ..\FK_VC13\lib\libiconv.lib

copy ReleaseStatic_x64\libiconv_2013Static.lib ..\FK_VC13\lib_x64\libiconv.lib

pause
