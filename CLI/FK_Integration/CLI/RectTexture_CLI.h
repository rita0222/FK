// Texture_CLI.h

#pragma once

#include <FK/Texture.h>
#include "Texture_CLI.h"

namespace FK_CLI
{
	using namespace std;
	using namespace System;

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
		
		void init(void)
		{
			GetP()->init();
		}

		bool setTextureSize(double argW, double argH)
		{
			return GetP()->setTextureSize(argW, argH);
		}

		fk_TexCoord^ getTextureSize(void)
		{
			fk_TexCoord^ T = gcnew fk_TexCoord();
			*T->pTex = GetP()->getTextureSize();
			return T;
		}

		void setRepeatMode(bool argMode)
		{
			GetP()->setRepeatMode(argMode);
		}

		bool getRepeatMode(void)
		{
			return GetP()->getRepeatMode();
		}

		void setRepeatParam(double argW, double argH)
		{
			GetP()->setRepeatParam(argW, argH);
		}

		fk_TexCoord^ getRepeatParam(void)
		{
			fk_TexCoord^ T = gcnew fk_TexCoord();
			*T->pTex = GetP()->getRepeatParam();
			return T;
		}
			
		void setTextureCoord(double argSX, double argSY, double argEX, double argEY)
		{
			GetP()->setTextureCoord(argSX, argSY, argEX, argEY);
		}

		void setTextureCoord(fk_TexCoord^ argS, fk_TexCoord^ argE)
		{
			if(!argS || !argE) return;
			GetP()->setTextureCoord(*argS->pTex, *argE->pTex);
		}

		fk_TexCoord^ getTextureCoord(int argID)
		{
			fk_TexCoord^ T = gcnew fk_TexCoord();
			*T->pTex = GetP()->getTextureCoord(argID);
			return T;
		}
	};
}
