#!/bin/sh

cd ../FK_ProjectWizard

if [ -z "$ZSH_NAME" ] ; then
	/cygdrive/c/Program\ Files/CreateInstall\ Free\ JP/ci-free.exe FK_CLI.ci
else
	cygstart FK_CLI.ci
fi
