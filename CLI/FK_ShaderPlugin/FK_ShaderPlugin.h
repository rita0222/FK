// FK_ShaderPlugin.h

#pragma once

using namespace System;

namespace FK_ShaderPlugin
{
	public ref class fk_ShaderModel
	{
	public:
		fk_ShaderModel::fk_ShaderModel();
		System::UInt32 Compile(System::String^ code, System::UInt32 type);
		bool Validate();
		bool SetUniform(System::String^ );
		System::String^ GetError();

	private:
		System::UInt32 idProgram;
		System::UInt32 idVertex;
		System::UInt32 idFragment;
		static bool	isExtensionInitialized = false;
		static bool Initialize();
	};
}
