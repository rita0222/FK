#!/bin/sh

echo "--- Create FK CLI Package ---"

sh -x cli_clean.sh
sh -x cli_build.sh
sh -x cli_copy.sh

if [ -z "$ZSH_NAME" ] ; then
	sh -x cli_installer.sh
else
	zsh -x cli_installer.sh
fi