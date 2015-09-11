#include "Image_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	::fk_Dimension * fk_Dimension::GetP(void)
	{
		return pDim;
	}

	fk_Dimension::fk_Dimension()
	{
		pDim = new ::fk_Dimension();
	}

	fk_Dimension::fk_Dimension(int argW, int argH)
	{
		pDim = new ::fk_Dimension(argW, argH);
	}

	fk_Dimension::~fk_Dimension()
	{
		this->!fk_Dimension();
	}

	fk_Dimension::!fk_Dimension()
	{
		delete pDim;
	}
	
	int fk_Dimension::w::get()
	{
		return pDim->w;
	}

	void fk_Dimension::w::set(int value)
	{
		pDim->w = value;
	}

	int fk_Dimension::h::get()
	{
		return pDim->h;
	}

	void fk_Dimension::h::set(int value)
	{
		pDim->h = value;
	}

	int fk_Dimension::x::get()
	{
		return pDim->w;
	}

	void fk_Dimension::x::set(int value)
	{
		pDim->w = value;
	}

	int fk_Dimension::y::get()
	{
		return pDim->h;
	}

	void fk_Dimension::y::set(int value)
	{
		pDim->h = value;
	}

	String^	fk_Dimension::ToString()
	{
		string	tmpBuf;
		tmpBuf = "DIM: " + to_string(pDim->w) + ", ";
		tmpBuf += to_string(pDim->h);
		return gcnew String(tmpBuf.c_str());
	}
	
	void fk_Dimension::Set(int argW, int argH)
	{
		GetP()->set(argW, argH);
	}
	
	//////////////////////////////////////////////////////////////



	::fk_Rect * fk_Rect::GetP(void)
	{
		return pRect;
	}

	fk_Rect::fk_Rect()
	{
		pRect = new ::fk_Rect();
	}

	fk_Rect::fk_Rect(int argX, int argY, int argW, int argH)
	{
		pRect = new ::fk_Rect(argX, argY, argW, argH);
	}

	fk_Rect::~fk_Rect()
	{
		this->!fk_Rect();
	}

	fk_Rect::!fk_Rect()
	{
		delete pRect;
	}

	int fk_Rect::x::get()
	{
		return pRect->x;
	}

	void fk_Rect::x::set(int value)
	{
		pRect->x = value;
	}

	int fk_Rect::y::get()
	{
		return pRect->y;
	}

	void fk_Rect::y::set(int value)
	{
		pRect->y = value;
	}

	int fk_Rect::w::get()
	{
		return pRect->w;
	}

	void fk_Rect::w::set(int value)
	{
		pRect->w = value;
	}

	int fk_Rect::h::get()
	{
		return pRect->h;
	}

	void fk_Rect::h::set(int value)
	{
		pRect->h = value;
	}
	
	String^	fk_Rect::ToString()
	{
		string	tmpBuf;
		tmpBuf = "RECT: ";
		tmpBuf += to_string(pRect->x) + ", ";
		tmpBuf += to_string(pRect->y) + ", ";
		tmpBuf += to_string(pRect->w) + ", ";
		tmpBuf += to_string(pRect->h);
		return gcnew String(tmpBuf.c_str());
	}

	void fk_Rect::Set(int argX, int argY, int argW, int argH)
	{
		GetP()->set(argX, argY, argW, argH);
	}

	void fk_Rect::SetPos(int argX, int argY)
	{
		GetP()->setPos(argX, argY);
	}

	void fk_Rect::SetSize(int argW, int argH)
	{
		GetP()->setSize(argW, argH);
	}

	fk_Dimension^ fk_Rect::GetSize(void)
	{
		fk_Dimension^ D = gcnew fk_Dimension();
		*D->pDim = GetP()->getSize();
		return D;
	}

	/////////////////////////////////////////////////////////////////////

	::fk_Image * fk_Image::GetP(void)
	{
		return (::fk_Image *)(pBase);
	}
	
	fk_Image::fk_Image() : fk_BaseObject(false)
	{
		pBase = new ::fk_Image();
	}

	fk_Image::fk_Image(bool argNewFlg) : fk_BaseObject(false)
	{
		if(argNewFlg == true) {
			pBase = new ::fk_Image();
		}
	}

	fk_Image::fk_Image(int argW, int argH) : fk_BaseObject(false)
	{
		pBase = new ::fk_Image(argW, argH);
	}

	fk_Image::~fk_Image()
	{
		this->!fk_Image();
	}

	fk_Image::!fk_Image()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	fk_Color^ fk_Image::default::get(int argX, int argY)
	{
		fk_Color^ C = gcnew fk_Color();
		*C->pCol = GetP()->getColor(argX, argY);
		return C;
	}

	void fk_Image::default::set(int argX, int argY, fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->setColor(argX, argY, *(argC->pCol));
	}

	fk_Dimension^ fk_Image::Size::get(void)
	{
		fk_Dimension^ D = gcnew fk_Dimension();
		*D->pDim = *(GetP()->getImageSize());
		return D;
	}

	fk_Dimension^ fk_Image::BufferSize::get(void)
	{
		fk_Dimension^ D = gcnew fk_Dimension();
		*D->pDim = *(GetP()->getBufferSize());
		return D;
	}
				
	void fk_Image::Init(void)
	{
		GetP()->init();
	}

	void fk_Image::NewImage(int argW, int argH, bool argInitFlg)
	{
		GetP()->newImage(argW, argH, argInitFlg);
	}

	void fk_Image::NewImage(int argW, int argH)
	{
		GetP()->newImage(argW, argH, true);
	}

	void fk_Image::CopyImage(fk_Image^ argImage)
	{
		if(!argImage) return;
		GetP()->copyImage(argImage->GetP());
	}

	void fk_Image::CopyImage(fk_Image^ argImage, int argX, int argY)
	{
		if(!argImage) return;
		GetP()->copyImage(argImage->GetP(), argX, argY);
	}

	bool fk_Image::SubImage(fk_Image^ argImage, int argX, int argY, int argW, int argH)
	{
		if(!argImage) return false;
		return GetP()->subImage(argImage->GetP(), argX, argY, argW, argH);
	}

	int	fk_Image::GetR(int argX, int argY)
	{
		return GetP()->getR(argX, argY);
	}

	int fk_Image::GetG(int argX, int argY)
	{
		return GetP()->getG(argX, argY);
	}

	int fk_Image::GetB(int argX, int argY)
	{
		return GetP()->getB(argX, argY);
	}
	int fk_Image::GetA(int argX, int argY)
	{
		return GetP()->getA(argX, argY);
	}

	bool fk_Image::SetRGBA(int argX, int argY, int argR, int argG, int argB, int argA)
	{
		return GetP()->setRGBA(argX, argY, argR, argG, argB, argA);
	}

	bool fk_Image::SetRGB(int argX, int argY, int argR, int argG, int argB)
	{
		return GetP()->setRGB(argX, argY, argR, argG, argB);
	}

	bool fk_Image::SetR(int argX, int argY, int argR)
	{
		return GetP()->setR(argX, argY, argR);
	}

	bool fk_Image::SetG(int argX, int argY, int argG)
	{
		return GetP()->setG(argX, argY, argG);
	}

	bool fk_Image::SetB(int argX, int argY, int argB)
	{
		return GetP()->setB(argX, argY, argB);
	}

	bool fk_Image::SetA(int argX, int argY, int argA)
	{
		return GetP()->setA(argX, argY, argA);
	}

	bool fk_Image::ReadBMP(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readBMP(marshal_as<string>(argFileName));
	}

	bool fk_Image::ReadPNG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readPNG(marshal_as<string>(argFileName));
	}

	bool fk_Image::ReadJPG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->readJPG(marshal_as<string>(argFileName));
	}

	bool fk_Image::WriteBMP(String^ argFileName, bool argTransFlg)
	{
		if(!argFileName) return false;
		return GetP()->writeBMP(marshal_as<string>(argFileName), argTransFlg);
	}

	bool fk_Image::WriteBMP(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->writeBMP(marshal_as<string>(argFileName), false);
	}

	bool fk_Image::WritePNG(String^ argFileName, bool argTransFlg)
	{
		if(!argFileName) return false;
		return GetP()->writePNG(marshal_as<string>(argFileName), argTransFlg);
	}

	bool fk_Image::WritePNG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->writePNG(marshal_as<string>(argFileName), true);
	}

	bool fk_Image::WriteJPG(String^ argFileName, int argQuality)
	{
		if(!argFileName) return false;
		return GetP()->writeJPG(marshal_as<string>(argFileName), argQuality);
	}

	bool fk_Image::WriteJPG(String^ argFileName)
	{
		if(!argFileName) return false;
		return GetP()->writeJPG(marshal_as<string>(argFileName), 80);
	}

	void fk_Image::FillColor(fk_Color^ argC)
	{
		if(!argC) return;
		GetP()->fillColor(*argC->pCol);
	}

	void fk_Image::FillColor(int argR, int argG, int argB, int argA)
	{
		GetP()->fillColor(argR, argG, argB, argA);
	}
		
	void fk_Image::FillColor(int argR, int argG, int argB)
	{
		GetP()->fillColor(argR, argG, argB);
	}
}
