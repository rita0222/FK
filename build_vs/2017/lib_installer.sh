#!/bin/sh

cd ../FK_ProjectWizard

if [ -z "$ZSH_NAME" ] ; then
	cygstart /cygdrive/c/Program\ Files/CreateInstall\ Free\ JP/ci-free.exe FK_VC17.ci
else
	cygstart FK_VC17.ci
fi
