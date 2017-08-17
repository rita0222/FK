#!/bin/sh

cd ../FK_ProjectWizard

if [ -z "$ZSH_NAME" ] ; then
	/cygdrive/c/Program\ Files/CreateInstall\ Free\ JP/ci-free.exe FK_VC15.ci
else
	cygstart FK_VC15.ci
fi
