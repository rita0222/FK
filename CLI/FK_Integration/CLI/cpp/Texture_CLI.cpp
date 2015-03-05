#include "Texture_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	::fk_TexCoord * fk_TexCoord::GetP(void)
	{
		return pTex;
	}

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

	double fk_TexCoord::x::get()
	{
		return double(pTex->x);
	}

	void fk_TexCoord::x::set(double v)
	{
		pTex->x = float(v);
	}

	double fk_TexCoord::y::get()
	{
		return double(pTex->y);
	}

	void fk_TexCoord::y::set(double v)
	{
		pTex->y = float(v);
	}

	bool fk_TexCoord::Equals(fk_TexCoord^ argT)
	{
		if(!argT) false;
		return (*argT->pTex == *pTex);
	}

	bool fk_TexCoord::Equals(Object^ argObj)
	{
		if(!argObj) return false;
		if(this == argObj) return true;
		if(GetType() == argObj->GetType()) {
			fk_TexCoord^ T = static_cast<fk_TexCoord^>(argObj);
			return (*T->pTex == *pTex);
		}
		return false;
	}

	void fk_TexCoord::Set(double argX, double argY)
	{
		GetP()->set(argX, argY);
	}

	String^ fk_TexCoord::ToString()
	{
		string tmpBuf;
		tmpBuf = "TxC: " + to_string(pTex->x) + ", ";
		tmpBuf += to_string(pTex->y);
		return gcnew String(tmpBuf.c_str());
	}

	//////////////////////////////////////////////////////////////////////////

	::fk_Texture * fk_Texture::GetP(void)
	{
		return (::fk_Texture *)(pBase);
	}
	
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

	void fk_Texture::Image::set(fk_Image^ argImage)
	{
		if(!argImage) return;
		GetP()->setImage(argImage->GetP());
	}

	fk_Image^ fk_Texture::Image::get(void)
	{
		fk_Image^ I = gcnew fk_Image(false);
		I->pBase = GetP()->getImage();
		I->dFlg = false;
		return I;
	}

	fk_Dimension^ fk_Texture::ImageSize::get(void)
	{
		fk_Dimension^ D = gcnew fk_Dimension();
		*D->pDim = *GetP()->getImageSize();
		return D;
	}
				
	fk_Dimension^ fk_Texture::BufferSize::get(void)
	{
		fk_Dimension^ D = gcnew fk_Dimension();
		*D->pDim = *GetP()->getBufferSize();
		return D;
	}

	void fk_Texture::TextureMode::set(fk_TexMode argMode)
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
				
	fk_TexMode fk_Texture::TextureMode::get(void)
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
				
	void fk_Texture::RendMode::set(fk_TexRendMode argMode)
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
					
	fk_TexRendMode fk_Texture::RendMode::get(void)
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
	
	bool fk_Texture::ReadBMP(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readBMP(marshal_as<string>(argFileName));
	}

	bool fk_Texture::ReadPNG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readPNG(marshal_as<string>(argFileName));
	}

	bool fk_Texture::ReadJPG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readJPG(marshal_as<string>(argFileName));
	}

	void fk_Texture::FillColor(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->fillColor(*argC->pCol);
	}
}

