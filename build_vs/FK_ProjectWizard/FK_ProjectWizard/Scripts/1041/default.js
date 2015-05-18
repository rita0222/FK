
function OnFinish(selProj, selObj)
{
	try
	{
		var strProjectPath = wizard.FindSymbol('PROJECT_PATH');
		var strProjectName = wizard.FindSymbol('PROJECT_NAME');

		selProj = CreateCustomProject(strProjectName, strProjectPath);
		AddConfig(selProj, strProjectName);
		AddFilters(selProj);

		var InfFile = CreateCustomInfFile();
		AddFilesToCustomProj(selProj, strProjectName, strProjectPath, InfFile);
		PchSettings(selProj);
		InfFile.Delete();

		selProj.Object.Save();
	}
	catch(e)
	{
		if (e.description.length != 0)
			SetErrorInfo(e);
		return e.number
	}
}

function CreateCustomProject(strProjectName, strProjectPath)
{
	try
	{
		var strProjTemplatePath = wizard.FindSymbol('PROJECT_TEMPLATE_PATH');
		var strProjTemplate = '';
		strProjTemplate = strProjTemplatePath + '\\default.vcproj';

		var Solution = dte.Solution;
		var strSolutionName = "";
		if (wizard.FindSymbol("CLOSE_SOLUTION"))
		{
			Solution.Close();
			strSolutionName = wizard.FindSymbol("VS_SOLUTION_NAME");
			if (strSolutionName.length)
			{
				var strSolutionPath = strProjectPath.substr(0, strProjectPath.length - strProjectName.length);
				Solution.Create(strSolutionPath, strSolutionName);
			}
		}

		var strProjectNameWithExt = '';
		strProjectNameWithExt = strProjectName + '.vcproj';

		var oTarget = wizard.FindSymbol("TARGET");
		var prj;
		if (wizard.FindSymbol("WIZARD_TYPE") == vsWizardAddSubProject)  // vsWizardAddSubProject
		{
			var prjItem = oTarget.AddFromTemplate(strProjTemplate, strProjectNameWithExt);
			prj = prjItem.SubProject;
		}
		else
		{
			prj = oTarget.AddFromTemplate(strProjTemplate, strProjectPath, strProjectNameWithExt);
		}
		var fxtarget = wizard.FindSymbol("TARGET_FRAMEWORK_VERSION");
		if (fxtarget != null && fxtarget != "")
		{
		    fxtarget = fxtarget.split('.', 2);
		    if (fxtarget.length == 2)
			prj.Object.TargetFrameworkVersion = parseInt(fxtarget[0]) * 0x10000 + parseInt(fxtarget[1])
		}
		return prj;
	}
	catch(e)
	{
		throw e;
	}
}

function AddFilters(proj)
{
	try
	{
		// �v���W�F�N�g�Ƀt�H���_��ǉ�����
		var strSrcFilter = wizard.FindSymbol('SOURCE_FILTER');
		var srcGroup = proj.Object.AddFilter('�\�[�X �t�@�C��');
		srcGroup.Filter = strSrcFilter;

		var strHeadFilter = wizard.FindSymbol('HEADER_FILTER');
		var headGroup = proj.Object.AddFilter('�w�b�_�[ �t�@�C��');
		headGroup.Filter = strHeadFilter;

		var rcFilter = wizard.FindSymbol('RESOURCE_FILTER');
		var rcGroup = proj.Object.AddFilter('���\�[�X �t�@�C��');
		rcGroup.Filter = rcFilter;
	}
	catch(e)
	{
		throw e;
	}
}

