// Image_CLI.h

#pragma once

#include <FK/Image.h>
#include "Base_CLI.h"
#include "Material_CLI.h"

namespace FK_CLI
{
	using namespace std;
	using namespace System;
	using namespace msclr::interop;
	
	public enum class fk_ImageStatus {
		OK,
		OPENERROR,
		DATAERROR,
		READERROR
	};

	public enum class fk_ImageFix {
		FIX_LARGE,
		FIX_SMALL,
		FIX_64,
		FIX_128,
		FIX_256,
		FIX_512,
		FIX_1024,
		FIX_2048,
		FIX_4096,
		FIX_8192,
		FIX_16384,
		FIX_32768,
		FIX_65536
	};

	public enum class fk_ImageType {
		BMP,
		PNG,
		JPG
	};

	public enum class fk_SnapProcMode {
		FK_GL_FRONT,
		FK_GL_BACK,
		FK_WIN32_GDI,
		FK_D3D_WINDOW,
		FK_D3D_FULL
	};

	public ref class fk_Dimension {
	internal:
		::fk_Dimension	*pDim;

		::fk_Dimension * GetP(void)
		{
			return pDim;
		}

	public:
		fk_Dimension::fk_Dimension()
		{
			pDim = new ::fk_Dimension();
		}

		fk_Dimension::fk_Dimension(int argW, int argH)
		{
			pDim = new ::fk_Dimension(argW, argH);
		}

		// デストラクタ
		fk_Dimension::~fk_Dimension()
		{
			this->!fk_Dimension();
		}

		// ファイナライザ
		fk_Dimension::!fk_Dimension()
		{
			delete pDim;
		}

		property int w {
			int get()
			{
				return pDim->w;
			}

			void set(int value)
			{
				pDim->w = value;
			}
		}

		property int h {
			int get()
			{
				return pDim->h;
			}

			void set(int value)
			{
				pDim->h = value;
			}
		}

		String^	ToString() override
		{
			std::string	tmpBuf;
			tmpBuf = "DIM: " + to_string(pDim->w) + ", ";
			tmpBuf += to_string(pDim->h);
			return gcnew String(tmpBuf.c_str());
		}

		void set(int argW, int argH)
		{
			GetP()->set(argW, argH);
		}
	};

	public ref class fk_Rect {
	internal:
		::fk_Rect	*pRect;

		::fk_Rect * GetP(void)
		{
			return pRect;
		}

	public:
		fk_Rect::fk_Rect()
		{
			pRect = new ::fk_Rect();
		}

		fk_Rect::fk_Rect(int argX, int argY, int argW, int argH)
		{
			pRect = new ::fk_Rect(argX, argY, argW, argH);
		}

		// デストラクタ
		fk_Rect::~fk_Rect()
		{
			this->!fk_Rect();
		}

		// ファイナライザ
		fk_Rect::!fk_Rect()
		{
			delete pRect;
		}

		property int x {
			int get()
			{
				return pRect->x;
			}

			void set(int value)
			{
				pRect->x = value;
			}
		}

		property int y {
			int get()
			{
				return pRect->y;
			}

			void set(int value)
			{
				pRect->y = value;
			}
		}

		property int w {
			int get()
			{
				return pRect->w;
			}

			void set(int value)
			{
				pRect->w = value;
			}
		}

		property int h {
			int get()
			{
				return pRect->h;
			}

			void set(int value)
			{
				pRect->h = value;
			}
		}

		String^	ToString() override
		{
			std::string	tmpBuf;
			tmpBuf = "RECT: ";
			tmpBuf += to_string(pRect->x) + ", ";
			tmpBuf += to_string(pRect->y) + ", ";
			tmpBuf += to_string(pRect->w) + ", ";
			tmpBuf += to_string(pRect->h);
			return gcnew String(tmpBuf.c_str());
		}

		void set(int argX, int argY, int argW, int argH)
		{
			GetP()->set(argX, argY, argW, argH);
		}

		void setPos(int argX, int argY)
		{
			GetP()->setPos(argX, argY);
		}

		void setSize(int argW, int argH)
		{
			GetP()->setSize(argW, argH);
		}

		fk_Dimension^ getSize(void)
		{
			fk_Dimension^ D = gcnew fk_Dimension();
			*D->pDim = GetP()->getSize();
			return D;
		}
	};

