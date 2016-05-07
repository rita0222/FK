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

	void fk_ShaderBinder::Dispose()
	{
		throw gcnew System::NotImplementedException();
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
		if (innerProgram != nullptr) innerProgram->Dispose();
		if (innerParameter != nullptr) innerParameter->Dispose();
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
		Console::WriteLine("ProcPreShader");
		if (Program->ProgramId != 0)
		{
			glUseProgram(Program->ProgramId);
			usingProgram = true;
		}
	}

	void fk_ShaderBinder::ProcPostShader(void)
	{
		Console::WriteLine("ProcPostShader");
		if (usingProgram)
		{
			glUseProgram(0);
			usingProgram = false;
		}
	}
}
