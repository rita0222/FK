#include "UniCode_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	::fk_UniChar * fk_UniChar::GetP(void)
	{
		return (::fk_UniChar *)(pBase);
	}

	fk_UniChar::fk_UniChar() : fk_BaseObject(false)
	{
		pBase = new ::fk_UniChar();
	}

	fk_UniChar::fk_UniChar(bool argNewFlg) : fk_BaseObject(false)
	{
		if(argNewFlg == true) {
			pBase = new ::fk_UniChar();
		}
	}

	fk_UniChar::fk_UniChar(int argCode) : fk_BaseObject(false)
	{
		pBase = new ::fk_UniChar(argCode);
	}

	fk_UniChar::~fk_UniChar()
	{
		this->!fk_UniChar();
	}

	fk_UniChar::!fk_UniChar()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	void fk_UniChar::Code::set(int argCode)
	{
		GetP()->setCode(argCode);
	}

	int fk_UniChar::Code::get(void)
	{
		return GetP()->getCode();
	}

	char fk_UniChar::Ascii::get(void)
	{
		return GetP()->getAscii();
	}

	bool fk_UniChar::IsAscii(void)
	{
		return GetP()->isAscii();
	}

	void fk_UniChar::SetBuffer(unsigned char argC1, unsigned char argC2)
	{
		GetP()->setBuffer(argC1, argC2);
	}

	//////////////////////////////////////////////////////////////////////////
	::fk_UniStr * fk_UniStr::GetP(void)
	{
		return (::fk_UniStr *)(pBase);
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

	fk_UniStr::fk_UniStr() : fk_BaseObject(false)
	{
		pBase = new ::fk_UniStr();
	}

	fk_UniStr::fk_UniStr(bool argNewFlg) : fk_BaseObject(false)
	{
		if(argNewFlg == true) {
			pBase = new ::fk_UniStr();
		}
	}

	fk_UniStr::~fk_UniStr()
	{
		this->!fk_UniStr();
	}

	fk_UniStr::!fk_UniStr()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	void fk_UniStr::Clear(void)
	{
		GetP()->clear();
	}

	int fk_UniStr::GetLength(void)
	{
		return GetP()->getLength();
	}

	bool fk_UniStr::GetLine(fk_UniStr^ argStr)
	{
		if(!argStr) return false;
		return GetP()->getLine(argStr->GetP());
	}

	void fk_UniStr::MarkClear(void)
	{
		GetP()->markClear();
	}

	bool fk_UniStr::ReadFile(String^ argFileName, fk_StringCode argCode)
	{
		if(!argFileName) return false;
		return GetP()->readFile(marshal_as<string>(argFileName),
								GetCode(argCode));
	}
		
	bool fk_UniStr::ReadFile(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readFile(marshal_as<string>(argFileName), FK_STR_SJIS);
	}

	void fk_UniStr::CopyStr(fk_UniStr^ argStr)
	{
		if(!argStr) return;
		GetP()->copyStr(argStr->GetP());
	}

	void fk_UniStr::Convert(String^ argStr, fk_StringCode argCode)
	{
		if(!argStr) return;
		GetP()->convert(marshal_as<string>(argStr), GetCode(argCode));
	}

	void fk_UniStr::Convert(String^ argStr)
	{
		if(!argStr) return;
		GetP()->convert(marshal_as<string>(argStr), FK_STR_SJIS);
	}

	int fk_UniStr::GetCode(int argNum)
	{
		return GetP()->getCode(argNum);
	}

	int fk_UniStr::Find(int argStart, int argCode)
	{
		return GetP()->find(argStart, argCode);
	}

	int fk_UniStr::Find(int argStart, unsigned char argC1, unsigned char argC2)
	{
		return GetP()->find(argStart, argC1, argC2);
	}

	void fk_UniStr::PopBack(void)
	{
		GetP()->pop_back();
	}

	void fk_UniStr::PushBack(fk_UniChar^ argC)
	{
		if(!argC) return;
		GetP()->push_back(argC->GetP());
	}

	void fk_UniStr::PushBack(int argCode)
	{
		GetP()->push_back(argCode);
	}
}
