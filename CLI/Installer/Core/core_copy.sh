#!/bin/sh

source ./vsenv.sh

COREDIR="netcoreapp3.1"
OUTPATH="./FK_Core19"

INPATH="../../Core2019/FK_Core_DLL"
X86DIR="x86/Release"
X64DIR="x64/Release"

rm -rf $OUTPATH
mkdir -p $OUTPATH/bin/x86
mkdir -p $OUTPATH/bin/x64
mkdir -p $OUTPATH/dll/x86
mkdir -p $OUTPATH/dll/x64
mkdir $OUTPATH/doc
mkdir $OUTPATH/redist

cp $INPATH/$X86DIR/$COREDIR/FK_*.dll $OUTPATH/bin/x86
cp $INPATH/$X86DIR/$COREDIR/Ijwhost.dll $OUTPATH/dll/x86

cp $INPATH/$X64DIR/$COREDIR/FK_*.dll $OUTPATH/bin/x64
cp $INPATH/$X64DIR/$COREDIR/Ijwhost.dll $OUTPATH/dll/x64

cp ./doc/License.txt $OUTPATH/doc
cp ./doc/Version_Core.txt $OUTPATH/doc/Version.txt
cp ../../contrib/bin/x86/* $OUTPATH/dll/x86
cp ../../contrib/bin/x64/* $OUTPATH/dll/x64
cp "$VS160COMNTOOLS"/VC/Redist/MSVC/*/vcredist_x86.exe $OUTPATH/redist
cp "$VS160COMNTOOLS"/VC/Redist/MSVC/*/vcredist_x64.exe $OUTPATH/redist
