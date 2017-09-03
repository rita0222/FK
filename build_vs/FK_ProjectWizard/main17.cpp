#include <windows.h>
#include <shlwapi.h>
#include <shlobj.h> 
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

bool addEnvPath(const string& name, const string& dirPath)
{
	HKEY hkey;
	DWORD result;
	const char *tmpStr = dirPath.c_str();
	DWORD dataSize = (DWORD)strlen(tmpStr);
	DWORD dataType = REG_SZ;
	DWORD dwReturnValue; 

	result = RegOpenKeyEx(HKEY_CURRENT_USER, "Environment", 0, KEY_WRITE, &hkey);
	if(result == ERROR_SUCCESS) {
		if(RegSetValueEx(hkey, name.c_str(), NULL, dataType, (LPBYTE)tmpStr, dataSize) == ERROR_SUCCESS) {
			RegCloseKey(hkey);

			SendMessageTimeout( 
				HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)TEXT("Environment"), 
				SMTO_ABORTIFHUNG, 5000, &dwReturnValue);

			return true;
		}
		RegCloseKey(hkey);
	}

	return false;
}

bool deleteEnvPath(const string& name)
{
	HKEY hkey;
	DWORD result;
	DWORD dwReturnValue; 

	result = RegOpenKeyEx(HKEY_CURRENT_USER, "Environment", 0, KEY_WRITE, &hkey);
	if(result == ERROR_SUCCESS) {
		if(RegDeleteValue(hkey, name.c_str()) == ERROR_SUCCESS) {
			RegCloseKey(hkey);

			SendMessageTimeout( 
				HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)TEXT("Environment"), 
				SMTO_ABORTIFHUNG, 5000, &dwReturnValue);

			return true;
		}
		RegCloseKey(hkey);
	}

	return false;
}

bool regist(const string &vcwizPath, const string &libPath)
{
	BOOL			retVal = TRUE;
	vector<string>	targetList;

	targetList.clear();
	targetList.push_back("FK_ProjectWizard.ico");
	targetList.push_back("FK_ProjectWizard.vsdir");
	targetList.push_back("FK_ProjectWizard.vsz");

	CreateDirectory(vcwizPath.c_str(), NULL);
	for(int i = 0; i < (int)targetList.size(); i++) {
		retVal &= CopyFile(targetList[i].c_str(), (vcwizPath + targetList[i]).c_str(), FALSE);
		if (i == (int)targetList.size() - 1) {
			ofstream vsz((vcwizPath + targetList[i]).c_str(), ios::app);
			if (vsz.is_open()) {
				vsz << "Param=\"ABSOLUTE_PATH = " << libPath << "\\vs_wizard\\FK_ProjectWizard\"" << endl;
			} else {
				retVal = FALSE;
				break;
			}
		}
	}

	return (retVal == TRUE);
}

bool unregist(const string &vcwizPath)
{
	BOOL			retVal = TRUE;
	vector<string>	targetList;

	targetList.clear();
	targetList.push_back("FK_ProjectWizard.ico");
	targetList.push_back("FK_ProjectWizard.vsdir");
	targetList.push_back("FK_ProjectWizard.vsz");

	for(int i = 0; i < (int)targetList.size(); i++) {
		retVal &= DeleteFile((vcwizPath + targetList[i]).c_str());
	}

	return (retVal == TRUE);
}

int main(int argc, char *argv[])
{
	char	tmpPath[MAX_PATH];
	SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, NULL, tmpPath);

	string	vcwizPath;
	vcwizPath = tmpPath;
	vcwizPath += "\\Visual Studio 2017\\Wizards\\";

	string	libPath;
	DWORD	pathRes = GetModuleFileName(NULL, tmpPath, MAX_PATH);
	libPath = tmpPath;
	libPath = libPath.substr(0, libPath.find_last_of('\\'));
	libPath = libPath.substr(0, libPath.find_last_of('\\'));

	if(argc >= 2) {
		if(strcmp("-u", argv[1]) == 0) {
			MessageBox(NULL, "Visual Studio の設定を削除するので、\n起動している場合は終了してください。", "Visual Studio 設定変更", NULL);

			// パス削除試行
			if(!deleteEnvPath("FK_VC17_DIR")) {
				MessageBox(NULL, "ライブラリのディレクトリ設定を削除できませんでした。\n環境変数を確認し、手動で削除してください。", "ディレクトリ設定失敗", NULL);
			}
			// ウィザード削除試行
			if(unregist(vcwizPath)) {
				MessageBox(NULL, "Visual Studio 2017 からプロジェクトウィザードを削除しました。", "ウィザード削除成功", NULL);
				return 0;
			} else {
				MessageBox(NULL, "Visual Studio 2017 からのウィザード削除に失敗しました。\n既に削除済みだったか、一部のファイルが残っている可能性があります。", "ウィザード削除失敗", NULL);
				return 1;
			}
		}
	} else {
		MessageBox(NULL, "Visual Studio の設定を追加するので、\nVisual Studio を起動している場合は終了してください。", "Visual Studio 設定変更", NULL);

		// パス追加試行
		if(!addEnvPath("FK_VC17_DIR", libPath)) {
			MessageBox(NULL, "ライブラリのディレクトリ設定を追加できませんでした。\n環境変数を確認し、手動で追加してください。", "ディレクトリ設定失敗", NULL);
		}

		// ウィザード追加試行
		if(regist(vcwizPath, libPath)) {
			MessageBox(NULL, "Visual Studio 2017 にプロジェクトウィザードを登録しました。", "ウィザード登録成功", NULL);
		} else {
			unregist(vcwizPath);
			MessageBox(NULL, "Visual Studio 2017 へのウィザード登録に失敗しました。\nプロジェクトの作成は手動で行ってください。", "ウィザード登録失敗", NULL);
			return 1;
		}
	}

	return 0;
}

// WinMain trap
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                             LPSTR lpCmdLine, int nCmdShow)
{
	int rc;

#ifdef _DEBUG
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
#endif /* _DEBUG */

	/* Run the standard main entry point function... */
	rc = main(__argc, __argv);

#ifdef _DEBUG
	fclose(stdin);
	fclose(stdout);
	fclose(stderr);
#endif /* _DEBUG */

	return rc;
}
