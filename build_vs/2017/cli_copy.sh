#!/bin/sh

CLIPATH="../Installer/FK_CLI"

source ./vsenv.sh

rm -rf $CLIPATH
mkdir $CLIPATH
mkdir $CLIPATH/bin
mkdir $CLIPATH/doc
mkdir $CLIPATH/redist
cp ../../CLI/x64/Release/FK_CLI_2017.dll $CLIPATH/bin/FK_CLI.dll
cp ../doc/License.txt $CLIPATH/doc
cp ../doc/Version_CLI.txt $CLIPATH/doc/Version.txt
cp ../extlibs/OpenAL/redist/*.exe $CLIPATH/redist
cp "$VS150COMNTOOLS\\VC\\Redist\\MSVC\\14.16.27012\\vcredist_x64.exe" $CLIPATH/redist
