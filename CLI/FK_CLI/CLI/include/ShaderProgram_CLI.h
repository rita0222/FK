#pragma once

using namespace System;

namespace FK_CLI
{
	public ref class fk_ShaderProgram
	{
	public:
		fk_ShaderProgram();
		virtual ~fk_ShaderProgram();

		property String^ VertexShaderSource;
		property String^ FragmentShaderSource;
		property UInt32 ProgramId { UInt32 get(void); };
		property String^ LastError { String^ get(void); };

		bool Validate(void);

	private:
		UInt32 Compile(String^ code, UInt32 kind);
		bool Link(void);
		bool UpdateLastError(UInt32 shader);

		String^ lastError;

		UInt32 idProgram;
		UInt32 idVertex;
		UInt32 idFragment;
	};
}
