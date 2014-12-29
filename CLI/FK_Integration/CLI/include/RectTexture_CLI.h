// RectTexture_CLI.h

#pragma once

#include <FK/Texture.h>
#include "Texture_CLI.h"

namespace FK_CLI
{
	public ref class fk_RectTexture : FK_CLI::fk_Texture {
	internal:
		::fk_RectTexture * GetP(void)
		{
			return (::fk_RectTexture *)(pBase);
		}

	public:
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
			if(dFlg == true) delete pBase;
			pBase = NULL;
		}
		
		void init(void);
		bool setTextureSize(double w, double h);
		fk_TexCoord^ getTextureSize(void);
		void setRepeatMode(bool mode);
		bool getRepeatMode(void);
		void setRepeatParam(double w, double h);
		fk_TexCoord^ getRepeatParam(void);
		void setTextureCoord(double startX, double startY, double endX, double endY);
		void setTextureCoord(fk_TexCoord^ startT, fk_TexCoord^ endT);
		fk_TexCoord^ getTextureCoord(int ID);
	};
}
