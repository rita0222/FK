#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace FK_CLI;

namespace FK_ShaderPlugin
{
	public ref class fk_ShaderParameter
	{
	public:
		fk_ShaderParameter();
		virtual ~fk_ShaderParameter();
	private:
		Dictionary<String^, Int32> locationTable;
		Dictionary<Int32, Single> floatTable;
		Dictionary<Int32, Single> floatTable;
	};
}