	public ref class fk_Image : FK_CLI::fk_BaseObject {
	internal:
		::fk_Image * GetP(void)
		{
			return (::fk_Image *)(pBase);
		}

	public:
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
			if(dFlg == true) delete pBase;
			pBase = NULL;
		}

		void init(void)
		{
			GetP()->init();
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

		bool writeBMP(String^ argFileName, bool argTransFlg)
		{
			if(!argFileName) return false;
			return GetP()->writeBMP(marshal_as<string>(argFileName), argTransFlg);
		}

		bool writeBMP(String^ argFileName)
		{
			if(!argFileName) return false;
			return GetP()->writeBMP(marshal_as<string>(argFileName), false);
		}

		bool writePNG(String^ argFileName, bool argTransFlg)
		{
			if(!argFileName) return false;
			return GetP()->writePNG(marshal_as<string>(argFileName), argTransFlg);
		}

		bool writePNG(String^ argFileName)
		{
			if(!argFileName) return false;
			return GetP()->writePNG(marshal_as<string>(argFileName), true);
		}

		bool writeJPG(String^ argFileName, int argQuality)
		{
			if(!argFileName) return false;
			return GetP()->writeJPG(marshal_as<string>(argFileName), argQuality);
		}

		bool writeJPG(String^ argFileName)
		{
			if(!argFileName) return false;
			return GetP()->writeJPG(marshal_as<string>(argFileName), 80);
		}

		void newImage(int argW, int argH, bool argInitFlg)
		{
			GetP()->newImage(argW, argH, argInitFlg);
		}

		void newImage(int argW, int argH)
		{
			GetP()->newImage(argW, argH, true);
		}

		void copyImage(fk_Image^ argImage)
		{
			if(!argImage) return;
			GetP()->copyImage(argImage->GetP());
		}

		void copyImage(fk_Image^ argImage, int argX, int argY)
		{
			if(!argImage) return;
			GetP()->copyImage(argImage->GetP(), argX, argY);
		}

		bool subImage(fk_Image^ argImage, int argX, int argY, int argW, int argH)
		{
			if(!argImage) return false;
			return GetP()->subImage(argImage->GetP(), argX, argY, argW, argH);
		}
		
		int	getWidth(void)
		{
			return GetP()->getWidth();
		}

		int getHeight(void)
		{
			return GetP()->getHeight();
		}
		
		fk_Dimension^ getImageSize(void)
		{
			fk_Dimension^ D = gcnew fk_Dimension();
			*D->pDim = *(GetP()->getImageSize());
			return D;
		}
				
		fk_Dimension^ getBufferSize(void)
		{
			fk_Dimension^ D = gcnew fk_Dimension();
			*D->pDim = *(GetP()->getBufferSize());
			return D;
		}
				
		int	getR(int argX, int argY)
		{
			return GetP()->getR(argX, argY);
		}

		int getG(int argX, int argY)
		{
			return GetP()->getG(argX, argY);
		}

		int getB(int argX, int argY)
		{
			return GetP()->getB(argX, argY);
		}
		int getA(int argX, int argY)
		{
			return GetP()->getA(argX, argY);
		}

		fk_Color^ getColor(int argX, int argY)
		{
			fk_Color^ C = gcnew fk_Color();
			*C->pCol = GetP()->getColor(argX, argY);
			return C;
		}

		bool setRGBA(int argX, int argY, int argR, int argG, int argB, int argA)
		{
			return GetP()->setRGBA(argX, argY, argR, argG, argB, argA);
		}

		bool setRGB(int argX, int argY, int argR, int argG, int argB)
		{
			return GetP()->setRGB(argX, argY, argR, argG, argB);
		}

		bool setR(int argX, int argY, int argR)
		{
			return GetP()->setR(argX, argY, argR);
		}

		bool setG(int argX, int argY, int argG)
		{
			return GetP()->setG(argX, argY, argG);
		}

		bool setB(int argX, int argY, int argB)
		{
			return GetP()->setB(argX, argY, argB);
		}

		bool setA(int argX, int argY, int argA)
		{
			return GetP()->setA(argX, argY, argA);
		}

		bool setColor(int argX, int argY, fk_Color^ argC)
		{
			if(!argC) return false;
			return GetP()->setColor(argX, argY, *(argC->pCol));
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
}
