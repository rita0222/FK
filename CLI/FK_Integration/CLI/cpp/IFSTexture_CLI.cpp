#include "IFSTexture_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	::fk_IFSTexture * fk_IFSTexture::GetP(void)
	{
		return (::fk_IFSTexture *)(pBase);
	}

	fk_IFSTexture::fk_IFSTexture() : fk_Texture(false)
	{
		pBase = new ::fk_IFSTexture();
	}

	fk_IFSTexture::fk_IFSTexture(bool argNewFlg) : fk_Texture(false)
	{
		if(argNewFlg == true) {
			pBase = new ::fk_IFSTexture();
		}
	}

	fk_IFSTexture::fk_IFSTexture(fk_Image^ argImage) : fk_Texture(false)
	{
		if(!argImage) {
			pBase = new ::fk_IFSTexture();
		} else {
			pBase = new ::fk_IFSTexture(argImage->GetP());
		}
	}

	fk_IFSTexture::~fk_IFSTexture()
	{
		this->!fk_IFSTexture();
	}

	fk_IFSTexture::!fk_IFSTexture()
	{
		if(pBase == nullptr) return;
		if(dFlg == true) delete GetP();
		pBase = nullptr;
	}

	fk_IndexFaceSet^ fk_IFSTexture::IFS::get(void)
	{
		fk_IndexFaceSet^ IFS = gcnew fk_IndexFaceSet(false);
		IFS->pBase = GetP()->getIFS();
		IFS->dFlg = false;
		return IFS;
	}
				
	void fk_IFSTexture::AnimationTime::set(double argT)
	{
		GetP()->setAnimationTime(argT);
	}

	void fk_IFSTexture::BVHMotion::set(fk_BVHMotion^ argBVH)
	{
		if(!argBVH) return;
		GetP()->setBVHMotion(argBVH->pMotion);
	}

	void fk_IFSTexture::ConnectMode::set(bool argConnectFlg)
	{
		GetP()->setConnectMode(argConnectFlg);
	}

	bool fk_IFSTexture::ConnectMode::get(void)
	{
		return GetP()->getConnectMode();
	}

	void fk_IFSTexture::Init(void)
	{
		GetP()->init();
	}
		
	fk_TexCoord^ fk_IFSTexture::GetTextureCoord(int argTID, int argVID)
	{
		fk_TexCoord^ T = gcnew fk_TexCoord();
		*T->pTex = GetP()->getTextureCoord(argTID, argVID);
		return T;
	}

	void fk_IFSTexture::CloneShape(fk_IFSTexture^ argIT)
	{
		if(!argIT) return;
		GetP()->cloneShape(argIT->GetP());
	}

	void fk_IFSTexture::SetTextureCoord(int argTID, int argVID, fk_TexCoord^ argTex)
	{
		if(!argTex) return;

		GetP()->setTextureCoord(argTID, argVID, *argTex->pTex);
	}

	bool fk_IFSTexture::ReadMQOFile(String^ argFileName, String^ argObjName,
									int argMatID, bool argContFlg)
	{
		if(!argFileName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName),
								   argMatID, argContFlg);

	}

	bool fk_IFSTexture::ReadMQOFile(String^ argFileName, String^ argObjName, int argMatID)
	{
		if(!argFileName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName), argMatID);
	}

	bool fk_IFSTexture::ReadMQOFile(String^ argFileName, String^ argObjName)
	{
		if(!argFileName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName));
	}

	bool fk_IFSTexture::ReadD3DXFile(String^ argFileName, String^ argObjName, int argMatID)
	{
		if(!argFileName || !argObjName) return false;
		return GetP()->readD3DXFile(marshal_as<string>(argFileName),
									marshal_as<string>(argObjName), argMatID);
	}

	bool fk_IFSTexture::ReadD3DXFile(String^ argFileName, String^ argObjName)
	{
		if(!argFileName || !argObjName) return false;
		return GetP()->readD3DXFile(marshal_as<string>(argFileName),
									marshal_as<string>(argObjName));
	}

	bool fk_IFSTexture::MoveVPosition(int argVID, const fk_Vector^ argP, int argOrder)
	{
		if(!argP) return false;
		return GetP()->moveVPosition(argVID, *argP->pVec, argOrder);
	}
				
	bool fk_IFSTexture::MoveVPosition(int argVID, const fk_Vector^ argP)
	{
		if(!argP) return false;
		return GetP()->moveVPosition(argVID, *argP->pVec);
	}

	bool fk_IFSTexture::MoveVPosition(int argVID, double argX, double argY, double argZ,
									  int argOrder)
	{
		return GetP()->moveVPosition(argVID, argX, argY, argZ, argOrder);
	}

	bool fk_IFSTexture::MoveVPosition(int argVID, double argX, double argY, double argZ)
	{
		return GetP()->moveVPosition(argVID, argX, argY, argZ);
	}

}

