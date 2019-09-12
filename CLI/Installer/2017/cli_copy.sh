#!/bin/sh

source ./vsenv.sh

OUTPATH="./FK_CLI17"
INPATH="../../2017/FK_CLI_DLL"

rm -rf $OUTPATH
mkdir -p $OUTPATH/bin/x86
mkdir -p $OUTPATH/bin/x64
mkdir -p $OUTPATH/dll/x86
mkdir -p $OUTPATH/dll/x64
mkdir $OUTPATH/doc
mkdir $OUTPATH/redist
cp $INPATH/Win32/Release/FK_CLI.dll $OUTPATH/bin/x86
cp $INPATH/Win32/Release/FK_FormHelper.dll $OUTPATH/bin/x86
cp $INPATH/x64/Release/FK_CLI.dll $OUTPATH/bin/x64
cp $INPATH/x64/Release/FK_FormHelper.dll $OUTPATH/bin/x64

cp ./doc/License.txt $OUTPATH/doc
cp ./doc/Version_CLI.txt $OUTPATH/doc/Version.txt
cp ../../contrib/bin/x86/* $OUTPATH/dll/x86
cp ../../contrib/bin/x64/* $OUTPATH/dll/x64
cp "$VS150COMNTOOLS\\VC\\Redist\\MSVC\\14.16.27012\\vcredist_x86.exe" $OUTPATH/redist
cp "$VS150COMNTOOLS\\VC\\Redist\\MSVC\\14.16.27012\\vcredist_x64.exe" $OUTPATH/redist
