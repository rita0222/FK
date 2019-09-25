#!/bin/sh

echo "--- Create FK CLI Package ---"

sh -x cli_clean.sh
sh -x cli_glsl.sh
sh -x cli_build.sh
sh -x cli_copy.sh
