#pragma once

//using namespace System;

namespace FK_CLI
{
	public ref class fk_ShaderProgram
	{
	public:
		fk_ShaderProgram();
		virtual ~fk_ShaderProgram();

		property System::String^ VertexShaderSource;
		property System::String^ FragmentShaderSource;
		property System::UInt32 ProgramId { System::UInt32 get(void); };
		property System::String^ LastError { System::String^ get(void); };

		bool Validate(void);

	private:
		System::UInt32 Compile(System::String^ code, System::UInt32 kind);
		bool Link(void);
		bool UpdateLastError(System::UInt32 shader);

		System::String^ lastError;

		System::UInt32 idProgram;
		System::UInt32 idVertex;
		System::UInt32 idFragment;
	};
}
