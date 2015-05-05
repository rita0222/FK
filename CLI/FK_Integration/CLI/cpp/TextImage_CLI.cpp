#include "TextImage_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;
	
	::fk_TextImage * fk_TextImage::GetP(void)
	{
		return (::fk_TextImage *)(pBase);
	}

	fk_TextImage::fk_TextImage() : fk_Image(false)
	{
		pBase = new ::fk_TextImage();
	}

	fk_TextImage::fk_TextImage(bool argNewFlg) : fk_Image(false)
	{
		if(argNewFlg == true) {
			pBase = new ::fk_TextImage();
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
			GetP()->setAlign(FK_ALIGN_LEFT);
			break;

		  case fk_TextAlign::CENTER:
			GetP()->setAlign(FK_ALIGN_CENTER);
			break;

		  case fk_TextAlign::RIGHT:
			GetP()->setAlign(FK_ALIGN_RIGHT);
			break;

		  default:
			break;
		}
	}

	fk_TextAlign fk_TextImage::Align::get(void)
	{
		switch(GetP()->getAlign()) {
		  case FK_ALIGN_LEFT:
			return fk_TextAlign::LEFT;

		  case FK_ALIGN_CENTER:
			return fk_TextAlign::CENTER;

		  case FK_ALIGN_RIGHT:
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
			GetP()->setSendingMode(FK_SENDING_ALL);
			break;

		  case fk_TextSendingMode::CHAR:
			GetP()->setSendingMode(FK_SENDING_CHAR);
			break;

		  case fk_TextSendingMode::LINE:
			GetP()->setSendingMode(FK_SENDING_LINE);
			break;

		  default:
			break;
		}
	}

	fk_TextSendingMode fk_TextImage::SendingMode::get(void)
	{
		switch(GetP()->getSendingMode()) {
		  case FK_SENDING_ALL:
			return fk_TextSendingMode::ALL;

		  case FK_SENDING_CHAR:
			return fk_TextSendingMode::CHAR;

		  case FK_SENDING_LINE:
			return fk_TextSendingMode::LINE;
			
		  default:
			break;
		}
		return fk_TextSendingMode::ALL;
	}

	void fk_TextImage::CacheMode::set(bool argMode)
	{
		::fk_TextImage::setCacheMode(argMode);
	}

	bool fk_TextImage::CacheMode::get(void)
	{
		return ::fk_TextImage::getCacheMode();
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
		return GetP()->loadStrFile(marshal_as<string>(argFileName), FK_STR_UTF8);
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
		::fk_TextImage::clearCache();
	}
}
