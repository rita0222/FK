#!/bin/sh

echo "--- Create FK Package ---"

sh -x lib_clean.sh
sh -x lib_build.sh
sh -x lib_copy.sh

echo "Completed!"
