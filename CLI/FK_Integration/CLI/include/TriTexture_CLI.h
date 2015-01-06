// TriTexture_CLI.h

#pragma once

#include <FK/Texture.h>
#include "Texture_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{
	public ref class fk_TriTexture : fk_Texture {
	internal:
		::fk_TriTexture * GetP(void)
		{
			return (::fk_TriTexture *)(pBase);
		}

	public:
		fk_TriTexture::fk_TriTexture() : fk_Texture(false)
		{
			pBase = new ::fk_TriTexture();
		}

		fk_TriTexture::fk_TriTexture(bool argNewFlg) : fk_Texture(false)
		{
			if(argNewFlg == true) {
				pBase = new ::fk_TriTexture();
			}
		}

		fk_TriTexture::fk_TriTexture(fk_Image^ argImage) : fk_Texture(false)
		{
			if(!argImage) {
				pBase = new ::fk_TriTexture();
			} else {
				pBase = new ::fk_TriTexture(argImage->GetP());
			}
		}

		fk_TriTexture::~fk_TriTexture()
		{
			this->!fk_TriTexture();
		}

		fk_TriTexture::!fk_TriTexture()
		{
			if(dFlg == true) delete pBase;
			pBase = NULL;
		}

		void init(void);
		bool setTextureCoord(int ID, double x, double y);
		bool setTextureCoord(int ID, fk_TexCoord^ color);
		fk_TexCoord^ getTextureCoord(int ID);
		bool setVertexPos(int ID, double x, double y, double z);
		bool setVertexPos(int ID, fk_Vector^ pos);
		fk_Vector^ getVertexPos(int ID);
	};
}
