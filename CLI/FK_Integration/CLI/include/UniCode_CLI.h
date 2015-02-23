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
		::fk_UniChar * GetP(void);

	public:
		fk_UniChar();
		fk_UniChar(bool argNewFlg);
		fk_UniChar(int argCode);
		~fk_UniChar();
		!fk_UniChar();

		property int Code {
			int get();
			void set(int);
		}

		property char Ascii {
			char get();
		}
		
		void SetBuffer(unsigned char c1, unsigned char c2);
		bool IsAscii(void);
	};

	public ref class fk_UniStr : fk_BaseObject {

	internal:
		::fk_UniStr * GetP(void);
		static ::fk_StringCode GetCode(fk_StringCode);

	public:
		fk_UniStr();
		fk_UniStr(bool argNewFlg);
		~fk_UniStr();
		!fk_UniStr();

		void	Clear(void);
		int		GetLength(void);
		bool	GetLine(fk_UniStr^ str);
		void	MarkClear(void);
		bool	ReadFile(String^ fileName, fk_StringCode code);
		bool	ReadFile(String^ fileName);
		void	CopyStr(fk_UniStr^ str);
		void	Convert(String^ str, fk_StringCode code);
		void	Convert(String^ str);
		int		GetCode(int num);
		int		Find(int start, int code);
		int		Find(int start, unsigned char c1, unsigned char c2);
		void	PopBack(void);
		void	PushBack(fk_UniChar^ c);
		void	PushBack(int code);
	};
}
