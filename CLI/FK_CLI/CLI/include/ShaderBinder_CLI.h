#pragma once

#include "ShaderProgram_CLI.h"
#include "ShaderParameter_CLI.h"

//using namespace System;

namespace FK_CLI
{
	public ref class fk_ShaderBinder
	{
	public:
		fk_ShaderBinder();
		fk_ShaderBinder(fk_ShaderProgram^ prog, fk_ShaderParameter^ param);
		~fk_ShaderBinder();

		property fk_ShaderProgram^ Program;
		property fk_ShaderParameter^ Parameter;

		void BindModel(fk_Model^ model);
		void UnbindModel(fk_Model^ model);

	internal:
		static bool Initialize(void);

	private:
		void ProcPreShader(void);
		void ProcPostShader(void);

		fk_ShaderProgram^ innerProgram = nullptr;
		fk_ShaderParameter^ innerParameter = nullptr;

		static bool	isExtensionInitialized = false;
		bool usingProgram = false;
	};
}
