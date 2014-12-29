// Texture_CLI.h

#pragma once

#include <FK/Texture.h>
#include "Texture_CLI.h"
#include "Vector_CLI.h"

namespace FK_CLI
{
	using namespace std;
	using namespace System;

	public ref class fk_TriTexture : FK_CLI::fk_Texture {
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

		void init(void)
		{
			GetP()->init();
		}

		bool setTextureCoord(int argID, double argX, double argY)
		{
			return GetP()->setTextureCoord(argID, argX, argY);
		}

		bool setTextureCoord(int argID, fk_TexCoord^ argC)
		{
			if(!argC) return false;
			return GetP()->setTextureCoord(argID, *argC->pTex);
		}

		fk_TexCoord^ getTextureCoord(int argID)
		{
			fk_TexCoord^ T = gcnew fk_TexCoord();
			*T->pTex = GetP()->getTextureCoord(argID);
			return T;
		}

		bool setVertexPos(int argID, double argX, double argY, double argZ)
		{
			return GetP()->setVertexPos(argID, argX, argY, argZ);
		}
		
		bool setVertexPos(int argID, fk_Vector^ argP)
		{
			if(!argP) return false;
			return GetP()->setVertexPos(argID, *argP->pVec);
		}

		fk_Vector^ getVertexPos(int argID)
		{
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = GetP()->getVertexPos(argID);
			return V;
		}
	};
}
