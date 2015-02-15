#include "Attribute_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	bool fk_Attribute::SetAttrII(int argKey, int argValue)
	{
		return GetP()->setAttrII(argKey, argValue);
	}

	bool fk_Attribute::SetAttrID(int argKey, double argValue)
	{
		return GetP()->setAttrID(argKey, argValue);
	}

	bool fk_Attribute::SetAttrIS(int argKey, String^ argValue)
	{
		return GetP()->setAttrIS(argKey, marshal_as<string>(argValue));
	}

	bool fk_Attribute::SetAttrSI(String^ argKey, int argValue)
	{
		return GetP()->setAttrSI(marshal_as<string>(argKey), argValue);
	}

	bool fk_Attribute::SetAttrSD(String^ argKey, double argValue)
	{
		return GetP()->setAttrSD(marshal_as<string>(argKey), argValue);
	}

	bool fk_Attribute::SetAttrSS(String ^argKey, String^ argValue)
	{
		return GetP()->setAttrSS(marshal_as<string>(argKey), marshal_as<string>(argValue));
	}

	int fk_Attribute::GetAttrII(int argKey)
	{
		return GetP()->getAttrII(argKey);
	}

	double fk_Attribute::GetAttrID(int argKey)
	{
		return GetP()->getAttrID(argKey);
	}

	String^ fk_Attribute::GetAttrIS(int argKey)
	{
		return marshal_as<String^>(GetP()->getAttrIS(argKey));
	}

	int fk_Attribute::GetAttrSI(String^ argKey)
	{
		return GetP()->getAttrSI(marshal_as<string>(argKey));
	}

	double fk_Attribute::GetAttrSD(String^ argKey)
	{
		return GetP()->getAttrSD(marshal_as<string>(argKey));
	}

	String^ fk_Attribute::GetAttrSS(String^ argKey)
	{
		string	str = GetP()->getAttrSS(marshal_as<string>(argKey));
		return marshal_as<String^>(str);
	}

	bool fk_Attribute::ExistAttrII(int argKey)
	{
		return GetP()->existAttrII(argKey);
	}

	bool fk_Attribute::ExistAttrID(int argKey)
	{
		return GetP()->existAttrID(argKey);
	}

	bool fk_Attribute::ExistAttrIS(int argKey)
	{
		return GetP()->existAttrIS(argKey);
	}

	bool fk_Attribute::ExistAttrSI(String^ argKey)
	{
		return GetP()->existAttrSI(marshal_as<string>(argKey));
	}

	bool fk_Attribute::ExistAttrSD(String^ argKey)
	{
		return GetP()->existAttrSD(marshal_as<string>(argKey));
	}

	bool fk_Attribute::ExistAttrSS(String^ argKey)
	{
		return GetP()->existAttrSS(marshal_as<string>(argKey));
	}

	bool fk_Attribute::DeleteAttrII(int argKey)
	{
		return GetP()->deleteAttrII(argKey);
	}

	bool fk_Attribute::DeleteAttrID(int argKey)
	{
		return GetP()->deleteAttrID(argKey);
	}

	bool fk_Attribute::DeleteAttrIS(int argKey)
	{
		return GetP()->deleteAttrIS(argKey);
	}

	bool fk_Attribute::DeleteAttrSI(String^ argKey)
	{
		return GetP()->deleteAttrSI(marshal_as<string>(argKey));
	}

	bool fk_Attribute::DeleteAttrSD(String^ argKey)
	{
		return GetP()->deleteAttrSD(marshal_as<string>(argKey));
	}

	bool fk_Attribute::DeleteAttrSS(String^ argKey)
	{
		return GetP()->deleteAttrSS(marshal_as<string>(argKey));
	}
}
