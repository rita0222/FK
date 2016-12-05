@echo off
echo --- Create FK CLI Package ---

call cli_clean.bat
call cli_build.bat
call cli_copy.bat

echo Completed!
