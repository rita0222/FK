// SpriteModel_CLI.h

#pragma once

#include <FK/SpriteModel.h>
#include "Model_CLI.h"
#include "Texture_CLI.h"
#include "TextImage_CLI.h"

namespace FK_CLI
{
	public ref class fk_SpriteModel : fk_Model {
	internal:
		::fk_SpriteModel * GetP(void);

	public:
		fk_SpriteModel();
		fk_SpriteModel(bool argNewFlg);
		~fk_SpriteModel();
		!fk_SpriteModel();

		property fk_TextImage^ Text {
			fk_TextImage^ get();
		}

		property fk_Image^ Image {
			fk_Image^ get();
			void set(fk_Image^);
		}

		property fk_TexCoord^ Size {
			fk_TexCoord^ get();
			void set(fk_TexCoord^);
		}

		property bool SmoothMode {
			bool get();
			void set(bool);
		}

		bool			ReadBMP(String^ filename);
		bool			ReadPNG(String^ filename);
		bool			ReadJPG(String^ filename);
		void			SetPositionLT(double x, double y);
		void			SetSpriteArea(double x, double y, double w, double h);
		bool			InitFont(String^ fontFileName);
		void			DrawText(String^ str);
		void			DrawText(String^ str, bool mode);
		void			ClearText(void);
	};
}
