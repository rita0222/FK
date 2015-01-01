#include "MeshTexture_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	void fk_MeshTexture::init(void)
	{
		GetP()->init();
	}
		
	bool fk_MeshTexture::setTriNum(int argN)
	{
		return GetP()->setTriNum(argN);
	}
		
	int fk_MeshTexture::getTriNum(void)
	{
		return GetP()->getTriNum();
	}
		
	bool fk_MeshTexture::setTextureCoord(int argTID, int argVID, double argX, double argY)
	{
		return GetP()->setTextureCoord(argTID, argVID, argX, argY);
	}

	bool fk_MeshTexture::setTextureCoord(int argTID, int argVID, fk_TexCoord^ argC)
	{
		if(!argC) return false;
		return GetP()->setTextureCoord(argTID, argVID, *argC->pTex);
	}

	bool fk_MeshTexture::setTriTextureCoord(int argTID, array<fk_TexCoord^>^ argArray)
	{
		if(!argArray) return false;
			
		vector<::fk_TexCoord> A(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			A[i] = *argArray[i]->pTex;
		}
		return GetP()->setTriTextureCoord(argTID, &A);
	}

	fk_TexCoord^ fk_MeshTexture::getTextureCoord(int argTID, int argVID)
	{
		fk_TexCoord^ T = gcnew fk_TexCoord();
		*T->pTex = GetP()->getTextureCoord(argTID, argVID);
		return T;
	}

	bool fk_MeshTexture::setVertexPos(int argTID, int argVID, double argX, double argY, double argZ)
	{
		return GetP()->setVertexPos(argTID, argVID, argX, argY, argZ);
	}

	bool fk_MeshTexture::setVertexPos(int argTID, int argVID, fk_Vector^ argP)
	{
		if(!argP) return false;
		return GetP()->setVertexPos(argTID, argVID, *argP->pVec);
	}

	bool fk_MeshTexture::setTriPos(int argTID, array<fk_Vector^>^ argArray)
	{
		if(!argArray) return false;
		vector<::fk_Vector> A(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			A[i] = *argArray[i]->pVec;
		}
		return GetP()->setTriPos(argTID, &A);
	}
				
	fk_Vector^ fk_MeshTexture::getVertexPos(int argTID, int argVID)
	{
		return gcnew fk_Vector(GetP()->getVertexPos(argTID, argVID));
	}
				
	void fk_MeshTexture::putIndexFaceSet(fk_IndexFaceSet^ argIFS)
	{
		if(!argIFS) return;
		GetP()->putIndexFaceSet(argIFS->GetP());
	}

	bool fk_MeshTexture::readMQOFile(String^ argFileName, String^ argObjName, bool argContFlg)
	{
		if(!argFileName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName), argContFlg);
	}

	bool fk_MeshTexture::readMQOFile(String^ argFileName, String^ argObjName)
	{
		if(!argFileName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName));
	}
}
