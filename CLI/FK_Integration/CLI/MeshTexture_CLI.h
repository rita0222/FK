// MeshTexture_CLI.h

#pragma once

#include <FK/Texture.h>
#include "Texture_CLI.h"
#include "Vector_CLI.h"
#include "IndexFace_CLI.h"

namespace FK_CLI
{
	using namespace std;
	using namespace System;
	using namespace msclr::interop;

	public ref class fk_MeshTexture : FK_CLI::fk_Texture {
	internal:
		::fk_MeshTexture * GetP(void)
		{
			return (::fk_MeshTexture *)(pBase);
		}

	public:
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
			if(dFlg == true) delete pBase;
			pBase = NULL;
		}

		void init(void)
		{
			GetP()->init();
		}
		
		bool setTriNum(int argN)
		{
			return GetP()->setTriNum(argN);
		}
		
		int getTriNum(void)
		{
			return GetP()->getTriNum();
		}
		
		bool setTextureCoord(int argTID, int argVID, double argX, double argY)
		{
			return GetP()->setTextureCoord(argTID, argVID, argX, argY);
		}

		bool setTextureCoord(int argTID, int argVID, fk_TexCoord^ argC)
		{
			if(!argC) return false;
			return GetP()->setTextureCoord(argTID, argVID, *argC->pTex);
		}

		bool setTriTextureCoord(int argTID, array<fk_TexCoord^>^ argArray)
		{
			if(!argArray) return false;
			
			vector<::fk_TexCoord> A(argArray->Length);
			for(int i = 0; i < argArray->Length; ++i) {
				A[i] = *argArray[i]->pTex;
			}
			return GetP()->setTriTextureCoord(argTID, &A);
		}

		fk_TexCoord^ getTextureCoord(int argTID, int argVID)
		{
			fk_TexCoord^ T = gcnew fk_TexCoord();
			*T->pTex = GetP()->getTextureCoord(argTID, argVID);
			return T;
		}

		bool setVertexPos(int argTID, int argVID, double argX, double argY, double argZ)
		{
			return GetP()->setVertexPos(argTID, argVID, argX, argY, argZ);
		}

		bool setVertexPos(int argTID, int argVID, fk_Vector^ argP)
		{
			if(!argP) return false;
			return GetP()->setVertexPos(argTID, argVID, *argP->pVec);
		}

		bool setTriPos(int argTID, array<fk_Vector^>^ argArray)
		{
			if(!argArray) return false;
			vector<::fk_Vector> A(argArray->Length);
			for(int i = 0; i < argArray->Length; ++i) {
				A[i] = *argArray[i]->pVec;
			}
			return GetP()->setTriPos(argTID, &A);
		}
				
		fk_Vector^ getVertexPos(int argTID, int argVID)
		{
			fk_Vector^ V = gcnew fk_Vector();
			*V->pVec = GetP()->getVertexPos(argTID, argVID);
			return V;
		}
				
		void putIndexFaceSet(fk_IndexFaceSet^ argIFS)
		{
			if(!argIFS) return;
			GetP()->putIndexFaceSet(argIFS->GetP());
		}

		bool readMQOFile(String^ argFileName, String^ argObjName, bool argContFlg)
		{
			if(!argFileName || !argObjName) return false;
			return GetP()->readMQOFile(marshal_as<string>(argFileName),
									   marshal_as<string>(argObjName), argContFlg);
		}

		bool readMQOFile(String^ argFileName, String^ argObjName)
		{
			if(!argFileName || !argObjName) return false;
			return GetP()->readMQOFile(marshal_as<string>(argFileName),
									   marshal_as<string>(argObjName));
		}
	};
}
