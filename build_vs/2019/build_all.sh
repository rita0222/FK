#!/bin/sh

echo "--- Create FK Package ---"

#sh -x lib_clean_other.sh
#sh -x lib_build_other.sh

sh -x lib_clean_FK.sh
sh -x lib_build_FK.sh
sh -x lib_copy.sh

#if [ -z "$ZSH_NAME" ] ; then
#	sh -x lib_installer.sh
#else
#	zsh -x lib_installer.sh
#fi

echo "Completed!"
