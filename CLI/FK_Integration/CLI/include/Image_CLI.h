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

		::fk_Dimension * GetP(void);

	public:
		fk_Dimension();
		fk_Dimension(int argW, int argH);
		~fk_Dimension();
		!fk_Dimension();

		property int w {
			int get();
			void set(int value);
		}

		property int h {
			int get();
			void set(int value);
		}

		property int x {
			int get();
			void set(int value);
		}

		property int y {
			int get();
			void set(int value);
		}

		String^	ToString() override;
		void Set(int w, int g);
	};

	public ref class fk_Rect {
	internal:
		::fk_Rect	*pRect;

		::fk_Rect * GetP(void);

	public:
		fk_Rect();
		fk_Rect(int argX, int argY, int argW, int argH);
		~fk_Rect();
		!fk_Rect();

		property int x {
			int get();
			void set(int value);
		}

		property int y {
			int get();
			void set(int value);
		}

		property int w {
			int get();
			void set(int value);
		}

		property int h {
			int get();
			void set(int value);
		}

		String^	ToString() override;
		void Set(int argX, int argY, int argW, int argH);
		void SetPos(int argX, int argY);
		void SetSize(int argW, int argH);
		fk_Dimension^ GetSize(void);
	};

	public ref class fk_Image : fk_BaseObject {
	internal:
		::fk_Image * GetP(void);

	public:
		fk_Image();
		fk_Image(bool argNewFlg);
		fk_Image(int argW, int argH);
		~fk_Image();
		!fk_Image();

		property fk_Color^ default[int, int] {
			fk_Color^ get(int, int);
			void set(int, int, fk_Color^);
		}

		property fk_Dimension^ Size {
			fk_Dimension^ get();
		}

		property fk_Dimension^ BufferSize {
			fk_Dimension^ get();
		}

		void Init(void);
		void NewImage(int w, int h, bool InitFlg);
		void NewImage(int w, int h);
		void CopyImage(fk_Image^ Image);
		void CopyImage(fk_Image^ Image, int x, int y);
		bool SubImage(fk_Image^ Image, int x, int y, int w, int h);

		int	GetR(int x, int y);
		int GetG(int x, int y);
		int GetB(int x, int y);
		int GetA(int x, int y);
		bool SetRGBA(int x, int y, int r, int g, int b, int a);
		bool SetRGB(int x, int y, int r, int g, int b);
		bool SetR(int x, int y, int r);
		bool SetG(int x, int y, int g);
		bool SetB(int x, int y, int b);
		bool SetA(int x, int y, int a);
		void FillColor(fk_Color^ color);
		void FillColor(int r, int g, int b, int a);
		void FillColor(int r, int g, int b);

		bool ReadBMP(String^ fileName);
		bool ReadPNG(String^ fileName);
		bool ReadJPG(String^ fileName);
		bool WriteBMP(String^ fileName, bool transFlg);
		bool WriteBMP(String^ fileName);
		bool WritePNG(String^ fileName, bool transFlg);
		bool WritePNG(String^ fileName);
		bool WriteJPG(String^ fileName, int quality);
		bool WriteJPG(String^ fileName);
	};
}
