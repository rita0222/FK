@echo off

copy ReleaseStatic_Win32\libiconv_2012Static.lib ..\FK_VC12\lib\libiconv.lib

copy ReleaseStatic_x64\libiconv_2012Static.lib ..\FK_VC12\lib_x64\libiconv.lib

pause
