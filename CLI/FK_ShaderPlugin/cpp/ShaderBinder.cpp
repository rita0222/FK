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

		Program = innerProgram = gcnew fk_ShaderProgram();
		Parameter = innerParameter = gcnew fk_ShaderParameter();
	}

	fk_ShaderBinder::fk_ShaderBinder(fk_ShaderProgram^ prog, fk_ShaderParameter^ param)
	{
		Initialize();

		if (prog != nullptr) Program = prog;
		else Program = innerProgram = gcnew fk_ShaderProgram();

		if (param != nullptr) Parameter = param;
		else Parameter = innerParameter = gcnew fk_ShaderParameter();
	}

	fk_ShaderBinder::~fk_ShaderBinder()
	{
		if (innerProgram != nullptr) delete innerProgram;
		if (innerParameter != nullptr) delete innerParameter;
		Program = innerProgram = nullptr;
		Parameter = innerParameter = nullptr;
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
		UInt32 id = Program->ProgramId;
		if (id != 0)
		{
			glUseProgram(id);
			Parameter->Apply(id);
			usingProgram = true;
		}
	}

	void fk_ShaderBinder::ProcPostShader(void)
	{
		if (usingProgram)
		{
			glUseProgram(0);
			usingProgram = false;
		}
	}
}
