#include "Attribute_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	bool fk_Attribute::setAttrII(int argKey, int argValue)
	{
		return GetP()->setAttrII(argKey, argValue);
	}

	bool fk_Attribute::setAttrID(int argKey, double argValue)
	{
		return GetP()->setAttrID(argKey, argValue);
	}

	bool fk_Attribute::setAttrIS(int argKey, String^ argValue)
	{
		return GetP()->setAttrIS(argKey, marshal_as<string>(argValue));
	}

	bool fk_Attribute::setAttrSI(String^ argKey, int argValue)
	{
		return GetP()->setAttrSI(marshal_as<string>(argKey), argValue);
	}

	bool fk_Attribute::setAttrSD(String^ argKey, double argValue)
	{
		return GetP()->setAttrSD(marshal_as<string>(argKey), argValue);
	}

	bool fk_Attribute::setAttrSS(String ^argKey, String^ argValue)
	{
		return GetP()->setAttrSS(marshal_as<string>(argKey), marshal_as<string>(argValue));
	}

	int fk_Attribute::getAttrII(int argKey)
	{
		return GetP()->getAttrII(argKey);
	}

	double fk_Attribute::getAttrID(int argKey)
	{
		return GetP()->getAttrID(argKey);
	}

	String^ fk_Attribute::getAttrIS(int argKey)
	{
		return marshal_as<String^>(GetP()->getAttrIS(argKey));
	}

	int fk_Attribute::getAttrSI(String^ argKey)
	{
		return GetP()->getAttrSI(marshal_as<string>(argKey));
	}

	double fk_Attribute::getAttrSD(String^ argKey)
	{
		return GetP()->getAttrSD(marshal_as<string>(argKey));
	}

	String^ fk_Attribute::getAttrSS(String^ argKey)
	{
		string	str = GetP()->getAttrSS(marshal_as<string>(argKey));
		return marshal_as<String^>(str);
	}

	bool fk_Attribute::existAttrII(int argKey)
	{
		return GetP()->existAttrII(argKey);
	}

	bool fk_Attribute::existAttrID(int argKey)
	{
		return GetP()->existAttrID(argKey);
	}

	bool fk_Attribute::existAttrIS(int argKey)
	{
		return GetP()->existAttrIS(argKey);
	}

	bool fk_Attribute::existAttrSI(String^ argKey)
	{
		return GetP()->existAttrSI(marshal_as<string>(argKey));
	}

	bool fk_Attribute::existAttrSD(String^ argKey)
	{
		return GetP()->existAttrSD(marshal_as<string>(argKey));
	}

	bool fk_Attribute::existAttrSS(String^ argKey)
	{
		return GetP()->existAttrSS(marshal_as<string>(argKey));
	}

	bool fk_Attribute::deleteAttrII(int argKey)
	{
		return GetP()->deleteAttrII(argKey);
	}

	bool fk_Attribute::deleteAttrID(int argKey)
	{
		return GetP()->deleteAttrID(argKey);
	}

	bool fk_Attribute::deleteAttrIS(int argKey)
	{
		return GetP()->deleteAttrIS(argKey);
	}

	bool fk_Attribute::deleteAttrSI(String^ argKey)
	{
		return GetP()->deleteAttrSI(marshal_as<string>(argKey));
	}

	bool fk_Attribute::deleteAttrSD(String^ argKey)
	{
		return GetP()->deleteAttrSD(marshal_as<string>(argKey));
	}

	bool fk_Attribute::deleteAttrSS(String^ argKey)
	{
		return GetP()->deleteAttrSS(marshal_as<string>(argKey));
	}
}
