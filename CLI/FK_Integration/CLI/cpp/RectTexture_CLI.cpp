#include "RectTexture_CLI.h"

namespace FK_CLI {

	::fk_RectTexture * fk_RectTexture::GetP(void)
	{
		return (::fk_RectTexture *)(pBase);
	}

	fk_RectTexture::fk_RectTexture() : fk_Texture(false)
	{
		pBase = new ::fk_RectTexture();
	}

	fk_RectTexture::fk_RectTexture(bool argNewFlg) : fk_Texture(false)
	{
		if(argNewFlg == true) {
			pBase = new ::fk_RectTexture();
		}
	}

	fk_RectTexture::fk_RectTexture(fk_Image^ argImage) : fk_Texture(false)
	{
		if(!argImage) {
			pBase = new ::fk_RectTexture();
		} else {
			pBase = new ::fk_RectTexture(argImage->GetP());
		}
	}

	fk_RectTexture::~fk_RectTexture()
	{
		this->!fk_RectTexture();
	}

	fk_RectTexture::!fk_RectTexture()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	void fk_RectTexture::TextureSize::set(fk_TexCoord^ argC)
	{
		if(!argC) return;
		GetP()->setTextureSize(argC->x_, argC->y_);
	}

	fk_TexCoord^ fk_RectTexture::TextureSize::get(void)
	{
		return gcnew fk_TexCoord(GetP()->getTextureSize());
	}
	
	void fk_RectTexture::RepeatMode::set(bool argMode)
	{
		GetP()->setRepeatMode(argMode);
	}

	bool fk_RectTexture::RepeatMode::get(void)
	{
		return GetP()->getRepeatMode();
	}
	
	void fk_RectTexture::RepeatParam::set(fk_TexCoord^ argC)
	{
		if(!argC) return;
		GetP()->setRepeatParam(argC->x_, argC->y_);
	}

	fk_TexCoord^ fk_RectTexture::RepeatParam::get(void)
	{
		return gcnew fk_TexCoord(GetP()->getRepeatParam());
	}
			
	void fk_RectTexture::Init(void)
	{
		GetP()->init();
	}

	void fk_RectTexture::SetTextureCoord(double argSX, double argSY, double argEX, double argEY)
	{
		GetP()->setTextureCoord(argSX, argSY, argEX, argEY);
	}

	void fk_RectTexture::SetTextureCoord(fk_TexCoord^ argS, fk_TexCoord^ argE)
	{
		if(!argS || !argE) return;
		GetP()->setTextureCoord(argS, argE);
	}

	fk_TexCoord^ fk_RectTexture::GetTextureCoord(int argID)
	{
		return gcnew fk_TexCoord(GetP()->getTextureCoord(argID));
	}
}
