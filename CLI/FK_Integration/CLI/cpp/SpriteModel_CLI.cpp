#include "SpriteModel_CLI.h"
#include <msclr/marshal_cppstd.h>


namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	bool fk_SpriteModel::readBMP(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readBMP(marshal_as<string>(argFileName));
	}

	bool fk_SpriteModel::readPNG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readPNG(marshal_as<string>(argFileName));
	}
		
	bool fk_SpriteModel::readJPG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readJPG(marshal_as<string>(argFileName));
	}

	void fk_SpriteModel::setImage(fk_Image^ argImage)
	{
		if(!argImage) return;
		GetP()->setImage(*argImage->GetP());
	}

	fk_Image^ fk_SpriteModel::getImage(void)
	{
		fk_Image ^I = gcnew fk_Image();
		I->pBase = GetP()->getImage();
		I->dFlg = false;
		return I;
	}

	void fk_SpriteModel::setPositionLT(double argX, double argY)
	{
		GetP()->setPositionLT(argX, argY);
	}

	void fk_SpriteModel::setSpriteArea(double argX, double argY, double argW, double argH)
	{
		GetP()->setSpriteArea(argX, argY, argW, argH);
	}

	void fk_SpriteModel::setSpriteSize(double argW, double argH)
	{
		GetP()->setSpriteSize(argW, argH);
	}

	fk_TexCoord^ fk_SpriteModel::getSpriteSize(void)
	{
		fk_TexCoord^ T = gcnew fk_TexCoord();
		*T->pTex = GetP()->getSpriteSize();
		return T;
	}

	void fk_SpriteModel::setSpriteSmoothMode(bool argMode)
	{
		GetP()->setSpriteSmoothMode(argMode);
	}

	bool fk_SpriteModel::getSpriteSmoothMode(void)
	{
		return GetP()->getSpriteSmoothMode();
	}

	bool fk_SpriteModel::initFont(String^ argFont)
	{
		if(!argFont) return false;
		return GetP()->initFont(marshal_as<string>(argFont));
	}

	void fk_SpriteModel::drawText(String^ argStr)
	{
		if(!argStr) return;
		GetP()->drawText(marshal_as<string>(argStr), FK_STR_SJIS);
	}

	void fk_SpriteModel::drawText(String^ argStr, bool argMode)
	{
		if(!argStr) return;
		GetP()->drawText(marshal_as<string>(argStr), argMode, FK_STR_SJIS);
	}

	void fk_SpriteModel::clearText(void)
	{
		GetP()->clearText();
	}
}
