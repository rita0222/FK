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
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->setAttrII(argKey, argValue);
		}

		bool setAttrID(int argKey, double argValue)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->setAttrID(argKey, argValue);
		}

		bool setAttrIS(int argKey, String^ argValue)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->setAttrIS(argKey, marshal_as<string>(argValue));
		}

		bool setAttrSI(String^ argKey, int argValue)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->setAttrSI(marshal_as<string>(argKey), argValue);
		}

		bool setAttrSD(String^ argKey, double argValue)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->setAttrSD(marshal_as<string>(argKey), argValue);
		}

		bool setAttrSS(String ^argKey, String^ argValue)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->setAttrSS(marshal_as<string>(argKey),
										  marshal_as<string>(argValue));
		}

		int getAttrII(int argKey)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->getAttrII(argKey);
		}

		double getAttrID(int argKey)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->getAttrID(argKey);
		}

		String^ getAttrIS(int argKey)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return marshal_as<String^>(p->getAttrIS(argKey));
		}

		int getAttrSI(String^ argKey)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->getAttrSI(marshal_as<string>(argKey));
		}

		double getAttrSD(String^ argKey)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->getAttrSD(marshal_as<string>(argKey));
		}

		String^ getAttrSS(String^ argKey)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			string	str = p->getAttrSS(marshal_as<string>(argKey));
			return marshal_as<String^>(str);
		}

		bool existAttrII(int argKey)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->existAttrII(argKey);
		}

		bool existAttrID(int argKey)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->existAttrID(argKey);
		}

		bool existAttrIS(int argKey)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->existAttrIS(argKey);
		}

		bool existAttrSI(String^ argKey)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->existAttrSI(marshal_as<string>(argKey));
		}

		bool existAttrSD(String^ argKey)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->existAttrSD(marshal_as<string>(argKey));
		}

		bool existAttrSS(String^ argKey)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->existAttrSS(marshal_as<string>(argKey));
		}

		bool deleteAttrII(int argKey)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->deleteAttrII(argKey);
		}

		bool deleteAttrID(int argKey)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->deleteAttrID(argKey);
		}

		bool deleteAttrIS(int argKey)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->deleteAttrIS(argKey);
		}

		bool deleteAttrSI(String^ argKey)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->deleteAttrSI(marshal_as<string>(argKey));
		}

		bool deleteAttrSD(String^ argKey)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->deleteAttrSD(marshal_as<string>(argKey));
		}

		bool deleteAttrSS(String^ argKey)
		{
			::fk_Attribute *p = reinterpret_cast<::fk_Attribute *>(this->pBase);
			return p->deleteAttrSS(marshal_as<string>(argKey));
		}

	};
}
