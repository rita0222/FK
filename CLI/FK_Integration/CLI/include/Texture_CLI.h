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
		double x_, y_;
		static operator ::fk_TexCoord (fk_TexCoord^);

	public:
		fk_TexCoord();
		fk_TexCoord(double argX, double argY);

#ifndef FK_DOXYGEN_USER_PROCESS
		fk_TexCoord(::fk_TexCoord);
		~fk_TexCoord();
		!fk_TexCoord();
#endif

		property double x {
			double get();
			void set(double v);
		}
		
		property double y {
			double get();
			void set(double v);
		}

		//////////////////// 比較演算子		
		bool Equals(fk_TexCoord^ argT);
		virtual bool Equals(Object^ argObj) override;

		void Set(double argX, double argY);
		String^ fk_TexCoord::ToString() override;
	};

	public ref class fk_Texture : fk_Shape {
	internal:
		::fk_Texture * GetP(void);

	public:
		fk_Texture(bool argNewFlg);
		~fk_Texture();
		!fk_Texture();

		property fk_Image^ Image {
			fk_Image^ get();
			void set(fk_Image^);
		}

		property fk_Dimension^ ImageSize {
			fk_Dimension^ get();
		}

		property fk_Dimension^ BufferSize {
			fk_Dimension^ get();
		}

		property fk_TexMode TextureMode {
			fk_TexMode get();
			void set(fk_TexMode);
		}

		property fk_TexRendMode RendMode {
			fk_TexRendMode get();
			void set(fk_TexRendMode);
		}
		
		bool	ReadBMP(String^ fileName);
		bool	ReadPNG(String^ fileName);
		bool	ReadJPG(String^ fileName);
		void	FillColor(fk_Color^ color);
	};
}
