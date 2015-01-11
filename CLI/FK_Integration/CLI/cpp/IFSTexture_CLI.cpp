#include "IFSTexture_CLI.h"
#include <msclr/marshal_cppstd.h>

namespace FK_CLI {
	using namespace std;
	using namespace msclr::interop;

	void fk_IFSTexture::init(void)
	{
		GetP()->init();
	}
		
	fk_TexCoord^ fk_IFSTexture::getTextureCoord(int argTID, int argVID)
	{
		fk_TexCoord^ T = gcnew fk_TexCoord();
		*T->pTex = GetP()->getTextureCoord(argTID, argVID);
		return T;
	}

	fk_IndexFaceSet^ fk_IFSTexture::getIFS(void)
	{
		fk_IndexFaceSet^ IFS = gcnew fk_IndexFaceSet(false);
		IFS->pBase = GetP()->getIFS();
		IFS->dFlg = false;
		return IFS;
	}
				
	void fk_IFSTexture::cloneShape(fk_IFSTexture^ argIT)
	{
		if(!argIT) return;
		GetP()->cloneShape(argIT->GetP());
	}

	void fk_IFSTexture::setTextureCoord(int argTID, int argVID, fk_TexCoord^ argTex)
	{
		if(!argTex) return;

		GetP()->setTextureCoord(argTID, argVID, *argTex->pTex);
	}

	bool fk_IFSTexture::readMQOFile(String^ argFileName, String^ argObjName,
									int argMatID, bool argContFlg)
	{
		if(!argFileName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName),
								   argMatID, argContFlg);

	}

	bool fk_IFSTexture::readMQOFile(String^ argFileName, String^ argObjName, int argMatID)
	{
		if(!argFileName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName), argMatID);
	}

	bool fk_IFSTexture::readMQOFile(String^ argFileName, String^ argObjName)
	{
		if(!argFileName || !argObjName) return false;
		return GetP()->readMQOFile(marshal_as<string>(argFileName),
								   marshal_as<string>(argObjName));
	}

	bool fk_IFSTexture::readD3DXFile(String^ argFileName, String^ argObjName, int argMatID)
	{
		if(!argFileName || !argObjName) return false;
		return GetP()->readD3DXFile(marshal_as<string>(argFileName),
									marshal_as<string>(argObjName), argMatID);
	}

	bool fk_IFSTexture::readD3DXFile(String^ argFileName, String^ argObjName)
	{
		if(!argFileName || !argObjName) return false;
		return GetP()->readD3DXFile(marshal_as<string>(argFileName),
									marshal_as<string>(argObjName));
	}

	void fk_IFSTexture::setConnectMode(bool argConnectFlg)
	{
		GetP()->setConnectMode(argConnectFlg);
	}

	bool fk_IFSTexture::getConnectMode(void)
	{
		return GetP()->getConnectMode();
	}

	bool fk_IFSTexture::moveVPosition(int argVID, const fk_Vector^ argP, int argOrder)
	{
		if(!argP) return false;
		return GetP()->moveVPosition(argVID, *argP->pVec, argOrder);
	}
				
	bool fk_IFSTexture::moveVPosition(int argVID, const fk_Vector^ argP)
	{
		if(!argP) return false;
		return GetP()->moveVPosition(argVID, *argP->pVec);
	}

	bool fk_IFSTexture::moveVPosition(int argVID, double argX, double argY, double argZ,
									  int argOrder)
	{
		return GetP()->moveVPosition(argVID, argX, argY, argZ, argOrder);
	}

	bool fk_IFSTexture::moveVPosition(int argVID, double argX, double argY, double argZ)
	{
		return GetP()->moveVPosition(argVID, argX, argY, argZ);
	}

	void fk_IFSTexture::setAnimationTime(double argT)
	{
		GetP()->setAnimationTime(argT);
	}

	void fk_IFSTexture::setBVHMotion(fk_BVHMotion^ argBVH)
	{
		if(!argBVH) return;
		GetP()->setBVHMotion(argBVH->pMotion);
	}
}

