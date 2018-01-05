#!/bin/sh

echo "--- Create FK Package ---"

sh -x lib_clean.sh
sh -x lib_build.sh
sh -x lib_copy.sh

if [ -z "$ZSH_NAME" ] ; then
	sh -x lib_installer.sh
else
	zsh -x lib_installer.sh
fi

echo "Completed!"
