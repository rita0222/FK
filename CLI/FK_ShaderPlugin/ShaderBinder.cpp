#include "ShaderBinder.h"
#include "GL/glew.h"
#include <string>
#include <vcclr.h>

namespace FK_ShaderPlugin
{
	bool fk_ShaderBinder::Initialize()
	{
		if (!isExtensionInitialized)
		{
			isExtensionInitialized = glewInit() == GLEW_OK;
		}

		return isExtensionInitialized;
	}

	fk_ShaderBinder::fk_ShaderBinder()
	{
		Initialize();
	}

	void fk_ShaderBinder::BindModel(fk_Model ^ model)
	{
		model->PreShader +=
			gcnew fk_ShaderCallback(this, &fk_ShaderBinder::ProcPreShader);
		model->PostShader +=
			gcnew fk_ShaderCallback(this, &fk_ShaderBinder::ProcPostShader);
	}

	void fk_ShaderBinder::UnbindModel(fk_Model ^ model)
	{
		model->PreShader -=
			gcnew fk_ShaderCallback(this, &fk_ShaderBinder::ProcPreShader);
		model->PostShader -=
			gcnew fk_ShaderCallback(this, &fk_ShaderBinder::ProcPostShader);
	}

	void fk_ShaderBinder::ProcPreShader(void)
	{
		Console::WriteLine("ProcPreShader");
	}

	void fk_ShaderBinder::ProcPostShader(void)
	{
		Console::WriteLine("ProcPostShader");
	}
}

