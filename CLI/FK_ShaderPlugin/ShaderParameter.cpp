#include "ShaderParameter.h"
#include "GL/glew.h"
#include <stdlib.h>
#include <vcclr.h>

namespace FK_ShaderPlugin {

	fk_ShaderParameter::fk_ShaderParameter() : lastAppliedId(0)
	{
		floatTable = gcnew Dictionary<String^, float>();
		floatArrayTable = gcnew Dictionary<String^, array<float>^>();
		intTable = gcnew Dictionary<String^, int>();
		intArrayTable = gcnew Dictionary<String^, array<int>^>();
		locationTable = gcnew Dictionary<String^, Int32>();
	}

	fk_ShaderParameter::~fk_ShaderParameter()
	{
		delete floatTable;
		delete floatArrayTable;
		delete intTable;
		delete intArrayTable;
		delete locationTable;
		floatTable = nullptr;
		floatArrayTable = nullptr;
		intTable = nullptr;
		intArrayTable = nullptr;
		locationTable = nullptr;
	}

	String^ fk_ShaderParameter::LastError::get(void)
	{
		return lastError;
	}

	void fk_ShaderParameter::Register(String ^ name, float value)
	{
		floatTable[name] = value;
	}

	void fk_ShaderParameter::Register(String ^ name, array<float>^ value)
	{
		floatArrayTable[name] = value;
	}

	void fk_ShaderParameter::Register(String ^ name, int value)
	{
		intTable[name] = value;
	}

	void fk_ShaderParameter::Register(String ^ name, array<int>^ value)
	{
		intArrayTable[name] = value;
	}

	bool fk_ShaderParameter::Unregister(String ^ name)
	{
		if (floatTable->ContainsKey(name))
		{
			floatTable->Remove(name);
			return true;
		}

		if (floatArrayTable->ContainsKey(name))
		{
			floatArrayTable->Remove(name);
			return true;
		}

		if (intTable->ContainsKey(name))
		{
			intTable->Remove(name);
			return true;
		}

		if (intArrayTable->ContainsKey(name))
		{
			intArrayTable->Remove(name);
			return true;
		}

		return false;
	}

	bool fk_ShaderParameter::Apply(UInt32 programId)
	{
		bool result = true;
		if (lastAppliedId != programId)
		{
			locationTable->Clear();
			lastAppliedId = programId;
		}

		lastError = "";

		for each (KeyValuePair<String^, float>^ pair in floatTable)
		{
			Int32 location = GetLocation(programId, pair->Key);
			if (location >= 0)
			{
				glUniform1f(location, pair->Value);
			}
			else
			{
				lastError += "ERROR: " + pair->Key + " is not found.";
				result = false;
			}
		}

		for each (KeyValuePair<String^, array<float>^>^ pair in floatArrayTable)
		{
			Int32 location = GetLocation(programId, pair->Key);
			if (location >= 0)
			{
				array<float>^ values = pair->Value;
				switch (values->Length)
				{
				case 1:
					glUniform1f(location, values[0]);
					break;
				case 2:
					glUniform2f(location, values[0], values[1]);
					break;
				case 3:
					glUniform3f(location, values[0], values[1], values[2]);
					break;
				case 4:
					glUniform4f(location, values[0], values[1], values[2], values[3]);
					break;
				default:
					result = false;
				}
			}
			else
			{
				lastError += "ERROR: " + pair->Key + " is not found.";
				result = false;
			}
		}

		for each (KeyValuePair<String^, int>^ pair in intTable)
		{
			Int32 location = GetLocation(programId, pair->Key);
			if (location >= 0)
			{
				glUniform1i(location, pair->Value);
			}
			else
			{
				lastError += "ERROR: " + pair->Key + " is not found.";
				result = false;
			}
		}

		for each (KeyValuePair<String^, array<int>^>^ pair in intArrayTable)
		{
			Int32 location = GetLocation(programId, pair->Key);
			if (location >= 0)
			{
				array<int>^ values = pair->Value;
				switch (values->Length)
				{
				case 1:
					glUniform1i(location, values[0]);
					break;
				case 2:
					glUniform2i(location, values[0], values[1]);
					break;
				case 3:
					glUniform3i(location, values[0], values[1], values[2]);
					break;
				case 4:
					glUniform4i(location, values[0], values[1], values[2], values[3]);
					break;
				default:
					result = false;
				}
			}
			else
			{
				lastError += "ERROR: " + pair->Key + " is not found.";
				result = false;
			}
		}

		return result;
	}

	Int32 fk_ShaderParameter::GetLocation(UInt32 programId, String^ name)
	{
		if (locationTable->ContainsKey(name))
		{
			return locationTable[name];
		}

		using namespace Runtime::InteropServices;
		const char* pName = (const char*)(Marshal::StringToHGlobalAnsi(name)).ToPointer();
		Int32 location = glGetUniformLocation(programId, pName);
		Marshal::FreeHGlobal(IntPtr((void*)pName));
		if (location >= 0)
		{
			locationTable->Add(name, location);
		}

		return location;
	}
}
