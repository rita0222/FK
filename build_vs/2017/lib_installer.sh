#!/bin/sh

cd ../FK_ProjectWizard

if [ -z "$ZSH_NAME" ] ; then
	cygstart /cygdrive/c/Program\ Files\ \(x86\)/CreateInstall\ Free/ci-free.exe FK_VC17.ci
else
	cygstart FK_VC17.ci
fi