function AddConfig(proj, strProjectName)
{
	try
	{
	    var libFK_GL = "TinyFK.lib FK2_base.lib FK2_fltkWin.lib FK2_fltkErr.lib ";
	    var libFK_GL_D = "TinyFK_d.lib FK2_base_d.lib FK2_fltkWin_d.lib FK2_fltkErr_d.lib ";
	    var libFLTK = "fltkgl.lib fltkjpeg.lib fltkpng.lib fltkimages.lib fltkforms.lib fltk.lib fltkz.lib ";
	    var libMisc = "freetype2MT.lib imdkcv.lib ";
	    var libOgg = "libvorbisfile.lib libvorbis.lib libogg.lib ";
	    var libAL = "EFX-Util.lib alut.lib OpenAL32.lib ";
	    var libCgGL = "cgGL.lib cg.lib ";
	    var libGL = "glu32.lib opengl32.lib ";
	    var libWin32 = "imm32.lib winmm.lib wsock32.lib comctl32.lib ";

        // Debug �\���ݒ�
        var config = proj.Object.Configurations('Debug');
        config.IntermediateDirectory = '$(ConfigurationName)';
        config.OutputDirectory = '.\\_exe';
        config.ConfigurationType = '1';
        config.CharacterSet = '2';

        var CLTool = config.Tools('VCCLCompilerTool');
        // TODO: �R���p�C���ݒ��ǉ�����
        CLTool.Optimization="0";
        if(wizard.FindSymbol('CONSOLE_CHECKBOX')) {
            CLTool.PreprocessorDefinitions="WIN32;_DEBUG;_CONSOLE";
        } else {
            CLTool.PreprocessorDefinitions="WIN32;_DEBUG;_WINDOWS";
        }
        CLTool.MinimalRebuild="true";
        CLTool.BasicRuntimeChecks="3";
        CLTool.RuntimeLibrary="1";
        CLTool.UsePrecompiledHeader="0";
        CLTool.WarningLevel="3";
        CLTool.DebugInformationFormat="4";

        var LinkTool = config.Tools('VCLinkerTool');
        // TODO: �����J�ݒ��ǉ�����
        LinkTool.OutputFile="$(OutDir)\\$(ProjectName)_d.exe"
        LinkTool.LinkIncremental="2";
        LinkTool.GenerateDebugInformation="true";
        if(wizard.FindSymbol('CONSOLE_CHECKBOX')) {
            LinkTool.SubSystem="1";
        } else {
            LinkTool.SubSystem="2";
        }
        LinkTool.TargetMachine="1";
        LinkTool.IgnoreDefaultLibraryNames="LIBCMT";
        LinkTool.AdditionalDependencies = "";
        if(wizard.FindSymbol('GUI_LISTBOX') == "FLTK") {
            LinkTool.AdditionalDependencies += libFK_GL_D + libFLTK + libMisc;
        }
        if(wizard.FindSymbol('Ogg_CHECKBOX')) {
            LinkTool.AdditionalDependencies += libOgg;
        }
        if(wizard.FindSymbol('AL_CHECKBOX')) {
            LinkTool.AdditionalDependencies += libAL;
        }
        if(wizard.FindSymbol('Cg_CHECKBOX')) {
            LinkTool.AdditionalDependencies += libCgGL;
        }
        if(wizard.FindSymbol('GUI_LISTBOX') == "FLTK") {
            LinkTool.AdditionalDependencies += libGL + libWin32;
        }

        // Release �\���ݒ�
        var config = proj.Object.Configurations('Release');
        config.IntermediateDirectory = '$(ConfigurationName)';
        config.OutputDirectory = '.\\_exe';
        config.ConfigurationType = '1';
        config.CharacterSet = '2';

        var CLTool = config.Tools('VCCLCompilerTool');
        // TODO: �R���p�C���ݒ��ǉ�����
        CLTool.Optimization="2";
        CLTool.EnableIntrinsicFunctions="true";
        if(wizard.FindSymbol('CONSOLE_CHECKBOX')) {
            CLTool.PreprocessorDefinitions="WIN32;NDEBUG;_CONSOLE";
        } else {
            CLTool.PreprocessorDefinitions="WIN32;NDEBUG;_WINDOWS";
        }
        CLTool.RuntimeLibrary="0";
        CLTool.EnableFunctionLevelLinking="true";
        CLTool.UsePrecompiledHeader="0";
        CLTool.WarningLevel="3";
        CLTool.DebugInformationFormat="3";

        var LinkTool = config.Tools('VCLinkerTool');
        // TODO: �����J�ݒ��ǉ�����
        LinkTool.OutputFile="$(OutDir)\\$(ProjectName).exe"
        LinkTool.LinkIncremental="1";
        LinkTool.GenerateDebugInformation="true";
        if(wizard.FindSymbol('CONSOLE_CHECKBOX')) {
            LinkTool.SubSystem="1";
        } else {
            LinkTool.SubSystem="2";
        }
        LinkTool.OptimizeReferences="2";
        LinkTool.EnableCOMDATFolding="2";
        LinkTool.TargetMachine="1";
        LinkTool.AdditionalDependencies = "";
        if(wizard.FindSymbol('GUI_LISTBOX') == "FLTK") {
            LinkTool.AdditionalDependencies += libFK_GL + libFLTK + libMisc;
        }
        if(wizard.FindSymbol('Ogg_CHECKBOX')) {
            LinkTool.AdditionalDependencies += libOgg;
        }
        if(wizard.FindSymbol('AL_CHECKBOX')) {
            LinkTool.AdditionalDependencies += libAL;
        }
        if(wizard.FindSymbol('Cg_CHECKBOX')) {
            LinkTool.AdditionalDependencies += libCgGL;
        }
        if(wizard.FindSymbol('GUI_LISTBOX') == "FLTK") {
            LinkTool.AdditionalDependencies += libGL + libWin32;
        }
	}
	catch(e)
	{
		throw e;
	}
}

function PchSettings(proj)
{
	// TODO: pch �ݒ���w�肷��
}

function DelFile(fso, strWizTempFile)
{
	try
	{
		if (fso.FileExists(strWizTempFile))
		{
			var tmpFile = fso.GetFile(strWizTempFile);
			tmpFile.Delete();
		}
	}
	catch(e)
	{
		throw e;
	}
}

function CreateCustomInfFile()
{
	try
	{
		var fso, TemplatesFolder, TemplateFiles, strTemplate;
		fso = new ActiveXObject('Scripting.FileSystemObject');

		var TemporaryFolder = 2;
		var tfolder = fso.GetSpecialFolder(TemporaryFolder);
		var strTempFolder = tfolder.Drive + '\\' + tfolder.Name;

		var strWizTempFile = strTempFolder + "\\" + fso.GetTempName();

		var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');
		var strInfFile = strTemplatePath + '\\Templates.inf';
		wizard.RenderTemplate(strInfFile, strWizTempFile);

		var WizTempFile = fso.GetFile(strWizTempFile);
		return WizTempFile;
	}
	catch(e)
	{
		throw e;
	}
}

function GetTargetName(strName, strProjectName)
{
	try
	{
		// TODO: �e���v���[�g �t�@�C��������ɒ�o���ꂽ�t�@�C���̖��O��ݒ肷��
		var strTarget = strName;

		return strTarget;
	}
	catch(e)
	{
		throw e;
	}
}

