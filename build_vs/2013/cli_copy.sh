#!/bin/sh

echo "--- Copying built files ---"

source ./vsenv.sh

rm -rf ../FK_CLI
mkdir ../FK_CLI
mkdir ../FK_CLI/bin
mkdir ../FK_CLI/doc
mkdir ../FK_CLI/redist
cp ../../CLI/FK_CLI_DLL/Release/*.dll ../FK_CLI/bin
cp ../doc/License.txt ../FK_CLI/doc
cp ../doc/Version_CLI.txt ../FK_CLI/doc/Version.txt
cp ../extlibs/OpenAL/redist/*.exe ../FK_CLI/redist
cp "$VS120COMNTOOLS\\..\\..\\VC\\redist\\1041\\vcredist_x86.exe" ../FK_CLI/redist

echo "Done!"
