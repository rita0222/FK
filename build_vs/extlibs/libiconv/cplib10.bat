@echo off
call "%VS100COMNTOOLS%vsvars32.bat"

devenv LibIconv.sln /rebuild "ReleaseStatic|Win32"
copy ReleaseStatic_Win32\libiconvStatic.lib ..\FK_VC10\lib\libiconv.lib

devenv LibIconv.sln /rebuild "ReleaseStatic|x64"
copy ReleaseStatic_x64\libiconvStatic.lib ..\FK_VC10\lib_x64\libiconv.lib

pause