function AddFilesToCustomProj(proj, strProjectName, strProjectPath, InfFile)
{
	try
	{
		var projItems = proj.ProjectItems

		var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');

		var strTpl = '';
		var strName = '';

		var strTextStream = InfFile.OpenAsTextStream(1, -2);
		while (!strTextStream.AtEndOfStream)
		{
			strTpl = strTextStream.ReadLine();
			if (strTpl != '')
			{
				strName = strTpl;
				var strTarget = GetTargetName(strName, strProjectName);
				var strTemplate = strTemplatePath + '\\' + strTpl;
				var strFile = strProjectPath + '\\' + strTarget;

				var bCopyOnly = false;  //"true" �́A�t�@�C�����v���W�F�N�g�ɒ�o/�ǉ����邱�ƂȂ��ɁAaddingstrTemplate ���� strTarget �Ƀt�@�C�����R�s�[���܂��B
				var strExt = strName.substr(strName.lastIndexOf("."));
				if(strExt==".bmp" || strExt==".ico" || strExt==".gif" || strExt==".rtf" || strExt==".css")
					bCopyOnly = true;
				wizard.RenderTemplate(strTemplate, strFile, bCopyOnly);
				proj.Object.AddFile(strFile);
			}
		}
		strTextStream.Close();
	}
	catch(e)
	{
		throw e;
	}
}


