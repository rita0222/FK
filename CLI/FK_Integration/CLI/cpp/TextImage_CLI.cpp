#include "TextImage_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;
	
	bool fk_TextImage::initFont(String^ argFontFileName)
	{
		return GetP()->initFont(marshal_as<string>(argFontFileName));
	}
		
	void fk_TextImage::setDPI(int argDPI)
	{
		GetP()->setDPI(argDPI);
	}

	int fk_TextImage::getDPI(void)
	{
		return GetP()->getDPI();
	}

	void fk_TextImage::setPTSize(int argSize)
	{
		GetP()->setPTSize(argSize);
	}

	int fk_TextImage::getPTSize(void)
	{
		return GetP()->getPTSize();
	}

	void fk_TextImage::setBoldStrength(int argStr)
	{
		GetP()->setBoldStrength(argStr);
	}

	int fk_TextImage::getBoldStrength(void)
	{
		return GetP()->getBoldStrength();
	}

	void fk_TextImage::setShadowMode(bool argMode)
	{
		GetP()->setShadowMode(argMode);
	}

	bool fk_TextImage::getShadowMode(void)
	{
		return GetP()->getShadowMode();
	}

	void fk_TextImage::setShadowOffset(int argX, int argY)
	{
		GetP()->setShadowOffset(argX, argY);
	}

	fk_Dimension^ fk_TextImage::getShadowOffset(void)
	{
		fk_Dimension^ D = gcnew fk_Dimension();
		*D->pDim = GetP()->getShadowOffset();
		return D;
	}

	void fk_TextImage::setShadowColor(fk_Color^ argCol)
	{
		GetP()->setShadowColor(*argCol->pCol);
	}

	void fk_TextImage::setShadowColor(float argR, float argG, float argB, float argA)
	{
		GetP()->setShadowColor(argR, argG, argB, argA);
	}

	void fk_TextImage::setShadowColor(double argR, double argG, double argB, double argA)
	{
		GetP()->setShadowColor(argR, argG, argB, argA);
	}

	fk_Color^ fk_TextImage::getShadowColor(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = GetP()->getShadowColor();
		return C;
	}

	void fk_TextImage::setForeColor(fk_Color^ argCol)
	{
		if(!argCol) return;
		GetP()->setForeColor(*argCol->pCol);
	}

	void fk_TextImage::setForeColor(float argR, float argG, float argB, float argA)
	{
		GetP()->setForeColor(argR, argG, argB, argA);
	}

	void fk_TextImage::setForeColor(double argR, double argG, double argB, double argA)
	{
		GetP()->setForeColor(argR, argG, argB, argA);
	}

	fk_Color^ fk_TextImage::getForeColor(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = GetP()->getForeColor();
		return C;
	}

	void fk_TextImage::setBackColor(fk_Color^ argCol)
	{
		if(!argCol) return;
		GetP()->setBackColor(*argCol->pCol);
	}

	void fk_TextImage::setBackColor(float argR, float argG, float argB, float argA)
	{
		GetP()->setBackColor(argR, argG, argB, argA);
	}

	void fk_TextImage::setBackColor(double argR, double argG, double argB, double argA)
	{
		GetP()->setBackColor(argR, argG, argB, argA);
	}

	fk_Color^ fk_TextImage::getBackColor(void)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = GetP()->getBackColor();
		return C;
	}

	void fk_TextImage::setSmoothMode(bool argMode)
	{
		GetP()->setSmoothMode(argMode);
	}

	bool fk_TextImage::getSmoothMode(void)
	{
		return GetP()->getSmoothMode();
	}

	void fk_TextImage::setCharSkip(int argSkip)
	{
		GetP()->setCharSkip(argSkip);
	}

	int fk_TextImage::getCharSkip(void)
	{
		return GetP()->getCharSkip();
	}

	void fk_TextImage::setLineSkip(int argSkip)
	{
		GetP()->setLineSkip(argSkip);
	}

	int fk_TextImage::getLineSkip(void)
	{
		return GetP()->getLineSkip();
	}

	void fk_TextImage::setSpaceLineSkip(int argSkip)
	{
		GetP()->setSpaceLineSkip(argSkip);
	}
		
	int fk_TextImage::getSpaceLineSkip(void)
	{
		return GetP()->getSpaceLineSkip();
	}

	void fk_TextImage::setOffset(int argU, int argD, int argL, int argR)
	{
		GetP()->setOffset(argU, argD, argL, argR);
	}

	int fk_TextImage::getUpOffset(void)
	{
		return GetP()->getUpOffset();
	}

	int fk_TextImage::getDownOffset(void)
	{
		return GetP()->getDownOffset();
	}

	int fk_TextImage::getLeftOffset(void)
	{
		return GetP()->getLeftOffset();
	}

	int fk_TextImage::getRightOffset(void)
	{
		return GetP()->getRightOffset();
	}

	void fk_TextImage::setAlign(fk_TextAlign argAlign)
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

	fk_TextAlign fk_TextImage::getAlign(void)
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

	void fk_TextImage::setMinLineWidth(int argWidth)
	{
		GetP()->setMinLineWidth(argWidth);
	}

	int fk_TextImage::getMinLineWidth(void)
	{
		return GetP()->getMinLineWidth();
	}

	bool fk_TextImage::loadUniStr(fk_UniStr^ argStr)
	{
		if(!argStr) return false;
		return GetP()->loadUniStr(argStr->GetP());
	}

	bool fk_TextImage::loadStrFile(String^ argFileName, fk_StringCode argCode)
	{
		if(!argFileName) return false;
		return GetP()->loadStrFile(marshal_as<string>(argFileName),
								   fk_UniStr::GetCode(argCode));
	}

	bool fk_TextImage::loadStrFile(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->loadStrFile(marshal_as<string>(argFileName), FK_STR_UTF8);
	}

	int fk_TextImage::getLineNum(void)
	{
		return GetP()->getLineNum();
	}

	int fk_TextImage::getLineCharNum(int argNum)
	{
		return GetP()->getLineCharNum(argNum);
	}

	int fk_TextImage::getAllCharNum(void)
	{
		return GetP()->getAllCharNum();
	}

	int fk_TextImage::getMaxLineWidth(void)
	{
		return GetP()->getMaxLineWidth();
	}

	int fk_TextImage::getMaxLineHeight(void)
	{
		return GetP()->getMaxLineHeight();
	}

	int fk_TextImage::getLineWidth(int argNum)
	{
		return GetP()->getLineWidth(argNum);
	}

	int fk_TextImage::getLineHeight(int argNum)
	{
		return GetP()->getLineHeight(argNum);
	}

	int fk_TextImage::getLineStartXPos(int argNum)
	{
		return GetP()->getLineStartXPos(argNum);
	}

	int fk_TextImage::getLineStartYPos(int argNum)
	{
		return GetP()->getLineStartYPos(argNum);
	}

	void fk_TextImage::setSendingMode(fk_TextSendingMode argMode)
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

	fk_TextSendingMode fk_TextImage::getSendingMode(void)
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

	bool fk_TextImage::send(void)
	{
		return GetP()->send();
	}

	bool fk_TextImage::finish(void)
	{
		return GetP()->finish();
	}

	bool fk_TextImage::clear(void)
	{
		return GetP()->clear();
	}

	void fk_TextImage::setCacheMode(bool argMode)
	{
		::fk_TextImage::setCacheMode(argMode);
	}

	bool fk_TextImage::getCacheMode(void)
	{
		return ::fk_TextImage::getCacheMode();
	}

	void fk_TextImage::clearCache(void)
	{
		::fk_TextImage::clearCache();
	}
}
