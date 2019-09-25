export VS16VSWHERE=/cygdrive/c/Program\ Files\ \(x86\)/Microsoft\ Visual\ Studio/Installer/vswhere
export VS160COMNTOOLS=`"${VS16VSWHERE}" -format value -property installationPath | grep 2019 | sed -e "s/\r//g" | sed -e "s/C:\\\\\/\/cygdrive\/c\//" | sed -e "s/\\\\\/\//g"`
export VS16_DEVENV_PATH="${VS160COMNTOOLS}/Common7/IDE/devenv.com"
