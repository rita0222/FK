// FK_ShaderPlugin.h

#pragma once

#include <FK/Model.h>

using namespace System;
using namespace FK_CLI;

#pragma make_public(::fk_Model)

class GLSLModel : public ::fk_Model
{
public:
	void preShader()
	{
		System::Diagnostics::Debug::WriteLine("preShader");
	};

	void postShader()
	{
		System::Diagnostics::Debug::WriteLine("postShader");
	};
};

namespace FK_ShaderPlugin
{

	public ref class fk_ShaderModel : public FK_CLI::fk_Model
	{
	private:
		GLSLModel	*unmanageP;
	public:
		fk_ShaderModel::fk_ShaderModel() : fk_Model(new GLSLModel())
		{
			unmanageP = (GLSLModel *)GetP();
		};
	};
}
