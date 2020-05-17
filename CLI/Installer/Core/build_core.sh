#!/bin/sh

echo "--- Create FK .NET Core Package ---"

sh -x core_clean.sh
sh -x core_glsl.sh
sh -x core_build.sh
sh -x core_copy.sh
