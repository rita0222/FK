// UniCode_CLI.h

#pragma once

#include <FK/UniCode.h>
#include "Base_CLI.h"

namespace FK_CLI
{
	public enum class fk_StringCode {
		UTF16,
		UTF8,
		JIS,
		SJIS,
		EUC
	};

	public ref class fk_UniChar : fk_BaseObject {
	internal:
		::fk_UniChar * GetP(void)
		{
			return (::fk_UniChar *)(pBase);
		}

	public:
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
			if(pBase == NULL) return;
			if(dFlg == true) delete GetP();
			pBase = NULL;
		}

		void setBuffer(unsigned char c1, unsigned char c2);
		void setCode(int code);
		int getCode(void);
		bool isAscii(void);
		char getAscii(void);
	};

	public ref class fk_UniStr : fk_BaseObject {

	internal:
		static ::fk_StringCode GetCode(fk_StringCode);

		::fk_UniStr * GetP(void)
		{
			return (::fk_UniStr *)(pBase);
		}
	public:
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
			if(dFlg == true) delete pBase;
			pBase = NULL;
		}

		void clear(void);
		int getLength(void);
		bool getLine(fk_UniStr^ str);
		void markClear(void);
		bool readFile(String^ fileName, fk_StringCode code);
		bool readFile(String^ fileName);
		void copyStr(fk_UniStr^ str);
		void convert(String^ str, fk_StringCode code);
		void convert(String^ str);
		int getCode(int num);
		int find(int start, int code);
		int find(int start, unsigned char c1, unsigned char c2);
		void pop_back(void);
		void push_back(fk_UniChar^ c);
		void push_back(int code);
	};
}
