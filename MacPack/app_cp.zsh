#!/usr/bin/env zsh

rm -rf Package

mkdir Package
mkdir Package/FK_Lib4
mkdir Package/FK_Lib4/include
mkdir Package/FK_Lib4/lib

cp -r include/FL Package/FK_Lib4/include
cp -r etc Package/FK_Lib4
cp -r doc Package/FK_Lib4
#cp -r lib/dynamic Package/FK_Lib4/lib
cp -r lib/static Package/FK_Lib4/lib
#cp ../lib/dynamic/*.dylib Package/FK_Lib4/lib/dynamic
cp ../lib/static/*.a Package/FK_Lib4/lib/static

ranlib Package/FK_Lib4/lib/static/*.a

cp -r ../FK Package/FK_Lib4/include

pkgbuild \
	--root ./Package \
	--identifier jp.gamescience.fk \
	--install-location /Library \
	--version 4.1.2 \
	--ownership preserve \
	--scripts ./script \
	tmpInst.pkg

productbuild \
	--distribution ./script/distribution.xml \
	--package-path . \
	fk_Installer.pkg

rm tmpInst.pkg
#rm -rf Package
