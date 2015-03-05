// TriTexture_CLI.h

#pragma once

#include <FK/Texture.h>
#include "Texture_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{
	public ref class fk_TriTexture : fk_Texture {
	internal:
		::fk_TriTexture * GetP(void);

	public:
		fk_TriTexture();
		fk_TriTexture(bool argNewFlg);
		fk_TriTexture(fk_Image^ argImage);
		~fk_TriTexture();
		!fk_TriTexture();

		void Init(void);
		bool SetTextureCoord(int ID, double x, double y);
		bool SetTextureCoord(int ID, fk_TexCoord^ color);
		fk_TexCoord^ GetTextureCoord(int ID);
		bool SetVertexPos(int ID, double x, double y, double z);
		bool SetVertexPos(int ID, fk_Vector^ pos);
		fk_Vector^ GetVertexPos(int ID);
	};
}
