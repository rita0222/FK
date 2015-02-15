// Attribute_CLI.h

#pragma once

#include <FK/Attribute.h>
#include "Base_CLI.h"

namespace FK_CLI
{
	public ref class fk_Attribute : fk_BaseObject {
	internal:
		::fk_Attribute * GetP(void)
		{
			return (::fk_Attribute *)(pBase);
		}

	public:
		fk_Attribute::fk_Attribute(bool argNewFlg) : fk_BaseObject(false)
		{
			if(argNewFlg == true) pBase = new ::fk_Attribute();
		}

		fk_Attribute::~fk_Attribute()
		{
			this->!fk_Attribute();
		}

		fk_Attribute::!fk_Attribute()
		{
			if(pBase == nullptr) return;
			if(dFlg == true) delete GetP();
			pBase = nullptr;
		}

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
