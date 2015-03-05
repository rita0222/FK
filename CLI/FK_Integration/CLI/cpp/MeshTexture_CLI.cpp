#include "MeshTexture_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	::fk_MeshTexture * fk_MeshTexture::GetP(void)
	{
		return (::fk_MeshTexture *)(pBase);
	}

	fk_MeshTexture::fk_MeshTexture() : fk_Texture(false)
	{
		pBase = new ::fk_MeshTexture();
	}

	fk_MeshTexture::fk_MeshTexture(bool argNewFlg) : fk_Texture(false)
	{
		if(argNewFlg == true) {
			pBase = new ::fk_MeshTexture();
		}
	}

	fk_MeshTexture::fk_MeshTexture(fk_Image^ argImage) : fk_Texture(false)
	{
		if(!argImage) {
			pBase = new ::fk_MeshTexture();
		} else {
			pBase = new ::fk_MeshTexture(argImage->GetP());
		}
	}

	fk_MeshTexture::~fk_MeshTexture()
	{
		this->!fk_MeshTexture();
	}

	fk_MeshTexture::!fk_MeshTexture()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	void fk_MeshTexture::TriNum::set(int argN)
	{
		GetP()->setTriNum(argN);
	}
		
	int fk_MeshTexture::TriNum::get(void)
	{
		return GetP()->getTriNum();
	}

	void fk_MeshTexture::Init(void)
	{
		GetP()->init();
	}
		
	bool fk_MeshTexture::SetTextureCoord(int argTID, int argVID, double argX, double argY)
	{
		return GetP()->setTextureCoord(argTID, argVID, argX, argY);
	}

	bool fk_MeshTexture::SetTextureCoord(int argTID, int argVID, fk_TexCoord^ argC)
	{
		if(!argC) return false;
		return GetP()->setTextureCoord(argTID, argVID, *argC->pTex);
	}

	bool fk_MeshTexture::SetTriTextureCoord(int argTID, array<fk_TexCoord^>^ argArray)
	{
		if(!argArray) return false;
			
		vector<::fk_TexCoord> A(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			A[i] = *argArray[i]->pTex;
		}
		return GetP()->setTriTextureCoord(argTID, &A);
	}

	fk_TexCoord^ fk_MeshTexture::GetTextureCoord(int argTID, int argVID)
	{
		fk_TexCoord^ T = gcnew fk_TexCoord();
		*T->pTex = GetP()->getTextureCoord(argTID, argVID);
		return T;
	}

	bool fk_MeshTexture::SetVertexPos(int argTID, int argVID, double argX, double argY, double argZ)
	{
		return GetP()->setVertexPos(argTID, argVID, argX, argY, argZ);
	}

	bool fk_MeshTexture::SetVertexPos(int argTID, int argVID, fk_Vector^ argP)
	{
		if(!argP) return false;
		return GetP()->setVertexPos(argTID, argVID, *argP->pVec);
	}

	bool fk_MeshTexture::SetTriPos(int argTID, array<fk_Vector^>^ argArray)
	{
		if(!argArray) return false;
		vector<::fk_Vector> A(argArray->Length);
		for(int i = 0; i < argArray->Length; ++i) {
			A[i] = *argArray[i]->pVec;
		}
		return GetP()->setTriPos(argTID, &A);
	}
				
	fk_Vector^ fk_MeshTexture::GetVertexPos(int argTID, int argVID)
	{
		return gcnew fk_Vector(GetP()->getVertexPos(argTID, argVID));
	}
				
	void fk_MeshTexture::PutIndexFaceSet(fk_IndexFaceSet^ argIFS)
	{
		if(!argIFS) return;
		GetP()->putIndexFaceSet(argIFS->GetP());
	}

	bool fk_MeshTexture::ReadMQOFile(String^ argFileName, String^ argObjName, bool argContFlg)
	{
		if(!argFileName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName), argContFlg);
	}

	bool fk_MeshTexture::ReadMQOFile(String^ argFileName, String^ argObjName)
	{
		if(!argFileName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName));
	}
}
