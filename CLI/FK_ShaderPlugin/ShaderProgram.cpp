#include "ShaderProgram.h"
#include "GL/glew.h"
#include <string>
#include <vcclr.h>

namespace FK_ShaderPlugin {

	fk_ShaderProgram::fk_ShaderProgram() : idProgram(0), idVertex(0), idFragment(0)
	{
	}

	fk_ShaderProgram::~fk_ShaderProgram()
	{
		if (idProgram != 0)
		{
			glDeleteProgram(idProgram);
			idProgram = 0;
		}

		if (idVertex != 0)
		{
			glDeleteShader(idVertex);
			idVertex = 0;
		}

		if (idFragment != 0)
		{
			glDeleteShader(idFragment);
			idFragment = 0;
		}
	}

	bool fk_ShaderProgram::Validate(void)
	{
		// 頂点シェーダ

		if (String::IsNullOrEmpty(VertexShaderSource))
		{
			lastError = "VertexShaderSource is empty.";
			return false;
		}

		if (idVertex != 0)
		{
			glDeleteShader(idVertex);
			idVertex = 0;
		}

		idVertex = Compile(VertexShaderSource, GL_VERTEX_SHADER);
		if (idVertex == 0)
		{
			lastError = "VertexShader could not create.";
			return false;
		}

		if (UpdateLastError(idVertex))
		{
			return false;
		}

		// フラグメントシェーダ

		if (String::IsNullOrEmpty(FragmentShaderSource))
		{
			lastError = "FragmentShaderSource is empty.";
			return false;
		}

		if (idFragment != 0)
		{
			glDeleteShader(idFragment);
			idFragment = 0;
		}

		idFragment = Compile(FragmentShaderSource, GL_FRAGMENT_SHADER);
		if (idFragment == 0)
		{
			lastError = "FragmentShader could not create.";
			return false;
		}

		if (UpdateLastError(idFragment))
		{
			return false;
		}

		// リンク
		return Link();
	}

	UInt32 fk_ShaderProgram::ProgramId::get(void)
	{
		return idProgram;
	}

	String^ fk_ShaderProgram::LastError::get(void)
	{
		return lastError;
	}

	UInt32 fk_ShaderProgram::Compile(String^ code, UInt32 kind)
	{
		UInt32 id = glCreateShader(kind);
		if (id == 0)
		{
			return id;
		}

		using namespace Runtime::InteropServices;
		const char* pCode = (const char*)(Marshal::StringToHGlobalAnsi(code)).ToPointer();
		glShaderSource(id, 1, &pCode, nullptr);
		glCompileShader(id);

		Marshal::FreeHGlobal(IntPtr((void*)pCode));

		return id;
	}

	bool fk_ShaderProgram::Link(void)
	{
		if (idProgram != 0)
		{
			glDeleteProgram(idProgram);
			idProgram = 0;
		}

		idProgram = glCreateProgram();
		if (idProgram == 0)
		{
			lastError = "Could not create program.";
			return false;
		}

		glAttachShader(idProgram, idVertex);
		glAttachShader(idProgram, idFragment);
		glLinkProgram(idProgram);

		GLint linked = 0;
		glGetProgramiv(idProgram, GL_LINK_STATUS, &linked);
		if (linked == GL_FALSE)
		{
			lastError = "Shader Link Error.";
			return false;
		}

		return true;
	}

	bool fk_ShaderProgram::UpdateLastError(UInt32 shader)
	{
		GLsizei bufSize;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);
		if (bufSize > 1)
		{
			GLchar *infoLog = (GLchar *)malloc(bufSize);
			if (infoLog != NULL)
			{
				GLsizei length;
				glGetShaderInfoLog(shader, bufSize, &length, infoLog);
				lastError = gcnew String(infoLog);
				free(infoLog);
			}
			else
			{
				lastError = "Could not allocate InfoLog buffer.";
			}

			return true;
		}
		else
		{
			lastError = nullptr;
			return false;
		}
	}
}