// SIG // Begin signature block
// SIG // MIIj7gYJKoZIhvcNAQcCoIIj3zCCI9sCAQExCzAJBgUr
// SIG // DgMCGgUAMGcGCisGAQQBgjcCAQSgWTBXMDIGCisGAQQB
// SIG // gjcCAR4wJAIBAQQQEODJBs441BGiowAQS9NQkAIBAAIB
// SIG // AAIBAAIBAAIBADAhMAkGBSsOAwIaBQAEFEwA9tAsqgNq
// SIG // ChpduVRqw/WODhKOoIIe4TCCBBIwggL6oAMCAQICDwDB
// SIG // AIs8PIgR0T72Y+zfQDANBgkqhkiG9w0BAQQFADBwMSsw
// SIG // KQYDVQQLEyJDb3B5cmlnaHQgKGMpIDE5OTcgTWljcm9z
// SIG // b2Z0IENvcnAuMR4wHAYDVQQLExVNaWNyb3NvZnQgQ29y
// SIG // cG9yYXRpb24xITAfBgNVBAMTGE1pY3Jvc29mdCBSb290
// SIG // IEF1dGhvcml0eTAeFw05NzAxMTAwNzAwMDBaFw0yMDEy
// SIG // MzEwNzAwMDBaMHAxKzApBgNVBAsTIkNvcHlyaWdodCAo
// SIG // YykgMTk5NyBNaWNyb3NvZnQgQ29ycC4xHjAcBgNVBAsT
// SIG // FU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEhMB8GA1UEAxMY
// SIG // TWljcm9zb2Z0IFJvb3QgQXV0aG9yaXR5MIIBIjANBgkq
// SIG // hkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAqQK9wXDmO/JO
// SIG // Gyifl3heMOqiqY0lX/j+lUyjt/6doiA+fFGim6KPYDJr
// SIG // 0UJkee6sdslU2vLrnIYcj5+EZrPFa3piI9YdPN4PAZLo
// SIG // lsS/LWaammgmmdA6LL8MtVgmwUbnCj44liypKDmo7EmD
// SIG // QuOED7uabFVhrIJ8oWAtd0zpmbRkO5pQHDEIJBSfqeeR
// SIG // KxjmPZhjFGBYBWWfHTdSh/en75QCxhvTv1VFs4mAvzrs
// SIG // VJROrv2nem10Tq8YzJYJKCEAV5BgaTe7SxIHPFb/W/uk
// SIG // ZgoIptKBVlfvtjteFoF3BNr2vq6Alf6wzX/WpxpyXDzK
// SIG // vPAIoyIwswaFybMgdxOF3wIDAQABo4GoMIGlMIGiBgNV
// SIG // HQEEgZowgZeAEFvQcO9pcp4jUX4Usk2O/8uhcjBwMSsw
// SIG // KQYDVQQLEyJDb3B5cmlnaHQgKGMpIDE5OTcgTWljcm9z
// SIG // b2Z0IENvcnAuMR4wHAYDVQQLExVNaWNyb3NvZnQgQ29y
// SIG // cG9yYXRpb24xITAfBgNVBAMTGE1pY3Jvc29mdCBSb290
// SIG // IEF1dGhvcml0eYIPAMEAizw8iBHRPvZj7N9AMA0GCSqG
// SIG // SIb3DQEBBAUAA4IBAQCV6AvAjfOXGDXtuAEk2HcR81xg
// SIG // Mp+eC8s+BZGIj8k65iHy8FeTLLWgR8hi7/zXzDs7Wqk2
// SIG // VGn+JG0/ycyq3gV83TGNPZ8QcGq7/hJPGGnA/NBD4xFa
// SIG // IE/qYnuvqhnIKzclLb5loRKKJQ9jo/dUHPkhydYV81Ks
// SIG // bkMyB/2CF/jlZ2wNUfa98VLHvefEMPwgMQmIHZUpGk3V
// SIG // HQKl8YDgA7Rb9LHdyFfuZUnHUlS2tAMoEv+Q1vAIj364
// SIG // l8WrNyzkeuSod+N2oADQaj/B0jaK4EESqDVqG2rbNeHU
// SIG // HATkqEUEyFozOG5NHA1itwqijNPVVD9GzRxVpnDbEjqH
// SIG // k3Wfp9KgMIIEEjCCAvqgAwIBAgIPAMEAizw8iBHRPvZj
// SIG // 7N9AMA0GCSqGSIb3DQEBBAUAMHAxKzApBgNVBAsTIkNv
// SIG // cHlyaWdodCAoYykgMTk5NyBNaWNyb3NvZnQgQ29ycC4x
// SIG // HjAcBgNVBAsTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEh
// SIG // MB8GA1UEAxMYTWljcm9zb2Z0IFJvb3QgQXV0aG9yaXR5
// SIG // MB4XDTk3MDExMDA3MDAwMFoXDTIwMTIzMTA3MDAwMFow
// SIG // cDErMCkGA1UECxMiQ29weXJpZ2h0IChjKSAxOTk3IE1p
// SIG // Y3Jvc29mdCBDb3JwLjEeMBwGA1UECxMVTWljcm9zb2Z0
// SIG // IENvcnBvcmF0aW9uMSEwHwYDVQQDExhNaWNyb3NvZnQg
// SIG // Um9vdCBBdXRob3JpdHkwggEiMA0GCSqGSIb3DQEBAQUA
// SIG // A4IBDwAwggEKAoIBAQCpAr3BcOY78k4bKJ+XeF4w6qKp
// SIG // jSVf+P6VTKO3/p2iID58UaKboo9gMmvRQmR57qx2yVTa
// SIG // 8uuchhyPn4Rms8VremIj1h083g8BkuiWxL8tZpqaaCaZ
// SIG // 0Dosvwy1WCbBRucKPjiWLKkoOajsSYNC44QPu5psVWGs
// SIG // gnyhYC13TOmZtGQ7mlAcMQgkFJ+p55ErGOY9mGMUYFgF
// SIG // ZZ8dN1KH96fvlALGG9O/VUWziYC/OuxUlE6u/ad6bXRO
// SIG // rxjMlgkoIQBXkGBpN7tLEgc8Vv9b+6RmCgim0oFWV++2
// SIG // O14WgXcE2va+roCV/rDNf9anGnJcPMq88AijIjCzBoXJ
// SIG // syB3E4XfAgMBAAGjgagwgaUwgaIGA1UdAQSBmjCBl4AQ
// SIG // W9Bw72lyniNRfhSyTY7/y6FyMHAxKzApBgNVBAsTIkNv
// SIG // cHlyaWdodCAoYykgMTk5NyBNaWNyb3NvZnQgQ29ycC4x
// SIG // HjAcBgNVBAsTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEh
// SIG // MB8GA1UEAxMYTWljcm9zb2Z0IFJvb3QgQXV0aG9yaXR5
// SIG // gg8AwQCLPDyIEdE+9mPs30AwDQYJKoZIhvcNAQEEBQAD
// SIG // ggEBAJXoC8CN85cYNe24ASTYdxHzXGAyn54Lyz4FkYiP
// SIG // yTrmIfLwV5MstaBHyGLv/NfMOztaqTZUaf4kbT/JzKre
// SIG // BXzdMY09nxBwarv+Ek8YacD80EPjEVogT+pie6+qGcgr
// SIG // NyUtvmWhEoolD2Oj91Qc+SHJ1hXzUqxuQzIH/YIX+OVn
// SIG // bA1R9r3xUse958Qw/CAxCYgdlSkaTdUdAqXxgOADtFv0
// SIG // sd3IV+5lScdSVLa0AygS/5DW8AiPfriXxas3LOR65Kh3
// SIG // 43agANBqP8HSNorgQRKoNWobats14dQcBOSoRQTIWjM4
// SIG // bk0cDWK3CqKM09VUP0bNHFWmcNsSOoeTdZ+n0qAwggRg
// SIG // MIIDTKADAgECAgouqxHcUP9cncvAMAkGBSsOAwIdBQAw
// SIG // cDErMCkGA1UECxMiQ29weXJpZ2h0IChjKSAxOTk3IE1p
// SIG // Y3Jvc29mdCBDb3JwLjEeMBwGA1UECxMVTWljcm9zb2Z0
// SIG // IENvcnBvcmF0aW9uMSEwHwYDVQQDExhNaWNyb3NvZnQg
// SIG // Um9vdCBBdXRob3JpdHkwHhcNMDcwODIyMjIzMTAyWhcN
// SIG // MTIwODI1MDcwMDAwWjB5MQswCQYDVQQGEwJVUzETMBEG
// SIG // A1UECBMKV2FzaGluZ3RvbjEQMA4GA1UEBxMHUmVkbW9u
// SIG // ZDEeMBwGA1UEChMVTWljcm9zb2Z0IENvcnBvcmF0aW9u
// SIG // MSMwIQYDVQQDExpNaWNyb3NvZnQgQ29kZSBTaWduaW5n
// SIG // IFBDQTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoC
// SIG // ggEBALd5fdZds0U5qDSsMdr5JTVJd8D7H57HRXHv0Ubo
// SIG // 1IzDa0xSYvSZAsNN2ElsLyQ+Zb/OI7cLSLd/dd1FvaqP
// SIG // DlDFJSvyoOcNIx/RQST6YpnPGUWlk0ofmc2zLyLDSi18
// SIG // b9kVHjuMORA53b0p9GY7LQEy//4nSKa1bAGHnPu6smN/
// SIG // gvlcoIGEhY6w8riUo884plCFFyeHTt0w9gA99Mb5PYG+
// SIG // hu1sOacuNPa0Lq8KfWKReGacmHMNhq/yxPMguU8SjWPL
// SIG // LNkyRRnuu0qWO1BTGM5mUXmqrYfIVj6fglCIbgWxNcF7
// SIG // JL1SZj2ZTswrfjNuhEcG0Z7QSoYCboYApMCH31MCAwEA
// SIG // AaOB+jCB9zATBgNVHSUEDDAKBggrBgEFBQcDAzCBogYD
// SIG // VR0BBIGaMIGXgBBb0HDvaXKeI1F+FLJNjv/LoXIwcDEr
// SIG // MCkGA1UECxMiQ29weXJpZ2h0IChjKSAxOTk3IE1pY3Jv
// SIG // c29mdCBDb3JwLjEeMBwGA1UECxMVTWljcm9zb2Z0IENv
// SIG // cnBvcmF0aW9uMSEwHwYDVQQDExhNaWNyb3NvZnQgUm9v
// SIG // dCBBdXRob3JpdHmCDwDBAIs8PIgR0T72Y+zfQDAPBgNV
// SIG // HRMBAf8EBTADAQH/MB0GA1UdDgQWBBTMHc52AHBbr/Ha
// SIG // xE6aUUQuo0Rj8DALBgNVHQ8EBAMCAYYwCQYFKw4DAh0F
// SIG // AAOCAQEAe6uufkom8s68TnSiWCd0KnWzhv2rTJR4AE3p
// SIG // yusY3GnFDqJ88wJDxsqHzPhTzMKfvVZv8GNEqUQA7pbI
// SIG // mtUcuAufGQ2U19oerSl97+2mc6yP3jmOPZhqvDht0oiv
// SIG // I/3f6dZpCZGIvf7hALs08/d8+RASLgXrKZaTQmsocbc4
// SIG // j+AHDcldaM29gEFrZqi7t7uONMryAxB8evXS4ELfe/7h
// SIG // 4az+9t/VDbNw1pLjT7Y4onwt1D3bNAtiNwKfgWojifZc
// SIG // Y4+wWrs512CMVYQaM/U7mKCCDKJfi7Mst6Gly6vaILa/
// SIG // MBmFIBQNKrxS9EHgXjDjkihph8Fw4vOnq86AQnJ2DjCC
// SIG // BGowggNSoAMCAQICCmEPeE0AAAAAAAMwDQYJKoZIhvcN
// SIG // AQEFBQAweTELMAkGA1UEBhMCVVMxEzARBgNVBAgTCldh
// SIG // c2hpbmd0b24xEDAOBgNVBAcTB1JlZG1vbmQxHjAcBgNV
// SIG // BAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEjMCEGA1UE
// SIG // AxMaTWljcm9zb2Z0IENvZGUgU2lnbmluZyBQQ0EwHhcN
// SIG // MDcwODIzMDAyMzEzWhcNMDkwMjIzMDAzMzEzWjB0MQsw
// SIG // CQYDVQQGEwJVUzETMBEGA1UECBMKV2FzaGluZ3RvbjEQ
// SIG // MA4GA1UEBxMHUmVkbW9uZDEeMBwGA1UEChMVTWljcm9z
// SIG // b2Z0IENvcnBvcmF0aW9uMR4wHAYDVQQDExVNaWNyb3Nv
// SIG // ZnQgQ29ycG9yYXRpb24wggEiMA0GCSqGSIb3DQEBAQUA
// SIG // A4IBDwAwggEKAoIBAQCi2wqNz8LBSZvNqjo0rSNZa9ts
// SIG // viEit5TI6q6/xtUmwjIRi7zaXSz7NlYeFSuujw3dFKNu
// SIG // KEx/Fj9BrI1AsUaIDdmBlK2XBtBXRHZc6vH8DuJ/dKMz
// SIG // y3Tl7+NhoX4Dt0X/1T4S1bDKXg3Qe/K3Ew38YGoohXWM
// SIG // t628hegXtJC+9Ra2Yl3tEd867iFbi6+Ac8NF45WJd2Cb
// SIG // 5613wTeNMxQvE9tiya4aqU+YZ63UIDkwceCNZ0bixhz0
// SIG // DVB0QS/oBSRqIWtJsJLEsjnHQqVtXBhKq4/XjoM+eApH
// SIG // 2KSyhCPD4vJ7ZrFKdL0mQUucYRRgTjDIgvPQC3B87lVN
// SIG // d9IIVXaBAgMBAAGjgfgwgfUwDgYDVR0PAQH/BAQDAgbA
// SIG // MB0GA1UdDgQWBBTzIUCOfFH4VEuY5RfXaoM0BS4m6DAT
// SIG // BgNVHSUEDDAKBggrBgEFBQcDAzAfBgNVHSMEGDAWgBTM
// SIG // Hc52AHBbr/HaxE6aUUQuo0Rj8DBEBgNVHR8EPTA7MDmg
// SIG // N6A1hjNodHRwOi8vY3JsLm1pY3Jvc29mdC5jb20vcGtp
// SIG // L2NybC9wcm9kdWN0cy9DU1BDQS5jcmwwSAYIKwYBBQUH
// SIG // AQEEPDA6MDgGCCsGAQUFBzAChixodHRwOi8vd3d3Lm1p
// SIG // Y3Jvc29mdC5jb20vcGtpL2NlcnRzL0NTUENBLmNydDAN
// SIG // BgkqhkiG9w0BAQUFAAOCAQEAQFdvU2eeIIM0AQ7mF0s8
// SIG // revYgX/uDXl0d0+XRxjzABVpfttikKL9Z6Gc5Cgp+lXX
// SIG // mf5Qv14Js7mm7YLzmB5vWfr18eEM04sIPhYXINHAtUVH
// SIG // CCZgVwlLlPAIzLpNbvDiSBIoNYshct9ftq9pEiSU7uk0
// SIG // Cdt+bm+SClLKKkxJqjIshuihzF0mvLw84Fuygwu6NRxP
// SIG // hEVH/7uUoVkHqZbdeL1Xf6WnTszyrZyaQeLLXCQ+3H80
// SIG // R072z8h7neu2yZxjFFOvrZrv17/PoKGrlcp6K4cswMfZ
// SIG // /GwD2r84rfHRXBkXD8D3yoCmEAga3ZAj57ChTD7qsBEm
// SIG // eA7BLLmka8ePPDCCBJ0wggOFoAMCAQICCmFHUroAAAAA
// SIG // AAQwDQYJKoZIhvcNAQEFBQAweTELMAkGA1UEBhMCVVMx
// SIG // EzARBgNVBAgTCldhc2hpbmd0b24xEDAOBgNVBAcTB1Jl
// SIG // ZG1vbmQxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3Jh
// SIG // dGlvbjEjMCEGA1UEAxMaTWljcm9zb2Z0IFRpbWVzdGFt
// SIG // cGluZyBQQ0EwHhcNMDYwOTE2MDE1MzAwWhcNMTEwOTE2
// SIG // MDIwMzAwWjCBpjELMAkGA1UEBhMCVVMxEzARBgNVBAgT
// SIG // Cldhc2hpbmd0b24xEDAOBgNVBAcTB1JlZG1vbmQxHjAc
// SIG // BgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEnMCUG
// SIG // A1UECxMebkNpcGhlciBEU0UgRVNOOkQ4QTktQ0ZDQy01
// SIG // NzlDMScwJQYDVQQDEx5NaWNyb3NvZnQgVGltZXN0YW1w
// SIG // aW5nIFNlcnZpY2UwggEiMA0GCSqGSIb3DQEBAQUAA4IB
// SIG // DwAwggEKAoIBAQCbbdyGUegyOzc6liWyz2/uYbVB0hg7
// SIG // Wp14Z7r4H9kIVZKIfuNBU/rsKFT+tdr+cDuVJ0h+Q6Ay
// SIG // LyaBSvICdnfIyan4oiFYfg29Adokxv5EEQU1OgGo6lQK
// SIG // MyyH0n5Bs+gJ2bC+45klprwl7dfTjtv0t20bSQvm08OH
// SIG // bu5GyX/zbevngx6oU0Y/yiR+5nzJLPt5FChFwE82a1Ma
// SIG // p4az5/zhwZ9RCdu8pbv+yocJ9rcyGb7hSlG8vHysLJVq
// SIG // l3PqclehnIuG2Ju9S/wnM8FtMqzgaBjYbjouIkPR+Y/t
// SIG // 8QABDWTAyaPdD/HI6VTKEf/ceCk+HaxYwNvfqtyuZRvT
// SIG // nbxnAgMBAAGjgfgwgfUwHQYDVR0OBBYEFE8YiYrSygB4
// SIG // xuxZDQ/9fMTBIoDeMB8GA1UdIwQYMBaAFG/oTj+XuTSr
// SIG // S4aPvJzqrDtBQ8bQMEQGA1UdHwQ9MDswOaA3oDWGM2h0
// SIG // dHA6Ly9jcmwubWljcm9zb2Z0LmNvbS9wa2kvY3JsL3By
// SIG // b2R1Y3RzL3RzcGNhLmNybDBIBggrBgEFBQcBAQQ8MDow
// SIG // OAYIKwYBBQUHMAKGLGh0dHA6Ly93d3cubWljcm9zb2Z0
// SIG // LmNvbS9wa2kvY2VydHMvdHNwY2EuY3J0MBMGA1UdJQQM
// SIG // MAoGCCsGAQUFBwMIMA4GA1UdDwEB/wQEAwIGwDANBgkq
// SIG // hkiG9w0BAQUFAAOCAQEANyce9YxA4PZlJj5kxJC8PuNX
// SIG // hd1DDUCEZ76HqCra3LQ2IJiOM3wuX+BQe2Ex8xoT3oS9
// SIG // 6mkcWHyzG5PhCCeBRbbUcMoUt1+6V+nUXtA7Q6q3P7ba
// SIG // YYtxz9R91Xtuv7TKWjCR39oKDqM1nyVhTsAydCt6BpRy
// SIG // AKwYnUvlnivFOlSspGDYp/ebf9mpbe1Ea7rc4BL68K2H
// SIG // DJVjCjIeiU7MzH6nN6X+X9hn+kZL0W0dp33SvgL/826C
// SIG // 84d0xGnluXDMS2WjBzWpRJ6EfTlu/hQFvRpQIbU+n/N3
// SIG // HI/Cmp1X4Wl9aeiDzwJvKiK7NzM6cvrWMB2RrfZQGusT
// SIG // 3jrFt1zNszCCBJ0wggOFoAMCAQICCmFJfO0AAAAAAAUw
// SIG // DQYJKoZIhvcNAQEFBQAweTELMAkGA1UEBhMCVVMxEzAR
// SIG // BgNVBAgTCldhc2hpbmd0b24xEDAOBgNVBAcTB1JlZG1v
// SIG // bmQxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlv
// SIG // bjEjMCEGA1UEAxMaTWljcm9zb2Z0IFRpbWVzdGFtcGlu
// SIG // ZyBQQ0EwHhcNMDYwOTE2MDE1NTIyWhcNMTEwOTE2MDIw
// SIG // NTIyWjCBpjELMAkGA1UEBhMCVVMxEzARBgNVBAgTCldh
// SIG // c2hpbmd0b24xEDAOBgNVBAcTB1JlZG1vbmQxHjAcBgNV
// SIG // BAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEnMCUGA1UE
// SIG // CxMebkNpcGhlciBEU0UgRVNOOjEwRDgtNTg0Ny1DQkY4
// SIG // MScwJQYDVQQDEx5NaWNyb3NvZnQgVGltZXN0YW1waW5n
// SIG // IFNlcnZpY2UwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAw
// SIG // ggEKAoIBAQDqugVjyNl5roREPqWzxO1MniTfOXYeCdYy
// SIG // Slh40ivZpQeQ7+c9+70mfKP75X1+Ms/ZPYs5N/L42Ds0
// SIG // FtSSgvs07GiFchqP4LhM4LiF8zMKAsGidnM1TF3xt+FK
// SIG // fR24lHjb/x6FFUJGcc5/J1cS0YNPO8/63vaL7T8A49Xe
// SIG // YfkXjUukgTz1aUDq4Ym/B0+6dHvpDOVH6qts8dVngQj4
// SIG // Fsp9E7tz4glM+mL77aA5mjr+6xHIYR5iWNgKVIPVO0tL
// SIG // 4lW9L2AajpIFQ9pd64IKI5cJoAUxZYuTTh5BIaKSkP1F
// SIG // REVvNbFFN61pqWX5NEOxF8I7OeEQjPIah+NUUB87nTGt
// SIG // AgMBAAGjgfgwgfUwHQYDVR0OBBYEFH5y8C4/VingJfdo
// SIG // uAH8S+F+z+M+MB8GA1UdIwQYMBaAFG/oTj+XuTSrS4aP
// SIG // vJzqrDtBQ8bQMEQGA1UdHwQ9MDswOaA3oDWGM2h0dHA6
// SIG // Ly9jcmwubWljcm9zb2Z0LmNvbS9wa2kvY3JsL3Byb2R1
// SIG // Y3RzL3RzcGNhLmNybDBIBggrBgEFBQcBAQQ8MDowOAYI
// SIG // KwYBBQUHMAKGLGh0dHA6Ly93d3cubWljcm9zb2Z0LmNv
// SIG // bS9wa2kvY2VydHMvdHNwY2EuY3J0MBMGA1UdJQQMMAoG
// SIG // CCsGAQUFBwMIMA4GA1UdDwEB/wQEAwIGwDANBgkqhkiG
// SIG // 9w0BAQUFAAOCAQEAaXqCCQwW0d7PRokuv9E0eoF/JyhB
// SIG // KvPTIZIOl61fU14p+e3BVEqoffcT0AsU+U3yhhUAbuOD
// SIG // HShFpyw5Mt1vmjda7iNSj1QDjT+nnGQ49jbIFEO2Oj6Y
// SIG // yQ3DcYEo82anMeJcXY/5UlLhXOuTkJ1pCUyJ0dF2TDQN
// SIG // auF8RKcrW4NUf0UkGSXEikbFJeMZgGkpFPYXxvAiLIFG
// SIG // Xiv0+abGdz4jb/mmZIWOomINqS0eqOWQPn//sI78l+zx
// SIG // /QSvzUnOWnSs+vMTHxs5zqO01rz0tO7IrfJWHvs88cjW
// SIG // KkS8v5w/fWYYzbIgYwrKQD1lMhl8srg9wSZITiIZmW6M
// SIG // MMHxkTCCBJ0wggOFoAMCAQICEGoLmU/AACWrEdtFH1h6
// SIG // Z6IwDQYJKoZIhvcNAQEFBQAwcDErMCkGA1UECxMiQ29w
// SIG // eXJpZ2h0IChjKSAxOTk3IE1pY3Jvc29mdCBDb3JwLjEe
// SIG // MBwGA1UECxMVTWljcm9zb2Z0IENvcnBvcmF0aW9uMSEw
// SIG // HwYDVQQDExhNaWNyb3NvZnQgUm9vdCBBdXRob3JpdHkw
// SIG // HhcNMDYwOTE2MDEwNDQ3WhcNMTkwOTE1MDcwMDAwWjB5
// SIG // MQswCQYDVQQGEwJVUzETMBEGA1UECBMKV2FzaGluZ3Rv
// SIG // bjEQMA4GA1UEBxMHUmVkbW9uZDEeMBwGA1UEChMVTWlj
// SIG // cm9zb2Z0IENvcnBvcmF0aW9uMSMwIQYDVQQDExpNaWNy
// SIG // b3NvZnQgVGltZXN0YW1waW5nIFBDQTCCASIwDQYJKoZI
// SIG // hvcNAQEBBQADggEPADCCAQoCggEBANw3bvuvyEJKcRjI
// SIG // zkg+U8D6qxS6LDK7Ek9SyIPtPjPZSTGSKLaRZOAfUIS6
// SIG // wkvRfwX473W+i8eo1a5pcGZ4J2botrfvhbnN7qr9EqQL
// SIG // WSIpL89A2VYEG3a1bWRtSlTb3fHev5+Dx4Dff0wCN5T1
// SIG // wJ4IVh5oR83ZwHZcL322JQS0VltqHGP/gHw87tUEJU05
// SIG // d3QHXcJc2IY3LHXJDuoeOQl8dv6dbG564Ow+j5eecQ5f
// SIG // Kk8YYmAyntKDTisiXGhFi94vhBBQsvm1Go1s7iWbE/jL
// SIG // ENeFDvSCdnM2xpV6osxgBuwFsIYzt/iUW4RBhFiFlG6w
// SIG // HyxIzG+cQ+Bq6H8mjmsCAwEAAaOCASgwggEkMBMGA1Ud
// SIG // JQQMMAoGCCsGAQUFBwMIMIGiBgNVHQEEgZowgZeAEFvQ
// SIG // cO9pcp4jUX4Usk2O/8uhcjBwMSswKQYDVQQLEyJDb3B5
// SIG // cmlnaHQgKGMpIDE5OTcgTWljcm9zb2Z0IENvcnAuMR4w
// SIG // HAYDVQQLExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xITAf
// SIG // BgNVBAMTGE1pY3Jvc29mdCBSb290IEF1dGhvcml0eYIP
// SIG // AMEAizw8iBHRPvZj7N9AMBAGCSsGAQQBgjcVAQQDAgEA
// SIG // MB0GA1UdDgQWBBRv6E4/l7k0q0uGj7yc6qw7QUPG0DAZ
// SIG // BgkrBgEEAYI3FAIEDB4KAFMAdQBiAEMAQTALBgNVHQ8E
// SIG // BAMCAYYwDwYDVR0TAQH/BAUwAwEB/zANBgkqhkiG9w0B
// SIG // AQUFAAOCAQEAlE0RMcJ8ULsRjqFhBwEOjHBFje9zVL0/
// SIG // CQUt/7hRU4Uc7TmRt6NWC96Mtjsb0fusp8m3sVEhG28I
// SIG // aX5rA6IiRu1stG18IrhG04TzjQ++B4o2wet+6XBdRZ+S
// SIG // 0szO3Y7A4b8qzXzsya4y1Ye5y2PENtEYIb923juasxtz
// SIG // niGI2LS0ElSM9JzCZUqaKCacYIoPO8cTZXhIu8+tgzpP
// SIG // sGJY3jDp6Tkd44ny2jmB+RMhjGSAYwYElvKaAkMve0aI
// SIG // uv8C2WX5St7aA3STswVuDMyd3ChhfEjxF5wRITgCHIes
// SIG // BsWWMrjlQMZTPb2pid7oZjeN9CKWnMywd1RROtZyRLIj
// SIG // 9jGCBHkwggR1AgEBMIGHMHkxCzAJBgNVBAYTAlVTMRMw
// SIG // EQYDVQQIEwpXYXNoaW5ndG9uMRAwDgYDVQQHEwdSZWRt
// SIG // b25kMR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRp
// SIG // b24xIzAhBgNVBAMTGk1pY3Jvc29mdCBDb2RlIFNpZ25p
// SIG // bmcgUENBAgphD3hNAAAAAAADMAkGBSsOAwIaBQCggaQw
// SIG // GQYJKoZIhvcNAQkDMQwGCisGAQQBgjcCAQQwHAYKKwYB
// SIG // BAGCNwIBCzEOMAwGCisGAQQBgjcCARUwIwYJKoZIhvcN
// SIG // AQkEMRYEFCx9DvENkDLn8fOGXjGdcpSVn5/cMEQGCisG
// SIG // AQQBgjcCAQwxNjA0oBqAGABjAHUAcwB0AG8AbQB3AGkA
// SIG // egAuAGoAc6EWgBRodHRwOi8vbWljcm9zb2Z0LmNvbTAN
// SIG // BgkqhkiG9w0BAQEFAASCAQArbOy/nq3G8TfH6BwdxYBf
// SIG // kcg/sSlJacn1JVjCl0kp14AIItt5g3lDeF5K4NLtGfl0
// SIG // EUvQZUeFNuV3BrjccKdbZbXzGj5kMdZqNYio7xZif78c
// SIG // eo8P8X0ugbVHyC6q/HRBDOOCQP2grLlWaIxz9qfyjI4V
// SIG // kPlWEnzISaNC8l8hoiU7HiPweemHkaQlcG+DxEWou+U0
// SIG // uXQRRvpQU9Vfi2m+6ZwWIYpuG9rFffSwPf8mPYpu9d6G
// SIG // Ezmgy/7cnojEVoAfA5sOag9b5f6doF57MDClPflXN9O2
// SIG // mYZEVpsQMp/KyYiY9oTeu/IC1vHTZVujQv++0c5zOtWG
// SIG // 9Z9mZyXCGiOAoYICHzCCAhsGCSqGSIb3DQEJBjGCAgww
// SIG // ggIIAgEBMIGHMHkxCzAJBgNVBAYTAlVTMRMwEQYDVQQI
// SIG // EwpXYXNoaW5ndG9uMRAwDgYDVQQHEwdSZWRtb25kMR4w
// SIG // HAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xIzAh
// SIG // BgNVBAMTGk1pY3Jvc29mdCBUaW1lc3RhbXBpbmcgUENB
// SIG // AgphSXztAAAAAAAFMAcGBSsOAwIaoF0wGAYJKoZIhvcN
// SIG // AQkDMQsGCSqGSIb3DQEHATAcBgkqhkiG9w0BCQUxDxcN
// SIG // MDcxMTIyMDkwOTEwWjAjBgkqhkiG9w0BCQQxFgQUKCME
// SIG // D0Nbb3X/56BO0ezCiFBDR6IwDQYJKoZIhvcNAQEFBQAE
// SIG // ggEAsChKLuVYnAj6CLiibqF8+FfgtPWK6cFvrkxZUA6B
// SIG // PETvW/+U9sqOLCfT4MfPSxMswfJXpcAzBsLmxnyIZlSt
// SIG // VHj8MRxStqzj9qPZqJW5E/1Go9URLAWGoNpxvBuEfc05
// SIG // fW8NiKdbYZ8Lzw0A50PqUsHWkLJ0EUcac9rb+DVylBno
// SIG // x4HJ/iT3FuD3Xfnbg3qNrMzxHOIc/iKoxYXfNYLs6GJJ
// SIG // mQqPdum0VRpT+KrPmEGV/4kvVgwFMgh3cHSeTtGcjxyl
// SIG // BU/sNYzDeC4+413DNBLRlacLMBlJ7sjcLFCHexOhUkWy
// SIG // cGaKVCaoroll5E+/htEUuFb5gOVT6T0huHa54A==
// SIG // End signature block
