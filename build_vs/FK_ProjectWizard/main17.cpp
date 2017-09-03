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
			MessageBox(NULL, "Visual Studio �̐ݒ���폜����̂ŁA\n�N�����Ă���ꍇ�͏I�����Ă��������B", "Visual Studio �ݒ�ύX", NULL);

			// �p�X�폜���s
			if(!deleteEnvPath("FK_VC17_DIR")) {
				MessageBox(NULL, "���C�u�����̃f�B���N�g���ݒ���폜�ł��܂���ł����B\n���ϐ����m�F���A�蓮�ō폜���Ă��������B", "�f�B���N�g���ݒ莸�s", NULL);
			}
			// �E�B�U�[�h�폜���s
			if(unregist(vcwizPath)) {
				MessageBox(NULL, "Visual Studio 2017 ����v���W�F�N�g�E�B�U�[�h���폜���܂����B", "�E�B�U�[�h�폜����", NULL);
				return 0;
			} else {
				MessageBox(NULL, "Visual Studio 2017 ����̃E�B�U�[�h�폜�Ɏ��s���܂����B\n���ɍ폜�ς݂��������A�ꕔ�̃t�@�C�����c���Ă���\��������܂��B", "�E�B�U�[�h�폜���s", NULL);
				return 1;
			}
		}
	} else {
		MessageBox(NULL, "Visual Studio �̐ݒ��ǉ�����̂ŁA\nVisual Studio ���N�����Ă���ꍇ�͏I�����Ă��������B", "Visual Studio �ݒ�ύX", NULL);

		// �p�X�ǉ����s
		if(!addEnvPath("FK_VC17_DIR", libPath)) {
			MessageBox(NULL, "���C�u�����̃f�B���N�g���ݒ��ǉ��ł��܂���ł����B\n���ϐ����m�F���A�蓮�Œǉ����Ă��������B", "�f�B���N�g���ݒ莸�s", NULL);
		}

		// �E�B�U�[�h�ǉ����s
		if(regist(vcwizPath, libPath)) {
			MessageBox(NULL, "Visual Studio 2017 �Ƀv���W�F�N�g�E�B�U�[�h��o�^���܂����B", "�E�B�U�[�h�o�^����", NULL);
		} else {
			unregist(vcwizPath);
			MessageBox(NULL, "Visual Studio 2017 �ւ̃E�B�U�[�h�o�^�Ɏ��s���܂����B\n�v���W�F�N�g�̍쐬�͎蓮�ōs���Ă��������B", "�E�B�U�[�h�o�^���s", NULL);
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
