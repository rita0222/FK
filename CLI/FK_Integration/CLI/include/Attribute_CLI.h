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
			if(pBase == NULL) return;
			if(dFlg == true) delete GetP();
			pBase = NULL;
		}

		bool setAttrII(int key, int value);
		bool setAttrID(int key, double value);
		bool setAttrIS(int key, String^ value);
		bool setAttrSI(String^ key, int value);
		bool setAttrSD(String^ key, double value);
		bool setAttrSS(String ^key, String^ value);
		int getAttrII(int key);
		double getAttrID(int key);
		String^ getAttrIS(int key);
		int getAttrSI(String^ key);
		double getAttrSD(String^ key);
		String^ getAttrSS(String^ key);
		bool existAttrII(int key);
		bool existAttrID(int key);
		bool existAttrIS(int key);
		bool existAttrSI(String^ key);
		bool existAttrSD(String^ key);
		bool existAttrSS(String^ key);
		bool deleteAttrII(int key);
		bool deleteAttrID(int key);
		bool deleteAttrIS(int key);
		bool deleteAttrSI(String^ key);
		bool deleteAttrSD(String^ key);
		bool deleteAttrSS(String^ key);
	};
}
