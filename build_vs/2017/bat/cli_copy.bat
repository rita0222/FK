@echo off
echo --- Copying built files ---

rd /s /q ..\FK_CLI
md ..\FK_CLI
md ..\FK_CLI\bin
md ..\FK_CLI\doc
md ..\FK_CLI\redist
copy ..\..\CLI\FK_CLI_DLL\Release\*.dll ..\FK_CLI\bin
copy ..\doc\License.txt ..\FK_CLI\doc
copy ..\doc\Version_CLI.txt ..\FK_CLI\doc\Version.txt
copy ..\extlibs\OpenAL\redist\*.exe ..\FK_CLI\redist
copy "%VS150COMNTOOLS%..\..\VC\redist\1033\vcredist_x86.exe" ..\FK_CLI\redist

echo Done!
