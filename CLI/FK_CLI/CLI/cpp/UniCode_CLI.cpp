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
/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
 *
 *	Redistribution and use in source and binary forms,
 *	with or without modification, are permitted provided that the
 *	following conditions are met:
 *
 *		- Redistributions of source code must retain the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer.
 *
 *		- Redistributions in binary form must reproduce the above
 *			copyright notice, this list of conditions and the
 *			following disclaimer in the documentation and/or
 *			other materials provided with the distribution.
 *
 *		- Neither the name of the copyright holders nor the names
 *			of its contributors may be used to endorse or promote
 *			products derived from this software without specific
 *			prior written permission.
 *
 *	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *	FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *	COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *	HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 *	STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *	IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *	POSSIBILITY OF SUCH DAMAGE. 
 *
 ****************************************************************************/
/****************************************************************************
 *
 *	Copyright (c) 1999-2016, Fine Kernel Project, All rights reserved.
 *
 *	本ソフトウェアおよびソースコードのライセンスは、基本的に
 *	「修正 BSD ライセンス」に従います。以下にその詳細を記します。
 *
 *	ソースコード形式かバイナリ形式か、変更するかしないかを問わず、
 *	以下の条件を満たす場合に限り、再頒布および使用が許可されます。
 *
 *	- ソースコードを再頒布する場合、上記の著作権表示、本条件一覧、
 *		および下記免責条項を含めること。
 *
 *	- バイナリ形式で再頒布する場合、頒布物に付属のドキュメント等の
 *		資料に、上記の著作権表示、本条件一覧、および下記免責条項を
 *		含めること。
 *
 *	- 書面による特別の許可なしに、本ソフトウェアから派生した製品の
 *		宣伝または販売促進に、本ソフトウェアの著作権者の名前または
 *		コントリビューターの名前を使用してはならない。
 *
 *	本ソフトウェアは、著作権者およびコントリビューターによって「現
 *	状のまま」提供されており、明示黙示を問わず、商業的な使用可能性、
 *	および特定の目的に対する適合性に関す暗黙の保証も含め、またそれ
 *	に限定されない、いかなる保証もないものとします。著作権者もコン
 *	トリビューターも、事由のいかんを問わず、損害発生の原因いかんを
 *	問わず、かつ責任の根拠が契約であるか厳格責任であるか(過失その
 *	他の)不法行為であるかを問わず、仮にそのような損害が発生する可
 *	能性を知らされていたとしても、本ソフトウェアの使用によって発生
 *	した(代替品または代用サービスの調達、使用の喪失、データの喪失、
 *	利益の喪失、業務の中断も含め、またそれに限定されない)直接損害、
 *	間接損害、偶発的な損害、特別損害、懲罰的損害、または結果損害に
 *	ついて、一切責任を負わないものとします。
 *
 ****************************************************************************/
