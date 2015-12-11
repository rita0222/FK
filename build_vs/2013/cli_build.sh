echo "--- Build solutions ---"

source ./vsenv.sh

# VS2013へのパスを設定
export VS12_DEVENV_PATH=$VS120COMNTOOLS/../IDE/devenv

# cli
"$VS12_DEVENV_PATH" ..\\..\\CLI\\FK_CLI_Build.sln /Build "Release|Mixed Platforms"

echo "Done!"
