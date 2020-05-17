#!/bin/sh

source ./vsenv.sh

OUTPATH="./FK_Core19"

TARGETNAME="netcoreapp3.1"

INPATH="../../Core2019/FK_Core_DLL"
X86DIR="x86/Release/$TARGETNAME"
X64DIR="x64/Release/$TARGETNAME"
WIN32DIR="Win32/Release/$TARGETNAME"

rm -rf $OUTPATH
mkdir -p $OUTPATH/bin/x86
mkdir -p $OUTPATH/bin/x64
mkdir -p $OUTPATH/dll/x86
mkdir -p $OUTPATH/dll/x64
mkdir $OUTPATH/doc
mkdir $OUTPATH/redist

cp $INPATH/Base/$WIN32DIR/FK_Core.dll $OUTPATH/bin/x86
cp $INPATH/Audio/$X86DIR/FK_Audio_Core.dll $OUTPATH/bin/x86
cp $INPATH/FormHelper/$X86DIR/FK_FormHelper_Core.dll $OUTPATH/bin/x86
cp $INPATH/Base/$WIN32DIR/Ijwhost.dll $OUTPATH/dll/x86

cp $INPATH/Base/$X64DIR/FK_Core.dll $OUTPATH/bin/x64
cp $INPATH/Audio/$X64DIR/FK_Audio_Core.dll $OUTPATH/bin/x64
cp $INPATH/FormHelper/$X64DIR/FK_FormHelper_Core.dll $OUTPATH/bin/x64
cp $INPATH/Base/$X64DIR/Ijwhost.dll $OUTPATH/dll/x64

cp ./doc/License.txt $OUTPATH/doc
cp ./doc/Version_Core.txt $OUTPATH/doc/Version.txt
cp ../../contrib/bin/x86/* $OUTPATH/dll/x86
cp ../../contrib/bin/x64/* $OUTPATH/dll/x64
cp "$VS160COMNTOOLS"/VC/Redist/MSVC/*/vcredist_x86.exe $OUTPATH/redist
cp "$VS160COMNTOOLS"/VC/Redist/MSVC/*/vcredist_x64.exe $OUTPATH/redist
