#!/bin/sh

source ./vsenv.sh

OUTPATH="./FK_Core19"
INPATH="../../Core2019/FK_Core_DLL"
COREDIR="netcoreapp3.1"

rm -rf $OUTPATH
mkdir -p $OUTPATH/bin/x86
mkdir -p $OUTPATH/bin/x64
mkdir -p $OUTPATH/dll/x86
mkdir -p $OUTPATH/dll/x64
mkdir $OUTPATH/doc
mkdir $OUTPATH/redist
cp $INPATH/Win32/Release/$COREDIR/FK*.dll $OUTPATH/bin/x86
cp $INPATH/Win32/Release/$COREDIR/Ijwhost.dll $OUTPATH/dll/x86
cp $INPATH/x64/Release/$COREDIR/FK*.dll $OUTPATH/bin/x64
cp $INPATH/x64/Release/$COREDIR/Ijwhost.dll $OUTPATH/dll/x64

cp ./doc/License.txt $OUTPATH/doc
cp ./doc/Version_Core.txt $OUTPATH/doc/Version.txt
cp ../../contrib/bin/x86/* $OUTPATH/dll/x86
cp ../../contrib/bin/x64/* $OUTPATH/dll/x64
cp "$VS160COMNTOOLS"/VC/Redist/MSVC/*/vcredist_x86.exe $OUTPATH/redist
cp "$VS160COMNTOOLS"/VC/Redist/MSVC/*/vcredist_x64.exe $OUTPATH/redist
