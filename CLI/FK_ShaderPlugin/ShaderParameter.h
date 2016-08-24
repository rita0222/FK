#pragma once

#include "TextureSampler.h"

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
		void Register(String^ name, fk_Matrix^ value);
		bool Unregister(String^ name);

		void AddAttribute(String^ name, int dim, array<float>^ value);
		void AddAttribute(String^ name, int dim, array<int>^ value);
		bool RemoveAttribute(String^ name);

		bool AttachTexture(int unit, fk_TextureSampler^ texture);
		bool DetachTexture(int unit);

		bool Apply(UInt32 programId);

	private:
		Int32 GetLocation(UInt32 programId, String^ name);
		Int32 GetAttributeLocation(UInt32 programId, String^ name);

		Dictionary<String^, float>^ floatTable;
		Dictionary<String^, array<float>^>^ floatArrayTable;
		Dictionary<String^, int>^ intTable;
		Dictionary<String^, array<int>^>^ intArrayTable;
		Dictionary<String^, fk_Matrix^>^ matrixTable;
		Dictionary<String^, Int32>^ locationTable;

		Dictionary<String^, Tuple<int, array<float>^>^>^ floatAttributeTable;
		Dictionary<String^, Tuple<int, array<int>^>^>^ intAttributeTable;
		Dictionary<String^, Int32>^ attributeLocationTable;

		Dictionary<int, fk_TextureSampler^>^ textureTable;

		String^ lastError;
		UInt32 lastAppliedId;
	};
}
