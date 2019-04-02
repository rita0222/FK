#!/bin/sh

FKPATH="../Installer/FK_VC17"
FK32R="$FKPATH/lib/Win32/Release"
FK32D="$FKPATH/lib/Win32/Debug"
FK64R="$FKPATH/lib/x64/Release"
FK64D="$FKPATH/lib/x64/Debug"

rm -rf $FKPATH

mkdir -p $FK32R
mkdir -p $FK32D
mkdir -p $FK64R
mkdir -p $FK64D

# for FK
cp lib/Win32/Release/*.lib $FK32R
cp lib/Win32/Debug/*.lib $FK32D
cp lib/x64/Release/*.lib $FK64R
cp lib/x64/Debug/*.lib $FK64D

# for Other
cp contrib/lib/Win32/Release/*.lib $FK32R
cp contrib/lib/Win32/Debug/*.lib $FK32D
cp contrib/lib/x64/Release/*.lib $FK64R
cp contrib/lib/x64/Debug/*.lib $FK64D

# for Header
cp -r contrib/include $FKPATH
mkdir -p $FKPATH/include/FK
cp ../../FK/*.[h,H] $FKPATH/include/FK

# misc
cp -r contrib/redist $FKPATH
cp -r contrib/doc $FKPATH
