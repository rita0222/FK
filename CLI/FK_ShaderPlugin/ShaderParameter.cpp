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
		matrixTable = gcnew Dictionary<String^, fk_Matrix^>();
		locationTable = gcnew Dictionary<String^, Int32>();
		textureTable = gcnew Dictionary<int, fk_TextureSampler^>();
	}

	fk_ShaderParameter::~fk_ShaderParameter()
	{
		delete floatTable;
		delete floatArrayTable;
		delete intTable;
		delete intArrayTable;
		delete matrixTable;
		delete locationTable;
		delete textureTable;
		floatTable = nullptr;
		floatArrayTable = nullptr;
		intTable = nullptr;
		intArrayTable = nullptr;
		matrixTable = nullptr;
		locationTable = nullptr;
		textureTable = nullptr;
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

	void fk_ShaderParameter::Register(String ^ name, fk_Matrix ^ value)
	{
		matrixTable[name] = value;
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

		if (matrixTable->ContainsKey(name))
		{
			matrixTable->Remove(name);
			return true;
		}

		return false;
	}

	bool fk_ShaderParameter::AttachTexture(int unit, fk_TextureSampler ^ texture)
	{
		if (unit < 0 || unit > 31) return false;
		textureTable[unit] = texture;
		return true;
	}

	bool fk_ShaderParameter::DetachTexture(int unit)
	{
		if (textureTable->ContainsKey(unit))
		{
			textureTable->Remove(unit);
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

		bool changed = false;
		for each (KeyValuePair<int, fk_TextureSampler^>^ pair in textureTable)
		{
			glActiveTexture(GL_TEXTURE0 + pair->Key);
			pair->Value->BindTexture(false);
			changed = true;
		}

		if (changed) glActiveTexture(GL_TEXTURE0);

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

		for each (KeyValuePair<String^, fk_Matrix^>^ pair in matrixTable)
		{
			Int32 location = GetLocation(programId, pair->Key);
			if (location >= 0)
			{
				pin_ptr<float> pArray = &(pair->Value->GetFloatArray()[0]);
				glUniformMatrix4fv(location, 1, GL_FALSE, pArray);
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
