// Texture_CLI.h

#pragma once

#include <FK/Texture.h>
#include "Shape_CLI.h"
#include "Image_CLI.h"

namespace FK_CLI
{
	using namespace std;
	using namespace System;
	using namespace msclr::interop;

	public enum class fk_TexMode {
		MODULATE,
		REPLACE,
		DECAL
	};

	public enum class fk_TexRendMode {
		NORMAL,
		SMOOTH
	};

	public ref class fk_TexCoord {
	internal:
		::fk_TexCoord *pTex;

		::fk_TexCoord * GetP(void)
		{
			return pTex;
		}

	public:
		fk_TexCoord::fk_TexCoord()
		{
			pTex = new ::fk_TexCoord();
		}

		fk_TexCoord::fk_TexCoord(double argX, double argY)
		{
			pTex = new ::fk_TexCoord(argX, argY);
		}

		fk_TexCoord::~fk_TexCoord()
		{
			this->!fk_TexCoord();
		}

		fk_TexCoord::!fk_TexCoord()
		{
			delete pTex;
		}

		property double x {
			double get()
			{
				return double(pTex->x);
			}

			void set(double v)
			{
				pTex->x = float(v);
			}
		}
		
		property double y {
			double get()
			{
				return double(pTex->y);
			}

			void set(double v)
			{
				pTex->y = float(v);
			}
		}

		//////////////////// 比較演算子		
		bool Equals(fk_TexCoord^ argT)
		{
			if(!argT) false;
			return (*argT->pTex == *pTex);
		}

		virtual bool Equals(Object^ argObj) override
		{
			if(!argObj) return false;
			if(this == argObj) return true;
			if(GetType() == argObj->GetType()) {
				fk_TexCoord^ T = static_cast<fk_TexCoord^>(argObj);
				return (*T->pTex == *pTex);
			}
			return false;
		}

		void set(double argX, double argY)
		{
			GetP()->set(argX, argY);
		}
	};

	public ref class fk_Texture : FK_CLI::fk_Shape {
	internal:
		::fk_Texture * GetP(void)
		{
			return (::fk_Texture *)(pBase);
		}

	public:
		fk_Texture::fk_Texture(bool argNewFlg) : fk_Shape(false)
		{
		}

		fk_Texture::~fk_Texture()
		{
			this->!fk_Texture();
		}

		fk_Texture::!fk_Texture()
		{
		}

		void setImage(fk_Image^ argImage)
		{
			if(!argImage) return;
			GetP()->setImage(argImage->GetP());
		}

		fk_Image^ getImage(void)
		{
			fk_Image^ I = gcnew fk_Image(false);
			I->pBase = GetP()->getImage();
			I->dFlg = false;
			return I;
		}

		bool readBMP(String^ argFileName)
		{
			if(!argFileName) return false;
			return GetP()->readBMP(marshal_as<string>(argFileName));
		}

		bool readPNG(String^ argFileName)
		{
			if(!argFileName) return false;
			return GetP()->readPNG(marshal_as<string>(argFileName));
		}

		bool readJPG(String^ argFileName)
		{
			if(!argFileName) return false;
			return GetP()->readJPG(marshal_as<string>(argFileName));
		}

		fk_Dimension^ getImageSize(void)
		{
			fk_Dimension^ D = gcnew fk_Dimension();
			*D->pDim = *GetP()->getImageSize();
			return D;
		}
				
		fk_Dimension^ getBufferSize(void)
		{
			fk_Dimension^ D = gcnew fk_Dimension();
			*D->pDim = *GetP()->getBufferSize();
			return D;
		}
			
		void setTextureMode(fk_TexMode argMode)
		{
			switch(argMode) {
			  case fk_TexMode::MODULATE:
				GetP()->setTextureMode(FK_TEX_MODULATE);
				break;

			  case fk_TexMode::REPLACE:
				GetP()->setTextureMode(FK_TEX_REPLACE);
				break;
				
			  case fk_TexMode::DECAL:
				GetP()->setTextureMode(FK_TEX_DECAL);
				break;

			  default:
				break;
			}
		}
				
		fk_TexMode getTextureMode(void)
		{
			switch(GetP()->getTextureMode()) {
			  case FK_TEX_MODULATE:
				return fk_TexMode::MODULATE;

			  case FK_TEX_REPLACE:
				return fk_TexMode::REPLACE;

			  case FK_TEX_DECAL:
				return fk_TexMode::DECAL;

			  default:
				break;
			}
			return fk_TexMode::MODULATE;
		}
				
		void setTexRendMode(fk_TexRendMode argMode)
		{
			switch(argMode) {
			  case fk_TexRendMode::NORMAL:
				GetP()->setTexRendMode(FK_TEX_REND_NORMAL);
				break;

			  case fk_TexRendMode::SMOOTH:
				GetP()->setTexRendMode(FK_TEX_REND_SMOOTH);
				break;

			  default:
				break;
			}
		}
					
		fk_TexRendMode getTexRendMode(void)
		{
			switch(GetP()->getTexRendMode()) {
			  case FK_TEX_REND_NORMAL:
				return fk_TexRendMode::NORMAL;

			  case FK_TEX_REND_SMOOTH:
				return fk_TexRendMode::SMOOTH;

			  default:
				break;
			}
			return fk_TexRendMode::NORMAL;
		}

		void fillColor(fk_Color^ argC)
		{
			if(!argC) return;
			GetP()->fillColor(*argC->pCol);
		}

		void fillColor(int argR, int argG, int argB, int argA)
		{
			GetP()->fillColor(argR, argG, argB, argA);
		}

		void fillColor(int argR, int argG, int argB)
		{
			GetP()->fillColor(argR, argG, argB);
		}
	};

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
