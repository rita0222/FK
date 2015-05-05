#include "Texture_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	fk_TexCoord::operator ::fk_TexCoord (fk_TexCoord^ argC)
	{
		::fk_TexCoord C(argC->x_, argC->y_);
		return C;
	}
	
	fk_TexCoord::fk_TexCoord()
		: x_(0.0), y_(0.0)
	{
		return;
	}

	fk_TexCoord::fk_TexCoord(double argX, double argY)
		: x_(argX), y_(argY)
	{
		return;
	}

	fk_TexCoord::fk_TexCoord(::fk_TexCoord argT)
		: x_(argT.x), y_(argT.y)
	{
		return;
	}
		
	fk_TexCoord::~fk_TexCoord()
	{
		this->!fk_TexCoord();
		return;
	}

	fk_TexCoord::!fk_TexCoord()
	{
		return;
	}

	double fk_TexCoord::x::get()
	{
		return x_;
	}

	void fk_TexCoord::x::set(double v)
	{
		x_ = v;
	}

	double fk_TexCoord::y::get()
	{
		return y_;
	}

	void fk_TexCoord::y::set(double v)
	{
		y_ = v;
	}

	bool fk_TexCoord::Equals(fk_TexCoord^ argT)
	{
		if(!argT) false;
		::fk_TexCoord T1(x_, y_);
		::fk_TexCoord T2(argT->x_, argT->y_);
		return (T1 == T2);
	}

	bool fk_TexCoord::Equals(Object^ argObj)
	{
		if(!argObj) return false;
		if(this == argObj) return true;
		if(GetType() == argObj->GetType()) {
			fk_TexCoord^ T = static_cast<fk_TexCoord^>(argObj);
			::fk_TexCoord T1(x_, y_);
			::fk_TexCoord T2(T->x_, T->y_);
			return (T1 == T2);
		}
		return false;
	}

	void fk_TexCoord::Set(double argX, double argY)
	{
		x_ = argX;
		y_ = argY;
	}

	String^ fk_TexCoord::ToString()
	{
		string tmpBuf;
		tmpBuf = "TxC: " + to_string(x_) + ", ";
		tmpBuf += to_string(y_);
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

