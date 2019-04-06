#!/bin/sh

source ./vsenv.sh

OUTPATH="../Installer/FK_CLI"
INPATH="../../CLI/FK_CLI_DLL"

rm -rf $OUTPATH
mkdir -p $OUtPATH/bin/x86
mkdir -p $OUTPATH/bin/x64
mkdir $OUTPATH/doc
mkdir $OUTPATH/redist
cp $INPATH/Win32/$CLIPATH/bin/FK_CLI.dll
cp ../doc/License.txt $CLIPATH/cddoc
cp ../doc/Version_CLI.txt $CLIPATH/doc/Version.txt
cp ../extlibs/OpenAL/redist/*.exe $CLIPATH/redist
cp "$VS150COMNTOOLS\\VC\\Redist\\MSVC\\14.16.27012\\vcredist_x64.exe" $CLIPATH/redist
