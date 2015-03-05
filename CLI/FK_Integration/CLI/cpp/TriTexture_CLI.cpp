#include "TriTexture_CLI.h"

namespace FK_CLI {

	::fk_TriTexture * fk_TriTexture::GetP(void)
	{
		return (::fk_TriTexture *)(pBase);
	}

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
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	void fk_TriTexture::Init(void)
	{
		GetP()->init();
	}

	bool fk_TriTexture::SetTextureCoord(int argID, double argX, double argY)
	{
		return GetP()->setTextureCoord(argID, argX, argY);
	}

	bool fk_TriTexture::SetTextureCoord(int argID, fk_TexCoord^ argC)
	{
		if(!argC) return false;
		return GetP()->setTextureCoord(argID, *argC->pTex);
	}

	fk_TexCoord^ fk_TriTexture::GetTextureCoord(int argID)
	{
		fk_TexCoord^ T = gcnew fk_TexCoord();
		*T->pTex = GetP()->getTextureCoord(argID);
		return T;
	}

	bool fk_TriTexture::SetVertexPos(int argID, double argX, double argY, double argZ)
	{
		return GetP()->setVertexPos(argID, argX, argY, argZ);
	}
		
	bool fk_TriTexture::SetVertexPos(int argID, fk_Vector^ argP)
	{
		if(!argP) return false;
		return GetP()->setVertexPos(argID, *argP->pVec);
	}

	fk_Vector^ fk_TriTexture::GetVertexPos(int argID)
	{
		return gcnew fk_Vector(GetP()->getVertexPos(argID));
	}
}
