// IFSTexture_CLI.h

#pragma once

#include <FK/IFSTexture.h>
#include "Texture_CLI.h"
#include "IndexFace_CLI.h"

namespace FK_CLI
{
	public ref class fk_IFSTexture : fk_Texture {
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
			if(pBase == NULL) return;
			if(dFlg == true) delete GetP();
			pBase = NULL;
		}

		void init(void);
		fk_TexCoord^ getTextureCoord(int triID, int vertexID);
		fk_IndexFaceSet^ getIFS(void);
		void cloneShape(fk_IFSTexture^ IFSTexture);
		void setTextureCoord(int triID, int vertexID, fk_TexCoord^ texCoord);
		bool readMQOFile(String^ fileName, String^ objName, int materialID, bool contFlg);
		bool readMQOFile(String^ fileName, String^ objName, int materialID);
		bool readMQOFile(String^ fileName, String^ objName);
		bool readD3DXFile(String^ fileName, String^ objName, int materialID);
		bool readD3DXFile(String^ fileName, String^ objName);
		void setConnectMode(bool connectFlg);
		bool getConnectMode(void);
		bool moveVPosition(int vertexID, const fk_Vector^ pos, int order);
		bool moveVPosition(int vertexID, const fk_Vector^ pos);
		bool moveVPosition(int vertexID, double x, double y, double z, int order);
		bool moveVPosition(int vertexID, double x, double y, double z);
		void setAnimationTime(double time);
		void setBVHMotion(fk_BVHMotion^ BVH);
	};
}
