#include "Texture_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	String^ fk_TexCoord::ToString()
	{
		string tmpBuf;
		tmpBuf = "TxC: " + to_string(pTex->x) + ", ";
		tmpBuf += to_string(pTex->y);
		return gcnew String(tmpBuf.c_str());
	}
	void fk_Texture::setImage(fk_Image^ argImage)
	{
		if(!argImage) return;
		GetP()->setImage(argImage->GetP());
	}

	fk_Image^ fk_Texture::getImage(void)
	{
		fk_Image^ I = gcnew fk_Image(false);
		I->pBase = GetP()->getImage();
		I->dFlg = false;
		return I;
	}

	bool fk_Texture::readBMP(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readBMP(marshal_as<string>(argFileName));
	}

	bool fk_Texture::readPNG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readPNG(marshal_as<string>(argFileName));
	}

	bool fk_Texture::readJPG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readJPG(marshal_as<string>(argFileName));
	}

	fk_Dimension^ fk_Texture::getImageSize(void)
	{
		fk_Dimension^ D = gcnew fk_Dimension();
		*D->pDim = *GetP()->getImageSize();
		return D;
	}
				
	fk_Dimension^ fk_Texture::getBufferSize(void)
	{
		fk_Dimension^ D = gcnew fk_Dimension();
		*D->pDim = *GetP()->getBufferSize();
		return D;
	}
			
	void fk_Texture::setTextureMode(fk_TexMode argMode)
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
				
	fk_TexMode fk_Texture::getTextureMode(void)
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
				
	void fk_Texture::setTexRendMode(fk_TexRendMode argMode)
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
					
	fk_TexRendMode fk_Texture::getTexRendMode(void)
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

	void fk_Texture::fillColor(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->fillColor(*argC->pCol);
	}

	void fk_Texture::fillColor(int argR, int argG, int argB, int argA)
	{
		GetP()->fillColor(argR, argG, argB, argA);
	}

	void fk_Texture::fillColor(int argR, int argG, int argB)
	{
		GetP()->fillColor(argR, argG, argB);
	}
}

