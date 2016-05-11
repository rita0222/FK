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

		property String^ LastError { String^ get(void); };

		void Register(String^ name, float value);
		void Register(String^ name, array<float>^ value);
		void Register(String^ name, int value);
		void Register(String^ name, array<int>^ value);
		bool Unregister(String^ name);
		bool Apply(UInt32 programId);

	private:
		Int32 GetLocation(UInt32 programId, String^ name);

		Dictionary<String^, float>^ floatTable;
		Dictionary<String^, array<float>^>^ floatArrayTable;
		Dictionary<String^, int>^ intTable;
		Dictionary<String^, array<int>^>^ intArrayTable;
		Dictionary<String^, Int32>^ locationTable;
		String^ lastError;

		UInt32 lastAppliedId;
	};
}

