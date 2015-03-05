// Attribute_CLI.h

#pragma once

#include <FK/Attribute.h>
#include "Base_CLI.h"

namespace FK_CLI
{
	public ref class fk_Attribute : fk_BaseObject {
	internal:
		::fk_Attribute * GetP(void);

	public:
		fk_Attribute(bool argNewFlg);
		~fk_Attribute();
		!fk_Attribute();

		bool SetAttrII(int key, int value);
		bool SetAttrID(int key, double value);
		bool SetAttrIS(int key, String^ value);
		bool SetAttrSI(String^ key, int value);
		bool SetAttrSD(String^ key, double value);
		bool SetAttrSS(String ^key, String^ value);
		int GetAttrII(int key);
		double GetAttrID(int key);
		String^ GetAttrIS(int key);
		int GetAttrSI(String^ key);
		double GetAttrSD(String^ key);
		String^ GetAttrSS(String^ key);
		bool ExistAttrII(int key);
		bool ExistAttrID(int key);
		bool ExistAttrIS(int key);
		bool ExistAttrSI(String^ key);
		bool ExistAttrSD(String^ key);
		bool ExistAttrSS(String^ key);
		bool DeleteAttrII(int key);
		bool DeleteAttrID(int key);
		bool DeleteAttrIS(int key);
		bool DeleteAttrSI(String^ key);
		bool DeleteAttrSD(String^ key);
		bool DeleteAttrSS(String^ key);
	};
}
