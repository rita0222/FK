// Texture_CLI.h

#pragma once

#include <FK/Texture.h>
#include "Shape_CLI.h"
#include "Image_CLI.h"
#include <string>

namespace FK_CLI
{
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

		String^ fk_TexCoord::ToString() override;
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

		void setImage(fk_Image^ image);
		fk_Image^ getImage(void);
		bool readBMP(String^ fileName);
		bool readPNG(String^ fileName);
		bool readJPG(String^ fileName);
		fk_Dimension^ getImageSize(void);
		fk_Dimension^ getBufferSize(void);
		void setTextureMode(fk_TexMode mode);
		fk_TexMode getTextureMode(void);
		void setTexRendMode(fk_TexRendMode mode);
		fk_TexRendMode getTexRendMode(void);
		void fillColor(fk_Color^ color);
		void fillColor(int r, int g, int b, int a);
		void fillColor(int r, int g, int b);
	};
}
