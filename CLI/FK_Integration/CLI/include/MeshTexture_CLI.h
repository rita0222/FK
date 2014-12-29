// MeshTexture_CLI.h

#pragma once

#include <FK/Texture.h>
#include "Texture_CLI.h"
#include "Vector_CLI.h"
#include "IndexFace_CLI.h"

namespace FK_CLI
{
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

		void init(void);
		bool setTriNum(int num);
		int getTriNum(void);
		bool setTextureCoord(int triID, int vertexID, double x, double y);
		bool setTextureCoord(int triID, int vertexID, fk_TexCoord^ color);
		bool setTriTextureCoord(int triID, array<fk_TexCoord^>^ array);
		fk_TexCoord^ getTextureCoord(int triID, int vertexID);
		bool setVertexPos(int triID, int vertexID, double x, double y, double z);
		bool setVertexPos(int triID, int vertexID, fk_Vector^ pos);
		bool setTriPos(int triID, array<fk_Vector^>^ array);
		fk_Vector^ getVertexPos(int triID, int vertexID);
		void putIndexFaceSet(fk_IndexFaceSet^ IFS);
		bool readMQOFile(String^ fileName, String^ objName, bool contFlg);
		bool readMQOFile(String^ fileName, String^ objName);
	};
}
