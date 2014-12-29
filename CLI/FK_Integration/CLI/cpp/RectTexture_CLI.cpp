#include "RectTexture_CLI.h"

namespace FK_CLI {

	void fk_RectTexture::init(void)
	{
		GetP()->init();
	}

	bool fk_RectTexture::setTextureSize(double argW, double argH)
	{
		return GetP()->setTextureSize(argW, argH);
	}

	fk_TexCoord^ fk_RectTexture::getTextureSize(void)
	{
		fk_TexCoord^ T = gcnew fk_TexCoord();
		*T->pTex = GetP()->getTextureSize();
		return T;
	}

	void fk_RectTexture::setRepeatMode(bool argMode)
	{
		GetP()->setRepeatMode(argMode);
	}

	bool fk_RectTexture::getRepeatMode(void)
	{
		return GetP()->getRepeatMode();
	}

	void fk_RectTexture::setRepeatParam(double argW, double argH)
	{
		GetP()->setRepeatParam(argW, argH);
	}

	fk_TexCoord^ fk_RectTexture::getRepeatParam(void)
	{
		fk_TexCoord^ T = gcnew fk_TexCoord();
		*T->pTex = GetP()->getRepeatParam();
		return T;
	}
			
	void fk_RectTexture::setTextureCoord(double argSX, double argSY, double argEX, double argEY)
	{
		GetP()->setTextureCoord(argSX, argSY, argEX, argEY);
	}

	void fk_RectTexture::setTextureCoord(fk_TexCoord^ argS, fk_TexCoord^ argE)
	{
		if(!argS || !argE) return;
		GetP()->setTextureCoord(*argS->pTex, *argE->pTex);
	}

	fk_TexCoord^ fk_RectTexture::getTextureCoord(int argID)
	{
		fk_TexCoord^ T = gcnew fk_TexCoord();
		*T->pTex = GetP()->getTextureCoord(argID);
		return T;
	}
}
