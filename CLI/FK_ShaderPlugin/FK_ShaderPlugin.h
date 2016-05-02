// FK_ShaderPlugin.h

#pragma once

#include <FK/Model.h>

using namespace System;
using namespace FK_CLI;

namespace FK_ShaderPlugin
{

	public ref class fk_ShaderModel : public FK_CLI::fk_Model
	{
	public:
		fk_ShaderModel::fk_ShaderModel() : fk_Model()
		{
		};
	};
}
