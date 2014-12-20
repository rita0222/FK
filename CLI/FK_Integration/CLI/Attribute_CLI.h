// Attribute_CLI.h

#pragma once

#include <FK/Attribute.h>
#include "Base_CLI.h"

using namespace std;
using namespace System;
using namespace msclr::interop;

namespace FK_CLI
{
	public ref class fk_Attribute : FK_CLI::fk_BaseObject
	{
	internal:
		::fk_Attribute * GetP(void)
		{
			return reinterpret_cast<::fk_Attribute *>(this->pBase);
		}

	public:
		fk_Attribute::fk_Attribute(bool argNewFlg) : fk_BaseObject(false)
		{
			if(argNewFlg == true) {
				::fk_Attribute *p = new ::fk_Attribute();
				this->pBase = reinterpret_cast<::fk_BaseObject *>(p);
			}
		}

		fk_Attribute::~fk_Attribute()
		{
			this->!fk_Attribute();
		}

		fk_Attribute::!fk_Attribute()
		{
			if(this->pBase != NULL) delete this->pBase;
			this->pBase = NULL;
		}

		bool setAttrII(int argKey, int argValue)
		{
			return GetP()->setAttrII(argKey, argValue);
		}

		bool setAttrID(int argKey, double argValue)
		{
			return GetP()->setAttrID(argKey, argValue);
		}

		bool setAttrIS(int argKey, String^ argValue)
		{
			return GetP()->setAttrIS(argKey, marshal_as<string>(argValue));
		}

		bool setAttrSI(String^ argKey, int argValue)
		{
			return GetP()->setAttrSI(marshal_as<string>(argKey), argValue);
		}

		bool setAttrSD(String^ argKey, double argValue)
		{
			return GetP()->setAttrSD(marshal_as<string>(argKey), argValue);
		}

		bool setAttrSS(String ^argKey, String^ argValue)
		{
			return GetP()->setAttrSS(marshal_as<string>(argKey), marshal_as<string>(argValue));
		}

		int getAttrII(int argKey)
		{
			return GetP()->getAttrII(argKey);
		}

		double getAttrID(int argKey)
		{
			return GetP()->getAttrID(argKey);
		}

		String^ getAttrIS(int argKey)
		{
			return marshal_as<String^>(GetP()->getAttrIS(argKey));
		}

		int getAttrSI(String^ argKey)
		{
			return GetP()->getAttrSI(marshal_as<string>(argKey));
		}

		double getAttrSD(String^ argKey)
		{
			return GetP()->getAttrSD(marshal_as<string>(argKey));
		}

		String^ getAttrSS(String^ argKey)
		{
			string	str = GetP()->getAttrSS(marshal_as<string>(argKey));
			return marshal_as<String^>(str);
		}

		bool existAttrII(int argKey)
		{
			return GetP()->existAttrII(argKey);
		}

		bool existAttrID(int argKey)
		{
			return GetP()->existAttrID(argKey);
		}

		bool existAttrIS(int argKey)
		{
			return GetP()->existAttrIS(argKey);
		}

		bool existAttrSI(String^ argKey)
		{
			return GetP()->existAttrSI(marshal_as<string>(argKey));
		}

		bool existAttrSD(String^ argKey)
		{
			return GetP()->existAttrSD(marshal_as<string>(argKey));
		}

		bool existAttrSS(String^ argKey)
		{
			return GetP()->existAttrSS(marshal_as<string>(argKey));
		}

		bool deleteAttrII(int argKey)
		{
			return GetP()->deleteAttrII(argKey);
		}

		bool deleteAttrID(int argKey)
		{
			return GetP()->deleteAttrID(argKey);
		}

		bool deleteAttrIS(int argKey)
		{
			return GetP()->deleteAttrIS(argKey);
		}

		bool deleteAttrSI(String^ argKey)
		{
			return GetP()->deleteAttrSI(marshal_as<string>(argKey));
		}

		bool deleteAttrSD(String^ argKey)
		{
			return GetP()->deleteAttrSD(marshal_as<string>(argKey));
		}

		bool deleteAttrSS(String^ argKey)
		{
			return GetP()->deleteAttrSS(marshal_as<string>(argKey));
		}
	};
}
