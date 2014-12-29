// Texture_CLI.h

#pragma once

#include <FK/IFSTexture.h>
#include "Texture_CLI.h"
#include "IndexFace_CLI.h"

namespace FK_CLI
{
	using namespace std;
	using namespace System;
	using namespace msclr::interop;

	public ref class fk_IFSTexture : FK_CLI::fk_Texture {
	internal:
		::fk_IFSTexture * GetP(void)
		{
			return (::fk_IFSTexture *)(pBase);
		}

	public:
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
			if(dFlg == true) delete pBase;
			pBase = NULL;
		}

		void init(void)
		{
			GetP()->init();
		}
		
		fk_TexCoord^ getTextureCoord(int argTID, int argVID)
		{
			fk_TexCoord^ T = gcnew fk_TexCoord();
			*T->pTex = GetP()->getTextureCoord(argTID, argVID);
			return T;
		}

		fk_IndexFaceSet^ getIFS(void)
		{
			fk_IndexFaceSet^ IFS = gcnew fk_IndexFaceSet(false);
			IFS->pBase = GetP()->getIFS();
			IFS->dFlg = false;
			return IFS;
		}
				
		void cloneShape(fk_IFSTexture^ argIT)
		{
			if(!argIT) return;
			GetP()->cloneShape(argIT->GetP());
		}

		void setTextureCoord(int argTID, int argVID, fk_TexCoord^ argTex)
		{
			if(!argTex) return;

			GetP()->setTextureCoord(argTID, argVID, *argTex->pTex);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName, int argMatID, bool argContFlg)
		{
			if(!argFileName || !argObjName) return false;
			return GetP()->readMQOFile(marshal_as<string>(argFileName),
									   marshal_as<string>(argObjName),
									   argMatID, argContFlg);

		}

		bool readMQOFile(String^ argFileName, String^ argObjName, int argMatID)
		{
			if(!argFileName || !argObjName) return false;
			return GetP()->readMQOFile(marshal_as<string>(argFileName),
									   marshal_as<string>(argObjName), argMatID);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName)
		{
			if(!argFileName || !argObjName) return false;
			return GetP()->readMQOFile(marshal_as<string>(argFileName),
									   marshal_as<string>(argObjName));
		}

		bool readD3DXFile(String^ argFileName, String^ argObjName, int argMatID)
		{
			if(!argFileName || !argObjName) return false;
			return GetP()->readD3DXFile(marshal_as<string>(argFileName),
										marshal_as<string>(argObjName), argMatID);
		}

		bool readD3DXFile(String^ argFileName, String^ argObjName)
		{
			if(!argFileName || !argObjName) return false;
			return GetP()->readD3DXFile(marshal_as<string>(argFileName),
										marshal_as<string>(argObjName));
		}

		void setConnectMode(bool argConnectFlg)
		{
			GetP()->setConnectMode(argConnectFlg);
		}

		bool getConnectMode(void)
		{
			return GetP()->getConnectMode();
		}

		bool moveVPosition(int argVID, const fk_Vector^ argP, int argOrder)
		{
			if(!argP) return false;
			return GetP()->moveVPosition(argVID, *argP->pVec, argOrder);
		}
				
		bool moveVPosition(int argVID, const fk_Vector^ argP)
		{
			if(!argP) return false;
			return GetP()->moveVPosition(argVID, *argP->pVec);
		}

		bool moveVPosition(int argVID, double argX, double argY, double argZ, int argOrder)
		{
			return GetP()->moveVPosition(argVID, argX, argY, argZ, argOrder);
		}

		bool moveVPosition(int argVID, double argX, double argY, double argZ)
		{
			return GetP()->moveVPosition(argVID, argX, argY, argZ);
		}

		void setAnimationTime(double argT)
		{
			GetP()->setAnimationTime(argT);
		}

		//void setBVHMotion(fk_BVHMotion^ argBVH);
	};
}
