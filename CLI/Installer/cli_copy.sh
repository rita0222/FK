#!/bin/sh

source ./vsenv.sh

OUTPATH="./FK_CLI"
INPATH="../FK_CLI_DLL"

rm -rf $OUTPATH
mkdir -p $OUTPATH/bin/x86
mkdir -p $OUTPATH/bin/x64
mkdir $OUTPATH/doc
mkdir $OUTPATH/redist
cp $INPATH/Win32/Release/FK_CLI.dll $OUTPATH/bin/x86
cp $INPATH/Win32/Release/FK_FormHelper.dll $OUTPATH/bin/x86
cp $INPATH/Win32/Debug/FK_CLI_d.dll $OUTPATH/bin/x86
cp $INPATH/Win32/Debug/FK_CLI_d.pdb $OUTPATH/bin/x86
cp $INPATH/Win32/Debug/FK_FormHelper.dll $OUTPATH/bin/x86/FK_FormHelper_d.dll
cp $INPATH/x64/Release/FK_CLI.dll $OUTPATH/bin/x64
cp $INPATH/x64/Release/FK_FormHelper.dll $OUTPATH/bin/x64
cp $INPATH/x64/Debug/FK_CLI_d.dll $OUTPATH/bin/x64
cp $INPATH/x64/Debug/FK_CLI_d.pdb $OUTPATH/bin/x64
cp $INPATH/x64/Debug/FK_FormHelper.dll $OUTPATH/bin/x64/FK_FormHelper_d.dll

cp ./doc/License.txt $OUTPATH/doc
cp ./doc/Version_CLI.txt $OUTPATH/doc/Version.txt
#cp ../../build_vs/extlibs/OpenAL/redist/*.exe $OUTPATH/redist
cp ../contrib/bin/x86/* $OUTPATH/bin/x86
cp ../contrib/bin/x64/* $OUTPATH/bin/x64
cp "$VS150COMNTOOLS\\VC\\Redist\\MSVC\\14.16.27012\\vcredist_x86.exe" $OUTPATH/redist
cp "$VS150COMNTOOLS\\VC\\Redist\\MSVC\\14.16.27012\\vcredist_x64.exe" $OUTPATH/redist
