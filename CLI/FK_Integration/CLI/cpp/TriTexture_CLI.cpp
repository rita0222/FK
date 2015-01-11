#include "TriTexture_CLI.h"

namespace FK_CLI {

	void fk_TriTexture::init(void)
	{
		GetP()->init();
	}

	bool fk_TriTexture::setTextureCoord(int argID, double argX, double argY)
	{
		return GetP()->setTextureCoord(argID, argX, argY);
	}

	bool fk_TriTexture::setTextureCoord(int argID, fk_TexCoord^ argC)
	{
		if(!argC) return false;
		return GetP()->setTextureCoord(argID, *argC->pTex);
	}

	fk_TexCoord^ fk_TriTexture::getTextureCoord(int argID)
	{
		fk_TexCoord^ T = gcnew fk_TexCoord();
		*T->pTex = GetP()->getTextureCoord(argID);
		return T;
	}

	bool fk_TriTexture::setVertexPos(int argID, double argX, double argY, double argZ)
	{
		return GetP()->setVertexPos(argID, argX, argY, argZ);
	}
		
	bool fk_TriTexture::setVertexPos(int argID, fk_Vector^ argP)
	{
		if(!argP) return false;
		return GetP()->setVertexPos(argID, *argP->pVec);
	}

	fk_Vector^ fk_TriTexture::getVertexPos(int argID)
	{
		return gcnew fk_Vector(GetP()->getVertexPos(argID));
	}
}
