#include <windows.h>
#include <shlwapi.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// �C���X�g�[���p�X�̎擾�����{��
bool readRegValue(const char *key, string &instPath)
{
	HKEY hkey;
	DWORD result;
	char tmpStr[MAX_PATH];
	DWORD dataSize = (DWORD)sizeof(tmpStr);
	DWORD dataTypeSize;

	result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, key, 0, KEY_READ, &hkey);
	if(result == ERROR_SUCCESS) {
		if(RegQueryValueEx(hkey, "ProductDir", NULL, &dataTypeSize, (LPBYTE)&tmpStr, &dataSize) == ERROR_SUCCESS) {
			instPath = tmpStr;
			RegCloseKey(hkey);
			return true;
		}
		RegCloseKey(hkey);
	}

	return false;
}

bool addEnvPath(string &dirPath)
{
	HKEY hkey;
	DWORD result;
	const char *tmpStr = dirPath.c_str();
	DWORD dataSize = (DWORD)strlen(tmpStr);
	DWORD dataType = REG_SZ;
	DWORD dwReturnValue; 

	result = RegOpenKeyEx(HKEY_CURRENT_USER, "Environment", 0, KEY_WRITE, &hkey);
	if(result == ERROR_SUCCESS) {
		if(RegSetValueEx(hkey, "FK_VC13_DIR", NULL, dataType, (LPBYTE)tmpStr, dataSize) == ERROR_SUCCESS) {
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

bool deleteEnvPath(void)
{
	HKEY hkey;
	DWORD result;
	DWORD dwReturnValue; 

	result = RegOpenKeyEx(HKEY_CURRENT_USER, "Environment", 0, KEY_WRITE, &hkey);
	if(result == ERROR_SUCCESS) {
		if(RegDeleteValue(hkey, "FK_VC13_DIR") == ERROR_SUCCESS) {
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

// ���W�X�g������VC++�̃p�X���擾
// -1:���W�X�g�����C�b���܂��Ă邺
//  0:�C���X�R����Ăˁ[�񂶂�˂��́H
//  1:���i�ŃQ�b�g�����I
//  2:Express�ŃQ�b�g�����I
int getVCPath(string &instPath)
{
	// x64���̐��i�ł��m�F
	if(readRegValue("SOFTWARE\\Wow6432Node\\Microsoft\\VisualStudio\\12.0\\Setup\\VC", instPath)) {
		return 1;
	}
	// ���i�ł��m�F
	if(readRegValue("SOFTWARE\\Microsoft\\VisualStudio\\12.0\\Setup\\VC", instPath)) {
		return 1;
	}
	// x64����Express���m�F
	if(readRegValue("SOFTWARE\\Wow6432Node\\Microsoft\\VCExpress\\12.0\\Setup\\VC", instPath)) {
		return 2;
	}
	// Express���m�F
	if(readRegValue("SOFTWARE\\Microsoft\\VCExpress\\12.0\\Setup\\VC", instPath)) {
		return 2;
	}

	MessageBox(NULL, "Visual Studio 2013 ���C���X�g�[������Ă��܂���ł����B", "�E�B�U�[�h�o�^���~", NULL);
	return 0;
}

bool regist(const string *vcprojPath, const string &vcwizPath)
{
	BOOL			retVal = TRUE;
	vector<string>	targetList;

	// �v���W�F�N�g�t�H���_�ւ̓o�^
	targetList.clear();
	targetList.push_back("FK_ProjectWizard.ico");
	targetList.push_back("FK_ProjectWizard.vsz");
	targetList.push_back("FK\\FK_ProjectWizard.vsdir");
	for(int j = 0; j < 2; j++) {
		CreateDirectory((vcprojPath[j] + "FK").c_str(), NULL);
		for(int i = 0; i < (int)targetList.size(); i++) {
			CopyFile(targetList[i].c_str(), (vcprojPath[j] + targetList[i]).c_str(), FALSE);
		}
	}

	// �E�B�U�[�h�t�H���_�ւ̓o�^
	targetList.clear();
	targetList.push_back("FK_ProjectWizard");
	targetList.push_back("FK_ProjectWizard\\1041");
	targetList.push_back("FK_ProjectWizard\\1041\\Images");
	targetList.push_back("FK_ProjectWizard\\HTML");
	targetList.push_back("FK_ProjectWizard\\HTML\\1041");
	targetList.push_back("FK_ProjectWizard\\Images");
	targetList.push_back("FK_ProjectWizard\\Scripts");
	targetList.push_back("FK_ProjectWizard\\Scripts\\1041");
	targetList.push_back("FK_ProjectWizard\\Templates");
	targetList.push_back("FK_ProjectWizard\\Templates\\1041");

	for(int i = 0; i < (int)targetList.size(); i++) {
		CreateDirectory((vcwizPath + targetList[i]).c_str(), NULL);
	}

	targetList.clear();
	targetList.push_back("FK_ProjectWizard\\FK_default.vcxproj");
	targetList.push_back("FK_ProjectWizard\\1041\\NewStyles.css");
	targetList.push_back("FK_ProjectWizard\\1041\\Images\\DottedHori.gif");
	targetList.push_back("FK_ProjectWizard\\1041\\Images\\DottedVert.gif");
	targetList.push_back("FK_ProjectWizard\\1041\\Images\\spacer.gif");
	targetList.push_back("FK_ProjectWizard\\HTML\\1041\\default.htm");
	targetList.push_back("FK_ProjectWizard\\Images\\FK_ProjectWizard.gif");
	targetList.push_back("FK_ProjectWizard\\Images\\FK_ProjectWizard_Background.gif");
	targetList.push_back("FK_ProjectWizard\\Scripts\\1041\\default.js");
	targetList.push_back("FK_ProjectWizard\\Templates\\1041\\main.cpp");
	targetList.push_back("FK_ProjectWizard\\Templates\\1041\\Templates.inf");

	for(int i = 0; i < (int)targetList.size(); i++) {
		retVal &= CopyFile(targetList[i].c_str(), (vcwizPath + targetList[i]).c_str(), FALSE);
	}

	return (retVal == TRUE);
}

bool unregist(const string *vcprojPath, const string &vcwizPath)
{
	BOOL			retVal = TRUE;
	vector<string>	targetList;

	targetList.clear();
	targetList.push_back("FK_ProjectWizard\\FK_default.vcxproj");
	targetList.push_back("FK_ProjectWizard\\1041\\NewStyles.css");
	targetList.push_back("FK_ProjectWizard\\1041\\Images\\DottedHori.gif");
	targetList.push_back("FK_ProjectWizard\\1041\\Images\\DottedVert.gif");
	targetList.push_back("FK_ProjectWizard\\1041\\Images\\spacer.gif");
	targetList.push_back("FK_ProjectWizard\\HTML\\1041\\default.htm");
	targetList.push_back("FK_ProjectWizard\\Images\\FK_ProjectWizard.gif");
	targetList.push_back("FK_ProjectWizard\\Images\\FK_ProjectWizard_Background.gif");
	targetList.push_back("FK_ProjectWizard\\Scripts\\1041\\default.js");
	targetList.push_back("FK_ProjectWizard\\Templates\\1041\\main.cpp");
	targetList.push_back("FK_ProjectWizard\\Templates\\1041\\Templates.inf");

	for(int i = 0; i < (int)targetList.size(); i++) {
		retVal &= DeleteFile((vcwizPath + targetList[i]).c_str());
	}

	targetList.clear();
	targetList.push_back("FK_ProjectWizard");
	targetList.push_back("FK_ProjectWizard\\1041");
	targetList.push_back("FK_ProjectWizard\\1041\\Images");
	targetList.push_back("FK_ProjectWizard\\HTML");
	targetList.push_back("FK_ProjectWizard\\HTML\\1041");
	targetList.push_back("FK_ProjectWizard\\Images");
	targetList.push_back("FK_ProjectWizard\\Scripts");
	targetList.push_back("FK_ProjectWizard\\Scripts\\1041");
	targetList.push_back("FK_ProjectWizard\\Templates");
	targetList.push_back("FK_ProjectWizard\\Templates\\1041");

	for(int i = (int)targetList.size()-1; i >= 0; i--) {
		retVal &= RemoveDirectory((vcwizPath + targetList[i]).c_str());
	}

	targetList.clear();
	targetList.push_back("FK_ProjectWizard.ico");
	targetList.push_back("FK_ProjectWizard.vsz");
	targetList.push_back("FK\\FK_ProjectWizard.vsdir");

	for(int j = 0; j < 2; j++) {
		for(int i = 0; i < (int)targetList.size(); i++) {
			DeleteFile((vcprojPath[j] + targetList[i]).c_str());
		}
		RemoveDirectory((vcprojPath[j] + "FK").c_str());
	}

	return (retVal == TRUE);
}

int main(int argc, char *argv[])
{
	string	instPath;
	int		edition;

	edition = getVCPath(instPath);
	if(edition <= 0) return 2;

	string	vcprojPath[2], vcwizPath;

	vcprojPath[0] = instPath + "vcprojects_WDExpress\\";
	vcprojPath[1] = instPath + "vcprojects\\";
	vcwizPath = instPath + "VCWizards\\";

	string	libPath;
	char	modulePath[MAX_PATH];
	DWORD	pathRes = GetModuleFileName(NULL, modulePath, MAX_PATH);
	if(pathRes == 0) {
		MessageBox(NULL, "���蓾�Ȃ����Ԃ��������܂����B", "�A���G�i�C�U�[", NULL);
		return -1;
	}
	libPath = modulePath;
	libPath = libPath.substr(0, libPath.find_last_of('\\'));
	libPath = libPath.substr(0, libPath.find_last_of('\\'));

	if(argc >= 2) {
		if(strcmp("-u", argv[1]) == 0) {
			MessageBox(NULL, "Visual Studio �̐ݒ���폜����̂ŁA\n�N�����Ă���ꍇ�͏I�����Ă��������B", "Visual Studio �ݒ�ύX", NULL);

			// �p�X�폜���s
			if(!deleteEnvPath()) {
				MessageBox(NULL, "���C�u�����̃f�B���N�g���ݒ���폜�ł��܂���ł����B\n���ϐ����m�F���A�蓮�ō폜���Ă��������B", "�f�B���N�g���ݒ莸�s", NULL);
			}
			// �E�B�U�[�h�폜���s
			if(unregist(vcprojPath, vcwizPath)) {
				MessageBox(NULL, "Visual Studio 2013 ����v���W�F�N�g�E�B�U�[�h���폜���܂����B", "�E�B�U�[�h�폜����", NULL);
				return 0;
			} else {
				MessageBox(NULL, "Visual Studio 2013 ����̃E�B�U�[�h�폜�Ɏ��s���܂����B\n���ɍ폜�ς݂��������A�ꕔ�̃t�@�C�����c���Ă���\��������܂��B", "�E�B�U�[�h�폜���s", NULL);
				return 1;
			}
		}
	} else {
		MessageBox(NULL, "Visual Studio �̐ݒ��ǉ�����̂ŁA\nVisual Studio ���N�����Ă���ꍇ�͏I�����Ă��������B", "Visual Studio �ݒ�ύX", NULL);

		// �p�X�ǉ����s
		if(!addEnvPath(libPath)) {
			MessageBox(NULL, "���C�u�����̃f�B���N�g���ݒ��ǉ��ł��܂���ł����B\n���ϐ����m�F���A�蓮�Œǉ����Ă��������B", "�f�B���N�g���ݒ莸�s", NULL);
		}

		// �E�B�U�[�h�ǉ����s
		if(regist(vcprojPath, vcwizPath)) {
			MessageBox(NULL, "Visual Studio 2013 �Ƀv���W�F�N�g�E�B�U�[�h��o�^���܂����B", "�E�B�U�[�h�o�^����", NULL);
		} else {
			unregist(vcprojPath, vcwizPath);
			MessageBox(NULL, "Visual Studio 2013 �ւ̃E�B�U�[�h�o�^�Ɏ��s���܂����B\n�v���W�F�N�g�̍쐬�͎蓮�ōs���Ă��������B", "�E�B�U�[�h�o�^���s", NULL);
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
