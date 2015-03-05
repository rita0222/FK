// RectTexture_CLI.h

#pragma once

#include <FK/Texture.h>
#include "Texture_CLI.h"

namespace FK_CLI
{
	public ref class fk_RectTexture : fk_Texture {
	internal:
		::fk_RectTexture * GetP(void);

	public:
		fk_RectTexture();
		fk_RectTexture(bool argNewFlg);
		fk_RectTexture(fk_Image^ argImage);
		~fk_RectTexture();
		!fk_RectTexture();

		property fk_TexCoord^ TextureSize {
			void set(fk_TexCoord^);
			fk_TexCoord^ get();
		}

		property bool RepeatMode {
			void set(bool);
			bool get();
		}

		property fk_TexCoord^ RepeatParam {
			void set(fk_TexCoord^);
			fk_TexCoord^ get();
		}
		
		void			Init(void);
		void			SetTextureCoord(double startX, double startY, double endX, double endY);
		void			SetTextureCoord(fk_TexCoord^ startT, fk_TexCoord^ endT);
		fk_TexCoord^	GetTextureCoord(int ID);
	};
}
