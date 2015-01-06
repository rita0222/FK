// Image_CLI.h

#pragma once

#include <FK/Image.h>
#include "Base_CLI.h"
#include "Material_CLI.h"

namespace FK_CLI
{
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

		String^	ToString() override;
		void set(int w, int g);
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

		String^	ToString() override;
		void set(int argX, int argY, int argW, int argH);
		void setPos(int argX, int argY);
		void setSize(int argW, int argH);
		fk_Dimension^ getSize(void);
	};

	public ref class fk_Image : fk_BaseObject {
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

		void init(void);
		bool readBMP(String^ fileName);
		bool readPNG(String^ fileName);
		bool readJPG(String^ fileName);
		bool writeBMP(String^ fileName, bool transFlg);
		bool writeBMP(String^ fileName);
		bool writePNG(String^ fileName, bool transFlg);
		bool writePNG(String^ fileName);
		bool writeJPG(String^ fileName, int quality);
		bool writeJPG(String^ fileName);
		void newImage(int w, int h, bool InitFlg);
		void newImage(int w, int h);
		void copyImage(fk_Image^ Image);
		void copyImage(fk_Image^ Image, int x, int y);
		bool subImage(fk_Image^ Image, int x, int y, int w, int h);
		int	getWidth(void);
		int getHeight(void);
		fk_Dimension^ getImageSize(void);
		fk_Dimension^ getBufferSize(void);
		int	getR(int x, int y);
		int getG(int x, int y);
		int getB(int x, int y);
		int getA(int x, int y);
		fk_Color^ getColor(int x, int y);
		bool setRGBA(int x, int y, int r, int g, int b, int a);
		bool setRGB(int x, int y, int r, int g, int b);
		bool setR(int x, int y, int r);
		bool setG(int x, int y, int g);
		bool setB(int x, int y, int b);
		bool setA(int x, int y, int a);
		bool setColor(int x, int y, fk_Color^ color);
		void fillColor(fk_Color^ color);
		void fillColor(int r, int g, int b, int a);
		void fillColor(int r, int g, int b);
	};
}
