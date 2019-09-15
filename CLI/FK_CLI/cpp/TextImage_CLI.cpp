/****************************************************************************
 *
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
 *	Copyright (c) 1999-2019, Fine Kernel Project, All rights reserved.
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
#include "TextImage_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;
	
	::FK::fk_TextImage * fk_TextImage::GetP(void)
	{
		return (::FK::fk_TextImage *)(pBase);
	}

	fk_TextImage::fk_TextImage() : fk_Image(false)
	{
		pBase = new ::FK::fk_TextImage();
	}

	fk_TextImage::fk_TextImage(bool argNewFlg) : fk_Image(false)
	{
		if(argNewFlg == true) {
			pBase = new ::FK::fk_TextImage();
		}
	}

	fk_TextImage::~fk_TextImage()
	{
		this->!fk_TextImage();
	}

	fk_TextImage::!fk_TextImage()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	//////////////////////////////////////////////////////////////////////

	void fk_TextImage::DPI::set(int argDPI)
	{
		GetP()->setDPI(argDPI);
	}

	int fk_TextImage::DPI::get(void)
	{
		return GetP()->getDPI();
	}

	void fk_TextImage::PTSize::set(int argSize)
	{
		GetP()->setPTSize(argSize);
	}

	int fk_TextImage::PTSize::get(void)
	{
		return GetP()->getPTSize();
	}

	void fk_TextImage::BoldStrength::set(int argStr)
	{
		GetP()->setBoldStrength(argStr);
	}

	int fk_TextImage::BoldStrength::get(void)
	{
		return GetP()->getBoldStrength();
	}

	void fk_TextImage::ShadowMode::set(bool argMode)
	{
		GetP()->setShadowMode(argMode);
	}

	bool fk_TextImage::ShadowMode::get(void)
	{
		return GetP()->getShadowMode();
	}

	void fk_TextImage::ShadowOffset::set(fk_Dimension^ argD)
	{
		if(!argD) return;
		GetP()->setShadowOffset(argD->pDim->w, argD->pDim->h);
	}

	fk_Dimension^ fk_TextImage::ShadowOffset::get(void)
	{
		fk_Dimension^ D = gcnew fk_Dimension();
		*D->pDim = GetP()->getShadowOffset();
		return D;
	}

	void fk_TextImage::ShadowColor::set(fk_Color^ argCol)
	{
		GetP()->setShadowColor(*argCol->pCol);
	}

	fk_Color^ fk_TextImage::ShadowColor::get(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = GetP()->getShadowColor();
		return C;
	}

	void fk_TextImage::ForeColor::set(fk_Color^ argCol)
	{
		if(!argCol) return;
		GetP()->setForeColor(*argCol->pCol);
	}

	fk_Color^ fk_TextImage::ForeColor::get(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = GetP()->getForeColor();
		return C;
	}

	void fk_TextImage::BackColor::set(fk_Color^ argCol)
	{
		if(!argCol) return;
		GetP()->setBackColor(*argCol->pCol);
	}

	fk_Color^ fk_TextImage::BackColor::get(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = GetP()->getBackColor();
		return C;
	}

	void fk_TextImage::SmoothMode::set(bool argMode)
	{
		GetP()->setSmoothMode(argMode);
	}

	bool fk_TextImage::SmoothMode::get(void)
	{
		return GetP()->getSmoothMode();
	}

	void fk_TextImage::MonospaceMode::set(bool argMode)
	{
		GetP()->setMonospaceMode(argMode);
	}

	bool fk_TextImage::MonospaceMode::get(void)
	{
		return GetP()->getMonospaceMode();
	}

	void fk_TextImage::MonospaceSize::set(int argSize)
	{
		GetP()->setMonospaceSize(argSize);
	}

	int fk_TextImage::MonospaceSize::get(void)
	{
		return GetP()->getMonospaceSize();
	}
	
	void fk_TextImage::CharSkip::set(int argSkip)
	{
		GetP()->setCharSkip(argSkip);
	}

	int fk_TextImage::CharSkip::get(void)
	{
		return GetP()->getCharSkip();
	}

	void fk_TextImage::LineSkip::set(int argSkip)
	{
		GetP()->setLineSkip(argSkip);
	}

	int fk_TextImage::LineSkip::get(void)
	{
		return GetP()->getLineSkip();
	}

	void fk_TextImage::SpaceLineSkip::set(int argSkip)
	{
		GetP()->setSpaceLineSkip(argSkip);
	}
		
	int fk_TextImage::SpaceLineSkip::get(void)
	{
		return GetP()->getSpaceLineSkip();
	}

	void fk_TextImage::Align::set(fk_TextAlign argAlign)
	{
		switch(argAlign) {
		  case fk_TextAlign::LEFT:
			GetP()->setAlign(::FK::fk_TextAlign::LEFT);
			break;

		  case fk_TextAlign::CENTER:
			GetP()->setAlign(::FK::fk_TextAlign::CENTER);
			break;

		  case fk_TextAlign::RIGHT:
			GetP()->setAlign(::FK::fk_TextAlign::RIGHT);
			break;

		  default:
			break;
		}
	}

	fk_TextAlign fk_TextImage::Align::get(void)
	{
		switch(GetP()->getAlign()) {
		case ::FK::fk_TextAlign::LEFT:
			return fk_TextAlign::LEFT;

		case ::FK::fk_TextAlign::CENTER:
			return fk_TextAlign::CENTER;

		case ::FK::fk_TextAlign::RIGHT:
			return fk_TextAlign::RIGHT;

		  default:
			break;
		}
		return fk_TextAlign::CENTER;
	}

	void fk_TextImage::MinLineWidth::set(int argWidth)
	{
		GetP()->setMinLineWidth(argWidth);
	}

	int fk_TextImage::MinLineWidth::get(void)
	{
		return GetP()->getMinLineWidth();
	}

	int fk_TextImage::LineNum::get(void)
	{
		return GetP()->getLineNum();
	}

	int fk_TextImage::AllCharNum::get(void)
	{
		return GetP()->getAllCharNum();
	}

	int fk_TextImage::MaxLineWidth::get(void)
	{
		return GetP()->getMaxLineWidth();
	}

	int fk_TextImage::MaxLineHeight::get(void)
	{
		return GetP()->getMaxLineHeight();
	}


	void fk_TextImage::SendingMode::set(fk_TextSendingMode argMode)
	{
		switch(argMode) {
		  case fk_TextSendingMode::ALL:
			GetP()->setSendingMode(::FK::fk_TextSendingMode::ALL);
			break;

		  case fk_TextSendingMode::CHAR:
			GetP()->setSendingMode(::FK::fk_TextSendingMode::CHAR);
			break;

		  case fk_TextSendingMode::LINE:
			GetP()->setSendingMode(::FK::fk_TextSendingMode::LINE);
			break;

		  default:
			break;
		}
	}

	fk_TextSendingMode fk_TextImage::SendingMode::get(void)
	{
		switch(GetP()->getSendingMode()) {
		case ::FK::fk_TextSendingMode::ALL:
			return fk_TextSendingMode::ALL;

		case ::FK::fk_TextSendingMode::CHAR:
			return fk_TextSendingMode::CHAR;

		case ::FK::fk_TextSendingMode::LINE:
			return fk_TextSendingMode::LINE;
			
		  default:
			break;
		}
		return fk_TextSendingMode::ALL;
	}

	void fk_TextImage::CacheMode::set(bool argMode)
	{
		::FK::fk_TextImage::setCacheMode(argMode);
	}

	bool fk_TextImage::CacheMode::get(void)
	{
		return ::FK::fk_TextImage::getCacheMode();
	}

	//////////////////////////////////////////////////////////////////////

	bool fk_TextImage::InitFont(String^ argFontFileName)
	{
		return GetP()->initFont(marshal_as<string>(argFontFileName));
	}

	void fk_TextImage::SetOffset(int argU, int argD, int argL, int argR)
	{
		GetP()->setOffset(argU, argD, argL, argR);
	}

	int fk_TextImage::GetUpOffset(void)
	{
		return GetP()->getUpOffset();
	}

	int fk_TextImage::GetDownOffset(void)
	{
		return GetP()->getDownOffset();
	}

	int fk_TextImage::GetLeftOffset(void)
	{
		return GetP()->getLeftOffset();
	}

	int fk_TextImage::GetRightOffset(void)
	{
		return GetP()->getRightOffset();
	}

	bool fk_TextImage::LoadUniStr(fk_UniStr^ argStr)
	{
		if(!argStr) return false;
		return GetP()->loadUniStr(argStr->GetP());
	}

	bool fk_TextImage::LoadStrFile(String^ argFileName, fk_StringCode argCode)
	{
		if(!argFileName) return false;
		return GetP()->loadStrFile(marshal_as<string>(argFileName),
								   fk_UniStr::GetCode(argCode));
	}

	bool fk_TextImage::LoadStrFile(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->loadStrFile(marshal_as<string>(argFileName),
			::FK::fk_StringCode::UTF8);
	}

	int fk_TextImage::GetLineCharNum(int argNum)
	{
		return GetP()->getLineCharNum(argNum);
	}

	int fk_TextImage::GetLineWidth(int argNum)
	{
		return GetP()->getLineWidth(argNum);
	}

	int fk_TextImage::GetLineHeight(int argNum)
	{
		return GetP()->getLineHeight(argNum);
	}

	int fk_TextImage::GetLineStartXPos(int argNum)
	{
		return GetP()->getLineStartXPos(argNum);
	}

	int fk_TextImage::GetLineStartYPos(int argNum)
	{
		return GetP()->getLineStartYPos(argNum);
	}

	bool fk_TextImage::Send(void)
	{
		return GetP()->send();
	}

	bool fk_TextImage::Finish(void)
	{
		return GetP()->finish();
	}

	bool fk_TextImage::Clear(void)
	{
		return GetP()->clear();
	}

	void fk_TextImage::ClearCache(void)
	{
		::FK::fk_TextImage::clearCache();
	}
}

