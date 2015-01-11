#include "UniCode_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	void fk_UniChar::setBuffer(unsigned char argC1, unsigned char argC2)
	{
		GetP()->setBuffer(argC1, argC2);
	}

	void fk_UniChar::setCode(int argCode)
	{
		GetP()->setCode(argCode);
	}

	int fk_UniChar::getCode(void)
	{
		return GetP()->getCode();
	}

	bool fk_UniChar::isAscii(void)
	{
		return GetP()->isAscii();
	}

	char fk_UniChar::getAscii(void)
	{
		return GetP()->getAscii();
	}

	::fk_StringCode fk_UniStr::GetCode(fk_StringCode argCode)
	{
		switch(argCode) {
		  case fk_StringCode::UTF16:
			return FK_STR_UTF16;

		  case fk_StringCode::UTF8:
			return FK_STR_UTF8;

		  case fk_StringCode::JIS:
			return FK_STR_JIS;

		  case fk_StringCode::SJIS:
			return FK_STR_SJIS;

		  case fk_StringCode::EUC:
			return FK_STR_EUC;

		  default:
			break;
		}
		return FK_STR_UTF16;
	}

	void fk_UniStr::clear(void)
	{
		GetP()->clear();
	}

	int fk_UniStr::getLength(void)
	{
		return GetP()->getLength();
	}

	bool fk_UniStr::getLine(fk_UniStr^ argStr)
	{
		if(!argStr) return false;
		return GetP()->getLine(argStr->GetP());
	}

	void fk_UniStr::markClear(void)
	{
		GetP()->markClear();
	}

	bool fk_UniStr::readFile(String^ argFileName, fk_StringCode argCode)
	{
		if(!argFileName) return false;
		return GetP()->readFile(marshal_as<string>(argFileName),
								GetCode(argCode));
	}
		
	bool fk_UniStr::readFile(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readFile(marshal_as<string>(argFileName), FK_STR_SJIS);
	}

	void fk_UniStr::copyStr(fk_UniStr^ argStr)
	{
		if(!argStr) return;
		GetP()->copyStr(argStr->GetP());
	}

	void fk_UniStr::convert(String^ argStr, fk_StringCode argCode)
	{
		if(!argStr) return;
		GetP()->convert(marshal_as<string>(argStr), GetCode(argCode));
	}

	void fk_UniStr::convert(String^ argStr)
	{
		if(!argStr) return;
		GetP()->convert(marshal_as<string>(argStr), FK_STR_SJIS);
	}

	int fk_UniStr::getCode(int argNum)
	{
		return GetP()->getCode(argNum);
	}

	int fk_UniStr::find(int argStart, int argCode)
	{
		return GetP()->find(argStart, argCode);
	}

	int fk_UniStr::find(int argStart, unsigned char argC1, unsigned char argC2)
	{
		return GetP()->find(argStart, argC1, argC2);
	}

	void fk_UniStr::pop_back(void)
	{
		GetP()->pop_back();
	}

	void fk_UniStr::push_back(fk_UniChar^ argC)
	{
		if(!argC) return;
		GetP()->push_back(argC->GetP());
	}

	void fk_UniStr::push_back(int argCode)
	{
		GetP()->push_back(argCode);
	}
}
