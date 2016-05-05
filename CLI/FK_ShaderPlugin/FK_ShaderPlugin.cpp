// これは メイン DLL ファイルです。

#include "FK_ShaderPlugin.h"
#include "GL/glew.h"
#include <string>
#include <vcclr.h>

namespace FK_ShaderPlugin
{
	bool fk_ShaderModel::Initialize()
	{
		if (!isExtensionInitialized)
		{
			isExtensionInitialized = glewInit() == GLEW_OK;
		}

		return isExtensionInitialized;
	}

	void MarshalString(String ^ s, std::string& os) {
		using namespace Runtime::InteropServices;
		const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}

	System::UInt32 fk_ShaderModel::Compile(System::String^ code, System::UInt32 type)
	{
		std::string nCode;
		MarshalString(code, nCode);
		const char *pCode = nCode.c_str();
		System::UInt32 id = glCreateShader(type);
		glShaderSource(id, 1, &pCode, nullptr);
		glCompileShader(id);

		return id;
	}

	fk_ShaderModel::fk_ShaderModel()
	{
		Initialize();
	}
}

