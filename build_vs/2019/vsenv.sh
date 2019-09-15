export VS15VSWHERE=/cygdrive/c/Program\ Files\ \(x86\)/Microsoft\ Visual\ Studio/Installer/vswhere
export VS150COMNTOOLS=`"${VS15VSWHERE}" -format value -property installationPath | grep 2019 | sed -e "s/\r//g" | sed -e "s/C:\\\\\/\/cygdrive\/c\//" | sed -e "s/\\\\\/\//g"`
export VS15_DEVENV_PATH="${VS150COMNTOOLS}/Common7/IDE/devenv.com"
